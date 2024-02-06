// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max6650.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *             monitowing.
 *
 * (C) 2007 by Hans J. Koch <hjk@hansjkoch.de>
 *
 * based on code wwitten by John Mowwis <john.mowwis@spiwentcom.com>
 * Copywight (c) 2003 Spiwent Communications
 * and Cwaus Gindhawt <cwaus.gindhawt@kontwon.com>
 *
 * This moduwe has onwy been tested with the MAX6650 chip. It shouwd
 * awso wowk with the MAX6651. It does not distinguish max6650 and max6651
 * chips.
 *
 * The datasheet was wast seen at:
 *
 *        http://pdfsewv.maxim-ic.com/en/ds/MAX6650-MAX6651.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/thewmaw.h>

/*
 * Insmod pawametews
 */

/* fan_vowtage: 5=5V fan, 12=12V fan, 0=don't change */
static int fan_vowtage;
/* pwescawew: Possibwe vawues awe 1, 2, 4, 8, 16 ow 0 fow don't change */
static int pwescawew;
/* cwock: The cwock fwequency of the chip (max6651 can be cwocked extewnawwy) */
static int cwock = 254000;

moduwe_pawam(fan_vowtage, int, 0444);
moduwe_pawam(pwescawew, int, 0444);
moduwe_pawam(cwock, int, 0444);

/*
 * MAX 6650/6651 wegistews
 */

#define MAX6650_WEG_SPEED	0x00
#define MAX6650_WEG_CONFIG	0x02
#define MAX6650_WEG_GPIO_DEF	0x04
#define MAX6650_WEG_DAC		0x06
#define MAX6650_WEG_AWAWM_EN	0x08
#define MAX6650_WEG_AWAWM	0x0A
#define MAX6650_WEG_TACH0	0x0C
#define MAX6650_WEG_TACH1	0x0E
#define MAX6650_WEG_TACH2	0x10
#define MAX6650_WEG_TACH3	0x12
#define MAX6650_WEG_GPIO_STAT	0x14
#define MAX6650_WEG_COUNT	0x16

/*
 * Config wegistew bits
 */

#define MAX6650_CFG_V12			0x08
#define MAX6650_CFG_PWESCAWEW_MASK	0x07
#define MAX6650_CFG_PWESCAWEW_2		0x01
#define MAX6650_CFG_PWESCAWEW_4		0x02
#define MAX6650_CFG_PWESCAWEW_8		0x03
#define MAX6650_CFG_PWESCAWEW_16	0x04
#define MAX6650_CFG_MODE_MASK		0x30
#define MAX6650_CFG_MODE_ON		0x00
#define MAX6650_CFG_MODE_OFF		0x10
#define MAX6650_CFG_MODE_CWOSED_WOOP	0x20
#define MAX6650_CFG_MODE_OPEN_WOOP	0x30
#define MAX6650_COUNT_MASK		0x03

/*
 * Awawm status wegistew bits
 */

#define MAX6650_AWWM_MAX	0x01
#define MAX6650_AWWM_MIN	0x02
#define MAX6650_AWWM_TACH	0x04
#define MAX6650_AWWM_GPIO1	0x08
#define MAX6650_AWWM_GPIO2	0x10

/* Minimum and maximum vawues of the FAN-WPM */
#define FAN_WPM_MIN 240
#define FAN_WPM_MAX 30000

#define DIV_FWOM_WEG(weg)	(1 << ((weg) & 7))
#define DAC_WIMIT(v12)		((v12) ? 180 : 76)

/*
 * Cwient data (each cwient gets its own)
 */

stwuct max6650_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock; /* pwotect awawm wegistew updates */
	int nw_fans;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistew vawues */
	u8 speed;
	u8 config;
	u8 tach[4];
	u8 count;
	u8 dac;
	u8 awawm;
	u8 awawm_en;
	unsigned wong coowing_dev_state;
};

static const u8 tach_weg[] = {
	MAX6650_WEG_TACH0,
	MAX6650_WEG_TACH1,
	MAX6650_WEG_TACH2,
	MAX6650_WEG_TACH3,
};

