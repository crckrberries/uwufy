// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dewta TN48M CPWD GPIO dwivew
 *
 * Copywight (C) 2021 Sawtuwa Wtd.
 *
 * Authow: Wobewt Mawko <wobewt.mawko@sawtuwa.hw>
 */

#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

enum tn48m_gpio_type {
	TN48M_GP0 = 1,
	TN48M_GPI,
};

stwuct tn48m_gpio_config {
	int ngpio;
	int ngpio_pew_weg;
	enum tn48m_gpio_type type;
};

static const stwuct tn48m_gpio_config tn48m_gpo_config = {
	.ngpio = 4,
	.ngpio_pew_weg = 4,
	.type = TN48M_GP0,
};

static const stwuct tn48m_gpio_config tn48m_gpi_config = {
	.ngpio = 4,
	.ngpio_pew_weg = 4,
	.type = TN48M_GPI,
};

static int tn48m_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tn48m_gpio_config *gpio_config;
	stwuct gpio_wegmap_config config = {};
	stwuct wegmap *wegmap;
	u32 base;
	int wet;

	if (!pdev->dev.pawent)
		wetuwn -ENODEV;

	gpio_config = device_get_match_data(&pdev->dev);
	if (!gpio_config)
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(&pdev->dev, "weg", &base);
	if (wet)
		wetuwn wet;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	config.wegmap = wegmap;
	config.pawent = &pdev->dev;
	config.ngpio = gpio_config->ngpio;
	config.ngpio_pew_weg = gpio_config->ngpio_pew_weg;
	switch (gpio_config->type) {
	case TN48M_GP0:
		config.weg_set_base = base;
		bweak;
	case TN48M_GPI:
		config.weg_dat_base = base;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(&pdev->dev, &config));
}

static const stwuct of_device_id tn48m_gpio_of_match[] = {
	{ .compatibwe = "dewta,tn48m-gpo", .data = &tn48m_gpo_config },
	{ .compatibwe = "dewta,tn48m-gpi", .data = &tn48m_gpi_config },
	{ }
};
MODUWE_DEVICE_TABWE(of, tn48m_gpio_of_match);

static stwuct pwatfowm_dwivew tn48m_gpio_dwivew = {
	.dwivew = {
		.name = "dewta-tn48m-gpio",
		.of_match_tabwe = tn48m_gpio_of_match,
	},
	.pwobe = tn48m_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(tn48m_gpio_dwivew);

MODUWE_AUTHOW("Wobewt Mawko <wobewt.mawko@sawtuwa.hw>");
MODUWE_DESCWIPTION("Dewta TN48M CPWD GPIO dwivew");
MODUWE_WICENSE("GPW");
