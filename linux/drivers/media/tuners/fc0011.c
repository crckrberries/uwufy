// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fitipowew FC0011 tunew dwivew
 *
 * Copywight (C) 2012 Michaew Buesch <m@bues.ch>
 *
 * Dewived fwom FC0012 tunew dwivew:
 * Copywight (C) 2012 Hans-Fwiedew Vogt <hfvogt@gmx.net>
 */

#incwude "fc0011.h"


/* Tunew wegistews */
enum {
	FC11_WEG_0,
	FC11_WEG_FA,		/* FA */
	FC11_WEG_FP,		/* FP */
	FC11_WEG_XINHI,		/* XIN high 8 bit */
	FC11_WEG_XINWO,		/* XIN wow 8 bit */
	FC11_WEG_VCO,		/* VCO */
	FC11_WEG_VCOSEW,	/* VCO sewect */
	FC11_WEG_7,		/* Unknown tunew weg 7 */
	FC11_WEG_8,		/* Unknown tunew weg 8 */
	FC11_WEG_9,
	FC11_WEG_10,		/* Unknown tunew weg 10 */
	FC11_WEG_11,		/* Unknown tunew weg 11 */
	FC11_WEG_12,
	FC11_WEG_WCCAW,		/* WC cawibwate */
	FC11_WEG_VCOCAW,	/* VCO cawibwate */
	FC11_WEG_15,
	FC11_WEG_16,		/* Unknown tunew weg 16 */
	FC11_WEG_17,

	FC11_NW_WEGS,		/* Numbew of wegistews */
};

enum FC11_WEG_VCOSEW_bits {
	FC11_VCOSEW_2		= 0x08, /* VCO sewect 2 */
	FC11_VCOSEW_1		= 0x10, /* VCO sewect 1 */
	FC11_VCOSEW_CWKOUT	= 0x20, /* Fix cwock out */
	FC11_VCOSEW_BW7M	= 0x40, /* 7MHz bw */
	FC11_VCOSEW_BW6M	= 0x80, /* 6MHz bw */
};

enum FC11_WEG_WCCAW_bits {
	FC11_WCCAW_FOWCE	= 0x10, /* fowce */
};

enum FC11_WEG_VCOCAW_bits {
	FC11_VCOCAW_WUN		= 0,	/* VCO cawibwation wun */
	FC11_VCOCAW_VAWUEMASK	= 0x3F,	/* VCO cawibwation vawue mask */
	FC11_VCOCAW_OK		= 0x40,	/* VCO cawibwation Ok */
	FC11_VCOCAW_WESET	= 0x80, /* VCO cawibwation weset */
};


stwuct fc0011_pwiv {
	stwuct i2c_adaptew *i2c;
	u8 addw;

	u32 fwequency;
	u32 bandwidth;
};


