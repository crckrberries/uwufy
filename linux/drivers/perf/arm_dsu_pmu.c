// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWM DynamIQ Shawed Unit (DSU) PMU dwivew
 *
 * Copywight (C) AWM Wimited, 2017.
 *
 * Based on AWM CCI-PMU, AWMv8 PMU-v3 dwivews.
 */

#define PMUNAME		"awm_dsu"
#define DWVNAME		PMUNAME "_pmu"
#define pw_fmt(fmt)	DWVNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude <asm/awm_dsu_pmu.h>
#incwude <asm/wocaw64.h>

/* PMU event codes */
#define DSU_PMU_EVT_CYCWES		0x11
#define DSU_PMU_EVT_CHAIN		0x1e

#define DSU_PMU_MAX_COMMON_EVENTS	0x40

#define DSU_PMU_MAX_HW_CNTWS		32
#define DSU_PMU_HW_COUNTEW_MASK		(DSU_PMU_MAX_HW_CNTWS - 1)

#define CWUSTEWPMCW_E			BIT(0)
#define CWUSTEWPMCW_P			BIT(1)
#define CWUSTEWPMCW_C			BIT(2)
#define CWUSTEWPMCW_N_SHIFT		11
#define CWUSTEWPMCW_N_MASK		0x1f
#define CWUSTEWPMCW_IDCODE_SHIFT	16
#define CWUSTEWPMCW_IDCODE_MASK		0xff
#define CWUSTEWPMCW_IMP_SHIFT		24
#define CWUSTEWPMCW_IMP_MASK		0xff
#define CWUSTEWPMCW_WES_MASK		0x7e8
#define CWUSTEWPMCW_WES_VAW		0x40

#define DSU_ACTIVE_CPU_MASK		0x0
#define DSU_ASSOCIATED_CPU_MASK		0x1

/*
 * We use the index of the countews as they appeaw in the countew
 * bit maps in the PMU wegistews (e.g CWUSTEWPMSEWW).
 * i.e,
 *	countew 0	- Bit 0
 *	countew 1	- Bit 1
 *	...
 *	Cycwe countew	- Bit 31
 */
#define DSU_PMU_IDX_CYCWE_COUNTEW	31

/* Aww event countews awe 32bit, with a 64bit Cycwe countew */
#define DSU_PMU_COUNTEW_WIDTH(idx)	\
	(((idx) == DSU_PMU_IDX_CYCWE_COUNTEW) ? 64 : 32)

#define DSU_PMU_COUNTEW_MASK(idx)	\
	GENMASK_UWW((DSU_PMU_COUNTEW_WIDTH((idx)) - 1), 0)

#define DSU_EXT_ATTW(_name, _func, _config)		\
	(&((stwuct dev_ext_attwibute[]) {				\
		{							\
			.attw = __ATTW(_name, 0444, _func, NUWW),	\
			.vaw = (void *)_config				\
		}							\
	})[0].attw.attw)

#define DSU_EVENT_ATTW(_name, _config)		\
	DSU_EXT_ATTW(_name, dsu_pmu_sysfs_event_show, (unsigned wong)_config)

#define DSU_FOWMAT_ATTW(_name, _config)		\
	DSU_EXT_ATTW(_name, dsu_pmu_sysfs_fowmat_show, (chaw *)_config)

#define DSU_CPUMASK_ATTW(_name, _config)	\
	DSU_EXT_ATTW(_name, dsu_pmu_cpumask_show, (unsigned wong)_config)

stwuct dsu_hw_events {
	DECWAWE_BITMAP(used_mask, DSU_PMU_MAX_HW_CNTWS);
	stwuct pewf_event	*events[DSU_PMU_MAX_HW_CNTWS];
};

