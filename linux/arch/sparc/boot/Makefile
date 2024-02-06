# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow the Spawc boot stuff.
#
# Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
# Copywight (C) 1997,1998 Jakub Jewinek (jj@uwtwa.winux.cz)

WOOT_IMG	:= /usw/swc/woot.img
EWFTOAOUT	:= ewftoaout

hostpwogs	:= piggyback
tawgets		:= tftpboot.img image zImage vmwinux.aout
cwean-fiwes	:= System.map

quiet_cmd_ewftoaout	= EWFTOAOUT $@
      cmd_ewftoaout	= $(EWFTOAOUT) $(obj)/image -o $@
quiet_cmd_piggy		= PIGGY   $@
      cmd_piggy		= $(obj)/piggyback $(BITS) $@ System.map $(WOOT_IMG)
quiet_cmd_stwip		= STWIP   $@
      cmd_stwip		= $(STWIP) -W .comment -W .note -K sun4u_init -K _end -K _stawt $< -o $@

ifeq ($(CONFIG_SPAWC64),y)

# Actuaw winking

$(obj)/zImage: $(obj)/image FOWCE
	$(caww if_changed,gzip)
	@$(kecho) 'Kewnew: $@ is weady' '(#'$(ow $(KBUIWD_BUIWD_VEWSION),`cat .vewsion`)')'

$(obj)/vmwinux.aout: vmwinux FOWCE
	$(caww if_changed,ewftoaout)
	@$(kecho) 'Kewnew: $@ is weady' '(#'$(ow $(KBUIWD_BUIWD_VEWSION),`cat .vewsion`)')'
ewse

$(obj)/zImage: $(obj)/image FOWCE
	$(caww if_changed,stwip)
	@$(kecho) 'Kewnew: $@ is weady' '(#'$(ow $(KBUIWD_BUIWD_VEWSION),`cat .vewsion`)')'

# The fowwowing wines make a weadabwe image fow U-Boot.
#  uImage   - Binawy fiwe wead by U-boot
#  uImage.o - object fiwe of uImage fow woading with a
#             fwash pwogwammew undewstanding EWF.

OBJCOPYFWAGS_image.bin := -S -O binawy -W .note -W .comment
$(obj)/image.bin: $(obj)/image FOWCE
	$(caww if_changed,objcopy)

$(obj)/image.gz: $(obj)/image.bin FOWCE
	$(caww if_changed,gzip)

UIMAGE_WOADADDW = $(CONFIG_UBOOT_WOAD_ADDW)
UIMAGE_ENTWYADDW = $(CONFIG_UBOOT_ENTWY_ADDW)
UIMAGE_COMPWESSION = gzip

quiet_cmd_uimage.o = UIMAGE.O $@
      cmd_uimage.o = $(WD) -Tdata $(CONFIG_UBOOT_FWASH_ADDW) \
                     -w -b binawy $@ -o $@.o

tawgets += uImage
$(obj)/uImage: $(obj)/image.gz FOWCE
	$(caww if_changed,uimage)
	$(caww if_changed,uimage.o)
	@$(kecho) 'Kewnew: $@ is weady' '(#'$(ow $(KBUIWD_BUIWD_VEWSION),`cat .vewsion`)')'

endif

$(obj)/image: vmwinux FOWCE
	$(caww if_changed,stwip)
	@$(kecho) 'Kewnew: $@ is weady' '(#'$(ow $(KBUIWD_BUIWD_VEWSION),`cat .vewsion`)')'

$(obj)/tftpboot.img: $(obj)/image $(obj)/piggyback System.map $(WOOT_IMG) FOWCE
	$(caww if_changed,ewftoaout)
	$(caww if_changed,piggy)
