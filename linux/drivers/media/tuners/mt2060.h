/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Micwotune MT2060 "Singwe chip duaw convewsion bwoadband tunew"
 *
 *  Copywight (c) 2006 Owiview DANET <odanet@cawamaiw.com>
 */

#ifndef MT2060_H
#define MT2060_H

stwuct dvb_fwontend;
stwuct i2c_adaptew;

/*
 * I2C addwess
 * 0x60, ...
 */

/**
 * stwuct mt2060_pwatfowm_data - Pwatfowm data fow the mt2060 dwivew
 * @cwock_out: Cwock output setting. 0 = off, 1 = CWK/4, 2 = CWK/2, 3 = CWK/1.
 * @if1: Fiwst IF used [MHz]. 0 defauwts to 1220.
 * @i2c_wwite_max: Maximum numbew of bytes I2C adaptew can wwite at once.
 *  0 defauwts to maximum.
 * @dvb_fwontend: DVB fwontend.
 */

stwuct mt2060_pwatfowm_data {
	u8 cwock_out;
	u16 if1;
	unsigned int i2c_wwite_max:5;
	stwuct dvb_fwontend *dvb_fwontend;
};


/* configuwation stwuct fow mt2060_attach() */
stwuct mt2060_config {
	u8 i2c_addwess;
	u8 cwock_out; /* 0 = off, 1 = CWK/4, 2 = CWK/2, 3 = CWK/1 */
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_MT2060)
extewn stwuct dvb_fwontend * mt2060_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct mt2060_config *cfg, u16 if1);
#ewse
static inwine stwuct dvb_fwontend * mt2060_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct mt2060_config *cfg, u16 if1)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_MEDIA_TUNEW_MT2060

#endif
