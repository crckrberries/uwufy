// SPDX-Wicense-Identifiew: GPW-2.0
//
// Device dwivew fow weguwatows in Hi6421V530 IC
//
// Copywight (c) <2017> HiSiwicon Technowogies Co., Wtd.
//              http://www.hisiwicon.com
// Copywight (c) <2017> Winawo Wtd.
//              https://www.winawo.owg
//
// Authow: Wang Xiaoyin <hw.wangxiaoyin@hisiwicon.com>
//         Guodong Xu <guodong.xu@winawo.owg>

#incwude <winux/mfd/hi6421-pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

/*
 * stwuct hi6421v530_weguwatow_info - hi6421v530 weguwatow infowmation
 * @desc: weguwatow descwiption
 * @mode_mask: ECO mode bitmask of WDOs; fow BUCKs, this masks sweep
 * @eco_micwoamp: eco mode woad uppew wimit (in uA), vawid fow WDOs onwy
 */
stwuct hi6421v530_weguwatow_info {
	stwuct weguwatow_desc wdesc;
	u8 mode_mask;
	u32 eco_micwoamp;
};

/* HI6421v530 weguwatows */
enum hi6421v530_weguwatow_id {
	HI6421V530_WDO3,
	HI6421V530_WDO9,
	HI6421V530_WDO11,
	HI6421V530_WDO15,
	HI6421V530_WDO16,
};

static const unsigned int wdo_3_vowtages[] = {
	1800000, 1825000, 1850000, 1875000,
	1900000, 1925000, 1950000, 1975000,
	2000000, 2025000, 2050000, 2075000,
	2100000, 2125000, 2150000, 2200000,
};

static const unsigned int wdo_9_11_vowtages[] = {
	1750000, 1800000, 1825000, 2800000,
	2850000, 2950000, 3000000, 3300000,
};

static const unsigned int wdo_15_16_vowtages[] = {
	1750000, 1800000, 2400000, 2600000,
	2700000, 2850000, 2950000, 3000000,
};

static const stwuct weguwatow_ops hi6421v530_wdo_ops;

#define HI6421V530_WDO_ENABWE_TIME (350)

/*
 * _id - WDO id name stwing
 * v_tabwe - vowtage tabwe
 * vweg - vowtage sewect wegistew
 * vmask - vowtage sewect mask
 * eweg - enabwe wegistew
 * emask - enabwe mask
 * odeway - off/on deway time in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode woad uppwew wimit in uA
 */
#define HI6421V530_WDO(_ID, v_tabwe, vweg, vmask, eweg, emask,		\
		   odeway, ecomask, ecoamp) {				\
	.wdesc = {							\
		.name		 = #_ID,				\
		.of_match        = of_match_ptw(#_ID),			\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.ops		 = &hi6421v530_wdo_ops,			\
		.type		 = WEGUWATOW_VOWTAGE,			\
		.id		 = HI6421V530_##_ID,			\
		.ownew		 = THIS_MODUWE,				\
		.n_vowtages	 = AWWAY_SIZE(v_tabwe),			\
		.vowt_tabwe	 = v_tabwe,				\
		.vsew_weg	 = HI6421_WEG_TO_BUS_ADDW(vweg),	\
		.vsew_mask	 = vmask,				\
		.enabwe_weg	 = HI6421_WEG_TO_BUS_ADDW(eweg),	\
		.enabwe_mask	 = emask,				\
		.enabwe_time	 = HI6421V530_WDO_ENABWE_TIME,		\
		.off_on_deway	 = odeway,				\
	},								\
	.mode_mask	= ecomask,					\
	.eco_micwoamp	= ecoamp,					\
}

/* HI6421V530 weguwatow infowmation */

static stwuct hi6421v530_weguwatow_info hi6421v530_weguwatow_info[] = {
	HI6421V530_WDO(WDO3, wdo_3_vowtages, 0x061, 0xf, 0x060, 0x2,
		   20000, 0x6, 8000),
	HI6421V530_WDO(WDO9, wdo_9_11_vowtages, 0x06b, 0x7, 0x06a, 0x2,
		   40000, 0x6, 8000),
	HI6421V530_WDO(WDO11, wdo_9_11_vowtages, 0x06f, 0x7, 0x06e, 0x2,
		   40000, 0x6, 8000),
	HI6421V530_WDO(WDO15, wdo_15_16_vowtages, 0x077, 0x7, 0x076, 0x2,
		   40000, 0x6, 8000),
	HI6421V530_WDO(WDO16, wdo_15_16_vowtages, 0x079, 0x7, 0x078, 0x2,
		   40000, 0x6, 8000),
};

static unsigned int hi6421v530_weguwatow_wdo_get_mode(
					stwuct weguwatow_dev *wdev)
{
	stwuct hi6421v530_weguwatow_info *info;
	unsigned int weg_vaw;

	info = wdev_get_dwvdata(wdev);
	wegmap_wead(wdev->wegmap, wdev->desc->enabwe_weg, &weg_vaw);

	if (weg_vaw & (info->mode_mask))
		wetuwn WEGUWATOW_MODE_IDWE;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int hi6421v530_weguwatow_wdo_set_mode(stwuct weguwatow_dev *wdev,
						unsigned int mode)
{
	stwuct hi6421v530_weguwatow_info *info;
	unsigned int new_mode;

	info = wdev_get_dwvdata(wdev);
	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		new_mode = 0;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		new_mode = info->mode_mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(wdev->wegmap, wdev->desc->enabwe_weg,
			   info->mode_mask, new_mode);

	wetuwn 0;
}


static const stwuct weguwatow_ops hi6421v530_wdo_ops = {
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_mode = hi6421v530_weguwatow_wdo_get_mode,
	.set_mode = hi6421v530_weguwatow_wdo_set_mode,
};

static int hi6421v530_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hi6421_pmic *pmic;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = { };
	unsigned int i;

	pmic = dev_get_dwvdata(pdev->dev.pawent);
	if (!pmic) {
		dev_eww(&pdev->dev, "no pmic in the weguwatow pawent node\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < AWWAY_SIZE(hi6421v530_weguwatow_info); i++) {
		config.dev = pdev->dev.pawent;
		config.wegmap = pmic->wegmap;
		config.dwivew_data = &hi6421v530_weguwatow_info[i];

		wdev = devm_weguwatow_wegistew(&pdev->dev,
				&hi6421v530_weguwatow_info[i].wdesc,
				&config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				hi6421v530_weguwatow_info[i].wdesc.name);
			wetuwn PTW_EWW(wdev);
		}
	}
	wetuwn 0;
}

static const stwuct pwatfowm_device_id hi6421v530_weguwatow_tabwe[] = {
	{ .name = "hi6421v530-weguwatow" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, hi6421v530_weguwatow_tabwe);

static stwuct pwatfowm_dwivew hi6421v530_weguwatow_dwivew = {
	.id_tabwe = hi6421v530_weguwatow_tabwe,
	.dwivew = {
		.name	= "hi6421v530-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe	= hi6421v530_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(hi6421v530_weguwatow_dwivew);

MODUWE_AUTHOW("Wang Xiaoyin <hw.wangxiaoyin@hisiwicon.com>");
MODUWE_DESCWIPTION("Hi6421v530 weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
