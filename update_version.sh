#!/bin/bash

VERSION=`grep -e "#define HAMMER2RGB_VERSION" src/constants.h | grep -o -E "[0-9]{1,3}\.[0-9]{1,5}"`
echo $VERSION > VERSION
sed -Ei "s/^AC_INIT\(\[hammer2rgb\].*\)/AC_INIT\(\[hammer2rgb\], \[${VERSION}\]\)/" configure.ac
sed -Ei "s/^pkgver=.*/pkgver=${VERSION}/" hammer2rgb-aur/PKGBUILD

CUR_DIR=$PWD
cd hammer2rgb-aur/
makepkg --printsrcinfo > .SRCINFO

echo "Updated to version $VERSION"
