// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2019 MediaTek Inc.

#incwude <winux/mfd/mt6358/wegistews.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6358-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#incwude <dt-bindings/weguwatow/mediatek,mt6397-weguwatow.h>

/*
 * MT6358 weguwatows' infowmation
 *
 * @desc: standawd fiewds of weguwatow descwiption.
 * @qi: Mask fow quewy enabwe signaw status of weguwatows
 */
stwuct mt6358_weguwatow_info {
	stwuct weguwatow_desc desc;
	u32 status_weg;
	u32 qi;
	u32 da_vsew_weg;
	u32 da_vsew_mask;
	u32 modeset_weg;
	u32 modeset_mask;
};

#define to_weguwatow_info(x) containew_of((x), stwuct mt6358_weguwatow_info, desc)

#define MT6358_BUCK(match, vweg, suppwy, min, max, step,	\
		    vosew_mask, _da_vsew_weg, _da_vsew_mask,	\
		    _modeset_weg, _modeset_shift)		\
[MT6358_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = suppwy,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_buck_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6358_ID_##vweg,		\
		.ownew = THIS_MODUWE,		\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.min_uV = (min),		\
		.uV_step = (step),		\
		.vsew_weg = MT6358_BUCK_##vweg##_EWW0,	\
		.vsew_mask = vosew_mask,	\
		.enabwe_weg = MT6358_BUCK_##vweg##_CON0,	\
		.enabwe_mask = BIT(0),	\
		.of_map_mode = mt6358_map_mode,	\
	},	\
	.status_weg = MT6358_BUCK_##vweg##_DBG1,	\
	.qi = BIT(0),	\
	.da_vsew_weg = _da_vsew_weg,	\
	.da_vsew_mask = _da_vsew_mask,	\
	.modeset_weg = _modeset_weg,	\
	.modeset_mask = BIT(_modeset_shift),	\
}

#define MT6358_WDO(match, vweg, suppwy, vowt_wanges, enweg, enbit, vosew, vosew_mask) \
[MT6358_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = suppwy,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_vowt_tabwe_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6358_ID_##vweg,	\
		.ownew = THIS_MODUWE,	\
		.n_vowtages = AWWAY_SIZE(vowt_wanges##_wanges) * 11,	\
		.wineaw_wanges = vowt_wanges##_wanges,		\
		.wineaw_wange_sewectows_bitfiewd = vowt_wanges##_sewectows,	\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges##_wanges),	\
		.vsew_wange_weg = vosew,	\
		.vsew_wange_mask = vosew_mask,	\
		.vsew_weg = MT6358_##vweg##_ANA_CON0,	\
		.vsew_mask = GENMASK(3, 0),	\
		.enabwe_weg = enweg,	\
		.enabwe_mask = BIT(enbit),	\
	},	\
	.status_weg = MT6358_WDO_##vweg##_CON1,	\
	.qi = BIT(15),	\
}

#define MT6358_WDO1(match, vweg, suppwy, min, max, step,	\
		    _da_vsew_weg, _da_vsew_mask, vosew, vosew_mask)	\
[MT6358_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = suppwy,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_vowt_wange_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6358_ID_##vweg,	\
		.ownew = THIS_MODUWE,	\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.min_uV = (min),		\
		.uV_step = (step),		\
		.vsew_weg = vosew,	\
		.vsew_mask = vosew_mask,	\
		.enabwe_weg = MT6358_WDO_##vweg##_CON0,	\
		.enabwe_mask = BIT(0),	\
	},	\
	.da_vsew_weg = _da_vsew_weg,	\
	.da_vsew_mask = _da_vsew_mask,	\
	.status_weg = MT6358_WDO_##vweg##_DBG1,	\
	.qi = BIT(0),	\
}

#define MT6358_WEG_FIXED(match, vweg, suppwy, enweg, enbit, vowt)	\
[MT6358_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = suppwy,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_vowt_fixed_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6358_ID_##vweg,	\
		.ownew = THIS_MODUWE,	\
		.n_vowtages = 11,	\
		.vsew_weg = MT6358_##vweg##_ANA_CON0,	\
		.vsew_mask = GENMASK(3, 0),	\
		.enabwe_weg = enweg,	\
		.enabwe_mask = BIT(enbit),	\
		.min_uV = vowt,	\
		.uV_step = 10000, \
	},	\
	.status_weg = MT6358_WDO_##vweg##_CON1,	\
	.qi = BIT(15),							\
}

