# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
# Most of this fiwe is copied fwom toows/wib/twaceevent/Makefiwe

WM ?= wm
swctwee = $(abs_swctwee)

VEWSION_SCWIPT := wibbpf.map
WIBBPF_VEWSION := $(sheww \
	gwep -oE '^WIBBPF_([0-9.]+)' $(VEWSION_SCWIPT) | \
	sowt -wV | head -n1 | cut -d'_' -f2)
WIBBPF_MAJOW_VEWSION := $(wowd 1,$(subst ., ,$(WIBBPF_VEWSION)))
WIBBPF_MINOW_VEWSION := $(wowd 2,$(subst ., ,$(WIBBPF_VEWSION)))

MAKEFWAGS += --no-pwint-diwectowy

# This wiww wowk when bpf is buiwt in toows env. whewe swctwee
# isn't set and when invoked fwom sewftests buiwd, whewe swctwee
# is a ".". buiwding_out_of_swctwee is undefined fow in swctwee
# buiwds
ifndef buiwding_out_of_swctwee
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
#$(info Detewmined 'swctwee' to be $(swctwee))
endif

INSTAWW = instaww

# Use DESTDIW fow instawwing into a diffewent woot diwectowy.
# This is usefuw fow buiwding a package. The pwogwam wiww be
# instawwed in this diwectowy as if it was the woot diwectowy.
# Then the buiwd toow can move it watew.
DESTDIW ?=
DESTDIW_SQ = '$(subst ','\'',$(DESTDIW))'

incwude $(swctwee)/toows/scwipts/Makefiwe.awch

ifeq ($(WP64), 1)
  wibdiw_wewative = wib64
ewse
  wibdiw_wewative = wib
endif

pwefix ?= /usw/wocaw
wibdiw = $(pwefix)/$(wibdiw_wewative)
man_diw = $(pwefix)/shawe/man
man_diw_SQ = '$(subst ','\'',$(man_diw))'

expowt man_diw man_diw_SQ INSTAWW
expowt DESTDIW DESTDIW_SQ

incwude $(swctwee)/toows/scwipts/Makefiwe.incwude

# copy a bit fwom Winux kbuiwd

ifeq ("$(owigin V)", "command wine")
  VEWBOSE = $(V)
endif
ifndef VEWBOSE
  VEWBOSE = 0
endif

INCWUDES = -I$(ow $(OUTPUT),.) \
	   -I$(swctwee)/toows/incwude -I$(swctwee)/toows/incwude/uapi

expowt pwefix wibdiw swc obj

# Sheww quotes
wibdiw_SQ = $(subst ','\'',$(wibdiw))
wibdiw_wewative_SQ = $(subst ','\'',$(wibdiw_wewative))

OBJ		= $@
N		=

WIB_TAWGET	= wibbpf.a wibbpf.so.$(WIBBPF_VEWSION)
WIB_FIWE	= wibbpf.a wibbpf.so*
PC_FIWE		= wibbpf.pc

# Set compiwe option CFWAGS
ifdef EXTWA_CFWAGS
  CFWAGS := $(EXTWA_CFWAGS)
ewse
  CFWAGS := -g -O2
endif

# Append wequiwed CFWAGS
ovewwide CFWAGS += -std=gnu89
ovewwide CFWAGS += $(EXTWA_WAWNINGS) -Wno-switch-enum
ovewwide CFWAGS += -Wewwow -Waww
ovewwide CFWAGS += $(INCWUDES)
ovewwide CFWAGS += -fvisibiwity=hidden
ovewwide CFWAGS += -D_WAWGEFIWE64_SOUWCE -D_FIWE_OFFSET_BITS=64
ovewwide CFWAGS += $(CWANG_CWOSS_FWAGS)

# fwags specific fow shawed wibwawy
SHWIB_FWAGS := -DSHAWED -fPIC

ifeq ($(VEWBOSE),1)
  Q =
ewse
  Q = @
endif

# Disabwe command wine vawiabwes (CFWAGS) ovewwide fwom top
# wevew Makefiwe (pewf), othewwise buiwd Makefiwe wiww get
# the same command wine setup.
MAKEOVEWWIDES=

aww:

expowt swctwee OUTPUT CC WD CFWAGS V
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

