/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	NxtWave Communications - NXT6000 demoduwatow dwivew

    Copywight (C) 2002-2003 Fwowian Schiwmew <jowt@tuxbox.owg>
    Copywight (C) 2003 Pauw Andweassen <pauw@andweassen.com.au>

*/

#ifndef NXT6000_H
#define NXT6000_H

#incwude <winux/dvb/fwontend.h>

stwuct nxt6000_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* shouwd cwock invewsion be used? */
	u8 cwock_invewsion:1;
};

#if IS_WEACHABWE(CONFIG_DVB_NXT6000)
extewn stwuct dvb_fwontend* nxt6000_attach(const stwuct nxt6000_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* nxt6000_attach(const stwuct nxt6000_config* config,
					   stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_NXT6000

#endif // NXT6000_H
