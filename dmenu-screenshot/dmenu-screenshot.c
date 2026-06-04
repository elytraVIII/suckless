#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xinerama.h>

#include "arg.h"

char *argv0;

#include "config.h"

static void
usage(void)
{
	fprintf(stderr, "usage: dmenu-screenshot [-v]\n");
	exit(1);
}

static int
run_menu(const char *const cmd[], const char *const options[], size_t num_options, char *output, size_t out_len)
{
	int pin[2], pout[2];
	pid_t pid;

	if (pipe(pin) < 0) {
		perror("pipe");
		return -1;
	}
	if (pipe(pout) < 0) {
		perror("pipe");
		close(pin[0]);
		close(pin[1]);
		return -1;
	}

	pid = fork();
	if (pid < 0) {
		perror("fork");
		close(pin[0]);
		close(pin[1]);
		close(pout[0]);
		close(pout[1]);
		return -1;
	}

	if (pid == 0) {
		/* Child process */
		if (dup2(pin[0], STDIN_FILENO) < 0 || dup2(pout[1], STDOUT_FILENO) < 0) {
			perror("dup2");
			exit(1);
		}

		close(pin[0]);
		close(pin[1]);
		close(pout[0]);
		close(pout[1]);

		execvp(cmd[0], (char *const *)cmd);
		perror("execvp");
		exit(1);
	}

	/* Parent process */
	close(pin[0]);
	close(pout[1]);

	for (size_t i = 0; i < num_options; i++) {
		if (write(pin[1], options[i], strlen(options[i])) < 0 ||
		    write(pin[1], "\n", 1) < 0) {
			perror("write");
			close(pin[1]);
			close(pout[0]);
			waitpid(pid, NULL, 0);
			return -1;
		}
	}
	close(pin[1]); /* EOF to child */

	size_t total = 0;
	ssize_t n;
	while (total < out_len - 1 && (n = read(pout[0], output + total, out_len - 1 - total)) > 0) {
		total += n;
	}
	output[total] = '\0';
	close(pout[0]);

	/* Strip trailing newline if present */
	if (total > 0 && output[total - 1] == '\n') {
		output[total - 1] = '\0';
	}

	int status;
	waitpid(pid, &status, 0);

	if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && total > 0) {
		return 0;
	}
	return -1;
}

static Window
get_active_window(Display *dpy)
{
	Atom actual_type;
	int format;
	unsigned long nitems, bytes_after;
	unsigned char *prop = NULL;
	Window win = None;
	Atom net_active = XInternAtom(dpy, "_NET_ACTIVE_WINDOW", False);

	if (XGetWindowProperty(dpy, DefaultRootWindow(dpy), net_active, 0, 1, False,
	                       XA_WINDOW, &actual_type, &format, &nitems, &bytes_after, &prop) == Success && prop) {
		if (nitems > 0) {
			win = *(Window *)prop;
		}
		XFree(prop);
	}
	return win;
}

int
main(int argc, char *argv[])
{
	char selection[128];
	size_t num_items = sizeof(items) / sizeof(items[0]);
	const char *labels[num_items];
	const ScreenshotItem *selected = NULL;

	ARGBEGIN {
	case 'v':
		printf("dmenu-screenshot-"VERSION"\n");
		return 0;
	default:
		usage();
	} ARGEND

	if (argc > 0)
		usage();

	for (size_t i = 0; i < num_items; i++) {
		labels[i] = items[i].label;
	}

	if (run_menu(dmenu_cmd, labels, num_items, selection, sizeof(selection)) < 0) {
		return 0; /* Menu cancelled or failed */
	}

	for (size_t i = 0; i < num_items; i++) {
		if (strcmp(selection, items[i].label) == 0) {
			selected = &items[i];
			break;
		}
	}

	if (!selected) {
		fprintf(stderr, "Invalid selection: %s\n", selection);
		return 1;
	}

	/* Build target options for maim */
	char cmd_target[128] = "";
	Display *dpy = NULL;

	switch (selected->type) {
	case SCREENSHOT_FULLSCREEN:
		/* Default empty, captures full screen */
		break;
	case SCREENSHOT_SELECTION:
		snprintf(cmd_target, sizeof(cmd_target), "-s");
		break;
	case SCREENSHOT_WINDOW:
		dpy = XOpenDisplay(NULL);
		if (dpy) {
			Window win = get_active_window(dpy);
			if (win != None) {
				snprintf(cmd_target, sizeof(cmd_target), "-i 0x%lx", win);
			}
			XCloseDisplay(dpy);
		}
		break;
	case SCREENSHOT_MONITOR:
		dpy = XOpenDisplay(NULL);
		if (dpy) {
			int screen = DefaultScreen(dpy);
			int sw = DisplayWidth(dpy, screen);
			int sh = DisplayHeight(dpy, screen);
			int sx = 0, sy = 0;

			Window root = RootWindow(dpy, screen);
			Window root_return, child_return;
			int win_x, win_y;
			int root_x, root_y;
			unsigned int mask;

			if (XQueryPointer(dpy, root, &root_return, &child_return, &root_x, &root_y, &win_x, &win_y, &mask)) {
				int nscreens = 0;
				XineramaScreenInfo *info = NULL;
				if (XineramaIsActive(dpy)) {
					info = XineramaQueryScreens(dpy, &nscreens);
				}
				if (info && nscreens > 0) {
					for (int i = 0; i < nscreens; i++) {
						if (root_x >= info[i].x_org && root_x < info[i].x_org + info[i].width &&
						    root_y >= info[i].y_org && root_y < info[i].y_org + info[i].height) {
							sw = info[i].width;
							sh = info[i].height;
							sx = info[i].x_org;
							sy = info[i].y_org;
							break;
						}
					}
					XFree(info);
				}
			}
			snprintf(cmd_target, sizeof(cmd_target), "-g %dx%d+%d+%d", sw, sh, sx, sy);
			XCloseDisplay(dpy);
		}
		break;
	}

	/* Build final command */
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char timestamp[64];
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H-%M-%S", tm);

	const char *home = getenv("HOME");
	if (!home) {
		home = "/home/elytra";
	}

	char filename[512];
	snprintf(filename, sizeof(filename), "%s/Pictures/Screenshots/%s.png", home, timestamp);

	char cmd[2048];
	snprintf(cmd, sizeof(cmd),
	         "mkdir -p \"%s/Pictures/Screenshots\" && "
	         "maim %s \"%s\" && "
	         "xclip -selection clipboard -t image/png -i \"%s\"",
	         home, cmd_target, filename, filename);

	/* Execute command via shell */
	execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
	perror("execl");
	return 1;
}
