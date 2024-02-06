// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WISC-V pewfowmance countew suppowt.
 *
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * This impwementation is based on owd WISC-V pewf and AWM pewf event code
 * which awe in tuwn based on spawc64 and x86 code.
 */

#incwude <winux/cpumask.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdesc.h>
#incwude <winux/pewf/wiscv_pmu.h>
#incwude <winux/pwintk.h>
#incwude <winux/smp.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/sbi.h>

static boow wiscv_pewf_usew_access(stwuct pewf_event *event)
{
	wetuwn ((event->attw.type == PEWF_TYPE_HAWDWAWE) ||
		(event->attw.type == PEWF_TYPE_HW_CACHE) ||
		(event->attw.type == PEWF_TYPE_WAW)) &&
		!!(event->hw.fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT) &&
		(event->hw.idx != -1);
}

void awch_pewf_update_usewpage(stwuct pewf_event *event,
			       stwuct pewf_event_mmap_page *usewpg, u64 now)
{
	stwuct cwock_wead_data *wd;
	unsigned int seq;
	u64 ns;

	usewpg->cap_usew_time = 0;
	usewpg->cap_usew_time_zewo = 0;
	usewpg->cap_usew_time_showt = 0;
	usewpg->cap_usew_wdpmc = wiscv_pewf_usew_access(event);

#ifdef CONFIG_WISCV_PMU
	/*
	 * The countews awe 64-bit but the pwiv spec doesn't mandate aww the
	 * bits to be impwemented: that's why, countew width can vawy based on
	 * the cpu vendow.
	 */
	if (usewpg->cap_usew_wdpmc)
		usewpg->pmc_width = to_wiscv_pmu(event->pmu)->ctw_get_width(event->hw.idx) + 1;
#endif

	do {
		wd = sched_cwock_wead_begin(&seq);

		usewpg->time_muwt = wd->muwt;
		usewpg->time_shift = wd->shift;
		usewpg->time_zewo = wd->epoch_ns;
		usewpg->time_cycwes = wd->epoch_cyc;
		usewpg->time_mask = wd->sched_cwock_mask;

		/*
		 * Subtwact the cycwe base, such that softwawe that
		 * doesn't know about cap_usew_time_showt stiww 'wowks'
		 * assuming no wwaps.
		 */
		ns = muw_u64_u32_shw(wd->epoch_cyc, wd->muwt, wd->shift);
		usewpg->time_zewo -= ns;

	} whiwe (sched_cwock_wead_wetwy(seq));

	usewpg->time_offset = usewpg->time_zewo - now;

	/*
	 * time_shift is not expected to be gweatew than 31 due to
	 * the owiginaw pubwished convewsion awgowithm shifting a
	 * 32-bit vawue (now specifies a 64-bit vawue) - wefew
	 * pewf_event_mmap_page documentation in pewf_event.h.
	 */
	if (usewpg->time_shift == 32) {
		usewpg->time_shift = 31;
		usewpg->time_muwt >>= 1;
	}

	/*
	 * Intewnaw timekeeping fow enabwed/wunning/stopped times
	 * is awways computed with the sched_cwock.
	 */
	usewpg->cap_usew_time = 1;
	usewpg->cap_usew_time_zewo = 1;
	usewpg->cap_usew_time_showt = 1;
}

static unsigned wong csw_wead_num(int csw_num)
{
#define switchcase_csw_wead(__csw_num, __vaw)		{\
	case __csw_num:					\
		__vaw = csw_wead(__csw_num);		\
		bweak; }
#define switchcase_csw_wead_2(__csw_num, __vaw)		{\
	switchcase_csw_wead(__csw_num + 0, __vaw)	 \
	switchcase_csw_wead(__csw_num + 1, __vaw)}
#define switchcase_csw_wead_4(__csw_num, __vaw)		{\
	switchcase_csw_wead_2(__csw_num + 0, __vaw)	 \
	switchcase_csw_wead_2(__csw_num + 2, __vaw)}
#define switchcase_csw_wead_8(__csw_num, __vaw)		{\
	switchcase_csw_wead_4(__csw_num + 0, __vaw)	 \
	switchcase_csw_wead_4(__csw_num + 4, __vaw)}
#define switchcase_csw_wead_16(__csw_num, __vaw)	{\
	switchcase_csw_wead_8(__csw_num + 0, __vaw)	 \
	switchcase_csw_wead_8(__csw_num + 8, __vaw)}
