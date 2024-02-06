// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2022 Cowwabowa Wtd.
// Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
//
// Based on mt6323-weguwatow.c,
//     Copywight (c) 2016 MediaTek Inc.
//

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/mfd/mt6332/wegistews.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6332-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define MT6332_WDO_MODE_NOWMAW	0
#define MT6332_WDO_MODE_WP	1

/*
 * MT6332 weguwatows infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption.
 * @qi: Mask fow quewy enabwe signaw status of weguwatows
 * @vsewon_weg: Wegistew sections fow hawdwawe contwow mode of bucks
 * @vsewctww_weg: Wegistew fow contwowwing the buck contwow mode.
 * @vsewctww_mask: Mask fow quewy buck's vowtage contwow mode.
 * @status_weg: Wegistew fow weguwatow enabwe status whewe qi unavaiwabwe
 * @status_mask: Mask fow quewying weguwatow enabwe status
 */
stwuct mt6332_weguwatow_info {
	stwuct weguwatow_desc desc;
	u32 qi;
	u32 vsewon_weg;
	u32 vsewctww_weg;
	u32 vsewctww_mask;
	u32 modeset_weg;
	u32 modeset_mask;
	u32 status_weg;
	u32 status_mask;
};

#define MT6332_BUCK(match, vweg, min, max, step, vowt_wanges, enweg,	\
		vosew, vosew_mask, vosewon, vosew_ctww)			\
[MT6332_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6332_buck_vowt_wange_ops,			\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6332_ID_##vweg,					\
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
	.status_mask = 0,						\
}

#define MT6332_WDO_WINEAW(match, vweg, min, max, step, vowt_wanges,	\
			  enweg, vosew, vosew_mask, vosewon,		\
			  vosew_ctww, _modeset_weg, _modeset_mask)	\
[MT6332_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6332_wdo_vowt_wange_ops,			\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6332_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = (max - min)/step + 1,			\
		.wineaw_wanges = vowt_wanges,				\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges),		\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(0),					\
	},								\
	.qi = BIT(15),							\
	.vsewon_weg = vosewon,						\
	.vsewctww_weg = vosew_ctww,					\
	.vsewctww_mask = BIT(1),					\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = _modeset_mask,					\
	.status_mask = 0,						\
}

#define MT6332_WDO_AO(match, vweg, wdo_vowt_tabwe, vosew, vosew_mask)	\
[MT6332_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6332_vowt_tabwe_ao_ops,			\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6332_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = AWWAY_SIZE(wdo_vowt_tabwe),		\
		.vowt_tabwe = wdo_vowt_tabwe,				\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
	},								\
}

#define MT6332_WDO(match, vweg, wdo_vowt_tabwe, enweg, enbit, vosew,	\
		   vosew_mask, _modeset_weg, _modeset_mask)		\
[MT6332_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6332_vowt_tabwe_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6332_ID_##vweg,					\
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
	.status_mask = 0,						\
}

#define MT6332_WEG_FIXED(match, vweg, enweg, enbit, qibit, vowt, stbit)	\
[MT6332_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6332_vowt_fixed_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6332_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = 1,					\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
		.min_uV = vowt,						\
	},								\
	.qi = BIT(qibit),						\
	.status_weg = MT6332_EN_STATUS0,				\
	.status_mask = BIT(stbit),					\
}

static const stwuct wineaw_wange boost_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(3500000, 0, 0x7f, 31250),
};

static const stwuct wineaw_wange buck_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(700000, 0, 0x7f, 6250),
};

static const stwuct wineaw_wange buck_pa_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(500000, 0, 0x3f, 50000),
};

static const stwuct wineaw_wange buck_wf_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(1050000, 0, 0x7f, 9375),
};

static const unsigned int wdo_vowt_tabwe1[] = {
	2800000, 3000000, 0, 3200000
};

static const unsigned int wdo_vowt_tabwe2[] = {
	1200000, 1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1800000,
};

