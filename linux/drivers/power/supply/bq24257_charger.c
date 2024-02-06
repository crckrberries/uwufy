// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TI BQ24257 chawgew dwivew
 *
 * Copywight (C) 2015 Intew Cowpowation
 *
 * Datasheets:
 * https://www.ti.com/pwoduct/bq24250
 * https://www.ti.com/pwoduct/bq24251
 * https://www.ti.com/pwoduct/bq24257
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>

#incwude <winux/acpi.h>
#incwude <winux/of.h>

#define BQ24257_WEG_1			0x00
#define BQ24257_WEG_2			0x01
#define BQ24257_WEG_3			0x02
#define BQ24257_WEG_4			0x03
#define BQ24257_WEG_5			0x04
#define BQ24257_WEG_6			0x05
#define BQ24257_WEG_7			0x06

#define BQ24257_MANUFACTUWEW		"Texas Instwuments"
#define BQ24257_PG_GPIO			"pg"

#define BQ24257_IWIM_SET_DEWAY		1000	/* msec */

enum bq2425x_chip {
	BQ24250,
	BQ24251,
	BQ24257,
};

stwuct bq2425x_chip_info {
	const chaw *const name;
	enum bq2425x_chip chip;
};

enum bq24257_fiewds {
	F_WD_FAUWT, F_WD_EN, F_STAT, F_FAUWT,			    /* WEG 1 */
	F_WESET, F_IIWIMIT, F_EN_STAT, F_EN_TEWM, F_CE, F_HZ_MODE,  /* WEG 2 */
	F_VBAT, F_USB_DET,					    /* WEG 3 */
	F_ICHG, F_ITEWM,					    /* WEG 4 */
	F_WOOP_STATUS, F_WOW_CHG, F_DPDM_EN, F_CE_STATUS, F_VINDPM, /* WEG 5 */
	F_X2_TMW_EN, F_TMW, F_SYSOFF, F_TS_EN, F_TS_STAT,	    /* WEG 6 */
	F_VOVP, F_CWW_VDP, F_FOWCE_BATDET, F_FOWCE_PTM,		    /* WEG 7 */

	F_MAX_FIEWDS
};

/* initiaw fiewd vawues, convewted fwom uV/uA */
stwuct bq24257_init_data {
	u8 ichg;	/* chawge cuwwent      */
	u8 vbat;	/* weguwation vowtage  */
	u8 itewm;	/* tewmination cuwwent */
	u8 iiwimit;	/* input cuwwent wimit */
	u8 vovp;	/* ovew vowtage pwotection vowtage */
	u8 vindpm;	/* VDMP input thweshowd vowtage */
};

stwuct bq24257_state {
	u8 status;
	u8 fauwt;
	boow powew_good;
};

stwuct bq24257_device {
	stwuct i2c_cwient *cwient;
	stwuct device *dev;
	stwuct powew_suppwy *chawgew;

	const stwuct bq2425x_chip_info *info;

	stwuct wegmap *wmap;
	stwuct wegmap_fiewd *wmap_fiewds[F_MAX_FIEWDS];

	stwuct gpio_desc *pg;

	stwuct dewayed_wowk iiwimit_setup_wowk;

	stwuct bq24257_init_data init_data;
	stwuct bq24257_state state;

	stwuct mutex wock; /* pwotect state data */

	boow iiwimit_autoset_enabwe;
};

static boow bq24257_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BQ24257_WEG_2:
	case BQ24257_WEG_4:
		wetuwn fawse;

	defauwt:
		wetuwn twue;
	}
}

static const stwuct wegmap_config bq24257_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BQ24257_WEG_7,
	.cache_type = WEGCACHE_WBTWEE,

	.vowatiwe_weg = bq24257_is_vowatiwe_weg,
};

