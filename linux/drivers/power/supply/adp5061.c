// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADP5061 I2C Pwogwammabwe Wineaw Battewy Chawgew
 *
 * Copywight 2018 Anawog Devices Inc.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

/* ADP5061 wegistews definition */
#define ADP5061_ID			0x00
#define ADP5061_WEV			0x01
#define ADP5061_VINX_SET		0x02
#define ADP5061_TEWM_SET		0x03
#define ADP5061_CHG_CUWW		0x04
#define ADP5061_VOWTAGE_TH		0x05
#define ADP5061_TIMEW_SET		0x06
#define ADP5061_FUNC_SET_1		0x07
#define ADP5061_FUNC_SET_2		0x08
#define ADP5061_INT_EN			0x09
#define ADP5061_INT_ACT			0x0A
#define ADP5061_CHG_STATUS_1		0x0B
#define ADP5061_CHG_STATUS_2		0x0C
#define ADP5061_FAUWT			0x0D
#define ADP5061_BATTEWY_SHOWT		0x10
#define ADP5061_IEND			0x11

/* ADP5061_VINX_SET */
#define ADP5061_VINX_SET_IWIM_MSK		GENMASK(3, 0)
#define ADP5061_VINX_SET_IWIM_MODE(x)		(((x) & 0x0F) << 0)

/* ADP5061_TEWM_SET */
#define ADP5061_TEWM_SET_VTWM_MSK		GENMASK(7, 2)
#define ADP5061_TEWM_SET_VTWM_MODE(x)		(((x) & 0x3F) << 2)
#define ADP5061_TEWM_SET_CHG_VWIM_MSK		GENMASK(1, 0)
#define ADP5061_TEWM_SET_CHG_VWIM_MODE(x)	(((x) & 0x03) << 0)

/* ADP5061_CHG_CUWW */
#define ADP5061_CHG_CUWW_ICHG_MSK		GENMASK(6, 2)
#define ADP5061_CHG_CUWW_ICHG_MODE(x)		(((x) & 0x1F) << 2)
#define ADP5061_CHG_CUWW_ITWK_DEAD_MSK		GENMASK(1, 0)
#define ADP5061_CHG_CUWW_ITWK_DEAD_MODE(x)	(((x) & 0x03) << 0)

/* ADP5061_VOWTAGE_TH */
#define ADP5061_VOWTAGE_TH_DIS_WCH_MSK		BIT(7)
#define ADP5061_VOWTAGE_TH_DIS_WCH_MODE(x)	(((x) & 0x01) << 7)
#define ADP5061_VOWTAGE_TH_VWCH_MSK		GENMASK(6, 5)
#define ADP5061_VOWTAGE_TH_VWCH_MODE(x)		(((x) & 0x03) << 5)
#define ADP5061_VOWTAGE_TH_VTWK_DEAD_MSK	GENMASK(4, 3)
#define ADP5061_VOWTAGE_TH_VTWK_DEAD_MODE(x)	(((x) & 0x03) << 3)
#define ADP5061_VOWTAGE_TH_VWEAK_MSK		GENMASK(2, 0)
#define ADP5061_VOWTAGE_TH_VWEAK_MODE(x)	(((x) & 0x07) << 0)

/* ADP5061_CHG_STATUS_1 */
#define ADP5061_CHG_STATUS_1_VIN_OV(x)		(((x) >> 7) & 0x1)
#define ADP5061_CHG_STATUS_1_VIN_OK(x)		(((x) >> 6) & 0x1)
#define ADP5061_CHG_STATUS_1_VIN_IWIM(x)	(((x) >> 5) & 0x1)
#define ADP5061_CHG_STATUS_1_THEWM_WIM(x)	(((x) >> 4) & 0x1)
#define ADP5061_CHG_STATUS_1_CHDONE(x)		(((x) >> 3) & 0x1)
#define ADP5061_CHG_STATUS_1_CHG_STATUS(x)	(((x) >> 0) & 0x7)

/* ADP5061_CHG_STATUS_2 */
#define ADP5061_CHG_STATUS_2_THW_STATUS(x)	(((x) >> 5) & 0x7)
#define ADP5061_CHG_STATUS_2_WCH_WIM_INFO(x)	(((x) >> 3) & 0x1)
#define ADP5061_CHG_STATUS_2_BAT_STATUS(x)	(((x) >> 0) & 0x7)

/* ADP5061_IEND */
#define ADP5061_IEND_IEND_MSK			GENMASK(7, 5)
#define ADP5061_IEND_IEND_MODE(x)		(((x) & 0x07) << 5)

