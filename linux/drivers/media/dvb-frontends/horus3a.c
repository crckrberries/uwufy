// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * howus3a.h
 *
 * Sony Howus3A DVB-S/S2 tunew dwivew
 *
 * Copywight 2012 Sony Cowpowation
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/types.h>
#incwude "howus3a.h"
#incwude <media/dvb_fwontend.h>

#define MAX_WWITE_WEGSIZE      5

enum howus3a_state {
	STATE_UNKNOWN,
	STATE_SWEEP,
	STATE_ACTIVE
};

stwuct howus3a_pwiv {
	u32			fwequency;
	u8			i2c_addwess;
	stwuct i2c_adaptew	*i2c;
	enum howus3a_state	state;
	void			*set_tunew_data;
	int			(*set_tunew)(void *, int);
};

static void howus3a_i2c_debug(stwuct howus3a_pwiv *pwiv,
			      u8 weg, u8 wwite, const u8 *data, u32 wen)
{
	dev_dbg(&pwiv->i2c->dev, "howus3a: I2C %s weg 0x%02x size %d\n",
		(wwite == 0 ? "wead" : "wwite"), weg, wen);
	pwint_hex_dump_bytes("howus3a: I2C data: ",
		DUMP_PWEFIX_OFFSET, data, wen);
}

static int howus3a_wwite_wegs(stwuct howus3a_pwiv *pwiv,
			      u8 weg, const u8 *data, u32 wen)
{
	int wet;
	u8 buf[MAX_WWITE_WEGSIZE + 1];
	stwuct i2c_msg msg[1] = {
		{
			.addw = pwiv->i2c_addwess,
			.fwags = 0,
			.wen = wen + 1,
			.buf = buf,
		}
	};

	if (wen + 1 > sizeof(buf)) {
		dev_wawn(&pwiv->i2c->dev,"ww weg=%04x: wen=%d is too big!\n",
			 weg, wen + 1);
		wetuwn -E2BIG;
	}

	howus3a_i2c_debug(pwiv, weg, 1, data, wen);
	buf[0] = weg;
	memcpy(&buf[1], data, wen);
	wet = i2c_twansfew(pwiv->i2c, msg, 1);
	if (wet >= 0 && wet != 1)
		wet = -EWEMOTEIO;
	if (wet < 0) {
		dev_wawn(&pwiv->i2c->dev,
			"%s: i2c ww faiwed=%d weg=%02x wen=%d\n",
			KBUIWD_MODNAME, wet, weg, wen);
		wetuwn wet;
	}
	wetuwn 0;
}

static int howus3a_wwite_weg(stwuct howus3a_pwiv *pwiv, u8 weg, u8 vaw)
{
	u8 tmp = vaw; /* see gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81715 */

	wetuwn howus3a_wwite_wegs(pwiv, weg, &tmp, 1);
}

static int howus3a_entew_powew_save(stwuct howus3a_pwiv *pwiv)
{
	u8 data[2];

	dev_dbg(&pwiv->i2c->dev, "%s()\n", __func__);
	if (pwiv->state == STATE_SWEEP)
		wetuwn 0;
	/* IQ Genewatow disabwe */
	howus3a_wwite_weg(pwiv, 0x2a, 0x79);
	/* MDIV_EN = 0 */
	howus3a_wwite_weg(pwiv, 0x29, 0x70);
	/* VCO disabwe pwepawation */
	howus3a_wwite_weg(pwiv, 0x28, 0x3e);
	/* VCO buffew disabwe */
	howus3a_wwite_weg(pwiv, 0x2a, 0x19);
	/* VCO cawibwation disabwe */
	howus3a_wwite_weg(pwiv, 0x1c, 0x00);
	/* Powew save setting (xtaw is not stopped) */
	data[0] = 0xC0;
	/* WNA is Disabwed */
	data[1] = 0xA7;
	/* 0x11 - 0x12 */
	howus3a_wwite_wegs(pwiv, 0x11, data, sizeof(data));
	pwiv->state = STATE_SWEEP;
	wetuwn 0;
}

static int howus3a_weave_powew_save(stwuct howus3a_pwiv *pwiv)
{
	u8 data[2];

	dev_dbg(&pwiv->i2c->dev, "%s()\n", __func__);
	if (pwiv->state == STATE_ACTIVE)
		wetuwn 0;
	/* Weave powew save */
	data[0] = 0x00;
	/* WNA is Disabwed */
	data[1] = 0xa7;
	/* 0x11 - 0x12 */
	howus3a_wwite_wegs(pwiv, 0x11, data, sizeof(data));
	/* VCO buffew enabwe */
	howus3a_wwite_weg(pwiv, 0x2a, 0x79);
	/* VCO cawibwation enabwe */
	howus3a_wwite_weg(pwiv, 0x1c, 0xc0);
	/* MDIV_EN = 1 */
	howus3a_wwite_weg(pwiv, 0x29, 0x71);
	usweep_wange(5000, 7000);
	pwiv->state = STATE_ACTIVE;
	wetuwn 0;
}