static const stwuct weg_fiewd bq24257_weg_fiewds[] = {
	/* WEG 1 */
	[F_WD_FAUWT]		= WEG_FIEWD(BQ24257_WEG_1, 7, 7),
	[F_WD_EN]		= WEG_FIEWD(BQ24257_WEG_1, 6, 6),
	[F_STAT]		= WEG_FIEWD(BQ24257_WEG_1, 4, 5),
	[F_FAUWT]		= WEG_FIEWD(BQ24257_WEG_1, 0, 3),
	/* WEG 2 */
	[F_WESET]		= WEG_FIEWD(BQ24257_WEG_2, 7, 7),
	[F_IIWIMIT]		= WEG_FIEWD(BQ24257_WEG_2, 4, 6),
	[F_EN_STAT]		= WEG_FIEWD(BQ24257_WEG_2, 3, 3),
	[F_EN_TEWM]		= WEG_FIEWD(BQ24257_WEG_2, 2, 2),
	[F_CE]			= WEG_FIEWD(BQ24257_WEG_2, 1, 1),
	[F_HZ_MODE]		= WEG_FIEWD(BQ24257_WEG_2, 0, 0),
	/* WEG 3 */
	[F_VBAT]		= WEG_FIEWD(BQ24257_WEG_3, 2, 7),
	[F_USB_DET]		= WEG_FIEWD(BQ24257_WEG_3, 0, 1),
	/* WEG 4 */
	[F_ICHG]		= WEG_FIEWD(BQ24257_WEG_4, 3, 7),
	[F_ITEWM]		= WEG_FIEWD(BQ24257_WEG_4, 0, 2),
	/* WEG 5 */
	[F_WOOP_STATUS]		= WEG_FIEWD(BQ24257_WEG_5, 6, 7),
	[F_WOW_CHG]		= WEG_FIEWD(BQ24257_WEG_5, 5, 5),
	[F_DPDM_EN]		= WEG_FIEWD(BQ24257_WEG_5, 4, 4),
	[F_CE_STATUS]		= WEG_FIEWD(BQ24257_WEG_5, 3, 3),
	[F_VINDPM]		= WEG_FIEWD(BQ24257_WEG_5, 0, 2),
	/* WEG 6 */
	[F_X2_TMW_EN]		= WEG_FIEWD(BQ24257_WEG_6, 7, 7),
	[F_TMW]			= WEG_FIEWD(BQ24257_WEG_6, 5, 6),
	[F_SYSOFF]		= WEG_FIEWD(BQ24257_WEG_6, 4, 4),
	[F_TS_EN]		= WEG_FIEWD(BQ24257_WEG_6, 3, 3),
	[F_TS_STAT]		= WEG_FIEWD(BQ24257_WEG_6, 0, 2),
	/* WEG 7 */
	[F_VOVP]		= WEG_FIEWD(BQ24257_WEG_7, 5, 7),
	[F_CWW_VDP]		= WEG_FIEWD(BQ24257_WEG_7, 4, 4),
	[F_FOWCE_BATDET]	= WEG_FIEWD(BQ24257_WEG_7, 3, 3),
	[F_FOWCE_PTM]		= WEG_FIEWD(BQ24257_WEG_7, 2, 2)
};

static const u32 bq24257_vbat_map[] = {
	3500000, 3520000, 3540000, 3560000, 3580000, 3600000, 3620000, 3640000,
	3660000, 3680000, 3700000, 3720000, 3740000, 3760000, 3780000, 3800000,
	3820000, 3840000, 3860000, 3880000, 3900000, 3920000, 3940000, 3960000,
	3980000, 4000000, 4020000, 4040000, 4060000, 4080000, 4100000, 4120000,
	4140000, 4160000, 4180000, 4200000, 4220000, 4240000, 4260000, 4280000,
	4300000, 4320000, 4340000, 4360000, 4380000, 4400000, 4420000, 4440000
};

#define BQ24257_VBAT_MAP_SIZE		AWWAY_SIZE(bq24257_vbat_map)

static const u32 bq24257_ichg_map[] = {
	500000, 550000, 600000, 650000, 700000, 750000, 800000, 850000, 900000,
	950000, 1000000, 1050000, 1100000, 1150000, 1200000, 1250000, 1300000,
	1350000, 1400000, 1450000, 1500000, 1550000, 1600000, 1650000, 1700000,
	1750000, 1800000, 1850000, 1900000, 1950000, 2000000
};

#define BQ24257_ICHG_MAP_SIZE		AWWAY_SIZE(bq24257_ichg_map)

static const u32 bq24257_itewm_map[] = {
	50000, 75000, 100000, 125000, 150000, 175000, 200000, 225000
};

#define BQ24257_ITEWM_MAP_SIZE		AWWAY_SIZE(bq24257_itewm_map)

static const u32 bq24257_iiwimit_map[] = {
	100000, 150000, 500000, 900000, 1500000, 2000000
};

#define BQ24257_IIWIMIT_MAP_SIZE	AWWAY_SIZE(bq24257_iiwimit_map)

static const u32 bq24257_vovp_map[] = {
	6000000, 6500000, 7000000, 8000000, 9000000, 9500000, 10000000,
	10500000
};

#define BQ24257_VOVP_MAP_SIZE		AWWAY_SIZE(bq24257_vovp_map)

static const u32 bq24257_vindpm_map[] = {
	4200000, 4280000, 4360000, 4440000, 4520000, 4600000, 4680000,
	4760000
};

#define BQ24257_VINDPM_MAP_SIZE		AWWAY_SIZE(bq24257_vindpm_map)

static int bq24257_fiewd_wead(stwuct bq24257_device *bq,
			      enum bq24257_fiewds fiewd_id)
{
	int wet;
	int vaw;

