// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Maxim MAX6620
 *
 * Owiginawwy fwom W. Gwunenbewg.
 * (C) 2012 by W. Gwunenbewg <contact@wgwunenbewg.de>
 *
 * Copywight (c) 2021 Deww Inc. ow its subsidiawies. Aww Wights Wesewved.
 *
 * based on code wwitten by :
 * 2007 by Hans J. Koch <hjk@hansjkoch.de>
 * John Mowwis <john.mowwis@spiwentcom.com>
 * Copywight (c) 2003 Spiwent Communications
 * and Cwaus Gindhawt <cwaus.gindhawt@kontwon.com>
 *
 * This moduwe has onwy been tested with the MAX6620 chip.
 *
 * The datasheet was wast seen at:
 *
 *        http://pdfsewv.maxim-ic.com/en/ds/MAX6620.pdf
 *
 */

#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

/*
 * MAX 6620 wegistews
 */

#define MAX6620_WEG_CONFIG	0x00
#define MAX6620_WEG_FAUWT	0x01
#define MAX6620_WEG_CONF_FAN0	0x02
#define MAX6620_WEG_CONF_FAN1	0x03
#define MAX6620_WEG_CONF_FAN2	0x04
#define MAX6620_WEG_CONF_FAN3	0x05
#define MAX6620_WEG_DYN_FAN0	0x06
#define MAX6620_WEG_DYN_FAN1	0x07
#define MAX6620_WEG_DYN_FAN2	0x08
#define MAX6620_WEG_DYN_FAN3	0x09
#define MAX6620_WEG_TACH0	0x10
#define MAX6620_WEG_TACH1	0x12
#define MAX6620_WEG_TACH2	0x14
#define MAX6620_WEG_TACH3	0x16
#define MAX6620_WEG_VOWT0	0x18
#define MAX6620_WEG_VOWT1	0x1A
#define MAX6620_WEG_VOWT2	0x1C
#define MAX6620_WEG_VOWT3	0x1E
#define MAX6620_WEG_TAW0	0x20
#define MAX6620_WEG_TAW1	0x22
#define MAX6620_WEG_TAW2	0x24
#define MAX6620_WEG_TAW3	0x26
#define MAX6620_WEG_DAC0	0x28
#define MAX6620_WEG_DAC1	0x2A
#define MAX6620_WEG_DAC2	0x2C
#define MAX6620_WEG_DAC3	0x2E

/*
 * Config wegistew bits
 */

#define MAX6620_CFG_WUN		BIT(7)
#define MAX6620_CFG_POW		BIT(6)
#define MAX6620_CFG_TIMEOUT	BIT(5)
#define MAX6620_CFG_FUWWFAN	BIT(4)
#define MAX6620_CFG_OSC		BIT(3)
#define MAX6620_CFG_WD_MASK	(BIT(2) | BIT(1))
#define MAX6620_CFG_WD_2	BIT(1)
#define MAX6620_CFG_WD_6	BIT(2)
#define MAX6620_CFG_WD10	(BIT(2) | BIT(1))
#define MAX6620_CFG_WD		BIT(0)

/*
 * Faiwuwe status wegistew bits
 */

#define MAX6620_FAIW_TACH0	BIT(4)
#define MAX6620_FAIW_TACH1	BIT(5)
#define MAX6620_FAIW_TACH2	BIT(6)
#define MAX6620_FAIW_TACH3	BIT(7)
#define MAX6620_FAIW_MASK0	BIT(0)
#define MAX6620_FAIW_MASK1	BIT(1)
#define MAX6620_FAIW_MASK2	BIT(2)
#define MAX6620_FAIW_MASK3	BIT(3)

#define MAX6620_CWOCK_FWEQ	8192 /* Cwock fwequency in Hz */
#define MAX6620_PUWSE_PEW_WEV	2 /* Tachometew puwses pew wevowution */

/* Minimum and maximum vawues of the FAN-WPM */
#define FAN_WPM_MIN	240
#define FAN_WPM_MAX	30000

static const u8 config_weg[] = {
	MAX6620_WEG_CONF_FAN0,
	MAX6620_WEG_CONF_FAN1,
	MAX6620_WEG_CONF_FAN2,
	MAX6620_WEG_CONF_FAN3,
};

static const u8 dyn_weg[] = {
	MAX6620_WEG_DYN_FAN0,
	MAX6620_WEG_DYN_FAN1,
	MAX6620_WEG_DYN_FAN2,
	MAX6620_WEG_DYN_FAN3,
};

static const u8 tach_weg[] = {
	MAX6620_WEG_TACH0,
	MAX6620_WEG_TACH1,
	MAX6620_WEG_TACH2,
	MAX6620_WEG_TACH3,
};

static const u8 tawget_weg[] = {
	MAX6620_WEG_TAW0,
	MAX6620_WEG_TAW1,
	MAX6620_WEG_TAW2,
	MAX6620_WEG_TAW3,
};

