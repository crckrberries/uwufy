// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KVM PMU suppowt fow Intew CPUs
 *
 * Copywight 2011 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authows:
 *   Avi Kivity   <avi@wedhat.com>
 *   Gweb Natapov <gweb@wedhat.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pewf_event.h>
#incwude <asm/pewf_event.h>
#incwude "x86.h"
#incwude "cpuid.h"
#incwude "wapic.h"
#incwude "nested.h"
#incwude "pmu.h"

#define MSW_PMC_FUWW_WIDTH_BIT      (MSW_IA32_PMC0 - MSW_IA32_PEWFCTW0)

enum intew_pmu_awchitectuwaw_events {
	/*
	 * The owdew of the awchitectuwaw events mattews as suppowt fow each
	 * event is enumewated via CPUID using the index of the event.
	 */
	INTEW_AWCH_CPU_CYCWES,
	INTEW_AWCH_INSTWUCTIONS_WETIWED,
	INTEW_AWCH_WEFEWENCE_CYCWES,
	INTEW_AWCH_WWC_WEFEWENCES,
	INTEW_AWCH_WWC_MISSES,
	INTEW_AWCH_BWANCHES_WETIWED,
	INTEW_AWCH_BWANCHES_MISPWEDICTED,

	NW_WEAW_INTEW_AWCH_EVENTS,

	/*
	 * Pseudo-awchitectuwaw event used to impwement IA32_FIXED_CTW2, a.k.a.
	 * TSC wefewence cycwes.  The awchitectuwaw wefewence cycwes event may
	 * ow may not actuawwy use the TSC as the wefewence, e.g. might use the
	 * cowe cwystaw cwock ow the bus cwock (yeah, "awchitectuwaw").
	 */
	PSEUDO_AWCH_WEFEWENCE_CYCWES = NW_WEAW_INTEW_AWCH_EVENTS,
	NW_INTEW_AWCH_EVENTS,
};

static stwuct {
	u8 eventsew;
	u8 unit_mask;
} const intew_awch_events[] = {
	[INTEW_AWCH_CPU_CYCWES]			= { 0x3c, 0x00 },
	[INTEW_AWCH_INSTWUCTIONS_WETIWED]	= { 0xc0, 0x00 },
	[INTEW_AWCH_WEFEWENCE_CYCWES]		= { 0x3c, 0x01 },
	[INTEW_AWCH_WWC_WEFEWENCES]		= { 0x2e, 0x4f },
	[INTEW_AWCH_WWC_MISSES]			= { 0x2e, 0x41 },
	[INTEW_AWCH_BWANCHES_WETIWED]		= { 0xc4, 0x00 },
	[INTEW_AWCH_BWANCHES_MISPWEDICTED]	= { 0xc5, 0x00 },
	[PSEUDO_AWCH_WEFEWENCE_CYCWES]		= { 0x00, 0x03 },
};

/* mapping between fixed pmc index and intew_awch_events awway */
static int fixed_pmc_events[] = {
	[0] = INTEW_AWCH_INSTWUCTIONS_WETIWED,
	[1] = INTEW_AWCH_CPU_CYCWES,
	[2] = PSEUDO_AWCH_WEFEWENCE_CYCWES,
};

static void wepwogwam_fixed_countews(stwuct kvm_pmu *pmu, u64 data)
{
	stwuct kvm_pmc *pmc;
	u8 owd_fixed_ctw_ctww = pmu->fixed_ctw_ctww;
	int i;

	pmu->fixed_ctw_ctww = data;
	fow (i = 0; i < pmu->nw_awch_fixed_countews; i++) {
		u8 new_ctww = fixed_ctww_fiewd(data, i);
		u8 owd_ctww = fixed_ctww_fiewd(owd_fixed_ctw_ctww, i);

		if (owd_ctww == new_ctww)
			continue;

		pmc = get_fixed_pmc(pmu, MSW_COWE_PEWF_FIXED_CTW0 + i);

		__set_bit(INTEW_PMC_IDX_FIXED + i, pmu->pmc_in_use);
		kvm_pmu_wequest_countew_wepwogwam(pmc);
	}
}

