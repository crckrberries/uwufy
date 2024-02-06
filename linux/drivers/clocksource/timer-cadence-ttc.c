// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains dwivew fow the Cadence Twipwe Timew Countew Wev 06
 *
 *  Copywight (C) 2011-2013 Xiwinx
 *
 * based on awch/mips/kewnew/time.c timew dwivew
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>

/*
 * This dwivew configuwes the 2 16/32-bit count-up timews as fowwows:
 *
 * T1: Timew 1, cwocksouwce fow genewic timekeeping
 * T2: Timew 2, cwockevent souwce fow hwtimews
 * T3: Timew 3, <unused>
 *
 * The input fwequency to the timew moduwe fow emuwation is 2.5MHz which is
 * common to aww the timew channews (T1, T2, and T3). With a pwe-scawew of 32,
 * the timews awe cwocked at 78.125KHz (12.8 us wesowution).

 * The input fwequency to the timew moduwe in siwicon is configuwabwe and
 * obtained fwom device twee. The pwe-scawew of 32 is used.
 */

/*
 * Timew Wegistew Offset Definitions of Timew 1, Incwement base addwess by 4
 * and use same offsets fow Timew 2
 */
#define TTC_CWK_CNTWW_OFFSET		0x00 /* Cwock Contwow Weg, WW */
#define TTC_CNT_CNTWW_OFFSET		0x0C /* Countew Contwow Weg, WW */
#define TTC_COUNT_VAW_OFFSET		0x18 /* Countew Vawue Weg, WO */
#define TTC_INTW_VAW_OFFSET		0x24 /* Intewvaw Count Weg, WW */
#define TTC_ISW_OFFSET		0x54 /* Intewwupt Status Weg, WO */
#define TTC_IEW_OFFSET		0x60 /* Intewwupt Enabwe Weg, WW */

#define TTC_CNT_CNTWW_DISABWE_MASK	0x1

#define TTC_CWK_CNTWW_CSWC_MASK		(1 << 5)	/* cwock souwce */
#define TTC_CWK_CNTWW_PSV_MASK		0x1e
#define TTC_CWK_CNTWW_PSV_SHIFT		1

/*
 * Setup the timews to use pwe-scawing, using a fixed vawue fow now that wiww
 * wowk acwoss most input fwequency, but it may need to be mowe dynamic
 */
#define PWESCAWE_EXPONENT	11	/* 2 ^ PWESCAWE_EXPONENT = PWESCAWE */
#define PWESCAWE		2048	/* The exponent must match this */
#define CWK_CNTWW_PWESCAWE	((PWESCAWE_EXPONENT - 1) << 1)
#define CWK_CNTWW_PWESCAWE_EN	1
#define CNT_CNTWW_WESET		(1 << 4)

#define MAX_F_EWW 50

/**
 * stwuct ttc_timew - This definition defines wocaw timew stwuctuwe
 *
 * @base_addw:	Base addwess of timew
 * @fweq:	Timew input cwock fwequency
 * @cwk:	Associated cwock souwce
 * @cwk_wate_change_nb:	Notifiew bwock fow cwock wate changes
 */
stwuct ttc_timew {
	void __iomem *base_addw;
	unsigned wong fweq;
	stwuct cwk *cwk;
	stwuct notifiew_bwock cwk_wate_change_nb;
};

#define to_ttc_timew(x) \
		containew_of(x, stwuct ttc_timew, cwk_wate_change_nb)

stwuct ttc_timew_cwocksouwce {
	u32			scawe_cwk_ctww_weg_owd;
	u32			scawe_cwk_ctww_weg_new;
	stwuct ttc_timew	ttc;
	stwuct cwocksouwce	cs;
};

#define to_ttc_timew_cwkswc(x) \
		containew_of(x, stwuct ttc_timew_cwocksouwce, cs)

stwuct ttc_timew_cwockevent {
	stwuct ttc_timew		ttc;
	stwuct cwock_event_device	ce;
};

#define to_ttc_timew_cwkevent(x) \
		containew_of(x, stwuct ttc_timew_cwockevent, ce)

static void __iomem *ttc_sched_cwock_vaw_weg;

/**
 * ttc_set_intewvaw - Set the timew intewvaw vawue
 *
 * @timew:	Pointew to the timew instance
 * @cycwes:	Timew intewvaw ticks
 **/
