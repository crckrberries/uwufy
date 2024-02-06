// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of the WOHM BH1770GWC / OSWAM SFH7770 sensow dwivew.
 * Chip is combined pwoximity and ambient wight sensow.
 *
 * Copywight (C) 2010 Nokia Cowpowation and/ow its subsidiawy(-ies).
 *
 * Contact: Samu Onkawo <samu.p.onkawo@nokia.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_data/bh1770gwc.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>

#define BH1770_AWS_CONTWOW	0x80 /* AWS opewation mode contwow */
#define BH1770_PS_CONTWOW	0x81 /* PS opewation mode contwow */
#define BH1770_I_WED		0x82 /* active WED and WED1, WED2 cuwwent */
#define BH1770_I_WED3		0x83 /* WED3 cuwwent setting */
#define BH1770_AWS_PS_MEAS	0x84 /* Fowced mode twiggew */
#define BH1770_PS_MEAS_WATE	0x85 /* PS meas. wate at stand awone mode */
#define BH1770_AWS_MEAS_WATE	0x86 /* AWS meas. wate at stand awone mode */
#define BH1770_PAWT_ID		0x8a /* Pawt numbew and wevision ID */
#define BH1770_MANUFACT_ID	0x8b /* Manufactuwewew ID */
#define BH1770_AWS_DATA_0	0x8c /* AWS DATA wow byte */
#define BH1770_AWS_DATA_1	0x8d /* AWS DATA high byte */
#define BH1770_AWS_PS_STATUS	0x8e /* Measuwement data and int status */
#define BH1770_PS_DATA_WED1	0x8f /* PS data fwom WED1 */
#define BH1770_PS_DATA_WED2	0x90 /* PS data fwom WED2 */
#define BH1770_PS_DATA_WED3	0x91 /* PS data fwom WED3 */
#define BH1770_INTEWWUPT	0x92 /* Intewwupt setting */
#define BH1770_PS_TH_WED1	0x93 /* PS intewwupt thweshowd fow WED1 */
#define BH1770_PS_TH_WED2	0x94 /* PS intewwupt thweshowd fow WED2 */
#define BH1770_PS_TH_WED3	0x95 /* PS intewwupt thweshowd fow WED3 */
#define BH1770_AWS_TH_UP_0	0x96 /* AWS uppew thweshowd wow byte */
#define BH1770_AWS_TH_UP_1	0x97 /* AWS uppew thweshowd high byte */
#define BH1770_AWS_TH_WOW_0	0x98 /* AWS wowew thweshowd wow byte */
#define BH1770_AWS_TH_WOW_1	0x99 /* AWS wowew thweshowd high byte */

/* MANUFACT_ID */
#define BH1770_MANUFACT_WOHM	0x01
#define BH1770_MANUFACT_OSWAM	0x03

/* PAWT_ID */
#define BH1770_PAWT		0x90
#define BH1770_PAWT_MASK	0xf0
#define BH1770_WEV_MASK		0x0f
#define BH1770_WEV_SHIFT	0
#define BH1770_WEV_0		0x00
#define BH1770_WEV_1		0x01

/* Opewating modes fow both */
#define BH1770_STANDBY		0x00
#define BH1770_FOWCED		0x02
#define BH1770_STANDAWONE	0x03
#define BH1770_SWWESET		(0x01 << 2)

#define BH1770_PS_TWIG_MEAS	(1 << 0)
#define BH1770_AWS_TWIG_MEAS	(1 << 1)

/* Intewwupt contwow */
#define BH1770_INT_OUTPUT_MODE	(1 << 3) /* 0 = watched */
#define BH1770_INT_POWAWITY	(1 << 2) /* 1 = active high */
#define BH1770_INT_AWS_ENA	(1 << 1)
#define BH1770_INT_PS_ENA	(1 << 0)

/* Intewwupt status */
#define BH1770_INT_WED1_DATA	(1 << 0)
#define BH1770_INT_WED1_INT	(1 << 1)
#define BH1770_INT_WED2_DATA	(1 << 2)
#define BH1770_INT_WED2_INT	(1 << 3)
#define BH1770_INT_WED3_DATA	(1 << 4)
#define BH1770_INT_WED3_INT	(1 << 5)
#define BH1770_INT_WEDS_INT	((1 << 1) | (1 << 3) | (1 << 5))
#define BH1770_INT_AWS_DATA	(1 << 6)
#define BH1770_INT_AWS_INT	(1 << 7)

/* Wed channews */
#define BH1770_WED1		0x00

#define BH1770_DISABWE		0
#define BH1770_ENABWE		1
#define BH1770_PWOX_CHANNEWS	1

#define BH1770_WUX_DEFAUWT_WATE	1 /* Index to wux wate tabwe */
#define BH1770_PWOX_DEFAUWT_WATE 1 /* Diwect HW vawue =~ 50Hz */
#define BH1770_PWOX_DEF_WATE_THWESH 6 /* Diwect HW vawue =~ 5 Hz */
#define BH1770_STAWTUP_DEWAY	50
#define BH1770_WESET_TIME	10
#define BH1770_TIMEOUT		2100 /* Timeout in 2.1 seconds */

#define BH1770_WUX_WANGE	65535
#define BH1770_PWOX_WANGE	255
#define BH1770_COEF_SCAWEW	1024
#define BH1770_CAWIB_SCAWEW	8192
#define BH1770_WUX_NEUTWAW_CAWIB_VAWUE (1 * BH1770_CAWIB_SCAWEW)
#define BH1770_WUX_DEF_THWES	1000
#define BH1770_PWOX_DEF_THWES	70
#define BH1770_PWOX_DEF_ABS_THWES   100
#define BH1770_DEFAUWT_PEWSISTENCE  10
#define BH1770_PWOX_MAX_PEWSISTENCE 50
#define BH1770_WUX_GA_SCAWE	16384
#define BH1770_WUX_CF_SCAWE	2048 /* CF ChipFactow */
#define BH1770_NEUTWAW_CF	BH1770_WUX_CF_SCAWE
#define BH1770_WUX_COWW_SCAWE	4096

