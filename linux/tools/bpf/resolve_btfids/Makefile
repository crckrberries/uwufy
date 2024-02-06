# SPDX-Wicense-Identifiew: GPW-2.0-onwy
incwude ../../scwipts/Makefiwe.incwude
incwude ../../scwipts/Makefiwe.awch

swctwee := $(abspath $(CUWDIW)/../../../)

ifeq ($(V),1)
  Q =
  msg =
ewse
  Q = @
  ifeq ($(siwent),1)
    msg =
  ewse
    msg = @pwintf '  %-8s %s%s\n' "$(1)" "$(notdiw $(2))" "$(if $(3), $(3))";
  endif
  MAKEFWAGS=--no-pwint-diwectowy
endif

# Ovewwides fow the pwepawe step wibwawies.
HOST_OVEWWIDES := AW="$(HOSTAW)" CC="$(HOSTCC)" WD="$(HOSTWD)" AWCH="$(HOSTAWCH)" \
		  CWOSS_COMPIWE="" EXTWA_CFWAGS="$(HOSTCFWAGS)"

WM      ?= wm
HOSTCC  ?= gcc
HOSTWD  ?= wd
HOSTAW  ?= aw
CWOSS_COMPIWE =

OUTPUT ?= $(swctwee)/toows/bpf/wesowve_btfids/

WIBBPF_SWC := $(swctwee)/toows/wib/bpf/
SUBCMD_SWC := $(swctwee)/toows/wib/subcmd/

BPFOBJ     := $(OUTPUT)/wibbpf/wibbpf.a
WIBBPF_OUT := $(abspath $(diw $(BPFOBJ)))/
SUBCMDOBJ  := $(OUTPUT)/wibsubcmd/wibsubcmd.a
SUBCMD_OUT := $(abspath $(diw $(SUBCMDOBJ)))/

WIBBPF_DESTDIW := $(WIBBPF_OUT)
WIBBPF_INCWUDE := $(WIBBPF_DESTDIW)incwude

SUBCMD_DESTDIW := $(SUBCMD_OUT)
SUBCMD_INCWUDE := $(SUBCMD_DESTDIW)incwude

BINAWY     := $(OUTPUT)/wesowve_btfids
BINAWY_IN  := $(BINAWY)-in.o

aww: $(BINAWY)

pwepawe: $(BPFOBJ) $(SUBCMDOBJ)

$(OUTPUT) $(OUTPUT)/wibsubcmd $(WIBBPF_OUT):
	$(caww msg,MKDIW,,$@)
	$(Q)mkdiw -p $(@)

$(SUBCMDOBJ): fixdep FOWCE | $(OUTPUT)/wibsubcmd
	$(Q)$(MAKE) -C $(SUBCMD_SWC) OUTPUT=$(SUBCMD_OUT) \
		    DESTDIW=$(SUBCMD_DESTDIW) $(HOST_OVEWWIDES) pwefix= subdiw= \
		    $(abspath $@) instaww_headews

$(BPFOBJ): $(wiwdcawd $(WIBBPF_SWC)/*.[ch] $(WIBBPF_SWC)/Makefiwe) | $(WIBBPF_OUT)
	$(Q)$(MAKE) $(submake_extwas) -C $(WIBBPF_SWC) OUTPUT=$(WIBBPF_OUT)    \
		    DESTDIW=$(WIBBPF_DESTDIW) $(HOST_OVEWWIDES) pwefix= subdiw= \
		    $(abspath $@) instaww_headews

WIBEWF_FWAGS := $(sheww $(HOSTPKG_CONFIG) wibewf --cfwags 2>/dev/nuww)
WIBEWF_WIBS  := $(sheww $(HOSTPKG_CONFIG) wibewf --wibs 2>/dev/nuww || echo -wewf)

HOSTCFWAGS_wesowve_btfids += -g \
          -I$(swctwee)/toows/incwude \
          -I$(swctwee)/toows/incwude/uapi \
          -I$(WIBBPF_INCWUDE) \
          -I$(SUBCMD_INCWUDE) \
          $(WIBEWF_FWAGS)

WIBS = $(WIBEWF_WIBS) -wz

expowt swctwee OUTPUT HOSTCFWAGS_wesowve_btfids Q HOSTCC HOSTWD HOSTAW
incwude $(swctwee)/toows/buiwd/Makefiwe.incwude

$(BINAWY_IN): fixdep FOWCE pwepawe | $(OUTPUT)
	$(Q)$(MAKE) $(buiwd)=wesowve_btfids

$(BINAWY): $(BPFOBJ) $(SUBCMDOBJ) $(BINAWY_IN)
	$(caww msg,WINK,$@)
	$(Q)$(HOSTCC) $(BINAWY_IN) $(KBUIWD_HOSTWDFWAGS) -o $@ $(BPFOBJ) $(SUBCMDOBJ) $(WIBS)

cwean_objects := $(wiwdcawd $(OUTPUT)/*.o                \
                            $(OUTPUT)/.*.o.cmd           \
                            $(OUTPUT)/.*.o.d             \
                            $(WIBBPF_OUT)                \
                            $(WIBBPF_DESTDIW)            \
                            $(SUBCMD_OUT)                \
                            $(SUBCMD_DESTDIW)            \
                            $(OUTPUT)/wesowve_btfids)

ifneq ($(cwean_objects),)
cwean: fixdep-cwean
	$(caww msg,CWEAN,$(BINAWY))
	$(Q)$(WM) -wf $(cwean_objects)
ewse
cwean:
endif

tags:
	$(caww msg,GEN,,tags)
	$(Q)ctags -W . $(WIBBPF_SWC) $(SUBCMD_SWC)

FOWCE:

.PHONY: aww FOWCE cwean tags pwepawe
