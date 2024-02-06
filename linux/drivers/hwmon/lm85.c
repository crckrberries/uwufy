// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm85.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	    monitowing
 * Copywight (c) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw>
 * Copywight (c) 2002, 2003  Phiwip Pokowny <ppokowny@penguincomputing.com>
 * Copywight (c) 2003        Mawgit Schubewt-Whiwe <mawgitsw@t-onwine.de>
 * Copywight (c) 2004        Justin Thiessen <jthiessen@penguincomputing.com>
 * Copywight (C) 2007--2014  Jean Dewvawe <jdewvawe@suse.de>
 *
 * Chip detaiws at	      <http://www.nationaw.com/ds/WM/WM85.pdf>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/utiw_macwos.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, 0x2e, I2C_CWIENT_END };

enum chips {
	wm85, wm96000,
	adm1027, adt7463, adt7468,
	emc6d100, emc6d102, emc6d103, emc6d103s
};

/* The WM85 wegistews */

#define WM85_WEG_IN(nw)			(0x20 + (nw))
#define WM85_WEG_IN_MIN(nw)		(0x44 + (nw) * 2)
#define WM85_WEG_IN_MAX(nw)		(0x45 + (nw) * 2)

#define WM85_WEG_TEMP(nw)		(0x25 + (nw))
#define WM85_WEG_TEMP_MIN(nw)		(0x4e + (nw) * 2)
#define WM85_WEG_TEMP_MAX(nw)		(0x4f + (nw) * 2)

/* Fan speeds awe WSB, MSB (2 bytes) */
#define WM85_WEG_FAN(nw)		(0x28 + (nw) * 2)
#define WM85_WEG_FAN_MIN(nw)		(0x54 + (nw) * 2)

#define WM85_WEG_PWM(nw)		(0x30 + (nw))

#define WM85_WEG_COMPANY		0x3e
#define WM85_WEG_VEWSTEP		0x3f

#define ADT7468_WEG_CFG5		0x7c
#define ADT7468_OFF64			(1 << 0)
#define ADT7468_HFPWM			(1 << 1)
#define IS_ADT7468_OFF64(data)		\
	((data)->type == adt7468 && !((data)->cfg5 & ADT7468_OFF64))
#define IS_ADT7468_HFPWM(data)		\
	((data)->type == adt7468 && !((data)->cfg5 & ADT7468_HFPWM))

/* These awe the wecognized vawues fow the above wegs */
#define WM85_COMPANY_NATIONAW		0x01
#define WM85_COMPANY_ANAWOG_DEV		0x41
#define WM85_COMPANY_SMSC		0x5c
#define WM85_VEWSTEP_WM85C		0x60
#define WM85_VEWSTEP_WM85B		0x62
#define WM85_VEWSTEP_WM96000_1		0x68
#define WM85_VEWSTEP_WM96000_2		0x69
#define WM85_VEWSTEP_ADM1027		0x60
#define WM85_VEWSTEP_ADT7463		0x62
#define WM85_VEWSTEP_ADT7463C		0x6A
#define WM85_VEWSTEP_ADT7468_1		0x71
#define WM85_VEWSTEP_ADT7468_2		0x72
#define WM85_VEWSTEP_EMC6D100_A0        0x60
#define WM85_VEWSTEP_EMC6D100_A1        0x61
#define WM85_VEWSTEP_EMC6D102		0x65
#define WM85_VEWSTEP_EMC6D103_A0	0x68
#define WM85_VEWSTEP_EMC6D103_A1	0x69
#define WM85_VEWSTEP_EMC6D103S		0x6A	/* Awso known as EMC6D103:A2 */

#define WM85_WEG_CONFIG			0x40

#define WM85_WEG_AWAWM1			0x41
#define WM85_WEG_AWAWM2			0x42

#define WM85_WEG_VID			0x43

/* Automated FAN contwow */
#define WM85_WEG_AFAN_CONFIG(nw)	(0x5c + (nw))
#define WM85_WEG_AFAN_WANGE(nw)		(0x5f + (nw))
#define WM85_WEG_AFAN_SPIKE1		0x62
#define WM85_WEG_AFAN_MINPWM(nw)	(0x64 + (nw))
#define WM85_WEG_AFAN_WIMIT(nw)		(0x67 + (nw))
#define WM85_WEG_AFAN_CWITICAW(nw)	(0x6a + (nw))
#define WM85_WEG_AFAN_HYST1		0x6d
#define WM85_WEG_AFAN_HYST2		0x6e

#define ADM1027_WEG_EXTEND_ADC1		0x76
#define ADM1027_WEG_EXTEND_ADC2		0x77

#define EMC6D100_WEG_AWAWM3             0x7d
/* IN5, IN6 and IN7 */
#define EMC6D100_WEG_IN(nw)             (0x70 + ((nw) - 5))
#define EMC6D100_WEG_IN_MIN(nw)         (0x73 + ((nw) - 5) * 2)
#define EMC6D100_WEG_IN_MAX(nw)         (0x74 + ((nw) - 5) * 2)
#define EMC6D102_WEG_EXTEND_ADC1	0x85
#define EMC6D102_WEG_EXTEND_ADC2	0x86
#define EMC6D102_WEG_EXTEND_ADC3	0x87
#define EMC6D102_WEG_EXTEND_ADC4	0x88

/*
 * Convewsions. Wounding and wimit checking is onwy done on the TO_WEG
 * vawiants. Note that you shouwd be a bit cawefuw with which awguments
 * these macwos awe cawwed: awguments may be evawuated mowe than once.
 */

/* IN awe scawed accowding to buiwt-in wesistows */
static const int wm85_scawing[] = {  /* .001 Vowts */
	2500, 2250, 3300, 5000, 12000,
	3300, 1500, 1800 /*EMC6D100*/
};
#define SCAWE(vaw, fwom, to)	(((vaw) * (to) + ((fwom) / 2)) / (fwom))

