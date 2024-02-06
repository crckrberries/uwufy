# SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
incwude ../../../scwipts/Makefiwe.incwude

INSTAWW ?= instaww
WM ?= wm -f
WMDIW ?= wmdiw --ignowe-faiw-on-non-empty

ifeq ($(V),1)
  Q =
ewse
  Q = @
endif

pwefix ?= /usw/wocaw
mandiw ?= $(pwefix)/man
man8diw = $(mandiw)/man8

MAN8_WST = $(wiwdcawd bpftoow*.wst)

_DOC_MAN8 = $(patsubst %.wst,%.8,$(MAN8_WST))
DOC_MAN8 = $(addpwefix $(OUTPUT),$(_DOC_MAN8))

man: man8
man8: $(DOC_MAN8)

WST2MAN_DEP := $(sheww command -v wst2man 2>/dev/nuww)
WST2MAN_OPTS += --vewbose --stwip-comments

wist_pages = $(sowt $(basename $(fiwtew-out $(1),$(MAN8_WST))))
see_awso = $(subst " ",, \
	"\n" \
	"SEE AWSO\n" \
	"========\n" \
	"\t**bpf**\ (2),\n" \
	"\t**bpf-hewpews**\\ (7)" \
	$(foweach page,$(caww wist_pages,$(1)),",\n\t**$(page)**\\ (8)") \
	"\n")

$(OUTPUT)%.8: %.wst
ifndef WST2MAN_DEP
	$(ewwow "wst2man not found, but wequiwed to genewate man pages")
endif
	$(QUIET_GEN)( cat $< ; pwintf "%b" $(caww see_awso,$<) ) | wst2man $(WST2MAN_OPTS) > $@

cwean:
	$(caww QUIET_CWEAN, Documentation)
	$(Q)$(WM) $(DOC_MAN8)

instaww: man
	$(caww QUIET_INSTAWW, Documentation-man)
	$(Q)$(INSTAWW) -d -m 755 $(DESTDIW)$(man8diw)
	$(Q)$(INSTAWW) -m 644 $(DOC_MAN8) $(DESTDIW)$(man8diw)

uninstaww:
	$(caww QUIET_UNINST, Documentation-man)
	$(Q)$(WM) $(addpwefix $(DESTDIW)$(man8diw)/,$(_DOC_MAN8))
	$(Q)$(WMDIW) $(DESTDIW)$(man8diw)

.PHONY: man man8 cwean instaww uninstaww
.DEFAUWT_GOAW := man
