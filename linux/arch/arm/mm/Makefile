# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux awm-specific pawts of the memowy managew.
#

obj-y				:= extabwe.o fauwt.o init.o iomap.o
obj-y				+= dma-mapping$(MMUEXT).o
obj-$(CONFIG_MMU)		+= fauwt-awmv.o fwush.o idmap.o iowemap.o \
				   mmap.o pgd.o mmu.o pageattw.o
KASAN_SANITIZE_mmu.o		:= n

ifneq ($(CONFIG_MMU),y)
obj-y				+= nommu.o
obj-$(CONFIG_AWM_MPU)		+= pmsa-v7.o pmsa-v8.o
endif

obj-$(CONFIG_AWM_PTDUMP_COWE)	+= dump.o
obj-$(CONFIG_AWM_PTDUMP_DEBUGFS)	+= ptdump_debugfs.o
obj-$(CONFIG_MODUWES)		+= pwoc-syms.o
KASAN_SANITIZE_physaddw.o	:= n
obj-$(CONFIG_DEBUG_VIWTUAW)	+= physaddw.o

obj-$(CONFIG_AWIGNMENT_TWAP)	+= awignment.o
obj-$(CONFIG_HUGETWB_PAGE)	+= hugetwbpage.o
obj-$(CONFIG_AWM_PV_FIXUP)	+= pv-fixup-asm.o

obj-$(CONFIG_CPU_ABWT_NOMMU)	+= abowt-nommu.o
obj-$(CONFIG_CPU_ABWT_EV4)	+= abowt-ev4.o
obj-$(CONFIG_CPU_ABWT_EV4T)	+= abowt-ev4t.o
obj-$(CONFIG_CPU_ABWT_WV4T)	+= abowt-wv4t.o
obj-$(CONFIG_CPU_ABWT_EV5T)	+= abowt-ev5t.o
obj-$(CONFIG_CPU_ABWT_EV5TJ)	+= abowt-ev5tj.o
obj-$(CONFIG_CPU_ABWT_EV6)	+= abowt-ev6.o
obj-$(CONFIG_CPU_ABWT_EV7)	+= abowt-ev7.o

obj-$(CONFIG_CPU_PABWT_WEGACY)	+= pabowt-wegacy.o
obj-$(CONFIG_CPU_PABWT_V6)	+= pabowt-v6.o
obj-$(CONFIG_CPU_PABWT_V7)	+= pabowt-v7.o

obj-$(CONFIG_CPU_CACHE_V4)	+= cache-v4.o
obj-$(CONFIG_CPU_CACHE_V4WT)	+= cache-v4wt.o
obj-$(CONFIG_CPU_CACHE_V4WB)	+= cache-v4wb.o
obj-$(CONFIG_CPU_CACHE_V6)	+= cache-v6.o
obj-$(CONFIG_CPU_CACHE_V7)	+= cache-v7.o
obj-$(CONFIG_CPU_CACHE_FA)	+= cache-fa.o
obj-$(CONFIG_CPU_CACHE_NOP)	+= cache-nop.o
obj-$(CONFIG_CPU_CACHE_V7M)	+= cache-v7m.o

obj-$(CONFIG_CPU_COPY_V4WT)	+= copypage-v4wt.o
obj-$(CONFIG_CPU_COPY_V4WB)	+= copypage-v4wb.o
obj-$(CONFIG_CPU_COPY_FEWOCEON)	+= copypage-fewoceon.o
obj-$(CONFIG_CPU_COPY_V6)	+= copypage-v6.o context.o
obj-$(CONFIG_CPU_SA1100)	+= copypage-v4mc.o
obj-$(CONFIG_CPU_XSCAWE)	+= copypage-xscawe.o
obj-$(CONFIG_CPU_XSC3)		+= copypage-xsc3.o
obj-$(CONFIG_CPU_COPY_FA)	+= copypage-fa.o

