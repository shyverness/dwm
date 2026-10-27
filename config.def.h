/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 2;
static const unsigned int snap        = 32;
static const int          showbar     = 1;
static const int          topbar      = 1;
static const char        *fonts[]     = {"monocraft:size=10"};
static const char         dmenufont[] = "monocraft:size=10";

static const char col_gray1[]         = "#282828"; /* background */
static const char col_gray2[]         = "#504945"; /* border */
static const char col_gray3[]         = "#ebdbb2"; /* foreground */
static const char col_gray4[]         = "#fbf1c7"; /* bright foreground */
static const char col_cyan[]          = "#458588"; /* selected accent */

static const char *colors[][3]        = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel]  = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact          = 0.55; /* factor of master area size [0.05..0.95] */
static const int   nmaster        = 1;    /* number of clients in master area */
static const int   resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int   lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */
static const int   refreshrate    = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[]     = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY            Mod4Mask
#define TAGKEYS(KEY, TAG)                                                         /**/                                 \
	{MODKEY, KEY, view, {.ui = 1 << TAG}},                                    /**/                                 \
	    {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},            /**/                                 \
	    {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                     /**/                                 \
	    {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}}, /**/

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                                                                     \
	{                                                                                                              \
		.v = (const char *[])                                                                                  \
		{                                                                                                      \
			"/usr/bin/zsh", "-c", cmd, NULL                                                                \
		}                                                                                                      \
	}

/* commands */
static char        dmenumon[2]       = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]        = {"dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
                                        "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[]         = {"st", NULL};
static const char *termfirefox[]     = {"firefox", NULL};
static const char *termpavucontrol[] = {"pavucontrol", NULL};
static const char *termbluetooth[]   = {"blueman-manager", NULL};

#include "movestack.c"
static const Key keys[] = {
    /* modifier                     key        function        argument */

    /* Spawn commands
     */
    {MODKEY, XK_r, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_w, spawn, {.v = termfirefox}},

    /* Volume */
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%+ && ~/.config/i3/volume-dunst.sh")},
    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%- && ~/.config/i3/volume-dunst.sh")},
    {MODKEY, XK_m, spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle && ~/.config/i3/volume-dunst.sh")},

    /* Media controls */
    {0, XF86XK_AudioMute, spawn, SHCMD("playerctl play-pause")},
    {0, XF86XK_AudioPlay, spawn, SHCMD("playerctl play-pause")},
    {0, XF86XK_AudioPause, spawn, SHCMD("playerctl play-pause")},
    {0, XF86XK_AudioNext, spawn, SHCMD("playerctl next")},
    {0, XF86XK_AudioPrev, spawn, SHCMD("playerctl previous")},

    /* Brightness */
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl -e s 2%+")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl -e s 2%-")},

    /* Misc */
    {MODKEY, XK_k, spawn, SHCMD("st rmpc")},
    {MODKEY, XK_Page_Up, spawn, {.v = termpavucontrol}},
    {MODKEY, XK_Page_Down, spawn, {.v = termbluetooth}},
    {MODKEY, XK_d, spawn, SHCMD("xdotool type --clearmodifiers \"$(date '+%Y.%m.%d')\"")},

    /* Windowing keybinds
     *
     */
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_n, focusstack, {.i = +1}},
    {MODKEY, XK_e, focusstack, {.i = -1}},
    // {MODKEY, XK_u, incnmaster, {.i = +1}},
    // {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_i, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_n, movestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_e, movestack, {.i = -1}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_c, killclient, {0}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ShiftMask, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_f, toggleFullscreen, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_slash, 0)       /**/
    TAGKEYS(XK_parenleft, 1)   /**/
    TAGKEYS(XK_bracketleft, 2) /**/
    TAGKEYS(XK_braceleft, 3)   /**/
    TAGKEYS(XK_apostrophe, 4)  /**/
    TAGKEYS(XK_dollar, 5)      /**/
    TAGKEYS(XK_exclam, 6)      /**/
    TAGKEYS(XK_braceright, 7)  /**/
    TAGKEYS(XK_bracketright, 8){MODKEY | ShiftMask, XK_q, quit, {0}},

    /* moveresize */

    {MODKEY, XK_Down, moveresize, {.v = "0x 25y 0w 0h"}},
    {MODKEY, XK_Up, moveresize, {.v = "0x -25y 0w 0h"}},
    {MODKEY, XK_Right, moveresize, {.v = "25x 0y 0w 0h"}},
    {MODKEY, XK_Left, moveresize, {.v = "-25x 0y 0w 0h"}},
    {MODKEY | ShiftMask, XK_Down, moveresize, {.v = "0x 0y 0w 25h"}},
    {MODKEY | ShiftMask, XK_Up, moveresize, {.v = "0x 0y 0w -25h"}},
    {MODKEY | ShiftMask, XK_Right, moveresize, {.v = "0x 0y 25w 0h"}},
    {MODKEY | ShiftMask, XK_Left, moveresize, {.v = "0x 0y -25w 0h"}},
    {MODKEY | ControlMask, XK_Up, moveresizeedge, {.v = "t"}},
    {MODKEY | ControlMask, XK_Down, moveresizeedge, {.v = "b"}},
    {MODKEY | ControlMask, XK_Left, moveresizeedge, {.v = "l"}},
    {MODKEY | ControlMask, XK_Right, moveresizeedge, {.v = "r"}},
    {MODKEY | ControlMask | ShiftMask, XK_Up, moveresizeedge, {.v = "T"}},
    {MODKEY | ControlMask | ShiftMask, XK_Down, moveresizeedge, {.v = "B"}},
    {MODKEY | ControlMask | ShiftMask, XK_Left, moveresizeedge, {.v = "L"}},
    {MODKEY | ControlMask | ShiftMask, XK_Right, moveresizeedge, {.v = "R"}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
