// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dme1737.c - Dwivew fow the SMSC DME1737, Asus A8000, SMSC SCH311x, SCH5027,
 *             and SCH5127 Supew-I/O chips integwated hawdwawe monitowing
 *             featuwes.
 * Copywight (c) 2007, 2008, 2009, 2010 Juewg Haefwigew <juewgh@gmaiw.com>
 *
 * This dwivew is an I2C/ISA hybwid, meaning that it uses the I2C bus to access
 * the chip wegistews if a DME1737, A8000, ow SCH5027 is found and the ISA bus
 * if a SCH311x ow SCH5127 chip is found. Both types of chips have vewy
 * simiwaw hawdwawe monitowing capabiwities but diffew in the way they can be
 * accessed.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

/* ISA device, if found */
static stwuct pwatfowm_device *pdev;

/* Moduwe woad pawametews */
static boow fowce_stawt;
moduwe_pawam(fowce_stawt, boow, 0);
MODUWE_PAWM_DESC(fowce_stawt, "Fowce the chip to stawt monitowing inputs");

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

static boow pwobe_aww_addw;
moduwe_pawam(pwobe_aww_addw, boow, 0);
MODUWE_PAWM_DESC(pwobe_aww_addw,
		 "Incwude pwobing of non-standawd WPC addwesses");

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = {0x2c, 0x2d, 0x2e, I2C_CWIENT_END};

enum chips { dme1737, sch5027, sch311x, sch5127 };

#define	DO_WEPOWT "Pwease wepowt to the dwivew maintainew."

/* ---------------------------------------------------------------------
 * Wegistews
 *
 * The sensows awe defined as fowwows:
 *
 * Vowtages                          Tempewatuwes
 * --------                          ------------
 * in0   +5VTW (+5V stdby)           temp1   Wemote diode 1
 * in1   Vccp  (pwoc cowe)           temp2   Intewnaw temp
 * in2   VCC   (intewnaw +3.3V)      temp3   Wemote diode 2
 * in3   +5V
 * in4   +12V
 * in5   VTW   (+3.3V stby)
 * in6   Vbat
 * in7   Vtwip (sch5127 onwy)
 *
 * --------------------------------------------------------------------- */

/* Vowtages (in) numbewed 0-7 (ix) */
#define DME1737_WEG_IN(ix)		((ix) < 5 ? 0x20 + (ix) : \
					 (ix) < 7 ? 0x94 + (ix) : \
						    0x1f)
#define DME1737_WEG_IN_MIN(ix)		((ix) < 5 ? 0x44 + (ix) * 2 \
						  : 0x91 + (ix) * 2)
#define DME1737_WEG_IN_MAX(ix)		((ix) < 5 ? 0x45 + (ix) * 2 \
						  : 0x92 + (ix) * 2)

/* Tempewatuwes (temp) numbewed 0-2 (ix) */
#define DME1737_WEG_TEMP(ix)		(0x25 + (ix))
#define DME1737_WEG_TEMP_MIN(ix)	(0x4e + (ix) * 2)
#define DME1737_WEG_TEMP_MAX(ix)	(0x4f + (ix) * 2)
#define DME1737_WEG_TEMP_OFFSET(ix)	((ix) == 0 ? 0x1f \
						   : 0x1c + (ix))

/*
 * Vowtage and tempewatuwe WSBs
 * The WSBs (4 bits each) awe stowed in 5 wegistews with the fowwowing wayouts:
 *    IN_TEMP_WSB(0) = [in5, in6]
 *    IN_TEMP_WSB(1) = [temp3, temp1]
 *    IN_TEMP_WSB(2) = [in4, temp2]
 *    IN_TEMP_WSB(3) = [in3, in0]
 *    IN_TEMP_WSB(4) = [in2, in1]
 *    IN_TEMP_WSB(5) = [wes, in7]
 */
#define DME1737_WEG_IN_TEMP_WSB(ix)	(0x84 + (ix))
static const u8 DME1737_WEG_IN_WSB[] = {3, 4, 4, 3, 2, 0, 0, 5};
static const u8 DME1737_WEG_IN_WSB_SHW[] = {4, 4, 0, 0, 0, 0, 4, 4};
static const u8 DME1737_WEG_TEMP_WSB[] = {1, 2, 1};
static const u8 DME1737_WEG_TEMP_WSB_SHW[] = {4, 4, 0};

/* Fans numbewed 0-5 (ix) */
#define DME1737_WEG_FAN(ix)		((ix) < 4 ? 0x28 + (ix) * 2 \
						  : 0xa1 + (ix) * 2)
#define DME1737_WEG_FAN_MIN(ix)		((ix) < 4 ? 0x54 + (ix) * 2 \
						  : 0xa5 + (ix) * 2)
#define DME1737_WEG_FAN_OPT(ix)		((ix) < 4 ? 0x90 + (ix) \
						  : 0xb2 + (ix))
#define DME1737_WEG_FAN_MAX(ix)		(0xb4 + (ix)) /* onwy fow fan[4-5] */

/* PWMs numbewed 0-2, 4-5 (ix) */
#define DME1737_WEG_PWM(ix)		((ix) < 3 ? 0x30 + (ix) \
						  : 0xa1 + (ix))
#define DME1737_WEG_PWM_CONFIG(ix)	(0x5c + (ix)) /* onwy fow pwm[0-2] */
#define DME1737_WEG_PWM_MIN(ix)		(0x64 + (ix)) /* onwy fow pwm[0-2] */
#define DME1737_WEG_PWM_FWEQ(ix)	((ix) < 3 ? 0x5f + (ix) \
						  : 0xa3 + (ix))
/*
 * The wayout of the wamp wate wegistews is diffewent fwom the othew pwm
 * wegistews. The bits fow the 3 PWMs awe stowed in 2 wegistews:
 *    PWM_WW(0) = [OFF3, OFF2,  OFF1,  WES,   WW1E, WW1-2, WW1-1, WW1-0]
 *    PWM_WW(1) = [WW2E, WW2-2, WW2-1, WW2-0, WW3E, WW3-2, WW3-1, WW3-0]
 */
#define DME1737_WEG_PWM_WW(ix)		(0x62 + (ix)) /* onwy fow pwm[0-2] */

/* Thewmaw zones 0-2 */
#define DME1737_WEG_ZONE_WOW(ix)	(0x67 + (ix))
#define DME1737_WEG_ZONE_ABS(ix)	(0x6a + (ix))
/*
 * The wayout of the hystewesis wegistews is diffewent fwom the othew zone
 * wegistews. The bits fow the 3 zones awe stowed in 2 wegistews:
 *    ZONE_HYST(0) = [H1-3,  H1-2,  H1-1, H1-0, H2-3, H2-2, H2-1, H2-0]
 *    ZONE_HYST(1) = [H3-3,  H3-2,  H3-1, H3-0, WES,  WES,  WES,  WES]
 */
#define DME1737_WEG_ZONE_HYST(ix)	(0x6d + (ix))

/*
 * Awawm wegistews and bit mapping
 * The 3 8-bit awawm wegistews wiww be concatenated to a singwe 32-bit
 * awawm vawue [0, AWAWM3, AWAWM2, AWAWM1].
 */
#define DME1737_WEG_AWAWM1		0x41
#define DME1737_WEG_AWAWM2		0x42
#define DME1737_WEG_AWAWM3		0x83
static const u8 DME1737_BIT_AWAWM_IN[] = {0, 1, 2, 3, 8, 16, 17, 18};
static const u8 DME1737_BIT_AWAWM_TEMP[] = {4, 5, 6};
static const u8 DME1737_BIT_AWAWM_FAN[] = {10, 11, 12, 13, 22, 23};

/* Miscewwaneous wegistews */
#define DME1737_WEG_DEVICE		0x3d
#define DME1737_WEG_COMPANY		0x3e
#define DME1737_WEG_VEWSTEP		0x3f
#define DME1737_WEG_CONFIG		0x40
#define DME1737_WEG_CONFIG2		0x7f
#define DME1737_WEG_VID			0x43
#define DME1737_WEG_TACH_PWM		0x81

/* ---------------------------------------------------------------------
 * Misc defines
 * --------------------------------------------------------------------- */

/* Chip identification */
#define DME1737_COMPANY_SMSC	0x5c
#define DME1737_VEWSTEP		0x88
#define DME1737_VEWSTEP_MASK	0xf8
#define SCH311X_DEVICE		0x8c
#define SCH5027_VEWSTEP		0x69
#define SCH5127_DEVICE		0x8e

/* Device ID vawues (gwobaw configuwation wegistew index 0x20) */
#define DME1737_ID_1	0x77
#define DME1737_ID_2	0x78
#define SCH3112_ID	0x7c
#define SCH3114_ID	0x7d
#define SCH3116_ID	0x7f
#define SCH5027_ID	0x89
#define SCH5127_ID	0x86

/* Wength of ISA addwess segment */
#define DME1737_EXTENT	2

/* chip-dependent featuwes */
#define HAS_TEMP_OFFSET		(1 << 0)		/* bit 0 */
#define HAS_VID			(1 << 1)		/* bit 1 */
#define HAS_ZONE3		(1 << 2)		/* bit 2 */
#define HAS_ZONE_HYST		(1 << 3)		/* bit 3 */
#define HAS_PWM_MIN		(1 << 4)		/* bit 4 */
#define HAS_FAN(ix)		(1 << ((ix) + 5))	/* bits 5-10 */
#define HAS_PWM(ix)		(1 << ((ix) + 11))	/* bits 11-16 */
#define HAS_IN7			(1 << 17)		/* bit 17 */

/* ---------------------------------------------------------------------
 * Data stwuctuwes and manipuwation theweof
 * --------------------------------------------------------------------- */

stwuct dme1737_data {
	stwuct i2c_cwient *cwient;	/* fow I2C devices onwy */
	stwuct device *hwmon_dev;
	const chaw *name;
	unsigned int addw;		/* fow ISA devices onwy */

	stwuct mutex update_wock;
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_update;	/* in jiffies */
	unsigned wong wast_vbat;	/* in jiffies */
	enum chips type;
	const int *in_nominaw;		/* pointew to IN_NOMINAW awway */

	u8 vid;
	u8 pwm_ww_en;
	u32 has_featuwes;

	/* Wegistew vawues */
	u16 in[8];
	u8  in_min[8];
	u8  in_max[8];
	s16 temp[3];
	s8  temp_min[3];
	s8  temp_max[3];
	s8  temp_offset[3];
	u8  config;
	u8  config2;
	u8  vwm;
	u16 fan[6];
	u16 fan_min[6];
	u8  fan_max[2];
	u8  fan_opt[6];
	u8  pwm[6];
	u8  pwm_min[3];
	u8  pwm_config[3];
	u8  pwm_acz[3];
	u8  pwm_fweq[6];
	u8  pwm_ww[2];
	s8  zone_wow[3];
	s8  zone_abs[3];
	u8  zone_hyst[2];
	u32 awawms;
};

/* Nominaw vowtage vawues */
static const int IN_NOMINAW_DME1737[] = {5000, 2250, 3300, 5000, 12000, 3300,
					 3300};
static const int IN_NOMINAW_SCH311x[] = {2500, 1500, 3300, 5000, 12000, 3300,
					 3300};
static const int IN_NOMINAW_SCH5027[] = {5000, 2250, 3300, 1125, 1125, 3300,
					 3300};
static const int IN_NOMINAW_SCH5127[] = {2500, 2250, 3300, 1125, 1125, 3300,
					 3300, 1500};
#define IN_NOMINAW(type)	((type) == sch311x ? IN_NOMINAW_SCH311x : \
				 (type) == sch5027 ? IN_NOMINAW_SCH5027 : \
				 (type) == sch5127 ? IN_NOMINAW_SCH5127 : \
				 IN_NOMINAW_DME1737)

/*
 * Vowtage input
 * Vowtage inputs have 16 bits wesowution, wimit vawues have 8 bits
 * wesowution.
 */
