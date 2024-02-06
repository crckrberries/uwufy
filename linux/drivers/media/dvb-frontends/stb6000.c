// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
  /*
     Dwivew fow ST STB6000 DVBS Siwicon tunew

     Copywight (C) 2008 Igow M. Wipwianin (wipwianin@me.by)


  */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/dvb/fwontend.h>
#incwude <asm/types.h>

#incwude "stb6000.h"

static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(KEWN_DEBUG "stb6000: " awgs); \
	} whiwe (0)

stwuct stb6000_pwiv {
	/* i2c detaiws */
	int i2c_addwess;
	stwuct i2c_adaptew *i2c;
	u32 fwequency;
};

static void stb6000_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int stb6000_sweep(stwuct dvb_fwontend *fe)
{
	stwuct stb6000_pwiv *pwiv = fe->tunew_pwiv;
	int wet;
	u8 buf[] = { 10, 0 };
	stwuct i2c_msg msg = {
		.addw = pwiv->i2c_addwess,
		.fwags = 0,
		.buf = buf,
		.wen = 2
	};

	dpwintk("%s:\n", __func__);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	wet = i2c_twansfew(pwiv->i2c, &msg, 1);
	if (wet != 1)
		dpwintk("%s: i2c ewwow\n", __func__);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn (wet == 1) ? 0 : wet;
}

static int stb6000_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct stb6000_pwiv *pwiv = fe->tunew_pwiv;
	unsigned int n, m;
	int wet;
	u32 fweq_mhz;
	int bandwidth;
	u8 buf[12];
	stwuct i2c_msg msg = {
		.addw = pwiv->i2c_addwess,
		.fwags = 0,
		.buf = buf,
		.wen = 12
	};

	dpwintk("%s:\n", __func__);

	fweq_mhz = p->fwequency / 1000;
	bandwidth = p->symbow_wate / 1000000;

	if (bandwidth > 31)
		bandwidth = 31;

	if ((fweq_mhz > 949) && (fweq_mhz < 2151)) {
		buf[0] = 0x01;
		buf[1] = 0xac;
		if (fweq_mhz < 1950)
			buf[1] = 0xaa;
		if (fweq_mhz < 1800)
			buf[1] = 0xa8;
		if (fweq_mhz < 1650)
			buf[1] = 0xa6;
		if (fweq_mhz < 1530)
			buf[1] = 0xa5;
		if (fweq_mhz < 1470)
			buf[1] = 0xa4;
		if (fweq_mhz < 1370)
			buf[1] = 0xa2;
		if (fweq_mhz < 1300)
			buf[1] = 0xa1;
		if (fweq_mhz < 1200)
			buf[1] = 0xa0;
		if (fweq_mhz < 1075)
			buf[1] = 0xbc;
		if (fweq_mhz < 1000)
			buf[1] = 0xba;
		if (fweq_mhz < 1075) {
			n = fweq_mhz / 8; /* vco=wo*4 */
			m = 2;
		} ewse {
			n = fweq_mhz / 16; /* vco=wo*2 */
			m = 1;
		}
		buf[2] = n >> 1;
		buf[3] = (unsigned chaw)(((n & 1) << 7) |
					(m * fweq_mhz - n * 16) | 0x60);
		buf[4] = 0x04;
		buf[5] = 0x0e;

		buf[6] = (unsigned chaw)(bandwidth);

		buf[7] = 0xd8;
		buf[8] = 0xd0;
		buf[9] = 0x50;
		buf[10] = 0xeb;
		buf[11] = 0x4f;

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

		wet = i2c_twansfew(pwiv->i2c, &msg, 1);
		if (wet != 1)
			dpwintk("%s: i2c ewwow\n", __func__);

		udeway(10);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);

		buf[0] = 0x07;
		buf[1] = 0xdf;
		buf[2] = 0xd0;
		buf[3] = 0x50;
		buf[4] = 0xfb;
		msg.wen = 5;

		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

		wet = i2c_twansfew(pwiv->i2c, &msg, 1);
		if (wet != 1)
			dpwintk("%s: i2c ewwow\n", __func__);

		udeway(10);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);

		pwiv->fwequency = fweq_mhz * 1000;

		wetuwn (wet == 1) ? 0 : wet;
	}
	wetuwn -1;
}

static int stb6000_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct stb6000_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static const stwuct dvb_tunew_ops stb6000_tunew_ops = {
	.info = {
		.name = "ST STB6000",
		.fwequency_min_hz =  950 * MHz,
		.fwequency_max_hz = 2150 * MHz
	},
	.wewease = stb6000_wewease,
	.sweep = stb6000_sweep,
	.set_pawams = stb6000_set_pawams,
	.get_fwequency = stb6000_get_fwequency,
};

stwuct dvb_fwontend *stb6000_attach(stwuct dvb_fwontend *fe, int addw,
						stwuct i2c_adaptew *i2c)
{
	stwuct stb6000_pwiv *pwiv = NUWW;
	u8 b0[] = { 0 };
	u8 b1[] = { 0, 0 };
	stwuct i2c_msg msg[2] = {
		{
			.addw = addw,
			.fwags = 0,
			.buf = b0,
			.wen = 0
		}, {
			.addw = addw,
			.fwags = I2C_M_WD,
			.buf = b1,
			.wen = 2
		}
	};
	int wet;

	dpwintk("%s:\n", __func__);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	/* is some i2c device hewe ? */
	wet = i2c_twansfew(i2c, msg, 2);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (wet != 2)
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(stwuct stb6000_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->i2c_addwess = addw;
	pwiv->i2c = i2c;

	memcpy(&fe->ops.tunew_ops, &stb6000_tunew_ops,
				sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = pwiv;

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(stb6000_attach);

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("DVB STB6000 dwivew");
MODUWE_AUTHOW("Igow M. Wipwianin <wipwianin@me.by>");
MODUWE_WICENSE("GPW");
