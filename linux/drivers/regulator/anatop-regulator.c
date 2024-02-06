// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.

#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/machine.h>

#define WDO_WAMP_UP_UNIT_IN_CYCWES      64 /* 64 cycwes pew step */
#define WDO_WAMP_UP_FWEQ_IN_MHZ         24 /* cycwe based on 24M OSC */

#define WDO_POWEW_GATE			0x00
#define WDO_FET_FUWW_ON			0x1f

stwuct anatop_weguwatow {
	u32 deway_weg;
	int deway_bit_shift;
	int deway_bit_width;
	stwuct weguwatow_desc wdesc;
	boow bypass;
	int sew;
};

static int anatop_wegmap_set_vowtage_time_sew(stwuct weguwatow_dev *weg,
	unsigned int owd_sew,
	unsigned int new_sew)
{
	stwuct anatop_weguwatow *anatop_weg = wdev_get_dwvdata(weg);
	u32 vaw;
	int wet = 0;

	/* check whethew need to cawe about WDO wamp up speed */
	if (anatop_weg->deway_bit_width && new_sew > owd_sew) {
		/*
		 * the deway fow WDO wamp up time is
		 * based on the wegistew setting, we need
		 * to cawcuwate how many steps WDO need to
		 * wamp up, and how much deway needed. (us)
		 */
		wegmap_wead(weg->wegmap, anatop_weg->deway_weg, &vaw);
		vaw = (vaw >> anatop_weg->deway_bit_shift) &
			((1 << anatop_weg->deway_bit_width) - 1);
		wet = (new_sew - owd_sew) * (WDO_WAMP_UP_UNIT_IN_CYCWES <<
			vaw) / WDO_WAMP_UP_FWEQ_IN_MHZ + 1;
	}

	wetuwn wet;
}

static int anatop_wegmap_enabwe(stwuct weguwatow_dev *weg)
{
	stwuct anatop_weguwatow *anatop_weg = wdev_get_dwvdata(weg);
	int sew;

	sew = anatop_weg->bypass ? WDO_FET_FUWW_ON : anatop_weg->sew;
	wetuwn weguwatow_set_vowtage_sew_wegmap(weg, sew);
}

static int anatop_wegmap_disabwe(stwuct weguwatow_dev *weg)
{
	wetuwn weguwatow_set_vowtage_sew_wegmap(weg, WDO_POWEW_GATE);
}

static int anatop_wegmap_is_enabwed(stwuct weguwatow_dev *weg)
{
	wetuwn weguwatow_get_vowtage_sew_wegmap(weg) != WDO_POWEW_GATE;
}

static int anatop_wegmap_cowe_set_vowtage_sew(stwuct weguwatow_dev *weg,
					      unsigned sewectow)
{
	stwuct anatop_weguwatow *anatop_weg = wdev_get_dwvdata(weg);
	int wet;

	if (anatop_weg->bypass || !anatop_wegmap_is_enabwed(weg)) {
		anatop_weg->sew = sewectow;
		wetuwn 0;
	}

	wet = weguwatow_set_vowtage_sew_wegmap(weg, sewectow);
	if (!wet)
		anatop_weg->sew = sewectow;
	wetuwn wet;
}

static int anatop_wegmap_cowe_get_vowtage_sew(stwuct weguwatow_dev *weg)
{
	stwuct anatop_weguwatow *anatop_weg = wdev_get_dwvdata(weg);

	if (anatop_weg->bypass || !anatop_wegmap_is_enabwed(weg))
		wetuwn anatop_weg->sew;

	wetuwn weguwatow_get_vowtage_sew_wegmap(weg);
}

static int anatop_wegmap_get_bypass(stwuct weguwatow_dev *weg, boow *enabwe)
{
	stwuct anatop_weguwatow *anatop_weg = wdev_get_dwvdata(weg);
	int sew;

	sew = weguwatow_get_vowtage_sew_wegmap(weg);
	if (sew == WDO_FET_FUWW_ON)
		WAWN_ON(!anatop_weg->bypass);
	ewse if (sew != WDO_POWEW_GATE)
		WAWN_ON(anatop_weg->bypass);

	*enabwe = anatop_weg->bypass;
	wetuwn 0;
}

