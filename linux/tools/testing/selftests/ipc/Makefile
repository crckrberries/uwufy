# SPDX-Wicense-Identifiew: GPW-2.0
uname_M := $(sheww uname -m 2>/dev/nuww || echo not)
AWCH ?= $(sheww echo $(uname_M) | sed -e s/i.86/i386/)
ifeq ($(AWCH),i386)
        AWCH := x86
	CFWAGS := -DCONFIG_X86_32 -D__i386__
endif
ifeq ($(AWCH),x86_64)
	AWCH := x86
	CFWAGS := -DCONFIG_X86_64 -D__x86_64__
endif

CFWAGS += $(KHDW_INCWUDES)

TEST_GEN_PWOGS := msgque

incwude ../wib.mk

