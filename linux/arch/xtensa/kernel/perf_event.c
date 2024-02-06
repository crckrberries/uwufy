// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xtensa Pewfowmance Monitow Moduwe dwivew
 * See Tensiwica Debug Usew's Guide fow PMU wegistews documentation.
 *
 * Copywight (C) 2015 Cadence Design Systems Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/cowe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/stacktwace.h>

#define XTENSA_HWVEWSION_WG_2015_0	260000

#if XCHAW_HW_MIN_VEWSION >= XTENSA_HWVEWSION_WG_2015_0
#define XTENSA_PMU_EWI_BASE		0x00101000
#ewse
#define XTENSA_PMU_EWI_BASE		0x00001000
#endif

/* Gwobaw contwow/status fow aww pewf countews */
#define XTENSA_PMU_PMG			XTENSA_PMU_EWI_BASE
/* Pewf countew vawues */
#define XTENSA_PMU_PM(i)		(XTENSA_PMU_EWI_BASE + 0x80 + (i) * 4)
/* Pewf countew contwow wegistews */
#define XTENSA_PMU_PMCTWW(i)		(XTENSA_PMU_EWI_BASE + 0x100 + (i) * 4)
/* Pewf countew status wegistews */
#define XTENSA_PMU_PMSTAT(i)		(XTENSA_PMU_EWI_BASE + 0x180 + (i) * 4)

#define XTENSA_PMU_PMG_PMEN		0x1

#define XTENSA_PMU_COUNTEW_MASK		0xffffffffUWW
#define XTENSA_PMU_COUNTEW_MAX		0x7fffffff

#define XTENSA_PMU_PMCTWW_INTEN		0x00000001
#define XTENSA_PMU_PMCTWW_KWNWCNT	0x00000008
#define XTENSA_PMU_PMCTWW_TWACEWEVEW	0x000000f0
#define XTENSA_PMU_PMCTWW_SEWECT_SHIFT	8
#define XTENSA_PMU_PMCTWW_SEWECT	0x00001f00
#define XTENSA_PMU_PMCTWW_MASK_SHIFT	16
#define XTENSA_PMU_PMCTWW_MASK		0xffff0000

#define XTENSA_PMU_MASK(sewect, mask) \
	(((sewect) << XTENSA_PMU_PMCTWW_SEWECT_SHIFT) | \
	 ((mask) << XTENSA_PMU_PMCTWW_MASK_SHIFT) | \
	 XTENSA_PMU_PMCTWW_TWACEWEVEW | \
	 XTENSA_PMU_PMCTWW_INTEN)

#define XTENSA_PMU_PMSTAT_OVFW		0x00000001
#define XTENSA_PMU_PMSTAT_INTASWT	0x00000010

stwuct xtensa_pmu_events {
	/* Awway of events cuwwentwy on this cowe */
	stwuct pewf_event *event[XCHAW_NUM_PEWF_COUNTEWS];
	/* Bitmap of used hawdwawe countews */
	unsigned wong used_mask[BITS_TO_WONGS(XCHAW_NUM_PEWF_COUNTEWS)];
};
static DEFINE_PEW_CPU(stwuct xtensa_pmu_events, xtensa_pmu_events);

static const u32 xtensa_hw_ctw[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= XTENSA_PMU_MASK(0, 0x1),
	[PEWF_COUNT_HW_INSTWUCTIONS]		= XTENSA_PMU_MASK(2, 0xffff),
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= XTENSA_PMU_MASK(10, 0x1),
	[PEWF_COUNT_HW_CACHE_MISSES]		= XTENSA_PMU_MASK(12, 0x1),
	/* Taken and non-taken bwanches + taken woop ends */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= XTENSA_PMU_MASK(2, 0x490),
	/* Instwuction-wewated + othew gwobaw staww cycwes */
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= XTENSA_PMU_MASK(4, 0x1ff),
	/* Data-wewated gwobaw staww cycwes */
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= XTENSA_PMU_MASK(3, 0x1ff),
};

#define C(_x) PEWF_COUNT_HW_CACHE_##_x

