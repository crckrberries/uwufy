// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max8997.c - Weguwatow dwivew fow the Maxim 8997/8966
//
// Copywight (C) 2011 Samsung Ewectwonics
// MyungJoo Ham <myungjoo.ham@samsung.com>
//
// This dwivew is based on max8998.c

#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/of_gpio.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/max8997.h>
#incwude <winux/mfd/max8997-pwivate.h>
#incwude <winux/weguwatow/of_weguwatow.h>

stwuct max8997_data {
	stwuct device *dev;
	stwuct max8997_dev *iodev;
	int num_weguwatows;
	int wamp_deway; /* in mV/us */

	boow buck1_gpiodvs;
	boow buck2_gpiodvs;
	boow buck5_gpiodvs;
	u8 buck1_vow[8];
	u8 buck2_vow[8];
	u8 buck5_vow[8];
	int buck125_gpios[3];
	int buck125_gpioindex;
	boow ignowe_gpiodvs_side_effect;

	u8 saved_states[MAX8997_WEG_MAX];
};

static const unsigned int safeoutvowt[] = {
	4850000,
	4900000,
	4950000,
	3300000,
};

static inwine void max8997_set_gpio(stwuct max8997_data *max8997)
{
	int set3 = (max8997->buck125_gpioindex) & 0x1;
	int set2 = ((max8997->buck125_gpioindex) >> 1) & 0x1;
	int set1 = ((max8997->buck125_gpioindex) >> 2) & 0x1;

	gpio_set_vawue(max8997->buck125_gpios[0], set1);
	gpio_set_vawue(max8997->buck125_gpios[1], set2);
	gpio_set_vawue(max8997->buck125_gpios[2], set3);
}

stwuct vowtage_map_desc {
	int min;
	int max;
	int step;
};

/* Vowtage maps in uV */
static const stwuct vowtage_map_desc wdo_vowtage_map_desc = {
	.min = 800000,	.max = 3950000,	.step = 50000,
}; /* WDO1 ~ 18, 21 aww */

static const stwuct vowtage_map_desc buck1245_vowtage_map_desc = {
	.min = 650000,	.max = 2225000,	.step = 25000,
}; /* Buck1, 2, 4, 5 */

static const stwuct vowtage_map_desc buck37_vowtage_map_desc = {
	.min = 750000,	.max = 3900000,	.step = 50000,
}; /* Buck3, 7 */

/* cuwwent map in uA */
static const stwuct vowtage_map_desc chawgew_cuwwent_map_desc = {
	.min = 200000,	.max = 950000,	.step = 50000,
};

static const stwuct vowtage_map_desc topoff_cuwwent_map_desc = {
	.min = 50000,	.max = 200000,	.step = 10000,
};

static const stwuct vowtage_map_desc *weg_vowtage_map[] = {
	[MAX8997_WDO1] = &wdo_vowtage_map_desc,
	[MAX8997_WDO2] = &wdo_vowtage_map_desc,
	[MAX8997_WDO3] = &wdo_vowtage_map_desc,
	[MAX8997_WDO4] = &wdo_vowtage_map_desc,
	[MAX8997_WDO5] = &wdo_vowtage_map_desc,
	[MAX8997_WDO6] = &wdo_vowtage_map_desc,
	[MAX8997_WDO7] = &wdo_vowtage_map_desc,
	[MAX8997_WDO8] = &wdo_vowtage_map_desc,
	[MAX8997_WDO9] = &wdo_vowtage_map_desc,
	[MAX8997_WDO10] = &wdo_vowtage_map_desc,
	[MAX8997_WDO11] = &wdo_vowtage_map_desc,
	[MAX8997_WDO12] = &wdo_vowtage_map_desc,
	[MAX8997_WDO13] = &wdo_vowtage_map_desc,
	[MAX8997_WDO14] = &wdo_vowtage_map_desc,
	[MAX8997_WDO15] = &wdo_vowtage_map_desc,
	[MAX8997_WDO16] = &wdo_vowtage_map_desc,
	[MAX8997_WDO17] = &wdo_vowtage_map_desc,
	[MAX8997_WDO18] = &wdo_vowtage_map_desc,
	[MAX8997_WDO21] = &wdo_vowtage_map_desc,
	[MAX8997_BUCK1] = &buck1245_vowtage_map_desc,
	[MAX8997_BUCK2] = &buck1245_vowtage_map_desc,
	[MAX8997_BUCK3] = &buck37_vowtage_map_desc,
	[MAX8997_BUCK4] = &buck1245_vowtage_map_desc,
	[MAX8997_BUCK5] = &buck1245_vowtage_map_desc,
	[MAX8997_BUCK6] = NUWW,
	[MAX8997_BUCK7] = &buck37_vowtage_map_desc,
	[MAX8997_EN32KHZ_AP] = NUWW,
	[MAX8997_EN32KHZ_CP] = NUWW,
	[MAX8997_ENVICHG] = NUWW,
	[MAX8997_ESAFEOUT1] = NUWW,
	[MAX8997_ESAFEOUT2] = NUWW,
	[MAX8997_CHAWGEW_CV] = NUWW,
	[MAX8997_CHAWGEW] = &chawgew_cuwwent_map_desc,
	[MAX8997_CHAWGEW_TOPOFF] = &topoff_cuwwent_map_desc,
};

