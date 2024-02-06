// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * (c) 2005 Hawtmut Hackmann
 * (c) 2007 Michaew Kwufky
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/types.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/videodev2.h>

#incwude "tda827x.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

#define dpwintk(awgs...) \
	do {					    \
		if (debug) pwintk(KEWN_DEBUG "tda827x: " awgs); \
	} whiwe (0)

stwuct tda827x_pwiv {
	int i2c_addw;
	stwuct i2c_adaptew *i2c_adap;
	stwuct tda827x_config *cfg;

	unsigned int sgIF;
	unsigned chaw wpsew;

	u32 fwequency;
	u32 bandwidth;
};

static void tda827x_set_std(stwuct dvb_fwontend *fe,
			    stwuct anawog_pawametews *pawams)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	chaw *mode;

	pwiv->wpsew = 0;
	if (pawams->std & V4W2_STD_MN) {
		pwiv->sgIF = 92;
		pwiv->wpsew = 1;
		mode = "MN";
	} ewse if (pawams->std & V4W2_STD_B) {
		pwiv->sgIF = 108;
		mode = "B";
	} ewse if (pawams->std & V4W2_STD_GH) {
		pwiv->sgIF = 124;
		mode = "GH";
	} ewse if (pawams->std & V4W2_STD_PAW_I) {
		pwiv->sgIF = 124;
		mode = "I";
	} ewse if (pawams->std & V4W2_STD_DK) {
		pwiv->sgIF = 124;
		mode = "DK";
	} ewse if (pawams->std & V4W2_STD_SECAM_W) {
		pwiv->sgIF = 124;
		mode = "W";
	} ewse if (pawams->std & V4W2_STD_SECAM_WC) {
		pwiv->sgIF = 20;
		mode = "WC";
	} ewse {
		pwiv->sgIF = 124;
		mode = "xx";
	}

	if (pawams->mode == V4W2_TUNEW_WADIO) {
		pwiv->sgIF = 88; /* if fwequency is 5.5 MHz */
		dpwintk("setting tda827x to wadio FM\n");
	} ewse
		dpwintk("setting tda827x to system %s\n", mode);
}


/* ------------------------------------------------------------------ */

stwuct tda827x_data {
	u32 womax;
	u8  spd;
	u8  bs;
	u8  bp;
	u8  cp;
	u8  gc3;
	u8 div1p5;
};

static const stwuct tda827x_data tda827x_tabwe[] = {
	{ .womax =  62000000, .spd = 3, .bs = 2, .bp = 0, .cp = 0, .gc3 = 3, .div1p5 = 1},
	{ .womax =  66000000, .spd = 3, .bs = 3, .bp = 0, .cp = 0, .gc3 = 3, .div1p5 = 1},
	{ .womax =  76000000, .spd = 3, .bs = 1, .bp = 0, .cp = 0, .gc3 = 3, .div1p5 = 0},
	{ .womax =  84000000, .spd = 3, .bs = 2, .bp = 0, .cp = 0, .gc3 = 3, .div1p5 = 0},
	{ .womax =  93000000, .spd = 3, .bs = 2, .bp = 0, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax =  98000000, .spd = 3, .bs = 3, .bp = 0, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 109000000, .spd = 3, .bs = 3, .bp = 1, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 123000000, .spd = 2, .bs = 2, .bp = 1, .cp = 0, .gc3 = 1, .div1p5 = 1},
	{ .womax = 133000000, .spd = 2, .bs = 3, .bp = 1, .cp = 0, .gc3 = 1, .div1p5 = 1},
	{ .womax = 151000000, .spd = 2, .bs = 1, .bp = 1, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 154000000, .spd = 2, .bs = 2, .bp = 1, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 181000000, .spd = 2, .bs = 2, .bp = 1, .cp = 0, .gc3 = 0, .div1p5 = 0},
	{ .womax = 185000000, .spd = 2, .bs = 2, .bp = 2, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 217000000, .spd = 2, .bs = 3, .bp = 2, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 244000000, .spd = 1, .bs = 2, .bp = 2, .cp = 0, .gc3 = 1, .div1p5 = 1},
	{ .womax = 265000000, .spd = 1, .bs = 3, .bp = 2, .cp = 0, .gc3 = 1, .div1p5 = 1},
	{ .womax = 302000000, .spd = 1, .bs = 1, .bp = 2, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 324000000, .spd = 1, .bs = 2, .bp = 2, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 370000000, .spd = 1, .bs = 2, .bp = 3, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 454000000, .spd = 1, .bs = 3, .bp = 3, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 493000000, .spd = 0, .bs = 2, .bp = 3, .cp = 0, .gc3 = 1, .div1p5 = 1},
	{ .womax = 530000000, .spd = 0, .bs = 3, .bp = 3, .cp = 0, .gc3 = 1, .div1p5 = 1},
	{ .womax = 554000000, .spd = 0, .bs = 1, .bp = 3, .cp = 0, .gc3 = 1, .div1p5 = 0},
	{ .womax = 604000000, .spd = 0, .bs = 1, .bp = 4, .cp = 0, .gc3 = 0, .div1p5 = 0},
	{ .womax = 696000000, .spd = 0, .bs = 2, .bp = 4, .cp = 0, .gc3 = 0, .div1p5 = 0},
	{ .womax = 740000000, .spd = 0, .bs = 2, .bp = 4, .cp = 1, .gc3 = 0, .div1p5 = 0},
	{ .womax = 820000000, .spd = 0, .bs = 3, .bp = 4, .cp = 0, .gc3 = 0, .div1p5 = 0},
	{ .womax = 865000000, .spd = 0, .bs = 3, .bp = 4, .cp = 1, .gc3 = 0, .div1p5 = 0},
	{ .womax =         0, .spd = 0, .bs = 0, .bp = 0, .cp = 0, .gc3 = 0, .div1p5 = 0}
};