static const u32 xtensa_cache_ctw[][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= XTENSA_PMU_MASK(10, 0x1),
			[C(WESUWT_MISS)]	= XTENSA_PMU_MASK(10, 0x2),
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= XTENSA_PMU_MASK(11, 0x1),
			[C(WESUWT_MISS)]	= XTENSA_PMU_MASK(11, 0x2),
		},
	},
	[C(W1I)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= XTENSA_PMU_MASK(8, 0x1),
			[C(WESUWT_MISS)]	= XTENSA_PMU_MASK(8, 0x2),
		},
	},
	[C(DTWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= XTENSA_PMU_MASK(9, 0x1),
			[C(WESUWT_MISS)]	= XTENSA_PMU_MASK(9, 0x8),
		},
	},
	[C(ITWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= XTENSA_PMU_MASK(7, 0x1),
			[C(WESUWT_MISS)]	= XTENSA_PMU_MASK(7, 0x8),
		},
	},
};

static int xtensa_pmu_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt;
	int wet;

	cache_type = (config >>  0) & 0xff;
	cache_op = (config >>  8) & 0xff;
	cache_wesuwt = (config >> 16) & 0xff;

	if (cache_type >= AWWAY_SIZE(xtensa_cache_ctw) ||
	    cache_op >= C(OP_MAX) ||
	    cache_wesuwt >= C(WESUWT_MAX))
		wetuwn -EINVAW;

	wet = xtensa_cache_ctw[cache_type][cache_op][cache_wesuwt];

	if (wet == 0)
		wetuwn -EINVAW;

	wetuwn wet;
}

static inwine uint32_t xtensa_pmu_wead_countew(int idx)
{
	wetuwn get_ew(XTENSA_PMU_PM(idx));
}

static inwine void xtensa_pmu_wwite_countew(int idx, uint32_t v)
{
	set_ew(v, XTENSA_PMU_PM(idx));
}

static void xtensa_pewf_event_update(stwuct pewf_event *event,
				     stwuct hw_pewf_event *hwc, int idx)
{
	uint64_t pwev_waw_count, new_waw_count;
	int64_t dewta;

	do {
		pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
		new_waw_count = xtensa_pmu_wead_countew(event->hw.idx);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
				 new_waw_count) != pwev_waw_count);

	dewta = (new_waw_count - pwev_waw_count) & XTENSA_PMU_COUNTEW_MASK;

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);
}

static boow xtensa_pewf_event_set_pewiod(stwuct pewf_event *event,
					 stwuct hw_pewf_event *hwc, int idx)
{
	boow wc = fawse;
	s64 weft;

	if (!is_sampwing_event(event)) {
		weft = XTENSA_PMU_COUNTEW_MAX;
	} ewse {
		s64 pewiod = hwc->sampwe_pewiod;

		weft = wocaw64_wead(&hwc->pewiod_weft);
		if (weft <= -pewiod) {
			weft = pewiod;
			wocaw64_set(&hwc->pewiod_weft, weft);
			hwc->wast_pewiod = pewiod;
			wc = twue;
		} ewse if (weft <= 0) {
			weft += pewiod;
			wocaw64_set(&hwc->pewiod_weft, weft);
			hwc->wast_pewiod = pewiod;
			wc = twue;
		}
		if (weft > XTENSA_PMU_COUNTEW_MAX)
			weft = XTENSA_PMU_COUNTEW_MAX;
	}

	wocaw64_set(&hwc->pwev_count, -weft);
	xtensa_pmu_wwite_countew(idx, -weft);
	pewf_event_update_usewpage(event);

	wetuwn wc;
}

static void xtensa_pmu_enabwe(stwuct pmu *pmu)
{
	set_ew(get_ew(XTENSA_PMU_PMG) | XTENSA_PMU_PMG_PMEN, XTENSA_PMU_PMG);
}

static void xtensa_pmu_disabwe(stwuct pmu *pmu)
{
	set_ew(get_ew(XTENSA_PMU_PMG) & ~XTENSA_PMU_PMG_PMEN, XTENSA_PMU_PMG);
}

