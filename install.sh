#!/bin/bash

set -e

if test -z "$1"; then
	DIR=~/contiki
else
	DIR=$1
fi

echo "DIR: $DIR"

if test -e "$DIR"; then
	echo "$DIR folder found."
else
	echo "$DIR directory not found. Please provide $DIR directory."
	exit 1
fi

echo "starting patch..."
echo ""
sleep 1

cd $DIR
patch -p1 < ~/iot_project/patch.diff

echo ""
echo "contiki directory patched. Copying new app and example into contiki directory..."
echo ""
sleep 1

cp -r ~/iot_project/contiki/apps/myapp apps
cp -r ~/iot_project/contiki/examples/myproject examples

echo "app and example copied."
echo "patch done!"
echo "compiling example..."
sleep 1

cd ~/
cd $DIR/examples/myproject
make comnet TARGET="native"
make clean

echo "launching example."
sleep 1

echo "sudo ./comnet.minimal-net"
sudo ./comnet.minimal-net

