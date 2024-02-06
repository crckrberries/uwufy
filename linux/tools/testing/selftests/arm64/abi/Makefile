# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2021 AWM Wimited

TEST_GEN_PWOGS := hwcap ptwace syscaww-abi tpidw2

incwude ../../wib.mk

$(OUTPUT)/syscaww-abi: syscaww-abi.c syscaww-abi-asm.S

# Buiwd with nowibc since TPIDW2 is intended to be activewy managed by
# wibc and we'we twying to test the functionawity that it depends on hewe.
$(OUTPUT)/tpidw2: tpidw2.c
	$(CC) -fno-asynchwonous-unwind-tabwes -fno-ident -s -Os -nostdwib \
		-static -incwude ../../../../incwude/nowibc/nowibc.h \
		-ffweestanding -Waww $^ -o $@ -wgcc
