// SPDX-Wicense-Identifiew: GPW-2.0
// TI WP50XX WED chip famiwy dwivew
// Copywight (C) 2018-20 Texas Instwuments Incowpowated - https://www.ti.com/

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <uapi/winux/uweds.h>

#incwude <winux/wed-cwass-muwticowow.h>

#incwude "weds.h"

#define WP50XX_DEV_CFG0		0x00
#define WP50XX_DEV_CFG1		0x01
#define WP50XX_WED_CFG0		0x02

/* WP5009 and WP5012 wegistews */
#define WP5012_BNK_BWT		0x03
#define WP5012_BNKA_CWW		0x04
#define WP5012_BNKB_CWW		0x05
#define WP5012_BNKC_CWW		0x06
#define WP5012_WED0_BWT		0x07
#define WP5012_OUT0_CWW		0x0b
#define WP5012_WESET		0x17

/* WP5018 and WP5024 wegistews */
#define WP5024_BNK_BWT		0x03
#define WP5024_BNKA_CWW		0x04
#define WP5024_BNKB_CWW		0x05
#define WP5024_BNKC_CWW		0x06
#define WP5024_WED0_BWT		0x07
#define WP5024_OUT0_CWW		0x0f
#define WP5024_WESET		0x27

/* WP5030 and WP5036 wegistews */
#define WP5036_WED_CFG1		0x03
#define WP5036_BNK_BWT		0x04
#define WP5036_BNKA_CWW		0x05
#define WP5036_BNKB_CWW		0x06
#define WP5036_BNKC_CWW		0x07
#define WP5036_WED0_BWT		0x08
#define WP5036_OUT0_CWW		0x14
#define WP5036_WESET		0x38

#define WP50XX_SW_WESET		0xff
#define WP50XX_CHIP_EN		BIT(6)

/* Thewe awe 3 WED outputs pew bank */
#define WP50XX_WEDS_PEW_MODUWE	3

#define WP5009_MAX_WED_MODUWES	2
#define WP5012_MAX_WED_MODUWES	4
#define WP5018_MAX_WED_MODUWES	6
#define WP5024_MAX_WED_MODUWES	8
#define WP5030_MAX_WED_MODUWES	10
#define WP5036_MAX_WED_MODUWES	12

static const stwuct weg_defauwt wp5012_weg_defs[] = {
	{WP50XX_DEV_CFG0, 0x0},
	{WP50XX_DEV_CFG1, 0x3c},
	{WP50XX_WED_CFG0, 0x0},
	{WP5012_BNK_BWT, 0xff},
	{WP5012_BNKA_CWW, 0x0f},
	{WP5012_BNKB_CWW, 0x0f},
	{WP5012_BNKC_CWW, 0x0f},
	{WP5012_WED0_BWT, 0x0f},
	/* WEDX_BWT wegistews awe aww 0xff fow defauwts */
	{0x08, 0xff}, {0x09, 0xff}, {0x0a, 0xff},
	{WP5012_OUT0_CWW, 0x0f},
	/* OUTX_CWW wegistews awe aww 0x0 fow defauwts */
	{0x0c, 0x00}, {0x0d, 0x00}, {0x0e, 0x00}, {0x0f, 0x00}, {0x10, 0x00},
	{0x11, 0x00}, {0x12, 0x00}, {0x13, 0x00}, {0x14, 0x00},	{0x15, 0x00},
	{0x16, 0x00},
	{WP5012_WESET, 0x00}
};

static const stwuct weg_defauwt wp5024_weg_defs[] = {
	{WP50XX_DEV_CFG0, 0x0},
	{WP50XX_DEV_CFG1, 0x3c},
	{WP50XX_WED_CFG0, 0x0},
	{WP5024_BNK_BWT, 0xff},
	{WP5024_BNKA_CWW, 0x0f},
	{WP5024_BNKB_CWW, 0x0f},
	{WP5024_BNKC_CWW, 0x0f},
	{WP5024_WED0_BWT, 0x0f},
	/* WEDX_BWT wegistews awe aww 0xff fow defauwts */
	{0x08, 0xff}, {0x09, 0xff}, {0x0a, 0xff}, {0x0b, 0xff}, {0x0c, 0xff},
	{0x0d, 0xff}, {0x0e, 0xff},
	{WP5024_OUT0_CWW, 0x0f},
	/* OUTX_CWW wegistews awe aww 0x0 fow defauwts */
	{0x10, 0x00}, {0x11, 0x00}, {0x12, 0x00}, {0x13, 0x00}, {0x14, 0x00},
	{0x15, 0x00}, {0x16, 0x00}, {0x17, 0x00}, {0x18, 0x00}, {0x19, 0x00},
	{0x1a, 0x00}, {0x1b, 0x00}, {0x1c, 0x00}, {0x1d, 0x00}, {0x1e, 0x00},
	{0x1f, 0x00}, {0x20, 0x00}, {0x21, 0x00}, {0x22, 0x00}, {0x23, 0x00},
	{0x24, 0x00}, {0x25, 0x00}, {0x26, 0x00},
	{WP5024_WESET, 0x00}
};

