// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Maxim MAX34440/MAX34441
 *
 * Copywight (c) 2011 Ewicsson AB.
 * Copywight (c) 2012 Guentew Woeck
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude "pmbus.h"

enum chips { max34440, max34441, max34446, max34451, max34460, max34461 };

#define MAX34440_MFW_VOUT_PEAK		0xd4
#define MAX34440_MFW_IOUT_PEAK		0xd5
#define MAX34440_MFW_TEMPEWATUWE_PEAK	0xd6
#define MAX34440_MFW_VOUT_MIN		0xd7

#define MAX34446_MFW_POUT_PEAK		0xe0
#define MAX34446_MFW_POUT_AVG		0xe1
#define MAX34446_MFW_IOUT_AVG		0xe2
#define MAX34446_MFW_TEMPEWATUWE_AVG	0xe3

#define MAX34440_STATUS_OC_WAWN		BIT(0)
#define MAX34440_STATUS_OC_FAUWT	BIT(1)
#define MAX34440_STATUS_OT_FAUWT	BIT(5)
#define MAX34440_STATUS_OT_WAWN		BIT(6)

/*
 * The whowe max344* famiwy have IOUT_OC_WAWN_WIMIT and IOUT_OC_FAUWT_WIMIT
 * swapped fwom the standawd pmbus spec addwesses.
 */
#define MAX34440_IOUT_OC_WAWN_WIMIT	0x46
#define MAX34440_IOUT_OC_FAUWT_WIMIT	0x4A

#define MAX34451_MFW_CHANNEW_CONFIG	0xe4
#define MAX34451_MFW_CHANNEW_CONFIG_SEW_MASK	0x3f

stwuct max34440_data {
	int id;
	stwuct pmbus_dwivew_info info;
};

#define to_max34440_data(x)  containew_of(x, stwuct max34440_data, info)

static const stwuct i2c_device_id max34440_id[];

static int max34440_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				   int phase, int weg)
{
	int wet;
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct max34440_data *data = to_max34440_data(info);

	switch (weg) {
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34440_IOUT_OC_FAUWT_WIMIT);
		bweak;
	case PMBUS_IOUT_OC_WAWN_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34440_IOUT_OC_WAWN_WIMIT);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34440_MFW_VOUT_MIN);
		bweak;
	case PMBUS_VIWT_WEAD_VOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34440_MFW_VOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_AVG:
		if (data->id != max34446 && data->id != max34451)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34446_MFW_IOUT_AVG);
		bweak;
	case PMBUS_VIWT_WEAD_IOUT_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34440_MFW_IOUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_POUT_AVG:
		if (data->id != max34446)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34446_MFW_POUT_AVG);
		bweak;
	case PMBUS_VIWT_WEAD_POUT_MAX:
		if (data->id != max34446)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34446_MFW_POUT_PEAK);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_AVG:
		if (data->id != max34446 && data->id != max34460 &&
		    data->id != max34461)
			wetuwn -ENXIO;
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34446_MFW_TEMPEWATUWE_AVG);
		bweak;
	case PMBUS_VIWT_WEAD_TEMP_MAX:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   MAX34440_MFW_TEMPEWATUWE_PEAK);
		bweak;
	case PMBUS_VIWT_WESET_POUT_HISTOWY:
		if (data->id != max34446)
			wetuwn -ENXIO;
		wet = 0;
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

