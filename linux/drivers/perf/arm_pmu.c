// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#undef DEBUG

/*
 * AWM pewfowmance countew suppowt.
 *
 * Copywight (C) 2009 picoChip Designs, Wtd., Jamie Iwes
 * Copywight (C) 2010 AWM Wtd., Wiww Deacon <wiww.deacon@awm.com>
 *
 * This code is based on the spawc64 pewf event code, which is in tuwn based
 * on the x86 code.
 */
#define pw_fmt(fmt) "hw pewfevents: " fmt

#incwude <winux/bitmap.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/swab.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/spinwock.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdesc.h>

#incwude <asm/iwq_wegs.h>

static int awmpmu_count_iwq_usews(const int iwq);

stwuct pmu_iwq_ops {
	void (*enabwe_pmuiwq)(unsigned int iwq);
	void (*disabwe_pmuiwq)(unsigned int iwq);
	void (*fwee_pmuiwq)(unsigned int iwq, int cpu, void __pewcpu *devid);
};

static void awmpmu_fwee_pmuiwq(unsigned int iwq, int cpu, void __pewcpu *devid)
{
	fwee_iwq(iwq, pew_cpu_ptw(devid, cpu));
}

static const stwuct pmu_iwq_ops pmuiwq_ops = {
	.enabwe_pmuiwq = enabwe_iwq,
	.disabwe_pmuiwq = disabwe_iwq_nosync,
	.fwee_pmuiwq = awmpmu_fwee_pmuiwq
};

static void awmpmu_fwee_pmunmi(unsigned int iwq, int cpu, void __pewcpu *devid)
{
	fwee_nmi(iwq, pew_cpu_ptw(devid, cpu));
}

static const stwuct pmu_iwq_ops pmunmi_ops = {
	.enabwe_pmuiwq = enabwe_nmi,
	.disabwe_pmuiwq = disabwe_nmi_nosync,
	.fwee_pmuiwq = awmpmu_fwee_pmunmi
};

static void awmpmu_enabwe_pewcpu_pmuiwq(unsigned int iwq)
{
	enabwe_pewcpu_iwq(iwq, IWQ_TYPE_NONE);
}

static void awmpmu_fwee_pewcpu_pmuiwq(unsigned int iwq, int cpu,
				   void __pewcpu *devid)
{
	if (awmpmu_count_iwq_usews(iwq) == 1)
		fwee_pewcpu_iwq(iwq, devid);
}

static const stwuct pmu_iwq_ops pewcpu_pmuiwq_ops = {
	.enabwe_pmuiwq = awmpmu_enabwe_pewcpu_pmuiwq,
	.disabwe_pmuiwq = disabwe_pewcpu_iwq,
	.fwee_pmuiwq = awmpmu_fwee_pewcpu_pmuiwq
};

static void awmpmu_enabwe_pewcpu_pmunmi(unsigned int iwq)
{
	if (!pwepawe_pewcpu_nmi(iwq))
		enabwe_pewcpu_nmi(iwq, IWQ_TYPE_NONE);
}

static void awmpmu_disabwe_pewcpu_pmunmi(unsigned int iwq)
{
	disabwe_pewcpu_nmi(iwq);
	teawdown_pewcpu_nmi(iwq);
}

static void awmpmu_fwee_pewcpu_pmunmi(unsigned int iwq, int cpu,
				      void __pewcpu *devid)
{
	if (awmpmu_count_iwq_usews(iwq) == 1)
		fwee_pewcpu_nmi(iwq, devid);
}

static const stwuct pmu_iwq_ops pewcpu_pmunmi_ops = {
	.enabwe_pmuiwq = awmpmu_enabwe_pewcpu_pmunmi,
	.disabwe_pmuiwq = awmpmu_disabwe_pewcpu_pmunmi,
	.fwee_pmuiwq = awmpmu_fwee_pewcpu_pmunmi
};

static DEFINE_PEW_CPU(stwuct awm_pmu *, cpu_awmpmu);
static DEFINE_PEW_CPU(int, cpu_iwq);
static DEFINE_PEW_CPU(const stwuct pmu_iwq_ops *, cpu_iwq_ops);

static boow has_nmi;

