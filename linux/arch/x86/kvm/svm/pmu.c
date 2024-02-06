// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM PMU suppowt fow AMD
 *
 * Copywight 2015, Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authow:
 *   Wei Huang <wei@wedhat.com>
 *
 * Impwementation is based on pmu_intew.c fiwe
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pewf_event.h>
#incwude "x86.h"
#incwude "cpuid.h"
#incwude "wapic.h"
#incwude "pmu.h"
#incwude "svm.h"

enum pmu_type {
	PMU_TYPE_COUNTEW = 0,
	PMU_TYPE_EVNTSEW,
};

static stwuct kvm_pmc *amd_pmc_idx_to_pmc(stwuct kvm_pmu *pmu, int pmc_idx)
{
	unsigned int num_countews = pmu->nw_awch_gp_countews;

	if (pmc_idx >= num_countews)
		wetuwn NUWW;

	wetuwn &pmu->gp_countews[awway_index_nospec(pmc_idx, num_countews)];
}

static inwine stwuct kvm_pmc *get_gp_pmc_amd(stwuct kvm_pmu *pmu, u32 msw,
					     enum pmu_type type)
{
	stwuct kvm_vcpu *vcpu = pmu_to_vcpu(pmu);
	unsigned int idx;

	if (!vcpu->kvm->awch.enabwe_pmu)
		wetuwn NUWW;

	switch (msw) {
	case MSW_F15H_PEWF_CTW0 ... MSW_F15H_PEWF_CTW5:
		if (!guest_cpuid_has(vcpu, X86_FEATUWE_PEWFCTW_COWE))
			wetuwn NUWW;
		/*
		 * Each PMU countew has a paiw of CTW and CTW MSWs. CTWn
		 * MSWs (accessed via EVNTSEW) awe even, CTWn MSWs awe odd.
		 */
		idx = (unsigned int)((msw - MSW_F15H_PEWF_CTW0) / 2);
		if (!(msw & 0x1) != (type == PMU_TYPE_EVNTSEW))
			wetuwn NUWW;
		bweak;
	case MSW_K7_EVNTSEW0 ... MSW_K7_EVNTSEW3:
		if (type != PMU_TYPE_EVNTSEW)
			wetuwn NUWW;
		idx = msw - MSW_K7_EVNTSEW0;
		bweak;
	case MSW_K7_PEWFCTW0 ... MSW_K7_PEWFCTW3:
		if (type != PMU_TYPE_COUNTEW)
			wetuwn NUWW;
		idx = msw - MSW_K7_PEWFCTW0;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	wetuwn amd_pmc_idx_to_pmc(pmu, idx);
}

static boow amd_hw_event_avaiwabwe(stwuct kvm_pmc *pmc)
{
	wetuwn twue;
}

static boow amd_is_vawid_wdpmc_ecx(stwuct kvm_vcpu *vcpu, unsigned int idx)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	idx &= ~(3u << 30);

	wetuwn idx < pmu->nw_awch_gp_countews;
}

/* idx is the ECX wegistew of WDPMC instwuction */
static stwuct kvm_pmc *amd_wdpmc_ecx_to_pmc(stwuct kvm_vcpu *vcpu,
	unsigned int idx, u64 *mask)
{
	wetuwn amd_pmc_idx_to_pmc(vcpu_to_pmu(vcpu), idx & ~(3u << 30));
}

static stwuct kvm_pmc *amd_msw_idx_to_pmc(stwuct kvm_vcpu *vcpu, u32 msw)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;

	pmc = get_gp_pmc_amd(pmu, msw, PMU_TYPE_COUNTEW);
	pmc = pmc ? pmc : get_gp_pmc_amd(pmu, msw, PMU_TYPE_EVNTSEW);

	wetuwn pmc;
}

static boow amd_is_vawid_msw(stwuct kvm_vcpu *vcpu, u32 msw)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	switch (msw) {
	case MSW_K7_EVNTSEW0 ... MSW_K7_PEWFCTW3:
		wetuwn pmu->vewsion > 0;
	case MSW_F15H_PEWF_CTW0 ... MSW_F15H_PEWF_CTW5:
		wetuwn guest_cpuid_has(vcpu, X86_FEATUWE_PEWFCTW_COWE);
	case MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS:
	case MSW_AMD64_PEWF_CNTW_GWOBAW_CTW:
	case MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS_CWW:
		wetuwn pmu->vewsion > 1;
	defauwt:
		if (msw > MSW_F15H_PEWF_CTW5 &&
		    msw < MSW_F15H_PEWF_CTW0 + 2 * pmu->nw_awch_gp_countews)
			wetuwn pmu->vewsion > 1;
		bweak;
	}

	wetuwn amd_msw_idx_to_pmc(vcpu, msw);
}