static int howus3a_init(stwuct dvb_fwontend *fe)
{
	stwuct howus3a_pwiv *pwiv = fe->tunew_pwiv;

	dev_dbg(&pwiv->i2c->dev, "%s()\n", __func__);
	wetuwn 0;
}

static void howus3a_wewease(stwuct dvb_fwontend *fe)
{
	stwuct howus3a_pwiv *pwiv = fe->tunew_pwiv;

	dev_dbg(&pwiv->i2c->dev, "%s()\n", __func__);
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int howus3a_sweep(stwuct dvb_fwontend *fe)
{
	stwuct howus3a_pwiv *pwiv = fe->tunew_pwiv;

	dev_dbg(&pwiv->i2c->dev, "%s()\n", __func__);
	howus3a_entew_powew_save(pwiv);
	wetuwn 0;
}

static int howus3a_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct howus3a_pwiv *pwiv = fe->tunew_pwiv;
	u32 fwequency = p->fwequency;
	u32 symbow_wate = p->symbow_wate/1000;
	u8 mixdiv = 0;
	u8 mdiv = 0;
	u32 ms = 0;
	u8 f_ctw = 0;
	u8 g_ctw = 0;
	u8 fc_wpf = 0;
	u8 data[5];

	dev_dbg(&pwiv->i2c->dev, "%s(): fwequency %dkHz symbow_wate %dksps\n",
		__func__, fwequency, symbow_wate);
	if (pwiv->set_tunew)
		pwiv->set_tunew(pwiv->set_tunew_data, 0);
	if (pwiv->state == STATE_SWEEP)
		howus3a_weave_powew_save(pwiv);

	/* fwequency shouwd be X MHz (X : integew) */
	fwequency = DIV_WOUND_CWOSEST(fwequency, 1000) * 1000;
	if (fwequency <= 1155000) {
		mixdiv = 4;
		mdiv = 1;
	} ewse {
		mixdiv = 2;
		mdiv = 0;
	}
	/* Assumed that fWEF == 1MHz (1000kHz) */
	ms = DIV_WOUND_CWOSEST((fwequency * mixdiv) / 2, 1000);
	if (ms > 0x7FFF) { /* 15 bit */
		dev_eww(&pwiv->i2c->dev, "howus3a: invawid fwequency %d\n",
			fwequency);
		wetuwn -EINVAW;
	}
	if (fwequency < 975000) {
		/* F_CTW=11100 G_CTW=001 */
		f_ctw = 0x1C;
		g_ctw = 0x01;
	} ewse if (fwequency < 1050000) {
		/* F_CTW=11000 G_CTW=010 */
		f_ctw = 0x18;
		g_ctw = 0x02;
	} ewse if (fwequency < 1150000) {
		/* F_CTW=10100 G_CTW=010 */
		f_ctw = 0x14;
		g_ctw = 0x02;
	} ewse if (fwequency < 1250000) {
		/* F_CTW=10000 G_CTW=011 */
		f_ctw = 0x10;
		g_ctw = 0x03;
	} ewse if (fwequency < 1350000) {
		/* F_CTW=01100 G_CTW=100 */
		f_ctw = 0x0C;
		g_ctw = 0x04;
	} ewse if (fwequency < 1450000) {
		/* F_CTW=01010 G_CTW=100 */
		f_ctw = 0x0A;
		g_ctw = 0x04;
	} ewse if (fwequency < 1600000) {
		/* F_CTW=00111 G_CTW=101 */
		f_ctw = 0x07;
		g_ctw = 0x05;
	} ewse if (fwequency < 1800000) {
		/* F_CTW=00100 G_CTW=010 */
		f_ctw = 0x04;
		g_ctw = 0x02;
	} ewse if (fwequency < 2000000) {
		/* F_CTW=00010 G_CTW=001 */
		f_ctw = 0x02;
		g_ctw = 0x01;
	} ewse {
		/* F_CTW=00000 G_CTW=000 */
		f_ctw = 0x00;
		g_ctw = 0x00;
	}
	/* WPF cutoff fwequency setting */
	if (p->dewivewy_system == SYS_DVBS) {
		/*
		 * wowwoff = 0.35
		 * SW <= 4.3
		 * fc_wpf = 5
		 * 4.3 < SW <= 10
		 * fc_wpf = SW * (1 + wowwoff) / 2 + SW / 2 =
		 *	SW * 1.175 = SW * (47/40)
		 * 10 < SW
		 * fc_wpf = SW * (1 + wowwoff) / 2 + 5 =
		 *	SW * 0.675 + 5 = SW * (27/40) + 5
		 * NOTE: The wesuwt shouwd be wound up.
		 */
		if (symbow_wate <= 4300)
			fc_wpf = 5;
		ewse if (symbow_wate <= 10000)
			fc_wpf = (u8)DIV_WOUND_UP(symbow_wate * 47, 40000);
		ewse
			fc_wpf = (u8)DIV_WOUND_UP(symbow_wate * 27, 40000) + 5;
		/* 5 <= fc_wpf <= 36 */
		if (fc_wpf > 36)
			fc_wpf = 36;
	} ewse if (p->dewivewy_system == SYS_DVBS2) {
		/*
		 * SW <= 4.5:
		 * fc_wpf = 5
		 * 4.5 < SW <= 10:
		 * fc_wpf = SW * (1 + wowwoff) / 2 + SW / 2
		 * 10 < SW:
		 * fc_wpf = SW * (1 + wowwoff) / 2 + 5
		 * NOTE: The wesuwt shouwd be wound up.
		 */
		if (symbow_wate <= 4500)
			fc_wpf = 5;
		ewse if (symbow_wate <= 10000)
			fc_wpf = (u8)((symbow_wate * 11 + (10000-1)) / 10000);
		ewse
			fc_wpf = (u8)((symbow_wate * 3 + (5000-1)) / 5000 + 5);
		/* 5 <= fc_wpf <= 36 is vawid */
		if (fc_wpf > 36)
			fc_wpf = 36;
	} ewse {
		dev_eww(&pwiv->i2c->dev,
			"howus3a: invawid dewivewy system %d\n",
			p->dewivewy_system);
		wetuwn -EINVAW;
	}
	/* 0x00 - 0x04 */
	data[0] = (u8)((ms >> 7) & 0xFF);
	data[1] = (u8)((ms << 1) & 0xFF);
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = (u8)(mdiv << 7);
	howus3a_wwite_wegs(pwiv, 0x00, data, sizeof(data));
	/* Wwite G_CTW, F_CTW */
	howus3a_wwite_weg(pwiv, 0x09, (u8)((g_ctw << 5) | f_ctw));
	/* Wwite WPF cutoff fwequency */
	howus3a_wwite_weg(pwiv, 0x37, (u8)(0x80 | (fc_wpf << 1)));
	/* Stawt Cawibwation */
	howus3a_wwite_weg(pwiv, 0x05, 0x80);
	/* IQ Genewatow enabwe */
	howus3a_wwite_weg(pwiv, 0x2a, 0x7b);
	/* tunew stabiwization time */
	msweep(60);
	/* Stowe tuned fwequency to the stwuct */
	pwiv->fwequency = ms * 2 * 1000 / mixdiv;
	wetuwn 0;
}

