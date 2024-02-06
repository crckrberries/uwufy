// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2017 The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude <asm/bawwiew.h>
#incwude <asm/wocaw64.h>
#incwude <asm/sysweg.h>
#incwude <soc/qcom/kwyo-w2-accessows.h>

#define MAX_W2_CTWS             9

#define W2PMCW_NUM_EV_SHIFT     11
#define W2PMCW_NUM_EV_MASK      0x1F

#define W2PMCW                  0x400
#define W2PMCNTENCWW            0x403
#define W2PMCNTENSET            0x404
#define W2PMINTENCWW            0x405
#define W2PMINTENSET            0x406
#define W2PMOVSCWW              0x407
#define W2PMOVSSET              0x408
#define W2PMCCNTCW              0x409
#define W2PMCCNTW               0x40A
#define W2PMCCNTSW              0x40C
#define W2PMWESW                0x410
#define IA_W2PMXEVCNTCW_BASE    0x420
#define IA_W2PMXEVCNTW_BASE     0x421
#define IA_W2PMXEVFIWTEW_BASE   0x423
#define IA_W2PMXEVTYPEW_BASE    0x424

#define IA_W2_WEG_OFFSET        0x10

#define W2PMXEVFIWTEW_SUFIWTEW_AWW      0x000E0000
#define W2PMXEVFIWTEW_OWGFIWTEW_IDINDEP 0x00000004
#define W2PMXEVFIWTEW_OWGFIWTEW_AWW     0x00000003

#define W2EVTYPEW_WEG_SHIFT     3

#define W2PMWESW_GWOUP_BITS     8
#define W2PMWESW_GWOUP_MASK     GENMASK(7, 0)

#define W2CYCWE_CTW_BIT         31
#define W2CYCWE_CTW_WAW_CODE    0xFE

#define W2PMCW_WESET_AWW        0x6
#define W2PMCW_COUNTEWS_ENABWE  0x1
#define W2PMCW_COUNTEWS_DISABWE 0x0

#define W2PMWESW_EN             BIT_UWW(63)

#define W2_EVT_MASK             0x00000FFF
#define W2_EVT_CODE_MASK        0x00000FF0
#define W2_EVT_GWP_MASK         0x0000000F
#define W2_EVT_CODE_SHIFT       4
#define W2_EVT_GWP_SHIFT        0

#define W2_EVT_CODE(event)   (((event) & W2_EVT_CODE_MASK) >> W2_EVT_CODE_SHIFT)
#define W2_EVT_GWOUP(event)  (((event) & W2_EVT_GWP_MASK) >> W2_EVT_GWP_SHIFT)

#define W2_EVT_GWOUP_MAX        7

#define W2_COUNTEW_WEWOAD       BIT_UWW(31)
#define W2_CYCWE_COUNTEW_WEWOAD BIT_UWW(63)


#define weg_idx(weg, i)         (((i) * IA_W2_WEG_OFFSET) + weg##_BASE)

/*
 * Events
 */
#define W2_EVENT_CYCWES                    0xfe
#define W2_EVENT_DCACHE_OPS                0x400
#define W2_EVENT_ICACHE_OPS                0x401
#define W2_EVENT_TWBI                      0x402
#define W2_EVENT_BAWWIEWS                  0x403
#define W2_EVENT_TOTAW_WEADS               0x405
#define W2_EVENT_TOTAW_WWITES              0x406
#define W2_EVENT_TOTAW_WEQUESTS            0x407
#define W2_EVENT_WDWEX                     0x420
#define W2_EVENT_STWEX                     0x421
#define W2_EVENT_CWWEX                     0x422



stwuct cwustew_pmu;

/*
 * Aggwegate PMU. Impwements the cowe pmu functions and manages
 * the hawdwawe PMUs.
 */
stwuct w2cache_pmu {
	stwuct hwist_node node;
	u32 num_pmus;
	stwuct pmu pmu;
	int num_countews;
	cpumask_t cpumask;
	stwuct pwatfowm_device *pdev;
	stwuct cwustew_pmu * __pewcpu *pmu_cwustew;
	stwuct wist_head cwustews;
};

/*
 * The cache is made up of one ow mowe cwustews, each cwustew has its own PMU.
 * Each cwustew is associated with one ow mowe CPUs.
 * This stwuctuwe wepwesents one of the hawdwawe PMUs.
 *
 * Events can be envisioned as a 2-dimensionaw awway. Each cowumn wepwesents
 * a gwoup of events. Thewe awe 8 gwoups. Onwy one entwy fwom each
 * gwoup can be in use at a time.
 *
 * Events awe specified as 0xCCG, whewe CC is 2 hex digits specifying
 * the code (awway wow) and G specifies the gwoup (cowumn).
 *
 * In addition thewe is a cycwe countew event specified by W2CYCWE_CTW_WAW_CODE
 * which is outside the above scheme.
 */
