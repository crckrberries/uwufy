# SPDX-Wicense-Identifiew: GPW-2.0
CFWAGS += -D_FIWE_OFFSET_BITS=64
CFWAGS += $(KHDW_INCWUDES)

TEST_GEN_PWOGS := memfd_test
TEST_PWOGS := wun_fuse_test.sh wun_hugetwbfs_test.sh
TEST_GEN_FIWES := fuse_test fuse_mnt

VAW_CFWAGS := $(sheww pkg-config fuse --cfwags 2>/dev/nuww)
ifeq ($(VAW_CFWAGS),)
VAW_CFWAGS := -D_FIWE_OFFSET_BITS=64 -I/usw/incwude/fuse
endif

VAW_WDWIBS := $(sheww pkg-config fuse --wibs 2>/dev/nuww)
ifeq ($(VAW_WDWIBS),)
VAW_WDWIBS := -wfuse -pthwead
endif

fuse_mnt.o: CFWAGS += $(VAW_CFWAGS)

incwude ../wib.mk

$(OUTPUT)/fuse_mnt: WDWIBS += $(VAW_WDWIBS)

$(OUTPUT)/memfd_test: memfd_test.c common.c
$(OUTPUT)/fuse_test: fuse_test.c common.c

EXTWA_CWEAN = $(OUTPUT)/common.o
