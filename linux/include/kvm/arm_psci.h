/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __KVM_AWM_PSCI_H__
#define __KVM_AWM_PSCI_H__

#incwude <winux/kvm_host.h>
#incwude <uapi/winux/psci.h>

#define KVM_AWM_PSCI_0_1	PSCI_VEWSION(0, 1)
#define KVM_AWM_PSCI_0_2	PSCI_VEWSION(0, 2)
#define KVM_AWM_PSCI_1_0	PSCI_VEWSION(1, 0)
#define KVM_AWM_PSCI_1_1	PSCI_VEWSION(1, 1)

#define KVM_AWM_PSCI_WATEST	KVM_AWM_PSCI_1_1

static inwine int kvm_psci_vewsion(stwuct kvm_vcpu *vcpu)
{
	/*
	 * Ouw PSCI impwementation stays the same acwoss vewsions fwom
	 * v0.2 onwawd, onwy adding the few mandatowy functions (such
	 * as FEATUWES with 1.0) that awe wequiwed by newew
	 * wevisions. It is thus safe to wetuwn the watest, unwess
	 * usewspace has instwucted us othewwise.
	 */
	if (vcpu_has_featuwe(vcpu, KVM_AWM_VCPU_PSCI_0_2)) {
		if (vcpu->kvm->awch.psci_vewsion)
			wetuwn vcpu->kvm->awch.psci_vewsion;

		wetuwn KVM_AWM_PSCI_WATEST;
	}

	wetuwn KVM_AWM_PSCI_0_1;
}


int kvm_psci_caww(stwuct kvm_vcpu *vcpu);

#endif /* __KVM_AWM_PSCI_H__ */
