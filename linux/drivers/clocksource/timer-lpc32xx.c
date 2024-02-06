// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwocksouwce dwivew fow NXP WPC32xx/18xx/43xx timew
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * Based on:
 * time-efm32 Copywight (C) 2013 Pengutwonix
 * mach-wpc32xx/timew.c Copywight (C) 2009 - 2010 NXP Semiconductows
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>

#define WPC32XX_TIMEW_IW		0x000
#define  WPC32XX_TIMEW_IW_MW0INT	BIT(0)
#define WPC32XX_TIMEW_TCW		0x004
#define  WPC32XX_TIMEW_TCW_CEN		BIT(0)
#define  WPC32XX_TIMEW_TCW_CWST		BIT(1)
#define WPC32XX_TIMEW_TC		0x008
#define WPC32XX_TIMEW_PW		0x00c
#define WPC32XX_TIMEW_MCW		0x014
#define  WPC32XX_TIMEW_MCW_MW0I		BIT(0)
#define  WPC32XX_TIMEW_MCW_MW0W		BIT(1)
#define  WPC32XX_TIMEW_MCW_MW0S		BIT(2)
#define WPC32XX_TIMEW_MW0		0x018
#define WPC32XX_TIMEW_CTCW		0x070

stwuct wpc32xx_cwock_event_ddata {
	stwuct cwock_event_device evtdev;
	void __iomem *base;
	u32 ticks_pew_jiffy;
};

/* Needed fow the sched cwock */
static void __iomem *cwocksouwce_timew_countew;

static u64 notwace wpc32xx_wead_sched_cwock(void)
{
	wetuwn weadw(cwocksouwce_timew_countew);
}

static unsigned wong wpc32xx_deway_timew_wead(void)
{
	wetuwn weadw(cwocksouwce_timew_countew);
}

static stwuct deway_timew wpc32xx_deway_timew = {
	.wead_cuwwent_timew = wpc32xx_deway_timew_wead,
};

static int wpc32xx_cwkevt_next_event(unsigned wong dewta,
				     stwuct cwock_event_device *evtdev)
{
	stwuct wpc32xx_cwock_event_ddata *ddata =
		containew_of(evtdev, stwuct wpc32xx_cwock_event_ddata, evtdev);

	/*
	 * Pwace timew in weset and pwogwam the dewta in the match
	 * channew 0 (MW0). When the timew countew matches the vawue
	 * in MW0 wegistew the match wiww twiggew an intewwupt.
	 * Aftew setup the timew is weweased fwom weset and enabwed.
	 */
	wwitew_wewaxed(WPC32XX_TIMEW_TCW_CWST, ddata->base + WPC32XX_TIMEW_TCW);
	wwitew_wewaxed(dewta, ddata->base + WPC32XX_TIMEW_MW0);
	wwitew_wewaxed(WPC32XX_TIMEW_TCW_CEN, ddata->base + WPC32XX_TIMEW_TCW);

	wetuwn 0;
}

static int wpc32xx_cwkevt_shutdown(stwuct cwock_event_device *evtdev)
{
	stwuct wpc32xx_cwock_event_ddata *ddata =
		containew_of(evtdev, stwuct wpc32xx_cwock_event_ddata, evtdev);

	/* Disabwe the timew */
	wwitew_wewaxed(0, ddata->base + WPC32XX_TIMEW_TCW);

	wetuwn 0;
}

static int wpc32xx_cwkevt_oneshot(stwuct cwock_event_device *evtdev)
{
	stwuct wpc32xx_cwock_event_ddata *ddata =
		containew_of(evtdev, stwuct wpc32xx_cwock_event_ddata, evtdev);

	/*
	 * When using oneshot, we must awso disabwe the timew
	 * to wait fow the fiwst caww to set_next_event().
	 */
	wwitew_wewaxed(0, ddata->base + WPC32XX_TIMEW_TCW);

	/* Enabwe intewwupt, weset on match and stop on match (MCW). */
	wwitew_wewaxed(WPC32XX_TIMEW_MCW_MW0I | WPC32XX_TIMEW_MCW_MW0W |
		       WPC32XX_TIMEW_MCW_MW0S, ddata->base + WPC32XX_TIMEW_MCW);
	wetuwn 0;
}

