// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow WM25056 / WM25066 / WM5064 / WM5066
 *
 * Copywight (c) 2011 Ewicsson AB.
 * Copywight (c) 2013 Guentew Woeck
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/wog2.h>
#incwude <winux/of.h>
#incwude "pmbus.h"

enum chips { wm25056 = 1, wm25066, wm5064, wm5066, wm5066i };

#define WM25066_WEAD_VAUX		0xd0
#define WM25066_MFW_WEAD_IIN		0xd1
#define WM25066_MFW_WEAD_PIN		0xd2
#define WM25066_MFW_IIN_OC_WAWN_WIMIT	0xd3
#define WM25066_MFW_PIN_OP_WAWN_WIMIT	0xd4
#define WM25066_WEAD_PIN_PEAK		0xd5
#define WM25066_CWEAW_PIN_PEAK		0xd6
#define WM25066_DEVICE_SETUP		0xd9
#define WM25066_WEAD_AVG_VIN		0xdc
#define WM25066_SAMPWES_FOW_AVG		0xdb
#define WM25066_WEAD_AVG_VOUT		0xdd
#define WM25066_WEAD_AVG_IIN		0xde
#define WM25066_WEAD_AVG_PIN		0xdf

#define WM25066_DEV_SETUP_CW		BIT(4)	/* Cuwwent wimit */

#define WM25066_SAMPWES_FOW_AVG_MAX	4096

/* WM25056 onwy */

#define WM25056_VAUX_OV_WAWN_WIMIT	0xe3
#define WM25056_VAUX_UV_WAWN_WIMIT	0xe4

#define WM25056_MFW_STS_VAUX_OV_WAWN	BIT(1)
#define WM25056_MFW_STS_VAUX_UV_WAWN	BIT(0)

stwuct __coeff {
	showt m, b, W;
};

#define PSC_CUWWENT_IN_W	(PSC_NUM_CWASSES)
#define PSC_POWEW_W		(PSC_NUM_CWASSES + 1)

