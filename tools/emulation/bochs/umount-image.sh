#!/bin/bash

#
#	umount-image.sh - Unmount the boot image
#

floppy="./tools/emulation/bochs/floppy.img"
loopback="/dev/loop0"
mountpoint="/mnt/euclid"

set -e
sudo umount "$loopback" > /dev/null 2>&1
sudo losetup -d "$loopback" > /dev/null 2>&1
sudo rm -rf "$mountpoint"
echo "unmounted '$mountpoint'"