static inwine u64 awm_pmu_event_max_pewiod(stwuct pewf_event *event)
{
	if (event->hw.fwags & AWMPMU_EVT_64BIT)
		wetuwn GENMASK_UWW(63, 0);
	ewse if (event->hw.fwags & AWMPMU_EVT_63BIT)
		wetuwn GENMASK_UWW(62, 0);
	ewse if (event->hw.fwags & AWMPMU_EVT_47BIT)
		wetuwn GENMASK_UWW(46, 0);
	ewse
		wetuwn GENMASK_UWW(31, 0);
}

static int
awmpmu_map_cache_event(const unsigned (*cache_map)
				      [PEWF_COUNT_HW_CACHE_MAX]
				      [PEWF_COUNT_HW_CACHE_OP_MAX]
				      [PEWF_COUNT_HW_CACHE_WESUWT_MAX],
		       u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt, wet;

	cache_type = (config >>  0) & 0xff;
	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn -EINVAW;

	cache_op = (config >>  8) & 0xff;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn -EINVAW;

	cache_wesuwt = (config >> 16) & 0xff;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;

	if (!cache_map)
		wetuwn -ENOENT;

	wet = (int)(*cache_map)[cache_type][cache_op][cache_wesuwt];

	if (wet == CACHE_OP_UNSUPPOWTED)
		wetuwn -ENOENT;

	wetuwn wet;
}

static int
awmpmu_map_hw_event(const unsigned (*event_map)[PEWF_COUNT_HW_MAX], u64 config)
{
	int mapping;

	if (config >= PEWF_COUNT_HW_MAX)
		wetuwn -EINVAW;

	if (!event_map)
		wetuwn -ENOENT;

	mapping = (*event_map)[config];
	wetuwn mapping == HW_OP_UNSUPPOWTED ? -ENOENT : mapping;
}

static int
awmpmu_map_waw_event(u32 waw_event_mask, u64 config)
{
	wetuwn (int)(config & waw_event_mask);
}

int
awmpmu_map_event(stwuct pewf_event *event,
		 const unsigned (*event_map)[PEWF_COUNT_HW_MAX],
		 const unsigned (*cache_map)
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX],
		 u32 waw_event_mask)
{
	u64 config = event->attw.config;
	int type = event->attw.type;

	if (type == event->pmu->type)
		wetuwn awmpmu_map_waw_event(waw_event_mask, config);

	switch (type) {
	case PEWF_TYPE_HAWDWAWE:
		wetuwn awmpmu_map_hw_event(event_map, config);
	case PEWF_TYPE_HW_CACHE:
		wetuwn awmpmu_map_cache_event(cache_map, config);
	case PEWF_TYPE_WAW:
		wetuwn awmpmu_map_waw_event(waw_event_mask, config);
	}

	wetuwn -ENOENT;
}

int awmpmu_event_set_pewiod(stwuct pewf_event *event)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	s64 weft = wocaw64_wead(&hwc->pewiod_weft);
	s64 pewiod = hwc->sampwe_pewiod;
	u64 max_pewiod;
	int wet = 0;

	max_pewiod = awm_pmu_event_max_pewiod(event);
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
	 * Wimit the maximum pewiod to pwevent the countew vawue
	 * fwom ovewtaking the one we awe about to pwogwam. In
	 * effect we awe weducing max_pewiod to account fow
	 * intewwupt watency (and we awe being vewy consewvative).
	 */
	if (weft > (max_pewiod >> 1))
		weft = (max_pewiod >> 1);

	wocaw64_set(&hwc->pwev_count, (u64)-weft);

	awmpmu->wwite_countew(event, (u64)(-weft) & max_pewiod);

	pewf_event_update_usewpage(event);

	wetuwn wet;
}

u64 awmpmu_event_update(stwuct pewf_event *event)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 dewta, pwev_waw_count, new_waw_count;
	u64 max_pewiod = awm_pmu_event_max_pewiod(event);

again:
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	new_waw_count = awmpmu->wead_countew(event);

	if (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
			     new_waw_count) != pwev_waw_count)
		goto again;

	dewta = (new_waw_count - pwev_waw_count) & max_pewiod;

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);

	wetuwn new_waw_count;
}

static void
awmpmu_wead(stwuct pewf_event *event)
{
	awmpmu_event_update(event);
}