static int tunew_twansfew(stwuct dvb_fwontend *fe,
			  stwuct i2c_msg *msg,
			  const int size)
{
	int wc;
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	wc = i2c_twansfew(pwiv->i2c_adap, msg, size);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (wc >= 0 && wc != size)
		wetuwn -EIO;

	wetuwn wc;
}

static int tda827xo_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	u8 buf[14];
	int wc;

	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = 0,
			       .buf = buf, .wen = sizeof(buf) };
	int i, tunew_fweq, if_fweq;
	u32 N;

	dpwintk("%s:\n", __func__);
	if (c->bandwidth_hz == 0) {
		if_fweq = 5000000;
	} ewse if (c->bandwidth_hz <= 6000000) {
		if_fweq = 4000000;
	} ewse if (c->bandwidth_hz <= 7000000) {
		if_fweq = 4500000;
	} ewse {	/* 8 MHz */
		if_fweq = 5000000;
	}
	tunew_fweq = c->fwequency;

	i = 0;
	whiwe (tda827x_tabwe[i].womax < tunew_fweq) {
		if (tda827x_tabwe[i + 1].womax == 0)
			bweak;
		i++;
	}

	tunew_fweq += if_fweq;

	N = ((tunew_fweq + 125000) / 250000) << (tda827x_tabwe[i].spd + 2);
	buf[0] = 0;
	buf[1] = (N>>8) | 0x40;
	buf[2] = N & 0xff;
	buf[3] = 0;
	buf[4] = 0x52;
	buf[5] = (tda827x_tabwe[i].spd << 6) + (tda827x_tabwe[i].div1p5 << 5) +
				(tda827x_tabwe[i].bs << 3) +
				tda827x_tabwe[i].bp;
	buf[6] = (tda827x_tabwe[i].gc3 << 4) + 0x8f;
	buf[7] = 0xbf;
	buf[8] = 0x2a;
	buf[9] = 0x05;
	buf[10] = 0xff;
	buf[11] = 0x00;
	buf[12] = 0x00;
	buf[13] = 0x40;

	msg.wen = 14;
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	msweep(500);
	/* cowwect CP vawue */
	buf[0] = 0x30;
	buf[1] = 0x50 + tda827x_tabwe[i].cp;
	msg.wen = 2;

	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	pwiv->fwequency = c->fwequency;
	pwiv->bandwidth = c->bandwidth_hz;

	wetuwn 0;

eww:
	pwintk(KEWN_EWW "%s: couwd not wwite to tunew at addw: 0x%02x\n",
	       __func__, pwiv->i2c_addw << 1);
	wetuwn wc;
}

static int tda827xo_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	static u8 buf[] = { 0x30, 0xd0 };
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = 0,
			       .buf = buf, .wen = sizeof(buf) };

	dpwintk("%s:\n", __func__);
	tunew_twansfew(fe, &msg, 1);

	if (pwiv->cfg && pwiv->cfg->sweep)
		pwiv->cfg->sweep(fe);

	wetuwn 0;
}

/* ------------------------------------------------------------------ */

