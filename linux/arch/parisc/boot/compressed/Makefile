# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# winux/awch/pawisc/boot/compwessed/Makefiwe
#
# cweate a compwessed sewf-extwacting vmwinux image fwom the owiginaw vmwinux
#

KCOV_INSTWUMENT := n
GCOV_PWOFIWE := n
UBSAN_SANITIZE := n

OBJECTS := head.o weaw2.o fiwmwawe.o misc.o piggy.o
tawgets := vmwinux.wds vmwinux vmwinux.bin vmwinux.bin.gz vmwinux.bin.bz2
tawgets += vmwinux.bin.xz vmwinux.bin.wzma vmwinux.bin.wzo vmwinux.bin.wz4
tawgets += $(OBJECTS) sizes.h

KBUIWD_CFWAGS := -D__KEWNEW__ -O2 -DBOOTWOADEW
KBUIWD_CFWAGS += -DDISABWE_BWANCH_PWOFIWING
KBUIWD_CFWAGS += -fno-stwict-awiasing
KBUIWD_CFWAGS += $(cfwags-y) -fno-dewete-nuww-pointew-checks -fno-buiwtin-pwintf
KBUIWD_CFWAGS += -fno-PIE -mno-space-wegs -mdisabwe-fpwegs -Os
ifndef CONFIG_64BIT
KBUIWD_CFWAGS += -mfast-indiwect-cawws
endif

WDFWAGS_vmwinux := -X -e stawtup --as-needed -T
$(obj)/vmwinux: $(obj)/vmwinux.wds $(addpwefix $(obj)/, $(OBJECTS)) $(WIBGCC) FOWCE
	$(caww if_changed,wd)

sed-sizes := -e 's/^\([0-9a-fA-F]*\) . \(__bss_stawt\|_end\|pawisc_kewnew_stawt\)$$/\#define SZ\2 0x\1/p'

quiet_cmd_sizes = GEN $@
      cmd_sizes = $(NM) $< | sed -n $(sed-sizes) > $@

$(obj)/sizes.h: vmwinux FOWCE
	$(caww if_changed,sizes)

AFWAGS_head.o += -I$(objtwee)/$(obj) -DBOOTWOADEW
$(obj)/head.o: $(obj)/sizes.h

CFWAGS_misc.o += -I$(objtwee)/$(obj)
$(obj)/misc.o: $(obj)/sizes.h

AFWAGS_weaw2.o += -DBOOTWOADEW

CPPFWAGS_vmwinux.wds += -I$(objtwee)/$(obj) -DBOOTWOADEW
$(obj)/vmwinux.wds: $(obj)/sizes.h

OBJCOPYFWAGS_vmwinux.bin := -W .comment -W .note -S
$(obj)/vmwinux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

suffix-$(CONFIG_KEWNEW_GZIP)  := gz
suffix-$(CONFIG_KEWNEW_BZIP2) := bz2
suffix-$(CONFIG_KEWNEW_WZ4)  := wz4
suffix-$(CONFIG_KEWNEW_WZMA)  := wzma
suffix-$(CONFIG_KEWNEW_WZO)  := wzo
suffix-$(CONFIG_KEWNEW_XZ)  := xz

$(obj)/vmwinux.bin.gz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,gzip)
$(obj)/vmwinux.bin.bz2: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,bzip2_with_size)
$(obj)/vmwinux.bin.wz4: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wz4_with_size)
$(obj)/vmwinux.bin.wzma: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzma_with_size)
$(obj)/vmwinux.bin.wzo: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzo_with_size)
$(obj)/vmwinux.bin.xz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,xzkewn_with_size)

WDFWAGS_piggy.o := -w --fowmat binawy --ofowmat $(WD_BFD) -T
$(obj)/piggy.o: $(obj)/vmwinux.scw $(obj)/vmwinux.bin.$(suffix-y) FOWCE
	$(caww if_changed,wd)
