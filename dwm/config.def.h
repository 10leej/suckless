/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;   /* border pixel of windows */
static const unsigned int gappx     = 3;  /* gap pixel between windows */
static const unsigned int snap      = 32;  /* snap pixel */
static const int showbar            = 1;   /* 0 means no bar */
static const int topbar             = 1;   /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "fontawesome:size=12" };
static const char dmenufont[]       = "monospace:size=12";

//backround color
static const char col_gray1[]       = "#222222";
//inactive window border color
static const char col_gray2[]       = "#444444";
//font color
static const char col_gray3[]       = "#bbbbbb";
//current tag and current window font color
static const char col_gray4[]       = "#eeeeee";
//top bar second (default blue) color and active window border color
static const char col_cyan[]        = "#ae3f3e";
//assign colors
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Pcmanfm",     NULL,       NULL,       0,            1,           -1 },
	{ "Virt-manager",     NULL,       NULL,       0,            1,           -1 },
	{ "discord",     NULL,       NULL,       0,            0,           -2 },
	{ "element",     NULL,       NULL,       0,            0,           -2 },
//	{ "Dungeondraft",     NULL,       NULL,       2,            1,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "(@)",      spiral },  /* first entry is default */
	{ "[]=",      tile },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *web[]  = { "firefox", NULL };
static const char *files[]  = { "pcmanfm", NULL };
static const char *editor[]  = { "codium", NULL };
static const char *webserver_cmd[] = { "/bin/sh", "-c", "alacritty -e ssh joshua@10leej.com", NULL };
static const char *localserver_cmd[] = { "/bin/sh", "-c", "alacritty -e ssh joshua@10leej.com", NULL };
static const char *print_screen_cmd[] = { "/bin/sh", "-c", "maim ~/Pictures/Screenshots/$(date +%s).png", NULL };
static const char *print_region_cmd[] = { "/bin/sh", "-c", "maim -s ~/Pictures/Screenshots/$(date +%s).png", NULL };
static const char *print_window_cmd[] = { "/bin/sh", "-c", "maim -i $(xdotool getactivewindow) ~/Pictures/Screenshots/$(date +%s).png", NULL };
/* test */
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} }, /* toggle the top status bar */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, /* change focus to the left */
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, /* change focus to the right */
	{ MODKEY,                       XK_s,      incnmaster,     {.i = +1 } }, /* single app focus? */
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, /* not sure yet */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, /* not sure yet*/
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, /* not sure yet*/
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} }, /* doesn't seem to work */
	{ MODKEY,                       XK_Tab,    view,           {0} }, /* doesn't seem to work */
	{ MODKEY,                       XK_q,      killclient,     {0} }, /* kill application */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* set tile layout */
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} }, /* set floating layout */
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} }, /* set fibonacci layout */
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[3]} }, /* set monocle layout */
	{ MODKEY,                       XK_space,  setlayout,      {0} }, /* set to default tile layout, this can't change */
	{ MODKEY|ControlMask,           XK_space,  togglefloating, {0} }, /* toggle window floating */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, /* not sure yet */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, /* not sure yet */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, /* not sure yet */
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, /* not sure yet */
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, /* not sure yet */
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, /* not sure yet*/
	TAGKEYS(                        XK_1,                      0) /* switch to tag 1 */
	TAGKEYS(                        XK_2,                      1) /* switch to tag 2 */
	TAGKEYS(                        XK_3,                      2) /* switch to tag 3 */
	TAGKEYS(                        XK_4,                      3) /* switch to tag 4 */
	TAGKEYS(                        XK_5,                      4) /* switch to tag 5 */
	TAGKEYS(                        XK_6,                      5) /* switch to tag 6 */
	TAGKEYS(                        XK_7,                      6) /* switch to tag 7 */
	TAGKEYS(                        XK_8,                      7) /* switch to tag 8 */
	TAGKEYS(                        XK_9,                      8) /* switch to tag 9 */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, /* quit dwm */
	/* App Launchers */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, /* open dmenu */
	{ MODKEY,                       XK_r,      spawn,          {.v = roficmd } }, /* open rofi */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } }, /* open terminal */
	{ MODKEY,                       XK_b,      spawn,          {.v = web } }, /* open web browser 1 */
	{ MODKEY,                       XK_f,      spawn,          {.v = files } }, /* open file manager */
	{ MODKEY,                       XK_e,      spawn,          {.v = editor } }, /* open text editor */

	{ 0,                            XK_Print,   spawn,          {.v = print_screen_cmd } }, /* full screenshot */
	{ ShiftMask,                    XK_Print,   spawn,          {.v = print_region_cmd } }, /* region screenshot */
	{ ControlMask,                  XK_Print,   spawn,          {.v = print_window_cmd } }, /* window screenshot */

	{ MODKEY,           XK_F12,   spawn,          {.v = webserver_cmd } }, /* ssh into web server */
	{ MODKEY,           XK_F11,   spawn,          {.v = localserver_cmd } }, /* ssh into local server */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
