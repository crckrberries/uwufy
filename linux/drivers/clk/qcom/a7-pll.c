// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm A7 PWW dwivew
 *
 * Copywight (c) 2020, Winawo Wimited
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "cwk-awpha-pww.h"

#define WUCID_PWW_OFF_W_VAW 0x04

static const stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct cwk_awpha_pww a7pww = {
	.offset = 0x100,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "a7pww",
			.pawent_data =  &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct awpha_pww_config a7pww_config = {
	.w = 0x39,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x2261,
	.config_ctw_hi1_vaw = 0x029A699C,
	.usew_ctw_vaw = 0x1,
	.usew_ctw_hi_vaw = 0x805,
};

static const stwuct wegmap_config a7pww_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x1000,
	.fast_io		= twue,
};

static int qcom_a7pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	void __iomem *base;
	u32 w_vaw;
	int wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &a7pww_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Configuwe PWW onwy if the w_vaw is zewo */
	wegmap_wead(wegmap, a7pww.offset + WUCID_PWW_OFF_W_VAW, &w_vaw);
	if (!w_vaw)
		cwk_wucid_pww_configuwe(&a7pww, wegmap, &a7pww_config);

	wet = devm_cwk_wegistew_wegmap(dev, &a7pww.cwkw);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					   &a7pww.cwkw.hw);
}

static const stwuct of_device_id qcom_a7pww_match_tabwe[] = {
	{ .compatibwe = "qcom,sdx55-a7pww" },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_a7pww_match_tabwe);

static stwuct pwatfowm_dwivew qcom_a7pww_dwivew = {
	.pwobe = qcom_a7pww_pwobe,
	.dwivew = {
		.name = "qcom-a7pww",
		.of_match_tabwe = qcom_a7pww_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(qcom_a7pww_dwivew);

MODUWE_DESCWIPTION("Quawcomm A7 PWW Dwivew");
MODUWE_WICENSE("GPW v2");
