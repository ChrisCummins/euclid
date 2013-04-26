#
#		Bochs emulation Makefile
#
# This defines a bochs target which automates the process of building, preparing
# and booting the euclid kernel under bochs.

bochs: k_build
	./tools/emulation/bochs/update-image.sh
	./tools/emulation/bochs/run-bochs.sh
