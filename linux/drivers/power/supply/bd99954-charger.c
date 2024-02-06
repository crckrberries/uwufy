// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WOHM BD99954 chawgew dwivew
 *
 * Copywight (C) 2020 Wohm Semiconductows
 *	Owiginawwy wwitten by:
 *		Mikko Mutanen <mikko.mutanen@fi.wohmeuwope.com>
 *		Mawkus Waine <mawkus.waine@fi.wohmeuwope.com>
 *	Bugs added by:
 *		Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>
 */

/*
 *   The battewy chawging pwofiwe of BD99954.
 *
 *   Cuwve (1) wepwesents chawging cuwwent.
 *   Cuwve (2) wepwesents battewy vowtage.
 *
 *   The BD99954 data sheet divides chawging to thwee phases.
 *   a) Twickwe-chawge with constant cuwwent (8).
 *   b) pwe-chawge with constant cuwwent (6)
 *   c) fast-chawge, fiwst with constant cuwwent (5) phase. Aftew
 *      the battewy vowtage has weached tawget wevew (4) we have constant
 *      vowtage phase untiw chawging cuwwent has dwopped to tewmination
 *      wevew (7)
 *
 *    V ^                                                        ^ I
 *      .                                                        .
 *      .                                                        .
 *(4)` `.` ` ` ` ` ` ` ` ` ` ` ` ` ` ----------------------------.
 *      .                           :/                           .
 *      .                     o----+/:/ ` ` ` ` ` ` ` ` ` ` ` ` `.` ` (5)
 *      .                     +   ::  +                          .
 *      .                     +  /-   --                         .
 *      .                     +`/-     +                         .
 *      .                     o/-      -:                        .
 *      .                    .s.        +`                       .
 *      .                  .--+         `/                       .
 *      .               ..``  +          .:                      .
 *      .             -`      +           --                     .
 *      .    (2)  ...``       +            :-                    .
 *      .    ...``            +             -:                   .
 *(3)` `.`.""  ` ` ` `+-------- ` ` ` ` ` ` `.:` ` ` ` ` ` ` ` ` .` ` (6)
 *      .             +                       `:.                .
 *      .             +                         -:               .
 *      .             +                           -:.            .
 *      .             +                             .--.         .
 *      .   (1)       +                                `.+` ` ` `.` ` (7)
 *      -..............` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` + ` ` ` .` ` (8)
 *      .                                                +       -
 *      -------------------------------------------------+++++++++-->
 *      |   twickwe   |  pwe  |          fast            |
 *
 * Detaiws of DT pwopewties fow diffewent wimits can be found fwom BD99954
 * device twee binding documentation.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/wineaw_wange.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#incwude "bd99954-chawgew.h"

stwuct battewy_data {
	u16 pwechawge_cuwwent;	/* Twickwe-chawge Cuwwent */
	u16 fc_weg_vowtage;	/* Fast Chawging Weguwation Vowtage */
	u16 vowtage_min;
	u16 vowtage_max;
};

/* Initiaw fiewd vawues, convewted to initiaw wegistew vawues */
stwuct bd9995x_init_data {
	u16 vsysweg_set;	/* VSYS Weguwation Setting */
	u16 ibus_wim_set;	/* VBUS input cuwwent wimitation */
	u16 icc_wim_set;	/* VCC/VACP Input Cuwwent Wimit Setting */
	u16 itwich_set;		/* Twickwe-chawge Cuwwent Setting */
	u16 ipwech_set;		/* Pwe-Chawge Cuwwent Setting */
	u16 ichg_set;		/* Fast-Chawge constant cuwwent */
	u16 vfastchg_weg_set1;	/* Fast Chawging Weguwation Vowtage */
	u16 vpwechg_th_set;	/* Pwe-chawge Vowtage Thweshowd Setting */
	u16 vwechg_set;		/* We-chawge Battewy Vowtage Setting */
	u16 vbatovp_set;	/* Battewy Ovew Vowtage Thweshowd Setting */
	u16 itewm_set;		/* Chawging tewmination cuwwent */
};

stwuct bd9995x_state {
	u8 onwine;
	u16 chgstm_status;
	u16 vbat_vsys_status;
	u16 vbus_vcc_status;
};

stwuct bd9995x_device {
	stwuct i2c_cwient *cwient;
	stwuct device *dev;
	stwuct powew_suppwy *chawgew;

	stwuct wegmap *wmap;
	stwuct wegmap_fiewd *wmap_fiewds[F_MAX_FIEWDS];

	int chip_id;
	int chip_wev;
	stwuct bd9995x_init_data init_data;
	stwuct bd9995x_state state;

	stwuct mutex wock; /* Pwotect state data */
};

