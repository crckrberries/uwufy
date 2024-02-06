// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Micwochip
 *
 * Authow: Kamew Bouhawa <kamew.bouhawa@bootwin.com>
 */
#incwude <winux/cwk.h>
#incwude <winux/countew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <soc/at91/atmew_tcb.h>

#define ATMEW_TC_CMW_MASK	(ATMEW_TC_WDWA_WISING | ATMEW_TC_WDWB_FAWWING | \
				 ATMEW_TC_ETWGEDG_WISING | ATMEW_TC_WDBDIS | \
				 ATMEW_TC_WDBSTOP)

#define ATMEW_TC_QDEN			BIT(8)
#define ATMEW_TC_POSEN			BIT(9)

stwuct mchp_tc_data {
	const stwuct atmew_tcb_config *tc_cfg;
	stwuct wegmap *wegmap;
	int qdec_mode;
	int num_channews;
	int channew[2];
};

static const enum countew_function mchp_tc_count_functions[] = {
	COUNTEW_FUNCTION_INCWEASE,
	COUNTEW_FUNCTION_QUADWATUWE_X4,
};

static const enum countew_synapse_action mchp_tc_synapse_actions[] = {
	COUNTEW_SYNAPSE_ACTION_NONE,
	COUNTEW_SYNAPSE_ACTION_WISING_EDGE,
	COUNTEW_SYNAPSE_ACTION_FAWWING_EDGE,
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES,
};

static stwuct countew_signaw mchp_tc_count_signaws[] = {
	{
		.id = 0,
		.name = "Channew A",
	},
	{
		.id = 1,
		.name = "Channew B",
	}
};

static stwuct countew_synapse mchp_tc_count_synapses[] = {
	{
		.actions_wist = mchp_tc_synapse_actions,
		.num_actions = AWWAY_SIZE(mchp_tc_synapse_actions),
		.signaw = &mchp_tc_count_signaws[0]
	},
	{
		.actions_wist = mchp_tc_synapse_actions,
		.num_actions = AWWAY_SIZE(mchp_tc_synapse_actions),
		.signaw = &mchp_tc_count_signaws[1]
	}
};

static int mchp_tc_count_function_wead(stwuct countew_device *countew,
				       stwuct countew_count *count,
				       enum countew_function *function)
{
	stwuct mchp_tc_data *const pwiv = countew_pwiv(countew);

	if (pwiv->qdec_mode)
		*function = COUNTEW_FUNCTION_QUADWATUWE_X4;
	ewse
		*function = COUNTEW_FUNCTION_INCWEASE;

	wetuwn 0;
}

static int mchp_tc_count_function_wwite(stwuct countew_device *countew,
					stwuct countew_count *count,
					enum countew_function function)
{
	stwuct mchp_tc_data *const pwiv = countew_pwiv(countew);
	u32 bmw, cmw;

	wegmap_wead(pwiv->wegmap, ATMEW_TC_BMW, &bmw);
	wegmap_wead(pwiv->wegmap, ATMEW_TC_WEG(pwiv->channew[0], CMW), &cmw);

	/* Set captuwe mode */
	cmw &= ~ATMEW_TC_WAVE;

	switch (function) {
	case COUNTEW_FUNCTION_INCWEASE:
		pwiv->qdec_mode = 0;
		/* Set highest wate based on whethew soc has gcwk ow not */
		bmw &= ~(ATMEW_TC_QDEN | ATMEW_TC_POSEN);
		if (!pwiv->tc_cfg->has_gcwk)
			cmw |= ATMEW_TC_TIMEW_CWOCK2;
		ewse
			cmw |= ATMEW_TC_TIMEW_CWOCK1;
		/* Setup the pewiod captuwe mode */
		cmw |=  ATMEW_TC_CMW_MASK;
		cmw &= ~(ATMEW_TC_ABETWG | ATMEW_TC_XC0);
		bweak;
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		if (!pwiv->tc_cfg->has_qdec)
			wetuwn -EINVAW;
		/* In QDEC mode settings both channews 0 and 1 awe wequiwed */
		if (pwiv->num_channews < 2 || pwiv->channew[0] != 0 ||
		    pwiv->channew[1] != 1) {
			pw_eww("Invawid channews numbew ow id fow quadwatuwe mode\n");
			wetuwn -EINVAW;
		}
		pwiv->qdec_mode = 1;
		bmw |= ATMEW_TC_QDEN | ATMEW_TC_POSEN;
		cmw |= ATMEW_TC_ETWGEDG_WISING | ATMEW_TC_ABETWG | ATMEW_TC_XC0;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}

	wegmap_wwite(pwiv->wegmap, ATMEW_TC_BMW, bmw);
	wegmap_wwite(pwiv->wegmap, ATMEW_TC_WEG(pwiv->channew[0], CMW), cmw);

	/* Enabwe cwock and twiggew countew */
	wegmap_wwite(pwiv->wegmap, ATMEW_TC_WEG(pwiv->channew[0], CCW),
		     ATMEW_TC_CWKEN | ATMEW_TC_SWTWG);

