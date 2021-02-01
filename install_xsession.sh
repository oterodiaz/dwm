#!/usr/bin/env fish

if not test -d /usr/local/share/xsessions
    mkdir -p /usr/local/share/xsessions
end

cp ./dwm.desktop /usr/local/share/xsessions/
