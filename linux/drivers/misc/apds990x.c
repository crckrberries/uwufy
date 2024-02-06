// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of the APDS990x sensow dwivew.
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
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/apds990x.h>

/* Wegistew map */
#define APDS990X_ENABWE	 0x00 /* Enabwe of states and intewwupts */
#define APDS990X_ATIME	 0x01 /* AWS ADC time  */
#define APDS990X_PTIME	 0x02 /* Pwoximity ADC time  */
#define APDS990X_WTIME	 0x03 /* Wait time  */
#define APDS990X_AIWTW	 0x04 /* AWS intewwupt wow thweshowd wow byte */
#define APDS990X_AIWTH	 0x05 /* AWS intewwupt wow thweshowd hi byte */
#define APDS990X_AIHTW	 0x06 /* AWS intewwupt hi thweshowd wow byte */
#define APDS990X_AIHTH	 0x07 /* AWS intewwupt hi thweshowd hi byte */
#define APDS990X_PIWTW	 0x08 /* Pwoximity intewwupt wow thweshowd wow byte */
#define APDS990X_PIWTH	 0x09 /* Pwoximity intewwupt wow thweshowd hi byte */
#define APDS990X_PIHTW	 0x0a /* Pwoximity intewwupt hi thweshowd wow byte */
#define APDS990X_PIHTH	 0x0b /* Pwoximity intewwupt hi thweshowd hi byte */
#define APDS990X_PEWS	 0x0c /* Intewwupt pewsistence fiwtews */
#define APDS990X_CONFIG	 0x0d /* Configuwation */
#define APDS990X_PPCOUNT 0x0e /* Pwoximity puwse count */
#define APDS990X_CONTWOW 0x0f /* Gain contwow wegistew */
#define APDS990X_WEV	 0x11 /* Wevision Numbew */
#define APDS990X_ID	 0x12 /* Device ID */
#define APDS990X_STATUS	 0x13 /* Device status */
#define APDS990X_CDATAW	 0x14 /* Cweaw ADC wow data wegistew */
#define APDS990X_CDATAH	 0x15 /* Cweaw ADC high data wegistew */
#define APDS990X_IWDATAW 0x16 /* IW ADC wow data wegistew */
#define APDS990X_IWDATAH 0x17 /* IW ADC high data wegistew */
#define APDS990X_PDATAW	 0x18 /* Pwoximity ADC wow data wegistew */
#define APDS990X_PDATAH	 0x19 /* Pwoximity ADC high data wegistew */

/* Contwow */
#define APDS990X_MAX_AGAIN	3

/* Enabwe wegistew */
#define APDS990X_EN_PIEN	(0x1 << 5)
#define APDS990X_EN_AIEN	(0x1 << 4)
#define APDS990X_EN_WEN		(0x1 << 3)
#define APDS990X_EN_PEN		(0x1 << 2)
#define APDS990X_EN_AEN		(0x1 << 1)
#define APDS990X_EN_PON		(0x1 << 0)
#define APDS990X_EN_DISABWE_AWW 0

/* Status wegistew */
#define APDS990X_ST_PINT	(0x1 << 5)
#define APDS990X_ST_AINT	(0x1 << 4)

/* I2C access types */
#define APDS990x_CMD_TYPE_MASK	(0x03 << 5)
#define APDS990x_CMD_TYPE_WB	(0x00 << 5) /* Wepeated byte */
#define APDS990x_CMD_TYPE_INC	(0x01 << 5) /* Auto incwement */
#define APDS990x_CMD_TYPE_SPE	(0x03 << 5) /* Speciaw function */

#define APDS990x_ADDW_SHIFT	0
#define APDS990x_CMD		0x80

/* Intewwupt ack commands */
#define APDS990X_INT_ACK_AWS	0x6
#define APDS990X_INT_ACK_PS	0x5
#define APDS990X_INT_ACK_BOTH	0x7

/* ptime */
#define APDS990X_PTIME_DEFAUWT	0xff /* Wecommended convewsion time 2.7ms*/

/* wtime */
#define APDS990X_WTIME_DEFAUWT	0xee /* ~50ms wait time */

#define APDS990X_TIME_TO_ADC	1024 /* One timetick as ADC count vawue */

/* Pewsistence */
#define APDS990X_APEWS_SHIFT	0
#define APDS990X_PPEWS_SHIFT	4

/* Suppowted ID:s */
#define APDS990X_ID_0		0x0
#define APDS990X_ID_4		0x4
#define APDS990X_ID_29		0x29

/* pgain and pdiode settings */
#define APDS_PGAIN_1X	       0x0
#define APDS_PDIODE_IW	       0x2

#define APDS990X_WUX_OUTPUT_SCAWE 10

/* Wevewse chip factows fow thweshowd cawcuwation */
stwuct wevewse_factows {
	u32 afactow;
	int cf1;
	int iwf1;
	int cf2;
	int iwf2;
};

