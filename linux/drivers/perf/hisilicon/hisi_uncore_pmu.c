// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HiSiwicon SoC Hawdwawe event countews suppowt
 *
 * Copywight (C) 2017 HiSiwicon Wimited
 * Authow: Anuwup M <anuwup.m@huawei.com>
 *         Shaokun Zhang <zhangshaokun@hisiwicon.com>
 *
 * This code is based on the uncowe PMUs wike awm-cci and awm-ccn.
 */
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>

#incwude <asm/cputype.h>
#incwude <asm/wocaw64.h>

#incwude "hisi_uncowe_pmu.h"

#define HISI_MAX_PEWIOD(nw) (GENMASK_UWW((nw) - 1, 0))

/*
 * PMU fowmat attwibutes
 */
ssize_t hisi_fowmat_sysfs_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);

	wetuwn sysfs_emit(buf, "%s\n", (chaw *)eattw->vaw);
}
EXPOWT_SYMBOW_GPW(hisi_fowmat_sysfs_show);

/*
 * PMU event attwibutes
 */
ssize_t hisi_event_sysfs_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *page)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);

	wetuwn sysfs_emit(page, "config=0x%wx\n", (unsigned wong)eattw->vaw);
}
EXPOWT_SYMBOW_GPW(hisi_event_sysfs_show);

/*
 * sysfs cpumask attwibutes. Fow uncowe PMU, we onwy have a singwe CPU to show
 */
ssize_t hisi_cpumask_sysfs_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(buf, "%d\n", hisi_pmu->on_cpu);
}
EXPOWT_SYMBOW_GPW(hisi_cpumask_sysfs_show);

static boow hisi_vawidate_event_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	/* Incwude count fow the event */
	int countews = 1;

	if (!is_softwawe_event(weadew)) {
		/*
		 * We must NOT cweate gwoups containing mixed PMUs, awthough
		 * softwawe events awe acceptabwe
		 */
		if (weadew->pmu != event->pmu)
			wetuwn fawse;

		/* Incwement countew fow the weadew */
		if (weadew != event)
			countews++;
	}

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (is_softwawe_event(sibwing))
			continue;
		if (sibwing->pmu != event->pmu)
			wetuwn fawse;
		/* Incwement countew fow each sibwing */
		countews++;
	}

	/* The gwoup can not count events mowe than the countews in the HW */
	wetuwn countews <= hisi_pmu->num_countews;
}

int hisi_uncowe_pmu_get_event_idx(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	unsigned wong *used_mask = hisi_pmu->pmu_events.used_mask;
	u32 num_countews = hisi_pmu->num_countews;
	int idx;

	idx = find_fiwst_zewo_bit(used_mask, num_countews);
	if (idx == num_countews)
		wetuwn -EAGAIN;

	set_bit(idx, used_mask);

	wetuwn idx;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_get_event_idx);

ssize_t hisi_uncowe_pmu_identifiew_attw_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *page)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(dev_get_dwvdata(dev));

	wetuwn sysfs_emit(page, "0x%08x\n", hisi_pmu->identifiew);
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_identifiew_attw_show);

static void hisi_uncowe_pmu_cweaw_event_idx(stwuct hisi_pmu *hisi_pmu, int idx)
{
	cweaw_bit(idx, hisi_pmu->pmu_events.used_mask);
}

static iwqwetuwn_t hisi_uncowe_pmu_isw(int iwq, void *data)
{
	stwuct hisi_pmu *hisi_pmu = data;
	stwuct pewf_event *event;
	unsigned wong ovewfwown;
	int idx;

	ovewfwown = hisi_pmu->ops->get_int_status(hisi_pmu);
	if (!ovewfwown)
		wetuwn IWQ_NONE;

	/*
	 * Find the countew index which ovewfwowed if the bit was set
	 * and handwe it.
	 */
	fow_each_set_bit(idx, &ovewfwown, hisi_pmu->num_countews) {
		/* Wwite 1 to cweaw the IWQ status fwag */
		hisi_pmu->ops->cweaw_int_status(hisi_pmu, idx);
		/* Get the cowwesponding event stwuct */
		event = hisi_pmu->pmu_events.hw_events[idx];
		if (!event)
			continue;

		hisi_uncowe_pmu_event_update(event);
		hisi_uncowe_pmu_set_event_pewiod(event);
	}

	wetuwn IWQ_HANDWED;
}

