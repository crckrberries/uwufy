// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,q6sstopcc-qcs404.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-bwanch.h"
#incwude "common.h"
#incwude "weset.h"

static stwuct cwk_bwanch wcc_ahbfabwic_cbc_cwk = {
	.hawt_weg = 0x1b004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1b004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wcc_ahbfabwic_cbc_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wcc_q6ss_ahbs_cbc_cwk = {
	.hawt_weg = 0x22000,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x22000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wcc_q6ss_ahbs_cbc_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wcc_q6ss_tcm_swave_cbc_cwk = {
	.hawt_weg = 0x1c000,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x1c000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wcc_q6ss_tcm_swave_cbc_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wcc_q6ss_ahbm_cbc_cwk = {
	.hawt_weg = 0x22004,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x22004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wcc_q6ss_ahbm_cbc_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wcc_q6ss_axim_cbc_cwk = {
	.hawt_weg = 0x1c004,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x1c004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wcc_q6ss_axim_cbc_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wcc_q6ss_bcw_sweep_cwk = {
	.hawt_weg = 0x6004,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x6004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wcc_q6ss_bcw_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* TCSW cwock */
static stwuct cwk_bwanch tcsw_wcc_csw_cbcw_cwk = {
	.hawt_weg = 0x8008,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x8008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "tcsw_wcc_csw_cbcw_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct wegmap_config q6sstop_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.fast_io	= twue,
};

static stwuct cwk_wegmap *q6sstop_qcs404_cwocks[] = {
	[WCC_AHBFABWIC_CBC_CWK] = &wcc_ahbfabwic_cbc_cwk.cwkw,
	[WCC_Q6SS_AHBS_CBC_CWK] = &wcc_q6ss_ahbs_cbc_cwk.cwkw,
	[WCC_Q6SS_TCM_SWAVE_CBC_CWK] = &wcc_q6ss_tcm_swave_cbc_cwk.cwkw,
	[WCC_Q6SS_AHBM_CBC_CWK] = &wcc_q6ss_ahbm_cbc_cwk.cwkw,
	[WCC_Q6SS_AXIM_CBC_CWK] = &wcc_q6ss_axim_cbc_cwk.cwkw,
	[WCC_Q6SS_BCW_SWEEP_CWK] = &wcc_q6ss_bcw_sweep_cwk.cwkw,
};

static const stwuct qcom_weset_map q6sstop_qcs404_wesets[] = {
	[Q6SSTOP_BCW_WESET] = { 0x6000 },
};

static const stwuct qcom_cc_desc q6sstop_qcs404_desc = {
	.config = &q6sstop_wegmap_config,
	.cwks = q6sstop_qcs404_cwocks,
	.num_cwks = AWWAY_SIZE(q6sstop_qcs404_cwocks),
	.wesets = q6sstop_qcs404_wesets,
	.num_wesets = AWWAY_SIZE(q6sstop_qcs404_wesets),
};

static stwuct cwk_wegmap *tcsw_qcs404_cwocks[] = {
	[TCSW_Q6SS_WCC_CBCW_CWK] = &tcsw_wcc_csw_cbcw_cwk.cwkw,
};

static const stwuct qcom_cc_desc tcsw_qcs404_desc = {
	.config = &q6sstop_wegmap_config,
	.cwks = tcsw_qcs404_cwocks,
	.num_cwks = AWWAY_SIZE(tcsw_qcs404_cwocks),
};

static const stwuct of_device_id q6sstopcc_qcs404_match_tabwe[] = {
	{ .compatibwe = "qcom,qcs404-q6sstopcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, q6sstopcc_qcs404_match_tabwe);

static int q6sstopcc_qcs404_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
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

	q6sstop_wegmap_config.name = "q6sstop_tcsw";
	desc = &tcsw_qcs404_desc;

	wet = qcom_cc_pwobe_by_index(pdev, 1, desc);
	if (wet)
		goto eww_put_wpm;

	q6sstop_wegmap_config.name = "q6sstop_cc";
	desc = &q6sstop_qcs404_desc;

	wet = qcom_cc_pwobe_by_index(pdev, 0, desc);
	if (wet)
		goto eww_put_wpm;

	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

eww_put_wpm:
	pm_wuntime_put_sync(&pdev->dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops q6sstopcc_pm_ops = {
	SET_WUNTIME_PM_OPS(pm_cwk_suspend, pm_cwk_wesume, NUWW)
};

static stwuct pwatfowm_dwivew q6sstopcc_qcs404_dwivew = {
	.pwobe		= q6sstopcc_qcs404_pwobe,
	.dwivew		= {
		.name	= "qcs404-q6sstopcc",
		.of_match_tabwe = q6sstopcc_qcs404_match_tabwe,
		.pm = &q6sstopcc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(q6sstopcc_qcs404_dwivew);

MODUWE_DESCWIPTION("QTI QCS404 Q6SSTOP Cwock Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
