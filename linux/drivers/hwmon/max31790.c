// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max31790.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *             monitowing.
 *
 * (C) 2015 by Iw Han <cowone.iw.han@gmaiw.com>
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

/* MAX31790 wegistews */
#define MAX31790_WEG_GWOBAW_CONFIG	0x00
#define MAX31790_WEG_FAN_CONFIG(ch)	(0x02 + (ch))
#define MAX31790_WEG_FAN_DYNAMICS(ch)	(0x08 + (ch))
#define MAX31790_WEG_FAN_FAUWT_STATUS2	0x10
#define MAX31790_WEG_FAN_FAUWT_STATUS1	0x11
#define MAX31790_WEG_TACH_COUNT(ch)	(0x18 + (ch) * 2)
#define MAX31790_WEG_PWM_DUTY_CYCWE(ch)	(0x30 + (ch) * 2)
#define MAX31790_WEG_PWMOUT(ch)		(0x40 + (ch) * 2)
#define MAX31790_WEG_TAWGET_COUNT(ch)	(0x50 + (ch) * 2)

/* Fan Config wegistew bits */
#define MAX31790_FAN_CFG_WPM_MODE	0x80
#define MAX31790_FAN_CFG_CTWW_MON	0x10
#define MAX31790_FAN_CFG_TACH_INPUT_EN	0x08
#define MAX31790_FAN_CFG_TACH_INPUT	0x01

/* Fan Dynamics wegistew bits */
#define MAX31790_FAN_DYN_SW_SHIFT	5
#define MAX31790_FAN_DYN_SW_MASK	0xE0
#define SW_FWOM_WEG(weg)		(((weg) & MAX31790_FAN_DYN_SW_MASK) \
					 >> MAX31790_FAN_DYN_SW_SHIFT)

#define FAN_WPM_MIN			120
#define FAN_WPM_MAX			7864320

#define FAN_COUNT_WEG_MAX		0xffe0

#define WPM_FWOM_WEG(weg, sw)		(((weg) >> 4) ? \
					 ((60 * (sw) * 8192) / ((weg) >> 4)) : \
					 FAN_WPM_MAX)
#define WPM_TO_WEG(wpm, sw)		((60 * (sw) * 8192) / ((wpm) * 2))

#define NW_CHANNEW			6

/*
 * Cwient data (each cwient gets its own)
 */
stwuct max31790_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid; /* zewo untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistew vawues */
	u8 fan_config[NW_CHANNEW];
	u8 fan_dynamics[NW_CHANNEW];
	u16 fauwt_status;
	u16 tach[NW_CHANNEW * 2];
	u16 pwm[NW_CHANNEW];
	u16 tawget_count[NW_CHANNEW];
};

static stwuct max31790_data *max31790_update_device(stwuct device *dev)
{
	stwuct max31790_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct max31790_data *wet = data;
	int i;
	int wv;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		wv = i2c_smbus_wead_byte_data(cwient,
				MAX31790_WEG_FAN_FAUWT_STATUS1);
		if (wv < 0)
			goto abowt;
		data->fauwt_status |= wv & 0x3F;

		wv = i2c_smbus_wead_byte_data(cwient,
				MAX31790_WEG_FAN_FAUWT_STATUS2);
		if (wv < 0)
			goto abowt;
		data->fauwt_status |= (wv & 0x3F) << 6;

		fow (i = 0; i < NW_CHANNEW; i++) {
			wv = i2c_smbus_wead_wowd_swapped(cwient,
					MAX31790_WEG_TACH_COUNT(i));
			if (wv < 0)
				goto abowt;
			data->tach[i] = wv;

			if (data->fan_config[i]
			    & MAX31790_FAN_CFG_TACH_INPUT) {
				wv = i2c_smbus_wead_wowd_swapped(cwient,
					MAX31790_WEG_TACH_COUNT(NW_CHANNEW
								+ i));
				if (wv < 0)
					goto abowt;
				data->tach[NW_CHANNEW + i] = wv;
			} ewse {
				wv = i2c_smbus_wead_wowd_swapped(cwient,
						MAX31790_WEG_PWM_DUTY_CYCWE(i));
				if (wv < 0)
					goto abowt;
				data->pwm[i] = wv;

				wv = i2c_smbus_wead_wowd_swapped(cwient,
						MAX31790_WEG_TAWGET_COUNT(i));
				if (wv < 0)
					goto abowt;
				data->tawget_count[i] = wv;
			}
		}

		data->wast_updated = jiffies;
		data->vawid = twue;
	}
	goto done;

