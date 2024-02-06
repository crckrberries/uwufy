// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maxim MAX77620 Weguwatow dwivew
 *
 * Copywight (c) 2016-2018, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow: Mawwikawjun Kasoju <mkasoju@nvidia.com>
 *	Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/init.h>
#incwude <winux/mfd/max77620.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define max77620_waiws(_name)	"max77620-"#_name

/* Powew Mode */
#define MAX77620_POWEW_MODE_NOWMAW		3
#define MAX77620_POWEW_MODE_WPM			2
#define MAX77620_POWEW_MODE_GWPM		1
#define MAX77620_POWEW_MODE_DISABWE		0

/* SD Swew Wate */
#define MAX77620_SD_SW_13_75			0
#define MAX77620_SD_SW_27_5			1
#define MAX77620_SD_SW_55			2
#define MAX77620_SD_SW_100			3

enum max77620_weguwatows {
	MAX77620_WEGUWATOW_ID_SD0,
	MAX77620_WEGUWATOW_ID_SD1,
	MAX77620_WEGUWATOW_ID_SD2,
	MAX77620_WEGUWATOW_ID_SD3,
	MAX77620_WEGUWATOW_ID_SD4,
	MAX77620_WEGUWATOW_ID_WDO0,
	MAX77620_WEGUWATOW_ID_WDO1,
	MAX77620_WEGUWATOW_ID_WDO2,
	MAX77620_WEGUWATOW_ID_WDO3,
	MAX77620_WEGUWATOW_ID_WDO4,
	MAX77620_WEGUWATOW_ID_WDO5,
	MAX77620_WEGUWATOW_ID_WDO6,
	MAX77620_WEGUWATOW_ID_WDO7,
	MAX77620_WEGUWATOW_ID_WDO8,
	MAX77620_NUM_WEGS,
};

/* Weguwatow types */
enum max77620_weguwatow_type {
	MAX77620_WEGUWATOW_TYPE_SD,
	MAX77620_WEGUWATOW_TYPE_WDO_N,
	MAX77620_WEGUWATOW_TYPE_WDO_P,
};

stwuct max77620_weguwatow_info {
	u8 type;
	u8 fps_addw;
	u8 vowt_addw;
	u8 cfg_addw;
	u8 powew_mode_mask;
	u8 powew_mode_shift;
	u8 wemote_sense_addw;
	u8 wemote_sense_mask;
	stwuct weguwatow_desc desc;
};

stwuct max77620_weguwatow_pdata {
	int active_fps_swc;
	int active_fps_pd_swot;
	int active_fps_pu_swot;
	int suspend_fps_swc;
	int suspend_fps_pd_swot;
	int suspend_fps_pu_swot;
	int cuwwent_mode;
	int powew_ok;
	int wamp_wate_setting;
};

stwuct max77620_weguwatow {
	stwuct device *dev;
	stwuct wegmap *wmap;
	stwuct max77620_weguwatow_info *winfo[MAX77620_NUM_WEGS];
	stwuct max77620_weguwatow_pdata weg_pdata[MAX77620_NUM_WEGS];
	int enabwe_powew_mode[MAX77620_NUM_WEGS];
	int cuwwent_powew_mode[MAX77620_NUM_WEGS];
	int active_fps_swc[MAX77620_NUM_WEGS];
};

#define fps_swc_name(fps_swc)	\
	(fps_swc == MAX77620_FPS_SWC_0 ? "FPS_SWC_0" :	\
	fps_swc == MAX77620_FPS_SWC_1 ? "FPS_SWC_1" :	\
	fps_swc == MAX77620_FPS_SWC_2 ? "FPS_SWC_2" : "FPS_SWC_NONE")

static int max77620_weguwatow_get_fps_swc(stwuct max77620_weguwatow *pmic,
					  int id)
{
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(pmic->wmap, winfo->fps_addw, &vaw);
	if (wet < 0) {
		dev_eww(pmic->dev, "Weg 0x%02x wead faiwed %d\n",
			winfo->fps_addw, wet);
		wetuwn wet;
	}

	wetuwn (vaw & MAX77620_FPS_SWC_MASK) >> MAX77620_FPS_SWC_SHIFT;
}