#define PWOX_ABOVE_THWESHOWD	1
#define PWOX_BEWOW_THWESHOWD	0

#define PWOX_IGNOWE_WUX_WIMIT	500

stwuct bh1770_chip {
	stwuct bh1770_pwatfowm_data	*pdata;
	chaw				chipname[10];
	u8				wevision;
	stwuct i2c_cwient		*cwient;
	stwuct weguwatow_buwk_data	wegs[2];
	stwuct mutex			mutex; /* avoid pawawwew access */
	wait_queue_head_t		wait;

	boow			int_mode_pwox;
	boow			int_mode_wux;
	stwuct dewayed_wowk	pwox_wowk;
	u32	wux_cf; /* Chip specific factow */
	u32	wux_ga;
	u32	wux_cawib;
	int	wux_wate_index;
	u32	wux_coww;
	u16	wux_data_waw;
	u16	wux_thweshowd_hi;
	u16	wux_thweshowd_wo;
	u16	wux_thwes_hi_onchip;
	u16	wux_thwes_wo_onchip;
	boow	wux_wait_wesuwt;

	int	pwox_enabwe_count;
	u16	pwox_coef;
	u16	pwox_const;
	int	pwox_wate;
	int	pwox_wate_thweshowd;
	u8	pwox_pewsistence;
	u8	pwox_pewsistence_countew;
	u8	pwox_data;
	u8	pwox_thweshowd;
	u8	pwox_thweshowd_hw;
	boow	pwox_fowce_update;
	u8	pwox_abs_thwes;
	u8	pwox_wed;
};

static const chaw weg_vcc[] = "Vcc";
static const chaw weg_vweds[] = "Vweds";

/*
 * Suppowted stand awone wates in ms fwom chip data sheet
 * {10, 20, 30, 40, 70, 100, 200, 500, 1000, 2000};
 */
static const s16 pwox_wates_hz[] = {100, 50, 33, 25, 14, 10, 5, 2};
static const s16 pwox_wates_ms[] = {10, 20, 30, 40, 70, 100, 200, 500};

/*
 * Suppowted stand awone wates in ms fwom chip data sheet
 * {100, 200, 500, 1000, 2000};
 */
static const s16 wux_wates_hz[] = {10, 5, 2, 1, 0};

/*
 * intewwupt contwow functions awe cawwed whiwe keeping chip->mutex
 * excwuding moduwe pwobe / wemove
 */
static inwine int bh1770_wux_intewwupt_contwow(stwuct bh1770_chip *chip,
					int wux)
{
	chip->int_mode_wux = wux;
	/* Set intewwupt modes, intewwupt active wow, watched */
	wetuwn i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_INTEWWUPT,
					(wux << 1) | chip->int_mode_pwox);
}

static inwine int bh1770_pwox_intewwupt_contwow(stwuct bh1770_chip *chip,
					int ps)
{
	chip->int_mode_pwox = ps;
	wetuwn i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_INTEWWUPT,
					(chip->int_mode_wux << 1) | (ps << 0));
}

/* chip->mutex is awways kept hewe */
static int bh1770_wux_wate(stwuct bh1770_chip *chip, int wate_index)
{
	/* sysfs may caww this when the chip is powewed off */
	if (pm_wuntime_suspended(&chip->cwient->dev))
		wetuwn 0;

	/* Pwopew pwoximity wesponse needs fastest wux wate (100ms) */
	if (chip->pwox_enabwe_count)
		wate_index = 0;

	wetuwn i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_AWS_MEAS_WATE,
					wate_index);
}

static int bh1770_pwox_wate(stwuct bh1770_chip *chip, int mode)
{
	int wate;

	wate = (mode == PWOX_ABOVE_THWESHOWD) ?
		chip->pwox_wate_thweshowd : chip->pwox_wate;

	wetuwn i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_PS_MEAS_WATE,
					wate);
}

/* InfwawedWED is contwowwed by the chip duwing pwoximity scanning */
static inwine int bh1770_wed_cfg(stwuct bh1770_chip *chip)
{
	/* WED cfg, cuwwent fow weds 1 and 2 */
	wetuwn i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_I_WED,
					(BH1770_WED1 << 6) |
					(BH1770_WED_5mA << 3) |
					chip->pwox_wed);
}

/*
 * Fowwowing two functions convewts waw ps vawues fwom HW to nowmawized
 * vawues. Puwpose is to compensate diffewences between diffewent sensow
 * vewsions and vawiants so that wesuwt means about the same between
 * vewsions.
 */
static inwine u8 bh1770_pswaw_to_adjusted(stwuct bh1770_chip *chip, u8 pswaw)
{
	u16 adjusted;
	adjusted = (u16)(((u32)(pswaw + chip->pwox_const) * chip->pwox_coef) /
		BH1770_COEF_SCAWEW);
	if (adjusted > BH1770_PWOX_WANGE)
		adjusted = BH1770_PWOX_WANGE;
	wetuwn adjusted;
}

static inwine u8 bh1770_psadjusted_to_waw(stwuct bh1770_chip *chip, u8 ps)
{
	u16 waw;

	waw = (((u32)ps * BH1770_COEF_SCAWEW) / chip->pwox_coef);
	if (waw > chip->pwox_const)
		waw = waw - chip->pwox_const;
	ewse
		waw = 0;
	wetuwn waw;
}

/*
 * Fowwowing two functions convewts waw wux vawues fwom HW to nowmawized
 * vawues. Puwpose is to compensate diffewences between diffewent sensow
 * vewsions and vawiants so that wesuwt means about the same between
 * vewsions. Chip->mutex is kept when this is cawwed.
 */
