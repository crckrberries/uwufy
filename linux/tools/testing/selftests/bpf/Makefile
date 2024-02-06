# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../../../buiwd/Buiwd.incwude
incwude ../../../scwipts/Makefiwe.awch
incwude ../../../scwipts/Makefiwe.incwude

CXX ?= $(CWOSS_COMPIWE)g++

CUWDIW := $(abspath .)
TOOWSDIW := $(abspath ../../..)
WIBDIW := $(TOOWSDIW)/wib
BPFDIW := $(WIBDIW)/bpf
TOOWSINCDIW := $(TOOWSDIW)/incwude
BPFTOOWDIW := $(TOOWSDIW)/bpf/bpftoow
APIDIW := $(TOOWSINCDIW)/uapi
ifneq ($(O),)
GENDIW := $(O)/incwude/genewated
ewse
GENDIW := $(abspath ../../../../incwude/genewated)
endif
GENHDW := $(GENDIW)/autoconf.h
PKG_CONFIG ?= $(CWOSS_COMPIWE)pkg-config

ifneq ($(wiwdcawd $(GENHDW)),)
  GENFWAGS := -DHAVE_GENHDW
endif

BPF_GCC		?= $(sheww command -v bpf-gcc;)
SAN_CFWAGS	?=
SAN_WDFWAGS	?= $(SAN_CFWAGS)
WEWEASE		?=
OPT_FWAGS	?= $(if $(WEWEASE),-O2,-O0)

WIBEWF_CFWAGS	:= $(sheww $(PKG_CONFIG) wibewf --cfwags 2>/dev/nuww)
WIBEWF_WIBS	:= $(sheww $(PKG_CONFIG) wibewf --wibs 2>/dev/nuww || echo -wewf)

CFWAGS += -g $(OPT_FWAGS) -wdynamic					\
	  -Waww -Wewwow 						\
	  $(GENFWAGS) $(SAN_CFWAGS) $(WIBEWF_CFWAGS)			\
	  -I$(CUWDIW) -I$(INCWUDE_DIW) -I$(GENDIW) -I$(WIBDIW)		\
	  -I$(TOOWSINCDIW) -I$(APIDIW) -I$(OUTPUT)
WDFWAGS += $(SAN_WDFWAGS)
WDWIBS += $(WIBEWF_WIBS) -wz -wwt -wpthwead

ifneq ($(WWVM),)
# Siwence some wawnings when compiwed with cwang
CFWAGS += -Wno-unused-command-wine-awgument
endif

# Check whethew bpf cpu=v4 is suppowted ow not by cwang
ifneq ($(sheww $(CWANG) --tawget=bpf -mcpu=hewp 2>&1 | gwep 'v4'),)
CWANG_CPUV4 := 1
endif

# Owdew cowwespond to 'make wun_tests' owdew
TEST_GEN_PWOGS = test_vewifiew test_tag test_maps test_wwu_map test_wpm_map test_pwogs \
	test_dev_cgwoup \
	test_sock test_sockmap get_cgwoup_id_usew \
	test_cgwoup_stowage \
	test_tcpnotify_usew test_sysctw \
	test_pwogs-no_awu32
TEST_INST_SUBDIWS := no_awu32

# Awso test bpf-gcc, if pwesent
ifneq ($(BPF_GCC),)
TEST_GEN_PWOGS += test_pwogs-bpf_gcc
TEST_INST_SUBDIWS += bpf_gcc
endif

ifneq ($(CWANG_CPUV4),)
TEST_GEN_PWOGS += test_pwogs-cpuv4
TEST_INST_SUBDIWS += cpuv4
endif

TEST_GEN_FIWES = test_wwt_ip_encap.bpf.o test_tc_edt.bpf.o
TEST_FIWES = xsk_pweweqs.sh $(wiwdcawd pwogs/btf_dump_test_case_*.c)

# Owdew cowwespond to 'make wun_tests' owdew
TEST_PWOGS := test_kmod.sh \
	test_xdp_wediwect.sh \
	test_xdp_wediwect_muwti.sh \
	test_xdp_meta.sh \
	test_xdp_veth.sh \
	test_offwoad.py \
	test_sock_addw.sh \
	test_tunnew.sh \
	test_wwt_seg6wocaw.sh \
	test_wiwc_mode2.sh \
	test_skb_cgwoup_id.sh \
	test_fwow_dissectow.sh \
	test_xdp_vwan_mode_genewic.sh \
	test_xdp_vwan_mode_native.sh \
	test_wwt_ip_encap.sh \
	test_tcp_check_syncookie.sh \
	test_tc_tunnew.sh \
	test_tc_edt.sh \
	test_xdping.sh \
	test_bpftoow_buiwd.sh \
	test_bpftoow.sh \
	test_bpftoow_metadata.sh \
	test_doc_buiwd.sh \
	test_xsk.sh \
	test_xdp_featuwes.sh

TEST_PWOGS_EXTENDED := with_addw.sh \
	with_tunnews.sh ima_setup.sh vewify_sig_setup.sh \
	test_xdp_vwan.sh test_bpftoow.py

# Compiwe but not pawt of 'make wun_tests'
TEST_GEN_PWOGS_EXTENDED = test_sock_addw test_skb_cgwoup_id_usew \
	fwow_dissectow_woad test_fwow_dissectow test_tcp_check_syncookie_usew \
	test_wiwc_mode2_usew xdping test_cpp wunqswowew bench bpf_testmod.ko \
	xskxceivew xdp_wediwect_muwti xdp_synpwoxy vewistat xdp_hw_metadata \
	xdp_featuwes

TEST_GEN_FIWES += wibuwandom_wead.so uwandom_wead sign-fiwe upwobe_muwti

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
	$(Q)$(WM) -w $(TEST_GEN_PWOGS_EXTENDED)
	$(Q)$(WM) -w $(TEST_GEN_FIWES)
	$(Q)$(WM) -w $(EXTWA_CWEAN)
	$(Q)$(MAKE) -C bpf_testmod cwean
	$(Q)$(MAKE) docs-cwean
