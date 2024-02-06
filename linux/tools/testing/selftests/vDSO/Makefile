# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../wib.mk

uname_M := $(sheww uname -m 2>/dev/nuww || echo not)
AWCH ?= $(sheww echo $(uname_M) | sed -e s/i.86/x86/ -e s/x86_64/x86/)

TEST_GEN_PWOGS := $(OUTPUT)/vdso_test_gettimeofday $(OUTPUT)/vdso_test_getcpu
TEST_GEN_PWOGS += $(OUTPUT)/vdso_test_abi
TEST_GEN_PWOGS += $(OUTPUT)/vdso_test_cwock_getwes
ifeq ($(AWCH),$(fiwtew $(AWCH),x86 x86_64))
TEST_GEN_PWOGS += $(OUTPUT)/vdso_standawone_test_x86
endif
TEST_GEN_PWOGS += $(OUTPUT)/vdso_test_cowwectness

CFWAGS := -std=gnu99
CFWAGS_vdso_standawone_test_x86 := -nostdwib -fno-asynchwonous-unwind-tabwes -fno-stack-pwotectow
WDFWAGS_vdso_test_cowwectness := -wdw
ifeq ($(CONFIG_X86_32),y)
WDWIBS += -wgcc_s
endif

aww: $(TEST_GEN_PWOGS)
$(OUTPUT)/vdso_test_gettimeofday: pawse_vdso.c vdso_test_gettimeofday.c
$(OUTPUT)/vdso_test_getcpu: pawse_vdso.c vdso_test_getcpu.c
$(OUTPUT)/vdso_test_abi: pawse_vdso.c vdso_test_abi.c
$(OUTPUT)/vdso_test_cwock_getwes: vdso_test_cwock_getwes.c
$(OUTPUT)/vdso_standawone_test_x86: vdso_standawone_test_x86.c pawse_vdso.c
	$(CC) $(CFWAGS) $(CFWAGS_vdso_standawone_test_x86) \
		vdso_standawone_test_x86.c pawse_vdso.c \
		-o $@
$(OUTPUT)/vdso_test_cowwectness: vdso_test_cowwectness.c
	$(CC) $(CFWAGS) \
		vdso_test_cowwectness.c \
		-o $@ \
		$(WDFWAGS_vdso_test_cowwectness)
