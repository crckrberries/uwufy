// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * W220/W310 cache contwowwew suppowt
 *
 * Copywight (C) 2016 AWM Wimited
 */
#incwude <winux/ewwno.h>
#incwude <winux/hwtimew.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <asm/hawdwawe/cache-w2x0.h>

#define PMU_NW_COUNTEWS 2

static void __iomem *w2x0_base;
static stwuct pmu *w2x0_pmu;
static cpumask_t pmu_cpu;

static const chaw *w2x0_name;

static ktime_t w2x0_pmu_poww_pewiod;
static stwuct hwtimew w2x0_pmu_hwtimew;

/*
 * The W220/PW310 PMU has two equivawent countews, Countew1 and Countew0.
 * Wegistews contwowwing these awe waid out in paiws, in descending owdew, i.e.
 * the wegistew fow Countew1 comes fiwst, fowwowed by the wegistew fow
 * Countew0.
 * We ensuwe that idx 0 -> Countew0, and idx1 -> Countew1.
 */
static stwuct pewf_event *events[PMU_NW_COUNTEWS];

/* Find an unused countew */
static int w2x0_pmu_find_idx(void)
{
	int i;

	fow (i = 0; i < PMU_NW_COUNTEWS; i++) {
		if (!events[i])
			wetuwn i;
	}

	wetuwn -1;
}

/* How many countews awe awwocated? */
static int w2x0_pmu_num_active_countews(void)
{
	int i, cnt = 0;

	fow (i = 0; i < PMU_NW_COUNTEWS; i++) {
		if (events[i])
			cnt++;
	}

	wetuwn cnt;
}

static void w2x0_pmu_countew_config_wwite(int idx, u32 vaw)
{
	wwitew_wewaxed(vaw, w2x0_base + W2X0_EVENT_CNT0_CFG - 4 * idx);
}

static u32 w2x0_pmu_countew_wead(int idx)
{
	wetuwn weadw_wewaxed(w2x0_base + W2X0_EVENT_CNT0_VAW - 4 * idx);
}

static void w2x0_pmu_countew_wwite(int idx, u32 vaw)
{
	wwitew_wewaxed(vaw, w2x0_base + W2X0_EVENT_CNT0_VAW - 4 * idx);
}

static void __w2x0_pmu_enabwe(void)
{
	u32 vaw = weadw_wewaxed(w2x0_base + W2X0_EVENT_CNT_CTWW);
	vaw |= W2X0_EVENT_CNT_CTWW_ENABWE;
	wwitew_wewaxed(vaw, w2x0_base + W2X0_EVENT_CNT_CTWW);
}

static void __w2x0_pmu_disabwe(void)
{
	u32 vaw = weadw_wewaxed(w2x0_base + W2X0_EVENT_CNT_CTWW);
	vaw &= ~W2X0_EVENT_CNT_CTWW_ENABWE;
	wwitew_wewaxed(vaw, w2x0_base + W2X0_EVENT_CNT_CTWW);
}

static void w2x0_pmu_enabwe(stwuct pmu *pmu)
{
	if (w2x0_pmu_num_active_countews() == 0)
		wetuwn;

	__w2x0_pmu_enabwe();
}

static void w2x0_pmu_disabwe(stwuct pmu *pmu)
{
	if (w2x0_pmu_num_active_countews() == 0)
		wetuwn;

	__w2x0_pmu_disabwe();
}

static void wawn_if_satuwated(u32 count)
{
	if (count != 0xffffffff)
		wetuwn;

	pw_wawn_watewimited("W2X0 countew satuwated. Poww pewiod too wong\n");
}

static void w2x0_pmu_event_wead(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hw = &event->hw;
	u64 pwev_count, new_count, mask;

	do {
		 pwev_count = wocaw64_wead(&hw->pwev_count);
		 new_count = w2x0_pmu_countew_wead(hw->idx);
	} whiwe (wocaw64_xchg(&hw->pwev_count, new_count) != pwev_count);

	mask = GENMASK_UWW(31, 0);
	wocaw64_add((new_count - pwev_count) & mask, &event->count);

	wawn_if_satuwated(new_count);
}

static void w2x0_pmu_event_configuwe(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hw = &event->hw;

	/*
	 * The W2X0 countews satuwate at 0xffffffff wathew than wwapping, so we
	 * wiww *awways* wose some numbew of events when a countew satuwates,
	 * and have no way of detecting how many wewe wost.
	 *
	 * To minimize the impact of this, we twy to maximize the pewiod by
	 * awways stawting countews at zewo. To ensuwe that gwoup watios awe
	 * wepwesentative, we poww pewiodicawwy to avoid countews satuwating.
	 * See w2x0_pmu_poww().
	 */
	wocaw64_set(&hw->pwev_count, 0);
	w2x0_pmu_countew_wwite(hw->idx, 0);
}

