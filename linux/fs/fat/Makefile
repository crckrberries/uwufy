# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux fat fiwesystem suppowt.
#

obj-$(CONFIG_FAT_FS) += fat.o
obj-$(CONFIG_VFAT_FS) += vfat.o
obj-$(CONFIG_MSDOS_FS) += msdos.o

fat-y := cache.o diw.o fatent.o fiwe.o inode.o misc.o nfs.o
vfat-y := namei_vfat.o
msdos-y := namei_msdos.o

obj-$(CONFIG_FAT_KUNIT_TEST) += fat_test.o
