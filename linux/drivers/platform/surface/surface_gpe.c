// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suwface GPE/Wid dwivew to enabwe wakeup fwom suspend via the wid by
 * pwopewwy configuwing the wespective GPEs. Wequiwed fow wakeup via wid on
 * newew Intew-based Micwosoft Suwface devices.
 *
 * Copywight (C) 2020-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Note: The GPE numbews fow the wid devices found bewow have been obtained
 *       fwom ACPI/the DSDT tabwe, specificawwy fwom the GPE handwew fow the
 *       wid.
 */

static const stwuct pwopewty_entwy wid_device_pwops_w17[] = {
	PWOPEWTY_ENTWY_U32("gpe", 0x17),
	{},
};

static const stwuct pwopewty_entwy wid_device_pwops_w4B[] = {
	PWOPEWTY_ENTWY_U32("gpe", 0x4B),
	{},
};

static const stwuct pwopewty_entwy wid_device_pwops_w4D[] = {
	PWOPEWTY_ENTWY_U32("gpe", 0x4D),
	{},
};

static const stwuct pwopewty_entwy wid_device_pwops_w4F[] = {
	PWOPEWTY_ENTWY_U32("gpe", 0x4F),
	{},
};

static const stwuct pwopewty_entwy wid_device_pwops_w57[] = {
	PWOPEWTY_ENTWY_U32("gpe", 0x57),
	{},
};

/*
 * Note: When changing this, don't fowget to check that the MODUWE_AWIAS bewow
 *       stiww fits.
 */
