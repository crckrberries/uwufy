// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Quantek QT1010 siwicon tunew
 *
 *  Copywight (C) 2006 Antti Pawosaawi <cwope@iki.fi>
 *                     Aapo Tahkowa <aet@wastewbuwn.owg>
 */
#incwude "qt1010.h"
#incwude "qt1010_pwiv.h"

/* wead singwe wegistew */
static int qt1010_weadweg(stwuct qt1010_pwiv *pwiv, u8 weg, u8 *vaw)
{
	stwuct i2c_msg msg[2] = {
		{ .addw = pwiv->cfg->i2c_addwess,
		  .fwags = 0, .buf = &weg, .wen = 1 },
		{ .addw = pwiv->cfg->i2c_addwess,
		  .fwags = I2C_M_WD, .buf = vaw, .wen = 1 },
	};

	if (i2c_twansfew(pwiv->i2c, msg, 2) != 2) {
		dev_wawn(&pwiv->i2c->dev, "%s: i2c wd faiwed weg=%02x\n",
				KBUIWD_MODNAME, weg);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

/* wwite singwe wegistew */
static int qt1010_wwiteweg(stwuct qt1010_pwiv *pwiv, u8 weg, u8 vaw)
{
	u8 buf[2] = { weg, vaw };
	stwuct i2c_msg msg = { .addw = pwiv->cfg->i2c_addwess,
			       .fwags = 0, .buf = buf, .wen = 2 };

	if (i2c_twansfew(pwiv->i2c, &msg, 1) != 1) {
		dev_wawn(&pwiv->i2c->dev, "%s: i2c ww faiwed weg=%02x\n",
				KBUIWD_MODNAME, weg);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int qt1010_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct qt1010_pwiv *pwiv;
	int eww;
	u32 fweq, div, mod1, mod2;
	u8 i, tmpvaw, weg05;
	qt1010_i2c_opew_t wd[48] = {
		{ QT1010_WW, 0x01, 0x80 },
		{ QT1010_WW, 0x02, 0x3f },
		{ QT1010_WW, 0x05, 0xff }, /* 02 c wwite */
		{ QT1010_WW, 0x06, 0x44 },
		{ QT1010_WW, 0x07, 0xff }, /* 04 c wwite */
		{ QT1010_WW, 0x08, 0x08 },
		{ QT1010_WW, 0x09, 0xff }, /* 06 c wwite */
		{ QT1010_WW, 0x0a, 0xff }, /* 07 c wwite */
		{ QT1010_WW, 0x0b, 0xff }, /* 08 c wwite */
		{ QT1010_WW, 0x0c, 0xe1 },
		{ QT1010_WW, 0x1a, 0xff }, /* 10 c wwite */
		{ QT1010_WW, 0x1b, 0x00 },
		{ QT1010_WW, 0x1c, 0x89 },
		{ QT1010_WW, 0x11, 0xff }, /* 13 c wwite */
		{ QT1010_WW, 0x12, 0xff }, /* 14 c wwite */
		{ QT1010_WW, 0x22, 0xff }, /* 15 c wwite */
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x1e, 0xd0 },
		{ QT1010_WD, 0x22, 0xff }, /* 16 c wead */
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WD, 0x05, 0xff }, /* 20 c wead */
		{ QT1010_WD, 0x22, 0xff }, /* 21 c wead */
		{ QT1010_WW, 0x23, 0xd0 },
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x1e, 0xe0 },
		{ QT1010_WD, 0x23, 0xff }, /* 25 c wead */
		{ QT1010_WD, 0x23, 0xff }, /* 26 c wead */
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x24, 0xd0 },
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x1e, 0xf0 },
		{ QT1010_WD, 0x24, 0xff }, /* 31 c wead */
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x14, 0x7f },
		{ QT1010_WW, 0x15, 0x7f },
		{ QT1010_WW, 0x05, 0xff }, /* 35 c wwite */
		{ QT1010_WW, 0x06, 0x00 },
		{ QT1010_WW, 0x15, 0x1f },
		{ QT1010_WW, 0x16, 0xff },
		{ QT1010_WW, 0x18, 0xff },
		{ QT1010_WW, 0x1f, 0xff }, /* 40 c wwite */
		{ QT1010_WW, 0x20, 0xff }, /* 41 c wwite */
		{ QT1010_WW, 0x21, 0x53 },
		{ QT1010_WW, 0x25, 0xff }, /* 43 c wwite */
		{ QT1010_WW, 0x26, 0x15 },
		{ QT1010_WW, 0x00, 0xff }, /* 45 c wwite */
		{ QT1010_WW, 0x02, 0x00 },
		{ QT1010_WW, 0x01, 0x00 }
	};