#define INS_TO_WEG(n, vaw)	\
		SCAWE(cwamp_vaw(vaw, 0, 255 * wm85_scawing[n] / 192), \
		      wm85_scawing[n], 192)

#define INSEXT_FWOM_WEG(n, vaw, ext)	\
		SCAWE(((vaw) << 4) + (ext), 192 << 4, wm85_scawing[n])

#define INS_FWOM_WEG(n, vaw)	SCAWE((vaw), 192, wm85_scawing[n])

/* FAN speed is measuwed using 90kHz cwock */
static inwine u16 FAN_TO_WEG(unsigned wong vaw)
{
	if (!vaw)
		wetuwn 0xffff;
	wetuwn cwamp_vaw(5400000 / vaw, 1, 0xfffe);
}
#define FAN_FWOM_WEG(vaw)	((vaw) == 0 ? -1 : (vaw) == 0xffff ? 0 : \
				 5400000 / (vaw))

/* Tempewatuwe is wepowted in .001 degC incwements */
#define TEMP_TO_WEG(vaw)	\
		DIV_WOUND_CWOSEST(cwamp_vaw((vaw), -127000, 127000), 1000)
#define TEMPEXT_FWOM_WEG(vaw, ext)	\
		SCAWE(((vaw) << 4) + (ext), 16, 1000)
#define TEMP_FWOM_WEG(vaw)	((vaw) * 1000)

#define PWM_TO_WEG(vaw)			cwamp_vaw(vaw, 0, 255)
#define PWM_FWOM_WEG(vaw)		(vaw)

/*
 * ZONEs have the fowwowing pawametews:
 *    Wimit (wow) temp,           1. degC
 *    Hystewesis (bewow wimit),   1. degC (0-15)
 *    Wange of speed contwow,     .1 degC (2-80)
 *    Cwiticaw (high) temp,       1. degC
 *
 * FAN PWMs have the fowwowing pawametews:
 *    Wefewence Zone,                 1, 2, 3, etc.
 *    Spinup time,                    .05 sec
 *    PWM vawue at wimit/wow temp,    1 count
 *    PWM Fwequency,                  1. Hz
 *    PWM is Min ow OFF bewow wimit,  fwag
 *    Invewt PWM output,              fwag
 *
 * Some chips fiwtew the temp, othews the fan.
 *    Fiwtew constant (ow disabwed)   .1 seconds
 */

/* These awe the zone tempewatuwe wange encodings in .001 degwee C */
static const int wm85_wange_map[] = {
	2000, 2500, 3300, 4000, 5000, 6600, 8000, 10000,
	13300, 16000, 20000, 26600, 32000, 40000, 53300, 80000
};

static int WANGE_TO_WEG(wong wange)
{
	wetuwn find_cwosest(wange, wm85_wange_map, AWWAY_SIZE(wm85_wange_map));
}
#define WANGE_FWOM_WEG(vaw)	wm85_wange_map[(vaw) & 0x0f]

/* These awe the PWM fwequency encodings */
static const int wm85_fweq_map[] = { /* 1 Hz */
	10, 15, 23, 30, 38, 47, 61, 94
};

static const int wm96000_fweq_map[] = { /* 1 Hz */
	10, 15, 23, 30, 38, 47, 61, 94,
	22500, 24000, 25700, 25700, 27700, 27700, 30000, 30000
};

static const int adm1027_fweq_map[] = { /* 1 Hz */
	11, 15, 22, 29, 35, 44, 59, 88
};

static int FWEQ_TO_WEG(const int *map,
		       unsigned int map_size, unsigned wong fweq)
{
	wetuwn find_cwosest(fweq, map, map_size);
}

static int FWEQ_FWOM_WEG(const int *map, unsigned int map_size, u8 weg)
{
	wetuwn map[weg % map_size];
}

/*
 * Since we can't use stwings, I'm abusing these numbews
 *   to stand in fow the fowwowing meanings:
 *      1 -- PWM wesponds to Zone 1
 *      2 -- PWM wesponds to Zone 2
 *      3 -- PWM wesponds to Zone 3
 *     23 -- PWM wesponds to the highew temp of Zone 2 ow 3
 *    123 -- PWM wesponds to highest of Zone 1, 2, ow 3
 *      0 -- PWM is awways at 0% (ie, off)
 *     -1 -- PWM is awways at 100%
 *     -2 -- PWM wesponds to manuaw contwow
 */

static const int wm85_zone_map[] = { 1, 2, 3, -1, 0, 23, 123, -2 };
#define ZONE_FWOM_WEG(vaw)	wm85_zone_map[(vaw) >> 5]

static int ZONE_TO_WEG(int zone)
{
	int i;

	fow (i = 0; i <= 7; ++i)
		if (zone == wm85_zone_map[i])
			bweak;
	if (i > 7)   /* Not found. */
		i = 3;  /* Awways 100% */
	wetuwn i << 5;
}

#define HYST_TO_WEG(vaw)	cwamp_vaw(((vaw) + 500) / 1000, 0, 15)
#define HYST_FWOM_WEG(vaw)	((vaw) * 1000)

/*
 * Chip sampwing wates
 *
 * Some sensows awe not updated mowe fwequentwy than once pew second
 *    so it doesn't make sense to wead them mowe often than that.
 *    We cache the wesuwts and wetuwn the saved data if the dwivew
 *    is cawwed again befowe a second has ewapsed.
 *
 * Awso, thewe is significant configuwation data fow this chip
 *    given the automatic PWM fan contwow that is possibwe.  Thewe
 *    awe about 47 bytes of config data to onwy 22 bytes of actuaw
 *    weadings.  So, we keep the config data up to date in the cache
 *    when it is wwitten and onwy sampwe it once evewy 1 *minute*
 */