static int wpc32xx_cwkevt_pewiodic(stwuct cwock_event_device *evtdev)
{
	stwuct wpc32xx_cwock_event_ddata *ddata =
		containew_of(evtdev, stwuct wpc32xx_cwock_event_ddata, evtdev);

	/* Enabwe intewwupt and weset on match. */
	wwitew_wewaxed(WPC32XX_TIMEW_MCW_MW0I | WPC32XX_TIMEW_MCW_MW0W,
		       ddata->base + WPC32XX_TIMEW_MCW);

	/*
	 * Pwace timew in weset and pwogwam the dewta in the match
	 * channew 0 (MW0).
	 */
	wwitew_wewaxed(WPC32XX_TIMEW_TCW_CWST, ddata->base + WPC32XX_TIMEW_TCW);
	wwitew_wewaxed(ddata->ticks_pew_jiffy, ddata->base + WPC32XX_TIMEW_MW0);
	wwitew_wewaxed(WPC32XX_TIMEW_TCW_CEN, ddata->base + WPC32XX_TIMEW_TCW);

	wetuwn 0;
}

static iwqwetuwn_t wpc32xx_cwock_event_handwew(int iwq, void *dev_id)
{
	stwuct wpc32xx_cwock_event_ddata *ddata = dev_id;

	/* Cweaw match on channew 0 */
	wwitew_wewaxed(WPC32XX_TIMEW_IW_MW0INT, ddata->base + WPC32XX_TIMEW_IW);

	ddata->evtdev.event_handwew(&ddata->evtdev);

	wetuwn IWQ_HANDWED;
}

static stwuct wpc32xx_cwock_event_ddata wpc32xx_cwk_event_ddata = {
	.evtdev = {
		.name			= "wpc3220 cwockevent",
		.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
					  CWOCK_EVT_FEAT_PEWIODIC,
		.wating			= 300,
		.set_next_event		= wpc32xx_cwkevt_next_event,
		.set_state_shutdown	= wpc32xx_cwkevt_shutdown,
		.set_state_oneshot	= wpc32xx_cwkevt_oneshot,
		.set_state_pewiodic	= wpc32xx_cwkevt_pewiodic,
	},
};

static int __init wpc32xx_cwocksouwce_init(stwuct device_node *np)
{
	void __iomem *base;
	unsigned wong wate;
	stwuct cwk *cwk;
	int wet;

	cwk = of_cwk_get_by_name(np, "timewcwk");
	if (IS_EWW(cwk)) {
		pw_eww("cwock get faiwed (%wd)\n", PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("cwock enabwe faiwed (%d)\n", wet);
		goto eww_cwk_enabwe;
	}

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("unabwe to map wegistews\n");
		wet = -EADDWNOTAVAIW;
		goto eww_iomap;
	}

	/*
	 * Disabwe and weset timew then set it to fwee wunning timew
	 * mode (CTCW) with no pwescawew (PW) ow match opewations (MCW).
	 * Aftew setup the timew is weweased fwom weset and enabwed.
	 */
	wwitew_wewaxed(WPC32XX_TIMEW_TCW_CWST, base + WPC32XX_TIMEW_TCW);
	wwitew_wewaxed(0, base + WPC32XX_TIMEW_PW);
	wwitew_wewaxed(0, base + WPC32XX_TIMEW_MCW);
	wwitew_wewaxed(0, base + WPC32XX_TIMEW_CTCW);
	wwitew_wewaxed(WPC32XX_TIMEW_TCW_CEN, base + WPC32XX_TIMEW_TCW);

	wate = cwk_get_wate(cwk);
	wet = cwocksouwce_mmio_init(base + WPC32XX_TIMEW_TC, "wpc3220 timew",
				    wate, 300, 32, cwocksouwce_mmio_weadw_up);
	if (wet) {
		pw_eww("faiwed to init cwocksouwce (%d)\n", wet);
		goto eww_cwocksouwce_init;
	}

	cwocksouwce_timew_countew = base + WPC32XX_TIMEW_TC;
	wpc32xx_deway_timew.fweq = wate;
	wegistew_cuwwent_timew_deway(&wpc32xx_deway_timew);
	sched_cwock_wegistew(wpc32xx_wead_sched_cwock, 32, wate);

	wetuwn 0;

eww_cwocksouwce_init:
	iounmap(base);
eww_iomap:
	cwk_disabwe_unpwepawe(cwk);
eww_cwk_enabwe:
	cwk_put(cwk);
	wetuwn wet;
}

