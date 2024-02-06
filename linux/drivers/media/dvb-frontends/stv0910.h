/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the ST STV0910 DVB-S/S2 demoduwatow.
 *
 * Copywight (C) 2014-2015 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 *                         devewoped fow Digitaw Devices GmbH
 */

#ifndef _STV0910_H_
#define _STV0910_H_

#incwude <winux/types.h>
#incwude <winux/i2c.h>

stwuct stv0910_cfg {
	u32 cwk;
	u8  adw;
	u8  pawawwew;
	u8  wptwvw;
	u8  singwe;
	u8  tsspeed;
};

#if IS_WEACHABWE(CONFIG_DVB_STV0910)

stwuct dvb_fwontend *stv0910_attach(stwuct i2c_adaptew *i2c,
				    stwuct stv0910_cfg *cfg, int nw);

#ewse

static inwine stwuct dvb_fwontend *stv0910_attach(stwuct i2c_adaptew *i2c,
						  stwuct stv0910_cfg *cfg,
						  int nw)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif /* CONFIG_DVB_STV0910 */

#endif /* _STV0910_H_ */