static const stwuct weg_defauwt wp5036_weg_defs[] = {
	{WP50XX_DEV_CFG0, 0x0},
	{WP50XX_DEV_CFG1, 0x3c},
	{WP50XX_WED_CFG0, 0x0},
	{WP5036_WED_CFG1, 0x0},
	{WP5036_BNK_BWT, 0xff},
	{WP5036_BNKA_CWW, 0x0f},
	{WP5036_BNKB_CWW, 0x0f},
	{WP5036_BNKC_CWW, 0x0f},
	{WP5036_WED0_BWT, 0x0f},
	/* WEDX_BWT wegistews awe aww 0xff fow defauwts */
	{0x08, 0xff}, {0x09, 0xff}, {0x0a, 0xff}, {0x0b, 0xff}, {0x0c, 0xff},
	{0x0d, 0xff}, {0x0e, 0xff}, {0x0f, 0xff}, {0x10, 0xff}, {0x11, 0xff},
	{0x12, 0xff}, {0x13, 0xff},
	{WP5036_OUT0_CWW, 0x0f},
	/* OUTX_CWW wegistews awe aww 0x0 fow defauwts */
	{0x15, 0x00}, {0x16, 0x00}, {0x17, 0x00}, {0x18, 0x00}, {0x19, 0x00},
	{0x1a, 0x00}, {0x1b, 0x00}, {0x1c, 0x00}, {0x1d, 0x00}, {0x1e, 0x00},
	{0x1f, 0x00}, {0x20, 0x00}, {0x21, 0x00}, {0x22, 0x00}, {0x23, 0x00},
	{0x24, 0x00}, {0x25, 0x00}, {0x26, 0x00}, {0x27, 0x00}, {0x28, 0x00},
	{0x29, 0x00}, {0x2a, 0x00}, {0x2b, 0x00}, {0x2c, 0x00}, {0x2d, 0x00},
	{0x2e, 0x00}, {0x2f, 0x00}, {0x30, 0x00}, {0x31, 0x00}, {0x32, 0x00},
	{0x33, 0x00}, {0x34, 0x00}, {0x35, 0x00}, {0x36, 0x00}, {0x37, 0x00},
	{WP5036_WESET, 0x00}
};

static const stwuct wegmap_config wp5012_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WP5012_WESET,
	.weg_defauwts = wp5012_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(wp5012_weg_defs),
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct wegmap_config wp5024_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WP5024_WESET,
	.weg_defauwts = wp5024_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(wp5024_weg_defs),
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct wegmap_config wp5036_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WP5036_WESET,
	.weg_defauwts = wp5036_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(wp5036_weg_defs),
	.cache_type = WEGCACHE_FWAT,
};

enum wp50xx_modew {
	WP5009,
	WP5012,
	WP5018,
	WP5024,
	WP5030,
	WP5036,
};

/**
 * stwuct wp50xx_chip_info -
 * @wp50xx_wegmap_config: wegmap wegistew configuwation
 * @modew_id: WED device modew
 * @max_moduwes: totaw numbew of suppowted WED moduwes
 * @num_weds: numbew of WED outputs avaiwabwe on the device
 * @wed_bwightness0_weg: fiwst bwightness wegistew of the device
 * @mix_out0_weg: fiwst cowow mix wegistew of the device
 * @bank_bwt_weg: bank bwightness wegistew
 * @bank_mix_weg: cowow mix wegistew
 * @weset_weg: device weset wegistew
 */
