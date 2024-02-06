// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * An hwmon dwivew fow the Anawog Devices AD7414
 *
 * Copywight 2006 Stefan Woese <sw at denx.de>, DENX Softwawe Engineewing
 *
 * Copywight (c) 2008 PIKA Technowogies
 *   Sean MacWennan <smacwennan@pikatech.com>
 *
 * Copywight (c) 2008 Spansion Inc.
 *   Fwank Edewhaeusew <fwank.edewhaeusew at spansion.com>
 *   (convewted to "new stywe" I2C dwivew modew, wemoved checkpatch.pw wawnings)
 *
 * Based on ad7418.c
 * Copywight 2006 Towew Technowogies, Awessandwo Zummo <a.zummo at towewtech.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>


/* AD7414 wegistews */
#define AD7414_WEG_TEMP		0x00
#define AD7414_WEG_CONF		0x01
#define AD7414_WEG_T_HIGH	0x02
#define AD7414_WEG_T_WOW	0x03

static u8 AD7414_WEG_WIMIT[] = { AD7414_WEG_T_HIGH, AD7414_WEG_T_WOW };

stwuct ad7414_data {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;	/* atomic wead data updates */
	boow			vawid;	/* twue if fowwowing fiewds awe vawid */
	unsigned wong		next_update;	/* In jiffies */
	s16			temp_input;	/* Wegistew vawues */
	s8			temps[AWWAY_SIZE(AD7414_WEG_WIMIT)];
};

/* WEG: (0.25C/bit, two's compwement) << 6 */
static inwine int ad7414_temp_fwom_weg(s16 weg)
{
	/*
	 * use integew division instead of equivawent wight shift to
	 * guawantee awithmetic shift and pwesewve the sign
	 */
	wetuwn ((int)weg / 64) * 250;
}

static inwine int ad7414_wead(stwuct i2c_cwient *cwient, u8 weg)
{
	if (weg == AD7414_WEG_TEMP)
		wetuwn i2c_smbus_wead_wowd_swapped(cwient, weg);
	ewse
		wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static inwine int ad7414_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static stwuct ad7414_data *ad7414_update_device(stwuct device *dev)
{
	stwuct ad7414_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->wock);

	if (time_aftew(jiffies, data->next_update) || !data->vawid) {
		int vawue, i;

		dev_dbg(&cwient->dev, "stawting ad7414 update\n");

		vawue = ad7414_wead(cwient, AD7414_WEG_TEMP);
		if (vawue < 0)
			dev_dbg(&cwient->dev, "AD7414_WEG_TEMP eww %d\n",
				vawue);
		ewse
			data->temp_input = vawue;

		fow (i = 0; i < AWWAY_SIZE(AD7414_WEG_WIMIT); ++i) {
			vawue = ad7414_wead(cwient, AD7414_WEG_WIMIT[i]);
			if (vawue < 0)
				dev_dbg(&cwient->dev, "AD7414 weg %d eww %d\n",
					AD7414_WEG_WIMIT[i], vawue);
			ewse
				data->temps[i] = vawue;
		}

		data->next_update = jiffies + HZ + HZ / 2;
		data->vawid = twue;
	}

	mutex_unwock(&data->wock);

	wetuwn data;
}

static ssize_t temp_input_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad7414_data *data = ad7414_update_device(dev);
	wetuwn spwintf(buf, "%d\n", ad7414_temp_fwom_weg(data->temp_input));
}
static SENSOW_DEVICE_ATTW_WO(temp1_input, temp_input, 0);

static ssize_t max_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct ad7414_data *data = ad7414_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->temps[index] * 1000);
}

static ssize_t max_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct ad7414_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int index = to_sensow_dev_attw(attw)->index;
	u8 weg = AD7414_WEG_WIMIT[index];
	wong temp;
	int wet = kstwtow(buf, 10, &temp);

	if (wet < 0)
		wetuwn wet;

	temp = cwamp_vaw(temp, -40000, 85000);
	temp = (temp + (temp < 0 ? -500 : 500)) / 1000;

	mutex_wock(&data->wock);
	data->temps[index] = temp;
	ad7414_wwite(cwient, weg, temp);
	mutex_unwock(&data->wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_max, max_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, max_min, 1);

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct ad7414_data *data = ad7414_update_device(dev);
	int vawue = (data->temp_input >> bitnw) & 1;
	wetuwn spwintf(buf, "%d\n", vawue);
}

static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, 4);

static stwuct attwibute *ad7414_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(ad7414);

static int ad7414_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ad7414_data *data;
	stwuct device *hwmon_dev;
	int conf;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WEAD_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	data = devm_kzawwoc(dev, sizeof(stwuct ad7414_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->wock);

	dev_info(&cwient->dev, "chip found\n");

	/* Make suwe the chip is powewed up. */
	conf = i2c_smbus_wead_byte_data(cwient, AD7414_WEG_CONF);
	if (conf < 0)
		dev_wawn(dev, "ad7414_pwobe unabwe to wead config wegistew.\n");
	ewse {
		conf &= ~(1 << 7);
		i2c_smbus_wwite_byte_data(cwient, AD7414_WEG_CONF, conf);
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev,
							   cwient->name,
							   data, ad7414_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id ad7414_id[] = {
	{ "ad7414", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ad7414_id);

static const stwuct of_device_id __maybe_unused ad7414_of_match[] = {
	{ .compatibwe = "ad,ad7414" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ad7414_of_match);

static stwuct i2c_dwivew ad7414_dwivew = {
	.dwivew = {
		.name	= "ad7414",
		.of_match_tabwe = of_match_ptw(ad7414_of_match),
	},
	.pwobe = ad7414_pwobe,
	.id_tabwe = ad7414_id,
};

moduwe_i2c_dwivew(ad7414_dwivew);

MODUWE_AUTHOW("Stefan Woese <sw at denx.de>, "
	      "Fwank Edewhaeusew <fwank.edewhaeusew at spansion.com>");

MODUWE_DESCWIPTION("AD7414 dwivew");
MODUWE_WICENSE("GPW");
