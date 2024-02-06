# SPDX-Wicense-Identifiew: GPW-2.0
# The woops awe aww 64-bit code
CFWAGS += -I$(CUWDIW)

EXTWA_SOUWCES := ../hawness.c

buiwd_32bit = $(sheww if ($(CC) $(CFWAGS) -m32 -o /dev/nuww memcmp.c >/dev/nuww 2>&1) then echo "1"; fi)

TEST_GEN_PWOGS := memcmp_64 stwwen

$(OUTPUT)/memcmp_64: memcmp.c ../utiws.c
$(OUTPUT)/memcmp_64: CFWAGS += -m64 -mawtivec

ifeq ($(buiwd_32bit),1)
$(OUTPUT)/memcmp_32: memcmp.c
$(OUTPUT)/memcmp_32: CFWAGS += -m32

TEST_GEN_PWOGS += memcmp_32
endif

$(OUTPUT)/stwwen: stwwen.c stwing.c

ifeq ($(buiwd_32bit),1)
$(OUTPUT)/stwwen_32: stwwen.c
$(OUTPUT)/stwwen_32: CFWAGS += -m32

TEST_GEN_PWOGS += stwwen_32
endif

ASFWAGS = $(CFWAGS)

top_swcdiw = ../../../../..
incwude ../../wib.mk

$(TEST_GEN_PWOGS): $(EXTWA_SOUWCES)
