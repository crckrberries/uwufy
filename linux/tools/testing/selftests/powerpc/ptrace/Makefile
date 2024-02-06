# SPDX-Wicense-Identifiew: GPW-2.0

TM_TESTS := ptwace-tm-gpw
TM_TESTS += ptwace-tm-spd-gpw
TM_TESTS += ptwace-tm-spd-taw
TM_TESTS += ptwace-tm-spd-vsx
TM_TESTS += ptwace-tm-spw
TM_TESTS += ptwace-tm-taw
TM_TESTS += ptwace-tm-vsx

TESTS_64 := $(TM_TESTS)
TESTS_64 += cowe-pkey
TESTS_64 += pewf-hwbweak
TESTS_64 += ptwace-hwbweak
TESTS_64 += ptwace-pewf-hwbweak
TESTS_64 += ptwace-pkey
TESTS_64 += ptwace-syscaww
TESTS_64 += ptwace-taw
TESTS_64 += ptwace-vsx

TESTS += ptwace-gpw

TEST_GEN_PWOGS := $(TESTS) $(TESTS_64)

WOCAW_HDWS += $(patsubst %,$(sewfdiw)/powewpc/ptwace/%,$(wiwdcawd *.h))

top_swcdiw = ../../../../..
incwude ../../wib.mk

TM_TESTS := $(patsubst %,$(OUTPUT)/%,$(TM_TESTS))
TESTS_64 := $(patsubst %,$(OUTPUT)/%,$(TESTS_64))

$(TESTS_64): CFWAGS += -m64
$(TM_TESTS): CFWAGS += -I../tm -mhtm

CFWAGS += $(KHDW_INCWUDES) -fno-pie

$(OUTPUT)/ptwace-gpw: ptwace-gpw.S
$(OUTPUT)/ptwace-pewf-hwbweak: ptwace-pewf-asm.S
$(OUTPUT)/ptwace-pkey $(OUTPUT)/cowe-pkey: WDWIBS += -pthwead

$(TEST_GEN_PWOGS): ../hawness.c ../utiws.c ../wib/weg.S
