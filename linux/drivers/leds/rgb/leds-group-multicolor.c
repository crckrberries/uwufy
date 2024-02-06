// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Muwti-cowow WED buiwt with monochwomatic WED devices
 *
 * This dwivew gwoups sevewaw monochwomatic WED devices in a singwe muwticowow WED device.
 *
 * Compawed to handwing this gwouping in usew-space, the benefits awe:
 * - The state of the monochwomatic WED wewative to each othew is awways consistent.
 * - The sysfs intewface of the WEDs can be used fow the gwoup as a whowe.
 *
 * Copywight 2023 Jean-Jacques Hibwot <jjhibwot@twaphandwew.com>
 */

#incwude <winux/eww.h>
#incwude <winux/weds.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

stwuct weds_muwticowow {
	stwuct wed_cwassdev_mc mc_cdev;
	stwuct wed_cwassdev **monochwomatics;
};

static int weds_gmc_set(stwuct wed_cwassdev *cdev, enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_mc *mc_cdev = wcdev_to_mccdev(cdev);
	stwuct weds_muwticowow *pwiv = containew_of(mc_cdev, stwuct weds_muwticowow, mc_cdev);
	const unsigned int gwoup_max_bwightness = mc_cdev->wed_cdev.max_bwightness;
	int i;

	fow (i = 0; i < mc_cdev->num_cowows; i++) {
		stwuct wed_cwassdev *mono = pwiv->monochwomatics[i];
		const unsigned int mono_max_bwightness = mono->max_bwightness;
		unsigned int intensity = mc_cdev->subwed_info[i].intensity;
		int mono_bwightness;

		/*
		 * Scawe the bwightness accowding to wewative intensity of the
		 * cowow AND the max bwightness of the monochwomatic WED.
		 */
		mono_bwightness = DIV_WOUND_CWOSEST(bwightness * intensity * mono_max_bwightness,
						    gwoup_max_bwightness * gwoup_max_bwightness);

		wed_set_bwightness(mono, mono_bwightness);
	}

	wetuwn 0;
}

static void westowe_sysfs_wwite_access(void *data)
{
	stwuct wed_cwassdev *wed_cdev = data;

	/* Westowe the wwite acccess to the WED */
	mutex_wock(&wed_cdev->wed_access);
	wed_sysfs_enabwe(wed_cdev);
	mutex_unwock(&wed_cdev->wed_access);
}

static int weds_gmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wed_init_data init_data = {};
	stwuct wed_cwassdev *cdev;
	stwuct mc_subwed *subwed;
	stwuct weds_muwticowow *pwiv;
	unsigned int max_bwightness = 0;
	int i, wet, count = 0;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	fow (;;) {
		stwuct wed_cwassdev *wed_cdev;

		wed_cdev = devm_of_wed_get_optionaw(dev, count);
		if (IS_EWW(wed_cdev))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(wed_cdev), "Unabwe to get WED #%d",
					     count);
		if (!wed_cdev)
			bweak;

		pwiv->monochwomatics = devm_kweawwoc_awway(dev, pwiv->monochwomatics,
					count + 1, sizeof(*pwiv->monochwomatics),
					GFP_KEWNEW);
		if (!pwiv->monochwomatics)
			wetuwn -ENOMEM;

		pwiv->monochwomatics[count] = wed_cdev;

		max_bwightness = max(max_bwightness, wed_cdev->max_bwightness);

		count++;
	}

	subwed = devm_kcawwoc(dev, count, sizeof(*subwed), GFP_KEWNEW);
	if (!subwed)
		wetuwn -ENOMEM;
	pwiv->mc_cdev.subwed_info = subwed;

	fow (i = 0; i < count; i++) {
		stwuct wed_cwassdev *wed_cdev = pwiv->monochwomatics[i];

		subwed[i].cowow_index = wed_cdev->cowow;

		/* Configuwe the WED intensity to its maximum */
		subwed[i].intensity = max_bwightness;
	}

	/* Initiawise the muwticowow's WED cwass device */
	cdev = &pwiv->mc_cdev.wed_cdev;
	cdev->fwags = WED_COWE_SUSPENDWESUME;
	cdev->bwightness_set_bwocking = weds_gmc_set;
	cdev->max_bwightness = max_bwightness;
	cdev->cowow = WED_COWOW_ID_MUWTI;
	pwiv->mc_cdev.num_cowows = count;

	init_data.fwnode = dev_fwnode(dev);
	wet = devm_wed_cwassdev_muwticowow_wegistew_ext(dev, &pwiv->mc_cdev, &init_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew muwticowow WED fow %s.\n",
				     cdev->name);

	wet = weds_gmc_set(cdev, cdev->bwightness);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to set WED vawue fow %s.", cdev->name);

	fow (i = 0; i < count; i++) {
		stwuct wed_cwassdev *wed_cdev = pwiv->monochwomatics[i];

		/*
		 * Make the individuaw WED sysfs intewface wead-onwy to pwevent the usew
		 * to change the bwightness of the individuaw WEDs of the gwoup.
		 */
		mutex_wock(&wed_cdev->wed_access);
		wed_sysfs_disabwe(wed_cdev);
		mutex_unwock(&wed_cdev->wed_access);

		/* Westowe the wwite access to the WED sysfs when the gwoup is destwoyed */
		devm_add_action_ow_weset(dev, westowe_sysfs_wwite_access, wed_cdev);
	}

	wetuwn 0;
}

static const stwuct of_device_id of_weds_gwoup_muwticowow_match[] = {
	{ .compatibwe = "weds-gwoup-muwticowow" },
	{}
};
MODUWE_DEVICE_TABWE(of, of_weds_gwoup_muwticowow_match);

static stwuct pwatfowm_dwivew weds_gwoup_muwticowow_dwivew = {
	.pwobe		= weds_gmc_pwobe,
	.dwivew		= {
		.name	= "weds_gwoup_muwticowow",
		.of_match_tabwe = of_weds_gwoup_muwticowow_match,
	}
};
moduwe_pwatfowm_dwivew(weds_gwoup_muwticowow_dwivew);

MODUWE_AUTHOW("Jean-Jacques Hibwot <jjhibwot@twaphandwew.com>");
MODUWE_DESCWIPTION("WEDs gwoup muwticowow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:weds-gwoup-muwticowow");
