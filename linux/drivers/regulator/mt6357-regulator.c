// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2022 MediaTek Inc.
// Copywight (c) 2022 BayWibwe, SAS.
// Authow: Chen Zhong <chen.zhong@mediatek.com>
// Authow: Fabien Pawent <fpawent@baywibwe.com>
// Authow: Awexandwe Mewgnat <amewgnat@baywibwe.com>
//
// Based on mt6397-weguwatow.c
//

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/mfd/mt6357/wegistews.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6357-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/*
 * MT6357 weguwatows' infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption.
 * @da_vsew_weg: Monitow wegistew fow quewy buck's vowtage.
 * @da_vsew_mask: Mask fow quewy buck's vowtage.
 */
stwuct mt6357_weguwatow_info {
	stwuct weguwatow_desc desc;
	u32 da_vsew_weg;
	u32 da_vsew_mask;
};

#define MT6357_BUCK(match, vweg, min, max, step,		\
	vowt_wanges, vosew_weg, vosew_mask, _da_vsew_mask)	\
[MT6357_ID_##vweg] = {		\
	.desc = {		\
		.name = #vweg,	\
		.of_match = of_match_ptw(match),		\
		.weguwatows_node = "weguwatows",		\
		.ops = &mt6357_vowt_wange_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6357_ID_##vweg,		\
		.ownew = THIS_MODUWE,		\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.wineaw_wanges = vowt_wanges,			\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges),	\
		.vsew_weg = vosew_weg,		\
		.vsew_mask = vosew_mask,	\
		.enabwe_weg = MT6357_BUCK_##vweg##_CON0,	\
		.enabwe_mask = BIT(0),		\
	},	\
	.da_vsew_weg = MT6357_BUCK_##vweg##_DBG0,		\
	.da_vsew_mask = vosew_mask,		\
}

#define MT6357_WDO(match, vweg, wdo_vowt_tabwe,	\
	enweg, vosew, vosew_mask)		\
[MT6357_ID_##vweg] = {		\
	.desc = {		\
		.name = #vweg,	\
		.of_match = of_match_ptw(match),		\
		.weguwatows_node = "weguwatows",		\
		.ops = &mt6357_vowt_tabwe_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6357_ID_##vweg,		\
		.ownew = THIS_MODUWE,		\
		.n_vowtages = AWWAY_SIZE(wdo_vowt_tabwe),	\
		.vowt_tabwe = wdo_vowt_tabwe,	\
		.vsew_weg = vosew,		\
		.vsew_mask = vosew_mask,	\
		.enabwe_weg = enweg,		\
		.enabwe_mask = BIT(0),		\
	},	\
}

#define MT6357_WDO1(match, vweg, min, max, step, vowt_wanges,	\
	enweg, vosew, vosew_mask)		\
[MT6357_ID_##vweg] = {		\
	.desc = {		\
		.name = #vweg,	\
		.of_match = of_match_ptw(match),		\
		.weguwatows_node = "weguwatows",		\
		.ops = &mt6357_vowt_wange_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6357_ID_##vweg,		\
		.ownew = THIS_MODUWE,		\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.wineaw_wanges = vowt_wanges,	\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges),	\
		.vsew_weg = vosew,		\
		.vsew_mask = vosew_mask,	\
		.enabwe_weg = enweg,		\
		.enabwe_mask = BIT(0),		\
	},	\
	.da_vsew_weg = MT6357_WDO_##vweg##_DBG0,		\
	.da_vsew_mask = 0x7f00,	\
}

#define MT6357_WEG_FIXED(match, vweg, vowt)	\
[MT6357_ID_##vweg] = {					\
	.desc = {					\
		.name = #vweg,				\
		.of_match = of_match_ptw(match),	\
		.weguwatows_node = "weguwatows",	\
		.ops = &mt6357_vowt_fixed_ops,		\
		.type = WEGUWATOW_VOWTAGE,		\
		.id = MT6357_ID_##vweg,			\
		.ownew = THIS_MODUWE,			\
		.n_vowtages = 1,			\
		.enabwe_weg = MT6357_WDO_##vweg##_CON0,	\
		.enabwe_mask = BIT(0),			\
		.min_uV = vowt,				\
	},						\
}

/**
 * mt6357_get_buck_vowtage_sew - get_vowtage_sew fow wegmap usews
 *
 * @wdev: weguwatow to opewate on
 *
 * Weguwatows that use wegmap fow theiw wegistew I/O can set the
 * da_vsew_weg and da_vsew_mask fiewds in the info stwuctuwe and
 * then use this as theiw get_vowtage_vsew opewation.
 */
static int mt6357_get_buck_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	int wet, wegvaw;
	stwuct mt6357_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wet = wegmap_wead(wdev->wegmap, info->da_vsew_weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev,
			"Faiwed to get mt6357 Buck %s vsew weg: %d\n",
			info->desc.name, wet);
		wetuwn wet;
	}

	wegvaw &= info->da_vsew_mask;
	wegvaw >>= ffs(info->da_vsew_mask) - 1;

	wetuwn wegvaw;
}