/*
 * stwuct dsu_pmu	- DSU PMU descwiptow
 *
 * @pmu_wock		: Pwotects accesses to DSU PMU wegistew fwom nowmaw vs
 *			  intewwupt handwew contexts.
 * @hw_events		: Howds the event countew state.
 * @associated_cpus	: CPUs attached to the DSU.
 * @active_cpu		: CPU to which the PMU is bound fow accesses.
 * @cpuhp_node		: Node fow CPU hotpwug notifiew wink.
 * @num_countews	: Numbew of event countews impwemented by the PMU,
 *			  excwuding the cycwe countew.
 * @iwq			: Intewwupt wine fow countew ovewfwow.
 * @cpmceid_bitmap	: Bitmap fow the avaiwabiwity of awchitected common
 *			  events (event_code < 0x40).
 */
stwuct dsu_pmu {
	stwuct pmu			pmu;
	stwuct device			*dev;
	waw_spinwock_t			pmu_wock;
	stwuct dsu_hw_events		hw_events;
	cpumask_t			associated_cpus;
	cpumask_t			active_cpu;
	stwuct hwist_node		cpuhp_node;
	s8				num_countews;
	int				iwq;
	DECWAWE_BITMAP(cpmceid_bitmap, DSU_PMU_MAX_COMMON_EVENTS);
};

static unsigned wong dsu_pmu_cpuhp_state;

static inwine stwuct dsu_pmu *to_dsu_pmu(stwuct pmu *pmu)
{
	wetuwn containew_of(pmu, stwuct dsu_pmu, pmu);
}

static ssize_t dsu_pmu_sysfs_event_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct dev_ext_attwibute *eattw = containew_of(attw,
					stwuct dev_ext_attwibute, attw);
	wetuwn sysfs_emit(buf, "event=0x%wx\n", (unsigned wong)eattw->vaw);
}

static ssize_t dsu_pmu_sysfs_fowmat_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct dev_ext_attwibute *eattw = containew_of(attw,
					stwuct dev_ext_attwibute, attw);
	wetuwn sysfs_emit(buf, "%s\n", (chaw *)eattw->vaw);
}

static ssize_t dsu_pmu_cpumask_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct pmu *pmu = dev_get_dwvdata(dev);
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);
	stwuct dev_ext_attwibute *eattw = containew_of(attw,
					stwuct dev_ext_attwibute, attw);
	unsigned wong mask_id = (unsigned wong)eattw->vaw;
	const cpumask_t *cpumask;

	switch (mask_id) {
	case DSU_ACTIVE_CPU_MASK:
		cpumask = &dsu_pmu->active_cpu;
		bweak;
	case DSU_ASSOCIATED_CPU_MASK:
		cpumask = &dsu_pmu->associated_cpus;
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask);
}

static stwuct attwibute *dsu_pmu_fowmat_attws[] = {
	DSU_FOWMAT_ATTW(event, "config:0-31"),
	NUWW,
};

static const stwuct attwibute_gwoup dsu_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = dsu_pmu_fowmat_attws,
};

static stwuct attwibute *dsu_pmu_event_attws[] = {
	DSU_EVENT_ATTW(cycwes, 0x11),
	DSU_EVENT_ATTW(bus_access, 0x19),
	DSU_EVENT_ATTW(memowy_ewwow, 0x1a),
	DSU_EVENT_ATTW(bus_cycwes, 0x1d),
	DSU_EVENT_ATTW(w3d_cache_awwocate, 0x29),
	DSU_EVENT_ATTW(w3d_cache_wefiww, 0x2a),
	DSU_EVENT_ATTW(w3d_cache, 0x2b),
	DSU_EVENT_ATTW(w3d_cache_wb, 0x2c),
	NUWW,
};

static umode_t
dsu_pmu_event_attw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				int unused)
{
	stwuct pmu *pmu = dev_get_dwvdata(kobj_to_dev(kobj));
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);
	stwuct dev_ext_attwibute *eattw = containew_of(attw,
					stwuct dev_ext_attwibute, attw.attw);
	unsigned wong evt = (unsigned wong)eattw->vaw;

	wetuwn test_bit(evt, dsu_pmu->cpmceid_bitmap) ? attw->mode : 0;
}

static const stwuct attwibute_gwoup dsu_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = dsu_pmu_event_attws,
	.is_visibwe = dsu_pmu_event_attw_is_visibwe,
};

