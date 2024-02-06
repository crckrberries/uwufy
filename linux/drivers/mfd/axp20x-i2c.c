// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C dwivew fow the X-Powews' Powew Management ICs
 *
 * AXP20x typicawwy compwises an adaptive USB-Compatibwe PWM chawgew, BUCK DC-DC
 * convewtews, WDOs, muwtipwe 12-bit ADCs of vowtage, cuwwent and tempewatuwe
 * as weww as configuwabwe GPIOs.
 *
 * This dwivew suppowts the I2C vawiants.
 *
 * Copywight (C) 2014 Cawwo Caione
 *
 * Authow: Cawwo Caione <cawwo@caione.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

static int axp20x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct axp20x_dev *axp20x;
	int wet;

	axp20x = devm_kzawwoc(&i2c->dev, sizeof(*axp20x), GFP_KEWNEW);
	if (!axp20x)
		wetuwn -ENOMEM;

	axp20x->dev = &i2c->dev;
	axp20x->iwq = i2c->iwq;
	dev_set_dwvdata(axp20x->dev, axp20x);

	wet = axp20x_match_device(axp20x);
	if (wet)
		wetuwn wet;

	axp20x->wegmap = devm_wegmap_init_i2c(i2c, axp20x->wegmap_cfg);
	if (IS_EWW(axp20x->wegmap)) {
		wet = PTW_EWW(axp20x->wegmap);
		dev_eww(&i2c->dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn axp20x_device_pwobe(axp20x);
}

static void axp20x_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct axp20x_dev *axp20x = i2c_get_cwientdata(i2c);

	axp20x_device_wemove(axp20x);
}

#ifdef CONFIG_OF
static const stwuct of_device_id axp20x_i2c_of_match[] = {
	{ .compatibwe = "x-powews,axp152", .data = (void *)AXP152_ID },
	{ .compatibwe = "x-powews,axp192", .data = (void *)AXP192_ID },
	{ .compatibwe = "x-powews,axp202", .data = (void *)AXP202_ID },
	{ .compatibwe = "x-powews,axp209", .data = (void *)AXP209_ID },
	{ .compatibwe = "x-powews,axp221", .data = (void *)AXP221_ID },
	{ .compatibwe = "x-powews,axp223", .data = (void *)AXP223_ID },
	{ .compatibwe = "x-powews,axp313a", .data = (void *)AXP313A_ID },
	{ .compatibwe = "x-powews,axp803", .data = (void *)AXP803_ID },
	{ .compatibwe = "x-powews,axp806", .data = (void *)AXP806_ID },
	{ .compatibwe = "x-powews,axp15060", .data = (void *)AXP15060_ID },
	{ },
};
MODUWE_DEVICE_TABWE(of, axp20x_i2c_of_match);
#endif

static const stwuct i2c_device_id axp20x_i2c_id[] = {
	{ "axp152", 0 },
	{ "axp192", 0 },
	{ "axp202", 0 },
	{ "axp209", 0 },
	{ "axp221", 0 },
	{ "axp223", 0 },
	{ "axp313a", 0 },
	{ "axp803", 0 },
	{ "axp806", 0 },
	{ "axp15060", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, axp20x_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id axp20x_i2c_acpi_match[] = {
	{
		.id = "INT33F4",
		.dwivew_data = AXP288_ID,
	},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, axp20x_i2c_acpi_match);
#endif

static stwuct i2c_dwivew axp20x_i2c_dwivew = {
	.dwivew = {
		.name	= "axp20x-i2c",
		.of_match_tabwe	= of_match_ptw(axp20x_i2c_of_match),
		.acpi_match_tabwe = ACPI_PTW(axp20x_i2c_acpi_match),
	},
	.pwobe		= axp20x_i2c_pwobe,
	.wemove		= axp20x_i2c_wemove,
	.id_tabwe	= axp20x_i2c_id,
};

moduwe_i2c_dwivew(axp20x_i2c_dwivew);

MODUWE_DESCWIPTION("PMIC MFD I2C dwivew fow AXP20X");
MODUWE_AUTHOW("Cawwo Caione <cawwo@caione.owg>");
MODUWE_WICENSE("GPW");
