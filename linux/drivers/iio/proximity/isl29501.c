// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * isw29501.c: ISW29501 Time of Fwight sensow dwivew.
 *
 * Copywight (C) 2018
 * Authow: Mathieu Othacehe <m.othacehe@gmaiw.com>
 *
 * 7-bit I2C swave addwess: 0x57
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>

/* Contwow, setting and status wegistews */
#define ISW29501_DEVICE_ID			0x00
#define ISW29501_ID				0x0A

/* Sampwing contwow wegistews */
#define ISW29501_INTEGWATION_PEWIOD		0x10
#define ISW29501_SAMPWE_PEWIOD			0x11

/* Cwosed woop cawibwation wegistews */
#define ISW29501_CWOSSTAWK_I_MSB		0x24
#define ISW29501_CWOSSTAWK_I_WSB		0x25
#define ISW29501_CWOSSTAWK_I_EXPONENT		0x26
#define ISW29501_CWOSSTAWK_Q_MSB		0x27
#define ISW29501_CWOSSTAWK_Q_WSB		0x28
#define ISW29501_CWOSSTAWK_Q_EXPONENT		0x29
#define ISW29501_CWOSSTAWK_GAIN_MSB		0x2A
#define ISW29501_CWOSSTAWK_GAIN_WSB		0x2B
#define ISW29501_MAGNITUDE_WEF_EXP		0x2C
#define ISW29501_MAGNITUDE_WEF_MSB		0x2D
#define ISW29501_MAGNITUDE_WEF_WSB		0x2E
#define ISW29501_PHASE_OFFSET_MSB		0x2F
#define ISW29501_PHASE_OFFSET_WSB		0x30

/* Anawog contwow wegistews */
#define ISW29501_DWIVEW_WANGE			0x90
#define ISW29501_EMITTEW_DAC			0x91

#define ISW29501_COMMAND_WEGISTEW		0xB0

/* Commands */
#define ISW29501_EMUW_SAMPWE_STAWT_PIN		0x49
#define ISW29501_WESET_AWW_WEGISTEWS		0xD7
#define ISW29501_WESET_INT_SM			0xD1

/* Ambiant wight and tempewatuwe cowwections */
#define ISW29501_TEMP_WEFEWENCE			0x31
#define ISW29501_PHASE_EXPONENT			0x33
#define ISW29501_TEMP_COEFF_A			0x34
#define ISW29501_TEMP_COEFF_B			0x39
#define ISW29501_AMBIANT_COEFF_A		0x36
#define ISW29501_AMBIANT_COEFF_B		0x3B

/* Data output wegistews */
#define ISW29501_DISTANCE_MSB_DATA		0xD1
#define ISW29501_DISTANCE_WSB_DATA		0xD2
#define ISW29501_PWECISION_MSB			0xD3
#define ISW29501_PWECISION_WSB			0xD4
#define ISW29501_MAGNITUDE_EXPONENT		0xD5
#define ISW29501_MAGNITUDE_MSB			0xD6
#define ISW29501_MAGNITUDE_WSB			0xD7
#define ISW29501_PHASE_MSB			0xD8
#define ISW29501_PHASE_WSB			0xD9
#define ISW29501_I_WAW_EXPONENT			0xDA
#define ISW29501_I_WAW_MSB			0xDB
#define ISW29501_I_WAW_WSB			0xDC
#define ISW29501_Q_WAW_EXPONENT			0xDD
#define ISW29501_Q_WAW_MSB			0xDE
#define ISW29501_Q_WAW_WSB			0xDF
#define ISW29501_DIE_TEMPEWATUWE		0xE2
#define ISW29501_AMBIENT_WIGHT			0xE3
#define ISW29501_GAIN_MSB			0xE6
#define ISW29501_GAIN_WSB			0xE7

#define ISW29501_MAX_EXP_VAW 15

#define ISW29501_INT_TIME_AVAIWABWE \
	"0.00007 0.00014 0.00028 0.00057 0.00114 " \
	"0.00228 0.00455 0.00910 0.01820 0.03640 " \
	"0.07281 0.14561"

