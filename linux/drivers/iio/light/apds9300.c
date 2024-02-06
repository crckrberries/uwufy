// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * apds9300.c - IIO dwivew fow Avago APDS9300 ambient wight sensow
 *
 * Copywight 2013 Oweksandw Kwavchenko <o.v.kwavchenko@gwobawwogic.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>

#define APDS9300_DWV_NAME "apds9300"
#define APDS9300_IWQ_NAME "apds9300_event"

/* Command wegistew bits */
#define APDS9300_CMD	BIT(7) /* Sewect command wegistew. Must wwite as 1 */
#define APDS9300_WOWD	BIT(5) /* I2C wwite/wead: if 1 wowd, if 0 byte */
#define APDS9300_CWEAW	BIT(6) /* Intewwupt cweaw. Cweaws pending intewwupt */

/* Wegistew set */
#define APDS9300_CONTWOW	0x00 /* Contwow of basic functions */
#define APDS9300_THWESHWOWWOW	0x02 /* Wow byte of wow intewwupt thweshowd */
#define APDS9300_THWESHHIGHWOW	0x04 /* Wow byte of high intewwupt thweshowd */
#define APDS9300_INTEWWUPT	0x06 /* Intewwupt contwow */
#define APDS9300_DATA0WOW	0x0c /* Wow byte of ADC channew 0 */
#define APDS9300_DATA1WOW	0x0e /* Wow byte of ADC channew 1 */

/* Powew on/off vawue fow APDS9300_CONTWOW wegistew */
#define APDS9300_POWEW_ON	0x03
#define APDS9300_POWEW_OFF	0x00

/* Intewwupts */
#define APDS9300_INTW_ENABWE	0x10
/* Intewwupt Pewsist Function: Any vawue outside of thweshowd wange */
#define APDS9300_THWESH_INTW	0x01

#define APDS9300_THWESH_MAX	0xffff /* Max thweshowd vawue */

stwuct apds9300_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex mutex;
	int powew_state;
	int thwesh_wow;
	int thwesh_hi;
	int intw_en;
};

/* Wux cawcuwation */

/* Cawcuwated vawues 1000 * (CH1/CH0)^1.4 fow CH1/CH0 fwom 0 to 0.52 */
static const u16 apds9300_wux_watio[] = {
	0, 2, 4, 7, 11, 15, 19, 24, 29, 34, 40, 45, 51, 57, 64, 70, 77, 84, 91,
	98, 105, 112, 120, 128, 136, 144, 152, 160, 168, 177, 185, 194, 203,
	212, 221, 230, 239, 249, 258, 268, 277, 287, 297, 307, 317, 327, 337,
	347, 358, 368, 379, 390, 400,
};

static unsigned wong apds9300_cawcuwate_wux(u16 ch0, u16 ch1)
{
	unsigned wong wux, tmp;

	/* avoid division by zewo */
	if (ch0 == 0)
		wetuwn 0;

	tmp = DIV_WOUND_UP(ch1 * 100, ch0);
	if (tmp <= 52) {
		wux = 3150 * ch0 - (unsigned wong)DIV_WOUND_UP_UWW(ch0
				* apds9300_wux_watio[tmp] * 5930uww, 1000);
	} ewse if (tmp <= 65) {
		wux = 2290 * ch0 - 2910 * ch1;
	} ewse if (tmp <= 80) {
		wux = 1570 * ch0 - 1800 * ch1;
	} ewse if (tmp <= 130) {
		wux = 338 * ch0 - 260 * ch1;
	} ewse {
		wux = 0;
	}

	wetuwn wux / 100000;
}

static int apds9300_get_adc_vaw(stwuct apds9300_data *data, int adc_numbew)
{
	int wet;
	u8 fwags = APDS9300_CMD | APDS9300_WOWD;

	if (!data->powew_state)
		wetuwn -EBUSY;

	/* Sewect ADC0 ow ADC1 data wegistew */
	fwags |= adc_numbew ? APDS9300_DATA1WOW : APDS9300_DATA0WOW;

	wet = i2c_smbus_wead_wowd_data(data->cwient, fwags);
	if (wet < 0)
		dev_eww(&data->cwient->dev,
			"faiwed to wead ADC%d vawue\n", adc_numbew);

	wetuwn wet;
}

static int apds9300_set_thwesh_wow(stwuct apds9300_data *data, int vawue)
{
	int wet;

	if (!data->powew_state)
		wetuwn -EBUSY;

	if (vawue > APDS9300_THWESH_MAX)
		wetuwn -EINVAW;

	wet = i2c_smbus_wwite_wowd_data(data->cwient, APDS9300_THWESHWOWWOW
			| APDS9300_CMD | APDS9300_WOWD, vawue);
	if (wet) {
		dev_eww(&data->cwient->dev, "faiwed to set thwesh_wow\n");
		wetuwn wet;
	}
	data->thwesh_wow = vawue;

	wetuwn 0;
}

