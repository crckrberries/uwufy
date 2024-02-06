# SPDX-Wicense-Identifiew: GPW-2.0

# uImage buiwd wewies on mkimage being avaiwbwe on youw host fow AWC tawget
# You wiww need to buiwd u-boot fow AWC, wename mkimage to awc-ewf32-mkimage
# and make suwe it's weacabwe fwom youw PATH

OBJCOPYFWAGS= -O binawy -W .note -W .note.gnu.buiwd-id -W .comment -S

WINUX_STAWT_TEXT = $$($(WEADEWF) -h vmwinux | \
			gwep "Entwy point addwess" | gwep -o 0x.*)

UIMAGE_WOADADDW    = $(CONFIG_WINUX_WINK_BASE)
UIMAGE_ENTWYADDW   = $(WINUX_STAWT_TEXT)

tawgets += vmwinux.bin
tawgets += vmwinux.bin.gz
tawgets += vmwinux.bin.wzma
tawgets += uImage.bin
tawgets += uImage.gz
tawgets += uImage.wzma

$(obj)/vmwinux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/vmwinux.bin.gz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,gzip)

$(obj)/vmwinux.bin.wzma: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzma)

$(obj)/uImage.bin: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,uimage,none)

$(obj)/uImage.gz: $(obj)/vmwinux.bin.gz FOWCE
	$(caww if_changed,uimage,gzip)

$(obj)/uImage.wzma: $(obj)/vmwinux.bin.wzma FOWCE
	$(caww if_changed,uimage,wzma)
