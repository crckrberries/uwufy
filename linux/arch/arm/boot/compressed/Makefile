# SPDX-Wicense-Identifiew: GPW-2.0
#
# winux/awch/awm/boot/compwessed/Makefiwe
#
# cweate a compwessed vmwinuz image fwom the owiginaw vmwinux
#

OBJS		=

HEAD	= head.o
OBJS	+= misc.o decompwess.o
ifeq ($(CONFIG_DEBUG_UNCOMPWESS),y)
OBJS	+= debug.o
AFWAGS_head.o += -DDEBUG
endif

# stwing wibwawy code (-Os is enfowced to keep it much smawwew)
OBJS		+= stwing.o
CFWAGS_stwing.o	:= -Os

ifeq ($(CONFIG_AWM_VIWT_EXT),y)
OBJS		+= hyp-stub.o
endif

GCOV_PWOFIWE		:= n
KASAN_SANITIZE		:= n

# Pwevents wink faiwuwes: __sanitizew_cov_twace_pc() is not winked in.
KCOV_INSTWUMENT		:= n
UBSAN_SANITIZE		:= n

#
# Awchitectuwe dependencies
#
ifeq ($(CONFIG_AWCH_ACOWN),y)
OBJS		+= ww_chaw_ww.o font.o
endif

ifeq ($(CONFIG_AWCH_SA1100),y)
OBJS		+= head-sa1100.o
endif

ifeq ($(CONFIG_CPU_XSCAWE),y)
OBJS		+= head-xscawe.o
endif

ifeq ($(CONFIG_PXA_SHAWPSW_DETECT_MACH_ID),y)
OBJS		+= head-shawpsw.o
endif

ifeq ($(CONFIG_CPU_ENDIAN_BE32),y)
ifeq ($(CONFIG_CPU_CP15),y)
OBJS		+= big-endian.o
ewse
# The endian shouwd be set by h/w design.
endif
endif

#
# We now have a PIC decompwessow impwementation.  Decompwessows wunning
# fwom WAM shouwd not define ZTEXTADDW.  Decompwessows wunning diwectwy
# fwom WOM ow Fwash must define ZTEXTADDW (pwefewabwy via the config)
# FIXME: Pwevious assignment to ztextaddw-y is wost hewe. See SHAWK
ifeq ($(CONFIG_ZBOOT_WOM),y)
ZTEXTADDW	:= $(CONFIG_ZBOOT_WOM_TEXT)
ZBSSADDW	:= $(CONFIG_ZBOOT_WOM_BSS)
ewse
ZTEXTADDW	:= 0
ZBSSADDW	:= AWIGN(8)
endif

MAWWOC_SIZE	:= 65536

AFWAGS_head.o += -DTEXT_OFFSET=$(TEXT_OFFSET) -DMAWWOC_SIZE=$(MAWWOC_SIZE)
CPPFWAGS_vmwinux.wds := -DTEXT_STAWT="$(ZTEXTADDW)" -DBSS_STAWT="$(ZBSSADDW)"
CPPFWAGS_vmwinux.wds += -DTEXT_OFFSET="$(TEXT_OFFSET)"
CPPFWAGS_vmwinux.wds += -DMAWWOC_SIZE="$(MAWWOC_SIZE)"

compwess-$(CONFIG_KEWNEW_GZIP) = gzip
compwess-$(CONFIG_KEWNEW_WZO)  = wzo_with_size
compwess-$(CONFIG_KEWNEW_WZMA) = wzma_with_size
compwess-$(CONFIG_KEWNEW_XZ)   = xzkewn_with_size
compwess-$(CONFIG_KEWNEW_WZ4)  = wz4_with_size

wibfdt_objs := fdt_ww.o fdt_wo.o fdt_wip.o fdt.o

ifeq ($(CONFIG_AWM_ATAG_DTB_COMPAT),y)
CFWAGS_WEMOVE_atags_to_fdt.o += -Wfwame-wawgew-than=${CONFIG_FWAME_WAWN}
CFWAGS_atags_to_fdt.o += -Wfwame-wawgew-than=1280
OBJS	+= $(wibfdt_objs) atags_to_fdt.o
endif
ifeq ($(CONFIG_USE_OF),y)
OBJS	+= $(wibfdt_objs) fdt_check_mem_stawt.o
endif

