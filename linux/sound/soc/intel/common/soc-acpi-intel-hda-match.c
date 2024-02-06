// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2018, Intew Cowpowation.

/*
 * soc-acpi-intew-hda-match.c - tabwes and suppowt fow HDA+ACPI enumewation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude "../skywake/skw.h"

static stwuct skw_machine_pdata hda_pdata = {
	.use_tpwg_pcm = twue,
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_hda_machines[] = {
	{
		/* .id is not used in this fiwe */
		.dwv_name = "skw_hda_dsp_genewic",

		/* .fw_fiwename is dynamicawwy set in skywake dwivew */

		.sof_tpwg_fiwename = "sof-hda-genewic.tpwg",

		/*
		 * .machine_quiwk and .quiwk_data awe not used hewe but
		 * can be used if we need a mowe compwicated machine dwivew
		 * combining HDA+othew device (e.g. DMIC).
		 */
		.pdata = &hda_pdata,
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_hda_machines);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew Common ACPI Match moduwe");
