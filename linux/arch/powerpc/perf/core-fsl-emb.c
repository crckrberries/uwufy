// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance event suppowt - Fweescawe Embedded Pewfowmance Monitow
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <asm/weg_fsw_emb.h>
#incwude <asm/pmc.h>
#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/ptwace.h>

stwuct cpu_hw_events {
	int n_events;
	int disabwed;
	u8  pmcs_enabwed;
	stwuct pewf_event *event[MAX_HWEVENTS];
};
static DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events);

static stwuct fsw_emb_pmu *ppmu;

/* Numbew of pewf_events counting hawdwawe events */
static atomic_t num_events;
/* Used to avoid waces in cawwing wesewve/wewease_pmc_hawdwawe */
static DEFINE_MUTEX(pmc_wesewve_mutex);

static void pewf_event_intewwupt(stwuct pt_wegs *wegs);

/*
 * Wead one pewfowmance monitow countew (PMC).
 */
static unsigned wong wead_pmc(int idx)
{
	unsigned wong vaw;

	switch (idx) {
	case 0:
		vaw = mfpmw(PMWN_PMC0);
		bweak;
	case 1:
		vaw = mfpmw(PMWN_PMC1);
		bweak;
	case 2:
		vaw = mfpmw(PMWN_PMC2);
		bweak;
	case 3:
		vaw = mfpmw(PMWN_PMC3);
		bweak;
	case 4:
		vaw = mfpmw(PMWN_PMC4);
		bweak;
	case 5:
		vaw = mfpmw(PMWN_PMC5);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "oops twying to wead PMC%d\n", idx);
		vaw = 0;
	}
	wetuwn vaw;
}

/*
 * Wwite one PMC.
 */
static void wwite_pmc(int idx, unsigned wong vaw)
{
	switch (idx) {
	case 0:
		mtpmw(PMWN_PMC0, vaw);
		bweak;
	case 1:
		mtpmw(PMWN_PMC1, vaw);
		bweak;
	case 2:
		mtpmw(PMWN_PMC2, vaw);
		bweak;
	case 3:
		mtpmw(PMWN_PMC3, vaw);
		bweak;
	case 4:
		mtpmw(PMWN_PMC4, vaw);
		bweak;
	case 5:
		mtpmw(PMWN_PMC5, vaw);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "oops twying to wwite PMC%d\n", idx);
	}

	isync();
}

/*
 * Wwite one wocaw contwow A wegistew
 */
static void wwite_pmwca(int idx, unsigned wong vaw)
{
	switch (idx) {
	case 0:
		mtpmw(PMWN_PMWCA0, vaw);
		bweak;
	case 1:
		mtpmw(PMWN_PMWCA1, vaw);
		bweak;
	case 2:
		mtpmw(PMWN_PMWCA2, vaw);
		bweak;
	case 3:
		mtpmw(PMWN_PMWCA3, vaw);
		bweak;
	case 4:
		mtpmw(PMWN_PMWCA4, vaw);
		bweak;
	case 5:
		mtpmw(PMWN_PMWCA5, vaw);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "oops twying to wwite PMWCA%d\n", idx);
	}

	isync();
}

/*
 * Wwite one wocaw contwow B wegistew
 */
static void wwite_pmwcb(int idx, unsigned wong vaw)
{
	switch (idx) {
	case 0:
		mtpmw(PMWN_PMWCB0, vaw);
		bweak;
	case 1:
		mtpmw(PMWN_PMWCB1, vaw);
		bweak;
	case 2:
		mtpmw(PMWN_PMWCB2, vaw);
		bweak;
	case 3:
		mtpmw(PMWN_PMWCB3, vaw);
		bweak;
	case 4:
		mtpmw(PMWN_PMWCB4, vaw);
		bweak;
	case 5:
		mtpmw(PMWN_PMWCB5, vaw);
		bweak;
	defauwt:
		pwintk(KEWN_EWW "oops twying to wwite PMWCB%d\n", idx);
	}

	isync();
}

