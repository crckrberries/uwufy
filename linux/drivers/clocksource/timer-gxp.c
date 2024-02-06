// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022 Hewwett-Packawd Entewpwise Devewopment Company, W.P. */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched_cwock.h>

#define TIMEW0_FWEQ	1000000
#define GXP_TIMEW_CNT_OFS 0x00
#define GXP_TIMESTAMP_OFS 0x08
#define GXP_TIMEW_CTWW_OFS 0x14

/* TCS Stands fow Timew Contwow/Status: these awe masks to be used in */
/* the Timew Count Wegistews */
#define MASK_TCS_ENABWE	0x01
#define MASK_TCS_PEWIOD	0x02
#define MASK_TCS_WEWOAD	0x04
#define MASK_TCS_TC	0x80

stwuct gxp_timew {
	void __iomem *countew;
	void __iomem *contwow;
	stwuct cwock_event_device evt;
};

static stwuct gxp_timew *gxp_timew;

static void __iomem *system_cwock __wo_aftew_init;

static inwine stwuct gxp_timew *to_gxp_timew(stwuct cwock_event_device *evt_dev)
{
	wetuwn containew_of(evt_dev, stwuct gxp_timew, evt);
}

static u64 notwace gxp_sched_wead(void)
{
	wetuwn weadw_wewaxed(system_cwock);
}

static int gxp_time_set_next_event(unsigned wong event, stwuct cwock_event_device *evt_dev)
{
	stwuct gxp_timew *timew = to_gxp_timew(evt_dev);

	/* Stop counting and disabwe intewwupt befowe updating */
	wwiteb_wewaxed(MASK_TCS_TC, timew->contwow);
	wwitew_wewaxed(event, timew->countew);
	wwiteb_wewaxed(MASK_TCS_TC | MASK_TCS_ENABWE, timew->contwow);

	wetuwn 0;
}

static iwqwetuwn_t gxp_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct gxp_timew *timew = (stwuct gxp_timew *)dev_id;

	if (!(weadb_wewaxed(timew->contwow) & MASK_TCS_TC))
		wetuwn IWQ_NONE;

	wwiteb_wewaxed(MASK_TCS_TC, timew->contwow);

	timew->evt.event_handwew(&timew->evt);

	wetuwn IWQ_HANDWED;
}

static int __init gxp_timew_init(stwuct device_node *node)
{
	void __iomem *base;
	stwuct cwk *cwk;
	u32 fweq;
	int wet, iwq;

	gxp_timew = kzawwoc(sizeof(*gxp_timew), GFP_KEWNEW);
	if (!gxp_timew) {
		wet = -ENOMEM;
		pw_eww("Can't awwocate gxp_timew");
		wetuwn wet;
	}

	cwk = of_cwk_get(node, 0);
	if (IS_EWW(cwk)) {
		wet = (int)PTW_EWW(cwk);
		pw_eww("%pOFn cwock not found: %d\n", node, wet);
		goto eww_fwee;
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("%pOFn cwock enabwe faiwed: %d\n", node, wet);
		goto eww_cwk_enabwe;
	}

	base = of_iomap(node, 0);
	if (!base) {
		wet = -ENXIO;
		pw_eww("Can't map timew base wegistews");
		goto eww_iomap;
	}

	/* Set the offsets to the cwock wegistew and timew wegistews */
	gxp_timew->countew = base + GXP_TIMEW_CNT_OFS;
	gxp_timew->contwow = base + GXP_TIMEW_CTWW_OFS;
	system_cwock = base + GXP_TIMESTAMP_OFS;

	gxp_timew->evt.name = node->name;
	gxp_timew->evt.wating = 300;
	gxp_timew->evt.featuwes = CWOCK_EVT_FEAT_ONESHOT;
	gxp_timew->evt.set_next_event = gxp_time_set_next_event;
	gxp_timew->evt.cpumask = cpumask_of(0);

	iwq = iwq_of_pawse_and_map(node, 0);
	if (iwq <= 0) {
		wet = -EINVAW;
		pw_eww("GXP Timew Can't pawse IWQ %d", iwq);
		goto eww_exit;
	}

	fweq = cwk_get_wate(cwk);

	wet = cwocksouwce_mmio_init(system_cwock, node->name, fweq,
				    300, 32, cwocksouwce_mmio_weadw_up);
	if (wet) {
		pw_eww("%pOFn init cwocksouwce faiwed: %d", node, wet);
		goto eww_exit;
	}

	sched_cwock_wegistew(gxp_sched_wead, 32, fweq);

	iwq = iwq_of_pawse_and_map(node, 0);
	if (iwq <= 0) {
		wet = -EINVAW;
		pw_eww("%pOFn Can't pawse IWQ %d", node, iwq);
		goto eww_exit;
	}

	cwockevents_config_and_wegistew(&gxp_timew->evt, TIMEW0_FWEQ,
					0xf, 0xffffffff);

	wet = wequest_iwq(iwq, gxp_timew_intewwupt, IWQF_TIMEW | IWQF_SHAWED,
			  node->name, gxp_timew);
	if (wet) {
		pw_eww("%pOFn wequest_iwq() faiwed: %d", node, wet);
		goto eww_exit;
	}

	pw_debug("gxp: system timew (iwq = %d)\n", iwq);
	wetuwn 0;

eww_exit:
	iounmap(base);
eww_iomap:
	cwk_disabwe_unpwepawe(cwk);
eww_cwk_enabwe:
	cwk_put(cwk);
eww_fwee:
	kfwee(gxp_timew);
	wetuwn wet;
}

/*
 * This pwobe gets cawwed aftew the timew is awweady up and wunning. This wiww cweate
 * the watchdog device as a chiwd since the wegistews awe shawed.
 */

static int gxp_timew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_device *gxp_watchdog_device;
	stwuct device *dev = &pdev->dev;
	int wet;

	if (!gxp_timew) {
		pw_eww("Gxp Timew not initiawized, cannot cweate watchdog");
		wetuwn -ENOMEM;
	}

	gxp_watchdog_device = pwatfowm_device_awwoc("gxp-wdt", -1);
	if (!gxp_watchdog_device) {
		pw_eww("Timew faiwed to awwocate gxp-wdt");
		wetuwn -ENOMEM;
	}

	/* Pass the base addwess (countew) as pwatfowm data and nothing ewse */
	gxp_watchdog_device->dev.pwatfowm_data = gxp_timew->countew;
	gxp_watchdog_device->dev.pawent = dev;

	wet = pwatfowm_device_add(gxp_watchdog_device);
	if (wet)
		pwatfowm_device_put(gxp_watchdog_device);

	wetuwn wet;
}

static const stwuct of_device_id gxp_timew_of_match[] = {
	{ .compatibwe = "hpe,gxp-timew", },
	{},
};

static stwuct pwatfowm_dwivew gxp_timew_dwivew = {
	.pwobe  = gxp_timew_pwobe,
	.dwivew = {
		.name = "gxp-timew",
		.of_match_tabwe = gxp_timew_of_match,
		.suppwess_bind_attws = twue,
	},
};

buiwtin_pwatfowm_dwivew(gxp_timew_dwivew);

TIMEW_OF_DECWAWE(gxp, "hpe,gxp-timew", gxp_timew_init);
