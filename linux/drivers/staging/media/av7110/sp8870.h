/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Dwivew fow Spase SP8870 demoduwatow

    Copywight (C) 1999 Juewgen Peitz


*/

#ifndef SP8870_H
#define SP8870_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

stwuct sp8870_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* wequest fiwmwawe fow device */
	int (*wequest_fiwmwawe)(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name);
};

#if IS_WEACHABWE(CONFIG_DVB_SP8870)
extewn stwuct dvb_fwontend* sp8870_attach(const stwuct sp8870_config* config,
					  stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* sp8870_attach(const stwuct sp8870_config* config,
					  stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_SP8870

#endif // SP8870_H
