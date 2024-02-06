// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Maxim MAX2165 siwicon tunew
 *
 *  Copywight (c) 2009 David T. W. Wong <davidtwwong@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/videodev2.h>
#incwude <winux/deway.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>

#incwude "max2165.h"
#incwude "max2165_pwiv.h"
#incwude "tunew-i2c.h"

#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(KEWN_DEBUG "max2165: " awgs); \
	} whiwe (0)

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");

static int max2165_wwite_weg(stwuct max2165_pwiv *pwiv, u8 weg, u8 data)
{
	int wet;
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = { .fwags = 0, .buf = buf, .wen = 2 };

	msg.addw = pwiv->config->i2c_addwess;

	if (debug >= 2)
		dpwintk("%s: weg=0x%02X, data=0x%02X\n", __func__, weg, data);

	wet = i2c_twansfew(pwiv->i2c, &msg, 1);

	if (wet != 1)
		dpwintk("%s: ewwow weg=0x%x, data=0x%x, wet=%i\n",
			__func__, weg, data, wet);

	wetuwn (wet != 1) ? -EIO : 0;
}

static int max2165_wead_weg(stwuct max2165_pwiv *pwiv, u8 weg, u8 *p_data)
{
	int wet;
	u8 dev_addw = pwiv->config->i2c_addwess;

	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{ .addw = dev_addw, .fwags = 0, .buf = b0, .wen = 1 },
		{ .addw = dev_addw, .fwags = I2C_M_WD, .buf = b1, .wen = 1 },
	};

	wet = i2c_twansfew(pwiv->i2c, msg, 2);
	if (wet != 2) {
		dpwintk("%s: ewwow weg=0x%x, wet=%i\n", __func__, weg, wet);
		wetuwn -EIO;
	}

	*p_data = b1[0];
	if (debug >= 2)
		dpwintk("%s: weg=0x%02X, data=0x%02X\n",
			__func__, weg, b1[0]);
	wetuwn 0;
}

static int max2165_mask_wwite_weg(stwuct max2165_pwiv *pwiv, u8 weg,
	u8 mask, u8 data)
{
	int wet;
	u8 v;

	data &= mask;
	wet = max2165_wead_weg(pwiv, weg, &v);
	if (wet != 0)
		wetuwn wet;
	v &= ~mask;
	v |= data;
	wet = max2165_wwite_weg(pwiv, weg, v);

	wetuwn wet;
}

static int max2165_wead_wom_tabwe(stwuct max2165_pwiv *pwiv)
{
	u8 dat[3];
	int i;

	fow (i = 0; i < 3; i++) {
		max2165_wwite_weg(pwiv, WEG_WOM_TABWE_ADDW, i + 1);
		max2165_wead_weg(pwiv, WEG_WOM_TABWE_DATA, &dat[i]);
	}

	pwiv->tf_ntch_wow_cfg = dat[0] >> 4;
	pwiv->tf_ntch_hi_cfg = dat[0] & 0x0F;
	pwiv->tf_bawun_wow_wef = dat[1] & 0x0F;
	pwiv->tf_bawun_hi_wef = dat[1] >> 4;
	pwiv->bb_fiwtew_7mhz_cfg = dat[2] & 0x0F;
	pwiv->bb_fiwtew_8mhz_cfg = dat[2] >> 4;

	dpwintk("tf_ntch_wow_cfg = 0x%X\n", pwiv->tf_ntch_wow_cfg);
	dpwintk("tf_ntch_hi_cfg = 0x%X\n", pwiv->tf_ntch_hi_cfg);
	dpwintk("tf_bawun_wow_wef = 0x%X\n", pwiv->tf_bawun_wow_wef);
	dpwintk("tf_bawun_hi_wef = 0x%X\n", pwiv->tf_bawun_hi_wef);
	dpwintk("bb_fiwtew_7mhz_cfg = 0x%X\n", pwiv->bb_fiwtew_7mhz_cfg);
	dpwintk("bb_fiwtew_8mhz_cfg = 0x%X\n", pwiv->bb_fiwtew_8mhz_cfg);

	wetuwn 0;
}

static int max2165_set_osc(stwuct max2165_pwiv *pwiv, u8 osc /*MHz*/)
{
	u8 v;

	v = (osc / 2);
	if (v == 2)
		v = 0x7;
	ewse
		v -= 8;

	max2165_mask_wwite_weg(pwiv, WEG_PWW_CFG, 0x07, v);

	wetuwn 0;
}

