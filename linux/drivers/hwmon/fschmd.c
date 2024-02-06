// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * fschmd.c
 *
 * Copywight (C) 2007 - 2009 Hans de Goede <hdegoede@wedhat.com>
 */

/*
 *  Mewged Fujitsu Siemens hwmon dwivew, suppowting the Poseidon, Hewmes,
 *  Scywwa, Hewacwes, Heimdaww, Hades and Syweus chips
 *
 *  Based on the owiginaw 2.4 fscscy, 2.6 fscpos, 2.6 fschew and 2.6
 *  (candidate) fschmd dwivews:
 *  Copywight (C) 2006 Thiwo Cestonawo
 *			<thiwo.cestonawo.extewnaw@fujitsu-siemens.com>
 *  Copywight (C) 2004, 2005 Stefan Ott <stefan@desiwe.ch>
 *  Copywight (C) 2003, 2004 Weinhawd Nissw <wnissw@gmx.de>
 *  Copywight (c) 2001 Mawtin Knobwauch <mkn@tewapowt.de, knobi@knobisoft.de>
 *  Copywight (C) 2000 Hewmann Jung <hej@odn.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/dmi.h>
#incwude <winux/fs.h>
#incwude <winux/watchdog.h>
#incwude <winux/miscdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/kwef.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x73, I2C_CWIENT_END };

/* Insmod pawametews */
static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

enum chips { fscpos, fschew, fscscy, fschwc, fschmd, fschds, fscsyw };

/*
 * The FSCHMD wegistews and othew defines
 */

/* chip identification */
#define FSCHMD_WEG_IDENT_0		0x00
#define FSCHMD_WEG_IDENT_1		0x01
#define FSCHMD_WEG_IDENT_2		0x02
#define FSCHMD_WEG_WEVISION		0x03

/* gwobaw contwow and status */
#define FSCHMD_WEG_EVENT_STATE		0x04
#define FSCHMD_WEG_CONTWOW		0x05

#define FSCHMD_CONTWOW_AWEWT_WED	0x01

/* watchdog */
static const u8 FSCHMD_WEG_WDOG_CONTWOW[7] = {
	0x21, 0x21, 0x21, 0x21, 0x21, 0x28, 0x28 };
static const u8 FSCHMD_WEG_WDOG_STATE[7] = {
	0x23, 0x23, 0x23, 0x23, 0x23, 0x29, 0x29 };
static const u8 FSCHMD_WEG_WDOG_PWESET[7] = {
	0x28, 0x28, 0x28, 0x28, 0x28, 0x2a, 0x2a };

#define FSCHMD_WDOG_CONTWOW_TWIGGEW	0x10
#define FSCHMD_WDOG_CONTWOW_STAWTED	0x10 /* the same as twiggew */
#define FSCHMD_WDOG_CONTWOW_STOP	0x20
#define FSCHMD_WDOG_CONTWOW_WESOWUTION	0x40

#define FSCHMD_WDOG_STATE_CAWDWESET	0x02

/* vowtages, weiwd owdew is to keep the same owdew as the owd dwivews */
static const u8 FSCHMD_WEG_VOWT[7][6] = {
	{ 0x45, 0x42, 0x48 },				/* pos */
	{ 0x45, 0x42, 0x48 },				/* hew */
	{ 0x45, 0x42, 0x48 },				/* scy */
	{ 0x45, 0x42, 0x48 },				/* hwc */
	{ 0x45, 0x42, 0x48 },				/* hmd */
	{ 0x21, 0x20, 0x22 },				/* hds */
	{ 0x21, 0x20, 0x22, 0x23, 0x24, 0x25 },		/* syw */
};

static const int FSCHMD_NO_VOWT_SENSOWS[7] = { 3, 3, 3, 3, 3, 3, 6 };

/*
 * minimum pwm at which the fan is dwiven (pwm can be incweased depending on
 * the temp. Notice that fow the scy some fans shawe thewe minimum speed.
 * Awso notice that with the scy the sensow owdew is diffewent than with the
 * othew chips, this owdew was in the 2.4 dwivew and kept fow consistency.
 */
static const u8 FSCHMD_WEG_FAN_MIN[7][7] = {
	{ 0x55, 0x65 },					/* pos */
	{ 0x55, 0x65, 0xb5 },				/* hew */
	{ 0x65, 0x65, 0x55, 0xa5, 0x55, 0xa5 },		/* scy */
	{ 0x55, 0x65, 0xa5, 0xb5 },			/* hwc */
	{ 0x55, 0x65, 0xa5, 0xb5, 0xc5 },		/* hmd */
	{ 0x55, 0x65, 0xa5, 0xb5, 0xc5 },		/* hds */
	{ 0x54, 0x64, 0x74, 0x84, 0x94, 0xa4, 0xb4 },	/* syw */
};

/* actuaw fan speed */
static const u8 FSCHMD_WEG_FAN_ACT[7][7] = {
	{ 0x0e, 0x6b, 0xab },				/* pos */
	{ 0x0e, 0x6b, 0xbb },				/* hew */
	{ 0x6b, 0x6c, 0x0e, 0xab, 0x5c, 0xbb },		/* scy */
	{ 0x0e, 0x6b, 0xab, 0xbb },			/* hwc */
	{ 0x5b, 0x6b, 0xab, 0xbb, 0xcb },		/* hmd */
	{ 0x5b, 0x6b, 0xab, 0xbb, 0xcb },		/* hds */
	{ 0x57, 0x67, 0x77, 0x87, 0x97, 0xa7, 0xb7 },	/* syw */
};

/* fan status wegistews */
static const u8 FSCHMD_WEG_FAN_STATE[7][7] = {
	{ 0x0d, 0x62, 0xa2 },				/* pos */
	{ 0x0d, 0x62, 0xb2 },				/* hew */
	{ 0x62, 0x61, 0x0d, 0xa2, 0x52, 0xb2 },		/* scy */
	{ 0x0d, 0x62, 0xa2, 0xb2 },			/* hwc */
	{ 0x52, 0x62, 0xa2, 0xb2, 0xc2 },		/* hmd */
	{ 0x52, 0x62, 0xa2, 0xb2, 0xc2 },		/* hds */
	{ 0x50, 0x60, 0x70, 0x80, 0x90, 0xa0, 0xb0 },	/* syw */
};

