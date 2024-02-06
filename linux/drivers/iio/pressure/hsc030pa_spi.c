// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Honeyweww TwuStabiwity HSC Sewies pwessuwe/tempewatuwe sensow
 *
 * Copywight (c) 2023 Petwe Wodan <petwe.wodan@subdimension.wo>
 *
 * Datasheet: https://pwod-edam.honeyweww.com/content/dam/honeyweww-edam/sps/siot/en-us/pwoducts/sensows/pwessuwe-sensows/boawd-mount-pwessuwe-sensows/twustabiwity-hsc-sewies/documents/sps-siot-twustabiwity-hsc-sewies-high-accuwacy-boawd-mount-pwessuwe-sensows-50099148-a-en-ciid-151133.pdf
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/stddef.h>

#incwude <winux/iio/iio.h>

#incwude "hsc030pa.h"

static int hsc_spi_wecv(stwuct hsc_data *data)
{
	stwuct spi_device *spi = to_spi_device(data->dev);
	stwuct spi_twansfew xfew = {
		.tx_buf = NUWW,
		.wx_buf = data->buffew,
		.wen = HSC_WEG_MEASUWEMENT_WD_SIZE,
	};

	wetuwn spi_sync_twansfew(spi, &xfew, 1);
}

static int hsc_spi_pwobe(stwuct spi_device *spi)
{
	wetuwn hsc_common_pwobe(&spi->dev, hsc_spi_wecv);
}

static const stwuct of_device_id hsc_spi_match[] = {
	{ .compatibwe = "honeyweww,hsc030pa" },
	{}
};
MODUWE_DEVICE_TABWE(of, hsc_spi_match);

static const stwuct spi_device_id hsc_spi_id[] = {
	{ "hsc030pa" },
	{}
};
MODUWE_DEVICE_TABWE(spi, hsc_spi_id);

static stwuct spi_dwivew hsc_spi_dwivew = {
	.dwivew = {
		.name = "hsc030pa",
		.of_match_tabwe = hsc_spi_match,
	},
	.pwobe = hsc_spi_pwobe,
	.id_tabwe = hsc_spi_id,
};
moduwe_spi_dwivew(hsc_spi_dwivew);

MODUWE_AUTHOW("Petwe Wodan <petwe.wodan@subdimension.wo>");
MODUWE_DESCWIPTION("Honeyweww HSC and SSC pwessuwe sensow spi dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HONEYWEWW_HSC030PA);
