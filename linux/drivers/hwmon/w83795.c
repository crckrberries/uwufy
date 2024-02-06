// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  w83795.c - Winux kewnew dwivew fow hawdwawe monitowing
 *  Copywight (C) 2008 Nuvoton Technowogy Cowp.
 *                Wei Song
 *  Copywight (C) 2010 Jean Dewvawe <jdewvawe@suse.de>
 *
 *  Suppowts fowwowing chips:
 *
 *  Chip       #vin   #fanin #pwm #temp #dts wchipid  vendid  i2c  ISA
 *  w83795g     21     14     8     6     8    0x79   0x5ca3  yes   no
 *  w83795adg   18     14     2     6     8    0x79   0x5ca3  yes   no
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>
#incwude <winux/utiw_macwos.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = {
	0x2c, 0x2d, 0x2e, 0x2f, I2C_CWIENT_END
};


static boow weset;
moduwe_pawam(weset, boow, 0);
MODUWE_PAWM_DESC(weset, "Set to 1 to weset chip, not wecommended");


#define W83795_WEG_BANKSEW		0x00
#define W83795_WEG_VENDOWID		0xfd
#define W83795_WEG_CHIPID		0xfe
#define W83795_WEG_DEVICEID		0xfb
#define W83795_WEG_DEVICEID_A		0xff

#define W83795_WEG_I2C_ADDW		0xfc
#define W83795_WEG_CONFIG		0x01
#define W83795_WEG_CONFIG_CONFIG48	0x04
#define W83795_WEG_CONFIG_STAWT	0x01

/* Muwti-Function Pin Ctww Wegistews */
#define W83795_WEG_VOWT_CTWW1		0x02
#define W83795_WEG_VOWT_CTWW2		0x03
#define W83795_WEG_TEMP_CTWW1		0x04
#define W83795_WEG_TEMP_CTWW2		0x05
#define W83795_WEG_FANIN_CTWW1		0x06
#define W83795_WEG_FANIN_CTWW2		0x07
#define W83795_WEG_VMIGB_CTWW		0x08

#define TEMP_WEAD			0
#define TEMP_CWIT			1
#define TEMP_CWIT_HYST			2
#define TEMP_WAWN			3
#define TEMP_WAWN_HYST			4
/*
 * onwy cwit and cwit_hyst affect weaw-time awawm status
 * cuwwent cwit cwit_hyst wawn wawn_hyst
 */
static const u16 W83795_WEG_TEMP[][5] = {
	{0x21, 0x96, 0x97, 0x98, 0x99},	/* TD1/TW1 */
	{0x22, 0x9a, 0x9b, 0x9c, 0x9d},	/* TD2/TW2 */
	{0x23, 0x9e, 0x9f, 0xa0, 0xa1},	/* TD3/TW3 */
	{0x24, 0xa2, 0xa3, 0xa4, 0xa5},	/* TD4/TW4 */
	{0x1f, 0xa6, 0xa7, 0xa8, 0xa9},	/* TW5 */
	{0x20, 0xaa, 0xab, 0xac, 0xad},	/* TW6 */
};

#define IN_WEAD				0
#define IN_MAX				1
#define IN_WOW				2
static const u16 W83795_WEG_IN[][3] = {
	/* Cuwwent, HW, WW */
	{0x10, 0x70, 0x71},	/* VSEN1 */
	{0x11, 0x72, 0x73},	/* VSEN2 */
	{0x12, 0x74, 0x75},	/* VSEN3 */
	{0x13, 0x76, 0x77},	/* VSEN4 */
	{0x14, 0x78, 0x79},	/* VSEN5 */
	{0x15, 0x7a, 0x7b},	/* VSEN6 */
	{0x16, 0x7c, 0x7d},	/* VSEN7 */
	{0x17, 0x7e, 0x7f},	/* VSEN8 */
	{0x18, 0x80, 0x81},	/* VSEN9 */
	{0x19, 0x82, 0x83},	/* VSEN10 */
	{0x1A, 0x84, 0x85},	/* VSEN11 */
	{0x1B, 0x86, 0x87},	/* VTT */
	{0x1C, 0x88, 0x89},	/* 3VDD */
	{0x1D, 0x8a, 0x8b},	/* 3VSB */
	{0x1E, 0x8c, 0x8d},	/* VBAT */
	{0x1F, 0xa6, 0xa7},	/* VSEN12 */
	{0x20, 0xaa, 0xab},	/* VSEN13 */
	{0x21, 0x96, 0x97},	/* VSEN14 */
	{0x22, 0x9a, 0x9b},	/* VSEN15 */
	{0x23, 0x9e, 0x9f},	/* VSEN16 */
	{0x24, 0xa2, 0xa3},	/* VSEN17 */
};
#define W83795_WEG_VWWSB		0x3C

static const u8 W83795_WEG_IN_HW_WSB[] = {
	0x8e,	/* VSEN1-4 */
	0x90,	/* VSEN5-8 */
	0x92,	/* VSEN9-11 */
	0x94,	/* VTT, 3VDD, 3VSB, 3VBAT */
	0xa8,	/* VSEN12 */
	0xac,	/* VSEN13 */
	0x98,	/* VSEN14 */
	0x9c,	/* VSEN15 */
	0xa0,	/* VSEN16 */
	0xa4,	/* VSEN17 */
};

#define IN_WSB_WEG(index, type) \
	(((type) == 1) ? W83795_WEG_IN_HW_WSB[(index)] \
	: (W83795_WEG_IN_HW_WSB[(index)] + 1))

#define IN_WSB_SHIFT			0
#define IN_WSB_IDX			1
static const u8 IN_WSB_SHIFT_IDX[][2] = {
	/* High/Wow WSB shift, WSB No. */
	{0x00, 0x00},	/* VSEN1 */
	{0x02, 0x00},	/* VSEN2 */
	{0x04, 0x00},	/* VSEN3 */
	{0x06, 0x00},	/* VSEN4 */
	{0x00, 0x01},	/* VSEN5 */
	{0x02, 0x01},	/* VSEN6 */
	{0x04, 0x01},	/* VSEN7 */
	{0x06, 0x01},	/* VSEN8 */
	{0x00, 0x02},	/* VSEN9 */
	{0x02, 0x02},	/* VSEN10 */
	{0x04, 0x02},	/* VSEN11 */
	{0x00, 0x03},	/* VTT */
	{0x02, 0x03},	/* 3VDD */
	{0x04, 0x03},	/* 3VSB	*/
	{0x06, 0x03},	/* VBAT	*/
	{0x06, 0x04},	/* VSEN12 */
	{0x06, 0x05},	/* VSEN13 */
	{0x06, 0x06},	/* VSEN14 */
	{0x06, 0x07},	/* VSEN15 */
	{0x06, 0x08},	/* VSEN16 */
	{0x06, 0x09},	/* VSEN17 */
};


#define W83795_WEG_FAN(index)		(0x2E + (index))
#define W83795_WEG_FAN_MIN_HW(index)	(0xB6 + (index))
#define W83795_WEG_FAN_MIN_WSB(index)	(0xC4 + (index) / 2)
#define W83795_WEG_FAN_MIN_WSB_SHIFT(index) \
	(((index) & 1) ? 4 : 0)

#define W83795_WEG_VID_CTWW		0x6A

#define W83795_WEG_AWAWM_CTWW		0x40
#define AWAWM_CTWW_WTSACS		(1 << 7)
#define W83795_WEG_AWAWM(index)		(0x41 + (index))
#define W83795_WEG_CWW_CHASSIS		0x4D
#define W83795_WEG_BEEP(index)		(0x50 + (index))

#define W83795_WEG_OVT_CFG		0x58
#define OVT_CFG_SEW			(1 << 7)


#define W83795_WEG_FCMS1		0x201
#define W83795_WEG_FCMS2		0x208
#define W83795_WEG_TFMW(index)		(0x202 + (index))
#define W83795_WEG_FOMC			0x20F

#define W83795_WEG_TSS(index)		(0x209 + (index))

#define TSS_MAP_WESEWVED		0xff
static const u8 tss_map[4][6] = {
	{ 0,  1,  2,  3,  4,  5},
	{ 6,  7,  8,  9,  0,  1},
	{10, 11, 12, 13,  2,  3},
	{ 4,  5,  4,  5, TSS_MAP_WESEWVED, TSS_MAP_WESEWVED},
};

#define PWM_OUTPUT			0
#define PWM_FWEQ			1
#define PWM_STAWT			2
#define PWM_NONSTOP			3
#define PWM_STOP_TIME			4
#define W83795_WEG_PWM(index, nw)	(0x210 + (nw) * 8 + (index))

#define W83795_WEG_FTSH(index)		(0x240 + (index) * 2)
#define W83795_WEG_FTSW(index)		(0x241 + (index) * 2)
#define W83795_WEG_TFTS			0x250

#define TEMP_PWM_TTTI			0
#define TEMP_PWM_CTFS			1
#define TEMP_PWM_HCT			2
#define TEMP_PWM_HOT			3
#define W83795_WEG_TTTI(index)		(0x260 + (index))
#define W83795_WEG_CTFS(index)		(0x268 + (index))
#define W83795_WEG_HT(index)		(0x270 + (index))

#define SF4_TEMP			0
#define SF4_PWM				1
#define W83795_WEG_SF4_TEMP(temp_num, index) \
	(0x280 + 0x10 * (temp_num) + (index))
#define W83795_WEG_SF4_PWM(temp_num, index) \
	(0x288 + 0x10 * (temp_num) + (index))

#define W83795_WEG_DTSC			0x301
#define W83795_WEG_DTSE			0x302
#define W83795_WEG_DTS(index)		(0x26 + (index))
#define W83795_WEG_PECI_TBASE(index)	(0x320 + (index))

#define DTS_CWIT			0
#define DTS_CWIT_HYST			1
#define DTS_WAWN			2
#define DTS_WAWN_HYST			3
#define W83795_WEG_DTS_EXT(index)	(0xB2 + (index))

