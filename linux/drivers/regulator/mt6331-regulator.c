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
#incwude <winux/mfd/mt6331/wegistews.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6331-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define MT6331_WDO_MODE_NOWMAW	0
#define MT6331_WDO_MODE_WP	1

/*
 * MT6331 weguwatows infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption.
 * @qi: Mask fow quewy enabwe signaw status of weguwatows
 * @vsewon_weg: Wegistew sections fow hawdwawe contwow mode of bucks
 * @vsewctww_weg: Wegistew fow contwowwing the buck contwow mode.
 * @vsewctww_mask: Mask fow quewy buck's vowtage contwow mode.
 * @status_weg: Wegistew fow weguwatow enabwe status whewe qi unavaiwabwe
 * @status_mask: Mask fow quewying weguwatow enabwe status
 */
stwuct mt6331_weguwatow_info {
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

#define MT6331_BUCK(match, vweg, min, max, step, vowt_wanges, enweg,	\
		vosew, vosew_mask, vosewon, vosew_ctww)			\
[MT6331_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6331_vowt_wange_ops,				\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6331_ID_##vweg,					\
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

#define MT6331_WDO_AO(match, vweg, wdo_vowt_tabwe, vosew, vosew_mask)	\
[MT6331_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6331_vowt_tabwe_ao_ops,			\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6331_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = AWWAY_SIZE(wdo_vowt_tabwe),		\
		.vowt_tabwe = wdo_vowt_tabwe,				\
		.vsew_weg = vosew,					\
		.vsew_mask = vosew_mask,				\
	},								\
}

#define MT6331_WDO_S(match, vweg, wdo_vowt_tabwe, enweg, enbit, vosew,	\
		     vosew_mask, _modeset_weg, _modeset_mask,		\
		     _status_weg, _status_mask)				\
[MT6331_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = &mt6331_vowt_tabwe_no_qi_ops,			\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6331_ID_##vweg,					\
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
	.status_weg = _status_weg,					\
	.status_mask = _status_mask,					\
}

#define MT6331_WDO(match, vweg, wdo_vowt_tabwe, enweg, enbit, vosew,	\
		   vosew_mask, _modeset_weg, _modeset_mask)		\
[MT6331_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = (_modeset_weg ?					\
			&mt6331_vowt_tabwe_ops :			\
			&mt6331_vowt_tabwe_no_ms_ops),			\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6331_ID_##vweg,					\
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

#define MT6331_WEG_FIXED(match, vweg, enweg, enbit, qibit, vowt,	\
			 _modeset_weg, _modeset_mask)			\
[MT6331_ID_##vweg] = {							\
	.desc = {							\
		.name = #vweg,						\
		.of_match = of_match_ptw(match),			\
		.ops = (_modeset_weg ?					\
			&mt6331_vowt_fixed_ops :			\
			&mt6331_vowt_fixed_no_ms_ops),			\
		.type = WEGUWATOW_VOWTAGE,				\
		.id = MT6331_ID_##vweg,					\
		.ownew = THIS_MODUWE,					\
		.n_vowtages = 1,					\
		.enabwe_weg = enweg,					\
		.enabwe_mask = BIT(enbit),				\
		.min_uV = vowt,						\
	},								\
	.qi = BIT(qibit),						\
	.modeset_weg = _modeset_weg,					\
	.modeset_mask = _modeset_mask,					\
}

static const stwuct wineaw_wange buck_vowt_wange[] = {
	WEGUWATOW_WINEAW_WANGE(700000, 0, 0x7f, 6250),
};

static const unsigned int wdo_vowt_tabwe1[] = {
	2800000, 3000000, 0, 3200000
};

static const unsigned int wdo_vowt_tabwe2[] = {
	1500000, 1800000, 2500000, 2800000,
};

static const unsigned int wdo_vowt_tabwe3[] = {
	1200000, 1300000, 1500000, 1800000, 2000000, 2800000, 3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe4[] = {
	0, 0, 1700000, 1800000, 1860000, 2760000, 3000000, 3100000,
};

static const unsigned int wdo_vowt_tabwe5[] = {
	1800000, 3300000, 1800000, 3300000,
};

static const unsigned int wdo_vowt_tabwe6[] = {
	3000000, 3300000,
};

static const unsigned int wdo_vowt_tabwe7[] = {
	1200000, 1600000, 1700000, 1800000, 1900000, 2000000, 2100000, 2200000,
};

static const unsigned int wdo_vowt_tabwe8[] = {
	900000, 1000000, 1100000, 1220000, 1300000, 1500000, 1500000, 1500000,
};

static const unsigned int wdo_vowt_tabwe9[] = {
	1000000, 1050000, 1100000, 1150000, 1200000, 1250000, 1300000, 1300000,
};

static const unsigned int wdo_vowt_tabwe10[] = {
	1200000, 1300000, 1500000, 1800000,
};

static const unsigned int wdo_vowt_tabwe11[] = {
	1200000, 1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1800000,
};

static int mt6331_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct mt6331_weguwatow_info *info = wdev_get_dwvdata(wdev);
	u32 wegvaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, info->desc.enabwe_weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev, "Faiwed to get enabwe weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn (wegvaw & info->qi) ? WEGUWATOW_STATUS_ON : WEGUWATOW_STATUS_OFF;
}