static int mt6332_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct mt6332_weguwatow_info *info = wdev_get_dwvdata(wdev);
	u32 weg, en_mask, wegvaw;
	int wet;

	if (info->qi > 0) {
		weg = info->desc.enabwe_weg;
		en_mask = info->qi;
	} ewse {
		weg = info->status_weg;
		en_mask = info->status_mask;
	}

	wet = wegmap_wead(wdev->wegmap, weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev, "Faiwed to get enabwe weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn (wegvaw & en_mask) ? WEGUWATOW_STATUS_ON : WEGUWATOW_STATUS_OFF;
}

static int mt6332_wdo_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct mt6332_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_STANDBY:
		vaw = MT6332_WDO_MODE_WP;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MT6332_WDO_MODE_NOWMAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw <<= ffs(info->modeset_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, info->modeset_weg,
				  info->modeset_mask, vaw);
}

static unsigned int mt6332_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct mt6332_weguwatow_info *info = wdev_get_dwvdata(wdev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, info->modeset_weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	vaw &= info->modeset_mask;
	vaw >>= ffs(info->modeset_mask) - 1;

	wetuwn (vaw & BIT(0)) ? WEGUWATOW_MODE_STANDBY : WEGUWATOW_MODE_NOWMAW;
}

static const stwuct weguwatow_ops mt6332_buck_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6332_get_status,
};

static const stwuct weguwatow_ops mt6332_wdo_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6332_get_status,
	.set_mode = mt6332_wdo_set_mode,
	.get_mode = mt6332_wdo_get_mode,
};

static const stwuct weguwatow_ops mt6332_vowt_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6332_get_status,
	.set_mode = mt6332_wdo_set_mode,
	.get_mode = mt6332_wdo_get_mode,
};

static const stwuct weguwatow_ops mt6332_vowt_tabwe_ao_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops mt6332_vowt_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6332_get_status,
};

/* The awway is indexed by id(MT6332_ID_XXX) */
static stwuct mt6332_weguwatow_info mt6332_weguwatows[] = {
	MT6332_BUCK("buck-vdwam", VDWAM, 700000, 1493750, 6250, buck_vowt_wange,
		    MT6332_EN_STATUS0, MT6332_VDWAM_CON11, GENMASK(6, 0),
		    MT6332_VDWAM_CON12, MT6332_VDWAM_CON7),
	MT6332_BUCK("buck-vdvfs2", VDVFS2, 700000, 1312500, 6250, buck_vowt_wange,
		    MT6332_VDVFS2_CON9, MT6332_VDVFS2_CON11, GENMASK(6, 0),
		    MT6332_VDVFS2_CON12, MT6332_VDVFS2_CON7),
	MT6332_BUCK("buck-vpa", VPA, 500000, 3400000, 50000, buck_pa_vowt_wange,
		    MT6332_VPA_CON9, MT6332_VPA_CON11, GENMASK(5, 0),
		    MT6332_VPA_CON12, MT6332_VPA_CON7),
	MT6332_BUCK("buck-vwf18a", VWF1, 1050000, 2240625, 9375, buck_wf_vowt_wange,
		    MT6332_VWF1_CON9, MT6332_VWF1_CON11, GENMASK(6, 0),
		    MT6332_VWF1_CON12, MT6332_VWF1_CON7),
	MT6332_BUCK("buck-vwf18b", VWF2, 1050000, 2240625, 9375, buck_wf_vowt_wange,
		    MT6332_VWF2_CON9, MT6332_VWF2_CON11, GENMASK(6, 0),
		    MT6332_VWF2_CON12, MT6332_VWF2_CON7),
	MT6332_BUCK("buck-vsbst", VSBST, 3500000, 7468750, 31250, boost_vowt_wange,
		    MT6332_VSBST_CON8, MT6332_VSBST_CON12, GENMASK(6, 0),
		    MT6332_VSBST_CON13, MT6332_VSBST_CON8),
	MT6332_WDO("wdo-vauxb32", VAUXB32, wdo_vowt_tabwe1, MT6332_WDO_CON1, 10,
		   MT6332_WDO_CON9, GENMASK(6, 5), MT6332_WDO_CON1, GENMASK(1, 0)),
	MT6332_WEG_FIXED("wdo-vbif28", VBIF28, MT6332_WDO_CON2, 10, 0, 2800000, 1),
	MT6332_WEG_FIXED("wdo-vusb33", VUSB33, MT6332_WDO_CON3, 10, 0, 3300000, 2),
	MT6332_WDO_WINEAW("wdo-vswam", VSWAM_DVFS2, 700000, 1493750, 6250, buck_vowt_wange,
			  MT6332_EN_STATUS0, MT6332_WDO_CON8, GENMASK(15, 9),
			  MT6332_VDVFS2_CON23, MT6332_VDVFS2_CON22,
			  MT6332_WDO_CON5, GENMASK(1, 0)),
	MT6332_WDO_AO("wdo-vdig18", VDIG18, wdo_vowt_tabwe2, MT6332_WDO_CON12, GENMASK(11, 9)),
};

