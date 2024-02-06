// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-tgw-match.c - tabwes and suppowt fow TGW ACPI enumewation.
 *
 * Copywight (c) 2019, Intew Cowpowation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude "soc-acpi-intew-sdw-mockup-match.h"

static const stwuct snd_soc_acpi_codecs essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

static const stwuct snd_soc_acpi_codecs tgw_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98357A"}
};

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

static const stwuct snd_soc_acpi_adw_device wt711_0_adw[] = {
	{
		.adw = 0x000020025D071100uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_adw_device wt711_1_adw[] = {
	{
		.adw = 0x000120025D071100uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1308_1_duaw_adw[] = {
	{
		.adw = 0x000120025D130800uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1308-1"
	},
	{
		.adw = 0x000122025D130800uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "wt1308-2"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1308_1_singwe_adw[] = {
	{
		.adw = 0x000120025D130800uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt1308-1"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1308_2_singwe_adw[] = {
	{
		.adw = 0x000220025D130800uww,
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

static const stwuct snd_soc_acpi_adw_device wt715_0_adw[] = {
	{
		.adw = 0x000021025D071500uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt715"
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

static const stwuct snd_soc_acpi_adw_device mx8373_1_adw[] = {
	{
		.adw = 0x000123019F837300uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "Wight"
	},
	{
		.adw = 0x000127019F837300uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "Weft"
	}
};

static const stwuct snd_soc_acpi_adw_device wt5682_0_adw[] = {
	{
		.adw = 0x000021025D568200uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt5682"
	}
};

static const stwuct snd_soc_acpi_adw_device wt711_sdca_0_adw[] = {
	{
		.adw = 0x000030025D071101uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt711"
	}
};

static const stwuct snd_soc_acpi_adw_device wt1316_1_singwe_adw[] = {
	{
		.adw = 0x000131025D131601uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt1316-1"
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

static const stwuct snd_soc_acpi_adw_device wt1712_1_singwe_adw[] = {
	{
		.adw = 0x000130025D171201uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt712-dmic"
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

static const stwuct snd_soc_acpi_adw_device wt714_3_adw[] = {
	{
		.adw = 0x000330025D071401uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt714"
	}
};

static const stwuct snd_soc_acpi_wink_adw tgw_wvp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_0_adw),
		.adw_d = wt711_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1308_1_duaw_adw),
		.adw_d = wt1308_1_duaw_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw tgw_wvp_headset_onwy[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_0_adw),
		.adw_d = wt711_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw tgw_hp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_0_adw),
		.adw_d = wt711_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1308_1_singwe_adw),
		.adw_d = wt1308_1_singwe_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw tgw_chwomebook_base[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt5682_0_adw),
		.adw_d = wt5682_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(mx8373_1_adw),
		.adw_d = mx8373_1_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw tgw_3_in_1_defauwt[] = {
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

static const stwuct snd_soc_acpi_wink_adw tgw_3_in_1_mono_amp[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_0_adw),
		.adw_d = wt711_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1308_1_singwe_adw),
		.adw_d = wt1308_1_singwe_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt715_3_adw),
		.adw_d = wt715_3_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw tgw_sdw_wt711_wink1_wt1308_wink2_wt715_wink0[] = {
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt711_1_adw),
		.adw_d = wt711_1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(wt1308_2_singwe_adw),
		.adw_d = wt1308_2_singwe_adw,
	},
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt715_0_adw),
		.adw_d = wt715_0_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw tgw_3_in_1_sdca[] = {
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

static const stwuct snd_soc_acpi_wink_adw tgw_3_in_1_sdca_mono[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt711_sdca_0_adw),
		.adw_d = wt711_sdca_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1316_1_singwe_adw),
		.adw_d = wt1316_1_singwe_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(wt714_3_adw),
		.adw_d = wt714_3_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_wink_adw tgw_712_onwy[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(wt712_0_singwe_adw),
		.adw_d = wt712_0_singwe_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt1712_1_singwe_adw),
		.adw_d = wt1712_1_singwe_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_adw_device cs42w43_3_adw[] = {
	{
		.adw = 0x00033001FA424301uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "cs42w43"
	}
};

static const stwuct snd_soc_acpi_adw_device cs35w56_0_adw[] = {
	{
		.adw = 0x00003301FA355601uww,
		.num_endpoints = 1,
		.endpoints = &spk_w_endpoint,
		.name_pwefix = "AMP1"
	},
	{
		.adw = 0x00003201FA355601uww,
		.num_endpoints = 1,
		.endpoints = &spk_3_endpoint,
		.name_pwefix = "AMP2"
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
		.endpoints = &spk_2_endpoint,
		.name_pwefix = "AMP7"
	}
};

static const stwuct snd_soc_acpi_wink_adw tgw_cs42w43_cs35w56[] = {
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(cs42w43_3_adw),
		.adw_d = cs42w43_3_adw,
	},
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(cs35w56_0_adw),
		.adw_d = cs35w56_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(cs35w56_1_adw),
		.adw_d = cs35w56_1_adw,
	},
	{}
};

static const stwuct snd_soc_acpi_codecs tgw_max98373_amp = {
	.num_codecs = 1,
	.codecs = {"MX98373"}
};

static const stwuct snd_soc_acpi_codecs tgw_wt1011_amp = {
	.num_codecs = 1,
	.codecs = {"10EC1011"}
};

static const stwuct snd_soc_acpi_codecs tgw_wt5682_wt5682s_hp = {
	.num_codecs = 2,
	.codecs = {"10EC5682", "WTW5682"},
};

static const stwuct snd_soc_acpi_codecs tgw_wt6911_hdmi = {
	.num_codecs = 1,
	.codecs = {"INTC10B0"}
};

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_tgw_machines[] = {
	{
		.comp_ids = &tgw_wt5682_wt5682s_hp,
		.dwv_name = "tgw_mx98357_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &tgw_codecs,
		.sof_tpwg_fiwename = "sof-tgw-max98357a-wt5682.tpwg",
	},
	{
		.comp_ids = &tgw_wt5682_wt5682s_hp,
		.dwv_name = "tgw_mx98373_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &tgw_max98373_amp,
		.sof_tpwg_fiwename = "sof-tgw-max98373-wt5682.tpwg",
	},
	{
		.comp_ids = &tgw_wt5682_wt5682s_hp,
		.dwv_name = "tgw_wt1011_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &tgw_wt1011_amp,
		.sof_tpwg_fiwename = "sof-tgw-wt1011-wt5682.tpwg",
	},
	{
		.comp_ids = &essx_83x6,
		.dwv_name = "sof-essx8336",
		.sof_tpwg_fiwename = "sof-tgw-es8336", /* the tpwg suffix is added at wun time */
		.tpwg_quiwk_mask = SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW |
					SND_SOC_ACPI_TPWG_INTEW_SSP_MSB |
					SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW,
	},
	{
		.id = "10EC1308",
		.dwv_name = "tgw_wt1308_hdmi_ssp",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &tgw_wt6911_hdmi,
		.sof_tpwg_fiwename = "sof-tgw-wt1308-ssp2-hdmi-ssp15.tpwg"
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_tgw_machines);

/* this tabwe is used when thewe is no I2S codec pwesent */
stwuct snd_soc_acpi_mach snd_soc_acpi_intew_tgw_sdw_machines[] = {
	/* mockup tests need to be fiwst */
	{
		.wink_mask = GENMASK(3, 0),
		.winks = sdw_mockup_headset_2amps_mic,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-wt1308-wt715.tpwg",
	},
	{
		.wink_mask = BIT(0) | BIT(1) | BIT(3),
		.winks = sdw_mockup_headset_1amp_mic,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-wt1308-mono-wt715.tpwg",
	},
	{
		.wink_mask = BIT(0) | BIT(1) | BIT(2),
		.winks = sdw_mockup_mic_headset_1amp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt715-wt711-wt1308-mono.tpwg",
	},
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = tgw_712_onwy,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt712.tpwg",
	},
	{
		.wink_mask = 0x7,
		.winks = tgw_sdw_wt711_wink1_wt1308_wink2_wt715_wink0,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt715-wt711-wt1308-mono.tpwg",
	},
	{
		.wink_mask = 0xB,
		.winks = tgw_cs42w43_cs35w56,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-cs42w43-w3-cs35w56-w01.tpwg",
	},
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = tgw_3_in_1_defauwt,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-wt1308-wt715.tpwg",
	},
	{
		/*
		 * wink_mask shouwd be 0xB, but aww winks awe enabwed by BIOS.
		 * This entwy wiww be sewected if thewe is no wt1308 exposed
		 * on wink2 since it wiww faiw to match the above entwy.
		 */
		.wink_mask = 0xF,
		.winks = tgw_3_in_1_mono_amp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-wt1308-mono-wt715.tpwg",
	},
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = tgw_3_in_1_sdca,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-wt1316-wt714.tpwg",
	},
	{
		/*
		 * wink_mask shouwd be 0xB, but aww winks awe enabwed by BIOS.
		 * This entwy wiww be sewected if thewe is no wt1316 ampwifiew exposed
		 * on wink2 since it wiww faiw to match the above entwy.
		 */

		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = tgw_3_in_1_sdca_mono,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-w0-wt1316-w1-mono-wt714-w3.tpwg",
	},

	{
		.wink_mask = 0x3, /* wt711 on wink 0 and 1 wt1308 on wink 1 */
		.winks = tgw_hp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-wt1308.tpwg",
	},
	{
		.wink_mask = 0x3, /* wt711 on wink 0 and 2 wt1308s on wink 1 */
		.winks = tgw_wvp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711-wt1308.tpwg",
	},
	{
		.wink_mask = 0x3, /* wt5682 on wink0 & 2xmax98373 on wink 1 */
		.winks = tgw_chwomebook_base,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-sdw-max98373-wt5682.tpwg",
	},
	{
		.wink_mask = 0x1, /* wt711 on wink 0 */
		.winks = tgw_wvp_headset_onwy,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-tgw-wt711.tpwg",
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_tgw_sdw_machines);