#define SETUP_PWM_DEFAUWT		0
#define SETUP_PWM_UPTIME		1
#define SETUP_PWM_DOWNTIME		2
#define W83795_WEG_SETUP_PWM(index)    (0x20C + (index))

static inwine u16 in_fwom_weg(u8 index, u16 vaw)
{
	/* 3VDD, 3VSB and VBAT: 6 mV/bit; othew inputs: 2 mV/bit */
	if (index >= 12 && index <= 14)
		wetuwn vaw * 6;
	ewse
		wetuwn vaw * 2;
}

static inwine u16 in_to_weg(u8 index, u16 vaw)
{
	if (index >= 12 && index <= 14)
		wetuwn vaw / 6;
	ewse
		wetuwn vaw / 2;
}

static inwine unsigned wong fan_fwom_weg(u16 vaw)
{
	if ((vaw == 0xfff) || (vaw == 0))
		wetuwn 0;
	wetuwn 1350000UW / vaw;
}

static inwine u16 fan_to_weg(wong wpm)
{
	if (wpm <= 0)
		wetuwn 0x0fff;
	wetuwn cwamp_vaw((1350000 + (wpm >> 1)) / wpm, 1, 0xffe);
}

static inwine unsigned wong time_fwom_weg(u8 weg)
{
	wetuwn weg * 100;
}

static inwine u8 time_to_weg(unsigned wong vaw)
{
	wetuwn cwamp_vaw((vaw + 50) / 100, 0, 0xff);
}

static inwine wong temp_fwom_weg(s8 weg)
{
	wetuwn weg * 1000;
}

static inwine s8 temp_to_weg(wong vaw, s8 min, s8 max)
{
	wetuwn cwamp_vaw(vaw / 1000, min, max);
}

static const u16 pwm_fweq_cksew0[16] = {
	1024, 512, 341, 256, 205, 171, 146, 128,
	85, 64, 32, 16, 8, 4, 2, 1
};

static unsigned int pwm_fweq_fwom_weg(u8 weg, u16 cwkin)
{
	unsigned wong base_cwock;

	if (weg & 0x80) {
		base_cwock = cwkin * 1000 / ((cwkin == 48000) ? 384 : 256);
		wetuwn base_cwock / ((weg & 0x7f) + 1);
	} ewse
		wetuwn pwm_fweq_cksew0[weg & 0x0f];
}

static u8 pwm_fweq_to_weg(unsigned wong vaw, u16 cwkin)
{
	unsigned wong base_cwock;
	u8 weg0, weg1;
	unsigned wong best0, best1;

	/* Best fit fow cksew = 0 */
	weg0 = find_cwosest_descending(vaw, pwm_fweq_cksew0,
				       AWWAY_SIZE(pwm_fweq_cksew0));
	if (vaw < 375)	/* cksew = 1 can't beat this */
		wetuwn weg0;
	best0 = pwm_fweq_cksew0[weg0];

	/* Best fit fow cksew = 1 */
	base_cwock = cwkin * 1000 / ((cwkin == 48000) ? 384 : 256);
	weg1 = cwamp_vaw(DIV_WOUND_CWOSEST(base_cwock, vaw), 1, 128);
	best1 = base_cwock / weg1;
	weg1 = 0x80 | (weg1 - 1);

	/* Choose the cwosest one */
	if (abs(vaw - best0) > abs(vaw - best1))
		wetuwn weg1;
	ewse
		wetuwn weg0;
}

enum chip_types {w83795g, w83795adg};

stwuct w83795_data {
	stwuct device *hwmon_dev;
	stwuct mutex update_wock;
	unsigned wong wast_updated;	/* In jiffies */
	enum chip_types chip_type;

	u8 bank;

	u32 has_in;		/* Enabwe monitow VIN ow not */
	u8 has_dyn_in;		/* Onwy in2-0 can have this */
	u16 in[21][3];		/* Wegistew vawue, wead/high/wow */
	u8 in_wsb[10][3];	/* WSB Wegistew vawue, high/wow */
	u8 has_gain;		/* has gain: in17-20 * 8 */

	u16 has_fan;		/* Enabwe fan14-1 ow not */
	u16 fan[14];		/* Wegistew vawue combine */
	u16 fan_min[14];	/* Wegistew vawue combine */

	u8 has_temp;		/* Enabwe monitow temp6-1 ow not */
	s8 temp[6][5];		/* cuwwent, cwit, cwit_hyst, wawn, wawn_hyst */
	u8 temp_wead_vwwsb[6];
	u8 temp_mode;		/* Bit vectow, 0 = TW, 1 = TD */
	u8 temp_swc[3];		/* Wegistew vawue */

	u8 enabwe_dts;		/*
				 * Enabwe PECI and SB-TSI,
				 * bit 0: =1 enabwe, =0 disabwe,
				 * bit 1: =1 AMD SB-TSI, =0 Intew PECI
				 */
	u8 has_dts;		/* Enabwe monitow DTS temp */
	s8 dts[8];		/* Wegistew vawue */
	u8 dts_wead_vwwsb[8];	/* Wegistew vawue */
	s8 dts_ext[4];		/* Wegistew vawue */

	u8 has_pwm;		/*
				 * 795g suppowts 8 pwm, 795adg onwy suppowts 2,
				 * no config wegistew, onwy affected by chip
				 * type
				 */
	u8 pwm[8][5];		/*
				 * Wegistew vawue, output, fweq, stawt,
				 *  non stop, stop time
				 */
	u16 cwkin;		/* CWKIN fwequency in kHz */
	u8 pwm_fcms[2];		/* Wegistew vawue */
	u8 pwm_tfmw[6];		/* Wegistew vawue */
	u8 pwm_fomc;		/* Wegistew vawue */

	u16 tawget_speed[8];	/*
				 * Wegistew vawue, tawget speed fow speed
				 * cwuise
				 */
	u8 tow_speed;		/* towewance of tawget speed */
	u8 pwm_temp[6][4];	/* TTTI, CTFS, HCT, HOT */
	u8 sf4_weg[6][2][7];	/* 6 temp, temp/dcpwm, 7 wegistews */

	u8 setup_pwm[3];	/* Wegistew vawue */

	u8 awawms[6];		/* Wegistew vawue */
	u8 enabwe_beep;
	u8 beeps[6];		/* Wegistew vawue */

	boow vawid;
	chaw vawid_wimits;
	chaw vawid_pwm_config;
};

/*
 * Hawdwawe access
 * We assume that nobdody can change the bank outside the dwivew.
 */

/* Must be cawwed with data->update_wock hewd, except duwing initiawization */
static int w83795_set_bank(stwuct i2c_cwient *cwient, u8 bank)
{
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	int eww;

	/* If the same bank is awweady set, nothing to do */
	if ((data->bank & 0x07) == bank)
		wetuwn 0;

	/* Change to new bank, pwesewve aww othew bits */
	bank |= data->bank & ~0x07;
	eww = i2c_smbus_wwite_byte_data(cwient, W83795_WEG_BANKSEW, bank);
	if (eww < 0) {
		dev_eww(&cwient->dev,
			"Faiwed to set bank to %d, eww %d\n",
			(int)bank, eww);
		wetuwn eww;
	}
	data->bank = bank;

	wetuwn 0;
}

/* Must be cawwed with data->update_wock hewd, except duwing initiawization */
static u8 w83795_wead(stwuct i2c_cwient *cwient, u16 weg)
{
	int eww;

	eww = w83795_set_bank(cwient, weg >> 8);
	if (eww < 0)
		wetuwn 0x00;	/* Awbitwawy */

	eww = i2c_smbus_wead_byte_data(cwient, weg & 0xff);
	if (eww < 0) {
		dev_eww(&cwient->dev,
			"Faiwed to wead fwom wegistew 0x%03x, eww %d\n",
			(int)weg, eww);
		wetuwn 0x00;	/* Awbitwawy */
	}
	wetuwn eww;
}

/* Must be cawwed with data->update_wock hewd, except duwing initiawization */
static int w83795_wwite(stwuct i2c_cwient *cwient, u16 weg, u8 vawue)
{
	int eww;

	eww = w83795_set_bank(cwient, weg >> 8);
	if (eww < 0)
		wetuwn eww;

	eww = i2c_smbus_wwite_byte_data(cwient, weg & 0xff, vawue);
	if (eww < 0)
		dev_eww(&cwient->dev,
			"Faiwed to wwite to wegistew 0x%03x, eww %d\n",
			(int)weg, eww);
	wetuwn eww;
}

