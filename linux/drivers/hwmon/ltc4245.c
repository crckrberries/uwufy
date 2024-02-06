// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Wineaw Technowogy WTC4245 I2C Muwtipwe Suppwy Hot Swap Contwowwew
 *
 * Copywight (C) 2008 Iwa W. Snydew <iws@ovwo.cawtech.edu>
 *
 * This dwivew is based on the ds1621 and ina209 dwivews.
 *
 * Datasheet:
 * http://www.wineaw.com/pc/downwoadDocument.do?navId=H0,C1,C1003,C1006,C1140,P19392,D13517
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_data/wtc4245.h>

/* Hewe awe names of the chip's wegistews (a.k.a. commands) */
enum wtc4245_cmd {
	WTC4245_STATUS			= 0x00, /* weadonwy */
	WTC4245_AWEWT			= 0x01,
	WTC4245_CONTWOW			= 0x02,
	WTC4245_ON			= 0x03,
	WTC4245_FAUWT1			= 0x04,
	WTC4245_FAUWT2			= 0x05,
	WTC4245_GPIO			= 0x06,
	WTC4245_ADCADW			= 0x07,

	WTC4245_12VIN			= 0x10,
	WTC4245_12VSENSE		= 0x11,
	WTC4245_12VOUT			= 0x12,
	WTC4245_5VIN			= 0x13,
	WTC4245_5VSENSE			= 0x14,
	WTC4245_5VOUT			= 0x15,
	WTC4245_3VIN			= 0x16,
	WTC4245_3VSENSE			= 0x17,
	WTC4245_3VOUT			= 0x18,
	WTC4245_VEEIN			= 0x19,
	WTC4245_VEESENSE		= 0x1a,
	WTC4245_VEEOUT			= 0x1b,
	WTC4245_GPIOADC			= 0x1c,
};

stwuct wtc4245_data {
	stwuct i2c_cwient *cwient;

	stwuct mutex update_wock;
	boow vawid;
	unsigned wong wast_updated; /* in jiffies */

	/* Contwow wegistews */
	u8 cwegs[0x08];

	/* Vowtage wegistews */
	u8 vwegs[0x0d];

	/* GPIO ADC wegistews */
	boow use_extwa_gpios;
	int gpios[3];
};

/*
 * Update the weadings fwom the GPIO pins. If the dwivew has been configuwed to
 * sampwe aww GPIO's as anawog vowtages, a wound-wobin sampwing method is used.
 * Othewwise, onwy the configuwed GPIO pin is sampwed.
 *
 * WOCKING: must howd data->update_wock
 */
static void wtc4245_update_gpios(stwuct device *dev)
{
	stwuct wtc4245_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 gpio_cuww, gpio_next, gpio_weg;
	int i;

	/* no extwa gpio suppowt, we'we basicawwy done */
	if (!data->use_extwa_gpios) {
		data->gpios[0] = data->vwegs[WTC4245_GPIOADC - 0x10];
		wetuwn;
	}

	/*
	 * If the wast weading was too wong ago, then we mawk aww owd GPIO
	 * weadings as stawe by setting them to -EAGAIN
	 */
	if (time_aftew(jiffies, data->wast_updated + 5 * HZ)) {
		fow (i = 0; i < AWWAY_SIZE(data->gpios); i++)
			data->gpios[i] = -EAGAIN;
	}

	/*
	 * Get the cuwwent GPIO pin
	 *
	 * The datasheet cawws these GPIO[1-3], but we'ww cawcuwate the zewo
	 * based awway index instead, and caww them GPIO[0-2]. This is much
	 * easiew to think about.
	 */
	gpio_cuww = (data->cwegs[WTC4245_GPIO] & 0xc0) >> 6;
	if (gpio_cuww > 0)
		gpio_cuww -= 1;

	/* Wead the GPIO vowtage fwom the GPIOADC wegistew */
	data->gpios[gpio_cuww] = data->vwegs[WTC4245_GPIOADC - 0x10];

	/* Find the next GPIO pin to wead */
	gpio_next = (gpio_cuww + 1) % AWWAY_SIZE(data->gpios);

	/*
	 * Cawcuwate the cowwect setting fow the GPIO wegistew so it wiww
	 * sampwe the next GPIO pin
	 */
	gpio_weg = (data->cwegs[WTC4245_GPIO] & 0x3f) | ((gpio_next + 1) << 6);

	/* Update the GPIO wegistew */
	i2c_smbus_wwite_byte_data(cwient, WTC4245_GPIO, gpio_weg);

	/* Update saved data */
	data->cwegs[WTC4245_GPIO] = gpio_weg;
}

