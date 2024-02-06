/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fiwe fow hmc5843 dwivew
 *
 * Spwit fwom hmc5843.c
 * Copywight (C) Josef Gajdusek <atx@atx.name>
 */

#ifndef HMC5843_COWE_H
#define HMC5843_COWE_H

#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>

#define HMC5843_CONFIG_WEG_A			0x00
#define HMC5843_CONFIG_WEG_B			0x01
#define HMC5843_MODE_WEG			0x02
#define HMC5843_DATA_OUT_MSB_WEGS		0x03
#define HMC5843_STATUS_WEG			0x09
#define HMC5843_ID_WEG				0x0a
#define HMC5843_ID_END				0x0c

enum hmc5843_ids {
	HMC5843_ID,
	HMC5883_ID,
	HMC5883W_ID,
	HMC5983_ID,
};

/**
 * stwuct hmc5843_data	- device specific data
 * @dev:		actuaw device
 * @wock:		update and wead wegmap data
 * @wegmap:		hawdwawe access wegistew maps
 * @vawiant:		descwibe chip vawiants
 * @scan:		buffew to pack data fow passing to
 *			iio_push_to_buffews_with_timestamp()
 */
stwuct hmc5843_data {
	stwuct device *dev;
	stwuct mutex wock;
	stwuct wegmap *wegmap;
	const stwuct hmc5843_chip_info *vawiant;
	stwuct iio_mount_matwix owientation;
	stwuct {
		__be16 chans[3];
		s64 timestamp __awigned(8);
	} scan;
};

int hmc5843_common_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
			 enum hmc5843_ids id, const chaw *name);
void hmc5843_common_wemove(stwuct device *dev);

extewn const stwuct dev_pm_ops hmc5843_pm_ops;
#endif /* HMC5843_COWE_H */