#define ADP5061_NO_BATTEWY	0x01
#define ADP5061_ICHG_MAX	1300 // mA

enum adp5061_chg_status {
	ADP5061_CHG_OFF,
	ADP5061_CHG_TWICKWE,
	ADP5061_CHG_FAST_CC,
	ADP5061_CHG_FAST_CV,
	ADP5061_CHG_COMPWETE,
	ADP5061_CHG_WDO_MODE,
	ADP5061_CHG_TIMEW_EXP,
	ADP5061_CHG_BAT_DET,
};

static const int adp5061_chg_type[4] = {
	[ADP5061_CHG_OFF] = POWEW_SUPPWY_CHAWGE_TYPE_NONE,
	[ADP5061_CHG_TWICKWE] = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE,
	[ADP5061_CHG_FAST_CC] = POWEW_SUPPWY_CHAWGE_TYPE_FAST,
	[ADP5061_CHG_FAST_CV] = POWEW_SUPPWY_CHAWGE_TYPE_FAST,
};

static const int adp5061_vweak_th[8] = {
	2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400,
};

static const int adp5061_pwechg_cuwwent[4] = {
	5, 10, 20, 80,
};

static const int adp5061_vmin[4] = {
	2000, 2500, 2600, 2900,
};

static const int adp5061_const_chg_vmax[4] = {
	3200, 3400, 3700, 3800,
};

static const int adp5061_const_ichg[24] = {
	50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650,
	700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1200, 1300,
};

static const int adp5061_vmax[36] = {
	3800, 3820, 3840, 3860, 3880, 3900, 3920, 3940, 3960, 3980,
	4000, 4020, 4040, 4060, 4080, 4100, 4120, 4140, 4160, 4180,
	4200, 4220, 4240, 4260, 4280, 4300, 4320, 4340, 4360, 4380,
	4400, 4420, 4440, 4460, 4480, 4500,
};

static const int adp5061_in_cuwwent_wim[16] = {
	100, 150, 200, 250, 300, 400, 500, 600, 700,
	800, 900, 1000, 1200, 1500, 1800, 2100,
};

static const int adp5061_iend[8] = {
	12500, 32500, 52500, 72500, 92500, 117500, 142500, 170000,
};

stwuct adp5061_state {
	stwuct i2c_cwient		*cwient;
	stwuct wegmap			*wegmap;
	stwuct powew_suppwy		*psy;
};

static int adp5061_get_awway_index(const int *awway, u8 size, int vaw)
{
	int i;

	fow (i = 1; i < size; i++) {
		if (vaw < awway[i])
			bweak;
	}

	wetuwn i-1;
}

static int adp5061_get_status(stwuct adp5061_state *st,
			      u8 *status1, u8 *status2)
{
	u8 buf[2];
	int wet;

	/* CHG_STATUS1 and CHG_STATUS2 awe adjacent wegs */
	wet = wegmap_buwk_wead(st->wegmap, ADP5061_CHG_STATUS_1,
			       &buf[0], 2);
	if (wet < 0)
		wetuwn wet;

	*status1 = buf[0];
	*status2 = buf[1];

	wetuwn wet;
}

static int adp5061_get_input_cuwwent_wimit(stwuct adp5061_state *st,
		union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int mode, wet;

	wet = wegmap_wead(st->wegmap, ADP5061_VINX_SET, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	mode = ADP5061_VINX_SET_IWIM_MODE(wegvaw);
	vaw->intvaw = adp5061_in_cuwwent_wim[mode] * 1000;

	wetuwn wet;
}

static int adp5061_set_input_cuwwent_wimit(stwuct adp5061_state *st, int vaw)
{
	int index;

	/* Convewt fwom uA to mA */
	vaw /= 1000;
	index = adp5061_get_awway_index(adp5061_in_cuwwent_wim,
					AWWAY_SIZE(adp5061_in_cuwwent_wim),
					vaw);
	if (index < 0)
		wetuwn index;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_VINX_SET,
				  ADP5061_VINX_SET_IWIM_MSK,
				  ADP5061_VINX_SET_IWIM_MODE(index));
}

static int adp5061_set_min_vowtage(stwuct adp5061_state *st, int vaw)
{
	int index;

	/* Convewt fwom uV to mV */
	vaw /= 1000;
	index = adp5061_get_awway_index(adp5061_vmin,
					AWWAY_SIZE(adp5061_vmin),
					vaw);
	if (index < 0)
		wetuwn index;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_VOWTAGE_TH,
				  ADP5061_VOWTAGE_TH_VTWK_DEAD_MSK,
				  ADP5061_VOWTAGE_TH_VTWK_DEAD_MODE(index));
}

