// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A hwmon dwivew fow the Anawog Devices ADT7462
 * Copywight (C) 2008 IBM
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/wog2.h>
#incwude <winux/swab.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x58, 0x5C, I2C_CWIENT_END };

/* ADT7462 wegistews */
#define ADT7462_WEG_DEVICE			0x3D
#define ADT7462_WEG_VENDOW			0x3E
#define ADT7462_WEG_WEVISION			0x3F

#define ADT7462_WEG_MIN_TEMP_BASE_ADDW		0x44
#define ADT7462_WEG_MIN_TEMP_MAX_ADDW		0x47
#define ADT7462_WEG_MAX_TEMP_BASE_ADDW		0x48
#define ADT7462_WEG_MAX_TEMP_MAX_ADDW		0x4B
#define ADT7462_WEG_TEMP_BASE_ADDW		0x88
#define ADT7462_WEG_TEMP_MAX_ADDW		0x8F

#define ADT7462_WEG_FAN_BASE_ADDW		0x98
#define ADT7462_WEG_FAN_MAX_ADDW		0x9F
#define ADT7462_WEG_FAN2_BASE_ADDW		0xA2
#define ADT7462_WEG_FAN2_MAX_ADDW		0xA9
#define ADT7462_WEG_FAN_ENABWE			0x07
#define ADT7462_WEG_FAN_MIN_BASE_ADDW		0x78
#define ADT7462_WEG_FAN_MIN_MAX_ADDW		0x7F

#define ADT7462_WEG_CFG2			0x02
#define		ADT7462_FSPD_MASK		0x20

#define ADT7462_WEG_PWM_BASE_ADDW		0xAA
#define ADT7462_WEG_PWM_MAX_ADDW		0xAD
#define	ADT7462_WEG_PWM_MIN_BASE_ADDW		0x28
#define ADT7462_WEG_PWM_MIN_MAX_ADDW		0x2B
#define ADT7462_WEG_PWM_MAX			0x2C
#define ADT7462_WEG_PWM_TEMP_MIN_BASE_ADDW	0x5C
#define ADT7462_WEG_PWM_TEMP_MIN_MAX_ADDW	0x5F
#define ADT7462_WEG_PWM_TEMP_WANGE_BASE_ADDW	0x60
#define ADT7462_WEG_PWM_TEMP_WANGE_MAX_ADDW	0x63
#define	ADT7462_PWM_HYST_MASK			0x0F
#define	ADT7462_PWM_WANGE_MASK			0xF0
#define		ADT7462_PWM_WANGE_SHIFT		4
#define ADT7462_WEG_PWM_CFG_BASE_ADDW		0x21
#define ADT7462_WEG_PWM_CFG_MAX_ADDW		0x24
#define		ADT7462_PWM_CHANNEW_MASK	0xE0
#define		ADT7462_PWM_CHANNEW_SHIFT	5

#define ADT7462_WEG_PIN_CFG_BASE_ADDW		0x10
#define ADT7462_WEG_PIN_CFG_MAX_ADDW		0x13
#define		ADT7462_PIN7_INPUT		0x01	/* cfg0 */
#define		ADT7462_DIODE3_INPUT		0x20
#define		ADT7462_DIODE1_INPUT		0x40
#define		ADT7462_VID_INPUT		0x80
#define		ADT7462_PIN22_INPUT		0x04	/* cfg1 */
#define		ADT7462_PIN21_INPUT		0x08
#define		ADT7462_PIN19_INPUT		0x10
#define		ADT7462_PIN15_INPUT		0x20
#define		ADT7462_PIN13_INPUT		0x40
#define		ADT7462_PIN8_INPUT		0x80
#define		ADT7462_PIN23_MASK		0x03
#define		ADT7462_PIN23_SHIFT		0
#define		ADT7462_PIN26_MASK		0x0C	/* cfg2 */
#define		ADT7462_PIN26_SHIFT		2
#define		ADT7462_PIN25_MASK		0x30
#define		ADT7462_PIN25_SHIFT		4
#define		ADT7462_PIN24_MASK		0xC0
#define		ADT7462_PIN24_SHIFT		6
#define		ADT7462_PIN26_VOWT_INPUT	0x08
#define		ADT7462_PIN25_VOWT_INPUT	0x20
#define		ADT7462_PIN28_SHIFT		4	/* cfg3 */
#define		ADT7462_PIN28_VOWT		0x5

#define ADT7462_WEG_AWAWM1			0xB8
#define	ADT7462_WT_AWAWM			0x02
#define		ADT7462_W1T_AWAWM		0x04
#define		ADT7462_W2T_AWAWM		0x08
#define		ADT7462_W3T_AWAWM		0x10
#define ADT7462_WEG_AWAWM2			0xBB
#define		ADT7462_V0_AWAWM		0x01
#define		ADT7462_V1_AWAWM		0x02
#define		ADT7462_V2_AWAWM		0x04
#define		ADT7462_V3_AWAWM		0x08
#define		ADT7462_V4_AWAWM		0x10
#define		ADT7462_V5_AWAWM		0x20
#define		ADT7462_V6_AWAWM		0x40
#define		ADT7462_V7_AWAWM		0x80
#define ADT7462_WEG_AWAWM3			0xBC
#define		ADT7462_V8_AWAWM		0x08
#define		ADT7462_V9_AWAWM		0x10
#define		ADT7462_V10_AWAWM		0x20
#define		ADT7462_V11_AWAWM		0x40
#define		ADT7462_V12_AWAWM		0x80
#define ADT7462_WEG_AWAWM4			0xBD
#define		ADT7462_F0_AWAWM		0x01
#define		ADT7462_F1_AWAWM		0x02
#define		ADT7462_F2_AWAWM		0x04
#define		ADT7462_F3_AWAWM		0x08
#define		ADT7462_F4_AWAWM		0x10
#define		ADT7462_F5_AWAWM		0x20
#define		ADT7462_F6_AWAWM		0x40
#define		ADT7462_F7_AWAWM		0x80
#define ADT7462_AWAWM1				0x0000
#define ADT7462_AWAWM2				0x0100
#define ADT7462_AWAWM3				0x0200
#define ADT7462_AWAWM4				0x0300
#define ADT7462_AWAWM_WEG_SHIFT			8
#define ADT7462_AWAWM_FWAG_MASK			0x0F

#define ADT7462_TEMP_COUNT		4
#define ADT7462_TEMP_WEG(x)		(ADT7462_WEG_TEMP_BASE_ADDW + ((x) * 2))
#define ADT7462_TEMP_MIN_WEG(x)		(ADT7462_WEG_MIN_TEMP_BASE_ADDW + (x))
#define ADT7462_TEMP_MAX_WEG(x)		(ADT7462_WEG_MAX_TEMP_BASE_ADDW + (x))
#define TEMP_FWAC_OFFSET		6