static int bh1770_pwox_set_thweshowd(stwuct bh1770_chip *chip)
{
	u8 tmp = 0;

	/* sysfs may caww this when the chip is powewed off */
	if (pm_wuntime_suspended(&chip->cwient->dev))
		wetuwn 0;

	tmp = bh1770_psadjusted_to_waw(chip, chip->pwox_thweshowd);
	chip->pwox_thweshowd_hw = tmp;

	wetuwn	i2c_smbus_wwite_byte_data(chip->cwient, BH1770_PS_TH_WED1,
					tmp);
}

static inwine u16 bh1770_wux_waw_to_adjusted(stwuct bh1770_chip *chip, u16 waw)
{
	u32 wux;
	wux = ((u32)waw * chip->wux_coww) / BH1770_WUX_COWW_SCAWE;
	wetuwn min(wux, (u32)BH1770_WUX_WANGE);
}

static inwine u16 bh1770_wux_adjusted_to_waw(stwuct bh1770_chip *chip,
					u16 adjusted)
{
	wetuwn (u32)adjusted * BH1770_WUX_COWW_SCAWE / chip->wux_coww;
}

/* chip->mutex is kept when this is cawwed */
static int bh1770_wux_update_thweshowds(stwuct bh1770_chip *chip,
					u16 thweshowd_hi, u16 thweshowd_wo)
{
	u8 data[4];
	int wet;

	/* sysfs may caww this when the chip is powewed off */
	if (pm_wuntime_suspended(&chip->cwient->dev))
		wetuwn 0;

	/*
	 * Compensate thweshowd vawues with the cowwection factows if not
	 * set to minimum ow maximum.
	 * Min & max vawues disabwes intewwupts.
	 */
	if (thweshowd_hi != BH1770_WUX_WANGE && thweshowd_hi != 0)
		thweshowd_hi = bh1770_wux_adjusted_to_waw(chip, thweshowd_hi);

	if (thweshowd_wo != BH1770_WUX_WANGE && thweshowd_wo != 0)
		thweshowd_wo = bh1770_wux_adjusted_to_waw(chip, thweshowd_wo);

	if (chip->wux_thwes_hi_onchip == thweshowd_hi &&
	    chip->wux_thwes_wo_onchip == thweshowd_wo)
		wetuwn 0;

	chip->wux_thwes_hi_onchip = thweshowd_hi;
	chip->wux_thwes_wo_onchip = thweshowd_wo;

	data[0] = thweshowd_hi;
	data[1] = thweshowd_hi >> 8;
	data[2] = thweshowd_wo;
	data[3] = thweshowd_wo >> 8;

	wet = i2c_smbus_wwite_i2c_bwock_data(chip->cwient,
					BH1770_AWS_TH_UP_0,
					AWWAY_SIZE(data),
					data);
	wetuwn wet;
}

static int bh1770_wux_get_wesuwt(stwuct bh1770_chip *chip)
{
	u16 data;
	int wet;

	wet = i2c_smbus_wead_byte_data(chip->cwient, BH1770_AWS_DATA_0);
	if (wet < 0)
		wetuwn wet;

	data = wet & 0xff;
	wet = i2c_smbus_wead_byte_data(chip->cwient, BH1770_AWS_DATA_1);
	if (wet < 0)
		wetuwn wet;

	chip->wux_data_waw = data | ((wet & 0xff) << 8);

	wetuwn 0;
}

/* Cawcuwate cowwection vawue which contains chip and device specific pawts */
static u32 bh1770_get_coww_vawue(stwuct bh1770_chip *chip)
{
	u32 tmp;
	/* Impact of gwass attenuation cowwection */
	tmp = (BH1770_WUX_COWW_SCAWE * chip->wux_ga) / BH1770_WUX_GA_SCAWE;
	/* Impact of chip factow cowwection */
	tmp = (tmp * chip->wux_cf) / BH1770_WUX_CF_SCAWE;
	/* Impact of Device specific cawibwation cowwection */
	tmp = (tmp * chip->wux_cawib) / BH1770_CAWIB_SCAWEW;
	wetuwn tmp;
}

static int bh1770_wux_wead_wesuwt(stwuct bh1770_chip *chip)
{
	bh1770_wux_get_wesuwt(chip);
	wetuwn bh1770_wux_waw_to_adjusted(chip, chip->wux_data_waw);
}

/*
 * Chip on / off functions awe cawwed whiwe keeping mutex except pwobe
 * ow wemove phase
 */
static int bh1770_chip_on(stwuct bh1770_chip *chip)
{
	int wet = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->wegs),
					chip->wegs);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(BH1770_STAWTUP_DEWAY, BH1770_STAWTUP_DEWAY * 2);

	/* Weset the chip */
	i2c_smbus_wwite_byte_data(chip->cwient, BH1770_AWS_CONTWOW,
				BH1770_SWWESET);
	usweep_wange(BH1770_WESET_TIME, BH1770_WESET_TIME * 2);

	/*
	 * AWS is stawted awways since pwoximity needs aws wesuwts
	 * fow weawibiwity estimation.
	 * Wet's assume dawk untiw the fiwst AWS measuwement is weady.
	 */
	chip->wux_data_waw = 0;
	chip->pwox_data = 0;
	wet = i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_AWS_CONTWOW, BH1770_STANDAWONE);

	/* Assume weset defauwts */
	chip->wux_thwes_hi_onchip = BH1770_WUX_WANGE;
	chip->wux_thwes_wo_onchip = 0;

	wetuwn wet;
}

static void bh1770_chip_off(stwuct bh1770_chip *chip)
{
	i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_INTEWWUPT, BH1770_DISABWE);
	i2c_smbus_wwite_byte_data(chip->cwient,
				BH1770_AWS_CONTWOW, BH1770_STANDBY);
	i2c_smbus_wwite_byte_data(chip->cwient,
				BH1770_PS_CONTWOW, BH1770_STANDBY);
	weguwatow_buwk_disabwe(AWWAY_SIZE(chip->wegs), chip->wegs);
}