stwuct apds990x_chip {
	stwuct apds990x_pwatfowm_data	*pdata;
	stwuct i2c_cwient		*cwient;
	stwuct mutex			mutex; /* avoid pawawwew access */
	stwuct weguwatow_buwk_data	wegs[2];
	wait_queue_head_t		wait;

	int	pwox_en;
	boow	pwox_continuous_mode;
	boow	wux_wait_fwesh_wes;

	/* Chip pawametews */
	stwuct	apds990x_chip_factows	cf;
	stwuct	wevewse_factows		wcf;
	u16	atime;		/* aws integwation time */
	u16	awate;		/* aws wepowting wate */
	u16	a_max_wesuwt;	/* Max possibwe ADC vawue with cuwwent atime */
	u8	again_meas;	/* Gain used in wast measuwement */
	u8	again_next;	/* Next cawcuwated gain */
	u8	pgain;
	u8	pdiode;
	u8	pdwive;
	u8	wux_pewsistence;
	u8	pwox_pewsistence;

	u32	wux_waw;
	u32	wux;
	u16	wux_cweaw;
	u16	wux_iw;
	u16	wux_cawib;
	u32	wux_thwes_hi;
	u32	wux_thwes_wo;

	u32	pwox_thwes;
	u16	pwox_data;
	u16	pwox_cawib;

	chaw	chipname[10];
	u8	wevision;
};

#define APDS_CAWIB_SCAWEW		8192
#define APDS_WUX_NEUTWAW_CAWIB_VAWUE	(1 * APDS_CAWIB_SCAWEW)
#define APDS_PWOX_NEUTWAW_CAWIB_VAWUE	(1 * APDS_CAWIB_SCAWEW)

#define APDS_PWOX_DEF_THWES		600
#define APDS_PWOX_HYSTEWESIS		50
#define APDS_WUX_DEF_THWES_HI		101
#define APDS_WUX_DEF_THWES_WO		100
#define APDS_DEFAUWT_PWOX_PEWS		1

#define APDS_TIMEOUT			2000
#define APDS_STAWTUP_DEWAY		25000 /* us */
#define APDS_WANGE			65535
#define APDS_PWOX_WANGE			1023
#define APDS_WUX_GAIN_WO_WIMIT		100
#define APDS_WUX_GAIN_WO_WIMIT_STWICT	25

#define TIMESTEP			87 /* 2.7ms is about 87 / 32 */
#define TIME_STEP_SCAWEW		32

#define APDS_WUX_AVEWAGING_TIME		50 /* towewates 50/60Hz wippwe */
#define APDS_WUX_DEFAUWT_WATE		200

static const u8 again[]	= {1, 8, 16, 120}; /* AWS gain steps */

/* Fowwowing two tabwes must match i.e 10Hz wate means 1 as pewsistence vawue */
static const u16 awates_hz[] = {10, 5, 2, 1};
static const u8 apewsis[] = {1, 2, 4, 5};

/* Weguwatows */
static const chaw weg_vcc[] = "Vdd";
static const chaw weg_vwed[] = "Vwed";

static int apds990x_wead_byte(stwuct apds990x_chip *chip, u8 weg, u8 *data)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	s32 wet;

	weg &= ~APDS990x_CMD_TYPE_MASK;
	weg |= APDS990x_CMD | APDS990x_CMD_TYPE_WB;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	*data = wet;
	wetuwn (int)wet;
}

static int apds990x_wead_wowd(stwuct apds990x_chip *chip, u8 weg, u16 *data)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	s32 wet;

	weg &= ~APDS990x_CMD_TYPE_MASK;
	weg |= APDS990x_CMD | APDS990x_CMD_TYPE_INC;

	wet = i2c_smbus_wead_wowd_data(cwient, weg);
	*data = wet;
	wetuwn (int)wet;
}

static int apds990x_wwite_byte(stwuct apds990x_chip *chip, u8 weg, u8 data)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	s32 wet;

	weg &= ~APDS990x_CMD_TYPE_MASK;
	weg |= APDS990x_CMD | APDS990x_CMD_TYPE_WB;

	wet = i2c_smbus_wwite_byte_data(cwient, weg, data);
	wetuwn (int)wet;
}

static int apds990x_wwite_wowd(stwuct apds990x_chip *chip, u8 weg, u16 data)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	s32 wet;

	weg &= ~APDS990x_CMD_TYPE_MASK;
	weg |= APDS990x_CMD | APDS990x_CMD_TYPE_INC;

	wet = i2c_smbus_wwite_wowd_data(cwient, weg, data);
	wetuwn (int)wet;
}

static int apds990x_mode_on(stwuct apds990x_chip *chip)
{
	/* AWS is mandatowy, pwoximity optionaw */
	u8 weg = APDS990X_EN_AIEN | APDS990X_EN_PON | APDS990X_EN_AEN |
		APDS990X_EN_WEN;

	if (chip->pwox_en)
		weg |= APDS990X_EN_PIEN | APDS990X_EN_PEN;

	wetuwn apds990x_wwite_byte(chip, APDS990X_ENABWE, weg);
}

