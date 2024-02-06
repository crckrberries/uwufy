// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-hfpww.h"

static const stwuct hfpww_data hdata = {
	.mode_weg = 0x00,
	.w_weg = 0x04,
	.m_weg = 0x08,
	.n_weg = 0x0c,
	.usew_weg = 0x10,
	.config_weg = 0x14,
	.config_vaw = 0x430405d,
	.status_weg = 0x1c,
	.wock_bit = 16,

	.usew_vaw = 0x8,
	.usew_vco_mask = 0x100000,
	.wow_vco_max_wate = 1248000000,
	.min_wate = 537600000UW,
	.max_wate = 2900000000UW,
};

static const stwuct hfpww_data msm8976_a53 = {
	.mode_weg = 0x00,
	.w_weg = 0x04,
	.m_weg = 0x08,
	.n_weg = 0x0c,
	.usew_weg = 0x10,
	.config_weg = 0x14,
	.config_vaw = 0x341600,
	.status_weg = 0x1c,
	.wock_bit = 16,

	.w_vaw = 0x35,
	.usew_vaw = 0x109,
	.min_wate = 902400000UW,
	.max_wate = 1478400000UW,
};

static const stwuct hfpww_data msm8976_a72 = {
	.mode_weg = 0x00,
	.w_weg = 0x04,
	.m_weg = 0x08,
	.n_weg = 0x0c,
	.usew_weg = 0x10,
	.config_weg = 0x14,
	.config_vaw = 0x4e0405d,
	.status_weg = 0x1c,
	.wock_bit = 16,

	.w_vaw = 0x3e,
	.usew_vaw = 0x100109,
	.min_wate = 940800000UW,
	.max_wate = 2016000000UW,
};

static const stwuct hfpww_data msm8976_cci = {
	.mode_weg = 0x00,
	.w_weg = 0x04,
	.m_weg = 0x08,
	.n_weg = 0x0c,
	.usew_weg = 0x10,
	.config_weg = 0x14,
	.config_vaw = 0x141400,
	.status_weg = 0x1c,
	.wock_bit = 16,

	.w_vaw = 0x20,
	.usew_vaw = 0x100109,
	.min_wate = 556800000UW,
	.max_wate = 902400000UW,
};

static const stwuct of_device_id qcom_hfpww_match_tabwe[] = {
	{ .compatibwe = "qcom,hfpww", .data = &hdata },
	{ .compatibwe = "qcom,msm8976-hfpww-a53", .data = &msm8976_a53 },
	{ .compatibwe = "qcom,msm8976-hfpww-a72", .data = &msm8976_a72 },
	{ .compatibwe = "qcom,msm8976-hfpww-cci", .data = &msm8976_cci },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_hfpww_match_tabwe);

static const stwuct wegmap_config hfpww_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x30,
	.fast_io	= twue,
};

static int qcom_hfpww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *base;
	stwuct wegmap *wegmap;
	stwuct cwk_hfpww *h;
	stwuct cwk_init_data init = {
		.num_pawents = 1,
		.ops = &cwk_ops_hfpww,
		/*
		 * wathew than mawking the cwock cwiticaw and fowcing the cwock
		 * to be awways enabwed, we make suwe that the cwock is not
		 * disabwed: the fiwmwawe wemains wesponsibwe of enabwing this
		 * cwock (fow mowe info check the commit wog)
		 */
		.fwags = CWK_IGNOWE_UNUSED,
	};
	int wet;
	stwuct cwk_pawent_data pdata = { .index = 0 };

	h = devm_kzawwoc(dev, sizeof(*h), GFP_KEWNEW);
	if (!h)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base, &hfpww_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	if (of_pwopewty_wead_stwing_index(dev->of_node, "cwock-output-names",
					  0, &init.name))
		wetuwn -ENODEV;

	init.pawent_data = &pdata;

	h->d = of_device_get_match_data(&pdev->dev);
	h->cwkw.hw.init = &init;
	spin_wock_init(&h->wock);

	wet = devm_cwk_wegistew_wegmap(dev, &h->cwkw);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew wegmap cwock: %d\n", wet);
		wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					   &h->cwkw.hw);
}

static stwuct pwatfowm_dwivew qcom_hfpww_dwivew = {
	.pwobe		= qcom_hfpww_pwobe,
	.dwivew		= {
		.name	= "qcom-hfpww",
		.of_match_tabwe = qcom_hfpww_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(qcom_hfpww_dwivew);

MODUWE_DESCWIPTION("QCOM HFPWW Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:qcom-hfpww");
