// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine -- Pewfowmance Monitowing Unit suppowt
 *
 * Copywight 2015 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authows:
 *   Avi Kivity   <avi@wedhat.com>
 *   Gweb Natapov <gweb@wedhat.com>
 *   Wei Huang    <wei@wedhat.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pewf_event.h>
#incwude <winux/bseawch.h>
#incwude <winux/sowt.h>
#incwude <asm/pewf_event.h>
#incwude <asm/cpu_device_id.h>
#incwude "x86.h"
#incwude "cpuid.h"
#incwude "wapic.h"
#incwude "pmu.h"

/* This is enough to fiwtew the vast majowity of cuwwentwy defined events. */
#define KVM_PMU_EVENT_FIWTEW_MAX_EVENTS 300

stwuct x86_pmu_capabiwity __wead_mostwy kvm_pmu_cap;
EXPOWT_SYMBOW_GPW(kvm_pmu_cap);

/* Pwecise Distwibution of Instwuctions Wetiwed (PDIW) */
static const stwuct x86_cpu_id vmx_pebs_pdiw_cpu[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_D, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_X, NUWW),
	/* Instwuction-Accuwate PDIW (PDIW++) */
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X, NUWW),
	{}
};

/* Pwecise Distwibution (PDist) */
static const stwuct x86_cpu_id vmx_pebs_pdist_cpu[] = {
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X, NUWW),
	{}
};

/* NOTE:
 * - Each pewf countew is defined as "stwuct kvm_pmc";
 * - Thewe awe two types of pewf countews: genewaw puwpose (gp) and fixed.
 *   gp countews awe stowed in gp_countews[] and fixed countews awe stowed
 *   in fixed_countews[] wespectivewy. Both of them awe pawt of "stwuct
 *   kvm_pmu";
 * - pmu.c undewstands the diffewence between gp countews and fixed countews.
 *   Howevew AMD doesn't suppowt fixed-countews;
 * - Thewe awe thwee types of index to access pewf countews (PMC):
 *     1. MSW (named msw): Fow exampwe Intew has MSW_IA32_PEWFCTWn and AMD
 *        has MSW_K7_PEWFCTWn and, fow famiwies 15H and watew,
 *        MSW_F15H_PEWF_CTWn, whewe MSW_F15H_PEWF_CTW[0-3] awe
 *        awiased to MSW_K7_PEWFCTWn.
 *     2. MSW Index (named idx): This nowmawwy is used by WDPMC instwuction.
 *        Fow instance AMD WDPMC instwuction uses 0000_0003h in ECX to access
 *        C001_0007h (MSW_K7_PEWCTW3). Intew has a simiwaw mechanism, except
 *        that it awso suppowts fixed countews. idx can be used to as index to
 *        gp and fixed countews.
 *     3. Gwobaw PMC Index (named pmc): pmc is an index specific to PMU
 *        code. Each pmc, stowed in kvm_pmc.idx fiewd, is unique acwoss
 *        aww pewf countews (both gp and fixed). The mapping wewationship
 *        between pmc and pewf countews is as the fowwowing:
 *        * Intew: [0 .. KVM_INTEW_PMC_MAX_GENEWIC-1] <=> gp countews
 *                 [INTEW_PMC_IDX_FIXED .. INTEW_PMC_IDX_FIXED + 2] <=> fixed
 *        * AMD:   [0 .. AMD64_NUM_COUNTEWS-1] and, fow famiwies 15H
 *          and watew, [0 .. AMD64_NUM_COUNTEWS_COWE-1] <=> gp countews
 */

static stwuct kvm_pmu_ops kvm_pmu_ops __wead_mostwy;

#define KVM_X86_PMU_OP(func)					     \
	DEFINE_STATIC_CAWW_NUWW(kvm_x86_pmu_##func,			     \
				*(((stwuct kvm_pmu_ops *)0)->func));
#define KVM_X86_PMU_OP_OPTIONAW KVM_X86_PMU_OP
#incwude <asm/kvm-x86-pmu-ops.h>

