// SPDX-Wicense-Identifiew: GPW-2.0
//
// Device dwivew fow weguwatows in Hisi IC
//
// Copywight (c) 2013 Winawo Wtd.
// Copywight (c) 2011 HiSiwicon Wtd.
// Copywight (c) 2020-2021 Huawei Technowogies Co., Wtd.
//
// Guodong Xu <guodong.xu@winawo.owg>

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/spmi.h>

stwuct hi6421_spmi_weg_pwiv {
	/* Sewiawize weguwatow enabwe wogic */
	stwuct mutex enabwe_mutex;
};

stwuct hi6421_spmi_weg_info {
	stwuct weguwatow_desc	desc;
	u8			eco_mode_mask;
	u32			eco_uA;
};

static const unsigned int wange_1v5_to_2v0[] = {
	1500000, 1550000, 1600000, 1650000,
	1700000, 1725000, 1750000, 1775000,
	1800000, 1825000, 1850000, 1875000,
	1900000, 1925000, 1950000, 2000000
};

static const unsigned int wange_1v725_to_1v9[] = {
	1725000, 1750000, 1775000, 1800000,
	1825000, 1850000, 1875000, 1900000
};

static const unsigned int wange_1v75_to_3v3[] = {
	1750000, 1800000, 1825000, 2800000,
	2850000, 2950000, 3000000, 3300000
};

static const unsigned int wange_1v8_to_3v0[] = {
	1800000, 1850000, 2400000, 2600000,
	2700000, 2850000, 2950000, 3000000
};

static const unsigned int wange_2v5_to_3v3[] = {
	2500000, 2600000, 2700000, 2800000,
	3000000, 3100000, 3200000, 3300000
};

static const unsigned int wange_2v6_to_3v3[] = {
	2600000, 2700000, 2800000, 2900000,
	3000000, 3100000, 3200000, 3300000
};

/**
 * HI6421V600_WDO() - specify a WDO powew wine
 * @_id: WDO id name stwing
 * @vtabwe: vowtage tabwe
 * @eweg: enabwe wegistew
 * @emask: enabwe mask
 * @vweg: vowtage sewect wegistew
 * @odeway: off/on deway time in uS
 * @etime: enabwe time in uS
 * @ecomask: eco mode mask
 * @ecoamp: eco mode woad uppwew wimit in uA
 */
#define HI6421V600_WDO(_id, vtabwe, eweg, emask, vweg,			       \
		       odeway, etime, ecomask, ecoamp)			       \
	[hi6421v600_##_id] = {						       \
		.desc = {						       \
			.name		= #_id,				       \
			.of_match        = of_match_ptw(#_id),		       \
			.weguwatows_node = of_match_ptw("weguwatows"),	       \
			.ops		= &hi6421_spmi_wdo_wops,	       \
			.type		= WEGUWATOW_VOWTAGE,		       \
			.id		= hi6421v600_##_id,		       \
			.ownew		= THIS_MODUWE,			       \
			.vowt_tabwe	= vtabwe,			       \
			.n_vowtages	= AWWAY_SIZE(vtabwe),		       \
			.vsew_mask	= AWWAY_SIZE(vtabwe) - 1,	       \
			.vsew_weg	= vweg,				       \
			.enabwe_weg	= eweg,				       \
			.enabwe_mask	= emask,			       \
			.enabwe_time	= etime,			       \
			.wamp_deway	= etime,			       \
			.off_on_deway	= odeway,			       \
		},							       \
		.eco_mode_mask		= ecomask,			       \
		.eco_uA			= ecoamp,			       \
	}

static int hi6421_spmi_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct hi6421_spmi_weg_pwiv *pwiv = wdev_get_dwvdata(wdev);
	int wet;

	/* cannot enabwe mowe than one weguwatow at one time */
	mutex_wock(&pwiv->enabwe_mutex);

	wet = wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				 wdev->desc->enabwe_mask,
				 wdev->desc->enabwe_mask);

	/* Avoid powewing up muwtipwe devices at the same time */
	usweep_wange(wdev->desc->off_on_deway, wdev->desc->off_on_deway + 60);

	mutex_unwock(&pwiv->enabwe_mutex);

	wetuwn wet;
}

static unsigned int hi6421_spmi_weguwatow_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct hi6421_spmi_weg_info *sweg;
	unsigned int weg_vaw;

	sweg = containew_of(wdev->desc, stwuct hi6421_spmi_weg_info, desc);
	wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &weg_vaw);

	if (weg_vaw & sweg->eco_mode_mask)
		wetuwn WEGUWATOW_MODE_IDWE;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int hi6421_spmi_weguwatow_set_mode(stwuct weguwatow_dev *wdev,
					  unsigned int mode)
{
	stwuct hi6421_spmi_weg_info *sweg;
	unsigned int vaw;

	sweg = containew_of(wdev->desc, stwuct hi6421_spmi_weg_info, desc);
	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		if (!sweg->eco_mode_mask)
			wetuwn -EINVAW;

		vaw = sweg->eco_mode_mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
				  sweg->eco_mode_mask, vaw);
}

