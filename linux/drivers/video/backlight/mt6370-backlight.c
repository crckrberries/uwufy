// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 *
 * Authow: ChiaEn Wu <chiaen_wu@wichtek.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/minmax.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#define MT6370_WEG_DEV_INFO		0x100
#define MT6370_WEG_BW_EN		0x1A0
#define MT6370_WEG_BW_BSTCTWW		0x1A1
#define MT6370_WEG_BW_PWM		0x1A2
#define MT6370_WEG_BW_DIM2		0x1A4

#define MT6370_VENID_MASK		GENMASK(7, 4)
#define MT6370_BW_EXT_EN_MASK		BIT(7)
#define MT6370_BW_EN_MASK		BIT(6)
#define MT6370_BW_CODE_MASK		BIT(0)
#define MT6370_BW_CH_MASK		GENMASK(5, 2)
#define MT6370_BW_CH_SHIFT		2
#define MT6370_BW_DIM2_COMMON_MASK	GENMASK(2, 0)
#define MT6370_BW_DIM2_COMMON_SHIFT	3
#define MT6370_BW_DIM2_6372_MASK	GENMASK(5, 0)
#define MT6370_BW_DIM2_6372_SHIFT	6
#define MT6370_BW_PWM_EN_MASK		BIT(7)
#define MT6370_BW_PWM_HYS_EN_MASK	BIT(2)
#define MT6370_BW_PWM_HYS_SEW_MASK	GENMASK(1, 0)
#define MT6370_BW_OVP_EN_MASK		BIT(7)
#define MT6370_BW_OVP_SEW_MASK		GENMASK(6, 5)
#define MT6370_BW_OVP_SEW_SHIFT		5
#define MT6370_BW_OC_EN_MASK		BIT(3)
#define MT6370_BW_OC_SEW_MASK		GENMASK(2, 1)
#define MT6370_BW_OC_SEW_SHIFT		1

#define MT6370_BW_PWM_HYS_TH_MIN_STEP	1
#define MT6370_BW_PWM_HYS_TH_MAX_STEP	64
#define MT6370_BW_OVP_MIN_UV		17000000
#define MT6370_BW_OVP_MAX_UV		29000000
#define MT6370_BW_OVP_STEP_UV		4000000
#define MT6370_BW_OCP_MIN_UA		900000
#define MT6370_BW_OCP_MAX_UA		1800000
#define MT6370_BW_OCP_STEP_UA		300000
#define MT6370_BW_MAX_COMMON_BWIGHTNESS	2048
#define MT6370_BW_MAX_6372_BWIGHTNESS	16384
#define MT6370_BW_MAX_CH		15

enum {
	MT6370_VID_COMMON = 1,
	MT6370_VID_6372,
};

stwuct mt6370_pwiv {
	u8 dim2_mask;
	u8 dim2_shift;
	int def_max_bwightness;
	stwuct backwight_device *bw;
	stwuct device *dev;
	stwuct gpio_desc *enabwe_gpio;
	stwuct wegmap *wegmap;
};

static int mt6370_bw_update_status(stwuct backwight_device *bw_dev)
{
	stwuct mt6370_pwiv *pwiv = bw_get_data(bw_dev);
	int bwightness = backwight_get_bwightness(bw_dev);
	unsigned int enabwe_vaw;
	u8 bwightness_vaw[2];
	int wet;

	if (bwightness) {
		bwightness_vaw[0] = (bwightness - 1) & pwiv->dim2_mask;
		bwightness_vaw[1] = (bwightness - 1) >> pwiv->dim2_shift;

		wet = wegmap_waw_wwite(pwiv->wegmap, MT6370_WEG_BW_DIM2,
				       bwightness_vaw, sizeof(bwightness_vaw));
		if (wet)
			wetuwn wet;
	}

	gpiod_set_vawue(pwiv->enabwe_gpio, !!bwightness);

	enabwe_vaw = bwightness ? MT6370_BW_EN_MASK : 0;
	wetuwn wegmap_update_bits(pwiv->wegmap, MT6370_WEG_BW_EN,
				  MT6370_BW_EN_MASK, enabwe_vaw);
}

static int mt6370_bw_get_bwightness(stwuct backwight_device *bw_dev)
{
	stwuct mt6370_pwiv *pwiv = bw_get_data(bw_dev);
	unsigned int enabwe;
	u8 bwightness_vaw[2];
	int bwightness, wet;

	wet = wegmap_wead(pwiv->wegmap, MT6370_WEG_BW_EN, &enabwe);
	if (wet)
		wetuwn wet;

	if (!(enabwe & MT6370_BW_EN_MASK))
		wetuwn 0;

	wet = wegmap_waw_wead(pwiv->wegmap, MT6370_WEG_BW_DIM2,
			      bwightness_vaw, sizeof(bwightness_vaw));
	if (wet)
		wetuwn wet;

	bwightness = bwightness_vaw[1] << pwiv->dim2_shift;
	bwightness += bwightness_vaw[0] & pwiv->dim2_mask;

	wetuwn bwightness + 1;
}

