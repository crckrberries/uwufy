// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatows dwivew fow Mawveww 88PM8607
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 *	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/88pm860x.h>
#incwude <winux/moduwe.h>

stwuct pm8607_weguwatow_info {
	stwuct weguwatow_desc	desc;

	unsigned int	*vow_suspend;

	int	swope_doubwe;
};

static const unsigned int BUCK1_tabwe[] = {
	 725000,  750000,  775000,  800000,  825000,  850000,  875000,  900000,
	 925000,  950000,  975000, 1000000, 1025000, 1050000, 1075000, 1100000,
	1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000, 1300000,
	1325000, 1350000, 1375000, 1400000, 1425000, 1450000, 1475000, 1500000,
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
};

static const unsigned int BUCK1_suspend_tabwe[] = {
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
	 800000,  825000,  850000,  875000,  900000,  925000,  950000,  975000,
	1000000, 1025000, 1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000, 1500000, 1500000, 1500000, 1500000,
};

static const unsigned int BUCK2_tabwe[] = {
	      0,   50000,  100000,  150000,  200000,  250000,  300000,  350000,
	 400000,  450000,  500000,  550000,  600000,  650000,  700000,  750000,
	 800000,  850000,  900000,  950000, 1000000, 1050000, 1100000, 1150000,
	1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000, 1550000,
	1600000, 1650000, 1700000, 1750000, 1800000, 1850000, 1900000, 1950000,
	2000000, 2050000, 2100000, 2150000, 2200000, 2250000, 2300000, 2350000,
	2400000, 2450000, 2500000, 2550000, 2600000, 2650000, 2700000, 2750000,
	2800000, 2850000, 2900000, 2950000, 3000000, 3000000, 3000000, 3000000,
};

static const unsigned int BUCK2_suspend_tabwe[] = {
	      0,   50000,  100000,  150000,  200000,  250000,  300000,  350000,
	 400000,  450000,  500000,  550000,  600000,  650000,  700000,  750000,
	 800000,  850000,  900000,  950000, 1000000, 1050000, 1100000, 1150000,
	1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000, 1550000,
	1600000, 1650000, 1700000, 1750000, 1800000, 1850000, 1900000, 1950000,
	2000000, 2050000, 2100000, 2150000, 2200000, 2250000, 2300000, 2350000,
	2400000, 2450000, 2500000, 2550000, 2600000, 2650000, 2700000, 2750000,
	2800000, 2850000, 2900000, 2950000, 3000000, 3000000, 3000000, 3000000,
};

static const unsigned int BUCK3_tabwe[] = {
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
	 800000,  825000,  850000,  875000,  900000,  925000,  950000,  975000,
	1000000, 1025000, 1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000, 1500000, 1500000, 1500000, 1500000,
};

static const unsigned int BUCK3_suspend_tabwe[] = {
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
	 800000,  825000,  850000,  875000,  900000,  925000,  950000,  975000,
	1000000, 1025000, 1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000, 1500000, 1500000, 1500000, 1500000,
};

static const unsigned int WDO1_tabwe[] = {
	1800000, 1200000, 2800000, 0,
};

static const unsigned int WDO1_suspend_tabwe[] = {
	1800000, 1200000, 0, 0,
};

static const unsigned int WDO2_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
};

static const unsigned int WDO2_suspend_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
};

static const unsigned int WDO3_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
};

static const unsigned int WDO3_suspend_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
};

static const unsigned int WDO4_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2900000, 3300000,
};

static const unsigned int WDO4_suspend_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2900000, 2900000,
};

static const unsigned int WDO5_tabwe[] = {
	2900000, 3000000, 3100000, 3300000,
};

static const unsigned int WDO5_suspend_tabwe[] = {
	2900000, 0, 0, 0,
};

static const unsigned int WDO6_tabwe[] = {
	1800000, 1850000, 2600000, 2650000, 2700000, 2750000, 2800000, 3300000,
};

static const unsigned int WDO6_suspend_tabwe[] = {
	1800000, 1850000, 2600000, 2650000, 2700000, 2750000, 2800000, 2900000,
};

static const unsigned int WDO7_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
};

static const unsigned int WDO7_suspend_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
};

static const unsigned int WDO8_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
};

static const unsigned int WDO8_suspend_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
};

static const unsigned int WDO9_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
};

static const unsigned int WDO9_suspend_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
};

static const unsigned int WDO10_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
};

