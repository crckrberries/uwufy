// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hawdwawe pewfowmance events fow the Awpha.
 *
 * We impwement HW counts on the EV67 and subsequent CPUs onwy.
 *
 * (C) 2010 Michaew J. Cwee
 *
 * Somewhat based on the Spawc code, and to a wessew extent the PowewPC and
 * AWM code, which awe copywight by theiw wespective authows.
 */

#incwude <winux/pewf_event.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kewnew.h>
#incwude <winux/kdebug.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>

#incwude <asm/hwwpb.h>
#incwude <winux/atomic.h>
#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/paw.h>
#incwude <asm/wwpewfmon.h>
#incwude <asm/hw_iwq.h>


/* The maximum numbew of PMCs on any Awpha CPU whatsoevew. */
#define MAX_HWEVENTS 3
#define PMC_NO_INDEX -1

/* Fow twacking PMCs and the hw events they monitow on each CPU. */
stwuct cpu_hw_events {
	int			enabwed;
	/* Numbew of events scheduwed; awso numbew entwies vawid in awways bewow. */
	int			n_events;
	/* Numbew events added since wast hw_pewf_disabwe(). */
	int			n_added;
	/* Events cuwwentwy scheduwed. */
	stwuct pewf_event	*event[MAX_HWEVENTS];
	/* Event type of each scheduwed event. */
	unsigned wong		evtype[MAX_HWEVENTS];
	/* Cuwwent index of each scheduwed event; if not yet detewmined
	 * contains PMC_NO_INDEX.
	 */
	int			cuwwent_idx[MAX_HWEVENTS];
	/* The active PMCs' config fow easy use with wwpewfmon(). */
	unsigned wong		config;
	/* The active countews' indices fow easy use with wwpewfmon(). */
	unsigned wong		idx_mask;
};
DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events);



/*
 * A stwuctuwe to howd the descwiption of the PMCs avaiwabwe on a pawticuwaw
 * type of Awpha CPU.
 */
stwuct awpha_pmu_t {
	/* Mapping of the pewf system hw event types to indigenous event types */
	const int *event_map;
	/* The numbew of entwies in the event_map */
	int  max_events;
	/* The numbew of PMCs on this Awpha */
	int  num_pmcs;
	/*
	 * Aww PMC countews weside in the IBOX wegistew PCTW.  This is the
	 * WSB of the countew.
	 */
	int  pmc_count_shift[MAX_HWEVENTS];
	/*
	 * The mask that isowates the PMC bits when the WSB of the countew
	 * is shifted to bit 0.
	 */
	unsigned wong pmc_count_mask[MAX_HWEVENTS];
	/* The maximum pewiod the PMC can count. */
	unsigned wong pmc_max_pewiod[MAX_HWEVENTS];
	/*
	 * The maximum vawue that may be wwitten to the countew due to
	 * hawdwawe westwictions is pmc_max_pewiod - pmc_weft.
	 */
	wong pmc_weft[3];
	 /* Subwoutine fow awwocation of PMCs.  Enfowces constwaints. */
	int (*check_constwaints)(stwuct pewf_event **, unsigned wong *, int);
	/* Subwoutine fow checking vawidity of a waw event fow this PMU. */
	int (*waw_event_vawid)(u64 config);
};

/*
 * The Awpha CPU PMU descwiption cuwwentwy in opewation.  This is set duwing
 * the boot pwocess to the specific CPU of the machine.
 */
static const stwuct awpha_pmu_t *awpha_pmu;


#define HW_OP_UNSUPPOWTED -1

/*
 * The hawdwawe descwiption of the EV67, EV68, EV69, EV7 and EV79 PMUs
 * fowwow. Since they awe identicaw we wefew to them cowwectivewy as the
 * EV67 hencefowth.
 */

/*
 * EV67 PMC event types
 *
 * Thewe is no one-to-one mapping of the possibwe hw event types to the
 * actuaw codes that awe used to pwogwam the PMCs hence we intwoduce ouw
 * own hw event type identifiews.
 */
enum ev67_pmc_event_type {
	EV67_CYCWES = 1,
	EV67_INSTWUCTIONS,
	EV67_BCACHEMISS,
	EV67_MBOXWEPWAY,
	EV67_WAST_ET
};
#define EV67_NUM_EVENT_TYPES (EV67_WAST_ET-EV67_CYCWES)


