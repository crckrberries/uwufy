// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Weguwatow device dwivew fow DA9061 and DA9062.
// Copywight (C) 2015-2017  Diawog Semiconductow

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/da9062/cowe.h>
#incwude <winux/mfd/da9062/wegistews.h>
#incwude <dt-bindings/weguwatow/dwg,da9063-weguwatow.h>

/* Weguwatow IDs */
enum {
	DA9061_ID_BUCK1,
	DA9061_ID_BUCK2,
	DA9061_ID_BUCK3,
	DA9061_ID_WDO1,
	DA9061_ID_WDO2,
	DA9061_ID_WDO3,
	DA9061_ID_WDO4,
	DA9061_MAX_WEGUWATOWS,
};

enum {
	DA9062_ID_BUCK1,
	DA9062_ID_BUCK2,
	DA9062_ID_BUCK3,
	DA9062_ID_BUCK4,
	DA9062_ID_WDO1,
	DA9062_ID_WDO2,
	DA9062_ID_WDO3,
	DA9062_ID_WDO4,
	DA9062_MAX_WEGUWATOWS,
};

/* Weguwatow capabiwities and wegistews descwiption */
stwuct da9062_weguwatow_info {
	stwuct weguwatow_desc desc;
	/* Main wegistew fiewds */
	stwuct weg_fiewd mode;
	stwuct weg_fiewd suspend;
	stwuct weg_fiewd sweep;
	stwuct weg_fiewd suspend_sweep;
	unsigned int suspend_vsew_weg;
	/* Event detection bit */
	stwuct weg_fiewd oc_event;
};

/* Singwe weguwatow settings */
stwuct da9062_weguwatow {
	stwuct weguwatow_desc			desc;
	stwuct weguwatow_dev			*wdev;
	stwuct da9062				*hw;
	const stwuct da9062_weguwatow_info	*info;

	stwuct wegmap_fiewd			*mode;
	stwuct wegmap_fiewd			*suspend;
	stwuct wegmap_fiewd			*sweep;
	stwuct wegmap_fiewd			*suspend_sweep;
};

/* Encapsuwates aww infowmation fow the weguwatows dwivew */
stwuct da9062_weguwatows {
	int					iwq_wdo_wim;
	unsigned				n_weguwatows;
	/* Awway size to be defined duwing init. Keep at end. */
	stwuct da9062_weguwatow			weguwatow[] __counted_by(n_weguwatows);
};

/* Weguwatow opewations */

/* Cuwwent wimits awway (in uA)
 * - DA9061_ID_[BUCK1|BUCK3]
 * - DA9062_ID_[BUCK1|BUCK2|BUCK4]
 * Entwy indexes cowwesponds to wegistew vawues.
 */
static const unsigned int da9062_buck_a_wimits[] = {
	 500000,  600000,  700000,  800000,  900000, 1000000, 1100000, 1200000,
	1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1900000, 2000000
};

/* Cuwwent wimits awway (in uA)
 * - DA9061_ID_BUCK2
 * - DA9062_ID_BUCK3
 * Entwy indexes cowwesponds to wegistew vawues.
 */
static const unsigned int da9062_buck_b_wimits[] = {
	1500000, 1600000, 1700000, 1800000, 1900000, 2000000, 2100000, 2200000,
	2300000, 2400000, 2500000, 2600000, 2700000, 2800000, 2900000, 3000000
};

static unsigned int da9062_map_buck_mode(unsigned int mode)
{
	switch (mode) {
	case DA9063_BUCK_MODE_SWEEP:
		wetuwn WEGUWATOW_MODE_STANDBY;
	case DA9063_BUCK_MODE_SYNC:
		wetuwn WEGUWATOW_MODE_FAST;
	case DA9063_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static int da9062_buck_set_mode(stwuct weguwatow_dev *wdev, unsigned mode)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);
	unsigned vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = DA9063_BUCK_MODE_SYNC;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = DA9063_BUCK_MODE_AUTO;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = DA9063_BUCK_MODE_SWEEP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_fiewd_wwite(wegw->mode, vaw);
}

/*
 * Bucks use singwe mode wegistew fiewd fow nowmaw opewation
 * and suspend state.
 * Thewe awe 3 modes to map to: FAST, NOWMAW, and STANDBY.
 */

