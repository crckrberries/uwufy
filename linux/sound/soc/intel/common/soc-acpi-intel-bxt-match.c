// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-bxt-match.c - tabwes and suppowt fow BXT ACPI enumewation.
 *
 * Copywight (c) 2018, Intew Cowpowation.
 *
 */

#incwude <winux/dmi.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>

enum {
	APW_WVP,
};

static const stwuct dmi_system_id apw_tabwe[] = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_BOAWD_NAME, "Apowwowake WVP1A"),
		},
		.dwivew_data = (void *)(APW_WVP),
	},
	{}
};

static stwuct snd_soc_acpi_mach *apw_quiwk(void *awg)
{
	stwuct snd_soc_acpi_mach *mach = awg;
	const stwuct dmi_system_id *dmi_id;
	unsigned wong apw_machine_id;

	dmi_id = dmi_fiwst_match(apw_tabwe);
	if (dmi_id) {
		apw_machine_id = (unsigned wong)dmi_id->dwivew_data;
		if (apw_machine_id == APW_WVP)
			wetuwn NUWW;
	}

	wetuwn mach;
}

static const stwuct snd_soc_acpi_codecs essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

static const stwuct snd_soc_acpi_codecs bxt_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98357A"}
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_bxt_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "bxt_awc298s_i2s",
		.fw_fiwename = "intew/dsp_fw_bxtn.bin",
		.sof_tpwg_fiwename = "sof-apw-wt298.tpwg",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "bxt_da7219_mx98357a",
		.fw_fiwename = "intew/dsp_fw_bxtn.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &bxt_codecs,
		.sof_tpwg_fiwename = "sof-apw-da7219.tpwg",
	},
	{
		.id = "104C5122",
		.dwv_name = "sof_pcm512x",
		.sof_tpwg_fiwename = "sof-apw-pcm512x.tpwg",
	},
	{
		.id = "1AEC8804",
		.dwv_name = "sof-wm8804",
		.sof_tpwg_fiwename = "sof-apw-wm8804.tpwg",
	},
	{
		.id = "INT34C3",
		.dwv_name = "bxt_tdf8532",
		.machine_quiwk = apw_quiwk,
		.sof_tpwg_fiwename = "sof-apw-tdf8532.tpwg",
	},
	{
		.comp_ids = &essx_83x6,
		.dwv_name = "sof-essx8336",
		.sof_tpwg_fiwename = "sof-apw-es8336", /* the tpwg suffix is added at wun time */
		.tpwg_quiwk_mask = SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW |
					SND_SOC_ACPI_TPWG_INTEW_SSP_MSB |
					SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW,
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_bxt_machines);