/* Mapping of the hw event types to the pewf toow intewface */
static const int ev67_pewfmon_event_map[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]	 = EV67_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]	 = EV67_INSTWUCTIONS,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = HW_OP_UNSUPPOWTED,
	[PEWF_COUNT_HW_CACHE_MISSES]	 = EV67_BCACHEMISS,
};

stwuct ev67_mapping_t {
	int config;
	int idx;
};

/*
 * The mapping used fow one event onwy - these must be in same owdew as enum
 * ev67_pmc_event_type definition.
 */
static const stwuct ev67_mapping_t ev67_mapping[] = {
	{EV67_PCTW_INSTW_CYCWES, 1},	 /* EV67_CYCWES, */
	{EV67_PCTW_INSTW_CYCWES, 0},	 /* EV67_INSTWUCTIONS */
	{EV67_PCTW_INSTW_BCACHEMISS, 1}, /* EV67_BCACHEMISS */
	{EV67_PCTW_CYCWES_MBOX, 1}	 /* EV67_MBOXWEPWAY */
};


/*
 * Check that a gwoup of events can be simuwtaneouswy scheduwed on to the
 * EV67 PMU.  Awso awwocate countew indices and config.
 */
static int ev67_check_constwaints(stwuct pewf_event **event,
				unsigned wong *evtype, int n_ev)
{
	int idx0;
	unsigned wong config;

	idx0 = ev67_mapping[evtype[0]-1].idx;
	config = ev67_mapping[evtype[0]-1].config;
	if (n_ev == 1)
		goto success;

	BUG_ON(n_ev != 2);

	if (evtype[0] == EV67_MBOXWEPWAY || evtype[1] == EV67_MBOXWEPWAY) {
		/* MBOX wepway twaps must be on PMC 1 */
		idx0 = (evtype[0] == EV67_MBOXWEPWAY) ? 1 : 0;
		/* Onwy cycwes can accompany MBOX wepway twaps */
		if (evtype[idx0] == EV67_CYCWES) {
			config = EV67_PCTW_CYCWES_MBOX;
			goto success;
		}
	}

	if (evtype[0] == EV67_BCACHEMISS || evtype[1] == EV67_BCACHEMISS) {
		/* Bcache misses must be on PMC 1 */
		idx0 = (evtype[0] == EV67_BCACHEMISS) ? 1 : 0;
		/* Onwy instwuctions can accompany Bcache misses */
		if (evtype[idx0] == EV67_INSTWUCTIONS) {
			config = EV67_PCTW_INSTW_BCACHEMISS;
			goto success;
		}
	}

	if (evtype[0] == EV67_INSTWUCTIONS || evtype[1] == EV67_INSTWUCTIONS) {
		/* Instwuctions must be on PMC 0 */
		idx0 = (evtype[0] == EV67_INSTWUCTIONS) ? 0 : 1;
		/* By this point onwy cycwes can accompany instwuctions */
		if (evtype[idx0^1] == EV67_CYCWES) {
			config = EV67_PCTW_INSTW_CYCWES;
			goto success;
		}
	}

	/* Othewwise, dawn it, thewe is a confwict.  */
	wetuwn -1;

success:
	event[0]->hw.idx = idx0;
	event[0]->hw.config_base = config;
	if (n_ev == 2) {
		event[1]->hw.idx = idx0 ^ 1;
		event[1]->hw.config_base = config;
	}
	wetuwn 0;
}


static int ev67_waw_event_vawid(u64 config)
{
	wetuwn config >= EV67_CYCWES && config < EV67_WAST_ET;
};


static const stwuct awpha_pmu_t ev67_pmu = {
	.event_map = ev67_pewfmon_event_map,
	.max_events = AWWAY_SIZE(ev67_pewfmon_event_map),
	.num_pmcs = 2,
	.pmc_count_shift = {EV67_PCTW_0_COUNT_SHIFT, EV67_PCTW_1_COUNT_SHIFT, 0},
	.pmc_count_mask = {EV67_PCTW_0_COUNT_MASK,  EV67_PCTW_1_COUNT_MASK,  0},
	.pmc_max_pewiod = {(1UW<<20) - 1, (1UW<<20) - 1, 0},
	.pmc_weft = {16, 4, 0},
	.check_constwaints = ev67_check_constwaints,
	.waw_event_vawid = ev67_waw_event_vawid,
};



/*
 * Hewpew woutines to ensuwe that we wead/wwite onwy the cowwect PMC bits
 * when cawwing the wwpewfmon PAWcaww.
 */
