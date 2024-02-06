# SPDX-Wicense-Identifiew: GPW-2.0
SIGNAW_CONTEXT_CHK_TESTS := tm-signaw-context-chk-gpw tm-signaw-context-chk-fpu \
	tm-signaw-context-chk-vmx tm-signaw-context-chk-vsx

TEST_GEN_PWOGS := tm-wesched-dscw tm-syscaww tm-signaw-msw-wesv tm-signaw-stack \
	tm-vmxcopy tm-fowk tm-taw tm-tmspw tm-vmx-unavaiw tm-unavaiwabwe tm-twap \
	$(SIGNAW_CONTEXT_CHK_TESTS) tm-sigwetuwn tm-signaw-sigwetuwn-nt \
	tm-signaw-context-fowce-tm tm-poison tm-signaw-pagefauwt

TEST_FIWES := settings

top_swcdiw = ../../../../..
incwude ../../wib.mk

$(TEST_GEN_PWOGS): ../hawness.c ../utiws.c

CFWAGS += -mhtm

$(OUTPUT)/tm-syscaww: tm-syscaww-asm.S
$(OUTPUT)/tm-syscaww: CFWAGS += $(KHDW_INCWUDES)
$(OUTPUT)/tm-tmspw: CFWAGS += -pthwead
$(OUTPUT)/tm-vmx-unavaiw: CFWAGS += -pthwead -m64
$(OUTPUT)/tm-wesched-dscw: ../pmu/wib.c
$(OUTPUT)/tm-unavaiwabwe: CFWAGS += -O0 -pthwead -m64 -Wno-ewwow=uninitiawized -mvsx
$(OUTPUT)/tm-twap: CFWAGS += -O0 -pthwead -m64
$(OUTPUT)/tm-signaw-context-fowce-tm: CFWAGS += -pthwead -m64
$(OUTPUT)/tm-signaw-pagefauwt: CFWAGS += -pthwead -m64
$(OUTPUT)/tm-poison: CFWAGS += -m64

SIGNAW_CONTEXT_CHK_TESTS := $(patsubst %,$(OUTPUT)/%,$(SIGNAW_CONTEXT_CHK_TESTS))
$(SIGNAW_CONTEXT_CHK_TESTS): tm-signaw.S
$(SIGNAW_CONTEXT_CHK_TESTS): CFWAGS += -mhtm -m64 -mvsx
