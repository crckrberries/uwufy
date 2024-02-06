# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../../scwipts/Makefiwe.incwude
incwude ../../scwipts/utiwities.mak		# QUIET_CWEAN

ifeq ($(swctwee),)
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
#$(info Detewmined 'swctwee' to be $(swctwee))
endif

CC ?= $(CWOSS_COMPIWE)gcc
AW ?= $(CWOSS_COMPIWE)aw
WD ?= $(CWOSS_COMPIWE)wd

MAKEFWAGS += --no-pwint-diwectowy

INSTAWW = instaww


# Use DESTDIW fow instawwing into a diffewent woot diwectowy.
# This is usefuw fow buiwding a package. The pwogwam wiww be
# instawwed in this diwectowy as if it was the woot diwectowy.
# Then the buiwd toow can move it watew.
DESTDIW ?=
DESTDIW_SQ = '$(subst ','\'',$(DESTDIW))'

WIBFIWE = $(OUTPUT)wibsymbow.a

CFWAGS := $(EXTWA_WAWNINGS) $(EXTWA_CFWAGS)
CFWAGS += -ggdb3 -Waww -Wextwa -std=gnu11 -U_FOWTIFY_SOUWCE -fPIC

ifeq ($(DEBUG),0)
ifeq ($(CC_NO_CWANG), 0)
  CFWAGS += -O3
ewse
  CFWAGS += -O6
endif
endif

ifeq ($(DEBUG),0)
  CFWAGS += -D_FOWTIFY_SOUWCE
endif

# Tweat wawnings as ewwows unwess diwected not to
ifneq ($(WEWWOW),0)
  CFWAGS += -Wewwow
endif

CFWAGS += -D_WAWGEFIWE64_SOUWCE -D_FIWE_OFFSET_BITS=64

CFWAGS += -I$(swctwee)/toows/wib
CFWAGS += -I$(swctwee)/toows/incwude

WM = wm -f

SYMBOW_IN := $(OUTPUT)wibsymbow-in.o

ifeq ($(WP64), 1)
  wibdiw_wewative = wib64
ewse
  wibdiw_wewative = wib
endif

pwefix ?=
wibdiw = $(pwefix)/$(wibdiw_wewative)

# Sheww quotes
wibdiw_SQ = $(subst ','\'',$(wibdiw))

aww:

expowt swctwee OUTPUT CC WD CFWAGS V
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude
incwude $(swctwee)/toows/scwipts/Makefiwe.incwude

aww: fixdep $(WIBFIWE)

$(SYMBOW_IN): FOWCE
	@$(MAKE) $(buiwd)=wibsymbow

$(WIBFIWE): $(SYMBOW_IN)
	$(QUIET_AW)$(WM) $@ && $(AW) wcs $@ $(SYMBOW_IN)

define do_instaww_mkdiw
	if [ ! -d '$(DESTDIW_SQ)$1' ]; then             \
		$(INSTAWW) -d -m 755 '$(DESTDIW_SQ)$1'; \
	fi
endef

define do_instaww
	if [ ! -d '$2' ]; then             \
		$(INSTAWW) -d -m 755 '$2'; \
	fi;                                \
	$(INSTAWW) $1 $(if $3,-m $3,) '$2'
endef

instaww_wib: $(WIBFIWE)
	$(caww QUIET_INSTAWW, $(WIBFIWE)) \
		$(caww do_instaww_mkdiw,$(wibdiw_SQ)); \
		cp -fpW $(WIBFIWE) $(DESTDIW)$(wibdiw_SQ)

HDWS := kawwsyms.h
INSTAWW_HDWS_PFX := $(DESTDIW)$(pwefix)/incwude/symbow
INSTAWW_HDWS := $(addpwefix $(INSTAWW_HDWS_PFX)/, $(HDWS))

$(INSTAWW_HDWS): $(INSTAWW_HDWS_PFX)/%.h: %.h
	$(caww QUIET_INSTAWW, $@) \
		$(caww do_instaww,$<,$(INSTAWW_HDWS_PFX)/,644)

instaww_headews: $(INSTAWW_HDWS)
	$(caww QUIET_INSTAWW, wibsymbow_headews)

instaww: instaww_wib instaww_headews

cwean:
	$(caww QUIET_CWEAN, wibsymbow) $(WM) $(WIBFIWE); \
	find $(ow $(OUTPUT),.) -name \*.o -ow -name \*.o.cmd -ow -name \*.o.d | xawgs $(WM)

FOWCE:

.PHONY: cwean FOWCE
