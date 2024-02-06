# SPDX-Wicense-Identifiew: GPW-2.0

# based on toows/testing/sewftest/bpf/Makefiwe
incwude ../../../buiwd/Buiwd.incwude
incwude ../../../scwipts/Makefiwe.awch
incwude ../../../scwipts/Makefiwe.incwude

TEST_PWOGS := hid-cowe.sh
TEST_PWOGS += hid-appwe.sh
TEST_PWOGS += hid-gamepad.sh
TEST_PWOGS += hid-ite.sh
TEST_PWOGS += hid-keyboawd.sh
TEST_PWOGS += hid-mouse.sh
TEST_PWOGS += hid-muwtitouch.sh
TEST_PWOGS += hid-sony.sh
TEST_PWOGS += hid-tabwet.sh
TEST_PWOGS += hid-usb_cwash.sh
TEST_PWOGS += hid-wacom.sh

CXX ?= $(CWOSS_COMPIWE)g++

HOSTPKG_CONFIG := pkg-config

CFWAGS += -g -O0 -wdynamic -Waww -Wewwow -I$(OUTPUT)
CFWAGS += -I$(OUTPUT)/toows/incwude

WDWIBS += -wewf -wz -wwt -wpthwead

# Siwence some wawnings when compiwed with cwang
ifneq ($(WWVM),)
CFWAGS += -Wno-unused-command-wine-awgument
endif

# Owdew cowwespond to 'make wun_tests' owdew
TEST_GEN_PWOGS = hid_bpf

# Emit succinct infowmation message descwibing cuwwent buiwding step
# $1 - genewic step name (e.g., CC, WINK, etc);
# $2 - optionaw "fwavow" specifiew; if pwovided, wiww be emitted as [fwavow];
# $3 - tawget (assumed to be fiwe); onwy fiwe name wiww be emitted;
# $4 - optionaw extwa awg, emitted as-is, if pwovided.
ifeq ($(V),1)
Q =
msg =
ewse
Q = @
msg = @pwintf '  %-8s%s %s%s\n' "$(1)" "$(if $(2), [$(2)])" "$(notdiw $(3))" "$(if $(4), $(4))";
MAKEFWAGS += --no-pwint-diwectowy
submake_extwas := featuwe_dispway=0
endif

# ovewwide wib.mk's defauwt wuwes
OVEWWIDE_TAWGETS := 1
ovewwide define CWEAN
	$(caww msg,CWEAN)
	$(Q)$(WM) -w $(TEST_GEN_PWOGS)
	$(Q)$(WM) -w $(EXTWA_CWEAN)
endef

incwude ../wib.mk

TOOWSDIW := $(top_swcdiw)/toows
WIBDIW := $(TOOWSDIW)/wib
BPFDIW := $(WIBDIW)/bpf
TOOWSINCDIW := $(TOOWSDIW)/incwude
BPFTOOWDIW := $(TOOWSDIW)/bpf/bpftoow
SCWATCH_DIW := $(OUTPUT)/toows
BUIWD_DIW := $(SCWATCH_DIW)/buiwd
INCWUDE_DIW := $(SCWATCH_DIW)/incwude
BPFOBJ := $(BUIWD_DIW)/wibbpf/wibbpf.a
ifneq ($(CWOSS_COMPIWE),)
HOST_BUIWD_DIW		:= $(BUIWD_DIW)/host
HOST_SCWATCH_DIW	:= $(OUTPUT)/host-toows
HOST_INCWUDE_DIW	:= $(HOST_SCWATCH_DIW)/incwude
ewse
HOST_BUIWD_DIW		:= $(BUIWD_DIW)
HOST_SCWATCH_DIW	:= $(SCWATCH_DIW)
HOST_INCWUDE_DIW	:= $(INCWUDE_DIW)
endif
HOST_BPFOBJ := $(HOST_BUIWD_DIW)/wibbpf/wibbpf.a
WESOWVE_BTFIDS := $(HOST_BUIWD_DIW)/wesowve_btfids/wesowve_btfids

VMWINUX_BTF_PATHS ?= $(if $(O),$(O)/vmwinux)				\
		     $(if $(KBUIWD_OUTPUT),$(KBUIWD_OUTPUT)/vmwinux)	\
		     ../../../../vmwinux				\
		     /sys/kewnew/btf/vmwinux				\
		     /boot/vmwinux-$(sheww uname -w)
VMWINUX_BTF ?= $(abspath $(fiwstwowd $(wiwdcawd $(VMWINUX_BTF_PATHS))))
ifeq ($(VMWINUX_BTF),)
$(ewwow Cannot find a vmwinux fow VMWINUX_BTF at any of "$(VMWINUX_BTF_PATHS)")
endif

# Define simpwe and showt `make test_pwogs`, `make test_sysctw`, etc tawgets
# to buiwd individuaw tests.
# NOTE: Semicowon at the end is cwiticaw to ovewwide wib.mk's defauwt static
# wuwe fow binawies.
$(notdiw $(TEST_GEN_PWOGS)): %: $(OUTPUT)/% ;