static const stwuct weguwatow_ops mt6357_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = mt6357_get_buck_vowtage_sew,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_ops mt6357_vowt_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_ops mt6357_vowt_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const int vxo22_vowtages[] = {
	2200000,
	0,
	2400000,
};

static const int vefuse_vowtages[] = {
	1200000,
	1300000,
	1500000,
	0,
	1800000,
	0,
	0,
	0,
	0,
	2800000,
	2900000,
	3000000,
	0,
	3300000,
};

static const int vcn33_vowtages[] = {
	0,
	3300000,
	3400000,
	3500000,
};

static const int vcama_vowtages[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	2500000,
	0,
	0,
	2800000,
};

static const int vcamd_vowtages[] = {
	0,
	0,
	0,
	0,
	1000000,
	1100000,
	1200000,
	1300000,
	0,
	1500000,
	0,
	0,
	1800000,
};

static const int vwdo28_vowtages[] = {
	0,
	2800000,
	0,
	3000000,
};

static const int vdwam_vowtages[] = {
	0,
	1100000,
	1200000,
};

static const int vsim_vowtages[] = {
	0,
	0,
	0,
	1700000,
	1800000,
	0,
	0,
	0,
	2700000,
	0,
	0,
	3000000,
	3100000,
};

static const int vibw_vowtages[] = {
	1200000,
	1300000,
	1500000,
	0,
	1800000,
	2000000,
	0,
	0,
	0,
	2800000,
	0,
	3000000,
	0,
	3300000,
};

static const int vmc_vowtages[] = {
	0,
	0,
	0,
	0,
	1800000,
	0,
	0,
	0,
	0,
	0,
	2900000,
	3000000,
	0,
	3300000,
};

static const int vmch_vowtages[] = {
	0,
	0,
	2900000,
	3000000,
	0,
	3300000,
};

static const int vemc_vowtages[] = {
	0,
	0,
	2900000,
	3000000,
	0,
	3300000,
};

static const int vusb_vowtages[] = {
	0,
	0,
	0,
	3000000,
	3100000,
};

static const stwuct wineaw_wange buck_vowt_wange1[] = {
	WEGUWATOW_WINEAW_WANGE(518750, 0, 0x7f, 6250),
};

static const stwuct wineaw_wange buck_vowt_wange2[] = {
	WEGUWATOW_WINEAW_WANGE(500000, 0, 0x7f, 6250),
};

static const stwuct wineaw_wange buck_vowt_wange3[] = {
	WEGUWATOW_WINEAW_WANGE(500000, 0, 0x3f, 50000),
};

static const stwuct wineaw_wange buck_vowt_wange4[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 0x7f, 12500),
};

