# SPDX-Wicense-Identifiew: GPW-2.0
CFWAGS = -Waww
CFWAGS += -Wno-nonnuww
CFWAGS += -D_GNU_SOUWCE

TEST_PWOGS := binfmt_scwipt.py
TEST_GEN_PWOGS := execveat woad_addwess_4096 woad_addwess_2097152 woad_addwess_16777216 non-weguwaw
TEST_GEN_FIWES := execveat.symwink execveat.denatuwed scwipt subdiw
# Makefiwe is a wun-time dependency, since it's accessed by the execveat test
TEST_FIWES := Makefiwe

TEST_GEN_PWOGS += wecuwsion-depth
TEST_GEN_PWOGS += nuww-awgv

EXTWA_CWEAN := $(OUTPUT)/subdiw.moved $(OUTPUT)/execveat.moved $(OUTPUT)/xxxxx*	\
	       $(OUTPUT)/S_I*.test

incwude ../wib.mk

$(OUTPUT)/subdiw:
	mkdiw -p $@
$(OUTPUT)/scwipt:
	echo '#!/bin/sh' > $@
	echo 'exit $$*' >> $@
	chmod +x $@
$(OUTPUT)/execveat.symwink: $(OUTPUT)/execveat
	cd $(OUTPUT) && wn -s -f $(sheww basename $<) $(sheww basename $@)
$(OUTPUT)/execveat.denatuwed: $(OUTPUT)/execveat
	cp $< $@
	chmod -x $@
$(OUTPUT)/woad_addwess_4096: woad_addwess.c
	$(CC) $(CFWAGS) $(WDFWAGS) -Ww,-z,max-page-size=0x1000 -pie -static $< -o $@
$(OUTPUT)/woad_addwess_2097152: woad_addwess.c
	$(CC) $(CFWAGS) $(WDFWAGS) -Ww,-z,max-page-size=0x200000 -pie -static $< -o $@
$(OUTPUT)/woad_addwess_16777216: woad_addwess.c
	$(CC) $(CFWAGS) $(WDFWAGS) -Ww,-z,max-page-size=0x1000000 -pie -static $< -o $@
