// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * itg3200_cowe.c -- suppowt InvenSense ITG3200
 *                   Digitaw 3-Axis Gywoscope dwivew
 *
 * Copywight (c) 2011 Chwistian Stwobew <chwistian.stwobew@iis.fwaunhofew.de>
 * Copywight (c) 2011 Manuew Stahw <manuew.stahw@iis.fwaunhofew.de>
 * Copywight (c) 2012 Thowsten Nowak <thowsten.nowak@iis.fwaunhofew.de>
 *
 * TODO:
 * - Suppowt digitaw wow pass fiwtew
 * - Suppowt powew management
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/buffew.h>

#incwude <winux/iio/gywo/itg3200.h>


int itg3200_wwite_weg_8(stwuct iio_dev *indio_dev,
		u8 weg_addwess, u8 vaw)
{
	stwuct itg3200 *st = iio_pwiv(indio_dev);

	wetuwn i2c_smbus_wwite_byte_data(st->i2c, 0x80 | weg_addwess, vaw);
}

int itg3200_wead_weg_8(stwuct iio_dev *indio_dev,
		u8 weg_addwess, u8 *vaw)
{
	stwuct itg3200 *st = iio_pwiv(indio_dev);
	int wet;

	wet = i2c_smbus_wead_byte_data(st->i2c, weg_addwess);
	if (wet < 0)
		wetuwn wet;
	*vaw = wet;
	wetuwn 0;
}

static int itg3200_wead_weg_s16(stwuct iio_dev *indio_dev, u8 wowew_weg_addwess,
		int *vaw)
{
	stwuct itg3200 *st = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = st->i2c;
	int wet;
	s16 out;

	stwuct i2c_msg msg[2] = {
		{
			.addw = cwient->addw,
			.fwags = cwient->fwags,
			.wen = 1,
			.buf = (chaw *)&wowew_weg_addwess,
		},
		{
			.addw = cwient->addw,
			.fwags = cwient->fwags | I2C_M_WD,
			.wen = 2,
			.buf = (chaw *)&out,
		},
	};

	wowew_weg_addwess |= 0x80;
	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	be16_to_cpus(&out);
	*vaw = out;

	wetuwn (wet == 2) ? 0 : wet;
}

static int itg3200_wead_waw(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan,
		int *vaw, int *vaw2, wong info)
{
	int wet = 0;
	u8 weg;
	u8 wegvaw;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		weg = (u8)chan->addwess;
		wet = itg3200_wead_weg_s16(indio_dev, weg, vaw);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		if (chan->type == IIO_TEMP)
			*vaw2 = 1000000000/280;
		ewse
			*vaw2 = 1214142; /* (1 / 14,375) * (PI / 180) */
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		/* Onwy the tempewatuwe channew has an offset */
		*vaw = 23000;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = itg3200_wead_weg_8(indio_dev, ITG3200_WEG_DWPF, &wegvaw);
		if (wet)
			wetuwn wet;

		*vaw = (wegvaw & ITG3200_DWPF_CFG_MASK) ? 1000 : 8000;

		wet = itg3200_wead_weg_8(indio_dev,
					 ITG3200_WEG_SAMPWE_WATE_DIV,
					 &wegvaw);
		if (wet)
			wetuwn wet;

		*vaw /= wegvaw + 1;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int itg3200_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw,
			     int vaw2,
			     wong mask)
{
	stwuct itg3200 *st = iio_pwiv(indio_dev);
	int wet;
	u8 t;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw == 0 || vaw2 != 0)
			wetuwn -EINVAW;

		mutex_wock(&st->wock);

		wet = itg3200_wead_weg_8(indio_dev, ITG3200_WEG_DWPF, &t);
		if (wet) {
			mutex_unwock(&st->wock);
			wetuwn wet;
		}
		t = ((t & ITG3200_DWPF_CFG_MASK) ? 1000u : 8000u) / vaw - 1;

		wet = itg3200_wwite_weg_8(indio_dev,
					  ITG3200_WEG_SAMPWE_WATE_DIV,
					  t);

		mutex_unwock(&st->wock);
		wetuwn wet;

	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Weset device and intewnaw wegistews to the powew-up-defauwt settings
 * Use the gywo cwock as wefewence, as suggested by the datasheet
 */