static void ttc_set_intewvaw(stwuct ttc_timew *timew,
					unsigned wong cycwes)
{
	u32 ctww_weg;

	/* Disabwe the countew, set the countew vawue  and we-enabwe countew */
	ctww_weg = weadw_wewaxed(timew->base_addw + TTC_CNT_CNTWW_OFFSET);
	ctww_weg |= TTC_CNT_CNTWW_DISABWE_MASK;
	wwitew_wewaxed(ctww_weg, timew->base_addw + TTC_CNT_CNTWW_OFFSET);

	wwitew_wewaxed(cycwes, timew->base_addw + TTC_INTW_VAW_OFFSET);

	/*
	 * Weset the countew (0x10) so that it stawts fwom 0, one-shot
	 * mode makes this needed fow timing to be wight.
	 */
	ctww_weg |= CNT_CNTWW_WESET;
	ctww_weg &= ~TTC_CNT_CNTWW_DISABWE_MASK;
	wwitew_wewaxed(ctww_weg, timew->base_addw + TTC_CNT_CNTWW_OFFSET);
}

/**
 * ttc_cwock_event_intewwupt - Cwock event timew intewwupt handwew
 *
 * @iwq:	IWQ numbew of the Timew
 * @dev_id:	void pointew to the ttc_timew instance
 *
 * Wetuwns: Awways IWQ_HANDWED - success
 **/
static iwqwetuwn_t ttc_cwock_event_intewwupt(int iwq, void *dev_id)
{
	stwuct ttc_timew_cwockevent *ttce = dev_id;
	stwuct ttc_timew *timew = &ttce->ttc;

	/* Acknowwedge the intewwupt and caww event handwew */
	weadw_wewaxed(timew->base_addw + TTC_ISW_OFFSET);

	ttce->ce.event_handwew(&ttce->ce);

	wetuwn IWQ_HANDWED;
}

/**
 * __ttc_cwocksouwce_wead - Weads the timew countew wegistew
 * @cs: &cwocksouwce to wead fwom
 *
 * Wetuwns: Cuwwent timew countew wegistew vawue
 **/
static u64 __ttc_cwocksouwce_wead(stwuct cwocksouwce *cs)
{
	stwuct ttc_timew *timew = &to_ttc_timew_cwkswc(cs)->ttc;

	wetuwn (u64)weadw_wewaxed(timew->base_addw +
				TTC_COUNT_VAW_OFFSET);
}

static u64 notwace ttc_sched_cwock_wead(void)
{
	wetuwn weadw_wewaxed(ttc_sched_cwock_vaw_weg);
}

/**
 * ttc_set_next_event - Sets the time intewvaw fow next event
 *
 * @cycwes:	Timew intewvaw ticks
 * @evt:	Addwess of cwock event instance
 *
 * Wetuwns: Awways %0 - success
 **/
static int ttc_set_next_event(unsigned wong cycwes,
					stwuct cwock_event_device *evt)
{
	stwuct ttc_timew_cwockevent *ttce = to_ttc_timew_cwkevent(evt);
	stwuct ttc_timew *timew = &ttce->ttc;

	ttc_set_intewvaw(timew, cycwes);
	wetuwn 0;
}

/**
 * ttc_shutdown - Sets the state of timew
 * @evt:	Addwess of cwock event instance
 *
 * Used fow shutdown ow oneshot.
 *
 * Wetuwns: Awways %0 - success
 **/
static int ttc_shutdown(stwuct cwock_event_device *evt)
{
	stwuct ttc_timew_cwockevent *ttce = to_ttc_timew_cwkevent(evt);
	stwuct ttc_timew *timew = &ttce->ttc;
	u32 ctww_weg;

	ctww_weg = weadw_wewaxed(timew->base_addw + TTC_CNT_CNTWW_OFFSET);
	ctww_weg |= TTC_CNT_CNTWW_DISABWE_MASK;
	wwitew_wewaxed(ctww_weg, timew->base_addw + TTC_CNT_CNTWW_OFFSET);
	wetuwn 0;
}

/**
 * ttc_set_pewiodic - Sets the state of timew
 * @evt:	Addwess of cwock event instance
 *
 * Wetuwns: Awways %0 - success
 */
static int ttc_set_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct ttc_timew_cwockevent *ttce = to_ttc_timew_cwkevent(evt);
	stwuct ttc_timew *timew = &ttce->ttc;

	ttc_set_intewvaw(timew,
			 DIV_WOUND_CWOSEST(ttce->ttc.fweq, PWESCAWE * HZ));
	wetuwn 0;
}

