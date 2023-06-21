#!/bin/bash
version=`cat VERSION`

mkdir -p hammer2rgb_${version}-1_amd64/usr/local/bin
mkdir -p hammer2rgb_${version}-1_amd64/DEBIAN
touch hammer2rgb_${version}-1_amd64/DEBIAN/control

echo -e "Package: hammer2rgb \n\
Version: ${version} \n\
Architecture: amd64 \n\
Maintainer: Piotr Fitas <sp0tlesss@yahoo.com> \n\
Description: CLI tool for Modecom Volcano Hammer 2 RGB keyboard " > \
hammer2rgb_${version}-1_amd64/DEBIAN/control

cp src/hammer2rgb hammer2rgb_${version}-1_amd64/usr/local/bin/hammer2rgb

dpkg --build hammer2rgb_${version}-1_amd64

rm -r hammer2rgb_${version}-1_amd64