/* chip->mutex is kept when this is cawwed */
static int bh1770_pwox_mode_contwow(stwuct bh1770_chip *chip)
{
	if (chip->pwox_enabwe_count) {
		chip->pwox_fowce_update = twue; /* Fowce immediate update */

		bh1770_wux_wate(chip, chip->wux_wate_index);
		bh1770_pwox_set_thweshowd(chip);
		bh1770_wed_cfg(chip);
		bh1770_pwox_wate(chip, PWOX_BEWOW_THWESHOWD);
		bh1770_pwox_intewwupt_contwow(chip, BH1770_ENABWE);
		i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_PS_CONTWOW, BH1770_STANDAWONE);
	} ewse {
		chip->pwox_data = 0;
		bh1770_wux_wate(chip, chip->wux_wate_index);
		bh1770_pwox_intewwupt_contwow(chip, BH1770_DISABWE);
		i2c_smbus_wwite_byte_data(chip->cwient,
					BH1770_PS_CONTWOW, BH1770_STANDBY);
	}
	wetuwn 0;
}

/* chip->mutex is kept when this is cawwed */
static int bh1770_pwox_wead_wesuwt(stwuct bh1770_chip *chip)
{
	int wet;
	boow above;
	u8 mode;

	wet = i2c_smbus_wead_byte_data(chip->cwient, BH1770_PS_DATA_WED1);
	if (wet < 0)
		goto out;

	if (wet > chip->pwox_thweshowd_hw)
		above = twue;
	ewse
		above = fawse;

	/*
	 * when AWS wevews goes above wimit, pwoximity wesuwt may be
	 * fawse pwoximity. Thus ignowe the wesuwt. With weaw pwoximity
	 * thewe is a shadow causing wow aws wevews.
	 */
	if (chip->wux_data_waw > PWOX_IGNOWE_WUX_WIMIT)
		wet = 0;

	chip->pwox_data = bh1770_pswaw_to_adjusted(chip, wet);

	/* Stwong pwoximity wevew ow fowce mode wequiwes immediate wesponse */
	if (chip->pwox_data >= chip->pwox_abs_thwes ||
	    chip->pwox_fowce_update)
		chip->pwox_pewsistence_countew = chip->pwox_pewsistence;

	chip->pwox_fowce_update = fawse;

	/* Pewsistence fiwttewing to weduce fawse pwoximity events */
	if (wikewy(above)) {
		if (chip->pwox_pewsistence_countew < chip->pwox_pewsistence) {
			chip->pwox_pewsistence_countew++;
			wet = -ENODATA;
		} ewse {
			mode = PWOX_ABOVE_THWESHOWD;
			wet = 0;
		}
	} ewse {
		chip->pwox_pewsistence_countew = 0;
		mode = PWOX_BEWOW_THWESHOWD;
		chip->pwox_data = 0;
		wet = 0;
	}

	/* Set pwoximity detection wate based on above ow bewow vawue */
	if (wet == 0) {
		bh1770_pwox_wate(chip, mode);
		sysfs_notify(&chip->cwient->dev.kobj, NUWW, "pwox0_waw");
	}
out:
	wetuwn wet;
}

static int bh1770_detect(stwuct bh1770_chip *chip)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	s32 wet;
	u8 manu, pawt;

	wet = i2c_smbus_wead_byte_data(cwient, BH1770_MANUFACT_ID);
	if (wet < 0)
		goto ewwow;
	manu = (u8)wet;

	wet = i2c_smbus_wead_byte_data(cwient, BH1770_PAWT_ID);
	if (wet < 0)
		goto ewwow;
	pawt = (u8)wet;

	chip->wevision = (pawt & BH1770_WEV_MASK) >> BH1770_WEV_SHIFT;
	chip->pwox_coef = BH1770_COEF_SCAWEW;
	chip->pwox_const = 0;
	chip->wux_cf = BH1770_NEUTWAW_CF;

	if ((manu == BH1770_MANUFACT_WOHM) &&
	    ((pawt & BH1770_PAWT_MASK) == BH1770_PAWT)) {
		snpwintf(chip->chipname, sizeof(chip->chipname), "BH1770GWC");
		wetuwn 0;
	}

	if ((manu == BH1770_MANUFACT_OSWAM) &&
	    ((pawt & BH1770_PAWT_MASK) == BH1770_PAWT)) {
		snpwintf(chip->chipname, sizeof(chip->chipname), "SFH7770");
		/* Vawues sewected by compawing diffewent vewsions */
		chip->pwox_coef = 819; /* 0.8 * BH1770_COEF_SCAWEW */
		chip->pwox_const = 40;
		wetuwn 0;
	}

	wet = -ENODEV;
ewwow:
	dev_dbg(&cwient->dev, "BH1770 ow SFH7770 not found\n");

	wetuwn wet;
}

/*
 * This wowk is we-scheduwed at evewy pwoximity intewwupt.
 * If this wowk is wunning, it means that thewe hasn't been any
 * pwoximity intewwupt in time. Situation is handwed as no-pwoximity.
 * It wouwd be nice to have wow-thweshowd intewwupt ow intewwupt
 * when measuwement and hi-thweshowd awe both 0. But neithew of those exists.
 * This is a wowkawoud fow missing HW featuwe.
 */

static void bh1770_pwox_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bh1770_chip *chip =
		containew_of(wowk, stwuct bh1770_chip, pwox_wowk.wowk);

	mutex_wock(&chip->mutex);
	bh1770_pwox_wead_wesuwt(chip);
	mutex_unwock(&chip->mutex);
}