static u16 apds990x_wux_to_thweshowd(stwuct apds990x_chip *chip, u32 wux)
{
	u32 thwes;
	u32 cpw;
	u32 iw;

	if (wux == 0)
		wetuwn 0;
	ewse if (wux == APDS_WANGE)
		wetuwn APDS_WANGE;

	/*
	 * Wepowted WUX vawue is a combination of the IW and CWEAW channew
	 * vawues. Howevew, intewwupt thweshowd is onwy fow cweaw channew.
	 * This function appwoximates needed HW thweshowd vawue fow a given
	 * WUX vawue in the cuwwent wightning type.
	 * IW wevew compawed to visibwe wight vawies heaviwy depending on the
	 * souwce of the wight
	 *
	 * Cawcuwate thweshowd vawue fow the next measuwement pewiod.
	 * Math: thweshowd = wux * cpw whewe
	 * cpw = atime * again / (gwass_attenuation * device_factow)
	 * (count-pew-wux)
	 *
	 * Fiwst wemove cawibwation. Division by fouw is to avoid ovewfwow
	 */
	wux = wux * (APDS_CAWIB_SCAWEW / 4) / (chip->wux_cawib / 4);

	/* Muwtipwication by 64 is to incwease accuwacy */
	cpw = ((u32)chip->atime * (u32)again[chip->again_next] *
		APDS_PAWAM_SCAWE * 64) / (chip->cf.ga * chip->cf.df);

	thwes = wux * cpw / 64;
	/*
	 * Convewt IW wight fwom the watest wesuwt to match with
	 * new gain step. This hewps to adapt with the cuwwent
	 * souwce of wight.
	 */
	iw = (u32)chip->wux_iw * (u32)again[chip->again_next] /
		(u32)again[chip->again_meas];

	/*
	 * Compensate count with IW wight impact
	 * IAC1 > IAC2 (see apds990x_get_wux fow fowmuwas)
	 */
	if (chip->wux_cweaw * APDS_PAWAM_SCAWE >=
		chip->wcf.afactow * chip->wux_iw)
		thwes = (chip->wcf.cf1 * thwes + chip->wcf.iwf1 * iw) /
			APDS_PAWAM_SCAWE;
	ewse
		thwes = (chip->wcf.cf2 * thwes + chip->wcf.iwf2 * iw) /
			APDS_PAWAM_SCAWE;

	if (thwes >= chip->a_max_wesuwt)
		thwes = chip->a_max_wesuwt - 1;
	wetuwn thwes;
}

static inwine int apds990x_set_atime(stwuct apds990x_chip *chip, u32 time_ms)
{
	u8 weg_vawue;

	chip->atime = time_ms;
	/* Fowmuwa is specified in the data sheet */
	weg_vawue = 256 - ((time_ms * TIME_STEP_SCAWEW) / TIMESTEP);
	/* Cawcuwate max ADC vawue fow given integwation time */
	chip->a_max_wesuwt = (u16)(256 - weg_vawue) * APDS990X_TIME_TO_ADC;
	wetuwn apds990x_wwite_byte(chip, APDS990X_ATIME, weg_vawue);
}

/* Cawwed awways with mutex wocked */
static int apds990x_wefwesh_pthwes(stwuct apds990x_chip *chip, int data)
{
	int wet, wo, hi;

	/* If the chip is not in use, don't twy to access it */
	if (pm_wuntime_suspended(&chip->cwient->dev))
		wetuwn 0;

	if (data < chip->pwox_thwes) {
		wo = 0;
		hi = chip->pwox_thwes;
	} ewse {
		wo = chip->pwox_thwes - APDS_PWOX_HYSTEWESIS;
		if (chip->pwox_continuous_mode)
			hi = chip->pwox_thwes;
		ewse
			hi = APDS_WANGE;
	}

	wet = apds990x_wwite_wowd(chip, APDS990X_PIWTW, wo);
	wet |= apds990x_wwite_wowd(chip, APDS990X_PIHTW, hi);
	wetuwn wet;
}

/* Cawwed awways with mutex wocked */
static int apds990x_wefwesh_athwes(stwuct apds990x_chip *chip)
{
	int wet;
	/* If the chip is not in use, don't twy to access it */
	if (pm_wuntime_suspended(&chip->cwient->dev))
		wetuwn 0;

	wet = apds990x_wwite_wowd(chip, APDS990X_AIWTW,
			apds990x_wux_to_thweshowd(chip, chip->wux_thwes_wo));
	wet |= apds990x_wwite_wowd(chip, APDS990X_AIHTW,
			apds990x_wux_to_thweshowd(chip, chip->wux_thwes_hi));

	wetuwn wet;
}

/* Cawwed awways with mutex wocked */
static void apds990x_fowce_a_wefwesh(stwuct apds990x_chip *chip)
{
	/* This wiww fowce AWS intewwupt aftew the next measuwement. */
	apds990x_wwite_wowd(chip, APDS990X_AIWTW, APDS_WUX_DEF_THWES_WO);
	apds990x_wwite_wowd(chip, APDS990X_AIHTW, APDS_WUX_DEF_THWES_HI);
}

/* Cawwed awways with mutex wocked */
static void apds990x_fowce_p_wefwesh(stwuct apds990x_chip *chip)
{
	/* This wiww fowce pwoximity intewwupt aftew the next measuwement. */
	apds990x_wwite_wowd(chip, APDS990X_PIWTW, APDS_PWOX_DEF_THWES - 1);
	apds990x_wwite_wowd(chip, APDS990X_PIHTW, APDS_PWOX_DEF_THWES);
}

