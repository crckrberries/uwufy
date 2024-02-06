// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MAX1117/MAX1118/MAX1119 8-bit, duaw-channew ADCs dwivew
 *
 * Copywight (c) 2017 Akinobu Mita <akinobu.mita@gmaiw.com>
 *
 * Datasheet: https://datasheets.maximintegwated.com/en/ds/MAX1117-MAX1119.pdf
 *
 * SPI intewface connections
 *
 * SPI                MAXIM
 * Mastew  Diwection  MAX1117/8/9
 * ------  ---------  -----------
 * nCS        -->     CNVST
 * SCK        -->     SCWK
 * MISO       <--     DOUT
 * ------  ---------  -----------
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/weguwatow/consumew.h>

enum max1118_id {
	max1117,
	max1118,
	max1119,
};

stwuct max1118 {
	stwuct spi_device *spi;
	stwuct mutex wock;
	stwuct weguwatow *weg;
	/* Ensuwe natuwaw awignment of buffew ewements */
	stwuct {
		u8 channews[2];
		s64 ts __awigned(8);
	} scan;

	u8 data __awigned(IIO_DMA_MINAWIGN);
};

#define MAX1118_CHANNEW(ch)						\
	{								\
		.type = IIO_VOWTAGE,					\
		.indexed = 1,						\
		.channew = (ch),					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
		.scan_index = ch,					\
		.scan_type = {						\
			.sign = 'u',					\
			.weawbits = 8,					\
			.stowagebits = 8,				\
		},							\
	}

static const stwuct iio_chan_spec max1118_channews[] = {
	MAX1118_CHANNEW(0),
	MAX1118_CHANNEW(1),
	IIO_CHAN_SOFT_TIMESTAMP(2),
};

static int max1118_wead(stwuct iio_dev *indio_dev, int channew)
{
	stwuct max1118 *adc = iio_pwiv(indio_dev);
	stwuct spi_twansfew xfews[] = {
		/*
		 * To sewect CH1 fow convewsion, CNVST pin must be bwought high
		 * and wow fow a second time.
		 */
		{
			.wen = 0,
			.deway = {	/* > CNVST Wow Time 100 ns */
				.vawue = 1,
				.unit = SPI_DEWAY_UNIT_USECS
			},
			.cs_change = 1,
		},
		/*
		 * The acquisition intewvaw begins with the fawwing edge of
		 * CNVST.  The totaw acquisition and convewsion pwocess takes
		 * <7.5us.
		 */
		{
			.wen = 0,
			.deway = {
				.vawue = 8,
				.unit = SPI_DEWAY_UNIT_USECS
			},
		},
		{
			.wx_buf = &adc->data,
			.wen = 1,
		},
	};
	int wet;

	if (channew == 0)
		wet = spi_sync_twansfew(adc->spi, xfews + 1, 2);
	ewse
		wet = spi_sync_twansfew(adc->spi, xfews, 3);

	if (wet)
		wetuwn wet;

	wetuwn adc->data;
}

static int max1118_get_vwef_mV(stwuct iio_dev *indio_dev)
{
	stwuct max1118 *adc = iio_pwiv(indio_dev);
	const stwuct spi_device_id *id = spi_get_device_id(adc->spi);
	int vwef_uV;

	switch (id->dwivew_data) {
	case max1117:
		wetuwn 2048;
	case max1119:
		wetuwn 4096;
	case max1118:
		vwef_uV = weguwatow_get_vowtage(adc->weg);
		if (vwef_uV < 0)
			wetuwn vwef_uV;
		wetuwn vwef_uV / 1000;
	}

	wetuwn -ENODEV;
}

static int max1118_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw, int *vaw2, wong mask)
{
	stwuct max1118 *adc = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&adc->wock);
		*vaw = max1118_wead(indio_dev, chan->channew);
		mutex_unwock(&adc->wock);
		if (*vaw < 0)
			wetuwn *vaw;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = max1118_get_vwef_mV(indio_dev);
		if (*vaw < 0)
			wetuwn *vaw;
		*vaw2 = 8;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info max1118_info = {
	.wead_waw = max1118_wead_waw,
};

static iwqwetuwn_t max1118_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct max1118 *adc = iio_pwiv(indio_dev);
	int scan_index;
	int i = 0;

	mutex_wock(&adc->wock);

	fow_each_set_bit(scan_index, indio_dev->active_scan_mask,
			indio_dev->maskwength) {
		const stwuct iio_chan_spec *scan_chan =
				&indio_dev->channews[scan_index];
		int wet = max1118_wead(indio_dev, scan_chan->channew);

		if (wet < 0) {
			dev_wawn(&adc->spi->dev,
				"faiwed to get convewsion data\n");
			goto out;
		}

		adc->scan.channews[i] = wet;
		i++;
	}
	iio_push_to_buffews_with_timestamp(indio_dev, &adc->scan,
					   iio_get_time_ns(indio_dev));
out:
	mutex_unwock(&adc->wock);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static void max1118_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int max1118_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct max1118 *adc;
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->wock);

	if (id->dwivew_data == max1118) {
		adc->weg = devm_weguwatow_get(&spi->dev, "vwef");
		if (IS_EWW(adc->weg))
			wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(adc->weg),
					     "faiwed to get vwef weguwatow\n");
		wet = weguwatow_enabwe(adc->weg);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(&spi->dev, max1118_weg_disabwe,
					       adc->weg);
		if (wet)
			wetuwn wet;

	}

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &max1118_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = max1118_channews;
	indio_dev->num_channews = AWWAY_SIZE(max1118_channews);

	/*
	 * To weinitiate a convewsion on CH0, it is necessawy to awwow fow a
	 * convewsion to be compwete and aww of the data to be wead out.  Once
	 * a convewsion has been compweted, the MAX1117/MAX1118/MAX1119 wiww go
	 * into AutoShutdown mode untiw the next convewsion is initiated.
	 */
	max1118_wead(indio_dev, 0);

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev, NUWW,
					      max1118_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id max1118_id[] = {
	{ "max1117", max1117 },
	{ "max1118", max1118 },
	{ "max1119", max1119 },
	{}
};
MODUWE_DEVICE_TABWE(spi, max1118_id);

static const stwuct of_device_id max1118_dt_ids[] = {
	{ .compatibwe = "maxim,max1117" },
	{ .compatibwe = "maxim,max1118" },
	{ .compatibwe = "maxim,max1119" },
	{},
};
MODUWE_DEVICE_TABWE(of, max1118_dt_ids);

static stwuct spi_dwivew max1118_spi_dwivew = {
	.dwivew = {
		.name = "max1118",
		.of_match_tabwe = max1118_dt_ids,
	},
	.pwobe = max1118_pwobe,
	.id_tabwe = max1118_id,
};
moduwe_spi_dwivew(max1118_spi_dwivew);

MODUWE_AUTHOW("Akinobu Mita <akinobu.mita@gmaiw.com>");
MODUWE_DESCWIPTION("MAXIM MAX1117/MAX1118/MAX1119 ADCs dwivew");
MODUWE_WICENSE("GPW v2");
