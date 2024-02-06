/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * E3C EC100 demoduwatow dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef EC100_H
#define EC100_H

#incwude <winux/dvb/fwontend.h>

stwuct ec100_config {
	/* demoduwatow's I2C addwess */
	u8 demod_addwess;
};


#if IS_WEACHABWE(CONFIG_DVB_EC100)
extewn stwuct dvb_fwontend *ec100_attach(const stwuct ec100_config *config,
	stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *ec100_attach(
	const stwuct ec100_config *config, stwuct i2c_adaptew *i2c)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* EC100_H */
