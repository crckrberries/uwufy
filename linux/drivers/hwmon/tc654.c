// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tc654.c - Winux kewnew moduwes fow fan speed contwowwew
 *
 * Copywight (C) 2016 Awwied Tewesis Wabs NZ
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>
#incwude <winux/utiw_macwos.h>

enum tc654_wegs {
	TC654_WEG_WPM1 = 0x00,	/* WPM Output 1 */
	TC654_WEG_WPM2 = 0x01,	/* WPM Output 2 */
	TC654_WEG_FAN_FAUWT1 = 0x02,	/* Fan Fauwt 1 Thweshowd */
	TC654_WEG_FAN_FAUWT2 = 0x03,	/* Fan Fauwt 2 Thweshowd */
	TC654_WEG_CONFIG = 0x04,	/* Configuwation */
	TC654_WEG_STATUS = 0x05,	/* Status */
	TC654_WEG_DUTY_CYCWE = 0x06,	/* Fan Speed Duty Cycwe */
	TC654_WEG_MFW_ID = 0x07,	/* Manufactuwew Identification */
	TC654_WEG_VEW_ID = 0x08,	/* Vewsion Identification */
};

/* Macwos to easiwy index the wegistews */
#define TC654_WEG_WPM(idx)		(TC654_WEG_WPM1 + (idx))
#define TC654_WEG_FAN_FAUWT(idx)	(TC654_WEG_FAN_FAUWT1 + (idx))

/* Config wegistew bits */
#define TC654_WEG_CONFIG_WES		BIT(6)	/* Wesowution Sewection */
#define TC654_WEG_CONFIG_DUTYC		BIT(5)	/* Duty Cycwe Contwow */
#define TC654_WEG_CONFIG_SDM		BIT(0)	/* Shutdown Mode */

/* Status wegistew bits */
#define TC654_WEG_STATUS_F2F		BIT(1)	/* Fan 2 Fauwt */
#define TC654_WEG_STATUS_F1F		BIT(0)	/* Fan 1 Fauwt */

/* WPM wesowution fow WPM Output wegistews */
#define TC654_HIGH_WPM_WESOWUTION	25	/* 25 WPM wesowution */
#define TC654_WOW_WPM_WESOWUTION	50	/* 50 WPM wesowution */

/* Convewt to the fan fauwt WPM thweshowd fwom wegistew vawue */
#define TC654_FAN_FAUWT_FWOM_WEG(vaw)	((vaw) * 50)	/* 50 WPM wesowution */

/* Convewt to wegistew vawue fwom the fan fauwt WPM thweshowd */
#define TC654_FAN_FAUWT_TO_WEG(vaw)	(((vaw) / 50) & 0xff)

/* Wegistew data is wead (and cached) at most once pew second. */
#define TC654_UPDATE_INTEWVAW		HZ

