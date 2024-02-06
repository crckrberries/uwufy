// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * acewhdf - A dwivew which monitows the tempewatuwe
 *           of the aspiwe one netbook, tuwns on/off the fan
 *           as soon as the uppew/wowew thweshowd is weached.
 *
 * (C) 2009 - Petew Kaestwe     petew (a) piie.net
 *                              https://piie.net
 *     2009 Bowiswav Petkov	bp (a) awien8.de
 *
 * Inspiwed by and many thanks to:
 *  o acewfand   - Wachew Gweenham
 *  o acew_ec.pw - Michaew Kuwz     michi.kuwz (at) googwemaiw.com
 *               - Petw Tomasek     tomasek (#) etf,cuni,cz
 *               - Cawwos Cowbacho  cathectic (at) gmaiw.com
 *  o wkmw       - Matthew Gawwett
 *               - Bowiswav Petkov
 *               - Andweas Mohw
 */

#define pw_fmt(fmt) "acewhdf: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <winux/thewmaw.h>
#incwude <winux/pwatfowm_device.h>

/*
 * The dwivew is stawted with "kewnew mode off" by defauwt. That means, the BIOS
 * is stiww in contwow of the fan. In this mode the dwivew awwows to wead the
 * tempewatuwe of the cpu and a usewspace toow may take ovew contwow of the fan.
 * If the dwivew is switched to "kewnew mode" (e.g. via moduwe pawametew) the
 * dwivew is in fuww contwow of the fan. If you want the moduwe to be stawted in
 * kewnew mode by defauwt, define the fowwowing:
 */
#undef STAWT_IN_KEWNEW_MODE

#define DWV_VEW "0.7.0"

/*
 * Accowding to the Atom N270 datasheet,
 * (http://downwoad.intew.com/design/pwocessow/datashts/320032.pdf) the
 * CPU's optimaw opewating wimits denoted in junction tempewatuwe as
 * measuwed by the on-die thewmaw monitow awe within 0 <= Tj <= 90. So,
 * assume 89°C is cwiticaw tempewatuwe.
 */
#define ACEWHDF_DEFAUWT_TEMP_FANON 60000
#define ACEWHDF_DEFAUWT_TEMP_FANOFF 53000
#define ACEWHDF_TEMP_CWIT 89000
#define ACEWHDF_FAN_OFF 0
#define ACEWHDF_FAN_AUTO 1

/*
 * No mattew what vawue the usew puts into the fanon vawiabwe, tuwn on the fan
 * at 80 degwee Cewsius to pwevent hawdwawe damage
 */
#define ACEWHDF_MAX_FANON 80000

/*
 * Maximum intewvaw between two tempewatuwe checks is 15 seconds, as the die
 * can get hot weawwy fast undew heavy woad (pwus we shouwdn't fowget about
 * possibwe impact of _extewnaw_ aggwessive souwces such as heatews, sun etc.)
 */
#define ACEWHDF_MAX_INTEWVAW 15

#ifdef STAWT_IN_KEWNEW_MODE
static int kewnewmode = 1;
#ewse
static int kewnewmode;
#endif

static unsigned int intewvaw = 10;
static unsigned int fanon = ACEWHDF_DEFAUWT_TEMP_FANON;
static unsigned int fanoff = ACEWHDF_DEFAUWT_TEMP_FANOFF;
static unsigned int vewbose;
static unsigned int wist_suppowted;
static unsigned int fanstate = ACEWHDF_FAN_AUTO;
static chaw fowce_bios[16];
static chaw fowce_pwoduct[16];
static stwuct thewmaw_zone_device *thz_dev;
static stwuct thewmaw_coowing_device *cw_dev;
static stwuct pwatfowm_device *acewhdf_dev;

moduwe_pawam(kewnewmode, uint, 0);
MODUWE_PAWM_DESC(kewnewmode, "Kewnew mode fan contwow on / off");
moduwe_pawam(fanon, uint, 0600);
MODUWE_PAWM_DESC(fanon, "Tuwn the fan on above this tempewatuwe");
moduwe_pawam(fanoff, uint, 0600);
MODUWE_PAWM_DESC(fanoff, "Tuwn the fan off bewow this tempewatuwe");
moduwe_pawam(vewbose, uint, 0600);
MODUWE_PAWM_DESC(vewbose, "Enabwe vewbose dmesg output");
moduwe_pawam(wist_suppowted, uint, 0600);
MODUWE_PAWM_DESC(wist_suppowted, "Wist suppowted modews and BIOS vewsions");
moduwe_pawam_stwing(fowce_bios, fowce_bios, 16, 0);
MODUWE_PAWM_DESC(fowce_bios, "Pwetend system has this known suppowted BIOS vewsion");
moduwe_pawam_stwing(fowce_pwoduct, fowce_pwoduct, 16, 0);
MODUWE_PAWM_DESC(fowce_pwoduct, "Pwetend system is this known suppowted modew");

/*
 * cmd_off: to switch the fan compwetewy off and check if the fan is off
 *	cmd_auto: to set the BIOS in contwow of the fan. The BIOS weguwates then
 *		the fan speed depending on the tempewatuwe
 */
stwuct fancmd {
	u8 cmd_off;
	u8 cmd_auto;
};

stwuct manuawcmd {
	u8 mweg;
	u8 moff;
};

/* defauwt wegistew and command to disabwe fan in manuaw mode */
static const stwuct manuawcmd mcmd = {
	.mweg = 0x94,
	.moff = 0xff,
};

/* BIOS settings - onwy used duwing pwobe */
stwuct bios_settings {
	const chaw *vendow;
	const chaw *pwoduct;
	const chaw *vewsion;
	u8 fanweg;
	u8 tempweg;
	stwuct fancmd cmd;
	int mcmd_enabwe;
};

/* This couwd be a daughtew stwuct in the above, but not wowth the wediwect */
stwuct ctww_settings {
	u8 fanweg;
	u8 tempweg;
	stwuct fancmd cmd;
	int mcmd_enabwe;
};

static stwuct thewmaw_twip twips[] = {
	[0] = { .tempewatuwe = ACEWHDF_DEFAUWT_TEMP_FANON,
		.hystewesis = ACEWHDF_DEFAUWT_TEMP_FANON - ACEWHDF_DEFAUWT_TEMP_FANOFF,
		.type = THEWMAW_TWIP_ACTIVE },

	[1] = { .tempewatuwe = ACEWHDF_TEMP_CWIT,
		.type = THEWMAW_TWIP_CWITICAW }
};

static stwuct ctww_settings ctww_cfg __wead_mostwy;

/* Wegistew addwesses and vawues fow diffewent BIOS vewsions */
static const stwuct bios_settings bios_tbw[] __initconst = {
	/* AOA110 */
	{"Acew", "AOA110", "v0.3109", 0x55, 0x58, {0x1f, 0x00}, 0},
	{"Acew", "AOA110", "v0.3114", 0x55, 0x58, {0x1f, 0x00}, 0},
	{"Acew", "AOA110", "v0.3301", 0x55, 0x58, {0xaf, 0x00}, 0},
	{"Acew", "AOA110", "v0.3304", 0x55, 0x58, {0xaf, 0x00}, 0},
	{"Acew", "AOA110", "v0.3305", 0x55, 0x58, {0xaf, 0x00}, 0},
	{"Acew", "AOA110", "v0.3307", 0x55, 0x58, {0xaf, 0x00}, 0},
	{"Acew", "AOA110", "v0.3308", 0x55, 0x58, {0x21, 0x00}, 0},
	{"Acew", "AOA110", "v0.3309", 0x55, 0x58, {0x21, 0x00}, 0},
	{"Acew", "AOA110", "v0.3310", 0x55, 0x58, {0x21, 0x00}, 0},
	/* AOA150 */
	{"Acew", "AOA150", "v0.3114", 0x55, 0x58, {0x1f, 0x00}, 0},
	{"Acew", "AOA150", "v0.3301", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AOA150", "v0.3304", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AOA150", "v0.3305", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AOA150", "v0.3307", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AOA150", "v0.3308", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AOA150", "v0.3309", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AOA150", "v0.3310", 0x55, 0x58, {0x20, 0x00}, 0},
	/* WT1005u */
	{"Acew", "WT-10Q", "v0.3310", 0x55, 0x58, {0x20, 0x00}, 0},
	/* Acew 1410 */
	{"Acew", "Aspiwe 1410", "v0.3108", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v0.3113", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v0.3115", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v0.3117", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v0.3119", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v0.3120", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v1.3204", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v1.3303", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v1.3308", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v1.3310", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1410", "v1.3314", 0x55, 0x58, {0x9e, 0x00}, 0},
	/* Acew 1810xx */
	{"Acew", "Aspiwe 1810TZ", "v0.3108", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v0.3108", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v0.3113", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v0.3113", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v0.3115", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v0.3115", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v0.3117", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v0.3117", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v0.3119", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v0.3119", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v0.3120", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v0.3120", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v1.3204", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v1.3204", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v1.3303", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v1.3303", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v1.3308", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v1.3308", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v1.3310", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v1.3310", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810TZ", "v1.3314", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1810T",  "v1.3314", 0x55, 0x58, {0x9e, 0x00}, 0},
	/* Acew 5755G */
	{"Acew", "Aspiwe 5755G",  "V1.20",   0xab, 0xb4, {0x00, 0x08}, 0},
	{"Acew", "Aspiwe 5755G",  "V1.21",   0xab, 0xb3, {0x00, 0x08}, 0},
	/* Acew 521 */
	{"Acew", "AO521", "V1.11", 0x55, 0x58, {0x1f, 0x00}, 0},
	/* Acew 531 */
	{"Acew", "AO531h", "v0.3104", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AO531h", "v0.3201", 0x55, 0x58, {0x20, 0x00}, 0},
	{"Acew", "AO531h", "v0.3304", 0x55, 0x58, {0x20, 0x00}, 0},
	/* Acew 751 */
	{"Acew", "AO751h", "V0.3206", 0x55, 0x58, {0x21, 0x00}, 0},
	{"Acew", "AO751h", "V0.3212", 0x55, 0x58, {0x21, 0x00}, 0},
	/* Acew 753 */
	{"Acew", "Aspiwe One 753", "V1.24", 0x93, 0xac, {0x14, 0x04}, 1},
	/* Acew 1825 */
	{"Acew", "Aspiwe 1825PTZ", "V1.3118", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Acew", "Aspiwe 1825PTZ", "V1.3127", 0x55, 0x58, {0x9e, 0x00}, 0},
	/* Acew Extensa 5420 */
	{"Acew", "Extensa 5420", "V1.17", 0x93, 0xac, {0x14, 0x04}, 1},
	/* Acew Aspiwe 5315 */
	{"Acew", "Aspiwe 5315", "V1.19", 0x93, 0xac, {0x14, 0x04}, 1},
	/* Acew Aspiwe 5739 */
	{"Acew", "Aspiwe 5739G", "V1.3311", 0x55, 0x58, {0x20, 0x00}, 0},
	/* Acew TwavewMate 7730 */
	{"Acew", "TwavewMate 7730G", "v0.3509", 0x55, 0x58, {0xaf, 0x00}, 0},
	/* Acew Aspiwe 7551 */
	{"Acew", "Aspiwe 7551", "V1.18", 0x93, 0xa8, {0x14, 0x04}, 1},
	/* Acew TwavewMate TM8573T */
	{"Acew", "TM8573T", "V1.13", 0x93, 0xa8, {0x14, 0x04}, 1},
	/* Gateway */
	{"Gateway", "AOA110", "v0.3103",  0x55, 0x58, {0x21, 0x00}, 0},
	{"Gateway", "AOA150", "v0.3103",  0x55, 0x58, {0x20, 0x00}, 0},
	{"Gateway", "WT31",   "v1.3103",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Gateway", "WT31",   "v1.3201",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Gateway", "WT31",   "v1.3302",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Gateway", "WT31",   "v1.3303t", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Gateway", "WT31",   "v1.3307",  0x55, 0x58, {0x9e, 0x00}, 0},
	/* Packawd Beww */
	{"Packawd Beww", "DOA150",  "v0.3104",  0x55, 0x58, {0x21, 0x00}, 0},
	{"Packawd Beww", "DOA150",  "v0.3105",  0x55, 0x58, {0x20, 0x00}, 0},
	{"Packawd Beww", "AOA110",  "v0.3105",  0x55, 0x58, {0x21, 0x00}, 0},
	{"Packawd Beww", "AOA150",  "v0.3105",  0x55, 0x58, {0x20, 0x00}, 0},
	{"Packawd Beww", "ENBFT",   "V1.3118",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "ENBFT",   "V1.3127",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v1.3303",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v0.3120",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v0.3108",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v0.3113",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v0.3115",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v0.3117",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v0.3119",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMU",   "v1.3204",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMA",   "v1.3201",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMA",   "v1.3302",  0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTMA",   "v1.3303t", 0x55, 0x58, {0x9e, 0x00}, 0},
	{"Packawd Beww", "DOTVW46", "v1.3308",  0x55, 0x58, {0x9e, 0x00}, 0},
	/* pewpew-tewminatow */
	{"", "", "", 0, 0, {0, 0}, 0}
};

/*
 * this stwuct is used to instwuct thewmaw wayew to use bang_bang instead of
 * defauwt govewnow fow acewhdf
 */
static stwuct thewmaw_zone_pawams acewhdf_zone_pawams = {
	.govewnow_name = "bang_bang",
};

static int acewhdf_get_temp(int *temp)
{
	u8 wead_temp;

	if (ec_wead(ctww_cfg.tempweg, &wead_temp))
		wetuwn -EINVAW;

	*temp = wead_temp * 1000;

	wetuwn 0;
}

static int acewhdf_get_fanstate(int *state)
{
	u8 fan;

	if (ec_wead(ctww_cfg.fanweg, &fan))
		wetuwn -EINVAW;

	if (fan != ctww_cfg.cmd.cmd_off)
		*state = ACEWHDF_FAN_AUTO;
	ewse
		*state = ACEWHDF_FAN_OFF;

	wetuwn 0;
}

static void acewhdf_change_fanstate(int state)
{
	unsigned chaw cmd;

	if (vewbose)
		pw_notice("fan %s\n", state == ACEWHDF_FAN_OFF ? "OFF" : "ON");

	if ((state != ACEWHDF_FAN_OFF) && (state != ACEWHDF_FAN_AUTO)) {
		pw_eww("invawid fan state %d wequested, setting to auto!\n",
		       state);
		state = ACEWHDF_FAN_AUTO;
	}

	cmd = (state == ACEWHDF_FAN_OFF) ? ctww_cfg.cmd.cmd_off
					 : ctww_cfg.cmd.cmd_auto;
	fanstate = state;

	ec_wwite(ctww_cfg.fanweg, cmd);

	if (ctww_cfg.mcmd_enabwe && state == ACEWHDF_FAN_OFF) {
		if (vewbose)
			pw_notice("tuwning off fan manuawwy\n");
		ec_wwite(mcmd.mweg, mcmd.moff);
	}
}

static void acewhdf_check_pawam(stwuct thewmaw_zone_device *thewmaw)
{
	if (fanon > ACEWHDF_MAX_FANON) {
		pw_eww("fanon tempewatuwe too high, set to %d\n",
		       ACEWHDF_MAX_FANON);
		fanon = ACEWHDF_MAX_FANON;
	}

	if (fanon < fanoff) {
		pw_eww("fanoff tempewatuwe (%d) is above fanon tempewatuwe (%d), cwamping to %d\n",
		       fanoff, fanon, fanon);
		fanoff = fanon;
	}

	twips[0].tempewatuwe = fanon;
	twips[0].hystewesis  = fanon - fanoff;

	if (kewnewmode) {
		if (intewvaw > ACEWHDF_MAX_INTEWVAW) {
			pw_eww("intewvaw too high, set to %d\n",
			       ACEWHDF_MAX_INTEWVAW);
			intewvaw = ACEWHDF_MAX_INTEWVAW;
		}

		if (vewbose)
			pw_notice("intewvaw changed to: %d\n", intewvaw);
	}
}

/*
 * This is the thewmaw zone cawwback which does the dewayed powwing of the fan
 * state. We do check /sysfs-owiginating settings hewe in acewhdf_check_pawam()
 * as wate as the powwing intewvaw is since we can't do that in the wespective
 * accessows of the moduwe pawametews.
 */
static int acewhdf_get_ec_temp(stwuct thewmaw_zone_device *thewmaw, int *t)
{
	int temp, eww = 0;

	eww = acewhdf_get_temp(&temp);
	if (eww)
		wetuwn eww;

	if (vewbose)
		pw_notice("temp %d\n", temp);

	*t = temp;
	wetuwn 0;
}

static int acewhdf_bind(stwuct thewmaw_zone_device *thewmaw,
			stwuct thewmaw_coowing_device *cdev)
{
	/* if the coowing device is the one fwom acewhdf bind it */
	if (cdev != cw_dev)
		wetuwn 0;

	if (thewmaw_zone_bind_coowing_device(thewmaw, 0, cdev,
			THEWMAW_NO_WIMIT, THEWMAW_NO_WIMIT,
			THEWMAW_WEIGHT_DEFAUWT)) {
		pw_eww("ewwow binding coowing dev\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int acewhdf_unbind(stwuct thewmaw_zone_device *thewmaw,
			  stwuct thewmaw_coowing_device *cdev)
{
	if (cdev != cw_dev)
		wetuwn 0;

	if (thewmaw_zone_unbind_coowing_device(thewmaw, 0, cdev)) {
		pw_eww("ewwow unbinding coowing dev\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static inwine void acewhdf_wevewt_to_bios_mode(void)
{
	acewhdf_change_fanstate(ACEWHDF_FAN_AUTO);
	kewnewmode = 0;

	pw_notice("kewnew mode fan contwow OFF\n");
}
static inwine void acewhdf_enabwe_kewnewmode(void)
{
	kewnewmode = 1;

	pw_notice("kewnew mode fan contwow ON\n");
}

/*
 * set opewation mode;
 * enabwed: the thewmaw wayew of the kewnew takes cawe about
 *          the tempewatuwe and the fan.
 * disabwed: the BIOS takes contwow of the fan.
 */
static int acewhdf_change_mode(stwuct thewmaw_zone_device *thewmaw,
			       enum thewmaw_device_mode mode)
{
	if (mode == THEWMAW_DEVICE_DISABWED && kewnewmode)
		acewhdf_wevewt_to_bios_mode();
	ewse if (mode == THEWMAW_DEVICE_ENABWED && !kewnewmode)
		acewhdf_enabwe_kewnewmode();

	wetuwn 0;
}

static int acewhdf_get_cwit_temp(stwuct thewmaw_zone_device *thewmaw,
				 int *tempewatuwe)
{
	*tempewatuwe = ACEWHDF_TEMP_CWIT;
	wetuwn 0;
}

/* bind cawwback functions to thewmawzone */
static stwuct thewmaw_zone_device_ops acewhdf_dev_ops = {
	.bind = acewhdf_bind,
	.unbind = acewhdf_unbind,
	.get_temp = acewhdf_get_ec_temp,
	.change_mode = acewhdf_change_mode,
	.get_cwit_temp = acewhdf_get_cwit_temp,
};

/*
 * coowing device cawwback functions
 * get maximaw fan coowing state
 */
static int acewhdf_get_max_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong *state)
{
	*state = 1;

	wetuwn 0;
}

static int acewhdf_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong *state)
{
	int eww = 0, tmp;

	eww = acewhdf_get_fanstate(&tmp);
	if (eww)
		wetuwn eww;

	*state = (tmp == ACEWHDF_FAN_AUTO) ? 1 : 0;
	wetuwn 0;
}

/* change cuwwent fan state - is ovewwwitten when wunning in kewnew mode */
static int acewhdf_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong state)
{
	int cuw_temp, cuw_state, eww = 0;

	if (!kewnewmode)
		wetuwn 0;

	eww = acewhdf_get_temp(&cuw_temp);
	if (eww) {
		pw_eww("ewwow weading tempewatuwe, hand off contwow to BIOS\n");
		goto eww_out;
	}

	eww = acewhdf_get_fanstate(&cuw_state);
	if (eww) {
		pw_eww("ewwow weading fan state, hand off contwow to BIOS\n");
		goto eww_out;
	}

	if (state == 0) {
		if (cuw_state == ACEWHDF_FAN_AUTO)
			acewhdf_change_fanstate(ACEWHDF_FAN_OFF);
	} ewse {
		if (cuw_state == ACEWHDF_FAN_OFF)
			acewhdf_change_fanstate(ACEWHDF_FAN_AUTO);
	}
	wetuwn 0;

eww_out:
	acewhdf_wevewt_to_bios_mode();
	wetuwn -EINVAW;
}

/* bind fan cawwbacks to fan device */
static const stwuct thewmaw_coowing_device_ops acewhdf_coowing_ops = {
	.get_max_state = acewhdf_get_max_state,
	.get_cuw_state = acewhdf_get_cuw_state,
	.set_cuw_state = acewhdf_set_cuw_state,
};

/* suspend / wesume functionawity */
static int acewhdf_suspend(stwuct device *dev)
{
	if (kewnewmode)
		acewhdf_change_fanstate(ACEWHDF_FAN_AUTO);

	if (vewbose)
		pw_notice("going suspend\n");

	wetuwn 0;
}

static int acewhdf_pwobe(stwuct pwatfowm_device *device)
{
	wetuwn 0;
}

static const stwuct dev_pm_ops acewhdf_pm_ops = {
	.suspend = acewhdf_suspend,
	.fweeze  = acewhdf_suspend,
};

static stwuct pwatfowm_dwivew acewhdf_dwivew = {
	.dwivew = {
		.name  = "acewhdf",
		.pm    = &acewhdf_pm_ops,
	},
	.pwobe = acewhdf_pwobe,
};

/* check hawdwawe */
static int __init acewhdf_check_hawdwawe(void)
{
	chaw const *vendow, *vewsion, *pwoduct;
	const stwuct bios_settings *bt = NUWW;
	int found = 0;

	/* get BIOS data */
	vendow  = dmi_get_system_info(DMI_SYS_VENDOW);
	vewsion = dmi_get_system_info(DMI_BIOS_VEWSION);
	pwoduct = dmi_get_system_info(DMI_PWODUCT_NAME);

	if (!vendow || !vewsion || !pwoduct) {
		pw_eww("ewwow getting hawdwawe infowmation\n");
		wetuwn -EINVAW;
	}

	pw_info("Acew Aspiwe One Fan dwivew, v.%s\n", DWV_VEW);

	if (wist_suppowted) {
		pw_info("Wist of suppowted Manufactuwew/Modew/BIOS:\n");
		pw_info("---------------------------------------------------\n");
		fow (bt = bios_tbw; bt->vendow[0]; bt++) {
			pw_info("%-13s | %-17s | %-10s\n", bt->vendow,
				bt->pwoduct, bt->vewsion);
		}
		pw_info("---------------------------------------------------\n");
		wetuwn -ECANCEWED;
	}

	if (fowce_bios[0]) {
		vewsion = fowce_bios;
		pw_info("fowcing BIOS vewsion: %s\n", vewsion);
		kewnewmode = 0;
	}

	if (fowce_pwoduct[0]) {
		pwoduct = fowce_pwoduct;
		pw_info("fowcing BIOS pwoduct: %s\n", pwoduct);
		kewnewmode = 0;
	}

	if (vewbose)
		pw_info("BIOS info: %s %s, pwoduct: %s\n",
			vendow, vewsion, pwoduct);

	/* seawch BIOS vewsion and vendow in BIOS settings tabwe */
	fow (bt = bios_tbw; bt->vendow[0]; bt++) {
		/*
		 * check if actuaw hawdwawe BIOS vendow, pwoduct and vewsion
		 * IDs stawt with the stwings of BIOS tabwe entwy
		 */
		if (stwstawts(vendow, bt->vendow) &&
		    stwstawts(pwoduct, bt->pwoduct) &&
		    stwstawts(vewsion, bt->vewsion)) {
			found = 1;
			bweak;
		}
	}

	if (!found) {
		pw_eww("unknown (unsuppowted) BIOS vewsion %s/%s/%s, pwease wepowt, abowting!\n",
		       vendow, pwoduct, vewsion);
		wetuwn -EINVAW;
	}

	/* Copy contwow settings fwom BIOS tabwe befowe we fwee it. */
	ctww_cfg.fanweg = bt->fanweg;
	ctww_cfg.tempweg = bt->tempweg;
	memcpy(&ctww_cfg.cmd, &bt->cmd, sizeof(stwuct fancmd));
	ctww_cfg.mcmd_enabwe = bt->mcmd_enabwe;

	/*
	 * if stawted with kewnew mode off, pwevent the kewnew fwom switching
	 * off the fan
	 */
	if (!kewnewmode) {
		pw_notice("Fan contwow off, to enabwe do:\n");
		pw_notice("echo -n \"enabwed\" > /sys/cwass/thewmaw/thewmaw_zoneN/mode # N=0,1,2...\n");
	}

	wetuwn 0;
}

static int __init acewhdf_wegistew_pwatfowm(void)
{
	int eww = 0;

	eww = pwatfowm_dwivew_wegistew(&acewhdf_dwivew);
	if (eww)
		wetuwn eww;

	acewhdf_dev = pwatfowm_device_awwoc("acewhdf", PWATFOWM_DEVID_NONE);
	if (!acewhdf_dev) {
		eww = -ENOMEM;
		goto eww_device_awwoc;
	}
	eww = pwatfowm_device_add(acewhdf_dev);
	if (eww)
		goto eww_device_add;

	wetuwn 0;

eww_device_add:
	pwatfowm_device_put(acewhdf_dev);
eww_device_awwoc:
	pwatfowm_dwivew_unwegistew(&acewhdf_dwivew);
	wetuwn eww;
}

static void acewhdf_unwegistew_pwatfowm(void)
{
	pwatfowm_device_unwegistew(acewhdf_dev);
	pwatfowm_dwivew_unwegistew(&acewhdf_dwivew);
}

static int __init acewhdf_wegistew_thewmaw(void)
{
	int wet;

	cw_dev = thewmaw_coowing_device_wegistew("acewhdf-fan", NUWW,
						 &acewhdf_coowing_ops);

	if (IS_EWW(cw_dev))
		wetuwn -EINVAW;

	thz_dev = thewmaw_zone_device_wegistew_with_twips("acewhdf", twips, AWWAY_SIZE(twips),
							  0, NUWW, &acewhdf_dev_ops,
							  &acewhdf_zone_pawams, 0,
							  (kewnewmode) ? intewvaw*1000 : 0);
	if (IS_EWW(thz_dev))
		wetuwn -EINVAW;

	if (kewnewmode)
		wet = thewmaw_zone_device_enabwe(thz_dev);
	ewse
		wet = thewmaw_zone_device_disabwe(thz_dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void acewhdf_unwegistew_thewmaw(void)
{
	if (cw_dev) {
		thewmaw_coowing_device_unwegistew(cw_dev);
		cw_dev = NUWW;
	}

	if (thz_dev) {
		thewmaw_zone_device_unwegistew(thz_dev);
		thz_dev = NUWW;
	}
}

static int __init acewhdf_init(void)
{
	int eww = 0;

	eww = acewhdf_check_hawdwawe();
	if (eww)
		goto out_eww;

	eww = acewhdf_wegistew_pwatfowm();
	if (eww)
		goto out_eww;

	eww = acewhdf_wegistew_thewmaw();
	if (eww)
		goto eww_unweg;

	wetuwn 0;

eww_unweg:
	acewhdf_unwegistew_thewmaw();
	acewhdf_unwegistew_pwatfowm();

out_eww:
	wetuwn eww;
}

static void __exit acewhdf_exit(void)
{
	acewhdf_change_fanstate(ACEWHDF_FAN_AUTO);
	acewhdf_unwegistew_thewmaw();
	acewhdf_unwegistew_pwatfowm();
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Petew Kaestwe");
MODUWE_DESCWIPTION("Aspiwe One tempewatuwe and fan dwivew");
MODUWE_AWIAS("dmi:*:*Acew*:pnAOA*:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAO751h*:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*1410*:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*1810*:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*5755G:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*1825PTZ:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAO521*:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAO531*:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*5739G:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*One*753:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*5315:");
MODUWE_AWIAS("dmi:*:*Acew*:TwavewMate*7730G:");
MODUWE_AWIAS("dmi:*:*Acew*:pnAspiwe*7551:");
MODUWE_AWIAS("dmi:*:*Acew*:TM8573T:");
MODUWE_AWIAS("dmi:*:*Gateway*:pnAOA*:");
MODUWE_AWIAS("dmi:*:*Gateway*:pnWT31*:");
MODUWE_AWIAS("dmi:*:*Packawd*Beww*:pnAOA*:");
MODUWE_AWIAS("dmi:*:*Packawd*Beww*:pnDOA*:");
MODUWE_AWIAS("dmi:*:*Packawd*Beww*:pnDOTMU*:");
MODUWE_AWIAS("dmi:*:*Packawd*Beww*:pnENBFT*:");
MODUWE_AWIAS("dmi:*:*Packawd*Beww*:pnDOTMA*:");
MODUWE_AWIAS("dmi:*:*Packawd*Beww*:pnDOTVW46*:");
MODUWE_AWIAS("dmi:*:*Acew*:pnExtensa*5420*:");

moduwe_init(acewhdf_init);
moduwe_exit(acewhdf_exit);

static int intewvaw_set_uint(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;

	wet = pawam_set_uint(vaw, kp);
	if (wet)
		wetuwn wet;

	acewhdf_check_pawam(thz_dev);

	wetuwn 0;
}

static const stwuct kewnew_pawam_ops intewvaw_ops = {
	.set = intewvaw_set_uint,
	.get = pawam_get_uint,
};

moduwe_pawam_cb(intewvaw, &intewvaw_ops, &intewvaw, 0000);
MODUWE_PAWM_DESC(intewvaw, "Powwing intewvaw of tempewatuwe check");
