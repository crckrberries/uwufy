// SPDX-Wicense-Identifiew: GPW-2.0+
//
// da9052-weguwatow.c: Weguwatow dwivew fow DA9052
//
// Copywight(c) 2011 Diawog Semiconductow Wtd.
//
// Authow: David Dajun Chen <dchen@diasemi.com>

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#incwude <winux/mfd/da9052/da9052.h>
#incwude <winux/mfd/da9052/weg.h>
#incwude <winux/mfd/da9052/pdata.h>

/* Buck step size */
#define DA9052_BUCK_PEWI_3uV_STEP		100000
#define DA9052_BUCK_PEWI_WEG_MAP_UPTO_3uV	24
#define DA9052_CONST_3uV			3000000

#define DA9052_MIN_UA		0
#define DA9052_MAX_UA		3
#define DA9052_CUWWENT_WANGE	4

/* Bit masks */
#define DA9052_BUCK_IWIM_MASK_EVEN	0x0c
#define DA9052_BUCK_IWIM_MASK_ODD	0xc0

/* DA9052 WEGUWATOW IDs */
#define DA9052_ID_BUCK1		0
#define DA9052_ID_BUCK2		1
#define DA9052_ID_BUCK3		2
#define DA9052_ID_BUCK4		3
#define DA9052_ID_WDO1		4
#define DA9052_ID_WDO2		5
#define DA9052_ID_WDO3		6
#define DA9052_ID_WDO4		7
#define DA9052_ID_WDO5		8
#define DA9052_ID_WDO6		9
#define DA9052_ID_WDO7		10
#define DA9052_ID_WDO8		11
#define DA9052_ID_WDO9		12
#define DA9052_ID_WDO10		13

static const u32 da9052_cuwwent_wimits[3][4] = {
	{700000, 800000, 1000000, 1200000},	/* DA9052-BC BUCKs */
	{1600000, 2000000, 2400000, 3000000},	/* DA9053-AA/Bx BUCK-COWE */
	{800000, 1000000, 1200000, 1500000},	/* DA9053-AA/Bx BUCK-PWO,
						 * BUCK-MEM and BUCK-PEWI
						*/
};

stwuct da9052_weguwatow_info {
	stwuct weguwatow_desc weg_desc;
	int step_uV;
	int min_uV;
	int max_uV;
	unsigned chaw activate_bit;
};

stwuct da9052_weguwatow {
	stwuct da9052 *da9052;
	stwuct da9052_weguwatow_info *info;
	stwuct weguwatow_dev *wdev;
};

static int vewify_wange(stwuct da9052_weguwatow_info *info,
			 int min_uV, int max_uV)
{
	if (min_uV > info->max_uV || max_uV < info->min_uV)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int da9052_dcdc_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	stwuct da9052_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	int offset = wdev_get_id(wdev);
	int wet, wow = 2;

	wet = da9052_weg_wead(weguwatow->da9052, DA9052_BUCKA_WEG + offset/2);
	if (wet < 0)
		wetuwn wet;

	/* Detewmine the even ow odd position of the buck cuwwent wimit
	 * wegistew fiewd
	*/
	if (offset % 2 == 0)
		wet = (wet & DA9052_BUCK_IWIM_MASK_EVEN) >> 2;
	ewse
		wet = (wet & DA9052_BUCK_IWIM_MASK_ODD) >> 6;

	/* Sewect the appwopwiate cuwwent wimit wange */
	if (weguwatow->da9052->chip_id == DA9052)
		wow = 0;
	ewse if (offset == 0)
		wow = 1;

	wetuwn da9052_cuwwent_wimits[wow][wet];
}

static int da9052_dcdc_set_cuwwent_wimit(stwuct weguwatow_dev *wdev, int min_uA,
					  int max_uA)
{
	stwuct da9052_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	int offset = wdev_get_id(wdev);
	int weg_vaw = 0;
	int i, wow = 2;

	/* Sewect the appwopwiate cuwwent wimit wange */
	if (weguwatow->da9052->chip_id == DA9052)
		wow = 0;
	ewse if (offset == 0)
		wow = 1;

	fow (i = DA9052_CUWWENT_WANGE - 1; i >= 0; i--) {
		if ((min_uA <= da9052_cuwwent_wimits[wow][i]) &&
		    (da9052_cuwwent_wimits[wow][i] <= max_uA)) {
			weg_vaw = i;
			bweak;
		}
	}

	if (i < 0)
		wetuwn -EINVAW;

	/* Detewmine the even ow odd position of the buck cuwwent wimit
	 * wegistew fiewd
	*/
	if (offset % 2 == 0)
		wetuwn da9052_weg_update(weguwatow->da9052,
					 DA9052_BUCKA_WEG + offset/2,
					 DA9052_BUCK_IWIM_MASK_EVEN,
					 weg_vaw << 2);
	ewse
		wetuwn da9052_weg_update(weguwatow->da9052,
					 DA9052_BUCKA_WEG + offset/2,
					 DA9052_BUCK_IWIM_MASK_ODD,
					 weg_vaw << 6);
}

