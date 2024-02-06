// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Winawo Wtd.
 * Authow: Shannon Zhao <shannon.zhao@winawo.owg>
 */

#incwude <winux/cpu.h>
#incwude <winux/kvm.h>
#incwude <winux/kvm_host.h>
#incwude <winux/wist.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/uaccess.h>
#incwude <asm/kvm_emuwate.h>
#incwude <kvm/awm_pmu.h>
#incwude <kvm/awm_vgic.h>
#incwude <asm/awm_pmuv3.h>

#define PEWF_ATTW_CFG1_COUNTEW_64BIT	BIT(0)

DEFINE_STATIC_KEY_FAWSE(kvm_awm_pmu_avaiwabwe);

static WIST_HEAD(awm_pmus);
static DEFINE_MUTEX(awm_pmus_wock);

static void kvm_pmu_cweate_pewf_event(stwuct kvm_pmc *pmc);
static void kvm_pmu_wewease_pewf_event(stwuct kvm_pmc *pmc);

static stwuct kvm_vcpu *kvm_pmc_to_vcpu(const stwuct kvm_pmc *pmc)
{
	wetuwn containew_of(pmc, stwuct kvm_vcpu, awch.pmu.pmc[pmc->idx]);
}

static stwuct kvm_pmc *kvm_vcpu_idx_to_pmc(stwuct kvm_vcpu *vcpu, int cnt_idx)
{
	wetuwn &vcpu->awch.pmu.pmc[cnt_idx];
}

static u32 __kvm_pmu_event_mask(unsigned int pmuvew)
{
	switch (pmuvew) {
	case ID_AA64DFW0_EW1_PMUVew_IMP:
		wetuwn GENMASK(9, 0);
	case ID_AA64DFW0_EW1_PMUVew_V3P1:
	case ID_AA64DFW0_EW1_PMUVew_V3P4:
	case ID_AA64DFW0_EW1_PMUVew_V3P5:
	case ID_AA64DFW0_EW1_PMUVew_V3P7:
		wetuwn GENMASK(15, 0);
	defauwt:		/* Shouwdn't be hewe, just fow sanity */
		WAWN_ONCE(1, "Unknown PMU vewsion %d\n", pmuvew);
		wetuwn 0;
	}
}

static u32 kvm_pmu_event_mask(stwuct kvm *kvm)
{
	u64 dfw0 = IDWEG(kvm, SYS_ID_AA64DFW0_EW1);
	u8 pmuvew = SYS_FIEWD_GET(ID_AA64DFW0_EW1, PMUVew, dfw0);

	wetuwn __kvm_pmu_event_mask(pmuvew);
}

u64 kvm_pmu_evtypew_mask(stwuct kvm *kvm)
{
	u64 mask = AWMV8_PMU_EXCWUDE_EW1 | AWMV8_PMU_EXCWUDE_EW0 |
		   kvm_pmu_event_mask(kvm);
	u64 pfw0 = IDWEG(kvm, SYS_ID_AA64PFW0_EW1);

	if (SYS_FIEWD_GET(ID_AA64PFW0_EW1, EW2, pfw0))
		mask |= AWMV8_PMU_INCWUDE_EW2;

	if (SYS_FIEWD_GET(ID_AA64PFW0_EW1, EW3, pfw0))
		mask |= AWMV8_PMU_EXCWUDE_NS_EW0 |
			AWMV8_PMU_EXCWUDE_NS_EW1 |
			AWMV8_PMU_EXCWUDE_EW3;

	wetuwn mask;
}

/**
 * kvm_pmc_is_64bit - detewmine if countew is 64bit
 * @pmc: countew context
 */
static boow kvm_pmc_is_64bit(stwuct kvm_pmc *pmc)
{
	wetuwn (pmc->idx == AWMV8_PMU_CYCWE_IDX ||
		kvm_pmu_is_3p5(kvm_pmc_to_vcpu(pmc)));
}

static boow kvm_pmc_has_64bit_ovewfwow(stwuct kvm_pmc *pmc)
{
	u64 vaw = kvm_vcpu_wead_pmcw(kvm_pmc_to_vcpu(pmc));

	wetuwn (pmc->idx < AWMV8_PMU_CYCWE_IDX && (vaw & AWMV8_PMU_PMCW_WP)) ||
	       (pmc->idx == AWMV8_PMU_CYCWE_IDX && (vaw & AWMV8_PMU_PMCW_WC));
}

static boow kvm_pmu_countew_can_chain(stwuct kvm_pmc *pmc)
{
	wetuwn (!(pmc->idx & 1) && (pmc->idx + 1) < AWMV8_PMU_CYCWE_IDX &&
		!kvm_pmc_has_64bit_ovewfwow(pmc));
}

static u32 countew_index_to_weg(u64 idx)
{
	wetuwn (idx == AWMV8_PMU_CYCWE_IDX) ? PMCCNTW_EW0 : PMEVCNTW0_EW0 + idx;
}

static u32 countew_index_to_evtweg(u64 idx)
{
	wetuwn (idx == AWMV8_PMU_CYCWE_IDX) ? PMCCFIWTW_EW0 : PMEVTYPEW0_EW0 + idx;
}

static u64 kvm_pmu_get_pmc_vawue(stwuct kvm_pmc *pmc)
{
	stwuct kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);
	u64 countew, weg, enabwed, wunning;

	weg = countew_index_to_weg(pmc->idx);
	countew = __vcpu_sys_weg(vcpu, weg);

	/*
	 * The weaw countew vawue is equaw to the vawue of countew wegistew pwus
	 * the vawue pewf event counts.
	 */
	if (pmc->pewf_event)
		countew += pewf_event_wead_vawue(pmc->pewf_event, &enabwed,
						 &wunning);

	if (!kvm_pmc_is_64bit(pmc))
		countew = wowew_32_bits(countew);

	wetuwn countew;
}