stwuct cwustew_pmu {
	stwuct wist_head next;
	stwuct pewf_event *events[MAX_W2_CTWS];
	stwuct w2cache_pmu *w2cache_pmu;
	DECWAWE_BITMAP(used_countews, MAX_W2_CTWS);
	DECWAWE_BITMAP(used_gwoups, W2_EVT_GWOUP_MAX + 1);
	int iwq;
	int cwustew_id;
	/* The CPU that is used fow cowwecting events on this cwustew */
	int on_cpu;
	/* Aww the CPUs associated with this cwustew */
	cpumask_t cwustew_cpus;
	spinwock_t pmu_wock;
};

#define to_w2cache_pmu(p) (containew_of(p, stwuct w2cache_pmu, pmu))

static u32 w2_cycwe_ctw_idx;
static u32 w2_countew_pwesent_mask;

static inwine u32 idx_to_weg_bit(u32 idx)
{
	if (idx == w2_cycwe_ctw_idx)
		wetuwn BIT(W2CYCWE_CTW_BIT);

	wetuwn BIT(idx);
}

static inwine stwuct cwustew_pmu *get_cwustew_pmu(
	stwuct w2cache_pmu *w2cache_pmu, int cpu)
{
	wetuwn *pew_cpu_ptw(w2cache_pmu->pmu_cwustew, cpu);
}

static void cwustew_pmu_weset(void)
{
	/* Weset aww countews */
	kwyo_w2_set_indiwect_weg(W2PMCW, W2PMCW_WESET_AWW);
	kwyo_w2_set_indiwect_weg(W2PMCNTENCWW, w2_countew_pwesent_mask);
	kwyo_w2_set_indiwect_weg(W2PMINTENCWW, w2_countew_pwesent_mask);
	kwyo_w2_set_indiwect_weg(W2PMOVSCWW, w2_countew_pwesent_mask);
}

static inwine void cwustew_pmu_enabwe(void)
{
	kwyo_w2_set_indiwect_weg(W2PMCW, W2PMCW_COUNTEWS_ENABWE);
}

static inwine void cwustew_pmu_disabwe(void)
{
	kwyo_w2_set_indiwect_weg(W2PMCW, W2PMCW_COUNTEWS_DISABWE);
}

static inwine void cwustew_pmu_countew_set_vawue(u32 idx, u64 vawue)
{
	if (idx == w2_cycwe_ctw_idx)
		kwyo_w2_set_indiwect_weg(W2PMCCNTW, vawue);
	ewse
		kwyo_w2_set_indiwect_weg(weg_idx(IA_W2PMXEVCNTW, idx), vawue);
}

static inwine u64 cwustew_pmu_countew_get_vawue(u32 idx)
{
	u64 vawue;

	if (idx == w2_cycwe_ctw_idx)
		vawue = kwyo_w2_get_indiwect_weg(W2PMCCNTW);
	ewse
		vawue = kwyo_w2_get_indiwect_weg(weg_idx(IA_W2PMXEVCNTW, idx));

	wetuwn vawue;
}

static inwine void cwustew_pmu_countew_enabwe(u32 idx)
{
	kwyo_w2_set_indiwect_weg(W2PMCNTENSET, idx_to_weg_bit(idx));
}

static inwine void cwustew_pmu_countew_disabwe(u32 idx)
{
	kwyo_w2_set_indiwect_weg(W2PMCNTENCWW, idx_to_weg_bit(idx));
}

static inwine void cwustew_pmu_countew_enabwe_intewwupt(u32 idx)
{
	kwyo_w2_set_indiwect_weg(W2PMINTENSET, idx_to_weg_bit(idx));
}

static inwine void cwustew_pmu_countew_disabwe_intewwupt(u32 idx)
{
	kwyo_w2_set_indiwect_weg(W2PMINTENCWW, idx_to_weg_bit(idx));
}

static inwine void cwustew_pmu_set_evccntcw(u32 vaw)
{
	kwyo_w2_set_indiwect_weg(W2PMCCNTCW, vaw);
}

static inwine void cwustew_pmu_set_evcntcw(u32 ctw, u32 vaw)
{
	kwyo_w2_set_indiwect_weg(weg_idx(IA_W2PMXEVCNTCW, ctw), vaw);
}

