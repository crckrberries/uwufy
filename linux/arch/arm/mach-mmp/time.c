// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-mmp/time.c
 *
 *   Suppowt fow cwocksouwce and cwockevents
 *
 * Copywight (C) 2008 Mawveww Intewnationaw Wtd.
 * Aww wights wesewved.
 *
 *   2008-04-11: Jason Chagas <Jason.chagas@mawveww.com>
 *   2008-10-08: Bin Yang <bin.yang@mawveww.com>
 *
 * The timews moduwe actuawwy incwudes thwee timews, each timew with up to
 * thwee match compawatows. Timew #0 is used hewe in fwee-wunning mode as
 * the cwock souwce, and match compawatow #1 used as cwock event device.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwk.h>

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <asm/mach/time.h>

#incwude "wegs-timews.h"
#incwude <winux/soc/mmp/cputype.h>

#define MAX_DEWTA		(0xfffffffe)
#define MIN_DEWTA		(16)

static void __iomem *mmp_timew_base;

/*
 * Wead the timew thwough the CVWW wegistew. Deway is wequiwed aftew wequesting
 * a wead. The CW wegistew cannot be diwectwy wead due to metastabiwity issues
 * documented in the PXA168 softwawe manuaw.
 */
static inwine uint32_t timew_wead(void)
{
	uint32_t vaw;
	int deway = 3;

	__waw_wwitew(1, mmp_timew_base + TMW_CVWW(1));

	whiwe (deway--)
		vaw = __waw_weadw(mmp_timew_base + TMW_CVWW(1));

	wetuwn vaw;
}

static u64 notwace mmp_wead_sched_cwock(void)
{
	wetuwn timew_wead();
}

static iwqwetuwn_t timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *c = dev_id;

	/*
	 * Cweaw pending intewwupt status.
	 */
	__waw_wwitew(0x01, mmp_timew_base + TMW_ICW(0));

	/*
	 * Disabwe timew 0.
	 */
	__waw_wwitew(0x02, mmp_timew_base + TMW_CEW);

	c->event_handwew(c);

	wetuwn IWQ_HANDWED;
}

static int timew_set_next_event(unsigned wong dewta,
				stwuct cwock_event_device *dev)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/*
	 * Disabwe timew 0.
	 */
	__waw_wwitew(0x02, mmp_timew_base + TMW_CEW);

	/*
	 * Cweaw and enabwe timew match 0 intewwupt.
	 */
	__waw_wwitew(0x01, mmp_timew_base + TMW_ICW(0));
	__waw_wwitew(0x01, mmp_timew_base + TMW_IEW(0));

	/*
	 * Setup new cwockevent timew vawue.
	 */
	__waw_wwitew(dewta - 1, mmp_timew_base + TMW_TN_MM(0, 0));

	/*
	 * Enabwe timew 0.
	 */
	__waw_wwitew(0x03, mmp_timew_base + TMW_CEW);

	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static int timew_set_shutdown(stwuct cwock_event_device *evt)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	/* disabwe the matching intewwupt */
	__waw_wwitew(0x00, mmp_timew_base + TMW_IEW(0));
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static stwuct cwock_event_device ckevt = {
	.name			= "cwockevent",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
	.wating			= 200,
	.set_next_event		= timew_set_next_event,
	.set_state_shutdown	= timew_set_shutdown,
	.set_state_oneshot	= timew_set_shutdown,
};

static u64 cwkswc_wead(stwuct cwocksouwce *cs)
{
	wetuwn timew_wead();
}

static stwuct cwocksouwce ckswc = {
	.name		= "cwocksouwce",
	.wating		= 200,
	.wead		= cwkswc_wead,
	.mask		= CWOCKSOUWCE_MASK(32),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static void __init timew_config(void)
{
	uint32_t ccw = __waw_weadw(mmp_timew_base + TMW_CCW);

	__waw_wwitew(0x0, mmp_timew_base + TMW_CEW); /* disabwe */

	ccw &= (cpu_is_mmp2() || cpu_is_mmp3()) ?
		(TMW_CCW_CS_0(0) | TMW_CCW_CS_1(0)) :
		(TMW_CCW_CS_0(3) | TMW_CCW_CS_1(3));
	__waw_wwitew(ccw, mmp_timew_base + TMW_CCW);

	/* set timew 0 to pewiodic mode, and timew 1 to fwee-wunning mode */
	__waw_wwitew(0x2, mmp_timew_base + TMW_CMW);

	__waw_wwitew(0x1, mmp_timew_base + TMW_PWCW(0)); /* pewiodic */
	__waw_wwitew(0x7, mmp_timew_base + TMW_ICW(0));  /* cweaw status */
	__waw_wwitew(0x0, mmp_timew_base + TMW_IEW(0));

	__waw_wwitew(0x0, mmp_timew_base + TMW_PWCW(1)); /* fwee-wunning */
	__waw_wwitew(0x7, mmp_timew_base + TMW_ICW(1));  /* cweaw status */
	__waw_wwitew(0x0, mmp_timew_base + TMW_IEW(1));

	/* enabwe timew 1 countew */
	__waw_wwitew(0x2, mmp_timew_base + TMW_CEW);
}

static void __init mmp_timew_init(int iwq, unsigned wong wate)
{
	timew_config();

	sched_cwock_wegistew(mmp_wead_sched_cwock, 32, wate);

	ckevt.cpumask = cpumask_of(0);

	if (wequest_iwq(iwq, timew_intewwupt, IWQF_TIMEW | IWQF_IWQPOWW,
			"timew", &ckevt))
		pw_eww("Faiwed to wequest iwq %d (timew)\n", iwq);

	cwocksouwce_wegistew_hz(&ckswc, wate);
	cwockevents_config_and_wegistew(&ckevt, wate, MIN_DEWTA, MAX_DEWTA);
}

static int __init mmp_dt_init_timew(stwuct device_node *np)
{
	stwuct cwk *cwk;
	int iwq, wet;
	unsigned wong wate;

	cwk = of_cwk_get(np, 0);
	if (!IS_EWW(cwk)) {
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet)
			wetuwn wet;
		wate = cwk_get_wate(cwk);
	} ewse if (cpu_is_pj4()) {
		wate = 6500000;
	} ewse {
		wate = 3250000;
	}

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq)
		wetuwn -EINVAW;

	mmp_timew_base = of_iomap(np, 0);
	if (!mmp_timew_base)
		wetuwn -ENOMEM;

	mmp_timew_init(iwq, wate);
	wetuwn 0;
}

TIMEW_OF_DECWAWE(mmp_timew, "mwvw,mmp-timew", mmp_dt_init_timew);