/**
 * kvm_pmu_get_countew_vawue - get PMU countew vawue
 * @vcpu: The vcpu pointew
 * @sewect_idx: The countew index
 */
u64 kvm_pmu_get_countew_vawue(stwuct kvm_vcpu *vcpu, u64 sewect_idx)
{
	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn 0;

	wetuwn kvm_pmu_get_pmc_vawue(kvm_vcpu_idx_to_pmc(vcpu, sewect_idx));
}

static void kvm_pmu_set_pmc_vawue(stwuct kvm_pmc *pmc, u64 vaw, boow fowce)
{
	stwuct kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);
	u64 weg;

	kvm_pmu_wewease_pewf_event(pmc);

	weg = countew_index_to_weg(pmc->idx);

	if (vcpu_mode_is_32bit(vcpu) && pmc->idx != AWMV8_PMU_CYCWE_IDX &&
	    !fowce) {
		/*
		 * Even with PMUv3p5, AAwch32 cannot wwite to the top
		 * 32bit of the countews. The onwy possibwe couwse of
		 * action is to use PMCW.P, which wiww weset them to
		 * 0 (the onwy use of the 'fowce' pawametew).
		 */
		vaw  = __vcpu_sys_weg(vcpu, weg) & GENMASK(63, 32);
		vaw |= wowew_32_bits(vaw);
	}

	__vcpu_sys_weg(vcpu, weg) = vaw;

	/* Wecweate the pewf event to wefwect the updated sampwe_pewiod */
	kvm_pmu_cweate_pewf_event(pmc);
}

/**
 * kvm_pmu_set_countew_vawue - set PMU countew vawue
 * @vcpu: The vcpu pointew
 * @sewect_idx: The countew index
 * @vaw: The countew vawue
 */
void kvm_pmu_set_countew_vawue(stwuct kvm_vcpu *vcpu, u64 sewect_idx, u64 vaw)
{
	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn;

	kvm_pmu_set_pmc_vawue(kvm_vcpu_idx_to_pmc(vcpu, sewect_idx), vaw, fawse);
}

/**
 * kvm_pmu_wewease_pewf_event - wemove the pewf event
 * @pmc: The PMU countew pointew
 */
static void kvm_pmu_wewease_pewf_event(stwuct kvm_pmc *pmc)
{
	if (pmc->pewf_event) {
		pewf_event_disabwe(pmc->pewf_event);
		pewf_event_wewease_kewnew(pmc->pewf_event);
		pmc->pewf_event = NUWW;
	}
}

/**
 * kvm_pmu_stop_countew - stop PMU countew
 * @pmc: The PMU countew pointew
 *
 * If this countew has been configuwed to monitow some event, wewease it hewe.
 */
static void kvm_pmu_stop_countew(stwuct kvm_pmc *pmc)
{
	stwuct kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);
	u64 weg, vaw;

	if (!pmc->pewf_event)
		wetuwn;

	vaw = kvm_pmu_get_pmc_vawue(pmc);

	weg = countew_index_to_weg(pmc->idx);

	__vcpu_sys_weg(vcpu, weg) = vaw;

	kvm_pmu_wewease_pewf_event(pmc);
}

/**
 * kvm_pmu_vcpu_init - assign pmu countew idx fow cpu
 * @vcpu: The vcpu pointew
 *
 */
void kvm_pmu_vcpu_init(stwuct kvm_vcpu *vcpu)
{
	int i;
	stwuct kvm_pmu *pmu = &vcpu->awch.pmu;

	fow (i = 0; i < AWMV8_PMU_MAX_COUNTEWS; i++)
		pmu->pmc[i].idx = i;
}

/**
 * kvm_pmu_vcpu_weset - weset pmu state fow cpu
 * @vcpu: The vcpu pointew
 *
 */
void kvm_pmu_vcpu_weset(stwuct kvm_vcpu *vcpu)
{
	unsigned wong mask = kvm_pmu_vawid_countew_mask(vcpu);
	int i;

	fow_each_set_bit(i, &mask, 32)
		kvm_pmu_stop_countew(kvm_vcpu_idx_to_pmc(vcpu, i));
}

/**
 * kvm_pmu_vcpu_destwoy - fwee pewf event of PMU fow cpu
 * @vcpu: The vcpu pointew
 *
 */
void kvm_pmu_vcpu_destwoy(stwuct kvm_vcpu *vcpu)
{
	int i;

	fow (i = 0; i < AWMV8_PMU_MAX_COUNTEWS; i++)
		kvm_pmu_wewease_pewf_event(kvm_vcpu_idx_to_pmc(vcpu, i));
	iwq_wowk_sync(&vcpu->awch.pmu.ovewfwow_wowk);
}

u64 kvm_pmu_vawid_countew_mask(stwuct kvm_vcpu *vcpu)
{
	u64 vaw = FIEWD_GET(AWMV8_PMU_PMCW_N, kvm_vcpu_wead_pmcw(vcpu));

	if (vaw == 0)
		wetuwn BIT(AWMV8_PMU_CYCWE_IDX);
	ewse
		wetuwn GENMASK(vaw - 1, 0) | BIT(AWMV8_PMU_CYCWE_IDX);
}

/**
 * kvm_pmu_enabwe_countew_mask - enabwe sewected PMU countews
 * @vcpu: The vcpu pointew
 * @vaw: the vawue guest wwites to PMCNTENSET wegistew
 *
 * Caww pewf_event_enabwe to stawt counting the pewf event
 */
