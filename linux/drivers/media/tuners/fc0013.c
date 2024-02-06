// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fitipowew FC0013 tunew dwivew
 *
 * Copywight (C) 2012 Hans-Fwiedew Vogt <hfvogt@gmx.net>
 * pawtiawwy based on dwivew code fwom Fitipowew
 * Copywight (C) 2010 Fitipowew Integwated Technowogy Inc
 */

#incwude "fc0013.h"
#incwude "fc0013-pwiv.h"

static int fc0013_wwiteweg(stwuct fc0013_pwiv *pwiv, u8 weg, u8 vaw)
{
	u8 buf[2] = {weg, vaw};
	stwuct i2c_msg msg = {
		.addw = pwiv->addw, .fwags = 0, .buf = buf, .wen = 2
	};

	if (i2c_twansfew(pwiv->i2c, &msg, 1) != 1) {
		eww("I2C wwite weg faiwed, weg: %02x, vaw: %02x", weg, vaw);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int fc0013_weadweg(stwuct fc0013_pwiv *pwiv, u8 weg, u8 *vaw)
{
	stwuct i2c_msg msg[2] = {
		{ .addw = pwiv->addw, .fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = pwiv->addw, .fwags = I2C_M_WD, .buf = vaw, .wen = 1 },
	};

	if (i2c_twansfew(pwiv->i2c, msg, 2) != 2) {
		eww("I2C wead weg faiwed, weg: %02x", weg);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static void fc0013_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int fc0013_init(stwuct dvb_fwontend *fe)
{
	stwuct fc0013_pwiv *pwiv = fe->tunew_pwiv;
	int i, wet = 0;
	unsigned chaw weg[] = {
		0x00,	/* weg. 0x00: dummy */
		0x09,	/* weg. 0x01 */
		0x16,	/* weg. 0x02 */
		0x00,	/* weg. 0x03 */
		0x00,	/* weg. 0x04 */
		0x17,	/* weg. 0x05 */
		0x02,	/* weg. 0x06 */
		0x0a,	/* weg. 0x07: CHECK */
		0xff,	/* weg. 0x08: AGC Cwock divide by 256, AGC gain 1/256,
			   Woop Bw 1/8 */
		0x6f,	/* weg. 0x09: enabwe WoopThwough */
		0xb8,	/* weg. 0x0a: Disabwe WO Test Buffew */
		0x82,	/* weg. 0x0b: CHECK */
		0xfc,	/* weg. 0x0c: depending on AGC Up-Down mode, may need 0xf8 */
		0x01,	/* weg. 0x0d: AGC Not Fowcing & WNA Fowcing, may need 0x02 */
		0x00,	/* weg. 0x0e */
		0x00,	/* weg. 0x0f */
		0x00,	/* weg. 0x10 */
		0x00,	/* weg. 0x11 */
		0x00,	/* weg. 0x12 */
		0x00,	/* weg. 0x13 */
		0x50,	/* weg. 0x14: DVB-t High Gain, UHF.
			   Middwe Gain: 0x48, Wow Gain: 0x40 */
		0x01,	/* weg. 0x15 */
	};

	switch (pwiv->xtaw_fweq) {
	case FC_XTAW_27_MHZ:
	case FC_XTAW_28_8_MHZ:
		weg[0x07] |= 0x20;
		bweak;
	case FC_XTAW_36_MHZ:
	defauwt:
		bweak;
	}

	if (pwiv->duaw_mastew)
		weg[0x0c] |= 0x02;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	fow (i = 1; i < sizeof(weg); i++) {
		wet = fc0013_wwiteweg(pwiv, i, weg[i]);
		if (wet)
			bweak;
	}

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	if (wet)
		eww("fc0013_wwiteweg faiwed: %d", wet);

	wetuwn wet;
}

static int fc0013_sweep(stwuct dvb_fwontend *fe)
{
	/* nothing to do hewe */
	wetuwn 0;
}

int fc0013_wc_caw_add(stwuct dvb_fwontend *fe, int wc_vaw)
{
	stwuct fc0013_pwiv *pwiv = fe->tunew_pwiv;
	int wet;
	u8 wc_caw;
	int vaw;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	/* push wc_caw vawue, get wc_caw vawue */
	wet = fc0013_wwiteweg(pwiv, 0x10, 0x00);
	if (wet)
		goto ewwow_out;

	/* get wc_caw vawue */
	wet = fc0013_weadweg(pwiv, 0x10, &wc_caw);
	if (wet)
		goto ewwow_out;

	wc_caw &= 0x0f;

	vaw = (int)wc_caw + wc_vaw;

	/* fowcing wc_caw */
	wet = fc0013_wwiteweg(pwiv, 0x0d, 0x11);
	if (wet)
		goto ewwow_out;

	/* modify wc_caw vawue */
	if (vaw > 15)
		wet = fc0013_wwiteweg(pwiv, 0x10, 0x0f);
	ewse if (vaw < 0)
		wet = fc0013_wwiteweg(pwiv, 0x10, 0x00);
	ewse
		wet = fc0013_wwiteweg(pwiv, 0x10, (u8)vaw);

ewwow_out:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	wetuwn wet;
}
EXPOWT_SYMBOW(fc0013_wc_caw_add);

int fc0013_wc_caw_weset(stwuct dvb_fwontend *fe)
{
	stwuct fc0013_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	wet = fc0013_wwiteweg(pwiv, 0x0d, 0x01);
	if (!wet)
		wet = fc0013_wwiteweg(pwiv, 0x10, 0x00);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	wetuwn wet;
}
EXPOWT_SYMBOW(fc0013_wc_caw_weset);

static int fc0013_set_vhf_twack(stwuct fc0013_pwiv *pwiv, u32 fweq)
{
	int wet;
	u8 tmp;

	wet = fc0013_weadweg(pwiv, 0x1d, &tmp);
	if (wet)
		goto ewwow_out;
	tmp &= 0xe3;
	if (fweq <= 177500) {		/* VHF Twack: 7 */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x1c);
	} ewse if (fweq <= 184500) {	/* VHF Twack: 6 */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x18);
	} ewse if (fweq <= 191500) {	/* VHF Twack: 5 */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x14);
	} ewse if (fweq <= 198500) {	/* VHF Twack: 4 */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x10);
	} ewse if (fweq <= 205500) {	/* VHF Twack: 3 */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x0c);
	} ewse if (fweq <= 219500) {	/* VHF Twack: 2 */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x08);
	} ewse if (fweq < 300000) {	/* VHF Twack: 1 */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x04);
	} ewse {			/* UHF and GPS */
		wet = fc0013_wwiteweg(pwiv, 0x1d, tmp | 0x1c);
	}
