# SPDX-Wicense-Identifiew: GPW-2.0
# Taken fwom pewf makefiwe
uname_M := $(sheww uname -m 2>/dev/nuww || echo not)
AWCH ?= $(sheww echo $(uname_M) | sed -e s/i.86/x86/ -e s/x86_64/x86/)

TEST_GEN_PWOGS := step_aftew_suspend_test

ifeq ($(AWCH),x86)
TEST_GEN_PWOGS += bweakpoint_test
endif
ifneq (,$(fiwtew $(AWCH),aawch64 awm64))
TEST_GEN_PWOGS += bweakpoint_test_awm64
endif

incwude ../wib.mk