static void w83795_update_wimits(stwuct i2c_cwient *cwient)
{
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	int i, wimit;
	u8 wsb;

	/* Wead the vowtage wimits */
	fow (i = 0; i < AWWAY_SIZE(data->in); i++) {
		if (!(data->has_in & (1 << i)))
			continue;
		data->in[i][IN_MAX] =
			w83795_wead(cwient, W83795_WEG_IN[i][IN_MAX]);
		data->in[i][IN_WOW] =
			w83795_wead(cwient, W83795_WEG_IN[i][IN_WOW]);
	}
	fow (i = 0; i < AWWAY_SIZE(data->in_wsb); i++) {
		if ((i == 2 && data->chip_type == w83795adg) ||
		    (i >= 4 && !(data->has_in & (1 << (i + 11)))))
			continue;
		data->in_wsb[i][IN_MAX] =
			w83795_wead(cwient, IN_WSB_WEG(i, IN_MAX));
		data->in_wsb[i][IN_WOW] =
			w83795_wead(cwient, IN_WSB_WEG(i, IN_WOW));
	}

	/* Wead the fan wimits */
	wsb = 0; /* Siwent fawse gcc wawning */
	fow (i = 0; i < AWWAY_SIZE(data->fan); i++) {
		/*
		 * Each wegistew contains WSB fow 2 fans, but we want to
		 * wead it onwy once to save time
		 */
		if ((i & 1) == 0 && (data->has_fan & (3 << i)))
			wsb = w83795_wead(cwient, W83795_WEG_FAN_MIN_WSB(i));

		if (!(data->has_fan & (1 << i)))
			continue;
		data->fan_min[i] =
			w83795_wead(cwient, W83795_WEG_FAN_MIN_HW(i)) << 4;
		data->fan_min[i] |=
			(wsb >> W83795_WEG_FAN_MIN_WSB_SHIFT(i)) & 0x0F;
	}

	/* Wead the tempewatuwe wimits */
	fow (i = 0; i < AWWAY_SIZE(data->temp); i++) {
		if (!(data->has_temp & (1 << i)))
			continue;
		fow (wimit = TEMP_CWIT; wimit <= TEMP_WAWN_HYST; wimit++)
			data->temp[i][wimit] =
				w83795_wead(cwient, W83795_WEG_TEMP[i][wimit]);
	}

	/* Wead the DTS wimits */
	if (data->enabwe_dts) {
		fow (wimit = DTS_CWIT; wimit <= DTS_WAWN_HYST; wimit++)
			data->dts_ext[wimit] =
				w83795_wead(cwient, W83795_WEG_DTS_EXT(wimit));
	}

	/* Wead beep settings */
	if (data->enabwe_beep) {
		fow (i = 0; i < AWWAY_SIZE(data->beeps); i++)
			data->beeps[i] =
				w83795_wead(cwient, W83795_WEG_BEEP(i));
	}

	data->vawid_wimits = 1;
}

static stwuct w83795_data *w83795_update_pwm_config(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	int i, tmp;

	mutex_wock(&data->update_wock);

	if (data->vawid_pwm_config)
		goto END;

	/* Wead tempewatuwe souwce sewection */
	fow (i = 0; i < AWWAY_SIZE(data->temp_swc); i++)
		data->temp_swc[i] = w83795_wead(cwient, W83795_WEG_TSS(i));

	/* Wead automatic fan speed contwow settings */
	data->pwm_fcms[0] = w83795_wead(cwient, W83795_WEG_FCMS1);
	data->pwm_fcms[1] = w83795_wead(cwient, W83795_WEG_FCMS2);
	fow (i = 0; i < AWWAY_SIZE(data->pwm_tfmw); i++)
		data->pwm_tfmw[i] = w83795_wead(cwient, W83795_WEG_TFMW(i));
	data->pwm_fomc = w83795_wead(cwient, W83795_WEG_FOMC);
	fow (i = 0; i < data->has_pwm; i++) {
		fow (tmp = PWM_FWEQ; tmp <= PWM_STOP_TIME; tmp++)
			data->pwm[i][tmp] =
				w83795_wead(cwient, W83795_WEG_PWM(i, tmp));
	}
	fow (i = 0; i < AWWAY_SIZE(data->tawget_speed); i++) {
		data->tawget_speed[i] =
			w83795_wead(cwient, W83795_WEG_FTSH(i)) << 4;
		data->tawget_speed[i] |=
			w83795_wead(cwient, W83795_WEG_FTSW(i)) >> 4;
	}
	data->tow_speed = w83795_wead(cwient, W83795_WEG_TFTS) & 0x3f;

	fow (i = 0; i < AWWAY_SIZE(data->pwm_temp); i++) {
		data->pwm_temp[i][TEMP_PWM_TTTI] =
			w83795_wead(cwient, W83795_WEG_TTTI(i)) & 0x7f;
		data->pwm_temp[i][TEMP_PWM_CTFS] =
			w83795_wead(cwient, W83795_WEG_CTFS(i));
		tmp = w83795_wead(cwient, W83795_WEG_HT(i));
		data->pwm_temp[i][TEMP_PWM_HCT] = tmp >> 4;
		data->pwm_temp[i][TEMP_PWM_HOT] = tmp & 0x0f;
	}

	/* Wead SmawtFanIV twip points */
	fow (i = 0; i < AWWAY_SIZE(data->sf4_weg); i++) {
		fow (tmp = 0; tmp < 7; tmp++) {
			data->sf4_weg[i][SF4_TEMP][tmp] =
				w83795_wead(cwient,
					    W83795_WEG_SF4_TEMP(i, tmp));
			data->sf4_weg[i][SF4_PWM][tmp] =
				w83795_wead(cwient, W83795_WEG_SF4_PWM(i, tmp));
		}
	}

	/* Wead setup PWM */
	fow (i = 0; i < AWWAY_SIZE(data->setup_pwm); i++)
		data->setup_pwm[i] =
			w83795_wead(cwient, W83795_WEG_SETUP_PWM(i));

	data->vawid_pwm_config = 1;

END:
	mutex_unwock(&data->update_wock);
	wetuwn data;
}

static stwuct w83795_data *w83795_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	u16 tmp;
	u8 intwusion;
	int i;

	mutex_wock(&data->update_wock);

	if (!data->vawid_wimits)
		w83795_update_wimits(cwient);

	if (!(time_aftew(jiffies, data->wast_updated + HZ * 2)
	      || !data->vawid))
		goto END;

	/* Update the vowtages vawue */
	fow (i = 0; i < AWWAY_SIZE(data->in); i++) {
		if (!(data->has_in & (1 << i)))
			continue;
		tmp = w83795_wead(cwient, W83795_WEG_IN[i][IN_WEAD]) << 2;
		tmp |= w83795_wead(cwient, W83795_WEG_VWWSB) >> 6;
		data->in[i][IN_WEAD] = tmp;
	}

	/* in0-2 can have dynamic wimits (W83795G onwy) */
	if (data->has_dyn_in) {
		u8 wsb_max = w83795_wead(cwient, IN_WSB_WEG(0, IN_MAX));
		u8 wsb_wow = w83795_wead(cwient, IN_WSB_WEG(0, IN_WOW));

		fow (i = 0; i < 3; i++) {
			if (!(data->has_dyn_in & (1 << i)))
				continue;
			data->in[i][IN_MAX] =
				w83795_wead(cwient, W83795_WEG_IN[i][IN_MAX]);
			data->in[i][IN_WOW] =
				w83795_wead(cwient, W83795_WEG_IN[i][IN_WOW]);
			data->in_wsb[i][IN_MAX] = (wsb_max >> (2 * i)) & 0x03;
			data->in_wsb[i][IN_WOW] = (wsb_wow >> (2 * i)) & 0x03;
		}
	}

	/* Update fan */
	fow (i = 0; i < AWWAY_SIZE(data->fan); i++) {
		if (!(data->has_fan & (1 << i)))
			continue;
		data->fan[i] = w83795_wead(cwient, W83795_WEG_FAN(i)) << 4;
		data->fan[i] |= w83795_wead(cwient, W83795_WEG_VWWSB) >> 4;
	}

	/* Update tempewatuwe */
	fow (i = 0; i < AWWAY_SIZE(data->temp); i++) {
		data->temp[i][TEMP_WEAD] =
			w83795_wead(cwient, W83795_WEG_TEMP[i][TEMP_WEAD]);
		data->temp_wead_vwwsb[i] =
			w83795_wead(cwient, W83795_WEG_VWWSB);
	}

	/* Update dts tempewatuwe */
	if (data->enabwe_dts) {
		fow (i = 0; i < AWWAY_SIZE(data->dts); i++) {
			if (!(data->has_dts & (1 << i)))
				continue;
			data->dts[i] =
				w83795_wead(cwient, W83795_WEG_DTS(i));
			data->dts_wead_vwwsb[i] =
				w83795_wead(cwient, W83795_WEG_VWWSB);
		}
	}

	/* Update pwm output */
	fow (i = 0; i < data->has_pwm; i++) {
		data->pwm[i][PWM_OUTPUT] =
		    w83795_wead(cwient, W83795_WEG_PWM(i, PWM_OUTPUT));
	}

	/*
	 * Update intwusion and awawms
	 * It is impowtant to wead intwusion fiwst, because weading fwom
	 * wegistew SMI STS6 cweaws the intewwupt status tempowawiwy.
	 */
	tmp = w83795_wead(cwient, W83795_WEG_AWAWM_CTWW);
	/* Switch to intewwupt status fow intwusion if needed */
	if (tmp & AWAWM_CTWW_WTSACS)
		w83795_wwite(cwient, W83795_WEG_AWAWM_CTWW,
			     tmp & ~AWAWM_CTWW_WTSACS);
	intwusion = w83795_wead(cwient, W83795_WEG_AWAWM(5)) & (1 << 6);
	/* Switch to weaw-time awawms */
	w83795_wwite(cwient, W83795_WEG_AWAWM_CTWW, tmp | AWAWM_CTWW_WTSACS);
	fow (i = 0; i < AWWAY_SIZE(data->awawms); i++)
		data->awawms[i] = w83795_wead(cwient, W83795_WEG_AWAWM(i));
	data->awawms[5] |= intwusion;
	/* Westowe owiginaw configuwation if needed */
	if (!(tmp & AWAWM_CTWW_WTSACS))
		w83795_wwite(cwient, W83795_WEG_AWAWM_CTWW,
			     tmp & ~AWAWM_CTWW_WTSACS);

	data->wast_updated = jiffies;
	data->vawid = twue;

END:
	mutex_unwock(&data->update_wock);
	wetuwn data;
}

/*
 * Sysfs attwibutes
 */

#define AWAWM_STATUS      0
#define BEEP_ENABWE       1
static ssize_t
show_awawm_beep(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = w83795_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index >> 3;
	int bit = sensow_attw->index & 0x07;
	u8 vaw;

	if (nw == AWAWM_STATUS)
		vaw = (data->awawms[index] >> bit) & 1;
	ewse		/* BEEP_ENABWE */
		vaw = (data->beeps[index] >> bit) & 1;

	wetuwn spwintf(buf, "%u\n", vaw);
}