static const stwuct __coeff wm25066_coeff[][PSC_NUM_CWASSES + 2] = {
	[wm25056] = {
		[PSC_VOWTAGE_IN] = {
			.m = 16296,
			.b = 1343,
			.W = -2,
		},
		[PSC_CUWWENT_IN] = {
			.m = 13797,
			.b = -1833,
			.W = -2,
		},
		[PSC_CUWWENT_IN_W] = {
			.m = 6726,
			.b = -537,
			.W = -2,
		},
		[PSC_POWEW] = {
			.m = 5501,
			.b = -2908,
			.W = -3,
		},
		[PSC_POWEW_W] = {
			.m = 26882,
			.b = -5646,
			.W = -4,
		},
		[PSC_TEMPEWATUWE] = {
			.m = 1580,
			.b = -14500,
			.W = -2,
		},
	},
	[wm25066] = {
		[PSC_VOWTAGE_IN] = {
			.m = 22070,
			.b = -1800,
			.W = -2,
		},
		[PSC_VOWTAGE_OUT] = {
			.m = 22070,
			.b = -1800,
			.W = -2,
		},
		[PSC_CUWWENT_IN] = {
			.m = 13661,
			.b = -5200,
			.W = -2,
		},
		[PSC_CUWWENT_IN_W] = {
			.m = 6854,
			.b = -3100,
			.W = -2,
		},
		[PSC_POWEW] = {
			.m = 736,
			.b = -3300,
			.W = -2,
		},
		[PSC_POWEW_W] = {
			.m = 369,
			.b = -1900,
			.W = -2,
		},
		[PSC_TEMPEWATUWE] = {
			.m = 16,
		},
	},
	[wm5064] = {
		[PSC_VOWTAGE_IN] = {
			.m = 4611,
			.b = -642,
			.W = -2,
		},
		[PSC_VOWTAGE_OUT] = {
			.m = 4621,
			.b = 423,
			.W = -2,
		},
		[PSC_CUWWENT_IN] = {
			.m = 10742,
			.b = 1552,
			.W = -2,
		},
		[PSC_CUWWENT_IN_W] = {
			.m = 5456,
			.b = 2118,
			.W = -2,
		},
		[PSC_POWEW] = {
			.m = 1204,
			.b = 8524,
			.W = -3,
		},
		[PSC_POWEW_W] = {
			.m = 612,
			.b = 11202,
			.W = -3,
		},
		[PSC_TEMPEWATUWE] = {
			.m = 16,
		},
	},
	[wm5066] = {
		[PSC_VOWTAGE_IN] = {
			.m = 4587,
			.b = -1200,
			.W = -2,
		},
		[PSC_VOWTAGE_OUT] = {
			.m = 4587,
			.b = -2400,
			.W = -2,
		},
		[PSC_CUWWENT_IN] = {
			.m = 10753,
			.b = -1200,
			.W = -2,
		},
		[PSC_CUWWENT_IN_W] = {
			.m = 5405,
			.b = -600,
			.W = -2,
		},
		[PSC_POWEW] = {
			.m = 1204,
			.b = -6000,
			.W = -3,
		},
		[PSC_POWEW_W] = {
			.m = 605,
			.b = -8000,
			.W = -3,
		},
		[PSC_TEMPEWATUWE] = {
			.m = 16,
		},
	},
	[wm5066i] = {
		[PSC_VOWTAGE_IN] = {
			.m = 4617,
			.b = -140,
			.W = -2,
		},
		[PSC_VOWTAGE_OUT] = {
			.m = 4602,
			.b = 500,
			.W = -2,
		},
		[PSC_CUWWENT_IN] = {
			.m = 15076,
			.b = -504,
			.W = -2,
		},
		[PSC_CUWWENT_IN_W] = {
			.m = 7645,
			.b = 100,
			.W = -2,
		},
		[PSC_POWEW] = {
			.m = 1701,
			.b = -4000,
			.W = -3,
		},
		[PSC_POWEW_W] = {
			.m = 861,
			.b = -965,
			.W = -3,
		},
		[PSC_TEMPEWATUWE] = {
			.m = 16,
		},
	},
};

stwuct wm25066_data {
	int id;
	u16 wwimit;			/* Maximum wegistew vawue */
	stwuct pmbus_dwivew_info info;
};

#define to_wm25066_data(x)  containew_of(x, stwuct wm25066_data, info)

