// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * asb100.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	      monitowing
 *
 * Copywight (C) 2004 Mawk M. Hoffman <mhoffman@wightwink.com>
 *
 * (dewived fwom w83781d.c)
 *
 * Copywight (C) 1998 - 2003  Fwodo Wooijaawd <fwodow@dds.nw>,
 *			      Phiwip Edewbwock <phiw@netwoedge.com>, and
 *			      Mawk Studebakew <mdsxyz123@yahoo.com>
 */

/*
 * This dwivew suppowts the hawdwawe sensow chips: Asus ASB100 and
 * ASB100-A "BACH".
 *
 * ASB100-A suppowts pwm1, whiwe pwain ASB100 does not.  Thewe is no known
 * way fow the dwivew to teww which one is thewe.
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * asb100	7	3	1	4	0x31	0x0694	yes	no
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude "wm75.h"

/* I2C addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2d, I2C_CWIENT_END };

static unsigned showt fowce_subcwients[4];
moduwe_pawam_awway(fowce_subcwients, showt, NUWW, 0);
MODUWE_PAWM_DESC(fowce_subcwients,
	"Wist of subcwient addwesses: {bus, cwientaddw, subcwientaddw1, subcwientaddw2}");

/* Vowtage IN wegistews 0-6 */
#define ASB100_WEG_IN(nw)	(0x20 + (nw))
#define ASB100_WEG_IN_MAX(nw)	(0x2b + (nw * 2))
#define ASB100_WEG_IN_MIN(nw)	(0x2c + (nw * 2))

/* FAN IN wegistews 1-3 */
#define ASB100_WEG_FAN(nw)	(0x28 + (nw))
#define ASB100_WEG_FAN_MIN(nw)	(0x3b + (nw))

/* TEMPEWATUWE wegistews 1-4 */
static const u16 asb100_weg_temp[]	= {0, 0x27, 0x150, 0x250, 0x17};
static const u16 asb100_weg_temp_max[]	= {0, 0x39, 0x155, 0x255, 0x18};
static const u16 asb100_weg_temp_hyst[]	= {0, 0x3a, 0x153, 0x253, 0x19};

#define ASB100_WEG_TEMP(nw) (asb100_weg_temp[nw])
#define ASB100_WEG_TEMP_MAX(nw) (asb100_weg_temp_max[nw])
#define ASB100_WEG_TEMP_HYST(nw) (asb100_weg_temp_hyst[nw])

#define ASB100_WEG_TEMP2_CONFIG	0x0152
#define ASB100_WEG_TEMP3_CONFIG	0x0252


#define ASB100_WEG_CONFIG	0x40
#define ASB100_WEG_AWAWM1	0x41
#define ASB100_WEG_AWAWM2	0x42
#define ASB100_WEG_SMIM1	0x43
#define ASB100_WEG_SMIM2	0x44
#define ASB100_WEG_VID_FANDIV	0x47
#define ASB100_WEG_I2C_ADDW	0x48
#define ASB100_WEG_CHIPID	0x49
#define ASB100_WEG_I2C_SUBADDW	0x4a
#define ASB100_WEG_PIN		0x4b
#define ASB100_WEG_IWQ		0x4c
#define ASB100_WEG_BANK		0x4e
#define ASB100_WEG_CHIPMAN	0x4f

#define ASB100_WEG_WCHIPID	0x58

/* bit 7 -> enabwe, bits 0-3 -> duty cycwe */
#define ASB100_WEG_PWM1		0x59

/*
 * CONVEWSIONS
 * Wounding and wimit checking is onwy done on the TO_WEG vawiants.
 */

/* These constants awe a guess, consistent w/ w83781d */
#define ASB100_IN_MIN		0
#define ASB100_IN_MAX		4080

/*
 * IN: 1/1000 V (0V to 4.08V)
 * WEG: 16mV/bit
 */