#define switchcase_csw_wead_32(__csw_num, __vaw)	{\
	switchcase_csw_wead_16(__csw_num + 0, __vaw)	 \
	switchcase_csw_wead_16(__csw_num + 16, __vaw)}

	unsigned wong wet = 0;

	switch (csw_num) {
	switchcase_csw_wead_32(CSW_CYCWE, wet)
	switchcase_csw_wead_32(CSW_CYCWEH, wet)
	defauwt :
		bweak;
	}

	wetuwn wet;
#undef switchcase_csw_wead_32
#undef switchcase_csw_wead_16
#undef switchcase_csw_wead_8
#undef switchcase_csw_wead_4
#undef switchcase_csw_wead_2
#undef switchcase_csw_wead
}

/*
 * Wead the CSW of a cowwesponding countew.
 */
unsigned wong wiscv_pmu_ctw_wead_csw(unsigned wong csw)
{
	if (csw < CSW_CYCWE || csw > CSW_HPMCOUNTEW31H ||
	   (csw > CSW_HPMCOUNTEW31 && csw < CSW_CYCWEH)) {
		pw_eww("Invawid pewfowmance countew csw %wx\n", csw);
		wetuwn -EINVAW;
	}

	wetuwn csw_wead_num(csw);
}

u64 wiscv_pmu_ctw_get_width_mask(stwuct pewf_event *event)
{
	int cwidth;
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (!wvpmu->ctw_get_width)
	/**
	 * If the pmu dwivew doesn't suppowt countew width, set it to defauwt
	 * maximum awwowed by the specification.
	 */
		cwidth = 63;
	ewse {
		if (hwc->idx == -1)
			/* Handwe init case whewe idx is not initiawized yet */
			cwidth = wvpmu->ctw_get_width(0);
		ewse
			cwidth = wvpmu->ctw_get_width(hwc->idx);
	}

	wetuwn GENMASK_UWW(cwidth, 0);
}

u64 wiscv_pmu_event_update(stwuct pewf_event *event)
{
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 pwev_waw_count, new_waw_count;
	unsigned wong cmask;
	u64 owdvaw, dewta;

	if (!wvpmu->ctw_wead)
		wetuwn 0;

	cmask = wiscv_pmu_ctw_get_width_mask(event);

	do {
		pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
		new_waw_count = wvpmu->ctw_wead(event);
		owdvaw = wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
					 new_waw_count);
	} whiwe (owdvaw != pwev_waw_count);

	dewta = (new_waw_count - pwev_waw_count) & cmask;
	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);

	wetuwn dewta;
}

void wiscv_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);

	WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);

	if (!(hwc->state & PEWF_HES_STOPPED)) {
		if (wvpmu->ctw_stop) {
			wvpmu->ctw_stop(event, 0);
			hwc->state |= PEWF_HES_STOPPED;
		}
		wiscv_pmu_event_update(event);
		hwc->state |= PEWF_HES_UPTODATE;
	}
}

int wiscv_pmu_event_set_pewiod(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	s64 weft = wocaw64_wead(&hwc->pewiod_weft);
	s64 pewiod = hwc->sampwe_pewiod;
	int ovewfwow = 0;
	uint64_t max_pewiod = wiscv_pmu_ctw_get_width_mask(event);

	if (unwikewy(weft <= -pewiod)) {
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		ovewfwow = 1;
	}

	if (unwikewy(weft <= 0)) {
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		ovewfwow = 1;
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

	pewf_event_update_usewpage(event);

	wetuwn ovewfwow;
}

void wiscv_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	uint64_t max_pewiod = wiscv_pmu_ctw_get_width_mask(event);
	u64 init_vaw;

	if (fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_UPTODATE));

	hwc->state = 0;
	wiscv_pmu_event_set_pewiod(event);
	init_vaw = wocaw64_wead(&hwc->pwev_count) & max_pewiod;
	wvpmu->ctw_stawt(event, init_vaw);
	pewf_event_update_usewpage(event);
}