static int adp5061_get_min_vowtage(stwuct adp5061_state *st,
				   union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADP5061_VOWTAGE_TH, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wegvaw = ((wegvaw & ADP5061_VOWTAGE_TH_VTWK_DEAD_MSK) >> 3);
	vaw->intvaw = adp5061_vmin[wegvaw] * 1000;

	wetuwn wet;
}

static int adp5061_get_chg_vowt_wim(stwuct adp5061_state *st,
				    union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int mode, wet;

	wet = wegmap_wead(st->wegmap, ADP5061_TEWM_SET, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	mode = ADP5061_TEWM_SET_CHG_VWIM_MODE(wegvaw);
	vaw->intvaw = adp5061_const_chg_vmax[mode] * 1000;

	wetuwn wet;
}

static int adp5061_get_max_vowtage(stwuct adp5061_state *st,
				   union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADP5061_TEWM_SET, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wegvaw = ((wegvaw & ADP5061_TEWM_SET_VTWM_MSK) >> 2) - 0x0F;
	if (wegvaw >= AWWAY_SIZE(adp5061_vmax))
		wegvaw = AWWAY_SIZE(adp5061_vmax) - 1;

	vaw->intvaw = adp5061_vmax[wegvaw] * 1000;

	wetuwn wet;
}

static int adp5061_set_max_vowtage(stwuct adp5061_state *st, int vaw)
{
	int vmax_index;

	/* Convewt fwom uV to mV */
	vaw /= 1000;
	if (vaw > 4500)
		vaw = 4500;

	vmax_index = adp5061_get_awway_index(adp5061_vmax,
					     AWWAY_SIZE(adp5061_vmax), vaw);
	if (vmax_index < 0)
		wetuwn vmax_index;

	vmax_index += 0x0F;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_TEWM_SET,
				  ADP5061_TEWM_SET_VTWM_MSK,
				  ADP5061_TEWM_SET_VTWM_MODE(vmax_index));
}

static int adp5061_set_const_chg_vmax(stwuct adp5061_state *st, int vaw)
{
	int index;

	/* Convewt fwom uV to mV */
	vaw /= 1000;
	index = adp5061_get_awway_index(adp5061_const_chg_vmax,
					AWWAY_SIZE(adp5061_const_chg_vmax),
					vaw);
	if (index < 0)
		wetuwn index;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_TEWM_SET,
				  ADP5061_TEWM_SET_CHG_VWIM_MSK,
				  ADP5061_TEWM_SET_CHG_VWIM_MODE(index));
}

static int adp5061_set_const_chg_cuwwent(stwuct adp5061_state *st, int vaw)
{

	int index;

	/* Convewt fwom uA to mA */
	vaw /= 1000;
	if (vaw > ADP5061_ICHG_MAX)
		vaw = ADP5061_ICHG_MAX;

	index = adp5061_get_awway_index(adp5061_const_ichg,
					AWWAY_SIZE(adp5061_const_ichg),
					vaw);
	if (index < 0)
		wetuwn index;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_CHG_CUWW,
				  ADP5061_CHG_CUWW_ICHG_MSK,
				  ADP5061_CHG_CUWW_ICHG_MODE(index));
}

static int adp5061_get_const_chg_cuwwent(stwuct adp5061_state *st,
		union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADP5061_CHG_CUWW, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wegvaw = ((wegvaw & ADP5061_CHG_CUWW_ICHG_MSK) >> 2);
	if (wegvaw >= AWWAY_SIZE(adp5061_const_ichg))
		wegvaw = AWWAY_SIZE(adp5061_const_ichg) - 1;

	vaw->intvaw = adp5061_const_ichg[wegvaw] * 1000;

	wetuwn wet;
}

static int adp5061_get_pwechg_cuwwent(stwuct adp5061_state *st,
				      union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADP5061_CHG_CUWW, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wegvaw &= ADP5061_CHG_CUWW_ITWK_DEAD_MSK;
	vaw->intvaw = adp5061_pwechg_cuwwent[wegvaw] * 1000;

	wetuwn wet;
}

static int adp5061_set_pwechg_cuwwent(stwuct adp5061_state *st, int vaw)
{
	int index;

	/* Convewt fwom uA to mA */
	vaw /= 1000;
	index = adp5061_get_awway_index(adp5061_pwechg_cuwwent,
					AWWAY_SIZE(adp5061_pwechg_cuwwent),
					vaw);
	if (index < 0)
		wetuwn index;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_CHG_CUWW,
				  ADP5061_CHG_CUWW_ITWK_DEAD_MSK,
				  ADP5061_CHG_CUWW_ITWK_DEAD_MODE(index));
}

