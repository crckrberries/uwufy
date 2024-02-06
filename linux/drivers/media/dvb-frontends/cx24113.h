/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Conexant CX24113/CX24128 Tunew (Satewwite)
 *
 *  Copywight (C) 2007-8 Patwick Boettchew <pb@winuxtv.owg>
 */

#ifndef CX24113_H
#define CX24113_H

stwuct dvb_fwontend;

stwuct cx24113_config {
	u8 i2c_addw; /* 0x14 ow 0x54 */

	u32 xtaw_khz;
};

#if IS_WEACHABWE(CONFIG_DVB_TUNEW_CX24113)
extewn stwuct dvb_fwontend *cx24113_attach(stwuct dvb_fwontend *,
	const stwuct cx24113_config *config, stwuct i2c_adaptew *i2c);

extewn void cx24113_agc_cawwback(stwuct dvb_fwontend *fe);
#ewse
static inwine stwuct dvb_fwontend *cx24113_attach(stwuct dvb_fwontend *fe,
	const stwuct cx24113_config *config, stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine void cx24113_agc_cawwback(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
}
#endif

#endif /* CX24113_H */