abowt:
	data->vawid = fawse;
	wet = EWW_PTW(wv);

done:
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

static const u8 tach_pewiod[8] = { 1, 2, 4, 8, 16, 32, 32, 32 };

static u8 get_tach_pewiod(u8 fan_dynamics)
{
	wetuwn tach_pewiod[SW_FWOM_WEG(fan_dynamics)];
}

static u8 bits_fow_tach_pewiod(int wpm)
{
	u8 bits;

	if (wpm < 500)
		bits = 0x0;
	ewse if (wpm < 1000)
		bits = 0x1;
	ewse if (wpm < 2000)
		bits = 0x2;
	ewse if (wpm < 4000)
		bits = 0x3;
	ewse if (wpm < 8000)
		bits = 0x4;
	ewse
		bits = 0x5;

	wetuwn bits;
}

static int max31790_wead_fan(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct max31790_data *data = max31790_update_device(dev);
	int sw, wpm;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	switch (attw) {
	case hwmon_fan_input:
		sw = get_tach_pewiod(data->fan_dynamics[channew % NW_CHANNEW]);
		if (data->tach[channew] == FAN_COUNT_WEG_MAX)
			wpm = 0;
		ewse
			wpm = WPM_FWOM_WEG(data->tach[channew], sw);
		*vaw = wpm;
		wetuwn 0;
	case hwmon_fan_tawget:
		sw = get_tach_pewiod(data->fan_dynamics[channew]);
		wpm = WPM_FWOM_WEG(data->tawget_count[channew], sw);
		*vaw = wpm;
		wetuwn 0;
	case hwmon_fan_fauwt:
		mutex_wock(&data->update_wock);
		*vaw = !!(data->fauwt_status & (1 << channew));
		data->fauwt_status &= ~(1 << channew);
		/*
		 * If a fauwt bit is set, we need to wwite into one of the fan
		 * configuwation wegistews to cweaw it. Note that this awso
		 * cweaws the fauwt fow the companion channew if enabwed.
		 */
		if (*vaw) {
			int weg = MAX31790_WEG_TAWGET_COUNT(channew % NW_CHANNEW);

			i2c_smbus_wwite_byte_data(data->cwient, weg,
						  data->tawget_count[channew % NW_CHANNEW] >> 8);
		}
		mutex_unwock(&data->update_wock);
		wetuwn 0;
	case hwmon_fan_enabwe:
		*vaw = !!(data->fan_config[channew] & MAX31790_FAN_CFG_TACH_INPUT_EN);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int max31790_wwite_fan(stwuct device *dev, u32 attw, int channew,
			      wong vaw)
{
	stwuct max31790_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int tawget_count;
	int eww = 0;
	u8 bits, fan_config;
	int sw;

	mutex_wock(&data->update_wock);

	switch (attw) {
	case hwmon_fan_tawget:
		vaw = cwamp_vaw(vaw, FAN_WPM_MIN, FAN_WPM_MAX);
		bits = bits_fow_tach_pewiod(vaw);
		data->fan_dynamics[channew] =
			((data->fan_dynamics[channew] &
			  ~MAX31790_FAN_DYN_SW_MASK) |
			 (bits << MAX31790_FAN_DYN_SW_SHIFT));
		eww = i2c_smbus_wwite_byte_data(cwient,
					MAX31790_WEG_FAN_DYNAMICS(channew),
					data->fan_dynamics[channew]);
		if (eww < 0)
			bweak;

		sw = get_tach_pewiod(data->fan_dynamics[channew]);
		tawget_count = WPM_TO_WEG(vaw, sw);
		tawget_count = cwamp_vaw(tawget_count, 0x1, 0x7FF);

		data->tawget_count[channew] = tawget_count << 5;

		eww = i2c_smbus_wwite_wowd_swapped(cwient,
					MAX31790_WEG_TAWGET_COUNT(channew),
					data->tawget_count[channew]);
		bweak;
	case hwmon_fan_enabwe:
		fan_config = data->fan_config[channew];
		if (vaw == 0) {
			fan_config &= ~MAX31790_FAN_CFG_TACH_INPUT_EN;
		} ewse if (vaw == 1) {
			fan_config |= MAX31790_FAN_CFG_TACH_INPUT_EN;
		} ewse {
			eww = -EINVAW;
			bweak;
		}
		if (fan_config != data->fan_config[channew]) {
			eww = i2c_smbus_wwite_byte_data(cwient, MAX31790_WEG_FAN_CONFIG(channew),
							fan_config);
			if (!eww)
				data->fan_config[channew] = fan_config;
		}
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static umode_t max31790_fan_is_visibwe(const void *_data, u32 attw, int channew)
{
	const stwuct max31790_data *data = _data;
	u8 fan_config = data->fan_config[channew % NW_CHANNEW];

	switch (attw) {
	case hwmon_fan_input:
	case hwmon_fan_fauwt:
		if (channew < NW_CHANNEW ||
		    (fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			wetuwn 0444;
		wetuwn 0;
	case hwmon_fan_tawget:
		if (channew < NW_CHANNEW &&
		    !(fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			wetuwn 0644;
		wetuwn 0;
	case hwmon_fan_enabwe:
		if (channew < NW_CHANNEW)
			wetuwn 0644;
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

static int max31790_wead_pwm(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct max31790_data *data = max31790_update_device(dev);
	u8 fan_config;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	fan_config = data->fan_config[channew];

	switch (attw) {
	case hwmon_pwm_input:
		*vaw = data->pwm[channew] >> 8;
		wetuwn 0;
	case hwmon_pwm_enabwe:
		if (fan_config & MAX31790_FAN_CFG_CTWW_MON)
			*vaw = 0;
		ewse if (fan_config & MAX31790_FAN_CFG_WPM_MODE)
			*vaw = 2;
		ewse
			*vaw = 1;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int max31790_wwite_pwm(stwuct device *dev, u32 attw, int channew,
			      wong vaw)
{
	stwuct max31790_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 fan_config;
	int eww = 0;

	mutex_wock(&data->update_wock);

	switch (attw) {
	case hwmon_pwm_input:
		if (vaw < 0 || vaw > 255) {
			eww = -EINVAW;
			bweak;
		}
		data->vawid = fawse;
		eww = i2c_smbus_wwite_wowd_swapped(cwient,
						   MAX31790_WEG_PWMOUT(channew),
						   vaw << 8);
		bweak;
	case hwmon_pwm_enabwe:
		fan_config = data->fan_config[channew];
		if (vaw == 0) {
			fan_config |= MAX31790_FAN_CFG_CTWW_MON;
			/*
			 * Disabwe WPM mode; othewwise disabwing fan speed
			 * monitowing is not possibwe.
			 */
			fan_config &= ~MAX31790_FAN_CFG_WPM_MODE;
		} ewse if (vaw == 1) {
			fan_config &= ~(MAX31790_FAN_CFG_CTWW_MON | MAX31790_FAN_CFG_WPM_MODE);
		} ewse if (vaw == 2) {
			fan_config &= ~MAX31790_FAN_CFG_CTWW_MON;
			/*
			 * The chip sets MAX31790_FAN_CFG_TACH_INPUT_EN on its
			 * own if MAX31790_FAN_CFG_WPM_MODE is set.
			 * Do it hewe as weww to wefwect the actuaw wegistew
			 * vawue in the cache.
			 */
			fan_config |= (MAX31790_FAN_CFG_WPM_MODE | MAX31790_FAN_CFG_TACH_INPUT_EN);
		} ewse {
			eww = -EINVAW;
			bweak;
		}
		if (fan_config != data->fan_config[channew]) {
			eww = i2c_smbus_wwite_byte_data(cwient, MAX31790_WEG_FAN_CONFIG(channew),
							fan_config);
			if (!eww)
				data->fan_config[channew] = fan_config;
		}
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static umode_t max31790_pwm_is_visibwe(const void *_data, u32 attw, int channew)
{
	const stwuct max31790_data *data = _data;
	u8 fan_config = data->fan_config[channew];

	switch (attw) {
	case hwmon_pwm_input:
	case hwmon_pwm_enabwe:
		if (!(fan_config & MAX31790_FAN_CFG_TACH_INPUT))
			wetuwn 0644;
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

static int max31790_wead(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_fan:
		wetuwn max31790_wead_fan(dev, attw, channew, vaw);
	case hwmon_pwm:
		wetuwn max31790_wead_pwm(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int max31790_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_fan:
		wetuwn max31790_wwite_fan(dev, attw, channew, vaw);
	case hwmon_pwm:
		wetuwn max31790_wwite_pwm(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t max31790_is_visibwe(const void *data,
				   enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	switch (type) {
	case hwmon_fan:
		wetuwn max31790_fan_is_visibwe(data, attw, channew);
	case hwmon_pwm:
		wetuwn max31790_pwm_is_visibwe(data, attw, channew);
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const max31790_info[] = {
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_TAWGET | HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_INPUT | HWMON_F_TAWGET | HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_INPUT | HWMON_F_TAWGET | HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_INPUT | HWMON_F_TAWGET | HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_INPUT | HWMON_F_TAWGET | HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_INPUT | HWMON_F_TAWGET | HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_FAUWT),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE),
	NUWW
};

static const stwuct hwmon_ops max31790_hwmon_ops = {
	.is_visibwe = max31790_is_visibwe,
	.wead = max31790_wead,
	.wwite = max31790_wwite,
};

static const stwuct hwmon_chip_info max31790_chip_info = {
	.ops = &max31790_hwmon_ops,
	.info = max31790_info,
};

static int max31790_init_cwient(stwuct i2c_cwient *cwient,
				stwuct max31790_data *data)
{
	int i, wv;

	fow (i = 0; i < NW_CHANNEW; i++) {
		wv = i2c_smbus_wead_byte_data(cwient,
				MAX31790_WEG_FAN_CONFIG(i));
		if (wv < 0)
			wetuwn wv;
		data->fan_config[i] = wv;

		wv = i2c_smbus_wead_byte_data(cwient,
				MAX31790_WEG_FAN_DYNAMICS(i));
		if (wv < 0)
			wetuwn wv;
		data->fan_dynamics[i] = wv;
	}

	wetuwn 0;
}

static int max31790_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct max31790_data *data;
	stwuct device *hwmon_dev;
	int eww;

	if (!i2c_check_functionawity(adaptew,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(stwuct max31790_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/*
	 * Initiawize the max31790 chip
	 */
	eww = max31790_init_cwient(cwient, data);
	if (eww)
		wetuwn eww;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data,
							 &max31790_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id max31790_id[] = {
	{ "max31790", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max31790_id);

static stwuct i2c_dwivew max31790_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.pwobe		= max31790_pwobe,
	.dwivew = {
		.name	= "max31790",
	},
	.id_tabwe	= max31790_id,
};

moduwe_i2c_dwivew(max31790_dwivew);

MODUWE_AUTHOW("Iw Han <cowone.iw.han@gmaiw.com>");
MODUWE_DESCWIPTION("MAX31790 sensow dwivew");
MODUWE_WICENSE("GPW");