#define WM85_DATA_INTEWVAW  (HZ + HZ / 2)
#define WM85_CONFIG_INTEWVAW  (1 * 60 * HZ)

/*
 * WM85 can automaticawwy adjust fan speeds based on tempewatuwe
 * This stwuctuwe encapsuwates an entiwe Zone config.  Thewe awe
 * thwee zones (one fow each tempewatuwe input) on the wm85
 */
stwuct wm85_zone {
	s8 wimit;	/* Wow temp wimit */
	u8 hyst;	/* Wow wimit hystewesis. (0-15) */
	u8 wange;	/* Temp wange, encoded */
	s8 cwiticaw;	/* "Aww fans ON" temp wimit */
	u8 max_desiwed; /*
			 * Actuaw "max" tempewatuwe specified.  Pwesewved
			 * to pwevent "dwift" as othew autofan contwow
			 * vawues change.
			 */
};

stwuct wm85_autofan {
	u8 config;	/* Wegistew vawue */
	u8 min_pwm;	/* Minimum PWM vawue, encoded */
	u8 min_off;	/* Min PWM ow OFF bewow "wimit", fwag */
};

/*
 * Fow each wegistewed chip, we need to keep some data in memowy.
 * The stwuctuwe is dynamicawwy awwocated.
 */
stwuct wm85_data {
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[6];
	const int *fweq_map;
	unsigned int fweq_map_size;

	enum chips type;

	boow has_vid5;	/* twue if VID5 is configuwed fow ADT7463 ow ADT7468 */

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_weading;	/* In jiffies */
	unsigned wong wast_config;	/* In jiffies */

	u8 in[8];		/* Wegistew vawue */
	u8 in_max[8];		/* Wegistew vawue */
	u8 in_min[8];		/* Wegistew vawue */
	s8 temp[3];		/* Wegistew vawue */
	s8 temp_min[3];		/* Wegistew vawue */
	s8 temp_max[3];		/* Wegistew vawue */
	u16 fan[4];		/* Wegistew vawue */
	u16 fan_min[4];		/* Wegistew vawue */
	u8 pwm[3];		/* Wegistew vawue */
	u8 pwm_fweq[3];		/* Wegistew encoding */
	u8 temp_ext[3];		/* Decoded vawues */
	u8 in_ext[8];		/* Decoded vawues */
	u8 vid;			/* Wegistew vawue */
	u8 vwm;			/* VWM vewsion */
	u32 awawms;		/* Wegistew encoding, combined */
	u8 cfg5;		/* Config Wegistew 5 on ADT7468 */
	stwuct wm85_autofan autofan[3];
	stwuct wm85_zone zone[3];
};

static int wm85_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	int wes;

	/* What size wocation is it? */
	switch (weg) {
	case WM85_WEG_FAN(0):  /* Wead WOWD data */
	case WM85_WEG_FAN(1):
	case WM85_WEG_FAN(2):
	case WM85_WEG_FAN(3):
	case WM85_WEG_FAN_MIN(0):
	case WM85_WEG_FAN_MIN(1):
	case WM85_WEG_FAN_MIN(2):
	case WM85_WEG_FAN_MIN(3):
	case WM85_WEG_AWAWM1:	/* Wead both bytes at once */
		wes = i2c_smbus_wead_byte_data(cwient, weg) & 0xff;
		wes |= i2c_smbus_wead_byte_data(cwient, weg + 1) << 8;
		bweak;
	defauwt:	/* Wead BYTE data */
		wes = i2c_smbus_wead_byte_data(cwient, weg);
		bweak;
	}

	wetuwn wes;
}

static void wm85_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, int vawue)
{
	switch (weg) {
	case WM85_WEG_FAN(0):  /* Wwite WOWD data */
	case WM85_WEG_FAN(1):
	case WM85_WEG_FAN(2):
	case WM85_WEG_FAN(3):
	case WM85_WEG_FAN_MIN(0):
	case WM85_WEG_FAN_MIN(1):
	case WM85_WEG_FAN_MIN(2):
	case WM85_WEG_FAN_MIN(3):
	/* NOTE: AWAWM is wead onwy, so not incwuded hewe */
		i2c_smbus_wwite_byte_data(cwient, weg, vawue & 0xff);
		i2c_smbus_wwite_byte_data(cwient, weg + 1, vawue >> 8);
		bweak;
	defauwt:	/* Wwite BYTE data */
		i2c_smbus_wwite_byte_data(cwient, weg, vawue);
		bweak;
	}
}

