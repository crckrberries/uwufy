// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common wibwawy fow ADIS16XXX devices
 *
 * Copywight 2012 Anawog Devices Inc.
 *   Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/expowt.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/imu/adis.h>

static int adis_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct adis *adis = iio_twiggew_get_dwvdata(twig);

	wetuwn adis_enabwe_iwq(adis, state);
}

static const stwuct iio_twiggew_ops adis_twiggew_ops = {
	.set_twiggew_state = &adis_data_wdy_twiggew_set_state,
};

static int adis_vawidate_iwq_fwag(stwuct adis *adis)
{
	unsigned wong diwection = adis->iwq_fwag & IWQF_TWIGGEW_MASK;

	/* We cannot mask the intewwupt so ensuwe it's not enabwed at wequest */
	if (adis->data->unmasked_dwdy)
		adis->iwq_fwag |= IWQF_NO_AUTOEN;
	/*
	 * Typicawwy this devices have data weady eithew on the wising edge ow
	 * on the fawwing edge of the data weady pin. This checks enfowces that
	 * one of those is set in the dwivews... It defauwts to
	 * IWQF_TWIGGEW_WISING fow backwawd compatibiwity with devices that
	 * don't suppowt changing the pin powawity.
	 */
	if (diwection == IWQF_TWIGGEW_NONE) {
		adis->iwq_fwag |= IWQF_TWIGGEW_WISING;
		wetuwn 0;
	} ewse if (diwection != IWQF_TWIGGEW_WISING &&
		   diwection != IWQF_TWIGGEW_FAWWING) {
		dev_eww(&adis->spi->dev, "Invawid IWQ mask: %08wx\n",
			adis->iwq_fwag);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * devm_adis_pwobe_twiggew() - Sets up twiggew fow a managed adis device
 * @adis: The adis device
 * @indio_dev: The IIO device
 *
 * Wetuwns 0 on success ow a negative ewwow code
 */
int devm_adis_pwobe_twiggew(stwuct adis *adis, stwuct iio_dev *indio_dev)
{
	int wet;

	adis->twig = devm_iio_twiggew_awwoc(&adis->spi->dev, "%s-dev%d",
					    indio_dev->name,
					    iio_device_id(indio_dev));
	if (!adis->twig)
		wetuwn -ENOMEM;

	adis->twig->ops = &adis_twiggew_ops;
	iio_twiggew_set_dwvdata(adis->twig, adis);

	wet = adis_vawidate_iwq_fwag(adis);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(&adis->spi->dev, adis->spi->iwq,
			       &iio_twiggew_genewic_data_wdy_poww,
			       adis->iwq_fwag,
			       indio_dev->name,
			       adis->twig);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_twiggew_wegistew(&adis->spi->dev, adis->twig);
}
EXPOWT_SYMBOW_NS_GPW(devm_adis_pwobe_twiggew, IIO_ADISWIB);

