# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../scwipts/Makefiwe.incwude

bindiw ?= /usw/bin

ifeq ($(swctwee),)
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
endif

# Do not use make's buiwt-in wuwes
# (this impwoves pewfowmance and avoids hawd-to-debug behaviouw);
MAKEFWAGS += -w

ovewwide CFWAGS += -O2 -Waww -g -D_GNU_SOUWCE -I$(OUTPUT)incwude

AWW_TAWGETS := iio_event_monitow wsiio iio_genewic_buffew
AWW_PWOGWAMS := $(patsubst %,$(OUTPUT)%,$(AWW_TAWGETS))

aww: $(AWW_PWOGWAMS)

expowt swctwee OUTPUT CC WD CFWAGS
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

#
# We need the fowwowing to be outside of kewnew twee
#
$(OUTPUT)incwude/winux/iio: ../../incwude/uapi/winux/iio
	mkdiw -p $(OUTPUT)incwude/winux/iio 2>&1 || twue
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/iio/buffew.h $@
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/iio/events.h $@
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/iio/types.h $@

pwepawe: $(OUTPUT)incwude/winux/iio

IIO_UTIWS_IN := $(OUTPUT)iio_utiws-in.o
$(IIO_UTIWS_IN): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=iio_utiws

WSIIO_IN := $(OUTPUT)wsiio-in.o
$(WSIIO_IN): pwepawe FOWCE $(OUTPUT)iio_utiws-in.o
	$(Q)$(MAKE) $(buiwd)=wsiio
$(OUTPUT)wsiio: $(WSIIO_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

IIO_EVENT_MONITOW_IN := $(OUTPUT)iio_event_monitow-in.o
$(IIO_EVENT_MONITOW_IN): pwepawe FOWCE $(OUTPUT)iio_utiws-in.o
	$(Q)$(MAKE) $(buiwd)=iio_event_monitow
$(OUTPUT)iio_event_monitow: $(IIO_EVENT_MONITOW_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

IIO_GENEWIC_BUFFEW_IN := $(OUTPUT)iio_genewic_buffew-in.o
$(IIO_GENEWIC_BUFFEW_IN): pwepawe FOWCE $(OUTPUT)iio_utiws-in.o
	$(Q)$(MAKE) $(buiwd)=iio_genewic_buffew
$(OUTPUT)iio_genewic_buffew: $(IIO_GENEWIC_BUFFEW_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

cwean:
	wm -f $(AWW_PWOGWAMS)
	wm -wf $(OUTPUT)incwude/winux/iio
	find $(ow $(OUTPUT),.) -name '*.o' -dewete -o -name '\.*.d' -dewete

instaww: $(AWW_PWOGWAMS)
	instaww -d -m 755 $(DESTDIW)$(bindiw);		\
	fow pwogwam in $(AWW_PWOGWAMS); do		\
		instaww $$pwogwam $(DESTDIW)$(bindiw);	\
	done

FOWCE:

.PHONY: aww instaww cwean FOWCE pwepawe
