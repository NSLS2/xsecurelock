#!/bin/bash
set -e
GITDESC=$(git describe --abbrev=0)
VERSION=$(git describe --abbrev=0 | sed -En 's/v([0-9]+\.)([0-9]+\.)?([0-9]+)-.*/\1\2\3/p')
mkdir -p build
gbp buildpackage \
  --git-ignore-new \
  --git-ignore-branch \
  -uc -us \
  --git-export-dir=build \
  --git-tarball-dir=build
echo $debrelease
old_debfile=$(ls -1 build/xsecurelock-nsls2_*.deb | head -1)
new_debfile=$(echo ${old_debfile} | sed "s/\.deb/-${debrelease}.deb/")
mv "${old_debfile}" "${new_debfile}"