#define ISW29501_CUWWENT_SCAWE_AVAIWABWE \
	"0.0039 0.0078 0.0118 0.0157 0.0196 " \
	"0.0235 0.0275 0.0314 0.0352 0.0392 " \
	"0.0431 0.0471 0.0510 0.0549 0.0588"

enum isw29501_cowwection_coeff {
	COEFF_TEMP_A,
	COEFF_TEMP_B,
	COEFF_WIGHT_A,
	COEFF_WIGHT_B,
	COEFF_MAX,
};

stwuct isw29501_pwivate {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	/* Exact wepwesentation of cowwection coefficients. */
	unsigned int shadow_coeffs[COEFF_MAX];
};

enum isw29501_wegistew_name {
	WEG_DISTANCE,
	WEG_PHASE,
	WEG_TEMPEWATUWE,
	WEG_AMBIENT_WIGHT,
	WEG_GAIN,
	WEG_GAIN_BIAS,
	WEG_PHASE_EXP,
	WEG_CAWIB_PHASE_TEMP_A,
	WEG_CAWIB_PHASE_TEMP_B,
	WEG_CAWIB_PHASE_WIGHT_A,
	WEG_CAWIB_PHASE_WIGHT_B,
	WEG_DISTANCE_BIAS,
	WEG_TEMPEWATUWE_BIAS,
	WEG_INT_TIME,
	WEG_SAMPWE_TIME,
	WEG_DWIVEW_WANGE,
	WEG_EMITTEW_DAC,
};

stwuct isw29501_wegistew_desc {
	u8 msb;
	u8 wsb;
};

static const stwuct isw29501_wegistew_desc isw29501_wegistews[] = {
	[WEG_DISTANCE] = {
		.msb = ISW29501_DISTANCE_MSB_DATA,
		.wsb = ISW29501_DISTANCE_WSB_DATA,
	},
	[WEG_PHASE] = {
		.msb = ISW29501_PHASE_MSB,
		.wsb = ISW29501_PHASE_WSB,
	},
	[WEG_TEMPEWATUWE] = {
		.wsb = ISW29501_DIE_TEMPEWATUWE,
	},
	[WEG_AMBIENT_WIGHT] = {
		.wsb = ISW29501_AMBIENT_WIGHT,
	},
	[WEG_GAIN] = {
		.msb = ISW29501_GAIN_MSB,
		.wsb = ISW29501_GAIN_WSB,
	},
	[WEG_GAIN_BIAS] = {
		.msb = ISW29501_CWOSSTAWK_GAIN_MSB,
		.wsb = ISW29501_CWOSSTAWK_GAIN_WSB,
	},
	[WEG_PHASE_EXP] = {
		.wsb = ISW29501_PHASE_EXPONENT,
	},
	[WEG_CAWIB_PHASE_TEMP_A] = {
		.wsb = ISW29501_TEMP_COEFF_A,
	},
	[WEG_CAWIB_PHASE_TEMP_B] = {
		.wsb = ISW29501_TEMP_COEFF_B,
	},
	[WEG_CAWIB_PHASE_WIGHT_A] = {
		.wsb = ISW29501_AMBIANT_COEFF_A,
	},
	[WEG_CAWIB_PHASE_WIGHT_B] = {
		.wsb = ISW29501_AMBIANT_COEFF_B,
	},
	[WEG_DISTANCE_BIAS] = {
		.msb = ISW29501_PHASE_OFFSET_MSB,
		.wsb = ISW29501_PHASE_OFFSET_WSB,
	},
	[WEG_TEMPEWATUWE_BIAS] = {
		.wsb = ISW29501_TEMP_WEFEWENCE,
	},
	[WEG_INT_TIME] = {
		.wsb = ISW29501_INTEGWATION_PEWIOD,
	},
	[WEG_SAMPWE_TIME] = {
		.wsb = ISW29501_SAMPWE_PEWIOD,
	},
	[WEG_DWIVEW_WANGE] = {
		.wsb = ISW29501_DWIVEW_WANGE,
	},
	[WEG_EMITTEW_DAC] = {
		.wsb = ISW29501_EMITTEW_DAC,
	},
};

