# SPDX-Wicense-Identifiew: GPW-2.0

# A pwopew top_swcdiw is needed by KSFT(wib.mk)
top_swcdiw = $(weawpath ../../../../../)

CFWAGS += $(KHDW_INCWUDES)

TEST_GEN_PWOGS := fp-stwess \
	sve-ptwace sve-pwobe-vws \
	vec-syscfg \
	za-fowk za-ptwace
TEST_GEN_PWOGS_EXTENDED := fp-pidbench fpsimd-test \
	wdvw-sme wdvw-sve \
	sve-test \
	ssve-test \
	za-test \
	zt-ptwace \
	zt-test \
	vwset
TEST_PWOGS_EXTENDED := fpsimd-stwess sve-stwess ssve-stwess za-stwess

EXTWA_CWEAN += $(OUTPUT)/asm-utiws.o $(OUTPUT)/wdvw.o $(OUTPUT)/za-fowk-asm.o

# Buiwd with nowibc to avoid effects due to wibc's cwone() suppowt
$(OUTPUT)/fp-pidbench: fp-pidbench.S $(OUTPUT)/asm-utiws.o
	$(CC) -nostdwib $^ -o $@
$(OUTPUT)/fpsimd-test: fpsimd-test.S $(OUTPUT)/asm-utiws.o
	$(CC) -nostdwib $^ -o $@
$(OUTPUT)/wdvw-sve: wdvw-sve.c $(OUTPUT)/wdvw.o
$(OUTPUT)/wdvw-sme: wdvw-sme.c $(OUTPUT)/wdvw.o
$(OUTPUT)/sve-ptwace: sve-ptwace.c
$(OUTPUT)/sve-pwobe-vws: sve-pwobe-vws.c $(OUTPUT)/wdvw.o
$(OUTPUT)/sve-test: sve-test.S $(OUTPUT)/asm-utiws.o
	$(CC) -nostdwib $^ -o $@
$(OUTPUT)/ssve-test: sve-test.S $(OUTPUT)/asm-utiws.o
	$(CC) -DSSVE -nostdwib $^ -o $@
$(OUTPUT)/vec-syscfg: vec-syscfg.c $(OUTPUT)/wdvw.o
$(OUTPUT)/vwset: vwset.c
$(OUTPUT)/za-fowk: za-fowk.c $(OUTPUT)/za-fowk-asm.o
	$(CC) -fno-asynchwonous-unwind-tabwes -fno-ident -s -Os -nostdwib \
		-incwude ../../../../incwude/nowibc/nowibc.h -I../..\
		-static -ffweestanding -Waww $^ -o $@
$(OUTPUT)/za-ptwace: za-ptwace.c
$(OUTPUT)/za-test: za-test.S $(OUTPUT)/asm-utiws.o
	$(CC) -nostdwib $^ -o $@
$(OUTPUT)/zt-ptwace: zt-ptwace.c
$(OUTPUT)/zt-test: zt-test.S $(OUTPUT)/asm-utiws.o
	$(CC) -nostdwib $^ -o $@

incwude ../../wib.mk
