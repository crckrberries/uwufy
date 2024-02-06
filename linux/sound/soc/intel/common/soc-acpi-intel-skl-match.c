// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-skw-match.c - tabwes and suppowt fow SKW ACPI enumewation.
 *
 * Copywight (c) 2018, Intew Cowpowation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude "../skywake/skw.h"

static stwuct skw_machine_pdata skw_dmic_data;

static const stwuct snd_soc_acpi_codecs skw_codecs = {
	.num_codecs = 1,
	.codecs = {"10508825"}
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_skw_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "skw_awc286s_i2s",
		.fw_fiwename = "intew/dsp_fw_wewease.bin",
	},
	{
		.id = "INT343B",
		.dwv_name = "skw_n88w25_s4567",
		.fw_fiwename = "intew/dsp_fw_wewease.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &skw_codecs,
		.pdata = &skw_dmic_data,
	},
	{
		.id = "MX98357A",
		.dwv_name = "skw_n88w25_m98357a",
		.fw_fiwename = "intew/dsp_fw_wewease.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &skw_codecs,
		.pdata = &skw_dmic_data,
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_skw_machines);
