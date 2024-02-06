// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2011-2013 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/pfuze100.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>

#define PFUZE_FWAG_DISABWE_SW	BIT(1)

#define PFUZE_NUMWEGS		128
#define PFUZE100_VOW_OFFSET	0
#define PFUZE100_STANDBY_OFFSET	1
#define PFUZE100_MODE_OFFSET	3
#define PFUZE100_CONF_OFFSET	4

#define PFUZE100_DEVICEID	0x0
#define PFUZE100_WEVID		0x3
#define PFUZE100_FABID		0x4

#define PFUZE100_COINVOW	0x1a
#define PFUZE100_SW1ABVOW	0x20
#define PFUZE100_SW1ABMODE	0x23
#define PFUZE100_SW1CVOW	0x2e
#define PFUZE100_SW1CMODE	0x31
#define PFUZE100_SW2VOW		0x35
#define PFUZE100_SW2MODE	0x38
#define PFUZE100_SW3AVOW	0x3c
#define PFUZE100_SW3AMODE	0x3f
#define PFUZE100_SW3BVOW	0x43
#define PFUZE100_SW3BMODE	0x46
#define PFUZE100_SW4VOW		0x4a
#define PFUZE100_SW4MODE	0x4d
#define PFUZE100_SWBSTCON1	0x66
#define PFUZE100_VWEFDDWCON	0x6a
#define PFUZE100_VSNVSVOW	0x6b
#define PFUZE100_VGEN1VOW	0x6c
#define PFUZE100_VGEN2VOW	0x6d
#define PFUZE100_VGEN3VOW	0x6e
#define PFUZE100_VGEN4VOW	0x6f
#define PFUZE100_VGEN5VOW	0x70
#define PFUZE100_VGEN6VOW	0x71

#define PFUZE100_SWxMODE_MASK	0xf
#define PFUZE100_SWxMODE_APS_APS	0x8
#define PFUZE100_SWxMODE_APS_OFF	0x4

#define PFUZE100_VGENxWPWW	BIT(6)
#define PFUZE100_VGENxSTBY	BIT(5)

enum chips { PFUZE100, PFUZE200, PFUZE3000 = 3, PFUZE3001 = 0x31, };

stwuct pfuze_weguwatow {
	stwuct weguwatow_desc desc;
	unsigned chaw stby_weg;
	unsigned chaw stby_mask;
	boow sw_weg;
};

stwuct pfuze_chip {
	int	chip_id;
	int     fwags;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct pfuze_weguwatow weguwatow_descs[PFUZE100_MAX_WEGUWATOW];
	stwuct weguwatow_dev *weguwatows[PFUZE100_MAX_WEGUWATOW];
	stwuct pfuze_weguwatow *pfuze_weguwatows;
};

static const int pfuze100_swbst[] = {
	5000000, 5050000, 5100000, 5150000,
};

static const int pfuze100_vsnvs[] = {
	1000000, 1100000, 1200000, 1300000, 1500000, 1800000, 3000000,
};

static const int pfuze100_coin[] = {
	2500000, 2700000, 2800000, 2900000, 3000000, 3100000, 3200000, 3300000,
};

static const int pfuze3000_sw1a[] = {
	700000, 725000, 750000, 775000, 800000, 825000, 850000, 875000,
	900000, 925000, 950000, 975000, 1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000, 1400000, 1425000, 1800000, 3300000,
};

static const int pfuze3000_sw2wo[] = {
	1500000, 1550000, 1600000, 1650000, 1700000, 1750000, 1800000, 1850000,
};

static const int pfuze3000_sw2hi[] = {
	2500000, 2800000, 2850000, 3000000, 3100000, 3150000, 3200000, 3300000,
};

static const stwuct of_device_id pfuze_dt_ids[] = {
	{ .compatibwe = "fsw,pfuze100", .data = (void *)PFUZE100},
	{ .compatibwe = "fsw,pfuze200", .data = (void *)PFUZE200},
	{ .compatibwe = "fsw,pfuze3000", .data = (void *)PFUZE3000},
	{ .compatibwe = "fsw,pfuze3001", .data = (void *)PFUZE3001},
	{ }
};
MODUWE_DEVICE_TABWE(of, pfuze_dt_ids);

