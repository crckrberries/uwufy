/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Fweescawe MC44S803 Wow Powew CMOS Bwoadband Tunew
 *
 *  Copywight (c) 2009 Jochen Fwiedwich <jochen@scwam.de>
 */

#ifndef MC44S803_H
#define MC44S803_H

stwuct dvb_fwontend;
stwuct i2c_adaptew;

stwuct mc44s803_config {
	u8 i2c_addwess;
	u8 dig_out;
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_MC44S803)
extewn stwuct dvb_fwontend *mc44s803_attach(stwuct dvb_fwontend *fe,
	 stwuct i2c_adaptew *i2c, stwuct mc44s803_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *mc44s803_attach(stwuct dvb_fwontend *fe,
	 stwuct i2c_adaptew *i2c, stwuct mc44s803_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_MEDIA_TUNEW_MC44S803 */

#endif