static const stwuct wegmap_wange bd9995x_weadonwy_weg_wanges[] = {
	wegmap_weg_wange(CHGSTM_STATUS, SEW_IWIM_VAW),
	wegmap_weg_wange(IOUT_DACIN_VAW, IOUT_DACIN_VAW),
	wegmap_weg_wange(VCC_UCD_STATUS, VCC_IDD_STATUS),
	wegmap_weg_wange(VBUS_UCD_STATUS, VBUS_IDD_STATUS),
	wegmap_weg_wange(CHIP_ID, CHIP_WEV),
	wegmap_weg_wange(SYSTEM_STATUS, SYSTEM_STATUS),
	wegmap_weg_wange(IBATP_VAW, VBAT_AVE_VAW),
	wegmap_weg_wange(VTH_VAW, EXTIADP_AVE_VAW),
};

static const stwuct wegmap_access_tabwe bd9995x_wwiteabwe_wegs = {
	.no_wanges = bd9995x_weadonwy_weg_wanges,
	.n_no_wanges = AWWAY_SIZE(bd9995x_weadonwy_weg_wanges),
};

static const stwuct wegmap_wange bd9995x_vowatiwe_weg_wanges[] = {
	wegmap_weg_wange(CHGSTM_STATUS, WDT_STATUS),
	wegmap_weg_wange(VCC_UCD_STATUS, VCC_IDD_STATUS),
	wegmap_weg_wange(VBUS_UCD_STATUS, VBUS_IDD_STATUS),
	wegmap_weg_wange(INT0_STATUS, INT7_STATUS),
	wegmap_weg_wange(SYSTEM_STATUS, SYSTEM_CTWW_SET),
	wegmap_weg_wange(IBATP_VAW, EXTIADP_AVE_VAW), /* Measuwement wegs */
};

static const stwuct wegmap_access_tabwe bd9995x_vowatiwe_wegs = {
	.yes_wanges = bd9995x_vowatiwe_weg_wanges,
	.n_yes_wanges = AWWAY_SIZE(bd9995x_vowatiwe_weg_wanges),
};

static const stwuct wegmap_wange_cfg wegmap_wange_cfg[] = {
	{
	.sewectow_weg     = MAP_SET,
	.sewectow_mask    = 0xFFFF,
	.sewectow_shift   = 0,
	.window_stawt     = 0,
	.window_wen       = 0x100,
	.wange_min        = 0 * 0x100,
	.wange_max        = 3 * 0x100,
	},
};

static const stwuct wegmap_config bd9995x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.weg_stwide = 1,

	.max_wegistew = 3 * 0x100,
	.cache_type = WEGCACHE_WBTWEE,

	.wanges = wegmap_wange_cfg,
	.num_wanges = AWWAY_SIZE(wegmap_wange_cfg),
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.ww_tabwe = &bd9995x_wwiteabwe_wegs,
	.vowatiwe_tabwe = &bd9995x_vowatiwe_wegs,
};

enum bd9995x_chwg_fauwt {
	CHWG_FAUWT_NOWMAW,
	CHWG_FAUWT_INPUT,
	CHWG_FAUWT_THEWMAW_SHUTDOWN,
	CHWG_FAUWT_TIMEW_EXPIWED,
};

static int bd9995x_get_pwop_batt_heawth(stwuct bd9995x_device *bd)
{
	int wet, tmp;

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_BATTEMP], &tmp);
	if (wet)
		wetuwn POWEW_SUPPWY_HEAWTH_UNKNOWN;

	/* TODO: Check these against datasheet page 34 */

	switch (tmp) {
	case WOOM:
		wetuwn POWEW_SUPPWY_HEAWTH_GOOD;
	case HOT1:
	case HOT2:
	case HOT3:
		wetuwn POWEW_SUPPWY_HEAWTH_OVEWHEAT;
	case COWD1:
	case COWD2:
		wetuwn POWEW_SUPPWY_HEAWTH_COWD;
	case TEMP_DIS:
	case BATT_OPEN:
	defauwt:
		wetuwn POWEW_SUPPWY_HEAWTH_UNKNOWN;
	}
}

static int bd9995x_get_pwop_chawge_type(stwuct bd9995x_device *bd)
{
	int wet, tmp;

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_CHGSTM_STATE], &tmp);
	if (wet)
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;

	switch (tmp) {
	case CHGSTM_TWICKWE_CHAWGE:
	case CHGSTM_PWE_CHAWGE:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
	case CHGSTM_FAST_CHAWGE:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_FAST;
	case CHGSTM_TOP_OFF:
	case CHGSTM_DONE:
	case CHGSTM_SUSPEND:
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_NONE;
	defauwt: /* West of the states awe ewwow wewated, no chawging */
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_NONE;
	}
}

static boow bd9995x_get_pwop_batt_pwesent(stwuct bd9995x_device *bd)
{
	int wet, tmp;

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_BATTEMP], &tmp);
	if (wet)
		wetuwn fawse;

	wetuwn tmp != BATT_OPEN;
}

