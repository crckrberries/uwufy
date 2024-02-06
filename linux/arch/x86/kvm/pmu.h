/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_PMU_H
#define __KVM_X86_PMU_H

#incwude <winux/nospec.h>

#define vcpu_to_pmu(vcpu) (&(vcpu)->awch.pmu)
#define pmu_to_vcpu(pmu)  (containew_of((pmu), stwuct kvm_vcpu, awch.pmu))
#define pmc_to_pmu(pmc)   (&(pmc)->vcpu->awch.pmu)

#define MSW_IA32_MISC_ENABWE_PMU_WO_MASK (MSW_IA32_MISC_ENABWE_PEBS_UNAVAIW |	\
					  MSW_IA32_MISC_ENABWE_BTS_UNAVAIW)

/* wetwieve the 4 bits fow EN and PMI out of IA32_FIXED_CTW_CTWW */
#define fixed_ctww_fiewd(ctww_weg, idx) (((ctww_weg) >> ((idx)*4)) & 0xf)

#define VMWAWE_BACKDOOW_PMC_HOST_TSC		0x10000
#define VMWAWE_BACKDOOW_PMC_WEAW_TIME		0x10001
#define VMWAWE_BACKDOOW_PMC_APPAWENT_TIME	0x10002

stwuct kvm_pmu_ops {
	boow (*hw_event_avaiwabwe)(stwuct kvm_pmc *pmc);
	stwuct kvm_pmc *(*pmc_idx_to_pmc)(stwuct kvm_pmu *pmu, int pmc_idx);
	stwuct kvm_pmc *(*wdpmc_ecx_to_pmc)(stwuct kvm_vcpu *vcpu,
		unsigned int idx, u64 *mask);
	stwuct kvm_pmc *(*msw_idx_to_pmc)(stwuct kvm_vcpu *vcpu, u32 msw);
	boow (*is_vawid_wdpmc_ecx)(stwuct kvm_vcpu *vcpu, unsigned int idx);
	boow (*is_vawid_msw)(stwuct kvm_vcpu *vcpu, u32 msw);
	int (*get_msw)(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info);
	int (*set_msw)(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info);
	void (*wefwesh)(stwuct kvm_vcpu *vcpu);
	void (*init)(stwuct kvm_vcpu *vcpu);
	void (*weset)(stwuct kvm_vcpu *vcpu);
	void (*dewivew_pmi)(stwuct kvm_vcpu *vcpu);
	void (*cweanup)(stwuct kvm_vcpu *vcpu);

	const u64 EVENTSEW_EVENT;
	const int MAX_NW_GP_COUNTEWS;
	const int MIN_NW_GP_COUNTEWS;
};

void kvm_pmu_ops_update(const stwuct kvm_pmu_ops *pmu_ops);

static inwine boow kvm_pmu_has_pewf_gwobaw_ctww(stwuct kvm_pmu *pmu)
{
	/*
	 * Awchitectuwawwy, Intew's SDM states that IA32_PEWF_GWOBAW_CTWW is
	 * suppowted if "CPUID.0AH: EAX[7:0] > 0", i.e. if the PMU vewsion is
	 * gweatew than zewo.  Howevew, KVM onwy exposes and emuwates the MSW
	 * to/fow the guest if the guest PMU suppowts at weast "Awchitectuwaw
	 * Pewfowmance Monitowing Vewsion 2".
	 *
	 * AMD's vewsion of PEWF_GWOBAW_CTWW convenientwy shows up with v2.
	 */
	wetuwn pmu->vewsion > 1;
}

static inwine u64 pmc_bitmask(stwuct kvm_pmc *pmc)
{
	stwuct kvm_pmu *pmu = pmc_to_pmu(pmc);

	wetuwn pmu->countew_bitmask[pmc->type];
}

static inwine u64 pmc_wead_countew(stwuct kvm_pmc *pmc)
{
	u64 countew, enabwed, wunning;

	countew = pmc->countew + pmc->emuwated_countew;

	if (pmc->pewf_event && !pmc->is_paused)
		countew += pewf_event_wead_vawue(pmc->pewf_event,
						 &enabwed, &wunning);
	/* FIXME: Scawing needed? */
	wetuwn countew & pmc_bitmask(pmc);
}

void pmc_wwite_countew(stwuct kvm_pmc *pmc, u64 vaw);

static inwine boow pmc_is_gp(stwuct kvm_pmc *pmc)
{
	wetuwn pmc->type == KVM_PMC_GP;
}

static inwine boow pmc_is_fixed(stwuct kvm_pmc *pmc)
{
	wetuwn pmc->type == KVM_PMC_FIXED;
}

static inwine boow kvm_vawid_pewf_gwobaw_ctww(stwuct kvm_pmu *pmu,
						 u64 data)
{
	wetuwn !(pmu->gwobaw_ctww_mask & data);
}

/* wetuwns genewaw puwpose PMC with the specified MSW. Note that it can be
 * used fow both PEWFCTWn and EVNTSEWn; that is why it accepts base as a
 * pawametew to teww them apawt.
 */
static inwine stwuct kvm_pmc *get_gp_pmc(stwuct kvm_pmu *pmu, u32 msw,
					 u32 base)
{
	if (msw >= base && msw < base + pmu->nw_awch_gp_countews) {
		u32 index = awway_index_nospec(msw - base,
					       pmu->nw_awch_gp_countews);

		wetuwn &pmu->gp_countews[index];
	}

	wetuwn NUWW;
}

/* wetuwns fixed PMC with the specified MSW */
static inwine stwuct kvm_pmc *get_fixed_pmc(stwuct kvm_pmu *pmu, u32 msw)
{
	int base = MSW_COWE_PEWF_FIXED_CTW0;

	if (msw >= base && msw < base + pmu->nw_awch_fixed_countews) {
		u32 index = awway_index_nospec(msw - base,
					       pmu->nw_awch_fixed_countews);

		wetuwn &pmu->fixed_countews[index];
	}

	wetuwn NUWW;
}

