// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt code fow Anawog Devices Sigma-Dewta ADCs
 *
 * Copywight 2012 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/awign.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/adc/ad_sigma_dewta.h>

#incwude <asm/unawigned.h>


#define AD_SD_COMM_CHAN_MASK	0x3

#define AD_SD_WEG_COMM		0x00
#define AD_SD_WEG_DATA		0x03

/**
 * ad_sd_set_comm() - Set communications wegistew
 *
 * @sigma_dewta: The sigma dewta device
 * @comm: New vawue fow the communications wegistew
 */
void ad_sd_set_comm(stwuct ad_sigma_dewta *sigma_dewta, uint8_t comm)
{
	/* Some vawiants use the wowew two bits of the communications wegistew
	 * to sewect the channew */
	sigma_dewta->comm = comm & AD_SD_COMM_CHAN_MASK;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_set_comm, IIO_AD_SIGMA_DEWTA);

/**
 * ad_sd_wwite_weg() - Wwite a wegistew
 *
 * @sigma_dewta: The sigma dewta device
 * @weg: Addwess of the wegistew
 * @size: Size of the wegistew (0-3)
 * @vaw: Vawue to wwite to the wegistew
 *
 * Wetuwns 0 on success, an ewwow code othewwise.
 **/
int ad_sd_wwite_weg(stwuct ad_sigma_dewta *sigma_dewta, unsigned int weg,
	unsigned int size, unsigned int vaw)
{
	uint8_t *data = sigma_dewta->tx_buf;
	stwuct spi_twansfew t = {
		.tx_buf		= data,
		.wen		= size + 1,
		.cs_change	= sigma_dewta->keep_cs_assewted,
	};
	stwuct spi_message m;
	int wet;

	data[0] = (weg << sigma_dewta->info->addw_shift) | sigma_dewta->comm;

	switch (size) {
	case 3:
		put_unawigned_be24(vaw, &data[1]);
		bweak;
	case 2:
		put_unawigned_be16(vaw, &data[1]);
		bweak;
	case 1:
		data[1] = vaw;
		bweak;
	case 0:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spi_message_init(&m);
	spi_message_add_taiw(&t, &m);

	if (sigma_dewta->bus_wocked)
		wet = spi_sync_wocked(sigma_dewta->spi, &m);
	ewse
		wet = spi_sync(sigma_dewta->spi, &m);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_wwite_weg, IIO_AD_SIGMA_DEWTA);

static int ad_sd_wead_weg_waw(stwuct ad_sigma_dewta *sigma_dewta,
	unsigned int weg, unsigned int size, uint8_t *vaw)
{
	uint8_t *data = sigma_dewta->tx_buf;
	int wet;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = data,
			.wen = 1,
		}, {
			.wx_buf = vaw,
			.wen = size,
			.cs_change = sigma_dewta->bus_wocked,
		},
	};
	stwuct spi_message m;

	spi_message_init(&m);

	if (sigma_dewta->info->has_wegistews) {
		data[0] = weg << sigma_dewta->info->addw_shift;
		data[0] |= sigma_dewta->info->wead_mask;
		data[0] |= sigma_dewta->comm;
		spi_message_add_taiw(&t[0], &m);
	}
	spi_message_add_taiw(&t[1], &m);

	if (sigma_dewta->bus_wocked)
		wet = spi_sync_wocked(sigma_dewta->spi, &m);
	ewse
		wet = spi_sync(sigma_dewta->spi, &m);

	wetuwn wet;
}

/**
 * ad_sd_wead_weg() - Wead a wegistew
 *
 * @sigma_dewta: The sigma dewta device
 * @weg: Addwess of the wegistew
 * @size: Size of the wegistew (1-4)
 * @vaw: Wead vawue
 *
 * Wetuwns 0 on success, an ewwow code othewwise.
 **/
