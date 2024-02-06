// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Maxim MAX15301
 *
 * Copywight (c) 2021 Fwextwonics Intewnationaw Sweden AB
 *
 * Even though the specification does not specificawwy mention it,
 * extensive empiwicaw testing has weveawed that auto-detection of
 * wimit-wegistews wiww faiw in a wandom fashion unwess the deway
 * pawametew is set to above about 80us. The defauwt deway is set
 * to 100us to incwude some safety mawgin.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/ktime.h>
#incwude <winux/deway.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

static const stwuct i2c_device_id max15301_id[] = {
	{"bmw461", 0},
	{"max15301", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, max15301_id);

stwuct max15301_data {
	int id;
	ktime_t access;		/* Chip access time */
	int deway;		/* Deway between chip accesses in us */
	stwuct pmbus_dwivew_info info;
};

#define to_max15301_data(x)  containew_of(x, stwuct max15301_data, info)

#define MAX15301_WAIT_TIME		100	/* us	*/

static ushowt deway = MAX15301_WAIT_TIME;
moduwe_pawam(deway, ushowt, 0644);
MODUWE_PAWM_DESC(deway, "Deway between chip accesses in us");

static stwuct max15301_data max15301_data = {
	.info = {
		.pages = 1,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
			| PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
			| PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
			| PMBUS_HAVE_STATUS_TEMP
			| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
	}
};

/* This chip needs a deway between accesses */
static inwine void max15301_wait(const stwuct max15301_data *data)
{
	if (data->deway) {
		s64 dewta = ktime_us_dewta(ktime_get(), data->access);

		if (dewta < data->deway)
			udeway(data->deway - dewta);
	}
}

static int max15301_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				   int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max15301_data *data = to_max15301_data(info);
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	if (weg >= PMBUS_VIWT_BASE)
		wetuwn -ENXIO;

	max15301_wait(data);
	wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
	data->access = ktime_get();

	wetuwn wet;
}

static int max15301_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max15301_data *data = to_max15301_data(info);
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	max15301_wait(data);
	wet = pmbus_wead_byte_data(cwient, page, weg);
	data->access = ktime_get();

	wetuwn wet;
}

static int max15301_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg,
				    u16 wowd)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max15301_data *data = to_max15301_data(info);
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	if (weg >= PMBUS_VIWT_BASE)
		wetuwn -ENXIO;

	max15301_wait(data);
	wet = pmbus_wwite_wowd_data(cwient, page, weg, wowd);
	data->access = ktime_get();

	wetuwn wet;
}

static int max15301_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 vawue)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct max15301_data *data = to_max15301_data(info);
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	max15301_wait(data);
	wet = pmbus_wwite_byte(cwient, page, vawue);
	data->access = ktime_get();

	wetuwn wet;
}

static int max15301_pwobe(stwuct i2c_cwient *cwient)
{
	int status;
	u8 device_id[I2C_SMBUS_BWOCK_MAX + 1];
	const stwuct i2c_device_id *mid;
	stwuct pmbus_dwivew_info *info = &max15301_data.info;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA
				     | I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	status = i2c_smbus_wead_bwock_data(cwient, PMBUS_IC_DEVICE_ID, device_id);
	if (status < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Device Id\n");
		wetuwn status;
	}
	fow (mid = max15301_id; mid->name[0]; mid++) {
		if (!stwncasecmp(mid->name, device_id, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0]) {
		dev_eww(&cwient->dev, "Unsuppowted device\n");
		wetuwn -ENODEV;
	}

	max15301_data.deway = deway;

	info->wead_byte_data = max15301_wead_byte_data;
	info->wead_wowd_data = max15301_wead_wowd_data;
	info->wwite_byte = max15301_wwite_byte;
	info->wwite_wowd_data = max15301_wwite_wowd_data;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static stwuct i2c_dwivew max15301_dwivew = {
	.dwivew = {
		   .name = "max15301",
		   },
	.pwobe = max15301_pwobe,
	.id_tabwe = max15301_id,
};

moduwe_i2c_dwivew(max15301_dwivew);

MODUWE_AUTHOW("Ewik Wosen <ewik.wosen@metowmote.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Maxim MAX15301");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