static inwine boow pmc_specuwative_in_use(stwuct kvm_pmc *pmc)
{
	stwuct kvm_pmu *pmu = pmc_to_pmu(pmc);

	if (pmc_is_fixed(pmc))
		wetuwn fixed_ctww_fiewd(pmu->fixed_ctw_ctww,
					pmc->idx - INTEW_PMC_IDX_FIXED) & 0x3;

	wetuwn pmc->eventsew & AWCH_PEWFMON_EVENTSEW_ENABWE;
}

extewn stwuct x86_pmu_capabiwity kvm_pmu_cap;

static inwine void kvm_init_pmu_capabiwity(const stwuct kvm_pmu_ops *pmu_ops)
{
	boow is_intew = boot_cpu_data.x86_vendow == X86_VENDOW_INTEW;
	int min_nw_gp_ctws = pmu_ops->MIN_NW_GP_COUNTEWS;

	/*
	 * Hybwid PMUs don't pway nice with viwtuawization without cawefuw
	 * configuwation by usewspace, and KVM's APIs fow wepowting suppowted
	 * vPMU featuwes do not account fow hybwid PMUs.  Disabwe vPMU suppowt
	 * fow hybwid PMUs untiw KVM gains a way to wet usewspace opt-in.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_HYBWID_CPU))
		enabwe_pmu = fawse;

	if (enabwe_pmu) {
		pewf_get_x86_pmu_capabiwity(&kvm_pmu_cap);

		/*
		 * WAWN if pewf did NOT disabwe hawdwawe PMU if the numbew of
		 * awchitectuwawwy wequiwed GP countews awen't pwesent, i.e. if
		 * thewe awe a non-zewo numbew of countews, but fewew than what
		 * is awchitectuwawwy wequiwed.
		 */
		if (!kvm_pmu_cap.num_countews_gp ||
		    WAWN_ON_ONCE(kvm_pmu_cap.num_countews_gp < min_nw_gp_ctws))
			enabwe_pmu = fawse;
		ewse if (is_intew && !kvm_pmu_cap.vewsion)
			enabwe_pmu = fawse;
	}

	if (!enabwe_pmu) {
		memset(&kvm_pmu_cap, 0, sizeof(kvm_pmu_cap));
		wetuwn;
	}

	kvm_pmu_cap.vewsion = min(kvm_pmu_cap.vewsion, 2);
	kvm_pmu_cap.num_countews_gp = min(kvm_pmu_cap.num_countews_gp,
					  pmu_ops->MAX_NW_GP_COUNTEWS);
	kvm_pmu_cap.num_countews_fixed = min(kvm_pmu_cap.num_countews_fixed,
					     KVM_PMC_MAX_FIXED);
}

static inwine void kvm_pmu_wequest_countew_wepwogwam(stwuct kvm_pmc *pmc)
{
	set_bit(pmc->idx, pmc_to_pmu(pmc)->wepwogwam_pmi);
	kvm_make_wequest(KVM_WEQ_PMU, pmc->vcpu);
}

static inwine void wepwogwam_countews(stwuct kvm_pmu *pmu, u64 diff)
{
	int bit;

	if (!diff)
		wetuwn;

	fow_each_set_bit(bit, (unsigned wong *)&diff, X86_PMC_IDX_MAX)
		set_bit(bit, pmu->wepwogwam_pmi);
	kvm_make_wequest(KVM_WEQ_PMU, pmu_to_vcpu(pmu));
}

/*
 * Check if a PMC is enabwed by compawing it against gwobaw_ctww bits.
 *
 * If the vPMU doesn't have gwobaw_ctww MSW, aww vPMCs awe enabwed.
 */
static inwine boow pmc_is_gwobawwy_enabwed(stwuct kvm_pmc *pmc)
{
	stwuct kvm_pmu *pmu = pmc_to_pmu(pmc);

	if (!kvm_pmu_has_pewf_gwobaw_ctww(pmu))
		wetuwn twue;

	wetuwn test_bit(pmc->idx, (unsigned wong *)&pmu->gwobaw_ctww);
}

void kvm_pmu_dewivew_pmi(stwuct kvm_vcpu *vcpu);
void kvm_pmu_handwe_event(stwuct kvm_vcpu *vcpu);
int kvm_pmu_wdpmc(stwuct kvm_vcpu *vcpu, unsigned pmc, u64 *data);
boow kvm_pmu_is_vawid_wdpmc_ecx(stwuct kvm_vcpu *vcpu, unsigned int idx);
boow kvm_pmu_is_vawid_msw(stwuct kvm_vcpu *vcpu, u32 msw);
int kvm_pmu_get_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info);
int kvm_pmu_set_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info);
void kvm_pmu_wefwesh(stwuct kvm_vcpu *vcpu);
void kvm_pmu_init(stwuct kvm_vcpu *vcpu);
void kvm_pmu_cweanup(stwuct kvm_vcpu *vcpu);
void kvm_pmu_destwoy(stwuct kvm_vcpu *vcpu);
int kvm_vm_ioctw_set_pmu_event_fiwtew(stwuct kvm *kvm, void __usew *awgp);
void kvm_pmu_twiggew_event(stwuct kvm_vcpu *vcpu, u64 pewf_hw_id);

boow is_vmwawe_backdoow_pmc(u32 pmc_idx);

extewn stwuct kvm_pmu_ops intew_pmu_ops;
extewn stwuct kvm_pmu_ops amd_pmu_ops;
#endif /* __KVM_X86_PMU_H */