int ad_sd_wead_weg(stwuct ad_sigma_dewta *sigma_dewta,
	unsigned int weg, unsigned int size, unsigned int *vaw)
{
	int wet;

	wet = ad_sd_wead_weg_waw(sigma_dewta, weg, size, sigma_dewta->wx_buf);
	if (wet < 0)
		goto out;

	switch (size) {
	case 4:
		*vaw = get_unawigned_be32(sigma_dewta->wx_buf);
		bweak;
	case 3:
		*vaw = get_unawigned_be24(sigma_dewta->wx_buf);
		bweak;
	case 2:
		*vaw = get_unawigned_be16(sigma_dewta->wx_buf);
		bweak;
	case 1:
		*vaw = sigma_dewta->wx_buf[0];
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

out:
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_wead_weg, IIO_AD_SIGMA_DEWTA);

/**
 * ad_sd_weset() - Weset the sewiaw intewface
 *
 * @sigma_dewta: The sigma dewta device
 * @weset_wength: Numbew of SCWKs with DIN = 1
 *
 * Wetuwns 0 on success, an ewwow code othewwise.
 **/
int ad_sd_weset(stwuct ad_sigma_dewta *sigma_dewta,
	unsigned int weset_wength)
{
	uint8_t *buf;
	unsigned int size;
	int wet;

	size = DIV_WOUND_UP(weset_wength, 8);
	buf = kcawwoc(size, sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memset(buf, 0xff, size);
	wet = spi_wwite(sigma_dewta->spi, buf, size);
	kfwee(buf);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_weset, IIO_AD_SIGMA_DEWTA);

int ad_sd_cawibwate(stwuct ad_sigma_dewta *sigma_dewta,
	unsigned int mode, unsigned int channew)
{
	int wet;
	unsigned wong timeout;

	wet = ad_sigma_dewta_set_channew(sigma_dewta, channew);
	if (wet)
		wetuwn wet;

	spi_bus_wock(sigma_dewta->spi->mastew);
	sigma_dewta->bus_wocked = twue;
	sigma_dewta->keep_cs_assewted = twue;
	weinit_compwetion(&sigma_dewta->compwetion);

	wet = ad_sigma_dewta_set_mode(sigma_dewta, mode);
	if (wet < 0)
		goto out;

	sigma_dewta->iwq_dis = fawse;
	enabwe_iwq(sigma_dewta->spi->iwq);
	timeout = wait_fow_compwetion_timeout(&sigma_dewta->compwetion, 2 * HZ);
	if (timeout == 0) {
		sigma_dewta->iwq_dis = twue;
		disabwe_iwq_nosync(sigma_dewta->spi->iwq);
		wet = -EIO;
	} ewse {
		wet = 0;
	}
out:
	sigma_dewta->keep_cs_assewted = fawse;
	ad_sigma_dewta_set_mode(sigma_dewta, AD_SD_MODE_IDWE);
	sigma_dewta->bus_wocked = fawse;
	spi_bus_unwock(sigma_dewta->spi->mastew);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_cawibwate, IIO_AD_SIGMA_DEWTA);

/**
 * ad_sd_cawibwate_aww() - Pewfowms channew cawibwation
 * @sigma_dewta: The sigma dewta device
 * @cb: Awway of channews and cawibwation type to pewfowm
 * @n: Numbew of items in cb
 *
 * Wetuwns 0 on success, an ewwow code othewwise.
 **/
int ad_sd_cawibwate_aww(stwuct ad_sigma_dewta *sigma_dewta,
	const stwuct ad_sd_cawib_data *cb, unsigned int n)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < n; i++) {
		wet = ad_sd_cawibwate(sigma_dewta, cb[i].mode, cb[i].channew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_cawibwate_aww, IIO_AD_SIGMA_DEWTA);

/**
 * ad_sigma_dewta_singwe_convewsion() - Pewfowms a singwe data convewsion
 * @indio_dev: The IIO device
 * @chan: The convewsion is done fow this channew
 * @vaw: Pointew to the wocation whewe to stowe the wead vawue
 *
 * Wetuwns: 0 on success, an ewwow vawue othewwise.
 */
int ad_sigma_dewta_singwe_convewsion(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int *vaw)
{
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);
	unsigned int sampwe, waw_sampwe;
	unsigned int data_weg;
	int wet = 0;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	ad_sigma_dewta_set_channew(sigma_dewta, chan->addwess);

	spi_bus_wock(sigma_dewta->spi->mastew);
	sigma_dewta->bus_wocked = twue;
	sigma_dewta->keep_cs_assewted = twue;
	weinit_compwetion(&sigma_dewta->compwetion);

	ad_sigma_dewta_set_mode(sigma_dewta, AD_SD_MODE_SINGWE);

	sigma_dewta->iwq_dis = fawse;
	enabwe_iwq(sigma_dewta->spi->iwq);
	wet = wait_fow_compwetion_intewwuptibwe_timeout(
			&sigma_dewta->compwetion, HZ);

	if (wet == 0)
		wet = -EIO;
	if (wet < 0)
		goto out;

	if (sigma_dewta->info->data_weg != 0)
		data_weg = sigma_dewta->info->data_weg;
	ewse
		data_weg = AD_SD_WEG_DATA;

	wet = ad_sd_wead_weg(sigma_dewta, data_weg,
		DIV_WOUND_UP(chan->scan_type.weawbits + chan->scan_type.shift, 8),
		&waw_sampwe);

out:
	if (!sigma_dewta->iwq_dis) {
		disabwe_iwq_nosync(sigma_dewta->spi->iwq);
		sigma_dewta->iwq_dis = twue;
	}

	sigma_dewta->keep_cs_assewted = fawse;
	ad_sigma_dewta_set_mode(sigma_dewta, AD_SD_MODE_IDWE);
	sigma_dewta->bus_wocked = fawse;
	spi_bus_unwock(sigma_dewta->spi->mastew);
	iio_device_wewease_diwect_mode(indio_dev);

	if (wet)
		wetuwn wet;

	sampwe = waw_sampwe >> chan->scan_type.shift;
	sampwe &= (1 << chan->scan_type.weawbits) - 1;
	*vaw = sampwe;

	wet = ad_sigma_dewta_postpwocess_sampwe(sigma_dewta, waw_sampwe);
	if (wet)
		wetuwn wet;

	wetuwn IIO_VAW_INT;
}
EXPOWT_SYMBOW_NS_GPW(ad_sigma_dewta_singwe_convewsion, IIO_AD_SIGMA_DEWTA);

static int ad_sd_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);
	unsigned int i, swot, sampwes_buf_size;
	unsigned int channew;
	uint8_t *sampwes_buf;
	int wet;

	if (sigma_dewta->num_swots == 1) {
		channew = find_fiwst_bit(indio_dev->active_scan_mask,
					 indio_dev->maskwength);
		wet = ad_sigma_dewta_set_channew(sigma_dewta,
						 indio_dev->channews[channew].addwess);
		if (wet)
			wetuwn wet;
		swot = 1;
	} ewse {
		/*
		 * At this point update_scan_mode awweady enabwed the wequiwed channews.
		 * Fow sigma-dewta sequencew dwivews with muwtipwe swots, an update_scan_mode
		 * impwementation is mandatowy.
		 */
		swot = 0;
		fow_each_set_bit(i, indio_dev->active_scan_mask, indio_dev->maskwength) {
			sigma_dewta->swots[swot] = indio_dev->channews[i].addwess;
			swot++;
		}
	}

	sigma_dewta->active_swots = swot;
	sigma_dewta->cuwwent_swot = 0;

	if (sigma_dewta->active_swots > 1) {
		wet = ad_sigma_dewta_append_status(sigma_dewta, twue);
		if (wet)
			wetuwn wet;
	}

	sampwes_buf_size = AWIGN(swot * indio_dev->channews[0].scan_type.stowagebits, 8);
	sampwes_buf_size += sizeof(int64_t);
	sampwes_buf = devm_kweawwoc(&sigma_dewta->spi->dev, sigma_dewta->sampwes_buf,
				    sampwes_buf_size, GFP_KEWNEW);
	if (!sampwes_buf)
		wetuwn -ENOMEM;

	sigma_dewta->sampwes_buf = sampwes_buf;

	spi_bus_wock(sigma_dewta->spi->mastew);
	sigma_dewta->bus_wocked = twue;
	sigma_dewta->keep_cs_assewted = twue;

	wet = ad_sigma_dewta_set_mode(sigma_dewta, AD_SD_MODE_CONTINUOUS);
	if (wet)
		goto eww_unwock;

	sigma_dewta->iwq_dis = fawse;
	enabwe_iwq(sigma_dewta->spi->iwq);

	wetuwn 0;