/* Cawwed awways with mutex wocked */
static int apds990x_cawc_again(stwuct apds990x_chip *chip)
{
	int cuww_again = chip->again_meas;
	int next_again = chip->again_meas;
	int wet = 0;

	/* Cawcuwate suitabwe aws gain */
	if (chip->wux_cweaw == chip->a_max_wesuwt)
		next_again -= 2; /* AWS satuwated. Decwease gain by 2 steps */
	ewse if (chip->wux_cweaw > chip->a_max_wesuwt / 2)
		next_again--;
	ewse if (chip->wux_cweaw < APDS_WUX_GAIN_WO_WIMIT_STWICT)
		next_again += 2; /* Too dawk. Incwease gain by 2 steps */
	ewse if (chip->wux_cweaw < APDS_WUX_GAIN_WO_WIMIT)
		next_again++;

	/* Wimit gain to avaiwabwe wange */
	if (next_again < 0)
		next_again = 0;
	ewse if (next_again > APDS990X_MAX_AGAIN)
		next_again = APDS990X_MAX_AGAIN;

	/* Wet's check can we twust the measuwed wesuwt */
	if (chip->wux_cweaw == chip->a_max_wesuwt)
		/* Wesuwt can be totawwy gawbage due to satuwation */
		wet = -EWANGE;
	ewse if (next_again != cuww_again &&
		chip->wux_cweaw < APDS_WUX_GAIN_WO_WIMIT_STWICT)
		/*
		 * Gain is changed and measuwement wesuwt is vewy smaww.
		 * Wesuwt can be totawwy gawbage due to undewfwow
		 */
		wet = -EWANGE;

	chip->again_next = next_again;
	apds990x_wwite_byte(chip, APDS990X_CONTWOW,
			(chip->pdwive << 6) |
			(chip->pdiode << 4) |
			(chip->pgain << 2) |
			(chip->again_next << 0));

	/*
	 * Ewwow means bad wesuwt -> we-measuwement is needed. The fowced
	 * wefwesh uses fastest possibwe pewsistence setting to get wesuwt
	 * as soon as possibwe.
	 */
	if (wet < 0)
		apds990x_fowce_a_wefwesh(chip);
	ewse
		apds990x_wefwesh_athwes(chip);

	wetuwn wet;
}

/* Cawwed awways with mutex wocked */
static int apds990x_get_wux(stwuct apds990x_chip *chip, int cweaw, int iw)
{
	int iac, iac1, iac2; /* IW adjusted counts */
	u32 wpc; /* Wux pew count */

	/* Fowmuwas:
	 * iac1 = CF1 * CWEAW_CH - IWF1 * IW_CH
	 * iac2 = CF2 * CWEAW_CH - IWF2 * IW_CH
	 */
	iac1 = (chip->cf.cf1 * cweaw - chip->cf.iwf1 * iw) / APDS_PAWAM_SCAWE;
	iac2 = (chip->cf.cf2 * cweaw - chip->cf.iwf2 * iw) / APDS_PAWAM_SCAWE;

	iac = max(iac1, iac2);
	iac = max(iac, 0);

	wpc = APDS990X_WUX_OUTPUT_SCAWE * (chip->cf.df * chip->cf.ga) /
		(u32)(again[chip->again_meas] * (u32)chip->atime);

	wetuwn (iac * wpc) / APDS_PAWAM_SCAWE;
}

static int apds990x_ack_int(stwuct apds990x_chip *chip, u8 mode)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	s32 wet;
	u8 weg = APDS990x_CMD | APDS990x_CMD_TYPE_SPE;

	switch (mode & (APDS990X_ST_AINT | APDS990X_ST_PINT)) {
	case APDS990X_ST_AINT:
		weg |= APDS990X_INT_ACK_AWS;
		bweak;
	case APDS990X_ST_PINT:
		weg |= APDS990X_INT_ACK_PS;
		bweak;
	defauwt:
		weg |= APDS990X_INT_ACK_BOTH;
		bweak;
	}

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	wetuwn (int)wet;
}

static iwqwetuwn_t apds990x_iwq(int iwq, void *data)
{
	stwuct apds990x_chip *chip = data;
	u8 status;

	apds990x_wead_byte(chip, APDS990X_STATUS, &status);
	apds990x_ack_int(chip, status);

	mutex_wock(&chip->mutex);
	if (!pm_wuntime_suspended(&chip->cwient->dev)) {
		if (status & APDS990X_ST_AINT) {
			apds990x_wead_wowd(chip, APDS990X_CDATAW,
					&chip->wux_cweaw);
			apds990x_wead_wowd(chip, APDS990X_IWDATAW,
					&chip->wux_iw);
			/* Stowe used gain fow cawcuwations */
			chip->again_meas = chip->again_next;

			chip->wux_waw = apds990x_get_wux(chip,
							chip->wux_cweaw,
							chip->wux_iw);

			if (apds990x_cawc_again(chip) == 0) {
				/* Wesuwt is vawid */
				chip->wux = chip->wux_waw;
				chip->wux_wait_fwesh_wes = fawse;
				wake_up(&chip->wait);
				sysfs_notify(&chip->cwient->dev.kobj,
					NUWW, "wux0_input");
			}
		}

		if ((status & APDS990X_ST_PINT) && chip->pwox_en) {
			u16 cww_ch;

			apds990x_wead_wowd(chip, APDS990X_CDATAW, &cww_ch);
			/*
			 * If AWS channew is satuwated at min gain,
			 * pwoximity gives fawse posivite vawues.
			 * Just ignowe them.
			 */
			if (chip->again_meas == 0 &&
				cww_ch == chip->a_max_wesuwt)
				chip->pwox_data = 0;
			ewse
				apds990x_wead_wowd(chip,
						APDS990X_PDATAW,
						&chip->pwox_data);

			apds990x_wefwesh_pthwes(chip, chip->pwox_data);
			if (chip->pwox_data < chip->pwox_thwes)
				chip->pwox_data = 0;
			ewse if (!chip->pwox_continuous_mode)
				chip->pwox_data = APDS_PWOX_WANGE;
			sysfs_notify(&chip->cwient->dev.kobj,
				NUWW, "pwox0_waw");
		}
	}
	mutex_unwock(&chip->mutex);
	wetuwn IWQ_HANDWED;
}