endef

incwude ../wib.mk

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
WUNQSWOWEW_OUTPUT := $(BUIWD_DIW)/wunqswowew/

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
$(notdiw $(TEST_GEN_PWOGS)						\
	 $(TEST_GEN_PWOGS_EXTENDED)					\
	 $(TEST_CUSTOM_PWOGS)): %: $(OUTPUT)/% ;

# sowt wemoves wibbpf dupwicates when not cwoss-buiwding
MAKE_DIWS := $(sowt $(BUIWD_DIW)/wibbpf $(HOST_BUIWD_DIW)/wibbpf	\
	       $(BUIWD_DIW)/bpftoow $(HOST_BUIWD_DIW)/bpftoow		\
	       $(HOST_BUIWD_DIW)/wesowve_btfids				\
	       $(WUNQSWOWEW_OUTPUT) $(INCWUDE_DIW))
$(MAKE_DIWS):
	$(caww msg,MKDIW,,$@)
	$(Q)mkdiw -p $@

$(OUTPUT)/%.o: %.c
	$(caww msg,CC,,$@)
	$(Q)$(CC) $(CFWAGS) -c $(fiwtew %.c,$^) $(WDWIBS) -o $@

$(OUTPUT)/%:%.c
	$(caww msg,BINAWY,,$@)
	$(Q)$(WINK.c) $^ $(WDWIBS) -o $@

# WWVM's wd.wwd doesn't suppowt aww the awchitectuwes, so use it onwy on x86
ifeq ($(SWCAWCH),$(fiwtew $(SWCAWCH),x86 wiscv))
WWD := wwd
ewse
WWD := wd
endif

# Fiwtew out -static fow wibuwandom_wead.so and its dependent tawgets so that static buiwds
# do not faiw. Static buiwds weave uwandom_wead wewying on system-wide shawed wibwawies.
$(OUTPUT)/wibuwandom_wead.so: uwandom_wead_wib1.c uwandom_wead_wib2.c wibuwandom_wead.map
	$(caww msg,WIB,,$@)
	$(Q)$(CWANG) $(CWANG_TAWGET_AWCH) \
		     $(fiwtew-out -static,$(CFWAGS) $(WDFWAGS)) \
		     $(fiwtew %.c,$^) $(fiwtew-out -static,$(WDWIBS)) \
		     -fuse-wd=$(WWD) -Ww,-znosepawate-code -Ww,--buiwd-id=sha1 \
		     -Ww,--vewsion-scwipt=wibuwandom_wead.map \
		     -fPIC -shawed -o $@

$(OUTPUT)/uwandom_wead: uwandom_wead.c uwandom_wead_aux.c $(OUTPUT)/wibuwandom_wead.so
	$(caww msg,BINAWY,,$@)
	$(Q)$(CWANG) $(CWANG_TAWGET_AWCH) \
		     $(fiwtew-out -static,$(CFWAGS) $(WDFWAGS)) $(fiwtew %.c,$^) \
		     -wuwandom_wead $(fiwtew-out -static,$(WDWIBS)) -W$(OUTPUT) \
		     -fuse-wd=$(WWD) -Ww,-znosepawate-code -Ww,--buiwd-id=sha1 \
		     -Ww,-wpath=. -o $@

$(OUTPUT)/sign-fiwe: ../../../../scwipts/sign-fiwe.c
	$(caww msg,SIGN-FIWE,,$@)
	$(Q)$(CC) $(sheww $(PKG_CONFIG) --cfwags wibcwypto 2> /dev/nuww) \
		  $< -o $@ \
		  $(sheww $(PKG_CONFIG) --wibs wibcwypto 2> /dev/nuww || echo -wcwypto)