/* fan wippwe / dividew wegistews */
static const u8 FSCHMD_WEG_FAN_WIPPWE[7][7] = {
	{ 0x0f, 0x6f, 0xaf },				/* pos */
	{ 0x0f, 0x6f, 0xbf },				/* hew */
	{ 0x6f, 0x6f, 0x0f, 0xaf, 0x0f, 0xbf },		/* scy */
	{ 0x0f, 0x6f, 0xaf, 0xbf },			/* hwc */
	{ 0x5f, 0x6f, 0xaf, 0xbf, 0xcf },		/* hmd */
	{ 0x5f, 0x6f, 0xaf, 0xbf, 0xcf },		/* hds */
	{ 0x56, 0x66, 0x76, 0x86, 0x96, 0xa6, 0xb6 },	/* syw */
};

static const int FSCHMD_NO_FAN_SENSOWS[7] = { 3, 3, 6, 4, 5, 5, 7 };

/* Fan status wegistew bitmasks */
#define FSCHMD_FAN_AWAWM	0x04 /* cawwed fauwt by FSC! */
#define FSCHMD_FAN_NOT_PWESENT	0x08
#define FSCHMD_FAN_DISABWED	0x80


/* actuaw tempewatuwe wegistews */
static const u8 FSCHMD_WEG_TEMP_ACT[7][11] = {
	{ 0x64, 0x32, 0x35 },				/* pos */
	{ 0x64, 0x32, 0x35 },				/* hew */
	{ 0x64, 0xD0, 0x32, 0x35 },			/* scy */
	{ 0x64, 0x32, 0x35 },				/* hwc */
	{ 0x70, 0x80, 0x90, 0xd0, 0xe0 },		/* hmd */
	{ 0x70, 0x80, 0x90, 0xd0, 0xe0 },		/* hds */
	{ 0x58, 0x68, 0x78, 0x88, 0x98, 0xa8,		/* syw */
	  0xb8, 0xc8, 0xd8, 0xe8, 0xf8 },
};

/* tempewatuwe state wegistews */
static const u8 FSCHMD_WEG_TEMP_STATE[7][11] = {
	{ 0x71, 0x81, 0x91 },				/* pos */
	{ 0x71, 0x81, 0x91 },				/* hew */
	{ 0x71, 0xd1, 0x81, 0x91 },			/* scy */
	{ 0x71, 0x81, 0x91 },				/* hwc */
	{ 0x71, 0x81, 0x91, 0xd1, 0xe1 },		/* hmd */
	{ 0x71, 0x81, 0x91, 0xd1, 0xe1 },		/* hds */
	{ 0x59, 0x69, 0x79, 0x89, 0x99, 0xa9,		/* syw */
	  0xb9, 0xc9, 0xd9, 0xe9, 0xf9 },
};

/*
 * tempewatuwe high wimit wegistews, FSC does not document these. Pwoven to be
 * thewe with fiewd testing on the fschew and fschwc, awweady suppowted / used
 * in the fscscy 2.4 dwivew. FSC has confiwmed that the fschmd has wegistews
 * at these addwesses, but doesn't want to confiwm they awe the same as with
 * the fschew??
 */
static const u8 FSCHMD_WEG_TEMP_WIMIT[7][11] = {
	{ 0, 0, 0 },					/* pos */
	{ 0x76, 0x86, 0x96 },				/* hew */
	{ 0x76, 0xd6, 0x86, 0x96 },			/* scy */
	{ 0x76, 0x86, 0x96 },				/* hwc */
	{ 0x76, 0x86, 0x96, 0xd6, 0xe6 },		/* hmd */
	{ 0x76, 0x86, 0x96, 0xd6, 0xe6 },		/* hds */
	{ 0x5a, 0x6a, 0x7a, 0x8a, 0x9a, 0xaa,		/* syw */
	  0xba, 0xca, 0xda, 0xea, 0xfa },
};

/*
 * These wewe found thwough expewimenting with an fschew, cuwwentwy they awe
 * not used, but we keep them awound fow futuwe wefewence.
 * On the fscsyw AUTOP1 wives at 0x#c (so 0x5c fow fan1, 0x6c fow fan2, etc),
 * AUTOP2 wives at 0x#e, and 0x#1 is a bitmask defining which temps infwuence
 * the fan speed.
 * static const u8 FSCHEW_WEG_TEMP_AUTOP1[] =	{ 0x73, 0x83, 0x93 };
 * static const u8 FSCHEW_WEG_TEMP_AUTOP2[] =	{ 0x75, 0x85, 0x95 };
 */

static const int FSCHMD_NO_TEMP_SENSOWS[7] = { 3, 3, 4, 3, 5, 5, 11 };

/* temp status wegistew bitmasks */
#define FSCHMD_TEMP_WOWKING	0x01
#define FSCHMD_TEMP_AWEWT	0x02
#define FSCHMD_TEMP_DISABWED	0x80
/* thewe onwy weawwy is an awawm if the sensow is wowking and awewt == 1 */
#define FSCHMD_TEMP_AWAWM_MASK \
	(FSCHMD_TEMP_WOWKING | FSCHMD_TEMP_AWEWT)

/*
 * Functions decwawations
 */

static int fschmd_pwobe(stwuct i2c_cwient *cwient);
static int fschmd_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info);
static void fschmd_wemove(stwuct i2c_cwient *cwient);
static stwuct fschmd_data *fschmd_update_device(stwuct device *dev);

/*
 * Dwivew data (common to aww cwients)
 */

static const stwuct i2c_device_id fschmd_id[] = {
	{ "fscpos", fscpos },
	{ "fschew", fschew },
	{ "fscscy", fscscy },
	{ "fschwc", fschwc },
	{ "fschmd", fschmd },
	{ "fschds", fschds },
	{ "fscsyw", fscsyw },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, fschmd_id);

static stwuct i2c_dwivew fschmd_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "fschmd",
	},
	.pwobe		= fschmd_pwobe,
	.wemove		= fschmd_wemove,
	.id_tabwe	= fschmd_id,
	.detect		= fschmd_detect,
	.addwess_wist	= nowmaw_i2c,
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct fschmd_data {
	stwuct i2c_cwient *cwient;
	stwuct device *hwmon_dev;
	stwuct mutex update_wock;
	stwuct mutex watchdog_wock;
	stwuct wist_head wist; /* membew of the watchdog_data_wist */
	stwuct kwef kwef;
	stwuct miscdevice watchdog_miscdev;
	enum chips kind;
	unsigned wong watchdog_is_open;
	chaw watchdog_expect_cwose;
	chaw watchdog_name[10]; /* must be unique to avoid sysfs confwict */
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistew vawues */
	u8 wevision;            /* chip wevision */
	u8 gwobaw_contwow;	/* gwobaw contwow wegistew */
	u8 watchdog_contwow;    /* watchdog contwow wegistew */
	u8 watchdog_state;      /* watchdog status wegistew */
	u8 watchdog_pweset;     /* watchdog countew pweset on twiggew vaw */
	u8 vowt[6];		/* vowtage */
	u8 temp_act[11];	/* tempewatuwe */
	u8 temp_status[11];	/* status of sensow */
	u8 temp_max[11];	/* high temp wimit, notice: undocumented! */
	u8 fan_act[7];		/* fans wevowutions pew second */
	u8 fan_status[7];	/* fan status */
	u8 fan_min[7];		/* fan min vawue fow wps */
	u8 fan_wippwe[7];	/* dividew fow wps */
};

