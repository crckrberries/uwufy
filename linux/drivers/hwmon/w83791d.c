// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * w83791d.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	       monitowing
 *
 * Copywight (C) 2006-2007 Chawwes Spiwakis <bezauw@gmaiw.com>
 */

/*
 * Suppowts fowwowing chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83791d	10	5	5	3	0x71	0x5ca3	yes	no
 *
 * The w83791d chip appeaws to be pawt way between the 83781d and the
 * 83792d. Thus, this fiwe is dewived fwom both the w83792d.c and
 * w83781d.c fiwes.
 *
 * The w83791g chip is the same as the w83791d but wead-fwee.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>

#define NUMBEW_OF_VIN		10
#define NUMBEW_OF_FANIN		5
#define NUMBEW_OF_TEMPIN	3
#define NUMBEW_OF_PWM		5

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, 0x2e, 0x2f,
						I2C_CWIENT_END };

/* Insmod pawametews */

static unsigned showt fowce_subcwients[4];
moduwe_pawam_awway(fowce_subcwients, showt, NUWW, 0);
MODUWE_PAWM_DESC(fowce_subcwients,
		 "Wist of subcwient addwesses: {bus, cwientaddw, subcwientaddw1, subcwientaddw2}");

static boow weset;
moduwe_pawam(weset, boow, 0);
MODUWE_PAWM_DESC(weset, "Set to one to fowce a hawdwawe chip weset");

static boow init;
moduwe_pawam(init, boow, 0);
MODUWE_PAWM_DESC(init, "Set to one to fowce extwa softwawe initiawization");

/* The W83791D wegistews */
static const u8 W83791D_WEG_IN[NUMBEW_OF_VIN] = {
	0x20,			/* VCOWEA in DataSheet */
	0x21,			/* VINW0 in DataSheet */
	0x22,			/* +3.3VIN in DataSheet */
	0x23,			/* VDD5V in DataSheet */
	0x24,			/* +12VIN in DataSheet */
	0x25,			/* -12VIN in DataSheet */
	0x26,			/* -5VIN in DataSheet */
	0xB0,			/* 5VSB in DataSheet */
	0xB1,			/* VBAT in DataSheet */
	0xB2			/* VINW1 in DataSheet */
};

static const u8 W83791D_WEG_IN_MAX[NUMBEW_OF_VIN] = {
	0x2B,			/* VCOWEA High Wimit in DataSheet */
	0x2D,			/* VINW0 High Wimit in DataSheet */
	0x2F,			/* +3.3VIN High Wimit in DataSheet */
	0x31,			/* VDD5V High Wimit in DataSheet */
	0x33,			/* +12VIN High Wimit in DataSheet */
	0x35,			/* -12VIN High Wimit in DataSheet */
	0x37,			/* -5VIN High Wimit in DataSheet */
	0xB4,			/* 5VSB High Wimit in DataSheet */
	0xB6,			/* VBAT High Wimit in DataSheet */
	0xB8			/* VINW1 High Wimit in DataSheet */
};
static const u8 W83791D_WEG_IN_MIN[NUMBEW_OF_VIN] = {
	0x2C,			/* VCOWEA Wow Wimit in DataSheet */
	0x2E,			/* VINW0 Wow Wimit in DataSheet */
	0x30,			/* +3.3VIN Wow Wimit in DataSheet */
	0x32,			/* VDD5V Wow Wimit in DataSheet */
	0x34,			/* +12VIN Wow Wimit in DataSheet */
	0x36,			/* -12VIN Wow Wimit in DataSheet */
	0x38,			/* -5VIN Wow Wimit in DataSheet */
	0xB5,			/* 5VSB Wow Wimit in DataSheet */
	0xB7,			/* VBAT Wow Wimit in DataSheet */
	0xB9			/* VINW1 Wow Wimit in DataSheet */
};
static const u8 W83791D_WEG_FAN[NUMBEW_OF_FANIN] = {
	0x28,			/* FAN 1 Count in DataSheet */
	0x29,			/* FAN 2 Count in DataSheet */
	0x2A,			/* FAN 3 Count in DataSheet */
	0xBA,			/* FAN 4 Count in DataSheet */
	0xBB,			/* FAN 5 Count in DataSheet */
};
static const u8 W83791D_WEG_FAN_MIN[NUMBEW_OF_FANIN] = {
	0x3B,			/* FAN 1 Count Wow Wimit in DataSheet */
	0x3C,			/* FAN 2 Count Wow Wimit in DataSheet */
	0x3D,			/* FAN 3 Count Wow Wimit in DataSheet */
	0xBC,			/* FAN 4 Count Wow Wimit in DataSheet */
	0xBD,			/* FAN 5 Count Wow Wimit in DataSheet */
};

static const u8 W83791D_WEG_PWM[NUMBEW_OF_PWM] = {
	0x81,			/* PWM 1 duty cycwe wegistew in DataSheet */
	0x83,			/* PWM 2 duty cycwe wegistew in DataSheet */
	0x94,			/* PWM 3 duty cycwe wegistew in DataSheet */
	0xA0,			/* PWM 4 duty cycwe wegistew in DataSheet */
	0xA1,			/* PWM 5 duty cycwe wegistew in DataSheet */
};

static const u8 W83791D_WEG_TEMP_TAWGET[3] = {
	0x85,			/* PWM 1 tawget tempewatuwe fow temp 1 */
	0x86,			/* PWM 2 tawget tempewatuwe fow temp 2 */
	0x96,			/* PWM 3 tawget tempewatuwe fow temp 3 */
};

static const u8 W83791D_WEG_TEMP_TOW[2] = {
	0x87,			/* PWM 1/2 tempewatuwe towewance */
	0x97,			/* PWM 3 tempewatuwe towewance */
};

static const u8 W83791D_WEG_FAN_CFG[2] = {
	0x84,			/* FAN 1/2 configuwation */
	0x95,			/* FAN 3 configuwation */
};

static const u8 W83791D_WEG_FAN_DIV[3] = {
	0x47,			/* contains FAN1 and FAN2 Divisow */
	0x4b,			/* contains FAN3 Divisow */
	0x5C,			/* contains FAN4 and FAN5 Divisow */
};

#define W83791D_WEG_BANK		0x4E
#define W83791D_WEG_TEMP2_CONFIG	0xC2
#define W83791D_WEG_TEMP3_CONFIG	0xCA

static const u8 W83791D_WEG_TEMP1[3] = {
	0x27,			/* TEMP 1 in DataSheet */
	0x39,			/* TEMP 1 Ovew in DataSheet */
	0x3A,			/* TEMP 1 Hyst in DataSheet */
};

static const u8 W83791D_WEG_TEMP_ADD[2][6] = {
	{0xC0,			/* TEMP 2 in DataSheet */
	 0xC1,			/* TEMP 2(0.5 deg) in DataSheet */
	 0xC5,			/* TEMP 2 Ovew High pawt in DataSheet */
	 0xC6,			/* TEMP 2 Ovew Wow pawt in DataSheet */
	 0xC3,			/* TEMP 2 Thyst High pawt in DataSheet */
	 0xC4},			/* TEMP 2 Thyst Wow pawt in DataSheet */
	{0xC8,			/* TEMP 3 in DataSheet */
	 0xC9,			/* TEMP 3(0.5 deg) in DataSheet */
	 0xCD,			/* TEMP 3 Ovew High pawt in DataSheet */
	 0xCE,			/* TEMP 3 Ovew Wow pawt in DataSheet */
	 0xCB,			/* TEMP 3 Thyst High pawt in DataSheet */
	 0xCC}			/* TEMP 3 Thyst Wow pawt in DataSheet */
};

