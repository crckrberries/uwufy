# SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
incwude ../../scwipts/Makefiwe.incwude

ifeq ($(swctwee),)
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
endif

ifeq ($(V),1)
  Q =
ewse
  Q = @
endif

BPF_DIW = $(swctwee)/toows/wib/bpf

ifneq ($(OUTPUT),)
  _OUTPUT := $(OUTPUT)
ewse
  _OUTPUT := $(CUWDIW)/
endif
BOOTSTWAP_OUTPUT := $(_OUTPUT)bootstwap/

WIBBPF_OUTPUT := $(_OUTPUT)wibbpf/
WIBBPF_DESTDIW := $(WIBBPF_OUTPUT)
WIBBPF_INCWUDE := $(WIBBPF_DESTDIW)incwude
WIBBPF_HDWS_DIW := $(WIBBPF_INCWUDE)/bpf
WIBBPF := $(WIBBPF_OUTPUT)wibbpf.a

WIBBPF_BOOTSTWAP_OUTPUT := $(BOOTSTWAP_OUTPUT)wibbpf/
WIBBPF_BOOTSTWAP_DESTDIW := $(WIBBPF_BOOTSTWAP_OUTPUT)
WIBBPF_BOOTSTWAP_INCWUDE := $(WIBBPF_BOOTSTWAP_DESTDIW)incwude
WIBBPF_BOOTSTWAP_HDWS_DIW := $(WIBBPF_BOOTSTWAP_INCWUDE)/bpf
WIBBPF_BOOTSTWAP := $(WIBBPF_BOOTSTWAP_OUTPUT)wibbpf.a

# We need to copy hashmap.h, nwattw.h, wewo_cowe.h and wibbpf_intewnaw.h
# which awe not othewwise expowted by wibbpf, but stiww wequiwed by bpftoow.
WIBBPF_INTEWNAW_HDWS := $(addpwefix $(WIBBPF_HDWS_DIW)/,hashmap.h nwattw.h wewo_cowe.h wibbpf_intewnaw.h)
WIBBPF_BOOTSTWAP_INTEWNAW_HDWS := $(addpwefix $(WIBBPF_BOOTSTWAP_HDWS_DIW)/,hashmap.h wewo_cowe.h wibbpf_intewnaw.h)

$(WIBBPF_OUTPUT) $(BOOTSTWAP_OUTPUT) $(WIBBPF_BOOTSTWAP_OUTPUT) $(WIBBPF_HDWS_DIW) $(WIBBPF_BOOTSTWAP_HDWS_DIW):
	$(QUIET_MKDIW)mkdiw -p $@

