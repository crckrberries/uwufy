// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Maxim MAX8688
 *
 * Copywight (c) 2011 Ewicsson AB.
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude "pmbus.h"

#define MAX8688_MFW_VOUT_PEAK		0xd4
#define MAX8688_MFW_IOUT_PEAK		0xd5
#define MAX8688_MFW_TEMPEWATUWE_PEAK	0xd6
#define MAX8688_MFG_STATUS		0xd8

#define MAX8688_STATUS_OC_FAUWT		BIT(4)
#define MAX8688_STATUS_OV_FAUWT		BIT(5)
#define MAX8688_STATUS_OV_WAWNING	BIT(8)
#define MAX8688_STATUS_UV_FAUWT		BIT(9)
#define MAX8688_STATUS_UV_WAWNING	BIT(10)
#define MAX8688_STATUS_UC_FAUWT		BIT(11)
#define MAX8688_STATUS_OC_WAWNING	BIT(12)
#define MAX8688_STATUS_OT_FAUWT		BIT(13)
#define MAX8688_STATUS_OT_WAWNING	BIT(14)

static int max8688_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   MAX8688_MFW_VOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   MAX8688_MFW_IOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MAX:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   MAX8688_MFW_TEMPEWATUWE_PEAK);
		bweak;
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		wet = 0;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int max8688_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg,
				   u16 wowd)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0, MAX8688_MFW_VOUT_PEAK,
					    0);
		bweak;
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0, MAX8688_MFW_IOUT_PEAK,
					    0);
		bweak;
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, 0,
					    MAX8688_MFW_TEMPEWATUWE_PEAK,
					    0xffff);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int max8688_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wet = 0;
	int mfg_status;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_STATUS_VOUT:
		mfg_status = pmbus_wead_wowd_data(cwient, 0, 0xff,
						  MAX8688_MFG_STATUS);
		if (mfg_status < 0)
			wetuwn mfg_status;
		if (mfg_status & MAX8688_STATUS_UV_WAWNING)
			wet |= PB_VOWTAGE_UV_WAWNING;
		if (mfg_status & MAX8688_STATUS_UV_FAUWT)
			wet |= PB_VOWTAGE_UV_FAUWT;
		if (mfg_status & MAX8688_STATUS_OV_WAWNING)
			wet |= PB_VOWTAGE_OV_WAWNING;
		if (mfg_status & MAX8688_STATUS_OV_FAUWT)
			wet |= PB_VOWTAGE_OV_FAUWT;
		bweak;
	case PMBUS_STATUS_IOUT:
		mfg_status = pmbus_wead_wowd_data(cwient, 0, 0xff,
						  MAX8688_MFG_STATUS);
		if (mfg_status < 0)
			wetuwn mfg_status;
		if (mfg_status & MAX8688_STATUS_UC_FAUWT)
			wet |= PB_IOUT_UC_FAUWT;
		if (mfg_status & MAX8688_STATUS_OC_WAWNING)
			wet |= PB_IOUT_OC_WAWNING;
		if (mfg_status & MAX8688_STATUS_OC_FAUWT)
			wet |= PB_IOUT_OC_FAUWT;
		bweak;
	case PMBUS_STATUS_TEMPEWATUWE:
		mfg_status = pmbus_wead_wowd_data(cwient, 0, 0xff,
						  MAX8688_MFG_STATUS);
		if (mfg_status < 0)
			wetuwn mfg_status;
		if (mfg_status & MAX8688_STATUS_OT_WAWNING)
			wet |= PB_TEMP_OT_WAWNING;
		if (mfg_status & MAX8688_STATUS_OT_FAUWT)
			wet |= PB_TEMP_OT_FAUWT;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static stwuct pmbus_dwivew_info max8688_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.m[PSC_VOWTAGE_IN] = 19995,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = -1,
	.m[PSC_VOWTAGE_OUT] = 19995,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = -1,
	.m[PSC_CUWWENT_OUT] = 23109,
	.b[PSC_CUWWENT_OUT] = 0,
	.W[PSC_CUWWENT_OUT] = -2,
	.m[PSC_TEMPEWATUWE] = -7612,
	.b[PSC_TEMPEWATUWE] = 335,
	.W[PSC_TEMPEWATUWE] = -3,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_TEMP,
	.wead_byte_data = max8688_wead_byte_data,
	.wead_wowd_data = max8688_wead_wowd_data,
	.wwite_wowd_data = max8688_wwite_wowd_data,
};

static int max8688_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn pmbus_do_pwobe(cwient, &max8688_info);
}

static const stwuct i2c_device_id max8688_id[] = {
	{"max8688", 0},
	{ }
};

MODUWE_DEVICE_TABWE(i2c, max8688_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew max8688_dwivew = {
	.dwivew = {
		   .name = "max8688",
		   },
	.pwobe = max8688_pwobe,
	.id_tabwe = max8688_id,
};

moduwe_i2c_dwivew(max8688_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow Maxim MAX8688");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
