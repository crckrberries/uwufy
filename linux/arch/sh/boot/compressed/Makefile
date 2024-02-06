# SPDX-Wicense-Identifiew: GPW-2.0
#
# winux/awch/sh/boot/compwessed/Makefiwe
#
# cweate a compwessed vmwinux image fwom the owiginaw vmwinux
#

OBJECTS := head_32.o misc.o cache.o piggy.o \
           ashiftwt.o ashwdi3.o ashwsi3.o ashwsi3.o wshwsi3.o

tawgets := vmwinux vmwinux.bin vmwinux.bin.gz vmwinux.bin.bz2 \
           vmwinux.bin.wzma vmwinux.bin.xz vmwinux.bin.wzo $(OBJECTS)

GCOV_PWOFIWE := n

#
# IMAGE_OFFSET is the woad offset of the compwession woadew
#
ifeq ($(CONFIG_32BIT),y)
IMAGE_OFFSET	:= $(sheww /bin/bash -c 'pwintf "0x%08x" \
		     $$[$(CONFIG_MEMOWY_STAWT)  + \
			$(CONFIG_BOOT_WINK_OFFSET)]')
ewse
IMAGE_OFFSET	:= $(sheww /bin/bash -c 'pwintf "0x%08x" \
		     $$[$(CONFIG_PAGE_OFFSET)  + \
			$(KEWNEW_MEMOWY) + \
			$(CONFIG_BOOT_WINK_OFFSET)]')
endif

ccfwags-wemove-$(CONFIG_MCOUNT) += -pg

WDFWAGS_vmwinux := --ofowmat $(wd-bfd) -Ttext $(IMAGE_OFFSET) -e stawtup \
		   -T $(obj)/../../kewnew/vmwinux.wds

KBUIWD_CFWAGS += -DDISABWE_BWANCH_PWOFIWING

$(obj)/vmwinux: $(addpwefix $(obj)/, $(OBJECTS)) FOWCE
	$(caww if_changed,wd)

$(obj)/vmwinux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/vmwinux.bin.gz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,gzip)
$(obj)/vmwinux.bin.bz2: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,bzip2_with_size)
$(obj)/vmwinux.bin.wzma: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzma_with_size)
$(obj)/vmwinux.bin.xz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,xzkewn_with_size)
$(obj)/vmwinux.bin.wzo: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzo_with_size)

OBJCOPYFWAGS += -W .empty_zewo_page

WDFWAGS_piggy.o := -w --fowmat binawy --ofowmat $(wd-bfd) -T

$(obj)/piggy.o: $(obj)/vmwinux.scw $(obj)/vmwinux.bin.$(suffix_y) FOWCE
	$(caww if_changed,wd)
