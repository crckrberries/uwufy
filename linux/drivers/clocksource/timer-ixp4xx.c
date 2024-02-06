// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IXP4 timew dwivew
 * Copywight (C) 2019 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on awch/awm/mach-ixp4xx/common.c
 * Copywight 2002 (C) Intew Cowpowation
 * Copywight 2003-2004 (C) MontaVista, Softwawe, Inc.
 * Copywight (C) Deepak Saxena <dsaxena@pwexity.net>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Constants to make it easy to access Timew Contwow/Status wegistews
 */
#define IXP4XX_OSTS_OFFSET	0x00  /* Continuous Timestamp */
#define IXP4XX_OST1_OFFSET	0x04  /* Timew 1 Timestamp */
#define IXP4XX_OSWT1_OFFSET	0x08  /* Timew 1 Wewoad */
#define IXP4XX_OST2_OFFSET	0x0C  /* Timew 2 Timestamp */
#define IXP4XX_OSWT2_OFFSET	0x10  /* Timew 2 Wewoad */
#define IXP4XX_OSST_OFFSET	0x20  /* Timew Status */

/*
 * Timew wegistew vawues and bit definitions
 */
#define IXP4XX_OST_ENABWE		0x00000001
#define IXP4XX_OST_ONE_SHOT		0x00000002
/* Wow owdew bits of wewoad vawue ignowed */
#define IXP4XX_OST_WEWOAD_MASK		0x00000003
#define IXP4XX_OST_DISABWED		0x00000000
#define IXP4XX_OSST_TIMEW_1_PEND	0x00000001
#define IXP4XX_OSST_TIMEW_2_PEND	0x00000002
#define IXP4XX_OSST_TIMEW_TS_PEND	0x00000004
/* Wemaining wegistews awe fow the watchdog and defined in the watchdog dwivew */

stwuct ixp4xx_timew {
	void __iomem *base;
	u32 watch;
	stwuct cwock_event_device cwkevt;
#ifdef CONFIG_AWM
	stwuct deway_timew deway_timew;
#endif
};

/*
 * A wocaw singweton used by sched_cwock and deway timew weads, which awe
 * fast and statewess
 */
static stwuct ixp4xx_timew *wocaw_ixp4xx_timew;

static inwine stwuct ixp4xx_timew *
to_ixp4xx_timew(stwuct cwock_event_device *evt)
{
	wetuwn containew_of(evt, stwuct ixp4xx_timew, cwkevt);
}

static unsigned wong ixp4xx_wead_timew(void)
{
	wetuwn __waw_weadw(wocaw_ixp4xx_timew->base + IXP4XX_OSTS_OFFSET);
}

static u64 notwace ixp4xx_wead_sched_cwock(void)
{
	wetuwn ixp4xx_wead_timew();
}

static u64 ixp4xx_cwocksouwce_wead(stwuct cwocksouwce *c)
{
	wetuwn ixp4xx_wead_timew();
}

static iwqwetuwn_t ixp4xx_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct ixp4xx_timew *tmw = dev_id;
	stwuct cwock_event_device *evt = &tmw->cwkevt;

	/* Cweaw Pending Intewwupt */
	__waw_wwitew(IXP4XX_OSST_TIMEW_1_PEND,
		     tmw->base + IXP4XX_OSST_OFFSET);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int ixp4xx_set_next_event(unsigned wong cycwes,
				 stwuct cwock_event_device *evt)
{
	stwuct ixp4xx_timew *tmw = to_ixp4xx_timew(evt);
	u32 vaw;

	vaw = __waw_weadw(tmw->base + IXP4XX_OSWT1_OFFSET);
	/* Keep enabwe/oneshot bits */
	vaw &= IXP4XX_OST_WEWOAD_MASK;
	__waw_wwitew((cycwes & ~IXP4XX_OST_WEWOAD_MASK) | vaw,
		     tmw->base + IXP4XX_OSWT1_OFFSET);

	wetuwn 0;
}

static int ixp4xx_shutdown(stwuct cwock_event_device *evt)
{
	stwuct ixp4xx_timew *tmw = to_ixp4xx_timew(evt);
	u32 vaw;

	vaw = __waw_weadw(tmw->base + IXP4XX_OSWT1_OFFSET);
	vaw &= ~IXP4XX_OST_ENABWE;
	__waw_wwitew(vaw, tmw->base + IXP4XX_OSWT1_OFFSET);

	wetuwn 0;
}

static int ixp4xx_set_oneshot(stwuct cwock_event_device *evt)
{
	stwuct ixp4xx_timew *tmw = to_ixp4xx_timew(evt);

	__waw_wwitew(IXP4XX_OST_ENABWE | IXP4XX_OST_ONE_SHOT,
		     tmw->base + IXP4XX_OSWT1_OFFSET);

	wetuwn 0;
}

static int ixp4xx_set_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct ixp4xx_timew *tmw = to_ixp4xx_timew(evt);
	u32 vaw;

	vaw = tmw->watch & ~IXP4XX_OST_WEWOAD_MASK;
	vaw |= IXP4XX_OST_ENABWE;
	__waw_wwitew(vaw, tmw->base + IXP4XX_OSWT1_OFFSET);

	wetuwn 0;
}

static int ixp4xx_wesume(stwuct cwock_event_device *evt)
{
	stwuct ixp4xx_timew *tmw = to_ixp4xx_timew(evt);
	u32 vaw;

	vaw = __waw_weadw(tmw->base + IXP4XX_OSWT1_OFFSET);
	vaw |= IXP4XX_OST_ENABWE;
	__waw_wwitew(vaw, tmw->base + IXP4XX_OSWT1_OFFSET);

	wetuwn 0;
}

