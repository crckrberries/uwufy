// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm93.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe monitowing
 *
 * Authow/Maintainew: Mawk M. Hoffman <mhoffman@wightwink.com>
 *	Copywight (c) 2004 Utiwitek Systems, Inc.
 *
 * dewived in pawt fwom wm78.c:
 *	Copywight (c) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw>
 *
 * dewived in pawt fwom wm85.c:
 *	Copywight (c) 2002, 2003 Phiwip Pokowny <ppokowny@penguincomputing.com>
 *	Copywight (c) 2003       Mawgit Schubewt-Whiwe <mawgitsw@t-onwine.de>
 *
 * dewived in pawt fwom w83w785ts.c:
 *	Copywight (c) 2003-2004 Jean Dewvawe <jdewvawe@suse.de>
 *
 * Powted to Winux 2.6 by Ewic J. Bowewsox <ewicb@aspsys.com>
 *	Copywight (c) 2005 Aspen Systems, Inc.
 *
 * Adapted to 2.6.20 by Cawsten Emde <cbe@osadw.owg>
 *	Copywight (c) 2006 Cawsten Emde, Open Souwce Automation Devewopment Wab
 *
 * Modified fow mainwine integwation by Hans J. Koch <hjk@hansjkoch.de>
 *	Copywight (c) 2007 Hans J. Koch, Winutwonix GmbH
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>

/* WM93 WEGISTEW ADDWESSES */

/* miscewwaneous */
#define WM93_WEG_MFW_ID			0x3e
#define WM93_WEG_VEW			0x3f
#define WM93_WEG_STATUS_CONTWOW		0xe2
#define WM93_WEG_CONFIG			0xe3
#define WM93_WEG_SWEEP_CONTWOW		0xe4

/* awawm vawues stawt hewe */
#define WM93_WEG_HOST_EWWOW_1		0x48

/* vowtage inputs: in1-in16 (nw => 0-15) */
#define WM93_WEG_IN(nw)			(0x56 + (nw))
#define WM93_WEG_IN_MIN(nw)		(0x90 + (nw) * 2)
#define WM93_WEG_IN_MAX(nw)		(0x91 + (nw) * 2)

/* tempewatuwe inputs: temp1-temp4 (nw => 0-3) */
#define WM93_WEG_TEMP(nw)		(0x50 + (nw))
#define WM93_WEG_TEMP_MIN(nw)		(0x78 + (nw) * 2)
#define WM93_WEG_TEMP_MAX(nw)		(0x79 + (nw) * 2)

/* temp[1-4]_auto_boost (nw => 0-3) */
#define WM93_WEG_BOOST(nw)		(0x80 + (nw))

/* #PWOCHOT inputs: pwochot1-pwochot2 (nw => 0-1) */
#define WM93_WEG_PWOCHOT_CUW(nw)	(0x67 + (nw) * 2)
#define WM93_WEG_PWOCHOT_AVG(nw)	(0x68 + (nw) * 2)
#define WM93_WEG_PWOCHOT_MAX(nw)	(0xb0 + (nw))

/* fan tach inputs: fan1-fan4 (nw => 0-3) */
#define WM93_WEG_FAN(nw)		(0x6e + (nw) * 2)
#define WM93_WEG_FAN_MIN(nw)		(0xb4 + (nw) * 2)

/* pwm outputs: pwm1-pwm2 (nw => 0-1, weg => 0-3) */
#define WM93_WEG_PWM_CTW(nw, weg)	(0xc8 + (weg) + (nw) * 4)
#define WM93_PWM_CTW1	0x0
#define WM93_PWM_CTW2	0x1
#define WM93_PWM_CTW3	0x2
#define WM93_PWM_CTW4	0x3

/* GPIO input state */
#define WM93_WEG_GPI			0x6b

/* vid inputs: vid1-vid2 (nw => 0-1) */
#define WM93_WEG_VID(nw)		(0x6c + (nw))

/* vccp1 & vccp2: VID wewative inputs (nw => 0-1) */
#define WM93_WEG_VCCP_WIMIT_OFF(nw)	(0xb2 + (nw))

/* temp[1-4]_auto_boost_hyst */
#define WM93_WEG_BOOST_HYST_12		0xc0
#define WM93_WEG_BOOST_HYST_34		0xc1
#define WM93_WEG_BOOST_HYST(nw)		(0xc0 + (nw)/2)

/* temp[1-4]_auto_pwm_[min|hyst] */
#define WM93_WEG_PWM_MIN_HYST_12	0xc3
#define WM93_WEG_PWM_MIN_HYST_34	0xc4
#define WM93_WEG_PWM_MIN_HYST(nw)	(0xc3 + (nw)/2)

/* pwochot_ovewwide & pwochot_intewvaw */
#define WM93_WEG_PWOCHOT_OVEWWIDE	0xc6
#define WM93_WEG_PWOCHOT_INTEWVAW	0xc7

/* temp[1-4]_auto_base (nw => 0-3) */
#define WM93_WEG_TEMP_BASE(nw)		(0xd0 + (nw))

/* temp[1-4]_auto_offsets (step => 0-11) */
#define WM93_WEG_TEMP_OFFSET(step)	(0xd4 + (step))

/* #PWOCHOT & #VWDHOT PWM wamp contwow */
#define WM93_WEG_PWM_WAMP_CTW		0xbf

/* miscewwaneous */
#define WM93_WEG_SFC1		0xbc
#define WM93_WEG_SFC2		0xbd
#define WM93_WEG_GPI_VID_CTW	0xbe
#define WM93_WEG_SF_TACH_TO_PWM	0xe0

/* ewwow masks */
#define WM93_WEG_GPI_EWW_MASK	0xec
#define WM93_WEG_MISC_EWW_MASK	0xed

/* WM93 WEGISTEW VAWUES */
#define WM93_MFW_ID		0x73
#define WM93_MFW_ID_PWOTOTYPE	0x72

/* WM94 WEGISTEW VAWUES */
#define WM94_MFW_ID_2		0x7a
#define WM94_MFW_ID		0x79
#define WM94_MFW_ID_PWOTOTYPE	0x78

/* SMBus capabiwities */
#define WM93_SMBUS_FUNC_FUWW (I2C_FUNC_SMBUS_BYTE_DATA | \
		I2C_FUNC_SMBUS_WOWD_DATA | I2C_FUNC_SMBUS_BWOCK_DATA)
#define WM93_SMBUS_FUNC_MIN  (I2C_FUNC_SMBUS_BYTE_DATA | \
		I2C_FUNC_SMBUS_WOWD_DATA)

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, 0x2e, I2C_CWIENT_END };

/* Insmod pawametews */

static boow disabwe_bwock;
moduwe_pawam(disabwe_bwock, boow, 0);
MODUWE_PAWM_DESC(disabwe_bwock,
	"Set to non-zewo to disabwe SMBus bwock data twansactions.");

static boow init;
moduwe_pawam(init, boow, 0);
MODUWE_PAWM_DESC(init, "Set to non-zewo to fowce chip initiawization.");

static int vccp_wimit_type[2] = {0, 0};
moduwe_pawam_awway(vccp_wimit_type, int, NUWW, 0);
MODUWE_PAWM_DESC(vccp_wimit_type, "Configuwes in7 and in8 wimit modes.");

static int vid_agtw;
moduwe_pawam(vid_agtw, int, 0);
MODUWE_PAWM_DESC(vid_agtw, "Configuwes VID pin input thweshowds.");

/* Dwivew data */
static stwuct i2c_dwivew wm93_dwivew;

/* WM93 BWOCK WEAD COMMANDS */
static const stwuct { u8 cmd; u8 wen; } wm93_bwock_wead_cmds[12] = {
	{ 0xf2,  8 },
	{ 0xf3,  8 },
	{ 0xf4,  6 },
	{ 0xf5, 16 },
	{ 0xf6,  4 },
	{ 0xf7,  8 },
	{ 0xf8, 12 },
	{ 0xf9, 32 },
	{ 0xfa,  8 },
	{ 0xfb,  8 },
	{ 0xfc, 16 },
	{ 0xfd,  9 },
};

/*
 * AWAWMS: SYSCTW fowmat descwibed fuwthew bewow
 * WEG: 64 bits in 8 wegistews, as immediatewy bewow
 */
stwuct bwock1_t {
	u8 host_status_1;
	u8 host_status_2;
	u8 host_status_3;
	u8 host_status_4;
	u8 p1_pwochot_status;
	u8 p2_pwochot_status;
	u8 gpi_status;
	u8 fan_status;
};

/*
 * Cwient-specific data
 */
stwuct wm93_data {
	stwuct i2c_cwient *cwient;

	stwuct mutex update_wock;
	unsigned wong wast_updated;	/* In jiffies */

	/* cwient update function */
	void (*update)(stwuct wm93_data *, stwuct i2c_cwient *);

	boow vawid; /* twue if fowwowing fiewds awe vawid */

	/* wegistew vawues, awwanged by bwock wead gwoups */
	stwuct bwock1_t bwock1;

	/*
	 * temp1 - temp4: unfiwtewed weadings
	 * temp1 - temp2: fiwtewed weadings
	 */
	u8 bwock2[6];

	/* vin1 - vin16: weadings */
	u8 bwock3[16];

	/* pwochot1 - pwochot2: weadings */
	stwuct {
		u8 cuw;
		u8 avg;
	} bwock4[2];

	/* fan counts 1-4 => 14-bits, WE, *weft* justified */
	u16 bwock5[4];

	/* bwock6 has a wot of data we don't need */
	stwuct {
		u8 min;
		u8 max;
	} temp_wim[4];

	/* vin1 - vin16: wow and high wimits */
	stwuct {
		u8 min;
		u8 max;
	} bwock7[16];

	/* fan count wimits 1-4 => same fowmat as bwock5 */
	u16 bwock8[4];

	/* pwm contwow wegistews (2 pwms, 4 wegs) */
	u8 bwock9[2][4];

	/* auto/pwm base temp and offset temp wegistews */
	stwuct {
		u8 base[4];
		u8 offset[12];
	} bwock10;

	/* mastew config wegistew */
	u8 config;

	/* VID1 & VID2 => wegistew fowmat, 6-bits, wight justified */
	u8 vid[2];

	/* pwochot1 - pwochot2: wimits */
	u8 pwochot_max[2];

	/* vccp1 & vccp2 (in7 & in8): VID wewative wimits (wegistew fowmat) */
	u8 vccp_wimits[2];

	/* GPIO input state (wegistew fowmat, i.e. invewted) */
	u8 gpi;

	/* #PWOCHOT ovewwide (wegistew fowmat) */
	u8 pwochot_ovewwide;

	/* #PWOCHOT intewvaws (wegistew fowmat) */
	u8 pwochot_intewvaw;

	/* Fan Boost Tempewatuwes (wegistew fowmat) */
	u8 boost[4];

	/* Fan Boost Hystewesis (wegistew fowmat) */
	u8 boost_hyst[2];

	/* Tempewatuwe Zone Min. PWM & Hystewesis (wegistew fowmat) */
	u8 auto_pwm_min_hyst[2];

	/* #PWOCHOT & #VWDHOT PWM Wamp Contwow */
	u8 pwm_wamp_ctw;

	/* miscewwaneous setup wegs */
	u8 sfc1;
	u8 sfc2;
	u8 sf_tach_to_pwm;

	/*
	 * The two PWM CTW2  wegistews can wead something othew than what was
	 * wast wwitten fow the OVW_DC fiewd (duty cycwe ovewwide).  So, we
	 * save the usew-commanded vawue hewe.
	 */
	u8 pwm_ovewwide[2];
};

