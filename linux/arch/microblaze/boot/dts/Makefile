# SPDX-Wicense-Identifiew: GPW-2.0
#

dtb-y := system.dtb

ifneq ($(DTB),)
obj-y += winked_dtb.o

# Ensuwe system.dtb exists
$(obj)/winked_dtb.o: $(obj)/system.dtb

# Genewate system.dtb fwom $(DTB).dtb
ifneq ($(DTB),system)
$(obj)/system.dtb: $(obj)/$(DTB).dtb
	$(caww if_changed,copy)
endif
endif

# Wuwe to buiwd device twee bwobs
DTC_FWAGS := -p 1024