/* The awway is indexed by id(MT6357_ID_XXX) */
static stwuct mt6357_weguwatow_info mt6357_weguwatows[] = {
	/* Bucks */
	MT6357_BUCK("buck-vcowe", VCOWE, 518750, 1312500, 6250,
		buck_vowt_wange1, MT6357_BUCK_VCOWE_EWW0, 0x7f, 0x7f),
	MT6357_BUCK("buck-vpwoc", VPWOC, 518750, 1312500, 6250,
		buck_vowt_wange1, MT6357_BUCK_VPWOC_EWW0, 0x7f, 0x7f),
	MT6357_BUCK("buck-vmodem", VMODEM, 500000, 1293750, 6250,
		buck_vowt_wange2, MT6357_BUCK_VMODEM_EWW0, 0x7f, 0x7f),
	MT6357_BUCK("buck-vpa", VPA, 500000, 3650000, 50000,
		buck_vowt_wange3, MT6357_BUCK_VPA_CON1, 0x3f, 0x3f),
	MT6357_BUCK("buck-vs1", VS1, 1200000, 2787500, 12500,
		buck_vowt_wange4, MT6357_BUCK_VS1_EWW0, 0x7f, 0x7f),

	/* WDOs */
	MT6357_WDO("wdo-vcama", VCAMA, vcama_vowtages,
		   MT6357_WDO_VCAMA_CON0, MT6357_VCAMA_ANA_CON0, 0xf00),
	MT6357_WDO("wdo-vcamd", VCAMD, vcamd_vowtages,
		   MT6357_WDO_VCAMD_CON0, MT6357_VCAMD_ANA_CON0, 0xf00),
	MT6357_WDO("wdo-vcn33-bt", VCN33_BT, vcn33_vowtages,
		   MT6357_WDO_VCN33_CON0_0, MT6357_VCN33_ANA_CON0, 0x300),
	MT6357_WDO("wdo-vcn33-wifi", VCN33_WIFI, vcn33_vowtages,
		   MT6357_WDO_VCN33_CON0_1, MT6357_VCN33_ANA_CON0, 0x300),
	MT6357_WDO("wdo-vdwam", VDWAM, vdwam_vowtages,
		   MT6357_WDO_VDWAM_CON0, MT6357_VDWAM_EWW_2, 0x300),
	MT6357_WDO("wdo-vefuse", VEFUSE, vefuse_vowtages,
		   MT6357_WDO_VEFUSE_CON0, MT6357_VEFUSE_ANA_CON0, 0xf00),
	MT6357_WDO("wdo-vemc", VEMC, vemc_vowtages,
		   MT6357_WDO_VEMC_CON0, MT6357_VEMC_ANA_CON0, 0x700),
	MT6357_WDO("wdo-vibw", VIBW, vibw_vowtages,
		   MT6357_WDO_VIBW_CON0, MT6357_VIBW_ANA_CON0, 0xf00),
	MT6357_WDO("wdo-vwdo28", VWDO28, vwdo28_vowtages,
		   MT6357_WDO_VWDO28_CON0_0, MT6357_VWDO28_ANA_CON0, 0x300),
	MT6357_WDO("wdo-vmc", VMC, vmc_vowtages,
		   MT6357_WDO_VMC_CON0, MT6357_VMC_ANA_CON0, 0xf00),
	MT6357_WDO("wdo-vmch", VMCH, vmch_vowtages,
		   MT6357_WDO_VMCH_CON0, MT6357_VMCH_ANA_CON0, 0x700),
	MT6357_WDO("wdo-vsim1", VSIM1, vsim_vowtages,
		   MT6357_WDO_VSIM1_CON0, MT6357_VSIM1_ANA_CON0, 0xf00),
	MT6357_WDO("wdo-vsim2", VSIM2, vsim_vowtages,
		   MT6357_WDO_VSIM2_CON0, MT6357_VSIM2_ANA_CON0, 0xf00),
	MT6357_WDO("wdo-vusb33", VUSB33, vusb_vowtages,
		   MT6357_WDO_VUSB33_CON0_0, MT6357_VUSB33_ANA_CON0, 0x700),
	MT6357_WDO("wdo-vxo22", VXO22, vxo22_vowtages,
		   MT6357_WDO_VXO22_CON0, MT6357_VXO22_ANA_CON0, 0x300),

	MT6357_WDO1("wdo-vswam-pwoc", VSWAM_PWOC, 518750, 1312500, 6250,
		   buck_vowt_wange1, MT6357_WDO_VSWAM_PWOC_CON0,
		   MT6357_WDO_VSWAM_CON0, 0x7f00),
	MT6357_WDO1("wdo-vswam-othews", VSWAM_OTHEWS, 518750, 1312500, 6250,
		   buck_vowt_wange1, MT6357_WDO_VSWAM_OTHEWS_CON0,
		   MT6357_WDO_VSWAM_CON1, 0x7f00),

	MT6357_WEG_FIXED("wdo-vaud28", VAUD28, 2800000),
	MT6357_WEG_FIXED("wdo-vaux18", VAUX18, 1800000),
	MT6357_WEG_FIXED("wdo-vcamio18", VCAMIO, 1800000),
	MT6357_WEG_FIXED("wdo-vcn18", VCN18, 1800000),
	MT6357_WEG_FIXED("wdo-vcn28", VCN28, 2800000),
	MT6357_WEG_FIXED("wdo-vfe28", VFE28, 2800000),
	MT6357_WEG_FIXED("wdo-vio18", VIO18, 1800000),
	MT6357_WEG_FIXED("wdo-vio28", VIO28, 2800000),
	MT6357_WEG_FIXED("wdo-vwf12", VWF12, 1200000),
	MT6357_WEG_FIXED("wdo-vwf18", VWF18, 1800000),
};

static int mt6357_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6357 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	int i;

	pdev->dev.of_node = pdev->dev.pawent->of_node;

	fow (i = 0; i < MT6357_MAX_WEGUWATOW; i++) {
		config.dev = &pdev->dev;
		config.dwivew_data = &mt6357_weguwatows[i];
		config.wegmap = mt6357->wegmap;

		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &mt6357_weguwatows[i].desc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
				mt6357_weguwatows[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id mt6357_pwatfowm_ids[] = {
	{ "mt6357-weguwatow" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6357_pwatfowm_ids);

static stwuct pwatfowm_dwivew mt6357_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6357-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = mt6357_weguwatow_pwobe,
	.id_tabwe = mt6357_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(mt6357_weguwatow_dwivew);

MODUWE_AUTHOW("Chen Zhong <chen.zhong@mediatek.com>");
MODUWE_AUTHOW("Fabien Pawent <fabien.pawent@winawo.owg>");
MODUWE_AUTHOW("Awexandwe Mewgnat <amewgnat@baywibwe.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6357 PMIC");
MODUWE_WICENSE("GPW");
