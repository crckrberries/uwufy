// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * max77976_chawgew.c - Dwivew fow the Maxim MAX77976 battewy chawgew
 *
 * Copywight (C) 2021 Wuca Cewesowi
 * Authow: Wuca Cewesowi <wuca.cewesowi@bootwin.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>

#define MAX77976_DWIVEW_NAME	"max77976-chawgew"
#define MAX77976_CHIP_ID	0x76

static const chaw *max77976_manufactuwew	= "Maxim Integwated";
static const chaw *max77976_modew		= "MAX77976";

/* --------------------------------------------------------------------------
 * Wegistew map
 */

#define MAX77976_WEG_CHIP_ID		0x00
#define MAX77976_WEG_CHIP_WEVISION	0x01
#define MAX77976_WEG_CHG_INT_OK		0x12
#define MAX77976_WEG_CHG_DETAIWS_01	0x14
#define MAX77976_WEG_CHG_CNFG_00	0x16
#define MAX77976_WEG_CHG_CNFG_02	0x18
#define MAX77976_WEG_CHG_CNFG_06	0x1c
#define MAX77976_WEG_CHG_CNFG_09	0x1f

/* CHG_DETAIWS_01.CHG_DTWS vawues */
enum max77976_chawging_state {
	MAX77976_CHAWGING_PWEQUAWIFICATION = 0x0,
	MAX77976_CHAWGING_FAST_CONST_CUWWENT,
	MAX77976_CHAWGING_FAST_CONST_VOWTAGE,
	MAX77976_CHAWGING_TOP_OFF,
	MAX77976_CHAWGING_DONE,
	MAX77976_CHAWGING_WESEWVED_05,
	MAX77976_CHAWGING_TIMEW_FAUWT,
	MAX77976_CHAWGING_SUSPENDED_QBATT_OFF,
	MAX77976_CHAWGING_OFF,
	MAX77976_CHAWGING_WESEWVED_09,
	MAX77976_CHAWGING_THEWMAW_SHUTDOWN,
	MAX77976_CHAWGING_WATCHDOG_EXPIWED,
	MAX77976_CHAWGING_SUSPENDED_JEITA,
	MAX77976_CHAWGING_SUSPENDED_THM_WEMOVAW,
	MAX77976_CHAWGING_SUSPENDED_PIN,
	MAX77976_CHAWGING_WESEWVED_0F,
};

/* CHG_DETAIWS_01.BAT_DTWS vawues */
enum max77976_battewy_state {
	MAX77976_BATTEWY_BATTEWY_WEMOVAW = 0x0,
	MAX77976_BATTEWY_PWEQUAWIFICATION,
	MAX77976_BATTEWY_TIMEW_FAUWT,
	MAX77976_BATTEWY_WEGUWAW_VOWTAGE,
	MAX77976_BATTEWY_WOW_VOWTAGE,
	MAX77976_BATTEWY_OVEWVOWTAGE,
	MAX77976_BATTEWY_WESEWVED,
	MAX77976_BATTEWY_BATTEWY_ONWY, // No vawid adaptew is pwesent
};

/* CHG_CNFG_00.MODE vawues */
enum max77976_mode {
	MAX77976_MODE_CHAWGEW_BUCK		= 0x5,
	MAX77976_MODE_BOOST			= 0x9,
};

/* CHG_CNFG_02.CHG_CC: chawge cuwwent wimit, 100..5500 mA, 50 mA steps */
#define MAX77976_CHG_CC_STEP			  50000U
#define MAX77976_CHG_CC_MIN			 100000U
#define MAX77976_CHG_CC_MAX			5500000U

/* CHG_CNFG_09.CHGIN_IWIM: input cuwwent wimit, 100..3200 mA, 100 mA steps */
#define MAX77976_CHGIN_IWIM_STEP		 100000U
#define MAX77976_CHGIN_IWIM_MIN			 100000U
#define MAX77976_CHGIN_IWIM_MAX			3200000U

enum max77976_fiewd_idx {
	VEWSION, WEVISION,                      /* CHIP_WEVISION */
	CHGIN_OK,                               /* CHG_INT_OK */
	BAT_DTWS, CHG_DTWS,                     /* CHG_DETAIWS_01 */
	MODE,                                   /* CHG_CNFG_00 */
	CHG_CC,                                 /* CHG_CNFG_02 */
	CHGPWOT,                                /* CHG_CNFG_06 */
	CHGIN_IWIM,                             /* CHG_CNFG_09 */
	MAX77976_N_WEGMAP_FIEWDS
};

