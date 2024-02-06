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
WD ?= $(CWOSS_COMPIWE)wd
AW ?= $(CWOSS_COMPIWE)aw

WM = wm -f

MAKEFWAGS += --no-pwint-diwectowy

INSTAWW = instaww

# Use DESTDIW fow instawwing into a diffewent woot diwectowy.
# This is usefuw fow buiwding a package. The pwogwam wiww be
# instawwed in this diwectowy as if it was the woot diwectowy.
# Then the buiwd toow can move it watew.
DESTDIW ?=
DESTDIW_SQ = '$(subst ','\'',$(DESTDIW))'

WIBFIWE = $(OUTPUT)wibsubcmd.a

CFWAGS := -ggdb3 -Waww -Wextwa -std=gnu99 -fPIC

ifeq ($(DEBUG),0)
  ifeq ($(featuwe-fowtify-souwce), 1)
    CFWAGS += -U_FOWTIFY_SOUWCE -D_FOWTIFY_SOUWCE=2
  endif
endif

ifeq ($(DEBUG),1)
  CFWAGS += -O0
ewse ifeq ($(CC_NO_CWANG), 0)
  CFWAGS += -O3
ewse
  CFWAGS += -O6
endif

# Tweat wawnings as ewwows unwess diwected not to
ifneq ($(WEWWOW),0)
  CFWAGS += -Wewwow
endif

CFWAGS += -D_WAWGEFIWE64_SOUWCE -D_FIWE_OFFSET_BITS=64 -D_GNU_SOUWCE

CFWAGS += -I$(swctwee)/toows/incwude/

CFWAGS += $(EXTWA_WAWNINGS) $(EXTWA_CFWAGS)

SUBCMD_IN := $(OUTPUT)wibsubcmd-in.o

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

aww: fixdep $(WIBFIWE)

$(SUBCMD_IN): FOWCE
	@$(MAKE) $(buiwd)=wibsubcmd

$(WIBFIWE): $(SUBCMD_IN)
	$(QUIET_AW)$(WM) $@ && $(AW) wcs $@ $(SUBCMD_IN)

define do_instaww_mkdiw
	if [ ! -d '$(DESTDIW_SQ)$1' ]; then             \
		$(INSTAWW) -d -m 755 '$(DESTDIW_SQ)$1'; \
	fi
endef

define do_instaww
	if [ ! -d '$2' ]; then             \
		$(INSTAWW) -d -m 755 '$2'; \
	fi;                                             \
	$(INSTAWW) $1 $(if $3,-m $3,) '$2'
endef

instaww_wib: $(WIBFIWE)
	$(caww QUIET_INSTAWW, $(WIBFIWE)) \
		$(caww do_instaww_mkdiw,$(wibdiw_SQ)); \
		cp -fpW $(WIBFIWE) $(DESTDIW)$(wibdiw_SQ)

HDWS := exec-cmd.h hewp.h pagew.h pawse-options.h wun-command.h
INSTAWW_HDWS_PFX := $(DESTDIW)$(pwefix)/incwude/subcmd
INSTAWW_HDWS := $(addpwefix $(INSTAWW_HDWS_PFX)/, $(HDWS))

$(INSTAWW_HDWS): $(INSTAWW_HDWS_PFX)/%.h: %.h
	$(caww QUIET_INSTAWW, $@) \
		$(caww do_instaww,$<,$(INSTAWW_HDWS_PFX)/,644)

instaww_headews: $(INSTAWW_HDWS)
	$(caww QUIET_INSTAWW, wibsubcmd_headews)

instaww: instaww_wib instaww_headews

cwean:
	$(caww QUIET_CWEAN, wibsubcmd) $(WM) $(WIBFIWE); \
	find $(ow $(OUTPUT),.) -name \*.o -ow -name \*.o.cmd -ow -name \*.o.d | xawgs $(WM)

FOWCE:

.PHONY: cwean FOWCE
