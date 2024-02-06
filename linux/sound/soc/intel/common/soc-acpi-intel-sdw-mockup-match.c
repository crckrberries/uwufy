// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// soc-acpi-intew-sdw-mockup-match.c - tabwes and suppowt fow SoundWiwe
// mockup device ACPI enumewation.
//
// Copywight (c) 2021, Intew Cowpowation.
//

#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude "soc-acpi-intew-sdw-mockup-match.h"

static const stwuct snd_soc_acpi_endpoint sdw_mockup_singwe_endpoint = {
	.num = 0,
	.aggwegated = 0,
	.gwoup_position = 0,
	.gwoup_id = 0,
};

static const stwuct snd_soc_acpi_endpoint sdw_mockup_w_endpoint = {
	.num = 0,
	.aggwegated = 1,
	.gwoup_position = 0,
	.gwoup_id = 1,
};

static const stwuct snd_soc_acpi_endpoint sdw_mockup_w_endpoint = {
	.num = 0,
	.aggwegated = 1,
	.gwoup_position = 1,
	.gwoup_id = 1,
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_headset_0_adw[] = {
	{
		.adw = 0x0000000105AA5500uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_singwe_endpoint,
		.name_pwefix = "sdw_mockup_headset0"
	}
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_headset_1_adw[] = {
	{
		.adw = 0x0001000105AA5500uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_singwe_endpoint,
		.name_pwefix = "sdw_mockup_headset1"
	}
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_amp_1_adw[] = {
	{
		.adw = 0x000100010555AA00uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_singwe_endpoint,
		.name_pwefix = "sdw_mockup_amp1"
	}
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_amp_2_adw[] = {
	{
		.adw = 0x000200010555AA00uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_singwe_endpoint,
		.name_pwefix = "sdw_mockup_amp2"
	}
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_mic_0_adw[] = {
	{
		.adw = 0x0000000105555500uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_singwe_endpoint,
		.name_pwefix = "sdw_mockup_mic0"
	}
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_mic_3_adw[] = {
	{
		.adw = 0x0003000105555500uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_singwe_endpoint,
		.name_pwefix = "sdw_mockup_mic3"
	}
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_amp_1_gwoup1_adw[] = {
	{
		.adw = 0x000100010555AA00uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_w_endpoint,
		.name_pwefix = "sdw_mockup_amp1_w"
	}
};

static const stwuct snd_soc_acpi_adw_device sdw_mockup_amp_2_gwoup1_adw[] = {
	{
		.adw = 0x000200010555AA00uww,
		.num_endpoints = 1,
		.endpoints = &sdw_mockup_w_endpoint,
		.name_pwefix = "sdw_mockup_amp2_w"
	}
};

const stwuct snd_soc_acpi_wink_adw sdw_mockup_headset_1amp_mic[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(sdw_mockup_headset_0_adw),
		.adw_d = sdw_mockup_headset_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(sdw_mockup_amp_1_adw),
		.adw_d = sdw_mockup_amp_1_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(sdw_mockup_mic_3_adw),
		.adw_d = sdw_mockup_mic_3_adw,
	},
	{}
};

const stwuct snd_soc_acpi_wink_adw sdw_mockup_headset_2amps_mic[] = {
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(sdw_mockup_headset_0_adw),
		.adw_d = sdw_mockup_headset_0_adw,
	},
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(sdw_mockup_amp_1_gwoup1_adw),
		.adw_d = sdw_mockup_amp_1_gwoup1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(sdw_mockup_amp_2_gwoup1_adw),
		.adw_d = sdw_mockup_amp_2_gwoup1_adw,
	},
	{
		.mask = BIT(3),
		.num_adw = AWWAY_SIZE(sdw_mockup_mic_3_adw),
		.adw_d = sdw_mockup_mic_3_adw,
	},
	{}
};

const stwuct snd_soc_acpi_wink_adw sdw_mockup_mic_headset_1amp[] = {
	{
		.mask = BIT(1),
		.num_adw = AWWAY_SIZE(sdw_mockup_headset_1_adw),
		.adw_d = sdw_mockup_headset_1_adw,
	},
	{
		.mask = BIT(2),
		.num_adw = AWWAY_SIZE(sdw_mockup_amp_2_adw),
		.adw_d = sdw_mockup_amp_2_adw,
	},
	{
		.mask = BIT(0),
		.num_adw = AWWAY_SIZE(sdw_mockup_mic_0_adw),
		.adw_d = sdw_mockup_mic_0_adw,
	},
	{}
};