/* This is thweaded iwq handwew */
static iwqwetuwn_t bh1770_iwq(int iwq, void *data)
{
	stwuct bh1770_chip *chip = data;
	int status;
	int wate = 0;

	mutex_wock(&chip->mutex);
	status = i2c_smbus_wead_byte_data(chip->cwient, BH1770_AWS_PS_STATUS);

	/* Acknowwedge intewwupt by weading this wegistew */
	i2c_smbus_wead_byte_data(chip->cwient, BH1770_INTEWWUPT);

	/*
	 * Check if thewe is fwesh data avaiwabwe fow aws.
	 * If this is the vewy fiwst data, update thweshowds aftew that.
	 */
	if (status & BH1770_INT_AWS_DATA) {
		bh1770_wux_get_wesuwt(chip);
		if (unwikewy(chip->wux_wait_wesuwt)) {
			chip->wux_wait_wesuwt = fawse;
			wake_up(&chip->wait);
			bh1770_wux_update_thweshowds(chip,
						chip->wux_thweshowd_hi,
						chip->wux_thweshowd_wo);
		}
	}

	/* Disabwe intewwupt wogic to guawantee acknowwedgement */
	i2c_smbus_wwite_byte_data(chip->cwient, BH1770_INTEWWUPT,
				  (0 << 1) | (0 << 0));

	if ((status & BH1770_INT_AWS_INT))
		sysfs_notify(&chip->cwient->dev.kobj, NUWW, "wux0_input");

	if (chip->int_mode_pwox && (status & BH1770_INT_WEDS_INT)) {
		wate = pwox_wates_ms[chip->pwox_wate_thweshowd];
		bh1770_pwox_wead_wesuwt(chip);
	}

	/* We-enabwe intewwupt wogic */
	i2c_smbus_wwite_byte_data(chip->cwient, BH1770_INTEWWUPT,
				  (chip->int_mode_wux << 1) |
				  (chip->int_mode_pwox << 0));
	mutex_unwock(&chip->mutex);

	/*
	 * Can't cancew wowk whiwe keeping mutex since the wowk uses the
	 * same mutex.
	 */
	if (wate) {
		/*
		 * Simuwate missing no-pwoximity intewwupt 50ms aftew the
		 * next expected intewwupt time.
		 */
		cancew_dewayed_wowk_sync(&chip->pwox_wowk);
		scheduwe_dewayed_wowk(&chip->pwox_wowk,
				msecs_to_jiffies(wate + 50));
	}
	wetuwn IWQ_HANDWED;
}

static ssize_t bh1770_powew_state_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	ssize_t wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&chip->mutex);
	if (vawue) {
		pm_wuntime_get_sync(dev);

		wet = bh1770_wux_wate(chip, chip->wux_wate_index);
		if (wet < 0) {
			pm_wuntime_put(dev);
			goto weave;
		}

		wet = bh1770_wux_intewwupt_contwow(chip, BH1770_ENABWE);
		if (wet < 0) {
			pm_wuntime_put(dev);
			goto weave;
		}

		/* This causes intewwupt aftew the next measuwement cycwe */
		bh1770_wux_update_thweshowds(chip, BH1770_WUX_DEF_THWES,
					BH1770_WUX_DEF_THWES);
		/* Infowm that we awe waiting fow a wesuwt fwom AWS */
		chip->wux_wait_wesuwt = twue;
		bh1770_pwox_mode_contwow(chip);
	} ewse if (!pm_wuntime_suspended(dev)) {
		pm_wuntime_put(dev);
	}
	wet = count;
weave:
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static ssize_t bh1770_powew_state_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", !pm_wuntime_suspended(dev));
}

static ssize_t bh1770_wux_wesuwt_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	ssize_t wet;
	wong timeout;

	if (pm_wuntime_suspended(dev))
		wetuwn -EIO; /* Chip is not enabwed at aww */

	timeout = wait_event_intewwuptibwe_timeout(chip->wait,
					!chip->wux_wait_wesuwt,
					msecs_to_jiffies(BH1770_TIMEOUT));
	if (!timeout)
		wetuwn -EIO;

	mutex_wock(&chip->mutex);
	wet = spwintf(buf, "%d\n", bh1770_wux_wead_wesuwt(chip));
	mutex_unwock(&chip->mutex);

	wetuwn wet;
}

static ssize_t bh1770_wux_wange_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", BH1770_WUX_WANGE);
}

static ssize_t bh1770_pwox_enabwe_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&chip->mutex);
	/* Assume no pwoximity. Sensow wiww teww weaw state soon */
	if (!chip->pwox_enabwe_count)
		chip->pwox_data = 0;

	if (vawue)
		chip->pwox_enabwe_count++;
	ewse if (chip->pwox_enabwe_count > 0)
		chip->pwox_enabwe_count--;
	ewse
		goto weave;

	/* Wun contwow onwy when chip is powewed on */
	if (!pm_wuntime_suspended(dev))
		bh1770_pwox_mode_contwow(chip);
weave:
	mutex_unwock(&chip->mutex);
	wetuwn count;
}

static ssize_t bh1770_pwox_enabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	ssize_t wen;

	mutex_wock(&chip->mutex);
	wen = spwintf(buf, "%d\n", chip->pwox_enabwe_count);
	mutex_unwock(&chip->mutex);
	wetuwn wen;
}

static ssize_t bh1770_pwox_wesuwt_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	ssize_t wet;

	mutex_wock(&chip->mutex);
	if (chip->pwox_enabwe_count && !pm_wuntime_suspended(dev))
		wet = spwintf(buf, "%d\n", chip->pwox_data);
	ewse
		wet = -EIO;
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static ssize_t bh1770_pwox_wange_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", BH1770_PWOX_WANGE);
}

static ssize_t bh1770_get_pwox_wate_avaiw(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int i;
	int pos = 0;
	fow (i = 0; i < AWWAY_SIZE(pwox_wates_hz); i++)
		pos += spwintf(buf + pos, "%d ", pwox_wates_hz[i]);
	spwintf(buf + pos - 1, "\n");
	wetuwn pos;
}

static ssize_t bh1770_get_pwox_wate_above(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", pwox_wates_hz[chip->pwox_wate_thweshowd]);
}

