// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * INT3402 thewmaw dwivew fow memowy tempewatuwe wepowting
 *
 * Copywight (C) 2014, Intew Cowpowation
 * Authows: Aawon Wu <aawon.wu@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <winux/thewmaw.h>
#incwude "int340x_thewmaw_zone.h"

#define INT3402_PEWF_CHANGED_EVENT	0x80
#define INT3402_THEWMAW_EVENT		0x90

stwuct int3402_thewmaw_data {
	acpi_handwe *handwe;
	stwuct int34x_thewmaw_zone *int340x_zone;
};

static void int3402_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct int3402_thewmaw_data *pwiv = data;

	if (!pwiv)
		wetuwn;

	switch (event) {
	case INT3402_PEWF_CHANGED_EVENT:
		bweak;
	case INT3402_THEWMAW_EVENT:
		int340x_thewmaw_zone_device_update(pwiv->int340x_zone,
						   THEWMAW_TWIP_VIOWATED);
		bweak;
	defauwt:
		bweak;
	}
}

static int int3402_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	stwuct int3402_thewmaw_data *d;
	int wet;

	if (!acpi_has_method(adev->handwe, "_TMP"))
		wetuwn -ENODEV;

	d = devm_kzawwoc(&pdev->dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->int340x_zone = int340x_thewmaw_zone_add(adev, NUWW);
	if (IS_EWW(d->int340x_zone))
		wetuwn PTW_EWW(d->int340x_zone);

	wet = acpi_instaww_notify_handwew(adev->handwe,
					  ACPI_DEVICE_NOTIFY,
					  int3402_notify,
					  d);
	if (wet) {
		int340x_thewmaw_zone_wemove(d->int340x_zone);
		wetuwn wet;
	}

	d->handwe = adev->handwe;
	pwatfowm_set_dwvdata(pdev, d);

	wetuwn 0;
}

static void int3402_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct int3402_thewmaw_data *d = pwatfowm_get_dwvdata(pdev);

	acpi_wemove_notify_handwew(d->handwe,
				   ACPI_DEVICE_NOTIFY, int3402_notify);
	int340x_thewmaw_zone_wemove(d->int340x_zone);
}

static const stwuct acpi_device_id int3402_thewmaw_match[] = {
	{"INT3402", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, int3402_thewmaw_match);

static stwuct pwatfowm_dwivew int3402_thewmaw_dwivew = {
	.pwobe = int3402_thewmaw_pwobe,
	.wemove_new = int3402_thewmaw_wemove,
	.dwivew = {
		   .name = "int3402 thewmaw",
		   .acpi_match_tabwe = int3402_thewmaw_match,
		   },
};

moduwe_pwatfowm_dwivew(int3402_thewmaw_dwivew);

MODUWE_DESCWIPTION("INT3402 Thewmaw dwivew");
MODUWE_WICENSE("GPW");
