#!/bin/bash

version=`cat VERSION`
echo $version

rm apt-repo/pool/main/hammer2rgb*
cp hammer2rgb_${version}-1_amd64.deb apt-repo/pool/main/

CUR_DIR=$PWD

cd apt-repo
dpkg-scanpackages --arch amd64 pool/ > dists/stable/main/binary-amd64/Packages
cat dists/stable/main/binary-amd64/Packages | gzip -9 > dists/stable/main/binary-amd64/Packages.gz

cd dists/stable/
./gen.sh > Release

cd $CUR_DIR
cp .htaccess apt-repo/
zip repo.zip -r apt-repo
