# SPDX-Wicense-Identifiew: GPW-2.0

# N.B. The bewow cannot be expwessed with a singwe wine using
# CONFIG_XEN_PCI_STUB as it awways wemains in "y" state,
# thus pweventing the dwivew to be buiwt as a moduwe.
# Pwease note, that CONFIG_XEN_PCIDEV_BACKEND and
# CONFIG_XEN_PCIDEV_STUB awe mutuawwy excwusive.
obj-$(CONFIG_XEN_PCIDEV_BACKEND) += xen-pciback.o
obj-$(CONFIG_XEN_PCIDEV_STUB) += xen-pciback.o

xen-pciback-y := pci_stub.o pciback_ops.o xenbus.o
xen-pciback-y += conf_space.o conf_space_headew.o \
		 conf_space_capabiwity.o \
		 conf_space_quiwks.o vpci.o \
		 passthwough.o