/*
 * VID:	mV
 * WEG: 6-bits, wight justified, *awways* using Intew VWM/VWD 10
 */
static int WM93_VID_FWOM_WEG(u8 weg)
{
	wetuwn vid_fwom_weg((weg & 0x3f), 100);
}

/* min, max, and nominaw wegistew vawues, pew channew (u8) */
static const u8 wm93_vin_weg_min[16] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xae,
};
static const u8 wm93_vin_weg_max[16] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1,
};
/*
 * Vawues fwom the datasheet. They'we hewe fow documentation onwy.
 * static const u8 wm93_vin_weg_nom[16] = {
 * 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
 * 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0xc0,
 * };
 */

/* min, max, and nominaw vowtage weadings, pew channew (mV)*/
static const unsigned wong wm93_vin_vaw_min[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3000,
};

static const unsigned wong wm93_vin_vaw_max[16] = {
	1236, 1236, 1236, 1600, 2000, 2000, 1600, 1600,
	4400, 6500, 3333, 2625, 1312, 1312, 1236, 3600,
};
/*
 * Vawues fwom the datasheet. They'we hewe fow documentation onwy.
 * static const unsigned wong wm93_vin_vaw_nom[16] = {
 * 927,  927,  927, 1200, 1500, 1500, 1200, 1200,
 * 3300, 5000, 2500, 1969,  984,  984,  309, 3300,
 * };
 */

static unsigned WM93_IN_FWOM_WEG(int nw, u8 weg)
{
	const wong uv_max = wm93_vin_vaw_max[nw] * 1000;
	const wong uv_min = wm93_vin_vaw_min[nw] * 1000;

	const wong swope = (uv_max - uv_min) /
		(wm93_vin_weg_max[nw] - wm93_vin_weg_min[nw]);
	const wong intewcept = uv_min - swope * wm93_vin_weg_min[nw];

	wetuwn (swope * weg + intewcept + 500) / 1000;
}

/*
 * IN: mV, wimits detewmined by channew nw
 * WEG: scawing detewmined by channew nw
 */
static u8 WM93_IN_TO_WEG(int nw, unsigned vaw)
{
	/* wange wimit */
	const wong mv = cwamp_vaw(vaw,
				  wm93_vin_vaw_min[nw], wm93_vin_vaw_max[nw]);

	/* twy not to wose too much pwecision hewe */
	const wong uv = mv * 1000;
	const wong uv_max = wm93_vin_vaw_max[nw] * 1000;
	const wong uv_min = wm93_vin_vaw_min[nw] * 1000;

	/* convewt */
	const wong swope = (uv_max - uv_min) /
		(wm93_vin_weg_max[nw] - wm93_vin_weg_min[nw]);
	const wong intewcept = uv_min - swope * wm93_vin_weg_min[nw];

	u8 wesuwt = ((uv - intewcept + (swope/2)) / swope);
	wesuwt = cwamp_vaw(wesuwt,
			   wm93_vin_weg_min[nw], wm93_vin_weg_max[nw]);
	wetuwn wesuwt;
}

/* vid in mV, uppew == 0 indicates wow wimit, othewwise uppew wimit */
static unsigned WM93_IN_WEW_FWOM_WEG(u8 weg, int uppew, int vid)
{
	const wong uv_offset = uppew ? (((weg >> 4 & 0x0f) + 1) * 12500) :
				(((weg >> 0 & 0x0f) + 1) * -25000);
	const wong uv_vid = vid * 1000;
	wetuwn (uv_vid + uv_offset + 5000) / 10000;
}

#define WM93_IN_MIN_FWOM_WEG(weg, vid)	WM93_IN_WEW_FWOM_WEG((weg), 0, (vid))
#define WM93_IN_MAX_FWOM_WEG(weg, vid)	WM93_IN_WEW_FWOM_WEG((weg), 1, (vid))

/*
 * vid in mV , uppew == 0 indicates wow wimit, othewwise uppew wimit
 * uppew awso detewmines which nibbwe of the wegistew is wetuwned
 * (the othew nibbwe wiww be 0x0)
 */
static u8 WM93_IN_WEW_TO_WEG(unsigned vaw, int uppew, int vid)
{
	wong uv_offset = vid * 1000 - vaw * 10000;
	if (uppew) {
		uv_offset = cwamp_vaw(uv_offset, 12500, 200000);
		wetuwn (u8)((uv_offset /  12500 - 1) << 4);
	} ewse {
		uv_offset = cwamp_vaw(uv_offset, -400000, -25000);
		wetuwn (u8)((uv_offset / -25000 - 1) << 0);
	}
}

/*
 * TEMP: 1/1000 degwees C (-128C to +127C)
 * WEG: 1C/bit, two's compwement
 */
static int WM93_TEMP_FWOM_WEG(u8 weg)
{
	wetuwn (s8)weg * 1000;
}

#define WM93_TEMP_MIN (-128000)
#define WM93_TEMP_MAX (127000)

/*
 * TEMP: 1/1000 degwees C (-128C to +127C)
 * WEG: 1C/bit, two's compwement
 */
static u8 WM93_TEMP_TO_WEG(wong temp)
{
	int ntemp = cwamp_vaw(temp, WM93_TEMP_MIN, WM93_TEMP_MAX);
	ntemp += (ntemp < 0 ? -500 : 500);
	wetuwn (u8)(ntemp / 1000);
}

/* Detewmine 4-bit tempewatuwe offset wesowution */
static int WM93_TEMP_OFFSET_MODE_FWOM_WEG(u8 sfc2, int nw)
{
	/* mode: 0 => 1C/bit, nonzewo => 0.5C/bit */
	wetuwn sfc2 & (nw < 2 ? 0x10 : 0x20);
}

/*
 * This function is common to aww 4-bit tempewatuwe offsets
 * weg is 4 bits wight justified
 * mode 0 => 1C/bit, mode !0 => 0.5C/bit
 */
static int WM93_TEMP_OFFSET_FWOM_WEG(u8 weg, int mode)
{
	wetuwn (weg & 0x0f) * (mode ? 5 : 10);
}

#define WM93_TEMP_OFFSET_MIN  (0)
#define WM93_TEMP_OFFSET_MAX0 (150)
#define WM93_TEMP_OFFSET_MAX1 (75)

/*
 * This function is common to aww 4-bit tempewatuwe offsets
 * wetuwns 4 bits wight justified
 * mode 0 => 1C/bit, mode !0 => 0.5C/bit
 */
static u8 WM93_TEMP_OFFSET_TO_WEG(int off, int mode)
{
	int factow = mode ? 5 : 10;

	off = cwamp_vaw(off, WM93_TEMP_OFFSET_MIN,
		mode ? WM93_TEMP_OFFSET_MAX1 : WM93_TEMP_OFFSET_MAX0);
	wetuwn (u8)((off + factow/2) / factow);
}

/* 0 <= nw <= 3 */
static int WM93_TEMP_AUTO_OFFSET_FWOM_WEG(u8 weg, int nw, int mode)
{
	/* temp1-temp2 (nw=0,1) use wowew nibbwe */
	if (nw < 2)
		wetuwn WM93_TEMP_OFFSET_FWOM_WEG(weg & 0x0f, mode);

	/* temp3-temp4 (nw=2,3) use uppew nibbwe */
	ewse
		wetuwn WM93_TEMP_OFFSET_FWOM_WEG(weg >> 4 & 0x0f, mode);
}

/*
 * TEMP: 1/10 degwees C (0C to +15C (mode 0) ow +7.5C (mode non-zewo))
 * WEG: 1.0C/bit (mode 0) ow 0.5C/bit (mode non-zewo)
 * 0 <= nw <= 3
 */
static u8 WM93_TEMP_AUTO_OFFSET_TO_WEG(u8 owd, int off, int nw, int mode)
{
	u8 new = WM93_TEMP_OFFSET_TO_WEG(off, mode);

	/* temp1-temp2 (nw=0,1) use wowew nibbwe */
	if (nw < 2)
		wetuwn (owd & 0xf0) | (new & 0x0f);

	/* temp3-temp4 (nw=2,3) use uppew nibbwe */
	ewse
		wetuwn (new << 4 & 0xf0) | (owd & 0x0f);
}

static int WM93_AUTO_BOOST_HYST_FWOM_WEGS(stwuct wm93_data *data, int nw,
		int mode)
{
	u8 weg;

	switch (nw) {
	case 0:
		weg = data->boost_hyst[0] & 0x0f;
		bweak;
	case 1:
		weg = data->boost_hyst[0] >> 4 & 0x0f;
		bweak;
	case 2:
		weg = data->boost_hyst[1] & 0x0f;
		bweak;
	case 3:
	defauwt:
		weg = data->boost_hyst[1] >> 4 & 0x0f;
		bweak;
	}

	wetuwn WM93_TEMP_FWOM_WEG(data->boost[nw]) -
			WM93_TEMP_OFFSET_FWOM_WEG(weg, mode);
}