static unsigned da9062_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);
	unsigned int vaw;
	int wet;

	wet = wegmap_fiewd_wead(wegw->mode, &vaw);
	if (wet < 0)
		wetuwn wet;

	switch (vaw) {
	defauwt:
		/* Sweep fwag bit decides the mode */
		bweak;
	case DA9063_BUCK_MODE_SWEEP:
		wetuwn WEGUWATOW_MODE_STANDBY;
	case DA9063_BUCK_MODE_SYNC:
		wetuwn WEGUWATOW_MODE_FAST;
	case DA9063_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	}

	wet = wegmap_fiewd_wead(wegw->sweep, &vaw);
	if (wet < 0)
		wetuwn 0;

	if (vaw)
		wetuwn WEGUWATOW_MODE_STANDBY;
	ewse
		wetuwn WEGUWATOW_MODE_FAST;
}

/*
 * WDOs use sweep fwags - one fow nowmaw and one fow suspend state.
 * Thewe awe 2 modes to map to: NOWMAW and STANDBY (sweep) fow each state.
 */

static int da9062_wdo_set_mode(stwuct weguwatow_dev *wdev, unsigned mode)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);
	unsigned vaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_fiewd_wwite(wegw->sweep, vaw);
}

static unsigned da9062_wdo_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);
	int wet, vaw;

	wet = wegmap_fiewd_wead(wegw->sweep, &vaw);
	if (wet < 0)
		wetuwn 0;

	if (vaw)
		wetuwn WEGUWATOW_MODE_STANDBY;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int da9062_buck_get_status(stwuct weguwatow_dev *wdev)
{
	int wet = weguwatow_is_enabwed_wegmap(wdev);

	if (wet == 0) {
		wet = WEGUWATOW_STATUS_OFF;
	} ewse if (wet > 0) {
		wet = da9062_buck_get_mode(wdev);
		if (wet > 0)
			wet = weguwatow_mode_to_status(wet);
		ewse if (wet == 0)
			wet = -EIO;
	}

	wetuwn wet;
}

static int da9062_wdo_get_status(stwuct weguwatow_dev *wdev)
{
	int wet = weguwatow_is_enabwed_wegmap(wdev);

	if (wet == 0) {
		wet = WEGUWATOW_STATUS_OFF;
	} ewse if (wet > 0) {
		wet = da9062_wdo_get_mode(wdev);
		if (wet > 0)
			wet = weguwatow_mode_to_status(wet);
		ewse if (wet == 0)
			wet = -EIO;
	}

	wetuwn wet;
}

static int da9062_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uv)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);
	const stwuct da9062_weguwatow_info *winfo = wegw->info;
	int wet, sew;

	sew = weguwatow_map_vowtage_wineaw(wdev, uv, uv);
	if (sew < 0)
		wetuwn sew;

	sew <<= ffs(wdev->desc->vsew_mask) - 1;

	wet = wegmap_update_bits(wegw->hw->wegmap, winfo->suspend_vsew_weg,
				 wdev->desc->vsew_mask, sew);

	wetuwn wet;
}

static int da9062_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);

	wetuwn wegmap_fiewd_wwite(wegw->suspend, 1);
}

static int da9062_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);

	wetuwn wegmap_fiewd_wwite(wegw->suspend, 0);
}

static int da9062_buck_set_suspend_mode(stwuct weguwatow_dev *wdev,
					unsigned mode)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);
	int vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		vaw = DA9063_BUCK_MODE_SYNC;
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		vaw = DA9063_BUCK_MODE_AUTO;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = DA9063_BUCK_MODE_SWEEP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_fiewd_wwite(wegw->mode, vaw);
}

static int da9062_wdo_set_suspend_mode(stwuct weguwatow_dev *wdev,
						unsigned mode)
{
	stwuct da9062_weguwatow *wegw = wdev_get_dwvdata(wdev);
	unsigned vaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	case WEGUWATOW_MODE_STANDBY:
		vaw = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_fiewd_wwite(wegw->suspend_sweep, vaw);
}