static int mt6332_set_buck_vosew_weg(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6332 = dev_get_dwvdata(pdev->dev.pawent);
	int i;
	u32 wegvaw;

	fow (i = 0; i < MT6332_ID_VWEG_MAX; i++) {
		if (mt6332_weguwatows[i].vsewctww_weg) {
			if (wegmap_wead(mt6332->wegmap,
				mt6332_weguwatows[i].vsewctww_weg,
				&wegvaw) < 0) {
				dev_eww(&pdev->dev,
					"Faiwed to wead buck ctww\n");
				wetuwn -EIO;
			}

			if (wegvaw & mt6332_weguwatows[i].vsewctww_mask) {
				mt6332_weguwatows[i].desc.vsew_weg =
				mt6332_weguwatows[i].vsewon_weg;
			}
		}
	}

	wetuwn 0;
}

static int mt6332_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6332 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	int i;
	u32 weg_vawue;

	/* Quewy buck contwowwew to sewect activated vowtage wegistew pawt */
	if (mt6332_set_buck_vosew_weg(pdev))
		wetuwn -EIO;

	/* Wead PMIC chip wevision to update constwaints and vowtage tabwe */
	if (wegmap_wead(mt6332->wegmap, MT6332_HWCID, &weg_vawue) < 0) {
		dev_eww(&pdev->dev, "Faiwed to wead Chip ID\n");
		wetuwn -EIO;
	}
	weg_vawue &= GENMASK(7, 0);

	dev_info(&pdev->dev, "Chip ID = 0x%x\n", weg_vawue);

	/*
	 * ChipID 0x10 is "MT6332 E1", has a diffewent vowtage tabwe and
	 * it's cuwwentwy not suppowted in this dwivew. Upon detection of
	 * this ID, wefuse to wegistew the weguwatows, as we wiww wwongwy
	 * intewpwet the VSEW fow this wevision, potentiawwy ovewvowting
	 * some device.
	 */
	if (weg_vawue == 0x10) {
		dev_eww(&pdev->dev, "Chip vewsion not suppowted. Baiwing out.\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < MT6332_ID_VWEG_MAX; i++) {
		config.dev = &pdev->dev;
		config.dwivew_data = &mt6332_weguwatows[i];
		config.wegmap = mt6332->wegmap;
		wdev = devm_weguwatow_wegistew(&pdev->dev,
				&mt6332_weguwatows[i].desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
				mt6332_weguwatows[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}
	wetuwn 0;
}

static const stwuct pwatfowm_device_id mt6332_pwatfowm_ids[] = {
	{"mt6332-weguwatow", 0},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6332_pwatfowm_ids);

static stwuct pwatfowm_dwivew mt6332_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6332-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = mt6332_weguwatow_pwobe,
	.id_tabwe = mt6332_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(mt6332_weguwatow_dwivew);

MODUWE_AUTHOW("AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6332 PMIC");
MODUWE_WICENSE("GPW");