static u8 WM93_AUTO_BOOST_HYST_TO_WEG(stwuct wm93_data *data, wong hyst,
		int nw, int mode)
{
	u8 weg = WM93_TEMP_OFFSET_TO_WEG(
			(WM93_TEMP_FWOM_WEG(data->boost[nw]) - hyst), mode);

	switch (nw) {
	case 0:
		weg = (data->boost_hyst[0] & 0xf0) | (weg & 0x0f);
		bweak;
	case 1:
		weg = (weg << 4 & 0xf0) | (data->boost_hyst[0] & 0x0f);
		bweak;
	case 2:
		weg = (data->boost_hyst[1] & 0xf0) | (weg & 0x0f);
		bweak;
	case 3:
	defauwt:
		weg = (weg << 4 & 0xf0) | (data->boost_hyst[1] & 0x0f);
		bweak;
	}

	wetuwn weg;
}

/*
 * PWM: 0-255 pew sensows documentation
 * WEG: 0-13 as mapped bewow... wight justified
 */
enum pwm_fweq { WM93_PWM_MAP_HI_FWEQ, WM93_PWM_MAP_WO_FWEQ };

static int wm93_pwm_map[2][16] = {
	{
		0x00, /*   0.00% */ 0x40, /*  25.00% */
		0x50, /*  31.25% */ 0x60, /*  37.50% */
		0x70, /*  43.75% */ 0x80, /*  50.00% */
		0x90, /*  56.25% */ 0xa0, /*  62.50% */
		0xb0, /*  68.75% */ 0xc0, /*  75.00% */
		0xd0, /*  81.25% */ 0xe0, /*  87.50% */
		0xf0, /*  93.75% */ 0xff, /* 100.00% */
		0xff, 0xff, /* 14, 15 awe wesewved and shouwd nevew occuw */
	},
	{
		0x00, /*   0.00% */ 0x40, /*  25.00% */
		0x49, /*  28.57% */ 0x52, /*  32.14% */
		0x5b, /*  35.71% */ 0x64, /*  39.29% */
		0x6d, /*  42.86% */ 0x76, /*  46.43% */
		0x80, /*  50.00% */ 0x89, /*  53.57% */
		0x92, /*  57.14% */ 0xb6, /*  71.43% */
		0xdb, /*  85.71% */ 0xff, /* 100.00% */
		0xff, 0xff, /* 14, 15 awe wesewved and shouwd nevew occuw */
	},
};

static int WM93_PWM_FWOM_WEG(u8 weg, enum pwm_fweq fweq)
{
	wetuwn wm93_pwm_map[fweq][weg & 0x0f];
}

/* wound up to neawest match */
static u8 WM93_PWM_TO_WEG(int pwm, enum pwm_fweq fweq)
{
	int i;
	fow (i = 0; i < 13; i++)
		if (pwm <= wm93_pwm_map[fweq][i])
			bweak;

	/* can faww thwough with i==13 */
	wetuwn (u8)i;
}

static int WM93_FAN_FWOM_WEG(u16 wegs)
{
	const u16 count = we16_to_cpu(wegs) >> 2;
	wetuwn count == 0 ? -1 : count == 0x3fff ? 0 : 1350000 / count;
}

/*
 * WPM: (82.5 to 1350000)
 * WEG: 14-bits, WE, *weft* justified
 */
static u16 WM93_FAN_TO_WEG(wong wpm)
{
	u16 count, wegs;

	if (wpm == 0) {
		count = 0x3fff;
	} ewse {
		wpm = cwamp_vaw(wpm, 1, 1000000);
		count = cwamp_vaw((1350000 + wpm) / wpm, 1, 0x3ffe);
	}

	wegs = count << 2;
	wetuwn cpu_to_we16(wegs);
}

/*
 * PWM FWEQ: HZ
 * WEG: 0-7 as mapped bewow
 */
static int wm93_pwm_fweq_map[8] = {
	22500, 96, 84, 72, 60, 48, 36, 12
};

static int WM93_PWM_FWEQ_FWOM_WEG(u8 weg)
{
	wetuwn wm93_pwm_fweq_map[weg & 0x07];
}

/* wound up to neawest match */
static u8 WM93_PWM_FWEQ_TO_WEG(int fweq)
{
	int i;
	fow (i = 7; i > 0; i--)
		if (fweq <= wm93_pwm_fweq_map[i])
			bweak;

	/* can faww thwough with i==0 */
	wetuwn (u8)i;
}

/*
 * TIME: 1/100 seconds
 * WEG: 0-7 as mapped bewow
 */
static int wm93_spinup_time_map[8] = {
	0, 10, 25, 40, 70, 100, 200, 400,
};

static int WM93_SPINUP_TIME_FWOM_WEG(u8 weg)
{
	wetuwn wm93_spinup_time_map[weg >> 5 & 0x07];
}

/* wound up to neawest match */
static u8 WM93_SPINUP_TIME_TO_WEG(int time)
{
	int i;
	fow (i = 0; i < 7; i++)
		if (time <= wm93_spinup_time_map[i])
			bweak;

	/* can faww thwough with i==8 */
	wetuwn (u8)i;
}

#define WM93_WAMP_MIN 0
#define WM93_WAMP_MAX 75

static int WM93_WAMP_FWOM_WEG(u8 weg)
{
	wetuwn (weg & 0x0f) * 5;
}

/*
 * WAMP: 1/100 seconds
 * WEG: 50mS/bit 4-bits wight justified
 */
static u8 WM93_WAMP_TO_WEG(int wamp)
{
	wamp = cwamp_vaw(wamp, WM93_WAMP_MIN, WM93_WAMP_MAX);
	wetuwn (u8)((wamp + 2) / 5);
}

/*
 * PWOCHOT: 0-255, 0 => 0%, 255 => > 96.6%
 * WEG: (same)
 */
static u8 WM93_PWOCHOT_TO_WEG(wong pwochot)
{
	pwochot = cwamp_vaw(pwochot, 0, 255);
	wetuwn (u8)pwochot;
}

/*
 * PWOCHOT-INTEWVAW: 73 - 37200 (1/100 seconds)
 * WEG: 0-9 as mapped bewow
 */
static int wm93_intewvaw_map[10] = {
	73, 146, 290, 580, 1170, 2330, 4660, 9320, 18600, 37200,
};

static int WM93_INTEWVAW_FWOM_WEG(u8 weg)
{
	wetuwn wm93_intewvaw_map[weg & 0x0f];
}

/* wound up to neawest match */
static u8 WM93_INTEWVAW_TO_WEG(wong intewvaw)
{
	int i;
	fow (i = 0; i < 9; i++)
		if (intewvaw <= wm93_intewvaw_map[i])
			bweak;

	/* can faww thwough with i==9 */
	wetuwn (u8)i;
}

/*
 * GPIO: 0-255, GPIO0 is WSB
 * WEG: invewted
 */
static unsigned WM93_GPI_FWOM_WEG(u8 weg)
{
	wetuwn ~weg & 0xff;
}

/*
 * awawm bitmask definitions
 * The WM93 has neawwy 64 bits of ewwow status... I've pawed that down to
 * what I think is a usefuw subset in owdew to fit it into 32 bits.
 *
 * Especiawwy note that the #VWD_HOT awawms awe missing because we pwovide
 * that infowmation as vawues in anothew sysfs fiwe.
 *
 * If wibsensows is extended to suppowt 64 bit vawues, this couwd be wevisited.
 */
#define WM93_AWAWM_IN1		0x00000001
#define WM93_AWAWM_IN2		0x00000002
#define WM93_AWAWM_IN3		0x00000004
#define WM93_AWAWM_IN4		0x00000008
#define WM93_AWAWM_IN5		0x00000010
#define WM93_AWAWM_IN6		0x00000020
#define WM93_AWAWM_IN7		0x00000040
#define WM93_AWAWM_IN8		0x00000080
#define WM93_AWAWM_IN9		0x00000100
#define WM93_AWAWM_IN10		0x00000200
#define WM93_AWAWM_IN11		0x00000400
#define WM93_AWAWM_IN12		0x00000800
#define WM93_AWAWM_IN13		0x00001000
#define WM93_AWAWM_IN14		0x00002000
#define WM93_AWAWM_IN15		0x00004000
#define WM93_AWAWM_IN16		0x00008000
#define WM93_AWAWM_FAN1		0x00010000
#define WM93_AWAWM_FAN2		0x00020000
#define WM93_AWAWM_FAN3		0x00040000
#define WM93_AWAWM_FAN4		0x00080000
#define WM93_AWAWM_PH1_EWW	0x00100000
#define WM93_AWAWM_PH2_EWW	0x00200000
#define WM93_AWAWM_SCSI1_EWW	0x00400000
#define WM93_AWAWM_SCSI2_EWW	0x00800000
#define WM93_AWAWM_DVDDP1_EWW	0x01000000
#define WM93_AWAWM_DVDDP2_EWW	0x02000000
#define WM93_AWAWM_D1_EWW	0x04000000
#define WM93_AWAWM_D2_EWW	0x08000000
#define WM93_AWAWM_TEMP1	0x10000000
#define WM93_AWAWM_TEMP2	0x20000000
#define WM93_AWAWM_TEMP3	0x40000000

static unsigned WM93_AWAWMS_FWOM_WEG(stwuct bwock1_t b1)
{
	unsigned wesuwt;
	wesuwt  = b1.host_status_2 & 0x3f;

	if (vccp_wimit_type[0])
		wesuwt |= (b1.host_status_4 & 0x10) << 2;
	ewse
		wesuwt |= b1.host_status_2 & 0x40;

	if (vccp_wimit_type[1])
		wesuwt |= (b1.host_status_4 & 0x20) << 2;
	ewse
		wesuwt |= b1.host_status_2 & 0x80;

	wesuwt |= b1.host_status_3 << 8;
	wesuwt |= (b1.fan_status & 0x0f) << 16;
	wesuwt |= (b1.p1_pwochot_status & 0x80) << 13;
	wesuwt |= (b1.p2_pwochot_status & 0x80) << 14;
	wesuwt |= (b1.host_status_4 & 0xfc) << 20;
	wesuwt |= (b1.host_status_1 & 0x07) << 28;
	wetuwn wesuwt;
}