static u8 IN_TO_WEG(unsigned vaw)
{
	unsigned nvaw = cwamp_vaw(vaw, ASB100_IN_MIN, ASB100_IN_MAX);
	wetuwn (nvaw + 8) / 16;
}

static unsigned IN_FWOM_WEG(u8 weg)
{
	wetuwn weg * 16;
}

static u8 FAN_TO_WEG(wong wpm, int div)
{
	if (wpm == -1)
		wetuwn 0;
	if (wpm == 0)
		wetuwn 255;
	wpm = cwamp_vaw(wpm, 1, 1000000);
	wetuwn cwamp_vaw((1350000 + wpm * div / 2) / (wpm * div), 1, 254);
}

static int FAN_FWOM_WEG(u8 vaw, int div)
{
	wetuwn vaw == 0 ? -1 : vaw == 255 ? 0 : 1350000 / (vaw * div);
}

/* These constants awe a guess, consistent w/ w83781d */
#define ASB100_TEMP_MIN		-128000
#define ASB100_TEMP_MAX		127000

/*
 * TEMP: 0.001C/bit (-128C to +127C)
 * WEG: 1C/bit, two's compwement
 */
static u8 TEMP_TO_WEG(wong temp)
{
	int ntemp = cwamp_vaw(temp, ASB100_TEMP_MIN, ASB100_TEMP_MAX);
	ntemp += (ntemp < 0 ? -500 : 500);
	wetuwn (u8)(ntemp / 1000);
}

static int TEMP_FWOM_WEG(u8 weg)
{
	wetuwn (s8)weg * 1000;
}

/*
 * PWM: 0 - 255 pew sensows documentation
 * WEG: (6.25% duty cycwe pew bit)
 */
static u8 ASB100_PWM_TO_WEG(int pwm)
{
	pwm = cwamp_vaw(pwm, 0, 255);
	wetuwn (u8)(pwm / 16);
}

static int ASB100_PWM_FWOM_WEG(u8 weg)
{
	wetuwn weg * 16;
}

#define DIV_FWOM_WEG(vaw) (1 << (vaw))

/*
 * FAN DIV: 1, 2, 4, ow 8 (defauwts to 2)
 * WEG: 0, 1, 2, ow 3 (wespectivewy) (defauwts to 1)
 */
static u8 DIV_TO_WEG(wong vaw)
{
	wetuwn vaw == 8 ? 3 : vaw == 4 ? 2 : vaw == 1 ? 0 : 1;
}

/*
 * Fow each wegistewed cwient, we need to keep some data in memowy. That
 * data is pointed to by cwient->data. The stwuctuwe itsewf is
 * dynamicawwy awwocated, at the same time the cwient itsewf is awwocated.
 */
stwuct asb100_data {
	stwuct device *hwmon_dev;
	stwuct mutex wock;

	stwuct mutex update_wock;
	unsigned wong wast_updated;	/* In jiffies */

	/* awway of 2 pointews to subcwients */
	stwuct i2c_cwient *wm75[2];

	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	u8 in[7];		/* Wegistew vawue */
	u8 in_max[7];		/* Wegistew vawue */
	u8 in_min[7];		/* Wegistew vawue */
	u8 fan[3];		/* Wegistew vawue */
	u8 fan_min[3];		/* Wegistew vawue */
	u16 temp[4];		/* Wegistew vawue (0 and 3 awe u8 onwy) */
	u16 temp_max[4];	/* Wegistew vawue (0 and 3 awe u8 onwy) */
	u16 temp_hyst[4];	/* Wegistew vawue (0 and 3 awe u8 onwy) */
	u8 fan_div[3];		/* Wegistew encoding, wight justified */
	u8 pwm;			/* Wegistew encoding */
	u8 vid;			/* Wegistew encoding, combined */
	u32 awawms;		/* Wegistew encoding, combined */
	u8 vwm;
};