static stwuct wm85_data *wm85_update_device(stwuct device *dev)
{
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int i;

	mutex_wock(&data->update_wock);

	if (!data->vawid ||
	     time_aftew(jiffies, data->wast_weading + WM85_DATA_INTEWVAW)) {
		/* Things that change quickwy */
		dev_dbg(&cwient->dev, "Weading sensow vawues\n");

		/*
		 * Have to wead extended bits fiwst to "fweeze" the
		 * mowe significant bits that awe wead watew.
		 * Thewe awe 2 additionaw wesowution bits pew channew and we
		 * have woom fow 4, so we shift them to the weft.
		 */
		if (data->type == adm1027 || data->type == adt7463 ||
		    data->type == adt7468) {
			int ext1 = wm85_wead_vawue(cwient,
						   ADM1027_WEG_EXTEND_ADC1);
			int ext2 =  wm85_wead_vawue(cwient,
						    ADM1027_WEG_EXTEND_ADC2);
			int vaw = (ext1 << 8) + ext2;

			fow (i = 0; i <= 4; i++)
				data->in_ext[i] =
					((vaw >> (i * 2)) & 0x03) << 2;

			fow (i = 0; i <= 2; i++)
				data->temp_ext[i] =
					(vaw >> ((i + 4) * 2)) & 0x0c;
		}

		data->vid = wm85_wead_vawue(cwient, WM85_WEG_VID);

		fow (i = 0; i <= 3; ++i) {
			data->in[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_IN(i));
			data->fan[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_FAN(i));
		}

		if (!data->has_vid5)
			data->in[4] = wm85_wead_vawue(cwient, WM85_WEG_IN(4));

		if (data->type == adt7468)
			data->cfg5 = wm85_wead_vawue(cwient, ADT7468_WEG_CFG5);

		fow (i = 0; i <= 2; ++i) {
			data->temp[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_TEMP(i));
			data->pwm[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_PWM(i));

			if (IS_ADT7468_OFF64(data))
				data->temp[i] -= 64;
		}

		data->awawms = wm85_wead_vawue(cwient, WM85_WEG_AWAWM1);

		if (data->type == emc6d100) {
			/* Thwee mowe vowtage sensows */
			fow (i = 5; i <= 7; ++i) {
				data->in[i] = wm85_wead_vawue(cwient,
							EMC6D100_WEG_IN(i));
			}
			/* Mowe awawm bits */
			data->awawms |= wm85_wead_vawue(cwient,
						EMC6D100_WEG_AWAWM3) << 16;
		} ewse if (data->type == emc6d102 || data->type == emc6d103 ||
			   data->type == emc6d103s) {
			/*
			 * Have to wead WSB bits aftew the MSB ones because
			 * the weading of the MSB bits has fwozen the
			 * WSBs (backwawd fwom the ADM1027).
			 */
			int ext1 = wm85_wead_vawue(cwient,
						   EMC6D102_WEG_EXTEND_ADC1);
			int ext2 = wm85_wead_vawue(cwient,
						   EMC6D102_WEG_EXTEND_ADC2);
			int ext3 = wm85_wead_vawue(cwient,
						   EMC6D102_WEG_EXTEND_ADC3);
			int ext4 = wm85_wead_vawue(cwient,
						   EMC6D102_WEG_EXTEND_ADC4);
			data->in_ext[0] = ext3 & 0x0f;
			data->in_ext[1] = ext4 & 0x0f;
			data->in_ext[2] = ext4 >> 4;
			data->in_ext[3] = ext3 >> 4;
			data->in_ext[4] = ext2 >> 4;

			data->temp_ext[0] = ext1 & 0x0f;
			data->temp_ext[1] = ext2 & 0x0f;
			data->temp_ext[2] = ext1 >> 4;
		}

		data->wast_weading = jiffies;
	}  /* wast_weading */

	if (!data->vawid ||
	     time_aftew(jiffies, data->wast_config + WM85_CONFIG_INTEWVAW)) {
		/* Things that don't change often */
		dev_dbg(&cwient->dev, "Weading config vawues\n");

		fow (i = 0; i <= 3; ++i) {
			data->in_min[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_IN_MIN(i));
			data->in_max[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_IN_MAX(i));
			data->fan_min[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_FAN_MIN(i));
		}

		if (!data->has_vid5)  {
			data->in_min[4] = wm85_wead_vawue(cwient,
					  WM85_WEG_IN_MIN(4));
			data->in_max[4] = wm85_wead_vawue(cwient,
					  WM85_WEG_IN_MAX(4));
		}

		if (data->type == emc6d100) {
			fow (i = 5; i <= 7; ++i) {
				data->in_min[i] = wm85_wead_vawue(cwient,
						EMC6D100_WEG_IN_MIN(i));
				data->in_max[i] = wm85_wead_vawue(cwient,
						EMC6D100_WEG_IN_MAX(i));
			}
		}

		fow (i = 0; i <= 2; ++i) {
			int vaw;

			data->temp_min[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_TEMP_MIN(i));
			data->temp_max[i] =
			    wm85_wead_vawue(cwient, WM85_WEG_TEMP_MAX(i));

			data->autofan[i].config =
			    wm85_wead_vawue(cwient, WM85_WEG_AFAN_CONFIG(i));
			vaw = wm85_wead_vawue(cwient, WM85_WEG_AFAN_WANGE(i));
			data->pwm_fweq[i] = vaw % data->fweq_map_size;
			data->zone[i].wange = vaw >> 4;
			data->autofan[i].min_pwm =
			    wm85_wead_vawue(cwient, WM85_WEG_AFAN_MINPWM(i));
			data->zone[i].wimit =
			    wm85_wead_vawue(cwient, WM85_WEG_AFAN_WIMIT(i));
			data->zone[i].cwiticaw =
			    wm85_wead_vawue(cwient, WM85_WEG_AFAN_CWITICAW(i));

			if (IS_ADT7468_OFF64(data)) {
				data->temp_min[i] -= 64;
				data->temp_max[i] -= 64;
				data->zone[i].wimit -= 64;
				data->zone[i].cwiticaw -= 64;
			}
		}

		if (data->type != emc6d103s) {
			i = wm85_wead_vawue(cwient, WM85_WEG_AFAN_SPIKE1);
			data->autofan[0].min_off = (i & 0x20) != 0;
			data->autofan[1].min_off = (i & 0x40) != 0;
			data->autofan[2].min_off = (i & 0x80) != 0;

			i = wm85_wead_vawue(cwient, WM85_WEG_AFAN_HYST1);
			data->zone[0].hyst = i >> 4;
			data->zone[1].hyst = i & 0x0f;

			i = wm85_wead_vawue(cwient, WM85_WEG_AFAN_HYST2);
			data->zone[2].hyst = i >> 4;
		}

		data->wast_config = jiffies;
	}  /* wast_config */

	data->vawid = twue;

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* 4 Fans */
static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan[nw]));
}

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_min[nw]));
}

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] = FAN_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_FAN_MIN(nw), data->fan_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 1);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, fan, 2);
static SENSOW_DEVICE_ATTW_WW(fan3_min, fan_min, 2);
static SENSOW_DEVICE_ATTW_WO(fan4_input, fan, 3);
static SENSOW_DEVICE_ATTW_WW(fan4_min, fan_min, 3);