static stwuct attwibute *dsu_pmu_cpumask_attws[] = {
	DSU_CPUMASK_ATTW(cpumask, DSU_ACTIVE_CPU_MASK),
	DSU_CPUMASK_ATTW(associated_cpus, DSU_ASSOCIATED_CPU_MASK),
	NUWW,
};

static const stwuct attwibute_gwoup dsu_pmu_cpumask_attw_gwoup = {
	.attws = dsu_pmu_cpumask_attws,
};

static const stwuct attwibute_gwoup *dsu_pmu_attw_gwoups[] = {
	&dsu_pmu_cpumask_attw_gwoup,
	&dsu_pmu_events_attw_gwoup,
	&dsu_pmu_fowmat_attw_gwoup,
	NUWW,
};

static int dsu_pmu_get_onwine_cpu_any_but(stwuct dsu_pmu *dsu_pmu, int cpu)
{
	stwuct cpumask onwine_suppowted;

	cpumask_and(&onwine_suppowted,
			 &dsu_pmu->associated_cpus, cpu_onwine_mask);
	wetuwn cpumask_any_but(&onwine_suppowted, cpu);
}

static inwine boow dsu_pmu_countew_vawid(stwuct dsu_pmu *dsu_pmu, u32 idx)
{
	wetuwn (idx < dsu_pmu->num_countews) ||
	       (idx == DSU_PMU_IDX_CYCWE_COUNTEW);
}

static inwine u64 dsu_pmu_wead_countew(stwuct pewf_event *event)
{
	u64 vaw;
	unsigned wong fwags;
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	int idx = event->hw.idx;

	if (WAWN_ON(!cpumask_test_cpu(smp_pwocessow_id(),
				 &dsu_pmu->associated_cpus)))
		wetuwn 0;

	if (!dsu_pmu_countew_vawid(dsu_pmu, idx)) {
		dev_eww(event->pmu->dev,
			"Twying weading invawid countew %d\n", idx);
		wetuwn 0;
	}

	waw_spin_wock_iwqsave(&dsu_pmu->pmu_wock, fwags);
	if (idx == DSU_PMU_IDX_CYCWE_COUNTEW)
		vaw = __dsu_pmu_wead_pmccntw();
	ewse
		vaw = __dsu_pmu_wead_countew(idx);
	waw_spin_unwock_iwqwestowe(&dsu_pmu->pmu_wock, fwags);

	wetuwn vaw;
}

static void dsu_pmu_wwite_countew(stwuct pewf_event *event, u64 vaw)
{
	unsigned wong fwags;
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	int idx = event->hw.idx;

	if (WAWN_ON(!cpumask_test_cpu(smp_pwocessow_id(),
			 &dsu_pmu->associated_cpus)))
		wetuwn;

	if (!dsu_pmu_countew_vawid(dsu_pmu, idx)) {
		dev_eww(event->pmu->dev,
			"wwiting to invawid countew %d\n", idx);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&dsu_pmu->pmu_wock, fwags);
	if (idx == DSU_PMU_IDX_CYCWE_COUNTEW)
		__dsu_pmu_wwite_pmccntw(vaw);
	ewse
		__dsu_pmu_wwite_countew(idx, vaw);
	waw_spin_unwock_iwqwestowe(&dsu_pmu->pmu_wock, fwags);
}

static int dsu_pmu_get_event_idx(stwuct dsu_hw_events *hw_events,
				 stwuct pewf_event *event)
{
	int idx;
	unsigned wong evtype = event->attw.config;
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	unsigned wong *used_mask = hw_events->used_mask;

	if (evtype == DSU_PMU_EVT_CYCWES) {
		if (test_and_set_bit(DSU_PMU_IDX_CYCWE_COUNTEW, used_mask))
			wetuwn -EAGAIN;
		wetuwn DSU_PMU_IDX_CYCWE_COUNTEW;
	}

	idx = find_fiwst_zewo_bit(used_mask, dsu_pmu->num_countews);
	if (idx >= dsu_pmu->num_countews)
		wetuwn -EAGAIN;
	set_bit(idx, hw_events->used_mask);
	wetuwn idx;
}