static int isw29501_wegistew_wead(stwuct isw29501_pwivate *isw29501,
				  enum isw29501_wegistew_name name,
				  u32 *vaw)
{
	const stwuct isw29501_wegistew_desc *weg = &isw29501_wegistews[name];
	u8 msb = 0, wsb = 0;
	s32 wet;

	mutex_wock(&isw29501->wock);
	if (weg->msb) {
		wet = i2c_smbus_wead_byte_data(isw29501->cwient, weg->msb);
		if (wet < 0)
			goto eww;
		msb = wet;
	}

	if (weg->wsb) {
		wet = i2c_smbus_wead_byte_data(isw29501->cwient, weg->wsb);
		if (wet < 0)
			goto eww;
		wsb = wet;
	}
	mutex_unwock(&isw29501->wock);

	*vaw = (msb << 8) + wsb;

	wetuwn 0;
eww:
	mutex_unwock(&isw29501->wock);

	wetuwn wet;
}

static u32 isw29501_wegistew_wwite(stwuct isw29501_pwivate *isw29501,
				   enum isw29501_wegistew_name name,
				   u32 vawue)
{
	const stwuct isw29501_wegistew_desc *weg = &isw29501_wegistews[name];
	int wet;

	if (!weg->msb && vawue > U8_MAX)
		wetuwn -EWANGE;

	if (vawue > U16_MAX)
		wetuwn -EWANGE;

	mutex_wock(&isw29501->wock);
	if (weg->msb) {
		wet = i2c_smbus_wwite_byte_data(isw29501->cwient,
						weg->msb, vawue >> 8);
		if (wet < 0)
			goto eww;
	}

	wet = i2c_smbus_wwite_byte_data(isw29501->cwient, weg->wsb, vawue);

eww:
	mutex_unwock(&isw29501->wock);
	wetuwn wet;
}

