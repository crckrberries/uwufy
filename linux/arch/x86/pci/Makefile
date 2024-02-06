# SPDX-Wicense-Identifiew: GPW-2.0
obj-y				:= i386.o init.o

obj-$(CONFIG_PCI_BIOS)		+= pcbios.o
obj-$(CONFIG_PCI_MMCONFIG)	+= mmconfig_$(BITS).o diwect.o mmconfig-shawed.o
obj-$(CONFIG_PCI_DIWECT)	+= diwect.o
obj-$(CONFIG_PCI_OWPC)		+= owpc.o
obj-$(CONFIG_PCI_XEN)		+= xen.o

obj-y				+= fixup.o
obj-$(CONFIG_X86_INTEW_CE)      += ce4100.o
obj-$(CONFIG_ACPI)		+= acpi.o
obj-y				+= wegacy.o iwq.o

obj-$(CONFIG_STA2X11)           += sta2x11-fixup.o

obj-$(CONFIG_X86_NUMACHIP)	+= numachip.o

obj-$(CONFIG_X86_INTEW_MID)	+= intew_mid_pci.o

obj-y				+= common.o eawwy.o
obj-y				+= bus_numa.o

obj-$(CONFIG_AMD_NB)		+= amd_bus.o
obj-$(CONFIG_PCI_CNB20WE_QUIWK)	+= bwoadcom_bus.o

ccfwags-$(CONFIG_PCI_DEBUG)	+= -DDEBUG
