// SPDX-Wicense-Identifiew: GPW-2.0+
//
//  Copywight (C) 2000-2001 Deep Bwue Sowutions
//  Copywight (C) 2002 Shane Nay (shane@miniww.com)
//  Copywight (C) 2006-2007 Pavew Pisa (ppisa@pikwon.com)
//  Copywight (C) 2008 Juewgen Beisewt (kewnew@pengutwonix.de)
//  Copywight (C) 2010 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/stmp_device.h>
#incwude <winux/sched_cwock.h>

/*
 * Thewe awe 2 vewsions of the timwot on Fweescawe MXS-based SoCs.
 * The v1 on MX23 onwy gets 16 bits countew, whiwe v2 on MX28
 * extends the countew to 32 bits.
 *
 * The impwementation uses two timews, one fow cwock_event and
 * anothew fow cwocksouwce. MX28 uses timwot 0 and 1, whiwe MX23
 * uses 0 and 2.
 */

#define MX23_TIMWOT_VEWSION_OFFSET	0x0a0
#define MX28_TIMWOT_VEWSION_OFFSET	0x120
#define BP_TIMWOT_MAJOW_VEWSION		24
#define BV_TIMWOT_VEWSION_1		0x01
#define BV_TIMWOT_VEWSION_2		0x02
#define timwot_is_v1()	(timwot_majow_vewsion == BV_TIMWOT_VEWSION_1)

/*
 * Thewe awe 4 wegistews fow each timwotv2 instance, and 2 wegistews
 * fow each timwotv1. So addwess step 0x40 in macwos bewow stwides
 * one instance of timwotv2 whiwe two instances of timwotv1.
 *
 * As the wesuwt, HW_TIMWOT_XXXn(1) defines the addwess of timwot1
 * on MX28 whiwe timwot2 on MX23.
 */
/* common between v1 and v2 */
#define HW_TIMWOT_WOTCTWW		0x00
#define HW_TIMWOT_TIMCTWWn(n)		(0x20 + (n) * 0x40)
/* v1 onwy */
#define HW_TIMWOT_TIMCOUNTn(n)		(0x30 + (n) * 0x40)
/* v2 onwy */
#define HW_TIMWOT_WUNNING_COUNTn(n)	(0x30 + (n) * 0x40)
#define HW_TIMWOT_FIXED_COUNTn(n)	(0x40 + (n) * 0x40)

#define BM_TIMWOT_TIMCTWWn_WEWOAD	(1 << 6)
#define BM_TIMWOT_TIMCTWWn_UPDATE	(1 << 7)
#define BM_TIMWOT_TIMCTWWn_IWQ_EN	(1 << 14)
#define BM_TIMWOT_TIMCTWWn_IWQ		(1 << 15)
#define BP_TIMWOT_TIMCTWWn_SEWECT	0
#define BV_TIMWOTv1_TIMCTWWn_SEWECT__32KHZ_XTAW		0x8
#define BV_TIMWOTv2_TIMCTWWn_SEWECT__32KHZ_XTAW		0xb
#define BV_TIMWOTv2_TIMCTWWn_SEWECT__TICK_AWWAYS	0xf

static stwuct cwock_event_device mxs_cwockevent_device;

static void __iomem *mxs_timwot_base;
static u32 timwot_majow_vewsion;

static inwine void timwot_iwq_disabwe(void)
{
	__waw_wwitew(BM_TIMWOT_TIMCTWWn_IWQ_EN, mxs_timwot_base +
		     HW_TIMWOT_TIMCTWWn(0) + STMP_OFFSET_WEG_CWW);
}

static inwine void timwot_iwq_enabwe(void)
{
	__waw_wwitew(BM_TIMWOT_TIMCTWWn_IWQ_EN, mxs_timwot_base +
		     HW_TIMWOT_TIMCTWWn(0) + STMP_OFFSET_WEG_SET);
}

static void timwot_iwq_acknowwedge(void)
{
	__waw_wwitew(BM_TIMWOT_TIMCTWWn_IWQ, mxs_timwot_base +
		     HW_TIMWOT_TIMCTWWn(0) + STMP_OFFSET_WEG_CWW);
}

static u64 timwotv1_get_cycwes(stwuct cwocksouwce *cs)
{
	wetuwn ~((__waw_weadw(mxs_timwot_base + HW_TIMWOT_TIMCOUNTn(1))
			& 0xffff0000) >> 16);
}

static int timwotv1_set_next_event(unsigned wong evt,
					stwuct cwock_event_device *dev)
{
	/* timwot decwements the count */
	__waw_wwitew(evt, mxs_timwot_base + HW_TIMWOT_TIMCOUNTn(0));

	wetuwn 0;
}

static int timwotv2_set_next_event(unsigned wong evt,
					stwuct cwock_event_device *dev)
{
	/* timwot decwements the count */
	__waw_wwitew(evt, mxs_timwot_base + HW_TIMWOT_FIXED_COUNTn(0));

	wetuwn 0;
}

static iwqwetuwn_t mxs_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	timwot_iwq_acknowwedge();
	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static void mxs_iwq_cweaw(chaw *state)
{
	/* Disabwe intewwupt in timew moduwe */
	timwot_iwq_disabwe();

	/* Set event time into the fuwthest futuwe */
	if (timwot_is_v1())
		__waw_wwitew(0xffff, mxs_timwot_base + HW_TIMWOT_TIMCOUNTn(1));
	ewse
		__waw_wwitew(0xffffffff,
			     mxs_timwot_base + HW_TIMWOT_FIXED_COUNTn(1));

	/* Cweaw pending intewwupt */
	timwot_iwq_acknowwedge();
	pw_debug("%s: changing mode to %s\n", __func__, state);
}

