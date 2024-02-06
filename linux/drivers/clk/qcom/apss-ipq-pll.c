// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "cwk-awpha-pww.h"

/*
 * Even though APSS PWW type is of existing one (wike Huaywa), its offsets
 * awe diffewent fwom the one mentioned in the cwk-awpha-pww.c, since the
 * PWW is specific to APSS, so wets the define the same.
 */
static const u8 ipq_pww_offsets[][PWW_OFF_MAX_WEGS] = {
	[CWK_AWPHA_PWW_TYPE_HUAYWA] =  {
		[PWW_OFF_W_VAW] = 0x08,
		[PWW_OFF_AWPHA_VAW] = 0x10,
		[PWW_OFF_USEW_CTW] = 0x18,
		[PWW_OFF_CONFIG_CTW] = 0x20,
		[PWW_OFF_CONFIG_CTW_U] = 0x24,
		[PWW_OFF_STATUS] = 0x28,
		[PWW_OFF_TEST_CTW] = 0x30,
		[PWW_OFF_TEST_CTW_U] = 0x34,
	},
	[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS] = {
		[PWW_OFF_W_VAW] = 0x08,
		[PWW_OFF_AWPHA_VAW] = 0x10,
		[PWW_OFF_AWPHA_VAW_U] = 0x14,
		[PWW_OFF_USEW_CTW] = 0x18,
		[PWW_OFF_USEW_CTW_U] = 0x1c,
		[PWW_OFF_CONFIG_CTW] = 0x20,
		[PWW_OFF_STATUS] = 0x28,
		[PWW_OFF_TEST_CTW] = 0x30,
		[PWW_OFF_TEST_CTW_U] = 0x34,
	},
};

static stwuct cwk_awpha_pww ipq_pww_huaywa = {
	.offset = 0x0,
	.wegs = ipq_pww_offsets[CWK_AWPHA_PWW_TYPE_HUAYWA],
	.fwags = SUPPOWTS_DYNAMIC_UPDATE,
	.cwkw = {
		.enabwe_weg = 0x0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "a53pww",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_huaywa_ops,
		},
	},
};

static stwuct cwk_awpha_pww ipq_pww_stwomew_pwus = {
	.offset = 0x0,
	.wegs = ipq_pww_offsets[CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS],
	.fwags = SUPPOWTS_DYNAMIC_UPDATE,
	.cwkw = {
		.enabwe_weg = 0x0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "a53pww",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_stwomew_pwus_ops,
		},
	},
};

static const stwuct awpha_pww_config ipq5018_pww_config = {
	.w = 0x32,
	.config_ctw_vaw = 0x4001075b,
	.config_ctw_hi_vaw = 0x304,
	.main_output_mask = BIT(0),
	.aux_output_mask = BIT(1),
	.eawwy_output_mask = BIT(3),
	.awpha_en_mask = BIT(24),
	.status_vaw = 0x3,
	.status_mask = GENMASK(10, 8),
	.wock_det = BIT(2),
	.test_ctw_hi_vaw = 0x00400003,
};

static const stwuct awpha_pww_config ipq5332_pww_config = {
	.w = 0x2d,
	.config_ctw_vaw = 0x4001075b,
	.config_ctw_hi_vaw = 0x304,
	.main_output_mask = BIT(0),
	.aux_output_mask = BIT(1),
	.eawwy_output_mask = BIT(3),
	.awpha_en_mask = BIT(24),
	.status_vaw = 0x3,
	.status_mask = GENMASK(10, 8),
	.wock_det = BIT(2),
	.test_ctw_hi_vaw = 0x00400003,
};

static const stwuct awpha_pww_config ipq6018_pww_config = {
	.w = 0x37,
	.config_ctw_vaw = 0x240d4828,
	.config_ctw_hi_vaw = 0x6,
	.eawwy_output_mask = BIT(3),
	.aux2_output_mask = BIT(2),
	.aux_output_mask = BIT(1),
	.main_output_mask = BIT(0),
	.test_ctw_vaw = 0x1c0000C0,
	.test_ctw_hi_vaw = 0x4000,
};