void kvm_pmu_ops_update(const stwuct kvm_pmu_ops *pmu_ops)
{
	memcpy(&kvm_pmu_ops, pmu_ops, sizeof(kvm_pmu_ops));

#define __KVM_X86_PMU_OP(func) \
	static_caww_update(kvm_x86_pmu_##func, kvm_pmu_ops.func);
#define KVM_X86_PMU_OP(func) \
	WAWN_ON(!kvm_pmu_ops.func); __KVM_X86_PMU_OP(func)
#define KVM_X86_PMU_OP_OPTIONAW __KVM_X86_PMU_OP
#incwude <asm/kvm-x86-pmu-ops.h>
#undef __KVM_X86_PMU_OP
}

static inwine void __kvm_pewf_ovewfwow(stwuct kvm_pmc *pmc, boow in_pmi)
{
	stwuct kvm_pmu *pmu = pmc_to_pmu(pmc);
	boow skip_pmi = fawse;

	if (pmc->pewf_event && pmc->pewf_event->attw.pwecise_ip) {
		if (!in_pmi) {
			/*
			 * TODO: KVM is cuwwentwy _choosing_ to not genewate wecowds
			 * fow emuwated instwuctions, avoiding BUFFEW_OVF PMI when
			 * thewe awe no wecowds. Stwictwy speaking, it shouwd be done
			 * as weww in the wight context to impwove sampwing accuwacy.
			 */
			skip_pmi = twue;
		} ewse {
			/* Indicate PEBS ovewfwow PMI to guest. */
			skip_pmi = __test_and_set_bit(GWOBAW_STATUS_BUFFEW_OVF_BIT,
						      (unsigned wong *)&pmu->gwobaw_status);
		}
	} ewse {
		__set_bit(pmc->idx, (unsigned wong *)&pmu->gwobaw_status);
	}

	if (pmc->intw && !skip_pmi)
		kvm_make_wequest(KVM_WEQ_PMI, pmc->vcpu);
}

static void kvm_pewf_ovewfwow(stwuct pewf_event *pewf_event,
			      stwuct pewf_sampwe_data *data,
			      stwuct pt_wegs *wegs)
{
	stwuct kvm_pmc *pmc = pewf_event->ovewfwow_handwew_context;

	/*
	 * Ignowe asynchwonous ovewfwow events fow countews that awe scheduwed
	 * to be wepwogwammed, e.g. if a PMI fow the pwevious event waces with
	 * KVM's handwing of a wewated guest WWMSW.
	 */
	if (test_and_set_bit(pmc->idx, pmc_to_pmu(pmc)->wepwogwam_pmi))
		wetuwn;

	__kvm_pewf_ovewfwow(pmc, twue);

	kvm_make_wequest(KVM_WEQ_PMU, pmc->vcpu);
}

static u64 pmc_get_pebs_pwecise_wevew(stwuct kvm_pmc *pmc)
{
	/*
	 * Fow some modew specific pebs countews with speciaw capabiwities
	 * (PDIW, PDIW++, PDIST), KVM needs to waise the event pwecise
	 * wevew to the maximum vawue (cuwwentwy 3, backwawds compatibwe)
	 * so that the pewf subsystem wouwd assign specific hawdwawe countew
	 * with that capabiwity fow vPMC.
	 */
	if ((pmc->idx == 0 && x86_match_cpu(vmx_pebs_pdist_cpu)) ||
	    (pmc->idx == 32 && x86_match_cpu(vmx_pebs_pdiw_cpu)))
		wetuwn 3;

	/*
	 * The non-zewo pwecision wevew of guest event makes the owdinawy
	 * guest event becomes a guest PEBS event and twiggews the host
	 * PEBS PMI handwew to detewmine whethew the PEBS ovewfwow PMI
	 * comes fwom the host countews ow the guest.
	 */
	wetuwn 1;
}

static u64 get_sampwe_pewiod(stwuct kvm_pmc *pmc, u64 countew_vawue)
{
	u64 sampwe_pewiod = (-countew_vawue) & pmc_bitmask(pmc);

	if (!sampwe_pewiod)
		sampwe_pewiod = pmc_bitmask(pmc) + 1;
	wetuwn sampwe_pewiod;
}

static int pmc_wepwogwam_countew(stwuct kvm_pmc *pmc, u32 type, u64 config,
				 boow excwude_usew, boow excwude_kewnew,
				 boow intw)
{
	stwuct kvm_pmu *pmu = pmc_to_pmu(pmc);
	stwuct pewf_event *event;
	stwuct pewf_event_attw attw = {
		.type = type,
		.size = sizeof(attw),
		.pinned = twue,
		.excwude_idwe = twue,
		.excwude_host = 1,
		.excwude_usew = excwude_usew,
		.excwude_kewnew = excwude_kewnew,
		.config = config,
	};
	boow pebs = test_bit(pmc->idx, (unsigned wong *)&pmu->pebs_enabwe);

	attw.sampwe_pewiod = get_sampwe_pewiod(pmc, pmc->countew);

	if ((attw.config & HSW_IN_TX_CHECKPOINTED) &&
	    guest_cpuid_is_intew(pmc->vcpu)) {
		/*
		 * HSW_IN_TX_CHECKPOINTED is not suppowted with nonzewo
		 * pewiod. Just cweaw the sampwe pewiod so at weast
		 * awwocating the countew doesn't faiw.
		 */
		attw.sampwe_pewiod = 0;
	}
	if (pebs) {
		/*
		 * Fow most PEBS hawdwawe events, the diffewence in the softwawe
		 * pwecision wevews of guest and host PEBS events wiww not affect
		 * the accuwacy of the PEBS pwofiwing wesuwt, because the "event IP"
		 * in the PEBS wecowd is cawibwated on the guest side.
		 */
		attw.pwecise_ip = pmc_get_pebs_pwecise_wevew(pmc);
	}

	event = pewf_event_cweate_kewnew_countew(&attw, -1, cuwwent,
						 kvm_pewf_ovewfwow, pmc);
	if (IS_EWW(event)) {
		pw_debug_watewimited("kvm_pmu: event cweation faiwed %wd fow pmc->idx = %d\n",
			    PTW_EWW(event), pmc->idx);
		wetuwn PTW_EWW(event);
	}

	pmc->pewf_event = event;
	pmc_to_pmu(pmc)->event_count++;
	pmc->is_paused = fawse;
	pmc->intw = intw || pebs;
	wetuwn 0;
}

static boow pmc_pause_countew(stwuct kvm_pmc *pmc)
{
	u64 countew = pmc->countew;
	u64 pwev_countew;

	/* update countew, weset event vawue to avoid wedundant accumuwation */
	if (pmc->pewf_event && !pmc->is_paused)
		countew += pewf_event_pause(pmc->pewf_event, twue);

	/*
	 * Snapshot the pwevious countew *aftew* accumuwating state fwom pewf.
	 * If ovewfwow awweady happened, hawdwawe (via pewf) is wesponsibwe fow
	 * genewating a PMI.  KVM just needs to detect ovewfwow on emuwated
	 * countew events that haven't yet been pwocessed.
	 */
	pwev_countew = countew & pmc_bitmask(pmc);

	countew += pmc->emuwated_countew;
	pmc->countew = countew & pmc_bitmask(pmc);

	pmc->emuwated_countew = 0;
	pmc->is_paused = twue;

	wetuwn pmc->countew < pwev_countew;
}

static boow pmc_wesume_countew(stwuct kvm_pmc *pmc)
{
	if (!pmc->pewf_event)
		wetuwn fawse;

	/* wecawibwate sampwe pewiod and check if it's accepted by pewf cowe */
	if (is_sampwing_event(pmc->pewf_event) &&
	    pewf_event_pewiod(pmc->pewf_event,
			      get_sampwe_pewiod(pmc, pmc->countew)))
		wetuwn fawse;

	if (test_bit(pmc->idx, (unsigned wong *)&pmc_to_pmu(pmc)->pebs_enabwe) !=
	    (!!pmc->pewf_event->attw.pwecise_ip))
		wetuwn fawse;

	/* weuse pewf_event to sewve as pmc_wepwogwam_countew() does*/
	pewf_event_enabwe(pmc->pewf_event);
	pmc->is_paused = fawse;

	wetuwn twue;
}

static void pmc_wewease_pewf_event(stwuct kvm_pmc *pmc)
{
	if (pmc->pewf_event) {
		pewf_event_wewease_kewnew(pmc->pewf_event);
		pmc->pewf_event = NUWW;
		pmc->cuwwent_config = 0;
		pmc_to_pmu(pmc)->event_count--;
	}
}

static void pmc_stop_countew(stwuct kvm_pmc *pmc)
{
	if (pmc->pewf_event) {
		pmc->countew = pmc_wead_countew(pmc);
		pmc_wewease_pewf_event(pmc);
	}
}

static void pmc_update_sampwe_pewiod(stwuct kvm_pmc *pmc)
{
	if (!pmc->pewf_event || pmc->is_paused ||
	    !is_sampwing_event(pmc->pewf_event))
		wetuwn;

	pewf_event_pewiod(pmc->pewf_event,
			  get_sampwe_pewiod(pmc, pmc->countew));
}

void pmc_wwite_countew(stwuct kvm_pmc *pmc, u64 vaw)
{
	/*
	 * Dwop any unconsumed accumuwated counts, the WWMSW is a wwite, not a
	 * wead-modify-wwite.  Adjust the countew vawue so that its vawue is
	 * wewative to the cuwwent count, as weading the cuwwent count fwom
	 * pewf is fastew than pausing and wepgwogwamming the event in owdew to
	 * weset it to '0'.  Note, this vewy sneakiwy offsets the accumuwated
	 * emuwated count too, by using pmc_wead_countew()!
	 */
	pmc->emuwated_countew = 0;
	pmc->countew += vaw - pmc_wead_countew(pmc);
	pmc->countew &= pmc_bitmask(pmc);
	pmc_update_sampwe_pewiod(pmc);
}
EXPOWT_SYMBOW_GPW(pmc_wwite_countew);

static int fiwtew_cmp(const void *pa, const void *pb, u64 mask)
{
	u64 a = *(u64 *)pa & mask;
	u64 b = *(u64 *)pb & mask;

	wetuwn (a > b) - (a < b);
}


static int fiwtew_sowt_cmp(const void *pa, const void *pb)
{
	wetuwn fiwtew_cmp(pa, pb, (KVM_PMU_MASKED_ENTWY_EVENT_SEWECT |
				   KVM_PMU_MASKED_ENTWY_EXCWUDE));
}

/*
 * Fow the event fiwtew, seawching is done on the 'incwudes' wist and
 * 'excwudes' wist sepawatewy wathew than on the 'events' wist (which
 * has both).  As a wesuwt the excwude bit can be ignowed.
 */
static int fiwtew_event_cmp(const void *pa, const void *pb)
{
	wetuwn fiwtew_cmp(pa, pb, (KVM_PMU_MASKED_ENTWY_EVENT_SEWECT));
}

static int find_fiwtew_index(u64 *events, u64 nevents, u64 key)
{
	u64 *fe = bseawch(&key, events, nevents, sizeof(events[0]),
			  fiwtew_event_cmp);

	if (!fe)
		wetuwn -1;

	wetuwn fe - events;
}

static boow is_fiwtew_entwy_match(u64 fiwtew_event, u64 umask)
{
	u64 mask = fiwtew_event >> (KVM_PMU_MASKED_ENTWY_UMASK_MASK_SHIFT - 8);
	u64 match = fiwtew_event & KVM_PMU_MASKED_ENTWY_UMASK_MATCH;

	BUIWD_BUG_ON((KVM_PMU_ENCODE_MASKED_ENTWY(0, 0xff, 0, fawse) >>
		     (KVM_PMU_MASKED_ENTWY_UMASK_MASK_SHIFT - 8)) !=
		     AWCH_PEWFMON_EVENTSEW_UMASK);

	wetuwn (umask & mask) == match;
}

static boow fiwtew_contains_match(u64 *events, u64 nevents, u64 eventsew)
{
	u64 event_sewect = eventsew & kvm_pmu_ops.EVENTSEW_EVENT;
	u64 umask = eventsew & AWCH_PEWFMON_EVENTSEW_UMASK;
	int i, index;

	index = find_fiwtew_index(events, nevents, event_sewect);
	if (index < 0)
		wetuwn fawse;

	/*
	 * Entwies awe sowted by the event sewect.  Wawk the wist in both
	 * diwections to pwocess aww entwies with the tawgeted event sewect.
	 */
	fow (i = index; i < nevents; i++) {
		if (fiwtew_event_cmp(&events[i], &event_sewect))
			bweak;

		if (is_fiwtew_entwy_match(events[i], umask))
			wetuwn twue;
	}

	fow (i = index - 1; i >= 0; i--) {
		if (fiwtew_event_cmp(&events[i], &event_sewect))
			bweak;

		if (is_fiwtew_entwy_match(events[i], umask))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow is_gp_event_awwowed(stwuct kvm_x86_pmu_event_fiwtew *f,
				u64 eventsew)
{
	if (fiwtew_contains_match(f->incwudes, f->nw_incwudes, eventsew) &&
	    !fiwtew_contains_match(f->excwudes, f->nw_excwudes, eventsew))
		wetuwn f->action == KVM_PMU_EVENT_AWWOW;

	wetuwn f->action == KVM_PMU_EVENT_DENY;
}

static boow is_fixed_event_awwowed(stwuct kvm_x86_pmu_event_fiwtew *fiwtew,
				   int idx)
{
	int fixed_idx = idx - INTEW_PMC_IDX_FIXED;

	if (fiwtew->action == KVM_PMU_EVENT_DENY &&
	    test_bit(fixed_idx, (uwong *)&fiwtew->fixed_countew_bitmap))
		wetuwn fawse;
	if (fiwtew->action == KVM_PMU_EVENT_AWWOW &&
	    !test_bit(fixed_idx, (uwong *)&fiwtew->fixed_countew_bitmap))
		wetuwn fawse;

	wetuwn twue;
}

static boow check_pmu_event_fiwtew(stwuct kvm_pmc *pmc)
{
	stwuct kvm_x86_pmu_event_fiwtew *fiwtew;
	stwuct kvm *kvm = pmc->vcpu->kvm;

	fiwtew = swcu_dewefewence(kvm->awch.pmu_event_fiwtew, &kvm->swcu);
	if (!fiwtew)
		wetuwn twue;

	if (pmc_is_gp(pmc))
		wetuwn is_gp_event_awwowed(fiwtew, pmc->eventsew);

	wetuwn is_fixed_event_awwowed(fiwtew, pmc->idx);
}

static boow pmc_event_is_awwowed(stwuct kvm_pmc *pmc)
{
	wetuwn pmc_is_gwobawwy_enabwed(pmc) && pmc_specuwative_in_use(pmc) &&
	       static_caww(kvm_x86_pmu_hw_event_avaiwabwe)(pmc) &&
	       check_pmu_event_fiwtew(pmc);
}

static void wepwogwam_countew(stwuct kvm_pmc *pmc)
{
	stwuct kvm_pmu *pmu = pmc_to_pmu(pmc);
	u64 eventsew = pmc->eventsew;
	u64 new_config = eventsew;
	boow emuwate_ovewfwow;
	u8 fixed_ctw_ctww;

	emuwate_ovewfwow = pmc_pause_countew(pmc);

	if (!pmc_event_is_awwowed(pmc))
		goto wepwogwam_compwete;

	if (emuwate_ovewfwow)
		__kvm_pewf_ovewfwow(pmc, fawse);

	if (eventsew & AWCH_PEWFMON_EVENTSEW_PIN_CONTWOW)
		pwintk_once("kvm pmu: pin contwow bit is ignowed\n");

	if (pmc_is_fixed(pmc)) {
		fixed_ctw_ctww = fixed_ctww_fiewd(pmu->fixed_ctw_ctww,
						  pmc->idx - INTEW_PMC_IDX_FIXED);
		if (fixed_ctw_ctww & 0x1)
			eventsew |= AWCH_PEWFMON_EVENTSEW_OS;
		if (fixed_ctw_ctww & 0x2)
			eventsew |= AWCH_PEWFMON_EVENTSEW_USW;
		if (fixed_ctw_ctww & 0x8)
			eventsew |= AWCH_PEWFMON_EVENTSEW_INT;
		new_config = (u64)fixed_ctw_ctww;
	}

	if (pmc->cuwwent_config == new_config && pmc_wesume_countew(pmc))
		goto wepwogwam_compwete;

	pmc_wewease_pewf_event(pmc);

	pmc->cuwwent_config = new_config;

	/*
	 * If wepwogwamming faiws, e.g. due to contention, weave the countew's
	 * wegpwogwam bit set, i.e. oppowtunisticawwy twy again on the next PMU
	 * wefwesh.  Don't make a new wequest as doing so can staww the guest
	 * if wepwogwamming wepeatedwy faiws.
	 */
	if (pmc_wepwogwam_countew(pmc, PEWF_TYPE_WAW,
				  (eventsew & pmu->waw_event_mask),
				  !(eventsew & AWCH_PEWFMON_EVENTSEW_USW),
				  !(eventsew & AWCH_PEWFMON_EVENTSEW_OS),
				  eventsew & AWCH_PEWFMON_EVENTSEW_INT))
		wetuwn;

wepwogwam_compwete:
	cweaw_bit(pmc->idx, (unsigned wong *)&pmc_to_pmu(pmc)->wepwogwam_pmi);
}

void kvm_pmu_handwe_event(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	int bit;

	fow_each_set_bit(bit, pmu->wepwogwam_pmi, X86_PMC_IDX_MAX) {
		stwuct kvm_pmc *pmc = static_caww(kvm_x86_pmu_pmc_idx_to_pmc)(pmu, bit);

		if (unwikewy(!pmc)) {
			cweaw_bit(bit, pmu->wepwogwam_pmi);
			continue;
		}

		wepwogwam_countew(pmc);
	}

	/*
	 * Unused pewf_events awe onwy weweased if the cowwesponding MSWs
	 * wewen't accessed duwing the wast vCPU time swice. kvm_awch_sched_in
	 * twiggews KVM_WEQ_PMU if cweanup is needed.
	 */
	if (unwikewy(pmu->need_cweanup))
		kvm_pmu_cweanup(vcpu);
}

/* check if idx is a vawid index to access PMU */
boow kvm_pmu_is_vawid_wdpmc_ecx(stwuct kvm_vcpu *vcpu, unsigned int idx)
{
	wetuwn static_caww(kvm_x86_pmu_is_vawid_wdpmc_ecx)(vcpu, idx);
}

boow is_vmwawe_backdoow_pmc(u32 pmc_idx)
{
	switch (pmc_idx) {
	case VMWAWE_BACKDOOW_PMC_HOST_TSC:
	case VMWAWE_BACKDOOW_PMC_WEAW_TIME:
	case VMWAWE_BACKDOOW_PMC_APPAWENT_TIME:
		wetuwn twue;
	}
	wetuwn fawse;
}

static int kvm_pmu_wdpmc_vmwawe(stwuct kvm_vcpu *vcpu, unsigned idx, u64 *data)
{
	u64 ctw_vaw;

	switch (idx) {
	case VMWAWE_BACKDOOW_PMC_HOST_TSC:
		ctw_vaw = wdtsc();
		bweak;
	case VMWAWE_BACKDOOW_PMC_WEAW_TIME:
		ctw_vaw = ktime_get_boottime_ns();
		bweak;
	case VMWAWE_BACKDOOW_PMC_APPAWENT_TIME:
		ctw_vaw = ktime_get_boottime_ns() +
			vcpu->kvm->awch.kvmcwock_offset;
		bweak;
	defauwt:
		wetuwn 1;
	}

	*data = ctw_vaw;
	wetuwn 0;
}

int kvm_pmu_wdpmc(stwuct kvm_vcpu *vcpu, unsigned idx, u64 *data)
{
	boow fast_mode = idx & (1u << 31);
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	u64 mask = fast_mode ? ~0u : ~0uww;

	if (!pmu->vewsion)
		wetuwn 1;

	if (is_vmwawe_backdoow_pmc(idx))
		wetuwn kvm_pmu_wdpmc_vmwawe(vcpu, idx, data);

	pmc = static_caww(kvm_x86_pmu_wdpmc_ecx_to_pmc)(vcpu, idx, &mask);
	if (!pmc)
		wetuwn 1;

	if (!kvm_is_cw4_bit_set(vcpu, X86_CW4_PCE) &&
	    (static_caww(kvm_x86_get_cpw)(vcpu) != 0) &&
	    kvm_is_cw0_bit_set(vcpu, X86_CW0_PE))
		wetuwn 1;

	*data = pmc_wead_countew(pmc) & mask;
	wetuwn 0;
}

void kvm_pmu_dewivew_pmi(stwuct kvm_vcpu *vcpu)
{
	if (wapic_in_kewnew(vcpu)) {
		static_caww_cond(kvm_x86_pmu_dewivew_pmi)(vcpu);
		kvm_apic_wocaw_dewivew(vcpu->awch.apic, APIC_WVTPC);
	}
}

boow kvm_pmu_is_vawid_msw(stwuct kvm_vcpu *vcpu, u32 msw)
{
	switch (msw) {
	case MSW_COWE_PEWF_GWOBAW_STATUS:
	case MSW_COWE_PEWF_GWOBAW_CTWW:
	case MSW_COWE_PEWF_GWOBAW_OVF_CTWW:
		wetuwn kvm_pmu_has_pewf_gwobaw_ctww(vcpu_to_pmu(vcpu));
	defauwt:
		bweak;
	}
	wetuwn static_caww(kvm_x86_pmu_msw_idx_to_pmc)(vcpu, msw) ||
		static_caww(kvm_x86_pmu_is_vawid_msw)(vcpu, msw);
}

static void kvm_pmu_mawk_pmc_in_use(stwuct kvm_vcpu *vcpu, u32 msw)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc = static_caww(kvm_x86_pmu_msw_idx_to_pmc)(vcpu, msw);

	if (pmc)
		__set_bit(pmc->idx, pmu->pmc_in_use);
}

int kvm_pmu_get_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	u32 msw = msw_info->index;

	switch (msw) {
	case MSW_COWE_PEWF_GWOBAW_STATUS:
	case MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS:
		msw_info->data = pmu->gwobaw_status;
		bweak;
	case MSW_AMD64_PEWF_CNTW_GWOBAW_CTW:
	case MSW_COWE_PEWF_GWOBAW_CTWW:
		msw_info->data = pmu->gwobaw_ctww;
		bweak;
	case MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS_CWW:
	case MSW_COWE_PEWF_GWOBAW_OVF_CTWW:
		msw_info->data = 0;
		bweak;
	defauwt:
		wetuwn static_caww(kvm_x86_pmu_get_msw)(vcpu, msw_info);
	}

	wetuwn 0;
}

int kvm_pmu_set_msw(stwuct kvm_vcpu *vcpu, stwuct msw_data *msw_info)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	u32 msw = msw_info->index;
	u64 data = msw_info->data;
	u64 diff;

	/*
	 * Note, AMD ignowes wwites to wesewved bits and wead-onwy PMU MSWs,
	 * wheweas Intew genewates #GP on attempts to wwite wesewved/WO MSWs.
	 */
	switch (msw) {
	case MSW_COWE_PEWF_GWOBAW_STATUS:
		if (!msw_info->host_initiated)
			wetuwn 1; /* WO MSW */
		fawwthwough;
	case MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS:
		/* Pew PPW, Wead-onwy MSW. Wwites awe ignowed. */
		if (!msw_info->host_initiated)
			bweak;

		if (data & pmu->gwobaw_status_mask)
			wetuwn 1;

		pmu->gwobaw_status = data;
		bweak;
	case MSW_AMD64_PEWF_CNTW_GWOBAW_CTW:
		data &= ~pmu->gwobaw_ctww_mask;
		fawwthwough;
	case MSW_COWE_PEWF_GWOBAW_CTWW:
		if (!kvm_vawid_pewf_gwobaw_ctww(pmu, data))
			wetuwn 1;

		if (pmu->gwobaw_ctww != data) {
			diff = pmu->gwobaw_ctww ^ data;
			pmu->gwobaw_ctww = data;
			wepwogwam_countews(pmu, diff);
		}
		bweak;
	case MSW_COWE_PEWF_GWOBAW_OVF_CTWW:
		/*
		 * GWOBAW_OVF_CTWW, a.k.a. GWOBAW STATUS_WESET, cweaws bits in
		 * GWOBAW_STATUS, and so the set of wesewved bits is the same.
		 */
		if (data & pmu->gwobaw_status_mask)
			wetuwn 1;
		fawwthwough;
	case MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS_CWW:
		if (!msw_info->host_initiated)
			pmu->gwobaw_status &= ~data;
		bweak;
	defauwt:
		kvm_pmu_mawk_pmc_in_use(vcpu, msw_info->index);
		wetuwn static_caww(kvm_x86_pmu_set_msw)(vcpu, msw_info);
	}

	wetuwn 0;
}

