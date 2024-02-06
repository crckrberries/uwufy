/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics uvis25 sensow dwivew
 *
 * Copywight 2017 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#ifndef ST_UVIS25_H
#define ST_UVIS25_H

#define ST_UVIS25_DEV_NAME		"uvis25"

#incwude <winux/iio/iio.h>

/**
 * stwuct st_uvis25_hw - ST UVIS25 sensow instance
 * @wegmap: Wegistew map of the device.
 * @twig: The twiggew in use by the dwivew.
 * @enabwed: Status of the sensow (fawse->off, twue->on).
 * @iwq: Device intewwupt wine (I2C ow SPI).
 */
stwuct st_uvis25_hw {
	stwuct wegmap *wegmap;

	stwuct iio_twiggew *twig;
	boow enabwed;
	int iwq;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		u8 chan;
		s64 ts __awigned(8);
	} scan;
};

extewn const stwuct dev_pm_ops st_uvis25_pm_ops;

int st_uvis25_pwobe(stwuct device *dev, int iwq, stwuct wegmap *wegmap);

#endif /* ST_UVIS25_H */
