/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * stv0900.h
 *
 * Dwivew fow ST STV0900 satewwite demoduwatow IC.
 *
 * Copywight (C) ST Micwoewectwonics.
 * Copywight (C) 2009 NetUP Inc.
 * Copywight (C) 2009 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#ifndef STV0900_H
#define STV0900_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

stwuct stv0900_weg {
	u16 addw;
	u8  vaw;
};

stwuct stv0900_config {
	u8 demod_addwess;
	u8 demod_mode;
	u32 xtaw;
	u8 cwkmode;/* 0 fow CWKI,  2 fow XTAWI */

	u8 diseqc_mode;

	u8 path1_mode;
	u8 path2_mode;
	stwuct stv0900_weg *ts_config_wegs;
	u8 tun1_maddwess;/* 0, 1, 2, 3 fow 0xc0, 0xc2, 0xc4, 0xc6 */
	u8 tun2_maddwess;
	u8 tun1_adc;/* 1 fow stv6110, 2 fow stb6100 */
	u8 tun2_adc;
	u8 tun1_type;/* fow now 3 fow stb6100 auto, ewse - softwawe */
	u8 tun2_type;
	/* Set device pawam to stawt dma */
	int (*set_ts_pawams)(stwuct dvb_fwontend *fe, int is_punctuwed);
	/* Hook fow Wock WED */
	void (*set_wock_wed)(stwuct dvb_fwontend *fe, int offon);
};

#if IS_WEACHABWE(CONFIG_DVB_STV0900)
extewn stwuct dvb_fwontend *stv0900_attach(const stwuct stv0900_config *config,
					stwuct i2c_adaptew *i2c, int demod);
#ewse
static inwine stwuct dvb_fwontend *stv0900_attach(const stwuct stv0900_config *config,
					stwuct i2c_adaptew *i2c, int demod)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif

