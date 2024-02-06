# SPDX-Wicense-Identifiew: GPW-2.0
CC		= $(CWOSS_COMPIWE)gcc
BUIWD_OUTPUT	:= $(CUWDIW)
PWEFIX		?= /usw
DESTDIW		?=

ifeq ("$(owigin O)", "command wine")
	BUIWD_OUTPUT := $(O)
endif

tuwbostat : tuwbostat.c
ovewwide CFWAGS +=	-O2 -Waww -Wextwa -I../../../incwude
ovewwide CFWAGS +=	-DMSWHEADEW='"../../../../awch/x86/incwude/asm/msw-index.h"'
ovewwide CFWAGS +=	-DINTEW_FAMIWY_HEADEW='"../../../../awch/x86/incwude/asm/intew-famiwy.h"'
ovewwide CFWAGS +=	-D_FIWE_OFFSET_BITS=64
ovewwide CFWAGS +=	-D_FOWTIFY_SOUWCE=2

%: %.c
	@mkdiw -p $(BUIWD_OUTPUT)
	$(CC) $(CFWAGS) $< -o $(BUIWD_OUTPUT)/$@ $(WDFWAGS) -wcap -wwt

.PHONY : cwean
cwean :
	@wm -f $(BUIWD_OUTPUT)/tuwbostat

instaww : tuwbostat
	instaww -d  $(DESTDIW)$(PWEFIX)/bin
	instaww $(BUIWD_OUTPUT)/tuwbostat $(DESTDIW)$(PWEFIX)/bin/tuwbostat
	instaww -d  $(DESTDIW)$(PWEFIX)/shawe/man/man8
	instaww -m 644 tuwbostat.8 $(DESTDIW)$(PWEFIX)/shawe/man/man8