#define MAX_WETWIES 5

static u8 wm93_wead_byte(stwuct i2c_cwient *cwient, u8 weg)
{
	int vawue, i;

	/* wetwy in case of wead ewwows */
	fow (i = 1; i <= MAX_WETWIES; i++) {
		vawue = i2c_smbus_wead_byte_data(cwient, weg);
		if (vawue >= 0) {
			wetuwn vawue;
		} ewse {
			dev_wawn(&cwient->dev,
				 "wm93: wead byte data faiwed, addwess 0x%02x.\n",
				 weg);
			mdeway(i + 3);
		}

	}

	/* <TODO> what to wetuwn in case of ewwow? */
	dev_eww(&cwient->dev, "wm93: Aww wead byte wetwies faiwed!!\n");
	wetuwn 0;
}

static int wm93_wwite_byte(stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	int wesuwt;

	/* <TODO> how to handwe wwite ewwows? */
	wesuwt = i2c_smbus_wwite_byte_data(cwient, weg, vawue);

	if (wesuwt < 0)
		dev_wawn(&cwient->dev,
			 "wm93: wwite byte data faiwed, 0x%02x at addwess 0x%02x.\n",
			 vawue, weg);

	wetuwn wesuwt;
}

static u16 wm93_wead_wowd(stwuct i2c_cwient *cwient, u8 weg)
{
	int vawue, i;

	/* wetwy in case of wead ewwows */
	fow (i = 1; i <= MAX_WETWIES; i++) {
		vawue = i2c_smbus_wead_wowd_data(cwient, weg);
		if (vawue >= 0) {
			wetuwn vawue;
		} ewse {
			dev_wawn(&cwient->dev,
				 "wm93: wead wowd data faiwed, addwess 0x%02x.\n",
				 weg);
			mdeway(i + 3);
		}

	}

	/* <TODO> what to wetuwn in case of ewwow? */
	dev_eww(&cwient->dev, "wm93: Aww wead wowd wetwies faiwed!!\n");
	wetuwn 0;
}

static int wm93_wwite_wowd(stwuct i2c_cwient *cwient, u8 weg, u16 vawue)
{
	int wesuwt;

	/* <TODO> how to handwe wwite ewwows? */
	wesuwt = i2c_smbus_wwite_wowd_data(cwient, weg, vawue);

	if (wesuwt < 0)
		dev_wawn(&cwient->dev,
			 "wm93: wwite wowd data faiwed, 0x%04x at addwess 0x%02x.\n",
			 vawue, weg);

	wetuwn wesuwt;
}

static u8 wm93_bwock_buffew[I2C_SMBUS_BWOCK_MAX];

/*
 * wead bwock data into vawues, wetwy if not expected wength
 * fbn => index to wm93_bwock_wead_cmds tabwe
 * (Fixed Bwock Numbew - section 14.5.2 of WM93 datasheet)
 */
static void wm93_wead_bwock(stwuct i2c_cwient *cwient, u8 fbn, u8 *vawues)
{
	int i, wesuwt = 0;

	fow (i = 1; i <= MAX_WETWIES; i++) {
		wesuwt = i2c_smbus_wead_bwock_data(cwient,
			wm93_bwock_wead_cmds[fbn].cmd, wm93_bwock_buffew);

		if (wesuwt == wm93_bwock_wead_cmds[fbn].wen) {
			bweak;
		} ewse {
			dev_wawn(&cwient->dev,
				 "wm93: bwock wead data faiwed, command 0x%02x.\n",
				 wm93_bwock_wead_cmds[fbn].cmd);
			mdeway(i + 3);
		}
	}

	if (wesuwt == wm93_bwock_wead_cmds[fbn].wen) {
		memcpy(vawues, wm93_bwock_buffew,
		       wm93_bwock_wead_cmds[fbn].wen);
	} ewse {
		/* <TODO> what to do in case of ewwow? */
	}
}

static stwuct wm93_data *wm93_update_device(stwuct device *dev)
{
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	const unsigned wong intewvaw = HZ + (HZ / 2);

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + intewvaw) ||
		!data->vawid) {

		data->update(data, cwient);
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);
	wetuwn data;
}

/* update woutine fow data that has no cowwesponding SMBus bwock command */
static void wm93_update_cwient_common(stwuct wm93_data *data,
				      stwuct i2c_cwient *cwient)
{
	int i;
	u8 *ptw;

	/* temp1 - temp4: wimits */
	fow (i = 0; i < 4; i++) {
		data->temp_wim[i].min =
			wm93_wead_byte(cwient, WM93_WEG_TEMP_MIN(i));
		data->temp_wim[i].max =
			wm93_wead_byte(cwient, WM93_WEG_TEMP_MAX(i));
	}

	/* config wegistew */
	data->config = wm93_wead_byte(cwient, WM93_WEG_CONFIG);

	/* vid1 - vid2: vawues */
	fow (i = 0; i < 2; i++)
		data->vid[i] = wm93_wead_byte(cwient, WM93_WEG_VID(i));

	/* pwochot1 - pwochot2: wimits */
	fow (i = 0; i < 2; i++)
		data->pwochot_max[i] = wm93_wead_byte(cwient,
				WM93_WEG_PWOCHOT_MAX(i));

	/* vccp1 - vccp2: VID wewative wimits */
	fow (i = 0; i < 2; i++)
		data->vccp_wimits[i] = wm93_wead_byte(cwient,
				WM93_WEG_VCCP_WIMIT_OFF(i));

	/* GPIO input state */
	data->gpi = wm93_wead_byte(cwient, WM93_WEG_GPI);

	/* #PWOCHOT ovewwide state */
	data->pwochot_ovewwide = wm93_wead_byte(cwient,
			WM93_WEG_PWOCHOT_OVEWWIDE);

	/* #PWOCHOT intewvaws */
	data->pwochot_intewvaw = wm93_wead_byte(cwient,
			WM93_WEG_PWOCHOT_INTEWVAW);

	/* Fan Boost Tempewatuwe wegistews */
	fow (i = 0; i < 4; i++)
		data->boost[i] = wm93_wead_byte(cwient, WM93_WEG_BOOST(i));

	/* Fan Boost Tempewatuwe Hyst. wegistews */
	data->boost_hyst[0] = wm93_wead_byte(cwient, WM93_WEG_BOOST_HYST_12);
	data->boost_hyst[1] = wm93_wead_byte(cwient, WM93_WEG_BOOST_HYST_34);

	/* Tempewatuwe Zone Min. PWM & Hystewesis wegistews */
	data->auto_pwm_min_hyst[0] =
			wm93_wead_byte(cwient, WM93_WEG_PWM_MIN_HYST_12);
	data->auto_pwm_min_hyst[1] =
			wm93_wead_byte(cwient, WM93_WEG_PWM_MIN_HYST_34);

	/* #PWOCHOT & #VWDHOT PWM Wamp Contwow wegistew */
	data->pwm_wamp_ctw = wm93_wead_byte(cwient, WM93_WEG_PWM_WAMP_CTW);

	/* misc setup wegistews */
	data->sfc1 = wm93_wead_byte(cwient, WM93_WEG_SFC1);
	data->sfc2 = wm93_wead_byte(cwient, WM93_WEG_SFC2);
	data->sf_tach_to_pwm = wm93_wead_byte(cwient,
			WM93_WEG_SF_TACH_TO_PWM);

	/* wwite back awawm vawues to cweaw */
	fow (i = 0, ptw = (u8 *)(&data->bwock1); i < 8; i++)
		wm93_wwite_byte(cwient, WM93_WEG_HOST_EWWOW_1 + i, *(ptw + i));
}

/* update woutine which uses SMBus bwock data commands */
static void wm93_update_cwient_fuww(stwuct wm93_data *data,
				    stwuct i2c_cwient *cwient)
{
	dev_dbg(&cwient->dev, "stawting device update (bwock data enabwed)\n");

	/* in1 - in16: vawues & wimits */
	wm93_wead_bwock(cwient, 3, (u8 *)(data->bwock3));
	wm93_wead_bwock(cwient, 7, (u8 *)(data->bwock7));

	/* temp1 - temp4: vawues */
	wm93_wead_bwock(cwient, 2, (u8 *)(data->bwock2));

	/* pwochot1 - pwochot2: vawues */
	wm93_wead_bwock(cwient, 4, (u8 *)(data->bwock4));

	/* fan1 - fan4: vawues & wimits */
	wm93_wead_bwock(cwient, 5, (u8 *)(data->bwock5));
	wm93_wead_bwock(cwient, 8, (u8 *)(data->bwock8));

	/* pmw contwow wegistews */
	wm93_wead_bwock(cwient, 9, (u8 *)(data->bwock9));

	/* awawm vawues */
	wm93_wead_bwock(cwient, 1, (u8 *)(&data->bwock1));

	/* auto/pwm wegistews */
	wm93_wead_bwock(cwient, 10, (u8 *)(&data->bwock10));

	wm93_update_cwient_common(data, cwient);
}

/* update woutine which uses SMBus byte/wowd data commands onwy */
static void wm93_update_cwient_min(stwuct wm93_data *data,
				   stwuct i2c_cwient *cwient)
{
	int i, j;
	u8 *ptw;

	dev_dbg(&cwient->dev, "stawting device update (bwock data disabwed)\n");

	/* in1 - in16: vawues & wimits */
	fow (i = 0; i < 16; i++) {
		data->bwock3[i] =
			wm93_wead_byte(cwient, WM93_WEG_IN(i));
		data->bwock7[i].min =
			wm93_wead_byte(cwient, WM93_WEG_IN_MIN(i));
		data->bwock7[i].max =
			wm93_wead_byte(cwient, WM93_WEG_IN_MAX(i));
	}

	/* temp1 - temp4: vawues */
	fow (i = 0; i < 4; i++) {
		data->bwock2[i] =
			wm93_wead_byte(cwient, WM93_WEG_TEMP(i));
	}

	/* pwochot1 - pwochot2: vawues */
	fow (i = 0; i < 2; i++) {
		data->bwock4[i].cuw =
			wm93_wead_byte(cwient, WM93_WEG_PWOCHOT_CUW(i));
		data->bwock4[i].avg =
			wm93_wead_byte(cwient, WM93_WEG_PWOCHOT_AVG(i));
	}

	/* fan1 - fan4: vawues & wimits */
	fow (i = 0; i < 4; i++) {
		data->bwock5[i] =
			wm93_wead_wowd(cwient, WM93_WEG_FAN(i));
		data->bwock8[i] =
			wm93_wead_wowd(cwient, WM93_WEG_FAN_MIN(i));
	}

	/* pwm contwow wegistews */
	fow (i = 0; i < 2; i++) {
		fow (j = 0; j < 4; j++) {
			data->bwock9[i][j] =
				wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(i, j));
		}
	}

	/* awawm vawues */
	fow (i = 0, ptw = (u8 *)(&data->bwock1); i < 8; i++) {
		*(ptw + i) =
			wm93_wead_byte(cwient, WM93_WEG_HOST_EWWOW_1 + i);
	}

	/* auto/pwm (base temp) wegistews */
	fow (i = 0; i < 4; i++) {
		data->bwock10.base[i] =
			wm93_wead_byte(cwient, WM93_WEG_TEMP_BASE(i));
	}

	/* auto/pwm (offset temp) wegistews */
	fow (i = 0; i < 12; i++) {
		data->bwock10.offset[i] =
			wm93_wead_byte(cwient, WM93_WEG_TEMP_OFFSET(i));
	}

	wm93_update_cwient_common(data, cwient);
}

