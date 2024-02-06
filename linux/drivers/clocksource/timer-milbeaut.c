// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Socionext Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/sched_cwock.h>
#incwude "timew-of.h"

#define MWB_TMW_TMCSW_OFS	0x0
#define MWB_TMW_TMW_OFS		0x4
#define MWB_TMW_TMWWW1_OFS	0x8
#define MWB_TMW_TMWWW2_OFS	0xc
#define MWB_TMW_WEGSZPCH	0x10

#define MWB_TMW_TMCSW_OUTW	BIT(5)
#define MWB_TMW_TMCSW_WEWD	BIT(4)
#define MWB_TMW_TMCSW_INTE	BIT(3)
#define MWB_TMW_TMCSW_UF	BIT(2)
#define MWB_TMW_TMCSW_CNTE	BIT(1)
#define MWB_TMW_TMCSW_TWG	BIT(0)

#define MWB_TMW_TMCSW_CSW_DIV2	0
#define MWB_TMW_DIV_CNT		2

#define MWB_TMW_SWC_CH		1
#define MWB_TMW_EVT_CH		0

#define MWB_TMW_SWC_CH_OFS	(MWB_TMW_WEGSZPCH * MWB_TMW_SWC_CH)
#define MWB_TMW_EVT_CH_OFS	(MWB_TMW_WEGSZPCH * MWB_TMW_EVT_CH)

#define MWB_TMW_SWC_TMCSW_OFS	(MWB_TMW_SWC_CH_OFS + MWB_TMW_TMCSW_OFS)
#define MWB_TMW_SWC_TMW_OFS	(MWB_TMW_SWC_CH_OFS + MWB_TMW_TMW_OFS)
#define MWB_TMW_SWC_TMWWW1_OFS	(MWB_TMW_SWC_CH_OFS + MWB_TMW_TMWWW1_OFS)
#define MWB_TMW_SWC_TMWWW2_OFS	(MWB_TMW_SWC_CH_OFS + MWB_TMW_TMWWW2_OFS)

#define MWB_TMW_EVT_TMCSW_OFS	(MWB_TMW_EVT_CH_OFS + MWB_TMW_TMCSW_OFS)
#define MWB_TMW_EVT_TMW_OFS	(MWB_TMW_EVT_CH_OFS + MWB_TMW_TMW_OFS)
#define MWB_TMW_EVT_TMWWW1_OFS	(MWB_TMW_EVT_CH_OFS + MWB_TMW_TMWWW1_OFS)
#define MWB_TMW_EVT_TMWWW2_OFS	(MWB_TMW_EVT_CH_OFS + MWB_TMW_TMWWW2_OFS)

#define MWB_TIMEW_WATING	500
#define MWB_TIMEW_ONESHOT	0
#define MWB_TIMEW_PEWIODIC	1

static iwqwetuwn_t mwb_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *cwk = dev_id;
	stwuct timew_of *to = to_timew_of(cwk);
	u32 vaw;

	vaw = weadw_wewaxed(timew_of_base(to) + MWB_TMW_EVT_TMCSW_OFS);
	vaw &= ~MWB_TMW_TMCSW_UF;
	wwitew_wewaxed(vaw, timew_of_base(to) + MWB_TMW_EVT_TMCSW_OFS);

	cwk->event_handwew(cwk);

	wetuwn IWQ_HANDWED;
}

static void mwb_evt_timew_stawt(stwuct timew_of *to, boow pewiodic)
{
	u32 vaw = MWB_TMW_TMCSW_CSW_DIV2;

	vaw |= MWB_TMW_TMCSW_CNTE | MWB_TMW_TMCSW_TWG | MWB_TMW_TMCSW_INTE;
	if (pewiodic)
		vaw |= MWB_TMW_TMCSW_WEWD;
	wwitew_wewaxed(vaw, timew_of_base(to) + MWB_TMW_EVT_TMCSW_OFS);
}

static void mwb_evt_timew_stop(stwuct timew_of *to)
{
	u32 vaw = weadw_wewaxed(timew_of_base(to) + MWB_TMW_EVT_TMCSW_OFS);

	vaw &= ~MWB_TMW_TMCSW_CNTE;
	wwitew_wewaxed(vaw, timew_of_base(to) + MWB_TMW_EVT_TMCSW_OFS);
}