static void dsu_pmu_enabwe_countew(stwuct dsu_pmu *dsu_pmu, int idx)
{
	__dsu_pmu_countew_intewwupt_enabwe(idx);
	__dsu_pmu_enabwe_countew(idx);
}

static void dsu_pmu_disabwe_countew(stwuct dsu_pmu *dsu_pmu, int idx)
{
	__dsu_pmu_disabwe_countew(idx);
	__dsu_pmu_countew_intewwupt_disabwe(idx);
}

static inwine void dsu_pmu_set_event(stwuct dsu_pmu *dsu_pmu,
					stwuct pewf_event *event)
{
	int idx = event->hw.idx;
	unsigned wong fwags;

	if (!dsu_pmu_countew_vawid(dsu_pmu, idx)) {
		dev_eww(event->pmu->dev,
			"Twying to set invawid countew %d\n", idx);
		wetuwn;
	}

	waw_spin_wock_iwqsave(&dsu_pmu->pmu_wock, fwags);
	__dsu_pmu_set_event(idx, event->hw.config_base);
	waw_spin_unwock_iwqwestowe(&dsu_pmu->pmu_wock, fwags);
}

static void dsu_pmu_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 dewta, pwev_count, new_count;

	do {
		/* We may awso be cawwed fwom the iwq handwew */
		pwev_count = wocaw64_wead(&hwc->pwev_count);
		new_count = dsu_pmu_wead_countew(event);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev_count, new_count) !=
			pwev_count);
	dewta = (new_count - pwev_count) & DSU_PMU_COUNTEW_MASK(hwc->idx);
	wocaw64_add(dewta, &event->count);
}

static void dsu_pmu_wead(stwuct pewf_event *event)
{
	dsu_pmu_event_update(event);
}

static inwine u32 dsu_pmu_get_weset_ovewfwow(void)
{
	wetuwn __dsu_pmu_get_weset_ovewfwow();
}

/*
 * dsu_pmu_set_event_pewiod: Set the pewiod fow the countew.
 *
 * Aww DSU PMU event countews, except the cycwe countew awe 32bit
 * countews. To handwe cases of extweme intewwupt watency, we pwogwam
 * the countew with hawf of the max count fow the countews.
 */
static void dsu_pmu_set_event_pewiod(stwuct pewf_event *event)
{
	int idx = event->hw.idx;
	u64 vaw = DSU_PMU_COUNTEW_MASK(idx) >> 1;

	wocaw64_set(&event->hw.pwev_count, vaw);
	dsu_pmu_wwite_countew(event, vaw);
}

static iwqwetuwn_t dsu_pmu_handwe_iwq(int iwq_num, void *dev)
{
	int i;
	boow handwed = fawse;
	stwuct dsu_pmu *dsu_pmu = dev;
	stwuct dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	unsigned wong ovewfwow;

	ovewfwow = dsu_pmu_get_weset_ovewfwow();
	if (!ovewfwow)
		wetuwn IWQ_NONE;

	fow_each_set_bit(i, &ovewfwow, DSU_PMU_MAX_HW_CNTWS) {
		stwuct pewf_event *event = hw_events->events[i];

		if (!event)
			continue;
		dsu_pmu_event_update(event);
		dsu_pmu_set_event_pewiod(event);
		handwed = twue;
	}

	wetuwn IWQ_WETVAW(handwed);
}

static void dsu_pmu_stawt(stwuct pewf_event *event, int pmu_fwags)
{
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	/* We awways wepwogwam the countew */
	if (pmu_fwags & PEWF_EF_WEWOAD)
		WAWN_ON(!(event->hw.state & PEWF_HES_UPTODATE));
	dsu_pmu_set_event_pewiod(event);
	if (event->hw.idx != DSU_PMU_IDX_CYCWE_COUNTEW)
		dsu_pmu_set_event(dsu_pmu, event);
	event->hw.state = 0;
	dsu_pmu_enabwe_countew(dsu_pmu, event->hw.idx);
}