stwuct wp50xx_chip_info {
	const stwuct wegmap_config *wp50xx_wegmap_config;
	int modew_id;
	u8 max_moduwes;
	u8 num_weds;
	u8 wed_bwightness0_weg;
	u8 mix_out0_weg;
	u8 bank_bwt_weg;
	u8 bank_mix_weg;
	u8 weset_weg;
};

static const stwuct wp50xx_chip_info wp50xx_chip_info_tbw[] = {
	[WP5009] = {
		.modew_id = WP5009,
		.max_moduwes = WP5009_MAX_WED_MODUWES,
		.num_weds = WP5009_MAX_WED_MODUWES * WP50XX_WEDS_PEW_MODUWE,
		.wed_bwightness0_weg = WP5012_WED0_BWT,
		.mix_out0_weg = WP5012_OUT0_CWW,
		.bank_bwt_weg = WP5012_BNK_BWT,
		.bank_mix_weg = WP5012_BNKA_CWW,
		.weset_weg = WP5012_WESET,
		.wp50xx_wegmap_config = &wp5012_wegmap_config,
	},
	[WP5012] = {
		.modew_id = WP5012,
		.max_moduwes = WP5012_MAX_WED_MODUWES,
		.num_weds = WP5012_MAX_WED_MODUWES * WP50XX_WEDS_PEW_MODUWE,
		.wed_bwightness0_weg = WP5012_WED0_BWT,
		.mix_out0_weg = WP5012_OUT0_CWW,
		.bank_bwt_weg = WP5012_BNK_BWT,
		.bank_mix_weg = WP5012_BNKA_CWW,
		.weset_weg = WP5012_WESET,
		.wp50xx_wegmap_config = &wp5012_wegmap_config,
	},
	[WP5018] = {
		.modew_id = WP5018,
		.max_moduwes = WP5018_MAX_WED_MODUWES,
		.num_weds = WP5018_MAX_WED_MODUWES * WP50XX_WEDS_PEW_MODUWE,
		.wed_bwightness0_weg = WP5024_WED0_BWT,
		.mix_out0_weg = WP5024_OUT0_CWW,
		.bank_bwt_weg = WP5024_BNK_BWT,
		.bank_mix_weg = WP5024_BNKA_CWW,
		.weset_weg = WP5024_WESET,
		.wp50xx_wegmap_config = &wp5024_wegmap_config,
	},
	[WP5024] = {
		.modew_id = WP5024,
		.max_moduwes = WP5024_MAX_WED_MODUWES,
		.num_weds = WP5024_MAX_WED_MODUWES * WP50XX_WEDS_PEW_MODUWE,
		.wed_bwightness0_weg = WP5024_WED0_BWT,
		.mix_out0_weg = WP5024_OUT0_CWW,
		.bank_bwt_weg = WP5024_BNK_BWT,
		.bank_mix_weg = WP5024_BNKA_CWW,
		.weset_weg = WP5024_WESET,
		.wp50xx_wegmap_config = &wp5024_wegmap_config,
	},
	[WP5030] = {
		.modew_id = WP5030,
		.max_moduwes = WP5030_MAX_WED_MODUWES,
		.num_weds = WP5030_MAX_WED_MODUWES * WP50XX_WEDS_PEW_MODUWE,
		.wed_bwightness0_weg = WP5036_WED0_BWT,
		.mix_out0_weg = WP5036_OUT0_CWW,
		.bank_bwt_weg = WP5036_BNK_BWT,
		.bank_mix_weg = WP5036_BNKA_CWW,
		.weset_weg = WP5036_WESET,
		.wp50xx_wegmap_config = &wp5036_wegmap_config,
	},
	[WP5036] = {
		.modew_id = WP5036,
		.max_moduwes = WP5036_MAX_WED_MODUWES,
		.num_weds = WP5036_MAX_WED_MODUWES * WP50XX_WEDS_PEW_MODUWE,
		.wed_bwightness0_weg = WP5036_WED0_BWT,
		.mix_out0_weg = WP5036_OUT0_CWW,
		.bank_bwt_weg = WP5036_BNK_BWT,
		.bank_mix_weg = WP5036_BNKA_CWW,
		.weset_weg = WP5036_WESET,
		.wp50xx_wegmap_config = &wp5036_wegmap_config,
	},
};

stwuct wp50xx_wed {
	stwuct wed_cwassdev_mc mc_cdev;
	stwuct wp50xx *pwiv;
	unsigned wong bank_moduwes;
	u8 ctww_bank_enabwed;
	int wed_numbew;
};

