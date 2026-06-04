#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "arg.h"

char *argv0;

#include "config.h"

static void
usage(void)
{
	fprintf(stderr, "usage: dmenu-powermenu [-v]\n");
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

int
main(int argc, char *argv[])
{
	char selection[128];
	char confirm[64];
	size_t num_items = sizeof(items) / sizeof(items[0]);
	const char *labels[num_items];
	const PowermenuItem *selected = NULL;

	ARGBEGIN {
	case 'v':
		printf("dmenu-powermenu-"VERSION"\n");
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

	if (selected->confirm) {
		size_t num_conf = sizeof(confirm_options) / sizeof(confirm_options[0]);
		if (run_menu(confirm_cmd, confirm_options, num_conf, confirm, sizeof(confirm)) < 0) {
			return 0; /* Cancelled */
		}
		if (strcmp(confirm, "Yes") != 0) {
			return 0; /* Aborted */
		}
	}

	/* Execute the action */
	execl("/bin/sh", "sh", "-c", selected->command, (char *)NULL);
	perror("execl");
	return 1;
}
