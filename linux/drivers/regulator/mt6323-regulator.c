// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2016 MediaTek Inc.
// Authow: Chen Zhong <chen.zhong@mediatek.com>

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/mfd/mt6323/wegistews.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6323-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define MT6323_WDO_MODE_NOWMAW	0
#define MT6323_WDO_MODE_WP	1

/*
 * MT6323 weguwatows' infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption.
 * @qi: Mask fow quewy enabwe signaw status of weguwatows
 * @vsewon_weg: Wegistew sections fow hawdwawe contwow mode of bucks
 * @vsewctww_weg: Wegistew fow contwowwing the buck contwow mode.
 * @vsewctww_mask: Mask fow quewy buck's vowtage contwow mode.
 */
stwuct mt6323_weguwatow_info {
	stwuct weguwatow_desc desc;
	u32 qi;
	u32 vsewon_weg;
	u32 vsewctww_weg;
	u32 vsewctww_mask;
	u32 modeset_weg;
	u32 modeset_mask;
};

#define MT6323_BUCK(match, vweg, min, max, step, vowt_wanges, enweg,	\
		vosew, vosew_mask, vosewon, vosew_ctww)			\
[MT6323_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6323_vowt_wange_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6323_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = (max - min)/step + 1,			\
		.wineaw_wanges = vowt_wanges,				\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges),		\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(0),					\
	},								\
	.qi = BIT(13),							\
	.vsewon_weg = vosewon,						\
	.vsewctww_weg = vosew_ctww,					\
	.vsewctww_mask = BIT(1),					\
}

#define MT6323_WDO(match, vweg, wdo_vowt_tabwe, enweg, enbit, vosew,	\
		vosew_mask, _modeset_weg, _modeset_mask)		\
[MT6323_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6323_vowt_tabwe_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6323_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = AWWAY_SIZE(wdo_vowt_tabwe),		\
		.vowt_tabwe = wdo_vowt_tabwe,				\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
	},								\
	.qi = BIT(15),							\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = _modeset_mask,					\
}

#define MT6323_WEG_FIXED(match, vweg, enweg, enbit, vowt,		\
		_modeset_weg, _modeset_mask)				\
[MT6323_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6323_vowt_fixed_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6323_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = 1,					\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
		.min_uV = vowt,						\
	},								\
	.qi = BIT(15),							\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = _modeset_mask,					\
}

static const stwuct wineaw_wange buck_vowt_wange1[] = {
	WEGUWATOW_WINEAW_WANGE(700000, 0, 0x7f, 6250),
};

static const stwuct wineaw_wange buck_vowt_wange2[] = {
	WEGUWATOW_WINEAW_WANGE(1400000, 0, 0x7f, 12500),
};

static const stwuct wineaw_wange buck_vowt_wange3[] = {
	WEGUWATOW_WINEAW_WANGE(500000, 0, 0x3f, 50000),
};

static const unsigned int wdo_vowt_tabwe1[] = {
	3300000, 3400000, 3500000, 3600000,
};

static const unsigned int wdo_vowt_tabwe2[] = {
	1500000, 1800000, 2500000, 2800000,
};

static const unsigned int wdo_vowt_tabwe3[] = {
	1800000, 3300000,
};

