/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"Iosevka:size=10"
};
static const char dmenufont[]       = "monospace:size=10";
static const char normbordercolor[] = "#3f3f3f";
static const char normbgcolor[]     = "#3f3f3f";
static const char normfgcolor[]     = "#dcdccc";
static const char selbordercolor[]  = "#8fb28f";
static const char selbgcolor[]      = "#a0afa0";
static const char selfgcolor[]      = "#040404";
static unsigned int baralpha        = 0xf0;
static unsigned int borderalpha     = 0xf5;
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define KMODKEY Mod4Mask
#define MMODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ KMODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KMODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KMODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KMODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "terminal", NULL }; // I decided to just symlink my preferred terminal to "terminal"
static const char *lockcmd[]  = { "locker", NULL }; // Same with screen locker

#include "mpdcontrol.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ KMODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ KMODKEY,             		 XK_t,	    spawn,          {.v = termcmd } },
	{ KMODKEY|ShiftMask,		 XK_l,	    spawn,	    {.v = lockcmd } },
	{ KMODKEY,                       XK_b,      togglebar,      {0} },
	{ KMODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ KMODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ KMODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ KMODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ KMODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ KMODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ KMODKEY,                       XK_Return, zoom,           {0} },
	{ KMODKEY,                       XK_Tab,    view,           {0} },
	{ KMODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ KMODKEY,                       XK_g,      setlayout,      {.v = &layouts[0]} },
	{ KMODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ KMODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ KMODKEY,                       XK_space,  setlayout,      {0} },
	{ KMODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ KMODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ KMODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ KMODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ KMODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ KMODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ KMODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ KMODKEY,			 XK_bracketleft,   mpdchange,	    {.i = -1 } },
	{ KMODKEY,			 XK_bracketright, mpdchange,	    {.i = +1 } },
	{ KMODKEY,			XK_p,	    mpdcontrol,	    {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ KMODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MMODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MMODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MMODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MMODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MMODKEY,         Button3,        toggletag,      {0} },
};