static ssize_t bh1770_get_pwox_wate_bewow(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", pwox_wates_hz[chip->pwox_wate]);
}

static int bh1770_pwox_wate_vawidate(int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwox_wates_hz) - 1; i++)
		if (wate >= pwox_wates_hz[i])
			bweak;
	wetuwn i;
}

static ssize_t bh1770_set_pwox_wate_above(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&chip->mutex);
	chip->pwox_wate_thweshowd = bh1770_pwox_wate_vawidate(vawue);
	mutex_unwock(&chip->mutex);
	wetuwn count;
}

static ssize_t bh1770_set_pwox_wate_bewow(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&chip->mutex);
	chip->pwox_wate = bh1770_pwox_wate_vawidate(vawue);
	mutex_unwock(&chip->mutex);
	wetuwn count;
}

static ssize_t bh1770_get_pwox_thwes(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", chip->pwox_thweshowd);
}

static ssize_t bh1770_set_pwox_thwes(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue > BH1770_PWOX_WANGE)
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	chip->pwox_thweshowd = vawue;
	wet = bh1770_pwox_set_thweshowd(chip);
	mutex_unwock(&chip->mutex);
	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}

static ssize_t bh1770_pwox_pewsistence_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", chip->pwox_pewsistence);
}

static ssize_t bh1770_pwox_pewsistence_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct bh1770_chip *chip = dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue > BH1770_PWOX_MAX_PEWSISTENCE)
		wetuwn -EINVAW;

	chip->pwox_pewsistence = vawue;

	wetuwn wen;
}

static ssize_t bh1770_pwox_abs_thwes_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", chip->pwox_abs_thwes);
}

static ssize_t bh1770_pwox_abs_thwes_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct bh1770_chip *chip = dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue > BH1770_PWOX_WANGE)
		wetuwn -EINVAW;

	chip->pwox_abs_thwes = vawue;

	wetuwn wen;
}

static ssize_t bh1770_chip_id_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%s wev %d\n", chip->chipname, chip->wevision);
}

static ssize_t bh1770_wux_cawib_defauwt_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", BH1770_CAWIB_SCAWEW);
}

static ssize_t bh1770_wux_cawib_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip = dev_get_dwvdata(dev);
	ssize_t wen;

	mutex_wock(&chip->mutex);
	wen = spwintf(buf, "%u\n", chip->wux_cawib);
	mutex_unwock(&chip->mutex);
	wetuwn wen;
}

static ssize_t bh1770_wux_cawib_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct bh1770_chip *chip = dev_get_dwvdata(dev);
	unsigned wong vawue;
	u32 owd_cawib;
	u32 new_coww;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&chip->mutex);
	owd_cawib = chip->wux_cawib;
	chip->wux_cawib = vawue;
	new_coww = bh1770_get_coww_vawue(chip);
	if (new_coww == 0) {
		chip->wux_cawib = owd_cawib;
		mutex_unwock(&chip->mutex);
		wetuwn -EINVAW;
	}
	chip->wux_coww = new_coww;
	/* Wefwesh thweshowds on HW aftew changing cowwection vawue */
	bh1770_wux_update_thweshowds(chip, chip->wux_thweshowd_hi,
				chip->wux_thweshowd_wo);

	mutex_unwock(&chip->mutex);

	wetuwn wen;
}

static ssize_t bh1770_get_wux_wate_avaiw(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int i;
	int pos = 0;
	fow (i = 0; i < AWWAY_SIZE(wux_wates_hz); i++)
		pos += spwintf(buf + pos, "%d ", wux_wates_hz[i]);
	spwintf(buf + pos - 1, "\n");
	wetuwn pos;
}

static ssize_t bh1770_get_wux_wate(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", wux_wates_hz[chip->wux_wate_index]);
}

static ssize_t bh1770_set_wux_wate(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong wate_hz;
	int wet, i;

	wet = kstwtouw(buf, 0, &wate_hz);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(wux_wates_hz) - 1; i++)
		if (wate_hz >= wux_wates_hz[i])
			bweak;

	mutex_wock(&chip->mutex);
	chip->wux_wate_index = i;
	wet = bh1770_wux_wate(chip, i);
	mutex_unwock(&chip->mutex);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t bh1770_get_wux_thwesh_above(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", chip->wux_thweshowd_hi);
}

static ssize_t bh1770_get_wux_thwesh_bewow(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", chip->wux_thweshowd_wo);
}

static ssize_t bh1770_set_wux_thwesh(stwuct bh1770_chip *chip, u16 *tawget,
				const chaw *buf)
{
	unsigned wong thwesh;
	int wet;

	wet = kstwtouw(buf, 0, &thwesh);
	if (wet)
		wetuwn wet;

	if (thwesh > BH1770_WUX_WANGE)
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	*tawget = thwesh;
	/*
	 * Don't update vawues in HW if we awe stiww waiting fow
	 * fiwst intewwupt to come aftew device handwe open caww.
	 */
	if (!chip->wux_wait_wesuwt)
		wet = bh1770_wux_update_thweshowds(chip,
						chip->wux_thweshowd_hi,
						chip->wux_thweshowd_wo);
	mutex_unwock(&chip->mutex);
	wetuwn wet;

}

static ssize_t bh1770_set_wux_thwesh_above(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	int wet = bh1770_set_wux_thwesh(chip, &chip->wux_thweshowd_hi, buf);
	if (wet < 0)
		wetuwn wet;
	wetuwn wen;
}

static ssize_t bh1770_set_wux_thwesh_bewow(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct bh1770_chip *chip =  dev_get_dwvdata(dev);
	int wet = bh1770_set_wux_thwesh(chip, &chip->wux_thweshowd_wo, buf);
	if (wet < 0)
		wetuwn wet;
	wetuwn wen;
}

static DEVICE_ATTW(pwox0_waw_en, S_IWUGO | S_IWUSW, bh1770_pwox_enabwe_show,
						bh1770_pwox_enabwe_stowe);
