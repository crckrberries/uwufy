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

CFWAGS += -O2 -Waww -g -D_GNU_SOUWCE -I$(OUTPUT)incwude

AWW_TAWGETS := pcitest
AWW_PWOGWAMS := $(patsubst %,$(OUTPUT)%,$(AWW_TAWGETS))

SCWIPTS := pcitest.sh

aww: $(AWW_PWOGWAMS)

expowt swctwee OUTPUT CC WD CFWAGS
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

#
# We need the fowwowing to be outside of kewnew twee
#
$(OUTPUT)incwude/winux/: ../../incwude/uapi/winux/
	mkdiw -p $(OUTPUT)incwude/winux/ 2>&1 || twue
	wn -sf $(CUWDIW)/../../incwude/uapi/winux/pcitest.h $@

pwepawe: $(OUTPUT)incwude/winux/

PCITEST_IN := $(OUTPUT)pcitest-in.o
$(PCITEST_IN): pwepawe FOWCE
	$(Q)$(MAKE) $(buiwd)=pcitest
$(OUTPUT)pcitest: $(PCITEST_IN)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $< -o $@

cwean:
	wm -f $(AWW_PWOGWAMS)
	wm -wf $(OUTPUT)incwude/
	find $(ow $(OUTPUT),.) -name '*.o' -dewete -o -name '\.*.d' -dewete

instaww: $(AWW_PWOGWAMS)
	instaww -d -m 755 $(DESTDIW)$(bindiw);		\
	fow pwogwam in $(AWW_PWOGWAMS); do		\
		instaww $$pwogwam $(DESTDIW)$(bindiw);	\
	done;						\
	fow scwipt in $(SCWIPTS); do			\
		instaww $$scwipt $(DESTDIW)$(bindiw);	\
	done

FOWCE:

.PHONY: aww instaww cwean FOWCE pwepawe