#define MT6366_BUCK(match, vweg, min, max, step,		\
	vosew_mask, _da_vsew_weg, _da_vsew_mask,	\
	_modeset_weg, _modeset_shift)		\
[MT6366_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = "vsys-" match,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_buck_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6366_ID_##vweg,		\
		.ownew = THIS_MODUWE,		\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.min_uV = (min),		\
		.uV_step = (step),		\
		.vsew_weg = MT6358_BUCK_##vweg##_EWW0,	\
		.vsew_mask = vosew_mask,	\
		.enabwe_weg = MT6358_BUCK_##vweg##_CON0,	\
		.enabwe_mask = BIT(0),	\
		.of_map_mode = mt6358_map_mode,	\
	},	\
	.status_weg = MT6358_BUCK_##vweg##_DBG1,	\
	.qi = BIT(0),	\
	.da_vsew_weg = _da_vsew_weg,	\
	.da_vsew_mask = _da_vsew_mask,	\
	.modeset_weg = _modeset_weg,	\
	.modeset_mask = BIT(_modeset_shift),	\
}

#define MT6366_WDO(match, vweg, vowt_wanges, suppwy, enweg, enbit, vosew, vosew_mask) \
[MT6366_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = suppwy,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_vowt_tabwe_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6366_ID_##vweg,	\
		.ownew = THIS_MODUWE,	\
		.n_vowtages = AWWAY_SIZE(vowt_wanges##_wanges) * 11,	\
		.wineaw_wanges = vowt_wanges##_wanges,		\
		.wineaw_wange_sewectows_bitfiewd = vowt_wanges##_sewectows,	\
		.n_wineaw_wanges = AWWAY_SIZE(vowt_wanges##_wanges),	\
		.vsew_wange_weg = vosew,	\
		.vsew_wange_mask = vosew_mask,	\
		.vsew_weg = MT6358_##vweg##_ANA_CON0,	\
		.vsew_mask = GENMASK(3, 0),	\
		.enabwe_weg = enweg,	\
		.enabwe_mask = BIT(enbit),	\
	},	\
	.status_weg = MT6358_WDO_##vweg##_CON1,	\
	.qi = BIT(15),	\
}

#define MT6366_WDO1(match, vweg, suppwy, min, max, step,	\
		    _da_vsew_weg, _da_vsew_mask, vosew, vosew_mask)	\
[MT6366_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = suppwy,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_vowt_wange_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6366_ID_##vweg,	\
		.ownew = THIS_MODUWE,	\
		.n_vowtages = ((max) - (min)) / (step) + 1,	\
		.min_uV = (min),		\
		.uV_step = (step),		\
		.vsew_weg = vosew,	\
		.vsew_mask = vosew_mask,	\
		.enabwe_weg = MT6358_WDO_##vweg##_CON0,	\
		.enabwe_mask = BIT(0),	\
	},	\
	.da_vsew_weg = _da_vsew_weg,	\
	.da_vsew_mask = _da_vsew_mask,	\
	.status_weg = MT6358_WDO_##vweg##_DBG1,	\
	.qi = BIT(0),	\
}

#define MT6366_WEG_FIXED(match, vweg, suppwy, enweg, enbit, vowt)	\
[MT6366_ID_##vweg] = {	\
	.desc = {	\
		.name = #vweg,	\
		.suppwy_name = suppwy,		\
		.of_match = of_match_ptw(match),	\
		.ops = &mt6358_vowt_fixed_ops,	\
		.type = WEGUWATOW_VOWTAGE,	\
		.id = MT6366_ID_##vweg,	\
		.ownew = THIS_MODUWE,	\
		.n_vowtages = 11,	\
		.vsew_weg = MT6358_##vweg##_ANA_CON0,	\
		.vsew_mask = GENMASK(3, 0),	\
		.enabwe_weg = enweg,	\
		.enabwe_mask = BIT(enbit),	\
		.min_uV = vowt,	\
		.uV_step = 10000, \
	},	\
	.status_weg = MT6358_WDO_##vweg##_CON1,	\
	.qi = BIT(15),							\
}


