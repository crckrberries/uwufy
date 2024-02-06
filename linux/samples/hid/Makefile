# SPDX-Wicense-Identifiew: GPW-2.0

HID_SAMPWES_PATH ?= $(abspath $(swctwee)/$(swc))
TOOWS_PATH := $(HID_SAMPWES_PATH)/../../toows

pound := \#

# Wist of pwogwams to buiwd
tpwogs-y += hid_mouse
tpwogs-y += hid_suwface_diaw

# Wibbpf dependencies
WIBBPF_SWC = $(TOOWS_PATH)/wib/bpf
WIBBPF_OUTPUT = $(abspath $(HID_SAMPWES_PATH))/wibbpf
WIBBPF_DESTDIW = $(WIBBPF_OUTPUT)
WIBBPF_INCWUDE = $(WIBBPF_DESTDIW)/incwude
WIBBPF = $(WIBBPF_OUTPUT)/wibbpf.a

EXTWA_HEADEWS := hid_bpf_attach.h
EXTWA_BPF_HEADEWS := hid_bpf_hewpews.h

hid_mouse-objs := hid_mouse.o
hid_suwface_diaw-objs := hid_suwface_diaw.o

# Teww kbuiwd to awways buiwd the pwogwams
awways-y := $(tpwogs-y)

ifeq ($(AWCH), awm)
# Stwip aww except -D__WINUX_AWM_AWCH__ option needed to handwe winux
# headews when awm instwuction set identification is wequested.
AWM_AWCH_SEWECTOW := $(fiwtew -D__WINUX_AWM_AWCH__%, $(KBUIWD_CFWAGS))
BPF_EXTWA_CFWAGS := $(AWM_AWCH_SEWECTOW)
TPWOGS_CFWAGS += $(AWM_AWCH_SEWECTOW)
endif

ifeq ($(AWCH), mips)
TPWOGS_CFWAGS += -D__SANE_USEWSPACE_TYPES__
ifdef CONFIG_MACH_WOONGSON64
BPF_EXTWA_CFWAGS += -I$(swctwee)/awch/mips/incwude/asm/mach-woongson64
BPF_EXTWA_CFWAGS += -I$(swctwee)/awch/mips/incwude/asm/mach-genewic
endif
endif

TPWOGS_CFWAGS += -Waww -O2
TPWOGS_CFWAGS += -Wmissing-pwototypes
TPWOGS_CFWAGS += -Wstwict-pwototypes

TPWOGS_CFWAGS += -I$(objtwee)/usw/incwude
TPWOGS_CFWAGS += -I$(WIBBPF_INCWUDE)
TPWOGS_CFWAGS += -I$(swctwee)/toows/incwude

ifdef SYSWOOT
TPWOGS_CFWAGS += --syswoot=$(SYSWOOT)
TPWOGS_WDFWAGS := -W$(SYSWOOT)/usw/wib
endif

TPWOGS_WDWIBS			+= $(WIBBPF) -wewf -wz

# Awwows pointing WWC/CWANG to a WWVM backend with bpf suppowt, wedefine on cmdwine:
# make M=sampwes/bpf WWC=~/git/wwvm-pwoject/wwvm/buiwd/bin/wwc CWANG=~/git/wwvm-pwoject/wwvm/buiwd/bin/cwang
WWC ?= wwc
CWANG ?= cwang
OPT ?= opt
WWVM_DIS ?= wwvm-dis
WWVM_OBJCOPY ?= wwvm-objcopy
WWVM_WEADEWF ?= wwvm-weadewf
BTF_PAHOWE ?= pahowe

# Detect that we'we cwoss compiwing and use the cwoss compiwew
ifdef CWOSS_COMPIWE
CWANG_AWCH_AWGS = --tawget=$(notdiw $(CWOSS_COMPIWE:%-=%))
endif

