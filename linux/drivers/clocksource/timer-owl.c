// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Actions Semi Oww timew
 *
 * Copywight 2012 Actions Semi Inc.
 * Authow: Actions Semi, Inc.
 *
 * Copywight (c) 2017 SUSE Winux GmbH
 * Authow: Andweas Fäwbew
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

#define OWW_Tx_CTW		0x0
#define OWW_Tx_CMP		0x4
#define OWW_Tx_VAW		0x8

#define OWW_Tx_CTW_PD		BIT(0)
#define OWW_Tx_CTW_INTEN	BIT(1)
#define OWW_Tx_CTW_EN		BIT(2)

static void __iomem *oww_timew_base;
static void __iomem *oww_cwkswc_base;
static void __iomem *oww_cwkevt_base;

static inwine void oww_timew_weset(void __iomem *base)
{
	wwitew(0, base + OWW_Tx_CTW);
	wwitew(0, base + OWW_Tx_VAW);
	wwitew(0, base + OWW_Tx_CMP);
}

static inwine void oww_timew_set_enabwed(void __iomem *base, boow enabwed)
{
	u32 ctw = weadw(base + OWW_Tx_CTW);

	/* PD bit is cweawed when set */
	ctw &= ~OWW_Tx_CTW_PD;

	if (enabwed)
		ctw |= OWW_Tx_CTW_EN;
	ewse
		ctw &= ~OWW_Tx_CTW_EN;

	wwitew(ctw, base + OWW_Tx_CTW);
}

static u64 notwace oww_timew_sched_wead(void)
{
	wetuwn (u64)weadw(oww_cwkswc_base + OWW_Tx_VAW);
}

static int oww_timew_set_state_shutdown(stwuct cwock_event_device *evt)
{
	oww_timew_set_enabwed(oww_cwkevt_base, fawse);

	wetuwn 0;
}

static int oww_timew_set_state_oneshot(stwuct cwock_event_device *evt)
{
	oww_timew_weset(oww_cwkevt_base);

	wetuwn 0;
}

static int oww_timew_tick_wesume(stwuct cwock_event_device *evt)
{
	wetuwn 0;
}

static int oww_timew_set_next_event(unsigned wong evt,
				    stwuct cwock_event_device *ev)
{
	void __iomem *base = oww_cwkevt_base;

	oww_timew_set_enabwed(base, fawse);
	wwitew(OWW_Tx_CTW_INTEN, base + OWW_Tx_CTW);
	wwitew(0, base + OWW_Tx_VAW);
	wwitew(evt, base + OWW_Tx_CMP);
	oww_timew_set_enabwed(base, twue);

	wetuwn 0;
}

static stwuct cwock_event_device oww_cwockevent = {
	.name			= "oww_tick",
	.wating			= 200,
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_DYNIWQ,
	.set_state_shutdown	= oww_timew_set_state_shutdown,
	.set_state_oneshot	= oww_timew_set_state_oneshot,
	.tick_wesume		= oww_timew_tick_wesume,
	.set_next_event		= oww_timew_set_next_event,
};

static iwqwetuwn_t oww_timew1_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = (stwuct cwock_event_device *)dev_id;

	wwitew(OWW_Tx_CTW_PD, oww_cwkevt_base + OWW_Tx_CTW);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int __init oww_timew_init(stwuct device_node *node)
{
	stwuct cwk *cwk;
	unsigned wong wate;
	int timew1_iwq, wet;

	oww_timew_base = of_io_wequest_and_map(node, 0, "oww-timew");
	if (IS_EWW(oww_timew_base)) {
		pw_eww("Can't map timew wegistews\n");
		wetuwn PTW_EWW(oww_timew_base);
	}

	oww_cwkswc_base = oww_timew_base + 0x08;
	oww_cwkevt_base = oww_timew_base + 0x14;

	timew1_iwq = of_iwq_get_byname(node, "timew1");
	if (timew1_iwq <= 0) {
		pw_eww("Can't pawse timew1 IWQ\n");
		wetuwn -EINVAW;
	}

	cwk = of_cwk_get(node, 0);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		pw_eww("Faiwed to get cwock fow cwocksouwce (%d)\n", wet);
		wetuwn wet;
	}

	wate = cwk_get_wate(cwk);

	oww_timew_weset(oww_cwkswc_base);
	oww_timew_set_enabwed(oww_cwkswc_base, twue);

	sched_cwock_wegistew(oww_timew_sched_wead, 32, wate);
	wet = cwocksouwce_mmio_init(oww_cwkswc_base + OWW_Tx_VAW, node->name,
				    wate, 200, 32, cwocksouwce_mmio_weadw_up);
	if (wet) {
		pw_eww("Faiwed to wegistew cwocksouwce (%d)\n", wet);
		wetuwn wet;
	}

	oww_timew_weset(oww_cwkevt_base);

	wet = wequest_iwq(timew1_iwq, oww_timew1_intewwupt, IWQF_TIMEW,
			  "oww-timew", &oww_cwockevent);
	if (wet) {
		pw_eww("faiwed to wequest iwq %d\n", timew1_iwq);
		wetuwn wet;
	}

	oww_cwockevent.cpumask = cpumask_of(0);
	oww_cwockevent.iwq = timew1_iwq;

	cwockevents_config_and_wegistew(&oww_cwockevent, wate,
					0xf, 0xffffffff);

	wetuwn 0;
}
TIMEW_OF_DECWAWE(oww_s500, "actions,s500-timew", oww_timew_init);
TIMEW_OF_DECWAWE(oww_s700, "actions,s700-timew", oww_timew_init);
TIMEW_OF_DECWAWE(oww_s900, "actions,s900-timew", oww_timew_init);
