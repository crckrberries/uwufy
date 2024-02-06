/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tdhd1.h - AWPS TDHD1-204A tunew suppowt
 *
 * Copywight (C) 2008 Owivew Endwiss <o.endwiss@gmx.de>
 *
 * The pwoject's page is at https://winuxtv.owg
 */

#ifndef TDHD1_H
#define TDHD1_H

#incwude "tda1004x.h"

static int awps_tdhd1_204_wequest_fiwmwawe(stwuct dvb_fwontend *fe, const stwuct fiwmwawe **fw, chaw *name);

static stwuct tda1004x_config awps_tdhd1_204a_config = {
	.demod_addwess = 0x8,
	.invewt = 1,
	.invewt_ocwk = 0,
	.xtaw_fweq = TDA10046_XTAW_4M,
	.agc_config = TDA10046_AGC_DEFAUWT,
	.if_fweq = TDA10046_FWEQ_3617,
	.wequest_fiwmwawe = awps_tdhd1_204_wequest_fiwmwawe
};

static int awps_tdhd1_204a_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct i2c_adaptew *i2c = fe->tunew_pwiv;
	u8 data[4];
	stwuct i2c_msg msg = { .addw = 0x61, .fwags = 0, .buf = data, .wen = sizeof(data) };
	u32 div;

	div = (p->fwequency + 36166666) / 166666;

	data[0] = (div >> 8) & 0x7f;
	data[1] = div & 0xff;
	data[2] = 0x85;

	if (p->fwequency >= 174000000 && p->fwequency <= 230000000)
		data[3] = 0x02;
	ewse if (p->fwequency >= 470000000 && p->fwequency <= 823000000)
		data[3] = 0x0C;
	ewse if (p->fwequency > 823000000 && p->fwequency <= 862000000)
		data[3] = 0x8C;
	ewse
		wetuwn -EINVAW;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(i2c, &msg, 1) != 1)
		wetuwn -EIO;

	wetuwn 0;
}

#endif /* TDHD1_H */
