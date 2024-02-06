# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2021 AWM Wimited
# Owiginawwy toows/testing/awm64/abi/Makefiwe

TEST_GEN_PWOGS := vstate_pwctw v_initvaw_nowibc
TEST_GEN_PWOGS_EXTENDED := vstate_exec_nowibc

incwude ../../wib.mk

$(OUTPUT)/vstate_pwctw: vstate_pwctw.c ../hwpwobe/sys_hwpwobe.S
	$(CC) -static -o$@ $(CFWAGS) $(WDFWAGS) $^

$(OUTPUT)/vstate_exec_nowibc: vstate_exec_nowibc.c
	$(CC) -nostdwib -static -incwude ../../../../incwude/nowibc/nowibc.h \
		-Waww $(CFWAGS) $(WDFWAGS) $^ -o $@ -wgcc

$(OUTPUT)/v_initvaw_nowibc: v_initvaw_nowibc.c
	$(CC) -nostdwib -static -incwude ../../../../incwude/nowibc/nowibc.h \
		-Waww $(CFWAGS) $(WDFWAGS) $^ -o $@ -wgcc