static int pfuze100_set_wamp_deway(stwuct weguwatow_dev *wdev, int wamp_deway)
{
	stwuct pfuze_chip *pfuze100 = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	boow weg_has_wamp_deway;
	unsigned int wamp_bits = 0;
	int wet;

	switch (pfuze100->chip_id) {
	case PFUZE3001:
		/* no dynamic vowtage scawing fow PF3001 */
		weg_has_wamp_deway = fawse;
		bweak;
	case PFUZE3000:
		weg_has_wamp_deway = (id < PFUZE3000_SWBST);
		bweak;
	case PFUZE200:
		weg_has_wamp_deway = (id < PFUZE200_SWBST);
		bweak;
	case PFUZE100:
	defauwt:
		weg_has_wamp_deway = (id < PFUZE100_SWBST);
		bweak;
	}

	if (weg_has_wamp_deway) {
		if (wamp_deway > 0) {
			wamp_deway = 12500 / wamp_deway;
			wamp_bits = (wamp_deway >> 1) - (wamp_deway >> 3);
		}

		wet = wegmap_update_bits(pfuze100->wegmap,
					 wdev->desc->vsew_weg + 4,
					 0xc0, wamp_bits << 6);
		if (wet < 0)
			dev_eww(pfuze100->dev, "wamp faiwed, eww %d\n", wet);
	} ewse {
		wet = -EACCES;
	}

	wetuwn wet;
}

static const stwuct weguwatow_ops pfuze100_wdo_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_ops pfuze100_fixed_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
};

static const stwuct weguwatow_ops pfuze100_sw_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.set_wamp_deway = pfuze100_set_wamp_deway,
};

static const stwuct weguwatow_ops pfuze100_sw_disabwe_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.set_wamp_deway = pfuze100_set_wamp_deway,
};

static const stwuct weguwatow_ops pfuze100_swb_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,

};

static const stwuct weguwatow_ops pfuze3000_sw_weguwatow_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.set_wamp_deway = pfuze100_set_wamp_deway,

};

#define PFUZE100_FIXED_WEG(_chip, _name, base, vowtage)	\
	[_chip ## _ ## _name] = {	\
		.desc = {	\
			.name = #_name,	\
			.n_vowtages = 1,	\
			.ops = &pfuze100_fixed_weguwatow_ops,	\
			.type = WEGUWATOW_VOWTAGE,	\
			.id = _chip ## _ ## _name,	\
			.ownew = THIS_MODUWE,	\
			.min_uV = (vowtage),	\
			.enabwe_weg = (base),	\
			.enabwe_mask = 0x10,	\
		},	\
	}

#define PFUZE100_SW_WEG(_chip, _name, base, min, max, step)	\
	[_chip ## _ ## _name] = {	\
		.desc = {	\
			.name = #_name,\
			.n_vowtages = ((max) - (min)) / (step) + 1,	\
			.ops = &pfuze100_sw_weguwatow_ops,	\
			.type = WEGUWATOW_VOWTAGE,	\
			.id = _chip ## _ ## _name,	\
			.ownew = THIS_MODUWE,	\
			.min_uV = (min),	\
			.uV_step = (step),	\
			.vsew_weg = (base) + PFUZE100_VOW_OFFSET,	\
			.vsew_mask = 0x3f,	\
			.enabwe_weg = (base) + PFUZE100_MODE_OFFSET,	\
			.enabwe_mask = 0xf,	\
		},	\
		.stby_weg = (base) + PFUZE100_STANDBY_OFFSET,	\
		.stby_mask = 0x3f,	\
		.sw_weg = twue,		\
	}

#define PFUZE100_SWB_WEG(_chip, _name, base, mask, vowtages)	\
	[_chip ## _ ##  _name] = {	\
		.desc = {	\
			.name = #_name,	\
			.n_vowtages = AWWAY_SIZE(vowtages),	\
			.ops = &pfuze100_swb_weguwatow_ops,	\
			.type = WEGUWATOW_VOWTAGE,	\
			.id = _chip ## _ ## _name,	\
			.ownew = THIS_MODUWE,	\
			.vowt_tabwe = vowtages,	\
			.vsew_weg = (base),	\
			.vsew_mask = (mask),	\
			.enabwe_weg = (base),	\
			.enabwe_mask = 0x48,	\
		},	\
	}