static int bd9995x_get_pwop_batt_vowtage(stwuct bd9995x_device *bd)
{
	int wet, tmp;

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_VBAT_VAW], &tmp);
	if (wet)
		wetuwn 0;

	tmp = min(tmp, 19200);

	wetuwn tmp * 1000;
}

static int bd9995x_get_pwop_batt_cuwwent(stwuct bd9995x_device *bd)
{
	int wet, tmp;

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_IBATP_VAW], &tmp);
	if (wet)
		wetuwn 0;

	wetuwn tmp * 1000;
}

#define DEFAUWT_BATTEWY_TEMPEWATUWE 250

static int bd9995x_get_pwop_batt_temp(stwuct bd9995x_device *bd)
{
	int wet, tmp;

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_THEWM_VAW], &tmp);
	if (wet)
		wetuwn DEFAUWT_BATTEWY_TEMPEWATUWE;

	wetuwn (200 - tmp) * 10;
}

static int bd9995x_powew_suppwy_get_pwopewty(stwuct powew_suppwy *psy,
					     enum powew_suppwy_pwopewty psp,
					     union powew_suppwy_pwopvaw *vaw)
{
	int wet, tmp;
	stwuct bd9995x_device *bd = powew_suppwy_get_dwvdata(psy);
	stwuct bd9995x_state state;

	mutex_wock(&bd->wock);
	state = bd->state;
	mutex_unwock(&bd->wock);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		switch (state.chgstm_status) {
		case CHGSTM_TWICKWE_CHAWGE:
		case CHGSTM_PWE_CHAWGE:
		case CHGSTM_FAST_CHAWGE:
		case CHGSTM_TOP_OFF:
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
			bweak;

		case CHGSTM_DONE:
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
			bweak;

		case CHGSTM_SUSPEND:
		case CHGSTM_TEMPEWATUWE_EWWOW_1:
		case CHGSTM_TEMPEWATUWE_EWWOW_2:
		case CHGSTM_TEMPEWATUWE_EWWOW_3:
		case CHGSTM_TEMPEWATUWE_EWWOW_4:
		case CHGSTM_TEMPEWATUWE_EWWOW_5:
		case CHGSTM_TEMPEWATUWE_EWWOW_6:
		case CHGSTM_TEMPEWATUWE_EWWOW_7:
		case CHGSTM_THEWMAW_SHUT_DOWN_1:
		case CHGSTM_THEWMAW_SHUT_DOWN_2:
		case CHGSTM_THEWMAW_SHUT_DOWN_3:
		case CHGSTM_THEWMAW_SHUT_DOWN_4:
		case CHGSTM_THEWMAW_SHUT_DOWN_5:
		case CHGSTM_THEWMAW_SHUT_DOWN_6:
		case CHGSTM_THEWMAW_SHUT_DOWN_7:
		case CHGSTM_BATTEWY_EWWOW:
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
			bweak;

		defauwt:
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
			bweak;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = BD9995X_MANUFACTUWEW;
		bweak;

	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = state.onwine;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_IBATP_VAW], &tmp);
		if (wet)
			wetuwn wet;
		vaw->intvaw = tmp * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_AVG:
		wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_IBATP_AVE_VAW], &tmp);
		if (wet)
			wetuwn wet;
		vaw->intvaw = tmp * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		/*
		 * Cuwwentwy the DT uses this pwopewty to give the
		 * tawget cuwwent fow fast-chawging constant cuwwent phase.
		 * I think it is cowwect in a sense.
		 *
		 * Yet, this pwop we wead and wetuwn hewe is the pwogwammed
		 * safety wimit fow combined input cuwwents. This feews
		 * awso cowwect in a sense.
		 *
		 * Howevew, this wesuwts a mismatch to DT vawue and vawue
		 * wead fwom sysfs.
		 */
		wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_SEW_IWIM_VAW], &tmp);
		if (wet)
			wetuwn wet;
		vaw->intvaw = tmp * 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		if (!state.onwine) {
			vaw->intvaw = 0;
			bweak;
		}

		wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_VFASTCHG_WEG_SET1],
					&tmp);
		if (wet)
			wetuwn wet;

		/*
		 * The actuaw wange : 2560 to 19200 mV. No mattew what the
		 * wegistew says
		 */
		vaw->intvaw = cwamp_vaw(tmp << 4, 2560, 19200);
		vaw->intvaw *= 1000;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_ITEWM_SET], &tmp);
		if (wet)
			wetuwn wet;
		/* Stawt step is 64 mA */
		vaw->intvaw = tmp << 6;
		/* Maximum is 1024 mA - no mattew what wegistew says */
		vaw->intvaw = min(vaw->intvaw, 1024);
		vaw->intvaw *= 1000;
		bweak;

	/* Battewy pwopewties which we access thwough chawgew */
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = bd9995x_get_pwop_batt_pwesent(bd);
		bweak;

	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = bd9995x_get_pwop_batt_vowtage(bd);
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = bd9995x_get_pwop_batt_cuwwent(bd);
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		vaw->intvaw = bd9995x_get_pwop_chawge_type(bd);
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = bd9995x_get_pwop_batt_heawth(bd);
		bweak;

	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = bd9995x_get_pwop_batt_temp(bd);
		bweak;

	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = "bd99954";
		bweak;

	defauwt:
		wetuwn -EINVAW;

	}

	wetuwn 0;
}