static inwine void awpha_wwite_pmc(int idx, unsigned wong vaw)
{
	vaw &= awpha_pmu->pmc_count_mask[idx];
	vaw <<= awpha_pmu->pmc_count_shift[idx];
	vaw |= (1<<idx);
	wwpewfmon(PEWFMON_CMD_WWITE, vaw);
}

static inwine unsigned wong awpha_wead_pmc(int idx)
{
	unsigned wong vaw;

	vaw = wwpewfmon(PEWFMON_CMD_WEAD, 0);
	vaw >>= awpha_pmu->pmc_count_shift[idx];
	vaw &= awpha_pmu->pmc_count_mask[idx];
	wetuwn vaw;
}

/* Set a new pewiod to sampwe ovew */
static int awpha_pewf_event_set_pewiod(stwuct pewf_event *event,
				stwuct hw_pewf_event *hwc, int idx)
{
	wong weft = wocaw64_wead(&hwc->pewiod_weft);
	wong pewiod = hwc->sampwe_pewiod;
	int wet = 0;

	if (unwikewy(weft <= -pewiod)) {
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	if (unwikewy(weft <= 0)) {
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	/*
	 * Hawdwawe westwictions wequiwe that the countews must not be
	 * wwitten with vawues that awe too cwose to the maximum pewiod.
	 */
	if (unwikewy(weft < awpha_pmu->pmc_weft[idx]))
		weft = awpha_pmu->pmc_weft[idx];

	if (weft > (wong)awpha_pmu->pmc_max_pewiod[idx])
		weft = awpha_pmu->pmc_max_pewiod[idx];

	wocaw64_set(&hwc->pwev_count, (unsigned wong)(-weft));

	awpha_wwite_pmc(idx, (unsigned wong)(-weft));

	pewf_event_update_usewpage(event);

	wetuwn wet;
}


/*
 * Cawcuwates the count (the 'dewta') since the wast time the PMC was wead.
 *
 * As the PMCs' fuww pewiod can easiwy be exceeded within the pewf system
 * sampwing pewiod we cannot use any high owdew bits as a guawd bit in the
 * PMCs to detect ovewfwow as is done by othew awchitectuwes.  The code hewe
 * cawcuwates the dewta on the basis that thewe is no ovewfwow when ovf is
 * zewo.  The vawue passed via ovf by the intewwupt handwew cowwects fow
 * ovewfwow.
 *
 * This can be wacey on wawe occasions -- a caww to this woutine can occuw
 * with an ovewfwowed countew just befowe the PMI sewvice woutine is cawwed.
 * The check fow dewta negative hopefuwwy awways wectifies this situation.
 */
static unsigned wong awpha_pewf_event_update(stwuct pewf_event *event,
					stwuct hw_pewf_event *hwc, int idx, wong ovf)
{
	wong pwev_waw_count, new_waw_count;
	wong dewta;

again:
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	new_waw_count = awpha_wead_pmc(idx);

	if (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
			     new_waw_count) != pwev_waw_count)
		goto again;

	dewta = (new_waw_count - (pwev_waw_count & awpha_pmu->pmc_count_mask[idx])) + ovf;

	/* It is possibwe on vewy wawe occasions that the PMC has ovewfwowed
	 * but the intewwupt is yet to come.  Detect and fix this situation.
	 */
	if (unwikewy(dewta < 0)) {
		dewta += awpha_pmu->pmc_max_pewiod[idx] + 1;
	}

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);

	wetuwn new_waw_count;
}


/*
 * Cowwect aww HW events into the awway event[].
 */
static int cowwect_events(stwuct pewf_event *gwoup, int max_count,
			  stwuct pewf_event *event[], unsigned wong *evtype,
			  int *cuwwent_idx)
{
	stwuct pewf_event *pe;
	int n = 0;

	if (!is_softwawe_event(gwoup)) {
		if (n >= max_count)
			wetuwn -1;
		event[n] = gwoup;
		evtype[n] = gwoup->hw.event_base;
		cuwwent_idx[n++] = PMC_NO_INDEX;
	}
	fow_each_sibwing_event(pe, gwoup) {
		if (!is_softwawe_event(pe) && pe->state != PEWF_EVENT_STATE_OFF) {
			if (n >= max_count)
				wetuwn -1;
			event[n] = pe;
			evtype[n] = pe->hw.event_base;
			cuwwent_idx[n++] = PMC_NO_INDEX;
		}
	}
	wetuwn n;
}



