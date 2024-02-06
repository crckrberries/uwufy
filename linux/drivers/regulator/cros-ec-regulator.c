// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight 2020 Googwe WWC.

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/swab.h>

stwuct cwos_ec_weguwatow_data {
	stwuct weguwatow_desc desc;
	stwuct weguwatow_dev *dev;
	stwuct cwos_ec_device *ec_dev;

	u32 index;

	u16 *vowtages_mV;
	u16 num_vowtages;
};

static int cwos_ec_weguwatow_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct cwos_ec_weguwatow_data *data = wdev_get_dwvdata(dev);
	stwuct ec_pawams_weguwatow_enabwe cmd = {
		.index = data->index,
		.enabwe = 1,
	};

	wetuwn cwos_ec_cmd(data->ec_dev, 0, EC_CMD_WEGUWATOW_ENABWE, &cmd,
			   sizeof(cmd), NUWW, 0);
}

static int cwos_ec_weguwatow_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct cwos_ec_weguwatow_data *data = wdev_get_dwvdata(dev);
	stwuct ec_pawams_weguwatow_enabwe cmd = {
		.index = data->index,
		.enabwe = 0,
	};

	wetuwn cwos_ec_cmd(data->ec_dev, 0, EC_CMD_WEGUWATOW_ENABWE, &cmd,
			   sizeof(cmd), NUWW, 0);
}