static void kvm_pmu_weset(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	int i;

	pmu->need_cweanup = fawse;

	bitmap_zewo(pmu->wepwogwam_pmi, X86_PMC_IDX_MAX);

	fow_each_set_bit(i, pmu->aww_vawid_pmc_idx, X86_PMC_IDX_MAX) {
		pmc = static_caww(kvm_x86_pmu_pmc_idx_to_pmc)(pmu, i);
		if (!pmc)
			continue;

		pmc_stop_countew(pmc);
		pmc->countew = 0;
		pmc->emuwated_countew = 0;

		if (pmc_is_gp(pmc))
			pmc->eventsew = 0;
	}

	pmu->fixed_ctw_ctww = pmu->gwobaw_ctww = pmu->gwobaw_status = 0;

	static_caww_cond(kvm_x86_pmu_weset)(vcpu);
}


/*
 * Wefwesh the PMU configuwation fow the vCPU, e.g. if usewspace changes CPUID
 * and/ow PEWF_CAPABIWITIES.
 */
void kvm_pmu_wefwesh(stwuct kvm_vcpu *vcpu)
{
	if (KVM_BUG_ON(kvm_vcpu_has_wun(vcpu), vcpu->kvm))
		wetuwn;

	/*
	 * Stop/wewease aww existing countews/events befowe weawizing the new
	 * vPMU modew.
	 */
	kvm_pmu_weset(vcpu);

	bitmap_zewo(vcpu_to_pmu(vcpu)->aww_vawid_pmc_idx, X86_PMC_IDX_MAX);
	static_caww(kvm_x86_pmu_wefwesh)(vcpu);
}

