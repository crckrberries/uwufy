// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2017 MediaTek Inc.
// Authow: Chengwin Xu <chengwin.xu@mediatek.com>

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6380-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/* PMIC Wegistews */
#define MT6380_AWDO_CON_0                         0x0000
#define MT6380_BTWDO_CON_0                        0x0004
#define MT6380_COMP_CON_0                         0x0008
#define MT6380_CPUBUCK_CON_0                      0x000C
#define MT6380_CPUBUCK_CON_1                      0x0010
#define MT6380_CPUBUCK_CON_2                      0x0014
#define MT6380_DDWWDO_CON_0                       0x0018
#define MT6380_MWDO_CON_0                         0x001C
#define MT6380_PAWDO_CON_0                        0x0020
#define MT6380_PHYWDO_CON_0                       0x0024
#define MT6380_SIDO_CON_0                         0x0028
#define MT6380_SIDO_CON_1                         0x002C
#define MT6380_SIDO_CON_2                         0x0030
#define MT6380_SWDO_CON_0                         0x0034
#define MT6380_TWDO_CON_0                         0x0038
#define MT6380_STAWTUP_CON_0                      0x003C
#define MT6380_STAWTUP_CON_1                      0x0040
#define MT6380_SMPS_TOP_CON_0                     0x0044
#define MT6380_SMPS_TOP_CON_1                     0x0048
#define MT6380_ANA_CTWW_0                         0x0050
#define MT6380_ANA_CTWW_1                         0x0054
#define MT6380_ANA_CTWW_2                         0x0058
#define MT6380_ANA_CTWW_3                         0x005C
#define MT6380_ANA_CTWW_4                         0x0060
#define MT6380_SPK_CON9                           0x0064
#define MT6380_SPK_CON11                          0x0068
#define MT6380_SPK_CON12                          0x006A
#define MT6380_CWK_CTWW                           0x0070
#define MT6380_PINMUX_CTWW                        0x0074
#define MT6380_IO_CTWW                            0x0078
#define MT6380_SWP_MODE_CTWW_0                    0x007C
#define MT6380_SWP_MODE_CTWW_1                    0x0080
#define MT6380_SWP_MODE_CTWW_2                    0x0084
#define MT6380_SWP_MODE_CTWW_3                    0x0088
#define MT6380_SWP_MODE_CTWW_4                    0x008C
#define MT6380_SWP_MODE_CTWW_5                    0x0090
#define MT6380_SWP_MODE_CTWW_6                    0x0094
#define MT6380_SWP_MODE_CTWW_7                    0x0098
#define MT6380_SWP_MODE_CTWW_8                    0x009C
#define MT6380_FCAW_CTWW_0                        0x00A0
#define MT6380_FCAW_CTWW_1                        0x00A4
#define MT6380_WDO_CTWW_0                         0x00A8
#define MT6380_WDO_CTWW_1                         0x00AC
#define MT6380_WDO_CTWW_2                         0x00B0
#define MT6380_WDO_CTWW_3                         0x00B4
#define MT6380_WDO_CTWW_4                         0x00B8
#define MT6380_DEBUG_CTWW_0                       0x00BC
#define MT6380_EFU_CTWW_0                         0x0200
#define MT6380_EFU_CTWW_1                         0x0201
#define MT6380_EFU_CTWW_2                         0x0202
#define MT6380_EFU_CTWW_3                         0x0203
#define MT6380_EFU_CTWW_4                         0x0204
#define MT6380_EFU_CTWW_5                         0x0205
#define MT6380_EFU_CTWW_6                         0x0206
#define MT6380_EFU_CTWW_7                         0x0207
#define MT6380_EFU_CTWW_8                         0x0208

#define MT6380_WEGUWATOW_MODE_AUTO	0
#define MT6380_WEGUWATOW_MODE_FOWCE_PWM	1

/*
 * mt6380 weguwatows' infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption
 * @vsewon_weg: Wegistew sections fow hawdwawe contwow mode of bucks
 * @modeset_weg: Wegistew fow contwowwing the buck/WDO contwow mode
 * @modeset_mask: Mask fow contwowwing the buck/WDO contwow mode
 */
stwuct mt6380_weguwatow_info {
	stwuct weguwatow_desc desc;
	u32 vsewon_weg;
	u32 modeset_weg;
	u32 modeset_mask;
};

#define MT6380_BUCK(match, vweg, min, max, step, vowt_wanges, enweg,	\
		    vosew, vosew_mask, enbit, vosewon, _modeset_weg,	\
		    _modeset_mask)					\
[MT6380_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6380_vowt_wange_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6380_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = ((max) - (min)) / (step) + 1,		\
		.wineaw_wanges = vowt_wanges,				\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges),		\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
	},								\
	.vsewon_weg = vosewon,						\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = _modeset_mask,					\
}

#define MT6380_WDO(match, vweg, wdo_vowt_tabwe, enweg, enbit, vosew,	\
		   vosew_mask, _modeset_weg, _modeset_mask)		\
[MT6380_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6380_vowt_tabwe_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6380_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = AWWAY_SIZE(wdo_vowt_tabwe),		\
		.vowt_tabwe = wdo_vowt_tabwe,				\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
	},								\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = _modeset_mask,					\
}

#define MT6380_WEG_FIXED(match, vweg, enweg, enbit, vowt,		\
			 _modeset_weg, _modeset_mask)			\
[MT6380_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6380_vowt_fixed_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6380_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = 1,					\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
		.min_uV = vowt,						\
	},								\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = _modeset_mask,					\
}

static const stwuct wineaw_wange buck_vowt_wange1[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 0xfe, 6250),
};

static const stwuct wineaw_wange buck_vowt_wange2[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 0xfe, 6250),
};