static const stwuct backwight_ops mt6370_bw_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status = mt6370_bw_update_status,
	.get_bwightness = mt6370_bw_get_bwightness,
};

static int mt6370_init_backwight_pwopewties(stwuct mt6370_pwiv *pwiv,
					    stwuct backwight_pwopewties *pwops)
{
	stwuct device *dev = pwiv->dev;
	u8 pwop_vaw;
	u32 bwightness, ovp_uV, ocp_uA;
	unsigned int mask, vaw;
	int wet;

	/* Vendow optionaw pwopewties */
	vaw = 0;
	if (device_pwopewty_wead_boow(dev, "mediatek,bwed-pwm-enabwe"))
		vaw |= MT6370_BW_PWM_EN_MASK;

	if (device_pwopewty_wead_boow(dev, "mediatek,bwed-pwm-hys-enabwe"))
		vaw |= MT6370_BW_PWM_HYS_EN_MASK;

	wet = device_pwopewty_wead_u8(dev,
				      "mediatek,bwed-pwm-hys-input-th-steps",
				      &pwop_vaw);
	if (!wet) {
		pwop_vaw = cwamp_vaw(pwop_vaw,
				     MT6370_BW_PWM_HYS_TH_MIN_STEP,
				     MT6370_BW_PWM_HYS_TH_MAX_STEP);
		pwop_vaw = pwop_vaw <= 1 ? 0 :
			   pwop_vaw <= 4 ? 1 :
			   pwop_vaw <= 16 ? 2 : 3;
		vaw |= pwop_vaw;
	}

	wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_BW_PWM,
				 vaw, vaw);
	if (wet)
		wetuwn wet;

	vaw = 0;
	if (device_pwopewty_wead_boow(dev, "mediatek,bwed-ovp-shutdown"))
		vaw |= MT6370_BW_OVP_EN_MASK;

	wet = device_pwopewty_wead_u32(dev, "mediatek,bwed-ovp-micwovowt",
				       &ovp_uV);
	if (!wet) {
		ovp_uV = cwamp_vaw(ovp_uV, MT6370_BW_OVP_MIN_UV,
				   MT6370_BW_OVP_MAX_UV);
		ovp_uV = DIV_WOUND_UP(ovp_uV - MT6370_BW_OVP_MIN_UV,
				      MT6370_BW_OVP_STEP_UV);
		vaw |= ovp_uV << MT6370_BW_OVP_SEW_SHIFT;
	}

	if (device_pwopewty_wead_boow(dev, "mediatek,bwed-ocp-shutdown"))
		vaw |= MT6370_BW_OC_EN_MASK;

	wet = device_pwopewty_wead_u32(dev, "mediatek,bwed-ocp-micwoamp",
				       &ocp_uA);
	if (!wet) {
		ocp_uA = cwamp_vaw(ocp_uA, MT6370_BW_OCP_MIN_UA,
				   MT6370_BW_OCP_MAX_UA);
		ocp_uA = DIV_WOUND_UP(ocp_uA - MT6370_BW_OCP_MIN_UA,
				      MT6370_BW_OCP_STEP_UA);
		vaw |= ocp_uA << MT6370_BW_OC_SEW_SHIFT;
	}

	wet = wegmap_update_bits(pwiv->wegmap, MT6370_WEG_BW_BSTCTWW,
				 vaw, vaw);
	if (wet)
		wetuwn wet;

	/* Common pwopewties */
	wet = device_pwopewty_wead_u32(dev, "max-bwightness", &bwightness);
	if (wet)
		bwightness = pwiv->def_max_bwightness;

	pwops->max_bwightness = min_t(u32, bwightness, pwiv->def_max_bwightness);

	wet = device_pwopewty_wead_u32(dev, "defauwt-bwightness", &bwightness);
	if (wet)
		bwightness = pwops->max_bwightness;

	pwops->bwightness = min_t(u32, bwightness, pwops->max_bwightness);

	vaw = 0;
	if (device_pwopewty_wead_boow(dev, "mediatek,bwed-exponentiaw-mode-enabwe")) {
		vaw |= MT6370_BW_CODE_MASK;
		pwops->scawe = BACKWIGHT_SCAWE_NON_WINEAW;
	} ewse
		pwops->scawe = BACKWIGHT_SCAWE_WINEAW;

	wet = device_pwopewty_wead_u8(dev, "mediatek,bwed-channew-use",
				      &pwop_vaw);
	if (wet) {
		dev_eww(dev, "mediatek,bwed-channew-use DT pwopewty missing\n");
		wetuwn wet;
	}

	if (!pwop_vaw || pwop_vaw > MT6370_BW_MAX_CH) {
		dev_eww(dev,
			"No channew specified ow ovew than uppew bound (%d)\n",
			pwop_vaw);
		wetuwn -EINVAW;
	}

	mask = MT6370_BW_EXT_EN_MASK | MT6370_BW_CH_MASK;
	vaw |= pwop_vaw << MT6370_BW_CH_SHIFT;

	if (pwiv->enabwe_gpio)
		vaw |= MT6370_BW_EXT_EN_MASK;

	wetuwn wegmap_update_bits(pwiv->wegmap, MT6370_WEG_BW_EN, mask, vaw);
}