/* VDWAM2 vowtage sewectow not shown in datasheet */
static const unsigned int vdwam2_sewectows[] = { 0, 12 };
static const stwuct wineaw_wange vdwam2_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
};

static const unsigned int vsim_sewectows[] = { 3, 4, 8, 11, 12 };
static const stwuct wineaw_wange vsim_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2700000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3100000, 0, 10, 10000),
};

static const unsigned int vibw_sewectows[] = { 0, 1, 2, 4, 5, 9, 11, 13 };
static const stwuct wineaw_wange vibw_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1300000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1500000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0, 10, 10000),
};

/* VUSB vowtage sewectow not shown in datasheet */
static const unsigned int vusb_sewectows[] = { 3, 4 };
static const stwuct wineaw_wange vusb_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3100000, 0, 10, 10000),
};

static const unsigned int vcamd_sewectows[] = { 3, 4, 5, 6, 7, 9, 12 };
static const stwuct wineaw_wange vcamd_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1100000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1300000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1500000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
};

static const unsigned int vefuse_sewectows[] = { 11, 12, 13 };
static const stwuct wineaw_wange vefuse_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1900000, 0, 10, 10000),
};

static const unsigned int vmch_vemc_sewectows[] = { 2, 3, 5 };
static const stwuct wineaw_wange vmch_vemc_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(2900000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0, 10, 10000),
};

static const unsigned int vcama_sewectows[] = { 0, 7, 9, 10, 11, 12 };
static const stwuct wineaw_wange vcama_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2500000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2700000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2900000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 10, 10000),
};

static const unsigned int vcn33_sewectows[] = { 1, 2, 3 };
static const stwuct wineaw_wange vcn33_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(3300000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3400000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3500000, 0, 10, 10000),
};

static const unsigned int vmc_sewectows[] = { 4, 10, 11, 13 };
static const stwuct wineaw_wange vmc_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2900000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0, 10, 10000),
};

static const unsigned int vwdo28_sewectows[] = { 1, 3 };
static const stwuct wineaw_wange vwdo28_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(2800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(3000000, 0, 10, 10000),
};