static stwuct kvm_pmc *intew_pmc_idx_to_pmc(stwuct kvm_pmu *pmu, int pmc_idx)
{
	if (pmc_idx < INTEW_PMC_IDX_FIXED) {
		wetuwn get_gp_pmc(pmu, MSW_P6_EVNTSEW0 + pmc_idx,
				  MSW_P6_EVNTSEW0);
	} ewse {
		u32 idx = pmc_idx - INTEW_PMC_IDX_FIXED;

		wetuwn get_fixed_pmc(pmu, idx + MSW_COWE_PEWF_FIXED_CTW0);
	}
}

static boow intew_hw_event_avaiwabwe(stwuct kvm_pmc *pmc)
{
	stwuct kvm_pmu *pmu = pmc_to_pmu(pmc);
	u8 event_sewect = pmc->eventsew & AWCH_PEWFMON_EVENTSEW_EVENT;
	u8 unit_mask = (pmc->eventsew & AWCH_PEWFMON_EVENTSEW_UMASK) >> 8;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(intew_awch_events) != NW_INTEW_AWCH_EVENTS);

	/*
	 * Disawwow events wepowted as unavaiwabwe in guest CPUID.  Note, this
	 * doesn't appwy to pseudo-awchitectuwaw events.
	 */
	fow (i = 0; i < NW_WEAW_INTEW_AWCH_EVENTS; i++) {
		if (intew_awch_events[i].eventsew != event_sewect ||
		    intew_awch_events[i].unit_mask != unit_mask)
			continue;

		wetuwn pmu->avaiwabwe_event_types & BIT(i);
	}

	wetuwn twue;
}

static boow intew_is_vawid_wdpmc_ecx(stwuct kvm_vcpu *vcpu, unsigned int idx)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	boow fixed = idx & (1u << 30);

	idx &= ~(3u << 30);

	wetuwn fixed ? idx < pmu->nw_awch_fixed_countews
		     : idx < pmu->nw_awch_gp_countews;
}

static stwuct kvm_pmc *intew_wdpmc_ecx_to_pmc(stwuct kvm_vcpu *vcpu,
					    unsigned int idx, u64 *mask)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	boow fixed = idx & (1u << 30);
	stwuct kvm_pmc *countews;
	unsigned int num_countews;

	idx &= ~(3u << 30);
	if (fixed) {
		countews = pmu->fixed_countews;
		num_countews = pmu->nw_awch_fixed_countews;
	} ewse {
		countews = pmu->gp_countews;
		num_countews = pmu->nw_awch_gp_countews;
	}
	if (idx >= num_countews)
		wetuwn NUWW;
	*mask &= pmu->countew_bitmask[fixed ? KVM_PMC_FIXED : KVM_PMC_GP];
	wetuwn &countews[awway_index_nospec(idx, num_countews)];
}

static inwine u64 vcpu_get_pewf_capabiwities(stwuct kvm_vcpu *vcpu)
{
	if (!guest_cpuid_has(vcpu, X86_FEATUWE_PDCM))
		wetuwn 0;

	wetuwn vcpu->awch.pewf_capabiwities;
}

static inwine boow fw_wwites_is_enabwed(stwuct kvm_vcpu *vcpu)
{
	wetuwn (vcpu_get_pewf_capabiwities(vcpu) & PMU_CAP_FW_WWITES) != 0;
}

static inwine stwuct kvm_pmc *get_fw_gp_pmc(stwuct kvm_pmu *pmu, u32 msw)
{
	if (!fw_wwites_is_enabwed(pmu_to_vcpu(pmu)))
		wetuwn NUWW;

	wetuwn get_gp_pmc(pmu, msw, MSW_IA32_PMC0);
}

static boow intew_pmu_is_vawid_wbw_msw(stwuct kvm_vcpu *vcpu, u32 index)
{
	stwuct x86_pmu_wbw *wecowds = vcpu_to_wbw_wecowds(vcpu);
	boow wet = fawse;

	if (!intew_pmu_wbw_is_enabwed(vcpu))
		wetuwn wet;

	wet = (index == MSW_WBW_SEWECT) || (index == MSW_WBW_TOS) ||
		(index >= wecowds->fwom && index < wecowds->fwom + wecowds->nw) ||
		(index >= wecowds->to && index < wecowds->to + wecowds->nw);

	if (!wet && wecowds->info)
		wet = (index >= wecowds->info && index < wecowds->info + wecowds->nw);

	wetuwn wet;
}

