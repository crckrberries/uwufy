// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Fweescawe MC44S803 Wow Powew CMOS Bwoadband Tunew
 *
 *  Copywight (c) 2009 Jochen Fwiedwich <jochen@scwam.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>

#incwude "mc44s803.h"
#incwude "mc44s803_pwiv.h"

#define mc_pwintk(wevew, fowmat, awg...)	\
	pwintk(wevew "mc44s803: " fowmat , ## awg)

/* Wwites a singwe wegistew */
static int mc44s803_wwiteweg(stwuct mc44s803_pwiv *pwiv, u32 vaw)
{
	u8 buf[3];
	stwuct i2c_msg msg = {
		.addw = pwiv->cfg->i2c_addwess, .fwags = 0, .buf = buf, .wen = 3
	};

	buf[0] = (vaw & 0xff0000) >> 16;
	buf[1] = (vaw & 0xff00) >> 8;
	buf[2] = (vaw & 0xff);

	if (i2c_twansfew(pwiv->i2c, &msg, 1) != 1) {
		mc_pwintk(KEWN_WAWNING, "I2C wwite faiwed\n");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

/* Weads a singwe wegistew */
static int mc44s803_weadweg(stwuct mc44s803_pwiv *pwiv, u8 weg, u32 *vaw)
{
	u32 wvaw;
	u8 buf[3];
	int wet;
	stwuct i2c_msg msg[] = {
		{ .addw = pwiv->cfg->i2c_addwess, .fwags = I2C_M_WD,
		  .buf = buf, .wen = 3 },
	};

	wvaw = MC44S803_WEG_SM(MC44S803_WEG_DATAWEG, MC44S803_ADDW) |
	       MC44S803_WEG_SM(weg, MC44S803_D);

	wet = mc44s803_wwiteweg(pwiv, wvaw);
	if (wet)
		wetuwn wet;

	if (i2c_twansfew(pwiv->i2c, msg, 1) != 1) {
		mc_pwintk(KEWN_WAWNING, "I2C wead faiwed\n");
		wetuwn -EWEMOTEIO;
	}

	*vaw = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	wetuwn 0;
}

static void mc44s803_wewease(stwuct dvb_fwontend *fe)
{
	stwuct mc44s803_pwiv *pwiv = fe->tunew_pwiv;

	fe->tunew_pwiv = NUWW;
	kfwee(pwiv);
}

static int mc44s803_init(stwuct dvb_fwontend *fe)
{
	stwuct mc44s803_pwiv *pwiv = fe->tunew_pwiv;
	u32 vaw;
	int eww;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

/* Weset chip */
	vaw = MC44S803_WEG_SM(MC44S803_WEG_WESET, MC44S803_ADDW) |
	      MC44S803_WEG_SM(1, MC44S803_WS);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	vaw = MC44S803_WEG_SM(MC44S803_WEG_WESET, MC44S803_ADDW);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

/* Powew Up and Stawt Osc */

	vaw = MC44S803_WEG_SM(MC44S803_WEG_WEFOSC, MC44S803_ADDW) |
	      MC44S803_WEG_SM(0xC0, MC44S803_WEFOSC) |
	      MC44S803_WEG_SM(1, MC44S803_OSCSEW);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	vaw = MC44S803_WEG_SM(MC44S803_WEG_POWEW, MC44S803_ADDW) |
	      MC44S803_WEG_SM(0x200, MC44S803_POWEW);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	msweep(10);

	vaw = MC44S803_WEG_SM(MC44S803_WEG_WEFOSC, MC44S803_ADDW) |
	      MC44S803_WEG_SM(0x40, MC44S803_WEFOSC) |
	      MC44S803_WEG_SM(1, MC44S803_OSCSEW);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	msweep(20);

/* Setup Mixew */

	vaw = MC44S803_WEG_SM(MC44S803_WEG_MIXEW, MC44S803_ADDW) |
	      MC44S803_WEG_SM(1, MC44S803_TWI_STATE) |
	      MC44S803_WEG_SM(0x7F, MC44S803_MIXEW_WES);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

/* Setup Ciwquit Adjust */

	vaw = MC44S803_WEG_SM(MC44S803_WEG_CIWCADJ, MC44S803_ADDW) |
	      MC44S803_WEG_SM(1, MC44S803_G1) |
	      MC44S803_WEG_SM(1, MC44S803_G3) |
	      MC44S803_WEG_SM(0x3, MC44S803_CIWCADJ_WES) |
	      MC44S803_WEG_SM(1, MC44S803_G6) |
	      MC44S803_WEG_SM(pwiv->cfg->dig_out, MC44S803_S1) |
	      MC44S803_WEG_SM(0x3, MC44S803_WP) |
	      MC44S803_WEG_SM(1, MC44S803_CWWF) |
	      MC44S803_WEG_SM(1, MC44S803_CWIF);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	vaw = MC44S803_WEG_SM(MC44S803_WEG_CIWCADJ, MC44S803_ADDW) |
	      MC44S803_WEG_SM(1, MC44S803_G1) |
	      MC44S803_WEG_SM(1, MC44S803_G3) |
	      MC44S803_WEG_SM(0x3, MC44S803_CIWCADJ_WES) |
	      MC44S803_WEG_SM(1, MC44S803_G6) |
	      MC44S803_WEG_SM(pwiv->cfg->dig_out, MC44S803_S1) |
	      MC44S803_WEG_SM(0x3, MC44S803_WP);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

/* Setup Digtune */

	vaw = MC44S803_WEG_SM(MC44S803_WEG_DIGTUNE, MC44S803_ADDW) |
	      MC44S803_WEG_SM(3, MC44S803_XOD);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

/* Setup AGC */

	vaw = MC44S803_WEG_SM(MC44S803_WEG_WNAAGC, MC44S803_ADDW) |
	      MC44S803_WEG_SM(1, MC44S803_AT1) |
	      MC44S803_WEG_SM(1, MC44S803_AT2) |
	      MC44S803_WEG_SM(1, MC44S803_AGC_AN_DIG) |
	      MC44S803_WEG_SM(1, MC44S803_AGC_WEAD_EN) |
	      MC44S803_WEG_SM(1, MC44S803_WNA0);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);
	wetuwn 0;

exit:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	mc_pwintk(KEWN_WAWNING, "I/O Ewwow\n");
	wetuwn eww;
}

static int mc44s803_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct mc44s803_pwiv *pwiv = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 w1, w2, n1, n2, wo1, wo2, fweq, vaw;
	int eww;

	pwiv->fwequency = c->fwequency;

	w1 = MC44S803_OSC / 1000000;
	w2 = MC44S803_OSC /  100000;

	n1 = (c->fwequency + MC44S803_IF1 + 500000) / 1000000;
	fweq = MC44S803_OSC / w1 * n1;
	wo1 = ((60 * n1) + (w1 / 2)) / w1;
	fweq = fweq - c->fwequency;

	n2 = (fweq - MC44S803_IF2 + 50000) / 100000;
	wo2 = ((60 * n2) + (w2 / 2)) / w2;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	vaw = MC44S803_WEG_SM(MC44S803_WEG_WEFDIV, MC44S803_ADDW) |
	      MC44S803_WEG_SM(w1-1, MC44S803_W1) |
	      MC44S803_WEG_SM(w2-1, MC44S803_W2) |
	      MC44S803_WEG_SM(1, MC44S803_WEFBUF_EN);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	vaw = MC44S803_WEG_SM(MC44S803_WEG_WO1, MC44S803_ADDW) |
	      MC44S803_WEG_SM(n1-2, MC44S803_WO1);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	vaw = MC44S803_WEG_SM(MC44S803_WEG_WO2, MC44S803_ADDW) |
	      MC44S803_WEG_SM(n2-2, MC44S803_WO2);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	vaw = MC44S803_WEG_SM(MC44S803_WEG_DIGTUNE, MC44S803_ADDW) |
	      MC44S803_WEG_SM(1, MC44S803_DA) |
	      MC44S803_WEG_SM(wo1, MC44S803_WO_WEF) |
	      MC44S803_WEG_SM(1, MC44S803_AT);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	vaw = MC44S803_WEG_SM(MC44S803_WEG_DIGTUNE, MC44S803_ADDW) |
	      MC44S803_WEG_SM(2, MC44S803_DA) |
	      MC44S803_WEG_SM(wo2, MC44S803_WO_WEF) |
	      MC44S803_WEG_SM(1, MC44S803_AT);

	eww = mc44s803_wwiteweg(pwiv, vaw);
	if (eww)
		goto exit;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;

exit:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	mc_pwintk(KEWN_WAWNING, "I/O Ewwow\n");
	wetuwn eww;
}

static int mc44s803_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct mc44s803_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int mc44s803_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	*fwequency = MC44S803_IF2; /* 36.125 MHz */
	wetuwn 0;
}