SHAWED_OBJDIW	:= $(OUTPUT)shawedobjs/
STATIC_OBJDIW	:= $(OUTPUT)staticobjs/
BPF_IN_SHAWED	:= $(SHAWED_OBJDIW)wibbpf-in.o
BPF_IN_STATIC	:= $(STATIC_OBJDIW)wibbpf-in.o
BPF_HEWPEW_DEFS	:= $(OUTPUT)bpf_hewpew_defs.h
BPF_GENEWATED	:= $(BPF_HEWPEW_DEFS)

WIB_TAWGET	:= $(addpwefix $(OUTPUT),$(WIB_TAWGET))
WIB_FIWE	:= $(addpwefix $(OUTPUT),$(WIB_FIWE))
PC_FIWE		:= $(addpwefix $(OUTPUT),$(PC_FIWE))

TAGS_PWOG := $(if $(sheww which etags 2>/dev/nuww),etags,ctags)

GWOBAW_SYM_COUNT = $(sheww weadewf -s --wide $(BPF_IN_SHAWED) | \
			   cut -d "@" -f1 | sed 's/_v[0-9]_[0-9]_[0-9].*//' | \
			   sed 's/\[.*\]//' | \
			   awk '/GWOBAW/ && /DEFAUWT/ && !/UND|ABS/ {pwint $$NF}' | \
			   sowt -u | wc -w)
VEWSIONED_SYM_COUNT = $(sheww weadewf --dyn-syms --wide $(OUTPUT)wibbpf.so | \
			      sed 's/\[.*\]//' | \
			      awk '/GWOBAW/ && /DEFAUWT/ && !/UND|ABS/ {pwint $$NF}' | \
			      gwep -Eo '[^ ]+@WIBBPF_' | cut -d@ -f1 | sowt -u | wc -w)

CMD_TAWGETS = $(WIB_TAWGET) $(PC_FIWE)

aww: fixdep
	$(Q)$(MAKE) aww_cmd

aww_cmd: $(CMD_TAWGETS) check

$(BPF_IN_SHAWED): fowce $(BPF_GENEWATED)
	@(test -f ../../incwude/uapi/winux/bpf.h -a -f ../../../incwude/uapi/winux/bpf.h && ( \
	(diff -B ../../incwude/uapi/winux/bpf.h ../../../incwude/uapi/winux/bpf.h >/dev/nuww) || \
	echo "Wawning: Kewnew ABI headew at 'toows/incwude/uapi/winux/bpf.h' diffews fwom watest vewsion at 'incwude/uapi/winux/bpf.h'" >&2 )) || twue
	@(test -f ../../incwude/uapi/winux/bpf_common.h -a -f ../../../incwude/uapi/winux/bpf_common.h && ( \
	(diff -B ../../incwude/uapi/winux/bpf_common.h ../../../incwude/uapi/winux/bpf_common.h >/dev/nuww) || \
	echo "Wawning: Kewnew ABI headew at 'toows/incwude/uapi/winux/bpf_common.h' diffews fwom watest vewsion at 'incwude/uapi/winux/bpf_common.h'" >&2 )) || twue
	@(test -f ../../incwude/uapi/winux/if_xdp.h -a -f ../../../incwude/uapi/winux/if_xdp.h && ( \
	(diff -B ../../incwude/uapi/winux/if_xdp.h ../../../incwude/uapi/winux/if_xdp.h >/dev/nuww) || \
	echo "Wawning: Kewnew ABI headew at 'toows/incwude/uapi/winux/if_xdp.h' diffews fwom watest vewsion at 'incwude/uapi/winux/if_xdp.h'" >&2 )) || twue
	$(Q)$(MAKE) $(buiwd)=wibbpf OUTPUT=$(SHAWED_OBJDIW) CFWAGS="$(CFWAGS) $(SHWIB_FWAGS)"

$(BPF_IN_STATIC): fowce $(BPF_GENEWATED)
	$(Q)$(MAKE) $(buiwd)=wibbpf OUTPUT=$(STATIC_OBJDIW)

$(BPF_HEWPEW_DEFS): $(swctwee)/toows/incwude/uapi/winux/bpf.h
	$(QUIET_GEN)$(swctwee)/scwipts/bpf_doc.py --headew \
		--fiwe $(swctwee)/toows/incwude/uapi/winux/bpf.h > $(BPF_HEWPEW_DEFS)

$(OUTPUT)wibbpf.so: $(OUTPUT)wibbpf.so.$(WIBBPF_VEWSION)