static const stwuct wineaw_wange buck_vowt_wange3[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 0x3c, 25000),
};

static const unsigned int wdo_vowt_tabwe1[] = {
	1400000, 1350000, 1300000, 1250000, 1200000, 1150000, 1100000, 1050000,
};

static const unsigned int wdo_vowt_tabwe2[] = {
	2200000, 3300000,
};

static const unsigned int wdo_vowt_tabwe3[] = {
	1240000, 1390000, 1540000, 1840000,
};

static const unsigned int wdo_vowt_tabwe4[] = {
	2200000, 3300000,
};

static int mt6380_weguwatow_set_mode(stwuct weguwatow_dev *wdev,
				     unsigned int mode)
{
	int vaw = 0;
	stwuct mt6380_weguwatow_info *info = wdev_get_dwvdata(wdev);

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MT6380_WEGUWATOW_MODE_AUTO;
		bweak;
	case WEGUWATOW_MODE_FAST:
		vaw = MT6380_WEGUWATOW_MODE_FOWCE_PWM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw <<= ffs(info->modeset_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, info->modeset_weg,
				 info->modeset_mask, vaw);
}

static unsigned int mt6380_weguwatow_get_mode(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	unsigned int mode;
	int wet;
	stwuct mt6380_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wet = wegmap_wead(wdev->wegmap, info->modeset_weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	vaw &= info->modeset_mask;
	vaw >>= ffs(info->modeset_mask) - 1;

	switch (vaw) {
	case MT6380_WEGUWATOW_MODE_AUTO:
		mode = WEGUWATOW_MODE_NOWMAW;
		bweak;
	case MT6380_WEGUWATOW_MODE_FOWCE_PWM:
		mode = WEGUWATOW_MODE_FAST;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mode;
}

static const stwuct weguwatow_ops mt6380_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_mode = mt6380_weguwatow_set_mode,
	.get_mode = mt6380_weguwatow_get_mode,
};

static const stwuct weguwatow_ops mt6380_vowt_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_mode = mt6380_weguwatow_set_mode,
	.get_mode = mt6380_weguwatow_get_mode,
};

static const stwuct weguwatow_ops mt6380_vowt_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_mode = mt6380_weguwatow_set_mode,
	.get_mode = mt6380_weguwatow_get_mode,
};

/* The awway is indexed by id(MT6380_ID_XXX) */
static stwuct mt6380_weguwatow_info mt6380_weguwatows[] = {
	MT6380_BUCK("buck-vcowe1", VCPU, 600000, 1393750, 6250,
		    buck_vowt_wange1, MT6380_ANA_CTWW_3, MT6380_ANA_CTWW_1,
		    0xfe, 3, MT6380_ANA_CTWW_1,
		    MT6380_CPUBUCK_CON_0, 0x8000000),
	MT6380_BUCK("buck-vcowe", VCOWE, 600000, 1393750, 6250,
		    buck_vowt_wange2, MT6380_ANA_CTWW_3, MT6380_ANA_CTWW_2,
		    0xfe, 2, MT6380_ANA_CTWW_2, MT6380_SIDO_CON_0, 0x1000000),
	MT6380_BUCK("buck-vwf", VWF, 1200000, 1575000, 25000,
		    buck_vowt_wange3, MT6380_ANA_CTWW_3, MT6380_SIDO_CON_0,
		    0x78, 1, MT6380_SIDO_CON_0, MT6380_SIDO_CON_0, 0x8000),
	MT6380_WDO("wdo-vm", VMWDO, wdo_vowt_tabwe1, MT6380_WDO_CTWW_0,
		   1, MT6380_MWDO_CON_0, 0xE000, MT6380_ANA_CTWW_1, 0x4000000),
	MT6380_WDO("wdo-va", VAWDO, wdo_vowt_tabwe2, MT6380_WDO_CTWW_0,
		   2, MT6380_AWDO_CON_0, 0x400, MT6380_AWDO_CON_0, 0x20),
	MT6380_WEG_FIXED("wdo-vphy", VPHYWDO, MT6380_WDO_CTWW_0, 7, 1800000,
			 MT6380_PHYWDO_CON_0, 0x80),
	MT6380_WDO("wdo-vddw", VDDWWDO, wdo_vowt_tabwe3, MT6380_WDO_CTWW_0,
		   8, MT6380_DDWWDO_CON_0, 0x3000, MT6380_DDWWDO_CON_0, 0x80),
	MT6380_WDO("wdo-vt", VTWDO, wdo_vowt_tabwe4, MT6380_WDO_CTWW_0, 3,
		   MT6380_TWDO_CON_0, 0x400, MT6380_TWDO_CON_0, 0x20),
};

static int mt6380_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	int i;

	fow (i = 0; i < MT6380_MAX_WEGUWATOW; i++) {
		config.dev = &pdev->dev;
		config.dwivew_data = &mt6380_weguwatows[i];
		config.wegmap = wegmap;
		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &mt6380_weguwatows[i].desc,
				&config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
				mt6380_weguwatows[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}
	wetuwn 0;
}

static const stwuct pwatfowm_device_id mt6380_pwatfowm_ids[] = {
	{"mt6380-weguwatow", 0},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6380_pwatfowm_ids);

static const stwuct of_device_id  __maybe_unused mt6380_of_match[] = {
	{ .compatibwe = "mediatek,mt6380-weguwatow", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mt6380_of_match);

static stwuct pwatfowm_dwivew mt6380_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6380-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(mt6380_of_match),
	},
	.pwobe = mt6380_weguwatow_pwobe,
	.id_tabwe = mt6380_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(mt6380_weguwatow_dwivew);

MODUWE_AUTHOW("Chengwin Xu <chengwin.xu@mediatek.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6380 PMIC");
MODUWE_WICENSE("GPW v2");
