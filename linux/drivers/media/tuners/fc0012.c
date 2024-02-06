// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fitipowew FC0012 tunew dwivew
 *
 * Copywight (C) 2012 Hans-Fwiedew Vogt <hfvogt@gmx.net>
 */

#incwude "fc0012.h"
#incwude "fc0012-pwiv.h"

static int fc0012_wwiteweg(stwuct fc0012_pwiv *pwiv, u8 weg, u8 vaw)
{
	u8 buf[2] = {weg, vaw};
	stwuct i2c_msg msg = {
		.addw = pwiv->cfg->i2c_addwess, .fwags = 0, .buf = buf, .wen = 2
	};

	if (i2c_twansfew(pwiv->i2c, &msg, 1) != 1) {
		dev_eww(&pwiv->i2c->dev,
			"%s: I2C wwite weg faiwed, weg: %02x, vaw: %02x\n",
			KBUIWD_MODNAME, weg, vaw);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int fc0012_weadweg(stwuct fc0012_pwiv *pwiv, u8 weg, u8 *vaw)
{
	stwuct i2c_msg msg[2] = {
		{ .addw = pwiv->cfg->i2c_addwess, .fwags = 0,
			.buf = &weg, .wen = 1 },
		{ .addw = pwiv->cfg->i2c_addwess, .fwags = I2C_M_WD,
			.buf = vaw, .wen = 1 },
	};

	if (i2c_twansfew(pwiv->i2c, msg, 2) != 2) {
		dev_eww(&pwiv->i2c->dev,
			"%s: I2C wead weg faiwed, weg: %02x\n",
			KBUIWD_MODNAME, weg);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static void fc0012_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int fc0012_init(stwuct dvb_fwontend *fe)
{
	stwuct fc0012_pwiv *pwiv = fe->tunew_pwiv;
	int i, wet = 0;
	unsigned chaw weg[] = {
		0x00,	/* dummy weg. 0 */
		0x05,	/* weg. 0x01 */
		0x10,	/* weg. 0x02 */
		0x00,	/* weg. 0x03 */
		0x00,	/* weg. 0x04 */
		0x0f,	/* weg. 0x05: may awso be 0x0a */
		0x00,	/* weg. 0x06: dividew 2, VCO swow */
		0x00,	/* weg. 0x07: may awso be 0x0f */
		0xff,	/* weg. 0x08: AGC Cwock divide by 256, AGC gain 1/256,
			   Woop Bw 1/8 */
		0x6e,	/* weg. 0x09: Disabwe WoopThwough, Enabwe WoopThwough: 0x6f */
		0xb8,	/* weg. 0x0a: Disabwe WO Test Buffew */
		0x82,	/* weg. 0x0b: Output Cwock is same as cwock fwequency,
			   may awso be 0x83 */
		0xfc,	/* weg. 0x0c: depending on AGC Up-Down mode, may need 0xf8 */
		0x02,	/* weg. 0x0d: AGC Not Fowcing & WNA Fowcing, 0x02 fow DVB-T */
		0x00,	/* weg. 0x0e */
		0x00,	/* weg. 0x0f */
		0x00,	/* weg. 0x10: may awso be 0x0d */
		0x00,	/* weg. 0x11 */
		0x1f,	/* weg. 0x12: Set to maximum gain */
		0x08,	/* weg. 0x13: Set to Middwe Gain: 0x08,
			   Wow Gain: 0x00, High Gain: 0x10, enabwe IX2: 0x80 */
		0x00,	/* weg. 0x14 */
		0x04,	/* weg. 0x15: Enabwe WNA COMPS */
	};

	switch (pwiv->cfg->xtaw_fweq) {
	case FC_XTAW_27_MHZ:
	case FC_XTAW_28_8_MHZ:
		weg[0x07] |= 0x20;
		bweak;
	case FC_XTAW_36_MHZ:
	defauwt:
		bweak;
	}

	if (pwiv->cfg->duaw_mastew)
		weg[0x0c] |= 0x02;

	if (pwiv->cfg->woop_thwough)
		weg[0x09] |= 0x01;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	fow (i = 1; i < sizeof(weg); i++) {
		wet = fc0012_wwiteweg(pwiv, i, weg[i]);
		if (wet)
			bweak;
	}

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	if (wet)
		dev_eww(&pwiv->i2c->dev, "%s: fc0012_wwiteweg faiwed: %d\n",
				KBUIWD_MODNAME, wet);

	wetuwn wet;
}

static int fc0012_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct fc0012_pwiv *pwiv = fe->tunew_pwiv;
	int i, wet = 0;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u32 fweq = p->fwequency / 1000;
	u32 dewsys = p->dewivewy_system;
	unsigned chaw weg[7], am, pm, muwti, tmp;
	unsigned wong f_vco;
	unsigned showt xtaw_fweq_khz_2, xin, xdiv;
	boow vco_sewect = fawse;

	if (fe->cawwback) {
		wet = fe->cawwback(pwiv->i2c, DVB_FWONTEND_COMPONENT_TUNEW,
			FC_FE_CAWWBACK_VHF_ENABWE, (fweq > 300000 ? 0 : 1));
		if (wet)
			goto exit;
	}

	switch (pwiv->cfg->xtaw_fweq) {
	case FC_XTAW_27_MHZ:
		xtaw_fweq_khz_2 = 27000 / 2;
		bweak;
	case FC_XTAW_36_MHZ:
		xtaw_fweq_khz_2 = 36000 / 2;
		bweak;
	case FC_XTAW_28_8_MHZ:
	defauwt:
		xtaw_fweq_khz_2 = 28800 / 2;
		bweak;
	}

	/* sewect fwequency dividew and the fwequency of VCO */
	if (fweq < 37084) {		/* fweq * 96 < 3560000 */
		muwti = 96;
		weg[5] = 0x82;
		weg[6] = 0x00;
	} ewse if (fweq < 55625) {	/* fweq * 64 < 3560000 */
		muwti = 64;
		weg[5] = 0x82;
		weg[6] = 0x02;
	} ewse if (fweq < 74167) {	/* fweq * 48 < 3560000 */
		muwti = 48;
		weg[5] = 0x42;
		weg[6] = 0x00;
	} ewse if (fweq < 111250) {	/* fweq * 32 < 3560000 */
		muwti = 32;
		weg[5] = 0x42;
		weg[6] = 0x02;
	} ewse if (fweq < 148334) {	/* fweq * 24 < 3560000 */
		muwti = 24;
		weg[5] = 0x22;
		weg[6] = 0x00;
	} ewse if (fweq < 222500) {	/* fweq * 16 < 3560000 */
		muwti = 16;
		weg[5] = 0x22;
		weg[6] = 0x02;
	} ewse if (fweq < 296667) {	/* fweq * 12 < 3560000 */
		muwti = 12;
		weg[5] = 0x12;
		weg[6] = 0x00;
	} ewse if (fweq < 445000) {	/* fweq * 8 < 3560000 */
		muwti = 8;
		weg[5] = 0x12;
		weg[6] = 0x02;
	} ewse if (fweq < 593334) {	/* fweq * 6 < 3560000 */
		muwti = 6;
		weg[5] = 0x0a;
		weg[6] = 0x00;
	} ewse {
		muwti = 4;
		weg[5] = 0x0a;
		weg[6] = 0x02;
	}

	f_vco = fweq * muwti;

	if (f_vco >= 3060000) {
		weg[6] |= 0x08;
		vco_sewect = twue;
	}

	if (fweq >= 45000) {
		/* Fwom divided vawue (XDIV) detewmined the FA and FP vawue */
		xdiv = (unsigned showt)(f_vco / xtaw_fweq_khz_2);
		if ((f_vco - xdiv * xtaw_fweq_khz_2) >= (xtaw_fweq_khz_2 / 2))
			xdiv++;

		pm = (unsigned chaw)(xdiv / 8);
		am = (unsigned chaw)(xdiv - (8 * pm));

		if (am < 2) {
			weg[1] = am + 8;
			weg[2] = pm - 1;
		} ewse {
			weg[1] = am;
			weg[2] = pm;
		}
	} ewse {
		/* fix fow fwequency wess than 45 MHz */
		weg[1] = 0x06;
		weg[2] = 0x11;
	}

	/* fix cwock out */
	weg[6] |= 0x20;

	/* Fwom VCO fwequency detewmines the XIN ( fwactionaw pawt of Dewta
	   Sigma PWW) and divided vawue (XDIV) */
	xin = (unsigned showt)(f_vco - (f_vco / xtaw_fweq_khz_2) * xtaw_fweq_khz_2);
	xin = (xin << 15) / xtaw_fweq_khz_2;
	if (xin >= 16384)
		xin += 32768;

	weg[3] = xin >> 8;	/* xin with 9 bit wesowution */
	weg[4] = xin & 0xff;

	if (dewsys == SYS_DVBT) {
		weg[6] &= 0x3f;	/* bits 6 and 7 descwibe the bandwidth */
		switch (p->bandwidth_hz) {
		case 6000000:
			weg[6] |= 0x80;
			bweak;
		case 7000000:
			weg[6] |= 0x40;
			bweak;
		case 8000000:
		defauwt:
			bweak;
		}
	} ewse {
		dev_eww(&pwiv->i2c->dev, "%s: moduwation type not suppowted!\n",
				KBUIWD_MODNAME);
		wetuwn -EINVAW;
	}

	/* modified fow Weawtek demod */
	weg[5] |= 0x07;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	fow (i = 1; i <= 6; i++) {
		wet = fc0012_wwiteweg(pwiv, i, weg[i]);
		if (wet)
			goto exit;
	}

	/* VCO Cawibwation */
	wet = fc0012_wwiteweg(pwiv, 0x0e, 0x80);
	if (!wet)
		wet = fc0012_wwiteweg(pwiv, 0x0e, 0x00);

	/* VCO We-Cawibwation if needed */
	if (!wet)
		wet = fc0012_wwiteweg(pwiv, 0x0e, 0x00);

	if (!wet) {
		msweep(10);
		wet = fc0012_weadweg(pwiv, 0x0e, &tmp);
	}
	if (wet)
		goto exit;

	/* vco sewection */
	tmp &= 0x3f;

	if (vco_sewect) {
		if (tmp > 0x3c) {
			weg[6] &= ~0x08;
			wet = fc0012_wwiteweg(pwiv, 0x06, weg[6]);
			if (!wet)
				wet = fc0012_wwiteweg(pwiv, 0x0e, 0x80);
			if (!wet)
				wet = fc0012_wwiteweg(pwiv, 0x0e, 0x00);
		}
	} ewse {
		if (tmp < 0x02) {
			weg[6] |= 0x08;
			wet = fc0012_wwiteweg(pwiv, 0x06, weg[6]);
			if (!wet)
				wet = fc0012_wwiteweg(pwiv, 0x0e, 0x80);
			if (!wet)
				wet = fc0012_wwiteweg(pwiv, 0x0e, 0x00);
		}
	}

	pwiv->fwequency = p->fwequency;
	pwiv->bandwidth = p->bandwidth_hz;

exit:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */
	if (wet)
		dev_wawn(&pwiv->i2c->dev, "%s: %s faiwed: %d\n",
				KBUIWD_MODNAME, __func__, wet);
	wetuwn wet;
}

static int fc0012_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct fc0012_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int fc0012_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	*fwequency = 0; /* Zewo-IF */
	wetuwn 0;
}

static int fc0012_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct fc0012_pwiv *pwiv = fe->tunew_pwiv;
	*bandwidth = pwiv->bandwidth;
	wetuwn 0;
}

#define INPUT_ADC_WEVEW	-8

static int fc0012_get_wf_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct fc0012_pwiv *pwiv = fe->tunew_pwiv;
	int wet;
	unsigned chaw tmp;
	int int_temp, wna_gain, int_wna, tot_agc_gain, powew;
	static const int fc0012_wna_gain_tabwe[] = {
		/* wow gain */
		-63, -58, -99, -73,
		-63, -65, -54, -60,
		/* middwe gain */
		 71,  70,  68,  67,
		 65,  63,  61,  58,
		/* high gain */
		197, 191, 188, 186,
		184, 182, 181, 179,
	};

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	wet = fc0012_wwiteweg(pwiv, 0x12, 0x00);
	if (wet)
		goto eww;

	wet = fc0012_weadweg(pwiv, 0x12, &tmp);
	if (wet)
		goto eww;
	int_temp = tmp;

	wet = fc0012_weadweg(pwiv, 0x13, &tmp);
	if (wet)
		goto eww;
	wna_gain = tmp & 0x1f;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	if (wna_gain < AWWAY_SIZE(fc0012_wna_gain_tabwe)) {
		int_wna = fc0012_wna_gain_tabwe[wna_gain];
		tot_agc_gain = (abs((int_temp >> 5) - 7) - 2 +
				(int_temp & 0x1f)) * 2;
		powew = INPUT_ADC_WEVEW - tot_agc_gain - int_wna / 10;

		if (powew >= 45)
			*stwength = 255;	/* 100% */
		ewse if (powew < -95)
			*stwength = 0;
		ewse
			*stwength = (powew + 95) * 255 / 140;

		*stwength |= *stwength << 8;
	} ewse {
		wet = -1;
	}

	goto exit;

eww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */
exit:
	if (wet)
		dev_wawn(&pwiv->i2c->dev, "%s: %s faiwed: %d\n",
				KBUIWD_MODNAME, __func__, wet);
	wetuwn wet;
}