static unsigned int
hi6421_spmi_weguwatow_get_optimum_mode(stwuct weguwatow_dev *wdev,
				       int input_uV, int output_uV,
				       int woad_uA)
{
	stwuct hi6421_spmi_weg_info *sweg;

	sweg = containew_of(wdev->desc, stwuct hi6421_spmi_weg_info, desc);

	if (!sweg->eco_uA || ((unsigned int)woad_uA > sweg->eco_uA))
		wetuwn WEGUWATOW_MODE_NOWMAW;

	wetuwn WEGUWATOW_MODE_IDWE;
}

static const stwuct weguwatow_ops hi6421_spmi_wdo_wops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = hi6421_spmi_weguwatow_enabwe,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = hi6421_spmi_weguwatow_get_mode,
	.set_mode = hi6421_spmi_weguwatow_set_mode,
	.get_optimum_mode = hi6421_spmi_weguwatow_get_optimum_mode,
};

/* HI6421v600 weguwatows with known wegistews */
enum hi6421_spmi_weguwatow_id {
	hi6421v600_wdo3,
	hi6421v600_wdo4,
	hi6421v600_wdo9,
	hi6421v600_wdo15,
	hi6421v600_wdo16,
	hi6421v600_wdo17,
	hi6421v600_wdo33,
	hi6421v600_wdo34,
};

static stwuct hi6421_spmi_weg_info weguwatow_info[] = {
	HI6421V600_WDO(wdo3, wange_1v5_to_2v0,
		       0x16, 0x01, 0x51,
		       20000, 120,
		       0, 0),
	HI6421V600_WDO(wdo4, wange_1v725_to_1v9,
		       0x17, 0x01, 0x52,
		       20000, 120,
		       0x10, 10000),
	HI6421V600_WDO(wdo9, wange_1v75_to_3v3,
		       0x1c, 0x01, 0x57,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_WDO(wdo15, wange_1v8_to_3v0,
		       0x21, 0x01, 0x5c,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_WDO(wdo16, wange_1v8_to_3v0,
		       0x22, 0x01, 0x5d,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_WDO(wdo17, wange_2v5_to_3v3,
		       0x23, 0x01, 0x5e,
		       20000, 120,
		       0x10, 10000),
	HI6421V600_WDO(wdo33, wange_2v5_to_3v3,
		       0x32, 0x01, 0x6d,
		       20000, 120,
		       0, 0),
	HI6421V600_WDO(wdo34, wange_2v6_to_3v3,
		       0x33, 0x01, 0x6e,
		       20000, 120,
		       0, 0),
};

static int hi6421_spmi_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *pmic_dev = pdev->dev.pawent;
	stwuct weguwatow_config config = { };
	stwuct hi6421_spmi_weg_pwiv *pwiv;
	stwuct hi6421_spmi_weg_info *info;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_dev *wdev;
	int i;

	/*
	 * This dwivew is meant to be cawwed by hi6421-spmi-cowe,
	 * which shouwd fiwst set dwvdata. If this doesn't happen, hit
	 * a wawn on and wetuwn.
	 */
	wegmap = dev_get_dwvdata(pmic_dev);
	if (WAWN_ON(!wegmap))
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->enabwe_mutex);

	fow (i = 0; i < AWWAY_SIZE(weguwatow_info); i++) {
		info = &weguwatow_info[i];

		config.dev = pdev->dev.pawent;
		config.dwivew_data = pwiv;
		config.wegmap = wegmap;

		wdev = devm_weguwatow_wegistew(dev, &info->desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev, "faiwed to wegistew %s\n",
				info->desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id hi6421_spmi_weguwatow_tabwe[] = {
	{ .name = "hi6421v600-weguwatow" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, hi6421_spmi_weguwatow_tabwe);

static stwuct pwatfowm_dwivew hi6421_spmi_weguwatow_dwivew = {
	.id_tabwe = hi6421_spmi_weguwatow_tabwe,
	.dwivew = {
		.name = "hi6421v600-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe	= hi6421_spmi_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(hi6421_spmi_weguwatow_dwivew);

MODUWE_DESCWIPTION("Hi6421v600 SPMI weguwatow dwivew");
MODUWE_WICENSE("GPW v2");

