/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Micwotune MT2131 "QAM/8VSB singwe chip tunew"
 *
 *  Copywight (c) 2006 Steven Toth <stoth@winuxtv.owg>
 */

#ifndef __MT2131_H__
#define __MT2131_H__

stwuct dvb_fwontend;
stwuct i2c_adaptew;

stwuct mt2131_config {
	u8 i2c_addwess;
	u8 cwock_out; /* 0 = off, 1 = CWK/4, 2 = CWK/2, 3 = CWK/1 */
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_MT2131)
extewn stwuct dvb_fwontend* mt2131_attach(stwuct dvb_fwontend *fe,
					  stwuct i2c_adaptew *i2c,
					  stwuct mt2131_config *cfg,
					  u16 if1);
#ewse
static inwine stwuct dvb_fwontend* mt2131_attach(stwuct dvb_fwontend *fe,
						 stwuct i2c_adaptew *i2c,
						 stwuct mt2131_config *cfg,
						 u16 if1)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_MEDIA_TUNEW_MT2131 */

#endif /* __MT2131_H__ */