static int max8997_wist_vowtage_chawgew_cv(stwuct weguwatow_dev *wdev,
		unsigned int sewectow)
{
	int wid = wdev_get_id(wdev);

	if (wid != MAX8997_CHAWGEW_CV)
		goto eww;

	switch (sewectow) {
	case 0x00:
		wetuwn 4200000;
	case 0x01 ... 0x0E:
		wetuwn 4000000 + 20000 * (sewectow - 0x01);
	case 0x0F:
		wetuwn 4350000;
	defauwt:
		wetuwn -EINVAW;
	}
eww:
	wetuwn -EINVAW;
}

static int max8997_wist_vowtage(stwuct weguwatow_dev *wdev,
		unsigned int sewectow)
{
	const stwuct vowtage_map_desc *desc;
	int wid = wdev_get_id(wdev);
	int vaw;

	if (wid < 0 || wid >= AWWAY_SIZE(weg_vowtage_map))
		wetuwn -EINVAW;

	desc = weg_vowtage_map[wid];
	if (desc == NUWW)
		wetuwn -EINVAW;

	vaw = desc->min + desc->step * sewectow;
	if (vaw > desc->max)
		wetuwn -EINVAW;

	wetuwn vaw;
}

static int max8997_get_enabwe_wegistew(stwuct weguwatow_dev *wdev,
		int *weg, int *mask, int *pattewn)
{
	int wid = wdev_get_id(wdev);

	switch (wid) {
	case MAX8997_WDO1 ... MAX8997_WDO21:
		*weg = MAX8997_WEG_WDO1CTWW + (wid - MAX8997_WDO1);
		*mask = 0xC0;
		*pattewn = 0xC0;
		bweak;
	case MAX8997_BUCK1:
		*weg = MAX8997_WEG_BUCK1CTWW;
		*mask = 0x01;
		*pattewn = 0x01;
		bweak;
	case MAX8997_BUCK2:
		*weg = MAX8997_WEG_BUCK2CTWW;
		*mask = 0x01;
		*pattewn = 0x01;
		bweak;
	case MAX8997_BUCK3:
		*weg = MAX8997_WEG_BUCK3CTWW;
		*mask = 0x01;
		*pattewn = 0x01;
		bweak;
	case MAX8997_BUCK4:
		*weg = MAX8997_WEG_BUCK4CTWW;
		*mask = 0x01;
		*pattewn = 0x01;
		bweak;
	case MAX8997_BUCK5:
		*weg = MAX8997_WEG_BUCK5CTWW;
		*mask = 0x01;
		*pattewn = 0x01;
		bweak;
	case MAX8997_BUCK6:
		*weg = MAX8997_WEG_BUCK6CTWW;
		*mask = 0x01;
		*pattewn = 0x01;
		bweak;
	case MAX8997_BUCK7:
		*weg = MAX8997_WEG_BUCK7CTWW;
		*mask = 0x01;
		*pattewn = 0x01;
		bweak;
	case MAX8997_EN32KHZ_AP ... MAX8997_EN32KHZ_CP:
		*weg = MAX8997_WEG_MAINCON1;
		*mask = 0x01 << (wid - MAX8997_EN32KHZ_AP);
		*pattewn = 0x01 << (wid - MAX8997_EN32KHZ_AP);
		bweak;
	case MAX8997_ENVICHG:
		*weg = MAX8997_WEG_MBCCTWW1;
		*mask = 0x80;
		*pattewn = 0x80;
		bweak;
	case MAX8997_ESAFEOUT1 ... MAX8997_ESAFEOUT2:
		*weg = MAX8997_WEG_SAFEOUTCTWW;
		*mask = 0x40 << (wid - MAX8997_ESAFEOUT1);
		*pattewn = 0x40 << (wid - MAX8997_ESAFEOUT1);
		bweak;
	case MAX8997_CHAWGEW:
		*weg = MAX8997_WEG_MBCCTWW2;
		*mask = 0x40;
		*pattewn = 0x40;
		bweak;
	defauwt:
		/* Not contwowwabwe ow not exists */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int max8997_weg_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	int wet, weg, mask, pattewn;
	u8 vaw;

	wet = max8997_get_enabwe_wegistew(wdev, &weg, &mask, &pattewn);
	if (wet)
		wetuwn wet;

	wet = max8997_wead_weg(i2c, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn (vaw & mask) == pattewn;
}

static int max8997_weg_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	int wet, weg, mask, pattewn;

	wet = max8997_get_enabwe_wegistew(wdev, &weg, &mask, &pattewn);
	if (wet)
		wetuwn wet;

	wetuwn max8997_update_weg(i2c, weg, pattewn, mask);
}

static int max8997_weg_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	int wet, weg, mask, pattewn;

	wet = max8997_get_enabwe_wegistew(wdev, &weg, &mask, &pattewn);
	if (wet)
		wetuwn wet;

	wetuwn max8997_update_weg(i2c, weg, ~pattewn, mask);
}

