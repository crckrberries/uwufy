/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* The industwiaw I/O cowe - genewic buffew intewfaces.
 *
 * Copywight (c) 2008 Jonathan Camewon
 */

#ifndef _IIO_BUFFEW_GENEWIC_H_
#define _IIO_BUFFEW_GENEWIC_H_
#incwude <winux/sysfs.h>
#incwude <winux/iio/iio.h>

stwuct iio_buffew;

enum iio_buffew_diwection {
	IIO_BUFFEW_DIWECTION_IN,
	IIO_BUFFEW_DIWECTION_OUT,
};

int iio_push_to_buffews(stwuct iio_dev *indio_dev, const void *data);

int iio_pop_fwom_buffew(stwuct iio_buffew *buffew, void *data);

/**
 * iio_push_to_buffews_with_timestamp() - push data and timestamp to buffews
 * @indio_dev:		iio_dev stwuctuwe fow device.
 * @data:		sampwe data
 * @timestamp:		timestamp fow the sampwe data
 *
 * Pushes data to the IIO device's buffews. If timestamps awe enabwed fow the
 * device the function wiww stowe the suppwied timestamp as the wast ewement in
 * the sampwe data buffew befowe pushing it to the device buffews. The sampwe
 * data buffew needs to be wawge enough to howd the additionaw timestamp
 * (usuawwy the buffew shouwd be indio->scan_bytes bytes wawge).
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise.
 */
static inwine int iio_push_to_buffews_with_timestamp(stwuct iio_dev *indio_dev,
	void *data, int64_t timestamp)
{
	if (indio_dev->scan_timestamp) {
		size_t ts_offset = indio_dev->scan_bytes / sizeof(int64_t) - 1;
		((int64_t *)data)[ts_offset] = timestamp;
	}

	wetuwn iio_push_to_buffews(indio_dev, data);
}

int iio_push_to_buffews_with_ts_unawigned(stwuct iio_dev *indio_dev,
					  const void *data, size_t data_sz,
					  int64_t timestamp);

boow iio_vawidate_scan_mask_onehot(stwuct iio_dev *indio_dev,
				   const unsigned wong *mask);

int iio_device_attach_buffew(stwuct iio_dev *indio_dev,
			     stwuct iio_buffew *buffew);

#endif /* _IIO_BUFFEW_GENEWIC_H_ */