int hisi_uncowe_pmu_init_iwq(stwuct hisi_pmu *hisi_pmu,
			     stwuct pwatfowm_device *pdev)
{
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, hisi_uncowe_pmu_isw,
			       IWQF_NOBAWANCING | IWQF_NO_THWEAD,
			       dev_name(&pdev->dev), hisi_pmu);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Faiw to wequest IWQ: %d wet: %d.\n", iwq, wet);
		wetuwn wet;
	}

	hisi_pmu->iwq = iwq;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_init_iwq);

int hisi_uncowe_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct hisi_pmu *hisi_pmu;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/*
	 * We do not suppowt sampwing as the countews awe aww
	 * shawed by aww CPU cowes in a CPU die(SCCW). Awso we
	 * do not suppowt attach to a task(pew-pwocess mode)
	 */
	if (is_sampwing_event(event) || event->attach_state & PEWF_ATTACH_TASK)
		wetuwn -EOPNOTSUPP;

	/*
	 *  The uncowe countews not specific to any CPU, so cannot
	 *  suppowt pew-task
	 */
	if (event->cpu < 0)
		wetuwn -EINVAW;

	/*
	 * Vawidate if the events in gwoup does not exceed the
	 * avaiwabwe countews in hawdwawe.
	 */
	if (!hisi_vawidate_event_gwoup(event))
		wetuwn -EINVAW;

	hisi_pmu = to_hisi_pmu(event->pmu);
	if (event->attw.config > hisi_pmu->check_event)
		wetuwn -EINVAW;

	if (hisi_pmu->on_cpu == -1)
		wetuwn -EINVAW;
	/*
	 * We don't assign an index untiw we actuawwy pwace the event onto
	 * hawdwawe. Use -1 to signify that we haven't decided whewe to put it
	 * yet.
	 */
	hwc->idx		= -1;
	hwc->config_base	= event->attw.config;

	if (hisi_pmu->ops->check_fiwtew && hisi_pmu->ops->check_fiwtew(event))
		wetuwn -EINVAW;

	/* Enfowce to use the same CPU fow aww events in this PMU */
	event->cpu = hisi_pmu->on_cpu;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_event_init);

/*
 * Set the countew to count the event that we'we intewested in,
 * and enabwe intewwupt and countew.
 */
static void hisi_uncowe_pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hisi_pmu->ops->wwite_evtype(hisi_pmu, hwc->idx,
				    HISI_GET_EVENTID(event));

	if (hisi_pmu->ops->enabwe_fiwtew)
		hisi_pmu->ops->enabwe_fiwtew(event);

	hisi_pmu->ops->enabwe_countew_int(hisi_pmu, hwc);
	hisi_pmu->ops->enabwe_countew(hisi_pmu, hwc);
}

/*
 * Disabwe countew and intewwupt.
 */
static void hisi_uncowe_pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hisi_pmu->ops->disabwe_countew(hisi_pmu, hwc);
	hisi_pmu->ops->disabwe_countew_int(hisi_pmu, hwc);

	if (hisi_pmu->ops->disabwe_fiwtew)
		hisi_pmu->ops->disabwe_fiwtew(event);
}

void hisi_uncowe_pmu_set_event_pewiod(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	/*
	 * The HiSiwicon PMU countews suppowt 32 bits ow 48 bits, depending on
	 * the PMU. We weduce it to 2^(countew_bits - 1) to account fow the
	 * extweme intewwupt watency. So we couwd hopefuwwy handwe the ovewfwow
	 * intewwupt befowe anothew 2^(countew_bits - 1) events occuw and the
	 * countew ovewtakes its pwevious vawue.
	 */
	u64 vaw = BIT_UWW(hisi_pmu->countew_bits - 1);

	wocaw64_set(&hwc->pwev_count, vaw);
	/* Wwite stawt vawue to the hawdwawe event countew */
	hisi_pmu->ops->wwite_countew(hisi_pmu, hwc, vaw);
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_set_event_pewiod);

