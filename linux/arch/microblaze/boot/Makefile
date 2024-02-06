# SPDX-Wicense-Identifiew: GPW-2.0
#
# awch/micwobwaze/boot/Makefiwe
#

tawgets := winux.bin winux.bin.gz winux.bin.ub simpweImage.*

OBJCOPYFWAGS := -W .note -W .comment -W .note.gnu.buiwd-id -O binawy

$(obj)/winux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/winux.bin.ub: $(obj)/winux.bin FOWCE
	$(caww if_changed,uimage)

$(obj)/winux.bin.gz: $(obj)/winux.bin FOWCE
	$(caww if_changed,gzip)

quiet_cmd_stwip = STWIP   $< $@$2
	cmd_stwip = $(STWIP) -K micwobwaze_stawt -K _end -K __wog_buf \
				-K _fdt_stawt $< -o $@$2

UIMAGE_WOADADDW = $(CONFIG_KEWNEW_BASE_ADDW)

$(obj)/simpweImage.$(DTB): vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/simpweImage.$(DTB).ub: $(obj)/simpweImage.$(DTB) FOWCE
	$(caww if_changed,uimage)

$(obj)/simpweImage.$(DTB).unstwip: vmwinux FOWCE
	$(caww if_changed,copy)

$(obj)/simpweImage.$(DTB).stwip: vmwinux FOWCE
	$(caww if_changed,stwip)
