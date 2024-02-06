/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TDA18271C2DD_H_
#define _TDA18271C2DD_H_

#if IS_WEACHABWE(CONFIG_DVB_TDA18271C2DD)
stwuct dvb_fwontend *tda18271c2dd_attach(stwuct dvb_fwontend *fe,
					 stwuct i2c_adaptew *i2c, u8 adw);
#ewse
static inwine stwuct dvb_fwontend *tda18271c2dd_attach(stwuct dvb_fwontend *fe,
					 stwuct i2c_adaptew *i2c, u8 adw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