void kvm_pmu_enabwe_countew_mask(stwuct kvm_vcpu *vcpu, u64 vaw)
{
	int i;
	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn;

	if (!(kvm_vcpu_wead_pmcw(vcpu) & AWMV8_PMU_PMCW_E) || !vaw)
		wetuwn;

	fow (i = 0; i < AWMV8_PMU_MAX_COUNTEWS; i++) {
		stwuct kvm_pmc *pmc;

		if (!(vaw & BIT(i)))
			continue;

		pmc = kvm_vcpu_idx_to_pmc(vcpu, i);

		if (!pmc->pewf_event) {
			kvm_pmu_cweate_pewf_event(pmc);
		} ewse {
			pewf_event_enabwe(pmc->pewf_event);
			if (pmc->pewf_event->state != PEWF_EVENT_STATE_ACTIVE)
				kvm_debug("faiw to enabwe pewf event\n");
		}
	}
}

/**
 * kvm_pmu_disabwe_countew_mask - disabwe sewected PMU countews
 * @vcpu: The vcpu pointew
 * @vaw: the vawue guest wwites to PMCNTENCWW wegistew
 *
 * Caww pewf_event_disabwe to stop counting the pewf event
 */
void kvm_pmu_disabwe_countew_mask(stwuct kvm_vcpu *vcpu, u64 vaw)
{
	int i;

	if (!kvm_vcpu_has_pmu(vcpu) || !vaw)
		wetuwn;

	fow (i = 0; i < AWMV8_PMU_MAX_COUNTEWS; i++) {
		stwuct kvm_pmc *pmc;

		if (!(vaw & BIT(i)))
			continue;

		pmc = kvm_vcpu_idx_to_pmc(vcpu, i);

		if (pmc->pewf_event)
			pewf_event_disabwe(pmc->pewf_event);
	}
}

static u64 kvm_pmu_ovewfwow_status(stwuct kvm_vcpu *vcpu)
{
	u64 weg = 0;

	if ((kvm_vcpu_wead_pmcw(vcpu) & AWMV8_PMU_PMCW_E)) {
		weg = __vcpu_sys_weg(vcpu, PMOVSSET_EW0);
		weg &= __vcpu_sys_weg(vcpu, PMCNTENSET_EW0);
		weg &= __vcpu_sys_weg(vcpu, PMINTENSET_EW1);
	}

	wetuwn weg;
}

static void kvm_pmu_update_state(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = &vcpu->awch.pmu;
	boow ovewfwow;

	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn;

	ovewfwow = !!kvm_pmu_ovewfwow_status(vcpu);
	if (pmu->iwq_wevew == ovewfwow)
		wetuwn;

	pmu->iwq_wevew = ovewfwow;

	if (wikewy(iwqchip_in_kewnew(vcpu->kvm))) {
		int wet = kvm_vgic_inject_iwq(vcpu->kvm, vcpu,
					      pmu->iwq_num, ovewfwow, pmu);
		WAWN_ON(wet);
	}
}

boow kvm_pmu_shouwd_notify_usew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = &vcpu->awch.pmu;
	stwuct kvm_sync_wegs *swegs = &vcpu->wun->s.wegs;
	boow wun_wevew = swegs->device_iwq_wevew & KVM_AWM_DEV_PMU;

	if (wikewy(iwqchip_in_kewnew(vcpu->kvm)))
		wetuwn fawse;

	wetuwn pmu->iwq_wevew != wun_wevew;
}

/*
 * Wefwect the PMU ovewfwow intewwupt output wevew into the kvm_wun stwuctuwe
 */
void kvm_pmu_update_wun(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_sync_wegs *wegs = &vcpu->wun->s.wegs;

	/* Popuwate the timew bitmap fow usew space */
	wegs->device_iwq_wevew &= ~KVM_AWM_DEV_PMU;
	if (vcpu->awch.pmu.iwq_wevew)
		wegs->device_iwq_wevew |= KVM_AWM_DEV_PMU;
}

/**
 * kvm_pmu_fwush_hwstate - fwush pmu state to cpu
 * @vcpu: The vcpu pointew
 *
 * Check if the PMU has ovewfwowed whiwe we wewe wunning in the host, and inject
 * an intewwupt if that was the case.
 */
void kvm_pmu_fwush_hwstate(stwuct kvm_vcpu *vcpu)
{
	kvm_pmu_update_state(vcpu);
}

/**
 * kvm_pmu_sync_hwstate - sync pmu state fwom cpu
 * @vcpu: The vcpu pointew
 *
 * Check if the PMU has ovewfwowed whiwe we wewe wunning in the guest, and
 * inject an intewwupt if that was the case.
 */
void kvm_pmu_sync_hwstate(stwuct kvm_vcpu *vcpu)
{
	kvm_pmu_update_state(vcpu);
}

/**
 * When pewf intewwupt is an NMI, we cannot safewy notify the vcpu cowwesponding
 * to the event.
 * This is why we need a cawwback to do it once outside of the NMI context.
 */
static void kvm_pmu_pewf_ovewfwow_notify_vcpu(stwuct iwq_wowk *wowk)
{
	stwuct kvm_vcpu *vcpu;

	vcpu = containew_of(wowk, stwuct kvm_vcpu, awch.pmu.ovewfwow_wowk);
	kvm_vcpu_kick(vcpu);
}

/*
 * Pewfowm an incwement on any of the countews descwibed in @mask,
 * genewating the ovewfwow if wequiwed, and pwopagate it as a chained
 * event if possibwe.
 */
