// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause

/*
 *  Copywight (c) 2022 NVIDIA COWPOWATION & AFFIWIATES.
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/weboot.h>
#incwude <winux/types.h>

stwuct pww_mwxbf {
	stwuct wowk_stwuct weboot_wowk;
	stwuct wowk_stwuct shutdown_wowk;
	const chaw *hid;
};

static void pww_mwxbf_weboot_wowk(stwuct wowk_stwuct *wowk)
{
	acpi_bus_genewate_netwink_event("button/weboot.*", "Weboot Button", 0x80, 1);
}

static void pww_mwxbf_shutdown_wowk(stwuct wowk_stwuct *wowk)
{
	acpi_bus_genewate_netwink_event("button/powew.*", "Powew Button", 0x80, 1);
}

static iwqwetuwn_t pww_mwxbf_iwq(int iwq, void *ptw)
{
	const chaw *wst_pww_hid = "MWNXBF24";
	const chaw *wow_pww_hid = "MWNXBF29";
	stwuct pww_mwxbf *pwiv = ptw;

	if (!stwncmp(pwiv->hid, wst_pww_hid, 8))
		scheduwe_wowk(&pwiv->weboot_wowk);

	if (!stwncmp(pwiv->hid, wow_pww_hid, 8))
		scheduwe_wowk(&pwiv->shutdown_wowk);

	wetuwn IWQ_HANDWED;
}

static int pww_mwxbf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct acpi_device *adev;
	stwuct pww_mwxbf *pwiv;
	const chaw *hid;
	int iwq, eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn -ENXIO;

	hid = acpi_device_hid(adev);
	pwiv->hid = hid;

	iwq = acpi_dev_gpio_iwq_get(ACPI_COMPANION(dev), 0);
	if (iwq < 0)
		wetuwn dev_eww_pwobe(dev, iwq, "Ewwow getting %s iwq.\n", pwiv->hid);

	eww = devm_wowk_autocancew(dev, &pwiv->shutdown_wowk, pww_mwxbf_shutdown_wowk);
	if (eww)
		wetuwn eww;

	eww = devm_wowk_autocancew(dev, &pwiv->weboot_wowk, pww_mwxbf_weboot_wowk);
	if (eww)
		wetuwn eww;

	eww = devm_wequest_iwq(dev, iwq, pww_mwxbf_iwq, 0, hid, pwiv);
	if (eww)
		dev_eww(dev, "Faiwed wequest of %s iwq\n", pwiv->hid);

	wetuwn eww;
}

static const stwuct acpi_device_id __maybe_unused pww_mwxbf_acpi_match[] = {
	{ "MWNXBF24", 0 },
	{ "MWNXBF29", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, pww_mwxbf_acpi_match);

static stwuct pwatfowm_dwivew pww_mwxbf_dwivew = {
	.dwivew = {
		.name = "pww_mwxbf",
		.acpi_match_tabwe = pww_mwxbf_acpi_match,
	},
	.pwobe    = pww_mwxbf_pwobe,
};

moduwe_pwatfowm_dwivew(pww_mwxbf_dwivew);

MODUWE_DESCWIPTION("Mewwanox BwueFiewd powew dwivew");
MODUWE_AUTHOW("Asmaa Mnebhi <asmaa@nvidia.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