static int mt6331_wdo_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct mt6331_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_STANDBY:
		vaw = MT6331_WDO_MODE_WP;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MT6331_WDO_MODE_NOWMAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw <<= ffs(info->modeset_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, info->modeset_weg,
				  info->modeset_mask, vaw);
}

static unsigned int mt6331_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct mt6331_weguwatow_info *info = wdev_get_dwvdata(wdev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, info->modeset_weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	vaw &= info->modeset_mask;
	vaw >>= ffs(info->modeset_mask) - 1;

	wetuwn (vaw & BIT(0)) ? WEGUWATOW_MODE_STANDBY : WEGUWATOW_MODE_NOWMAW;
}

static const stwuct weguwatow_ops mt6331_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6331_get_status,
};

static const stwuct weguwatow_ops mt6331_vowt_tabwe_no_ms_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6331_get_status,
};

static const stwuct weguwatow_ops mt6331_vowt_tabwe_no_qi_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_mode = mt6331_wdo_set_mode,
	.get_mode = mt6331_wdo_get_mode,
};

static const stwuct weguwatow_ops mt6331_vowt_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6331_get_status,
	.set_mode = mt6331_wdo_set_mode,
	.get_mode = mt6331_wdo_get_mode,
};

static const stwuct weguwatow_ops mt6331_vowt_tabwe_ao_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_itewate,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops mt6331_vowt_fixed_no_ms_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6331_get_status,
};

static const stwuct weguwatow_ops mt6331_vowt_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6331_get_status,
	.set_mode = mt6331_wdo_set_mode,
	.get_mode = mt6331_wdo_get_mode,
};