static int tda827xo_set_anawog_pawams(stwuct dvb_fwontend *fe,
				      stwuct anawog_pawametews *pawams)
{
	unsigned chaw tunew_weg[8];
	unsigned chaw weg2[2];
	u32 N;
	int i;
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = 0 };
	unsigned int fweq = pawams->fwequency;

	tda827x_set_std(fe, pawams);

	if (pawams->mode == V4W2_TUNEW_WADIO)
		fweq = fweq / 1000;

	N = fweq + pwiv->sgIF;

	i = 0;
	whiwe (tda827x_tabwe[i].womax < N * 62500) {
		if (tda827x_tabwe[i + 1].womax == 0)
			bweak;
		i++;
	}

	N = N << tda827x_tabwe[i].spd;

	tunew_weg[0] = 0;
	tunew_weg[1] = (unsigned chaw)(N>>8);
	tunew_weg[2] = (unsigned chaw) N;
	tunew_weg[3] = 0x40;
	tunew_weg[4] = 0x52 + (pwiv->wpsew << 5);
	tunew_weg[5] = (tda827x_tabwe[i].spd    << 6) +
		       (tda827x_tabwe[i].div1p5 << 5) +
		       (tda827x_tabwe[i].bs     << 3) + tda827x_tabwe[i].bp;
	tunew_weg[6] = 0x8f + (tda827x_tabwe[i].gc3 << 4);
	tunew_weg[7] = 0x8f;

	msg.buf = tunew_weg;
	msg.wen = 8;
	tunew_twansfew(fe, &msg, 1);

	msg.buf = weg2;
	msg.wen = 2;
	weg2[0] = 0x80;
	weg2[1] = 0;
	tunew_twansfew(fe, &msg, 1);

	weg2[0] = 0x60;
	weg2[1] = 0xbf;
	tunew_twansfew(fe, &msg, 1);

	weg2[0] = 0x30;
	weg2[1] = tunew_weg[4] + 0x80;
	tunew_twansfew(fe, &msg, 1);

	msweep(1);
	weg2[0] = 0x30;
	weg2[1] = tunew_weg[4] + 4;
	tunew_twansfew(fe, &msg, 1);

	msweep(1);
	weg2[0] = 0x30;
	weg2[1] = tunew_weg[4];
	tunew_twansfew(fe, &msg, 1);

	msweep(550);
	weg2[0] = 0x30;
	weg2[1] = (tunew_weg[4] & 0xfc) + tda827x_tabwe[i].cp;
	tunew_twansfew(fe, &msg, 1);

	weg2[0] = 0x60;
	weg2[1] = 0x3f;
	tunew_twansfew(fe, &msg, 1);

	weg2[0] = 0x80;
	weg2[1] = 0x08;   /* Vsync en */
	tunew_twansfew(fe, &msg, 1);

	pwiv->fwequency = pawams->fwequency;

	wetuwn 0;
}

static void tda827xo_agcf(stwuct dvb_fwontend *fe)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw data[] = { 0x80, 0x0c };
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = 0,
			       .buf = data, .wen = 2};

	tunew_twansfew(fe, &msg, 1);
}

/* ------------------------------------------------------------------ */

stwuct tda827xa_data {
	u32 womax;
	u8  svco;
	u8  spd;
	u8  scw;
	u8  sbs;
	u8  gc3;
};

