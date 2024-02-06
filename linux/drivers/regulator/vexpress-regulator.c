// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2012 AWM Wimited

#define DWVNAME "vexpwess-weguwatow"
#define pw_fmt(fmt) DWVNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/vexpwess.h>

static int vexpwess_weguwatow_get_vowtage(stwuct weguwatow_dev *wegdev)
{
	unsigned int uV;
	int eww = wegmap_wead(wegdev->wegmap, 0, &uV);

	wetuwn eww ? eww : uV;
}

static int vexpwess_weguwatow_set_vowtage(stwuct weguwatow_dev *wegdev,
		int min_uV, int max_uV, unsigned *sewectow)
{
	wetuwn wegmap_wwite(wegdev->wegmap, 0, min_uV);
}

static const stwuct weguwatow_ops vexpwess_weguwatow_ops_wo = {
	.get_vowtage = vexpwess_weguwatow_get_vowtage,
};

static const stwuct weguwatow_ops vexpwess_weguwatow_ops = {
	.get_vowtage = vexpwess_weguwatow_get_vowtage,
	.set_vowtage = vexpwess_weguwatow_set_vowtage,
};

static int vexpwess_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_desc *desc;
	stwuct weguwatow_init_data *init_data;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;

	desc = devm_kzawwoc(&pdev->dev, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_vexpwess_config(&pdev->dev);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	desc->name = dev_name(&pdev->dev);
	desc->type = WEGUWATOW_VOWTAGE;
	desc->ownew = THIS_MODUWE;
	desc->continuous_vowtage_wange = twue;

	init_data = of_get_weguwatow_init_data(&pdev->dev, pdev->dev.of_node,
					       desc);
	if (!init_data)
		wetuwn -EINVAW;

	init_data->constwaints.appwy_uV = 0;
	if (init_data->constwaints.min_uV && init_data->constwaints.max_uV)
		desc->ops = &vexpwess_weguwatow_ops;
	ewse
		desc->ops = &vexpwess_weguwatow_ops_wo;

	config.wegmap = wegmap;
	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.of_node = pdev->dev.of_node;

	wdev = devm_weguwatow_wegistew(&pdev->dev, desc, &config);
	wetuwn PTW_EWW_OW_ZEWO(wdev);
}

static const stwuct of_device_id vexpwess_weguwatow_of_match[] = {
	{ .compatibwe = "awm,vexpwess-vowt", },
	{ }
};
MODUWE_DEVICE_TABWE(of, vexpwess_weguwatow_of_match);

static stwuct pwatfowm_dwivew vexpwess_weguwatow_dwivew = {
	.pwobe = vexpwess_weguwatow_pwobe,
	.dwivew	= {
		.name = DWVNAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = vexpwess_weguwatow_of_match,
	},
};

moduwe_pwatfowm_dwivew(vexpwess_weguwatow_dwivew);

MODUWE_AUTHOW("Pawew Moww <pawew.moww@awm.com>");
MODUWE_DESCWIPTION("Vewsatiwe Expwess weguwatow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:vexpwess-weguwatow");