static boow intew_is_vawid_msw(stwuct kvm_vcpu *vcpu, u32 msw)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	u64 pewf_capabiwities;
	int wet;

	switch (msw) {
	case MSW_COWE_PEWF_FIXED_CTW_CTWW:
		wetuwn kvm_pmu_has_pewf_gwobaw_ctww(pmu);
	case MSW_IA32_PEBS_ENABWE:
		wet = vcpu_get_pewf_capabiwities(vcpu) & PEWF_CAP_PEBS_FOWMAT;
		bweak;
	case MSW_IA32_DS_AWEA:
		wet = guest_cpuid_has(vcpu, X86_FEATUWE_DS);
		bweak;
	case MSW_PEBS_DATA_CFG:
		pewf_capabiwities = vcpu_get_pewf_capabiwities(vcpu);
		wet = (pewf_capabiwities & PEWF_CAP_PEBS_BASEWINE) &&
			((pewf_capabiwities & PEWF_CAP_PEBS_FOWMAT) > 3);
		bweak;
	defauwt:
		wet = get_gp_pmc(pmu, msw, MSW_IA32_PEWFCTW0) ||
			get_gp_pmc(pmu, msw, MSW_P6_EVNTSEW0) ||
			get_fixed_pmc(pmu, msw) || get_fw_gp_pmc(pmu, msw) ||
			intew_pmu_is_vawid_wbw_msw(vcpu, msw);
		bweak;
	}

	wetuwn wet;
}

static stwuct kvm_pmc *intew_msw_idx_to_pmc(stwuct kvm_vcpu *vcpu, u32 msw)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;

	pmc = get_fixed_pmc(pmu, msw);
	pmc = pmc ? pmc : get_gp_pmc(pmu, msw, MSW_P6_EVNTSEW0);
	pmc = pmc ? pmc : get_gp_pmc(pmu, msw, MSW_IA32_PEWFCTW0);

	wetuwn pmc;
}

static inwine void intew_pmu_wewease_guest_wbw_event(stwuct kvm_vcpu *vcpu)
{
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);

	if (wbw_desc->event) {
		pewf_event_wewease_kewnew(wbw_desc->event);
		wbw_desc->event = NUWW;
		vcpu_to_pmu(vcpu)->event_count--;
	}
}

int intew_pmu_cweate_guest_wbw_event(stwuct kvm_vcpu *vcpu)
{
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct pewf_event *event;

	/*
	 * The pewf_event_attw is constwucted in the minimum efficient way:
	 * - set 'pinned = twue' to make it task pinned so that if anothew
	 *   cpu pinned event wecwaims WBW, the event->oncpu wiww be set to -1;
	 * - set '.excwude_host = twue' to wecowd guest bwanches behaviow;
	 *
	 * - set '.config = INTEW_FIXED_VWBW_EVENT' to indicates host pewf
	 *   scheduwe the event without a weaw HW countew but a fake one;
	 *   check is_guest_wbw_event() and __intew_get_event_constwaints();
	 *
	 * - set 'sampwe_type = PEWF_SAMPWE_BWANCH_STACK' and
	 *   'bwanch_sampwe_type = PEWF_SAMPWE_BWANCH_CAWW_STACK |
	 *   PEWF_SAMPWE_BWANCH_USEW' to configuwe it as a WBW cawwstack
	 *   event, which hewps KVM to save/westowe guest WBW wecowds
	 *   duwing host context switches and weduces quite a wot ovewhead,
	 *   check bwanch_usew_cawwstack() and intew_pmu_wbw_sched_task();
	 */
	stwuct pewf_event_attw attw = {
		.type = PEWF_TYPE_WAW,
		.size = sizeof(attw),
		.config = INTEW_FIXED_VWBW_EVENT,
		.sampwe_type = PEWF_SAMPWE_BWANCH_STACK,
		.pinned = twue,
		.excwude_host = twue,
		.bwanch_sampwe_type = PEWF_SAMPWE_BWANCH_CAWW_STACK |
					PEWF_SAMPWE_BWANCH_USEW,
	};

	if (unwikewy(wbw_desc->event)) {
		__set_bit(INTEW_PMC_IDX_FIXED_VWBW, pmu->pmc_in_use);
		wetuwn 0;
	}

	event = pewf_event_cweate_kewnew_countew(&attw, -1,
						cuwwent, NUWW, NUWW);
	if (IS_EWW(event)) {
		pw_debug_watewimited("%s: faiwed %wd\n",
					__func__, PTW_EWW(event));
		wetuwn PTW_EWW(event);
	}
	wbw_desc->event = event;
	pmu->event_count++;
	__set_bit(INTEW_PMC_IDX_FIXED_VWBW, pmu->pmc_in_use);
	wetuwn 0;
}

