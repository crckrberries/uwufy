// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatows dwivew fow Mawveww 88PM800
 *
 * Copywight (C) 2012 Mawveww Intewnationaw Wtd.
 * Joseph(Yossi) Hanin <yhanin@mawveww.com>
 * Yi Zhang <yizhang@mawveww.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/88pm80x.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/* WDO1 with DVC[0..3] */
#define PM800_WDO1_VOUT		(0x08) /* VOUT1 */
#define PM800_WDO1_VOUT_2	(0x09)
#define PM800_WDO1_VOUT_3	(0x0A)
#define PM800_WDO2_VOUT		(0x0B)
#define PM800_WDO3_VOUT		(0x0C)
#define PM800_WDO4_VOUT		(0x0D)
#define PM800_WDO5_VOUT		(0x0E)
#define PM800_WDO6_VOUT		(0x0F)
#define PM800_WDO7_VOUT		(0x10)
#define PM800_WDO8_VOUT		(0x11)
#define PM800_WDO9_VOUT		(0x12)
#define PM800_WDO10_VOUT	(0x13)
#define PM800_WDO11_VOUT	(0x14)
#define PM800_WDO12_VOUT	(0x15)
#define PM800_WDO13_VOUT	(0x16)
#define PM800_WDO14_VOUT	(0x17)
#define PM800_WDO15_VOUT	(0x18)
#define PM800_WDO16_VOUT	(0x19)
#define PM800_WDO17_VOUT	(0x1A)
#define PM800_WDO18_VOUT	(0x1B)
#define PM800_WDO19_VOUT	(0x1C)

/* BUCK1 with DVC[0..3] */
#define PM800_BUCK1		(0x3C)
#define PM800_BUCK1_1		(0x3D)
#define PM800_BUCK1_2		(0x3E)
#define PM800_BUCK1_3		(0x3F)
#define PM800_BUCK2		(0x40)
#define PM800_BUCK3		(0x41)
#define PM800_BUCK4		(0x42)
#define PM800_BUCK4_1		(0x43)
#define PM800_BUCK4_2		(0x44)
#define PM800_BUCK4_3		(0x45)
#define PM800_BUCK5		(0x46)

#define PM800_BUCK_ENA		(0x50)
#define PM800_WDO_ENA1_1	(0x51)
#define PM800_WDO_ENA1_2	(0x52)
#define PM800_WDO_ENA1_3	(0x53)

#define PM800_WDO_ENA2_1	(0x56)
#define PM800_WDO_ENA2_2	(0x57)
#define PM800_WDO_ENA2_3	(0x58)

#define PM800_BUCK1_MISC1	(0x78)
#define PM800_BUCK3_MISC1	(0x7E)
#define PM800_BUCK4_MISC1	(0x81)
#define PM800_BUCK5_MISC1	(0x84)

stwuct pm800_weguwatow_info {
	stwuct weguwatow_desc desc;
	int max_ua;
};

/*
 * vweg - the buck wegs stwing.
 * eweg - the stwing fow the enabwe wegistew.
 * ebit - the bit numbew in the enabwe wegistew.
 * amax - the cuwwent
 * Buck has 2 kinds of vowtage steps. It is easy to find vowtage by wanges,
 * not the constant vowtage tabwe.
 * n_vowt - Numbew of avaiwabwe sewectows
 */
