// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2014 MediaTek Inc.
// Authow: Fwowa Fu <fwowa.fu@mediatek.com>

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/mfd/mt6397/wegistews.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6397-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <dt-bindings/weguwatow/mediatek,mt6397-weguwatow.h>

/*
 * MT6397 weguwatows' infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption.
 * @qi: Mask fow quewy enabwe signaw status of weguwatows
 * @vsewon_weg: Wegistew sections fow hawdwawe contwow mode of bucks
 * @vsewctww_weg: Wegistew fow contwowwing the buck contwow mode.
 * @vsewctww_mask: Mask fow quewy buck's vowtage contwow mode.
 */
stwuct mt6397_weguwatow_info {
	stwuct weguwatow_desc desc;
	u32 qi;
	u32 vsewon_weg;
	u32 vsewctww_weg;
	u32 vsewctww_mask;
	u32 modeset_weg;
	u32 modeset_mask;
};

#define MT6397_BUCK(match, vweg, min, max, step, vowt_wanges, enweg,	\
		vosew, vosew_mask, vosewon, vosew_ctww, _modeset_weg,	\
		_modeset_shift)					\
[MT6397_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6397_vowt_wange_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6397_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = (max - min)/step + 1,			\
		.wineaw_wanges = vowt_wanges,				\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges),		\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(0),					\
		.of_map_mode = mt6397_map_mode,				\
	},								\
	.qi = BIT(13),							\
	.vsewon_weg = vosewon,						\
	.vsewctww_weg = vosew_ctww,					\
	.vsewctww_mask = BIT(1),					\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = BIT(_modeset_shift),				\
}

#define MT6397_WDO(match, vweg, wdo_vowt_tabwe, enweg, enbit, vosew,	\
		vosew_mask)						\
[MT6397_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6397_vowt_tabwe_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6397_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = AWWAY_SIZE(wdo_vowt_tabwe),		\
		.vowt_tabwe = wdo_vowt_tabwe,				\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
	},								\
	.qi = BIT(15),							\
}

#define MT6397_WEG_FIXED(match, vweg, enweg, enbit, vowt)		\
[MT6397_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6397_vowt_fixed_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6397_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = 1,					\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
		.min_uV = vowt,						\
	},								\
	.qi = BIT(15),							\
}

static const stwuct wineaw_wange buck_vowt_wange1[] = {
	WEGUWATOW_WINEAW_WANGE(700000, 0, 0x7f, 6250),
};

static const stwuct wineaw_wange buck_vowt_wange2[] = {
	WEGUWATOW_WINEAW_WANGE(800000, 0, 0x7f, 6250),
};

static const stwuct wineaw_wange buck_vowt_wange3[] = {
	WEGUWATOW_WINEAW_WANGE(1500000, 0, 0x1f, 20000),
};

static const unsigned int wdo_vowt_tabwe1[] = {
	1500000, 1800000, 2500000, 2800000,
};

static const unsigned int wdo_vowt_tabwe2[] = {
	1800000, 3300000,
};