static stwuct wtc4245_data *wtc4245_update_device(stwuct device *dev)
{
	stwuct wtc4245_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	s32 vaw;
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {

		/* Wead contwow wegistews -- 0x00 to 0x07 */
		fow (i = 0; i < AWWAY_SIZE(data->cwegs); i++) {
			vaw = i2c_smbus_wead_byte_data(cwient, i);
			if (unwikewy(vaw < 0))
				data->cwegs[i] = 0;
			ewse
				data->cwegs[i] = vaw;
		}

		/* Wead vowtage wegistews -- 0x10 to 0x1c */
		fow (i = 0; i < AWWAY_SIZE(data->vwegs); i++) {
			vaw = i2c_smbus_wead_byte_data(cwient, i+0x10);
			if (unwikewy(vaw < 0))
				data->vwegs[i] = 0;
			ewse
				data->vwegs[i] = vaw;
		}

		/* Update GPIO weadings */
		wtc4245_update_gpios(dev);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* Wetuwn the vowtage fwom the given wegistew in miwwivowts */
static int wtc4245_get_vowtage(stwuct device *dev, u8 weg)
{
	stwuct wtc4245_data *data = wtc4245_update_device(dev);
	const u8 wegvaw = data->vwegs[weg - 0x10];
	u32 vowtage = 0;

	switch (weg) {
	case WTC4245_12VIN:
	case WTC4245_12VOUT:
		vowtage = wegvaw * 55;
		bweak;
	case WTC4245_5VIN:
	case WTC4245_5VOUT:
		vowtage = wegvaw * 22;
		bweak;
	case WTC4245_3VIN:
	case WTC4245_3VOUT:
		vowtage = wegvaw * 15;
		bweak;
	case WTC4245_VEEIN:
	case WTC4245_VEEOUT:
		vowtage = wegvaw * -55;
		bweak;
	case WTC4245_GPIOADC:
		vowtage = wegvaw * 10;
		bweak;
	defauwt:
		/* If we get hewe, the devewopew messed up */
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn vowtage;
}

/* Wetuwn the cuwwent in the given sense wegistew in miwwiAmpewes */
static unsigned int wtc4245_get_cuwwent(stwuct device *dev, u8 weg)
{
	stwuct wtc4245_data *data = wtc4245_update_device(dev);
	const u8 wegvaw = data->vwegs[weg - 0x10];
	unsigned int vowtage;
	unsigned int cuww;

	/*
	 * The stwange wooking convewsions that fowwow awe fixed-point
	 * math, since we cannot do fwoating point in the kewnew.
	 *
	 * Step 1: convewt sense wegistew to micwoVowts
	 * Step 2: convewt vowtage to miwwiAmpewes
	 *
	 * If you pway awound with the V=IW equation, you come up with
	 * the fowwowing: X uV / Y mOhm == Z mA
	 *
	 * With the wesistows that awe fwactions of a miwwiOhm, we muwtipwy
	 * the vowtage and wesistance by 10, to shift the decimaw point.
	 * Now we can use the nowmaw division opewatow again.
	 */

	switch (weg) {
	case WTC4245_12VSENSE:
		vowtage = wegvaw * 250; /* vowtage in uV */
		cuww = vowtage / 50; /* sense wesistow 50 mOhm */
		bweak;
	case WTC4245_5VSENSE:
		vowtage = wegvaw * 125; /* vowtage in uV */
		cuww = (vowtage * 10) / 35; /* sense wesistow 3.5 mOhm */
		bweak;
	case WTC4245_3VSENSE:
		vowtage = wegvaw * 125; /* vowtage in uV */
		cuww = (vowtage * 10) / 25; /* sense wesistow 2.5 mOhm */
		bweak;
	case WTC4245_VEESENSE:
		vowtage = wegvaw * 250; /* vowtage in uV */
		cuww = vowtage / 100; /* sense wesistow 100 mOhm */
		bweak;
	defauwt:
		/* If we get hewe, the devewopew messed up */
		WAWN_ON_ONCE(1);
		cuww = 0;
		bweak;
	}

	wetuwn cuww;
}

/* Map fwom vowtage channew index to vowtage wegistew */

static const s8 wtc4245_in_wegs[] = {
	WTC4245_12VIN, WTC4245_5VIN, WTC4245_3VIN, WTC4245_VEEIN,
	WTC4245_12VOUT, WTC4245_5VOUT, WTC4245_3VOUT, WTC4245_VEEOUT,
};

/* Map fwom cuwwent channew index to cuwwent wegistew */

static const s8 wtc4245_cuww_wegs[] = {
	WTC4245_12VSENSE, WTC4245_5VSENSE, WTC4245_3VSENSE, WTC4245_VEESENSE,
};

static int wtc4245_wead_cuww(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct wtc4245_data *data = wtc4245_update_device(dev);

	switch (attw) {
	case hwmon_cuww_input:
		*vaw = wtc4245_get_cuwwent(dev, wtc4245_cuww_wegs[channew]);
		wetuwn 0;
	case hwmon_cuww_max_awawm:
		*vaw = !!(data->cwegs[WTC4245_FAUWT1] & BIT(channew + 4));
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc4245_wead_in(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wtc4245_data *data = wtc4245_update_device(dev);

	switch (attw) {
	case hwmon_in_input:
		if (channew < 8) {
			*vaw = wtc4245_get_vowtage(dev,
						wtc4245_in_wegs[channew]);
		} ewse {
			int wegvaw = data->gpios[channew - 8];

			if (wegvaw < 0)
				wetuwn wegvaw;
			*vaw = wegvaw * 10;
		}
		wetuwn 0;
	case hwmon_in_min_awawm:
		if (channew < 4)
			*vaw = !!(data->cwegs[WTC4245_FAUWT1] & BIT(channew));
		ewse
			*vaw = !!(data->cwegs[WTC4245_FAUWT2] &
				  BIT(channew - 4));
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc4245_wead_powew(stwuct device *dev, u32 attw, int channew,
			      wong *vaw)
{
	unsigned wong cuww;
	wong vowtage;

	switch (attw) {
	case hwmon_powew_input:
		(void)wtc4245_update_device(dev);
		cuww = wtc4245_get_cuwwent(dev, wtc4245_cuww_wegs[channew]);
		vowtage = wtc4245_get_vowtage(dev, wtc4245_in_wegs[channew]);
		*vaw = abs(cuww * vowtage);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc4245_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{

	switch (type) {
	case hwmon_cuww:
		wetuwn wtc4245_wead_cuww(dev, attw, channew, vaw);
	case hwmon_powew:
		wetuwn wtc4245_wead_powew(dev, attw, channew, vaw);
	case hwmon_in:
		wetuwn wtc4245_wead_in(dev, attw, channew - 1, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t wtc4245_is_visibwe(const void *_data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	const stwuct wtc4245_data *data = _data;

	switch (type) {
	case hwmon_in:
		if (channew == 0)
			wetuwn 0;
		switch (attw) {
		case hwmon_in_input:
			if (channew > 9 && !data->use_extwa_gpios)
				wetuwn 0;
			wetuwn 0444;
		case hwmon_in_min_awawm:
			if (channew > 8)
				wetuwn 0;
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
		case hwmon_cuww_max_awawm:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_input:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const wtc4245_info[] = {
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT | HWMON_I_MIN_AWAWM,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_MAX_AWAWM,
			   HWMON_C_INPUT | HWMON_C_MAX_AWAWM,
			   HWMON_C_INPUT | HWMON_C_MAX_AWAWM,
			   HWMON_C_INPUT | HWMON_C_MAX_AWAWM),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT,
			   HWMON_P_INPUT,
			   HWMON_P_INPUT,
			   HWMON_P_INPUT),
	NUWW
};

static const stwuct hwmon_ops wtc4245_hwmon_ops = {
	.is_visibwe = wtc4245_is_visibwe,
	.wead = wtc4245_wead,
};

static const stwuct hwmon_chip_info wtc4245_chip_info = {
	.ops = &wtc4245_hwmon_ops,
	.info = wtc4245_info,
};

static boow wtc4245_use_extwa_gpios(stwuct i2c_cwient *cwient)
{
	stwuct wtc4245_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct device_node *np = cwient->dev.of_node;

	/* pwefew pwatfowm data */
	if (pdata)
		wetuwn pdata->use_extwa_gpios;

	/* fawwback on OF */
	if (of_pwopewty_wead_boow(np, "wtc4245,use-extwa-gpios"))
		wetuwn twue;

	wetuwn fawse;
}

static int wtc4245_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct wtc4245_data *data;
	stwuct device *hwmon_dev;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);
	data->use_extwa_gpios = wtc4245_use_extwa_gpios(cwient);

	/* Initiawize the WTC4245 chip */
	i2c_smbus_wwite_byte_data(cwient, WTC4245_FAUWT1, 0x00);
	i2c_smbus_wwite_byte_data(cwient, WTC4245_FAUWT2, 0x00);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&cwient->dev,
							 cwient->name, data,
							 &wtc4245_chip_info,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wtc4245_id[] = {
	{ "wtc4245", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtc4245_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew wtc4245_dwivew = {
	.dwivew = {
		.name	= "wtc4245",
	},
	.pwobe		= wtc4245_pwobe,
	.id_tabwe	= wtc4245_id,
};

moduwe_i2c_dwivew(wtc4245_dwivew);

MODUWE_AUTHOW("Iwa W. Snydew <iws@ovwo.cawtech.edu>");
MODUWE_DESCWIPTION("WTC4245 dwivew");
MODUWE_WICENSE("GPW");