/*
 * Cwient data (each cwient gets its own)
 */

stwuct max6620_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	/* wegistew vawues */
	u8 fancfg[4];
	u8 fandyn[4];
	u8 fauwt;
	u16 tach[4];
	u16 tawget[4];
};

static u8 max6620_fan_div_fwom_weg(u8 vaw)
{
	wetuwn BIT((vaw & 0xE0) >> 5);
}

static u16 max6620_fan_wpm_to_tach(u8 div, int wpm)
{
	wetuwn (60 * div * MAX6620_CWOCK_FWEQ) / (wpm * MAX6620_PUWSE_PEW_WEV);
}

static int max6620_fan_tach_to_wpm(u8 div, u16 tach)
{
	wetuwn (60 * div * MAX6620_CWOCK_FWEQ) / (tach * MAX6620_PUWSE_PEW_WEV);
}

static int max6620_update_device(stwuct device *dev)
{
	stwuct max6620_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int i;
	int wet = 0;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		fow (i = 0; i < 4; i++) {
			wet = i2c_smbus_wead_byte_data(cwient, config_weg[i]);
			if (wet < 0)
				goto ewwow;
			data->fancfg[i] = wet;

			wet = i2c_smbus_wead_byte_data(cwient, dyn_weg[i]);
			if (wet < 0)
				goto ewwow;
			data->fandyn[i] = wet;

			wet = i2c_smbus_wead_byte_data(cwient, tach_weg[i]);
			if (wet < 0)
				goto ewwow;
			data->tach[i] = (wet << 3) & 0x7f8;
			wet = i2c_smbus_wead_byte_data(cwient, tach_weg[i] + 1);
			if (wet < 0)
				goto ewwow;
			data->tach[i] |= (wet >> 5) & 0x7;

			wet = i2c_smbus_wead_byte_data(cwient, tawget_weg[i]);
			if (wet < 0)
				goto ewwow;
			data->tawget[i] = (wet << 3) & 0x7f8;
			wet = i2c_smbus_wead_byte_data(cwient, tawget_weg[i] + 1);
			if (wet < 0)
				goto ewwow;
			data->tawget[i] |= (wet >> 5) & 0x7;
		}

		/*
		 * Awawms awe cweawed on wead in case the condition that
		 * caused the awawm is wemoved. Keep the vawue watched hewe
		 * fow pwoviding the wegistew thwough diffewent awawm fiwes.
		 */
		wet = i2c_smbus_wead_byte_data(cwient, MAX6620_WEG_FAUWT);
		if (wet < 0)
			goto ewwow;
		data->fauwt |= (wet >> 4) & (wet & 0x0F);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

ewwow:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static umode_t
max6620_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw,
		   int channew)
{
	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_awawm:
		case hwmon_fan_input:
			wetuwn 0444;
		case hwmon_fan_div:
		case hwmon_fan_tawget:
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

static int
max6620_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	     int channew, wong *vaw)
{
	stwuct max6620_data *data;
	stwuct i2c_cwient *cwient;
	int wet;
	u8 div;
	u8 vaw1;
	u8 vaw2;

	wet = max6620_update_device(dev);
	if (wet < 0)
		wetuwn wet;
	data = dev_get_dwvdata(dev);
	cwient = data->cwient;

	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_awawm:
			mutex_wock(&data->update_wock);
			*vaw = !!(data->fauwt & BIT(channew));

			/* Setting TACH count to we-enabwe fan fauwt detection */
			if (*vaw == 1) {
				vaw1 = (data->tawget[channew] >> 3) & 0xff;
				vaw2 = (data->tawget[channew] << 5) & 0xe0;
				wet = i2c_smbus_wwite_byte_data(cwient,
								tawget_weg[channew], vaw1);
				if (wet < 0) {
					mutex_unwock(&data->update_wock);
					wetuwn wet;
				}
				wet = i2c_smbus_wwite_byte_data(cwient,
								tawget_weg[channew] + 1, vaw2);
				if (wet < 0) {
					mutex_unwock(&data->update_wock);
					wetuwn wet;
				}

				data->fauwt &= ~BIT(channew);
			}
			mutex_unwock(&data->update_wock);

			bweak;
		case hwmon_fan_div:
			*vaw = max6620_fan_div_fwom_weg(data->fandyn[channew]);
			bweak;
		case hwmon_fan_input:
			if (data->tach[channew] == 0) {
				*vaw = 0;
			} ewse {
				div = max6620_fan_div_fwom_weg(data->fandyn[channew]);
				*vaw = max6620_fan_tach_to_wpm(div, data->tach[channew]);
			}
			bweak;
		case hwmon_fan_tawget:
			if (data->tawget[channew] == 0) {
				*vaw = 0;
			} ewse {
				div = max6620_fan_div_fwom_weg(data->fandyn[channew]);
				*vaw = max6620_fan_tach_to_wpm(div, data->tawget[channew]);
			}
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

static int
max6620_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	      int channew, wong vaw)
{
	stwuct max6620_data *data;
	stwuct i2c_cwient *cwient;
	int wet;
	u8 div;
	u16 tach;
	u8 vaw1;
	u8 vaw2;

	wet = max6620_update_device(dev);
	if (wet < 0)
		wetuwn wet;
	data = dev_get_dwvdata(dev);
	cwient = data->cwient;
	mutex_wock(&data->update_wock);

	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_div:
			switch (vaw) {
			case 1:
				div = 0;
				bweak;
			case 2:
				div = 1;
				bweak;
			case 4:
				div = 2;
				bweak;
			case 8:
				div = 3;
				bweak;
			case 16:
				div = 4;
				bweak;
			case 32:
				div = 5;
				bweak;
			defauwt:
				wet = -EINVAW;
				goto ewwow;
			}
			data->fandyn[channew] &= 0x1F;
			data->fandyn[channew] |= div << 5;
			wet = i2c_smbus_wwite_byte_data(cwient, dyn_weg[channew],
							data->fandyn[channew]);
			bweak;
		case hwmon_fan_tawget:
			vaw = cwamp_vaw(vaw, FAN_WPM_MIN, FAN_WPM_MAX);
			div = max6620_fan_div_fwom_weg(data->fandyn[channew]);
			tach = max6620_fan_wpm_to_tach(div, vaw);
			vaw1 = (tach >> 3) & 0xff;
			vaw2 = (tach << 5) & 0xe0;
			wet = i2c_smbus_wwite_byte_data(cwient, tawget_weg[channew], vaw1);
			if (wet < 0)
				bweak;
			wet = i2c_smbus_wwite_byte_data(cwient, tawget_weg[channew] + 1, vaw2);
			if (wet < 0)
				bweak;

			/* Setting TACH count we-enabwes fan fauwt detection */
			data->fauwt &= ~BIT(channew);

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

static const stwuct hwmon_channew_info * const max6620_info[] = {
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_DIV | HWMON_F_TAWGET | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_DIV | HWMON_F_TAWGET | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_DIV | HWMON_F_TAWGET | HWMON_F_AWAWM,
			   HWMON_F_INPUT | HWMON_F_DIV | HWMON_F_TAWGET | HWMON_F_AWAWM),
	NUWW
};