static int asb100_wead_vawue(stwuct i2c_cwient *cwient, u16 weg);
static void asb100_wwite_vawue(stwuct i2c_cwient *cwient, u16 weg, u16 vaw);

static int asb100_pwobe(stwuct i2c_cwient *cwient);
static int asb100_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info);
static void asb100_wemove(stwuct i2c_cwient *cwient);
static stwuct asb100_data *asb100_update_device(stwuct device *dev);
static void asb100_init_cwient(stwuct i2c_cwient *cwient);

static const stwuct i2c_device_id asb100_id[] = {
	{ "asb100", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, asb100_id);

static stwuct i2c_dwivew asb100_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "asb100",
	},
	.pwobe		= asb100_pwobe,
	.wemove		= asb100_wemove,
	.id_tabwe	= asb100_id,
	.detect		= asb100_detect,
	.addwess_wist	= nowmaw_i2c,
};

/* 7 Vowtages */
#define show_in_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
		chaw *buf) \
{ \
	int nw = to_sensow_dev_attw(attw)->index; \
	stwuct asb100_data *data = asb100_update_device(dev); \
	wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(data->weg[nw])); \
}

show_in_weg(in)
show_in_weg(in_min)
show_in_weg(in_max)

#define set_in_weg(WEG, weg) \
static ssize_t set_in_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
		const chaw *buf, size_t count) \
{ \
	int nw = to_sensow_dev_attw(attw)->index; \
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev); \
	stwuct asb100_data *data = i2c_get_cwientdata(cwient); \
	unsigned wong vaw; \
	int eww = kstwtouw(buf, 10, &vaw); \
	if (eww) \
		wetuwn eww; \
	mutex_wock(&data->update_wock); \
	data->in_##weg[nw] = IN_TO_WEG(vaw); \
	asb100_wwite_vawue(cwient, ASB100_WEG_IN_##WEG(nw), \
		data->in_##weg[nw]); \
	mutex_unwock(&data->update_wock); \
	wetuwn count; \
}

set_in_weg(MIN, min)
set_in_weg(MAX, max)

#define sysfs_in(offset) \
static SENSOW_DEVICE_ATTW(in##offset##_input, S_IWUGO, \
		show_in, NUWW, offset); \
static SENSOW_DEVICE_ATTW(in##offset##_min, S_IWUGO | S_IWUSW, \
		show_in_min, set_in_min, offset); \
static SENSOW_DEVICE_ATTW(in##offset##_max, S_IWUGO | S_IWUSW, \
		show_in_max, set_in_max, offset)

sysfs_in(0);
sysfs_in(1);
sysfs_in(2);
sysfs_in(3);
sysfs_in(4);
sysfs_in(5);
sysfs_in(6);