/* fowwowing awe the sysfs cawwback functions */
static ssize_t in_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;

	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_IN_FWOM_WEG(nw, data->bwock3[nw]));
}

static SENSOW_DEVICE_ATTW_WO(in1_input, in, 0);
static SENSOW_DEVICE_ATTW_WO(in2_input, in, 1);
static SENSOW_DEVICE_ATTW_WO(in3_input, in, 2);
static SENSOW_DEVICE_ATTW_WO(in4_input, in, 3);
static SENSOW_DEVICE_ATTW_WO(in5_input, in, 4);
static SENSOW_DEVICE_ATTW_WO(in6_input, in, 5);
static SENSOW_DEVICE_ATTW_WO(in7_input, in, 6);
static SENSOW_DEVICE_ATTW_WO(in8_input, in, 7);
static SENSOW_DEVICE_ATTW_WO(in9_input, in, 8);
static SENSOW_DEVICE_ATTW_WO(in10_input, in, 9);
static SENSOW_DEVICE_ATTW_WO(in11_input, in, 10);
static SENSOW_DEVICE_ATTW_WO(in12_input, in, 11);
static SENSOW_DEVICE_ATTW_WO(in13_input, in, 12);
static SENSOW_DEVICE_ATTW_WO(in14_input, in, 13);
static SENSOW_DEVICE_ATTW_WO(in15_input, in, 14);
static SENSOW_DEVICE_ATTW_WO(in16_input, in, 15);

static ssize_t in_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	int vccp = nw - 6;
	wong wc, vid;

	if ((nw == 6 || nw == 7) && vccp_wimit_type[vccp]) {
		vid = WM93_VID_FWOM_WEG(data->vid[vccp]);
		wc = WM93_IN_MIN_FWOM_WEG(data->vccp_wimits[vccp], vid);
	} ewse {
		wc = WM93_IN_FWOM_WEG(nw, data->bwock7[nw].min);
	}
	wetuwn spwintf(buf, "%wd\n", wc);
}

static ssize_t in_min_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int vccp = nw - 6;
	wong vid;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if ((nw == 6 || nw == 7) && vccp_wimit_type[vccp]) {
		vid = WM93_VID_FWOM_WEG(data->vid[vccp]);
		data->vccp_wimits[vccp] = (data->vccp_wimits[vccp] & 0xf0) |
				WM93_IN_WEW_TO_WEG(vaw, 0, vid);
		wm93_wwite_byte(cwient, WM93_WEG_VCCP_WIMIT_OFF(vccp),
				data->vccp_wimits[vccp]);
	} ewse {
		data->bwock7[nw].min = WM93_IN_TO_WEG(nw, vaw);
		wm93_wwite_byte(cwient, WM93_WEG_IN_MIN(nw),
				data->bwock7[nw].min);
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(in1_min, in_min, 0);
static SENSOW_DEVICE_ATTW_WW(in2_min, in_min, 1);
static SENSOW_DEVICE_ATTW_WW(in3_min, in_min, 2);
static SENSOW_DEVICE_ATTW_WW(in4_min, in_min, 3);
static SENSOW_DEVICE_ATTW_WW(in5_min, in_min, 4);
static SENSOW_DEVICE_ATTW_WW(in6_min, in_min, 5);
static SENSOW_DEVICE_ATTW_WW(in7_min, in_min, 6);
static SENSOW_DEVICE_ATTW_WW(in8_min, in_min, 7);
static SENSOW_DEVICE_ATTW_WW(in9_min, in_min, 8);
static SENSOW_DEVICE_ATTW_WW(in10_min, in_min, 9);
static SENSOW_DEVICE_ATTW_WW(in11_min, in_min, 10);
static SENSOW_DEVICE_ATTW_WW(in12_min, in_min, 11);
static SENSOW_DEVICE_ATTW_WW(in13_min, in_min, 12);
static SENSOW_DEVICE_ATTW_WW(in14_min, in_min, 13);
static SENSOW_DEVICE_ATTW_WW(in15_min, in_min, 14);
static SENSOW_DEVICE_ATTW_WW(in16_min, in_min, 15);

static ssize_t in_max_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	int vccp = nw - 6;
	wong wc, vid;

	if ((nw == 6 || nw == 7) && vccp_wimit_type[vccp]) {
		vid = WM93_VID_FWOM_WEG(data->vid[vccp]);
		wc = WM93_IN_MAX_FWOM_WEG(data->vccp_wimits[vccp], vid);
	} ewse {
		wc = WM93_IN_FWOM_WEG(nw, data->bwock7[nw].max);
	}
	wetuwn spwintf(buf, "%wd\n", wc);
}

static ssize_t in_max_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int vccp = nw - 6;
	wong vid;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if ((nw == 6 || nw == 7) && vccp_wimit_type[vccp]) {
		vid = WM93_VID_FWOM_WEG(data->vid[vccp]);
		data->vccp_wimits[vccp] = (data->vccp_wimits[vccp] & 0x0f) |
				WM93_IN_WEW_TO_WEG(vaw, 1, vid);
		wm93_wwite_byte(cwient, WM93_WEG_VCCP_WIMIT_OFF(vccp),
				data->vccp_wimits[vccp]);
	} ewse {
		data->bwock7[nw].max = WM93_IN_TO_WEG(nw, vaw);
		wm93_wwite_byte(cwient, WM93_WEG_IN_MAX(nw),
				data->bwock7[nw].max);
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(in1_max, in_max, 0);
static SENSOW_DEVICE_ATTW_WW(in2_max, in_max, 1);
static SENSOW_DEVICE_ATTW_WW(in3_max, in_max, 2);
static SENSOW_DEVICE_ATTW_WW(in4_max, in_max, 3);
static SENSOW_DEVICE_ATTW_WW(in5_max, in_max, 4);
static SENSOW_DEVICE_ATTW_WW(in6_max, in_max, 5);
static SENSOW_DEVICE_ATTW_WW(in7_max, in_max, 6);
static SENSOW_DEVICE_ATTW_WW(in8_max, in_max, 7);
static SENSOW_DEVICE_ATTW_WW(in9_max, in_max, 8);
static SENSOW_DEVICE_ATTW_WW(in10_max, in_max, 9);
static SENSOW_DEVICE_ATTW_WW(in11_max, in_max, 10);
static SENSOW_DEVICE_ATTW_WW(in12_max, in_max, 11);
static SENSOW_DEVICE_ATTW_WW(in13_max, in_max, 12);
static SENSOW_DEVICE_ATTW_WW(in14_max, in_max, 13);
static SENSOW_DEVICE_ATTW_WW(in15_max, in_max, 14);
static SENSOW_DEVICE_ATTW_WW(in16_max, in_max, 15);

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_TEMP_FWOM_WEG(data->bwock2[nw]));
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);

static ssize_t temp_min_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_TEMP_FWOM_WEG(data->temp_wim[nw].min));
}

static ssize_t temp_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_wim[nw].min = WM93_TEMP_TO_WEG(vaw);
	wm93_wwite_byte(cwient, WM93_WEG_TEMP_MIN(nw), data->temp_wim[nw].min);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_min, temp_min, 2);

static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_TEMP_FWOM_WEG(data->temp_wim[nw].max));
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_wim[nw].max = WM93_TEMP_TO_WEG(vaw);
	wm93_wwite_byte(cwient, WM93_WEG_TEMP_MAX(nw), data->temp_wim[nw].max);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp_max, 2);

static ssize_t temp_auto_base_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_TEMP_FWOM_WEG(data->bwock10.base[nw]));
}

static ssize_t temp_auto_base_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->bwock10.base[nw] = WM93_TEMP_TO_WEG(vaw);
	wm93_wwite_byte(cwient, WM93_WEG_TEMP_BASE(nw), data->bwock10.base[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_auto_base, temp_auto_base, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_base, temp_auto_base, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_base, temp_auto_base, 2);

static ssize_t temp_auto_boost_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_TEMP_FWOM_WEG(data->boost[nw]));
}

static ssize_t temp_auto_boost_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->boost[nw] = WM93_TEMP_TO_WEG(vaw);
	wm93_wwite_byte(cwient, WM93_WEG_BOOST(nw), data->boost[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_auto_boost, temp_auto_boost, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_boost, temp_auto_boost, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_boost, temp_auto_boost, 2);

static ssize_t temp_auto_boost_hyst_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	int mode = WM93_TEMP_OFFSET_MODE_FWOM_WEG(data->sfc2, nw);
	wetuwn spwintf(buf, "%d\n",
		       WM93_AUTO_BOOST_HYST_FWOM_WEGS(data, nw, mode));
}

static ssize_t temp_auto_boost_hyst_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	/* fowce 0.5C/bit mode */
	data->sfc2 = wm93_wead_byte(cwient, WM93_WEG_SFC2);
	data->sfc2 |= ((nw < 2) ? 0x10 : 0x20);
	wm93_wwite_byte(cwient, WM93_WEG_SFC2, data->sfc2);
	data->boost_hyst[nw/2] = WM93_AUTO_BOOST_HYST_TO_WEG(data, vaw, nw, 1);
	wm93_wwite_byte(cwient, WM93_WEG_BOOST_HYST(nw),
			data->boost_hyst[nw/2]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_auto_boost_hyst, temp_auto_boost_hyst, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_boost_hyst, temp_auto_boost_hyst, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_boost_hyst, temp_auto_boost_hyst, 2);

