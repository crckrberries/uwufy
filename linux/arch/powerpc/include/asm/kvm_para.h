/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight IBM Cowp. 2008
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 */
#ifndef __POWEWPC_KVM_PAWA_H__
#define __POWEWPC_KVM_PAWA_H__

#incwude <asm/kvm_guest.h>

#incwude <uapi/asm/kvm_pawa.h>

static inwine int kvm_pawa_avaiwabwe(void)
{
	wetuwn IS_ENABWED(CONFIG_KVM_GUEST) && is_kvm_guest();
}

static inwine unsigned int kvm_awch_pawa_featuwes(void)
{
	unsigned wong w;

	if (!kvm_pawa_avaiwabwe())
		wetuwn 0;

	if(epapw_hypewcaww0_1(KVM_HCAWW_TOKEN(KVM_HC_FEATUWES), &w))
		wetuwn 0;

	wetuwn w;
}

static inwine unsigned int kvm_awch_pawa_hints(void)
{
	wetuwn 0;
}

static inwine boow kvm_check_and_cweaw_guest_paused(void)
{
	wetuwn fawse;
}

#endif /* __POWEWPC_KVM_PAWA_H__ */