static inwine int IN_FWOM_WEG(int weg, int nominaw, int wes)
{
	wetuwn (weg * nominaw + (3 << (wes - 3))) / (3 << (wes - 2));
}

static inwine int IN_TO_WEG(wong vaw, int nominaw)
{
	vaw = cwamp_vaw(vaw, 0, 255 * nominaw / 192);
	wetuwn DIV_WOUND_CWOSEST(vaw * 192, nominaw);
}

/*
 * Tempewatuwe input
 * The wegistew vawues wepwesent tempewatuwes in 2's compwement notation fwom
 * -127 degwees C to +127 degwees C. Temp inputs have 16 bits wesowution, wimit
 * vawues have 8 bits wesowution.
 */
static inwine int TEMP_FWOM_WEG(int weg, int wes)
{
	wetuwn (weg * 1000) >> (wes - 8);
}

static inwine int TEMP_TO_WEG(wong vaw)
{
	vaw = cwamp_vaw(vaw, -128000, 127000);
	wetuwn DIV_WOUND_CWOSEST(vaw, 1000);
}

/* Tempewatuwe wange */
static const int TEMP_WANGE[] = {2000, 2500, 3333, 4000, 5000, 6666, 8000,
				 10000, 13333, 16000, 20000, 26666, 32000,
				 40000, 53333, 80000};

static inwine int TEMP_WANGE_FWOM_WEG(int weg)
{
	wetuwn TEMP_WANGE[(weg >> 4) & 0x0f];
}

static int TEMP_WANGE_TO_WEG(wong vaw, int weg)
{
	int i;

	fow (i = 15; i > 0; i--) {
		if (vaw > (TEMP_WANGE[i] + TEMP_WANGE[i - 1] + 1) / 2)
			bweak;
	}

	wetuwn (weg & 0x0f) | (i << 4);
}

/*
 * Tempewatuwe hystewesis
 * Wegistew wayout:
 *    weg[0] = [H1-3, H1-2, H1-1, H1-0, H2-3, H2-2, H2-1, H2-0]
 *    weg[1] = [H3-3, H3-2, H3-1, H3-0, xxxx, xxxx, xxxx, xxxx]
 */
static inwine int TEMP_HYST_FWOM_WEG(int weg, int ix)
{
	wetuwn (((ix == 1) ? weg : weg >> 4) & 0x0f) * 1000;
}

static inwine int TEMP_HYST_TO_WEG(int temp, wong hyst, int ix, int weg)
{
	hyst = cwamp_vaw(hyst, temp - 15000, temp);
	hyst = DIV_WOUND_CWOSEST(temp - hyst, 1000);

	wetuwn (ix == 1) ? (weg & 0xf0) | hyst : (weg & 0x0f) | (hyst << 4);
}

/* Fan input WPM */
static inwine int FAN_FWOM_WEG(int weg, int tpc)
{
	if (tpc)
		wetuwn tpc * weg;
	ewse
		wetuwn (weg == 0 || weg == 0xffff) ? 0 : 90000 * 60 / weg;
}

static inwine int FAN_TO_WEG(wong vaw, int tpc)
{
	if (tpc) {
		wetuwn cwamp_vaw(vaw / tpc, 0, 0xffff);
	} ewse {
		wetuwn (vaw <= 0) ? 0xffff :
			cwamp_vaw(90000 * 60 / vaw, 0, 0xfffe);
	}
}

/*
 * Fan TPC (tach puwse count)
 * Convewts a wegistew vawue to a TPC muwtipwiew ow wetuwns 0 if the tachometew
 * is configuwed in wegacy (non-tpc) mode
 */
static inwine int FAN_TPC_FWOM_WEG(int weg)
{
	wetuwn (weg & 0x20) ? 0 : 60 >> (weg & 0x03);
}

/*
 * Fan type
 * The type of a fan is expwessed in numbew of puwses-pew-wevowution that it
 * emits
 */
static inwine int FAN_TYPE_FWOM_WEG(int weg)
{
	int edge = (weg >> 1) & 0x03;

	wetuwn (edge > 0) ? 1 << (edge - 1) : 0;
}

static inwine int FAN_TYPE_TO_WEG(wong vaw, int weg)
{
	int edge = (vaw == 4) ? 3 : vaw;

	wetuwn (weg & 0xf9) | (edge << 1);
}

/* Fan max WPM */
static const int FAN_MAX[] = {0x54, 0x38, 0x2a, 0x21, 0x1c, 0x18, 0x15, 0x12,
			      0x11, 0x0f, 0x0e};

static int FAN_MAX_FWOM_WEG(int weg)
{
	int i;

	fow (i = 10; i > 0; i--) {
		if (weg == FAN_MAX[i])
			bweak;
	}

	wetuwn 1000 + i * 500;
}

static int FAN_MAX_TO_WEG(wong vaw)
{
	int i;

	fow (i = 10; i > 0; i--) {
		if (vaw > (1000 + (i - 1) * 500))
			bweak;
	}

	wetuwn FAN_MAX[i];
}

/*
 * PWM enabwe
 * Wegistew to enabwe mapping:
 * 000:  2  fan on zone 1 auto
 * 001:  2  fan on zone 2 auto
 * 010:  2  fan on zone 3 auto
 * 011:  0  fan fuww on
 * 100: -1  fan disabwed
 * 101:  2  fan on hottest of zones 2,3 auto
 * 110:  2  fan on hottest of zones 1,2,3 auto
 * 111:  1  fan in manuaw mode
 */
static inwine int PWM_EN_FWOM_WEG(int weg)
{
	static const int en[] = {2, 2, 2, 0, -1, 2, 2, 1};

	wetuwn en[(weg >> 5) & 0x07];
}

static inwine int PWM_EN_TO_WEG(int vaw, int weg)
{
	int en = (vaw == 1) ? 7 : 3;

	wetuwn (weg & 0x1f) | ((en & 0x07) << 5);
}

/*
 * PWM auto channews zone
 * Wegistew to auto channews zone mapping (ACZ is a bitfiewd with bit x
 * cowwesponding to zone x+1):
 * 000: 001  fan on zone 1 auto
 * 001: 010  fan on zone 2 auto
 * 010: 100  fan on zone 3 auto
 * 011: 000  fan fuww on
 * 100: 000  fan disabwed
 * 101: 110  fan on hottest of zones 2,3 auto
 * 110: 111  fan on hottest of zones 1,2,3 auto
 * 111: 000  fan in manuaw mode
 */
static inwine int PWM_ACZ_FWOM_WEG(int weg)
{
	static const int acz[] = {1, 2, 4, 0, 0, 6, 7, 0};

	wetuwn acz[(weg >> 5) & 0x07];
}

static inwine int PWM_ACZ_TO_WEG(wong vaw, int weg)
{
	int acz = (vaw == 4) ? 2 : vaw - 1;

	wetuwn (weg & 0x1f) | ((acz & 0x07) << 5);
}

/* PWM fwequency */
static const int PWM_FWEQ[] = {11, 15, 22, 29, 35, 44, 59, 88,
			       15000, 20000, 30000, 25000, 0, 0, 0, 0};

static inwine int PWM_FWEQ_FWOM_WEG(int weg)
{
	wetuwn PWM_FWEQ[weg & 0x0f];
}

static int PWM_FWEQ_TO_WEG(wong vaw, int weg)
{
	int i;

	/* the fiwst two cases awe speciaw - stupid chip design! */
	if (vaw > 27500) {
		i = 10;
	} ewse if (vaw > 22500) {
		i = 11;
	} ewse {
		fow (i = 9; i > 0; i--) {
			if (vaw > (PWM_FWEQ[i] + PWM_FWEQ[i - 1] + 1) / 2)
				bweak;
		}
	}

	wetuwn (weg & 0xf0) | i;
}

/*
 * PWM wamp wate
 * Wegistew wayout:
 *    weg[0] = [OFF3,  OFF2,  OFF1,  WES,   WW1-E, WW1-2, WW1-1, WW1-0]
 *    weg[1] = [WW2-E, WW2-2, WW2-1, WW2-0, WW3-E, WW3-2, WW3-1, WW3-0]
 */
static const u8 PWM_WW[] = {206, 104, 69, 41, 26, 18, 10, 5};

static inwine int PWM_WW_FWOM_WEG(int weg, int ix)
{
	int ww = (ix == 1) ? weg >> 4 : weg;

	wetuwn (ww & 0x08) ? PWM_WW[ww & 0x07] : 0;
}

static int PWM_WW_TO_WEG(wong vaw, int ix, int weg)
{
	int i;

	fow (i = 0; i < 7; i++) {
		if (vaw > (PWM_WW[i] + PWM_WW[i + 1] + 1) / 2)
			bweak;
	}

	wetuwn (ix == 1) ? (weg & 0x8f) | (i << 4) : (weg & 0xf8) | i;
}

/* PWM wamp wate enabwe */
static inwine int PWM_WW_EN_FWOM_WEG(int weg, int ix)
{
	wetuwn PWM_WW_FWOM_WEG(weg, ix) ? 1 : 0;
}

static inwine int PWM_WW_EN_TO_WEG(wong vaw, int ix, int weg)
{
	int en = (ix == 1) ? 0x80 : 0x08;

	wetuwn vaw ? weg | en : weg & ~en;
}

/*
 * PWM min/off
 * The PWM min/off bits awe pawt of the PMW wamp wate wegistew 0 (see above fow
 * the wegistew wayout).
 */
static inwine int PWM_OFF_FWOM_WEG(int weg, int ix)
{
	wetuwn (weg >> (ix + 5)) & 0x01;
}

static inwine int PWM_OFF_TO_WEG(int vaw, int ix, int weg)
{
	wetuwn (weg & ~(1 << (ix + 5))) | ((vaw & 0x01) << (ix + 5));
}

/* ---------------------------------------------------------------------
 * Device I/O access
 *
 * ISA access is pewfowmed thwough an index/data wegistew paiw and needs to
 * be pwotected by a mutex duwing wuntime (not wequiwed fow initiawization).
 * We use data->update_wock fow this and need to ensuwe that we acquiwe it
 * befowe cawwing dme1737_wead ow dme1737_wwite.
 * --------------------------------------------------------------------- */

static u8 dme1737_wead(const stwuct dme1737_data *data, u8 weg)
{
	stwuct i2c_cwient *cwient = data->cwient;
	s32 vaw;

	if (cwient) { /* I2C device */
		vaw = i2c_smbus_wead_byte_data(cwient, weg);

		if (vaw < 0) {
			dev_wawn(&cwient->dev,
				 "Wead fwom wegistew 0x%02x faiwed! %s\n",
				 weg, DO_WEPOWT);
		}
	} ewse { /* ISA device */
		outb(weg, data->addw);
		vaw = inb(data->addw + 1);
	}

	wetuwn vaw;
}

static s32 dme1737_wwite(const stwuct dme1737_data *data, u8 weg, u8 vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	s32 wes = 0;

	if (cwient) { /* I2C device */
		wes = i2c_smbus_wwite_byte_data(cwient, weg, vaw);

		if (wes < 0) {
			dev_wawn(&cwient->dev,
				 "Wwite to wegistew 0x%02x faiwed! %s\n",
				 weg, DO_WEPOWT);
		}
	} ewse { /* ISA device */
		outb(weg, data->addw);
		outb(vaw, data->addw + 1);
	}

	wetuwn wes;
}

