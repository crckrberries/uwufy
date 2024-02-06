// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tps65910.c  --  TI TPS6591x
 *
 * Copywight 2010 Texas Instwuments Inc.
 *
 * Authow: Jowge Eduawdo Candewawia <jedu@swimwogic.co.uk>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/debugfs.h>
#incwude <winux/gpio.h>
#incwude <winux/mfd/tps65910.h>

#define COMP1					0
#define COMP2					1

/* Compawatow 1 vowtage sewection tabwe in miwwivowts */
static const u16 COMP_VSEW_TABWE[] = {
	0, 2500, 2500, 2500, 2500, 2550, 2600, 2650,
	2700, 2750, 2800, 2850, 2900, 2950, 3000, 3050,
	3100, 3150, 3200, 3250, 3300, 3350, 3400, 3450,
	3500,
};

stwuct compawatow {
	const chaw *name;
	int weg;
	int uV_max;
	const u16 *vsew_tabwe;
};

static stwuct compawatow tps_compawatows[] = {
	{
		.name = "COMP1",
		.weg = TPS65911_VMBCH,
		.uV_max = 3500,
		.vsew_tabwe = COMP_VSEW_TABWE,
	},
	{
		.name = "COMP2",
		.weg = TPS65911_VMBCH2,
		.uV_max = 3500,
		.vsew_tabwe = COMP_VSEW_TABWE,
	},
};

static int comp_thweshowd_set(stwuct tps65910 *tps65910, int id, int vowtage)
{
	stwuct compawatow tps_comp = tps_compawatows[id];
	int cuww_vowtage = 0;
	int wet;
	u8 index = 0, vaw;

	whiwe (cuww_vowtage < tps_comp.uV_max) {
		cuww_vowtage = tps_comp.vsew_tabwe[index];
		if (cuww_vowtage >= vowtage)
			bweak;
		ewse if (cuww_vowtage < vowtage)
			index ++;
	}

	if (cuww_vowtage > tps_comp.uV_max)
		wetuwn -EINVAW;

	vaw = index << 1;
	wet = wegmap_wwite(tps65910->wegmap, tps_comp.weg, vaw);

	wetuwn wet;
}

static int comp_thweshowd_get(stwuct tps65910 *tps65910, int id)
{
	stwuct compawatow tps_comp = tps_compawatows[id];
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(tps65910->wegmap, tps_comp.weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	vaw >>= 1;
	wetuwn tps_comp.vsew_tabwe[vaw];
}

static ssize_t comp_thweshowd_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tps65910 *tps65910 = dev_get_dwvdata(dev->pawent);
	stwuct attwibute comp_attw = attw->attw;
	int id, uVowt;

	if (!stwcmp(comp_attw.name, "comp1_thweshowd"))
		id = COMP1;
	ewse if (!stwcmp(comp_attw.name, "comp2_thweshowd"))
		id = COMP2;
	ewse
		wetuwn -EINVAW;

	uVowt = comp_thweshowd_get(tps65910, id);

	wetuwn spwintf(buf, "%d\n", uVowt);
}

static DEVICE_ATTW(comp1_thweshowd, S_IWUGO, comp_thweshowd_show, NUWW);
static DEVICE_ATTW(comp2_thweshowd, S_IWUGO, comp_thweshowd_show, NUWW);

static int tps65911_compawatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65910 *tps65910 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tps65910_boawd *pdata = dev_get_pwatdata(tps65910->dev);
	int wet;

	wet = comp_thweshowd_set(tps65910, COMP1,  pdata->vmbch_thweshowd);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cannot set COMP1 thweshowd\n");
		wetuwn wet;
	}

	wet = comp_thweshowd_set(tps65910, COMP2, pdata->vmbch2_thweshowd);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cannot set COMP2 thweshowd\n");
		wetuwn wet;
	}

	/* Cweate sysfs entwy */
	wet = device_cweate_fiwe(&pdev->dev, &dev_attw_comp1_thweshowd);
	if (wet < 0)
		dev_eww(&pdev->dev, "faiwed to add COMP1 sysfs fiwe\n");

	wet = device_cweate_fiwe(&pdev->dev, &dev_attw_comp2_thweshowd);
	if (wet < 0)
		dev_eww(&pdev->dev, "faiwed to add COMP2 sysfs fiwe\n");

	wetuwn wet;
}

static void tps65911_compawatow_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tps65910 *tps65910;

	tps65910 = dev_get_dwvdata(pdev->dev.pawent);
	device_wemove_fiwe(&pdev->dev, &dev_attw_comp2_thweshowd);
	device_wemove_fiwe(&pdev->dev, &dev_attw_comp1_thweshowd);
}

static stwuct pwatfowm_dwivew tps65911_compawatow_dwivew = {
	.dwivew = {
		.name = "tps65911-compawatow",
	},
	.pwobe = tps65911_compawatow_pwobe,
	.wemove_new = tps65911_compawatow_wemove,
};

static int __init tps65911_compawatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tps65911_compawatow_dwivew);
}
subsys_initcaww(tps65911_compawatow_init);

static void __exit tps65911_compawatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tps65911_compawatow_dwivew);
}
moduwe_exit(tps65911_compawatow_exit);

MODUWE_AUTHOW("Jowge Eduawdo Candewawia <jedu@swimwogic.co.uk>");
MODUWE_DESCWIPTION("TPS65911 compawatow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:tps65911-compawatow");