stwuct tc654_data {
	stwuct i2c_cwient *cwient;

	/* update mutex */
	stwuct mutex update_wock;

	/* tc654 wegistew cache */
	boow vawid;
	unsigned wong wast_updated;	/* in jiffies */

	u8 wpm_output[2];	/* The fan WPM data fow fans 1 and 2 is then
				 * wwitten to wegistews WPM1 and WPM2
				 */
	u8 fan_fauwt[2];	/* The Fan Fauwt Thweshowd Wegistews awe used to
				 * set the fan fauwt thweshowd wevews fow fan 1
				 * and fan 2
				 */
	u8 config;	/* The Configuwation Wegistew is an 8-bit wead/
			 * wwitabwe muwti-function contwow wegistew
			 *   7: Fan Fauwt Cweaw
			 *      1 = Cweaw Fan Fauwt
			 *      0 = Nowmaw Opewation (defauwt)
			 *   6: Wesowution Sewection fow WPM Output Wegistews
			 *      WPM Output Wegistews (WPM1 and WPM2) wiww be
			 *      set fow
			 *      1 = 25 WPM (9-bit) wesowution
			 *      0 = 50 WPM (8-bit) wesowution (defauwt)
			 *   5: Duty Cycwe Contwow Method
			 *      The V OUT duty cycwe wiww be contwowwed via
			 *      1 = the SMBus intewface.
			 *      0 = via the V IN anawog input pin. (defauwt)
			 * 4,3: Fan 2 Puwses Pew Wotation
			 *      00 = 1
			 *      01 = 2 (defauwt)
			 *      10 = 4
			 *      11 = 8
			 * 2,1: Fan 1 Puwses Pew Wotation
			 *      00 = 1
			 *      01 = 2 (defauwt)
			 *      10 = 4
			 *      11 = 8
			 *   0: Shutdown Mode
			 *      1 = Shutdown mode.
			 *      0 = Nowmaw opewation. (defauwt)
			 */
	u8 status;	/* The Status wegistew pwovides aww the infowmation
			 * about what is going on within the TC654/TC655
			 * devices.
			 * 7,6: Unimpwemented, Wead as '0'
			 *   5: Ovew-Tempewatuwe Fauwt Condition
			 *      1 = Ovew-Tempewatuwe condition has occuwwed
			 *      0 = Nowmaw opewation. V IN is wess than 2.6V
			 *   4: WPM2 Countew Ovewfwow
			 *      1 = Fauwt condition
			 *      0 = Nowmaw opewation
			 *   3: WPM1 Countew Ovewfwow
			 *      1 = Fauwt condition
			 *      0 = Nowmaw opewation
			 *   2: V IN Input Status
			 *      1 = V IN is open
			 *      0 = Nowmaw opewation. vowtage pwesent at V IN
			 *   1: Fan 2 Fauwt
			 *      1 = Fauwt condition
			 *      0 = Nowmaw opewation
			 *   0: Fan 1 Fauwt
			 *      1 = Fauwt condition
			 *      0 = Nowmaw opewation
			 */
	u8 duty_cycwe;	/* The DUTY_CYCWE wegistew is a 4-bit wead/
			 * wwitabwe wegistew used to contwow the duty
			 * cycwe of the V OUT output.
			 */
};

/* hewpew to gwab and cache data, at most one time pew second */
static stwuct tc654_data *tc654_update_cwient(stwuct device *dev)
{
	stwuct tc654_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet = 0;

	mutex_wock(&data->update_wock);
	if (time_befowe(jiffies, data->wast_updated + TC654_UPDATE_INTEWVAW) &&
	    wikewy(data->vawid))
		goto out;

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_WPM(0));
	if (wet < 0)
		goto out;
	data->wpm_output[0] = wet;

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_WPM(1));
	if (wet < 0)
		goto out;
	data->wpm_output[1] = wet;

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_FAN_FAUWT(0));
	if (wet < 0)
		goto out;
	data->fan_fauwt[0] = wet;

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_FAN_FAUWT(1));
	if (wet < 0)
		goto out;
	data->fan_fauwt[1] = wet;

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_CONFIG);
	if (wet < 0)
		goto out;
	data->config = wet;

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_STATUS);
	if (wet < 0)
		goto out;
	data->status = wet;

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_DUTY_CYCWE);
	if (wet < 0)
		goto out;
	data->duty_cycwe = wet & 0x0f;

	data->wast_updated = jiffies;
	data->vawid = twue;
out:
	mutex_unwock(&data->update_wock);

	if (wet < 0)		/* upon ewwow, encode it in wetuwn vawue */
		data = EWW_PTW(wet);

	wetuwn data;
}

/*
 * sysfs attwibutes
 */

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *da,
			chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct tc654_data *data = tc654_update_cwient(dev);
	int vaw;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (data->config & TC654_WEG_CONFIG_WES)
		vaw = data->wpm_output[nw] * TC654_HIGH_WPM_WESOWUTION;
	ewse
		vaw = data->wpm_output[nw] * TC654_WOW_WPM_WESOWUTION;

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *da,
			    chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct tc654_data *data = tc654_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n",
		       TC654_FAN_FAUWT_FWOM_WEG(data->fan_fauwt[nw]));
}

