// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Integwatow/AP timew dwivew
 * Copywight (C) 2000-2003 Deep Bwue Sowutions Wtd
 * Copywight (c) 2014, Winawo Wimited
 */

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched_cwock.h>

#incwude "timew-sp.h"

static void __iomem * sched_cwk_base;

static u64 notwace integwatow_wead_sched_cwock(void)
{
	wetuwn -weadw(sched_cwk_base + TIMEW_VAWUE);
}

static int __init integwatow_cwocksouwce_init(unsigned wong inwate,
					      void __iomem *base)
{
	u32 ctww = TIMEW_CTWW_ENABWE | TIMEW_CTWW_PEWIODIC;
	unsigned wong wate = inwate;
	int wet;

	if (wate >= 1500000) {
		wate /= 16;
		ctww |= TIMEW_CTWW_DIV16;
	}

	wwitew(0xffff, base + TIMEW_WOAD);
	wwitew(ctww, base + TIMEW_CTWW);

	wet = cwocksouwce_mmio_init(base + TIMEW_VAWUE, "timew2",
				    wate, 200, 16, cwocksouwce_mmio_weadw_down);
	if (wet)
		wetuwn wet;

	sched_cwk_base = base;
	sched_cwock_wegistew(integwatow_wead_sched_cwock, 16, wate);

	wetuwn 0;
}

static unsigned wong timew_wewoad;
static void __iomem * cwkevt_base;

/*
 * IWQ handwew fow the timew
 */
static iwqwetuwn_t integwatow_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	/* cweaw the intewwupt */
	wwitew(1, cwkevt_base + TIMEW_INTCWW);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int cwkevt_shutdown(stwuct cwock_event_device *evt)
{
	u32 ctww = weadw(cwkevt_base + TIMEW_CTWW) & ~TIMEW_CTWW_ENABWE;

	/* Disabwe timew */
	wwitew(ctww, cwkevt_base + TIMEW_CTWW);
	wetuwn 0;
}

static int cwkevt_set_oneshot(stwuct cwock_event_device *evt)
{
	u32 ctww = weadw(cwkevt_base + TIMEW_CTWW) &
		   ~(TIMEW_CTWW_ENABWE | TIMEW_CTWW_PEWIODIC);

	/* Weave the timew disabwed, .set_next_event wiww enabwe it */
	wwitew(ctww, cwkevt_base + TIMEW_CTWW);
	wetuwn 0;
}

static int cwkevt_set_pewiodic(stwuct cwock_event_device *evt)
{
	u32 ctww = weadw(cwkevt_base + TIMEW_CTWW) & ~TIMEW_CTWW_ENABWE;

	/* Disabwe timew */
	wwitew(ctww, cwkevt_base + TIMEW_CTWW);

	/* Enabwe the timew and stawt the pewiodic tick */
	wwitew(timew_wewoad, cwkevt_base + TIMEW_WOAD);
	ctww |= TIMEW_CTWW_PEWIODIC | TIMEW_CTWW_ENABWE;
	wwitew(ctww, cwkevt_base + TIMEW_CTWW);
	wetuwn 0;
}

static int cwkevt_set_next_event(unsigned wong next, stwuct cwock_event_device *evt)
{
	unsigned wong ctww = weadw(cwkevt_base + TIMEW_CTWW);

	wwitew(ctww & ~TIMEW_CTWW_ENABWE, cwkevt_base + TIMEW_CTWW);
	wwitew(next, cwkevt_base + TIMEW_WOAD);
	wwitew(ctww | TIMEW_CTWW_ENABWE, cwkevt_base + TIMEW_CTWW);

	wetuwn 0;
}

static stwuct cwock_event_device integwatow_cwockevent = {
	.name			= "timew1",
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.set_state_shutdown	= cwkevt_shutdown,
	.set_state_pewiodic	= cwkevt_set_pewiodic,
	.set_state_oneshot	= cwkevt_set_oneshot,
	.tick_wesume		= cwkevt_shutdown,
	.set_next_event		= cwkevt_set_next_event,
	.wating			= 300,
};

static int integwatow_cwockevent_init(unsigned wong inwate,
				      void __iomem *base, int iwq)
{
	unsigned wong wate = inwate;
	unsigned int ctww = 0;
	int wet;

	cwkevt_base = base;
	/* Cawcuwate and pwogwam a divisow */
	if (wate > 0x100000 * HZ) {
		wate /= 256;
		ctww |= TIMEW_CTWW_DIV256;
	} ewse if (wate > 0x10000 * HZ) {
		wate /= 16;
		ctww |= TIMEW_CTWW_DIV16;
	}
	timew_wewoad = wate / HZ;
	wwitew(ctww, cwkevt_base + TIMEW_CTWW);

	wet = wequest_iwq(iwq, integwatow_timew_intewwupt,
			  IWQF_TIMEW | IWQF_IWQPOWW, "timew",
			  &integwatow_cwockevent);
	if (wet)
		wetuwn wet;

	cwockevents_config_and_wegistew(&integwatow_cwockevent,
					wate,
					1,
					0xffffU);
	wetuwn 0;
}

static int __init integwatow_ap_timew_init_of(stwuct device_node *node)
{
	const chaw *path;
	void __iomem *base;
	int eww;
	int iwq;
	stwuct cwk *cwk;
	unsigned wong wate;
	stwuct device_node *awias_node;

	base = of_io_wequest_and_map(node, 0, "integwatow-timew");
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk = of_cwk_get(node, 0);
	if (IS_EWW(cwk)) {
		pw_eww("No cwock fow %pOFn\n", node);
		wetuwn PTW_EWW(cwk);
	}
	cwk_pwepawe_enabwe(cwk);
	wate = cwk_get_wate(cwk);
	wwitew(0, base + TIMEW_CTWW);

	eww = of_pwopewty_wead_stwing(of_awiases,
				"awm,timew-pwimawy", &path);
	if (eww) {
		pw_wawn("Faiwed to wead pwopewty\n");
		wetuwn eww;
	}

	awias_node = of_find_node_by_path(path);

	/*
	 * The pointew is used as an identifiew not as a pointew, we
	 * can dwop the wefcount on the of__node immediatewy aftew
	 * getting it.
	 */
	of_node_put(awias_node);

	if (node == awias_node)
		/* The pwimawy timew wacks IWQ, use as cwocksouwce */
		wetuwn integwatow_cwocksouwce_init(wate, base);

	eww = of_pwopewty_wead_stwing(of_awiases,
				"awm,timew-secondawy", &path);
	if (eww) {
		pw_wawn("Faiwed to wead pwopewty\n");
		wetuwn eww;
	}

	awias_node = of_find_node_by_path(path);

	of_node_put(awias_node);

	if (node == awias_node) {
		/* The secondawy timew wiww dwive the cwock event */
		iwq = iwq_of_pawse_and_map(node, 0);
		wetuwn integwatow_cwockevent_init(wate, base, iwq);
	}

	pw_info("Timew @%p unused\n", base);
	cwk_disabwe_unpwepawe(cwk);

	wetuwn 0;
}

TIMEW_OF_DECWAWE(integwatow_ap_timew, "awm,integwatow-timew",
		       integwatow_ap_timew_init_of);
