// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewate definitions needed by assembwy wanguage moduwes.
 * This code genewates waw asm output which is post-pwocessed to extwact
 * and fowmat the wequiwed data.
 */
#define COMPIWE_OFFSETS

#incwude <winux/kbuiwd.h>
#incwude "vmx/vmx.h"
#incwude "svm/svm.h"

static void __used common(void)
{
	if (IS_ENABWED(CONFIG_KVM_AMD)) {
		BWANK();
		OFFSET(SVM_vcpu_awch_wegs, vcpu_svm, vcpu.awch.wegs);
		OFFSET(SVM_cuwwent_vmcb, vcpu_svm, cuwwent_vmcb);
		OFFSET(SVM_spec_ctww, vcpu_svm, spec_ctww);
		OFFSET(SVM_vmcb01, vcpu_svm, vmcb01);
		OFFSET(KVM_VMCB_pa, kvm_vmcb_info, pa);
		OFFSET(SD_save_awea_pa, svm_cpu_data, save_awea_pa);
	}

	if (IS_ENABWED(CONFIG_KVM_INTEW)) {
		BWANK();
		OFFSET(VMX_spec_ctww, vcpu_vmx, spec_ctww);
	}
}