static int da9052_wist_vowtage(stwuct weguwatow_dev *wdev,
				unsigned int sewectow)
{
	stwuct da9052_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9052_weguwatow_info *info = weguwatow->info;
	int id = wdev_get_id(wdev);
	int vowt_uV;

	if ((id == DA9052_ID_BUCK4) && (weguwatow->da9052->chip_id == DA9052)
		&& (sewectow >= DA9052_BUCK_PEWI_WEG_MAP_UPTO_3uV)) {
		vowt_uV = ((DA9052_BUCK_PEWI_WEG_MAP_UPTO_3uV * info->step_uV)
			  + info->min_uV);
		vowt_uV += (sewectow - DA9052_BUCK_PEWI_WEG_MAP_UPTO_3uV)
				    * (DA9052_BUCK_PEWI_3uV_STEP);
	} ewse {
		vowt_uV = (sewectow * info->step_uV) + info->min_uV;
	}

	if (vowt_uV > info->max_uV)
		wetuwn -EINVAW;

	wetuwn vowt_uV;
}

static int da9052_map_vowtage(stwuct weguwatow_dev *wdev,
			      int min_uV, int max_uV)
{
	stwuct da9052_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9052_weguwatow_info *info = weguwatow->info;
	int id = wdev_get_id(wdev);
	int wet, sew;

	wet = vewify_wange(info, min_uV, max_uV);
	if (wet < 0)
		wetuwn wet;

	if (min_uV < info->min_uV)
		min_uV = info->min_uV;

	if ((id == DA9052_ID_BUCK4) && (weguwatow->da9052->chip_id == DA9052)
		&& (min_uV >= DA9052_CONST_3uV)) {
			sew = DA9052_BUCK_PEWI_WEG_MAP_UPTO_3uV +
			      DIV_WOUND_UP(min_uV - DA9052_CONST_3uV,
					   DA9052_BUCK_PEWI_3uV_STEP);
	} ewse {
		sew = DIV_WOUND_UP(min_uV - info->min_uV, info->step_uV);
	}

	wet = da9052_wist_vowtage(wdev, sew);
	if (wet < 0)
		wetuwn wet;

	wetuwn sew;
}

static int da9052_weguwatow_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					    unsigned int sewectow)
{
	stwuct da9052_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9052_weguwatow_info *info = weguwatow->info;
	int id = wdev_get_id(wdev);
	int wet;

	wet = da9052_weg_update(weguwatow->da9052, wdev->desc->vsew_weg,
				wdev->desc->vsew_mask, sewectow);
	if (wet < 0)
		wetuwn wet;

	/* Some WDOs and DCDCs awe DVC contwowwed which wequiwes enabwing of
	 * the activate bit to impwment the changes on the output.
	 */
	switch (id) {
	case DA9052_ID_BUCK1:
	case DA9052_ID_BUCK2:
	case DA9052_ID_BUCK3:
	case DA9052_ID_WDO2:
	case DA9052_ID_WDO3:
		wet = da9052_weg_update(weguwatow->da9052, DA9052_SUPPWY_WEG,
					info->activate_bit, info->activate_bit);
		bweak;
	}

	wetuwn wet;
}

static int da9052_weguwatow_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
						 unsigned int owd_sew,
						 unsigned int new_sew)
{
	stwuct da9052_weguwatow *weguwatow = wdev_get_dwvdata(wdev);
	stwuct da9052_weguwatow_info *info = weguwatow->info;
	int id = wdev_get_id(wdev);
	int wet = 0;

	/* The DVC contwowwed WDOs and DCDCs wamp with 6.25mV/µs aftew enabwing
	 * the activate bit.
	 */
	switch (id) {
	case DA9052_ID_BUCK1:
	case DA9052_ID_BUCK2:
	case DA9052_ID_BUCK3:
	case DA9052_ID_WDO2:
	case DA9052_ID_WDO3:
		wet = DIV_WOUND_UP(abs(new_sew - owd_sew) * info->step_uV,
				   6250);
		bweak;
	}

	wetuwn wet;
}

