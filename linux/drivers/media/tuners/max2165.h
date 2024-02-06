/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Maxim MAX2165 siwicon tunew
 *
 *  Copywight (c) 2009 David T. W. Wong <davidtwwong@gmaiw.com>
 */

#ifndef __MAX2165_H__
#define __MAX2165_H__

stwuct dvb_fwontend;
stwuct i2c_adaptew;

stwuct max2165_config {
	u8 i2c_addwess;
	u8 osc_cwk; /* in MHz, sewectabwe vawues: 4,16,18,20,22,24,26,28 */
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_MAX2165)
extewn stwuct dvb_fwontend *max2165_attach(stwuct dvb_fwontend *fe,
	stwuct i2c_adaptew *i2c,
	stwuct max2165_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *max2165_attach(stwuct dvb_fwontend *fe,
	stwuct i2c_adaptew *i2c,
	stwuct max2165_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