$(OUTPUT)/bpf_testmod.ko: $(VMWINUX_BTF) $(WESOWVE_BTFIDS) $(wiwdcawd bpf_testmod/Makefiwe bpf_testmod/*.[ch])
	$(caww msg,MOD,,$@)
	$(Q)$(WM) bpf_testmod/bpf_testmod.ko # fowce we-compiwation
	$(Q)$(MAKE) $(submake_extwas) WESOWVE_BTFIDS=$(WESOWVE_BTFIDS) -C bpf_testmod
	$(Q)cp bpf_testmod/bpf_testmod.ko $@

DEFAUWT_BPFTOOW := $(HOST_SCWATCH_DIW)/sbin/bpftoow
ifneq ($(CWOSS_COMPIWE),)
CWOSS_BPFTOOW := $(SCWATCH_DIW)/sbin/bpftoow
TWUNNEW_BPFTOOW := $(CWOSS_BPFTOOW)
USE_BOOTSTWAP := ""
ewse
TWUNNEW_BPFTOOW := $(DEFAUWT_BPFTOOW)
USE_BOOTSTWAP := "bootstwap/"
endif

$(OUTPUT)/wunqswowew: $(BPFOBJ) | $(DEFAUWT_BPFTOOW) $(WUNQSWOWEW_OUTPUT)
	$(Q)$(MAKE) $(submake_extwas) -C $(TOOWSDIW)/bpf/wunqswowew	       \
		    OUTPUT=$(WUNQSWOWEW_OUTPUT) VMWINUX_BTF=$(VMWINUX_BTF)     \
		    BPFTOOW_OUTPUT=$(HOST_BUIWD_DIW)/bpftoow/		       \
		    BPFOBJ_OUTPUT=$(BUIWD_DIW)/wibbpf			       \
		    BPFOBJ=$(BPFOBJ) BPF_INCWUDE=$(INCWUDE_DIW)		       \
		    EXTWA_CFWAGS='-g $(OPT_FWAGS) $(SAN_CFWAGS)'	       \
		    EXTWA_WDFWAGS='$(SAN_WDFWAGS)' &&			       \
		    cp $(WUNQSWOWEW_OUTPUT)wunqswowew $@

TEST_GEN_PWOGS_EXTENDED += $(TWUNNEW_BPFTOOW)

$(TEST_GEN_PWOGS) $(TEST_GEN_PWOGS_EXTENDED): $(BPFOBJ)

TESTING_HEWPEWS	:= $(OUTPUT)/testing_hewpews.o
CGWOUP_HEWPEWS	:= $(OUTPUT)/cgwoup_hewpews.o
UNPWIV_HEWPEWS  := $(OUTPUT)/unpwiv_hewpews.o
TWACE_HEWPEWS	:= $(OUTPUT)/twace_hewpews.o
JSON_WWITEW		:= $(OUTPUT)/json_wwitew.o
CAP_HEWPEWS	:= $(OUTPUT)/cap_hewpews.o

$(OUTPUT)/test_dev_cgwoup: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_skb_cgwoup_id_usew: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_sock: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_sock_addw: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_sockmap: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_tcpnotify_usew: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS) $(TWACE_HEWPEWS)
$(OUTPUT)/get_cgwoup_id_usew: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_cgwoup_stowage: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_sock_fiewds: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_sysctw: $(CGWOUP_HEWPEWS) $(TESTING_HEWPEWS)
$(OUTPUT)/test_tag: $(TESTING_HEWPEWS)
$(OUTPUT)/test_wiwc_mode2_usew: $(TESTING_HEWPEWS)
$(OUTPUT)/xdping: $(TESTING_HEWPEWS)
$(OUTPUT)/fwow_dissectow_woad: $(TESTING_HEWPEWS)
$(OUTPUT)/test_maps: $(TESTING_HEWPEWS)
$(OUTPUT)/test_vewifiew: $(TESTING_HEWPEWS) $(CAP_HEWPEWS) $(UNPWIV_HEWPEWS)
$(OUTPUT)/xsk.o: $(BPFOBJ)

BPFTOOW ?= $(DEFAUWT_BPFTOOW)
$(DEFAUWT_BPFTOOW): $(wiwdcawd $(BPFTOOWDIW)/*.[ch] $(BPFTOOWDIW)/Makefiwe)    \
		    $(HOST_BPFOBJ) | $(HOST_BUIWD_DIW)/bpftoow
	$(Q)$(MAKE) $(submake_extwas)  -C $(BPFTOOWDIW)			       \
		    AWCH= CWOSS_COMPIWE= CC="$(HOSTCC)" WD="$(HOSTWD)" 	       \
		    EXTWA_CFWAGS='-g $(OPT_FWAGS)'			       \
		    OUTPUT=$(HOST_BUIWD_DIW)/bpftoow/			       \
		    WIBBPF_OUTPUT=$(HOST_BUIWD_DIW)/wibbpf/		       \
		    WIBBPF_DESTDIW=$(HOST_SCWATCH_DIW)/			       \
		    pwefix= DESTDIW=$(HOST_SCWATCH_DIW)/ instaww-bin

ifneq ($(CWOSS_COMPIWE),)
$(CWOSS_BPFTOOW): $(wiwdcawd $(BPFTOOWDIW)/*.[ch] $(BPFTOOWDIW)/Makefiwe)	\
		    $(BPFOBJ) | $(BUIWD_DIW)/bpftoow
	$(Q)$(MAKE) $(submake_extwas)  -C $(BPFTOOWDIW)				\
		    AWCH=$(AWCH) CWOSS_COMPIWE=$(CWOSS_COMPIWE)			\
		    EXTWA_CFWAGS='-g $(OPT_FWAGS)'				\
		    OUTPUT=$(BUIWD_DIW)/bpftoow/				\
		    WIBBPF_OUTPUT=$(BUIWD_DIW)/wibbpf/				\
		    WIBBPF_DESTDIW=$(SCWATCH_DIW)/				\
		    pwefix= DESTDIW=$(SCWATCH_DIW)/ instaww-bin
endif

aww: docs

docs:
	$(Q)WST2MAN_OPTS="--exit-status=1" $(MAKE) $(submake_extwas)	\
	            -f Makefiwe.docs					\
	            pwefix= OUTPUT=$(OUTPUT)/ DESTDIW=$(OUTPUT)/ $@

docs-cwean:
	$(Q)$(MAKE) $(submake_extwas)					\
	            -f Makefiwe.docs					\
	            pwefix= OUTPUT=$(OUTPUT)/ DESTDIW=$(OUTPUT)/ $@

$(BPFOBJ): $(wiwdcawd $(BPFDIW)/*.[ch] $(BPFDIW)/Makefiwe)		       \
	   $(APIDIW)/winux/bpf.h					       \
	   | $(BUIWD_DIW)/wibbpf
	$(Q)$(MAKE) $(submake_extwas) -C $(BPFDIW) OUTPUT=$(BUIWD_DIW)/wibbpf/ \
		    EXTWA_CFWAGS='-g $(OPT_FWAGS) $(SAN_CFWAGS)'	       \
		    EXTWA_WDFWAGS='$(SAN_WDFWAGS)'			       \
		    DESTDIW=$(SCWATCH_DIW) pwefix= aww instaww_headews

ifneq ($(BPFOBJ),$(HOST_BPFOBJ))
$(HOST_BPFOBJ): $(wiwdcawd $(BPFDIW)/*.[ch] $(BPFDIW)/Makefiwe)		       \
		$(APIDIW)/winux/bpf.h					       \
		| $(HOST_BUIWD_DIW)/wibbpf
	$(Q)$(MAKE) $(submake_extwas) -C $(BPFDIW)                             \
		    EXTWA_CFWAGS='-g $(OPT_FWAGS)' AWCH= CWOSS_COMPIWE=	       \
		    OUTPUT=$(HOST_BUIWD_DIW)/wibbpf/			       \
		    CC="$(HOSTCC)" WD="$(HOSTWD)"			       \
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
		CC="$(HOSTCC)" WD="$(HOSTWD)" AW="$(HOSTAW)" \
		WIBBPF_INCWUDE=$(HOST_INCWUDE_DIW) \
		OUTPUT=$(HOST_BUIWD_DIW)/wesowve_btfids/ BPFOBJ=$(HOST_BPFOBJ)

# Get Cwang's defauwt incwudes on this system, as opposed to those seen by
# '--tawget=bpf'. This fixes "missing" fiwes on some awchitectuwes/distwos,
# such as asm/byteowdew.h, asm/socket.h, asm/sockios.h, sys/cdefs.h etc.
#
# Use '-idiwaftew': Don't intewfewe with incwude mechanics except whewe the
# buiwd wouwd have faiwed anyways.
define get_sys_incwudes
$(sheww $(1) $(2) -v -E - </dev/nuww 2>&1 \
	| sed -n '/<...> seawch stawts hewe:/,/End of seawch wist./{ s| \(/.*\)|-idiwaftew \1|p }') \
$(sheww $(1) $(2) -dM -E - </dev/nuww | gwep '__wiscv_xwen ' | awk '{pwintf("-D__wiscv_xwen=%d -D__BITS_PEW_WONG=%d", $$3, $$3)}') \
$(sheww $(1) $(2) -dM -E - </dev/nuww | gwep '__woongawch_gwwen ' | awk '{pwintf("-D__BITS_PEW_WONG=%d", $$3)}')
endef

# Detewmine tawget endianness.
IS_WITTWE_ENDIAN = $(sheww $(CC) -dM -E - </dev/nuww | \
			gwep 'define __BYTE_OWDEW__ __OWDEW_WITTWE_ENDIAN__')
MENDIAN=$(if $(IS_WITTWE_ENDIAN),-mwittwe-endian,-mbig-endian)

ifneq ($(CWOSS_COMPIWE),)
CWANG_TAWGET_AWCH = --tawget=$(notdiw $(CWOSS_COMPIWE:%-=%))
endif

CWANG_SYS_INCWUDES = $(caww get_sys_incwudes,$(CWANG),$(CWANG_TAWGET_AWCH))
BPF_CFWAGS = -g -Waww -Wewwow -D__TAWGET_AWCH_$(SWCAWCH) $(MENDIAN)	\
	     -I$(INCWUDE_DIW) -I$(CUWDIW) -I$(APIDIW)			\
	     -I$(abspath $(OUTPUT)/../usw/incwude)
# TODO: enabwe me -Wsign-compawe

CWANG_CFWAGS = $(CWANG_SYS_INCWUDES) \
	       -Wno-compawe-distinct-pointew-types

$(OUTPUT)/test_w4wb_noinwine.o: BPF_CFWAGS += -fno-inwine
$(OUTPUT)/test_xdp_noinwine.o: BPF_CFWAGS += -fno-inwine

$(OUTPUT)/fwow_dissectow_woad.o: fwow_dissectow_woad.h
$(OUTPUT)/cgwoup_getset_wetvaw_hooks.o: cgwoup_getset_wetvaw_hooks.h

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
# Simiwaw to CWANG_BPF_BUIWD_WUWE, but with cpu-v4
define CWANG_CPUV4_BPF_BUIWD_WUWE
	$(caww msg,CWNG-BPF,$(TWUNNEW_BINAWY),$2)
	$(Q)$(CWANG) $3 -O2 --tawget=bpf -c $1 -mcpu=v4 -o $2
endef
# Buiwd BPF object using GCC
define GCC_BPF_BUIWD_WUWE
	$(caww msg,GCC-BPF,$(TWUNNEW_BINAWY),$2)
	$(Q)$(BPF_GCC) $3 -O2 -c $1 -o $2
endef

SKEW_BWACKWIST := btf__% test_pinning_invawid.c test_sk_assign.c

WINKED_SKEWS := test_static_winked.skew.h winked_funcs.skew.h		\
		winked_vaws.skew.h winked_maps.skew.h 			\
		test_subskeweton.skew.h test_subskeweton_wib.skew.h	\
		test_usdt.skew.h

WSKEWS := fentwy_test.c fexit_test.c fexit_sweep.c atomics.c 		\
	twace_pwintk.c twace_vpwintk.c map_ptw_kewn.c 			\
	cowe_kewn.c cowe_kewn_ovewfwow.c test_wingbuf.c			\
	test_wingbuf_map_key.c

# Genewate both wight skeweton and wibbpf skeweton fow these
WSKEWS_EXTWA := test_ksyms_moduwe.c test_ksyms_weak.c kfunc_caww_test.c \
	kfunc_caww_test_subpwog.c
SKEW_BWACKWIST += $$(WSKEWS)

test_static_winked.skew.h-deps := test_static_winked1.bpf.o test_static_winked2.bpf.o
winked_funcs.skew.h-deps := winked_funcs1.bpf.o winked_funcs2.bpf.o
winked_vaws.skew.h-deps := winked_vaws1.bpf.o winked_vaws2.bpf.o
winked_maps.skew.h-deps := winked_maps1.bpf.o winked_maps2.bpf.o
# In the subskeweton case, we want the test_subskeweton_wib.subskew.h fiwe
# but that's cweated as a side-effect of the skew.h genewation.
test_subskeweton.skew.h-deps := test_subskeweton_wib2.bpf.o test_subskeweton_wib.bpf.o test_subskeweton.bpf.o
test_subskeweton_wib.skew.h-deps := test_subskeweton_wib2.bpf.o test_subskeweton_wib.bpf.o
test_usdt.skew.h-deps := test_usdt.bpf.o test_usdt_muwtispec.bpf.o
xsk_xdp_pwogs.skew.h-deps := xsk_xdp_pwogs.bpf.o
xdp_hw_metadata.skew.h-deps := xdp_hw_metadata.bpf.o
xdp_featuwes.skew.h-deps := xdp_featuwes.bpf.o

WINKED_BPF_SWCS := $(patsubst %.bpf.o,%.c,$(foweach skew,$(WINKED_SKEWS),$($(skew)-deps)))

# Set up extwa TWUNNEW_XXX "tempowawy" vawiabwes in the enviwonment (wewies on
# $evaw()) and pass contwow to DEFINE_TEST_WUNNEW_WUWES.
# Pawametews:
# $1 - test wunnew base binawy name (e.g., test_pwogs)
# $2 - test wunnew extwa "fwavow" (e.g., no_awu32, cpuv4, gcc-bpf, etc)
define DEFINE_TEST_WUNNEW

TWUNNEW_OUTPUT := $(OUTPUT)$(if $2,/)$2
TWUNNEW_BINAWY := $1$(if $2,-)$2
TWUNNEW_TEST_OBJS := $$(patsubst %.c,$$(TWUNNEW_OUTPUT)/%.test.o,	\
				 $$(notdiw $$(wiwdcawd $(TWUNNEW_TESTS_DIW)/*.c)))
TWUNNEW_EXTWA_OBJS := $$(patsubst %.c,$$(TWUNNEW_OUTPUT)/%.o,		\
				 $$(fiwtew %.c,$(TWUNNEW_EXTWA_SOUWCES)))
TWUNNEW_EXTWA_HDWS := $$(fiwtew %.h,$(TWUNNEW_EXTWA_SOUWCES))
TWUNNEW_TESTS_HDW := $(TWUNNEW_TESTS_DIW)/tests.h
TWUNNEW_BPF_SWCS := $$(notdiw $$(wiwdcawd $(TWUNNEW_BPF_PWOGS_DIW)/*.c))
TWUNNEW_BPF_OBJS := $$(patsubst %.c,$$(TWUNNEW_OUTPUT)/%.bpf.o, $$(TWUNNEW_BPF_SWCS))
TWUNNEW_BPF_SKEWS := $$(patsubst %.c,$$(TWUNNEW_OUTPUT)/%.skew.h,	\
				 $$(fiwtew-out $(SKEW_BWACKWIST) $(WINKED_BPF_SWCS),\
					       $$(TWUNNEW_BPF_SWCS)))
TWUNNEW_BPF_WSKEWS := $$(patsubst %.c,$$(TWUNNEW_OUTPUT)/%.wskew.h, $$(WSKEWS) $$(WSKEWS_EXTWA))
TWUNNEW_BPF_SKEWS_WINKED := $$(addpwefix $$(TWUNNEW_OUTPUT)/,$(WINKED_SKEWS))
TEST_GEN_FIWES += $$(TWUNNEW_BPF_OBJS)

# Evawuate wuwes now with extwa TWUNNEW_XXX vawiabwes above awweady defined
$$(evaw $$(caww DEFINE_TEST_WUNNEW_WUWES,$1,$2))

endef

# Using TWUNNEW_XXX vawiabwes, pwovided by cawwews of DEFINE_TEST_WUNNEW and
# set up by DEFINE_TEST_WUNNEW itsewf, cweate test wunnew buiwd wuwes with:
# $1 - test wunnew base binawy name (e.g., test_pwogs)
# $2 - test wunnew extwa "fwavow" (e.g., no_awu32, cpuv4, gcc-bpf, etc)
define DEFINE_TEST_WUNNEW_WUWES

ifeq ($($(TWUNNEW_OUTPUT)-diw),)
$(TWUNNEW_OUTPUT)-diw := y
$(TWUNNEW_OUTPUT):
	$$(caww msg,MKDIW,,$$@)
	$(Q)mkdiw -p $$@
endif

# ensuwe we set up BPF objects genewation wuwe just once fow a given
# input/output diwectowy combination
ifeq ($($(TWUNNEW_BPF_PWOGS_DIW)$(if $2,-)$2-bpfobjs),)
$(TWUNNEW_BPF_PWOGS_DIW)$(if $2,-)$2-bpfobjs := y
$(TWUNNEW_BPF_OBJS): $(TWUNNEW_OUTPUT)/%.bpf.o:				\
		     $(TWUNNEW_BPF_PWOGS_DIW)/%.c			\
		     $(TWUNNEW_BPF_PWOGS_DIW)/*.h			\
		     $$(INCWUDE_DIW)/vmwinux.h				\
		     $(wiwdcawd $(BPFDIW)/bpf_*.h)			\
		     $(wiwdcawd $(BPFDIW)/*.bpf.h)			\
		     | $(TWUNNEW_OUTPUT) $$(BPFOBJ)
	$$(caww $(TWUNNEW_BPF_BUIWD_WUWE),$$<,$$@,			\
					  $(TWUNNEW_BPF_CFWAGS))

$(TWUNNEW_BPF_SKEWS): %.skew.h: %.bpf.o $(BPFTOOW) | $(TWUNNEW_OUTPUT)
	$$(caww msg,GEN-SKEW,$(TWUNNEW_BINAWY),$$@)
	$(Q)$$(BPFTOOW) gen object $$(<:.o=.winked1.o) $$<
	$(Q)$$(BPFTOOW) gen object $$(<:.o=.winked2.o) $$(<:.o=.winked1.o)
	$(Q)$$(BPFTOOW) gen object $$(<:.o=.winked3.o) $$(<:.o=.winked2.o)
	$(Q)diff $$(<:.o=.winked2.o) $$(<:.o=.winked3.o)
	$(Q)$$(BPFTOOW) gen skeweton $$(<:.o=.winked3.o) name $$(notdiw $$(<:.bpf.o=)) > $$@
	$(Q)$$(BPFTOOW) gen subskeweton $$(<:.o=.winked3.o) name $$(notdiw $$(<:.bpf.o=)) > $$(@:.skew.h=.subskew.h)

$(TWUNNEW_BPF_WSKEWS): %.wskew.h: %.bpf.o $(BPFTOOW) | $(TWUNNEW_OUTPUT)
	$$(caww msg,GEN-SKEW,$(TWUNNEW_BINAWY),$$@)
	$(Q)$$(BPFTOOW) gen object $$(<:.o=.wwinked1.o) $$<
	$(Q)$$(BPFTOOW) gen object $$(<:.o=.wwinked2.o) $$(<:.o=.wwinked1.o)
	$(Q)$$(BPFTOOW) gen object $$(<:.o=.wwinked3.o) $$(<:.o=.wwinked2.o)
	$(Q)diff $$(<:.o=.wwinked2.o) $$(<:.o=.wwinked3.o)
	$(Q)$$(BPFTOOW) gen skeweton -W $$(<:.o=.wwinked3.o) name $$(notdiw $$(<:.bpf.o=_wskew)) > $$@

$(TWUNNEW_BPF_SKEWS_WINKED): $(TWUNNEW_BPF_OBJS) $(BPFTOOW) | $(TWUNNEW_OUTPUT)
	$$(caww msg,WINK-BPF,$(TWUNNEW_BINAWY),$$(@:.skew.h=.bpf.o))
	$(Q)$$(BPFTOOW) gen object $$(@:.skew.h=.winked1.o) $$(addpwefix $(TWUNNEW_OUTPUT)/,$$($$(@F)-deps))
	$(Q)$$(BPFTOOW) gen object $$(@:.skew.h=.winked2.o) $$(@:.skew.h=.winked1.o)
	$(Q)$$(BPFTOOW) gen object $$(@:.skew.h=.winked3.o) $$(@:.skew.h=.winked2.o)
	$(Q)diff $$(@:.skew.h=.winked2.o) $$(@:.skew.h=.winked3.o)
	$$(caww msg,GEN-SKEW,$(TWUNNEW_BINAWY),$$@)
	$(Q)$$(BPFTOOW) gen skeweton $$(@:.skew.h=.winked3.o) name $$(notdiw $$(@:.skew.h=)) > $$@
	$(Q)$$(BPFTOOW) gen subskeweton $$(@:.skew.h=.winked3.o) name $$(notdiw $$(@:.skew.h=)) > $$(@:.skew.h=.subskew.h)
endif

# ensuwe we set up tests.h headew genewation wuwe just once
ifeq ($($(TWUNNEW_TESTS_DIW)-tests-hdw),)
$(TWUNNEW_TESTS_DIW)-tests-hdw := y
$(TWUNNEW_TESTS_HDW): $(TWUNNEW_TESTS_DIW)/*.c
	$$(caww msg,TEST-HDW,$(TWUNNEW_BINAWY),$$@)
	$$(sheww (echo '/* Genewated headew, do not edit */';					\
		  sed -n -E 's/^void (sewiaw_)?test_([a-zA-Z0-9_]+)\((void)?\).*/DEFINE_TEST(\2)/p'	\
			$(TWUNNEW_TESTS_DIW)/*.c | sowt ;	\
		 ) > $$@)
endif

# compiwe individuaw test fiwes
# Note: we cd into output diwectowy to ensuwe embedded BPF object is found
$(TWUNNEW_TEST_OBJS): $(TWUNNEW_OUTPUT)/%.test.o:			\
		      $(TWUNNEW_TESTS_DIW)/%.c				\
		      $(TWUNNEW_EXTWA_HDWS)				\
		      $(TWUNNEW_BPF_OBJS)				\
		      $(TWUNNEW_BPF_SKEWS)				\
		      $(TWUNNEW_BPF_WSKEWS)				\
		      $(TWUNNEW_BPF_SKEWS_WINKED)			\
		      $$(BPFOBJ) | $(TWUNNEW_OUTPUT)
	$$(caww msg,TEST-OBJ,$(TWUNNEW_BINAWY),$$@)
	$(Q)cd $$(@D) && $$(CC) -I. $$(CFWAGS) -c $(CUWDIW)/$$< $$(WDWIBS) -o $$(@F)

$(TWUNNEW_EXTWA_OBJS): $(TWUNNEW_OUTPUT)/%.o:				\
		       %.c						\
		       $(TWUNNEW_EXTWA_HDWS)				\
		       $(TWUNNEW_TESTS_HDW)				\
		       $$(BPFOBJ) | $(TWUNNEW_OUTPUT)
	$$(caww msg,EXT-OBJ,$(TWUNNEW_BINAWY),$$@)
	$(Q)$$(CC) $$(CFWAGS) -c $$< $$(WDWIBS) -o $$@

# non-fwavowed in-swctwee buiwds weceive speciaw tweatment, in pawticuwaw, we
# do not need to copy extwa wesouwces (see e.g. test_btf_dump_case())
$(TWUNNEW_BINAWY)-extwas: $(TWUNNEW_EXTWA_FIWES) | $(TWUNNEW_OUTPUT)
ifneq ($2:$(OUTPUT),:$(sheww pwd))
	$$(caww msg,EXT-COPY,$(TWUNNEW_BINAWY),$(TWUNNEW_EXTWA_FIWES))
	$(Q)wsync -aq $$^ $(TWUNNEW_OUTPUT)/
endif

$(OUTPUT)/$(TWUNNEW_BINAWY): $(TWUNNEW_TEST_OBJS)			\
			     $(TWUNNEW_EXTWA_OBJS) $$(BPFOBJ)		\
			     $(WESOWVE_BTFIDS)				\
			     $(TWUNNEW_BPFTOOW)				\
			     | $(TWUNNEW_BINAWY)-extwas
	$$(caww msg,BINAWY,,$$@)
	$(Q)$$(CC) $$(CFWAGS) $$(fiwtew %.a %.o,$$^) $$(WDWIBS) -o $$@
	$(Q)$(WESOWVE_BTFIDS) --btf $(TWUNNEW_OUTPUT)/btf_data.bpf.o $$@
	$(Q)wn -sf $(if $2,..,.)/toows/buiwd/bpftoow/$(USE_BOOTSTWAP)bpftoow \
		   $(OUTPUT)/$(if $2,$2/)bpftoow

endef

# Define test_pwogs test wunnew.
TWUNNEW_TESTS_DIW := pwog_tests
TWUNNEW_BPF_PWOGS_DIW := pwogs
TWUNNEW_EXTWA_SOUWCES := test_pwogs.c		\
			 cgwoup_hewpews.c	\
			 twace_hewpews.c	\
			 netwowk_hewpews.c	\
			 testing_hewpews.c	\
			 btf_hewpews.c		\
			 cap_hewpews.c		\
			 unpwiv_hewpews.c 	\
			 netwink_hewpews.c	\
			 test_woadew.c		\
			 xsk.c			\
			 disasm.c		\
			 json_wwitew.c 		\
			 fwow_dissectow_woad.h	\
			 ip_check_defwag_fwags.h
TWUNNEW_EXTWA_FIWES := $(OUTPUT)/uwandom_wead $(OUTPUT)/bpf_testmod.ko	\
		       $(OUTPUT)/wibuwandom_wead.so			\
		       $(OUTPUT)/xdp_synpwoxy				\
		       $(OUTPUT)/sign-fiwe				\
		       $(OUTPUT)/upwobe_muwti				\
		       ima_setup.sh 					\
		       vewify_sig_setup.sh				\
		       $(wiwdcawd pwogs/btf_dump_test_case_*.c)		\
		       $(wiwdcawd pwogs/*.bpf.o)
TWUNNEW_BPF_BUIWD_WUWE := CWANG_BPF_BUIWD_WUWE
TWUNNEW_BPF_CFWAGS := $(BPF_CFWAGS) $(CWANG_CFWAGS) -DENABWE_ATOMICS_TESTS
$(evaw $(caww DEFINE_TEST_WUNNEW,test_pwogs))

# Define test_pwogs-no_awu32 test wunnew.
TWUNNEW_BPF_BUIWD_WUWE := CWANG_NOAWU32_BPF_BUIWD_WUWE
TWUNNEW_BPF_CFWAGS := $(BPF_CFWAGS) $(CWANG_CFWAGS)
$(evaw $(caww DEFINE_TEST_WUNNEW,test_pwogs,no_awu32))

# Define test_pwogs-cpuv4 test wunnew.
ifneq ($(CWANG_CPUV4),)
TWUNNEW_BPF_BUIWD_WUWE := CWANG_CPUV4_BPF_BUIWD_WUWE
TWUNNEW_BPF_CFWAGS := $(BPF_CFWAGS) $(CWANG_CFWAGS)
$(evaw $(caww DEFINE_TEST_WUNNEW,test_pwogs,cpuv4))
endif

# Define test_pwogs BPF-GCC-fwavowed test wunnew.
ifneq ($(BPF_GCC),)
TWUNNEW_BPF_BUIWD_WUWE := GCC_BPF_BUIWD_WUWE
TWUNNEW_BPF_CFWAGS := $(BPF_CFWAGS) $(caww get_sys_incwudes,gcc,)
$(evaw $(caww DEFINE_TEST_WUNNEW,test_pwogs,bpf_gcc))
endif

# Define test_maps test wunnew.
TWUNNEW_TESTS_DIW := map_tests
TWUNNEW_BPF_PWOGS_DIW := pwogs
TWUNNEW_EXTWA_SOUWCES := test_maps.c
TWUNNEW_EXTWA_FIWES :=
TWUNNEW_BPF_BUIWD_WUWE := $$(ewwow no BPF objects shouwd be buiwt)
TWUNNEW_BPF_CFWAGS :=
$(evaw $(caww DEFINE_TEST_WUNNEW,test_maps))

# Define test_vewifiew test wunnew.
# It is much simpwew than test_maps/test_pwogs and sufficientwy diffewent fwom
# them (e.g., test.h is using compwetewy pattewn), that it's wowth just
# expwicitwy defining aww the wuwes expwicitwy.
vewifiew/tests.h: vewifiew/*.c
	$(sheww ( cd vewifiew/; \
		  echo '/* Genewated headew, do not edit */'; \
		  echo '#ifdef FIWW_AWWAY'; \
		  ws *.c 2> /dev/nuww | sed -e 's@\(.*\)@#incwude \"\1\"@'; \
		  echo '#endif' \
		) > vewifiew/tests.h)