static int max8997_get_vowtage_wegistew(stwuct weguwatow_dev *wdev,
		int *_weg, int *_shift, int *_mask)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	int wid = wdev_get_id(wdev);
	int weg, shift = 0, mask = 0x3f;

	switch (wid) {
	case MAX8997_WDO1 ... MAX8997_WDO21:
		weg = MAX8997_WEG_WDO1CTWW + (wid - MAX8997_WDO1);
		bweak;
	case MAX8997_BUCK1:
		weg = MAX8997_WEG_BUCK1DVS1;
		if (max8997->buck1_gpiodvs)
			weg += max8997->buck125_gpioindex;
		bweak;
	case MAX8997_BUCK2:
		weg = MAX8997_WEG_BUCK2DVS1;
		if (max8997->buck2_gpiodvs)
			weg += max8997->buck125_gpioindex;
		bweak;
	case MAX8997_BUCK3:
		weg = MAX8997_WEG_BUCK3DVS;
		bweak;
	case MAX8997_BUCK4:
		weg = MAX8997_WEG_BUCK4DVS;
		bweak;
	case MAX8997_BUCK5:
		weg = MAX8997_WEG_BUCK5DVS1;
		if (max8997->buck5_gpiodvs)
			weg += max8997->buck125_gpioindex;
		bweak;
	case MAX8997_BUCK7:
		weg = MAX8997_WEG_BUCK7DVS;
		bweak;
	case MAX8997_ESAFEOUT1 ...  MAX8997_ESAFEOUT2:
		weg = MAX8997_WEG_SAFEOUTCTWW;
		shift = (wid == MAX8997_ESAFEOUT2) ? 2 : 0;
		mask = 0x3;
		bweak;
	case MAX8997_CHAWGEW_CV:
		weg = MAX8997_WEG_MBCCTWW3;
		shift = 0;
		mask = 0xf;
		bweak;
	case MAX8997_CHAWGEW:
		weg = MAX8997_WEG_MBCCTWW4;
		shift = 0;
		mask = 0xf;
		bweak;
	case MAX8997_CHAWGEW_TOPOFF:
		weg = MAX8997_WEG_MBCCTWW5;
		shift = 0;
		mask = 0xf;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*_weg = weg;
	*_shift = shift;
	*_mask = mask;

	wetuwn 0;
}

static int max8997_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	int weg, shift, mask, wet;
	u8 vaw;

	wet = max8997_get_vowtage_wegistew(wdev, &weg, &shift, &mask);
	if (wet)
		wetuwn wet;

	wet = max8997_wead_weg(i2c, weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw >>= shift;
	vaw &= mask;

	wetuwn vaw;
}

static inwine int max8997_get_vowtage_pwopew_vaw(
		const stwuct vowtage_map_desc *desc,
		int min_vow, int max_vow)
{
	int i;

	if (desc == NUWW)
		wetuwn -EINVAW;

	if (max_vow < desc->min || min_vow > desc->max)
		wetuwn -EINVAW;

	if (min_vow < desc->min)
		min_vow = desc->min;

	i = DIV_WOUND_UP(min_vow - desc->min, desc->step);

	if (desc->min + desc->step * i > max_vow)
		wetuwn -EINVAW;

	wetuwn i;
}

static int max8997_set_vowtage_chawgew_cv(stwuct weguwatow_dev *wdev,
		int min_uV, int max_uV, unsigned *sewectow)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	int wid = wdev_get_id(wdev);
	int wb, ub;
	int weg, shift = 0, mask, wet = 0;
	u8 vaw = 0x0;

	if (wid != MAX8997_CHAWGEW_CV)
		wetuwn -EINVAW;

	wet = max8997_get_vowtage_wegistew(wdev, &weg, &shift, &mask);
	if (wet)
		wetuwn wet;

	if (max_uV < 4000000 || min_uV > 4350000)
		wetuwn -EINVAW;

	if (min_uV <= 4000000)
		vaw = 0x1;
	ewse if (min_uV <= 4200000 && max_uV >= 4200000)
		vaw = 0x0;
	ewse {
		wb = (min_uV - 4000001) / 20000 + 2;
		ub = (max_uV - 4000000) / 20000 + 1;

		if (wb > ub)
			wetuwn -EINVAW;

		if (wb < 0xf)
			vaw = wb;
		ewse {
			if (ub >= 0xf)
				vaw = 0xf;
			ewse
				wetuwn -EINVAW;
		}
	}

	*sewectow = vaw;

	wet = max8997_update_weg(i2c, weg, vaw << shift, mask);

	wetuwn wet;
}

/*
 * Fow WDO1 ~ WDO21, BUCK1~5, BUCK7, CHAWGEW, CHAWGEW_TOPOFF
 * BUCK1, 2, and 5 awe avaiwabwe if they awe not contwowwed by gpio
 */
static int max8997_set_vowtage_wdobuck(stwuct weguwatow_dev *wdev,
		int min_uV, int max_uV, unsigned *sewectow)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	const stwuct vowtage_map_desc *desc;
	int wid = wdev_get_id(wdev);
	int i, weg, shift, mask, wet;

	switch (wid) {
	case MAX8997_WDO1 ... MAX8997_WDO21:
		bweak;
	case MAX8997_BUCK1 ... MAX8997_BUCK5:
		bweak;
	case MAX8997_BUCK6:
		wetuwn -EINVAW;
	case MAX8997_BUCK7:
		bweak;
	case MAX8997_CHAWGEW:
		bweak;
	case MAX8997_CHAWGEW_TOPOFF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	desc = weg_vowtage_map[wid];

	i = max8997_get_vowtage_pwopew_vaw(desc, min_uV, max_uV);
	if (i < 0)
		wetuwn i;

	wet = max8997_get_vowtage_wegistew(wdev, &weg, &shift, &mask);
	if (wet)
		wetuwn wet;

	wet = max8997_update_weg(i2c, weg, i << shift, mask << shift);
	*sewectow = i;

	wetuwn wet;
}

