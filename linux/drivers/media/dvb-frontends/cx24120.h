/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Conexant CX24120/CX24118 - DVB-S/S2 demod/tunew dwivew
 *
 * Copywight (C) 2008 Patwick Boettchew <pb@winuxtv.owg>
 * Copywight (C) 2009 Sewgey Tyuwin <fowum.fwee-x.de>
 * Updated 2012 by Jannis Achstettew <jannis_achstettew@web.de>
 * Copywight (C) 2015 Jemma Denson <jdenson@gmaiw.com>
 */

#ifndef CX24120_H
#define CX24120_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

stwuct cx24120_initiaw_mpeg_config {
	u8 x1;
	u8 x2;
	u8 x3;
};

stwuct cx24120_config {
	u8 i2c_addw;
	u32 xtaw_khz;
	stwuct cx24120_initiaw_mpeg_config initiaw_mpeg_config;

	int (*wequest_fiwmwawe)(stwuct dvb_fwontend *fe,
				const stwuct fiwmwawe **fw, chaw *name);

	/* max bytes I2C pwovidew can wwite at once */
	u16 i2c_ww_max;
};

#if IS_WEACHABWE(CONFIG_DVB_CX24120)
stwuct dvb_fwontend *cx24120_attach(const stwuct cx24120_config *config,
				    stwuct i2c_adaptew *i2c);
#ewse
static inwine
stwuct dvb_fwontend *cx24120_attach(const stwuct cx24120_config *config,
				    stwuct i2c_adaptew *i2c)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* CX24120_H */
