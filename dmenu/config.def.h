/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int fuzzy  = 1;                      /* -F  option; if 0, dmenu doesn't use fuzzy matching */
static int draw_input = 1;                  /* -noi option; if 0, the input will not be drawn by default */
static int centered = 1;                    /* -c option; centers dmenu on screen */
static int min_width = 500;                 /* minimum width when centered */
static const float menu_height_ratio = 4.0f;  /* This is the ratio used in the original calculation */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"monospace:size=10"
    "FiraCode Nerd Font:size=12",
};

static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][10] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#bbbbbb", "#222222" },
	[SchemeSel] = { "#eeeeee", "#005577" },
	[SchemeSelHighlight] = { "#ffc978", "#005577" },
	[SchemeNormHighlight] = { "#ffc978", "#222222" },
	[SchemeOut] = { "#000000", "#00ffff" },
    [SchemeHighlight] = {"#f1fa8c", "#596377", "#3E485B"},
    [SchemeHover] = {"#ffffff", "#353D4B", "#3E485B"},
    [SchemeGreen] = {"#ffffff", "#52E067", "#41b252"},
    [SchemeRed] = {"#ffffff", "#e05252", "#c24343"},
    [SchemeYellow] = {"#ffffff", "#e0c452", "#bca33f"},
    [SchemeBlue] = {"#ffffff", "#5280e0", "#3a62b3"},
    [SchemePurple] = {"#ffffff", "#9952e0", "#7439b0"},
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

static unsigned int lineheight = 0; /* -h option; minimum height of a menu line     */
static unsigned int min_lineheight = 8;
static int sely = 0;
static int commented = 0;
static int animated = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static unsigned int border_width = 0;