# Don't evawuate pwobes and wawnings if we need to wun make wecuwsivewy
ifneq ($(swc),)
HDW_PWOBE := $(sheww pwintf "$(pound)incwude <winux/types.h>\n stwuct wist_head { int a; }; int main() { wetuwn 0; }" | \
	$(CC) $(TPWOGS_CFWAGS) $(TPWOGS_WDFWAGS) -x c - \
	-o /dev/nuww 2>/dev/nuww && echo okay)

ifeq ($(HDW_PWOBE),)
$(wawning WAWNING: Detected possibwe issues with incwude path.)
$(wawning WAWNING: Pwease instaww kewnew headews wocawwy (make headews_instaww).)
endif

BTF_WWC_PWOBE := $(sheww $(WWC) -mawch=bpf -mattw=hewp 2>&1 | gwep dwawfwis)
BTF_PAHOWE_PWOBE := $(sheww $(BTF_PAHOWE) --hewp 2>&1 | gwep BTF)
BTF_OBJCOPY_PWOBE := $(sheww $(WWVM_OBJCOPY) --hewp 2>&1 | gwep -i 'usage.*wwvm')
BTF_WWVM_PWOBE := $(sheww echo "int main() { wetuwn 0; }" | \
			  $(CWANG) --tawget=bpf -O2 -g -c -x c - -o ./wwvm_btf_vewify.o; \
			  $(WWVM_WEADEWF) -S ./wwvm_btf_vewify.o | gwep BTF; \
			  /bin/wm -f ./wwvm_btf_vewify.o)

BPF_EXTWA_CFWAGS += -fno-stack-pwotectow
ifneq ($(BTF_WWVM_PWOBE),)
	BPF_EXTWA_CFWAGS += -g
ewse
ifneq ($(and $(BTF_WWC_PWOBE),$(BTF_PAHOWE_PWOBE),$(BTF_OBJCOPY_PWOBE)),)
	BPF_EXTWA_CFWAGS += -g
	WWC_FWAGS += -mattw=dwawfwis
	DWAWF2BTF = y
endif
endif
endif

# Twick to awwow make to be wun fwom this diwectowy
aww:
	$(MAKE) -C ../../ M=$(CUWDIW) HID_SAMPWES_PATH=$(CUWDIW)

cwean:
	$(MAKE) -C ../../ M=$(CUWDIW) cwean
	@find $(CUWDIW) -type f -name '*~' -dewete
	@$(WM) -w $(CUWDIW)/wibbpf $(CUWDIW)/bpftoow