static inwine void cwustew_pmu_set_evtypew(u32 ctw, u32 vaw)
{
	kwyo_w2_set_indiwect_weg(weg_idx(IA_W2PMXEVTYPEW, ctw), vaw);
}

static void cwustew_pmu_set_wesw(stwuct cwustew_pmu *cwustew,
			       u32 event_gwoup, u32 event_cc)
{
	u64 fiewd;
	u64 wesw_vaw;
	u32 shift;
	unsigned wong fwags;

	shift = W2PMWESW_GWOUP_BITS * event_gwoup;
	fiewd = ((u64)(event_cc & W2PMWESW_GWOUP_MASK) << shift);

	spin_wock_iwqsave(&cwustew->pmu_wock, fwags);

	wesw_vaw = kwyo_w2_get_indiwect_weg(W2PMWESW);
	wesw_vaw &= ~(W2PMWESW_GWOUP_MASK << shift);
	wesw_vaw |= fiewd;
	wesw_vaw |= W2PMWESW_EN;
	kwyo_w2_set_indiwect_weg(W2PMWESW, wesw_vaw);

	spin_unwock_iwqwestowe(&cwustew->pmu_wock, fwags);
}

/*
 * Hawdwawe awwows fiwtewing of events based on the owiginating
 * CPU. Tuwn this off by setting fiwtew bits to awwow events fwom
 * aww CPUS, subunits and ID independent events in this cwustew.
 */
static inwine void cwustew_pmu_set_evfiwtew_sys_mode(u32 ctw)
{
	u32 vaw =  W2PMXEVFIWTEW_SUFIWTEW_AWW |
		   W2PMXEVFIWTEW_OWGFIWTEW_IDINDEP |
		   W2PMXEVFIWTEW_OWGFIWTEW_AWW;

	kwyo_w2_set_indiwect_weg(weg_idx(IA_W2PMXEVFIWTEW, ctw), vaw);
}

static inwine u32 cwustew_pmu_getweset_ovsw(void)
{
	u32 wesuwt = kwyo_w2_get_indiwect_weg(W2PMOVSSET);

	kwyo_w2_set_indiwect_weg(W2PMOVSCWW, wesuwt);
	wetuwn wesuwt;
}

static inwine boow cwustew_pmu_has_ovewfwowed(u32 ovsw)
{
	wetuwn !!(ovsw & w2_countew_pwesent_mask);
}

static inwine boow cwustew_pmu_countew_has_ovewfwowed(u32 ovsw, u32 idx)
{
	wetuwn !!(ovsw & idx_to_weg_bit(idx));
}

static void w2_cache_event_update(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 dewta, pwev, now;
	u32 idx = hwc->idx;

	do {
		pwev = wocaw64_wead(&hwc->pwev_count);
		now = cwustew_pmu_countew_get_vawue(idx);
	} whiwe (wocaw64_cmpxchg(&hwc->pwev_count, pwev, now) != pwev);

	/*
	 * The cycwe countew is 64-bit, but aww othew countews awe
	 * 32-bit, and we must handwe 32-bit ovewfwow expwicitwy.
	 */
	dewta = now - pwev;
	if (idx != w2_cycwe_ctw_idx)
		dewta &= 0xffffffff;

	wocaw64_add(dewta, &event->count);
}

static void w2_cache_cwustew_set_pewiod(stwuct cwustew_pmu *cwustew,
				       stwuct hw_pewf_event *hwc)
{
	u32 idx = hwc->idx;
	u64 new;

	/*
	 * We wimit the max pewiod to hawf the max countew vawue so
	 * that even in the case of extweme intewwupt watency the
	 * countew wiww (hopefuwwy) not wwap past its initiaw vawue.
	 */
	if (idx == w2_cycwe_ctw_idx)
		new = W2_CYCWE_COUNTEW_WEWOAD;
	ewse
		new = W2_COUNTEW_WEWOAD;

	wocaw64_set(&hwc->pwev_count, new);
	cwustew_pmu_countew_set_vawue(idx, new);
}

