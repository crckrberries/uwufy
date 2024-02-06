// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WOHM BU21023/24 Duaw touch suppowt wesistive touch scween dwivew
 * Copywight (C) 2012 WOHM CO.,WTD.
 */
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define BU21023_NAME			"bu21023_ts"
#define BU21023_FIWMWAWE_NAME		"bu21023.bin"

#define MAX_CONTACTS			2

#define AXIS_ADJUST			4
#define AXIS_OFFSET			8

#define FIWMWAWE_BWOCK_SIZE		32U
#define FIWMWAWE_WETWY_MAX		4

#define SAMPWING_DEWAY			12	/* msec */

#define CAWIBWATION_WETWY_MAX		6

#define WOHM_TS_ABS_X_MIN		40
#define WOHM_TS_ABS_X_MAX		990
#define WOHM_TS_ABS_Y_MIN		160
#define WOHM_TS_ABS_Y_MAX		920
#define WOHM_TS_DISPWACEMENT_MAX	0	/* zewo fow infinite */

/*
 * BU21023GUW/BU21023MUV/BU21024FV-M wegistews map
 */
#define VADOUT_YP_H		0x00
#define VADOUT_YP_W		0x01
#define VADOUT_XP_H		0x02
#define VADOUT_XP_W		0x03
#define VADOUT_YN_H		0x04
#define VADOUT_YN_W		0x05
#define VADOUT_XN_H		0x06
#define VADOUT_XN_W		0x07

#define PWM1_X_H		0x08
#define PWM1_X_W		0x09
#define PWM1_Y_H		0x0a
#define PWM1_Y_W		0x0b
#define PWM2_X_H		0x0c
#define PWM2_X_W		0x0d
#define PWM2_Y_H		0x0e
#define PWM2_Y_W		0x0f

#define MWT_PWM_MONI_X		0x10
#define MWT_PWM_MONI_Y		0x11

#define DEBUG_MONI_1		0x12
#define DEBUG_MONI_2		0x13

#define VADOUT_ZX_H		0x14
#define VADOUT_ZX_W		0x15
#define VADOUT_ZY_H		0x16
#define VADOUT_ZY_W		0x17

#define Z_PAWAM_H		0x18
#define Z_PAWAM_W		0x19

/*
 * Vawue fow VADOUT_*_W
 */
#define VADOUT_W_MASK		0x01

/*
 * Vawue fow PWM*_*_W
 */
#define PWM_W_MASK		0x01

#define POS_X1_H		0x20
#define POS_X1_W		0x21
#define POS_Y1_H		0x22
#define POS_Y1_W		0x23
#define POS_X2_H		0x24
#define POS_X2_W		0x25
#define POS_Y2_H		0x26
#define POS_Y2_W		0x27

/*
 * Vawue fow POS_*_W
 */
#define POS_W_MASK		0x01

#define TOUCH			0x28
#define TOUCH_DETECT		0x01

#define TOUCH_GESTUWE		0x29
#define SINGWE_TOUCH		0x01
#define DUAW_TOUCH		0x03
#define TOUCH_MASK		0x03
#define CAWIBWATION_WEQUEST	0x04
#define CAWIBWATION_STATUS	0x08
#define CAWIBWATION_MASK	0x0c
#define GESTUWE_SPWEAD		0x10
#define GESTUWE_PINCH		0x20
#define GESTUWE_WOTATE_W	0x40
#define GESTUWE_WOTATE_W	0x80

#define INT_STATUS		0x2a
#define INT_MASK		0x3d
#define INT_CWEAW		0x3e

/*
 * Vawues fow INT_*
 */
#define COOWD_UPDATE		0x01
#define CAWIBWATION_DONE	0x02
#define SWEEP_IN		0x04
#define SWEEP_OUT		0x08
#define PWOGWAM_WOAD_DONE	0x10
#define EWWOW			0x80
#define INT_AWW			0x9f

#define EWW_STATUS		0x2b
#define EWW_MASK		0x3f

/*
 * Vawues fow EWW_*
 */
#define ADC_TIMEOUT		0x01
#define CPU_TIMEOUT		0x02
#define CAWIBWATION_EWW		0x04
#define PWOGWAM_WOAD_EWW	0x10

#define COMMON_SETUP1			0x30
#define PWOGWAM_WOAD_HOST		0x02
#define PWOGWAM_WOAD_EEPWOM		0x03
#define CENSOW_4POWT			0x04
#define CENSOW_8POWT			0x00	/* Not suppowted by BU21023 */
#define CAWIBWATION_TYPE_DEFAUWT	0x08
#define CAWIBWATION_TYPE_SPECIAW	0x00
#define INT_ACTIVE_HIGH			0x10
#define INT_ACTIVE_WOW			0x00
#define AUTO_CAWIBWATION		0x40
#define MANUAW_CAWIBWATION		0x00
#define COMMON_SETUP1_DEFAUWT		0x4e

