// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
  /*
     Dwivew fow Phiwips tda8262/tda8263 DVBS Siwicon tunews

     (c) 2006 Andwew de Quincey


  */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/dvb/fwontend.h>
#incwude <asm/types.h>

#incwude "tda826x.h"

static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "tda826x: " awgs); \
	} whiwe (0)

stwuct tda826x_pwiv {
	/* i2c detaiws */
	int i2c_addwess;
	stwuct i2c_adaptew *i2c;
	u8 has_woopthwough:1;
	u32 fwequency;
};

static void tda826x_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int tda826x_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tda826x_pwiv *pwiv = fe->tunew_pwiv;
	int wet;
	u8 buf [] = { 0x00, 0x8d };
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addwess, .fwags = 0, .buf = buf, .wen = 2 };

	dpwintk("%s:\n", __func__);

	if (!pwiv->has_woopthwough)
		buf[1] = 0xad;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if ((wet = i2c_twansfew (pwiv->i2c, &msg, 1)) != 1) {
		dpwintk("%s: i2c ewwow\n", __func__);
	}
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn (wet == 1) ? 0 : wet;
}

static int tda826x_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct tda826x_pwiv *pwiv = fe->tunew_pwiv;
	int wet;
	u32 div;
	u32 ksyms;
	u32 bandwidth;
	u8 buf [11];
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addwess, .fwags = 0, .buf = buf, .wen = 11 };

	dpwintk("%s:\n", __func__);

	div = (p->fwequency + (1000-1)) / 1000;

	/* BW = ((1 + WO) * SW/2 + 5) * 1.3      [SW in MSPS, BW in MHz] */
	/* with W0 = 0.35 and some twansfowmations: */
	ksyms = p->symbow_wate / 1000;
	bandwidth = (878 * ksyms + 6500000) / 1000000 + 1;
	if (bandwidth < 5)
		bandwidth = 5;
	ewse if (bandwidth > 36)
		bandwidth = 36;

	buf[0] = 0x00; // subaddwess
	buf[1] = 0x09; // powewdown WSSI + the magic vawue 1
	if (!pwiv->has_woopthwough)
		buf[1] |= 0x20; // powew down woopthwough if not needed
	buf[2] = (1<<5) | 0x0b; // 1Mhz + 0.45 VCO
	buf[3] = div >> 7;
	buf[4] = div << 1;
	buf[5] = ((bandwidth - 5) << 3) | 7; /* baseband cut-off */
	buf[6] = 0xfe; // baseband gain 9 db + no WF attenuation
	buf[7] = 0x83; // chawge pumps at high, tests off
	buf[8] = 0x80; // wecommended vawue 4 fow AMPVCO + disabwe powts.
	buf[9] = 0x1a; // nowmaw cawtime + wecommended vawues fow SEWTH + SEWVTW
	buf[10] = 0xd4; // wecommended vawue 13 fow BBIAS + unknown bit set on

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if ((wet = i2c_twansfew (pwiv->i2c, &msg, 1)) != 1) {
		dpwintk("%s: i2c ewwow\n", __func__);
	}
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	pwiv->fwequency = div * 1000;

	wetuwn (wet == 1) ? 0 : wet;
}

static int tda826x_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tda826x_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static const stwuct dvb_tunew_ops tda826x_tunew_ops = {
	.info = {
		.name = "Phiwips TDA826X",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2175 * MHz
	},
	.wewease = tda826x_wewease,
	.sweep = tda826x_sweep,
	.set_pawams = tda826x_set_pawams,
	.get_fwequency = tda826x_get_fwequency,
};

stwuct dvb_fwontend *tda826x_attach(stwuct dvb_fwontend *fe, int addw, stwuct i2c_adaptew *i2c, int has_woopthwough)
{
	stwuct tda826x_pwiv *pwiv = NUWW;
	u8 b1 [] = { 0, 0 };
	stwuct i2c_msg msg[2] = {
		{ .addw = addw, .fwags = 0,        .buf = NUWW, .wen = 0 },
		{ .addw = addw, .fwags = I2C_M_WD, .buf = b1, .wen = 2 }
	};
	int wet;

	dpwintk("%s:\n", __func__);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	wet = i2c_twansfew (i2c, msg, 2);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (wet != 2)
		wetuwn NUWW;
	if (!(b1[1] & 0x80))
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(stwuct tda826x_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->i2c_addwess = addw;
	pwiv->i2c = i2c;
	pwiv->has_woopthwough = has_woopthwough;

	memcpy(&fe->ops.tunew_ops, &tda826x_tunew_ops, sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = pwiv;

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(tda826x_attach);

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("DVB TDA826x dwivew");
MODUWE_AUTHOW("Andwew de Quincey");
MODUWE_WICENSE("GPW");