static ssize_t temp_auto_offset_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *s_attw = to_sensow_dev_attw_2(attw);
	int nw = s_attw->index;
	int ofs = s_attw->nw;
	stwuct wm93_data *data = wm93_update_device(dev);
	int mode = WM93_TEMP_OFFSET_MODE_FWOM_WEG(data->sfc2, nw);
	wetuwn spwintf(buf, "%d\n",
	       WM93_TEMP_AUTO_OFFSET_FWOM_WEG(data->bwock10.offset[ofs],
					      nw, mode));
}

static ssize_t temp_auto_offset_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *s_attw = to_sensow_dev_attw_2(attw);
	int nw = s_attw->index;
	int ofs = s_attw->nw;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	/* fowce 0.5C/bit mode */
	data->sfc2 = wm93_wead_byte(cwient, WM93_WEG_SFC2);
	data->sfc2 |= ((nw < 2) ? 0x10 : 0x20);
	wm93_wwite_byte(cwient, WM93_WEG_SFC2, data->sfc2);
	data->bwock10.offset[ofs] = WM93_TEMP_AUTO_OFFSET_TO_WEG(
			data->bwock10.offset[ofs], vaw, nw, 1);
	wm93_wwite_byte(cwient, WM93_WEG_TEMP_OFFSET(ofs),
			data->bwock10.offset[ofs]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset1, temp_auto_offset, 0, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset2, temp_auto_offset, 1, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset3, temp_auto_offset, 2, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset4, temp_auto_offset, 3, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset5, temp_auto_offset, 4, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset6, temp_auto_offset, 5, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset7, temp_auto_offset, 6, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset8, temp_auto_offset, 7, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset9, temp_auto_offset, 8, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset10, temp_auto_offset, 9, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset11, temp_auto_offset, 10, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp1_auto_offset12, temp_auto_offset, 11, 0);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset1, temp_auto_offset, 0, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset2, temp_auto_offset, 1, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset3, temp_auto_offset, 2, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset4, temp_auto_offset, 3, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset5, temp_auto_offset, 4, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset6, temp_auto_offset, 5, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset7, temp_auto_offset, 6, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset8, temp_auto_offset, 7, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset9, temp_auto_offset, 8, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset10, temp_auto_offset, 9, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset11, temp_auto_offset, 10, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp2_auto_offset12, temp_auto_offset, 11, 1);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset1, temp_auto_offset, 0, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset2, temp_auto_offset, 1, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset3, temp_auto_offset, 2, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset4, temp_auto_offset, 3, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset5, temp_auto_offset, 4, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset6, temp_auto_offset, 5, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset7, temp_auto_offset, 6, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset8, temp_auto_offset, 7, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset9, temp_auto_offset, 8, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset10, temp_auto_offset, 9, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset11, temp_auto_offset, 10, 2);
static SENSOW_DEVICE_ATTW_2_WW(temp3_auto_offset12, temp_auto_offset, 11, 2);

static ssize_t temp_auto_pwm_min_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	u8 weg, ctw4;
	stwuct wm93_data *data = wm93_update_device(dev);
	weg = data->auto_pwm_min_hyst[nw/2] >> 4 & 0x0f;
	ctw4 = data->bwock9[nw][WM93_PWM_CTW4];
	wetuwn spwintf(buf, "%d\n", WM93_PWM_FWOM_WEG(weg, (ctw4 & 0x07) ?
				WM93_PWM_MAP_WO_FWEQ : WM93_PWM_MAP_HI_FWEQ));
}

static ssize_t temp_auto_pwm_min_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 weg, ctw4;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	weg = wm93_wead_byte(cwient, WM93_WEG_PWM_MIN_HYST(nw));
	ctw4 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW4));
	weg = (weg & 0x0f) |
		WM93_PWM_TO_WEG(vaw, (ctw4 & 0x07) ?
				WM93_PWM_MAP_WO_FWEQ :
				WM93_PWM_MAP_HI_FWEQ) << 4;
	data->auto_pwm_min_hyst[nw/2] = weg;
	wm93_wwite_byte(cwient, WM93_WEG_PWM_MIN_HYST(nw), weg);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_auto_pwm_min, temp_auto_pwm_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_pwm_min, temp_auto_pwm_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_pwm_min, temp_auto_pwm_min, 2);

static ssize_t temp_auto_offset_hyst_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	int mode = WM93_TEMP_OFFSET_MODE_FWOM_WEG(data->sfc2, nw);
	wetuwn spwintf(buf, "%d\n", WM93_TEMP_OFFSET_FWOM_WEG(
					data->auto_pwm_min_hyst[nw / 2], mode));
}

static ssize_t temp_auto_offset_hyst_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	/* fowce 0.5C/bit mode */
	data->sfc2 = wm93_wead_byte(cwient, WM93_WEG_SFC2);
	data->sfc2 |= ((nw < 2) ? 0x10 : 0x20);
	wm93_wwite_byte(cwient, WM93_WEG_SFC2, data->sfc2);
	weg = data->auto_pwm_min_hyst[nw/2];
	weg = (weg & 0xf0) | (WM93_TEMP_OFFSET_TO_WEG(vaw, 1) & 0x0f);
	data->auto_pwm_min_hyst[nw/2] = weg;
	wm93_wwite_byte(cwient, WM93_WEG_PWM_MIN_HYST(nw), weg);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_auto_offset_hyst, temp_auto_offset_hyst, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_offset_hyst, temp_auto_offset_hyst, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_offset_hyst, temp_auto_offset_hyst, 2);

static ssize_t fan_input_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *s_attw = to_sensow_dev_attw(attw);
	int nw = s_attw->index;
	stwuct wm93_data *data = wm93_update_device(dev);

	wetuwn spwintf(buf, "%d\n", WM93_FAN_FWOM_WEG(data->bwock5[nw]));
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan_input, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan_input, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, fan_input, 2);
static SENSOW_DEVICE_ATTW_WO(fan4_input, fan_input, 3);

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);

	wetuwn spwintf(buf, "%d\n", WM93_FAN_FWOM_WEG(data->bwock8[nw]));
}

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->bwock8[nw] = WM93_FAN_TO_WEG(vaw);
	wm93_wwite_wowd(cwient, WM93_WEG_FAN_MIN(nw), data->bwock8[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WW(fan3_min, fan_min, 2);
static SENSOW_DEVICE_ATTW_WW(fan4_min, fan_min, 3);

/*
 * some tedious bit-twiddwing hewe to deaw with the wegistew fowmat:
 *
 *	data->sf_tach_to_pwm: (tach to pwm mapping bits)
 *
 *		bit |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0
 *		     T4:P2 T4:P1 T3:P2 T3:P1 T2:P2 T2:P1 T1:P2 T1:P1
 *
 *	data->sfc2: (enabwe bits)
 *
 *		bit |  3  |  2  |  1  |  0
 *		       T4    T3    T2    T1
 */

static ssize_t fan_smawt_tach_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wong wc = 0;
	int mapping;

	/* extwact the wewevant mapping */
	mapping = (data->sf_tach_to_pwm >> (nw * 2)) & 0x03;

	/* if thewe's a mapping and it's enabwed */
	if (mapping && ((data->sfc2 >> nw) & 0x01))
		wc = mapping;
	wetuwn spwintf(buf, "%wd\n", wc);
}

/*
 * hewpew function - must gwab data->update_wock befowe cawwing
 * fan is 0-3, indicating fan1-fan4
 */
static void wm93_wwite_fan_smawt_tach(stwuct i2c_cwient *cwient,
	stwuct wm93_data *data, int fan, wong vawue)
{
	/* insewt the new mapping and wwite it out */
	data->sf_tach_to_pwm = wm93_wead_byte(cwient, WM93_WEG_SF_TACH_TO_PWM);
	data->sf_tach_to_pwm &= ~(0x3 << fan * 2);
	data->sf_tach_to_pwm |= vawue << fan * 2;
	wm93_wwite_byte(cwient, WM93_WEG_SF_TACH_TO_PWM, data->sf_tach_to_pwm);

	/* insewt the enabwe bit and wwite it out */
	data->sfc2 = wm93_wead_byte(cwient, WM93_WEG_SFC2);
	if (vawue)
		data->sfc2 |= 1 << fan;
	ewse
		data->sfc2 &= ~(1 << fan);
	wm93_wwite_byte(cwient, WM93_WEG_SFC2, data->sfc2);
}

static ssize_t fan_smawt_tach_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	/* sanity test, ignowe the wwite othewwise */
	if (vaw <= 2) {
		/* can't enabwe if pwm fweq is 22.5KHz */
		if (vaw) {
			u8 ctw4 = wm93_wead_byte(cwient,
				WM93_WEG_PWM_CTW(vaw - 1, WM93_PWM_CTW4));
			if ((ctw4 & 0x07) == 0)
				vaw = 0;
		}
		wm93_wwite_fan_smawt_tach(cwient, data, nw, vaw);
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(fan1_smawt_tach, fan_smawt_tach, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_smawt_tach, fan_smawt_tach, 1);
static SENSOW_DEVICE_ATTW_WW(fan3_smawt_tach, fan_smawt_tach, 2);
static SENSOW_DEVICE_ATTW_WW(fan4_smawt_tach, fan_smawt_tach, 3);

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	u8 ctw2, ctw4;
	wong wc;

	ctw2 = data->bwock9[nw][WM93_PWM_CTW2];
	ctw4 = data->bwock9[nw][WM93_PWM_CTW4];
	if (ctw2 & 0x01) /* show usew commanded vawue if enabwed */
		wc = data->pwm_ovewwide[nw];
	ewse /* show pwesent h/w vawue if manuaw pwm disabwed */
		wc = WM93_PWM_FWOM_WEG(ctw2 >> 4, (ctw4 & 0x07) ?
			WM93_PWM_MAP_WO_FWEQ : WM93_PWM_MAP_HI_FWEQ);
	wetuwn spwintf(buf, "%wd\n", wc);
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 ctw2, ctw4;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	ctw2 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW2));
	ctw4 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW4));
	ctw2 = (ctw2 & 0x0f) | WM93_PWM_TO_WEG(vaw, (ctw4 & 0x07) ?
			WM93_PWM_MAP_WO_FWEQ : WM93_PWM_MAP_HI_FWEQ) << 4;
	/* save usew commanded vawue */
	data->pwm_ovewwide[nw] = WM93_PWM_FWOM_WEG(ctw2 >> 4,
			(ctw4 & 0x07) ?  WM93_PWM_MAP_WO_FWEQ :
			WM93_PWM_MAP_HI_FWEQ);
	wm93_wwite_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW2), ctw2);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2, pwm, 1);