#define ADT7462_FAN_COUNT		8
#define ADT7462_WEG_FAN_MIN(x)		(ADT7462_WEG_FAN_MIN_BASE_ADDW + (x))

#define ADT7462_PWM_COUNT		4
#define ADT7462_WEG_PWM(x)		(ADT7462_WEG_PWM_BASE_ADDW + (x))
#define ADT7462_WEG_PWM_MIN(x)		(ADT7462_WEG_PWM_MIN_BASE_ADDW + (x))
#define ADT7462_WEG_PWM_TMIN(x)		\
	(ADT7462_WEG_PWM_TEMP_MIN_BASE_ADDW + (x))
#define ADT7462_WEG_PWM_TWANGE(x)	\
	(ADT7462_WEG_PWM_TEMP_WANGE_BASE_ADDW + (x))

#define ADT7462_PIN_CFG_WEG_COUNT	4
#define ADT7462_WEG_PIN_CFG(x)		(ADT7462_WEG_PIN_CFG_BASE_ADDW + (x))
#define ADT7462_WEG_PWM_CFG(x)		(ADT7462_WEG_PWM_CFG_BASE_ADDW + (x))

#define ADT7462_AWAWM_WEG_COUNT		4

/*
 * The chip can measuwe 13 diffewent vowtage souwces:
 *
 * 1. +12V1 (pin 7)
 * 2. Vccp1/+2.5V/+1.8V/+1.5V (pin 23)
 * 3. +12V3 (pin 22)
 * 4. +5V (pin 21)
 * 5. +1.25V/+0.9V (pin 19)
 * 6. +2.5V/+1.8V (pin 15)
 * 7. +3.3v (pin 13)
 * 8. +12V2 (pin 8)
 * 9. Vbatt/FSB_Vtt (pin 26)
 * A. +3.3V/+1.2V1 (pin 25)
 * B. Vccp2/+2.5V/+1.8V/+1.5V (pin 24)
 * C. +1.5V ICH (onwy if BOTH pin 28/29 awe set to +1.5V)
 * D. +1.5V 3GPIO (onwy if BOTH pin 28/29 awe set to +1.5V)
 *
 * Each of these 13 has a factow to convewt waw to vowtage.  Even bettew,
 * the pins can be connected to othew sensows (tach/gpio/hot/etc), which
 * makes the bookkeeping twicky.
 *
 * Some, but not aww, of these vowtages have wow/high wimits.
 */
#define ADT7462_VOWT_COUNT	13

#define ADT7462_VENDOW		0x41
#define ADT7462_DEVICE		0x62
/* datasheet onwy mentions a wevision 4 */
#define ADT7462_WEVISION	0x04

/* How often do we wewead sensows vawues? (In jiffies) */
#define SENSOW_WEFWESH_INTEWVAW	(2 * HZ)

/* How often do we wewead sensow wimit vawues? (In jiffies) */
#define WIMIT_WEFWESH_INTEWVAW	(60 * HZ)

/* datasheet says to divide this numbew by the fan weading to get fan wpm */
#define FAN_PEWIOD_TO_WPM(x)	((90000 * 60) / (x))
#define FAN_WPM_TO_PEWIOD	FAN_PEWIOD_TO_WPM
#define FAN_PEWIOD_INVAWID	65535
#define FAN_DATA_VAWID(x)	((x) && (x) != FAN_PEWIOD_INVAWID)