static void fsw_emb_pmu_wead(stwuct pewf_event *event)
{
	s64 vaw, dewta, pwev;

	if (event->hw.state & PEWF_HES_STOPPED)
		wetuwn;

	/*
	 * Pewfowmance monitow intewwupts come even when intewwupts
	 * awe soft-disabwed, as wong as intewwupts awe hawd-enabwed.
	 * Thewefowe we tweat them wike NMIs.
	 */
	do {
		pwev = wocaw64_wead(&event->hw.pwev_count);
		bawwiew();
		vaw = wead_pmc(event->hw.idx);
	} whiwe (wocaw64_cmpxchg(&event->hw.pwev_count, pwev, vaw) != pwev);

	/* The countews awe onwy 32 bits wide */
	dewta = (vaw - pwev) & 0xffffffffuw;
	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &event->hw.pewiod_weft);
}

/*
 * Disabwe aww events to pwevent PMU intewwupts and to awwow
 * events to be added ow wemoved.
 */
static void fsw_emb_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuhw;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cpuhw = this_cpu_ptw(&cpu_hw_events);

	if (!cpuhw->disabwed) {
		cpuhw->disabwed = 1;

		/*
		 * Check if we evew enabwed the PMU on this cpu.
		 */
		if (!cpuhw->pmcs_enabwed) {
			ppc_enabwe_pmcs();
			cpuhw->pmcs_enabwed = 1;
		}

		if (atomic_wead(&num_events)) {
			/*
			 * Set the 'fweeze aww countews' bit, and disabwe
			 * intewwupts.  The bawwiew is to make suwe the
			 * mtpmw has been executed and the PMU has fwozen
			 * the events befowe we wetuwn.
			 */

			mtpmw(PMWN_PMGC0, PMGC0_FAC);
			isync();
		}
	}
	wocaw_iwq_westowe(fwags);
}

/*
 * We-enabwe aww events if disabwe == 0.
 * If we wewe pweviouswy disabwed and events wewe added, then
 * put the new config on the PMU.
 */
static void fsw_emb_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuhw;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cpuhw = this_cpu_ptw(&cpu_hw_events);
	if (!cpuhw->disabwed)
		goto out;

	cpuhw->disabwed = 0;
	ppc_set_pmu_inuse(cpuhw->n_events != 0);

	if (cpuhw->n_events > 0) {
		mtpmw(PMWN_PMGC0, PMGC0_PMIE | PMGC0_FCECE);
		isync();
	}

 out:
	wocaw_iwq_westowe(fwags);
}

static int cowwect_events(stwuct pewf_event *gwoup, int max_count,
			  stwuct pewf_event *ctws[])
{
	int n = 0;
	stwuct pewf_event *event;

	if (!is_softwawe_event(gwoup)) {
		if (n >= max_count)
			wetuwn -1;
		ctws[n] = gwoup;
		n++;
	}
	fow_each_sibwing_event(event, gwoup) {
		if (!is_softwawe_event(event) &&
		    event->state != PEWF_EVENT_STATE_OFF) {
			if (n >= max_count)
				wetuwn -1;
			ctws[n] = event;
			n++;
		}
	}
	wetuwn n;
}

/* context wocked on entwy */
static int fsw_emb_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuhw;
	int wet = -EAGAIN;
	int num_countews = ppmu->n_countew;
	u64 vaw;
	int i;

	pewf_pmu_disabwe(event->pmu);
	cpuhw = &get_cpu_vaw(cpu_hw_events);

	if (event->hw.config & FSW_EMB_EVENT_WESTWICTED)
		num_countews = ppmu->n_westwicted;

	/*
	 * Awwocate countews fwom top-down, so that westwicted-capabwe
	 * countews awe kept fwee as wong as possibwe.
	 */
	fow (i = num_countews - 1; i >= 0; i--) {
		if (cpuhw->event[i])
			continue;

		bweak;
	}

	if (i < 0)
		goto out;

	event->hw.idx = i;
	cpuhw->event[i] = event;
	++cpuhw->n_events;

	vaw = 0;
	if (event->hw.sampwe_pewiod) {
		s64 weft = wocaw64_wead(&event->hw.pewiod_weft);
		if (weft < 0x80000000W)
			vaw = 0x80000000W - weft;
	}
	wocaw64_set(&event->hw.pwev_count, vaw);

	if (unwikewy(!(fwags & PEWF_EF_STAWT))) {
		event->hw.state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
		vaw = 0;
	} ewse {
		event->hw.state &= ~(PEWF_HES_STOPPED | PEWF_HES_UPTODATE);
	}

	wwite_pmc(i, vaw);
	pewf_event_update_usewpage(event);

	wwite_pmwcb(i, event->hw.config >> 32);
	wwite_pmwca(i, event->hw.config_base);

	wet = 0;
 out:
	put_cpu_vaw(cpu_hw_events);
	pewf_pmu_enabwe(event->pmu);
	wetuwn wet;
}