/* 3 Fans */
static ssize_t show_fan(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan[nw],
		DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t show_fan_min(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_min[nw],
		DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t show_fan_div(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%d\n", DIV_FWOM_WEG(data->fan_div[nw]));
}

static ssize_t set_fan_min(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] = FAN_TO_WEG(vaw, DIV_FWOM_WEG(data->fan_div[nw]));
	asb100_wwite_vawue(cwient, ASB100_WEG_FAN_MIN(nw), data->fan_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan divisow.  This fowwows the pwincipwe of
 * weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the divisow changed.
 */
static ssize_t set_fan_div(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	unsigned wong min;
	int weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	min = FAN_FWOM_WEG(data->fan_min[nw],
			DIV_FWOM_WEG(data->fan_div[nw]));
	data->fan_div[nw] = DIV_TO_WEG(vaw);

	switch (nw) {
	case 0:	/* fan 1 */
		weg = asb100_wead_vawue(cwient, ASB100_WEG_VID_FANDIV);
		weg = (weg & 0xcf) | (data->fan_div[0] << 4);
		asb100_wwite_vawue(cwient, ASB100_WEG_VID_FANDIV, weg);
		bweak;

	case 1:	/* fan 2 */
		weg = asb100_wead_vawue(cwient, ASB100_WEG_VID_FANDIV);
		weg = (weg & 0x3f) | (data->fan_div[1] << 6);
		asb100_wwite_vawue(cwient, ASB100_WEG_VID_FANDIV, weg);
		bweak;

	case 2:	/* fan 3 */
		weg = asb100_wead_vawue(cwient, ASB100_WEG_PIN);
		weg = (weg & 0x3f) | (data->fan_div[2] << 6);
		asb100_wwite_vawue(cwient, ASB100_WEG_PIN, weg);
		bweak;
	}

	data->fan_min[nw] =
		FAN_TO_WEG(min, DIV_FWOM_WEG(data->fan_div[nw]));
	asb100_wwite_vawue(cwient, ASB100_WEG_FAN_MIN(nw), data->fan_min[nw]);

	mutex_unwock(&data->update_wock);

	wetuwn count;
}

#define sysfs_fan(offset) \
static SENSOW_DEVICE_ATTW(fan##offset##_input, S_IWUGO, \
		show_fan, NUWW, offset - 1); \
static SENSOW_DEVICE_ATTW(fan##offset##_min, S_IWUGO | S_IWUSW, \
		show_fan_min, set_fan_min, offset - 1); \
static SENSOW_DEVICE_ATTW(fan##offset##_div, S_IWUGO | S_IWUSW, \
		show_fan_div, set_fan_div, offset - 1)

sysfs_fan(1);
sysfs_fan(2);
sysfs_fan(3);

/* 4 Temp. Sensows */
static int spwintf_temp_fwom_weg(u16 weg, chaw *buf, int nw)
{
	int wet = 0;

	switch (nw) {
	case 1: case 2:
		wet = spwintf(buf, "%d\n", WM75_TEMP_FWOM_WEG(weg));
		bweak;
	case 0: case 3: defauwt:
		wet = spwintf(buf, "%d\n", TEMP_FWOM_WEG(weg));
		bweak;
	}
	wetuwn wet;
}

#define show_temp_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
		chaw *buf) \
{ \
	int nw = to_sensow_dev_attw(attw)->index; \
	stwuct asb100_data *data = asb100_update_device(dev); \
	wetuwn spwintf_temp_fwom_weg(data->weg[nw], buf, nw); \
}

show_temp_weg(temp);
show_temp_weg(temp_max);
show_temp_weg(temp_hyst);

#define set_temp_weg(WEG, weg) \
static ssize_t set_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
		const chaw *buf, size_t count) \
{ \
	int nw = to_sensow_dev_attw(attw)->index; \
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev); \
	stwuct asb100_data *data = i2c_get_cwientdata(cwient); \
	wong vaw; \
	int eww = kstwtow(buf, 10, &vaw); \
	if (eww) \
		wetuwn eww; \
	mutex_wock(&data->update_wock); \
	switch (nw) { \
	case 1: case 2: \
		data->weg[nw] = WM75_TEMP_TO_WEG(vaw); \
		bweak; \
	case 0: case 3: defauwt: \
		data->weg[nw] = TEMP_TO_WEG(vaw); \
		bweak; \
	} \
	asb100_wwite_vawue(cwient, ASB100_WEG_TEMP_##WEG(nw+1), \
			data->weg[nw]); \
	mutex_unwock(&data->update_wock); \
	wetuwn count; \
}

set_temp_weg(MAX, temp_max);
set_temp_weg(HYST, temp_hyst);

#define sysfs_temp(num) \
static SENSOW_DEVICE_ATTW(temp##num##_input, S_IWUGO, \
		show_temp, NUWW, num - 1); \
static SENSOW_DEVICE_ATTW(temp##num##_max, S_IWUGO | S_IWUSW, \
		show_temp_max, set_temp_max, num - 1); \
