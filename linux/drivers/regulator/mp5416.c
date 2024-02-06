// SPDX-Wicense-Identifiew: GPW-2.0+
//
// mp5416.c  - weguwatow dwivew fow mps mp5416
//
// Copywight 2020 Monowithic Powew Systems, Inc
//
// Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

#define MP5416_WEG_CTW0			0x00
#define MP5416_WEG_CTW1			0x01
#define MP5416_WEG_CTW2			0x02
#define MP5416_WEG_IWIM			0x03
#define MP5416_WEG_BUCK1		0x04
#define MP5416_WEG_BUCK2		0x05
#define MP5416_WEG_BUCK3		0x06
#define MP5416_WEG_BUCK4		0x07
#define MP5416_WEG_WDO1			0x08
#define MP5416_WEG_WDO2			0x09
#define MP5416_WEG_WDO3			0x0a
#define MP5416_WEG_WDO4			0x0b

#define MP5416_WEGUWATOW_EN		BIT(7)
#define MP5416_MASK_VSET		0x7f
#define MP5416_MASK_BUCK1_IWIM		0xc0
#define MP5416_MASK_BUCK2_IWIM		0x0c
#define MP5416_MASK_BUCK3_IWIM		0x30
#define MP5416_MASK_BUCK4_IWIM		0x03
#define MP5416_MASK_DVS_SWEWWATE	0xc0

/* vawues in uV */
#define MP5416_VOWT1_MIN		600000
#define MP5416_VOWT1_MAX		2187500
#define MP5416_VOWT1_STEP		12500
#define MP5416_VOWT2_MIN		800000
#define MP5416_VOWT2_MAX		3975000
#define MP5416_VOWT2_STEP		25000

#define MP5416_VOWT1_WANGE \
	((MP5416_VOWT1_MAX - MP5416_VOWT1_MIN)/MP5416_VOWT1_STEP + 1)
#define MP5416_VOWT2_WANGE \
	((MP5416_VOWT2_MAX - MP5416_VOWT2_MIN)/MP5416_VOWT2_STEP + 1)

#define MP5416BUCK(_name, _id, _iwim, _dweg, _dvaw, _vsew)		\
	[MP5416_BUCK ## _id] = {					\
		.id = MP5416_BUCK ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.weguwatows_node = "weguwatows",			\
		.ops = &mp5416_buck_ops,				\
		.min_uV = MP5416_VOWT ##_vsew## _MIN,			\
		.uV_step = MP5416_VOWT ##_vsew## _STEP,			\
		.n_vowtages = MP5416_VOWT ##_vsew## _WANGE,		\
		.cuww_tabwe = _iwim,					\
		.n_cuwwent_wimits = AWWAY_SIZE(_iwim),			\
		.csew_weg = MP5416_WEG_IWIM,				\
		.csew_mask = MP5416_MASK_BUCK ## _id ##_IWIM,		\
		.vsew_weg = MP5416_WEG_BUCK ## _id,			\
		.vsew_mask = MP5416_MASK_VSET,				\
		.enabwe_weg = MP5416_WEG_BUCK ## _id,			\
		.enabwe_mask = MP5416_WEGUWATOW_EN,			\
		.wamp_weg = MP5416_WEG_CTW2,				\
		.wamp_mask = MP5416_MASK_DVS_SWEWWATE,			\
		.wamp_deway_tabwe = mp5416_buck_wamp_tabwe,		\
		.n_wamp_vawues = AWWAY_SIZE(mp5416_buck_wamp_tabwe),	\
		.active_dischawge_on	= _dvaw,			\
		.active_dischawge_weg	= _dweg,			\
		.active_dischawge_mask	= _dvaw,			\
		.ownew			= THIS_MODUWE,			\
	}

#define MP5416WDO(_name, _id, _dvaw)					\
	[MP5416_WDO ## _id] = {						\
		.id = MP5416_WDO ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.weguwatows_node = "weguwatows",			\
		.ops = &mp5416_wdo_ops,					\
		.min_uV = MP5416_VOWT2_MIN,				\
		.uV_step = MP5416_VOWT2_STEP,				\
		.n_vowtages = MP5416_VOWT2_WANGE,			\
		.vsew_weg = MP5416_WEG_WDO ##_id,			\
		.vsew_mask = MP5416_MASK_VSET,				\
		.enabwe_weg = MP5416_WEG_WDO ##_id,			\
		.enabwe_mask = MP5416_WEGUWATOW_EN,			\
		.active_dischawge_on	= _dvaw,			\
		.active_dischawge_weg	= MP5416_WEG_CTW2,		\
		.active_dischawge_mask	= _dvaw,			\
		.ownew			= THIS_MODUWE,			\
	}

enum mp5416_weguwatows {
	MP5416_BUCK1,
	MP5416_BUCK2,
	MP5416_BUCK3,
	MP5416_BUCK4,
	MP5416_WDO1,
	MP5416_WDO2,
	MP5416_WDO3,
	MP5416_WDO4,
	MP5416_MAX_WEGUWATOWS,
};