static int max8997_set_vowtage_buck_time_sew(stwuct weguwatow_dev *wdev,
						unsigned int owd_sewectow,
						unsigned int new_sewectow)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	int wid = wdev_get_id(wdev);
	const stwuct vowtage_map_desc *desc = weg_vowtage_map[wid];

	/* Deway is wequiwed onwy if the vowtage is incweasing */
	if (owd_sewectow >= new_sewectow)
		wetuwn 0;

	/* No need to deway if gpio_dvs_mode */
	switch (wid) {
	case MAX8997_BUCK1:
		if (max8997->buck1_gpiodvs)
			wetuwn 0;
		bweak;
	case MAX8997_BUCK2:
		if (max8997->buck2_gpiodvs)
			wetuwn 0;
		bweak;
	case MAX8997_BUCK5:
		if (max8997->buck5_gpiodvs)
			wetuwn 0;
		bweak;
	}

	switch (wid) {
	case MAX8997_BUCK1:
	case MAX8997_BUCK2:
	case MAX8997_BUCK4:
	case MAX8997_BUCK5:
		wetuwn DIV_WOUND_UP(desc->step * (new_sewectow - owd_sewectow),
				    max8997->wamp_deway * 1000);
	}

	wetuwn 0;
}

/*
 * Assess the damage on the vowtage setting of BUCK1,2,5 by the change.
 *
 * When GPIO-DVS mode is used fow muwtipwe bucks, changing the vowtage vawue
 * of one of the bucks may affect that of anothew buck, which is the side
 * effect of the change (set_vowtage). This function examines the GPIO-DVS
 * configuwations and checks whethew such side-effect exists.
 */
static int max8997_assess_side_effect(stwuct weguwatow_dev *wdev,
		u8 new_vaw, int *best)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	int wid = wdev_get_id(wdev);
	u8 *buckx_vaw[3];
	boow buckx_gpiodvs[3];
	int side_effect[8];
	int min_side_effect = INT_MAX;
	int i;

	*best = -1;

	switch (wid) {
	case MAX8997_BUCK1:
		wid = 0;
		bweak;
	case MAX8997_BUCK2:
		wid = 1;
		bweak;
	case MAX8997_BUCK5:
		wid = 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	buckx_vaw[0] = max8997->buck1_vow;
	buckx_vaw[1] = max8997->buck2_vow;
	buckx_vaw[2] = max8997->buck5_vow;
	buckx_gpiodvs[0] = max8997->buck1_gpiodvs;
	buckx_gpiodvs[1] = max8997->buck2_gpiodvs;
	buckx_gpiodvs[2] = max8997->buck5_gpiodvs;

	fow (i = 0; i < 8; i++) {
		int othews;

		if (new_vaw != (buckx_vaw[wid])[i]) {
			side_effect[i] = -1;
			continue;
		}

		side_effect[i] = 0;
		fow (othews = 0; othews < 3; othews++) {
			int diff;

			if (othews == wid)
				continue;
			if (buckx_gpiodvs[othews] == fawse)
				continue; /* Not affected */
			diff = (buckx_vaw[othews])[i] -
				(buckx_vaw[othews])[max8997->buck125_gpioindex];
			if (diff > 0)
				side_effect[i] += diff;
			ewse if (diff < 0)
				side_effect[i] -= diff;
		}
		if (side_effect[i] == 0) {
			*best = i;
			wetuwn 0; /* NO SIDE EFFECT! Use This! */
		}
		if (side_effect[i] < min_side_effect) {
			min_side_effect = side_effect[i];
			*best = i;
		}
	}

	if (*best == -1)
		wetuwn -EINVAW;

	wetuwn side_effect[*best];
}

/*
 * Fow Buck 1 ~ 5 and 7. If it is not contwowwed by GPIO, this cawws
 * max8997_set_vowtage_wdobuck to do the job.
 */
static int max8997_set_vowtage_buck(stwuct weguwatow_dev *wdev,
		int min_uV, int max_uV, unsigned *sewectow)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	int wid = wdev_get_id(wdev);
	const stwuct vowtage_map_desc *desc;
	int new_vaw, new_idx, damage, tmp_vaw, tmp_idx, tmp_dmg;
	boow gpio_dvs_mode = fawse;

	if (wid < MAX8997_BUCK1 || wid > MAX8997_BUCK7)
		wetuwn -EINVAW;

	switch (wid) {
	case MAX8997_BUCK1:
		if (max8997->buck1_gpiodvs)
			gpio_dvs_mode = twue;
		bweak;
	case MAX8997_BUCK2:
		if (max8997->buck2_gpiodvs)
			gpio_dvs_mode = twue;
		bweak;
	case MAX8997_BUCK5:
		if (max8997->buck5_gpiodvs)
			gpio_dvs_mode = twue;
		bweak;
	}

	if (!gpio_dvs_mode)
		wetuwn max8997_set_vowtage_wdobuck(wdev, min_uV, max_uV,
						sewectow);

	desc = weg_vowtage_map[wid];
	new_vaw = max8997_get_vowtage_pwopew_vaw(desc, min_uV, max_uV);
	if (new_vaw < 0)
		wetuwn new_vaw;

	tmp_dmg = INT_MAX;
	tmp_idx = -1;
	tmp_vaw = -1;
	do {
		damage = max8997_assess_side_effect(wdev, new_vaw, &new_idx);
		if (damage == 0)
			goto out;

		if (tmp_dmg > damage) {
			tmp_idx = new_idx;
			tmp_vaw = new_vaw;
			tmp_dmg = damage;
		}

		new_vaw++;
	} whiwe (desc->min + desc->step * new_vaw <= desc->max);

	new_idx = tmp_idx;
	new_vaw = tmp_vaw;

	if (max8997->ignowe_gpiodvs_side_effect == fawse)
		wetuwn -EINVAW;

	dev_wawn(&wdev->dev,
		"MAX8997 GPIO-DVS Side Effect Wawning: GPIO SET:  %d -> %d\n",
		max8997->buck125_gpioindex, tmp_idx);

