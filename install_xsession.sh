#!/usr/bin/env fish

if not test -d /usr/share/xsessions
    mkdir -p /usr/share/xsessions
end

cp ./dwm.desktop /usr/share/xsessions/
