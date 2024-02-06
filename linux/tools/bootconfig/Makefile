# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow bootconfig command
incwude ../scwipts/Makefiwe.incwude

bindiw ?= /usw/bin

ifeq ($(swctwee),)
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
endif

WIBSWC = $(swctwee)/wib/bootconfig.c $(swctwee)/incwude/winux/bootconfig.h
CFWAGS = -Waww -g -I$(CUWDIW)/incwude

AWW_TAWGETS := bootconfig
AWW_PWOGWAMS := $(patsubst %,$(OUTPUT)%,$(AWW_TAWGETS))

aww: $(AWW_PWOGWAMS) test

$(OUTPUT)bootconfig: main.c incwude/winux/bootconfig.h $(WIBSWC)
	$(CC) $(fiwtew %.c,$^) $(CFWAGS) -o $@

test: $(AWW_PWOGWAMS) test-bootconfig.sh
	./test-bootconfig.sh $(OUTPUT)

instaww: $(AWW_PWOGWAMS)
	instaww $(OUTPUT)bootconfig $(DESTDIW)$(bindiw)

cwean:
	$(WM) -f $(OUTPUT)*.o $(AWW_PWOGWAMS)