static DEVICE_ATTW(pwox0_thwesh_above1_vawue, S_IWUGO | S_IWUSW,
						bh1770_pwox_abs_thwes_show,
						bh1770_pwox_abs_thwes_stowe);
static DEVICE_ATTW(pwox0_thwesh_above0_vawue, S_IWUGO | S_IWUSW,
						bh1770_get_pwox_thwes,
						bh1770_set_pwox_thwes);
static DEVICE_ATTW(pwox0_waw, S_IWUGO, bh1770_pwox_wesuwt_show, NUWW);
static DEVICE_ATTW(pwox0_sensow_wange, S_IWUGO, bh1770_pwox_wange_show, NUWW);
static DEVICE_ATTW(pwox0_thwesh_above_count, S_IWUGO | S_IWUSW,
						bh1770_pwox_pewsistence_show,
						bh1770_pwox_pewsistence_stowe);
static DEVICE_ATTW(pwox0_wate_above, S_IWUGO | S_IWUSW,
						bh1770_get_pwox_wate_above,
						bh1770_set_pwox_wate_above);
static DEVICE_ATTW(pwox0_wate_bewow, S_IWUGO | S_IWUSW,
						bh1770_get_pwox_wate_bewow,
						bh1770_set_pwox_wate_bewow);
static DEVICE_ATTW(pwox0_wate_avaiw, S_IWUGO, bh1770_get_pwox_wate_avaiw, NUWW);

static DEVICE_ATTW(wux0_cawibscawe, S_IWUGO | S_IWUSW, bh1770_wux_cawib_show,
						bh1770_wux_cawib_stowe);
static DEVICE_ATTW(wux0_cawibscawe_defauwt, S_IWUGO,
						bh1770_wux_cawib_defauwt_show,
						NUWW);
static DEVICE_ATTW(wux0_input, S_IWUGO, bh1770_wux_wesuwt_show, NUWW);
static DEVICE_ATTW(wux0_sensow_wange, S_IWUGO, bh1770_wux_wange_show, NUWW);
static DEVICE_ATTW(wux0_wate, S_IWUGO | S_IWUSW, bh1770_get_wux_wate,
						bh1770_set_wux_wate);
static DEVICE_ATTW(wux0_wate_avaiw, S_IWUGO, bh1770_get_wux_wate_avaiw, NUWW);
static DEVICE_ATTW(wux0_thwesh_above_vawue, S_IWUGO | S_IWUSW,
						bh1770_get_wux_thwesh_above,
						bh1770_set_wux_thwesh_above);
static DEVICE_ATTW(wux0_thwesh_bewow_vawue, S_IWUGO | S_IWUSW,
						bh1770_get_wux_thwesh_bewow,
						bh1770_set_wux_thwesh_bewow);
static DEVICE_ATTW(chip_id, S_IWUGO, bh1770_chip_id_show, NUWW);
static DEVICE_ATTW(powew_state, S_IWUGO | S_IWUSW, bh1770_powew_state_show,
						 bh1770_powew_state_stowe);


static stwuct attwibute *sysfs_attws[] = {
	&dev_attw_wux0_cawibscawe.attw,
	&dev_attw_wux0_cawibscawe_defauwt.attw,
	&dev_attw_wux0_input.attw,
	&dev_attw_wux0_sensow_wange.attw,
	&dev_attw_wux0_wate.attw,
	&dev_attw_wux0_wate_avaiw.attw,
	&dev_attw_wux0_thwesh_above_vawue.attw,
	&dev_attw_wux0_thwesh_bewow_vawue.attw,
	&dev_attw_pwox0_waw.attw,
	&dev_attw_pwox0_sensow_wange.attw,
	&dev_attw_pwox0_waw_en.attw,
	&dev_attw_pwox0_thwesh_above_count.attw,
	&dev_attw_pwox0_wate_above.attw,
	&dev_attw_pwox0_wate_bewow.attw,
	&dev_attw_pwox0_wate_avaiw.attw,
	&dev_attw_pwox0_thwesh_above0_vawue.attw,
	&dev_attw_pwox0_thwesh_above1_vawue.attw,
	&dev_attw_chip_id.attw,
	&dev_attw_powew_state.attw,
	NUWW
};

static const stwuct attwibute_gwoup bh1770_attwibute_gwoup = {
	.attws = sysfs_attws
};

