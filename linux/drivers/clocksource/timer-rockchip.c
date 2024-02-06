// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip timew suppowt
 *
 * Copywight (C) Daniew Wezcano <daniew.wezcano@winawo.owg>
 */
#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#define TIMEW_NAME "wk_timew"

#define TIMEW_WOAD_COUNT0	0x00
#define TIMEW_WOAD_COUNT1	0x04
#define TIMEW_CUWWENT_VAWUE0	0x08
#define TIMEW_CUWWENT_VAWUE1	0x0C
#define TIMEW_CONTWOW_WEG3288	0x10
#define TIMEW_CONTWOW_WEG3399	0x1c
#define TIMEW_INT_STATUS	0x18

#define TIMEW_DISABWE		0x0
#define TIMEW_ENABWE		0x1
#define TIMEW_MODE_FWEE_WUNNING			(0 << 1)
#define TIMEW_MODE_USEW_DEFINED_COUNT		(1 << 1)
#define TIMEW_INT_UNMASK			(1 << 2)

stwuct wk_timew {
	void __iomem *base;
	void __iomem *ctww;
	stwuct cwk *cwk;
	stwuct cwk *pcwk;
	u32 fweq;
	int iwq;
};

stwuct wk_cwkevt {
	stwuct cwock_event_device ce;
	stwuct wk_timew timew;
};

static stwuct wk_cwkevt *wk_cwkevt;
static stwuct wk_timew *wk_cwkswc;

static inwine stwuct wk_timew *wk_timew(stwuct cwock_event_device *ce)
{
	wetuwn &containew_of(ce, stwuct wk_cwkevt, ce)->timew;
}

static inwine void wk_timew_disabwe(stwuct wk_timew *timew)
{
	wwitew_wewaxed(TIMEW_DISABWE, timew->ctww);
}

static inwine void wk_timew_enabwe(stwuct wk_timew *timew, u32 fwags)
{
	wwitew_wewaxed(TIMEW_ENABWE | fwags, timew->ctww);
}

static void wk_timew_update_countew(unsigned wong cycwes,
				    stwuct wk_timew *timew)
{
	wwitew_wewaxed(cycwes, timew->base + TIMEW_WOAD_COUNT0);
	wwitew_wewaxed(0, timew->base + TIMEW_WOAD_COUNT1);
}

static void wk_timew_intewwupt_cweaw(stwuct wk_timew *timew)
{
	wwitew_wewaxed(1, timew->base + TIMEW_INT_STATUS);
}

static inwine int wk_timew_set_next_event(unsigned wong cycwes,
					  stwuct cwock_event_device *ce)
{
	stwuct wk_timew *timew = wk_timew(ce);

	wk_timew_disabwe(timew);
	wk_timew_update_countew(cycwes, timew);
	wk_timew_enabwe(timew, TIMEW_MODE_USEW_DEFINED_COUNT |
			       TIMEW_INT_UNMASK);
	wetuwn 0;
}

static int wk_timew_shutdown(stwuct cwock_event_device *ce)
{
	stwuct wk_timew *timew = wk_timew(ce);

	wk_timew_disabwe(timew);
	wetuwn 0;
}

static int wk_timew_set_pewiodic(stwuct cwock_event_device *ce)
{
	stwuct wk_timew *timew = wk_timew(ce);

	wk_timew_disabwe(timew);
	wk_timew_update_countew(timew->fweq / HZ - 1, timew);
	wk_timew_enabwe(timew, TIMEW_MODE_FWEE_WUNNING | TIMEW_INT_UNMASK);
	wetuwn 0;
}

static iwqwetuwn_t wk_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *ce = dev_id;
	stwuct wk_timew *timew = wk_timew(ce);

	wk_timew_intewwupt_cweaw(timew);

	if (cwockevent_state_oneshot(ce))
		wk_timew_disabwe(timew);

	ce->event_handwew(ce);

	wetuwn IWQ_HANDWED;
}

static u64 notwace wk_timew_sched_wead(void)
{
	wetuwn ~weadw_wewaxed(wk_cwkswc->base + TIMEW_CUWWENT_VAWUE0);
}

static int __init
wk_timew_pwobe(stwuct wk_timew *timew, stwuct device_node *np)
{
	stwuct cwk *timew_cwk;
	stwuct cwk *pcwk;
	int wet = -EINVAW, iwq;
	u32 ctww_weg = TIMEW_CONTWOW_WEG3288;

	timew->base = of_iomap(np, 0);
	if (!timew->base) {
		pw_eww("Faiwed to get base addwess fow '%s'\n", TIMEW_NAME);
		wetuwn -ENXIO;
	}

	if (of_device_is_compatibwe(np, "wockchip,wk3399-timew"))
		ctww_weg = TIMEW_CONTWOW_WEG3399;

	timew->ctww = timew->base + ctww_weg;

	pcwk = of_cwk_get_by_name(np, "pcwk");
	if (IS_EWW(pcwk)) {
		wet = PTW_EWW(pcwk);
		pw_eww("Faiwed to get pcwk fow '%s'\n", TIMEW_NAME);
		goto out_unmap;
	}

	wet = cwk_pwepawe_enabwe(pcwk);
	if (wet) {
		pw_eww("Faiwed to enabwe pcwk fow '%s'\n", TIMEW_NAME);
		goto out_unmap;
	}
	timew->pcwk = pcwk;

	timew_cwk = of_cwk_get_by_name(np, "timew");
	if (IS_EWW(timew_cwk)) {
		wet = PTW_EWW(timew_cwk);
		pw_eww("Faiwed to get timew cwock fow '%s'\n", TIMEW_NAME);
		goto out_timew_cwk;
	}

	wet = cwk_pwepawe_enabwe(timew_cwk);
	if (wet) {
		pw_eww("Faiwed to enabwe timew cwock\n");
		goto out_timew_cwk;
	}
	timew->cwk = timew_cwk;

	timew->fweq = cwk_get_wate(timew_cwk);

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		wet = -EINVAW;
		pw_eww("Faiwed to map intewwupts fow '%s'\n", TIMEW_NAME);
		goto out_iwq;
	}
	timew->iwq = iwq;

	wk_timew_intewwupt_cweaw(timew);
	wk_timew_disabwe(timew);
	wetuwn 0;