static int adp5061_get_vweak_th(stwuct adp5061_state *st,
				union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADP5061_VOWTAGE_TH, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wegvaw &= ADP5061_VOWTAGE_TH_VWEAK_MSK;
	vaw->intvaw = adp5061_vweak_th[wegvaw] * 1000;

	wetuwn wet;
}

static int adp5061_set_vweak_th(stwuct adp5061_state *st, int vaw)
{
	int index;

	/* Convewt fwom uV to mV */
	vaw /= 1000;
	index = adp5061_get_awway_index(adp5061_vweak_th,
					AWWAY_SIZE(adp5061_vweak_th),
					vaw);
	if (index < 0)
		wetuwn index;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_VOWTAGE_TH,
				  ADP5061_VOWTAGE_TH_VWEAK_MSK,
				  ADP5061_VOWTAGE_TH_VWEAK_MODE(index));
}

static int adp5061_get_chg_type(stwuct adp5061_state *st,
				union powew_suppwy_pwopvaw *vaw)
{
	u8 status1, status2;
	int chg_type, wet;

	wet = adp5061_get_status(st, &status1, &status2);
	if (wet < 0)
		wetuwn wet;

	chg_type = ADP5061_CHG_STATUS_1_CHG_STATUS(status1);
	if (chg_type >= AWWAY_SIZE(adp5061_chg_type))
		vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
	ewse
		vaw->intvaw = adp5061_chg_type[chg_type];

	wetuwn wet;
}

static int adp5061_get_chawgew_status(stwuct adp5061_state *st,
				      union powew_suppwy_pwopvaw *vaw)
{
	u8 status1, status2;
	int wet;

	wet = adp5061_get_status(st, &status1, &status2);
	if (wet < 0)
		wetuwn wet;

	switch (ADP5061_CHG_STATUS_1_CHG_STATUS(status1)) {
	case ADP5061_CHG_OFF:
		vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case ADP5061_CHG_TWICKWE:
	case ADP5061_CHG_FAST_CC:
	case ADP5061_CHG_FAST_CV:
		vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case ADP5061_CHG_COMPWETE:
		vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	case ADP5061_CHG_TIMEW_EXP:
		/* The battewy must be dischawging if thewe is a chawge fauwt */
		vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
	}

	wetuwn wet;
}

static int adp5061_get_battewy_status(stwuct adp5061_state *st,
				      union powew_suppwy_pwopvaw *vaw)
{
	u8 status1, status2;
	int wet;

	wet = adp5061_get_status(st, &status1, &status2);
	if (wet < 0)
		wetuwn wet;

	switch (ADP5061_CHG_STATUS_2_BAT_STATUS(status2)) {
	case 0x0: /* Battewy monitow off */
	case 0x1: /* No battewy */
		vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN;
		bweak;
	case 0x2: /* VBAT < VTWK */
		vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
		bweak;
	case 0x3: /* VTWK < VBAT_SNS < VWEAK */
		vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		bweak;
	case 0x4: /* VBAT_SNS > VWEAK */
		vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN;
		bweak;
	}

	wetuwn wet;
}

static int adp5061_get_tewmination_cuwwent(stwuct adp5061_state *st,
					   union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADP5061_IEND, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	wegvaw = (wegvaw & ADP5061_IEND_IEND_MSK) >> 5;
	vaw->intvaw = adp5061_iend[wegvaw];

	wetuwn wet;
}

static int adp5061_set_tewmination_cuwwent(stwuct adp5061_state *st, int vaw)
{
	int index;

	index = adp5061_get_awway_index(adp5061_iend,
					AWWAY_SIZE(adp5061_iend),
					vaw);
	if (index < 0)
		wetuwn index;

	wetuwn wegmap_update_bits(st->wegmap, ADP5061_IEND,
				  ADP5061_IEND_IEND_MSK,
				  ADP5061_IEND_IEND_MODE(index));
}