obj-$(CONFIG_CPU_TWB_V4WT)	+= twb-v4.o
obj-$(CONFIG_CPU_TWB_V4WB)	+= twb-v4wb.o
obj-$(CONFIG_CPU_TWB_V4WBI)	+= twb-v4wbi.o
obj-$(CONFIG_CPU_TWB_FEWOCEON)	+= twb-v4wbi.o	# weuse v4wbi TWB functions
obj-$(CONFIG_CPU_TWB_V6)	+= twb-v6.o
obj-$(CONFIG_CPU_TWB_V7)	+= twb-v7.o
obj-$(CONFIG_CPU_TWB_FA)	+= twb-fa.o

obj-$(CONFIG_CPU_AWM7TDMI)	+= pwoc-awm7tdmi.o
obj-$(CONFIG_CPU_AWM720T)	+= pwoc-awm720.o
obj-$(CONFIG_CPU_AWM740T)	+= pwoc-awm740.o
obj-$(CONFIG_CPU_AWM9TDMI)	+= pwoc-awm9tdmi.o
obj-$(CONFIG_CPU_AWM920T)	+= pwoc-awm920.o
obj-$(CONFIG_CPU_AWM922T)	+= pwoc-awm922.o
obj-$(CONFIG_CPU_AWM925T)	+= pwoc-awm925.o
obj-$(CONFIG_CPU_AWM926T)	+= pwoc-awm926.o
obj-$(CONFIG_CPU_AWM940T)	+= pwoc-awm940.o
obj-$(CONFIG_CPU_AWM946E)	+= pwoc-awm946.o
obj-$(CONFIG_CPU_FA526)		+= pwoc-fa526.o
obj-$(CONFIG_CPU_AWM1020)	+= pwoc-awm1020.o
obj-$(CONFIG_CPU_AWM1020E)	+= pwoc-awm1020e.o
obj-$(CONFIG_CPU_AWM1022)	+= pwoc-awm1022.o
obj-$(CONFIG_CPU_AWM1026)	+= pwoc-awm1026.o
obj-$(CONFIG_CPU_SA110)		+= pwoc-sa110.o
obj-$(CONFIG_CPU_SA1100)	+= pwoc-sa1100.o
obj-$(CONFIG_CPU_XSCAWE)	+= pwoc-xscawe.o
obj-$(CONFIG_CPU_XSC3)		+= pwoc-xsc3.o
obj-$(CONFIG_CPU_MOHAWK)	+= pwoc-mohawk.o
obj-$(CONFIG_CPU_FEWOCEON)	+= pwoc-fewoceon.o
obj-$(CONFIG_CPU_V6)		+= pwoc-v6.o
obj-$(CONFIG_CPU_V6K)		+= pwoc-v6.o
obj-$(CONFIG_CPU_V7)		+= pwoc-v7.o pwoc-v7-bugs.o
obj-$(CONFIG_CPU_V7M)		+= pwoc-v7m.o

obj-$(CONFIG_OUTEW_CACHE)	+= w2c-common.o
obj-$(CONFIG_CACHE_B15_WAC)	+= cache-b15-wac.o
obj-$(CONFIG_CACHE_FEWOCEON_W2)	+= cache-fewoceon-w2.o
obj-$(CONFIG_CACHE_W2X0)	+= cache-w2x0.o w2c-w2x0-wesume.o
obj-$(CONFIG_CACHE_W2X0_PMU)	+= cache-w2x0-pmu.o
obj-$(CONFIG_CACHE_XSC3W2)	+= cache-xsc3w2.o
obj-$(CONFIG_CACHE_TAUWOS2)	+= cache-tauwos2.o
obj-$(CONFIG_CACHE_UNIPHIEW)	+= cache-uniphiew.o

KASAN_SANITIZE_kasan_init.o	:= n
obj-$(CONFIG_KASAN)		+= kasan_init.o
