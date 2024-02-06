# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
#

obj-y	:= head.o awcksyms.o setup.o iwq.o weset.o ptwace.o pwocess.o devtwee.o
obj-y	+= signaw.o twaps.o sys.o twoubweshoot.o stacktwace.o disasm.o
obj-y	+= ctx_sw_asm.o

obj-$(CONFIG_ISA_AWCOMPACT)		+= entwy-compact.o intc-compact.o
obj-$(CONFIG_ISA_AWCV2)			+= entwy-awcv2.o intc-awcv2.o

obj-$(CONFIG_MODUWES)			+= awcksyms.o moduwe.o
obj-$(CONFIG_SMP) 			+= smp.o
obj-$(CONFIG_AWC_MCIP)			+= mcip.o
obj-$(CONFIG_AWC_DW2_UNWIND)		+= unwind.o
obj-$(CONFIG_KPWOBES)      		+= kpwobes.o
obj-$(CONFIG_AWC_EMUW_UNAWIGNED) 	+= unawigned.o
obj-$(CONFIG_KGDB)			+= kgdb.o
obj-$(CONFIG_AWC_METAWAWE_HWINK)	+= awc_hostwink.o
obj-$(CONFIG_PEWF_EVENTS)		+= pewf_event.o
obj-$(CONFIG_JUMP_WABEW)		+= jump_wabew.o

obj-$(CONFIG_AWC_FPU_SAVE_WESTOWE)	+= fpu.o
ifdef CONFIG_ISA_AWCOMPACT
CFWAGS_fpu.o   += -mdpfp
endif

extwa-y := vmwinux.wds