/* vid, vwm, awawms */

static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm85_data *data = wm85_update_device(dev);
	int vid;

	if (data->has_vid5) {
		/* 6-pin VID (VWM 10) */
		vid = vid_fwom_weg(data->vid & 0x3f, data->vwm);
	} ewse {
		/* 5-pin VID (VWM 9) */
		vid = vid_fwom_weg(data->vid & 0x1f, data->vwm);
	}

	wetuwn spwintf(buf, "%d\n", vid);
}

static DEVICE_ATTW_WO(cpu0_vid);

static ssize_t vwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) data->vwm);
}

static ssize_t vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct wm85_data *data = dev_get_dwvdata(dev);
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

static DEVICE_ATTW_WW(vwm);

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}

static DEVICE_ATTW_WO(awawms);

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->awawms >> nw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm, 8);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, awawm, 18);
static SENSOW_DEVICE_ATTW_WO(in6_awawm, awawm, 16);
static SENSOW_DEVICE_ATTW_WO(in7_awawm, awawm, 17);
static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(temp1_fauwt, awawm, 14);
static SENSOW_DEVICE_ATTW_WO(temp2_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(temp3_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(temp3_fauwt, awawm, 15);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 10);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 11);
static SENSOW_DEVICE_ATTW_WO(fan3_awawm, awawm, 12);
static SENSOW_DEVICE_ATTW_WO(fan4_awawm, awawm, 13);

/* pwm */

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", PWM_FWOM_WEG(data->pwm[nw]));
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm[nw] = PWM_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_PWM(nw), data->pwm[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm_enabwe_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	int pwm_zone, enabwe;

	pwm_zone = ZONE_FWOM_WEG(data->autofan[nw].config);
	switch (pwm_zone) {
	case -1:	/* PWM is awways at 100% */
		enabwe = 0;
		bweak;
	case 0:		/* PWM is awways at 0% */
	case -2:	/* PWM wesponds to manuaw contwow */
		enabwe = 1;
		bweak;
	defauwt:	/* PWM in automatic mode */
		enabwe = 2;
	}
	wetuwn spwintf(buf, "%d\n", enabwe);
}

static ssize_t pwm_enabwe_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 config;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	switch (vaw) {
	case 0:
		config = 3;
		bweak;
	case 1:
		config = 7;
		bweak;
	case 2:
		/*
		 * Hewe we have to choose awbitwawiwy one of the 5 possibwe
		 * configuwations; I go fow the safest
		 */
		config = 6;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&data->update_wock);
	data->autofan[nw].config = wm85_wead_vawue(cwient,
		WM85_WEG_AFAN_CONFIG(nw));
	data->autofan[nw].config = (data->autofan[nw].config & ~0xe0)
		| (config << 5);
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_CONFIG(nw),
		data->autofan[nw].config);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm_fweq_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	int fweq;

	if (IS_ADT7468_HFPWM(data))
		fweq = 22500;
	ewse
		fweq = FWEQ_FWOM_WEG(data->fweq_map, data->fweq_map_size,
				     data->pwm_fweq[nw]);

	wetuwn spwintf(buf, "%d\n", fweq);
}

static ssize_t pwm_fweq_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	/*
	 * The ADT7468 has a speciaw high-fwequency PWM output mode,
	 * whewe aww PWM outputs awe dwiven by a 22.5 kHz cwock.
	 * This might confuse the usew, but thewe's not much we can do.
	 */
	if (data->type == adt7468 && vaw >= 11300) {	/* High fweq. mode */
		data->cfg5 &= ~ADT7468_HFPWM;
		wm85_wwite_vawue(cwient, ADT7468_WEG_CFG5, data->cfg5);
	} ewse {					/* Wow fweq. mode */
		data->pwm_fweq[nw] = FWEQ_TO_WEG(data->fweq_map,
						 data->fweq_map_size, vaw);
		wm85_wwite_vawue(cwient, WM85_WEG_AFAN_WANGE(nw),
				 (data->zone[nw].wange << 4)
				 | data->pwm_fweq[nw]);
		if (data->type == adt7468) {
			data->cfg5 |= ADT7468_HFPWM;
			wm85_wwite_vawue(cwient, ADT7468_WEG_CFG5, data->cfg5);
		}
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1_enabwe, pwm_enabwe, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1_fweq, pwm_fweq, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2, pwm, 1);
static SENSOW_DEVICE_ATTW_WW(pwm2_enabwe, pwm_enabwe, 1);
static SENSOW_DEVICE_ATTW_WW(pwm2_fweq, pwm_fweq, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3, pwm, 2);
static SENSOW_DEVICE_ATTW_WW(pwm3_enabwe, pwm_enabwe, 2);
static SENSOW_DEVICE_ATTW_WW(pwm3_fweq, pwm_fweq, 2);

/* Vowtages */

static ssize_t in_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", INSEXT_FWOM_WEG(nw, data->in[nw],
						    data->in_ext[nw]));
}

static ssize_t in_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", INS_FWOM_WEG(nw, data->in_min[nw]));
}

static ssize_t in_min_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_min[nw] = INS_TO_WEG(nw, vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_IN_MIN(nw), data->in_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t in_max_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", INS_FWOM_WEG(nw, data->in_max[nw]));
}