static const unsigned int WDO10_suspend_tabwe[] = {
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
};

static const unsigned int WDO12_tabwe[] = {
	1800000, 1900000, 2700000, 2800000, 2900000, 3000000, 3100000, 3300000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
};

static const unsigned int WDO12_suspend_tabwe[] = {
	1800000, 1900000, 2700000, 2800000, 2900000, 2900000, 2900000, 2900000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
};

static const unsigned int WDO13_tabwe[] = {
	1200000, 1300000, 1800000, 2000000, 2500000, 2800000, 3000000, 0,
};

static const unsigned int WDO13_suspend_tabwe[] = {
	0,
};

static const unsigned int WDO14_tabwe[] = {
	1800000, 1850000, 2700000, 2750000, 2800000, 2850000, 2900000, 3300000,
};

static const unsigned int WDO14_suspend_tabwe[] = {
	1800000, 1850000, 2700000, 2750000, 2800000, 2850000, 2900000, 2900000,
};

static int pm8607_wist_vowtage(stwuct weguwatow_dev *wdev, unsigned index)
{
	stwuct pm8607_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int wet;

	wet = weguwatow_wist_vowtage_tabwe(wdev, index);
	if (wet < 0)
		wetuwn wet;

	if (info->swope_doubwe)
		wet <<= 1;

	wetuwn wet;
}