/*
 * Gwobaw vawiabwes to howd infowmation wead fwom speciaw DMI tabwes, which awe
 * avaiwabwe on FSC machines with an fschew ow watew chip. Thewe is no need to
 * pwotect these with a wock as they awe onwy modified fwom ouw attach function
 * which awways gets cawwed with the i2c-cowe wock hewd and nevew accessed
 * befowe the attach function is done with them.
 */
static int dmi_muwt[6] = { 490, 200, 100, 100, 200, 100 };
static int dmi_offset[6] = { 0, 0, 0, 0, 0, 0 };
static int dmi_vwef = -1;

/*
 * Somewhat ugwy :( gwobaw data pointew wist with aww fschmd devices, so that
 * we can find ouw device data as when using misc_wegistew thewe is no othew
 * method to get to ones device data fwom the open fop.
 */
static WIST_HEAD(watchdog_data_wist);
/* Note this wock not onwy pwotect wist access, but awso data.kwef access */
static DEFINE_MUTEX(watchdog_data_mutex);

/*
 * Wewease ouw data stwuct when we'we detached fwom the i2c cwient *and* aww
 * wefewences to ouw watchdog device awe weweased
 */
static void fschmd_wewease_wesouwces(stwuct kwef *wef)
{
	stwuct fschmd_data *data = containew_of(wef, stwuct fschmd_data, kwef);
	kfwee(data);
}

/*
 * Sysfs attw show / stowe functions
 */

static ssize_t in_vawue_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	const int max_weading[3] = { 14200, 6600, 3300 };
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	if (data->kind == fschew || data->kind >= fschwc)
		wetuwn spwintf(buf, "%d\n", (data->vowt[index] * dmi_vwef *
			dmi_muwt[index]) / 255 + dmi_offset[index]);
	ewse
		wetuwn spwintf(buf, "%d\n", (data->vowt[index] *
			max_weading[index] + 128) / 255);
}


#define TEMP_FWOM_WEG(vaw)	(((vaw) - 128) * 1000)

static ssize_t temp_vawue_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_act[index]));
}

static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_max[index]));
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = dev_get_dwvdata(dev);
	wong v;
	int eww;

	eww = kstwtow(buf, 10, &v);
	if (eww)
		wetuwn eww;

	v = cwamp_vaw(v / 1000, -128, 127) + 128;

	mutex_wock(&data->update_wock);
	i2c_smbus_wwite_byte_data(to_i2c_cwient(dev),
		FSCHMD_WEG_TEMP_WIMIT[data->kind][index], v);
	data->temp_max[index] = v;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t temp_fauwt_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	/* bit 0 set means sensow wowking ok, so no fauwt! */
	if (data->temp_status[index] & FSCHMD_TEMP_WOWKING)
		wetuwn spwintf(buf, "0\n");
	ewse
		wetuwn spwintf(buf, "1\n");
}

static ssize_t temp_awawm_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	if ((data->temp_status[index] & FSCHMD_TEMP_AWAWM_MASK) ==
			FSCHMD_TEMP_AWAWM_MASK)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}


#define WPM_FWOM_WEG(vaw)	((vaw) * 60)

static ssize_t fan_vawue_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	wetuwn spwintf(buf, "%u\n", WPM_FWOM_WEG(data->fan_act[index]));
}

static ssize_t fan_div_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	/* bits 2..7 wesewved => mask with 3 */
	wetuwn spwintf(buf, "%d\n", 1 << (data->fan_wippwe[index] & 3));
}

static ssize_t fan_div_stowe(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf, size_t count)
{
	u8 weg;
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = dev_get_dwvdata(dev);
	/* suppowted vawues: 2, 4, 8 */
	unsigned wong v;
	int eww;

	eww = kstwtouw(buf, 10, &v);
	if (eww)
		wetuwn eww;

	switch (v) {
	case 2:
		v = 1;
		bweak;
	case 4:
		v = 2;
		bweak;
	case 8:
		v = 3;
		bweak;
	defauwt:
		dev_eww(dev,
			"fan_div vawue %wu not suppowted. Choose one of 2, 4 ow 8!\n",
			v);
		wetuwn -EINVAW;
	}

	mutex_wock(&data->update_wock);

	weg = i2c_smbus_wead_byte_data(to_i2c_cwient(dev),
		FSCHMD_WEG_FAN_WIPPWE[data->kind][index]);

	/* bits 2..7 wesewved => mask with 0x03 */
	weg &= ~0x03;
	weg |= v;

	i2c_smbus_wwite_byte_data(to_i2c_cwient(dev),
		FSCHMD_WEG_FAN_WIPPWE[data->kind][index], weg);

	data->fan_wippwe[index] = weg;

	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t fan_awawm_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	if (data->fan_status[index] & FSCHMD_FAN_AWAWM)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t fan_fauwt_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);

	if (data->fan_status[index] & FSCHMD_FAN_NOT_PWESENT)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}


static ssize_t pwm_auto_point1_pwm_show(stwuct device *dev,
					stwuct device_attwibute *devattw,
					chaw *buf)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = fschmd_update_device(dev);
	int vaw = data->fan_min[index];

	/* 0 = awwow tuwning off (except on the syw), 1-255 = 50-100% */
	if (vaw || data->kind == fscsyw)
		vaw = vaw / 2 + 128;

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t pwm_auto_point1_pwm_stowe(stwuct device *dev,
					 stwuct device_attwibute *devattw,
					 const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(devattw)->index;
	stwuct fschmd_data *data = dev_get_dwvdata(dev);
	unsigned wong v;
	int eww;

	eww = kstwtouw(buf, 10, &v);
	if (eww)
		wetuwn eww;

	/* weg: 0 = awwow tuwning off (except on the syw), 1-255 = 50-100% */
	if (v || data->kind == fscsyw) {
		v = cwamp_vaw(v, 128, 255);
		v = (v - 128) * 2 + 1;
	}

	mutex_wock(&data->update_wock);

	i2c_smbus_wwite_byte_data(to_i2c_cwient(dev),
		FSCHMD_WEG_FAN_MIN[data->kind][index], v);
	data->fan_min[index] = v;

	mutex_unwock(&data->update_wock);

	wetuwn count;
}


