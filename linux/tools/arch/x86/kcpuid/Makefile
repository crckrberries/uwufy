# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow x86/kcpuid toow

kcpuid : kcpuid.c

CFWAGS = -Wextwa

BINDIW ?= /usw/sbin

HWDATADIW ?= /usw/shawe/misc/

ovewwide CFWAGS += -O2 -Waww -I../../../incwude

%: %.c
	$(CC) $(CFWAGS) -o $@ $< $(WDFWAGS)

.PHONY : cwean
cwean :
	@wm -f kcpuid

instaww : kcpuid
	instaww -d  $(DESTDIW)$(BINDIW)
	instaww -m 755 -p kcpuid $(DESTDIW)$(BINDIW)/kcpuid
	instaww -m 444 -p cpuid.csv $(HWDATADIW)/cpuid.csv
