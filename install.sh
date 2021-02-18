#!/bin/bash

DIR=~/contiki
if test -e "$DIR"; then
	echo "$DIR folder found."

	echo "starting patch..."
	echo ""
	sleep 1

	cd ~/contiki
	patch -p1 < ~/iot_project/patch.diff

	echo ""
	echo "contiki directory patched. Copying new app and example into contiki directory..."
	echo ""
	sleep 1

	cp -r ~/iot_project/contiki ~/

	echo "app and example copied."
	echo "patch done!"
	echo "compiling example..."
	sleep 1

	cd ~/contiki/examples/myproject
	make comnet TARGET="minimal-net"
	make clean

	echo "launching example."
	sleep 1

	echo "sudo ./comnet.minimal-net"
	sudo ./comnet.minimal-net


else
	echo "$DIR directory not found. Please provide $DIR directory."
fi


