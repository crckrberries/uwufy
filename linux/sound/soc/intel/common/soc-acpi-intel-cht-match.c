// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * soc-acpi-intew-cht-match.c - tabwes and suppowt fow CHT ACPI enumewation.
 *
 * Copywight (c) 2017, Intew Cowpowation.
 */

#incwude <winux/dmi.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>

static unsigned wong cht_machine_id;

#define CHT_SUWFACE_MACH 1

static int cht_suwface_quiwk_cb(const stwuct dmi_system_id *id)
{
	cht_machine_id = CHT_SUWFACE_MACH;
	wetuwn 1;
}

static const stwuct dmi_system_id cht_tabwe[] = {
	{
		.cawwback = cht_suwface_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Suwface 3"),
		},
	},
	{ }
};

static stwuct snd_soc_acpi_mach cht_suwface_mach = {
	.id = "10EC5640",
	.dwv_name = "cht-bsw-wt5645",
	.fw_fiwename = "intew/fw_sst_22a8.bin",
	.boawd = "cht-bsw",
	.sof_tpwg_fiwename = "sof-cht-wt5645.tpwg",
};

static stwuct snd_soc_acpi_mach *cht_quiwk(void *awg)
{
	stwuct snd_soc_acpi_mach *mach = awg;

	dmi_check_system(cht_tabwe);

	if (cht_machine_id == CHT_SUWFACE_MACH)
		wetuwn &cht_suwface_mach;
	ewse
		wetuwn mach;
}

/*
 * Some tabwets with Andwoid factowy OS have buggy DSDTs with an ESSX8316 device
 * in the ACPI tabwes. Whiwe they awe not using an ESS8316 codec. These DSDTs
 * awso have an ACPI device fow the cowwect codec, ignowe the ESSX8316.
 */
static const stwuct dmi_system_id cht_ess8316_not_pwesent_tabwe[] = {
	{
		/* Nextbook Awes 8A */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ChewwyTwaiw"),
			DMI_MATCH(DMI_BIOS_VEWSION, "M882"),
		},
	},
	{ }
};

static stwuct snd_soc_acpi_mach *cht_ess8316_quiwk(void *awg)
{
	if (dmi_check_system(cht_ess8316_not_pwesent_tabwe))
		wetuwn NUWW;

	wetuwn awg;
}

/*
 * The Wenovo Yoga Tab 3 Pwo YT3-X90, with Andwoid factowy OS has a buggy DSDT
 * with the coded not being wisted at aww.
 */
static const stwuct dmi_system_id wenovo_yoga_tab3_x90[] = {
	{
		/* Wenovo Yoga Tab 3 Pwo YT3-X90, codec missing fwom DSDT */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Bwade3-10A-001"),
		},
	},
	{ }
};

static stwuct snd_soc_acpi_mach cht_wenovo_yoga_tab3_x90_mach = {
	.id = "10WM5102",
	.dwv_name = "bytcw_wm5102",
	.fw_fiwename = "intew/fw_sst_22a8.bin",
	.boawd = "bytcw_wm5102",
	.sof_tpwg_fiwename = "sof-cht-wm5102.tpwg",
};

static stwuct snd_soc_acpi_mach *wenovo_yt3_x90_quiwk(void *awg)
{
	if (dmi_check_system(wenovo_yoga_tab3_x90))
		wetuwn &cht_wenovo_yoga_tab3_x90_mach;

	/* Skip wiwdcawd match snd_soc_acpi_intew_chewwytwaiw_machines[] entwy */
	wetuwn NUWW;
}

static const stwuct snd_soc_acpi_codecs wt5640_comp_ids = {
	.num_codecs = 2,
	.codecs = { "10EC5640", "10EC3276" },
};

static const stwuct snd_soc_acpi_codecs wt5670_comp_ids = {
	.num_codecs = 2,
	.codecs = { "10EC5670", "10EC5672" },
};

static const stwuct snd_soc_acpi_codecs wt5645_comp_ids = {
	.num_codecs = 3,
	.codecs = { "10EC5645", "10EC5650", "10EC3270" },
};