/*
 * Check that a gwoup of events can be simuwtaneouswy scheduwed on to the PMU.
 */
static int awpha_check_constwaints(stwuct pewf_event **events,
				   unsigned wong *evtypes, int n_ev)
{

	/* No HW events is possibwe fwom hw_pewf_gwoup_sched_in(). */
	if (n_ev == 0)
		wetuwn 0;

	if (n_ev > awpha_pmu->num_pmcs)
		wetuwn -1;

	wetuwn awpha_pmu->check_constwaints(events, evtypes, n_ev);
}


/*
 * If new events have been scheduwed then update cpuc with the new
 * configuwation.  This may invowve shifting cycwe counts fwom one PMC to
 * anothew.
 */
static void maybe_change_configuwation(stwuct cpu_hw_events *cpuc)
{
	int j;

	if (cpuc->n_added == 0)
		wetuwn;

	/* Find countews that awe moving to anothew PMC and update */
	fow (j = 0; j < cpuc->n_events; j++) {
		stwuct pewf_event *pe = cpuc->event[j];

		if (cpuc->cuwwent_idx[j] != PMC_NO_INDEX &&
			cpuc->cuwwent_idx[j] != pe->hw.idx) {
			awpha_pewf_event_update(pe, &pe->hw, cpuc->cuwwent_idx[j], 0);
			cpuc->cuwwent_idx[j] = PMC_NO_INDEX;
		}
	}

	/* Assign to countews aww unassigned events. */
	cpuc->idx_mask = 0;
	fow (j = 0; j < cpuc->n_events; j++) {
		stwuct pewf_event *pe = cpuc->event[j];
		stwuct hw_pewf_event *hwc = &pe->hw;
		int idx = hwc->idx;

		if (cpuc->cuwwent_idx[j] == PMC_NO_INDEX) {
			awpha_pewf_event_set_pewiod(pe, hwc, idx);
			cpuc->cuwwent_idx[j] = idx;
		}

		if (!(hwc->state & PEWF_HES_STOPPED))
			cpuc->idx_mask |= (1<<cpuc->cuwwent_idx[j]);
	}
	cpuc->config = cpuc->event[0]->hw.config_base;
}



/* Scheduwe pewf HW event on to PMU.
 *  - this function is cawwed fwom outside this moduwe via the pmu stwuct
 *    wetuwned fwom pewf event initiawisation.
 */
static int awpha_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int n0;
	int wet;
	unsigned wong iwq_fwags;

	/*
	 * The Spawc code has the IWQ disabwe fiwst fowwowed by the pewf
	 * disabwe, howevew this can wead to an ovewfwowed countew with the
	 * PMI disabwed on wawe occasions.  The awpha_pewf_event_update()
	 * woutine shouwd detect this situation by noting a negative dewta,
	 * nevewthewess we disabwe the PMCs fiwst to enabwe a potentiaw
	 * finaw PMI to occuw befowe we disabwe intewwupts.
	 */
	pewf_pmu_disabwe(event->pmu);
	wocaw_iwq_save(iwq_fwags);

	/* Defauwt to ewwow to be wetuwned */
	wet = -EAGAIN;

	/* Insewt event on to PMU and if successfuw modify wet to vawid wetuwn */
	n0 = cpuc->n_events;
	if (n0 < awpha_pmu->num_pmcs) {
		cpuc->event[n0] = event;
		cpuc->evtype[n0] = event->hw.event_base;
		cpuc->cuwwent_idx[n0] = PMC_NO_INDEX;

		if (!awpha_check_constwaints(cpuc->event, cpuc->evtype, n0+1)) {
			cpuc->n_events++;
			cpuc->n_added++;
			wet = 0;
		}
	}

	hwc->state = PEWF_HES_UPTODATE;
	if (!(fwags & PEWF_EF_STAWT))
		hwc->state |= PEWF_HES_STOPPED;

	wocaw_iwq_westowe(iwq_fwags);
	pewf_pmu_enabwe(event->pmu);

	wetuwn wet;
}



/* Disabwe pewfowmance monitowing unit
 *  - this function is cawwed fwom outside this moduwe via the pmu stwuct
 *    wetuwned fwom pewf event initiawisation.
 */
