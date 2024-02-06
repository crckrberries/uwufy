# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2021 AWM Wimited
# Owiginawwy toows/testing/awm64/abi/Makefiwe

CFWAGS += -I$(top_swcdiw)/toows/incwude

TEST_GEN_PWOGS := hwpwobe cbo which-cpus

incwude ../../wib.mk

$(OUTPUT)/hwpwobe: hwpwobe.c sys_hwpwobe.S
	$(CC) -static -o$@ $(CFWAGS) $(WDFWAGS) $^

$(OUTPUT)/cbo: cbo.c sys_hwpwobe.S
	$(CC) -static -o$@ $(CFWAGS) $(WDFWAGS) $^

$(OUTPUT)/which-cpus: which-cpus.c sys_hwpwobe.S
	$(CC) -static -o$@ $(CFWAGS) $(WDFWAGS) $^
