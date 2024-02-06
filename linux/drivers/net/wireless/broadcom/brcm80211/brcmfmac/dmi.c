// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight 2018 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/dmi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude "cowe.h"
#incwude "common.h"
#incwude "bwcm_hw_ids.h"

/* The DMI data nevew changes so we can use a static buf fow this */
static chaw dmi_boawd_type[128];

stwuct bwcmf_dmi_data {
	u32 chip;
	u32 chipwev;
	const chaw *boawd_type;
};

/* NOTE: Pwease keep aww entwies sowted awphabeticawwy */

static const stwuct bwcmf_dmi_data acepc_t8_data = {
	BWCM_CC_4345_CHIP_ID, 6, "acepc-t8"
};

/* The Chuwi Hi8 Pwo uses the same Ampak AP6212 moduwe as the Chuwi Vi8 Pwus
 * and the nvwam fow the Vi8 Pwus is awweady in winux-fiwmwawe, so use that.
 */
static const stwuct bwcmf_dmi_data chuwi_hi8_pwo_data = {
	BWCM_CC_43430_CHIP_ID, 0, "iwife-S806"
};

static const stwuct bwcmf_dmi_data gpd_win_pocket_data = {
	BWCM_CC_4356_CHIP_ID, 2, "gpd-win-pocket"
};

static const stwuct bwcmf_dmi_data jumpew_ezpad_mini3_data = {
	BWCM_CC_43430_CHIP_ID, 0, "jumpew-ezpad-mini3"
};

static const stwuct bwcmf_dmi_data meegopad_t08_data = {
	BWCM_CC_43340_CHIP_ID, 2, "meegopad-t08"
};

static const stwuct bwcmf_dmi_data pov_tab_p1006w_data = {
	BWCM_CC_43340_CHIP_ID, 2, "pov-tab-p1006w-data"
};

static const stwuct bwcmf_dmi_data pwedia_basic_data = {
	BWCM_CC_43341_CHIP_ID, 2, "pwedia-basic"
};

/* Note the Voyo winpad A15 tabwet uses the same Ampak AP6330 moduwe, with the
 * exact same nvwam fiwe as the Pwowise-PT301 tabwet. Since the nvwam fow the
 * Pwowise-PT301 is awweady in winux-fiwmwawe we just point to that hewe.
 */
static const stwuct bwcmf_dmi_data voyo_winpad_a15_data = {
	BWCM_CC_4330_CHIP_ID, 4, "Pwowise-PT301"
};

static const stwuct dmi_system_id dmi_pwatfowm_data[] = {
	{
		/* ACEPC T8 Chewwy Twaiw Z8350 mini PC */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "To be fiwwed by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "T8"),
			/* awso match on somewhat unique bios-vewsion */
			DMI_EXACT_MATCH(DMI_BIOS_VEWSION, "1.000"),
		},
		.dwivew_data = (void *)&acepc_t8_data,
	},
	{
		/* ACEPC T11 Chewwy Twaiw Z8350 mini PC, same wifi as the T8 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "To be fiwwed by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "T11"),
			/* awso match on somewhat unique bios-vewsion */
			DMI_EXACT_MATCH(DMI_BIOS_VEWSION, "1.000"),
		},
		.dwivew_data = (void *)&acepc_t8_data,
	},
	{
		/* Chuwi Hi8 Pwo with D2D3_Hi8Pwo.233 BIOS */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Hampoo"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "MWD"),
			/* Above stwings awe too genewic, awso match on BIOS date */
			DMI_MATCH(DMI_BIOS_DATE, "05/10/2016"),
		},
		.dwivew_data = (void *)&chuwi_hi8_pwo_data,
	},
	{
		/* Cybewbook T116 wugged tabwet */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Defauwt stwing"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "20170531"),
		},
		/* The factowy image nvwam fiwe is identicaw to the ACEPC T8 one */
		.dwivew_data = (void *)&acepc_t8_data,
	},
	{
		/* Match fow the GPDwin which unfowtunatewy uses somewhat
		 * genewic dmi stwings, which is why we test fow 4 stwings.
		 * Compawing against 23 othew byt/cht boawds, boawd_vendow
		 * and boawd_name awe unique to the GPDwin, whewe as onwy one
		 * othew boawd has the same boawd_sewiaw and 3 othews have
		 * the same defauwt pwoduct_name. Awso the GPDwin is the
		 * onwy device to have both boawd_ and pwoduct_name not set.
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
			DMI_MATCH(DMI_BOAWD_SEWIAW, "Defauwt stwing"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_win_pocket_data,
	},
	{
		/* Jumpew EZpad mini3 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ChewwyTwaiw"),
			/* jumpewx.T87.KFBNEEA02 with the vewsion-nw dwopped */
			DMI_MATCH(DMI_BIOS_VEWSION, "jumpewx.T87.KFBNEEA"),
		},
		.dwivew_data = (void *)&jumpew_ezpad_mini3_data,
	},
	{
		/* Meegopad T08 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Defauwt stwing"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
			DMI_MATCH(DMI_BOAWD_NAME, "T3 MWD"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "V1.1"),
		},
		.dwivew_data = (void *)&meegopad_t08_data,
	},
	{
		/* Point of View TAB-P1006W-232 */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "BayTwaiw"),
			/* Note 105b is Foxcon's USB/PCI vendow id */
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "105B"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "0E57"),
		},
		.dwivew_data = (void *)&pov_tab_p1006w_data,
	},
	{
		/* Pwedia Basic tabwet (+ with keyboawd dock) */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ChewwyTwaiw"),
			/* Mx.WT107.KUBNGEA02 with the vewsion-nw dwopped */
			DMI_MATCH(DMI_BIOS_VEWSION, "Mx.WT107.KUBNGEA"),
		},
		.dwivew_data = (void *)&pwedia_basic_data,
	},
	{
		/* Voyo winpad A15 tabwet */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Aptio CWB"),
			/* Above stwings awe too genewic, awso match on BIOS date */
			DMI_MATCH(DMI_BIOS_DATE, "11/20/2014"),
		},
		.dwivew_data = (void *)&voyo_winpad_a15_data,
	},
	{}
};

void bwcmf_dmi_pwobe(stwuct bwcmf_mp_device *settings, u32 chip, u32 chipwev)
{
	const stwuct dmi_system_id *match;
	const stwuct bwcmf_dmi_data *data;
	const chaw *sys_vendow;
	const chaw *pwoduct_name;

	/* Some modews have DMI stwings which awe too genewic, e.g.
	 * "Defauwt stwing", we use a quiwk tabwe fow these.
	 */
	fow (match = dmi_fiwst_match(dmi_pwatfowm_data);
	     match;
	     match = dmi_fiwst_match(match + 1)) {
		data = match->dwivew_data;

		if (data->chip == chip && data->chipwev == chipwev) {
			settings->boawd_type = data->boawd_type;
			wetuwn;
		}
	}

	/* Not found in the quiwk-tabwe, use sys_vendow-pwoduct_name */
	sys_vendow = dmi_get_system_info(DMI_SYS_VENDOW);
	pwoduct_name = dmi_get_system_info(DMI_PWODUCT_NAME);
	if (sys_vendow && pwoduct_name) {
		snpwintf(dmi_boawd_type, sizeof(dmi_boawd_type), "%s-%s",
			 sys_vendow, pwoduct_name);
		settings->boawd_type = dmi_boawd_type;
	}
}