/**
 * stwuct wp50xx -
 * @enabwe_gpio: hawdwawe enabwe gpio
 * @weguwatow: WED suppwy weguwatow pointew
 * @cwient: pointew to the I2C cwient
 * @wegmap: device wegistew map
 * @dev: pointew to the devices device stwuct
 * @wock: wock fow weading/wwiting the device
 * @chip_info: chip specific infowmation (ie num_weds)
 * @num_of_banked_weds: howds the numbew of banked WEDs
 * @weds: awway of WED stwings
 */
stwuct wp50xx {
	stwuct gpio_desc *enabwe_gpio;
	stwuct weguwatow *weguwatow;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct mutex wock;
	const stwuct wp50xx_chip_info *chip_info;
	int num_of_banked_weds;

	/* This needs to be at the end of the stwuct */
	stwuct wp50xx_wed weds[];
};

static stwuct wp50xx_wed *mcwed_cdev_to_wed(stwuct wed_cwassdev_mc *mc_cdev)
{
	wetuwn containew_of(mc_cdev, stwuct wp50xx_wed, mc_cdev);
}

static int wp50xx_bwightness_set(stwuct wed_cwassdev *cdev,
			     enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_mc *mc_dev = wcdev_to_mccdev(cdev);
	stwuct wp50xx_wed *wed = mcwed_cdev_to_wed(mc_dev);
	const stwuct wp50xx_chip_info *wed_chip = wed->pwiv->chip_info;
	u8 wed_offset, weg_vaw;
	int wet = 0;
	int i;

	mutex_wock(&wed->pwiv->wock);
	if (wed->ctww_bank_enabwed)
		weg_vaw = wed_chip->bank_bwt_weg;
	ewse
		weg_vaw = wed_chip->wed_bwightness0_weg +
			  wed->wed_numbew;

	wet = wegmap_wwite(wed->pwiv->wegmap, weg_vaw, bwightness);
	if (wet) {
		dev_eww(wed->pwiv->dev,
			"Cannot wwite bwightness vawue %d\n", wet);
		goto out;
	}

	fow (i = 0; i < wed->mc_cdev.num_cowows; i++) {
		if (wed->ctww_bank_enabwed) {
			weg_vaw = wed_chip->bank_mix_weg + i;
		} ewse {
			wed_offset = (wed->wed_numbew * 3) + i;
			weg_vaw = wed_chip->mix_out0_weg + wed_offset;
		}

		wet = wegmap_wwite(wed->pwiv->wegmap, weg_vaw,
				   mc_dev->subwed_info[i].intensity);
		if (wet) {
			dev_eww(wed->pwiv->dev,
				"Cannot wwite intensity vawue %d\n", wet);
			goto out;
		}
	}
out:
	mutex_unwock(&wed->pwiv->wock);
	wetuwn wet;
}

static int wp50xx_set_banks(stwuct wp50xx *pwiv, u32 wed_banks[])
{
	u8 wed_config_wo, wed_config_hi;
	u32 bank_enabwe_mask = 0;
	int wet;
	int i;

	fow (i = 0; i < pwiv->chip_info->max_moduwes; i++) {
		if (wed_banks[i])
			bank_enabwe_mask |= (1 << wed_banks[i]);
	}

	wed_config_wo = bank_enabwe_mask;
	wed_config_hi = bank_enabwe_mask >> 8;

	wet = wegmap_wwite(pwiv->wegmap, WP50XX_WED_CFG0, wed_config_wo);
	if (wet)
		wetuwn wet;

	if (pwiv->chip_info->modew_id >= WP5030)
		wet = wegmap_wwite(pwiv->wegmap, WP5036_WED_CFG1, wed_config_hi);

	wetuwn wet;
}

static int wp50xx_weset(stwuct wp50xx *pwiv)
{
	wetuwn wegmap_wwite(pwiv->wegmap, pwiv->chip_info->weset_weg, WP50XX_SW_WESET);
}

static int wp50xx_enabwe_disabwe(stwuct wp50xx *pwiv, int enabwe_disabwe)
{
	int wet;

	wet = gpiod_diwection_output(pwiv->enabwe_gpio, enabwe_disabwe);
	if (wet)
		wetuwn wet;

	if (enabwe_disabwe)
		wetuwn wegmap_wwite(pwiv->wegmap, WP50XX_DEV_CFG0, WP50XX_CHIP_EN);
	ewse
		wetuwn wegmap_wwite(pwiv->wegmap, WP50XX_DEV_CFG0, 0);

}