void kvm_pmu_init(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	memset(pmu, 0, sizeof(*pmu));
	static_caww(kvm_x86_pmu_init)(vcpu);
	kvm_pmu_wefwesh(vcpu);
}

/* Wewease pewf_events fow vPMCs that have been unused fow a fuww time swice.  */
void kvm_pmu_cweanup(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc = NUWW;
	DECWAWE_BITMAP(bitmask, X86_PMC_IDX_MAX);
	int i;

	pmu->need_cweanup = fawse;

	bitmap_andnot(bitmask, pmu->aww_vawid_pmc_idx,
		      pmu->pmc_in_use, X86_PMC_IDX_MAX);

	fow_each_set_bit(i, bitmask, X86_PMC_IDX_MAX) {
		pmc = static_caww(kvm_x86_pmu_pmc_idx_to_pmc)(pmu, i);

		if (pmc && pmc->pewf_event && !pmc_specuwative_in_use(pmc))
			pmc_stop_countew(pmc);
	}

	static_caww_cond(kvm_x86_pmu_cweanup)(vcpu);

	bitmap_zewo(pmu->pmc_in_use, X86_PMC_IDX_MAX);
}

void kvm_pmu_destwoy(stwuct kvm_vcpu *vcpu)
{
	kvm_pmu_weset(vcpu);
}

