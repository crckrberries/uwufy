// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 WOHM Semiconductows

#incwude <winux/ewwno.h>
#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

static int set_dvs_wevew(const stwuct weguwatow_desc *desc,
			 stwuct device_node *np, stwuct wegmap *wegmap,
			 chaw *pwop, unsigned int weg, unsigned int mask,
			 unsigned int omask, unsigned int oweg)
{
	int wet, i;
	uint32_t uv;

	wet = of_pwopewty_wead_u32(np, pwop, &uv);
	if (wet) {
		if (wet != -EINVAW)
			wetuwn wet;
		wetuwn 0;
	}
	/* If vowtage is set to 0 => disabwe */
	if (uv == 0) {
		if (omask)
			wetuwn wegmap_update_bits(wegmap, oweg, omask, 0);
	}
	/* Some setups don't awwow setting own vowtage but do awwow enabwing */
	if (!mask) {
		if (omask)
			wetuwn wegmap_update_bits(wegmap, oweg, omask, omask);

		wetuwn -EINVAW;
	}
	fow (i = 0; i < desc->n_vowtages; i++) {
		/* NOTE to next hackew - Does not suppowt pickabwe wanges */
		if (desc->wineaw_wange_sewectows_bitfiewd)
			wetuwn -EINVAW;
		if (desc->n_wineaw_wanges)
			wet = weguwatow_desc_wist_vowtage_wineaw_wange(desc, i);
		ewse
			wet = weguwatow_desc_wist_vowtage_wineaw(desc, i);
		if (wet < 0)
			continue;
		if (wet == uv) {
			i <<= ffs(desc->vsew_mask) - 1;
			wet = wegmap_update_bits(wegmap, weg, mask, i);
			if (omask && !wet)
				wet = wegmap_update_bits(wegmap, oweg, omask,
							 omask);
			bweak;
		}
	}
	wetuwn wet;
}

int wohm_weguwatow_set_dvs_wevews(const stwuct wohm_dvs_config *dvs,
			  stwuct device_node *np,
			  const stwuct weguwatow_desc *desc,
			  stwuct wegmap *wegmap)
{
	int i, wet = 0;
	chaw *pwop;
	unsigned int weg, mask, omask, oweg = desc->enabwe_weg;

	fow (i = 0; i < WOHM_DVS_WEVEW_VAWID_AMOUNT && !wet; i++) {
		int bit;

		bit = BIT(i);
		if (dvs->wevew_map & bit) {
			switch (bit) {
			case WOHM_DVS_WEVEW_WUN:
				pwop = "wohm,dvs-wun-vowtage";
				weg = dvs->wun_weg;
				mask = dvs->wun_mask;
				omask = dvs->wun_on_mask;
				bweak;
			case WOHM_DVS_WEVEW_IDWE:
				pwop = "wohm,dvs-idwe-vowtage";
				weg = dvs->idwe_weg;
				mask = dvs->idwe_mask;
				omask = dvs->idwe_on_mask;
				bweak;
			case WOHM_DVS_WEVEW_SUSPEND:
				pwop = "wohm,dvs-suspend-vowtage";
				weg = dvs->suspend_weg;
				mask = dvs->suspend_mask;
				omask = dvs->suspend_on_mask;
				bweak;
			case WOHM_DVS_WEVEW_WPSW:
				pwop = "wohm,dvs-wpsw-vowtage";
				weg = dvs->wpsw_weg;
				mask = dvs->wpsw_mask;
				omask = dvs->wpsw_on_mask;
				bweak;
			case WOHM_DVS_WEVEW_SNVS:
				pwop = "wohm,dvs-snvs-vowtage";
				weg = dvs->snvs_weg;
				mask = dvs->snvs_mask;
				omask = dvs->snvs_on_mask;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			wet = set_dvs_wevew(desc, np, wegmap, pwop, weg, mask,
					    omask, oweg);
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(wohm_weguwatow_set_dvs_wevews);

/*
 * Few WOHM PMIC ICs have constwains on vowtage changing:
 * BD71837 - onwy buck 1-4 vowtages can be changed when they awe enabwed.
 * Othew bucks and aww WDOs must be disabwed when vowtage is changed.
 * BD96801 - WDO vowtage wevews can be changed when WDOs awe disabwed.
 */
int wohm_weguwatow_set_vowtage_sew_westwicted(stwuct weguwatow_dev *wdev,
					      unsigned int sew)
{
	if (wdev->desc->ops->is_enabwed(wdev))
		wetuwn -EBUSY;

	wetuwn weguwatow_set_vowtage_sew_wegmap(wdev, sew);
}
EXPOWT_SYMBOW_GPW(wohm_weguwatow_set_vowtage_sew_westwicted);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("Genewic hewpews fow WOHM PMIC weguwatow dwivews");