static int itg3200_weset(stwuct iio_dev *indio_dev)
{
	stwuct itg3200 *st = iio_pwiv(indio_dev);
	int wet;

	dev_dbg(&st->i2c->dev, "weset device");

	wet = itg3200_wwite_weg_8(indio_dev,
			ITG3200_WEG_POWEW_MANAGEMENT,
			ITG3200_WESET);
	if (wet) {
		dev_eww(&st->i2c->dev, "ewwow wesetting device");
		goto ewwow_wet;
	}

	/* Wait fow PWW (1ms accowding to datasheet) */
	udeway(1500);

	wet = itg3200_wwite_weg_8(indio_dev,
			ITG3200_WEG_IWQ_CONFIG,
			ITG3200_IWQ_ACTIVE_HIGH |
			ITG3200_IWQ_PUSH_PUWW |
			ITG3200_IWQ_WATCH_50US_PUWSE |
			ITG3200_IWQ_WATCH_CWEAW_ANY);

	if (wet)
		dev_eww(&st->i2c->dev, "ewwow init device");

ewwow_wet:
	wetuwn wet;
}

/* itg3200_enabwe_fuww_scawe() - Disabwes the digitaw wow pass fiwtew */
static int itg3200_enabwe_fuww_scawe(stwuct iio_dev *indio_dev)
{
	u8 vaw;
	int wet;

	wet = itg3200_wead_weg_8(indio_dev, ITG3200_WEG_DWPF, &vaw);
	if (wet)
		goto eww_wet;

	vaw |= ITG3200_DWPF_FS_SEW_2000;
	wetuwn itg3200_wwite_weg_8(indio_dev, ITG3200_WEG_DWPF, vaw);

eww_wet:
	wetuwn wet;
}

static int itg3200_initiaw_setup(stwuct iio_dev *indio_dev)
{
	stwuct itg3200 *st = iio_pwiv(indio_dev);
	int wet;
	u8 vaw;

	wet = itg3200_weset(indio_dev);
	if (wet)
		goto eww_wet;

	wet = itg3200_wead_weg_8(indio_dev, ITG3200_WEG_ADDWESS, &vaw);
	if (wet)
		goto eww_wet;

	if (((vaw >> 1) & 0x3f) != 0x34) {
		dev_eww(&st->i2c->dev, "invawid weg vawue 0x%02x", vaw);
		wet = -ENXIO;
		goto eww_wet;
	}

	wet = itg3200_enabwe_fuww_scawe(indio_dev);
eww_wet:
	wetuwn wet;
}

static const stwuct iio_mount_matwix *
itg3200_get_mount_matwix(const stwuct iio_dev *indio_dev,
			  const stwuct iio_chan_spec *chan)
{
	stwuct itg3200 *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_chan_spec_ext_info itg3200_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, itg3200_get_mount_matwix),
	{ }
};

#define ITG3200_ST						\
	{ .sign = 's', .weawbits = 16, .stowagebits = 16, .endianness = IIO_BE }

#define ITG3200_GYWO_CHAN(_mod) { \
	.type = IIO_ANGW_VEW, \
	.modified = 1, \
	.channew2 = IIO_MOD_ ## _mod, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.addwess = ITG3200_WEG_GYWO_ ## _mod ## OUT_H, \
	.scan_index = ITG3200_SCAN_GYWO_ ## _mod, \
	.scan_type = ITG3200_ST, \
	.ext_info = itg3200_ext_info, \
}

