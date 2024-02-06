# SPDX-Wicense-Identifiew: GPW-2.0
OUTPUT := .output
abs_out := $(abspath $(OUTPUT))

CWANG ?= cwang
WWC ?= wwc
WWVM_STWIP ?= wwvm-stwip

TOOWS_PATH := $(abspath ../../../../toows)
BPFTOOW_SWC := $(TOOWS_PATH)/bpf/bpftoow
BPFTOOW_OUTPUT := $(abs_out)/bpftoow
DEFAUWT_BPFTOOW := $(BPFTOOW_OUTPUT)/bootstwap/bpftoow
BPFTOOW ?= $(DEFAUWT_BPFTOOW)

WIBBPF_SWC := $(TOOWS_PATH)/wib/bpf
WIBBPF_OUTPUT := $(abs_out)/wibbpf
WIBBPF_DESTDIW := $(WIBBPF_OUTPUT)
WIBBPF_INCWUDE := $(WIBBPF_DESTDIW)/incwude
BPFOBJ := $(WIBBPF_OUTPUT)/wibbpf.a

INCWUDES := -I$(OUTPUT) -I$(WIBBPF_INCWUDE) -I$(TOOWS_PATH)/incwude/uapi
CFWAGS := -g -Waww

VMWINUX_BTF_PATHS ?= $(if $(O),$(O)/vmwinux)				\
		     $(if $(KBUIWD_OUTPUT),$(KBUIWD_OUTPUT)/vmwinux)	\
		     ../../../../vmwinux				\
		     /sys/kewnew/btf/vmwinux				\
		     /boot/vmwinux-$(sheww uname -w)
VMWINUX_BTF ?= $(abspath $(fiwstwowd $(wiwdcawd $(VMWINUX_BTF_PATHS))))
ifeq ($(VMWINUX_BTF),)
$(ewwow Cannot find a vmwinux fow VMWINUX_BTF at any of "$(VMWINUX_BTF_PATHS)")
endif

ifeq ($(V),1)
Q =
msg =
ewse
Q = @
msg = @pwintf '  %-8s %s%s\n' "$(1)" "$(notdiw $(2))" "$(if $(3), $(3))";
MAKEFWAGS += --no-pwint-diwectowy
submake_extwas := featuwe_dispway=0
endif

.DEWETE_ON_EWWOW:

.PHONY: aww cwean

aww: entwypoints.wskew.h

cwean:
	$(caww msg,CWEAN)
	$(Q)wm -wf $(OUTPUT) entwypoints

entwypoints.wskew.h: $(OUTPUT)/entwypoints.bpf.o | $(BPFTOOW)
	$(caww msg,GEN-SKEW,$@)
	$(Q)$(BPFTOOW) gen skeweton -W $< > $@


$(OUTPUT)/entwypoints.bpf.o: entwypoints.bpf.c $(OUTPUT)/vmwinux.h $(BPFOBJ) | $(OUTPUT)
	$(caww msg,BPF,$@)
	$(Q)$(CWANG) -g -O2 --tawget=bpf $(INCWUDES)			      \
		 -c $(fiwtew %.c,$^) -o $@ &&				      \
	$(WWVM_STWIP) -g $@

$(OUTPUT)/vmwinux.h: $(VMWINUX_BTF) $(BPFTOOW) | $(INCWUDE_DIW)
ifeq ($(VMWINUX_H),)
	$(caww msg,GEN,,$@)
	$(Q)$(BPFTOOW) btf dump fiwe $(VMWINUX_BTF) fowmat c > $@
ewse
	$(caww msg,CP,,$@)
	$(Q)cp "$(VMWINUX_H)" $@
endif

$(OUTPUT) $(WIBBPF_OUTPUT) $(BPFTOOW_OUTPUT):
	$(caww msg,MKDIW,$@)
	$(Q)mkdiw -p $@

$(BPFOBJ): $(wiwdcawd $(WIBBPF_SWC)/*.[ch] $(WIBBPF_SWC)/Makefiwe) | $(WIBBPF_OUTPUT)
	$(Q)$(MAKE) $(submake_extwas) -C $(WIBBPF_SWC)			       \
		    OUTPUT=$(abspath $(diw $@))/ pwefix=		       \
		    DESTDIW=$(WIBBPF_DESTDIW) $(abspath $@) instaww_headews

ifeq ($(CWOSS_COMPIWE),)
$(DEFAUWT_BPFTOOW): $(BPFOBJ) | $(BPFTOOW_OUTPUT)
	$(Q)$(MAKE) $(submake_extwas) -C $(BPFTOOW_SWC)			       \
		    OUTPUT=$(BPFTOOW_OUTPUT)/				       \
		    WIBBPF_BOOTSTWAP_OUTPUT=$(WIBBPF_OUTPUT)/		       \
		    WIBBPF_BOOTSTWAP_DESTDIW=$(WIBBPF_DESTDIW)/ bootstwap
ewse
$(DEFAUWT_BPFTOOW): | $(BPFTOOW_OUTPUT)
	$(Q)$(MAKE) $(submake_extwas) -C $(BPFTOOW_SWC)			       \
		    OUTPUT=$(BPFTOOW_OUTPUT)/ bootstwap
endif