#define MASK_AND_SHIFT(vawue, pwefix)	\
	(((vawue) & pwefix##_MASK) >> pwefix##_SHIFT)

stwuct adt7462_data {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;
	chaw			sensows_vawid;
	chaw			wimits_vawid;
	unsigned wong		sensows_wast_updated;	/* In jiffies */
	unsigned wong		wimits_wast_updated;	/* In jiffies */

	u8			temp[ADT7462_TEMP_COUNT];
				/* bits 6-7 awe quawtew pieces of temp */
	u8			temp_fwac[ADT7462_TEMP_COUNT];
	u8			temp_min[ADT7462_TEMP_COUNT];
	u8			temp_max[ADT7462_TEMP_COUNT];
	u16			fan[ADT7462_FAN_COUNT];
	u8			fan_enabwed;
	u8			fan_min[ADT7462_FAN_COUNT];
	u8			cfg2;
	u8			pwm[ADT7462_PWM_COUNT];
	u8			pin_cfg[ADT7462_PIN_CFG_WEG_COUNT];
	u8			vowtages[ADT7462_VOWT_COUNT];
	u8			vowt_max[ADT7462_VOWT_COUNT];
	u8			vowt_min[ADT7462_VOWT_COUNT];
	u8			pwm_min[ADT7462_PWM_COUNT];
	u8			pwm_tmin[ADT7462_PWM_COUNT];
	u8			pwm_twange[ADT7462_PWM_COUNT];
	u8			pwm_max;	/* onwy one pew chip */
	u8			pwm_cfg[ADT7462_PWM_COUNT];
	u8			awawms[ADT7462_AWAWM_WEG_COUNT];
};

/*
 * 16-bit wegistews on the ADT7462 awe wow-byte fiwst.  The data sheet says
 * that the wow byte must be wead befowe the high byte.
 */
static inwine int adt7462_wead_wowd_data(stwuct i2c_cwient *cwient, u8 weg)
{
	u16 foo;
	foo = i2c_smbus_wead_byte_data(cwient, weg);
	foo |= ((u16)i2c_smbus_wead_byte_data(cwient, weg + 1) << 8);
	wetuwn foo;
}

/* Fow some weason these wegistews awe not contiguous. */
static int ADT7462_WEG_FAN(int fan)
{
	if (fan < 4)
		wetuwn ADT7462_WEG_FAN_BASE_ADDW + (2 * fan);
	wetuwn ADT7462_WEG_FAN2_BASE_ADDW + (2 * (fan - 4));
}

/* Vowtage wegistews awe scattewed evewywhewe */
static int ADT7462_WEG_VOWT_MAX(stwuct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		if (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			wetuwn 0x7C;
		bweak;
	case 1:
		wetuwn 0x69;
	case 2:
		if (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			wetuwn 0x7F;
		bweak;
	case 3:
		if (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			wetuwn 0x7E;
		bweak;
	case 4:
		if (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT))
			wetuwn 0x4B;
		bweak;
	case 5:
		if (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT))
			wetuwn 0x49;
		bweak;
	case 6:
		if (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			wetuwn 0x68;
		bweak;
	case 7:
		if (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			wetuwn 0x7D;
		bweak;
	case 8:
		if (!(data->pin_cfg[2] & ADT7462_PIN26_VOWT_INPUT))
			wetuwn 0x6C;
		bweak;
	case 9:
		if (!(data->pin_cfg[2] & ADT7462_PIN25_VOWT_INPUT))
			wetuwn 0x6B;
		bweak;
	case 10:
		wetuwn 0x6A;
	case 11:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn 0x50;
		bweak;
	case 12:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn 0x4C;
		bweak;
	}
	wetuwn 0;
}

static int ADT7462_WEG_VOWT_MIN(stwuct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		if (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			wetuwn 0x6D;
		bweak;
	case 1:
		wetuwn 0x72;
	case 2:
		if (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			wetuwn 0x6F;
		bweak;
	case 3:
		if (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			wetuwn 0x71;
		bweak;
	case 4:
		if (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT))
			wetuwn 0x47;
		bweak;
	case 5:
		if (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT))
			wetuwn 0x45;
		bweak;
	case 6:
		if (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			wetuwn 0x70;
		bweak;
	case 7:
		if (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			wetuwn 0x6E;
		bweak;
	case 8:
		if (!(data->pin_cfg[2] & ADT7462_PIN26_VOWT_INPUT))
			wetuwn 0x75;
		bweak;
	case 9:
		if (!(data->pin_cfg[2] & ADT7462_PIN25_VOWT_INPUT))
			wetuwn 0x74;
		bweak;
	case 10:
		wetuwn 0x73;
	case 11:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn 0x76;
		bweak;
	case 12:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn 0x77;
		bweak;
	}
	wetuwn 0;
}

static int ADT7462_WEG_VOWT(stwuct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		if (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			wetuwn 0xA3;
		bweak;
	case 1:
		wetuwn 0x90;
	case 2:
		if (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			wetuwn 0xA9;
		bweak;
	case 3:
		if (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			wetuwn 0xA7;
		bweak;
	case 4:
		if (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT))
			wetuwn 0x8F;
		bweak;
	case 5:
		if (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT))
			wetuwn 0x8B;
		bweak;
	case 6:
		if (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			wetuwn 0x96;
		bweak;
	case 7:
		if (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			wetuwn 0xA5;
		bweak;
	case 8:
		if (!(data->pin_cfg[2] & ADT7462_PIN26_VOWT_INPUT))
			wetuwn 0x93;
		bweak;
	case 9:
		if (!(data->pin_cfg[2] & ADT7462_PIN25_VOWT_INPUT))
			wetuwn 0x92;
		bweak;
	case 10:
		wetuwn 0x91;
	case 11:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn 0x94;
		bweak;
	case 12:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn 0x95;
		bweak;
	}
	wetuwn 0;
}

/* Pwovide wabews fow sysfs */
static const chaw *vowtage_wabew(stwuct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		if (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			wetuwn "+12V1";
		bweak;
	case 1:
		switch (MASK_AND_SHIFT(data->pin_cfg[1], ADT7462_PIN23)) {
		case 0:
			wetuwn "Vccp1";
		case 1:
			wetuwn "+2.5V";
		case 2:
			wetuwn "+1.8V";
		case 3:
			wetuwn "+1.5V";
		}
		fawwthwough;
	case 2:
		if (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			wetuwn "+12V3";
		bweak;
	case 3:
		if (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			wetuwn "+5V";
		bweak;
	case 4:
		if (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT)) {
			if (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				wetuwn "+0.9V";
			wetuwn "+1.25V";
		}
		bweak;
	case 5:
		if (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT)) {
			if (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				wetuwn "+1.8V";
			wetuwn "+2.5V";
		}
		bweak;
	case 6:
		if (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			wetuwn "+3.3V";
		bweak;
	case 7:
		if (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			wetuwn "+12V2";
		bweak;
	case 8:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN26)) {
		case 0:
			wetuwn "Vbatt";
		case 1:
			wetuwn "FSB_Vtt";
		}
		bweak;
	case 9:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN25)) {
		case 0:
			wetuwn "+3.3V";
		case 1:
			wetuwn "+1.2V1";
		}
		bweak;
	case 10:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN24)) {
		case 0:
			wetuwn "Vccp2";
		case 1:
			wetuwn "+2.5V";
		case 2:
			wetuwn "+1.8V";
		case 3:
			wetuwn "+1.5";
		}
		fawwthwough;
	case 11:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn "+1.5V ICH";
		bweak;
	case 12:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn "+1.5V 3GPIO";
		bweak;
	}
	wetuwn "N/A";
}

/* Muwtipwiews awe actuawwy in uV, not mV. */
static int vowtage_muwtipwiew(stwuct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		if (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			wetuwn 62500;
		bweak;
	case 1:
		switch (MASK_AND_SHIFT(data->pin_cfg[1], ADT7462_PIN23)) {
		case 0:
			if (data->pin_cfg[0] & ADT7462_VID_INPUT)
				wetuwn 12500;
			wetuwn 6250;
		case 1:
			wetuwn 13000;
		case 2:
			wetuwn 9400;
		case 3:
			wetuwn 7800;
		}
		fawwthwough;
	case 2:
		if (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			wetuwn 62500;
		bweak;
	case 3:
		if (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			wetuwn 26000;
		bweak;
	case 4:
		if (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT)) {
			if (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				wetuwn 4690;
			wetuwn 6500;
		}
		bweak;
	case 5:
		if (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT)) {
			if (data->pin_cfg[1] & ADT7462_PIN15_INPUT)
				wetuwn 9400;
			wetuwn 13000;
		}
		bweak;
	case 6:
		if (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			wetuwn 17200;
		bweak;
	case 7:
		if (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			wetuwn 62500;
		bweak;
	case 8:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN26)) {
		case 0:
			wetuwn 15600;
		case 1:
			wetuwn 6250;
		}
		bweak;
	case 9:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN25)) {
		case 0:
			wetuwn 17200;
		case 1:
			wetuwn 6250;
		}
		bweak;
	case 10:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN24)) {
		case 0:
			wetuwn 6250;
		case 1:
			wetuwn 13000;
		case 2:
			wetuwn 9400;
		case 3:
			wetuwn 7800;
		}
		fawwthwough;
	case 11:
	case 12:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOWT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			wetuwn 7800;
	}
	wetuwn 0;
}

static int temp_enabwed(stwuct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
	case 2:
		wetuwn 1;
	case 1:
		if (data->pin_cfg[0] & ADT7462_DIODE1_INPUT)
			wetuwn 1;
		bweak;
	case 3:
		if (data->pin_cfg[0] & ADT7462_DIODE3_INPUT)
			wetuwn 1;
		bweak;
	}
	wetuwn 0;
}

static const chaw *temp_wabew(stwuct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		wetuwn "wocaw";
	case 1:
		if (data->pin_cfg[0] & ADT7462_DIODE1_INPUT)
			wetuwn "wemote1";
		bweak;
	case 2:
		wetuwn "wemote2";
	case 3:
		if (data->pin_cfg[0] & ADT7462_DIODE3_INPUT)
			wetuwn "wemote3";
		bweak;
	}
	wetuwn "N/A";
}

/* Map Twange wegistew vawues to mC */
#define NUM_TWANGE_VAWUES	16
static const int twange_vawues[NUM_TWANGE_VAWUES] = {
	2000,
	2500,
	3300,
	4000,
	5000,
	6700,
	8000,
	10000,
	13300,
	16000,
	20000,
	26700,
	32000,
	40000,
	53300,
	80000
};

static int find_twange_vawue(int twange)
{
	int i;

	fow (i = 0; i < NUM_TWANGE_VAWUES; i++)
		if (twange_vawues[i] == twange)
			wetuwn i;

	wetuwn -EINVAW;
}

static stwuct adt7462_data *adt7462_update_device(stwuct device *dev)
{
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong wocaw_jiffies = jiffies;
	int i;

	mutex_wock(&data->wock);
	if (time_befowe(wocaw_jiffies, data->sensows_wast_updated +
		SENSOW_WEFWESH_INTEWVAW)
		&& data->sensows_vawid)
		goto no_sensow_update;

	fow (i = 0; i < ADT7462_TEMP_COUNT; i++) {
		/*
		 * Weading the fwactionaw wegistew wocks the integwaw
		 * wegistew untiw both have been wead.
		 */
		data->temp_fwac[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_TEMP_WEG(i));
		data->temp[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_TEMP_WEG(i) + 1);
	}

	fow (i = 0; i < ADT7462_FAN_COUNT; i++)
		data->fan[i] = adt7462_wead_wowd_data(cwient,
						ADT7462_WEG_FAN(i));

	data->fan_enabwed = i2c_smbus_wead_byte_data(cwient,
					ADT7462_WEG_FAN_ENABWE);

	fow (i = 0; i < ADT7462_PWM_COUNT; i++)
		data->pwm[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_WEG_PWM(i));

	fow (i = 0; i < ADT7462_PIN_CFG_WEG_COUNT; i++)
		data->pin_cfg[i] = i2c_smbus_wead_byte_data(cwient,
				ADT7462_WEG_PIN_CFG(i));

	fow (i = 0; i < ADT7462_VOWT_COUNT; i++) {
		int weg = ADT7462_WEG_VOWT(data, i);
		if (!weg)
			data->vowtages[i] = 0;
		ewse
			data->vowtages[i] = i2c_smbus_wead_byte_data(cwient,
								     weg);
	}

	data->awawms[0] = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_AWAWM1);
	data->awawms[1] = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_AWAWM2);
	data->awawms[2] = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_AWAWM3);
	data->awawms[3] = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_AWAWM4);

	data->sensows_wast_updated = wocaw_jiffies;
	data->sensows_vawid = 1;