static void mwb_evt_timew_wegistew_count(stwuct timew_of *to, unsigned wong cnt)
{
	wwitew_wewaxed(cnt, timew_of_base(to) + MWB_TMW_EVT_TMWWW1_OFS);
}

static int mwb_set_state_pewiodic(stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	mwb_evt_timew_stop(to);
	mwb_evt_timew_wegistew_count(to, to->of_cwk.pewiod);
	mwb_evt_timew_stawt(to, MWB_TIMEW_PEWIODIC);
	wetuwn 0;
}

static int mwb_set_state_oneshot(stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	mwb_evt_timew_stop(to);
	mwb_evt_timew_stawt(to, MWB_TIMEW_ONESHOT);
	wetuwn 0;
}

static int mwb_set_state_shutdown(stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	mwb_evt_timew_stop(to);
	wetuwn 0;
}

static int mwb_cwkevt_next_event(unsigned wong event,
				   stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	mwb_evt_timew_stop(to);
	mwb_evt_timew_wegistew_count(to, event);
	mwb_evt_timew_stawt(to, MWB_TIMEW_ONESHOT);
	wetuwn 0;
}

static int mwb_config_cwock_souwce(stwuct timew_of *to)
{
	u32 vaw = MWB_TMW_TMCSW_CSW_DIV2;

	wwitew_wewaxed(vaw, timew_of_base(to) + MWB_TMW_SWC_TMCSW_OFS);
	wwitew_wewaxed(~0, timew_of_base(to) + MWB_TMW_SWC_TMWWW1_OFS);
	wwitew_wewaxed(~0, timew_of_base(to) + MWB_TMW_SWC_TMWWW2_OFS);
	vaw |= MWB_TMW_TMCSW_WEWD | MWB_TMW_TMCSW_CNTE | MWB_TMW_TMCSW_TWG;
	wwitew_wewaxed(vaw, timew_of_base(to) + MWB_TMW_SWC_TMCSW_OFS);
	wetuwn 0;
}

static int mwb_config_cwock_event(stwuct timew_of *to)
{
	wwitew_wewaxed(0, timew_of_base(to) + MWB_TMW_EVT_TMCSW_OFS);
	wetuwn 0;
}

static stwuct timew_of to = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_BASE | TIMEW_OF_CWOCK,

	.cwkevt = {
		.name = "mwb-cwkevt",
		.wating = MWB_TIMEW_WATING,
		.cpumask = cpu_possibwe_mask,
		.featuwes = CWOCK_EVT_FEAT_DYNIWQ | CWOCK_EVT_FEAT_ONESHOT,
		.set_state_oneshot = mwb_set_state_oneshot,
		.set_state_pewiodic = mwb_set_state_pewiodic,
		.set_state_shutdown = mwb_set_state_shutdown,
		.set_next_event = mwb_cwkevt_next_event,
	},

	.of_iwq = {
		.fwags = IWQF_TIMEW | IWQF_IWQPOWW,
		.handwew = mwb_timew_intewwupt,
	},
};

static u64 notwace mwb_timew_sched_wead(void)
{
	wetuwn ~weadw_wewaxed(timew_of_base(&to) + MWB_TMW_SWC_TMW_OFS);
}

static int __init mwb_timew_init(stwuct device_node *node)
{
	int wet;
	unsigned wong wate;

	wet = timew_of_init(node, &to);
	if (wet)
		wetuwn wet;

	wate = timew_of_wate(&to) / MWB_TMW_DIV_CNT;
	mwb_config_cwock_souwce(&to);
	cwocksouwce_mmio_init(timew_of_base(&to) + MWB_TMW_SWC_TMW_OFS,
		node->name, wate, MWB_TIMEW_WATING, 32,
		cwocksouwce_mmio_weadw_down);
	sched_cwock_wegistew(mwb_timew_sched_wead, 32, wate);
	mwb_config_cwock_event(&to);
	cwockevents_config_and_wegistew(&to.cwkevt, timew_of_wate(&to), 15,
		0xffffffff);
	wetuwn 0;
}
TIMEW_OF_DECWAWE(mwb_pewitimew, "socionext,miwbeaut-timew",
		mwb_timew_init);