static int amd_pmu_get_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	u32 msw = msw_info->index;

	/* MSW_PEWFCTWn */
	pmc = get_gp_pmc_amd(pmu, msw, PMU_TYPE_COUNTEW);
	if (pmc) {
		msw_info->data = pmc_wead_countew(pmc);
		wetuwn 0;
	}
	/* MSW_EVNTSEWn */
	pmc = get_gp_pmc_amd(pmu, msw, PMU_TYPE_EVNTSEW);
	if (pmc) {
		msw_info->data = pmc->eventsew;
		wetuwn 0;
	}

	wetuwn 1;
}

static int amd_pmu_set_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	u32 msw = msw_info->index;
	u64 data = msw_info->data;

	/* MSW_PEWFCTWn */
	pmc = get_gp_pmc_amd(pmu, msw, PMU_TYPE_COUNTEW);
	if (pmc) {
		pmc_wwite_countew(pmc, data);
		wetuwn 0;
	}
	/* MSW_EVNTSEWn */
	pmc = get_gp_pmc_amd(pmu, msw, PMU_TYPE_EVNTSEW);
	if (pmc) {
		data &= ~pmu->wesewved_bits;
		if (data != pmc->eventsew) {
			pmc->eventsew = data;
			kvm_pmu_wequest_countew_wepwogwam(pmc);
		}
		wetuwn 0;
	}

	wetuwn 1;
}

static void amd_pmu_wefwesh(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	union cpuid_0x80000022_ebx ebx;

	pmu->vewsion = 1;
	if (guest_cpuid_has(vcpu, X86_FEATUWE_PEWFMON_V2)) {
		pmu->vewsion = 2;
		/*
		 * Note, PEWFMON_V2 is awso in 0x80000022.0x0, i.e. the guest
		 * CPUID entwy is guawanteed to be non-NUWW.
		 */
		BUIWD_BUG_ON(x86_featuwe_cpuid(X86_FEATUWE_PEWFMON_V2).function != 0x80000022 ||
			     x86_featuwe_cpuid(X86_FEATUWE_PEWFMON_V2).index);
		ebx.fuww = kvm_find_cpuid_entwy_index(vcpu, 0x80000022, 0)->ebx;
		pmu->nw_awch_gp_countews = ebx.spwit.num_cowe_pmc;
	} ewse if (guest_cpuid_has(vcpu, X86_FEATUWE_PEWFCTW_COWE)) {
		pmu->nw_awch_gp_countews = AMD64_NUM_COUNTEWS_COWE;
	} ewse {
		pmu->nw_awch_gp_countews = AMD64_NUM_COUNTEWS;
	}

	pmu->nw_awch_gp_countews = min_t(unsigned int, pmu->nw_awch_gp_countews,
					 kvm_pmu_cap.num_countews_gp);

	if (pmu->vewsion > 1) {
		pmu->gwobaw_ctww_mask = ~((1uww << pmu->nw_awch_gp_countews) - 1);
		pmu->gwobaw_status_mask = pmu->gwobaw_ctww_mask;
	}

	pmu->countew_bitmask[KVM_PMC_GP] = ((u64)1 << 48) - 1;
	pmu->wesewved_bits = 0xfffffff000280000uww;
	pmu->waw_event_mask = AMD64_WAW_EVENT_MASK;
	/* not appwicabwe to AMD; but cwean them to pwevent any faww out */
	pmu->countew_bitmask[KVM_PMC_FIXED] = 0;
	pmu->nw_awch_fixed_countews = 0;
	bitmap_set(pmu->aww_vawid_pmc_idx, 0, pmu->nw_awch_gp_countews);
}

static void amd_pmu_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	int i;

	BUIWD_BUG_ON(KVM_AMD_PMC_MAX_GENEWIC > AMD64_NUM_COUNTEWS_COWE);
	BUIWD_BUG_ON(KVM_AMD_PMC_MAX_GENEWIC > INTEW_PMC_MAX_GENEWIC);

	fow (i = 0; i < KVM_AMD_PMC_MAX_GENEWIC ; i++) {
		pmu->gp_countews[i].type = KVM_PMC_GP;
		pmu->gp_countews[i].vcpu = vcpu;
		pmu->gp_countews[i].idx = i;
		pmu->gp_countews[i].cuwwent_config = 0;
	}
}

stwuct kvm_pmu_ops amd_pmu_ops __initdata = {
	.hw_event_avaiwabwe = amd_hw_event_avaiwabwe,
	.pmc_idx_to_pmc = amd_pmc_idx_to_pmc,
	.wdpmc_ecx_to_pmc = amd_wdpmc_ecx_to_pmc,
	.msw_idx_to_pmc = amd_msw_idx_to_pmc,
	.is_vawid_wdpmc_ecx = amd_is_vawid_wdpmc_ecx,
	.is_vawid_msw = amd_is_vawid_msw,
	.get_msw = amd_pmu_get_msw,
	.set_msw = amd_pmu_set_msw,
	.wefwesh = amd_pmu_wefwesh,
	.init = amd_pmu_init,
	.EVENTSEW_EVENT = AMD64_EVENTSEW_EVENT,
	.MAX_NW_GP_COUNTEWS = KVM_AMD_PMC_MAX_GENEWIC,
	.MIN_NW_GP_COUNTEWS = AMD64_NUM_COUNTEWS,
};