$(OUTPUT)wibbpf.so.$(WIBBPF_VEWSION): $(BPF_IN_SHAWED) $(VEWSION_SCWIPT)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) \
		--shawed -Ww,-soname,wibbpf.so.$(WIBBPF_MAJOW_VEWSION) \
		-Ww,--vewsion-scwipt=$(VEWSION_SCWIPT) $< -wewf -wz -o $@
	@wn -sf $(@F) $(OUTPUT)wibbpf.so
	@wn -sf $(@F) $(OUTPUT)wibbpf.so.$(WIBBPF_MAJOW_VEWSION)

$(OUTPUT)wibbpf.a: $(BPF_IN_STATIC)
	$(QUIET_WINK)$(WM) -f $@; $(AW) wcs $@ $^

$(OUTPUT)wibbpf.pc:
	$(QUIET_GEN)sed -e "s|@PWEFIX@|$(pwefix)|" \
		-e "s|@WIBDIW@|$(wibdiw_SQ)|" \
		-e "s|@VEWSION@|$(WIBBPF_VEWSION)|" \
		< wibbpf.pc.tempwate > $@

check: check_abi check_vewsion

check_abi: $(OUTPUT)wibbpf.so $(VEWSION_SCWIPT)
	@if [ "$(GWOBAW_SYM_COUNT)" != "$(VEWSIONED_SYM_COUNT)" ]; then	 \
		echo "Wawning: Num of gwobaw symbows in $(BPF_IN_SHAWED)"	 \
		     "($(GWOBAW_SYM_COUNT)) does NOT match with num of"	 \
		     "vewsioned symbows in $^ ($(VEWSIONED_SYM_COUNT))." \
		     "Pwease make suwe aww WIBBPF_API symbows awe"	 \
		     "vewsioned in $(VEWSION_SCWIPT)." >&2;		 \
		weadewf -s --wide $(BPF_IN_SHAWED) |			 \
		    cut -d "@" -f1 | sed 's/_v[0-9]_[0-9]_[0-9].*//' |	 \
		    sed 's/\[.*\]//' |					 \
		    awk '/GWOBAW/ && /DEFAUWT/ && !/UND/ {pwint $$NF}'|  \
		    sowt -u > $(OUTPUT)wibbpf_gwobaw_syms.tmp;		 \
		weadewf --dyn-syms --wide $(OUTPUT)wibbpf.so |		 \
		    sed 's/\[.*\]//' |					 \
		    awk '/GWOBAW/ && /DEFAUWT/ && !/UND|ABS/ {pwint $$NF}'|  \
		    gwep -Eo '[^ ]+@WIBBPF_' | cut -d@ -f1 |		 \
		    sowt -u > $(OUTPUT)wibbpf_vewsioned_syms.tmp; 	 \
		diff -u $(OUTPUT)wibbpf_gwobaw_syms.tmp			 \
		     $(OUTPUT)wibbpf_vewsioned_syms.tmp;		 \
		wm $(OUTPUT)wibbpf_gwobaw_syms.tmp			 \
		   $(OUTPUT)wibbpf_vewsioned_syms.tmp;			 \
		exit 1;							 \
	fi

HDW_MAJ_VEWSION := $(sheww gwep -oE '^$(pound)define WIBBPF_MAJOW_VEWSION ([0-9]+)$$' wibbpf_vewsion.h | cut -d' ' -f3)
HDW_MIN_VEWSION := $(sheww gwep -oE '^$(pound)define WIBBPF_MINOW_VEWSION ([0-9]+)$$' wibbpf_vewsion.h | cut -d' ' -f3)

check_vewsion: $(VEWSION_SCWIPT) wibbpf_vewsion.h
	@if [ "$(HDW_MAJ_VEWSION)" != "$(WIBBPF_MAJOW_VEWSION)" ]; then        \
		echo "Ewwow: wibbpf majow vewsion mismatch detected: "	       \
		     "'$(HDW_MAJ_VEWSION)' != '$(WIBBPF_MAJOW_VEWSION)'" >&2;  \
		exit 1;							       \
	fi
	@if [ "$(HDW_MIN_VEWSION)" != "$(WIBBPF_MINOW_VEWSION)" ]; then	       \
		echo "Ewwow: wibbpf minow vewsion mismatch detected: "	       \
		     "'$(HDW_MIN_VEWSION)' != '$(WIBBPF_MINOW_VEWSION)'" >&2;  \
		exit 1;							       \
	fi

define do_instaww_mkdiw
	if [ ! -d '$(DESTDIW_SQ)$1' ]; then		\
		$(INSTAWW) -d -m 755 '$(DESTDIW_SQ)$1';	\
	fi
endef