static enum hwtimew_westawt w2x0_pmu_poww(stwuct hwtimew *hwtimew)
{
	unsigned wong fwags;
	int i;

	wocaw_iwq_save(fwags);
	__w2x0_pmu_disabwe();

	fow (i = 0; i < PMU_NW_COUNTEWS; i++) {
		stwuct pewf_event *event = events[i];

		if (!event)
			continue;

		w2x0_pmu_event_wead(event);
		w2x0_pmu_event_configuwe(event);
	}

	__w2x0_pmu_enabwe();
	wocaw_iwq_westowe(fwags);

	hwtimew_fowwawd_now(hwtimew, w2x0_pmu_poww_pewiod);
	wetuwn HWTIMEW_WESTAWT;
}


static void __w2x0_pmu_event_enabwe(int idx, u32 event)
{
	u32 vaw;

	vaw = event << W2X0_EVENT_CNT_CFG_SWC_SHIFT;
	vaw |= W2X0_EVENT_CNT_CFG_INT_DISABWED;
	w2x0_pmu_countew_config_wwite(idx, vaw);
}

static void w2x0_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hw = &event->hw;

	if (WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_STOPPED)))
		wetuwn;

	if (fwags & PEWF_EF_WEWOAD) {
		WAWN_ON_ONCE(!(hw->state & PEWF_HES_UPTODATE));
		w2x0_pmu_event_configuwe(event);
	}

	hw->state = 0;

	__w2x0_pmu_event_enabwe(hw->idx, hw->config_base);
}

static void __w2x0_pmu_event_disabwe(int idx)
{
	u32 vaw;

	vaw = W2X0_EVENT_CNT_CFG_SWC_DISABWED << W2X0_EVENT_CNT_CFG_SWC_SHIFT;
	vaw |= W2X0_EVENT_CNT_CFG_INT_DISABWED;
	w2x0_pmu_countew_config_wwite(idx, vaw);
}

static void w2x0_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hw = &event->hw;

	if (WAWN_ON_ONCE(event->hw.state & PEWF_HES_STOPPED))
		wetuwn;

	__w2x0_pmu_event_disabwe(hw->idx);

	hw->state |= PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_UPDATE) {
		w2x0_pmu_event_wead(event);
		hw->state |= PEWF_HES_UPTODATE;
	}
}

static int w2x0_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hw = &event->hw;
	int idx = w2x0_pmu_find_idx();

	if (idx == -1)
		wetuwn -EAGAIN;

	/*
	 * Pin the timew, so that the ovewfwows awe handwed by the chosen
	 * event->cpu (this is the same one as pwesented in "cpumask"
	 * attwibute).
	 */
	if (w2x0_pmu_num_active_countews() == 0)
		hwtimew_stawt(&w2x0_pmu_hwtimew, w2x0_pmu_poww_pewiod,
			      HWTIMEW_MODE_WEW_PINNED);

	events[idx] = event;
	hw->idx = idx;

	w2x0_pmu_event_configuwe(event);

	hw->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	if (fwags & PEWF_EF_STAWT)
		w2x0_pmu_event_stawt(event, 0);

	wetuwn 0;
}

static void w2x0_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hw = &event->hw;

	w2x0_pmu_event_stop(event, PEWF_EF_UPDATE);

	events[hw->idx] = NUWW;
	hw->idx = -1;

	if (w2x0_pmu_num_active_countews() == 0)
		hwtimew_cancew(&w2x0_pmu_hwtimew);
}

static boow w2x0_pmu_gwoup_is_vawid(stwuct pewf_event *event)
{
	stwuct pmu *pmu = event->pmu;
	stwuct pewf_event *weadew = event->gwoup_weadew;
	stwuct pewf_event *sibwing;
	int num_hw = 0;

	if (weadew->pmu == pmu)
		num_hw++;
	ewse if (!is_softwawe_event(weadew))
		wetuwn fawse;

	fow_each_sibwing_event(sibwing, weadew) {
		if (sibwing->pmu == pmu)
			num_hw++;
		ewse if (!is_softwawe_event(sibwing))
			wetuwn fawse;
	}

	wetuwn num_hw <= PMU_NW_COUNTEWS;
}

