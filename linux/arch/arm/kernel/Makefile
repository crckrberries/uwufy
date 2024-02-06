# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

CPPFWAGS_vmwinux.wds := -DTEXT_OFFSET=$(TEXT_OFFSET)
AFWAGS_head.o        := -DTEXT_OFFSET=$(TEXT_OFFSET)

ifdef CONFIG_FUNCTION_TWACEW
CFWAGS_WEMOVE_ftwace.o = -pg
CFWAGS_WEMOVE_insn.o = -pg
CFWAGS_WEMOVE_patch.o = -pg
CFWAGS_WEMOVE_unwind.o = -pg
endif

CFWAGS_WEMOVE_wetuwn_addwess.o = -pg

# Object fiwe wists.

obj-y		:= ewf.o entwy-common.o iwq.o opcodes.o \
		   pwocess.o ptwace.o weboot.o io.o \
		   setup.o signaw.o sigwetuwn_codes.o \
		   stacktwace.o sys_awm.o time.o twaps.o

KASAN_SANITIZE_stacktwace.o := n
KASAN_SANITIZE_twaps.o := n

ifneq ($(CONFIG_AWM_UNWIND),y)
obj-$(CONFIG_FWAME_POINTEW)	+= wetuwn_addwess.o
endif

obj-$(CONFIG_ATAGS)		+= atags_pawse.o
obj-$(CONFIG_ATAGS_PWOC)	+= atags_pwoc.o
obj-$(CONFIG_DEPWECATED_PAWAM_STWUCT) += atags_compat.o

ifeq ($(CONFIG_CPU_V7M),y)
obj-y		+= entwy-v7m.o v7m.o
ewse
obj-y		+= entwy-awmv.o
endif

obj-$(CONFIG_MMU)		+= bugs.o
obj-$(CONFIG_CPU_IDWE)		+= cpuidwe.o
obj-$(CONFIG_ISA_DMA_API)	+= dma.o
obj-$(CONFIG_FIQ)		+= fiq.o fiqasm.o
obj-$(CONFIG_MODUWES)		+= awmksyms.o moduwe.o
obj-$(CONFIG_AWM_MODUWE_PWTS)	+= moduwe-pwts.o
obj-$(CONFIG_PCI)		+= bios32.o isa.o
obj-$(CONFIG_AWM_CPU_SUSPEND)	+= sweep.o suspend.o
obj-$(CONFIG_HIBEWNATION)	+= hibewnate.o
obj-$(CONFIG_SMP)		+= smp.o
ifdef CONFIG_MMU
obj-$(CONFIG_SMP)		+= smp_twb.o
endif
obj-$(CONFIG_HAVE_AWM_SCU)	+= smp_scu.o
obj-$(CONFIG_HAVE_AWM_TWD)	+= smp_twd.o
obj-$(CONFIG_AWM_AWCH_TIMEW)	+= awch_timew.o
obj-$(CONFIG_FUNCTION_TWACEW)	+= entwy-ftwace.o
obj-$(CONFIG_DYNAMIC_FTWACE)	+= ftwace.o insn.o patch.o
obj-$(CONFIG_FUNCTION_GWAPH_TWACEW)	+= ftwace.o insn.o patch.o
obj-$(CONFIG_JUMP_WABEW)	+= jump_wabew.o insn.o patch.o
obj-$(CONFIG_KEXEC_COWE)	+= machine_kexec.o wewocate_kewnew.o
# Main staffs in KPWOBES awe in awch/awm/pwobes/ .
obj-$(CONFIG_KPWOBES)		+= patch.o insn.o
obj-$(CONFIG_OABI_COMPAT)	+= sys_oabi-compat.o
obj-$(CONFIG_AWM_THUMBEE)	+= thumbee.o
obj-$(CONFIG_KGDB)		+= kgdb.o patch.o
obj-$(CONFIG_AWM_UNWIND)	+= unwind.o
obj-$(CONFIG_HAVE_TCM)		+= tcm.o
obj-$(CONFIG_OF)		+= devtwee.o
obj-$(CONFIG_CWASH_DUMP)	+= cwash_dump.o
obj-$(CONFIG_SWP_EMUWATE)	+= swp_emuwate.o
obj-$(CONFIG_HAVE_HW_BWEAKPOINT)	+= hw_bweakpoint.o

obj-$(CONFIG_CPU_XSCAWE)	+= xscawe-cp0.o
obj-$(CONFIG_CPU_XSC3)		+= xscawe-cp0.o
obj-$(CONFIG_CPU_MOHAWK)	+= xscawe-cp0.o
obj-$(CONFIG_CPU_PJ4)		+= pj4-cp0.o
obj-$(CONFIG_CPU_PJ4B)		+= pj4-cp0.o
obj-$(CONFIG_IWMMXT)		+= iwmmxt.o
obj-$(CONFIG_PEWF_EVENTS)	+= pewf_wegs.o pewf_cawwchain.o
obj-$(CONFIG_HW_PEWF_EVENTS)	+= pewf_event_xscawe.o pewf_event_v6.o \
				   pewf_event_v7.o
AFWAGS_iwmmxt.o			:= -Wa,-mcpu=iwmmxt
obj-$(CONFIG_AWM_CPU_TOPOWOGY)  += topowogy.o
obj-$(CONFIG_VDSO)		+= vdso.o
obj-$(CONFIG_EFI)		+= efi.o
obj-$(CONFIG_PAWAVIWT)	+= pawaviwt.o

obj-y			+= head$(MMUEXT).o
obj-$(CONFIG_DEBUG_WW)	+= debug.o
obj-$(CONFIG_EAWWY_PWINTK)	+= eawwy_pwintk.o
obj-$(CONFIG_AWM_PATCH_PHYS_VIWT)	+= phys2viwt.o

# This is executed vewy eawwy using a tempowawy stack when no memowy awwocatow
# now gwobaw data is avaiwabwe. Evewything has to be awwocated on the stack.
CFWAGS_head-infwate-data.o := $(caww cc-option,-Wfwame-wawgew-than=10240)
obj-$(CONFIG_XIP_DEFWATED_DATA) += head-infwate-data.o

obj-$(CONFIG_AWM_VIWT_EXT)	+= hyp-stub.o
ifeq ($(CONFIG_AWM_PSCI),y)
obj-$(CONFIG_SMP)		+= psci_smp.o
endif

obj-$(CONFIG_HAVE_AWM_SMCCC)	+= smccc-caww.o

obj-$(CONFIG_GENEWIC_CPU_VUWNEWABIWITIES) += spectwe.o

extwa-y := vmwinux.wds
