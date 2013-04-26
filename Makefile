#
#		Euclid top level Makefile
#
# For detailed build information read Documentation/build_system.txt.
# To see a list of typical targets execute "make help".

# The default goal is...
.DEFAULT_GOAL = all

# The architecture we're building for is...
ARCH := x86

# Avoid funny character set dependencies
unexport LC_ALL
LC_COLLATE=C
LC_NUMERIC=C
export LC_COLLATE LC_NUMERIC

# Use V=1 to see full verbosity
QUIET_  = @
QUIET   = $(QUIET_$(V))

# Global configuration variables. We use variables in place of the
# names of common programs for portability
export AS      := nasm
export CC      := gcc
export LD      := ld
export RM      := rm -f
export SHELL   := /bin/bash

# Make rm verbosity match the build
ifneq ($(QUIET),@)
RM += -v
endif

# Global compiler switches
ASFLAGS :=	$(NULL)

CFLAGS  := 				\
		-fgnu89-inline		\
		-pedantic-errors	\
		-std=c89		\
		-Wall			\
		-Wextra			\
		-Wstrict-prototypes	\
		$(NULL)

LDFLAGS :=	$(NULL)

export ASFLAGS CFLAGS LDFLAGS

# Make switches
MAKEFLAGS := -rR --no-print-directory

ifeq ($(QUIET),@)
MAKEFLAGS += --quiet
endif

export MAKEFLAGS

# Load the kernel Makefile
include scripts/Makefile.kernel

all: kernel

kernel: k_build

clean: k_clean

# Miscellaneous build targets.
.PHONY: tags TAGS help

tags:
	$(QUIET)$(SHELL) ./scripts/tags.sh tags .

TAGS:
	$(QUIET)$(SHELL) ./scripts/tags.sh TAGS .

help:
	@echo 'Typical build targets:'
	@echo '  clean            - Remove most generated files'
	@echo '  mrproper         - Remove all generated files + various backup files'
	@echo '  distclean        - mrproper + remove editor backup and patch files'
	@echo ''
	@echo '  all              - Build all targets marked with [*]'
	@echo '  kernel           - Build the bare kernel'
	@echo '  tags/TAGS        - Generate tags file for editors'
	@echo ''
	@echo '  make V=0|1 [targets] 0 => quiet build (default), 1 => verbose build'