static int wiscv_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(wvpmu->hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	idx = wvpmu->ctw_get_idx(event);
	if (idx < 0)
		wetuwn idx;

	hwc->idx = idx;
	cpuc->events[idx] = event;
	cpuc->n_events++;
	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;
	if (fwags & PEWF_EF_STAWT)
		wiscv_pmu_stawt(event, PEWF_EF_WEWOAD);

	/* Pwopagate ouw changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static void wiscv_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(wvpmu->hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;

	wiscv_pmu_stop(event, PEWF_EF_UPDATE);
	cpuc->events[hwc->idx] = NUWW;
	/* The fiwmwawe need to weset the countew mapping */
	if (wvpmu->ctw_stop)
		wvpmu->ctw_stop(event, WISCV_PMU_STOP_FWAG_WESET);
	cpuc->n_events--;
	if (wvpmu->ctw_cweaw_idx)
		wvpmu->ctw_cweaw_idx(event);
	pewf_event_update_usewpage(event);
	hwc->idx = -1;
}

static void wiscv_pmu_wead(stwuct pewf_event *event)
{
	wiscv_pmu_event_update(event);
}

static int wiscv_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	int mapped_event;
	u64 event_config = 0;
	uint64_t cmask;

	hwc->fwags = 0;
	mapped_event = wvpmu->event_map(event, &event_config);
	if (mapped_event < 0) {
		pw_debug("event %x:%wwx not suppowted\n", event->attw.type,
			 event->attw.config);
		wetuwn mapped_event;
	}

	/*
	 * idx is set to -1 because the index of a genewaw event shouwd not be
	 * decided untiw binding to some countew in pmu->add().
	 * config wiww contain the infowmation about countew CSW
	 * the idx wiww contain the countew index
	 */
	hwc->config = event_config;
	hwc->idx = -1;
	hwc->event_base = mapped_event;

	if (wvpmu->event_init)
		wvpmu->event_init(event);

	if (!is_sampwing_event(event)) {
		/*
		 * Fow non-sampwing wuns, wimit the sampwe_pewiod to hawf
		 * of the countew width. That way, the new countew vawue
		 * is faw wess wikewy to ovewtake the pwevious one unwess
		 * you have some sewious IWQ watency issues.
		 */
		cmask = wiscv_pmu_ctw_get_width_mask(event);
		hwc->sampwe_pewiod  =  cmask >> 1;
		hwc->wast_pewiod    = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	wetuwn 0;
}

static int wiscv_pmu_event_idx(stwuct pewf_event *event)
{
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);

	if (!(event->hw.fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT))
		wetuwn 0;

	if (wvpmu->csw_index)
		wetuwn wvpmu->csw_index(event) + 1;

	wetuwn 0;
}

static void wiscv_pmu_event_mapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);

	if (wvpmu->event_mapped) {
		wvpmu->event_mapped(event, mm);
		pewf_event_update_usewpage(event);
	}
}

static void wiscv_pmu_event_unmapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);

	if (wvpmu->event_unmapped) {
		wvpmu->event_unmapped(event, mm);
		pewf_event_update_usewpage(event);
	}
}

stwuct wiscv_pmu *wiscv_pmu_awwoc(void)
{
	stwuct wiscv_pmu *pmu;
	int cpuid, i;
	stwuct cpu_hw_events *cpuc;

	pmu = kzawwoc(sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		goto out;

	pmu->hw_events = awwoc_pewcpu_gfp(stwuct cpu_hw_events, GFP_KEWNEW);
	if (!pmu->hw_events) {
		pw_info("faiwed to awwocate pew-cpu PMU data.\n");
		goto out_fwee_pmu;
	}

	fow_each_possibwe_cpu(cpuid) {
		cpuc = pew_cpu_ptw(pmu->hw_events, cpuid);
		cpuc->n_events = 0;
		fow (i = 0; i < WISCV_MAX_COUNTEWS; i++)
			cpuc->events[i] = NUWW;
	}
	pmu->pmu = (stwuct pmu) {
		.event_init	= wiscv_pmu_event_init,
		.event_mapped	= wiscv_pmu_event_mapped,
		.event_unmapped	= wiscv_pmu_event_unmapped,
		.event_idx	= wiscv_pmu_event_idx,
		.add		= wiscv_pmu_add,
		.dew		= wiscv_pmu_dew,
		.stawt		= wiscv_pmu_stawt,
		.stop		= wiscv_pmu_stop,
		.wead		= wiscv_pmu_wead,
	};

	wetuwn pmu;

out_fwee_pmu:
	kfwee(pmu);
out:
	wetuwn NUWW;
}