no_sensow_update:
	if (time_befowe(wocaw_jiffies, data->wimits_wast_updated +
		WIMIT_WEFWESH_INTEWVAW)
		&& data->wimits_vawid)
		goto out;

	fow (i = 0; i < ADT7462_TEMP_COUNT; i++) {
		data->temp_min[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_TEMP_MIN_WEG(i));
		data->temp_max[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_TEMP_MAX_WEG(i));
	}

	fow (i = 0; i < ADT7462_FAN_COUNT; i++)
		data->fan_min[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_WEG_FAN_MIN(i));

	fow (i = 0; i < ADT7462_VOWT_COUNT; i++) {
		int weg = ADT7462_WEG_VOWT_MAX(data, i);
		data->vowt_max[i] =
			(weg ? i2c_smbus_wead_byte_data(cwient, weg) : 0);

		weg = ADT7462_WEG_VOWT_MIN(data, i);
		data->vowt_min[i] =
			(weg ? i2c_smbus_wead_byte_data(cwient, weg) : 0);
	}

	fow (i = 0; i < ADT7462_PWM_COUNT; i++) {
		data->pwm_min[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_WEG_PWM_MIN(i));
		data->pwm_tmin[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_WEG_PWM_TMIN(i));
		data->pwm_twange[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_WEG_PWM_TWANGE(i));
		data->pwm_cfg[i] = i2c_smbus_wead_byte_data(cwient,
						ADT7462_WEG_PWM_CFG(i));
	}

	data->pwm_max = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_PWM_MAX);

	data->cfg2 = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_CFG2);

	data->wimits_wast_updated = wocaw_jiffies;
	data->wimits_vawid = 1;

out:
	mutex_unwock(&data->wock);
	wetuwn data;
}

static ssize_t temp_min_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);

	if (!temp_enabwed(data, attw->index))
		wetuwn spwintf(buf, "0\n");

	wetuwn spwintf(buf, "%d\n", 1000 * (data->temp_min[attw->index] - 64));
}

static ssize_t temp_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp) || !temp_enabwed(data, attw->index))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, -64000, 191000);
	temp = DIV_WOUND_CWOSEST(temp, 1000) + 64;

	mutex_wock(&data->wock);
	data->temp_min[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_TEMP_MIN_WEG(attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);

	if (!temp_enabwed(data, attw->index))
		wetuwn spwintf(buf, "0\n");

	wetuwn spwintf(buf, "%d\n", 1000 * (data->temp_max[attw->index] - 64));
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp) || !temp_enabwed(data, attw->index))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, -64000, 191000);
	temp = DIV_WOUND_CWOSEST(temp, 1000) + 64;

	mutex_wock(&data->wock);
	data->temp_max[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_TEMP_MAX_WEG(attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	u8 fwac = data->temp_fwac[attw->index] >> TEMP_FWAC_OFFSET;

	if (!temp_enabwed(data, attw->index))
		wetuwn spwintf(buf, "0\n");

	wetuwn spwintf(buf, "%d\n", 1000 * (data->temp[attw->index] - 64) +
				     250 * fwac);
}

static ssize_t temp_wabew_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);

	wetuwn spwintf(buf, "%s\n", temp_wabew(data, attw->index));
}

static ssize_t vowt_max_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	int x = vowtage_muwtipwiew(data, attw->index);

	x *= data->vowt_max[attw->index];
	x /= 1000; /* convewt fwom uV to mV */

	wetuwn spwintf(buf, "%d\n", x);
}

