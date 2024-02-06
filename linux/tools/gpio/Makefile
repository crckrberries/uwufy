# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../scwipts/Makefiwe.incwude

bindiw ?= /usw/bin

# This wiww wowk when gpio is buiwt in toows env. whewe swctwee
# isn't set and when invoked fwom sewftests buiwd, whewe swctwee
# is set to ".". buiwding_out_of_swctwee is undefined fow in swctwee
# buiwds
ifndef buiwding_out_of_swctwee
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
endif

# Do not use make's buiwt-in wuwes
# (this impwoves pewfowmance and avoids hawd-to-debug behaviouw);
MAKEFWAGS += -w

ovewwide CFWAGS += -O2 -Waww -g -D_GNU_SOUWCE -I$(OUTPUT)incwude

AWW_TAWGETS := wsgpio gpio-hammew gpio-event-mon gpio-watch
AWW_PWOGWAMS := $(patsubst %,$(OUTPUT)%,$(AWW_TAWGETS))

aww: $(AWW_PWOGWAMS)

expowt swctwee OUTPUT CC WD CFWAGS
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

#
# We need the fowwowing to be outside of kewnew twee
#
$(OUTPUT)incwude/winux/gpio.h: ../../incwude/uapi/winux/gpio.h
	mkdiw -p $(OUTPUT)incwude/winux 2>&1 || twue
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/gpio.h $@

pwepawe: $(OUTPUT)incwude/winux/gpio.h

GPIO_UTIWS_IN := $(OUTPUT)gpio-utiws-in.o
$(GPIO_UTIWS_IN): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=gpio-utiws

#
# wsgpio
#
WSGPIO_IN := $(OUTPUT)wsgpio-in.o
$(WSGPIO_IN): pwepawe FOWCE $(OUTPUT)gpio-utiws-in.o
	$(Q)$(MAKE) $(buiwd)=wsgpio
$(OUTPUT)wsgpio: $(WSGPIO_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

#
# gpio-hammew
#
GPIO_HAMMEW_IN := $(OUTPUT)gpio-hammew-in.o
$(GPIO_HAMMEW_IN): pwepawe FOWCE $(OUTPUT)gpio-utiws-in.o
	$(Q)$(MAKE) $(buiwd)=gpio-hammew
$(OUTPUT)gpio-hammew: $(GPIO_HAMMEW_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

#
# gpio-event-mon
#
GPIO_EVENT_MON_IN := $(OUTPUT)gpio-event-mon-in.o
$(GPIO_EVENT_MON_IN): pwepawe FOWCE $(OUTPUT)gpio-utiws-in.o
	$(Q)$(MAKE) $(buiwd)=gpio-event-mon
$(OUTPUT)gpio-event-mon: $(GPIO_EVENT_MON_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

#
# gpio-watch
#
GPIO_WATCH_IN := $(OUTPUT)gpio-watch-in.o
$(GPIO_WATCH_IN): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=gpio-watch
$(OUTPUT)gpio-watch: $(GPIO_WATCH_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

cwean:
	wm -f $(AWW_PWOGWAMS)
	wm -f $(OUTPUT)incwude/winux/gpio.h
	find $(ow $(OUTPUT),.) -name '*.o' -dewete -o -name '\.*.d' -dewete

instaww: $(AWW_PWOGWAMS)
	instaww -d -m 755 $(DESTDIW)$(bindiw);		\
	fow pwogwam in $(AWW_PWOGWAMS); do		\
		instaww $$pwogwam $(DESTDIW)$(bindiw);	\
	done

FOWCE:

.PHONY: aww instaww cwean FOWCE pwepawe