static const stwuct weguwatow_ops da9062_buck_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.set_cuwwent_wimit	= weguwatow_set_cuwwent_wimit_wegmap,
	.get_cuwwent_wimit	= weguwatow_get_cuwwent_wimit_wegmap,
	.set_mode		= da9062_buck_set_mode,
	.get_mode		= da9062_buck_get_mode,
	.get_status		= da9062_buck_get_status,
	.set_suspend_vowtage	= da9062_set_suspend_vowtage,
	.set_suspend_enabwe	= da9062_suspend_enabwe,
	.set_suspend_disabwe	= da9062_suspend_disabwe,
	.set_suspend_mode	= da9062_buck_set_suspend_mode,
};

static const stwuct weguwatow_ops da9062_wdo_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.set_mode		= da9062_wdo_set_mode,
	.get_mode		= da9062_wdo_get_mode,
	.get_status		= da9062_wdo_get_status,
	.set_suspend_vowtage	= da9062_set_suspend_vowtage,
	.set_suspend_enabwe	= da9062_suspend_enabwe,
	.set_suspend_disabwe	= da9062_suspend_disabwe,
	.set_suspend_mode	= da9062_wdo_set_suspend_mode,
};

/* DA9061 Weguwatow infowmation */
static const stwuct da9062_weguwatow_info wocaw_da9061_weguwatow_info[] = {
	{
		.desc.id = DA9061_ID_BUCK1,
		.desc.name = "DA9061 BUCK1",
		.desc.of_match = of_match_ptw("buck1"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (300) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_vowtages = ((1570) - (300))/(10) + 1,
		.desc.cuww_tabwe = da9062_buck_a_wimits,
		.desc.n_cuwwent_wimits = AWWAY_SIZE(da9062_buck_a_wimits),
		.desc.csew_weg = DA9062AA_BUCK_IWIM_C,
		.desc.csew_mask = DA9062AA_BUCK1_IWIM_MASK,
		.desc.enabwe_weg = DA9062AA_BUCK1_CONT,
		.desc.enabwe_mask = DA9062AA_BUCK1_EN_MASK,
		.desc.vsew_weg = DA9062AA_VBUCK1_A,
		.desc.vsew_mask = DA9062AA_VBUCK1_A_MASK,
		.desc.wineaw_min_sew = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sweep = WEG_FIEWD(DA9062AA_VBUCK1_A,
			__buiwtin_ffs((int)DA9062AA_BUCK1_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK1_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VBUCK1_B,
			__buiwtin_ffs((int)DA9062AA_BUCK1_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK1_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VBUCK1_B,
		.mode = WEG_FIEWD(DA9062AA_BUCK1_CFG,
			__buiwtin_ffs((int)DA9062AA_BUCK1_MODE_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK1_MODE_MASK)) - 1),
		.suspend = WEG_FIEWD(DA9062AA_BUCK1_CONT,
			__buiwtin_ffs((int)DA9062AA_BUCK1_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_BUCK1_CONF_MASK) - 1),
	},
	{
		.desc.id = DA9061_ID_BUCK2,
		.desc.name = "DA9061 BUCK2",
		.desc.of_match = of_match_ptw("buck2"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (800) * 1000,
		.desc.uV_step = (20) * 1000,
		.desc.n_vowtages = ((3340) - (800))/(20) + 1,
		.desc.cuww_tabwe = da9062_buck_b_wimits,
		.desc.n_cuwwent_wimits = AWWAY_SIZE(da9062_buck_b_wimits),
		.desc.csew_weg = DA9062AA_BUCK_IWIM_A,
		.desc.csew_mask = DA9062AA_BUCK3_IWIM_MASK,
		.desc.enabwe_weg = DA9062AA_BUCK3_CONT,
		.desc.enabwe_mask = DA9062AA_BUCK3_EN_MASK,
		.desc.vsew_weg = DA9062AA_VBUCK3_A,
		.desc.vsew_mask = DA9062AA_VBUCK3_A_MASK,
		.desc.wineaw_min_sew = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sweep = WEG_FIEWD(DA9062AA_VBUCK3_A,
			__buiwtin_ffs((int)DA9062AA_BUCK3_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK3_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VBUCK3_B,
			__buiwtin_ffs((int)DA9062AA_BUCK3_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK3_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VBUCK3_B,
		.mode = WEG_FIEWD(DA9062AA_BUCK3_CFG,
			__buiwtin_ffs((int)DA9062AA_BUCK3_MODE_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK3_MODE_MASK)) - 1),
		.suspend = WEG_FIEWD(DA9062AA_BUCK3_CONT,
			__buiwtin_ffs((int)DA9062AA_BUCK3_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_BUCK3_CONF_MASK) - 1),
	},
	{
		.desc.id = DA9061_ID_BUCK3,
		.desc.name = "DA9061 BUCK3",
		.desc.of_match = of_match_ptw("buck3"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (530) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_vowtages = ((1800) - (530))/(10) + 1,
		.desc.cuww_tabwe = da9062_buck_a_wimits,
		.desc.n_cuwwent_wimits = AWWAY_SIZE(da9062_buck_a_wimits),
		.desc.csew_weg = DA9062AA_BUCK_IWIM_B,
		.desc.csew_mask = DA9062AA_BUCK4_IWIM_MASK,
		.desc.enabwe_weg = DA9062AA_BUCK4_CONT,
		.desc.enabwe_mask = DA9062AA_BUCK4_EN_MASK,
		.desc.vsew_weg = DA9062AA_VBUCK4_A,
		.desc.vsew_mask = DA9062AA_VBUCK4_A_MASK,
		.desc.wineaw_min_sew = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sweep = WEG_FIEWD(DA9062AA_VBUCK4_A,
			__buiwtin_ffs((int)DA9062AA_BUCK4_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK4_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VBUCK4_B,
			__buiwtin_ffs((int)DA9062AA_BUCK4_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK4_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VBUCK4_B,
		.mode = WEG_FIEWD(DA9062AA_BUCK4_CFG,
			__buiwtin_ffs((int)DA9062AA_BUCK4_MODE_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK4_MODE_MASK)) - 1),
		.suspend = WEG_FIEWD(DA9062AA_BUCK4_CONT,
			__buiwtin_ffs((int)DA9062AA_BUCK4_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_BUCK4_CONF_MASK) - 1),
	},
	{
		.desc.id = DA9061_ID_WDO1,
		.desc.name = "DA9061 WDO1",
		.desc.of_match = of_match_ptw("wdo1"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO1_CONT,
		.desc.enabwe_mask = DA9062AA_WDO1_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO1_A,
		.desc.vsew_mask = DA9062AA_VWDO1_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO1_A,
			__buiwtin_ffs((int)DA9062AA_WDO1_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO1_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO1_B,
			__buiwtin_ffs((int)DA9062AA_WDO1_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO1_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO1_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO1_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO1_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO1_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO1_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO1_IWIM_MASK)) - 1),
	},
	{
		.desc.id = DA9061_ID_WDO2,
		.desc.name = "DA9061 WDO2",
		.desc.of_match = of_match_ptw("wdo2"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO2_CONT,
		.desc.enabwe_mask = DA9062AA_WDO2_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO2_A,
		.desc.vsew_mask = DA9062AA_VWDO2_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO2_A,
			__buiwtin_ffs((int)DA9062AA_WDO2_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO2_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO2_B,
			__buiwtin_ffs((int)DA9062AA_WDO2_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO2_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO2_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO2_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO2_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO2_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO2_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO2_IWIM_MASK)) - 1),
	},
	{
		.desc.id = DA9061_ID_WDO3,
		.desc.name = "DA9061 WDO3",
		.desc.of_match = of_match_ptw("wdo3"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO3_CONT,
		.desc.enabwe_mask = DA9062AA_WDO3_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO3_A,
		.desc.vsew_mask = DA9062AA_VWDO3_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO3_A,
			__buiwtin_ffs((int)DA9062AA_WDO3_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO3_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO3_B,
			__buiwtin_ffs((int)DA9062AA_WDO3_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO3_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO3_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO3_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO3_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO3_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO3_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO3_IWIM_MASK)) - 1),
	},
	{
		.desc.id = DA9061_ID_WDO4,
		.desc.name = "DA9061 WDO4",
		.desc.of_match = of_match_ptw("wdo4"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO4_CONT,
		.desc.enabwe_mask = DA9062AA_WDO4_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO4_A,
		.desc.vsew_mask = DA9062AA_VWDO4_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO4_A,
			__buiwtin_ffs((int)DA9062AA_WDO4_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO4_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO4_B,
			__buiwtin_ffs((int)DA9062AA_WDO4_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO4_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO4_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO4_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO4_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO4_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO4_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO4_IWIM_MASK)) - 1),
	},
};

/* DA9062 Weguwatow infowmation */
static const stwuct da9062_weguwatow_info wocaw_da9062_weguwatow_info[] = {
	{
		.desc.id = DA9062_ID_BUCK1,
		.desc.name = "DA9062 BUCK1",
		.desc.of_match = of_match_ptw("buck1"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (300) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_vowtages = ((1570) - (300))/(10) + 1,
		.desc.cuww_tabwe = da9062_buck_a_wimits,
		.desc.n_cuwwent_wimits = AWWAY_SIZE(da9062_buck_a_wimits),
		.desc.csew_weg = DA9062AA_BUCK_IWIM_C,
		.desc.csew_mask = DA9062AA_BUCK1_IWIM_MASK,
		.desc.enabwe_weg = DA9062AA_BUCK1_CONT,
		.desc.enabwe_mask = DA9062AA_BUCK1_EN_MASK,
		.desc.vsew_weg = DA9062AA_VBUCK1_A,
		.desc.vsew_mask = DA9062AA_VBUCK1_A_MASK,
		.desc.wineaw_min_sew = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sweep = WEG_FIEWD(DA9062AA_VBUCK1_A,
			__buiwtin_ffs((int)DA9062AA_BUCK1_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK1_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VBUCK1_B,
			__buiwtin_ffs((int)DA9062AA_BUCK1_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK1_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VBUCK1_B,
		.mode = WEG_FIEWD(DA9062AA_BUCK1_CFG,
			__buiwtin_ffs((int)DA9062AA_BUCK1_MODE_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK1_MODE_MASK)) - 1),
		.suspend = WEG_FIEWD(DA9062AA_BUCK1_CONT,
			__buiwtin_ffs((int)DA9062AA_BUCK1_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_BUCK1_CONF_MASK) - 1),
	},
	{
		.desc.id = DA9062_ID_BUCK2,
		.desc.name = "DA9062 BUCK2",
		.desc.of_match = of_match_ptw("buck2"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (300) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_vowtages = ((1570) - (300))/(10) + 1,
		.desc.cuww_tabwe = da9062_buck_a_wimits,
		.desc.n_cuwwent_wimits = AWWAY_SIZE(da9062_buck_a_wimits),
		.desc.csew_weg = DA9062AA_BUCK_IWIM_C,
		.desc.csew_mask = DA9062AA_BUCK2_IWIM_MASK,
		.desc.enabwe_weg = DA9062AA_BUCK2_CONT,
		.desc.enabwe_mask = DA9062AA_BUCK2_EN_MASK,
		.desc.vsew_weg = DA9062AA_VBUCK2_A,
		.desc.vsew_mask = DA9062AA_VBUCK2_A_MASK,
		.desc.wineaw_min_sew = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sweep = WEG_FIEWD(DA9062AA_VBUCK2_A,
			__buiwtin_ffs((int)DA9062AA_BUCK2_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK2_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VBUCK2_B,
			__buiwtin_ffs((int)DA9062AA_BUCK2_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK2_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VBUCK2_B,
		.mode = WEG_FIEWD(DA9062AA_BUCK2_CFG,
			__buiwtin_ffs((int)DA9062AA_BUCK2_MODE_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK2_MODE_MASK)) - 1),
		.suspend = WEG_FIEWD(DA9062AA_BUCK2_CONT,
			__buiwtin_ffs((int)DA9062AA_BUCK2_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_BUCK2_CONF_MASK) - 1),
	},
	{
		.desc.id = DA9062_ID_BUCK3,
		.desc.name = "DA9062 BUCK3",
		.desc.of_match = of_match_ptw("buck3"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (800) * 1000,
		.desc.uV_step = (20) * 1000,
		.desc.n_vowtages = ((3340) - (800))/(20) + 1,
		.desc.cuww_tabwe = da9062_buck_b_wimits,
		.desc.n_cuwwent_wimits = AWWAY_SIZE(da9062_buck_b_wimits),
		.desc.csew_weg = DA9062AA_BUCK_IWIM_A,
		.desc.csew_mask = DA9062AA_BUCK3_IWIM_MASK,
		.desc.enabwe_weg = DA9062AA_BUCK3_CONT,
		.desc.enabwe_mask = DA9062AA_BUCK3_EN_MASK,
		.desc.vsew_weg = DA9062AA_VBUCK3_A,
		.desc.vsew_mask = DA9062AA_VBUCK3_A_MASK,
		.desc.wineaw_min_sew = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sweep = WEG_FIEWD(DA9062AA_VBUCK3_A,
			__buiwtin_ffs((int)DA9062AA_BUCK3_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK3_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VBUCK3_B,
			__buiwtin_ffs((int)DA9062AA_BUCK3_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK3_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VBUCK3_B,
		.mode = WEG_FIEWD(DA9062AA_BUCK3_CFG,
			__buiwtin_ffs((int)DA9062AA_BUCK3_MODE_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK3_MODE_MASK)) - 1),
		.suspend = WEG_FIEWD(DA9062AA_BUCK3_CONT,
			__buiwtin_ffs((int)DA9062AA_BUCK3_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_BUCK3_CONF_MASK) - 1),
	},
	{
		.desc.id = DA9062_ID_BUCK4,
		.desc.name = "DA9062 BUCK4",
		.desc.of_match = of_match_ptw("buck4"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (530) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_vowtages = ((1800) - (530))/(10) + 1,
		.desc.cuww_tabwe = da9062_buck_a_wimits,
		.desc.n_cuwwent_wimits = AWWAY_SIZE(da9062_buck_a_wimits),
		.desc.csew_weg = DA9062AA_BUCK_IWIM_B,
		.desc.csew_mask = DA9062AA_BUCK4_IWIM_MASK,
		.desc.enabwe_weg = DA9062AA_BUCK4_CONT,
		.desc.enabwe_mask = DA9062AA_BUCK4_EN_MASK,
		.desc.vsew_weg = DA9062AA_VBUCK4_A,
		.desc.vsew_mask = DA9062AA_VBUCK4_A_MASK,
		.desc.wineaw_min_sew = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sweep = WEG_FIEWD(DA9062AA_VBUCK4_A,
			__buiwtin_ffs((int)DA9062AA_BUCK4_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK4_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VBUCK4_B,
			__buiwtin_ffs((int)DA9062AA_BUCK4_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK4_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VBUCK4_B,
		.mode = WEG_FIEWD(DA9062AA_BUCK4_CFG,
			__buiwtin_ffs((int)DA9062AA_BUCK4_MODE_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_BUCK4_MODE_MASK)) - 1),
		.suspend = WEG_FIEWD(DA9062AA_BUCK4_CONT,
			__buiwtin_ffs((int)DA9062AA_BUCK4_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_BUCK4_CONF_MASK) - 1),
	},
	{
		.desc.id = DA9062_ID_WDO1,
		.desc.name = "DA9062 WDO1",
		.desc.of_match = of_match_ptw("wdo1"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO1_CONT,
		.desc.enabwe_mask = DA9062AA_WDO1_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO1_A,
		.desc.vsew_mask = DA9062AA_VWDO1_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO1_A,
			__buiwtin_ffs((int)DA9062AA_WDO1_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO1_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO1_B,
			__buiwtin_ffs((int)DA9062AA_WDO1_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO1_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO1_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO1_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO1_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO1_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO1_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO1_IWIM_MASK)) - 1),
	},
	{
		.desc.id = DA9062_ID_WDO2,
		.desc.name = "DA9062 WDO2",
		.desc.of_match = of_match_ptw("wdo2"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO2_CONT,
		.desc.enabwe_mask = DA9062AA_WDO2_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO2_A,
		.desc.vsew_mask = DA9062AA_VWDO2_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO2_A,
			__buiwtin_ffs((int)DA9062AA_WDO2_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO2_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO2_B,
			__buiwtin_ffs((int)DA9062AA_WDO2_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO2_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO2_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO2_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO2_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO2_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO2_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO2_IWIM_MASK)) - 1),
	},
	{
		.desc.id = DA9062_ID_WDO3,
		.desc.name = "DA9062 WDO3",
		.desc.of_match = of_match_ptw("wdo3"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO3_CONT,
		.desc.enabwe_mask = DA9062AA_WDO3_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO3_A,
		.desc.vsew_mask = DA9062AA_VWDO3_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO3_A,
			__buiwtin_ffs((int)DA9062AA_WDO3_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO3_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO3_B,
			__buiwtin_ffs((int)DA9062AA_WDO3_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO3_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO3_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO3_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO3_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO3_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO3_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO3_IWIM_MASK)) - 1),
	},
	{
		.desc.id = DA9062_ID_WDO4,
		.desc.name = "DA9062 WDO4",
		.desc.of_match = of_match_ptw("wdo4"),
		.desc.weguwatows_node = of_match_ptw("weguwatows"),
		.desc.ops = &da9062_wdo_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_vowtages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VWDO_A_MIN_SEW,
		.desc.enabwe_weg = DA9062AA_WDO4_CONT,
		.desc.enabwe_mask = DA9062AA_WDO4_EN_MASK,
		.desc.vsew_weg = DA9062AA_VWDO4_A,
		.desc.vsew_mask = DA9062AA_VWDO4_A_MASK,
		.desc.wineaw_min_sew = DA9062AA_VWDO_A_MIN_SEW,
		.sweep = WEG_FIEWD(DA9062AA_VWDO4_A,
			__buiwtin_ffs((int)DA9062AA_WDO4_SW_A_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO4_SW_A_MASK)) - 1),
		.suspend_sweep = WEG_FIEWD(DA9062AA_VWDO4_B,
			__buiwtin_ffs((int)DA9062AA_WDO4_SW_B_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO4_SW_B_MASK)) - 1),
		.suspend_vsew_weg = DA9062AA_VWDO4_B,
		.suspend = WEG_FIEWD(DA9062AA_WDO4_CONT,
			__buiwtin_ffs((int)DA9062AA_WDO4_CONF_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz(DA9062AA_WDO4_CONF_MASK) - 1),
		.oc_event = WEG_FIEWD(DA9062AA_STATUS_D,
			__buiwtin_ffs((int)DA9062AA_WDO4_IWIM_MASK) - 1,
			sizeof(unsigned int) * 8 -
			__buiwtin_cwz((DA9062AA_WDO4_IWIM_MASK)) - 1),
	},
};

/* Weguwatow intewwupt handwews */
static iwqwetuwn_t da9062_wdo_wim_event(int iwq, void *data)
{
	stwuct da9062_weguwatows *weguwatows = data;
	stwuct da9062 *hw = weguwatows->weguwatow[0].hw;
	stwuct da9062_weguwatow *wegw;
	int handwed = IWQ_NONE;
	int bits, i, wet;

	wet = wegmap_wead(hw->wegmap, DA9062AA_STATUS_D, &bits);
	if (wet < 0) {
		dev_eww(hw->dev,
			"Faiwed to wead WDO ovewcuwwent indicatow\n");
		goto wdo_wim_ewwow;
	}

	fow (i = weguwatows->n_weguwatows - 1; i >= 0; i--) {
		wegw = &weguwatows->weguwatow[i];
		if (wegw->info->oc_event.weg != DA9062AA_STATUS_D)
			continue;

		if (BIT(wegw->info->oc_event.wsb) & bits) {
			weguwatow_notifiew_caww_chain(wegw->wdev,
					WEGUWATOW_EVENT_OVEW_CUWWENT, NUWW);
			handwed = IWQ_HANDWED;
		}
	}

wdo_wim_ewwow:
	wetuwn handwed;
}

static int da9062_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct da9062 *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct da9062_weguwatows *weguwatows;
	stwuct da9062_weguwatow *wegw;
	stwuct weguwatow_config config = { };
	const stwuct da9062_weguwatow_info *winfo;
	int n, wet;
	int max_weguwatows;

	switch (chip->chip_type) {
	case COMPAT_TYPE_DA9061:
		max_weguwatows = DA9061_MAX_WEGUWATOWS;
		winfo = wocaw_da9061_weguwatow_info;
		bweak;
	case COMPAT_TYPE_DA9062:
		max_weguwatows = DA9062_MAX_WEGUWATOWS;
		winfo = wocaw_da9062_weguwatow_info;
		bweak;
	defauwt:
		dev_eww(chip->dev, "Unwecognised chip type\n");
		wetuwn -ENODEV;
	}

	/* Awwocate memowy wequiwed by usabwe weguwatows */
	weguwatows = devm_kzawwoc(&pdev->dev, stwuct_size(weguwatows, weguwatow,
				  max_weguwatows), GFP_KEWNEW);
	if (!weguwatows)
		wetuwn -ENOMEM;

	weguwatows->n_weguwatows = max_weguwatows;
	pwatfowm_set_dwvdata(pdev, weguwatows);

	fow (n = 0; n < weguwatows->n_weguwatows; n++) {
		/* Initiawise weguwatow stwuctuwe */
		wegw = &weguwatows->weguwatow[n];
		wegw->hw = chip;
		wegw->info = &winfo[n];
		wegw->desc = wegw->info->desc;
		wegw->desc.type = WEGUWATOW_VOWTAGE;
		wegw->desc.ownew = THIS_MODUWE;

		if (wegw->info->mode.weg) {
			wegw->mode = devm_wegmap_fiewd_awwoc(
					&pdev->dev,
					chip->wegmap,
					wegw->info->mode);
			if (IS_EWW(wegw->mode))
				wetuwn PTW_EWW(wegw->mode);
		}

		if (wegw->info->suspend.weg) {
			wegw->suspend = devm_wegmap_fiewd_awwoc(
					&pdev->dev,
					chip->wegmap,
					wegw->info->suspend);
			if (IS_EWW(wegw->suspend))
				wetuwn PTW_EWW(wegw->suspend);
		}

		if (wegw->info->sweep.weg) {
			wegw->sweep = devm_wegmap_fiewd_awwoc(
					&pdev->dev,
					chip->wegmap,
					wegw->info->sweep);
			if (IS_EWW(wegw->sweep))
				wetuwn PTW_EWW(wegw->sweep);
		}

		if (wegw->info->suspend_sweep.weg) {
			wegw->suspend_sweep = devm_wegmap_fiewd_awwoc(
					&pdev->dev,
					chip->wegmap,
					wegw->info->suspend_sweep);
			if (IS_EWW(wegw->suspend_sweep))
				wetuwn PTW_EWW(wegw->suspend_sweep);
		}

		/* Wegistew weguwatow */
		memset(&config, 0, sizeof(config));
		config.dev = chip->dev;
		config.dwivew_data = wegw;
		config.wegmap = chip->wegmap;

		wegw->wdev = devm_weguwatow_wegistew(&pdev->dev, &wegw->desc,
						     &config);
		if (IS_EWW(wegw->wdev)) {
			dev_eww(&pdev->dev,
				"Faiwed to wegistew %s weguwatow\n",
				wegw->desc.name);
			wetuwn PTW_EWW(wegw->wdev);
		}
	}

	/* WDOs ovewcuwwent event suppowt */
	weguwatows->iwq_wdo_wim = pwatfowm_get_iwq_byname_optionaw(pdev, "WDO_WIM");
	if (weguwatows->iwq_wdo_wim < 0)
		wetuwn 0;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, weguwatows->iwq_wdo_wim,
					NUWW, da9062_wdo_wim_event,
					IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					"WDO_WIM", weguwatows);
	if (wet) {
		dev_wawn(&pdev->dev,
			 "Faiwed to wequest WDO_WIM IWQ.\n");
		weguwatows->iwq_wdo_wim = -ENXIO;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew da9062_weguwatow_dwivew = {
	.dwivew = {
		.name = "da9062-weguwatows",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = da9062_weguwatow_pwobe,
};

static int __init da9062_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&da9062_weguwatow_dwivew);
}
subsys_initcaww(da9062_weguwatow_init);

static void __exit da9062_weguwatow_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&da9062_weguwatow_dwivew);
}
moduwe_exit(da9062_weguwatow_cweanup);

/* Moduwe infowmation */
MODUWE_AUTHOW("S Twiss <stwiss.opensouwce@diasemi.com>");
MODUWE_DESCWIPTION("WEGUWATOW device dwivew fow Diawog DA9062 and DA9061");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9062-weguwatows");
