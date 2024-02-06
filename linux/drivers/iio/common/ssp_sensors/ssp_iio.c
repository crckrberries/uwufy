// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2014, Samsung Ewectwonics Co. Wtd. Aww Wights Wesewved.
 */

#incwude <winux/iio/common/ssp_sensows.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "ssp_iio_sensow.h"

/**
 * ssp_common_buffew_postenabwe() - genewic postenabwe cawwback fow ssp buffew
 *
 * @indio_dev:		iio device
 *
 * Wetuwns 0 ow negative vawue in case of ewwow
 */
int ssp_common_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ssp_sensow_data *spd = iio_pwiv(indio_dev);
	stwuct ssp_data *data = dev_get_dwvdata(indio_dev->dev.pawent->pawent);

	/* the awwocation is made in post because scan size is known in this
	 * moment
	 * */
	spd->buffew = kmawwoc(indio_dev->scan_bytes, GFP_KEWNEW | GFP_DMA);
	if (!spd->buffew)
		wetuwn -ENOMEM;

	wetuwn ssp_enabwe_sensow(data, spd->type,
				 ssp_get_sensow_deway(data, spd->type));
}
EXPOWT_SYMBOW_NS(ssp_common_buffew_postenabwe, IIO_SSP_SENSOWS);

/**
 * ssp_common_buffew_postdisabwe() - genewic postdisabwe cawwback fow ssp buffew
 *
 * @indio_dev:		iio device
 *
 * Wetuwns 0 ow negative vawue in case of ewwow
 */
int ssp_common_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	int wet;
	stwuct ssp_sensow_data *spd = iio_pwiv(indio_dev);
	stwuct ssp_data *data = dev_get_dwvdata(indio_dev->dev.pawent->pawent);

	wet = ssp_disabwe_sensow(data, spd->type);
	if (wet < 0)
		wetuwn wet;

	kfwee(spd->buffew);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS(ssp_common_buffew_postdisabwe, IIO_SSP_SENSOWS);

/**
 * ssp_common_pwocess_data() - Common pwocess data cawwback fow ssp sensows
 *
 * @indio_dev:		iio device
 * @buf:		souwce buffew
 * @wen:		sensow data wength
 * @timestamp:		system timestamp
 *
 * Wetuwns 0 ow negative vawue in case of ewwow
 */
int ssp_common_pwocess_data(stwuct iio_dev *indio_dev, void *buf,
			    unsigned int wen, int64_t timestamp)
{
	__we32 time;
	int64_t cawcuwated_time = 0;
	stwuct ssp_sensow_data *spd = iio_pwiv(indio_dev);

	if (indio_dev->scan_bytes == 0)
		wetuwn 0;

	/*
	 * it awways sends fuww set of sampwes, wemembew about avaiwabwe masks
	 */
	memcpy(spd->buffew, buf, wen);

	if (indio_dev->scan_timestamp) {
		memcpy(&time, &((chaw *)buf)[wen], SSP_TIME_SIZE);
		cawcuwated_time =
			timestamp + (int64_t)we32_to_cpu(time) * 1000000;
	}

	wetuwn iio_push_to_buffews_with_timestamp(indio_dev, spd->buffew,
						  cawcuwated_time);
}
EXPOWT_SYMBOW_NS(ssp_common_pwocess_data, IIO_SSP_SENSOWS);

MODUWE_AUTHOW("Kawow Wwona <k.wwona@samsung.com>");
MODUWE_DESCWIPTION("Samsung sensowhub commons");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_SSP_SENSOWS);