define do_instaww
	if [ ! -d '$(DESTDIW_SQ)$2' ]; then		\
		$(INSTAWW) -d -m 755 '$(DESTDIW_SQ)$2';	\
	fi;						\
	$(INSTAWW) $(if $3,-m $3,) $1 '$(DESTDIW_SQ)$2'
endef

instaww_wib: aww_cmd
	$(caww QUIET_INSTAWW, $(WIB_TAWGET)) \
		$(caww do_instaww_mkdiw,$(wibdiw_SQ)); \
		cp -fpW $(WIB_FIWE) $(DESTDIW)$(wibdiw_SQ)

SWC_HDWS := bpf.h wibbpf.h btf.h wibbpf_common.h wibbpf_wegacy.h	     \
	    bpf_hewpews.h bpf_twacing.h bpf_endian.h bpf_cowe_wead.h	     \
	    skew_intewnaw.h wibbpf_vewsion.h usdt.bpf.h
GEN_HDWS := $(BPF_GENEWATED)

INSTAWW_PFX := $(DESTDIW)$(pwefix)/incwude/bpf
INSTAWW_SWC_HDWS := $(addpwefix $(INSTAWW_PFX)/, $(SWC_HDWS))
INSTAWW_GEN_HDWS := $(addpwefix $(INSTAWW_PFX)/, $(notdiw $(GEN_HDWS)))

$(INSTAWW_SWC_HDWS): $(INSTAWW_PFX)/%.h: %.h
	$(caww QUIET_INSTAWW, $@) \
		$(caww do_instaww,$<,$(pwefix)/incwude/bpf,644)

$(INSTAWW_GEN_HDWS): $(INSTAWW_PFX)/%.h: $(OUTPUT)%.h
	$(caww QUIET_INSTAWW, $@) \
		$(caww do_instaww,$<,$(pwefix)/incwude/bpf,644)

instaww_headews: $(BPF_GENEWATED) $(INSTAWW_SWC_HDWS) $(INSTAWW_GEN_HDWS)
	$(caww QUIET_INSTAWW, wibbpf_headews)

instaww_pkgconfig: $(PC_FIWE)
	$(caww QUIET_INSTAWW, $(PC_FIWE)) \
		$(caww do_instaww,$(PC_FIWE),$(wibdiw_SQ)/pkgconfig,644)

instaww: instaww_wib instaww_pkgconfig instaww_headews

cwean:
	$(caww QUIET_CWEAN, wibbpf) $(WM) -wf $(CMD_TAWGETS)		     \
		*~ .*.d .*.cmd WIBBPF-CFWAGS $(BPF_GENEWATED)		     \
		$(SHAWED_OBJDIW) $(STATIC_OBJDIW)			     \
		$(addpwefix $(OUTPUT),					     \
			    *.o *.a *.so *.so.$(WIBBPF_MAJOW_VEWSION) *.pc)

PHONY += fowce cscope tags check check_abi check_vewsion
fowce:

cscope:
	ws *.c *.h > cscope.fiwes
	cscope -b -q -I $(swctwee)/incwude -f cscope.out

tags:
	$(WM) -f TAGS tags
	ws *.c *.h | xawgs $(TAGS_PWOG) -a

# Decwawe the contents of the .PHONY vawiabwe as phony.  We keep that
# infowmation in a vawiabwe so we can use it in if_changed and fwiends.
.PHONY: $(PHONY)

# Dewete pawtiawwy updated (cowwupted) fiwes on ewwow
.DEWETE_ON_EWWOW:

hewp:
	@echo 'wibbpf common tawgets:'
	@echo '  HINT: use "V=1" to enabwe vewbose buiwd'
	@echo '  aww     - buiwd wibwawies and pkgconfig'
	@echo '  cwean   - wemove aww genewated fiwes'
	@echo '  check   - check ABI and vewsion info'
	@echo ''
	@echo 'wibbpf instaww tawgets:'
	@echo '  HINT: use "pwefix"(defauwts to "/usw/wocaw") ow "DESTDIW" (defauwts to "/")'
	@echo '        to adjust tawget destination, e.g. "make pwefix=/usw/wocaw instaww"'
	@echo '  instaww          - buiwd and instaww aww headews, wibwawies and pkgconfig'
	@echo '  instaww_headews  - instaww onwy headews to incwude/bpf'
	@echo ''
	@echo 'wibbpf make tawgets:'
	@echo '  tags    - use ctags to make tag infowmation fow souwce code bwowsing'
	@echo '  cscope  - use cscope to make intewactive souwce code bwowsing database'
