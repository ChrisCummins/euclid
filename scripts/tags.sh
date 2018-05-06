#!/bin/bash

#
#	tags.sh - Generate tags files for Euclid sources
#
# Execute with "--help" argument for usage information

print_usage() {
    echo "Usage: $(basename $0) <tags|TAGS> <directory ...>" >&2
}

generate_tags() {
    local dirs="$@"

    for d in $dirs; do
        test -d "$d" || {
        echo "Directory '$d' not found" >&2
        exit 1
    }
    done

    local sources=$(find $dirs -name '*.[ch]')

    $tagp $sources
}

#
# Script begins here
#

# Parse --help argument
test "x$1" == "x--help" && { print_usage;
    exit 0; }

# Fail if no directory is specified
test -z "$2" && { print_usage;
    exit 1; }

# Determine the program to use to create the tags file. We use etags and ctags
# to generate tag files for Emacs and vi respectively
case "$1" in
    TAGS)
        tagp=etags
    ;;
    tags)
        tagp=ctags
    ;;
    *)
        print_usage
        exit 1
esac

# Discard the tags/TAGS argument
shift

$tagp --version &> /dev/null || {
    echo "Missing package '$tagp' is required to generate tags file" >&2
    exit 1
}

generate_tags $@

exit 0