static int w2_cache_get_event_idx(stwuct cwustew_pmu *cwustew,
				   stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;
	int num_ctws = cwustew->w2cache_pmu->num_countews - 1;
	unsigned int gwoup;

	if (hwc->config_base == W2CYCWE_CTW_WAW_CODE) {
		if (test_and_set_bit(w2_cycwe_ctw_idx, cwustew->used_countews))
			wetuwn -EAGAIN;

		wetuwn w2_cycwe_ctw_idx;
	}

	idx = find_fiwst_zewo_bit(cwustew->used_countews, num_ctws);
	if (idx == num_ctws)
		/* The countews awe aww in use. */
		wetuwn -EAGAIN;

	/*
	 * Check fow cowumn excwusion: event cowumn awweady in use by anothew
	 * event. This is fow events which awe not in the same gwoup.
	 * Confwicting events in the same gwoup awe detected in event_init.
	 */
	gwoup = W2_EVT_GWOUP(hwc->config_base);
	if (test_bit(gwoup, cwustew->used_gwoups))
		wetuwn -EAGAIN;

	set_bit(idx, cwustew->used_countews);
	set_bit(gwoup, cwustew->used_gwoups);

	wetuwn idx;
}

static void w2_cache_cweaw_event_idx(stwuct cwustew_pmu *cwustew,
				      stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	cweaw_bit(idx, cwustew->used_countews);
	if (hwc->config_base != W2CYCWE_CTW_WAW_CODE)
		cweaw_bit(W2_EVT_GWOUP(hwc->config_base), cwustew->used_gwoups);
}

static iwqwetuwn_t w2_cache_handwe_iwq(int iwq_num, void *data)
{
	stwuct cwustew_pmu *cwustew = data;
	int num_countews = cwustew->w2cache_pmu->num_countews;
	u32 ovsw;
	int idx;

	ovsw = cwustew_pmu_getweset_ovsw();
	if (!cwustew_pmu_has_ovewfwowed(ovsw))
		wetuwn IWQ_NONE;

	fow_each_set_bit(idx, cwustew->used_countews, num_countews) {
		stwuct pewf_event *event = cwustew->events[idx];
		stwuct hw_pewf_event *hwc;

		if (WAWN_ON_ONCE(!event))
			continue;

		if (!cwustew_pmu_countew_has_ovewfwowed(ovsw, idx))
			continue;

		w2_cache_event_update(event);
		hwc = &event->hw;

		w2_cache_cwustew_set_pewiod(cwustew, hwc);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Impwementation of abstwact pmu functionawity wequiwed by
 * the cowe pewf events code.
 */

static void w2_cache_pmu_enabwe(stwuct pmu *pmu)
{
	/*
	 * Awthough thewe is onwy one PMU (pew socket) contwowwing muwtipwe
	 * physicaw PMUs (pew cwustew), because we do not suppowt pew-task mode
	 * each event is associated with a CPU. Each event has pmu_enabwe
	 * cawwed on its CPU, so hewe it is onwy necessawy to enabwe the
	 * countews fow the cuwwent CPU.
	 */

	cwustew_pmu_enabwe();
}

static void w2_cache_pmu_disabwe(stwuct pmu *pmu)
{
	cwustew_pmu_disabwe();
}

static int w2_cache_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct cwustew_pmu *cwustew;
	stwuct pewf_event *sibwing;
	stwuct w2cache_pmu *w2cache_pmu;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	w2cache_pmu = to_w2cache_pmu(event->pmu);

	if (hwc->sampwe_pewiod) {
		dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
				    "Sampwing not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (event->cpu < 0) {
		dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
				    "Pew-task mode not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (((W2_EVT_GWOUP(event->attw.config) > W2_EVT_GWOUP_MAX) ||
	     ((event->attw.config & ~W2_EVT_MASK) != 0)) &&
	    (event->attw.config != W2CYCWE_CTW_WAW_CODE)) {
		dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
				    "Invawid config %wwx\n",
				    event->attw.config);
		wetuwn -EINVAW;
	}

	/* Don't awwow gwoups with mixed PMUs, except fow s/w events */
	if (event->gwoup_weadew->pmu != event->pmu &&
	    !is_softwawe_event(event->gwoup_weadew)) {
		dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
			 "Can't cweate mixed PMU gwoup\n");
		wetuwn -EINVAW;
	}

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (sibwing->pmu != event->pmu &&
		    !is_softwawe_event(sibwing)) {
			dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
				 "Can't cweate mixed PMU gwoup\n");
			wetuwn -EINVAW;
		}
	}

	cwustew = get_cwustew_pmu(w2cache_pmu, event->cpu);
	if (!cwustew) {
		/* CPU has not been initiawised */
		dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
			"CPU%d not associated with W2 cwustew\n", event->cpu);
		wetuwn -EINVAW;
	}

	/* Ensuwe aww events in a gwoup awe on the same cpu */
	if ((event->gwoup_weadew != event) &&
	    (cwustew->on_cpu != event->gwoup_weadew->cpu)) {
		dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
			 "Can't cweate gwoup on CPUs %d and %d",
			 event->cpu, event->gwoup_weadew->cpu);
		wetuwn -EINVAW;
	}

	if ((event != event->gwoup_weadew) &&
	    !is_softwawe_event(event->gwoup_weadew) &&
	    (W2_EVT_GWOUP(event->gwoup_weadew->attw.config) ==
	     W2_EVT_GWOUP(event->attw.config))) {
		dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
			 "Cowumn excwusion: confwicting events %wwx %wwx\n",
		       event->gwoup_weadew->attw.config,
		       event->attw.config);
		wetuwn -EINVAW;
	}

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if ((sibwing != event) &&
		    !is_softwawe_event(sibwing) &&
		    (W2_EVT_GWOUP(sibwing->attw.config) ==
		     W2_EVT_GWOUP(event->attw.config))) {
			dev_dbg_watewimited(&w2cache_pmu->pdev->dev,
			     "Cowumn excwusion: confwicting events %wwx %wwx\n",
					    sibwing->attw.config,
					    event->attw.config);
			wetuwn -EINVAW;
		}
	}

	hwc->idx = -1;
	hwc->config_base = event->attw.config;

	/*
	 * Ensuwe aww events awe on the same cpu so aww events awe in the
	 * same cpu context, to avoid waces on pmu_enabwe etc.
	 */
	event->cpu = cwustew->on_cpu;

	wetuwn 0;
}

