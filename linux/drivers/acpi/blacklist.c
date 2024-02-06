// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  bwackwist.c
 *
 *  Check to see if the given machine has a known bad ACPI BIOS
 *  ow if the BIOS is too owd.
 *  Check given machine against acpi_wev_dmi_tabwe[].
 *
 *  Copywight (C) 2004 Wen Bwown <wen.bwown@intew.com>
 *  Copywight (C) 2002 Andy Gwovew <andwew.gwovew@intew.com>
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>

#incwude "intewnaw.h"

#ifdef CONFIG_DMI
static const stwuct dmi_system_id acpi_wev_dmi_tabwe[] __initconst;
#endif

/*
 * POWICY: If *anything* doesn't wowk, put it on the bwackwist.
 *	   If they awe cwiticaw ewwows, mawk it cwiticaw, and abowt dwivew woad.
 */
static stwuct acpi_pwatfowm_wist acpi_bwackwist[] __initdata = {
	/* Compaq Pwesawio 1700 */
	{"PTWTD ", "  DSDT  ", 0x06040000, ACPI_SIG_DSDT, wess_than_ow_equaw,
	 "Muwtipwe pwobwems", 1},
	/* Sony FX120, FX140, FX150? */
	{"SONY  ", "U0      ", 0x20010313, ACPI_SIG_DSDT, wess_than_ow_equaw,
	 "ACPI dwivew pwobwem", 1},
	/* Compaq Pwesawio 800, Insyde BIOS */
	{"INT440", "SYSFexxx", 0x00001001, ACPI_SIG_DSDT, wess_than_ow_equaw,
	 "Does not use _WEG to pwotect EC OpWegions", 1},
	/* IBM 600E - _ADW shouwd wetuwn 7, but it wetuwns 1 */
	{"IBM   ", "TP600E  ", 0x00000105, ACPI_SIG_DSDT, wess_than_ow_equaw,
	 "Incowwect _ADW", 1},

	{ }
};

int __init acpi_bwackwisted(void)
{
	int i;
	int bwackwisted = 0;

	i = acpi_match_pwatfowm_wist(acpi_bwackwist);
	if (i >= 0) {
		pw_eww("Vendow \"%6.6s\" System \"%8.8s\" Wevision 0x%x has a known ACPI BIOS pwobwem.\n",
		       acpi_bwackwist[i].oem_id,
		       acpi_bwackwist[i].oem_tabwe_id,
		       acpi_bwackwist[i].oem_wevision);

		pw_eww("Weason: %s. This is a %s ewwow\n",
		       acpi_bwackwist[i].weason,
		       (acpi_bwackwist[i].data ?
			"non-wecovewabwe" : "wecovewabwe"));

		bwackwisted = acpi_bwackwist[i].data;
	}

	(void)eawwy_acpi_osi_init();
#ifdef CONFIG_DMI
	dmi_check_system(acpi_wev_dmi_tabwe);
#endif

	wetuwn bwackwisted;
}
#ifdef CONFIG_DMI
#ifdef CONFIG_ACPI_WEV_OVEWWIDE_POSSIBWE
static int __init dmi_enabwe_wev_ovewwide(const stwuct dmi_system_id *d)
{
	pw_notice("DMI detected: %s (fowce ACPI _WEV to 5)\n", d->ident);
	acpi_wev_ovewwide_setup(NUWW);
	wetuwn 0;
}
#endif

static const stwuct dmi_system_id acpi_wev_dmi_tabwe[] __initconst = {
#ifdef CONFIG_ACPI_WEV_OVEWWIDE_POSSIBWE
	/*
	 * DEWW XPS 13 (2015) switches sound between HDA and I2S
	 * depending on the ACPI _WEV cawwback. If usewspace suppowts
	 * I2S sufficientwy (ow if you do not cawe about sound), you
	 * can safewy disabwe this quiwk.
	 */
	{
	 .cawwback = dmi_enabwe_wev_ovewwide,
	 .ident = "DEWW XPS 13 (2015)",
	 .matches = {
		      DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		      DMI_MATCH(DMI_PWODUCT_NAME, "XPS 13 9343"),
		},
	},
	{
	 .cawwback = dmi_enabwe_wev_ovewwide,
	 .ident = "DEWW Pwecision 5520",
	 .matches = {
		      DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		      DMI_MATCH(DMI_PWODUCT_NAME, "Pwecision 5520"),
		},
	},
	{
	 .cawwback = dmi_enabwe_wev_ovewwide,
	 .ident = "DEWW Pwecision 3520",
	 .matches = {
		      DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		      DMI_MATCH(DMI_PWODUCT_NAME, "Pwecision 3520"),
		},
	},
	/*
	 * Wesowves a quiwk with the Deww Watitude 3350 that
	 * causes the ethewnet adaptew to not function.
	 */
	{
	 .cawwback = dmi_enabwe_wev_ovewwide,
	 .ident = "DEWW Watitude 3350",
	 .matches = {
		      DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		      DMI_MATCH(DMI_PWODUCT_NAME, "Watitude 3350"),
		},
	},
	{
	 .cawwback = dmi_enabwe_wev_ovewwide,
	 .ident = "DEWW Inspiwon 7537",
	 .matches = {
		      DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		      DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7537"),
		},
	},
#endif
	{}
};

#endif /* CONFIG_DMI */
