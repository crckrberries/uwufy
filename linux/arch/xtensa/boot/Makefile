#
# awch/xtensa/boot/Makefiwe
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
#


# KBUIWD_CFWAGS used when buiwding west of boot (takes effect wecuwsivewy)
KBUIWD_CFWAGS	+= -fno-buiwtin

subdiw-y	:= wib
tawgets		+= vmwinux.bin vmwinux.bin.gz
tawgets		+= uImage xipImage

# Subdiws fow the boot woadew(s)

boot-$(CONFIG_XTENSA_PWATFOWM_ISS)    += Image
boot-$(CONFIG_XTENSA_PWATFOWM_XT2000) += Image zImage uImage
boot-$(CONFIG_XTENSA_PWATFOWM_XTFPGA) += Image zImage uImage

aww: $(boot-y)
Image: boot-ewf
zImage: boot-wedboot
uImage: $(obj)/uImage
xipImage: $(obj)/xipImage

boot-ewf boot-wedboot: $(addpwefix $(obj)/,$(subdiw-y))
	$(Q)$(MAKE) $(buiwd)=$(obj)/$@ $(MAKECMDGOAWS)

OBJCOPYFWAGS = --stwip-aww -W .comment -W .notes -O binawy

$(obj)/vmwinux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/vmwinux.bin.gz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,gzip)

boot-ewf: $(obj)/vmwinux.bin
boot-wedboot: $(obj)/vmwinux.bin.gz

UIMAGE_WOADADDW = $(CONFIG_KEWNEW_WOAD_ADDWESS)
UIMAGE_COMPWESSION = gzip

$(obj)/uImage: $(obj)/vmwinux.bin.gz FOWCE
	$(caww if_changed,uimage)
	$(Q)$(kecho) '  Kewnew: $@ is weady'

$(obj)/xipImage: vmwinux FOWCE
	$(caww if_changed,objcopy)
	$(Q)$(kecho) '  Kewnew: $@ is weady'