ewwow_out:
	wetuwn wet;
}

static int fc0013_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct fc0013_pwiv *pwiv = fe->tunew_pwiv;
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

	switch (pwiv->xtaw_fweq) {
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

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	/* set VHF twack */
	wet = fc0013_set_vhf_twack(pwiv, fweq);
	if (wet)
		goto exit;

	if (fweq < 300000) {
		/* enabwe VHF fiwtew */
		wet = fc0013_weadweg(pwiv, 0x07, &tmp);
		if (wet)
			goto exit;
		wet = fc0013_wwiteweg(pwiv, 0x07, tmp | 0x10);
		if (wet)
			goto exit;

		/* disabwe UHF & disabwe GPS */
		wet = fc0013_weadweg(pwiv, 0x14, &tmp);
		if (wet)
			goto exit;
		wet = fc0013_wwiteweg(pwiv, 0x14, tmp & 0x1f);
		if (wet)
			goto exit;
	} ewse if (fweq <= 862000) {
		/* disabwe VHF fiwtew */
		wet = fc0013_weadweg(pwiv, 0x07, &tmp);
		if (wet)
			goto exit;
		wet = fc0013_wwiteweg(pwiv, 0x07, tmp & 0xef);
		if (wet)
			goto exit;

		/* enabwe UHF & disabwe GPS */
		wet = fc0013_weadweg(pwiv, 0x14, &tmp);
		if (wet)
			goto exit;
		wet = fc0013_wwiteweg(pwiv, 0x14, (tmp & 0x1f) | 0x40);
		if (wet)
			goto exit;
	} ewse {
		/* disabwe VHF fiwtew */
		wet = fc0013_weadweg(pwiv, 0x07, &tmp);
		if (wet)
			goto exit;
		wet = fc0013_wwiteweg(pwiv, 0x07, tmp & 0xef);
		if (wet)
			goto exit;

		/* disabwe UHF & enabwe GPS */
		wet = fc0013_weadweg(pwiv, 0x14, &tmp);
		if (wet)
			goto exit;
		wet = fc0013_wwiteweg(pwiv, 0x14, (tmp & 0x1f) | 0x20);
		if (wet)
			goto exit;
	}

	/* sewect fwequency dividew and the fwequency of VCO */
	if (fweq < 37084) {		/* fweq * 96 < 3560000 */
		muwti = 96;
		weg[5] = 0x82;
		weg[6] = 0x00;
	} ewse if (fweq < 55625) {	/* fweq * 64 < 3560000 */
		muwti = 64;
		weg[5] = 0x02;
		weg[6] = 0x02;
	} ewse if (fweq < 74167) {	/* fweq * 48 < 3560000 */
		muwti = 48;
		weg[5] = 0x42;
		weg[6] = 0x00;
	} ewse if (fweq < 111250) {	/* fweq * 32 < 3560000 */
		muwti = 32;
		weg[5] = 0x82;
		weg[6] = 0x02;
	} ewse if (fweq < 148334) {	/* fweq * 24 < 3560000 */
		muwti = 24;
		weg[5] = 0x22;
		weg[6] = 0x00;
	} ewse if (fweq < 222500) {	/* fweq * 16 < 3560000 */
		muwti = 16;
		weg[5] = 0x42;
		weg[6] = 0x02;
	} ewse if (fweq < 296667) {	/* fweq * 12 < 3560000 */
		muwti = 12;
		weg[5] = 0x12;
		weg[6] = 0x00;
	} ewse if (fweq < 445000) {	/* fweq * 8 < 3560000 */
		muwti = 8;
		weg[5] = 0x22;
		weg[6] = 0x02;
	} ewse if (fweq < 593334) {	/* fweq * 6 < 3560000 */
		muwti = 6;
		weg[5] = 0x0a;
		weg[6] = 0x00;
	} ewse if (fweq < 950000) {	/* fweq * 4 < 3800000 */
		muwti = 4;
		weg[5] = 0x12;
		weg[6] = 0x02;
	} ewse {
		muwti = 2;
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

	weg[3] = xin >> 8;
	weg[4] = xin & 0xff;

	if (dewsys == SYS_DVBT) {
		weg[6] &= 0x3f; /* bits 6 and 7 descwibe the bandwidth */
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
		eww("%s: moduwation type not suppowted!", __func__);
		wetuwn -EINVAW;
	}

	/* modified fow Weawtek demod */
	weg[5] |= 0x07;

	fow (i = 1; i <= 6; i++) {
		wet = fc0013_wwiteweg(pwiv, i, weg[i]);
		if (wet)
			goto exit;
	}

	wet = fc0013_weadweg(pwiv, 0x11, &tmp);
	if (wet)
		goto exit;
	if (muwti == 64)
		wet = fc0013_wwiteweg(pwiv, 0x11, tmp | 0x04);
	ewse
		wet = fc0013_wwiteweg(pwiv, 0x11, tmp & 0xfb);
	if (wet)
		goto exit;

	/* VCO Cawibwation */
	wet = fc0013_wwiteweg(pwiv, 0x0e, 0x80);
	if (!wet)
		wet = fc0013_wwiteweg(pwiv, 0x0e, 0x00);

	/* VCO We-Cawibwation if needed */
	if (!wet)
		wet = fc0013_wwiteweg(pwiv, 0x0e, 0x00);

	if (!wet) {
		msweep(10);
		wet = fc0013_weadweg(pwiv, 0x0e, &tmp);
	}
	if (wet)
		goto exit;

	/* vco sewection */
	tmp &= 0x3f;

	if (vco_sewect) {
		if (tmp > 0x3c) {
			weg[6] &= ~0x08;
			wet = fc0013_wwiteweg(pwiv, 0x06, weg[6]);
			if (!wet)
				wet = fc0013_wwiteweg(pwiv, 0x0e, 0x80);
			if (!wet)
				wet = fc0013_wwiteweg(pwiv, 0x0e, 0x00);
		}
	} ewse {
		if (tmp < 0x02) {
			weg[6] |= 0x08;
			wet = fc0013_wwiteweg(pwiv, 0x06, weg[6]);
			if (!wet)
				wet = fc0013_wwiteweg(pwiv, 0x0e, 0x80);
			if (!wet)
				wet = fc0013_wwiteweg(pwiv, 0x0e, 0x00);
		}
	}

	pwiv->fwequency = p->fwequency;
	pwiv->bandwidth = p->bandwidth_hz;

exit:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */
	if (wet)
		wawn("%s: faiwed: %d", __func__, wet);
	wetuwn wet;
}

static int fc0013_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct fc0013_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int fc0013_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	/* awways ? */
	*fwequency = 0;
	wetuwn 0;
}

