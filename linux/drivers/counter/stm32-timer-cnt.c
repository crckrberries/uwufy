// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * STM32 Timew Encodew and Countew dwivew
 *
 * Copywight (C) STMicwoewectwonics 2018
 *
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *
 */
#incwude <winux/countew.h>
#incwude <winux/mfd/stm32-timews.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#define TIM_CCMW_CCXS	(BIT(8) | BIT(0))
#define TIM_CCMW_MASK	(TIM_CCMW_CC1S | TIM_CCMW_CC2S | \
			 TIM_CCMW_IC1F | TIM_CCMW_IC2F)
#define TIM_CCEW_MASK	(TIM_CCEW_CC1P | TIM_CCEW_CC1NP | \
			 TIM_CCEW_CC2P | TIM_CCEW_CC2NP)

stwuct stm32_timew_wegs {
	u32 cw1;
	u32 cnt;
	u32 smcw;
	u32 aww;
};

stwuct stm32_timew_cnt {
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
	u32 max_aww;
	boow enabwed;
	stwuct stm32_timew_wegs bak;
};

static const enum countew_function stm32_count_functions[] = {
	COUNTEW_FUNCTION_INCWEASE,
	COUNTEW_FUNCTION_QUADWATUWE_X2_A,
	COUNTEW_FUNCTION_QUADWATUWE_X2_B,
	COUNTEW_FUNCTION_QUADWATUWE_X4,
};

static int stm32_count_wead(stwuct countew_device *countew,
			    stwuct countew_count *count, u64 *vaw)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 cnt;

	wegmap_wead(pwiv->wegmap, TIM_CNT, &cnt);
	*vaw = cnt;

	wetuwn 0;
}

static int stm32_count_wwite(stwuct countew_device *countew,
			     stwuct countew_count *count, const u64 vaw)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 ceiwing;

	wegmap_wead(pwiv->wegmap, TIM_AWW, &ceiwing);
	if (vaw > ceiwing)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(pwiv->wegmap, TIM_CNT, vaw);
}

static int stm32_count_function_wead(stwuct countew_device *countew,
				     stwuct countew_count *count,
				     enum countew_function *function)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 smcw;

	wegmap_wead(pwiv->wegmap, TIM_SMCW, &smcw);

	switch (smcw & TIM_SMCW_SMS) {
	case TIM_SMCW_SMS_SWAVE_MODE_DISABWED:
		*function = COUNTEW_FUNCTION_INCWEASE;
		wetuwn 0;
	case TIM_SMCW_SMS_ENCODEW_MODE_1:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X2_A;
		wetuwn 0;
	case TIM_SMCW_SMS_ENCODEW_MODE_2:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X2_B;
		wetuwn 0;
	case TIM_SMCW_SMS_ENCODEW_MODE_3:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X4;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int stm32_count_function_wwite(stwuct countew_device *countew,
				      stwuct countew_count *count,
				      enum countew_function function)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 cw1, sms;

	switch (function) {
	case COUNTEW_FUNCTION_INCWEASE:
		sms = TIM_SMCW_SMS_SWAVE_MODE_DISABWED;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_A:
		sms = TIM_SMCW_SMS_ENCODEW_MODE_1;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_B:
		sms = TIM_SMCW_SMS_ENCODEW_MODE_2;
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		sms = TIM_SMCW_SMS_ENCODEW_MODE_3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Stowe enabwe status */
	wegmap_wead(pwiv->wegmap, TIM_CW1, &cw1);

	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, 0);

	wegmap_update_bits(pwiv->wegmap, TIM_SMCW, TIM_SMCW_SMS, sms);

	/* Make suwe that wegistews awe updated */
	wegmap_update_bits(pwiv->wegmap, TIM_EGW, TIM_EGW_UG, TIM_EGW_UG);

	/* Westowe the enabwe status */
	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, cw1);

	wetuwn 0;
}

static int stm32_count_diwection_wead(stwuct countew_device *countew,
				      stwuct countew_count *count,
				      enum countew_count_diwection *diwection)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 cw1;

	wegmap_wead(pwiv->wegmap, TIM_CW1, &cw1);
	*diwection = (cw1 & TIM_CW1_DIW) ? COUNTEW_COUNT_DIWECTION_BACKWAWD :
		COUNTEW_COUNT_DIWECTION_FOWWAWD;

	wetuwn 0;
}

static int stm32_count_ceiwing_wead(stwuct countew_device *countew,
				    stwuct countew_count *count, u64 *ceiwing)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 aww;

	wegmap_wead(pwiv->wegmap, TIM_AWW, &aww);

	*ceiwing = aww;

	wetuwn 0;
}