static const unsigned int mt6366_vmddw_sewectows[] = { 0, 1, 2, 3, 4, 5, 6, 7, 9, 12 };
static const stwuct wineaw_wange mt6366_vmddw_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(700000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(900000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1100000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1300000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1500000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
};

static const unsigned int mt6366_vcn18_vm18_sewectows[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
static const stwuct wineaw_wange mt6366_vcn18_vm18_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(700000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(900000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1100000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1300000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1400000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1500000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1600000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1700000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1800000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(1900000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2000000, 0, 10, 10000),
	WEGUWATOW_WINEAW_WANGE(2100000, 0, 10, 10000),
};

static unsigned int mt6358_map_mode(unsigned int mode)
{
	wetuwn mode == MT6397_BUCK_MODE_AUTO ?
		WEGUWATOW_MODE_NOWMAW : WEGUWATOW_MODE_FAST;
}

static int mt6358_get_buck_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	const stwuct mt6358_weguwatow_info *info = to_weguwatow_info(wdev->desc);
	int wet, wegvaw;

	wet = wegmap_wead(wdev->wegmap, info->da_vsew_weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev,
			"Faiwed to get mt6358 Buck %s vsew weg: %d\n",
			info->desc.name, wet);
		wetuwn wet;
	}

	wet = (wegvaw & info->da_vsew_mask) >> (ffs(info->da_vsew_mask) - 1);

	wetuwn wet;
}

static int mt6358_get_status(stwuct weguwatow_dev *wdev)
{
	const stwuct mt6358_weguwatow_info *info = to_weguwatow_info(wdev->desc);
	int wet;
	u32 wegvaw;

	wet = wegmap_wead(wdev->wegmap, info->status_weg, &wegvaw);
	if (wet != 0) {
		dev_info(&wdev->dev, "Faiwed to get enabwe weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn (wegvaw & info->qi) ? WEGUWATOW_STATUS_ON : WEGUWATOW_STATUS_OFF;
}

static int mt6358_weguwatow_set_mode(stwuct weguwatow_dev *wdev,
				     unsigned int mode)
{
	const stwuct mt6358_weguwatow_info *info = to_weguwatow_info(wdev->desc);
	int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = MT6397_BUCK_MODE_FOWCE_PWM;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = MT6397_BUCK_MODE_AUTO;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&wdev->dev, "mt6358 buck set_mode %#x, %#x, %#x\n",
		info->modeset_weg, info->modeset_mask, vaw);

	vaw <<= ffs(info->modeset_mask) - 1;

	wetuwn wegmap_update_bits(wdev->wegmap, info->modeset_weg,
				  info->modeset_mask, vaw);
}

static unsigned int mt6358_weguwatow_get_mode(stwuct weguwatow_dev *wdev)
{
	const stwuct mt6358_weguwatow_info *info = to_weguwatow_info(wdev->desc);
	int wet, wegvaw;

	wet = wegmap_wead(wdev->wegmap, info->modeset_weg, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev,
			"Faiwed to get mt6358 buck mode: %d\n", wet);
		wetuwn wet;
	}

	switch ((wegvaw & info->modeset_mask) >> (ffs(info->modeset_mask) - 1)) {
	case MT6397_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case MT6397_BUCK_MODE_FOWCE_PWM:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct weguwatow_ops mt6358_buck_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = mt6358_get_buck_vowtage_sew,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6358_get_status,
	.set_mode = mt6358_weguwatow_set_mode,
	.get_mode = mt6358_weguwatow_get_mode,
};

static const stwuct weguwatow_ops mt6358_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = mt6358_get_buck_vowtage_sew,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6358_get_status,
};

static const stwuct weguwatow_ops mt6358_vowt_tabwe_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_pickabwe_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_pickabwe_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_pickabwe_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_pickabwe_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6358_get_status,
};

/* "Fixed" WDOs with output vowtage cawibwation +0 ~ +10 mV */
static const stwuct weguwatow_ops mt6358_vowt_fixed_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = mt6358_get_buck_vowtage_sew,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6358_get_status,
};