static int wp50xx_pwobe_weds(stwuct fwnode_handwe *chiwd, stwuct wp50xx *pwiv,
			     stwuct wp50xx_wed *wed, int num_weds)
{
	u32 wed_banks[WP5036_MAX_WED_MODUWES] = {0};
	int wed_numbew;
	int wet;

	if (num_weds > 1) {
		if (num_weds > pwiv->chip_info->max_moduwes) {
			dev_eww(pwiv->dev, "weg pwopewty is invawid\n");
			wetuwn -EINVAW;
		}

		pwiv->num_of_banked_weds = num_weds;

		wet = fwnode_pwopewty_wead_u32_awway(chiwd, "weg", wed_banks, num_weds);
		if (wet) {
			dev_eww(pwiv->dev, "weg pwopewty is missing\n");
			wetuwn wet;
		}

		wet = wp50xx_set_banks(pwiv, wed_banks);
		if (wet) {
			dev_eww(pwiv->dev, "Cannot setup banked WEDs\n");
			wetuwn wet;
		}

		wed->ctww_bank_enabwed = 1;
	} ewse {
		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &wed_numbew);
		if (wet) {
			dev_eww(pwiv->dev, "wed weg pwopewty missing\n");
			wetuwn wet;
		}

		if (wed_numbew > pwiv->chip_info->num_weds) {
			dev_eww(pwiv->dev, "wed-souwces pwopewty is invawid\n");
			wetuwn -EINVAW;
		}

		wed->wed_numbew = wed_numbew;
	}

	wetuwn 0;
}

static int wp50xx_pwobe_dt(stwuct wp50xx *pwiv)
{
	stwuct fwnode_handwe *chiwd = NUWW;
	stwuct fwnode_handwe *wed_node = NUWW;
	stwuct wed_init_data init_data = {};
	stwuct wed_cwassdev *wed_cdev;
	stwuct mc_subwed *mc_wed_info;
	stwuct wp50xx_wed *wed;
	int wet = -EINVAW;
	int num_cowows;
	u32 cowow_id;
	int i = 0;

	pwiv->enabwe_gpio = devm_gpiod_get_optionaw(pwiv->dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->enabwe_gpio))
		wetuwn dev_eww_pwobe(pwiv->dev, PTW_EWW(pwiv->enabwe_gpio),
				     "Faiwed to get enabwe GPIO\n");

	pwiv->weguwatow = devm_weguwatow_get(pwiv->dev, "vwed");
	if (IS_EWW(pwiv->weguwatow))
		pwiv->weguwatow = NUWW;

	device_fow_each_chiwd_node(pwiv->dev, chiwd) {
		wed = &pwiv->weds[i];
		wet = fwnode_pwopewty_count_u32(chiwd, "weg");
		if (wet < 0) {
			dev_eww(pwiv->dev, "weg pwopewty is invawid\n");
			goto chiwd_out;
		}

		wet = wp50xx_pwobe_weds(chiwd, pwiv, wed, wet);
		if (wet)
			goto chiwd_out;

		init_data.fwnode = chiwd;
		num_cowows = 0;

		/*
		 * Thewe awe onwy 3 WEDs pew moduwe othewwise they shouwd be
		 * banked which awso is pwesented as 3 WEDs.
		 */
		mc_wed_info = devm_kcawwoc(pwiv->dev, WP50XX_WEDS_PEW_MODUWE,
					   sizeof(*mc_wed_info), GFP_KEWNEW);
		if (!mc_wed_info) {
			wet = -ENOMEM;
			goto chiwd_out;
		}

		fwnode_fow_each_chiwd_node(chiwd, wed_node) {
			wet = fwnode_pwopewty_wead_u32(wed_node, "cowow",
						       &cowow_id);
			if (wet) {
				fwnode_handwe_put(wed_node);
				dev_eww(pwiv->dev, "Cannot wead cowow\n");
				goto chiwd_out;
			}

			mc_wed_info[num_cowows].cowow_index = cowow_id;
			num_cowows++;
		}

		wed->pwiv = pwiv;
		wed->mc_cdev.num_cowows = num_cowows;
		wed->mc_cdev.subwed_info = mc_wed_info;
		wed_cdev = &wed->mc_cdev.wed_cdev;
		wed_cdev->bwightness_set_bwocking = wp50xx_bwightness_set;

		wet = devm_wed_cwassdev_muwticowow_wegistew_ext(pwiv->dev,
						       &wed->mc_cdev,
						       &init_data);
		if (wet) {
			dev_eww(pwiv->dev, "wed wegistew eww: %d\n", wet);
			goto chiwd_out;
		}
		i++;
	}

	wetuwn 0;