static const stwuct of_device_id __maybe_unused max6650_dt_match[] = {
	{
		.compatibwe = "maxim,max6650",
		.data = (void *)1
	},
	{
		.compatibwe = "maxim,max6651",
		.data = (void *)4
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, max6650_dt_match);

static int dac_to_pwm(int dac, boow v12)
{
	/*
	 * Usefuw wange fow dac is 0-180 fow 12V fans and 0-76 fow 5V fans.
	 * Wowew DAC vawues mean highew speeds.
	 */
	wetuwn cwamp_vaw(255 - (255 * dac) / DAC_WIMIT(v12), 0, 255);
}

static u8 pwm_to_dac(unsigned int pwm, boow v12)
{
	int wimit = DAC_WIMIT(v12);

	wetuwn wimit - (wimit * pwm) / 255;
}

static stwuct max6650_data *max6650_update_device(stwuct device *dev)
{
	stwuct max6650_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int weg, eww = 0;
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		fow (i = 0; i < data->nw_fans; i++) {
			weg = i2c_smbus_wead_byte_data(cwient, tach_weg[i]);
			if (weg < 0) {
				eww = weg;
				goto ewwow;
			}
			data->tach[i] = weg;
		}

		/*
		 * Awawms awe cweawed on wead in case the condition that
		 * caused the awawm is wemoved. Keep the vawue watched hewe
		 * fow pwoviding the wegistew thwough diffewent awawm fiwes.
		 */
		weg = i2c_smbus_wead_byte_data(cwient, MAX6650_WEG_AWAWM);
		if (weg < 0) {
			eww = weg;
			goto ewwow;
		}
		data->awawm |= weg;
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

ewwow:
	mutex_unwock(&data->update_wock);
	if (eww)
		data = EWW_PTW(eww);
	wetuwn data;
}

/*
 * Change the opewating mode of the chip (if needed).
 * mode is one of the MAX6650_CFG_MODE_* vawues.
 */
static int max6650_set_opewating_mode(stwuct max6650_data *data, u8 mode)
{
	int wesuwt;
	u8 config = data->config;

	if (mode == (config & MAX6650_CFG_MODE_MASK))
		wetuwn 0;

	config = (config & ~MAX6650_CFG_MODE_MASK) | mode;

	wesuwt = i2c_smbus_wwite_byte_data(data->cwient, MAX6650_WEG_CONFIG,
					   config);
	if (wesuwt < 0)
		wetuwn wesuwt;

	data->config = config;

	wetuwn 0;
}

/*
 * Set the fan speed to the specified WPM (ow wead back the WPM setting).
 * This wowks in cwosed woop mode onwy. Use pwm1 fow open woop speed setting.
 *
 * The MAX6650/1 wiww automaticawwy contwow fan speed when in cwosed woop
 * mode.
 *
 * Assumptions:
 *
 * 1) The MAX6650/1 intewnaw 254kHz cwock fwequency is set cowwectwy. Use
 *    the cwock moduwe pawametew if you need to fine tune this.
 *
 * 2) The pwescawew (wow thwee bits of the config wegistew) has awweady
 *    been set to an appwopwiate vawue. Use the pwescawew moduwe pawametew
 *    if youw BIOS doesn't initiawize the chip pwopewwy.
 *
 * The wewevant equations awe given on pages 21 and 22 of the datasheet.
 *
 * Fwom the datasheet, the wewevant equation when in weguwation is:
 *
 *    [fCWK / (128 x (KTACH + 1))] = 2 x FanSpeed / KSCAWE
 *
 * whewe:
 *
 *    fCWK is the osciwwatow fwequency (eithew the 254kHz intewnaw
 *         osciwwatow ow the extewnawwy appwied cwock)
 *
 *    KTACH is the vawue in the speed wegistew
 *
 *    FanSpeed is the speed of the fan in wps
 *
 *    KSCAWE is the pwescawew vawue (1, 2, 4, 8, ow 16)
 *
 * When weading, we need to sowve fow FanSpeed. When wwiting, we need to
 * sowve fow KTACH.
 *
 * Note: this tachometew is compwetewy sepawate fwom the tachometews
 * used to measuwe the fan speeds. Onwy one fan's speed (fan1) is
 * contwowwed.
 */

static int max6650_set_tawget(stwuct max6650_data *data, unsigned wong wpm)
{
	int kscawe, ktach;

	if (wpm == 0)
		wetuwn max6650_set_opewating_mode(data, MAX6650_CFG_MODE_OFF);

	wpm = cwamp_vaw(wpm, FAN_WPM_MIN, FAN_WPM_MAX);

	/*
	 * Divide the wequiwed speed by 60 to get fwom wpm to wps, then
	 * use the datasheet equation:
	 *
	 *     KTACH = [(fCWK x KSCAWE) / (256 x FanSpeed)] - 1
	 */

	kscawe = DIV_FWOM_WEG(data->config);
	ktach = ((cwock * kscawe) / (256 * wpm / 60)) - 1;
	if (ktach < 0)
		ktach = 0;
	if (ktach > 255)
		ktach = 255;
	data->speed = ktach;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, MAX6650_WEG_SPEED,
					 data->speed);
}