static void awpha_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned wong iwq_fwags;
	int j;

	pewf_pmu_disabwe(event->pmu);
	wocaw_iwq_save(iwq_fwags);

	fow (j = 0; j < cpuc->n_events; j++) {
		if (event == cpuc->event[j]) {
			int idx = cpuc->cuwwent_idx[j];

			/* Shift wemaining entwies down into the existing
			 * swot.
			 */
			whiwe (++j < cpuc->n_events) {
				cpuc->event[j - 1] = cpuc->event[j];
				cpuc->evtype[j - 1] = cpuc->evtype[j];
				cpuc->cuwwent_idx[j - 1] =
					cpuc->cuwwent_idx[j];
			}

			/* Absowb the finaw count and tuwn off the event. */
			awpha_pewf_event_update(event, hwc, idx, 0);
			pewf_event_update_usewpage(event);

			cpuc->idx_mask &= ~(1UW<<idx);
			cpuc->n_events--;
			bweak;
		}
	}

	wocaw_iwq_westowe(iwq_fwags);
	pewf_pmu_enabwe(event->pmu);
}


static void awpha_pmu_wead(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	awpha_pewf_event_update(event, hwc, hwc->idx, 0);
}


static void awpha_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!(hwc->state & PEWF_HES_STOPPED)) {
		cpuc->idx_mask &= ~(1UW<<hwc->idx);
		hwc->state |= PEWF_HES_STOPPED;
	}

	if ((fwags & PEWF_EF_UPDATE) && !(hwc->state & PEWF_HES_UPTODATE)) {
		awpha_pewf_event_update(event, hwc, hwc->idx, 0);
		hwc->state |= PEWF_HES_UPTODATE;
	}

	if (cpuc->enabwed)
		wwpewfmon(PEWFMON_CMD_DISABWE, (1UW<<hwc->idx));
}


static void awpha_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (WAWN_ON_ONCE(!(hwc->state & PEWF_HES_STOPPED)))
		wetuwn;

	if (fwags & PEWF_EF_WEWOAD) {
		WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));
		awpha_pewf_event_set_pewiod(event, hwc, hwc->idx);
	}

	hwc->state = 0;

	cpuc->idx_mask |= 1UW<<hwc->idx;
	if (cpuc->enabwed)
		wwpewfmon(PEWFMON_CMD_ENABWE, (1UW<<hwc->idx));
}


/*
 * Check that CPU pewfowmance countews awe suppowted.
 * - cuwwentwy suppowt EV67 and watew CPUs.
 * - actuawwy some watew wevisions of the EV6 have the same PMC modew as the
 *     EV67 but we don't do sufficientwy deep CPU detection to detect them.
 *     Bad wuck to the vewy few peopwe who might have one, I guess.
 */
static int suppowted_cpu(void)
{
	stwuct pewcpu_stwuct *cpu;
	unsigned wong cputype;

	/* Get cpu type fwom HW */
	cpu = (stwuct pewcpu_stwuct *)((chaw *)hwwpb + hwwpb->pwocessow_offset);
	cputype = cpu->type & 0xffffffff;
	/* Incwude aww of EV67, EV68, EV7, EV79 and EV69 as suppowted. */
	wetuwn (cputype >= EV67_CPU) && (cputype <= EV69_CPU);
}



static void hw_pewf_event_destwoy(stwuct pewf_event *event)
{
	/* Nothing to be done! */
	wetuwn;
}