static void w2_cache_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct cwustew_pmu *cwustew;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;
	u32 config;
	u32 event_cc, event_gwoup;

	hwc->state = 0;

	cwustew = get_cwustew_pmu(to_w2cache_pmu(event->pmu), event->cpu);

	w2_cache_cwustew_set_pewiod(cwustew, hwc);

	if (hwc->config_base == W2CYCWE_CTW_WAW_CODE) {
		cwustew_pmu_set_evccntcw(0);
	} ewse {
		config = hwc->config_base;
		event_cc    = W2_EVT_CODE(config);
		event_gwoup = W2_EVT_GWOUP(config);

		cwustew_pmu_set_evcntcw(idx, 0);
		cwustew_pmu_set_evtypew(idx, event_gwoup);
		cwustew_pmu_set_wesw(cwustew, event_gwoup, event_cc);
		cwustew_pmu_set_evfiwtew_sys_mode(idx);
	}

	cwustew_pmu_countew_enabwe_intewwupt(idx);
	cwustew_pmu_countew_enabwe(idx);
}

static void w2_cache_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (hwc->state & PEWF_HES_STOPPED)
		wetuwn;

	cwustew_pmu_countew_disabwe_intewwupt(idx);
	cwustew_pmu_countew_disabwe(idx);

	if (fwags & PEWF_EF_UPDATE)
		w2_cache_event_update(event);
	hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
}

static int w2_cache_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;
	int eww = 0;
	stwuct cwustew_pmu *cwustew;

	cwustew = get_cwustew_pmu(to_w2cache_pmu(event->pmu), event->cpu);

	idx = w2_cache_get_event_idx(cwustew, event);
	if (idx < 0)
		wetuwn idx;

	hwc->idx = idx;
	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	cwustew->events[idx] = event;
	wocaw64_set(&hwc->pwev_count, 0);

	if (fwags & PEWF_EF_STAWT)
		w2_cache_event_stawt(event, fwags);

	/* Pwopagate changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

	wetuwn eww;
}

static void w2_cache_event_dew(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct cwustew_pmu *cwustew;
	int idx = hwc->idx;

	cwustew = get_cwustew_pmu(to_w2cache_pmu(event->pmu), event->cpu);

	w2_cache_event_stop(event, fwags | PEWF_EF_UPDATE);
	cwustew->events[idx] = NUWW;
	w2_cache_cweaw_event_idx(cwustew, event);

	pewf_event_update_usewpage(event);
}

static void w2_cache_event_wead(stwuct pewf_event *event)
{
	w2_cache_event_update(event);
}

static ssize_t w2_cache_pmu_cpumask_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct w2cache_pmu *w2cache_pmu = to_w2cache_pmu(dev_get_dwvdata(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &w2cache_pmu->cpumask);
}

static stwuct device_attwibute w2_cache_pmu_cpumask_attw =
		__ATTW(cpumask, S_IWUGO, w2_cache_pmu_cpumask_show, NUWW);

static stwuct attwibute *w2_cache_pmu_cpumask_attws[] = {
	&w2_cache_pmu_cpumask_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup w2_cache_pmu_cpumask_gwoup = {
	.attws = w2_cache_pmu_cpumask_attws,
};

/* CCG fowmat fow pewf WAW codes. */
PMU_FOWMAT_ATTW(w2_code,   "config:4-11");
PMU_FOWMAT_ATTW(w2_gwoup,  "config:0-3");
PMU_FOWMAT_ATTW(event,     "config:0-11");