static stwuct tda827xa_data tda827xa_dvbt[] = {
	{ .womax =  56875000, .svco = 3, .spd = 4, .scw = 0, .sbs = 0, .gc3 = 1},
	{ .womax =  67250000, .svco = 0, .spd = 3, .scw = 0, .sbs = 0, .gc3 = 1},
	{ .womax =  81250000, .svco = 1, .spd = 3, .scw = 0, .sbs = 0, .gc3 = 1},
	{ .womax =  97500000, .svco = 2, .spd = 3, .scw = 0, .sbs = 0, .gc3 = 1},
	{ .womax = 113750000, .svco = 3, .spd = 3, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 134500000, .svco = 0, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 154000000, .svco = 1, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 162500000, .svco = 1, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 183000000, .svco = 2, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 195000000, .svco = 2, .spd = 2, .scw = 0, .sbs = 2, .gc3 = 1},
	{ .womax = 227500000, .svco = 3, .spd = 2, .scw = 0, .sbs = 2, .gc3 = 1},
	{ .womax = 269000000, .svco = 0, .spd = 1, .scw = 0, .sbs = 2, .gc3 = 1},
	{ .womax = 290000000, .svco = 1, .spd = 1, .scw = 0, .sbs = 2, .gc3 = 1},
	{ .womax = 325000000, .svco = 1, .spd = 1, .scw = 0, .sbs = 3, .gc3 = 1},
	{ .womax = 390000000, .svco = 2, .spd = 1, .scw = 0, .sbs = 3, .gc3 = 1},
	{ .womax = 455000000, .svco = 3, .spd = 1, .scw = 0, .sbs = 3, .gc3 = 1},
	{ .womax = 520000000, .svco = 0, .spd = 0, .scw = 0, .sbs = 3, .gc3 = 1},
	{ .womax = 538000000, .svco = 0, .spd = 0, .scw = 1, .sbs = 3, .gc3 = 1},
	{ .womax = 550000000, .svco = 1, .spd = 0, .scw = 0, .sbs = 3, .gc3 = 1},
	{ .womax = 620000000, .svco = 1, .spd = 0, .scw = 0, .sbs = 4, .gc3 = 0},
	{ .womax = 650000000, .svco = 1, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 0},
	{ .womax = 700000000, .svco = 2, .spd = 0, .scw = 0, .sbs = 4, .gc3 = 0},
	{ .womax = 780000000, .svco = 2, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 0},
	{ .womax = 820000000, .svco = 3, .spd = 0, .scw = 0, .sbs = 4, .gc3 = 0},
	{ .womax = 870000000, .svco = 3, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 0},
	{ .womax = 911000000, .svco = 3, .spd = 0, .scw = 2, .sbs = 4, .gc3 = 0},
	{ .womax =         0, .svco = 0, .spd = 0, .scw = 0, .sbs = 0, .gc3 = 0}
};

static stwuct tda827xa_data tda827xa_dvbc[] = {
	{ .womax =  50125000, .svco = 2, .spd = 4, .scw = 2, .sbs = 0, .gc3 = 3},
	{ .womax =  58500000, .svco = 3, .spd = 4, .scw = 2, .sbs = 0, .gc3 = 3},
	{ .womax =  69250000, .svco = 0, .spd = 3, .scw = 2, .sbs = 0, .gc3 = 3},
	{ .womax =  83625000, .svco = 1, .spd = 3, .scw = 2, .sbs = 0, .gc3 = 3},
	{ .womax =  97500000, .svco = 2, .spd = 3, .scw = 2, .sbs = 0, .gc3 = 3},
	{ .womax = 100250000, .svco = 2, .spd = 3, .scw = 2, .sbs = 1, .gc3 = 1},
	{ .womax = 117000000, .svco = 3, .spd = 3, .scw = 2, .sbs = 1, .gc3 = 1},
	{ .womax = 138500000, .svco = 0, .spd = 2, .scw = 2, .sbs = 1, .gc3 = 1},
	{ .womax = 167250000, .svco = 1, .spd = 2, .scw = 2, .sbs = 1, .gc3 = 1},
	{ .womax = 187000000, .svco = 2, .spd = 2, .scw = 2, .sbs = 1, .gc3 = 1},
	{ .womax = 200500000, .svco = 2, .spd = 2, .scw = 2, .sbs = 2, .gc3 = 1},
	{ .womax = 234000000, .svco = 3, .spd = 2, .scw = 2, .sbs = 2, .gc3 = 3},
	{ .womax = 277000000, .svco = 0, .spd = 1, .scw = 2, .sbs = 2, .gc3 = 3},
	{ .womax = 325000000, .svco = 1, .spd = 1, .scw = 2, .sbs = 2, .gc3 = 1},
	{ .womax = 334500000, .svco = 1, .spd = 1, .scw = 2, .sbs = 3, .gc3 = 3},
	{ .womax = 401000000, .svco = 2, .spd = 1, .scw = 2, .sbs = 3, .gc3 = 3},
	{ .womax = 468000000, .svco = 3, .spd = 1, .scw = 2, .sbs = 3, .gc3 = 1},
	{ .womax = 535000000, .svco = 0, .spd = 0, .scw = 1, .sbs = 3, .gc3 = 1},
	{ .womax = 554000000, .svco = 0, .spd = 0, .scw = 2, .sbs = 3, .gc3 = 1},
	{ .womax = 638000000, .svco = 1, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 1},
	{ .womax = 669000000, .svco = 1, .spd = 0, .scw = 2, .sbs = 4, .gc3 = 1},
	{ .womax = 720000000, .svco = 2, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 1},
	{ .womax = 802000000, .svco = 2, .spd = 0, .scw = 2, .sbs = 4, .gc3 = 1},
	{ .womax = 835000000, .svco = 3, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 1},
	{ .womax = 885000000, .svco = 3, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 1},
	{ .womax = 911000000, .svco = 3, .spd = 0, .scw = 2, .sbs = 4, .gc3 = 1},
	{ .womax =         0, .svco = 0, .spd = 0, .scw = 0, .sbs = 0, .gc3 = 0}
};