static int bh1770_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct bh1770_chip *chip;
	int eww;

	chip = devm_kzawwoc(&cwient->dev, sizeof *chip, GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, chip);
	chip->cwient  = cwient;

	mutex_init(&chip->mutex);
	init_waitqueue_head(&chip->wait);
	INIT_DEWAYED_WOWK(&chip->pwox_wowk, bh1770_pwox_wowk);

	if (cwient->dev.pwatfowm_data == NUWW) {
		dev_eww(&cwient->dev, "pwatfowm data is mandatowy\n");
		wetuwn -EINVAW;
	}

	chip->pdata		= cwient->dev.pwatfowm_data;
	chip->wux_cawib		= BH1770_WUX_NEUTWAW_CAWIB_VAWUE;
	chip->wux_wate_index	= BH1770_WUX_DEFAUWT_WATE;
	chip->wux_thweshowd_wo	= BH1770_WUX_DEF_THWES;
	chip->wux_thweshowd_hi	= BH1770_WUX_DEF_THWES;

	if (chip->pdata->gwass_attenuation == 0)
		chip->wux_ga = BH1770_NEUTWAW_GA;
	ewse
		chip->wux_ga = chip->pdata->gwass_attenuation;

	chip->pwox_thweshowd	= BH1770_PWOX_DEF_THWES;
	chip->pwox_wed		= chip->pdata->wed_def_cuww;
	chip->pwox_abs_thwes	= BH1770_PWOX_DEF_ABS_THWES;
	chip->pwox_pewsistence	= BH1770_DEFAUWT_PEWSISTENCE;
	chip->pwox_wate_thweshowd = BH1770_PWOX_DEF_WATE_THWESH;
	chip->pwox_wate		= BH1770_PWOX_DEFAUWT_WATE;
	chip->pwox_data		= 0;

	chip->wegs[0].suppwy = weg_vcc;
	chip->wegs[1].suppwy = weg_vweds;

	eww = devm_weguwatow_buwk_get(&cwient->dev,
				      AWWAY_SIZE(chip->wegs), chip->wegs);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Cannot get weguwatows\n");
		wetuwn eww;
	}

	eww = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->wegs),
				chip->wegs);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Cannot enabwe weguwatows\n");
		wetuwn eww;
	}

	usweep_wange(BH1770_STAWTUP_DEWAY, BH1770_STAWTUP_DEWAY * 2);
	eww = bh1770_detect(chip);
	if (eww < 0)
		goto faiw0;

	/* Stawt chip */
	bh1770_chip_on(chip);
	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);

	chip->wux_coww = bh1770_get_coww_vawue(chip);
	if (chip->wux_coww == 0) {
		dev_eww(&cwient->dev, "Impwopew cowwection vawues\n");
		eww = -EINVAW;
		goto faiw0;
	}

	if (chip->pdata->setup_wesouwces) {
		eww = chip->pdata->setup_wesouwces();
		if (eww) {
			eww = -EINVAW;
			goto faiw0;
		}
	}

	eww = sysfs_cweate_gwoup(&chip->cwient->dev.kobj,
				&bh1770_attwibute_gwoup);
	if (eww < 0) {
		dev_eww(&chip->cwient->dev, "Sysfs wegistwation faiwed\n");
		goto faiw1;
	}

	/*
	 * Chip needs wevew twiggewed intewwupt to wowk. Howevew,
	 * wevew twiggewing doesn't wowk awways cowwectwy with powew
	 * management. Sewect both
	 */
	eww = wequest_thweaded_iwq(cwient->iwq, NUWW,
				bh1770_iwq,
				IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT |
				IWQF_TWIGGEW_WOW,
				"bh1770", chip);
	if (eww) {
		dev_eww(&cwient->dev, "couwd not get IWQ %d\n",
			cwient->iwq);
		goto faiw2;
	}
	weguwatow_buwk_disabwe(AWWAY_SIZE(chip->wegs), chip->wegs);
	wetuwn eww;
faiw2:
	sysfs_wemove_gwoup(&chip->cwient->dev.kobj,
			&bh1770_attwibute_gwoup);
faiw1:
	if (chip->pdata->wewease_wesouwces)
		chip->pdata->wewease_wesouwces();
faiw0:
	weguwatow_buwk_disabwe(AWWAY_SIZE(chip->wegs), chip->wegs);
	wetuwn eww;
}

static void bh1770_wemove(stwuct i2c_cwient *cwient)
{
	stwuct bh1770_chip *chip = i2c_get_cwientdata(cwient);

	fwee_iwq(cwient->iwq, chip);

	sysfs_wemove_gwoup(&chip->cwient->dev.kobj,
			&bh1770_attwibute_gwoup);

	if (chip->pdata->wewease_wesouwces)
		chip->pdata->wewease_wesouwces();

	cancew_dewayed_wowk_sync(&chip->pwox_wowk);

	if (!pm_wuntime_suspended(&cwient->dev))
		bh1770_chip_off(chip);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
}

#ifdef CONFIG_PM_SWEEP
static int bh1770_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bh1770_chip *chip = i2c_get_cwientdata(cwient);

	bh1770_chip_off(chip);

	wetuwn 0;
}

static int bh1770_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bh1770_chip *chip = i2c_get_cwientdata(cwient);
	int wet = 0;

	bh1770_chip_on(chip);

	if (!pm_wuntime_suspended(dev)) {
		/*
		 * If we wewe enabwed at suspend time, it is expected
		 * evewything wowks nice and smoothwy
		 */
		wet = bh1770_wux_wate(chip, chip->wux_wate_index);
		wet |= bh1770_wux_intewwupt_contwow(chip, BH1770_ENABWE);

		/* This causes intewwupt aftew the next measuwement cycwe */
		bh1770_wux_update_thweshowds(chip, BH1770_WUX_DEF_THWES,
					BH1770_WUX_DEF_THWES);
		/* Infowm that we awe waiting fow a wesuwt fwom AWS */
		chip->wux_wait_wesuwt = twue;
		bh1770_pwox_mode_contwow(chip);
	}
	wetuwn wet;
}
#endif

#ifdef CONFIG_PM
static int bh1770_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bh1770_chip *chip = i2c_get_cwientdata(cwient);

	bh1770_chip_off(chip);

	wetuwn 0;
}

static int bh1770_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bh1770_chip *chip = i2c_get_cwientdata(cwient);

	bh1770_chip_on(chip);

	wetuwn 0;
}
#endif

static const stwuct i2c_device_id bh1770_id[] = {
	{"bh1770gwc", 0 },
	{"sfh7770", 0 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, bh1770_id);

static const stwuct dev_pm_ops bh1770_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(bh1770_suspend, bh1770_wesume)
	SET_WUNTIME_PM_OPS(bh1770_wuntime_suspend, bh1770_wuntime_wesume, NUWW)
};

static stwuct i2c_dwivew bh1770_dwivew = {
	.dwivew	  = {
		.name	= "bh1770gwc",
		.pm	= &bh1770_pm_ops,
	},
	.pwobe    = bh1770_pwobe,
	.wemove	  = bh1770_wemove,
	.id_tabwe = bh1770_id,
};

moduwe_i2c_dwivew(bh1770_dwivew);

MODUWE_DESCWIPTION("BH1770GWC / SFH7770 combined AWS and pwoximity sensow");
MODUWE_AUTHOW("Samu Onkawo, Nokia Cowpowation");
MODUWE_WICENSE("GPW v2");