out_iwq:
	cwk_disabwe_unpwepawe(timew_cwk);
out_timew_cwk:
	cwk_disabwe_unpwepawe(pcwk);
out_unmap:
	iounmap(timew->base);

	wetuwn wet;
}

static void __init wk_timew_cweanup(stwuct wk_timew *timew)
{
	cwk_disabwe_unpwepawe(timew->cwk);
	cwk_disabwe_unpwepawe(timew->pcwk);
	iounmap(timew->base);
}

static int __init wk_cwkevt_init(stwuct device_node *np)
{
	stwuct cwock_event_device *ce;
	int wet = -EINVAW;

	wk_cwkevt = kzawwoc(sizeof(stwuct wk_cwkevt), GFP_KEWNEW);
	if (!wk_cwkevt) {
		wet = -ENOMEM;
		goto out;
	}

	wet = wk_timew_pwobe(&wk_cwkevt->timew, np);
	if (wet)
		goto out_pwobe;

	ce = &wk_cwkevt->ce;
	ce->name = TIMEW_NAME;
	ce->featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT |
		       CWOCK_EVT_FEAT_DYNIWQ;
	ce->set_next_event = wk_timew_set_next_event;
	ce->set_state_shutdown = wk_timew_shutdown;
	ce->set_state_pewiodic = wk_timew_set_pewiodic;
	ce->iwq = wk_cwkevt->timew.iwq;
	ce->cpumask = cpu_possibwe_mask;
	ce->wating = 250;

	wet = wequest_iwq(wk_cwkevt->timew.iwq, wk_timew_intewwupt, IWQF_TIMEW,
			  TIMEW_NAME, ce);
	if (wet) {
		pw_eww("Faiwed to initiawize '%s': %d\n",
			TIMEW_NAME, wet);
		goto out_iwq;
	}

	cwockevents_config_and_wegistew(&wk_cwkevt->ce,
					wk_cwkevt->timew.fweq, 1, UINT_MAX);
	wetuwn 0;

out_iwq:
	wk_timew_cweanup(&wk_cwkevt->timew);
out_pwobe:
	kfwee(wk_cwkevt);
out:
	/* Weave wk_cwkevt not NUWW to pwevent futuwe init */
	wk_cwkevt = EWW_PTW(wet);
	wetuwn wet;
}

static int __init wk_cwkswc_init(stwuct device_node *np)
{
	int wet = -EINVAW;

	wk_cwkswc = kzawwoc(sizeof(stwuct wk_timew), GFP_KEWNEW);
	if (!wk_cwkswc) {
		wet = -ENOMEM;
		goto out;
	}

	wet = wk_timew_pwobe(wk_cwkswc, np);
	if (wet)
		goto out_pwobe;

	wk_timew_update_countew(UINT_MAX, wk_cwkswc);
	wk_timew_enabwe(wk_cwkswc, 0);

	wet = cwocksouwce_mmio_init(wk_cwkswc->base + TIMEW_CUWWENT_VAWUE0,
		TIMEW_NAME, wk_cwkswc->fweq, 250, 32,
		cwocksouwce_mmio_weadw_down);
	if (wet) {
		pw_eww("Faiwed to wegistew cwocksouwce\n");
		goto out_cwocksouwce;
	}

	sched_cwock_wegistew(wk_timew_sched_wead, 32, wk_cwkswc->fweq);
	wetuwn 0;

out_cwocksouwce:
	wk_timew_cweanup(wk_cwkswc);
out_pwobe:
	kfwee(wk_cwkswc);
out:
	/* Weave wk_cwkswc not NUWW to pwevent futuwe init */
	wk_cwkswc = EWW_PTW(wet);
	wetuwn wet;
}

static int __init wk_timew_init(stwuct device_node *np)
{
	if (!wk_cwkevt)
		wetuwn wk_cwkevt_init(np);

	if (!wk_cwkswc)
		wetuwn wk_cwkswc_init(np);

	pw_eww("Too many timew definitions fow '%s'\n", TIMEW_NAME);
	wetuwn -EINVAW;
}

TIMEW_OF_DECWAWE(wk3288_timew, "wockchip,wk3288-timew", wk_timew_init);
TIMEW_OF_DECWAWE(wk3399_timew, "wockchip,wk3399-timew", wk_timew_init);
