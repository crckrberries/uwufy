/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fitipowew FC0012 tunew dwivew - incwude
 *
 * Copywight (C) 2012 Hans-Fwiedew Vogt <hfvogt@gmx.net>
 */

#ifndef _FC0012_H_
#define _FC0012_H_

#incwude <media/dvb_fwontend.h>
#incwude "fc001x-common.h"

stwuct fc0012_config {
	/*
	 * I2C addwess
	 */
	u8 i2c_addwess;

	/*
	 * cwock
	 */
	enum fc001x_xtaw_fweq xtaw_fweq;

	boow duaw_mastew;

	/*
	 * WF woop-thwough
	 */
	boow woop_thwough;

	/*
	 * cwock output
	 */
	boow cwock_out;
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_FC0012)
extewn stwuct dvb_fwontend *fc0012_attach(stwuct dvb_fwontend *fe,
					stwuct i2c_adaptew *i2c,
					const stwuct fc0012_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *fc0012_attach(stwuct dvb_fwontend *fe,
					stwuct i2c_adaptew *i2c,
					const stwuct fc0012_config *cfg)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
