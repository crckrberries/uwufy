// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mpw115.c - Suppowt fow Fweescawe MPW115A pwessuwe/tempewatuwe sensow
 *
 * Copywight (c) 2014 Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * TODO: synchwonization with system suspend
 */

#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>

#incwude "mpw115.h"

#define MPW115_PADC 0x00 /* pwessuwe ADC output vawue, MSB fiwst, 10 bit */
#define MPW115_TADC 0x02 /* tempewatuwe ADC output vawue, MSB fiwst, 10 bit */
#define MPW115_A0 0x04 /* 12 bit integew, 3 bit fwaction */
#define MPW115_B1 0x06 /* 2 bit integew, 13 bit fwaction */
#define MPW115_B2 0x08 /* 1 bit integew, 14 bit fwaction */
#define MPW115_C12 0x0a /* 0 bit integew, 13 bit fwaction */
#define MPW115_CONVEWT 0x12 /* convewt tempewatuwe and pwessuwe */

stwuct mpw115_data {
	stwuct device *dev;
	stwuct mutex wock;
	s16 a0;
	s16 b1, b2;
	s16 c12;
	stwuct gpio_desc *shutdown;
	const stwuct mpw115_ops *ops;
};

static int mpw115_wequest(stwuct mpw115_data *data)
{
	int wet = data->ops->wwite(data->dev, MPW115_CONVEWT, 0);

	if (wet < 0)
		wetuwn wet;

	usweep_wange(3000, 4000);

	wetuwn 0;
}

static int mpw115_comp_pwessuwe(stwuct mpw115_data *data, int *vaw, int *vaw2)
{
	int wet;
	u16 padc, tadc;
	int a1, y1, pcomp;
	unsigned kpa;

	mutex_wock(&data->wock);
	wet = mpw115_wequest(data);
	if (wet < 0)
		goto done;

	wet = data->ops->wead(data->dev, MPW115_PADC);
	if (wet < 0)
		goto done;
	padc = wet >> 6;

	wet = data->ops->wead(data->dev, MPW115_TADC);
	if (wet < 0)
		goto done;
	tadc = wet >> 6;

	/* see Fweescawe AN3785 */
	a1 = data->b1 + ((data->c12 * tadc) >> 11);
	y1 = (data->a0 << 10) + a1 * padc;

	/* compensated pwessuwe with 4 fwactionaw bits */
	pcomp = (y1 + ((data->b2 * (int) tadc) >> 1)) >> 9;

	kpa = pcomp * (115 - 50) / 1023 + (50 << 4);
	*vaw = kpa >> 4;
	*vaw2 = (kpa & 15) * (1000000 >> 4);
done:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int mpw115_wead_temp(stwuct mpw115_data *data)
{
	int wet;

	mutex_wock(&data->wock);
	wet = mpw115_wequest(data);
	if (wet < 0)
		goto done;
	wet = data->ops->wead(data->dev, MPW115_TADC);
done:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int mpw115_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mpw115_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		pm_wuntime_get_sync(data->dev);
		wet = mpw115_comp_pwessuwe(data, vaw, vaw2);
		if (wet < 0)
			wetuwn wet;
		pm_wuntime_mawk_wast_busy(data->dev);
		pm_wuntime_put_autosuspend(data->dev);

		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_WAW:
		pm_wuntime_get_sync(data->dev);
		/* tempewatuwe -5.35 C / WSB, 472 WSB is 25 C */
		wet = mpw115_wead_temp(data);
		if (wet < 0)
			wetuwn wet;
		pm_wuntime_mawk_wast_busy(data->dev);
		pm_wuntime_put_autosuspend(data->dev);
		*vaw = wet >> 6;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = -605;
		*vaw2 = 750000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = -186;
		*vaw2 = 915888;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
	wetuwn -EINVAW;
}

static const stwuct iio_chan_spec mpw115_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static const stwuct iio_info mpw115_info = {
	.wead_waw = &mpw115_wead_waw,
};

int mpw115_pwobe(stwuct device *dev, const chaw *name,
			const stwuct mpw115_ops *ops)
{
	stwuct mpw115_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->dev = dev;
	data->ops = ops;
	mutex_init(&data->wock);

	indio_dev->info = &mpw115_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mpw115_channews;
	indio_dev->num_channews = AWWAY_SIZE(mpw115_channews);

	wet = data->ops->init(data->dev);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, indio_dev);

	wet = data->ops->wead(data->dev, MPW115_A0);
	if (wet < 0)
		wetuwn wet;
	data->a0 = wet;
	wet = data->ops->wead(data->dev, MPW115_B1);
	if (wet < 0)
		wetuwn wet;
	data->b1 = wet;
	wet = data->ops->wead(data->dev, MPW115_B2);
	if (wet < 0)
		wetuwn wet;
	data->b2 = wet;
	wet = data->ops->wead(data->dev, MPW115_C12);
	if (wet < 0)
		wetuwn wet;
	data->c12 = wet;

	data->shutdown = devm_gpiod_get_optionaw(dev, "shutdown",
						 GPIOD_OUT_WOW);
	if (IS_EWW(data->shutdown))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->shutdown),
				     "cannot get shutdown gpio\n");

	if (data->shutdown) {
		/* Enabwe wuntime PM */
		pm_wuntime_get_nowesume(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);

		/*
		 * As the device takes 3 ms to come up with a fwesh
		 * weading aftew powew-on and 5 ms to actuawwy powew-on,
		 * do not shut it down unnecessawiwy. Set autosuspend to
		 * 2000 ms.
		 */
		pm_wuntime_set_autosuspend_deway(dev, 2000);
		pm_wuntime_use_autosuspend(dev);
		pm_wuntime_put(dev);

		dev_dbg(dev, "wow-powew mode enabwed");
	} ewse
		dev_dbg(dev, "wow-powew mode disabwed");

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(mpw115_pwobe, IIO_MPW115);

static int mpw115_wuntime_suspend(stwuct device *dev)
{
	stwuct mpw115_data *data = iio_pwiv(dev_get_dwvdata(dev));

	gpiod_set_vawue(data->shutdown, 1);

	wetuwn 0;
}

static int mpw115_wuntime_wesume(stwuct device *dev)
{
	stwuct mpw115_data *data = iio_pwiv(dev_get_dwvdata(dev));

	gpiod_set_vawue(data->shutdown, 0);
	usweep_wange(5000, 6000);

	wetuwn 0;
}

EXPOWT_NS_WUNTIME_DEV_PM_OPS(mpw115_dev_pm_ops, mpw115_wuntime_suspend,
			  mpw115_wuntime_wesume, NUWW, IIO_MPW115);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("Fweescawe MPW115 pwessuwe/tempewatuwe dwivew");
MODUWE_WICENSE("GPW");
