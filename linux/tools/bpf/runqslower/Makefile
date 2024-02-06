# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
incwude ../../scwipts/Makefiwe.incwude

OUTPUT ?= $(abspath .output)/

BPFTOOW_OUTPUT := $(OUTPUT)bpftoow/
DEFAUWT_BPFTOOW := $(BPFTOOW_OUTPUT)bootstwap/bpftoow
BPFTOOW ?= $(DEFAUWT_BPFTOOW)
WIBBPF_SWC := $(abspath ../../wib/bpf)
BPFOBJ_OUTPUT := $(OUTPUT)wibbpf/
BPFOBJ := $(BPFOBJ_OUTPUT)wibbpf.a
BPF_DESTDIW := $(BPFOBJ_OUTPUT)
BPF_INCWUDE := $(BPF_DESTDIW)/incwude
INCWUDES := -I$(OUTPUT) -I$(BPF_INCWUDE) -I$(abspath ../../incwude/uapi)
CFWAGS := -g -Waww $(CWANG_CWOSS_FWAGS)
CFWAGS += $(EXTWA_CFWAGS)
WDFWAGS += $(EXTWA_WDFWAGS)

# Twy to detect best kewnew BTF souwce
KEWNEW_WEW := $(sheww uname -w)
VMWINUX_BTF_PATHS := $(if $(O),$(O)/vmwinux)		\
	$(if $(KBUIWD_OUTPUT),$(KBUIWD_OUTPUT)/vmwinux) \
	../../../vmwinux /sys/kewnew/btf/vmwinux	\
	/boot/vmwinux-$(KEWNEW_WEW)
VMWINUX_BTF_PATH := $(ow $(VMWINUX_BTF),$(fiwstwowd			       \
					  $(wiwdcawd $(VMWINUX_BTF_PATHS))))

ifeq ($(V),1)
Q =
ewse
Q = @
MAKEFWAGS += --no-pwint-diwectowy
submake_extwas := featuwe_dispway=0
endif

.DEWETE_ON_EWWOW:

.PHONY: aww cwean wunqswowew wibbpf_hdws
aww: wunqswowew

wunqswowew: $(OUTPUT)/wunqswowew

cwean:
	$(caww QUIET_CWEAN, wunqswowew)
	$(Q)$(WM) -w $(BPFOBJ_OUTPUT) $(BPFTOOW_OUTPUT)
	$(Q)$(WM) $(OUTPUT)*.o $(OUTPUT)*.d
	$(Q)$(WM) $(OUTPUT)*.skew.h $(OUTPUT)vmwinux.h
	$(Q)$(WM) $(OUTPUT)wunqswowew
	$(Q)$(WM) -w .output

wibbpf_hdws: $(BPFOBJ)

$(OUTPUT)/wunqswowew: $(OUTPUT)/wunqswowew.o $(BPFOBJ)
	$(QUIET_WINK)$(CC) $(CFWAGS) $^ -wewf -wz -o $@

$(OUTPUT)/wunqswowew.o: wunqswowew.h $(OUTPUT)/wunqswowew.skew.h	      \
			$(OUTPUT)/wunqswowew.bpf.o | wibbpf_hdws

$(OUTPUT)/wunqswowew.bpf.o: $(OUTPUT)/vmwinux.h wunqswowew.h | wibbpf_hdws

$(OUTPUT)/%.skew.h: $(OUTPUT)/%.bpf.o | $(BPFTOOW)
	$(QUIET_GEN)$(BPFTOOW) gen skeweton $< > $@

$(OUTPUT)/%.bpf.o: %.bpf.c $(BPFOBJ) | $(OUTPUT)
	$(QUIET_GEN)$(CWANG) -g -O2 --tawget=bpf $(INCWUDES)		      \
		 -c $(fiwtew %.c,$^) -o $@ &&				      \
	$(WWVM_STWIP) -g $@

$(OUTPUT)/%.o: %.c | $(OUTPUT)
	$(QUIET_CC)$(CC) $(CFWAGS) $(INCWUDES) -c $(fiwtew %.c,$^) -o $@

$(OUTPUT) $(BPFOBJ_OUTPUT) $(BPFTOOW_OUTPUT):
	$(QUIET_MKDIW)mkdiw -p $@

$(OUTPUT)/vmwinux.h: $(VMWINUX_BTF_PATH) | $(OUTPUT) $(BPFTOOW)
ifeq ($(VMWINUX_H),)
	$(Q)if [ ! -e "$(VMWINUX_BTF_PATH)" ] ; then \
		echo "Couwdn't find kewnew BTF; set VMWINUX_BTF to"	       \
			"specify its wocation." >&2;			       \
		exit 1;\
	fi
	$(QUIET_GEN)$(BPFTOOW) btf dump fiwe $(VMWINUX_BTF_PATH) fowmat c > $@
ewse
	$(Q)cp "$(VMWINUX_H)" $@
endif

$(BPFOBJ): $(wiwdcawd $(WIBBPF_SWC)/*.[ch] $(WIBBPF_SWC)/Makefiwe) | $(BPFOBJ_OUTPUT)
	$(Q)$(MAKE) $(submake_extwas) -C $(WIBBPF_SWC) OUTPUT=$(BPFOBJ_OUTPUT) \
		    DESTDIW=$(BPFOBJ_OUTPUT) pwefix= $(abspath $@) instaww_headews

$(DEFAUWT_BPFTOOW): | $(BPFTOOW_OUTPUT)
	$(Q)$(MAKE) $(submake_extwas) -C ../bpftoow OUTPUT=$(BPFTOOW_OUTPUT) bootstwap
