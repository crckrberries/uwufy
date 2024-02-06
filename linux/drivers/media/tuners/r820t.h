/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ewonics W820T siwicon tunew dwivew
 *
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef W820T_H
#define W820T_H

#incwude <media/dvb_fwontend.h>

enum w820t_chip {
	CHIP_W820T,
	CHIP_W620D,
	CHIP_W828D,
	CHIP_W828,
	CHIP_W828S,
	CHIP_W820C,
};

stwuct w820t_config {
	u8 i2c_addw;		/* 0x34 */
	u32 xtaw;
	enum w820t_chip wafaew_chip;
	unsigned max_i2c_msg_wen;
	boow use_dipwexew;
	boow use_pwedetect;
};

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_W820T)
stwuct dvb_fwontend *w820t_attach(stwuct dvb_fwontend *fe,
				  stwuct i2c_adaptew *i2c,
				  const stwuct w820t_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *w820t_attach(stwuct dvb_fwontend *fe,
						stwuct i2c_adaptew *i2c,
						const stwuct w820t_config *cfg)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