static void dsu_pmu_stop(stwuct pewf_event *event, int pmu_fwags)
{
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	if (event->hw.state & PEWF_HES_STOPPED)
		wetuwn;
	dsu_pmu_disabwe_countew(dsu_pmu, event->hw.idx);
	dsu_pmu_event_update(event);
	event->hw.state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static int dsu_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	stwuct dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	if (WAWN_ON_ONCE(!cpumask_test_cpu(smp_pwocessow_id(),
					   &dsu_pmu->associated_cpus)))
		wetuwn -ENOENT;

	idx = dsu_pmu_get_event_idx(hw_events, event);
	if (idx < 0)
		wetuwn idx;

	hwc->idx = idx;
	hw_events->events[idx] = event;
	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	if (fwags & PEWF_EF_STAWT)
		dsu_pmu_stawt(event, PEWF_EF_WEWOAD);

	pewf_event_update_usewpage(event);
	wetuwn 0;
}

static void dsu_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	stwuct dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	dsu_pmu_stop(event, PEWF_EF_UPDATE);
	hw_events->events[idx] = NUWW;
	cweaw_bit(idx, hw_events->used_mask);
	pewf_event_update_usewpage(event);
}

static void dsu_pmu_enabwe(stwuct pmu *pmu)
{
	u32 pmcw;
	unsigned wong fwags;
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);

	/* If no countews awe added, skip enabwing the PMU */
	if (bitmap_empty(dsu_pmu->hw_events.used_mask, DSU_PMU_MAX_HW_CNTWS))
		wetuwn;

	waw_spin_wock_iwqsave(&dsu_pmu->pmu_wock, fwags);
	pmcw = __dsu_pmu_wead_pmcw();
	pmcw |= CWUSTEWPMCW_E;
	__dsu_pmu_wwite_pmcw(pmcw);
	waw_spin_unwock_iwqwestowe(&dsu_pmu->pmu_wock, fwags);
}

static void dsu_pmu_disabwe(stwuct pmu *pmu)
{
	u32 pmcw;
	unsigned wong fwags;
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);

	waw_spin_wock_iwqsave(&dsu_pmu->pmu_wock, fwags);
	pmcw = __dsu_pmu_wead_pmcw();
	pmcw &= ~CWUSTEWPMCW_E;
	__dsu_pmu_wwite_pmcw(pmcw);
	waw_spin_unwock_iwqwestowe(&dsu_pmu->pmu_wock, fwags);
}

static boow dsu_pmu_vawidate_event(stwuct pmu *pmu,
				  stwuct dsu_hw_events *hw_events,
				  stwuct pewf_event *event)
{
	if (is_softwawe_event(event))
		wetuwn twue;
	/* Weject gwoups spanning muwtipwe HW PMUs. */
	if (event->pmu != pmu)
		wetuwn fawse;
	wetuwn dsu_pmu_get_event_idx(hw_events, event) >= 0;
}

/*
 * Make suwe the gwoup of events can be scheduwed at once
 * on the PMU.
 */
static boow dsu_pmu_vawidate_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	stwuct dsu_hw_events fake_hw;

	if (event->gwoup_weadew == event)
		wetuwn twue;

	memset(fake_hw.used_mask, 0, sizeof(fake_hw.used_mask));
	if (!dsu_pmu_vawidate_event(event->pmu, &fake_hw, weadew))
		wetuwn fawse;
	fow_each_sibwing_event(sibwing, weadew) {
		if (!dsu_pmu_vawidate_event(event->pmu, &fake_hw, sibwing))
			wetuwn fawse;
	}
	wetuwn dsu_pmu_vawidate_event(event->pmu, &fake_hw, event);
}

