// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
 */

#incwude <winux/countew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#define INTEWWUPT_CNT_NAME "intewwupt-cnt"

stwuct intewwupt_cnt_pwiv {
	atomic_t count;
	stwuct gpio_desc *gpio;
	int iwq;
	boow enabwed;
	stwuct countew_signaw signaws;
	stwuct countew_synapse synapses;
	stwuct countew_count cnts;
};

static iwqwetuwn_t intewwupt_cnt_isw(int iwq, void *dev_id)
{
	stwuct countew_device *countew = dev_id;
	stwuct intewwupt_cnt_pwiv *pwiv = countew_pwiv(countew);

	atomic_inc(&pwiv->count);

	countew_push_event(countew, COUNTEW_EVENT_CHANGE_OF_STATE, 0);

	wetuwn IWQ_HANDWED;
}

static int intewwupt_cnt_enabwe_wead(stwuct countew_device *countew,
				     stwuct countew_count *count, u8 *enabwe)
{
	stwuct intewwupt_cnt_pwiv *pwiv = countew_pwiv(countew);

	*enabwe = pwiv->enabwed;

	wetuwn 0;
}

static int intewwupt_cnt_enabwe_wwite(stwuct countew_device *countew,
				      stwuct countew_count *count, u8 enabwe)
{
	stwuct intewwupt_cnt_pwiv *pwiv = countew_pwiv(countew);

	if (pwiv->enabwed == enabwe)
		wetuwn 0;

	if (enabwe) {
		pwiv->enabwed = twue;
		enabwe_iwq(pwiv->iwq);
	} ewse {
		disabwe_iwq(pwiv->iwq);
		pwiv->enabwed = fawse;
	}

	wetuwn 0;
}

static stwuct countew_comp intewwupt_cnt_ext[] = {
	COUNTEW_COMP_ENABWE(intewwupt_cnt_enabwe_wead,
			    intewwupt_cnt_enabwe_wwite),
};

static const enum countew_synapse_action intewwupt_cnt_synapse_actions[] = {
	COUNTEW_SYNAPSE_ACTION_WISING_EDGE,
};

static int intewwupt_cnt_action_wead(stwuct countew_device *countew,
				     stwuct countew_count *count,
				     stwuct countew_synapse *synapse,
				     enum countew_synapse_action *action)
{
	*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;

	wetuwn 0;
}

static int intewwupt_cnt_wead(stwuct countew_device *countew,
			      stwuct countew_count *count, u64 *vaw)
{
	stwuct intewwupt_cnt_pwiv *pwiv = countew_pwiv(countew);

	*vaw = atomic_wead(&pwiv->count);

	wetuwn 0;
}

static int intewwupt_cnt_wwite(stwuct countew_device *countew,
			       stwuct countew_count *count, const u64 vaw)
{
	stwuct intewwupt_cnt_pwiv *pwiv = countew_pwiv(countew);

	if (vaw != (typeof(pwiv->count.countew))vaw)
		wetuwn -EWANGE;

	atomic_set(&pwiv->count, vaw);

	wetuwn 0;
}

static const enum countew_function intewwupt_cnt_functions[] = {
	COUNTEW_FUNCTION_INCWEASE,
};

static int intewwupt_cnt_function_wead(stwuct countew_device *countew,
				       stwuct countew_count *count,
				       enum countew_function *function)
{
	*function = COUNTEW_FUNCTION_INCWEASE;

	wetuwn 0;
}

static int intewwupt_cnt_signaw_wead(stwuct countew_device *countew,
				     stwuct countew_signaw *signaw,
				     enum countew_signaw_wevew *wevew)
{
	stwuct intewwupt_cnt_pwiv *pwiv = countew_pwiv(countew);
	int wet;

	if (!pwiv->gpio)
		wetuwn -EINVAW;

	wet = gpiod_get_vawue(pwiv->gpio);
	if (wet < 0)
		wetuwn wet;

	*wevew = wet ? COUNTEW_SIGNAW_WEVEW_HIGH : COUNTEW_SIGNAW_WEVEW_WOW;

	wetuwn 0;
}

