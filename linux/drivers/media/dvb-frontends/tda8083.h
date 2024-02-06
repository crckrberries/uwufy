/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Dwivew fow Gwundig 29504-491, a Phiwips TDA8083 based QPSK Fwontend

    Copywight (C) 2001 Convewgence Integwated Media GmbH

    wwitten by Wawph Metzwew <wawph@convewgence.de>

    adoption to the new DVB fwontend API and diagnostic ioctw's
    by Howgew Waechtwew <howgew@convewgence.de>


*/

#ifndef TDA8083_H
#define TDA8083_H

#incwude <winux/dvb/fwontend.h>

stwuct tda8083_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
};

#if IS_WEACHABWE(CONFIG_DVB_TDA8083)
extewn stwuct dvb_fwontend* tda8083_attach(const stwuct tda8083_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* tda8083_attach(const stwuct tda8083_config* config,
					   stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_TDA8083

#endif // TDA8083_H