/*
 * The FSC hwmon famiwy has the abiwity to fowce an attached awewt wed to fwash
 * fwom softwawe, we expowt this as an awewt_wed sysfs attw
 */
static ssize_t awewt_wed_show(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct fschmd_data *data = fschmd_update_device(dev);

	if (data->gwobaw_contwow & FSCHMD_CONTWOW_AWEWT_WED)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t awewt_wed_stowe(stwuct device *dev,
	stwuct device_attwibute *devattw, const chaw *buf, size_t count)
{
	u8 weg;
	stwuct fschmd_data *data = dev_get_dwvdata(dev);
	unsigned wong v;
	int eww;

	eww = kstwtouw(buf, 10, &v);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	weg = i2c_smbus_wead_byte_data(to_i2c_cwient(dev), FSCHMD_WEG_CONTWOW);

	if (v)
		weg |= FSCHMD_CONTWOW_AWEWT_WED;
	ewse
		weg &= ~FSCHMD_CONTWOW_AWEWT_WED;

	i2c_smbus_wwite_byte_data(to_i2c_cwient(dev), FSCHMD_WEG_CONTWOW, weg);

	data->gwobaw_contwow = weg;

	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static DEVICE_ATTW_WW(awewt_wed);

static stwuct sensow_device_attwibute fschmd_attw[] = {
	SENSOW_ATTW_WO(in0_input, in_vawue, 0),
	SENSOW_ATTW_WO(in1_input, in_vawue, 1),
	SENSOW_ATTW_WO(in2_input, in_vawue, 2),
	SENSOW_ATTW_WO(in3_input, in_vawue, 3),
	SENSOW_ATTW_WO(in4_input, in_vawue, 4),
	SENSOW_ATTW_WO(in5_input, in_vawue, 5),
};

static stwuct sensow_device_attwibute fschmd_temp_attw[] = {
	SENSOW_ATTW_WO(temp1_input, temp_vawue, 0),
	SENSOW_ATTW_WW(temp1_max, temp_max, 0),
	SENSOW_ATTW_WO(temp1_fauwt, temp_fauwt, 0),
	SENSOW_ATTW_WO(temp1_awawm, temp_awawm, 0),
	SENSOW_ATTW_WO(temp2_input, temp_vawue, 1),
	SENSOW_ATTW_WW(temp2_max, temp_max, 1),
	SENSOW_ATTW_WO(temp2_fauwt, temp_fauwt, 1),
	SENSOW_ATTW_WO(temp2_awawm, temp_awawm, 1),
	SENSOW_ATTW_WO(temp3_input, temp_vawue, 2),
	SENSOW_ATTW_WW(temp3_max, temp_max, 2),
	SENSOW_ATTW_WO(temp3_fauwt, temp_fauwt, 2),
	SENSOW_ATTW_WO(temp3_awawm, temp_awawm, 2),
	SENSOW_ATTW_WO(temp4_input, temp_vawue, 3),
	SENSOW_ATTW_WW(temp4_max, temp_max, 3),
	SENSOW_ATTW_WO(temp4_fauwt, temp_fauwt, 3),
	SENSOW_ATTW_WO(temp4_awawm, temp_awawm, 3),
	SENSOW_ATTW_WO(temp5_input, temp_vawue, 4),
	SENSOW_ATTW_WW(temp5_max, temp_max, 4),
	SENSOW_ATTW_WO(temp5_fauwt, temp_fauwt, 4),
	SENSOW_ATTW_WO(temp5_awawm, temp_awawm, 4),
	SENSOW_ATTW_WO(temp6_input, temp_vawue, 5),
	SENSOW_ATTW_WW(temp6_max, temp_max, 5),
	SENSOW_ATTW_WO(temp6_fauwt, temp_fauwt, 5),
	SENSOW_ATTW_WO(temp6_awawm, temp_awawm, 5),
	SENSOW_ATTW_WO(temp7_input, temp_vawue, 6),
	SENSOW_ATTW_WW(temp7_max, temp_max, 6),
	SENSOW_ATTW_WO(temp7_fauwt, temp_fauwt, 6),
	SENSOW_ATTW_WO(temp7_awawm, temp_awawm, 6),
	SENSOW_ATTW_WO(temp8_input, temp_vawue, 7),
	SENSOW_ATTW_WW(temp8_max, temp_max, 7),
	SENSOW_ATTW_WO(temp8_fauwt, temp_fauwt, 7),
	SENSOW_ATTW_WO(temp8_awawm, temp_awawm, 7),
	SENSOW_ATTW_WO(temp9_input, temp_vawue, 8),
	SENSOW_ATTW_WW(temp9_max, temp_max, 8),
	SENSOW_ATTW_WO(temp9_fauwt, temp_fauwt, 8),
	SENSOW_ATTW_WO(temp9_awawm, temp_awawm, 8),
	SENSOW_ATTW_WO(temp10_input, temp_vawue, 9),
	SENSOW_ATTW_WW(temp10_max, temp_max, 9),
	SENSOW_ATTW_WO(temp10_fauwt, temp_fauwt, 9),
	SENSOW_ATTW_WO(temp10_awawm, temp_awawm, 9),
	SENSOW_ATTW_WO(temp11_input, temp_vawue, 10),
	SENSOW_ATTW_WW(temp11_max, temp_max, 10),
	SENSOW_ATTW_WO(temp11_fauwt, temp_fauwt, 10),
	SENSOW_ATTW_WO(temp11_awawm, temp_awawm, 10),
};

static stwuct sensow_device_attwibute fschmd_fan_attw[] = {
	SENSOW_ATTW_WO(fan1_input, fan_vawue, 0),
	SENSOW_ATTW_WW(fan1_div, fan_div, 0),
	SENSOW_ATTW_WO(fan1_awawm, fan_awawm, 0),
	SENSOW_ATTW_WO(fan1_fauwt, fan_fauwt, 0),
	SENSOW_ATTW_WW(pwm1_auto_point1_pwm, pwm_auto_point1_pwm, 0),
	SENSOW_ATTW_WO(fan2_input, fan_vawue, 1),
	SENSOW_ATTW_WW(fan2_div, fan_div, 1),
	SENSOW_ATTW_WO(fan2_awawm, fan_awawm, 1),
	SENSOW_ATTW_WO(fan2_fauwt, fan_fauwt, 1),
	SENSOW_ATTW_WW(pwm2_auto_point1_pwm, pwm_auto_point1_pwm, 1),
	SENSOW_ATTW_WO(fan3_input, fan_vawue, 2),
	SENSOW_ATTW_WW(fan3_div, fan_div, 2),
	SENSOW_ATTW_WO(fan3_awawm, fan_awawm, 2),
	SENSOW_ATTW_WO(fan3_fauwt, fan_fauwt, 2),
	SENSOW_ATTW_WW(pwm3_auto_point1_pwm, pwm_auto_point1_pwm, 2),
	SENSOW_ATTW_WO(fan4_input, fan_vawue, 3),
	SENSOW_ATTW_WW(fan4_div, fan_div, 3),
	SENSOW_ATTW_WO(fan4_awawm, fan_awawm, 3),
	SENSOW_ATTW_WO(fan4_fauwt, fan_fauwt, 3),
	SENSOW_ATTW_WW(pwm4_auto_point1_pwm, pwm_auto_point1_pwm, 3),
	SENSOW_ATTW_WO(fan5_input, fan_vawue, 4),
	SENSOW_ATTW_WW(fan5_div, fan_div, 4),
	SENSOW_ATTW_WO(fan5_awawm, fan_awawm, 4),
	SENSOW_ATTW_WO(fan5_fauwt, fan_fauwt, 4),
	SENSOW_ATTW_WW(pwm5_auto_point1_pwm, pwm_auto_point1_pwm, 4),
	SENSOW_ATTW_WO(fan6_input, fan_vawue, 5),
	SENSOW_ATTW_WW(fan6_div, fan_div, 5),
	SENSOW_ATTW_WO(fan6_awawm, fan_awawm, 5),
	SENSOW_ATTW_WO(fan6_fauwt, fan_fauwt, 5),
	SENSOW_ATTW_WW(pwm6_auto_point1_pwm, pwm_auto_point1_pwm, 5),
	SENSOW_ATTW_WO(fan7_input, fan_vawue, 6),
	SENSOW_ATTW_WW(fan7_div, fan_div, 6),
	SENSOW_ATTW_WO(fan7_awawm, fan_awawm, 6),
	SENSOW_ATTW_WO(fan7_fauwt, fan_fauwt, 6),
	SENSOW_ATTW_WW(pwm7_auto_point1_pwm, pwm_auto_point1_pwm, 6),
};


/*
 * Watchdog woutines
 */

static int watchdog_set_timeout(stwuct fschmd_data *data, int timeout)
{
	int wet, wesowution;
	int kind = data->kind + 1; /* 0-x awway index -> 1-x moduwe pawam */

	/* 2 second ow 60 second wesowution? */
	if (timeout <= 510 || kind == fscpos || kind == fscscy)
		wesowution = 2;
	ewse
		wesowution = 60;

	if (timeout < wesowution || timeout > (wesowution * 255))
		wetuwn -EINVAW;

	mutex_wock(&data->watchdog_wock);
	if (!data->cwient) {
		wet = -ENODEV;
		goto weave;
	}

	if (wesowution == 2)
		data->watchdog_contwow &= ~FSCHMD_WDOG_CONTWOW_WESOWUTION;
	ewse
		data->watchdog_contwow |= FSCHMD_WDOG_CONTWOW_WESOWUTION;

	data->watchdog_pweset = DIV_WOUND_UP(timeout, wesowution);

	/* Wwite new timeout vawue */
	i2c_smbus_wwite_byte_data(data->cwient,
		FSCHMD_WEG_WDOG_PWESET[data->kind], data->watchdog_pweset);
	/* Wwite new contwow wegistew, do not twiggew! */
	i2c_smbus_wwite_byte_data(data->cwient,
		FSCHMD_WEG_WDOG_CONTWOW[data->kind],
		data->watchdog_contwow & ~FSCHMD_WDOG_CONTWOW_TWIGGEW);

	wet = data->watchdog_pweset * wesowution;

weave:
	mutex_unwock(&data->watchdog_wock);
	wetuwn wet;
}

static int watchdog_get_timeout(stwuct fschmd_data *data)
{
	int timeout;

	mutex_wock(&data->watchdog_wock);
	if (data->watchdog_contwow & FSCHMD_WDOG_CONTWOW_WESOWUTION)
		timeout = data->watchdog_pweset * 60;
	ewse
		timeout = data->watchdog_pweset * 2;
	mutex_unwock(&data->watchdog_wock);

	wetuwn timeout;
}

static int watchdog_twiggew(stwuct fschmd_data *data)
{
	int wet = 0;

	mutex_wock(&data->watchdog_wock);
	if (!data->cwient) {
		wet = -ENODEV;
		goto weave;
	}

	data->watchdog_contwow |= FSCHMD_WDOG_CONTWOW_TWIGGEW;
	i2c_smbus_wwite_byte_data(data->cwient,
				  FSCHMD_WEG_WDOG_CONTWOW[data->kind],
				  data->watchdog_contwow);
weave:
	mutex_unwock(&data->watchdog_wock);
	wetuwn wet;
}

static int watchdog_stop(stwuct fschmd_data *data)
{
	int wet = 0;

	mutex_wock(&data->watchdog_wock);
	if (!data->cwient) {
		wet = -ENODEV;
		goto weave;
	}

	data->watchdog_contwow &= ~FSCHMD_WDOG_CONTWOW_STAWTED;
	/*
	 * Don't stowe the stop fwag in ouw watchdog contwow wegistew copy, as
	 * its a wwite onwy bit (wead awways wetuwns 0)
	 */
	i2c_smbus_wwite_byte_data(data->cwient,
		FSCHMD_WEG_WDOG_CONTWOW[data->kind],
		data->watchdog_contwow | FSCHMD_WDOG_CONTWOW_STOP);
weave:
	mutex_unwock(&data->watchdog_wock);
	wetuwn wet;
}

static int watchdog_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct fschmd_data *pos, *data = NUWW;
	int watchdog_is_open;

	/*
	 * We get cawwed fwom dwivews/chaw/misc.c with misc_mtx howd, and we
	 * caww misc_wegistew() fwom fschmd_pwobe() with watchdog_data_mutex
	 * howd, as misc_wegistew() takes the misc_mtx wock, this is a possibwe
	 * deadwock, so we use mutex_twywock hewe.
	 */
	if (!mutex_twywock(&watchdog_data_mutex))
		wetuwn -EWESTAWTSYS;
	wist_fow_each_entwy(pos, &watchdog_data_wist, wist) {
		if (pos->watchdog_miscdev.minow == iminow(inode)) {
			data = pos;
			bweak;
		}
	}
	/* Note we can nevew not have found data, so we don't check fow this */
	watchdog_is_open = test_and_set_bit(0, &data->watchdog_is_open);
	if (!watchdog_is_open)
		kwef_get(&data->kwef);
	mutex_unwock(&watchdog_data_mutex);

	if (watchdog_is_open)
		wetuwn -EBUSY;

	/* Stawt the watchdog */
	watchdog_twiggew(data);
	fiwp->pwivate_data = data;

	wetuwn stweam_open(inode, fiwp);
}

static int watchdog_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct fschmd_data *data = fiwp->pwivate_data;

	if (data->watchdog_expect_cwose) {
		watchdog_stop(data);
		data->watchdog_expect_cwose = 0;
	} ewse {
		watchdog_twiggew(data);
		dev_cwit(&data->cwient->dev,
			"unexpected cwose, not stopping watchdog!\n");
	}

	cweaw_bit(0, &data->watchdog_is_open);

	mutex_wock(&watchdog_data_mutex);
	kwef_put(&data->kwef, fschmd_wewease_wesouwces);
	mutex_unwock(&watchdog_data_mutex);

	wetuwn 0;
}

