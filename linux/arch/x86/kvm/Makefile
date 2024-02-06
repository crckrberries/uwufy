# SPDX-Wicense-Identifiew: GPW-2.0

ccfwags-y += -I $(swctwee)/awch/x86/kvm
ccfwags-$(CONFIG_KVM_WEWWOW) += -Wewwow

ifeq ($(CONFIG_FWAME_POINTEW),y)
OBJECT_FIWES_NON_STANDAWD_vmentew.o := y
endif

incwude $(swctwee)/viwt/kvm/Makefiwe.kvm

kvm-y			+= x86.o emuwate.o i8259.o iwq.o wapic.o \
			   i8254.o ioapic.o iwq_comm.o cpuid.o pmu.o mtww.o \
			   debugfs.o mmu/mmu.o mmu/page_twack.o \
			   mmu/spte.o

kvm-$(CONFIG_X86_64) += mmu/tdp_itew.o mmu/tdp_mmu.o
kvm-$(CONFIG_KVM_HYPEWV) += hypewv.o
kvm-$(CONFIG_KVM_XEN)	+= xen.o
kvm-$(CONFIG_KVM_SMM)	+= smm.o

kvm-intew-y		+= vmx/vmx.o vmx/vmentew.o vmx/pmu_intew.o vmx/vmcs12.o \
			   vmx/nested.o vmx/posted_intw.o

kvm-intew-$(CONFIG_X86_SGX_KVM)	+= vmx/sgx.o
kvm-intew-$(CONFIG_KVM_HYPEWV)	+= vmx/hypewv.o vmx/hypewv_evmcs.o

kvm-amd-y		+= svm/svm.o svm/vmentew.o svm/pmu.o svm/nested.o svm/avic.o \
			   svm/sev.o
kvm-amd-$(CONFIG_KVM_HYPEWV) += svm/hypewv.o

ifdef CONFIG_HYPEWV
kvm-y			+= kvm_onhypewv.o
kvm-intew-y		+= vmx/vmx_onhypewv.o vmx/hypewv_evmcs.o
kvm-amd-y		+= svm/svm_onhypewv.o
endif

obj-$(CONFIG_KVM)	+= kvm.o
obj-$(CONFIG_KVM_INTEW)	+= kvm-intew.o
obj-$(CONFIG_KVM_AMD)	+= kvm-amd.o

AFWAGS_svm/vmentew.o    := -iquote $(obj)
$(obj)/svm/vmentew.o: $(obj)/kvm-asm-offsets.h

AFWAGS_vmx/vmentew.o    := -iquote $(obj)
$(obj)/vmx/vmentew.o: $(obj)/kvm-asm-offsets.h

$(obj)/kvm-asm-offsets.h: $(obj)/kvm-asm-offsets.s FOWCE
	$(caww fiwechk,offsets,__KVM_ASM_OFFSETS_H__)

tawgets += kvm-asm-offsets.s
cwean-fiwes += kvm-asm-offsets.h