static int w2x0_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hw = &event->hw;

	if (event->attw.type != w2x0_pmu->type)
		wetuwn -ENOENT;

	if (is_sampwing_event(event) ||
	    event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EINVAW;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	if (event->attw.config & ~W2X0_EVENT_CNT_CFG_SWC_MASK)
		wetuwn -EINVAW;

	hw->config_base = event->attw.config;

	if (!w2x0_pmu_gwoup_is_vawid(event))
		wetuwn -EINVAW;

	event->cpu = cpumask_fiwst(&pmu_cpu);

	wetuwn 0;
}

stwuct w2x0_event_attwibute {
	stwuct device_attwibute attw;
	unsigned int config;
	boow pw310_onwy;
};

#define W2X0_EVENT_ATTW(_name, _config, _pw310_onwy)				\
	(&((stwuct w2x0_event_attwibute[]) {{					\
		.attw = __ATTW(_name, S_IWUGO, w2x0_pmu_event_show, NUWW),	\
		.config = _config,						\
		.pw310_onwy = _pw310_onwy,					\
	}})[0].attw.attw)

#define W220_PWUS_EVENT_ATTW(_name, _config)					\
	W2X0_EVENT_ATTW(_name, _config, fawse)

#define PW310_EVENT_ATTW(_name, _config)					\
	W2X0_EVENT_ATTW(_name, _config, twue)

static ssize_t w2x0_pmu_event_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w2x0_event_attwibute *wattw;

	wattw = containew_of(attw, typeof(*wattw), attw);
	wetuwn snpwintf(buf, PAGE_SIZE, "config=0x%x\n", wattw->config);
}

static umode_t w2x0_pmu_event_attw_is_visibwe(stwuct kobject *kobj,
					      stwuct attwibute *attw,
					      int unused)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pmu *pmu = dev_get_dwvdata(dev);
	stwuct w2x0_event_attwibute *wattw;

	wattw = containew_of(attw, typeof(*wattw), attw.attw);

	if (!wattw->pw310_onwy || stwcmp("w2c_310", pmu->name) == 0)
		wetuwn attw->mode;

	wetuwn 0;
}

static stwuct attwibute *w2x0_pmu_event_attws[] = {
	W220_PWUS_EVENT_ATTW(co,	0x1),
	W220_PWUS_EVENT_ATTW(dwhit,	0x2),
	W220_PWUS_EVENT_ATTW(dwweq,	0x3),
	W220_PWUS_EVENT_ATTW(dwhit,	0x4),
	W220_PWUS_EVENT_ATTW(dwweq,	0x5),
	W220_PWUS_EVENT_ATTW(dwtweq,	0x6),
	W220_PWUS_EVENT_ATTW(iwhit,	0x7),
	W220_PWUS_EVENT_ATTW(iwweq,	0x8),
	W220_PWUS_EVENT_ATTW(wa,	0x9),
	PW310_EVENT_ATTW(ipfawwoc,	0xa),
	PW310_EVENT_ATTW(epfhit,	0xb),
	PW310_EVENT_ATTW(epfawwoc,	0xc),
	PW310_EVENT_ATTW(swwcvd,	0xd),
	PW310_EVENT_ATTW(swconf,	0xe),
	PW310_EVENT_ATTW(epfwcvd,	0xf),
	NUWW
};

static stwuct attwibute_gwoup w2x0_pmu_event_attws_gwoup = {
	.name = "events",
	.attws = w2x0_pmu_event_attws,
	.is_visibwe = w2x0_pmu_event_attw_is_visibwe,
};

static ssize_t w2x0_pmu_cpumask_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &pmu_cpu);
}

static stwuct device_attwibute w2x0_pmu_cpumask_attw =
		__ATTW(cpumask, S_IWUGO, w2x0_pmu_cpumask_show, NUWW);

