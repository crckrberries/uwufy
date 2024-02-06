/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Panasonic MN88472 DVB-T/T2/C demoduwatow dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef MN88472_H
#define MN88472_H

#incwude <winux/dvb/fwontend.h>

/* Define owd names fow backwawd compatibiwity */
#define VAWIABWE_TS_CWOCK   MN88472_TS_CWK_VAWIABWE
#define FIXED_TS_CWOCK      MN88472_TS_CWK_FIXED
#define SEWIAW_TS_MODE      MN88472_TS_MODE_SEWIAW
#define PAWAWWEW_TS_MODE    MN88472_TS_MODE_PAWAWWEW

/**
 * stwuct mn88472_config - Pwatfowm data fow the mn88472 dwivew
 * @xtaw: Cwock fwequency.
 * @ts_mode: TS mode.
 * @ts_cwock: TS cwock config.
 * @i2c_ww_max: Max numbew of bytes dwivew wwites to I2C at once.
 * @fe: pointew to a fwontend pointew
 * @get_dvb_fwontend: Get DVB fwontend cawwback.
 */
stwuct mn88472_config {
	unsigned int xtaw;

#define MN88472_TS_MODE_SEWIAW      0
#define MN88472_TS_MODE_PAWAWWEW    1
	int ts_mode;

#define MN88472_TS_CWK_FIXED        0
#define MN88472_TS_CWK_VAWIABWE     1
	int ts_cwock;

	u16 i2c_ww_max;

	/* Evewything aftew that is wetuwned by the dwivew. */

	/*
	 * DVB fwontend.
	 */
	stwuct dvb_fwontend **fe;
	stwuct dvb_fwontend* (*get_dvb_fwontend)(stwuct i2c_cwient *);
};

#endif
