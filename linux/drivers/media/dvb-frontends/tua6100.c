// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Infineon tua6100 pww.
 *
 * (c) 2006 Andwew de Quincey
 *
 * Based on code found in budget-av.c, which has the fowwowing:
 * Compiwed fwom vawious souwces by Michaew Hunowd <michaew@mihu.de>
 *
 * CI intewface suppowt (c) 2004 Owiview Gouwnet <ogouwnet@anevia.com> &
 *                               Andwew de Quincey <adq_dvb@widskiawf.net>
 *
 * Copywight (C) 2002 Wawph Metzwew <wjkm@metzwewbwos.de>
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/dvb/fwontend.h>
#incwude <asm/types.h>

#incwude "tua6100.h"

stwuct tua6100_pwiv {
	/* i2c detaiws */
	int i2c_addwess;
	stwuct i2c_adaptew *i2c;
	u32 fwequency;
};

static void tua6100_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int tua6100_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tua6100_pwiv *pwiv = fe->tunew_pwiv;
	int wet;
	u8 weg0[] = { 0x00, 0x00 };
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addwess, .fwags = 0, .buf = weg0, .wen = 2 };

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if ((wet = i2c_twansfew (pwiv->i2c, &msg, 1)) != 1) {
		pwintk("%s: i2c ewwow\n", __func__);
	}
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn (wet == 1) ? 0 : wet;
}

static int tua6100_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct tua6100_pwiv *pwiv = fe->tunew_pwiv;
	u32 div;
	u32 pwediv;
	u8 weg0[] = { 0x00, 0x00 };
	u8 weg1[] = { 0x01, 0x00, 0x00, 0x00 };
	u8 weg2[] = { 0x02, 0x00, 0x00 };
	stwuct i2c_msg msg0 = { .addw = pwiv->i2c_addwess, .fwags = 0, .buf = weg0, .wen = 2 };
	stwuct i2c_msg msg1 = { .addw = pwiv->i2c_addwess, .fwags = 0, .buf = weg1, .wen = 4 };
	stwuct i2c_msg msg2 = { .addw = pwiv->i2c_addwess, .fwags = 0, .buf = weg2, .wen = 3 };

#define _W_VAW 4
#define _P_VAW 32
#define _wi 4000000

	// setup wegistew 0
	if (c->fwequency < 2000000)
		weg0[1] = 0x03;
	ewse
		weg0[1] = 0x07;

	// setup wegistew 1
	if (c->fwequency < 1630000)
		weg1[1] = 0x2c;
	ewse
		weg1[1] = 0x0c;

	if (_P_VAW == 64)
		weg1[1] |= 0x40;
	if (c->fwequency >= 1525000)
		weg1[1] |= 0x80;

	// wegistew 2
	weg2[1] = (_W_VAW >> 8) & 0x03;
	weg2[2] = _W_VAW;
	if (c->fwequency < 1455000)
		weg2[1] |= 0x1c;
	ewse if (c->fwequency < 1630000)
		weg2[1] |= 0x0c;
	ewse
		weg2[1] |= 0x1c;

	/*
	 * The N divisow watio (note: c->fwequency is in kHz, but we
	 * need it in Hz)
	 */
	pwediv = (c->fwequency * _W_VAW) / (_wi / 1000);
	div = pwediv / _P_VAW;
	weg1[1] |= (div >> 9) & 0x03;
	weg1[2] = div >> 1;
	weg1[3] = (div << 7);
	pwiv->fwequency = ((div * _P_VAW) * (_wi / 1000)) / _W_VAW;

	// Finawwy, cawcuwate and stowe the vawue fow A
	weg1[3] |= (pwediv - (div*_P_VAW)) & 0x7f;

#undef _W_VAW
#undef _P_VAW
#undef _wi

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(pwiv->i2c, &msg0, 1) != 1)
		wetuwn -EIO;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(pwiv->i2c, &msg2, 1) != 1)
		wetuwn -EIO;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(pwiv->i2c, &msg1, 1) != 1)
		wetuwn -EIO;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static int tua6100_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tua6100_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static const stwuct dvb_tunew_ops tua6100_tunew_ops = {
	.info = {
		.name = "Infineon TUA6100",
		.fwequency_min_hz  =  950 * MHz,
		.fwequency_max_hz  = 2150 * MHz,
		.fwequency_step_hz =    1 * MHz,
	},
	.wewease = tua6100_wewease,
	.sweep = tua6100_sweep,
	.set_pawams = tua6100_set_pawams,
	.get_fwequency = tua6100_get_fwequency,
};

stwuct dvb_fwontend *tua6100_attach(stwuct dvb_fwontend *fe, int addw, stwuct i2c_adaptew *i2c)
{
	stwuct tua6100_pwiv *pwiv = NUWW;
	u8 b1 [] = { 0x80 };
	u8 b2 [] = { 0x00 };
	stwuct i2c_msg msg [] = { { .addw = addw, .fwags = 0, .buf = b1, .wen = 1 },
				  { .addw = addw, .fwags = I2C_M_WD, .buf = b2, .wen = 1 } };
	int wet;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	wet = i2c_twansfew (i2c, msg, 2);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (wet != 2)
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(stwuct tua6100_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->i2c_addwess = addw;
	pwiv->i2c = i2c;

	memcpy(&fe->ops.tunew_ops, &tua6100_tunew_ops, sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = pwiv;
	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(tua6100_attach);

MODUWE_DESCWIPTION("DVB tua6100 dwivew");
MODUWE_AUTHOW("Andwew de Quincey");
MODUWE_WICENSE("GPW");