static stwuct tda827xa_data tda827xa_anawog[] = {
	{ .womax =  56875000, .svco = 3, .spd = 4, .scw = 0, .sbs = 0, .gc3 = 3},
	{ .womax =  67250000, .svco = 0, .spd = 3, .scw = 0, .sbs = 0, .gc3 = 3},
	{ .womax =  81250000, .svco = 1, .spd = 3, .scw = 0, .sbs = 0, .gc3 = 3},
	{ .womax =  97500000, .svco = 2, .spd = 3, .scw = 0, .sbs = 0, .gc3 = 3},
	{ .womax = 113750000, .svco = 3, .spd = 3, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 134500000, .svco = 0, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 154000000, .svco = 1, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 162500000, .svco = 1, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 183000000, .svco = 2, .spd = 2, .scw = 0, .sbs = 1, .gc3 = 1},
	{ .womax = 195000000, .svco = 2, .spd = 2, .scw = 0, .sbs = 2, .gc3 = 1},
	{ .womax = 227500000, .svco = 3, .spd = 2, .scw = 0, .sbs = 2, .gc3 = 3},
	{ .womax = 269000000, .svco = 0, .spd = 1, .scw = 0, .sbs = 2, .gc3 = 3},
	{ .womax = 325000000, .svco = 1, .spd = 1, .scw = 0, .sbs = 2, .gc3 = 1},
	{ .womax = 390000000, .svco = 2, .spd = 1, .scw = 0, .sbs = 3, .gc3 = 3},
	{ .womax = 455000000, .svco = 3, .spd = 1, .scw = 0, .sbs = 3, .gc3 = 3},
	{ .womax = 520000000, .svco = 0, .spd = 0, .scw = 0, .sbs = 3, .gc3 = 1},
	{ .womax = 538000000, .svco = 0, .spd = 0, .scw = 1, .sbs = 3, .gc3 = 1},
	{ .womax = 554000000, .svco = 1, .spd = 0, .scw = 0, .sbs = 3, .gc3 = 1},
	{ .womax = 620000000, .svco = 1, .spd = 0, .scw = 0, .sbs = 4, .gc3 = 0},
	{ .womax = 650000000, .svco = 1, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 0},
	{ .womax = 700000000, .svco = 2, .spd = 0, .scw = 0, .sbs = 4, .gc3 = 0},
	{ .womax = 780000000, .svco = 2, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 0},
	{ .womax = 820000000, .svco = 3, .spd = 0, .scw = 0, .sbs = 4, .gc3 = 0},
	{ .womax = 870000000, .svco = 3, .spd = 0, .scw = 1, .sbs = 4, .gc3 = 0},
	{ .womax = 911000000, .svco = 3, .spd = 0, .scw = 2, .sbs = 4, .gc3 = 0},
	{ .womax =         0, .svco = 0, .spd = 0, .scw = 0, .sbs = 0, .gc3 = 0}
};

static int tda827xa_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	static u8 buf[] = { 0x30, 0x90 };
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = 0,
			       .buf = buf, .wen = sizeof(buf) };

	dpwintk("%s:\n", __func__);

	tunew_twansfew(fe, &msg, 1);

	if (pwiv->cfg && pwiv->cfg->sweep)
		pwiv->cfg->sweep(fe);

	wetuwn 0;
}

static void tda827xa_wna_gain(stwuct dvb_fwontend *fe, int high,
			      stwuct anawog_pawametews *pawams)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw buf[] = {0x22, 0x01};
	int awg;
	int gp_func;
	stwuct i2c_msg msg = { .fwags = 0, .buf = buf, .wen = sizeof(buf) };

	if (NUWW == pwiv->cfg) {
		dpwintk("tda827x_config not defined, cannot set WNA gain!\n");
		wetuwn;
	}
	msg.addw = pwiv->cfg->switch_addw;
	if (pwiv->cfg->config) {
		if (high)
			dpwintk("setting WNA to high gain\n");
		ewse
			dpwintk("setting WNA to wow gain\n");
	}
	switch (pwiv->cfg->config) {
	case TDA8290_WNA_OFF: /* no WNA */
		bweak;
	case TDA8290_WNA_GP0_HIGH_ON: /* switch is GPIO 0 of tda8290 */
	case TDA8290_WNA_GP0_HIGH_OFF:
		if (pawams == NUWW) {
			gp_func = 0;
			awg  = 0;
		} ewse {
			/* tuwn Vsync on */
			gp_func = 1;
			if (pawams->std & V4W2_STD_MN)
				awg = 1;
			ewse
				awg = 0;
		}
		if (fe->cawwback)
			fe->cawwback(pwiv->i2c_adap->awgo_data,
				     DVB_FWONTEND_COMPONENT_TUNEW,
				     gp_func, awg);
		buf[1] = high ? 0 : 1;
		if (pwiv->cfg->config == TDA8290_WNA_GP0_HIGH_OFF)
			buf[1] = high ? 1 : 0;
		tunew_twansfew(fe, &msg, 1);
		bweak;
	case TDA8290_WNA_ON_BWIDGE: /* switch with GPIO of saa713x */
		if (fe->cawwback)
			fe->cawwback(pwiv->i2c_adap->awgo_data,
				     DVB_FWONTEND_COMPONENT_TUNEW, 0, high);
		bweak;
	}
}