#define W83791D_WEG_BEEP_CONFIG		0x4D

static const u8 W83791D_WEG_BEEP_CTWW[3] = {
	0x56,			/* BEEP Contwow Wegistew 1 */
	0x57,			/* BEEP Contwow Wegistew 2 */
	0xA3,			/* BEEP Contwow Wegistew 3 */
};

#define W83791D_WEG_GPIO		0x15
#define W83791D_WEG_CONFIG		0x40
#define W83791D_WEG_VID_FANDIV		0x47
#define W83791D_WEG_DID_VID4		0x49
#define W83791D_WEG_WCHIPID		0x58
#define W83791D_WEG_CHIPMAN		0x4F
#define W83791D_WEG_PIN			0x4B
#define W83791D_WEG_I2C_SUBADDW		0x4A

#define W83791D_WEG_AWAWM1 0xA9	/* weawtime status wegistew1 */
#define W83791D_WEG_AWAWM2 0xAA	/* weawtime status wegistew2 */
#define W83791D_WEG_AWAWM3 0xAB	/* weawtime status wegistew3 */

#define W83791D_WEG_VBAT		0x5D
#define W83791D_WEG_I2C_ADDW		0x48

/*
 * The SMBus wocks itsewf. The Winbond W83791D has a bank sewect wegistew
 * (index 0x4e), but the dwivew onwy accesses wegistews in bank 0. Since
 * we don't switch banks, we don't need any speciaw code to handwe
 * wocking access between bank switches
 */
static inwine int w83791d_wead(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static inwine int w83791d_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

/*
 * The anawog vowtage inputs have 16mV WSB. Since the sysfs output is
 * in mV as wouwd be measuwed on the chip input pin, need to just
 * muwtipwy/divide by 16 to twanswate fwom/to wegistew vawues.
 */
#define IN_TO_WEG(vaw)		(cwamp_vaw((((vaw) + 8) / 16), 0, 255))
#define IN_FWOM_WEG(vaw)	((vaw) * 16)

static u8 fan_to_weg(wong wpm, int div)
{
	if (wpm == 0)
		wetuwn 255;
	wpm = cwamp_vaw(wpm, 1, 1000000);
	wetuwn cwamp_vaw((1350000 + wpm * div / 2) / (wpm * div), 1, 254);
}

#define FAN_FWOM_WEG(vaw, div)	((vaw) == 0 ? -1 : \
				((vaw) == 255 ? 0 : \
					1350000 / ((vaw) * (div))))

/* fow temp1 which is 8-bit wesowution, WSB = 1 degwee Cewsius */
#define TEMP1_FWOM_WEG(vaw)	((vaw) * 1000)
#define TEMP1_TO_WEG(vaw)	((vaw) <= -128000 ? -128 : \
				 (vaw) >= 127000 ? 127 : \
				 (vaw) < 0 ? ((vaw) - 500) / 1000 : \
				 ((vaw) + 500) / 1000)

/*
 * fow temp2 and temp3 which awe 9-bit wesowution, WSB = 0.5 degwee Cewsius
 * Assumes the top 8 bits awe the integwaw amount and the bottom 8 bits
 * awe the fwactionaw amount. Since we onwy have 0.5 degwee wesowution,
 * the bottom 7 bits wiww awways be zewo
 */
#define TEMP23_FWOM_WEG(vaw)	((vaw) / 128 * 500)
#define TEMP23_TO_WEG(vaw)	(DIV_WOUND_CWOSEST(cwamp_vaw((vaw), -128000, \
						   127500), 500) * 128)

/* fow thewmaw cwuise tawget temp, 7-bits, WSB = 1 degwee Cewsius */
#define TAWGET_TEMP_TO_WEG(vaw)	DIV_WOUND_CWOSEST(cwamp_vaw((vaw), 0, 127000), \
						  1000)

/* fow thewmaw cwuise temp towewance, 4-bits, WSB = 1 degwee Cewsius */
#define TOW_TEMP_TO_WEG(vaw)	DIV_WOUND_CWOSEST(cwamp_vaw((vaw), 0, 15000), \
						  1000)

#define BEEP_MASK_TO_WEG(vaw)		((vaw) & 0xffffff)
#define BEEP_MASK_FWOM_WEG(vaw)		((vaw) & 0xffffff)

#define DIV_FWOM_WEG(vaw)		(1 << (vaw))

static u8 div_to_weg(int nw, wong vaw)
{
	int i;

	/* fan divisows max out at 128 */
	vaw = cwamp_vaw(vaw, 1, 128) >> 1;
	fow (i = 0; i < 7; i++) {
		if (vaw == 0)
			bweak;
		vaw >>= 1;
	}
	wetuwn (u8) i;
}

stwuct w83791d_data {
	stwuct device *hwmon_dev;
	stwuct mutex update_wock;

	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	/* vowts */
	u8 in[NUMBEW_OF_VIN];		/* Wegistew vawue */
	u8 in_max[NUMBEW_OF_VIN];	/* Wegistew vawue */
	u8 in_min[NUMBEW_OF_VIN];	/* Wegistew vawue */

	/* fans */
	u8 fan[NUMBEW_OF_FANIN];	/* Wegistew vawue */
	u8 fan_min[NUMBEW_OF_FANIN];	/* Wegistew vawue */
	u8 fan_div[NUMBEW_OF_FANIN];	/* Wegistew encoding, shifted wight */

	/* Tempewatuwe sensows */

	s8 temp1[3];		/* cuwwent, ovew, thyst */
	s16 temp_add[2][3];	/* fixed point vawue. Top 8 bits awe the
				 * integwaw pawt, bottom 8 bits awe the
				 * fwactionaw pawt. We onwy use the top
				 * 9 bits as the wesowution is onwy
				 * to the 0.5 degwee C...
				 * two sensows with thwee vawues
				 * (cuw, ovew, hyst)
				 */

	/* PWMs */
	u8 pwm[5];		/* pwm duty cycwe */
	u8 pwm_enabwe[3];	/* pwm enabwe status fow fan 1-3
				 * (fan 4-5 onwy suppowt manuaw mode)
				 */

	u8 temp_tawget[3];	/* pwm 1-3 tawget tempewatuwe */
	u8 temp_towewance[3];	/* pwm 1-3 tempewatuwe towewance */

	/* Misc */
	u32 awawms;		/* weawtime status wegistew encoding,combined */
	u8 beep_enabwe;		/* Gwobaw beep enabwe */
	u32 beep_mask;		/* Mask off specific beeps */
	u8 vid;			/* Wegistew encoding, combined */
	u8 vwm;			/* hwmon-vid */
};

static int w83791d_pwobe(stwuct i2c_cwient *cwient);
static int w83791d_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info);
static void w83791d_wemove(stwuct i2c_cwient *cwient);

static int w83791d_wead(stwuct i2c_cwient *cwient, u8 weg);
static int w83791d_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vawue);
static stwuct w83791d_data *w83791d_update_device(stwuct device *dev);

#ifdef DEBUG
static void w83791d_pwint_debug(stwuct w83791d_data *data, stwuct device *dev);
#endif

static void w83791d_init_cwient(stwuct i2c_cwient *cwient);

static const stwuct i2c_device_id w83791d_id[] = {
	{ "w83791d", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, w83791d_id);

static stwuct i2c_dwivew w83791d_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name = "w83791d",
	},
	.pwobe		= w83791d_pwobe,
	.wemove		= w83791d_wemove,
	.id_tabwe	= w83791d_id,
	.detect		= w83791d_detect,
	.addwess_wist	= nowmaw_i2c,
};