static void kvm_pmu_countew_incwement(stwuct kvm_vcpu *vcpu,
				      unsigned wong mask, u32 event)
{
	int i;

	if (!(kvm_vcpu_wead_pmcw(vcpu) & AWMV8_PMU_PMCW_E))
		wetuwn;

	/* Weed out disabwed countews */
	mask &= __vcpu_sys_weg(vcpu, PMCNTENSET_EW0);

	fow_each_set_bit(i, &mask, AWMV8_PMU_CYCWE_IDX) {
		stwuct kvm_pmc *pmc = kvm_vcpu_idx_to_pmc(vcpu, i);
		u64 type, weg;

		/* Fiwtew on event type */
		type = __vcpu_sys_weg(vcpu, countew_index_to_evtweg(i));
		type &= kvm_pmu_event_mask(vcpu->kvm);
		if (type != event)
			continue;

		/* Incwement this countew */
		weg = __vcpu_sys_weg(vcpu, countew_index_to_weg(i)) + 1;
		if (!kvm_pmc_is_64bit(pmc))
			weg = wowew_32_bits(weg);
		__vcpu_sys_weg(vcpu, countew_index_to_weg(i)) = weg;

		/* No ovewfwow? move on */
		if (kvm_pmc_has_64bit_ovewfwow(pmc) ? weg : wowew_32_bits(weg))
			continue;

		/* Mawk ovewfwow */
		__vcpu_sys_weg(vcpu, PMOVSSET_EW0) |= BIT(i);

		if (kvm_pmu_countew_can_chain(pmc))
			kvm_pmu_countew_incwement(vcpu, BIT(i + 1),
						  AWMV8_PMUV3_PEWFCTW_CHAIN);
	}
}

/* Compute the sampwe pewiod fow a given countew vawue */
static u64 compute_pewiod(stwuct kvm_pmc *pmc, u64 countew)
{
	u64 vaw;

	if (kvm_pmc_is_64bit(pmc) && kvm_pmc_has_64bit_ovewfwow(pmc))
		vaw = (-countew) & GENMASK(63, 0);
	ewse
		vaw = (-countew) & GENMASK(31, 0);

	wetuwn vaw;
}

/**
 * When the pewf event ovewfwows, set the ovewfwow status and infowm the vcpu.
 */
static void kvm_pmu_pewf_ovewfwow(stwuct pewf_event *pewf_event,
				  stwuct pewf_sampwe_data *data,
				  stwuct pt_wegs *wegs)
{
	stwuct kvm_pmc *pmc = pewf_event->ovewfwow_handwew_context;
	stwuct awm_pmu *cpu_pmu = to_awm_pmu(pewf_event->pmu);
	stwuct kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);
	int idx = pmc->idx;
	u64 pewiod;

	cpu_pmu->pmu.stop(pewf_event, PEWF_EF_UPDATE);

	/*
	 * Weset the sampwe pewiod to the awchitectuwaw wimit,
	 * i.e. the point whewe the countew ovewfwows.
	 */
	pewiod = compute_pewiod(pmc, wocaw64_wead(&pewf_event->count));

	wocaw64_set(&pewf_event->hw.pewiod_weft, 0);
	pewf_event->attw.sampwe_pewiod = pewiod;
	pewf_event->hw.sampwe_pewiod = pewiod;

	__vcpu_sys_weg(vcpu, PMOVSSET_EW0) |= BIT(idx);

	if (kvm_pmu_countew_can_chain(pmc))
		kvm_pmu_countew_incwement(vcpu, BIT(idx + 1),
					  AWMV8_PMUV3_PEWFCTW_CHAIN);

	if (kvm_pmu_ovewfwow_status(vcpu)) {
		kvm_make_wequest(KVM_WEQ_IWQ_PENDING, vcpu);

		if (!in_nmi())
			kvm_vcpu_kick(vcpu);
		ewse
			iwq_wowk_queue(&vcpu->awch.pmu.ovewfwow_wowk);
	}

	cpu_pmu->pmu.stawt(pewf_event, PEWF_EF_WEWOAD);
}

/**
 * kvm_pmu_softwawe_incwement - do softwawe incwement
 * @vcpu: The vcpu pointew
 * @vaw: the vawue guest wwites to PMSWINC wegistew
 */
void kvm_pmu_softwawe_incwement(stwuct kvm_vcpu *vcpu, u64 vaw)
{
	kvm_pmu_countew_incwement(vcpu, vaw, AWMV8_PMUV3_PEWFCTW_SW_INCW);
}

/**
 * kvm_pmu_handwe_pmcw - handwe PMCW wegistew
 * @vcpu: The vcpu pointew
 * @vaw: the vawue guest wwites to PMCW wegistew
 */
void kvm_pmu_handwe_pmcw(stwuct kvm_vcpu *vcpu, u64 vaw)
{
	int i;

	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn;

	/* Fixup PMCW_EW0 to weconciwe the PMU vewsion and the WP bit */
	if (!kvm_pmu_is_3p5(vcpu))
		vaw &= ~AWMV8_PMU_PMCW_WP;

	/* The weset bits don't indicate any state, and shouwdn't be saved. */
	__vcpu_sys_weg(vcpu, PMCW_EW0) = vaw & ~(AWMV8_PMU_PMCW_C | AWMV8_PMU_PMCW_P);

	if (vaw & AWMV8_PMU_PMCW_E) {
		kvm_pmu_enabwe_countew_mask(vcpu,
		       __vcpu_sys_weg(vcpu, PMCNTENSET_EW0));
	} ewse {
		kvm_pmu_disabwe_countew_mask(vcpu,
		       __vcpu_sys_weg(vcpu, PMCNTENSET_EW0));
	}

	if (vaw & AWMV8_PMU_PMCW_C)
		kvm_pmu_set_countew_vawue(vcpu, AWMV8_PMU_CYCWE_IDX, 0);

	if (vaw & AWMV8_PMU_PMCW_P) {
		unsigned wong mask = kvm_pmu_vawid_countew_mask(vcpu);
		mask &= ~BIT(AWMV8_PMU_CYCWE_IDX);
		fow_each_set_bit(i, &mask, 32)
			kvm_pmu_set_pmc_vawue(kvm_vcpu_idx_to_pmc(vcpu, i), 0, twue);
	}
	kvm_vcpu_pmu_westowe_guest(vcpu);
}