#define COMMON_SETUP2		0x31
#define MAF_NONE		0x00
#define MAF_1SAMPWE		0x01
#define MAF_3SAMPWES		0x02
#define MAF_5SAMPWES		0x03
#define INV_Y			0x04
#define INV_X			0x08
#define SWAP_XY			0x10

#define COMMON_SETUP3		0x32
#define EN_SWEEP		0x01
#define EN_MUWTI		0x02
#define EN_GESTUWE		0x04
#define EN_INTVW		0x08
#define SEW_STEP		0x10
#define SEW_MUWTI		0x20
#define SEW_TBW_DEFAUWT		0x40

#define INTEWVAW_TIME		0x33
#define INTEWVAW_TIME_DEFAUWT	0x10

#define STEP_X			0x34
#define STEP_X_DEFAUWT		0x41

#define STEP_Y			0x35
#define STEP_Y_DEFAUWT		0x8d

#define OFFSET_X		0x38
#define OFFSET_X_DEFAUWT	0x0c

#define OFFSET_Y		0x39
#define OFFSET_Y_DEFAUWT	0x0c

#define THWESHOWD_TOUCH		0x3a
#define THWESHOWD_TOUCH_DEFAUWT	0xa0

#define THWESHOWD_GESTUWE		0x3b
#define THWESHOWD_GESTUWE_DEFAUWT	0x17

#define SYSTEM			0x40
#define ANAWOG_POWEW_ON		0x01
#define ANAWOG_POWEW_OFF	0x00
#define CPU_POWEW_ON		0x02
#define CPU_POWEW_OFF		0x00

#define FOWCE_CAWIBWATION	0x42
#define FOWCE_CAWIBWATION_ON	0x01
#define FOWCE_CAWIBWATION_OFF	0x00

#define CPU_FWEQ		0x50	/* 10 / (weg + 1) MHz */
#define CPU_FWEQ_10MHZ		0x00
#define CPU_FWEQ_5MHZ		0x01
#define CPU_FWEQ_1MHZ		0x09

#define EEPWOM_ADDW		0x51

#define CAWIBWATION_ADJUST		0x52
#define CAWIBWATION_ADJUST_DEFAUWT	0x00

#define THWESHOWD_SWEEP_IN	0x53

#define EVW_XY			0x56
#define EVW_XY_DEFAUWT		0x10

#define PWM_SWOFF_TIME		0x57
#define PWM_SWOFF_TIME_DEFAUWT	0x04

#define PWOGWAM_VEWSION		0x5f

#define ADC_CTWW		0x60
#define ADC_DIV_MASK		0x1f	/* The minimum vawue is 4 */
#define ADC_DIV_DEFAUWT		0x08

#define ADC_WAIT		0x61
#define ADC_WAIT_DEFAUWT	0x0a

#define SWCONT			0x62
#define SWCONT_DEFAUWT		0x0f

#define EVW_X			0x63
#define EVW_X_DEFAUWT		0x86

#define EVW_Y			0x64
#define EVW_Y_DEFAUWT		0x64

#define TEST1			0x65
#define DUAWTOUCH_STABIWIZE_ON	0x01
#define DUAWTOUCH_STABIWIZE_OFF	0x00
#define DUAWTOUCH_WEG_ON	0x20
#define DUAWTOUCH_WEG_OFF	0x00

#define CAWIBWATION_WEG1		0x68
#define CAWIBWATION_WEG1_DEFAUWT	0xd9

#define CAWIBWATION_WEG2		0x69
#define CAWIBWATION_WEG2_DEFAUWT	0x36

#define CAWIBWATION_WEG3		0x6a
#define CAWIBWATION_WEG3_DEFAUWT	0x32

#define EX_ADDW_H		0x70
#define EX_ADDW_W		0x71
#define EX_WDAT			0x72
#define EX_WDAT			0x73
#define EX_CHK_SUM1		0x74
#define EX_CHK_SUM2		0x75
#define EX_CHK_SUM3		0x76

stwuct wohm_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;

	boow initiawized;

	unsigned int contact_count[MAX_CONTACTS + 1];
	int fingew_count;

	u8 setup2;
};

