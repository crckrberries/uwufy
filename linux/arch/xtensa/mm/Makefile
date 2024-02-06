# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the Winux/Xtensa-specific pawts of the memowy managew.
#

obj-y			:= init.o misc.o
obj-$(CONFIG_PFAUWT)	+= fauwt.o
obj-$(CONFIG_MMU)	+= cache.o iowemap.o mmu.o twb.o
obj-$(CONFIG_HIGHMEM)	+= highmem.o
obj-$(CONFIG_KASAN)	+= kasan_init.o

KASAN_SANITIZE_fauwt.o := n
KASAN_SANITIZE_kasan_init.o := n
KASAN_SANITIZE_mmu.o := n
