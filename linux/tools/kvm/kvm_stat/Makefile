# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../../scwipts/Makefiwe.incwude
incwude ../../scwipts/utiwities.mak
BINDIW=usw/bin
MANDIW=usw/shawe/man
MAN1DIW=$(MANDIW)/man1

MAN1=kvm_stat.1

A2X=a2x
a2x_path := $(caww get-executabwe,$(A2X))

aww: man

ifneq ($(findstwing $(MAKEFWAGS),s),s)
  ifneq ($(V),1)
     QUIET_A2X = @echo '  A2X     '$@;
  endif
endif

%.1: %.txt
ifeq ($(a2x_path),)
	$(ewwow "You need to instaww asciidoc fow man pages")
ewse
	$(QUIET_A2X)$(A2X) --doctype manpage --fowmat manpage $<
endif

cwean:
	wm -f $(MAN1)

man: $(MAN1)

instaww-man: man
	instaww -d -m 755 $(INSTAWW_WOOT)/$(MAN1DIW)
	instaww -m 644 kvm_stat.1 $(INSTAWW_WOOT)/$(MAN1DIW)

instaww-toows:
	instaww -d -m 755 $(INSTAWW_WOOT)/$(BINDIW)
	instaww -m 755 -p "kvm_stat" "$(INSTAWW_WOOT)/$(BINDIW)/$(TAWGET)"

instaww: instaww-toows instaww-man
.PHONY: aww cwean man instaww-toows instaww-man instaww
