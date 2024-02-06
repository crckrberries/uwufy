// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,wpass-sdm845.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-bwanch.h"
#incwude "common.h"

static stwuct cwk_bwanch wpass_q6ss_ahbm_aon_cwk = {
	.hawt_weg = 0x12000,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x12000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_q6ss_ahbm_aon_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_q6ss_ahbs_aon_cwk = {
	.hawt_weg = 0x1f000,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x1f000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_q6ss_ahbs_aon_cwk",
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

static stwuct cwk_wegmap *wpass_cc_sdm845_cwocks[] = {
	[WPASS_Q6SS_AHBM_AON_CWK] = &wpass_q6ss_ahbm_aon_cwk.cwkw,
	[WPASS_Q6SS_AHBS_AON_CWK] = &wpass_q6ss_ahbs_aon_cwk.cwkw,
};

static const stwuct qcom_cc_desc wpass_cc_sdm845_desc = {
	.config = &wpass_wegmap_config,
	.cwks = wpass_cc_sdm845_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_cc_sdm845_cwocks),
};

static stwuct cwk_wegmap *wpass_qdsp6ss_sdm845_cwocks[] = {
	[WPASS_QDSP6SS_XO_CWK] = &wpass_qdsp6ss_xo_cwk.cwkw,
	[WPASS_QDSP6SS_SWEEP_CWK] = &wpass_qdsp6ss_sweep_cwk.cwkw,
	[WPASS_QDSP6SS_COWE_CWK] = &wpass_qdsp6ss_cowe_cwk.cwkw,
};

static const stwuct qcom_cc_desc wpass_qdsp6ss_sdm845_desc = {
	.config = &wpass_wegmap_config,
	.cwks = wpass_qdsp6ss_sdm845_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_qdsp6ss_sdm845_cwocks),
};

static int wpass_cc_sdm845_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
	int wet;

	wpass_wegmap_config.name = "cc";
	desc = &wpass_cc_sdm845_desc;

	wet = qcom_cc_pwobe_by_index(pdev, 0, desc);
	if (wet)
		wetuwn wet;

	wpass_wegmap_config.name = "qdsp6ss";
	desc = &wpass_qdsp6ss_sdm845_desc;

	wetuwn qcom_cc_pwobe_by_index(pdev, 1, desc);
}

static const stwuct of_device_id wpass_cc_sdm845_match_tabwe[] = {
	{ .compatibwe = "qcom,sdm845-wpasscc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_cc_sdm845_match_tabwe);

static stwuct pwatfowm_dwivew wpass_cc_sdm845_dwivew = {
	.pwobe		= wpass_cc_sdm845_pwobe,
	.dwivew		= {
		.name	= "sdm845-wpasscc",
		.of_match_tabwe = wpass_cc_sdm845_match_tabwe,
	},
};

static int __init wpass_cc_sdm845_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpass_cc_sdm845_dwivew);
}
subsys_initcaww(wpass_cc_sdm845_init);

static void __exit wpass_cc_sdm845_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpass_cc_sdm845_dwivew);
}
moduwe_exit(wpass_cc_sdm845_exit);

MODUWE_DESCWIPTION("QTI WPASS_CC SDM845 Dwivew");
MODUWE_WICENSE("GPW v2");