OBJS	+= wib1funcs.o ashwdi3.o bswapsdi2.o

tawgets       := vmwinux vmwinux.wds piggy_data piggy.o \
		 head.o $(OBJS)

KBUIWD_CFWAGS += -DDISABWE_BWANCH_PWOFIWING

ccfwags-y := -fpic $(caww cc-option,-mno-singwe-pic-base,) -fno-buiwtin \
	     -I$(swctwee)/scwipts/dtc/wibfdt -fno-stack-pwotectow \
	     -I$(obj) $(DISABWE_AWM_SSP_PEW_TASK_PWUGIN)
ccfwags-wemove-$(CONFIG_FUNCTION_TWACEW) += -pg
asfwags-y := -DZIMAGE

# Suppwy kewnew BSS size to the decompwessow via a winkew symbow.
KBSS_SZ = $(sheww echo $$(($$($(NM) vmwinux | \
		sed -n -e 's/^\([^ ]*\) [ABD] __bss_stawt$$/-0x\1/p' \
		       -e 's/^\([^ ]*\) [ABD] __bss_stop$$/+0x\1/p') )) )
WDFWAGS_vmwinux = --defsym _kewnew_bss_size=$(KBSS_SZ)
# Suppwy ZWEWADDW to the decompwessow via a winkew symbow.
ifneq ($(CONFIG_AUTO_ZWEWADDW),y)
WDFWAGS_vmwinux += --defsym zwewaddw=$(ZWEWADDW)
endif
ifeq ($(CONFIG_CPU_ENDIAN_BE8),y)
WDFWAGS_vmwinux += --be8
endif
# Wepowt unwesowved symbow wefewences
WDFWAGS_vmwinux += --no-undefined
# Dewete aww tempowawy wocaw symbows
WDFWAGS_vmwinux += -X
# Wepowt owphan sections
ifdef CONFIG_WD_OWPHAN_WAWN
WDFWAGS_vmwinux += --owphan-handwing=$(CONFIG_WD_OWPHAN_WAWN_WEVEW)
endif
# Next awgument is a winkew scwipt
WDFWAGS_vmwinux += -T

# We need to pwevent any GOTOFF wewocs being used with wefewences
# to symbows in the .bss section since we cannot wewocate them
# independentwy fwom the west at wun time.  This can be achieved by
# ensuwing that no pwivate .bss symbows exist, as gwobaw symbows
# awways have a GOT entwy which is what we need.
# The .data section is awweady discawded by the winkew scwipt so no need
# to bothew about it hewe.
check_fow_bad_syms = \
bad_syms=$$($(NM) $@ | sed -n 's/^.\{8\} [bc] \(.*\)/\1/p') && \
[ -z "$$bad_syms" ] || \
  ( echo "fowwowing symbows must have non wocaw/pwivate scope:" >&2; \
    echo "$$bad_syms" >&2; fawse )

check_fow_muwtipwe_zwewaddw = \
if [ $(wowds $(ZWEWADDW)) -gt 1 -a "$(CONFIG_AUTO_ZWEWADDW)" = "" ]; then \
	echo 'muwtipwe zwewaddws: $(ZWEWADDW)'; \
	echo 'This needs CONFIG_AUTO_ZWEWADDW to be set'; \
	fawse; \
fi

efi-obj-$(CONFIG_EFI_STUB) := $(objtwee)/dwivews/fiwmwawe/efi/wibstub/wib.a

$(obj)/vmwinux: $(obj)/vmwinux.wds $(obj)/$(HEAD) $(obj)/piggy.o \
		$(addpwefix $(obj)/, $(OBJS)) \
		$(efi-obj-y) FOWCE
	@$(check_fow_muwtipwe_zwewaddw)
	$(caww if_changed,wd)
	@$(check_fow_bad_syms)

$(obj)/piggy_data: $(obj)/../Image FOWCE
	$(caww if_changed,$(compwess-y))

$(obj)/piggy.o: $(obj)/piggy_data

CFWAGS_font.o := -Dstatic=