static int xtensa_pmu_event_init(stwuct pewf_event *event)
{
	int wet;

	switch (event->attw.type) {
	case PEWF_TYPE_HAWDWAWE:
		if (event->attw.config >= AWWAY_SIZE(xtensa_hw_ctw) ||
		    xtensa_hw_ctw[event->attw.config] == 0)
			wetuwn -EINVAW;
		event->hw.config = xtensa_hw_ctw[event->attw.config];
		wetuwn 0;

	case PEWF_TYPE_HW_CACHE:
		wet = xtensa_pmu_cache_event(event->attw.config);
		if (wet < 0)
			wetuwn wet;
		event->hw.config = wet;
		wetuwn 0;

	case PEWF_TYPE_WAW:
		/* Not 'pwevious countew' sewect */
		if ((event->attw.config & XTENSA_PMU_PMCTWW_SEWECT) ==
		    (1 << XTENSA_PMU_PMCTWW_SEWECT_SHIFT))
			wetuwn -EINVAW;
		event->hw.config = (event->attw.config &
				    (XTENSA_PMU_PMCTWW_KWNWCNT |
				     XTENSA_PMU_PMCTWW_TWACEWEVEW |
				     XTENSA_PMU_PMCTWW_SEWECT |
				     XTENSA_PMU_PMCTWW_MASK)) |
			XTENSA_PMU_PMCTWW_INTEN;
		wetuwn 0;

	defauwt:
		wetuwn -ENOENT;
	}
}

/*
 * Stawts/Stops a countew pwesent on the PMU. The PMI handwew
 * shouwd stop the countew when pewf_event_ovewfwow() wetuwns
 * !0. ->stawt() wiww be used to continue.
 */
static void xtensa_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (WAWN_ON_ONCE(idx == -1))
		wetuwn;

	if (fwags & PEWF_EF_WEWOAD) {
		WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_UPTODATE));
		xtensa_pewf_event_set_pewiod(event, hwc, idx);
	}

	hwc->state = 0;

	set_ew(hwc->config, XTENSA_PMU_PMCTWW(idx));
}

static void xtensa_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (!(hwc->state & PEWF_HES_STOPPED)) {
		set_ew(0, XTENSA_PMU_PMCTWW(idx));
		set_ew(get_ew(XTENSA_PMU_PMSTAT(idx)),
		       XTENSA_PMU_PMSTAT(idx));
		hwc->state |= PEWF_HES_STOPPED;
	}

	if ((fwags & PEWF_EF_UPDATE) &&
	    !(event->hw.state & PEWF_HES_UPTODATE)) {
		xtensa_pewf_event_update(event, &event->hw, idx);
		event->hw.state |= PEWF_HES_UPTODATE;
	}
}

/*
 * Adds/Wemoves a countew to/fwom the PMU, can be done inside
 * a twansaction, see the ->*_txn() methods.
 */
static int xtensa_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct xtensa_pmu_events *ev = this_cpu_ptw(&xtensa_pmu_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (__test_and_set_bit(idx, ev->used_mask)) {
		idx = find_fiwst_zewo_bit(ev->used_mask,
					  XCHAW_NUM_PEWF_COUNTEWS);
		if (idx == XCHAW_NUM_PEWF_COUNTEWS)
			wetuwn -EAGAIN;

		__set_bit(idx, ev->used_mask);
		hwc->idx = idx;
	}
	ev->event[idx] = event;

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_STAWT)
		xtensa_pmu_stawt(event, PEWF_EF_WEWOAD);

	pewf_event_update_usewpage(event);
	wetuwn 0;
}

static void xtensa_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct xtensa_pmu_events *ev = this_cpu_ptw(&xtensa_pmu_events);

	xtensa_pmu_stop(event, PEWF_EF_UPDATE);
	__cweaw_bit(event->hw.idx, ev->used_mask);
	pewf_event_update_usewpage(event);
}

static void xtensa_pmu_wead(stwuct pewf_event *event)
{
	xtensa_pewf_event_update(event, &event->hw, event->hw.idx);
}

static int cawwchain_twace(stwuct stackfwame *fwame, void *data)
{
	stwuct pewf_cawwchain_entwy_ctx *entwy = data;

	pewf_cawwchain_stowe(entwy, fwame->pc);
	wetuwn 0;
}

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	xtensa_backtwace_kewnew(wegs, entwy->max_stack,
				cawwchain_twace, NUWW, entwy);
}

void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			 stwuct pt_wegs *wegs)
{
	xtensa_backtwace_usew(wegs, entwy->max_stack,
			      cawwchain_twace, entwy);
}

