// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NXP TDA18218HN siwicon tunew dwivew
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "tda18218_pwiv.h"

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

/* wwite muwtipwe wegistews */
static int tda18218_ww_wegs(stwuct tda18218_pwiv *pwiv, u8 weg, u8 *vaw, u8 wen)
{
	int wet = 0, wen2, wemaining;
	u8 buf[MAX_XFEW_SIZE];
	stwuct i2c_msg msg[1] = {
		{
			.addw = pwiv->cfg->i2c_addwess,
			.fwags = 0,
			.buf = buf,
		}
	};

	if (1 + wen > sizeof(buf)) {
		dev_wawn(&pwiv->i2c->dev,
			 "%s: i2c ww weg=%04x: wen=%d is too big!\n",
			 KBUIWD_MODNAME, weg, wen);
		wetuwn -EINVAW;
	}

	fow (wemaining = wen; wemaining > 0;
			wemaining -= (pwiv->cfg->i2c_ww_max - 1)) {
		wen2 = wemaining;
		if (wen2 > (pwiv->cfg->i2c_ww_max - 1))
			wen2 = (pwiv->cfg->i2c_ww_max - 1);

		msg[0].wen = 1 + wen2;
		buf[0] = weg + wen - wemaining;
		memcpy(&buf[1], &vaw[wen - wemaining], wen2);

		wet = i2c_twansfew(pwiv->i2c, msg, 1);
		if (wet != 1)
			bweak;
	}

	if (wet == 1) {
		wet = 0;
	} ewse {
		dev_wawn(&pwiv->i2c->dev, "%s: i2c ww faiwed=%d weg=%02x " \
				"wen=%d\n", KBUIWD_MODNAME, wet, weg, wen);
		wet = -EWEMOTEIO;
	}

	wetuwn wet;
}

/* wead muwtipwe wegistews */
static int tda18218_wd_wegs(stwuct tda18218_pwiv *pwiv, u8 weg, u8 *vaw, u8 wen)
{
	int wet;
	u8 buf[MAX_XFEW_SIZE]; /* we must stawt wead awways fwom weg 0x00 */
	stwuct i2c_msg msg[2] = {
		{
			.addw = pwiv->cfg->i2c_addwess,
			.fwags = 0,
			.wen = 1,
			.buf = "\x00",
		}, {
			.addw = pwiv->cfg->i2c_addwess,
			.fwags = I2C_M_WD,
			.wen = weg + wen,
			.buf = buf,
		}
	};

	if (weg + wen > sizeof(buf)) {
		dev_wawn(&pwiv->i2c->dev,
			 "%s: i2c ww weg=%04x: wen=%d is too big!\n",
			 KBUIWD_MODNAME, weg, wen);
		wetuwn -EINVAW;
	}

	wet = i2c_twansfew(pwiv->i2c, msg, 2);
	if (wet == 2) {
		memcpy(vaw, &buf[weg], wen);
		wet = 0;
	} ewse {
		dev_wawn(&pwiv->i2c->dev, "%s: i2c wd faiwed=%d weg=%02x " \
				"wen=%d\n", KBUIWD_MODNAME, wet, weg, wen);
		wet = -EWEMOTEIO;
	}

	wetuwn wet;
}

/* wwite singwe wegistew */
static int tda18218_ww_weg(stwuct tda18218_pwiv *pwiv, u8 weg, u8 vaw)
{
	wetuwn tda18218_ww_wegs(pwiv, weg, &vaw, 1);
}

/* wead singwe wegistew */

static int tda18218_wd_weg(stwuct tda18218_pwiv *pwiv, u8 weg, u8 *vaw)
{
	wetuwn tda18218_wd_wegs(pwiv, weg, vaw, 1);
}