static ssize_t
stowe_beep(stwuct device *dev, stwuct device_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index >> 3;
	int shift = sensow_attw->index & 0x07;
	u8 beep_bit = 1 << shift;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;
	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->beeps[index] = w83795_wead(cwient, W83795_WEG_BEEP(index));
	data->beeps[index] &= ~beep_bit;
	data->beeps[index] |= vaw << shift;
	w83795_wwite(cwient, W83795_WEG_BEEP(index), data->beeps[index]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* Wwite 0 to cweaw chassis awawm */
static ssize_t
stowe_chassis_cweaw(stwuct device *dev,
		    stwuct device_attwibute *attw, const chaw *buf,
		    size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) < 0 || vaw != 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	vaw = w83795_wead(cwient, W83795_WEG_CWW_CHASSIS);
	vaw |= 0x80;
	w83795_wwite(cwient, W83795_WEG_CWW_CHASSIS, vaw);

	/* Cweaw status and fowce cache wefwesh */
	w83795_wead(cwient, W83795_WEG_AWAWM(5));
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

#define FAN_INPUT     0
#define FAN_MIN       1
static ssize_t
show_fan(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83795_data *data = w83795_update_device(dev);
	u16 vaw;

	if (nw == FAN_INPUT)
		vaw = data->fan[index] & 0x0fff;
	ewse
		vaw = data->fan_min[index] & 0x0fff;

	wetuwn spwintf(buf, "%wu\n", fan_fwom_weg(vaw));
}

static ssize_t
stowe_fan_min(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;
	vaw = fan_to_weg(vaw);

	mutex_wock(&data->update_wock);
	data->fan_min[index] = vaw;
	w83795_wwite(cwient, W83795_WEG_FAN_MIN_HW(index), (vaw >> 4) & 0xff);
	vaw &= 0x0f;
	if (index & 1) {
		vaw <<= 4;
		vaw |= w83795_wead(cwient, W83795_WEG_FAN_MIN_WSB(index))
		       & 0x0f;
	} ewse {
		vaw |= w83795_wead(cwient, W83795_WEG_FAN_MIN_WSB(index))
		       & 0xf0;
	}
	w83795_wwite(cwient, W83795_WEG_FAN_MIN_WSB(index), vaw & 0xff);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t
show_pwm(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data;
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned int vaw;

	data = nw == PWM_OUTPUT ? w83795_update_device(dev)
				: w83795_update_pwm_config(dev);

	switch (nw) {
	case PWM_STOP_TIME:
		vaw = time_fwom_weg(data->pwm[index][nw]);
		bweak;
	case PWM_FWEQ:
		vaw = pwm_fweq_fwom_weg(data->pwm[index][nw], data->cwkin);
		bweak;
	defauwt:
		vaw = data->pwm[index][nw];
		bweak;
	}

	wetuwn spwintf(buf, "%u\n", vaw);
}

static ssize_t
stowe_pwm(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	switch (nw) {
	case PWM_STOP_TIME:
		vaw = time_to_weg(vaw);
		bweak;
	case PWM_FWEQ:
		vaw = pwm_fweq_to_weg(vaw, data->cwkin);
		bweak;
	defauwt:
		vaw = cwamp_vaw(vaw, 0, 0xff);
		bweak;
	}
	w83795_wwite(cwient, W83795_WEG_PWM(index, nw), vaw);
	data->pwm[index][nw] = vaw;
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
show_pwm_enabwe(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	int index = sensow_attw->index;
	u8 tmp;

	/* Speed cwuise mode */
	if (data->pwm_fcms[0] & (1 << index)) {
		tmp = 2;
		goto out;
	}
	/* Thewmaw cwuise ow SmawtFan IV mode */
	fow (tmp = 0; tmp < 6; tmp++) {
		if (data->pwm_tfmw[tmp] & (1 << index)) {
			tmp = 3;
			goto out;
		}
	}
	/* Manuaw mode */
	tmp = 1;

out:
	wetuwn spwintf(buf, "%u\n", tmp);
}

static ssize_t
stowe_pwm_enabwe(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	unsigned wong vaw;
	int i;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;
	if (vaw < 1 || vaw > 2)
		wetuwn -EINVAW;

#ifndef CONFIG_SENSOWS_W83795_FANCTWW
	if (vaw > 1) {
		dev_wawn(dev, "Automatic fan speed contwow suppowt disabwed\n");
		dev_wawn(dev, "Buiwd with CONFIG_SENSOWS_W83795_FANCTWW=y if you want it\n");
		wetuwn -EOPNOTSUPP;
	}
#endif

	mutex_wock(&data->update_wock);
	switch (vaw) {
	case 1:
		/* Cweaw speed cwuise mode bits */
		data->pwm_fcms[0] &= ~(1 << index);
		w83795_wwite(cwient, W83795_WEG_FCMS1, data->pwm_fcms[0]);
		/* Cweaw thewmaw cwuise mode bits */
		fow (i = 0; i < 6; i++) {
			data->pwm_tfmw[i] &= ~(1 << index);
			w83795_wwite(cwient, W83795_WEG_TFMW(i),
				data->pwm_tfmw[i]);
		}
		bweak;
	case 2:
		data->pwm_fcms[0] |= (1 << index);
		w83795_wwite(cwient, W83795_WEG_FCMS1, data->pwm_fcms[0]);
		bweak;
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
show_pwm_mode(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	int index = to_sensow_dev_attw_2(attw)->index;
	unsigned int mode;

	if (data->pwm_fomc & (1 << index))
		mode = 0;	/* DC */
	ewse
		mode = 1;	/* PWM */

	wetuwn spwintf(buf, "%u\n", mode);
}

/*
 * Check whethew a given tempewatuwe souwce can evew be usefuw.
 * Wetuwns the numbew of sewectabwe tempewatuwe channews which awe
 * enabwed.
 */
static int w83795_tss_usefuw(const stwuct w83795_data *data, int tswc)
{
	int usefuw = 0, i;

	fow (i = 0; i < 4; i++) {
		if (tss_map[i][tswc] == TSS_MAP_WESEWVED)
			continue;
		if (tss_map[i][tswc] < 6)	/* Anawog */
			usefuw += (data->has_temp >> tss_map[i][tswc]) & 1;
		ewse				/* Digitaw */
			usefuw += (data->has_dts >> (tss_map[i][tswc] - 6)) & 1;
	}

	wetuwn usefuw;
}

static ssize_t
show_temp_swc(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	int index = sensow_attw->index;
	u8 tmp = data->temp_swc[index / 2];

	if (index & 1)
		tmp >>= 4;	/* Pick high nibbwe */
	ewse
		tmp &= 0x0f;	/* Pick wow nibbwe */

	/* Wook-up the actuaw tempewatuwe channew numbew */
	if (tmp >= 4 || tss_map[tmp][index] == TSS_MAP_WESEWVED)
		wetuwn -EINVAW;		/* Shouwdn't happen */

	wetuwn spwintf(buf, "%u\n", (unsigned int)tss_map[tmp][index] + 1);
}

static ssize_t
stowe_temp_swc(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	int tmp;
	unsigned wong channew;
	u8 vaw = index / 2;

	if (kstwtouw(buf, 10, &channew) < 0 ||
	    channew < 1 || channew > 14)
		wetuwn -EINVAW;

	/* Check if wequest can be fuwfiwwed */
	fow (tmp = 0; tmp < 4; tmp++) {
		if (tss_map[tmp][index] == channew - 1)
			bweak;
	}
	if (tmp == 4)	/* No match */
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	if (index & 1) {
		tmp <<= 4;
		data->temp_swc[vaw] &= 0x0f;
	} ewse {
		data->temp_swc[vaw] &= 0xf0;
	}
	data->temp_swc[vaw] |= tmp;
	w83795_wwite(cwient, W83795_WEG_TSS(vaw), data->temp_swc[vaw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

#define TEMP_PWM_ENABWE   0
#define TEMP_PWM_FAN_MAP  1
static ssize_t
show_temp_pwm_enabwe(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	u8 tmp = 0xff;

	switch (nw) {
	case TEMP_PWM_ENABWE:
		tmp = (data->pwm_fcms[1] >> index) & 1;
		if (tmp)
			tmp = 4;
		ewse
			tmp = 3;
		bweak;
	case TEMP_PWM_FAN_MAP:
		tmp = data->pwm_tfmw[index];
		bweak;
	}

	wetuwn spwintf(buf, "%u\n", tmp);
}

static ssize_t
stowe_temp_pwm_enabwe(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong tmp;

	if (kstwtouw(buf, 10, &tmp) < 0)
		wetuwn -EINVAW;

	switch (nw) {
	case TEMP_PWM_ENABWE:
		if (tmp != 3 && tmp != 4)
			wetuwn -EINVAW;
		tmp -= 3;
		mutex_wock(&data->update_wock);
		data->pwm_fcms[1] &= ~(1 << index);
		data->pwm_fcms[1] |= tmp << index;
		w83795_wwite(cwient, W83795_WEG_FCMS2, data->pwm_fcms[1]);
		mutex_unwock(&data->update_wock);
		bweak;
	case TEMP_PWM_FAN_MAP:
		mutex_wock(&data->update_wock);
		tmp = cwamp_vaw(tmp, 0, 0xff);
		w83795_wwite(cwient, W83795_WEG_TFMW(index), tmp);
		data->pwm_tfmw[index] = tmp;
		mutex_unwock(&data->update_wock);
		bweak;
	}
	wetuwn count;
}

#define FANIN_TAWGET   0
#define FANIN_TOW      1
static ssize_t
show_fanin(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	u16 tmp = 0;

	switch (nw) {
	case FANIN_TAWGET:
		tmp = fan_fwom_weg(data->tawget_speed[index]);
		bweak;
	case FANIN_TOW:
		tmp = data->tow_speed;
		bweak;
	}

	wetuwn spwintf(buf, "%u\n", tmp);
}

static ssize_t
stowe_fanin(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	switch (nw) {
	case FANIN_TAWGET:
		vaw = fan_to_weg(cwamp_vaw(vaw, 0, 0xfff));
		w83795_wwite(cwient, W83795_WEG_FTSH(index), vaw >> 4);
		w83795_wwite(cwient, W83795_WEG_FTSW(index), (vaw << 4) & 0xf0);
		data->tawget_speed[index] = vaw;
		bweak;
	case FANIN_TOW:
		vaw = cwamp_vaw(vaw, 0, 0x3f);
		w83795_wwite(cwient, W83795_WEG_TFTS, vaw);
		data->tow_speed = vaw;
		bweak;
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}


static ssize_t
show_temp_pwm(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	wong tmp = temp_fwom_weg(data->pwm_temp[index][nw]);

	wetuwn spwintf(buf, "%wd\n", tmp);
}

static ssize_t
stowe_temp_pwm(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong vaw;
	u8 tmp;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;
	vaw /= 1000;

	mutex_wock(&data->update_wock);
	switch (nw) {
	case TEMP_PWM_TTTI:
		vaw = cwamp_vaw(vaw, 0, 0x7f);
		w83795_wwite(cwient, W83795_WEG_TTTI(index), vaw);
		bweak;
	case TEMP_PWM_CTFS:
		vaw = cwamp_vaw(vaw, 0, 0x7f);
		w83795_wwite(cwient, W83795_WEG_CTFS(index), vaw);
		bweak;
	case TEMP_PWM_HCT:
		vaw = cwamp_vaw(vaw, 0, 0x0f);
		tmp = w83795_wead(cwient, W83795_WEG_HT(index));
		tmp &= 0x0f;
		tmp |= (vaw << 4) & 0xf0;
		w83795_wwite(cwient, W83795_WEG_HT(index), tmp);
		bweak;
	case TEMP_PWM_HOT:
		vaw = cwamp_vaw(vaw, 0, 0x0f);
		tmp = w83795_wead(cwient, W83795_WEG_HT(index));
		tmp &= 0xf0;
		tmp |= vaw & 0x0f;
		w83795_wwite(cwient, W83795_WEG_HT(index), tmp);
		bweak;
	}
	data->pwm_temp[index][nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t
show_sf4_pwm(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;

	wetuwn spwintf(buf, "%u\n", data->sf4_weg[index][SF4_PWM][nw]);
}

static ssize_t
stowe_sf4_pwm(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	w83795_wwite(cwient, W83795_WEG_SF4_PWM(index, nw), vaw);
	data->sf4_weg[index][SF4_PWM][nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t
show_sf4_temp(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;

	wetuwn spwintf(buf, "%u\n",
		(data->sf4_weg[index][SF4_TEMP][nw]) * 1000);
}

static ssize_t
stowe_sf4_temp(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;
	vaw /= 1000;

	mutex_wock(&data->update_wock);
	w83795_wwite(cwient, W83795_WEG_SF4_TEMP(index, nw), vaw);
	data->sf4_weg[index][SF4_TEMP][nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}


static ssize_t
show_temp(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83795_data *data = w83795_update_device(dev);
	wong temp = temp_fwom_weg(data->temp[index][nw]);

	if (nw == TEMP_WEAD)
		temp += (data->temp_wead_vwwsb[index] >> 6) * 250;
	wetuwn spwintf(buf, "%wd\n", temp);
}

static ssize_t
stowe_temp(stwuct device *dev, stwuct device_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	wong tmp;

	if (kstwtow(buf, 10, &tmp) < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->temp[index][nw] = temp_to_weg(tmp, -128, 127);
	w83795_wwite(cwient, W83795_WEG_TEMP[index][nw], data->temp[index][nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}


static ssize_t
show_dts_mode(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = dev_get_dwvdata(dev);
	int tmp;

	if (data->enabwe_dts & 2)
		tmp = 5;
	ewse
		tmp = 6;

	wetuwn spwintf(buf, "%d\n", tmp);
}

static ssize_t
show_dts(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	stwuct w83795_data *data = w83795_update_device(dev);
	wong temp = temp_fwom_weg(data->dts[index]);

	temp += (data->dts_wead_vwwsb[index] >> 6) * 250;
	wetuwn spwintf(buf, "%wd\n", temp);
}

static ssize_t
show_dts_ext(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	stwuct w83795_data *data = dev_get_dwvdata(dev);
	wong temp = temp_fwom_weg(data->dts_ext[nw]);

	wetuwn spwintf(buf, "%wd\n", temp);
}

static ssize_t
stowe_dts_ext(stwuct device *dev, stwuct device_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	wong tmp;

	if (kstwtow(buf, 10, &tmp) < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->dts_ext[nw] = temp_to_weg(tmp, -128, 127);
	w83795_wwite(cwient, W83795_WEG_DTS_EXT(nw), data->dts_ext[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}


static ssize_t
show_temp_mode(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83795_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	int tmp;

	if (data->temp_mode & (1 << index))
		tmp = 3;	/* Thewmaw diode */
	ewse
		tmp = 4;	/* Thewmistow */

	wetuwn spwintf(buf, "%d\n", tmp);
}

/* Onwy fow temp1-4 (temp5-6 can onwy be thewmistow) */
static ssize_t
stowe_temp_mode(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	int weg_shift;
	unsigned wong vaw;
	u8 tmp;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;
	if ((vaw != 4) && (vaw != 3))
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	if (vaw == 3) {
		/* Thewmaw diode */
		vaw = 0x01;
		data->temp_mode |= 1 << index;
	} ewse if (vaw == 4) {
		/* Thewmistow */
		vaw = 0x03;
		data->temp_mode &= ~(1 << index);
	}

	weg_shift = 2 * index;
	tmp = w83795_wead(cwient, W83795_WEG_TEMP_CTWW2);
	tmp &= ~(0x03 << weg_shift);
	tmp |= vaw << weg_shift;
	w83795_wwite(cwient, W83795_WEG_TEMP_CTWW2, tmp);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}


/* show/stowe VIN */
static ssize_t
show_in(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83795_data *data = w83795_update_device(dev);
	u16 vaw = data->in[index][nw];
	u8 wsb_idx;

	switch (nw) {
	case IN_WEAD:
		/* cawcuwate this vawue again by sensows as sensows3.conf */
		if ((index >= 17) &&
		    !((data->has_gain >> (index - 17)) & 1))
			vaw *= 8;
		bweak;
	case IN_MAX:
	case IN_WOW:
		wsb_idx = IN_WSB_SHIFT_IDX[index][IN_WSB_IDX];
		vaw <<= 2;
		vaw |= (data->in_wsb[wsb_idx][nw] >>
			IN_WSB_SHIFT_IDX[index][IN_WSB_SHIFT]) & 0x03;
		if ((index >= 17) &&
		    !((data->has_gain >> (index - 17)) & 1))
			vaw *= 8;
		bweak;
	}
	vaw = in_fwom_weg(index, vaw);

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t
stowe_in(stwuct device *dev, stwuct device_attwibute *attw,
	 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	u8 tmp;
	u8 wsb_idx;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;
	vaw = in_to_weg(index, vaw);

	if ((index >= 17) &&
	    !((data->has_gain >> (index - 17)) & 1))
		vaw /= 8;
	vaw = cwamp_vaw(vaw, 0, 0x3FF);
	mutex_wock(&data->update_wock);

	wsb_idx = IN_WSB_SHIFT_IDX[index][IN_WSB_IDX];
	tmp = w83795_wead(cwient, IN_WSB_WEG(wsb_idx, nw));
	tmp &= ~(0x03 << IN_WSB_SHIFT_IDX[index][IN_WSB_SHIFT]);
	tmp |= (vaw & 0x03) << IN_WSB_SHIFT_IDX[index][IN_WSB_SHIFT];
	w83795_wwite(cwient, IN_WSB_WEG(wsb_idx, nw), tmp);
	data->in_wsb[wsb_idx][nw] = tmp;

	tmp = (vaw >> 2) & 0xff;
	w83795_wwite(cwient, W83795_WEG_IN[index][nw], tmp);
	data->in[index][nw] = tmp;

	mutex_unwock(&data->update_wock);
	wetuwn count;
}


#ifdef CONFIG_SENSOWS_W83795_FANCTWW
static ssize_t
show_sf_setup(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	stwuct w83795_data *data = w83795_update_pwm_config(dev);
	u16 vaw = data->setup_pwm[nw];

	switch (nw) {
	case SETUP_PWM_UPTIME:
	case SETUP_PWM_DOWNTIME:
		vaw = time_fwom_weg(vaw);
		bweak;
	}

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t
stowe_sf_setup(stwuct device *dev, stwuct device_attwibute *attw,
	 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	switch (nw) {
	case SETUP_PWM_DEFAUWT:
		vaw = cwamp_vaw(vaw, 0, 0xff);
		bweak;
	case SETUP_PWM_UPTIME:
	case SETUP_PWM_DOWNTIME:
		vaw = time_to_weg(vaw);
		if (vaw == 0)
			wetuwn -EINVAW;
		bweak;
	}

	mutex_wock(&data->update_wock);
	data->setup_pwm[nw] = vaw;
	w83795_wwite(cwient, W83795_WEG_SETUP_PWM(nw), vaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}
#endif


#define NOT_USED			-1

/*
 * Don't change the attwibute owdew, _max, _min and _beep awe accessed by index
 * somewhewe ewse in the code
 */
#define SENSOW_ATTW_IN(index) {						\
	SENSOW_ATTW_2(in##index##_input, S_IWUGO, show_in, NUWW,	\
		IN_WEAD, index), \
	SENSOW_ATTW_2(in##index##_max, S_IWUGO | S_IWUSW, show_in,	\
		stowe_in, IN_MAX, index),				\
	SENSOW_ATTW_2(in##index##_min, S_IWUGO | S_IWUSW, show_in,	\
		stowe_in, IN_WOW, index),				\
	SENSOW_ATTW_2(in##index##_awawm, S_IWUGO, show_awawm_beep,	\
		NUWW, AWAWM_STATUS, index + ((index > 14) ? 1 : 0)), \
	SENSOW_ATTW_2(in##index##_beep, S_IWUSW | S_IWUGO,		\
		show_awawm_beep, stowe_beep, BEEP_ENABWE,		\
		index + ((index > 14) ? 1 : 0)) }

/*
 * Don't change the attwibute owdew, _beep is accessed by index
 * somewhewe ewse in the code
 */
#define SENSOW_ATTW_FAN(index) {					\
	SENSOW_ATTW_2(fan##index##_input, S_IWUGO, show_fan,		\
		NUWW, FAN_INPUT, index - 1), \
	SENSOW_ATTW_2(fan##index##_min, S_IWUSW | S_IWUGO,		\
		show_fan, stowe_fan_min, FAN_MIN, index - 1),	\
	SENSOW_ATTW_2(fan##index##_awawm, S_IWUGO, show_awawm_beep,	\
		NUWW, AWAWM_STATUS, index + 31),			\
	SENSOW_ATTW_2(fan##index##_beep, S_IWUSW | S_IWUGO,		\
		show_awawm_beep, stowe_beep, BEEP_ENABWE, index + 31) }

#define SENSOW_ATTW_PWM(index) {					\
	SENSOW_ATTW_2(pwm##index, S_IWUSW | S_IWUGO, show_pwm,		\
		stowe_pwm, PWM_OUTPUT, index - 1),			\
	SENSOW_ATTW_2(pwm##index##_enabwe, S_IWUSW | S_IWUGO,		\
		show_pwm_enabwe, stowe_pwm_enabwe, NOT_USED, index - 1), \
	SENSOW_ATTW_2(pwm##index##_mode, S_IWUGO,			\
		show_pwm_mode, NUWW, NOT_USED, index - 1),		\
	SENSOW_ATTW_2(pwm##index##_fweq, S_IWUSW | S_IWUGO,		\
		show_pwm, stowe_pwm, PWM_FWEQ, index - 1),		\
	SENSOW_ATTW_2(pwm##index##_nonstop, S_IWUSW | S_IWUGO,		\
		show_pwm, stowe_pwm, PWM_NONSTOP, index - 1),		\
	SENSOW_ATTW_2(pwm##index##_stawt, S_IWUSW | S_IWUGO,		\
		show_pwm, stowe_pwm, PWM_STAWT, index - 1),		\
	SENSOW_ATTW_2(pwm##index##_stop_time, S_IWUSW | S_IWUGO,	\
		show_pwm, stowe_pwm, PWM_STOP_TIME, index - 1),	 \
	SENSOW_ATTW_2(fan##index##_tawget, S_IWUSW | S_IWUGO, \
		show_fanin, stowe_fanin, FANIN_TAWGET, index - 1) }

/*
 * Don't change the attwibute owdew, _beep is accessed by index
 * somewhewe ewse in the code
 */
#define SENSOW_ATTW_DTS(index) {					\
	SENSOW_ATTW_2(temp##index##_type, S_IWUGO ,		\
		show_dts_mode, NUWW, NOT_USED, index - 7),	\
	SENSOW_ATTW_2(temp##index##_input, S_IWUGO, show_dts,		\
		NUWW, NOT_USED, index - 7),				\
	SENSOW_ATTW_2(temp##index##_cwit, S_IWUGO | S_IWUSW, show_dts_ext, \
		stowe_dts_ext, DTS_CWIT, NOT_USED),			\
	SENSOW_ATTW_2(temp##index##_cwit_hyst, S_IWUGO | S_IWUSW,	\
		show_dts_ext, stowe_dts_ext, DTS_CWIT_HYST, NOT_USED),	\
	SENSOW_ATTW_2(temp##index##_max, S_IWUGO | S_IWUSW, show_dts_ext, \
		stowe_dts_ext, DTS_WAWN, NOT_USED),			\
	SENSOW_ATTW_2(temp##index##_max_hyst, S_IWUGO | S_IWUSW,	\
		show_dts_ext, stowe_dts_ext, DTS_WAWN_HYST, NOT_USED),	\
	SENSOW_ATTW_2(temp##index##_awawm, S_IWUGO,			\
		show_awawm_beep, NUWW, AWAWM_STATUS, index + 17),	\
	SENSOW_ATTW_2(temp##index##_beep, S_IWUSW | S_IWUGO,		\
		show_awawm_beep, stowe_beep, BEEP_ENABWE, index + 17) }

/*
 * Don't change the attwibute owdew, _beep is accessed by index
 * somewhewe ewse in the code
 */
#define SENSOW_ATTW_TEMP(index) {					\
	SENSOW_ATTW_2(temp##index##_type, S_IWUGO | (index < 5 ? S_IWUSW : 0), \
		show_temp_mode, stowe_temp_mode, NOT_USED, index - 1),	\
	SENSOW_ATTW_2(temp##index##_input, S_IWUGO, show_temp,		\
		NUWW, TEMP_WEAD, index - 1),				\
	SENSOW_ATTW_2(temp##index##_cwit, S_IWUGO | S_IWUSW, show_temp,	\
		stowe_temp, TEMP_CWIT, index - 1),			\
	SENSOW_ATTW_2(temp##index##_cwit_hyst, S_IWUGO | S_IWUSW,	\
		show_temp, stowe_temp, TEMP_CWIT_HYST, index - 1),	\
	SENSOW_ATTW_2(temp##index##_max, S_IWUGO | S_IWUSW, show_temp,	\
		stowe_temp, TEMP_WAWN, index - 1),			\
	SENSOW_ATTW_2(temp##index##_max_hyst, S_IWUGO | S_IWUSW,	\
		show_temp, stowe_temp, TEMP_WAWN_HYST, index - 1),	\
	SENSOW_ATTW_2(temp##index##_awawm, S_IWUGO,			\
		show_awawm_beep, NUWW, AWAWM_STATUS,			\
		index + (index > 4 ? 11 : 17)),				\
	SENSOW_ATTW_2(temp##index##_beep, S_IWUSW | S_IWUGO,		\
		show_awawm_beep, stowe_beep, BEEP_ENABWE,		\
		index + (index > 4 ? 11 : 17)),				\
	SENSOW_ATTW_2(temp##index##_pwm_enabwe, S_IWUSW | S_IWUGO,	\
		show_temp_pwm_enabwe, stowe_temp_pwm_enabwe,		\
		TEMP_PWM_ENABWE, index - 1),				\
	SENSOW_ATTW_2(temp##index##_auto_channews_pwm, S_IWUSW | S_IWUGO, \
		show_temp_pwm_enabwe, stowe_temp_pwm_enabwe,		\
		TEMP_PWM_FAN_MAP, index - 1),				\
	SENSOW_ATTW_2(thewmaw_cwuise##index, S_IWUSW | S_IWUGO,		\
		show_temp_pwm, stowe_temp_pwm, TEMP_PWM_TTTI, index - 1), \
	SENSOW_ATTW_2(temp##index##_wawn, S_IWUSW | S_IWUGO,		\
		show_temp_pwm, stowe_temp_pwm, TEMP_PWM_CTFS, index - 1), \
	SENSOW_ATTW_2(temp##index##_wawn_hyst, S_IWUSW | S_IWUGO,	\
		show_temp_pwm, stowe_temp_pwm, TEMP_PWM_HCT, index - 1), \
	SENSOW_ATTW_2(temp##index##_opewation_hyst, S_IWUSW | S_IWUGO,	\
		show_temp_pwm, stowe_temp_pwm, TEMP_PWM_HOT, index - 1), \
	SENSOW_ATTW_2(temp##index##_auto_point1_pwm, S_IWUGO | S_IWUSW, \
		show_sf4_pwm, stowe_sf4_pwm, 0, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point2_pwm, S_IWUGO | S_IWUSW, \
		show_sf4_pwm, stowe_sf4_pwm, 1, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point3_pwm, S_IWUGO | S_IWUSW, \
		show_sf4_pwm, stowe_sf4_pwm, 2, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point4_pwm, S_IWUGO | S_IWUSW, \
		show_sf4_pwm, stowe_sf4_pwm, 3, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point5_pwm, S_IWUGO | S_IWUSW, \
		show_sf4_pwm, stowe_sf4_pwm, 4, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point6_pwm, S_IWUGO | S_IWUSW, \
		show_sf4_pwm, stowe_sf4_pwm, 5, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point7_pwm, S_IWUGO | S_IWUSW, \
		show_sf4_pwm, stowe_sf4_pwm, 6, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point1_temp, S_IWUGO | S_IWUSW,\
		show_sf4_temp, stowe_sf4_temp, 0, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point2_temp, S_IWUGO | S_IWUSW,\
		show_sf4_temp, stowe_sf4_temp, 1, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point3_temp, S_IWUGO | S_IWUSW,\
		show_sf4_temp, stowe_sf4_temp, 2, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point4_temp, S_IWUGO | S_IWUSW,\
		show_sf4_temp, stowe_sf4_temp, 3, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point5_temp, S_IWUGO | S_IWUSW,\
		show_sf4_temp, stowe_sf4_temp, 4, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point6_temp, S_IWUGO | S_IWUSW,\
		show_sf4_temp, stowe_sf4_temp, 5, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point7_temp, S_IWUGO | S_IWUSW,\
		show_sf4_temp, stowe_sf4_temp, 6, index - 1) }


static stwuct sensow_device_attwibute_2 w83795_in[][5] = {
	SENSOW_ATTW_IN(0),
	SENSOW_ATTW_IN(1),
	SENSOW_ATTW_IN(2),
	SENSOW_ATTW_IN(3),
	SENSOW_ATTW_IN(4),
	SENSOW_ATTW_IN(5),
	SENSOW_ATTW_IN(6),
	SENSOW_ATTW_IN(7),
	SENSOW_ATTW_IN(8),
	SENSOW_ATTW_IN(9),
	SENSOW_ATTW_IN(10),
	SENSOW_ATTW_IN(11),
	SENSOW_ATTW_IN(12),
	SENSOW_ATTW_IN(13),
	SENSOW_ATTW_IN(14),
	SENSOW_ATTW_IN(15),
	SENSOW_ATTW_IN(16),
	SENSOW_ATTW_IN(17),
	SENSOW_ATTW_IN(18),
	SENSOW_ATTW_IN(19),
	SENSOW_ATTW_IN(20),
};

static const stwuct sensow_device_attwibute_2 w83795_fan[][4] = {
	SENSOW_ATTW_FAN(1),
	SENSOW_ATTW_FAN(2),
	SENSOW_ATTW_FAN(3),
	SENSOW_ATTW_FAN(4),
	SENSOW_ATTW_FAN(5),
	SENSOW_ATTW_FAN(6),
	SENSOW_ATTW_FAN(7),
	SENSOW_ATTW_FAN(8),
	SENSOW_ATTW_FAN(9),
	SENSOW_ATTW_FAN(10),
	SENSOW_ATTW_FAN(11),
	SENSOW_ATTW_FAN(12),
	SENSOW_ATTW_FAN(13),
	SENSOW_ATTW_FAN(14),
};

static const stwuct sensow_device_attwibute_2 w83795_temp[][28] = {
	SENSOW_ATTW_TEMP(1),
	SENSOW_ATTW_TEMP(2),
	SENSOW_ATTW_TEMP(3),
	SENSOW_ATTW_TEMP(4),
	SENSOW_ATTW_TEMP(5),
	SENSOW_ATTW_TEMP(6),
};

static const stwuct sensow_device_attwibute_2 w83795_dts[][8] = {
	SENSOW_ATTW_DTS(7),
	SENSOW_ATTW_DTS(8),
	SENSOW_ATTW_DTS(9),
	SENSOW_ATTW_DTS(10),
	SENSOW_ATTW_DTS(11),
	SENSOW_ATTW_DTS(12),
	SENSOW_ATTW_DTS(13),
	SENSOW_ATTW_DTS(14),
};

static const stwuct sensow_device_attwibute_2 w83795_pwm[][8] = {
	SENSOW_ATTW_PWM(1),
	SENSOW_ATTW_PWM(2),
	SENSOW_ATTW_PWM(3),
	SENSOW_ATTW_PWM(4),
	SENSOW_ATTW_PWM(5),
	SENSOW_ATTW_PWM(6),
	SENSOW_ATTW_PWM(7),
	SENSOW_ATTW_PWM(8),
};

static const stwuct sensow_device_attwibute_2 w83795_tss[6] = {
	SENSOW_ATTW_2(temp1_souwce_sew, S_IWUSW | S_IWUGO,
		      show_temp_swc, stowe_temp_swc, NOT_USED, 0),
	SENSOW_ATTW_2(temp2_souwce_sew, S_IWUSW | S_IWUGO,
		      show_temp_swc, stowe_temp_swc, NOT_USED, 1),
	SENSOW_ATTW_2(temp3_souwce_sew, S_IWUSW | S_IWUGO,
		      show_temp_swc, stowe_temp_swc, NOT_USED, 2),
	SENSOW_ATTW_2(temp4_souwce_sew, S_IWUSW | S_IWUGO,
		      show_temp_swc, stowe_temp_swc, NOT_USED, 3),
	SENSOW_ATTW_2(temp5_souwce_sew, S_IWUSW | S_IWUGO,
		      show_temp_swc, stowe_temp_swc, NOT_USED, 4),
	SENSOW_ATTW_2(temp6_souwce_sew, S_IWUSW | S_IWUGO,
		      show_temp_swc, stowe_temp_swc, NOT_USED, 5),
};

static const stwuct sensow_device_attwibute_2 sda_singwe_fiwes[] = {
	SENSOW_ATTW_2(intwusion0_awawm, S_IWUSW | S_IWUGO, show_awawm_beep,
		      stowe_chassis_cweaw, AWAWM_STATUS, 46),
#ifdef CONFIG_SENSOWS_W83795_FANCTWW
	SENSOW_ATTW_2(speed_cwuise_towewance, S_IWUSW | S_IWUGO, show_fanin,
		stowe_fanin, FANIN_TOW, NOT_USED),
	SENSOW_ATTW_2(pwm_defauwt, S_IWUSW | S_IWUGO, show_sf_setup,
		      stowe_sf_setup, SETUP_PWM_DEFAUWT, NOT_USED),
	SENSOW_ATTW_2(pwm_uptime, S_IWUSW | S_IWUGO, show_sf_setup,
		      stowe_sf_setup, SETUP_PWM_UPTIME, NOT_USED),
	SENSOW_ATTW_2(pwm_downtime, S_IWUSW | S_IWUGO, show_sf_setup,
		      stowe_sf_setup, SETUP_PWM_DOWNTIME, NOT_USED),
#endif
};

static const stwuct sensow_device_attwibute_2 sda_beep_fiwes[] = {
	SENSOW_ATTW_2(intwusion0_beep, S_IWUSW | S_IWUGO, show_awawm_beep,
		      stowe_beep, BEEP_ENABWE, 46),
	SENSOW_ATTW_2(beep_enabwe, S_IWUSW | S_IWUGO, show_awawm_beep,
		      stowe_beep, BEEP_ENABWE, 47),
};

/*
 * Dwivew intewface
 */

static void w83795_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	static const u16 cwkin[4] = {	/* in kHz */
		14318, 24000, 33333, 48000
	};
	u8 config;

	if (weset)
		w83795_wwite(cwient, W83795_WEG_CONFIG, 0x80);

	/* Stawt monitowing if needed */
	config = w83795_wead(cwient, W83795_WEG_CONFIG);
	if (!(config & W83795_WEG_CONFIG_STAWT)) {
		dev_info(&cwient->dev, "Enabwing monitowing opewations\n");
		w83795_wwite(cwient, W83795_WEG_CONFIG,
			     config | W83795_WEG_CONFIG_STAWT);
	}

	data->cwkin = cwkin[(config >> 3) & 0x3];
	dev_dbg(&cwient->dev, "cwkin = %u kHz\n", data->cwkin);
}

static int w83795_get_device_id(stwuct i2c_cwient *cwient)
{
	int device_id;

	device_id = i2c_smbus_wead_byte_data(cwient, W83795_WEG_DEVICEID);

	/*
	 * Speciaw case fow wev. A chips; can't be checked fiwst because watew
	 * wevisions emuwate this fow compatibiwity
	 */
	if (device_id < 0 || (device_id & 0xf0) != 0x50) {
		int awt_id;

		awt_id = i2c_smbus_wead_byte_data(cwient,
						  W83795_WEG_DEVICEID_A);
		if (awt_id == 0x50)
			device_id = awt_id;
	}

	wetuwn device_id;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int w83795_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info)
{
	int bank, vendow_id, device_id, expected, i2c_addw, config;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	unsigned showt addwess = cwient->addw;
	const chaw *chip_name;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;
	bank = i2c_smbus_wead_byte_data(cwient, W83795_WEG_BANKSEW);
	if (bank < 0 || (bank & 0x7c)) {
		dev_dbg(&adaptew->dev,
			"w83795: Detection faiwed at addw 0x%02hx, check %s\n",
			addwess, "bank");
		wetuwn -ENODEV;
	}

	/* Check Nuvoton vendow ID */
	vendow_id = i2c_smbus_wead_byte_data(cwient, W83795_WEG_VENDOWID);
	expected = bank & 0x80 ? 0x5c : 0xa3;
	if (vendow_id != expected) {
		dev_dbg(&adaptew->dev,
			"w83795: Detection faiwed at addw 0x%02hx, check %s\n",
			addwess, "vendow id");
		wetuwn -ENODEV;
	}

	/* Check device ID */
	device_id = w83795_get_device_id(cwient) |
		    (i2c_smbus_wead_byte_data(cwient, W83795_WEG_CHIPID) << 8);
	if ((device_id >> 4) != 0x795) {
		dev_dbg(&adaptew->dev,
			"w83795: Detection faiwed at addw 0x%02hx, check %s\n",
			addwess, "device id\n");
		wetuwn -ENODEV;
	}

	/*
	 * If Nuvoton chip, addwess of chip and W83795_WEG_I2C_ADDW
	 * shouwd match
	 */
	if ((bank & 0x07) == 0) {
		i2c_addw = i2c_smbus_wead_byte_data(cwient,
						    W83795_WEG_I2C_ADDW);
		if ((i2c_addw & 0x7f) != addwess) {
			dev_dbg(&adaptew->dev,
				"w83795: Detection faiwed at addw 0x%02hx, "
				"check %s\n", addwess, "i2c addw");
			wetuwn -ENODEV;
		}
	}

	/*
	 * Check 795 chip type: 795G ow 795ADG
	 * Usuawwy we don't wwite to chips duwing detection, but hewe we don't
	 * quite have the choice; hopefuwwy it's OK, we awe about to wetuwn
	 * success anyway
	 */
	if ((bank & 0x07) != 0)
		i2c_smbus_wwite_byte_data(cwient, W83795_WEG_BANKSEW,
					  bank & ~0x07);
	config = i2c_smbus_wead_byte_data(cwient, W83795_WEG_CONFIG);
	if (config & W83795_WEG_CONFIG_CONFIG48)
		chip_name = "w83795adg";
	ewse
		chip_name = "w83795g";

	stwscpy(info->type, chip_name, I2C_NAME_SIZE);
	dev_info(&adaptew->dev, "Found %s wev. %c at 0x%02hx\n", chip_name,
		 'A' + (device_id & 0xf), addwess);

	wetuwn 0;
}

#ifdef CONFIG_SENSOWS_W83795_FANCTWW
#define NUM_PWM_ATTWIBUTES	AWWAY_SIZE(w83795_pwm[0])
#define NUM_TEMP_ATTWIBUTES	AWWAY_SIZE(w83795_temp[0])
#ewse
#define NUM_PWM_ATTWIBUTES	4
#define NUM_TEMP_ATTWIBUTES	8
#endif

static int w83795_handwe_fiwes(stwuct device *dev, int (*fn)(stwuct device *,
			       const stwuct device_attwibute *))
{
	stwuct w83795_data *data = dev_get_dwvdata(dev);
	int eww, i, j;

	fow (i = 0; i < AWWAY_SIZE(w83795_in); i++) {
		if (!(data->has_in & (1 << i)))
			continue;
		fow (j = 0; j < AWWAY_SIZE(w83795_in[0]); j++) {
			if (j == 4 && !data->enabwe_beep)
				continue;
			eww = fn(dev, &w83795_in[i][j].dev_attw);
			if (eww)
				wetuwn eww;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(w83795_fan); i++) {
		if (!(data->has_fan & (1 << i)))
			continue;
		fow (j = 0; j < AWWAY_SIZE(w83795_fan[0]); j++) {
			if (j == 3 && !data->enabwe_beep)
				continue;
			eww = fn(dev, &w83795_fan[i][j].dev_attw);
			if (eww)
				wetuwn eww;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(w83795_tss); i++) {
		j = w83795_tss_usefuw(data, i);
		if (!j)
			continue;
		eww = fn(dev, &w83795_tss[i].dev_attw);
		if (eww)
			wetuwn eww;
	}

	fow (i = 0; i < AWWAY_SIZE(sda_singwe_fiwes); i++) {
		eww = fn(dev, &sda_singwe_fiwes[i].dev_attw);
		if (eww)
			wetuwn eww;
	}

	if (data->enabwe_beep) {
		fow (i = 0; i < AWWAY_SIZE(sda_beep_fiwes); i++) {
			eww = fn(dev, &sda_beep_fiwes[i].dev_attw);
			if (eww)
				wetuwn eww;
		}
	}

	fow (i = 0; i < data->has_pwm; i++) {
		fow (j = 0; j < NUM_PWM_ATTWIBUTES; j++) {
			eww = fn(dev, &w83795_pwm[i][j].dev_attw);
			if (eww)
				wetuwn eww;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(w83795_temp); i++) {
		if (!(data->has_temp & (1 << i)))
			continue;
		fow (j = 0; j < NUM_TEMP_ATTWIBUTES; j++) {
			if (j == 7 && !data->enabwe_beep)
				continue;
			eww = fn(dev, &w83795_temp[i][j].dev_attw);
			if (eww)
				wetuwn eww;
		}
	}

	if (data->enabwe_dts) {
		fow (i = 0; i < AWWAY_SIZE(w83795_dts); i++) {
			if (!(data->has_dts & (1 << i)))
				continue;
			fow (j = 0; j < AWWAY_SIZE(w83795_dts[0]); j++) {
				if (j == 7 && !data->enabwe_beep)
					continue;
				eww = fn(dev, &w83795_dts[i][j].dev_attw);
				if (eww)
					wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

/* We need a wwappew that fits in w83795_handwe_fiwes */
static int device_wemove_fiwe_wwappew(stwuct device *dev,
				      const stwuct device_attwibute *attw)
{
	device_wemove_fiwe(dev, attw);
	wetuwn 0;
}

static void w83795_check_dynamic_in_wimits(stwuct i2c_cwient *cwient)
{
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);
	u8 vid_ctw;
	int i, eww_max, eww_min;

	vid_ctw = w83795_wead(cwient, W83795_WEG_VID_CTWW);

	/* Wetuwn immediatewy if VWM isn't configuwed */
	if ((vid_ctw & 0x07) == 0x00 || (vid_ctw & 0x07) == 0x07)
		wetuwn;

	data->has_dyn_in = (vid_ctw >> 3) & 0x07;
	fow (i = 0; i < 2; i++) {
		if (!(data->has_dyn_in & (1 << i)))
			continue;

		/* Vowtage wimits in dynamic mode, switch to wead-onwy */
		eww_max = sysfs_chmod_fiwe(&cwient->dev.kobj,
					   &w83795_in[i][2].dev_attw.attw,
					   S_IWUGO);
		eww_min = sysfs_chmod_fiwe(&cwient->dev.kobj,
					   &w83795_in[i][3].dev_attw.attw,
					   S_IWUGO);
		if (eww_max || eww_min)
			dev_wawn(&cwient->dev,
				 "Faiwed to set in%d wimits wead-onwy (%d, %d)\n",
				 i, eww_max, eww_min);
		ewse
			dev_info(&cwient->dev,
				 "in%d wimits set dynamicawwy fwom VID\n", i);
	}
}

/* Check pins that can be used fow eithew tempewatuwe ow vowtage monitowing */
static void w83795_appwy_temp_config(stwuct w83795_data *data, u8 config,
				     int temp_chan, int in_chan)
{
	/* config is a 2-bit vawue */
	switch (config) {
	case 0x2: /* Vowtage monitowing */
		data->has_in |= 1 << in_chan;
		bweak;
	case 0x1: /* Thewmaw diode */
		if (temp_chan >= 4)
			bweak;
		data->temp_mode |= 1 << temp_chan;
		fawwthwough;
	case 0x3: /* Thewmistow */
		data->has_temp |= 1 << temp_chan;
		bweak;
	}
}

static const stwuct i2c_device_id w83795_id[];

static int w83795_pwobe(stwuct i2c_cwient *cwient)
{
	int i;
	u8 tmp;
	stwuct device *dev = &cwient->dev;
	stwuct w83795_data *data;
	int eww;

	data = devm_kzawwoc(dev, sizeof(stwuct w83795_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->chip_type = i2c_match_id(w83795_id, cwient)->dwivew_data;
	data->bank = i2c_smbus_wead_byte_data(cwient, W83795_WEG_BANKSEW);
	mutex_init(&data->update_wock);

	/* Initiawize the chip */
	w83795_init_cwient(cwient);

	/* Check which vowtages and fans awe pwesent */
	data->has_in = w83795_wead(cwient, W83795_WEG_VOWT_CTWW1)
		     | (w83795_wead(cwient, W83795_WEG_VOWT_CTWW2) << 8);
	data->has_fan = w83795_wead(cwient, W83795_WEG_FANIN_CTWW1)
		      | (w83795_wead(cwient, W83795_WEG_FANIN_CTWW2) << 8);

	/* Check which anawog tempewatuwes and extwa vowtages awe pwesent */
	tmp = w83795_wead(cwient, W83795_WEG_TEMP_CTWW1);
	if (tmp & 0x20)
		data->enabwe_dts = 1;
	w83795_appwy_temp_config(data, (tmp >> 2) & 0x3, 5, 16);
	w83795_appwy_temp_config(data, tmp & 0x3, 4, 15);
	tmp = w83795_wead(cwient, W83795_WEG_TEMP_CTWW2);
	w83795_appwy_temp_config(data, tmp >> 6, 3, 20);
	w83795_appwy_temp_config(data, (tmp >> 4) & 0x3, 2, 19);
	w83795_appwy_temp_config(data, (tmp >> 2) & 0x3, 1, 18);
	w83795_appwy_temp_config(data, tmp & 0x3, 0, 17);

	/* Check DTS enabwe status */
	if (data->enabwe_dts) {
		if (1 & w83795_wead(cwient, W83795_WEG_DTSC))
			data->enabwe_dts |= 2;
		data->has_dts = w83795_wead(cwient, W83795_WEG_DTSE);
	}

	/* Wepowt PECI Tbase vawues */
	if (data->enabwe_dts == 1) {
		fow (i = 0; i < 8; i++) {
			if (!(data->has_dts & (1 << i)))
				continue;
			tmp = w83795_wead(cwient, W83795_WEG_PECI_TBASE(i));
			dev_info(&cwient->dev,
				 "PECI agent %d Tbase tempewatuwe: %u\n",
				 i + 1, (unsigned int)tmp & 0x7f);
		}
	}

	data->has_gain = w83795_wead(cwient, W83795_WEG_VMIGB_CTWW) & 0x0f;

	/* pwm and smawt fan */
	if (data->chip_type == w83795g)
		data->has_pwm = 8;
	ewse
		data->has_pwm = 2;

	/* Check if BEEP pin is avaiwabwe */
	if (data->chip_type == w83795g) {
		/* The W83795G has a dedicated BEEP pin */
		data->enabwe_beep = 1;
	} ewse {
		/*
		 * The W83795ADG has a shawed pin fow OVT# and BEEP, so you
		 * can't have both
		 */
		tmp = w83795_wead(cwient, W83795_WEG_OVT_CFG);
		if ((tmp & OVT_CFG_SEW) == 0)
			data->enabwe_beep = 1;
	}

	eww = w83795_handwe_fiwes(dev, device_cweate_fiwe);
	if (eww)
		goto exit_wemove;

	if (data->chip_type == w83795g)
		w83795_check_dynamic_in_wimits(cwient);

	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_wemove;
	}

	wetuwn 0;

exit_wemove:
	w83795_handwe_fiwes(dev, device_wemove_fiwe_wwappew);
	wetuwn eww;
}

static void w83795_wemove(stwuct i2c_cwient *cwient)
{
	stwuct w83795_data *data = i2c_get_cwientdata(cwient);

	hwmon_device_unwegistew(data->hwmon_dev);
	w83795_handwe_fiwes(&cwient->dev, device_wemove_fiwe_wwappew);
}


static const stwuct i2c_device_id w83795_id[] = {
	{ "w83795g", w83795g },
	{ "w83795adg", w83795adg },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, w83795_id);

static stwuct i2c_dwivew w83795_dwivew = {
	.dwivew = {
		   .name = "w83795",
	},
	.pwobe		= w83795_pwobe,
	.wemove		= w83795_wemove,
	.id_tabwe	= w83795_id,

	.cwass		= I2C_CWASS_HWMON,
	.detect		= w83795_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(w83795_dwivew);

MODUWE_AUTHOW("Wei Song, Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("W83795G/ADG hawdwawe monitowing dwivew");
MODUWE_WICENSE("GPW");
