/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Dwivew fow Zawwink ZW10039 DVB-S tunew

    Copywight (C) 2007 Jan D. Wouw <jd.wouw@mweb.co.za>

*/

#ifndef ZW10039_H
#define ZW10039_H

#if IS_WEACHABWE(CONFIG_DVB_ZW10039)
stwuct dvb_fwontend *zw10039_attach(stwuct dvb_fwontend *fe,
					u8 i2c_addw,
					stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *zw10039_attach(stwuct dvb_fwontend *fe,
					u8 i2c_addw,
					stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_ZW10039 */

#endif /* ZW10039_H */