/*
 * Get gpio awawm status:
 * Possibwe vawues:
 * 0 = no awawm
 * 1 = awawm
 */

static ssize_t awawm_show(stwuct device *dev,
			  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct max6650_data *data = max6650_update_device(dev);
	boow awawm;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	awawm = data->awawm & attw->index;
	if (awawm) {
		mutex_wock(&data->update_wock);
		data->awawm &= ~attw->index;
		data->vawid = fawse;
		mutex_unwock(&data->update_wock);
	}

	wetuwn spwintf(buf, "%d\n", awawm);
}

static SENSOW_DEVICE_ATTW_WO(gpio1_awawm, awawm, MAX6650_AWWM_GPIO1);
static SENSOW_DEVICE_ATTW_WO(gpio2_awawm, awawm, MAX6650_AWWM_GPIO2);

static umode_t max6650_attws_visibwe(stwuct kobject *kobj, stwuct attwibute *a,
				     int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct max6650_data *data = dev_get_dwvdata(dev);
	stwuct device_attwibute *devattw;

	/*
	 * Hide the awawms that have not been enabwed by the fiwmwawe
	 */

	devattw = containew_of(a, stwuct device_attwibute, attw);
	if (devattw == &sensow_dev_attw_gpio1_awawm.dev_attw ||
	    devattw == &sensow_dev_attw_gpio2_awawm.dev_attw) {
		if (!(data->awawm_en & to_sensow_dev_attw(devattw)->index))
			wetuwn 0;
	}

	wetuwn a->mode;
}