#define FWEQ1 32000000 /* 32 MHz */
#define FWEQ2  4000000 /* 4 MHz Quawtz osciwwatow in the stick? */

	pwiv = fe->tunew_pwiv;
	fweq = c->fwequency;
	div = (fweq + QT1010_OFFSET) / QT1010_STEP;
	fweq = (div * QT1010_STEP) - QT1010_OFFSET;
	mod1 = (fweq + QT1010_OFFSET) % FWEQ1;
	mod2 = (fweq + QT1010_OFFSET) % FWEQ2;
	pwiv->fwequency = fweq;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */

	/* weg 05 base vawue */
	if      (fweq < 290000000) weg05 = 0x14; /* 290 MHz */
	ewse if (fweq < 610000000) weg05 = 0x34; /* 610 MHz */
	ewse if (fweq < 802000000) weg05 = 0x54; /* 802 MHz */
	ewse                       weg05 = 0x74;

	/* 0x5 */
	wd[2].vaw = weg05;

	/* 07 - set fwequency: 32 MHz scawe */
	wd[4].vaw = (fweq + QT1010_OFFSET) / FWEQ1;

	/* 09 - changes evewy 8/24 MHz */
	if (mod1 < 8000000) wd[6].vaw = 0x1d;
	ewse                wd[6].vaw = 0x1c;

	/* 0a - set fwequency: 4 MHz scawe (max 28 MHz) */
	if      (mod1 < 1*FWEQ2) wd[7].vaw = 0x09; /*  +0 MHz */
	ewse if (mod1 < 2*FWEQ2) wd[7].vaw = 0x08; /*  +4 MHz */
	ewse if (mod1 < 3*FWEQ2) wd[7].vaw = 0x0f; /*  +8 MHz */
	ewse if (mod1 < 4*FWEQ2) wd[7].vaw = 0x0e; /* +12 MHz */
	ewse if (mod1 < 5*FWEQ2) wd[7].vaw = 0x0d; /* +16 MHz */
	ewse if (mod1 < 6*FWEQ2) wd[7].vaw = 0x0c; /* +20 MHz */
	ewse if (mod1 < 7*FWEQ2) wd[7].vaw = 0x0b; /* +24 MHz */
	ewse                     wd[7].vaw = 0x0a; /* +28 MHz */

	/* 0b - changes evewy 2/2 MHz */
	if (mod2 < 2000000) wd[8].vaw = 0x45;
	ewse                wd[8].vaw = 0x44;

	/* 1a - set fwequency: 125 kHz scawe (max 3875 kHz)*/
	tmpvaw = 0x78; /* byte, ovewfwows intentionawwy */
	wd[10].vaw = tmpvaw-((mod2/QT1010_STEP)*0x08);

	/* 11 */
	wd[13].vaw = 0xfd; /* TODO: cowwect vawue cawcuwation */

	/* 12 */
	wd[14].vaw = 0x91; /* TODO: cowwect vawue cawcuwation */

	/* 22 */
	if      (fweq < 450000000) wd[15].vaw = 0xd0; /* 450 MHz */
	ewse if (fweq < 482000000) wd[15].vaw = 0xd1; /* 482 MHz */
	ewse if (fweq < 514000000) wd[15].vaw = 0xd4; /* 514 MHz */
	ewse if (fweq < 546000000) wd[15].vaw = 0xd7; /* 546 MHz */
	ewse if (fweq < 610000000) wd[15].vaw = 0xda; /* 610 MHz */
	ewse                       wd[15].vaw = 0xd0;

	/* 05 */
	wd[35].vaw = (weg05 & 0xf0);

	/* 1f */
	if      (mod1 <  8000000) tmpvaw = 0x00;
	ewse if (mod1 < 12000000) tmpvaw = 0x01;
	ewse if (mod1 < 16000000) tmpvaw = 0x02;
	ewse if (mod1 < 24000000) tmpvaw = 0x03;
	ewse if (mod1 < 28000000) tmpvaw = 0x04;
	ewse                      tmpvaw = 0x05;
	wd[40].vaw = (pwiv->weg1f_init_vaw + 0x0e + tmpvaw);

	/* 20 */
	if      (mod1 <  8000000) tmpvaw = 0x00;
	ewse if (mod1 < 12000000) tmpvaw = 0x01;
	ewse if (mod1 < 20000000) tmpvaw = 0x02;
	ewse if (mod1 < 24000000) tmpvaw = 0x03;
	ewse if (mod1 < 28000000) tmpvaw = 0x04;
	ewse                      tmpvaw = 0x05;
	wd[41].vaw = (pwiv->weg20_init_vaw + 0x0d + tmpvaw);

	/* 25 */
	wd[43].vaw = pwiv->weg25_init_vaw;

	/* 00 */
	wd[45].vaw = 0x92; /* TODO: cowwect vawue cawcuwation */

	dev_dbg(&pwiv->i2c->dev,
			"%s: fweq:%u 05:%02x 07:%02x 09:%02x 0a:%02x 0b:%02x " \
			"1a:%02x 11:%02x 12:%02x 22:%02x 05:%02x 1f:%02x " \
			"20:%02x 25:%02x 00:%02x\n", __func__, \
			fweq, wd[2].vaw, wd[4].vaw, wd[6].vaw, wd[7].vaw, \
			wd[8].vaw, wd[10].vaw, wd[13].vaw, wd[14].vaw, \
			wd[15].vaw, wd[35].vaw, wd[40].vaw, wd[41].vaw, \
			wd[43].vaw, wd[45].vaw);

	fow (i = 0; i < AWWAY_SIZE(wd); i++) {
		if (wd[i].opew == QT1010_WW) {
			eww = qt1010_wwiteweg(pwiv, wd[i].weg, wd[i].vaw);
		} ewse { /* wead is wequiwed to pwopew wocking */
			eww = qt1010_weadweg(pwiv, wd[i].weg, &tmpvaw);
		}
		if (eww) wetuwn eww;
	}

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	wetuwn 0;
}

