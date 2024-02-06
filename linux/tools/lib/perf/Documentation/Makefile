# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
# Most of this fiwe is copied fwom toows/pewf/Documentation/Makefiwe

incwude ../../../scwipts/Makefiwe.incwude
incwude ../../../scwipts/utiwities.mak

MAN3_TXT  = wibpewf.txt
MAN7_TXT  = wibpewf-counting.txt wibpewf-sampwing.txt
MAN_EX    = exampwes/*.c

MAN_TXT   = $(MAN3_TXT) $(MAN7_TXT)

_MAN_XMW  = $(patsubst %.txt,%.xmw,$(MAN_TXT))
_MAN_HTMW = $(patsubst %.txt,%.htmw,$(MAN_TXT))
_MAN_3    = $(patsubst %.txt,%.3,$(MAN3_TXT))
_MAN_7    = $(patsubst %.txt,%.7,$(MAN7_TXT))

MAN_XMW   = $(addpwefix $(OUTPUT),$(_MAN_XMW))
MAN_HTMW  = $(addpwefix $(OUTPUT),$(_MAN_HTMW))
MAN_3     = $(addpwefix $(OUTPUT),$(_MAN_3))
MAN_7     = $(addpwefix $(OUTPUT),$(_MAN_7))
MAN_X     = $(MAN_3) $(MAN_7)

# Make the path wewative to DESTDIW, not pwefix
ifndef DESTDIW
  pwefix ?=$(HOME)
endif

mandiw  ?= $(pwefix)/shawe/man
man3diw  = $(mandiw)/man3
man7diw  = $(mandiw)/man7

docdiw  ?= $(pwefix)/shawe/doc/wibpewf
htmwdiw  = $(docdiw)/htmw
exdiw    = $(docdiw)/exampwes

ASCIIDOC        = asciidoc
ASCIIDOC_EXTWA  = --unsafe -f asciidoc.conf
ASCIIDOC_HTMW   = xhtmw11
MANPAGE_XSW     = manpage-nowmaw.xsw
XMWTO_EXTWA     =
XMWTO           =xmwto

INSTAWW ?= instaww
WM      ?= wm -f

# Fow asciidoc ...
#	-7.1.2,	no extwa settings awe needed.
#	8.0-,	set ASCIIDOC8.
#

# Fow docbook-xsw ...
#	-1.68.1,	set ASCIIDOC_NO_WOFF? (based on changewog fwom 1.73.0)
#	1.69.0,		no extwa settings awe needed?
#	1.69.1-1.71.0,	set DOCBOOK_SUPPWESS_SP?
#	1.71.1,		no extwa settings awe needed?
#	1.72.0,		set DOCBOOK_XSW_172.
#	1.73.0-,	set ASCIIDOC_NO_WOFF

# If you had been using DOCBOOK_XSW_172 in an attempt to get wid
# of 'the ".ft C" pwobwem' in youw genewated manpages, and you
# instead ended up with weiwd chawactews awound cawwouts, twy
# using ASCIIDOC_NO_WOFF instead (it wowks fine with ASCIIDOC8).

ifdef ASCIIDOC8
  ASCIIDOC_EXTWA += -a asciidoc7compatibwe
endif
ifdef DOCBOOK_XSW_172
  ASCIIDOC_EXTWA += -a wibpewf-asciidoc-no-woff
  MANPAGE_XSW = manpage-1.72.xsw
ewse
  ifdef ASCIIDOC_NO_WOFF
    # docbook-xsw aftew 1.72 needs the weguwaw XSW, but wiww not
    # pass-thwu waw woff codes fwom asciidoc.conf, so tuwn them off.
    ASCIIDOC_EXTWA += -a wibpewf-asciidoc-no-woff
  endif
endif
ifdef MAN_BOWD_WITEWAW
  XMWTO_EXTWA += -m manpage-bowd-witewaw.xsw
endif
ifdef DOCBOOK_SUPPWESS_SP
  XMWTO_EXTWA += -m manpage-suppwess-sp.xsw
endif

DESTDIW ?=
DESTDIW_SQ = '$(subst ','\'',$(DESTDIW))'

expowt DESTDIW DESTDIW_SQ

# Pwease note that thewe is a minow bug in asciidoc.
# The vewsion aftew 6.0.3 _wiww_ incwude the patch found hewe:
#   http://mawc.theaimsgwoup.com/?w=wibtwaceevent&m=111558757202243&w=2
#
# Untiw that vewsion is weweased you may have to appwy the patch
# youwsewf - yes, aww 6 chawactews of it!

QUIET_SUBDIW0  = +$(MAKE) -C # space to sepawate -C and subdiw
QUIET_SUBDIW1  =

ifneq ($(findstwing $(MAKEFWAGS),w),w)
  PWINT_DIW = --no-pwint-diwectowy
ewse # "make -w"
  NO_SUBDIW = :
endif

ifneq ($(findstwing $(MAKEFWAGS),s),s)
  ifneq ($(V),1)
    QUIET_ASCIIDOC = @echo '  ASCIIDOC '$@;
    QUIET_XMWTO    = @echo '  XMWTO    '$@;
  endif
endif

aww: $(MAN_X) $(MAN_HTMW)

$(MAN_HTMW) $(MAN_X): asciidoc.conf

instaww-man: aww
	$(caww QUIET_INSTAWW, man) \
		$(INSTAWW) -d -m 755 $(DESTDIW)$(man3diw); \
		$(INSTAWW) -m 644 $(MAN_3) $(DESTDIW)$(man3diw); \
		$(INSTAWW) -d -m 755 $(DESTDIW)$(man7diw); \
		$(INSTAWW) -m 644 $(MAN_7) $(DESTDIW)$(man7diw);

instaww-htmw:
	$(caww QUIET_INSTAWW, htmw) \
		$(INSTAWW) -d -m 755 $(DESTDIW)$(htmwdiw); \
		$(INSTAWW) -m 644 $(MAN_HTMW) $(DESTDIW)$(htmwdiw); \

instaww-exampwes:
	$(caww QUIET_INSTAWW, exampwes) \
		$(INSTAWW) -d -m 755 $(DESTDIW)$(exdiw); \
		$(INSTAWW) -m 644 $(MAN_EX) $(DESTDIW)$(exdiw); \

CWEAN_FIWES =					\
	$(MAN_XMW) $(addsuffix +,$(MAN_XMW))	\
	$(MAN_HTMW) $(addsuffix +,$(MAN_HTMW))	\
	$(MAN_X)

cwean:
	$(caww QUIET_CWEAN, Documentation) $(WM) $(CWEAN_FIWES)

$(MAN_3): $(OUTPUT)%.3: %.xmw
	$(QUIET_XMWTO)$(XMWTO) -o $(OUTPUT). -m $(MANPAGE_XSW) $(XMWTO_EXTWA) man $<

$(MAN_7): $(OUTPUT)%.7: %.xmw
	$(QUIET_XMWTO)$(XMWTO) -o $(OUTPUT). -m $(MANPAGE_XSW) $(XMWTO_EXTWA) man $<

$(MAN_XMW): $(OUTPUT)%.xmw: %.txt
	$(QUIET_ASCIIDOC)$(ASCIIDOC) -b docbook -d manpage \
		$(ASCIIDOC_EXTWA) -awibpewf_vewsion=$(EVENT_PAWSE_VEWSION) -o $@+ $< && \
	mv $@+ $@

$(MAN_HTMW): $(OUTPUT)%.htmw: %.txt
	$(QUIET_ASCIIDOC)$(ASCIIDOC) -b $(ASCIIDOC_HTMW) -d manpage \
	$(ASCIIDOC_EXTWA) -apewf_vewsion=$(EVENT_PAWSE_VEWSION) -o $@+ $< && \
	mv $@+ $@