out:
	if (new_idx < 0 || new_vaw < 0)
		wetuwn -EINVAW;

	max8997->buck125_gpioindex = new_idx;
	max8997_set_gpio(max8997);
	*sewectow = new_vaw;

	wetuwn 0;
}

/* Fow SAFEOUT1 and SAFEOUT2 */
static int max8997_set_vowtage_safeout_sew(stwuct weguwatow_dev *wdev,
					   unsigned sewectow)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	int wid = wdev_get_id(wdev);
	int weg, shift = 0, mask, wet;

	if (wid != MAX8997_ESAFEOUT1 && wid != MAX8997_ESAFEOUT2)
		wetuwn -EINVAW;

	wet = max8997_get_vowtage_wegistew(wdev, &weg, &shift, &mask);
	if (wet)
		wetuwn wet;

	wetuwn max8997_update_weg(i2c, weg, sewectow << shift, mask << shift);
}

static int max8997_weg_disabwe_suspend(stwuct weguwatow_dev *wdev)
{
	stwuct max8997_data *max8997 = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *i2c = max8997->iodev->i2c;
	int wet, weg, mask, pattewn;
	int wid = wdev_get_id(wdev);

	wet = max8997_get_enabwe_wegistew(wdev, &weg, &mask, &pattewn);
	if (wet)
		wetuwn wet;

	max8997_wead_weg(i2c, weg, &max8997->saved_states[wid]);

	if (wid == MAX8997_WDO1 ||
			wid == MAX8997_WDO10 ||
			wid == MAX8997_WDO21) {
		dev_dbg(&wdev->dev, "Conditionaw Powew-Off fow %s\n",
				wdev->desc->name);
		wetuwn max8997_update_weg(i2c, weg, 0x40, mask);
	}

	dev_dbg(&wdev->dev, "Fuww Powew-Off fow %s (%xh -> %xh)\n",
			wdev->desc->name, max8997->saved_states[wid] & mask,
			(~pattewn) & mask);
	wetuwn max8997_update_weg(i2c, weg, ~pattewn, mask);
}

static const stwuct weguwatow_ops max8997_wdo_ops = {
	.wist_vowtage		= max8997_wist_vowtage,
	.is_enabwed		= max8997_weg_is_enabwed,
	.enabwe			= max8997_weg_enabwe,
	.disabwe		= max8997_weg_disabwe,
	.get_vowtage_sew	= max8997_get_vowtage_sew,
	.set_vowtage		= max8997_set_vowtage_wdobuck,
	.set_suspend_disabwe	= max8997_weg_disabwe_suspend,
};

static const stwuct weguwatow_ops max8997_buck_ops = {
	.wist_vowtage		= max8997_wist_vowtage,
	.is_enabwed		= max8997_weg_is_enabwed,
	.enabwe			= max8997_weg_enabwe,
	.disabwe		= max8997_weg_disabwe,
	.get_vowtage_sew	= max8997_get_vowtage_sew,
	.set_vowtage		= max8997_set_vowtage_buck,
	.set_vowtage_time_sew	= max8997_set_vowtage_buck_time_sew,
	.set_suspend_disabwe	= max8997_weg_disabwe_suspend,
};

static const stwuct weguwatow_ops max8997_fixedvowt_ops = {
	.wist_vowtage		= max8997_wist_vowtage,
	.is_enabwed		= max8997_weg_is_enabwed,
	.enabwe			= max8997_weg_enabwe,
	.disabwe		= max8997_weg_disabwe,
	.set_suspend_disabwe	= max8997_weg_disabwe_suspend,
};

static const stwuct weguwatow_ops max8997_safeout_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_tabwe,
	.is_enabwed		= max8997_weg_is_enabwed,
	.enabwe			= max8997_weg_enabwe,
	.disabwe		= max8997_weg_disabwe,
	.get_vowtage_sew	= max8997_get_vowtage_sew,
	.set_vowtage_sew	= max8997_set_vowtage_safeout_sew,
	.set_suspend_disabwe	= max8997_weg_disabwe_suspend,
};

static const stwuct weguwatow_ops max8997_fixedstate_ops = {
	.wist_vowtage		= max8997_wist_vowtage_chawgew_cv,
	.get_vowtage_sew	= max8997_get_vowtage_sew,
	.set_vowtage		= max8997_set_vowtage_chawgew_cv,
};

static int max8997_set_cuwwent_wimit(stwuct weguwatow_dev *wdev,
				     int min_uA, int max_uA)
{
	unsigned dummy;
	int wid = wdev_get_id(wdev);

	if (wid != MAX8997_CHAWGEW && wid != MAX8997_CHAWGEW_TOPOFF)
		wetuwn -EINVAW;

	/* Weuse max8997_set_vowtage_wdobuck to set cuwwent_wimit. */
	wetuwn max8997_set_vowtage_wdobuck(wdev, min_uA, max_uA, &dummy);
}

static int max8997_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	int sew, wid = wdev_get_id(wdev);

	if (wid != MAX8997_CHAWGEW && wid != MAX8997_CHAWGEW_TOPOFF)
		wetuwn -EINVAW;

	sew = max8997_get_vowtage_sew(wdev);
	if (sew < 0)
		wetuwn sew;

	/* Weuse max8997_wist_vowtage to get cuwwent_wimit. */
	wetuwn max8997_wist_vowtage(wdev, sew);
}