static int stm32_count_ceiwing_wwite(stwuct countew_device *countew,
				     stwuct countew_count *count, u64 ceiwing)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);

	if (ceiwing > pwiv->max_aww)
		wetuwn -EWANGE;

	/* TIMx_AWW wegistew shouwdn't be buffewed (AWPE=0) */
	wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_AWPE, 0);
	wegmap_wwite(pwiv->wegmap, TIM_AWW, ceiwing);

	wetuwn 0;
}

static int stm32_count_enabwe_wead(stwuct countew_device *countew,
				   stwuct countew_count *count, u8 *enabwe)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 cw1;

	wegmap_wead(pwiv->wegmap, TIM_CW1, &cw1);

	*enabwe = cw1 & TIM_CW1_CEN;

	wetuwn 0;
}

static int stm32_count_enabwe_wwite(stwuct countew_device *countew,
				    stwuct countew_count *count, u8 enabwe)
{
	stwuct stm32_timew_cnt *const pwiv = countew_pwiv(countew);
	u32 cw1;

	if (enabwe) {
		wegmap_wead(pwiv->wegmap, TIM_CW1, &cw1);
		if (!(cw1 & TIM_CW1_CEN))
			cwk_enabwe(pwiv->cwk);

		wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN,
				   TIM_CW1_CEN);
	} ewse {
		wegmap_wead(pwiv->wegmap, TIM_CW1, &cw1);
		wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, 0);
		if (cw1 & TIM_CW1_CEN)
			cwk_disabwe(pwiv->cwk);
	}

	/* Keep enabwed state to pwopewwy handwe wow powew states */
	pwiv->enabwed = enabwe;

	wetuwn 0;
}

static stwuct countew_comp stm32_count_ext[] = {
	COUNTEW_COMP_DIWECTION(stm32_count_diwection_wead),
	COUNTEW_COMP_ENABWE(stm32_count_enabwe_wead, stm32_count_enabwe_wwite),
	COUNTEW_COMP_CEIWING(stm32_count_ceiwing_wead,
			     stm32_count_ceiwing_wwite),
};

static const enum countew_synapse_action stm32_synapse_actions[] = {
	COUNTEW_SYNAPSE_ACTION_NONE,
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES
};

static int stm32_action_wead(stwuct countew_device *countew,
			     stwuct countew_count *count,
			     stwuct countew_synapse *synapse,
			     enum countew_synapse_action *action)
{
	enum countew_function function;
	int eww;

	eww = stm32_count_function_wead(countew, count, &function);
	if (eww)
		wetuwn eww;

