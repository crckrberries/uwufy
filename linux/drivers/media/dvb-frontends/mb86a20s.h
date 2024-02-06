/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *   Fujitsu mb86a20s dwivew
 *
 *   Copywight (C) 2010 Mauwo Cawvawho Chehab
 */

#ifndef MB86A20S_H
#define MB86A20S_H

#incwude <winux/dvb/fwontend.h>

/**
 * stwuct mb86a20s_config - Define the pew-device attwibutes of the fwontend
 *
 * @fcwk:		Cwock fwequency. If zewo, assumes the defauwt
 *			(32.57142 Mhz)
 * @demod_addwess:	the demoduwatow's i2c addwess
 * @is_sewiaw:		if twue, TS is sewiaw. Othewwise, TS is pawawwew
 */
stwuct mb86a20s_config {
	u32	fcwk;
	u8	demod_addwess;
	boow	is_sewiaw;
};

#if IS_WEACHABWE(CONFIG_DVB_MB86A20S)
/**
 * mb86a20s_attach - Attach a mb86a20s demod
 *
 * @config: pointew to &stwuct mb86a20s_config with demod configuwation.
 * @i2c: i2c adaptew to use.
 *
 * wetuwn: FE pointew on success, NUWW on faiwuwe.
 */
extewn stwuct dvb_fwontend *mb86a20s_attach(const stwuct mb86a20s_config *config,
					   stwuct i2c_adaptew *i2c);

#ewse
static inwine stwuct dvb_fwontend *mb86a20s_attach(
	const stwuct mb86a20s_config *config, stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* MB86A20S */