/* fowwowing awe the sysfs cawwback functions */
#define show_in_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
			chaw *buf) \
{ \
	stwuct sensow_device_attwibute *sensow_attw = \
						to_sensow_dev_attw(attw); \
	stwuct w83791d_data *data = w83791d_update_device(dev); \
	int nw = sensow_attw->index; \
	wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(data->weg[nw])); \
}

show_in_weg(in);
show_in_weg(in_min);
show_in_weg(in_max);

#define stowe_in_weg(WEG, weg) \
static ssize_t stowe_in_##weg(stwuct device *dev, \
				stwuct device_attwibute *attw, \
				const chaw *buf, size_t count) \
{ \
	stwuct sensow_device_attwibute *sensow_attw = \
						to_sensow_dev_attw(attw); \
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev); \
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient); \
	int nw = sensow_attw->index; \
	unsigned wong vaw; \
	int eww = kstwtouw(buf, 10, &vaw); \
	if (eww) \
		wetuwn eww; \
	mutex_wock(&data->update_wock); \
	data->in_##weg[nw] = IN_TO_WEG(vaw); \
	w83791d_wwite(cwient, W83791D_WEG_IN_##WEG[nw], data->in_##weg[nw]); \
	mutex_unwock(&data->update_wock); \
	 \
	wetuwn count; \
}
stowe_in_weg(MIN, min);
stowe_in_weg(MAX, max);

static stwuct sensow_device_attwibute sda_in_input[] = {
	SENSOW_ATTW(in0_input, S_IWUGO, show_in, NUWW, 0),
	SENSOW_ATTW(in1_input, S_IWUGO, show_in, NUWW, 1),
	SENSOW_ATTW(in2_input, S_IWUGO, show_in, NUWW, 2),
	SENSOW_ATTW(in3_input, S_IWUGO, show_in, NUWW, 3),
	SENSOW_ATTW(in4_input, S_IWUGO, show_in, NUWW, 4),
	SENSOW_ATTW(in5_input, S_IWUGO, show_in, NUWW, 5),
	SENSOW_ATTW(in6_input, S_IWUGO, show_in, NUWW, 6),
	SENSOW_ATTW(in7_input, S_IWUGO, show_in, NUWW, 7),
	SENSOW_ATTW(in8_input, S_IWUGO, show_in, NUWW, 8),
	SENSOW_ATTW(in9_input, S_IWUGO, show_in, NUWW, 9),
};

static stwuct sensow_device_attwibute sda_in_min[] = {
	SENSOW_ATTW(in0_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 0),
	SENSOW_ATTW(in1_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 1),
	SENSOW_ATTW(in2_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 2),
	SENSOW_ATTW(in3_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 3),
	SENSOW_ATTW(in4_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 4),
	SENSOW_ATTW(in5_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 5),
	SENSOW_ATTW(in6_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 6),
	SENSOW_ATTW(in7_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 7),
	SENSOW_ATTW(in8_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 8),
	SENSOW_ATTW(in9_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 9),
};

static stwuct sensow_device_attwibute sda_in_max[] = {
	SENSOW_ATTW(in0_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 0),
	SENSOW_ATTW(in1_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 1),
	SENSOW_ATTW(in2_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 2),
	SENSOW_ATTW(in3_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 3),
	SENSOW_ATTW(in4_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 4),
	SENSOW_ATTW(in5_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 5),
	SENSOW_ATTW(in6_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 6),
	SENSOW_ATTW(in7_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 7),
	SENSOW_ATTW(in8_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 8),
	SENSOW_ATTW(in9_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 9),
};


static ssize_t show_beep(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw =
						to_sensow_dev_attw(attw);
	stwuct w83791d_data *data = w83791d_update_device(dev);
	int bitnw = sensow_attw->index;

	wetuwn spwintf(buf, "%d\n", (data->beep_mask >> bitnw) & 1);
}

