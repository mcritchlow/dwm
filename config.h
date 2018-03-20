/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
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
	/* class          instance      title       tags mask     isfloating   monitor */
	{ "Gimp",         NULL,         NULL,       0,            1,           -1 },
	{ "etcher",       NULL,         NULL,       0,            1,           -1 },
	{ "Firefox",      NULL,         NULL,       1 << 8,       0,           -1 },
	{ "Slack",        NULL,         NULL,       1 << 3,       0,           -1 },
	{ "Hexchat",      NULL,         NULL,       1 << 4,       0,           -1 },
	{ "Spotiy",       NULL,         NULL,       1 << 5,       0,           -1 },
	{ "st-256color",  "mutt",       NULL,       1 << 7,       0,           -1 },
	{ "st-256color",  "calcurse",   NULL,       1 << 6,       0,           -1 },
	{ "st-256color",  "ncmpcpp",    NULL,       1 << 8,       0,           -1 },
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
};

/* key definitions */
#define MODKEY Mod4Mask /* use super key as MODKEY */
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
static const char *clipcmd[] = { "clipmenu", "-i", "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *rangercmd[]  = { "st", "-e", "ranger", NULL };
static const char *brightnessupcmd[]  = { "/usr/local/bin/brightlight", "-p", "-i", "10", NULL };
static const char *brightnessdowncmd[]  = { "/usr/local/bin/brightlight", "-p", "-d", "10", NULL };
static const char *pctlplaycmd[]  = { "playerctl", "play", NULL };
static const char *pctlpausecmd[]  = { "playerctl", "pause", NULL };
static const char *pctlnextcmd[]  = { "playerctl", "next", NULL };
static const char *pctlpreviouscmd[]  = { "playerctl", "previous", NULL };
static const char *hexchatcmd[]  = { "hexchat", NULL };
static const char *slackcmd[]  = { "slack", NULL };
static const char *gbrowsercmd[]  = { "firefox", NULL };
static const char *tbrowsercmd[]  = { "st", "-e", "bash", "-i", "-c", "w3m", "https://duckduckgo.com", NULL };
/* TODO: move mail.sh out to non-i3 */
static const char *mailcmd[]  = { "st", "-n", "mutt", "-e", "bash", "-i", "-c", "~/.config/i3/scripts/mail.sh", NULL };
static const char *calcursecmd[]  = { "st", "-n", "calcurse", "-e", "bash", "-i", "-c", "calcurse -D $HOME/.config/calcurse/", NULL };
static const char *ncmpcppcmd[]  = { "st", "-n", "ncmpcpp", "-e", "bash", "-i", "-c", "ncmpcpp -s media_library", NULL };
static const char *spotifycmd[]  = { "spotify", NULL };
static const char *printcmd[]  = { "scrot", "-q", "100", "-e", "mv $f ~/Pictures/", NULL };
static const char *printselcmd[]  = { "scrot", "-s", "-q", "100", "-e", "mv $f ~/Pictures/", NULL };
static const char *raisevolumecmd[]  = { "amixer", "-D", "pulse", "sset", "Master", "5%+", "&&", "paplay", "/usr/share/sounds/freedesktop/stereo/audio-volume-change.oga", NULL };
static const char *lowervolumecmd[]  = { "amixer", "-D", "pulse", "sset", "Master", "5%-", "&&", "paplay", "/usr/share/sounds/freedesktop/stereo/audio-volume-change.oga", NULL };
static const char *mutecmd[]  = { "amixer", "-D", "pulse", "sset", "Master", "toggle-mute", NULL };
static const char *mpctogglecmd[]  = { "mpc", "toggle", NULL };
static const char *mpcffcmd[]  = { "mpc", "seek", "+10", NULL };
static const char *mpcfffcmd[]  = { "mpc", "seek", "+120", NULL };
static const char *mpcrrcmd[]  = { "mpc", "seek", "-10", NULL };
static const char *mpcrrrcmd[]  = { "mpc", "seek", "-120", NULL };
static const char *mpcprevcmd[]  = { "mpc", "prev", NULL };
static const char *mpcnextcmd[]  = { "mpc", "next", NULL };
static const char *restartcmd[]  = { "systemctl", "reboot", NULL };
static const char *shutdowncmd[]  = { "systemctl", "poweroff", "-i", NULL };
static const char *lockcmd[] = { "slock", NULL };

/* 
 */

#include <X11/XF86keysym.h> /* makes XF86* keys work */
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = clipcmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_f,      spawn,          {.v = rangercmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = hexchatcmd } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = slackcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = mailcmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = calcursecmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = gbrowsercmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = tbrowsercmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = spotifycmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = ncmpcppcmd } },
	{ MODKEY,                       XK_bracketright,   spawn,  {.v = mpcffcmd } },
	{ MODKEY|ShiftMask,             XK_bracketright,   spawn,  {.v = mpcfffcmd } },
	{ MODKEY,                       XK_bracketleft,   spawn,   {.v = mpcrrcmd } },
	{ MODKEY|ShiftMask,             XK_bracketleft,   spawn,   {.v = mpcrrrcmd } },
	{ MODKEY,                       XK_less,   spawn,          {.v = mpcprevcmd } },
	{ MODKEY,                       XK_greater, spawn,         {.v = mpcnextcmd } },
	{ 0,                            XK_Print,     spawn,       {.v = printcmd } },
	{ ShiftMask,                    XK_Print,     spawn,       {.v = printselcmd } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,      {.v = brightnessupcmd } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,      {.v = brightnessdowncmd } },
	{ 0,                            XF86XK_AudioPlay,          spawn,      {.v = pctlplaycmd } },
	{ 0,                            XF86XK_AudioPause,         spawn,      {.v = pctlpausecmd } },
	{ 0,                            XF86XK_AudioNext,          spawn,      {.v = pctlnextcmd } },
	{ 0,                            XF86XK_AudioPrev,          spawn,      {.v = pctlpreviouscmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,      {.v = raisevolumecmd } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,      {.v = lowervolumecmd } },
	{ 0,                            XF86XK_AudioMute,          spawn,      {.v = mutecmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_k,      killclient,     {0} },
	{ MODKEY,                       XK_t,      spawn,           {.v = mpctogglecmd } },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = restartcmd } },
	{ MODKEY,                       XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = shutdowncmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
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