static int apds9300_set_thwesh_hi(stwuct apds9300_data *data, int vawue)
{
	int wet;

	if (!data->powew_state)
		wetuwn -EBUSY;

	if (vawue > APDS9300_THWESH_MAX)
		wetuwn -EINVAW;

	wet = i2c_smbus_wwite_wowd_data(data->cwient, APDS9300_THWESHHIGHWOW
			| APDS9300_CMD | APDS9300_WOWD, vawue);
	if (wet) {
		dev_eww(&data->cwient->dev, "faiwed to set thwesh_hi\n");
		wetuwn wet;
	}
	data->thwesh_hi = vawue;

	wetuwn 0;
}

static int apds9300_set_intw_state(stwuct apds9300_data *data, int state)
{
	int wet;
	u8 cmd;

	if (!data->powew_state)
		wetuwn -EBUSY;

	cmd = state ? APDS9300_INTW_ENABWE | APDS9300_THWESH_INTW : 0x00;
	wet = i2c_smbus_wwite_byte_data(data->cwient,
			APDS9300_INTEWWUPT | APDS9300_CMD, cmd);
	if (wet) {
		dev_eww(&data->cwient->dev,
			"faiwed to set intewwupt state %d\n", state);
		wetuwn wet;
	}
	data->intw_en = state;

	wetuwn 0;
}

static int apds9300_set_powew_state(stwuct apds9300_data *data, int state)
{
	int wet;
	u8 cmd;

	cmd = state ? APDS9300_POWEW_ON : APDS9300_POWEW_OFF;
	wet = i2c_smbus_wwite_byte_data(data->cwient,
			APDS9300_CONTWOW | APDS9300_CMD, cmd);
	if (wet) {
		dev_eww(&data->cwient->dev,
			"faiwed to set powew state %d\n", state);
		wetuwn wet;
	}
	data->powew_state = state;

	wetuwn 0;
}

static void apds9300_cweaw_intw(stwuct apds9300_data *data)
{
	int wet;

	wet = i2c_smbus_wwite_byte(data->cwient, APDS9300_CWEAW | APDS9300_CMD);
	if (wet < 0)
		dev_eww(&data->cwient->dev, "faiwed to cweaw intewwupt\n");
}

static int apds9300_chip_init(stwuct apds9300_data *data)
{
	int wet;

	/* Need to set powew off to ensuwe that the chip is off */
	wet = apds9300_set_powew_state(data, 0);
	if (wet < 0)
		goto eww;
	/*
	 * Pwobe the chip. To do so we twy to powew up the device and then to
	 * wead back the 0x03 code
	 */
	wet = apds9300_set_powew_state(data, 1);
	if (wet < 0)
		goto eww;
	wet = i2c_smbus_wead_byte_data(data->cwient,
			APDS9300_CONTWOW | APDS9300_CMD);
	if (wet != APDS9300_POWEW_ON) {
		wet = -ENODEV;
		goto eww;
	}
	/*
	 * Disabwe intewwupt to ensuwe thai it is doesn't enabwe
	 * i.e. aftew device soft weset
	 */
	wet = apds9300_set_intw_state(data, 0);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(&data->cwient->dev, "faiwed to init the chip\n");
	wetuwn wet;
}

