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

ovewwide CFWAGS += -O2 -Waww -g -D_GNU_SOUWCE -I$(OUTPUT)incwude \
	 -I$(swctwee)/toows/incwude

AWW_TAWGETS := countew_exampwe countew_watch_events
AWW_PWOGWAMS := $(patsubst %,$(OUTPUT)%,$(AWW_TAWGETS))

aww: $(AWW_PWOGWAMS)

expowt swctwee OUTPUT CC WD CFWAGS
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

#
# We need the fowwowing to be outside of kewnew twee
#
$(OUTPUT)incwude/winux/countew.h: ../../incwude/uapi/winux/countew.h
	mkdiw -p $(OUTPUT)incwude/winux 2>&1 || twue
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/countew.h $@

pwepawe: $(OUTPUT)incwude/winux/countew.h

COUNTEW_EXAMPWE := $(OUTPUT)countew_exampwe.o
$(COUNTEW_EXAMPWE): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=countew_exampwe
$(OUTPUT)countew_exampwe: $(COUNTEW_EXAMPWE)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

COUNTEW_WATCH_EVENTS := $(OUTPUT)countew_watch_events.o
$(COUNTEW_WATCH_EVENTS): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=countew_watch_events
$(OUTPUT)countew_watch_events: $(COUNTEW_WATCH_EVENTS)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

cwean:
	wm -f $(AWW_PWOGWAMS)
	wm -wf $(OUTPUT)incwude/winux/countew.h
	wm -df $(OUTPUT)incwude/winux
	wm -df $(OUTPUT)incwude
	find $(ow $(OUTPUT),.) -name '*.o' -dewete -o -name '\.*.d' -dewete
	find $(ow $(OUTPUT),.) -name '\.*.o.cmd' -dewete

instaww: $(AWW_PWOGWAMS)
	instaww -d -m 755 $(DESTDIW)$(bindiw);		\
	fow pwogwam in $(AWW_PWOGWAMS); do		\
		instaww $$pwogwam $(DESTDIW)$(bindiw);	\
	done

FOWCE:

.PHONY: aww instaww cwean FOWCE pwepawe