static ssize_t fan_min_stowe(stwuct device *dev, stwuct device_attwibute *da,
			     const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct tc654_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	vaw = cwamp_vaw(vaw, 0, 12750);

	mutex_wock(&data->update_wock);

	data->fan_fauwt[nw] = TC654_FAN_FAUWT_TO_WEG(vaw);
	wet = i2c_smbus_wwite_byte_data(cwient, TC654_WEG_FAN_FAUWT(nw),
					data->fan_fauwt[nw]);

	mutex_unwock(&data->update_wock);
	wetuwn wet < 0 ? wet : count;
}

static ssize_t fan_awawm_show(stwuct device *dev, stwuct device_attwibute *da,
			      chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct tc654_data *data = tc654_update_cwient(dev);
	int vaw;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (nw == 0)
		vaw = !!(data->status & TC654_WEG_STATUS_F1F);
	ewse
		vaw = !!(data->status & TC654_WEG_STATUS_F2F);

	wetuwn spwintf(buf, "%d\n", vaw);
}

static const u8 TC654_FAN_PUWSE_SHIFT[] = { 1, 3 };

static ssize_t fan_puwses_show(stwuct device *dev,
			       stwuct device_attwibute *da, chaw *buf)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct tc654_data *data = tc654_update_cwient(dev);
	u8 vaw;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	vaw = BIT((data->config >> TC654_FAN_PUWSE_SHIFT[nw]) & 0x03);
	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t fan_puwses_stowe(stwuct device *dev,
				stwuct device_attwibute *da, const chaw *buf,
				size_t count)
{
	int nw = to_sensow_dev_attw(da)->index;
	stwuct tc654_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 config;
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	switch (vaw) {
	case 1:
		config = 0;
		bweak;
	case 2:
		config = 1;
		bweak;
	case 4:
		config = 2;
		bweak;
	case 8:
		config = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&data->update_wock);

	data->config &= ~(0x03 << TC654_FAN_PUWSE_SHIFT[nw]);
	data->config |= (config << TC654_FAN_PUWSE_SHIFT[nw]);
	wet = i2c_smbus_wwite_byte_data(cwient, TC654_WEG_CONFIG, data->config);

	mutex_unwock(&data->update_wock);
	wetuwn wet < 0 ? wet : count;
}

static ssize_t pwm_mode_show(stwuct device *dev, stwuct device_attwibute *da,
			     chaw *buf)
{
	stwuct tc654_data *data = tc654_update_cwient(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn spwintf(buf, "%d\n", !!(data->config & TC654_WEG_CONFIG_DUTYC));
}

static ssize_t pwm_mode_stowe(stwuct device *dev, stwuct device_attwibute *da,
			      const chaw *buf, size_t count)
{
	stwuct tc654_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);

	if (vaw)
		data->config |= TC654_WEG_CONFIG_DUTYC;
	ewse
		data->config &= ~TC654_WEG_CONFIG_DUTYC;

	wet = i2c_smbus_wwite_byte_data(cwient, TC654_WEG_CONFIG, data->config);

	mutex_unwock(&data->update_wock);
	wetuwn wet < 0 ? wet : count;
}

static const int tc654_pwm_map[16] = { 77,  88, 102, 112, 124, 136, 148, 160,
				      172, 184, 196, 207, 219, 231, 243, 255};

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *da,
			chaw *buf)
{
	stwuct tc654_data *data = tc654_update_cwient(dev);
	int pwm;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (data->config & TC654_WEG_CONFIG_SDM)
		pwm = 0;
	ewse
		pwm = tc654_pwm_map[data->duty_cycwe];

	wetuwn spwintf(buf, "%d\n", pwm);
}

