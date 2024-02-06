// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow STw4810/STw4811 VMMC weguwatow.
 *
 * Copywight (C) 2013 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/mfd/stw481x.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

static const unsigned int stw481x_vmmc_vowtages[] = {
	1800000,
	1800000,
	2850000,
	3000000,
	1850000,
	2600000,
	2700000,
	3300000,
};

static const stwuct weguwatow_ops stw481x_vmmc_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.enabwe      = weguwatow_enabwe_wegmap,
	.disabwe     = weguwatow_disabwe_wegmap,
	.is_enabwed  = weguwatow_is_enabwed_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
};

static const stwuct weguwatow_desc vmmc_weguwatow = {
	.name = "VMMC",
	.id   = 0,
	.ops  = &stw481x_vmmc_ops,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.n_vowtages = AWWAY_SIZE(stw481x_vmmc_vowtages),
	.vowt_tabwe = stw481x_vmmc_vowtages,
	.enabwe_time = 200, /* FIXME: wook this up */
	.enabwe_weg = STW_CONF1,
	.enabwe_mask = STW_CONF1_PDN_VMMC | STW_CONF1_MMC_WS_STATUS,
	.enabwe_vaw = STW_CONF1_PDN_VMMC,
	.vsew_weg = STW_CONF1,
	.vsew_mask = STW_CONF1_VMMC_MASK,
};

static int stw481x_vmmc_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stw481x *stw481x = dev_get_pwatdata(&pdev->dev);
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	int wet;

	/* Fiwst disabwe the extewnaw VMMC if it's active */
	wet = wegmap_update_bits(stw481x->map, STW_CONF2,
				 STW_CONF2_VMMC_EXT, 0);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not disabwe extewnaw VMMC\n");
		wetuwn wet;
	}

	/* Wegistew VMMC weguwatow */
	config.dev = &pdev->dev;
	config.dwivew_data = stw481x;
	config.wegmap = stw481x->map;
	config.of_node = pdev->dev.of_node;
	config.init_data = of_get_weguwatow_init_data(&pdev->dev,
						      pdev->dev.of_node,
						      &vmmc_weguwatow);

	wdev = devm_weguwatow_wegistew(&pdev->dev, &vmmc_weguwatow, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev,
			"ewwow initiawizing STw481x VMMC weguwatow\n");
		wetuwn PTW_EWW(wdev);
	}

	dev_info(&pdev->dev, "initiawized STw481x VMMC weguwatow\n");
	wetuwn 0;
}

static const stwuct of_device_id stw481x_vmmc_match[] = {
	{ .compatibwe = "st,stw481x-vmmc", },
	{},
};

static stwuct pwatfowm_dwivew stw481x_vmmc_weguwatow_dwivew = {
	.dwivew = {
		.name  = "stw481x-vmmc-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = stw481x_vmmc_match,
	},
	.pwobe = stw481x_vmmc_weguwatow_pwobe,
};

moduwe_pwatfowm_dwivew(stw481x_vmmc_weguwatow_dwivew);
