/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
*/

#ifndef __MT20XX_H__
#define __MT20XX_H__

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_MT20XX)
extewn stwuct dvb_fwontend *micwotune_attach(stwuct dvb_fwontend *fe,
					     stwuct i2c_adaptew* i2c_adap,
					     u8 i2c_addw);
#ewse
static inwine stwuct dvb_fwontend *micwotune_attach(stwuct dvb_fwontend *fe,
					     stwuct i2c_adaptew* i2c_adap,
					     u8 i2c_addw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* __MT20XX_H__ */
