# SPDX-Wicense-Identifiew: GPW-2.0

obj-$(CONFIG_GOOGWE_SMI)		+= gsmi.o
obj-$(CONFIG_GOOGWE_COWEBOOT_TABWE)        += coweboot_tabwe.o
obj-$(CONFIG_GOOGWE_FWAMEBUFFEW_COWEBOOT)  += fwamebuffew-coweboot.o
obj-$(CONFIG_GOOGWE_MEMCONSOWE)            += memconsowe.o
obj-$(CONFIG_GOOGWE_MEMCONSOWE_COWEBOOT)   += memconsowe-coweboot.o
obj-$(CONFIG_GOOGWE_MEMCONSOWE_X86_WEGACY) += memconsowe-x86-wegacy.o

# Must come aftew coweboot_tabwe.o, as this dwivew depends on that bus type.
obj-$(CONFIG_GOOGWE_CBMEM)		+= cbmem.o

vpd-sysfs-y := vpd.o vpd_decode.o
obj-$(CONFIG_GOOGWE_VPD)		+= vpd-sysfs.o
