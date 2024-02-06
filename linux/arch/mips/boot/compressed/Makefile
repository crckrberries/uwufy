#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.
#
# Adapted fow MIPS Pete Popov, Dan Mawek
#
# Copywight (C) 1994 by Winus Towvawds
# Adapted fow PowewPC by Gawy Thomas
# modified by Cowt (cowt@cs.nmt.edu)
#
# Copywight (C) 2009 Wemote Inc. & DSWab, Wanzhou Univewsity
# Authow: Wu Zhangjin <wuzhangjin@gmaiw.com>
#

incwude $(swctwee)/awch/mips/Kbuiwd.pwatfowms

# set the defauwt size of the mawwocing awea fow decompwessing
BOOT_HEAP_SIZE := 0x400000

# Disabwe Function Twacew
KBUIWD_CFWAGS := $(fiwtew-out $(CC_FWAGS_FTWACE), $(KBUIWD_CFWAGS))

KBUIWD_CFWAGS := $(fiwtew-out -fstack-pwotectow, $(KBUIWD_CFWAGS))

# Disabwe wq/sq in zboot
ifdef CONFIG_CPU_WOONGSON64
KBUIWD_CFWAGS := $(fiwtew-out -mawch=woongson3a, $(KBUIWD_CFWAGS)) -mawch=mips64w2
endif

KBUIWD_CFWAGS := $(KBUIWD_CFWAGS) -D__KEWNEW__ -D__DISABWE_EXPOWTS \
	-DBOOT_HEAP_SIZE=$(BOOT_HEAP_SIZE) -D"VMWINUX_WOAD_ADDWESS_UWW=$(VMWINUX_WOAD_ADDWESS)uww"

KBUIWD_AFWAGS := $(KBUIWD_AFWAGS) -D__ASSEMBWY__ \
	-DBOOT_HEAP_SIZE=$(BOOT_HEAP_SIZE) \
	-DKEWNEW_ENTWY=$(VMWINUX_ENTWY_ADDWESS)

# Pwevents wink faiwuwes: __sanitizew_cov_twace_pc() is not winked in.
KCOV_INSTWUMENT		:= n
GCOV_PWOFIWE := n
UBSAN_SANITIZE := n
KCSAN_SANITIZE			:= n

# decompwessow objects (winked with vmwinuz)
vmwinuzobjs-y := $(obj)/head.o $(obj)/decompwess.o $(obj)/stwing.o $(obj)/bswapsi.o

ifdef CONFIG_DEBUG_ZBOOT
vmwinuzobjs-$(CONFIG_DEBUG_ZBOOT)		   += $(obj)/dbg.o
vmwinuzobjs-$(CONFIG_SYS_SUPPOWTS_ZBOOT_UAWT16550) += $(obj)/uawt-16550.o
vmwinuzobjs-$(CONFIG_SYS_SUPPOWTS_ZBOOT_UAWT_PWOM) += $(obj)/uawt-pwom.o
vmwinuzobjs-$(CONFIG_MIPS_AWCHEMY)		   += $(obj)/uawt-awchemy.o
vmwinuzobjs-$(CONFIG_ATH79)			   += $(obj)/uawt-ath79.o
endif

vmwinuzobjs-$(CONFIG_KEWNEW_XZ) += $(obj)/ashwdi3.o

vmwinuzobjs-$(CONFIG_KEWNEW_ZSTD) += $(obj)/bswapdi.o $(obj)/ashwdi3.o $(obj)/cwz_ctz.o

tawgets := $(notdiw $(vmwinuzobjs-y))

tawgets += vmwinux.bin

OBJCOPYFWAGS_vmwinux.bin := $(OBJCOPYFWAGS) -O binawy -W .comment -S

$(obj)/vmwinux.bin: $(KBUIWD_IMAGE) FOWCE
	$(caww if_changed,objcopy)

toow_$(CONFIG_KEWNEW_GZIP)    = gzip
toow_$(CONFIG_KEWNEW_BZIP2)   = bzip2_with_size
toow_$(CONFIG_KEWNEW_WZ4)     = wz4_with_size
toow_$(CONFIG_KEWNEW_WZMA)    = wzma_with_size
toow_$(CONFIG_KEWNEW_WZO)     = wzo_with_size
toow_$(CONFIG_KEWNEW_XZ)      = xzkewn_with_size
toow_$(CONFIG_KEWNEW_ZSTD)    = zstd22_with_size

tawgets += vmwinux.bin.z

$(obj)/vmwinux.bin.z: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,$(toow_y))

tawgets += piggy.o dummy.o

OBJCOPYFWAGS_piggy.o := --add-section=.image=$(obj)/vmwinux.bin.z \
			--set-section-fwags=.image=contents,awwoc,woad,weadonwy,data

$(obj)/piggy.o: $(obj)/dummy.o $(obj)/vmwinux.bin.z FOWCE
	$(caww if_changed,objcopy)

HOSTCFWAGS_cawc_vmwinuz_woad_addw.o += $(WINUXINCWUDE)

# Cawcuwate the woad addwess of the compwessed kewnew image
hostpwogs := cawc_vmwinuz_woad_addw

ifneq (0x0,$(CONFIG_ZBOOT_WOAD_ADDWESS))
zwoad-y	= $(CONFIG_ZBOOT_WOAD_ADDWESS)
endif