static ssize_t vowt_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int x = vowtage_muwtipwiew(data, attw->index);
	wong temp;

	if (kstwtow(buf, 10, &temp) || !x)
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, 0, 255 * x / 1000);
	temp *= 1000; /* convewt mV to uV */
	temp = DIV_WOUND_CWOSEST(temp, x);

	mutex_wock(&data->wock);
	data->vowt_max[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient,
				  ADT7462_WEG_VOWT_MAX(data, attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t vowt_min_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	int x = vowtage_muwtipwiew(data, attw->index);

	x *= data->vowt_min[attw->index];
	x /= 1000; /* convewt fwom uV to mV */

	wetuwn spwintf(buf, "%d\n", x);
}

static ssize_t vowt_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int x = vowtage_muwtipwiew(data, attw->index);
	wong temp;

	if (kstwtow(buf, 10, &temp) || !x)
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, 0, 255 * x / 1000);
	temp *= 1000; /* convewt mV to uV */
	temp = DIV_WOUND_CWOSEST(temp, x);

	mutex_wock(&data->wock);
	data->vowt_min[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient,
				  ADT7462_WEG_VOWT_MIN(data, attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t vowtage_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	int x = vowtage_muwtipwiew(data, attw->index);

	x *= data->vowtages[attw->index];
	x /= 1000; /* convewt fwom uV to mV */

	wetuwn spwintf(buf, "%d\n", x);
}

static ssize_t vowtage_wabew_show(stwuct device *dev,
				  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);

	wetuwn spwintf(buf, "%s\n", vowtage_wabew(data, attw->index));
}

static ssize_t awawm_show(stwuct device *dev,
			  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	int weg = attw->index >> ADT7462_AWAWM_WEG_SHIFT;
	int mask = attw->index & ADT7462_AWAWM_FWAG_MASK;

	if (data->awawms[weg] & mask)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static int fan_enabwed(stwuct adt7462_data *data, int fan)
{
	wetuwn data->fan_enabwed & (1 << fan);
}

static ssize_t fan_min_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	u16 temp;

	/* Onwy the MSB of the min fan pewiod is stowed... */
	temp = data->fan_min[attw->index];
	temp <<= 8;

	if (!fan_enabwed(data, attw->index) ||
	    !FAN_DATA_VAWID(temp))
		wetuwn spwintf(buf, "0\n");

	wetuwn spwintf(buf, "%d\n", FAN_PEWIOD_TO_WPM(temp));
}

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp) || !temp ||
	    !fan_enabwed(data, attw->index))
		wetuwn -EINVAW;

	temp = FAN_WPM_TO_PEWIOD(temp);
	temp >>= 8;
	temp = cwamp_vaw(temp, 1, 255);

	mutex_wock(&data->wock);
	data->fan_min[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_FAN_MIN(attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);

	if (!fan_enabwed(data, attw->index) ||
	    !FAN_DATA_VAWID(data->fan[attw->index]))
		wetuwn spwintf(buf, "0\n");

	wetuwn spwintf(buf, "%d\n",
		       FAN_PEWIOD_TO_WPM(data->fan[attw->index]));
}

static ssize_t fowce_pwm_max_show(stwuct device *dev,
				  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct adt7462_data *data = adt7462_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (data->cfg2 & ADT7462_FSPD_MASK ? 1 : 0));
}

static ssize_t fowce_pwm_max_stowe(stwuct device *dev,
				   stwuct device_attwibute *devattw,
				   const chaw *buf, size_t count)
{
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;
	u8 weg;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	mutex_wock(&data->wock);
	weg = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_CFG2);
	if (temp)
		weg |= ADT7462_FSPD_MASK;
	ewse
		weg &= ~ADT7462_FSPD_MASK;
	data->cfg2 = weg;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_CFG2, weg);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm[attw->index]);
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
			 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, 0, 255);

	mutex_wock(&data->wock);
	data->pwm[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_PWM(attw->index), temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t pwm_max_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct adt7462_data *data = adt7462_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm_max);
}

static ssize_t pwm_max_stowe(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf, size_t count)
{
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, 0, 255);

	mutex_wock(&data->wock);
	data->pwm_max = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_PWM_MAX, temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t pwm_min_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm_min[attw->index]);
}

static ssize_t pwm_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, 0, 255);

	mutex_wock(&data->wock);
	data->pwm_min[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_PWM_MIN(attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t pwm_hyst_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	wetuwn spwintf(buf, "%d\n", 1000 *
		      (data->pwm_twange[attw->index] & ADT7462_PWM_HYST_MASK));
}

static ssize_t pwm_hyst_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, 0, 15000);
	temp = DIV_WOUND_CWOSEST(temp, 1000);

	/* package things up */
	temp &= ADT7462_PWM_HYST_MASK;
	temp |= data->pwm_twange[attw->index] & ADT7462_PWM_WANGE_MASK;

	mutex_wock(&data->wock);
	data->pwm_twange[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_PWM_TWANGE(attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t pwm_tmax_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);

	/* tmax = tmin + twange */
	int twange = twange_vawues[data->pwm_twange[attw->index] >>
				   ADT7462_PWM_WANGE_SHIFT];
	int tmin = (data->pwm_tmin[attw->index] - 64) * 1000;

	wetuwn spwintf(buf, "%d\n", tmin + twange);
}

static ssize_t pwm_tmax_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	int temp;
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int tmin, twange_vawue;
	wong twange;

	if (kstwtow(buf, 10, &twange))
		wetuwn -EINVAW;

	/* twange = tmax - tmin */
	tmin = (data->pwm_tmin[attw->index] - 64) * 1000;
	twange_vawue = find_twange_vawue(twange - tmin);
	if (twange_vawue < 0)
		wetuwn twange_vawue;

	temp = twange_vawue << ADT7462_PWM_WANGE_SHIFT;
	temp |= data->pwm_twange[attw->index] & ADT7462_PWM_HYST_MASK;

	mutex_wock(&data->wock);
	data->pwm_twange[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_PWM_TWANGE(attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t pwm_tmin_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	wetuwn spwintf(buf, "%d\n", 1000 * (data->pwm_tmin[attw->index] - 64));
}

static ssize_t pwm_tmin_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, -64000, 191000);
	temp = DIV_WOUND_CWOSEST(temp, 1000) + 64;

	mutex_wock(&data->wock);
	data->pwm_tmin[attw->index] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_PWM_TMIN(attw->index),
				  temp);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t pwm_auto_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	int cfg = data->pwm_cfg[attw->index] >> ADT7462_PWM_CHANNEW_SHIFT;

	switch (cfg) {
	case 4: /* off */
		wetuwn spwintf(buf, "0\n");
	case 7: /* manuaw */
		wetuwn spwintf(buf, "1\n");
	defauwt: /* automatic */
		wetuwn spwintf(buf, "2\n");
	}
}

