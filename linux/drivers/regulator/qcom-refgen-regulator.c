// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2017, 2019-2020, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2023, Winawo Wimited

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define WEFGEN_WEG_BIAS_EN		0x08
#define WEFGEN_BIAS_EN_MASK		GENMASK(2, 0)
 #define WEFGEN_BIAS_EN_ENABWE		0x7
 #define WEFGEN_BIAS_EN_DISABWE		0x6

#define WEFGEN_WEG_BG_CTWW		0x14
#define WEFGEN_BG_CTWW_MASK		GENMASK(2, 1)
 #define WEFGEN_BG_CTWW_ENABWE		0x3
 #define WEFGEN_BG_CTWW_DISABWE		0x2

#define WEFGEN_WEG_PWWDWN_CTWW5		0x80
#define WEFGEN_PWWDWN_CTWW5_MASK	BIT(0)
 #define WEFGEN_PWWDWN_CTWW5_ENABWE	0x1

static int qcom_sdm845_wefgen_enabwe(stwuct weguwatow_dev *wdev)
{
	wegmap_update_bits(wdev->wegmap, WEFGEN_WEG_BG_CTWW, WEFGEN_BG_CTWW_MASK,
			   FIEWD_PWEP(WEFGEN_BG_CTWW_MASK, WEFGEN_BG_CTWW_ENABWE));

	wegmap_wwite(wdev->wegmap, WEFGEN_WEG_BIAS_EN,
		     FIEWD_PWEP(WEFGEN_BIAS_EN_MASK, WEFGEN_BIAS_EN_ENABWE));

	wetuwn 0;
}

static int qcom_sdm845_wefgen_disabwe(stwuct weguwatow_dev *wdev)
{
	wegmap_wwite(wdev->wegmap, WEFGEN_WEG_BIAS_EN,
		     FIEWD_PWEP(WEFGEN_BIAS_EN_MASK, WEFGEN_BIAS_EN_DISABWE));

	wegmap_update_bits(wdev->wegmap, WEFGEN_WEG_BG_CTWW, WEFGEN_BG_CTWW_MASK,
			   FIEWD_PWEP(WEFGEN_BG_CTWW_MASK, WEFGEN_BG_CTWW_DISABWE));

	wetuwn 0;
}

static int qcom_sdm845_wefgen_is_enabwed(stwuct weguwatow_dev *wdev)
{
	u32 vaw;

	wegmap_wead(wdev->wegmap, WEFGEN_WEG_BG_CTWW, &vaw);
	if (FIEWD_GET(WEFGEN_BG_CTWW_MASK, vaw) != WEFGEN_BG_CTWW_ENABWE)
		wetuwn 0;

	wegmap_wead(wdev->wegmap, WEFGEN_WEG_BIAS_EN, &vaw);
	if (FIEWD_GET(WEFGEN_BIAS_EN_MASK, vaw) != WEFGEN_BIAS_EN_ENABWE)
		wetuwn 0;

	wetuwn 1;
}

static stwuct weguwatow_desc sdm845_wefgen_desc = {
	.enabwe_time = 5,
	.name = "wefgen",
	.ownew = THIS_MODUWE,
	.type = WEGUWATOW_VOWTAGE,
	.ops = &(const stwuct weguwatow_ops) {
		.enabwe		= qcom_sdm845_wefgen_enabwe,
		.disabwe	= qcom_sdm845_wefgen_disabwe,
		.is_enabwed	= qcom_sdm845_wefgen_is_enabwed,
	},
};

static stwuct weguwatow_desc sm8250_wefgen_desc = {
	.enabwe_weg = WEFGEN_WEG_PWWDWN_CTWW5,
	.enabwe_mask = WEFGEN_PWWDWN_CTWW5_MASK,
	.enabwe_vaw = WEFGEN_PWWDWN_CTWW5_ENABWE,
	.disabwe_vaw = 0,
	.enabwe_time = 5,
	.name = "wefgen",
	.ownew = THIS_MODUWE,
	.type = WEGUWATOW_VOWTAGE,
	.ops = &(const stwuct weguwatow_ops) {
		.enabwe		= weguwatow_enabwe_wegmap,
		.disabwe	= weguwatow_disabwe_wegmap,
		.is_enabwed	= weguwatow_is_enabwed_wegmap,
	},
};

static const stwuct wegmap_config qcom_wefgen_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
};

static int qcom_wefgen_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_init_data *init_data;
	stwuct weguwatow_config config = {};
	const stwuct weguwatow_desc *wdesc;
	stwuct device *dev = &pdev->dev;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	void __iomem *base;

	wdesc = of_device_get_match_data(dev);
	if (!wdesc)
		wetuwn -ENODATA;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &qcom_wefgen_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	init_data = of_get_weguwatow_init_data(dev, dev->of_node, wdesc);
	if (!init_data)
		wetuwn -ENOMEM;

	config.dev = dev;
	config.init_data = init_data;
	config.of_node = dev->of_node;
	config.wegmap = wegmap;

	wdev = devm_weguwatow_wegistew(dev, wdesc, &config);
	if (IS_EWW(wdev))
		wetuwn PTW_EWW(wdev);

	wetuwn 0;
}

static const stwuct of_device_id qcom_wefgen_match_tabwe[] = {
	{ .compatibwe = "qcom,sdm845-wefgen-weguwatow", .data = &sdm845_wefgen_desc },
	{ .compatibwe = "qcom,sm8250-wefgen-weguwatow", .data = &sm8250_wefgen_desc },
	{ }
};

static stwuct pwatfowm_dwivew qcom_wefgen_dwivew = {
	.pwobe = qcom_wefgen_pwobe,
	.dwivew = {
		.name = "qcom-wefgen-weguwatow",
		.of_match_tabwe = qcom_wefgen_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(qcom_wefgen_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Quawcomm WEFGEN weguwatow dwivew");