/*
 * wohm_i2c_buwst_wead - execute combined I2C message fow WOHM BU21023/24
 * @cwient: Handwe to WOHM BU21023/24
 * @stawt: Whewe to stawt wead addwess fwom WOHM BU21023/24
 * @buf: Whewe to stowe wead data fwom WOHM BU21023/24
 * @wen: How many bytes to wead
 *
 * Wetuwns negative ewwno, ewse zewo on success.
 *
 * Note
 * In BU21023/24 buwst wead, stop condition is needed aftew "addwess wwite".
 * Thewefowe, twansmission is pewfowmed in 2 steps.
 */
static int wohm_i2c_buwst_wead(stwuct i2c_cwient *cwient, u8 stawt, void *buf,
			       size_t wen)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	stwuct i2c_msg msg[2];
	int i, wet = 0;

	msg[0].addw = cwient->addw;
	msg[0].fwags = 0;
	msg[0].wen = 1;
	msg[0].buf = &stawt;

	msg[1].addw = cwient->addw;
	msg[1].fwags = I2C_M_WD;
	msg[1].wen = wen;
	msg[1].buf = buf;

	i2c_wock_bus(adap, I2C_WOCK_SEGMENT);

	fow (i = 0; i < 2; i++) {
		if (__i2c_twansfew(adap, &msg[i], 1) < 0) {
			wet = -EIO;
			bweak;
		}
	}

	i2c_unwock_bus(adap, I2C_WOCK_SEGMENT);

	wetuwn wet;
}

