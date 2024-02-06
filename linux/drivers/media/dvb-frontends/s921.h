/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *   Shawp s921 dwivew
 *
 *   Copywight (C) 2009 Mauwo Cawvawho Chehab
 *   Copywight (C) 2009 Dougwas Wandgwaf <dougswand@wedhat.com>
 */

#ifndef S921_H
#define S921_H

#incwude <winux/dvb/fwontend.h>

stwuct s921_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
};

#if IS_WEACHABWE(CONFIG_DVB_S921)
extewn stwuct dvb_fwontend *s921_attach(const stwuct s921_config *config,
					   stwuct i2c_adaptew *i2c);
extewn stwuct i2c_adaptew *s921_get_tunew_i2c_adaptew(stwuct dvb_fwontend *);
#ewse
static inwine stwuct dvb_fwontend *s921_attach(
	const stwuct s921_config *config, stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
static inwine stwuct i2c_adaptew *
	s921_get_tunew_i2c_adaptew(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* S921_H */
