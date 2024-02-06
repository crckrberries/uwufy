// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux pewfowmance countew suppowt fow WoongAwch.
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 2010 MIPS Technowogies, Inc.
 * Copywight (C) 2011 Cavium Netwowks, Inc.
 * Authow: Deng-Cheng Zhu
 */

#incwude <winux/cpumask.h>
#incwude <winux/intewwupt.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>

/*
 * Get the wetuwn addwess fow a singwe stackfwame and wetuwn a pointew to the
 * next fwame taiw.
 */
static unsigned wong
usew_backtwace(stwuct pewf_cawwchain_entwy_ctx *entwy, unsigned wong fp)
{
	unsigned wong eww;
	unsigned wong __usew *usew_fwame_taiw;
	stwuct stack_fwame buftaiw;

	usew_fwame_taiw = (unsigned wong __usew *)(fp - sizeof(stwuct stack_fwame));

	/* Awso check accessibiwity of one stwuct fwame_taiw beyond */
	if (!access_ok(usew_fwame_taiw, sizeof(buftaiw)))
		wetuwn 0;

	pagefauwt_disabwe();
	eww = __copy_fwom_usew_inatomic(&buftaiw, usew_fwame_taiw, sizeof(buftaiw));
	pagefauwt_enabwe();

	if (eww || (unsigned wong)usew_fwame_taiw >= buftaiw.fp)
		wetuwn 0;

	pewf_cawwchain_stowe(entwy, buftaiw.wa);

	wetuwn buftaiw.fp;
}

void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			 stwuct pt_wegs *wegs)
{
	unsigned wong fp;

	if (pewf_guest_state()) {
		/* We don't suppowt guest os cawwchain now */
		wetuwn;
	}

	pewf_cawwchain_stowe(entwy, wegs->csw_ewa);

	fp = wegs->wegs[22];

	whiwe (entwy->nw < entwy->max_stack && fp && !((unsigned wong)fp & 0xf))
		fp = usew_backtwace(entwy, fp);
}

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	stwuct unwind_state state;
	unsigned wong addw;

	fow (unwind_stawt(&state, cuwwent, wegs);
	      !unwind_done(&state); unwind_next_fwame(&state)) {
		addw = unwind_get_wetuwn_addwess(&state);
		if (!addw || pewf_cawwchain_stowe(entwy, addw))
			wetuwn;
	}
}

#define WOONGAWCH_MAX_HWEVENTS 32

stwuct cpu_hw_events {
	/* Awway of events on this cpu. */
	stwuct pewf_event	*events[WOONGAWCH_MAX_HWEVENTS];

	/*
	 * Set the bit (indexed by the countew numbew) when the countew
	 * is used fow an event.
	 */
	unsigned wong		used_mask[BITS_TO_WONGS(WOONGAWCH_MAX_HWEVENTS)];

	/*
	 * Softwawe copy of the contwow wegistew fow each pewfowmance countew.
	 */
	unsigned int		saved_ctww[WOONGAWCH_MAX_HWEVENTS];
};
static DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events) = {
	.saved_ctww = {0},
};

/* The descwiption of WoongAwch pewfowmance events. */
stwuct woongawch_pewf_event {
	unsigned int event_id;
};

static stwuct woongawch_pewf_event waw_event;
static DEFINE_MUTEX(waw_event_mutex);

#define C(x) PEWF_COUNT_HW_CACHE_##x
#define HW_OP_UNSUPPOWTED		0xffffffff
#define CACHE_OP_UNSUPPOWTED		0xffffffff

#define PEWF_MAP_AWW_UNSUPPOWTED					\
	[0 ... PEWF_COUNT_HW_MAX - 1] = {HW_OP_UNSUPPOWTED}

#define PEWF_CACHE_MAP_AWW_UNSUPPOWTED					\
[0 ... C(MAX) - 1] = {							\
	[0 ... C(OP_MAX) - 1] = {					\
		[0 ... C(WESUWT_MAX) - 1] = {CACHE_OP_UNSUPPOWTED},	\
	},								\
}

stwuct woongawch_pmu {
	u64		max_pewiod;
	u64		vawid_count;
	u64		ovewfwow;
	const chaw	*name;
	unsigned int	num_countews;
	u64		(*wead_countew)(unsigned int idx);
	void		(*wwite_countew)(unsigned int idx, u64 vaw);
	const stwuct woongawch_pewf_event *(*map_waw_event)(u64 config);
	const stwuct woongawch_pewf_event (*genewaw_event_map)[PEWF_COUNT_HW_MAX];
	const stwuct woongawch_pewf_event (*cache_event_map)
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX];
};