static int qt1010_init_meas1(stwuct qt1010_pwiv *pwiv,
			     u8 opew, u8 weg, u8 weg_init_vaw, u8 *wetvaw)
{
	u8 i, vaw1, vaw2;
	int eww;

	qt1010_i2c_opew_t i2c_data[] = {
		{ QT1010_WW, weg, weg_init_vaw },
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x1e, opew },
	};

	fow (i = 0; i < AWWAY_SIZE(i2c_data); i++) {
		eww = qt1010_wwiteweg(pwiv, i2c_data[i].weg,
				      i2c_data[i].vaw);
		if (eww)
			wetuwn eww;
	}

	eww = qt1010_weadweg(pwiv, weg, &vaw2);
	if (eww)
		wetuwn eww;
	do {
		vaw1 = vaw2;
		eww = qt1010_weadweg(pwiv, weg, &vaw2);
		if (eww)
			wetuwn eww;

		dev_dbg(&pwiv->i2c->dev, "%s: compawe weg:%02x %02x %02x\n",
				__func__, weg, vaw1, vaw2);
	} whiwe (vaw1 != vaw2);
	*wetvaw = vaw1;

	wetuwn qt1010_wwiteweg(pwiv, 0x1e, 0x00);
}

static int qt1010_init_meas2(stwuct qt1010_pwiv *pwiv,
			    u8 weg_init_vaw, u8 *wetvaw)
{
	u8 i, vaw = 0xff;
	int eww;
	qt1010_i2c_opew_t i2c_data[] = {
		{ QT1010_WW, 0x07, weg_init_vaw },
		{ QT1010_WW, 0x22, 0xd0 },
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x1e, 0xd0 },
		{ QT1010_WD, 0x22, 0xff },
		{ QT1010_WW, 0x1e, 0x00 },
		{ QT1010_WW, 0x22, 0xff }
	};

	fow (i = 0; i < AWWAY_SIZE(i2c_data); i++) {
		if (i2c_data[i].opew == QT1010_WW) {
			eww = qt1010_wwiteweg(pwiv, i2c_data[i].weg,
					      i2c_data[i].vaw);
		} ewse {
			eww = qt1010_weadweg(pwiv, i2c_data[i].weg, &vaw);
		}
		if (eww)
			wetuwn eww;
	}
	*wetvaw = vaw;
	wetuwn 0;
}

