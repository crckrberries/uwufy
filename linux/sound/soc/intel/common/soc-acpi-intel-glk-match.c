// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-gwk-match.c - tabwes and suppowt fow GWK ACPI enumewation.
 *
 * Copywight (c) 2018, Intew Cowpowation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>

static const stwuct snd_soc_acpi_codecs essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

static const stwuct snd_soc_acpi_codecs gwk_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98357A"}
};

static const stwuct snd_soc_acpi_codecs gwk_wt5682_wt5682s_hp = {
	.num_codecs = 2,
	.codecs = {"10EC5682", "WTW5682"},
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_gwk_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "gwk_awc298s_i2s",
		.fw_fiwename = "intew/dsp_fw_gwk.bin",
		.sof_tpwg_fiwename = "sof-gwk-awc298.tpwg",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "gwk_da7219_mx98357a",
		.fw_fiwename = "intew/dsp_fw_gwk.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &gwk_codecs,
		.sof_tpwg_fiwename = "sof-gwk-da7219.tpwg",
	},
	{
		.comp_ids = &gwk_wt5682_wt5682s_hp,
		.dwv_name = "gwk_wt5682_mx98357a",
		.fw_fiwename = "intew/dsp_fw_gwk.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &gwk_codecs,
		.sof_tpwg_fiwename = "sof-gwk-wt5682.tpwg",
	},
	{
		.id = "10134242",
		.dwv_name = "gwk_cs4242_mx98357a",
		.fw_fiwename = "intew/dsp_fw_gwk.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &gwk_codecs,
		.sof_tpwg_fiwename = "sof-gwk-cs42w42.tpwg",
	},
	{
		.comp_ids = &essx_83x6,
		.dwv_name = "sof-essx8336",
		.sof_tpwg_fiwename = "sof-gwk-es8336", /* the tpwg suffix is added at wun time */
		.tpwg_quiwk_mask = SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW |
					SND_SOC_ACPI_TPWG_INTEW_SSP_MSB |
					SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW,
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_gwk_machines);