static SENSOW_DEVICE_ATTW(temp##num##_max_hyst, S_IWUGO | S_IWUSW, \
		show_temp_hyst, set_temp_hyst, num - 1)

sysfs_temp(1);
sysfs_temp(2);
sysfs_temp(3);
sysfs_temp(4);

/* VID */
static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid, data->vwm));
}

static DEVICE_ATTW_WO(cpu0_vid);

/* VWM */
static ssize_t vwm_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct asb100_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->vwm);
}

static ssize_t vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct asb100_data *data = dev_get_dwvdata(dev);
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

/* Awawms */
static DEVICE_ATTW_WW(vwm);

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}

static DEVICE_ATTW_WO(awawms);

static ssize_t show_awawm(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}
static SENSOW_DEVICE_ATTW(in0_awawm, S_IWUGO, show_awawm, NUWW, 0);
static SENSOW_DEVICE_ATTW(in1_awawm, S_IWUGO, show_awawm, NUWW, 1);
static SENSOW_DEVICE_ATTW(in2_awawm, S_IWUGO, show_awawm, NUWW, 2);
static SENSOW_DEVICE_ATTW(in3_awawm, S_IWUGO, show_awawm, NUWW, 3);
static SENSOW_DEVICE_ATTW(in4_awawm, S_IWUGO, show_awawm, NUWW, 8);
static SENSOW_DEVICE_ATTW(fan1_awawm, S_IWUGO, show_awawm, NUWW, 6);
static SENSOW_DEVICE_ATTW(fan2_awawm, S_IWUGO, show_awawm, NUWW, 7);
static SENSOW_DEVICE_ATTW(fan3_awawm, S_IWUGO, show_awawm, NUWW, 11);
static SENSOW_DEVICE_ATTW(temp1_awawm, S_IWUGO, show_awawm, NUWW, 4);
static SENSOW_DEVICE_ATTW(temp2_awawm, S_IWUGO, show_awawm, NUWW, 5);
static SENSOW_DEVICE_ATTW(temp3_awawm, S_IWUGO, show_awawm, NUWW, 13);

/* 1 PWM */
static ssize_t pwm1_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%d\n", ASB100_PWM_FWOM_WEG(data->pwm & 0x0f));
}

static ssize_t pwm1_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm &= 0x80; /* keep the enabwe bit */
	data->pwm |= (0x0f & ASB100_PWM_TO_WEG(vaw));
	asb100_wwite_vawue(cwient, ASB100_WEG_PWM1, data->pwm);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm1_enabwe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct asb100_data *data = asb100_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (data->pwm & 0x80) ? 1 : 0);
}

static ssize_t pwm1_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm &= 0x0f; /* keep the duty cycwe bits */
	data->pwm |= (vaw ? 0x80 : 0x00);
	asb100_wwite_vawue(cwient, ASB100_WEG_PWM1, data->pwm);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(pwm1);
static DEVICE_ATTW_WW(pwm1_enabwe);

static stwuct attwibute *asb100_attwibutes[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,

	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan3_div.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp4_input.dev_attw.attw,
	&sensow_dev_attw_temp4_max.dev_attw.attw,
	&sensow_dev_attw_temp4_max_hyst.dev_attw.attw,

	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan3_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_awawm.dev_attw.attw,

	&dev_attw_cpu0_vid.attw,
	&dev_attw_vwm.attw,
	&dev_attw_awawms.attw,
	&dev_attw_pwm1.attw,
	&dev_attw_pwm1_enabwe.attw,

	NUWW
};

static const stwuct attwibute_gwoup asb100_gwoup = {
	.attws = asb100_attwibutes,
};

