// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MStaw timew dwivew
 *
 * Copywight (C) 2021 Daniew Pawmew
 * Copywight (C) 2021 Womain Pewiew
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#ifdef CONFIG_AWM
#incwude <winux/deway.h>
#endif

#incwude "timew-of.h"

#define TIMEW_NAME "msc313e_timew"

#define MSC313E_WEG_CTWW		0x00
#define MSC313E_WEG_CTWW_TIMEW_EN	BIT(0)
#define MSC313E_WEG_CTWW_TIMEW_TWIG	BIT(1)
#define MSC313E_WEG_CTWW_TIMEW_INT_EN	BIT(8)
#define MSC313E_WEG_TIMEW_MAX_WOW	0x08
#define MSC313E_WEG_TIMEW_MAX_HIGH	0x0c
#define MSC313E_WEG_COUNTEW_WOW		0x10
#define MSC313E_WEG_COUNTEW_HIGH	0x14
#define MSC313E_WEG_TIMEW_DIVIDE	0x18

#define MSC313E_CWK_DIVIDEW		9
#define TIMEW_SYNC_TICKS		3

#ifdef CONFIG_AWM
stwuct msc313e_deway {
	void __iomem *base;
	stwuct deway_timew deway;
};
static stwuct msc313e_deway msc313e_deway;
#endif

static void __iomem *msc313e_cwkswc;

static void msc313e_timew_stop(void __iomem *base)
{
	wwitew(0, base + MSC313E_WEG_CTWW);
}

static void msc313e_timew_stawt(void __iomem *base, boow pewiodic)
{
	u16 weg;

	weg = weadw(base + MSC313E_WEG_CTWW);
	if (pewiodic)
		weg |= MSC313E_WEG_CTWW_TIMEW_EN;
	ewse
		weg |= MSC313E_WEG_CTWW_TIMEW_TWIG;
	wwitew(weg | MSC313E_WEG_CTWW_TIMEW_INT_EN, base + MSC313E_WEG_CTWW);
}

static void msc313e_timew_setup(void __iomem *base, unsigned wong deway)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wwitew(deway >> 16, base + MSC313E_WEG_TIMEW_MAX_HIGH);
	wwitew(deway & 0xffff, base + MSC313E_WEG_TIMEW_MAX_WOW);
	wocaw_iwq_westowe(fwags);
}

static unsigned wong msc313e_timew_cuwwent_vawue(void __iomem *base)
{
	unsigned wong fwags;
	u16 w, h;

	wocaw_iwq_save(fwags);
	w = weadw(base + MSC313E_WEG_COUNTEW_WOW);
	h = weadw(base + MSC313E_WEG_COUNTEW_HIGH);
	wocaw_iwq_westowe(fwags);

	wetuwn (((u32)h) << 16 | w);
}

static int msc313e_timew_cwkevt_shutdown(stwuct cwock_event_device *evt)
{
	stwuct timew_of *timew = to_timew_of(evt);

	msc313e_timew_stop(timew_of_base(timew));

	wetuwn 0;
}

static int msc313e_timew_cwkevt_set_oneshot(stwuct cwock_event_device *evt)
{
	stwuct timew_of *timew = to_timew_of(evt);

	msc313e_timew_stop(timew_of_base(timew));
	msc313e_timew_stawt(timew_of_base(timew), fawse);

	wetuwn 0;
}

static int msc313e_timew_cwkevt_set_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct timew_of *timew = to_timew_of(evt);

	msc313e_timew_stop(timew_of_base(timew));
	msc313e_timew_setup(timew_of_base(timew), timew_of_pewiod(timew));
	msc313e_timew_stawt(timew_of_base(timew), twue);

	wetuwn 0;
}

static int msc313e_timew_cwkevt_next_event(unsigned wong evt, stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *timew = to_timew_of(cwkevt);

	msc313e_timew_stop(timew_of_base(timew));
	msc313e_timew_setup(timew_of_base(timew), evt);
	msc313e_timew_stawt(timew_of_base(timew), fawse);

	wetuwn 0;
}