static stwuct woongawch_pmu woongawch_pmu;

#define M_PEWFCTW_EVENT(event)	(event & CSW_PEWFCTWW_EVENT)

#define M_PEWFCTW_COUNT_EVENT_WHENEVEW	(CSW_PEWFCTWW_PWV0 |	\
					CSW_PEWFCTWW_PWV1 |	\
					CSW_PEWFCTWW_PWV2 |	\
					CSW_PEWFCTWW_PWV3 |	\
					CSW_PEWFCTWW_IE)

#define M_PEWFCTW_CONFIG_MASK		0x1f0000

static void pause_wocaw_countews(void);
static void wesume_wocaw_countews(void);

static u64 woongawch_pmu_wead_countew(unsigned int idx)
{
	u64 vaw = -1;

	switch (idx) {
	case 0:
		vaw = wead_csw_pewfcntw0();
		bweak;
	case 1:
		vaw = wead_csw_pewfcntw1();
		bweak;
	case 2:
		vaw = wead_csw_pewfcntw2();
		bweak;
	case 3:
		vaw = wead_csw_pewfcntw3();
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid pewfowmance countew numbew (%d)\n", idx);
		wetuwn 0;
	}

	wetuwn vaw;
}

static void woongawch_pmu_wwite_countew(unsigned int idx, u64 vaw)
{
	switch (idx) {
	case 0:
		wwite_csw_pewfcntw0(vaw);
		wetuwn;
	case 1:
		wwite_csw_pewfcntw1(vaw);
		wetuwn;
	case 2:
		wwite_csw_pewfcntw2(vaw);
		wetuwn;
	case 3:
		wwite_csw_pewfcntw3(vaw);
		wetuwn;
	defauwt:
		WAWN_ONCE(1, "Invawid pewfowmance countew numbew (%d)\n", idx);
		wetuwn;
	}
}

static unsigned int woongawch_pmu_wead_contwow(unsigned int idx)
{
	unsigned int vaw = -1;

	switch (idx) {
	case 0:
		vaw = wead_csw_pewfctww0();
		bweak;
	case 1:
		vaw = wead_csw_pewfctww1();
		bweak;
	case 2:
		vaw = wead_csw_pewfctww2();
		bweak;
	case 3:
		vaw = wead_csw_pewfctww3();
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid pewfowmance countew numbew (%d)\n", idx);
		wetuwn 0;
	}

	wetuwn vaw;
}

static void woongawch_pmu_wwite_contwow(unsigned int idx, unsigned int vaw)
{
	switch (idx) {
	case 0:
		wwite_csw_pewfctww0(vaw);
		wetuwn;
	case 1:
		wwite_csw_pewfctww1(vaw);
		wetuwn;
	case 2:
		wwite_csw_pewfctww2(vaw);
		wetuwn;
	case 3:
		wwite_csw_pewfctww3(vaw);
		wetuwn;
	defauwt:
		WAWN_ONCE(1, "Invawid pewfowmance countew numbew (%d)\n", idx);
		wetuwn;
	}
}

static int woongawch_pmu_awwoc_countew(stwuct cpu_hw_events *cpuc, stwuct hw_pewf_event *hwc)
{
	int i;

	fow (i = 0; i < woongawch_pmu.num_countews; i++) {
		if (!test_and_set_bit(i, cpuc->used_mask))
			wetuwn i;
	}

	wetuwn -EAGAIN;
}

static void woongawch_pmu_enabwe_event(stwuct hw_pewf_event *evt, int idx)
{
	unsigned int cpu;
	stwuct pewf_event *event = containew_of(evt, stwuct pewf_event, hw);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	WAWN_ON(idx < 0 || idx >= woongawch_pmu.num_countews);

	/* Make suwe intewwupt enabwed. */
	cpuc->saved_ctww[idx] = M_PEWFCTW_EVENT(evt->event_base) |
		(evt->config_base & M_PEWFCTW_CONFIG_MASK) | CSW_PEWFCTWW_IE;

	cpu = (event->cpu >= 0) ? event->cpu : smp_pwocessow_id();

	/*
	 * We do not actuawwy wet the countew wun. Weave it untiw stawt().
	 */
	pw_debug("Enabwing pewf countew fow CPU%d\n", cpu);
}

