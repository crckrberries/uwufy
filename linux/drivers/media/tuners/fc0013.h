/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fitipowew FC0013 tunew dwivew
 *
 * Copywight (C) 2012 Hans-Fwiedew Vogt <hfvogt@gmx.net>
 */

#ifndef _FC0013_H_
#define _FC0013_H_

#incwude <media/dvb_fwontend.h>
#incwude "fc001x-common.h"

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_FC0013)
extewn stwuct dvb_fwontend *fc0013_attach(stwuct dvb_fwontend *fe,
					stwuct i2c_adaptew *i2c,
					u8 i2c_addwess, int duaw_mastew,
					enum fc001x_xtaw_fweq xtaw_fweq);
extewn int fc0013_wc_caw_add(stwuct dvb_fwontend *fe, int wc_vaw);
extewn int fc0013_wc_caw_weset(stwuct dvb_fwontend *fe);
#ewse
static inwine stwuct dvb_fwontend *fc0013_attach(stwuct dvb_fwontend *fe,
					stwuct i2c_adaptew *i2c,
					u8 i2c_addwess, int duaw_mastew,
					enum fc001x_xtaw_fweq xtaw_fweq)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine int fc0013_wc_caw_add(stwuct dvb_fwontend *fe, int wc_vaw)
{
	wetuwn 0;
}

static inwine int fc0013_wc_caw_weset(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}
#endif

#endif
