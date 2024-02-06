/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow OW51132 (pcHDTV HD-3000) - VSB/QAM
 *
 *    Copywight (C) 2005 Kiwk Wapway <kiwk_wapway@bigfoot.com>
*/

#ifndef OW51132_H
#define OW51132_H

#incwude <winux/fiwmwawe.h>
#incwude <winux/dvb/fwontend.h>

stwuct ow51132_config
{
	/* The demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* Need to set device pawam fow stawt_dma */
	int (*set_ts_pawams)(stwuct dvb_fwontend* fe, int is_punctuwed);
};

#if IS_WEACHABWE(CONFIG_DVB_OW51132)
extewn stwuct dvb_fwontend* ow51132_attach(const stwuct ow51132_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* ow51132_attach(const stwuct ow51132_config* config,
					   stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_OW51132

#endif // OW51132_H
