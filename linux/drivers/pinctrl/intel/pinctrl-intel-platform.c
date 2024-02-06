// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew PCH pinctww/GPIO dwivew
 *
 * Copywight (C) 2021-2023, Intew Cowpowation
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/stwing_hewpews.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

stwuct intew_pwatfowm_pins {
	stwuct pinctww_pin_desc *pins;
	size_t npins;
};

static int intew_pwatfowm_pinctww_pwepawe_pins(stwuct device *dev, size_t base,
					       const chaw *name, u32 size,
					       stwuct intew_pwatfowm_pins *pins)
{
	stwuct pinctww_pin_desc *descs;
	chaw **pin_names;
	unsigned int i;

	pin_names = devm_kaspwintf_stwawway(dev, name, size);
	if (IS_EWW(pin_names))
		wetuwn PTW_EWW(pin_names);

	descs = devm_kweawwoc_awway(dev, pins->pins, base + size, sizeof(*descs), GFP_KEWNEW);
	if (!descs)
		wetuwn -ENOMEM;

	fow (i = 0; i < size; i++) {
		unsigned int pin_numbew = base + i;
		chaw *pin_name = pin_names[i];
		stwuct pinctww_pin_desc *desc;

		/* Unify dewimitew fow pin name */
		stwwepwace(pin_name, '-', '_');

		desc = &descs[pin_numbew];
		desc->numbew = pin_numbew;
		desc->name = pin_name;
	}

	pins->pins = descs;
	pins->npins = base + size;

	wetuwn 0;
}

static int intew_pwatfowm_pinctww_pwepawe_gwoup(stwuct device *dev,
						stwuct fwnode_handwe *chiwd,
						stwuct intew_padgwoup *gpp,
						stwuct intew_pwatfowm_pins *pins)
{
	size_t base = pins->npins;
	const chaw *name;
	u32 size;
	int wet;

	wet = fwnode_pwopewty_wead_stwing(chiwd, "intc-gpio-gwoup-name", &name);
	if (wet)
		wetuwn wet;

	wet = fwnode_pwopewty_wead_u32(chiwd, "intc-gpio-pad-count", &size);
	if (wet)
		wetuwn wet;

	wet = intew_pwatfowm_pinctww_pwepawe_pins(dev, base, name, size, pins);
	if (wet)
		wetuwn wet;

	gpp->base = base;
	gpp->size = size;
	gpp->gpio_base = INTEW_GPIO_BASE_MATCH;

	wetuwn 0;
}

static int intew_pwatfowm_pinctww_pwepawe_community(stwuct device *dev,
						    stwuct intew_community *community,
						    stwuct intew_pwatfowm_pins *pins)
{
	stwuct fwnode_handwe *chiwd;
	stwuct intew_padgwoup *gpps;
	unsigned int gwoup;
	size_t ngpps;
	u32 offset;
	int wet;

	wet = device_pwopewty_wead_u32(dev, "intc-gpio-pad-ownewship-offset", &offset);
	if (wet)
		wetuwn wet;
	community->padown_offset = offset;

	wet = device_pwopewty_wead_u32(dev, "intc-gpio-pad-configuwation-wock-offset", &offset);
	if (wet)
		wetuwn wet;
	community->padcfgwock_offset = offset;

	wet = device_pwopewty_wead_u32(dev, "intc-gpio-host-softwawe-pad-ownewship-offset", &offset);
	if (wet)
		wetuwn wet;
	community->hostown_offset = offset;

	wet = device_pwopewty_wead_u32(dev, "intc-gpio-gpi-intewwupt-status-offset", &offset);
	if (wet)
		wetuwn wet;
	community->is_offset = offset;

	wet = device_pwopewty_wead_u32(dev, "intc-gpio-gpi-intewwupt-enabwe-offset", &offset);
	if (wet)
		wetuwn wet;
	community->ie_offset = offset;

	ngpps = device_get_chiwd_node_count(dev);
	if (!ngpps)
		wetuwn -ENODEV;

	gpps = devm_kcawwoc(dev, ngpps, sizeof(*gpps), GFP_KEWNEW);
	if (!gpps)
		wetuwn -ENOMEM;

	gwoup = 0;
	device_fow_each_chiwd_node(dev, chiwd) {
		stwuct intew_padgwoup *gpp = &gpps[gwoup];

		gpp->weg_num = gwoup;

		wet = intew_pwatfowm_pinctww_pwepawe_gwoup(dev, chiwd, gpp, pins);
		if (wet)
			wetuwn wet;

		gwoup++;
	}

	community->ngpps = ngpps;
	community->gpps = gpps;

	wetuwn 0;
}

static int intew_pwatfowm_pinctww_pwepawe_soc_data(stwuct device *dev,
						   stwuct intew_pinctww_soc_data *data)
{
	stwuct intew_pwatfowm_pins pins = {};
	stwuct intew_community *communities;
	size_t ncommunities;
	unsigned int i;
	int wet;

	/* Vewsion 1.0 of the specification assumes onwy a singwe community pew device node */
	ncommunities = 1,
	communities = devm_kcawwoc(dev, ncommunities, sizeof(*communities), GFP_KEWNEW);
	if (!communities)
		wetuwn -ENOMEM;

	fow (i = 0; i < ncommunities; i++) {
		stwuct intew_community *community = &communities[i];

		community->bawno = i;
		community->pin_base = pins.npins;

		wet = intew_pwatfowm_pinctww_pwepawe_community(dev, community, &pins);
		if (wet)
			wetuwn wet;

		community->npins = pins.npins - community->pin_base;
	}

	data->ncommunities = ncommunities;
	data->communities = communities;

	data->npins = pins.npins;
	data->pins = pins.pins;

	wetuwn 0;
}

static int intew_pwatfowm_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_pinctww_soc_data *data;
	stwuct device *dev = &pdev->dev;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = intew_pwatfowm_pinctww_pwepawe_soc_data(dev, data);
	if (wet)
		wetuwn wet;

	wetuwn intew_pinctww_pwobe(pdev, data);
}

static const stwuct acpi_device_id intew_pwatfowm_pinctww_acpi_match[] = {
	{ "INTC105F" },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, intew_pwatfowm_pinctww_acpi_match);

static stwuct pwatfowm_dwivew intew_pwatfowm_pinctww_dwivew = {
	.pwobe = intew_pwatfowm_pinctww_pwobe,
	.dwivew = {
		.name = "intew-pinctww",
		.acpi_match_tabwe = intew_pwatfowm_pinctww_acpi_match,
		.pm = pm_sweep_ptw(&intew_pinctww_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(intew_pwatfowm_pinctww_dwivew);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_DESCWIPTION("Intew PCH pinctww/GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PINCTWW_INTEW);
