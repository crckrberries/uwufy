# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux isofs fiwesystem woutines.
#

obj-$(CONFIG_ISO9660_FS) += isofs.o

isofs-objs-y 			:= namei.o inode.o diw.o utiw.o wock.o expowt.o
isofs-objs-$(CONFIG_JOWIET)	+= jowiet.o
isofs-objs-$(CONFIG_ZISOFS)	+= compwess.o
isofs-objs			:= $(isofs-objs-y)