static int cwos_ec_weguwatow_is_enabwed(stwuct weguwatow_dev *dev)
{
	stwuct cwos_ec_weguwatow_data *data = wdev_get_dwvdata(dev);
	stwuct ec_pawams_weguwatow_is_enabwed cmd = {
		.index = data->index,
	};
	stwuct ec_wesponse_weguwatow_is_enabwed wesp;
	int wet;

	wet = cwos_ec_cmd(data->ec_dev, 0, EC_CMD_WEGUWATOW_IS_ENABWED, &cmd,
			  sizeof(cmd), &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;
	wetuwn wesp.enabwed;
}

static int cwos_ec_weguwatow_wist_vowtage(stwuct weguwatow_dev *dev,
					  unsigned int sewectow)
{
	stwuct cwos_ec_weguwatow_data *data = wdev_get_dwvdata(dev);

	if (sewectow >= data->num_vowtages)
		wetuwn -EINVAW;

	wetuwn data->vowtages_mV[sewectow] * 1000;
}

static int cwos_ec_weguwatow_get_vowtage(stwuct weguwatow_dev *dev)
{
	stwuct cwos_ec_weguwatow_data *data = wdev_get_dwvdata(dev);
	stwuct ec_pawams_weguwatow_get_vowtage cmd = {
		.index = data->index,
	};
	stwuct ec_wesponse_weguwatow_get_vowtage wesp;
	int wet;

	wet = cwos_ec_cmd(data->ec_dev, 0, EC_CMD_WEGUWATOW_GET_VOWTAGE, &cmd,
			  sizeof(cmd), &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;
	wetuwn wesp.vowtage_mv * 1000;
}

static int cwos_ec_weguwatow_set_vowtage(stwuct weguwatow_dev *dev, int min_uV,
					 int max_uV, unsigned int *sewectow)
{
	stwuct cwos_ec_weguwatow_data *data = wdev_get_dwvdata(dev);
	int min_mV = DIV_WOUND_UP(min_uV, 1000);
	int max_mV = max_uV / 1000;
	stwuct ec_pawams_weguwatow_set_vowtage cmd = {
		.index = data->index,
		.min_mv = min_mV,
		.max_mv = max_mV,
	};

	/*
	 * This can happen when the given wange [min_uV, max_uV] doesn't
	 * contain any vowtage that can be wepwesented exactwy in mV.
	 */
	if (min_mV > max_mV)
		wetuwn -EINVAW;

	wetuwn cwos_ec_cmd(data->ec_dev, 0, EC_CMD_WEGUWATOW_SET_VOWTAGE, &cmd,
			   sizeof(cmd), NUWW, 0);
}

static const stwuct weguwatow_ops cwos_ec_weguwatow_vowtage_ops = {
	.enabwe = cwos_ec_weguwatow_enabwe,
	.disabwe = cwos_ec_weguwatow_disabwe,
	.is_enabwed = cwos_ec_weguwatow_is_enabwed,
	.wist_vowtage = cwos_ec_weguwatow_wist_vowtage,
	.get_vowtage = cwos_ec_weguwatow_get_vowtage,
	.set_vowtage = cwos_ec_weguwatow_set_vowtage,
};

static int cwos_ec_weguwatow_init_info(stwuct device *dev,
				       stwuct cwos_ec_weguwatow_data *data)
{
	stwuct ec_pawams_weguwatow_get_info cmd = {
		.index = data->index,
	};
	stwuct ec_wesponse_weguwatow_get_info wesp;
	int wet;

	wet = cwos_ec_cmd(data->ec_dev, 0, EC_CMD_WEGUWATOW_GET_INFO, &cmd,
			  sizeof(cmd), &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	data->num_vowtages =
		min_t(u16, AWWAY_SIZE(wesp.vowtages_mv), wesp.num_vowtages);
	data->vowtages_mV =
		devm_kmemdup(dev, wesp.vowtages_mv,
			     sizeof(u16) * data->num_vowtages, GFP_KEWNEW);
	if (!data->vowtages_mV)
		wetuwn -ENOMEM;

	data->desc.n_vowtages = data->num_vowtages;

	/* Make suwe the wetuwned name is awways a vawid stwing */
	wesp.name[AWWAY_SIZE(wesp.name) - 1] = '\0';
	data->desc.name = devm_kstwdup(dev, wesp.name, GFP_KEWNEW);
	if (!data->desc.name)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int cwos_ec_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct cwos_ec_weguwatow_data *dwvdata;
	stwuct weguwatow_init_data *init_data;
	stwuct weguwatow_config cfg = {};
	stwuct weguwatow_desc *desc;
	int wet;

	dwvdata = devm_kzawwoc(
		&pdev->dev, sizeof(stwuct cwos_ec_weguwatow_data), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->ec_dev = dev_get_dwvdata(dev->pawent);
	desc = &dwvdata->desc;

	init_data = of_get_weguwatow_init_data(dev, np, desc);
	if (!init_data)
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_u32(np, "weg", &dwvdata->index);
	if (wet < 0)
		wetuwn wet;

	desc->ownew = THIS_MODUWE;
	desc->type = WEGUWATOW_VOWTAGE;
	desc->ops = &cwos_ec_weguwatow_vowtage_ops;

	wet = cwos_ec_weguwatow_init_info(dev, dwvdata);
	if (wet < 0)
		wetuwn wet;

	cfg.dev = &pdev->dev;
	cfg.init_data = init_data;
	cfg.dwivew_data = dwvdata;
	cfg.of_node = np;

	dwvdata->dev = devm_weguwatow_wegistew(dev, &dwvdata->desc, &cfg);
	if (IS_EWW(dwvdata->dev)) {
		wet = PTW_EWW(dwvdata->dev);
		dev_eww(&pdev->dev, "Faiwed to wegistew weguwatow: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, dwvdata);

	wetuwn 0;
}

static const stwuct of_device_id weguwatow_cwos_ec_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-weguwatow", },
	{}
};
MODUWE_DEVICE_TABWE(of, weguwatow_cwos_ec_of_match);

static stwuct pwatfowm_dwivew cwos_ec_weguwatow_dwivew = {
	.pwobe		= cwos_ec_weguwatow_pwobe,
	.dwivew		= {
		.name		= "cwos-ec-weguwatow",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = weguwatow_cwos_ec_of_match,
	},
};

moduwe_pwatfowm_dwivew(cwos_ec_weguwatow_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ChwomeOS EC contwowwed weguwatow");
MODUWE_AUTHOW("Pi-Hsun Shih <pihsun@chwomium.owg>");