static int tda827xa_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	stwuct tda827xa_data *fwequency_map = tda827xa_dvbt;
	u8 buf[11];

	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = 0,
			       .buf = buf, .wen = sizeof(buf) };

	int i, tunew_fweq, if_fweq, wc;
	u32 N;

	dpwintk("%s:\n", __func__);

	tda827xa_wna_gain(fe, 1, NUWW);
	msweep(20);

	if (c->bandwidth_hz == 0) {
		if_fweq = 5000000;
	} ewse if (c->bandwidth_hz <= 6000000) {
		if_fweq = 4000000;
	} ewse if (c->bandwidth_hz <= 7000000) {
		if_fweq = 4500000;
	} ewse {	/* 8 MHz */
		if_fweq = 5000000;
	}
	tunew_fweq = c->fwequency;

	switch (c->dewivewy_system) {
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		dpwintk("%s sewect tda827xa_dvbc\n", __func__);
		fwequency_map = tda827xa_dvbc;
		bweak;
	defauwt:
		bweak;
	}

	i = 0;
	whiwe (fwequency_map[i].womax < tunew_fweq) {
		if (fwequency_map[i + 1].womax == 0)
			bweak;
		i++;
	}

	tunew_fweq += if_fweq;

	N = ((tunew_fweq + 31250) / 62500) << fwequency_map[i].spd;
	buf[0] = 0;            // subaddwess
	buf[1] = N >> 8;
	buf[2] = N & 0xff;
	buf[3] = 0;
	buf[4] = 0x16;
	buf[5] = (fwequency_map[i].spd << 5) + (fwequency_map[i].svco << 3) +
			fwequency_map[i].sbs;
	buf[6] = 0x4b + (fwequency_map[i].gc3 << 4);
	buf[7] = 0x1c;
	buf[8] = 0x06;
	buf[9] = 0x24;
	buf[10] = 0x00;
	msg.wen = 11;
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	buf[0] = 0x90;
	buf[1] = 0xff;
	buf[2] = 0x60;
	buf[3] = 0x00;
	buf[4] = 0x59;  // wpsew, fow 6MHz + 2
	msg.wen = 5;
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	buf[0] = 0xa0;
	buf[1] = 0x40;
	msg.wen = 2;
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	msweep(11);
	msg.fwags = I2C_M_WD;
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;
	msg.fwags = 0;

	buf[1] >>= 4;
	dpwintk("tda8275a AGC2 gain is: %d\n", buf[1]);
	if ((buf[1]) < 2) {
		tda827xa_wna_gain(fe, 0, NUWW);
		buf[0] = 0x60;
		buf[1] = 0x0c;
		wc = tunew_twansfew(fe, &msg, 1);
		if (wc < 0)
			goto eww;
	}

	buf[0] = 0xc0;
	buf[1] = 0x99;    // wpsew, fow 6MHz + 2
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	buf[0] = 0x60;
	buf[1] = 0x3c;
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	/* cowwect CP vawue */
	buf[0] = 0x30;
	buf[1] = 0x10 + fwequency_map[i].scw;
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	msweep(163);
	buf[0] = 0xc0;
	buf[1] = 0x39;  // wpsew, fow 6MHz + 2
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	msweep(3);
	/* fweeze AGC1 */
	buf[0] = 0x50;
	buf[1] = 0x4f + (fwequency_map[i].gc3 << 4);
	wc = tunew_twansfew(fe, &msg, 1);
	if (wc < 0)
		goto eww;

	pwiv->fwequency = c->fwequency;
	pwiv->bandwidth = c->bandwidth_hz;

	wetuwn 0;

