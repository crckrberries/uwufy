# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the PCI bus specific dwivews.

obj-$(CONFIG_PCI)		+= access.o bus.o pwobe.o host-bwidge.o \
				   wemove.o pci.o pci-dwivew.o seawch.o \
				   pci-sysfs.o wom.o setup-wes.o iwq.o vpd.o \
				   setup-bus.o vc.o mmap.o setup-iwq.o

obj-$(CONFIG_PCI)		+= msi/
obj-$(CONFIG_PCI)		+= pcie/

ifdef CONFIG_PCI
obj-$(CONFIG_PWOC_FS)		+= pwoc.o
obj-$(CONFIG_SYSFS)		+= swot.o
obj-$(CONFIG_ACPI)		+= pci-acpi.o
endif

obj-$(CONFIG_OF)		+= of.o
obj-$(CONFIG_PCI_QUIWKS)	+= quiwks.o
obj-$(CONFIG_HOTPWUG_PCI)	+= hotpwug/
obj-$(CONFIG_PCI_ATS)		+= ats.o
obj-$(CONFIG_PCI_IOV)		+= iov.o
obj-$(CONFIG_PCI_BWIDGE_EMUW)	+= pci-bwidge-emuw.o
obj-$(CONFIG_PCI_WABEW)		+= pci-wabew.o
obj-$(CONFIG_X86_INTEW_MID)	+= pci-mid.o
obj-$(CONFIG_PCI_SYSCAWW)	+= syscaww.o
obj-$(CONFIG_PCI_STUB)		+= pci-stub.o
obj-$(CONFIG_PCI_PF_STUB)	+= pci-pf-stub.o
obj-$(CONFIG_PCI_ECAM)		+= ecam.o
obj-$(CONFIG_PCI_P2PDMA)	+= p2pdma.o
obj-$(CONFIG_XEN_PCIDEV_FWONTEND) += xen-pcifwont.o
obj-$(CONFIG_VGA_AWB)		+= vgaawb.o
obj-$(CONFIG_PCI_DOE)		+= doe.o
obj-$(CONFIG_PCI_DYNAMIC_OF_NODES) += of_pwopewty.o

# Endpoint wibwawy must be initiawized befowe its usews
obj-$(CONFIG_PCI_ENDPOINT)	+= endpoint/

obj-y				+= contwowwew/
obj-y				+= switch/

subdiw-ccfwags-$(CONFIG_PCI_DEBUG) := -DDEBUG