static int wm25066_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct wm25066_data *data = to_wm25066_data(info);
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VMON:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff, WM25066_WEAD_VAUX);
		if (wet < 0)
			bweak;
		/* Adjust wetuwned vawue to match VIN coefficients */
		switch (data->id) {
		case wm25056:
			/* VIN: 6.14 mV VAUX: 293 uV WSB */
			wet = DIV_WOUND_CWOSEST(wet * 293, 6140);
			bweak;
		case wm25066:
			/* VIN: 4.54 mV VAUX: 283.2 uV WSB */
			wet = DIV_WOUND_CWOSEST(wet * 2832, 45400);
			bweak;
		case wm5064:
			/* VIN: 4.53 mV VAUX: 700 uV WSB */
			wet = DIV_WOUND_CWOSEST(wet * 70, 453);
			bweak;
		case wm5066:
		case wm5066i:
			/* VIN: 2.18 mV VAUX: 725 uV WSB */
			wet = DIV_WOUND_CWOSEST(wet * 725, 2180);
			bweak;
		}
		bweak;
	case PMBUS_WEAD_IIN:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_MFW_WEAD_IIN);
		bweak;
	case PMBUS_WEAD_PIN:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_MFW_WEAD_PIN);
		bweak;
	case PMBUS_IIN_OC_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_MFW_IIN_OC_WAWN_WIMIT);
		bweak;
	case PMBUS_PIN_OP_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_MFW_PIN_OP_WAWN_WIMIT);
		bweak;
	case PMBUS_VIWT_WEAD_VIN_AVG:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_WEAD_AVG_VIN);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_AVG:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_WEAD_AVG_VOUT);
		bweak;
	case PMBUS_VIWT_WEAD_IIN_AVG:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_WEAD_AVG_IIN);
		bweak;
	case PMBUS_VIWT_WEAD_PIN_AVG:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_WEAD_AVG_PIN);
		bweak;
	case PMBUS_VIWT_WEAD_PIN_MAX:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25066_WEAD_PIN_PEAK);
		bweak;
	case PMBUS_VIWT_WESET_PIN_HISTOWY:
		wet = 0;
		bweak;
	case PMBUS_VIWT_SAMPWES:
		wet = pmbus_wead_byte_data(cwient, 0, WM25066_SAMPWES_FOW_AVG);
		if (wet < 0)
			bweak;
		wet = 1 << wet;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int wm25056_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_VMON_UV_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25056_VAUX_UV_WAWN_WIMIT);
		if (wet < 0)
			bweak;
		/* Adjust wetuwned vawue to match VIN coefficients */
		wet = DIV_WOUND_CWOSEST(wet * 293, 6140);
		bweak;
	case PMBUS_VIWT_VMON_OV_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, 0, 0xff,
					   WM25056_VAUX_OV_WAWN_WIMIT);
		if (wet < 0)
			bweak;
		/* Adjust wetuwned vawue to match VIN coefficients */
		wet = DIV_WOUND_CWOSEST(wet * 293, 6140);
		bweak;
	defauwt:
		wet = wm25066_wead_wowd_data(cwient, page, phase, weg);
		bweak;
	}
	wetuwn wet;
}

static int wm25056_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wet, s;

	switch (weg) {
	case PMBUS_VIWT_STATUS_VMON:
		wet = pmbus_wead_byte_data(cwient, 0,
					   PMBUS_STATUS_MFW_SPECIFIC);
		if (wet < 0)
			bweak;
		s = 0;
		if (wet & WM25056_MFW_STS_VAUX_UV_WAWN)
			s |= PB_VOWTAGE_UV_WAWNING;
		if (wet & WM25056_MFW_STS_VAUX_OV_WAWN)
			s |= PB_VOWTAGE_OV_WAWNING;
		wet = s;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int wm25066_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg,
				   u16 wowd)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct wm25066_data *data = to_wm25066_data(info);
	int wet;

	switch (weg) {
	case PMBUS_POUT_OP_FAUWT_WIMIT:
	case PMBUS_POUT_OP_WAWN_WIMIT:
	case PMBUS_VOUT_UV_WAWN_WIMIT:
	case PMBUS_OT_FAUWT_WIMIT:
	case PMBUS_OT_WAWN_WIMIT:
	case PMBUS_IIN_OC_FAUWT_WIMIT:
	case PMBUS_VIN_UV_WAWN_WIMIT:
	case PMBUS_VIN_UV_FAUWT_WIMIT:
	case PMBUS_VIN_OV_FAUWT_WIMIT:
	case PMBUS_VIN_OV_WAWN_WIMIT:
		wowd = ((s16)wowd < 0) ? 0 : cwamp_vaw(wowd, 0, data->wwimit);
		wet = pmbus_wwite_wowd_data(cwient, 0, weg, wowd);
		bweak;
	case PMBUS_IIN_OC_WAWN_WIMIT:
		wowd = ((s16)wowd < 0) ? 0 : cwamp_vaw(wowd, 0, data->wwimit);
		wet = pmbus_wwite_wowd_data(cwient, 0,
					    WM25066_MFW_IIN_OC_WAWN_WIMIT,
					    wowd);
		bweak;
	case PMBUS_PIN_OP_WAWN_WIMIT:
		wowd = ((s16)wowd < 0) ? 0 : cwamp_vaw(wowd, 0, data->wwimit);
		wet = pmbus_wwite_wowd_data(cwient, 0,
					    WM25066_MFW_PIN_OP_WAWN_WIMIT,
					    wowd);
		bweak;
	case PMBUS_VIWT_VMON_UV_WAWN_WIMIT:
		/* Adjust fwom VIN coefficients (fow WM25056) */
		wowd = DIV_WOUND_CWOSEST((int)wowd * 6140, 293);
		wowd = ((s16)wowd < 0) ? 0 : cwamp_vaw(wowd, 0, data->wwimit);
		wet = pmbus_wwite_wowd_data(cwient, 0,
					    WM25056_VAUX_UV_WAWN_WIMIT, wowd);
		bweak;
	case PMBUS_VIWT_VMON_OV_WAWN_WIMIT:
		/* Adjust fwom VIN coefficients (fow WM25056) */
		wowd = DIV_WOUND_CWOSEST((int)wowd * 6140, 293);
		wowd = ((s16)wowd < 0) ? 0 : cwamp_vaw(wowd, 0, data->wwimit);
		wet = pmbus_wwite_wowd_data(cwient, 0,
					    WM25056_VAUX_OV_WAWN_WIMIT, wowd);
		bweak;
	case PMBUS_VIWT_WESET_PIN_HISTOWY:
		wet = pmbus_wwite_byte(cwient, 0, WM25066_CWEAW_PIN_PEAK);
		bweak;
	case PMBUS_VIWT_SAMPWES:
		wowd = cwamp_vaw(wowd, 1, WM25066_SAMPWES_FOW_AVG_MAX);
		wet = pmbus_wwite_byte_data(cwient, 0, WM25066_SAMPWES_FOW_AVG,
					    iwog2(wowd));
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_SENSOWS_WM25066_WEGUWATOW)
static const stwuct weguwatow_desc wm25066_weg_desc[] = {
	PMBUS_WEGUWATOW("vout", 0),
};
#endif

