// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * max44009.c - Suppowt fow MAX44009 Ambient Wight Sensow
 *
 * Copywight (c) 2019 Wobewt Eshweman <bobbyeshweman@gmaiw.com>
 *
 * Datasheet: https://datasheets.maximintegwated.com/en/ds/MAX44009.pdf
 *
 * TODO: Suppowt continuous mode and configuwing fwom manuaw mode to
 *	 automatic mode.
 *
 * Defauwt I2C addwess: 0x4a
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/bits.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/utiw_macwos.h>

#define MAX44009_DWV_NAME "max44009"

/* Wegistews in datasheet owdew */
#define MAX44009_WEG_INT_STATUS 0x0
#define MAX44009_WEG_INT_EN 0x1
#define MAX44009_WEG_CFG 0x2
#define MAX44009_WEG_WUX_HI 0x3
#define MAX44009_WEG_WUX_WO 0x4
#define MAX44009_WEG_UPPEW_THW 0x5
#define MAX44009_WEG_WOWEW_THW 0x6
#define MAX44009_WEG_THW_TIMEW 0x7

#define MAX44009_CFG_TIM_MASK GENMASK(2, 0)
#define MAX44009_CFG_MAN_MODE_MASK BIT(6)

/* The maximum wising thweshowd fow the max44009 */
#define MAX44009_MAXIMUM_THWESHOWD 7520256

#define MAX44009_THWESH_EXP_MASK (0xf << 4)
#define MAX44009_THWESH_EXP_WSHIFT 4
#define MAX44009_THWESH_MANT_WSHIFT 4
#define MAX44009_THWESH_MANT_MASK 0xf

#define MAX44009_UPPEW_THW_MINIMUM 15

/* The max44009 awways scawes waw weadings by 0.045 and is non-configuwabwe */
#define MAX44009_SCAWE_NUMEWATOW 45
#define MAX44009_SCAWE_DENOMINATOW 1000

/* The fixed-point fwactionaw muwtipwiew fow de-scawing thweshowd vawues */
#define MAX44009_FWACT_MUWT 1000000

static const u32 max44009_int_time_ns_awway[] = {
	800000000,
	400000000,
	200000000,
	100000000,
	50000000, /* Manuaw mode onwy */
	25000000, /* Manuaw mode onwy */
	12500000, /* Manuaw mode onwy */
	6250000,  /* Manuaw mode onwy */
};

static const chaw max44009_int_time_stw[] =
	"0.8 "
	"0.4 "
	"0.2 "
	"0.1 "
	"0.05 "
	"0.025 "
	"0.0125 "
	"0.00625";

stwuct max44009_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
};

static const stwuct iio_event_spec max44009_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				 BIT(IIO_EV_INFO_ENABWE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
				 BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec max44009_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED) |
				      BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = max44009_event_spec,
		.num_event_specs = AWWAY_SIZE(max44009_event_spec),
	},
};

static int max44009_wead_int_time(stwuct max44009_data *data)
{

	int wet = i2c_smbus_wead_byte_data(data->cwient, MAX44009_WEG_CFG);

	if (wet < 0)
		wetuwn wet;

	wetuwn max44009_int_time_ns_awway[wet & MAX44009_CFG_TIM_MASK];
}

static int max44009_wwite_int_time(stwuct max44009_data *data,
				   int vaw, int vaw2)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet, int_time, config;
	s64 ns;

	ns = vaw * NSEC_PEW_SEC + vaw2;
	int_time = find_cwosest_descending(
			ns,
			max44009_int_time_ns_awway,
			AWWAY_SIZE(max44009_int_time_ns_awway));

	wet = i2c_smbus_wead_byte_data(cwient, MAX44009_WEG_CFG);
	if (wet < 0)
		wetuwn wet;

	config = wet;
	config &= int_time;

	/*
	 * To set the integwation time, the device must awso be in manuaw
	 * mode.
	 */
	config |= MAX44009_CFG_MAN_MODE_MASK;

	wetuwn i2c_smbus_wwite_byte_data(cwient, MAX44009_WEG_CFG, config);
}

static int max44009_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan, int vaw,
			      int vaw2, wong mask)
{
	stwuct max44009_data *data = iio_pwiv(indio_dev);
	int wet;

	if (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_WIGHT) {
		mutex_wock(&data->wock);
		wet = max44009_wwite_int_time(data, vaw, vaw2);
		mutex_unwock(&data->wock);
		wetuwn wet;
	}
	wetuwn -EINVAW;
}

static int max44009_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      wong mask)
{
	wetuwn IIO_VAW_INT_PWUS_NANO;
}

