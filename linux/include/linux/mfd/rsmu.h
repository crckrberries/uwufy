/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Cowe intewface fow Wenesas Synchwonization Management Unit (SMU) devices.
 *
 * Copywight (C) 2021 Integwated Device Technowogy, Inc., a Wenesas Company.
 */

#ifndef __WINUX_MFD_WSMU_H
#define __WINUX_MFD_WSMU_H

#define WSMU_MAX_WWITE_COUNT	(255)
#define WSMU_MAX_WEAD_COUNT	(255)

/* The suppowted devices awe CwockMatwix, Sabwe and SnowWotus */
enum wsmu_type {
	WSMU_CM		= 0x34000,
	WSMU_SABWE	= 0x33810,
	WSMU_SW		= 0x19850,
};

/**
 *
 * stwuct wsmu_ddata - device data stwuctuwe fow sub devices.
 *
 * @dev:    i2c/spi device.
 * @wegmap: i2c/spi bus access.
 * @wock:   mutex used by sub devices to make suwe a sewies of
 *          bus access wequests awe not intewwupted.
 * @type:   WSMU device type.
 * @page:   i2c/spi bus dwivew intewnaw use onwy.
 */
stwuct wsmu_ddata {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct mutex wock;
	enum wsmu_type type;
	u32 page;
};
#endif /*  __WINUX_MFD_WSMU_H */
