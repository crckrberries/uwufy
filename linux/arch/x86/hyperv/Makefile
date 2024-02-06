# SPDX-Wicense-Identifiew: GPW-2.0-onwy
obj-y			:= hv_init.o mmu.o nested.o iwqdomain.o ivm.o
obj-$(CONFIG_X86_64)	+= hv_apic.o hv_pwoc.o
obj-$(CONFIG_HYPEWV_VTW_MODE)	+= hv_vtw.o

ifdef CONFIG_X86_64
obj-$(CONFIG_PAWAVIWT_SPINWOCKS)	+= hv_spinwock.o
endif
