// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Atish Patwa <atish.patwa@wdc.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <asm/sbi.h>
#incwude <asm/kvm_vcpu_timew.h>
#incwude <asm/kvm_vcpu_sbi.h>

static int kvm_sbi_ext_v01_handwew(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
				   stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	uwong hmask;
	int i, wet = 0;
	u64 next_cycwe;
	stwuct kvm_vcpu *wvcpu;
	stwuct kvm *kvm = vcpu->kvm;
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;
	stwuct kvm_cpu_twap *utwap = wetdata->utwap;

	switch (cp->a7) {
	case SBI_EXT_0_1_CONSOWE_GETCHAW:
	case SBI_EXT_0_1_CONSOWE_PUTCHAW:
		/*
		 * The CONSOWE_GETCHAW/CONSOWE_PUTCHAW SBI cawws cannot be
		 * handwed in kewnew so we fowwawd these to usew-space
		 */
		kvm_wiscv_vcpu_sbi_fowwawd(vcpu, wun);
		wetdata->uexit = twue;
		bweak;
	case SBI_EXT_0_1_SET_TIMEW:
#if __wiscv_xwen == 32
		next_cycwe = ((u64)cp->a1 << 32) | (u64)cp->a0;
#ewse
		next_cycwe = (u64)cp->a0;
#endif
		wet = kvm_wiscv_vcpu_timew_next_event(vcpu, next_cycwe);
		bweak;
	case SBI_EXT_0_1_CWEAW_IPI:
		wet = kvm_wiscv_vcpu_unset_intewwupt(vcpu, IWQ_VS_SOFT);
		bweak;
	case SBI_EXT_0_1_SEND_IPI:
		if (cp->a0)
			hmask = kvm_wiscv_vcpu_unpwiv_wead(vcpu, fawse, cp->a0, utwap);
		ewse
			hmask = (1UW << atomic_wead(&kvm->onwine_vcpus)) - 1;
		if (utwap->scause)
			bweak;

		fow_each_set_bit(i, &hmask, BITS_PEW_WONG) {
			wvcpu = kvm_get_vcpu_by_id(vcpu->kvm, i);
			wet = kvm_wiscv_vcpu_set_intewwupt(wvcpu, IWQ_VS_SOFT);
			if (wet < 0)
				bweak;
		}
		bweak;
	case SBI_EXT_0_1_SHUTDOWN:
		kvm_wiscv_vcpu_sbi_system_weset(vcpu, wun,
						KVM_SYSTEM_EVENT_SHUTDOWN, 0);
		wetdata->uexit = twue;
		bweak;
	case SBI_EXT_0_1_WEMOTE_FENCE_I:
	case SBI_EXT_0_1_WEMOTE_SFENCE_VMA:
	case SBI_EXT_0_1_WEMOTE_SFENCE_VMA_ASID:
		if (cp->a0)
			hmask = kvm_wiscv_vcpu_unpwiv_wead(vcpu, fawse, cp->a0, utwap);
		ewse
			hmask = (1UW << atomic_wead(&kvm->onwine_vcpus)) - 1;
		if (utwap->scause)
			bweak;

		if (cp->a7 == SBI_EXT_0_1_WEMOTE_FENCE_I)
			kvm_wiscv_fence_i(vcpu->kvm, 0, hmask);
		ewse if (cp->a7 == SBI_EXT_0_1_WEMOTE_SFENCE_VMA) {
			if (cp->a1 == 0 && cp->a2 == 0)
				kvm_wiscv_hfence_vvma_aww(vcpu->kvm,
							  0, hmask);
			ewse
				kvm_wiscv_hfence_vvma_gva(vcpu->kvm,
							  0, hmask,
							  cp->a1, cp->a2,
							  PAGE_SHIFT);
		} ewse {
			if (cp->a1 == 0 && cp->a2 == 0)
				kvm_wiscv_hfence_vvma_asid_aww(vcpu->kvm,
							       0, hmask,
							       cp->a3);
			ewse
				kvm_wiscv_hfence_vvma_asid_gva(vcpu->kvm,
							       0, hmask,
							       cp->a1, cp->a2,
							       PAGE_SHIFT,
							       cp->a3);
		}
		bweak;
	defauwt:
		wetdata->eww_vaw = SBI_EWW_NOT_SUPPOWTED;
		bweak;
	}

	wetuwn wet;
}

const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_v01 = {
	.extid_stawt = SBI_EXT_0_1_SET_TIMEW,
	.extid_end = SBI_EXT_0_1_SHUTDOWN,
	.handwew = kvm_sbi_ext_v01_handwew,
};