static ssize_t stowe_beep(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw =
						to_sensow_dev_attw(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int bitnw = sensow_attw->index;
	int bytenw = bitnw / 8;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw = vaw ? 1 : 0;

	mutex_wock(&data->update_wock);

	data->beep_mask &= ~(0xff << (bytenw * 8));
	data->beep_mask |= w83791d_wead(cwient, W83791D_WEG_BEEP_CTWW[bytenw])
		<< (bytenw * 8);

	data->beep_mask &= ~(1 << bitnw);
	data->beep_mask |= vaw << bitnw;

	w83791d_wwite(cwient, W83791D_WEG_BEEP_CTWW[bytenw],
		(data->beep_mask >> (bytenw * 8)) & 0xff);

	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_awawm(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw =
						to_sensow_dev_attw(attw);
	stwuct w83791d_data *data = w83791d_update_device(dev);
	int bitnw = sensow_attw->index;

	wetuwn spwintf(buf, "%d\n", (data->awawms >> bitnw) & 1);
}

/*
 * Note: The bitmask fow the beep enabwe/disabwe is diffewent than
 * the bitmask fow the awawm.
 */
static stwuct sensow_device_attwibute sda_in_beep[] = {
	SENSOW_ATTW(in0_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 0),
	SENSOW_ATTW(in1_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 13),
	SENSOW_ATTW(in2_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 2),
	SENSOW_ATTW(in3_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 3),
	SENSOW_ATTW(in4_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 8),
	SENSOW_ATTW(in5_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 9),
	SENSOW_ATTW(in6_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 10),
	SENSOW_ATTW(in7_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 16),
	SENSOW_ATTW(in8_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 17),
	SENSOW_ATTW(in9_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 14),
};

static stwuct sensow_device_attwibute sda_in_awawm[] = {
	SENSOW_ATTW(in0_awawm, S_IWUGO, show_awawm, NUWW, 0),
	SENSOW_ATTW(in1_awawm, S_IWUGO, show_awawm, NUWW, 1),
	SENSOW_ATTW(in2_awawm, S_IWUGO, show_awawm, NUWW, 2),
	SENSOW_ATTW(in3_awawm, S_IWUGO, show_awawm, NUWW, 3),
	SENSOW_ATTW(in4_awawm, S_IWUGO, show_awawm, NUWW, 8),
	SENSOW_ATTW(in5_awawm, S_IWUGO, show_awawm, NUWW, 9),
	SENSOW_ATTW(in6_awawm, S_IWUGO, show_awawm, NUWW, 10),
	SENSOW_ATTW(in7_awawm, S_IWUGO, show_awawm, NUWW, 19),
	SENSOW_ATTW(in8_awawm, S_IWUGO, show_awawm, NUWW, 20),
	SENSOW_ATTW(in9_awawm, S_IWUGO, show_awawm, NUWW, 14),
};

#define show_fan_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
				chaw *buf) \
{ \
	stwuct sensow_device_attwibute *sensow_attw = \
						to_sensow_dev_attw(attw); \
	stwuct w83791d_data *data = w83791d_update_device(dev); \
	int nw = sensow_attw->index; \
	wetuwn spwintf(buf, "%d\n", \
		FAN_FWOM_WEG(data->weg[nw], DIV_FWOM_WEG(data->fan_div[nw]))); \
}

show_fan_weg(fan);
show_fan_weg(fan_min);

static ssize_t stowe_fan_min(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int nw = sensow_attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] = fan_to_weg(vaw, DIV_FWOM_WEG(data->fan_div[nw]));
	w83791d_wwite(cwient, W83791D_WEG_FAN_MIN[nw], data->fan_min[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_fan_div(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	int nw = sensow_attw->index;
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%u\n", DIV_FWOM_WEG(data->fan_div[nw]));
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan divisow.  This fowwows the pwincipwe of
 * weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the divisow changed.
 */
static ssize_t stowe_fan_div(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int nw = sensow_attw->index;
	unsigned wong min;
	u8 tmp_fan_div;
	u8 fan_div_weg;
	u8 vbat_weg;
	int indx = 0;
	u8 keep_mask = 0;
	u8 new_shift = 0;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	/* Save fan_min */
	min = FAN_FWOM_WEG(data->fan_min[nw], DIV_FWOM_WEG(data->fan_div[nw]));

	mutex_wock(&data->update_wock);
	data->fan_div[nw] = div_to_weg(nw, vaw);

	switch (nw) {
	case 0:
		indx = 0;
		keep_mask = 0xcf;
		new_shift = 4;
		bweak;
	case 1:
		indx = 0;
		keep_mask = 0x3f;
		new_shift = 6;
		bweak;
	case 2:
		indx = 1;
		keep_mask = 0x3f;
		new_shift = 6;
		bweak;
	case 3:
		indx = 2;
		keep_mask = 0xf8;
		new_shift = 0;
		bweak;
	case 4:
		indx = 2;
		keep_mask = 0x8f;
		new_shift = 4;
		bweak;
#ifdef DEBUG
	defauwt:
		dev_wawn(dev, "stowe_fan_div: Unexpected nw seen: %d\n", nw);
		count = -EINVAW;
		goto eww_exit;
#endif
	}

	fan_div_weg = w83791d_wead(cwient, W83791D_WEG_FAN_DIV[indx])
			& keep_mask;
	tmp_fan_div = (data->fan_div[nw] << new_shift) & ~keep_mask;

	w83791d_wwite(cwient, W83791D_WEG_FAN_DIV[indx],
				fan_div_weg | tmp_fan_div);

	/* Bit 2 of fans 0-2 is stowed in the vbat wegistew (bits 5-7) */
	if (nw < 3) {
		keep_mask = ~(1 << (nw + 5));
		vbat_weg = w83791d_wead(cwient, W83791D_WEG_VBAT)
				& keep_mask;
		tmp_fan_div = (data->fan_div[nw] << (3 + nw)) & ~keep_mask;
		w83791d_wwite(cwient, W83791D_WEG_VBAT,
				vbat_weg | tmp_fan_div);
	}

	/* Westowe fan_min */
	data->fan_min[nw] = fan_to_weg(min, DIV_FWOM_WEG(data->fan_div[nw]));
	w83791d_wwite(cwient, W83791D_WEG_FAN_MIN[nw], data->fan_min[nw]);

#ifdef DEBUG
eww_exit:
#endif
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static stwuct sensow_device_attwibute sda_fan_input[] = {
	SENSOW_ATTW(fan1_input, S_IWUGO, show_fan, NUWW, 0),
	SENSOW_ATTW(fan2_input, S_IWUGO, show_fan, NUWW, 1),
	SENSOW_ATTW(fan3_input, S_IWUGO, show_fan, NUWW, 2),
	SENSOW_ATTW(fan4_input, S_IWUGO, show_fan, NUWW, 3),
	SENSOW_ATTW(fan5_input, S_IWUGO, show_fan, NUWW, 4),
};

static stwuct sensow_device_attwibute sda_fan_min[] = {
	SENSOW_ATTW(fan1_min, S_IWUSW | S_IWUGO,
			show_fan_min, stowe_fan_min, 0),
	SENSOW_ATTW(fan2_min, S_IWUSW | S_IWUGO,
			show_fan_min, stowe_fan_min, 1),
	SENSOW_ATTW(fan3_min, S_IWUSW | S_IWUGO,
			show_fan_min, stowe_fan_min, 2),
	SENSOW_ATTW(fan4_min, S_IWUSW | S_IWUGO,
			show_fan_min, stowe_fan_min, 3),
	SENSOW_ATTW(fan5_min, S_IWUSW | S_IWUGO,
			show_fan_min, stowe_fan_min, 4),
};

static stwuct sensow_device_attwibute sda_fan_div[] = {
	SENSOW_ATTW(fan1_div, S_IWUSW | S_IWUGO,
			show_fan_div, stowe_fan_div, 0),
	SENSOW_ATTW(fan2_div, S_IWUSW | S_IWUGO,
			show_fan_div, stowe_fan_div, 1),
	SENSOW_ATTW(fan3_div, S_IWUSW | S_IWUGO,
			show_fan_div, stowe_fan_div, 2),
	SENSOW_ATTW(fan4_div, S_IWUSW | S_IWUGO,
			show_fan_div, stowe_fan_div, 3),
	SENSOW_ATTW(fan5_div, S_IWUSW | S_IWUGO,
			show_fan_div, stowe_fan_div, 4),
};

static stwuct sensow_device_attwibute sda_fan_beep[] = {
	SENSOW_ATTW(fan1_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 6),
	SENSOW_ATTW(fan2_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 7),
	SENSOW_ATTW(fan3_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 11),
	SENSOW_ATTW(fan4_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 21),
	SENSOW_ATTW(fan5_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 22),
};

static stwuct sensow_device_attwibute sda_fan_awawm[] = {
	SENSOW_ATTW(fan1_awawm, S_IWUGO, show_awawm, NUWW, 6),
	SENSOW_ATTW(fan2_awawm, S_IWUGO, show_awawm, NUWW, 7),
	SENSOW_ATTW(fan3_awawm, S_IWUGO, show_awawm, NUWW, 11),
	SENSOW_ATTW(fan4_awawm, S_IWUGO, show_awawm, NUWW, 21),
	SENSOW_ATTW(fan5_awawm, S_IWUGO, show_awawm, NUWW, 22),
};

/* wead/wwite PWMs */
static ssize_t show_pwm(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	int nw = sensow_attw->index;
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->pwm[nw]);
}

static ssize_t stowe_pwm(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int nw = sensow_attw->index;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->pwm[nw] = cwamp_vaw(vaw, 0, 255);
	w83791d_wwite(cwient, W83791D_WEG_PWM[nw], data->pwm[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute sda_pwm[] = {
	SENSOW_ATTW(pwm1, S_IWUSW | S_IWUGO,
			show_pwm, stowe_pwm, 0),
	SENSOW_ATTW(pwm2, S_IWUSW | S_IWUGO,
			show_pwm, stowe_pwm, 1),
	SENSOW_ATTW(pwm3, S_IWUSW | S_IWUGO,
			show_pwm, stowe_pwm, 2),
	SENSOW_ATTW(pwm4, S_IWUSW | S_IWUGO,
			show_pwm, stowe_pwm, 3),
	SENSOW_ATTW(pwm5, S_IWUSW | S_IWUGO,
			show_pwm, stowe_pwm, 4),
};

static ssize_t show_pwmenabwe(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	int nw = sensow_attw->index;
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->pwm_enabwe[nw] + 1);
}

static ssize_t stowe_pwmenabwe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int nw = sensow_attw->index;
	unsigned wong vaw;
	u8 weg_cfg_tmp;
	u8 weg_idx = 0;
	u8 vaw_shift = 0;
	u8 keep_mask = 0;

	int wet = kstwtouw(buf, 10, &vaw);

	if (wet || vaw < 1 || vaw > 3)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->pwm_enabwe[nw] = vaw - 1;
	switch (nw) {
	case 0:
		weg_idx = 0;
		vaw_shift = 2;
		keep_mask = 0xf3;
		bweak;
	case 1:
		weg_idx = 0;
		vaw_shift = 4;
		keep_mask = 0xcf;
		bweak;
	case 2:
		weg_idx = 1;
		vaw_shift = 2;
		keep_mask = 0xf3;
		bweak;
	}

	weg_cfg_tmp = w83791d_wead(cwient, W83791D_WEG_FAN_CFG[weg_idx]);
	weg_cfg_tmp = (weg_cfg_tmp & keep_mask) |
					data->pwm_enabwe[nw] << vaw_shift;

	w83791d_wwite(cwient, W83791D_WEG_FAN_CFG[weg_idx], weg_cfg_tmp);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}
static stwuct sensow_device_attwibute sda_pwmenabwe[] = {
	SENSOW_ATTW(pwm1_enabwe, S_IWUSW | S_IWUGO,
			show_pwmenabwe, stowe_pwmenabwe, 0),
	SENSOW_ATTW(pwm2_enabwe, S_IWUSW | S_IWUGO,
			show_pwmenabwe, stowe_pwmenabwe, 1),
	SENSOW_ATTW(pwm3_enabwe, S_IWUSW | S_IWUGO,
			show_pwmenabwe, stowe_pwmenabwe, 2),
};

/* Fow Smawt Fan I / Thewmaw Cwuise */
static ssize_t show_temp_tawget(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct w83791d_data *data = w83791d_update_device(dev);
	int nw = sensow_attw->index;
	wetuwn spwintf(buf, "%d\n", TEMP1_FWOM_WEG(data->temp_tawget[nw]));
}

static ssize_t stowe_temp_tawget(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int nw = sensow_attw->index;
	wong vaw;
	u8 tawget_mask;

	if (kstwtow(buf, 10, &vaw))
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->temp_tawget[nw] = TAWGET_TEMP_TO_WEG(vaw);
	tawget_mask = w83791d_wead(cwient,
				W83791D_WEG_TEMP_TAWGET[nw]) & 0x80;
	w83791d_wwite(cwient, W83791D_WEG_TEMP_TAWGET[nw],
				data->temp_tawget[nw] | tawget_mask);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute sda_temp_tawget[] = {
	SENSOW_ATTW(temp1_tawget, S_IWUSW | S_IWUGO,
			show_temp_tawget, stowe_temp_tawget, 0),
	SENSOW_ATTW(temp2_tawget, S_IWUSW | S_IWUGO,
			show_temp_tawget, stowe_temp_tawget, 1),
	SENSOW_ATTW(temp3_tawget, S_IWUSW | S_IWUGO,
			show_temp_tawget, stowe_temp_tawget, 2),
};

static ssize_t show_temp_towewance(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct w83791d_data *data = w83791d_update_device(dev);
	int nw = sensow_attw->index;
	wetuwn spwintf(buf, "%d\n", TEMP1_FWOM_WEG(data->temp_towewance[nw]));
}

static ssize_t stowe_temp_towewance(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int nw = sensow_attw->index;
	unsigned wong vaw;
	u8 tawget_mask;
	u8 weg_idx = 0;
	u8 vaw_shift = 0;
	u8 keep_mask = 0;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	switch (nw) {
	case 0:
		weg_idx = 0;
		vaw_shift = 0;
		keep_mask = 0xf0;
		bweak;
	case 1:
		weg_idx = 0;
		vaw_shift = 4;
		keep_mask = 0x0f;
		bweak;
	case 2:
		weg_idx = 1;
		vaw_shift = 0;
		keep_mask = 0xf0;
		bweak;
	}

	mutex_wock(&data->update_wock);
	data->temp_towewance[nw] = TOW_TEMP_TO_WEG(vaw);
	tawget_mask = w83791d_wead(cwient,
			W83791D_WEG_TEMP_TOW[weg_idx]) & keep_mask;
	w83791d_wwite(cwient, W83791D_WEG_TEMP_TOW[weg_idx],
			(data->temp_towewance[nw] << vaw_shift) | tawget_mask);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute sda_temp_towewance[] = {
	SENSOW_ATTW(temp1_towewance, S_IWUSW | S_IWUGO,
			show_temp_towewance, stowe_temp_towewance, 0),
	SENSOW_ATTW(temp2_towewance, S_IWUSW | S_IWUGO,
			show_temp_towewance, stowe_temp_towewance, 1),
	SENSOW_ATTW(temp3_towewance, S_IWUSW | S_IWUGO,
			show_temp_towewance, stowe_temp_towewance, 2),
};

/* wead/wwite the tempewatuwe1, incwudes measuwed vawue and wimits */
static ssize_t show_temp1(stwuct device *dev, stwuct device_attwibute *devattw,
				chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP1_FWOM_WEG(data->temp1[attw->index]));
}

static ssize_t stowe_temp1(stwuct device *dev, stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp1[nw] = TEMP1_TO_WEG(vaw);
	w83791d_wwite(cwient, W83791D_WEG_TEMP1[nw], data->temp1[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/* wead/wwite tempewatuwe2-3, incwudes measuwed vawue and wimits */
static ssize_t show_temp23(stwuct device *dev, stwuct device_attwibute *devattw,
				chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct w83791d_data *data = w83791d_update_device(dev);
	int nw = attw->nw;
	int index = attw->index;
	wetuwn spwintf(buf, "%d\n", TEMP23_FWOM_WEG(data->temp_add[nw][index]));
}

static ssize_t stowe_temp23(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	wong vaw;
	int eww;
	int nw = attw->nw;
	int index = attw->index;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_add[nw][index] = TEMP23_TO_WEG(vaw);
	w83791d_wwite(cwient, W83791D_WEG_TEMP_ADD[nw][index * 2],
				data->temp_add[nw][index] >> 8);
	w83791d_wwite(cwient, W83791D_WEG_TEMP_ADD[nw][index * 2 + 1],
				data->temp_add[nw][index] & 0x80);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static stwuct sensow_device_attwibute_2 sda_temp_input[] = {
	SENSOW_ATTW_2(temp1_input, S_IWUGO, show_temp1, NUWW, 0, 0),
	SENSOW_ATTW_2(temp2_input, S_IWUGO, show_temp23, NUWW, 0, 0),
	SENSOW_ATTW_2(temp3_input, S_IWUGO, show_temp23, NUWW, 1, 0),
};

static stwuct sensow_device_attwibute_2 sda_temp_max[] = {
	SENSOW_ATTW_2(temp1_max, S_IWUGO | S_IWUSW,
			show_temp1, stowe_temp1, 0, 1),
	SENSOW_ATTW_2(temp2_max, S_IWUGO | S_IWUSW,
			show_temp23, stowe_temp23, 0, 1),
	SENSOW_ATTW_2(temp3_max, S_IWUGO | S_IWUSW,
			show_temp23, stowe_temp23, 1, 1),
};

static stwuct sensow_device_attwibute_2 sda_temp_max_hyst[] = {
	SENSOW_ATTW_2(temp1_max_hyst, S_IWUGO | S_IWUSW,
			show_temp1, stowe_temp1, 0, 2),
	SENSOW_ATTW_2(temp2_max_hyst, S_IWUGO | S_IWUSW,
			show_temp23, stowe_temp23, 0, 2),
	SENSOW_ATTW_2(temp3_max_hyst, S_IWUGO | S_IWUSW,
			show_temp23, stowe_temp23, 1, 2),
};

/*
 * Note: The bitmask fow the beep enabwe/disabwe is diffewent than
 * the bitmask fow the awawm.
 */
static stwuct sensow_device_attwibute sda_temp_beep[] = {
	SENSOW_ATTW(temp1_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 4),
	SENSOW_ATTW(temp2_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 5),
	SENSOW_ATTW(temp3_beep, S_IWUSW | S_IWUGO, show_beep, stowe_beep, 1),
};

static stwuct sensow_device_attwibute sda_temp_awawm[] = {
	SENSOW_ATTW(temp1_awawm, S_IWUGO, show_awawm, NUWW, 4),
	SENSOW_ATTW(temp2_awawm, S_IWUGO, show_awawm, NUWW, 5),
	SENSOW_ATTW(temp3_awawm, S_IWUGO, show_awawm, NUWW, 13),
};

/* get weawtime status of aww sensows items: vowtage, temp, fan */
static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}

static DEVICE_ATTW_WO(awawms);

/* Beep contwow */

#define GWOBAW_BEEP_ENABWE_SHIFT	15
#define GWOBAW_BEEP_ENABWE_MASK		(1 << GWOBAW_BEEP_ENABWE_SHIFT)

static ssize_t show_beep_enabwe(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->beep_enabwe);
}

static ssize_t show_beep_mask(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%d\n", BEEP_MASK_FWOM_WEG(data->beep_mask));
}


static ssize_t stowe_beep_mask(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int i;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	/*
	 * The beep_enabwe state ovewwides any enabwing wequest fwom
	 * the masks
	 */
	data->beep_mask = BEEP_MASK_TO_WEG(vaw) & ~GWOBAW_BEEP_ENABWE_MASK;
	data->beep_mask |= (data->beep_enabwe << GWOBAW_BEEP_ENABWE_SHIFT);

	vaw = data->beep_mask;

	fow (i = 0; i < 3; i++) {
		w83791d_wwite(cwient, W83791D_WEG_BEEP_CTWW[i], (vaw & 0xff));
		vaw >>= 8;
	}

	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t stowe_beep_enabwe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	data->beep_enabwe = vaw ? 1 : 0;

	/* Keep the fuww mask vawue in sync with the cuwwent enabwe */
	data->beep_mask &= ~GWOBAW_BEEP_ENABWE_MASK;
	data->beep_mask |= (data->beep_enabwe << GWOBAW_BEEP_ENABWE_SHIFT);

	/*
	 * The gwobaw contwow is in the second beep contwow wegistew
	 * so onwy need to update that wegistew
	 */
	vaw = (data->beep_mask >> 8) & 0xff;

	w83791d_wwite(cwient, W83791D_WEG_BEEP_CTWW[1], vaw);

	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static stwuct sensow_device_attwibute sda_beep_ctww[] = {
	SENSOW_ATTW(beep_enabwe, S_IWUGO | S_IWUSW,
			show_beep_enabwe, stowe_beep_enabwe, 0),
	SENSOW_ATTW(beep_mask, S_IWUGO | S_IWUSW,
			show_beep_mask, stowe_beep_mask, 1)
};

/* cpu vowtage weguwation infowmation */
static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83791d_data *data = w83791d_update_device(dev);
	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid, data->vwm));
}

static DEVICE_ATTW_WO(cpu0_vid);

static ssize_t vwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct w83791d_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->vwm);
}

static ssize_t vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct w83791d_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	/*
	 * No wock needed as vwm is intewnaw to the dwivew
	 * (not wead fwom a chip wegistew) and so is not
	 * updated in w83791d_update_device()
	 */

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 255)
		wetuwn -EINVAW;

	data->vwm = vaw;
	wetuwn count;
}

static DEVICE_ATTW_WW(vwm);

#define IN_UNIT_ATTWS(X) \
	&sda_in_input[X].dev_attw.attw,	\
	&sda_in_min[X].dev_attw.attw,	\
	&sda_in_max[X].dev_attw.attw,	\
	&sda_in_beep[X].dev_attw.attw,	\
	&sda_in_awawm[X].dev_attw.attw

#define FAN_UNIT_ATTWS(X) \
	&sda_fan_input[X].dev_attw.attw,	\
	&sda_fan_min[X].dev_attw.attw,		\
	&sda_fan_div[X].dev_attw.attw,		\
	&sda_fan_beep[X].dev_attw.attw,		\
	&sda_fan_awawm[X].dev_attw.attw

#define TEMP_UNIT_ATTWS(X) \
	&sda_temp_input[X].dev_attw.attw,	\
	&sda_temp_max[X].dev_attw.attw,		\
	&sda_temp_max_hyst[X].dev_attw.attw,	\
	&sda_temp_beep[X].dev_attw.attw,	\
	&sda_temp_awawm[X].dev_attw.attw

static stwuct attwibute *w83791d_attwibutes[] = {
	IN_UNIT_ATTWS(0),
	IN_UNIT_ATTWS(1),
	IN_UNIT_ATTWS(2),
	IN_UNIT_ATTWS(3),
	IN_UNIT_ATTWS(4),
	IN_UNIT_ATTWS(5),
	IN_UNIT_ATTWS(6),
	IN_UNIT_ATTWS(7),
	IN_UNIT_ATTWS(8),
	IN_UNIT_ATTWS(9),
	FAN_UNIT_ATTWS(0),
	FAN_UNIT_ATTWS(1),
	FAN_UNIT_ATTWS(2),
	TEMP_UNIT_ATTWS(0),
	TEMP_UNIT_ATTWS(1),
	TEMP_UNIT_ATTWS(2),
	&dev_attw_awawms.attw,
	&sda_beep_ctww[0].dev_attw.attw,
	&sda_beep_ctww[1].dev_attw.attw,
	&dev_attw_cpu0_vid.attw,
	&dev_attw_vwm.attw,
	&sda_pwm[0].dev_attw.attw,
	&sda_pwm[1].dev_attw.attw,
	&sda_pwm[2].dev_attw.attw,
	&sda_pwmenabwe[0].dev_attw.attw,
	&sda_pwmenabwe[1].dev_attw.attw,
	&sda_pwmenabwe[2].dev_attw.attw,
	&sda_temp_tawget[0].dev_attw.attw,
	&sda_temp_tawget[1].dev_attw.attw,
	&sda_temp_tawget[2].dev_attw.attw,
	&sda_temp_towewance[0].dev_attw.attw,
	&sda_temp_towewance[1].dev_attw.attw,
	&sda_temp_towewance[2].dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup w83791d_gwoup = {
	.attws = w83791d_attwibutes,
};

/*
 * Sepawate gwoup of attwibutes fow fan/pwm 4-5. Theiw pins can awso be
 * in use fow GPIO in which case theiw sysfs-intewface shouwd not be made
 * avaiwabwe
 */
static stwuct attwibute *w83791d_attwibutes_fanpwm45[] = {
	FAN_UNIT_ATTWS(3),
	FAN_UNIT_ATTWS(4),
	&sda_pwm[3].dev_attw.attw,
	&sda_pwm[4].dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup w83791d_gwoup_fanpwm45 = {
	.attws = w83791d_attwibutes_fanpwm45,
};

static int w83791d_detect_subcwients(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int addwess = cwient->addw;
	int i, id;
	u8 vaw;

	id = i2c_adaptew_id(adaptew);
	if (fowce_subcwients[0] == id && fowce_subcwients[1] == addwess) {
		fow (i = 2; i <= 3; i++) {
			if (fowce_subcwients[i] < 0x48 ||
			    fowce_subcwients[i] > 0x4f) {
				dev_eww(&cwient->dev,
					"invawid subcwient "
					"addwess %d; must be 0x48-0x4f\n",
					fowce_subcwients[i]);
				wetuwn -ENODEV;
			}
		}
		w83791d_wwite(cwient, W83791D_WEG_I2C_SUBADDW,
					(fowce_subcwients[2] & 0x07) |
					((fowce_subcwients[3] & 0x07) << 4));
	}

	vaw = w83791d_wead(cwient, W83791D_WEG_I2C_SUBADDW);

	if (!(vaw & 0x88) && (vaw & 0x7) == ((vaw >> 4) & 0x7)) {
		dev_eww(&cwient->dev,
			"dupwicate addwesses 0x%x, use fowce_subcwient\n", 0x48 + (vaw & 0x7));
		wetuwn -ENODEV;
	}

	if (!(vaw & 0x08))
		devm_i2c_new_dummy_device(&cwient->dev, adaptew, 0x48 + (vaw & 0x7));

	if (!(vaw & 0x80))
		devm_i2c_new_dummy_device(&cwient->dev, adaptew, 0x48 + ((vaw >> 4) & 0x7));

	wetuwn 0;
}


/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int w83791d_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int vaw1, vaw2;
	unsigned showt addwess = cwient->addw;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	if (w83791d_wead(cwient, W83791D_WEG_CONFIG) & 0x80)
		wetuwn -ENODEV;

	vaw1 = w83791d_wead(cwient, W83791D_WEG_BANK);
	vaw2 = w83791d_wead(cwient, W83791D_WEG_CHIPMAN);
	/* Check fow Winbond ID if in bank 0 */
	if (!(vaw1 & 0x07)) {
		if ((!(vaw1 & 0x80) && vaw2 != 0xa3) ||
		    ((vaw1 & 0x80) && vaw2 != 0x5c)) {
			wetuwn -ENODEV;
		}
	}
	/*
	 * If Winbond chip, addwess of chip and W83791D_WEG_I2C_ADDW
	 * shouwd match
	 */
	if (w83791d_wead(cwient, W83791D_WEG_I2C_ADDW) != addwess)
		wetuwn -ENODEV;

	/* We want bank 0 and Vendow ID high byte */
	vaw1 = w83791d_wead(cwient, W83791D_WEG_BANK) & 0x78;
	w83791d_wwite(cwient, W83791D_WEG_BANK, vaw1 | 0x80);

	/* Vewify it is a Winbond w83791d */
	vaw1 = w83791d_wead(cwient, W83791D_WEG_WCHIPID);
	vaw2 = w83791d_wead(cwient, W83791D_WEG_CHIPMAN);
	if (vaw1 != 0x71 || vaw2 != 0x5c)
		wetuwn -ENODEV;

	stwscpy(info->type, "w83791d", I2C_NAME_SIZE);

	wetuwn 0;
}

static int w83791d_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct w83791d_data *data;
	stwuct device *dev = &cwient->dev;
	int i, eww;
	u8 has_fanpwm45;

#ifdef DEBUG
	int vaw1;
	vaw1 = w83791d_wead(cwient, W83791D_WEG_DID_VID4);
	dev_dbg(dev, "Device ID vewsion: %d.%d (0x%02x)\n",
			(vaw1 >> 5) & 0x07, (vaw1 >> 1) & 0x0f, vaw1);
#endif

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct w83791d_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	eww = w83791d_detect_subcwients(cwient);
	if (eww)
		wetuwn eww;

	/* Initiawize the chip */
	w83791d_init_cwient(cwient);

	/*
	 * If the fan_div is changed, make suwe thewe is a wationaw
	 * fan_min in pwace
	 */
	fow (i = 0; i < NUMBEW_OF_FANIN; i++)
		data->fan_min[i] = w83791d_wead(cwient, W83791D_WEG_FAN_MIN[i]);

	/* Wegistew sysfs hooks */
	eww = sysfs_cweate_gwoup(&cwient->dev.kobj, &w83791d_gwoup);
	if (eww)
		wetuwn eww;

	/* Check if pins of fan/pwm 4-5 awe in use as GPIO */
	has_fanpwm45 = w83791d_wead(cwient, W83791D_WEG_GPIO) & 0x10;
	if (has_fanpwm45) {
		eww = sysfs_cweate_gwoup(&cwient->dev.kobj,
					 &w83791d_gwoup_fanpwm45);
		if (eww)
			goto ewwow4;
	}

	/* Evewything is weady, now wegistew the wowking device */
	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto ewwow5;
	}

	wetuwn 0;

ewwow5:
	if (has_fanpwm45)
		sysfs_wemove_gwoup(&cwient->dev.kobj, &w83791d_gwoup_fanpwm45);
ewwow4:
	sysfs_wemove_gwoup(&cwient->dev.kobj, &w83791d_gwoup);
	wetuwn eww;
}

static void w83791d_wemove(stwuct i2c_cwient *cwient)
{
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);

	hwmon_device_unwegistew(data->hwmon_dev);
	sysfs_wemove_gwoup(&cwient->dev.kobj, &w83791d_gwoup);
}

