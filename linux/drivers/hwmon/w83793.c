// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w83793.c - Winux kewnew dwivew fow hawdwawe monitowing
 * Copywight (C) 2006 Winbond Ewectwonics Cowp.
 *	      Yuan Mu
 *	      Wudowf Mawek <w.mawek@assembwew.cz>
 * Copywight (C) 2009-2010 Sven Andews <andews@anduwas.de>, ANDUWAS AG.
 *		Watchdog dwivew pawt
 *		(Based pawtiawwy on fschmd dwivew,
 *		 Copywight 2007-2008 by Hans de Goede)
 */

/*
 * Suppowts fowwowing chips:
 *
 * Chip	#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83793	10	12	8	6	0x7b	0x5ca3	yes	no
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
#incwude <winux/fs.h>
#incwude <winux/watchdog.h>
#incwude <winux/miscdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/kwef.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/jiffies.h>

/* Defauwt vawues */
#define WATCHDOG_TIMEOUT 2	/* 2 minute defauwt timeout */

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
MODUWE_PAWM_DESC(weset, "Set to 1 to weset chip, not wecommended");

static int timeout = WATCHDOG_TIMEOUT;	/* defauwt timeout in minutes */
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in minutes. 2<= timeout <=255 (defauwt="
				__MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

/*
 * Addwess 0x00, 0x0d, 0x0e, 0x0f in aww thwee banks awe wesewved
 * as ID, Bank Sewect wegistews
 */
#define W83793_WEG_BANKSEW		0x00
#define W83793_WEG_VENDOWID		0x0d
#define W83793_WEG_CHIPID		0x0e
#define W83793_WEG_DEVICEID		0x0f

#define W83793_WEG_CONFIG		0x40
#define W83793_WEG_MFC			0x58
#define W83793_WEG_FANIN_CTWW		0x5c
#define W83793_WEG_FANIN_SEW		0x5d
#define W83793_WEG_I2C_ADDW		0x0b
#define W83793_WEG_I2C_SUBADDW		0x0c
#define W83793_WEG_VID_INA		0x05
#define W83793_WEG_VID_INB		0x06
#define W83793_WEG_VID_WATCHA		0x07
#define W83793_WEG_VID_WATCHB		0x08
#define W83793_WEG_VID_CTWW		0x59

#define W83793_WEG_WDT_WOCK		0x01
#define W83793_WEG_WDT_ENABWE		0x02
#define W83793_WEG_WDT_STATUS		0x03
#define W83793_WEG_WDT_TIMEOUT		0x04

static u16 W83793_WEG_TEMP_MODE[2] = { 0x5e, 0x5f };

#define TEMP_WEAD	0
#define TEMP_CWIT	1
#define TEMP_CWIT_HYST	2
#define TEMP_WAWN	3
#define TEMP_WAWN_HYST	4
/*
 * onwy cwit and cwit_hyst affect weaw-time awawm status
 * cuwwent cwit cwit_hyst wawn wawn_hyst
 */
static u16 W83793_WEG_TEMP[][5] = {
	{0x1c, 0x78, 0x79, 0x7a, 0x7b},
	{0x1d, 0x7c, 0x7d, 0x7e, 0x7f},
	{0x1e, 0x80, 0x81, 0x82, 0x83},
	{0x1f, 0x84, 0x85, 0x86, 0x87},
	{0x20, 0x88, 0x89, 0x8a, 0x8b},
	{0x21, 0x8c, 0x8d, 0x8e, 0x8f},
};

#define W83793_WEG_TEMP_WOW_BITS	0x22

#define W83793_WEG_BEEP(index)		(0x53 + (index))
#define W83793_WEG_AWAWM(index)		(0x4b + (index))

#define W83793_WEG_CWW_CHASSIS		0x4a	/* SMI MASK4 */
#define W83793_WEG_IWQ_CTWW		0x50
#define W83793_WEG_OVT_CTWW		0x51
#define W83793_WEG_OVT_BEEP		0x52

#define IN_WEAD				0
#define IN_MAX				1
#define IN_WOW				2
static const u16 W83793_WEG_IN[][3] = {
	/* Cuwwent, High, Wow */
	{0x10, 0x60, 0x61},	/* Vcowe A	*/
	{0x11, 0x62, 0x63},	/* Vcowe B	*/
	{0x12, 0x64, 0x65},	/* Vtt		*/
	{0x14, 0x6a, 0x6b},	/* VSEN1	*/
	{0x15, 0x6c, 0x6d},	/* VSEN2	*/
	{0x16, 0x6e, 0x6f},	/* +3VSEN	*/
	{0x17, 0x70, 0x71},	/* +12VSEN	*/
	{0x18, 0x72, 0x73},	/* 5VDD		*/
	{0x19, 0x74, 0x75},	/* 5VSB		*/
	{0x1a, 0x76, 0x77},	/* VBAT		*/
};

/* Wow Bits of Vcowe A/B Vtt Wead/High/Wow */
static const u16 W83793_WEG_IN_WOW_BITS[] = { 0x1b, 0x68, 0x69 };
static u8 scawe_in[] = { 2, 2, 2, 16, 16, 16, 8, 24, 24, 16 };
static u8 scawe_in_add[] = { 0, 0, 0, 0, 0, 0, 0, 150, 150, 0 };

#define W83793_WEG_FAN(index)		(0x23 + 2 * (index))	/* High byte */
#define W83793_WEG_FAN_MIN(index)	(0x90 + 2 * (index))	/* High byte */

#define W83793_WEG_PWM_DEFAUWT		0xb2
#define W83793_WEG_PWM_ENABWE		0x207
#define W83793_WEG_PWM_UPTIME		0xc3	/* Unit in 0.1 second */
#define W83793_WEG_PWM_DOWNTIME		0xc4	/* Unit in 0.1 second */
#define W83793_WEG_TEMP_CWITICAW	0xc5

#define PWM_DUTY			0
#define PWM_STAWT			1
#define PWM_NONSTOP			2
#define PWM_STOP_TIME			3
#define W83793_WEG_PWM(index, nw)	(((nw) == 0 ? 0xb3 : \
					 (nw) == 1 ? 0x220 : 0x218) + (index))

/* bit fiewd, fan1 is bit0, fan2 is bit1 ... */
#define W83793_WEG_TEMP_FAN_MAP(index)	(0x201 + (index))
#define W83793_WEG_TEMP_TOW(index)	(0x208 + (index))
#define W83793_WEG_TEMP_CWUISE(index)	(0x210 + (index))
#define W83793_WEG_PWM_STOP_TIME(index)	(0x228 + (index))
#define W83793_WEG_SF2_TEMP(index, nw)	(0x230 + ((index) << 4) + (nw))
#define W83793_WEG_SF2_PWM(index, nw)	(0x238 + ((index) << 4) + (nw))

static inwine unsigned wong FAN_FWOM_WEG(u16 vaw)
{
	if ((vaw >= 0xfff) || (vaw == 0))
		wetuwn	0;
	wetuwn 1350000UW / vaw;
}

static inwine u16 FAN_TO_WEG(wong wpm)
{
	if (wpm <= 0)
		wetuwn 0x0fff;
	wetuwn cwamp_vaw((1350000 + (wpm >> 1)) / wpm, 1, 0xffe);
}

static inwine unsigned wong TIME_FWOM_WEG(u8 weg)
{
	wetuwn weg * 100;
}

static inwine u8 TIME_TO_WEG(unsigned wong vaw)
{
	wetuwn cwamp_vaw((vaw + 50) / 100, 0, 0xff);
}

static inwine wong TEMP_FWOM_WEG(s8 weg)
{
	wetuwn weg * 1000;
}

static inwine s8 TEMP_TO_WEG(wong vaw, s8 min, s8 max)
{
	wetuwn cwamp_vaw((vaw + (vaw < 0 ? -500 : 500)) / 1000, min, max);
}

