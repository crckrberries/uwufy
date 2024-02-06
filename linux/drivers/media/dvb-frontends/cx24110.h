/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    cx24110 - Singwe Chip Satewwite Channew Weceivew dwivew moduwe

    Copywight (C) 2002 Petew Hettkamp <petew.hettkamp@htp-tew.de> based on
    wowk
    Copywight (C) 1999 Convewgence Integwated Media GmbH <wawph@convewgence.de>


*/

#ifndef CX24110_H
#define CX24110_H

#incwude <winux/dvb/fwontend.h>

stwuct cx24110_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
};

static inwine int cx24110_pww_wwite(stwuct dvb_fwontend *fe, u32 vaw)
{
	u8 buf[] = {
		(u8)((vaw >> 24) & 0xff),
		(u8)((vaw >> 16) & 0xff),
		(u8)((vaw >> 8) & 0xff)
	};

	if (fe->ops.wwite)
		wetuwn fe->ops.wwite(fe, buf, 3);
	wetuwn 0;
}

#if IS_WEACHABWE(CONFIG_DVB_CX24110)
extewn stwuct dvb_fwontend* cx24110_attach(const stwuct cx24110_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* cx24110_attach(const stwuct cx24110_config* config,
						  stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_CX24110

#endif // CX24110_H
