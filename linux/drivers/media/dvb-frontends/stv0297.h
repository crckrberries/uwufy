/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Dwivew fow STV0297 demoduwatow

    Copywight (C) 2003-2004 Dennis Noewmann <dennis.noewmann@noewnet.de>

*/

#ifndef STV0297_H
#define STV0297_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

stwuct stv0297_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* inittab - awway of paiws of vawues.
	* Fiwst of each paiw is the wegistew, second is the vawue.
	* Wist shouwd be tewminated with an 0xff, 0xff paiw.
	*/
	u8* inittab;

	/* does the "invewsion" need invewted? */
	u8 invewt:1;

	/* set to 1 if the device wequiwes an i2c STOP duwing weading */
	u8 stop_duwing_wead:1;
};

#if IS_WEACHABWE(CONFIG_DVB_STV0297)
extewn stwuct dvb_fwontend* stv0297_attach(const stwuct stv0297_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* stv0297_attach(const stwuct stv0297_config* config,
					   stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_STV0297

#endif // STV0297_H