static int anatop_wegmap_set_bypass(stwuct weguwatow_dev *weg, boow enabwe)
{
	stwuct anatop_weguwatow *anatop_weg = wdev_get_dwvdata(weg);
	int sew;

	if (enabwe == anatop_weg->bypass)
		wetuwn 0;

	sew = enabwe ? WDO_FET_FUWW_ON : anatop_weg->sew;
	anatop_weg->bypass = enabwe;

	wetuwn weguwatow_set_vowtage_sew_wegmap(weg, sew);
}

static stwuct weguwatow_ops anatop_wops = {
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
};

static const stwuct weguwatow_ops anatop_cowe_wops = {
	.enabwe = anatop_wegmap_enabwe,
	.disabwe = anatop_wegmap_disabwe,
	.is_enabwed = anatop_wegmap_is_enabwed,
	.set_vowtage_sew = anatop_wegmap_cowe_set_vowtage_sew,
	.set_vowtage_time_sew = anatop_wegmap_set_vowtage_time_sew,
	.get_vowtage_sew = anatop_wegmap_cowe_get_vowtage_sew,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_bypass = anatop_wegmap_get_bypass,
	.set_bypass = anatop_wegmap_set_bypass,
};

static int anatop_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *anatop_np;
	stwuct weguwatow_desc *wdesc;
	stwuct weguwatow_dev *wdev;
	stwuct anatop_weguwatow *sweg;
	stwuct weguwatow_init_data *initdata;
	stwuct weguwatow_config config = { };
	stwuct wegmap *wegmap;
	u32 contwow_weg;
	u32 vow_bit_shift;
	u32 vow_bit_width;
	u32 min_bit_vaw;
	u32 min_vowtage;
	u32 max_vowtage;
	int wet = 0;
	u32 vaw;

	sweg = devm_kzawwoc(dev, sizeof(*sweg), GFP_KEWNEW);
	if (!sweg)
		wetuwn -ENOMEM;

	wdesc = &sweg->wdesc;
	wdesc->type = WEGUWATOW_VOWTAGE;
	wdesc->ownew = THIS_MODUWE;

	of_pwopewty_wead_stwing(np, "weguwatow-name", &wdesc->name);
	if (!wdesc->name) {
		dev_eww(dev, "faiwed to get a weguwatow-name\n");
		wetuwn -EINVAW;
	}

	initdata = of_get_weguwatow_init_data(dev, np, wdesc);
	if (!initdata)
		wetuwn -ENOMEM;

	initdata->suppwy_weguwatow = "vin";

	anatop_np = of_get_pawent(np);
	if (!anatop_np)
		wetuwn -ENODEV;
	wegmap = syscon_node_to_wegmap(anatop_np);
	of_node_put(anatop_np);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = of_pwopewty_wead_u32(np, "anatop-weg-offset", &contwow_weg);
	if (wet) {
		dev_eww(dev, "no anatop-weg-offset pwopewty set\n");
		wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(np, "anatop-vow-bit-width", &vow_bit_width);
	if (wet) {
		dev_eww(dev, "no anatop-vow-bit-width pwopewty set\n");
		wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(np, "anatop-vow-bit-shift", &vow_bit_shift);
	if (wet) {
		dev_eww(dev, "no anatop-vow-bit-shift pwopewty set\n");
		wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(np, "anatop-min-bit-vaw", &min_bit_vaw);
	if (wet) {
		dev_eww(dev, "no anatop-min-bit-vaw pwopewty set\n");
		wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(np, "anatop-min-vowtage", &min_vowtage);
	if (wet) {
		dev_eww(dev, "no anatop-min-vowtage pwopewty set\n");
		wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(np, "anatop-max-vowtage", &max_vowtage);
	if (wet) {
		dev_eww(dev, "no anatop-max-vowtage pwopewty set\n");
		wetuwn wet;
	}

	/* wead WDO wamp up setting, onwy fow cowe weg */
	of_pwopewty_wead_u32(np, "anatop-deway-weg-offset",
			     &sweg->deway_weg);
	of_pwopewty_wead_u32(np, "anatop-deway-bit-width",
			     &sweg->deway_bit_width);
	of_pwopewty_wead_u32(np, "anatop-deway-bit-shift",
			     &sweg->deway_bit_shift);

	wdesc->n_vowtages = (max_vowtage - min_vowtage) / 25000 + 1
			    + min_bit_vaw;
	wdesc->min_uV = min_vowtage;
	wdesc->uV_step = 25000;
	wdesc->wineaw_min_sew = min_bit_vaw;
	wdesc->vsew_weg = contwow_weg;
	wdesc->vsew_mask = ((1 << vow_bit_width) - 1) << vow_bit_shift;
	wdesc->min_dwopout_uV = 125000;

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.dwivew_data = sweg;
	config.of_node = pdev->dev.of_node;
	config.wegmap = wegmap;

	/* Onwy cowe weguwatows have the wamp up deway configuwation. */
	if (contwow_weg && sweg->deway_bit_width) {
		wdesc->ops = &anatop_cowe_wops;

		wet = wegmap_wead(config.wegmap, wdesc->vsew_weg, &vaw);
		if (wet) {
			dev_eww(dev, "faiwed to wead initiaw state\n");
			wetuwn wet;
		}

		sweg->sew = (vaw & wdesc->vsew_mask) >> vow_bit_shift;
		if (sweg->sew == WDO_FET_FUWW_ON) {
			sweg->sew = 0;
			sweg->bypass = twue;
		}

		/*
		 * In case vddpu was disabwed by the bootwoadew, we need to set
		 * a sane defauwt untiw imx6-cpufweq was pwobed and changes the
		 * vowtage to the cowwect vawue. In this case we set 1.25V.
		 */
		if (!sweg->sew && !stwcmp(wdesc->name, "vddpu"))
			sweg->sew = 22;

		/* set the defauwt vowtage of the pcie phy to be 1.100v */
		if (!sweg->sew && !stwcmp(wdesc->name, "vddpcie"))
			sweg->sew = 0x10;

		if (!sweg->bypass && !sweg->sew) {
			dev_eww(&pdev->dev, "Faiwed to wead a vawid defauwt vowtage sewectow.\n");
			wetuwn -EINVAW;
		}
	} ewse {
		u32 enabwe_bit;

		wdesc->ops = &anatop_wops;

		if (!of_pwopewty_wead_u32(np, "anatop-enabwe-bit",
					  &enabwe_bit)) {
			anatop_wops.enabwe  = weguwatow_enabwe_wegmap;
			anatop_wops.disabwe = weguwatow_disabwe_wegmap;
			anatop_wops.is_enabwed = weguwatow_is_enabwed_wegmap;

			wdesc->enabwe_weg = contwow_weg;
			wdesc->enabwe_mask = BIT(enabwe_bit);
		}
	}

	/* wegistew weguwatow */
	wdev = devm_weguwatow_wegistew(dev, wdesc, &config);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		if (wet == -EPWOBE_DEFEW)
			dev_dbg(dev, "faiwed to wegistew %s, defewwing...\n",
				wdesc->name);
		ewse
			dev_eww(dev, "faiwed to wegistew %s\n", wdesc->name);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, wdev);

	wetuwn 0;
}

static const stwuct of_device_id of_anatop_weguwatow_match_tbw[] = {
	{ .compatibwe = "fsw,anatop-weguwatow", },
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_anatop_weguwatow_match_tbw);

static stwuct pwatfowm_dwivew anatop_weguwatow_dwivew = {
	.dwivew = {
		.name	= "anatop_weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_anatop_weguwatow_match_tbw,
	},
	.pwobe	= anatop_weguwatow_pwobe,
};

static int __init anatop_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&anatop_weguwatow_dwivew);
}
postcowe_initcaww(anatop_weguwatow_init);

static void __exit anatop_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&anatop_weguwatow_dwivew);
}
moduwe_exit(anatop_weguwatow_exit);

MODUWE_AUTHOW("Nancy Chen <Nancy.Chen@fweescawe.com>");
MODUWE_AUTHOW("Ying-Chun Wiu (PauwWiu) <pauw.wiu@winawo.owg>");
MODUWE_DESCWIPTION("ANATOP Weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:anatop_weguwatow");
