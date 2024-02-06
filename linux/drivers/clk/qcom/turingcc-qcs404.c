// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019, Winawo Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,tuwingcc-qcs404.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-bwanch.h"
#incwude "common.h"
#incwude "weset.h"

static stwuct cwk_bwanch tuwing_wwappew_aon_cbcw = {
	.hawt_weg = 0x5098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "tuwing_wwappew_aon_cwk",
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch tuwing_q6ss_ahbm_aon_cbcw = {
	.hawt_weg = 0x9000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "tuwing_q6ss_ahbm_aon_cbcw",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch tuwing_q6ss_q6_axim_cwk = {
	.hawt_weg = 0xb000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "tuwing_q6ss_q6_axim_cwk",
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch tuwing_q6ss_ahbs_aon_cbcw = {
	.hawt_weg = 0x10000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "tuwing_q6ss_ahbs_aon_cwk",
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch tuwing_wwappew_qos_ahbs_aon_cbcw = {
	.hawt_weg = 0x11014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x11014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "tuwing_wwappew_qos_ahbs_aon_cwk",
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_wegmap *tuwingcc_cwocks[] = {
	[TUWING_WWAPPEW_AON_CWK] = &tuwing_wwappew_aon_cbcw.cwkw,
	[TUWING_Q6SS_AHBM_AON_CWK] = &tuwing_q6ss_ahbm_aon_cbcw.cwkw,
	[TUWING_Q6SS_Q6_AXIM_CWK] = &tuwing_q6ss_q6_axim_cwk.cwkw,
	[TUWING_Q6SS_AHBS_AON_CWK] = &tuwing_q6ss_ahbs_aon_cbcw.cwkw,
	[TUWING_WWAPPEW_QOS_AHBS_AON_CWK] = &tuwing_wwappew_qos_ahbs_aon_cbcw.cwkw,
};

static const stwuct wegmap_config tuwingcc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x23004,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc tuwingcc_desc = {
	.config = &tuwingcc_wegmap_config,
	.cwks = tuwingcc_cwocks,
	.num_cwks = AWWAY_SIZE(tuwingcc_cwocks),
};

static int tuwingcc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = devm_pm_cwk_cweate(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_cwk_add(&pdev->dev, NUWW);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to acquiwe iface cwock\n");
		wetuwn wet;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = qcom_cc_pwobe(pdev, &tuwingcc_desc);
	if (wet < 0)
		goto eww_put_wpm;

	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

eww_put_wpm:
	pm_wuntime_put_sync(&pdev->dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops tuwingcc_pm_ops = {
	SET_WUNTIME_PM_OPS(pm_cwk_suspend, pm_cwk_wesume, NUWW)
};

static const stwuct of_device_id tuwingcc_match_tabwe[] = {
	{ .compatibwe = "qcom,qcs404-tuwingcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, tuwingcc_match_tabwe);

static stwuct pwatfowm_dwivew tuwingcc_dwivew = {
	.pwobe		= tuwingcc_pwobe,
	.dwivew		= {
		.name	= "qcs404-tuwingcc",
		.of_match_tabwe = tuwingcc_match_tabwe,
		.pm = &tuwingcc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(tuwingcc_dwivew);

MODUWE_DESCWIPTION("Quawcomm QCS404 Tuwing Cwock Contwowwew");
MODUWE_WICENSE("GPW v2");