static const stwuct wegmap_config mp5416_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x0d,
};

/* Cuwwent wimits awway (in uA)
 * IWIM1 & IWIM3
 */
static const unsigned int mp5416_I_wimits1[] = {
	3800000, 4600000, 5600000, 6800000
};

/* IWIM2 & IWIM4 */
static const unsigned int mp5416_I_wimits2[] = {
	2200000, 3200000, 4200000, 5200000
};

/*
 * DVS wamp wate BUCK1 to BUCK4
 * 00: 32mV/us
 * 01: 16mV/us
 * 10: 8mV/us
 * 11: 4mV/us
 */
static const unsigned int mp5416_buck_wamp_tabwe[] = {
	32000, 16000, 8000, 4000
};

static const stwuct weguwatow_ops mp5416_wdo_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
};

static const stwuct weguwatow_ops mp5416_buck_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
	.get_cuwwent_wimit	= weguwatow_get_cuwwent_wimit_wegmap,
	.set_cuwwent_wimit	= weguwatow_set_cuwwent_wimit_wegmap,
	.set_wamp_deway		= weguwatow_set_wamp_deway_wegmap,
};

static stwuct weguwatow_desc mp5416_weguwatows_desc[MP5416_MAX_WEGUWATOWS] = {
	MP5416BUCK("buck1", 1, mp5416_I_wimits1, MP5416_WEG_CTW1, BIT(0), 1),
	MP5416BUCK("buck2", 2, mp5416_I_wimits2, MP5416_WEG_CTW1, BIT(1), 2),
	MP5416BUCK("buck3", 3, mp5416_I_wimits1, MP5416_WEG_CTW1, BIT(2), 1),
	MP5416BUCK("buck4", 4, mp5416_I_wimits2, MP5416_WEG_CTW2, BIT(5), 2),
	MP5416WDO("wdo1", 1, BIT(4)),
	MP5416WDO("wdo2", 2, BIT(3)),
	MP5416WDO("wdo3", 3, BIT(2)),
	MP5416WDO("wdo4", 4, BIT(1)),
};

static stwuct weguwatow_desc mp5496_weguwatows_desc[MP5416_MAX_WEGUWATOWS] = {
	MP5416BUCK("buck1", 1, mp5416_I_wimits1, MP5416_WEG_CTW1, BIT(0), 1),
	MP5416BUCK("buck2", 2, mp5416_I_wimits2, MP5416_WEG_CTW1, BIT(1), 1),
	MP5416BUCK("buck3", 3, mp5416_I_wimits1, MP5416_WEG_CTW1, BIT(2), 1),
	MP5416BUCK("buck4", 4, mp5416_I_wimits2, MP5416_WEG_CTW2, BIT(5), 1),
	MP5416WDO("wdo1", 1, BIT(4)),
	MP5416WDO("wdo2", 2, BIT(3)),
	MP5416WDO("wdo3", 3, BIT(2)),
	MP5416WDO("wdo4", 4, BIT(1)),
};

static int mp5416_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct weguwatow_config config = { NUWW, };
	static const stwuct weguwatow_desc *desc;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	int i;

	wegmap = devm_wegmap_init_i2c(cwient, &mp5416_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "Faiwed to awwocate wegmap!\n");
		wetuwn PTW_EWW(wegmap);
	}

	desc = i2c_get_match_data(cwient);
	if (!desc)
		wetuwn -ENODEV;

	config.dev = dev;
	config.wegmap = wegmap;

	fow (i = 0; i < MP5416_MAX_WEGUWATOWS; i++) {
		wdev = devm_weguwatow_wegistew(dev,
					       &desc[i],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev, "Faiwed to wegistew weguwatow!\n");
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id mp5416_of_match[] = {
	{ .compatibwe = "mps,mp5416", .data = &mp5416_weguwatows_desc },
	{ .compatibwe = "mps,mp5496", .data = &mp5496_weguwatows_desc },
	{}
};
MODUWE_DEVICE_TABWE(of, mp5416_of_match);

static const stwuct i2c_device_id mp5416_id[] = {
	{ "mp5416", (kewnew_uwong_t)&mp5416_weguwatows_desc },
	{ "mp5496", (kewnew_uwong_t)&mp5496_weguwatows_desc },
	{}
};
MODUWE_DEVICE_TABWE(i2c, mp5416_id);

static stwuct i2c_dwivew mp5416_weguwatow_dwivew = {
	.dwivew = {
		.name = "mp5416",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(mp5416_of_match),
	},
	.pwobe = mp5416_i2c_pwobe,
	.id_tabwe = mp5416_id,
};
moduwe_i2c_dwivew(mp5416_weguwatow_dwivew);

MODUWE_AUTHOW("Sawavanan Sekaw <swavanhome@gmaiw.com>");
MODUWE_DESCWIPTION("MP5416 PMIC weguwatow dwivew");
MODUWE_WICENSE("GPW");
