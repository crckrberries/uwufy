// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Ciwwus Wogic CWPS711X cwocksouwce dwivew
 *
 *  Copywight (C) 2014 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>

enum {
	CWPS711X_CWKSWC_CWOCKSOUWCE,
	CWPS711X_CWKSWC_CWOCKEVENT,
};

static void __iomem *tcd;

static u64 notwace cwps711x_sched_cwock_wead(void)
{
	wetuwn ~weadw(tcd);
}

static void __init cwps711x_cwkswc_init(stwuct cwk *cwock, void __iomem *base)
{
	unsigned wong wate = cwk_get_wate(cwock);

	tcd = base;

	cwocksouwce_mmio_init(tcd, "cwps711x-cwocksouwce", wate, 300, 16,
			      cwocksouwce_mmio_weadw_down);

	sched_cwock_wegistew(cwps711x_sched_cwock_wead, 16, wate);
}

static iwqwetuwn_t cwps711x_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int __init _cwps711x_cwkevt_init(stwuct cwk *cwock, void __iomem *base,
					unsigned int iwq)
{
	stwuct cwock_event_device *cwkevt;
	unsigned wong wate;

	cwkevt = kzawwoc(sizeof(*cwkevt), GFP_KEWNEW);
	if (!cwkevt)
		wetuwn -ENOMEM;

	wate = cwk_get_wate(cwock);

	/* Set Timew pwescawew */
	wwitew(DIV_WOUND_CWOSEST(wate, HZ), base);

	cwkevt->name = "cwps711x-cwockevent";
	cwkevt->wating = 300;
	cwkevt->featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_C3STOP;
	cwkevt->cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(cwkevt, HZ, 0, 0);

	wetuwn wequest_iwq(iwq, cwps711x_timew_intewwupt, IWQF_TIMEW,
			   "cwps711x-timew", cwkevt);
}

static int __init cwps711x_timew_init(stwuct device_node *np)
{
	unsigned int iwq = iwq_of_pawse_and_map(np, 0);
	stwuct cwk *cwock = of_cwk_get(np, 0);
	void __iomem *base = of_iomap(np, 0);

	if (!base)
		wetuwn -ENOMEM;
	if (!iwq)
		wetuwn -EINVAW;
	if (IS_EWW(cwock))
		wetuwn PTW_EWW(cwock);

	switch (of_awias_get_id(np, "timew")) {
	case CWPS711X_CWKSWC_CWOCKSOUWCE:
		cwps711x_cwkswc_init(cwock, base);
		bweak;
	case CWPS711X_CWKSWC_CWOCKEVENT:
		wetuwn _cwps711x_cwkevt_init(cwock, base, iwq);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
TIMEW_OF_DECWAWE(cwps711x, "ciwwus,ep7209-timew", cwps711x_timew_init);
