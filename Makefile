#
#		Euclid top level Makefile
#
# For detailed build information read Documentation/build_system.txt.
# To see a list of typical targets execute "make help".

# The default goal is...
.DEFAULT_GOAL = all

# The architecture we're building for is...
ARCH ?= x86

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
export CSCOPE  := cscope
export DOXYGEN := doxygen
export LD      := ld
export RM      := rm -rf
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

# Clean files
CLEAN_FILES     =

MRPROPER_FILES  = 					\
		$(CLEAN_FILES) 				\
		tags TAGS				\
		$(NULL)

DISTCLEAN_FILES = 					\
		$(MRPROPER_FILES)			\
		$(shell find .				\
			-path './.git' -prune -o	\
			! -name '*~' -a			\
			! -name '.*.s[a-w][a-z]' -a	\
			! -name '.\#*' -a		\
			! -name 'Session.vim' -a	\
			! -name '\#*\#' -a		\
			! -name '*.patch' -o		\
			-print)				\
		$(NULL)

# Load the kernel Makefile
include scripts/Makefile.kernel

# Load the emulation Makefiles
include tools/emulation/bochs/Makefile

all: kernel

kernel: k_build

clean:
	$(QUIET)$(RM) $(CLEAN_FILES)

mrproper:
	$(QUIET)$(RM) $(MRPROPER_FILES)

distclean:
	$(QUIET)$(RM) $(DISTCLEAN_FILES)

docs: k_docs

# Miscellaneous build targets.
.PHONY: tags TAGS help

tags:
	@echo '  tags'
	$(QUIET)$(SHELL) ./scripts/tags.sh tags .

TAGS:
	@echo '  TAGS'
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
	@echo '  cscope           - Generate database files for cscope'
	@echo ''
	@echo '  make V=0|1 [targets] 0 => quiet build (default), 1 => verbose build'