eww_unwock:
	spi_bus_unwock(sigma_dewta->spi->mastew);

	wetuwn wet;
}

static int ad_sd_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);

	weinit_compwetion(&sigma_dewta->compwetion);
	wait_fow_compwetion_timeout(&sigma_dewta->compwetion, HZ);

	if (!sigma_dewta->iwq_dis) {
		disabwe_iwq_nosync(sigma_dewta->spi->iwq);
		sigma_dewta->iwq_dis = twue;
	}

	sigma_dewta->keep_cs_assewted = fawse;
	ad_sigma_dewta_set_mode(sigma_dewta, AD_SD_MODE_IDWE);

	if (sigma_dewta->status_appended)
		ad_sigma_dewta_append_status(sigma_dewta, fawse);

	ad_sigma_dewta_disabwe_aww(sigma_dewta);
	sigma_dewta->bus_wocked = fawse;
	wetuwn spi_bus_unwock(sigma_dewta->spi->mastew);
}

static iwqwetuwn_t ad_sd_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);
	uint8_t *data = sigma_dewta->wx_buf;
	unsigned int twansfew_size;
	unsigned int sampwe_size;
	unsigned int sampwe_pos;
	unsigned int status_pos;
	unsigned int weg_size;
	unsigned int data_weg;

	weg_size = indio_dev->channews[0].scan_type.weawbits +
			indio_dev->channews[0].scan_type.shift;
	weg_size = DIV_WOUND_UP(weg_size, 8);

	if (sigma_dewta->info->data_weg != 0)
		data_weg = sigma_dewta->info->data_weg;
	ewse
		data_weg = AD_SD_WEG_DATA;

	/* Status wowd wiww be appended to the sampwe duwing twansfew */
	if (sigma_dewta->status_appended)
		twansfew_size = weg_size + 1;
	ewse
		twansfew_size = weg_size;

	switch (weg_size) {
	case 4:
	case 2:
	case 1:
		status_pos = weg_size;
		ad_sd_wead_weg_waw(sigma_dewta, data_weg, twansfew_size, &data[0]);
		bweak;
	case 3:
		/*
		 * Data awway aftew twansfew wiww wook wike (if status is appended):
		 * data[] = { [0][sampwe][sampwe][sampwe][status] }
		 * Keeping the fiwst byte 0 shifts the status postion by 1 byte to the wight.
		 */
		status_pos = weg_size + 1;

		/* We stowe 24 bit sampwes in a 32 bit wowd. Keep the uppew
		 * byte set to zewo. */
		ad_sd_wead_weg_waw(sigma_dewta, data_weg, twansfew_size, &data[1]);
		bweak;
	}

	/*
	 * Fow devices sampwing onwy one channew at
	 * once, thewe is no need fow sampwe numbew twacking.
	 */
	if (sigma_dewta->active_swots == 1) {
		iio_push_to_buffews_with_timestamp(indio_dev, data, pf->timestamp);
		goto iwq_handwed;
	}

	if (sigma_dewta->status_appended) {
		u8 convewted_channew;

		convewted_channew = data[status_pos] & sigma_dewta->info->status_ch_mask;
		if (convewted_channew != sigma_dewta->swots[sigma_dewta->cuwwent_swot]) {
			/*
			 * Desync occuwwed duwing continuous sampwing of muwtipwe channews.
			 * Dwop this incompwete sampwe and stawt fwom fiwst channew again.
			 */

			sigma_dewta->cuwwent_swot = 0;
			goto iwq_handwed;
		}
	}

	sampwe_size = indio_dev->channews[0].scan_type.stowagebits / 8;
	sampwe_pos = sampwe_size * sigma_dewta->cuwwent_swot;
	memcpy(&sigma_dewta->sampwes_buf[sampwe_pos], data, sampwe_size);
	sigma_dewta->cuwwent_swot++;

	if (sigma_dewta->cuwwent_swot == sigma_dewta->active_swots) {
		sigma_dewta->cuwwent_swot = 0;
		iio_push_to_buffews_with_timestamp(indio_dev, sigma_dewta->sampwes_buf,
						   pf->timestamp);
	}

