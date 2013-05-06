#!/bin/bash
#
#	listincludes.sh - List all header files and the sources
#			  that include them
#

h_files="$(find . -name '*.h')"
c_files="$(find . -name '*.c')"

for h in $h_files; do
	header=$(basename "$h")
	echo "HEADER $h"

	# Check first for header file includes
	for hin in $h_files; do
		grep -E "\s*#\s*include\s+<.*$header\s*>" \
			"$hin" &>/dev/null && {
			echo -e "\tHEADER "$hin
		}
	done

	# Then check for source file includes
	for cin in $c_files; do
		grep -E "\s*#\s*include\s+<.*$header\s*>" \
			"$cin" &>/dev/null && {
			echo -e "\tSOURCE "$cin
		}
	done
	echo ""
done