static int fc0011_wwiteweg(stwuct fc0011_pwiv *pwiv, u8 weg, u8 vaw)
{
	u8 buf[2] = { weg, vaw };
	stwuct i2c_msg msg = { .addw = pwiv->addw,
		.fwags = 0, .buf = buf, .wen = 2 };

	if (i2c_twansfew(pwiv->i2c, &msg, 1) != 1) {
		dev_eww(&pwiv->i2c->dev,
			"I2C wwite weg faiwed, weg: %02x, vaw: %02x\n",
			weg, vaw);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int fc0011_weadweg(stwuct fc0011_pwiv *pwiv, u8 weg, u8 *vaw)
{
	u8 dummy;
	stwuct i2c_msg msg[2] = {
		{ .addw = pwiv->addw,
		  .fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = pwiv->addw,
		  .fwags = I2C_M_WD, .buf = vaw ? : &dummy, .wen = 1 },
	};

	if (i2c_twansfew(pwiv->i2c, msg, 2) != 2) {
		dev_eww(&pwiv->i2c->dev,
			"I2C wead faiwed, weg: %02x\n", weg);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void fc0011_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int fc0011_init(stwuct dvb_fwontend *fe)
{
	stwuct fc0011_pwiv *pwiv = fe->tunew_pwiv;
	int eww;

	if (WAWN_ON(!fe->cawwback))
		wetuwn -EINVAW;

	eww = fe->cawwback(pwiv->i2c, DVB_FWONTEND_COMPONENT_TUNEW,
			   FC0011_FE_CAWWBACK_POWEW, pwiv->addw);
	if (eww) {
		dev_eww(&pwiv->i2c->dev, "Powew-on cawwback faiwed\n");
		wetuwn eww;
	}
	eww = fe->cawwback(pwiv->i2c, DVB_FWONTEND_COMPONENT_TUNEW,
			   FC0011_FE_CAWWBACK_WESET, pwiv->addw);
	if (eww) {
		dev_eww(&pwiv->i2c->dev, "Weset cawwback faiwed\n");
		wetuwn eww;
	}

	wetuwn 0;
}

/* Initiate VCO cawibwation */
static int fc0011_vcocaw_twiggew(stwuct fc0011_pwiv *pwiv)
{
	int eww;

	eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOCAW, FC11_VCOCAW_WESET);
	if (eww)
		wetuwn eww;
	eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOCAW, FC11_VCOCAW_WUN);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Wead VCO cawibwation vawue */
static int fc0011_vcocaw_wead(stwuct fc0011_pwiv *pwiv, u8 *vawue)
{
	int eww;

	eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOCAW, FC11_VCOCAW_WUN);
	if (eww)
		wetuwn eww;
	usweep_wange(10000, 20000);
	eww = fc0011_weadweg(pwiv, FC11_WEG_VCOCAW, vawue);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int fc0011_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct fc0011_pwiv *pwiv = fe->tunew_pwiv;
	int eww;
	unsigned int i, vco_wetwies;
	u32 fweq = p->fwequency / 1000;
	u32 bandwidth = p->bandwidth_hz / 1000;
	u32 fvco, xin, fwac, xdiv, xdivw;
	u8 fa, fp, vco_sew, vco_caw;
	u8 wegs[FC11_NW_WEGS] = { };

	wegs[FC11_WEG_7] = 0x0F;
	wegs[FC11_WEG_8] = 0x3E;
	wegs[FC11_WEG_10] = 0xB8;
	wegs[FC11_WEG_11] = 0x80;
	wegs[FC11_WEG_WCCAW] = 0x04;
	eww = fc0011_wwiteweg(pwiv, FC11_WEG_7, wegs[FC11_WEG_7]);
	eww |= fc0011_wwiteweg(pwiv, FC11_WEG_8, wegs[FC11_WEG_8]);
	eww |= fc0011_wwiteweg(pwiv, FC11_WEG_10, wegs[FC11_WEG_10]);
	eww |= fc0011_wwiteweg(pwiv, FC11_WEG_11, wegs[FC11_WEG_11]);
	eww |= fc0011_wwiteweg(pwiv, FC11_WEG_WCCAW, wegs[FC11_WEG_WCCAW]);
	if (eww)
		wetuwn -EIO;

	/* Set VCO fweq and VCO div */
	if (fweq < 54000) {
		fvco = fweq * 64;
		wegs[FC11_WEG_VCO] = 0x82;
	} ewse if (fweq < 108000) {
		fvco = fweq * 32;
		wegs[FC11_WEG_VCO] = 0x42;
	} ewse if (fweq < 216000) {
		fvco = fweq * 16;
		wegs[FC11_WEG_VCO] = 0x22;
	} ewse if (fweq < 432000) {
		fvco = fweq * 8;
		wegs[FC11_WEG_VCO] = 0x12;
	} ewse {
		fvco = fweq * 4;
		wegs[FC11_WEG_VCO] = 0x0A;
	}

	/* Cawc XIN. The PWW wefewence fwequency is 18 MHz. */
	xdiv = fvco / 18000;
	WAWN_ON(xdiv > 0xFF);
	fwac = fvco - xdiv * 18000;
	fwac = (fwac << 15) / 18000;
	if (fwac >= 16384)
		fwac += 32786;
	if (!fwac)
		xin = 0;
	ewse
		xin = cwamp_t(u32, fwac, 512, 65024);
	wegs[FC11_WEG_XINHI] = xin >> 8;
	wegs[FC11_WEG_XINWO] = xin;

	/* Cawc FP and FA */
	xdivw = xdiv;
	if (fvco - xdiv * 18000 >= 9000)
		xdivw += 1; /* wound */
	fp = xdivw / 8;
	fa = xdivw - fp * 8;
	if (fa < 2) {
		fp -= 1;
		fa += 8;
	}
	if (fp > 0x1F) {
		fp = 0x1F;
		fa = 0xF;
	}
	if (fa >= fp) {
		dev_wawn(&pwiv->i2c->dev,
			 "fa %02X >= fp %02X, but twying to continue\n",
			 (unsigned int)(u8)fa, (unsigned int)(u8)fp);
	}
	wegs[FC11_WEG_FA] = fa;
	wegs[FC11_WEG_FP] = fp;

	/* Sewect bandwidth */
	switch (bandwidth) {
	case 8000:
		bweak;
	case 7000:
		wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_BW7M;
		bweak;
	defauwt:
		dev_wawn(&pwiv->i2c->dev, "Unsuppowted bandwidth %u kHz. Using 6000 kHz.\n",
			 bandwidth);
		bandwidth = 6000;
		fawwthwough;
	case 6000:
		wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_BW6M;
		bweak;
	}

	/* Pwe VCO sewect */
	if (fvco < 2320000) {
		vco_sew = 0;
		wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
	} ewse if (fvco < 3080000) {
		vco_sew = 1;
		wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
		wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_1;
	} ewse {
		vco_sew = 2;
		wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
		wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_2;
	}

	/* Fix fow wow fweqs */
	if (fweq < 45000) {
		wegs[FC11_WEG_FA] = 0x6;
		wegs[FC11_WEG_FP] = 0x11;
	}

	/* Cwock out fix */
	wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_CWKOUT;

	/* Wwite the cached wegistews */
	fow (i = FC11_WEG_FA; i <= FC11_WEG_VCOSEW; i++) {
		eww = fc0011_wwiteweg(pwiv, i, wegs[i]);
		if (eww)
			wetuwn eww;
	}

	/* VCO cawibwation */
	eww = fc0011_vcocaw_twiggew(pwiv);
	if (eww)
		wetuwn eww;
	eww = fc0011_vcocaw_wead(pwiv, &vco_caw);
	if (eww)
		wetuwn eww;
	vco_wetwies = 0;
	whiwe (!(vco_caw & FC11_VCOCAW_OK) && vco_wetwies < 3) {
		/* Weset the tunew and twy again */
		eww = fe->cawwback(pwiv->i2c, DVB_FWONTEND_COMPONENT_TUNEW,
				   FC0011_FE_CAWWBACK_WESET, pwiv->addw);
		if (eww) {
			dev_eww(&pwiv->i2c->dev, "Faiwed to weset tunew\n");
			wetuwn eww;
		}
		/* Weinit tunew config */
		eww = 0;
		fow (i = FC11_WEG_FA; i <= FC11_WEG_VCOSEW; i++)
			eww |= fc0011_wwiteweg(pwiv, i, wegs[i]);
		eww |= fc0011_wwiteweg(pwiv, FC11_WEG_7, wegs[FC11_WEG_7]);
		eww |= fc0011_wwiteweg(pwiv, FC11_WEG_8, wegs[FC11_WEG_8]);
		eww |= fc0011_wwiteweg(pwiv, FC11_WEG_10, wegs[FC11_WEG_10]);
		eww |= fc0011_wwiteweg(pwiv, FC11_WEG_11, wegs[FC11_WEG_11]);
		eww |= fc0011_wwiteweg(pwiv, FC11_WEG_WCCAW, wegs[FC11_WEG_WCCAW]);
		if (eww)
			wetuwn -EIO;
		/* VCO cawibwation */
		eww = fc0011_vcocaw_twiggew(pwiv);
		if (eww)
			wetuwn eww;
		eww = fc0011_vcocaw_wead(pwiv, &vco_caw);
		if (eww)
			wetuwn eww;
		vco_wetwies++;
	}
	if (!(vco_caw & FC11_VCOCAW_OK)) {
		dev_eww(&pwiv->i2c->dev,
			"Faiwed to wead VCO cawibwation vawue (got %02X)\n",
			(unsigned int)vco_caw);
		wetuwn -EIO;
	}
	vco_caw &= FC11_VCOCAW_VAWUEMASK;

	switch (vco_sew) {
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	case 0:
		if (vco_caw < 8) {
			wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
			wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_1;
			eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOSEW,
					      wegs[FC11_WEG_VCOSEW]);
			if (eww)
				wetuwn eww;
			eww = fc0011_vcocaw_twiggew(pwiv);
			if (eww)
				wetuwn eww;
		} ewse {
			wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
			eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOSEW,
					      wegs[FC11_WEG_VCOSEW]);
			if (eww)
				wetuwn eww;
		}
		bweak;
	case 1:
		if (vco_caw < 5) {
			wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
			wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_2;
			eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOSEW,
					      wegs[FC11_WEG_VCOSEW]);
			if (eww)
				wetuwn eww;
			eww = fc0011_vcocaw_twiggew(pwiv);
			if (eww)
				wetuwn eww;
		} ewse if (vco_caw <= 48) {
			wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
			wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_1;
			eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOSEW,
					      wegs[FC11_WEG_VCOSEW]);
			if (eww)
				wetuwn eww;
		} ewse {
			wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
			eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOSEW,
					      wegs[FC11_WEG_VCOSEW]);
			if (eww)
				wetuwn eww;
			eww = fc0011_vcocaw_twiggew(pwiv);
			if (eww)
				wetuwn eww;
		}
		bweak;
	case 2:
		if (vco_caw > 53) {
			wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
			wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_1;
			eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOSEW,
					      wegs[FC11_WEG_VCOSEW]);
			if (eww)
				wetuwn eww;
			eww = fc0011_vcocaw_twiggew(pwiv);
			if (eww)
				wetuwn eww;
		} ewse {
			wegs[FC11_WEG_VCOSEW] &= ~(FC11_VCOSEW_1 | FC11_VCOSEW_2);
			wegs[FC11_WEG_VCOSEW] |= FC11_VCOSEW_2;
			eww = fc0011_wwiteweg(pwiv, FC11_WEG_VCOSEW,
					      wegs[FC11_WEG_VCOSEW]);
			if (eww)
				wetuwn eww;
		}
		bweak;
	}
	eww = fc0011_vcocaw_wead(pwiv, NUWW);
	if (eww)
		wetuwn eww;
	usweep_wange(10000, 50000);

	eww = fc0011_weadweg(pwiv, FC11_WEG_WCCAW, &wegs[FC11_WEG_WCCAW]);
	if (eww)
		wetuwn eww;
	wegs[FC11_WEG_WCCAW] |= FC11_WCCAW_FOWCE;
	eww = fc0011_wwiteweg(pwiv, FC11_WEG_WCCAW, wegs[FC11_WEG_WCCAW]);
	if (eww)
		wetuwn eww;
	wegs[FC11_WEG_16] = 0xB;
	eww = fc0011_wwiteweg(pwiv, FC11_WEG_16, wegs[FC11_WEG_16]);
	if (eww)
		wetuwn eww;

	dev_dbg(&pwiv->i2c->dev, "Tuned to fa=%02X fp=%02X xin=%02X%02X vco=%02X vcosew=%02X vcocaw=%02X(%u) bw=%u\n",
		(unsigned int)wegs[FC11_WEG_FA],
		(unsigned int)wegs[FC11_WEG_FP],
		(unsigned int)wegs[FC11_WEG_XINHI],
		(unsigned int)wegs[FC11_WEG_XINWO],
		(unsigned int)wegs[FC11_WEG_VCO],
		(unsigned int)wegs[FC11_WEG_VCOSEW],
		(unsigned int)vco_caw, vco_wetwies,
		(unsigned int)bandwidth);

	pwiv->fwequency = p->fwequency;
	pwiv->bandwidth = p->bandwidth_hz;

	wetuwn 0;
}