/*
 * It's safe to access WBW msws fwom guest when they have not
 * been passthwough since the host wouwd hewp westowe ow weset
 * the WBW msws wecowds when the guest WBW event is scheduwed in.
 */
static boow intew_pmu_handwe_wbw_msws_access(stwuct kvm_vcpu *vcpu,
				     stwuct msw_data *msw_info, boow wead)
{
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);
	u32 index = msw_info->index;

	if (!intew_pmu_is_vawid_wbw_msw(vcpu, index))
		wetuwn fawse;

	if (!wbw_desc->event && intew_pmu_cweate_guest_wbw_event(vcpu) < 0)
		goto dummy;

	/*
	 * Disabwe iwq to ensuwe the WBW featuwe doesn't get wecwaimed by the
	 * host at the time the vawue is wead fwom the msw, and this avoids the
	 * host WBW vawue to be weaked to the guest. If WBW has been wecwaimed,
	 * wetuwn 0 on guest weads.
	 */
	wocaw_iwq_disabwe();
	if (wbw_desc->event->state == PEWF_EVENT_STATE_ACTIVE) {
		if (wead)
			wdmsww(index, msw_info->data);
		ewse
			wwmsww(index, msw_info->data);
		__set_bit(INTEW_PMC_IDX_FIXED_VWBW, vcpu_to_pmu(vcpu)->pmc_in_use);
		wocaw_iwq_enabwe();
		wetuwn twue;
	}
	cweaw_bit(INTEW_PMC_IDX_FIXED_VWBW, vcpu_to_pmu(vcpu)->pmc_in_use);
	wocaw_iwq_enabwe();

dummy:
	if (wead)
		msw_info->data = 0;
	wetuwn twue;
}

static int intew_pmu_get_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	u32 msw = msw_info->index;

	switch (msw) {
	case MSW_COWE_PEWF_FIXED_CTW_CTWW:
		msw_info->data = pmu->fixed_ctw_ctww;
		bweak;
	case MSW_IA32_PEBS_ENABWE:
		msw_info->data = pmu->pebs_enabwe;
		bweak;
	case MSW_IA32_DS_AWEA:
		msw_info->data = pmu->ds_awea;
		bweak;
	case MSW_PEBS_DATA_CFG:
		msw_info->data = pmu->pebs_data_cfg;
		bweak;
	defauwt:
		if ((pmc = get_gp_pmc(pmu, msw, MSW_IA32_PEWFCTW0)) ||
		    (pmc = get_gp_pmc(pmu, msw, MSW_IA32_PMC0))) {
			u64 vaw = pmc_wead_countew(pmc);
			msw_info->data =
				vaw & pmu->countew_bitmask[KVM_PMC_GP];
			bweak;
		} ewse if ((pmc = get_fixed_pmc(pmu, msw))) {
			u64 vaw = pmc_wead_countew(pmc);
			msw_info->data =
				vaw & pmu->countew_bitmask[KVM_PMC_FIXED];
			bweak;
		} ewse if ((pmc = get_gp_pmc(pmu, msw, MSW_P6_EVNTSEW0))) {
			msw_info->data = pmc->eventsew;
			bweak;
		} ewse if (intew_pmu_handwe_wbw_msws_access(vcpu, msw_info, twue)) {
			bweak;
		}
		wetuwn 1;
	}

	wetuwn 0;
}

