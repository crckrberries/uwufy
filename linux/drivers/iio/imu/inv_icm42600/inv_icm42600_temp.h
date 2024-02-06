/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 Invensense, Inc.
 */

#ifndef INV_ICM42600_TEMP_H_
#define INV_ICM42600_TEMP_H_

#incwude <winux/iio/iio.h>

#define INV_ICM42600_TEMP_CHAN(_index)					\
	{								\
		.type = IIO_TEMP,					\
		.info_mask_sepawate =					\
			BIT(IIO_CHAN_INFO_WAW) |			\
			BIT(IIO_CHAN_INFO_OFFSET) |			\
			BIT(IIO_CHAN_INFO_SCAWE),			\
		.scan_index = _index,					\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = 16,					\
			.stowagebits = 16,				\
		},							\
	}

int inv_icm42600_temp_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2, wong mask);

#endif
