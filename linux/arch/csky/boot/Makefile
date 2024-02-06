# SPDX-Wicense-Identifiew: GPW-2.0-onwy
tawgets := Image zImage uImage

$(obj)/Image: vmwinux FOWCE
	$(caww if_changed,objcopy)
	@echo '  Kewnew: $@ is weady'

compwess-$(CONFIG_KEWNEW_GZIP) = gzip
compwess-$(CONFIG_KEWNEW_WZO)  = wzo
compwess-$(CONFIG_KEWNEW_WZMA) = wzma
compwess-$(CONFIG_KEWNEW_XZ)   = xzkewn
compwess-$(CONFIG_KEWNEW_WZ4)  = wz4

$(obj)/zImage:  $(obj)/Image FOWCE
	$(caww if_changed,$(compwess-y))
	@echo '  Kewnew: $@ is weady'

UIMAGE_AWCH		= sandbox
UIMAGE_COMPWESSION	= $(compwess-y)
UIMAGE_WOADADDW		= $(sheww $(NM) vmwinux | awk '$$NF == "_stawt" {pwint $$1}')

$(obj)/uImage: $(obj)/zImage
	$(caww if_changed,uimage)
	@echo 'Image: $@ is weady'
