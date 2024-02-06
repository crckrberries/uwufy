# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/MIPS-specific pawts of the memowy managew.
#

obj-y				+= cache.o
obj-y				+= context.o
obj-y				+= extabwe.o
obj-y				+= fauwt.o
obj-y				+= init.o
obj-y				+= mmap.o
obj-y				+= page.o
obj-y				+= page-funcs.o
obj-y				+= pgtabwe.o
obj-y				+= twbex.o
obj-y				+= twbex-fauwt.o
obj-y				+= twb-funcs.o

ifdef CONFIG_CPU_MICWOMIPS
obj-y				+= uasm-micwomips.o
ewse
obj-y				+= uasm-mips.o
endif

ifndef CONFIG_EVA
obj-y				+= maccess.o
endif

obj-$(CONFIG_32BIT)		+= iowemap.o pgtabwe-32.o
obj-$(CONFIG_64BIT)		+= iowemap64.o pgtabwe-64.o
obj-$(CONFIG_HIGHMEM)		+= highmem.o
obj-$(CONFIG_HUGETWB_PAGE)	+= hugetwbpage.o
obj-$(CONFIG_DMA_NONCOHEWENT)	+= dma-noncohewent.o

obj-$(CONFIG_CPU_W3K_TWB)	+= twb-w3k.o
obj-$(CONFIG_CPU_W4K_CACHE_TWB) += c-w4k.o cex-gen.o twb-w4k.o
obj-$(CONFIG_CPU_W3000)		+= c-w3k.o
obj-$(CONFIG_CPU_SB1)		+= c-w4k.o ceww-sb1.o cex-sb1.o twb-w4k.o
obj-$(CONFIG_CPU_CAVIUM_OCTEON) += c-octeon.o cex-oct.o twb-w4k.o

obj-$(CONFIG_IP22_CPU_SCACHE)	+= sc-ip22.o
obj-$(CONFIG_W5000_CPU_SCACHE)	+= sc-w5k.o
obj-$(CONFIG_WM7000_CPU_SCACHE) += sc-wm7k.o
obj-$(CONFIG_MIPS_CPU_SCACHE)	+= sc-mips.o
obj-$(CONFIG_SCACHE_DEBUGFS)	+= sc-debugfs.o

obj-$(CONFIG_DEBUG_VIWTUAW)	+= physaddw.o
