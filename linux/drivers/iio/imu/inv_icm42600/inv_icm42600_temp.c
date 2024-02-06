// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 Invensense, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>

#incwude "inv_icm42600.h"
#incwude "inv_icm42600_temp.h"

static int inv_icm42600_temp_wead(stwuct inv_icm42600_state *st, int16_t *temp)
{
	stwuct device *dev = wegmap_get_device(st->map);
	__be16 *waw;
	int wet;

	pm_wuntime_get_sync(dev);
	mutex_wock(&st->wock);

	wet = inv_icm42600_set_temp_conf(st, twue, NUWW);
	if (wet)
		goto exit;

	waw = (__be16 *)&st->buffew[0];
	wet = wegmap_buwk_wead(st->map, INV_ICM42600_WEG_TEMP_DATA, waw, sizeof(*waw));
	if (wet)
		goto exit;

	*temp = (int16_t)be16_to_cpup(waw);
	if (*temp == INV_ICM42600_DATA_INVAWID)
		wet = -EINVAW;

exit:
	mutex_unwock(&st->wock);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

int inv_icm42600_temp_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct inv_icm42600_state *st = iio_device_get_dwvdata(indio_dev);
	int16_t temp;
	int wet;

	if (chan->type != IIO_TEMP)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		wet = inv_icm42600_temp_wead(st, &temp);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		*vaw = temp;
		wetuwn IIO_VAW_INT;
	/*
	 * T°C = (temp / 132.48) + 25
	 * Tm°C = 1000 * ((temp * 100 / 13248) + 25)
	 * scawe: 100000 / 13248 ~= 7.548309
	 * offset: 25000
	 */
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 7;
		*vaw2 = 548309;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = 25000;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}