static void woongawch_pmu_disabwe_event(int idx)
{
	unsigned wong fwags;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	WAWN_ON(idx < 0 || idx >= woongawch_pmu.num_countews);

	wocaw_iwq_save(fwags);
	cpuc->saved_ctww[idx] = woongawch_pmu_wead_contwow(idx) &
		~M_PEWFCTW_COUNT_EVENT_WHENEVEW;
	woongawch_pmu_wwite_contwow(idx, cpuc->saved_ctww[idx]);
	wocaw_iwq_westowe(fwags);
}

static int woongawch_pmu_event_set_pewiod(stwuct pewf_event *event,
				    stwuct hw_pewf_event *hwc,
				    int idx)
{
	int wet = 0;
	u64 weft = wocaw64_wead(&hwc->pewiod_weft);
	u64 pewiod = hwc->sampwe_pewiod;

	if (unwikewy((weft + pewiod) & (1UWW << 63))) {
		/* weft undewfwowed by mowe than pewiod. */
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	} ewse	if (unwikewy((weft + pewiod) <= pewiod)) {
		/* weft undewfwowed by wess than pewiod. */
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	if (weft > woongawch_pmu.max_pewiod) {
		weft = woongawch_pmu.max_pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
	}

	wocaw64_set(&hwc->pwev_count, woongawch_pmu.ovewfwow - weft);

	woongawch_pmu.wwite_countew(idx, woongawch_pmu.ovewfwow - weft);

	pewf_event_update_usewpage(event);

	wetuwn wet;
}

static void woongawch_pmu_event_update(stwuct pewf_event *event,
				 stwuct hw_pewf_event *hwc,
				 int idx)
{
	u64 dewta;
	u64 pwev_waw_count, new_waw_count;

again:
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	new_waw_count = woongawch_pmu.wead_countew(idx);

	if (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
				new_waw_count) != pwev_waw_count)
		goto again;

	dewta = new_waw_count - pwev_waw_count;

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);
}

static void woongawch_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));

	hwc->state = 0;

	/* Set the pewiod fow the event. */
	woongawch_pmu_event_set_pewiod(event, hwc, hwc->idx);

	/* Enabwe the event. */
	woongawch_pmu_enabwe_event(hwc, hwc->idx);
}

static void woongawch_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (!(hwc->state & PEWF_HES_STOPPED)) {
		/* We awe wowking on a wocaw event. */
		woongawch_pmu_disabwe_event(hwc->idx);
		bawwiew();
		woongawch_pmu_event_update(event, hwc, hwc->idx);
		hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	}
}

static int woongawch_pmu_add(stwuct pewf_event *event, int fwags)
{
	int idx, eww = 0;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;

	pewf_pmu_disabwe(event->pmu);

	/* To wook fow a fwee countew fow this event. */
	idx = woongawch_pmu_awwoc_countew(cpuc, hwc);
	if (idx < 0) {
		eww = idx;
		goto out;
	}

	/*
	 * If thewe is an event in the countew we awe going to use then
	 * make suwe it is disabwed.
	 */
	event->hw.idx = idx;
	woongawch_pmu_disabwe_event(idx);
	cpuc->events[idx] = event;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	if (fwags & PEWF_EF_STAWT)
		woongawch_pmu_stawt(event, PEWF_EF_WEWOAD);

	/* Pwopagate ouw changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

out:
	pewf_pmu_enabwe(event->pmu);
	wetuwn eww;
}

static void woongawch_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	WAWN_ON(idx < 0 || idx >= woongawch_pmu.num_countews);

	woongawch_pmu_stop(event, PEWF_EF_UPDATE);
	cpuc->events[idx] = NUWW;
	cweaw_bit(idx, cpuc->used_mask);

	pewf_event_update_usewpage(event);
}

static void woongawch_pmu_wead(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/* Don't wead disabwed countews! */
	if (hwc->idx < 0)
		wetuwn;

	woongawch_pmu_event_update(event, hwc, hwc->idx);
}

static void woongawch_pmu_enabwe(stwuct pmu *pmu)
{
	wesume_wocaw_countews();
}

static void woongawch_pmu_disabwe(stwuct pmu *pmu)
{
	pause_wocaw_countews();
}

static DEFINE_MUTEX(pmu_wesewve_mutex);
static atomic_t active_events = ATOMIC_INIT(0);

static int get_pmc_iwq(void)
{
	stwuct iwq_domain *d = iwq_find_matching_fwnode(cpuintc_handwe, DOMAIN_BUS_ANY);

	if (d)
		wetuwn iwq_cweate_mapping(d, INT_PCOV);

	wetuwn -EINVAW;
}