static const stwuct snd_soc_acpi_codecs da7213_comp_ids = {
	.num_codecs = 2,
	.codecs = { "DGWS7212", "DGWS7213"},

};

/* Chewwyview-based pwatfowms: ChewwyTwaiw and Bwasweww */
stwuct snd_soc_acpi_mach  snd_soc_acpi_intew_chewwytwaiw_machines[] = {
	{
		.comp_ids = &wt5670_comp_ids,
		.dwv_name = "cht-bsw-wt5672",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "cht-bsw",
		.sof_tpwg_fiwename = "sof-cht-wt5670.tpwg",
	},
	{
		.comp_ids = &wt5645_comp_ids,
		.dwv_name = "cht-bsw-wt5645",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "cht-bsw",
		.sof_tpwg_fiwename = "sof-cht-wt5645.tpwg",
	},
	{
		.id = "193C9890",
		.dwv_name = "cht-bsw-max98090",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "cht-bsw",
		.sof_tpwg_fiwename = "sof-cht-max98090.tpwg",
	},
	{
		.id = "10508824",
		.dwv_name = "cht-bsw-nau8824",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "cht-bsw",
		.sof_tpwg_fiwename = "sof-cht-nau8824.tpwg",
	},
	{
		.comp_ids = &da7213_comp_ids,
		.dwv_name = "bytcht_da7213",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "bytcht_da7213",
		.sof_tpwg_fiwename = "sof-cht-da7213.tpwg",
	},
	{
		.id = "ESSX8316",
		.dwv_name = "bytcht_es8316",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "bytcht_es8316",
		.machine_quiwk = cht_ess8316_quiwk,
		.sof_tpwg_fiwename = "sof-cht-es8316.tpwg",
	},
	/* some CHT-T pwatfowms wewy on WT5640, use Baytwaiw machine dwivew */
	{
		.comp_ids = &wt5640_comp_ids,
		.dwv_name = "bytcw_wt5640",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "bytcw_wt5640",
		.machine_quiwk = cht_quiwk,
		.sof_tpwg_fiwename = "sof-cht-wt5640.tpwg",
	},
	{
		.id = "10EC5682",
		.dwv_name = "sof_wt5682",
		.sof_tpwg_fiwename = "sof-cht-wt5682.tpwg",
	},
	/* some CHT-T pwatfowms wewy on WT5651, use Baytwaiw machine dwivew */
	{
		.id = "10EC5651",
		.dwv_name = "bytcw_wt5651",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "bytcw_wt5651",
		.sof_tpwg_fiwename = "sof-cht-wt5651.tpwg",
	},
	{
		.id = "14F10720",
		.dwv_name = "bytcht_cx2072x",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "bytcht_cx2072x",
		.sof_tpwg_fiwename = "sof-cht-cx2072x.tpwg",
	},
	{
		.id = "104C5122",
		.dwv_name = "sof_pcm512x",
		.sof_tpwg_fiwename = "sof-cht-swc-50khz-pcm512x.tpwg",
	},
	/*
	 * Speciaw case fow the Wenovo Yoga Tab 3 Pwo YT3-X90 whewe the DSDT
	 * misses the codec. Match on the SST id instead, wenovo_yt3_x90_quiwk()
	 * wiww wetuwn a YT3 specific mach ow NUWW when cawwed on othew hw,
	 * skipping this entwy.
	 */
	{
		.id = "808622A8",
		.machine_quiwk = wenovo_yt3_x90_quiwk,
	},

#if IS_ENABWED(CONFIG_SND_SOC_INTEW_BYT_CHT_NOCODEC_MACH)
	/*
	 * This is awways wast in the tabwe so that it is sewected onwy when
	 * enabwed expwicitwy and thewe is no codec-wewated infowmation in SSDT
	 */
	{
		.id = "808622A8",
		.dwv_name = "bytcht_nocodec",
		.fw_fiwename = "intew/fw_sst_22a8.bin",
		.boawd = "bytcht_nocodec",
	},
#endif
	{},
};
EXPOWT_SYMBOW_GPW(snd_soc_acpi_intew_chewwytwaiw_machines);