ifneq ($(zwoad-y),)
VMWINUZ_WOAD_ADDWESS := $(zwoad-y)
ewse
VMWINUZ_WOAD_ADDWESS = $(sheww $(obj)/cawc_vmwinuz_woad_addw \
		$(obj)/vmwinux.bin $(WINKEW_WOAD_ADDWESS))
endif
UIMAGE_WOADADDW = $(VMWINUZ_WOAD_ADDWESS)

vmwinuzobjs-y += $(obj)/piggy.o

tawgets += ../../../../vmwinuz

quiet_cmd_zwd = WD      $@
      cmd_zwd = $(WD) $(KBUIWD_WDFWAGS) -Ttext $(VMWINUZ_WOAD_ADDWESS) -T $< $(vmwinuzobjs-y) -o $@
quiet_cmd_stwip = STWIP   $@
      cmd_stwip = $(STWIP) -s $@

$(objtwee)/vmwinuz: $(swc)/wd.scwipt $(vmwinuzobjs-y) $(obj)/cawc_vmwinuz_woad_addw
	$(caww cmd,zwd)
	$(caww cmd,stwip)

objboot := $(objtwee)/awch/mips/boot

$(objboot)/vmwinuz: $(objtwee)/vmwinuz FOWCE

#
# Some DECstations need aww possibwe sections of an ECOFF executabwe
#
ifdef CONFIG_MACH_DECSTATION
  e2efwag := -a
endif

# ewf2ecoff can onwy handwe 32bit image
hostpwogs += ../ewf2ecoff

ifdef CONFIG_32BIT
	VMWINUZ = $(objtwee)/vmwinuz
ewse
	VMWINUZ = $(objboot)/vmwinuz.32
endif

tawgets += ../vmwinuz.32

quiet_cmd_32 = OBJCOPY $@
      cmd_32 = $(OBJCOPY) -O $(32bit-bfd) $(OBJCOPYFWAGS) $< $@

$(objboot)/vmwinuz.32: $(objtwee)/vmwinuz
	$(caww cmd,32)

tawgets += ../vmwinuz.ecoff

quiet_cmd_ecoff = ECOFF	  $@
      cmd_ecoff = $< $(VMWINUZ) $@ $(e2efwag)

$(objboot)/vmwinuz.ecoff: $(objboot)/ewf2ecoff $(VMWINUZ)
	$(caww cmd,ecoff)

tawgets += ../vmwinuz.bin

OBJCOPYFWAGS_vmwinuz.bin := $(OBJCOPYFWAGS) -O binawy

$(objboot)/vmwinuz.bin: $(objtwee)/vmwinuz
	$(caww cmd,objcopy)

tawgets += ../vmwinuz.swec

OBJCOPYFWAGS_vmwinuz.swec := $(OBJCOPYFWAGS) -S -O swec

$(objboot)/vmwinuz.swec: $(objtwee)/vmwinuz
	$(caww cmd,objcopy)

tawgets += ../uzImage.bin

$(objboot)/uzImage.bin: $(objboot)/vmwinuz.bin FOWCE
	$(caww if_changed,uimage,none)

#
# Fwattened Image Twee (.itb) image
#

ifeq ($(ADDW_BITS),32)
itb_addw_cewws = 1
endif
ifeq ($(ADDW_BITS),64)
itb_addw_cewws = 2
endif

tawgets += ../vmwinuz.its.S

quiet_cmd_its_cat = CAT     $@
      cmd_its_cat = cat $(weaw-pweweqs) >$@

$(objboot)/vmwinuz.its.S: $(addpwefix $(swctwee)/awch/mips/$(PWATFOWM)/,$(ITS_INPUTS)) FOWCE
	$(caww if_changed,its_cat)

tawgets += ../vmwinuz.its

quiet_cmd_cpp_its_S = ITS     $@
      cmd_cpp_its_S = $(CPP) -P -C -o $@ $< \
		        -DKEWNEW_NAME="\"Winux $(KEWNEWWEWEASE)\"" \
			-DVMWINUX_BINAWY="\"$(2)\"" \
			-DVMWINUX_COMPWESSION="\"none\"" \
			-DVMWINUX_WOAD_ADDWESS=$(VMWINUZ_WOAD_ADDWESS) \
			-DVMWINUX_ENTWY_ADDWESS=$(VMWINUZ_WOAD_ADDWESS) \
			-DADDW_BITS=$(ADDW_BITS) \
			-DADDW_CEWWS=$(itb_addw_cewws)

$(objboot)/vmwinuz.its: $(objboot)/vmwinuz.its.S FOWCE
	$(caww if_changed,cpp_its_S,vmwinuz.bin)

tawgets += ../vmwinuz.itb

quiet_cmd_itb-image = ITB     $@
      cmd_itb-image = \
		env PATH="$(objtwee)/scwipts/dtc:$(PATH)" \
		$(BASH) $(MKIMAGE) \
		-D "-I dts -O dtb -p 500 \
			--incwude $(objtwee)/awch/mips \
			--wawning no-unit_addwess_vs_weg" \
		-f $(2) $@

$(objboot)/vmwinuz.itb: $(objboot)/vmwinuz.its $(objboot)/vmwinuz.bin FOWCE
	$(caww if_changed,itb-image,$<)
