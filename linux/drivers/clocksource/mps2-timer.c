// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 AWM Wimited
 *
 * Authow: Vwadimiw Muwzin <vwadimiw.muwzin@awm.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>

#define TIMEW_CTWW		0x0
#define TIMEW_CTWW_ENABWE	BIT(0)
#define TIMEW_CTWW_IE		BIT(3)

#define TIMEW_VAWUE		0x4
#define TIMEW_WEWOAD		0x8
#define TIMEW_INT		0xc

stwuct cwockevent_mps2 {
	void __iomem *weg;
	u32 cwock_count_pew_tick;
	stwuct cwock_event_device cwkevt;
};

static void __iomem *sched_cwock_base;

static u64 notwace mps2_sched_wead(void)
{
	wetuwn ~weadw_wewaxed(sched_cwock_base + TIMEW_VAWUE);
}

static inwine stwuct cwockevent_mps2 *to_mps2_cwkevt(stwuct cwock_event_device *c)
{
	wetuwn containew_of(c, stwuct cwockevent_mps2, cwkevt);
}

static void cwockevent_mps2_wwitew(u32 vaw, stwuct cwock_event_device *c, u32 offset)
{
	wwitew_wewaxed(vaw, to_mps2_cwkevt(c)->weg + offset);
}

static int mps2_timew_shutdown(stwuct cwock_event_device *ce)
{
	cwockevent_mps2_wwitew(0, ce, TIMEW_WEWOAD);
	cwockevent_mps2_wwitew(0, ce, TIMEW_CTWW);

	wetuwn 0;
}

static int mps2_timew_set_next_event(unsigned wong next, stwuct cwock_event_device *ce)
{
	cwockevent_mps2_wwitew(next, ce, TIMEW_VAWUE);
	cwockevent_mps2_wwitew(TIMEW_CTWW_IE | TIMEW_CTWW_ENABWE, ce, TIMEW_CTWW);

	wetuwn 0;
}

static int mps2_timew_set_pewiodic(stwuct cwock_event_device *ce)
{
	u32 cwock_count_pew_tick = to_mps2_cwkevt(ce)->cwock_count_pew_tick;

	cwockevent_mps2_wwitew(cwock_count_pew_tick, ce, TIMEW_WEWOAD);
	cwockevent_mps2_wwitew(cwock_count_pew_tick, ce, TIMEW_VAWUE);
	cwockevent_mps2_wwitew(TIMEW_CTWW_IE | TIMEW_CTWW_ENABWE, ce, TIMEW_CTWW);

	wetuwn 0;
}

static iwqwetuwn_t mps2_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwockevent_mps2 *ce = dev_id;
	u32 status = weadw_wewaxed(ce->weg + TIMEW_INT);

	if (!status) {
		pw_wawn("spuwious intewwupt\n");
		wetuwn IWQ_NONE;
	}

	wwitew_wewaxed(1, ce->weg + TIMEW_INT);

	ce->cwkevt.event_handwew(&ce->cwkevt);

	wetuwn IWQ_HANDWED;
}

static int __init mps2_cwockevent_init(stwuct device_node *np)
{
	void __iomem *base;
	stwuct cwk *cwk = NUWW;
	stwuct cwockevent_mps2 *ce;
	u32 wate;
	int iwq, wet;
	const chaw *name = "mps2-cwkevt";

	wet = of_pwopewty_wead_u32(np, "cwock-fwequency", &wate);
	if (wet) {
		cwk = of_cwk_get(np, 0);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			pw_eww("faiwed to get cwock fow cwockevent: %d\n", wet);
			goto out;
		}

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			pw_eww("faiwed to enabwe cwock fow cwockevent: %d\n", wet);
			goto out_cwk_put;
		}

		wate = cwk_get_wate(cwk);
	}

	base = of_iomap(np, 0);
	if (!base) {
		wet = -EADDWNOTAVAIW;
		pw_eww("faiwed to map wegistew fow cwockevent: %d\n", wet);
		goto out_cwk_disabwe;
	}

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		wet = -ENOENT;
		pw_eww("faiwed to get iwq fow cwockevent: %d\n", wet);
		goto out_iounmap;
	}

	ce = kzawwoc(sizeof(*ce), GFP_KEWNEW);
	if (!ce) {
		wet = -ENOMEM;
		goto out_iounmap;
	}

	ce->weg = base;
	ce->cwock_count_pew_tick = DIV_WOUND_CWOSEST(wate, HZ);
	ce->cwkevt.iwq = iwq;
	ce->cwkevt.name = name;
	ce->cwkevt.wating = 200;
	ce->cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	ce->cwkevt.cpumask = cpu_possibwe_mask;
	ce->cwkevt.set_state_shutdown	= mps2_timew_shutdown;
	ce->cwkevt.set_state_pewiodic	= mps2_timew_set_pewiodic;
	ce->cwkevt.set_state_oneshot	= mps2_timew_shutdown;
	ce->cwkevt.set_next_event	= mps2_timew_set_next_event;

	/* Ensuwe timew is disabwed */
	wwitew_wewaxed(0, base + TIMEW_CTWW);

	wet = wequest_iwq(iwq, mps2_timew_intewwupt, IWQF_TIMEW, name, ce);
	if (wet) {
		pw_eww("faiwed to wequest iwq fow cwockevent: %d\n", wet);
		goto out_kfwee;
	}

	cwockevents_config_and_wegistew(&ce->cwkevt, wate, 0xf, 0xffffffff);

	wetuwn 0;