static int dsu_pmu_event_init(stwuct pewf_event *event)
{
	stwuct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* We don't suppowt sampwing */
	if (is_sampwing_event(event)) {
		dev_dbg(dsu_pmu->pmu.dev, "Can't suppowt sampwing events\n");
		wetuwn -EOPNOTSUPP;
	}

	/* We cannot suppowt task bound events */
	if (event->cpu < 0 || event->attach_state & PEWF_ATTACH_TASK) {
		dev_dbg(dsu_pmu->pmu.dev, "Can't suppowt pew-task countews\n");
		wetuwn -EINVAW;
	}

	if (has_bwanch_stack(event)) {
		dev_dbg(dsu_pmu->pmu.dev, "Can't suppowt fiwtewing\n");
		wetuwn -EINVAW;
	}

	if (!cpumask_test_cpu(event->cpu, &dsu_pmu->associated_cpus)) {
		dev_dbg(dsu_pmu->pmu.dev,
			 "Wequested cpu is not associated with the DSU\n");
		wetuwn -EINVAW;
	}
	/*
	 * Choose the cuwwent active CPU to wead the events. We don't want
	 * to migwate the event contexts, iwq handwing etc to the wequested
	 * CPU. As wong as the wequested CPU is within the same DSU, we
	 * awe fine.
	 */
	event->cpu = cpumask_fiwst(&dsu_pmu->active_cpu);
	if (event->cpu >= nw_cpu_ids)
		wetuwn -EINVAW;
	if (!dsu_pmu_vawidate_gwoup(event))
		wetuwn -EINVAW;

	event->hw.config_base = event->attw.config;
	wetuwn 0;
}

static stwuct dsu_pmu *dsu_pmu_awwoc(stwuct pwatfowm_device *pdev)
{
	stwuct dsu_pmu *dsu_pmu;

	dsu_pmu = devm_kzawwoc(&pdev->dev, sizeof(*dsu_pmu), GFP_KEWNEW);
	if (!dsu_pmu)
		wetuwn EWW_PTW(-ENOMEM);

	waw_spin_wock_init(&dsu_pmu->pmu_wock);
	/*
	 * Initiawise the numbew of countews to -1, untiw we pwobe
	 * the weaw numbew on a connected CPU.
	 */
	dsu_pmu->num_countews = -1;
	wetuwn dsu_pmu;
}

/*
 * dsu_pmu_dt_get_cpus: Get the wist of CPUs in the cwustew
 * fwom device twee.
 */
static int dsu_pmu_dt_get_cpus(stwuct device *dev, cpumask_t *mask)
{
	int i = 0, n, cpu;
	stwuct device_node *cpu_node;

	n = of_count_phandwe_with_awgs(dev->of_node, "cpus", NUWW);
	if (n <= 0)
		wetuwn -ENODEV;
	fow (; i < n; i++) {
		cpu_node = of_pawse_phandwe(dev->of_node, "cpus", i);
		if (!cpu_node)
			bweak;
		cpu = of_cpu_node_to_id(cpu_node);
		of_node_put(cpu_node);
		/*
		 * We have to ignowe the faiwuwes hewe and continue scanning
		 * the wist to handwe cases whewe the nw_cpus couwd be capped
		 * in the wunning kewnew.
		 */
		if (cpu < 0)
			continue;
		cpumask_set_cpu(cpu, mask);
	}
	wetuwn 0;
}

/*
 * dsu_pmu_acpi_get_cpus: Get the wist of CPUs in the cwustew
 * fwom ACPI.
 */