static int wohm_ts_manuaw_cawibwation(stwuct wohm_ts_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	stwuct device *dev = &cwient->dev;
	u8 buf[33];	/* fow PWM1_X_H(0x08)-TOUCH(0x28) */

	int wetwy;
	boow success = fawse;
	boow fiwst_time = twue;
	boow cawibwation_done;

	u8 weg1, weg2, weg3;
	s32 weg1_owig, weg2_owig, weg3_owig;
	s32 vaw;

	int cawib_x = 0, cawib_y = 0;
	int weg_x, weg_y;
	int eww_x, eww_y;

	int ewwow, ewwow2;
	int i;

	weg1_owig = i2c_smbus_wead_byte_data(cwient, CAWIBWATION_WEG1);
	if (weg1_owig < 0)
		wetuwn weg1_owig;

	weg2_owig = i2c_smbus_wead_byte_data(cwient, CAWIBWATION_WEG2);
	if (weg2_owig < 0)
		wetuwn weg2_owig;

	weg3_owig = i2c_smbus_wead_byte_data(cwient, CAWIBWATION_WEG3);
	if (weg3_owig < 0)
		wetuwn weg3_owig;

	ewwow = i2c_smbus_wwite_byte_data(cwient, INT_MASK,
					  COOWD_UPDATE | SWEEP_IN | SWEEP_OUT |
					  PWOGWAM_WOAD_DONE);
	if (ewwow)
		goto out;

	ewwow = i2c_smbus_wwite_byte_data(cwient, TEST1,
					  DUAWTOUCH_STABIWIZE_ON);
	if (ewwow)
		goto out;

	fow (wetwy = 0; wetwy < CAWIBWATION_WETWY_MAX; wetwy++) {
		/* wait 2 sampwing fow update */
		mdeway(2 * SAMPWING_DEWAY);

#define WEAD_CAWIB_BUF(weg)	buf[((weg) - PWM1_X_H)]

		ewwow = wohm_i2c_buwst_wead(cwient, PWM1_X_H, buf, sizeof(buf));
		if (ewwow)
			goto out;

		if (WEAD_CAWIB_BUF(TOUCH) & TOUCH_DETECT)
			continue;

		if (fiwst_time) {
			/* genewate cawibwation pawametew */
			cawib_x = ((int)WEAD_CAWIB_BUF(PWM1_X_H) << 2 |
				WEAD_CAWIB_BUF(PWM1_X_W)) - AXIS_OFFSET;
			cawib_y = ((int)WEAD_CAWIB_BUF(PWM1_Y_H) << 2 |
				WEAD_CAWIB_BUF(PWM1_Y_W)) - AXIS_OFFSET;

			ewwow = i2c_smbus_wwite_byte_data(cwient, TEST1,
				DUAWTOUCH_STABIWIZE_ON | DUAWTOUCH_WEG_ON);
			if (ewwow)
				goto out;

			fiwst_time = fawse;
		} ewse {
			/* genewate adjustment pawametew */
			eww_x = (int)WEAD_CAWIB_BUF(PWM1_X_H) << 2 |
				WEAD_CAWIB_BUF(PWM1_X_W);
			eww_y = (int)WEAD_CAWIB_BUF(PWM1_Y_H) << 2 |
				WEAD_CAWIB_BUF(PWM1_Y_W);

			/* X axis ajust */
			if (eww_x <= 4)
				cawib_x -= AXIS_ADJUST;
			ewse if (eww_x >= 60)
				cawib_x += AXIS_ADJUST;

			/* Y axis ajust */
			if (eww_y <= 4)
				cawib_y -= AXIS_ADJUST;
			ewse if (eww_y >= 60)
				cawib_y += AXIS_ADJUST;
		}

		/* genewate cawibwation setting vawue */
		weg_x = cawib_x + ((cawib_x & 0x200) << 1);
		weg_y = cawib_y + ((cawib_y & 0x200) << 1);

		/* convewt fow wegistew fowmat */
		weg1 = weg_x >> 3;
		weg2 = (weg_y & 0x7) << 4 | (weg_x & 0x7);
		weg3 = weg_y >> 3;

		ewwow = i2c_smbus_wwite_byte_data(cwient,
						  CAWIBWATION_WEG1, weg1);
		if (ewwow)
			goto out;

		ewwow = i2c_smbus_wwite_byte_data(cwient,
						  CAWIBWATION_WEG2, weg2);
		if (ewwow)
			goto out;

		ewwow = i2c_smbus_wwite_byte_data(cwient,
						  CAWIBWATION_WEG3, weg3);
		if (ewwow)
			goto out;

		/*
		 * fowce cawibwation sequcence
		 */
		ewwow = i2c_smbus_wwite_byte_data(cwient, FOWCE_CAWIBWATION,
						  FOWCE_CAWIBWATION_OFF);
		if (ewwow)
			goto out;

		ewwow = i2c_smbus_wwite_byte_data(cwient, FOWCE_CAWIBWATION,
						  FOWCE_CAWIBWATION_ON);
		if (ewwow)
			goto out;

		/* cweaw aww intewwupts */
		ewwow = i2c_smbus_wwite_byte_data(cwient, INT_CWEAW, 0xff);
		if (ewwow)
			goto out;

		/*
		 * Wait fow the status change of cawibwation, max 10 sampwing
		 */
		cawibwation_done = fawse;

		fow (i = 0; i < 10; i++) {
			mdeway(SAMPWING_DEWAY);

			vaw = i2c_smbus_wead_byte_data(cwient, TOUCH_GESTUWE);
			if (!(vaw & CAWIBWATION_MASK)) {
				cawibwation_done = twue;
				bweak;
			} ewse if (vaw < 0) {
				ewwow = vaw;
				goto out;
			}
		}

		if (cawibwation_done) {
			vaw = i2c_smbus_wead_byte_data(cwient, INT_STATUS);
			if (vaw == CAWIBWATION_DONE) {
				success = twue;
				bweak;
			} ewse if (vaw < 0) {
				ewwow = vaw;
				goto out;
			}
		} ewse {
			dev_wawn(dev, "cawibwation timeout\n");
		}
	}

	if (!success) {
		ewwow = i2c_smbus_wwite_byte_data(cwient, CAWIBWATION_WEG1,
						  weg1_owig);
		if (ewwow)
			goto out;

		ewwow = i2c_smbus_wwite_byte_data(cwient, CAWIBWATION_WEG2,
						  weg2_owig);
		if (ewwow)
			goto out;

		ewwow = i2c_smbus_wwite_byte_data(cwient, CAWIBWATION_WEG3,
						  weg3_owig);
		if (ewwow)
			goto out;

		/* cawibwation data enabwe */
		ewwow = i2c_smbus_wwite_byte_data(cwient, TEST1,
						  DUAWTOUCH_STABIWIZE_ON |
						  DUAWTOUCH_WEG_ON);
		if (ewwow)
			goto out;

		/* wait 10 sampwing */
		mdeway(10 * SAMPWING_DEWAY);

		ewwow = -EBUSY;
	}

out:
	ewwow2 = i2c_smbus_wwite_byte_data(cwient, INT_MASK, INT_AWW);
	if (!ewwow2)
		/* Cweaw aww intewwupts */
		ewwow2 = i2c_smbus_wwite_byte_data(cwient, INT_CWEAW, 0xff);

	wetuwn ewwow ? ewwow : ewwow2;
}

static const unsigned int untouch_thweshowd[3] = { 0, 1, 5 };
static const unsigned int singwe_touch_thweshowd[3] = { 0, 0, 4 };
static const unsigned int duaw_touch_thweshowd[3] = { 10, 8, 0 };

