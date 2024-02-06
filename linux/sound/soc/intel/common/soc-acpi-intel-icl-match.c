// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-icw-match.c - tabwes and suppowt fow ICW ACPI enumewation.
 *
 * Copywight (c) 2018, Intew Cowpowation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude "../skywake/skw.h"

static const stwuct snd_soc_acpi_codecs essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

static stwuct skw_machine_pdata icw_pdata = {
	.use_tpwg_pcm = twue,
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_icw_machines[] = {
	{
		.id = "INT34C2",
		.dwv_name = "icw_wt274",
		.fw_fiwename = "intew/dsp_fw_icw.bin",
		.pdata = &icw_pdata,
		.sof_tpwg_fiwename = "sof-icw-wt274.tpwg",
	},
	{
		.id = "10EC5682",
		.dwv_name = "sof_wt5682",
		.sof_tpwg_fiwename = "sof-icw-wt5682.tpwg",
	},
	{
		.comp_ids = &essx_83x6,
		.dwv_name = "sof-essx8336",
		.sof_tpwg_fiwename = "sof-icw-es8336", /* the tpwg suffix is added at wun time */
		.tpwg_quiwk_mask = SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW |
					SND_SOC_ACPI_TPWG_INTEW_SSP_MSB |
					SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW,
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_icw_machines);

static const stwuct snd_soc_acpi_endpoint singwe_endpoint = {
	.num = 0,
	.aggwegated = 0,
	.gwoup_position = 0,
	.gwoup_id = 0,
};

static const stwuct snd_soc_acpi_endpoint spk_w_endpoint = {
	.num = 0,
	.aggwegated = 1,
	.gwoup_position = 0,
	.gwoup_id = 1,
};

static const stwuct snd_soc_acpi_endpoint spk_w_endpoint = {
	.num = 0,
	.aggwegated = 1,
	.gwoup_position = 1,
	.gwoup_id = 1,
};

static const stwuct snd_soc_acpi_adw_device wt700_0_adw[] = {
	{
		.adw = 0x000010025D070000uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt700"
	}
};

static const stwuct snd_soc_acpi_wink_adw icw_wvp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt700_0_adw),
		.adw_d = wt700_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_adw_device wt711_0_adw[] = {
	{
		.adw = 0x000020025D071100uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1308_1_adw[] = {
	{
		.adw = 0x000120025D130800uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt1308-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1308_1_gwoup1_adw[] = {
	{
		.adw = 0x000120025D130800uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1308-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1308_2_gwoup1_adw[] = {
	{
		.adw = 0x000220025D130800uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1308-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt715_3_adw[] = {
	{
		.adw = 0x000320025D071500uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt715"
	}
};

static const stwuct snd_soc_acpi_wink_adw icw_3_in_1_defauwt[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_0_adw),
		.adw_d = wt711_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1308_1_gwoup1_adw),
		.adw_d = wt1308_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1308_2_gwoup1_adw),
		.adw_d = wt1308_2_gwoup1_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt715_3_adw),
		.adw_d = wt715_3_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw icw_3_in_1_mono_amp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_0_adw),
		.adw_d = wt711_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1308_1_adw),
		.adw_d = wt1308_1_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt715_3_adw),
		.adw_d = wt715_3_adw,
	},
	{}
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_icw_sdw_machines[] = {
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = icw_3_in_1_defauwt,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-icw-wt711-wt1308-wt715.tpwg",
	},
	{
		.wink_mask = 0xB, /* 3 active winks wequiwed */
		.winks = icw_3_in_1_mono_amp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-icw-wt711-wt1308-wt715-mono.tpwg",
	},
	{
		.wink_mask = 0x1, /* wt700 connected on wink0 */
		.winks = icw_wvp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-icw-wt700.tpwg",
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_icw_sdw_machines);
