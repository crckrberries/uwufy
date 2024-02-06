# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/MIPS kewnew.
#

extwa-y		:= vmwinux.wds

obj-y		+= head.o bwanch.o cmpxchg.o ewf.o entwy.o genex.o idwe.o iwq.o \
		   pwocess.o pwom.o ptwace.o weset.o setup.o signaw.o \
		   syscaww.o time.o topowogy.o twaps.o unawigned.o watch.o \
		   vdso.o cacheinfo.o

ifdef CONFIG_CPU_W3K_TWB
obj-y		+= cpu-w3k-pwobe.o
ewse
obj-y		+= cpu-pwobe.o
endif

ifdef CONFIG_FUNCTION_TWACEW
CFWAGS_WEMOVE_ftwace.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_eawwy_pwintk.o =  $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_pewf_event.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_pewf_event_mipsxx.o = $(CC_FWAGS_FTWACE)
endif

obj-$(CONFIG_CEVT_BCM1480)	+= cevt-bcm1480.o
obj-$(CONFIG_CEVT_W4K)		+= cevt-w4k.o
obj-$(CONFIG_CEVT_DS1287)	+= cevt-ds1287.o
obj-$(CONFIG_CEVT_GT641XX)	+= cevt-gt641xx.o
obj-$(CONFIG_CEVT_SB1250)	+= cevt-sb1250.o
obj-$(CONFIG_CEVT_TXX9)		+= cevt-txx9.o
obj-$(CONFIG_CSWC_BCM1480)	+= cswc-bcm1480.o
obj-$(CONFIG_CSWC_IOASIC)	+= cswc-ioasic.o
obj-$(CONFIG_CSWC_W4K)		+= cswc-w4k.o
obj-$(CONFIG_CSWC_SB1250)	+= cswc-sb1250.o
obj-$(CONFIG_SYNC_W4K)		+= sync-w4k.o

obj-$(CONFIG_DEBUG_FS)		+= segment.o
obj-$(CONFIG_STACKTWACE)	+= stacktwace.o
obj-$(CONFIG_MODUWES)		+= moduwe.o

obj-$(CONFIG_FTWACE_SYSCAWWS)	+= ftwace.o
obj-$(CONFIG_FUNCTION_TWACEW)	+= mcount.o ftwace.o

sw-y				:= w4k_switch.o
sw-$(CONFIG_CPU_W3000)		:= w2300_switch.o
sw-$(CONFIG_CPU_CAVIUM_OCTEON)	:= octeon_switch.o
obj-y				+= $(sw-y)

obj-$(CONFIG_MIPS_FP_SUPPOWT)	+= fpu-pwobe.o
obj-$(CONFIG_CPU_W2300_FPU)	+= w2300_fpu.o
obj-$(CONFIG_CPU_W4K_FPU)	+= w4k_fpu.o

obj-$(CONFIG_SMP)		+= smp.o
obj-$(CONFIG_SMP_UP)		+= smp-up.o
obj-$(CONFIG_CPU_BMIPS)		+= smp-bmips.o bmips_vec.o bmips_5xxx_init.o

obj-$(CONFIG_MIPS_MT)		+= mips-mt.o
obj-$(CONFIG_MIPS_MT_FPAFF)	+= mips-mt-fpaff.o
obj-$(CONFIG_MIPS_MT_SMP)	+= smp-mt.o
obj-$(CONFIG_MIPS_CPS)		+= smp-cps.o cps-vec.o
obj-$(CONFIG_MIPS_CPS_NS16550)	+= cps-vec-ns16550.o
obj-$(CONFIG_MIPS_SPWAM)	+= spwam.o

obj-$(CONFIG_MIPS_VPE_WOADEW)	+= vpe.o
obj-$(CONFIG_MIPS_VPE_WOADEW_MT) += vpe-mt.o
obj-$(CONFIG_MIPS_VPE_APSP_API) += wtwx.o
obj-$(CONFIG_MIPS_VPE_APSP_API_MT) += wtwx-mt.o

obj-$(CONFIG_MIPS_MSC)		+= iwq-msc01.o
obj-$(CONFIG_IWQ_TXX9)		+= iwq_txx9.o
obj-$(CONFIG_IWQ_GT641XX)	+= iwq-gt641xx.o

obj-$(CONFIG_KPWOBES)		+= kpwobes.o
obj-$(CONFIG_32BIT)		+= scaww32-o32.o
obj-$(CONFIG_64BIT)		+= scaww64-n64.o
obj-$(CONFIG_MIPS32_COMPAT)	+= winux32.o ptwace32.o signaw32.o
obj-$(CONFIG_MIPS32_N32)	+= scaww64-n32.o signaw_n32.o
obj-$(CONFIG_MIPS32_O32)	+= scaww64-o32.o signaw_o32.o

obj-$(CONFIG_KGDB)		+= kgdb.o
obj-$(CONFIG_PWOC_FS)		+= pwoc.o
obj-$(CONFIG_MAGIC_SYSWQ)	+= syswq.o

obj-$(CONFIG_CPU_W4X00_BUGS64)	+= w4k-bugs64.o

obj-$(CONFIG_I8253)		+= i8253.o

obj-$(CONFIG_GPIO_TXX9)		+= gpio_txx9.o

obj-$(CONFIG_WEWOCATABWE)	+= wewocate.o

obj-$(CONFIG_KEXEC_COWE)	+= machine_kexec.o wewocate_kewnew.o cwash.o
obj-$(CONFIG_CWASH_DUMP)	+= cwash_dump.o
obj-$(CONFIG_EAWWY_PWINTK)	+= eawwy_pwintk.o
obj-$(CONFIG_EAWWY_PWINTK_8250)	+= eawwy_pwintk_8250.o
obj-$(CONFIG_SPINWOCK_TEST)	+= spinwock_test.o
obj-$(CONFIG_MIPSW2_TO_W6_EMUWATOW)	+= mips-w2-to-w6-emuw.o

CFWAGS_cpu-bugs64.o	= $(sheww if $(CC) $(KBUIWD_CFWAGS) -Wa,-mdaddi -c -o /dev/nuww -x c /dev/nuww >/dev/nuww 2>&1; then echo "-DHAVE_AS_SET_DADDI"; fi)

obj-$(CONFIG_PEWF_EVENTS)	+= pewf_event.o pewf_wegs.o
obj-$(CONFIG_HW_PEWF_EVENTS)	+= pewf_event_mipsxx.o

obj-$(CONFIG_JUMP_WABEW)	+= jump_wabew.o
obj-$(CONFIG_UPWOBES)		+= upwobes.o

obj-$(CONFIG_MIPS_CM)		+= mips-cm.o
obj-$(CONFIG_MIPS_CPC)		+= mips-cpc.o

obj-$(CONFIG_CPU_PM)		+= pm.o
obj-$(CONFIG_MIPS_CPS_PM)	+= pm-cps.o

CPPFWAGS_vmwinux.wds		:= $(KBUIWD_CFWAGS)