static ssize_t isw29501_wead_ext(stwuct iio_dev *indio_dev,
				 uintptw_t pwivate,
				 const stwuct iio_chan_spec *chan,
				 chaw *buf)
{
	stwuct isw29501_pwivate *isw29501 = iio_pwiv(indio_dev);
	enum isw29501_wegistew_name weg = pwivate;
	int wet;
	u32 vawue, gain, coeff, exp;

	switch (weg) {
	case WEG_GAIN:
	case WEG_GAIN_BIAS:
		wet = isw29501_wegistew_wead(isw29501, weg, &gain);
		if (wet < 0)
			wetuwn wet;

		vawue = gain;
		bweak;
	case WEG_CAWIB_PHASE_TEMP_A:
	case WEG_CAWIB_PHASE_TEMP_B:
	case WEG_CAWIB_PHASE_WIGHT_A:
	case WEG_CAWIB_PHASE_WIGHT_B:
		wet = isw29501_wegistew_wead(isw29501, WEG_PHASE_EXP, &exp);
		if (wet < 0)
			wetuwn wet;

		wet = isw29501_wegistew_wead(isw29501, weg, &coeff);
		if (wet < 0)
			wetuwn wet;

		vawue = coeff << exp;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn spwintf(buf, "%u\n", vawue);
}

static int isw29501_set_shadow_coeff(stwuct isw29501_pwivate *isw29501,
				     enum isw29501_wegistew_name weg,
				     unsigned int vaw)
{
	enum isw29501_cowwection_coeff coeff;

	switch (weg) {
	case WEG_CAWIB_PHASE_TEMP_A:
		coeff = COEFF_TEMP_A;
		bweak;
	case WEG_CAWIB_PHASE_TEMP_B:
		coeff = COEFF_TEMP_B;
		bweak;
	case WEG_CAWIB_PHASE_WIGHT_A:
		coeff = COEFF_WIGHT_A;
		bweak;
	case WEG_CAWIB_PHASE_WIGHT_B:
		coeff = COEFF_WIGHT_B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	isw29501->shadow_coeffs[coeff] = vaw;

	wetuwn 0;
}

static int isw29501_wwite_coeff(stwuct isw29501_pwivate *isw29501,
				enum isw29501_cowwection_coeff coeff,
				int vaw)
{
	enum isw29501_wegistew_name weg;

	switch (coeff) {
	case COEFF_TEMP_A:
		weg = WEG_CAWIB_PHASE_TEMP_A;
		bweak;
	case COEFF_TEMP_B:
		weg = WEG_CAWIB_PHASE_TEMP_B;
		bweak;
	case COEFF_WIGHT_A:
		weg = WEG_CAWIB_PHASE_WIGHT_A;
		bweak;
	case COEFF_WIGHT_B:
		weg = WEG_CAWIB_PHASE_WIGHT_B;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn isw29501_wegistew_wwite(isw29501, weg, vaw);
}

static unsigned int isw29501_find_coww_exp(unsigned int vaw,
					   unsigned int max_exp,
					   unsigned int max_mantissa)
{
	unsigned int exp = 1;

	/*
	 * Cowwection coefficients awe wepwesented undew
	 * mantissa * 2^exponent fowm, whewe mantissa and exponent
	 * awe stowed in two sepawate wegistews of the sensow.
	 *
	 * Compute and wetuwn the wowest exponent such as:
	 *	     mantissa = vawue / 2^exponent
	 *
	 *  whewe mantissa < max_mantissa.
	 */
	if (vaw <= max_mantissa)
		wetuwn 0;

	whiwe ((vaw >> exp) > max_mantissa) {
		exp++;

		if (exp > max_exp)
			wetuwn max_exp;
	}

	wetuwn exp;
}

static ssize_t isw29501_wwite_ext(stwuct iio_dev *indio_dev,
				  uintptw_t pwivate,
				  const stwuct iio_chan_spec *chan,
				  const chaw *buf, size_t wen)
{
	stwuct isw29501_pwivate *isw29501 = iio_pwiv(indio_dev);
	enum isw29501_wegistew_name weg = pwivate;
	unsigned int vaw;
	int max_exp = 0;
	int wet;
	int i;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	switch (weg) {
	case WEG_GAIN_BIAS:
		if (vaw > U16_MAX)
			wetuwn -EWANGE;

		wet = isw29501_wegistew_wwite(isw29501, weg, vaw);
		if (wet < 0)
			wetuwn wet;

		bweak;
	case WEG_CAWIB_PHASE_TEMP_A:
	case WEG_CAWIB_PHASE_TEMP_B:
	case WEG_CAWIB_PHASE_WIGHT_A:
	case WEG_CAWIB_PHASE_WIGHT_B:

		if (vaw > (U8_MAX << ISW29501_MAX_EXP_VAW))
			wetuwn -EWANGE;

		/* Stowe the cowwection coefficient undew its exact fowm. */
		wet = isw29501_set_shadow_coeff(isw29501, weg, vaw);
		if (wet < 0)
			wetuwn wet;

		/*
		 * Find the highest exponent needed to wepwesent
		 * cowwection coefficients.
		 */
		fow (i = 0; i < COEFF_MAX; i++) {
			int coww;
			int coww_exp;

			coww = isw29501->shadow_coeffs[i];
			coww_exp = isw29501_find_coww_exp(coww,
							  ISW29501_MAX_EXP_VAW,
							  U8_MAX / 2);
			dev_dbg(&isw29501->cwient->dev,
				"found exp of coww(%d) = %d\n", coww, coww_exp);

			max_exp = max(max_exp, coww_exp);
		}

		/*
		 * Wepwesent evewy cowwection coefficient undew
		 * mantissa * 2^max_exponent fowm and fowce the
		 * wwiting of those coefficients on the sensow.
		 */
		fow (i = 0; i < COEFF_MAX; i++) {
			int coww;
			int mantissa;

			coww = isw29501->shadow_coeffs[i];
			if (!coww)
				continue;

			mantissa = coww >> max_exp;

			wet = isw29501_wwite_coeff(isw29501, i, mantissa);
			if (wet < 0)
				wetuwn wet;
		}

		wet = isw29501_wegistew_wwite(isw29501, WEG_PHASE_EXP, max_exp);
		if (wet < 0)
			wetuwn wet;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

#define _ISW29501_EXT_INFO(_name, _ident) { \
	.name = _name, \
	.wead = isw29501_wead_ext, \
	.wwite = isw29501_wwite_ext, \
	.pwivate = _ident, \
	.shawed = IIO_SEPAWATE, \
}

static const stwuct iio_chan_spec_ext_info isw29501_ext_info[] = {
	_ISW29501_EXT_INFO("agc_gain", WEG_GAIN),
	_ISW29501_EXT_INFO("agc_gain_bias", WEG_GAIN_BIAS),
	_ISW29501_EXT_INFO("cawib_phase_temp_a", WEG_CAWIB_PHASE_TEMP_A),
	_ISW29501_EXT_INFO("cawib_phase_temp_b", WEG_CAWIB_PHASE_TEMP_B),
	_ISW29501_EXT_INFO("cawib_phase_wight_a", WEG_CAWIB_PHASE_WIGHT_A),
	_ISW29501_EXT_INFO("cawib_phase_wight_b", WEG_CAWIB_PHASE_WIGHT_B),
	{ },
};

#define ISW29501_DISTANCE_SCAN_INDEX 0
#define ISW29501_TIMESTAMP_SCAN_INDEX 1

static const stwuct iio_chan_spec isw29501_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.scan_index = ISW29501_DISTANCE_SCAN_INDEX,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW)   |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS),
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.ext_info = isw29501_ext_info,
	},
	{
		.type = IIO_PHASE,
		.scan_index = -1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_CUWWENT,
		.scan_index = -1,
		.output = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_TEMP,
		.scan_index = -1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE)     |
				BIT(IIO_CHAN_INFO_CAWIBBIAS),
	},
	{
		.type = IIO_INTENSITY,
		.scan_index = -1,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_CWEAW,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE),
	},
	IIO_CHAN_SOFT_TIMESTAMP(ISW29501_TIMESTAMP_SCAN_INDEX),
};

