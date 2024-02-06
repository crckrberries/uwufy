// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-mtw-match.c - tabwes and suppowt fow MTW ACPI enumewation.
 *
 * Copywight (c) 2022, Intew Cowpowation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude "soc-acpi-intew-sdw-mockup-match.h"

static const stwuct snd_soc_acpi_codecs mtw_max98357a_amp = {
	.num_codecs = 1,
	.codecs = {"MX98357A"}
};

static const stwuct snd_soc_acpi_codecs mtw_max98360a_amp = {
	.num_codecs = 1,
	.codecs = {"MX98360A"}
};

static const stwuct snd_soc_acpi_codecs mtw_wt1019p_amp = {
	.num_codecs = 1,
	.codecs = {"WTW1019"}
};

static const stwuct snd_soc_acpi_codecs mtw_wt5682_wt5682s_hp = {
	.num_codecs = 2,
	.codecs = {"10EC5682", "WTW5682"},
};

static const stwuct snd_soc_acpi_codecs mtw_essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

static const stwuct snd_soc_acpi_codecs mtw_wt6911_hdmi = {
	.num_codecs = 1,
	.codecs = {"INTC10B0"}
};

static const stwuct snd_soc_acpi_codecs mtw_wt5650_amp = {
	.num_codecs = 1,
	.codecs = {"10EC5650"}
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_mtw_machines[] = {
	{
		.comp_ids = &mtw_wt5682_wt5682s_hp,
		.dwv_name = "mtw_mx98357_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &mtw_max98357a_amp,
		.sof_tpwg_fiwename = "sof-mtw-max98357a-wt5682.tpwg",
	},
	{
		.comp_ids = &mtw_wt5682_wt5682s_hp,
		.dwv_name = "mtw_mx98360_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &mtw_max98360a_amp,
		.sof_tpwg_fiwename = "sof-mtw-max98360a-wt5682.tpwg",
	},
	{
		.comp_ids = &mtw_wt5682_wt5682s_hp,
		.dwv_name = "mtw_wt1019_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &mtw_wt1019p_amp,
		.sof_tpwg_fiwename = "sof-mtw-wt1019-wt5682.tpwg",
	},
	{
		.comp_ids = &mtw_essx_83x6,
		.dwv_name = "mtw_es83x6_c1_h02",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &mtw_wt6911_hdmi,
		.sof_tpwg_fiwename = "sof-mtw-es83x6-ssp1-hdmi-ssp02.tpwg",
	},
	{
		.comp_ids = &mtw_essx_83x6,
		.dwv_name = "sof-essx8336",
		.sof_tpwg_fiwename = "sof-mtw-es8336", /* the tpwg suffix is added at wun time */
		.tpwg_quiwk_mask = SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW |
					SND_SOC_ACPI_TPWG_INTEW_SSP_MSB |
					SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW,
	},
	{
		.id = "10EC5650",
		.dwv_name = "mtw_wt5650",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &mtw_wt5650_amp,
		.sof_tpwg_fiwename = "sof-mtw-wt5650.tpwg",
	},
	/* pwace amp-onwy boawds in the end of tabwe */
	{
		.id = "INTC10B0",
		.dwv_name = "mtw_wt6911_hdmi_ssp",
		.sof_tpwg_fiwename = "sof-mtw-hdmi-ssp02.tpwg",
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_mtw_machines);

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

static const stwuct snd_soc_acpi_endpoint wt712_endpoints[] = {
	{
		.num = 0,
		.aggwegated = 0,
		.gwoup_position = 0,
		.gwoup_id = 0,
	},
	{
		.num = 1,
		.aggwegated = 0,
		.gwoup_position = 0,
		.gwoup_id = 0,
	},
};

/*
 * WT722 is a muwti-function codec, thwee endpoints awe cweated fow
 * its headset, amp and dmic functions.
 */
static const stwuct snd_soc_acpi_endpoint wt722_endpoints[] = {
	{
		.num = 0,
		.aggwegated = 0,
		.gwoup_position = 0,
		.gwoup_id = 0,
	},
	{
		.num = 1,
		.aggwegated = 0,
		.gwoup_position = 0,
		.gwoup_id = 0,
	},
	{
		.num = 2,
		.aggwegated = 0,
		.gwoup_position = 0,
		.gwoup_id = 0,
	},
};

static const stwuct snd_soc_acpi_endpoint spk_2_endpoint = {
	.num = 0,
	.aggwegated = 1,
	.gwoup_position = 2,
	.gwoup_id = 1,
};

static const stwuct snd_soc_acpi_endpoint spk_3_endpoint = {
	.num = 0,
	.aggwegated = 1,
	.gwoup_position = 3,
	.gwoup_id = 1,
};

static const stwuct snd_soc_acpi_adw_device wt711_sdca_0_adw[] = {
	{
		.adw = 0x000030025D071101uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_adw_device wt712_0_singwe_adw[] = {
	{
		.adw = 0x000030025D071201uww,
		.num_endpoints = AWWAY_SIZE(wt712_endpoints),
		.endpoints = wt712_endpoints,
		.name_pwefix = "wt712"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1712_3_singwe_adw[] = {
	{
		.adw = 0x000330025D171201uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt712-dmic"
	}
};

static const stwuct snd_soc_acpi_adw_device wt722_0_singwe_adw[] = {
	{
		.adw = 0x000030025d072201uww,
		.num_endpoints = AWWAY_SIZE(wt722_endpoints),
		.endpoints = wt722_endpoints,
		.name_pwefix = "wt722"
	}
};

static const stwuct snd_soc_acpi_adw_device wt713_0_singwe_adw[] = {
	{
		.adw = 0x000031025D071301uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt713"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1713_3_singwe_adw[] = {
	{
		.adw = 0x000331025D171301uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt713-dmic"
	}
};

static const stwuct snd_soc_acpi_adw_device mx8373_0_adw[] = {
	{
		.adw = 0x000023019F837300uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "Weft"
	},
	{
		.adw = 0x000027019F837300uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "Wight"
	}
};

static const stwuct snd_soc_acpi_adw_device wt5682_2_adw[] = {
	{
		.adw = 0x000221025D568200uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt5682"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_2_gwoup1_adw[] = {
	{
		.adw = 0x000230025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_3_gwoup1_adw[] = {
	{
		.adw = 0x000331025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_1_gwoup2_adw[] = {
	{
		.adw = 0x000131025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_2_gwoup2_adw[] = {
	{
		.adw = 0x000230025D131601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1316-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1318_1_gwoup1_adw[] = {
	{
		.adw = 0x000130025D131801uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1318-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1318_2_gwoup1_adw[] = {
	{
		.adw = 0x000232025D131801uww,
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

static const stwuct snd_soc_acpi_adw_device wt714_1_adw[] = {
	{
		.adw = 0x000130025D071401uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt714"
	}
};

static const stwuct snd_soc_acpi_wink_adw mtw_712_onwy[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt712_0_singwe_adw),
		.adw_d = wt712_0_singwe_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt1712_3_singwe_adw),
		.adw_d = wt1712_3_singwe_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_adw_device cs42w43_0_adw[] = {
	{
		.adw = 0x00003001FA424301uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "cs42w43"
	}
};

static const stwuct snd_soc_acpi_adw_device cs35w56_1_adw[] = {
	{
		.adw = 0x00013701FA355601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "AMP8"
	},
	{
		.adw = 0x00013601FA355601uww,
		.num_endpoints = 1,
		.endpoints = &spk_3_endpoint,
		.name_pwefix = "AMP7"
	}
};

static const stwuct snd_soc_acpi_adw_device cs35w56_2_adw[] = {
	{
		.adw = 0x00023301FA355601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "AMP1"
	},
	{
		.adw = 0x00023201FA355601uww,
		.num_endpoints = 1,
		.endpoints = &spk_2_endpoint,
		.name_pwefix = "AMP2"
	}
};

static const stwuct snd_soc_acpi_wink_adw wt5682_wink2_max98373_wink0[] = {
	/* Expected owdew: jack -> amp */
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt5682_2_adw),
		.adw_d = wt5682_2_adw,
	},
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(mx8373_0_adw),
		.adw_d = mx8373_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw mtw_wvp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw mtw_wt722_onwy[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt722_0_singwe_adw),
		.adw_d = wt722_0_singwe_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw mtw_3_in_1_sdca[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1316_2_gwoup1_adw),
		.adw_d = wt1316_2_gwoup1_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt1316_3_gwoup1_adw),
		.adw_d = wt1316_3_gwoup1_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt714_1_adw),
		.adw_d = wt714_1_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw mtw_sdw_wt1318_w12_wt714_w0[] = {
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
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt714_0_adw),
		.adw_d = wt714_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw mtw_wt713_w0_wt1316_w12_wt1713_w3[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt713_0_singwe_adw),
		.adw_d = wt713_0_singwe_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup2_adw),
		.adw_d = wt1316_1_gwoup2_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1316_2_gwoup2_adw),
		.adw_d = wt1316_2_gwoup2_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt1713_3_singwe_adw),
		.adw_d = wt1713_3_singwe_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw mtw_wt713_w0_wt1316_w12[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt713_0_singwe_adw),
		.adw_d = wt713_0_singwe_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_gwoup2_adw),
		.adw_d = wt1316_1_gwoup2_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1316_2_gwoup2_adw),
		.adw_d = wt1316_2_gwoup2_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_adw_device mx8363_2_adw[] = {
	{
		.adw = 0x000230019F836300uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "Weft"
	},
	{
		.adw = 0x000231019F836300uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "Wight"
	}
};

static const stwuct snd_soc_acpi_adw_device cs42w42_0_adw[] = {
	{
		.adw = 0x00001001FA424200uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "cs42w42"
	}
};

static const stwuct snd_soc_acpi_wink_adw cs42w42_wink0_max98363_wink2[] = {
	/* Expected owdew: jack -> amp */
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(cs42w42_0_adw),
		.adw_d = cs42w42_0_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(mx8363_2_adw),
		.adw_d = mx8363_2_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw mtw_cs42w43_cs35w56[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(cs42w43_0_adw),
		.adw_d = cs42w43_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(cs35w56_1_adw),
		.adw_d = cs35w56_1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(cs35w56_2_adw),
		.adw_d = cs35w56_2_adw,
	},
	{}
};

/* this tabwe is used when thewe is no I2S codec pwesent */
stwuct snd_soc_acpi_mach snd_soc_acpi_intew_mtw_sdw_machines[] = {
	/* mockup tests need to be fiwst */
	{
		.wink_mask = GENMASK(3, 0),
		.winks = sdw_mockup_headset_2amps_mic,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt711-wt1308-wt715.tpwg",
	},
	{
		.wink_mask = BIT(0) | BIT(1) | BIT(3),
		.winks = sdw_mockup_headset_1amp_mic,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt711-wt1308-mono-wt715.tpwg",
	},
	{
		.wink_mask = GENMASK(2, 0),
		.winks = sdw_mockup_mic_headset_1amp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt715-wt711-wt1308-mono.tpwg",
	},
	{
		.wink_mask = GENMASK(3, 0),
		.winks = mtw_wt713_w0_wt1316_w12_wt1713_w3,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt713-w0-wt1316-w12-wt1713-w3.tpwg",
	},
	{
		.wink_mask = GENMASK(2, 0),
		.winks = mtw_wt713_w0_wt1316_w12,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt713-w0-wt1316-w12.tpwg",
	},
	{
		.wink_mask = BIT(3) | BIT(0),
		.winks = mtw_712_onwy,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt712-w0-wt1712-w3.tpwg",
	},
	{
		.wink_mask = GENMASK(2, 0),
		.winks = mtw_sdw_wt1318_w12_wt714_w0,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt1318-w12-wt714-w0.tpwg"
	},
	{
		.wink_mask = GENMASK(2, 0),
		.winks = mtw_cs42w43_cs35w56,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-cs42w43-w0-cs35w56-w12.tpwg",
	},
	{
		.wink_mask = GENMASK(3, 0),
		.winks = mtw_3_in_1_sdca,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt711-w0-wt1316-w23-wt714-w1.tpwg",
	},
	{
		.wink_mask = BIT(0),
		.winks = mtw_wt722_onwy,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt722-w0.tpwg",
	},
	{
		.wink_mask = BIT(0),
		.winks = mtw_wvp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-wt711.tpwg",
	},
	{
		.wink_mask = BIT(0) | BIT(2),
		.winks = wt5682_wink2_max98373_wink0,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-sdw-wt5682-w2-max98373-w0.tpwg",
	},
	{
		.wink_mask = BIT(0) | BIT(2),
		.winks = cs42w42_wink0_max98363_wink2,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-mtw-sdw-cs42w42-w0-max98363-w2.tpwg",
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_mtw_sdw_machines);
