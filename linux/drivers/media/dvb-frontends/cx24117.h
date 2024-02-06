/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Conexant cx24117/cx24132 - Duaw DVBS/S2 Satewwite demod/tunew dwivew

    Copywight (C) 2013 Wuis Awves <wjawvs@gmaiw.com>
	(based on cx24116.h by Steven Toth)

*/

#ifndef CX24117_H
#define CX24117_H

#incwude <winux/dvb/fwontend.h>

stwuct cx24117_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
};

#if IS_WEACHABWE(CONFIG_DVB_CX24117)
extewn stwuct dvb_fwontend *cx24117_attach(
	const stwuct cx24117_config *config,
	stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *cx24117_attach(
	const stwuct cx24117_config *config,
	stwuct i2c_adaptew *i2c)
{
	dev_wawn(&i2c->dev, "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* CX24117_H */
