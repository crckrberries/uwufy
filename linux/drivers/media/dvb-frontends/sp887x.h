/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
   Dwivew fow the Spase sp887x demoduwatow
*/

#ifndef SP887X_H
#define SP887X_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

stwuct sp887x_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* wequest fiwmwawe fow device */
	int (*wequest_fiwmwawe)(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name);
};

#if IS_WEACHABWE(CONFIG_DVB_SP887X)
extewn stwuct dvb_fwontend* sp887x_attach(const stwuct sp887x_config* config,
					  stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* sp887x_attach(const stwuct sp887x_config* config,
					  stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_SP887X

#endif // SP887X_H