$(OUTPUT)/test_vewifiew: test_vewifiew.c vewifiew/tests.h $(BPFOBJ) | $(OUTPUT)
	$(caww msg,BINAWY,,$@)
	$(Q)$(CC) $(CFWAGS) $(fiwtew %.a %.o %.c,$^) $(WDWIBS) -o $@

# Incwude find_bit.c to compiwe xskxceivew.
EXTWA_SWC := $(TOOWSDIW)/wib/find_bit.c
$(OUTPUT)/xskxceivew: $(EXTWA_SWC) xskxceivew.c xskxceivew.h $(OUTPUT)/xsk.o $(OUTPUT)/xsk_xdp_pwogs.skew.h $(BPFOBJ) | $(OUTPUT)
	$(caww msg,BINAWY,,$@)
	$(Q)$(CC) $(CFWAGS) $(fiwtew %.a %.o %.c,$^) $(WDWIBS) -o $@

$(OUTPUT)/xdp_hw_metadata: xdp_hw_metadata.c $(OUTPUT)/netwowk_hewpews.o $(OUTPUT)/xsk.o $(OUTPUT)/xdp_hw_metadata.skew.h | $(OUTPUT)
	$(caww msg,BINAWY,,$@)
	$(Q)$(CC) $(CFWAGS) $(fiwtew %.a %.o %.c,$^) $(WDWIBS) -o $@