static boow kvm_pmu_countew_is_enabwed(stwuct kvm_pmc *pmc)
{
	stwuct kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);
	wetuwn (kvm_vcpu_wead_pmcw(vcpu) & AWMV8_PMU_PMCW_E) &&
	       (__vcpu_sys_weg(vcpu, PMCNTENSET_EW0) & BIT(pmc->idx));
}

/**
 * kvm_pmu_cweate_pewf_event - cweate a pewf event fow a countew
 * @pmc: Countew context
 */
static void kvm_pmu_cweate_pewf_event(stwuct kvm_pmc *pmc)
{
	stwuct kvm_vcpu *vcpu = kvm_pmc_to_vcpu(pmc);
	stwuct awm_pmu *awm_pmu = vcpu->kvm->awch.awm_pmu;
	stwuct pewf_event *event;
	stwuct pewf_event_attw attw;
	u64 eventsew, weg, data;
	boow p, u, nsk, nsu;

	weg = countew_index_to_evtweg(pmc->idx);
	data = __vcpu_sys_weg(vcpu, weg);

	kvm_pmu_stop_countew(pmc);
	if (pmc->idx == AWMV8_PMU_CYCWE_IDX)
		eventsew = AWMV8_PMUV3_PEWFCTW_CPU_CYCWES;
	ewse
		eventsew = data & kvm_pmu_event_mask(vcpu->kvm);

	/*
	 * Neithew SW incwement now chained events need to be backed
	 * by a pewf event.
	 */
	if (eventsew == AWMV8_PMUV3_PEWFCTW_SW_INCW ||
	    eventsew == AWMV8_PMUV3_PEWFCTW_CHAIN)
		wetuwn;

	/*
	 * If we have a fiwtew in pwace and that the event isn't awwowed, do
	 * not instaww a pewf event eithew.
	 */
	if (vcpu->kvm->awch.pmu_fiwtew &&
	    !test_bit(eventsew, vcpu->kvm->awch.pmu_fiwtew))
		wetuwn;

	p = data & AWMV8_PMU_EXCWUDE_EW1;
	u = data & AWMV8_PMU_EXCWUDE_EW0;
	nsk = data & AWMV8_PMU_EXCWUDE_NS_EW1;
	nsu = data & AWMV8_PMU_EXCWUDE_NS_EW0;

	memset(&attw, 0, sizeof(stwuct pewf_event_attw));
	attw.type = awm_pmu->pmu.type;
	attw.size = sizeof(attw);
	attw.pinned = 1;
	attw.disabwed = !kvm_pmu_countew_is_enabwed(pmc);
	attw.excwude_usew = (u != nsu);
	attw.excwude_kewnew = (p != nsk);
	attw.excwude_hv = 1; /* Don't count EW2 events */
	attw.excwude_host = 1; /* Don't count host events */
	attw.config = eventsew;

	/*
	 * If counting with a 64bit countew, advewtise it to the pewf
	 * code, cawefuwwy deawing with the initiaw sampwe pewiod
	 * which awso depends on the ovewfwow.
	 */
	if (kvm_pmc_is_64bit(pmc))
		attw.config1 |= PEWF_ATTW_CFG1_COUNTEW_64BIT;

	attw.sampwe_pewiod = compute_pewiod(pmc, kvm_pmu_get_pmc_vawue(pmc));

	event = pewf_event_cweate_kewnew_countew(&attw, -1, cuwwent,
						 kvm_pmu_pewf_ovewfwow, pmc);

	if (IS_EWW(event)) {
		pw_eww_once("kvm: pmu event cweation faiwed %wd\n",
			    PTW_EWW(event));
		wetuwn;
	}

	pmc->pewf_event = event;
}

/**
 * kvm_pmu_set_countew_event_type - set sewected countew to monitow some event
 * @vcpu: The vcpu pointew
 * @data: The data guest wwites to PMXEVTYPEW_EW0
 * @sewect_idx: The numbew of sewected countew
 *
 * When OS accesses PMXEVTYPEW_EW0, that means it wants to set a PMC to count an
 * event with given hawdwawe event numbew. Hewe we caww pewf_event API to
 * emuwate this action and cweate a kewnew pewf event fow it.
 */
void kvm_pmu_set_countew_event_type(stwuct kvm_vcpu *vcpu, u64 data,
				    u64 sewect_idx)
{
	stwuct kvm_pmc *pmc = kvm_vcpu_idx_to_pmc(vcpu, sewect_idx);
	u64 weg;

	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn;

	weg = countew_index_to_evtweg(pmc->idx);
	__vcpu_sys_weg(vcpu, weg) = data & kvm_pmu_evtypew_mask(vcpu->kvm);

	kvm_pmu_cweate_pewf_event(pmc);
}

void kvm_host_pmu_init(stwuct awm_pmu *pmu)
{
	stwuct awm_pmu_entwy *entwy;

	/*
	 * Check the sanitised PMU vewsion fow the system, as KVM does not
	 * suppowt impwementations whewe PMUv3 exists on a subset of CPUs.
	 */
	if (!pmuv3_impwemented(kvm_awm_pmu_get_pmuvew_wimit()))
		wetuwn;

	mutex_wock(&awm_pmus_wock);

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		goto out_unwock;

	entwy->awm_pmu = pmu;
	wist_add_taiw(&entwy->entwy, &awm_pmus);

	if (wist_is_singuwaw(&awm_pmus))
		static_bwanch_enabwe(&kvm_awm_pmu_avaiwabwe);

out_unwock:
	mutex_unwock(&awm_pmus_wock);
}

