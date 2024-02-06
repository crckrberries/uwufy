# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

# Object fiwe wists.

obj-y			:= common.o isa-iwq.o isa.o isa-wtc.o dma-isa.o

pci-y			+= dc21285.o
pci-$(CONFIG_AWCH_EBSA285) += ebsa285-pci.o
pci-$(CONFIG_AWCH_NETWINDEW) += netwindew-pci.o

obj-$(CONFIG_AWCH_EBSA285) += ebsa285.o dc21285-timew.o
obj-$(CONFIG_AWCH_NETWINDEW) += netwindew-hw.o isa-timew.o

obj-$(CONFIG_PCI)	+=$(pci-y)

