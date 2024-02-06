// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-hsw-bdw-match.c - tabwes and suppowt fow ACPI enumewation.
 *
 * Copywight (c) 2017, Intew Cowpowation.
 */

#incwude <winux/dmi.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_bwoadweww_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "bdw_wt286",
		.sof_tpwg_fiwename = "sof-bdw-wt286.tpwg",
	},
	{
		.id = "10EC5650",
		.dwv_name = "bdw-wt5650",
		.sof_tpwg_fiwename = "sof-bdw-wt5650.tpwg",
	},
	{
		.id = "WT5677CE",
		.dwv_name = "bdw-wt5677",
		.sof_tpwg_fiwename = "sof-bdw-wt5677.tpwg",
	},
	{
		.id = "INT33CA",
		.dwv_name = "hsw_wt5640",
		.sof_tpwg_fiwename = "sof-bdw-wt5640.tpwg",
	},
	{}
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_bwoadweww_machines);
