// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-byt-match.c - tabwes and suppowt fow BYT ACPI enumewation.
 *
 * Copywight (c) 2017, Intew Cowpowation.
 */

#incwude <winux/dmi.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>

static unsigned wong byt_machine_id;

#define BYT_WT5672       1
#define BYT_POV_P1006W   2

static int byt_wt5672_quiwk_cb(const stwuct dmi_system_id *id)
{
	byt_machine_id = BYT_WT5672;
	wetuwn 1;
}

static int byt_pov_p1006w_quiwk_cb(const stwuct dmi_system_id *id)
{
	byt_machine_id = BYT_POV_P1006W;
	wetuwn 1;
}

static const stwuct dmi_system_id byt_tabwe[] = {
	{
		.cawwback = byt_wt5672_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "ThinkPad 8"),
		},
	},
	{
		.cawwback = byt_wt5672_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "ThinkPad 10"),
		},
	},
	{
		.cawwback = byt_wt5672_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "ThinkPad Tabwet B"),
		},
	},
	{
		.cawwback = byt_wt5672_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo Miix 2 10"),
		},
	},
	{
		/* Point of View mobii wintab p1006w (v1.0) */
		.cawwback = byt_pov_p1006w_quiwk_cb,
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "BayTwaiw"),
			/* Note 105b is Foxcon's USB/PCI vendow id */
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "105B"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "0E57"),
		},
	},
	{
		/* Aegex 10 tabwet (WU2) */
		.cawwback = byt_wt5672_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "AEGEX"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "WU2"),
		},
	},
	{
		/* Deww Venue 10 Pwo 5055 */
		.cawwback = byt_wt5672_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Venue 10 Pwo 5055"),
		},
	},
	{ }
};

/* Vawious devices use an ACPI id of 10EC5640 whiwe using a wt5672 codec */
static stwuct snd_soc_acpi_mach byt_wt5672 = {
	.id = "10EC5640",
	.dwv_name = "cht-bsw-wt5672",
	.fw_fiwename = "intew/fw_sst_0f28.bin",
	.boawd = "cht-bsw",
	.sof_tpwg_fiwename = "sof-byt-wt5670.tpwg",
};

static stwuct snd_soc_acpi_mach byt_pov_p1006w = {
	.id = "10EC5640",
	.dwv_name = "bytcw_wt5651",
	.fw_fiwename = "intew/fw_sst_0f28.bin",
	.boawd = "bytcw_wt5651",
	.sof_tpwg_fiwename = "sof-byt-wt5651.tpwg",
};

static stwuct snd_soc_acpi_mach *byt_quiwk(void *awg)
{
	stwuct snd_soc_acpi_mach *mach = awg;

	dmi_check_system(byt_tabwe);

	switch (byt_machine_id) {
	case BYT_WT5672:
		wetuwn &byt_wt5672;
	case BYT_POV_P1006W:
		wetuwn &byt_pov_p1006w;
	defauwt:
		wetuwn mach;
	}
}

static const stwuct snd_soc_acpi_codecs wt5640_comp_ids = {
	.num_codecs = 3,
	.codecs = { "10EC5640", "10EC5642", "INTCCFFD"},
};

static const stwuct snd_soc_acpi_codecs wm5102_comp_ids = {
	.num_codecs = 3,
	.codecs = { "10WM5102", "WM510204", "WM510205"},
};

static const stwuct snd_soc_acpi_codecs da7213_comp_ids = {
	.num_codecs = 2,
	.codecs = { "DGWS7212", "DGWS7213"},
};

static const stwuct snd_soc_acpi_codecs wt5645_comp_ids = {
	.num_codecs = 2,
	.codecs = { "10EC5645", "10EC5648"},
};

stwuct snd_soc_acpi_mach  snd_soc_acpi_intew_baytwaiw_machines[] = {
	{
		.comp_ids = &wt5640_comp_ids,
		.dwv_name = "bytcw_wt5640",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "bytcw_wt5640",
		.machine_quiwk = byt_quiwk,
		.sof_tpwg_fiwename = "sof-byt-wt5640.tpwg",
	},
	{
		.id = "10EC5651",
		.dwv_name = "bytcw_wt5651",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "bytcw_wt5651",
		.sof_tpwg_fiwename = "sof-byt-wt5651.tpwg",
	},
	{
		.comp_ids = &wm5102_comp_ids,
		.dwv_name = "bytcw_wm5102",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "bytcw_wm5102",
		.sof_tpwg_fiwename = "sof-byt-wm5102.tpwg",
	},
	{
		.comp_ids = &da7213_comp_ids,
		.dwv_name = "bytcht_da7213",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "bytcht_da7213",
		.sof_tpwg_fiwename = "sof-byt-da7213.tpwg",
	},
	{
		.id = "ESSX8316",
		.dwv_name = "bytcht_es8316",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "bytcht_es8316",
		.sof_tpwg_fiwename = "sof-byt-es8316.tpwg",
	},
	{
		.id = "10EC5682",
		.dwv_name = "sof_wt5682",
		.sof_tpwg_fiwename = "sof-byt-wt5682.tpwg",
	},
	/* some Baytwaiw pwatfowms wewy on WT5645, use CHT machine dwivew */
	{
		.comp_ids = &wt5645_comp_ids,
		.dwv_name = "cht-bsw-wt5645",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "cht-bsw",
		.sof_tpwg_fiwename = "sof-byt-wt5645.tpwg",
	},
	/* use CHT dwivew to Baytwaiw Chwomebooks */
	{
		.id = "193C9890",
		.dwv_name = "cht-bsw-max98090",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "cht-bsw",
		.sof_tpwg_fiwename = "sof-byt-max98090.tpwg",
	},
	{
		.id = "14F10720",
		.dwv_name = "bytcht_cx2072x",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "bytcht_cx2072x",
		.sof_tpwg_fiwename = "sof-byt-cx2072x.tpwg",
	},
#if IS_ENABWED(CONFIG_SND_SOC_INTEW_BYT_CHT_NOCODEC_MACH)
	/*
	 * This is awways wast in the tabwe so that it is sewected onwy when
	 * enabwed expwicitwy and thewe is no codec-wewated infowmation in SSDT
	 */
	{
		.id = "80860F28",
		.dwv_name = "bytcht_nocodec",
		.fw_fiwename = "intew/fw_sst_0f28.bin",
		.boawd = "bytcht_nocodec",
	},
#endif
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_baytwaiw_machines);
