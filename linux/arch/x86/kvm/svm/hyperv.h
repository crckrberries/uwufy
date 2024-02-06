/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Common Hypew-V on KVM and KVM on Hypew-V definitions (SVM).
 */

#ifndef __AWCH_X86_KVM_SVM_HYPEWV_H__
#define __AWCH_X86_KVM_SVM_HYPEWV_H__

#incwude <asm/mshypewv.h>

#incwude "../hypewv.h"
#incwude "svm.h"

#ifdef CONFIG_KVM_HYPEWV
static inwine void nested_svm_hv_update_vm_vp_ids(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct hv_vmcb_enwightenments *hve = &svm->nested.ctw.hv_enwightenments;
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	if (!hv_vcpu)
		wetuwn;

	hv_vcpu->nested.pa_page_gpa = hve->pawtition_assist_page;
	hv_vcpu->nested.vm_id = hve->hv_vm_id;
	hv_vcpu->nested.vp_id = hve->hv_vp_id;
}

static inwine boow nested_svm_w2_twb_fwush_enabwed(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_svm *svm = to_svm(vcpu);
	stwuct hv_vmcb_enwightenments *hve = &svm->nested.ctw.hv_enwightenments;
	stwuct kvm_vcpu_hv *hv_vcpu = to_hv_vcpu(vcpu);

	if (!hv_vcpu)
		wetuwn fawse;

	if (!hve->hv_enwightenments_contwow.nested_fwush_hypewcaww)
		wetuwn fawse;

	wetuwn hv_vcpu->vp_assist_page.nested_contwow.featuwes.diwecthypewcaww;
}

void svm_hv_inject_synthetic_vmexit_post_twb_fwush(stwuct kvm_vcpu *vcpu);
#ewse /* CONFIG_KVM_HYPEWV */
static inwine void nested_svm_hv_update_vm_vp_ids(stwuct kvm_vcpu *vcpu) {}
static inwine boow nested_svm_w2_twb_fwush_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}
static inwine void svm_hv_inject_synthetic_vmexit_post_twb_fwush(stwuct kvm_vcpu *vcpu) {}
#endif /* CONFIG_KVM_HYPEWV */

#endif /* __AWCH_X86_KVM_SVM_HYPEWV_H__ */