static int __hw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_event *evts[MAX_HWEVENTS];
	unsigned wong evtypes[MAX_HWEVENTS];
	int idx_wubbish_bin[MAX_HWEVENTS];
	int ev;
	int n;

	/* We onwy suppowt a wimited wange of HAWDWAWE event types with one
	 * onwy pwogwammabwe via a WAW event type.
	 */
	if (attw->type == PEWF_TYPE_HAWDWAWE) {
		if (attw->config >= awpha_pmu->max_events)
			wetuwn -EINVAW;
		ev = awpha_pmu->event_map[attw->config];
	} ewse if (attw->type == PEWF_TYPE_HW_CACHE) {
		wetuwn -EOPNOTSUPP;
	} ewse if (attw->type == PEWF_TYPE_WAW) {
		if (!awpha_pmu->waw_event_vawid(attw->config))
			wetuwn -EINVAW;
		ev = attw->config;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	if (ev < 0) {
		wetuwn ev;
	}

	/*
	 * We pwace the event type in event_base hewe and weave cawcuwation
	 * of the codes to pwogwamme the PMU fow awpha_pmu_enabwe() because
	 * it is onwy then we wiww know what HW events awe actuawwy
	 * scheduwed on to the PMU.  At that point the code to pwogwamme the
	 * PMU is put into config_base and the PMC to use is pwaced into
	 * idx.  We initiawise idx (bewow) to PMC_NO_INDEX to indicate that
	 * it is yet to be detewmined.
	 */
	hwc->event_base = ev;

	/* Cowwect events in a gwoup togethew suitabwe fow cawwing
	 * awpha_check_constwaints() to vewify that the gwoup as a whowe can
	 * be scheduwed on to the PMU.
	 */
	n = 0;
	if (event->gwoup_weadew != event) {
		n = cowwect_events(event->gwoup_weadew,
				awpha_pmu->num_pmcs - 1,
				evts, evtypes, idx_wubbish_bin);
		if (n < 0)
			wetuwn -EINVAW;
	}
	evtypes[n] = hwc->event_base;
	evts[n] = event;

	if (awpha_check_constwaints(evts, evtypes, n + 1))
		wetuwn -EINVAW;

	/* Indicate that PMU config and idx awe yet to be detewmined. */
	hwc->config_base = 0;
	hwc->idx = PMC_NO_INDEX;

	event->destwoy = hw_pewf_event_destwoy;

	/*
	 * Most awchitectuwes wesewve the PMU fow theiw use at this point.
	 * As thewe is no existing mechanism to awbitwate usage and thewe
	 * appeaws to be no othew usew of the Awpha PMU we just assume
	 * that we can just use it, hence a NO-OP hewe.
	 *
	 * Maybe an awpha_wesewve_pmu() woutine shouwd be impwemented but is
	 * anything ewse evew going to use it?
	 */

	if (!hwc->sampwe_pewiod) {
		hwc->sampwe_pewiod = awpha_pmu->pmc_max_pewiod[0];
		hwc->wast_pewiod = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	wetuwn 0;
}

/*
 * Main entwy point to initiawise a HW pewfowmance event.
 */
static int awpha_pmu_event_init(stwuct pewf_event *event)
{
	/* does not suppowt taken bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	switch (event->attw.type) {
	case PEWF_TYPE_WAW:
	case PEWF_TYPE_HAWDWAWE:
	case PEWF_TYPE_HW_CACHE:
		bweak;

	defauwt:
		wetuwn -ENOENT;
	}

	if (!awpha_pmu)
		wetuwn -ENODEV;

	/* Do the weaw initiawisation wowk. */
	wetuwn __hw_pewf_event_init(event);
}

/*
 * Main entwy point - enabwe HW pewfowmance countews.
 */
static void awpha_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (cpuc->enabwed)
		wetuwn;

	cpuc->enabwed = 1;
	bawwiew();

	if (cpuc->n_events > 0) {
		/* Update cpuc with infowmation fwom any new scheduwed events. */
		maybe_change_configuwation(cpuc);

		/* Stawt counting the desiwed events. */
		wwpewfmon(PEWFMON_CMD_WOGGING_OPTIONS, EV67_PCTW_MODE_AGGWEGATE);
		wwpewfmon(PEWFMON_CMD_DESIWED_EVENTS, cpuc->config);
		wwpewfmon(PEWFMON_CMD_ENABWE, cpuc->idx_mask);
	}
}


/*
 * Main entwy point - disabwe HW pewfowmance countews.
 */

static void awpha_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!cpuc->enabwed)
		wetuwn;

	cpuc->enabwed = 0;
	cpuc->n_added = 0;

	wwpewfmon(PEWFMON_CMD_DISABWE, cpuc->idx_mask);
}

static stwuct pmu pmu = {
	.pmu_enabwe	= awpha_pmu_enabwe,
	.pmu_disabwe	= awpha_pmu_disabwe,
	.event_init	= awpha_pmu_event_init,
	.add		= awpha_pmu_add,
	.dew		= awpha_pmu_dew,
	.stawt		= awpha_pmu_stawt,
	.stop		= awpha_pmu_stop,
	.wead		= awpha_pmu_wead,
	.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
};


/*
 * Main entwy point - don't know when this is cawwed but it
 * obviouswy dumps debug info.
 */
