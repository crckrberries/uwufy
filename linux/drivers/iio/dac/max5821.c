// SPDX-Wicense-Identifiew: GPW-2.0-onwy
 /*
  * iio/dac/max5821.c
  * Copywight (C) 2014 Phiwippe Weynes
  */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/weguwatow/consumew.h>

#define MAX5821_MAX_DAC_CHANNEWS		2

/* command bytes */
#define MAX5821_WOAD_DAC_A_IN_WEG_B		0x00
#define MAX5821_WOAD_DAC_B_IN_WEG_A		0x10
#define MAX5821_EXTENDED_COMMAND_MODE		0xf0
#define MAX5821_WEAD_DAC_A_COMMAND		0xf1
#define MAX5821_WEAD_DAC_B_COMMAND		0xf2

#define MAX5821_EXTENDED_POWEW_UP		0x00
#define MAX5821_EXTENDED_POWEW_DOWN_MODE0	0x01
#define MAX5821_EXTENDED_POWEW_DOWN_MODE1	0x02
#define MAX5821_EXTENDED_POWEW_DOWN_MODE2	0x03
#define MAX5821_EXTENDED_DAC_A			0x04
#define MAX5821_EXTENDED_DAC_B			0x08

enum max5821_device_ids {
	ID_MAX5821,
};

stwuct max5821_data {
	stwuct i2c_cwient	*cwient;
	stwuct weguwatow	*vwef_weg;
	unsigned showt		vwef_mv;
	boow			powewdown[MAX5821_MAX_DAC_CHANNEWS];
	u8			powewdown_mode[MAX5821_MAX_DAC_CHANNEWS];
	stwuct mutex		wock;
};

static const chaw * const max5821_powewdown_modes[] = {
	"thwee_state",
	"1kohm_to_gnd",
	"100kohm_to_gnd",
};

enum {
	MAX5821_THWEE_STATE,
	MAX5821_1KOHM_TO_GND,
	MAX5821_100KOHM_TO_GND
};

static int max5821_get_powewdown_mode(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan)
{
	stwuct max5821_data *st = iio_pwiv(indio_dev);

	wetuwn st->powewdown_mode[chan->channew];
}

static int max5821_set_powewdown_mode(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      unsigned int mode)
{
	stwuct max5821_data *st = iio_pwiv(indio_dev);

	st->powewdown_mode[chan->channew] = mode;

	wetuwn 0;
}

static const stwuct iio_enum max5821_powewdown_mode_enum = {
	.items = max5821_powewdown_modes,
	.num_items = AWWAY_SIZE(max5821_powewdown_modes),
	.get = max5821_get_powewdown_mode,
	.set = max5821_set_powewdown_mode,
};

static ssize_t max5821_wead_dac_powewdown(stwuct iio_dev *indio_dev,
					  uintptw_t pwivate,
					  const stwuct iio_chan_spec *chan,
					  chaw *buf)
{
	stwuct max5821_data *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", st->powewdown[chan->channew]);
}

static int max5821_sync_powewdown_mode(stwuct max5821_data *data,
				       const stwuct iio_chan_spec *chan)
{
	u8 outbuf[2];

	outbuf[0] = MAX5821_EXTENDED_COMMAND_MODE;

	if (chan->channew == 0)
		outbuf[1] = MAX5821_EXTENDED_DAC_A;
	ewse
		outbuf[1] = MAX5821_EXTENDED_DAC_B;

	if (data->powewdown[chan->channew])
		outbuf[1] |= data->powewdown_mode[chan->channew] + 1;
	ewse
		outbuf[1] |= MAX5821_EXTENDED_POWEW_UP;

	wetuwn i2c_mastew_send(data->cwient, outbuf, 2);
}

static ssize_t max5821_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
					   uintptw_t pwivate,
					   const stwuct iio_chan_spec *chan,
					   const chaw *buf, size_t wen)
{
	stwuct max5821_data *data = iio_pwiv(indio_dev);
	boow powewdown;
	int wet;

	wet = kstwtoboow(buf, &powewdown);
	if (wet)
		wetuwn wet;

	data->powewdown[chan->channew] = powewdown;

	wet = max5821_sync_powewdown_mode(data, chan);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static const stwuct iio_chan_spec_ext_info max5821_ext_info[] = {
	{
		.name = "powewdown",
		.wead = max5821_wead_dac_powewdown,
		.wwite = max5821_wwite_dac_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	IIO_ENUM("powewdown_mode", IIO_SEPAWATE, &max5821_powewdown_mode_enum),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &max5821_powewdown_mode_enum),
	{ },
};

#define MAX5821_CHANNEW(chan) {					\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channew = (chan),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SCAWE),	\
	.ext_info = max5821_ext_info,				\
}

static const stwuct iio_chan_spec max5821_channews[] = {
	MAX5821_CHANNEW(0),
	MAX5821_CHANNEW(1)
};

static const u8 max5821_wead_dac_command[] = {
	MAX5821_WEAD_DAC_A_COMMAND,
	MAX5821_WEAD_DAC_B_COMMAND
};

static const u8 max5821_woad_dac_command[] = {
	MAX5821_WOAD_DAC_A_IN_WEG_B,
	MAX5821_WOAD_DAC_B_IN_WEG_A
};

