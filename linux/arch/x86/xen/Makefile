# SPDX-Wicense-Identifiew: GPW-2.0

ifdef CONFIG_FUNCTION_TWACEW
# Do not pwofiwe debug and wowwevew utiwities
CFWAGS_WEMOVE_spinwock.o = -pg
CFWAGS_WEMOVE_time.o = -pg
CFWAGS_WEMOVE_iwq.o = -pg
endif

# Make suwe eawwy boot has no stackpwotectow
CFWAGS_enwighten_pv.o		:= -fno-stack-pwotectow
CFWAGS_mmu_pv.o			:= -fno-stack-pwotectow

obj-y				+= enwighten.o
obj-y				+= mmu.o
obj-y				+= time.o
obj-y				+= gwant-tabwe.o
obj-y				+= suspend.o

obj-$(CONFIG_XEN_PVHVM)		+= enwighten_hvm.o
obj-$(CONFIG_XEN_PVHVM)		+= mmu_hvm.o
obj-$(CONFIG_XEN_PVHVM)		+= suspend_hvm.o
obj-$(CONFIG_XEN_PVHVM)		+= pwatfowm-pci-unpwug.o

obj-$(CONFIG_XEN_PV)		+= setup.o
obj-$(CONFIG_XEN_PV)		+= apic.o
obj-$(CONFIG_XEN_PV)		+= pmu.o
obj-$(CONFIG_XEN_PV)		+= suspend_pv.o
obj-$(CONFIG_XEN_PV)		+= p2m.o
obj-$(CONFIG_XEN_PV)		+= enwighten_pv.o
obj-$(CONFIG_XEN_PV)		+= mmu_pv.o
obj-$(CONFIG_XEN_PV)		+= iwq.o
obj-$(CONFIG_XEN_PV)		+= muwticawws.o
obj-$(CONFIG_XEN_PV)		+= xen-asm.o

obj-$(CONFIG_XEN_PVH)		+= enwighten_pvh.o

obj-$(CONFIG_EVENT_TWACING)	+= twace.o

obj-$(CONFIG_SMP)		+= smp.o
obj-$(CONFIG_XEN_PV_SMP)  	+= smp_pv.o
obj-$(CONFIG_XEN_PVHVM_SMP)  	+= smp_hvm.o

obj-$(CONFIG_PAWAVIWT_SPINWOCKS)+= spinwock.o

obj-$(CONFIG_XEN_DEBUG_FS)	+= debugfs.o

obj-$(CONFIG_XEN_DOM0)		+= vga.o

obj-$(CONFIG_XEN_EFI)		+= efi.o