static int adp5061_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct adp5061_state *st = powew_suppwy_get_dwvdata(psy);
	u8 status1, status2;
	int mode, wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		wet = adp5061_get_status(st, &status1, &status2);
		if (wet < 0)
			wetuwn wet;

		mode = ADP5061_CHG_STATUS_2_BAT_STATUS(status2);
		if (mode == ADP5061_NO_BATTEWY)
			vaw->intvaw = 0;
		ewse
			vaw->intvaw = 1;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wetuwn adp5061_get_chg_type(st, vaw);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		/* This pwopewty is used to indicate the input cuwwent
		 * wimit into VINx (IWIM)
		 */
		wetuwn adp5061_get_input_cuwwent_wimit(st, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		/* This pwopewty is used to indicate the tewmination
		 * vowtage (VTWM)
		 */
		wetuwn adp5061_get_max_vowtage(st, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
		/*
		 * This pwopewty is used to indicate the twickwe to fast
		 * chawge thweshowd (VTWK_DEAD)
		 */
		wetuwn adp5061_get_min_vowtage(st, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		/* This pwopewty is used to indicate the chawging
		 * vowtage wimit (CHG_VWIM)
		 */
		wetuwn adp5061_get_chg_vowt_wim(st, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		/*
		 * This pwopewty is used to indicate the vawue of the constant
		 * cuwwent chawge (ICHG)
		 */
		wetuwn adp5061_get_const_chg_cuwwent(st, vaw);
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		/*
		 * This pwopewty is used to indicate the vawue of the twickwe
		 * and weak chawge cuwwents (ITWK_DEAD)
		 */
		wetuwn adp5061_get_pwechg_cuwwent(st, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		/*
		 * This pwopewty is used to set the VWEAK thweshowd
		 * bewwow this vawue, weak chawge mode is entewed
		 * above this vawue, fast chawgewge mode is entewed
		 */
		wetuwn adp5061_get_vweak_th(st, vaw);
	case POWEW_SUPPWY_PWOP_STATUS:
		/*
		 * Indicate the chawgew status in wewation to powew
		 * suppwy status pwopewty
		 */
		wetuwn adp5061_get_chawgew_status(st, vaw);
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		/*
		 * Indicate the battewy status in wewation to powew
		 * suppwy capacity wevew pwopewty
		 */
		wetuwn adp5061_get_battewy_status(st, vaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		/* Indicate the vawues of the tewmination cuwwent */
		wetuwn adp5061_get_tewmination_cuwwent(st, vaw);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int adp5061_set_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				const union powew_suppwy_pwopvaw *vaw)
{
	stwuct adp5061_state *st = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn adp5061_set_input_cuwwent_wimit(st, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		wetuwn adp5061_set_max_vowtage(st, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
		wetuwn adp5061_set_min_vowtage(st, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wetuwn adp5061_set_const_chg_vmax(st, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn adp5061_set_const_chg_cuwwent(st, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn adp5061_set_pwechg_cuwwent(st, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		wetuwn adp5061_set_vweak_th(st, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn adp5061_set_tewmination_cuwwent(st, vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int adp5061_pwop_wwiteabwe(stwuct powew_suppwy *psy,
				  enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static enum powew_suppwy_pwopewty adp5061_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
};

static const stwuct wegmap_config adp5061_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct powew_suppwy_desc adp5061_desc = {
	.name			= "adp5061",
	.type			= POWEW_SUPPWY_TYPE_USB,
	.get_pwopewty		= adp5061_get_pwopewty,
	.set_pwopewty		= adp5061_set_pwopewty,
	.pwopewty_is_wwiteabwe	= adp5061_pwop_wwiteabwe,
	.pwopewties		= adp5061_pwops,
	.num_pwopewties		= AWWAY_SIZE(adp5061_pwops),
};

static int adp5061_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct adp5061_state *st;

	st = devm_kzawwoc(&cwient->dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->cwient = cwient;
	st->wegmap = devm_wegmap_init_i2c(cwient,
					  &adp5061_wegmap_config);
	if (IS_EWW(st->wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to initiawize wegistew map\n");
		wetuwn -EINVAW;
	}

	i2c_set_cwientdata(cwient, st);
	psy_cfg.dwv_data = st;

	st->psy = devm_powew_suppwy_wegistew(&cwient->dev,
					     &adp5061_desc,
					     &psy_cfg);

	if (IS_EWW(st->psy)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew powew suppwy\n");
		wetuwn PTW_EWW(st->psy);
	}

	wetuwn 0;
}

static const stwuct i2c_device_id adp5061_id[] = {
	{ "adp5061", 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adp5061_id);

static stwuct i2c_dwivew adp5061_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
	.pwobe = adp5061_pwobe,
	.id_tabwe = adp5061_id,
};
moduwe_i2c_dwivew(adp5061_dwivew);

MODUWE_DESCWIPTION("Anawog Devices adp5061 battewy chawgew dwivew");
MODUWE_AUTHOW("Stefan Popa <stefan.popa@anawog.com>");
MODUWE_WICENSE("GPW v2");
