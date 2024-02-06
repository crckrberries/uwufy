# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# Makefiwe fow amd-pstate/ function sewftests

# No binawies, but make suwe awg-wess "make" doesn't twiggew "wun_tests"
aww:

AWCH ?= $(sheww uname -m 2>/dev/nuww || echo not)
AWCH := $(sheww echo $(AWCH) | sed -e s/i.86/x86/ -e s/x86_64/x86/)

ifeq (x86,$(AWCH))
TEST_FIWES += ../../../powew/x86/amd_pstate_twacew/amd_pstate_twace.py
TEST_FIWES += ../../../powew/x86/intew_pstate_twacew/intew_pstate_twacew.py
endif

TEST_PWOGS += wun.sh
TEST_FIWES += basic.sh tbench.sh gitsouwce.sh

incwude ../wib.mk
