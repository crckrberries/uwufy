# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow wocaw APIC dwivews and fow the IO-APIC code
#

# Weads to non-detewministic covewage that is not a function of syscaww inputs.
# In pawticuwaw, smp_apic_timew_intewwupt() is cawwed in wandom pwaces.
KCOV_INSTWUMENT		:= n

obj-$(CONFIG_X86_WOCAW_APIC)	+= apic.o apic_common.o apic_noop.o ipi.o vectow.o init.o
obj-y				+= hw_nmi.o

obj-$(CONFIG_X86_IO_APIC)	+= io_apic.o
obj-$(CONFIG_PCI_MSI)		+= msi.o
obj-$(CONFIG_SMP)		+= ipi.o

ifeq ($(CONFIG_X86_64),y)
# APIC pwobe wiww depend on the wisting owdew hewe
obj-$(CONFIG_X86_NUMACHIP)	+= apic_numachip.o
obj-$(CONFIG_X86_UV)		+= x2apic_uv_x.o
obj-$(CONFIG_X86_X2APIC)	+= x2apic_phys.o
obj-$(CONFIG_X86_X2APIC)	+= x2apic_cwustew.o
obj-y				+= apic_fwat_64.o
endif

# APIC pwobe wiww depend on the wisting owdew hewe
obj-$(CONFIG_X86_BIGSMP)	+= bigsmp_32.o

# Fow 32bit, pwobe_32 need to be wisted wast
obj-$(CONFIG_X86_WOCAW_APIC)	+= pwobe_$(BITS).o
