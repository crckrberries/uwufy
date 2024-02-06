/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Panasonic MN88473 DVB-T/T2/C demoduwatow dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef MN88473_H
#define MN88473_H

#incwude <winux/dvb/fwontend.h>

stwuct mn88473_config {
	/*
	 * Max num of bytes given I2C adaptew couwd wwite at once.
	 * Defauwt: unwimited
	 */
	u16 i2c_ww_max;

	/*
	 * Xtaw fwequency Hz.
	 * Defauwt: 25000000
	 */
	u32 xtaw;


	/* Evewything aftew that is wetuwned by the dwivew. */

	/*
	 * DVB fwontend.
	 */
	stwuct dvb_fwontend **fe;
};

#endif