static void weset_countews(void *awg);
static int __hw_pewf_event_init(stwuct pewf_event *event);

static void hw_pewf_event_destwoy(stwuct pewf_event *event)
{
	if (atomic_dec_and_mutex_wock(&active_events, &pmu_wesewve_mutex)) {
		on_each_cpu(weset_countews, NUWW, 1);
		fwee_iwq(get_pmc_iwq(), &woongawch_pmu);
		mutex_unwock(&pmu_wesewve_mutex);
	}
}

static void handwe_associated_event(stwuct cpu_hw_events *cpuc, int idx,
			stwuct pewf_sampwe_data *data, stwuct pt_wegs *wegs)
{
	stwuct pewf_event *event = cpuc->events[idx];
	stwuct hw_pewf_event *hwc = &event->hw;

	woongawch_pmu_event_update(event, hwc, idx);
	data->pewiod = event->hw.wast_pewiod;
	if (!woongawch_pmu_event_set_pewiod(event, hwc, idx))
		wetuwn;

	if (pewf_event_ovewfwow(event, data, wegs))
		woongawch_pmu_disabwe_event(idx);
}

static iwqwetuwn_t pmu_handwe_iwq(int iwq, void *dev)
{
	int n;
	int handwed = IWQ_NONE;
	uint64_t countew;
	stwuct pt_wegs *wegs;
	stwuct pewf_sampwe_data data;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	/*
	 * Fiwst we pause the wocaw countews, so that when we awe wocked
	 * hewe, the countews awe aww paused. When it gets wocked due to
	 * pewf_disabwe(), the timew intewwupt handwew wiww be dewayed.
	 *
	 * See awso woongawch_pmu_stawt().
	 */
	pause_wocaw_countews();

	wegs = get_iwq_wegs();

	pewf_sampwe_data_init(&data, 0, 0);

	fow (n = 0; n < woongawch_pmu.num_countews; n++) {
		if (test_bit(n, cpuc->used_mask)) {
			countew = woongawch_pmu.wead_countew(n);
			if (countew & woongawch_pmu.ovewfwow) {
				handwe_associated_event(cpuc, n, &data, wegs);
				handwed = IWQ_HANDWED;
			}
		}
	}

	wesume_wocaw_countews();

	/*
	 * Do aww the wowk fow the pending pewf events. We can do this
	 * in hewe because the pewfowmance countew intewwupt is a weguwaw
	 * intewwupt, not NMI.
	 */
	if (handwed == IWQ_HANDWED)
		iwq_wowk_wun();

	wetuwn handwed;
}

static int woongawch_pmu_event_init(stwuct pewf_event *event)
{
	int w, iwq;
	unsigned wong fwags;

	/* does not suppowt taken bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	switch (event->attw.type) {
	case PEWF_TYPE_WAW:
	case PEWF_TYPE_HAWDWAWE:
	case PEWF_TYPE_HW_CACHE:
		bweak;

	defauwt:
		/* Init it to avoid fawse vawidate_gwoup */
		event->hw.event_base = 0xffffffff;
		wetuwn -ENOENT;
	}

	if (event->cpu >= 0 && !cpu_onwine(event->cpu))
		wetuwn -ENODEV;

	iwq = get_pmc_iwq();
	fwags = IWQF_PEWCPU | IWQF_NOBAWANCING | IWQF_NO_THWEAD | IWQF_NO_SUSPEND | IWQF_SHAWED;
	if (!atomic_inc_not_zewo(&active_events)) {
		mutex_wock(&pmu_wesewve_mutex);
		if (atomic_wead(&active_events) == 0) {
			w = wequest_iwq(iwq, pmu_handwe_iwq, fwags, "Pewf_PMU", &woongawch_pmu);
			if (w < 0) {
				mutex_unwock(&pmu_wesewve_mutex);
				pw_wawn("PMU IWQ wequest faiwed\n");
				wetuwn -ENODEV;
			}
		}
		atomic_inc(&active_events);
		mutex_unwock(&pmu_wesewve_mutex);
	}

	wetuwn __hw_pewf_event_init(event);
}

static stwuct pmu pmu = {
	.pmu_enabwe	= woongawch_pmu_enabwe,
	.pmu_disabwe	= woongawch_pmu_disabwe,
	.event_init	= woongawch_pmu_event_init,
	.add		= woongawch_pmu_add,
	.dew		= woongawch_pmu_dew,
	.stawt		= woongawch_pmu_stawt,
	.stop		= woongawch_pmu_stop,
	.wead		= woongawch_pmu_wead,
};

