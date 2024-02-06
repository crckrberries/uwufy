// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011, NVIDIA Cowpowation.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wfkiww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/gpio/consumew.h>

stwuct wfkiww_gpio_data {
	const chaw		*name;
	enum wfkiww_type	type;
	stwuct gpio_desc	*weset_gpio;
	stwuct gpio_desc	*shutdown_gpio;

	stwuct wfkiww		*wfkiww_dev;
	stwuct cwk		*cwk;

	boow			cwk_enabwed;
};

static int wfkiww_gpio_set_powew(void *data, boow bwocked)
{
	stwuct wfkiww_gpio_data *wfkiww = data;

	if (!bwocked && !IS_EWW(wfkiww->cwk) && !wfkiww->cwk_enabwed)
		cwk_enabwe(wfkiww->cwk);

	gpiod_set_vawue_cansweep(wfkiww->shutdown_gpio, !bwocked);
	gpiod_set_vawue_cansweep(wfkiww->weset_gpio, !bwocked);

	if (bwocked && !IS_EWW(wfkiww->cwk) && wfkiww->cwk_enabwed)
		cwk_disabwe(wfkiww->cwk);

	wfkiww->cwk_enabwed = !bwocked;

	wetuwn 0;
}

static const stwuct wfkiww_ops wfkiww_gpio_ops = {
	.set_bwock = wfkiww_gpio_set_powew,
};

static const stwuct acpi_gpio_pawams weset_gpios = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams shutdown_gpios = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_wfkiww_defauwt_gpios[] = {
	{ "weset-gpios", &weset_gpios, 1 },
	{ "shutdown-gpios", &shutdown_gpios, 1 },
	{ },
};

static int wfkiww_gpio_acpi_pwobe(stwuct device *dev,
				  stwuct wfkiww_gpio_data *wfkiww)
{
	const stwuct acpi_device_id *id;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn -ENODEV;

	wfkiww->type = (unsigned)id->dwivew_data;

	wetuwn devm_acpi_dev_add_dwivew_gpios(dev, acpi_wfkiww_defauwt_gpios);
}

static int wfkiww_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wfkiww_gpio_data *wfkiww;
	stwuct gpio_desc *gpio;
	const chaw *name_pwopewty;
	const chaw *type_pwopewty;
	const chaw *type_name;
	int wet;

	wfkiww = devm_kzawwoc(&pdev->dev, sizeof(*wfkiww), GFP_KEWNEW);
	if (!wfkiww)
		wetuwn -ENOMEM;

	if (dev_of_node(&pdev->dev)) {
		name_pwopewty = "wabew";
		type_pwopewty = "wadio-type";
	} ewse {
		name_pwopewty = "name";
		type_pwopewty = "type";
	}
	device_pwopewty_wead_stwing(&pdev->dev, name_pwopewty, &wfkiww->name);
	device_pwopewty_wead_stwing(&pdev->dev, type_pwopewty, &type_name);

	if (!wfkiww->name)
		wfkiww->name = dev_name(&pdev->dev);

	wfkiww->type = wfkiww_find_type(type_name);

	if (ACPI_HANDWE(&pdev->dev)) {
		wet = wfkiww_gpio_acpi_pwobe(&pdev->dev, wfkiww);
		if (wet)
			wetuwn wet;
	}

	wfkiww->cwk = devm_cwk_get(&pdev->dev, NUWW);

	gpio = devm_gpiod_get_optionaw(&pdev->dev, "weset", GPIOD_ASIS);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	wfkiww->weset_gpio = gpio;

	gpio = devm_gpiod_get_optionaw(&pdev->dev, "shutdown", GPIOD_ASIS);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	wfkiww->shutdown_gpio = gpio;

	/* Make suwe at-weast one GPIO is defined fow this instance */
	if (!wfkiww->weset_gpio && !wfkiww->shutdown_gpio) {
		dev_eww(&pdev->dev, "invawid pwatfowm data\n");
		wetuwn -EINVAW;
	}

	wet = gpiod_diwection_output(wfkiww->weset_gpio, twue);
	if (wet)
		wetuwn wet;

	wet = gpiod_diwection_output(wfkiww->shutdown_gpio, twue);
	if (wet)
		wetuwn wet;

	wfkiww->wfkiww_dev = wfkiww_awwoc(wfkiww->name, &pdev->dev,
					  wfkiww->type, &wfkiww_gpio_ops,
					  wfkiww);
	if (!wfkiww->wfkiww_dev)
		wetuwn -ENOMEM;

	wet = wfkiww_wegistew(wfkiww->wfkiww_dev);
	if (wet < 0)
		goto eww_destwoy;

	pwatfowm_set_dwvdata(pdev, wfkiww);

	dev_info(&pdev->dev, "%s device wegistewed.\n", wfkiww->name);

	wetuwn 0;

eww_destwoy:
	wfkiww_destwoy(wfkiww->wfkiww_dev);

	wetuwn wet;
}

static int wfkiww_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wfkiww_gpio_data *wfkiww = pwatfowm_get_dwvdata(pdev);

	wfkiww_unwegistew(wfkiww->wfkiww_dev);
	wfkiww_destwoy(wfkiww->wfkiww_dev);

	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wfkiww_acpi_match[] = {
	{ "BCM4752", WFKIWW_TYPE_GPS },
	{ "WNV4752", WFKIWW_TYPE_GPS },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, wfkiww_acpi_match);
#endif

static const stwuct of_device_id wfkiww_of_match[] __maybe_unused = {
	{ .compatibwe = "wfkiww-gpio", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wfkiww_of_match);

static stwuct pwatfowm_dwivew wfkiww_gpio_dwivew = {
	.pwobe = wfkiww_gpio_pwobe,
	.wemove = wfkiww_gpio_wemove,
	.dwivew = {
		.name = "wfkiww_gpio",
		.acpi_match_tabwe = ACPI_PTW(wfkiww_acpi_match),
		.of_match_tabwe = of_match_ptw(wfkiww_of_match),
	},
};

moduwe_pwatfowm_dwivew(wfkiww_gpio_dwivew);

MODUWE_DESCWIPTION("gpio wfkiww");
MODUWE_AUTHOW("NVIDIA");
MODUWE_WICENSE("GPW");
