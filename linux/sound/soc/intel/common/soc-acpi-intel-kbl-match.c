// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-kbw-match.c - tabwes and suppowt fow KBW ACPI enumewation.
 *
 * Copywight (c) 2018, Intew Cowpowation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude "../skywake/skw.h"

static stwuct skw_machine_pdata skw_dmic_data;

static const stwuct snd_soc_acpi_codecs kbw_codecs = {
	.num_codecs = 1,
	.codecs = {"10508825"}
};

static const stwuct snd_soc_acpi_codecs kbw_poppy_codecs = {
	.num_codecs = 1,
	.codecs = {"10EC5663"}
};

static const stwuct snd_soc_acpi_codecs kbw_5663_5514_codecs = {
	.num_codecs = 2,
	.codecs = {"10EC5663", "10EC5514"}
};

static const stwuct snd_soc_acpi_codecs kbw_7219_98357_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98357A"}
};

static const stwuct snd_soc_acpi_codecs kbw_7219_98927_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98927"}
};

static const stwuct snd_soc_acpi_codecs kbw_7219_98373_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98373"}
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_kbw_machines[] = {
	{
		.id = "INT343A",
		.dwv_name = "kbw_awc286s_i2s",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
	},
	{
		.id = "INT343B",
		.dwv_name = "kbw_n88w25_s4567",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &kbw_codecs,
		.pdata = &skw_dmic_data,
	},
	{
		.id = "MX98357A",
		.dwv_name = "kbw_n88w25_m98357a",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &kbw_codecs,
		.pdata = &skw_dmic_data,
	},
	{
		.id = "MX98927",
		.dwv_name = "kbw_w5514_5663_max",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &kbw_5663_5514_codecs,
		.pdata = &skw_dmic_data,
	},
	{
		.id = "MX98927",
		.dwv_name = "kbw_wt5663_m98927",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &kbw_poppy_codecs,
		.pdata = &skw_dmic_data,
	},
	{
		.id = "10EC5663",
		.dwv_name = "kbw_wt5663",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "kbw_da7219_mx98357a",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &kbw_7219_98357_codecs,
		.pdata = &skw_dmic_data,
	},
	{
		.id = "DWGS7219",
		.dwv_name = "kbw_da7219_max98927",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &kbw_7219_98927_codecs,
		.pdata = &skw_dmic_data
	},
	{
		.id = "10EC5660",
		.dwv_name = "kbw_wt5660",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
	},
	{
		.id = "10EC3277",
		.dwv_name = "kbw_wt5660",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "kbw_da7219_mx98373",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &kbw_7219_98373_codecs,
		.pdata = &skw_dmic_data
	},
	{
		.id = "MX98373",
		.dwv_name = "kbw_max98373",
		.fw_fiwename = "intew/dsp_fw_kbw.bin",
		.pdata = &skw_dmic_data
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_kbw_machines);