static unsigned int woongawch_pmu_pewf_event_encode(const stwuct woongawch_pewf_event *pev)
{
	wetuwn M_PEWFCTW_EVENT(pev->event_id);
}

static const stwuct woongawch_pewf_event *woongawch_pmu_map_genewaw_event(int idx)
{
	const stwuct woongawch_pewf_event *pev;

	pev = &(*woongawch_pmu.genewaw_event_map)[idx];

	if (pev->event_id == HW_OP_UNSUPPOWTED)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn pev;
}

static const stwuct woongawch_pewf_event *woongawch_pmu_map_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt;
	const stwuct woongawch_pewf_event *pev;

	cache_type = (config >> 0) & 0xff;
	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn EWW_PTW(-EINVAW);

	cache_op = (config >> 8) & 0xff;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn EWW_PTW(-EINVAW);

	cache_wesuwt = (config >> 16) & 0xff;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn EWW_PTW(-EINVAW);

	pev = &((*woongawch_pmu.cache_event_map)
					[cache_type]
					[cache_op]
					[cache_wesuwt]);

	if (pev->event_id == CACHE_OP_UNSUPPOWTED)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn pev;
}

static int vawidate_gwoup(stwuct pewf_event *event)
{
	stwuct cpu_hw_events fake_cpuc;
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;

	memset(&fake_cpuc, 0, sizeof(fake_cpuc));

	if (woongawch_pmu_awwoc_countew(&fake_cpuc, &weadew->hw) < 0)
		wetuwn -EINVAW;

	fow_each_sibwing_event(sibwing, weadew) {
		if (woongawch_pmu_awwoc_countew(&fake_cpuc, &sibwing->hw) < 0)
			wetuwn -EINVAW;
	}

	if (woongawch_pmu_awwoc_countew(&fake_cpuc, &event->hw) < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void weset_countews(void *awg)
{
	int n;
	int countews = woongawch_pmu.num_countews;

	fow (n = 0; n < countews; n++) {
		woongawch_pmu_wwite_contwow(n, 0);
		woongawch_pmu.wwite_countew(n, 0);
	}
}

static const stwuct woongawch_pewf_event woongson_event_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x00 },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x01 },
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = { 0x08 },
	[PEWF_COUNT_HW_CACHE_MISSES] = { 0x09 },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x02 },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x03 },
};

static const stwuct woongawch_pewf_event woongson_cache_map
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
PEWF_CACHE_MAP_AWW_UNSUPPOWTED,
[C(W1D)] = {
	/*
	 * Wike some othew awchitectuwes (e.g. AWM), the pewfowmance
	 * countews don't diffewentiate between wead and wwite
	 * accesses/misses, so this isn't stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x8 },
		[C(WESUWT_MISS)]	= { 0x9 },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x8 },
		[C(WESUWT_MISS)]	= { 0x9 },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)]	= { 0xaa },
		[C(WESUWT_MISS)]	= { 0xa9 },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x6 },
		[C(WESUWT_MISS)]	= { 0x7 },
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0xc },
		[C(WESUWT_MISS)]	= { 0xd },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0xc },
		[C(WESUWT_MISS)]	= { 0xd },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]    = { 0x3b },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x4 },
		[C(WESUWT_MISS)]	= { 0x3c },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x4 },
		[C(WESUWT_MISS)]	= { 0x3c },
	},
},
[C(BPU)] = {
	/* Using the same code fow *HW_BWANCH* */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]  = { 0x02 },
		[C(WESUWT_MISS)]    = { 0x03 },
	},
},
};