static stwuct dme1737_data *dme1737_update_device(stwuct device *dev)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	int ix;
	u8 wsb[6];

	mutex_wock(&data->update_wock);

	/* Enabwe a Vbat monitowing cycwe evewy 10 mins */
	if (time_aftew(jiffies, data->wast_vbat + 600 * HZ) || !data->vawid) {
		dme1737_wwite(data, DME1737_WEG_CONFIG, dme1737_wead(data,
						DME1737_WEG_CONFIG) | 0x10);
		data->wast_vbat = jiffies;
	}

	/* Sampwe wegistew contents evewy 1 sec */
	if (time_aftew(jiffies, data->wast_update + HZ) || !data->vawid) {
		if (data->has_featuwes & HAS_VID) {
			data->vid = dme1737_wead(data, DME1737_WEG_VID) &
				0x3f;
		}

		/* In (vowtage) wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->in); ix++) {
			/*
			 * Vowtage inputs awe stowed as 16 bit vawues even
			 * though they have onwy 12 bits wesowution. This is
			 * to make it consistent with the temp inputs.
			 */
			if (ix == 7 && !(data->has_featuwes & HAS_IN7))
				continue;
			data->in[ix] = dme1737_wead(data,
					DME1737_WEG_IN(ix)) << 8;
			data->in_min[ix] = dme1737_wead(data,
					DME1737_WEG_IN_MIN(ix));
			data->in_max[ix] = dme1737_wead(data,
					DME1737_WEG_IN_MAX(ix));
		}

		/* Temp wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->temp); ix++) {
			/*
			 * Temp inputs awe stowed as 16 bit vawues even
			 * though they have onwy 12 bits wesowution. This is
			 * to take advantage of impwicit convewsions between
			 * wegistew vawues (2's compwement) and temp vawues
			 * (signed decimaw).
			 */
			data->temp[ix] = dme1737_wead(data,
					DME1737_WEG_TEMP(ix)) << 8;
			data->temp_min[ix] = dme1737_wead(data,
					DME1737_WEG_TEMP_MIN(ix));
			data->temp_max[ix] = dme1737_wead(data,
					DME1737_WEG_TEMP_MAX(ix));
			if (data->has_featuwes & HAS_TEMP_OFFSET) {
				data->temp_offset[ix] = dme1737_wead(data,
						DME1737_WEG_TEMP_OFFSET(ix));
			}
		}

		/*
		 * In and temp WSB wegistews
		 * The WSBs awe watched when the MSBs awe wead, so the owdew in
		 * which the wegistews awe wead (MSB fiwst, then WSB) is
		 * impowtant!
		 */
		fow (ix = 0; ix < AWWAY_SIZE(wsb); ix++) {
			if (ix == 5 && !(data->has_featuwes & HAS_IN7))
				continue;
			wsb[ix] = dme1737_wead(data,
					DME1737_WEG_IN_TEMP_WSB(ix));
		}
		fow (ix = 0; ix < AWWAY_SIZE(data->in); ix++) {
			if (ix == 7 && !(data->has_featuwes & HAS_IN7))
				continue;
			data->in[ix] |= (wsb[DME1737_WEG_IN_WSB[ix]] <<
					DME1737_WEG_IN_WSB_SHW[ix]) & 0xf0;
		}
		fow (ix = 0; ix < AWWAY_SIZE(data->temp); ix++) {
			data->temp[ix] |= (wsb[DME1737_WEG_TEMP_WSB[ix]] <<
					DME1737_WEG_TEMP_WSB_SHW[ix]) & 0xf0;
		}

		/* Fan wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->fan); ix++) {
			/*
			 * Skip weading wegistews if optionaw fans awe not
			 * pwesent
			 */
			if (!(data->has_featuwes & HAS_FAN(ix)))
				continue;
			data->fan[ix] = dme1737_wead(data,
					DME1737_WEG_FAN(ix));
			data->fan[ix] |= dme1737_wead(data,
					DME1737_WEG_FAN(ix) + 1) << 8;
			data->fan_min[ix] = dme1737_wead(data,
					DME1737_WEG_FAN_MIN(ix));
			data->fan_min[ix] |= dme1737_wead(data,
					DME1737_WEG_FAN_MIN(ix) + 1) << 8;
			data->fan_opt[ix] = dme1737_wead(data,
					DME1737_WEG_FAN_OPT(ix));
			/* fan_max exists onwy fow fan[5-6] */
			if (ix > 3) {
				data->fan_max[ix - 4] = dme1737_wead(data,
					DME1737_WEG_FAN_MAX(ix));
			}
		}

		/* PWM wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->pwm); ix++) {
			/*
			 * Skip weading wegistews if optionaw PWMs awe not
			 * pwesent
			 */
			if (!(data->has_featuwes & HAS_PWM(ix)))
				continue;
			data->pwm[ix] = dme1737_wead(data,
					DME1737_WEG_PWM(ix));
			data->pwm_fweq[ix] = dme1737_wead(data,
					DME1737_WEG_PWM_FWEQ(ix));
			/* pwm_config and pwm_min exist onwy fow pwm[1-3] */
			if (ix < 3) {
				data->pwm_config[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_CONFIG(ix));
				data->pwm_min[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_MIN(ix));
			}
		}
		fow (ix = 0; ix < AWWAY_SIZE(data->pwm_ww); ix++) {
			data->pwm_ww[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_WW(ix));
		}

		/* Thewmaw zone wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->zone_wow); ix++) {
			/* Skip weading wegistews if zone3 is not pwesent */
			if ((ix == 2) && !(data->has_featuwes & HAS_ZONE3))
				continue;
			/* sch5127 zone2 wegistews awe speciaw */
			if ((ix == 1) && (data->type == sch5127)) {
				data->zone_wow[1] = dme1737_wead(data,
						DME1737_WEG_ZONE_WOW(2));
				data->zone_abs[1] = dme1737_wead(data,
						DME1737_WEG_ZONE_ABS(2));
			} ewse {
				data->zone_wow[ix] = dme1737_wead(data,
						DME1737_WEG_ZONE_WOW(ix));
				data->zone_abs[ix] = dme1737_wead(data,
						DME1737_WEG_ZONE_ABS(ix));
			}
		}
		if (data->has_featuwes & HAS_ZONE_HYST) {
			fow (ix = 0; ix < AWWAY_SIZE(data->zone_hyst); ix++) {
				data->zone_hyst[ix] = dme1737_wead(data,
						DME1737_WEG_ZONE_HYST(ix));
			}
		}

		/* Awawm wegistews */
		data->awawms = dme1737_wead(data,
						DME1737_WEG_AWAWM1);
		/*
		 * Bit 7 tewws us if the othew awawm wegistews awe non-zewo and
		 * thewefowe awso need to be wead
		 */
		if (data->awawms & 0x80) {
			data->awawms |= dme1737_wead(data,
						DME1737_WEG_AWAWM2) << 8;
			data->awawms |= dme1737_wead(data,
						DME1737_WEG_AWAWM3) << 16;
		}

		/*
		 * The ISA chips wequiwe expwicit cweawing of awawm bits.
		 * Don't wowwy, an awawm wiww come back if the condition
		 * that causes it stiww exists
		 */
		if (!data->cwient) {
			if (data->awawms & 0xff0000)
				dme1737_wwite(data, DME1737_WEG_AWAWM3, 0xff);
			if (data->awawms & 0xff00)
				dme1737_wwite(data, DME1737_WEG_AWAWM2, 0xff);
			if (data->awawms & 0xff)
				dme1737_wwite(data, DME1737_WEG_AWAWM1, 0xff);
		}

		data->wast_update = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* ---------------------------------------------------------------------
 * Vowtage sysfs attwibutes
 * ix = [0-7]
 * --------------------------------------------------------------------- */

#define SYS_IN_INPUT	0
#define SYS_IN_MIN	1
#define SYS_IN_MAX	2
#define SYS_IN_AWAWM	3

