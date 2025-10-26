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

GITDESC=$(git describe --abbrev=0)
VERSION=$(git describe --abbrev=0 | sed -En 's/v([0-9]+\.)([0-9]+\.)?([0-9]+)-.*/\1\2\3/p')
echo "##[debug] GITDESC = $GITDESC"
echo "##[debug] VERSION = $VERSION"

RPMDIR="`pwd`/rpmbuild"
echo $RPMDIR
SOURCES=${RPMDIR}/SOURCES
mkdir -p ${SOURCES}
git archive --format=tar \
  --prefix=xsecurelock-$VERSION-nsls2/ \
  --output=${SOURCES}/xsecurelock-v$VERSION-nsls2.tar.gz \
  HEAD
cp xautolock.patch ${SOURCES}
cp xautolock-allow-locknow.patch ${SOURCES}
rpmbuild -bb --define "_topdir ${RPMDIR}" --define "version $VERSION" xsecurelock-nsls2.spec
rpmbuild -bs --define "_topdir ${RPMDIR}" --define "version $VERSION" xsecurelock-nsls2.spec
rpmbuild -bb --undefine="_disable_source_fetch" --define "_topdir ${RPMDIR}" xautolock-nsls2.spec
rpmbuild -bb --undefine="_disable_source_fetch" --define "_topdir ${RPMDIR}" feh.spec

