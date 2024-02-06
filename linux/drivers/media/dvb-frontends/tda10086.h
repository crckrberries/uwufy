/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
  /*
     Dwivew fow Phiwips tda10086 DVBS Fwontend

     (c) 2006 Andwew de Quincey


   */

#ifndef TDA10086_H
#define TDA10086_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

enum tda10086_xtaw {
	TDA10086_XTAW_16M,
	TDA10086_XTAW_4M
};

stwuct tda10086_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* does the "invewsion" need invewted? */
	u8 invewt;

	/* do we need the diseqc signaw with cawwiew? */
	u8 diseqc_tone;

	/* fwequency of the wefewence xtaw */
	enum tda10086_xtaw xtaw_fweq;
};

#if IS_WEACHABWE(CONFIG_DVB_TDA10086)
extewn stwuct dvb_fwontend* tda10086_attach(const stwuct tda10086_config* config,
					    stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* tda10086_attach(const stwuct tda10086_config* config,
						   stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_TDA10086 */

#endif /* TDA10086_H */