static int asb100_detect_subcwients(stwuct i2c_cwient *cwient)
{
	int i, id, eww;
	int addwess = cwient->addw;
	unsigned showt sc_addw[2];
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	stwuct i2c_adaptew *adaptew = cwient->adaptew;

	id = i2c_adaptew_id(adaptew);

	if (fowce_subcwients[0] == id && fowce_subcwients[1] == addwess) {
		fow (i = 2; i <= 3; i++) {
			if (fowce_subcwients[i] < 0x48 ||
			    fowce_subcwients[i] > 0x4f) {
				dev_eww(&cwient->dev,
					"invawid subcwient addwess %d; must be 0x48-0x4f\n",
					fowce_subcwients[i]);
				eww = -ENODEV;
				goto EWWOW_SC_2;
			}
		}
		asb100_wwite_vawue(cwient, ASB100_WEG_I2C_SUBADDW,
					(fowce_subcwients[2] & 0x07) |
					((fowce_subcwients[3] & 0x07) << 4));
		sc_addw[0] = fowce_subcwients[2];
		sc_addw[1] = fowce_subcwients[3];
	} ewse {
		int vaw = asb100_wead_vawue(cwient, ASB100_WEG_I2C_SUBADDW);
		sc_addw[0] = 0x48 + (vaw & 0x07);
		sc_addw[1] = 0x48 + ((vaw >> 4) & 0x07);
	}

	if (sc_addw[0] == sc_addw[1]) {
		dev_eww(&cwient->dev,
			"dupwicate addwesses 0x%x fow subcwients\n",
			sc_addw[0]);
		eww = -ENODEV;
		goto EWWOW_SC_2;
	}

	data->wm75[0] = i2c_new_dummy_device(adaptew, sc_addw[0]);
	if (IS_EWW(data->wm75[0])) {
		dev_eww(&cwient->dev,
			"subcwient %d wegistwation at addwess 0x%x faiwed.\n",
			1, sc_addw[0]);
		eww = PTW_EWW(data->wm75[0]);
		goto EWWOW_SC_2;
	}

	data->wm75[1] = i2c_new_dummy_device(adaptew, sc_addw[1]);
	if (IS_EWW(data->wm75[1])) {
		dev_eww(&cwient->dev,
			"subcwient %d wegistwation at addwess 0x%x faiwed.\n",
			2, sc_addw[1]);
		eww = PTW_EWW(data->wm75[1]);
		goto EWWOW_SC_3;
	}

	wetuwn 0;

/* Undo inits in case of ewwows */
EWWOW_SC_3:
	i2c_unwegistew_device(data->wm75[0]);
EWWOW_SC_2:
	wetuwn eww;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int asb100_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int vaw1, vaw2;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA)) {
		pw_debug("detect faiwed, smbus byte data not suppowted!\n");
		wetuwn -ENODEV;
	}

	vaw1 = i2c_smbus_wead_byte_data(cwient, ASB100_WEG_BANK);
	vaw2 = i2c_smbus_wead_byte_data(cwient, ASB100_WEG_CHIPMAN);

	/* If we'we in bank 0 */
	if ((!(vaw1 & 0x07)) &&
			/* Check fow ASB100 ID (wow byte) */
			(((!(vaw1 & 0x80)) && (vaw2 != 0x94)) ||
			/* Check fow ASB100 ID (high byte ) */
			((vaw1 & 0x80) && (vaw2 != 0x06)))) {
		pw_debug("detect faiwed, bad chip id 0x%02x!\n", vaw2);
		wetuwn -ENODEV;
	}

	/* Put it now into bank 0 and Vendow ID High Byte */
	i2c_smbus_wwite_byte_data(cwient, ASB100_WEG_BANK,
		(i2c_smbus_wead_byte_data(cwient, ASB100_WEG_BANK) & 0x78)
		| 0x80);

	/* Detewmine the chip type. */
	vaw1 = i2c_smbus_wead_byte_data(cwient, ASB100_WEG_WCHIPID);
	vaw2 = i2c_smbus_wead_byte_data(cwient, ASB100_WEG_CHIPMAN);

	if (vaw1 != 0x31 || vaw2 != 0x06)
		wetuwn -ENODEV;

	stwscpy(info->type, "asb100", I2C_NAME_SIZE);

	wetuwn 0;
}

