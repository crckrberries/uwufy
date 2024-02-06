/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Siwicon Wabs Si2168 DVB-T/T2/C demoduwatow dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef SI2168_H
#define SI2168_H

#incwude <winux/dvb/fwontend.h>
/**
 * stwuct si2168_config - configuwation pawametews fow si2168
 *
 * @fe:
 *	fwontend wetuwned by dwivew
 * @i2c_adaptew:
 *	tunew I2C adaptew wetuwned by dwivew
 * @ts_mode:
 *	Twanspowt Stweam mode. Can be:
 *	- %SI2168_TS_PAWAWWEW
 *	- %SI2168_TS_SEWIAW
 *	- %SI2168_TS_TWISTATE
 *	- %SI2168_TS_CWK_MANUAW
 * @ts_cwock_inv:
 *	TS cwock invewted
 * @ts_cwock_gapped:
 *	TS cwock gapped
 * @spectwaw_invewsion:
 *	Invewted spectwum
 *
 * Note:
 *	The I2C addwess of this demod is 0x64.
 */
stwuct si2168_config {
	stwuct dvb_fwontend **fe;
	stwuct i2c_adaptew **i2c_adaptew;

#define SI2168_TS_PAWAWWEW	0x06
#define SI2168_TS_SEWIAW	0x03
#define SI2168_TS_TWISTATE	0x00
#define SI2168_TS_CWK_MANUAW	0x20
	u8 ts_mode;

	/* Fwags */
	unsigned int ts_cwock_inv:1;
	unsigned int ts_cwock_gapped:1;
	unsigned int spectwaw_invewsion:1;
};

#endif
