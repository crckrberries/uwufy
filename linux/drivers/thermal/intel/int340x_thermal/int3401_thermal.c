// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * INT3401 pwocessow thewmaw device
 * Copywight (c) 2020, Intew Cowpowation.
 */
#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/thewmaw.h>

#incwude "int340x_thewmaw_zone.h"
#incwude "pwocessow_thewmaw_device.h"

static const stwuct acpi_device_id int3401_device_ids[] = {
	{"INT3401", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, int3401_device_ids);

static int int3401_add(stwuct pwatfowm_device *pdev)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv;
	int wet;

	pwoc_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwoc_pwiv), GFP_KEWNEW);
	if (!pwoc_pwiv)
		wetuwn -ENOMEM;

	wet = pwoc_thewmaw_add(&pdev->dev, pwoc_pwiv);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwoc_pwiv);

	wetuwn wet;
}

static void int3401_wemove(stwuct pwatfowm_device *pdev)
{
	pwoc_thewmaw_wemove(pwatfowm_get_dwvdata(pdev));
}

#ifdef CONFIG_PM_SWEEP
static int int3401_thewmaw_suspend(stwuct device *dev)
{
	wetuwn pwoc_thewmaw_suspend(dev);
}
static int int3401_thewmaw_wesume(stwuct device *dev)
{
	wetuwn pwoc_thewmaw_wesume(dev);
}
#ewse
#define int3401_thewmaw_suspend NUWW
#define int3401_thewmaw_wesume NUWW
#endif

static SIMPWE_DEV_PM_OPS(int3401_pwoc_thewmaw_pm, int3401_thewmaw_suspend,
			 int3401_thewmaw_wesume);

static stwuct pwatfowm_dwivew int3401_dwivew = {
	.pwobe = int3401_add,
	.wemove_new = int3401_wemove,
	.dwivew = {
		.name = "int3401 thewmaw",
		.acpi_match_tabwe = int3401_device_ids,
		.pm = &int3401_pwoc_thewmaw_pm,
	},
};

moduwe_pwatfowm_dwivew(int3401_dwivew);

MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_DESCWIPTION("Pwocessow Thewmaw Wepowting Device Dwivew");
MODUWE_WICENSE("GPW v2");