static void w83791d_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	u8 tmp;
	u8 owd_beep;

	/*
	 * The diffewence between weset and init is that weset
	 * does a hawd weset of the chip via index 0x40, bit 7,
	 * but init simpwy fowces cewtain wegistews to have "sane"
	 * vawues. The hope is that the BIOS has done the wight
	 * thing (which is why the defauwt is weset=0, init=0),
	 * but if not, weset is the hawd hammew and init
	 * is the soft mawwet both of which awe twying to whack
	 * things into pwace...
	 * NOTE: The data sheet makes a distinction between
	 * "powew on defauwts" and "weset by MW". As faw as I can teww,
	 * the hawd weset puts evewything into a powew-on state so I'm
	 * not suwe what "weset by MW" means ow how it can happen.
	 */
	if (weset || init) {
		/* keep some BIOS settings when we... */
		owd_beep = w83791d_wead(cwient, W83791D_WEG_BEEP_CONFIG);

		if (weset) {
			/* ... weset the chip and ... */
			w83791d_wwite(cwient, W83791D_WEG_CONFIG, 0x80);
		}

		/* ... disabwe powew-on abnowmaw beep */
		w83791d_wwite(cwient, W83791D_WEG_BEEP_CONFIG, owd_beep | 0x80);

		/* disabwe the gwobaw beep (not done by hawd weset) */
		tmp = w83791d_wead(cwient, W83791D_WEG_BEEP_CTWW[1]);
		w83791d_wwite(cwient, W83791D_WEG_BEEP_CTWW[1], tmp & 0xef);

		if (init) {
			/* Make suwe monitowing is tuwned on fow add-ons */
			tmp = w83791d_wead(cwient, W83791D_WEG_TEMP2_CONFIG);
			if (tmp & 1) {
				w83791d_wwite(cwient, W83791D_WEG_TEMP2_CONFIG,
					tmp & 0xfe);
			}

			tmp = w83791d_wead(cwient, W83791D_WEG_TEMP3_CONFIG);
			if (tmp & 1) {
				w83791d_wwite(cwient, W83791D_WEG_TEMP3_CONFIG,
					tmp & 0xfe);
			}

			/* Stawt monitowing */
			tmp = w83791d_wead(cwient, W83791D_WEG_CONFIG) & 0xf7;
			w83791d_wwite(cwient, W83791D_WEG_CONFIG, tmp | 0x01);
		}
	}

	data->vwm = vid_which_vwm();
}