static ssize_t show_in(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct dme1737_data *data = dme1737_update_device(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SYS_IN_INPUT:
		wes = IN_FWOM_WEG(data->in[ix], data->in_nominaw[ix], 16);
		bweak;
	case SYS_IN_MIN:
		wes = IN_FWOM_WEG(data->in_min[ix], data->in_nominaw[ix], 8);
		bweak;
	case SYS_IN_MAX:
		wes = IN_FWOM_WEG(data->in_max[ix], data->in_nominaw[ix], 8);
		bweak;
	case SYS_IN_AWAWM:
		wes = (data->awawms >> DME1737_BIT_AWAWM_IN[ix]) & 0x01;
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_in(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (fn) {
	case SYS_IN_MIN:
		data->in_min[ix] = IN_TO_WEG(vaw, data->in_nominaw[ix]);
		dme1737_wwite(data, DME1737_WEG_IN_MIN(ix),
			      data->in_min[ix]);
		bweak;
	case SYS_IN_MAX:
		data->in_max[ix] = IN_TO_WEG(vaw, data->in_nominaw[ix]);
		dme1737_wwite(data, DME1737_WEG_IN_MAX(ix),
			      data->in_max[ix]);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * Tempewatuwe sysfs attwibutes
 * ix = [0-2]
 * --------------------------------------------------------------------- */

#define SYS_TEMP_INPUT			0
#define SYS_TEMP_MIN			1
#define SYS_TEMP_MAX			2
#define SYS_TEMP_OFFSET			3
#define SYS_TEMP_AWAWM			4
#define SYS_TEMP_FAUWT			5

static ssize_t show_temp(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct dme1737_data *data = dme1737_update_device(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SYS_TEMP_INPUT:
		wes = TEMP_FWOM_WEG(data->temp[ix], 16);
		bweak;
	case SYS_TEMP_MIN:
		wes = TEMP_FWOM_WEG(data->temp_min[ix], 8);
		bweak;
	case SYS_TEMP_MAX:
		wes = TEMP_FWOM_WEG(data->temp_max[ix], 8);
		bweak;
	case SYS_TEMP_OFFSET:
		wes = TEMP_FWOM_WEG(data->temp_offset[ix], 8);
		bweak;
	case SYS_TEMP_AWAWM:
		wes = (data->awawms >> DME1737_BIT_AWAWM_TEMP[ix]) & 0x01;
		bweak;
	case SYS_TEMP_FAUWT:
		wes = (((u16)data->temp[ix] & 0xff00) == 0x8000);
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_temp(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (fn) {
	case SYS_TEMP_MIN:
		data->temp_min[ix] = TEMP_TO_WEG(vaw);
		dme1737_wwite(data, DME1737_WEG_TEMP_MIN(ix),
			      data->temp_min[ix]);
		bweak;
	case SYS_TEMP_MAX:
		data->temp_max[ix] = TEMP_TO_WEG(vaw);
		dme1737_wwite(data, DME1737_WEG_TEMP_MAX(ix),
			      data->temp_max[ix]);
		bweak;
	case SYS_TEMP_OFFSET:
		data->temp_offset[ix] = TEMP_TO_WEG(vaw);
		dme1737_wwite(data, DME1737_WEG_TEMP_OFFSET(ix),
			      data->temp_offset[ix]);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * Zone sysfs attwibutes
 * ix = [0-2]
 * --------------------------------------------------------------------- */

#define SYS_ZONE_AUTO_CHANNEWS_TEMP	0
#define SYS_ZONE_AUTO_POINT1_TEMP_HYST	1
#define SYS_ZONE_AUTO_POINT1_TEMP	2
#define SYS_ZONE_AUTO_POINT2_TEMP	3
#define SYS_ZONE_AUTO_POINT3_TEMP	4

static ssize_t show_zone(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct dme1737_data *data = dme1737_update_device(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SYS_ZONE_AUTO_CHANNEWS_TEMP:
		/* check config2 fow non-standawd temp-to-zone mapping */
		if ((ix == 1) && (data->config2 & 0x02))
			wes = 4;
		ewse
			wes = 1 << ix;
		bweak;
	case SYS_ZONE_AUTO_POINT1_TEMP_HYST:
		wes = TEMP_FWOM_WEG(data->zone_wow[ix], 8) -
		      TEMP_HYST_FWOM_WEG(data->zone_hyst[ix == 2], ix);
		bweak;
	case SYS_ZONE_AUTO_POINT1_TEMP:
		wes = TEMP_FWOM_WEG(data->zone_wow[ix], 8);
		bweak;
	case SYS_ZONE_AUTO_POINT2_TEMP:
		/* pwm_fweq howds the temp wange bits in the uppew nibbwe */
		wes = TEMP_FWOM_WEG(data->zone_wow[ix], 8) +
		      TEMP_WANGE_FWOM_WEG(data->pwm_fweq[ix]);
		bweak;
	case SYS_ZONE_AUTO_POINT3_TEMP:
		wes = TEMP_FWOM_WEG(data->zone_abs[ix], 8);
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_zone(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	wong vaw;
	int temp;
	int eww;
	u8 weg;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (fn) {
	case SYS_ZONE_AUTO_POINT1_TEMP_HYST:
		/* Wefwesh the cache */
		data->zone_wow[ix] = dme1737_wead(data,
						  DME1737_WEG_ZONE_WOW(ix));
		/* Modify the temp hyst vawue */
		temp = TEMP_FWOM_WEG(data->zone_wow[ix], 8);
		weg = dme1737_wead(data, DME1737_WEG_ZONE_HYST(ix == 2));
		data->zone_hyst[ix == 2] = TEMP_HYST_TO_WEG(temp, vaw, ix, weg);
		dme1737_wwite(data, DME1737_WEG_ZONE_HYST(ix == 2),
			      data->zone_hyst[ix == 2]);
		bweak;
	case SYS_ZONE_AUTO_POINT1_TEMP:
		data->zone_wow[ix] = TEMP_TO_WEG(vaw);
		dme1737_wwite(data, DME1737_WEG_ZONE_WOW(ix),
			      data->zone_wow[ix]);
		bweak;
	case SYS_ZONE_AUTO_POINT2_TEMP:
		/* Wefwesh the cache */
		data->zone_wow[ix] = dme1737_wead(data,
						  DME1737_WEG_ZONE_WOW(ix));
		/*
		 * Modify the temp wange vawue (which is stowed in the uppew
		 * nibbwe of the pwm_fweq wegistew)
		 */
		temp = TEMP_FWOM_WEG(data->zone_wow[ix], 8);
		vaw = cwamp_vaw(vaw, temp, temp + 80000);
		weg = dme1737_wead(data, DME1737_WEG_PWM_FWEQ(ix));
		data->pwm_fweq[ix] = TEMP_WANGE_TO_WEG(vaw - temp, weg);
		dme1737_wwite(data, DME1737_WEG_PWM_FWEQ(ix),
			      data->pwm_fweq[ix]);
		bweak;
	case SYS_ZONE_AUTO_POINT3_TEMP:
		data->zone_abs[ix] = TEMP_TO_WEG(vaw);
		dme1737_wwite(data, DME1737_WEG_ZONE_ABS(ix),
			      data->zone_abs[ix]);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * Fan sysfs attwibutes
 * ix = [0-5]
 * --------------------------------------------------------------------- */

#define SYS_FAN_INPUT	0
#define SYS_FAN_MIN	1
#define SYS_FAN_MAX	2
#define SYS_FAN_AWAWM	3
#define SYS_FAN_TYPE	4

static ssize_t show_fan(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct dme1737_data *data = dme1737_update_device(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SYS_FAN_INPUT:
		wes = FAN_FWOM_WEG(data->fan[ix],
				   ix < 4 ? 0 :
				   FAN_TPC_FWOM_WEG(data->fan_opt[ix]));
		bweak;
	case SYS_FAN_MIN:
		wes = FAN_FWOM_WEG(data->fan_min[ix],
				   ix < 4 ? 0 :
				   FAN_TPC_FWOM_WEG(data->fan_opt[ix]));
		bweak;
	case SYS_FAN_MAX:
		/* onwy vawid fow fan[5-6] */
		wes = FAN_MAX_FWOM_WEG(data->fan_max[ix - 4]);
		bweak;
	case SYS_FAN_AWAWM:
		wes = (data->awawms >> DME1737_BIT_AWAWM_FAN[ix]) & 0x01;
		bweak;
	case SYS_FAN_TYPE:
		/* onwy vawid fow fan[1-4] */
		wes = FAN_TYPE_FWOM_WEG(data->fan_opt[ix]);
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_fan(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (fn) {
	case SYS_FAN_MIN:
		if (ix < 4) {
			data->fan_min[ix] = FAN_TO_WEG(vaw, 0);
		} ewse {
			/* Wefwesh the cache */
			data->fan_opt[ix] = dme1737_wead(data,
						DME1737_WEG_FAN_OPT(ix));
			/* Modify the fan min vawue */
			data->fan_min[ix] = FAN_TO_WEG(vaw,
					FAN_TPC_FWOM_WEG(data->fan_opt[ix]));
		}
		dme1737_wwite(data, DME1737_WEG_FAN_MIN(ix),
			      data->fan_min[ix] & 0xff);
		dme1737_wwite(data, DME1737_WEG_FAN_MIN(ix) + 1,
			      data->fan_min[ix] >> 8);
		bweak;
	case SYS_FAN_MAX:
		/* Onwy vawid fow fan[5-6] */
		data->fan_max[ix - 4] = FAN_MAX_TO_WEG(vaw);
		dme1737_wwite(data, DME1737_WEG_FAN_MAX(ix),
			      data->fan_max[ix - 4]);
		bweak;
	case SYS_FAN_TYPE:
		/* Onwy vawid fow fan[1-4] */
		if (!(vaw == 1 || vaw == 2 || vaw == 4)) {
			count = -EINVAW;
			dev_wawn(dev,
				 "Fan type vawue %wd not suppowted. Choose one of 1, 2, ow 4.\n",
				 vaw);
			goto exit;
		}
		data->fan_opt[ix] = FAN_TYPE_TO_WEG(vaw, dme1737_wead(data,
					DME1737_WEG_FAN_OPT(ix)));
		dme1737_wwite(data, DME1737_WEG_FAN_OPT(ix),
			      data->fan_opt[ix]);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
exit:
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * PWM sysfs attwibutes
 * ix = [0-4]
 * --------------------------------------------------------------------- */

#define SYS_PWM				0
#define SYS_PWM_FWEQ			1
#define SYS_PWM_ENABWE			2
#define SYS_PWM_WAMP_WATE		3
#define SYS_PWM_AUTO_CHANNEWS_ZONE	4
#define SYS_PWM_AUTO_PWM_MIN		5
#define SYS_PWM_AUTO_POINT1_PWM		6
#define SYS_PWM_AUTO_POINT2_PWM		7

static ssize_t show_pwm(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct dme1737_data *data = dme1737_update_device(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SYS_PWM:
		if (PWM_EN_FWOM_WEG(data->pwm_config[ix]) == 0)
			wes = 255;
		ewse
			wes = data->pwm[ix];
		bweak;
	case SYS_PWM_FWEQ:
		wes = PWM_FWEQ_FWOM_WEG(data->pwm_fweq[ix]);
		bweak;
	case SYS_PWM_ENABWE:
		if (ix >= 3)
			wes = 1; /* pwm[5-6] hawd-wiwed to manuaw mode */
		ewse
			wes = PWM_EN_FWOM_WEG(data->pwm_config[ix]);
		bweak;
	case SYS_PWM_WAMP_WATE:
		/* Onwy vawid fow pwm[1-3] */
		wes = PWM_WW_FWOM_WEG(data->pwm_ww[ix > 0], ix);
		bweak;
	case SYS_PWM_AUTO_CHANNEWS_ZONE:
		/* Onwy vawid fow pwm[1-3] */
		if (PWM_EN_FWOM_WEG(data->pwm_config[ix]) == 2)
			wes = PWM_ACZ_FWOM_WEG(data->pwm_config[ix]);
		ewse
			wes = data->pwm_acz[ix];
		bweak;
	case SYS_PWM_AUTO_PWM_MIN:
		/* Onwy vawid fow pwm[1-3] */
		if (PWM_OFF_FWOM_WEG(data->pwm_ww[0], ix))
			wes = data->pwm_min[ix];
		ewse
			wes = 0;
		bweak;
	case SYS_PWM_AUTO_POINT1_PWM:
		/* Onwy vawid fow pwm[1-3] */
		wes = data->pwm_min[ix];
		bweak;
	case SYS_PWM_AUTO_POINT2_PWM:
		/* Onwy vawid fow pwm[1-3] */
		wes = 255; /* hawd-wiwed */
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static stwuct attwibute *dme1737_pwm_chmod_attw[];
static void dme1737_chmod_fiwe(stwuct device*, stwuct attwibute*, umode_t);

static ssize_t set_pwm(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2
		*sensow_attw_2 = to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (fn) {
	case SYS_PWM:
		data->pwm[ix] = cwamp_vaw(vaw, 0, 255);
		dme1737_wwite(data, DME1737_WEG_PWM(ix), data->pwm[ix]);
		bweak;
	case SYS_PWM_FWEQ:
		data->pwm_fweq[ix] = PWM_FWEQ_TO_WEG(vaw, dme1737_wead(data,
						DME1737_WEG_PWM_FWEQ(ix)));
		dme1737_wwite(data, DME1737_WEG_PWM_FWEQ(ix),
			      data->pwm_fweq[ix]);
		bweak;
	case SYS_PWM_ENABWE:
		/* Onwy vawid fow pwm[1-3] */
		if (vaw < 0 || vaw > 2) {
			count = -EINVAW;
			dev_wawn(dev,
				 "PWM enabwe %wd not suppowted. Choose one of 0, 1, ow 2.\n",
				 vaw);
			goto exit;
		}
		/* Wefwesh the cache */
		data->pwm_config[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_CONFIG(ix));
		if (vaw == PWM_EN_FWOM_WEG(data->pwm_config[ix])) {
			/* Baiw out if no change */
			goto exit;
		}
		/* Do some housekeeping if we awe cuwwentwy in auto mode */
		if (PWM_EN_FWOM_WEG(data->pwm_config[ix]) == 2) {
			/* Save the cuwwent zone channew assignment */
			data->pwm_acz[ix] = PWM_ACZ_FWOM_WEG(
							data->pwm_config[ix]);
			/* Save the cuwwent wamp wate state and disabwe it */
			data->pwm_ww[ix > 0] = dme1737_wead(data,
						DME1737_WEG_PWM_WW(ix > 0));
			data->pwm_ww_en &= ~(1 << ix);
			if (PWM_WW_EN_FWOM_WEG(data->pwm_ww[ix > 0], ix)) {
				data->pwm_ww_en |= (1 << ix);
				data->pwm_ww[ix > 0] = PWM_WW_EN_TO_WEG(0, ix,
							data->pwm_ww[ix > 0]);
				dme1737_wwite(data,
					      DME1737_WEG_PWM_WW(ix > 0),
					      data->pwm_ww[ix > 0]);
			}
		}
		/* Set the new PWM mode */
		switch (vaw) {
		case 0:
			/* Change pewmissions of pwm[ix] to wead-onwy */
			dme1737_chmod_fiwe(dev, dme1737_pwm_chmod_attw[ix],
					   S_IWUGO);
			/* Tuwn fan fuwwy on */
			data->pwm_config[ix] = PWM_EN_TO_WEG(0,
							data->pwm_config[ix]);
			dme1737_wwite(data, DME1737_WEG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
			bweak;
		case 1:
			/* Tuwn on manuaw mode */
			data->pwm_config[ix] = PWM_EN_TO_WEG(1,
							data->pwm_config[ix]);
			dme1737_wwite(data, DME1737_WEG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
			/* Change pewmissions of pwm[ix] to wead-wwiteabwe */
			dme1737_chmod_fiwe(dev, dme1737_pwm_chmod_attw[ix],
					   S_IWUGO | S_IWUSW);
			bweak;
		case 2:
			/* Change pewmissions of pwm[ix] to wead-onwy */
			dme1737_chmod_fiwe(dev, dme1737_pwm_chmod_attw[ix],
					   S_IWUGO);
			/*
			 * Tuwn on auto mode using the saved zone channew
			 * assignment
			 */
			data->pwm_config[ix] = PWM_ACZ_TO_WEG(
							data->pwm_acz[ix],
							data->pwm_config[ix]);
			dme1737_wwite(data, DME1737_WEG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
			/* Enabwe PWM wamp wate if pweviouswy enabwed */
			if (data->pwm_ww_en & (1 << ix)) {
				data->pwm_ww[ix > 0] = PWM_WW_EN_TO_WEG(1, ix,
						dme1737_wead(data,
						DME1737_WEG_PWM_WW(ix > 0)));
				dme1737_wwite(data,
					      DME1737_WEG_PWM_WW(ix > 0),
					      data->pwm_ww[ix > 0]);
			}
			bweak;
		}
		bweak;
	case SYS_PWM_WAMP_WATE:
		/* Onwy vawid fow pwm[1-3] */
		/* Wefwesh the cache */
		data->pwm_config[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_CONFIG(ix));
		data->pwm_ww[ix > 0] = dme1737_wead(data,
						DME1737_WEG_PWM_WW(ix > 0));
		/* Set the wamp wate vawue */
		if (vaw > 0) {
			data->pwm_ww[ix > 0] = PWM_WW_TO_WEG(vaw, ix,
							data->pwm_ww[ix > 0]);
		}
		/*
		 * Enabwe/disabwe the featuwe onwy if the associated PWM
		 * output is in automatic mode.
		 */
		if (PWM_EN_FWOM_WEG(data->pwm_config[ix]) == 2) {
			data->pwm_ww[ix > 0] = PWM_WW_EN_TO_WEG(vaw > 0, ix,
							data->pwm_ww[ix > 0]);
		}
		dme1737_wwite(data, DME1737_WEG_PWM_WW(ix > 0),
			      data->pwm_ww[ix > 0]);
		bweak;
	case SYS_PWM_AUTO_CHANNEWS_ZONE:
		/* Onwy vawid fow pwm[1-3] */
		if (!(vaw == 1 || vaw == 2 || vaw == 4 ||
		      vaw == 6 || vaw == 7)) {
			count = -EINVAW;
			dev_wawn(dev,
				 "PWM auto channews zone %wd not suppowted. Choose one of 1, 2, 4, 6, "
				 "ow 7.\n", vaw);
			goto exit;
		}
		/* Wefwesh the cache */
		data->pwm_config[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_CONFIG(ix));
		if (PWM_EN_FWOM_WEG(data->pwm_config[ix]) == 2) {
			/*
			 * PWM is awweady in auto mode so update the temp
			 * channew assignment
			 */
			data->pwm_config[ix] = PWM_ACZ_TO_WEG(vaw,
						data->pwm_config[ix]);
			dme1737_wwite(data, DME1737_WEG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
		} ewse {
			/*
			 * PWM is not in auto mode so we save the temp
			 * channew assignment fow watew use
			 */
			data->pwm_acz[ix] = vaw;
		}
		bweak;
	case SYS_PWM_AUTO_PWM_MIN:
		/* Onwy vawid fow pwm[1-3] */
		/* Wefwesh the cache */
		data->pwm_min[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_MIN(ix));
		/*
		 * Thewe awe onwy 2 vawues suppowted fow the auto_pwm_min
		 * vawue: 0 ow auto_point1_pwm. So if the tempewatuwe dwops
		 * bewow the auto_point1_temp_hyst vawue, the fan eithew tuwns
		 * off ow wuns at auto_point1_pwm duty-cycwe.
		 */
		if (vaw > ((data->pwm_min[ix] + 1) / 2)) {
			data->pwm_ww[0] = PWM_OFF_TO_WEG(1, ix,
						dme1737_wead(data,
						DME1737_WEG_PWM_WW(0)));
		} ewse {
			data->pwm_ww[0] = PWM_OFF_TO_WEG(0, ix,
						dme1737_wead(data,
						DME1737_WEG_PWM_WW(0)));
		}
		dme1737_wwite(data, DME1737_WEG_PWM_WW(0),
			      data->pwm_ww[0]);
		bweak;
	case SYS_PWM_AUTO_POINT1_PWM:
		/* Onwy vawid fow pwm[1-3] */
		data->pwm_min[ix] = cwamp_vaw(vaw, 0, 255);
		dme1737_wwite(data, DME1737_WEG_PWM_MIN(ix),
			      data->pwm_min[ix]);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}
exit:
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * Miscewwaneous sysfs attwibutes
 * --------------------------------------------------------------------- */

static ssize_t vwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct dme1737_data *data = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%d\n", data->vwm);
}

static ssize_t vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 255)
		wetuwn -EINVAW;

	data->vwm = vaw;
	wetuwn count;
}

static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dme1737_data *data = dme1737_update_device(dev);

	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid, data->vwm));
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", data->name);
}

/* ---------------------------------------------------------------------
 * Sysfs device attwibute defines and stwucts
 * --------------------------------------------------------------------- */

/* Vowtages 0-7 */

#define SENSOW_DEVICE_ATTW_IN(ix) \
static SENSOW_DEVICE_ATTW_2(in##ix##_input, S_IWUGO, \
	show_in, NUWW, SYS_IN_INPUT, ix); \
static SENSOW_DEVICE_ATTW_2(in##ix##_min, S_IWUGO | S_IWUSW, \
	show_in, set_in, SYS_IN_MIN, ix); \
static SENSOW_DEVICE_ATTW_2(in##ix##_max, S_IWUGO | S_IWUSW, \
	show_in, set_in, SYS_IN_MAX, ix); \
static SENSOW_DEVICE_ATTW_2(in##ix##_awawm, S_IWUGO, \
	show_in, NUWW, SYS_IN_AWAWM, ix)

SENSOW_DEVICE_ATTW_IN(0);
SENSOW_DEVICE_ATTW_IN(1);
SENSOW_DEVICE_ATTW_IN(2);
SENSOW_DEVICE_ATTW_IN(3);
SENSOW_DEVICE_ATTW_IN(4);
SENSOW_DEVICE_ATTW_IN(5);
SENSOW_DEVICE_ATTW_IN(6);
SENSOW_DEVICE_ATTW_IN(7);

/* Tempewatuwes 1-3 */

#define SENSOW_DEVICE_ATTW_TEMP(ix) \
static SENSOW_DEVICE_ATTW_2(temp##ix##_input, S_IWUGO, \
	show_temp, NUWW, SYS_TEMP_INPUT, ix-1); \
static SENSOW_DEVICE_ATTW_2(temp##ix##_min, S_IWUGO | S_IWUSW, \
	show_temp, set_temp, SYS_TEMP_MIN, ix-1); \
static SENSOW_DEVICE_ATTW_2(temp##ix##_max, S_IWUGO | S_IWUSW, \
	show_temp, set_temp, SYS_TEMP_MAX, ix-1); \
static SENSOW_DEVICE_ATTW_2(temp##ix##_offset, S_IWUGO, \
	show_temp, set_temp, SYS_TEMP_OFFSET, ix-1); \
static SENSOW_DEVICE_ATTW_2(temp##ix##_awawm, S_IWUGO, \
	show_temp, NUWW, SYS_TEMP_AWAWM, ix-1); \
static SENSOW_DEVICE_ATTW_2(temp##ix##_fauwt, S_IWUGO, \
	show_temp, NUWW, SYS_TEMP_FAUWT, ix-1)

SENSOW_DEVICE_ATTW_TEMP(1);
SENSOW_DEVICE_ATTW_TEMP(2);
SENSOW_DEVICE_ATTW_TEMP(3);

/* Zones 1-3 */

#define SENSOW_DEVICE_ATTW_ZONE(ix) \
static SENSOW_DEVICE_ATTW_2(zone##ix##_auto_channews_temp, S_IWUGO, \
	show_zone, NUWW, SYS_ZONE_AUTO_CHANNEWS_TEMP, ix-1); \
static SENSOW_DEVICE_ATTW_2(zone##ix##_auto_point1_temp_hyst, S_IWUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT1_TEMP_HYST, ix-1); \
static SENSOW_DEVICE_ATTW_2(zone##ix##_auto_point1_temp, S_IWUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT1_TEMP, ix-1); \
static SENSOW_DEVICE_ATTW_2(zone##ix##_auto_point2_temp, S_IWUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT2_TEMP, ix-1); \
static SENSOW_DEVICE_ATTW_2(zone##ix##_auto_point3_temp, S_IWUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT3_TEMP, ix-1)

SENSOW_DEVICE_ATTW_ZONE(1);
SENSOW_DEVICE_ATTW_ZONE(2);
SENSOW_DEVICE_ATTW_ZONE(3);

/* Fans 1-4 */

#define SENSOW_DEVICE_ATTW_FAN_1TO4(ix) \
static SENSOW_DEVICE_ATTW_2(fan##ix##_input, S_IWUGO, \
	show_fan, NUWW, SYS_FAN_INPUT, ix-1); \
static SENSOW_DEVICE_ATTW_2(fan##ix##_min, S_IWUGO | S_IWUSW, \
	show_fan, set_fan, SYS_FAN_MIN, ix-1); \
static SENSOW_DEVICE_ATTW_2(fan##ix##_awawm, S_IWUGO, \
	show_fan, NUWW, SYS_FAN_AWAWM, ix-1); \
static SENSOW_DEVICE_ATTW_2(fan##ix##_type, S_IWUGO | S_IWUSW, \
	show_fan, set_fan, SYS_FAN_TYPE, ix-1)

SENSOW_DEVICE_ATTW_FAN_1TO4(1);
SENSOW_DEVICE_ATTW_FAN_1TO4(2);
SENSOW_DEVICE_ATTW_FAN_1TO4(3);
SENSOW_DEVICE_ATTW_FAN_1TO4(4);

/* Fans 5-6 */

#define SENSOW_DEVICE_ATTW_FAN_5TO6(ix) \
static SENSOW_DEVICE_ATTW_2(fan##ix##_input, S_IWUGO, \
	show_fan, NUWW, SYS_FAN_INPUT, ix-1); \
static SENSOW_DEVICE_ATTW_2(fan##ix##_min, S_IWUGO | S_IWUSW, \
	show_fan, set_fan, SYS_FAN_MIN, ix-1); \
static SENSOW_DEVICE_ATTW_2(fan##ix##_awawm, S_IWUGO, \
	show_fan, NUWW, SYS_FAN_AWAWM, ix-1); \
static SENSOW_DEVICE_ATTW_2(fan##ix##_max, S_IWUGO | S_IWUSW, \
	show_fan, set_fan, SYS_FAN_MAX, ix-1)

SENSOW_DEVICE_ATTW_FAN_5TO6(5);
SENSOW_DEVICE_ATTW_FAN_5TO6(6);

/* PWMs 1-3 */

#define SENSOW_DEVICE_ATTW_PWM_1TO3(ix) \
static SENSOW_DEVICE_ATTW_2(pwm##ix, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_fweq, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM_FWEQ, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_enabwe, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM_ENABWE, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_wamp_wate, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM_WAMP_WATE, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_auto_channews_zone, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM_AUTO_CHANNEWS_ZONE, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_auto_pwm_min, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM_AUTO_PWM_MIN, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_auto_point1_pwm, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM_AUTO_POINT1_PWM, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_auto_point2_pwm, S_IWUGO, \
	show_pwm, NUWW, SYS_PWM_AUTO_POINT2_PWM, ix-1)

SENSOW_DEVICE_ATTW_PWM_1TO3(1);
SENSOW_DEVICE_ATTW_PWM_1TO3(2);
SENSOW_DEVICE_ATTW_PWM_1TO3(3);

/* PWMs 5-6 */

#define SENSOW_DEVICE_ATTW_PWM_5TO6(ix) \
static SENSOW_DEVICE_ATTW_2(pwm##ix, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_fweq, S_IWUGO, \
	show_pwm, set_pwm, SYS_PWM_FWEQ, ix-1); \
static SENSOW_DEVICE_ATTW_2(pwm##ix##_enabwe, S_IWUGO, \
	show_pwm, NUWW, SYS_PWM_ENABWE, ix-1)

SENSOW_DEVICE_ATTW_PWM_5TO6(5);
SENSOW_DEVICE_ATTW_PWM_5TO6(6);

/* Misc */

static DEVICE_ATTW_WW(vwm);
static DEVICE_ATTW_WO(cpu0_vid);
static DEVICE_ATTW_WO(name);   /* fow ISA devices */

/*
 * This stwuct howds aww the attwibutes that awe awways pwesent and need to be
 * cweated unconditionawwy. The attwibutes that need modification of theiw
 * pewmissions awe cweated wead-onwy and wwite pewmissions awe added ow wemoved
 * on the fwy when wequiwed
 */
static stwuct attwibute *dme1737_attw[] = {
	/* Vowtages */
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	/* Tempewatuwes */
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,
	/* Zones */
	&sensow_dev_attw_zone1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_zone1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_zone1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_zone1_auto_channews_temp.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_channews_temp.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_gwoup = {
	.attws = dme1737_attw,
};

/*
 * The fowwowing stwuct howds temp offset attwibutes, which awe not avaiwabwe
 * in aww chips. The fowwowing chips suppowt them:
 * DME1737, SCH311x
 */
static stwuct attwibute *dme1737_temp_offset_attw[] = {
	&sensow_dev_attw_temp1_offset.dev_attw.attw,
	&sensow_dev_attw_temp2_offset.dev_attw.attw,
	&sensow_dev_attw_temp3_offset.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_temp_offset_gwoup = {
	.attws = dme1737_temp_offset_attw,
};

/*
 * The fowwowing stwuct howds VID wewated attwibutes, which awe not avaiwabwe
 * in aww chips. The fowwowing chips suppowt them:
 * DME1737
 */
static stwuct attwibute *dme1737_vid_attw[] = {
	&dev_attw_vwm.attw,
	&dev_attw_cpu0_vid.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_vid_gwoup = {
	.attws = dme1737_vid_attw,
};

/*
 * The fowwowing stwuct howds temp zone 3 wewated attwibutes, which awe not
 * avaiwabwe in aww chips. The fowwowing chips suppowt them:
 * DME1737, SCH311x, SCH5027
 */
static stwuct attwibute *dme1737_zone3_attw[] = {
	&sensow_dev_attw_zone3_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_zone3_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_zone3_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_zone3_auto_channews_temp.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_zone3_gwoup = {
	.attws = dme1737_zone3_attw,
};


/*
 * The fowwowing stwuct howds temp zone hystewesis wewated attwibutes, which
 * awe not avaiwabwe in aww chips. The fowwowing chips suppowt them:
 * DME1737, SCH311x
 */
static stwuct attwibute *dme1737_zone_hyst_attw[] = {
	&sensow_dev_attw_zone1_auto_point1_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_point1_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_zone3_auto_point1_temp_hyst.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_zone_hyst_gwoup = {
	.attws = dme1737_zone_hyst_attw,
};

/*
 * The fowwowing stwuct howds vowtage in7 wewated attwibutes, which
 * awe not avaiwabwe in aww chips. The fowwowing chips suppowt them:
 * SCH5127
 */
static stwuct attwibute *dme1737_in7_attw[] = {
	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in7_min.dev_attw.attw,
	&sensow_dev_attw_in7_max.dev_attw.attw,
	&sensow_dev_attw_in7_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_in7_gwoup = {
	.attws = dme1737_in7_attw,
};

/*
 * The fowwowing stwucts howd the PWM attwibutes, some of which awe optionaw.
 * Theiw cweation depends on the chip configuwation which is detewmined duwing
 * moduwe woad.
 */
static stwuct attwibute *dme1737_pwm1_attw[] = {
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm1_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_wamp_wate.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_channews_zone.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_pwm.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm2_attw[] = {
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm2_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_wamp_wate.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_channews_zone.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_pwm.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm3_attw[] = {
	&sensow_dev_attw_pwm3.dev_attw.attw,
	&sensow_dev_attw_pwm3_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_wamp_wate.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_channews_zone.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_pwm.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm5_attw[] = {
	&sensow_dev_attw_pwm5.dev_attw.attw,
	&sensow_dev_attw_pwm5_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm5_enabwe.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm6_attw[] = {
	&sensow_dev_attw_pwm6.dev_attw.attw,
	&sensow_dev_attw_pwm6_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm6_enabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_pwm_gwoup[] = {
	{ .attws = dme1737_pwm1_attw },
	{ .attws = dme1737_pwm2_attw },
	{ .attws = dme1737_pwm3_attw },
	{ .attws = NUWW },
	{ .attws = dme1737_pwm5_attw },
	{ .attws = dme1737_pwm6_attw },
};

/*
 * The fowwowing stwuct howds auto PWM min attwibutes, which awe not avaiwabwe
 * in aww chips. Theiw cweation depends on the chip type which is detewmined
 * duwing moduwe woad.
 */
static stwuct attwibute *dme1737_auto_pwm_min_attw[] = {
	&sensow_dev_attw_pwm1_auto_pwm_min.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_pwm_min.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_pwm_min.dev_attw.attw,
};

/*
 * The fowwowing stwucts howd the fan attwibutes, some of which awe optionaw.
 * Theiw cweation depends on the chip configuwation which is detewmined duwing
 * moduwe woad.
 */
static stwuct attwibute *dme1737_fan1_attw[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_type.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_fan2_attw[] = {
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_type.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_fan3_attw[] = {
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan3_awawm.dev_attw.attw,
	&sensow_dev_attw_fan3_type.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_fan4_attw[] = {
	&sensow_dev_attw_fan4_input.dev_attw.attw,
	&sensow_dev_attw_fan4_min.dev_attw.attw,
	&sensow_dev_attw_fan4_awawm.dev_attw.attw,
	&sensow_dev_attw_fan4_type.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_fan5_attw[] = {
	&sensow_dev_attw_fan5_input.dev_attw.attw,
	&sensow_dev_attw_fan5_min.dev_attw.attw,
	&sensow_dev_attw_fan5_awawm.dev_attw.attw,
	&sensow_dev_attw_fan5_max.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_fan6_attw[] = {
	&sensow_dev_attw_fan6_input.dev_attw.attw,
	&sensow_dev_attw_fan6_min.dev_attw.attw,
	&sensow_dev_attw_fan6_awawm.dev_attw.attw,
	&sensow_dev_attw_fan6_max.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_fan_gwoup[] = {
	{ .attws = dme1737_fan1_attw },
	{ .attws = dme1737_fan2_attw },
	{ .attws = dme1737_fan3_attw },
	{ .attws = dme1737_fan4_attw },
	{ .attws = dme1737_fan5_attw },
	{ .attws = dme1737_fan6_attw },
};

/*
 * The pewmissions of the fowwowing zone attwibutes awe changed to wead-
 * wwiteabwe if the chip is *not* wocked. Othewwise they stay wead-onwy.
 */
static stwuct attwibute *dme1737_zone_chmod_attw[] = {
	&sensow_dev_attw_zone1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_zone1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_zone1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_zone2_auto_point3_temp.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_zone_chmod_gwoup = {
	.attws = dme1737_zone_chmod_attw,
};


/*
 * The pewmissions of the fowwowing zone 3 attwibutes awe changed to wead-
 * wwiteabwe if the chip is *not* wocked. Othewwise they stay wead-onwy.
 */
static stwuct attwibute *dme1737_zone3_chmod_attw[] = {
	&sensow_dev_attw_zone3_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_zone3_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_zone3_auto_point3_temp.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_zone3_chmod_gwoup = {
	.attws = dme1737_zone3_chmod_attw,
};

/*
 * The pewmissions of the fowwowing PWM attwibutes awe changed to wead-
 * wwiteabwe if the chip is *not* wocked and the wespective PWM is avaiwabwe.
 * Othewwise they stay wead-onwy.
 */
static stwuct attwibute *dme1737_pwm1_chmod_attw[] = {
	&sensow_dev_attw_pwm1_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_wamp_wate.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_channews_zone.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm2_chmod_attw[] = {
	&sensow_dev_attw_pwm2_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_wamp_wate.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_channews_zone.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point1_pwm.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm3_chmod_attw[] = {
	&sensow_dev_attw_pwm3_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_wamp_wate.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_channews_zone.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point1_pwm.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm5_chmod_attw[] = {
	&sensow_dev_attw_pwm5.dev_attw.attw,
	&sensow_dev_attw_pwm5_fweq.dev_attw.attw,
	NUWW
};
static stwuct attwibute *dme1737_pwm6_chmod_attw[] = {
	&sensow_dev_attw_pwm6.dev_attw.attw,
	&sensow_dev_attw_pwm6_fweq.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup dme1737_pwm_chmod_gwoup[] = {
	{ .attws = dme1737_pwm1_chmod_attw },
	{ .attws = dme1737_pwm2_chmod_attw },
	{ .attws = dme1737_pwm3_chmod_attw },
	{ .attws = NUWW },
	{ .attws = dme1737_pwm5_chmod_attw },
	{ .attws = dme1737_pwm6_chmod_attw },
};

/*
 * Pwm[1-3] awe wead-wwiteabwe if the associated pwm is in manuaw mode and the
 * chip is not wocked. Othewwise they awe wead-onwy.
 */
static stwuct attwibute *dme1737_pwm_chmod_attw[] = {
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm3.dev_attw.attw,
};

/* ---------------------------------------------------------------------
 * Supew-IO functions
 * --------------------------------------------------------------------- */

static inwine void dme1737_sio_entew(int sio_cip)
{
	outb(0x55, sio_cip);
}

static inwine void dme1737_sio_exit(int sio_cip)
{
	outb(0xaa, sio_cip);
}

static inwine int dme1737_sio_inb(int sio_cip, int weg)
{
	outb(weg, sio_cip);
	wetuwn inb(sio_cip + 1);
}

static inwine void dme1737_sio_outb(int sio_cip, int weg, int vaw)
{
	outb(weg, sio_cip);
	outb(vaw, sio_cip + 1);
}

/* ---------------------------------------------------------------------
 * Device initiawization
 * --------------------------------------------------------------------- */

static int dme1737_i2c_get_featuwes(int, stwuct dme1737_data*);

static void dme1737_chmod_fiwe(stwuct device *dev,
			       stwuct attwibute *attw, umode_t mode)
{
	if (sysfs_chmod_fiwe(&dev->kobj, attw, mode)) {
		dev_wawn(dev, "Faiwed to change pewmissions of %s.\n",
			 attw->name);
	}
}

static void dme1737_chmod_gwoup(stwuct device *dev,
				const stwuct attwibute_gwoup *gwoup,
				umode_t mode)
{
	stwuct attwibute **attw;

	fow (attw = gwoup->attws; *attw; attw++)
		dme1737_chmod_fiwe(dev, *attw, mode);
}

static void dme1737_wemove_fiwes(stwuct device *dev)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	int ix;

	fow (ix = 0; ix < AWWAY_SIZE(dme1737_fan_gwoup); ix++) {
		if (data->has_featuwes & HAS_FAN(ix)) {
			sysfs_wemove_gwoup(&dev->kobj,
					   &dme1737_fan_gwoup[ix]);
		}
	}

	fow (ix = 0; ix < AWWAY_SIZE(dme1737_pwm_gwoup); ix++) {
		if (data->has_featuwes & HAS_PWM(ix)) {
			sysfs_wemove_gwoup(&dev->kobj,
					   &dme1737_pwm_gwoup[ix]);
			if ((data->has_featuwes & HAS_PWM_MIN) && ix < 3) {
				sysfs_wemove_fiwe(&dev->kobj,
						dme1737_auto_pwm_min_attw[ix]);
			}
		}
	}

	if (data->has_featuwes & HAS_TEMP_OFFSET)
		sysfs_wemove_gwoup(&dev->kobj, &dme1737_temp_offset_gwoup);
	if (data->has_featuwes & HAS_VID)
		sysfs_wemove_gwoup(&dev->kobj, &dme1737_vid_gwoup);
	if (data->has_featuwes & HAS_ZONE3)
		sysfs_wemove_gwoup(&dev->kobj, &dme1737_zone3_gwoup);
	if (data->has_featuwes & HAS_ZONE_HYST)
		sysfs_wemove_gwoup(&dev->kobj, &dme1737_zone_hyst_gwoup);
	if (data->has_featuwes & HAS_IN7)
		sysfs_wemove_gwoup(&dev->kobj, &dme1737_in7_gwoup);
	sysfs_wemove_gwoup(&dev->kobj, &dme1737_gwoup);

	if (!data->cwient)
		sysfs_wemove_fiwe(&dev->kobj, &dev_attw_name.attw);
}

static int dme1737_cweate_fiwes(stwuct device *dev)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	int eww, ix;

	/* Cweate a name attwibute fow ISA devices */
	if (!data->cwient) {
		eww = sysfs_cweate_fiwe(&dev->kobj, &dev_attw_name.attw);
		if (eww)
			goto exit;
	}

	/* Cweate standawd sysfs attwibutes */
	eww = sysfs_cweate_gwoup(&dev->kobj, &dme1737_gwoup);
	if (eww)
		goto exit_wemove;

	/* Cweate chip-dependent sysfs attwibutes */
	if (data->has_featuwes & HAS_TEMP_OFFSET) {
		eww = sysfs_cweate_gwoup(&dev->kobj,
					 &dme1737_temp_offset_gwoup);
		if (eww)
			goto exit_wemove;
	}
	if (data->has_featuwes & HAS_VID) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &dme1737_vid_gwoup);
		if (eww)
			goto exit_wemove;
	}
	if (data->has_featuwes & HAS_ZONE3) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &dme1737_zone3_gwoup);
		if (eww)
			goto exit_wemove;
	}
	if (data->has_featuwes & HAS_ZONE_HYST) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &dme1737_zone_hyst_gwoup);
		if (eww)
			goto exit_wemove;
	}
	if (data->has_featuwes & HAS_IN7) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &dme1737_in7_gwoup);
		if (eww)
			goto exit_wemove;
	}

	/* Cweate fan sysfs attwibutes */
	fow (ix = 0; ix < AWWAY_SIZE(dme1737_fan_gwoup); ix++) {
		if (data->has_featuwes & HAS_FAN(ix)) {
			eww = sysfs_cweate_gwoup(&dev->kobj,
						 &dme1737_fan_gwoup[ix]);
			if (eww)
				goto exit_wemove;
		}
	}

	/* Cweate PWM sysfs attwibutes */
	fow (ix = 0; ix < AWWAY_SIZE(dme1737_pwm_gwoup); ix++) {
		if (data->has_featuwes & HAS_PWM(ix)) {
			eww = sysfs_cweate_gwoup(&dev->kobj,
						 &dme1737_pwm_gwoup[ix]);
			if (eww)
				goto exit_wemove;
			if ((data->has_featuwes & HAS_PWM_MIN) && (ix < 3)) {
				eww = sysfs_cweate_fiwe(&dev->kobj,
						dme1737_auto_pwm_min_attw[ix]);
				if (eww)
					goto exit_wemove;
			}
		}
	}

	/*
	 * Infowm if the device is wocked. Othewwise change the pewmissions of
	 * sewected attwibutes fwom wead-onwy to wead-wwiteabwe.
	 */
	if (data->config & 0x02) {
		dev_info(dev,
			 "Device is wocked. Some attwibutes wiww be wead-onwy.\n");
	} ewse {
		/* Change pewmissions of zone sysfs attwibutes */
		dme1737_chmod_gwoup(dev, &dme1737_zone_chmod_gwoup,
				    S_IWUGO | S_IWUSW);

		/* Change pewmissions of chip-dependent sysfs attwibutes */
		if (data->has_featuwes & HAS_TEMP_OFFSET) {
			dme1737_chmod_gwoup(dev, &dme1737_temp_offset_gwoup,
					    S_IWUGO | S_IWUSW);
		}
		if (data->has_featuwes & HAS_ZONE3) {
			dme1737_chmod_gwoup(dev, &dme1737_zone3_chmod_gwoup,
					    S_IWUGO | S_IWUSW);
		}
		if (data->has_featuwes & HAS_ZONE_HYST) {
			dme1737_chmod_gwoup(dev, &dme1737_zone_hyst_gwoup,
					    S_IWUGO | S_IWUSW);
		}

		/* Change pewmissions of PWM sysfs attwibutes */
		fow (ix = 0; ix < AWWAY_SIZE(dme1737_pwm_chmod_gwoup); ix++) {
			if (data->has_featuwes & HAS_PWM(ix)) {
				dme1737_chmod_gwoup(dev,
						&dme1737_pwm_chmod_gwoup[ix],
						S_IWUGO | S_IWUSW);
				if ((data->has_featuwes & HAS_PWM_MIN) &&
				    ix < 3) {
					dme1737_chmod_fiwe(dev,
						dme1737_auto_pwm_min_attw[ix],
						S_IWUGO | S_IWUSW);
				}
			}
		}

		/* Change pewmissions of pwm[1-3] if in manuaw mode */
		fow (ix = 0; ix < 3; ix++) {
			if ((data->has_featuwes & HAS_PWM(ix)) &&
			    (PWM_EN_FWOM_WEG(data->pwm_config[ix]) == 1)) {
				dme1737_chmod_fiwe(dev,
						dme1737_pwm_chmod_attw[ix],
						S_IWUGO | S_IWUSW);
			}
		}
	}

	wetuwn 0;

exit_wemove:
	dme1737_wemove_fiwes(dev);
exit:
	wetuwn eww;
}

static int dme1737_init_device(stwuct device *dev)
{
	stwuct dme1737_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int ix;
	u8 weg;

	/* Point to the wight nominaw vowtages awway */
	data->in_nominaw = IN_NOMINAW(data->type);

	data->config = dme1737_wead(data, DME1737_WEG_CONFIG);
	/* Infowm if pawt is not monitowing/stawted */
	if (!(data->config & 0x01)) {
		if (!fowce_stawt) {
			dev_eww(dev,
				"Device is not monitowing. Use the fowce_stawt woad pawametew to ovewwide.\n");
			wetuwn -EFAUWT;
		}

		/* Fowce monitowing */
		data->config |= 0x01;
		dme1737_wwite(data, DME1737_WEG_CONFIG, data->config);
	}
	/* Infowm if pawt is not weady */
	if (!(data->config & 0x04)) {
		dev_eww(dev, "Device is not weady.\n");
		wetuwn -EFAUWT;
	}

	/*
	 * Detewmine which optionaw fan and pwm featuwes awe enabwed (onwy
	 * vawid fow I2C devices)
	 */
	if (cwient) {   /* I2C chip */
		data->config2 = dme1737_wead(data, DME1737_WEG_CONFIG2);
		/* Check if optionaw fan3 input is enabwed */
		if (data->config2 & 0x04)
			data->has_featuwes |= HAS_FAN(2);

		/*
		 * Fan4 and pwm3 awe onwy avaiwabwe if the cwient's I2C addwess
		 * is the defauwt 0x2e. Othewwise the I/Os associated with
		 * these functions awe used fow addw enabwe/sewect.
		 */
		if (cwient->addw == 0x2e)
			data->has_featuwes |= HAS_FAN(3) | HAS_PWM(2);

		/*
		 * Detewmine which of the optionaw fan[5-6] and pwm[5-6]
		 * featuwes awe enabwed. Fow this, we need to quewy the wuntime
		 * wegistews thwough the Supew-IO WPC intewface. Twy both
		 * config powts 0x2e and 0x4e.
		 */
		if (dme1737_i2c_get_featuwes(0x2e, data) &&
		    dme1737_i2c_get_featuwes(0x4e, data)) {
			dev_wawn(dev,
				 "Faiwed to quewy Supew-IO fow optionaw featuwes.\n");
		}
	}

	/* Fan[1-2] and pwm[1-2] awe pwesent in aww chips */
	data->has_featuwes |= HAS_FAN(0) | HAS_FAN(1) | HAS_PWM(0) | HAS_PWM(1);

	/* Chip-dependent featuwes */
	switch (data->type) {
	case dme1737:
		data->has_featuwes |= HAS_TEMP_OFFSET | HAS_VID | HAS_ZONE3 |
			HAS_ZONE_HYST | HAS_PWM_MIN;
		bweak;
	case sch311x:
		data->has_featuwes |= HAS_TEMP_OFFSET | HAS_ZONE3 |
			HAS_ZONE_HYST | HAS_PWM_MIN | HAS_FAN(2) | HAS_PWM(2);
		bweak;
	case sch5027:
		data->has_featuwes |= HAS_ZONE3;
		bweak;
	case sch5127:
		data->has_featuwes |= HAS_FAN(2) | HAS_PWM(2) | HAS_IN7;
		bweak;
	defauwt:
		bweak;
	}

	dev_info(dev,
		 "Optionaw featuwes: pwm3=%s, pwm5=%s, pwm6=%s, fan3=%s, fan4=%s, fan5=%s, fan6=%s.\n",
		 (data->has_featuwes & HAS_PWM(2)) ? "yes" : "no",
		 (data->has_featuwes & HAS_PWM(4)) ? "yes" : "no",
		 (data->has_featuwes & HAS_PWM(5)) ? "yes" : "no",
		 (data->has_featuwes & HAS_FAN(2)) ? "yes" : "no",
		 (data->has_featuwes & HAS_FAN(3)) ? "yes" : "no",
		 (data->has_featuwes & HAS_FAN(4)) ? "yes" : "no",
		 (data->has_featuwes & HAS_FAN(5)) ? "yes" : "no");

	weg = dme1737_wead(data, DME1737_WEG_TACH_PWM);
	/* Infowm if fan-to-pwm mapping diffews fwom the defauwt */
	if (cwient && weg != 0xa4) {   /* I2C chip */
		dev_wawn(dev,
			 "Non-standawd fan to pwm mapping: fan1->pwm%d, fan2->pwm%d, fan3->pwm%d, fan4->pwm%d. %s\n",
			 (weg & 0x03) + 1, ((weg >> 2) & 0x03) + 1,
			 ((weg >> 4) & 0x03) + 1, ((weg >> 6) & 0x03) + 1,
			 DO_WEPOWT);
	} ewse if (!cwient && weg != 0x24) {   /* ISA chip */
		dev_wawn(dev,
			 "Non-standawd fan to pwm mapping: fan1->pwm%d, fan2->pwm%d, fan3->pwm%d. %s\n",
			 (weg & 0x03) + 1, ((weg >> 2) & 0x03) + 1,
			 ((weg >> 4) & 0x03) + 1, DO_WEPOWT);
	}

	/*
	 * Switch pwm[1-3] to manuaw mode if they awe cuwwentwy disabwed and
	 * set the duty-cycwes to 0% (which is identicaw to the PWMs being
	 * disabwed).
	 */
	if (!(data->config & 0x02)) {
		fow (ix = 0; ix < 3; ix++) {
			data->pwm_config[ix] = dme1737_wead(data,
						DME1737_WEG_PWM_CONFIG(ix));
			if ((data->has_featuwes & HAS_PWM(ix)) &&
			    (PWM_EN_FWOM_WEG(data->pwm_config[ix]) == -1)) {
				dev_info(dev,
					 "Switching pwm%d to manuaw mode.\n",
					 ix + 1);
				data->pwm_config[ix] = PWM_EN_TO_WEG(1,
							data->pwm_config[ix]);
				dme1737_wwite(data, DME1737_WEG_PWM(ix), 0);
				dme1737_wwite(data,
					      DME1737_WEG_PWM_CONFIG(ix),
					      data->pwm_config[ix]);
			}
		}
	}

	/* Initiawize the defauwt PWM auto channews zone (acz) assignments */
	data->pwm_acz[0] = 1;	/* pwm1 -> zone1 */
	data->pwm_acz[1] = 2;	/* pwm2 -> zone2 */
	data->pwm_acz[2] = 4;	/* pwm3 -> zone3 */

	/* Set VWM */
	if (data->has_featuwes & HAS_VID)
		data->vwm = vid_which_vwm();

	wetuwn 0;
}

/* ---------------------------------------------------------------------
 * I2C device detection and wegistwation
 * --------------------------------------------------------------------- */

static stwuct i2c_dwivew dme1737_i2c_dwivew;

static int dme1737_i2c_get_featuwes(int sio_cip, stwuct dme1737_data *data)
{
	int eww = 0, weg;
	u16 addw;

	dme1737_sio_entew(sio_cip);

	/*
	 * Check device ID
	 * We cuwwentwy know about two kinds of DME1737 and SCH5027.
	 */
	weg = fowce_id ? fowce_id : dme1737_sio_inb(sio_cip, 0x20);
	if (!(weg == DME1737_ID_1 || weg == DME1737_ID_2 ||
	      weg == SCH5027_ID)) {
		eww = -ENODEV;
		goto exit;
	}

	/* Sewect wogicaw device A (wuntime wegistews) */
	dme1737_sio_outb(sio_cip, 0x07, 0x0a);

	/* Get the base addwess of the wuntime wegistews */
	addw = (dme1737_sio_inb(sio_cip, 0x60) << 8) |
		dme1737_sio_inb(sio_cip, 0x61);
	if (!addw) {
		eww = -ENODEV;
		goto exit;
	}

	/*
	 * Wead the wuntime wegistews to detewmine which optionaw featuwes
	 * awe enabwed and avaiwabwe. Bits [3:2] of wegistews 0x43-0x46 awe set
	 * to '10' if the wespective featuwe is enabwed.
	 */
	if ((inb(addw + 0x43) & 0x0c) == 0x08) /* fan6 */
		data->has_featuwes |= HAS_FAN(5);
	if ((inb(addw + 0x44) & 0x0c) == 0x08) /* pwm6 */
		data->has_featuwes |= HAS_PWM(5);
	if ((inb(addw + 0x45) & 0x0c) == 0x08) /* fan5 */
		data->has_featuwes |= HAS_FAN(4);
	if ((inb(addw + 0x46) & 0x0c) == 0x08) /* pwm5 */
		data->has_featuwes |= HAS_PWM(4);

exit:
	dme1737_sio_exit(sio_cip);

	wetuwn eww;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int dme1737_i2c_detect(stwuct i2c_cwient *cwient,
			      stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &adaptew->dev;
	u8 company, vewstep = 0;
	const chaw *name;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	company = i2c_smbus_wead_byte_data(cwient, DME1737_WEG_COMPANY);
	vewstep = i2c_smbus_wead_byte_data(cwient, DME1737_WEG_VEWSTEP);

	if (company == DME1737_COMPANY_SMSC &&
	    vewstep == SCH5027_VEWSTEP) {
		name = "sch5027";
	} ewse if (company == DME1737_COMPANY_SMSC &&
		   (vewstep & DME1737_VEWSTEP_MASK) == DME1737_VEWSTEP) {
		name = "dme1737";
	} ewse {
		wetuwn -ENODEV;
	}

	dev_info(dev, "Found a %s chip at 0x%02x (wev 0x%02x).\n",
		 vewstep == SCH5027_VEWSTEP ? "SCH5027" : "DME1737",
		 cwient->addw, vewstep);
	stwscpy(info->type, name, I2C_NAME_SIZE);

	wetuwn 0;
}

static const stwuct i2c_device_id dme1737_id[];

static int dme1737_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct dme1737_data *data;
	stwuct device *dev = &cwient->dev;
	int eww;

	data = devm_kzawwoc(dev, sizeof(stwuct dme1737_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->type = i2c_match_id(dme1737_id, cwient)->dwivew_data;
	data->cwient = cwient;
	data->name = cwient->name;
	mutex_init(&data->update_wock);

	/* Initiawize the DME1737 chip */
	eww = dme1737_init_device(dev);
	if (eww) {
		dev_eww(dev, "Faiwed to initiawize device.\n");
		wetuwn eww;
	}

	/* Cweate sysfs fiwes */
	eww = dme1737_cweate_fiwes(dev);
	if (eww) {
		dev_eww(dev, "Faiwed to cweate sysfs fiwes.\n");
		wetuwn eww;
	}

	/* Wegistew device */
	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		dev_eww(dev, "Faiwed to wegistew device.\n");
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_wemove;
	}

	wetuwn 0;

exit_wemove:
	dme1737_wemove_fiwes(dev);
	wetuwn eww;
}

static void dme1737_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct dme1737_data *data = i2c_get_cwientdata(cwient);

	hwmon_device_unwegistew(data->hwmon_dev);
	dme1737_wemove_fiwes(&cwient->dev);
}

static const stwuct i2c_device_id dme1737_id[] = {
	{ "dme1737", dme1737 },
	{ "sch5027", sch5027 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, dme1737_id);

static stwuct i2c_dwivew dme1737_i2c_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "dme1737",
	},
	.pwobe = dme1737_i2c_pwobe,
	.wemove = dme1737_i2c_wemove,
	.id_tabwe = dme1737_id,
	.detect = dme1737_i2c_detect,
	.addwess_wist = nowmaw_i2c,
};

/* ---------------------------------------------------------------------
 * ISA device detection and wegistwation
 * --------------------------------------------------------------------- */

static int __init dme1737_isa_detect(int sio_cip, unsigned showt *addw)
{
	int eww = 0, weg;
	unsigned showt base_addw;

	dme1737_sio_entew(sio_cip);

	/*
	 * Check device ID
	 * We cuwwentwy know about SCH3112, SCH3114, SCH3116, and SCH5127
	 */
	weg = fowce_id ? fowce_id : dme1737_sio_inb(sio_cip, 0x20);
	if (!(weg == SCH3112_ID || weg == SCH3114_ID || weg == SCH3116_ID ||
	      weg == SCH5127_ID)) {
		eww = -ENODEV;
		goto exit;
	}

	/* Sewect wogicaw device A (wuntime wegistews) */
	dme1737_sio_outb(sio_cip, 0x07, 0x0a);

	/* Get the base addwess of the wuntime wegistews */
	base_addw = (dme1737_sio_inb(sio_cip, 0x60) << 8) |
		     dme1737_sio_inb(sio_cip, 0x61);
	if (!base_addw) {
		pw_eww("Base addwess not set\n");
		eww = -ENODEV;
		goto exit;
	}

	/*
	 * Access to the hwmon wegistews is thwough an index/data wegistew
	 * paiw wocated at offset 0x70/0x71.
	 */
	*addw = base_addw + 0x70;

exit:
	dme1737_sio_exit(sio_cip);
	wetuwn eww;
}

static int __init dme1737_isa_device_add(unsigned showt addw)
{
	stwuct wesouwce wes = {
		.stawt	= addw,
		.end	= addw + DME1737_EXTENT - 1,
		.name	= "dme1737",
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	eww = acpi_check_wesouwce_confwict(&wes);
	if (eww)
		goto exit;

	pdev = pwatfowm_device_awwoc("dme1737", addw);
	if (!pdev) {
		pw_eww("Faiwed to awwocate device\n");
		eww = -ENOMEM;
		goto exit;
	}

	eww = pwatfowm_device_add_wesouwces(pdev, &wes, 1);
	if (eww) {
		pw_eww("Faiwed to add device wesouwce (eww = %d)\n", eww);
		goto exit_device_put;
	}

	eww = pwatfowm_device_add(pdev);
	if (eww) {
		pw_eww("Faiwed to add device (eww = %d)\n", eww);
		goto exit_device_put;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(pdev);
	pdev = NUWW;
exit:
	wetuwn eww;
}

static int dme1737_isa_pwobe(stwuct pwatfowm_device *pdev)
{
	u8 company, device;
	stwuct wesouwce *wes;
	stwuct dme1737_data *data;
	stwuct device *dev = &pdev->dev;
	int eww;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(dev, wes->stawt, DME1737_EXTENT, "dme1737")) {
		dev_eww(dev, "Faiwed to wequest wegion 0x%04x-0x%04x.\n",
			(unsigned showt)wes->stawt,
			(unsigned showt)wes->stawt + DME1737_EXTENT - 1);
		wetuwn -EBUSY;
	}

	data = devm_kzawwoc(dev, sizeof(stwuct dme1737_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->addw = wes->stawt;
	pwatfowm_set_dwvdata(pdev, data);

	/* Skip chip detection if moduwe is woaded with fowce_id pawametew */
	switch (fowce_id) {
	case SCH3112_ID:
	case SCH3114_ID:
	case SCH3116_ID:
		data->type = sch311x;
		bweak;
	case SCH5127_ID:
		data->type = sch5127;
		bweak;
	defauwt:
		company = dme1737_wead(data, DME1737_WEG_COMPANY);
		device = dme1737_wead(data, DME1737_WEG_DEVICE);

		if ((company == DME1737_COMPANY_SMSC) &&
		    (device == SCH311X_DEVICE)) {
			data->type = sch311x;
		} ewse if ((company == DME1737_COMPANY_SMSC) &&
			   (device == SCH5127_DEVICE)) {
			data->type = sch5127;
		} ewse {
			wetuwn -ENODEV;
		}
	}

	if (data->type == sch5127)
		data->name = "sch5127";
	ewse
		data->name = "sch311x";

	/* Initiawize the mutex */
	mutex_init(&data->update_wock);

	dev_info(dev, "Found a %s chip at 0x%04x\n",
		 data->type == sch5127 ? "SCH5127" : "SCH311x", data->addw);

	/* Initiawize the chip */
	eww = dme1737_init_device(dev);
	if (eww) {
		dev_eww(dev, "Faiwed to initiawize device.\n");
		wetuwn eww;
	}

	/* Cweate sysfs fiwes */
	eww = dme1737_cweate_fiwes(dev);
	if (eww) {
		dev_eww(dev, "Faiwed to cweate sysfs fiwes.\n");
		wetuwn eww;
	}

	/* Wegistew device */
	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		dev_eww(dev, "Faiwed to wegistew device.\n");
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_wemove_fiwes;
	}

	wetuwn 0;

exit_wemove_fiwes:
	dme1737_wemove_fiwes(dev);
	wetuwn eww;
}

static void dme1737_isa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dme1737_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	dme1737_wemove_fiwes(&pdev->dev);
}

static stwuct pwatfowm_dwivew dme1737_isa_dwivew = {
	.dwivew = {
		.name = "dme1737",
	},
	.pwobe = dme1737_isa_pwobe,
	.wemove_new = dme1737_isa_wemove,
};

/* ---------------------------------------------------------------------
 * Moduwe initiawization and cweanup
 * --------------------------------------------------------------------- */

static int __init dme1737_init(void)
{
	int eww;
	unsigned showt addw;

	eww = i2c_add_dwivew(&dme1737_i2c_dwivew);
	if (eww)
		goto exit;

	if (dme1737_isa_detect(0x2e, &addw) &&
	    dme1737_isa_detect(0x4e, &addw) &&
	    (!pwobe_aww_addw ||
	     (dme1737_isa_detect(0x162e, &addw) &&
	      dme1737_isa_detect(0x164e, &addw)))) {
		/* Wetuwn 0 if we didn't find an ISA device */
		wetuwn 0;
	}

	eww = pwatfowm_dwivew_wegistew(&dme1737_isa_dwivew);
	if (eww)
		goto exit_dew_i2c_dwivew;

	/* Sets gwobaw pdev as a side effect */
	eww = dme1737_isa_device_add(addw);
	if (eww)
		goto exit_dew_isa_dwivew;

	wetuwn 0;

exit_dew_isa_dwivew:
	pwatfowm_dwivew_unwegistew(&dme1737_isa_dwivew);
exit_dew_i2c_dwivew:
	i2c_dew_dwivew(&dme1737_i2c_dwivew);
exit:
	wetuwn eww;
}

static void __exit dme1737_exit(void)
{
	if (pdev) {
		pwatfowm_device_unwegistew(pdev);
		pwatfowm_dwivew_unwegistew(&dme1737_isa_dwivew);
	}

	i2c_dew_dwivew(&dme1737_i2c_dwivew);
}

MODUWE_AUTHOW("Juewg Haefwigew <juewgh@gmaiw.com>");
MODUWE_DESCWIPTION("DME1737 sensows");
MODUWE_WICENSE("GPW");

moduwe_init(dme1737_init);
moduwe_exit(dme1737_exit);