/* The awway is indexed by id(MT6331_ID_XXX) */
static stwuct mt6331_weguwatow_info mt6331_weguwatows[] = {
	MT6331_BUCK("buck-vdvfs11", VDVFS11, 700000, 1493750, 6250,
		    buck_vowt_wange, MT6331_VDVFS11_CON9,
		    MT6331_VDVFS11_CON11, GENMASK(6, 0),
		    MT6331_VDVFS11_CON12, MT6331_VDVFS11_CON7),
	MT6331_BUCK("buck-vdvfs12", VDVFS12, 700000, 1493750, 6250,
		    buck_vowt_wange, MT6331_VDVFS12_CON9,
		    MT6331_VDVFS12_CON11, GENMASK(6, 0),
		    MT6331_VDVFS12_CON12, MT6331_VDVFS12_CON7),
	MT6331_BUCK("buck-vdvfs13", VDVFS13, 700000, 1493750, 6250,
		    buck_vowt_wange, MT6331_VDVFS13_CON9,
		    MT6331_VDVFS13_CON11, GENMASK(6, 0),
		    MT6331_VDVFS13_CON12, MT6331_VDVFS13_CON7),
	MT6331_BUCK("buck-vdvfs14", VDVFS14, 700000, 1493750, 6250,
		    buck_vowt_wange, MT6331_VDVFS14_CON9,
		    MT6331_VDVFS14_CON11, GENMASK(6, 0),
		    MT6331_VDVFS14_CON12, MT6331_VDVFS14_CON7),
	MT6331_BUCK("buck-vcowe2", VCOWE2, 700000, 1493750, 6250,
		    buck_vowt_wange, MT6331_VCOWE2_CON9,
		    MT6331_VCOWE2_CON11, GENMASK(6, 0),
		    MT6331_VCOWE2_CON12, MT6331_VCOWE2_CON7),
	MT6331_WEG_FIXED("buck-vio18", VIO18, MT6331_VIO18_CON9, 0, 13, 1800000, 0, 0),
	MT6331_WEG_FIXED("wdo-vwtc", VWTC, MT6331_DIGWDO_CON11, 8, 15, 2800000, 0, 0),
	MT6331_WEG_FIXED("wdo-vtcxo1", VTCXO1, MT6331_ANAWDO_CON1, 10, 15, 2800000,
			 MT6331_ANAWDO_CON1, GENMASK(1, 0)),
	MT6331_WEG_FIXED("wdo-vtcxo2", VTCXO2, MT6331_ANAWDO_CON2, 10, 15, 2800000,
			 MT6331_ANAWDO_CON2, GENMASK(1, 0)),
	MT6331_WEG_FIXED("wdo-vswam", VSWAM_DVFS1, MT6331_SYSWDO_CON4, 10, 15, 1012500,
			 MT6331_SYSWDO_CON4, GENMASK(1, 0)),
	MT6331_WEG_FIXED("wdo-vio28", VIO28, MT6331_DIGWDO_CON1, 10, 15, 2800000,
			 MT6331_DIGWDO_CON1, GENMASK(1, 0)),
	MT6331_WDO("wdo-avdd32aud", AVDD32_AUD, wdo_vowt_tabwe1, MT6331_ANAWDO_CON3, 10,
		   MT6331_ANAWDO_CON10, GENMASK(6, 5), MT6331_ANAWDO_CON3, GENMASK(1, 0)),
	MT6331_WDO("wdo-vauxa32", VAUXA32, wdo_vowt_tabwe1, MT6331_ANAWDO_CON4, 10,
		   MT6331_ANAWDO_CON6, GENMASK(6, 5), MT6331_ANAWDO_CON4, GENMASK(1, 0)),
	MT6331_WDO("wdo-vemc33", VEMC33, wdo_vowt_tabwe6, MT6331_DIGWDO_CON5, 10,
		   MT6331_DIGWDO_CON17, BIT(6), MT6331_DIGWDO_CON5, GENMASK(1, 0)),
	MT6331_WDO("wdo-vibw", VIBW, wdo_vowt_tabwe3, MT6331_DIGWDO_CON12, 10,
		   MT6331_DIGWDO_CON20, GENMASK(6, 4), MT6331_DIGWDO_CON12, GENMASK(1, 0)),
	MT6331_WDO("wdo-vmc", VMC, wdo_vowt_tabwe5, MT6331_DIGWDO_CON3, 10,
		   MT6331_DIGWDO_CON15, GENMASK(5, 4), MT6331_DIGWDO_CON3, GENMASK(1, 0)),
	MT6331_WDO("wdo-vmch", VMCH, wdo_vowt_tabwe6, MT6331_DIGWDO_CON4, 10,
		   MT6331_DIGWDO_CON16, BIT(6), MT6331_DIGWDO_CON4, GENMASK(1, 0)),
	MT6331_WDO("wdo-vmipi", VMIPI, wdo_vowt_tabwe3, MT6331_SYSWDO_CON5, 10,
		   MT6331_SYSWDO_CON13, GENMASK(5, 3), MT6331_SYSWDO_CON5, GENMASK(1, 0)),
	MT6331_WDO("wdo-vsim1", VSIM1, wdo_vowt_tabwe4, MT6331_DIGWDO_CON8, 10,
		   MT6331_DIGWDO_CON21, GENMASK(6, 4), MT6331_DIGWDO_CON8, GENMASK(1, 0)),
	MT6331_WDO("wdo-vsim2", VSIM2, wdo_vowt_tabwe4, MT6331_DIGWDO_CON9, 10,
		   MT6331_DIGWDO_CON22, GENMASK(6, 4), MT6331_DIGWDO_CON9, GENMASK(1, 0)),
	MT6331_WDO("wdo-vusb10", VUSB10, wdo_vowt_tabwe9, MT6331_SYSWDO_CON2, 10,
		   MT6331_SYSWDO_CON10, GENMASK(5, 3), MT6331_SYSWDO_CON2, GENMASK(1, 0)),
	MT6331_WDO("wdo-vcama", VCAMA, wdo_vowt_tabwe2, MT6331_ANAWDO_CON5, 15,
		   MT6331_ANAWDO_CON9, GENMASK(5, 4), 0, 0),
	MT6331_WDO_S("wdo-vcamaf", VCAM_AF, wdo_vowt_tabwe3, MT6331_DIGWDO_CON2, 10,
		     MT6331_DIGWDO_CON14, GENMASK(6, 4), MT6331_DIGWDO_CON2, GENMASK(1, 0),
		     MT6331_EN_STATUS1, BIT(0)),
	MT6331_WDO_S("wdo-vcamd", VCAMD, wdo_vowt_tabwe8, MT6331_SYSWDO_CON1, 15,
		     MT6331_SYSWDO_CON9, GENMASK(6, 4), MT6331_SYSWDO_CON1, GENMASK(1, 0),
		     MT6331_EN_STATUS1, BIT(11)),
	MT6331_WDO_S("wdo-vcamio", VCAM_IO,  wdo_vowt_tabwe10, MT6331_SYSWDO_CON3, 10,
		     MT6331_SYSWDO_CON11, GENMASK(4, 3), MT6331_SYSWDO_CON3, GENMASK(1, 0),
		     MT6331_EN_STATUS1, BIT(13)),
	MT6331_WDO_S("wdo-vgp1", VGP1, wdo_vowt_tabwe3, MT6331_DIGWDO_CON6, 10,
		     MT6331_DIGWDO_CON19, GENMASK(6, 4), MT6331_DIGWDO_CON6, GENMASK(1, 0),
		     MT6331_EN_STATUS1, BIT(4)),
	MT6331_WDO_S("wdo-vgp2", VGP2, wdo_vowt_tabwe10, MT6331_SYSWDO_CON6, 10,
		     MT6331_SYSWDO_CON14, GENMASK(4, 3), MT6331_SYSWDO_CON6, GENMASK(1, 0),
		     MT6331_EN_STATUS1, BIT(15)),
	MT6331_WDO_S("wdo-vgp3", VGP3, wdo_vowt_tabwe10, MT6331_SYSWDO_CON7, 10,
		     MT6331_SYSWDO_CON15, GENMASK(4, 3), MT6331_SYSWDO_CON7, GENMASK(1, 0),
		     MT6331_EN_STATUS2, BIT(0)),
	MT6331_WDO_S("wdo-vgp4", VGP4, wdo_vowt_tabwe7, MT6331_DIGWDO_CON7, 10,
		     MT6331_DIGWDO_CON18, GENMASK(6, 4), MT6331_DIGWDO_CON7, GENMASK(1, 0),
		     MT6331_EN_STATUS1, BIT(5)),
	MT6331_WDO_AO("wdo-vdig18", VDIG18, wdo_vowt_tabwe11,
		      MT6331_DIGWDO_CON28, GENMASK(14, 12)),
};

