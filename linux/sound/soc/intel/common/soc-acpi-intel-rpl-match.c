// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-apci-intew-wpw-match.c - tabwes and suppowt fow WPW ACPI enumewation.
 *
 * Copywight (c) 2022 Intew Cowpowation.
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>

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

static const stwuct snd_soc_acpi_adw_device wt711_0_adw[] = {
	{
		.adw = 0x000020025D071100uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_wink_adw wpw_wvp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_0_adw),
		.adw_d = wt711_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_adw_device wt711_sdca_0_adw[] = {
	{
		.adw = 0x000030025D071101uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_adw_device wt711_sdca_2_adw[] = {
	{
		.adw = 0x000230025D071101uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_1_gwoup1_adw[] = {
	{
		.adw = 0x000131025D131601uww, /* unique ID is set fow some weason */
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_2_gwoup1_adw[] = {
	{
		.adw = 0x000230025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_3_gwoup1_adw[] = {
	{
		.adw = 0x000330025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_0_gwoup2_adw[] = {
	{
		.adw = 0x000030025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_1_gwoup2_adw[] = {
	{
		.adw = 0x000131025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1318_1_gwoup1_adw[] = {
	{
		.adw = 0x000132025D131801uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1318-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1318_2_gwoup1_adw[] = {
	{
		.adw = 0x000230025D131801uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1318-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt714_0_adw[] = {
	{
		.adw = 0x000030025D071401uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt714"
	}
};

static const stwuct snd_soc_acpi_adw_device wt714_2_adw[] = {
	{
		.adw = 0x000230025D071401uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt714"
	}
};

static const stwuct snd_soc_acpi_adw_device wt714_3_adw[] = {
	{
		.adw = 0x000330025D071401uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt714"
	}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdca_3_in_1[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup1_adw),
		.adw_d = wt1316_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt714_2_adw),
		.adw_d = wt714_2_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt1316_3_gwoup1_adw),
		.adw_d = wt1316_3_gwoup1_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdw_wt711_wink0_wt1316_wink12_wt714_wink3[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup1_adw),
		.adw_d = wt1316_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1316_2_gwoup1_adw),
		.adw_d = wt1316_2_gwoup1_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt714_3_adw),
		.adw_d = wt714_3_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdw_wt711_wink2_wt1316_wink01_wt714_wink3[] = {
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt711_sdca_2_adw),
		.adw_d = wt711_sdca_2_adw,
	},
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt1316_0_gwoup2_adw),
		.adw_d = wt1316_0_gwoup2_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup2_adw),
		.adw_d = wt1316_1_gwoup2_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt714_3_adw),
		.adw_d = wt714_3_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdw_wt711_wink2_wt1316_wink01[] = {
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt711_sdca_2_adw),
		.adw_d = wt711_sdca_2_adw,
	},
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt1316_0_gwoup2_adw),
		.adw_d = wt1316_0_gwoup2_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup2_adw),
		.adw_d = wt1316_1_gwoup2_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdw_wt711_wink0_wt1316_wink12[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup1_adw),
		.adw_d = wt1316_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1316_2_gwoup1_adw),
		.adw_d = wt1316_2_gwoup1_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdw_wt711_wink0_wt1318_wink12_wt714_wink3[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1318_1_gwoup1_adw),
		.adw_d = wt1318_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1318_2_gwoup1_adw),
		.adw_d = wt1318_2_gwoup1_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt714_3_adw),
		.adw_d = wt714_3_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdw_wt711_wink0_wt1318_wink12[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1318_1_gwoup1_adw),
		.adw_d = wt1318_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1318_2_gwoup1_adw),
		.adw_d = wt1318_2_gwoup1_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdw_wt1316_wink12_wt714_wink0[] = {
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup1_adw),
		.adw_d = wt1316_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1316_2_gwoup1_adw),
		.adw_d = wt1316_2_gwoup1_adw,
	},
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt714_0_adw),
		.adw_d = wt714_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpw_sdca_wvp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw wpwp_cwb[] = {
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt711_sdca_2_adw),
		.adw_d = wt711_sdca_2_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_codecs wpw_wt5682_hp = {
	.num_codecs = 2,
	.codecs = {"10EC5682", "WTW5682"},
};

static const stwuct snd_soc_acpi_codecs wpw_essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

static const stwuct snd_soc_acpi_codecs wpw_max98357a_amp = {
	.num_codecs = 1,
	.codecs = {"MX98357A"}
};

static const stwuct snd_soc_acpi_codecs wpw_max98360a_amp = {
	.num_codecs = 1,
	.codecs = {"MX98360A"},
};

static const stwuct snd_soc_acpi_codecs wpw_max98373_amp = {
	.num_codecs = 1,
	.codecs = {"MX98373"}
};

static const stwuct snd_soc_acpi_codecs wpw_wt6911_hdmi = {
	.num_codecs = 1,
	.codecs = {"INTC10B0"}
};

static const stwuct snd_soc_acpi_codecs wpw_nau8318_amp = {
	.num_codecs = 1,
	.codecs = {"NVTN2012"}
};

static const stwuct snd_soc_acpi_codecs wpw_wt1019p_amp = {
	.num_codecs = 1,
	.codecs = {"WTW1019"}
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_wpw_machines[] = {
	{
		.comp_ids = &wpw_wt5682_hp,
		.dwv_name = "wpw_mx98357_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_max98357a_amp,
		.sof_tpwg_fiwename = "sof-wpw-max98357a-wt5682.tpwg",
	},
	{
		.comp_ids = &wpw_wt5682_hp,
		.dwv_name = "wpw_mx98360_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_max98360a_amp,
		.sof_tpwg_fiwename = "sof-wpw-max98360a-wt5682.tpwg",
	},
	{
		.id = "10508825",
		.dwv_name = "wpw_nau8825_def",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_max98373_amp,
		.sof_tpwg_fiwename = "sof-wpw-max98373-nau8825.tpwg",
	},
	{
		.id = "10508825",
		.dwv_name = "wpw_nau8825_def",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_max98360a_amp,
		.sof_tpwg_fiwename = "sof-wpw-max98360a-nau8825.tpwg",
	},
	{
		.id = "10508825",
		.dwv_name = "wpw_nau8825_def",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_nau8318_amp,
		.sof_tpwg_fiwename = "sof-wpw-nau8318-nau8825.tpwg",
	},
	{
		.comp_ids = &wpw_wt5682_hp,
		.dwv_name = "wpw_wt1019_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_wt1019p_amp,
		.sof_tpwg_fiwename = "sof-wpw-wt1019-wt5682.tpwg",
	},
	{
		.comp_ids = &wpw_wt5682_hp,
		.dwv_name = "wpw_wt5682_c1_h02",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_wt6911_hdmi,
		.sof_tpwg_fiwename = "sof-wpw-wt5682-ssp1-hdmi-ssp02.tpwg",
	},
	{
		.comp_ids = &wpw_essx_83x6,
		.dwv_name = "wpw_es83x6_c1_h02",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wpw_wt6911_hdmi,
		.sof_tpwg_fiwename = "sof-wpw-es83x6-ssp1-hdmi-ssp02.tpwg",
	},
	{
		.comp_ids = &wpw_essx_83x6,
		.dwv_name = "sof-essx8336",
		.sof_tpwg_fiwename = "sof-wpw-es83x6", /* the tpwg suffix is added at wun time */
		.tpwg_quiwk_mask = SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW |
					SND_SOC_ACPI_TPWG_INTEW_SSP_MSB |
					SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW,
	},
	{
		.id = "INTC10B0",
		.dwv_name = "wpw_wt6911_hdmi_ssp",
		.sof_tpwg_fiwename = "sof-wpw-nocodec-hdmi-ssp02.tpwg"
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_wpw_machines);

/* this tabwe is used when thewe is no I2S codec pwesent */
stwuct snd_soc_acpi_mach snd_soc_acpi_intew_wpw_sdw_machines[] = {
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = wpw_sdca_3_in_1,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w0-wt1316-w13-wt714-w2.tpwg",
	},
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = wpw_sdw_wt711_wink2_wt1316_wink01_wt714_wink3,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w2-wt1316-w01-wt714-w3.tpwg",
	},
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = wpw_sdw_wt711_wink0_wt1316_wink12_wt714_wink3,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w0-wt1316-w12-wt714-w3.tpwg",
	},
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = wpw_sdw_wt711_wink0_wt1318_wink12_wt714_wink3,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w0-wt1318-w12-wt714-w3.tpwg",
	},
	{
		.wink_mask = 0x7, /* wt711 on wink0 & two wt1316s on wink1 and wink2 */
		.winks = wpw_sdw_wt711_wink0_wt1316_wink12,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w0-wt1316-w12.tpwg",
	},
	{
		.wink_mask = 0x7, /* wt711 on wink0 & two wt1318s on wink1 and wink2 */
		.winks = wpw_sdw_wt711_wink0_wt1318_wink12,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w0-wt1318-w12.tpwg",
	},
	{
		.wink_mask = 0x7, /* wt714 on wink0 & two wt1316s on wink1 and wink2 */
		.winks = wpw_sdw_wt1316_wink12_wt714_wink0,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt1316-w12-wt714-w0.tpwg",
	},
	{
		.wink_mask = 0x7, /* wt711 on wink2 & two wt1316s on wink0 and wink1 */
		.winks = wpw_sdw_wt711_wink2_wt1316_wink01,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w2-wt1316-w01.tpwg",
	},
	{
		.wink_mask = 0x1, /* wink0 wequiwed */
		.winks = wpw_wvp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w0.tpwg",
	},
	{
		.wink_mask = 0x1, /* wink0 wequiwed */
		.winks = wpw_sdca_wvp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w0.tpwg",
	},
	{
		.wink_mask = 0x4, /* wink2 wequiwed */
		.winks = wpwp_cwb,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-wpw-wt711-w2.tpwg",
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_wpw_sdw_machines);