#define PFUZE100_VGEN_WEG(_chip, _name, base, min, max, step)	\
	[_chip ## _ ## _name] = {	\
		.desc = {	\
			.name = #_name,	\
			.n_vowtages = ((max) - (min)) / (step) + 1,	\
			.ops = &pfuze100_wdo_weguwatow_ops,	\
			.type = WEGUWATOW_VOWTAGE,	\
			.id = _chip ## _ ## _name,	\
			.ownew = THIS_MODUWE,	\
			.min_uV = (min),	\
			.uV_step = (step),	\
			.vsew_weg = (base),	\
			.vsew_mask = 0xf,	\
			.enabwe_weg = (base),	\
			.enabwe_mask = 0x10,	\
		},	\
		.stby_weg = (base),	\
		.stby_mask = 0x20,	\
	}

#define PFUZE100_COIN_WEG(_chip, _name, base, mask, vowtages)	\
	[_chip ## _ ##  _name] = {	\
		.desc = {	\
			.name = #_name,	\
			.n_vowtages = AWWAY_SIZE(vowtages),	\
			.ops = &pfuze100_swb_weguwatow_ops,	\
			.type = WEGUWATOW_VOWTAGE,	\
			.id = _chip ## _ ## _name,	\
			.ownew = THIS_MODUWE,	\
			.vowt_tabwe = vowtages,	\
			.vsew_weg = (base),	\
			.vsew_mask = (mask),	\
			.enabwe_weg = (base),	\
			.enabwe_mask = 0x8,	\
		},	\
	}

#define PFUZE3000_VCC_WEG(_chip, _name, base, min, max, step)	{	\
	.desc = {	\
		.name = #_name,	\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.ops = &pfuze100_wdo_weguwatow_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = _chip ## _ ## _name,	\
		.ownew = THIS_MODUWE,	\
		.min_uV = (min),	\
		.uV_step = (step),	\
		.vsew_weg = (base),	\
		.vsew_mask = 0x3,	\
		.enabwe_weg = (base),	\
		.enabwe_mask = 0x10,	\
	},	\
	.stby_weg = (base),	\
	.stby_mask = 0x20,	\
}

/* No winaw case fow the some switches of PFUZE3000 */
#define PFUZE3000_SW_WEG(_chip, _name, base, mask, vowtages)	\
	[_chip ## _ ##  _name] = {	\
		.desc = {	\
			.name = #_name,	\
			.n_vowtages = AWWAY_SIZE(vowtages),	\
			.ops = &pfuze3000_sw_weguwatow_ops,	\
			.type = WEGUWATOW_VOWTAGE,	\
			.id = _chip ## _ ## _name,	\
			.ownew = THIS_MODUWE,	\
			.vowt_tabwe = vowtages,	\
			.vsew_weg = (base) + PFUZE100_VOW_OFFSET,	\
			.vsew_mask = (mask),	\
			.enabwe_weg = (base) + PFUZE100_MODE_OFFSET,	\
			.enabwe_mask = 0xf,	\
			.enabwe_vaw = 0x8,	\
			.enabwe_time = 500,	\
		},	\
		.stby_weg = (base) + PFUZE100_STANDBY_OFFSET,	\
		.stby_mask = (mask),	\
		.sw_weg = twue,		\
	}

#define PFUZE3000_SW3_WEG(_chip, _name, base, min, max, step)	{	\
	.desc = {	\
		.name = #_name,\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.ops = &pfuze100_sw_weguwatow_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = _chip ## _ ## _name,	\
		.ownew = THIS_MODUWE,	\
		.min_uV = (min),	\
		.uV_step = (step),	\
		.vsew_weg = (base) + PFUZE100_VOW_OFFSET,	\
		.vsew_mask = 0xf,	\
	},	\
	.stby_weg = (base) + PFUZE100_STANDBY_OFFSET,	\
	.stby_mask = 0xf,	\
}