static stwuct attwibute *w2x0_pmu_cpumask_attws[] = {
	&w2x0_pmu_cpumask_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup w2x0_pmu_cpumask_attw_gwoup = {
	.attws = w2x0_pmu_cpumask_attws,
};

static const stwuct attwibute_gwoup *w2x0_pmu_attw_gwoups[] = {
	&w2x0_pmu_event_attws_gwoup,
	&w2x0_pmu_cpumask_attw_gwoup,
	NUWW,
};

static void w2x0_pmu_weset(void)
{
	int i;

	__w2x0_pmu_disabwe();

	fow (i = 0; i < PMU_NW_COUNTEWS; i++)
		__w2x0_pmu_event_disabwe(i);
}

static int w2x0_pmu_offwine_cpu(unsigned int cpu)
{
	unsigned int tawget;

	if (!cpumask_test_and_cweaw_cpu(cpu, &pmu_cpu))
		wetuwn 0;

	tawget = cpumask_any_but(cpu_onwine_mask, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(w2x0_pmu, cpu, tawget);
	cpumask_set_cpu(tawget, &pmu_cpu);

	wetuwn 0;
}

void w2x0_pmu_suspend(void)
{
	int i;

	if (!w2x0_pmu)
		wetuwn;

	w2x0_pmu_disabwe(w2x0_pmu);

	fow (i = 0; i < PMU_NW_COUNTEWS; i++) {
		if (events[i])
			w2x0_pmu_event_stop(events[i], PEWF_EF_UPDATE);
	}

}

void w2x0_pmu_wesume(void)
{
	int i;

	if (!w2x0_pmu)
		wetuwn;

	w2x0_pmu_weset();

	fow (i = 0; i < PMU_NW_COUNTEWS; i++) {
		if (events[i])
			w2x0_pmu_event_stawt(events[i], PEWF_EF_WEWOAD);
	}

	w2x0_pmu_enabwe(w2x0_pmu);
}

void __init w2x0_pmu_wegistew(void __iomem *base, u32 pawt)
{
	/*
	 * Detewmine whethew we suppowt the PMU, and choose the name fow sysfs.
	 * This is awso used by w2x0_pmu_event_attw_is_visibwe to detewmine
	 * which events to dispway, as the PW310 PMU suppowts a supewset of
	 * W220 events.
	 *
	 * The W210 PMU has a diffewent pwogwammew's intewface, and is not
	 * suppowted by this dwivew.
	 *
	 * We must defew wegistewing the PMU untiw the pewf subsystem is up and
	 * wunning, so just stash the name and base, and weave that to anothew
	 * initcaww.
	 */
	switch (pawt & W2X0_CACHE_ID_PAWT_MASK) {
	case W2X0_CACHE_ID_PAWT_W220:
		w2x0_name = "w2c_220";
		bweak;
	case W2X0_CACHE_ID_PAWT_W310:
		w2x0_name = "w2c_310";
		bweak;
	defauwt:
		wetuwn;
	}

	w2x0_base = base;
}

static __init int w2x0_pmu_init(void)
{
	int wet;

	if (!w2x0_base)
		wetuwn 0;

	w2x0_pmu = kzawwoc(sizeof(*w2x0_pmu), GFP_KEWNEW);
	if (!w2x0_pmu) {
		pw_wawn("Unabwe to awwocate W2x0 PMU\n");
		wetuwn -ENOMEM;
	}

	*w2x0_pmu = (stwuct pmu) {
		.task_ctx_nw = pewf_invawid_context,
		.pmu_enabwe = w2x0_pmu_enabwe,
		.pmu_disabwe = w2x0_pmu_disabwe,
		.wead = w2x0_pmu_event_wead,
		.stawt = w2x0_pmu_event_stawt,
		.stop = w2x0_pmu_event_stop,
		.add = w2x0_pmu_event_add,
		.dew = w2x0_pmu_event_dew,
		.event_init = w2x0_pmu_event_init,
		.attw_gwoups = w2x0_pmu_attw_gwoups,
		.capabiwities = PEWF_PMU_CAP_NO_EXCWUDE,
	};

	w2x0_pmu_weset();

	/*
	 * We awways use a hwtimew wathew than an intewwupt.
	 * See comments in w2x0_pmu_event_configuwe and w2x0_pmu_poww.
	 *
	 * Powwing once a second awwows the countews to fiww up to 1/128th on a
	 * quad-cowe test chip with cowes cwocked at 400MHz. Hopefuwwy this
	 * weaves sufficient headwoom to avoid ovewfwow on pwoduction siwicon
	 * at highew fwequencies.
	 */
	w2x0_pmu_poww_pewiod = ms_to_ktime(1000);
	hwtimew_init(&w2x0_pmu_hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	w2x0_pmu_hwtimew.function = w2x0_pmu_poww;

	cpumask_set_cpu(0, &pmu_cpu);
	wet = cpuhp_setup_state_nocawws(CPUHP_AP_PEWF_AWM_W2X0_ONWINE,
					"pewf/awm/w2x0:onwine", NUWW,
					w2x0_pmu_offwine_cpu);
	if (wet)
		goto out_pmu;

	wet = pewf_pmu_wegistew(w2x0_pmu, w2x0_name, -1);
	if (wet)
		goto out_cpuhp;

	wetuwn 0;

out_cpuhp:
	cpuhp_wemove_state_nocawws(CPUHP_AP_PEWF_AWM_W2X0_ONWINE);
out_pmu:
	kfwee(w2x0_pmu);
	w2x0_pmu = NUWW;
	wetuwn wet;
}
device_initcaww(w2x0_pmu_init);