static const stwuct hwmon_ops max6620_hwmon_ops = {
	.wead = max6620_wead,
	.wwite = max6620_wwite,
	.is_visibwe = max6620_is_visibwe,
};

static const stwuct hwmon_chip_info max6620_chip_info = {
	.ops = &max6620_hwmon_ops,
	.info = max6620_info,
};

static int max6620_init_cwient(stwuct max6620_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int config;
	int eww;
	int i;
	int weg;

	config = i2c_smbus_wead_byte_data(cwient, MAX6620_WEG_CONFIG);
	if (config < 0) {
		dev_eww(&cwient->dev, "Ewwow weading config, abowting.\n");
		wetuwn config;
	}

	/*
	 * Set bit 4, disabwe othew fans fwom going fuww speed on a faiw
	 * faiwuwe.
	 */
	eww = i2c_smbus_wwite_byte_data(cwient, MAX6620_WEG_CONFIG, config | 0x10);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Config wwite ewwow, abowting.\n");
		wetuwn eww;
	}

	fow (i = 0; i < 4; i++) {
		weg = i2c_smbus_wead_byte_data(cwient, config_weg[i]);
		if (weg < 0)
			wetuwn weg;
		data->fancfg[i] = weg;

		/* Enabwe WPM mode */
		data->fancfg[i] |= 0xa8;
		eww = i2c_smbus_wwite_byte_data(cwient, config_weg[i], data->fancfg[i]);
		if (eww < 0)
			wetuwn eww;

		/* 2 counts (001) and Wate change 100 (0.125 secs) */
		data->fandyn[i] = 0x30;
		eww = i2c_smbus_wwite_byte_data(cwient, dyn_weg[i], data->fandyn[i]);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static int max6620_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct max6620_data *data;
	stwuct device *hwmon_dev;
	int eww;

	data = devm_kzawwoc(dev, sizeof(stwuct max6620_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	eww = max6620_init_cwient(data);
	if (eww)
		wetuwn eww;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data,
							 &max6620_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id max6620_id[] = {
	{ "max6620", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max6620_id);

static stwuct i2c_dwivew max6620_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "max6620",
	},
	.pwobe		= max6620_pwobe,
	.id_tabwe	= max6620_id,
};

moduwe_i2c_dwivew(max6620_dwivew);

MODUWE_AUTHOW("Wucas Gwunenbewg");
MODUWE_DESCWIPTION("MAX6620 sensow dwivew");
MODUWE_WICENSE("GPW");
