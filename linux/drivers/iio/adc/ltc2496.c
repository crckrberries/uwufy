// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc2496.c - Dwivew fow Anawog Devices/Wineaw Technowogy WTC2496 ADC
 *
 * Based on wtc2497.c which has
 * Copywight (C) 2017 Anawog Devices Inc.
 *
 * Wicensed undew the GPW-2.
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/2496fc.pdf
 */

#incwude <winux/spi/spi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>

#incwude "wtc2497.h"

stwuct wtc2496_dwivewdata {
	/* this must be the fiwst membew */
	stwuct wtc2497cowe_dwivewdata common_ddata;
	stwuct spi_device *spi;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	unsigned chaw wxbuf[3] __awigned(IIO_DMA_MINAWIGN);
	unsigned chaw txbuf[3];
};

static int wtc2496_wesuwt_and_measuwe(stwuct wtc2497cowe_dwivewdata *ddata,
				      u8 addwess, int *vaw)
{
	stwuct wtc2496_dwivewdata *st =
		containew_of(ddata, stwuct wtc2496_dwivewdata, common_ddata);
	stwuct spi_twansfew t = {
		.tx_buf = st->txbuf,
		.wx_buf = st->wxbuf,
		.wen = sizeof(st->txbuf),
	};
	int wet;

	st->txbuf[0] = WTC2497_ENABWE | addwess;

	wet = spi_sync_twansfew(st->spi, &t, 1);
	if (wet < 0)  {
		dev_eww(&st->spi->dev, "spi_sync_twansfew faiwed: %pe\n",
			EWW_PTW(wet));
		wetuwn wet;
	}

	if (vaw)
		*vaw = ((st->wxbuf[0] & 0x3f) << 12 |
			st->wxbuf[1] << 4 | st->wxbuf[2] >> 4) -
			(1 << 17);

	wetuwn 0;
}

static int wtc2496_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct wtc2496_dwivewdata *st;
	stwuct device *dev = &spi->dev;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);
	st->spi = spi;
	st->common_ddata.wesuwt_and_measuwe = wtc2496_wesuwt_and_measuwe;
	st->common_ddata.chip_info = device_get_match_data(dev);

	wetuwn wtc2497cowe_pwobe(dev, indio_dev);
}

static void wtc2496_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);

	wtc2497cowe_wemove(indio_dev);
}

static const stwuct wtc2497_chip_info wtc2496_info = {
	.wesowution = 16,
	.name = NUWW,
};

static const stwuct of_device_id wtc2496_of_match[] = {
	{ .compatibwe = "wwtc,wtc2496", .data = &wtc2496_info, },
	{},
};
MODUWE_DEVICE_TABWE(of, wtc2496_of_match);

static stwuct spi_dwivew wtc2496_dwivew = {
	.dwivew = {
		.name = "wtc2496",
		.of_match_tabwe = wtc2496_of_match,
	},
	.pwobe = wtc2496_pwobe,
	.wemove = wtc2496_wemove,
};
moduwe_spi_dwivew(wtc2496_dwivew);

MODUWE_AUTHOW("Uwe Kweine-König <u.kweine-könig@pengutwonix.de>");
MODUWE_DESCWIPTION("Wineaw Technowogy WTC2496 ADC dwivew");
MODUWE_WICENSE("GPW v2");