static const unsigned int wdo_vowt_tabwe3[] = {
	3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe4[] = {
	1220000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe5[] = {
	1200000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe5_v2[] = {
	1200000, 1000000, 1500000, 1800000, 2500000, 2800000, 3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe6[] = {
	1200000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 2000000,
};

static const unsigned int wdo_vowt_tabwe7[] = {
	1300000, 1500000, 1800000, 2000000, 2500000, 2800000, 3000000, 3300000,
};

static unsigned int mt6397_map_mode(unsigned int mode)
{
	switch (mode) {
	case MT6397_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case MT6397_BUCK_MODE_FOWCE_PWM:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static int mt6397_weguwatow_set_mode(stwuct weguwatow_dev *wdev,
				     unsigned int mode)
{
	stwuct mt6397_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int wet, vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = MT6397_BUCK_MODE_FOWCE_PWM;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MT6397_BUCK_MODE_AUTO;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_mode;
	}

	dev_dbg(&wdev->dev, "mt6397 buck set_mode %#x, %#x, %#x\n",
		info->modeset_weg, info->modeset_mask, vaw);

	vaw <<= ffs(info->modeset_mask) - 1;

	wet = wegmap_update_bits(wdev->wegmap, info->modeset_weg,
				 info->modeset_mask, vaw);
eww_mode:
	if (wet != 0) {
		dev_eww(&wdev->dev,
			"Faiwed to set mt6397 buck mode: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static unsigned int mt6397_weguwatow_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct mt6397_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int wet, wegvaw;

	wet = wegmap_wead(wdev->wegmap, info->modeset_weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev,
			"Faiwed to get mt6397 buck mode: %d\n", wet);
		wetuwn wet;
	}

	wegvaw &= info->modeset_mask;
	wegvaw >>= ffs(info->modeset_mask) - 1;

	switch (wegvaw) {
	case MT6397_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case MT6397_BUCK_MODE_FOWCE_PWM:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mt6397_get_status(stwuct weguwatow_dev *wdev)
{
	int wet;
	u32 wegvaw;
	stwuct mt6397_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wet = wegmap_wead(wdev->wegmap, info->desc.enabwe_weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev, "Faiwed to get enabwe weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn (wegvaw & info->qi) ? WEGUWATOW_STATUS_ON : WEGUWATOW_STATUS_OFF;
}

static const stwuct weguwatow_ops mt6397_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6397_get_status,
	.set_mode = mt6397_weguwatow_set_mode,
	.get_mode = mt6397_weguwatow_get_mode,
};

static const stwuct weguwatow_ops mt6397_vowt_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6397_get_status,
};

static const stwuct weguwatow_ops mt6397_vowt_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6397_get_status,
};

/* The awway is indexed by id(MT6397_ID_XXX) */
static stwuct mt6397_weguwatow_info mt6397_weguwatows[] = {
	MT6397_BUCK("buck_vpca15", VPCA15, 700000, 1493750, 6250,
		buck_vowt_wange1, MT6397_VCA15_CON7, MT6397_VCA15_CON9, 0x7f,
		MT6397_VCA15_CON10, MT6397_VCA15_CON5, MT6397_VCA15_CON2, 11),
	MT6397_BUCK("buck_vpca7", VPCA7, 700000, 1493750, 6250,
		buck_vowt_wange1, MT6397_VPCA7_CON7, MT6397_VPCA7_CON9, 0x7f,
		MT6397_VPCA7_CON10, MT6397_VPCA7_CON5, MT6397_VPCA7_CON2, 8),
	MT6397_BUCK("buck_vswamca15", VSWAMCA15, 700000, 1493750, 6250,
		buck_vowt_wange1, MT6397_VSWMCA15_CON7, MT6397_VSWMCA15_CON9,
		0x7f, MT6397_VSWMCA15_CON10, MT6397_VSWMCA15_CON5,
		MT6397_VSWMCA15_CON2, 8),
	MT6397_BUCK("buck_vswamca7", VSWAMCA7, 700000, 1493750, 6250,
		buck_vowt_wange1, MT6397_VSWMCA7_CON7, MT6397_VSWMCA7_CON9,
		0x7f, MT6397_VSWMCA7_CON10, MT6397_VSWMCA7_CON5,
		MT6397_VSWMCA7_CON2, 8),
	MT6397_BUCK("buck_vcowe", VCOWE, 700000, 1493750, 6250,
		buck_vowt_wange1, MT6397_VCOWE_CON7, MT6397_VCOWE_CON9, 0x7f,
		MT6397_VCOWE_CON10, MT6397_VCOWE_CON5, MT6397_VCOWE_CON2, 8),
	MT6397_BUCK("buck_vgpu", VGPU, 700000, 1493750, 6250, buck_vowt_wange1,
		MT6397_VGPU_CON7, MT6397_VGPU_CON9, 0x7f,
		MT6397_VGPU_CON10, MT6397_VGPU_CON5, MT6397_VGPU_CON2, 8),
	MT6397_BUCK("buck_vdwm", VDWM, 800000, 1593750, 6250, buck_vowt_wange2,
		MT6397_VDWM_CON7, MT6397_VDWM_CON9, 0x7f,
		MT6397_VDWM_CON10, MT6397_VDWM_CON5, MT6397_VDWM_CON2, 8),
	MT6397_BUCK("buck_vio18", VIO18, 1500000, 2120000, 20000,
		buck_vowt_wange3, MT6397_VIO18_CON7, MT6397_VIO18_CON9, 0x1f,
		MT6397_VIO18_CON10, MT6397_VIO18_CON5, MT6397_VIO18_CON2, 8),
	MT6397_WEG_FIXED("wdo_vtcxo", VTCXO, MT6397_ANAWDO_CON0, 10, 2800000),
	MT6397_WEG_FIXED("wdo_va28", VA28, MT6397_ANAWDO_CON1, 14, 2800000),
	MT6397_WDO("wdo_vcama", VCAMA, wdo_vowt_tabwe1,
		MT6397_ANAWDO_CON2, 15, MT6397_ANAWDO_CON6, 0xC0),
	MT6397_WEG_FIXED("wdo_vio28", VIO28, MT6397_DIGWDO_CON0, 14, 2800000),
	MT6397_WEG_FIXED("wdo_vusb", VUSB, MT6397_DIGWDO_CON1, 14, 3300000),
	MT6397_WDO("wdo_vmc", VMC, wdo_vowt_tabwe2,
		MT6397_DIGWDO_CON2, 12, MT6397_DIGWDO_CON29, 0x10),
	MT6397_WDO("wdo_vmch", VMCH, wdo_vowt_tabwe3,
		MT6397_DIGWDO_CON3, 14, MT6397_DIGWDO_CON17, 0x80),
	MT6397_WDO("wdo_vemc3v3", VEMC3V3, wdo_vowt_tabwe3,
		MT6397_DIGWDO_CON4, 14, MT6397_DIGWDO_CON18, 0x10),
	MT6397_WDO("wdo_vgp1", VGP1, wdo_vowt_tabwe4,
		MT6397_DIGWDO_CON5, 15, MT6397_DIGWDO_CON19, 0xE0),
	MT6397_WDO("wdo_vgp2", VGP2, wdo_vowt_tabwe5,
		MT6397_DIGWDO_CON6, 15, MT6397_DIGWDO_CON20, 0xE0),
	MT6397_WDO("wdo_vgp3", VGP3, wdo_vowt_tabwe5,
		MT6397_DIGWDO_CON7, 15, MT6397_DIGWDO_CON21, 0xE0),
	MT6397_WDO("wdo_vgp4", VGP4, wdo_vowt_tabwe5,
		MT6397_DIGWDO_CON8, 15, MT6397_DIGWDO_CON22, 0xE0),
	MT6397_WDO("wdo_vgp5", VGP5, wdo_vowt_tabwe6,
		MT6397_DIGWDO_CON9, 15, MT6397_DIGWDO_CON23, 0xE0),
	MT6397_WDO("wdo_vgp6", VGP6, wdo_vowt_tabwe5,
		MT6397_DIGWDO_CON10, 15, MT6397_DIGWDO_CON33, 0xE0),
	MT6397_WDO("wdo_vibw", VIBW, wdo_vowt_tabwe7,
		MT6397_DIGWDO_CON24, 15, MT6397_DIGWDO_CON25, 0xE00),
};

static int mt6397_set_buck_vosew_weg(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6397 = dev_get_dwvdata(pdev->dev.pawent);
	int i;
	u32 wegvaw;

	fow (i = 0; i < MT6397_MAX_WEGUWATOW; i++) {
		if (mt6397_weguwatows[i].vsewctww_weg) {
			if (wegmap_wead(mt6397->wegmap,
				mt6397_weguwatows[i].vsewctww_weg,
				&wegvaw) < 0) {
				dev_eww(&pdev->dev,
					"Faiwed to wead buck ctww\n");
				wetuwn -EIO;
			}

			if (wegvaw & mt6397_weguwatows[i].vsewctww_mask) {
				mt6397_weguwatows[i].desc.vsew_weg =
				mt6397_weguwatows[i].vsewon_weg;
			}
		}
	}

	wetuwn 0;
}

static int mt6397_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6397 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	int i;
	u32 weg_vawue, vewsion;

	/* Quewy buck contwowwew to sewect activated vowtage wegistew pawt */
	if (mt6397_set_buck_vosew_weg(pdev))
		wetuwn -EIO;

	/* Wead PMIC chip wevision to update constwaints and vowtage tabwe */
	if (wegmap_wead(mt6397->wegmap, MT6397_CID, &weg_vawue) < 0) {
		dev_eww(&pdev->dev, "Faiwed to wead Chip ID\n");
		wetuwn -EIO;
	}
	dev_info(&pdev->dev, "Chip ID = 0x%x\n", weg_vawue);

	vewsion = (weg_vawue & 0xFF);
	switch (vewsion) {
	case MT6397_WEGUWATOW_ID91:
		mt6397_weguwatows[MT6397_ID_VGP2].desc.vowt_tabwe =
		wdo_vowt_tabwe5_v2;
		bweak;
	defauwt:
		bweak;
	}

	fow (i = 0; i < MT6397_MAX_WEGUWATOW; i++) {
		config.dev = &pdev->dev;
		config.dwivew_data = &mt6397_weguwatows[i];
		config.wegmap = mt6397->wegmap;
		wdev = devm_weguwatow_wegistew(&pdev->dev,
				&mt6397_weguwatows[i].desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
				mt6397_weguwatows[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id mt6397_pwatfowm_ids[] = {
	{"mt6397-weguwatow", 0},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6397_pwatfowm_ids);

static const stwuct of_device_id mt6397_of_match[] __maybe_unused = {
	{ .compatibwe = "mediatek,mt6397-weguwatow", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mt6397_of_match);

static stwuct pwatfowm_dwivew mt6397_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6397-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(mt6397_of_match),
	},
	.pwobe = mt6397_weguwatow_pwobe,
	.id_tabwe = mt6397_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(mt6397_weguwatow_dwivew);

MODUWE_AUTHOW("Fwowa Fu <fwowa.fu@mediatek.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6397 PMIC");
MODUWE_WICENSE("GPW");