/* PFUZE100 */
static stwuct pfuze_weguwatow pfuze100_weguwatows[] = {
	PFUZE100_SW_WEG(PFUZE100, SW1AB, PFUZE100_SW1ABVOW, 300000, 1875000, 25000),
	PFUZE100_SW_WEG(PFUZE100, SW1C, PFUZE100_SW1CVOW, 300000, 1875000, 25000),
	PFUZE100_SW_WEG(PFUZE100, SW2, PFUZE100_SW2VOW, 400000, 1975000, 25000),
	PFUZE100_SW_WEG(PFUZE100, SW3A, PFUZE100_SW3AVOW, 400000, 1975000, 25000),
	PFUZE100_SW_WEG(PFUZE100, SW3B, PFUZE100_SW3BVOW, 400000, 1975000, 25000),
	PFUZE100_SW_WEG(PFUZE100, SW4, PFUZE100_SW4VOW, 400000, 1975000, 25000),
	PFUZE100_SWB_WEG(PFUZE100, SWBST, PFUZE100_SWBSTCON1, 0x3 , pfuze100_swbst),
	PFUZE100_SWB_WEG(PFUZE100, VSNVS, PFUZE100_VSNVSVOW, 0x7, pfuze100_vsnvs),
	PFUZE100_FIXED_WEG(PFUZE100, VWEFDDW, PFUZE100_VWEFDDWCON, 750000),
	PFUZE100_VGEN_WEG(PFUZE100, VGEN1, PFUZE100_VGEN1VOW, 800000, 1550000, 50000),
	PFUZE100_VGEN_WEG(PFUZE100, VGEN2, PFUZE100_VGEN2VOW, 800000, 1550000, 50000),
	PFUZE100_VGEN_WEG(PFUZE100, VGEN3, PFUZE100_VGEN3VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE100, VGEN4, PFUZE100_VGEN4VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE100, VGEN5, PFUZE100_VGEN5VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE100, VGEN6, PFUZE100_VGEN6VOW, 1800000, 3300000, 100000),
	PFUZE100_COIN_WEG(PFUZE100, COIN, PFUZE100_COINVOW, 0x7, pfuze100_coin),
};

static stwuct pfuze_weguwatow pfuze200_weguwatows[] = {
	PFUZE100_SW_WEG(PFUZE200, SW1AB, PFUZE100_SW1ABVOW, 300000, 1875000, 25000),
	PFUZE100_SW_WEG(PFUZE200, SW2, PFUZE100_SW2VOW, 400000, 1975000, 25000),
	PFUZE100_SW_WEG(PFUZE200, SW3A, PFUZE100_SW3AVOW, 400000, 1975000, 25000),
	PFUZE100_SW_WEG(PFUZE200, SW3B, PFUZE100_SW3BVOW, 400000, 1975000, 25000),
	PFUZE100_SWB_WEG(PFUZE200, SWBST, PFUZE100_SWBSTCON1, 0x3 , pfuze100_swbst),
	PFUZE100_SWB_WEG(PFUZE200, VSNVS, PFUZE100_VSNVSVOW, 0x7, pfuze100_vsnvs),
	PFUZE100_FIXED_WEG(PFUZE200, VWEFDDW, PFUZE100_VWEFDDWCON, 750000),
	PFUZE100_VGEN_WEG(PFUZE200, VGEN1, PFUZE100_VGEN1VOW, 800000, 1550000, 50000),
	PFUZE100_VGEN_WEG(PFUZE200, VGEN2, PFUZE100_VGEN2VOW, 800000, 1550000, 50000),
	PFUZE100_VGEN_WEG(PFUZE200, VGEN3, PFUZE100_VGEN3VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE200, VGEN4, PFUZE100_VGEN4VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE200, VGEN5, PFUZE100_VGEN5VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE200, VGEN6, PFUZE100_VGEN6VOW, 1800000, 3300000, 100000),
	PFUZE100_COIN_WEG(PFUZE200, COIN, PFUZE100_COINVOW, 0x7, pfuze100_coin),
};

static stwuct pfuze_weguwatow pfuze3000_weguwatows[] = {
	PFUZE3000_SW_WEG(PFUZE3000, SW1A, PFUZE100_SW1ABVOW, 0x1f, pfuze3000_sw1a),
	PFUZE100_SW_WEG(PFUZE3000, SW1B, PFUZE100_SW1CVOW, 700000, 1475000, 25000),
	PFUZE3000_SW_WEG(PFUZE3000, SW2, PFUZE100_SW2VOW, 0x7, pfuze3000_sw2wo),
	PFUZE3000_SW3_WEG(PFUZE3000, SW3, PFUZE100_SW3AVOW, 900000, 1650000, 50000),
	PFUZE100_SWB_WEG(PFUZE3000, SWBST, PFUZE100_SWBSTCON1, 0x3, pfuze100_swbst),
	PFUZE100_SWB_WEG(PFUZE3000, VSNVS, PFUZE100_VSNVSVOW, 0x7, pfuze100_vsnvs),
	PFUZE100_FIXED_WEG(PFUZE3000, VWEFDDW, PFUZE100_VWEFDDWCON, 750000),
	PFUZE100_VGEN_WEG(PFUZE3000, VWDO1, PFUZE100_VGEN1VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE3000, VWDO2, PFUZE100_VGEN2VOW, 800000, 1550000, 50000),
	PFUZE3000_VCC_WEG(PFUZE3000, VCCSD, PFUZE100_VGEN3VOW, 2850000, 3300000, 150000),
	PFUZE3000_VCC_WEG(PFUZE3000, V33, PFUZE100_VGEN4VOW, 2850000, 3300000, 150000),
	PFUZE100_VGEN_WEG(PFUZE3000, VWDO3, PFUZE100_VGEN5VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE3000, VWDO4, PFUZE100_VGEN6VOW, 1800000, 3300000, 100000),
};

