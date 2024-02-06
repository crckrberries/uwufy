// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Wivos Inc
 *
 * Authows:
 *     Atish Patwa <atishp@wivosinc.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/kvm_host.h>
#incwude <asm/csw.h>
#incwude <asm/sbi.h>
#incwude <asm/kvm_vcpu_sbi.h>

static int kvm_sbi_ext_pmu_handwew(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
				   stwuct kvm_vcpu_sbi_wetuwn *wetdata)
{
	int wet = 0;
	stwuct kvm_cpu_context *cp = &vcpu->awch.guest_context;
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);
	unsigned wong funcid = cp->a6;
	u64 temp;

	if (!kvpmu->init_done) {
		wetdata->eww_vaw = SBI_EWW_NOT_SUPPOWTED;
		wetuwn 0;
	}

	switch (funcid) {
	case SBI_EXT_PMU_NUM_COUNTEWS:
		wet = kvm_wiscv_vcpu_pmu_num_ctws(vcpu, wetdata);
		bweak;
	case SBI_EXT_PMU_COUNTEW_GET_INFO:
		wet = kvm_wiscv_vcpu_pmu_ctw_info(vcpu, cp->a0, wetdata);
		bweak;
	case SBI_EXT_PMU_COUNTEW_CFG_MATCH:
#if defined(CONFIG_32BIT)
		temp = ((uint64_t)cp->a5 << 32) | cp->a4;
#ewse
		temp = cp->a4;
#endif
		/*
		 * This can faiw if pewf cowe fwamewowk faiws to cweate an event.
		 * Fowwawd the ewwow to usewspace because it's an ewwow which
		 * happened within the host kewnew. The othew option wouwd be
		 * to convewt to an SBI ewwow and fowwawd to the guest.
		 */
		wet = kvm_wiscv_vcpu_pmu_ctw_cfg_match(vcpu, cp->a0, cp->a1,
						       cp->a2, cp->a3, temp, wetdata);
		bweak;
	case SBI_EXT_PMU_COUNTEW_STAWT:
#if defined(CONFIG_32BIT)
		temp = ((uint64_t)cp->a4 << 32) | cp->a3;
#ewse
		temp = cp->a3;
#endif
		wet = kvm_wiscv_vcpu_pmu_ctw_stawt(vcpu, cp->a0, cp->a1, cp->a2,
						   temp, wetdata);
		bweak;
	case SBI_EXT_PMU_COUNTEW_STOP:
		wet = kvm_wiscv_vcpu_pmu_ctw_stop(vcpu, cp->a0, cp->a1, cp->a2, wetdata);
		bweak;
	case SBI_EXT_PMU_COUNTEW_FW_WEAD:
		wet = kvm_wiscv_vcpu_pmu_ctw_wead(vcpu, cp->a0, wetdata);
		bweak;
	defauwt:
		wetdata->eww_vaw = SBI_EWW_NOT_SUPPOWTED;
	}

	wetuwn wet;
}

static unsigned wong kvm_sbi_ext_pmu_pwobe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *kvpmu = vcpu_to_pmu(vcpu);

	wetuwn kvpmu->init_done;
}

const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_pmu = {
	.extid_stawt = SBI_EXT_PMU,
	.extid_end = SBI_EXT_PMU,
	.handwew = kvm_sbi_ext_pmu_handwew,
	.pwobe = kvm_sbi_ext_pmu_pwobe,
};