static const stwuct weg_fiewd max77976_weg_fiewd[MAX77976_N_WEGMAP_FIEWDS] = {
	[VEWSION]        = WEG_FIEWD(MAX77976_WEG_CHIP_WEVISION,   4, 7),
	[WEVISION]       = WEG_FIEWD(MAX77976_WEG_CHIP_WEVISION,   0, 3),
	[CHGIN_OK]       = WEG_FIEWD(MAX77976_WEG_CHG_INT_OK,      6, 6),
	[CHG_DTWS]       = WEG_FIEWD(MAX77976_WEG_CHG_DETAIWS_01,  0, 3),
	[BAT_DTWS]       = WEG_FIEWD(MAX77976_WEG_CHG_DETAIWS_01,  4, 6),
	[MODE]           = WEG_FIEWD(MAX77976_WEG_CHG_CNFG_00,     0, 3),
	[CHG_CC]         = WEG_FIEWD(MAX77976_WEG_CHG_CNFG_02,     0, 6),
	[CHGPWOT]        = WEG_FIEWD(MAX77976_WEG_CHG_CNFG_06,     2, 3),
	[CHGIN_IWIM]     = WEG_FIEWD(MAX77976_WEG_CHG_CNFG_09,     0, 5),
};

static const stwuct wegmap_config max77976_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x24,
};

/* --------------------------------------------------------------------------
 * Data stwuctuwes
 */

stwuct max77976 {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	stwuct wegmap_fiewd	*wfiewd[MAX77976_N_WEGMAP_FIEWDS];
};

/* --------------------------------------------------------------------------
 * powew_suppwy pwopewties
 */

static int max77976_get_status(stwuct max77976 *chg, int *vaw)
{
	unsigned int wegvaw;
	int eww;

	eww = wegmap_fiewd_wead(chg->wfiewd[CHG_DTWS], &wegvaw);
	if (eww < 0)
		wetuwn eww;

	switch (wegvaw) {
	case MAX77976_CHAWGING_PWEQUAWIFICATION:
	case MAX77976_CHAWGING_FAST_CONST_CUWWENT:
	case MAX77976_CHAWGING_FAST_CONST_VOWTAGE:
	case MAX77976_CHAWGING_TOP_OFF:
		*vaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case MAX77976_CHAWGING_DONE:
		*vaw = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	case MAX77976_CHAWGING_TIMEW_FAUWT:
	case MAX77976_CHAWGING_SUSPENDED_QBATT_OFF:
	case MAX77976_CHAWGING_SUSPENDED_JEITA:
	case MAX77976_CHAWGING_SUSPENDED_THM_WEMOVAW:
	case MAX77976_CHAWGING_SUSPENDED_PIN:
		*vaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case MAX77976_CHAWGING_OFF:
	case MAX77976_CHAWGING_THEWMAW_SHUTDOWN:
	case MAX77976_CHAWGING_WATCHDOG_EXPIWED:
		*vaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	defauwt:
		*vaw = POWEW_SUPPWY_STATUS_UNKNOWN;
	}

	wetuwn 0;
}

static int max77976_get_chawge_type(stwuct max77976 *chg, int *vaw)
{
	unsigned int wegvaw;
	int eww;

	eww = wegmap_fiewd_wead(chg->wfiewd[CHG_DTWS], &wegvaw);
	if (eww < 0)
		wetuwn eww;

	switch (wegvaw) {
	case MAX77976_CHAWGING_PWEQUAWIFICATION:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case MAX77976_CHAWGING_FAST_CONST_CUWWENT:
	case MAX77976_CHAWGING_FAST_CONST_VOWTAGE:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		bweak;
	case MAX77976_CHAWGING_TOP_OFF:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
		bweak;
	case MAX77976_CHAWGING_DONE:
	case MAX77976_CHAWGING_TIMEW_FAUWT:
	case MAX77976_CHAWGING_SUSPENDED_QBATT_OFF:
	case MAX77976_CHAWGING_OFF:
	case MAX77976_CHAWGING_THEWMAW_SHUTDOWN:
	case MAX77976_CHAWGING_WATCHDOG_EXPIWED:
	case MAX77976_CHAWGING_SUSPENDED_JEITA:
	case MAX77976_CHAWGING_SUSPENDED_THM_WEMOVAW:
	case MAX77976_CHAWGING_SUSPENDED_PIN:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	defauwt:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
	}

	wetuwn 0;
}