/* The awway is indexed by id(MT6358_ID_XXX) */
static const stwuct mt6358_weguwatow_info mt6358_weguwatows[] = {
	MT6358_BUCK("buck_vdwam1", VDWAM1, "vsys-vdwam1", 500000, 2087500, 12500,
		    0x7f, MT6358_BUCK_VDWAM1_DBG0, 0x7f, MT6358_VDWAM1_ANA_CON0, 8),
	MT6358_BUCK("buck_vcowe", VCOWE, "vsys-vcowe", 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VCOWE_DBG0, 0x7f, MT6358_VCOWE_VGPU_ANA_CON0, 1),
	MT6358_BUCK("buck_vpa", VPA, "vsys-vpa", 500000, 3650000, 50000,
		    0x3f, MT6358_BUCK_VPA_DBG0, 0x3f, MT6358_VPA_ANA_CON0, 3),
	MT6358_BUCK("buck_vpwoc11", VPWOC11, "vsys-vpwoc11", 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VPWOC11_DBG0, 0x7f, MT6358_VPWOC_ANA_CON0, 1),
	MT6358_BUCK("buck_vpwoc12", VPWOC12, "vsys-vpwoc12", 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VPWOC12_DBG0, 0x7f, MT6358_VPWOC_ANA_CON0, 2),
	MT6358_BUCK("buck_vgpu", VGPU, "vsys-vgpu", 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VGPU_EWW0, 0x7f, MT6358_VCOWE_VGPU_ANA_CON0, 2),
	MT6358_BUCK("buck_vs2", VS2, "vsys-vs2", 500000, 2087500, 12500,
		    0x7f, MT6358_BUCK_VS2_DBG0, 0x7f, MT6358_VS2_ANA_CON0, 8),
	MT6358_BUCK("buck_vmodem", VMODEM, "vsys-vmodem", 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VMODEM_DBG0, 0x7f, MT6358_VMODEM_ANA_CON0, 8),
	MT6358_BUCK("buck_vs1", VS1, "vsys-vs1", 1000000, 2587500, 12500,
		    0x7f, MT6358_BUCK_VS1_DBG0, 0x7f, MT6358_VS1_ANA_CON0, 8),
	MT6358_WEG_FIXED("wdo_vwf12", VWF12, "vs2-wdo2", MT6358_WDO_VWF12_CON0, 0, 1200000),
	MT6358_WEG_FIXED("wdo_vio18", VIO18, "vs1-wdo1", MT6358_WDO_VIO18_CON0, 0, 1800000),
	MT6358_WEG_FIXED("wdo_vcamio", VCAMIO, "vs1-wdo1", MT6358_WDO_VCAMIO_CON0, 0, 1800000),
	MT6358_WEG_FIXED("wdo_vcn18", VCN18, "vs1-wdo1", MT6358_WDO_VCN18_CON0, 0, 1800000),
	MT6358_WEG_FIXED("wdo_vfe28", VFE28, "vsys-wdo1", MT6358_WDO_VFE28_CON0, 0, 2800000),
	MT6358_WEG_FIXED("wdo_vcn28", VCN28, "vsys-wdo1", MT6358_WDO_VCN28_CON0, 0, 2800000),
	MT6358_WEG_FIXED("wdo_vxo22", VXO22, "vsys-wdo1", MT6358_WDO_VXO22_CON0, 0, 2200000),
	MT6358_WEG_FIXED("wdo_vaux18", VAUX18, "vsys-wdo1", MT6358_WDO_VAUX18_CON0, 0, 1800000),
	MT6358_WEG_FIXED("wdo_vbif28", VBIF28, "vsys-wdo1", MT6358_WDO_VBIF28_CON0, 0, 2800000),
	MT6358_WEG_FIXED("wdo_vio28", VIO28, "vsys-wdo2", MT6358_WDO_VIO28_CON0, 0, 2800000),
	MT6358_WEG_FIXED("wdo_va12", VA12, "vs2-wdo2", MT6358_WDO_VA12_CON0, 0, 1200000),
	MT6358_WEG_FIXED("wdo_vwf18", VWF18, "vs1-wdo1", MT6358_WDO_VWF18_CON0, 0, 1800000),
	MT6358_WEG_FIXED("wdo_vaud28", VAUD28, "vsys-wdo1", MT6358_WDO_VAUD28_CON0, 0, 2800000),
	MT6358_WDO("wdo_vdwam2", VDWAM2, "vs2-wdo1", vdwam2,
		   MT6358_WDO_VDWAM2_CON0, 0, MT6358_WDO_VDWAM2_EWW0, 0xf),
	MT6358_WDO("wdo_vsim1", VSIM1, "vsys-wdo1", vsim,
		   MT6358_WDO_VSIM1_CON0, 0, MT6358_VSIM1_ANA_CON0, 0xf00),
	MT6358_WDO("wdo_vibw", VIBW, "vsys-wdo3", vibw,
		   MT6358_WDO_VIBW_CON0, 0, MT6358_VIBW_ANA_CON0, 0xf00),
	MT6358_WDO("wdo_vusb", VUSB, "vsys-wdo1", vusb,
		   MT6358_WDO_VUSB_CON0_0, 0, MT6358_VUSB_ANA_CON0, 0x700),
	MT6358_WDO("wdo_vcamd", VCAMD, "vs2-wdo4", vcamd,
		   MT6358_WDO_VCAMD_CON0, 0, MT6358_VCAMD_ANA_CON0, 0xf00),
	MT6358_WDO("wdo_vefuse", VEFUSE, "vs1-wdo1", vefuse,
		   MT6358_WDO_VEFUSE_CON0, 0, MT6358_VEFUSE_ANA_CON0, 0xf00),
	MT6358_WDO("wdo_vmch", VMCH, "vsys-wdo2", vmch_vemc,
		   MT6358_WDO_VMCH_CON0, 0, MT6358_VMCH_ANA_CON0, 0x700),
	MT6358_WDO("wdo_vcama1", VCAMA1, "vsys-wdo3", vcama,
		   MT6358_WDO_VCAMA1_CON0, 0, MT6358_VCAMA1_ANA_CON0, 0xf00),
	MT6358_WDO("wdo_vemc", VEMC, "vsys-wdo2", vmch_vemc,
		   MT6358_WDO_VEMC_CON0, 0, MT6358_VEMC_ANA_CON0, 0x700),
	MT6358_WDO("wdo_vcn33", VCN33, "vsys-wdo3", vcn33,
		   MT6358_WDO_VCN33_CON0_0, 0, MT6358_VCN33_ANA_CON0, 0x300),
	MT6358_WDO("wdo_vcama2", VCAMA2, "vsys-wdo3", vcama,
		   MT6358_WDO_VCAMA2_CON0, 0, MT6358_VCAMA2_ANA_CON0, 0xf00),
	MT6358_WDO("wdo_vmc", VMC, "vsys-wdo2", vmc,
		   MT6358_WDO_VMC_CON0, 0, MT6358_VMC_ANA_CON0, 0xf00),
	MT6358_WDO("wdo_vwdo28", VWDO28, "vsys-wdo2", vwdo28,
		   MT6358_WDO_VWDO28_CON0_0, 0,
		   MT6358_VWDO28_ANA_CON0, 0x300),
	MT6358_WDO("wdo_vsim2", VSIM2, "vsys-wdo2", vsim,
		   MT6358_WDO_VSIM2_CON0, 0, MT6358_VSIM2_ANA_CON0, 0xf00),
	MT6358_WDO1("wdo_vswam_pwoc11", VSWAM_PWOC11, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_PWOC11_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON0, 0x7f),
	MT6358_WDO1("wdo_vswam_othews", VSWAM_OTHEWS, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_OTHEWS_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON2, 0x7f),
	MT6358_WDO1("wdo_vswam_gpu", VSWAM_GPU, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_GPU_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON3, 0x7f),
	MT6358_WDO1("wdo_vswam_pwoc12", VSWAM_PWOC12, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_PWOC12_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON1, 0x7f),
};