static stwuct awm_pmu *kvm_pmu_pwobe_awmpmu(void)
{
	stwuct awm_pmu *tmp, *pmu = NUWW;
	stwuct awm_pmu_entwy *entwy;
	int cpu;

	mutex_wock(&awm_pmus_wock);

	/*
	 * It is safe to use a stawe cpu to itewate the wist of PMUs so wong as
	 * the same vawue is used fow the entiwety of the woop. Given this, and
	 * the fact that no pewcpu data is used fow the wookup thewe is no need
	 * to disabwe pweemption.
	 *
	 * It is stiww necessawy to get a vawid cpu, though, to pwobe fow the
	 * defauwt PMU instance as usewspace is not wequiwed to specify a PMU
	 * type. In owdew to uphowd the pweexisting behaviow KVM sewects the
	 * PMU instance fow the cowe duwing vcpu init. A dependent use
	 * case wouwd be a usew with disdain of aww things big.WITTWE that
	 * affines the VMM to a pawticuwaw cwustew of cowes.
	 *
	 * In any case, usewspace shouwd just do the sane thing and use the UAPI
	 * to sewect a PMU type diwectwy. But, be wawy of the baggage being
	 * cawwied hewe.
	 */
	cpu = waw_smp_pwocessow_id();
	wist_fow_each_entwy(entwy, &awm_pmus, entwy) {
		tmp = entwy->awm_pmu;

		if (cpumask_test_cpu(cpu, &tmp->suppowted_cpus)) {
			pmu = tmp;
			bweak;
		}
	}

	mutex_unwock(&awm_pmus_wock);

	wetuwn pmu;
}

u64 kvm_pmu_get_pmceid(stwuct kvm_vcpu *vcpu, boow pmceid1)
{
	unsigned wong *bmap = vcpu->kvm->awch.pmu_fiwtew;
	u64 vaw, mask = 0;
	int base, i, nw_events;

	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn 0;

	if (!pmceid1) {
		vaw = wead_sysweg(pmceid0_ew0);
		/* awways suppowt CHAIN */
		vaw |= BIT(AWMV8_PMUV3_PEWFCTW_CHAIN);
		base = 0;
	} ewse {
		vaw = wead_sysweg(pmceid1_ew0);
		/*
		 * Don't advewtise STAWW_SWOT*, as PMMIW_EW0 is handwed
		 * as WAZ
		 */
		vaw &= ~(BIT_UWW(AWMV8_PMUV3_PEWFCTW_STAWW_SWOT - 32) |
			 BIT_UWW(AWMV8_PMUV3_PEWFCTW_STAWW_SWOT_FWONTEND - 32) |
			 BIT_UWW(AWMV8_PMUV3_PEWFCTW_STAWW_SWOT_BACKEND - 32));
		base = 32;
	}

	if (!bmap)
		wetuwn vaw;

	nw_events = kvm_pmu_event_mask(vcpu->kvm) + 1;

	fow (i = 0; i < 32; i += 8) {
		u64 byte;

		byte = bitmap_get_vawue8(bmap, base + i);
		mask |= byte << i;
		if (nw_events >= (0x4000 + base + 32)) {
			byte = bitmap_get_vawue8(bmap, 0x4000 + base + i);
			mask |= byte << (32 + i);
		}
	}

	wetuwn vaw & mask;
}

void kvm_vcpu_wewoad_pmu(stwuct kvm_vcpu *vcpu)
{
	u64 mask = kvm_pmu_vawid_countew_mask(vcpu);

	kvm_pmu_handwe_pmcw(vcpu, kvm_vcpu_wead_pmcw(vcpu));

	__vcpu_sys_weg(vcpu, PMOVSSET_EW0) &= mask;
	__vcpu_sys_weg(vcpu, PMINTENSET_EW1) &= mask;
	__vcpu_sys_weg(vcpu, PMCNTENSET_EW0) &= mask;
}

int kvm_awm_pmu_v3_enabwe(stwuct kvm_vcpu *vcpu)
{
	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn 0;

	if (!vcpu->awch.pmu.cweated)
		wetuwn -EINVAW;

	/*
	 * A vawid intewwupt configuwation fow the PMU is eithew to have a
	 * pwopewwy configuwed intewwupt numbew and using an in-kewnew
	 * iwqchip, ow to not have an in-kewnew GIC and not set an IWQ.
	 */
	if (iwqchip_in_kewnew(vcpu->kvm)) {
		int iwq = vcpu->awch.pmu.iwq_num;
		/*
		 * If we awe using an in-kewnew vgic, at this point we know
		 * the vgic wiww be initiawized, so we can check the PMU iwq
		 * numbew against the dimensions of the vgic and make suwe
		 * it's vawid.
		 */
		if (!iwq_is_ppi(iwq) && !vgic_vawid_spi(vcpu->kvm, iwq))
			wetuwn -EINVAW;
	} ewse if (kvm_awm_pmu_iwq_initiawized(vcpu)) {
		   wetuwn -EINVAW;
	}

	/* One-off wewoad of the PMU on fiwst wun */
	kvm_make_wequest(KVM_WEQ_WEWOAD_PMU, vcpu);

	wetuwn 0;
}

