/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka Nerd Font Mono:style=Bold:size=10" };
static const char dmenufont[]       = "Iosevka Nerd Font Mono:style=Bold:size=10";

/* Tokyo Night Theme Colors */
static const char col_tokyo_bg[]     = "#1a1b26"; /* Dark background */
static const char col_tokyo_fg[]     = "#a9b1d6"; /* Light foreground */
static const char col_tokyo_border[] = "#24283b"; /* Normal border color */
static const char col_tokyo_accent[] = "#7aa2f7"; /* Selected tag / active bar background (blue) */
static const char col_tokyo_sel_bd[] = "#7aa2f7"; /* Selected window border color (blue) */

static const char *colors[][3]      = {
	/*               fg              bg              border   */
	[SchemeNorm] = { col_tokyo_fg,   col_tokyo_bg,   col_tokyo_border },
	[SchemeSel]  = { col_tokyo_bg,   col_tokyo_accent, col_tokyo_sel_bd },
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|| Mode: []= ||",      tile },    /* first entry is default */
	{ "|| Mode: ><> ||",      NULL },    /* no layout function means floating behavior */
	{ "|| Mode: [M] ||",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                                                               \
       &((Keychord){1, {{MODKEY, KEY}},                                        view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                            toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                              tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},                  toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_tokyo_bg, "-nf", col_tokyo_fg, "-sb", col_tokyo_accent, "-sf", col_tokyo_bg, NULL };
static const char *termcmd[]    = { "alacritty", NULL };
static const char *browsercmd[] = { "zen-browser", NULL };
static const char *vacuumcmd[]  = { "startvacuumtube", NULL };
static const char *yazicmd[]    = { "alacritty", "-e", "env", "yazi", NULL };
static const char *bluecmd[]    = { "alacritty", "-e", "bluetui", NULL };
static const char *nvimcmd[]    = { "alacritty", "-e", "nvim", NULL };
static const char *powermenucmd[] = { "dmenu-powermenu", NULL };
static const char *tunedcmd[]     = { "dmenu-tuned", NULL };

static Keychord *keychords[] = {
	/* Keys        function        argument */

	/* Applications / Launchers */
	&((Keychord){1, {{MODKEY, XK_r}},      spawn,          {.v = dmenucmd } }),
	&((Keychord){1, {{MODKEY, XK_Return}}, spawn,          {.v = termcmd } }),
	&((Keychord){1, {{MODKEY, XK_b}},      spawn,          {.v = browsercmd } }),
	&((Keychord){1, {{MODKEY, XK_v}},      spawn,          {.v = vacuumcmd } }),
	&((Keychord){1, {{MODKEY, XK_y}},      spawn,          {.v = yazicmd } }),
	&((Keychord){1, {{MODKEY|ControlMask, XK_b}},      spawn,          {.v = bluecmd } }),
	&((Keychord){1, {{MODKEY, XK_n}},      spawn,          {.v = nvimcmd } }),

	/* Example Keychord: MODKEY+Shift+x, then e -> launches browser */
	&((Keychord){2, {{MODKEY|ShiftMask, XK_x}, {0, XK_e}}, spawn,          {.v = browsercmd } }),

	/* Windows Focus & Stack Navigation */
	&((Keychord){1, {{MODKEY, XK_j}},      focusstack,     {.i = +1 } }),
	&((Keychord){1, {{MODKEY, XK_k}},      focusstack,     {.i = -1 } }),
	&((Keychord){1, {{MODKEY, XK_Return}}, zoom,           {0} }),
	&((Keychord){1, {{MODKEY, XK_Tab}},    view,           {0} }),
	&((Keychord){1, {{MODKEY, XK_q}},      killclient,     {0} }),

	/* Layout Adjustments */
	&((Keychord){1, {{MODKEY, XK_i}},      incnmaster,     {.i = +1 } }),
	&((Keychord){1, {{MODKEY, XK_d}},      incnmaster,     {.i = -1 } }),
	&((Keychord){1, {{MODKEY, XK_h}},      setmfact,       {.f = -0.05} }),
	&((Keychord){1, {{MODKEY, XK_l}},      setmfact,       {.f = +0.05} }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_space}},  togglefloating, {0} }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_b}},      togglebar,      {0} }),

	/* Layout Modes */
	&((Keychord){1, {{MODKEY, XK_t}},      setlayout,      {.v = &layouts[0]} }),
	&((Keychord){1, {{MODKEY, XK_f}},      setlayout,      {.v = &layouts[1]} }),
	&((Keychord){1, {{MODKEY, XK_m}},      setlayout,      {.v = &layouts[2]} }),
	&((Keychord){1, {{MODKEY, XK_space}},  setlayout,      {0} }),

	/* Monitor Navigation / Routing */
	&((Keychord){1, {{MODKEY, XK_comma}},  focusmon,       {.i = -1 } }),
	&((Keychord){1, {{MODKEY, XK_period}}, focusmon,       {.i = +1 } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_comma}},  tagmon,         {.i = -1 } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_period}}, tagmon,         {.i = +1 } }),

	/* Volume / Media Control */
	&((Keychord){1, {{MODKEY, XK_F12}},    spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+") }),
	&((Keychord){1, {{MODKEY, XK_F11}},    spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-") }),
	&((Keychord){1, {{MODKEY, XK_F10}},    spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") }),
	/* Screenshots */
	&((Keychord){1, {{0, XK_Print}},       spawn,          SHCMD("dmenu-screenshot") }),

	/* Tags & Workspaces */
	&((Keychord){1, {{MODKEY, XK_0}},      view,           {.ui = ~0 } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_0}},     tag,            {.ui = ~0 } }),
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* Session / DWM control */
	&((Keychord){1, {{MODKEY|ShiftMask, XK_Escape}}, spawn,          {.v = powermenucmd } }),
	&((Keychord){1, {{MODKEY, XK_p}},      spawn,          {.v = tunedcmd } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_c}},      quit,           {0} }),
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