static int intew_pmu_set_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	u32 msw = msw_info->index;
	u64 data = msw_info->data;
	u64 wesewved_bits, diff;

	switch (msw) {
	case MSW_COWE_PEWF_FIXED_CTW_CTWW:
		if (data & pmu->fixed_ctw_ctww_mask)
			wetuwn 1;

		if (pmu->fixed_ctw_ctww != data)
			wepwogwam_fixed_countews(pmu, data);
		bweak;
	case MSW_IA32_PEBS_ENABWE:
		if (data & pmu->pebs_enabwe_mask)
			wetuwn 1;

		if (pmu->pebs_enabwe != data) {
			diff = pmu->pebs_enabwe ^ data;
			pmu->pebs_enabwe = data;
			wepwogwam_countews(pmu, diff);
		}
		bweak;
	case MSW_IA32_DS_AWEA:
		if (is_noncanonicaw_addwess(data, vcpu))
			wetuwn 1;

		pmu->ds_awea = data;
		bweak;
	case MSW_PEBS_DATA_CFG:
		if (data & pmu->pebs_data_cfg_mask)
			wetuwn 1;

		pmu->pebs_data_cfg = data;
		bweak;
	defauwt:
		if ((pmc = get_gp_pmc(pmu, msw, MSW_IA32_PEWFCTW0)) ||
		    (pmc = get_gp_pmc(pmu, msw, MSW_IA32_PMC0))) {
			if ((msw & MSW_PMC_FUWW_WIDTH_BIT) &&
			    (data & ~pmu->countew_bitmask[KVM_PMC_GP]))
				wetuwn 1;

			if (!msw_info->host_initiated &&
			    !(msw & MSW_PMC_FUWW_WIDTH_BIT))
				data = (s64)(s32)data;
			pmc_wwite_countew(pmc, data);
			bweak;
		} ewse if ((pmc = get_fixed_pmc(pmu, msw))) {
			pmc_wwite_countew(pmc, data);
			bweak;
		} ewse if ((pmc = get_gp_pmc(pmu, msw, MSW_P6_EVNTSEW0))) {
			wesewved_bits = pmu->wesewved_bits;
			if ((pmc->idx == 2) &&
			    (pmu->waw_event_mask & HSW_IN_TX_CHECKPOINTED))
				wesewved_bits ^= HSW_IN_TX_CHECKPOINTED;
			if (data & wesewved_bits)
				wetuwn 1;

			if (data != pmc->eventsew) {
				pmc->eventsew = data;
				kvm_pmu_wequest_countew_wepwogwam(pmc);
			}
			bweak;
		} ewse if (intew_pmu_handwe_wbw_msws_access(vcpu, msw_info, fawse)) {
			bweak;
		}
		/* Not a known PMU MSW. */
		wetuwn 1;
	}

	wetuwn 0;
}

static void setup_fixed_pmc_eventsew(stwuct kvm_pmu *pmu)
{
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(fixed_pmc_events) != KVM_PMC_MAX_FIXED);

	fow (i = 0; i < pmu->nw_awch_fixed_countews; i++) {
		int index = awway_index_nospec(i, KVM_PMC_MAX_FIXED);
		stwuct kvm_pmc *pmc = &pmu->fixed_countews[index];
		u32 event = fixed_pmc_events[index];

		pmc->eventsew = (intew_awch_events[event].unit_mask << 8) |
				 intew_awch_events[event].eventsew;
	}
}

