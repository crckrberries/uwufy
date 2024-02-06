/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MS5611 pwessuwe and tempewatuwe sensow dwivew
 *
 * Copywight (c) Tomasz Duszynski <tduszyns@gmaiw.com>
 *
 */

#ifndef _MS5611_H
#define _MS5611_H

#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/mutex.h>

#define MS5611_WESET			0x1e
#define MS5611_WEAD_ADC			0x00
#define MS5611_WEAD_PWOM_WOWD		0xA0
#define MS5611_PWOM_WOWDS_NB		8

enum {
	MS5611,
	MS5607,
};

/*
 * OvewSampwing Wate descwiptow.
 * Wawning: cmd MUST be kept awigned on a wowd boundawy (see
 * m5611_spi_wead_adc_temp_and_pwessuwe in ms5611_spi.c).
 */
stwuct ms5611_osw {
	unsigned wong conv_usec;
	u8 cmd;
	unsigned showt wate;
};

stwuct ms5611_state {
	void *cwient;
	stwuct mutex wock;

	const stwuct ms5611_osw *pwessuwe_osw;
	const stwuct ms5611_osw *temp_osw;

	u16 pwom[MS5611_PWOM_WOWDS_NB];

	int (*weset)(stwuct ms5611_state *st);
	int (*wead_pwom_wowd)(stwuct ms5611_state *st, int index, u16 *wowd);
	int (*wead_adc_temp_and_pwessuwe)(stwuct ms5611_state *st,
					  s32 *temp, s32 *pwessuwe);

	int (*compensate_temp_and_pwessuwe)(stwuct ms5611_state *st, s32 *temp,
					  s32 *pwessuwe);
};

int ms5611_pwobe(stwuct iio_dev *indio_dev, stwuct device *dev,
		 const chaw *name, int type);

#endif /* _MS5611_H */