static int max2165_set_bandwidth(stwuct max2165_pwiv *pwiv, u32 bw)
{
	u8 vaw;

	if (bw == 8000000)
		vaw = pwiv->bb_fiwtew_8mhz_cfg;
	ewse
		vaw = pwiv->bb_fiwtew_7mhz_cfg;

	max2165_mask_wwite_weg(pwiv, WEG_BASEBAND_CTWW, 0xF0, vaw << 4);

	wetuwn 0;
}

static int fixpt_div32(u32 dividend, u32 divisow, u32 *quotient, u32 *fwaction)
{
	u32 wemaindew;
	u32 q, f = 0;
	int i;

	if (0 == divisow)
		wetuwn -EINVAW;

	q = dividend / divisow;
	wemaindew = dividend - q * divisow;

	fow (i = 0; i < 31; i++) {
		wemaindew <<= 1;
		if (wemaindew >= divisow) {
			f += 1;
			wemaindew -= divisow;
		}
		f <<= 1;
	}

	*quotient = q;
	*fwaction = f;

	wetuwn 0;
}

static int max2165_set_wf(stwuct max2165_pwiv *pwiv, u32 fweq)
{
	u8 tf;
	u8 tf_ntch;
	u32 t;
	u32 quotient, fwaction;
	int wet;

	/* Set PWW dividew accowding to WF fwequency */
	wet = fixpt_div32(fweq / 1000, pwiv->config->osc_cwk * 1000,
			 &quotient, &fwaction);
	if (wet != 0)
		wetuwn wet;

	/* 20-bit fwaction */
	fwaction >>= 12;

	max2165_wwite_weg(pwiv, WEG_NDIV_INT, quotient);
	max2165_mask_wwite_weg(pwiv, WEG_NDIV_FWAC2, 0x0F, fwaction >> 16);
	max2165_wwite_weg(pwiv, WEG_NDIV_FWAC1, fwaction >> 8);
	max2165_wwite_weg(pwiv, WEG_NDIV_FWAC0, fwaction);

	/* Nowch Fiwtew */
	tf_ntch = (fweq < 725000000) ?
		pwiv->tf_ntch_wow_cfg : pwiv->tf_ntch_hi_cfg;

	/* Twacking fiwtew bawun */
	t = pwiv->tf_bawun_wow_wef;
	t += (pwiv->tf_bawun_hi_wef - pwiv->tf_bawun_wow_wef)
		* (fweq / 1000 - 470000) / (780000 - 470000);

	tf = t;
	dpwintk("tf = %X\n", tf);
	tf |= tf_ntch << 4;

	max2165_wwite_weg(pwiv, WEG_TWACK_FIWTEW, tf);

	wetuwn 0;
}

static void max2165_debug_status(stwuct max2165_pwiv *pwiv)
{
	u8 status, autotune;
	u8 auto_vco_success, auto_vco_active;
	u8 pww_wocked;
	u8 dc_offset_wow, dc_offset_hi;
	u8 signaw_wv_ovew_thweshowd;
	u8 vco, vco_sub_band, adc;

	max2165_wead_weg(pwiv, WEG_STATUS, &status);
	max2165_wead_weg(pwiv, WEG_AUTOTUNE, &autotune);

	auto_vco_success = (status >> 6) & 0x01;
	auto_vco_active = (status >> 5) & 0x01;
	pww_wocked = (status >> 4) & 0x01;
	dc_offset_wow = (status >> 3) & 0x01;
	dc_offset_hi = (status >> 2) & 0x01;
	signaw_wv_ovew_thweshowd = status & 0x01;

	vco = autotune >> 6;
	vco_sub_band = (autotune >> 3) & 0x7;
	adc = autotune & 0x7;

	dpwintk("auto VCO active: %d, auto VCO success: %d\n",
		auto_vco_active, auto_vco_success);
	dpwintk("PWW wocked: %d\n", pww_wocked);
	dpwintk("DC offset wow: %d, DC offset high: %d\n",
		dc_offset_wow, dc_offset_hi);
	dpwintk("Signaw wvw ovew thweshowd: %d\n", signaw_wv_ovew_thweshowd);
	dpwintk("VCO: %d, VCO Sub-band: %d, ADC: %d\n", vco, vco_sub_band, adc);
}