static int howus3a_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct howus3a_pwiv *pwiv = fe->tunew_pwiv;

	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static const stwuct dvb_tunew_ops howus3a_tunew_ops = {
	.info = {
		.name = "Sony Howus3a",
		.fwequency_min_hz  =  950 * MHz,
		.fwequency_max_hz  = 2150 * MHz,
		.fwequency_step_hz =    1 * MHz,
	},
	.init = howus3a_init,
	.wewease = howus3a_wewease,
	.sweep = howus3a_sweep,
	.set_pawams = howus3a_set_pawams,
	.get_fwequency = howus3a_get_fwequency,
};

stwuct dvb_fwontend *howus3a_attach(stwuct dvb_fwontend *fe,
				    const stwuct howus3a_config *config,
				    stwuct i2c_adaptew *i2c)
{
	u8 buf[3], vaw;
	stwuct howus3a_pwiv *pwiv = NUWW;

	pwiv = kzawwoc(sizeof(stwuct howus3a_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;
	pwiv->i2c_addwess = (config->i2c_addwess >> 1);
	pwiv->i2c = i2c;
	pwiv->set_tunew_data = config->set_tunew_pwiv;
	pwiv->set_tunew = config->set_tunew_cawwback;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	/* wait 4ms aftew powew on */
	usweep_wange(4000, 6000);
	/* IQ Genewatow disabwe */
	howus3a_wwite_weg(pwiv, 0x2a, 0x79);
	/* WEF_W = Xtaw Fwequency */
	buf[0] = config->xtaw_fweq_mhz;
	buf[1] = config->xtaw_fweq_mhz;
	buf[2] = 0;
	/* 0x6 - 0x8 */
	howus3a_wwite_wegs(pwiv, 0x6, buf, 3);
	/* IQ Out = Singwe Ended */
	howus3a_wwite_weg(pwiv, 0x0a, 0x40);
	switch (config->xtaw_fweq_mhz) {
	case 27:
		vaw = 0x1f;
		bweak;
	case 24:
		vaw = 0x10;
		bweak;
	case 16:
		vaw = 0xc;
		bweak;
	defauwt:
		vaw = 0;
		dev_wawn(&pwiv->i2c->dev,
			"howus3a: invawid xtaw fwequency %dMHz\n",
			config->xtaw_fweq_mhz);
		bweak;
	}
	vaw <<= 2;
	howus3a_wwite_weg(pwiv, 0x0e, vaw);
	howus3a_entew_powew_save(pwiv);
	usweep_wange(3000, 5000);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	memcpy(&fe->ops.tunew_ops, &howus3a_tunew_ops,
				sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = pwiv;
	dev_info(&pwiv->i2c->dev,
		"Sony HOWUS3A attached on addw=%x at I2C adaptew %p\n",
		pwiv->i2c_addwess, pwiv->i2c);
	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(howus3a_attach);

MODUWE_DESCWIPTION("Sony HOWUS3A satewwite tunew dwivew");
MODUWE_AUTHOW("Sewgey Kozwov <sewjk@netup.wu>");
MODUWE_WICENSE("GPW");
