#!/bin/bash
set -e
./autogen.sh
./configure \
  --with-pam \
  --with-pam-service-name=xsecurelock \
  --with-userfile-priv=/etc/xsecurelock/userfile-priv \
  --with-userfile-block=/etc/xsecurelock/userfile-block \
  --with-userfile-any=/etc/xsecurelock/userfile-any \
  --with-userfile-noblank=/etc/xsecurelock/userfile-noblank \
  --with-banner-filename=/etc/xsecurelock/banner \
  --enable-any-user-auth \
  --enable-banner \
  --enable-wallpaper \
  --enable-no-blank \
  --enable-secure \
  --with-fontconfig \
  --without-htpasswd \
  --with-fontconfig \
  --with-mplayer=/usr/bin/mplayer \
  --with-mpv=/usr/bin/mpv \
  --with-pamtester=no \
  --with-xcomposite \
  --with-xf86misc=no \
  --with-xrandr \
  --with-xss \
  --with-xsync \
  --with-xfixes \
  --with-xft \
  --with-xkb

make