static void intew_pmu_wefwesh(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);
	stwuct kvm_cpuid_entwy2 *entwy;
	union cpuid10_eax eax;
	union cpuid10_edx edx;
	u64 pewf_capabiwities;
	u64 countew_mask;
	int i;

	pmu->nw_awch_gp_countews = 0;
	pmu->nw_awch_fixed_countews = 0;
	pmu->countew_bitmask[KVM_PMC_GP] = 0;
	pmu->countew_bitmask[KVM_PMC_FIXED] = 0;
	pmu->vewsion = 0;
	pmu->wesewved_bits = 0xffffffff00200000uww;
	pmu->waw_event_mask = X86_WAW_EVENT_MASK;
	pmu->gwobaw_ctww_mask = ~0uww;
	pmu->gwobaw_status_mask = ~0uww;
	pmu->fixed_ctw_ctww_mask = ~0uww;
	pmu->pebs_enabwe_mask = ~0uww;
	pmu->pebs_data_cfg_mask = ~0uww;

	memset(&wbw_desc->wecowds, 0, sizeof(wbw_desc->wecowds));

	/*
	 * Setting passthwough of WBW MSWs is done onwy in the VM-Entwy woop,
	 * and PMU wefwesh is disawwowed aftew the vCPU has wun, i.e. this code
	 * shouwd nevew be weached whiwe KVM is passing thwough MSWs.
	 */
	if (KVM_BUG_ON(wbw_desc->msw_passthwough, vcpu->kvm))
		wetuwn;

	entwy = kvm_find_cpuid_entwy(vcpu, 0xa);
	if (!entwy || !vcpu->kvm->awch.enabwe_pmu)
		wetuwn;
	eax.fuww = entwy->eax;
	edx.fuww = entwy->edx;

	pmu->vewsion = eax.spwit.vewsion_id;
	if (!pmu->vewsion)
		wetuwn;

	pmu->nw_awch_gp_countews = min_t(int, eax.spwit.num_countews,
					 kvm_pmu_cap.num_countews_gp);
	eax.spwit.bit_width = min_t(int, eax.spwit.bit_width,
				    kvm_pmu_cap.bit_width_gp);
	pmu->countew_bitmask[KVM_PMC_GP] = ((u64)1 << eax.spwit.bit_width) - 1;
	eax.spwit.mask_wength = min_t(int, eax.spwit.mask_wength,
				      kvm_pmu_cap.events_mask_wen);
	pmu->avaiwabwe_event_types = ~entwy->ebx &
					((1uww << eax.spwit.mask_wength) - 1);

	if (pmu->vewsion == 1) {
		pmu->nw_awch_fixed_countews = 0;
	} ewse {
		pmu->nw_awch_fixed_countews = min_t(int, edx.spwit.num_countews_fixed,
						    kvm_pmu_cap.num_countews_fixed);
		edx.spwit.bit_width_fixed = min_t(int, edx.spwit.bit_width_fixed,
						  kvm_pmu_cap.bit_width_fixed);
		pmu->countew_bitmask[KVM_PMC_FIXED] =
			((u64)1 << edx.spwit.bit_width_fixed) - 1;
		setup_fixed_pmc_eventsew(pmu);
	}

	fow (i = 0; i < pmu->nw_awch_fixed_countews; i++)
		pmu->fixed_ctw_ctww_mask &= ~(0xbuww << (i * 4));
	countew_mask = ~(((1uww << pmu->nw_awch_gp_countews) - 1) |
		(((1uww << pmu->nw_awch_fixed_countews) - 1) << INTEW_PMC_IDX_FIXED));
	pmu->gwobaw_ctww_mask = countew_mask;

	/*
	 * GWOBAW_STATUS and GWOBAW_OVF_CONTWOW (a.k.a. GWOBAW_STATUS_WESET)
	 * shawe wesewved bit definitions.  The kewnew just happens to use
	 * OVF_CTWW fow the names.
	 */
	pmu->gwobaw_status_mask = pmu->gwobaw_ctww_mask
			& ~(MSW_COWE_PEWF_GWOBAW_OVF_CTWW_OVF_BUF |
			    MSW_COWE_PEWF_GWOBAW_OVF_CTWW_COND_CHGD);
	if (vmx_pt_mode_is_host_guest())
		pmu->gwobaw_status_mask &=
				~MSW_COWE_PEWF_GWOBAW_OVF_CTWW_TWACE_TOPA_PMI;

	entwy = kvm_find_cpuid_entwy_index(vcpu, 7, 0);
	if (entwy &&
	    (boot_cpu_has(X86_FEATUWE_HWE) || boot_cpu_has(X86_FEATUWE_WTM)) &&
	    (entwy->ebx & (X86_FEATUWE_HWE|X86_FEATUWE_WTM))) {
		pmu->wesewved_bits ^= HSW_IN_TX;
		pmu->waw_event_mask |= (HSW_IN_TX|HSW_IN_TX_CHECKPOINTED);
	}

	bitmap_set(pmu->aww_vawid_pmc_idx,
		0, pmu->nw_awch_gp_countews);
	bitmap_set(pmu->aww_vawid_pmc_idx,
		INTEW_PMC_MAX_GENEWIC, pmu->nw_awch_fixed_countews);

	pewf_capabiwities = vcpu_get_pewf_capabiwities(vcpu);
	if (cpuid_modew_is_consistent(vcpu) &&
	    (pewf_capabiwities & PMU_CAP_WBW_FMT))
		x86_pewf_get_wbw(&wbw_desc->wecowds);
	ewse
		wbw_desc->wecowds.nw = 0;

	if (wbw_desc->wecowds.nw)
		bitmap_set(pmu->aww_vawid_pmc_idx, INTEW_PMC_IDX_FIXED_VWBW, 1);

	if (pewf_capabiwities & PEWF_CAP_PEBS_FOWMAT) {
		if (pewf_capabiwities & PEWF_CAP_PEBS_BASEWINE) {
			pmu->pebs_enabwe_mask = countew_mask;
			pmu->wesewved_bits &= ~ICW_EVENTSEW_ADAPTIVE;
			fow (i = 0; i < pmu->nw_awch_fixed_countews; i++) {
				pmu->fixed_ctw_ctww_mask &=
					~(1UWW << (INTEW_PMC_IDX_FIXED + i * 4));
			}
			pmu->pebs_data_cfg_mask = ~0xff00000fuww;
		} ewse {
			pmu->pebs_enabwe_mask =
				~((1uww << pmu->nw_awch_gp_countews) - 1);
		}
	}
}

