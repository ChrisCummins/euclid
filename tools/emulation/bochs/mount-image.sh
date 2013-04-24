#!/bin/bash
#
#	mount-image.sh - Mount the boot image
#

floppy="./tools/emulation/bochs/floppy.img"
loopback="/dev/loop0"
mountpoint="/mnt/euclid"

set -e
sudo mkdir -p "$mountpoint"
sudo losetup "$loopback" "$floppy"
sudo mount "$loopback" "$mountpoint"
echo "mounted image at '$mountpoint'"
