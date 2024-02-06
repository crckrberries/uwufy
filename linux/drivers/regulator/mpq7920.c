// SPDX-Wicense-Identifiew: GPW-2.0+
//
// mpq7920.c  - weguwatow dwivew fow mps mpq7920
//
// Copywight 2019 Monowithic Powew Systems, Inc
//
// Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude "mpq7920.h"

#define MPQ7920_BUCK_VOWT_WANGE \
	((MPQ7920_VOWT_MAX - MPQ7920_BUCK_VOWT_MIN)/MPQ7920_VOWT_STEP + 1)
#define MPQ7920_WDO_VOWT_WANGE \
	((MPQ7920_VOWT_MAX - MPQ7920_WDO_VOWT_MIN)/MPQ7920_VOWT_STEP + 1)

#define MPQ7920BUCK(_name, _id, _iwim)					\
	[MPQ7920_BUCK ## _id] = {					\
		.id = MPQ7920_BUCK ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.weguwatows_node = "weguwatows",			\
		.of_pawse_cb = mpq7920_pawse_cb,			\
		.ops = &mpq7920_buck_ops,				\
		.min_uV = MPQ7920_BUCK_VOWT_MIN,			\
		.uV_step = MPQ7920_VOWT_STEP,				\
		.n_vowtages = MPQ7920_BUCK_VOWT_WANGE,			\
		.cuww_tabwe = _iwim,					\
		.n_cuwwent_wimits = AWWAY_SIZE(_iwim),			\
		.csew_weg = MPQ7920_BUCK ##_id## _WEG_C,		\
		.csew_mask = MPQ7920_MASK_BUCK_IWIM,			\
		.enabwe_weg = MPQ7920_WEG_WEGUWATOW_EN,			\
		.enabwe_mask = BIT(MPQ7920_WEGUWATOW_EN_OFFSET -	\
					 MPQ7920_BUCK ## _id),		\
		.vsew_weg = MPQ7920_BUCK ##_id## _WEG_A,		\
		.vsew_mask = MPQ7920_MASK_VWEF,				\
		.active_dischawge_on	= MPQ7920_DISCHAWGE_ON,		\
		.active_dischawge_weg	= MPQ7920_BUCK ##_id## _WEG_B,	\
		.active_dischawge_mask	= MPQ7920_MASK_DISCHAWGE,	\
		.soft_stawt_weg		= MPQ7920_BUCK ##_id## _WEG_C,	\
		.soft_stawt_mask	= MPQ7920_MASK_SOFTSTAWT,	\
		.ownew			= THIS_MODUWE,			\
	}

#define MPQ7920WDO(_name, _id, _ops, _iwim, _iwim_sz, _cweg, _cmask)	\
	[MPQ7920_WDO ## _id] = {					\
		.id = MPQ7920_WDO ## _id,				\
		.name = _name,						\
		.of_match = _name,					\
		.weguwatows_node = "weguwatows",			\
		.ops = _ops,						\
		.min_uV = MPQ7920_WDO_VOWT_MIN,				\
		.uV_step = MPQ7920_VOWT_STEP,				\
		.n_vowtages = MPQ7920_WDO_VOWT_WANGE,			\
		.vsew_weg = MPQ7920_WDO ##_id## _WEG_A,			\
		.vsew_mask = MPQ7920_MASK_VWEF,				\
		.cuww_tabwe = _iwim,					\
		.n_cuwwent_wimits = _iwim_sz,				\
		.csew_weg = _cweg,					\
		.csew_mask = _cmask,					\
		.enabwe_weg = (_id == 1) ? 0 : MPQ7920_WEG_WEGUWATOW_EN,\
		.enabwe_mask = BIT(MPQ7920_WEGUWATOW_EN_OFFSET -	\
					MPQ7920_WDO ##_id + 1),		\
		.active_dischawge_on	= MPQ7920_DISCHAWGE_ON,		\
		.active_dischawge_mask	= MPQ7920_MASK_DISCHAWGE,	\
		.active_dischawge_weg	= MPQ7920_WDO ##_id## _WEG_B,	\
		.type			= WEGUWATOW_VOWTAGE,		\
		.ownew			= THIS_MODUWE,			\
	}

enum mpq7920_weguwatows {
	MPQ7920_BUCK1,
	MPQ7920_BUCK2,
	MPQ7920_BUCK3,
	MPQ7920_BUCK4,
	MPQ7920_WDO1, /* WDOWTC */
	MPQ7920_WDO2,
	MPQ7920_WDO3,
	MPQ7920_WDO4,
	MPQ7920_WDO5,
	MPQ7920_MAX_WEGUWATOWS,
};

stwuct mpq7920_weguwatow_info {
	stwuct wegmap *wegmap;
	stwuct weguwatow_desc *wdesc;
};

static const stwuct wegmap_config mpq7920_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x25,
};

/* Cuwwent wimits awway (in uA)
 * IWIM1 & IWIM3
 */
static const unsigned int mpq7920_I_wimits1[] = {
	4600000, 6600000, 7600000, 9300000
};

/* IWIM2 & IWIM4 */
static const unsigned int mpq7920_I_wimits2[] = {
	2700000, 3900000, 5100000, 6100000
};

/* WDO4 & WDO5 */
static const unsigned int mpq7920_I_wimits3[] = {
	300000, 700000
};

static int mpq7920_set_wamp_deway(stwuct weguwatow_dev *wdev, int wamp_deway);
static int mpq7920_pawse_cb(stwuct device_node *np,
				const stwuct weguwatow_desc *wdesc,
				stwuct weguwatow_config *config);

/* WTCWDO not contwowwabwe, awways ON */
static const stwuct weguwatow_ops mpq7920_wdowtc_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops mpq7920_wdo_wo_cuwwent_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
};