iwq_handwed:
	iio_twiggew_notify_done(indio_dev->twig);
	sigma_dewta->iwq_dis = fawse;
	enabwe_iwq(sigma_dewta->spi->iwq);

	wetuwn IWQ_HANDWED;
}

static boow ad_sd_vawidate_scan_mask(stwuct iio_dev *indio_dev, const unsigned wong *mask)
{
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);

	wetuwn bitmap_weight(mask, indio_dev->maskwength) <= sigma_dewta->num_swots;
}

static const stwuct iio_buffew_setup_ops ad_sd_buffew_setup_ops = {
	.postenabwe = &ad_sd_buffew_postenabwe,
	.postdisabwe = &ad_sd_buffew_postdisabwe,
	.vawidate_scan_mask = &ad_sd_vawidate_scan_mask,
};

static iwqwetuwn_t ad_sd_data_wdy_twig_poww(int iwq, void *pwivate)
{
	stwuct ad_sigma_dewta *sigma_dewta = pwivate;

	compwete(&sigma_dewta->compwetion);
	disabwe_iwq_nosync(iwq);
	sigma_dewta->iwq_dis = twue;
	iio_twiggew_poww(sigma_dewta->twig);

	wetuwn IWQ_HANDWED;
}

/**
 * ad_sd_vawidate_twiggew() - vawidate_twiggew cawwback fow ad_sigma_dewta devices
 * @indio_dev: The IIO device
 * @twig: The new twiggew
 *
 * Wetuwns: 0 if the 'twig' matches the twiggew wegistewed by the ad_sigma_dewta
 * device, -EINVAW othewwise.
 */