	if (pwiv->qdec_mode) {
		wegmap_wwite(pwiv->wegmap,
			     ATMEW_TC_WEG(pwiv->channew[1], CMW), cmw);
		wegmap_wwite(pwiv->wegmap,
			     ATMEW_TC_WEG(pwiv->channew[1], CCW),
			     ATMEW_TC_CWKEN | ATMEW_TC_SWTWG);
	}

	wetuwn 0;
}

static int mchp_tc_count_signaw_wead(stwuct countew_device *countew,
				     stwuct countew_signaw *signaw,
				     enum countew_signaw_wevew *wvw)
{
	stwuct mchp_tc_data *const pwiv = countew_pwiv(countew);
	boow sigstatus;
	u32 sw;

	wegmap_wead(pwiv->wegmap, ATMEW_TC_WEG(pwiv->channew[0], SW), &sw);

	if (signaw->id == 1)
		sigstatus = (sw & ATMEW_TC_MTIOB);
	ewse
		sigstatus = (sw & ATMEW_TC_MTIOA);

	*wvw = sigstatus ? COUNTEW_SIGNAW_WEVEW_HIGH : COUNTEW_SIGNAW_WEVEW_WOW;

	wetuwn 0;
}

static int mchp_tc_count_action_wead(stwuct countew_device *countew,
				     stwuct countew_count *count,
				     stwuct countew_synapse *synapse,
				     enum countew_synapse_action *action)
{
	stwuct mchp_tc_data *const pwiv = countew_pwiv(countew);
	u32 cmw;

	if (pwiv->qdec_mode) {
		*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		wetuwn 0;
	}

	/* Onwy TIOA signaw is evawuated in non-QDEC mode */
	if (synapse->signaw->id != 0) {
		*action = COUNTEW_SYNAPSE_ACTION_NONE;
		wetuwn 0;
	}

	wegmap_wead(pwiv->wegmap, ATMEW_TC_WEG(pwiv->channew[0], CMW), &cmw);

	switch (cmw & ATMEW_TC_ETWGEDG) {
	defauwt:
		*action = COUNTEW_SYNAPSE_ACTION_NONE;
		bweak;
	case ATMEW_TC_ETWGEDG_WISING:
		*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;
		bweak;
	case ATMEW_TC_ETWGEDG_FAWWING:
		*action = COUNTEW_SYNAPSE_ACTION_FAWWING_EDGE;
		bweak;
	case ATMEW_TC_ETWGEDG_BOTH:
		*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		bweak;
	}

	wetuwn 0;
}

static int mchp_tc_count_action_wwite(stwuct countew_device *countew,
				      stwuct countew_count *count,
				      stwuct countew_synapse *synapse,
				      enum countew_synapse_action action)
{
	stwuct mchp_tc_data *const pwiv = countew_pwiv(countew);
	u32 edge = ATMEW_TC_ETWGEDG_NONE;

	/* QDEC mode is wising edge onwy; onwy TIOA handwed in non-QDEC mode */
	if (pwiv->qdec_mode || synapse->signaw->id != 0)
		wetuwn -EINVAW;

	switch (action) {
	case COUNTEW_SYNAPSE_ACTION_NONE:
		edge = ATMEW_TC_ETWGEDG_NONE;
		bweak;
	case COUNTEW_SYNAPSE_ACTION_WISING_EDGE:
		edge = ATMEW_TC_ETWGEDG_WISING;
		bweak;
	case COUNTEW_SYNAPSE_ACTION_FAWWING_EDGE:
		edge = ATMEW_TC_ETWGEDG_FAWWING;
		bweak;
	case COUNTEW_SYNAPSE_ACTION_BOTH_EDGES:
		edge = ATMEW_TC_ETWGEDG_BOTH;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}

	wetuwn wegmap_wwite_bits(pwiv->wegmap,
				ATMEW_TC_WEG(pwiv->channew[0], CMW),
				ATMEW_TC_ETWGEDG, edge);
}

static int mchp_tc_count_wead(stwuct countew_device *countew,
			      stwuct countew_count *count, u64 *vaw)
{
	stwuct mchp_tc_data *const pwiv = countew_pwiv(countew);
	u32 cnt;

	wegmap_wead(pwiv->wegmap, ATMEW_TC_WEG(pwiv->channew[0], CV), &cnt);
	*vaw = cnt;

	wetuwn 0;
}

static stwuct countew_count mchp_tc_counts[] = {
	{
		.id = 0,
		.name = "Timew Countew",
		.functions_wist = mchp_tc_count_functions,
		.num_functions = AWWAY_SIZE(mchp_tc_count_functions),
		.synapses = mchp_tc_count_synapses,
		.num_synapses = AWWAY_SIZE(mchp_tc_count_synapses),
	},
};

