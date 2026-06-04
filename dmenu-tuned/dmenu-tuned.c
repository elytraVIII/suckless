#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "arg.h"

char *argv0;

#include "config.h"

#define MAX_PROFILES 128
#define MAX_PROFILE_LEN 64
#define MAX_DESC_LEN 256

typedef struct {
	char name[MAX_PROFILE_LEN];
	char desc[MAX_DESC_LEN];
} Profile;

static Profile profiles[MAX_PROFILES];
static size_t num_profiles = 0;

static void
usage(void)
{
	fprintf(stderr, "usage: dmenu-tuned [-v]\n");
	exit(1);
}

static int
get_active_profile(char *active, size_t len)
{
	FILE *fp;
	char line[256];
	const char *prefix = "Current active profile: ";
	size_t prefix_len = strlen(prefix);
	int found = 0;

	fp = popen("tuned-adm active 2>/dev/null", "r");
	if (!fp)
		return -1;

	while (fgets(line, sizeof(line), fp)) {
		line[strcspn(line, "\r\n")] = '\0';
		if (strncmp(line, prefix, prefix_len) == 0) {
			char *start = line + prefix_len;
			while (*start == ' ')
				start++;
			strncpy(active, start, len - 1);
			active[len - 1] = '\0';
			found = 1;
			break;
		}
	}
	pclose(fp);
	return found ? 0 : -1;
}

static int
get_dynamic_profiles(char *active_profile, size_t active_len)
{
	FILE *fp;
	char line[512];
	const char *active_prefix = "Current active profile: ";
	size_t active_prefix_len = strlen(active_prefix);

	fp = popen("tuned-adm list 2>/dev/null", "r");
	if (!fp)
		return -1;

	num_profiles = 0;
	while (fgets(line, sizeof(line), fp)) {
		line[strcspn(line, "\r\n")] = '\0';

		/* Parse available profile */
		if (strncmp(line, "- ", 2) == 0) {
			if (num_profiles >= MAX_PROFILES)
				continue;

			char *name_start = line + 2;
			char *desc_ptr = strstr(name_start, " - ");
			char *name_end = strchr(name_start, ' ');

			if (name_end && (!desc_ptr || name_end < desc_ptr)) {
				*name_end = '\0';
			}

			strncpy(profiles[num_profiles].name, name_start, sizeof(profiles[num_profiles].name) - 1);
			profiles[num_profiles].name[sizeof(profiles[num_profiles].name) - 1] = '\0';

			if (desc_ptr) {
				char *desc_start = desc_ptr + 3;
				while (*desc_start == ' ')
					desc_start++;
				strncpy(profiles[num_profiles].desc, desc_start, sizeof(profiles[num_profiles].desc) - 1);
				profiles[num_profiles].desc[sizeof(profiles[num_profiles].desc) - 1] = '\0';
			} else {
				profiles[num_profiles].desc[0] = '\0';
			}
			num_profiles++;
		}
		/* Parse active profile if printed at the end of output */
		else if (strncmp(line, active_prefix, active_prefix_len) == 0) {
			char *start = line + active_prefix_len;
			while (*start == ' ')
				start++;
			strncpy(active_profile, start, active_len - 1);
			active_profile[active_len - 1] = '\0';
		}
	}
	pclose(fp);
	return 0;
}

static void
get_static_profiles(char *active_profile, size_t active_len)
{
	/* Try to get active profile dynamically */
	if (get_active_profile(active_profile, active_len) < 0) {
		active_profile[0] = '\0';
	}

	size_t num_static = sizeof(static_profiles) / sizeof(static_profiles[0]);
	num_profiles = 0;
	for (size_t i = 0; i < num_static; i++) {
		if (num_profiles >= MAX_PROFILES)
			break;
		strncpy(profiles[num_profiles].name, static_profiles[i].name, sizeof(profiles[num_profiles].name) - 1);
		profiles[num_profiles].name[sizeof(profiles[num_profiles].name) - 1] = '\0';
		strncpy(profiles[num_profiles].desc, static_profiles[i].desc, sizeof(profiles[num_profiles].desc) - 1);
		profiles[num_profiles].desc[sizeof(profiles[num_profiles].desc) - 1] = '\0';
		num_profiles++;
	}
}

static int
run_menu(const char *const cmd[], const Profile items[], size_t num_items, const char *active, char *output, size_t out_len)
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

	/* Write options to dmenu */
	for (size_t i = 0; i < num_items; i++) {
		int is_active = (strcmp(items[i].name, active) == 0);
		char formatted_line[512];

		/* Format: "* <profile_name>       - <description>\n" or "  <profile_name>       - <description>\n" */
		snprintf(formatted_line, sizeof(formatted_line), "%s%-24.63s - %.255s\n",
		         is_active ? "* " : "  ",
		         items[i].name,
		         items[i].desc);

		if (write(pin[1], formatted_line, strlen(formatted_line)) < 0) {
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
	char active_profile[MAX_PROFILE_LEN] = "";
	char selection[512];
	char *sel_start;
	char *sel_end;
	int found = 0;

	ARGBEGIN {
	case 'v':
		printf("dmenu-tuned-"VERSION"\n");
		return 0;
	default:
		usage();
	} ARGEND

	if (argc > 0)
		usage();

	if (dynamic_profiles) {
		if (get_dynamic_profiles(active_profile, sizeof(active_profile)) < 0) {
			fprintf(stderr, "error: failed to query tuned profiles. is tuned-adm running?\n");
			return 1;
		}
	} else {
		get_static_profiles(active_profile, sizeof(active_profile));
	}

	if (num_profiles == 0) {
		fprintf(stderr, "error: no power profiles found.\n");
		return 1;
	}

	if (run_menu(dmenu_cmd, profiles, num_profiles, active_profile, selection, sizeof(selection)) < 0) {
		return 0; /* Cancelled or failed */
	}

	/* Parse selection: skip starting "* " or "  " */
	sel_start = selection;
	if (strncmp(sel_start, "* ", 2) == 0 || strncmp(sel_start, "  ", 2) == 0) {
		sel_start += 2;
	}

	/* Terminate name at first space */
	sel_end = strchr(sel_start, ' ');
	if (sel_end) {
		*sel_end = '\0';
	}

	/* Validate selection */
	for (size_t i = 0; i < num_profiles; i++) {
		if (strcmp(sel_start, profiles[i].name) == 0) {
			found = 1;
			break;
		}
	}

	if (!found) {
		fprintf(stderr, "error: invalid profile selected: %s\n", sel_start);
		return 1;
	}

	/* Execute tuned-adm to set the profile */
	execlp("tuned-adm", "tuned-adm", "profile", sel_start, (char *)NULL);
	perror("execlp");
	return 1;
}