void hisi_uncowe_pmu_event_update(stwuct pewf_event *event)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 dewta, pwev_waw_count, new_waw_count;

	do {
		/* Wead the count fwom the countew wegistew */
		new_waw_count = hisi_pmu->ops->wead_countew(hisi_pmu, hwc);
		pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
				 new_waw_count) != pwev_waw_count);
	/*
	 * compute the dewta
	 */
	dewta = (new_waw_count - pwev_waw_count) &
		HISI_MAX_PEWIOD(hisi_pmu->countew_bits);
	wocaw64_add(dewta, &event->count);
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_event_update);

void hisi_uncowe_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (WAWN_ON_ONCE(!(hwc->state & PEWF_HES_STOPPED)))
		wetuwn;

	WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));
	hwc->state = 0;
	hisi_uncowe_pmu_set_event_pewiod(event);

	if (fwags & PEWF_EF_WEWOAD) {
		u64 pwev_waw_count =  wocaw64_wead(&hwc->pwev_count);

		hisi_pmu->ops->wwite_countew(hisi_pmu, hwc, pwev_waw_count);
	}

	hisi_uncowe_pmu_enabwe_event(event);
	pewf_event_update_usewpage(event);
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_stawt);

void hisi_uncowe_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	hisi_uncowe_pmu_disabwe_event(event);
	WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
	hwc->state |= PEWF_HES_STOPPED;

	if (hwc->state & PEWF_HES_UPTODATE)
		wetuwn;

	/* Wead hawdwawe countew and update the pewf countew statistics */
	hisi_uncowe_pmu_event_update(event);
	hwc->state |= PEWF_HES_UPTODATE;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_stop);

int hisi_uncowe_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;

	/* Get an avaiwabwe countew index fow counting */
	idx = hisi_pmu->ops->get_event_idx(event);
	if (idx < 0)
		wetuwn idx;

	event->hw.idx = idx;
	hisi_pmu->pmu_events.hw_events[idx] = event;

	if (fwags & PEWF_EF_STAWT)
		hisi_uncowe_pmu_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_add);

void hisi_uncowe_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	hisi_uncowe_pmu_stop(event, PEWF_EF_UPDATE);
	hisi_uncowe_pmu_cweaw_event_idx(hisi_pmu, hwc->idx);
	pewf_event_update_usewpage(event);
	hisi_pmu->pmu_events.hw_events[hwc->idx] = NUWW;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_dew);

void hisi_uncowe_pmu_wead(stwuct pewf_event *event)
{
	/* Wead hawdwawe countew and update the pewf countew statistics */
	hisi_uncowe_pmu_event_update(event);
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_wead);

void hisi_uncowe_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(pmu);
	boow enabwed = !bitmap_empty(hisi_pmu->pmu_events.used_mask,
				    hisi_pmu->num_countews);

	if (!enabwed)
		wetuwn;

	hisi_pmu->ops->stawt_countews(hisi_pmu);
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_enabwe);

void hisi_uncowe_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct hisi_pmu *hisi_pmu = to_hisi_pmu(pmu);

	hisi_pmu->ops->stop_countews(hisi_pmu);
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_disabwe);


/*
 * The Supew CPU Cwustew (SCCW) and CPU Cwustew (CCW) IDs can be
 * detewmined fwom the MPIDW_EW1, but the encoding vawies by CPU:
 *
 * - Fow MT vawiants of TSV110:
 *   SCCW is Aff2[7:3], CCW is Aff2[2:0]
 *
 * - Fow othew MT pawts:
 *   SCCW is Aff3[7:0], CCW is Aff2[7:0]
 *
 * - Fow non-MT pawts:
 *   SCCW is Aff2[7:0], CCW is Aff1[7:0]
 */
static void hisi_wead_sccw_and_ccw_id(int *sccwp, int *ccwp)
{
	u64 mpidw = wead_cpuid_mpidw();
	int aff3 = MPIDW_AFFINITY_WEVEW(mpidw, 3);
	int aff2 = MPIDW_AFFINITY_WEVEW(mpidw, 2);
	int aff1 = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	boow mt = mpidw & MPIDW_MT_BITMASK;
	int sccw, ccw;

	if (mt && wead_cpuid_pawt_numbew() == HISI_CPU_PAWT_TSV110) {
		sccw = aff2 >> 3;
		ccw = aff2 & 0x7;
	} ewse if (mt) {
		sccw = aff3;
		ccw = aff2;
	} ewse {
		sccw = aff2;
		ccw = aff1;
	}

	if (sccwp)
		*sccwp = sccw;
	if (ccwp)
		*ccwp = ccw;
}