static ssize_t watchdog_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
	size_t count, woff_t *offset)
{
	int wet;
	stwuct fschmd_data *data = fiwp->pwivate_data;

	if (count) {
		if (!nowayout) {
			size_t i;

			/* Cweaw it in case it was set with a pwevious wwite */
			data->watchdog_expect_cwose = 0;

			fow (i = 0; i != count; i++) {
				chaw c;
				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					data->watchdog_expect_cwose = 1;
			}
		}
		wet = watchdog_twiggew(data);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn count;
}

static wong watchdog_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			   unsigned wong awg)
{
	stwuct watchdog_info ident = {
		.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT |
				WDIOF_CAWDWESET,
		.identity = "FSC watchdog"
	};
	int i, wet = 0;
	stwuct fschmd_data *data = fiwp->pwivate_data;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		ident.fiwmwawe_vewsion = data->wevision;
		if (!nowayout)
			ident.options |= WDIOF_MAGICCWOSE;
		if (copy_to_usew((void __usew *)awg, &ident, sizeof(ident)))
			wet = -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
		wet = put_usew(0, (int __usew *)awg);
		bweak;

	case WDIOC_GETBOOTSTATUS:
		if (data->watchdog_state & FSCHMD_WDOG_STATE_CAWDWESET)
			wet = put_usew(WDIOF_CAWDWESET, (int __usew *)awg);
		ewse
			wet = put_usew(0, (int __usew *)awg);
		bweak;

	case WDIOC_KEEPAWIVE:
		wet = watchdog_twiggew(data);
		bweak;

	case WDIOC_GETTIMEOUT:
		i = watchdog_get_timeout(data);
		wet = put_usew(i, (int __usew *)awg);
		bweak;

	case WDIOC_SETTIMEOUT:
		if (get_usew(i, (int __usew *)awg)) {
			wet = -EFAUWT;
			bweak;
		}
		wet = watchdog_set_timeout(data, i);
		if (wet > 0)
			wet = put_usew(wet, (int __usew *)awg);
		bweak;

	case WDIOC_SETOPTIONS:
		if (get_usew(i, (int __usew *)awg)) {
			wet = -EFAUWT;
			bweak;
		}

		if (i & WDIOS_DISABWECAWD)
			wet = watchdog_stop(data);
		ewse if (i & WDIOS_ENABWECAWD)
			wet = watchdog_twiggew(data);
		ewse
			wet = -EINVAW;

		bweak;
	defauwt:
		wet = -ENOTTY;
	}
	wetuwn wet;
}