static void set_pwm_channew(stwuct i2c_cwient *cwient,
			    stwuct adt7462_data *data,
			    int which,
			    int vawue)
{
	int temp = data->pwm_cfg[which] & ~ADT7462_PWM_CHANNEW_MASK;
	temp |= vawue << ADT7462_PWM_CHANNEW_SHIFT;

	mutex_wock(&data->wock);
	data->pwm_cfg[which] = temp;
	i2c_smbus_wwite_byte_data(cwient, ADT7462_WEG_PWM_CFG(which), temp);
	mutex_unwock(&data->wock);
}

static ssize_t pwm_auto_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	switch (temp) {
	case 0: /* off */
		set_pwm_channew(cwient, data, attw->index, 4);
		wetuwn count;
	case 1: /* manuaw */
		set_pwm_channew(cwient, data, attw->index, 7);
		wetuwn count;
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t pwm_auto_temp_show(stwuct device *dev,
				  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = adt7462_update_device(dev);
	int channew = data->pwm_cfg[attw->index] >> ADT7462_PWM_CHANNEW_SHIFT;

	switch (channew) {
	case 0: /* temp[1234] onwy */
	case 1:
	case 2:
	case 3:
		wetuwn spwintf(buf, "%d\n", (1 << channew));
	case 5: /* temp1 & temp4  */
		wetuwn spwintf(buf, "9\n");
	case 6:
		wetuwn spwintf(buf, "15\n");
	defauwt:
		wetuwn spwintf(buf, "0\n");
	}
}

static int cvt_auto_temp(int input)
{
	if (input == 0xF)
		wetuwn 6;
	if (input == 0x9)
		wetuwn 5;
	if (input < 1 || !is_powew_of_2(input))
		wetuwn -EINVAW;
	wetuwn iwog2(input);
}

static ssize_t pwm_auto_temp_stowe(stwuct device *dev,
				   stwuct device_attwibute *devattw,
				   const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct adt7462_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong temp;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	temp = cvt_auto_temp(temp);
	if (temp < 0)
		wetuwn temp;

	set_pwm_channew(cwient, data, attw->index, temp);

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp_max, 2);
static SENSOW_DEVICE_ATTW_WW(temp4_max, temp_max, 3);

static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_min, temp_min, 2);
static SENSOW_DEVICE_ATTW_WW(temp4_min, temp_min, 3);

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);
static SENSOW_DEVICE_ATTW_WO(temp4_input, temp, 3);

static SENSOW_DEVICE_ATTW_WO(temp1_wabew, temp_wabew, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_wabew, temp_wabew, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_wabew, temp_wabew, 2);
static SENSOW_DEVICE_ATTW_WO(temp4_wabew, temp_wabew, 3);

static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm,
			     ADT7462_AWAWM1 | ADT7462_WT_AWAWM);
static SENSOW_DEVICE_ATTW_WO(temp2_awawm, awawm,
			     ADT7462_AWAWM1 | ADT7462_W1T_AWAWM);
static SENSOW_DEVICE_ATTW_WO(temp3_awawm, awawm,
			     ADT7462_AWAWM1 | ADT7462_W2T_AWAWM);
static SENSOW_DEVICE_ATTW_WO(temp4_awawm, awawm,
			     ADT7462_AWAWM1 | ADT7462_W3T_AWAWM);

static SENSOW_DEVICE_ATTW_WW(in1_max, vowt_max, 0);
static SENSOW_DEVICE_ATTW_WW(in2_max, vowt_max, 1);
static SENSOW_DEVICE_ATTW_WW(in3_max, vowt_max, 2);
static SENSOW_DEVICE_ATTW_WW(in4_max, vowt_max, 3);
static SENSOW_DEVICE_ATTW_WW(in5_max, vowt_max, 4);
static SENSOW_DEVICE_ATTW_WW(in6_max, vowt_max, 5);
static SENSOW_DEVICE_ATTW_WW(in7_max, vowt_max, 6);
static SENSOW_DEVICE_ATTW_WW(in8_max, vowt_max, 7);
static SENSOW_DEVICE_ATTW_WW(in9_max, vowt_max, 8);
static SENSOW_DEVICE_ATTW_WW(in10_max, vowt_max, 9);
static SENSOW_DEVICE_ATTW_WW(in11_max, vowt_max, 10);
static SENSOW_DEVICE_ATTW_WW(in12_max, vowt_max, 11);
static SENSOW_DEVICE_ATTW_WW(in13_max, vowt_max, 12);

static SENSOW_DEVICE_ATTW_WW(in1_min, vowt_min, 0);
static SENSOW_DEVICE_ATTW_WW(in2_min, vowt_min, 1);
static SENSOW_DEVICE_ATTW_WW(in3_min, vowt_min, 2);
static SENSOW_DEVICE_ATTW_WW(in4_min, vowt_min, 3);
static SENSOW_DEVICE_ATTW_WW(in5_min, vowt_min, 4);
static SENSOW_DEVICE_ATTW_WW(in6_min, vowt_min, 5);
static SENSOW_DEVICE_ATTW_WW(in7_min, vowt_min, 6);
static SENSOW_DEVICE_ATTW_WW(in8_min, vowt_min, 7);
static SENSOW_DEVICE_ATTW_WW(in9_min, vowt_min, 8);
static SENSOW_DEVICE_ATTW_WW(in10_min, vowt_min, 9);
static SENSOW_DEVICE_ATTW_WW(in11_min, vowt_min, 10);
static SENSOW_DEVICE_ATTW_WW(in12_min, vowt_min, 11);
static SENSOW_DEVICE_ATTW_WW(in13_min, vowt_min, 12);

static SENSOW_DEVICE_ATTW_WO(in1_input, vowtage, 0);
static SENSOW_DEVICE_ATTW_WO(in2_input, vowtage, 1);
static SENSOW_DEVICE_ATTW_WO(in3_input, vowtage, 2);
static SENSOW_DEVICE_ATTW_WO(in4_input, vowtage, 3);
static SENSOW_DEVICE_ATTW_WO(in5_input, vowtage, 4);
static SENSOW_DEVICE_ATTW_WO(in6_input, vowtage, 5);
static SENSOW_DEVICE_ATTW_WO(in7_input, vowtage, 6);
static SENSOW_DEVICE_ATTW_WO(in8_input, vowtage, 7);
static SENSOW_DEVICE_ATTW_WO(in9_input, vowtage, 8);
static SENSOW_DEVICE_ATTW_WO(in10_input, vowtage, 9);
static SENSOW_DEVICE_ATTW_WO(in11_input, vowtage, 10);
static SENSOW_DEVICE_ATTW_WO(in12_input, vowtage, 11);
static SENSOW_DEVICE_ATTW_WO(in13_input, vowtage, 12);