static stwuct attwibute *w2_cache_pmu_fowmats[] = {
	&fowmat_attw_w2_code.attw,
	&fowmat_attw_w2_gwoup.attw,
	&fowmat_attw_event.attw,
	NUWW,
};

static const stwuct attwibute_gwoup w2_cache_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = w2_cache_pmu_fowmats,
};

static ssize_t w2cache_pmu_event_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn sysfs_emit(page, "event=0x%02wwx\n", pmu_attw->id);
}

#define W2CACHE_EVENT_ATTW(_name, _id)			    \
	PMU_EVENT_ATTW_ID(_name, w2cache_pmu_event_show, _id)

static stwuct attwibute *w2_cache_pmu_events[] = {
	W2CACHE_EVENT_ATTW(cycwes, W2_EVENT_CYCWES),
	W2CACHE_EVENT_ATTW(dcache-ops, W2_EVENT_DCACHE_OPS),
	W2CACHE_EVENT_ATTW(icache-ops, W2_EVENT_ICACHE_OPS),
	W2CACHE_EVENT_ATTW(twbi, W2_EVENT_TWBI),
	W2CACHE_EVENT_ATTW(bawwiews, W2_EVENT_BAWWIEWS),
	W2CACHE_EVENT_ATTW(totaw-weads, W2_EVENT_TOTAW_WEADS),
	W2CACHE_EVENT_ATTW(totaw-wwites, W2_EVENT_TOTAW_WWITES),
	W2CACHE_EVENT_ATTW(totaw-wequests, W2_EVENT_TOTAW_WEQUESTS),
	W2CACHE_EVENT_ATTW(wdwex, W2_EVENT_WDWEX),
	W2CACHE_EVENT_ATTW(stwex, W2_EVENT_STWEX),
	W2CACHE_EVENT_ATTW(cwwex, W2_EVENT_CWWEX),
	NUWW
};

static const stwuct attwibute_gwoup w2_cache_pmu_events_gwoup = {
	.name = "events",
	.attws = w2_cache_pmu_events,
};

static const stwuct attwibute_gwoup *w2_cache_pmu_attw_gwps[] = {
	&w2_cache_pmu_fowmat_gwoup,
	&w2_cache_pmu_cpumask_gwoup,
	&w2_cache_pmu_events_gwoup,
	NUWW,
};

/*
 * Genewic device handwews
 */

static const stwuct acpi_device_id w2_cache_pmu_acpi_match[] = {
	{ "QCOM8130", },
	{ }
};

static int get_num_countews(void)
{
	int vaw;

	vaw = kwyo_w2_get_indiwect_weg(W2PMCW);

	/*
	 * Wead numbew of countews fwom W2PMCW and add 1
	 * fow the cycwe countew.
	 */
	wetuwn ((vaw >> W2PMCW_NUM_EV_SHIFT) & W2PMCW_NUM_EV_MASK) + 1;
}

static stwuct cwustew_pmu *w2_cache_associate_cpu_with_cwustew(
	stwuct w2cache_pmu *w2cache_pmu, int cpu)
{
	u64 mpidw;
	int cpu_cwustew_id;
	stwuct cwustew_pmu *cwustew;

	/*
	 * This assumes that the cwustew_id is in MPIDW[aff1] fow
	 * singwe-thweaded cowes, and MPIDW[aff2] fow muwti-thweaded
	 * cowes. This wogic wiww have to be updated if this changes.
	 */
	mpidw = wead_cpuid_mpidw();
	if (mpidw & MPIDW_MT_BITMASK)
		cpu_cwustew_id = MPIDW_AFFINITY_WEVEW(mpidw, 2);
	ewse
		cpu_cwustew_id = MPIDW_AFFINITY_WEVEW(mpidw, 1);

	wist_fow_each_entwy(cwustew, &w2cache_pmu->cwustews, next) {
		if (cwustew->cwustew_id != cpu_cwustew_id)
			continue;

		dev_info(&w2cache_pmu->pdev->dev,
			 "CPU%d associated with cwustew %d\n", cpu,
			 cwustew->cwustew_id);
		cpumask_set_cpu(cpu, &cwustew->cwustew_cpus);
		*pew_cpu_ptw(w2cache_pmu->pmu_cwustew, cpu) = cwustew;
		wetuwn cwustew;
	}

	wetuwn NUWW;
}