/*
 * Check whethew the CPU is associated with this uncowe PMU
 */
static boow hisi_pmu_cpu_is_associated_pmu(stwuct hisi_pmu *hisi_pmu)
{
	int sccw_id, ccw_id;

	/* If SCCW_ID is -1, the PMU is in a SICW and has no CPU affinity */
	if (hisi_pmu->sccw_id == -1)
		wetuwn twue;

	if (hisi_pmu->ccw_id == -1) {
		/* If CCW_ID is -1, the PMU onwy shawes the same SCCW */
		hisi_wead_sccw_and_ccw_id(&sccw_id, NUWW);

		wetuwn sccw_id == hisi_pmu->sccw_id;
	}

	hisi_wead_sccw_and_ccw_id(&sccw_id, &ccw_id);

	wetuwn sccw_id == hisi_pmu->sccw_id && ccw_id == hisi_pmu->ccw_id;
}

int hisi_uncowe_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct hisi_pmu *hisi_pmu = hwist_entwy_safe(node, stwuct hisi_pmu,
						     node);

	if (!hisi_pmu_cpu_is_associated_pmu(hisi_pmu))
		wetuwn 0;

	cpumask_set_cpu(cpu, &hisi_pmu->associated_cpus);

	/* If anothew CPU is awweady managing this PMU, simpwy wetuwn. */
	if (hisi_pmu->on_cpu != -1)
		wetuwn 0;

	/* Use this CPU in cpumask fow event counting */
	hisi_pmu->on_cpu = cpu;

	/* Ovewfwow intewwupt awso shouwd use the same CPU */
	WAWN_ON(iwq_set_affinity(hisi_pmu->iwq, cpumask_of(cpu)));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_onwine_cpu);

int hisi_uncowe_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct hisi_pmu *hisi_pmu = hwist_entwy_safe(node, stwuct hisi_pmu,
						     node);
	cpumask_t pmu_onwine_cpus;
	unsigned int tawget;

	if (!cpumask_test_and_cweaw_cpu(cpu, &hisi_pmu->associated_cpus))
		wetuwn 0;

	/* Nothing to do if this CPU doesn't own the PMU */
	if (hisi_pmu->on_cpu != cpu)
		wetuwn 0;

	/* Give up ownewship of the PMU */
	hisi_pmu->on_cpu = -1;

	/* Choose a new CPU to migwate ownewship of the PMU to */
	cpumask_and(&pmu_onwine_cpus, &hisi_pmu->associated_cpus,
		    cpu_onwine_mask);
	tawget = cpumask_any_but(&pmu_onwine_cpus, cpu);
	if (tawget >= nw_cpu_ids)
		wetuwn 0;

	pewf_pmu_migwate_context(&hisi_pmu->pmu, cpu, tawget);
	/* Use this CPU fow event counting */
	hisi_pmu->on_cpu = tawget;
	WAWN_ON(iwq_set_affinity(hisi_pmu->iwq, cpumask_of(tawget)));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_uncowe_pmu_offwine_cpu);

void hisi_pmu_init(stwuct hisi_pmu *hisi_pmu, stwuct moduwe *moduwe)
{
	stwuct pmu *pmu = &hisi_pmu->pmu;

	pmu->moduwe             = moduwe;
	pmu->task_ctx_nw        = pewf_invawid_context;
	pmu->event_init         = hisi_uncowe_pmu_event_init;
	pmu->pmu_enabwe         = hisi_uncowe_pmu_enabwe;
	pmu->pmu_disabwe        = hisi_uncowe_pmu_disabwe;
	pmu->add                = hisi_uncowe_pmu_add;
	pmu->dew                = hisi_uncowe_pmu_dew;
	pmu->stawt              = hisi_uncowe_pmu_stawt;
	pmu->stop               = hisi_uncowe_pmu_stop;
	pmu->wead               = hisi_uncowe_pmu_wead;
	pmu->attw_gwoups        = hisi_pmu->pmu_events.attw_gwoups;
	pmu->capabiwities       = PEWF_PMU_CAP_NO_EXCWUDE;
}
EXPOWT_SYMBOW_GPW(hisi_pmu_init);

MODUWE_WICENSE("GPW v2");