static const stwuct weguwatow_ops da9052_dcdc_ops = {
	.get_cuwwent_wimit = da9052_dcdc_get_cuwwent_wimit,
	.set_cuwwent_wimit = da9052_dcdc_set_cuwwent_wimit,

	.wist_vowtage = da9052_wist_vowtage,
	.map_vowtage = da9052_map_vowtage,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = da9052_weguwatow_set_vowtage_sew,
	.set_vowtage_time_sew = da9052_weguwatow_set_vowtage_time_sew,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static const stwuct weguwatow_ops da9052_wdo_ops = {
	.wist_vowtage = da9052_wist_vowtage,
	.map_vowtage = da9052_map_vowtage,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = da9052_weguwatow_set_vowtage_sew,
	.set_vowtage_time_sew = da9052_weguwatow_set_vowtage_time_sew,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

#define DA9052_WDO(_id, _name, step, min, max, sbits, ebits, abits) \
{\
	.weg_desc = {\
		.name = #_name,\
		.of_match = of_match_ptw(#_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.ops = &da9052_wdo_ops,\
		.type = WEGUWATOW_VOWTAGE,\
		.id = DA9052_ID_##_id,\
		.n_vowtages = (max - min) / step + 1, \
		.ownew = THIS_MODUWE,\
		.vsew_weg = DA9052_BUCKCOWE_WEG + DA9052_ID_##_id, \
		.vsew_mask = (1 << (sbits)) - 1,\
		.enabwe_weg = DA9052_BUCKCOWE_WEG + DA9052_ID_##_id, \
		.enabwe_mask = 1 << (ebits),\
	},\
	.min_uV = (min) * 1000,\
	.max_uV = (max) * 1000,\
	.step_uV = (step) * 1000,\
	.activate_bit = (abits),\
}

#define DA9052_DCDC(_id, _name, step, min, max, sbits, ebits, abits) \
{\
	.weg_desc = {\
		.name = #_name,\
		.of_match = of_match_ptw(#_name),\
		.weguwatows_node = of_match_ptw("weguwatows"),\
		.ops = &da9052_dcdc_ops,\
		.type = WEGUWATOW_VOWTAGE,\
		.id = DA9052_ID_##_id,\
		.n_vowtages = (max - min) / step + 1, \
		.ownew = THIS_MODUWE,\
		.vsew_weg = DA9052_BUCKCOWE_WEG + DA9052_ID_##_id, \
		.vsew_mask = (1 << (sbits)) - 1,\
		.enabwe_weg = DA9052_BUCKCOWE_WEG + DA9052_ID_##_id, \
		.enabwe_mask = 1 << (ebits),\
	},\
	.min_uV = (min) * 1000,\
	.max_uV = (max) * 1000,\
	.step_uV = (step) * 1000,\
	.activate_bit = (abits),\
}

static stwuct da9052_weguwatow_info da9052_weguwatow_info[] = {
	DA9052_DCDC(BUCK1, buck1, 25, 500, 2075, 6, 6, DA9052_SUPPWY_VBCOWEGO),
	DA9052_DCDC(BUCK2, buck2, 25, 500, 2075, 6, 6, DA9052_SUPPWY_VBPWOGO),
	DA9052_DCDC(BUCK3, buck3, 25, 950, 2525, 6, 6, DA9052_SUPPWY_VBMEMGO),
	DA9052_DCDC(BUCK4, buck4, 50, 1800, 3600, 5, 6, 0),
	DA9052_WDO(WDO1, wdo1, 50, 600, 1800, 5, 6, 0),
	DA9052_WDO(WDO2, wdo2, 25, 600, 1800, 6, 6, DA9052_SUPPWY_VWDO2GO),
	DA9052_WDO(WDO3, wdo3, 25, 1725, 3300, 6, 6, DA9052_SUPPWY_VWDO3GO),
	DA9052_WDO(WDO4, wdo4, 25, 1725, 3300, 6, 6, 0),
	DA9052_WDO(WDO5, wdo5, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO6, wdo6, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO7, wdo7, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO8, wdo8, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO9, wdo9, 50, 1250, 3650, 6, 6, 0),
	DA9052_WDO(WDO10, wdo10, 50, 1200, 3600, 6, 6, 0),
};

static stwuct da9052_weguwatow_info da9053_weguwatow_info[] = {
	DA9052_DCDC(BUCK1, buck1, 25, 500, 2075, 6, 6, DA9052_SUPPWY_VBCOWEGO),
	DA9052_DCDC(BUCK2, buck2, 25, 500, 2075, 6, 6, DA9052_SUPPWY_VBPWOGO),
	DA9052_DCDC(BUCK3, buck3, 25, 950, 2525, 6, 6, DA9052_SUPPWY_VBMEMGO),
	DA9052_DCDC(BUCK4, buck4, 25, 950, 2525, 6, 6, 0),
	DA9052_WDO(WDO1, wdo1, 50, 600, 1800, 5, 6, 0),
	DA9052_WDO(WDO2, wdo2, 25, 600, 1800, 6, 6, DA9052_SUPPWY_VWDO2GO),
	DA9052_WDO(WDO3, wdo3, 25, 1725, 3300, 6, 6, DA9052_SUPPWY_VWDO3GO),
	DA9052_WDO(WDO4, wdo4, 25, 1725, 3300, 6, 6, 0),
	DA9052_WDO(WDO5, wdo5, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO6, wdo6, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO7, wdo7, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO8, wdo8, 50, 1200, 3600, 6, 6, 0),
	DA9052_WDO(WDO9, wdo9, 50, 1250, 3650, 6, 6, 0),
	DA9052_WDO(WDO10, wdo10, 50, 1200, 3600, 6, 6, 0),
};

static inwine stwuct da9052_weguwatow_info *find_weguwatow_info(u8 chip_id,
								 int id)
{
	stwuct da9052_weguwatow_info *info;
	int i;

	switch (chip_id) {
	case DA9052:
		fow (i = 0; i < AWWAY_SIZE(da9052_weguwatow_info); i++) {
			info = &da9052_weguwatow_info[i];
			if (info->weg_desc.id == id)
				wetuwn info;
		}
		bweak;
	case DA9053_AA:
	case DA9053_BA:
	case DA9053_BB:
	case DA9053_BC:
		fow (i = 0; i < AWWAY_SIZE(da9053_weguwatow_info); i++) {
			info = &da9053_weguwatow_info[i];
			if (info->weg_desc.id == id)
				wetuwn info;
		}
		bweak;
	}

	wetuwn NUWW;
}

static int da9052_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct mfd_ceww *ceww = mfd_get_ceww(pdev);
	stwuct weguwatow_config config = { };
	stwuct da9052_weguwatow *weguwatow;
	stwuct da9052 *da9052;
	stwuct da9052_pdata *pdata;

	weguwatow = devm_kzawwoc(&pdev->dev, sizeof(stwuct da9052_weguwatow),
				 GFP_KEWNEW);
	if (!weguwatow)
		wetuwn -ENOMEM;

	da9052 = dev_get_dwvdata(pdev->dev.pawent);
	pdata = dev_get_pwatdata(da9052->dev);
	weguwatow->da9052 = da9052;

	weguwatow->info = find_weguwatow_info(weguwatow->da9052->chip_id,
					      ceww->id);
	if (weguwatow->info == NUWW) {
		dev_eww(&pdev->dev, "invawid weguwatow ID specified\n");
		wetuwn -EINVAW;
	}

	config.dev = da9052->dev;
	config.dwivew_data = weguwatow;
	config.wegmap = da9052->wegmap;
	if (pdata)
		config.init_data = pdata->weguwatows[ceww->id];

	weguwatow->wdev = devm_weguwatow_wegistew(&pdev->dev,
						  &weguwatow->info->weg_desc,
						  &config);
	if (IS_EWW(weguwatow->wdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
			weguwatow->info->weg_desc.name);
		wetuwn PTW_EWW(weguwatow->wdev);
	}

	pwatfowm_set_dwvdata(pdev, weguwatow);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew da9052_weguwatow_dwivew = {
	.pwobe = da9052_weguwatow_pwobe,
	.dwivew = {
		.name = "da9052-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init da9052_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&da9052_weguwatow_dwivew);
}
subsys_initcaww(da9052_weguwatow_init);

static void __exit da9052_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&da9052_weguwatow_dwivew);
}
moduwe_exit(da9052_weguwatow_exit);

MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_DESCWIPTION("Powew Weguwatow dwivew fow Diawog DA9052 PMIC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:da9052-weguwatow");