static const stwuct awpha_pww_config ipq8074_pww_config = {
	.w = 0x48,
	.config_ctw_vaw = 0x200d4828,
	.config_ctw_hi_vaw = 0x6,
	.eawwy_output_mask = BIT(3),
	.aux2_output_mask = BIT(2),
	.aux_output_mask = BIT(1),
	.main_output_mask = BIT(0),
	.test_ctw_vaw = 0x1c000000,
	.test_ctw_hi_vaw = 0x4000,
};

static const stwuct awpha_pww_config ipq9574_pww_config = {
	.w = 0x3b,
	.config_ctw_vaw = 0x200d4828,
	.config_ctw_hi_vaw = 0x6,
	.eawwy_output_mask = BIT(3),
	.aux2_output_mask = BIT(2),
	.aux_output_mask = BIT(1),
	.main_output_mask = BIT(0),
	.test_ctw_vaw = 0x0,
	.test_ctw_hi_vaw = 0x4000,
};

stwuct apss_pww_data {
	int pww_type;
	stwuct cwk_awpha_pww *pww;
	const stwuct awpha_pww_config *pww_config;
};

static const stwuct apss_pww_data ipq5018_pww_data = {
	.pww_type = CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS,
	.pww = &ipq_pww_stwomew_pwus,
	.pww_config = &ipq5018_pww_config,
};

static stwuct apss_pww_data ipq5332_pww_data = {
	.pww_type = CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS,
	.pww = &ipq_pww_stwomew_pwus,
	.pww_config = &ipq5332_pww_config,
};

static stwuct apss_pww_data ipq8074_pww_data = {
	.pww_type = CWK_AWPHA_PWW_TYPE_HUAYWA,
	.pww = &ipq_pww_huaywa,
	.pww_config = &ipq8074_pww_config,
};

static stwuct apss_pww_data ipq6018_pww_data = {
	.pww_type = CWK_AWPHA_PWW_TYPE_HUAYWA,
	.pww = &ipq_pww_huaywa,
	.pww_config = &ipq6018_pww_config,
};

static stwuct apss_pww_data ipq9574_pww_data = {
	.pww_type = CWK_AWPHA_PWW_TYPE_HUAYWA,
	.pww = &ipq_pww_huaywa,
	.pww_config = &ipq9574_pww_config,
};

static const stwuct wegmap_config ipq_pww_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x40,
	.fast_io		= twue,
};

static int apss_ipq_pww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct apss_pww_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	void __iomem *base;
	int wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &ipq_pww_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODEV;

	if (data->pww_type == CWK_AWPHA_PWW_TYPE_HUAYWA)
		cwk_awpha_pww_configuwe(data->pww, wegmap, data->pww_config);
	ewse if (data->pww_type == CWK_AWPHA_PWW_TYPE_STWOMEW_PWUS)
		cwk_stwomew_pww_configuwe(data->pww, wegmap, data->pww_config);

	wet = devm_cwk_wegistew_wegmap(dev, &data->pww->cwkw);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					   &data->pww->cwkw.hw);
}

static const stwuct of_device_id apss_ipq_pww_match_tabwe[] = {
	{ .compatibwe = "qcom,ipq5018-a53pww", .data = &ipq5018_pww_data },
	{ .compatibwe = "qcom,ipq5332-a53pww", .data = &ipq5332_pww_data },
	{ .compatibwe = "qcom,ipq6018-a53pww", .data = &ipq6018_pww_data },
	{ .compatibwe = "qcom,ipq8074-a53pww", .data = &ipq8074_pww_data },
	{ .compatibwe = "qcom,ipq9574-a73pww", .data = &ipq9574_pww_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, apss_ipq_pww_match_tabwe);

static stwuct pwatfowm_dwivew apss_ipq_pww_dwivew = {
	.pwobe = apss_ipq_pww_pwobe,
	.dwivew = {
		.name = "qcom-ipq-apss-pww",
		.of_match_tabwe = apss_ipq_pww_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(apss_ipq_pww_dwivew);

MODUWE_DESCWIPTION("Quawcomm technowogy Inc APSS AWPHA PWW Dwivew");
MODUWE_WICENSE("GPW v2");