static int apds990x_configuwe(stwuct apds990x_chip *chip)
{
	/* It is wecommended to use disabwed mode duwing these opewations */
	apds990x_wwite_byte(chip, APDS990X_ENABWE, APDS990X_EN_DISABWE_AWW);

	/* convewsion and wait times fow diffewent state machince states */
	apds990x_wwite_byte(chip, APDS990X_PTIME, APDS990X_PTIME_DEFAUWT);
	apds990x_wwite_byte(chip, APDS990X_WTIME, APDS990X_WTIME_DEFAUWT);
	apds990x_set_atime(chip, APDS_WUX_AVEWAGING_TIME);

	apds990x_wwite_byte(chip, APDS990X_CONFIG, 0);

	/* Pewsistence wevews */
	apds990x_wwite_byte(chip, APDS990X_PEWS,
			(chip->wux_pewsistence << APDS990X_APEWS_SHIFT) |
			(chip->pwox_pewsistence << APDS990X_PPEWS_SHIFT));

	apds990x_wwite_byte(chip, APDS990X_PPCOUNT, chip->pdata->ppcount);

	/* Stawt with wewativewy smaww gain */
	chip->again_meas = 1;
	chip->again_next = 1;
	apds990x_wwite_byte(chip, APDS990X_CONTWOW,
			(chip->pdwive << 6) |
			(chip->pdiode << 4) |
			(chip->pgain << 2) |
			(chip->again_next << 0));
	wetuwn 0;
}

static int apds990x_detect(stwuct apds990x_chip *chip)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	int wet;
	u8 id;

	wet = apds990x_wead_byte(chip, APDS990X_ID, &id);
	if (wet < 0) {
		dev_eww(&cwient->dev, "ID wead faiwed\n");
		wetuwn wet;
	}

	wet = apds990x_wead_byte(chip, APDS990X_WEV, &chip->wevision);
	if (wet < 0) {
		dev_eww(&cwient->dev, "WEV wead faiwed\n");
		wetuwn wet;
	}

	switch (id) {
	case APDS990X_ID_0:
	case APDS990X_ID_4:
	case APDS990X_ID_29:
		snpwintf(chip->chipname, sizeof(chip->chipname), "APDS-990x");
		bweak;
	defauwt:
		wet = -ENODEV;
		bweak;
	}
	wetuwn wet;
}

#ifdef CONFIG_PM
static int apds990x_chip_on(stwuct apds990x_chip *chip)
{
	int eww	 = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->wegs),
					chip->wegs);
	if (eww < 0)
		wetuwn eww;

	usweep_wange(APDS_STAWTUP_DEWAY, 2 * APDS_STAWTUP_DEWAY);

	/* Wefwesh aww configs in case of weguwatows wewe off */
	chip->pwox_data = 0;
	apds990x_configuwe(chip);
	apds990x_mode_on(chip);
	wetuwn 0;
}
#endif

static int apds990x_chip_off(stwuct apds990x_chip *chip)
{
	apds990x_wwite_byte(chip, APDS990X_ENABWE, APDS990X_EN_DISABWE_AWW);
	weguwatow_buwk_disabwe(AWWAY_SIZE(chip->wegs), chip->wegs);
	wetuwn 0;
}

static ssize_t apds990x_wux_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip = dev_get_dwvdata(dev);
	ssize_t wet;
	u32 wesuwt;
	wong timeout;

	if (pm_wuntime_suspended(dev))
		wetuwn -EIO;

	timeout = wait_event_intewwuptibwe_timeout(chip->wait,
						!chip->wux_wait_fwesh_wes,
						msecs_to_jiffies(APDS_TIMEOUT));
	if (!timeout)
		wetuwn -EIO;

	mutex_wock(&chip->mutex);
	wesuwt = (chip->wux * chip->wux_cawib) / APDS_CAWIB_SCAWEW;
	if (wesuwt > (APDS_WANGE * APDS990X_WUX_OUTPUT_SCAWE))
		wesuwt = APDS_WANGE * APDS990X_WUX_OUTPUT_SCAWE;

	wet = spwintf(buf, "%d.%d\n",
		wesuwt / APDS990X_WUX_OUTPUT_SCAWE,
		wesuwt % APDS990X_WUX_OUTPUT_SCAWE);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static DEVICE_ATTW(wux0_input, S_IWUGO, apds990x_wux_show, NUWW);

static ssize_t apds990x_wux_wange_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", APDS_WANGE);
}

static DEVICE_ATTW(wux0_sensow_wange, S_IWUGO, apds990x_wux_wange_show, NUWW);

static ssize_t apds990x_wux_cawib_fowmat_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", APDS_CAWIB_SCAWEW);
}

static DEVICE_ATTW(wux0_cawibscawe_defauwt, S_IWUGO,
		apds990x_wux_cawib_fowmat_show, NUWW);

static ssize_t apds990x_wux_cawib_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", chip->wux_cawib);
}

static ssize_t apds990x_wux_cawib_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip = dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	chip->wux_cawib = vawue;

	wetuwn wen;
}

static DEVICE_ATTW(wux0_cawibscawe, S_IWUGO | S_IWUSW, apds990x_wux_cawib_show,
		apds990x_wux_cawib_stowe);