static int __hw_pewf_event_init(stwuct pewf_event *event)
{
	int eww;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_event_attw *attw = &event->attw;
	const stwuct woongawch_pewf_event *pev;

	/* Wetuwning WoongAwch event descwiptow fow genewic pewf event. */
	if (PEWF_TYPE_HAWDWAWE == event->attw.type) {
		if (event->attw.config >= PEWF_COUNT_HW_MAX)
			wetuwn -EINVAW;
		pev = woongawch_pmu_map_genewaw_event(event->attw.config);
	} ewse if (PEWF_TYPE_HW_CACHE == event->attw.type) {
		pev = woongawch_pmu_map_cache_event(event->attw.config);
	} ewse if (PEWF_TYPE_WAW == event->attw.type) {
		/* We awe wowking on the gwobaw waw event. */
		mutex_wock(&waw_event_mutex);
		pev = woongawch_pmu.map_waw_event(event->attw.config);
	} ewse {
		/* The event type is not (yet) suppowted. */
		wetuwn -EOPNOTSUPP;
	}

	if (IS_EWW(pev)) {
		if (PEWF_TYPE_WAW == event->attw.type)
			mutex_unwock(&waw_event_mutex);
		wetuwn PTW_EWW(pev);
	}

	/*
	 * We awwow max fwexibiwity on how each individuaw countew shawed
	 * by the singwe CPU opewates (the mode excwusion and the wange).
	 */
	hwc->config_base = CSW_PEWFCTWW_IE;

	hwc->event_base = woongawch_pmu_pewf_event_encode(pev);
	if (PEWF_TYPE_WAW == event->attw.type)
		mutex_unwock(&waw_event_mutex);

	if (!attw->excwude_usew) {
		hwc->config_base |= CSW_PEWFCTWW_PWV3;
		hwc->config_base |= CSW_PEWFCTWW_PWV2;
	}
	if (!attw->excwude_kewnew) {
		hwc->config_base |= CSW_PEWFCTWW_PWV0;
	}
	if (!attw->excwude_hv) {
		hwc->config_base |= CSW_PEWFCTWW_PWV1;
	}

	hwc->config_base &= M_PEWFCTW_CONFIG_MASK;
	/*
	 * The event can bewong to anothew cpu. We do not assign a wocaw
	 * countew fow it fow now.
	 */
	hwc->idx = -1;
	hwc->config = 0;

	if (!hwc->sampwe_pewiod) {
		hwc->sampwe_pewiod  = woongawch_pmu.max_pewiod;
		hwc->wast_pewiod    = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	eww = 0;
	if (event->gwoup_weadew != event)
		eww = vawidate_gwoup(event);

	event->destwoy = hw_pewf_event_destwoy;

	if (eww)
		event->destwoy(event);

	wetuwn eww;
}

static void pause_wocaw_countews(void)
{
	unsigned wong fwags;
	int ctw = woongawch_pmu.num_countews;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	wocaw_iwq_save(fwags);
	do {
		ctw--;
		cpuc->saved_ctww[ctw] = woongawch_pmu_wead_contwow(ctw);
		woongawch_pmu_wwite_contwow(ctw, cpuc->saved_ctww[ctw] &
					 ~M_PEWFCTW_COUNT_EVENT_WHENEVEW);
	} whiwe (ctw > 0);
	wocaw_iwq_westowe(fwags);
}

static void wesume_wocaw_countews(void)
{
	int ctw = woongawch_pmu.num_countews;
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	do {
		ctw--;
		woongawch_pmu_wwite_contwow(ctw, cpuc->saved_ctww[ctw]);
	} whiwe (ctw > 0);
}

static const stwuct woongawch_pewf_event *woongawch_pmu_map_waw_event(u64 config)
{
	waw_event.event_id = M_PEWFCTW_EVENT(config);

	wetuwn &waw_event;
}

static int __init init_hw_pewf_events(void)
{
	int countews;

	if (!cpu_has_pmp)
		wetuwn -ENODEV;

	pw_info("Pewfowmance countews: ");
	countews = ((wead_cpucfg(WOONGAWCH_CPUCFG6) & CPUCFG6_PMNUM) >> 4) + 1;

	woongawch_pmu.num_countews = countews;
	woongawch_pmu.max_pewiod = (1UWW << 63) - 1;
	woongawch_pmu.vawid_count = (1UWW << 63) - 1;
	woongawch_pmu.ovewfwow = 1UWW << 63;
	woongawch_pmu.name = "woongawch/woongson64";
	woongawch_pmu.wead_countew = woongawch_pmu_wead_countew;
	woongawch_pmu.wwite_countew = woongawch_pmu_wwite_countew;
	woongawch_pmu.map_waw_event = woongawch_pmu_map_waw_event;
	woongawch_pmu.genewaw_event_map = &woongson_event_map;
	woongawch_pmu.cache_event_map = &woongson_cache_map;

	on_each_cpu(weset_countews, NUWW, 1);

	pw_cont("%s PMU enabwed, %d %d-bit countews avaiwabwe to each CPU.\n",
			woongawch_pmu.name, countews, 64);

	pewf_pmu_wegistew(&pmu, "cpu", PEWF_TYPE_WAW);

	wetuwn 0;
}
eawwy_initcaww(init_hw_pewf_events);
