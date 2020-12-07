/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 5;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static int showsystray              = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 25;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static const unsigned int baralpha = 0x66;      /*0xff is opaque*/
static const unsigned int borderalpha = OPAQUE;
static const char *fonts[]          = { "SFMono:size=11:style=Bold", "SFMono Nerd Font:size=13", "Apple Color Emoji:size=11" };
static const char dmenufont[]       = "SFMono Nerd Font:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#9F0BD9";
/* static const char col_cyan[]        = "#4A05AB"; */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
    "dwmblocks", NULL,
	"/home/diego/.config/dwm/autostart.sh", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",         NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Telegram",     NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",      NULL,     NULL,           0,         0,          0,          -1,        -1 },
	{ "Alacritty",    NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,           NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	/* { "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 }, */
	/* { "St",      NULL,     NULL,           0,         0,          1,           0,        -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenuopacity[4] = "0.65"; /* Values from 0 (transparent) to 1 (opaque) */
static char dmenudim[4] = "0"; /* Values from 0 (transparent) to 1 (opaque) */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static char dmenuheight[3] = "25";
static const char *dmenucmd[] = { "dmenu_run", "-s", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-o", dmenuopacity, "-dim", dmenudim, "-h", dmenuheight, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_slash,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("emacs") },
	{ MODKEY,                       XK_F1,     spawn,          SHCMD("redshift -O 3500") },
	{ MODKEY,                       XK_F2,     spawn,          SHCMD("redshift -x") },
	{ MODKEY|Mod1Mask,              XK_n,      spawn,          SHCMD("nitrogen") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("pcmanfm") },
	{ MODKEY,                       XK_t,      spawn,          SHCMD("telegram-desktop") },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("/home/diego/.config/dwm/Screenshots/screenshot.fish --area-clipboard") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("/home/diego/.config/dwm/Screenshots/screenshot.fish --screen-clipboard") },
	{ Mod1Mask,                     XK_s,      spawn,          SHCMD("/home/diego/.config/dwm/Screenshots/screenshot.fish --area-file") },
	{ Mod1Mask|ShiftMask,           XK_s,      spawn,          SHCMD("/home/diego/.config/dwm/Screenshots/screenshot.fish --screen-file") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglesystray,  {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	/* { MODKEY,                       XK_Return, zoom,           {0} }, */
 	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
 	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
 	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
 	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
 	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
 	{ MODKEY|ControlMask,           XK_period, togglealwaysontop, {0} },
	{ MODKEY,                       XK_period, togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,        {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },  /* Restart dwm*/
	{ 0,                       0x1008ff13,      spawn,          SHCMD("amixer sset 'Master' 5%+ && kill -44 $(pidof dwmblocks)") },    /* Keycode for XF86AudioRaiseVolume */
	{ ShiftMask,               0x1008ff13,      spawn,          SHCMD("amixer sset 'Master' 100% && kill -44 $(pidof dwmblocks)") },   /* Keycode for XF86AudioRaiseVolume */
	{ 0,                       0x1008ff11,      spawn,          SHCMD("amixer sset 'Master' 5%- && kill -44 $(pidof dwmblocks)") },    /* Keycode for XF86AudioLowerVolume */
	{ ShiftMask,               0x1008ff11,      spawn,          SHCMD("amixer sset 'Master' 50% && kill -44 $(pidof dwmblocks)") },    /* Keycode for XF86AudioRaiseVolume */
	{ 0,                       0x1008ff12,      spawn,          SHCMD("amixer sset 'Master' toggle && kill -44 $(pidof dwmblocks)") }, /* Keycode for XF86AudioMute */
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