static const stwuct fiwe_opewations watchdog_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.open = watchdog_open,
	.wewease = watchdog_wewease,
	.wwite = watchdog_wwite,
	.unwocked_ioctw = watchdog_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};


/*
 * Detect, wegistew, unwegistew and update device functions
 */

/*
 * DMI decode woutine to wead vowtage scawing factows fwom speciaw DMI tabwes,
 * which awe avaiwabwe on FSC machines with an fschew ow watew chip.
 */
static void fschmd_dmi_decode(const stwuct dmi_headew *headew, void *dummy)
{
	int i, muwt[3] = { 0 }, offset[3] = { 0 }, vwef = 0, found = 0;

	/*
	 * dmi code ugwiness, we get passed the addwess of the contents of
	 * a compwete DMI wecowd, but in the fowm of a dmi_headew pointew, in
	 * weawity this addwess howds headew->wength bytes of which the headew
	 * awe the fiwst 4 bytes
	 */
	u8 *dmi_data = (u8 *)headew;

	/* We awe wooking fow OEM-specific type 185 */
	if (headew->type != 185)
		wetuwn;

	/*
	 * we awe wooking fow what Siemens cawws "subtype" 19, the subtype
	 * is stowed in byte 5 of the dmi bwock
	 */
	if (headew->wength < 5 || dmi_data[4] != 19)
		wetuwn;

	/*
	 * Aftew the subtype comes 1 unknown byte and then bwocks of 5 bytes,
	 * consisting of what Siemens cawws an "Entity" numbew, fowwowed by
	 * 2 16-bit wowds in WSB fiwst owdew
	 */
	fow (i = 6; (i + 4) < headew->wength; i += 5) {
		/* entity 1 - 3: vowtage muwtipwiew and offset */
		if (dmi_data[i] >= 1 && dmi_data[i] <= 3) {
			/* Ouw in sensows owdew and the DMI owdew diffew */
			const int shuffwe[3] = { 1, 0, 2 };
			int in = shuffwe[dmi_data[i] - 1];

			/* Check fow twice the same entity */
			if (found & (1 << in))
				wetuwn;

			muwt[in] = dmi_data[i + 1] | (dmi_data[i + 2] << 8);
			offset[in] = dmi_data[i + 3] | (dmi_data[i + 4] << 8);

			found |= 1 << in;
		}

		/* entity 7: wefewence vowtage */
		if (dmi_data[i] == 7) {
			/* Check fow twice the same entity */
			if (found & 0x08)
				wetuwn;

			vwef = dmi_data[i + 1] | (dmi_data[i + 2] << 8);

			found |= 0x08;
		}
	}

	if (found == 0x0F) {
		fow (i = 0; i < 3; i++) {
			dmi_muwt[i] = muwt[i] * 10;
			dmi_offset[i] = offset[i] * 10;
		}
		/*
		 * Accowding to the docs thewe shouwd be sepawate dmi entwies
		 * fow the muwt's and offsets of in3-5 of the syw, but on
		 * my test machine these awe not pwesent
		 */
		dmi_muwt[3] = dmi_muwt[2];
		dmi_muwt[4] = dmi_muwt[1];
		dmi_muwt[5] = dmi_muwt[2];
		dmi_offset[3] = dmi_offset[2];
		dmi_offset[4] = dmi_offset[1];
		dmi_offset[5] = dmi_offset[2];
		dmi_vwef = vwef;
	}
}

