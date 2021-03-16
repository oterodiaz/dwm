/* See LICENSE file for copyright and license details. */

/* Borders and gaps */
static const Gap          default_gap     = \
{.isgap = 1, .realgap = 10, .gappx = 10};           // Gaps size in pixels (.realgap and .gappx should be equal)
static const unsigned int borderpx        = 2;      // Window border width in pixels
static const unsigned int snap            = 5;      // Snap floating windows to the edge of the screen when 'snap' pixels away
static const unsigned int borderalpha     = OPAQUE; // Fix window borders being transparent, don't touch this

/* Statusbar and systray */
static const int          topbar                  = 1;    // 0: Bottom bar, 1: Top bar
static const int          showbar                 = 1;    // 0: Hide bar, 1: Show bar
static int                showsystray             = 1;    // 0: Hide systray, 1: Show systray
static const int          user_bh                 = 25;   // Bar height in pixels (0: Calculate bar height, >=1: user_bh as bar height)
static const int          horizpadbar             = 2;    // Horizontal padding for statusbar in pixels
static const int          vertpadbar              = 0;    // Vertical padding for statusbar in pixels
static const unsigned int systrayspacing          = 2;    // Systray spacing in pixels
static const unsigned int baralpha                = 0x44; // Bar opacity in Hex (0xff is opaque)
static const unsigned int systraypinning          = 0;    // 0: Sloppy systray follows selected monitor, >0: Pin systray to monitor X
static const int          systraypinningfailfirst = 1;    // 0: display systray on the last monitor, 1: If pinning fails, display systray on the first monitor

/* Swallow */
static const int swallowfloating = 0;   // 0: Do nothing, 1: Swallow floating windows by default

/* Fonts */
static const char *fonts[]    = { "SFMono Nerd Font:size=11:style=Regular", "Apple Color Emoji:size=11" };
static const char dmenufont[] = "SFMono Nerd Font:size=11:style=Regular";

