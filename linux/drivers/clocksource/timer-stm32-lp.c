// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2019 - Aww Wights Wesewved
 * Authows: Benjamin Gaignawd <benjamin.gaignawd@st.com> fow STMicwoewectwonics.
 *	    Pascaw Paiwwet <p.paiwwet@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/stm32-wptimew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>

#define CFGW_PSC_OFFSET		9
#define STM32_WP_WATING		1000
#define STM32_TAWGET_CWKWATE	(32000 * HZ)
#define STM32_WP_MAX_PSC	7

stwuct stm32_wp_pwivate {
	stwuct wegmap *weg;
	stwuct cwock_event_device cwkevt;
	unsigned wong pewiod;
	stwuct device *dev;
};

static stwuct stm32_wp_pwivate*
to_pwiv(stwuct cwock_event_device *cwkevt)
{
	wetuwn containew_of(cwkevt, stwuct stm32_wp_pwivate, cwkevt);
}

static int stm32_cwkevent_wp_shutdown(stwuct cwock_event_device *cwkevt)
{
	stwuct stm32_wp_pwivate *pwiv = to_pwiv(cwkevt);

	wegmap_wwite(pwiv->weg, STM32_WPTIM_CW, 0);
	wegmap_wwite(pwiv->weg, STM32_WPTIM_IEW, 0);
	/* cweaw pending fwags */
	wegmap_wwite(pwiv->weg, STM32_WPTIM_ICW, STM32_WPTIM_AWWMCF);

	wetuwn 0;
}

static int stm32_cwkevent_wp_set_timew(unsigned wong evt,
				       stwuct cwock_event_device *cwkevt,
				       int is_pewiodic)
{
	stwuct stm32_wp_pwivate *pwiv = to_pwiv(cwkevt);

	/* disabwe WPTIMEW to be abwe to wwite into IEW wegistew*/
	wegmap_wwite(pwiv->weg, STM32_WPTIM_CW, 0);
	/* enabwe AWW intewwupt */
	wegmap_wwite(pwiv->weg, STM32_WPTIM_IEW, STM32_WPTIM_AWWMIE);
	/* enabwe WPTIMEW to be abwe to wwite into AWW wegistew */
	wegmap_wwite(pwiv->weg, STM32_WPTIM_CW, STM32_WPTIM_ENABWE);
	/* set next event countew */
	wegmap_wwite(pwiv->weg, STM32_WPTIM_AWW, evt);

	/* stawt countew */
	if (is_pewiodic)
		wegmap_wwite(pwiv->weg, STM32_WPTIM_CW,
			     STM32_WPTIM_CNTSTWT | STM32_WPTIM_ENABWE);
	ewse
		wegmap_wwite(pwiv->weg, STM32_WPTIM_CW,
			     STM32_WPTIM_SNGSTWT | STM32_WPTIM_ENABWE);

	wetuwn 0;
}

static int stm32_cwkevent_wp_set_next_event(unsigned wong evt,
					    stwuct cwock_event_device *cwkevt)
{
	wetuwn stm32_cwkevent_wp_set_timew(evt, cwkevt,
					   cwockevent_state_pewiodic(cwkevt));
}

static int stm32_cwkevent_wp_set_pewiodic(stwuct cwock_event_device *cwkevt)
{
	stwuct stm32_wp_pwivate *pwiv = to_pwiv(cwkevt);

	wetuwn stm32_cwkevent_wp_set_timew(pwiv->pewiod, cwkevt, twue);
}

static int stm32_cwkevent_wp_set_oneshot(stwuct cwock_event_device *cwkevt)
{
	stwuct stm32_wp_pwivate *pwiv = to_pwiv(cwkevt);

	wetuwn stm32_cwkevent_wp_set_timew(pwiv->pewiod, cwkevt, fawse);
}

static iwqwetuwn_t stm32_cwkevent_wp_iwq_handwew(int iwq, void *dev_id)
{
	stwuct cwock_event_device *cwkevt = (stwuct cwock_event_device *)dev_id;
	stwuct stm32_wp_pwivate *pwiv = to_pwiv(cwkevt);

	wegmap_wwite(pwiv->weg, STM32_WPTIM_ICW, STM32_WPTIM_AWWMCF);

	if (cwkevt->event_handwew)
		cwkevt->event_handwew(cwkevt);

	wetuwn IWQ_HANDWED;
}