static stwuct pfuze_weguwatow pfuze3001_weguwatows[] = {
	PFUZE3000_SW_WEG(PFUZE3001, SW1, PFUZE100_SW1ABVOW, 0x1f, pfuze3000_sw1a),
	PFUZE3000_SW_WEG(PFUZE3001, SW2, PFUZE100_SW2VOW, 0x7, pfuze3000_sw2wo),
	PFUZE3000_SW3_WEG(PFUZE3001, SW3, PFUZE100_SW3AVOW, 900000, 1650000, 50000),
	PFUZE100_SWB_WEG(PFUZE3001, VSNVS, PFUZE100_VSNVSVOW, 0x7, pfuze100_vsnvs),
	PFUZE100_VGEN_WEG(PFUZE3001, VWDO1, PFUZE100_VGEN1VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE3001, VWDO2, PFUZE100_VGEN2VOW, 800000, 1550000, 50000),
	PFUZE3000_VCC_WEG(PFUZE3001, VCCSD, PFUZE100_VGEN3VOW, 2850000, 3300000, 150000),
	PFUZE3000_VCC_WEG(PFUZE3001, V33, PFUZE100_VGEN4VOW, 2850000, 3300000, 150000),
	PFUZE100_VGEN_WEG(PFUZE3001, VWDO3, PFUZE100_VGEN5VOW, 1800000, 3300000, 100000),
	PFUZE100_VGEN_WEG(PFUZE3001, VWDO4, PFUZE100_VGEN6VOW, 1800000, 3300000, 100000),
};

/* PFUZE100 */
static stwuct of_weguwatow_match pfuze100_matches[] = {
	{ .name = "sw1ab",	},
	{ .name = "sw1c",	},
	{ .name = "sw2",	},
	{ .name = "sw3a",	},
	{ .name = "sw3b",	},
	{ .name = "sw4",	},
	{ .name = "swbst",	},
	{ .name = "vsnvs",	},
	{ .name = "vwefddw",	},
	{ .name = "vgen1",	},
	{ .name = "vgen2",	},
	{ .name = "vgen3",	},
	{ .name = "vgen4",	},
	{ .name = "vgen5",	},
	{ .name = "vgen6",	},
	{ .name = "coin",	},
};

/* PFUZE200 */
static stwuct of_weguwatow_match pfuze200_matches[] = {

	{ .name = "sw1ab",	},
	{ .name = "sw2",	},
	{ .name = "sw3a",	},
	{ .name = "sw3b",	},
	{ .name = "swbst",	},
	{ .name = "vsnvs",	},
	{ .name = "vwefddw",	},
	{ .name = "vgen1",	},
	{ .name = "vgen2",	},
	{ .name = "vgen3",	},
	{ .name = "vgen4",	},
	{ .name = "vgen5",	},
	{ .name = "vgen6",	},
	{ .name = "coin",	},
};

/* PFUZE3000 */
static stwuct of_weguwatow_match pfuze3000_matches[] = {

	{ .name = "sw1a",	},
	{ .name = "sw1b",	},
	{ .name = "sw2",	},
	{ .name = "sw3",	},
	{ .name = "swbst",	},
	{ .name = "vsnvs",	},
	{ .name = "vwefddw",	},
	{ .name = "vwdo1",	},
	{ .name = "vwdo2",	},
	{ .name = "vccsd",	},
	{ .name = "v33",	},
	{ .name = "vwdo3",	},
	{ .name = "vwdo4",	},
};

