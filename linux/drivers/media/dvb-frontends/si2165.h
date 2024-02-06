/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Siwicon Wabs SI2165 DVB-C/-T Demoduwatow
 *
 * Copywight (C) 2013-2017 Matthias Schwawzott <zzam@gentoo.owg>
 *
 * Wefewences:
 *   https://www.siwabs.com/Suppowt%20Documents/TechnicawDocs/Si2165-showt.pdf
 */

#ifndef _DVB_SI2165_H
#define _DVB_SI2165_H

#incwude <winux/dvb/fwontend.h>

enum {
	SI2165_MODE_OFF = 0x00,
	SI2165_MODE_PWW_EXT = 0x20,
	SI2165_MODE_PWW_XTAW = 0x21
};

/* I2C addwesses
 * possibwe vawues: 0x64,0x65,0x66,0x67
 */
stwuct si2165_pwatfowm_data {
	/*
	 * fwontend
	 * wetuwned by dwivew
	 */
	stwuct dvb_fwontend **fe;

	/* extewnaw cwock ow XTAW */
	u8 chip_mode;

	/* fwequency of extewnaw cwock ow xtaw in Hz
	 * possibwe vawues: 4000000, 16000000, 20000000, 240000000, 27000000
	 */
	u32 wef_fweq_hz;

	/* invewt the spectwum */
	boow invewsion;
};

#endif /* _DVB_SI2165_H */