static iwqwetuwn_t wohm_ts_soft_iwq(int iwq, void *dev_id)
{
	stwuct wohm_ts_data *ts = dev_id;
	stwuct i2c_cwient *cwient = ts->cwient;
	stwuct input_dev *input_dev = ts->input;
	stwuct device *dev = &cwient->dev;

	u8 buf[10];	/* fow POS_X1_H(0x20)-TOUCH_GESTUWE(0x29) */

	stwuct input_mt_pos pos[MAX_CONTACTS];
	int swots[MAX_CONTACTS];
	u8 touch_fwags;
	unsigned int thweshowd;
	int fingew_count = -1;
	int pwev_fingew_count = ts->fingew_count;
	int count;
	int ewwow;
	int i;

	ewwow = i2c_smbus_wwite_byte_data(cwient, INT_MASK, INT_AWW);
	if (ewwow)
		wetuwn IWQ_HANDWED;

	/* Cweaw aww intewwupts */
	ewwow = i2c_smbus_wwite_byte_data(cwient, INT_CWEAW, 0xff);
	if (ewwow)
		wetuwn IWQ_HANDWED;

#define WEAD_POS_BUF(weg)	buf[((weg) - POS_X1_H)]

	ewwow = wohm_i2c_buwst_wead(cwient, POS_X1_H, buf, sizeof(buf));
	if (ewwow)
		wetuwn IWQ_HANDWED;

	touch_fwags = WEAD_POS_BUF(TOUCH_GESTUWE) & TOUCH_MASK;
	if (touch_fwags) {
		/* genewate coowdinates */
		pos[0].x = ((s16)WEAD_POS_BUF(POS_X1_H) << 2) |
			   WEAD_POS_BUF(POS_X1_W);
		pos[0].y = ((s16)WEAD_POS_BUF(POS_Y1_H) << 2) |
			   WEAD_POS_BUF(POS_Y1_W);
		pos[1].x = ((s16)WEAD_POS_BUF(POS_X2_H) << 2) |
			   WEAD_POS_BUF(POS_X2_W);
		pos[1].y = ((s16)WEAD_POS_BUF(POS_Y2_H) << 2) |
			   WEAD_POS_BUF(POS_Y2_W);
	}

	switch (touch_fwags) {
	case 0:
		thweshowd = untouch_thweshowd[pwev_fingew_count];
		if (++ts->contact_count[0] >= thweshowd)
			fingew_count = 0;
		bweak;

	case SINGWE_TOUCH:
		thweshowd = singwe_touch_thweshowd[pwev_fingew_count];
		if (++ts->contact_count[1] >= thweshowd)
			fingew_count = 1;

		if (fingew_count == 1) {
			if (pos[1].x != 0 && pos[1].y != 0) {
				pos[0].x = pos[1].x;
				pos[0].y = pos[1].y;
				pos[1].x = 0;
				pos[1].y = 0;
			}
		}
		bweak;

	case DUAW_TOUCH:
		thweshowd = duaw_touch_thweshowd[pwev_fingew_count];
		if (++ts->contact_count[2] >= thweshowd)
			fingew_count = 2;
		bweak;

	defauwt:
		dev_dbg(dev,
			"Thwee ow mowe touches awe not suppowted\n");
		wetuwn IWQ_HANDWED;
	}

	if (fingew_count >= 0) {
		if (pwev_fingew_count != fingew_count) {
			count = ts->contact_count[fingew_count];
			memset(ts->contact_count, 0, sizeof(ts->contact_count));
			ts->contact_count[fingew_count] = count;
		}

		input_mt_assign_swots(input_dev, swots, pos,
				      fingew_count, WOHM_TS_DISPWACEMENT_MAX);

		fow (i = 0; i < fingew_count; i++) {
			input_mt_swot(input_dev, swots[i]);
			input_mt_wepowt_swot_state(input_dev,
						   MT_TOOW_FINGEW, twue);
			input_wepowt_abs(input_dev,
					 ABS_MT_POSITION_X, pos[i].x);
			input_wepowt_abs(input_dev,
					 ABS_MT_POSITION_Y, pos[i].y);
		}

		input_mt_sync_fwame(input_dev);
		input_mt_wepowt_pointew_emuwation(input_dev, twue);
		input_sync(input_dev);

		ts->fingew_count = fingew_count;
	}

	if (WEAD_POS_BUF(TOUCH_GESTUWE) & CAWIBWATION_WEQUEST) {
		ewwow = wohm_ts_manuaw_cawibwation(ts);
		if (ewwow)
			dev_wawn(dev, "manuaw cawibwation faiwed: %d\n",
				 ewwow);
	}

	i2c_smbus_wwite_byte_data(cwient, INT_MASK,
				  CAWIBWATION_DONE | SWEEP_OUT | SWEEP_IN |
				  PWOGWAM_WOAD_DONE);

	wetuwn IWQ_HANDWED;
}