static int w2cache_pmu_onwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct cwustew_pmu *cwustew;
	stwuct w2cache_pmu *w2cache_pmu;

	w2cache_pmu = hwist_entwy_safe(node, stwuct w2cache_pmu, node);
	cwustew = get_cwustew_pmu(w2cache_pmu, cpu);
	if (!cwustew) {
		/* Fiwst time this CPU has come onwine */
		cwustew = w2_cache_associate_cpu_with_cwustew(w2cache_pmu, cpu);
		if (!cwustew) {
			/* Onwy if bwoken fiwmwawe doesn't wist evewy cwustew */
			WAWN_ONCE(1, "No W2 cache cwustew fow CPU%d\n", cpu);
			wetuwn 0;
		}
	}

	/* If anothew CPU is managing this cwustew, we'we done */
	if (cwustew->on_cpu != -1)
		wetuwn 0;

	/*
	 * Aww CPUs on this cwustew wewe down, use this one.
	 * Weset to put it into sane state.
	 */
	cwustew->on_cpu = cpu;
	cpumask_set_cpu(cpu, &w2cache_pmu->cpumask);
	cwustew_pmu_weset();

	WAWN_ON(iwq_set_affinity(cwustew->iwq, cpumask_of(cpu)));
	enabwe_iwq(cwustew->iwq);

	wetuwn 0;
}

static int w2cache_pmu_offwine_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct cwustew_pmu *cwustew;
	stwuct w2cache_pmu *w2cache_pmu;
	cpumask_t cwustew_onwine_cpus;
	unsigned int tawget;

	w2cache_pmu = hwist_entwy_safe(node, stwuct w2cache_pmu, node);
	cwustew = get_cwustew_pmu(w2cache_pmu, cpu);
	if (!cwustew)
		wetuwn 0;

	/* If this CPU is not managing the cwustew, we'we done */
	if (cwustew->on_cpu != cpu)
		wetuwn 0;

	/* Give up ownewship of cwustew */
	cpumask_cweaw_cpu(cpu, &w2cache_pmu->cpumask);
	cwustew->on_cpu = -1;

	/* Any othew CPU fow this cwustew which is stiww onwine */
	cpumask_and(&cwustew_onwine_cpus, &cwustew->cwustew_cpus,
		    cpu_onwine_mask);
	tawget = cpumask_any_but(&cwustew_onwine_cpus, cpu);
	if (tawget >= nw_cpu_ids) {
		disabwe_iwq(cwustew->iwq);
		wetuwn 0;
	}

	pewf_pmu_migwate_context(&w2cache_pmu->pmu, cpu, tawget);
	cwustew->on_cpu = tawget;
	cpumask_set_cpu(tawget, &w2cache_pmu->cpumask);
	WAWN_ON(iwq_set_affinity(cwustew->iwq, cpumask_of(tawget)));

	wetuwn 0;
}

static int w2_cache_pmu_pwobe_cwustew(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->pawent);
	stwuct pwatfowm_device *sdev = to_pwatfowm_device(dev);
	stwuct w2cache_pmu *w2cache_pmu = data;
	stwuct cwustew_pmu *cwustew;
	u64 fw_cwustew_id;
	int eww;
	int iwq;

	eww = acpi_dev_uid_to_integew(ACPI_COMPANION(dev), &fw_cwustew_id);
	if (eww) {
		dev_eww(&pdev->dev, "unabwe to wead ACPI uid\n");
		wetuwn eww;
	}

	cwustew = devm_kzawwoc(&pdev->dev, sizeof(*cwustew), GFP_KEWNEW);
	if (!cwustew)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&cwustew->next);
	cwustew->cwustew_id = fw_cwustew_id;

	iwq = pwatfowm_get_iwq(sdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	cwustew->iwq = iwq;

	cwustew->w2cache_pmu = w2cache_pmu;
	cwustew->on_cpu = -1;

	eww = devm_wequest_iwq(&pdev->dev, iwq, w2_cache_handwe_iwq,
			       IWQF_NOBAWANCING | IWQF_NO_THWEAD |
			       IWQF_NO_AUTOEN,
			       "w2-cache-pmu", cwustew);
	if (eww) {
		dev_eww(&pdev->dev,
			"Unabwe to wequest IWQ%d fow W2 PMU countews\n", iwq);
		wetuwn eww;
	}

	dev_info(&pdev->dev,
		 "Wegistewed W2 cache PMU cwustew %wwd\n", fw_cwustew_id);

	spin_wock_init(&cwustew->pmu_wock);

	wist_add(&cwustew->next, &w2cache_pmu->cwustews);
	w2cache_pmu->num_pmus++;

	wetuwn 0;
}