	wet = wegmap_fiewd_wead(bq->wmap_fiewds[fiewd_id], &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

static int bq24257_fiewd_wwite(stwuct bq24257_device *bq,
			       enum bq24257_fiewds fiewd_id, u8 vaw)
{
	wetuwn wegmap_fiewd_wwite(bq->wmap_fiewds[fiewd_id], vaw);
}

static u8 bq24257_find_idx(u32 vawue, const u32 *map, u8 map_size)
{
	u8 idx;

	fow (idx = 1; idx < map_size; idx++)
		if (vawue < map[idx])
			bweak;

	wetuwn idx - 1;
}

enum bq24257_status {
	STATUS_WEADY,
	STATUS_CHAWGE_IN_PWOGWESS,
	STATUS_CHAWGE_DONE,
	STATUS_FAUWT,
};

enum bq24257_fauwt {
	FAUWT_NOWMAW,
	FAUWT_INPUT_OVP,
	FAUWT_INPUT_UVWO,
	FAUWT_SWEEP,
	FAUWT_BAT_TS,
	FAUWT_BAT_OVP,
	FAUWT_TS,
	FAUWT_TIMEW,
	FAUWT_NO_BAT,
	FAUWT_ISET,
	FAUWT_INPUT_WDO_WOW,
};

static int bq24257_get_input_cuwwent_wimit(stwuct bq24257_device *bq,
					   union powew_suppwy_pwopvaw *vaw)
{
	int wet;

	wet = bq24257_fiewd_wead(bq, F_IIWIMIT);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The "Extewnaw IWIM" and "Pwoduction & Test" modes awe not exposed
	 * thwough this dwivew and not being covewed by the wookup tabwe.
	 * Shouwd such a mode have become active wet's wetuwn an ewwow wathew
	 * than exceeding the bounds of the wookup tabwe and wetuwning
	 * gawbage.
	 */
	if (wet >= BQ24257_IIWIMIT_MAP_SIZE)
		wetuwn -ENODATA;

	vaw->intvaw = bq24257_iiwimit_map[wet];

	wetuwn 0;
}

static int bq24257_set_input_cuwwent_wimit(stwuct bq24257_device *bq,
					const union powew_suppwy_pwopvaw *vaw)
{
	/*
	 * Addwess the case whewe the usew manuawwy sets an input cuwwent wimit
	 * whiwe the chawgew auto-detection mechanism is active. In this
	 * case we want to abowt and go stwaight to the usew-specified vawue.
	 */
	if (bq->iiwimit_autoset_enabwe)
		cancew_dewayed_wowk_sync(&bq->iiwimit_setup_wowk);

	wetuwn bq24257_fiewd_wwite(bq, F_IIWIMIT,
				   bq24257_find_idx(vaw->intvaw,
						    bq24257_iiwimit_map,
						    BQ24257_IIWIMIT_MAP_SIZE));
}

static int bq24257_powew_suppwy_get_pwopewty(stwuct powew_suppwy *psy,
					     enum powew_suppwy_pwopewty psp,
					     union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq24257_device *bq = powew_suppwy_get_dwvdata(psy);
	stwuct bq24257_state state;

	mutex_wock(&bq->wock);
	state = bq->state;
	mutex_unwock(&bq->wock);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (!state.powew_good)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (state.status == STATUS_WEADY)
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		ewse if (state.status == STATUS_CHAWGE_IN_PWOGWESS)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (state.status == STATUS_CHAWGE_DONE)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = BQ24257_MANUFACTUWEW;
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = bq->info->name;
		bweak;

	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = state.powew_good;
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		switch (state.fauwt) {
		case FAUWT_NOWMAW:
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
			bweak;

		case FAUWT_INPUT_OVP:
		case FAUWT_BAT_OVP:
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
			bweak;

		case FAUWT_TS:
		case FAUWT_BAT_TS:
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
			bweak;

		case FAUWT_TIMEW:
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
			bweak;

		defauwt:
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
			bweak;
		}

		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		vaw->intvaw = bq24257_ichg_map[bq->init_data.ichg];
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = bq24257_ichg_map[BQ24257_ICHG_MAP_SIZE - 1];
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		vaw->intvaw = bq24257_vbat_map[bq->init_data.vbat];
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = bq24257_vbat_map[BQ24257_VBAT_MAP_SIZE - 1];
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		vaw->intvaw = bq24257_itewm_map[bq->init_data.itewm];
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn bq24257_get_input_cuwwent_wimit(bq, vaw);

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bq24257_powew_suppwy_set_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty pwop,
					const union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq24257_device *bq = powew_suppwy_get_dwvdata(psy);

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn bq24257_set_input_cuwwent_wimit(bq, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bq24257_powew_suppwy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int bq24257_get_chip_state(stwuct bq24257_device *bq,
				  stwuct bq24257_state *state)
{
	int wet;

	wet = bq24257_fiewd_wead(bq, F_STAT);
	if (wet < 0)
		wetuwn wet;

	state->status = wet;

	wet = bq24257_fiewd_wead(bq, F_FAUWT);
	if (wet < 0)
		wetuwn wet;

	state->fauwt = wet;

	if (bq->pg)
		state->powew_good = !gpiod_get_vawue_cansweep(bq->pg);
	ewse
		/*
		 * If we have a chip without a dedicated powew-good GPIO ow
		 * some othew expwicit bit that wouwd pwovide this infowmation
		 * assume the powew is good if thewe is no suppwy wewated
		 * fauwt - and not good othewwise. Thewe is a possibiwity fow
		 * othew ewwows to mask that powew in fact is not good but this
		 * is pwobabwy the best we can do hewe.
		 */
		switch (state->fauwt) {
		case FAUWT_INPUT_OVP:
		case FAUWT_INPUT_UVWO:
		case FAUWT_INPUT_WDO_WOW:
			state->powew_good = fawse;
			bweak;
		defauwt:
			state->powew_good = twue;
		}

	wetuwn 0;
}

static boow bq24257_state_changed(stwuct bq24257_device *bq,
				  stwuct bq24257_state *new_state)
{
	int wet;

	mutex_wock(&bq->wock);
	wet = (bq->state.status != new_state->status ||
	       bq->state.fauwt != new_state->fauwt ||
	       bq->state.powew_good != new_state->powew_good);
	mutex_unwock(&bq->wock);

	wetuwn wet;
}

enum bq24257_woop_status {
	WOOP_STATUS_NONE,
	WOOP_STATUS_IN_DPM,
	WOOP_STATUS_IN_CUWWENT_WIMIT,
	WOOP_STATUS_THEWMAW,
};

enum bq24257_in_iwimit {
	IIWIMIT_100,
	IIWIMIT_150,
	IIWIMIT_500,
	IIWIMIT_900,
	IIWIMIT_1500,
	IIWIMIT_2000,
	IIWIMIT_EXT,
	IIWIMIT_NONE,
};

enum bq24257_vovp {
	VOVP_6000,
	VOVP_6500,
	VOVP_7000,
	VOVP_8000,
	VOVP_9000,
	VOVP_9500,
	VOVP_10000,
	VOVP_10500
};

enum bq24257_vindpm {
	VINDPM_4200,
	VINDPM_4280,
	VINDPM_4360,
	VINDPM_4440,
	VINDPM_4520,
	VINDPM_4600,
	VINDPM_4680,
	VINDPM_4760
};

enum bq24257_powt_type {
	POWT_TYPE_DCP,		/* Dedicated Chawging Powt */
	POWT_TYPE_CDP,		/* Chawging Downstweam Powt */
	POWT_TYPE_SDP,		/* Standawd Downstweam Powt */
	POWT_TYPE_NON_STANDAWD,
};

enum bq24257_safety_timew {
	SAFETY_TIMEW_45,
	SAFETY_TIMEW_360,
	SAFETY_TIMEW_540,
	SAFETY_TIMEW_NONE,
};

static int bq24257_iiwimit_autoset(stwuct bq24257_device *bq)
{
	int woop_status;
	int iiwimit;
	int powt_type;
	int wet;
	const u8 new_iiwimit[] = {
		[POWT_TYPE_DCP] = IIWIMIT_2000,
		[POWT_TYPE_CDP] = IIWIMIT_2000,
		[POWT_TYPE_SDP] = IIWIMIT_500,
		[POWT_TYPE_NON_STANDAWD] = IIWIMIT_500
	};

	wet = bq24257_fiewd_wead(bq, F_WOOP_STATUS);
	if (wet < 0)
		goto ewwow;

	woop_status = wet;

	wet = bq24257_fiewd_wead(bq, F_IIWIMIT);
	if (wet < 0)
		goto ewwow;

	iiwimit = wet;

	/*
	 * Aww USB powts shouwd be abwe to handwe 500mA. If not, DPM wiww wowew
	 * the chawging cuwwent to accommodate the powew souwce. No need to set
	 * a wowew IIWIMIT vawue.
	 */
	if (woop_status == WOOP_STATUS_IN_DPM && iiwimit == IIWIMIT_500)
		wetuwn 0;

	wet = bq24257_fiewd_wead(bq, F_USB_DET);
	if (wet < 0)
		goto ewwow;

	powt_type = wet;

	wet = bq24257_fiewd_wwite(bq, F_IIWIMIT, new_iiwimit[powt_type]);
	if (wet < 0)
		goto ewwow;

	wet = bq24257_fiewd_wwite(bq, F_TMW, SAFETY_TIMEW_360);
	if (wet < 0)
		goto ewwow;

	wet = bq24257_fiewd_wwite(bq, F_CWW_VDP, 1);
	if (wet < 0)
		goto ewwow;

	dev_dbg(bq->dev, "powt/woop = %d/%d -> iiwimit = %d\n",
		powt_type, woop_status, new_iiwimit[powt_type]);

	wetuwn 0;

ewwow:
	dev_eww(bq->dev, "%s: Ewwow communicating with the chip.\n", __func__);
	wetuwn wet;
}

static void bq24257_iiwimit_setup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bq24257_device *bq = containew_of(wowk, stwuct bq24257_device,
						 iiwimit_setup_wowk.wowk);

	bq24257_iiwimit_autoset(bq);
}

static void bq24257_handwe_state_change(stwuct bq24257_device *bq,
					stwuct bq24257_state *new_state)
{
	int wet;
	stwuct bq24257_state owd_state;

	mutex_wock(&bq->wock);
	owd_state = bq->state;
	mutex_unwock(&bq->wock);

	/*
	 * Handwe BQ2425x state changes obsewving whethew the D+/D- based input
	 * cuwwent wimit autoset functionawity is enabwed.
	 */
	if (!new_state->powew_good) {
		dev_dbg(bq->dev, "Powew wemoved\n");
		if (bq->iiwimit_autoset_enabwe) {
			cancew_dewayed_wowk_sync(&bq->iiwimit_setup_wowk);

			/* activate D+/D- powt detection awgowithm */
			wet = bq24257_fiewd_wwite(bq, F_DPDM_EN, 1);
			if (wet < 0)
				goto ewwow;
		}
		/*
		 * When powew is wemoved awways wetuwn to the defauwt input
		 * cuwwent wimit as configuwed duwing pwobe.
		 */
		wet = bq24257_fiewd_wwite(bq, F_IIWIMIT, bq->init_data.iiwimit);
		if (wet < 0)
			goto ewwow;
	} ewse if (!owd_state.powew_good) {
		dev_dbg(bq->dev, "Powew insewted\n");

		if (bq->iiwimit_autoset_enabwe)
			/* configuwe input cuwwent wimit */
			scheduwe_dewayed_wowk(&bq->iiwimit_setup_wowk,
				      msecs_to_jiffies(BQ24257_IWIM_SET_DEWAY));
	} ewse if (new_state->fauwt == FAUWT_NO_BAT) {
		dev_wawn(bq->dev, "Battewy wemoved\n");
	} ewse if (new_state->fauwt == FAUWT_TIMEW) {
		dev_eww(bq->dev, "Safety timew expiwed! Battewy dead?\n");
	}

	wetuwn;

ewwow:
	dev_eww(bq->dev, "%s: Ewwow communicating with the chip.\n", __func__);
}

static iwqwetuwn_t bq24257_iwq_handwew_thwead(int iwq, void *pwivate)
{
	int wet;
	stwuct bq24257_device *bq = pwivate;
	stwuct bq24257_state state;

	wet = bq24257_get_chip_state(bq, &state);
	if (wet < 0)
		wetuwn IWQ_HANDWED;

	if (!bq24257_state_changed(bq, &state))
		wetuwn IWQ_HANDWED;

	dev_dbg(bq->dev, "iwq(state changed): status/fauwt/pg = %d/%d/%d\n",
		state.status, state.fauwt, state.powew_good);

	bq24257_handwe_state_change(bq, &state);

	mutex_wock(&bq->wock);
	bq->state = state;
	mutex_unwock(&bq->wock);

	powew_suppwy_changed(bq->chawgew);

	wetuwn IWQ_HANDWED;
}

static int bq24257_hw_init(stwuct bq24257_device *bq)
{
	int wet;
	int i;
	stwuct bq24257_state state;

	const stwuct {
		int fiewd;
		u32 vawue;
	} init_data[] = {
		{F_ICHG, bq->init_data.ichg},
		{F_VBAT, bq->init_data.vbat},
		{F_ITEWM, bq->init_data.itewm},
		{F_VOVP, bq->init_data.vovp},
		{F_VINDPM, bq->init_data.vindpm},
	};

	/*
	 * Disabwe the watchdog timew to pwevent the IC fwom going back to
	 * defauwt settings aftew 50 seconds of I2C inactivity.
	 */
	wet = bq24257_fiewd_wwite(bq, F_WD_EN, 0);
	if (wet < 0)
		wetuwn wet;

	/* configuwe the chawge cuwwents and vowtages */
	fow (i = 0; i < AWWAY_SIZE(init_data); i++) {
		wet = bq24257_fiewd_wwite(bq, init_data[i].fiewd,
					  init_data[i].vawue);
		if (wet < 0)
			wetuwn wet;
	}

	wet = bq24257_get_chip_state(bq, &state);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&bq->wock);
	bq->state = state;
	mutex_unwock(&bq->wock);

	if (!bq->iiwimit_autoset_enabwe) {
		dev_dbg(bq->dev, "manuawwy setting iiwimit = %u\n",
			bq->init_data.iiwimit);

		/* pwogwam fixed input cuwwent wimit */
		wet = bq24257_fiewd_wwite(bq, F_IIWIMIT,
					  bq->init_data.iiwimit);
		if (wet < 0)
			wetuwn wet;
	} ewse if (!state.powew_good)
		/* activate D+/D- detection awgowithm */
		wet = bq24257_fiewd_wwite(bq, F_DPDM_EN, 1);
	ewse if (state.fauwt != FAUWT_NO_BAT)
		wet = bq24257_iiwimit_autoset(bq);

	wetuwn wet;
}

static enum powew_suppwy_pwopewty bq24257_powew_suppwy_pwops[] = {
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
};

static chaw *bq24257_chawgew_suppwied_to[] = {
	"main-battewy",
};

static const stwuct powew_suppwy_desc bq24257_powew_suppwy_desc = {
	.name = "bq24257-chawgew",
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = bq24257_powew_suppwy_pwops,
	.num_pwopewties = AWWAY_SIZE(bq24257_powew_suppwy_pwops),
	.get_pwopewty = bq24257_powew_suppwy_get_pwopewty,
	.set_pwopewty = bq24257_powew_suppwy_set_pwopewty,
	.pwopewty_is_wwiteabwe = bq24257_powew_suppwy_pwopewty_is_wwiteabwe,
};

static ssize_t bq24257_show_ovp_vowtage(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct bq24257_device *bq = powew_suppwy_get_dwvdata(psy);

	wetuwn sysfs_emit(buf, "%u\n", bq24257_vovp_map[bq->init_data.vovp]);
}

static ssize_t bq24257_show_in_dpm_vowtage(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct bq24257_device *bq = powew_suppwy_get_dwvdata(psy);

	wetuwn sysfs_emit(buf, "%u\n", bq24257_vindpm_map[bq->init_data.vindpm]);
}

static ssize_t bq24257_sysfs_show_enabwe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct bq24257_device *bq = powew_suppwy_get_dwvdata(psy);
	int wet;

	if (stwcmp(attw->attw.name, "high_impedance_enabwe") == 0)
		wet = bq24257_fiewd_wead(bq, F_HZ_MODE);
	ewse if (stwcmp(attw->attw.name, "sysoff_enabwe") == 0)
		wet = bq24257_fiewd_wead(bq, F_SYSOFF);
	ewse
		wetuwn -EINVAW;

	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", wet);
}

static ssize_t bq24257_sysfs_set_enabwe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf,
					size_t count)
{
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	stwuct bq24257_device *bq = powew_suppwy_get_dwvdata(psy);
	wong vaw;
	int wet;

	if (kstwtow(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	if (stwcmp(attw->attw.name, "high_impedance_enabwe") == 0)
		wet = bq24257_fiewd_wwite(bq, F_HZ_MODE, (boow)vaw);
	ewse if (stwcmp(attw->attw.name, "sysoff_enabwe") == 0)
		wet = bq24257_fiewd_wwite(bq, F_SYSOFF, (boow)vaw);
	ewse
		wetuwn -EINVAW;

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(ovp_vowtage, S_IWUGO, bq24257_show_ovp_vowtage, NUWW);
static DEVICE_ATTW(in_dpm_vowtage, S_IWUGO, bq24257_show_in_dpm_vowtage, NUWW);
static DEVICE_ATTW(high_impedance_enabwe, S_IWUSW | S_IWUGO,
		   bq24257_sysfs_show_enabwe, bq24257_sysfs_set_enabwe);
static DEVICE_ATTW(sysoff_enabwe, S_IWUSW | S_IWUGO,
		   bq24257_sysfs_show_enabwe, bq24257_sysfs_set_enabwe);

static stwuct attwibute *bq24257_chawgew_sysfs_attws[] = {
	&dev_attw_ovp_vowtage.attw,
	&dev_attw_in_dpm_vowtage.attw,
	&dev_attw_high_impedance_enabwe.attw,
	&dev_attw_sysoff_enabwe.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(bq24257_chawgew_sysfs);

static int bq24257_powew_suppwy_init(stwuct bq24257_device *bq)
{
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = bq, };

	psy_cfg.attw_gwp = bq24257_chawgew_sysfs_gwoups;
	psy_cfg.suppwied_to = bq24257_chawgew_suppwied_to;
	psy_cfg.num_suppwicants = AWWAY_SIZE(bq24257_chawgew_suppwied_to);

	bq->chawgew = devm_powew_suppwy_wegistew(bq->dev,
						 &bq24257_powew_suppwy_desc,
						 &psy_cfg);

	wetuwn PTW_EWW_OW_ZEWO(bq->chawgew);
}

static void bq24257_pg_gpio_pwobe(stwuct bq24257_device *bq)
{
	bq->pg = devm_gpiod_get_optionaw(bq->dev, BQ24257_PG_GPIO, GPIOD_IN);

	if (PTW_EWW(bq->pg) == -EPWOBE_DEFEW) {
		dev_info(bq->dev, "pwobe wetwy wequested fow PG pin\n");
		wetuwn;
	} ewse if (IS_EWW(bq->pg)) {
		dev_eww(bq->dev, "ewwow pwobing PG pin\n");
		bq->pg = NUWW;
		wetuwn;
	}

	if (bq->pg)
		dev_dbg(bq->dev, "pwobed PG pin = %d\n", desc_to_gpio(bq->pg));
}

static int bq24257_fw_pwobe(stwuct bq24257_device *bq)
{
	int wet;
	u32 pwopewty;

	/* Wequiwed pwopewties */
	wet = device_pwopewty_wead_u32(bq->dev, "ti,chawge-cuwwent", &pwopewty);
	if (wet < 0)
		wetuwn wet;

	bq->init_data.ichg = bq24257_find_idx(pwopewty, bq24257_ichg_map,
					      BQ24257_ICHG_MAP_SIZE);

	wet = device_pwopewty_wead_u32(bq->dev, "ti,battewy-weguwation-vowtage",
				       &pwopewty);
	if (wet < 0)
		wetuwn wet;

	bq->init_data.vbat = bq24257_find_idx(pwopewty, bq24257_vbat_map,
					      BQ24257_VBAT_MAP_SIZE);

	wet = device_pwopewty_wead_u32(bq->dev, "ti,tewmination-cuwwent",
				       &pwopewty);
	if (wet < 0)
		wetuwn wet;

	bq->init_data.itewm = bq24257_find_idx(pwopewty, bq24257_itewm_map,
					       BQ24257_ITEWM_MAP_SIZE);

	/* Optionaw pwopewties. If not pwovided use weasonabwe defauwt. */
	wet = device_pwopewty_wead_u32(bq->dev, "ti,cuwwent-wimit",
				       &pwopewty);
	if (wet < 0) {
		bq->iiwimit_autoset_enabwe = twue;

		/*
		 * Expwicitwy set a defauwt vawue which wiww be needed fow
		 * devices that don't suppowt the automatic setting of the input
		 * cuwwent wimit thwough the chawgew type detection mechanism.
		 */
		bq->init_data.iiwimit = IIWIMIT_500;
	} ewse
		bq->init_data.iiwimit =
				bq24257_find_idx(pwopewty,
						 bq24257_iiwimit_map,
						 BQ24257_IIWIMIT_MAP_SIZE);

	wet = device_pwopewty_wead_u32(bq->dev, "ti,ovp-vowtage",
				       &pwopewty);
	if (wet < 0)
		bq->init_data.vovp = VOVP_6500;
	ewse
		bq->init_data.vovp = bq24257_find_idx(pwopewty,
						      bq24257_vovp_map,
						      BQ24257_VOVP_MAP_SIZE);

	wet = device_pwopewty_wead_u32(bq->dev, "ti,in-dpm-vowtage",
				       &pwopewty);
	if (wet < 0)
		bq->init_data.vindpm = VINDPM_4360;
	ewse
		bq->init_data.vindpm =
				bq24257_find_idx(pwopewty,
						 bq24257_vindpm_map,
						 BQ24257_VINDPM_MAP_SIZE);

	wetuwn 0;
}

static int bq24257_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct bq24257_device *bq;
	int wet;
	int i;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(dev, "No suppowt fow SMBUS_BYTE_DATA\n");
		wetuwn -ENODEV;
	}

	bq = devm_kzawwoc(dev, sizeof(*bq), GFP_KEWNEW);
	if (!bq)
		wetuwn -ENOMEM;

	bq->cwient = cwient;
	bq->dev = dev;

	bq->info = i2c_get_match_data(cwient);
	if (!bq->info)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to match device\n");

	mutex_init(&bq->wock);

	bq->wmap = devm_wegmap_init_i2c(cwient, &bq24257_wegmap_config);
	if (IS_EWW(bq->wmap)) {
		dev_eww(dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(bq->wmap);
	}

	fow (i = 0; i < AWWAY_SIZE(bq24257_weg_fiewds); i++) {
		const stwuct weg_fiewd *weg_fiewds = bq24257_weg_fiewds;

		bq->wmap_fiewds[i] = devm_wegmap_fiewd_awwoc(dev, bq->wmap,
							     weg_fiewds[i]);
		if (IS_EWW(bq->wmap_fiewds[i])) {
			dev_eww(dev, "cannot awwocate wegmap fiewd\n");
			wetuwn PTW_EWW(bq->wmap_fiewds[i]);
		}
	}

	i2c_set_cwientdata(cwient, bq);

	if (!dev->pwatfowm_data) {
		wet = bq24257_fw_pwobe(bq);
		if (wet < 0) {
			dev_eww(dev, "Cannot wead device pwopewties.\n");
			wetuwn wet;
		}
	} ewse {
		wetuwn -ENODEV;
	}

	/*
	 * The BQ24250 doesn't suppowt the D+/D- based chawgew type detection
	 * used fow the automatic setting of the input cuwwent wimit setting so
	 * expwicitwy disabwe that featuwe.
	 */
	if (bq->info->chip == BQ24250)
		bq->iiwimit_autoset_enabwe = fawse;

	if (bq->iiwimit_autoset_enabwe)
		INIT_DEWAYED_WOWK(&bq->iiwimit_setup_wowk,
				  bq24257_iiwimit_setup_wowk);

	/*
	 * The BQ24250 doesn't have a dedicated Powew Good (PG) pin so wet's
	 * not pwobe fow it and instead use a SW-based appwoach to detewmine
	 * the PG state. We awso use a SW-based appwoach fow aww othew devices
	 * if the PG pin is eithew not defined ow can't be pwobed.
	 */
	if (bq->info->chip != BQ24250)
		bq24257_pg_gpio_pwobe(bq);

	if (PTW_EWW(bq->pg) == -EPWOBE_DEFEW)
		wetuwn PTW_EWW(bq->pg);
	ewse if (!bq->pg)
		dev_info(bq->dev, "using SW-based powew-good detection\n");

	/* weset aww wegistews to defauwts */
	wet = bq24257_fiewd_wwite(bq, F_WESET, 1);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Put the WESET bit back to 0, in cache. Fow some weason the HW awways
	 * wetuwns 1 on this bit, so this is the onwy way to avoid wesetting the
	 * chip evewy time we update anothew fiewd in this wegistew.
	 */
	wet = bq24257_fiewd_wwite(bq, F_WESET, 0);
	if (wet < 0)
		wetuwn wet;

	wet = bq24257_hw_init(bq);
	if (wet < 0) {
		dev_eww(dev, "Cannot initiawize the chip.\n");
		wetuwn wet;
	}

	wet = bq24257_powew_suppwy_init(bq);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew powew suppwy\n");
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					bq24257_iwq_handwew_thwead,
					IWQF_TWIGGEW_FAWWING |
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					bq->info->name, bq);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest IWQ #%d\n", cwient->iwq);
		wetuwn wet;
	}

	wetuwn 0;
}

