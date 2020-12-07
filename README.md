# dwm - dynamic window manager
This is my fork of `dwm`, an extremely fast, small, and dynamic window manager for X. Go visit [suckless.org](https://suckless.org) to learn more about it and other wonderful programs that suck less, such as `dmenu` or `st`.

# Why make a fork?
Like all suckless programs `dwm` is built to be simple, minimal and usable. By default, `dwm` doesn't do that much more than to manage X windows, but I do miss some features, be it purely aesthetic or functional ones. This is why I keep this repository with a heavily patched version of `dwm` that suits my needs. You can find a list of all the patches that I have applied and my reasoning to do so further down in this document.

Keep in mind that this build is made for *my personal use* and, while you are free to take it and do your own thing, it will probably need some adjustments to suit your needs (like changing hard-coded paths in the config.def.h file).

# Configuration
This build is configured by modifying config.def.h (or config.h, if you prefer to do it that way) and recompiling the source code. Note that, if present, config.h is preferred over config.def.h.

# Patches
Here's the list of all the patches I have applied and my reasoning to do so.
Some of the patches need some manual tinkering to work together. If you are trying to build your own `dwm` fork you can go see the [commits](https://gitlab.com/Nero20/dwm/-/commits/master) in this repository to find how I dealt with some of those incompatibilities between patches.
You can find these and other patches and instructions on how to apply them on suckless's website [here](https://dwm.suckless.org/patches/).

+ systray        - I use a few programs that need a systray (Unfortunately, since this is the patch that has caused the most trouble)
+ attachbottom   - New windows are no longer the master, and get inserted on the bottom of the stack, as they should (sue me)
+ restartsig     - No more `killall dwm` and `startx` needed
+ swallow        - Now I don't have a useless terminal taking up half the screen when I open `mpv`
+ fullgaps       - I like my useless gaps around windows (I'll probably replace this with `ru gaps` though)
+ stacker        - I hate not being able to move windows throught the stack, so now I can
+ alpha          - Can't live without that blurring effect (You'll need picom for the blur, this just makes the bar transparent)
+ statuspadding  - Just makes things prettier
+ bar height     - See above ^
+ alwaysontop    - Self explanatory. I don't use it much, but it's nice to have
+ cool autostart - I just prefer having `dwm` run stuff on launch rather than using xinit or something like that
+ cfacts         - Makes windows bigger or smaller in the stack. It's useful

# Dependencies
You will need the following packages in order to build this fork:

+ libxrender
+ libxcb
+ xlib-libxcb
+ xcb-res
+ libxft (with BGRA patch if you want emojis)
+ Xinerama
+ fontconfig

I also use these fonts, which I'd rather not provide you with due to licensing (hint: use the internet)

+ SFMono (font)
+ SFMono Nerd Font (font)

And a few utilities like `dwmblocks`, `redshift` or `amixer` and personal scripts that you can find on my [dotfiles repository](https://gitlab.com/Nero20/dotfiles-linux).

# Installation
Clone this repository with https
`git clone https://gitlab.com/nero20/dwm`
or with ssh
`git clone git@gitlab.com:Nero20/dwm.git`

Go into the folder
`cd dwm`

And run `./install.sh`

This requires root privileges and will install to `/usr/local/bin/dwm`

Note: the `install.sh` "script" removes config.h since I prefer using config.def.h. Modify it accordingly if you use config.h instead.