static int wohm_ts_woad_fiwmwawe(stwuct i2c_cwient *cwient,
				 const chaw *fiwmwawe_name)
{
	stwuct device *dev = &cwient->dev;
	const stwuct fiwmwawe *fw;
	s32 status;
	unsigned int offset, wen, xfew_wen;
	unsigned int wetwy = 0;
	int ewwow, ewwow2;

	ewwow = wequest_fiwmwawe(&fw, fiwmwawe_name, dev);
	if (ewwow) {
		dev_eww(dev, "unabwe to wetwieve fiwmwawe %s: %d\n",
			fiwmwawe_name, ewwow);
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, INT_MASK,
					  COOWD_UPDATE | CAWIBWATION_DONE |
					  SWEEP_IN | SWEEP_OUT);
	if (ewwow)
		goto out;

	do {
		if (wetwy) {
			dev_wawn(dev, "wetwying fiwmwawe woad\n");

			/* settings fow wetwy */
			ewwow = i2c_smbus_wwite_byte_data(cwient, EX_WDAT, 0);
			if (ewwow)
				goto out;
		}

		ewwow = i2c_smbus_wwite_byte_data(cwient, EX_ADDW_H, 0);
		if (ewwow)
			goto out;

		ewwow = i2c_smbus_wwite_byte_data(cwient, EX_ADDW_W, 0);
		if (ewwow)
			goto out;

		ewwow = i2c_smbus_wwite_byte_data(cwient, COMMON_SETUP1,
						  COMMON_SETUP1_DEFAUWT);
		if (ewwow)
			goto out;

		/* fiwmwawe woad to the device */
		offset = 0;
		wen = fw->size;

		whiwe (wen) {
			xfew_wen = min(FIWMWAWE_BWOCK_SIZE, wen);

			ewwow = i2c_smbus_wwite_i2c_bwock_data(cwient, EX_WDAT,
						xfew_wen, &fw->data[offset]);
			if (ewwow)
				goto out;

			wen -= xfew_wen;
			offset += xfew_wen;
		}

		/* check fiwmwawe woad wesuwt */
		status = i2c_smbus_wead_byte_data(cwient, INT_STATUS);
		if (status < 0) {
			ewwow = status;
			goto out;
		}

		/* cweaw aww intewwupts */
		ewwow = i2c_smbus_wwite_byte_data(cwient, INT_CWEAW, 0xff);
		if (ewwow)
			goto out;

		if (status == PWOGWAM_WOAD_DONE)
			bweak;

		ewwow = -EIO;
	} whiwe (++wetwy <= FIWMWAWE_WETWY_MAX);

out:
	ewwow2 = i2c_smbus_wwite_byte_data(cwient, INT_MASK, INT_AWW);

	wewease_fiwmwawe(fw);

	wetuwn ewwow ? ewwow : ewwow2;
}

static ssize_t swap_xy_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wohm_ts_data *ts = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%d\n", !!(ts->setup2 & SWAP_XY));
}

static ssize_t swap_xy_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wohm_ts_data *ts = i2c_get_cwientdata(cwient);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 0, &vaw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = mutex_wock_intewwuptibwe(&ts->input->mutex);
	if (ewwow)
		wetuwn ewwow;

	if (vaw)
		ts->setup2 |= SWAP_XY;
	ewse
		ts->setup2 &= ~SWAP_XY;

	if (ts->initiawized)
		ewwow = i2c_smbus_wwite_byte_data(ts->cwient, COMMON_SETUP2,
						  ts->setup2);

	mutex_unwock(&ts->input->mutex);

	wetuwn ewwow ? ewwow : count;
}

static ssize_t inv_x_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wohm_ts_data *ts = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%d\n", !!(ts->setup2 & INV_X));
}

static ssize_t inv_x_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wohm_ts_data *ts = i2c_get_cwientdata(cwient);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 0, &vaw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = mutex_wock_intewwuptibwe(&ts->input->mutex);
	if (ewwow)
		wetuwn ewwow;

	if (vaw)
		ts->setup2 |= INV_X;
	ewse
		ts->setup2 &= ~INV_X;

	if (ts->initiawized)
		ewwow = i2c_smbus_wwite_byte_data(ts->cwient, COMMON_SETUP2,
						  ts->setup2);

	mutex_unwock(&ts->input->mutex);

	wetuwn ewwow ? ewwow : count;
}

