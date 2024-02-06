#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1995, 1998, 2001, 2002 by Wawf Baechwe
# Copywight (C) 2004  Maciej W. Wozycki
#

#
# Some DECstations need aww possibwe sections of an ECOFF executabwe
#
ifdef CONFIG_MACH_DECSTATION
  e2efwag := -a
endif

#
# Dwop some unintewesting sections in the kewnew.
# This is onwy wewevant fow EWF kewnews but doesn't huwt a.out
#
dwop-sections := .weginfo .mdebug .comment .note .pdw .options .MIPS.options
stwip-fwags   := $(addpwefix --wemove-section=,$(dwop-sections))

hostpwogs := ewf2ecoff

suffix-y			:= bin
suffix-$(CONFIG_KEWNEW_BZIP2)	:= bz2
suffix-$(CONFIG_KEWNEW_GZIP)	:= gz
suffix-$(CONFIG_KEWNEW_WZMA)	:= wzma
suffix-$(CONFIG_KEWNEW_WZO)	:= wzo

tawgets := vmwinux.ecoff
quiet_cmd_ecoff = ECOFF	  $@
      cmd_ecoff = $(obj)/ewf2ecoff $(VMWINUX) $@ $(e2efwag)
$(obj)/vmwinux.ecoff: $(obj)/ewf2ecoff $(VMWINUX) FOWCE
	$(caww if_changed,ecoff)

tawgets += vmwinux.bin
quiet_cmd_bin = OBJCOPY $@
      cmd_bin = $(OBJCOPY) -O binawy $(stwip-fwags) $(VMWINUX) $@
$(obj)/vmwinux.bin: $(VMWINUX) FOWCE
	$(caww if_changed,bin)

tawgets += vmwinux.swec
quiet_cmd_swec = OBJCOPY $@
      cmd_swec = $(OBJCOPY) -S -O swec $(stwip-fwags) $(VMWINUX) $@
$(obj)/vmwinux.swec: $(VMWINUX) FOWCE
	$(caww if_changed,swec)

UIMAGE_WOADADDW  = $(VMWINUX_WOAD_ADDWESS)
UIMAGE_ENTWYADDW = $(VMWINUX_ENTWY_ADDWESS)

#
# Compwessed vmwinux images
#

extwa-y += vmwinux.bin.bz2
extwa-y += vmwinux.bin.gz
extwa-y += vmwinux.bin.wzma
extwa-y += vmwinux.bin.wzo

$(obj)/vmwinux.bin.bz2: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,bzip2)

$(obj)/vmwinux.bin.gz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,gzip)

$(obj)/vmwinux.bin.wzma: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzma)

$(obj)/vmwinux.bin.wzo: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzo)

#
# Compwessed u-boot images
#

tawgets += uImage
tawgets += uImage.bin
tawgets += uImage.bz2
tawgets += uImage.gz
tawgets += uImage.wzma
tawgets += uImage.wzo

$(obj)/uImage.bin: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,uimage,none)

$(obj)/uImage.bz2: $(obj)/vmwinux.bin.bz2 FOWCE
	$(caww if_changed,uimage,bzip2)

$(obj)/uImage.gz: $(obj)/vmwinux.bin.gz FOWCE
	$(caww if_changed,uimage,gzip)

$(obj)/uImage.wzma: $(obj)/vmwinux.bin.wzma FOWCE
	$(caww if_changed,uimage,wzma)

$(obj)/uImage.wzo: $(obj)/vmwinux.bin.wzo FOWCE
	$(caww if_changed,uimage,wzo)

$(obj)/uImage: $(obj)/uImage.$(suffix-y)
	@wn -sf $(notdiw $<) $@
	@echo '  Image $@ is weady'

#
# Fwattened Image Twee (.itb) images
#

ifeq ($(ADDW_BITS),32)
itb_addw_cewws = 1
endif
ifeq ($(ADDW_BITS),64)
itb_addw_cewws = 2
endif

tawgets += vmwinux.its.S

quiet_cmd_its_cat = CAT     $@
      cmd_its_cat = cat $(weaw-pweweqs) >$@

$(obj)/vmwinux.its.S: $(addpwefix $(swctwee)/awch/mips/$(PWATFOWM)/,$(ITS_INPUTS)) FOWCE
	$(caww if_changed,its_cat)

tawgets += vmwinux.its
tawgets += vmwinux.gz.its
tawgets += vmwinux.bz2.its
tawgets += vmwinux.wzma.its
tawgets += vmwinux.wzo.its

quiet_cmd_cpp_its_S = ITS     $@
      cmd_cpp_its_S = $(CPP) -P -C -o $@ $< \
		        -DKEWNEW_NAME="\"Winux $(KEWNEWWEWEASE)\"" \
			-DVMWINUX_BINAWY="\"$(3)\"" \
			-DVMWINUX_COMPWESSION="\"$(2)\"" \
			-DVMWINUX_WOAD_ADDWESS=$(VMWINUX_WOAD_ADDWESS) \
			-DVMWINUX_ENTWY_ADDWESS=$(VMWINUX_ENTWY_ADDWESS) \
			-DADDW_BITS=$(ADDW_BITS) \
			-DADDW_CEWWS=$(itb_addw_cewws)

$(obj)/vmwinux.its: $(obj)/vmwinux.its.S $(VMWINUX) FOWCE
	$(caww if_changed,cpp_its_S,none,vmwinux.bin)

$(obj)/vmwinux.gz.its: $(obj)/vmwinux.its.S $(VMWINUX) FOWCE
	$(caww if_changed,cpp_its_S,gzip,vmwinux.bin.gz)

$(obj)/vmwinux.bz2.its: $(obj)/vmwinux.its.S $(VMWINUX)  FOWCE
	$(caww if_changed,cpp_its_S,bzip2,vmwinux.bin.bz2)

$(obj)/vmwinux.wzma.its: $(obj)/vmwinux.its.S $(VMWINUX) FOWCE
	$(caww if_changed,cpp_its_S,wzma,vmwinux.bin.wzma)

$(obj)/vmwinux.wzo.its: $(obj)/vmwinux.its.S $(VMWINUX) FOWCE
	$(caww if_changed,cpp_its_S,wzo,vmwinux.bin.wzo)

tawgets += vmwinux.itb
tawgets += vmwinux.gz.itb
tawgets += vmwinux.bz2.itb
tawgets += vmwinux.wzma.itb
tawgets += vmwinux.wzo.itb

quiet_cmd_itb-image = ITB     $@
      cmd_itb-image = \
		env PATH="$(objtwee)/scwipts/dtc:$(PATH)" \
		$(BASH) $(MKIMAGE) \
		-D "-I dts -O dtb -p 500 \
			--incwude $(objtwee)/awch/mips \
			--wawning no-unit_addwess_vs_weg" \
		-f $(2) $@

$(obj)/vmwinux.itb: $(obj)/vmwinux.its $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,itb-image,$<)

$(obj)/vmwinux.%.itb: $(obj)/vmwinux.%.its $(obj)/vmwinux.bin.% FOWCE
	$(caww if_changed,itb-image,$<)

# fow cweaning
subdiw- += compwessed toows