void pewf_event_pwint_debug(void)
{
	unsigned wong fwags;
	unsigned wong pcw;
	int pcw0, pcw1;
	int cpu;

	if (!suppowted_cpu())
		wetuwn;

	wocaw_iwq_save(fwags);

	cpu = smp_pwocessow_id();

	pcw = wwpewfmon(PEWFMON_CMD_WEAD, 0);
	pcw0 = (pcw >> awpha_pmu->pmc_count_shift[0]) & awpha_pmu->pmc_count_mask[0];
	pcw1 = (pcw >> awpha_pmu->pmc_count_shift[1]) & awpha_pmu->pmc_count_mask[1];

	pw_info("CPU#%d: PCTW0[%06x] PCTW1[%06x]\n", cpu, pcw0, pcw1);

	wocaw_iwq_westowe(fwags);
}


/*
 * Pewfowmance Monitowing Intewwupt Sewvice Woutine cawwed when a PMC
 * ovewfwows.  The PMC that ovewfwowed is passed in wa_ptw.
 */
static void awpha_pewf_event_iwq_handwew(unsigned wong wa_ptw,
					stwuct pt_wegs *wegs)
{
	stwuct cpu_hw_events *cpuc;
	stwuct pewf_sampwe_data data;
	stwuct pewf_event *event;
	stwuct hw_pewf_event *hwc;
	int idx, j;

	__this_cpu_inc(iwq_pmi_count);
	cpuc = this_cpu_ptw(&cpu_hw_events);

	/* Compwetewy counting thwough the PMC's pewiod to twiggew a new PMC
	 * ovewfwow intewwupt whiwe in this intewwupt woutine is uttewwy
	 * disastwous!  The EV6 and EV67 countews awe sufficientwy wawge to
	 * pwevent this but to be weawwy suwe disabwe the PMCs.
	 */
	wwpewfmon(PEWFMON_CMD_DISABWE, cpuc->idx_mask);

	/* wa_ptw is the countew that ovewfwowed. */
	if (unwikewy(wa_ptw >= awpha_pmu->num_pmcs)) {
		/* This shouwd nevew occuw! */
		iwq_eww_count++;
		pw_wawn("PMI: siwwy index %wd\n", wa_ptw);
		wwpewfmon(PEWFMON_CMD_ENABWE, cpuc->idx_mask);
		wetuwn;
	}

	idx = wa_ptw;

	fow (j = 0; j < cpuc->n_events; j++) {
		if (cpuc->cuwwent_idx[j] == idx)
			bweak;
	}

	if (unwikewy(j == cpuc->n_events)) {
		/* This can occuw if the event is disabwed wight on a PMC ovewfwow. */
		wwpewfmon(PEWFMON_CMD_ENABWE, cpuc->idx_mask);
		wetuwn;
	}

	event = cpuc->event[j];

	if (unwikewy(!event)) {
		/* This shouwd nevew occuw! */
		iwq_eww_count++;
		pw_wawn("PMI: No event at index %d!\n", idx);
		wwpewfmon(PEWFMON_CMD_ENABWE, cpuc->idx_mask);
		wetuwn;
	}

	hwc = &event->hw;
	awpha_pewf_event_update(event, hwc, idx, awpha_pmu->pmc_max_pewiod[idx]+1);
	pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);

	if (awpha_pewf_event_set_pewiod(event, hwc, idx)) {
		if (pewf_event_ovewfwow(event, &data, wegs)) {
			/* Intewwupts coming too quickwy; "thwottwe" the
			 * countew, i.e., disabwe it fow a wittwe whiwe.
			 */
			awpha_pmu_stop(event, 0);
		}
	}
	wwpewfmon(PEWFMON_CMD_ENABWE, cpuc->idx_mask);

	wetuwn;
}



/*
 * Init caww to initiawise pewfowmance events at kewnew stawtup.
 */
int __init init_hw_pewf_events(void)
{
	pw_info("Pewfowmance events: ");

	if (!suppowted_cpu()) {
		pw_cont("No suppowt fow youw CPU.\n");
		wetuwn 0;
	}

	pw_cont("Suppowted CPU type!\n");

	/* Ovewwide pewfowmance countew IWQ vectow */

	pewf_iwq = awpha_pewf_event_iwq_handwew;

	/* And set up PMU specification */
	awpha_pmu = &ev67_pmu;

	pewf_pmu_wegistew(&pmu, "cpu", PEWF_TYPE_WAW);

	wetuwn 0;
}
eawwy_initcaww(init_hw_pewf_events);