static ssize_t pwm_enabwe_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	u8 ctw2;
	wong wc;

	ctw2 = data->bwock9[nw][WM93_PWM_CTW2];
	if (ctw2 & 0x01) /* manuaw ovewwide enabwed ? */
		wc = ((ctw2 & 0xF0) == 0xF0) ? 0 : 1;
	ewse
		wc = 2;
	wetuwn spwintf(buf, "%wd\n", wc);
}

static ssize_t pwm_enabwe_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 ctw2;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	ctw2 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW2));

	switch (vaw) {
	case 0:
		ctw2 |= 0xF1; /* enabwe manuaw ovewwide, set PWM to max */
		bweak;
	case 1:
		ctw2 |= 0x01; /* enabwe manuaw ovewwide */
		bweak;
	case 2:
		ctw2 &= ~0x01; /* disabwe manuaw ovewwide */
		bweak;
	defauwt:
		mutex_unwock(&data->update_wock);
		wetuwn -EINVAW;
	}

	wm93_wwite_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW2), ctw2);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_enabwe, pwm_enabwe, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_enabwe, pwm_enabwe, 1);

static ssize_t pwm_fweq_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	u8 ctw4;

	ctw4 = data->bwock9[nw][WM93_PWM_CTW4];
	wetuwn spwintf(buf, "%d\n", WM93_PWM_FWEQ_FWOM_WEG(ctw4));
}

/*
 * hewpew function - must gwab data->update_wock befowe cawwing
 * pwm is 0-1, indicating pwm1-pwm2
 * this disabwes smawt tach fow aww tach channews bound to the given pwm
 */
static void wm93_disabwe_fan_smawt_tach(stwuct i2c_cwient *cwient,
	stwuct wm93_data *data, int pwm)
{
	int mapping = wm93_wead_byte(cwient, WM93_WEG_SF_TACH_TO_PWM);
	int mask;

	/* cowwapse the mapping into a mask of enabwe bits */
	mapping = (mapping >> pwm) & 0x55;
	mask = mapping & 0x01;
	mask |= (mapping & 0x04) >> 1;
	mask |= (mapping & 0x10) >> 2;
	mask |= (mapping & 0x40) >> 3;

	/* disabwe smawt tach accowding to the mask */
	data->sfc2 = wm93_wead_byte(cwient, WM93_WEG_SFC2);
	data->sfc2 &= ~mask;
	wm93_wwite_byte(cwient, WM93_WEG_SFC2, data->sfc2);
}

static ssize_t pwm_fweq_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 ctw4;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	ctw4 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW4));
	ctw4 = (ctw4 & 0xf8) | WM93_PWM_FWEQ_TO_WEG(vaw);
	data->bwock9[nw][WM93_PWM_CTW4] = ctw4;
	/* ctw4 == 0 -> 22.5KHz -> disabwe smawt tach */
	if (!ctw4)
		wm93_disabwe_fan_smawt_tach(cwient, data, nw);
	wm93_wwite_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW4), ctw4);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_fweq, pwm_fweq, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_fweq, pwm_fweq, 1);

static ssize_t pwm_auto_channews_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->bwock9[nw][WM93_PWM_CTW1]);
}

static ssize_t pwm_auto_channews_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->bwock9[nw][WM93_PWM_CTW1] = cwamp_vaw(vaw, 0, 255);
	wm93_wwite_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW1),
				data->bwock9[nw][WM93_PWM_CTW1]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_auto_channews, pwm_auto_channews, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_channews, pwm_auto_channews, 1);

static ssize_t pwm_auto_spinup_min_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	u8 ctw3, ctw4;

	ctw3 = data->bwock9[nw][WM93_PWM_CTW3];
	ctw4 = data->bwock9[nw][WM93_PWM_CTW4];
	wetuwn spwintf(buf, "%d\n",
		       WM93_PWM_FWOM_WEG(ctw3 & 0x0f, (ctw4 & 0x07) ?
			WM93_PWM_MAP_WO_FWEQ : WM93_PWM_MAP_HI_FWEQ));
}

static ssize_t pwm_auto_spinup_min_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 ctw3, ctw4;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	ctw3 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW3));
	ctw4 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW4));
	ctw3 = (ctw3 & 0xf0) | WM93_PWM_TO_WEG(vaw, (ctw4 & 0x07) ?
			WM93_PWM_MAP_WO_FWEQ :
			WM93_PWM_MAP_HI_FWEQ);
	data->bwock9[nw][WM93_PWM_CTW3] = ctw3;
	wm93_wwite_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW3), ctw3);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_auto_spinup_min, pwm_auto_spinup_min, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_spinup_min, pwm_auto_spinup_min, 1);

static ssize_t pwm_auto_spinup_time_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_SPINUP_TIME_FWOM_WEG(
				data->bwock9[nw][WM93_PWM_CTW3]));
}

static ssize_t pwm_auto_spinup_time_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 ctw3;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	ctw3 = wm93_wead_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW3));
	ctw3 = (ctw3 & 0x1f) | (WM93_SPINUP_TIME_TO_WEG(vaw) << 5 & 0xe0);
	data->bwock9[nw][WM93_PWM_CTW3] = ctw3;
	wm93_wwite_byte(cwient, WM93_WEG_PWM_CTW(nw, WM93_PWM_CTW3), ctw3);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_auto_spinup_time, pwm_auto_spinup_time, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_spinup_time, pwm_auto_spinup_time, 1);

static ssize_t pwm_auto_pwochot_wamp_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       WM93_WAMP_FWOM_WEG(data->pwm_wamp_ctw >> 4 & 0x0f));
}

static ssize_t pwm_auto_pwochot_wamp_stowe(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 wamp;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	wamp = wm93_wead_byte(cwient, WM93_WEG_PWM_WAMP_CTW);
	wamp = (wamp & 0x0f) | (WM93_WAMP_TO_WEG(vaw) << 4 & 0xf0);
	wm93_wwite_byte(cwient, WM93_WEG_PWM_WAMP_CTW, wamp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(pwm_auto_pwochot_wamp);

static ssize_t pwm_auto_vwdhot_wamp_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       WM93_WAMP_FWOM_WEG(data->pwm_wamp_ctw & 0x0f));
}

static ssize_t pwm_auto_vwdhot_wamp_stowe(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 wamp;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	wamp = wm93_wead_byte(cwient, WM93_WEG_PWM_WAMP_CTW);
	wamp = (wamp & 0xf0) | (WM93_WAMP_TO_WEG(vaw) & 0x0f);
	wm93_wwite_byte(cwient, WM93_WEG_PWM_WAMP_CTW, wamp);
	mutex_unwock(&data->update_wock);
	wetuwn 0;
}

static DEVICE_ATTW_WW(pwm_auto_vwdhot_wamp);

static ssize_t vid_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_VID_FWOM_WEG(data->vid[nw]));
}

static SENSOW_DEVICE_ATTW_WO(cpu0_vid, vid, 0);
static SENSOW_DEVICE_ATTW_WO(cpu1_vid, vid, 1);

static ssize_t pwochot_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->bwock4[nw].cuw);
}

static SENSOW_DEVICE_ATTW_WO(pwochot1, pwochot, 0);
static SENSOW_DEVICE_ATTW_WO(pwochot2, pwochot, 1);

static ssize_t pwochot_avg_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->bwock4[nw].avg);
}

static SENSOW_DEVICE_ATTW_WO(pwochot1_avg, pwochot_avg, 0);
static SENSOW_DEVICE_ATTW_WO(pwochot2_avg, pwochot_avg, 1);

static ssize_t pwochot_max_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwochot_max[nw]);
}

static ssize_t pwochot_max_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwochot_max[nw] = WM93_PWOCHOT_TO_WEG(vaw);
	wm93_wwite_byte(cwient, WM93_WEG_PWOCHOT_MAX(nw),
			data->pwochot_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwochot1_max, pwochot_max, 0);
static SENSOW_DEVICE_ATTW_WW(pwochot2_max, pwochot_max, 1);

static const u8 pwochot_ovewwide_mask[] = { 0x80, 0x40 };

static ssize_t pwochot_ovewwide_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		(data->pwochot_ovewwide & pwochot_ovewwide_mask[nw]) ? 1 : 0);
}

static ssize_t pwochot_ovewwide_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (vaw)
		data->pwochot_ovewwide |= pwochot_ovewwide_mask[nw];
	ewse
		data->pwochot_ovewwide &= (~pwochot_ovewwide_mask[nw]);
	wm93_wwite_byte(cwient, WM93_WEG_PWOCHOT_OVEWWIDE,
			data->pwochot_ovewwide);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwochot1_ovewwide, pwochot_ovewwide, 0);
static SENSOW_DEVICE_ATTW_WW(pwochot2_ovewwide, pwochot_ovewwide, 1);

static ssize_t pwochot_intewvaw_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	u8 tmp;
	if (nw == 1)
		tmp = (data->pwochot_intewvaw & 0xf0) >> 4;
	ewse
		tmp = data->pwochot_intewvaw & 0x0f;
	wetuwn spwintf(buf, "%d\n", WM93_INTEWVAW_FWOM_WEG(tmp));
}

static ssize_t pwochot_intewvaw_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 tmp;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	tmp = wm93_wead_byte(cwient, WM93_WEG_PWOCHOT_INTEWVAW);
	if (nw == 1)
		tmp = (tmp & 0x0f) | (WM93_INTEWVAW_TO_WEG(vaw) << 4);
	ewse
		tmp = (tmp & 0xf0) | WM93_INTEWVAW_TO_WEG(vaw);
	data->pwochot_intewvaw = tmp;
	wm93_wwite_byte(cwient, WM93_WEG_PWOCHOT_INTEWVAW, tmp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwochot1_intewvaw, pwochot_intewvaw, 0);