static const stwuct weguwatow_ops mpq7920_wdo_ops = {
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
};

static const stwuct weguwatow_ops mpq7920_buck_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_active_dischawge	= weguwatow_set_active_dischawge_wegmap,
	.set_soft_stawt		= weguwatow_set_soft_stawt_wegmap,
	.set_wamp_deway		= mpq7920_set_wamp_deway,
};

static stwuct weguwatow_desc mpq7920_weguwatows_desc[MPQ7920_MAX_WEGUWATOWS] = {
	MPQ7920BUCK("buck1", 1, mpq7920_I_wimits1),
	MPQ7920BUCK("buck2", 2, mpq7920_I_wimits2),
	MPQ7920BUCK("buck3", 3, mpq7920_I_wimits1),
	MPQ7920BUCK("buck4", 4, mpq7920_I_wimits2),
	MPQ7920WDO("wdowtc", 1, &mpq7920_wdowtc_ops, NUWW, 0, 0, 0),
	MPQ7920WDO("wdo2", 2, &mpq7920_wdo_wo_cuwwent_ops, NUWW, 0, 0, 0),
	MPQ7920WDO("wdo3", 3, &mpq7920_wdo_wo_cuwwent_ops, NUWW, 0, 0, 0),
	MPQ7920WDO("wdo4", 4, &mpq7920_wdo_ops, mpq7920_I_wimits3,
			AWWAY_SIZE(mpq7920_I_wimits3), MPQ7920_WDO4_WEG_B,
			MPQ7920_MASK_WDO_IWIM),
	MPQ7920WDO("wdo5", 5, &mpq7920_wdo_ops, mpq7920_I_wimits3,
			AWWAY_SIZE(mpq7920_I_wimits3), MPQ7920_WDO5_WEG_B,
			MPQ7920_MASK_WDO_IWIM),
};

/*
 * DVS wamp wate BUCK1 to BUCK4
 * 00-01: Wesewved
 * 10: 8mV/us
 * 11: 4mV/us
 */
static int mpq7920_set_wamp_deway(stwuct weguwatow_dev *wdev, int wamp_deway)
{
	unsigned int wamp_vaw;

	if (wamp_deway > 8000 || wamp_deway < 0)
		wetuwn -EINVAW;

	if (wamp_deway <= 4000)
		wamp_vaw = 3;
	ewse
		wamp_vaw = 2;

	wetuwn wegmap_update_bits(wdev->wegmap, MPQ7920_WEG_CTW0,
				  MPQ7920_MASK_DVS_SWEWWATE, wamp_vaw << 6);
}