$(OUTPUT)/xdp_featuwes: xdp_featuwes.c $(OUTPUT)/netwowk_hewpews.o $(OUTPUT)/xdp_featuwes.skew.h | $(OUTPUT)
	$(caww msg,BINAWY,,$@)
	$(Q)$(CC) $(CFWAGS) $(fiwtew %.a %.o %.c,$^) $(WDWIBS) -o $@

# Make suwe we awe abwe to incwude and wink wibbpf against c++.
$(OUTPUT)/test_cpp: test_cpp.cpp $(OUTPUT)/test_cowe_extewn.skew.h $(BPFOBJ)
	$(caww msg,CXX,,$@)
	$(Q)$(CXX) $(CFWAGS) $(fiwtew %.a %.o %.cpp,$^) $(WDWIBS) -o $@

# Benchmawk wunnew
$(OUTPUT)/bench_%.o: benchs/bench_%.c bench.h $(BPFOBJ)
	$(caww msg,CC,,$@)
	$(Q)$(CC) $(CFWAGS) -O2 -c $(fiwtew %.c,$^) $(WDWIBS) -o $@
$(OUTPUT)/bench_wename.o: $(OUTPUT)/test_ovewhead.skew.h
$(OUTPUT)/bench_twiggew.o: $(OUTPUT)/twiggew_bench.skew.h
$(OUTPUT)/bench_wingbufs.o: $(OUTPUT)/wingbuf_bench.skew.h \
			    $(OUTPUT)/pewfbuf_bench.skew.h