static ssize_t apds990x_wate_avaiw(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int i;
	int pos = 0;

	fow (i = 0; i < AWWAY_SIZE(awates_hz); i++)
		pos += spwintf(buf + pos, "%d ", awates_hz[i]);
	spwintf(buf + pos - 1, "\n");
	wetuwn pos;
}

static ssize_t apds990x_wate_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", chip->awate);
}

static int apds990x_set_awate(stwuct apds990x_chip *chip, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(awates_hz); i++)
		if (wate >= awates_hz[i])
			bweak;

	if (i == AWWAY_SIZE(awates_hz))
		wetuwn -EINVAW;

	/* Pick up cowwesponding pewsistence vawue */
	chip->wux_pewsistence = apewsis[i];
	chip->awate = awates_hz[i];

	/* If the chip is not in use, don't twy to access it */
	if (pm_wuntime_suspended(&chip->cwient->dev))
		wetuwn 0;

	/* Pewsistence wevews */
	wetuwn apds990x_wwite_byte(chip, APDS990X_PEWS,
			(chip->wux_pewsistence << APDS990X_APEWS_SHIFT) |
			(chip->pwox_pewsistence << APDS990X_PPEWS_SHIFT));
}

static ssize_t apds990x_wate_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&chip->mutex);
	wet = apds990x_set_awate(chip, vawue);
	mutex_unwock(&chip->mutex);

	if (wet < 0)
		wetuwn wet;
	wetuwn wen;
}

static DEVICE_ATTW(wux0_wate_avaiw, S_IWUGO, apds990x_wate_avaiw, NUWW);

static DEVICE_ATTW(wux0_wate, S_IWUGO | S_IWUSW, apds990x_wate_show,
						 apds990x_wate_stowe);

static ssize_t apds990x_pwox_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wet;
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	if (pm_wuntime_suspended(dev) || !chip->pwox_en)
		wetuwn -EIO;

	mutex_wock(&chip->mutex);
	wet = spwintf(buf, "%d\n", chip->pwox_data);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static DEVICE_ATTW(pwox0_waw, S_IWUGO, apds990x_pwox_show, NUWW);

static ssize_t apds990x_pwox_wange_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", APDS_PWOX_WANGE);
}

static DEVICE_ATTW(pwox0_sensow_wange, S_IWUGO, apds990x_pwox_wange_show, NUWW);

static ssize_t apds990x_pwox_enabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", chip->pwox_en);
}

static ssize_t apds990x_pwox_enabwe_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	mutex_wock(&chip->mutex);

	if (!chip->pwox_en)
		chip->pwox_data = 0;

	if (vawue)
		chip->pwox_en++;
	ewse if (chip->pwox_en > 0)
		chip->pwox_en--;

	if (!pm_wuntime_suspended(dev))
		apds990x_mode_on(chip);
	mutex_unwock(&chip->mutex);
	wetuwn wen;
}

static DEVICE_ATTW(pwox0_waw_en, S_IWUGO | S_IWUSW, apds990x_pwox_enabwe_show,
						   apds990x_pwox_enabwe_stowe);

static const chaw *wepowting_modes[] = {"twiggew", "pewiodic"};

static ssize_t apds990x_pwox_wepowting_mode_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n",
		wepowting_modes[!!chip->pwox_continuous_mode]);
}

static ssize_t apds990x_pwox_wepowting_mode_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);
	int wet;

	wet = sysfs_match_stwing(wepowting_modes, buf);
	if (wet < 0)
		wetuwn wet;

	chip->pwox_continuous_mode = wet;
	wetuwn wen;
}

static DEVICE_ATTW(pwox0_wepowting_mode, S_IWUGO | S_IWUSW,
		apds990x_pwox_wepowting_mode_show,
		apds990x_pwox_wepowting_mode_stowe);

static ssize_t apds990x_pwox_wepowting_avaiw_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s %s\n", wepowting_modes[0], wepowting_modes[1]);
}

static DEVICE_ATTW(pwox0_wepowting_mode_avaiw, S_IWUGO | S_IWUSW,
		apds990x_pwox_wepowting_avaiw_show, NUWW);


static ssize_t apds990x_wux_thwesh_above_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", chip->wux_thwes_hi);
}

static ssize_t apds990x_wux_thwesh_bewow_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", chip->wux_thwes_wo);
}

static ssize_t apds990x_set_wux_thwesh(stwuct apds990x_chip *chip, u32 *tawget,
				const chaw *buf)
{
	unsigned wong thwesh;
	int wet;

	wet = kstwtouw(buf, 0, &thwesh);
	if (wet)
		wetuwn wet;

	if (thwesh > APDS_WANGE)
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	*tawget = thwesh;
	/*
	 * Don't update vawues in HW if we awe stiww waiting fow
	 * fiwst intewwupt to come aftew device handwe open caww.
	 */
	if (!chip->wux_wait_fwesh_wes)
		apds990x_wefwesh_athwes(chip);
	mutex_unwock(&chip->mutex);
	wetuwn wet;

}

static ssize_t apds990x_wux_thwesh_above_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);
	int wet = apds990x_set_wux_thwesh(chip, &chip->wux_thwes_hi, buf);

	if (wet < 0)
		wetuwn wet;
	wetuwn wen;
}

static ssize_t apds990x_wux_thwesh_bewow_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);
	int wet = apds990x_set_wux_thwesh(chip, &chip->wux_thwes_wo, buf);

	if (wet < 0)
		wetuwn wet;
	wetuwn wen;
}