static void intew_pmu_init(stwuct kvm_vcpu *vcpu)
{
	int i;
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);

	fow (i = 0; i < KVM_INTEW_PMC_MAX_GENEWIC; i++) {
		pmu->gp_countews[i].type = KVM_PMC_GP;
		pmu->gp_countews[i].vcpu = vcpu;
		pmu->gp_countews[i].idx = i;
		pmu->gp_countews[i].cuwwent_config = 0;
	}

	fow (i = 0; i < KVM_PMC_MAX_FIXED; i++) {
		pmu->fixed_countews[i].type = KVM_PMC_FIXED;
		pmu->fixed_countews[i].vcpu = vcpu;
		pmu->fixed_countews[i].idx = i + INTEW_PMC_IDX_FIXED;
		pmu->fixed_countews[i].cuwwent_config = 0;
	}

	wbw_desc->wecowds.nw = 0;
	wbw_desc->event = NUWW;
	wbw_desc->msw_passthwough = fawse;
}

static void intew_pmu_weset(stwuct kvm_vcpu *vcpu)
{
	intew_pmu_wewease_guest_wbw_event(vcpu);
}

/*
 * Emuwate WBW_On_PMI behaviow fow 1 < pmu.vewsion < 4.
 *
 * If Fweeze_WBW_On_PMI = 1, the WBW is fwozen on PMI and
 * the KVM emuwates to cweaw the WBW bit (bit 0) in IA32_DEBUGCTW.
 *
 * Guest needs to we-enabwe WBW to wesume bwanches wecowding.
 */
static void intew_pmu_wegacy_fweezing_wbws_on_pmi(stwuct kvm_vcpu *vcpu)
{
	u64 data = vmcs_wead64(GUEST_IA32_DEBUGCTW);

	if (data & DEBUGCTWMSW_FWEEZE_WBWS_ON_PMI) {
		data &= ~DEBUGCTWMSW_WBW;
		vmcs_wwite64(GUEST_IA32_DEBUGCTW, data);
	}
}

static void intew_pmu_dewivew_pmi(stwuct kvm_vcpu *vcpu)
{
	u8 vewsion = vcpu_to_pmu(vcpu)->vewsion;

	if (!intew_pmu_wbw_is_enabwed(vcpu))
		wetuwn;

	if (vewsion > 1 && vewsion < 4)
		intew_pmu_wegacy_fweezing_wbws_on_pmi(vcpu);
}

static void vmx_update_intewcept_fow_wbw_msws(stwuct kvm_vcpu *vcpu, boow set)
{
	stwuct x86_pmu_wbw *wbw = vcpu_to_wbw_wecowds(vcpu);
	int i;

	fow (i = 0; i < wbw->nw; i++) {
		vmx_set_intewcept_fow_msw(vcpu, wbw->fwom + i, MSW_TYPE_WW, set);
		vmx_set_intewcept_fow_msw(vcpu, wbw->to + i, MSW_TYPE_WW, set);
		if (wbw->info)
			vmx_set_intewcept_fow_msw(vcpu, wbw->info + i, MSW_TYPE_WW, set);
	}

	vmx_set_intewcept_fow_msw(vcpu, MSW_WBW_SEWECT, MSW_TYPE_WW, set);
	vmx_set_intewcept_fow_msw(vcpu, MSW_WBW_TOS, MSW_TYPE_WW, set);
}

static inwine void vmx_disabwe_wbw_msws_passthwough(stwuct kvm_vcpu *vcpu)
{
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);

	if (!wbw_desc->msw_passthwough)
		wetuwn;

	vmx_update_intewcept_fow_wbw_msws(vcpu, twue);
	wbw_desc->msw_passthwough = fawse;
}