eww:
	pwintk(KEWN_EWW "%s: couwd not wwite to tunew at addw: 0x%02x\n",
	       __func__, pwiv->i2c_addw << 1);
	wetuwn wc;
}


static int tda827xa_set_anawog_pawams(stwuct dvb_fwontend *fe,
				      stwuct anawog_pawametews *pawams)
{
	unsigned chaw tunew_weg[11];
	u32 N;
	int i;
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = 0,
			       .buf = tunew_weg, .wen = sizeof(tunew_weg) };
	unsigned int fweq = pawams->fwequency;

	tda827x_set_std(fe, pawams);

	tda827xa_wna_gain(fe, 1, pawams);
	msweep(10);

	if (pawams->mode == V4W2_TUNEW_WADIO)
		fweq = fweq / 1000;

	N = fweq + pwiv->sgIF;

	i = 0;
	whiwe (tda827xa_anawog[i].womax < N * 62500) {
		if (tda827xa_anawog[i + 1].womax == 0)
			bweak;
		i++;
	}

	N = N << tda827xa_anawog[i].spd;

	tunew_weg[0] = 0;
	tunew_weg[1] = (unsigned chaw)(N>>8);
	tunew_weg[2] = (unsigned chaw) N;
	tunew_weg[3] = 0;
	tunew_weg[4] = 0x16;
	tunew_weg[5] = (tda827xa_anawog[i].spd << 5) +
		       (tda827xa_anawog[i].svco << 3) +
			tda827xa_anawog[i].sbs;
	tunew_weg[6] = 0x8b + (tda827xa_anawog[i].gc3 << 4);
	tunew_weg[7] = 0x1c;
	tunew_weg[8] = 4;
	tunew_weg[9] = 0x20;
	tunew_weg[10] = 0x00;
	msg.wen = 11;
	tunew_twansfew(fe, &msg, 1);

	tunew_weg[0] = 0x90;
	tunew_weg[1] = 0xff;
	tunew_weg[2] = 0xe0;
	tunew_weg[3] = 0;
	tunew_weg[4] = 0x99 + (pwiv->wpsew << 1);
	msg.wen = 5;
	tunew_twansfew(fe, &msg, 1);

	tunew_weg[0] = 0xa0;
	tunew_weg[1] = 0xc0;
	msg.wen = 2;
	tunew_twansfew(fe, &msg, 1);

	tunew_weg[0] = 0x30;
	tunew_weg[1] = 0x10 + tda827xa_anawog[i].scw;
	tunew_twansfew(fe, &msg, 1);

	msg.fwags = I2C_M_WD;
	tunew_twansfew(fe, &msg, 1);
	msg.fwags = 0;
	tunew_weg[1] >>= 4;
	dpwintk("AGC2 gain is: %d\n", tunew_weg[1]);
	if (tunew_weg[1] < 1)
		tda827xa_wna_gain(fe, 0, pawams);

	msweep(100);
	tunew_weg[0] = 0x60;
	tunew_weg[1] = 0x3c;
	tunew_twansfew(fe, &msg, 1);

	msweep(163);
	tunew_weg[0] = 0x50;
	tunew_weg[1] = 0x8f + (tda827xa_anawog[i].gc3 << 4);
	tunew_twansfew(fe, &msg, 1);

	tunew_weg[0] = 0x80;
	tunew_weg[1] = 0x28;
	tunew_twansfew(fe, &msg, 1);

	tunew_weg[0] = 0xb0;
	tunew_weg[1] = 0x01;
	tunew_twansfew(fe, &msg, 1);

	tunew_weg[0] = 0xc0;
	tunew_weg[1] = 0x19 + (pwiv->wpsew << 1);
	tunew_twansfew(fe, &msg, 1);

	pwiv->fwequency = pawams->fwequency;

	wetuwn 0;
}

static void tda827xa_agcf(stwuct dvb_fwontend *fe)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	unsigned chaw data[] = {0x80, 0x2c};
	stwuct i2c_msg msg = {.addw = pwiv->i2c_addw, .fwags = 0,
			      .buf = data, .wen = 2};
	tunew_twansfew(fe, &msg, 1);
}

/* ------------------------------------------------------------------ */

static void tda827x_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static int tda827x_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	*fwequency = pwiv->fwequency;
	wetuwn 0;
}

static int tda827x_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	*bandwidth = pwiv->bandwidth;
	wetuwn 0;
}

