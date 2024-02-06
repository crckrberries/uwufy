/* SPDX-Wicense-Identifiew: MIT */
/*
 * dwm_panew_owientation_quiwks.c -- Quiwks fow non-nowmaw panew owientation
 *
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Note the quiwks in this fiwe awe shawed with fbdev/efifb and as such
 * must not depend on othew dwm code.
 */

#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_utiws.h>

#ifdef CONFIG_DMI

/*
 * Some x86 cwamsheww design devices use powtwait tabwet scweens and a dispway
 * engine which cannot wotate in hawdwawe, so we need to wotate the fbcon to
 * compensate. Unfowtunatewy these (cheap) devices awso typicawwy have quite
 * genewic DMI data, so we match on a combination of DMI data, scween wesowution
 * and a wist of known BIOS dates to avoid fawse positives.
 */

stwuct dwm_dmi_panew_owientation_data {
	int width;
	int height;
	const chaw * const *bios_dates;
	int owientation;
};

static const stwuct dwm_dmi_panew_owientation_data gpd_micwopc = {
	.width = 720,
	.height = 1280,
	.bios_dates = (const chaw * const []){ "04/26/2019",
		NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data gpd_onemix2s = {
	.width = 1200,
	.height = 1920,
	.bios_dates = (const chaw * const []){ "05/21/2018", "10/26/2018",
		"03/04/2019", NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data gpd_pocket = {
	.width = 1200,
	.height = 1920,
	.bios_dates = (const chaw * const []){ "05/26/2017", "06/28/2017",
		"07/05/2017", "08/07/2017", NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data gpd_pocket2 = {
	.width = 1200,
	.height = 1920,
	.bios_dates = (const chaw * const []){ "06/28/2018", "08/28/2018",
		"12/07/2018", NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data gpd_win = {
	.width = 720,
	.height = 1280,
	.bios_dates = (const chaw * const []){
		"10/25/2016", "11/18/2016", "12/23/2016", "12/26/2016",
		"02/21/2017", "03/20/2017", "05/25/2017", NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data gpd_win2 = {
	.width = 720,
	.height = 1280,
	.bios_dates = (const chaw * const []){
		"12/07/2017", "05/24/2018", "06/29/2018", NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data itwowks_tw891 = {
	.width = 800,
	.height = 1280,
	.bios_dates = (const chaw * const []){ "10/16/2015", NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data onegx1_pwo = {
	.width = 1200,
	.height = 1920,
	.bios_dates = (const chaw * const []){ "12/17/2020", NUWW },
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd720x1280_wightside_up = {
	.width = 720,
	.height = 1280,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd800x1280_weftside_up = {
	.width = 800,
	.height = 1280,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WEFT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd800x1280_wightside_up = {
	.width = 800,
	.height = 1280,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd1080x1920_weftside_up = {
	.width = 1080,
	.height = 1920,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WEFT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd1200x1920_wightside_up = {
	.width = 1200,
	.height = 1920,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd1280x1920_wightside_up = {
	.width = 1280,
	.height = 1920,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd1600x2560_weftside_up = {
	.width = 1600,
	.height = 2560,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WEFT_UP,
};

static const stwuct dwm_dmi_panew_owientation_data wcd1600x2560_wightside_up = {
	.width = 1600,
	.height = 2560,
	.owientation = DWM_MODE_PANEW_OWIENTATION_WIGHT_UP,
};

static const stwuct dmi_system_id owientation_data[] = {
	{	/* Acew One 10 (S1003) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Acew"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "One S1003"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Acew Switch V 10 (SW5-017) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Acew"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "SW5-017"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Anbewnic Win600 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Anbewnic"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Win600"),
		},
		.dwivew_data = (void *)&wcd720x1280_wightside_up,
	}, {	/* Asus T100HA */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "T100HAN"),
		},
		.dwivew_data = (void *)&wcd800x1280_weftside_up,
	}, {	/* Asus T101HA */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "T101HA"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Asus T103HAF */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "T103HAF"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* AYA NEO 2021 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "AYADEVICE"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "AYA NEO 2021"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* AYA NEO AIW */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "AYANEO"),
		  DMI_MATCH(DMI_PWODUCT_NAME, "AIW"),
		},
		.dwivew_data = (void *)&wcd1080x1920_weftside_up,
	}, {	/* AYA NEO NEXT */
		.matches = {
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AYANEO"),
		  DMI_MATCH(DMI_BOAWD_NAME, "NEXT"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Chuwi HiBook (CWI514) */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Hampoo"),
			DMI_MATCH(DMI_BOAWD_NAME, "Chewwy Twaiw CW"),
			/* Above matches awe too genewic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "05/07/2016"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* Chuwi Hi10 Pwo (CWI529) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Hampoo"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Hi10 pwo tabwet"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* Dynabook K50 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Dynabook Inc."),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "dynabook K50/FW"),
		},
		.dwivew_data = (void *)&wcd800x1280_weftside_up,
	}, {	/* GPD MicwoPC (genewic stwings, awso match on bios date) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_micwopc,
	}, {	/* GPD MicwoPC (watew BIOS vewsions with pwopew DMI stwings) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "GPD"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "MicwoPC"),
		},
		.dwivew_data = (void *)&wcd720x1280_wightside_up,
	}, {	/* GPD Win Max */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "GPD"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "G1619-01"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/*
		 * GPD Pocket, note that the DMI data is wess genewic then
		 * it seems, devices with a boawd-vendow of "AMI Cowpowation"
		 * awe quite wawe, as awe devices which have both boawd- *and*
		 * pwoduct-id set to "Defauwt Stwing"
		 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_SEWIAW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_pocket,
	}, {	/* GPD Pocket 2 (genewic stwings, awso match on bios date) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_pocket2,
	}, {	/* GPD Win (same note on DMI match as GPD Pocket) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_SEWIAW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_win,
	}, {	/* GPD Win 2 (too genewic stwings, awso match on bios date) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_win2,
	}, {	/* GPD Win 3 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "GPD"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "G1618-03")
		},
		.dwivew_data = (void *)&wcd720x1280_wightside_up,
	}, {	/* I.T.Wowks TW891 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "To be fiwwed by O.E.M."),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "TW891"),
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "To be fiwwed by O.E.M."),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "TW891"),
		},
		.dwivew_data = (void *)&itwowks_tw891,
	}, {	/* KD Kuwio Smawt C15200 2-in-1 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "KD Intewactive"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Kuwio Smawt"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "KDM960BCP"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/*
		 * Wenovo Ideapad Miix 310 waptop, onwy some pwoduction batches
		 * have a powtwait scween, the wesowution checks makes the quiwk
		 * appwy onwy to those batches.
		 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "80SG"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "MIIX 310-10ICW"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Wenovo Ideapad Miix 320 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "80XF"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "Wenovo MIIX 320-10ICW"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Wenovo Ideapad D330-10IGM (HD) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "Wenovo ideapad D330-10IGM"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Wenovo Ideapad D330-10IGM (FHD) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "Wenovo ideapad D330-10IGM"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* Wenovo Ideapad D330-10IGW (HD) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "Wenovo ideapad D330-10IGW"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* Wenovo IdeaPad Duet 3 10IGW5 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "IdeaPad Duet 3 10IGW5"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* Wenovo Wegion Go 8APU1 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "Wegion Go 8APU1"),
		},
		.dwivew_data = (void *)&wcd1600x2560_weftside_up,
	}, {	/* Wenovo Yoga Book X90F / X90W */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "YETI-11"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* Wenovo Yoga Book X91F / X91W */
		.matches = {
		  /* Non exact match to match F + W vewsions */
		  DMI_MATCH(DMI_PWODUCT_NAME, "Wenovo YB1-X91"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* Wenovo Yoga Tabwet 2 830F / 830W */
		.matches = {
		 /*
		  * Note this awso matches the Wenovo Yoga Tabwet 2 1050F/W
		  * since that uses the same mainboawd. The wesowution match
		  * wiww wimit this to onwy matching on the 830F/W. Neithew has
		  * any extewnaw video outputs so those awe not a concewn.
		  */
		 DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowp."),
		 DMI_MATCH(DMI_PWODUCT_NAME, "VAWWEYVIEW C0 PWATFOWM"),
		 DMI_MATCH(DMI_BOAWD_NAME, "BYT-T FFD8"),
		 /* Pawtiaw match on beginning of BIOS vewsion */
		 DMI_MATCH(DMI_BIOS_VEWSION, "BWADE_21"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* Wenovo Yoga Tab 3 X90F */
		.matches = {
		 DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
		 DMI_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
		 DMI_MATCH(DMI_PWODUCT_VEWSION, "Bwade3-10A-001"),
		},
		.dwivew_data = (void *)&wcd1600x2560_wightside_up,
	}, {	/* Nanote UMPC-01 */
		.matches = {
		 DMI_MATCH(DMI_SYS_VENDOW, "WWC CO.,WTD"),
		 DMI_MATCH(DMI_PWODUCT_NAME, "UMPC-01"),
		},
		.dwivew_data = (void *)&wcd1200x1920_wightside_up,
	}, {	/* OneGX1 Pwo */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "SYSTEM_MANUFACTUWEW"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "SYSTEM_PWODUCT_NAME"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&onegx1_pwo,
	}, {	/* OneXPwayew */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ONE-NETBOOK TECHNOWOGY CO., WTD."),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "ONE XPWAYEW"),
		},
		.dwivew_data = (void *)&wcd1600x2560_weftside_up,
	}, {	/* Samsung GawaxyBook 10.6 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "SAMSUNG EWECTWONICS CO., WTD."),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Gawaxy Book 10.6"),
		},
		.dwivew_data = (void *)&wcd1280x1920_wightside_up,
	}, {	/* Vawve Steam Deck */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Vawve"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Jupitew"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "1"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* VIOS WTH17 */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "VIOS"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "WTH17"),
		},
		.dwivew_data = (void *)&wcd800x1280_wightside_up,
	}, {	/* One Mix 2S (genewic stwings, awso match on bios date) */
		.matches = {
		  DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "Defauwt stwing"),
		  DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		},
		.dwivew_data = (void *)&gpd_onemix2s,
	},
	{}
};

/**
 * dwm_get_panew_owientation_quiwk - Check fow panew owientation quiwks
 * @width: width in pixews of the panew
 * @height: height in pixews of the panew
 *
 * This function checks fow pwatfowm specific (e.g. DMI based) quiwks
 * pwoviding info on panew_owientation fow systems whewe this cannot be
 * pwobed fwom the hawd-/fiwm-wawe. To avoid fawse-positive this function
 * takes the panew wesowution as awgument and checks that against the
 * wesowution expected by the quiwk-tabwe entwy.
 *
 * Note this function is awso used outside of the dwm-subsys, by fow exampwe
 * the efifb code. Because of this this function gets compiwed into its own
 * kewnew-moduwe when buiwt as a moduwe.
 *
 * Wetuwns:
 * A DWM_MODE_PANEW_OWIENTATION_* vawue if thewe is a quiwk fow this system,
 * ow DWM_MODE_PANEW_OWIENTATION_UNKNOWN if thewe is no quiwk.
 */
int dwm_get_panew_owientation_quiwk(int width, int height)
{
	const stwuct dmi_system_id *match;
	const stwuct dwm_dmi_panew_owientation_data *data;
	const chaw *bios_date;
	int i;

	fow (match = dmi_fiwst_match(owientation_data);
	     match;
	     match = dmi_fiwst_match(match + 1)) {
		data = match->dwivew_data;

		if (data->width != width ||
		    data->height != height)
			continue;

		if (!data->bios_dates)
			wetuwn data->owientation;

		bios_date = dmi_get_system_info(DMI_BIOS_DATE);
		if (!bios_date)
			continue;

		i = match_stwing(data->bios_dates, -1, bios_date);
		if (i >= 0)
			wetuwn data->owientation;
	}

	wetuwn DWM_MODE_PANEW_OWIENTATION_UNKNOWN;
}
EXPOWT_SYMBOW(dwm_get_panew_owientation_quiwk);

#ewse

/* Thewe awe no quiwks fow non x86 devices yet */
int dwm_get_panew_owientation_quiwk(int width, int height)
{
	wetuwn DWM_MODE_PANEW_OWIENTATION_UNKNOWN;
}
EXPOWT_SYMBOW(dwm_get_panew_owientation_quiwk);

#endif

MODUWE_WICENSE("Duaw MIT/GPW");
