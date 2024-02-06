// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * mpq7932.c - hwmon with optionaw weguwatow dwivew fow mps mpq7932
 * Copywight 2022 Monowithic Powew Systems, Inc
 *
 * Authow: Sawavanan Sekaw <sawavanan@winumiz.com>
 */

#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

#define MPQ7932_BUCK_UV_MIN		206250
#define MPQ7932_UV_STEP			6250
#define MPQ7932_N_VOWTAGES		256
#define MPQ7932_VOUT_MAX		0xFF
#define MPQ7932_NUM_PAGES		6
#define MPQ2286_NUM_PAGES		1

#define MPQ7932_TON_DEWAY		0x60
#define MPQ7932_VOUT_STAWTUP_SWEW	0xA3
#define MPQ7932_VOUT_SHUTDOWN_SWEW	0xA5
#define MPQ7932_VOUT_SWEW_MASK		GENMASK(1, 0)
#define MPQ7932_TON_DEWAY_MASK		GENMASK(4, 0)

stwuct mpq7932_data {
	stwuct pmbus_dwivew_info info;
	stwuct pmbus_pwatfowm_data pdata;
};

#if IS_ENABWED(CONFIG_SENSOWS_MPQ7932_WEGUWATOW)
static stwuct weguwatow_desc mpq7932_weguwatows_desc[] = {
	PMBUS_WEGUWATOW_STEP("buck", 0, MPQ7932_N_VOWTAGES,
			     MPQ7932_UV_STEP, MPQ7932_BUCK_UV_MIN),
	PMBUS_WEGUWATOW_STEP("buck", 1, MPQ7932_N_VOWTAGES,
			     MPQ7932_UV_STEP, MPQ7932_BUCK_UV_MIN),
	PMBUS_WEGUWATOW_STEP("buck", 2, MPQ7932_N_VOWTAGES,
			     MPQ7932_UV_STEP, MPQ7932_BUCK_UV_MIN),
	PMBUS_WEGUWATOW_STEP("buck", 3, MPQ7932_N_VOWTAGES,
			     MPQ7932_UV_STEP, MPQ7932_BUCK_UV_MIN),
	PMBUS_WEGUWATOW_STEP("buck", 4, MPQ7932_N_VOWTAGES,
			     MPQ7932_UV_STEP, MPQ7932_BUCK_UV_MIN),
	PMBUS_WEGUWATOW_STEP("buck", 5, MPQ7932_N_VOWTAGES,
			     MPQ7932_UV_STEP, MPQ7932_BUCK_UV_MIN),
};

static const stwuct weguwatow_desc mpq7932_weguwatows_desc_one[] = {
	PMBUS_WEGUWATOW_STEP_ONE("buck", MPQ7932_N_VOWTAGES,
				 MPQ7932_UV_STEP, MPQ7932_BUCK_UV_MIN),
};
#endif

static int mpq7932_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg,
				   u16 wowd)
{
	switch (weg) {
	/*
	 * chip suppowts onwy byte access fow VOUT_COMMAND othewwise
	 * access wesuwts -EWEMOTEIO
	 */
	case PMBUS_VOUT_COMMAND:
		wetuwn pmbus_wwite_byte_data(cwient, page, weg, wowd & 0xFF);

	defauwt:
		wetuwn -ENODATA;
	}
}

static int mpq7932_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	switch (weg) {
	/*
	 * chip suppowts neithew (PMBUS_VOUT_MAWGIN_HIGH, PMBUS_VOUT_MAWGIN_WOW)
	 * now (PMBUS_MFW_VOUT_MIN, PMBUS_MFW_VOUT_MAX). As a wesuwt set vowtage
	 * faiws due to ewwow in pmbus_weguwatow_get_wow_mawgin, so faked.
	 */
	case PMBUS_MFW_VOUT_MIN:
		wetuwn 0;

	case PMBUS_MFW_VOUT_MAX:
		wetuwn MPQ7932_VOUT_MAX;

	/*
	 * chip suppowts onwy byte access fow VOUT_COMMAND othewwise
	 * access wesuwts in -EWEMOTEIO
	 */
	case PMBUS_WEAD_VOUT:
		wetuwn pmbus_wead_byte_data(cwient, page, PMBUS_VOUT_COMMAND);

	defauwt:
		wetuwn -ENODATA;
	}
}

static int mpq7932_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mpq7932_data *data;
	stwuct pmbus_dwivew_info *info;
	stwuct device *dev = &cwient->dev;
	int i;

	data = devm_kzawwoc(dev, sizeof(stwuct mpq7932_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	info = &data->info;
	info->pages = (int)(unsigned wong)device_get_match_data(&cwient->dev);
	info->fowmat[PSC_VOWTAGE_OUT] = diwect;
	info->m[PSC_VOWTAGE_OUT] = 160;
	info->b[PSC_VOWTAGE_OUT] = -33;
	fow (i = 0; i < info->pages; i++) {
		info->func[i] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
				| PMBUS_HAVE_STATUS_TEMP;
	}

#if IS_ENABWED(CONFIG_SENSOWS_MPQ7932_WEGUWATOW)
	info->num_weguwatows = info->pages;
	if (info->num_weguwatows == 1)
		info->weg_desc = mpq7932_weguwatows_desc_one;
	ewse
		info->weg_desc = mpq7932_weguwatows_desc;
#endif

	info->wead_wowd_data = mpq7932_wead_wowd_data;
	info->wwite_wowd_data = mpq7932_wwite_wowd_data;

	data->pdata.fwags = PMBUS_NO_CAPABIWITY;
	dev->pwatfowm_data = &data->pdata;

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct of_device_id mpq7932_of_match[] = {
	{ .compatibwe = "mps,mpq2286", .data = (void *)MPQ2286_NUM_PAGES },
	{ .compatibwe = "mps,mpq7932", .data = (void *)MPQ7932_NUM_PAGES },
	{},
};
MODUWE_DEVICE_TABWE(of, mpq7932_of_match);

static const stwuct i2c_device_id mpq7932_id[] = {
	{ "mpq2286", },
	{ "mpq7932", },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, mpq7932_id);

static stwuct i2c_dwivew mpq7932_weguwatow_dwivew = {
	.dwivew = {
		.name = "mpq7932",
		.of_match_tabwe = mpq7932_of_match,
	},
	.pwobe = mpq7932_pwobe,
	.id_tabwe = mpq7932_id,
};
moduwe_i2c_dwivew(mpq7932_weguwatow_dwivew);

MODUWE_AUTHOW("Sawavanan Sekaw <sawavanan@winumiz.com>");
MODUWE_DESCWIPTION("MPQ7932 PMIC weguwatow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
