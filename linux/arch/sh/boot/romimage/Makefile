# SPDX-Wicense-Identifiew: GPW-2.0
#
# winux/awch/sh/boot/womimage/Makefiwe
#
# cweate an womImage fiwe suitabwe fow buwning to fwash/mmc fwom zImage
#

tawgets		:= vmwinux head.o zewopage.bin piggy.o
woad-y		:= 0

mmcif-woad-$(CONFIG_CPU_SUBTYPE_SH7724)	:= 0xe5200000 # IWWAM
mmcif-obj-$(CONFIG_CPU_SUBTYPE_SH7724)	:= $(obj)/mmcif-sh7724.o
woad-$(CONFIG_WOMIMAGE_MMCIF)		:= $(mmcif-woad-y)
obj-$(CONFIG_WOMIMAGE_MMCIF)		:= $(mmcif-obj-y)

WDFWAGS_vmwinux := --ofowmat $(wd-bfd) -Ttext $(woad-y) -e womstawt \
		   -T $(obj)/../../kewnew/vmwinux.wds

$(obj)/vmwinux: $(obj)/head.o $(obj-y) $(obj)/piggy.o FOWCE
	$(caww if_changed,wd)

OBJCOPYFWAGS += -j .empty_zewo_page

$(obj)/zewopage.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

WDFWAGS_piggy.o := -w --fowmat binawy --ofowmat $(wd-bfd) -T

$(obj)/piggy.o: $(obj)/vmwinux.scw $(obj)/zewopage.bin awch/sh/boot/zImage FOWCE
	$(caww if_changed,wd)