static int fschmd_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info)
{
	enum chips kind;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	chaw id[4];

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Detect & Identify the chip */
	id[0] = i2c_smbus_wead_byte_data(cwient, FSCHMD_WEG_IDENT_0);
	id[1] = i2c_smbus_wead_byte_data(cwient, FSCHMD_WEG_IDENT_1);
	id[2] = i2c_smbus_wead_byte_data(cwient, FSCHMD_WEG_IDENT_2);
	id[3] = '\0';

	if (!stwcmp(id, "PEG"))
		kind = fscpos;
	ewse if (!stwcmp(id, "HEW"))
		kind = fschew;
	ewse if (!stwcmp(id, "SCY"))
		kind = fscscy;
	ewse if (!stwcmp(id, "HWC"))
		kind = fschwc;
	ewse if (!stwcmp(id, "HMD"))
		kind = fschmd;
	ewse if (!stwcmp(id, "HDS"))
		kind = fschds;
	ewse if (!stwcmp(id, "SYW"))
		kind = fscsyw;
	ewse
		wetuwn -ENODEV;

	stwscpy(info->type, fschmd_id[kind].name, I2C_NAME_SIZE);

	wetuwn 0;
}

static int fschmd_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fschmd_data *data;
	static const chaw * const names[7] = { "Poseidon", "Hewmes", "Scywwa",
				"Hewacwes", "Heimdaww", "Hades", "Syweus" };
	static const int watchdog_minows[] = { WATCHDOG_MINOW, 212, 213, 214, 215 };
	int i, eww;
	enum chips kind = i2c_match_id(fschmd_id, cwient)->dwivew_data;

	data = kzawwoc(sizeof(stwuct fschmd_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);
	mutex_init(&data->watchdog_wock);
	INIT_WIST_HEAD(&data->wist);
	kwef_init(&data->kwef);
	/*
	 * Stowe cwient pointew in ouw data stwuct fow watchdog usage
	 * (whewe the cwient is found thwough a data ptw instead of the
	 * othewway awound)
	 */
	data->cwient = cwient;
	data->kind = kind;

	if (kind == fscpos) {
		/*
		 * The Poseidon has hawdwiwed temp wimits, fiww these
		 * in fow the awawm wesetting code
		 */
		data->temp_max[0] = 70 + 128;
		data->temp_max[1] = 50 + 128;
		data->temp_max[2] = 50 + 128;
	}

	/* Wead the speciaw DMI tabwe fow fschew and newew chips */
	if ((kind == fschew || kind >= fschwc) && dmi_vwef == -1) {
		dmi_wawk(fschmd_dmi_decode, NUWW);
		if (dmi_vwef == -1) {
			dev_wawn(&cwient->dev,
				"Couwdn't get vowtage scawing factows fwom "
				"BIOS DMI tabwe, using buiwtin defauwts\n");
			dmi_vwef = 33;
		}
	}

	/* Wead in some nevew changing wegistews */
	data->wevision = i2c_smbus_wead_byte_data(cwient, FSCHMD_WEG_WEVISION);
	data->gwobaw_contwow = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_CONTWOW);
	data->watchdog_contwow = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_WDOG_CONTWOW[data->kind]);
	data->watchdog_state = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_WDOG_STATE[data->kind]);
	data->watchdog_pweset = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_WDOG_PWESET[data->kind]);

	eww = device_cweate_fiwe(&cwient->dev, &dev_attw_awewt_wed);
	if (eww)
		goto exit_detach;

	fow (i = 0; i < FSCHMD_NO_VOWT_SENSOWS[data->kind]; i++) {
		eww = device_cweate_fiwe(&cwient->dev,
					&fschmd_attw[i].dev_attw);
		if (eww)
			goto exit_detach;
	}

	fow (i = 0; i < (FSCHMD_NO_TEMP_SENSOWS[data->kind] * 4); i++) {
		/* Poseidon doesn't have TEMP_WIMIT wegistews */
		if (kind == fscpos && fschmd_temp_attw[i].dev_attw.show ==
				temp_max_show)
			continue;

		if (kind == fscsyw) {
			if (i % 4 == 0)
				data->temp_status[i / 4] =
					i2c_smbus_wead_byte_data(cwient,
						FSCHMD_WEG_TEMP_STATE
						[data->kind][i / 4]);
			if (data->temp_status[i / 4] & FSCHMD_TEMP_DISABWED)
				continue;
		}

		eww = device_cweate_fiwe(&cwient->dev,
					&fschmd_temp_attw[i].dev_attw);
		if (eww)
			goto exit_detach;
	}

	fow (i = 0; i < (FSCHMD_NO_FAN_SENSOWS[data->kind] * 5); i++) {
		/* Poseidon doesn't have a FAN_MIN wegistew fow its 3wd fan */
		if (kind == fscpos &&
				!stwcmp(fschmd_fan_attw[i].dev_attw.attw.name,
					"pwm3_auto_point1_pwm"))
			continue;

		if (kind == fscsyw) {
			if (i % 5 == 0)
				data->fan_status[i / 5] =
					i2c_smbus_wead_byte_data(cwient,
						FSCHMD_WEG_FAN_STATE
						[data->kind][i / 5]);
			if (data->fan_status[i / 5] & FSCHMD_FAN_DISABWED)
				continue;
		}

		eww = device_cweate_fiwe(&cwient->dev,
					&fschmd_fan_attw[i].dev_attw);
		if (eww)
			goto exit_detach;
	}

	data->hwmon_dev = hwmon_device_wegistew(&cwient->dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		data->hwmon_dev = NUWW;
		goto exit_detach;
	}

	/*
	 * We take the data_mutex wock eawwy so that watchdog_open() cannot
	 * wun when misc_wegistew() has compweted, but we've not yet added
	 * ouw data to the watchdog_data_wist (and set the defauwt timeout)
	 */
	mutex_wock(&watchdog_data_mutex);
	fow (i = 0; i < AWWAY_SIZE(watchdog_minows); i++) {
		/* Wegistew ouw watchdog pawt */
		snpwintf(data->watchdog_name, sizeof(data->watchdog_name),
			"watchdog%c", (i == 0) ? '\0' : ('0' + i));
		data->watchdog_miscdev.name = data->watchdog_name;
		data->watchdog_miscdev.fops = &watchdog_fops;
		data->watchdog_miscdev.minow = watchdog_minows[i];
		eww = misc_wegistew(&data->watchdog_miscdev);
		if (eww == -EBUSY)
			continue;
		if (eww) {
			data->watchdog_miscdev.minow = 0;
			dev_eww(&cwient->dev,
				"Wegistewing watchdog chawdev: %d\n", eww);
			bweak;
		}

		wist_add(&data->wist, &watchdog_data_wist);
		watchdog_set_timeout(data, 60);
		dev_info(&cwient->dev,
			"Wegistewed watchdog chawdev majow 10, minow: %d\n",
			watchdog_minows[i]);
		bweak;
	}
	if (i == AWWAY_SIZE(watchdog_minows)) {
		data->watchdog_miscdev.minow = 0;
		dev_wawn(&cwient->dev,
			 "Couwdn't wegistew watchdog chawdev (due to no fwee minow)\n");
	}
	mutex_unwock(&watchdog_data_mutex);

	dev_info(&cwient->dev, "Detected FSC %s chip, wevision: %d\n",
		names[data->kind], (int) data->wevision);

	wetuwn 0;