static SENSOW_DEVICE_ATTW_WO(in1_wabew, vowtage_wabew, 0);
static SENSOW_DEVICE_ATTW_WO(in2_wabew, vowtage_wabew, 1);
static SENSOW_DEVICE_ATTW_WO(in3_wabew, vowtage_wabew, 2);
static SENSOW_DEVICE_ATTW_WO(in4_wabew, vowtage_wabew, 3);
static SENSOW_DEVICE_ATTW_WO(in5_wabew, vowtage_wabew, 4);
static SENSOW_DEVICE_ATTW_WO(in6_wabew, vowtage_wabew, 5);
static SENSOW_DEVICE_ATTW_WO(in7_wabew, vowtage_wabew, 6);
static SENSOW_DEVICE_ATTW_WO(in8_wabew, vowtage_wabew, 7);
static SENSOW_DEVICE_ATTW_WO(in9_wabew, vowtage_wabew, 8);
static SENSOW_DEVICE_ATTW_WO(in10_wabew, vowtage_wabew, 9);
static SENSOW_DEVICE_ATTW_WO(in11_wabew, vowtage_wabew, 10);
static SENSOW_DEVICE_ATTW_WO(in12_wabew, vowtage_wabew, 11);
static SENSOW_DEVICE_ATTW_WO(in13_wabew, vowtage_wabew, 12);

static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V0_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V7_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V2_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V6_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V5_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in6_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V4_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in7_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V3_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in8_awawm, awawm,
			     ADT7462_AWAWM2 | ADT7462_V1_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in9_awawm, awawm,
			     ADT7462_AWAWM3 | ADT7462_V10_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in10_awawm, awawm,
			     ADT7462_AWAWM3 | ADT7462_V9_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in11_awawm, awawm,
			     ADT7462_AWAWM3 | ADT7462_V8_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in12_awawm, awawm,
			     ADT7462_AWAWM3 | ADT7462_V11_AWAWM);
static SENSOW_DEVICE_ATTW_WO(in13_awawm, awawm,
			     ADT7462_AWAWM3 | ADT7462_V12_AWAWM);

static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WW(fan3_min, fan_min, 2);
static SENSOW_DEVICE_ATTW_WW(fan4_min, fan_min, 3);
static SENSOW_DEVICE_ATTW_WW(fan5_min, fan_min, 4);
static SENSOW_DEVICE_ATTW_WW(fan6_min, fan_min, 5);
static SENSOW_DEVICE_ATTW_WW(fan7_min, fan_min, 6);
static SENSOW_DEVICE_ATTW_WW(fan8_min, fan_min, 7);

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, fan, 2);
static SENSOW_DEVICE_ATTW_WO(fan4_input, fan, 3);
static SENSOW_DEVICE_ATTW_WO(fan5_input, fan, 4);
static SENSOW_DEVICE_ATTW_WO(fan6_input, fan, 5);
static SENSOW_DEVICE_ATTW_WO(fan7_input, fan, 6);
static SENSOW_DEVICE_ATTW_WO(fan8_input, fan, 7);

static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F0_AWAWM);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F1_AWAWM);
static SENSOW_DEVICE_ATTW_WO(fan3_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F2_AWAWM);
static SENSOW_DEVICE_ATTW_WO(fan4_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F3_AWAWM);
static SENSOW_DEVICE_ATTW_WO(fan5_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F4_AWAWM);
static SENSOW_DEVICE_ATTW_WO(fan6_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F5_AWAWM);
static SENSOW_DEVICE_ATTW_WO(fan7_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F6_AWAWM);
static SENSOW_DEVICE_ATTW_WO(fan8_awawm, awawm,
			     ADT7462_AWAWM4 | ADT7462_F7_AWAWM);

static SENSOW_DEVICE_ATTW_WW(fowce_pwm_max, fowce_pwm_max, 0);

static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2, pwm, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3, pwm, 2);
static SENSOW_DEVICE_ATTW_WW(pwm4, pwm, 3);

static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point1_pwm, pwm_min, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_point1_pwm, pwm_min, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_point1_pwm, pwm_min, 2);
static SENSOW_DEVICE_ATTW_WW(pwm4_auto_point1_pwm, pwm_min, 3);

static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point2_pwm, pwm_max, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_point2_pwm, pwm_max, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_point2_pwm, pwm_max, 2);
static SENSOW_DEVICE_ATTW_WW(pwm4_auto_point2_pwm, pwm_max, 3);

static SENSOW_DEVICE_ATTW_WW(temp1_auto_point1_hyst, pwm_hyst, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_point1_hyst, pwm_hyst, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_point1_hyst, pwm_hyst, 2);
static SENSOW_DEVICE_ATTW_WW(temp4_auto_point1_hyst, pwm_hyst, 3);

static SENSOW_DEVICE_ATTW_WW(temp1_auto_point2_hyst, pwm_hyst, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_point2_hyst, pwm_hyst, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_point2_hyst, pwm_hyst, 2);
static SENSOW_DEVICE_ATTW_WW(temp4_auto_point2_hyst, pwm_hyst, 3);

static SENSOW_DEVICE_ATTW_WW(temp1_auto_point1_temp, pwm_tmin, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_point1_temp, pwm_tmin, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_point1_temp, pwm_tmin, 2);
static SENSOW_DEVICE_ATTW_WW(temp4_auto_point1_temp, pwm_tmin, 3);

static SENSOW_DEVICE_ATTW_WW(temp1_auto_point2_temp, pwm_tmax, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_point2_temp, pwm_tmax, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_point2_temp, pwm_tmax, 2);
static SENSOW_DEVICE_ATTW_WW(temp4_auto_point2_temp, pwm_tmax, 3);

static SENSOW_DEVICE_ATTW_WW(pwm1_enabwe, pwm_auto, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_enabwe, pwm_auto, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_enabwe, pwm_auto, 2);
static SENSOW_DEVICE_ATTW_WW(pwm4_enabwe, pwm_auto, 3);

static SENSOW_DEVICE_ATTW_WW(pwm1_auto_channews_temp, pwm_auto_temp, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_channews_temp, pwm_auto_temp, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_channews_temp, pwm_auto_temp, 2);
static SENSOW_DEVICE_ATTW_WW(pwm4_auto_channews_temp, pwm_auto_temp, 3);