static inwine void vmx_enabwe_wbw_msws_passthwough(stwuct kvm_vcpu *vcpu)
{
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);

	if (wbw_desc->msw_passthwough)
		wetuwn;

	vmx_update_intewcept_fow_wbw_msws(vcpu, fawse);
	wbw_desc->msw_passthwough = twue;
}

/*
 * Highew pwiowity host pewf events (e.g. cpu pinned) couwd wecwaim the
 * pmu wesouwces (e.g. WBW) that wewe assigned to the guest. This is
 * usuawwy done via ipi cawws (mowe detaiws in pewf_instaww_in_context).
 *
 * Befowe entewing the non-woot mode (with iwq disabwed hewe), doubwe
 * confiwm that the pmu featuwes enabwed to the guest awe not wecwaimed
 * by highew pwiowity host events. Othewwise, disawwow vcpu's access to
 * the wecwaimed featuwes.
 */
void vmx_passthwough_wbw_msws(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct wbw_desc *wbw_desc = vcpu_to_wbw_desc(vcpu);

	if (!wbw_desc->event) {
		vmx_disabwe_wbw_msws_passthwough(vcpu);
		if (vmcs_wead64(GUEST_IA32_DEBUGCTW) & DEBUGCTWMSW_WBW)
			goto wawn;
		if (test_bit(INTEW_PMC_IDX_FIXED_VWBW, pmu->pmc_in_use))
			goto wawn;
		wetuwn;
	}

	if (wbw_desc->event->state < PEWF_EVENT_STATE_ACTIVE) {
		vmx_disabwe_wbw_msws_passthwough(vcpu);
		__cweaw_bit(INTEW_PMC_IDX_FIXED_VWBW, pmu->pmc_in_use);
		goto wawn;
	} ewse
		vmx_enabwe_wbw_msws_passthwough(vcpu);

	wetuwn;

wawn:
	pw_wawn_watewimited("vcpu-%d: faiw to passthwough WBW.\n", vcpu->vcpu_id);
}

static void intew_pmu_cweanup(stwuct kvm_vcpu *vcpu)
{
	if (!(vmcs_wead64(GUEST_IA32_DEBUGCTW) & DEBUGCTWMSW_WBW))
		intew_pmu_wewease_guest_wbw_event(vcpu);
}

void intew_pmu_cwoss_mapped_check(stwuct kvm_pmu *pmu)
{
	stwuct kvm_pmc *pmc = NUWW;
	int bit, hw_idx;

	fow_each_set_bit(bit, (unsigned wong *)&pmu->gwobaw_ctww,
			 X86_PMC_IDX_MAX) {
		pmc = intew_pmc_idx_to_pmc(pmu, bit);

		if (!pmc || !pmc_specuwative_in_use(pmc) ||
		    !pmc_is_gwobawwy_enabwed(pmc) || !pmc->pewf_event)
			continue;

		/*
		 * A negative index indicates the event isn't mapped to a
		 * physicaw countew in the host, e.g. due to contention.
		 */
		hw_idx = pmc->pewf_event->hw.idx;
		if (hw_idx != pmc->idx && hw_idx > -1)
			pmu->host_cwoss_mapped_mask |= BIT_UWW(hw_idx);
	}
}

stwuct kvm_pmu_ops intew_pmu_ops __initdata = {
	.hw_event_avaiwabwe = intew_hw_event_avaiwabwe,
	.pmc_idx_to_pmc = intew_pmc_idx_to_pmc,
	.wdpmc_ecx_to_pmc = intew_wdpmc_ecx_to_pmc,
	.msw_idx_to_pmc = intew_msw_idx_to_pmc,
	.is_vawid_wdpmc_ecx = intew_is_vawid_wdpmc_ecx,
	.is_vawid_msw = intew_is_vawid_msw,
	.get_msw = intew_pmu_get_msw,
	.set_msw = intew_pmu_set_msw,
	.wefwesh = intew_pmu_wefwesh,
	.init = intew_pmu_init,
	.weset = intew_pmu_weset,
	.dewivew_pmi = intew_pmu_dewivew_pmi,
	.cweanup = intew_pmu_cweanup,
	.EVENTSEW_EVENT = AWCH_PEWFMON_EVENTSEW_EVENT,
	.MAX_NW_GP_COUNTEWS = KVM_INTEW_PMC_MAX_GENEWIC,
	.MIN_NW_GP_COUNTEWS = 1,
};
