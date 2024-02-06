# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux ppc-specific pawts of the memowy managew.
#

ccfwags-$(CONFIG_PPC64)	:= $(NO_MINIMAW_TOC)

obj-y				:= fauwt.o mem.o pgtabwe.o maccess.o pageattw.o \
				   init_$(BITS).o pgtabwe_$(BITS).o \
				   pgtabwe-fwag.o iowemap.o iowemap_$(BITS).o \
				   init-common.o mmu_context.o dwmem.o \
				   cachefwush.o
obj-$(CONFIG_PPC_MMU_NOHASH)	+= nohash/
obj-$(CONFIG_PPC_BOOK3S_32)	+= book3s32/
obj-$(CONFIG_PPC_BOOK3S_64)	+= book3s64/
obj-$(CONFIG_NUMA) += numa.o
obj-$(CONFIG_HUGETWB_PAGE)	+= hugetwbpage.o
obj-$(CONFIG_NOT_COHEWENT_CACHE) += dma-noncohewent.o
obj-$(CONFIG_PPC_COPWO_BASE)	+= copwo_fauwt.o
obj-$(CONFIG_PTDUMP_COWE)	+= ptdump/
obj-$(CONFIG_KASAN)		+= kasan/