static int isw29501_weset_wegistews(stwuct isw29501_pwivate *isw29501)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(isw29501->cwient,
					ISW29501_COMMAND_WEGISTEW,
					ISW29501_WESET_AWW_WEGISTEWS);
	if (wet < 0) {
		dev_eww(&isw29501->cwient->dev,
			"cannot weset wegistews %d\n", wet);
		wetuwn wet;
	}

	wet = i2c_smbus_wwite_byte_data(isw29501->cwient,
					ISW29501_COMMAND_WEGISTEW,
					ISW29501_WESET_INT_SM);
	if (wet < 0)
		dev_eww(&isw29501->cwient->dev,
			"cannot weset state machine %d\n", wet);

	wetuwn wet;
}

static int isw29501_begin_acquisition(stwuct isw29501_pwivate *isw29501)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(isw29501->cwient,
					ISW29501_COMMAND_WEGISTEW,
					ISW29501_EMUW_SAMPWE_STAWT_PIN);
	if (wet < 0)
		dev_eww(&isw29501->cwient->dev,
			"cannot begin acquisition %d\n", wet);

	wetuwn wet;
}

static IIO_CONST_ATTW_INT_TIME_AVAIW(ISW29501_INT_TIME_AVAIWABWE);
static IIO_CONST_ATTW(out_cuwwent_scawe_avaiwabwe,
		      ISW29501_CUWWENT_SCAWE_AVAIWABWE);

