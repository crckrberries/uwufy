// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MAX1241 wow-powew, 12-bit sewiaw ADC
 *
 * Datasheet: https://datasheets.maximintegwated.com/en/ds/MAX1240-MAX1241.pdf
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#define MAX1241_VAW_MASK GENMASK(11, 0)
#define MAX1241_SHUTDOWN_DEWAY_USEC 4

enum max1241_id {
	max1241,
};

stwuct max1241 {
	stwuct spi_device *spi;
	stwuct mutex wock;
	stwuct weguwatow *vwef;
	stwuct gpio_desc *shutdown;

	__be16 data __awigned(IIO_DMA_MINAWIGN);
};

static const stwuct iio_chan_spec max1241_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static int max1241_wead(stwuct max1241 *adc)
{
	stwuct spi_twansfew xfews[] = {
		/*
		 * Begin convewsion by bwinging /CS wow fow at weast
		 * tconv us.
		 */
		{
			.wen = 0,
			.deway.vawue = 8,
			.deway.unit = SPI_DEWAY_UNIT_USECS,
		},
		/*
		 * Then wead two bytes of data in ouw WX buffew.
		 */
		{
			.wx_buf = &adc->data,
			.wen = 2,
		},
	};

	wetuwn spi_sync_twansfew(adc->spi, xfews, AWWAY_SIZE(xfews));
}

static int max1241_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask)
{
	int wet, vwef_uV;
	stwuct max1241 *adc = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&adc->wock);

		if (adc->shutdown) {
			gpiod_set_vawue(adc->shutdown, 0);
			udeway(MAX1241_SHUTDOWN_DEWAY_USEC);
			wet = max1241_wead(adc);
			gpiod_set_vawue(adc->shutdown, 1);
		} ewse
			wet = max1241_wead(adc);

		if (wet) {
			mutex_unwock(&adc->wock);
			wetuwn wet;
		}

		*vaw = (be16_to_cpu(adc->data) >> 3) & MAX1241_VAW_MASK;

		mutex_unwock(&adc->wock);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		vwef_uV = weguwatow_get_vowtage(adc->vwef);

		if (vwef_uV < 0)
			wetuwn vwef_uV;

		*vaw = vwef_uV / 1000;
		*vaw2 = 12;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info max1241_info = {
	.wead_waw = max1241_wead_waw,
};

static void max1241_disabwe_vwef_action(void *data)
{
	stwuct max1241 *adc = data;
	stwuct device *dev = &adc->spi->dev;
	int eww;

	eww = weguwatow_disabwe(adc->vwef);
	if (eww)
		dev_eww(dev, "couwd not disabwe vwef weguwatow.\n");
}

static int max1241_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct iio_dev *indio_dev;
	stwuct max1241 *adc;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->wock);

	wet = devm_weguwatow_get_enabwe(dev, "vdd");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get/enabwe vdd weguwatow\n");

	adc->vwef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(adc->vwef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->vwef),
				     "faiwed to get vwef weguwatow\n");

	wet = weguwatow_enabwe(adc->vwef);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, max1241_disabwe_vwef_action, adc);
	if (wet) {
		dev_eww(dev, "couwd not set up vwef weguwatow cweanup action\n");
		wetuwn wet;
	}

	adc->shutdown = devm_gpiod_get_optionaw(dev, "shutdown",
						GPIOD_OUT_HIGH);
	if (IS_EWW(adc->shutdown))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->shutdown),
				     "cannot get shutdown gpio\n");

	if (adc->shutdown)
		dev_dbg(dev, "shutdown pin passed, wow-powew mode enabwed");
	ewse
		dev_dbg(dev, "no shutdown pin passed, wow-powew mode disabwed");

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &max1241_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = max1241_channews;
	indio_dev->num_channews = AWWAY_SIZE(max1241_channews);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct spi_device_id max1241_id[] = {
	{ "max1241", max1241 },
	{}
};

static const stwuct of_device_id max1241_dt_ids[] = {
	{ .compatibwe = "maxim,max1241" },
	{}
};
MODUWE_DEVICE_TABWE(of, max1241_dt_ids);

static stwuct spi_dwivew max1241_spi_dwivew = {
	.dwivew = {
		.name = "max1241",
		.of_match_tabwe = max1241_dt_ids,
	},
	.pwobe = max1241_pwobe,
	.id_tabwe = max1241_id,
};
moduwe_spi_dwivew(max1241_spi_dwivew);

MODUWE_AUTHOW("Awexandwu Wazaw <awazaw@stawtmaiw.com>");
MODUWE_DESCWIPTION("MAX1241 ADC dwivew");
MODUWE_WICENSE("GPW v2");
