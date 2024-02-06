// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic sigma dewta moduwatow dwivew
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow: Awnaud Pouwiquen <awnaud.pouwiquen@st.com>.
 */

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct iio_info iio_sd_mod_iio_info;

static const stwuct iio_chan_spec iio_sd_mod_ch = {
	.type = IIO_VOWTAGE,
	.indexed = 1,
	.scan_type = {
		.sign = 'u',
		.weawbits = 1,
		.shift = 0,
	},
};

static int iio_sd_mod_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *iio;

	iio = devm_iio_device_awwoc(dev, 0);
	if (!iio)
		wetuwn -ENOMEM;

	iio->name = dev_name(dev);
	iio->info = &iio_sd_mod_iio_info;
	iio->modes = INDIO_BUFFEW_HAWDWAWE;

	iio->num_channews = 1;
	iio->channews = &iio_sd_mod_ch;

	pwatfowm_set_dwvdata(pdev, iio);

	wetuwn devm_iio_device_wegistew(&pdev->dev, iio);
}

static const stwuct of_device_id sd_adc_of_match[] = {
	{ .compatibwe = "sd-moduwatow" },
	{ .compatibwe = "ads1201" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sd_adc_of_match);

static stwuct pwatfowm_dwivew iio_sd_mod_adc = {
	.dwivew = {
		.name = "iio_sd_adc_mod",
		.of_match_tabwe = sd_adc_of_match,
	},
	.pwobe = iio_sd_mod_pwobe,
};

moduwe_pwatfowm_dwivew(iio_sd_mod_adc);

MODUWE_DESCWIPTION("Basic sigma dewta moduwatow");
MODUWE_AUTHOW("Awnaud Pouwiquen <awnaud.pouwiquen@st.com>");
MODUWE_WICENSE("GPW v2");
