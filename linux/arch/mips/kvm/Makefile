# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow KVM suppowt fow MIPS
#

incwude $(swctwee)/viwt/kvm/Makefiwe.kvm

ccfwags-y += -Iviwt/kvm -Iawch/mips/kvm

kvm-$(CONFIG_CPU_HAS_MSA) += msa.o

kvm-y +=    mips.o emuwate.o entwy.o \
	    intewwupt.o stats.o \
	    fpu.o
kvm-y += hypcaww.o
kvm-y += mmu.o
kvm-$(CONFIG_CPU_WOONGSON64) += woongson_ipi.o

kvm-y		+= vz.o
obj-$(CONFIG_KVM)	+= kvm.o
obj-y			+= twb.o
