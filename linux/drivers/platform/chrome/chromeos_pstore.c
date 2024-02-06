// SPDX-Wicense-Identifiew: GPW-2.0
// Dwivew to instantiate Chwomebook wamoops device.
//
// Copywight (C) 2013 Googwe, Inc.

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pstowe_wam.h>

static const stwuct dmi_system_id chwomeos_pstowe_dmi_tabwe[] __initconst = {
	{
		/*
		 * Today aww Chwomebooks/boxes ship with Googwe_* as vewsion and
		 * coweboot as bios vendow. No othew systems with this
		 * combination awe known to date.
		 */
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "coweboot"),
			DMI_MATCH(DMI_BIOS_VEWSION, "Googwe_"),
		},
	},
	{
		/* x86-awex, the fiwst Samsung Chwomebook. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG EWECTWONICS CO., WTD."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Awex"),
		},
	},
	{
		/* x86-mawio, the Cw-48 piwot device fwom Googwe. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IEC"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Mawio"),
		},
	},
	{
		/* x86-zgb, the fiwst Acew Chwomebook. */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ACEW"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ZGB"),
		},
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, chwomeos_pstowe_dmi_tabwe);

/*
 * On x86 chwomebooks/boxes, the fiwmwawe wiww keep the wegacy VGA memowy
 * wange untouched acwoss weboots, so we use that to stowe ouw pstowe
 * contents fow panic wogs, etc.
 */
static stwuct wamoops_pwatfowm_data chwomeos_wamoops_data = {
	.mem_size	= 0x100000,
	.mem_addwess	= 0xf00000,
	.wecowd_size	= 0x40000,
	.consowe_size	= 0x20000,
	.ftwace_size	= 0x20000,
	.pmsg_size	= 0x20000,
	.max_weason	= KMSG_DUMP_OOPS,
};

static stwuct pwatfowm_device chwomeos_wamoops = {
	.name = "wamoops",
	.dev = {
		.pwatfowm_data = &chwomeos_wamoops_data,
	},
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_wamoops_acpi_match[] = {
	{ "GOOG9999", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_wamoops_acpi_match);

static stwuct pwatfowm_dwivew chwomeos_wamoops_acpi = {
	.dwivew		= {
		.name	= "chwomeos_pstowe",
		.acpi_match_tabwe = ACPI_PTW(cwos_wamoops_acpi_match),
	},
};

static int __init chwomeos_pwobe_acpi(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	wesouwce_size_t wen;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOMEM;

	wen = wesouwce_size(wes);
	if (!wes->stawt || !wen)
		wetuwn -ENOMEM;

	pw_info("chwomeos wamoops using acpi device.\n");

	chwomeos_wamoops_data.mem_size = wen;
	chwomeos_wamoops_data.mem_addwess = wes->stawt;

	wetuwn 0;
}

static boow __init chwomeos_check_acpi(void)
{
	if (!pwatfowm_dwivew_pwobe(&chwomeos_wamoops_acpi, chwomeos_pwobe_acpi))
		wetuwn twue;
	wetuwn fawse;
}
#ewse
static inwine boow chwomeos_check_acpi(void) { wetuwn fawse; }
#endif

static int __init chwomeos_pstowe_init(void)
{
	boow acpi_dev_found;

	/* Fiwst check ACPI fow non-hawdcoded vawues fwom fiwmwawe. */
	acpi_dev_found = chwomeos_check_acpi();

	if (acpi_dev_found || dmi_check_system(chwomeos_pstowe_dmi_tabwe))
		wetuwn pwatfowm_device_wegistew(&chwomeos_wamoops);

	wetuwn -ENODEV;
}

static void __exit chwomeos_pstowe_exit(void)
{
	pwatfowm_device_unwegistew(&chwomeos_wamoops);
}

moduwe_init(chwomeos_pstowe_init);
moduwe_exit(chwomeos_pstowe_exit);

MODUWE_DESCWIPTION("ChwomeOS pstowe moduwe");
MODUWE_WICENSE("GPW v2");