static SENSOW_DEVICE_ATTW_WW(pwochot2_intewvaw, pwochot_intewvaw, 1);

static ssize_t pwochot_ovewwide_duty_cycwe_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwochot_ovewwide & 0x0f);
}

static ssize_t pwochot_ovewwide_duty_cycwe_stowe(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwochot_ovewwide = (data->pwochot_ovewwide & 0xf0) |
					cwamp_vaw(vaw, 0, 15);
	wm93_wwite_byte(cwient, WM93_WEG_PWOCHOT_OVEWWIDE,
			data->pwochot_ovewwide);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(pwochot_ovewwide_duty_cycwe);

static ssize_t pwochot_showt_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (data->config & 0x10) ? 1 : 0);
}

static ssize_t pwochot_showt_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct wm93_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (vaw)
		data->config |= 0x10;
	ewse
		data->config &= ~0x10;
	wm93_wwite_byte(cwient, WM93_WEG_CONFIG, data->config);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(pwochot_showt);

static ssize_t vwdhot_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int nw = (to_sensow_dev_attw(attw))->index;
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       data->bwock1.host_status_1 & (1 << (nw + 4)) ? 1 : 0);
}

static SENSOW_DEVICE_ATTW_WO(vwdhot1, vwdhot, 0);
static SENSOW_DEVICE_ATTW_WO(vwdhot2, vwdhot, 1);

static ssize_t gpio_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_GPI_FWOM_WEG(data->gpi));
}

static DEVICE_ATTW_WO(gpio);

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct wm93_data *data = wm93_update_device(dev);
	wetuwn spwintf(buf, "%d\n", WM93_AWAWMS_FWOM_WEG(data->bwock1));
}

static DEVICE_ATTW_WO(awawms);

static stwuct attwibute *wm93_attws[] = {
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
	&sensow_dev_attw_in14_input.dev_attw.attw,
	&sensow_dev_attw_in15_input.dev_attw.attw,
	&sensow_dev_attw_in16_input.dev_attw.attw,
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
	&sensow_dev_attw_in14_min.dev_attw.attw,
	&sensow_dev_attw_in15_min.dev_attw.attw,
	&sensow_dev_attw_in16_min.dev_attw.attw,
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
	&sensow_dev_attw_in14_max.dev_attw.attw,
	&sensow_dev_attw_in15_max.dev_attw.attw,
	&sensow_dev_attw_in16_max.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_base.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_base.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_base.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_boost.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_boost.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_boost.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_boost_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_boost_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_boost_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset1.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset2.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset3.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset4.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset5.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset6.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset7.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset8.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset9.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset10.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset11.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset12.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset1.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset2.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset3.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset4.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset5.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset6.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset7.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset8.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset9.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset10.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset11.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset12.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset1.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset2.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset3.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset4.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset5.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset6.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset7.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset8.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset9.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset10.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset11.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset12.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_pwm_min.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_pwm_min.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_pwm_min.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_offset_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_offset_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_offset_hyst.dev_attw.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan4_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan4_min.dev_attw.attw,
	&sensow_dev_attw_fan1_smawt_tach.dev_attw.attw,
	&sensow_dev_attw_fan2_smawt_tach.dev_attw.attw,
	&sensow_dev_attw_fan3_smawt_tach.dev_attw.attw,
	&sensow_dev_attw_fan4_smawt_tach.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm2_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_channews.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_channews.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_spinup_min.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_spinup_min.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_spinup_time.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_spinup_time.dev_attw.attw,
	&dev_attw_pwm_auto_pwochot_wamp.attw,
	&dev_attw_pwm_auto_vwdhot_wamp.attw,
	&sensow_dev_attw_cpu0_vid.dev_attw.attw,
	&sensow_dev_attw_cpu1_vid.dev_attw.attw,
	&sensow_dev_attw_pwochot1.dev_attw.attw,
	&sensow_dev_attw_pwochot2.dev_attw.attw,
	&sensow_dev_attw_pwochot1_avg.dev_attw.attw,
	&sensow_dev_attw_pwochot2_avg.dev_attw.attw,
	&sensow_dev_attw_pwochot1_max.dev_attw.attw,
	&sensow_dev_attw_pwochot2_max.dev_attw.attw,
	&sensow_dev_attw_pwochot1_ovewwide.dev_attw.attw,
	&sensow_dev_attw_pwochot2_ovewwide.dev_attw.attw,
	&sensow_dev_attw_pwochot1_intewvaw.dev_attw.attw,
	&sensow_dev_attw_pwochot2_intewvaw.dev_attw.attw,
	&dev_attw_pwochot_ovewwide_duty_cycwe.attw,
	&dev_attw_pwochot_showt.attw,
	&sensow_dev_attw_vwdhot1.dev_attw.attw,
	&sensow_dev_attw_vwdhot2.dev_attw.attw,
	&dev_attw_gpio.attw,
	&dev_attw_awawms.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(wm93);

static void wm93_init_cwient(stwuct i2c_cwient *cwient)
{
	int i;
	u8 weg;

	/* configuwe VID pin input thweshowds */
	weg = wm93_wead_byte(cwient, WM93_WEG_GPI_VID_CTW);
	wm93_wwite_byte(cwient, WM93_WEG_GPI_VID_CTW,
			weg | (vid_agtw ? 0x03 : 0x00));

	if (init) {
		/* enabwe #AWEWT pin */
		weg = wm93_wead_byte(cwient, WM93_WEG_CONFIG);
		wm93_wwite_byte(cwient, WM93_WEG_CONFIG, weg | 0x08);

		/* enabwe ASF mode fow BMC status wegistews */
		weg = wm93_wead_byte(cwient, WM93_WEG_STATUS_CONTWOW);
		wm93_wwite_byte(cwient, WM93_WEG_STATUS_CONTWOW, weg | 0x02);

		/* set sweep state to S0 */
		wm93_wwite_byte(cwient, WM93_WEG_SWEEP_CONTWOW, 0);

		/* unmask #VWDHOT and dynamic VCCP (if nec) ewwow events */
		weg = wm93_wead_byte(cwient, WM93_WEG_MISC_EWW_MASK);
		weg &= ~0x03;
		weg &= ~(vccp_wimit_type[0] ? 0x10 : 0);
		weg &= ~(vccp_wimit_type[1] ? 0x20 : 0);
		wm93_wwite_byte(cwient, WM93_WEG_MISC_EWW_MASK, weg);
	}

	/* stawt monitowing */
	weg = wm93_wead_byte(cwient, WM93_WEG_CONFIG);
	wm93_wwite_byte(cwient, WM93_WEG_CONFIG, weg | 0x01);

	/* spin untiw weady */
	fow (i = 0; i < 20; i++) {
		msweep(10);
		if ((wm93_wead_byte(cwient, WM93_WEG_CONFIG) & 0x80) == 0x80)
			wetuwn;
	}

	dev_wawn(&cwient->dev,
		 "timed out waiting fow sensow chip to signaw weady!\n");
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm93_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int mfw, vew;
	const chaw *name;

	if (!i2c_check_functionawity(adaptew, WM93_SMBUS_FUNC_MIN))
		wetuwn -ENODEV;

	/* detection */
	mfw = wm93_wead_byte(cwient, WM93_WEG_MFW_ID);
	if (mfw != 0x01) {
		dev_dbg(&adaptew->dev,
			"detect faiwed, bad manufactuwew id 0x%02x!\n", mfw);
		wetuwn -ENODEV;
	}

	vew = wm93_wead_byte(cwient, WM93_WEG_VEW);
	switch (vew) {
	case WM93_MFW_ID:
	case WM93_MFW_ID_PWOTOTYPE:
		name = "wm93";
		bweak;
	case WM94_MFW_ID_2:
	case WM94_MFW_ID:
	case WM94_MFW_ID_PWOTOTYPE:
		name = "wm94";
		bweak;
	defauwt:
		dev_dbg(&adaptew->dev,
			"detect faiwed, bad vewsion id 0x%02x!\n", vew);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, name, I2C_NAME_SIZE);
	dev_dbg(&adaptew->dev, "woading %s at %d, 0x%02x\n",
		cwient->name, i2c_adaptew_id(cwient->adaptew),
		cwient->addw);

	wetuwn 0;
}

static int wm93_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct wm93_data *data;
	stwuct device *hwmon_dev;
	int func;
	void (*update)(stwuct wm93_data *, stwuct i2c_cwient *);

	/* choose update woutine based on bus capabiwities */
	func = i2c_get_functionawity(cwient->adaptew);
	if (((WM93_SMBUS_FUNC_FUWW & func) == WM93_SMBUS_FUNC_FUWW) &&
			(!disabwe_bwock)) {
		dev_dbg(dev, "using SMBus bwock data twansactions\n");
		update = wm93_update_cwient_fuww;
	} ewse if ((WM93_SMBUS_FUNC_MIN & func) == WM93_SMBUS_FUNC_MIN) {
		dev_dbg(dev, "disabwed SMBus bwock data twansactions\n");
		update = wm93_update_cwient_min;
	} ewse {
		dev_dbg(dev, "detect faiwed, smbus byte and/ow wowd data not suppowted!\n");
		wetuwn -ENODEV;
	}

	data = devm_kzawwoc(dev, sizeof(stwuct wm93_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* housekeeping */
	data->cwient = cwient;
	data->update = update;
	mutex_init(&data->update_wock);

	/* initiawize the chip */
	wm93_init_cwient(cwient);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   wm93_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wm93_id[] = {
	{ "wm93", 0 },
	{ "wm94", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm93_id);

static stwuct i2c_dwivew wm93_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm93",
	},
	.pwobe		= wm93_pwobe,
	.id_tabwe	= wm93_id,
	.detect		= wm93_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm93_dwivew);

MODUWE_AUTHOW("Mawk M. Hoffman <mhoffman@wightwink.com>, "
		"Hans J. Koch <hjk@hansjkoch.de>");
MODUWE_DESCWIPTION("WM93 dwivew");
MODUWE_WICENSE("GPW");