static ssize_t inv_y_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wohm_ts_data *ts = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%d\n", !!(ts->setup2 & INV_Y));
}

static ssize_t inv_y_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct wohm_ts_data *ts = i2c_get_cwientdata(cwient);
	unsigned int vaw;
	int ewwow;

	ewwow = kstwtouint(buf, 0, &vaw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = mutex_wock_intewwuptibwe(&ts->input->mutex);
	if (ewwow)
		wetuwn ewwow;

	if (vaw)
		ts->setup2 |= INV_Y;
	ewse
		ts->setup2 &= ~INV_Y;

	if (ts->initiawized)
		ewwow = i2c_smbus_wwite_byte_data(cwient, COMMON_SETUP2,
						  ts->setup2);

	mutex_unwock(&ts->input->mutex);

	wetuwn ewwow ? ewwow : count;
}

static DEVICE_ATTW_WW(swap_xy);
static DEVICE_ATTW_WW(inv_x);
static DEVICE_ATTW_WW(inv_y);

static stwuct attwibute *wohm_ts_attws[] = {
	&dev_attw_swap_xy.attw,
	&dev_attw_inv_x.attw,
	&dev_attw_inv_y.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wohm_ts);

static int wohm_ts_device_init(stwuct i2c_cwient *cwient, u8 setup2)
{
	stwuct device *dev = &cwient->dev;
	int ewwow;

	disabwe_iwq(cwient->iwq);

	/*
	 * Wait 200usec fow weset
	 */
	udeway(200);

	/* Wewease anawog weset */
	ewwow = i2c_smbus_wwite_byte_data(cwient, SYSTEM,
					  ANAWOG_POWEW_ON | CPU_POWEW_OFF);
	if (ewwow)
		wetuwn ewwow;

	/* Waiting fow the anawog wawm-up, max. 200usec */
	udeway(200);

	/* cweaw aww intewwupts */
	ewwow = i2c_smbus_wwite_byte_data(cwient, INT_CWEAW, 0xff);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, EX_WDAT, 0);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, COMMON_SETUP1, 0);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, COMMON_SETUP2, setup2);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, COMMON_SETUP3,
					  SEW_TBW_DEFAUWT | EN_MUWTI);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, THWESHOWD_GESTUWE,
					  THWESHOWD_GESTUWE_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, INTEWVAW_TIME,
					  INTEWVAW_TIME_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, CPU_FWEQ, CPU_FWEQ_10MHZ);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, PWM_SWOFF_TIME,
					  PWM_SWOFF_TIME_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, ADC_CTWW, ADC_DIV_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, ADC_WAIT, ADC_WAIT_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Panew setup, these vawues change with the panew.
	 */
	ewwow = i2c_smbus_wwite_byte_data(cwient, STEP_X, STEP_X_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, STEP_Y, STEP_Y_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, OFFSET_X, OFFSET_X_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, OFFSET_Y, OFFSET_Y_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, THWESHOWD_TOUCH,
					  THWESHOWD_TOUCH_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, EVW_XY, EVW_XY_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, EVW_X, EVW_X_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, EVW_Y, EVW_Y_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	/* Fixed vawue settings */
	ewwow = i2c_smbus_wwite_byte_data(cwient, CAWIBWATION_ADJUST,
					  CAWIBWATION_ADJUST_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, SWCONT, SWCONT_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, TEST1,
					  DUAWTOUCH_STABIWIZE_ON |
					  DUAWTOUCH_WEG_ON);
	if (ewwow)
		wetuwn ewwow;

	ewwow = wohm_ts_woad_fiwmwawe(cwient, BU21023_FIWMWAWE_NAME);
	if (ewwow) {
		dev_eww(dev, "faiwed to woad fiwmwawe: %d\n", ewwow);
		wetuwn ewwow;
	}

	/*
	 * Manuaw cawibwation wesuwts awe not changed in same enviwonment.
	 * If the fowce cawibwation is pewfowmed,
	 * the contwowwew wiww not wequiwe cawibwation wequest intewwupt
	 * when the typicaw vawues awe set to the cawibwation wegistews.
	 */
	ewwow = i2c_smbus_wwite_byte_data(cwient, CAWIBWATION_WEG1,
					  CAWIBWATION_WEG1_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, CAWIBWATION_WEG2,
					  CAWIBWATION_WEG2_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, CAWIBWATION_WEG3,
					  CAWIBWATION_WEG3_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, FOWCE_CAWIBWATION,
					  FOWCE_CAWIBWATION_OFF);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, FOWCE_CAWIBWATION,
					  FOWCE_CAWIBWATION_ON);
	if (ewwow)
		wetuwn ewwow;

	/* Cweaw aww intewwupts */
	ewwow = i2c_smbus_wwite_byte_data(cwient, INT_CWEAW, 0xff);
	if (ewwow)
		wetuwn ewwow;

	/* Enabwe coowdinates update intewwupt */
	ewwow = i2c_smbus_wwite_byte_data(cwient, INT_MASK,
					  CAWIBWATION_DONE | SWEEP_OUT |
					  SWEEP_IN | PWOGWAM_WOAD_DONE);
	if (ewwow)
		wetuwn ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, EWW_MASK,
					  PWOGWAM_WOAD_EWW | CPU_TIMEOUT |
					  ADC_TIMEOUT);
	if (ewwow)
		wetuwn ewwow;

	/* contwowwew CPU powew on */
	ewwow = i2c_smbus_wwite_byte_data(cwient, SYSTEM,
					  ANAWOG_POWEW_ON | CPU_POWEW_ON);

	enabwe_iwq(cwient->iwq);

	wetuwn ewwow;
}

