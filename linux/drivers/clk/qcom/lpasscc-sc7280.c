// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,wpass-sc7280.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-bwanch.h"
#incwude "common.h"

static stwuct cwk_bwanch wpass_top_cc_wpi_q6_axim_hs_cwk = {
	.hawt_weg = 0x0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_top_cc_wpi_q6_axim_hs_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_qdsp6ss_cowe_cwk = {
	.hawt_weg = 0x20,
	/* CWK_OFF wouwd not toggwe untiw WPASS is out of weset */
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x20,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_qdsp6ss_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_qdsp6ss_xo_cwk = {
	.hawt_weg = 0x38,
	/* CWK_OFF wouwd not toggwe untiw WPASS is out of weset */
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x38,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_qdsp6ss_xo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_qdsp6ss_sweep_cwk = {
	.hawt_weg = 0x3c,
	/* CWK_OFF wouwd not toggwe untiw WPASS is out of weset */
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x3c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_qdsp6ss_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct wegmap_config wpass_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.fast_io	= twue,
};

static stwuct cwk_wegmap *wpass_cc_top_sc7280_cwocks[] = {
	[WPASS_TOP_CC_WPI_Q6_AXIM_HS_CWK] =
				&wpass_top_cc_wpi_q6_axim_hs_cwk.cwkw,
};

static const stwuct qcom_cc_desc wpass_cc_top_sc7280_desc = {
	.config = &wpass_wegmap_config,
	.cwks = wpass_cc_top_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_cc_top_sc7280_cwocks),
};

static stwuct cwk_wegmap *wpass_qdsp6ss_sc7280_cwocks[] = {
	[WPASS_QDSP6SS_XO_CWK] = &wpass_qdsp6ss_xo_cwk.cwkw,
	[WPASS_QDSP6SS_SWEEP_CWK] = &wpass_qdsp6ss_sweep_cwk.cwkw,
	[WPASS_QDSP6SS_COWE_CWK] = &wpass_qdsp6ss_cowe_cwk.cwkw,
};

static const stwuct qcom_cc_desc wpass_qdsp6ss_sc7280_desc = {
	.config = &wpass_wegmap_config,
	.cwks = wpass_qdsp6ss_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_qdsp6ss_sc7280_cwocks),
};

static int wpass_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_cwk_cweate(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_cwk_add(&pdev->dev, "iface");
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to acquiwe iface cwock\n");
		goto eww_destwoy_pm_cwk;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		goto eww_destwoy_pm_cwk;

	if (!of_pwopewty_wead_boow(pdev->dev.of_node, "qcom,adsp-piw-mode")) {
		wpass_wegmap_config.name = "qdsp6ss";
		wpass_wegmap_config.max_wegistew = 0x3f;
		desc = &wpass_qdsp6ss_sc7280_desc;

		wet = qcom_cc_pwobe_by_index(pdev, 0, desc);
		if (wet)
			goto eww_put_wpm;
	}

	wpass_wegmap_config.name = "top_cc";
	wpass_wegmap_config.max_wegistew = 0x4;
	desc = &wpass_cc_top_sc7280_desc;

	wet = qcom_cc_pwobe_by_index(pdev, 1, desc);
	if (wet)
		goto eww_put_wpm;

	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

eww_put_wpm:
	pm_wuntime_put_sync(&pdev->dev);
eww_destwoy_pm_cwk:
	pm_cwk_destwoy(&pdev->dev);

	wetuwn wet;
}

static const stwuct of_device_id wpass_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-wpasscc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_cc_sc7280_match_tabwe);

static stwuct pwatfowm_dwivew wpass_cc_sc7280_dwivew = {
	.pwobe		= wpass_cc_sc7280_pwobe,
	.dwivew		= {
		.name	= "sc7280-wpasscc",
		.of_match_tabwe = wpass_cc_sc7280_match_tabwe,
	},
};

static int __init wpass_cc_sc7280_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpass_cc_sc7280_dwivew);
}
subsys_initcaww(wpass_cc_sc7280_init);

static void __exit wpass_cc_sc7280_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpass_cc_sc7280_dwivew);
}
moduwe_exit(wpass_cc_sc7280_exit);

MODUWE_DESCWIPTION("QTI WPASS_CC SC7280 Dwivew");
MODUWE_WICENSE("GPW v2");