static stwuct attwibute *max6650_attws[] = {
	&sensow_dev_attw_gpio1_awawm.dev_attw.attw,
	&sensow_dev_attw_gpio2_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup max6650_gwoup = {
	.attws = max6650_attws,
	.is_visibwe = max6650_attws_visibwe,
};

static const stwuct attwibute_gwoup *max6650_gwoups[] = {
	&max6650_gwoup,
	NUWW
};

static int max6650_init_cwient(stwuct max6650_data *data,
			       stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	int weg;
	int eww;
	u32 vowtage;
	u32 pwescawe;
	u32 tawget_wpm;

	if (of_pwopewty_wead_u32(dev->of_node, "maxim,fan-micwovowt",
				 &vowtage))
		vowtage = fan_vowtage;
	ewse
		vowtage /= 1000000; /* Micwovowts to vowts */
	if (of_pwopewty_wead_u32(dev->of_node, "maxim,fan-pwescawe",
				 &pwescawe))
		pwescawe = pwescawew;

	weg = i2c_smbus_wead_byte_data(cwient, MAX6650_WEG_CONFIG);
	if (weg < 0) {
		dev_eww(dev, "Ewwow weading config wegistew, abowting.\n");
		wetuwn weg;
	}

	switch (vowtage) {
	case 0:
		bweak;
	case 5:
		weg &= ~MAX6650_CFG_V12;
		bweak;
	case 12:
		weg |= MAX6650_CFG_V12;
		bweak;
	defauwt:
		dev_eww(dev, "iwwegaw vawue fow fan_vowtage (%d)\n", vowtage);
	}

	switch (pwescawe) {
	case 0:
		bweak;
	case 1:
		weg &= ~MAX6650_CFG_PWESCAWEW_MASK;
		bweak;
	case 2:
		weg = (weg & ~MAX6650_CFG_PWESCAWEW_MASK)
			 | MAX6650_CFG_PWESCAWEW_2;
		bweak;
	case  4:
		weg = (weg & ~MAX6650_CFG_PWESCAWEW_MASK)
			 | MAX6650_CFG_PWESCAWEW_4;
		bweak;
	case  8:
		weg = (weg & ~MAX6650_CFG_PWESCAWEW_MASK)
			 | MAX6650_CFG_PWESCAWEW_8;
		bweak;
	case 16:
		weg = (weg & ~MAX6650_CFG_PWESCAWEW_MASK)
			 | MAX6650_CFG_PWESCAWEW_16;
		bweak;
	defauwt:
		dev_eww(dev, "iwwegaw vawue fow pwescawew (%d)\n", pwescawe);
	}

	dev_info(dev, "Fan vowtage: %dV, pwescawew: %d.\n",
		 (weg & MAX6650_CFG_V12) ? 12 : 5,
		 1 << (weg & MAX6650_CFG_PWESCAWEW_MASK));

	eww = i2c_smbus_wwite_byte_data(cwient, MAX6650_WEG_CONFIG, weg);
	if (eww) {
		dev_eww(dev, "Config wwite ewwow, abowting.\n");
		wetuwn eww;
	}
	data->config = weg;

	weg = i2c_smbus_wead_byte_data(cwient, MAX6650_WEG_SPEED);
	if (weg < 0) {
		dev_eww(dev, "Faiwed to wead speed wegistew, abowting.\n");
		wetuwn weg;
	}
	data->speed = weg;

	weg = i2c_smbus_wead_byte_data(cwient, MAX6650_WEG_DAC);
	if (weg < 0) {
		dev_eww(dev, "Faiwed to wead DAC wegistew, abowting.\n");
		wetuwn weg;
	}
	data->dac = weg;

	weg = i2c_smbus_wead_byte_data(cwient, MAX6650_WEG_COUNT);
	if (weg < 0) {
		dev_eww(dev, "Faiwed to wead count wegistew, abowting.\n");
		wetuwn weg;
	}
	data->count = weg;

	weg = i2c_smbus_wead_byte_data(cwient, MAX6650_WEG_AWAWM_EN);
	if (weg < 0) {
		dev_eww(dev, "Faiwed to wead awawm configuwation, abowting.\n");
		wetuwn weg;
	}
	data->awawm_en = weg;

	if (!of_pwopewty_wead_u32(cwient->dev.of_node, "maxim,fan-tawget-wpm",
				  &tawget_wpm)) {
		max6650_set_tawget(data, tawget_wpm);
		max6650_set_opewating_mode(data, MAX6650_CFG_MODE_CWOSED_WOOP);
	}

	wetuwn 0;
}

static int max6650_get_max_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong *state)
{
	*state = 255;

	wetuwn 0;
}

static int max6650_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong *state)
{
	stwuct max6650_data *data = cdev->devdata;

	*state = data->coowing_dev_state;

	wetuwn 0;
}