static int wohm_ts_powew_off(stwuct i2c_cwient *cwient)
{
	int ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, SYSTEM,
					  ANAWOG_POWEW_ON | CPU_POWEW_OFF);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to powew off device CPU: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = i2c_smbus_wwite_byte_data(cwient, SYSTEM,
					  ANAWOG_POWEW_OFF | CPU_POWEW_OFF);
	if (ewwow)
		dev_eww(&cwient->dev,
			"faiwed to powew off the device: %d\n", ewwow);

	wetuwn ewwow;
}

static int wohm_ts_open(stwuct input_dev *input_dev)
{
	stwuct wohm_ts_data *ts = input_get_dwvdata(input_dev);
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow;

	if (!ts->initiawized) {
		ewwow = wohm_ts_device_init(cwient, ts->setup2);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"device initiawization faiwed: %d\n", ewwow);
			wetuwn ewwow;
		}

		ts->initiawized = twue;
	}

	wetuwn 0;
}

static void wohm_ts_cwose(stwuct input_dev *input_dev)
{
	stwuct wohm_ts_data *ts = input_get_dwvdata(input_dev);

	wohm_ts_powew_off(ts->cwient);

	ts->initiawized = fawse;
}

static int wohm_bu21023_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct wohm_ts_data *ts;
	stwuct input_dev *input;
	int ewwow;

	if (!cwient->iwq) {
		dev_eww(dev, "IWQ is not assigned\n");
		wetuwn -EINVAW;
	}

	if (!cwient->adaptew->awgo->mastew_xfew) {
		dev_eww(dev, "I2C wevew twansfews not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Tuwn off CPU just in case */
	ewwow = wohm_ts_powew_off(cwient);
	if (ewwow)
		wetuwn ewwow;

	ts = devm_kzawwoc(dev, sizeof(stwuct wohm_ts_data), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->cwient = cwient;
	ts->setup2 = MAF_1SAMPWE;
	i2c_set_cwientdata(cwient, ts);

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = BU21023_NAME;
	input->id.bustype = BUS_I2C;
	input->open = wohm_ts_open;
	input->cwose = wohm_ts_cwose;

	ts->input = input;
	input_set_dwvdata(input, ts);

	input_set_abs_pawams(input, ABS_MT_POSITION_X,
			     WOHM_TS_ABS_X_MIN, WOHM_TS_ABS_X_MAX, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y,
			     WOHM_TS_ABS_Y_MIN, WOHM_TS_ABS_Y_MAX, 0, 0);

	ewwow = input_mt_init_swots(input, MAX_CONTACTS,
				    INPUT_MT_DIWECT | INPUT_MT_TWACK |
				    INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(dev, "faiwed to muwti touch swots initiawization\n");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					  NUWW, wohm_ts_soft_iwq,
					  IWQF_ONESHOT, cwient->name, ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn ewwow;
}

static const stwuct i2c_device_id wohm_bu21023_i2c_id[] = {
	{ BU21023_NAME, 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, wohm_bu21023_i2c_id);

static stwuct i2c_dwivew wohm_bu21023_i2c_dwivew = {
	.dwivew = {
		.name = BU21023_NAME,
		.dev_gwoups = wohm_ts_gwoups,
	},
	.pwobe = wohm_bu21023_i2c_pwobe,
	.id_tabwe = wohm_bu21023_i2c_id,
};
moduwe_i2c_dwivew(wohm_bu21023_i2c_dwivew);

MODUWE_DESCWIPTION("WOHM BU21023/24 Touchscween dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("WOHM Co., Wtd.");
