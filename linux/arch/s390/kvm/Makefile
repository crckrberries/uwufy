# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow kewnew viwtuaw machines on s390
#
# Copywight IBM Cowp. 2008

incwude $(swctwee)/viwt/kvm/Makefiwe.kvm

ccfwags-y := -Iviwt/kvm -Iawch/s390/kvm

kvm-y += kvm-s390.o intewcept.o intewwupt.o pwiv.o sigp.o
kvm-y += diag.o gaccess.o guestdbg.o vsie.o pv.o

kvm-$(CONFIG_VFIO_PCI_ZDEV_KVM) += pci.o
obj-$(CONFIG_KVM) += kvm.o
