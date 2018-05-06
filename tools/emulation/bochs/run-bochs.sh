#!/bin/bash

#
#	run-bochs.sh - Run a bochs session
#
# Execute with "--help" argument for usage information

config="./tools/emulation/bochs/bochsrc"
log="./tools/emulation/bochs/log"
floppy="./tools/emulation/bochs/floppy.img"
loopback="/dev/loop0"
mountpoint="/mnt/euclid"

print_usage() {
    echo "Usage: $(basename $0)" >&2
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
    sudo umount "$loopback" > /dev/null 2>&1
    sudo losetup -d "$loopback" > /dev/null 2>&1
    sudo rm -rf "$mountpoint"
}

trap destroy_loopback EXIT

run_bochs() {
    create_loopback
    sudo bochs -qf "$config" -log "$log"
}

# Parse --help argument
test "x$1" == "x--help" && { print_usage;
    exit 0; }

test -f "$config" || fatal "configuration file '$config' not found"
run_bochs

exit 0