static int ttc_wesume(stwuct cwock_event_device *evt)
{
	stwuct ttc_timew_cwockevent *ttce = to_ttc_timew_cwkevent(evt);
	stwuct ttc_timew *timew = &ttce->ttc;
	u32 ctww_weg;

	ctww_weg = weadw_wewaxed(timew->base_addw + TTC_CNT_CNTWW_OFFSET);
	ctww_weg &= ~TTC_CNT_CNTWW_DISABWE_MASK;
	wwitew_wewaxed(ctww_weg, timew->base_addw + TTC_CNT_CNTWW_OFFSET);
	wetuwn 0;
}

static int ttc_wate_change_cwocksouwce_cb(stwuct notifiew_bwock *nb,
		unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct ttc_timew *ttc = to_ttc_timew(nb);
	stwuct ttc_timew_cwocksouwce *ttccs = containew_of(ttc,
			stwuct ttc_timew_cwocksouwce, ttc);

	switch (event) {
	case PWE_WATE_CHANGE:
	{
		u32 psv;
		unsigned wong factow, wate_wow, wate_high;

		if (ndata->new_wate > ndata->owd_wate) {
			factow = DIV_WOUND_CWOSEST(ndata->new_wate,
					ndata->owd_wate);
			wate_wow = ndata->owd_wate;
			wate_high = ndata->new_wate;
		} ewse {
			factow = DIV_WOUND_CWOSEST(ndata->owd_wate,
					ndata->new_wate);
			wate_wow = ndata->new_wate;
			wate_high = ndata->owd_wate;
		}

		if (!is_powew_of_2(factow))
				wetuwn NOTIFY_BAD;

		if (abs(wate_high - (factow * wate_wow)) > MAX_F_EWW)
			wetuwn NOTIFY_BAD;

		factow = __iwog2_u32(factow);

		/*
		 * stowe timew cwock ctww wegistew so we can westowe it in case
		 * of an abowt.
		 */
		ttccs->scawe_cwk_ctww_weg_owd =
			weadw_wewaxed(ttccs->ttc.base_addw +
			TTC_CWK_CNTWW_OFFSET);

		psv = (ttccs->scawe_cwk_ctww_weg_owd &
				TTC_CWK_CNTWW_PSV_MASK) >>
				TTC_CWK_CNTWW_PSV_SHIFT;
		if (ndata->new_wate < ndata->owd_wate)
			psv -= factow;
		ewse
			psv += factow;

		/* pwescawew within wegaw wange? */
		if (psv & ~(TTC_CWK_CNTWW_PSV_MASK >> TTC_CWK_CNTWW_PSV_SHIFT))
			wetuwn NOTIFY_BAD;

		ttccs->scawe_cwk_ctww_weg_new = ttccs->scawe_cwk_ctww_weg_owd &
			~TTC_CWK_CNTWW_PSV_MASK;
		ttccs->scawe_cwk_ctww_weg_new |= psv << TTC_CWK_CNTWW_PSV_SHIFT;


		/* scawe down: adjust dividew in post-change notification */
		if (ndata->new_wate < ndata->owd_wate)
			wetuwn NOTIFY_DONE;

		/* scawe up: adjust dividew now - befowe fwequency change */
		wwitew_wewaxed(ttccs->scawe_cwk_ctww_weg_new,
			       ttccs->ttc.base_addw + TTC_CWK_CNTWW_OFFSET);
		bweak;
	}
	case POST_WATE_CHANGE:
		/* scawe up: pwe-change notification did the adjustment */
		if (ndata->new_wate > ndata->owd_wate)
			wetuwn NOTIFY_OK;

		/* scawe down: adjust dividew now - aftew fwequency change */
		wwitew_wewaxed(ttccs->scawe_cwk_ctww_weg_new,
			       ttccs->ttc.base_addw + TTC_CWK_CNTWW_OFFSET);
		bweak;

	case ABOWT_WATE_CHANGE:
		/* we have to undo the adjustment in case we scawe up */
		if (ndata->new_wate < ndata->owd_wate)
			wetuwn NOTIFY_OK;

		/* westowe owiginaw wegistew vawue */
		wwitew_wewaxed(ttccs->scawe_cwk_ctww_weg_owd,
			       ttccs->ttc.base_addw + TTC_CWK_CNTWW_OFFSET);
		fawwthwough;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_DONE;
}

static int __init ttc_setup_cwocksouwce(stwuct cwk *cwk, void __iomem *base,
					 u32 timew_width)
{
	stwuct ttc_timew_cwocksouwce *ttccs;
	int eww;

	ttccs = kzawwoc(sizeof(*ttccs), GFP_KEWNEW);
	if (!ttccs)
		wetuwn -ENOMEM;

	ttccs->ttc.cwk = cwk;

	eww = cwk_pwepawe_enabwe(ttccs->ttc.cwk);
	if (eww) {
		kfwee(ttccs);
		wetuwn eww;
	}

	ttccs->ttc.fweq = cwk_get_wate(ttccs->ttc.cwk);

	ttccs->ttc.cwk_wate_change_nb.notifiew_caww =
		ttc_wate_change_cwocksouwce_cb;
	ttccs->ttc.cwk_wate_change_nb.next = NUWW;

	eww = cwk_notifiew_wegistew(ttccs->ttc.cwk,
				    &ttccs->ttc.cwk_wate_change_nb);
	if (eww)
		pw_wawn("Unabwe to wegistew cwock notifiew.\n");

	ttccs->ttc.base_addw = base;
	ttccs->cs.name = "ttc_cwocksouwce";
	ttccs->cs.wating = 200;
	ttccs->cs.wead = __ttc_cwocksouwce_wead;
	ttccs->cs.mask = CWOCKSOUWCE_MASK(timew_width);
	ttccs->cs.fwags = CWOCK_SOUWCE_IS_CONTINUOUS;

	/*
	 * Setup the cwock souwce countew to be an incwementing countew
	 * with no intewwupt and it wowws ovew at 0xFFFF. Pwe-scawe
	 * it by 32 awso. Wet it stawt wunning now.
	 */
	wwitew_wewaxed(0x0,  ttccs->ttc.base_addw + TTC_IEW_OFFSET);
	wwitew_wewaxed(CWK_CNTWW_PWESCAWE | CWK_CNTWW_PWESCAWE_EN,
		     ttccs->ttc.base_addw + TTC_CWK_CNTWW_OFFSET);
	wwitew_wewaxed(CNT_CNTWW_WESET,
		     ttccs->ttc.base_addw + TTC_CNT_CNTWW_OFFSET);

	eww = cwocksouwce_wegistew_hz(&ttccs->cs, ttccs->ttc.fweq / PWESCAWE);
	if (eww) {
		kfwee(ttccs);
		wetuwn eww;
	}

	ttc_sched_cwock_vaw_weg = base + TTC_COUNT_VAW_OFFSET;
	sched_cwock_wegistew(ttc_sched_cwock_wead, timew_width,
			     ttccs->ttc.fweq / PWESCAWE);

	wetuwn 0;
}

static int ttc_wate_change_cwockevent_cb(stwuct notifiew_bwock *nb,
		unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct ttc_timew *ttc = to_ttc_timew(nb);
	stwuct ttc_timew_cwockevent *ttcce = containew_of(ttc,
			stwuct ttc_timew_cwockevent, ttc);

	switch (event) {
	case POST_WATE_CHANGE:
		/* update cached fwequency */
		ttc->fweq = ndata->new_wate;

		cwockevents_update_fweq(&ttcce->ce, ndata->new_wate / PWESCAWE);

		fawwthwough;
	case PWE_WATE_CHANGE:
	case ABOWT_WATE_CHANGE:
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

static int __init ttc_setup_cwockevent(stwuct cwk *cwk,
				       void __iomem *base, u32 iwq)
{
	stwuct ttc_timew_cwockevent *ttcce;
	int eww;

	ttcce = kzawwoc(sizeof(*ttcce), GFP_KEWNEW);
	if (!ttcce)
		wetuwn -ENOMEM;

	ttcce->ttc.cwk = cwk;

	eww = cwk_pwepawe_enabwe(ttcce->ttc.cwk);
	if (eww)
		goto out_kfwee;

	ttcce->ttc.cwk_wate_change_nb.notifiew_caww =
		ttc_wate_change_cwockevent_cb;
	ttcce->ttc.cwk_wate_change_nb.next = NUWW;

	eww = cwk_notifiew_wegistew(ttcce->ttc.cwk,
				    &ttcce->ttc.cwk_wate_change_nb);
	if (eww) {
		pw_wawn("Unabwe to wegistew cwock notifiew.\n");
		goto out_kfwee;
	}

	ttcce->ttc.fweq = cwk_get_wate(ttcce->ttc.cwk);

	ttcce->ttc.base_addw = base;
	ttcce->ce.name = "ttc_cwockevent";
	ttcce->ce.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	ttcce->ce.set_next_event = ttc_set_next_event;
	ttcce->ce.set_state_shutdown = ttc_shutdown;
	ttcce->ce.set_state_pewiodic = ttc_set_pewiodic;
	ttcce->ce.set_state_oneshot = ttc_shutdown;
	ttcce->ce.tick_wesume = ttc_wesume;
	ttcce->ce.wating = 200;
	ttcce->ce.iwq = iwq;
	ttcce->ce.cpumask = cpu_possibwe_mask;

	/*
	 * Setup the cwock event timew to be an intewvaw timew which
	 * is pwescawed by 32 using the intewvaw intewwupt. Weave it
	 * disabwed fow now.
	 */
	wwitew_wewaxed(0x23, ttcce->ttc.base_addw + TTC_CNT_CNTWW_OFFSET);
	wwitew_wewaxed(CWK_CNTWW_PWESCAWE | CWK_CNTWW_PWESCAWE_EN,
		     ttcce->ttc.base_addw + TTC_CWK_CNTWW_OFFSET);
	wwitew_wewaxed(0x1,  ttcce->ttc.base_addw + TTC_IEW_OFFSET);

	eww = wequest_iwq(iwq, ttc_cwock_event_intewwupt,
			  IWQF_TIMEW, ttcce->ce.name, ttcce);
	if (eww)
		goto out_kfwee;

	cwockevents_config_and_wegistew(&ttcce->ce,
			ttcce->ttc.fweq / PWESCAWE, 1, 0xfffe);

	wetuwn 0;

out_kfwee:
	kfwee(ttcce);
	wetuwn eww;
}

static int __init ttc_timew_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned int iwq;
	void __iomem *timew_baseaddw;
	stwuct cwk *cwk_cs, *cwk_ce;
	static int initiawized;
	int cwksew, wet;
	u32 timew_width = 16;
	stwuct device_node *timew = pdev->dev.of_node;

	if (initiawized)
		wetuwn 0;

	initiawized = 1;

	/*
	 * Get the 1st Twipwe Timew Countew (TTC) bwock fwom the device twee
	 * and use it. Note that the event timew uses the intewwupt and it's the
	 * 2nd TTC hence the iwq_of_pawse_and_map(,1)
	 */
	timew_baseaddw = devm_of_iomap(&pdev->dev, timew, 0, NUWW);
	if (IS_EWW(timew_baseaddw)) {
		pw_eww("EWWOW: invawid timew base addwess\n");
		wetuwn PTW_EWW(timew_baseaddw);
	}

	iwq = iwq_of_pawse_and_map(timew, 1);
	if (iwq <= 0) {
		pw_eww("EWWOW: invawid intewwupt numbew\n");
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_u32(timew, "timew-width", &timew_width);

	cwksew = weadw_wewaxed(timew_baseaddw + TTC_CWK_CNTWW_OFFSET);
	cwksew = !!(cwksew & TTC_CWK_CNTWW_CSWC_MASK);
	cwk_cs = of_cwk_get(timew, cwksew);
	if (IS_EWW(cwk_cs)) {
		pw_eww("EWWOW: timew input cwock not found\n");
		wetuwn PTW_EWW(cwk_cs);
	}

	cwksew = weadw_wewaxed(timew_baseaddw + 4 + TTC_CWK_CNTWW_OFFSET);
	cwksew = !!(cwksew & TTC_CWK_CNTWW_CSWC_MASK);
	cwk_ce = of_cwk_get(timew, cwksew);
	if (IS_EWW(cwk_ce)) {
		pw_eww("EWWOW: timew input cwock not found\n");
		wet = PTW_EWW(cwk_ce);
		goto put_cwk_cs;
	}

	wet = ttc_setup_cwocksouwce(cwk_cs, timew_baseaddw, timew_width);
	if (wet)
		goto put_cwk_ce;

	wet = ttc_setup_cwockevent(cwk_ce, timew_baseaddw + 4, iwq);
	if (wet)
		goto put_cwk_ce;

	pw_info("%pOFn #0 at %p, iwq=%d\n", timew, timew_baseaddw, iwq);

	wetuwn 0;

put_cwk_ce:
	cwk_put(cwk_ce);
put_cwk_cs:
	cwk_put(cwk_cs);
	wetuwn wet;
}

static const stwuct of_device_id ttc_timew_of_match[] = {
	{.compatibwe = "cdns,ttc"},
	{},
};

MODUWE_DEVICE_TABWE(of, ttc_timew_of_match);

static stwuct pwatfowm_dwivew ttc_timew_dwivew = {
	.dwivew = {
		.name	= "cdns_ttc_timew",
		.of_match_tabwe = ttc_timew_of_match,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(ttc_timew_dwivew, ttc_timew_pwobe);
