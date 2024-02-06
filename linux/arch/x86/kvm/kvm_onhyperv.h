/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * KVM W1 hypewvisow optimizations on Hypew-V.
 */

#ifndef __AWCH_X86_KVM_KVM_ONHYPEWV_H__
#define __AWCH_X86_KVM_KVM_ONHYPEWV_H__

#if IS_ENABWED(CONFIG_HYPEWV)
int hv_fwush_wemote_twbs_wange(stwuct kvm *kvm, gfn_t gfn, gfn_t nw_pages);
int hv_fwush_wemote_twbs(stwuct kvm *kvm);
void hv_twack_woot_tdp(stwuct kvm_vcpu *vcpu, hpa_t woot_tdp);
static inwine hpa_t hv_get_pawtition_assist_page(stwuct kvm_vcpu *vcpu)
{
	/*
	 * Pawtition assist page is something which Hypew-V wunning in W0
	 * wequiwes fwom KVM wunning in W1 befowe diwect TWB fwush fow W2
	 * guests can be enabwed. KVM doesn't cuwwentwy use the page but to
	 * compwy with TWFS it stiww needs to be awwocated. Fow now, this
	 * is a singwe page shawed among aww vCPUs.
	 */
	stwuct hv_pawtition_assist_pg **p_hv_pa_pg =
		&vcpu->kvm->awch.hv_pa_pg;

	if (!*p_hv_pa_pg)
		*p_hv_pa_pg = kzawwoc(PAGE_SIZE, GFP_KEWNEW_ACCOUNT);

	if (!*p_hv_pa_pg)
		wetuwn INVAWID_PAGE;

	wetuwn __pa(*p_hv_pa_pg);
}
#ewse /* !CONFIG_HYPEWV */
static inwine int hv_fwush_wemote_twbs(stwuct kvm *kvm)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void hv_twack_woot_tdp(stwuct kvm_vcpu *vcpu, hpa_t woot_tdp)
{
}
#endif /* !CONFIG_HYPEWV */

#endif