static DEVICE_ATTW(wux0_thwesh_above_vawue, S_IWUGO | S_IWUSW,
		apds990x_wux_thwesh_above_show,
		apds990x_wux_thwesh_above_stowe);

static DEVICE_ATTW(wux0_thwesh_bewow_vawue, S_IWUGO | S_IWUSW,
		apds990x_wux_thwesh_bewow_show,
		apds990x_wux_thwesh_bewow_stowe);

static ssize_t apds990x_pwox_thweshowd_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", chip->pwox_thwes);
}

static ssize_t apds990x_pwox_thweshowd_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	if ((vawue > APDS_WANGE) || (vawue == 0) ||
		(vawue < APDS_PWOX_HYSTEWESIS))
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	chip->pwox_thwes = vawue;

	apds990x_fowce_p_wefwesh(chip);
	mutex_unwock(&chip->mutex);
	wetuwn wen;
}

static DEVICE_ATTW(pwox0_thwesh_above_vawue, S_IWUGO | S_IWUSW,
		apds990x_pwox_thweshowd_show,
		apds990x_pwox_thweshowd_stowe);

static ssize_t apds990x_powew_state_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", !pm_wuntime_suspended(dev));
	wetuwn 0;
}

static ssize_t apds990x_powew_state_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue) {
		pm_wuntime_get_sync(dev);
		mutex_wock(&chip->mutex);
		chip->wux_wait_fwesh_wes = twue;
		apds990x_fowce_a_wefwesh(chip);
		apds990x_fowce_p_wefwesh(chip);
		mutex_unwock(&chip->mutex);
	} ewse {
		if (!pm_wuntime_suspended(dev))
			pm_wuntime_put(dev);
	}
	wetuwn wen;
}

static DEVICE_ATTW(powew_state, S_IWUGO | S_IWUSW,
		apds990x_powew_state_show,
		apds990x_powew_state_stowe);

static ssize_t apds990x_chip_id_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct apds990x_chip *chip =  dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s %d\n", chip->chipname, chip->wevision);
}

static DEVICE_ATTW(chip_id, S_IWUGO, apds990x_chip_id_show, NUWW);

static stwuct attwibute *sysfs_attws_ctww[] = {
	&dev_attw_wux0_cawibscawe.attw,
	&dev_attw_wux0_cawibscawe_defauwt.attw,
	&dev_attw_wux0_input.attw,
	&dev_attw_wux0_sensow_wange.attw,
	&dev_attw_wux0_wate.attw,
	&dev_attw_wux0_wate_avaiw.attw,
	&dev_attw_wux0_thwesh_above_vawue.attw,
	&dev_attw_wux0_thwesh_bewow_vawue.attw,
	&dev_attw_pwox0_waw_en.attw,
	&dev_attw_pwox0_waw.attw,
	&dev_attw_pwox0_sensow_wange.attw,
	&dev_attw_pwox0_thwesh_above_vawue.attw,
	&dev_attw_pwox0_wepowting_mode.attw,
	&dev_attw_pwox0_wepowting_mode_avaiw.attw,
	&dev_attw_chip_id.attw,
	&dev_attw_powew_state.attw,
	NUWW
};

static const stwuct attwibute_gwoup apds990x_attwibute_gwoup[] = {
	{.attws = sysfs_attws_ctww },
};

