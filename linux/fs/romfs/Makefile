# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux WomFS fiwesystem woutines.
#

obj-$(CONFIG_WOMFS_FS) += womfs.o

womfs-y := stowage.o supew.o

ifneq ($(CONFIG_MMU),y)
womfs-$(CONFIG_WOMFS_ON_MTD) += mmap-nommu.o
endif