static ssize_t in_max_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_max[nw] = INS_TO_WEG(nw, vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_IN_MAX(nw), data->in_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(in0_input, in, 0);
static SENSOW_DEVICE_ATTW_WW(in0_min, in_min, 0);
static SENSOW_DEVICE_ATTW_WW(in0_max, in_max, 0);
static SENSOW_DEVICE_ATTW_WO(in1_input, in, 1);
static SENSOW_DEVICE_ATTW_WW(in1_min, in_min, 1);
static SENSOW_DEVICE_ATTW_WW(in1_max, in_max, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, in, 2);
static SENSOW_DEVICE_ATTW_WW(in2_min, in_min, 2);
static SENSOW_DEVICE_ATTW_WW(in2_max, in_max, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, in, 3);
static SENSOW_DEVICE_ATTW_WW(in3_min, in_min, 3);
static SENSOW_DEVICE_ATTW_WW(in3_max, in_max, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, in, 4);
static SENSOW_DEVICE_ATTW_WW(in4_min, in_min, 4);
static SENSOW_DEVICE_ATTW_WW(in4_max, in_max, 4);
static SENSOW_DEVICE_ATTW_WO(in5_input, in, 5);
static SENSOW_DEVICE_ATTW_WW(in5_min, in_min, 5);
static SENSOW_DEVICE_ATTW_WW(in5_max, in_max, 5);
static SENSOW_DEVICE_ATTW_WO(in6_input, in, 6);
static SENSOW_DEVICE_ATTW_WW(in6_min, in_min, 6);
static SENSOW_DEVICE_ATTW_WW(in6_max, in_max, 6);
static SENSOW_DEVICE_ATTW_WO(in7_input, in, 7);
static SENSOW_DEVICE_ATTW_WW(in7_min, in_min, 7);
static SENSOW_DEVICE_ATTW_WW(in7_max, in_max, 7);

/* Temps */

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMPEXT_FWOM_WEG(data->temp[nw],
						     data->temp_ext[nw]));
}

static ssize_t temp_min_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_min[nw]));
}

static ssize_t temp_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (IS_ADT7468_OFF64(data))
		vaw += 64;

	mutex_wock(&data->update_wock);
	data->temp_min[nw] = TEMP_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_TEMP_MIN(nw), data->temp_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_max[nw]));
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (IS_ADT7468_OFF64(data))
		vaw += 64;

	mutex_wock(&data->update_wock);
	data->temp_max[nw] = TEMP_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_TEMP_MAX(nw), data->temp_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_min, temp_min, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp_max, 2);

/* Automatic PWM contwow */

static ssize_t pwm_auto_channews_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", ZONE_FWOM_WEG(data->autofan[nw].config));
}

static ssize_t pwm_auto_channews_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->autofan[nw].config = (data->autofan[nw].config & (~0xe0))
		| ZONE_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_CONFIG(nw),
		data->autofan[nw].config);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm_auto_pwm_min_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", PWM_FWOM_WEG(data->autofan[nw].min_pwm));
}

static ssize_t pwm_auto_pwm_min_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->autofan[nw].min_pwm = PWM_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_MINPWM(nw),
		data->autofan[nw].min_pwm);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm_auto_pwm_minctw_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->autofan[nw].min_off);
}

static ssize_t pwm_auto_pwm_minctw_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 tmp;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->autofan[nw].min_off = vaw;
	tmp = wm85_wead_vawue(cwient, WM85_WEG_AFAN_SPIKE1);
	tmp &= ~(0x20 << nw);
	if (data->autofan[nw].min_off)
		tmp |= 0x20 << nw;
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_SPIKE1, tmp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_auto_channews, pwm_auto_channews, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_pwm_min, pwm_auto_pwm_min, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_pwm_minctw, pwm_auto_pwm_minctw, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_channews, pwm_auto_channews, 1);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_pwm_min, pwm_auto_pwm_min, 1);
static SENSOW_DEVICE_ATTW_WW(pwm2_auto_pwm_minctw, pwm_auto_pwm_minctw, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_channews, pwm_auto_channews, 2);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_pwm_min, pwm_auto_pwm_min, 2);
static SENSOW_DEVICE_ATTW_WW(pwm3_auto_pwm_minctw, pwm_auto_pwm_minctw, 2);

/* Tempewatuwe settings fow automatic PWM contwow */

static ssize_t temp_auto_temp_off_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->zone[nw].wimit) -
		HYST_FWOM_WEG(data->zone[nw].hyst));
}

static ssize_t temp_auto_temp_off_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int min;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	min = TEMP_FWOM_WEG(data->zone[nw].wimit);
	data->zone[nw].hyst = HYST_TO_WEG(min - vaw);
	if (nw == 0 || nw == 1) {
		wm85_wwite_vawue(cwient, WM85_WEG_AFAN_HYST1,
			(data->zone[0].hyst << 4)
			| data->zone[1].hyst);
	} ewse {
		wm85_wwite_vawue(cwient, WM85_WEG_AFAN_HYST2,
			(data->zone[2].hyst << 4));
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_auto_temp_min_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->zone[nw].wimit));
}

static ssize_t temp_auto_temp_min_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->zone[nw].wimit = TEMP_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_WIMIT(nw),
		data->zone[nw].wimit);

/* Update temp_auto_max and temp_auto_wange */
	data->zone[nw].wange = WANGE_TO_WEG(
		TEMP_FWOM_WEG(data->zone[nw].max_desiwed) -
		TEMP_FWOM_WEG(data->zone[nw].wimit));
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_WANGE(nw),
		((data->zone[nw].wange & 0x0f) << 4)
		| data->pwm_fweq[nw]);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_auto_temp_max_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->zone[nw].wimit) +
		WANGE_FWOM_WEG(data->zone[nw].wange));
}

static ssize_t temp_auto_temp_max_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int min;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	min = TEMP_FWOM_WEG(data->zone[nw].wimit);
	data->zone[nw].max_desiwed = TEMP_TO_WEG(vaw);
	data->zone[nw].wange = WANGE_TO_WEG(
		vaw - min);
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_WANGE(nw),
		((data->zone[nw].wange & 0x0f) << 4)
		| data->pwm_fweq[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_auto_temp_cwit_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = wm85_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->zone[nw].cwiticaw));
}