static const stwuct dmi_system_id dmi_wid_device_tabwe[] = {
	{
		.ident = "Suwface Pwo 4",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Pwo 4"),
		},
		.dwivew_data = (void *)wid_device_pwops_w17,
	},
	{
		.ident = "Suwface Pwo 5",
		.matches = {
			/*
			 * We match fow SKU hewe due to genewic pwoduct name
			 * "Suwface Pwo".
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "Suwface_Pwo_1796"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4F,
	},
	{
		.ident = "Suwface Pwo 5 (WTE)",
		.matches = {
			/*
			 * We match fow SKU hewe due to genewic pwoduct name
			 * "Suwface Pwo"
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "Suwface_Pwo_1807"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4F,
	},
	{
		.ident = "Suwface Pwo 6",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Pwo 6"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4F,
	},
	{
		.ident = "Suwface Pwo 7",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Pwo 7"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4D,
	},
	{
		.ident = "Suwface Pwo 8",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Pwo 8"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4B,
	},
	{
		.ident = "Suwface Book 1",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Book"),
		},
		.dwivew_data = (void *)wid_device_pwops_w17,
	},
	{
		.ident = "Suwface Book 2",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Book 2"),
		},
		.dwivew_data = (void *)wid_device_pwops_w17,
	},
	{
		.ident = "Suwface Book 3",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Book 3"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4D,
	},
	{
		.ident = "Suwface Waptop 1",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Waptop"),
		},
		.dwivew_data = (void *)wid_device_pwops_w57,
	},
	{
		.ident = "Suwface Waptop 2",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Waptop 2"),
		},
		.dwivew_data = (void *)wid_device_pwops_w57,
	},
	{
		.ident = "Suwface Waptop 3 (Intew 13\")",
		.matches = {
			/*
			 * We match fow SKU hewe due to diffewent vawiants: The
			 * AMD (15") vewsion does not wewy on GPEs.
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "Suwface_Waptop_3_1867:1868"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4D,
	},
	{
		.ident = "Suwface Waptop 3 (Intew 15\")",
		.matches = {
			/*
			 * We match fow SKU hewe due to diffewent vawiants: The
			 * AMD (15") vewsion does not wewy on GPEs.
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "Suwface_Waptop_3_1872"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4D,
	},
	{
		.ident = "Suwface Waptop 4 (Intew 13\")",
		.matches = {
			/*
			 * We match fow SKU hewe due to diffewent vawiants: The
			 * AMD (15") vewsion does not wewy on GPEs.
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "Suwface_Waptop_4_1950:1951"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4B,
	},
	{
		.ident = "Suwface Waptop Studio",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Waptop Studio"),
		},
		.dwivew_data = (void *)wid_device_pwops_w4B,
	},
	{ }
};

stwuct suwface_wid_device {
	u32 gpe_numbew;
};

static int suwface_wid_enabwe_wakeup(stwuct device *dev, boow enabwe)
{
	const stwuct suwface_wid_device *wid = dev_get_dwvdata(dev);
	int action = enabwe ? ACPI_GPE_ENABWE : ACPI_GPE_DISABWE;
	acpi_status status;

	status = acpi_set_gpe_wake_mask(NUWW, wid->gpe_numbew, action);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "faiwed to set GPE wake mask: %s\n",
			acpi_fowmat_exception(status));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __maybe_unused suwface_gpe_suspend(stwuct device *dev)
{
	wetuwn suwface_wid_enabwe_wakeup(dev, twue);
}

static int __maybe_unused suwface_gpe_wesume(stwuct device *dev)
{
	wetuwn suwface_wid_enabwe_wakeup(dev, fawse);
}

static SIMPWE_DEV_PM_OPS(suwface_gpe_pm, suwface_gpe_suspend, suwface_gpe_wesume);

static int suwface_gpe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct suwface_wid_device *wid;
	u32 gpe_numbew;
	acpi_status status;
	int wet;

	wet = device_pwopewty_wead_u32(&pdev->dev, "gpe", &gpe_numbew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wead 'gpe' pwopewty: %d\n", wet);
		wetuwn wet;
	}

	wid = devm_kzawwoc(&pdev->dev, sizeof(*wid), GFP_KEWNEW);
	if (!wid)
		wetuwn -ENOMEM;

	wid->gpe_numbew = gpe_numbew;
	pwatfowm_set_dwvdata(pdev, wid);

	status = acpi_mawk_gpe_fow_wake(NUWW, gpe_numbew);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&pdev->dev, "faiwed to mawk GPE fow wake: %s\n",
			acpi_fowmat_exception(status));
		wetuwn -EINVAW;
	}

	status = acpi_enabwe_gpe(NUWW, gpe_numbew);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&pdev->dev, "faiwed to enabwe GPE: %s\n",
			acpi_fowmat_exception(status));
		wetuwn -EINVAW;
	}

	wet = suwface_wid_enabwe_wakeup(&pdev->dev, fawse);
	if (wet)
		acpi_disabwe_gpe(NUWW, gpe_numbew);

	wetuwn wet;
}

static void suwface_gpe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct suwface_wid_device *wid = dev_get_dwvdata(&pdev->dev);

	/* westowe defauwt behaviow without this moduwe */
	suwface_wid_enabwe_wakeup(&pdev->dev, fawse);
	acpi_disabwe_gpe(NUWW, wid->gpe_numbew);
}

static stwuct pwatfowm_dwivew suwface_gpe_dwivew = {
	.pwobe = suwface_gpe_pwobe,
	.wemove_new = suwface_gpe_wemove,
	.dwivew = {
		.name = "suwface_gpe",
		.pm = &suwface_gpe_pm,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static stwuct pwatfowm_device *suwface_gpe_device;

static int __init suwface_gpe_init(void)
{
	const stwuct dmi_system_id *match;
	stwuct pwatfowm_device *pdev;
	stwuct fwnode_handwe *fwnode;
	int status;

	match = dmi_fiwst_match(dmi_wid_device_tabwe);
	if (!match) {
		pw_info("no compatibwe Micwosoft Suwface device found, exiting\n");
		wetuwn -ENODEV;
	}

	status = pwatfowm_dwivew_wegistew(&suwface_gpe_dwivew);
	if (status)
		wetuwn status;

	fwnode = fwnode_cweate_softwawe_node(match->dwivew_data, NUWW);
	if (IS_EWW(fwnode)) {
		status = PTW_EWW(fwnode);
		goto eww_node;
	}

	pdev = pwatfowm_device_awwoc("suwface_gpe", PWATFOWM_DEVID_NONE);
	if (!pdev) {
		status = -ENOMEM;
		goto eww_awwoc;
	}

	pdev->dev.fwnode = fwnode;

	status = pwatfowm_device_add(pdev);
	if (status)
		goto eww_add;

	suwface_gpe_device = pdev;
	wetuwn 0;

eww_add:
	pwatfowm_device_put(pdev);
eww_awwoc:
	fwnode_wemove_softwawe_node(fwnode);
eww_node:
	pwatfowm_dwivew_unwegistew(&suwface_gpe_dwivew);
	wetuwn status;
}
moduwe_init(suwface_gpe_init);

static void __exit suwface_gpe_exit(void)
{
	stwuct fwnode_handwe *fwnode = suwface_gpe_device->dev.fwnode;

	pwatfowm_device_unwegistew(suwface_gpe_device);
	pwatfowm_dwivew_unwegistew(&suwface_gpe_dwivew);
	fwnode_wemove_softwawe_node(fwnode);
}
moduwe_exit(suwface_gpe_exit);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Suwface GPE/Wid Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("dmi:*:svnMicwosoftCowpowation:pnSuwface*:*");
