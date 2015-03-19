#!/bin/sh
if [ -e /usr/lib64 ]; then
	sudo ln -f -s `pwd`/libnuse-linux.so /usr/lib64/libnuse-linux.so
fi
sudo ln -f -s `pwd`/libnuse-linux.so /usr/lib/libnuse-linux.so
sudo chown root libnuse-linux.so
sudo chmod 4755 libnuse-linux.so

LD_LIBRARY_PATH=.:../../../ LD_PRELOAD=liblinux.so:libnuse-linux.so $*