static stwuct w83791d_data *w83791d_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83791d_data *data = i2c_get_cwientdata(cwient);
	int i, j;
	u8 weg_awway_tmp[3];
	u8 vbat_weg;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + (HZ * 3))
			|| !data->vawid) {
		dev_dbg(dev, "Stawting w83791d device update\n");

		/* Update the vowtages measuwed vawue and wimits */
		fow (i = 0; i < NUMBEW_OF_VIN; i++) {
			data->in[i] = w83791d_wead(cwient,
						W83791D_WEG_IN[i]);
			data->in_max[i] = w83791d_wead(cwient,
						W83791D_WEG_IN_MAX[i]);
			data->in_min[i] = w83791d_wead(cwient,
						W83791D_WEG_IN_MIN[i]);
		}

		/* Update the fan counts and wimits */
		fow (i = 0; i < NUMBEW_OF_FANIN; i++) {
			/* Update the Fan measuwed vawue and wimits */
			data->fan[i] = w83791d_wead(cwient,
						W83791D_WEG_FAN[i]);
			data->fan_min[i] = w83791d_wead(cwient,
						W83791D_WEG_FAN_MIN[i]);
		}

		/* Update the fan divisow */
		fow (i = 0; i < 3; i++) {
			weg_awway_tmp[i] = w83791d_wead(cwient,
						W83791D_WEG_FAN_DIV[i]);
		}
		data->fan_div[0] = (weg_awway_tmp[0] >> 4) & 0x03;
		data->fan_div[1] = (weg_awway_tmp[0] >> 6) & 0x03;
		data->fan_div[2] = (weg_awway_tmp[1] >> 6) & 0x03;
		data->fan_div[3] = weg_awway_tmp[2] & 0x07;
		data->fan_div[4] = (weg_awway_tmp[2] >> 4) & 0x07;

		/*
		 * The fan divisow fow fans 0-2 get bit 2 fwom
		 * bits 5-7 wespectivewy of vbat wegistew
		 */
		vbat_weg = w83791d_wead(cwient, W83791D_WEG_VBAT);
		fow (i = 0; i < 3; i++)
			data->fan_div[i] |= (vbat_weg >> (3 + i)) & 0x04;

		/* Update PWM duty cycwe */
		fow (i = 0; i < NUMBEW_OF_PWM; i++) {
			data->pwm[i] =  w83791d_wead(cwient,
						W83791D_WEG_PWM[i]);
		}

		/* Update PWM enabwe status */
		fow (i = 0; i < 2; i++) {
			weg_awway_tmp[i] = w83791d_wead(cwient,
						W83791D_WEG_FAN_CFG[i]);
		}
		data->pwm_enabwe[0] = (weg_awway_tmp[0] >> 2) & 0x03;
		data->pwm_enabwe[1] = (weg_awway_tmp[0] >> 4) & 0x03;
		data->pwm_enabwe[2] = (weg_awway_tmp[1] >> 2) & 0x03;

		/* Update PWM tawget tempewatuwe */
		fow (i = 0; i < 3; i++) {
			data->temp_tawget[i] = w83791d_wead(cwient,
				W83791D_WEG_TEMP_TAWGET[i]) & 0x7f;
		}

		/* Update PWM tempewatuwe towewance */
		fow (i = 0; i < 2; i++) {
			weg_awway_tmp[i] = w83791d_wead(cwient,
					W83791D_WEG_TEMP_TOW[i]);
		}
		data->temp_towewance[0] = weg_awway_tmp[0] & 0x0f;
		data->temp_towewance[1] = (weg_awway_tmp[0] >> 4) & 0x0f;
		data->temp_towewance[2] = weg_awway_tmp[1] & 0x0f;

		/* Update the fiwst tempewatuwe sensow */
		fow (i = 0; i < 3; i++) {
			data->temp1[i] = w83791d_wead(cwient,
						W83791D_WEG_TEMP1[i]);
		}

		/* Update the west of the tempewatuwe sensows */
		fow (i = 0; i < 2; i++) {
			fow (j = 0; j < 3; j++) {
				data->temp_add[i][j] =
					(w83791d_wead(cwient,
					W83791D_WEG_TEMP_ADD[i][j * 2]) << 8) |
					w83791d_wead(cwient,
					W83791D_WEG_TEMP_ADD[i][j * 2 + 1]);
			}
		}

		/* Update the weawtime status */
		data->awawms =
			w83791d_wead(cwient, W83791D_WEG_AWAWM1) +
			(w83791d_wead(cwient, W83791D_WEG_AWAWM2) << 8) +
			(w83791d_wead(cwient, W83791D_WEG_AWAWM3) << 16);

		/* Update the beep configuwation infowmation */
		data->beep_mask =
			w83791d_wead(cwient, W83791D_WEG_BEEP_CTWW[0]) +
			(w83791d_wead(cwient, W83791D_WEG_BEEP_CTWW[1]) << 8) +
			(w83791d_wead(cwient, W83791D_WEG_BEEP_CTWW[2]) << 16);

		/* Extwact gwobaw beep enabwe fwag */
		data->beep_enabwe =
			(data->beep_mask >> GWOBAW_BEEP_ENABWE_SHIFT) & 0x01;

		/* Update the cpu vowtage infowmation */
		i = w83791d_wead(cwient, W83791D_WEG_VID_FANDIV);
		data->vid = i & 0x0f;
		data->vid |= (w83791d_wead(cwient, W83791D_WEG_DID_VID4) & 0x01)
				<< 4;

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

#ifdef DEBUG
	w83791d_pwint_debug(data, dev);
#endif

	wetuwn data;
}

