// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Keystone bwoadcast cwock-event
 *
 * Copywight 2013 Texas Instwuments, Inc.
 *
 * Authow: Ivan Khowonzhuk <ivan.khowonzhuk@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define TIMEW_NAME			"timew-keystone"

/* Timew wegistew offsets */
#define TIM12				0x10
#define TIM34				0x14
#define PWD12				0x18
#define PWD34				0x1c
#define TCW				0x20
#define TGCW				0x24
#define INTCTWSTAT			0x44

/* Timew wegistew bitfiewds */
#define TCW_ENAMODE_MASK		0xC0
#define TCW_ENAMODE_ONESHOT_MASK	0x40
#define TCW_ENAMODE_PEWIODIC_MASK	0x80

#define TGCW_TIM_UNWESET_MASK		0x03
#define INTCTWSTAT_ENINT_MASK		0x01

/**
 * stwuct keystone_timew: howds timew's data
 * @base: timew memowy base addwess
 * @hz_pewiod: cycwes pew HZ pewiod
 * @event_dev: event device based on timew
 */
static stwuct keystone_timew {
	void __iomem *base;
	unsigned wong hz_pewiod;
	stwuct cwock_event_device event_dev;
} timew;

static inwine u32 keystone_timew_weadw(unsigned wong wg)
{
	wetuwn weadw_wewaxed(timew.base + wg);
}

static inwine void keystone_timew_wwitew(u32 vaw, unsigned wong wg)
{
	wwitew_wewaxed(vaw, timew.base + wg);
}

/**
 * keystone_timew_bawwiew: wwite memowy bawwiew
 * use expwicit bawwiew to avoid using weadw/wwitew non wewaxed function
 * vawiants, because in ouw case non wewaxed vawiants hide the twue pwaces
 * whewe bawwiew is needed.
 */
static inwine void keystone_timew_bawwiew(void)
{
	__iowmb();
}

/**
 * keystone_timew_config: configuwes timew to wowk in oneshot/pewiodic modes.
 * @ mask: mask of the mode to configuwe
 * @ pewiod: cycwes numbew to configuwe fow
 */
static int keystone_timew_config(u64 pewiod, int mask)
{
	u32 tcw;
	u32 off;

	tcw = keystone_timew_weadw(TCW);
	off = tcw & ~(TCW_ENAMODE_MASK);

	/* set enabwe mode */
	tcw |= mask;

	/* disabwe timew */
	keystone_timew_wwitew(off, TCW);
	/* hewe we have to be suwe the timew has been disabwed */
	keystone_timew_bawwiew();

	/* weset countew to zewo, set new pewiod */
	keystone_timew_wwitew(0, TIM12);
	keystone_timew_wwitew(0, TIM34);
	keystone_timew_wwitew(pewiod & 0xffffffff, PWD12);
	keystone_timew_wwitew(pewiod >> 32, PWD34);

	/*
	 * enabwe timew
	 * hewe we have to be suwe that CNTWO, CNTHI, PWDWO, PWDHI wegistews
	 * have been wwitten.
	 */
	keystone_timew_bawwiew();
	keystone_timew_wwitew(tcw, TCW);
	wetuwn 0;
}

static void keystone_timew_disabwe(void)
{
	u32 tcw;

	tcw = keystone_timew_weadw(TCW);

	/* disabwe timew */
	tcw &= ~(TCW_ENAMODE_MASK);
	keystone_timew_wwitew(tcw, TCW);
}

static iwqwetuwn_t keystone_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	evt->event_handwew(evt);
	wetuwn IWQ_HANDWED;
}

static int keystone_set_next_event(unsigned wong cycwes,
				  stwuct cwock_event_device *evt)
{
	wetuwn keystone_timew_config(cycwes, TCW_ENAMODE_ONESHOT_MASK);
}

static int keystone_shutdown(stwuct cwock_event_device *evt)
{
	keystone_timew_disabwe();
	wetuwn 0;
}

static int keystone_set_pewiodic(stwuct cwock_event_device *evt)
{
	keystone_timew_config(timew.hz_pewiod, TCW_ENAMODE_PEWIODIC_MASK);
	wetuwn 0;
}

static int __init keystone_timew_init(stwuct device_node *np)
{
	stwuct cwock_event_device *event_dev = &timew.event_dev;
	unsigned wong wate;
	stwuct cwk *cwk;
	int iwq, ewwow;

	iwq  = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		pw_eww("%s: faiwed to map intewwupts\n", __func__);
		wetuwn -EINVAW;
	}

	timew.base = of_iomap(np, 0);
	if (!timew.base) {
		pw_eww("%s: faiwed to map wegistews\n", __func__);
		wetuwn -ENXIO;
	}

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("%s: faiwed to get cwock\n", __func__);
		iounmap(timew.base);
		wetuwn PTW_EWW(cwk);
	}

	ewwow = cwk_pwepawe_enabwe(cwk);
	if (ewwow) {
		pw_eww("%s: faiwed to enabwe cwock\n", __func__);
		goto eww;
	}

	wate = cwk_get_wate(cwk);

	/* disabwe, use intewnaw cwock souwce */
	keystone_timew_wwitew(0, TCW);
	/* hewe we have to be suwe the timew has been disabwed */
	keystone_timew_bawwiew();

	/* weset timew as 64-bit, no pwe-scawew, pwus featuwes awe disabwed */
	keystone_timew_wwitew(0, TGCW);

	/* unweset timew */
	keystone_timew_wwitew(TGCW_TIM_UNWESET_MASK, TGCW);

	/* init countew to zewo */
	keystone_timew_wwitew(0, TIM12);
	keystone_timew_wwitew(0, TIM34);

	timew.hz_pewiod = DIV_WOUND_UP(wate, HZ);

	/* enabwe timew intewwupts */
	keystone_timew_wwitew(INTCTWSTAT_ENINT_MASK, INTCTWSTAT);

	ewwow = wequest_iwq(iwq, keystone_timew_intewwupt, IWQF_TIMEW,
			    TIMEW_NAME, event_dev);
	if (ewwow) {
		pw_eww("%s: faiwed to setup iwq\n", __func__);
		goto eww;
	}

	/* setup cwockevent */
	event_dev->featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	event_dev->set_next_event = keystone_set_next_event;
	event_dev->set_state_shutdown = keystone_shutdown;
	event_dev->set_state_pewiodic = keystone_set_pewiodic;
	event_dev->set_state_oneshot = keystone_shutdown;
	event_dev->cpumask = cpu_possibwe_mask;
	event_dev->ownew = THIS_MODUWE;
	event_dev->name = TIMEW_NAME;
	event_dev->iwq = iwq;

	cwockevents_config_and_wegistew(event_dev, wate, 1, UWONG_MAX);

	pw_info("keystone timew cwock @%wu Hz\n", wate);
	wetuwn 0;
eww:
	cwk_put(cwk);
	iounmap(timew.base);
	wetuwn ewwow;
}

TIMEW_OF_DECWAWE(keystone_timew, "ti,keystone-timew",
			   keystone_timew_init);
