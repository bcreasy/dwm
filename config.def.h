/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "ProFont";
static const char font_pro[]        = "ProFont";
static const char font_vga[]        = "vga";
static const char font_nexus[]      = "nexus";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* terminal specific settings */
static const char termbase[]             = "rxvt -ls -sl 1000";
static const char termbg_light[]         = "white";
static const char termbg_dark[]          = "black";
static const char termscheme_light[]     = "-bg black -fg white";
static const char termscheme_dark[]      = "-bg black -fg white";
static const char termfont_nexus[]       = "-fn nexus";
static const char termfont_vga[]         = "-fn vga";
static const char termfont_pro[]         = "-fn ProFont";

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "Gimp",           NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",        NULL,       NULL,       1 << 8,       False,       -1 },
	{ "Google-chrome",  NULL,       NULL,       1 << 1,       True,        -1 },
	{ "Pidgin",         NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

/* dmenu */
static const char *dmenucmd[]             = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
/* default terminal */
static const char *termcmd[]              = { "rxvt", "-ls", "-sl", "1000", "-bg", termbg_dark, "-fg", termbg_light, "-fn", font, NULL };
/* various terminal setups */
static const char *termcmd_nexusdark[]    = { "rxvt", "-ls", "-sl", "1000", "-bg", termbg_dark,  "-fg", termbg_light, "-fn", font_nexus, NULL };
static const char *termcmd_nexuslight[]   = { "rxvt", "-ls", "-sl", "1000", "-bg", termbg_light, "-fg", termbg_dark,  "-fn", font_nexus, NULL };
static const char *termcmd_vgadark[]      = { "rxvt", "-ls", "-sl", "1000", "-bg", termbg_dark,  "-fg", termbg_light, "-fn", font_vga,   NULL };
static const char *termcmd_vgalight[]     = { "rxvt", "-ls", "-sl", "1000", "-bg", termbg_light, "-fg", termbg_dark,  "-fn", font_vga,   NULL };
static const char *termcmd_prodark[]      = { "rxvt", "-ls", "-sl", "1000", "-bg", termbg_dark,  "-fg", termbg_light, "-fn", font_pro,   NULL };
static const char *termcmd_prolight[]     = { "rxvt", "-ls", "-sl", "1000", "-bg", termbg_light, "-fg", termbg_dark,  "-fn", font_pro,   NULL };
/* volume adjustments */
static const char *volumedown[]           = { "amixer", "-q", "set", "Master", "2%-", "unmute", NULL };
static const char *volumeup[]             = { "amixer", "-q", "set", "Master", "2%+", "unmute", NULL };
/* audacious commands */
static const char *audio_playpause[]      = { "audtool", "--playback-playpause", NULL };
static const char *audio_next[]           = { "audtool", "--playlist-advance", NULL };
static const char *audio_prev[]           = { "audtool", "--playlist-reverse", NULL };
/* lock screen */
static const char *screensaver[]          = { "xscreensaver-command", "--lock", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_F1,                     0)
	TAGKEYS(                        XK_F2,                     1)
	TAGKEYS(                        XK_F3,                     2)
	TAGKEYS(                        XK_F4,                     3)
	TAGKEYS(                        XK_F5,                     4)
	TAGKEYS(                        XK_F6,                     5)
	TAGKEYS(                        XK_F7,                     6)
	TAGKEYS(                        XK_F8,                     7)
	TAGKEYS(                        XK_F9,                     8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                            XK_F2,     spawn,          {.v = termcmd_nexusdark}},
	{ ShiftMask,                    XK_F2,     spawn,          {.v = termcmd_nexuslight}},
	{ 0,                            XK_F3,     spawn,          {.v = termcmd_vgadark}},
	{ ShiftMask,                    XK_F3,     spawn,          {.v = termcmd_vgalight}},
	{ 0,                            XK_F4,     spawn,          {.v = termcmd_prolight}},
	{ ShiftMask,                    XK_F4,     spawn,          {.v = termcmd_prodark}},
	{ 0,                            XK_F7,     spawn,          {.v = volumedown}},
	{ 0,                            XK_F8,     spawn,          {.v = volumeup}},
	{ 0,                            XK_F9,     spawn,          {.v = audio_playpause}},
	{ 0,                            XK_F10,    spawn,          {.v = audio_prev}},
	{ 0,                            XK_F11,    spawn,          {.v = audio_next}},
	{ 0,                            XK_F12,    spawn,          {.v = screensaver}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