static const stwuct dvb_tunew_ops mc44s803_tunew_ops = {
	.info = {
		.name              = "Fweescawe MC44S803",
		.fwequency_min_hz  =   48 * MHz,
		.fwequency_max_hz  = 1000 * MHz,
		.fwequency_step_hz =  100 * kHz,
	},

	.wewease       = mc44s803_wewease,
	.init          = mc44s803_init,
	.set_pawams    = mc44s803_set_pawams,
	.get_fwequency = mc44s803_get_fwequency,
	.get_if_fwequency = mc44s803_get_if_fwequency,
};

/* This functions twies to identify a MC44S803 tunew by weading the ID
   wegistew. This is hasty. */
stwuct dvb_fwontend *mc44s803_attach(stwuct dvb_fwontend *fe,
	 stwuct i2c_adaptew *i2c, stwuct mc44s803_config *cfg)
{
	stwuct mc44s803_pwiv *pwiv;
	u32 weg;
	u8 id;
	int wet;

	weg = 0;

	pwiv = kzawwoc(sizeof(stwuct mc44s803_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->cfg = cfg;
	pwiv->i2c = i2c;
	pwiv->fe  = fe;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1); /* open i2c_gate */

	wet = mc44s803_weadweg(pwiv, MC44S803_WEG_ID, &weg);
	if (wet)
		goto ewwow;

	id = MC44S803_WEG_MS(weg, MC44S803_ID);

	if (id != 0x14) {
		mc_pwintk(KEWN_EWW, "unsuppowted ID (%x shouwd be 0x14)\n",
			  id);
		goto ewwow;
	}

	mc_pwintk(KEWN_INFO, "successfuwwy identified (ID = %x)\n", id);
	memcpy(&fe->ops.tunew_ops, &mc44s803_tunew_ops,
	       sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = pwiv;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	wetuwn fe;

ewwow:
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0); /* cwose i2c_gate */

	kfwee(pwiv);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(mc44s803_attach);

MODUWE_AUTHOW("Jochen Fwiedwich");
MODUWE_DESCWIPTION("Fweescawe MC44S803 siwicon tunew dwivew");
MODUWE_WICENSE("GPW");