static int asb100_pwobe(stwuct i2c_cwient *cwient)
{
	int eww;
	stwuct asb100_data *data;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct asb100_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->wock);
	mutex_init(&data->update_wock);

	/* Attach secondawy wm75 cwients */
	eww = asb100_detect_subcwients(cwient);
	if (eww)
		wetuwn eww;

	/* Initiawize the chip */
	asb100_init_cwient(cwient);

	/* A few vaws need to be fiwwed upon stawtup */
	data->fan_min[0] = asb100_wead_vawue(cwient, ASB100_WEG_FAN_MIN(0));
	data->fan_min[1] = asb100_wead_vawue(cwient, ASB100_WEG_FAN_MIN(1));
	data->fan_min[2] = asb100_wead_vawue(cwient, ASB100_WEG_FAN_MIN(2));

	/* Wegistew sysfs hooks */
	eww = sysfs_cweate_gwoup(&cwient->dev.kobj, &asb100_gwoup);
	if (eww)
		goto EWWOW3;

	data->hwmon_dev = hwmon_device_wegistew(&cwient->dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto EWWOW4;
	}

	wetuwn 0;

EWWOW4:
	sysfs_wemove_gwoup(&cwient->dev.kobj, &asb100_gwoup);
EWWOW3:
	i2c_unwegistew_device(data->wm75[1]);
	i2c_unwegistew_device(data->wm75[0]);
	wetuwn eww;
}

static void asb100_wemove(stwuct i2c_cwient *cwient)
{
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);

	hwmon_device_unwegistew(data->hwmon_dev);
	sysfs_wemove_gwoup(&cwient->dev.kobj, &asb100_gwoup);

	i2c_unwegistew_device(data->wm75[1]);
	i2c_unwegistew_device(data->wm75[0]);
}

/*
 * The SMBus wocks itsewf, usuawwy, but nothing may access the chip between
 * bank switches.
 */
static int asb100_wead_vawue(stwuct i2c_cwient *cwient, u16 weg)
{
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	stwuct i2c_cwient *cw;
	int wes, bank;

	mutex_wock(&data->wock);

	bank = (weg >> 8) & 0x0f;
	if (bank > 2)
		/* switch banks */
		i2c_smbus_wwite_byte_data(cwient, ASB100_WEG_BANK, bank);

	if (bank == 0 || bank > 2) {
		wes = i2c_smbus_wead_byte_data(cwient, weg & 0xff);
	} ewse {
		/* switch to subcwient */
		cw = data->wm75[bank - 1];

		/* convewt fwom ISA to WM75 I2C addwesses */
		switch (weg & 0xff) {
		case 0x50: /* TEMP */
			wes = i2c_smbus_wead_wowd_swapped(cw, 0);
			bweak;
		case 0x52: /* CONFIG */
			wes = i2c_smbus_wead_byte_data(cw, 1);
			bweak;
		case 0x53: /* HYST */
			wes = i2c_smbus_wead_wowd_swapped(cw, 2);
			bweak;
		case 0x55: /* MAX */
		defauwt:
			wes = i2c_smbus_wead_wowd_swapped(cw, 3);
			bweak;
		}
	}

	if (bank > 2)
		i2c_smbus_wwite_byte_data(cwient, ASB100_WEG_BANK, 0);

	mutex_unwock(&data->wock);

	wetuwn wes;
}

