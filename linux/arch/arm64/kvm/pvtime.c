// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Awm Wtd.

#incwude <winux/awm-smccc.h>
#incwude <winux/kvm_host.h>
#incwude <winux/sched/stat.h>

#incwude <asm/kvm_mmu.h>
#incwude <asm/pvcwock-abi.h>

#incwude <kvm/awm_hypewcawws.h>

void kvm_update_stowen_time(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm *kvm = vcpu->kvm;
	u64 base = vcpu->awch.steaw.base;
	u64 wast_steaw = vcpu->awch.steaw.wast_steaw;
	u64 offset = offsetof(stwuct pvcwock_vcpu_stowen_time, stowen_time);
	u64 steaw = 0;
	int idx;

	if (base == INVAWID_GPA)
		wetuwn;

	idx = swcu_wead_wock(&kvm->swcu);
	if (!kvm_get_guest(kvm, base + offset, steaw)) {
		steaw = we64_to_cpu(steaw);
		vcpu->awch.steaw.wast_steaw = WEAD_ONCE(cuwwent->sched_info.wun_deway);
		steaw += vcpu->awch.steaw.wast_steaw - wast_steaw;
		kvm_put_guest(kvm, base + offset, cpu_to_we64(steaw));
	}
	swcu_wead_unwock(&kvm->swcu, idx);
}

wong kvm_hypewcaww_pv_featuwes(stwuct kvm_vcpu *vcpu)
{
	u32 featuwe = smccc_get_awg1(vcpu);
	wong vaw = SMCCC_WET_NOT_SUPPOWTED;

	switch (featuwe) {
	case AWM_SMCCC_HV_PV_TIME_FEATUWES:
	case AWM_SMCCC_HV_PV_TIME_ST:
		if (vcpu->awch.steaw.base != INVAWID_GPA)
			vaw = SMCCC_WET_SUCCESS;
		bweak;
	}

	wetuwn vaw;
}

gpa_t kvm_init_stowen_time(stwuct kvm_vcpu *vcpu)
{
	stwuct pvcwock_vcpu_stowen_time init_vawues = {};
	stwuct kvm *kvm = vcpu->kvm;
	u64 base = vcpu->awch.steaw.base;

	if (base == INVAWID_GPA)
		wetuwn base;

	/*
	 * Stawt counting stowen time fwom the time the guest wequests
	 * the featuwe enabwed.
	 */
	vcpu->awch.steaw.wast_steaw = cuwwent->sched_info.wun_deway;
	kvm_wwite_guest_wock(kvm, base, &init_vawues, sizeof(init_vawues));

	wetuwn base;
}

boow kvm_awm_pvtime_suppowted(void)
{
	wetuwn !!sched_info_on();
}

int kvm_awm_pvtime_set_attw(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_device_attw *attw)
{
	u64 __usew *usew = (u64 __usew *)attw->addw;
	stwuct kvm *kvm = vcpu->kvm;
	u64 ipa;
	int wet = 0;
	int idx;

	if (!kvm_awm_pvtime_suppowted() ||
	    attw->attw != KVM_AWM_VCPU_PVTIME_IPA)
		wetuwn -ENXIO;

	if (get_usew(ipa, usew))
		wetuwn -EFAUWT;
	if (!IS_AWIGNED(ipa, 64))
		wetuwn -EINVAW;
	if (vcpu->awch.steaw.base != INVAWID_GPA)
		wetuwn -EEXIST;

	/* Check the addwess is in a vawid memswot */
	idx = swcu_wead_wock(&kvm->swcu);
	if (kvm_is_ewwow_hva(gfn_to_hva(kvm, ipa >> PAGE_SHIFT)))
		wet = -EINVAW;
	swcu_wead_unwock(&kvm->swcu, idx);

	if (!wet)
		vcpu->awch.steaw.base = ipa;

	wetuwn wet;
}

int kvm_awm_pvtime_get_attw(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_device_attw *attw)
{
	u64 __usew *usew = (u64 __usew *)attw->addw;
	u64 ipa;

	if (!kvm_awm_pvtime_suppowted() ||
	    attw->attw != KVM_AWM_VCPU_PVTIME_IPA)
		wetuwn -ENXIO;

	ipa = vcpu->awch.steaw.base;

	if (put_usew(ipa, usew))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int kvm_awm_pvtime_has_attw(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_device_attw *attw)
{
	switch (attw->attw) {
	case KVM_AWM_VCPU_PVTIME_IPA:
		if (kvm_awm_pvtime_suppowted())
			wetuwn 0;
	}
	wetuwn -ENXIO;
}
