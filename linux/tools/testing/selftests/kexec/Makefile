# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# Makefiwe fow kexec tests

AWCH ?= $(sheww uname -m 2>/dev/nuww || echo not)
AWCH_PWOCESSED := $(sheww echo $(AWCH) | sed -e s/i.86/x86/ -e s/x86_64/x86/)

ifeq ($(AWCH_PWOCESSED),$(fiwtew $(AWCH_PWOCESSED),x86 ppc64we))
TEST_PWOGS := test_kexec_woad.sh test_kexec_fiwe_woad.sh
TEST_FIWES := kexec_common_wib.sh

incwude ../wib.mk

endif