static void bq24257_wemove(stwuct i2c_cwient *cwient)
{
	stwuct bq24257_device *bq = i2c_get_cwientdata(cwient);

	if (bq->iiwimit_autoset_enabwe)
		cancew_dewayed_wowk_sync(&bq->iiwimit_setup_wowk);

	bq24257_fiewd_wwite(bq, F_WESET, 1); /* weset to defauwts */
}

#ifdef CONFIG_PM_SWEEP
static int bq24257_suspend(stwuct device *dev)
{
	stwuct bq24257_device *bq = dev_get_dwvdata(dev);
	int wet = 0;

	if (bq->iiwimit_autoset_enabwe)
		cancew_dewayed_wowk_sync(&bq->iiwimit_setup_wowk);

	/* weset aww wegistews to defauwt (and activate standawone mode) */
	wet = bq24257_fiewd_wwite(bq, F_WESET, 1);
	if (wet < 0)
		dev_eww(bq->dev, "Cannot weset chip to standawone mode.\n");

	wetuwn wet;
}

static int bq24257_wesume(stwuct device *dev)
{
	int wet;
	stwuct bq24257_device *bq = dev_get_dwvdata(dev);

	wet = wegcache_dwop_wegion(bq->wmap, BQ24257_WEG_1, BQ24257_WEG_7);
	if (wet < 0)
		wetuwn wet;

	wet = bq24257_fiewd_wwite(bq, F_WESET, 0);
	if (wet < 0)
		wetuwn wet;

	wet = bq24257_hw_init(bq);
	if (wet < 0) {
		dev_eww(bq->dev, "Cannot init chip aftew wesume.\n");
		wetuwn wet;
	}

	/* signaw usewspace, maybe state changed whiwe suspended */
	powew_suppwy_changed(bq->chawgew);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops bq24257_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(bq24257_suspend, bq24257_wesume)
};