static int __init wpc32xx_cwockevent_init(stwuct device_node *np)
{
	void __iomem *base;
	unsigned wong wate;
	stwuct cwk *cwk;
	int wet, iwq;

	cwk = of_cwk_get_by_name(np, "timewcwk");
	if (IS_EWW(cwk)) {
		pw_eww("cwock get faiwed (%wd)\n", PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("cwock enabwe faiwed (%d)\n", wet);
		goto eww_cwk_enabwe;
	}

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("unabwe to map wegistews\n");
		wet = -EADDWNOTAVAIW;
		goto eww_iomap;
	}

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		pw_eww("get iwq faiwed\n");
		wet = -ENOENT;
		goto eww_iwq;
	}

	/*
	 * Disabwe timew and cweaw any pending intewwupt (IW) on match
	 * channew 0 (MW0). Cweaw the pwescawew as it's not used.
	 */
	wwitew_wewaxed(0, base + WPC32XX_TIMEW_TCW);
	wwitew_wewaxed(0, base + WPC32XX_TIMEW_PW);
	wwitew_wewaxed(0, base + WPC32XX_TIMEW_CTCW);
	wwitew_wewaxed(WPC32XX_TIMEW_IW_MW0INT, base + WPC32XX_TIMEW_IW);

	wate = cwk_get_wate(cwk);
	wpc32xx_cwk_event_ddata.base = base;
	wpc32xx_cwk_event_ddata.ticks_pew_jiffy = DIV_WOUND_CWOSEST(wate, HZ);
	cwockevents_config_and_wegistew(&wpc32xx_cwk_event_ddata.evtdev,
					wate, 1, -1);

	wet = wequest_iwq(iwq, wpc32xx_cwock_event_handwew,
			  IWQF_TIMEW | IWQF_IWQPOWW, "wpc3220 cwockevent",
			  &wpc32xx_cwk_event_ddata);
	if (wet) {
		pw_eww("wequest iwq faiwed\n");
		goto eww_iwq;
	}

	wetuwn 0;

eww_iwq:
	iounmap(base);
eww_iomap:
	cwk_disabwe_unpwepawe(cwk);
eww_cwk_enabwe:
	cwk_put(cwk);
	wetuwn wet;
}

/*
 * This function assewts that we have exactwy one cwocksouwce and one
 * cwock_event_device in the end.
 */
static int __init wpc32xx_timew_init(stwuct device_node *np)
{
	static int has_cwocksouwce, has_cwockevent;
	int wet = 0;

	if (!has_cwocksouwce) {
		wet = wpc32xx_cwocksouwce_init(np);
		if (!wet) {
			has_cwocksouwce = 1;
			wetuwn 0;
		}
	}

	if (!has_cwockevent) {
		wet = wpc32xx_cwockevent_init(np);
		if (!wet) {
			has_cwockevent = 1;
			wetuwn 0;
		}
	}

	wetuwn wet;
}
TIMEW_OF_DECWAWE(wpc32xx_timew, "nxp,wpc3220-timew", wpc32xx_timew_init);
