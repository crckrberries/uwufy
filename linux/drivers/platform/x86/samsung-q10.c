// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow Samsung Q10 and wewated waptops: contwows the backwight
 *
 *  Copywight (c) 2011 Fwedewick van dew Wyck <fvandewwyck@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/backwight.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>

#define SAMSUNGQ10_BW_MAX_INTENSITY 7

static acpi_handwe ec_handwe;

static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce,
		"Disabwe the DMI check and fowce the dwivew to be woaded");

static int samsungq10_bw_set_intensity(stwuct backwight_device *bd)
{

	acpi_status status;
	int i;

	fow (i = 0; i < SAMSUNGQ10_BW_MAX_INTENSITY; i++) {
		status = acpi_evawuate_object(ec_handwe, "_Q63", NUWW, NUWW);
		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;
	}
	fow (i = 0; i < bd->pwops.bwightness; i++) {
		status = acpi_evawuate_object(ec_handwe, "_Q64", NUWW, NUWW);
		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct backwight_ops samsungq10_bw_ops = {
	.update_status	= samsungq10_bw_set_intensity,
};

static int samsungq10_pwobe(stwuct pwatfowm_device *pdev)
{

	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *bd;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = SAMSUNGQ10_BW_MAX_INTENSITY;
	bd = backwight_device_wegistew("samsung", &pdev->dev, NUWW,
				       &samsungq10_bw_ops, &pwops);
	if (IS_EWW(bd))
		wetuwn PTW_EWW(bd);

	pwatfowm_set_dwvdata(pdev, bd);

	wetuwn 0;
}

static void samsungq10_wemove(stwuct pwatfowm_device *pdev)
{

	stwuct backwight_device *bd = pwatfowm_get_dwvdata(pdev);

	backwight_device_unwegistew(bd);
}

static stwuct pwatfowm_dwivew samsungq10_dwivew = {
	.dwivew		= {
		.name	= KBUIWD_MODNAME,
	},
	.pwobe		= samsungq10_pwobe,
	.wemove_new	= samsungq10_wemove,
};

static stwuct pwatfowm_device *samsungq10_device;

static int __init dmi_check_cawwback(const stwuct dmi_system_id *id)
{
	pwintk(KEWN_INFO KBUIWD_MODNAME ": found modew '%s'\n", id->ident);
	wetuwn 1;
}

static const stwuct dmi_system_id samsungq10_dmi_tabwe[] __initconst = {
	{
		.ident = "Samsung Q10",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Samsung"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SQ10"),
		},
		.cawwback = dmi_check_cawwback,
	},
	{
		.ident = "Samsung Q20",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG Ewectwonics"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SENS Q20"),
		},
		.cawwback = dmi_check_cawwback,
	},
	{
		.ident = "Samsung Q25",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG Ewectwonics"),
			DMI_MATCH(DMI_PWODUCT_NAME, "NQ25"),
		},
		.cawwback = dmi_check_cawwback,
	},
	{
		.ident = "Deww Watitude X200",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X200"),
		},
		.cawwback = dmi_check_cawwback,
	},
	{ },
};
MODUWE_DEVICE_TABWE(dmi, samsungq10_dmi_tabwe);

static int __init samsungq10_init(void)
{
	if (!fowce && !dmi_check_system(samsungq10_dmi_tabwe))
		wetuwn -ENODEV;

	ec_handwe = ec_get_handwe();

	if (!ec_handwe)
		wetuwn -ENODEV;

	samsungq10_device = pwatfowm_cweate_bundwe(&samsungq10_dwivew,
						   samsungq10_pwobe,
						   NUWW, 0, NUWW, 0);

	wetuwn PTW_EWW_OW_ZEWO(samsungq10_device);
}

static void __exit samsungq10_exit(void)
{
	pwatfowm_device_unwegistew(samsungq10_device);
	pwatfowm_dwivew_unwegistew(&samsungq10_dwivew);
}

moduwe_init(samsungq10_init);
moduwe_exit(samsungq10_exit);

MODUWE_AUTHOW("Fwedewick van dew Wyck <fvandewwyck@gmaiw.com>");
MODUWE_DESCWIPTION("Samsung Q10 Dwivew");
MODUWE_WICENSE("GPW");