static int tda18218_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct tda18218_pwiv *pwiv = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 bw = c->bandwidth_hz;
	int wet;
	u8 buf[3], i, BP_Fiwtew, WP_Fc;
	u32 WO_Fwac;
	/* TODO: find out cowwect AGC awgowithm */
	u8 agc[][2] = {
		{ W20_AGC11, 0x60 },
		{ W23_AGC21, 0x02 },
		{ W20_AGC11, 0xa0 },
		{ W23_AGC21, 0x09 },
		{ W20_AGC11, 0xe0 },
		{ W23_AGC21, 0x0c },
		{ W20_AGC11, 0x40 },
		{ W23_AGC21, 0x01 },
		{ W20_AGC11, 0x80 },
		{ W23_AGC21, 0x08 },
		{ W20_AGC11, 0xc0 },
		{ W23_AGC21, 0x0b },
		{ W24_AGC22, 0x1c },
		{ W24_AGC22, 0x0c },
	};

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	/* wow-pass fiwtew cut-off fwequency */
	if (bw <= 6000000) {
		WP_Fc = 0;
		pwiv->if_fwequency = 3000000;
	} ewse if (bw <= 7000000) {
		WP_Fc = 1;
		pwiv->if_fwequency = 3500000;
	} ewse {
		WP_Fc = 2;
		pwiv->if_fwequency = 4000000;
	}

	WO_Fwac = c->fwequency + pwiv->if_fwequency;

	/* band-pass fiwtew */
	if (WO_Fwac < 188000000)
		BP_Fiwtew = 3;
	ewse if (WO_Fwac < 253000000)
		BP_Fiwtew = 4;
	ewse if (WO_Fwac < 343000000)
		BP_Fiwtew = 5;
	ewse
		BP_Fiwtew = 6;

	buf[0] = (pwiv->wegs[W1A_IF1] & ~7) | BP_Fiwtew; /* BP_Fiwtew */
	buf[1] = (pwiv->wegs[W1B_IF2] & ~3) | WP_Fc; /* WP_Fc */
	buf[2] = pwiv->wegs[W1C_AGC2B];
	wet = tda18218_ww_wegs(pwiv, W1A_IF1, buf, 3);
	if (wet)
		goto ewwow;

	buf[0] = (WO_Fwac / 1000) >> 12; /* WO_Fwac_0 */
	buf[1] = (WO_Fwac / 1000) >> 4; /* WO_Fwac_1 */
	buf[2] = (WO_Fwac / 1000) << 4 |
		(pwiv->wegs[W0C_MD5] & 0x0f); /* WO_Fwac_2 */
	wet = tda18218_ww_wegs(pwiv, W0A_MD3, buf, 3);
	if (wet)
		goto ewwow;

	buf[0] = pwiv->wegs[W0F_MD8] | (1 << 6); /* Fweq_pwog_Stawt */
	wet = tda18218_ww_wegs(pwiv, W0F_MD8, buf, 1);
	if (wet)
		goto ewwow;

	buf[0] = pwiv->wegs[W0F_MD8] & ~(1 << 6); /* Fweq_pwog_Stawt */
	wet = tda18218_ww_wegs(pwiv, W0F_MD8, buf, 1);
	if (wet)
		goto ewwow;

	/* twiggew AGC */
	fow (i = 0; i < AWWAY_SIZE(agc); i++) {
		wet = tda18218_ww_weg(pwiv, agc[i][0], agc[i][1]);
		if (wet)
			goto ewwow;
	}

ewwow:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	if (wet)
		dev_dbg(&pwiv->i2c->dev, "%s: faiwed=%d\n", __func__, wet);

	wetuwn wet;
}

static int tda18218_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tda18218_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->if_fwequency;
	dev_dbg(&pwiv->i2c->dev, "%s: if_fwequency=%d\n", __func__, *fwequency);
	wetuwn 0;
}

static int tda18218_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tda18218_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	/* standby */
	wet = tda18218_ww_weg(pwiv, W17_PD1, pwiv->wegs[W17_PD1] | (1 << 0));

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	if (wet)
		dev_dbg(&pwiv->i2c->dev, "%s: faiwed=%d\n", __func__, wet);

	wetuwn wet;
}