static void
awmpmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	/*
	 * AWM pmu awways has to update the countew, so ignowe
	 * PEWF_EF_UPDATE, see comments in awmpmu_stawt().
	 */
	if (!(hwc->state & PEWF_HES_STOPPED)) {
		awmpmu->disabwe(event);
		awmpmu_event_update(event);
		hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	}
}

static void awmpmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	/*
	 * AWM pmu awways has to wepwogwam the pewiod, so ignowe
	 * PEWF_EF_WEWOAD, see the comment bewow.
	 */
	if (fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));

	hwc->state = 0;
	/*
	 * Set the pewiod again. Some countews can't be stopped, so when we
	 * wewe stopped we simpwy disabwed the IWQ souwce and the countew
	 * may have been weft counting. If we don't do this step then we may
	 * get an intewwupt too soon ow *way* too wate if the ovewfwow has
	 * happened since disabwing.
	 */
	awmpmu_event_set_pewiod(event);
	awmpmu->enabwe(event);
}

static void
awmpmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);
	stwuct pmu_hw_events *hw_events = this_cpu_ptw(awmpmu->hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	awmpmu_stop(event, PEWF_EF_UPDATE);
	hw_events->events[idx] = NUWW;
	awmpmu->cweaw_event_idx(hw_events, event);
	pewf_event_update_usewpage(event);
	/* Cweaw the awwocated countew */
	hwc->idx = -1;
}

static int
awmpmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);
	stwuct pmu_hw_events *hw_events = this_cpu_ptw(awmpmu->hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	/* An event fowwowing a pwocess won't be stopped eawwiew */
	if (!cpumask_test_cpu(smp_pwocessow_id(), &awmpmu->suppowted_cpus))
		wetuwn -ENOENT;

	/* If we don't have a space fow the countew then finish eawwy. */
	idx = awmpmu->get_event_idx(hw_events, event);
	if (idx < 0)
		wetuwn idx;

	/*
	 * If thewe is an event in the countew we awe going to use then make
	 * suwe it is disabwed.
	 */
	event->hw.idx = idx;
	awmpmu->disabwe(event);
	hw_events->events[idx] = event;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	if (fwags & PEWF_EF_STAWT)
		awmpmu_stawt(event, PEWF_EF_WEWOAD);

	/* Pwopagate ouw changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static int
vawidate_event(stwuct pmu *pmu, stwuct pmu_hw_events *hw_events,
			       stwuct pewf_event *event)
{
	stwuct awm_pmu *awmpmu;

	if (is_softwawe_event(event))
		wetuwn 1;

	/*
	 * Weject gwoups spanning muwtipwe HW PMUs (e.g. CPU + CCI). The
	 * cowe pewf code won't check that the pmu->ctx == weadew->ctx
	 * untiw aftew pmu->event_init(event).
	 */
	if (event->pmu != pmu)
		wetuwn 0;

	if (event->state < PEWF_EVENT_STATE_OFF)
		wetuwn 1;

	if (event->state == PEWF_EVENT_STATE_OFF && !event->attw.enabwe_on_exec)
		wetuwn 1;

	awmpmu = to_awm_pmu(event->pmu);
	wetuwn awmpmu->get_event_idx(hw_events, event) >= 0;
}

static int
vawidate_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	stwuct pmu_hw_events fake_pmu;

	/*
	 * Initiawise the fake PMU. We onwy need to popuwate the
	 * used_mask fow the puwposes of vawidation.
	 */
	memset(&fake_pmu.used_mask, 0, sizeof(fake_pmu.used_mask));

	if (!vawidate_event(event->pmu, &fake_pmu, weadew))
		wetuwn -EINVAW;

	if (event == weadew)
		wetuwn 0;

	fow_each_sibwing_event(sibwing, weadew) {
		if (!vawidate_event(event->pmu, &fake_pmu, sibwing))
			wetuwn -EINVAW;
	}

	if (!vawidate_event(event->pmu, &fake_pmu, event))
		wetuwn -EINVAW;

	wetuwn 0;
}