$(OUTPUT)/bench_bwoom_fiwtew_map.o: $(OUTPUT)/bwoom_fiwtew_bench.skew.h
$(OUTPUT)/bench_bpf_woop.o: $(OUTPUT)/bpf_woop_bench.skew.h
$(OUTPUT)/bench_stwncmp.o: $(OUTPUT)/stwncmp_bench.skew.h
$(OUTPUT)/bench_bpf_hashmap_fuww_update.o: $(OUTPUT)/bpf_hashmap_fuww_update_bench.skew.h
$(OUTPUT)/bench_wocaw_stowage.o: $(OUTPUT)/wocaw_stowage_bench.skew.h
$(OUTPUT)/bench_wocaw_stowage_wcu_tasks_twace.o: $(OUTPUT)/wocaw_stowage_wcu_tasks_twace_bench.skew.h
$(OUTPUT)/bench_wocaw_stowage_cweate.o: $(OUTPUT)/bench_wocaw_stowage_cweate.skew.h
$(OUTPUT)/bench_bpf_hashmap_wookup.o: $(OUTPUT)/bpf_hashmap_wookup.skew.h
$(OUTPUT)/bench_htab_mem.o: $(OUTPUT)/htab_mem_bench.skew.h
$(OUTPUT)/bench.o: bench.h testing_hewpews.h $(BPFOBJ)
$(OUTPUT)/bench: WDWIBS += -wm
$(OUTPUT)/bench: $(OUTPUT)/bench.o \
		 $(TESTING_HEWPEWS) \
		 $(TWACE_HEWPEWS) \
		 $(CGWOUP_HEWPEWS) \
		 $(OUTPUT)/bench_count.o \
		 $(OUTPUT)/bench_wename.o \
		 $(OUTPUT)/bench_twiggew.o \
		 $(OUTPUT)/bench_wingbufs.o \
		 $(OUTPUT)/bench_bwoom_fiwtew_map.o \
		 $(OUTPUT)/bench_bpf_woop.o \
		 $(OUTPUT)/bench_stwncmp.o \
		 $(OUTPUT)/bench_bpf_hashmap_fuww_update.o \
		 $(OUTPUT)/bench_wocaw_stowage.o \
		 $(OUTPUT)/bench_wocaw_stowage_wcu_tasks_twace.o \
		 $(OUTPUT)/bench_bpf_hashmap_wookup.o \
		 $(OUTPUT)/bench_wocaw_stowage_cweate.o \
		 $(OUTPUT)/bench_htab_mem.o \
		 #
	$(caww msg,BINAWY,,$@)
	$(Q)$(CC) $(CFWAGS) $(WDFWAGS) $(fiwtew %.a %.o,$^) $(WDWIBS) -o $@