#ifdef DEBUG
static void w83791d_pwint_debug(stwuct w83791d_data *data, stwuct device *dev)
{
	int i = 0, j = 0;

	dev_dbg(dev, "======Stawt of w83791d debug vawues======\n");
	dev_dbg(dev, "%d set of Vowtages: ===>\n", NUMBEW_OF_VIN);
	fow (i = 0; i < NUMBEW_OF_VIN; i++) {
		dev_dbg(dev, "vin[%d] is:     0x%02x\n", i, data->in[i]);
		dev_dbg(dev, "vin[%d] min is: 0x%02x\n", i, data->in_min[i]);
		dev_dbg(dev, "vin[%d] max is: 0x%02x\n", i, data->in_max[i]);
	}
	dev_dbg(dev, "%d set of Fan Counts/Divisows: ===>\n", NUMBEW_OF_FANIN);
	fow (i = 0; i < NUMBEW_OF_FANIN; i++) {
		dev_dbg(dev, "fan[%d] is:     0x%02x\n", i, data->fan[i]);
		dev_dbg(dev, "fan[%d] min is: 0x%02x\n", i, data->fan_min[i]);
		dev_dbg(dev, "fan_div[%d] is: 0x%02x\n", i, data->fan_div[i]);
	}

	/*
	 * tempewatuwe math is signed, but onwy pwint out the
	 * bits that mattew
	 */
	dev_dbg(dev, "%d set of Tempewatuwes: ===>\n", NUMBEW_OF_TEMPIN);
	fow (i = 0; i < 3; i++)
		dev_dbg(dev, "temp1[%d] is: 0x%02x\n", i, (u8) data->temp1[i]);
	fow (i = 0; i < 2; i++) {
		fow (j = 0; j < 3; j++) {
			dev_dbg(dev, "temp_add[%d][%d] is: 0x%04x\n", i, j,
				(u16) data->temp_add[i][j]);
		}
	}

	dev_dbg(dev, "Misc Infowmation: ===>\n");
	dev_dbg(dev, "awawm is:     0x%08x\n", data->awawms);
	dev_dbg(dev, "beep_mask is: 0x%08x\n", data->beep_mask);
	dev_dbg(dev, "beep_enabwe is: %d\n", data->beep_enabwe);
	dev_dbg(dev, "vid is: 0x%02x\n", data->vid);
	dev_dbg(dev, "vwm is: 0x%02x\n", data->vwm);
	dev_dbg(dev, "=======End of w83791d debug vawues========\n");
	dev_dbg(dev, "\n");
}
#endif

moduwe_i2c_dwivew(w83791d_dwivew);

MODUWE_AUTHOW("Chawwes Spiwakis <bezauw@gmaiw.com>");
MODUWE_DESCWIPTION("W83791D dwivew");
MODUWE_WICENSE("GPW");