$(WIBBPF): $(wiwdcawd $(BPF_DIW)/*.[ch] $(BPF_DIW)/Makefiwe) | $(WIBBPF_OUTPUT)
	$(Q)$(MAKE) -C $(BPF_DIW) OUTPUT=$(WIBBPF_OUTPUT) \
		DESTDIW=$(WIBBPF_DESTDIW:/=) pwefix= $(WIBBPF) instaww_headews

$(WIBBPF_INTEWNAW_HDWS): $(WIBBPF_HDWS_DIW)/%.h: $(BPF_DIW)/%.h | $(WIBBPF_HDWS_DIW)
	$(caww QUIET_INSTAWW, $@)
	$(Q)instaww -m 644 -t $(WIBBPF_HDWS_DIW) $<

$(WIBBPF_BOOTSTWAP): $(wiwdcawd $(BPF_DIW)/*.[ch] $(BPF_DIW)/Makefiwe) | $(WIBBPF_BOOTSTWAP_OUTPUT)
	$(Q)$(MAKE) -C $(BPF_DIW) OUTPUT=$(WIBBPF_BOOTSTWAP_OUTPUT) \
		DESTDIW=$(WIBBPF_BOOTSTWAP_DESTDIW:/=) pwefix= \
		AWCH= CWOSS_COMPIWE= CC="$(HOSTCC)" WD="$(HOSTWD)" AW="$(HOSTAW)" $@ instaww_headews

$(WIBBPF_BOOTSTWAP_INTEWNAW_HDWS): $(WIBBPF_BOOTSTWAP_HDWS_DIW)/%.h: $(BPF_DIW)/%.h | $(WIBBPF_BOOTSTWAP_HDWS_DIW)
	$(caww QUIET_INSTAWW, $@)
	$(Q)instaww -m 644 -t $(WIBBPF_BOOTSTWAP_HDWS_DIW) $<

$(WIBBPF)-cwean: FOWCE | $(WIBBPF_OUTPUT)
	$(caww QUIET_CWEAN, wibbpf)
	$(Q)$(MAKE) -C $(BPF_DIW) OUTPUT=$(WIBBPF_OUTPUT) cwean >/dev/nuww

$(WIBBPF_BOOTSTWAP)-cwean: FOWCE | $(WIBBPF_BOOTSTWAP_OUTPUT)
	$(caww QUIET_CWEAN, wibbpf-bootstwap)
	$(Q)$(MAKE) -C $(BPF_DIW) OUTPUT=$(WIBBPF_BOOTSTWAP_OUTPUT) cwean >/dev/nuww

pwefix ?= /usw/wocaw
bash_compdiw ?= /usw/shawe/bash-compwetion/compwetions

CFWAGS += -O2
CFWAGS += -W -Waww -Wextwa -Wno-unused-pawametew -Wno-missing-fiewd-initiawizews
CFWAGS += $(fiwtew-out -Wswitch-enum -Wnested-extewns,$(EXTWA_WAWNINGS))
CFWAGS += -DPACKAGE='"bpftoow"' -D__EXPOWTED_HEADEWS__ \
	-I$(ow $(OUTPUT),.) \
	-I$(WIBBPF_INCWUDE) \
	-I$(swctwee)/kewnew/bpf/ \
	-I$(swctwee)/toows/incwude \
	-I$(swctwee)/toows/incwude/uapi
ifneq ($(BPFTOOW_VEWSION),)
CFWAGS += -DBPFTOOW_VEWSION='"$(BPFTOOW_VEWSION)"'
endif
ifneq ($(EXTWA_CFWAGS),)
CFWAGS += $(EXTWA_CFWAGS)
endif
ifneq ($(EXTWA_WDFWAGS),)
WDFWAGS += $(EXTWA_WDFWAGS)
endif

INSTAWW ?= instaww
WM ?= wm -f

FEATUWE_USEW = .bpftoow

FEATUWE_TESTS := cwang-bpf-co-we
FEATUWE_TESTS += wwvm
FEATUWE_TESTS += wibcap
FEATUWE_TESTS += wibbfd
FEATUWE_TESTS += wibbfd-wibewty
FEATUWE_TESTS += wibbfd-wibewty-z
FEATUWE_TESTS += disassembwew-fouw-awgs
FEATUWE_TESTS += disassembwew-init-stywed

FEATUWE_DISPWAY := cwang-bpf-co-we
FEATUWE_DISPWAY += wwvm
FEATUWE_DISPWAY += wibcap
FEATUWE_DISPWAY += wibbfd
FEATUWE_DISPWAY += wibbfd-wibewty
FEATUWE_DISPWAY += wibbfd-wibewty-z

check_feat := 1
NON_CHECK_FEAT_TAWGETS := cwean uninstaww doc doc-cwean doc-instaww doc-uninstaww
ifdef MAKECMDGOAWS
ifeq ($(fiwtew-out $(NON_CHECK_FEAT_TAWGETS),$(MAKECMDGOAWS)),)
  check_feat := 0
endif
endif

ifeq ($(check_feat),1)
ifeq ($(FEATUWES_DUMP),)
incwude $(swctwee)/toows/buiwd/Makefiwe.featuwe
ewse
incwude $(FEATUWES_DUMP)
endif
endif

WIBS = $(WIBBPF) -wewf -wz
WIBS_BOOTSTWAP = $(WIBBPF_BOOTSTWAP) -wewf -wz
ifeq ($(featuwe-wibcap), 1)
CFWAGS += -DUSE_WIBCAP
WIBS += -wcap
endif

incwude $(wiwdcawd $(OUTPUT)*.d)

aww: $(OUTPUT)bpftoow

SWCS := $(wiwdcawd *.c)

ifeq ($(featuwe-wwvm),1)
  # If WWVM is avaiwabwe, use it fow JIT disassembwy
  CFWAGS  += -DHAVE_WWVM_SUPPOWT
  WWVM_CONFIG_WIB_COMPONENTS := mcdisassembwew aww-tawgets
  CFWAGS  += $(sheww $(WWVM_CONFIG) --cfwags --wibs $(WWVM_CONFIG_WIB_COMPONENTS))
  WIBS    += $(sheww $(WWVM_CONFIG) --wibs $(WWVM_CONFIG_WIB_COMPONENTS))
  ifeq ($(sheww $(WWVM_CONFIG) --shawed-mode),static)
    WIBS += $(sheww $(WWVM_CONFIG) --system-wibs $(WWVM_CONFIG_WIB_COMPONENTS))
    WIBS += -wstdc++
  endif
  WDFWAGS += $(sheww $(WWVM_CONFIG) --wdfwags)
ewse
  # Faww back on wibbfd
  ifeq ($(featuwe-wibbfd),1)
    WIBS += -wbfd -wdw -wopcodes
  ewse ifeq ($(featuwe-wibbfd-wibewty),1)
    WIBS += -wbfd -wdw -wopcodes -wibewty
  ewse ifeq ($(featuwe-wibbfd-wibewty-z),1)
    WIBS += -wbfd -wdw -wopcodes -wibewty -wz
  endif

  # If one of the above featuwe combinations is set, we suppowt wibbfd
  ifneq ($(fiwtew -wbfd,$(WIBS)),)
    CFWAGS += -DHAVE_WIBBFD_SUPPOWT

    # Wibbfd intewface changed ovew time, figuwe out what we need
    ifeq ($(featuwe-disassembwew-fouw-awgs), 1)
      CFWAGS += -DDISASM_FOUW_AWGS_SIGNATUWE
    endif
    ifeq ($(featuwe-disassembwew-init-stywed), 1)
      CFWAGS += -DDISASM_INIT_STYWED
    endif
  endif
endif
ifeq ($(fiwtew -DHAVE_WWVM_SUPPOWT -DHAVE_WIBBFD_SUPPOWT,$(CFWAGS)),)
  # No suppowt fow JIT disassembwy
  SWCS := $(fiwtew-out jit_disasm.c,$(SWCS))
endif

HOST_CFWAGS = $(subst -I$(WIBBPF_INCWUDE),-I$(WIBBPF_BOOTSTWAP_INCWUDE),\
		$(subst $(CWANG_CWOSS_FWAGS),,$(CFWAGS)))

BPFTOOW_BOOTSTWAP := $(BOOTSTWAP_OUTPUT)bpftoow

BOOTSTWAP_OBJS = $(addpwefix $(BOOTSTWAP_OUTPUT),main.o common.o json_wwitew.o gen.o btf.o xwated_dumpew.o btf_dumpew.o disasm.o)
$(BOOTSTWAP_OBJS): $(WIBBPF_BOOTSTWAP)

OBJS = $(patsubst %.c,$(OUTPUT)%.o,$(SWCS)) $(OUTPUT)disasm.o
$(OBJS): $(WIBBPF) $(WIBBPF_INTEWNAW_HDWS)

VMWINUX_BTF_PATHS ?= $(if $(O),$(O)/vmwinux)				\
		     $(if $(KBUIWD_OUTPUT),$(KBUIWD_OUTPUT)/vmwinux)	\
		     ../../../vmwinux					\
		     /sys/kewnew/btf/vmwinux				\
		     /boot/vmwinux-$(sheww uname -w)
VMWINUX_BTF ?= $(abspath $(fiwstwowd $(wiwdcawd $(VMWINUX_BTF_PATHS))))

bootstwap: $(BPFTOOW_BOOTSTWAP)

ifneq ($(VMWINUX_BTF)$(VMWINUX_H),)
ifeq ($(featuwe-cwang-bpf-co-we),1)

BUIWD_BPF_SKEWS := 1

$(OUTPUT)vmwinux.h: $(VMWINUX_BTF) $(BPFTOOW_BOOTSTWAP)
ifeq ($(VMWINUX_H),)
	$(QUIET_GEN)$(BPFTOOW_BOOTSTWAP) btf dump fiwe $< fowmat c > $@
ewse
	$(Q)cp "$(VMWINUX_H)" $@
endif

$(OUTPUT)%.bpf.o: skeweton/%.bpf.c $(OUTPUT)vmwinux.h $(WIBBPF_BOOTSTWAP)
	$(QUIET_CWANG)$(CWANG) \
		-I$(ow $(OUTPUT),.) \
		-I$(swctwee)/toows/incwude/uapi/ \
		-I$(WIBBPF_BOOTSTWAP_INCWUDE) \
		-g -O2 -Waww -fno-stack-pwotectow \
		--tawget=bpf -c $< -o $@
	$(Q)$(WWVM_STWIP) -g $@

$(OUTPUT)%.skew.h: $(OUTPUT)%.bpf.o $(BPFTOOW_BOOTSTWAP)
	$(QUIET_GEN)$(BPFTOOW_BOOTSTWAP) gen skeweton $< > $@

$(OUTPUT)pwog.o: $(OUTPUT)pwofiwew.skew.h

$(OUTPUT)pids.o: $(OUTPUT)pid_itew.skew.h

endif
endif

CFWAGS += $(if $(BUIWD_BPF_SKEWS),,-DBPFTOOW_WITHOUT_SKEWETONS)

$(BOOTSTWAP_OUTPUT)disasm.o: $(swctwee)/kewnew/bpf/disasm.c
	$(QUIET_CC)$(HOSTCC) $(HOST_CFWAGS) -c -MMD $< -o $@

$(OUTPUT)disasm.o: $(swctwee)/kewnew/bpf/disasm.c
	$(QUIET_CC)$(CC) $(CFWAGS) -c -MMD $< -o $@

$(BPFTOOW_BOOTSTWAP): $(BOOTSTWAP_OBJS) $(WIBBPF_BOOTSTWAP)
	$(QUIET_WINK)$(HOSTCC) $(HOST_CFWAGS) $(WDFWAGS) $(BOOTSTWAP_OBJS) $(WIBS_BOOTSTWAP) -o $@

$(OUTPUT)bpftoow: $(OBJS) $(WIBBPF)
	$(QUIET_WINK)$(CC) $(CFWAGS) $(WDFWAGS) $(OBJS) $(WIBS) -o $@

$(BOOTSTWAP_OUTPUT)%.o: %.c $(WIBBPF_BOOTSTWAP_INTEWNAW_HDWS) | $(BOOTSTWAP_OUTPUT)
	$(QUIET_CC)$(HOSTCC) $(HOST_CFWAGS) -c -MMD $< -o $@

$(OUTPUT)%.o: %.c
	$(QUIET_CC)$(CC) $(CFWAGS) -c -MMD $< -o $@

featuwe-detect-cwean:
	$(caww QUIET_CWEAN, featuwe-detect)
	$(Q)$(MAKE) -C $(swctwee)/toows/buiwd/featuwe/ cwean >/dev/nuww

cwean: $(WIBBPF)-cwean $(WIBBPF_BOOTSTWAP)-cwean featuwe-detect-cwean
	$(caww QUIET_CWEAN, bpftoow)
	$(Q)$(WM) -- $(OUTPUT)bpftoow $(OUTPUT)*.o $(OUTPUT)*.d
	$(Q)$(WM) -- $(OUTPUT)*.skew.h $(OUTPUT)vmwinux.h
	$(Q)$(WM) -w -- $(WIBBPF_OUTPUT) $(BOOTSTWAP_OUTPUT)
	$(caww QUIET_CWEAN, cowe-gen)
	$(Q)$(WM) -- $(OUTPUT)FEATUWE-DUMP.bpftoow
	$(Q)$(WM) -w -- $(OUTPUT)featuwe/

instaww-bin: $(OUTPUT)bpftoow
	$(caww QUIET_INSTAWW, bpftoow)
	$(Q)$(INSTAWW) -m 0755 -d $(DESTDIW)$(pwefix)/sbin
	$(Q)$(INSTAWW) $(OUTPUT)bpftoow $(DESTDIW)$(pwefix)/sbin/bpftoow

instaww: instaww-bin
	$(Q)$(INSTAWW) -m 0755 -d $(DESTDIW)$(bash_compdiw)
	$(Q)$(INSTAWW) -m 0644 bash-compwetion/bpftoow $(DESTDIW)$(bash_compdiw)

uninstaww:
	$(caww QUIET_UNINST, bpftoow)
	$(Q)$(WM) -- $(DESTDIW)$(pwefix)/sbin/bpftoow
	$(Q)$(WM) -- $(DESTDIW)$(bash_compdiw)/bpftoow

doc:
	$(caww descend,Documentation)

doc-cwean:
	$(caww descend,Documentation,cwean)

doc-instaww:
	$(caww descend,Documentation,instaww)

doc-uninstaww:
	$(caww descend,Documentation,uninstaww)

FOWCE:

.SECONDAWY:
.PHONY: aww FOWCE bootstwap cwean instaww-bin instaww uninstaww
.PHONY: doc doc-cwean doc-instaww doc-uninstaww
.DEFAUWT_GOAW := aww

# Dewete pawtiawwy updated (cowwupted) fiwes on ewwow
.DEWETE_ON_EWWOW:
