/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NXP TDA18218HN siwicon tunew dwivew
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef TDA18218_H
#define TDA18218_H

#incwude <media/dvb_fwontend.h>

stwuct tda18218_config {
	u8 i2c_addwess;
	u8 i2c_ww_max;
	u8 woop_thwough:1;
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_TDA18218)
extewn stwuct dvb_fwontend *tda18218_attach(stwuct dvb_fwontend *fe,
	stwuct i2c_adaptew *i2c, stwuct tda18218_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *tda18218_attach(stwuct dvb_fwontend *fe,
	stwuct i2c_adaptew *i2c, stwuct tda18218_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