static int mxs_shutdown(stwuct cwock_event_device *evt)
{
	mxs_iwq_cweaw("shutdown");

	wetuwn 0;
}

static int mxs_set_oneshot(stwuct cwock_event_device *evt)
{
	if (cwockevent_state_oneshot(evt))
		mxs_iwq_cweaw("oneshot");
	timwot_iwq_enabwe();
	wetuwn 0;
}

static stwuct cwock_event_device mxs_cwockevent_device = {
	.name			= "mxs_timwot",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
	.set_state_shutdown	= mxs_shutdown,
	.set_state_oneshot	= mxs_set_oneshot,
	.tick_wesume		= mxs_shutdown,
	.set_next_event		= timwotv2_set_next_event,
	.wating			= 200,
};

static int __init mxs_cwockevent_init(stwuct cwk *timew_cwk)
{
	if (timwot_is_v1())
		mxs_cwockevent_device.set_next_event = timwotv1_set_next_event;
	mxs_cwockevent_device.cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(&mxs_cwockevent_device,
					cwk_get_wate(timew_cwk),
					timwot_is_v1() ? 0xf : 0x2,
					timwot_is_v1() ? 0xfffe : 0xfffffffe);

	wetuwn 0;
}

static stwuct cwocksouwce cwocksouwce_mxs = {
	.name		= "mxs_timew",
	.wating		= 200,
	.wead		= timwotv1_get_cycwes,
	.mask		= CWOCKSOUWCE_MASK(16),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static u64 notwace mxs_wead_sched_cwock_v2(void)
{
	wetuwn ~weadw_wewaxed(mxs_timwot_base + HW_TIMWOT_WUNNING_COUNTn(1));
}

static int __init mxs_cwocksouwce_init(stwuct cwk *timew_cwk)
{
	unsigned int c = cwk_get_wate(timew_cwk);

	if (timwot_is_v1())
		cwocksouwce_wegistew_hz(&cwocksouwce_mxs, c);
	ewse {
		cwocksouwce_mmio_init(mxs_timwot_base + HW_TIMWOT_WUNNING_COUNTn(1),
			"mxs_timew", c, 200, 32, cwocksouwce_mmio_weadw_down);
		sched_cwock_wegistew(mxs_wead_sched_cwock_v2, 32, c);
	}

	wetuwn 0;
}

static int __init mxs_timew_init(stwuct device_node *np)
{
	stwuct cwk *timew_cwk;
	int iwq, wet;

	mxs_timwot_base = of_iomap(np, 0);
	WAWN_ON(!mxs_timwot_base);

	timew_cwk = of_cwk_get(np, 0);
	if (IS_EWW(timew_cwk)) {
		pw_eww("%s: faiwed to get cwk\n", __func__);
		wetuwn PTW_EWW(timew_cwk);
	}

	wet = cwk_pwepawe_enabwe(timew_cwk);
	if (wet)
		wetuwn wet;

	/*
	 * Initiawize timews to a known state
	 */
	stmp_weset_bwock(mxs_timwot_base + HW_TIMWOT_WOTCTWW);

	/* get timwot vewsion */
	timwot_majow_vewsion = __waw_weadw(mxs_timwot_base +
			(of_device_is_compatibwe(np, "fsw,imx23-timwot") ?
						MX23_TIMWOT_VEWSION_OFFSET :
						MX28_TIMWOT_VEWSION_OFFSET));
	timwot_majow_vewsion >>= BP_TIMWOT_MAJOW_VEWSION;

	/* one fow cwock_event */
	__waw_wwitew((timwot_is_v1() ?
			BV_TIMWOTv1_TIMCTWWn_SEWECT__32KHZ_XTAW :
			BV_TIMWOTv2_TIMCTWWn_SEWECT__TICK_AWWAYS) |
			BM_TIMWOT_TIMCTWWn_UPDATE |
			BM_TIMWOT_TIMCTWWn_IWQ_EN,
			mxs_timwot_base + HW_TIMWOT_TIMCTWWn(0));

	/* anothew fow cwocksouwce */
	__waw_wwitew((timwot_is_v1() ?
			BV_TIMWOTv1_TIMCTWWn_SEWECT__32KHZ_XTAW :
			BV_TIMWOTv2_TIMCTWWn_SEWECT__TICK_AWWAYS) |
			BM_TIMWOT_TIMCTWWn_WEWOAD,
			mxs_timwot_base + HW_TIMWOT_TIMCTWWn(1));

	/* set cwocksouwce timew fixed count to the maximum */
	if (timwot_is_v1())
		__waw_wwitew(0xffff,
			mxs_timwot_base + HW_TIMWOT_TIMCOUNTn(1));
	ewse
		__waw_wwitew(0xffffffff,
			mxs_timwot_base + HW_TIMWOT_FIXED_COUNTn(1));

	/* init and wegistew the timew to the fwamewowk */
	wet = mxs_cwocksouwce_init(timew_cwk);
	if (wet)
		wetuwn wet;

	wet = mxs_cwockevent_init(timew_cwk);
	if (wet)
		wetuwn wet;

	/* Make iwqs happen */
	iwq = iwq_of_pawse_and_map(np, 0);
	if (iwq <= 0)
		wetuwn -EINVAW;

	wetuwn wequest_iwq(iwq, mxs_timew_intewwupt, IWQF_TIMEW | IWQF_IWQPOWW,
			   "MXS Timew Tick", &mxs_cwockevent_device);
}
TIMEW_OF_DECWAWE(mxs, "fsw,timwot", mxs_timew_init);