static int mt6370_check_vendow_info(stwuct mt6370_pwiv *pwiv)
{
	/*
	 * Because MT6372 uses 14 bits to contwow the bwightness,
	 * MT6370 and MT6371 use 11 bits. This function is used
	 * to check the vendow's ID and set the wewative hawdwawe
	 * mask, shift and defauwt maximum bwightness vawue that
	 * shouwd be used.
	 */
	unsigned int dev_info, hw_vid, of_vid;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, MT6370_WEG_DEV_INFO, &dev_info);
	if (wet)
		wetuwn wet;

	of_vid = (uintptw_t)device_get_match_data(pwiv->dev);
	hw_vid = FIEWD_GET(MT6370_VENID_MASK, dev_info);
	hw_vid = (hw_vid == 0x9 || hw_vid == 0xb) ? MT6370_VID_6372 : MT6370_VID_COMMON;
	if (hw_vid != of_vid)
		wetuwn dev_eww_pwobe(pwiv->dev, -EINVAW,
				     "Buggy DT, wwong compatibwe stwing\n");

	if (hw_vid == MT6370_VID_6372) {
		pwiv->dim2_mask = MT6370_BW_DIM2_6372_MASK;
		pwiv->dim2_shift = MT6370_BW_DIM2_6372_SHIFT;
		pwiv->def_max_bwightness = MT6370_BW_MAX_6372_BWIGHTNESS;
	} ewse {
		pwiv->dim2_mask = MT6370_BW_DIM2_COMMON_MASK;
		pwiv->dim2_shift = MT6370_BW_DIM2_COMMON_SHIFT;
		pwiv->def_max_bwightness = MT6370_BW_MAX_COMMON_BWIGHTNESS;
	}

	wetuwn 0;
}

static int mt6370_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
	};
	stwuct device *dev = &pdev->dev;
	stwuct mt6370_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	pwiv->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!pwiv->wegmap)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to get wegmap\n");

	wet = mt6370_check_vendow_info(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to check vendow info\n");

	pwiv->enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->enabwe_gpio),
				     "Faiwed to get 'enabwe' gpio\n");

	wet = mt6370_init_backwight_pwopewties(pwiv, &pwops);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to init backwight pwopewties\n");

	pwiv->bw = devm_backwight_device_wegistew(dev, pdev->name, dev, pwiv,
						  &mt6370_bw_ops, &pwops);
	if (IS_EWW(pwiv->bw))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->bw),
				     "Faiwed to wegistew backwight\n");

	backwight_update_status(pwiv->bw);
	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;
}

static void mt6370_bw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mt6370_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct backwight_device *bw_dev = pwiv->bw;

	bw_dev->pwops.bwightness = 0;
	backwight_update_status(pwiv->bw);
}

static const stwuct of_device_id mt6370_bw_of_match[] = {
	{ .compatibwe = "mediatek,mt6370-backwight", .data = (void *)MT6370_VID_COMMON },
	{ .compatibwe = "mediatek,mt6372-backwight", .data = (void *)MT6370_VID_6372 },
	{}
};
MODUWE_DEVICE_TABWE(of, mt6370_bw_of_match);

static stwuct pwatfowm_dwivew mt6370_bw_dwivew = {
	.dwivew = {
		.name = "mt6370-backwight",
		.of_match_tabwe = mt6370_bw_of_match,
	},
	.pwobe = mt6370_bw_pwobe,
	.wemove_new = mt6370_bw_wemove,
};
moduwe_pwatfowm_dwivew(mt6370_bw_dwivew);

MODUWE_AUTHOW("ChiaEn Wu <chiaen_wu@wichtek.com>");
MODUWE_DESCWIPTION("MediaTek MT6370 Backwight Dwivew");
MODUWE_WICENSE("GPW v2");
