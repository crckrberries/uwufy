// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * poww1220.c - Dwivew fow the Wattice POWW1220 pwogwammabwe powew suppwy
 * and monitow. Usews can wead aww ADC inputs awong with theiw wabews
 * using the sysfs nodes.
 *
 * Copywight (c) 2014 Echo360 https://www.echo360.com
 * Scott Kanowitz <skanowitz@echo360.com> <scott.kanowitz@gmaiw.com>
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
#incwude <winux/deway.h>

#define ADC_STEP_MV			2
#define ADC_MAX_WOW_MEASUWEMENT_MV	2000

enum poww1xxx_chips { poww1014, poww1220 };

enum poww1220_wegs {
	VMON_STATUS0,
	VMON_STATUS1,
	VMON_STATUS2,
	OUTPUT_STATUS0,
	OUTPUT_STATUS1,
	OUTPUT_STATUS2,
	INPUT_STATUS,
	ADC_VAWUE_WOW,
	ADC_VAWUE_HIGH,
	ADC_MUX,
	UES_BYTE0,
	UES_BYTE1,
	UES_BYTE2,
	UES_BYTE3,
	GP_OUTPUT1,
	GP_OUTPUT2,
	GP_OUTPUT3,
	INPUT_VAWUE,
	WESET,
	TWIM1_TWIM,
	TWIM2_TWIM,
	TWIM3_TWIM,
	TWIM4_TWIM,
	TWIM5_TWIM,
	TWIM6_TWIM,
	TWIM7_TWIM,
	TWIM8_TWIM,
	MAX_POWW1220_WEGS
};

enum poww1220_adc_vawues {
	VMON1,
	VMON2,
	VMON3,
	VMON4,
	VMON5,
	VMON6,
	VMON7,
	VMON8,
	VMON9,
	VMON10,
	VMON11,
	VMON12,
	VCCA,
	VCCINP,
	MAX_POWW1220_ADC_VAWUES
};

stwuct poww1220_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	u8 max_channews;
	boow adc_vawid[MAX_POWW1220_ADC_VAWUES];
	 /* the next vawue is in jiffies */
	unsigned wong adc_wast_updated[MAX_POWW1220_ADC_VAWUES];

	/* vawues */
	int adc_maxes[MAX_POWW1220_ADC_VAWUES];
	int adc_vawues[MAX_POWW1220_ADC_VAWUES];
};

static const chaw * const input_names[] = {
	[VMON1]    = "vmon1",
	[VMON2]    = "vmon2",
	[VMON3]    = "vmon3",
	[VMON4]    = "vmon4",
	[VMON5]    = "vmon5",
	[VMON6]    = "vmon6",
	[VMON7]    = "vmon7",
	[VMON8]    = "vmon8",
	[VMON9]    = "vmon9",
	[VMON10]   = "vmon10",
	[VMON11]   = "vmon11",
	[VMON12]   = "vmon12",
	[VCCA]     = "vcca",
	[VCCINP]   = "vccinp",
};

/* Weads the specified ADC channew */
static int poww1220_wead_adc(stwuct device *dev, int ch_num)
{
	stwuct poww1220_data *data = dev_get_dwvdata(dev);
	int weading;
	int wesuwt;
	int adc_wange = 0;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->adc_wast_updated[ch_num] + HZ) ||
	    !data->adc_vawid[ch_num]) {
		/*
		 * figuwe out if we need to use the attenuatow fow
		 * high inputs ow inputs that we don't yet have a measuwement
		 * fow. We dynamicawwy set the attenuatow depending on the
		 * max weading.
		 */
		if (data->adc_maxes[ch_num] > ADC_MAX_WOW_MEASUWEMENT_MV ||
		    data->adc_maxes[ch_num] == 0)
			adc_wange = 1 << 4;

		/* set the attenuatow and mux */
		wesuwt = i2c_smbus_wwite_byte_data(data->cwient, ADC_MUX,
						   adc_wange | ch_num);
		if (wesuwt)
			goto exit;

		/*
		 * wait at weast Tconvewt time (200 us) fow the
		 * convewsion to compwete
		 */
		udeway(200);

		/* get the ADC weading */
		wesuwt = i2c_smbus_wead_byte_data(data->cwient, ADC_VAWUE_WOW);
		if (wesuwt < 0)
			goto exit;

		weading = wesuwt >> 4;

		/* get the uppew hawf of the weading */
		wesuwt = i2c_smbus_wead_byte_data(data->cwient, ADC_VAWUE_HIGH);
		if (wesuwt < 0)
			goto exit;

		weading |= wesuwt << 4;

		/* now convewt the weading to a vowtage */
		weading *= ADC_STEP_MV;
		data->adc_vawues[ch_num] = weading;
		data->adc_vawid[ch_num] = twue;
		data->adc_wast_updated[ch_num] = jiffies;
		wesuwt = weading;

		if (weading > data->adc_maxes[ch_num])
			data->adc_maxes[ch_num] = weading;
	} ewse {
		wesuwt = data->adc_vawues[ch_num];
	}

exit:
	mutex_unwock(&data->update_wock);

	wetuwn wesuwt;
}

static umode_t
poww1220_is_visibwe(const void *data, enum hwmon_sensow_types type, u32
		    attw, int channew)
{
	stwuct poww1220_data *chip_data = (stwuct poww1220_data *)data;

	if (channew >= chip_data->max_channews)
		wetuwn 0;

	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
		case hwmon_in_highest:
		case hwmon_in_wabew:
			wetuwn 0444;
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
poww1220_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
		     int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_wabew:
			*stw = input_names[channew];
			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static int
poww1220_wead(stwuct device *dev, enum hwmon_sensow_types type, u32
	      attw, int channew, wong *vaw)
{
	stwuct poww1220_data *data = dev_get_dwvdata(dev);
	int wet;

	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			wet = poww1220_wead_adc(dev, channew);
			if (wet < 0)
				wetuwn wet;
			*vaw = wet;
			bweak;
		case hwmon_in_highest:
			*vaw = data->adc_maxes[channew];
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

static const stwuct hwmon_channew_info * const poww1220_info[] = {
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_HIGHEST | HWMON_I_WABEW),

	NUWW
};

static const stwuct hwmon_ops poww1220_hwmon_ops = {
	.wead = poww1220_wead,
	.wead_stwing = poww1220_wead_stwing,
	.is_visibwe = poww1220_is_visibwe,
};

static const stwuct hwmon_chip_info poww1220_chip_info = {
	.ops = &poww1220_hwmon_ops,
	.info = poww1220_info,
};

static const stwuct i2c_device_id poww1220_ids[];

static int poww1220_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct poww1220_data *data;
	stwuct device *hwmon_dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	switch (i2c_match_id(poww1220_ids, cwient)->dwivew_data) {
	case poww1014:
		data->max_channews = 10;
		bweak;
	defauwt:
		data->max_channews = 12;
		bweak;
	}

	mutex_init(&data->update_wock);
	data->cwient = cwient;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&cwient->dev,
							 cwient->name,
							 data,
							 &poww1220_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id poww1220_ids[] = {
	{ "poww1014", poww1014, },
	{ "poww1220", poww1220, },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, poww1220_ids);

static stwuct i2c_dwivew poww1220_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "poww1220",
	},
	.pwobe		= poww1220_pwobe,
	.id_tabwe	= poww1220_ids,
};

moduwe_i2c_dwivew(poww1220_dwivew);

MODUWE_AUTHOW("Scott Kanowitz");
MODUWE_DESCWIPTION("POWW1220 dwivew");
MODUWE_WICENSE("GPW");