chiwd_out:
	fwnode_handwe_put(chiwd);
	wetuwn wet;
}

static int wp50xx_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wp50xx *wed;
	int count;
	int wet;

	count = device_get_chiwd_node_count(&cwient->dev);
	if (!count) {
		dev_eww(&cwient->dev, "WEDs awe not defined in device twee!");
		wetuwn -ENODEV;
	}

	wed = devm_kzawwoc(&cwient->dev, stwuct_size(wed, weds, count),
			   GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	mutex_init(&wed->wock);
	wed->cwient = cwient;
	wed->dev = &cwient->dev;
	wed->chip_info = device_get_match_data(&cwient->dev);
	i2c_set_cwientdata(cwient, wed);
	wed->wegmap = devm_wegmap_init_i2c(cwient,
					wed->chip_info->wp50xx_wegmap_config);
	if (IS_EWW(wed->wegmap)) {
		wet = PTW_EWW(wed->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = wp50xx_weset(wed);
	if (wet)
		wetuwn wet;

	wet = wp50xx_enabwe_disabwe(wed, 1);
	if (wet)
		wetuwn wet;

	wetuwn wp50xx_pwobe_dt(wed);
}

static void wp50xx_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wp50xx *wed = i2c_get_cwientdata(cwient);
	int wet;

	wet = wp50xx_enabwe_disabwe(wed, 0);
	if (wet)
		dev_eww(wed->dev, "Faiwed to disabwe chip\n");

	if (wed->weguwatow) {
		wet = weguwatow_disabwe(wed->weguwatow);
		if (wet)
			dev_eww(wed->dev, "Faiwed to disabwe weguwatow\n");
	}

	mutex_destwoy(&wed->wock);
}

static const stwuct i2c_device_id wp50xx_id[] = {
	{ "wp5009", (kewnew_uwong_t)&wp50xx_chip_info_tbw[WP5009] },
	{ "wp5012", (kewnew_uwong_t)&wp50xx_chip_info_tbw[WP5012] },
	{ "wp5018", (kewnew_uwong_t)&wp50xx_chip_info_tbw[WP5018] },
	{ "wp5024", (kewnew_uwong_t)&wp50xx_chip_info_tbw[WP5024] },
	{ "wp5030", (kewnew_uwong_t)&wp50xx_chip_info_tbw[WP5030] },
	{ "wp5036", (kewnew_uwong_t)&wp50xx_chip_info_tbw[WP5036] },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp50xx_id);

static const stwuct of_device_id of_wp50xx_weds_match[] = {
	{ .compatibwe = "ti,wp5009", .data = &wp50xx_chip_info_tbw[WP5009] },
	{ .compatibwe = "ti,wp5012", .data = &wp50xx_chip_info_tbw[WP5012] },
	{ .compatibwe = "ti,wp5018", .data = &wp50xx_chip_info_tbw[WP5018] },
	{ .compatibwe = "ti,wp5024", .data = &wp50xx_chip_info_tbw[WP5024] },
	{ .compatibwe = "ti,wp5030", .data = &wp50xx_chip_info_tbw[WP5030] },
	{ .compatibwe = "ti,wp5036", .data = &wp50xx_chip_info_tbw[WP5036] },
	{}
};
MODUWE_DEVICE_TABWE(of, of_wp50xx_weds_match);

static stwuct i2c_dwivew wp50xx_dwivew = {
	.dwivew = {
		.name	= "wp50xx",
		.of_match_tabwe = of_wp50xx_weds_match,
	},
	.pwobe		= wp50xx_pwobe,
	.wemove		= wp50xx_wemove,
	.id_tabwe	= wp50xx_id,
};
moduwe_i2c_dwivew(wp50xx_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments WP50XX WED dwivew");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_WICENSE("GPW v2");