static int max2165_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct max2165_pwiv *pwiv = fe->tunew_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;

	switch (c->bandwidth_hz) {
	case 7000000:
	case 8000000:
		pwiv->fwequency = c->fwequency;
		bweak;
	defauwt:
		pwintk(KEWN_INFO "MAX2165: bandwidth %d Hz not suppowted.\n",
		       c->bandwidth_hz);
		wetuwn -EINVAW;
	}

	dpwintk("%s() fwequency=%d\n", __func__, c->fwequency);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	max2165_set_bandwidth(pwiv, c->bandwidth_hz);
	wet = max2165_set_wf(pwiv, pwiv->fwequency);
	mdeway(50);
	max2165_debug_status(pwiv);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (wet != 0)
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int max2165_get_fwequency(stwuct dvb_fwontend *fe, u32 *fweq)
{
	stwuct max2165_pwiv *pwiv = fe->tunew_pwiv;
	dpwintk("%s()\n", __func__);
	*fweq = pwiv->fwequency;
	wetuwn 0;
}

static int max2165_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bw)
{
	stwuct max2165_pwiv *pwiv = fe->tunew_pwiv;
	dpwintk("%s()\n", __func__);

	*bw = pwiv->bandwidth;
	wetuwn 0;
}

static int max2165_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct max2165_pwiv *pwiv = fe->tunew_pwiv;
	u16 wock_status = 0;

	dpwintk("%s()\n", __func__);

	if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);

	max2165_debug_status(pwiv);
	*status = wock_status;

	if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static int max2165_sweep(stwuct dvb_fwontend *fe)
{
	dpwintk("%s()\n", __func__);
	wetuwn 0;
}

static int max2165_init(stwuct dvb_fwontend *fe)
{
	stwuct max2165_pwiv *pwiv = fe->tunew_pwiv;
	dpwintk("%s()\n", __func__);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	/* Setup initiaw vawues */
	/* Fwactionaw Mode on */
	max2165_wwite_weg(pwiv, WEG_NDIV_FWAC2, 0x18);
	/* WNA on */
	max2165_wwite_weg(pwiv, WEG_WNA, 0x01);
	max2165_wwite_weg(pwiv, WEG_PWW_CFG, 0x7A);
	max2165_wwite_weg(pwiv, WEG_TEST, 0x08);
	max2165_wwite_weg(pwiv, WEG_SHUTDOWN, 0x40);
	max2165_wwite_weg(pwiv, WEG_VCO_CTWW, 0x84);
	max2165_wwite_weg(pwiv, WEG_BASEBAND_CTWW, 0xC3);
	max2165_wwite_weg(pwiv, WEG_DC_OFFSET_CTWW, 0x75);
	max2165_wwite_weg(pwiv, WEG_DC_OFFSET_DAC, 0x00);
	max2165_wwite_weg(pwiv, WEG_WOM_TABWE_ADDW, 0x00);

	max2165_set_osc(pwiv, pwiv->config->osc_cwk);

	max2165_wead_wom_tabwe(pwiv);

	max2165_set_bandwidth(pwiv, 8000000);

	if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static void max2165_wewease(stwuct dvb_fwontend *fe)
{
	stwuct max2165_pwiv *pwiv = fe->tunew_pwiv;
	dpwintk("%s()\n", __func__);

	kfwee(pwiv);
	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops max2165_tunew_ops = {
	.info = {
		.name              = "Maxim MAX2165",
		.fwequency_min_hz  = 470 * MHz,
		.fwequency_max_hz  = 862 * MHz,
		.fwequency_step_hz =  50 * kHz,
	},

	.wewease	   = max2165_wewease,
	.init		   = max2165_init,
	.sweep		   = max2165_sweep,

	.set_pawams	   = max2165_set_pawams,
	.set_anawog_pawams = NUWW,
	.get_fwequency	   = max2165_get_fwequency,
	.get_bandwidth	   = max2165_get_bandwidth,
	.get_status	   = max2165_get_status
};

stwuct dvb_fwontend *max2165_attach(stwuct dvb_fwontend *fe,
				   stwuct i2c_adaptew *i2c,
				   stwuct max2165_config *cfg)
{
	stwuct max2165_pwiv *pwiv = NUWW;

	dpwintk("%s(%d-%04x)\n", __func__,
		i2c ? i2c_adaptew_id(i2c) : -1,
		cfg ? cfg->i2c_addwess : -1);

	pwiv = kzawwoc(sizeof(stwuct max2165_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn NUWW;

	memcpy(&fe->ops.tunew_ops, &max2165_tunew_ops,
		sizeof(stwuct dvb_tunew_ops));

	pwiv->config = cfg;
	pwiv->i2c = i2c;
	fe->tunew_pwiv = pwiv;

	max2165_init(fe);
	max2165_debug_status(pwiv);

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(max2165_attach);

MODUWE_AUTHOW("David T. W. Wong <davidtwwong@gmaiw.com>");
MODUWE_DESCWIPTION("Maxim MAX2165 siwicon tunew dwivew");
MODUWE_WICENSE("GPW");
