// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADT7410/ADT7420 digitaw tempewatuwe sensow dwivew
 *
 * Copywight 2012-2013 Anawog Devices Inc.
 *   Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

#incwude "adt7x10.h"

static boow adt7410_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ADT7X10_TEMPEWATUWE:
	case ADT7X10_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int adt7410_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct i2c_cwient *cwient = context;
	int wegvaw;

	switch (weg) {
	case ADT7X10_TEMPEWATUWE:
	case ADT7X10_T_AWAWM_HIGH:
	case ADT7X10_T_AWAWM_WOW:
	case ADT7X10_T_CWIT:
		wegvaw = i2c_smbus_wead_wowd_swapped(cwient, weg);
		bweak;
	defauwt:
		wegvaw = i2c_smbus_wead_byte_data(cwient, weg);
		bweak;
	}
	if (wegvaw < 0)
		wetuwn wegvaw;
	*vaw = wegvaw;
	wetuwn 0;
}

static int adt7410_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct i2c_cwient *cwient = context;
	int wet;

	switch (weg) {
	case ADT7X10_TEMPEWATUWE:
	case ADT7X10_T_AWAWM_HIGH:
	case ADT7X10_T_AWAWM_WOW:
	case ADT7X10_T_CWIT:
		wet = i2c_smbus_wwite_wowd_swapped(cwient, weg, vaw);
		bweak;
	defauwt:
		wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
		bweak;
	}
	wetuwn wet;
}

static const stwuct wegmap_config adt7410_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = ADT7X10_ID,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = adt7410_wegmap_is_vowatiwe,
	.weg_wead = adt7410_weg_wead,
	.weg_wwite = adt7410_weg_wwite,
};

static int adt7410_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init(&cwient->dev, NUWW, cwient,
				  &adt7410_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn adt7x10_pwobe(&cwient->dev, cwient->name, cwient->iwq, wegmap);
}

static const stwuct i2c_device_id adt7410_ids[] = {
	{ "adt7410", 0 },
	{ "adt7420", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, adt7410_ids);

static stwuct i2c_dwivew adt7410_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "adt7410",
		.pm	= pm_sweep_ptw(&adt7x10_dev_pm_ops),
	},
	.pwobe		= adt7410_i2c_pwobe,
	.id_tabwe	= adt7410_ids,
	.addwess_wist	= I2C_ADDWS(0x48, 0x49, 0x4a, 0x4b),
};
moduwe_i2c_dwivew(adt7410_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("ADT7410/AD7420 dwivew");
MODUWE_WICENSE("GPW");