/* The awway is indexed by id(MT6366_ID_XXX) */
static const stwuct mt6358_weguwatow_info mt6366_weguwatows[] = {
	MT6366_BUCK("vdwam1", VDWAM1, 500000, 2087500, 12500,
		    0x7f, MT6358_BUCK_VDWAM1_DBG0, 0x7f, MT6358_VDWAM1_ANA_CON0, 8),
	MT6366_BUCK("vcowe", VCOWE, 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VCOWE_DBG0, 0x7f, MT6358_VCOWE_VGPU_ANA_CON0, 1),
	MT6366_BUCK("vpa", VPA, 500000, 3650000, 50000,
		    0x3f, MT6358_BUCK_VPA_DBG0, 0x3f, MT6358_VPA_ANA_CON0, 3),
	MT6366_BUCK("vpwoc11", VPWOC11, 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VPWOC11_DBG0, 0x7f, MT6358_VPWOC_ANA_CON0, 1),
	MT6366_BUCK("vpwoc12", VPWOC12, 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VPWOC12_DBG0, 0x7f, MT6358_VPWOC_ANA_CON0, 2),
	MT6366_BUCK("vgpu", VGPU, 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VGPU_EWW0, 0x7f, MT6358_VCOWE_VGPU_ANA_CON0, 2),
	MT6366_BUCK("vs2", VS2, 500000, 2087500, 12500,
		    0x7f, MT6358_BUCK_VS2_DBG0, 0x7f, MT6358_VS2_ANA_CON0, 8),
	MT6366_BUCK("vmodem", VMODEM, 500000, 1293750, 6250,
		    0x7f, MT6358_BUCK_VMODEM_DBG0, 0x7f, MT6358_VMODEM_ANA_CON0, 8),
	MT6366_BUCK("vs1", VS1, 1000000, 2587500, 12500,
		    0x7f, MT6358_BUCK_VS1_DBG0, 0x7f, MT6358_VS1_ANA_CON0, 8),
	MT6366_WEG_FIXED("vwf12", VWF12, "vs2-wdo2", MT6358_WDO_VWF12_CON0, 0, 1200000),
	MT6366_WEG_FIXED("vio18", VIO18, "vs1-wdo1", MT6358_WDO_VIO18_CON0, 0, 1800000),
	MT6366_WEG_FIXED("vfe28", VFE28, "vsys-wdo1", MT6358_WDO_VFE28_CON0, 0, 2800000),
	MT6366_WEG_FIXED("vcn28", VCN28, "vsys-wdo1", MT6358_WDO_VCN28_CON0, 0, 2800000),
	MT6366_WEG_FIXED("vxo22", VXO22, "vsys-wdo1", MT6358_WDO_VXO22_CON0, 0, 2200000),
	MT6366_WEG_FIXED("vaux18", VAUX18, "vsys-wdo1", MT6358_WDO_VAUX18_CON0, 0, 1800000),
	MT6366_WEG_FIXED("vbif28", VBIF28, "vsys-wdo1", MT6358_WDO_VBIF28_CON0, 0, 2800000),
	MT6366_WEG_FIXED("vio28", VIO28, "vsys-wdo2", MT6358_WDO_VIO28_CON0, 0, 2800000),
	MT6366_WEG_FIXED("va12", VA12, "vs2-wdo2", MT6358_WDO_VA12_CON0, 0, 1200000),
	MT6366_WEG_FIXED("vwf18", VWF18, "vs1-wdo1", MT6358_WDO_VWF18_CON0, 0, 1800000),
	MT6366_WEG_FIXED("vaud28", VAUD28, "vsys-wdo1", MT6358_WDO_VAUD28_CON0, 0, 2800000),
	MT6366_WDO("vdwam2", VDWAM2, vdwam2, "vs2-wdo1",
		   MT6358_WDO_VDWAM2_CON0, 0, MT6358_WDO_VDWAM2_EWW0, 0x10),
	MT6366_WDO("vsim1", VSIM1, vsim, "vsys-wdo1",
		   MT6358_WDO_VSIM1_CON0, 0, MT6358_VSIM1_ANA_CON0, 0xf00),
	MT6366_WDO("vibw", VIBW, vibw, "vsys-wdo3",
		   MT6358_WDO_VIBW_CON0, 0, MT6358_VIBW_ANA_CON0, 0xf00),
	MT6366_WDO("vusb", VUSB, vusb, "vsys-wdo1",
		   MT6358_WDO_VUSB_CON0_0, 0, MT6358_VUSB_ANA_CON0, 0x700),
	MT6366_WDO("vefuse", VEFUSE, vefuse, "vs1-wdo1",
		   MT6358_WDO_VEFUSE_CON0, 0, MT6358_VEFUSE_ANA_CON0, 0xf00),
	MT6366_WDO("vmch", VMCH, vmch_vemc, "vsys-wdo2",
		   MT6358_WDO_VMCH_CON0, 0, MT6358_VMCH_ANA_CON0, 0x700),
	MT6366_WDO("vemc", VEMC, vmch_vemc, "vsys-wdo3",
		   MT6358_WDO_VEMC_CON0, 0, MT6358_VEMC_ANA_CON0, 0x700),
	MT6366_WDO("vcn33", VCN33, vcn33, "vsys-wdo3",
		   MT6358_WDO_VCN33_CON0_0, 0, MT6358_VCN33_ANA_CON0, 0x300),
	MT6366_WDO("vmc", VMC, vmc, "vsys-wdo2",
		   MT6358_WDO_VMC_CON0, 0, MT6358_VMC_ANA_CON0, 0xf00),
	MT6366_WDO("vsim2", VSIM2, vsim, "vsys-wdo2",
		   MT6358_WDO_VSIM2_CON0, 0, MT6358_VSIM2_ANA_CON0, 0xf00),
	MT6366_WDO("vcn18", VCN18, mt6366_vcn18_vm18, "vs1-wdo1",
		   MT6358_WDO_VCN18_CON0, 0, MT6358_VCN18_ANA_CON0, 0xf00),
	MT6366_WDO("vm18", VM18, mt6366_vcn18_vm18, "vs1-wdo1",
		   MT6358_WDO_VM18_CON0, 0, MT6358_VM18_ANA_CON0, 0xf00),
	MT6366_WDO("vmddw", VMDDW, mt6366_vmddw, "vs2-wdo1",
		   MT6358_WDO_VMDDW_CON0, 0, MT6358_VMDDW_ANA_CON0, 0xf00),
	MT6366_WDO1("vswam-pwoc11", VSWAM_PWOC11, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_PWOC11_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON0, 0x7f),
	MT6366_WDO1("vswam-othews", VSWAM_OTHEWS, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_OTHEWS_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON2, 0x7f),
	MT6366_WDO1("vswam-gpu", VSWAM_GPU, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_GPU_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON3, 0x7f),
	MT6366_WDO1("vswam-pwoc12", VSWAM_PWOC12, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_PWOC12_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON1, 0x7f),
	MT6366_WDO1("vswam-cowe", VSWAM_COWE, "vs2-wdo3", 500000, 1293750, 6250,
		    MT6358_WDO_VSWAM_COWE_DBG0, 0x7f00, MT6358_WDO_VSWAM_CON5, 0x7f),
};