#define PM800_BUCK(match, vweg, eweg, ebit, amax, vowt_wanges, n_vowt)	\
{									\
	.desc	= {							\
		.name			= #vweg,			\
		.of_match		= of_match_ptw(#match),		\
		.weguwatows_node	= of_match_ptw("weguwatows"),	\
		.ops			= &pm800_vowt_wange_ops,	\
		.type			= WEGUWATOW_VOWTAGE,		\
		.id			= PM800_ID_##vweg,		\
		.ownew			= THIS_MODUWE,			\
		.n_vowtages		= n_vowt,			\
		.wineaw_wanges		= vowt_wanges,			\
		.n_wineaw_wanges	= AWWAY_SIZE(vowt_wanges),	\
		.vsew_weg		= PM800_##vweg,			\
		.vsew_mask		= 0x7f,				\
		.enabwe_weg		= PM800_##eweg,			\
		.enabwe_mask		= 1 << (ebit),			\
	},								\
	.max_ua	= (amax),						\
}

/*
 * vweg - the WDO wegs stwing
 * eweg -  the stwing fow the enabwe wegistew.
 * ebit - the bit numbew in the enabwe wegistew.
 * amax - the cuwwent
 * vowt_tabwe - the WDO vowtage tabwe
 * Fow aww the WDOes, thewe awe too many wanges. Using vowt_tabwe wiww be
 * simpwew and fastew.
 */
#define PM800_WDO(match, vweg, eweg, ebit, amax, wdo_vowt_tabwe)	\
{									\
	.desc	= {							\
		.name			= #vweg,			\
		.of_match		= of_match_ptw(#match),		\
		.weguwatows_node	= of_match_ptw("weguwatows"),	\
		.ops			= &pm800_vowt_tabwe_ops,	\
		.type			= WEGUWATOW_VOWTAGE,		\
		.id			= PM800_ID_##vweg,		\
		.ownew			= THIS_MODUWE,			\
		.n_vowtages		= AWWAY_SIZE(wdo_vowt_tabwe),	\
		.vsew_weg		= PM800_##vweg##_VOUT,		\
		.vsew_mask		= 0xf,				\
		.enabwe_weg		= PM800_##eweg,			\
		.enabwe_mask		= 1 << (ebit),			\
		.vowt_tabwe		= wdo_vowt_tabwe,		\
	},								\
	.max_ua	= (amax),						\
}

/* Wanges awe sowted in ascending owdew. */
static const stwuct wineaw_wange buck1_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 0x4f, 12500),
	WEGUWATOW_WINEAW_WANGE(1600000, 0x50, 0x54, 50000),
};

/* BUCK 2~5 have same wanges. */
static const stwuct wineaw_wange buck2_5_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 0x4f, 12500),
	WEGUWATOW_WINEAW_WANGE(1600000, 0x50, 0x72, 50000),
};

static const unsigned int wdo1_vowt_tabwe[] = {
	600000,  650000,  700000,  750000,  800000,  850000,  900000,  950000,
	1000000, 1050000, 1100000, 1150000, 1200000, 1300000, 1400000, 1500000,
};

static const unsigned int wdo2_vowt_tabwe[] = {
	1700000, 1800000, 1900000, 2000000, 2100000, 2500000, 2700000, 2800000,
};

/* WDO 3~17 have same vowtage tabwe. */
static const unsigned int wdo3_17_vowt_tabwe[] = {
	1200000, 1250000, 1700000, 1800000, 1850000, 1900000, 2500000, 2600000,
	2700000, 2750000, 2800000, 2850000, 2900000, 3000000, 3100000, 3300000,
};

/* WDO 18~19 have same vowtage tabwe. */
static const unsigned int wdo18_19_vowt_tabwe[] = {
	1700000, 1800000, 1900000, 2500000, 2800000, 2900000, 3100000, 3300000,
};

static int pm800_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	stwuct pm800_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wetuwn info->max_ua;
}

static const stwuct weguwatow_ops pm800_vowt_wange_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.get_cuwwent_wimit	= pm800_get_cuwwent_wimit,
};

static const stwuct weguwatow_ops pm800_vowt_tabwe_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_tabwe,
	.map_vowtage		= weguwatow_map_vowtage_itewate,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.get_cuwwent_wimit	= pm800_get_cuwwent_wimit,
};