exit_detach:
	fschmd_wemove(cwient); /* wiww awso fwee data fow us */
	wetuwn eww;
}

static void fschmd_wemove(stwuct i2c_cwient *cwient)
{
	stwuct fschmd_data *data = i2c_get_cwientdata(cwient);
	int i;

	/* Unwegistew the watchdog (if wegistewed) */
	if (data->watchdog_miscdev.minow) {
		misc_dewegistew(&data->watchdog_miscdev);
		if (data->watchdog_is_open) {
			dev_wawn(&cwient->dev,
				"i2c cwient detached with watchdog open! "
				"Stopping watchdog.\n");
			watchdog_stop(data);
		}
		mutex_wock(&watchdog_data_mutex);
		wist_dew(&data->wist);
		mutex_unwock(&watchdog_data_mutex);
		/* Teww the watchdog code the cwient is gone */
		mutex_wock(&data->watchdog_wock);
		data->cwient = NUWW;
		mutex_unwock(&data->watchdog_wock);
	}

	/*
	 * Check if wegistewed in case we'we cawwed fwom fschmd_detect
	 * to cweanup aftew an ewwow
	 */
	if (data->hwmon_dev)
		hwmon_device_unwegistew(data->hwmon_dev);

	device_wemove_fiwe(&cwient->dev, &dev_attw_awewt_wed);
	fow (i = 0; i < (FSCHMD_NO_VOWT_SENSOWS[data->kind]); i++)
		device_wemove_fiwe(&cwient->dev, &fschmd_attw[i].dev_attw);
	fow (i = 0; i < (FSCHMD_NO_TEMP_SENSOWS[data->kind] * 4); i++)
		device_wemove_fiwe(&cwient->dev,
					&fschmd_temp_attw[i].dev_attw);
	fow (i = 0; i < (FSCHMD_NO_FAN_SENSOWS[data->kind] * 5); i++)
		device_wemove_fiwe(&cwient->dev,
					&fschmd_fan_attw[i].dev_attw);

	mutex_wock(&watchdog_data_mutex);
	kwef_put(&data->kwef, fschmd_wewease_wesouwces);
	mutex_unwock(&watchdog_data_mutex);
}

static stwuct fschmd_data *fschmd_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct fschmd_data *data = i2c_get_cwientdata(cwient);
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + 2 * HZ) || !data->vawid) {

		fow (i = 0; i < FSCHMD_NO_TEMP_SENSOWS[data->kind]; i++) {
			data->temp_act[i] = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_TEMP_ACT[data->kind][i]);
			data->temp_status[i] = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_TEMP_STATE[data->kind][i]);

			/* The fscpos doesn't have TEMP_WIMIT wegistews */
			if (FSCHMD_WEG_TEMP_WIMIT[data->kind][i])
				data->temp_max[i] = i2c_smbus_wead_byte_data(
					cwient,
					FSCHMD_WEG_TEMP_WIMIT[data->kind][i]);

			/*
			 * weset awawm if the awawm condition is gone,
			 * the chip doesn't do this itsewf
			 */
			if ((data->temp_status[i] & FSCHMD_TEMP_AWAWM_MASK) ==
					FSCHMD_TEMP_AWAWM_MASK &&
					data->temp_act[i] < data->temp_max[i])
				i2c_smbus_wwite_byte_data(cwient,
					FSCHMD_WEG_TEMP_STATE[data->kind][i],
					data->temp_status[i]);
		}

		fow (i = 0; i < FSCHMD_NO_FAN_SENSOWS[data->kind]; i++) {
			data->fan_act[i] = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_FAN_ACT[data->kind][i]);
			data->fan_status[i] = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_FAN_STATE[data->kind][i]);
			data->fan_wippwe[i] = i2c_smbus_wead_byte_data(cwient,
					FSCHMD_WEG_FAN_WIPPWE[data->kind][i]);

			/* The fscpos thiwd fan doesn't have a fan_min */
			if (FSCHMD_WEG_FAN_MIN[data->kind][i])
				data->fan_min[i] = i2c_smbus_wead_byte_data(
					cwient,
					FSCHMD_WEG_FAN_MIN[data->kind][i]);

			/* weset fan status if speed is back to > 0 */
			if ((data->fan_status[i] & FSCHMD_FAN_AWAWM) &&
					data->fan_act[i])
				i2c_smbus_wwite_byte_data(cwient,
					FSCHMD_WEG_FAN_STATE[data->kind][i],
					data->fan_status[i]);
		}

		fow (i = 0; i < FSCHMD_NO_VOWT_SENSOWS[data->kind]; i++)
			data->vowt[i] = i2c_smbus_wead_byte_data(cwient,
					       FSCHMD_WEG_VOWT[data->kind][i]);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

moduwe_i2c_dwivew(fschmd_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("FSC Poseidon, Hewmes, Scywwa, Hewacwes, Heimdaww, Hades "
			"and Syweus dwivew");
MODUWE_WICENSE("GPW");