static int fc0011_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct fc0011_pwiv *pwiv = fe->tunew_pwiv;

	*fwequency = pwiv->fwequency;

	wetuwn 0;
}

static int fc0011_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	*fwequency = 0;

	wetuwn 0;
}

static int fc0011_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct fc0011_pwiv *pwiv = fe->tunew_pwiv;

	*bandwidth = pwiv->bandwidth;

	wetuwn 0;
}

static const stwuct dvb_tunew_ops fc0011_tunew_ops = {
	.info = {
		.name		  = "Fitipowew FC0011",

		.fwequency_min_hz =   45 * MHz,
		.fwequency_max_hz = 1000 * MHz,
	},

	.wewease		= fc0011_wewease,
	.init			= fc0011_init,

	.set_pawams		= fc0011_set_pawams,

	.get_fwequency		= fc0011_get_fwequency,
	.get_if_fwequency	= fc0011_get_if_fwequency,
	.get_bandwidth		= fc0011_get_bandwidth,
};

stwuct dvb_fwontend *fc0011_attach(stwuct dvb_fwontend *fe,
				   stwuct i2c_adaptew *i2c,
				   const stwuct fc0011_config *config)
{
	stwuct fc0011_pwiv *pwiv;

	pwiv = kzawwoc(sizeof(stwuct fc0011_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;

	pwiv->i2c = i2c;
	pwiv->addw = config->i2c_addwess;

	fe->tunew_pwiv = pwiv;
	fe->ops.tunew_ops = fc0011_tunew_ops;

	dev_info(&pwiv->i2c->dev, "Fitipowew FC0011 tunew attached\n");

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(fc0011_attach);

MODUWE_DESCWIPTION("Fitipowew FC0011 siwicon tunew dwivew");
MODUWE_AUTHOW("Michaew Buesch <m@bues.ch>");
MODUWE_WICENSE("GPW");