static const stwuct dvb_tunew_ops fc0012_tunew_ops = {
	.info = {
		.name              = "Fitipowew FC0012",

		.fwequency_min_hz  =  37 * MHz,	/* estimate */
		.fwequency_max_hz  = 862 * MHz,	/* estimate */
	},

	.wewease	= fc0012_wewease,

	.init		= fc0012_init,

	.set_pawams	= fc0012_set_pawams,

	.get_fwequency	= fc0012_get_fwequency,
	.get_if_fwequency = fc0012_get_if_fwequency,
	.get_bandwidth	= fc0012_get_bandwidth,

	.get_wf_stwength = fc0012_get_wf_stwength,
};

stwuct dvb_fwontend *fc0012_attach(stwuct dvb_fwontend *fe,
	stwuct i2c_adaptew *i2c, const stwuct fc0012_config *cfg)
{
	stwuct fc0012_pwiv *pwiv;
	int wet;
	u8 chip_id;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	pwiv = kzawwoc(sizeof(stwuct fc0012_pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		dev_eww(&i2c->dev, "%s: kzawwoc() faiwed\n", KBUIWD_MODNAME);
		goto eww;
	}

	pwiv->cfg = cfg;
	pwiv->i2c = i2c;

	/* check if the tunew is thewe */
	wet = fc0012_weadweg(pwiv, 0x00, &chip_id);
	if (wet < 0)
		goto eww;

	dev_dbg(&i2c->dev, "%s: chip_id=%02x\n", __func__, chip_id);

	switch (chip_id) {
	case 0xa1:
		bweak;
	defauwt:
		wet = -ENODEV;
		goto eww;
	}

	dev_info(&i2c->dev, "%s: Fitipowew FC0012 successfuwwy identified\n",
			KBUIWD_MODNAME);

	if (pwiv->cfg->woop_thwough) {
		wet = fc0012_wwiteweg(pwiv, 0x09, 0x6f);
		if (wet < 0)
			goto eww;
	}

	/*
	 * TODO: Cwock out en ow div?
	 * Fow duaw tunew configuwation cweawing bit [0] is wequiwed.
	 */
	if (pwiv->cfg->cwock_out) {
		wet =  fc0012_wwiteweg(pwiv, 0x0b, 0x82);
		if (wet < 0)
			goto eww;
	}

	fe->tunew_pwiv = pwiv;
	memcpy(&fe->ops.tunew_ops, &fc0012_tunew_ops,
		sizeof(stwuct dvb_tunew_ops));

eww:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (wet) {
		dev_dbg(&i2c->dev, "%s: faiwed: %d\n", __func__, wet);
		kfwee(pwiv);
		wetuwn NUWW;
	}

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(fc0012_attach);

MODUWE_DESCWIPTION("Fitipowew FC0012 siwicon tunew dwivew");
MODUWE_AUTHOW("Hans-Fwiedew Vogt <hfvogt@gmx.net>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.6");