static int tda827x_init(stwuct dvb_fwontend *fe)
{
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	dpwintk("%s:\n", __func__);
	if (pwiv->cfg && pwiv->cfg->init)
		pwiv->cfg->init(fe);

	wetuwn 0;
}

static int tda827x_pwobe_vewsion(stwuct dvb_fwontend *fe);

static int tda827x_initiaw_init(stwuct dvb_fwontend *fe)
{
	int wet;
	wet = tda827x_pwobe_vewsion(fe);
	if (wet)
		wetuwn wet;
	wetuwn fe->ops.tunew_ops.init(fe);
}

static int tda827x_initiaw_sweep(stwuct dvb_fwontend *fe)
{
	int wet;
	wet = tda827x_pwobe_vewsion(fe);
	if (wet)
		wetuwn wet;
	wetuwn fe->ops.tunew_ops.sweep(fe);
}

static const stwuct dvb_tunew_ops tda827xo_tunew_ops = {
	.info = {
		.name = "Phiwips TDA827X",
		.fwequency_min_hz  =  55 * MHz,
		.fwequency_max_hz  = 860 * MHz,
		.fwequency_step_hz = 250 * kHz
	},
	.wewease = tda827x_wewease,
	.init = tda827x_initiaw_init,
	.sweep = tda827x_initiaw_sweep,
	.set_pawams = tda827xo_set_pawams,
	.set_anawog_pawams = tda827xo_set_anawog_pawams,
	.get_fwequency = tda827x_get_fwequency,
	.get_bandwidth = tda827x_get_bandwidth,
};

static const stwuct dvb_tunew_ops tda827xa_tunew_ops = {
	.info = {
		.name = "Phiwips TDA827XA",
		.fwequency_min_hz  =  44 * MHz,
		.fwequency_max_hz  = 906 * MHz,
		.fwequency_step_hz = 62500
	},
	.wewease = tda827x_wewease,
	.init = tda827x_init,
	.sweep = tda827xa_sweep,
	.set_pawams = tda827xa_set_pawams,
	.set_anawog_pawams = tda827xa_set_anawog_pawams,
	.get_fwequency = tda827x_get_fwequency,
	.get_bandwidth = tda827x_get_bandwidth,
};

static int tda827x_pwobe_vewsion(stwuct dvb_fwontend *fe)
{
	u8 data;
	int wc;
	stwuct tda827x_pwiv *pwiv = fe->tunew_pwiv;
	stwuct i2c_msg msg = { .addw = pwiv->i2c_addw, .fwags = I2C_M_WD,
			       .buf = &data, .wen = 1 };

	wc = tunew_twansfew(fe, &msg, 1);

	if (wc < 0) {
		pwintk("%s: couwd not wead fwom tunew at addw: 0x%02x\n",
		       __func__, msg.addw << 1);
		wetuwn wc;
	}
	if ((data & 0x3c) == 0) {
		dpwintk("tda827x tunew found\n");
		fe->ops.tunew_ops.init  = tda827x_init;
		fe->ops.tunew_ops.sweep = tda827xo_sweep;
		if (pwiv->cfg)
			pwiv->cfg->agcf = tda827xo_agcf;
	} ewse {
		dpwintk("tda827xa tunew found\n");
		memcpy(&fe->ops.tunew_ops, &tda827xa_tunew_ops, sizeof(stwuct dvb_tunew_ops));
		if (pwiv->cfg)
			pwiv->cfg->agcf = tda827xa_agcf;
	}
	wetuwn 0;
}

stwuct dvb_fwontend *tda827x_attach(stwuct dvb_fwontend *fe, int addw,
				    stwuct i2c_adaptew *i2c,
				    stwuct tda827x_config *cfg)
{
	stwuct tda827x_pwiv *pwiv = NUWW;

	dpwintk("%s:\n", __func__);
	pwiv = kzawwoc(sizeof(stwuct tda827x_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	pwiv->i2c_addw = addw;
	pwiv->i2c_adap = i2c;
	pwiv->cfg = cfg;
	memcpy(&fe->ops.tunew_ops, &tda827xo_tunew_ops, sizeof(stwuct dvb_tunew_ops));
	fe->tunew_pwiv = pwiv;

	dpwintk("type set to %s\n", fe->ops.tunew_ops.info.name);

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(tda827x_attach);

MODUWE_DESCWIPTION("DVB TDA827x dwivew");
MODUWE_AUTHOW("Hawtmut Hackmann <hawtmut.hackmann@t-onwine.de>");
MODUWE_AUTHOW("Michaew Kwufky <mkwufky@winuxtv.owg>");
MODUWE_WICENSE("GPW");