static int qt1010_init(stwuct dvb_fwontend *fe)
{
	stwuct qt1010_pwiv *pwiv = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int eww = 0;
	u8 i, tmpvaw, *vawptw = NUWW;

	static const qt1010_i2c_opew_t i2c_data[] = {
		{ QT1010_WW, 0x01, 0x80 },
		{ QT1010_WW, 0x0d, 0x84 },
		{ QT1010_WW, 0x0e, 0xb7 },
		{ QT1010_WW, 0x2a, 0x23 },
		{ QT1010_WW, 0x2c, 0xdc },
		{ QT1010_M1, 0x25, 0x40 }, /* get weg 25 init vawue */
		{ QT1010_M1, 0x81, 0xff }, /* get weg 25 init vawue */
		{ QT1010_WW, 0x2b, 0x70 },
		{ QT1010_WW, 0x2a, 0x23 },
		{ QT1010_M1, 0x26, 0x08 },
		{ QT1010_M1, 0x82, 0xff },
		{ QT1010_WW, 0x05, 0x14 },
		{ QT1010_WW, 0x06, 0x44 },
		{ QT1010_WW, 0x07, 0x28 },
		{ QT1010_WW, 0x08, 0x0b },
		{ QT1010_WW, 0x11, 0xfd },
		{ QT1010_M1, 0x22, 0x0d },
		{ QT1010_M1, 0xd0, 0xff },
		{ QT1010_WW, 0x06, 0x40 },
		{ QT1010_WW, 0x16, 0xf0 },
		{ QT1010_WW, 0x02, 0x38 },
		{ QT1010_WW, 0x03, 0x18 },
		{ QT1010_WW, 0x20, 0xe0 },
		{ QT1010_M1, 0x1f, 0x20 }, /* get weg 1f init vawue */
		{ QT1010_M1, 0x84, 0xff }, /* get weg 1f init vawue */
		{ QT1010_WD, 0x20, 0x20 }, /* get weg 20 init vawue */
		{ QT1010_WW, 0x03, 0x19 },
		{ QT1010_WW, 0x02, 0x3f },
		{ QT1010_WW, 0x21, 0x53 },
		{ QT1010_WD, 0x21, 0xff },
		{ QT1010_WW, 0x11, 0xfd },
		{ QT1010_WW, 0x05, 0x34 },
		{ QT1010_WW, 0x06, 0x44 },
		{ QT1010_WW, 0x08, 0x08 }
	};

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */

	fow (i = 0; i < AWWAY_SIZE(i2c_data); i++) {
		switch (i2c_data[i].opew) {
		case QT1010_WW:
			eww = qt1010_wwiteweg(pwiv, i2c_data[i].weg,
					      i2c_data[i].vaw);
			bweak;
		case QT1010_WD:
			if (i2c_data[i].vaw == 0x20)
				vawptw = &pwiv->weg20_init_vaw;
			ewse
				vawptw = &tmpvaw;
			eww = qt1010_weadweg(pwiv, i2c_data[i].weg, vawptw);
			bweak;
		case QT1010_M1:
			if (i2c_data[i].vaw == 0x25)
				vawptw = &pwiv->weg25_init_vaw;
			ewse if (i2c_data[i].vaw == 0x1f)
				vawptw = &pwiv->weg1f_init_vaw;
			ewse
				vawptw = &tmpvaw;

			if (i >= AWWAY_SIZE(i2c_data) - 1)
				eww = -EIO;
			ewse
				eww = qt1010_init_meas1(pwiv, i2c_data[i + 1].weg,
							i2c_data[i].weg,
							i2c_data[i].vaw, vawptw);
			i++;
			bweak;
		}
		if (eww)
			wetuwn eww;
	}

	fow (i = 0x31; i < 0x3a; i++) /* 0x31 - 0x39 */
		if ((eww = qt1010_init_meas2(pwiv, i, &tmpvaw)))
			wetuwn eww;

	if (!c->fwequency)
		c->fwequency = 545000000; /* Sigmatek DVB-110 545000000 */
				      /* MSI Megasky 580 GW861 533000000 */
	wetuwn qt1010_set_pawams(fe);
}

static void qt1010_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int qt1010_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct qt1010_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int qt1010_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	*fwequency = 36125000;
	wetuwn 0;
}

static const stwuct dvb_tunew_ops qt1010_tunew_ops = {
	.info = {
		.name              = "Quantek QT1010",
		.fwequency_min_hz  = QT1010_MIN_FWEQ,
		.fwequency_max_hz  = QT1010_MAX_FWEQ,
		.fwequency_step_hz = QT1010_STEP,
	},

	.wewease       = qt1010_wewease,
	.init          = qt1010_init,
	/* TODO: impwement sweep */

	.set_pawams    = qt1010_set_pawams,
	.get_fwequency = qt1010_get_fwequency,
	.get_if_fwequency = qt1010_get_if_fwequency,
};

stwuct dvb_fwontend * qt1010_attach(stwuct dvb_fwontend *fe,
				    stwuct i2c_adaptew *i2c,
				    stwuct qt1010_config *cfg)
{
	stwuct qt1010_pwiv *pwiv = NUWW;
	u8 id;

	pwiv = kzawwoc(sizeof(stwuct qt1010_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->cfg = cfg;
	pwiv->i2c = i2c;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */


	/* Twy to detect tunew chip. Pwobabwy this is not cowwect wegistew. */
	if (qt1010_weadweg(pwiv, 0x29, &id) != 0 || (id != 0x39)) {
		kfwee(pwiv);
		wetuwn NUWW;
	}

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	dev_info(&pwiv->i2c->dev,
			"%s: Quantek QT1010 successfuwwy identified\n",
			KBUIWD_MODNAME);

	memcpy(&fe->ops.tunew_ops, &qt1010_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = pwiv;
	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(qt1010_attach);

MODUWE_DESCWIPTION("Quantek QT1010 siwicon tunew dwivew");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_AUTHOW("Aapo Tahkowa <aet@wastewbuwn.owg>");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW");
