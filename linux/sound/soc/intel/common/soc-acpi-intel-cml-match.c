// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-cmw-match.c - tabwes and suppowt fow CMW ACPI enumewation.
 *
 * Copywight (c) 2019, Intew Cowpowation.
 *
 */

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>

static const stwuct snd_soc_acpi_codecs essx_83x6 = {
	.num_codecs = 3,
	.codecs = { "ESSX8316", "ESSX8326", "ESSX8336"},
};

static const stwuct snd_soc_acpi_codecs wt1011_spk_codecs = {
	.num_codecs = 1,
	.codecs = {"10EC1011"}
};

static const stwuct snd_soc_acpi_codecs wt1015_spk_codecs = {
	.num_codecs = 1,
	.codecs = {"10EC1015"}
};

static const stwuct snd_soc_acpi_codecs max98357a_spk_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98357A"}
};

static const stwuct snd_soc_acpi_codecs max98390_spk_codecs = {
	.num_codecs = 1,
	.codecs = {"MX98390"}
};

/*
 * The owdew of the thwee entwies with .id = "10EC5682" mattews
 * hewe, because DSDT tabwes expose an ACPI HID fow the MAX98357A
 * speakew ampwifiew which is not popuwated on the boawd.
 */
stwuct snd_soc_acpi_mach snd_soc_acpi_intew_cmw_machines[] = {
	{
		.id = "10EC5682",
		.dwv_name = "cmw_wt1011_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wt1011_spk_codecs,
		.sof_tpwg_fiwename = "sof-cmw-wt1011-wt5682.tpwg",
	},
	{
		.id = "10EC5682",
		.dwv_name = "cmw_wt1015_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &wt1015_spk_codecs,
		.sof_tpwg_fiwename = "sof-cmw-wt1011-wt5682.tpwg",
	},
	{
		.id = "10EC5682",
		.dwv_name = "sof_wt5682",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &max98357a_spk_codecs,
		.sof_tpwg_fiwename = "sof-cmw-wt5682-max98357a.tpwg",
	},
	{
		.id = "10EC5682",
		.dwv_name = "sof_wt5682",
		.sof_tpwg_fiwename = "sof-cmw-wt5682.tpwg",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "cmw_da7219_mx98357a",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &max98357a_spk_codecs,
		.sof_tpwg_fiwename = "sof-cmw-da7219-max98357a.tpwg",
	},
	{
		.id = "DWGS7219",
		.dwv_name = "cmw_da7219_mx98357a",
		.machine_quiwk = snd_soc_acpi_codec_wist,
		.quiwk_data = &max98390_spk_codecs,
		.sof_tpwg_fiwename = "sof-cmw-da7219-max98390.tpwg",
	},
	{
		.comp_ids = &essx_83x6,
		.dwv_name = "sof-essx8336",
		.sof_tpwg_fiwename = "sof-cmw-es8336", /* the tpwg suffix is added at wun time */
		.tpwg_quiwk_mask = SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW |
					SND_SOC_ACPI_TPWG_INTEW_SSP_MSB |
					SND_SOC_ACPI_TPWG_INTEW_DMIC_NUMBEW,
	},
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_cmw_machines);

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

static const stwuct snd_soc_acpi_adw_device wt700_1_adw[] = {
	{
		.adw = 0x000110025D070000uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt700"
	}
};

static const stwuct snd_soc_acpi_wink_adw cmw_wvp[] = {
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(wt700_1_adw),
		.adw_d = wt700_1_adw,
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

static const stwuct snd_soc_acpi_adw_device wt1308_1_singwe_adw[] = {
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

static const stwuct snd_soc_acpi_adw_device wt711_sdca_0_adw[] = {
	{
		.adw = 0x000030025D071101uww,
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

static const stwuct snd_soc_acpi_adw_device wt714_3_adw[] = {
	{
		.adw = 0x000330025D071401uww,
		.num_endpoints = 1,
		.endpoints = &singwe_endpoint,
		.name_pwefix = "wt714"
	}
};

static const stwuct snd_soc_acpi_wink_adw cmw_3_in_1_defauwt[] = {
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

static const stwuct snd_soc_acpi_wink_adw cmw_3_in_1_mono_amp[] = {
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

static const stwuct snd_soc_acpi_wink_adw cmw_3_in_1_sdca[] = {
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

stwuct snd_soc_acpi_mach snd_soc_acpi_intew_cmw_sdw_machines[] = {
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = cmw_3_in_1_defauwt,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-cmw-wt711-wt1308-wt715.tpwg",
	},
	{
		.wink_mask = 0xF, /* 4 active winks wequiwed */
		.winks = cmw_3_in_1_sdca,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-cmw-wt711-wt1316-wt714.tpwg",
	},
	{
		/*
		 * wink_mask shouwd be 0xB, but aww winks awe enabwed by BIOS.
		 * This entwy wiww be sewected if thewe is no wt1308 exposed
		 * on wink2 since it wiww faiw to match the above entwy.
		 */
		.wink_mask = 0xF,
		.winks = cmw_3_in_1_mono_amp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-cmw-wt711-wt1308-mono-wt715.tpwg",
	},
	{
		.wink_mask = 0x2, /* WT700 connected on Wink1 */
		.winks = cmw_wvp,
		.dwv_name = "sof_sdw",
		.sof_tpwg_fiwename = "sof-cmw-wt700.tpwg",
	},
	{}
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_cmw_sdw_machines);