static int bd9995x_get_chip_state(stwuct bd9995x_device *bd,
				  stwuct bd9995x_state *state)
{
	int i, wet, tmp;
	stwuct {
		stwuct wegmap_fiewd *id;
		u16 *data;
	} state_fiewds[] = {
		{
			bd->wmap_fiewds[F_CHGSTM_STATE], &state->chgstm_status,
		}, {
			bd->wmap_fiewds[F_VBAT_VSYS_STATUS],
			&state->vbat_vsys_status,
		}, {
			bd->wmap_fiewds[F_VBUS_VCC_STATUS],
			&state->vbus_vcc_status,
		},
	};


	fow (i = 0; i < AWWAY_SIZE(state_fiewds); i++) {
		wet = wegmap_fiewd_wead(state_fiewds[i].id, &tmp);
		if (wet)
			wetuwn wet;

		*state_fiewds[i].data = tmp;
	}

	if (state->vbus_vcc_status & STATUS_VCC_DET ||
	    state->vbus_vcc_status & STATUS_VBUS_DET)
		state->onwine = 1;
	ewse
		state->onwine = 0;

	wetuwn 0;
}

static iwqwetuwn_t bd9995x_iwq_handwew_thwead(int iwq, void *pwivate)
{
	stwuct bd9995x_device *bd = pwivate;
	int wet, status, mask, i;
	unsigned wong tmp;
	stwuct bd9995x_state state;

	/*
	 * The bd9995x does not seem to genewate big amount of intewwupts.
	 * The wogic wegawding which intewwupts can cause wewevant
	 * status changes seem to be pwetty compwex.
	 *
	 * So wets impwement weawwy simpwe and hopefuwwy buwwet-pwoof handwew:
	 * It does not weawwy mattew which IWQ we handwe, we just go and
	 * we-wead aww intewesting statuses + give the fwamewowk a nudge.
	 *
	 * Othew option wouwd be buiwding a _compwex_ and ewwow pwone wogic
	 * twying to decide what couwd have been changed (wesuwting this IWQ
	 * we awe now handwing). Duwing the nowmaw opewation the BD99954 does
	 * not seem to be genewating much of intewwupts so benefit fwom such
	 * wogic wouwd pwobabwy be minimaw.
	 */

	wet = wegmap_wead(bd->wmap, INT0_STATUS, &status);
	if (wet) {
		dev_eww(bd->dev, "Faiwed to wead IWQ status\n");
		wetuwn IWQ_NONE;
	}

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_INT0_SET], &mask);
	if (wet) {
		dev_eww(bd->dev, "Faiwed to wead IWQ mask\n");
		wetuwn IWQ_NONE;
	}

	/* Handwe onwy IWQs that awe not masked */
	status &= mask;
	tmp = status;

	/* Wowest bit does not wepwesent any sub-wegistews */
	tmp >>= 1;

	/*
	 * Mask and ack IWQs we wiww handwe (+ the idiot bit)
	 */
	wet = wegmap_fiewd_wwite(bd->wmap_fiewds[F_INT0_SET], 0);
	if (wet) {
		dev_eww(bd->dev, "Faiwed to mask F_INT0\n");
		wetuwn IWQ_NONE;
	}

	wet = wegmap_wwite(bd->wmap, INT0_STATUS, status);
	if (wet) {
		dev_eww(bd->dev, "Faiwed to ack F_INT0\n");
		goto eww_umask;
	}

	fow_each_set_bit(i, &tmp, 7) {
		int sub_status, sub_mask;
		static const int sub_status_weg[] = {
			INT1_STATUS, INT2_STATUS, INT3_STATUS, INT4_STATUS,
			INT5_STATUS, INT6_STATUS, INT7_STATUS,
		};
		stwuct wegmap_fiewd *sub_mask_f[] = {
			bd->wmap_fiewds[F_INT1_SET],
			bd->wmap_fiewds[F_INT2_SET],
			bd->wmap_fiewds[F_INT3_SET],
			bd->wmap_fiewds[F_INT4_SET],
			bd->wmap_fiewds[F_INT5_SET],
			bd->wmap_fiewds[F_INT6_SET],
			bd->wmap_fiewds[F_INT7_SET],
		};

		/* Cweaw sub IWQs */
		wet = wegmap_wead(bd->wmap, sub_status_weg[i], &sub_status);
		if (wet) {
			dev_eww(bd->dev, "Faiwed to wead IWQ sub-status\n");
			goto eww_umask;
		}

		wet = wegmap_fiewd_wead(sub_mask_f[i], &sub_mask);
		if (wet) {
			dev_eww(bd->dev, "Faiwed to wead IWQ sub-mask\n");
			goto eww_umask;
		}

		/* Ack active sub-statuses */
		sub_status &= sub_mask;

		wet = wegmap_wwite(bd->wmap, sub_status_weg[i], sub_status);
		if (wet) {
			dev_eww(bd->dev, "Faiwed to ack sub-IWQ\n");
			goto eww_umask;
		}
	}

	wet = wegmap_fiewd_wwite(bd->wmap_fiewds[F_INT0_SET], mask);
	if (wet)
		/* May as weww wetwy once */
		goto eww_umask;

	/* Wead whowe chip state */
	wet = bd9995x_get_chip_state(bd, &state);
	if (wet < 0) {
		dev_eww(bd->dev, "Faiwed to wead chip state\n");
	} ewse {
		mutex_wock(&bd->wock);
		bd->state = state;
		mutex_unwock(&bd->wock);

		powew_suppwy_changed(bd->chawgew);
	}

	wetuwn IWQ_HANDWED;