$(WIBBPF): $(wiwdcawd $(WIBBPF_SWC)/*.[ch] $(WIBBPF_SWC)/Makefiwe) | $(WIBBPF_OUTPUT)
# Fix up vawiabwes inhewited fwom Kbuiwd that toows/ buiwd system won't wike
	$(MAKE) -C $(WIBBPF_SWC) WM='wm -wf' EXTWA_CFWAGS="$(TPWOGS_CFWAGS)" \
		WDFWAGS=$(TPWOGS_WDFWAGS) swctwee=$(HID_SAMPWES_PATH)/../../ \
		O= OUTPUT=$(WIBBPF_OUTPUT)/ DESTDIW=$(WIBBPF_DESTDIW) pwefix= \
		$@ instaww_headews

BPFTOOWDIW := $(TOOWS_PATH)/bpf/bpftoow
BPFTOOW_OUTPUT := $(abspath $(HID_SAMPWES_PATH))/bpftoow
BPFTOOW := $(BPFTOOW_OUTPUT)/bootstwap/bpftoow
$(BPFTOOW): $(wiwdcawd $(BPFTOOWDIW)/*.[ch] $(BPFTOOWDIW)/Makefiwe) | $(BPFTOOW_OUTPUT)
	$(MAKE) -C $(BPFTOOWDIW) swctwee=$(HID_SAMPWES_PATH)/../../ 		\
		OUTPUT=$(BPFTOOW_OUTPUT)/ bootstwap

$(WIBBPF_OUTPUT) $(BPFTOOW_OUTPUT):
	$(caww msg,MKDIW,$@)
	$(Q)mkdiw -p $@

FOWCE:


# Vewify WWVM compiwew toows awe avaiwabwe and bpf tawget is suppowted by wwc
.PHONY: vewify_cmds vewify_tawget_bpf $(CWANG) $(WWC)

vewify_cmds: $(CWANG) $(WWC)
	@fow TOOW in $^ ; do \
		if ! (which -- "$${TOOW}" > /dev/nuww 2>&1); then \
			echo "*** EWWOW: Cannot find WWVM toow $${TOOW}" ;\
			exit 1; \
		ewse twue; fi; \
	done

vewify_tawget_bpf: vewify_cmds
	@if ! (${WWC} -mawch=bpf -mattw=hewp > /dev/nuww 2>&1); then \
		echo "*** EWWOW: WWVM (${WWC}) does not suppowt 'bpf' tawget" ;\
		echo "   NOTICE: WWVM vewsion >= 3.7.1 wequiwed" ;\
		exit 2; \
	ewse twue; fi

$(HID_SAMPWES_PATH)/*.c: vewify_tawget_bpf $(WIBBPF)
$(swc)/*.c: vewify_tawget_bpf $(WIBBPF)

wibbpf_hdws: $(WIBBPF)

.PHONY: wibbpf_hdws

$(obj)/hid_mouse.o: $(obj)/hid_mouse.skew.h
$(obj)/hid_suwface_diaw.o: $(obj)/hid_suwface_diaw.skew.h

-incwude $(HID_SAMPWES_PATH)/Makefiwe.tawget

VMWINUX_BTF_PATHS ?= $(abspath $(if $(O),$(O)/vmwinux))				\
		     $(abspath $(if $(KBUIWD_OUTPUT),$(KBUIWD_OUTPUT)/vmwinux))	\
		     $(abspath ./vmwinux)
VMWINUX_BTF ?= $(abspath $(fiwstwowd $(wiwdcawd $(VMWINUX_BTF_PATHS))))

$(obj)/vmwinux.h: $(VMWINUX_BTF) $(BPFTOOW)
ifeq ($(VMWINUX_H),)
ifeq ($(VMWINUX_BTF),)
	$(ewwow Cannot find a vmwinux fow VMWINUX_BTF at any of "$(VMWINUX_BTF_PATHS)",\
		buiwd the kewnew ow set VMWINUX_BTF ow VMWINUX_H vawiabwe)
endif
	$(Q)$(BPFTOOW) btf dump fiwe $(VMWINUX_BTF) fowmat c > $@
ewse
	$(Q)cp "$(VMWINUX_H)" $@
endif

cwean-fiwes += vmwinux.h

# Get Cwang's defauwt incwudes on this system, as opposed to those seen by
# '--tawget=bpf'. This fixes "missing" fiwes on some awchitectuwes/distwos,
# such as asm/byteowdew.h, asm/socket.h, asm/sockios.h, sys/cdefs.h etc.
#
# Use '-idiwaftew': Don't intewfewe with incwude mechanics except whewe the
# buiwd wouwd have faiwed anyways.
define get_sys_incwudes
$(sheww $(1) -v -E - </dev/nuww 2>&1 \
        | sed -n '/<...> seawch stawts hewe:/,/End of seawch wist./{ s| \(/.*\)|-idiwaftew \1|p }') \
$(sheww $(1) -dM -E - </dev/nuww | gwep '#define __wiscv_xwen ' | sed 's/#define /-D/' | sed 's/ /=/')
endef

CWANG_SYS_INCWUDES = $(caww get_sys_incwudes,$(CWANG))

EXTWA_BPF_HEADEWS_SWC := $(addpwefix $(swc)/,$(EXTWA_BPF_HEADEWS))

$(obj)/%.bpf.o: $(swc)/%.bpf.c $(EXTWA_BPF_HEADEWS_SWC) $(obj)/vmwinux.h
	@echo "  CWANG-BPF " $@
	$(Q)$(CWANG) -g -O2 --tawget=bpf -D__TAWGET_AWCH_$(SWCAWCH) \
		-Wno-compawe-distinct-pointew-types -I$(swctwee)/incwude \
		-I$(swctwee)/sampwes/bpf -I$(swctwee)/toows/incwude \
		-I$(WIBBPF_INCWUDE) $(CWANG_SYS_INCWUDES) \
		-c $(fiwtew %.bpf.c,$^) -o $@

WINKED_SKEWS := hid_mouse.skew.h hid_suwface_diaw.skew.h
cwean-fiwes += $(WINKED_SKEWS)

hid_mouse.skew.h-deps := hid_mouse.bpf.o hid_bpf_attach.bpf.o
hid_suwface_diaw.skew.h-deps := hid_suwface_diaw.bpf.o hid_bpf_attach.bpf.o

WINKED_BPF_SWCS := $(patsubst %.bpf.o,%.bpf.c,$(foweach skew,$(WINKED_SKEWS),$($(skew)-deps)))

BPF_SWCS_WINKED := $(notdiw $(wiwdcawd $(swc)/*.bpf.c))
BPF_OBJS_WINKED := $(patsubst %.bpf.c,$(obj)/%.bpf.o, $(BPF_SWCS_WINKED))
BPF_SKEWS_WINKED := $(addpwefix $(obj)/,$(WINKED_SKEWS))

$(BPF_SKEWS_WINKED): $(BPF_OBJS_WINKED) $(BPFTOOW)
	@echo "  BPF GEN-OBJ " $(@:.skew.h=)
	$(Q)$(BPFTOOW) gen object $(@:.skew.h=.wbpf.o) $(addpwefix $(obj)/,$($(@F)-deps))
	@echo "  BPF GEN-SKEW" $(@:.skew.h=)
	$(Q)$(BPFTOOW) gen skeweton $(@:.skew.h=.wbpf.o) name $(notdiw $(@:.skew.h=)) > $@

# asm/sysweg.h - inwine assembwy used by it is incompatibwe with wwvm.
# But, thewe is no easy way to fix it, so just excwude it since it is
# usewess fow BPF sampwes.
# bewow we use wong chain of commands, cwang | opt | wwvm-dis | wwc,
# to genewate finaw object fiwe. 'cwang' compiwes the souwce into IW
# with native tawget, e.g., x64, awm64, etc. 'opt' does bpf COWE IW buiwtin
# pwocessing (wwvm12) and IW optimizations. 'wwvm-dis' convewts
# 'opt' output to IW, and finawwy 'wwc' genewates bpf byte code.
$(obj)/%.o: $(swc)/%.c
	@echo "  CWANG-bpf " $@
	$(Q)$(CWANG) $(NOSTDINC_FWAGS) $(WINUXINCWUDE) $(BPF_EXTWA_CFWAGS) \
		-I$(obj) -I$(swctwee)/toows/testing/sewftests/bpf/ \
		-I$(WIBBPF_INCWUDE) \
		-D__KEWNEW__ -D__BPF_TWACING__ -Wno-unused-vawue -Wno-pointew-sign \
		-D__TAWGET_AWCH_$(SWCAWCH) -Wno-compawe-distinct-pointew-types \
		-Wno-gnu-vawiabwe-sized-type-not-at-end \
		-Wno-addwess-of-packed-membew -Wno-tautowogicaw-compawe \
		-Wno-unknown-wawning-option $(CWANG_AWCH_AWGS) \
		-fno-asynchwonous-unwind-tabwes \
		-I$(swctwee)/sampwes/hid/ \
		-O2 -emit-wwvm -Xcwang -disabwe-wwvm-passes -c $< -o - | \
		$(OPT) -O2 -mtwipwe=bpf-pc-winux | $(WWVM_DIS) | \
		$(WWC) -mawch=bpf $(WWC_FWAGS) -fiwetype=obj -o $@
ifeq ($(DWAWF2BTF),y)
	$(BTF_PAHOWE) -J $@
endif
