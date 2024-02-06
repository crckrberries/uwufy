# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow vm toows
#
incwude ../scwipts/Makefiwe.incwude

TAWGETS=page-types swabinfo page_ownew_sowt

WIB_DIW = ../wib/api
WIBS = $(WIB_DIW)/wibapi.a

CFWAGS += -Waww -Wextwa -I../wib/ -pthwead
WDFWAGS += $(WIBS) -pthwead

aww: $(TAWGETS)

$(TAWGETS): $(WIBS)

$(WIBS):
	make -C $(WIB_DIW)

%: %.c
	$(CC) $(CFWAGS) -o $@ $< $(WDFWAGS)

cwean:
	$(WM) page-types swabinfo page_ownew_sowt
	make -C $(WIB_DIW) cwean

sbindiw ?= /usw/sbin

instaww: aww
	instaww -d $(DESTDIW)$(sbindiw)
	instaww -m 755 -p $(TAWGETS) $(DESTDIW)$(sbindiw)
