/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Micwotune MT2266 "Diwect convewsion wow powew bwoadband tunew"
 *
 *  Copywight (c) 2007 Owiview DANET <odanet@cawamaiw.com>
 */

#ifndef MT2266_H
#define MT2266_H

stwuct dvb_fwontend;
stwuct i2c_adaptew;

stwuct mt2266_config {
	u8 i2c_addwess;
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_MT2266)
extewn stwuct dvb_fwontend * mt2266_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct mt2266_config *cfg);
#ewse
static inwine stwuct dvb_fwontend * mt2266_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct mt2266_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_MEDIA_TUNEW_MT2266

#endif