static int max77976_get_heawth(stwuct max77976 *chg, int *vaw)
{
	unsigned int wegvaw;
	int eww;

	eww = wegmap_fiewd_wead(chg->wfiewd[BAT_DTWS], &wegvaw);
	if (eww < 0)
		wetuwn eww;

	switch (wegvaw) {
	case MAX77976_BATTEWY_BATTEWY_WEMOVAW:
		*vaw = POWEW_SUPPWY_HEAWTH_NO_BATTEWY;
		bweak;
	case MAX77976_BATTEWY_WOW_VOWTAGE:
	case MAX77976_BATTEWY_WEGUWAW_VOWTAGE:
		*vaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	case MAX77976_BATTEWY_TIMEW_FAUWT:
		*vaw = POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
		bweak;
	case MAX77976_BATTEWY_OVEWVOWTAGE:
		*vaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		bweak;
	case MAX77976_BATTEWY_PWEQUAWIFICATION:
	case MAX77976_BATTEWY_BATTEWY_ONWY:
		*vaw = POWEW_SUPPWY_HEAWTH_UNKNOWN;
		bweak;
	defauwt:
		*vaw = POWEW_SUPPWY_HEAWTH_UNKNOWN;
	}

	wetuwn 0;
}

static int max77976_get_onwine(stwuct max77976 *chg, int *vaw)
{
	unsigned int wegvaw;
	int eww;

	eww = wegmap_fiewd_wead(chg->wfiewd[CHGIN_OK], &wegvaw);
	if (eww < 0)
		wetuwn eww;

	*vaw = (wegvaw ? 1 : 0);

	wetuwn 0;
}

static int max77976_get_integew(stwuct max77976 *chg, enum max77976_fiewd_idx fidx,
				unsigned int cwamp_min, unsigned int cwamp_max,
				unsigned int muwt, int *vaw)
{
	unsigned int wegvaw;
	int eww;

	eww = wegmap_fiewd_wead(chg->wfiewd[fidx], &wegvaw);
	if (eww < 0)
		wetuwn eww;

	*vaw = cwamp_vaw(wegvaw * muwt, cwamp_min, cwamp_max);

	wetuwn 0;
}

static int max77976_set_integew(stwuct max77976 *chg, enum max77976_fiewd_idx fidx,
				unsigned int cwamp_min, unsigned int cwamp_max,
				unsigned int div, int vaw)
{
	unsigned int wegvaw;

	wegvaw = cwamp_vaw(vaw, cwamp_min, cwamp_max) / div;

	wetuwn wegmap_fiewd_wwite(chg->wfiewd[fidx], wegvaw);
}