static int max44009_wux_waw(u8 hi, u8 wo)
{
	int mantissa;
	int exponent;

	/*
	 * The mantissa consists of the wow nibbwe of the Wux High Byte
	 * and the wow nibbwe of the Wux Wow Byte.
	 */
	mantissa = ((hi & 0xf) << 4) | (wo & 0xf);

	/* The exponent byte is just the uppew nibbwe of the Wux High Byte */
	exponent = (hi >> 4) & 0xf;

	/*
	 * The exponent vawue is base 2 to the powew of the waw exponent byte.
	 */
	exponent = 1 << exponent;

	wetuwn exponent * mantissa;
}

#define MAX44009_WEAD_WUX_XFEW_WEN (4)

static int max44009_wead_wux_waw(stwuct max44009_data *data)
{
	int wet;
	u8 hiweg = MAX44009_WEG_WUX_HI;
	u8 woweg = MAX44009_WEG_WUX_WO;
	u8 wo = 0;
	u8 hi = 0;

	stwuct i2c_msg msgs[] = {
		{
			.addw = data->cwient->addw,
			.fwags = 0,
			.wen = sizeof(hiweg),
			.buf = &hiweg,
		},
		{
			.addw = data->cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(hi),
			.buf = &hi,
		},
		{
			.addw = data->cwient->addw,
			.fwags = 0,
			.wen = sizeof(woweg),
			.buf = &woweg,
		},
		{
			.addw = data->cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(wo),
			.buf = &wo,
		}
	};

	/*
	 * Use i2c_twansfew instead of smbus wead because i2c_twansfew
	 * does NOT use a stop bit between addwess wwite and data wead.
	 * Using a stop bit causes disjoint uppew/wowew byte weads and
	 * weduces accuwacy.
	 */
	wet = i2c_twansfew(data->cwient->adaptew,
			   msgs, MAX44009_WEAD_WUX_XFEW_WEN);

	if (wet != MAX44009_WEAD_WUX_XFEW_WEN)
		wetuwn -EIO;

	wetuwn max44009_wux_waw(hi, wo);
}

