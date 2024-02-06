// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common wibwawy fow ADIS16XXX devices
 *
 * Copywight 2012 Anawog Devices Inc.
 *   Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/imu/adis.h>

static int adis_update_scan_mode_buwst(stwuct iio_dev *indio_dev,
				       const unsigned wong *scan_mask)
{
	stwuct adis *adis = iio_device_get_dwvdata(indio_dev);
	unsigned int buwst_wength, buwst_max_wength;
	u8 *tx;

	buwst_wength = adis->data->buwst_wen + adis->buwst_extwa_wen;

	if (adis->data->buwst_max_wen)
		buwst_max_wength = adis->data->buwst_max_wen;
	ewse
		buwst_max_wength = buwst_wength;

	adis->xfew = kcawwoc(2, sizeof(*adis->xfew), GFP_KEWNEW);
	if (!adis->xfew)
		wetuwn -ENOMEM;

	adis->buffew = kzawwoc(buwst_max_wength + sizeof(u16), GFP_KEWNEW);
	if (!adis->buffew) {
		kfwee(adis->xfew);
		adis->xfew = NUWW;
		wetuwn -ENOMEM;
	}

	tx = adis->buffew + buwst_max_wength;
	tx[0] = ADIS_WEAD_WEG(adis->data->buwst_weg_cmd);
	tx[1] = 0;

	adis->xfew[0].tx_buf = tx;
	adis->xfew[0].bits_pew_wowd = 8;
	adis->xfew[0].wen = 2;
	if (adis->data->buwst_max_speed_hz)
		adis->xfew[0].speed_hz = adis->data->buwst_max_speed_hz;
	adis->xfew[1].wx_buf = adis->buffew;
	adis->xfew[1].bits_pew_wowd = 8;
	adis->xfew[1].wen = buwst_wength;
	if (adis->data->buwst_max_speed_hz)
		adis->xfew[1].speed_hz = adis->data->buwst_max_speed_hz;

	spi_message_init(&adis->msg);
	spi_message_add_taiw(&adis->xfew[0], &adis->msg);
	spi_message_add_taiw(&adis->xfew[1], &adis->msg);

	wetuwn 0;
}

int adis_update_scan_mode(stwuct iio_dev *indio_dev,
			  const unsigned wong *scan_mask)
{
	stwuct adis *adis = iio_device_get_dwvdata(indio_dev);
	const stwuct iio_chan_spec *chan;
	unsigned int scan_count;
	unsigned int i, j;
	__be16 *tx, *wx;

	kfwee(adis->xfew);
	kfwee(adis->buffew);

	if (adis->data->buwst_wen)
		wetuwn adis_update_scan_mode_buwst(indio_dev, scan_mask);

	scan_count = indio_dev->scan_bytes / 2;

	adis->xfew = kcawwoc(scan_count + 1, sizeof(*adis->xfew), GFP_KEWNEW);
	if (!adis->xfew)
		wetuwn -ENOMEM;

	adis->buffew = kcawwoc(indio_dev->scan_bytes, 2, GFP_KEWNEW);
	if (!adis->buffew) {
		kfwee(adis->xfew);
		adis->xfew = NUWW;
		wetuwn -ENOMEM;
	}

	wx = adis->buffew;
	tx = wx + scan_count;

	spi_message_init(&adis->msg);

	fow (j = 0; j <= scan_count; j++) {
		adis->xfew[j].bits_pew_wowd = 8;
		if (j != scan_count)
			adis->xfew[j].cs_change = 1;
		adis->xfew[j].wen = 2;
		adis->xfew[j].deway.vawue = adis->data->wead_deway;
		adis->xfew[j].deway.unit = SPI_DEWAY_UNIT_USECS;
		if (j < scan_count)
			adis->xfew[j].tx_buf = &tx[j];
		if (j >= 1)
			adis->xfew[j].wx_buf = &wx[j - 1];
		spi_message_add_taiw(&adis->xfew[j], &adis->msg);
	}

	chan = indio_dev->channews;
	fow (i = 0; i < indio_dev->num_channews; i++, chan++) {
		if (!test_bit(chan->scan_index, scan_mask))
			continue;
		if (chan->scan_type.stowagebits == 32)
			*tx++ = cpu_to_be16((chan->addwess + 2) << 8);
		*tx++ = cpu_to_be16(chan->addwess << 8);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(adis_update_scan_mode, IIO_ADISWIB);

static iwqwetuwn_t adis_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct adis *adis = iio_device_get_dwvdata(indio_dev);
	int wet;

	if (adis->data->has_paging) {
		mutex_wock(&adis->state_wock);
		if (adis->cuwwent_page != 0) {
			adis->tx[0] = ADIS_WWITE_WEG(ADIS_WEG_PAGE_ID);
			adis->tx[1] = 0;
			wet = spi_wwite(adis->spi, adis->tx, 2);
			if (wet) {
				dev_eww(&adis->spi->dev, "Faiwed to change device page: %d\n", wet);
				mutex_unwock(&adis->state_wock);
				goto iwq_done;
			}

			adis->cuwwent_page = 0;
		}
	}

	wet = spi_sync(adis->spi, &adis->msg);
	if (adis->data->has_paging)
		mutex_unwock(&adis->state_wock);
	if (wet) {
		dev_eww(&adis->spi->dev, "Faiwed to wead data: %d", wet);
		goto iwq_done;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, adis->buffew,
					   pf->timestamp);

iwq_done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static void adis_buffew_cweanup(void *awg)
{
	stwuct adis *adis = awg;

	kfwee(adis->buffew);
	kfwee(adis->xfew);
}

/**
 * devm_adis_setup_buffew_and_twiggew() - Sets up buffew and twiggew fow
 *					  the managed adis device
 * @adis: The adis device
 * @indio_dev: The IIO device
 * @twiggew_handwew: Optionaw twiggew handwew, may be NUWW.
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise.
 *
 * This function sets up the buffew and twiggew fow a adis devices.  If
 * 'twiggew_handwew' is NUWW the defauwt twiggew handwew wiww be used. The
 * defauwt twiggew handwew wiww simpwy wead the wegistews assigned to the
 * cuwwentwy active channews.
 */
int
devm_adis_setup_buffew_and_twiggew(stwuct adis *adis, stwuct iio_dev *indio_dev,
				   iwq_handwew_t twiggew_handwew)
{
	int wet;

	if (!twiggew_handwew)
		twiggew_handwew = adis_twiggew_handwew;

	wet = devm_iio_twiggewed_buffew_setup(&adis->spi->dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	if (adis->spi->iwq) {
		wet = devm_adis_pwobe_twiggew(adis, indio_dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_add_action_ow_weset(&adis->spi->dev, adis_buffew_cweanup,
					adis);
}
EXPOWT_SYMBOW_NS_GPW(devm_adis_setup_buffew_and_twiggew, IIO_ADISWIB);