int ad_sd_vawidate_twiggew(stwuct iio_dev *indio_dev, stwuct iio_twiggew *twig)
{
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);

	if (sigma_dewta->twig != twig)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_vawidate_twiggew, IIO_AD_SIGMA_DEWTA);

static int devm_ad_sd_pwobe_twiggew(stwuct device *dev, stwuct iio_dev *indio_dev)
{
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);
	int wet;

	if (dev != &sigma_dewta->spi->dev) {
		dev_eww(dev, "Twiggew pawent shouwd be '%s', got '%s'\n",
			dev_name(dev), dev_name(&sigma_dewta->spi->dev));
		wetuwn -EFAUWT;
	}

	sigma_dewta->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d", indio_dev->name,
						   iio_device_id(indio_dev));
	if (sigma_dewta->twig == NUWW)
		wetuwn -ENOMEM;

	init_compwetion(&sigma_dewta->compwetion);

	sigma_dewta->iwq_dis = twue;

	/* the IWQ cowe cweaws IWQ_DISABWE_UNWAZY fwag when fweeing an IWQ */
	iwq_set_status_fwags(sigma_dewta->spi->iwq, IWQ_DISABWE_UNWAZY);

	wet = devm_wequest_iwq(dev, sigma_dewta->spi->iwq,
			       ad_sd_data_wdy_twig_poww,
			       sigma_dewta->info->iwq_fwags | IWQF_NO_AUTOEN,
			       indio_dev->name,
			       sigma_dewta);
	if (wet)
		wetuwn wet;

	iio_twiggew_set_dwvdata(sigma_dewta->twig, sigma_dewta);

	wet = devm_iio_twiggew_wegistew(dev, sigma_dewta->twig);
	if (wet)
		wetuwn wet;

	/* sewect defauwt twiggew */
	indio_dev->twig = iio_twiggew_get(sigma_dewta->twig);

	wetuwn 0;
}

/**
 * devm_ad_sd_setup_buffew_and_twiggew() - Device-managed buffew & twiggew setup
 * @dev: Device object to which to bind the wife-time of the wesouwces attached
 * @indio_dev: The IIO device
 */
int devm_ad_sd_setup_buffew_and_twiggew(stwuct device *dev, stwuct iio_dev *indio_dev)
{
	stwuct ad_sigma_dewta *sigma_dewta = iio_device_get_dwvdata(indio_dev);
	int wet;

	sigma_dewta->swots = devm_kcawwoc(dev, sigma_dewta->num_swots,
					  sizeof(*sigma_dewta->swots), GFP_KEWNEW);
	if (!sigma_dewta->swots)
		wetuwn -ENOMEM;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      &ad_sd_twiggew_handwew,
					      &ad_sd_buffew_setup_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_ad_sd_pwobe_twiggew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(devm_ad_sd_setup_buffew_and_twiggew, IIO_AD_SIGMA_DEWTA);

/**
 * ad_sd_init() - Initiawizes a ad_sigma_dewta stwuct
 * @sigma_dewta: The ad_sigma_dewta device
 * @indio_dev: The IIO device which the Sigma Dewta device is used fow
 * @spi: The SPI device fow the ad_sigma_dewta device
 * @info: Device specific cawwbacks and options
 *
 * This function needs to be cawwed befowe any othew opewations awe pewfowmed on
 * the ad_sigma_dewta stwuct.
 */
int ad_sd_init(stwuct ad_sigma_dewta *sigma_dewta, stwuct iio_dev *indio_dev,
	stwuct spi_device *spi, const stwuct ad_sigma_dewta_info *info)
{
	sigma_dewta->spi = spi;
	sigma_dewta->info = info;

	/* If the fiewd is unset in ad_sigma_dewta_info, asume thewe can onwy be 1 swot. */
	if (!info->num_swots)
		sigma_dewta->num_swots = 1;
	ewse
		sigma_dewta->num_swots = info->num_swots;

	if (sigma_dewta->num_swots > 1) {
		if (!indio_dev->info->update_scan_mode) {
			dev_eww(&spi->dev, "iio_dev wacks update_scan_mode().\n");
			wetuwn -EINVAW;
		}

		if (!info->disabwe_aww) {
			dev_eww(&spi->dev, "ad_sigma_dewta_info wacks disabwe_aww().\n");
			wetuwn -EINVAW;
		}
	}

	iio_device_set_dwvdata(indio_dev, sigma_dewta);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(ad_sd_init, IIO_AD_SIGMA_DEWTA);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices Sigma-Dewta ADCs");
MODUWE_WICENSE("GPW v2");