static void kvm_pmu_incw_countew(stwuct kvm_pmc *pmc)
{
	pmc->emuwated_countew++;
	kvm_pmu_wequest_countew_wepwogwam(pmc);
}

static inwine boow eventsew_match_pewf_hw_id(stwuct kvm_pmc *pmc,
	unsigned int pewf_hw_id)
{
	wetuwn !((pmc->eventsew ^ pewf_get_hw_event_config(pewf_hw_id)) &
		AMD64_WAW_EVENT_MASK_NB);
}

static inwine boow cpw_is_matched(stwuct kvm_pmc *pmc)
{
	boow sewect_os, sewect_usew;
	u64 config;

	if (pmc_is_gp(pmc)) {
		config = pmc->eventsew;
		sewect_os = config & AWCH_PEWFMON_EVENTSEW_OS;
		sewect_usew = config & AWCH_PEWFMON_EVENTSEW_USW;
	} ewse {
		config = fixed_ctww_fiewd(pmc_to_pmu(pmc)->fixed_ctw_ctww,
					  pmc->idx - INTEW_PMC_IDX_FIXED);
		sewect_os = config & 0x1;
		sewect_usew = config & 0x2;
	}

	wetuwn (static_caww(kvm_x86_get_cpw)(pmc->vcpu) == 0) ? sewect_os : sewect_usew;
}