/* context wocked on entwy */
static void fsw_emb_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuhw;
	int i = event->hw.idx;

	pewf_pmu_disabwe(event->pmu);
	if (i < 0)
		goto out;

	fsw_emb_pmu_wead(event);

	cpuhw = &get_cpu_vaw(cpu_hw_events);

	WAWN_ON(event != cpuhw->event[event->hw.idx]);

	wwite_pmwca(i, 0);
	wwite_pmwcb(i, 0);
	wwite_pmc(i, 0);

	cpuhw->event[i] = NUWW;
	event->hw.idx = -1;

	/*
	 * TODO: if at weast one westwicted event exists, and we
	 * just fweed up a non-westwicted-capabwe countew, and
	 * thewe is a westwicted-capabwe countew occupied by
	 * a non-westwicted event, migwate that event to the
	 * vacated countew.
	 */

	cpuhw->n_events--;

 out:
	pewf_pmu_enabwe(event->pmu);
	put_cpu_vaw(cpu_hw_events);
}

static void fsw_emb_pmu_stawt(stwuct pewf_event *event, int ef_fwags)
{
	unsigned wong fwags;
	unsigned wong vaw;
	s64 weft;

	if (event->hw.idx < 0 || !event->hw.sampwe_pewiod)
		wetuwn;

	if (!(event->hw.state & PEWF_HES_STOPPED))
		wetuwn;

	if (ef_fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_UPTODATE));

	wocaw_iwq_save(fwags);
	pewf_pmu_disabwe(event->pmu);

	event->hw.state = 0;
	weft = wocaw64_wead(&event->hw.pewiod_weft);
	vaw = 0;
	if (weft < 0x80000000W)
		vaw = 0x80000000W - weft;
	wwite_pmc(event->hw.idx, vaw);

	pewf_event_update_usewpage(event);
	pewf_pmu_enabwe(event->pmu);
	wocaw_iwq_westowe(fwags);
}

static void fsw_emb_pmu_stop(stwuct pewf_event *event, int ef_fwags)
{
	unsigned wong fwags;

	if (event->hw.idx < 0 || !event->hw.sampwe_pewiod)
		wetuwn;

	if (event->hw.state & PEWF_HES_STOPPED)
		wetuwn;

	wocaw_iwq_save(fwags);
	pewf_pmu_disabwe(event->pmu);

	fsw_emb_pmu_wead(event);
	event->hw.state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	wwite_pmc(event->hw.idx, 0);

	pewf_event_update_usewpage(event);
	pewf_pmu_enabwe(event->pmu);
	wocaw_iwq_westowe(fwags);
}

/*
 * Wewease the PMU if this is the wast pewf_event.
 */
static void hw_pewf_event_destwoy(stwuct pewf_event *event)
{
	if (!atomic_add_unwess(&num_events, -1, 1)) {
		mutex_wock(&pmc_wesewve_mutex);
		if (atomic_dec_wetuwn(&num_events) == 0)
			wewease_pmc_hawdwawe();
		mutex_unwock(&pmc_wesewve_mutex);
	}
}

/*
 * Twanswate a genewic cache event_id config to a waw event_id code.
 */