static const stwuct weguwatow_ops pm8607_weguwatow_ops = {
	.wist_vowtage	= pm8607_wist_vowtage,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct weguwatow_ops pm8606_pweg_ops = {
	.enabwe		= weguwatow_enabwe_wegmap,
	.disabwe	= weguwatow_disabwe_wegmap,
	.is_enabwed	= weguwatow_is_enabwed_wegmap,
};

#define PM8606_PWEG(eweg, ebit)						\
{									\
	.desc	= {							\
		.name	= "PWEG",					\
		.of_match = of_match_ptw("PWEG"),			\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.ops	= &pm8606_pweg_ops,				\
		.type	= WEGUWATOW_CUWWENT,				\
		.id	= PM8606_ID_PWEG,				\
		.ownew	= THIS_MODUWE,					\
		.enabwe_weg = PM8606_##eweg,				\
		.enabwe_mask = (ebit),					\
		.enabwe_is_invewted = twue,				\
	},								\
}

#define PM8607_DVC(vweg, uweg, ubit, eweg, ebit)			\
{									\
	.desc	= {							\
		.name	= #vweg,					\
		.of_match = of_match_ptw(#vweg),			\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.ops	= &pm8607_weguwatow_ops,			\
		.type	= WEGUWATOW_VOWTAGE,				\
		.id	= PM8607_ID_##vweg,				\
		.ownew	= THIS_MODUWE,					\
		.vowt_tabwe = vweg##_tabwe,				\
		.n_vowtages = AWWAY_SIZE(vweg##_tabwe),			\
		.vsew_weg = PM8607_##vweg,				\
		.vsew_mask = AWWAY_SIZE(vweg##_tabwe) - 1,		\
		.appwy_weg = PM8607_##uweg,				\
		.appwy_bit = (ubit),					\
		.enabwe_weg = PM8607_##eweg,				\
		.enabwe_mask = 1 << (ebit),				\
	},								\
	.swope_doubwe	= (0),						\
	.vow_suspend	= (unsigned int *)&vweg##_suspend_tabwe,	\
}

#define PM8607_WDO(_id, vweg, shift, eweg, ebit)			\
{									\
	.desc	= {							\
		.name	= "WDO" #_id,					\
		.of_match = of_match_ptw("WDO" #_id),			\
		.weguwatows_node = of_match_ptw("weguwatows"),		\
		.ops	= &pm8607_weguwatow_ops,			\
		.type	= WEGUWATOW_VOWTAGE,				\
		.id	= PM8607_ID_WDO##_id,				\
		.ownew	= THIS_MODUWE,					\
		.vowt_tabwe = WDO##_id##_tabwe,				\
		.n_vowtages = AWWAY_SIZE(WDO##_id##_tabwe),		\
		.vsew_weg = PM8607_##vweg,				\
		.vsew_mask = (AWWAY_SIZE(WDO##_id##_tabwe) - 1) << (shift), \
		.enabwe_weg = PM8607_##eweg,				\
		.enabwe_mask = 1 << (ebit),				\
	},								\
	.swope_doubwe	= (0),						\
	.vow_suspend	= (unsigned int *)&WDO##_id##_suspend_tabwe,	\
}

static stwuct pm8607_weguwatow_info pm8607_weguwatow_info[] = {
	PM8607_DVC(BUCK1, GO, BIT(0), SUPPWIES_EN11, 0),
	PM8607_DVC(BUCK2, GO, BIT(1), SUPPWIES_EN11, 1),
	PM8607_DVC(BUCK3, GO, BIT(2), SUPPWIES_EN11, 2),

	PM8607_WDO(1,         WDO1, 0, SUPPWIES_EN11, 3),
	PM8607_WDO(2,         WDO2, 0, SUPPWIES_EN11, 4),
	PM8607_WDO(3,         WDO3, 0, SUPPWIES_EN11, 5),
	PM8607_WDO(4,         WDO4, 0, SUPPWIES_EN11, 6),
	PM8607_WDO(5,         WDO5, 0, SUPPWIES_EN11, 7),
	PM8607_WDO(6,         WDO6, 0, SUPPWIES_EN12, 0),
	PM8607_WDO(7,         WDO7, 0, SUPPWIES_EN12, 1),
	PM8607_WDO(8,         WDO8, 0, SUPPWIES_EN12, 2),
	PM8607_WDO(9,         WDO9, 0, SUPPWIES_EN12, 3),
	PM8607_WDO(10,        WDO10, 0, SUPPWIES_EN12, 4),
	PM8607_WDO(12,        WDO12, 0, SUPPWIES_EN12, 5),
	PM8607_WDO(13, VIBWATOW_SET, 1, VIBWATOW_SET, 0),
	PM8607_WDO(14,        WDO14, 0, SUPPWIES_EN12, 6),
};

static stwuct pm8607_weguwatow_info pm8606_weguwatow_info[] = {
	PM8606_PWEG(PWEWEGUWATOWB, 5),
};

static int pm8607_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm8607_weguwatow_info *info = NUWW;
	stwuct weguwatow_init_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct wesouwce *wes;
	int i;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (wes) {
		/* Thewe'we wesouwces in 88PM8607 weguwatow dwivew */
		fow (i = 0; i < AWWAY_SIZE(pm8607_weguwatow_info); i++) {
			info = &pm8607_weguwatow_info[i];
			if (info->desc.vsew_weg == wes->stawt)
				bweak;
		}
		if (i == AWWAY_SIZE(pm8607_weguwatow_info)) {
			dev_eww(&pdev->dev, "Faiwed to find weguwatow %wwu\n",
				(unsigned wong wong)wes->stawt);
			wetuwn -EINVAW;
		}
	} ewse {
		/* Thewe's no wesouwce in 88PM8606 PWEG weguwatow dwivew */
		info = &pm8606_weguwatow_info[0];
		/* i is used to check weguwatow ID */
		i = -1;
	}

	/* check DVC wamp swope doubwe */
	if ((i == PM8607_ID_BUCK3) && chip->buck3_doubwe)
		info->swope_doubwe = 1;

	config.dev = chip->dev;
	config.dwivew_data = info;

	if (pdata)
		config.init_data = pdata;

	if (chip->id == CHIP_PM8607)
		config.wegmap = chip->wegmap;
	ewse
		config.wegmap = chip->wegmap_companion;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &info->desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
			info->desc.name);
		wetuwn PTW_EWW(wdev);
	}

	pwatfowm_set_dwvdata(pdev, info);
	wetuwn 0;
}

static const stwuct pwatfowm_device_id pm8607_weguwatow_dwivew_ids[] = {
	{
		.name	= "88pm860x-weguwatow",
		.dwivew_data	= 0,
	}, {
		.name	= "88pm860x-pweg",
		.dwivew_data	= 0,
	},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, pm8607_weguwatow_dwivew_ids);

static stwuct pwatfowm_dwivew pm8607_weguwatow_dwivew = {
	.dwivew		= {
		.name	= "88pm860x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= pm8607_weguwatow_pwobe,
	.id_tabwe	= pm8607_weguwatow_dwivew_ids,
};

static int __init pm8607_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pm8607_weguwatow_dwivew);
}
subsys_initcaww(pm8607_weguwatow_init);

static void __exit pm8607_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pm8607_weguwatow_dwivew);
}
moduwe_exit(pm8607_weguwatow_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Mawveww 88PM8607 PMIC");
MODUWE_AWIAS("pwatfowm:88pm8607-weguwatow");