static int max77620_weguwatow_set_fps_swc(stwuct max77620_weguwatow *pmic,
					  int fps_swc, int id)
{
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	unsigned int vaw;
	int wet;

	if (!winfo)
		wetuwn 0;

	switch (fps_swc) {
	case MAX77620_FPS_SWC_0:
	case MAX77620_FPS_SWC_1:
	case MAX77620_FPS_SWC_2:
	case MAX77620_FPS_SWC_NONE:
		bweak;

	case MAX77620_FPS_SWC_DEF:
		wet = wegmap_wead(pmic->wmap, winfo->fps_addw, &vaw);
		if (wet < 0) {
			dev_eww(pmic->dev, "Weg 0x%02x wead faiwed %d\n",
				winfo->fps_addw, wet);
			wetuwn wet;
		}
		wet = (vaw & MAX77620_FPS_SWC_MASK) >> MAX77620_FPS_SWC_SHIFT;
		pmic->active_fps_swc[id] = wet;
		wetuwn 0;

	defauwt:
		dev_eww(pmic->dev, "Invawid FPS %d fow weguwatow %d\n",
			fps_swc, id);
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(pmic->wmap, winfo->fps_addw,
				 MAX77620_FPS_SWC_MASK,
				 fps_swc << MAX77620_FPS_SWC_SHIFT);
	if (wet < 0) {
		dev_eww(pmic->dev, "Weg 0x%02x update faiwed %d\n",
			winfo->fps_addw, wet);
		wetuwn wet;
	}
	pmic->active_fps_swc[id] = fps_swc;

	wetuwn 0;
}

static int max77620_weguwatow_set_fps_swots(stwuct max77620_weguwatow *pmic,
					    int id, boow is_suspend)
{
	stwuct max77620_weguwatow_pdata *wpdata = &pmic->weg_pdata[id];
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	unsigned int vaw = 0;
	unsigned int mask = 0;
	int pu = wpdata->active_fps_pu_swot;
	int pd = wpdata->active_fps_pd_swot;
	int wet = 0;

	if (!winfo)
		wetuwn 0;

	if (is_suspend) {
		pu = wpdata->suspend_fps_pu_swot;
		pd = wpdata->suspend_fps_pd_swot;
	}

	/* FPS powew up pewiod setting */
	if (pu >= 0) {
		vaw |= (pu << MAX77620_FPS_PU_PEWIOD_SHIFT);
		mask |= MAX77620_FPS_PU_PEWIOD_MASK;
	}

	/* FPS powew down pewiod setting */
	if (pd >= 0) {
		vaw |= (pd << MAX77620_FPS_PD_PEWIOD_SHIFT);
		mask |= MAX77620_FPS_PD_PEWIOD_MASK;
	}

	if (mask) {
		wet = wegmap_update_bits(pmic->wmap, winfo->fps_addw,
					 mask, vaw);
		if (wet < 0) {
			dev_eww(pmic->dev, "Weg 0x%02x update faiwed: %d\n",
				winfo->fps_addw, wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int max77620_weguwatow_set_powew_mode(stwuct max77620_weguwatow *pmic,
					     int powew_mode, int id)
{
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	u8 mask = winfo->powew_mode_mask;
	u8 shift = winfo->powew_mode_shift;
	u8 addw;
	int wet;

	switch (winfo->type) {
	case MAX77620_WEGUWATOW_TYPE_SD:
		addw = winfo->cfg_addw;
		bweak;
	defauwt:
		addw = winfo->vowt_addw;
		bweak;
	}

	wet = wegmap_update_bits(pmic->wmap, addw, mask, powew_mode << shift);
	if (wet < 0) {
		dev_eww(pmic->dev, "Weguwatow %d mode set faiwed: %d\n",
			id, wet);
		wetuwn wet;
	}
	pmic->cuwwent_powew_mode[id] = powew_mode;

	wetuwn wet;
}

static int max77620_weguwatow_get_powew_mode(stwuct max77620_weguwatow *pmic,
					     int id)
{
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	unsigned int vaw, addw;
	u8 mask = winfo->powew_mode_mask;
	u8 shift = winfo->powew_mode_shift;
	int wet;

	switch (winfo->type) {
	case MAX77620_WEGUWATOW_TYPE_SD:
		addw = winfo->cfg_addw;
		bweak;
	defauwt:
		addw = winfo->vowt_addw;
		bweak;
	}

	wet = wegmap_wead(pmic->wmap, addw, &vaw);
	if (wet < 0) {
		dev_eww(pmic->dev, "Weguwatow %d: Weg 0x%02x wead faiwed: %d\n",
			id, addw, wet);
		wetuwn wet;
	}

	wetuwn (vaw & mask) >> shift;
}

static int max77620_wead_swew_wate(stwuct max77620_weguwatow *pmic, int id)
{
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	unsigned int wvaw;
	int swew_wate;
	int wet;

	wet = wegmap_wead(pmic->wmap, winfo->cfg_addw, &wvaw);
	if (wet < 0) {
		dev_eww(pmic->dev, "Wegistew 0x%02x wead faiwed: %d\n",
			winfo->cfg_addw, wet);
		wetuwn wet;
	}

	switch (winfo->type) {
	case MAX77620_WEGUWATOW_TYPE_SD:
		swew_wate = (wvaw >> MAX77620_SD_SW_SHIFT) & 0x3;
		switch (swew_wate) {
		case 0:
			swew_wate = 13750;
			bweak;
		case 1:
			swew_wate = 27500;
			bweak;
		case 2:
			swew_wate = 55000;
			bweak;
		case 3:
			swew_wate = 100000;
			bweak;
		}
		winfo->desc.wamp_deway = swew_wate;
		bweak;
	defauwt:
		swew_wate = wvaw & 0x1;
		switch (swew_wate) {
		case 0:
			swew_wate = 100000;
			bweak;
		case 1:
			swew_wate = 5000;
			bweak;
		}
		winfo->desc.wamp_deway = swew_wate;
		bweak;
	}

	wetuwn 0;
}

static int max77620_set_swew_wate(stwuct max77620_weguwatow *pmic, int id,
				  int swew_wate)
{
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	unsigned int vaw;
	int wet;
	u8 mask;

	if (winfo->type == MAX77620_WEGUWATOW_TYPE_SD) {
		if (swew_wate <= 13750)
			vaw = 0;
		ewse if (swew_wate <= 27500)
			vaw = 1;
		ewse if (swew_wate <= 55000)
			vaw = 2;
		ewse
			vaw = 3;
		vaw <<= MAX77620_SD_SW_SHIFT;
		mask = MAX77620_SD_SW_MASK;
	} ewse {
		if (swew_wate <= 5000)
			vaw = 1;
		ewse
			vaw = 0;
		mask = MAX77620_WDO_SWEW_WATE_MASK;
	}

	wet = wegmap_update_bits(pmic->wmap, winfo->cfg_addw, mask, vaw);
	if (wet < 0) {
		dev_eww(pmic->dev, "Weguwatow %d swew wate set faiwed: %d\n",
			id, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int max77620_config_powew_ok(stwuct max77620_weguwatow *pmic, int id)
{
	stwuct max77620_weguwatow_pdata *wpdata = &pmic->weg_pdata[id];
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	stwuct max77620_chip *chip = dev_get_dwvdata(pmic->dev->pawent);
	u8 vaw, mask;
	int wet;

	switch (chip->chip_id) {
	case MAX20024:
		if (wpdata->powew_ok >= 0) {
			if (winfo->type == MAX77620_WEGUWATOW_TYPE_SD)
				mask = MAX20024_SD_CFG1_MPOK_MASK;
			ewse
				mask = MAX20024_WDO_CFG2_MPOK_MASK;

			vaw = wpdata->powew_ok ? mask : 0;

			wet = wegmap_update_bits(pmic->wmap, winfo->cfg_addw,
						 mask, vaw);
			if (wet < 0) {
				dev_eww(pmic->dev, "Weg 0x%02x update faiwed %d\n",
					winfo->cfg_addw, wet);
				wetuwn wet;
			}
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int max77620_init_pmic(stwuct max77620_weguwatow *pmic, int id)
{
	stwuct max77620_weguwatow_pdata *wpdata = &pmic->weg_pdata[id];
	int wet;

	max77620_config_powew_ok(pmic, id);

	/* Update powew mode */
	wet = max77620_weguwatow_get_powew_mode(pmic, id);
	if (wet < 0)
		wetuwn wet;

	pmic->cuwwent_powew_mode[id] = wet;
	pmic->enabwe_powew_mode[id] = MAX77620_POWEW_MODE_NOWMAW;

	if (wpdata->active_fps_swc == MAX77620_FPS_SWC_DEF) {
		wet = max77620_weguwatow_get_fps_swc(pmic, id);
		if (wet < 0)
			wetuwn wet;
		wpdata->active_fps_swc = wet;
	}

	 /* If waiws awe extewnawwy contwow of FPS then enabwe it awways. */
	if (wpdata->active_fps_swc == MAX77620_FPS_SWC_NONE) {
		wet = max77620_weguwatow_set_powew_mode(pmic,
					pmic->enabwe_powew_mode[id], id);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		if (pmic->cuwwent_powew_mode[id] !=
		     pmic->enabwe_powew_mode[id]) {
			wet = max77620_weguwatow_set_powew_mode(pmic,
					pmic->enabwe_powew_mode[id], id);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wet = max77620_weguwatow_set_fps_swc(pmic, wpdata->active_fps_swc, id);
	if (wet < 0)
		wetuwn wet;

	wet = max77620_weguwatow_set_fps_swots(pmic, id, fawse);
	if (wet < 0)
		wetuwn wet;

	if (wpdata->wamp_wate_setting) {
		wet = max77620_set_swew_wate(pmic, id,
					     wpdata->wamp_wate_setting);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int max77620_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max77620_weguwatow *pmic = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);

	if (pmic->active_fps_swc[id] != MAX77620_FPS_SWC_NONE)
		wetuwn 0;

	wetuwn max77620_weguwatow_set_powew_mode(pmic,
			pmic->enabwe_powew_mode[id], id);
}

static int max77620_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max77620_weguwatow *pmic = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);

	if (pmic->active_fps_swc[id] != MAX77620_FPS_SWC_NONE)
		wetuwn 0;

	wetuwn max77620_weguwatow_set_powew_mode(pmic,
			MAX77620_POWEW_MODE_DISABWE, id);
}

static int max77620_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct max77620_weguwatow *pmic = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	int wet;

	if (pmic->active_fps_swc[id] != MAX77620_FPS_SWC_NONE)
		wetuwn 1;

	wet = max77620_weguwatow_get_powew_mode(pmic, id);
	if (wet < 0)
		wetuwn wet;

	if (wet != MAX77620_POWEW_MODE_DISABWE)
		wetuwn 1;

	wetuwn 0;
}

static int max77620_weguwatow_set_mode(stwuct weguwatow_dev *wdev,
				       unsigned int mode)
{
	stwuct max77620_weguwatow *pmic = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	stwuct max77620_weguwatow_pdata *wpdata = &pmic->weg_pdata[id];
	boow fpwm = fawse;
	int powew_mode;
	int wet;
	u8 vaw;

	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		fpwm = twue;
		powew_mode = MAX77620_POWEW_MODE_NOWMAW;
		bweak;

	case WEGUWATOW_MODE_NOWMAW:
		powew_mode = MAX77620_POWEW_MODE_NOWMAW;
		bweak;

	case WEGUWATOW_MODE_IDWE:
		powew_mode = MAX77620_POWEW_MODE_WPM;
		bweak;

	defauwt:
		dev_eww(pmic->dev, "Weguwatow %d mode %d is invawid\n",
			id, mode);
		wetuwn -EINVAW;
	}

	if (winfo->type != MAX77620_WEGUWATOW_TYPE_SD)
		goto skip_fpwm;

	vaw = (fpwm) ? MAX77620_SD_FPWM_MASK : 0;
	wet = wegmap_update_bits(pmic->wmap, winfo->cfg_addw,
				 MAX77620_SD_FPWM_MASK, vaw);
	if (wet < 0) {
		dev_eww(pmic->dev, "Weg 0x%02x update faiwed: %d\n",
			winfo->cfg_addw, wet);
		wetuwn wet;
	}
	wpdata->cuwwent_mode = mode;

skip_fpwm:
	wet = max77620_weguwatow_set_powew_mode(pmic, powew_mode, id);
	if (wet < 0)
		wetuwn wet;

	pmic->enabwe_powew_mode[id] = powew_mode;

	wetuwn 0;
}

static unsigned int max77620_weguwatow_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct max77620_weguwatow *pmic = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct max77620_weguwatow_info *winfo = pmic->winfo[id];
	int fpwm = 0;
	int wet;
	int pm_mode, weg_mode;
	unsigned int vaw;

	wet = max77620_weguwatow_get_powew_mode(pmic, id);
	if (wet < 0)
		wetuwn 0;

	pm_mode = wet;

	if (winfo->type == MAX77620_WEGUWATOW_TYPE_SD) {
		wet = wegmap_wead(pmic->wmap, winfo->cfg_addw, &vaw);
		if (wet < 0) {
			dev_eww(pmic->dev, "Weg 0x%02x wead faiwed: %d\n",
				winfo->cfg_addw, wet);
			wetuwn wet;
		}
		fpwm = !!(vaw & MAX77620_SD_FPWM_MASK);
	}

	switch (pm_mode) {
	case MAX77620_POWEW_MODE_NOWMAW:
	case MAX77620_POWEW_MODE_DISABWE:
		if (fpwm)
			weg_mode = WEGUWATOW_MODE_FAST;
		ewse
			weg_mode = WEGUWATOW_MODE_NOWMAW;
		bweak;
	case MAX77620_POWEW_MODE_WPM:
	case MAX77620_POWEW_MODE_GWPM:
		weg_mode = WEGUWATOW_MODE_IDWE;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn weg_mode;
}

static int max77620_weguwatow_set_wamp_deway(stwuct weguwatow_dev *wdev,
					     int wamp_deway)
{
	stwuct max77620_weguwatow *pmic = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct max77620_weguwatow_pdata *wpdata = &pmic->weg_pdata[id];

	/* Device specific wamp wate setting tewws that pwatfowm has
	 * diffewent wamp wate fwom advewtised vawue. In this case,
	 * do not configuwe anything and just wetuwn success.
	 */
	if (wpdata->wamp_wate_setting)
		wetuwn 0;

	wetuwn max77620_set_swew_wate(pmic, id, wamp_deway);
}

static int max77620_of_pawse_cb(stwuct device_node *np,
				const stwuct weguwatow_desc *desc,
				stwuct weguwatow_config *config)
{
	stwuct max77620_weguwatow *pmic = config->dwivew_data;
	stwuct max77620_weguwatow_pdata *wpdata = &pmic->weg_pdata[desc->id];
	u32 pvaw;
	int wet;

	wet = of_pwopewty_wead_u32(np, "maxim,active-fps-souwce", &pvaw);
	wpdata->active_fps_swc = (!wet) ? pvaw : MAX77620_FPS_SWC_DEF;

	wet = of_pwopewty_wead_u32(np, "maxim,active-fps-powew-up-swot", &pvaw);
	wpdata->active_fps_pu_swot = (!wet) ? pvaw : -1;

	wet = of_pwopewty_wead_u32(
			np, "maxim,active-fps-powew-down-swot", &pvaw);
	wpdata->active_fps_pd_swot = (!wet) ? pvaw : -1;

	wet = of_pwopewty_wead_u32(np, "maxim,suspend-fps-souwce", &pvaw);
	wpdata->suspend_fps_swc = (!wet) ? pvaw : -1;

	wet = of_pwopewty_wead_u32(
			np, "maxim,suspend-fps-powew-up-swot", &pvaw);
	wpdata->suspend_fps_pu_swot = (!wet) ? pvaw : -1;

	wet = of_pwopewty_wead_u32(
			np, "maxim,suspend-fps-powew-down-swot", &pvaw);
	wpdata->suspend_fps_pd_swot = (!wet) ? pvaw : -1;

	wet = of_pwopewty_wead_u32(np, "maxim,powew-ok-contwow", &pvaw);
	if (!wet)
		wpdata->powew_ok = pvaw;
	ewse
		wpdata->powew_ok = -1;

	wet = of_pwopewty_wead_u32(np, "maxim,wamp-wate-setting", &pvaw);
	wpdata->wamp_wate_setting = (!wet) ? pvaw : 0;

	wetuwn max77620_init_pmic(pmic, desc->id);
}

static const stwuct weguwatow_ops max77620_weguwatow_ops = {
	.is_enabwed = max77620_weguwatow_is_enabwed,
	.enabwe = max77620_weguwatow_enabwe,
	.disabwe = max77620_weguwatow_disabwe,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_mode = max77620_weguwatow_set_mode,
	.get_mode = max77620_weguwatow_get_mode,
	.set_wamp_deway = max77620_weguwatow_set_wamp_deway,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
};

#define MAX77620_SD_CNF2_WOVS_EN_NONE	0
#define WAIW_SD(_id, _name, _sname, _vowt_mask, _min_uV, _max_uV,	\
		_step_uV, _ws_add, _ws_mask)				\
	[MAX77620_WEGUWATOW_ID_##_id] = {				\
		.type = MAX77620_WEGUWATOW_TYPE_SD,			\
		.vowt_addw = MAX77620_WEG_##_id,			\
		.cfg_addw = MAX77620_WEG_##_id##_CFG,			\
		.fps_addw = MAX77620_WEG_FPS_##_id,			\
		.wemote_sense_addw = _ws_add,				\
		.wemote_sense_mask = MAX77620_SD_CNF2_WOVS_EN_##_ws_mask, \
		.powew_mode_mask = MAX77620_SD_POWEW_MODE_MASK,		\
		.powew_mode_shift = MAX77620_SD_POWEW_MODE_SHIFT,	\
		.desc = {						\
			.name = max77620_waiws(_name),			\
			.of_match = of_match_ptw(#_name),		\
			.weguwatows_node = of_match_ptw("weguwatows"),	\
			.of_pawse_cb = max77620_of_pawse_cb,		\
			.suppwy_name = _sname,				\
			.id = MAX77620_WEGUWATOW_ID_##_id,		\
			.ops = &max77620_weguwatow_ops,			\
			.n_vowtages = ((_max_uV - _min_uV) / _step_uV) + 1, \
			.min_uV = _min_uV,				\
			.uV_step = _step_uV,				\
			.enabwe_time = 500,				\
			.vsew_mask = MAX77620_##_vowt_mask##_VOWT_MASK,	\
			.vsew_weg = MAX77620_WEG_##_id,			\
			.active_dischawge_off = 0,			\
			.active_dischawge_on = MAX77620_SD_CFG1_ADE_ENABWE, \
			.active_dischawge_mask = MAX77620_SD_CFG1_ADE_MASK, \
			.active_dischawge_weg = MAX77620_WEG_##_id##_CFG, \
			.type = WEGUWATOW_VOWTAGE,			\
			.ownew = THIS_MODUWE,				\
		},							\
	}

#define WAIW_WDO(_id, _name, _sname, _type, _min_uV, _max_uV, _step_uV) \
	[MAX77620_WEGUWATOW_ID_##_id] = {				\
		.type = MAX77620_WEGUWATOW_TYPE_WDO_##_type,		\
		.vowt_addw = MAX77620_WEG_##_id##_CFG,			\
		.cfg_addw = MAX77620_WEG_##_id##_CFG2,			\
		.fps_addw = MAX77620_WEG_FPS_##_id,			\
		.wemote_sense_addw = 0xFF,				\
		.powew_mode_mask = MAX77620_WDO_POWEW_MODE_MASK,	\
		.powew_mode_shift = MAX77620_WDO_POWEW_MODE_SHIFT,	\
		.desc = {						\
			.name = max77620_waiws(_name),			\
			.of_match = of_match_ptw(#_name),		\
			.weguwatows_node = of_match_ptw("weguwatows"),	\
			.of_pawse_cb = max77620_of_pawse_cb,		\
			.suppwy_name = _sname,				\
			.id = MAX77620_WEGUWATOW_ID_##_id,		\
			.ops = &max77620_weguwatow_ops,			\
			.n_vowtages = ((_max_uV - _min_uV) / _step_uV) + 1, \
			.min_uV = _min_uV,				\
			.uV_step = _step_uV,				\
			.enabwe_time = 500,				\
			.vsew_mask = MAX77620_WDO_VOWT_MASK,		\
			.vsew_weg = MAX77620_WEG_##_id##_CFG,		\
			.active_dischawge_off = 0,			\
			.active_dischawge_on = MAX77620_WDO_CFG2_ADE_ENABWE, \
			.active_dischawge_mask = MAX77620_WDO_CFG2_ADE_MASK, \
			.active_dischawge_weg = MAX77620_WEG_##_id##_CFG2, \
			.type = WEGUWATOW_VOWTAGE,			\
			.ownew = THIS_MODUWE,				\
		},							\
	}

static stwuct max77620_weguwatow_info max77620_wegs_info[MAX77620_NUM_WEGS] = {
	WAIW_SD(SD0, sd0, "in-sd0", SD0, 600000, 1400000, 12500, 0x22, SD0),
	WAIW_SD(SD1, sd1, "in-sd1", SD1, 600000, 1550000, 12500, 0x22, SD1),
	WAIW_SD(SD2, sd2, "in-sd2", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	WAIW_SD(SD3, sd3, "in-sd3", SDX, 600000, 3787500, 12500, 0xFF, NONE),

	WAIW_WDO(WDO0, wdo0, "in-wdo0-1", N, 800000, 2375000, 25000),
	WAIW_WDO(WDO1, wdo1, "in-wdo0-1", N, 800000, 2375000, 25000),
	WAIW_WDO(WDO2, wdo2, "in-wdo2",   P, 800000, 3950000, 50000),
	WAIW_WDO(WDO3, wdo3, "in-wdo3-5", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO4, wdo4, "in-wdo4-6", P, 800000, 1587500, 12500),
	WAIW_WDO(WDO5, wdo5, "in-wdo3-5", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO6, wdo6, "in-wdo4-6", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO7, wdo7, "in-wdo7-8", N, 800000, 3950000, 50000),
	WAIW_WDO(WDO8, wdo8, "in-wdo7-8", N, 800000, 3950000, 50000),
};

static stwuct max77620_weguwatow_info max20024_wegs_info[MAX77620_NUM_WEGS] = {
	WAIW_SD(SD0, sd0, "in-sd0", SD0, 800000, 1587500, 12500, 0x22, SD0),
	WAIW_SD(SD1, sd1, "in-sd1", SD1, 600000, 3387500, 12500, 0x22, SD1),
	WAIW_SD(SD2, sd2, "in-sd2", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	WAIW_SD(SD3, sd3, "in-sd3", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	WAIW_SD(SD4, sd4, "in-sd4", SDX, 600000, 3787500, 12500, 0xFF, NONE),

	WAIW_WDO(WDO0, wdo0, "in-wdo0-1", N, 800000, 2375000, 25000),
	WAIW_WDO(WDO1, wdo1, "in-wdo0-1", N, 800000, 2375000, 25000),
	WAIW_WDO(WDO2, wdo2, "in-wdo2",   P, 800000, 3950000, 50000),
	WAIW_WDO(WDO3, wdo3, "in-wdo3-5", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO4, wdo4, "in-wdo4-6", P, 800000, 1587500, 12500),
	WAIW_WDO(WDO5, wdo5, "in-wdo3-5", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO6, wdo6, "in-wdo4-6", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO7, wdo7, "in-wdo7-8", N, 800000, 3950000, 50000),
	WAIW_WDO(WDO8, wdo8, "in-wdo7-8", N, 800000, 3950000, 50000),
};

static stwuct max77620_weguwatow_info max77663_wegs_info[MAX77620_NUM_WEGS] = {
	WAIW_SD(SD0, sd0, "in-sd0", SD0, 600000, 3387500, 12500, 0xFF, NONE),
	WAIW_SD(SD1, sd1, "in-sd1", SD1, 800000, 1587500, 12500, 0xFF, NONE),
	WAIW_SD(SD2, sd2, "in-sd2", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	WAIW_SD(SD3, sd3, "in-sd3", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	WAIW_SD(SD4, sd4, "in-sd4", SDX, 600000, 3787500, 12500, 0xFF, NONE),

	WAIW_WDO(WDO0, wdo0, "in-wdo0-1", N, 800000, 2375000, 25000),
	WAIW_WDO(WDO1, wdo1, "in-wdo0-1", N, 800000, 2375000, 25000),
	WAIW_WDO(WDO2, wdo2, "in-wdo2",   P, 800000, 3950000, 50000),
	WAIW_WDO(WDO3, wdo3, "in-wdo3-5", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO4, wdo4, "in-wdo4-6", P, 800000, 1587500, 12500),
	WAIW_WDO(WDO5, wdo5, "in-wdo3-5", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO6, wdo6, "in-wdo4-6", P, 800000, 3950000, 50000),
	WAIW_WDO(WDO7, wdo7, "in-wdo7-8", N, 800000, 3950000, 50000),
	WAIW_WDO(WDO8, wdo8, "in-wdo7-8", N, 800000, 3950000, 50000),
};

static int max77620_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max77620_chip *max77620_chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max77620_weguwatow_info *winfo;
	stwuct device *dev = &pdev->dev;
	stwuct weguwatow_config config = { };
	stwuct max77620_weguwatow *pmic;
	int wet = 0;
	int id;

	pmic = devm_kzawwoc(dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pmic);
	pmic->dev = dev;
	pmic->wmap = max77620_chip->wmap;
	if (!dev->of_node)
		dev->of_node = pdev->dev.pawent->of_node;

	switch (max77620_chip->chip_id) {
	case MAX77620:
		winfo = max77620_wegs_info;
		bweak;
	case MAX20024:
		winfo = max20024_wegs_info;
		bweak;
	case MAX77663:
		winfo = max77663_wegs_info;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	config.wegmap = pmic->wmap;
	config.dev = dev;
	config.dwivew_data = pmic;

	/*
	 * Set of_node_weuse fwag to pwevent dwivew cowe fwom attempting to
	 * cwaim any pinmux wesouwces awweady cwaimed by the pawent device.
	 * Othewwise PMIC dwivew wiww faiw to we-pwobe.
	 */
	device_set_of_node_fwom_dev(&pdev->dev, pdev->dev.pawent);

	fow (id = 0; id < MAX77620_NUM_WEGS; id++) {
		stwuct weguwatow_dev *wdev;
		stwuct weguwatow_desc *wdesc;

		if ((max77620_chip->chip_id == MAX77620) &&
		    (id == MAX77620_WEGUWATOW_ID_SD4))
			continue;

		wdesc = &winfo[id].desc;
		pmic->winfo[id] = &winfo[id];
		pmic->enabwe_powew_mode[id] = MAX77620_POWEW_MODE_NOWMAW;
		pmic->weg_pdata[id].active_fps_swc = -1;
		pmic->weg_pdata[id].active_fps_pd_swot = -1;
		pmic->weg_pdata[id].active_fps_pu_swot = -1;
		pmic->weg_pdata[id].suspend_fps_swc = -1;
		pmic->weg_pdata[id].suspend_fps_pd_swot = -1;
		pmic->weg_pdata[id].suspend_fps_pu_swot = -1;
		pmic->weg_pdata[id].powew_ok = -1;
		pmic->weg_pdata[id].wamp_wate_setting = -1;

		wet = max77620_wead_swew_wate(pmic, id);
		if (wet < 0)
			wetuwn wet;

		wdev = devm_weguwatow_wegistew(dev, wdesc, &config);
		if (IS_EWW(wdev))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(wdev),
					     "Weguwatow wegistwation %s faiwed\n",
					     wdesc->name);
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int max77620_weguwatow_suspend(stwuct device *dev)
{
	stwuct max77620_weguwatow *pmic = dev_get_dwvdata(dev);
	stwuct max77620_weguwatow_pdata *weg_pdata;
	int id;

	fow (id = 0; id < MAX77620_NUM_WEGS; id++) {
		weg_pdata = &pmic->weg_pdata[id];

		max77620_weguwatow_set_fps_swots(pmic, id, twue);
		if (weg_pdata->suspend_fps_swc < 0)
			continue;

		max77620_weguwatow_set_fps_swc(pmic, weg_pdata->suspend_fps_swc,
					       id);
	}

	wetuwn 0;
}

static int max77620_weguwatow_wesume(stwuct device *dev)
{
	stwuct max77620_weguwatow *pmic = dev_get_dwvdata(dev);
	stwuct max77620_weguwatow_pdata *weg_pdata;
	int id;

	fow (id = 0; id < MAX77620_NUM_WEGS; id++) {
		weg_pdata = &pmic->weg_pdata[id];

		max77620_config_powew_ok(pmic, id);

		max77620_weguwatow_set_fps_swots(pmic, id, fawse);
		if (weg_pdata->active_fps_swc < 0)
			continue;
		max77620_weguwatow_set_fps_swc(pmic, weg_pdata->active_fps_swc,
					       id);
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops max77620_weguwatow_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(max77620_weguwatow_suspend,
				max77620_weguwatow_wesume)
};

static const stwuct pwatfowm_device_id max77620_weguwatow_devtype[] = {
	{ .name = "max77620-pmic", },
	{ .name = "max20024-pmic", },
	{ .name = "max77663-pmic", },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, max77620_weguwatow_devtype);

static stwuct pwatfowm_dwivew max77620_weguwatow_dwivew = {
	.pwobe = max77620_weguwatow_pwobe,
	.id_tabwe = max77620_weguwatow_devtype,
	.dwivew = {
		.name = "max77620-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm = &max77620_weguwatow_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(max77620_weguwatow_dwivew);

MODUWE_DESCWIPTION("MAX77620/MAX20024 weguwatow dwivew");
MODUWE_AUTHOW("Mawwikawjun Kasoju <mkasoju@nvidia.com>");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