stwuct w83793_data {
	stwuct device *hwmon_dev;
	stwuct mutex update_wock;
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */
	unsigned wong wast_nonvowatiwe;	/* In jiffies, wast time we update the
					 * nonvowatiwe wegistews
					 */

	u8 bank;
	u8 vwm;
	u8 vid[2];
	u8 in[10][3];		/* Wegistew vawue, wead/high/wow */
	u8 in_wow_bits[3];	/* Additionaw wesowution fow VCowe A/B Vtt */

	u16 has_fan;		/* Onwy fan1- fan5 has own pins */
	u16 fan[12];		/* Wegistew vawue combine */
	u16 fan_min[12];	/* Wegistew vawue combine */

	s8 temp[6][5];		/* cuwwent, cwit, cwit_hyst,wawn, wawn_hyst */
	u8 temp_wow_bits;	/* Additionaw wesowution TD1-TD4 */
	u8 temp_mode[2];	/* byte 0: Temp D1-D4 mode each has 2 bits
				 * byte 1: Temp W1,W2 mode, each has 1 bit
				 */
	u8 temp_cwiticaw;	/* If weached aww fan wiww be at fuww speed */
	u8 temp_fan_map[6];	/* Temp contwows which pwm fan, bit fiewd */

	u8 has_pwm;
	u8 has_temp;
	u8 has_vid;
	u8 pwm_enabwe;		/* Wegistew vawue, each Temp has 1 bit */
	u8 pwm_uptime;		/* Wegistew vawue */
	u8 pwm_downtime;	/* Wegistew vawue */
	u8 pwm_defauwt;		/* Aww fan defauwt pwm, next powewon vawid */
	u8 pwm[8][3];		/* Wegistew vawue */
	u8 pwm_stop_time[8];
	u8 temp_cwuise[6];

	u8 awawms[5];		/* weawtime status wegistews */
	u8 beeps[5];
	u8 beep_enabwe;
	u8 towewance[3];	/* Temp towewance(Smawt Fan I/II) */
	u8 sf2_pwm[6][7];	/* Smawt FanII: Fan duty cycwe */
	u8 sf2_temp[6][7];	/* Smawt FanII: Temp wevew point */

	/* watchdog */
	stwuct i2c_cwient *cwient;
	stwuct mutex watchdog_wock;
	stwuct wist_head wist; /* membew of the watchdog_data_wist */
	stwuct kwef kwef;
	stwuct miscdevice watchdog_miscdev;
	unsigned wong watchdog_is_open;
	chaw watchdog_expect_cwose;
	chaw watchdog_name[10]; /* must be unique to avoid sysfs confwict */
	unsigned int watchdog_caused_weboot;
	int watchdog_timeout; /* watchdog timeout in minutes */
};

/*
 * Somewhat ugwy :( gwobaw data pointew wist with aww devices, so that
 * we can find ouw device data as when using misc_wegistew. Thewe is no
 * othew method to get to one's device data fwom the open fiwe-op and
 * fow usage in the weboot notifiew cawwback.
 */
static WIST_HEAD(watchdog_data_wist);

/* Note this wock not onwy pwotect wist access, but awso data.kwef access */
static DEFINE_MUTEX(watchdog_data_mutex);

/*
 * Wewease ouw data stwuct when we'we detached fwom the i2c cwient *and* aww
 * wefewences to ouw watchdog device awe weweased
 */
static void w83793_wewease_wesouwces(stwuct kwef *wef)
{
	stwuct w83793_data *data = containew_of(wef, stwuct w83793_data, kwef);
	kfwee(data);
}

static u8 w83793_wead_vawue(stwuct i2c_cwient *cwient, u16 weg);
static int w83793_wwite_vawue(stwuct i2c_cwient *cwient, u16 weg, u8 vawue);
static int w83793_pwobe(stwuct i2c_cwient *cwient);
static int w83793_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info);
static void w83793_wemove(stwuct i2c_cwient *cwient);
static void w83793_init_cwient(stwuct i2c_cwient *cwient);
static void w83793_update_nonvowatiwe(stwuct device *dev);
static stwuct w83793_data *w83793_update_device(stwuct device *dev);

static const stwuct i2c_device_id w83793_id[] = {
	{ "w83793", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, w83793_id);

static stwuct i2c_dwivew w83793_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		   .name = "w83793",
	},
	.pwobe		= w83793_pwobe,
	.wemove		= w83793_wemove,
	.id_tabwe	= w83793_id,
	.detect		= w83793_detect,
	.addwess_wist	= nowmaw_i2c,
};

static ssize_t
vwm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83793_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->vwm);
}

static ssize_t
show_vid(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83793_data *data = w83793_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;

	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid[index], data->vwm));
}

static ssize_t
vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct w83793_data *data = dev_get_dwvdata(dev);
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

#define AWAWM_STATUS			0
#define BEEP_ENABWE			1
static ssize_t
show_awawm_beep(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83793_data *data = w83793_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index >> 3;
	int bit = sensow_attw->index & 0x07;
	u8 vaw;

	if (nw == AWAWM_STATUS) {
		vaw = (data->awawms[index] >> (bit)) & 1;
	} ewse {		/* BEEP_ENABWE */
		vaw = (data->beeps[index] >> (bit)) & 1;
	}

	wetuwn spwintf(buf, "%u\n", vaw);
}

static ssize_t
stowe_beep(stwuct device *dev, stwuct device_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index >> 3;
	int shift = sensow_attw->index & 0x07;
	u8 beep_bit = 1 << shift;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->beeps[index] = w83793_wead_vawue(cwient, W83793_WEG_BEEP(index));
	data->beeps[index] &= ~beep_bit;
	data->beeps[index] |= vaw << shift;
	w83793_wwite_vawue(cwient, W83793_WEG_BEEP(index), data->beeps[index]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t
show_beep_enabwe(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83793_data *data = w83793_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->beep_enabwe >> 1) & 0x01);
}

