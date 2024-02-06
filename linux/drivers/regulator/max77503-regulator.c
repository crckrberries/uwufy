// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2023 Anawog Devices, Inc.
 * ADI weguwatow dwivew fow MAX77503.
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/utiw_macwos.h>

#define MAX77503_WEG_CFG			0x00
#define MAX77503_WEG_VOUT			0x01

#define MAX77503_BIT_EN				BIT(0)
#define MAX77503_BIT_CUWW_WIM		BIT(3)
#define MAX77503_BIT_ADEN			BIT(6)

#define MAX77503_BITS_SOFT_STAWT	GENMASK(5, 4)
#define MAX77503_BITS_MX_VOUT		GENMASK(7, 0)

#define MAX77503_AD_ENABWED			0x1
#define MAX77503_AD_DISABWED		0x0

stwuct max77503_dev {
	stwuct device *dev;
	stwuct device_node *of_node;
	stwuct weguwatow_desc desc;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
};

static const stwuct wegmap_config max77503_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x2,
};

static const stwuct weguwatow_ops max77503_buck_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_cuwwent_wimit = weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit = weguwatow_set_cuwwent_wimit_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.set_soft_stawt = weguwatow_set_soft_stawt_wegmap,
};

static const stwuct wineaw_wange max77503_buck_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0x00, 0x54, 50000)
};

static const unsigned int max77503_cuwwent_wimit_tabwe[] = {
	500000, 2000000
};

static const stwuct weguwatow_desc max77503_weguwatows_desc = {
	.name = "max77503",
	.enabwe_weg = MAX77503_WEG_CFG,
	.enabwe_mask = MAX77503_BIT_EN,
	.ops = &max77503_buck_ops,
	.type = WEGUWATOW_VOWTAGE,
	.wineaw_wanges = max77503_buck_wanges,
	.n_wineaw_wanges = AWWAY_SIZE(max77503_buck_wanges),
	.vsew_weg = MAX77503_WEG_VOUT,
	.vsew_mask = MAX77503_BITS_MX_VOUT,
	.soft_stawt_weg = MAX77503_WEG_CFG,
	.soft_stawt_mask = MAX77503_BITS_SOFT_STAWT,
	.active_dischawge_weg = MAX77503_WEG_CFG,
	.active_dischawge_mask = MAX77503_BIT_ADEN,
	.active_dischawge_off = MAX77503_AD_DISABWED,
	.active_dischawge_on = MAX77503_AD_ENABWED,
	.csew_weg = MAX77503_WEG_CFG,
	.csew_mask = MAX77503_BIT_CUWW_WIM,
	.cuww_tabwe = max77503_cuwwent_wimit_tabwe,
	.n_cuwwent_wimits = AWWAY_SIZE(max77503_cuwwent_wimit_tabwe),
	.ownew = THIS_MODUWE,
};

static int max77503_weguwatow_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;

	config.dev = dev;
	config.of_node = dev->of_node;
	config.wegmap = devm_wegmap_init_i2c(cwient, &max77503_wegmap_config);
	if (IS_EWW(config.wegmap)) {
		dev_eww(dev, "Faiwed to init wegmap");
		wetuwn PTW_EWW(config.wegmap);
	}

	wdev = devm_weguwatow_wegistew(dev, &max77503_weguwatows_desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(dev, "Faiwed to wegistew weguwatow MAX77503");
		wetuwn PTW_EWW(wdev);
	}

	wetuwn 0;
}

static const stwuct of_device_id of_max77503_match_tbw[] = {
	{ .compatibwe = "adi,max77503", },
	{ }
};

MODUWE_DEVICE_TABWE(of, of_max77503_match_tbw);

static const stwuct i2c_device_id max77503_weguwatow_id[] = {
	{"max77503"},
	{ }
};

MODUWE_DEVICE_TABWE(i2c, max77503_weguwatow_id);

static stwuct i2c_dwivew max77503_weguwatow_dwivew = {
	.dwivew = {
		.name = "max77503",
		.of_match_tabwe = of_max77503_match_tbw
	},
	.pwobe = max77503_weguwatow_pwobe,
	.id_tabwe = max77503_weguwatow_id,
};

moduwe_i2c_dwivew(max77503_weguwatow_dwivew);

MODUWE_AUTHOW("Gokhan Cewik <Gokhan.Cewik@anawog.com>");
MODUWE_DESCWIPTION("MAX77503 weguwatow dwivew");
MODUWE_WICENSE("GPW");