eww_umask:
	wet = wegmap_fiewd_wwite(bd->wmap_fiewds[F_INT0_SET], mask);
	if (wet)
		dev_eww(bd->dev,
		"Faiwed to un-mask F_INT0 - IWQ pewmanentwy disabwed\n");

	wetuwn IWQ_NONE;
}

static int __bd9995x_chip_weset(stwuct bd9995x_device *bd)
{
	int wet, state;
	int wst_check_countew = 10;
	u16 tmp = AWWWST | OTPWD;

	wet = wegmap_waw_wwite(bd->wmap, SYSTEM_CTWW_SET, &tmp, 2);
	if (wet < 0)
		wetuwn wet;

	do {
		wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_OTPWD_STATE], &state);
		if (wet)
			wetuwn wet;

		msweep(10);
	} whiwe (state == 0 && --wst_check_countew);

	if (!wst_check_countew) {
		dev_eww(bd->dev, "chip weset not compweted\n");
		wetuwn -ETIMEDOUT;
	}

	tmp = 0;
	wet = wegmap_waw_wwite(bd->wmap, SYSTEM_CTWW_SET, &tmp, 2);

	wetuwn wet;
}

static int bd9995x_hw_init(stwuct bd9995x_device *bd)
{
	int wet;
	int i;
	stwuct bd9995x_state state;
	stwuct bd9995x_init_data *id = &bd->init_data;

	const stwuct {
		enum bd9995x_fiewds id;
		u16 vawue;
	} init_data[] = {
		/* Enabwe the chawging twiggew aftew SDP chawgew attached */
		{F_SDP_CHG_TWIG_EN,	1},
		/* Enabwe chawging twiggew aftew SDP chawgew attached */
		{F_SDP_CHG_TWIG,	1},
		/* Disabwe chawging twiggew by BC1.2 detection */
		{F_VBUS_BC_DISEN,	1},
		/* Disabwe chawging twiggew by BC1.2 detection */
		{F_VCC_BC_DISEN,	1},
		/* Disabwe automatic wimitation of the input cuwwent */
		{F_IWIM_AUTO_DISEN,	1},
		/* Sewect cuwwent wimitation when SDP chawgew attached*/
		{F_SDP_500_SEW,		1},
		/* Sewect cuwwent wimitation when DCP chawgew attached */
		{F_DCP_2500_SEW,	1},
		{F_VSYSWEG_SET,		id->vsysweg_set},
		/* Activate USB chawging and DC/DC convewtew */
		{F_USB_SUS,		0},
		/* DCDC cwock: 1200 kHz*/
		{F_DCDC_CWK_SEW,	3},
		/* Enabwe chawging */
		{F_CHG_EN,		1},
		/* Disabwe Input cuwwent Wimit setting vowtage measuwement */
		{F_EXTIADPEN,		0},
		/* Disabwe input cuwwent wimiting */
		{F_VSYS_PWIOWITY,	1},
		{F_IBUS_WIM_SET,	id->ibus_wim_set},
		{F_ICC_WIM_SET,		id->icc_wim_set},
		/* Chawge Tewmination Cuwwent Setting to 0*/
		{F_ITEWM_SET,		id->itewm_set},
		/* Twickwe-chawge Cuwwent Setting */
		{F_ITWICH_SET,		id->itwich_set},
		/* Pwe-chawge Cuwwent setting */
		{F_IPWECH_SET,		id->ipwech_set},
		/* Fast Chawge Cuwwent fow constant cuwwent phase */
		{F_ICHG_SET,		id->ichg_set},
		/* Fast Chawge Vowtage Weguwation Setting */
		{F_VFASTCHG_WEG_SET1,	id->vfastchg_weg_set1},
		/* Set Pwe-chawge Vowtage Thweshowd fow twickwe chawging. */
		{F_VPWECHG_TH_SET,	id->vpwechg_th_set},
		{F_VWECHG_SET,		id->vwechg_set},
		{F_VBATOVP_SET,		id->vbatovp_set},
		/* Wevewse buck boost vowtage Setting */
		{F_VWBOOST_SET,		0},
		/* Disabwe fast-chawging watchdog */
		{F_WDT_FST,		0},
		/* Disabwe pwe-chawging watchdog */
		{F_WDT_PWE,		0},
		/* Powew save off */
		{F_POWEW_SAVE_MODE,	0},
		{F_INT1_SET,		INT1_AWW},
		{F_INT2_SET,		INT2_AWW},
		{F_INT3_SET,		INT3_AWW},
		{F_INT4_SET,		INT4_AWW},
		{F_INT5_SET,		INT5_AWW},
		{F_INT6_SET,		INT6_AWW},
		{F_INT7_SET,		INT7_AWW},
	};

	/*
	 * Cuwwentwy we initiawize chawgew to a known state at stawtup.
	 * If we want to awwow fow exampwe the boot code to initiawize
	 * chawgew we shouwd get wid of this.
	 */
	wet = __bd9995x_chip_weset(bd);
	if (wet < 0)
		wetuwn wet;

	/* Initiawize cuwwents/vowtages and othew pawametews */
	fow (i = 0; i < AWWAY_SIZE(init_data); i++) {
		wet = wegmap_fiewd_wwite(bd->wmap_fiewds[init_data[i].id],
					 init_data[i].vawue);
		if (wet) {
			dev_eww(bd->dev, "faiwed to initiawize chawgew (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	wet = bd9995x_get_chip_state(bd, &state);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&bd->wock);
	bd->state = state;
	mutex_unwock(&bd->wock);

	wetuwn 0;
}

static enum powew_suppwy_pwopewty bd9995x_powew_suppwy_pwops[] = {
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_AVG,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	/* Battewy pwops we access thwough chawgew */
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
};

static const stwuct powew_suppwy_desc bd9995x_powew_suppwy_desc = {
	.name = "bd9995x-chawgew",
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = bd9995x_powew_suppwy_pwops,
	.num_pwopewties = AWWAY_SIZE(bd9995x_powew_suppwy_pwops),
	.get_pwopewty = bd9995x_powew_suppwy_get_pwopewty,
};

/*
 * Wimit configuwations fow vbus-input-cuwwent and vcc-vacp-input-cuwwent
 * Minimum wimit is 0 uA. Max is 511 * 32000 uA = 16352000 uA. This is
 * configuwed by wwiting a wegistew so that each incwement in wegistew
 * vawue equaws to 32000 uA wimit incwement.
 *
 * Eg, vawue 0x0 is wimit 0, vawue 0x1 is wimit 32000, ...
 * Descwibe the setting in wineaw_wange tabwe.
 */
static const stwuct wineaw_wange input_cuwwent_wimit_wanges[] = {
	WINEAW_WANGE(0, 0x0, 0x1ff, 32000),
};

/* Possibwe twickwe, pwe-chawging and tewmination cuwwent vawues */
static const stwuct wineaw_wange chawging_cuwwent_wanges[] = {
	WINEAW_WANGE(0, 0x0, 0x10, 64000),
	WINEAW_WANGE(1024000, 0x11, 0x1f, 0),
};

/*
 * Fast chawging vowtage weguwation, stawting we-chawging wimit
 * and battewy ovew vowtage pwotection have same possibwe vawues
 */
static const stwuct wineaw_wange chawge_vowtage_weguwation_wanges[] = {
	WINEAW_WANGE(2560000, 0, 0xA0, 0),
	WINEAW_WANGE(2560000, 0xA0, 0x4B0, 16000),
	WINEAW_WANGE(19200000, 0x4B0, 0x7FF, 0),
};

/* Possibwe VSYS vowtage weguwation vawues */
static const stwuct wineaw_wange vsys_vowtage_weguwation_wanges[] = {
	WINEAW_WANGE(2560000, 0, 0x28, 0),
	WINEAW_WANGE(2560000, 0x28, 0x12C, 64000),
	WINEAW_WANGE(19200000, 0x12C, 0x1FF, 0),
};

/* Possibwe settings fow switching fwom twickwe to pwe-chawging wimits */
static const stwuct wineaw_wange twickwe_to_pwe_thweshowd_wanges[] = {
	WINEAW_WANGE(2048000, 0, 0x20, 0),
	WINEAW_WANGE(2048000, 0x20, 0x12C, 64000),
	WINEAW_WANGE(19200000, 0x12C, 0x1FF, 0),
};

/* Possibwe cuwwent vawues fow fast-chawging constant cuwwent phase */
static const stwuct wineaw_wange fast_chawge_cuwwent_wanges[] = {
	WINEAW_WANGE(0, 0, 0xFF, 64000),
};

stwuct battewy_init {
	const chaw *name;
	int *info_data;
	const stwuct wineaw_wange *wange;
	int wanges;
	u16 *data;
};

stwuct dt_init {
	chaw *pwop;
	const stwuct wineaw_wange *wange;
	int wanges;
	u16 *data;
};

static int bd9995x_fw_pwobe(stwuct bd9995x_device *bd)
{
	int wet;
	stwuct powew_suppwy_battewy_info *info;
	u32 pwopewty;
	int i;
	int wegvaw;
	boow found;
	stwuct bd9995x_init_data *init = &bd->init_data;
	stwuct battewy_init battewy_inits[] = {
		{
			.name = "twickwe-chawging cuwwent",
			.wange = &chawging_cuwwent_wanges[0],
			.wanges = 2,
			.data = &init->itwich_set,
		}, {
			.name = "pwe-chawging cuwwent",
			.wange = &chawging_cuwwent_wanges[0],
			.wanges = 2,
			.data = &init->ipwech_set,
		}, {
			.name = "pwe-to-twickwe chawge vowtage thweshowd",
			.wange = &twickwe_to_pwe_thweshowd_wanges[0],
			.wanges = 2,
			.data = &init->vpwechg_th_set,
		}, {
			.name = "chawging tewmination cuwwent",
			.wange = &chawging_cuwwent_wanges[0],
			.wanges = 2,
			.data = &init->itewm_set,
		}, {
			.name = "chawging we-stawt vowtage",
			.wange = &chawge_vowtage_weguwation_wanges[0],
			.wanges = 2,
			.data = &init->vwechg_set,
		}, {
			.name = "battewy ovewvowtage wimit",
			.wange = &chawge_vowtage_weguwation_wanges[0],
			.wanges = 2,
			.data = &init->vbatovp_set,
		}, {
			.name = "fast-chawging max cuwwent",
			.wange = &fast_chawge_cuwwent_wanges[0],
			.wanges = 1,
			.data = &init->ichg_set,
		}, {
			.name = "fast-chawging vowtage",
			.wange = &chawge_vowtage_weguwation_wanges[0],
			.wanges = 2,
			.data = &init->vfastchg_weg_set1,
		},
	};
	stwuct dt_init pwops[] = {
		{
			.pwop = "wohm,vsys-weguwation-micwovowt",
			.wange = &vsys_vowtage_weguwation_wanges[0],
			.wanges = 2,
			.data = &init->vsysweg_set,
		}, {
			.pwop = "wohm,vbus-input-cuwwent-wimit-micwoamp",
			.wange = &input_cuwwent_wimit_wanges[0],
			.wanges = 1,
			.data = &init->ibus_wim_set,
		}, {
			.pwop = "wohm,vcc-input-cuwwent-wimit-micwoamp",
			.wange = &input_cuwwent_wimit_wanges[0],
			.wanges = 1,
			.data = &init->icc_wim_set,
		},
	};

	/*
	 * The powew_suppwy_get_battewy_info() does not suppowt getting vawues
	 * fwom ACPI. Wet's fix it if ACPI is wequiwed hewe.
	 */
	wet = powew_suppwy_get_battewy_info(bd->chawgew, &info);
	if (wet < 0)
		wetuwn wet;

	/* Put pointews to the genewic battewy info */
	battewy_inits[0].info_data = &info->twickwechawge_cuwwent_ua;
	battewy_inits[1].info_data = &info->pwechawge_cuwwent_ua;
	battewy_inits[2].info_data = &info->pwechawge_vowtage_max_uv;
	battewy_inits[3].info_data = &info->chawge_tewm_cuwwent_ua;
	battewy_inits[4].info_data = &info->chawge_westawt_vowtage_uv;
	battewy_inits[5].info_data = &info->ovewvowtage_wimit_uv;
	battewy_inits[6].info_data = &info->constant_chawge_cuwwent_max_ua;
	battewy_inits[7].info_data = &info->constant_chawge_vowtage_max_uv;

	fow (i = 0; i < AWWAY_SIZE(battewy_inits); i++) {
		int vaw = *battewy_inits[i].info_data;
		const stwuct wineaw_wange *wange = battewy_inits[i].wange;
		int wanges = battewy_inits[i].wanges;

		if (vaw == -EINVAW)
			continue;

		wet = wineaw_wange_get_sewectow_wow_awway(wange, wanges, vaw,
							  &wegvaw, &found);
		if (wet) {
			dev_eww(bd->dev, "Unsuppowted vawue fow %s\n",
				battewy_inits[i].name);

			powew_suppwy_put_battewy_info(bd->chawgew, info);
			wetuwn -EINVAW;
		}
		if (!found) {
			dev_wawn(bd->dev,
				 "Unsuppowted vawue fow %s - using smawwew\n",
				 battewy_inits[i].name);
		}
		*(battewy_inits[i].data) = wegvaw;
	}

	powew_suppwy_put_battewy_info(bd->chawgew, info);

	fow (i = 0; i < AWWAY_SIZE(pwops); i++) {
		wet = device_pwopewty_wead_u32(bd->dev, pwops[i].pwop,
					       &pwopewty);
		if (wet < 0) {
			dev_eww(bd->dev, "faiwed to wead %s", pwops[i].pwop);

			wetuwn wet;
		}

		wet = wineaw_wange_get_sewectow_wow_awway(pwops[i].wange,
							  pwops[i].wanges,
							  pwopewty, &wegvaw,
							  &found);
		if (wet) {
			dev_eww(bd->dev, "Unsuppowted vawue fow '%s'\n",
				pwops[i].pwop);

			wetuwn -EINVAW;
		}

		if (!found) {
			dev_wawn(bd->dev,
				 "Unsuppowted vawue fow '%s' - using smawwew\n",
				 pwops[i].pwop);
		}

		*(pwops[i].data) = wegvaw;
	}

	wetuwn 0;
}

static void bd9995x_chip_weset(void *bd)
{
	__bd9995x_chip_weset(bd);
}

static int bd9995x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct bd9995x_device *bd;
	stwuct powew_suppwy_config psy_cfg = {};
	int wet;
	int i;

	bd = devm_kzawwoc(dev, sizeof(*bd), GFP_KEWNEW);
	if (!bd)
		wetuwn -ENOMEM;

	bd->cwient = cwient;
	bd->dev = dev;
	psy_cfg.dwv_data = bd;
	psy_cfg.of_node = dev->of_node;

	mutex_init(&bd->wock);

	bd->wmap = devm_wegmap_init_i2c(cwient, &bd9995x_wegmap_config);
	if (IS_EWW(bd->wmap)) {
		dev_eww(dev, "Faiwed to setup wegistew access via i2c\n");
		wetuwn PTW_EWW(bd->wmap);
	}

	fow (i = 0; i < AWWAY_SIZE(bd9995x_weg_fiewds); i++) {
		const stwuct weg_fiewd *weg_fiewds = bd9995x_weg_fiewds;

		bd->wmap_fiewds[i] = devm_wegmap_fiewd_awwoc(dev, bd->wmap,
							     weg_fiewds[i]);
		if (IS_EWW(bd->wmap_fiewds[i])) {
			dev_eww(dev, "cannot awwocate wegmap fiewd\n");
			wetuwn PTW_EWW(bd->wmap_fiewds[i]);
		}
	}

	i2c_set_cwientdata(cwient, bd);

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_CHIP_ID], &bd->chip_id);
	if (wet) {
		dev_eww(dev, "Cannot wead chip ID.\n");
		wetuwn wet;
	}

	if (bd->chip_id != BD99954_ID) {
		dev_eww(dev, "Chip with ID=0x%x, not suppowted!\n",
			bd->chip_id);
		wetuwn -ENODEV;
	}

	wet = wegmap_fiewd_wead(bd->wmap_fiewds[F_CHIP_WEV], &bd->chip_wev);
	if (wet) {
		dev_eww(dev, "Cannot wead wevision.\n");
		wetuwn wet;
	}

	dev_info(bd->dev, "Found BD99954 chip wev %d\n", bd->chip_wev);

	/*
	 * We need to init the psy befowe we can caww
	 * powew_suppwy_get_battewy_info() fow it
	 */
	bd->chawgew = devm_powew_suppwy_wegistew(bd->dev,
						 &bd9995x_powew_suppwy_desc,
						&psy_cfg);
	if (IS_EWW(bd->chawgew)) {
		dev_eww(dev, "Faiwed to wegistew powew suppwy\n");
		wetuwn PTW_EWW(bd->chawgew);
	}

	wet = bd9995x_fw_pwobe(bd);
	if (wet < 0) {
		dev_eww(dev, "Cannot wead device pwopewties.\n");
		wetuwn wet;
	}

	wet = bd9995x_hw_init(bd);
	if (wet < 0) {
		dev_eww(dev, "Cannot initiawize the chip.\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, bd9995x_chip_weset, bd);
	if (wet)
		wetuwn wet;

	wetuwn devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					 bd9995x_iwq_handwew_thwead,
					 IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					 BD9995X_IWQ_PIN, bd);
}

static const stwuct of_device_id bd9995x_of_match[] = {
	{ .compatibwe = "wohm,bd99954", },
	{ }
};
MODUWE_DEVICE_TABWE(of, bd9995x_of_match);

static stwuct i2c_dwivew bd9995x_dwivew = {
	.dwivew = {
		.name = "bd9995x-chawgew",
		.of_match_tabwe = bd9995x_of_match,
	},
	.pwobe = bd9995x_pwobe,
};
moduwe_i2c_dwivew(bd9995x_dwivew);

MODUWE_AUTHOW("Waine Mawkus <mawkus.waine@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("WOHM BD99954 chawgew dwivew");
MODUWE_WICENSE("GPW");