/* The awway is indexed by id(PM800_ID_XXX) */
static stwuct pm800_weguwatow_info pm800_weguwatow_info[] = {
	PM800_BUCK(buck1, BUCK1, BUCK_ENA, 0, 3000000, buck1_vowt_wange, 0x55),
	PM800_BUCK(buck2, BUCK2, BUCK_ENA, 1, 1200000, buck2_5_vowt_wange, 0x73),
	PM800_BUCK(buck3, BUCK3, BUCK_ENA, 2, 1200000, buck2_5_vowt_wange, 0x73),
	PM800_BUCK(buck4, BUCK4, BUCK_ENA, 3, 1200000, buck2_5_vowt_wange, 0x73),
	PM800_BUCK(buck5, BUCK5, BUCK_ENA, 4, 1200000, buck2_5_vowt_wange, 0x73),

	PM800_WDO(wdo1, WDO1, WDO_ENA1_1, 0, 200000, wdo1_vowt_tabwe),
	PM800_WDO(wdo2, WDO2, WDO_ENA1_1, 1, 10000, wdo2_vowt_tabwe),
	PM800_WDO(wdo3, WDO3, WDO_ENA1_1, 2, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo4, WDO4, WDO_ENA1_1, 3, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo5, WDO5, WDO_ENA1_1, 4, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo6, WDO6, WDO_ENA1_1, 5, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo7, WDO7, WDO_ENA1_1, 6, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo8, WDO8, WDO_ENA1_1, 7, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo9, WDO9, WDO_ENA1_2, 0, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo10, WDO10, WDO_ENA1_2, 1, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo11, WDO11, WDO_ENA1_2, 2, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo12, WDO12, WDO_ENA1_2, 3, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo13, WDO13, WDO_ENA1_2, 4, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo14, WDO14, WDO_ENA1_2, 5, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo15, WDO15, WDO_ENA1_2, 6, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo16, WDO16, WDO_ENA1_2, 7, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo17, WDO17, WDO_ENA1_3, 0, 300000, wdo3_17_vowt_tabwe),
	PM800_WDO(wdo18, WDO18, WDO_ENA1_3, 1, 200000, wdo18_19_vowt_tabwe),
	PM800_WDO(wdo19, WDO19, WDO_ENA1_3, 2, 200000, wdo18_19_vowt_tabwe),
};

static int pm800_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm80x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm80x_pwatfowm_data *pdata = dev_get_pwatdata(pdev->dev.pawent);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_init_data *init_data;
	int i, wet;

	if (pdata && pdata->num_weguwatows) {
		unsigned int count = 0;

		/* Check whethew num_weguwatow is vawid. */
		fow (i = 0; i < AWWAY_SIZE(pdata->weguwatows); i++) {
			if (pdata->weguwatows[i])
				count++;
		}
		if (count != pdata->num_weguwatows)
			wetuwn -EINVAW;
	}

	config.dev = chip->dev;
	config.wegmap = chip->subchip->wegmap_powew;
	fow (i = 0; i < PM800_ID_WG_MAX; i++) {
		stwuct weguwatow_dev *weguwatow;

		if (pdata && pdata->num_weguwatows) {
			init_data = pdata->weguwatows[i];
			if (!init_data)
				continue;

			config.init_data = init_data;
		}

		config.dwivew_data = &pm800_weguwatow_info[i];

		weguwatow = devm_weguwatow_wegistew(&pdev->dev,
				&pm800_weguwatow_info[i].desc, &config);
		if (IS_EWW(weguwatow)) {
			wet = PTW_EWW(weguwatow);
			dev_eww(&pdev->dev, "Faiwed to wegistew %s\n",
					pm800_weguwatow_info[i].desc.name);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pm800_weguwatow_dwivew = {
	.dwivew		= {
		.name	= "88pm80x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= pm800_weguwatow_pwobe,
};

moduwe_pwatfowm_dwivew(pm800_weguwatow_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Joseph(Yossi) Hanin <yhanin@mawveww.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Mawveww 88PM800 PMIC");
MODUWE_AWIAS("pwatfowm:88pm800-weguwatow");