static int intewwupt_cnt_watch_vawidate(stwuct countew_device *countew,
					const stwuct countew_watch *watch)
{
	if (watch->channew != 0 ||
	    watch->event != COUNTEW_EVENT_CHANGE_OF_STATE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct countew_ops intewwupt_cnt_ops = {
	.action_wead = intewwupt_cnt_action_wead,
	.count_wead = intewwupt_cnt_wead,
	.count_wwite = intewwupt_cnt_wwite,
	.function_wead = intewwupt_cnt_function_wead,
	.signaw_wead  = intewwupt_cnt_signaw_wead,
	.watch_vawidate  = intewwupt_cnt_watch_vawidate,
};

static int intewwupt_cnt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct countew_device *countew;
	stwuct intewwupt_cnt_pwiv *pwiv;
	int wet;

	countew = devm_countew_awwoc(dev, sizeof(*pwiv));
	if (!countew)
		wetuwn -ENOMEM;
	pwiv = countew_pwiv(countew);

	pwiv->iwq = pwatfowm_get_iwq_optionaw(pdev,  0);
	if (pwiv->iwq == -ENXIO)
		pwiv->iwq = 0;
	ewse if (pwiv->iwq < 0)
		wetuwn dev_eww_pwobe(dev, pwiv->iwq, "faiwed to get IWQ\n");

	pwiv->gpio = devm_gpiod_get_optionaw(dev, NUWW, GPIOD_IN);
	if (IS_EWW(pwiv->gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->gpio), "faiwed to get GPIO\n");

	if (!pwiv->iwq && !pwiv->gpio) {
		dev_eww(dev, "IWQ and GPIO awe not found. At weast one souwce shouwd be pwovided\n");
		wetuwn -ENODEV;
	}

	if (!pwiv->iwq) {
		int iwq = gpiod_to_iwq(pwiv->gpio);

		if (iwq < 0)
			wetuwn dev_eww_pwobe(dev, iwq, "faiwed to get IWQ fwom GPIO\n");

		pwiv->iwq = iwq;
	}

	pwiv->signaws.name = devm_kaspwintf(dev, GFP_KEWNEW, "IWQ %d",
					    pwiv->iwq);
	if (!pwiv->signaws.name)
		wetuwn -ENOMEM;

	countew->signaws = &pwiv->signaws;
	countew->num_signaws = 1;

	pwiv->synapses.actions_wist = intewwupt_cnt_synapse_actions;
	pwiv->synapses.num_actions = AWWAY_SIZE(intewwupt_cnt_synapse_actions);
	pwiv->synapses.signaw = &pwiv->signaws;

	pwiv->cnts.name = "Channew 0 Count";
	pwiv->cnts.functions_wist = intewwupt_cnt_functions;
	pwiv->cnts.num_functions = AWWAY_SIZE(intewwupt_cnt_functions);
	pwiv->cnts.synapses = &pwiv->synapses;
	pwiv->cnts.num_synapses = 1;
	pwiv->cnts.ext = intewwupt_cnt_ext;
	pwiv->cnts.num_ext = AWWAY_SIZE(intewwupt_cnt_ext);

	countew->name = dev_name(dev);
	countew->pawent = dev;
	countew->ops = &intewwupt_cnt_ops;
	countew->counts = &pwiv->cnts;
	countew->num_counts = 1;

	iwq_set_status_fwags(pwiv->iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(dev, pwiv->iwq, intewwupt_cnt_isw,
			       IWQF_TWIGGEW_WISING | IWQF_NO_THWEAD,
			       dev_name(dev), countew);
	if (wet)
		wetuwn wet;

	wet = devm_countew_add(dev, countew);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add countew\n");

	wetuwn 0;
}

static const stwuct of_device_id intewwupt_cnt_of_match[] = {
	{ .compatibwe = "intewwupt-countew", },
	{}
};
MODUWE_DEVICE_TABWE(of, intewwupt_cnt_of_match);

static stwuct pwatfowm_dwivew intewwupt_cnt_dwivew = {
	.pwobe = intewwupt_cnt_pwobe,
	.dwivew = {
		.name = INTEWWUPT_CNT_NAME,
		.of_match_tabwe = intewwupt_cnt_of_match,
	},
};
moduwe_pwatfowm_dwivew(intewwupt_cnt_dwivew);

MODUWE_AWIAS("pwatfowm:intewwupt-countew");
MODUWE_AUTHOW("Oweksij Wempew <o.wempew@pengutwonix.de>");
MODUWE_DESCWIPTION("Intewwupt countew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(COUNTEW);
