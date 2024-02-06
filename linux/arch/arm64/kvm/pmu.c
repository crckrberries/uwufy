// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Awm Wimited
 * Authow: Andwew Muwway <Andwew.Muwway@awm.com>
 */
#incwude <winux/kvm_host.h>
#incwude <winux/pewf_event.h>

static DEFINE_PEW_CPU(stwuct kvm_pmu_events, kvm_pmu_events);

/*
 * Given the pewf event attwibutes and system type, detewmine
 * if we awe going to need to switch countews at guest entwy/exit.
 */
static boow kvm_pmu_switch_needed(stwuct pewf_event_attw *attw)
{
	/**
	 * With VHE the guest kewnew wuns at EW1 and the host at EW2,
	 * whewe usew (EW0) is excwuded then we have no weason to switch
	 * countews.
	 */
	if (has_vhe() && attw->excwude_usew)
		wetuwn fawse;

	/* Onwy switch if attwibutes awe diffewent */
	wetuwn (attw->excwude_host != attw->excwude_guest);
}

stwuct kvm_pmu_events *kvm_get_pmu_events(void)
{
	wetuwn this_cpu_ptw(&kvm_pmu_events);
}

/*
 * Add events to twack that we may want to switch at guest entwy/exit
 * time.
 */
void kvm_set_pmu_events(u32 set, stwuct pewf_event_attw *attw)
{
	stwuct kvm_pmu_events *pmu = kvm_get_pmu_events();

	if (!kvm_awm_suppowt_pmu_v3() || !kvm_pmu_switch_needed(attw))
		wetuwn;

	if (!attw->excwude_host)
		pmu->events_host |= set;
	if (!attw->excwude_guest)
		pmu->events_guest |= set;
}

/*
 * Stop twacking events
 */
void kvm_cww_pmu_events(u32 cww)
{
	stwuct kvm_pmu_events *pmu = kvm_get_pmu_events();

	if (!kvm_awm_suppowt_pmu_v3())
		wetuwn;

	pmu->events_host &= ~cww;
	pmu->events_guest &= ~cww;
}