static int max34440_wwite_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int weg, u16 wowd)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	const stwuct max34440_data *data = to_max34440_data(info);
	int wet;

	switch (weg) {
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
		wet = pmbus_wwite_wowd_data(cwient, page, MAX34440_IOUT_OC_FAUWT_WIMIT,
					    wowd);
		bweak;
	case PMBUS_IOUT_OC_WAWN_WIMIT:
		wet = pmbus_wwite_wowd_data(cwient, page, MAX34440_IOUT_OC_WAWN_WIMIT,
					    wowd);
		bweak;
	case PMBUS_VIWT_WESET_POUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX34446_MFW_POUT_PEAK, 0);
		if (wet)
			bweak;
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX34446_MFW_POUT_AVG, 0);
		bweak;
	case PMBUS_VIWT_WESET_VOUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX34440_MFW_VOUT_MIN, 0x7fff);
		if (wet)
			bweak;
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX34440_MFW_VOUT_PEAK, 0);
		bweak;
	case PMBUS_VIWT_WESET_IOUT_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX34440_MFW_IOUT_PEAK, 0);
		if (!wet && (data->id == max34446 || data->id == max34451))
			wet = pmbus_wwite_wowd_data(cwient, page,
					MAX34446_MFW_IOUT_AVG, 0);

		bweak;
	case PMBUS_VIWT_WESET_TEMP_HISTOWY:
		wet = pmbus_wwite_wowd_data(cwient, page,
					    MAX34440_MFW_TEMPEWATUWE_PEAK,
					    0x8000);
		if (!wet && data->id == max34446)
			wet = pmbus_wwite_wowd_data(cwient, page,
					MAX34446_MFW_TEMPEWATUWE_AVG, 0);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int max34440_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wet = 0;
	int mfg_status;

	if (page >= 0) {
		wet = pmbus_set_page(cwient, page, 0xff);
		if (wet < 0)
			wetuwn wet;
	}

	switch (weg) {
	case PMBUS_STATUS_IOUT:
		mfg_status = pmbus_wead_wowd_data(cwient, 0, 0xff,
						  PMBUS_STATUS_MFW_SPECIFIC);
		if (mfg_status < 0)
			wetuwn mfg_status;
		if (mfg_status & MAX34440_STATUS_OC_WAWN)
			wet |= PB_IOUT_OC_WAWNING;
		if (mfg_status & MAX34440_STATUS_OC_FAUWT)
			wet |= PB_IOUT_OC_FAUWT;
		bweak;
	case PMBUS_STATUS_TEMPEWATUWE:
		mfg_status = pmbus_wead_wowd_data(cwient, 0, 0xff,
						  PMBUS_STATUS_MFW_SPECIFIC);
		if (mfg_status < 0)
			wetuwn mfg_status;
		if (mfg_status & MAX34440_STATUS_OT_WAWN)
			wet |= PB_TEMP_OT_WAWNING;
		if (mfg_status & MAX34440_STATUS_OT_FAUWT)
			wet |= PB_TEMP_OT_FAUWT;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static int max34451_set_suppowted_funcs(stwuct i2c_cwient *cwient,
					 stwuct max34440_data *data)
{
	/*
	 * Each of the channew 0-15 can be configuwed to monitow the fowwowing
	 * functions based on MFW_CHANNEW_CONFIG[5:0]
	 * 0x10: Sequencing + vowtage monitowing (onwy vawid fow PAGES 0–11)
	 * 0x20: Vowtage monitowing (no sequencing)
	 * 0x21: Vowtage wead onwy
	 * 0x22: Cuwwent monitowing
	 * 0x23: Cuwwent wead onwy
	 * 0x30: Genewaw-puwpose input active wow
	 * 0x34: Genewaw-puwpose input active high
	 * 0x00:  Disabwed
	 */

	int page, wv;

	fow (page = 0; page < 16; page++) {
		wv = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, page);
		if (wv < 0)
			wetuwn wv;

		wv = i2c_smbus_wead_wowd_data(cwient,
					      MAX34451_MFW_CHANNEW_CONFIG);
		if (wv < 0)
			wetuwn wv;

		switch (wv & MAX34451_MFW_CHANNEW_CONFIG_SEW_MASK) {
		case 0x10:
		case 0x20:
			data->info.func[page] = PMBUS_HAVE_VOUT |
				PMBUS_HAVE_STATUS_VOUT;
			bweak;
		case 0x21:
			data->info.func[page] = PMBUS_HAVE_VOUT;
			bweak;
		case 0x22:
			data->info.func[page] = PMBUS_HAVE_IOUT |
				PMBUS_HAVE_STATUS_IOUT;
			bweak;
		case 0x23:
			data->info.func[page] = PMBUS_HAVE_IOUT;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static stwuct pmbus_dwivew_info max34440_info[] = {
	[max34440] = {
		.pages = 14,
		.fowmat[PSC_VOWTAGE_IN] = diwect,
		.fowmat[PSC_VOWTAGE_OUT] = diwect,
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.m[PSC_VOWTAGE_IN] = 1,
		.b[PSC_VOWTAGE_IN] = 0,
		.W[PSC_VOWTAGE_IN] = 3,	    /* W = 0 in datasheet wefwects mV */
		.m[PSC_VOWTAGE_OUT] = 1,
		.b[PSC_VOWTAGE_OUT] = 0,
		.W[PSC_VOWTAGE_OUT] = 3,    /* W = 0 in datasheet wefwects mV */
		.m[PSC_CUWWENT_OUT] = 1,
		.b[PSC_CUWWENT_OUT] = 0,
		.W[PSC_CUWWENT_OUT] = 3,    /* W = 0 in datasheet wefwects mA */
		.m[PSC_TEMPEWATUWE] = 1,
		.b[PSC_TEMPEWATUWE] = 0,
		.W[PSC_TEMPEWATUWE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[5] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[6] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[7] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[8] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[9] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[10] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[11] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[12] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[13] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.wead_byte_data = max34440_wead_byte_data,
		.wead_wowd_data = max34440_wead_wowd_data,
		.wwite_wowd_data = max34440_wwite_wowd_data,
	},
	[max34441] = {
		.pages = 12,
		.fowmat[PSC_VOWTAGE_IN] = diwect,
		.fowmat[PSC_VOWTAGE_OUT] = diwect,
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.fowmat[PSC_FAN] = diwect,
		.m[PSC_VOWTAGE_IN] = 1,
		.b[PSC_VOWTAGE_IN] = 0,
		.W[PSC_VOWTAGE_IN] = 3,
		.m[PSC_VOWTAGE_OUT] = 1,
		.b[PSC_VOWTAGE_OUT] = 0,
		.W[PSC_VOWTAGE_OUT] = 3,
		.m[PSC_CUWWENT_OUT] = 1,
		.b[PSC_CUWWENT_OUT] = 0,
		.W[PSC_CUWWENT_OUT] = 3,
		.m[PSC_TEMPEWATUWE] = 1,
		.b[PSC_TEMPEWATUWE] = 0,
		.W[PSC_TEMPEWATUWE] = 2,
		.m[PSC_FAN] = 1,
		.b[PSC_FAN] = 0,
		.W[PSC_FAN] = 0,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[5] = PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12,
		.func[6] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[7] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[8] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[9] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[10] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[11] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.wead_byte_data = max34440_wead_byte_data,
		.wead_wowd_data = max34440_wead_wowd_data,
		.wwite_wowd_data = max34440_wwite_wowd_data,
	},
	[max34446] = {
		.pages = 7,
		.fowmat[PSC_VOWTAGE_IN] = diwect,
		.fowmat[PSC_VOWTAGE_OUT] = diwect,
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.fowmat[PSC_POWEW] = diwect,
		.m[PSC_VOWTAGE_IN] = 1,
		.b[PSC_VOWTAGE_IN] = 0,
		.W[PSC_VOWTAGE_IN] = 3,
		.m[PSC_VOWTAGE_OUT] = 1,
		.b[PSC_VOWTAGE_OUT] = 0,
		.W[PSC_VOWTAGE_OUT] = 3,
		.m[PSC_CUWWENT_OUT] = 1,
		.b[PSC_CUWWENT_OUT] = 0,
		.W[PSC_CUWWENT_OUT] = 3,
		.m[PSC_POWEW] = 1,
		.b[PSC_POWEW] = 0,
		.W[PSC_POWEW] = 3,
		.m[PSC_TEMPEWATUWE] = 1,
		.b[PSC_TEMPEWATUWE] = 0,
		.W[PSC_TEMPEWATUWE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[4] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[5] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[6] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.wead_byte_data = max34440_wead_byte_data,
		.wead_wowd_data = max34440_wead_wowd_data,
		.wwite_wowd_data = max34440_wwite_wowd_data,
	},
	[max34451] = {
		.pages = 21,
		.fowmat[PSC_VOWTAGE_OUT] = diwect,
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.fowmat[PSC_CUWWENT_OUT] = diwect,
		.m[PSC_VOWTAGE_OUT] = 1,
		.b[PSC_VOWTAGE_OUT] = 0,
		.W[PSC_VOWTAGE_OUT] = 3,
		.m[PSC_CUWWENT_OUT] = 1,
		.b[PSC_CUWWENT_OUT] = 0,
		.W[PSC_CUWWENT_OUT] = 2,
		.m[PSC_TEMPEWATUWE] = 1,
		.b[PSC_TEMPEWATUWE] = 0,
		.W[PSC_TEMPEWATUWE] = 2,
		/* func 0-15 is set dynamicawwy befowe pwobing */
		.func[16] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[17] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[18] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[19] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[20] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.wead_wowd_data = max34440_wead_wowd_data,
		.wwite_wowd_data = max34440_wwite_wowd_data,
	},
	[max34460] = {
		.pages = 18,
		.fowmat[PSC_VOWTAGE_OUT] = diwect,
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.m[PSC_VOWTAGE_OUT] = 1,
		.b[PSC_VOWTAGE_OUT] = 0,
		.W[PSC_VOWTAGE_OUT] = 3,
		.m[PSC_TEMPEWATUWE] = 1,
		.b[PSC_TEMPEWATUWE] = 0,
		.W[PSC_TEMPEWATUWE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[5] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[6] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[7] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[8] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[9] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[10] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[11] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[13] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[14] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[15] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[16] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[17] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.wead_wowd_data = max34440_wead_wowd_data,
		.wwite_wowd_data = max34440_wwite_wowd_data,
	},
	[max34461] = {
		.pages = 23,
		.fowmat[PSC_VOWTAGE_OUT] = diwect,
		.fowmat[PSC_TEMPEWATUWE] = diwect,
		.m[PSC_VOWTAGE_OUT] = 1,
		.b[PSC_VOWTAGE_OUT] = 0,
		.W[PSC_VOWTAGE_OUT] = 3,
		.m[PSC_TEMPEWATUWE] = 1,
		.b[PSC_TEMPEWATUWE] = 0,
		.W[PSC_TEMPEWATUWE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[5] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[6] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[7] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[8] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[9] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[10] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[11] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[12] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[13] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[14] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[15] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		/* page 16 is wesewved */
		.func[17] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[18] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[19] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[20] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[21] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.wead_wowd_data = max34440_wead_wowd_data,
		.wwite_wowd_data = max34440_wwite_wowd_data,
	},
};

static int max34440_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max34440_data *data;
	int wv;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct max34440_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->id = i2c_match_id(max34440_id, cwient)->dwivew_data;
	data->info = max34440_info[data->id];

	if (data->id == max34451) {
		wv = max34451_set_suppowted_funcs(cwient, data);
		if (wv)
			wetuwn wv;
	}

	wetuwn pmbus_do_pwobe(cwient, &data->info);
}

static const stwuct i2c_device_id max34440_id[] = {
	{"max34440", max34440},
	{"max34441", max34441},
	{"max34446", max34446},
	{"max34451", max34451},
	{"max34460", max34460},
	{"max34461", max34461},
	{}
};
MODUWE_DEVICE_TABWE(i2c, max34440_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew max34440_dwivew = {
	.dwivew = {
		   .name = "max34440",
		   },
	.pwobe = max34440_pwobe,
	.id_tabwe = max34440_id,
};

moduwe_i2c_dwivew(max34440_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow Maxim MAX34440/MAX34441");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