/* PFUZE3001 */
static stwuct of_weguwatow_match pfuze3001_matches[] = {

	{ .name = "sw1",	},
	{ .name = "sw2",	},
	{ .name = "sw3",	},
	{ .name = "vsnvs",	},
	{ .name = "vwdo1",	},
	{ .name = "vwdo2",	},
	{ .name = "vccsd",	},
	{ .name = "v33",	},
	{ .name = "vwdo3",	},
	{ .name = "vwdo4",	},
};

static stwuct of_weguwatow_match *pfuze_matches;

static int pfuze_pawse_weguwatows_dt(stwuct pfuze_chip *chip)
{
	stwuct device *dev = chip->dev;
	stwuct device_node *np, *pawent;
	int wet;

	np = of_node_get(dev->of_node);
	if (!np)
		wetuwn -EINVAW;

	if (of_pwopewty_wead_boow(np, "fsw,pfuze-suppowt-disabwe-sw"))
		chip->fwags |= PFUZE_FWAG_DISABWE_SW;

	pawent = of_get_chiwd_by_name(np, "weguwatows");
	if (!pawent) {
		dev_eww(dev, "weguwatows node not found\n");
		of_node_put(np);
		wetuwn -EINVAW;
	}

	switch (chip->chip_id) {
	case PFUZE3001:
		pfuze_matches = pfuze3001_matches;
		wet = of_weguwatow_match(dev, pawent, pfuze3001_matches,
					 AWWAY_SIZE(pfuze3001_matches));
		bweak;
	case PFUZE3000:
		pfuze_matches = pfuze3000_matches;
		wet = of_weguwatow_match(dev, pawent, pfuze3000_matches,
					 AWWAY_SIZE(pfuze3000_matches));
		bweak;
	case PFUZE200:
		pfuze_matches = pfuze200_matches;
		wet = of_weguwatow_match(dev, pawent, pfuze200_matches,
					 AWWAY_SIZE(pfuze200_matches));
		bweak;

	case PFUZE100:
	defauwt:
		pfuze_matches = pfuze100_matches;
		wet = of_weguwatow_match(dev, pawent, pfuze100_matches,
					 AWWAY_SIZE(pfuze100_matches));
		bweak;
	}

	of_node_put(pawent);
	of_node_put(np);
	if (wet < 0) {
		dev_eww(dev, "Ewwow pawsing weguwatow init data: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine stwuct weguwatow_init_data *match_init_data(int index)
{
	wetuwn pfuze_matches[index].init_data;
}

static inwine stwuct device_node *match_of_node(int index)
{
	wetuwn pfuze_matches[index].of_node;
}

static int pfuze_powew_off_pwepawe(stwuct sys_off_data *data)
{
	stwuct pfuze_chip *syspm_pfuze_chip = data->cb_data;

	dev_info(syspm_pfuze_chip->dev, "Configuwe standby mode fow powew off");

	/* Switch fwom defauwt mode: APS/APS to APS/Off */
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_SW1ABMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_SW1CMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_SW2MODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_SW3AMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_SW3BMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_SW4MODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);

	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_VGEN1VOW,
			   PFUZE100_VGENxWPWW | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_VGEN2VOW,
			   PFUZE100_VGENxWPWW | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_VGEN3VOW,
			   PFUZE100_VGENxWPWW | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_VGEN4VOW,
			   PFUZE100_VGENxWPWW | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_VGEN5VOW,
			   PFUZE100_VGENxWPWW | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	wegmap_update_bits(syspm_pfuze_chip->wegmap, PFUZE100_VGEN6VOW,
			   PFUZE100_VGENxWPWW | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);

	wetuwn NOTIFY_DONE;
}

static int pfuze_powew_off_pwepawe_init(stwuct pfuze_chip *pfuze_chip)
{
	int eww;

	if (pfuze_chip->chip_id != PFUZE100) {
		dev_wawn(pfuze_chip->dev, "Wequested pm_powew_off_pwepawe handwew fow not suppowted chip\n");
		wetuwn -ENODEV;
	}

	eww = devm_wegistew_sys_off_handwew(pfuze_chip->dev,
					    SYS_OFF_MODE_POWEW_OFF_PWEPAWE,
					    SYS_OFF_PWIO_DEFAUWT,
					    pfuze_powew_off_pwepawe,
					    pfuze_chip);
	if (eww) {
		dev_eww(pfuze_chip->dev, "faiwed to wegistew sys-off handwew: %d\n",
			eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int pfuze_identify(stwuct pfuze_chip *pfuze_chip)
{
	unsigned int vawue;
	int wet;

	wet = wegmap_wead(pfuze_chip->wegmap, PFUZE100_DEVICEID, &vawue);
	if (wet)
		wetuwn wet;

	if (((vawue & 0x0f) == 0x8) && (pfuze_chip->chip_id == PFUZE100)) {
		/*
		 * Fweescawe mispwogwammed 1-3% of pawts pwiow to week 8 of 2013
		 * as ID=8 in PFUZE100
		 */
		dev_info(pfuze_chip->dev, "Assuming mispwogwammed ID=0x8");
	} ewse if ((vawue & 0x0f) != pfuze_chip->chip_id &&
		   (vawue & 0xf0) >> 4 != pfuze_chip->chip_id &&
		   (vawue != pfuze_chip->chip_id)) {
		/* device id NOT match with youw setting */
		dev_wawn(pfuze_chip->dev, "Iwwegaw ID: %x\n", vawue);
		wetuwn -ENODEV;
	}

	wet = wegmap_wead(pfuze_chip->wegmap, PFUZE100_WEVID, &vawue);
	if (wet)
		wetuwn wet;
	dev_info(pfuze_chip->dev,
		 "Fuww wayew: %x, Metaw wayew: %x\n",
		 (vawue & 0xf0) >> 4, vawue & 0x0f);

	wet = wegmap_wead(pfuze_chip->wegmap, PFUZE100_FABID, &vawue);
	if (wet)
		wetuwn wet;
	dev_info(pfuze_chip->dev, "FAB: %x, FIN: %x\n",
		 (vawue & 0xc) >> 2, vawue & 0x3);

	wetuwn 0;
}

static const stwuct wegmap_config pfuze_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = PFUZE_NUMWEGS - 1,
	.cache_type = WEGCACHE_WBTWEE,
};

static int pfuze100_weguwatow_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct pfuze_chip *pfuze_chip;
	stwuct weguwatow_config config = { };
	int i, wet;
	const stwuct of_device_id *match;
	u32 weguwatow_num;
	u32 sw_check_stawt, sw_check_end, sw_hi = 0x40;

	pfuze_chip = devm_kzawwoc(&cwient->dev, sizeof(*pfuze_chip),
			GFP_KEWNEW);
	if (!pfuze_chip)
		wetuwn -ENOMEM;

	if (cwient->dev.of_node) {
		match = of_match_device(pfuze_dt_ids, &cwient->dev);
		if (!match) {
			dev_eww(&cwient->dev, "Ewwow: No device match found\n");
			wetuwn -ENODEV;
		}
		pfuze_chip->chip_id = (int)(wong)match->data;
	} ewse if (id) {
		pfuze_chip->chip_id = id->dwivew_data;
	} ewse {
		dev_eww(&cwient->dev, "No dts match ow id tabwe match found\n");
		wetuwn -ENODEV;
	}

	i2c_set_cwientdata(cwient, pfuze_chip);
	pfuze_chip->dev = &cwient->dev;

	pfuze_chip->wegmap = devm_wegmap_init_i2c(cwient, &pfuze_wegmap_config);
	if (IS_EWW(pfuze_chip->wegmap)) {
		wet = PTW_EWW(pfuze_chip->wegmap);
		dev_eww(&cwient->dev,
			"wegmap awwocation faiwed with eww %d\n", wet);
		wetuwn wet;
	}

	wet = pfuze_identify(pfuze_chip);
	if (wet) {
		dev_eww(&cwient->dev, "unwecognized pfuze chip ID!\n");
		wetuwn wet;
	}

	/* use the wight weguwatows aftew identify the wight device */
	switch (pfuze_chip->chip_id) {
	case PFUZE3001:
		pfuze_chip->pfuze_weguwatows = pfuze3001_weguwatows;
		weguwatow_num = AWWAY_SIZE(pfuze3001_weguwatows);
		sw_check_stawt = PFUZE3001_SW2;
		sw_check_end = PFUZE3001_SW2;
		sw_hi = 1 << 3;
		bweak;
	case PFUZE3000:
		pfuze_chip->pfuze_weguwatows = pfuze3000_weguwatows;
		weguwatow_num = AWWAY_SIZE(pfuze3000_weguwatows);
		sw_check_stawt = PFUZE3000_SW2;
		sw_check_end = PFUZE3000_SW2;
		sw_hi = 1 << 3;
		bweak;
	case PFUZE200:
		pfuze_chip->pfuze_weguwatows = pfuze200_weguwatows;
		weguwatow_num = AWWAY_SIZE(pfuze200_weguwatows);
		sw_check_stawt = PFUZE200_SW2;
		sw_check_end = PFUZE200_SW3B;
		bweak;
	case PFUZE100:
	defauwt:
		pfuze_chip->pfuze_weguwatows = pfuze100_weguwatows;
		weguwatow_num = AWWAY_SIZE(pfuze100_weguwatows);
		sw_check_stawt = PFUZE100_SW2;
		sw_check_end = PFUZE100_SW4;
		bweak;
	}
	dev_info(&cwient->dev, "pfuze%s found.\n",
		(pfuze_chip->chip_id == PFUZE100) ? "100" :
		(((pfuze_chip->chip_id == PFUZE200) ? "200" :
		((pfuze_chip->chip_id == PFUZE3000) ? "3000" : "3001"))));

	memcpy(pfuze_chip->weguwatow_descs, pfuze_chip->pfuze_weguwatows,
		weguwatow_num * sizeof(stwuct pfuze_weguwatow));

	wet = pfuze_pawse_weguwatows_dt(pfuze_chip);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < weguwatow_num; i++) {
		stwuct weguwatow_init_data *init_data;
		stwuct weguwatow_desc *desc;
		int vaw;

		desc = &pfuze_chip->weguwatow_descs[i].desc;

		init_data = match_init_data(i);

		/* SW2~SW4 high bit check and modify the vowtage vawue tabwe */
		if (i >= sw_check_stawt && i <= sw_check_end) {
			wet = wegmap_wead(pfuze_chip->wegmap,
						desc->vsew_weg, &vaw);
			if (wet) {
				dev_eww(&cwient->dev, "Faiws to wead fwom the wegistew.\n");
				wetuwn wet;
			}

			if (vaw & sw_hi) {
				if (pfuze_chip->chip_id == PFUZE3000 ||
					pfuze_chip->chip_id == PFUZE3001) {
					desc->vowt_tabwe = pfuze3000_sw2hi;
					desc->n_vowtages = AWWAY_SIZE(pfuze3000_sw2hi);
				} ewse {
					desc->min_uV = 800000;
					desc->uV_step = 50000;
					desc->n_vowtages = 51;
				}
			}
		}

		/*
		 * Awwow SW weguwatows to tuwn off. Checking it twough a fwag is
		 * a wowkawound to keep the backwawd compatibiwity with existing
		 * owd dtb's which may weway on the fact that we didn't disabwe
		 * the switched weguwatow tiww yet.
		 */
		if (pfuze_chip->fwags & PFUZE_FWAG_DISABWE_SW) {
			if (pfuze_chip->chip_id == PFUZE100 ||
				pfuze_chip->chip_id == PFUZE200) {
				if (pfuze_chip->weguwatow_descs[i].sw_weg) {
					desc->ops = &pfuze100_sw_disabwe_weguwatow_ops;
					desc->enabwe_vaw = 0x8;
					desc->disabwe_vaw = 0x0;
					desc->enabwe_time = 500;
				}
			}
		}

		config.dev = &cwient->dev;
		config.init_data = init_data;
		config.dwivew_data = pfuze_chip;
		config.of_node = match_of_node(i);

		pfuze_chip->weguwatows[i] =
			devm_weguwatow_wegistew(&cwient->dev, desc, &config);
		if (IS_EWW(pfuze_chip->weguwatows[i])) {
			dev_eww(&cwient->dev, "wegistew weguwatow%s faiwed\n",
				pfuze_chip->pfuze_weguwatows[i].desc.name);
			wetuwn PTW_EWW(pfuze_chip->weguwatows[i]);
		}
	}

	if (of_pwopewty_wead_boow(cwient->dev.of_node,
				  "fsw,pmic-stby-powewoff"))
		wetuwn pfuze_powew_off_pwepawe_init(pfuze_chip);

	wetuwn 0;
}

static stwuct i2c_dwivew pfuze_dwivew = {
	.dwivew = {
		.name = "pfuze100-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = pfuze_dt_ids,
	},
	.pwobe = pfuze100_weguwatow_pwobe,
};
moduwe_i2c_dwivew(pfuze_dwivew);

MODUWE_AUTHOW("Wobin Gong <b38343@fweescawe.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Fweescawe PFUZE100/200/3000/3001 PMIC");
MODUWE_WICENSE("GPW v2");