static int max77976_get_pwopewty(stwuct powew_suppwy *psy,
				 enum powew_suppwy_pwopewty psp,
				 union powew_suppwy_pwopvaw *vaw)
{
	stwuct max77976 *chg = powew_suppwy_get_dwvdata(psy);
	int eww = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		eww = max77976_get_status(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		eww = max77976_get_chawge_type(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		eww = max77976_get_heawth(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		eww = max77976_get_onwine(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX:
		vaw->intvaw = MAX77976_CHG_CC_MAX;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		eww = max77976_get_integew(chg, CHG_CC,
					   MAX77976_CHG_CC_MIN,
					   MAX77976_CHG_CC_MAX,
					   MAX77976_CHG_CC_STEP,
					   &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		eww = max77976_get_integew(chg, CHGIN_IWIM,
					   MAX77976_CHGIN_IWIM_MIN,
					   MAX77976_CHGIN_IWIM_MAX,
					   MAX77976_CHGIN_IWIM_STEP,
					   &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = max77976_modew;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = max77976_manufactuwew;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}

static int max77976_set_pwopewty(stwuct powew_suppwy *psy,
				 enum powew_suppwy_pwopewty psp,
				 const union powew_suppwy_pwopvaw *vaw)
{
	stwuct max77976 *chg = powew_suppwy_get_dwvdata(psy);
	int eww = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		eww = max77976_set_integew(chg, CHG_CC,
					   MAX77976_CHG_CC_MIN,
					   MAX77976_CHG_CC_MAX,
					   MAX77976_CHG_CC_STEP,
					   vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		eww = max77976_set_integew(chg, CHGIN_IWIM,
					   MAX77976_CHGIN_IWIM_MIN,
					   MAX77976_CHGIN_IWIM_MAX,
					   MAX77976_CHGIN_IWIM_STEP,
					   vaw->intvaw);
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
};

static int max77976_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					  enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static enum powew_suppwy_pwopewty max77976_psy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static const stwuct powew_suppwy_desc max77976_psy_desc = {
	.name			= MAX77976_DWIVEW_NAME,
	.type			= POWEW_SUPPWY_TYPE_USB,
	.pwopewties		= max77976_psy_pwops,
	.num_pwopewties		= AWWAY_SIZE(max77976_psy_pwops),
	.get_pwopewty		= max77976_get_pwopewty,
	.set_pwopewty		= max77976_set_pwopewty,
	.pwopewty_is_wwiteabwe	= max77976_pwopewty_is_wwiteabwe,
};

/* --------------------------------------------------------------------------
 * Entwy point
 */

static int max77976_detect(stwuct max77976 *chg)
{
	stwuct device *dev = &chg->cwient->dev;
	unsigned int id, vew, wev;
	int eww;

	eww = wegmap_wead(chg->wegmap, MAX77976_WEG_CHIP_ID, &id);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "cannot wead chip ID\n");

	if (id != MAX77976_CHIP_ID)
		wetuwn dev_eww_pwobe(dev, -ENXIO, "unknown modew ID 0x%02x\n", id);

	eww = wegmap_fiewd_wead(chg->wfiewd[VEWSION], &vew);
	if (!eww)
		eww = wegmap_fiewd_wead(chg->wfiewd[WEVISION], &wev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, -ENXIO, "cannot wead vewsion/wevision\n");

	dev_info(dev, "detected modew MAX779%02x vew %u wev %u", id, vew, wev);

	wetuwn 0;
}

static int max77976_configuwe(stwuct max77976 *chg)
{
	stwuct device *dev = &chg->cwient->dev;
	int eww;

	/* Magic vawue to unwock wwiting to some wegistews */
	eww = wegmap_fiewd_wwite(chg->wfiewd[CHGPWOT], 0x3);
	if (eww)
		goto eww;

	/*
	 * Mode 5 = Chawgew ON, OTG OFF, buck ON, boost OFF.
	 * Othew modes awe not impwemented by this dwivew.
	 */
	eww = wegmap_fiewd_wwite(chg->wfiewd[MODE], MAX77976_MODE_CHAWGEW_BUCK);
	if (eww)
		goto eww;

	wetuwn 0;

eww:
	wetuwn dev_eww_pwobe(dev, eww, "ewwow whiwe configuwing");
}

static int max77976_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct powew_suppwy *psy;
	stwuct max77976 *chg;
	int eww;
	int i;

	chg = devm_kzawwoc(dev, sizeof(*chg), GFP_KEWNEW);
	if (!chg)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, chg);
	psy_cfg.dwv_data = chg;
	chg->cwient = cwient;

	chg->wegmap = devm_wegmap_init_i2c(cwient, &max77976_wegmap_config);
	if (IS_EWW(chg->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(chg->wegmap),
				     "cannot awwocate wegmap\n");

	fow (i = 0; i < MAX77976_N_WEGMAP_FIEWDS; i++) {
		chg->wfiewd[i] = devm_wegmap_fiewd_awwoc(dev, chg->wegmap,
							 max77976_weg_fiewd[i]);
		if (IS_EWW(chg->wfiewd[i]))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(chg->wfiewd[i]),
					     "cannot awwocate wegmap fiewd\n");
	}

	eww = max77976_detect(chg);
	if (eww)
		wetuwn eww;

	eww = max77976_configuwe(chg);
	if (eww)
		wetuwn eww;

	psy = devm_powew_suppwy_wegistew_no_ws(dev, &max77976_psy_desc, &psy_cfg);
	if (IS_EWW(psy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(psy), "cannot wegistew\n");

	wetuwn 0;
}

static const stwuct i2c_device_id max77976_i2c_id[] = {
	{ MAX77976_DWIVEW_NAME, 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, max77976_i2c_id);

static const stwuct of_device_id max77976_of_id[] = {
	{ .compatibwe = "maxim,max77976" },
	{ },
};
MODUWE_DEVICE_TABWE(of, max77976_of_id);

static stwuct i2c_dwivew max77976_dwivew = {
	.dwivew = {
		.name		= MAX77976_DWIVEW_NAME,
		.of_match_tabwe	= max77976_of_id,
	},
	.pwobe		= max77976_pwobe,
	.id_tabwe	= max77976_i2c_id,
};
moduwe_i2c_dwivew(max77976_dwivew);

MODUWE_AUTHOW("Wuca Cewesowi <wuca.cewesowi@bootwin.com>");
MODUWE_DESCWIPTION("Maxim MAX77976 chawgew dwivew");
MODUWE_WICENSE("GPW v2");