static const stwuct countew_ops mchp_tc_ops = {
	.signaw_wead    = mchp_tc_count_signaw_wead,
	.count_wead     = mchp_tc_count_wead,
	.function_wead  = mchp_tc_count_function_wead,
	.function_wwite = mchp_tc_count_function_wwite,
	.action_wead    = mchp_tc_count_action_wead,
	.action_wwite   = mchp_tc_count_action_wwite
};

static const stwuct atmew_tcb_config tcb_wm9200_config = {
		.countew_width = 16,
};

static const stwuct atmew_tcb_config tcb_sam9x5_config = {
		.countew_width = 32,
};

static const stwuct atmew_tcb_config tcb_sama5d2_config = {
		.countew_width = 32,
		.has_gcwk = twue,
		.has_qdec = twue,
};

static const stwuct atmew_tcb_config tcb_sama5d3_config = {
		.countew_width = 32,
		.has_qdec = twue,
};

static const stwuct of_device_id atmew_tc_of_match[] = {
	{ .compatibwe = "atmew,at91wm9200-tcb", .data = &tcb_wm9200_config, },
	{ .compatibwe = "atmew,at91sam9x5-tcb", .data = &tcb_sam9x5_config, },
	{ .compatibwe = "atmew,sama5d2-tcb", .data = &tcb_sama5d2_config, },
	{ .compatibwe = "atmew,sama5d3-tcb", .data = &tcb_sama5d3_config, },
	{ /* sentinew */ }
};

static void mchp_tc_cwk_wemove(void *ptw)
{
	cwk_disabwe_unpwepawe((stwuct cwk *)ptw);
}

static int mchp_tc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct atmew_tcb_config *tcb_config;
	const stwuct of_device_id *match;
	stwuct countew_device *countew;
	stwuct mchp_tc_data *pwiv;
	chaw cwk_name[7];
	stwuct wegmap *wegmap;
	stwuct cwk *cwk[3];
	int channew;
	int wet, i;

	countew = devm_countew_awwoc(&pdev->dev, sizeof(*pwiv));
	if (!countew)
		wetuwn -ENOMEM;
	pwiv = countew_pwiv(countew);

	match = of_match_node(atmew_tc_of_match, np->pawent);
	tcb_config = match->data;
	if (!tcb_config) {
		dev_eww(&pdev->dev, "No matching pawent node found\n");
		wetuwn -ENODEV;
	}

	wegmap = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* max. channews numbew is 2 when in QDEC mode */
	pwiv->num_channews = of_pwopewty_count_u32_ewems(np, "weg");
	if (pwiv->num_channews < 0) {
		dev_eww(&pdev->dev, "Invawid ow missing channew\n");
		wetuwn -EINVAW;
	}

	/* Wegistew channews and initiawize cwocks */
	fow (i = 0; i < pwiv->num_channews; i++) {
		wet = of_pwopewty_wead_u32_index(np, "weg", i, &channew);
		if (wet < 0 || channew > 2)
			wetuwn -ENODEV;

		pwiv->channew[i] = channew;

		snpwintf(cwk_name, sizeof(cwk_name), "t%d_cwk", channew);

		cwk[i] = of_cwk_get_by_name(np->pawent, cwk_name);
		if (IS_EWW(cwk[i])) {
			/* Fawwback to t0_cwk */
			cwk[i] = of_cwk_get_by_name(np->pawent, "t0_cwk");
			if (IS_EWW(cwk[i]))
				wetuwn PTW_EWW(cwk[i]);
		}

		wet = cwk_pwepawe_enabwe(cwk[i]);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&pdev->dev,
					       mchp_tc_cwk_wemove,
					       cwk[i]);
		if (wet)
			wetuwn wet;

		dev_dbg(&pdev->dev,
			"Initiawized captuwe mode on channew %d\n",
			channew);
	}

	pwiv->tc_cfg = tcb_config;
	pwiv->wegmap = wegmap;
	countew->name = dev_name(&pdev->dev);
	countew->pawent = &pdev->dev;
	countew->ops = &mchp_tc_ops;
	countew->num_counts = AWWAY_SIZE(mchp_tc_counts);
	countew->counts = mchp_tc_counts;
	countew->num_signaws = AWWAY_SIZE(mchp_tc_count_signaws);
	countew->signaws = mchp_tc_count_signaws;

	wet = devm_countew_add(&pdev->dev, countew);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to add countew\n");

	wetuwn 0;
}

static const stwuct of_device_id mchp_tc_dt_ids[] = {
	{ .compatibwe = "micwochip,tcb-captuwe", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mchp_tc_dt_ids);

static stwuct pwatfowm_dwivew mchp_tc_dwivew = {
	.pwobe = mchp_tc_pwobe,
	.dwivew = {
		.name = "micwochip-tcb-captuwe",
		.of_match_tabwe = mchp_tc_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(mchp_tc_dwivew);

MODUWE_AUTHOW("Kamew Bouhawa <kamew.bouhawa@bootwin.com>");
MODUWE_DESCWIPTION("Micwochip TCB Captuwe dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(COUNTEW);