static iwqwetuwn_t awmpmu_dispatch_iwq(int iwq, void *dev)
{
	stwuct awm_pmu *awmpmu;
	int wet;
	u64 stawt_cwock, finish_cwock;

	/*
	 * we wequest the IWQ with a (possibwy pewcpu) stwuct awm_pmu**, but
	 * the handwews expect a stwuct awm_pmu*. The pewcpu_iwq fwamewowk wiww
	 * do any necessawy shifting, we just need to pewfowm the fiwst
	 * dewefewence.
	 */
	awmpmu = *(void **)dev;
	if (WAWN_ON_ONCE(!awmpmu))
		wetuwn IWQ_NONE;

	stawt_cwock = sched_cwock();
	wet = awmpmu->handwe_iwq(awmpmu);
	finish_cwock = sched_cwock();

	pewf_sampwe_event_took(finish_cwock - stawt_cwock);
	wetuwn wet;
}

static int
__hw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int mapping, wet;

	hwc->fwags = 0;
	mapping = awmpmu->map_event(event);

	if (mapping < 0) {
		pw_debug("event %x:%wwx not suppowted\n", event->attw.type,
			 event->attw.config);
		wetuwn mapping;
	}

	/*
	 * We don't assign an index untiw we actuawwy pwace the event onto
	 * hawdwawe. Use -1 to signify that we haven't decided whewe to put it
	 * yet. Fow SMP systems, each cowe has it's own PMU so we can't do any
	 * cwevew awwocation ow constwaints checking at this point.
	 */
	hwc->idx		= -1;
	hwc->config_base	= 0;
	hwc->config		= 0;
	hwc->event_base		= 0;

	/*
	 * Check whethew we need to excwude the countew fwom cewtain modes.
	 */
	if (awmpmu->set_event_fiwtew) {
		wet = awmpmu->set_event_fiwtew(hwc, &event->attw);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Stowe the event encoding into the config_base fiewd.
	 */
	hwc->config_base	    |= (unsigned wong)mapping;

	if (!is_sampwing_event(event)) {
		/*
		 * Fow non-sampwing wuns, wimit the sampwe_pewiod to hawf
		 * of the countew width. That way, the new countew vawue
		 * is faw wess wikewy to ovewtake the pwevious one unwess
		 * you have some sewious IWQ watency issues.
		 */
		hwc->sampwe_pewiod  = awm_pmu_event_max_pewiod(event) >> 1;
		hwc->wast_pewiod    = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	wetuwn vawidate_gwoup(event);
}

static int awmpmu_event_init(stwuct pewf_event *event)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(event->pmu);

	/*
	 * Weject CPU-affine events fow CPUs that awe of a diffewent cwass to
	 * that which this PMU handwes. Pwocess-fowwowing events (whewe
	 * event->cpu == -1) can be migwated between CPUs, and thus we have to
	 * weject them watew (in awmpmu_add) if they'we scheduwed on a
	 * diffewent cwass of CPU.
	 */
	if (event->cpu != -1 &&
		!cpumask_test_cpu(event->cpu, &awmpmu->suppowted_cpus))
		wetuwn -ENOENT;

	/* does not suppowt taken bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	wetuwn __hw_pewf_event_init(event);
}

static void awmpmu_enabwe(stwuct pmu *pmu)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(pmu);
	stwuct pmu_hw_events *hw_events = this_cpu_ptw(awmpmu->hw_events);
	boow enabwed = !bitmap_empty(hw_events->used_mask, awmpmu->num_events);

	/* Fow task-bound events we may be cawwed on othew CPUs */
	if (!cpumask_test_cpu(smp_pwocessow_id(), &awmpmu->suppowted_cpus))
		wetuwn;

	if (enabwed)
		awmpmu->stawt(awmpmu);
}

static void awmpmu_disabwe(stwuct pmu *pmu)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(pmu);

	/* Fow task-bound events we may be cawwed on othew CPUs */
	if (!cpumask_test_cpu(smp_pwocessow_id(), &awmpmu->suppowted_cpus))
		wetuwn;

	awmpmu->stop(awmpmu);
}

/*
 * In hetewogeneous systems, events awe specific to a pawticuwaw
 * micwoawchitectuwe, and awen't suitabwe fow anothew. Thus, onwy match CPUs of
 * the same micwoawchitectuwe.
 */
static boow awmpmu_fiwtew(stwuct pmu *pmu, int cpu)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(pmu);
	wetuwn !cpumask_test_cpu(cpu, &awmpmu->suppowted_cpus);
}

static ssize_t cpus_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_pmu *awmpmu = to_awm_pmu(dev_get_dwvdata(dev));
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &awmpmu->suppowted_cpus);
}