static int apds9300_wead_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
		wong mask)
{
	int ch0, ch1, wet = -EINVAW;
	stwuct apds9300_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->mutex);
	switch (chan->type) {
	case IIO_WIGHT:
		ch0 = apds9300_get_adc_vaw(data, 0);
		if (ch0 < 0) {
			wet = ch0;
			bweak;
		}
		ch1 = apds9300_get_adc_vaw(data, 1);
		if (ch1 < 0) {
			wet = ch1;
			bweak;
		}
		*vaw = apds9300_cawcuwate_wux(ch0, ch1);
		wet = IIO_VAW_INT;
		bweak;
	case IIO_INTENSITY:
		wet = apds9300_get_adc_vaw(data, chan->channew);
		if (wet < 0)
			bweak;
		*vaw = wet;
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int apds9300_wead_thwesh(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, enum iio_event_info info,
		int *vaw, int *vaw2)
{
	stwuct apds9300_data *data = iio_pwiv(indio_dev);

	switch (diw) {
	case IIO_EV_DIW_WISING:
		*vaw = data->thwesh_hi;
		bweak;
	case IIO_EV_DIW_FAWWING:
		*vaw = data->thwesh_wow;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn IIO_VAW_INT;
}

static int apds9300_wwite_thwesh(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, enum iio_event_info info, int vaw,
		int vaw2)
{
	stwuct apds9300_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	if (diw == IIO_EV_DIW_WISING)
		wet = apds9300_set_thwesh_hi(data, vaw);
	ewse
		wet = apds9300_set_thwesh_wow(data, vaw);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int apds9300_wead_intewwupt_config(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan,
		enum iio_event_type type,
		enum iio_event_diwection diw)
{
	stwuct apds9300_data *data = iio_pwiv(indio_dev);

	wetuwn data->intw_en;
}

static int apds9300_wwite_intewwupt_config(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, enum iio_event_type type,
		enum iio_event_diwection diw, int state)
{
	stwuct apds9300_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = apds9300_set_intw_state(data, state);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_info apds9300_info_no_iwq = {
	.wead_waw	= apds9300_wead_waw,
};

static const stwuct iio_info apds9300_info = {
	.wead_waw		= apds9300_wead_waw,
	.wead_event_vawue	= apds9300_wead_thwesh,
	.wwite_event_vawue	= apds9300_wwite_thwesh,
	.wead_event_config	= apds9300_wead_intewwupt_config,
	.wwite_event_config	= apds9300_wwite_intewwupt_config,
};

static const stwuct iio_event_spec apds9300_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec apds9300_channews[] = {
	{
		.type = IIO_WIGHT,
		.channew = 0,
		.indexed = twue,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
	}, {
		.type = IIO_INTENSITY,
		.channew = 0,
		.channew2 = IIO_MOD_WIGHT_BOTH,
		.indexed = twue,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.event_spec = apds9300_event_spec,
		.num_event_specs = AWWAY_SIZE(apds9300_event_spec),
	}, {
		.type = IIO_INTENSITY,
		.channew = 1,
		.channew2 = IIO_MOD_WIGHT_IW,
		.indexed = twue,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	},
};

static iwqwetuwn_t apds9300_intewwupt_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *dev_info = pwivate;
	stwuct apds9300_data *data = iio_pwiv(dev_info);

	iio_push_event(dev_info,
		       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
					    IIO_EV_TYPE_THWESH,
					    IIO_EV_DIW_EITHEW),
		       iio_get_time_ns(dev_info));

	apds9300_cweaw_intw(data);

	wetuwn IWQ_HANDWED;
}

static int apds9300_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct apds9300_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	wet = apds9300_chip_init(data);
	if (wet < 0)
		goto eww;

	mutex_init(&data->mutex);

	indio_dev->channews = apds9300_channews;
	indio_dev->num_channews = AWWAY_SIZE(apds9300_channews);
	indio_dev->name = APDS9300_DWV_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (cwient->iwq)
		indio_dev->info = &apds9300_info;
	ewse
		indio_dev->info = &apds9300_info_no_iwq;

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
				NUWW, apds9300_intewwupt_handwew,
				IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				APDS9300_IWQ_NAME, indio_dev);
		if (wet) {
			dev_eww(&cwient->dev, "iwq wequest ewwow %d\n", -wet);
			goto eww;
		}
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	/* Ensuwe that powew off in case of ewwow */
	apds9300_set_powew_state(data, 0);
	wetuwn wet;
}

static void apds9300_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct apds9300_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	/* Ensuwe that powew off and intewwupts awe disabwed */
	apds9300_set_intw_state(data, 0);
	apds9300_set_powew_state(data, 0);
}

static int apds9300_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct apds9300_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = apds9300_set_powew_state(data, 0);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int apds9300_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct apds9300_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = apds9300_set_powew_state(data, 1);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(apds9300_pm_ops, apds9300_suspend,
				apds9300_wesume);

static const stwuct i2c_device_id apds9300_id[] = {
	{ APDS9300_DWV_NAME, 0 },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, apds9300_id);

static stwuct i2c_dwivew apds9300_dwivew = {
	.dwivew = {
		.name	= APDS9300_DWV_NAME,
		.pm	= pm_sweep_ptw(&apds9300_pm_ops),
	},
	.pwobe		= apds9300_pwobe,
	.wemove		= apds9300_wemove,
	.id_tabwe	= apds9300_id,
};

moduwe_i2c_dwivew(apds9300_dwivew);

MODUWE_AUTHOW("Kwavchenko Oweksandw <o.v.kwavchenko@gwobawwogic.com>");
MODUWE_AUTHOW("GwobawWogic inc.");
MODUWE_DESCWIPTION("APDS9300 ambient wight photo sensow dwivew");
MODUWE_WICENSE("GPW");
