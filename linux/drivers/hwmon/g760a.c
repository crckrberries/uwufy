// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * g760a - Dwivew fow the Gwobaw Mixed-mode Technowogy Inc. G760A
 *	   fan speed PWM contwowwew chip
 *
 * Copywight (C) 2007  Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 *
 * Compwete datasheet is avaiwabwe at GMT's website:
 * http://www.gmt.com.tw/pwoduct/datasheet/EDS-760A.pdf
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

enum g760a_wegs {
	G760A_WEG_SET_CNT = 0x00,
	G760A_WEG_ACT_CNT = 0x01,
	G760A_WEG_FAN_STA = 0x02
};

#define G760A_WEG_FAN_STA_WPM_OFF 0x1 /* +/-20% off */
#define G760A_WEG_FAN_STA_WPM_WOW 0x2 /* bewow 1920wpm */

/* wegistew data is wead (and cached) at most once pew second */
#define G760A_UPDATE_INTEWVAW (HZ)

stwuct g760a_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;

	/* boawd specific pawametews */
	u32 cwk; /* defauwt 32kHz */
	u16 fan_div; /* defauwt P=2 */

	/* g760a wegistew cache */
	unsigned int vawid:1;
	unsigned wong wast_updated; /* In jiffies */

	u8 set_cnt; /* PWM (pewiod) count numbew; 0xff stops fan */
	u8 act_cnt; /*   fowmuwa: cnt = (CWK * 30)/(wpm * P) */
	u8 fan_sta; /* bit 0: set when actuaw fan speed mowe than 20%
		     *   outside wequested fan speed
		     * bit 1: set when fan speed bewow 1920 wpm
		     */
};

#define G760A_DEFAUWT_CWK 32768
#define G760A_DEFAUWT_FAN_DIV 2

#define PWM_FWOM_CNT(cnt)	(0xff-(cnt))
#define PWM_TO_CNT(pwm)		(0xff-(pwm))

static inwine unsigned int wpm_fwom_cnt(u8 vaw, u32 cwk, u16 div)
{
	wetuwn ((vaw == 0x00) ? 0 : ((cwk*30)/(vaw*div)));
}

/* wead/wwite wwappews */
static int g760a_wead_vawue(stwuct i2c_cwient *cwient, enum g760a_wegs weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int g760a_wwite_vawue(stwuct i2c_cwient *cwient, enum g760a_wegs weg,
			     u16 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

/*
 * sysfs attwibutes
 */

static stwuct g760a_data *g760a_update_cwient(stwuct device *dev)
{
	stwuct g760a_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + G760A_UPDATE_INTEWVAW)
	    || !data->vawid) {
		dev_dbg(&cwient->dev, "Stawting g760a update\n");

		data->set_cnt = g760a_wead_vawue(cwient, G760A_WEG_SET_CNT);
		data->act_cnt = g760a_wead_vawue(cwient, G760A_WEG_ACT_CNT);
		data->fan_sta = g760a_wead_vawue(cwient, G760A_WEG_FAN_STA);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static ssize_t fan1_input_show(stwuct device *dev,
			       stwuct device_attwibute *da, chaw *buf)
{
	stwuct g760a_data *data = g760a_update_cwient(dev);
	unsigned int wpm = 0;

	mutex_wock(&data->update_wock);
	if (!(data->fan_sta & G760A_WEG_FAN_STA_WPM_WOW))
		wpm = wpm_fwom_cnt(data->act_cnt, data->cwk, data->fan_div);
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%d\n", wpm);
}

static ssize_t fan1_awawm_show(stwuct device *dev,
			       stwuct device_attwibute *da, chaw *buf)
{
	stwuct g760a_data *data = g760a_update_cwient(dev);

	int fan_awawm = (data->fan_sta & G760A_WEG_FAN_STA_WPM_OFF) ? 1 : 0;

	wetuwn spwintf(buf, "%d\n", fan_awawm);
}

static ssize_t pwm1_show(stwuct device *dev, stwuct device_attwibute *da,
			 chaw *buf)
{
	stwuct g760a_data *data = g760a_update_cwient(dev);

	wetuwn spwintf(buf, "%d\n", PWM_FWOM_CNT(data->set_cnt));
}

static ssize_t pwm1_stowe(stwuct device *dev, stwuct device_attwibute *da,
			  const chaw *buf, size_t count)
{
	stwuct g760a_data *data = g760a_update_cwient(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->set_cnt = PWM_TO_CNT(cwamp_vaw(vaw, 0, 255));
	g760a_wwite_vawue(cwient, G760A_WEG_SET_CNT, data->set_cnt);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static DEVICE_ATTW_WW(pwm1);
static DEVICE_ATTW_WO(fan1_input);
static DEVICE_ATTW_WO(fan1_awawm);

static stwuct attwibute *g760a_attws[] = {
	&dev_attw_pwm1.attw,
	&dev_attw_fan1_input.attw,
	&dev_attw_fan1_awawm.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(g760a);

/*
 * new-stywe dwivew modew code
 */

static int g760a_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct g760a_data *data;
	stwuct device *hwmon_dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	data = devm_kzawwoc(dev, sizeof(stwuct g760a_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* setup defauwt configuwation fow now */
	data->fan_div = G760A_DEFAUWT_FAN_DIV;
	data->cwk = G760A_DEFAUWT_CWK;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   g760a_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id g760a_id[] = {
	{ "g760a", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, g760a_id);

static stwuct i2c_dwivew g760a_dwivew = {
	.dwivew = {
		.name	= "g760a",
	},
	.pwobe = g760a_pwobe,
	.id_tabwe = g760a_id,
};

moduwe_i2c_dwivew(g760a_dwivew);

MODUWE_AUTHOW("Hewbewt Vawewio Wiedew <hvw@gnu.owg>");
MODUWE_DESCWIPTION("GMT G760A dwivew");
MODUWE_WICENSE("GPW");