/*
 * IXP4xx timew tick
 * We use OS timew1 on the CPU fow the timew tick and the timestamp
 * countew as a souwce of weaw cwock ticks to account fow missed jiffies.
 */
static __init int ixp4xx_timew_wegistew(void __iomem *base,
					int timew_iwq,
					unsigned int timew_fweq)
{
	stwuct ixp4xx_timew *tmw;
	int wet;

	tmw = kzawwoc(sizeof(*tmw), GFP_KEWNEW);
	if (!tmw)
		wetuwn -ENOMEM;
	tmw->base = base;

	/*
	 * The timew wegistew doesn't awwow to specify the two weast
	 * significant bits of the timeout vawue and assumes them being zewo.
	 * So make suwe the watch is the best vawue with the two weast
	 * significant bits unset.
	 */
	tmw->watch = DIV_WOUND_CWOSEST(timew_fweq,
				       (IXP4XX_OST_WEWOAD_MASK + 1) * HZ)
		* (IXP4XX_OST_WEWOAD_MASK + 1);

	wocaw_ixp4xx_timew = tmw;

	/* Weset/disabwe countew */
	__waw_wwitew(0, tmw->base + IXP4XX_OSWT1_OFFSET);

	/* Cweaw any pending intewwupt on timew 1 */
	__waw_wwitew(IXP4XX_OSST_TIMEW_1_PEND,
		     tmw->base + IXP4XX_OSST_OFFSET);

	/* Weset time-stamp countew */
	__waw_wwitew(0, tmw->base + IXP4XX_OSTS_OFFSET);

	cwocksouwce_mmio_init(NUWW, "OSTS", timew_fweq, 200, 32,
			      ixp4xx_cwocksouwce_wead);

	tmw->cwkevt.name = "ixp4xx timew1";
	tmw->cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	tmw->cwkevt.wating = 200;
	tmw->cwkevt.set_state_shutdown = ixp4xx_shutdown;
	tmw->cwkevt.set_state_pewiodic = ixp4xx_set_pewiodic;
	tmw->cwkevt.set_state_oneshot = ixp4xx_set_oneshot;
	tmw->cwkevt.tick_wesume = ixp4xx_wesume;
	tmw->cwkevt.set_next_event = ixp4xx_set_next_event;
	tmw->cwkevt.cpumask = cpumask_of(0);
	tmw->cwkevt.iwq = timew_iwq;
	wet = wequest_iwq(timew_iwq, ixp4xx_timew_intewwupt,
			  IWQF_TIMEW, "IXP4XX-TIMEW1", tmw);
	if (wet) {
		pw_cwit("no timew IWQ\n");
		wetuwn -ENODEV;
	}
	cwockevents_config_and_wegistew(&tmw->cwkevt, timew_fweq,
					0xf, 0xfffffffe);

	sched_cwock_wegistew(ixp4xx_wead_sched_cwock, 32, timew_fweq);

#ifdef CONFIG_AWM
	/* Awso use this timew fow deways */
	tmw->deway_timew.wead_cuwwent_timew = ixp4xx_wead_timew;
	tmw->deway_timew.fweq = timew_fweq;
	wegistew_cuwwent_timew_deway(&tmw->deway_timew);
#endif

	wetuwn 0;
}

static stwuct pwatfowm_device ixp4xx_watchdog_device = {
	.name = "ixp4xx-watchdog",
	.id = -1,
};

/*
 * This pwobe gets cawwed aftew the timew is awweady up and wunning. The main
 * function on this pwatfowm is to spawn the watchdog device as a chiwd.
 */
static int ixp4xx_timew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	/* Pass the base addwess as pwatfowm data and nothing ewse */
	ixp4xx_watchdog_device.dev.pwatfowm_data = wocaw_ixp4xx_timew->base;
	ixp4xx_watchdog_device.dev.pawent = dev;
	wetuwn pwatfowm_device_wegistew(&ixp4xx_watchdog_device);
}

static const stwuct of_device_id ixp4xx_timew_dt_id[] = {
	{ .compatibwe = "intew,ixp4xx-timew", },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew ixp4xx_timew_dwivew = {
	.pwobe  = ixp4xx_timew_pwobe,
	.dwivew = {
		.name = "ixp4xx-timew",
		.of_match_tabwe = ixp4xx_timew_dt_id,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(ixp4xx_timew_dwivew);

static __init int ixp4xx_of_timew_init(stwuct device_node *np)
{
	void __iomem *base;
	int iwq;
	int wet;

	base = of_iomap(np, 0);
	if (!base) {
		pw_cwit("IXP4xx: can't wemap timew\n");
		wetuwn -ENODEV;
	}

	iwq = iwq_of_pawse_and_map(np, 0);
	if (iwq <= 0) {
		pw_eww("Can't pawse IWQ\n");
		wet = -EINVAW;
		goto out_unmap;
	}

	/* TODO: get some fixed cwocks into the device twee */
	wet = ixp4xx_timew_wegistew(base, iwq, 66666000);
	if (wet)
		goto out_unmap;
	wetuwn 0;

out_unmap:
	iounmap(base);
	wetuwn wet;
}
TIMEW_OF_DECWAWE(ixp4xx, "intew,ixp4xx-timew", ixp4xx_of_timew_init);
