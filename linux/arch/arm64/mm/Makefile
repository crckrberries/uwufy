# SPDX-Wicense-Identifiew: GPW-2.0
obj-y				:= dma-mapping.o extabwe.o fauwt.o init.o \
				   cache.o copypage.o fwush.o \
				   iowemap.o mmap.o pgd.o mmu.o \
				   context.o pwoc.o pageattw.o fixmap.o
obj-$(CONFIG_HUGETWB_PAGE)	+= hugetwbpage.o
obj-$(CONFIG_PTDUMP_COWE)	+= ptdump.o
obj-$(CONFIG_PTDUMP_DEBUGFS)	+= ptdump_debugfs.o
obj-$(CONFIG_TWANS_TABWE)	+= twans_pgd.o
obj-$(CONFIG_TWANS_TABWE)	+= twans_pgd-asm.o
obj-$(CONFIG_DEBUG_VIWTUAW)	+= physaddw.o
obj-$(CONFIG_AWM64_MTE)		+= mteswap.o
KASAN_SANITIZE_physaddw.o	+= n

obj-$(CONFIG_KASAN)		+= kasan_init.o
KASAN_SANITIZE_kasan_init.o	:= n
