// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Maxim MAX16064
 *
 * Copywight (c) 2011 Ewicsson AB.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude "pmbus.h"

#define MAX16064_MFW_VOUT_PEAK		0xd4
#define MAX16064_MFW_TEMPEWATUWE_PEAK	0xd6

static int max16064_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				   int phase, int weg)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX16064_MFW_VOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX16064_MFW_TEMPEWATUWE_PEAK);
		bweak;
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		wet = 0;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int max16064_wwite_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int weg, u16 wowd)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX16064_MFW_VOUT_PEAK, 0);
		bweak;
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX16064_MFW_TEMPEWATUWE_PEAK,
					    0xffff);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static stwuct pmbus_dwivew_info max16064_info = {
	.pages = 4,
	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.m[PSC_VOWTAGE_IN] = 19995,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = -1,
	.m[PSC_VOWTAGE_OUT] = 19995,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = -1,
	.m[PSC_TEMPEWATUWE] = -7612,
	.b[PSC_TEMPEWATUWE] = 335,
	.W[PSC_TEMPEWATUWE] = -3,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_TEMP,
	.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
	.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
	.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
	.wead_wowd_data = max16064_wead_wowd_data,
	.wwite_wowd_data = max16064_wwite_wowd_data,
};

static int max16064_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn pmbus_do_pwobe(cwient, &max16064_info);
}

static const stwuct i2c_device_id max16064_id[] = {
	{"max16064", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, max16064_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew max16064_dwivew = {
	.dwivew = {
		   .name = "max16064",
		   },
	.pwobe = max16064_pwobe,
	.id_tabwe = max16064_id,
};

moduwe_i2c_dwivew(max16064_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow Maxim MAX16064");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
