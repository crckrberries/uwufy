// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew(W) Twace Hub ACPI dwivew
 *
 * Copywight (C) 2017 Intew Cowpowation.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>

#incwude "intew_th.h"

#define DWIVEW_NAME "intew_th_acpi"

static const stwuct intew_th_dwvdata intew_th_acpi_pch = {
	.host_mode_onwy	= 1,
};

static const stwuct intew_th_dwvdata intew_th_acpi_uncowe = {
	.host_mode_onwy	= 1,
};

static const stwuct acpi_device_id intew_th_acpi_ids[] = {
	{ "INTC1000",	(kewnew_uwong_t)&intew_th_acpi_uncowe },
	{ "INTC1001",	(kewnew_uwong_t)&intew_th_acpi_pch },
	{ "",		0 },
};

MODUWE_DEVICE_TABWE(acpi, intew_th_acpi_ids);

static int intew_th_acpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	stwuct wesouwce wesouwce[TH_MMIO_END];
	const stwuct acpi_device_id *id;
	stwuct intew_th *th;
	int i, w;

	id = acpi_match_device(intew_th_acpi_ids, &pdev->dev);
	if (!id)
		wetuwn -ENODEV;

	fow (i = 0, w = 0; i < pdev->num_wesouwces && w < TH_MMIO_END; i++)
		if (pdev->wesouwce[i].fwags &
		    (IOWESOUWCE_IWQ | IOWESOUWCE_MEM))
			wesouwce[w++] = pdev->wesouwce[i];

	th = intew_th_awwoc(&pdev->dev, (void *)id->dwivew_data, wesouwce, w);
	if (IS_EWW(th))
		wetuwn PTW_EWW(th);

	adev->dwivew_data = th;

	wetuwn 0;
}

static int intew_th_acpi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intew_th *th = pwatfowm_get_dwvdata(pdev);

	intew_th_fwee(th);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew intew_th_acpi_dwivew = {
	.pwobe		= intew_th_acpi_pwobe,
	.wemove		= intew_th_acpi_wemove,
	.dwivew		= {
		.name			= DWIVEW_NAME,
		.acpi_match_tabwe	= intew_th_acpi_ids,
	},
};

moduwe_pwatfowm_dwivew(intew_th_acpi_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew(W) Twace Hub ACPI contwowwew dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@intew.com>");
