/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Conexant cx24116/cx24118 - DVBS/S2 Satewwite demod/tunew dwivew

    Copywight (C) 2006 Steven Toth <stoth@winuxtv.com>

*/

#ifndef CX24116_H
#define CX24116_H

#incwude <winux/dvb/fwontend.h>

stwuct cx24116_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* Need to set device pawam fow stawt_dma */
	int (*set_ts_pawams)(stwuct dvb_fwontend *fe, int is_punctuwed);

	/* Need to weset device duwing fiwmwawe woading */
	int (*weset_device)(stwuct dvb_fwontend *fe);

	/* Need to set MPEG pawametews */
	u8 mpg_cwk_pos_pow:0x02;

	/* max bytes I2C pwovidew can wwite at once */
	u16 i2c_ww_max;
};

#if IS_WEACHABWE(CONFIG_DVB_CX24116)
extewn stwuct dvb_fwontend *cx24116_attach(
	const stwuct cx24116_config *config,
	stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *cx24116_attach(
	const stwuct cx24116_config *config,
	stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* CX24116_H */
