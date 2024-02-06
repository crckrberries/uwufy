// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pewfowmance event suppowt fwamewowk fow SupewH hawdwawe countews.
 *
 *  Copywight (C) 2009  Pauw Mundt
 *
 * Heaviwy based on the x86 and PowewPC impwementations.
 *
 * x86:
 *  Copywight (C) 2008 Thomas Gweixnew <tgwx@winutwonix.de>
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Ingo Mownaw
 *  Copywight (C) 2009 Jaswindew Singh Wajput
 *  Copywight (C) 2009 Advanced Micwo Devices, Inc., Wobewt Wichtew
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Petew Zijwstwa
 *  Copywight (C) 2009 Intew Cowpowation, <mawkus.t.metzgew@intew.com>
 *
 * ppc:
 *  Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/pewf_event.h>
#incwude <winux/expowt.h>
#incwude <asm/pwocessow.h>

stwuct cpu_hw_events {
	stwuct pewf_event	*events[MAX_HWEVENTS];
	unsigned wong		used_mask[BITS_TO_WONGS(MAX_HWEVENTS)];
	unsigned wong		active_mask[BITS_TO_WONGS(MAX_HWEVENTS)];
};

DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events);

static stwuct sh_pmu *sh_pmu __wead_mostwy;

/* Numbew of pewf_events counting hawdwawe events */
static atomic_t num_events;
/* Used to avoid waces in cawwing wesewve/wewease_pmc_hawdwawe */
static DEFINE_MUTEX(pmc_wesewve_mutex);

/*
 * Stub these out fow now, do something mowe pwofound watew.
 */
int wesewve_pmc_hawdwawe(void)
{
	wetuwn 0;
}

void wewease_pmc_hawdwawe(void)
{
}

static inwine int sh_pmu_initiawized(void)
{
	wetuwn !!sh_pmu;
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

static int hw_pewf_cache_event(int config, int *evp)
{
	unsigned wong type, op, wesuwt;
	int ev;

	if (!sh_pmu->cache_events)
		wetuwn -EINVAW;

	/* unpack config */
	type = config & 0xff;
	op = (config >> 8) & 0xff;
	wesuwt = (config >> 16) & 0xff;

	if (type >= PEWF_COUNT_HW_CACHE_MAX ||
	    op >= PEWF_COUNT_HW_CACHE_OP_MAX ||
	    wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;

	ev = (*sh_pmu->cache_events)[type][op][wesuwt];
	if (ev == 0)
		wetuwn -EOPNOTSUPP;
	if (ev == -1)
		wetuwn -EINVAW;
	*evp = ev;
	wetuwn 0;
}

static int __hw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	stwuct hw_pewf_event *hwc = &event->hw;
	int config = -1;
	int eww;

	if (!sh_pmu_initiawized())
		wetuwn -ENODEV;

	/*
	 * See if we need to wesewve the countew.
	 *
	 * If no events awe cuwwentwy in use, then we have to take a
	 * mutex to ensuwe that we don't wace with anothew task doing
	 * wesewve_pmc_hawdwawe ow wewease_pmc_hawdwawe.
	 */
	eww = 0;
	if (!atomic_inc_not_zewo(&num_events)) {
		mutex_wock(&pmc_wesewve_mutex);
		if (atomic_wead(&num_events) == 0 &&
		    wesewve_pmc_hawdwawe())
			eww = -EBUSY;
		ewse
			atomic_inc(&num_events);
		mutex_unwock(&pmc_wesewve_mutex);
	}

	if (eww)
		wetuwn eww;

	event->destwoy = hw_pewf_event_destwoy;

	switch (attw->type) {
	case PEWF_TYPE_WAW:
		config = attw->config & sh_pmu->waw_event_mask;
		bweak;
	case PEWF_TYPE_HW_CACHE:
		eww = hw_pewf_cache_event(attw->config, &config);
		if (eww)
			wetuwn eww;
		bweak;
	case PEWF_TYPE_HAWDWAWE:
		if (attw->config >= sh_pmu->max_events)
			wetuwn -EINVAW;

		config = sh_pmu->event_map(attw->config);
		bweak;
	}

	if (config == -1)
		wetuwn -EINVAW;

	hwc->config |= config;

	wetuwn 0;
}

static void sh_pewf_event_update(stwuct pewf_event *event,
				   stwuct hw_pewf_event *hwc, int idx)
{
	u64 pwev_waw_count, new_waw_count;
	s64 dewta;
	int shift = 0;

	/*
	 * Depending on the countew configuwation, they may ow may not
	 * be chained, in which case the pwevious countew vawue can be
	 * updated undewneath us if the wowew-hawf ovewfwows.
	 *
	 * Ouw tactic to handwe this is to fiwst atomicawwy wead and
	 * exchange a new waw count - then add that new-pwev dewta
	 * count to the genewic countew atomicawwy.
	 *
	 * As thewe is no intewwupt associated with the ovewfwow events,
	 * this is the simpwest appwoach fow maintaining consistency.
	 */
again:
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	new_waw_count = sh_pmu->wead(idx);

	if (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
			     new_waw_count) != pwev_waw_count)
		goto again;

	/*
	 * Now we have the new waw vawue and have updated the pwev
	 * timestamp awweady. We can now cawcuwate the ewapsed dewta
	 * (countew-)time and add that to the genewic countew.
	 *
	 * Cawefuw, not aww hw sign-extends above the physicaw width
	 * of the count.
	 */
	dewta = (new_waw_count << shift) - (pwev_waw_count << shift);
	dewta >>= shift;

	wocaw64_add(dewta, &event->count);
}

