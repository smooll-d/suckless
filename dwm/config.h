/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  	 = 3;   /* border pixel of windows */
static const unsigned int gappx     	 = 15;  /* gaps between windows */
static const unsigned int snap      	 = 32;  /* snap pixel */

// Systray
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        	 = 1;   /* 0 means no systray */

// dwmbar
static const int showbar             	 = 1;   /* 0 means no standard bar */
static const int topbar             	 = 1;   /* 0 means standard bar at bottom */

// Custom bar height
static const int user_bh            	 = 6;   /* 2 is the default spacing around the bar's font */

// Colorful tags
static const unsigned int colorfultag    = 1;   /* 0 means use SchemeSel for selected tag */

// Fonts
static const char *fonts[]          	 = { "JetBrains Mono NF:size=14" };
static const char dmenufont[]       	 = "Ubuntu Nerd Font:size=14";

#include "themes/tokyo_night.h"

// Colors
// static const char background[]       	 = "#111111";
// static const char foreground[]        	 = "#eeeeee";
// static const char border[] 				 = "#f38127";
// static const char black[] 			 	 = "#000000";
// static const char white[] 			 	 = "#ffffff";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm]   = { foreground, background, black  },
	[SchemeSel]    = { foreground, background, border },
	[SchemeTag]    = { foreground, background, black  },
    [SchemeTag1]   = { border,     background, black  },
	[SchemeTag2]   = { "#ff4444",  background, black  },
    [SchemeTag3]   = { "#ffff00",  background, black  },
    [SchemeTag4]   = { "#00ff00",  background, black  },
    [SchemeTag5]   = { "#0000ff",  background, black  },
	[SchemeTag6]   = { "#4b0082",  background, black  },
	[SchemeTag7]   = { "#9400d3",  background, black  },
	[SchemeTag8]   = { "#fec260",  background, black  },
	[SchemeTag9]   = { "#f05454",  background, black  },
	[SchemeLayout] = { foreground, background, black  }
};

#define ICONSIZE 24   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
#define ICON_OFFSET 15 /* offset between layout characters and icon */

static const char *const autostart[] = {
	"lxsession", "-s", "/usr/share/xsession/dwm.desktop", NULL,
	"dwmblocks", NULL,
	"nitrogen", "--restore", NULL,
	"wired", NULL,
	"systemctl", "--user", "import-environment", "DISPLAY", NULL,
	"parcellite", NULL,
	"redshift", "-l", "54.00696:15.98751", "-t", "6500:3500", NULL,
	"nm-applet", NULL,
	"blueman-applet", NULL,
	"volctl", NULL,
	"polychromatic-tray-applet", NULL,
	"discord", NULL,
	//"steam", NULL,
	"st", NULL,
	"sc-controller", NULL,
	//"caprine", NULL,
	NULL /* terminate */
};

static const char *autostart_lockfile = "/tmp/dwm-autostart.lock";

/* tagging */
static const char *tags[] = { "", "󰖟", "", "󰝚", "󰃣", "", "", "", "" };

static const int tagschemes[] = { SchemeTag1, SchemeTag2, SchemeTag3,
                                  SchemeTag4, SchemeTag5, SchemeTag6,
                                  SchemeTag7, SchemeTag8, SchemeTag9 };

// Underline
static const unsigned int ulinepad	   = 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke  = 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset = 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 			   = 0;

// Tags
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	  instance   title   tags mask   isfloating   monitor */
	{ "Eog", 		   NULL, 	 NULL,   0, 		 1, 		  -1 },
	{ "steam", 		   NULL, 	 NULL,   1 << 6, 	 0, 		  -1 },
	{ "discord", 	   NULL, 	 NULL, 	 1 << 2, 	 0, 		  -1 },
	{ "SC Controller", NULL,     NULL,   1 << 8, 	 1, 		  -1 }
};

/* layout(s) */
static const float mfact     	= 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     	= 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  	= 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 	= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", foreground, "-nf", background, "-sb", border, "-sf", black, NULL };
//static const char *termcmd[]  	= { "tabbed", "-c", "-d", "-r", "2", "st", "-w", "''", NULL };
static const char *termcmd[] 	= { "st", NULL };
//static const char *clipmenu[]     = { "clipmenu", NULL };
static const char *pcmanfm[] 	= { "pcmanfm", NULL };
/*static const char *rofi[] 	    = { "rofi", "-show", "drun", "-theme", "~/.config/rofi/config.rasi", NULL };*/
static const char *rofi[] 		= { "launcher.sh", NULL };
static const char *powermenu[]  = { "powermenu.sh", NULL };
static const char *picom[] 		= { "picom" };
static const char *kill_picom[] = { "killall", "picom" };
static const char *bsethalf[] 	= { "brightnessctl", "s", "50%" };
static const char *bsetone[]	= { "brightnessctl", "s", "0" };
static const char *screenshot[] = { "gnome-screenshot" };

// Keys
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = rofi } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask, 			XK_b, 	   spawn, 	   	   {.v = bsetone } },
	{ MODKEY|ShiftMask|ControlMask, XK_b, 	   spawn, 		   {.v = bsethalf } },
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
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY, 						XK_Right,  viewnext,       {0} },
	{ MODKEY, 						XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask, 			XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask, 			XK_Left,   tagtoprev,      {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask, 			XK_e, 	   spawn, 		   {.v = pcmanfm } },
	{ MODKEY, 						XK_q, 	   spawn, 		   {.v = powermenu } },
	{ MODKEY, 						XK_n, 	   spawn, 		   SHCMD("kill -s USR1 $(pidof deadd-notification-center)") },
	{ MODKEY, 						XK_p, 	   spawn, 		   {.v = picom } },
	{ MODKEY|ShiftMask, 			XK_p, 	   spawn, 		   {.v = kill_picom } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
	{ MODKEY, 						XK_s, 	   togglesticky,   {0} },
	{ MODKEY|ShiftMask, 			XK_s, 	   spawn, 		   {.v = screenshot } }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