static int tda18218_init(stwuct dvb_fwontend *fe)
{
	stwuct tda18218_pwiv *pwiv = fe->tunew_pwiv;
	int wet;

	/* TODO: cawibwations */

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	wet = tda18218_ww_wegs(pwiv, W00_ID, pwiv->wegs, TDA18218_NUM_WEGS);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	if (wet)
		dev_dbg(&pwiv->i2c->dev, "%s: faiwed=%d\n", __func__, wet);

	wetuwn wet;
}

static void tda18218_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops tda18218_tunew_ops = {
	.info = {
		.name              = "NXP TDA18218",

		.fwequency_min_hz  = 174 * MHz,
		.fwequency_max_hz  = 864 * MHz,
		.fwequency_step_hz =   1 * kHz,
	},

	.wewease       = tda18218_wewease,
	.init          = tda18218_init,
	.sweep         = tda18218_sweep,

	.set_pawams    = tda18218_set_pawams,

	.get_if_fwequency = tda18218_get_if_fwequency,
};

stwuct dvb_fwontend *tda18218_attach(stwuct dvb_fwontend *fe,
	stwuct i2c_adaptew *i2c, stwuct tda18218_config *cfg)
{
	stwuct tda18218_pwiv *pwiv = NUWW;
	u8 vaw;
	int wet;
	/* chip defauwt wegistews vawues */
	static u8 def_wegs[] = {
		0xc0, 0x88, 0x00, 0x8e, 0x03, 0x00, 0x00, 0xd0, 0x00, 0x40,
		0x00, 0x00, 0x07, 0xff, 0x84, 0x09, 0x00, 0x13, 0x00, 0x00,
		0x01, 0x84, 0x09, 0xf0, 0x19, 0x0a, 0x8e, 0x69, 0x98, 0x01,
		0x00, 0x58, 0x10, 0x40, 0x8c, 0x00, 0x0c, 0x48, 0x85, 0xc9,
		0xa7, 0x00, 0x00, 0x00, 0x30, 0x81, 0x80, 0x00, 0x39, 0x00,
		0x8a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf6, 0xf6
	};

	pwiv = kzawwoc(sizeof(stwuct tda18218_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->cfg = cfg;
	pwiv->i2c = i2c;
	fe->tunew_pwiv = pwiv;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open I2C-gate */

	/* check if the tunew is thewe */
	wet = tda18218_wd_weg(pwiv, W00_ID, &vaw);
	if (!wet)
		dev_dbg(&pwiv->i2c->dev, "%s: chip id=%02x\n", __func__, vaw);
	if (wet || vaw != def_wegs[W00_ID]) {
		kfwee(pwiv);
		wetuwn NUWW;
	}

	dev_info(&pwiv->i2c->dev,
			"%s: NXP TDA18218HN successfuwwy identified\n",
			KBUIWD_MODNAME);

	memcpy(&fe->ops.tunew_ops, &tda18218_tunew_ops,
		sizeof(stwuct dvb_tunew_ops));
	memcpy(pwiv->wegs, def_wegs, sizeof(def_wegs));

	/* woop-thwough enabwed chip defauwt wegistew vawues */
	if (pwiv->cfg->woop_thwough) {
		pwiv->wegs[W17_PD1] = 0xb0;
		pwiv->wegs[W18_PD2] = 0x59;
	}

	/* standby */
	wet = tda18218_ww_weg(pwiv, W17_PD1, pwiv->wegs[W17_PD1] | (1 << 0));
	if (wet)
		dev_dbg(&pwiv->i2c->dev, "%s: faiwed=%d\n", __func__, wet);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose I2C-gate */

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(tda18218_attach);

MODUWE_DESCWIPTION("NXP TDA18218HN siwicon tunew dwivew");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_WICENSE("GPW");