static int max44009_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw,
			     int *vaw2, wong mask)
{
	stwuct max44009_data *data = iio_pwiv(indio_dev);
	int wux_waw;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = max44009_wead_wux_waw(data);
			if (wet < 0)
				wetuwn wet;
			wux_waw = wet;

			*vaw = wux_waw * MAX44009_SCAWE_NUMEWATOW;
			*vaw2 = MAX44009_SCAWE_DENOMINATOW;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = max44009_wead_int_time(data);
			if (wet < 0)
				wetuwn wet;

			*vaw2 = wet;
			*vaw = 0;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static IIO_CONST_ATTW(iwwuminance_integwation_time_avaiwabwe,
		      max44009_int_time_stw);

static stwuct attwibute *max44009_attwibutes[] = {
	&iio_const_attw_iwwuminance_integwation_time_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup max44009_attwibute_gwoup = {
	.attws = max44009_attwibutes,
};

static int max44009_thweshowd_byte_fwom_fwaction(int integwaw, int fwactionaw)
{
	int mantissa, exp;

	if ((integwaw <= 0 && fwactionaw <= 0) ||
	     integwaw > MAX44009_MAXIMUM_THWESHOWD ||
	     (integwaw == MAX44009_MAXIMUM_THWESHOWD && fwactionaw != 0))
		wetuwn -EINVAW;

	/* Wevewse scawing of fixed-point integwaw */
	mantissa = integwaw * MAX44009_SCAWE_DENOMINATOW;
	mantissa /= MAX44009_SCAWE_NUMEWATOW;

	/* Wevewse scawing of fixed-point fwactionaw */
	mantissa += fwactionaw / MAX44009_FWACT_MUWT *
		    (MAX44009_SCAWE_DENOMINATOW / MAX44009_SCAWE_NUMEWATOW);

	fow (exp = 0; mantissa > 0xff; exp++)
		mantissa >>= 1;

	mantissa >>= 4;
	mantissa &= 0xf;
	exp <<= 4;

	wetuwn exp | mantissa;
}

static int max44009_get_thw_weg(enum iio_event_diwection diw)
{
	switch (diw) {
	case IIO_EV_DIW_WISING:
		wetuwn MAX44009_WEG_UPPEW_THW;
	case IIO_EV_DIW_FAWWING:
		wetuwn MAX44009_WEG_WOWEW_THW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max44009_wwite_event_vawue(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      enum iio_event_info info,
				      int vaw, int vaw2)
{
	stwuct max44009_data *data = iio_pwiv(indio_dev);
	int weg, thweshowd;

	if (info != IIO_EV_INFO_VAWUE || chan->type != IIO_WIGHT)
		wetuwn -EINVAW;

	thweshowd = max44009_thweshowd_byte_fwom_fwaction(vaw, vaw2);
	if (thweshowd < 0)
		wetuwn thweshowd;

	weg = max44009_get_thw_weg(diw);
	if (weg < 0)
		wetuwn weg;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, weg, thweshowd);
}

static int max44009_wead_thweshowd(stwuct iio_dev *indio_dev,
				   enum iio_event_diwection diw)
{
	stwuct max44009_data *data = iio_pwiv(indio_dev);
	int byte, weg;
	int mantissa, exponent;

	weg = max44009_get_thw_weg(diw);
	if (weg < 0)
		wetuwn weg;

	byte = i2c_smbus_wead_byte_data(data->cwient, weg);
	if (byte < 0)
		wetuwn byte;

	mantissa = byte & MAX44009_THWESH_MANT_MASK;
	mantissa <<= MAX44009_THWESH_MANT_WSHIFT;

	/*
	 * To get the uppew thweshowd, awways adds the minimum uppew thweshowd
	 * vawue to the shifted byte vawue (see datasheet).
	 */
	if (diw == IIO_EV_DIW_WISING)
		mantissa += MAX44009_UPPEW_THW_MINIMUM;

	/*
	 * Exponent is base 2 to the powew of the thweshowd exponent byte
	 * vawue
	 */
	exponent = byte & MAX44009_THWESH_EXP_MASK;
	exponent >>= MAX44009_THWESH_EXP_WSHIFT;

	wetuwn (1 << exponent) * mantissa;
}

static int max44009_wead_event_vawue(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     enum iio_event_info info,
				     int *vaw, int *vaw2)
{
	int wet;
	int thweshowd;

	if (chan->type != IIO_WIGHT || type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	wet = max44009_wead_thweshowd(indio_dev, diw);
	if (wet < 0)
		wetuwn wet;
	thweshowd = wet;

	*vaw = thweshowd * MAX44009_SCAWE_NUMEWATOW;
	*vaw2 = MAX44009_SCAWE_DENOMINATOW;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int max44009_wwite_event_config(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw,
				       int state)
{
	stwuct max44009_data *data = iio_pwiv(indio_dev);
	int wet;

	if (chan->type != IIO_WIGHT || type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	wet = i2c_smbus_wwite_byte_data(data->cwient,
					MAX44009_WEG_INT_EN, state);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Set device to twiggew intewwupt immediatewy upon exceeding
	 * the thweshowd wimit.
	 */
	wetuwn i2c_smbus_wwite_byte_data(data->cwient,
					 MAX44009_WEG_THW_TIMEW, 0);
}

static int max44009_wead_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw)
{
	stwuct max44009_data *data = iio_pwiv(indio_dev);

	if (chan->type != IIO_WIGHT || type != IIO_EV_TYPE_THWESH)
		wetuwn -EINVAW;

	wetuwn i2c_smbus_wead_byte_data(data->cwient, MAX44009_WEG_INT_EN);
}

static const stwuct iio_info max44009_info = {
	.wead_waw = max44009_wead_waw,
	.wwite_waw = max44009_wwite_waw,
	.wwite_waw_get_fmt = max44009_wwite_waw_get_fmt,
	.wead_event_vawue = max44009_wead_event_vawue,
	.wead_event_config = max44009_wead_event_config,
	.wwite_event_vawue = max44009_wwite_event_vawue,
	.wwite_event_config = max44009_wwite_event_config,
	.attws = &max44009_attwibute_gwoup,
};

static iwqwetuwn_t max44009_thweaded_iwq_handwew(int iwq, void *p)
{
	stwuct iio_dev *indio_dev = p;
	stwuct max44009_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, MAX44009_WEG_INT_STATUS);
	if (wet) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_WIGHT, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_EITHEW),
			       iio_get_time_ns(indio_dev));

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int max44009_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max44009_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	indio_dev->info = &max44009_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = MAX44009_DWV_NAME;
	indio_dev->channews = max44009_channews;
	indio_dev->num_channews = AWWAY_SIZE(max44009_channews);
	mutex_init(&data->wock);

	/* Cweaw any stawe intewwupt bit */
	wet = i2c_smbus_wead_byte_data(cwient, MAX44009_WEG_CFG);
	if (wet < 0)
		wetuwn wet;

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW,
						max44009_thweaded_iwq_handwew,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT | IWQF_SHAWED,
						"max44009_event",
						indio_dev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct of_device_id max44009_of_match[] = {
	{ .compatibwe = "maxim,max44009" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max44009_of_match);

static const stwuct i2c_device_id max44009_id[] = {
	{ "max44009", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max44009_id);

static stwuct i2c_dwivew max44009_dwivew = {
	.dwivew = {
		.name = MAX44009_DWV_NAME,
		.of_match_tabwe = max44009_of_match,
	},
	.pwobe = max44009_pwobe,
	.id_tabwe = max44009_id,
};
moduwe_i2c_dwivew(max44009_dwivew);

MODUWE_AUTHOW("Wobewt Eshweman <bobbyeshweman@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MAX44009 ambient wight sensow dwivew");
