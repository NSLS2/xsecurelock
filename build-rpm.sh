#!/bin/bash
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