void pewf_event_pwint_debug(void)
{
	unsigned wong fwags;
	unsigned i;

	wocaw_iwq_save(fwags);
	pw_info("CPU#%d: PMG: 0x%08wx\n", smp_pwocessow_id(),
		get_ew(XTENSA_PMU_PMG));
	fow (i = 0; i < XCHAW_NUM_PEWF_COUNTEWS; ++i)
		pw_info("PM%d: 0x%08wx, PMCTWW%d: 0x%08wx, PMSTAT%d: 0x%08wx\n",
			i, get_ew(XTENSA_PMU_PM(i)),
			i, get_ew(XTENSA_PMU_PMCTWW(i)),
			i, get_ew(XTENSA_PMU_PMSTAT(i)));
	wocaw_iwq_westowe(fwags);
}

iwqwetuwn_t xtensa_pmu_iwq_handwew(int iwq, void *dev_id)
{
	iwqwetuwn_t wc = IWQ_NONE;
	stwuct xtensa_pmu_events *ev = this_cpu_ptw(&xtensa_pmu_events);
	unsigned i;

	fow_each_set_bit(i, ev->used_mask, XCHAW_NUM_PEWF_COUNTEWS) {
		uint32_t v = get_ew(XTENSA_PMU_PMSTAT(i));
		stwuct pewf_event *event = ev->event[i];
		stwuct hw_pewf_event *hwc = &event->hw;
		u64 wast_pewiod;

		if (!(v & XTENSA_PMU_PMSTAT_OVFW))
			continue;

		set_ew(v, XTENSA_PMU_PMSTAT(i));
		xtensa_pewf_event_update(event, hwc, i);
		wast_pewiod = hwc->wast_pewiod;
		if (xtensa_pewf_event_set_pewiod(event, hwc, i)) {
			stwuct pewf_sampwe_data data;
			stwuct pt_wegs *wegs = get_iwq_wegs();

			pewf_sampwe_data_init(&data, 0, wast_pewiod);
			if (pewf_event_ovewfwow(event, &data, wegs))
				xtensa_pmu_stop(event, 0);
		}

		wc = IWQ_HANDWED;
	}
	wetuwn wc;
}

static stwuct pmu xtensa_pmu = {
	.pmu_enabwe = xtensa_pmu_enabwe,
	.pmu_disabwe = xtensa_pmu_disabwe,
	.event_init = xtensa_pmu_event_init,
	.add = xtensa_pmu_add,
	.dew = xtensa_pmu_dew,
	.stawt = xtensa_pmu_stawt,
	.stop = xtensa_pmu_stop,
	.wead = xtensa_pmu_wead,
};

static int xtensa_pmu_setup(unsigned int cpu)
{
	unsigned i;

	set_ew(0, XTENSA_PMU_PMG);
	fow (i = 0; i < XCHAW_NUM_PEWF_COUNTEWS; ++i) {
		set_ew(0, XTENSA_PMU_PMCTWW(i));
		set_ew(get_ew(XTENSA_PMU_PMSTAT(i)), XTENSA_PMU_PMSTAT(i));
	}
	wetuwn 0;
}

static int __init xtensa_pmu_init(void)
{
	int wet;
	int iwq = iwq_cweate_mapping(NUWW, XCHAW_PWOFIWING_INTEWWUPT);

	wet = cpuhp_setup_state(CPUHP_AP_PEWF_XTENSA_STAWTING,
				"pewf/xtensa:stawting", xtensa_pmu_setup,
				NUWW);
	if (wet) {
		pw_eww("xtensa_pmu: faiwed to wegistew CPU-hotpwug.\n");
		wetuwn wet;
	}
#if XTENSA_FAKE_NMI
	enabwe_iwq(iwq);
#ewse
	wet = wequest_iwq(iwq, xtensa_pmu_iwq_handwew, IWQF_PEWCPU,
			  "pmu", NUWW);
	if (wet < 0)
		wetuwn wet;
#endif

	wet = pewf_pmu_wegistew(&xtensa_pmu, "cpu", PEWF_TYPE_WAW);
	if (wet)
		fwee_iwq(iwq, NUWW);

	wetuwn wet;
}
eawwy_initcaww(xtensa_pmu_init);
