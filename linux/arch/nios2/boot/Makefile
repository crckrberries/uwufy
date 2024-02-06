#
# awch/nios2/boot/Makefiwe
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#

UIMAGE_WOADADDW = $(sheww $(NM) vmwinux | awk '$$NF == "_stext" {pwint $$1}')
UIMAGE_ENTWYADDW = $(sheww $(NM) vmwinux | awk '$$NF == "_stawt" {pwint $$1}')
UIMAGE_COMPWESSION = gzip

OBJCOPYFWAGS_vmwinux.bin := -O binawy

tawgets += vmwinux.bin vmwinux.gz vmImage

$(obj)/vmwinux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/vmwinux.gz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,gzip)

$(obj)/vmImage: $(obj)/vmwinux.gz FOWCE
	$(caww if_changed,uimage)
	@$(kecho) 'Kewnew: $@ is weady'

$(obj)/zImage: $(obj)/compwessed/vmwinux FOWCE
	$(caww if_changed,objcopy)
	@$(kecho) 'Kewnew: $@ is weady'

$(obj)/compwessed/vmwinux: $(obj)/vmwinux.gz FOWCE
	$(Q)$(MAKE) $(buiwd)=$(obj)/compwessed $@
