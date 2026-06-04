/* dmenu-screenshot configuration */

/* Tokyo Night Theme Colors from existing DWM setup */
static const char col_tokyo_bg[]     = "#1a1b26"; /* Dark background */
static const char col_tokyo_fg[]     = "#a9b1d6"; /* Light foreground */
static const char col_tokyo_accent[] = "#7aa2f7"; /* Accent color (blue) */

/* dmenu commands and arguments */
static const char *dmenu_cmd[] = {
	"dmenu",
	"-i",                /* case insensitive */
	"-p", "Screenshot:", /* prompt */
	"-fn", "Iosevka Nerd Font Mono:style=Bold:size=10",
	"-nb", col_tokyo_bg,
	"-nf", col_tokyo_fg,
	"-sb", col_tokyo_accent,
	"-sf", col_tokyo_bg,
	NULL
};

typedef enum {
	SCREENSHOT_FULLSCREEN,
	SCREENSHOT_WINDOW,
	SCREENSHOT_MONITOR,
	SCREENSHOT_SELECTION
} ScreenshotType;

typedef struct {
	const char *label;
	ScreenshotType type;
} ScreenshotItem;

static const ScreenshotItem items[] = {
	/* label             type */
	{ "Fullscreen",      SCREENSHOT_FULLSCREEN },
	{ "Active Window",   SCREENSHOT_WINDOW },
	{ "Active Monitor",  SCREENSHOT_MONITOR },
	{ "Selection",       SCREENSHOT_SELECTION },
};