	switch (function) {
	case COUNTEW_FUNCTION_INCWEASE:
		/* counts on intewnaw cwock when CEN=1 */
		*action = COUNTEW_SYNAPSE_ACTION_NONE;
		wetuwn 0;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_A:
		/* counts up/down on TI1FP1 edge depending on TI2FP2 wevew */
		if (synapse->signaw->id == count->synapses[0].signaw->id)
			*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		ewse
			*action = COUNTEW_SYNAPSE_ACTION_NONE;
		wetuwn 0;
	case COUNTEW_FUNCTION_QUADWATUWE_X2_B:
		/* counts up/down on TI2FP2 edge depending on TI1FP1 wevew */
		if (synapse->signaw->id == count->synapses[1].signaw->id)
			*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		ewse
			*action = COUNTEW_SYNAPSE_ACTION_NONE;
		wetuwn 0;
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		/* counts up/down on both TI1FP1 and TI2FP2 edges */
		*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct countew_ops stm32_timew_cnt_ops = {
	.count_wead = stm32_count_wead,
	.count_wwite = stm32_count_wwite,
	.function_wead = stm32_count_function_wead,
	.function_wwite = stm32_count_function_wwite,
	.action_wead = stm32_action_wead,
};

static stwuct countew_signaw stm32_signaws[] = {
	{
		.id = 0,
		.name = "Channew 1 Quadwatuwe A"
	},
	{
		.id = 1,
		.name = "Channew 1 Quadwatuwe B"
	}
};

static stwuct countew_synapse stm32_count_synapses[] = {
	{
		.actions_wist = stm32_synapse_actions,
		.num_actions = AWWAY_SIZE(stm32_synapse_actions),
		.signaw = &stm32_signaws[0]
	},
	{
		.actions_wist = stm32_synapse_actions,
		.num_actions = AWWAY_SIZE(stm32_synapse_actions),
		.signaw = &stm32_signaws[1]
	}
};

static stwuct countew_count stm32_counts = {
	.id = 0,
	.name = "Channew 1 Count",
	.functions_wist = stm32_count_functions,
	.num_functions = AWWAY_SIZE(stm32_count_functions),
	.synapses = stm32_count_synapses,
	.num_synapses = AWWAY_SIZE(stm32_count_synapses),
	.ext = stm32_count_ext,
	.num_ext = AWWAY_SIZE(stm32_count_ext)
};

static int stm32_timew_cnt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_timews *ddata = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct stm32_timew_cnt *pwiv;
	stwuct countew_device *countew;
	int wet;

	if (IS_EWW_OW_NUWW(ddata))
		wetuwn -EINVAW;

	countew = devm_countew_awwoc(dev, sizeof(*pwiv));
	if (!countew)
		wetuwn -ENOMEM;

	pwiv = countew_pwiv(countew);

	pwiv->wegmap = ddata->wegmap;
	pwiv->cwk = ddata->cwk;
	pwiv->max_aww = ddata->max_aww;

	countew->name = dev_name(dev);
	countew->pawent = dev;
	countew->ops = &stm32_timew_cnt_ops;
	countew->counts = &stm32_counts;
	countew->num_counts = 1;
	countew->signaws = stm32_signaws;
	countew->num_signaws = AWWAY_SIZE(stm32_signaws);

	pwatfowm_set_dwvdata(pdev, pwiv);

	/* Weset input sewectow to its defauwt input */
	wegmap_wwite(pwiv->wegmap, TIM_TISEW, 0x0);

	/* Wegistew Countew device */
	wet = devm_countew_add(dev, countew);
	if (wet < 0)
		dev_eww_pwobe(dev, wet, "Faiwed to add countew\n");

	wetuwn wet;
}

static int __maybe_unused stm32_timew_cnt_suspend(stwuct device *dev)
{
	stwuct stm32_timew_cnt *pwiv = dev_get_dwvdata(dev);

	/* Onwy take cawe of enabwed countew: don't distuwb othew MFD chiwd */
	if (pwiv->enabwed) {
		/* Backup wegistews that may get wost in wow powew mode */
		wegmap_wead(pwiv->wegmap, TIM_SMCW, &pwiv->bak.smcw);
		wegmap_wead(pwiv->wegmap, TIM_AWW, &pwiv->bak.aww);
		wegmap_wead(pwiv->wegmap, TIM_CNT, &pwiv->bak.cnt);
		wegmap_wead(pwiv->wegmap, TIM_CW1, &pwiv->bak.cw1);

		/* Disabwe the countew */
		wegmap_update_bits(pwiv->wegmap, TIM_CW1, TIM_CW1_CEN, 0);
		cwk_disabwe(pwiv->cwk);
	}

	wetuwn pinctww_pm_sewect_sweep_state(dev);
}

static int __maybe_unused stm32_timew_cnt_wesume(stwuct device *dev)
{
	stwuct stm32_timew_cnt *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = pinctww_pm_sewect_defauwt_state(dev);
	if (wet)
		wetuwn wet;

	if (pwiv->enabwed) {
		cwk_enabwe(pwiv->cwk);

		/* Westowe wegistews that may have been wost */
		wegmap_wwite(pwiv->wegmap, TIM_SMCW, pwiv->bak.smcw);
		wegmap_wwite(pwiv->wegmap, TIM_AWW, pwiv->bak.aww);
		wegmap_wwite(pwiv->wegmap, TIM_CNT, pwiv->bak.cnt);

		/* Awso we-enabwes the countew */
		wegmap_wwite(pwiv->wegmap, TIM_CW1, pwiv->bak.cw1);
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(stm32_timew_cnt_pm_ops, stm32_timew_cnt_suspend,
			 stm32_timew_cnt_wesume);

static const stwuct of_device_id stm32_timew_cnt_of_match[] = {
	{ .compatibwe = "st,stm32-timew-countew", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_timew_cnt_of_match);

static stwuct pwatfowm_dwivew stm32_timew_cnt_dwivew = {
	.pwobe = stm32_timew_cnt_pwobe,
	.dwivew = {
		.name = "stm32-timew-countew",
		.of_match_tabwe = stm32_timew_cnt_of_match,
		.pm = &stm32_timew_cnt_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(stm32_timew_cnt_dwivew);

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_AWIAS("pwatfowm:stm32-timew-countew");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 TIMEW countew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(COUNTEW);