/* Colors */
static const char col_gray1[]  = "#222222";
static const char col_gray2[]  = "#444444";
static const char col_gray3[]  = "#bbbbbb";
static const char col_gray4[]  = "#eeeeee";
static const char col_cyan[]   = "#9F0BD9"; // Accent
static const char *colors[][3] = {
	/* Format: Foreground, Background, Border */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 }, // Regular windows
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, // Focused windows
};
static const unsigned int alphas[][3]      = {
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* Autostart */
static const char *const autostart[] = {
    "/home/diego/.config/dwm/autostart.sh", NULL,
    "dwmblocks", NULL,
    NULL /* Terminate */
};

/* Tags */
static const char *tags[] = { "", "", "", "" };

/* Rules */
static const Rule rules[] = {
    /* xprop(1):
      	WM_CLASS(STRING) = instance, class
      	WM_NAME(STRING) = title
     */

    /* Class          Instance  Title               Tags mask  isfloating  isterminal  noswallow  monitor      fullscreen*/
    { "Telegram",     NULL,     NULL,               ~0,        1,          0,           0,        -1,           0 },
    { "firefox",      NULL,     NULL,               1 << 3,    0,          0,          -1,        -1,           0 },
    { "Brave-browser",NULL,     NULL,               1 << 3,    0,          0,          -1,        -1,           0 },
    { "FreeTube",     NULL,     NULL,               1 << 3,    0,          0,          -1,        -1,           0 },
    { "pcmanfm",      NULL,     NULL,               0,         0,          0,           1,        -1,           0 },
    { "Pcmanfm",      NULL,     NULL,               0,         0,          0,           1,        -1,           0 },
    { "Alacritty",    NULL,     NULL,               0,         0,          1,           0,        -1,           0 },
    { NULL,           NULL,     "Arcolinux Logout", 0,         0,          0,           1,        -1,           1 },
    { NULL,           NULL,     "Event Tester",     0,         0,          0,           1,        -1,           0 }, // xev
    /* { "Firefox",   NULL,     NULL,               1 << 8,    0,          0,          -1,        -1            0 }, */
    /* { "St",        NULL,     NULL,               0,         0,          1,           0,        -1            0 }, */
};

/* Layouts */
static const float mfact     = 0.55; // Factor of master area size [0.05..0.95] (Vertical split position)
static const int nmaster     = 1;    // Number of windows in the master stack
static const int resizehints = 1;    // 1 means respect size hints in tiled resizals
static const Layout layouts[] = {
    /* Symbol     Arrange function */
    { "[]=",      tile },    // First entry is default
    { "><>",      NULL },    // No layout function means floating behavior
    { "[M]",      monocle },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
};

/* Key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
    { MODKEY,                       CHAIN, KEY, view,       {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           CHAIN, KEY, toggleview, {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             CHAIN, KEY, tag,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, CHAIN, KEY, toggletag,  {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD, -1, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
    { MOD, -1, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
    { MOD, -1, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
    { MOD, -1, XK_z,     ACTION##stack, {.i = 0 } }, \
    { MOD, -1, XK_x,     ACTION##stack, {.i = -1 } },
    /* { MOD, -1, XK_z,     ACTION##stack, {.i = 1 } }, \ */
    /* { MOD, -1, XK_x,     ACTION##stack, {.i = 2 } }, \ */

/* Helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static char        dmenumon[2]     = "0";        // component of dmenucmd, manipulated in spawn()
static char        dmenuheight[3]  = "25";       // dmenu height
static char        dmenuopacity[4] = "0.65";     // Values from 0 (transparent) to 1 (opaque)
static char        dmenudim[4]     = "0";        // Values from 0 (transparent) to 1 (opaque)
static const char *termcmd[]       = { "alacritty", NULL };
static const char *dmenucmd[]      = \
{ "dmenu_run", "-s", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-o", dmenuopacity, "-dim", dmenudim, "-h", dmenuheight, NULL };

/* Keybindings */
static Key keys[] = {
	/* Format: Modifier, Key chain, Key, Function, Argument */

    /* Misc. */
    { MODKEY,            -1, XK_Return, spawn, {.v = termcmd } },                           // Terminal
    { MODKEY|ShiftMask,  -1, XK_Return, spawn, SHCMD("pcmanfm") },                          // File manager
    { MODKEY,            -1, XK_w,      spawn, SHCMD("brave") },                            // Web browser
    { MODKEY,            -1, XK_e,      spawn, SHCMD("emacsclient -c -a 'emacs'") },        // Emacs
    { MODKEY,            -1, XK_t,      spawn, SHCMD("telegram-desktop") },                 // Telegram
    { MODKEY,            -1, XK_y,      spawn, SHCMD("pamixer -t; pamixer -t; freetube") }, // FreeTube
    { MODKEY,            -1, XK_o,      spawn, SHCMD("notion-app") },                       // Nitrogen
    { MODKEY|Mod1Mask,   -1, XK_h,      spawn, SHCMD("sxiv /home/diego/horario") },         // Timetable
    { MODKEY,            -1, XK_n,      spawn, SHCMD("nitrogen") },                         // Nitrogen
    { MODKEY,            -1, XK_m,      spawn, SHCMD("mailspring") },                       // Mailspring

    /* dmenu */
    { MODKEY,            -1, XK_slash, spawn, {.v = dmenucmd } },                              // dmenu
    { MODKEY|ShiftMask,  -1, XK_slash, spawn, SHCMD("/home/diego/.scripts/dmsearch.fish") },   // dmsearch.fish
    { MODKEY,            -1, XK_space, spawn, SHCMD("/home/diego/.scripts/dmdotfiles.fish") }, // dmdotfiles.fish
    { MODKEY,            -1, XK_p,     spawn, SHCMD("/home/diego/.scripts/passmenu") },        // passmenu (clipboard)
    { MODKEY|ShiftMask,  -1, XK_p,     spawn, SHCMD("/home/diego/.scripts/passmenu --type") }, // passmenu (xdotool)

    /* Screenshots */
    { MODKEY,             -1, XK_s, spawn, SHCMD("/home/diego/.scripts/screenshot.fish --area-clipboard") },   // Screenshot copy area
    { MODKEY|ShiftMask,   -1, XK_s, spawn, SHCMD("/home/diego/.scripts/screenshot.fish --screen-clipboard") }, // Screenshot copy screen
    { Mod1Mask,           -1, XK_s, spawn, SHCMD("/home/diego/.scripts/screenshot.fish --area-file") },        // Screenshot save area
    { Mod1Mask|ShiftMask, -1, XK_s, spawn, SHCMD("/home/diego/.scripts/screenshot.fish --screen-file") },      // Screenshot save screen

    /* dwm */
    { MODKEY,            -1, XK_f,         togglefullscr,     {0} },               // Toggle fullscreen on the focused window
    { MODKEY,            -1, XK_b,         togglebar,         {0} },               // Toggle the bar
    { MODKEY|ShiftMask,  -1, XK_b,         togglesystray,     {0} },               // Toggle the systray
    { MODKEY,            -1, XK_i,         incnmaster,        {.i = +1 } },        // Increase number of master windows
    { MODKEY,            -1, XK_d,         incnmaster,        {.i = -1 } },        // Decrease number of master windows
    { MODKEY,            -1, XK_h,         setmfact,          {.f = -0.05} },      // Move vertical split to the left
    { MODKEY,            -1, XK_l,         setmfact,          {.f = +0.05} },      // Move vertical split to the right
    { MODKEY|ShiftMask,  -1, XK_h,         setcfact,          {.f = +0.25} },      // Decrease window weight
    { MODKEY|ShiftMask,  -1, XK_l,         setcfact,          {.f = -0.25} },      // Increase window weight
    { MODKEY|ShiftMask,  -1, XK_o,         setcfact,          {.f =  0.00} },      // Reset window weight
    { MODKEY,            -1, XK_Tab,       view,              {0} },               // View recent tag
    { MODKEY,            -1, XK_Left,      viewtoleft,        {0} },               // View left tag
    { MODKEY,            -1, XK_Right,     viewtoright,       {0} },               // View right tag
    { MODKEY|ShiftMask,  -1, XK_Left,      tagtoleft,         {0} },               // Move window to left tag
    { MODKEY|ShiftMask,  -1, XK_Right,     tagtoright,        {0} },               // Move window to right tag
    { MODKEY,            -1, XK_q,         killclient,        {0} },               // Close focused window
    { MODKEY|ControlMask,-1, XK_space,     focusmaster,       {0} },               // Focus master
    { MODKEY,            -1, XK_period,    togglefloating,    {0} },               // Toggle float
    { MODKEY|ControlMask,-1, XK_period,    togglealwaysontop, {0} },               // Toggle always on top
    { MODKEY,            -1, XK_0,         view,              {.ui = ~0 } },       // View all tags
    { MODKEY|ShiftMask,  -1, XK_0,         tag,               {.ui = ~0 } },       // Move to all tags
    { MODKEY,            -1, XK_minus,     setgaps,           {.i = -5 } },        // Decrease gaps
    { MODKEY,            -1, XK_equal,     setgaps,           {.i = +5 } },        // Increase gaps
    { MODKEY|ShiftMask,  -1, XK_minus,     setgaps,           {.i = GAP_RESET } }, // Reset gaps
    { MODKEY|ShiftMask,  -1, XK_equal,     setgaps,           {.i = GAP_TOGGLE} }, // Toggle gaps
    { MODKEY|ShiftMask,  -1, XK_BackSpace, quit,              {0} },               // Quit dwm
    { MODKEY|ShiftMask,  -1, XK_r,         quit,              {1} },               // Restart dwm

    /* Stacker */
    STACKKEYS(MODKEY, focus)
    STACKKEYS(MODKEY|ShiftMask, push)

    /* Tags */
    TAGKEYS( -1, XK_1, 0) // First tag
    TAGKEYS( -1, XK_2, 1) // Second tag
    TAGKEYS( -1, XK_3, 2) // Third tag
    TAGKEYS( -1, XK_4, 3) // Fourth tag

    /* Lock/Log Out */
    { MODKEY|ShiftMask,   -1, XK_q, spawn, SHCMD("arcologout") }, // Arcologout
    { MODKEY|ControlMask, -1, XK_q, spawn, SHCMD("slock -m \"Locked at $(date '+%a %d, %H:%M:%S')\"") }, // Lock screen

    /* Layouts */
    { MODKEY|ControlMask, XK_l, XK_t, setlayout, {.v = &layouts[0]} }, // Tile
    { MODKEY|ControlMask, XK_l, XK_f, setlayout, {.v = &layouts[1]} }, // Floating
    { MODKEY|ControlMask, XK_l, XK_m, setlayout, {.v = &layouts[2]} }, // Monocle
    { MODKEY|ControlMask, XK_l, XK_c, setlayout, {.v = &layouts[3]} }, // CenteredMaster
    { MODKEY|ControlMask, XK_l, XK_v, setlayout, {.v = &layouts[4]} }, // CenteredFloatingMaster
    { MODKEY|ControlMask, XK_l, XK_s, setlayout, {.v = &layouts[5]} }, // Spiral
    { MODKEY|ControlMask, XK_l, XK_d, setlayout, {.v = &layouts[6]} }, // Dwindle

    /* Volume */
    { 0,         -1, 0x1008ff13, spawn, SHCMD("pamixer -i 5 && kill -44 $(pidof dwmblocks)") },             // +5%
    { 0,         -1, 0x1008ff11, spawn, SHCMD("pamixer -d 5 && kill -44 $(pidof dwmblocks)") },             // -5%
    { ShiftMask, -1, 0x1008ff13, spawn, SHCMD("pamixer --set-volume 100 && kill -44 $(pidof dwmblocks)") }, // 100%
    { ShiftMask, -1, 0x1008ff11, spawn, SHCMD("pamixer --set-volume 50 && kill -44 $(pidof dwmblocks)") },  // 50%
    { 0,         -1, 0x1008ff12, spawn, SHCMD("pamixer -t && kill -44 $(pidof dwmblocks)") },               // Mute

    /* Brightness */
    { 0,         -1, 0x1008ff03, spawn, SHCMD("/home/diego/.scripts/brightness.py -r -10 && kill -45 $(pidof dwmblocks)") }, // -10%
    { 0,         -1, 0x1008ff02, spawn, SHCMD("/home/diego/.scripts/brightness.py -r 10 && kill -45 $(pidof dwmblocks)") },  // +10%
    { ShiftMask, -1, 0x1008ff03, spawn, SHCMD("/home/diego/.scripts/brightness.py -s 0 && kill -45 $(pidof dwmblocks)") },   // 0%
    { ShiftMask, -1, 0x1008ff02, spawn, SHCMD("/home/diego/.scripts/brightness.py -s 100 && kill -45 $(pidof dwmblocks)") }, // 100%
    { MODKEY,    -1, 0x1008ff02, spawn, SHCMD("/home/diego/.scripts/brightness.py -s 50 && kill -45 $(pidof dwmblocks)") },  // 50%
    { MODKEY,    -1, 0x1008ff03, spawn, SHCMD("/home/diego/.scripts/brightness.py -s 50 && kill -45 $(pidof dwmblocks)") },  // 50%

    /* Blue Light Filter */
    { MODKEY, -1, XK_F2, spawn, SHCMD("redshift -x && fish -c 'set -Ux REDSHIFT_ON false' && kill -45 $(pidof dwmblocks)") },        // Disable redshift
    { MODKEY, -1, XK_F1, spawn, SHCMD("redshift -P -O 3500 && fish -c 'set -Ux REDSHIFT_ON true' && kill -45 $(pidof dwmblocks)") }, // Enable redshift

    /* Unused keybindings */
    /* { MODKEY,           XK_z,      zoom,      {0} }, */
    /* { MODKEY,           XK_space,  setlayout, {0} }, */
    /* { MODKEY,           XK_comma,  focusmon,  {.i = -1 } }, */
    /* { MODKEY,           XK_period, focusmon,  {.i = +1 } }, */
    /* { MODKEY|ShiftMask, XK_comma,  tagmon,    {.i = -1 } }, */
    /* { MODKEY|ShiftMask, XK_period, tagmon,    {.i = +1 } }, */
    /* TAGKEYS(            XK_5,                 4) */
    /* TAGKEYS(            XK_6,                 5) */
    /* TAGKEYS(            XK_7,                 6) */
    /* TAGKEYS(            XK_8,                 7) */
    /* TAGKEYS(            XK_9,                 8) */
};

/* Button definitions */
/* Click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* Click         Event mask  Button   Function        Argument */
    { ClkLtSymbol,   0,          Button1, setlayout,      {0} },
    { ClkLtSymbol,   0,          Button3, setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,   0,          Button2, zoom,           {0} },
    { ClkStatusText, 0,          Button2, spawn,          {.v = termcmd } },
    { ClkClientWin,  MODKEY,     Button1, movemouse,      {0} },
    { ClkClientWin,  MODKEY,     Button2, togglefloating, {0} },
    { ClkClientWin,  MODKEY,     Button3, resizemouse,    {0} },
    { ClkTagBar,     0,          Button1, view,           {0} },
    { ClkTagBar,     0,          Button3, toggleview,     {0} },
    { ClkTagBar,     MODKEY,     Button1, tag,            {0} },
    { ClkTagBar,     MODKEY,     Button3, toggletag,      {0} },
};

/* Signals */
/* signum must be greater than 0 */
/* trigger signals using 'xsetroot -name "fsignal:<signum>"' */
static Signal signals[] = {
    /* Signum  Function       Argument  */
    { 1,       togglefullscr, {0} },
    { 2,       view,          {.ui = 1 << 3} },
};