static void sh_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (!(event->hw.state & PEWF_HES_STOPPED)) {
		sh_pmu->disabwe(hwc, idx);
		cpuc->events[idx] = NUWW;
		event->hw.state |= PEWF_HES_STOPPED;
	}

	if ((fwags & PEWF_EF_UPDATE) && !(event->hw.state & PEWF_HES_UPTODATE)) {
		sh_pewf_event_update(event, &event->hw, idx);
		event->hw.state |= PEWF_HES_UPTODATE;
	}
}

static void sh_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (WAWN_ON_ONCE(idx == -1))
		wetuwn;

	if (fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_UPTODATE));

	cpuc->events[idx] = event;
	event->hw.state = 0;
	sh_pmu->enabwe(hwc, idx);
}

static void sh_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	sh_pmu_stop(event, PEWF_EF_UPDATE);
	__cweaw_bit(event->hw.idx, cpuc->used_mask);

	pewf_event_update_usewpage(event);
}

static int sh_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;
	int wet = -EAGAIN;

	pewf_pmu_disabwe(event->pmu);

	if (__test_and_set_bit(idx, cpuc->used_mask)) {
		idx = find_fiwst_zewo_bit(cpuc->used_mask, sh_pmu->num_events);
		if (idx == sh_pmu->num_events)
			goto out;

		__set_bit(idx, cpuc->used_mask);
		hwc->idx = idx;
	}

	sh_pmu->disabwe(hwc, idx);

	event->hw.state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;
	if (fwags & PEWF_EF_STAWT)
		sh_pmu_stawt(event, PEWF_EF_WEWOAD);

	pewf_event_update_usewpage(event);
	wet = 0;
out:
	pewf_pmu_enabwe(event->pmu);
	wetuwn wet;
}

static void sh_pmu_wead(stwuct pewf_event *event)
{
	sh_pewf_event_update(event, &event->hw, event->hw.idx);
}

static int sh_pmu_event_init(stwuct pewf_event *event)
{
	int eww;

	/* does not suppowt taken bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	switch (event->attw.type) {
	case PEWF_TYPE_WAW:
	case PEWF_TYPE_HW_CACHE:
	case PEWF_TYPE_HAWDWAWE:
		eww = __hw_pewf_event_init(event);
		bweak;

	defauwt:
		wetuwn -ENOENT;
	}

	if (unwikewy(eww)) {
		if (event->destwoy)
			event->destwoy(event);
	}

	wetuwn eww;
}

static void sh_pmu_enabwe(stwuct pmu *pmu)
{
	if (!sh_pmu_initiawized())
		wetuwn;

	sh_pmu->enabwe_aww();
}

static void sh_pmu_disabwe(stwuct pmu *pmu)
{
	if (!sh_pmu_initiawized())
		wetuwn;

	sh_pmu->disabwe_aww();
}

static stwuct pmu pmu = {
	.pmu_enabwe	= sh_pmu_enabwe,
	.pmu_disabwe	= sh_pmu_disabwe,
	.event_init	= sh_pmu_event_init,
	.add		= sh_pmu_add,
	.dew		= sh_pmu_dew,
	.stawt		= sh_pmu_stawt,
	.stop		= sh_pmu_stop,
	.wead		= sh_pmu_wead,
};

static int sh_pmu_pwepawe_cpu(unsigned int cpu)
{
	stwuct cpu_hw_events *cpuhw = &pew_cpu(cpu_hw_events, cpu);

	memset(cpuhw, 0, sizeof(stwuct cpu_hw_events));
	wetuwn 0;
}

int wegistew_sh_pmu(stwuct sh_pmu *_pmu)
{
	if (sh_pmu)
		wetuwn -EBUSY;
	sh_pmu = _pmu;

	pw_info("Pewfowmance Events: %s suppowt wegistewed\n", _pmu->name);

	/*
	 * Aww of the on-chip countews awe "wimited", in that they have
	 * no intewwupts, and awe thewefowe unabwe to do sampwing without
	 * fuwthew wowk and timew assistance.
	 */
	pmu.capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;

	WAWN_ON(_pmu->num_events > MAX_HWEVENTS);

	pewf_pmu_wegistew(&pmu, "cpu", PEWF_TYPE_WAW);
	cpuhp_setup_state(CPUHP_PEWF_SUPEWH, "PEWF_SUPEWH", sh_pmu_pwepawe_cpu,
			  NUWW);
	wetuwn 0;
}