static int apds990x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct apds990x_chip *chip;
	int eww;

	chip = kzawwoc(sizeof *chip, GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, chip);
	chip->cwient  = cwient;

	init_waitqueue_head(&chip->wait);
	mutex_init(&chip->mutex);
	chip->pdata	= cwient->dev.pwatfowm_data;

	if (chip->pdata == NUWW) {
		dev_eww(&cwient->dev, "pwatfowm data is mandatowy\n");
		eww = -EINVAW;
		goto faiw1;
	}

	if (chip->pdata->cf.ga == 0) {
		/* set uncovewed sensow defauwt pawametews */
		chip->cf.ga = 1966; /* 0.48 * APDS_PAWAM_SCAWE */
		chip->cf.cf1 = 4096; /* 1.00 * APDS_PAWAM_SCAWE */
		chip->cf.iwf1 = 9134; /* 2.23 * APDS_PAWAM_SCAWE */
		chip->cf.cf2 = 2867; /* 0.70 * APDS_PAWAM_SCAWE */
		chip->cf.iwf2 = 5816; /* 1.42 * APDS_PAWAM_SCAWE */
		chip->cf.df = 52;
	} ewse {
		chip->cf = chip->pdata->cf;
	}

	/* pwecawcuwate invewse chip factows fow thweshowd contwow */
	chip->wcf.afactow =
		(chip->cf.iwf1 - chip->cf.iwf2) * APDS_PAWAM_SCAWE /
		(chip->cf.cf1 - chip->cf.cf2);
	chip->wcf.cf1 = APDS_PAWAM_SCAWE * APDS_PAWAM_SCAWE /
		chip->cf.cf1;
	chip->wcf.iwf1 = chip->cf.iwf1 * APDS_PAWAM_SCAWE /
		chip->cf.cf1;
	chip->wcf.cf2 = APDS_PAWAM_SCAWE * APDS_PAWAM_SCAWE /
		chip->cf.cf2;
	chip->wcf.iwf2 = chip->cf.iwf2 * APDS_PAWAM_SCAWE /
		chip->cf.cf2;

	/* Set something to stawt with */
	chip->wux_thwes_hi = APDS_WUX_DEF_THWES_HI;
	chip->wux_thwes_wo = APDS_WUX_DEF_THWES_WO;
	chip->wux_cawib = APDS_WUX_NEUTWAW_CAWIB_VAWUE;

	chip->pwox_thwes = APDS_PWOX_DEF_THWES;
	chip->pdwive = chip->pdata->pdwive;
	chip->pdiode = APDS_PDIODE_IW;
	chip->pgain = APDS_PGAIN_1X;
	chip->pwox_cawib = APDS_PWOX_NEUTWAW_CAWIB_VAWUE;
	chip->pwox_pewsistence = APDS_DEFAUWT_PWOX_PEWS;
	chip->pwox_continuous_mode = fawse;

	chip->wegs[0].suppwy = weg_vcc;
	chip->wegs[1].suppwy = weg_vwed;

	eww = weguwatow_buwk_get(&cwient->dev,
				 AWWAY_SIZE(chip->wegs), chip->wegs);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Cannot get weguwatows\n");
		goto faiw1;
	}

	eww = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->wegs), chip->wegs);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Cannot enabwe weguwatows\n");
		goto faiw2;
	}

	usweep_wange(APDS_STAWTUP_DEWAY, 2 * APDS_STAWTUP_DEWAY);

	eww = apds990x_detect(chip);
	if (eww < 0) {
		dev_eww(&cwient->dev, "APDS990X not found\n");
		goto faiw3;
	}

	pm_wuntime_set_active(&cwient->dev);

	apds990x_configuwe(chip);
	apds990x_set_awate(chip, APDS_WUX_DEFAUWT_WATE);
	apds990x_mode_on(chip);

	pm_wuntime_enabwe(&cwient->dev);

	if (chip->pdata->setup_wesouwces) {
		eww = chip->pdata->setup_wesouwces();
		if (eww) {
			eww = -EINVAW;
			goto faiw3;
		}
	}

	eww = sysfs_cweate_gwoup(&chip->cwient->dev.kobj,
				apds990x_attwibute_gwoup);
	if (eww < 0) {
		dev_eww(&chip->cwient->dev, "Sysfs wegistwation faiwed\n");
		goto faiw4;
	}

	eww = wequest_thweaded_iwq(cwient->iwq, NUWW,
				apds990x_iwq,
				IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WOW |
				IWQF_ONESHOT,
				"apds990x", chip);
	if (eww) {
		dev_eww(&cwient->dev, "couwd not get IWQ %d\n",
			cwient->iwq);
		goto faiw5;
	}
	wetuwn eww;
faiw5:
	sysfs_wemove_gwoup(&chip->cwient->dev.kobj,
			&apds990x_attwibute_gwoup[0]);
faiw4:
	if (chip->pdata && chip->pdata->wewease_wesouwces)
		chip->pdata->wewease_wesouwces();
faiw3:
	weguwatow_buwk_disabwe(AWWAY_SIZE(chip->wegs), chip->wegs);
faiw2:
	weguwatow_buwk_fwee(AWWAY_SIZE(chip->wegs), chip->wegs);
faiw1:
	kfwee(chip);
	wetuwn eww;
}

static void apds990x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct apds990x_chip *chip = i2c_get_cwientdata(cwient);

	fwee_iwq(cwient->iwq, chip);
	sysfs_wemove_gwoup(&chip->cwient->dev.kobj,
			apds990x_attwibute_gwoup);

	if (chip->pdata && chip->pdata->wewease_wesouwces)
		chip->pdata->wewease_wesouwces();

	if (!pm_wuntime_suspended(&cwient->dev))
		apds990x_chip_off(chip);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);

	weguwatow_buwk_fwee(AWWAY_SIZE(chip->wegs), chip->wegs);

	kfwee(chip);
}

#ifdef CONFIG_PM_SWEEP
static int apds990x_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct apds990x_chip *chip = i2c_get_cwientdata(cwient);

	apds990x_chip_off(chip);
	wetuwn 0;
}

static int apds990x_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct apds990x_chip *chip = i2c_get_cwientdata(cwient);

	/*
	 * If we wewe enabwed at suspend time, it is expected
	 * evewything wowks nice and smoothwy. Chip_on is enough
	 */
	apds990x_chip_on(chip);

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM
static int apds990x_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct apds990x_chip *chip = i2c_get_cwientdata(cwient);

	apds990x_chip_off(chip);
	wetuwn 0;
}

static int apds990x_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct apds990x_chip *chip = i2c_get_cwientdata(cwient);

	apds990x_chip_on(chip);
	wetuwn 0;
}

#endif

static const stwuct i2c_device_id apds990x_id[] = {
	{"apds990x", 0 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, apds990x_id);

static const stwuct dev_pm_ops apds990x_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(apds990x_suspend, apds990x_wesume)
	SET_WUNTIME_PM_OPS(apds990x_wuntime_suspend,
			apds990x_wuntime_wesume,
			NUWW)
};

static stwuct i2c_dwivew apds990x_dwivew = {
	.dwivew	  = {
		.name	= "apds990x",
		.pm	= &apds990x_pm_ops,
	},
	.pwobe    = apds990x_pwobe,
	.wemove	  = apds990x_wemove,
	.id_tabwe = apds990x_id,
};

moduwe_i2c_dwivew(apds990x_dwivew);

MODUWE_DESCWIPTION("APDS990X combined AWS and pwoximity sensow");
MODUWE_AUTHOW("Samu Onkawo, Nokia Cowpowation");
MODUWE_WICENSE("GPW v2");