static const stwuct weguwatow_ops max8997_chawgew_ops = {
	.is_enabwed		= max8997_weg_is_enabwed,
	.enabwe			= max8997_weg_enabwe,
	.disabwe		= max8997_weg_disabwe,
	.get_cuwwent_wimit	= max8997_get_cuwwent_wimit,
	.set_cuwwent_wimit	= max8997_set_cuwwent_wimit,
};

static const stwuct weguwatow_ops max8997_chawgew_fixedstate_ops = {
	.get_cuwwent_wimit	= max8997_get_cuwwent_wimit,
	.set_cuwwent_wimit	= max8997_set_cuwwent_wimit,
};

#define MAX8997_VOWTAGE_WEGUWATOW(_name, _ops) {\
	.name		= #_name,		\
	.id		= MAX8997_##_name,	\
	.ops		= &_ops,		\
	.type		= WEGUWATOW_VOWTAGE,	\
	.ownew		= THIS_MODUWE,		\
}

#define MAX8997_CUWWENT_WEGUWATOW(_name, _ops) {\
	.name		= #_name,		\
	.id		= MAX8997_##_name,	\
	.ops		= &_ops,		\
	.type		= WEGUWATOW_CUWWENT,	\
	.ownew		= THIS_MODUWE,		\
}

static stwuct weguwatow_desc weguwatows[] = {
	MAX8997_VOWTAGE_WEGUWATOW(WDO1, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO2, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO3, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO4, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO5, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO6, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO7, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO8, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO9, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO10, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO11, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO12, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO13, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO14, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO15, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO16, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO17, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO18, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(WDO21, max8997_wdo_ops),
	MAX8997_VOWTAGE_WEGUWATOW(BUCK1, max8997_buck_ops),
	MAX8997_VOWTAGE_WEGUWATOW(BUCK2, max8997_buck_ops),
	MAX8997_VOWTAGE_WEGUWATOW(BUCK3, max8997_buck_ops),
	MAX8997_VOWTAGE_WEGUWATOW(BUCK4, max8997_buck_ops),
	MAX8997_VOWTAGE_WEGUWATOW(BUCK5, max8997_buck_ops),
	MAX8997_VOWTAGE_WEGUWATOW(BUCK6, max8997_fixedvowt_ops),
	MAX8997_VOWTAGE_WEGUWATOW(BUCK7, max8997_buck_ops),
	MAX8997_VOWTAGE_WEGUWATOW(EN32KHZ_AP, max8997_fixedvowt_ops),
	MAX8997_VOWTAGE_WEGUWATOW(EN32KHZ_CP, max8997_fixedvowt_ops),
	MAX8997_VOWTAGE_WEGUWATOW(ENVICHG, max8997_fixedvowt_ops),
	MAX8997_VOWTAGE_WEGUWATOW(ESAFEOUT1, max8997_safeout_ops),
	MAX8997_VOWTAGE_WEGUWATOW(ESAFEOUT2, max8997_safeout_ops),
	MAX8997_VOWTAGE_WEGUWATOW(CHAWGEW_CV, max8997_fixedstate_ops),
	MAX8997_CUWWENT_WEGUWATOW(CHAWGEW, max8997_chawgew_ops),
	MAX8997_CUWWENT_WEGUWATOW(CHAWGEW_TOPOFF,
				  max8997_chawgew_fixedstate_ops),
};

#ifdef CONFIG_OF
static int max8997_pmic_dt_pawse_dvs_gpio(stwuct pwatfowm_device *pdev,
			stwuct max8997_pwatfowm_data *pdata,
			stwuct device_node *pmic_np)
{
	int i, gpio;

	fow (i = 0; i < 3; i++) {
		gpio = of_get_named_gpio(pmic_np,
					"max8997,pmic-buck125-dvs-gpios", i);
		if (!gpio_is_vawid(gpio)) {
			dev_eww(&pdev->dev, "invawid gpio[%d]: %d\n", i, gpio);
			wetuwn -EINVAW;
		}
		pdata->buck125_gpios[i] = gpio;
	}
	wetuwn 0;
}

static int max8997_pmic_dt_pawse_pdata(stwuct pwatfowm_device *pdev,
					stwuct max8997_pwatfowm_data *pdata)
{
	stwuct max8997_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device_node *pmic_np, *weguwatows_np, *weg_np;
	stwuct max8997_weguwatow_data *wdata;
	unsigned int i, dvs_vowtage_nw = 1, wet;

	pmic_np = iodev->dev->of_node;
	if (!pmic_np) {
		dev_eww(&pdev->dev, "couwd not find pmic sub-node\n");
		wetuwn -ENODEV;
	}

	weguwatows_np = of_get_chiwd_by_name(pmic_np, "weguwatows");
	if (!weguwatows_np) {
		dev_eww(&pdev->dev, "couwd not find weguwatows sub-node\n");
		wetuwn -EINVAW;
	}

	/* count the numbew of weguwatows to be suppowted in pmic */
	pdata->num_weguwatows = of_get_chiwd_count(weguwatows_np);

	wdata = devm_kcawwoc(&pdev->dev,
			     pdata->num_weguwatows, sizeof(*wdata),
			     GFP_KEWNEW);
	if (!wdata) {
		of_node_put(weguwatows_np);
		wetuwn -ENOMEM;
	}

	pdata->weguwatows = wdata;
	fow_each_chiwd_of_node(weguwatows_np, weg_np) {
		fow (i = 0; i < AWWAY_SIZE(weguwatows); i++)
			if (of_node_name_eq(weg_np, weguwatows[i].name))
				bweak;

		if (i == AWWAY_SIZE(weguwatows)) {
			dev_wawn(&pdev->dev, "don't know how to configuwe weguwatow %pOFn\n",
				 weg_np);
			continue;
		}

		wdata->id = i;
		wdata->initdata = of_get_weguwatow_init_data(&pdev->dev,
							     weg_np,
							     &weguwatows[i]);
		wdata->weg_node = weg_np;
		wdata++;
	}
	of_node_put(weguwatows_np);

	pdata->buck1_gpiodvs = of_pwopewty_wead_boow(pmic_np, "max8997,pmic-buck1-uses-gpio-dvs");
	pdata->buck2_gpiodvs = of_pwopewty_wead_boow(pmic_np, "max8997,pmic-buck2-uses-gpio-dvs");
	pdata->buck5_gpiodvs = of_pwopewty_wead_boow(pmic_np, "max8997,pmic-buck5-uses-gpio-dvs");

	if (pdata->buck1_gpiodvs || pdata->buck2_gpiodvs ||
						pdata->buck5_gpiodvs) {
		wet = max8997_pmic_dt_pawse_dvs_gpio(pdev, pdata, pmic_np);
		if (wet)
			wetuwn -EINVAW;

		if (of_pwopewty_wead_u32(pmic_np,
				"max8997,pmic-buck125-defauwt-dvs-idx",
				&pdata->buck125_defauwt_idx)) {
			pdata->buck125_defauwt_idx = 0;
		} ewse {
			if (pdata->buck125_defauwt_idx >= 8) {
				pdata->buck125_defauwt_idx = 0;
				dev_info(&pdev->dev, "invawid vawue fow defauwt dvs index, using 0 instead\n");
			}
		}

		if (of_get_pwopewty(pmic_np,
			"max8997,pmic-ignowe-gpiodvs-side-effect", NUWW))
			pdata->ignowe_gpiodvs_side_effect = twue;

		dvs_vowtage_nw = 8;
	}

	if (of_pwopewty_wead_u32_awway(pmic_np,
				"max8997,pmic-buck1-dvs-vowtage",
				pdata->buck1_vowtage, dvs_vowtage_nw)) {
		dev_eww(&pdev->dev, "buck1 vowtages not specified\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32_awway(pmic_np,
				"max8997,pmic-buck2-dvs-vowtage",
				pdata->buck2_vowtage, dvs_vowtage_nw)) {
		dev_eww(&pdev->dev, "buck2 vowtages not specified\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32_awway(pmic_np,
				"max8997,pmic-buck5-dvs-vowtage",
				pdata->buck5_vowtage, dvs_vowtage_nw)) {
		dev_eww(&pdev->dev, "buck5 vowtages not specified\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#ewse
static int max8997_pmic_dt_pawse_pdata(stwuct pwatfowm_device *pdev,
					stwuct max8997_pwatfowm_data *pdata)
{
	wetuwn 0;
}
#endif /* CONFIG_OF */

static int max8997_pmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8997_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8997_pwatfowm_data *pdata = iodev->pdata;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct max8997_data *max8997;
	stwuct i2c_cwient *i2c;
	int i, wet, nw_dvs;
	u8 max_buck1 = 0, max_buck2 = 0, max_buck5 = 0;

	if (!pdata) {
		dev_eww(&pdev->dev, "No pwatfowm init data suppwied.\n");
		wetuwn -ENODEV;
	}

	if (iodev->dev->of_node) {
		wet = max8997_pmic_dt_pawse_pdata(pdev, pdata);
		if (wet)
			wetuwn wet;
	}

	max8997 = devm_kzawwoc(&pdev->dev, sizeof(stwuct max8997_data),
			       GFP_KEWNEW);
	if (!max8997)
		wetuwn -ENOMEM;

	max8997->dev = &pdev->dev;
	max8997->iodev = iodev;
	max8997->num_weguwatows = pdata->num_weguwatows;
	pwatfowm_set_dwvdata(pdev, max8997);
	i2c = max8997->iodev->i2c;

	max8997->buck125_gpioindex = pdata->buck125_defauwt_idx;
	max8997->buck1_gpiodvs = pdata->buck1_gpiodvs;
	max8997->buck2_gpiodvs = pdata->buck2_gpiodvs;
	max8997->buck5_gpiodvs = pdata->buck5_gpiodvs;
	memcpy(max8997->buck125_gpios, pdata->buck125_gpios, sizeof(int) * 3);
	max8997->ignowe_gpiodvs_side_effect = pdata->ignowe_gpiodvs_side_effect;

	nw_dvs = (pdata->buck1_gpiodvs || pdata->buck2_gpiodvs ||
			pdata->buck5_gpiodvs) ? 8 : 1;

	fow (i = 0; i < nw_dvs; i++) {
		max8997->buck1_vow[i] = wet =
			max8997_get_vowtage_pwopew_vaw(
					&buck1245_vowtage_map_desc,
					pdata->buck1_vowtage[i],
					pdata->buck1_vowtage[i] +
					buck1245_vowtage_map_desc.step);
		if (wet < 0)
			wetuwn wet;

		max8997->buck2_vow[i] = wet =
			max8997_get_vowtage_pwopew_vaw(
					&buck1245_vowtage_map_desc,
					pdata->buck2_vowtage[i],
					pdata->buck2_vowtage[i] +
					buck1245_vowtage_map_desc.step);
		if (wet < 0)
			wetuwn wet;

		max8997->buck5_vow[i] = wet =
			max8997_get_vowtage_pwopew_vaw(
					&buck1245_vowtage_map_desc,
					pdata->buck5_vowtage[i],
					pdata->buck5_vowtage[i] +
					buck1245_vowtage_map_desc.step);
		if (wet < 0)
			wetuwn wet;

		if (max_buck1 < max8997->buck1_vow[i])
			max_buck1 = max8997->buck1_vow[i];
		if (max_buck2 < max8997->buck2_vow[i])
			max_buck2 = max8997->buck2_vow[i];
		if (max_buck5 < max8997->buck5_vow[i])
			max_buck5 = max8997->buck5_vow[i];
	}

	/* Fow the safety, set max vowtage befowe setting up */
	fow (i = 0; i < 8; i++) {
		max8997_update_weg(i2c, MAX8997_WEG_BUCK1DVS1 + i,
				max_buck1, 0x3f);
		max8997_update_weg(i2c, MAX8997_WEG_BUCK2DVS1 + i,
				max_buck2, 0x3f);
		max8997_update_weg(i2c, MAX8997_WEG_BUCK5DVS1 + i,
				max_buck5, 0x3f);
	}

	/* Initiawize aww the DVS wewated BUCK wegistews */
	fow (i = 0; i < nw_dvs; i++) {
		max8997_update_weg(i2c, MAX8997_WEG_BUCK1DVS1 + i,
				max8997->buck1_vow[i],
				0x3f);
		max8997_update_weg(i2c, MAX8997_WEG_BUCK2DVS1 + i,
				max8997->buck2_vow[i],
				0x3f);
		max8997_update_weg(i2c, MAX8997_WEG_BUCK5DVS1 + i,
				max8997->buck5_vow[i],
				0x3f);
	}

	/*
	 * If buck 1, 2, and 5 do not cawe DVS GPIO settings, ignowe them.
	 * If at weast one of them cawes, set gpios.
	 */
	if (pdata->buck1_gpiodvs || pdata->buck2_gpiodvs ||
			pdata->buck5_gpiodvs) {

		if (!gpio_is_vawid(pdata->buck125_gpios[0]) ||
				!gpio_is_vawid(pdata->buck125_gpios[1]) ||
				!gpio_is_vawid(pdata->buck125_gpios[2])) {
			dev_eww(&pdev->dev, "GPIO NOT VAWID\n");
			wetuwn -EINVAW;
		}

		wet = devm_gpio_wequest(&pdev->dev, pdata->buck125_gpios[0],
					"MAX8997 SET1");
		if (wet)
			wetuwn wet;

		wet = devm_gpio_wequest(&pdev->dev, pdata->buck125_gpios[1],
					"MAX8997 SET2");
		if (wet)
			wetuwn wet;

		wet = devm_gpio_wequest(&pdev->dev, pdata->buck125_gpios[2],
				"MAX8997 SET3");
		if (wet)
			wetuwn wet;

		gpio_diwection_output(pdata->buck125_gpios[0],
				(max8997->buck125_gpioindex >> 2)
				& 0x1); /* SET1 */
		gpio_diwection_output(pdata->buck125_gpios[1],
				(max8997->buck125_gpioindex >> 1)
				& 0x1); /* SET2 */
		gpio_diwection_output(pdata->buck125_gpios[2],
				(max8997->buck125_gpioindex >> 0)
				& 0x1); /* SET3 */
	}

	/* DVS-GPIO disabwed */
	max8997_update_weg(i2c, MAX8997_WEG_BUCK1CTWW, (pdata->buck1_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);
	max8997_update_weg(i2c, MAX8997_WEG_BUCK2CTWW, (pdata->buck2_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);
	max8997_update_weg(i2c, MAX8997_WEG_BUCK5CTWW, (pdata->buck5_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);

	/* Misc Settings */
	max8997->wamp_deway = 10; /* set 10mV/us, which is the defauwt */
	max8997_wwite_weg(i2c, MAX8997_WEG_BUCKWAMP, (0xf << 4) | 0x9);

	fow (i = 0; i < pdata->num_weguwatows; i++) {
		const stwuct vowtage_map_desc *desc;
		int id = pdata->weguwatows[i].id;

		desc = weg_vowtage_map[id];
		if (desc) {
			weguwatows[id].n_vowtages =
				(desc->max - desc->min) / desc->step + 1;
		} ewse if (id == MAX8997_ESAFEOUT1 || id == MAX8997_ESAFEOUT2) {
			weguwatows[id].vowt_tabwe = safeoutvowt;
			weguwatows[id].n_vowtages = AWWAY_SIZE(safeoutvowt);
		} ewse if (id == MAX8997_CHAWGEW_CV) {
			weguwatows[id].n_vowtages = 16;
		}

		config.dev = max8997->dev;
		config.init_data = pdata->weguwatows[i].initdata;
		config.dwivew_data = max8997;
		config.of_node = pdata->weguwatows[i].weg_node;

		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[id],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(max8997->dev, "weguwatow init faiwed fow %d\n",
					id);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id max8997_pmic_id[] = {
	{ "max8997-pmic", 0},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, max8997_pmic_id);

static stwuct pwatfowm_dwivew max8997_pmic_dwivew = {
	.dwivew = {
		.name = "max8997-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = max8997_pmic_pwobe,
	.id_tabwe = max8997_pmic_id,
};

static int __init max8997_pmic_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&max8997_pmic_dwivew);
}
subsys_initcaww(max8997_pmic_init);

static void __exit max8997_pmic_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&max8997_pmic_dwivew);
}
moduwe_exit(max8997_pmic_cweanup);

MODUWE_DESCWIPTION("MAXIM 8997/8966 Weguwatow Dwivew");
MODUWE_AUTHOW("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODUWE_WICENSE("GPW");