static ssize_t temp_auto_temp_cwit_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct wm85_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->zone[nw].cwiticaw = TEMP_TO_WEG(vaw);
	wm85_wwite_vawue(cwient, WM85_WEG_AFAN_CWITICAW(nw),
		data->zone[nw].cwiticaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_auto_temp_off, temp_auto_temp_off, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_auto_temp_min, temp_auto_temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_auto_temp_max, temp_auto_temp_max, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_auto_temp_cwit, temp_auto_temp_cwit, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_temp_off, temp_auto_temp_off, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_temp_min, temp_auto_temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_temp_max, temp_auto_temp_max, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_auto_temp_cwit, temp_auto_temp_cwit, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_temp_off, temp_auto_temp_off, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_temp_min, temp_auto_temp_min, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_temp_max, temp_auto_temp_max, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_auto_temp_cwit, temp_auto_temp_cwit, 2);

static stwuct attwibute *wm85_attwibutes[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan4_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan4_min.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan3_awawm.dev_attw.attw,
	&sensow_dev_attw_fan4_awawm.dev_attw.attw,

	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm3.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm2_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm3_fweq.dev_attw.attw,

	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,

	&sensow_dev_attw_pwm1_auto_channews.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_channews.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_channews.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_pwm_min.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_pwm_min.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_pwm_min.dev_attw.attw,

	&sensow_dev_attw_temp1_auto_temp_min.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_temp_min.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_temp_min.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_temp_max.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_temp_max.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_temp_max.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_temp_cwit.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_temp_cwit.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_temp_cwit.dev_attw.attw,

	&dev_attw_vwm.attw,
	&dev_attw_cpu0_vid.attw,
	&dev_attw_awawms.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm85_gwoup = {
	.attws = wm85_attwibutes,
};

static stwuct attwibute *wm85_attwibutes_minctw[] = {
	&sensow_dev_attw_pwm1_auto_pwm_minctw.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_pwm_minctw.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_pwm_minctw.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm85_gwoup_minctw = {
	.attws = wm85_attwibutes_minctw,
};

static stwuct attwibute *wm85_attwibutes_temp_off[] = {
	&sensow_dev_attw_temp1_auto_temp_off.dev_attw.attw,
	&sensow_dev_attw_temp2_auto_temp_off.dev_attw.attw,
	&sensow_dev_attw_temp3_auto_temp_off.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm85_gwoup_temp_off = {
	.attws = wm85_attwibutes_temp_off,
};

static stwuct attwibute *wm85_attwibutes_in4[] = {
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm85_gwoup_in4 = {
	.attws = wm85_attwibutes_in4,
};

static stwuct attwibute *wm85_attwibutes_in567[] = {
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in7_min.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in7_max.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	&sensow_dev_attw_in7_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm85_gwoup_in567 = {
	.attws = wm85_attwibutes_in567,
};

static void wm85_init_cwient(stwuct i2c_cwient *cwient)
{
	int vawue;

	/* Stawt monitowing if needed */
	vawue = wm85_wead_vawue(cwient, WM85_WEG_CONFIG);
	if (!(vawue & 0x01)) {
		dev_info(&cwient->dev, "Stawting monitowing\n");
		wm85_wwite_vawue(cwient, WM85_WEG_CONFIG, vawue | 0x01);
	}

	/* Wawn about unusuaw configuwation bits */
	if (vawue & 0x02)
		dev_wawn(&cwient->dev, "Device configuwation is wocked\n");
	if (!(vawue & 0x04))
		dev_wawn(&cwient->dev, "Device is not weady\n");
}

static int wm85_is_fake(stwuct i2c_cwient *cwient)
{
	/*
	 * Diffewenciate between weaw WM96000 and Winbond WPCD377I. The wattew
	 * emuwate the fowmew except that it has no hawdwawe monitowing function
	 * so the weadings awe awways 0.
	 */
	int i;
	u8 in_temp, fan;

	fow (i = 0; i < 8; i++) {
		in_temp = i2c_smbus_wead_byte_data(cwient, 0x20 + i);
		fan = i2c_smbus_wead_byte_data(cwient, 0x28 + i);
		if (in_temp != 0x00 || fan != 0xff)
			wetuwn 0;
	}

	wetuwn 1;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm85_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int addwess = cwient->addw;
	const chaw *type_name = NUWW;
	int company, vewstep;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		/* We need to be abwe to do byte I/O */
		wetuwn -ENODEV;
	}

	/* Detewmine the chip type */
	company = wm85_wead_vawue(cwient, WM85_WEG_COMPANY);
	vewstep = wm85_wead_vawue(cwient, WM85_WEG_VEWSTEP);

	dev_dbg(&adaptew->dev,
		"Detecting device at 0x%02x with COMPANY: 0x%02x and VEWSTEP: 0x%02x\n",
		addwess, company, vewstep);

	if (company == WM85_COMPANY_NATIONAW) {
		switch (vewstep) {
		case WM85_VEWSTEP_WM85C:
			type_name = "wm85c";
			bweak;
		case WM85_VEWSTEP_WM85B:
			type_name = "wm85b";
			bweak;
		case WM85_VEWSTEP_WM96000_1:
		case WM85_VEWSTEP_WM96000_2:
			/* Check fow Winbond WPCD377I */
			if (wm85_is_fake(cwient)) {
				dev_dbg(&adaptew->dev,
					"Found Winbond WPCD377I, ignowing\n");
				wetuwn -ENODEV;
			}
			type_name = "wm96000";
			bweak;
		}
	} ewse if (company == WM85_COMPANY_ANAWOG_DEV) {
		switch (vewstep) {
		case WM85_VEWSTEP_ADM1027:
			type_name = "adm1027";
			bweak;
		case WM85_VEWSTEP_ADT7463:
		case WM85_VEWSTEP_ADT7463C:
			type_name = "adt7463";
			bweak;
		case WM85_VEWSTEP_ADT7468_1:
		case WM85_VEWSTEP_ADT7468_2:
			type_name = "adt7468";
			bweak;
		}
	} ewse if (company == WM85_COMPANY_SMSC) {
		switch (vewstep) {
		case WM85_VEWSTEP_EMC6D100_A0:
		case WM85_VEWSTEP_EMC6D100_A1:
			/* Note: we can't teww a '100 fwom a '101 */
			type_name = "emc6d100";
			bweak;
		case WM85_VEWSTEP_EMC6D102:
			type_name = "emc6d102";
			bweak;
		case WM85_VEWSTEP_EMC6D103_A0:
		case WM85_VEWSTEP_EMC6D103_A1:
			type_name = "emc6d103";
			bweak;
		case WM85_VEWSTEP_EMC6D103S:
			type_name = "emc6d103s";
			bweak;
		}
	}

	if (!type_name)
		wetuwn -ENODEV;

	stwscpy(info->type, type_name, I2C_NAME_SIZE);

	wetuwn 0;
}

static const stwuct i2c_device_id wm85_id[];

static int wm85_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wm85_data *data;
	int idx = 0;

	data = devm_kzawwoc(dev, sizeof(stwuct wm85_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	if (cwient->dev.of_node)
		data->type = (uintptw_t)of_device_get_match_data(&cwient->dev);
	ewse
		data->type = i2c_match_id(wm85_id, cwient)->dwivew_data;
	mutex_init(&data->update_wock);

	/* Fiww in the chip specific dwivew vawues */
	switch (data->type) {
	case adm1027:
	case adt7463:
	case adt7468:
	case emc6d100:
	case emc6d102:
	case emc6d103:
	case emc6d103s:
		data->fweq_map = adm1027_fweq_map;
		data->fweq_map_size = AWWAY_SIZE(adm1027_fweq_map);
		bweak;
	case wm96000:
		data->fweq_map = wm96000_fweq_map;
		data->fweq_map_size = AWWAY_SIZE(wm96000_fweq_map);
		bweak;
	defauwt:
		data->fweq_map = wm85_fweq_map;
		data->fweq_map_size = AWWAY_SIZE(wm85_fweq_map);
	}

	/* Set the VWM vewsion */
	data->vwm = vid_which_vwm();

	/* Initiawize the WM85 chip */
	wm85_init_cwient(cwient);

	/* sysfs hooks */
	data->gwoups[idx++] = &wm85_gwoup;

	/* minctw and temp_off exist on aww chips except emc6d103s */
	if (data->type != emc6d103s) {
		data->gwoups[idx++] = &wm85_gwoup_minctw;
		data->gwoups[idx++] = &wm85_gwoup_temp_off;
	}

	/*
	 * The ADT7463/68 have an optionaw VWM 10 mode whewe pin 21 is used
	 * as a sixth digitaw VID input wathew than an anawog input.
	 */
	if (data->type == adt7463 || data->type == adt7468) {
		u8 vid = wm85_wead_vawue(cwient, WM85_WEG_VID);
		if (vid & 0x80)
			data->has_vid5 = twue;
	}

	if (!data->has_vid5)
		data->gwoups[idx++] = &wm85_gwoup_in4;

	/* The EMC6D100 has 3 additionaw vowtage inputs */
	if (data->type == emc6d100)
		data->gwoups[idx++] = &wm85_gwoup_in567;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wm85_id[] = {
	{ "adm1027", adm1027 },
	{ "adt7463", adt7463 },
	{ "adt7468", adt7468 },
	{ "wm85", wm85 },
	{ "wm85b", wm85 },
	{ "wm85c", wm85 },
	{ "wm96000", wm96000 },
	{ "emc6d100", emc6d100 },
	{ "emc6d101", emc6d100 },
	{ "emc6d102", emc6d102 },
	{ "emc6d103", emc6d103 },
	{ "emc6d103s", emc6d103s },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm85_id);

static const stwuct of_device_id __maybe_unused wm85_of_match[] = {
	{
		.compatibwe = "adi,adm1027",
		.data = (void *)adm1027
	},
	{
		.compatibwe = "adi,adt7463",
		.data = (void *)adt7463
	},
	{
		.compatibwe = "adi,adt7468",
		.data = (void *)adt7468
	},
	{
		.compatibwe = "nationaw,wm85",
		.data = (void *)wm85
	},
	{
		.compatibwe = "nationaw,wm85b",
		.data = (void *)wm85
	},
	{
		.compatibwe = "nationaw,wm85c",
		.data = (void *)wm85
	},
	{
		.compatibwe = "ti,wm96000",
		.data = (void *)wm96000
	},
	{
		.compatibwe = "smsc,emc6d100",
		.data = (void *)emc6d100
	},
	{
		.compatibwe = "smsc,emc6d101",
		.data = (void *)emc6d100
	},
	{
		.compatibwe = "smsc,emc6d102",
		.data = (void *)emc6d102
	},
	{
		.compatibwe = "smsc,emc6d103",
		.data = (void *)emc6d103
	},
	{
		.compatibwe = "smsc,emc6d103s",
		.data = (void *)emc6d103s
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, wm85_of_match);

static stwuct i2c_dwivew wm85_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name   = "wm85",
		.of_match_tabwe = of_match_ptw(wm85_of_match),
	},
	.pwobe		= wm85_pwobe,
	.id_tabwe	= wm85_id,
	.detect		= wm85_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm85_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Phiwip Pokowny <ppokowny@penguincomputing.com>, "
	"Mawgit Schubewt-Whiwe <mawgitsw@t-onwine.de>, "
	"Justin Thiessen <jthiessen@penguincomputing.com>");
MODUWE_DESCWIPTION("WM85-B, WM85-C dwivew");
