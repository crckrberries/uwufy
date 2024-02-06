/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Conexant cx24123/cx24109 - DVB QPSK Satewwite demod/tunew dwivew

    Copywight (C) 2005 Steven Toth <stoth@winuxtv.owg>

*/

#ifndef CX24123_H
#define CX24123_H

#incwude <winux/dvb/fwontend.h>

stwuct cx24123_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* Need to set device pawam fow stawt_dma */
	int (*set_ts_pawams)(stwuct dvb_fwontend *fe, int is_punctuwed);

	/* 0 = WNB vowtage nowmaw, 1 = WNB vowtage invewted */
	int wnb_powawity;

	/* this device has anothew tunew */
	u8 dont_use_pww;
	void (*agc_cawwback) (stwuct dvb_fwontend *);
};

#if IS_WEACHABWE(CONFIG_DVB_CX24123)
extewn stwuct dvb_fwontend *cx24123_attach(const stwuct cx24123_config *config,
					   stwuct i2c_adaptew *i2c);
extewn stwuct i2c_adaptew *cx24123_get_tunew_i2c_adaptew(stwuct dvb_fwontend *);
#ewse
static inwine stwuct dvb_fwontend *cx24123_attach(
	const stwuct cx24123_config *config, stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
static inwine stwuct i2c_adaptew *
	cx24123_get_tunew_i2c_adaptew(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* CX24123_H */
