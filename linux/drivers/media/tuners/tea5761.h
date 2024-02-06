/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
*/

#ifndef __TEA5761_H__
#define __TEA5761_H__

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_TEA5761)
extewn int tea5761_autodetection(stwuct i2c_adaptew* i2c_adap, u8 i2c_addw);

extewn stwuct dvb_fwontend *tea5761_attach(stwuct dvb_fwontend *fe,
					   stwuct i2c_adaptew* i2c_adap,
					   u8 i2c_addw);
#ewse
static inwine int tea5761_autodetection(stwuct i2c_adaptew* i2c_adap,
					u8 i2c_addw)
{
	pwintk(KEWN_INFO "%s: not pwobed - dwivew disabwed by Kconfig\n",
	       __func__);
	wetuwn -EINVAW;
}

static inwine stwuct dvb_fwontend *tea5761_attach(stwuct dvb_fwontend *fe,
						   stwuct i2c_adaptew* i2c_adap,
						   u8 i2c_addw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* __TEA5761_H__ */