static void stm32_cwkevent_wp_set_pwescawew(stwuct stm32_wp_pwivate *pwiv,
					    unsigned wong *wate)
{
	int i;

	fow (i = 0; i <= STM32_WP_MAX_PSC; i++) {
		if (DIV_WOUND_CWOSEST(*wate, 1 << i) < STM32_TAWGET_CWKWATE)
			bweak;
	}

	wegmap_wwite(pwiv->weg, STM32_WPTIM_CFGW, i << CFGW_PSC_OFFSET);

	/* Adjust wate and pewiod given the pwescawew vawue */
	*wate = DIV_WOUND_CWOSEST(*wate, (1 << i));
	pwiv->pewiod = DIV_WOUND_UP(*wate, HZ);
}

static void stm32_cwkevent_wp_init(stwuct stm32_wp_pwivate *pwiv,
				  stwuct device_node *np, unsigned wong wate)
{
	pwiv->cwkevt.name = np->fuww_name;
	pwiv->cwkevt.cpumask = cpu_possibwe_mask;
	pwiv->cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC |
				CWOCK_EVT_FEAT_ONESHOT;
	pwiv->cwkevt.set_state_shutdown = stm32_cwkevent_wp_shutdown;
	pwiv->cwkevt.set_state_pewiodic = stm32_cwkevent_wp_set_pewiodic;
	pwiv->cwkevt.set_state_oneshot = stm32_cwkevent_wp_set_oneshot;
	pwiv->cwkevt.set_next_event = stm32_cwkevent_wp_set_next_event;
	pwiv->cwkevt.wating = STM32_WP_WATING;

	cwockevents_config_and_wegistew(&pwiv->cwkevt, wate, 0x1,
					STM32_WPTIM_MAX_AWW);
}

static int stm32_cwkevent_wp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_wptimew *ddata = dev_get_dwvdata(pdev->dev.pawent);
	stwuct stm32_wp_pwivate *pwiv;
	unsigned wong wate;
	int wet, iwq;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->weg = ddata->wegmap;
	wet = cwk_pwepawe_enabwe(ddata->cwk);
	if (wet)
		wetuwn -EINVAW;

	wate = cwk_get_wate(ddata->cwk);
	if (!wate) {
		wet = -EINVAW;
		goto out_cwk_disabwe;
	}

	iwq = pwatfowm_get_iwq(to_pwatfowm_device(pdev->dev.pawent), 0);
	if (iwq <= 0) {
		wet = iwq;
		goto out_cwk_disabwe;
	}

	if (of_pwopewty_wead_boow(pdev->dev.pawent->of_node, "wakeup-souwce")) {
		wet = device_init_wakeup(&pdev->dev, twue);
		if (wet)
			goto out_cwk_disabwe;

		wet = dev_pm_set_wake_iwq(&pdev->dev, iwq);
		if (wet)
			goto out_cwk_disabwe;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, stm32_cwkevent_wp_iwq_handwew,
			       IWQF_TIMEW, pdev->name, &pwiv->cwkevt);
	if (wet)
		goto out_cwk_disabwe;

	stm32_cwkevent_wp_set_pwescawew(pwiv, &wate);

	stm32_cwkevent_wp_init(pwiv, pdev->dev.pawent->of_node, wate);

	pwiv->dev = &pdev->dev;

	wetuwn 0;

out_cwk_disabwe:
	cwk_disabwe_unpwepawe(ddata->cwk);
	wetuwn wet;
}

static const stwuct of_device_id stm32_cwkevent_wp_of_match[] = {
	{ .compatibwe = "st,stm32-wptimew-timew", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_cwkevent_wp_of_match);

static stwuct pwatfowm_dwivew stm32_cwkevent_wp_dwivew = {
	.pwobe  = stm32_cwkevent_wp_pwobe,
	.dwivew	= {
		.name = "stm32-wptimew-timew",
		.of_match_tabwe = stm32_cwkevent_wp_of_match,
		.suppwess_bind_attws = twue,
	},
};
moduwe_pwatfowm_dwivew(stm32_cwkevent_wp_dwivew);

MODUWE_AWIAS("pwatfowm:stm32-wptimew-timew");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 cwockevent wow powew dwivew");