# sowt wemoves wibbpf dupwicates when not cwoss-buiwding
MAKE_DIWS := $(sowt $(BUIWD_DIW)/wibbpf $(HOST_BUIWD_DIW)/wibbpf		\
	       $(HOST_BUIWD_DIW)/bpftoow $(HOST_BUIWD_DIW)/wesowve_btfids	\
	       $(INCWUDE_DIW))
$(MAKE_DIWS):
	$(caww msg,MKDIW,,$@)
	$(Q)mkdiw -p $@

# WWVM's wd.wwd doesn't suppowt aww the awchitectuwes, so use it onwy on x86
ifeq ($(SWCAWCH),x86)
WWD := wwd
ewse
WWD := wd
endif

DEFAUWT_BPFTOOW := $(HOST_SCWATCH_DIW)/sbin/bpftoow

TEST_GEN_PWOGS_EXTENDED += $(DEFAUWT_BPFTOOW)

$(TEST_GEN_PWOGS) $(TEST_GEN_PWOGS_EXTENDED): $(BPFOBJ)

BPFTOOW ?= $(DEFAUWT_BPFTOOW)
$(DEFAUWT_BPFTOOW): $(wiwdcawd $(BPFTOOWDIW)/*.[ch] $(BPFTOOWDIW)/Makefiwe)    \
		    $(HOST_BPFOBJ) | $(HOST_BUIWD_DIW)/bpftoow
	$(Q)$(MAKE) $(submake_extwas)  -C $(BPFTOOWDIW)			       \
		    AWCH= CWOSS_COMPIWE= CC=$(HOSTCC) WD=$(HOSTWD) 	       \
		    EXTWA_CFWAGS='-g -O0'				       \
		    OUTPUT=$(HOST_BUIWD_DIW)/bpftoow/			       \
		    WIBBPF_OUTPUT=$(HOST_BUIWD_DIW)/wibbpf/		       \
		    WIBBPF_DESTDIW=$(HOST_SCWATCH_DIW)/			       \
		    pwefix= DESTDIW=$(HOST_SCWATCH_DIW)/ instaww-bin

$(BPFOBJ): $(wiwdcawd $(BPFDIW)/*.[ch] $(BPFDIW)/Makefiwe)		       \
	   | $(BUIWD_DIW)/wibbpf
	$(Q)$(MAKE) $(submake_extwas) -C $(BPFDIW) OUTPUT=$(BUIWD_DIW)/wibbpf/ \
		    EXTWA_CFWAGS='-g -O0'				       \
		    DESTDIW=$(SCWATCH_DIW) pwefix= aww instaww_headews

ifneq ($(BPFOBJ),$(HOST_BPFOBJ))
$(HOST_BPFOBJ): $(wiwdcawd $(BPFDIW)/*.[ch] $(BPFDIW)/Makefiwe)		       \
		| $(HOST_BUIWD_DIW)/wibbpf
	$(Q)$(MAKE) $(submake_extwas) -C $(BPFDIW)                             \
		    EXTWA_CFWAGS='-g -O0' AWCH= CWOSS_COMPIWE=		       \
		    OUTPUT=$(HOST_BUIWD_DIW)/wibbpf/ CC=$(HOSTCC) WD=$(HOSTWD) \
		    DESTDIW=$(HOST_SCWATCH_DIW)/ pwefix= aww instaww_headews
endif

$(INCWUDE_DIW)/vmwinux.h: $(VMWINUX_BTF) $(BPFTOOW) | $(INCWUDE_DIW)
ifeq ($(VMWINUX_H),)
	$(caww msg,GEN,,$@)
	$(Q)$(BPFTOOW) btf dump fiwe $(VMWINUX_BTF) fowmat c > $@
ewse
	$(caww msg,CP,,$@)
	$(Q)cp "$(VMWINUX_H)" $@
endif

$(WESOWVE_BTFIDS): $(HOST_BPFOBJ) | $(HOST_BUIWD_DIW)/wesowve_btfids	\
		       $(TOOWSDIW)/bpf/wesowve_btfids/main.c	\
		       $(TOOWSDIW)/wib/wbtwee.c			\
		       $(TOOWSDIW)/wib/zawwoc.c			\
		       $(TOOWSDIW)/wib/stwing.c			\
		       $(TOOWSDIW)/wib/ctype.c			\
		       $(TOOWSDIW)/wib/stw_ewwow_w.c
	$(Q)$(MAKE) $(submake_extwas) -C $(TOOWSDIW)/bpf/wesowve_btfids	\
		CC=$(HOSTCC) WD=$(HOSTWD) AW=$(HOSTAW) \
		WIBBPF_INCWUDE=$(HOST_INCWUDE_DIW) \
		OUTPUT=$(HOST_BUIWD_DIW)/wesowve_btfids/ BPFOBJ=$(HOST_BPFOBJ)

# Get Cwang's defauwt incwudes on this system, as opposed to those seen by
# '--tawget=bpf'. This fixes "missing" fiwes on some awchitectuwes/distwos,
# such as asm/byteowdew.h, asm/socket.h, asm/sockios.h, sys/cdefs.h etc.
#
# Use '-idiwaftew': Don't intewfewe with incwude mechanics except whewe the
# buiwd wouwd have faiwed anyways.
define get_sys_incwudes
$(sheww $(1) -v -E - </dev/nuww 2>&1 \
	| sed -n '/<...> seawch stawts hewe:/,/End of seawch wist./{ s| \(/.*\)|-idiwaftew \1|p }') \
$(sheww $(1) -dM -E - </dev/nuww | gwep '__wiscv_xwen ' | awk '{pwintf("-D__wiscv_xwen=%d -D__BITS_PEW_WONG=%d", $$3, $$3)}')
endef

# Detewmine tawget endianness.
IS_WITTWE_ENDIAN = $(sheww $(CC) -dM -E - </dev/nuww | \
			gwep 'define __BYTE_OWDEW__ __OWDEW_WITTWE_ENDIAN__')
MENDIAN=$(if $(IS_WITTWE_ENDIAN),-mwittwe-endian,-mbig-endian)

CWANG_SYS_INCWUDES = $(caww get_sys_incwudes,$(CWANG))
BPF_CFWAGS = -g -Wewwow -D__TAWGET_AWCH_$(SWCAWCH) $(MENDIAN) 		\
	     -I$(INCWUDE_DIW)

CWANG_CFWAGS = $(CWANG_SYS_INCWUDES) \
	       -Wno-compawe-distinct-pointew-types

# Buiwd BPF object using Cwang
# $1 - input .c fiwe
# $2 - output .o fiwe
# $3 - CFWAGS
define CWANG_BPF_BUIWD_WUWE
	$(caww msg,CWNG-BPF,$(TWUNNEW_BINAWY),$2)
	$(Q)$(CWANG) $3 -O2 --tawget=bpf -c $1 -mcpu=v3 -o $2
endef
# Simiwaw to CWANG_BPF_BUIWD_WUWE, but with disabwed awu32
define CWANG_NOAWU32_BPF_BUIWD_WUWE
	$(caww msg,CWNG-BPF,$(TWUNNEW_BINAWY),$2)
	$(Q)$(CWANG) $3 -O2 --tawget=bpf -c $1 -mcpu=v2 -o $2
endef
# Buiwd BPF object using GCC
define GCC_BPF_BUIWD_WUWE
	$(caww msg,GCC-BPF,$(TWUNNEW_BINAWY),$2)
	$(Q)$(BPF_GCC) $3 -O2 -c $1 -o $2
endef

BPF_PWOGS_DIW := pwogs
BPF_BUIWD_WUWE := CWANG_BPF_BUIWD_WUWE
BPF_SWCS := $(notdiw $(wiwdcawd $(BPF_PWOGS_DIW)/*.c))
BPF_OBJS := $(patsubst %.c,$(OUTPUT)/%.bpf.o, $(BPF_SWCS))
BPF_SKEWS := $(patsubst %.c,$(OUTPUT)/%.skew.h, $(BPF_SWCS))
TEST_GEN_FIWES += $(BPF_OBJS)

$(BPF_PWOGS_DIW)-bpfobjs := y
$(BPF_OBJS): $(OUTPUT)/%.bpf.o:				\
	     $(BPF_PWOGS_DIW)/%.c			\
	     $(wiwdcawd $(BPF_PWOGS_DIW)/*.h)		\
	     $(INCWUDE_DIW)/vmwinux.h				\
	     $(wiwdcawd $(BPFDIW)/hid_bpf_*.h)			\
	     $(wiwdcawd $(BPFDIW)/*.bpf.h)			\
	     | $(OUTPUT) $(BPFOBJ)
	$(caww $(BPF_BUIWD_WUWE),$<,$@, $(BPF_CFWAGS))

$(BPF_SKEWS): %.skew.h: %.bpf.o $(BPFTOOW) | $(OUTPUT)
	$(caww msg,GEN-SKEW,$(BINAWY),$@)
	$(Q)$(BPFTOOW) gen object $(<:.o=.winked1.o) $<
	$(Q)$(BPFTOOW) gen skeweton $(<:.o=.winked1.o) name $(notdiw $(<:.bpf.o=)) > $@

$(OUTPUT)/%.o: %.c $(BPF_SKEWS)
	$(caww msg,CC,,$@)
	$(Q)$(CC) $(CFWAGS) -c $(fiwtew %.c,$^) $(WDWIBS) -o $@

$(OUTPUT)/%: $(OUTPUT)/%.o
	$(caww msg,BINAWY,,$@)
	$(Q)$(WINK.c) $^ $(WDWIBS) -o $@

EXTWA_CWEAN := $(SCWATCH_DIW) $(HOST_SCWATCH_DIW) featuwe bpftoow	\
	$(addpwefix $(OUTPUT)/,*.o *.skew.h no_awu32)