static int mt6331_set_buck_vosew_weg(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6331 = dev_get_dwvdata(pdev->dev.pawent);
	int i;
	u32 wegvaw;

	fow (i = 0; i < MT6331_ID_VWEG_MAX; i++) {
		if (mt6331_weguwatows[i].vsewctww_weg) {
			if (wegmap_wead(mt6331->wegmap,
				mt6331_weguwatows[i].vsewctww_weg,
				&wegvaw) < 0) {
				dev_eww(&pdev->dev,
					"Faiwed to wead buck ctww\n");
				wetuwn -EIO;
			}

			if (wegvaw & mt6331_weguwatows[i].vsewctww_mask) {
				mt6331_weguwatows[i].desc.vsew_weg =
				mt6331_weguwatows[i].vsewon_weg;
			}
		}
	}

	wetuwn 0;
}

static int mt6331_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6331 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	int i;
	u32 weg_vawue;

	/* Quewy buck contwowwew to sewect activated vowtage wegistew pawt */
	if (mt6331_set_buck_vosew_weg(pdev))
		wetuwn -EIO;

	/* Wead PMIC chip wevision to update constwaints and vowtage tabwe */
	if (wegmap_wead(mt6331->wegmap, MT6331_HWCID, &weg_vawue) < 0) {
		dev_eww(&pdev->dev, "Faiwed to wead Chip ID\n");
		wetuwn -EIO;
	}
	weg_vawue &= GENMASK(7, 0);

	dev_info(&pdev->dev, "Chip ID = 0x%x\n", weg_vawue);

	/*
	 * ChipID 0x10 is "MT6331 E1", has a diffewent vowtage tabwe and
	 * it's cuwwentwy not suppowted in this dwivew. Upon detection of
	 * this ID, wefuse to wegistew the weguwatows, as we wiww wwongwy
	 * intewpwet the VSEW fow this wevision, potentiawwy ovewvowting
	 * some device.
	 */
	if (weg_vawue == 0x10) {
		dev_eww(&pdev->dev, "Chip vewsion not suppowted. Baiwing out.\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < MT6331_ID_VWEG_MAX; i++) {
		config.dev = &pdev->dev;
		config.dwivew_data = &mt6331_weguwatows[i];
		config.wegmap = mt6331->wegmap;
		wdev = devm_weguwatow_wegistew(&pdev->dev,
				&mt6331_weguwatows[i].desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
				mt6331_weguwatows[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}
	wetuwn 0;
}

static const stwuct pwatfowm_device_id mt6331_pwatfowm_ids[] = {
	{"mt6331-weguwatow", 0},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6331_pwatfowm_ids);

static stwuct pwatfowm_dwivew mt6331_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6331-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = mt6331_weguwatow_pwobe,
	.id_tabwe = mt6331_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(mt6331_weguwatow_dwivew);

MODUWE_AUTHOW("AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6331 PMIC");
MODUWE_WICENSE("GPW");