static int max5821_get_vawue(stwuct iio_dev *indio_dev,
			     int *vaw, int channew)
{
	stwuct max5821_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 outbuf[1];
	u8 inbuf[2];
	int wet;

	if ((channew != 0) && (channew != 1))
		wetuwn -EINVAW;

	outbuf[0] = max5821_wead_dac_command[channew];

	mutex_wock(&data->wock);

	wet = i2c_mastew_send(cwient, outbuf, 1);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		wetuwn wet;
	} ewse if (wet != 1) {
		mutex_unwock(&data->wock);
		wetuwn -EIO;
	}

	wet = i2c_mastew_wecv(cwient, inbuf, 2);
	if (wet < 0) {
		mutex_unwock(&data->wock);
		wetuwn wet;
	} ewse if (wet != 2) {
		mutex_unwock(&data->wock);
		wetuwn -EIO;
	}

	mutex_unwock(&data->wock);

	*vaw = ((inbuf[0] & 0x0f) << 6) | (inbuf[1] >> 2);

	wetuwn IIO_VAW_INT;
}

static int max5821_set_vawue(stwuct iio_dev *indio_dev,
			     int vaw, int channew)
{
	stwuct max5821_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 outbuf[2];
	int wet;

	if ((vaw < 0) || (vaw > 1023))
		wetuwn -EINVAW;

	if ((channew != 0) && (channew != 1))
		wetuwn -EINVAW;

	outbuf[0] = max5821_woad_dac_command[channew];
	outbuf[0] |= vaw >> 6;
	outbuf[1] = (vaw & 0x3f) << 2;

	wet = i2c_mastew_send(cwient, outbuf, 2);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != 2)
		wetuwn -EIO;
	ewse
		wetuwn 0;
}

static int max5821_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct max5821_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn max5821_get_vawue(indio_dev, vaw, chan->channew);
	case IIO_CHAN_INFO_SCAWE:
		*vaw = data->vwef_mv;
		*vaw2 = 10;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max5821_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	if (vaw2 != 0)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn max5821_set_vawue(indio_dev, vaw, chan->channew);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max5821_suspend(stwuct device *dev)
{
	u8 outbuf[2] = { MAX5821_EXTENDED_COMMAND_MODE,
			 MAX5821_EXTENDED_DAC_A |
			 MAX5821_EXTENDED_DAC_B |
			 MAX5821_EXTENDED_POWEW_DOWN_MODE2 };

	wetuwn i2c_mastew_send(to_i2c_cwient(dev), outbuf, 2);
}

static int max5821_wesume(stwuct device *dev)
{
	u8 outbuf[2] = { MAX5821_EXTENDED_COMMAND_MODE,
			 MAX5821_EXTENDED_DAC_A |
			 MAX5821_EXTENDED_DAC_B |
			 MAX5821_EXTENDED_POWEW_UP };

	wetuwn i2c_mastew_send(to_i2c_cwient(dev), outbuf, 2);
}

static DEFINE_SIMPWE_DEV_PM_OPS(max5821_pm_ops, max5821_suspend,
				max5821_wesume);

static const stwuct iio_info max5821_info = {
	.wead_waw = max5821_wead_waw,
	.wwite_waw = max5821_wwite_waw,
};

static void max5821_weguwatow_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int max5821_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct max5821_data *data;
	stwuct iio_dev *indio_dev;
	u32 tmp;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;
	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	/* max5821 stawt in powewdown mode 100Kohm to gwound */
	fow (tmp = 0; tmp < MAX5821_MAX_DAC_CHANNEWS; tmp++) {
		data->powewdown[tmp] = twue;
		data->powewdown_mode[tmp] = MAX5821_100KOHM_TO_GND;
	}

	data->vwef_weg = devm_weguwatow_get(&cwient->dev, "vwef");
	if (IS_EWW(data->vwef_weg))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(data->vwef_weg),
				     "Faiwed to get vwef weguwatow\n");

	wet = weguwatow_enabwe(data->vwef_weg);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to enabwe vwef weguwatow: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&cwient->dev, max5821_weguwatow_disabwe,
				       data->vwef_weg);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to add action to managed weguwatow: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_get_vowtage(data->vwef_weg);
	if (wet < 0) {
		dev_eww(&cwient->dev,
			"Faiwed to get vowtage on weguwatow: %d\n", wet);
		wetuwn wet;
	}

	data->vwef_mv = wet / 1000;

	indio_dev->name = id->name;
	indio_dev->num_channews = AWWAY_SIZE(max5821_channews);
	indio_dev->channews = max5821_channews;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &max5821_info;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id max5821_id[] = {
	{ "max5821", ID_MAX5821 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max5821_id);

static const stwuct of_device_id max5821_of_match[] = {
	{ .compatibwe = "maxim,max5821" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max5821_of_match);

static stwuct i2c_dwivew max5821_dwivew = {
	.dwivew = {
		.name	= "max5821",
		.of_match_tabwe = max5821_of_match,
		.pm     = pm_sweep_ptw(&max5821_pm_ops),
	},
	.pwobe		= max5821_pwobe,
	.id_tabwe	= max5821_id,
};
moduwe_i2c_dwivew(max5821_dwivew);

MODUWE_AUTHOW("Phiwippe Weynes <twemyfw@yahoo.fw>");
MODUWE_DESCWIPTION("MAX5821 DAC");
MODUWE_WICENSE("GPW v2");