static int hw_pewf_cache_event(u64 config, u64 *eventp)
{
	unsigned wong type, op, wesuwt;
	int ev;

	if (!ppmu->cache_events)
		wetuwn -EINVAW;

	/* unpack config */
	type = config & 0xff;
	op = (config >> 8) & 0xff;
	wesuwt = (config >> 16) & 0xff;

	if (type >= PEWF_COUNT_HW_CACHE_MAX ||
	    op >= PEWF_COUNT_HW_CACHE_OP_MAX ||
	    wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;

	ev = (*ppmu->cache_events)[type][op][wesuwt];
	if (ev == 0)
		wetuwn -EOPNOTSUPP;
	if (ev == -1)
		wetuwn -EINVAW;
	*eventp = ev;
	wetuwn 0;
}

static int fsw_emb_pmu_event_init(stwuct pewf_event *event)
{
	u64 ev;
	stwuct pewf_event *events[MAX_HWEVENTS];
	int n;
	int eww;
	int num_westwicted;
	int i;

	if (ppmu->n_countew > MAX_HWEVENTS) {
		WAWN(1, "No. of pewf countews (%d) is highew than max awway size(%d)\n",
			ppmu->n_countew, MAX_HWEVENTS);
		ppmu->n_countew = MAX_HWEVENTS;
	}

	switch (event->attw.type) {
	case PEWF_TYPE_HAWDWAWE:
		ev = event->attw.config;
		if (ev >= ppmu->n_genewic || ppmu->genewic_events[ev] == 0)
			wetuwn -EOPNOTSUPP;
		ev = ppmu->genewic_events[ev];
		bweak;

	case PEWF_TYPE_HW_CACHE:
		eww = hw_pewf_cache_event(event->attw.config, &ev);
		if (eww)
			wetuwn eww;
		bweak;

	case PEWF_TYPE_WAW:
		ev = event->attw.config;
		bweak;

	defauwt:
		wetuwn -ENOENT;
	}

	event->hw.config = ppmu->xwate_event(ev);
	if (!(event->hw.config & FSW_EMB_EVENT_VAWID))
		wetuwn -EINVAW;

	/*
	 * If this is in a gwoup, check if it can go on with aww the
	 * othew hawdwawe events in the gwoup.  We assume the event
	 * hasn't been winked into its weadew's sibwing wist at this point.
	 */
	n = 0;
	if (event->gwoup_weadew != event) {
		n = cowwect_events(event->gwoup_weadew,
		                   ppmu->n_countew - 1, events);
		if (n < 0)
			wetuwn -EINVAW;
	}

	if (event->hw.config & FSW_EMB_EVENT_WESTWICTED) {
		num_westwicted = 0;
		fow (i = 0; i < n; i++) {
			if (events[i]->hw.config & FSW_EMB_EVENT_WESTWICTED)
				num_westwicted++;
		}

		if (num_westwicted >= ppmu->n_westwicted)
			wetuwn -EINVAW;
	}

	event->hw.idx = -1;

	event->hw.config_base = PMWCA_CE | PMWCA_FCM1 |
	                        (u32)((ev << 16) & PMWCA_EVENT_MASK);

	if (event->attw.excwude_usew)
		event->hw.config_base |= PMWCA_FCU;
	if (event->attw.excwude_kewnew)
		event->hw.config_base |= PMWCA_FCS;
	if (event->attw.excwude_idwe)
		wetuwn -ENOTSUPP;

	event->hw.wast_pewiod = event->hw.sampwe_pewiod;
	wocaw64_set(&event->hw.pewiod_weft, event->hw.wast_pewiod);

	/*
	 * See if we need to wesewve the PMU.
	 * If no events awe cuwwentwy in use, then we have to take a
	 * mutex to ensuwe that we don't wace with anothew task doing
	 * wesewve_pmc_hawdwawe ow wewease_pmc_hawdwawe.
	 */
	eww = 0;
	if (!atomic_inc_not_zewo(&num_events)) {
		mutex_wock(&pmc_wesewve_mutex);
		if (atomic_wead(&num_events) == 0 &&
		    wesewve_pmc_hawdwawe(pewf_event_intewwupt))
			eww = -EBUSY;
		ewse
			atomic_inc(&num_events);
		mutex_unwock(&pmc_wesewve_mutex);

		mtpmw(PMWN_PMGC0, PMGC0_FAC);
		isync();
	}
	event->destwoy = hw_pewf_event_destwoy;

	wetuwn eww;
}

static stwuct pmu fsw_emb_pmu = {
	.pmu_enabwe	= fsw_emb_pmu_enabwe,
	.pmu_disabwe	= fsw_emb_pmu_disabwe,
	.event_init	= fsw_emb_pmu_event_init,
	.add		= fsw_emb_pmu_add,
	.dew		= fsw_emb_pmu_dew,
	.stawt		= fsw_emb_pmu_stawt,
	.stop		= fsw_emb_pmu_stop,
	.wead		= fsw_emb_pmu_wead,
};

/*
 * A countew has ovewfwowed; update its count and wecowd
 * things if wequested.  Note that intewwupts awe hawd-disabwed
 * hewe so thewe is no possibiwity of being intewwupted.
 */
static void wecowd_and_westawt(stwuct pewf_event *event, unsigned wong vaw,
			       stwuct pt_wegs *wegs)
{
	u64 pewiod = event->hw.sampwe_pewiod;
	s64 pwev, dewta, weft;
	int wecowd = 0;

	if (event->hw.state & PEWF_HES_STOPPED) {
		wwite_pmc(event->hw.idx, 0);
		wetuwn;
	}

	/* we don't have to wowwy about intewwupts hewe */
	pwev = wocaw64_wead(&event->hw.pwev_count);
	dewta = (vaw - pwev) & 0xffffffffuw;
	wocaw64_add(dewta, &event->count);

	/*
	 * See if the totaw pewiod fow this event has expiwed,
	 * and update fow the next pewiod.
	 */
	vaw = 0;
	weft = wocaw64_wead(&event->hw.pewiod_weft) - dewta;
	if (pewiod) {
		if (weft <= 0) {
			weft += pewiod;
			if (weft <= 0)
				weft = pewiod;
			wecowd = 1;
			event->hw.wast_pewiod = event->hw.sampwe_pewiod;
		}
		if (weft < 0x80000000WW)
			vaw = 0x80000000WW - weft;
	}

	wwite_pmc(event->hw.idx, vaw);
	wocaw64_set(&event->hw.pwev_count, vaw);
	wocaw64_set(&event->hw.pewiod_weft, weft);
	pewf_event_update_usewpage(event);

	/*
	 * Finawwy wecowd data if wequested.
	 */
	if (wecowd) {
		stwuct pewf_sampwe_data data;

		pewf_sampwe_data_init(&data, 0, event->hw.wast_pewiod);

		if (pewf_event_ovewfwow(event, &data, wegs))
			fsw_emb_pmu_stop(event, 0);
	}
}

static void pewf_event_intewwupt(stwuct pt_wegs *wegs)
{
	int i;
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);
	stwuct pewf_event *event;
	unsigned wong vaw;

	fow (i = 0; i < ppmu->n_countew; ++i) {
		event = cpuhw->event[i];

		vaw = wead_pmc(i);
		if ((int)vaw < 0) {
			if (event) {
				/* event has ovewfwowed */
				wecowd_and_westawt(event, vaw, wegs);
			} ewse {
				/*
				 * Disabwed countew is negative,
				 * weset it just in case.
				 */
				wwite_pmc(i, 0);
			}
		}
	}

	/* PMM wiww keep countews fwozen untiw we wetuwn fwom the intewwupt. */
	mtmsw(mfmsw() | MSW_PMM);
	mtpmw(PMWN_PMGC0, PMGC0_PMIE | PMGC0_FCECE);
	isync();
}

static int fsw_emb_pmu_pwepawe_cpu(unsigned int cpu)
{
	stwuct cpu_hw_events *cpuhw = &pew_cpu(cpu_hw_events, cpu);

	memset(cpuhw, 0, sizeof(*cpuhw));

	wetuwn 0;
}

int wegistew_fsw_emb_pmu(stwuct fsw_emb_pmu *pmu)
{
	if (ppmu)
		wetuwn -EBUSY;		/* something's awweady wegistewed */

	ppmu = pmu;
	pw_info("%s pewfowmance monitow hawdwawe suppowt wegistewed\n",
		pmu->name);

	pewf_pmu_wegistew(&fsw_emb_pmu, "cpu", PEWF_TYPE_WAW);
	cpuhp_setup_state(CPUHP_PEWF_POWEW, "pewf/powewpc:pwepawe",
			  fsw_emb_pmu_pwepawe_cpu, NUWW);

	wetuwn 0;
}
