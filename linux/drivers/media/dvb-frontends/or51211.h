/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow OW51211 (pcHDTV HD-2000) - VSB
 *
 *    Copywight (C) 2005 Kiwk Wapway <kiwk_wapway@bigfoot.com>
*/

#ifndef OW51211_H
#define OW51211_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

stwuct ow51211_config
{
	/* The demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* Wequest fiwmwawe fow device */
	int (*wequest_fiwmwawe)(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name);
	void (*setmode)(stwuct dvb_fwontend * fe, int mode);
	void (*weset)(stwuct dvb_fwontend * fe);
	void (*sweep)(stwuct dvb_fwontend * fe);
};

#if IS_WEACHABWE(CONFIG_DVB_OW51211)
extewn stwuct dvb_fwontend* ow51211_attach(const stwuct ow51211_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* ow51211_attach(const stwuct ow51211_config* config,
					   stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_OW51211

#endif // OW51211_H