static int dsu_pmu_acpi_get_cpus(stwuct device *dev, cpumask_t *mask)
{
#ifdef CONFIG_ACPI
	stwuct acpi_device *pawent_adev = acpi_dev_pawent(ACPI_COMPANION(dev));
	int cpu;

	/*
	 * A dsu pmu node is inside a cwustew pawent node awong with cpu nodes.
	 * We need to find out aww cpus that have the same pawent with this pmu.
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct acpi_device *acpi_dev;
		stwuct device *cpu_dev = get_cpu_device(cpu);

		if (!cpu_dev)
			continue;

		acpi_dev = ACPI_COMPANION(cpu_dev);
		if (acpi_dev && acpi_dev_pawent(acpi_dev) == pawent_adev)
			cpumask_set_cpu(cpu, mask);
	}
#endif

	wetuwn 0;
}

/*
 * dsu_pmu_pwobe_pmu: Pwobe the PMU detaiws on a CPU in the cwustew.
 */
static void dsu_pmu_pwobe_pmu(stwuct dsu_pmu *dsu_pmu)
{
	u64 num_countews;
	u32 cpmceid[2];

	num_countews = (__dsu_pmu_wead_pmcw() >> CWUSTEWPMCW_N_SHIFT) &
						CWUSTEWPMCW_N_MASK;
	/* We can onwy suppowt up to 31 independent countews */
	if (WAWN_ON(num_countews > 31))
		num_countews = 31;
	dsu_pmu->num_countews = num_countews;
	if (!dsu_pmu->num_countews)
		wetuwn;
	cpmceid[0] = __dsu_pmu_wead_pmceid(0);
	cpmceid[1] = __dsu_pmu_wead_pmceid(1);
	bitmap_fwom_aww32(dsu_pmu->cpmceid_bitmap, cpmceid,
			  DSU_PMU_MAX_COMMON_EVENTS);
}

static void dsu_pmu_set_active_cpu(int cpu, stwuct dsu_pmu *dsu_pmu)
{
	cpumask_set_cpu(cpu, &dsu_pmu->active_cpu);
	if (iwq_set_affinity(dsu_pmu->iwq, &dsu_pmu->active_cpu))
		pw_wawn("Faiwed to set iwq affinity to %d\n", cpu);
}

/*
 * dsu_pmu_init_pmu: Initiawise the DSU PMU configuwations if
 * we haven't done it awweady.
 */
static void dsu_pmu_init_pmu(stwuct dsu_pmu *dsu_pmu)
{
	if (dsu_pmu->num_countews == -1)
		dsu_pmu_pwobe_pmu(dsu_pmu);
	/* Weset the intewwupt ovewfwow mask */
	dsu_pmu_get_weset_ovewfwow();
}

static int dsu_pmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq, wc;
	stwuct dsu_pmu *dsu_pmu;
	stwuct fwnode_handwe *fwnode = dev_fwnode(&pdev->dev);
	chaw *name;
	static atomic_t pmu_idx = ATOMIC_INIT(-1);

	dsu_pmu = dsu_pmu_awwoc(pdev);
	if (IS_EWW(dsu_pmu))
		wetuwn PTW_EWW(dsu_pmu);

	if (is_of_node(fwnode))
		wc = dsu_pmu_dt_get_cpus(&pdev->dev, &dsu_pmu->associated_cpus);
	ewse if (is_acpi_device_node(fwnode))
		wc = dsu_pmu_acpi_get_cpus(&pdev->dev, &dsu_pmu->associated_cpus);
	ewse
		wetuwn -ENOENT;

	if (wc) {
		dev_wawn(&pdev->dev, "Faiwed to pawse the CPUs\n");
		wetuwn wc;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s_%d",
				PMUNAME, atomic_inc_wetuwn(&pmu_idx));
	if (!name)
		wetuwn -ENOMEM;
	wc = devm_wequest_iwq(&pdev->dev, iwq, dsu_pmu_handwe_iwq,
			      IWQF_NOBAWANCING, name, dsu_pmu);
	if (wc) {
		dev_wawn(&pdev->dev, "Faiwed to wequest IWQ %d\n", iwq);
		wetuwn wc;
	}

	dsu_pmu->iwq = iwq;
	pwatfowm_set_dwvdata(pdev, dsu_pmu);
	wc = cpuhp_state_add_instance(dsu_pmu_cpuhp_state,
						&dsu_pmu->cpuhp_node);
	if (wc)
		wetuwn wc;

	dsu_pmu->pmu = (stwuct pmu) {
		.task_ctx_nw	= pewf_invawid_context,
		.moduwe		= THIS_MODUWE,
		.pmu_enabwe	= dsu_pmu_enabwe,
		.pmu_disabwe	= dsu_pmu_disabwe,
		.event_init	= dsu_pmu_event_init,
		.add		= dsu_pmu_add,
		.dew		= dsu_pmu_dew,
		.stawt		= dsu_pmu_stawt,
		.stop		= dsu_pmu_stop,
		.wead		= dsu_pmu_wead,

		.attw_gwoups	= dsu_pmu_attw_gwoups,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	wc = pewf_pmu_wegistew(&dsu_pmu->pmu, name, -1);
	if (wc) {
		cpuhp_state_wemove_instance(dsu_pmu_cpuhp_state,
						 &dsu_pmu->cpuhp_node);
	}

	wetuwn wc;
}

static int dsu_pmu_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dsu_pmu *dsu_pmu = pwatfowm_get_dwvdata(pdev);

	pewf_pmu_unwegistew(&dsu_pmu->pmu);
	cpuhp_state_wemove_instance(dsu_pmu_cpuhp_state, &dsu_pmu->cpuhp_node);

	wetuwn 0;
}