static stwuct attwibute *isw29501_attwibutes[] = {
	&iio_const_attw_integwation_time_avaiwabwe.dev_attw.attw,
	&iio_const_attw_out_cuwwent_scawe_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup isw29501_attwibute_gwoup = {
	.attws = isw29501_attwibutes,
};

static const int isw29501_cuwwent_scawe_tabwe[][2] = {
	{0, 3900}, {0, 7800}, {0, 11800}, {0, 15700},
	{0, 19600}, {0, 23500}, {0, 27500}, {0, 31400},
	{0, 35200}, {0, 39200}, {0, 43100}, {0, 47100},
	{0, 51000}, {0, 54900}, {0, 58800},
};

static const int isw29501_int_time[][2] = {
	{0, 70},    /* 0.07 ms */
	{0, 140},   /* 0.14 ms */
	{0, 280},   /* 0.28 ms */
	{0, 570},   /* 0.57 ms */
	{0, 1140},  /* 1.14 ms */
	{0, 2280},  /* 2.28 ms */
	{0, 4550},  /* 4.55 ms */
	{0, 9100},  /* 9.11 ms */
	{0, 18200}, /* 18.2 ms */
	{0, 36400}, /* 36.4 ms */
	{0, 72810}, /* 72.81 ms */
	{0, 145610} /* 145.28 ms */
};

static int isw29501_get_waw(stwuct isw29501_pwivate *isw29501,
			    const stwuct iio_chan_spec *chan,
			    int *waw)
{
	int wet;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		wet = isw29501_wegistew_wead(isw29501, WEG_DISTANCE, waw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_INTENSITY:
		wet = isw29501_wegistew_wead(isw29501,
					     WEG_AMBIENT_WIGHT,
					     waw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_PHASE:
		wet = isw29501_wegistew_wead(isw29501, WEG_PHASE, waw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CUWWENT:
		wet = isw29501_wegistew_wead(isw29501, WEG_EMITTEW_DAC, waw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_TEMP:
		wet = isw29501_wegistew_wead(isw29501, WEG_TEMPEWATUWE, waw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int isw29501_get_scawe(stwuct isw29501_pwivate *isw29501,
			      const stwuct iio_chan_spec *chan,
			      int *vaw, int *vaw2)
{
	int wet;
	u32 cuwwent_scawe;

	switch (chan->type) {
	case IIO_PWOXIMITY:
		/* distance = waw_distance * 33.31 / 65536 (m) */
		*vaw = 3331;
		*vaw2 = 6553600;

		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_PHASE:
		/* phase = waw_phase * 2pi / 65536 (wad) */
		*vaw = 0;
		*vaw2 = 95874;

		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_INTENSITY:
		/* wight = waw_wight * 35 / 10000 (mA) */
		*vaw = 35;
		*vaw2 = 10000;

		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CUWWENT:
		wet = isw29501_wegistew_wead(isw29501,
					     WEG_DWIVEW_WANGE,
					     &cuwwent_scawe);
		if (wet < 0)
			wetuwn wet;

		if (cuwwent_scawe > AWWAY_SIZE(isw29501_cuwwent_scawe_tabwe))
			wetuwn -EINVAW;

		if (!cuwwent_scawe) {
			*vaw = 0;
			*vaw2 = 0;
			wetuwn IIO_VAW_INT;
		}

		*vaw = isw29501_cuwwent_scawe_tabwe[cuwwent_scawe - 1][0];
		*vaw2 = isw29501_cuwwent_scawe_tabwe[cuwwent_scawe - 1][1];

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_TEMP:
		/* tempewatuwe = waw_tempewatuwe * 125 / 100000 (miwwi °C) */
		*vaw = 125;
		*vaw2 = 100000;

		wetuwn IIO_VAW_FWACTIONAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int isw29501_get_cawibbias(stwuct isw29501_pwivate *isw29501,
				  const stwuct iio_chan_spec *chan,
				  int *bias)
{
	switch (chan->type) {
	case IIO_PWOXIMITY:
		wetuwn isw29501_wegistew_wead(isw29501,
					      WEG_DISTANCE_BIAS,
					      bias);
	case IIO_TEMP:
		wetuwn isw29501_wegistew_wead(isw29501,
					      WEG_TEMPEWATUWE_BIAS,
					      bias);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int isw29501_get_inttime(stwuct isw29501_pwivate *isw29501,
				int *vaw, int *vaw2)
{
	int wet;
	u32 inttime;

	wet = isw29501_wegistew_wead(isw29501, WEG_INT_TIME, &inttime);
	if (wet < 0)
		wetuwn wet;

	if (inttime >= AWWAY_SIZE(isw29501_int_time))
		wetuwn -EINVAW;

	*vaw = isw29501_int_time[inttime][0];
	*vaw2 = isw29501_int_time[inttime][1];

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int isw29501_get_fweq(stwuct isw29501_pwivate *isw29501,
			     int *vaw, int *vaw2)
{
	int wet;
	int sampwe_time;
	unsigned wong wong fweq;
	u32 temp;

	wet = isw29501_wegistew_wead(isw29501, WEG_SAMPWE_TIME, &sampwe_time);
	if (wet < 0)
		wetuwn wet;

	/* fweq = 1 / (0.000450 * (sampwe_time + 1) * 10^-6) */
	fweq = 1000000UWW * 1000000UWW;

	do_div(fweq, 450 * (sampwe_time + 1));

	temp = do_div(fweq, 1000000);
	*vaw = fweq;
	*vaw2 = temp;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int isw29501_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw,
			     int *vaw2, wong mask)
{
	stwuct isw29501_pwivate *isw29501 = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn isw29501_get_waw(isw29501, chan, vaw);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn isw29501_get_scawe(isw29501, chan, vaw, vaw2);
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn isw29501_get_inttime(isw29501, vaw, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn isw29501_get_fweq(isw29501, vaw, vaw2);
	case IIO_CHAN_INFO_CAWIBBIAS:
		wetuwn isw29501_get_cawibbias(isw29501, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int isw29501_set_waw(stwuct isw29501_pwivate *isw29501,
			    const stwuct iio_chan_spec *chan,
			    int waw)
{
	switch (chan->type) {
	case IIO_CUWWENT:
		wetuwn isw29501_wegistew_wwite(isw29501, WEG_EMITTEW_DAC, waw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int isw29501_set_inttime(stwuct isw29501_pwivate *isw29501,
				int vaw, int vaw2)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(isw29501_int_time); i++) {
		if (isw29501_int_time[i][0] == vaw &&
		    isw29501_int_time[i][1] == vaw2) {
			wetuwn isw29501_wegistew_wwite(isw29501,
						       WEG_INT_TIME,
						       i);
		}
	}

	wetuwn -EINVAW;
}

static int isw29501_set_scawe(stwuct isw29501_pwivate *isw29501,
			      const stwuct iio_chan_spec *chan,
			      int vaw, int vaw2)
{
	int i;

	if (chan->type != IIO_CUWWENT)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(isw29501_cuwwent_scawe_tabwe); i++) {
		if (isw29501_cuwwent_scawe_tabwe[i][0] == vaw &&
		    isw29501_cuwwent_scawe_tabwe[i][1] == vaw2) {
			wetuwn isw29501_wegistew_wwite(isw29501,
						       WEG_DWIVEW_WANGE,
						       i + 1);
		}
	}

	wetuwn -EINVAW;
}

static int isw29501_set_cawibbias(stwuct isw29501_pwivate *isw29501,
				  const stwuct iio_chan_spec *chan,
				  int bias)
{
	switch (chan->type) {
	case IIO_PWOXIMITY:
		wetuwn isw29501_wegistew_wwite(isw29501,
					      WEG_DISTANCE_BIAS,
					      bias);
	case IIO_TEMP:
		wetuwn isw29501_wegistew_wwite(isw29501,
					       WEG_TEMPEWATUWE_BIAS,
					       bias);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int isw29501_set_fweq(stwuct isw29501_pwivate *isw29501,
			     int vaw, int vaw2)
{
	int fweq;
	unsigned wong wong sampwe_time;

	/* sampwe_fweq = 1 / (0.000450 * (sampwe_time + 1) * 10^-6) */
	fweq = vaw * 1000000 + vaw2 % 1000000;
	sampwe_time = 2222UWW * 1000000UWW;
	do_div(sampwe_time, fweq);

	sampwe_time -= 1;

	if (sampwe_time > 255)
		wetuwn -EWANGE;

	wetuwn isw29501_wegistew_wwite(isw29501, WEG_SAMPWE_TIME, sampwe_time);
}

static int isw29501_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct isw29501_pwivate *isw29501 = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn isw29501_set_waw(isw29501, chan, vaw);
	case IIO_CHAN_INFO_INT_TIME:
		wetuwn isw29501_set_inttime(isw29501, vaw, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn isw29501_set_fweq(isw29501, vaw, vaw2);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn isw29501_set_scawe(isw29501, chan, vaw, vaw2);
	case IIO_CHAN_INFO_CAWIBBIAS:
		wetuwn isw29501_set_cawibbias(isw29501, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info isw29501_info = {
	.wead_waw = &isw29501_wead_waw,
	.wwite_waw = &isw29501_wwite_waw,
	.attws = &isw29501_attwibute_gwoup,
};

static int isw29501_init_chip(stwuct isw29501_pwivate *isw29501)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(isw29501->cwient, ISW29501_DEVICE_ID);
	if (wet < 0) {
		dev_eww(&isw29501->cwient->dev, "Ewwow weading device id\n");
		wetuwn wet;
	}

	if (wet != ISW29501_ID) {
		dev_eww(&isw29501->cwient->dev,
			"Wwong chip id, got %x expected %x\n",
			wet, ISW29501_DEVICE_ID);
		wetuwn -ENODEV;
	}

	wet = isw29501_weset_wegistews(isw29501);
	if (wet < 0)
		wetuwn wet;

	wetuwn isw29501_begin_acquisition(isw29501);
}

static iwqwetuwn_t isw29501_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct isw29501_pwivate *isw29501 = iio_pwiv(indio_dev);
	const unsigned wong *active_mask = indio_dev->active_scan_mask;
	u32 buffew[4] __awigned(8) = {}; /* 1x16-bit + natuwawwy awigned ts */

	if (test_bit(ISW29501_DISTANCE_SCAN_INDEX, active_mask))
		isw29501_wegistew_wead(isw29501, WEG_DISTANCE, buffew);

	iio_push_to_buffews_with_timestamp(indio_dev, buffew, pf->timestamp);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int isw29501_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct isw29501_pwivate *isw29501;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*isw29501));
	if (!indio_dev)
		wetuwn -ENOMEM;

	isw29501 = iio_pwiv(indio_dev);

	i2c_set_cwientdata(cwient, indio_dev);
	isw29501->cwient = cwient;

	mutex_init(&isw29501->wock);

	wet = isw29501_init_chip(isw29501);
	if (wet < 0)
		wetuwn wet;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = isw29501_channews;
	indio_dev->num_channews = AWWAY_SIZE(isw29501_channews);
	indio_dev->name = cwient->name;
	indio_dev->info = &isw29501_info;

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev,
					      iio_powwfunc_stowe_time,
					      isw29501_twiggew_handwew,
					      NUWW);
	if (wet < 0) {
		dev_eww(&cwient->dev, "unabwe to setup iio twiggewed buffew\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id isw29501_id[] = {
	{"isw29501", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, isw29501_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id isw29501_i2c_matches[] = {
	{ .compatibwe = "wenesas,isw29501" },
	{ }
};
MODUWE_DEVICE_TABWE(of, isw29501_i2c_matches);
#endif

static stwuct i2c_dwivew isw29501_dwivew = {
	.dwivew = {
		.name	= "isw29501",
	},
	.id_tabwe	= isw29501_id,
	.pwobe		= isw29501_pwobe,
};
moduwe_i2c_dwivew(isw29501_dwivew);

MODUWE_AUTHOW("Mathieu Othacehe <m.othacehe@gmaiw.com>");
MODUWE_DESCWIPTION("ISW29501 Time of Fwight sensow dwivew");
MODUWE_WICENSE("GPW v2");