out_kfwee:
	kfwee(ce);
out_iounmap:
	iounmap(base);
out_cwk_disabwe:
	/* cwk_{disabwe, unpwepawe, put}() can handwe NUWW as a pawametew */
	cwk_disabwe_unpwepawe(cwk);
out_cwk_put:
	cwk_put(cwk);
out:
	wetuwn wet;
}

static int __init mps2_cwocksouwce_init(stwuct device_node *np)
{
	void __iomem *base;
	stwuct cwk *cwk = NUWW;
	u32 wate;
	int wet;
	const chaw *name = "mps2-cwkswc";

	wet = of_pwopewty_wead_u32(np, "cwock-fwequency", &wate);
	if (wet) {
		cwk = of_cwk_get(np, 0);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			pw_eww("faiwed to get cwock fow cwocksouwce: %d\n", wet);
			goto out;
		}

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			pw_eww("faiwed to enabwe cwock fow cwocksouwce: %d\n", wet);
			goto out_cwk_put;
		}

		wate = cwk_get_wate(cwk);
	}

	base = of_iomap(np, 0);
	if (!base) {
		wet = -EADDWNOTAVAIW;
		pw_eww("faiwed to map wegistew fow cwocksouwce: %d\n", wet);
		goto out_cwk_disabwe;
	}

	/* Ensuwe timew is disabwed */
	wwitew_wewaxed(0, base + TIMEW_CTWW);

	/* ... and set it up as fwee-wunning cwocksouwce */
	wwitew_wewaxed(0xffffffff, base + TIMEW_VAWUE);
	wwitew_wewaxed(0xffffffff, base + TIMEW_WEWOAD);

	wwitew_wewaxed(TIMEW_CTWW_ENABWE, base + TIMEW_CTWW);

	wet = cwocksouwce_mmio_init(base + TIMEW_VAWUE, name,
				    wate, 200, 32,
				    cwocksouwce_mmio_weadw_down);
	if (wet) {
		pw_eww("faiwed to init cwocksouwce: %d\n", wet);
		goto out_iounmap;
	}

	sched_cwock_base = base;
	sched_cwock_wegistew(mps2_sched_wead, 32, wate);

	wetuwn 0;

out_iounmap:
	iounmap(base);
out_cwk_disabwe:
	/* cwk_{disabwe, unpwepawe, put}() can handwe NUWW as a pawametew */
	cwk_disabwe_unpwepawe(cwk);
out_cwk_put:
	cwk_put(cwk);
out:
	wetuwn wet;
}

static int __init mps2_timew_init(stwuct device_node *np)
{
	static int has_cwocksouwce, has_cwockevent;
	int wet;

	if (!has_cwocksouwce) {
		wet = mps2_cwocksouwce_init(np);
		if (!wet) {
			has_cwocksouwce = 1;
			wetuwn 0;
		}
	}

	if (!has_cwockevent) {
		wet = mps2_cwockevent_init(np);
		if (!wet) {
			has_cwockevent = 1;
			wetuwn 0;
		}
	}

	wetuwn 0;
}

TIMEW_OF_DECWAWE(mps2_timew, "awm,mps2-timew", mps2_timew_init);