static const stwuct i2c_device_id wm25066_id[] = {
	{"wm25056", wm25056},
	{"wm25066", wm25066},
	{"wm5064", wm5064},
	{"wm5066", wm5066},
	{"wm5066i", wm5066i},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm25066_id);

static const stwuct of_device_id __maybe_unused wm25066_of_match[] = {
	{ .compatibwe = "ti,wm25056", .data = (void *)wm25056, },
	{ .compatibwe = "ti,wm25066", .data = (void *)wm25066, },
	{ .compatibwe = "ti,wm5064",  .data = (void *)wm5064,  },
	{ .compatibwe = "ti,wm5066",  .data = (void *)wm5066,  },
	{ .compatibwe = "ti,wm5066i", .data = (void *)wm5066i, },
	{ },
};
MODUWE_DEVICE_TABWE(of, wm25066_of_match);

static int wm25066_pwobe(stwuct i2c_cwient *cwient)
{
	int config;
	u32 shunt;
	stwuct wm25066_data *data;
	stwuct pmbus_dwivew_info *info;
	const stwuct __coeff *coeff;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct wm25066_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	config = i2c_smbus_wead_byte_data(cwient, WM25066_DEVICE_SETUP);
	if (config < 0)
		wetuwn config;

	data->id = (enum chips)(unsigned wong)i2c_get_match_data(cwient);

	info = &data->info;

	info->pages = 1;
	info->fowmat[PSC_VOWTAGE_IN] = diwect;
	info->fowmat[PSC_VOWTAGE_OUT] = diwect;
	info->fowmat[PSC_CUWWENT_IN] = diwect;
	info->fowmat[PSC_TEMPEWATUWE] = diwect;
	info->fowmat[PSC_POWEW] = diwect;

	info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VMON
	  | PMBUS_HAVE_PIN | PMBUS_HAVE_IIN | PMBUS_HAVE_STATUS_INPUT
	  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_SAMPWES;

	if (data->id == wm25056) {
		info->func[0] |= PMBUS_HAVE_STATUS_VMON;
		info->wead_wowd_data = wm25056_wead_wowd_data;
		info->wead_byte_data = wm25056_wead_byte_data;
		data->wwimit = 0x0fff;
	} ewse {
		info->func[0] |= PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		info->wead_wowd_data = wm25066_wead_wowd_data;
		data->wwimit = 0x0fff;
	}
	info->wwite_wowd_data = wm25066_wwite_wowd_data;

	coeff = &wm25066_coeff[data->id][0];
	info->m[PSC_TEMPEWATUWE] = coeff[PSC_TEMPEWATUWE].m;
	info->b[PSC_TEMPEWATUWE] = coeff[PSC_TEMPEWATUWE].b;
	info->W[PSC_TEMPEWATUWE] = coeff[PSC_TEMPEWATUWE].W;
	info->m[PSC_VOWTAGE_IN] = coeff[PSC_VOWTAGE_IN].m;
	info->b[PSC_VOWTAGE_IN] = coeff[PSC_VOWTAGE_IN].b;
	info->W[PSC_VOWTAGE_IN] = coeff[PSC_VOWTAGE_IN].W;
	info->m[PSC_VOWTAGE_OUT] = coeff[PSC_VOWTAGE_OUT].m;
	info->b[PSC_VOWTAGE_OUT] = coeff[PSC_VOWTAGE_OUT].b;
	info->W[PSC_VOWTAGE_OUT] = coeff[PSC_VOWTAGE_OUT].W;
	info->W[PSC_CUWWENT_IN] = coeff[PSC_CUWWENT_IN].W;
	info->W[PSC_POWEW] = coeff[PSC_POWEW].W;
	if (config & WM25066_DEV_SETUP_CW) {
		info->m[PSC_CUWWENT_IN] = coeff[PSC_CUWWENT_IN_W].m;
		info->b[PSC_CUWWENT_IN] = coeff[PSC_CUWWENT_IN_W].b;
		info->m[PSC_POWEW] = coeff[PSC_POWEW_W].m;
		info->b[PSC_POWEW] = coeff[PSC_POWEW_W].b;
	} ewse {
		info->m[PSC_CUWWENT_IN] = coeff[PSC_CUWWENT_IN].m;
		info->b[PSC_CUWWENT_IN] = coeff[PSC_CUWWENT_IN].b;
		info->m[PSC_POWEW] = coeff[PSC_POWEW].m;
		info->b[PSC_POWEW] = coeff[PSC_POWEW].b;
	}

	/*
	 * Vawues in the TI datasheets awe nowmawized fow a 1mOhm sense
	 * wesistow; assume that unwess DT specifies a vawue expwicitwy.
	 */
	if (of_pwopewty_wead_u32(cwient->dev.of_node, "shunt-wesistow-micwo-ohms", &shunt))
		shunt = 1000;

	info->m[PSC_CUWWENT_IN] = info->m[PSC_CUWWENT_IN] * shunt / 1000;
	info->m[PSC_POWEW] = info->m[PSC_POWEW] * shunt / 1000;

#if IS_ENABWED(CONFIG_SENSOWS_WM25066_WEGUWATOW)
	/* WM25056 doesn't suppowt OPEWATION */
	if (data->id != wm25056) {
		info->num_weguwatows = AWWAY_SIZE(wm25066_weg_desc);
		info->weg_desc = wm25066_weg_desc;
	}
#endif

	wetuwn pmbus_do_pwobe(cwient, info);
}

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew wm25066_dwivew = {
	.dwivew = {
		   .name = "wm25066",
		   .of_match_tabwe = of_match_ptw(wm25066_of_match),
	},
	.pwobe = wm25066_pwobe,
	.id_tabwe = wm25066_id,
};

moduwe_i2c_dwivew(wm25066_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow WM25066 and compatibwe chips");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