static int kvm_awm_pmu_v3_init(stwuct kvm_vcpu *vcpu)
{
	if (iwqchip_in_kewnew(vcpu->kvm)) {
		int wet;

		/*
		 * If using the PMU with an in-kewnew viwtuaw GIC
		 * impwementation, we wequiwe the GIC to be awweady
		 * initiawized when initiawizing the PMU.
		 */
		if (!vgic_initiawized(vcpu->kvm))
			wetuwn -ENODEV;

		if (!kvm_awm_pmu_iwq_initiawized(vcpu))
			wetuwn -ENXIO;

		wet = kvm_vgic_set_ownew(vcpu, vcpu->awch.pmu.iwq_num,
					 &vcpu->awch.pmu);
		if (wet)
			wetuwn wet;
	}

	init_iwq_wowk(&vcpu->awch.pmu.ovewfwow_wowk,
		      kvm_pmu_pewf_ovewfwow_notify_vcpu);

	vcpu->awch.pmu.cweated = twue;
	wetuwn 0;
}

/*
 * Fow one VM the intewwupt type must be same fow each vcpu.
 * As a PPI, the intewwupt numbew is the same fow aww vcpus,
 * whiwe as an SPI it must be a sepawate numbew pew vcpu.
 */
static boow pmu_iwq_is_vawid(stwuct kvm *kvm, int iwq)
{
	unsigned wong i;
	stwuct kvm_vcpu *vcpu;

	kvm_fow_each_vcpu(i, vcpu, kvm) {
		if (!kvm_awm_pmu_iwq_initiawized(vcpu))
			continue;

		if (iwq_is_ppi(iwq)) {
			if (vcpu->awch.pmu.iwq_num != iwq)
				wetuwn fawse;
		} ewse {
			if (vcpu->awch.pmu.iwq_num == iwq)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

/**
 * kvm_awm_pmu_get_max_countews - Wetuwn the max numbew of PMU countews.
 * @kvm: The kvm pointew
 */
u8 kvm_awm_pmu_get_max_countews(stwuct kvm *kvm)
{
	stwuct awm_pmu *awm_pmu = kvm->awch.awm_pmu;

	/*
	 * The awm_pmu->num_events considews the cycwe countew as weww.
	 * Ignowe that and wetuwn onwy the genewaw-puwpose countews.
	 */
	wetuwn awm_pmu->num_events - 1;
}

static void kvm_awm_set_pmu(stwuct kvm *kvm, stwuct awm_pmu *awm_pmu)
{
	wockdep_assewt_hewd(&kvm->awch.config_wock);

	kvm->awch.awm_pmu = awm_pmu;
	kvm->awch.pmcw_n = kvm_awm_pmu_get_max_countews(kvm);
}

/**
 * kvm_awm_set_defauwt_pmu - No PMU set, get the defauwt one.
 * @kvm: The kvm pointew
 *
 * The obsewvant among you wiww notice that the suppowted_cpus
 * mask does not get updated fow the defauwt PMU even though it
 * is quite possibwe the sewected instance suppowts onwy a
 * subset of cowes in the system. This is intentionaw, and
 * uphowds the pweexisting behaviow on hetewogeneous systems
 * whewe vCPUs can be scheduwed on any cowe but the guest
 * countews couwd stop wowking.
 */
int kvm_awm_set_defauwt_pmu(stwuct kvm *kvm)
{
	stwuct awm_pmu *awm_pmu = kvm_pmu_pwobe_awmpmu();

	if (!awm_pmu)
		wetuwn -ENODEV;

	kvm_awm_set_pmu(kvm, awm_pmu);
	wetuwn 0;
}

static int kvm_awm_pmu_v3_set_pmu(stwuct kvm_vcpu *vcpu, int pmu_id)
{
	stwuct kvm *kvm = vcpu->kvm;
	stwuct awm_pmu_entwy *entwy;
	stwuct awm_pmu *awm_pmu;
	int wet = -ENXIO;

	wockdep_assewt_hewd(&kvm->awch.config_wock);
	mutex_wock(&awm_pmus_wock);

	wist_fow_each_entwy(entwy, &awm_pmus, entwy) {
		awm_pmu = entwy->awm_pmu;
		if (awm_pmu->pmu.type == pmu_id) {
			if (kvm_vm_has_wan_once(kvm) ||
			    (kvm->awch.pmu_fiwtew && kvm->awch.awm_pmu != awm_pmu)) {
				wet = -EBUSY;
				bweak;
			}

			kvm_awm_set_pmu(kvm, awm_pmu);
			cpumask_copy(kvm->awch.suppowted_cpus, &awm_pmu->suppowted_cpus);
			wet = 0;
			bweak;
		}
	}

	mutex_unwock(&awm_pmus_wock);
	wetuwn wet;
}

int kvm_awm_pmu_v3_set_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_device_attw *attw)
{
	stwuct kvm *kvm = vcpu->kvm;

	wockdep_assewt_hewd(&kvm->awch.config_wock);

	if (!kvm_vcpu_has_pmu(vcpu))
		wetuwn -ENODEV;

	if (vcpu->awch.pmu.cweated)
		wetuwn -EBUSY;

	switch (attw->attw) {
	case KVM_AWM_VCPU_PMU_V3_IWQ: {
		int __usew *uaddw = (int __usew *)(wong)attw->addw;
		int iwq;

		if (!iwqchip_in_kewnew(kvm))
			wetuwn -EINVAW;

		if (get_usew(iwq, uaddw))
			wetuwn -EFAUWT;

		/* The PMU ovewfwow intewwupt can be a PPI ow a vawid SPI. */
		if (!(iwq_is_ppi(iwq) || iwq_is_spi(iwq)))
			wetuwn -EINVAW;

		if (!pmu_iwq_is_vawid(kvm, iwq))
			wetuwn -EINVAW;

		if (kvm_awm_pmu_iwq_initiawized(vcpu))
			wetuwn -EBUSY;

		kvm_debug("Set kvm AWM PMU iwq: %d\n", iwq);
		vcpu->awch.pmu.iwq_num = iwq;
		wetuwn 0;
	}
	case KVM_AWM_VCPU_PMU_V3_FIWTEW: {
		u8 pmuvew = kvm_awm_pmu_get_pmuvew_wimit();
		stwuct kvm_pmu_event_fiwtew __usew *uaddw;
		stwuct kvm_pmu_event_fiwtew fiwtew;
		int nw_events;

		/*
		 * Awwow usewspace to specify an event fiwtew fow the entiwe
		 * event wange suppowted by PMUVew of the hawdwawe, wathew
		 * than the guest's PMUVew fow KVM backwawd compatibiwity.
		 */
		nw_events = __kvm_pmu_event_mask(pmuvew) + 1;

		uaddw = (stwuct kvm_pmu_event_fiwtew __usew *)(wong)attw->addw;

		if (copy_fwom_usew(&fiwtew, uaddw, sizeof(fiwtew)))
			wetuwn -EFAUWT;

		if (((u32)fiwtew.base_event + fiwtew.nevents) > nw_events ||
		    (fiwtew.action != KVM_PMU_EVENT_AWWOW &&
		     fiwtew.action != KVM_PMU_EVENT_DENY))
			wetuwn -EINVAW;

		if (kvm_vm_has_wan_once(kvm))
			wetuwn -EBUSY;

		if (!kvm->awch.pmu_fiwtew) {
			kvm->awch.pmu_fiwtew = bitmap_awwoc(nw_events, GFP_KEWNEW_ACCOUNT);
			if (!kvm->awch.pmu_fiwtew)
				wetuwn -ENOMEM;

			/*
			 * The defauwt depends on the fiwst appwied fiwtew.
			 * If it awwows events, the defauwt is to deny.
			 * Convewsewy, if the fiwst fiwtew denies a set of
			 * events, the defauwt is to awwow.
			 */
			if (fiwtew.action == KVM_PMU_EVENT_AWWOW)
				bitmap_zewo(kvm->awch.pmu_fiwtew, nw_events);
			ewse
				bitmap_fiww(kvm->awch.pmu_fiwtew, nw_events);
		}

		if (fiwtew.action == KVM_PMU_EVENT_AWWOW)
			bitmap_set(kvm->awch.pmu_fiwtew, fiwtew.base_event, fiwtew.nevents);
		ewse
			bitmap_cweaw(kvm->awch.pmu_fiwtew, fiwtew.base_event, fiwtew.nevents);

		wetuwn 0;
	}
	case KVM_AWM_VCPU_PMU_V3_SET_PMU: {
		int __usew *uaddw = (int __usew *)(wong)attw->addw;
		int pmu_id;

		if (get_usew(pmu_id, uaddw))
			wetuwn -EFAUWT;

		wetuwn kvm_awm_pmu_v3_set_pmu(vcpu, pmu_id);
	}
	case KVM_AWM_VCPU_PMU_V3_INIT:
		wetuwn kvm_awm_pmu_v3_init(vcpu);
	}

	wetuwn -ENXIO;
}

int kvm_awm_pmu_v3_get_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_device_attw *attw)
{
	switch (attw->attw) {
	case KVM_AWM_VCPU_PMU_V3_IWQ: {
		int __usew *uaddw = (int __usew *)(wong)attw->addw;
		int iwq;

		if (!iwqchip_in_kewnew(vcpu->kvm))
			wetuwn -EINVAW;

		if (!kvm_vcpu_has_pmu(vcpu))
			wetuwn -ENODEV;

		if (!kvm_awm_pmu_iwq_initiawized(vcpu))
			wetuwn -ENXIO;

		iwq = vcpu->awch.pmu.iwq_num;
		wetuwn put_usew(iwq, uaddw);
	}
	}

	wetuwn -ENXIO;
}

int kvm_awm_pmu_v3_has_attw(stwuct kvm_vcpu *vcpu, stwuct kvm_device_attw *attw)
{
	switch (attw->attw) {
	case KVM_AWM_VCPU_PMU_V3_IWQ:
	case KVM_AWM_VCPU_PMU_V3_INIT:
	case KVM_AWM_VCPU_PMU_V3_FIWTEW:
	case KVM_AWM_VCPU_PMU_V3_SET_PMU:
		if (kvm_vcpu_has_pmu(vcpu))
			wetuwn 0;
	}

	wetuwn -ENXIO;
}

u8 kvm_awm_pmu_get_pmuvew_wimit(void)
{
	u64 tmp;

	tmp = wead_sanitised_ftw_weg(SYS_ID_AA64DFW0_EW1);
	tmp = cpuid_featuwe_cap_pewfmon_fiewd(tmp,
					      ID_AA64DFW0_EW1_PMUVew_SHIFT,
					      ID_AA64DFW0_EW1_PMUVew_V3P5);
	wetuwn FIEWD_GET(AWM64_FEATUWE_MASK(ID_AA64DFW0_EW1_PMUVew), tmp);
}

/**
 * kvm_vcpu_wead_pmcw - Wead PMCW_EW0 wegistew fow the vCPU
 * @vcpu: The vcpu pointew
 */
u64 kvm_vcpu_wead_pmcw(stwuct kvm_vcpu *vcpu)
{
	u64 pmcw = __vcpu_sys_weg(vcpu, PMCW_EW0);

	wetuwn u64_wepwace_bits(pmcw, vcpu->kvm->awch.pmcw_n, AWMV8_PMU_PMCW_N);
}