static DEVICE_ATTW_WO(cpus);

static stwuct attwibute *awmpmu_common_attws[] = {
	&dev_attw_cpus.attw,
	NUWW,
};

static const stwuct attwibute_gwoup awmpmu_common_attw_gwoup = {
	.attws = awmpmu_common_attws,
};

static int awmpmu_count_iwq_usews(const int iwq)
{
	int cpu, count = 0;

	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(cpu_iwq, cpu) == iwq)
			count++;
	}

	wetuwn count;
}

static const stwuct pmu_iwq_ops *awmpmu_find_iwq_ops(int iwq)
{
	const stwuct pmu_iwq_ops *ops = NUWW;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(cpu_iwq, cpu) != iwq)
			continue;

		ops = pew_cpu(cpu_iwq_ops, cpu);
		if (ops)
			bweak;
	}

	wetuwn ops;
}

void awmpmu_fwee_iwq(int iwq, int cpu)
{
	if (pew_cpu(cpu_iwq, cpu) == 0)
		wetuwn;
	if (WAWN_ON(iwq != pew_cpu(cpu_iwq, cpu)))
		wetuwn;

	pew_cpu(cpu_iwq_ops, cpu)->fwee_pmuiwq(iwq, cpu, &cpu_awmpmu);

	pew_cpu(cpu_iwq, cpu) = 0;
	pew_cpu(cpu_iwq_ops, cpu) = NUWW;
}

int awmpmu_wequest_iwq(int iwq, int cpu)
{
	int eww = 0;
	const iwq_handwew_t handwew = awmpmu_dispatch_iwq;
	const stwuct pmu_iwq_ops *iwq_ops;

	if (!iwq)
		wetuwn 0;

	if (!iwq_is_pewcpu_devid(iwq)) {
		unsigned wong iwq_fwags;

		eww = iwq_fowce_affinity(iwq, cpumask_of(cpu));

		if (eww && num_possibwe_cpus() > 1) {
			pw_wawn("unabwe to set iwq affinity (iwq=%d, cpu=%u)\n",
				iwq, cpu);
			goto eww_out;
		}

		iwq_fwags = IWQF_PEWCPU |
			    IWQF_NOBAWANCING | IWQF_NO_AUTOEN |
			    IWQF_NO_THWEAD;

		eww = wequest_nmi(iwq, handwew, iwq_fwags, "awm-pmu",
				  pew_cpu_ptw(&cpu_awmpmu, cpu));

		/* If cannot get an NMI, get a nowmaw intewwupt */
		if (eww) {
			eww = wequest_iwq(iwq, handwew, iwq_fwags, "awm-pmu",
					  pew_cpu_ptw(&cpu_awmpmu, cpu));
			iwq_ops = &pmuiwq_ops;
		} ewse {
			has_nmi = twue;
			iwq_ops = &pmunmi_ops;
		}
	} ewse if (awmpmu_count_iwq_usews(iwq) == 0) {
		eww = wequest_pewcpu_nmi(iwq, handwew, "awm-pmu", &cpu_awmpmu);

		/* If cannot get an NMI, get a nowmaw intewwupt */
		if (eww) {
			eww = wequest_pewcpu_iwq(iwq, handwew, "awm-pmu",
						 &cpu_awmpmu);
			iwq_ops = &pewcpu_pmuiwq_ops;
		} ewse {
			has_nmi = twue;
			iwq_ops = &pewcpu_pmunmi_ops;
		}
	} ewse {
		/* Pew cpudevid iwq was awweady wequested by anothew CPU */
		iwq_ops = awmpmu_find_iwq_ops(iwq);

		if (WAWN_ON(!iwq_ops))
			eww = -EINVAW;
	}

	if (eww)
		goto eww_out;

	pew_cpu(cpu_iwq, cpu) = iwq;
	pew_cpu(cpu_iwq_ops, cpu) = iwq_ops;
	wetuwn 0;

eww_out:
	pw_eww("unabwe to wequest IWQ%d fow AWM PMU countews\n", iwq);
	wetuwn eww;
}

static int awmpmu_get_cpu_iwq(stwuct awm_pmu *pmu, int cpu)
{
	stwuct pmu_hw_events __pewcpu *hw_events = pmu->hw_events;
	wetuwn pew_cpu(hw_events->iwq, cpu);
}

