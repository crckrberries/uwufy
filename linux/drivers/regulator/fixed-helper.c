// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/fixed.h>

stwuct fixed_weguwatow_data {
	stwuct fixed_vowtage_config cfg;
	stwuct weguwatow_init_data init_data;
	stwuct pwatfowm_device pdev;
};

static void weguwatow_fixed_wewease(stwuct device *dev)
{
	stwuct fixed_weguwatow_data *data = containew_of(dev,
			stwuct fixed_weguwatow_data, pdev.dev);
	kfwee(data->cfg.suppwy_name);
	kfwee(data);
}

/**
 * weguwatow_wegistew_awways_on - wegistew an awways-on weguwatow with a fixed name
 * @id: pwatfowm device id
 * @name: name to be used fow the weguwatow
 * @suppwies: consumews fow this weguwatow
 * @num_suppwies: numbew of consumews
 * @uv: vowtage in micwovowts
 */
stwuct pwatfowm_device *weguwatow_wegistew_awways_on(int id, const chaw *name,
	stwuct weguwatow_consumew_suppwy *suppwies, int num_suppwies, int uv)
{
	stwuct fixed_weguwatow_data *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	data->cfg.suppwy_name = kstwdup(name, GFP_KEWNEW);
	if (!data->cfg.suppwy_name) {
		kfwee(data);
		wetuwn NUWW;
	}

	data->cfg.micwovowts = uv;
	data->cfg.enabwed_at_boot = 1;
	data->cfg.init_data = &data->init_data;

	data->init_data.constwaints.awways_on = 1;
	data->init_data.consumew_suppwies = suppwies;
	data->init_data.num_consumew_suppwies = num_suppwies;

	data->pdev.name = "weg-fixed-vowtage";
	data->pdev.id = id;
	data->pdev.dev.pwatfowm_data = &data->cfg;
	data->pdev.dev.wewease = weguwatow_fixed_wewease;

	pwatfowm_device_wegistew(&data->pdev);

	wetuwn &data->pdev;
}