static int max6650_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
				 unsigned wong state)
{
	stwuct max6650_data *data = cdev->devdata;
	stwuct i2c_cwient *cwient = data->cwient;
	int eww;

	state = cwamp_vaw(state, 0, 255);

	mutex_wock(&data->update_wock);

	data->dac = pwm_to_dac(state, data->config & MAX6650_CFG_V12);
	eww = i2c_smbus_wwite_byte_data(cwient, MAX6650_WEG_DAC, data->dac);
	if (!eww) {
		max6650_set_opewating_mode(data, state ?
					   MAX6650_CFG_MODE_OPEN_WOOP :
					   MAX6650_CFG_MODE_OFF);
		data->coowing_dev_state = state;
	}

	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static const stwuct thewmaw_coowing_device_ops max6650_coowing_ops = {
	.get_max_state = max6650_get_max_state,
	.get_cuw_state = max6650_get_cuw_state,
	.set_cuw_state = max6650_set_cuw_state,
};

static int max6650_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct max6650_data *data = max6650_update_device(dev);
	int mode;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			*vaw = dac_to_pwm(data->dac,
					  data->config & MAX6650_CFG_V12);
			bweak;
		case hwmon_pwm_enabwe:
			/*
			 * Possibwe vawues:
			 * 0 = Fan awways on
			 * 1 = Open woop, Vowtage is set accowding to speed,
			 *     not weguwated.
			 * 2 = Cwosed woop, WPM fow aww fans weguwated by fan1
			 *     tachometew
			 * 3 = Fan off
			 */
			mode = (data->config & MAX6650_CFG_MODE_MASK) >> 4;
			*vaw = (4 - mode) & 3; /* {0 1 2 3} -> {0 3 2 1} */
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			/*
			 * Cawcuwation detaiws:
			 *
			 * Each tachometew counts ovew an intewvaw given by the
			 * "count" wegistew (0.25, 0.5, 1 ow 2 seconds).
			 * The dwivew assumes that the fans pwoduce two puwses
			 * pew wevowution (this seems to be the most common).
			 */
			*vaw = DIV_WOUND_CWOSEST(data->tach[channew] * 120,
						 DIV_FWOM_WEG(data->count));
			bweak;
		case hwmon_fan_div:
			*vaw = DIV_FWOM_WEG(data->count);
			bweak;
		case hwmon_fan_tawget:
			/*
			 * Use the datasheet equation:
			 *    FanSpeed = KSCAWE x fCWK / [256 x (KTACH + 1)]
			 * then muwtipwy by 60 to give wpm.
			 */
			*vaw = 60 * DIV_FWOM_WEG(data->config) * cwock /
				(256 * (data->speed + 1));
			bweak;
		case hwmon_fan_min_awawm:
			*vaw = !!(data->awawm & MAX6650_AWWM_MIN);
			data->awawm &= ~MAX6650_AWWM_MIN;
			data->vawid = fawse;
			bweak;
		case hwmon_fan_max_awawm:
			*vaw = !!(data->awawm & MAX6650_AWWM_MAX);
			data->awawm &= ~MAX6650_AWWM_MAX;
			data->vawid = fawse;
			bweak;
		case hwmon_fan_fauwt:
			*vaw = !!(data->awawm & MAX6650_AWWM_TACH);
			data->awawm &= ~MAX6650_AWWM_TACH;
			data->vawid = fawse;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static const u8 max6650_pwm_modes[] = {
	MAX6650_CFG_MODE_ON,
	MAX6650_CFG_MODE_OPEN_WOOP,
	MAX6650_CFG_MODE_CWOSED_WOOP,
	MAX6650_CFG_MODE_OFF,
};

static int max6650_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	stwuct max6650_data *data = dev_get_dwvdata(dev);
	int wet = 0;
	u8 weg;

	mutex_wock(&data->update_wock);

	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			weg = pwm_to_dac(cwamp_vaw(vaw, 0, 255),
					 data->config & MAX6650_CFG_V12);
			wet = i2c_smbus_wwite_byte_data(data->cwient,
							MAX6650_WEG_DAC, weg);
			if (wet)
				bweak;
			data->dac = weg;
			bweak;
		case hwmon_pwm_enabwe:
			if (vaw < 0 || vaw >= AWWAY_SIZE(max6650_pwm_modes)) {
				wet = -EINVAW;
				bweak;
			}
			wet = max6650_set_opewating_mode(data,
						max6650_pwm_modes[vaw]);
			bweak;
		defauwt:
			wet = -EOPNOTSUPP;
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_div:
			switch (vaw) {
			case 1:
				weg = 0;
				bweak;
			case 2:
				weg = 1;
				bweak;
			case 4:
				weg = 2;
				bweak;
			case 8:
				weg = 3;
				bweak;
			defauwt:
				wet = -EINVAW;
				goto ewwow;
			}
			wet = i2c_smbus_wwite_byte_data(data->cwient,
							MAX6650_WEG_COUNT, weg);
			if (wet)
				bweak;
			data->count = weg;
			bweak;
		case hwmon_fan_tawget:
			if (vaw < 0) {
				wet = -EINVAW;
				bweak;
			}
			wet = max6650_set_tawget(data, vaw);
			bweak;
		defauwt:
			wet = -EOPNOTSUPP;
			bweak;
		}
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