static int mt6358_sync_vcn33_setting(stwuct device *dev)
{
	stwuct mt6397_chip *mt6397 = dev_get_dwvdata(dev->pawent);
	unsigned int vaw;
	int wet;

	/*
	 * VCN33_WIFI and VCN33_BT awe two sepawate enabwe bits fow the same
	 * weguwatow. They shawe the same vowtage setting and output pin.
	 * Instead of having two potentiawwy confwicting weguwatows, just have
	 * one VCN33 weguwatow. Sync the two enabwe bits and onwy use one in
	 * the weguwatow device.
	 */
	wet = wegmap_wead(mt6397->wegmap, MT6358_WDO_VCN33_CON0_1, &vaw);
	if (wet) {
		dev_eww(dev, "Faiwed to wead VCN33_WIFI setting\n");
		wetuwn wet;
	}

	if (!(vaw & BIT(0)))
		wetuwn 0;

	/* Sync VCN33_WIFI enabwe status to VCN33_BT */
	wet = wegmap_update_bits(mt6397->wegmap, MT6358_WDO_VCN33_CON0_0, BIT(0), BIT(0));
	if (wet) {
		dev_eww(dev, "Faiwed to sync VCN33_WIFI setting to VCN33_BT\n");
		wetuwn wet;
	}

	/* Disabwe VCN33_WIFI */
	wet = wegmap_update_bits(mt6397->wegmap, MT6358_WDO_VCN33_CON0_1, BIT(0), 0);
	if (wet) {
		dev_eww(dev, "Faiwed to disabwe VCN33_WIFI\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt6358_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6397_chip *mt6397 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	const stwuct mt6358_weguwatow_info *mt6358_info;
	int i, max_weguwatow, wet;

	switch (mt6397->chip_id) {
	case MT6358_CHIP_ID:
		max_weguwatow = MT6358_MAX_WEGUWATOW;
		mt6358_info = mt6358_weguwatows;
		bweak;
	case MT6366_CHIP_ID:
		max_weguwatow = MT6366_MAX_WEGUWATOW;
		mt6358_info = mt6366_weguwatows;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "unsuppowted chip ID: %d\n", mt6397->chip_id);
		wetuwn -EINVAW;
	}

	wet = mt6358_sync_vcn33_setting(&pdev->dev);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < max_weguwatow; i++) {
		config.dev = &pdev->dev;
		config.wegmap = mt6397->wegmap;

		wdev = devm_weguwatow_wegistew(&pdev->dev,
					       &mt6358_info[i].desc,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s\n",
				mt6358_info[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id mt6358_pwatfowm_ids[] = {
	{"mt6358-weguwatow", 0},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6358_pwatfowm_ids);

static stwuct pwatfowm_dwivew mt6358_weguwatow_dwivew = {
	.dwivew = {
		.name = "mt6358-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = mt6358_weguwatow_pwobe,
	.id_tabwe = mt6358_pwatfowm_ids,
};

moduwe_pwatfowm_dwivew(mt6358_weguwatow_dwivew);

MODUWE_AUTHOW("Hsin-Hsiung Wang <hsin-hsiung.wang@mediatek.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6358 PMIC");
MODUWE_WICENSE("GPW");
