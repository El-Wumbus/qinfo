#!/usr/bin/env sh

if [ -d "/usr/bin/qinfo" ]; then
    echo "qinfo is already installed at '/usr/bin/qinfo'"
    exit 0
elif [ -d "/usr/local/bin/qinfo" ]; then
    echo "qinfo is already installed at '/usr/local/bin/qinfo'"
    exit 0
fi

if [ ! -d build ]; then
    mkdir build
    meson setup build || exit $?
fi

meson compile -C build || exit $?

if [ "$(id -u)" -ne "0" ]; then
    sudo install build/qinfo -Dm755 /usr/local/bin/qinfo || exit $?
else
    install build/qinfo -Dm755 /usr/local/bin/qinfo || exit $?
fi