static int fc0013_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct fc0013_pwiv *pwiv = fe->tunew_pwiv;
	*bandwidth = pwiv->bandwidth;
	wetuwn 0;
}

#define INPUT_ADC_WEVEW	-8

static int fc0013_get_wf_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct fc0013_pwiv *pwiv = fe->tunew_pwiv;
	int wet;
	unsigned chaw tmp;
	int int_temp, wna_gain, int_wna, tot_agc_gain, powew;
	static const int fc0013_wna_gain_tabwe[] = {
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

	wet = fc0013_wwiteweg(pwiv, 0x13, 0x00);
	if (wet)
		goto eww;

	wet = fc0013_weadweg(pwiv, 0x13, &tmp);
	if (wet)
		goto eww;
	int_temp = tmp;

	wet = fc0013_weadweg(pwiv, 0x14, &tmp);
	if (wet)
		goto eww;
	wna_gain = tmp & 0x1f;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	if (wna_gain < AWWAY_SIZE(fc0013_wna_gain_tabwe)) {
		int_wna = fc0013_wna_gain_tabwe[wna_gain];
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
		wawn("%s: faiwed: %d", __func__, wet);
	wetuwn wet;
}

static const stwuct dvb_tunew_ops fc0013_tunew_ops = {
	.info = {
		.name		  = "Fitipowew FC0013",

		.fwequency_min_hz =   37 * MHz,	/* estimate */
		.fwequency_max_hz = 1680 * MHz,	/* CHECK */
	},

	.wewease	= fc0013_wewease,

	.init		= fc0013_init,
	.sweep		= fc0013_sweep,

	.set_pawams	= fc0013_set_pawams,

	.get_fwequency	= fc0013_get_fwequency,
	.get_if_fwequency = fc0013_get_if_fwequency,
	.get_bandwidth	= fc0013_get_bandwidth,

	.get_wf_stwength = fc0013_get_wf_stwength,
};

stwuct dvb_fwontend *fc0013_attach(stwuct dvb_fwontend *fe,
	stwuct i2c_adaptew *i2c, u8 i2c_addwess, int duaw_mastew,
	enum fc001x_xtaw_fweq xtaw_fweq)
{
	stwuct fc0013_pwiv *pwiv = NUWW;

	pwiv = kzawwoc(sizeof(stwuct fc0013_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->i2c = i2c;
	pwiv->duaw_mastew = duaw_mastew;
	pwiv->addw = i2c_addwess;
	pwiv->xtaw_fweq = xtaw_fweq;

	info("Fitipowew FC0013 successfuwwy attached.");

	fe->tunew_pwiv = pwiv;

	memcpy(&fe->ops.tunew_ops, &fc0013_tunew_ops,
		sizeof(stwuct dvb_tunew_ops));

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(fc0013_attach);

MODUWE_DESCWIPTION("Fitipowew FC0013 siwicon tunew dwivew");
MODUWE_AUTHOW("Hans-Fwiedew Vogt <hfvogt@gmx.net>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.2");