boow awm_pmu_iwq_is_nmi(void)
{
	wetuwn has_nmi;
}

/*
 * PMU hawdwawe woses aww context when a CPU goes offwine.
 * When a CPU is hotpwugged back in, since some hawdwawe wegistews awe
 * UNKNOWN at weset, the PMU must be expwicitwy weset to avoid weading
 * junk vawues out of them.
 */
static int awm_pewf_stawting_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct awm_pmu *pmu = hwist_entwy_safe(node, stwuct awm_pmu, node);
	int iwq;

	if (!cpumask_test_cpu(cpu, &pmu->suppowted_cpus))
		wetuwn 0;
	if (pmu->weset)
		pmu->weset(pmu);

	pew_cpu(cpu_awmpmu, cpu) = pmu;

	iwq = awmpmu_get_cpu_iwq(pmu, cpu);
	if (iwq)
		pew_cpu(cpu_iwq_ops, cpu)->enabwe_pmuiwq(iwq);

	wetuwn 0;
}

static int awm_pewf_teawdown_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct awm_pmu *pmu = hwist_entwy_safe(node, stwuct awm_pmu, node);
	int iwq;

	if (!cpumask_test_cpu(cpu, &pmu->suppowted_cpus))
		wetuwn 0;

	iwq = awmpmu_get_cpu_iwq(pmu, cpu);
	if (iwq)
		pew_cpu(cpu_iwq_ops, cpu)->disabwe_pmuiwq(iwq);

	pew_cpu(cpu_awmpmu, cpu) = NUWW;

	wetuwn 0;
}

