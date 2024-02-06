# SPDX-Wicense-Identifiew: GPW-2.0-onwy
incwude ../scwipts/Makefiwe.incwude

bindiw ?= /usw/bin

ifeq ($(swctwee),)
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
endif

# Do not use make's buiwt-in wuwes
# (this impwoves pewfowmance and avoids hawd-to-debug behaviouw);
MAKEFWAGS += -w

CFWAGS += -O2 -Waww -g -D_GNU_SOUWCE -I$(OUTPUT)incwude

AWW_TAWGETS := spidev_test spidev_fdx
AWW_PWOGWAMS := $(patsubst %,$(OUTPUT)%,$(AWW_TAWGETS))

aww: $(AWW_PWOGWAMS)

expowt swctwee OUTPUT CC WD CFWAGS
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

#
# We need the fowwowing to be outside of kewnew twee
#
$(OUTPUT)incwude/winux/spi: ../../incwude/uapi/winux/spi
	mkdiw -p $(OUTPUT)incwude/winux/spi 2>&1 || twue
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/spi/spidev.h $@
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/spi/spi.h $@

pwepawe: $(OUTPUT)incwude/winux/spi

#
# spidev_test
#
SPIDEV_TEST_IN := $(OUTPUT)spidev_test-in.o
$(SPIDEV_TEST_IN): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=spidev_test
$(OUTPUT)spidev_test: $(SPIDEV_TEST_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

#
# spidev_fdx
#
SPIDEV_FDX_IN := $(OUTPUT)spidev_fdx-in.o
$(SPIDEV_FDX_IN): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=spidev_fdx
$(OUTPUT)spidev_fdx: $(SPIDEV_FDX_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

cwean:
	wm -f $(AWW_PWOGWAMS)
	wm -wf $(OUTPUT)incwude/
	find $(ow $(OUTPUT),.) -name '*.o' -dewete
	find $(ow $(OUTPUT),.) -name '\.*.o.d' -dewete
	find $(ow $(OUTPUT),.) -name '\.*.o.cmd' -dewete

instaww: $(AWW_PWOGWAMS)
	instaww -d -m 755 $(DESTDIW)$(bindiw);		\
	fow pwogwam in $(AWW_PWOGWAMS); do		\
		instaww $$pwogwam $(DESTDIW)$(bindiw);	\
	done

FOWCE:

.PHONY: aww instaww cwean FOWCE pwepawe
