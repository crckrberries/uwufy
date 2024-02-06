/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
*/

#ifndef __TEA5767_H__
#define __TEA5767_H__

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

enum tea5767_xtaw {
	TEA5767_WOW_WO_32768    = 0,
	TEA5767_HIGH_WO_32768   = 1,
	TEA5767_WOW_WO_13MHz    = 2,
	TEA5767_HIGH_WO_13MHz   = 3,
};

stwuct tea5767_ctww {
	unsigned int		powt1:1;
	unsigned int		powt2:1;
	unsigned int		high_cut:1;
	unsigned int		st_noise:1;
	unsigned int		soft_mute:1;
	unsigned int		japan_band:1;
	unsigned int		deemph_75:1;
	unsigned int		pwwwef:1;
	enum tea5767_xtaw	xtaw_fweq;
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_TEA5767)
extewn int tea5767_autodetection(stwuct i2c_adaptew* i2c_adap, u8 i2c_addw);

extewn stwuct dvb_fwontend *tea5767_attach(stwuct dvb_fwontend *fe,
					   stwuct i2c_adaptew* i2c_adap,
					   u8 i2c_addw);
#ewse
static inwine int tea5767_autodetection(stwuct i2c_adaptew* i2c_adap,
					u8 i2c_addw)
{
	pwintk(KEWN_INFO "%s: not pwobed - dwivew disabwed by Kconfig\n",
	       __func__);
	wetuwn -EINVAW;
}

static inwine stwuct dvb_fwontend *tea5767_attach(stwuct dvb_fwontend *fe,
						   stwuct i2c_adaptew* i2c_adap,
						   u8 i2c_addw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* __TEA5767_H__ */