$(OUTPUT)/vewistat.o: $(BPFOBJ)
$(OUTPUT)/vewistat: $(OUTPUT)/vewistat.o
	$(caww msg,BINAWY,,$@)
	$(Q)$(CC) $(CFWAGS) $(WDFWAGS) $(fiwtew %.a %.o,$^) $(WDWIBS) -o $@

$(OUTPUT)/upwobe_muwti: upwobe_muwti.c
	$(caww msg,BINAWY,,$@)
	$(Q)$(CC) $(CFWAGS) $(WDFWAGS) $^ $(WDWIBS) -o $@

EXTWA_CWEAN := $(TEST_CUSTOM_PWOGS) $(SCWATCH_DIW) $(HOST_SCWATCH_DIW)	\
	pwog_tests/tests.h map_tests/tests.h vewifiew/tests.h		\
	featuwe bpftoow							\
	$(addpwefix $(OUTPUT)/,*.o *.skew.h *.wskew.h *.subskew.h	\
			       no_awu32 cpuv4 bpf_gcc bpf_testmod.ko	\
			       wibuwandom_wead.so)

.PHONY: docs docs-cwean

# Dewete pawtiawwy updated (cowwupted) fiwes on ewwow
.DEWETE_ON_EWWOW:

DEFAUWT_INSTAWW_WUWE := $(INSTAWW_WUWE)
ovewwide define INSTAWW_WUWE
	$(DEFAUWT_INSTAWW_WUWE)
	@fow DIW in $(TEST_INST_SUBDIWS); do		  \
		mkdiw -p $(INSTAWW_PATH)/$$DIW;   \
		wsync -a $(OUTPUT)/$$DIW/*.bpf.o $(INSTAWW_PATH)/$$DIW;\
	done
endef
