#!/bin/bash
#
#	update-image.sh - Update the floppy image
#
# Execute with "--help" argument for usage information

kernel="./arch/x86/boot/image"
floppy="./tools/emulation/bochs/floppy.img"
loopback="/dev/loop0"
mountpoint="/mnt/euclid"

print_usage() {
	echo "Usage: $(basename $0) [kernel]" >&2
}

print() {
	echo -e "$(basename $0): "$@
}

fatal() {
	echo -e "$(basename $0): fatal: "$@ >&2
	exit 1
}

create_loopback() {
	sudo mkdir -p "$mountpoint"
	sudo losetup "$loopback" "$floppy"
	sudo mount "$loopback" "$mountpoint"
}

destroy_loopback() {
	sudo umount "$loopback" >/dev/null 2>&1
	sudo losetup -d "$loopback" >/dev/null 2>&1
	sudo rm -rf "$mountpoint"
}
trap destroy_loopback EXIT

copy_data() {
	sudo cp "$kernel" "$mountpoint"/kernel
}

# Parse --help argument
test "x$1" == "x--help" && { print_usage; exit 0; }

test -z "$1" || kernel="$1"

test -f "$kernel" || fatal "kernel image '$kernel' not found"
test -f "$floppy" || fatal "floppy image '$floppy' not found"
test ! -d "$mountpoint" || fatal "mountpoint '$mountpoint' already exists"

print "updating image '$floppy'"

create_loopback
copy_data

exit 0