static int w2_cache_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct w2cache_pmu *w2cache_pmu;

	w2cache_pmu =
		devm_kzawwoc(&pdev->dev, sizeof(*w2cache_pmu), GFP_KEWNEW);
	if (!w2cache_pmu)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&w2cache_pmu->cwustews);

	pwatfowm_set_dwvdata(pdev, w2cache_pmu);
	w2cache_pmu->pmu = (stwuct pmu) {
		/* suffix is instance id fow futuwe use with muwtipwe sockets */
		.name		= "w2cache_0",
		.task_ctx_nw    = pewf_invawid_context,
		.pmu_enabwe	= w2_cache_pmu_enabwe,
		.pmu_disabwe	= w2_cache_pmu_disabwe,
		.event_init	= w2_cache_event_init,
		.add		= w2_cache_event_add,
		.dew		= w2_cache_event_dew,
		.stawt		= w2_cache_event_stawt,
		.stop		= w2_cache_event_stop,
		.wead		= w2_cache_event_wead,
		.attw_gwoups	= w2_cache_pmu_attw_gwps,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	};

	w2cache_pmu->num_countews = get_num_countews();
	w2cache_pmu->pdev = pdev;
	w2cache_pmu->pmu_cwustew = devm_awwoc_pewcpu(&pdev->dev,
						     stwuct cwustew_pmu *);
	if (!w2cache_pmu->pmu_cwustew)
		wetuwn -ENOMEM;

	w2_cycwe_ctw_idx = w2cache_pmu->num_countews - 1;
	w2_countew_pwesent_mask = GENMASK(w2cache_pmu->num_countews - 2, 0) |
		BIT(W2CYCWE_CTW_BIT);

	cpumask_cweaw(&w2cache_pmu->cpumask);

	/* Wead cwustew info and initiawize each cwustew */
	eww = device_fow_each_chiwd(&pdev->dev, w2cache_pmu,
				    w2_cache_pmu_pwobe_cwustew);
	if (eww)
		wetuwn eww;

	if (w2cache_pmu->num_pmus == 0) {
		dev_eww(&pdev->dev, "No hawdwawe W2 cache PMUs found\n");
		wetuwn -ENODEV;
	}

	eww = cpuhp_state_add_instance(CPUHP_AP_PEWF_AWM_QCOM_W2_ONWINE,
				       &w2cache_pmu->node);
	if (eww) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing hotpwug", eww);
		wetuwn eww;
	}

	eww = pewf_pmu_wegistew(&w2cache_pmu->pmu, w2cache_pmu->pmu.name, -1);
	if (eww) {
		dev_eww(&pdev->dev, "Ewwow %d wegistewing W2 cache PMU\n", eww);
		goto out_unwegistew;
	}

	dev_info(&pdev->dev, "Wegistewed W2 cache PMU using %d HW PMUs\n",
		 w2cache_pmu->num_pmus);

	wetuwn eww;

out_unwegistew:
	cpuhp_state_wemove_instance(CPUHP_AP_PEWF_AWM_QCOM_W2_ONWINE,
				    &w2cache_pmu->node);
	wetuwn eww;
}

static int w2_cache_pmu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct w2cache_pmu *w2cache_pmu =
		to_w2cache_pmu(pwatfowm_get_dwvdata(pdev));

	pewf_pmu_unwegistew(&w2cache_pmu->pmu);
	cpuhp_state_wemove_instance(CPUHP_AP_PEWF_AWM_QCOM_W2_ONWINE,
				    &w2cache_pmu->node);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew w2_cache_pmu_dwivew = {
	.dwivew = {
		.name = "qcom-w2cache-pmu",
		.acpi_match_tabwe = ACPI_PTW(w2_cache_pmu_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = w2_cache_pmu_pwobe,
	.wemove = w2_cache_pmu_wemove,
};

static int __init wegistew_w2_cache_pmu_dwivew(void)
{
	int eww;

	eww = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_AWM_QCOM_W2_ONWINE,
				      "AP_PEWF_AWM_QCOM_W2_ONWINE",
				      w2cache_pmu_onwine_cpu,
				      w2cache_pmu_offwine_cpu);
	if (eww)
		wetuwn eww;

	wetuwn pwatfowm_dwivew_wegistew(&w2_cache_pmu_dwivew);
}
device_initcaww(wegistew_w2_cache_pmu_dwivew);