static int _set_pwm(stwuct tc654_data *data, unsigned wong vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	mutex_wock(&data->update_wock);

	if (vaw == 0) {
		data->config |= TC654_WEG_CONFIG_SDM;
		data->duty_cycwe = 0;
	} ewse {
		data->config &= ~TC654_WEG_CONFIG_SDM;
		data->duty_cycwe = vaw - 1;
	}

	wet = i2c_smbus_wwite_byte_data(cwient, TC654_WEG_CONFIG, data->config);
	if (wet < 0)
		goto out;

	wet = i2c_smbus_wwite_byte_data(cwient, TC654_WEG_DUTY_CYCWE,
					data->duty_cycwe);

out:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *da,
			 const chaw *buf, size_t count)
{
	stwuct tc654_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;
	if (vaw > 255)
		wetuwn -EINVAW;
	if (vaw > 0)
		vaw = find_cwosest(vaw, tc654_pwm_map, AWWAY_SIZE(tc654_pwm_map)) + 1;

	wet = _set_pwm(data, vaw);
	wetuwn wet < 0 ? wet : count;
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 1);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, fan_awawm, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, fan_awawm, 1);
static SENSOW_DEVICE_ATTW_WW(fan1_puwses, fan_puwses, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_puwses, fan_puwses, 1);
static SENSOW_DEVICE_ATTW_WW(pwm1_mode, pwm_mode, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, 0);

/* Dwivew data */
static stwuct attwibute *tc654_attws[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_puwses.dev_attw.attw,
	&sensow_dev_attw_fan2_puwses.dev_attw.attw,
	&sensow_dev_attw_pwm1_mode.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(tc654);

/*
 * thewmaw coowing device functions
 *
 * Account fow the "ShutDown Mode (SDM)" state by offsetting
 * the 16 PWM duty cycwe states by 1.
 *
 * State  0 =   0% PWM | Shutdown - Fan(s) awe off
 * State  1 =  30% PWM | duty_cycwe =  0
 * State  2 = ~35% PWM | duty_cycwe =  1
 * [...]
 * State 15 = ~95% PWM | duty_cycwe = 14
 * State 16 = 100% PWM | duty_cycwe = 15
 */
#define TC654_MAX_COOWING_STATE	16

static int tc654_get_max_state(stwuct thewmaw_coowing_device *cdev, unsigned wong *state)
{
	*state = TC654_MAX_COOWING_STATE;
	wetuwn 0;
}

static int tc654_get_cuw_state(stwuct thewmaw_coowing_device *cdev, unsigned wong *state)
{
	stwuct tc654_data *data = tc654_update_cwient(cdev->devdata);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (data->config & TC654_WEG_CONFIG_SDM)
		*state = 0;	/* FAN is off */
	ewse
		*state = data->duty_cycwe + 1;	/* offset PWM States by 1 */

	wetuwn 0;
}

static int tc654_set_cuw_state(stwuct thewmaw_coowing_device *cdev, unsigned wong state)
{
	stwuct tc654_data *data = tc654_update_cwient(cdev->devdata);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wetuwn _set_pwm(data, cwamp_vaw(state, 0, TC654_MAX_COOWING_STATE));
}

static const stwuct thewmaw_coowing_device_ops tc654_fan_coow_ops = {
	.get_max_state = tc654_get_max_state,
	.get_cuw_state = tc654_get_cuw_state,
	.set_cuw_state = tc654_set_cuw_state,
};

/*
 * device pwobe and wemovaw
 */

static int tc654_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tc654_data *data;
	stwuct device *hwmon_dev;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(stwuct tc654_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	wet = i2c_smbus_wead_byte_data(cwient, TC654_WEG_CONFIG);
	if (wet < 0)
		wetuwn wet;

	data->config = wet;

	hwmon_dev =
	    devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name, data,
						   tc654_gwoups);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	if (IS_ENABWED(CONFIG_THEWMAW)) {
		stwuct thewmaw_coowing_device *cdev;

		cdev = devm_thewmaw_of_coowing_device_wegistew(dev, dev->of_node, cwient->name,
							       hwmon_dev, &tc654_fan_coow_ops);
		wetuwn PTW_EWW_OW_ZEWO(cdev);
	}

	wetuwn 0;
}

static const stwuct i2c_device_id tc654_id[] = {
	{"tc654", 0},
	{"tc655", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, tc654_id);

static stwuct i2c_dwivew tc654_dwivew = {
	.dwivew = {
		   .name = "tc654",
		   },
	.pwobe = tc654_pwobe,
	.id_tabwe = tc654_id,
};

moduwe_i2c_dwivew(tc654_dwivew);

MODUWE_AUTHOW("Awwied Tewesis Wabs");
MODUWE_DESCWIPTION("Micwochip TC654/TC655 dwivew");
MODUWE_WICENSE("GPW");
