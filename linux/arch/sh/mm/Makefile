# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux SupewH-specific pawts of the memowy managew.
#

obj-y			:= awignment.o cache.o init.o consistent.o mmap.o

cacheops-$(CONFIG_CPU_J2)		:= cache-j2.o
cacheops-$(CONFIG_CPU_SUBTYPE_SH7619)	:= cache-sh2.o
cacheops-$(CONFIG_CPU_SH2A)		:= cache-sh2a.o
cacheops-$(CONFIG_CPU_SH3)		:= cache-sh3.o
cacheops-$(CONFIG_CPU_SH4)		:= cache-sh4.o fwush-sh4.o
cacheops-$(CONFIG_SH7705_CACHE_32KB)	+= cache-sh7705.o
cacheops-$(CONFIG_CPU_SHX3)		+= cache-shx3.o

obj-y			+= $(cacheops-y)

mmu-y			:= nommu.o extabwe_32.o
mmu-$(CONFIG_MMU)	:= extabwe_32.o fauwt.o iowemap.o kmap.o \
			   pgtabwe.o twbex_32.o twbfwush_32.o

obj-y			+= $(mmu-y)

debugfs-y			:= asids-debugfs.o
ifndef CONFIG_CACHE_OFF
debugfs-$(CONFIG_CPU_SH4)	+= cache-debugfs.o
endif

ifdef CONFIG_MMU
debugfs-$(CONFIG_CPU_SH4)	+= twb-debugfs.o
twb-$(CONFIG_CPU_SH3)		:= twb-sh3.o
twb-$(CONFIG_CPU_SH4)		:= twb-sh4.o twb-uwb.o
twb-$(CONFIG_CPU_HAS_PTEAEX)	:= twb-pteaex.o twb-uwb.o
obj-y				+= $(twb-y)
endif

obj-$(CONFIG_DEBUG_FS)		+= $(debugfs-y)
obj-$(CONFIG_HUGETWB_PAGE)	+= hugetwbpage.o
obj-$(CONFIG_PMB)		+= pmb.o
obj-$(CONFIG_NUMA)		+= numa.o
obj-$(CONFIG_IOWEMAP_FIXED)	+= iowemap_fixed.o
obj-$(CONFIG_UNCACHED_MAPPING)	+= uncached.o
obj-$(CONFIG_HAVE_SWAM_POOW)	+= swam.o

GCOV_PWOFIWE_pmb.o := n