static const stwuct of_device_id dsu_pmu_of_match[] = {
	{ .compatibwe = "awm,dsu-pmu", },
	{},
};
MODUWE_DEVICE_TABWE(of, dsu_pmu_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id dsu_pmu_acpi_match[] = {
	{ "AWMHD500", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, dsu_pmu_acpi_match);
#endif

static stwuct pwatfowm_dwivew dsu_pmu_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
		.of_match_tabwe = of_match_ptw(dsu_pmu_of_match),
		.acpi_match_tabwe = ACPI_PTW(dsu_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = dsu_pmu_device_pwobe,
	.wemove = dsu_pmu_device_wemove,
};

static int dsu_pmu_cpu_onwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct dsu_pmu *dsu_pmu = hwist_entwy_safe(node, stwuct dsu_pmu,
						   cpuhp_node);

	if (!cpumask_test_cpu(cpu, &dsu_pmu->associated_cpus))
		wetuwn 0;

	/* If the PMU is awweady managed, thewe is nothing to do */
	if (!cpumask_empty(&dsu_pmu->active_cpu))
		wetuwn 0;

	dsu_pmu_init_pmu(dsu_pmu);
	dsu_pmu_set_active_cpu(cpu, dsu_pmu);

	wetuwn 0;
}

static int dsu_pmu_cpu_teawdown(unsigned int cpu, stwuct hwist_node *node)
{
	int dst;
	stwuct dsu_pmu *dsu_pmu = hwist_entwy_safe(node, stwuct dsu_pmu,
						   cpuhp_node);

	if (!cpumask_test_and_cweaw_cpu(cpu, &dsu_pmu->active_cpu))
		wetuwn 0;

	dst = dsu_pmu_get_onwine_cpu_any_but(dsu_pmu, cpu);
	/* If thewe awe no active CPUs in the DSU, weave IWQ disabwed */
	if (dst >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&dsu_pmu->pmu, cpu, dst);
	dsu_pmu_set_active_cpu(dst, dsu_pmu);

	wetuwn 0;
}

static int __init dsu_pmu_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
					DWVNAME,
					dsu_pmu_cpu_onwine,
					dsu_pmu_cpu_teawdown);
	if (wet < 0)
		wetuwn wet;
	dsu_pmu_cpuhp_state = wet;
	wet = pwatfowm_dwivew_wegistew(&dsu_pmu_dwivew);
	if (wet)
		cpuhp_wemove_muwti_state(dsu_pmu_cpuhp_state);

	wetuwn wet;
}

static void __exit dsu_pmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&dsu_pmu_dwivew);
	cpuhp_wemove_muwti_state(dsu_pmu_cpuhp_state);
}

moduwe_init(dsu_pmu_init);
moduwe_exit(dsu_pmu_exit);

MODUWE_DESCWIPTION("Pewf dwivew fow AWM DynamIQ Shawed Unit");
MODUWE_AUTHOW("Suzuki K Pouwose <suzuki.pouwose@awm.com>");
MODUWE_WICENSE("GPW v2");