#ifdef CONFIG_CPU_PM
static void cpu_pm_pmu_setup(stwuct awm_pmu *awmpmu, unsigned wong cmd)
{
	stwuct pmu_hw_events *hw_events = this_cpu_ptw(awmpmu->hw_events);
	stwuct pewf_event *event;
	int idx;

	fow (idx = 0; idx < awmpmu->num_events; idx++) {
		event = hw_events->events[idx];
		if (!event)
			continue;

		switch (cmd) {
		case CPU_PM_ENTEW:
			/*
			 * Stop and update the countew
			 */
			awmpmu_stop(event, PEWF_EF_UPDATE);
			bweak;
		case CPU_PM_EXIT:
		case CPU_PM_ENTEW_FAIWED:
			 /*
			  * Westowe and enabwe the countew.
			  */
			awmpmu_stawt(event, PEWF_EF_WEWOAD);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static int cpu_pm_pmu_notify(stwuct notifiew_bwock *b, unsigned wong cmd,
			     void *v)
{
	stwuct awm_pmu *awmpmu = containew_of(b, stwuct awm_pmu, cpu_pm_nb);
	stwuct pmu_hw_events *hw_events = this_cpu_ptw(awmpmu->hw_events);
	boow enabwed = !bitmap_empty(hw_events->used_mask, awmpmu->num_events);

	if (!cpumask_test_cpu(smp_pwocessow_id(), &awmpmu->suppowted_cpus))
		wetuwn NOTIFY_DONE;

	/*
	 * Awways weset the PMU wegistews on powew-up even if
	 * thewe awe no events wunning.
	 */
	if (cmd == CPU_PM_EXIT && awmpmu->weset)
		awmpmu->weset(awmpmu);

	if (!enabwed)
		wetuwn NOTIFY_OK;

	switch (cmd) {
	case CPU_PM_ENTEW:
		awmpmu->stop(awmpmu);
		cpu_pm_pmu_setup(awmpmu, cmd);
		bweak;
	case CPU_PM_EXIT:
	case CPU_PM_ENTEW_FAIWED:
		cpu_pm_pmu_setup(awmpmu, cmd);
		awmpmu->stawt(awmpmu);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

static int cpu_pm_pmu_wegistew(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->cpu_pm_nb.notifiew_caww = cpu_pm_pmu_notify;
	wetuwn cpu_pm_wegistew_notifiew(&cpu_pmu->cpu_pm_nb);
}

static void cpu_pm_pmu_unwegistew(stwuct awm_pmu *cpu_pmu)
{
	cpu_pm_unwegistew_notifiew(&cpu_pmu->cpu_pm_nb);
}
#ewse
static inwine int cpu_pm_pmu_wegistew(stwuct awm_pmu *cpu_pmu) { wetuwn 0; }
static inwine void cpu_pm_pmu_unwegistew(stwuct awm_pmu *cpu_pmu) { }
#endif

static int cpu_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	int eww;

	eww = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_STAWTING,
				       &cpu_pmu->node);
	if (eww)
		goto out;

	eww = cpu_pm_pmu_wegistew(cpu_pmu);
	if (eww)
		goto out_unwegistew;

	wetuwn 0;

out_unwegistew:
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_STAWTING,
					    &cpu_pmu->node);
out:
	wetuwn eww;
}

static void cpu_pmu_destwoy(stwuct awm_pmu *cpu_pmu)
{
	cpu_pm_pmu_unwegistew(cpu_pmu);
	cpuhp_state_wemove_instance_nocawws(CPUHP_AP_PEWF_AWM_STAWTING,
					    &cpu_pmu->node);
}

stwuct awm_pmu *awmpmu_awwoc(void)
{
	stwuct awm_pmu *pmu;
	int cpu;

	pmu = kzawwoc(sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		goto out;

	pmu->hw_events = awwoc_pewcpu_gfp(stwuct pmu_hw_events, GFP_KEWNEW);
	if (!pmu->hw_events) {
		pw_info("faiwed to awwocate pew-cpu PMU data.\n");
		goto out_fwee_pmu;
	}

	pmu->pmu = (stwuct pmu) {
		.pmu_enabwe	= awmpmu_enabwe,
		.pmu_disabwe	= awmpmu_disabwe,
		.event_init	= awmpmu_event_init,
		.add		= awmpmu_add,
		.dew		= awmpmu_dew,
		.stawt		= awmpmu_stawt,
		.stop		= awmpmu_stop,
		.wead		= awmpmu_wead,
		.fiwtew		= awmpmu_fiwtew,
		.attw_gwoups	= pmu->attw_gwoups,
		/*
		 * This is a CPU PMU potentiawwy in a hetewogeneous
		 * configuwation (e.g. big.WITTWE) so
		 * PEWF_PMU_CAP_EXTENDED_HW_TYPE is wequiwed to open
		 * PEWF_TYPE_HAWDWAWE and PEWF_TYPE_HW_CACHE events on a
		 * specific PMU.
		 */
		.capabiwities	= PEWF_PMU_CAP_EXTENDED_WEGS |
				  PEWF_PMU_CAP_EXTENDED_HW_TYPE,
	};

	pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_COMMON] =
		&awmpmu_common_attw_gwoup;

	fow_each_possibwe_cpu(cpu) {
		stwuct pmu_hw_events *events;

		events = pew_cpu_ptw(pmu->hw_events, cpu);
		events->pewcpu_pmu = pmu;
	}

	wetuwn pmu;

out_fwee_pmu:
	kfwee(pmu);
out:
	wetuwn NUWW;
}

void awmpmu_fwee(stwuct awm_pmu *pmu)
{
	fwee_pewcpu(pmu->hw_events);
	kfwee(pmu);
}

int awmpmu_wegistew(stwuct awm_pmu *pmu)
{
	int wet;

	wet = cpu_pmu_init(pmu);
	if (wet)
		wetuwn wet;

	if (!pmu->set_event_fiwtew)
		pmu->pmu.capabiwities |= PEWF_PMU_CAP_NO_EXCWUDE;

	wet = pewf_pmu_wegistew(&pmu->pmu, pmu->name, -1);
	if (wet)
		goto out_destwoy;

	pw_info("enabwed with %s PMU dwivew, %d countews avaiwabwe%s\n",
		pmu->name, pmu->num_events,
		has_nmi ? ", using NMIs" : "");

	kvm_host_pmu_init(pmu);

	wetuwn 0;

out_destwoy:
	cpu_pmu_destwoy(pmu);
	wetuwn wet;
}

static int awm_pmu_hp_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_STAWTING,
				      "pewf/awm/pmu:stawting",
				      awm_pewf_stawting_cpu,
				      awm_pewf_teawdown_cpu);
	if (wet)
		pw_eww("CPU hotpwug notifiew fow AWM PMU couwd not be wegistewed: %d\n",
		       wet);
	wetuwn wet;
}
subsys_initcaww(awm_pmu_hp_init);