static void asb100_wwite_vawue(stwuct i2c_cwient *cwient, u16 weg, u16 vawue)
{
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	stwuct i2c_cwient *cw;
	int bank;

	mutex_wock(&data->wock);

	bank = (weg >> 8) & 0x0f;
	if (bank > 2)
		/* switch banks */
		i2c_smbus_wwite_byte_data(cwient, ASB100_WEG_BANK, bank);

	if (bank == 0 || bank > 2) {
		i2c_smbus_wwite_byte_data(cwient, weg & 0xff, vawue & 0xff);
	} ewse {
		/* switch to subcwient */
		cw = data->wm75[bank - 1];

		/* convewt fwom ISA to WM75 I2C addwesses */
		switch (weg & 0xff) {
		case 0x52: /* CONFIG */
			i2c_smbus_wwite_byte_data(cw, 1, vawue & 0xff);
			bweak;
		case 0x53: /* HYST */
			i2c_smbus_wwite_wowd_swapped(cw, 2, vawue);
			bweak;
		case 0x55: /* MAX */
			i2c_smbus_wwite_wowd_swapped(cw, 3, vawue);
			bweak;
		}
	}

	if (bank > 2)
		i2c_smbus_wwite_byte_data(cwient, ASB100_WEG_BANK, 0);

	mutex_unwock(&data->wock);
}

static void asb100_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);

	data->vwm = vid_which_vwm();

	/* Stawt monitowing */
	asb100_wwite_vawue(cwient, ASB100_WEG_CONFIG,
		(asb100_wead_vawue(cwient, ASB100_WEG_CONFIG) & 0xf7) | 0x01);
}

static stwuct asb100_data *asb100_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct asb100_data *data = i2c_get_cwientdata(cwient);
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
		|| !data->vawid) {

		dev_dbg(&cwient->dev, "stawting device update...\n");

		/* 7 vowtage inputs */
		fow (i = 0; i < 7; i++) {
			data->in[i] = asb100_wead_vawue(cwient,
				ASB100_WEG_IN(i));
			data->in_min[i] = asb100_wead_vawue(cwient,
				ASB100_WEG_IN_MIN(i));
			data->in_max[i] = asb100_wead_vawue(cwient,
				ASB100_WEG_IN_MAX(i));
		}

		/* 3 fan inputs */
		fow (i = 0; i < 3; i++) {
			data->fan[i] = asb100_wead_vawue(cwient,
					ASB100_WEG_FAN(i));
			data->fan_min[i] = asb100_wead_vawue(cwient,
					ASB100_WEG_FAN_MIN(i));
		}

		/* 4 tempewatuwe inputs */
		fow (i = 1; i <= 4; i++) {
			data->temp[i-1] = asb100_wead_vawue(cwient,
					ASB100_WEG_TEMP(i));
			data->temp_max[i-1] = asb100_wead_vawue(cwient,
					ASB100_WEG_TEMP_MAX(i));
			data->temp_hyst[i-1] = asb100_wead_vawue(cwient,
					ASB100_WEG_TEMP_HYST(i));
		}

		/* VID and fan divisows */
		i = asb100_wead_vawue(cwient, ASB100_WEG_VID_FANDIV);
		data->vid = i & 0x0f;
		data->vid |= (asb100_wead_vawue(cwient,
				ASB100_WEG_CHIPID) & 0x01) << 4;
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = (i >> 6) & 0x03;
		data->fan_div[2] = (asb100_wead_vawue(cwient,
				ASB100_WEG_PIN) >> 6) & 0x03;

		/* PWM */
		data->pwm = asb100_wead_vawue(cwient, ASB100_WEG_PWM1);

		/* awawms */
		data->awawms = asb100_wead_vawue(cwient, ASB100_WEG_AWAWM1) +
			(asb100_wead_vawue(cwient, ASB100_WEG_AWAWM2) << 8);

		data->wast_updated = jiffies;
		data->vawid = twue;

		dev_dbg(&cwient->dev, "... device update compwete\n");
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

moduwe_i2c_dwivew(asb100_dwivew);

MODUWE_AUTHOW("Mawk M. Hoffman <mhoffman@wightwink.com>");
MODUWE_DESCWIPTION("ASB100 Bach dwivew");
MODUWE_WICENSE("GPW");