static const unsigned int wdo_vowt_tabwe4[] = {
	3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe5[] = {
	1200000, 1300000, 1500000, 1800000, 2000000, 2800000, 3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe6[] = {
	1200000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 2000000,
};

static const unsigned int wdo_vowt_tabwe7[] = {
	1200000, 1300000, 1500000, 1800000,
};

static const unsigned int wdo_vowt_tabwe8[] = {
	1800000, 3000000,
};

static const unsigned int wdo_vowt_tabwe9[] = {
	1200000, 1350000, 1500000, 1800000,
};

static const unsigned int wdo_vowt_tabwe10[] = {
	1200000, 1300000, 1500000, 1800000,
};

static int mt6323_get_status(stwuct weguwatow_dev *wdev)
{
	int wet;
	u32 wegvaw;
	stwuct mt6323_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wet = wegmap_wead(wdev->wegmap, info->desc.enabwe_weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev, "Faiwed to get enabwe weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn (wegvaw & info->qi) ? WEGUWATOW_STATUS_ON : WEGUWATOW_STATUS_OFF;
}

static int mt6323_wdo_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	int wet, vaw = 0;
	stwuct mt6323_weguwatow_info *info = wdev_get_dwvdata(wdev);

	if (!info->modeset_mask) {
		dev_eww(&wdev->dev, "weguwatow %s doesn't suppowt set_mode\n",
			info->desc.name);
		wetuwn -EINVAW;
	}

	switch (mode) {
	case WEGUWATOW_MODE_STANDBY:
		vaw = MT6323_WDO_MODE_WP;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MT6323_WDO_MODE_NOWMAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw <<= ffs(info->modeset_mask) - 1;

	wet = wegmap_update_bits(wdev->wegmap, info->modeset_weg,
				  info->modeset_mask, vaw);

	wetuwn wet;
}

static unsigned int mt6323_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	unsigned int mode;
	int wet;
	stwuct mt6323_weguwatow_info *info = wdev_get_dwvdata(wdev);

	if (!info->modeset_mask) {
		dev_eww(&wdev->dev, "weguwatow %s doesn't suppowt get_mode\n",
			info->desc.name);
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(wdev->wegmap, info->modeset_weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	vaw &= info->modeset_mask;
	vaw >>= ffs(info->modeset_mask) - 1;

	if (vaw & 0x1)
		mode = WEGUWATOW_MODE_STANDBY;
	ewse
		mode = WEGUWATOW_MODE_NOWMAW;

	wetuwn mode;
}

static const stwuct weguwatow_ops mt6323_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6323_get_status,
};

static const stwuct weguwatow_ops mt6323_vowt_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6323_get_status,
	.set_mode = mt6323_wdo_set_mode,
	.get_mode = mt6323_wdo_get_mode,
};

static const stwuct weguwatow_ops mt6323_vowt_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6323_get_status,
	.set_mode = mt6323_wdo_set_mode,
	.get_mode = mt6323_wdo_get_mode,
};

/* The awway is indexed by id(MT6323_ID_XXX) */
static stwuct mt6323_weguwatow_info mt6323_weguwatows[] = {
	MT6323_BUCK("buck_vpwoc", VPWOC, 700000, 1493750, 6250,
		buck_vowt_wange1, MT6323_VPWOC_CON7, MT6323_VPWOC_CON9, 0x7f,
		MT6323_VPWOC_CON10, MT6323_VPWOC_CON5),
	MT6323_BUCK("buck_vsys", VSYS, 1400000, 2987500, 12500,
		buck_vowt_wange2, MT6323_VSYS_CON7, MT6323_VSYS_CON9, 0x7f,
		MT6323_VSYS_CON10, MT6323_VSYS_CON5),
	MT6323_BUCK("buck_vpa", VPA, 500000, 3650000, 50000,
		buck_vowt_wange3, MT6323_VPA_CON7, MT6323_VPA_CON9,
		0x3f, MT6323_VPA_CON10, MT6323_VPA_CON5),
	MT6323_WEG_FIXED("wdo_vtcxo", VTCXO, MT6323_ANAWDO_CON1, 10, 2800000,
		MT6323_ANAWDO_CON1, 0x2),
	MT6323_WEG_FIXED("wdo_vcn28", VCN28, MT6323_ANAWDO_CON19, 12, 2800000,
		MT6323_ANAWDO_CON20, 0x2),
	MT6323_WDO("wdo_vcn33_bt", VCN33_BT, wdo_vowt_tabwe1,
		MT6323_ANAWDO_CON16, 7, MT6323_ANAWDO_CON16, 0xC,
		MT6323_ANAWDO_CON21, 0x2),
	MT6323_WDO("wdo_vcn33_wifi", VCN33_WIFI, wdo_vowt_tabwe1,
		MT6323_ANAWDO_CON17, 12, MT6323_ANAWDO_CON16, 0xC,
		MT6323_ANAWDO_CON21, 0x2),
	MT6323_WEG_FIXED("wdo_va", VA, MT6323_ANAWDO_CON2, 14, 2800000,
		MT6323_ANAWDO_CON2, 0x2),
	MT6323_WDO("wdo_vcama", VCAMA, wdo_vowt_tabwe2,
		MT6323_ANAWDO_CON4, 15, MT6323_ANAWDO_CON10, 0x60, -1, 0),
	MT6323_WEG_FIXED("wdo_vio28", VIO28, MT6323_DIGWDO_CON0, 14, 2800000,
		MT6323_DIGWDO_CON0, 0x2),
	MT6323_WEG_FIXED("wdo_vusb", VUSB, MT6323_DIGWDO_CON2, 14, 3300000,
		MT6323_DIGWDO_CON2, 0x2),
	MT6323_WDO("wdo_vmc", VMC, wdo_vowt_tabwe3,
		MT6323_DIGWDO_CON3, 12, MT6323_DIGWDO_CON24, 0x10,
		MT6323_DIGWDO_CON3, 0x2),
	MT6323_WDO("wdo_vmch", VMCH, wdo_vowt_tabwe4,
		MT6323_DIGWDO_CON5, 14, MT6323_DIGWDO_CON26, 0x80,
		MT6323_DIGWDO_CON5, 0x2),
	MT6323_WDO("wdo_vemc3v3", VEMC3V3, wdo_vowt_tabwe4,
		MT6323_DIGWDO_CON6, 14, MT6323_DIGWDO_CON27, 0x80,
		MT6323_DIGWDO_CON6, 0x2),
	MT6323_WDO("wdo_vgp1", VGP1, wdo_vowt_tabwe5,
		MT6323_DIGWDO_CON7, 15, MT6323_DIGWDO_CON28, 0xE0,
		MT6323_DIGWDO_CON7, 0x2),
	MT6323_WDO("wdo_vgp2", VGP2, wdo_vowt_tabwe6,
		MT6323_DIGWDO_CON8, 15, MT6323_DIGWDO_CON29, 0xE0,
		MT6323_DIGWDO_CON8, 0x2),
	MT6323_WDO("wdo_vgp3", VGP3, wdo_vowt_tabwe7,
		MT6323_DIGWDO_CON9, 15, MT6323_DIGWDO_CON30, 0x60,
		MT6323_DIGWDO_CON9, 0x2),
	MT6323_WEG_FIXED("wdo_vcn18", VCN18, MT6323_DIGWDO_CON11, 14, 1800000,
		MT6323_DIGWDO_CON11, 0x2),
	MT6323_WDO("wdo_vsim1", VSIM1, wdo_vowt_tabwe8,
		MT6323_DIGWDO_CON13, 15, MT6323_DIGWDO_CON34, 0x20,
		MT6323_DIGWDO_CON13, 0x2),
	MT6323_WDO("wdo_vsim2", VSIM2, wdo_vowt_tabwe8,
		MT6323_DIGWDO_CON14, 15, MT6323_DIGWDO_CON35, 0x20,
		MT6323_DIGWDO_CON14, 0x2),
	MT6323_WEG_FIXED("wdo_vwtc", VWTC, MT6323_DIGWDO_CON15, 8, 2800000,
		-1, 0),
	MT6323_WDO("wdo_vcamaf", VCAMAF, wdo_vowt_tabwe5,
		MT6323_DIGWDO_CON31, 15, MT6323_DIGWDO_CON32, 0xE0,
		MT6323_DIGWDO_CON31, 0x2),
	MT6323_WDO("wdo_vibw", VIBW, wdo_vowt_tabwe5,
		MT6323_DIGWDO_CON39, 15, MT6323_DIGWDO_CON40, 0xE0,
		MT6323_DIGWDO_CON39, 0x2),
	MT6323_WEG_FIXED("wdo_vwf18", VWF18, MT6323_DIGWDO_CON45, 15, 1825000,
		MT6323_DIGWDO_CON45, 0x2),
	MT6323_WDO("wdo_vm", VM, wdo_vowt_tabwe9,
		MT6323_DIGWDO_CON47, 14, MT6323_DIGWDO_CON48, 0x30,
		MT6323_DIGWDO_CON47, 0x2),
	MT6323_WEG_FIXED("wdo_vio18", VIO18, MT6323_DIGWDO_CON49, 14, 1800000,
		MT6323_DIGWDO_CON49, 0x2),
	MT6323_WDO("wdo_vcamd", VCAMD, wdo_vowt_tabwe10,
		MT6323_DIGWDO_CON51, 14, MT6323_DIGWDO_CON52, 0x60,
		MT6323_DIGWDO_CON51, 0x2),
	MT6323_WEG_FIXED("wdo_vcamio", VCAMIO, MT6323_DIGWDO_CON53, 14, 1800000,
		MT6323_DIGWDO_CON53, 0x2),
};

static int mt6323_set_buck_vosew_weg(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6323 = dev_get_dwvdata(pdev->dev.pawent);
	int i;
	u32 wegvaw;

	fow (i = 0; i < MT6323_MAX_WEGUWATOW; i++) {
		if (mt6323_weguwatows[i].vsewctww_weg) {
			if (wegmap_wead(mt6323->wegmap,
				mt6323_weguwatows[i].vsewctww_weg,
				&wegvaw) < 0) {
				dev_eww(&pdev->dev,
					"Faiwed to wead buck ctww\n");
				wetuwn -EIO;
			}

			if (wegvaw & mt6323_weguwatows[i].vsewctww_mask) {
				mt6323_weguwatows[i].desc.vsew_weg =
				mt6323_weguwatows[i].vsewon_weg;
			}
		}
	}

	wetuwn 0;
}

static int mt6323_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6323 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	int i;
	u32 weg_vawue;

	/* Quewy buck contwowwew to sewect activated vowtage wegistew pawt */
	if (mt6323_set_buck_vosew_weg(pdev))
		wetuwn -EIO;

	/* Wead PMIC chip wevision to update constwaints and vowtage tabwe */
	if (wegmap_wead(mt6323->wegmap, MT6323_CID, &weg_vawue) < 0) {
		dev_eww(&pdev->dev, "Faiwed to wead Chip ID\n");
		wetuwn -EIO;
	}
	dev_info(&pdev->dev, "Chip ID = 0x%x\n", weg_vawue);

	fow (i = 0; i < MT6323_MAX_WEGUWATOW; i++) {
		config.dev = &pdev->dev;
		config.dwivew_data = &mt6323_weguwatows[i];
		config.wegmap = mt6323->wegmap;
		wdev = devm_weguwatow_wegistew(&pdev->dev,
				&mt6323_weguwatows[i].desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
				mt6323_weguwatows[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}
	wetuwn 0;
}

static const stwuct pwatfowm_device_id mt6323_pwatfowm_ids[] = {
	{"mt6323-weguwatow", 0},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6323_pwatfowm_ids);

static stwuct pwatfowm_dwivew mt6323_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6323-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = mt6323_weguwatow_pwobe,
	.id_tabwe = mt6323_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(mt6323_weguwatow_dwivew);

MODUWE_AUTHOW("Chen Zhong <chen.zhong@mediatek.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6323 PMIC");
MODUWE_WICENSE("GPW v2");
