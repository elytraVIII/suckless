/* dmenu-powermenu configuration */

/* Tokyo Night Theme Colors from existing DWM setup */
static const char col_tokyo_bg[]     = "#1a1b26"; /* Dark background */
static const char col_tokyo_fg[]     = "#a9b1d6"; /* Light foreground */
static const char col_tokyo_accent[] = "#7aa2f7"; /* Accent color (blue) */
static const char col_tokyo_red[]    = "#f7768e"; /* Red accent for confirmation */

/* dmenu commands and arguments */
static const char *dmenu_cmd[] = {
	"dmenu",
	"-i",                /* case insensitive */
	"-p", "Power Menu:", /* prompt */
	"-fn", "Iosevka Nerd Font Mono:style=Bold:size=10",
	"-nb", col_tokyo_bg,
	"-nf", col_tokyo_fg,
	"-sb", col_tokyo_accent,
	"-sf", col_tokyo_bg,
	NULL
};

static const char *confirm_cmd[] = {
	"dmenu",
	"-i",
	"-p", "Are you sure?",
	"-fn", "Iosevka Nerd Font Mono:style=Bold:size=10",
	"-nb", col_tokyo_bg,
	"-nf", col_tokyo_fg,
	"-sb", col_tokyo_red, /* Red background for confirmation highlight */
	"-sf", col_tokyo_bg,
	NULL
};

/* Confirmation options (first option is default/selected on Enter) */
static const char *confirm_options[] = {
	"No",
	"Yes"
};

typedef struct {
	const char *label;
	const char *command;
	int confirm;
} PowermenuItem;

static const PowermenuItem items[] = {
	/* label       command              confirm */
	{ "Lock",      "slock",             0 },
	{ "Suspend",   "systemctl suspend", 0 },
	{ "Logout",    "killall dwm",       1 },
	{ "Reboot",    "systemctl reboot",  1 },
	{ "Shutdown",  "systemctl poweroff",1 },
};