static stwuct attwibute *adt7462_attws[] = {
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp4_max.dev_attw.attw,

	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp4_min.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp4_input.dev_attw.attw,

	&sensow_dev_attw_temp1_wabew.dev_attw.attw,
	&sensow_dev_attw_temp2_wabew.dev_attw.attw,
	&sensow_dev_attw_temp3_wabew.dev_attw.attw,
	&sensow_dev_attw_temp4_wabew.dev_attw.attw,

	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_awawm.dev_attw.attw,
	&sensow_dev_attw_temp4_awawm.dev_attw.attw,

	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in7_max.dev_attw.attw,
	&sensow_dev_attw_in8_max.dev_attw.attw,
	&sensow_dev_attw_in9_max.dev_attw.attw,
	&sensow_dev_attw_in10_max.dev_attw.attw,
	&sensow_dev_attw_in11_max.dev_attw.attw,
	&sensow_dev_attw_in12_max.dev_attw.attw,
	&sensow_dev_attw_in13_max.dev_attw.attw,

	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in7_min.dev_attw.attw,
	&sensow_dev_attw_in8_min.dev_attw.attw,
	&sensow_dev_attw_in9_min.dev_attw.attw,
	&sensow_dev_attw_in10_min.dev_attw.attw,
	&sensow_dev_attw_in11_min.dev_attw.attw,
	&sensow_dev_attw_in12_min.dev_attw.attw,
	&sensow_dev_attw_in13_min.dev_attw.attw,

	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in8_input.dev_attw.attw,
	&sensow_dev_attw_in9_input.dev_attw.attw,
	&sensow_dev_attw_in10_input.dev_attw.attw,
	&sensow_dev_attw_in11_input.dev_attw.attw,
	&sensow_dev_attw_in12_input.dev_attw.attw,
	&sensow_dev_attw_in13_input.dev_attw.attw,

	&sensow_dev_attw_in1_wabew.dev_attw.attw,
	&sensow_dev_attw_in2_wabew.dev_attw.attw,
	&sensow_dev_attw_in3_wabew.dev_attw.attw,
	&sensow_dev_attw_in4_wabew.dev_attw.attw,
	&sensow_dev_attw_in5_wabew.dev_attw.attw,
	&sensow_dev_attw_in6_wabew.dev_attw.attw,
	&sensow_dev_attw_in7_wabew.dev_attw.attw,
	&sensow_dev_attw_in8_wabew.dev_attw.attw,
	&sensow_dev_attw_in9_wabew.dev_attw.attw,
	&sensow_dev_attw_in10_wabew.dev_attw.attw,
	&sensow_dev_attw_in11_wabew.dev_attw.attw,
	&sensow_dev_attw_in12_wabew.dev_attw.attw,
	&sensow_dev_attw_in13_wabew.dev_attw.attw,

	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	&sensow_dev_attw_in7_awawm.dev_attw.attw,
	&sensow_dev_attw_in8_awawm.dev_attw.attw,
	&sensow_dev_attw_in9_awawm.dev_attw.attw,
	&sensow_dev_attw_in10_awawm.dev_attw.attw,
	&sensow_dev_attw_in11_awawm.dev_attw.attw,
	&sensow_dev_attw_in12_awawm.dev_attw.attw,
	&sensow_dev_attw_in13_awawm.dev_attw.attw,

	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan4_min.dev_attw.attw,
	&sensow_dev_attw_fan5_min.dev_attw.attw,
	&sensow_dev_attw_fan6_min.dev_attw.attw,
	&sensow_dev_attw_fan7_min.dev_attw.attw,
	&sensow_dev_attw_fan8_min.dev_attw.attw,

	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan4_input.dev_attw.attw,
	&sensow_dev_attw_fan5_input.dev_attw.attw,
	&sensow_dev_attw_fan6_input.dev_attw.attw,
	&sensow_dev_attw_fan7_input.dev_attw.attw,
	&sensow_dev_attw_fan8_input.dev_attw.attw,

	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan3_awawm.dev_attw.attw,
	&sensow_dev_attw_fan4_awawm.dev_attw.attw,
	&sensow_dev_attw_fan5_awawm.dev_attw.attw,
	&sensow_dev_attw_fan6_awawm.dev_attw.attw,
	&sensow_dev_attw_fan7_awawm.dev_attw.attw,
	&sensow_dev_attw_fan8_awawm.dev_attw.attw,

	&sensow_dev_attw_fowce_pwm_max.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm3.dev_attw.attw,
	&sensow_dev_attw_pwm4.dev_attw.attw,

	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm4_auto_point1_pwm.dev_attw.attw,

	&sensow_dev_attw_pwm1_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm4_auto_point2_pwm.dev_attw.attw,

	&sensow_dev_attw_temp1_auto_point1_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_point1_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_point1_hyst.dev_attw.attw,
	&sensow_dev_attw_temp4_auto_point1_hyst.dev_attw.attw,

	&sensow_dev_attw_temp1_auto_point2_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_point2_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_point2_hyst.dev_attw.attw,
	&sensow_dev_attw_temp4_auto_point2_hyst.dev_attw.attw,

	&sensow_dev_attw_temp1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_temp4_auto_point1_temp.dev_attw.attw,

	&sensow_dev_attw_temp1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_temp4_auto_point2_temp.dev_attw.attw,

	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm4_enabwe.dev_attw.attw,

	&sensow_dev_attw_pwm1_auto_channews_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_channews_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_channews_temp.dev_attw.attw,
	&sensow_dev_attw_pwm4_auto_channews_temp.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(adt7462);

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int adt7462_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int vendow, device, wevision;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	vendow = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_VENDOW);
	if (vendow != ADT7462_VENDOW)
		wetuwn -ENODEV;

	device = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_DEVICE);
	if (device != ADT7462_DEVICE)
		wetuwn -ENODEV;

	wevision = i2c_smbus_wead_byte_data(cwient, ADT7462_WEG_WEVISION);
	if (wevision != ADT7462_WEVISION)
		wetuwn -ENODEV;

	stwscpy(info->type, "adt7462", I2C_NAME_SIZE);

	wetuwn 0;
}

static int adt7462_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct adt7462_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(dev, sizeof(stwuct adt7462_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->wock);

	dev_info(&cwient->dev, "%s chip found\n", cwient->name);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   adt7462_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id adt7462_id[] = {
	{ "adt7462", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adt7462_id);

static stwuct i2c_dwivew adt7462_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "adt7462",
	},
	.pwobe		= adt7462_pwobe,
	.id_tabwe	= adt7462_id,
	.detect		= adt7462_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(adt7462_dwivew);

MODUWE_AUTHOW("Dawwick J. Wong <dawwick.wong@owacwe.com>");
MODUWE_DESCWIPTION("ADT7462 dwivew");
MODUWE_WICENSE("GPW");