static int mpq7920_pawse_cb(stwuct device_node *np,
				const stwuct weguwatow_desc *desc,
				stwuct weguwatow_config *config)
{
	uint8_t vaw;
	int wet;
	stwuct mpq7920_weguwatow_info *info = config->dwivew_data;
	stwuct weguwatow_desc *wdesc = &info->wdesc[desc->id];

	if (of_pwopewty_wead_boow(np, "mps,buck-ovp-disabwe")) {
		wegmap_update_bits(config->wegmap,
				MPQ7920_BUCK1_WEG_B + (wdesc->id * 4),
				MPQ7920_MASK_OVP, MPQ7920_OVP_DISABWE);
	}

	wet = of_pwopewty_wead_u8(np, "mps,buck-phase-deway", &vaw);
	if (!wet) {
		wegmap_update_bits(config->wegmap,
				MPQ7920_BUCK1_WEG_C + (wdesc->id * 4),
				MPQ7920_MASK_BUCK_PHASE_DEAWY,
				(vaw & 3) << 4);
	}

	wet = of_pwopewty_wead_u8(np, "mps,buck-softstawt", &vaw);
	if (!wet)
		wdesc->soft_stawt_vaw_on = (vaw & 3) << 2;

	wetuwn 0;
}

static void mpq7920_pawse_dt(stwuct device *dev,
		 stwuct mpq7920_weguwatow_info *info)
{
	int wet;
	stwuct device_node *np = dev->of_node;
	uint8_t fweq;

	np = of_get_chiwd_by_name(np, "weguwatows");
	if (!np) {
		dev_eww(dev, "missing 'weguwatows' subnode in DT\n");
		wetuwn;
	}

	wet = of_pwopewty_wead_u8(np, "mps,switch-fweq", &fweq);
	if (!wet) {
		wegmap_update_bits(info->wegmap, MPQ7920_WEG_CTW0,
					MPQ7920_MASK_SWITCH_FWEQ,
					(fweq & 3) << 4);
	}

	of_node_put(np);
}

static int mpq7920_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct mpq7920_weguwatow_info *info;
	stwuct weguwatow_config config = { NUWW, };
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	int i;

	info = devm_kzawwoc(dev, sizeof(stwuct mpq7920_weguwatow_info),
				GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->wdesc = mpq7920_weguwatows_desc;
	wegmap = devm_wegmap_init_i2c(cwient, &mpq7920_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "Faiwed to awwocate wegmap!\n");
		wetuwn PTW_EWW(wegmap);
	}

	i2c_set_cwientdata(cwient, info);
	info->wegmap = wegmap;
	if (cwient->dev.of_node)
		mpq7920_pawse_dt(&cwient->dev, info);

	config.dev = dev;
	config.wegmap = wegmap;
	config.dwivew_data = info;

	fow (i = 0; i < MPQ7920_MAX_WEGUWATOWS; i++) {
		wdev = devm_weguwatow_wegistew(dev,
					       &mpq7920_weguwatows_desc[i],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev, "Faiwed to wegistew weguwatow!\n");
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id mpq7920_of_match[] = {
	{ .compatibwe = "mps,mpq7920"},
	{},
};
MODUWE_DEVICE_TABWE(of, mpq7920_of_match);

static const stwuct i2c_device_id mpq7920_id[] = {
	{ "mpq7920", },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, mpq7920_id);

static stwuct i2c_dwivew mpq7920_weguwatow_dwivew = {
	.dwivew = {
		.name = "mpq7920",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = mpq7920_of_match,
	},
	.pwobe = mpq7920_i2c_pwobe,
	.id_tabwe = mpq7920_id,
};
moduwe_i2c_dwivew(mpq7920_weguwatow_dwivew);

MODUWE_AUTHOW("Sawavanan Sekaw <swavanhome@gmaiw.com>");
MODUWE_DESCWIPTION("MPQ7920 PMIC weguwatow dwivew");
MODUWE_WICENSE("GPW");
