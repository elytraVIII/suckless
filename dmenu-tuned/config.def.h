/* dmenu-tuned configuration */

/* Tokyo Night Theme Colors from DWM setup */
static const char col_tokyo_bg[]     = "#1a1b26"; /* Dark background */
static const char col_tokyo_fg[]     = "#a9b1d6"; /* Light foreground */
static const char col_tokyo_accent[] = "#7aa2f7"; /* Accent color (blue) */

/* dmenu command and arguments */
static const char *dmenu_cmd[] = {
	"dmenu",
	"-i",                   /* Case insensitive */
	"-p", "Power Profile:", /* Prompt */
	"-fn", "Iosevka Nerd Font Mono:style=Bold:size=10",
	"-nb", col_tokyo_bg,
	"-nf", col_tokyo_fg,
	"-sb", col_tokyo_accent,
	"-sf", col_tokyo_bg,
	NULL
};

/*
 * Whether to dynamically query available profiles from tuned-adm.
 * 1: Dynamic mode (queries tuned-adm at runtime)
 * 0: Static mode (uses static_profiles array defined below)
 */
static const int dynamic_profiles = 1;

/* Static profiles list (used only if dynamic_profiles is 0).
 * Format: { profile_name, description }
 */
typedef struct {
	const char *name;
	const char *desc;
} StaticProfile;

static const StaticProfile static_profiles[] = {
	/* profile_name             description */
	{ "balanced",               "General non-specialized tuned profile" },
	{ "powersave",              "Optimize for low power consumption" },
	{ "throughput-performance", "Broadly applicable tuning for performance" },
	{ "balanced-battery",       "Balanced profile biased towards battery savings" },
};