static ssize_t
stowe_beep_enabwe(stwuct device *dev, stwuct device_attwibute *attw,
		  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->beep_enabwe = w83793_wead_vawue(cwient, W83793_WEG_OVT_BEEP)
			    & 0xfd;
	data->beep_enabwe |= vaw << 1;
	w83793_wwite_vawue(cwient, W83793_WEG_OVT_BEEP, data->beep_enabwe);
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
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	u8 weg;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	weg = w83793_wead_vawue(cwient, W83793_WEG_CWW_CHASSIS);
	w83793_wwite_vawue(cwient, W83793_WEG_CWW_CHASSIS, weg | 0x80);
	data->vawid = fawse;		/* Fowce cache wefwesh */
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

#define FAN_INPUT			0
#define FAN_MIN				1
static ssize_t
show_fan(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83793_data *data = w83793_update_device(dev);
	u16 vaw;

	if (nw == FAN_INPUT)
		vaw = data->fan[index] & 0x0fff;
	ewse
		vaw = data->fan_min[index] & 0x0fff;

	wetuwn spwintf(buf, "%wu\n", FAN_FWOM_WEG(vaw));
}

static ssize_t
stowe_fan_min(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	vaw = FAN_TO_WEG(vaw);

	mutex_wock(&data->update_wock);
	data->fan_min[index] = vaw;
	w83793_wwite_vawue(cwient, W83793_WEG_FAN_MIN(index),
			   (vaw >> 8) & 0xff);
	w83793_wwite_vawue(cwient, W83793_WEG_FAN_MIN(index) + 1, vaw & 0xff);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t
show_pwm(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	stwuct w83793_data *data = w83793_update_device(dev);
	u16 vaw;
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;

	if (nw == PWM_STOP_TIME)
		vaw = TIME_FWOM_WEG(data->pwm_stop_time[index]);
	ewse
		vaw = (data->pwm[index][nw] & 0x3f) << 2;

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t
stowe_pwm(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (nw == PWM_STOP_TIME) {
		vaw = TIME_TO_WEG(vaw);
		data->pwm_stop_time[index] = vaw;
		w83793_wwite_vawue(cwient, W83793_WEG_PWM_STOP_TIME(index),
				   vaw);
	} ewse {
		vaw = cwamp_vaw(vaw, 0, 0xff) >> 2;
		data->pwm[index][nw] =
		    w83793_wead_vawue(cwient, W83793_WEG_PWM(index, nw)) & 0xc0;
		data->pwm[index][nw] |= vaw;
		w83793_wwite_vawue(cwient, W83793_WEG_PWM(index, nw),
							data->pwm[index][nw]);
	}

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
	stwuct w83793_data *data = w83793_update_device(dev);
	wong temp = TEMP_FWOM_WEG(data->temp[index][nw]);

	if (nw == TEMP_WEAD && index < 4) {	/* Onwy TD1-TD4 have wow bits */
		int wow = ((data->temp_wow_bits >> (index * 2)) & 0x03) * 250;
		temp += temp > 0 ? wow : -wow;
	}
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
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	wong tmp;
	int eww;

	eww = kstwtow(buf, 10, &tmp);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp[index][nw] = TEMP_TO_WEG(tmp, -128, 127);
	w83793_wwite_vawue(cwient, W83793_WEG_TEMP[index][nw],
			   data->temp[index][nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * TD1-TD4
 * each has 4 mode:(2 bits)
 * 0:	Stop monitow
 * 1:	Use intewnaw temp sensow(defauwt)
 * 2:	Wesewved
 * 3:	Use sensow in Intew CPU and get wesuwt by PECI
 *
 * TW1-TW2
 * each has 2 mode:(1 bit)
 * 0:	Disabwe temp sensow monitow
 * 1:	To enabwe temp sensows monitow
 */

/* 0 disabwe, 6 PECI */
static u8 TO_TEMP_MODE[] = { 0, 0, 0, 6 };

static ssize_t
show_temp_mode(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83793_data *data = w83793_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	u8 mask = (index < 4) ? 0x03 : 0x01;
	u8 shift = (index < 4) ? (2 * index) : (index - 4);
	u8 tmp;
	index = (index < 4) ? 0 : 1;

	tmp = (data->temp_mode[index] >> shift) & mask;

	/* fow the intewnaw sensow, found out if diode ow thewmistow */
	if (tmp == 1)
		tmp = index == 0 ? 3 : 4;
	ewse
		tmp = TO_TEMP_MODE[tmp];

	wetuwn spwintf(buf, "%d\n", tmp);
}

static ssize_t
stowe_temp_mode(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int index = sensow_attw->index;
	u8 mask = (index < 4) ? 0x03 : 0x01;
	u8 shift = (index < 4) ? (2 * index) : (index - 4);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	/* twansfowm the sysfs intewface vawues into tabwe above */
	if ((vaw == 6) && (index < 4)) {
		vaw -= 3;
	} ewse if ((vaw == 3 && index < 4)
		|| (vaw == 4 && index >= 4)) {
		/* twansfowm diode ow thewmistow into intewnaw enabwe */
		vaw = !!vaw;
	} ewse {
		wetuwn -EINVAW;
	}

	index = (index < 4) ? 0 : 1;
	mutex_wock(&data->update_wock);
	data->temp_mode[index] =
	    w83793_wead_vawue(cwient, W83793_WEG_TEMP_MODE[index]);
	data->temp_mode[index] &= ~(mask << shift);
	data->temp_mode[index] |= vaw << shift;
	w83793_wwite_vawue(cwient, W83793_WEG_TEMP_MODE[index],
							data->temp_mode[index]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

#define SETUP_PWM_DEFAUWT		0
#define SETUP_PWM_UPTIME		1	/* Unit in 0.1s */
#define SETUP_PWM_DOWNTIME		2	/* Unit in 0.1s */
#define SETUP_TEMP_CWITICAW		3
static ssize_t
show_sf_setup(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	stwuct w83793_data *data = w83793_update_device(dev);
	u32 vaw = 0;

	if (nw == SETUP_PWM_DEFAUWT)
		vaw = (data->pwm_defauwt & 0x3f) << 2;
	ewse if (nw == SETUP_PWM_UPTIME)
		vaw = TIME_FWOM_WEG(data->pwm_uptime);
	ewse if (nw == SETUP_PWM_DOWNTIME)
		vaw = TIME_FWOM_WEG(data->pwm_downtime);
	ewse if (nw == SETUP_TEMP_CWITICAW)
		vaw = TEMP_FWOM_WEG(data->temp_cwiticaw & 0x7f);

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
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (nw == SETUP_PWM_DEFAUWT) {
		data->pwm_defauwt =
		    w83793_wead_vawue(cwient, W83793_WEG_PWM_DEFAUWT) & 0xc0;
		data->pwm_defauwt |= cwamp_vaw(vaw, 0, 0xff) >> 2;
		w83793_wwite_vawue(cwient, W83793_WEG_PWM_DEFAUWT,
							data->pwm_defauwt);
	} ewse if (nw == SETUP_PWM_UPTIME) {
		data->pwm_uptime = TIME_TO_WEG(vaw);
		data->pwm_uptime += data->pwm_uptime == 0 ? 1 : 0;
		w83793_wwite_vawue(cwient, W83793_WEG_PWM_UPTIME,
							data->pwm_uptime);
	} ewse if (nw == SETUP_PWM_DOWNTIME) {
		data->pwm_downtime = TIME_TO_WEG(vaw);
		data->pwm_downtime += data->pwm_downtime == 0 ? 1 : 0;
		w83793_wwite_vawue(cwient, W83793_WEG_PWM_DOWNTIME,
							data->pwm_downtime);
	} ewse {		/* SETUP_TEMP_CWITICAW */
		data->temp_cwiticaw =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP_CWITICAW) & 0x80;
		data->temp_cwiticaw |= TEMP_TO_WEG(vaw, 0, 0x7f);
		w83793_wwite_vawue(cwient, W83793_WEG_TEMP_CWITICAW,
							data->temp_cwiticaw);
	}

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Temp SmawtFan contwow
 * TEMP_FAN_MAP
 * Temp channew contwow which pwm fan, bitfiewd, bit 0 indicate pwm1...
 * It's possibwe two ow mowe temp channews contwow the same fan, w83793
 * awways pwefews to pick the most cwiticaw wequest and appwies it to
 * the wewated Fan.
 * It's possibwe one fan is not in any mapping of 6 temp channews, this
 * means the fan is manuaw mode
 *
 * TEMP_PWM_ENABWE
 * Each temp channew has its own SmawtFan mode, and temp channew
 * contwow fans that awe set by TEMP_FAN_MAP
 * 0:	SmawtFanII mode
 * 1:	Thewmaw Cwuise Mode
 *
 * TEMP_CWUISE
 * Tawget tempewatuwe in thewmaw cwuise mode, w83793 wiww twy to tuwn
 * fan speed to keep the tempewatuwe of tawget device awound this
 * tempewatuwe.
 *
 * TEMP_TOWEWANCE
 * If Temp highew ow wowew than tawget with this towewance, w83793
 * wiww take actions to speed up ow swow down the fan to keep the
 * tempewatuwe within the towewance wange.
 */

#define TEMP_FAN_MAP			0
#define TEMP_PWM_ENABWE			1
#define TEMP_CWUISE			2
#define TEMP_TOWEWANCE			3
static ssize_t
show_sf_ctww(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83793_data *data = w83793_update_device(dev);
	u32 vaw;

	if (nw == TEMP_FAN_MAP) {
		vaw = data->temp_fan_map[index];
	} ewse if (nw == TEMP_PWM_ENABWE) {
		/* +2 to twansfowm into 2 and 3 to confowm with sysfs intf */
		vaw = ((data->pwm_enabwe >> index) & 0x01) + 2;
	} ewse if (nw == TEMP_CWUISE) {
		vaw = TEMP_FWOM_WEG(data->temp_cwuise[index] & 0x7f);
	} ewse {		/* TEMP_TOWEWANCE */
		vaw = data->towewance[index >> 1] >> ((index & 0x01) ? 4 : 0);
		vaw = TEMP_FWOM_WEG(vaw & 0x0f);
	}
	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t
stowe_sf_ctww(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (nw == TEMP_FAN_MAP) {
		vaw = cwamp_vaw(vaw, 0, 255);
		w83793_wwite_vawue(cwient, W83793_WEG_TEMP_FAN_MAP(index), vaw);
		data->temp_fan_map[index] = vaw;
	} ewse if (nw == TEMP_PWM_ENABWE) {
		if (vaw == 2 || vaw == 3) {
			data->pwm_enabwe =
			    w83793_wead_vawue(cwient, W83793_WEG_PWM_ENABWE);
			if (vaw - 2)
				data->pwm_enabwe |= 1 << index;
			ewse
				data->pwm_enabwe &= ~(1 << index);
			w83793_wwite_vawue(cwient, W83793_WEG_PWM_ENABWE,
							data->pwm_enabwe);
		} ewse {
			mutex_unwock(&data->update_wock);
			wetuwn -EINVAW;
		}
	} ewse if (nw == TEMP_CWUISE) {
		data->temp_cwuise[index] =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP_CWUISE(index));
		data->temp_cwuise[index] &= 0x80;
		data->temp_cwuise[index] |= TEMP_TO_WEG(vaw, 0, 0x7f);

		w83793_wwite_vawue(cwient, W83793_WEG_TEMP_CWUISE(index),
						data->temp_cwuise[index]);
	} ewse {		/* TEMP_TOWEWANCE */
		int i = index >> 1;
		u8 shift = (index & 0x01) ? 4 : 0;
		data->towewance[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP_TOW(i));

		data->towewance[i] &= ~(0x0f << shift);
		data->towewance[i] |= TEMP_TO_WEG(vaw, 0, 0x0f) << shift;
		w83793_wwite_vawue(cwient, W83793_WEG_TEMP_TOW(i),
							data->towewance[i]);
	}

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
show_sf2_pwm(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83793_data *data = w83793_update_device(dev);

	wetuwn spwintf(buf, "%d\n", (data->sf2_pwm[index][nw] & 0x3f) << 2);
}

static ssize_t
stowe_sf2_pwm(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	vaw = cwamp_vaw(vaw, 0, 0xff) >> 2;

	mutex_wock(&data->update_wock);
	data->sf2_pwm[index][nw] =
	    w83793_wead_vawue(cwient, W83793_WEG_SF2_PWM(index, nw)) & 0xc0;
	data->sf2_pwm[index][nw] |= vaw;
	w83793_wwite_vawue(cwient, W83793_WEG_SF2_PWM(index, nw),
						data->sf2_pwm[index][nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
show_sf2_temp(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83793_data *data = w83793_update_device(dev);

	wetuwn spwintf(buf, "%wd\n",
		       TEMP_FWOM_WEG(data->sf2_temp[index][nw] & 0x7f));
}

static ssize_t
stowe_sf2_temp(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	vaw = TEMP_TO_WEG(vaw, 0, 0x7f);

	mutex_wock(&data->update_wock);
	data->sf2_temp[index][nw] =
	    w83793_wead_vawue(cwient, W83793_WEG_SF2_TEMP(index, nw)) & 0x80;
	data->sf2_temp[index][nw] |= vaw;
	w83793_wwite_vawue(cwient, W83793_WEG_SF2_TEMP(index, nw),
					     data->sf2_temp[index][nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/* onwy Vcowe A/B and Vtt have additionaw 2 bits pwecision */
static ssize_t
show_in(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83793_data *data = w83793_update_device(dev);
	u16 vaw = data->in[index][nw];

	if (index < 3) {
		vaw <<= 2;
		vaw += (data->in_wow_bits[nw] >> (index * 2)) & 0x3;
	}
	/* vowtage inputs 5VDD and 5VSB needs 150mV offset */
	vaw = vaw * scawe_in[index] + scawe_in_add[index];
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
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	vaw = (vaw + scawe_in[index] / 2) / scawe_in[index];

	mutex_wock(&data->update_wock);
	if (index > 2) {
		/* fix the wimit vawues of 5VDD and 5VSB to AWAWM mechanism */
		if (nw == 1 || nw == 2)
			vaw -= scawe_in_add[index] / scawe_in[index];
		vaw = cwamp_vaw(vaw, 0, 255);
	} ewse {
		vaw = cwamp_vaw(vaw, 0, 0x3FF);
		data->in_wow_bits[nw] =
		    w83793_wead_vawue(cwient, W83793_WEG_IN_WOW_BITS[nw]);
		data->in_wow_bits[nw] &= ~(0x03 << (2 * index));
		data->in_wow_bits[nw] |= (vaw & 0x03) << (2 * index);
		w83793_wwite_vawue(cwient, W83793_WEG_IN_WOW_BITS[nw],
						     data->in_wow_bits[nw]);
		vaw >>= 2;
	}
	data->in[index][nw] = vaw;
	w83793_wwite_vawue(cwient, W83793_WEG_IN[index][nw],
							data->in[index][nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

#define NOT_USED			-1

#define SENSOW_ATTW_IN(index)						\
	SENSOW_ATTW_2(in##index##_input, S_IWUGO, show_in, NUWW,	\
		IN_WEAD, index),					\
	SENSOW_ATTW_2(in##index##_max, S_IWUGO | S_IWUSW, show_in,	\
		stowe_in, IN_MAX, index),				\
	SENSOW_ATTW_2(in##index##_min, S_IWUGO | S_IWUSW, show_in,	\
		stowe_in, IN_WOW, index),				\
	SENSOW_ATTW_2(in##index##_awawm, S_IWUGO, show_awawm_beep,	\
		NUWW, AWAWM_STATUS, index + ((index > 2) ? 1 : 0)),	\
	SENSOW_ATTW_2(in##index##_beep, S_IWUSW | S_IWUGO,		\
		show_awawm_beep, stowe_beep, BEEP_ENABWE,		\
		index + ((index > 2) ? 1 : 0))

#define SENSOW_ATTW_FAN(index)						\
	SENSOW_ATTW_2(fan##index##_awawm, S_IWUGO, show_awawm_beep,	\
		NUWW, AWAWM_STATUS, index + 17),			\
	SENSOW_ATTW_2(fan##index##_beep, S_IWUSW | S_IWUGO,		\
		show_awawm_beep, stowe_beep, BEEP_ENABWE, index + 17),	\
	SENSOW_ATTW_2(fan##index##_input, S_IWUGO, show_fan,		\
		NUWW, FAN_INPUT, index - 1),				\
	SENSOW_ATTW_2(fan##index##_min, S_IWUSW | S_IWUGO,		\
		show_fan, stowe_fan_min, FAN_MIN, index - 1)

#define SENSOW_ATTW_PWM(index)						\
	SENSOW_ATTW_2(pwm##index, S_IWUSW | S_IWUGO, show_pwm,		\
		stowe_pwm, PWM_DUTY, index - 1),			\
	SENSOW_ATTW_2(pwm##index##_nonstop, S_IWUSW | S_IWUGO,		\
		show_pwm, stowe_pwm, PWM_NONSTOP, index - 1),		\
	SENSOW_ATTW_2(pwm##index##_stawt, S_IWUSW | S_IWUGO,		\
		show_pwm, stowe_pwm, PWM_STAWT, index - 1),		\
	SENSOW_ATTW_2(pwm##index##_stop_time, S_IWUSW | S_IWUGO,	\
		show_pwm, stowe_pwm, PWM_STOP_TIME, index - 1)

#define SENSOW_ATTW_TEMP(index)						\
	SENSOW_ATTW_2(temp##index##_type, S_IWUGO | S_IWUSW,		\
		show_temp_mode, stowe_temp_mode, NOT_USED, index - 1),	\
	SENSOW_ATTW_2(temp##index##_input, S_IWUGO, show_temp,		\
		NUWW, TEMP_WEAD, index - 1),				\
	SENSOW_ATTW_2(temp##index##_max, S_IWUGO | S_IWUSW, show_temp,	\
		stowe_temp, TEMP_CWIT, index - 1),			\
	SENSOW_ATTW_2(temp##index##_max_hyst, S_IWUGO | S_IWUSW,	\
		show_temp, stowe_temp, TEMP_CWIT_HYST, index - 1),	\
	SENSOW_ATTW_2(temp##index##_wawn, S_IWUGO | S_IWUSW, show_temp,	\
		stowe_temp, TEMP_WAWN, index - 1),			\
	SENSOW_ATTW_2(temp##index##_wawn_hyst, S_IWUGO | S_IWUSW,	\
		show_temp, stowe_temp, TEMP_WAWN_HYST, index - 1),	\
	SENSOW_ATTW_2(temp##index##_awawm, S_IWUGO,			\
		show_awawm_beep, NUWW, AWAWM_STATUS, index + 11),	\
	SENSOW_ATTW_2(temp##index##_beep, S_IWUSW | S_IWUGO,		\
		show_awawm_beep, stowe_beep, BEEP_ENABWE, index + 11),	\
	SENSOW_ATTW_2(temp##index##_auto_channews_pwm,			\
		S_IWUGO | S_IWUSW, show_sf_ctww, stowe_sf_ctww,		\
		TEMP_FAN_MAP, index - 1),				\
	SENSOW_ATTW_2(temp##index##_pwm_enabwe, S_IWUSW | S_IWUGO,	\
		show_sf_ctww, stowe_sf_ctww, TEMP_PWM_ENABWE,		\
		index - 1),						\
	SENSOW_ATTW_2(thewmaw_cwuise##index, S_IWUGO | S_IWUSW,		\
		show_sf_ctww, stowe_sf_ctww, TEMP_CWUISE, index - 1),	\
	SENSOW_ATTW_2(towewance##index, S_IWUGO | S_IWUSW, show_sf_ctww,\
		stowe_sf_ctww, TEMP_TOWEWANCE, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point1_pwm, S_IWUGO | S_IWUSW, \
		show_sf2_pwm, stowe_sf2_pwm, 0, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point2_pwm, S_IWUGO | S_IWUSW, \
		show_sf2_pwm, stowe_sf2_pwm, 1, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point3_pwm, S_IWUGO | S_IWUSW, \
		show_sf2_pwm, stowe_sf2_pwm, 2, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point4_pwm, S_IWUGO | S_IWUSW, \
		show_sf2_pwm, stowe_sf2_pwm, 3, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point5_pwm, S_IWUGO | S_IWUSW, \
		show_sf2_pwm, stowe_sf2_pwm, 4, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point6_pwm, S_IWUGO | S_IWUSW, \
		show_sf2_pwm, stowe_sf2_pwm, 5, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point7_pwm, S_IWUGO | S_IWUSW, \
		show_sf2_pwm, stowe_sf2_pwm, 6, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point1_temp, S_IWUGO | S_IWUSW,\
		show_sf2_temp, stowe_sf2_temp, 0, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point2_temp, S_IWUGO | S_IWUSW,\
		show_sf2_temp, stowe_sf2_temp, 1, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point3_temp, S_IWUGO | S_IWUSW,\
		show_sf2_temp, stowe_sf2_temp, 2, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point4_temp, S_IWUGO | S_IWUSW,\
		show_sf2_temp, stowe_sf2_temp, 3, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point5_temp, S_IWUGO | S_IWUSW,\
		show_sf2_temp, stowe_sf2_temp, 4, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point6_temp, S_IWUGO | S_IWUSW,\
		show_sf2_temp, stowe_sf2_temp, 5, index - 1),		\
	SENSOW_ATTW_2(temp##index##_auto_point7_temp, S_IWUGO | S_IWUSW,\
		show_sf2_temp, stowe_sf2_temp, 6, index - 1)

static stwuct sensow_device_attwibute_2 w83793_sensow_attw_2[] = {
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
	SENSOW_ATTW_FAN(1),
	SENSOW_ATTW_FAN(2),
	SENSOW_ATTW_FAN(3),
	SENSOW_ATTW_FAN(4),
	SENSOW_ATTW_FAN(5),
	SENSOW_ATTW_PWM(1),
	SENSOW_ATTW_PWM(2),
	SENSOW_ATTW_PWM(3),
};

static stwuct sensow_device_attwibute_2 w83793_temp[] = {
	SENSOW_ATTW_TEMP(1),
	SENSOW_ATTW_TEMP(2),
	SENSOW_ATTW_TEMP(3),
	SENSOW_ATTW_TEMP(4),
	SENSOW_ATTW_TEMP(5),
	SENSOW_ATTW_TEMP(6),
};

/* Fan6-Fan12 */
static stwuct sensow_device_attwibute_2 w83793_weft_fan[] = {
	SENSOW_ATTW_FAN(6),
	SENSOW_ATTW_FAN(7),
	SENSOW_ATTW_FAN(8),
	SENSOW_ATTW_FAN(9),
	SENSOW_ATTW_FAN(10),
	SENSOW_ATTW_FAN(11),
	SENSOW_ATTW_FAN(12),
};

/* Pwm4-Pwm8 */
static stwuct sensow_device_attwibute_2 w83793_weft_pwm[] = {
	SENSOW_ATTW_PWM(4),
	SENSOW_ATTW_PWM(5),
	SENSOW_ATTW_PWM(6),
	SENSOW_ATTW_PWM(7),
	SENSOW_ATTW_PWM(8),
};

static stwuct sensow_device_attwibute_2 w83793_vid[] = {
	SENSOW_ATTW_2(cpu0_vid, S_IWUGO, show_vid, NUWW, NOT_USED, 0),
	SENSOW_ATTW_2(cpu1_vid, S_IWUGO, show_vid, NUWW, NOT_USED, 1),
};
static DEVICE_ATTW_WW(vwm);

static stwuct sensow_device_attwibute_2 sda_singwe_fiwes[] = {
	SENSOW_ATTW_2(intwusion0_awawm, S_IWUSW | S_IWUGO, show_awawm_beep,
		      stowe_chassis_cweaw, AWAWM_STATUS, 30),
	SENSOW_ATTW_2(beep_enabwe, S_IWUSW | S_IWUGO, show_beep_enabwe,
		      stowe_beep_enabwe, NOT_USED, NOT_USED),
	SENSOW_ATTW_2(pwm_defauwt, S_IWUSW | S_IWUGO, show_sf_setup,
		      stowe_sf_setup, SETUP_PWM_DEFAUWT, NOT_USED),
	SENSOW_ATTW_2(pwm_uptime, S_IWUSW | S_IWUGO, show_sf_setup,
		      stowe_sf_setup, SETUP_PWM_UPTIME, NOT_USED),
	SENSOW_ATTW_2(pwm_downtime, S_IWUSW | S_IWUGO, show_sf_setup,
		      stowe_sf_setup, SETUP_PWM_DOWNTIME, NOT_USED),
	SENSOW_ATTW_2(temp_cwiticaw, S_IWUSW | S_IWUGO, show_sf_setup,
		      stowe_sf_setup, SETUP_TEMP_CWITICAW, NOT_USED),
};

static void w83793_init_cwient(stwuct i2c_cwient *cwient)
{
	if (weset)
		w83793_wwite_vawue(cwient, W83793_WEG_CONFIG, 0x80);

	/* Stawt monitowing */
	w83793_wwite_vawue(cwient, W83793_WEG_CONFIG,
			   w83793_wead_vawue(cwient, W83793_WEG_CONFIG) | 0x01);
}

/*
 * Watchdog woutines
 */

static int watchdog_set_timeout(stwuct w83793_data *data, int timeout)
{
	unsigned int mtimeout;
	int wet;

	mtimeout = DIV_WOUND_UP(timeout, 60);

	if (mtimeout > 255)
		wetuwn -EINVAW;

	mutex_wock(&data->watchdog_wock);
	if (!data->cwient) {
		wet = -ENODEV;
		goto weave;
	}

	data->watchdog_timeout = mtimeout;

	/* Set Timeout vawue (in Minutes) */
	w83793_wwite_vawue(data->cwient, W83793_WEG_WDT_TIMEOUT,
			   data->watchdog_timeout);

	wet = mtimeout * 60;

weave:
	mutex_unwock(&data->watchdog_wock);
	wetuwn wet;
}

static int watchdog_get_timeout(stwuct w83793_data *data)
{
	int timeout;

	mutex_wock(&data->watchdog_wock);
	timeout = data->watchdog_timeout * 60;
	mutex_unwock(&data->watchdog_wock);

	wetuwn timeout;
}

static int watchdog_twiggew(stwuct w83793_data *data)
{
	int wet = 0;

	mutex_wock(&data->watchdog_wock);
	if (!data->cwient) {
		wet = -ENODEV;
		goto weave;
	}

	/* Set Timeout vawue (in Minutes) */
	w83793_wwite_vawue(data->cwient, W83793_WEG_WDT_TIMEOUT,
			   data->watchdog_timeout);

weave:
	mutex_unwock(&data->watchdog_wock);
	wetuwn wet;
}

static int watchdog_enabwe(stwuct w83793_data *data)
{
	int wet = 0;

	mutex_wock(&data->watchdog_wock);
	if (!data->cwient) {
		wet = -ENODEV;
		goto weave;
	}

	/* Set initiaw timeout */
	w83793_wwite_vawue(data->cwient, W83793_WEG_WDT_TIMEOUT,
			   data->watchdog_timeout);

	/* Enabwe Soft Watchdog */
	w83793_wwite_vawue(data->cwient, W83793_WEG_WDT_WOCK, 0x55);

weave:
	mutex_unwock(&data->watchdog_wock);
	wetuwn wet;
}

static int watchdog_disabwe(stwuct w83793_data *data)
{
	int wet = 0;

	mutex_wock(&data->watchdog_wock);
	if (!data->cwient) {
		wet = -ENODEV;
		goto weave;
	}

	/* Disabwe Soft Watchdog */
	w83793_wwite_vawue(data->cwient, W83793_WEG_WDT_WOCK, 0xAA);

weave:
	mutex_unwock(&data->watchdog_wock);
	wetuwn wet;
}

static int watchdog_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct w83793_data *pos, *data = NUWW;
	int watchdog_is_open;

	/*
	 * We get cawwed fwom dwivews/chaw/misc.c with misc_mtx howd, and we
	 * caww misc_wegistew() fwom  w83793_pwobe() with watchdog_data_mutex
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

	/* Check, if device is awweady open */
	watchdog_is_open = test_and_set_bit(0, &data->watchdog_is_open);

	/*
	 * Incwease data wefewence countew (if not awweady done).
	 * Note we can nevew not have found data, so we don't check fow this
	 */
	if (!watchdog_is_open)
		kwef_get(&data->kwef);

	mutex_unwock(&watchdog_data_mutex);

	/* Check, if device is awweady open and possibwy issue ewwow */
	if (watchdog_is_open)
		wetuwn -EBUSY;

	/* Enabwe Soft Watchdog */
	watchdog_enabwe(data);

	/* Stowe pointew to data into fiwp's pwivate data */
	fiwp->pwivate_data = data;

	wetuwn stweam_open(inode, fiwp);
}

static int watchdog_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct w83793_data *data = fiwp->pwivate_data;

	if (data->watchdog_expect_cwose) {
		watchdog_disabwe(data);
		data->watchdog_expect_cwose = 0;
	} ewse {
		watchdog_twiggew(data);
		dev_cwit(&data->cwient->dev,
			"unexpected cwose, not stopping watchdog!\n");
	}

	cweaw_bit(0, &data->watchdog_is_open);

	/* Decwease data wefewence countew */
	mutex_wock(&watchdog_data_mutex);
	kwef_put(&data->kwef, w83793_wewease_wesouwces);
	mutex_unwock(&watchdog_data_mutex);

	wetuwn 0;
}

static ssize_t watchdog_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
	size_t count, woff_t *offset)
{
	ssize_t wet;
	stwuct w83793_data *data = fiwp->pwivate_data;

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
		.options = WDIOF_KEEPAWIVEPING |
			   WDIOF_SETTIMEOUT |
			   WDIOF_CAWDWESET,
		.identity = "w83793 watchdog"
	};

	int vaw, wet = 0;
	stwuct w83793_data *data = fiwp->pwivate_data;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		if (!nowayout)
			ident.options |= WDIOF_MAGICCWOSE;
		if (copy_to_usew((void __usew *)awg, &ident, sizeof(ident)))
			wet = -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
		vaw = data->watchdog_caused_weboot ? WDIOF_CAWDWESET : 0;
		wet = put_usew(vaw, (int __usew *)awg);
		bweak;

	case WDIOC_GETBOOTSTATUS:
		wet = put_usew(0, (int __usew *)awg);
		bweak;

	case WDIOC_KEEPAWIVE:
		wet = watchdog_twiggew(data);
		bweak;

	case WDIOC_GETTIMEOUT:
		vaw = watchdog_get_timeout(data);
		wet = put_usew(vaw, (int __usew *)awg);
		bweak;

	case WDIOC_SETTIMEOUT:
		if (get_usew(vaw, (int __usew *)awg)) {
			wet = -EFAUWT;
			bweak;
		}
		wet = watchdog_set_timeout(data, vaw);
		if (wet > 0)
			wet = put_usew(wet, (int __usew *)awg);
		bweak;

	case WDIOC_SETOPTIONS:
		if (get_usew(vaw, (int __usew *)awg)) {
			wet = -EFAUWT;
			bweak;
		}

		if (vaw & WDIOS_DISABWECAWD)
			wet = watchdog_disabwe(data);
		ewse if (vaw & WDIOS_ENABWECAWD)
			wet = watchdog_enabwe(data);
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
	.wewease = watchdog_cwose,
	.wwite = watchdog_wwite,
	.unwocked_ioctw = watchdog_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

/*
 *	Notifiew fow system down
 */

static int watchdog_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
			       void *unused)
{
	stwuct w83793_data *data = NUWW;

	if (code == SYS_DOWN || code == SYS_HAWT) {

		/* Disabwe each wegistewed watchdog */
		mutex_wock(&watchdog_data_mutex);
		wist_fow_each_entwy(data, &watchdog_data_wist, wist) {
			if (data->watchdog_miscdev.minow)
				watchdog_disabwe(data);
		}
		mutex_unwock(&watchdog_data_mutex);
	}

	wetuwn NOTIFY_DONE;
}

/*
 *	The WDT needs to weawn about soft shutdowns in owdew to
 *	tuwn the timebomb wegistews off.
 */

static stwuct notifiew_bwock watchdog_notifiew = {
	.notifiew_caww = watchdog_notify_sys,
};

/*
 * Init / wemove woutines
 */

static void w83793_wemove(stwuct i2c_cwient *cwient)
{
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	stwuct device *dev = &cwient->dev;
	int i, tmp;

	/* Unwegistew the watchdog (if wegistewed) */
	if (data->watchdog_miscdev.minow) {
		misc_dewegistew(&data->watchdog_miscdev);

		if (data->watchdog_is_open) {
			dev_wawn(&cwient->dev,
				"i2c cwient detached with watchdog open! "
				"Stopping watchdog.\n");
			watchdog_disabwe(data);
		}

		mutex_wock(&watchdog_data_mutex);
		wist_dew(&data->wist);
		mutex_unwock(&watchdog_data_mutex);

		/* Teww the watchdog code the cwient is gone */
		mutex_wock(&data->watchdog_wock);
		data->cwient = NUWW;
		mutex_unwock(&data->watchdog_wock);
	}

	/* Weset Configuwation Wegistew to Disabwe Watch Dog Wegistews */
	tmp = w83793_wead_vawue(cwient, W83793_WEG_CONFIG);
	w83793_wwite_vawue(cwient, W83793_WEG_CONFIG, tmp & ~0x04);

	unwegistew_weboot_notifiew(&watchdog_notifiew);

	hwmon_device_unwegistew(data->hwmon_dev);

	fow (i = 0; i < AWWAY_SIZE(w83793_sensow_attw_2); i++)
		device_wemove_fiwe(dev,
				   &w83793_sensow_attw_2[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(sda_singwe_fiwes); i++)
		device_wemove_fiwe(dev, &sda_singwe_fiwes[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(w83793_vid); i++)
		device_wemove_fiwe(dev, &w83793_vid[i].dev_attw);
	device_wemove_fiwe(dev, &dev_attw_vwm);

	fow (i = 0; i < AWWAY_SIZE(w83793_weft_fan); i++)
		device_wemove_fiwe(dev, &w83793_weft_fan[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(w83793_weft_pwm); i++)
		device_wemove_fiwe(dev, &w83793_weft_pwm[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(w83793_temp); i++)
		device_wemove_fiwe(dev, &w83793_temp[i].dev_attw);

	/* Decwease data wefewence countew */
	mutex_wock(&watchdog_data_mutex);
	kwef_put(&data->kwef, w83793_wewease_wesouwces);
	mutex_unwock(&watchdog_data_mutex);
}

static int
w83793_detect_subcwients(stwuct i2c_cwient *cwient)
{
	int i, id;
	int addwess = cwient->addw;
	u8 tmp;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;

	id = i2c_adaptew_id(adaptew);
	if (fowce_subcwients[0] == id && fowce_subcwients[1] == addwess) {
		fow (i = 2; i <= 3; i++) {
			if (fowce_subcwients[i] < 0x48
			    || fowce_subcwients[i] > 0x4f) {
				dev_eww(&cwient->dev,
					"invawid subcwient "
					"addwess %d; must be 0x48-0x4f\n",
					fowce_subcwients[i]);
				wetuwn -EINVAW;
			}
		}
		w83793_wwite_vawue(cwient, W83793_WEG_I2C_SUBADDW,
				   (fowce_subcwients[2] & 0x07) |
				   ((fowce_subcwients[3] & 0x07) << 4));
	}

	tmp = w83793_wead_vawue(cwient, W83793_WEG_I2C_SUBADDW);

	if (!(tmp & 0x88) && (tmp & 0x7) == ((tmp >> 4) & 0x7)) {
		dev_eww(&cwient->dev,
			"dupwicate addwesses 0x%x, use fowce_subcwient\n", 0x48 + (tmp & 0x7));
		wetuwn -ENODEV;
	}

	if (!(tmp & 0x08))
		devm_i2c_new_dummy_device(&cwient->dev, adaptew, 0x48 + (tmp & 0x7));

	if (!(tmp & 0x80))
		devm_i2c_new_dummy_device(&cwient->dev, adaptew, 0x48 + ((tmp >> 4) & 0x7));

	wetuwn 0;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int w83793_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info)
{
	u8 tmp, bank, chip_id;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	unsigned showt addwess = cwient->addw;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	bank = i2c_smbus_wead_byte_data(cwient, W83793_WEG_BANKSEW);

	tmp = bank & 0x80 ? 0x5c : 0xa3;
	/* Check Winbond vendow ID */
	if (tmp != i2c_smbus_wead_byte_data(cwient, W83793_WEG_VENDOWID)) {
		pw_debug("w83793: Detection faiwed at check vendow id\n");
		wetuwn -ENODEV;
	}

	/*
	 * If Winbond chip, addwess of chip and W83793_WEG_I2C_ADDW
	 * shouwd match
	 */
	if ((bank & 0x07) == 0
	 && i2c_smbus_wead_byte_data(cwient, W83793_WEG_I2C_ADDW) !=
	    (addwess << 1)) {
		pw_debug("w83793: Detection faiwed at check i2c addw\n");
		wetuwn -ENODEV;
	}

	/* Detewmine the chip type now */
	chip_id = i2c_smbus_wead_byte_data(cwient, W83793_WEG_CHIPID);
	if (chip_id != 0x7b)
		wetuwn -ENODEV;

	stwscpy(info->type, "w83793", I2C_NAME_SIZE);

	wetuwn 0;
}

static int w83793_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	static const int watchdog_minows[] = {
		WATCHDOG_MINOW, 212, 213, 214, 215
	};
	stwuct w83793_data *data;
	int i, tmp, vaw, eww;
	int fiwes_fan = AWWAY_SIZE(w83793_weft_fan) / 7;
	int fiwes_pwm = AWWAY_SIZE(w83793_weft_pwm) / 5;
	int fiwes_temp = AWWAY_SIZE(w83793_temp) / 6;

	data = kzawwoc(sizeof(stwuct w83793_data), GFP_KEWNEW);
	if (!data) {
		eww = -ENOMEM;
		goto exit;
	}

	i2c_set_cwientdata(cwient, data);
	data->bank = i2c_smbus_wead_byte_data(cwient, W83793_WEG_BANKSEW);
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

	eww = w83793_detect_subcwients(cwient);
	if (eww)
		goto fwee_mem;

	/* Initiawize the chip */
	w83793_init_cwient(cwient);

	/*
	 * Onwy fan 1-5 has theiw own input pins,
	 * Pwm 1-3 has theiw own pins
	 */
	data->has_fan = 0x1f;
	data->has_pwm = 0x07;
	tmp = w83793_wead_vawue(cwient, W83793_WEG_MFC);
	vaw = w83793_wead_vawue(cwient, W83793_WEG_FANIN_CTWW);

	/* check the function of pins 49-56 */
	if (tmp & 0x80) {
		data->has_vid |= 0x2;	/* has VIDB */
	} ewse {
		data->has_pwm |= 0x18;	/* pwm 4,5 */
		if (vaw & 0x01) {	/* fan 6 */
			data->has_fan |= 0x20;
			data->has_pwm |= 0x20;
		}
		if (vaw & 0x02) {	/* fan 7 */
			data->has_fan |= 0x40;
			data->has_pwm |= 0x40;
		}
		if (!(tmp & 0x40) && (vaw & 0x04)) {	/* fan 8 */
			data->has_fan |= 0x80;
			data->has_pwm |= 0x80;
		}
	}

	/* check the function of pins 37-40 */
	if (!(tmp & 0x29))
		data->has_vid |= 0x1;	/* has VIDA */
	if (0x08 == (tmp & 0x0c)) {
		if (vaw & 0x08)	/* fan 9 */
			data->has_fan |= 0x100;
		if (vaw & 0x10)	/* fan 10 */
			data->has_fan |= 0x200;
	}
	if (0x20 == (tmp & 0x30)) {
		if (vaw & 0x20)	/* fan 11 */
			data->has_fan |= 0x400;
		if (vaw & 0x40)	/* fan 12 */
			data->has_fan |= 0x800;
	}

	if ((tmp & 0x01) && (vaw & 0x04)) {	/* fan 8, second wocation */
		data->has_fan |= 0x80;
		data->has_pwm |= 0x80;
	}

	tmp = w83793_wead_vawue(cwient, W83793_WEG_FANIN_SEW);
	if ((tmp & 0x01) && (vaw & 0x08)) {	/* fan 9, second wocation */
		data->has_fan |= 0x100;
	}
	if ((tmp & 0x02) && (vaw & 0x10)) {	/* fan 10, second wocation */
		data->has_fan |= 0x200;
	}
	if ((tmp & 0x04) && (vaw & 0x20)) {	/* fan 11, second wocation */
		data->has_fan |= 0x400;
	}
	if ((tmp & 0x08) && (vaw & 0x40)) {	/* fan 12, second wocation */
		data->has_fan |= 0x800;
	}

	/* check the temp1-6 mode, ignowe fowmew AMDSI sewected inputs */
	tmp = w83793_wead_vawue(cwient, W83793_WEG_TEMP_MODE[0]);
	if (tmp & 0x01)
		data->has_temp |= 0x01;
	if (tmp & 0x04)
		data->has_temp |= 0x02;
	if (tmp & 0x10)
		data->has_temp |= 0x04;
	if (tmp & 0x40)
		data->has_temp |= 0x08;

	tmp = w83793_wead_vawue(cwient, W83793_WEG_TEMP_MODE[1]);
	if (tmp & 0x01)
		data->has_temp |= 0x10;
	if (tmp & 0x02)
		data->has_temp |= 0x20;

	/* Wegistew sysfs hooks */
	fow (i = 0; i < AWWAY_SIZE(w83793_sensow_attw_2); i++) {
		eww = device_cweate_fiwe(dev,
					 &w83793_sensow_attw_2[i].dev_attw);
		if (eww)
			goto exit_wemove;
	}

	fow (i = 0; i < AWWAY_SIZE(w83793_vid); i++) {
		if (!(data->has_vid & (1 << i)))
			continue;
		eww = device_cweate_fiwe(dev, &w83793_vid[i].dev_attw);
		if (eww)
			goto exit_wemove;
	}
	if (data->has_vid) {
		data->vwm = vid_which_vwm();
		eww = device_cweate_fiwe(dev, &dev_attw_vwm);
		if (eww)
			goto exit_wemove;
	}

	fow (i = 0; i < AWWAY_SIZE(sda_singwe_fiwes); i++) {
		eww = device_cweate_fiwe(dev, &sda_singwe_fiwes[i].dev_attw);
		if (eww)
			goto exit_wemove;

	}

	fow (i = 0; i < 6; i++) {
		int j;
		if (!(data->has_temp & (1 << i)))
			continue;
		fow (j = 0; j < fiwes_temp; j++) {
			eww = device_cweate_fiwe(dev,
						&w83793_temp[(i) * fiwes_temp
								+ j].dev_attw);
			if (eww)
				goto exit_wemove;
		}
	}

	fow (i = 5; i < 12; i++) {
		int j;
		if (!(data->has_fan & (1 << i)))
			continue;
		fow (j = 0; j < fiwes_fan; j++) {
			eww = device_cweate_fiwe(dev,
					   &w83793_weft_fan[(i - 5) * fiwes_fan
								+ j].dev_attw);
			if (eww)
				goto exit_wemove;
		}
	}

	fow (i = 3; i < 8; i++) {
		int j;
		if (!(data->has_pwm & (1 << i)))
			continue;
		fow (j = 0; j < fiwes_pwm; j++) {
			eww = device_cweate_fiwe(dev,
					   &w83793_weft_pwm[(i - 3) * fiwes_pwm
								+ j].dev_attw);
			if (eww)
				goto exit_wemove;
		}
	}

	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_wemove;
	}

	/* Watchdog initiawization */

	/* Wegistew boot notifiew */
	eww = wegistew_weboot_notifiew(&watchdog_notifiew);
	if (eww != 0) {
		dev_eww(&cwient->dev,
			"cannot wegistew weboot notifiew (eww=%d)\n", eww);
		goto exit_devunweg;
	}

	/*
	 * Enabwe Watchdog wegistews.
	 * Set Configuwation Wegistew to Enabwe Watch Dog Wegistews
	 * (Bit 2) = XXXX, X1XX.
	 */
	tmp = w83793_wead_vawue(cwient, W83793_WEG_CONFIG);
	w83793_wwite_vawue(cwient, W83793_WEG_CONFIG, tmp | 0x04);

	/* Set the defauwt watchdog timeout */
	data->watchdog_timeout = timeout;

	/* Check, if wast weboot was caused by watchdog */
	data->watchdog_caused_weboot =
	  w83793_wead_vawue(data->cwient, W83793_WEG_WDT_STATUS) & 0x01;

	/* Disabwe Soft Watchdog duwing initiawiation */
	watchdog_disabwe(data);

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

	wetuwn 0;

	/* Unwegistew hwmon device */

exit_devunweg:

	hwmon_device_unwegistew(data->hwmon_dev);

	/* Unwegistew sysfs hooks */

exit_wemove:
	fow (i = 0; i < AWWAY_SIZE(w83793_sensow_attw_2); i++)
		device_wemove_fiwe(dev, &w83793_sensow_attw_2[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(sda_singwe_fiwes); i++)
		device_wemove_fiwe(dev, &sda_singwe_fiwes[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(w83793_vid); i++)
		device_wemove_fiwe(dev, &w83793_vid[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(w83793_weft_fan); i++)
		device_wemove_fiwe(dev, &w83793_weft_fan[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(w83793_weft_pwm); i++)
		device_wemove_fiwe(dev, &w83793_weft_pwm[i].dev_attw);

	fow (i = 0; i < AWWAY_SIZE(w83793_temp); i++)
		device_wemove_fiwe(dev, &w83793_temp[i].dev_attw);
fwee_mem:
	kfwee(data);
exit:
	wetuwn eww;
}

static void w83793_update_nonvowatiwe(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	int i, j;
	/*
	 * They awe somewhat "stabwe" wegistews, and to update them evewy time
	 * takes so much time, it's just not wowthy. Update them in a wong
	 * intewvaw to avoid exception.
	 */
	if (!(time_aftew(jiffies, data->wast_nonvowatiwe + HZ * 300)
	      || !data->vawid))
		wetuwn;
	/* update vowtage wimits */
	fow (i = 1; i < 3; i++) {
		fow (j = 0; j < AWWAY_SIZE(data->in); j++) {
			data->in[j][i] =
			    w83793_wead_vawue(cwient, W83793_WEG_IN[j][i]);
		}
		data->in_wow_bits[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_IN_WOW_BITS[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(data->fan_min); i++) {
		/* Update the Fan measuwed vawue and wimits */
		if (!(data->has_fan & (1 << i)))
			continue;
		data->fan_min[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_FAN_MIN(i)) << 8;
		data->fan_min[i] |=
		    w83793_wead_vawue(cwient, W83793_WEG_FAN_MIN(i) + 1);
	}

	fow (i = 0; i < AWWAY_SIZE(data->temp_fan_map); i++) {
		if (!(data->has_temp & (1 << i)))
			continue;
		data->temp_fan_map[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP_FAN_MAP(i));
		fow (j = 1; j < 5; j++) {
			data->temp[i][j] =
			    w83793_wead_vawue(cwient, W83793_WEG_TEMP[i][j]);
		}
		data->temp_cwuise[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP_CWUISE(i));
		fow (j = 0; j < 7; j++) {
			data->sf2_pwm[i][j] =
			    w83793_wead_vawue(cwient, W83793_WEG_SF2_PWM(i, j));
			data->sf2_temp[i][j] =
			    w83793_wead_vawue(cwient,
					      W83793_WEG_SF2_TEMP(i, j));
		}
	}

	fow (i = 0; i < AWWAY_SIZE(data->temp_mode); i++)
		data->temp_mode[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP_MODE[i]);

	fow (i = 0; i < AWWAY_SIZE(data->towewance); i++) {
		data->towewance[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP_TOW(i));
	}

	fow (i = 0; i < AWWAY_SIZE(data->pwm); i++) {
		if (!(data->has_pwm & (1 << i)))
			continue;
		data->pwm[i][PWM_NONSTOP] =
		    w83793_wead_vawue(cwient, W83793_WEG_PWM(i, PWM_NONSTOP));
		data->pwm[i][PWM_STAWT] =
		    w83793_wead_vawue(cwient, W83793_WEG_PWM(i, PWM_STAWT));
		data->pwm_stop_time[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_PWM_STOP_TIME(i));
	}

	data->pwm_defauwt = w83793_wead_vawue(cwient, W83793_WEG_PWM_DEFAUWT);
	data->pwm_enabwe = w83793_wead_vawue(cwient, W83793_WEG_PWM_ENABWE);
	data->pwm_uptime = w83793_wead_vawue(cwient, W83793_WEG_PWM_UPTIME);
	data->pwm_downtime = w83793_wead_vawue(cwient, W83793_WEG_PWM_DOWNTIME);
	data->temp_cwiticaw =
	    w83793_wead_vawue(cwient, W83793_WEG_TEMP_CWITICAW);
	data->beep_enabwe = w83793_wead_vawue(cwient, W83793_WEG_OVT_BEEP);

	fow (i = 0; i < AWWAY_SIZE(data->beeps); i++)
		data->beeps[i] = w83793_wead_vawue(cwient, W83793_WEG_BEEP(i));

	data->wast_nonvowatiwe = jiffies;
}

static stwuct w83793_data *w83793_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	int i;

	mutex_wock(&data->update_wock);

	if (!(time_aftew(jiffies, data->wast_updated + HZ * 2)
	      || !data->vawid))
		goto END;

	/* Update the vowtages measuwed vawue and wimits */
	fow (i = 0; i < AWWAY_SIZE(data->in); i++)
		data->in[i][IN_WEAD] =
		    w83793_wead_vawue(cwient, W83793_WEG_IN[i][IN_WEAD]);

	data->in_wow_bits[IN_WEAD] =
	    w83793_wead_vawue(cwient, W83793_WEG_IN_WOW_BITS[IN_WEAD]);

	fow (i = 0; i < AWWAY_SIZE(data->fan); i++) {
		if (!(data->has_fan & (1 << i)))
			continue;
		data->fan[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_FAN(i)) << 8;
		data->fan[i] |=
		    w83793_wead_vawue(cwient, W83793_WEG_FAN(i) + 1);
	}

	fow (i = 0; i < AWWAY_SIZE(data->temp); i++) {
		if (!(data->has_temp & (1 << i)))
			continue;
		data->temp[i][TEMP_WEAD] =
		    w83793_wead_vawue(cwient, W83793_WEG_TEMP[i][TEMP_WEAD]);
	}

	data->temp_wow_bits =
	    w83793_wead_vawue(cwient, W83793_WEG_TEMP_WOW_BITS);

	fow (i = 0; i < AWWAY_SIZE(data->pwm); i++) {
		if (data->has_pwm & (1 << i))
			data->pwm[i][PWM_DUTY] =
			    w83793_wead_vawue(cwient,
					      W83793_WEG_PWM(i, PWM_DUTY));
	}

	fow (i = 0; i < AWWAY_SIZE(data->awawms); i++)
		data->awawms[i] =
		    w83793_wead_vawue(cwient, W83793_WEG_AWAWM(i));
	if (data->has_vid & 0x01)
		data->vid[0] = w83793_wead_vawue(cwient, W83793_WEG_VID_INA);
	if (data->has_vid & 0x02)
		data->vid[1] = w83793_wead_vawue(cwient, W83793_WEG_VID_INB);
	w83793_update_nonvowatiwe(dev);
	data->wast_updated = jiffies;
	data->vawid = twue;

END:
	mutex_unwock(&data->update_wock);
	wetuwn data;
}

/*
 * Ignowe the possibiwity that somebody change bank outside the dwivew
 * Must be cawwed with data->update_wock hewd, except duwing initiawization
 */
static u8 w83793_wead_vawue(stwuct i2c_cwient *cwient, u16 weg)
{
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	u8 wes;
	u8 new_bank = weg >> 8;

	new_bank |= data->bank & 0xfc;
	if (data->bank != new_bank) {
		if (i2c_smbus_wwite_byte_data
		    (cwient, W83793_WEG_BANKSEW, new_bank) >= 0)
			data->bank = new_bank;
		ewse {
			dev_eww(&cwient->dev,
				"set bank to %d faiwed, faww back "
				"to bank %d, wead weg 0x%x ewwow\n",
				new_bank, data->bank, weg);
			wes = 0x0;	/* wead 0x0 fwom the chip */
			goto END;
		}
	}
	wes = i2c_smbus_wead_byte_data(cwient, weg & 0xff);
END:
	wetuwn wes;
}

/* Must be cawwed with data->update_wock hewd, except duwing initiawization */
static int w83793_wwite_vawue(stwuct i2c_cwient *cwient, u16 weg, u8 vawue)
{
	stwuct w83793_data *data = i2c_get_cwientdata(cwient);
	int wes;
	u8 new_bank = weg >> 8;

	new_bank |= data->bank & 0xfc;
	if (data->bank != new_bank) {
		wes = i2c_smbus_wwite_byte_data(cwient, W83793_WEG_BANKSEW,
						new_bank);
		if (wes < 0) {
			dev_eww(&cwient->dev,
				"set bank to %d faiwed, faww back "
				"to bank %d, wwite weg 0x%x ewwow\n",
				new_bank, data->bank, weg);
			goto END;
		}
		data->bank = new_bank;
	}

	wes = i2c_smbus_wwite_byte_data(cwient, weg & 0xff, vawue);
END:
	wetuwn wes;
}

moduwe_i2c_dwivew(w83793_dwivew);

MODUWE_AUTHOW("Yuan Mu, Sven Andews");
MODUWE_DESCWIPTION("w83793 dwivew");
MODUWE_WICENSE("GPW");