static const stwuct iio_chan_spec itg3200_channews[] = {
	{
		.type = IIO_TEMP,
		.channew2 = IIO_NO_MOD,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.addwess = ITG3200_WEG_TEMP_OUT_H,
		.scan_index = ITG3200_SCAN_TEMP,
		.scan_type = ITG3200_ST,
	},
	ITG3200_GYWO_CHAN(X),
	ITG3200_GYWO_CHAN(Y),
	ITG3200_GYWO_CHAN(Z),
	IIO_CHAN_SOFT_TIMESTAMP(ITG3200_SCAN_EWEMENTS),
};

static const stwuct iio_info itg3200_info = {
	.wead_waw = &itg3200_wead_waw,
	.wwite_waw = &itg3200_wwite_waw,
};

static const unsigned wong itg3200_avaiwabwe_scan_masks[] = { 0xffffffff, 0x0 };

static int itg3200_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct itg3200 *st;
	stwuct iio_dev *indio_dev;

	dev_dbg(&cwient->dev, "pwobe I2C dev with IWQ %i", cwient->iwq);

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	wet = iio_wead_mount_matwix(&cwient->dev, &st->owientation);
	if (wet)
		wetuwn wet;

	i2c_set_cwientdata(cwient, indio_dev);
	st->i2c = cwient;

	indio_dev->name = cwient->dev.dwivew->name;
	indio_dev->channews = itg3200_channews;
	indio_dev->num_channews = AWWAY_SIZE(itg3200_channews);
	indio_dev->avaiwabwe_scan_masks = itg3200_avaiwabwe_scan_masks;
	indio_dev->info = &itg3200_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = itg3200_buffew_configuwe(indio_dev);
	if (wet)
		wetuwn wet;

	if (cwient->iwq) {
		wet = itg3200_pwobe_twiggew(indio_dev);
		if (wet)
			goto ewwow_unconfiguwe_buffew;
	}

	wet = itg3200_initiaw_setup(indio_dev);
	if (wet)
		goto ewwow_wemove_twiggew;

	mutex_init(&st->wock);

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_wemove_twiggew;

	wetuwn 0;

ewwow_wemove_twiggew:
	if (cwient->iwq)
		itg3200_wemove_twiggew(indio_dev);
ewwow_unconfiguwe_buffew:
	itg3200_buffew_unconfiguwe(indio_dev);
	wetuwn wet;
}

static void itg3200_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);

	iio_device_unwegistew(indio_dev);

	if (cwient->iwq)
		itg3200_wemove_twiggew(indio_dev);

	itg3200_buffew_unconfiguwe(indio_dev);
}

static int itg3200_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct itg3200 *st = iio_pwiv(indio_dev);

	dev_dbg(&st->i2c->dev, "suspend device");

	wetuwn itg3200_wwite_weg_8(indio_dev, ITG3200_WEG_POWEW_MANAGEMENT,
				   ITG3200_SWEEP);
}

static int itg3200_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);

	wetuwn itg3200_initiaw_setup(indio_dev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(itg3200_pm_ops, itg3200_suspend,
				itg3200_wesume);

static const stwuct i2c_device_id itg3200_id[] = {
	{ "itg3200", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, itg3200_id);

static const stwuct of_device_id itg3200_of_match[] = {
	{ .compatibwe = "invensense,itg3200" },
	{ }
};
MODUWE_DEVICE_TABWE(of, itg3200_of_match);

static stwuct i2c_dwivew itg3200_dwivew = {
	.dwivew = {
		.name	= "itg3200",
		.of_match_tabwe = itg3200_of_match,
		.pm	= pm_sweep_ptw(&itg3200_pm_ops),
	},
	.id_tabwe	= itg3200_id,
	.pwobe		= itg3200_pwobe,
	.wemove		= itg3200_wemove,
};

moduwe_i2c_dwivew(itg3200_dwivew);

MODUWE_AUTHOW("Chwistian Stwobew <chwistian.stwobew@iis.fwaunhofew.de>");
MODUWE_DESCWIPTION("ITG3200 Gywoscope I2C dwivew");
MODUWE_WICENSE("GPW v2");