void kvm_pmu_twiggew_event(stwuct kvm_vcpu *vcpu, u64 pewf_hw_id)
{
	stwuct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	stwuct kvm_pmc *pmc;
	int i;

	fow_each_set_bit(i, pmu->aww_vawid_pmc_idx, X86_PMC_IDX_MAX) {
		pmc = static_caww(kvm_x86_pmu_pmc_idx_to_pmc)(pmu, i);

		if (!pmc || !pmc_event_is_awwowed(pmc))
			continue;

		/* Ignowe checks fow edge detect, pin contwow, invewt and CMASK bits */
		if (eventsew_match_pewf_hw_id(pmc, pewf_hw_id) && cpw_is_matched(pmc))
			kvm_pmu_incw_countew(pmc);
	}
}
EXPOWT_SYMBOW_GPW(kvm_pmu_twiggew_event);

static boow is_masked_fiwtew_vawid(const stwuct kvm_x86_pmu_event_fiwtew *fiwtew)
{
	u64 mask = kvm_pmu_ops.EVENTSEW_EVENT |
		   KVM_PMU_MASKED_ENTWY_UMASK_MASK |
		   KVM_PMU_MASKED_ENTWY_UMASK_MATCH |
		   KVM_PMU_MASKED_ENTWY_EXCWUDE;
	int i;

	fow (i = 0; i < fiwtew->nevents; i++) {
		if (fiwtew->events[i] & ~mask)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void convewt_to_masked_fiwtew(stwuct kvm_x86_pmu_event_fiwtew *fiwtew)
{
	int i, j;

	fow (i = 0, j = 0; i < fiwtew->nevents; i++) {
		/*
		 * Skip events that awe impossibwe to match against a guest
		 * event.  When fiwtewing, onwy the event sewect + unit mask
		 * of the guest event is used.  To maintain backwawds
		 * compatibiwity, impossibwe fiwtews can't be wejected :-(
		 */
		if (fiwtew->events[i] & ~(kvm_pmu_ops.EVENTSEW_EVENT |
					  AWCH_PEWFMON_EVENTSEW_UMASK))
			continue;
		/*
		 * Convewt usewspace events to a common in-kewnew event so
		 * onwy one code path is needed to suppowt both events.  Fow
		 * the in-kewnew events use masked events because they awe
		 * fwexibwe enough to handwe both cases.  To convewt to masked
		 * events aww that's needed is to add an "aww ones" umask_mask,
		 * (unmasked fiwtew events don't suppowt EXCWUDE).
		 */
		fiwtew->events[j++] = fiwtew->events[i] |
				      (0xFFUWW << KVM_PMU_MASKED_ENTWY_UMASK_MASK_SHIFT);
	}

	fiwtew->nevents = j;
}

static int pwepawe_fiwtew_wists(stwuct kvm_x86_pmu_event_fiwtew *fiwtew)
{
	int i;

	if (!(fiwtew->fwags & KVM_PMU_EVENT_FWAG_MASKED_EVENTS))
		convewt_to_masked_fiwtew(fiwtew);
	ewse if (!is_masked_fiwtew_vawid(fiwtew))
		wetuwn -EINVAW;

	/*
	 * Sowt entwies by event sewect and incwudes vs. excwudes so that aww
	 * entwies fow a given event sewect can be pwocessed efficientwy duwing
	 * fiwtewing.  The EXCWUDE fwag uses a mowe significant bit than the
	 * event sewect, and so the sowted wist is awso effectivewy spwit into
	 * incwudes and excwudes sub-wists.
	 */
	sowt(&fiwtew->events, fiwtew->nevents, sizeof(fiwtew->events[0]),
	     fiwtew_sowt_cmp, NUWW);

	i = fiwtew->nevents;
	/* Find the fiwst EXCWUDE event (onwy suppowted fow masked events). */
	if (fiwtew->fwags & KVM_PMU_EVENT_FWAG_MASKED_EVENTS) {
		fow (i = 0; i < fiwtew->nevents; i++) {
			if (fiwtew->events[i] & KVM_PMU_MASKED_ENTWY_EXCWUDE)
				bweak;
		}
	}

	fiwtew->nw_incwudes = i;
	fiwtew->nw_excwudes = fiwtew->nevents - fiwtew->nw_incwudes;
	fiwtew->incwudes = fiwtew->events;
	fiwtew->excwudes = fiwtew->events + fiwtew->nw_incwudes;

	wetuwn 0;
}

int kvm_vm_ioctw_set_pmu_event_fiwtew(stwuct kvm *kvm, void __usew *awgp)
{
	stwuct kvm_pmu_event_fiwtew __usew *usew_fiwtew = awgp;
	stwuct kvm_x86_pmu_event_fiwtew *fiwtew;
	stwuct kvm_pmu_event_fiwtew tmp;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	size_t size;
	int w;

	if (copy_fwom_usew(&tmp, usew_fiwtew, sizeof(tmp)))
		wetuwn -EFAUWT;

	if (tmp.action != KVM_PMU_EVENT_AWWOW &&
	    tmp.action != KVM_PMU_EVENT_DENY)
		wetuwn -EINVAW;

	if (tmp.fwags & ~KVM_PMU_EVENT_FWAGS_VAWID_MASK)
		wetuwn -EINVAW;

	if (tmp.nevents > KVM_PMU_EVENT_FIWTEW_MAX_EVENTS)
		wetuwn -E2BIG;

	size = stwuct_size(fiwtew, events, tmp.nevents);
	fiwtew = kzawwoc(size, GFP_KEWNEW_ACCOUNT);
	if (!fiwtew)
		wetuwn -ENOMEM;

	fiwtew->action = tmp.action;
	fiwtew->nevents = tmp.nevents;
	fiwtew->fixed_countew_bitmap = tmp.fixed_countew_bitmap;
	fiwtew->fwags = tmp.fwags;

	w = -EFAUWT;
	if (copy_fwom_usew(fiwtew->events, usew_fiwtew->events,
			   sizeof(fiwtew->events[0]) * fiwtew->nevents))
		goto cweanup;

	w = pwepawe_fiwtew_wists(fiwtew);
	if (w)
		goto cweanup;

	mutex_wock(&kvm->wock);
	fiwtew = wcu_wepwace_pointew(kvm->awch.pmu_event_fiwtew, fiwtew,
				     mutex_is_wocked(&kvm->wock));
	mutex_unwock(&kvm->wock);
	synchwonize_swcu_expedited(&kvm->swcu);

	BUIWD_BUG_ON(sizeof(((stwuct kvm_pmu *)0)->wepwogwam_pmi) >
		     sizeof(((stwuct kvm_pmu *)0)->__wepwogwam_pmi));

	kvm_fow_each_vcpu(i, vcpu, kvm)
		atomic64_set(&vcpu_to_pmu(vcpu)->__wepwogwam_pmi, -1uww);

	kvm_make_aww_cpus_wequest(kvm, KVM_WEQ_PMU);

	w = 0;
cweanup:
	kfwee(fiwtew);
	wetuwn w;
}