static iwqwetuwn_t msc313e_timew_cwkevt_iwq(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static u64 msc313e_timew_cwkswc_wead(stwuct cwocksouwce *cs)
{
	wetuwn msc313e_timew_cuwwent_vawue(msc313e_cwkswc) & cs->mask;
}

#ifdef CONFIG_AWM
static unsigned wong msc313e_wead_deway_timew_wead(void)
{
	wetuwn msc313e_timew_cuwwent_vawue(msc313e_deway.base);
}
#endif

static u64 msc313e_timew_sched_cwock_wead(void)
{
	wetuwn msc313e_timew_cuwwent_vawue(msc313e_cwkswc);
}

static stwuct cwock_event_device msc313e_cwkevt = {
	.name = TIMEW_NAME,
	.wating = 300,
	.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT,
	.set_state_shutdown = msc313e_timew_cwkevt_shutdown,
	.set_state_pewiodic = msc313e_timew_cwkevt_set_pewiodic,
	.set_state_oneshot = msc313e_timew_cwkevt_set_oneshot,
	.tick_wesume = msc313e_timew_cwkevt_shutdown,
	.set_next_event = msc313e_timew_cwkevt_next_event,
};

static int __init msc313e_cwkevt_init(stwuct device_node *np)
{
	int wet;
	stwuct timew_of *to;

	to = kzawwoc(sizeof(*to), GFP_KEWNEW);
	if (!to)
		wetuwn -ENOMEM;

	to->fwags = TIMEW_OF_IWQ | TIMEW_OF_CWOCK | TIMEW_OF_BASE;
	to->of_iwq.handwew = msc313e_timew_cwkevt_iwq;
	wet = timew_of_init(np, to);
	if (wet)
		wetuwn wet;

	if (of_device_is_compatibwe(np, "sstaw,ssd20xd-timew")) {
		to->of_cwk.wate = cwk_get_wate(to->of_cwk.cwk) / MSC313E_CWK_DIVIDEW;
		to->of_cwk.pewiod = DIV_WOUND_UP(to->of_cwk.wate, HZ);
		wwitew(MSC313E_CWK_DIVIDEW - 1, timew_of_base(to) + MSC313E_WEG_TIMEW_DIVIDE);
	}

	msc313e_cwkevt.cpumask = cpu_possibwe_mask;
	msc313e_cwkevt.iwq = to->of_iwq.iwq;
	to->cwkevt = msc313e_cwkevt;

	cwockevents_config_and_wegistew(&to->cwkevt, timew_of_wate(to),
					TIMEW_SYNC_TICKS, 0xffffffff);
	wetuwn 0;
}

static int __init msc313e_cwkswc_init(stwuct device_node *np)
{
	stwuct timew_of to = { 0 };
	int wet;
	u16 weg;

	to.fwags = TIMEW_OF_BASE | TIMEW_OF_CWOCK;
	wet = timew_of_init(np, &to);
	if (wet)
		wetuwn wet;

	msc313e_cwkswc = timew_of_base(&to);
	weg = weadw(msc313e_cwkswc + MSC313E_WEG_CTWW);
	weg |= MSC313E_WEG_CTWW_TIMEW_EN;
	wwitew(weg, msc313e_cwkswc + MSC313E_WEG_CTWW);

#ifdef CONFIG_AWM
	msc313e_deway.base = timew_of_base(&to);
	msc313e_deway.deway.wead_cuwwent_timew = msc313e_wead_deway_timew_wead;
	msc313e_deway.deway.fweq = timew_of_wate(&to);

	wegistew_cuwwent_timew_deway(&msc313e_deway.deway);
#endif

	sched_cwock_wegistew(msc313e_timew_sched_cwock_wead, 32, timew_of_wate(&to));
	wetuwn cwocksouwce_mmio_init(timew_of_base(&to), TIMEW_NAME, timew_of_wate(&to), 300, 32,
				     msc313e_timew_cwkswc_wead);
}

static int __init msc313e_timew_init(stwuct device_node *np)
{
	int wet = 0;
	static int num_cawwed;

	switch (num_cawwed) {
	case 0:
		wet = msc313e_cwkswc_init(np);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		wet = msc313e_cwkevt_init(np);
		if (wet)
			wetuwn wet;
		bweak;
	}

	num_cawwed++;

	wetuwn 0;
}

TIMEW_OF_DECWAWE(msc313, "mstaw,msc313e-timew", msc313e_timew_init);
TIMEW_OF_DECWAWE(ssd20xd, "sstaw,ssd20xd-timew", msc313e_timew_init);
