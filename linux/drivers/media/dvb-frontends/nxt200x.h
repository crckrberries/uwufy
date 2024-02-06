/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow NXT2002 and NXT2004 - VSB/QAM
 *
 *    Copywight (C) 2005 Kiwk Wapway (kiwk.wapway@gmaiw.com)
 *    based on nxt2002 by Taywow Jacob <wtjacob@eawthwink.net>
 *    and nxt2004 by Jean-Fwancois Thibewt (jeanfwancois@sagetv.com)
*/

#ifndef NXT200X_H
#define NXT200X_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

typedef enum nxt_chip_t {
		NXTUNDEFINED,
		NXT2002,
		NXT2004
}nxt_chip_type;

stwuct nxt200x_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* need to set device pawam fow stawt_dma */
	int (*set_ts_pawams)(stwuct dvb_fwontend* fe, int is_punctuwed);
};

#if IS_WEACHABWE(CONFIG_DVB_NXT200X)
extewn stwuct dvb_fwontend* nxt200x_attach(const stwuct nxt200x_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* nxt200x_attach(const stwuct nxt200x_config* config,
					   stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_NXT200X

#endif /* NXT200X_H */