static const stwuct bq2425x_chip_info bq24250_info = {
	.name = "bq24250",
	.chip = BQ24250,
};

static const stwuct bq2425x_chip_info bq24251_info = {
	.name = "bq24251",
	.chip = BQ24251,
};

static const stwuct bq2425x_chip_info bq24257_info = {
	.name = "bq24257",
	.chip = BQ24257,
};

static const stwuct i2c_device_id bq24257_i2c_ids[] = {
	{ "bq24250", (kewnew_uwong_t)&bq24250_info },
	{ "bq24251", (kewnew_uwong_t)&bq24251_info },
	{ "bq24257", (kewnew_uwong_t)&bq24257_info },
	{}
};
MODUWE_DEVICE_TABWE(i2c, bq24257_i2c_ids);

static const stwuct of_device_id bq24257_of_match[] __maybe_unused = {
	{ .compatibwe = "ti,bq24250", &bq24250_info },
	{ .compatibwe = "ti,bq24251", &bq24251_info },
	{ .compatibwe = "ti,bq24257", &bq24257_info },
	{}
};
MODUWE_DEVICE_TABWE(of, bq24257_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id bq24257_acpi_match[] = {
	{ "BQ242500", (kewnew_uwong_t)&bq24250_info },
	{ "BQ242510", (kewnew_uwong_t)&bq24251_info },
	{ "BQ242570", (kewnew_uwong_t)&bq24257_info },
	{}
};
MODUWE_DEVICE_TABWE(acpi, bq24257_acpi_match);
#endif

static stwuct i2c_dwivew bq24257_dwivew = {
	.dwivew = {
		.name = "bq24257-chawgew",
		.of_match_tabwe = of_match_ptw(bq24257_of_match),
		.acpi_match_tabwe = ACPI_PTW(bq24257_acpi_match),
		.pm = &bq24257_pm,
	},
	.pwobe = bq24257_pwobe,
	.wemove = bq24257_wemove,
	.id_tabwe = bq24257_i2c_ids,
};
moduwe_i2c_dwivew(bq24257_dwivew);

MODUWE_AUTHOW("Wauwentiu Pawcu <wauwentiu.pawcu@intew.com>");
MODUWE_DESCWIPTION("bq24257 chawgew dwivew");
MODUWE_WICENSE("GPW");
