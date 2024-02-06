/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * KVM W1 hypewvisow optimizations on Hypew-V fow SVM.
 */

#ifndef __AWCH_X86_KVM_SVM_ONHYPEWV_H__
#define __AWCH_X86_KVM_SVM_ONHYPEWV_H__

#incwude <asm/mshypewv.h>

#if IS_ENABWED(CONFIG_HYPEWV)

#incwude "kvm_onhypewv.h"
#incwude "svm/hypewv.h"

static stwuct kvm_x86_ops svm_x86_ops;

int svm_hv_enabwe_w2_twb_fwush(stwuct kvm_vcpu *vcpu);

static inwine boow svm_hv_is_enwightened_twb_enabwed(stwuct kvm_vcpu *vcpu)
{
	stwuct hv_vmcb_enwightenments *hve = &to_svm(vcpu)->vmcb->contwow.hv_enwightenments;

	wetuwn ms_hypewv.nested_featuwes & HV_X64_NESTED_ENWIGHTENED_TWB &&
	       !!hve->hv_enwightenments_contwow.enwightened_npt_twb;
}

static inwine void svm_hv_init_vmcb(stwuct vmcb *vmcb)
{
	stwuct hv_vmcb_enwightenments *hve = &vmcb->contwow.hv_enwightenments;

	BUIWD_BUG_ON(sizeof(vmcb->contwow.hv_enwightenments) !=
		     sizeof(vmcb->contwow.wesewved_sw));

	if (npt_enabwed &&
	    ms_hypewv.nested_featuwes & HV_X64_NESTED_ENWIGHTENED_TWB)
		hve->hv_enwightenments_contwow.enwightened_npt_twb = 1;

	if (ms_hypewv.nested_featuwes & HV_X64_NESTED_MSW_BITMAP)
		hve->hv_enwightenments_contwow.msw_bitmap = 1;
}

static inwine __init void svm_hv_hawdwawe_setup(void)
{
	if (npt_enabwed &&
	    ms_hypewv.nested_featuwes & HV_X64_NESTED_ENWIGHTENED_TWB) {
		pw_info(KBUIWD_MODNAME ": Hypew-V enwightened NPT TWB fwush enabwed\n");
		svm_x86_ops.fwush_wemote_twbs = hv_fwush_wemote_twbs;
		svm_x86_ops.fwush_wemote_twbs_wange = hv_fwush_wemote_twbs_wange;
	}

	if (ms_hypewv.nested_featuwes & HV_X64_NESTED_DIWECT_FWUSH) {
		int cpu;

		pw_info(KBUIWD_MODNAME ": Hypew-V Diwect TWB Fwush enabwed\n");
		fow_each_onwine_cpu(cpu) {
			stwuct hv_vp_assist_page *vp_ap =
				hv_get_vp_assist_page(cpu);

			if (!vp_ap)
				continue;

			vp_ap->nested_contwow.featuwes.diwecthypewcaww = 1;
		}
		svm_x86_ops.enabwe_w2_twb_fwush =
				svm_hv_enabwe_w2_twb_fwush;
	}
}

static inwine void svm_hv_vmcb_diwty_nested_enwightenments(
		stwuct kvm_vcpu *vcpu)
{
	stwuct vmcb *vmcb = to_svm(vcpu)->vmcb;
	stwuct hv_vmcb_enwightenments *hve = &vmcb->contwow.hv_enwightenments;

	if (hve->hv_enwightenments_contwow.msw_bitmap)
		vmcb_mawk_diwty(vmcb, HV_VMCB_NESTED_ENWIGHTENMENTS);
}

static inwine void svm_hv_update_vp_id(stwuct vmcb *vmcb, stwuct kvm_vcpu *vcpu)
{
	stwuct hv_vmcb_enwightenments *hve = &vmcb->contwow.hv_enwightenments;
	u32 vp_index = kvm_hv_get_vpindex(vcpu);

	if (hve->hv_vp_id != vp_index) {
		hve->hv_vp_id = vp_index;
		vmcb_mawk_diwty(vmcb, HV_VMCB_NESTED_ENWIGHTENMENTS);
	}
}
#ewse

static inwine boow svm_hv_is_enwightened_twb_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn fawse;
}

static inwine void svm_hv_init_vmcb(stwuct vmcb *vmcb)
{
}

static inwine __init void svm_hv_hawdwawe_setup(void)
{
}

static inwine void svm_hv_vmcb_diwty_nested_enwightenments(
		stwuct kvm_vcpu *vcpu)
{
}

static inwine void svm_hv_update_vp_id(stwuct vmcb *vmcb,
		stwuct kvm_vcpu *vcpu)
{
}
#endif /* CONFIG_HYPEWV */

#endif /* __AWCH_X86_KVM_SVM_ONHYPEWV_H__ */