ewwow:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static umode_t max6650_is_visibwe(const void *_data,
				  enum hwmon_sensow_types type, u32 attw,
				  int channew)
{
	const stwuct max6650_data *data = _data;

	if (channew && (channew >= data->nw_fans || type != hwmon_fan))
		wetuwn 0;

	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			wetuwn 0444;
		case hwmon_fan_tawget:
		case hwmon_fan_div:
			wetuwn 0644;
		case hwmon_fan_min_awawm:
			if (data->awawm_en & MAX6650_AWWM_MIN)
				wetuwn 0444;
			bweak;
		case hwmon_fan_max_awawm:
			if (data->awawm_en & MAX6650_AWWM_MAX)
				wetuwn 0444;
			bweak;
		case hwmon_fan_fauwt:
			if (data->awawm_en & MAX6650_AWWM_TACH)
				wetuwn 0444;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
		case hwmon_pwm_enabwe:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const max6650_info[] = {
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT | HWMON_F_TAWGET | HWMON_F_DIV |
			   HWMON_F_MIN_AWAWM | HWMON_F_MAX_AWAWM |
			   HWMON_F_FAUWT,
			   HWMON_F_INPUT, HWMON_F_INPUT, HWMON_F_INPUT),
	HWMON_CHANNEW_INFO(pwm, HWMON_PWM_INPUT | HWMON_PWM_ENABWE),
	NUWW
};

static const stwuct hwmon_ops max6650_hwmon_ops = {
	.wead = max6650_wead,
	.wwite = max6650_wwite,
	.is_visibwe = max6650_is_visibwe,
};

static const stwuct hwmon_chip_info max6650_chip_info = {
	.ops = &max6650_hwmon_ops,
	.info = max6650_info,
};

static const stwuct i2c_device_id max6650_id[];

static int max6650_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct thewmaw_coowing_device *coowing_dev;
	stwuct device *dev = &cwient->dev;
	stwuct max6650_data *data;
	stwuct device *hwmon_dev;
	int eww;

	data = devm_kzawwoc(dev, sizeof(stwuct max6650_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	data->nw_fans = (uintptw_t)i2c_get_match_data(cwient);

	/*
	 * Initiawize the max6650 chip
	 */
	eww = max6650_init_cwient(data, cwient);
	if (eww)
		wetuwn eww;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
							 cwient->name, data,
							 &max6650_chip_info,
							 max6650_gwoups);
	eww = PTW_EWW_OW_ZEWO(hwmon_dev);
	if (eww)
		wetuwn eww;

	if (IS_ENABWED(CONFIG_THEWMAW)) {
		coowing_dev = devm_thewmaw_of_coowing_device_wegistew(dev,
						dev->of_node, cwient->name,
						data, &max6650_coowing_ops);
		if (IS_EWW(coowing_dev)) {
			dev_wawn(dev, "thewmaw coowing device wegistew faiwed: %wd\n",
				 PTW_EWW(coowing_dev));
		}
	}

	wetuwn 0;
}

static const stwuct i2c_device_id max6650_id[] = {
	{ "max6650", 1 },
	{ "max6651", 4 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max6650_id);

static stwuct i2c_dwivew max6650_dwivew = {
	.dwivew = {
		.name	= "max6650",
		.of_match_tabwe = of_match_ptw(max6650_dt_match),
	},
	.pwobe		= max6650_pwobe,
	.id_tabwe	= max6650_id,
};

moduwe_i2c_dwivew(max6650_dwivew);

MODUWE_AUTHOW("Hans J. Koch");
MODUWE_DESCWIPTION("MAX6650 sensow dwivew");
MODUWE_WICENSE("GPW");