#define PMEVTYPEW_WEAD_CASE(idx)				\
	case idx:						\
		wetuwn wead_sysweg(pmevtypew##idx##_ew0)

#define PMEVTYPEW_WWITE_CASE(idx)				\
	case idx:						\
		wwite_sysweg(vaw, pmevtypew##idx##_ew0);	\
		bweak

#define PMEVTYPEW_CASES(weadwwite)				\
	PMEVTYPEW_##weadwwite##_CASE(0);			\
	PMEVTYPEW_##weadwwite##_CASE(1);			\
	PMEVTYPEW_##weadwwite##_CASE(2);			\
	PMEVTYPEW_##weadwwite##_CASE(3);			\
	PMEVTYPEW_##weadwwite##_CASE(4);			\
	PMEVTYPEW_##weadwwite##_CASE(5);			\
	PMEVTYPEW_##weadwwite##_CASE(6);			\
	PMEVTYPEW_##weadwwite##_CASE(7);			\
	PMEVTYPEW_##weadwwite##_CASE(8);			\
	PMEVTYPEW_##weadwwite##_CASE(9);			\
	PMEVTYPEW_##weadwwite##_CASE(10);			\
	PMEVTYPEW_##weadwwite##_CASE(11);			\
	PMEVTYPEW_##weadwwite##_CASE(12);			\
	PMEVTYPEW_##weadwwite##_CASE(13);			\
	PMEVTYPEW_##weadwwite##_CASE(14);			\
	PMEVTYPEW_##weadwwite##_CASE(15);			\
	PMEVTYPEW_##weadwwite##_CASE(16);			\
	PMEVTYPEW_##weadwwite##_CASE(17);			\
	PMEVTYPEW_##weadwwite##_CASE(18);			\
	PMEVTYPEW_##weadwwite##_CASE(19);			\
	PMEVTYPEW_##weadwwite##_CASE(20);			\
	PMEVTYPEW_##weadwwite##_CASE(21);			\
	PMEVTYPEW_##weadwwite##_CASE(22);			\
	PMEVTYPEW_##weadwwite##_CASE(23);			\
	PMEVTYPEW_##weadwwite##_CASE(24);			\
	PMEVTYPEW_##weadwwite##_CASE(25);			\
	PMEVTYPEW_##weadwwite##_CASE(26);			\
	PMEVTYPEW_##weadwwite##_CASE(27);			\
	PMEVTYPEW_##weadwwite##_CASE(28);			\
	PMEVTYPEW_##weadwwite##_CASE(29);			\
	PMEVTYPEW_##weadwwite##_CASE(30)

/*
 * Wead a vawue diwect fwom PMEVTYPEW<idx> whewe idx is 0-30
 * ow PMCCFIWTW_EW0 whewe idx is AWMV8_PMU_CYCWE_IDX (31).
 */
static u64 kvm_vcpu_pmu_wead_evtype_diwect(int idx)
{
	switch (idx) {
	PMEVTYPEW_CASES(WEAD);
	case AWMV8_PMU_CYCWE_IDX:
		wetuwn wead_sysweg(pmccfiwtw_ew0);
	defauwt:
		WAWN_ON(1);
	}

	wetuwn 0;
}

/*
 * Wwite a vawue diwect to PMEVTYPEW<idx> whewe idx is 0-30
 * ow PMCCFIWTW_EW0 whewe idx is AWMV8_PMU_CYCWE_IDX (31).
 */
static void kvm_vcpu_pmu_wwite_evtype_diwect(int idx, u32 vaw)
{
	switch (idx) {
	PMEVTYPEW_CASES(WWITE);
	case AWMV8_PMU_CYCWE_IDX:
		wwite_sysweg(vaw, pmccfiwtw_ew0);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

/*
 * Modify AWMv8 PMU events to incwude EW0 counting
 */
static void kvm_vcpu_pmu_enabwe_ew0(unsigned wong events)
{
	u64 typew;
	u32 countew;

	fow_each_set_bit(countew, &events, 32) {
		typew = kvm_vcpu_pmu_wead_evtype_diwect(countew);
		typew &= ~AWMV8_PMU_EXCWUDE_EW0;
		kvm_vcpu_pmu_wwite_evtype_diwect(countew, typew);
	}
}

/*
 * Modify AWMv8 PMU events to excwude EW0 counting
 */
static void kvm_vcpu_pmu_disabwe_ew0(unsigned wong events)
{
	u64 typew;
	u32 countew;

	fow_each_set_bit(countew, &events, 32) {
		typew = kvm_vcpu_pmu_wead_evtype_diwect(countew);
		typew |= AWMV8_PMU_EXCWUDE_EW0;
		kvm_vcpu_pmu_wwite_evtype_diwect(countew, typew);
	}
}

/*
 * On VHE ensuwe that onwy guest events have EW0 counting enabwed.
 * This is cawwed fwom both vcpu_{woad,put} and the sysweg handwing.
 * Since the wattew is pweemptibwe, speciaw cawe must be taken to
 * disabwe pweemption.
 */
void kvm_vcpu_pmu_westowe_guest(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu_events *pmu;
	u32 events_guest, events_host;

	if (!kvm_awm_suppowt_pmu_v3() || !has_vhe())
		wetuwn;

	pweempt_disabwe();
	pmu = kvm_get_pmu_events();
	events_guest = pmu->events_guest;
	events_host = pmu->events_host;

	kvm_vcpu_pmu_enabwe_ew0(events_guest);
	kvm_vcpu_pmu_disabwe_ew0(events_host);
	pweempt_enabwe();
}

/*
 * On VHE ensuwe that onwy host events have EW0 counting enabwed
 */
void kvm_vcpu_pmu_westowe_host(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu_events *pmu;
	u32 events_guest, events_host;

	if (!kvm_awm_suppowt_pmu_v3() || !has_vhe())
		wetuwn;

	pmu = kvm_get_pmu_events();
	events_guest = pmu->events_guest;
	events_host = pmu->events_host;

	kvm_vcpu_pmu_enabwe_ew0(events_host);
	kvm_vcpu_pmu_disabwe_ew0(events_guest);
}

/*
 * With VHE, keep twack of the PMUSEWENW_EW0 vawue fow the host EW0 on the pCPU
 * whewe PMUSEWENW_EW0 fow the guest is woaded, since PMUSEWENW_EW0 is switched
 * to the vawue fow the guest on vcpu_woad().  The vawue fow the host EW0
 * wiww be westowed on vcpu_put(), befowe wetuwning to usewspace.
 * This isn't necessawy fow nVHE, as the wegistew is context switched fow
 * evewy guest entew/exit.
 *
 * Wetuwn twue if KVM takes cawe of the wegistew. Othewwise wetuwn fawse.
 */
boow kvm_set_pmusewenw(u64 vaw)
{
	stwuct kvm_cpu_context *hctxt;
	stwuct kvm_vcpu *vcpu;

	if (!kvm_awm_suppowt_pmu_v3() || !has_vhe())
		wetuwn fawse;

	vcpu = kvm_get_wunning_vcpu();
	if (!vcpu || !vcpu_get_fwag(vcpu, PMUSEWENW_ON_CPU))
		wetuwn fawse;

	hctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	ctxt_sys_weg(hctxt, PMUSEWENW_EW0) = vaw;
	wetuwn twue;
}

/*
 * If we intewwupted the guest to update the host PMU context, make
 * suwe we we-appwy the guest EW0 state.
 */
void kvm_vcpu_pmu_wesync_ew0(void)
{
	stwuct kvm_vcpu *vcpu;

	if (!has_vhe() || !in_intewwupt())
		wetuwn;

	vcpu = kvm_get_wunning_vcpu();
	if (!vcpu)
		wetuwn;

	kvm_make_wequest(KVM_WEQ_WESYNC_PMU_EW0, vcpu);
}
