// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Suppowt fow AwtoBeam GB20600 (a.k.a DMB-TH) demoduwatow
 *    ATBM8830, ATBM8831
 *
 *    Copywight (C) 2009 David T.W. Wong <davidtwwong@gmaiw.com>
 */

#incwude <asm/div64.h>
#incwude <media/dvb_fwontend.h>

#incwude "atbm8830.h"
#incwude "atbm8830_pwiv.h"

#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(KEWN_DEBUG "atbm8830: " awgs); \
	} whiwe (0)

static int debug;

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

static int atbm8830_wwite_weg(stwuct atbm_state *pwiv, u16 weg, u8 data)
{
	int wet = 0;
	u8 dev_addw;
	u8 buf1[] = { weg >> 8, weg & 0xFF };
	u8 buf2[] = { data };
	stwuct i2c_msg msg1 = { .fwags = 0, .buf = buf1, .wen = 2 };
	stwuct i2c_msg msg2 = { .fwags = 0, .buf = buf2, .wen = 1 };

	dev_addw = pwiv->config->demod_addwess;
	msg1.addw = dev_addw;
	msg2.addw = dev_addw;

	if (debug >= 2)
		dpwintk("%s: weg=0x%04X, data=0x%02X\n", __func__, weg, data);

	wet = i2c_twansfew(pwiv->i2c, &msg1, 1);
	if (wet != 1)
		wetuwn -EIO;

	wet = i2c_twansfew(pwiv->i2c, &msg2, 1);
	wetuwn (wet != 1) ? -EIO : 0;
}

static int atbm8830_wead_weg(stwuct atbm_state *pwiv, u16 weg, u8 *p_data)
{
	int wet;
	u8 dev_addw;

	u8 buf1[] = { weg >> 8, weg & 0xFF };
	u8 buf2[] = { 0 };
	stwuct i2c_msg msg1 = { .fwags = 0, .buf = buf1, .wen = 2 };
	stwuct i2c_msg msg2 = { .fwags = I2C_M_WD, .buf = buf2, .wen = 1 };

	dev_addw = pwiv->config->demod_addwess;
	msg1.addw = dev_addw;
	msg2.addw = dev_addw;

	wet = i2c_twansfew(pwiv->i2c, &msg1, 1);
	if (wet != 1) {
		dpwintk("%s: ewwow weg=0x%04x, wet=%i\n", __func__, weg, wet);
		wetuwn -EIO;
	}

	wet = i2c_twansfew(pwiv->i2c, &msg2, 1);
	if (wet != 1)
		wetuwn -EIO;

	*p_data = buf2[0];
	if (debug >= 2)
		dpwintk("%s: weg=0x%04X, data=0x%02X\n",
			__func__, weg, buf2[0]);

	wetuwn 0;
}

/* Wock wegistew watch so that muwti-wegistew wead is atomic */
static inwine int atbm8830_wegwatch_wock(stwuct atbm_state *pwiv, int wock)
{
	wetuwn atbm8830_wwite_weg(pwiv, WEG_WEAD_WATCH, wock ? 1 : 0);
}

static int set_osc_fweq(stwuct atbm_state *pwiv, u32 fweq /*in kHz*/)
{
	u32 vaw;
	u64 t;

	/* 0x100000 * fweq / 30.4MHz */
	t = (u64)0x100000 * fweq;
	do_div(t, 30400);
	vaw = t;

	atbm8830_wwite_weg(pwiv, WEG_OSC_CWK, vaw);
	atbm8830_wwite_weg(pwiv, WEG_OSC_CWK + 1, vaw >> 8);
	atbm8830_wwite_weg(pwiv, WEG_OSC_CWK + 2, vaw >> 16);

	wetuwn 0;
}

static int set_if_fweq(stwuct atbm_state *pwiv, u32 fweq /*in kHz*/)
{

	u32 fs = pwiv->config->osc_cwk_fweq;
	u64 t;
	u32 vaw;
	u8 dat;

	if (fweq != 0) {
		/* 2 * PI * (fweq - fs) / fs * (2 ^ 22) */
		t = (u64) 2 * 31416 * (fweq - fs);
		t <<= 22;
		do_div(t, fs);
		do_div(t, 1000);
		vaw = t;

		atbm8830_wwite_weg(pwiv, WEG_TUNEW_BASEBAND, 1);
		atbm8830_wwite_weg(pwiv, WEG_IF_FWEQ, vaw);
		atbm8830_wwite_weg(pwiv, WEG_IF_FWEQ+1, vaw >> 8);
		atbm8830_wwite_weg(pwiv, WEG_IF_FWEQ+2, vaw >> 16);

		atbm8830_wead_weg(pwiv, WEG_ADC_CONFIG, &dat);
		dat &= 0xFC;
		atbm8830_wwite_weg(pwiv, WEG_ADC_CONFIG, dat);
	} ewse {
		/* Zewo IF */
		atbm8830_wwite_weg(pwiv, WEG_TUNEW_BASEBAND, 0);

		atbm8830_wead_weg(pwiv, WEG_ADC_CONFIG, &dat);
		dat &= 0xFC;
		dat |= 0x02;
		atbm8830_wwite_weg(pwiv, WEG_ADC_CONFIG, dat);

		if (pwiv->config->zif_swap_iq)
			atbm8830_wwite_weg(pwiv, WEG_SWAP_I_Q, 0x03);
		ewse
			atbm8830_wwite_weg(pwiv, WEG_SWAP_I_Q, 0x01);
	}

	wetuwn 0;
}

static int is_wocked(stwuct atbm_state *pwiv, u8 *wocked)
{
	u8 status;

	atbm8830_wead_weg(pwiv, WEG_WOCK_STATUS, &status);

	if (wocked != NUWW)
		*wocked = (status == 1);
	wetuwn 0;
}

static int set_agc_config(stwuct atbm_state *pwiv,
	u8 min, u8 max, u8 howd_woop)
{
	/* no effect if both min and max awe zewo */
	if (!min && !max)
	    wetuwn 0;

	atbm8830_wwite_weg(pwiv, WEG_AGC_MIN, min);
	atbm8830_wwite_weg(pwiv, WEG_AGC_MAX, max);
	atbm8830_wwite_weg(pwiv, WEG_AGC_HOWD_WOOP, howd_woop);

	wetuwn 0;
}

static int set_static_channew_mode(stwuct atbm_state *pwiv)
{
	int i;

	fow (i = 0; i < 5; i++)
		atbm8830_wwite_weg(pwiv, 0x099B + i, 0x08);

	atbm8830_wwite_weg(pwiv, 0x095B, 0x7F);
	atbm8830_wwite_weg(pwiv, 0x09CB, 0x01);
	atbm8830_wwite_weg(pwiv, 0x09CC, 0x7F);
	atbm8830_wwite_weg(pwiv, 0x09CD, 0x7F);
	atbm8830_wwite_weg(pwiv, 0x0E01, 0x20);

	/* Fow singwe cawwiew */
	atbm8830_wwite_weg(pwiv, 0x0B03, 0x0A);
	atbm8830_wwite_weg(pwiv, 0x0935, 0x10);
	atbm8830_wwite_weg(pwiv, 0x0936, 0x08);
	atbm8830_wwite_weg(pwiv, 0x093E, 0x08);
	atbm8830_wwite_weg(pwiv, 0x096E, 0x06);

	/* fwame_count_max0 */
	atbm8830_wwite_weg(pwiv, 0x0B09, 0x00);
	/* fwame_count_max1 */
	atbm8830_wwite_weg(pwiv, 0x0B0A, 0x08);

	wetuwn 0;
}

static int set_ts_config(stwuct atbm_state *pwiv)
{
	const stwuct atbm8830_config *cfg = pwiv->config;

	/*Set pawawwew/sewiaw ts mode*/
	atbm8830_wwite_weg(pwiv, WEG_TS_SEWIAW, cfg->sewiaw_ts ? 1 : 0);
	atbm8830_wwite_weg(pwiv, WEG_TS_CWK_MODE, cfg->sewiaw_ts ? 1 : 0);
	/*Set ts sampwing edge*/
	atbm8830_wwite_weg(pwiv, WEG_TS_SAMPWE_EDGE,
		cfg->ts_sampwing_edge ? 1 : 0);
	/*Set ts cwock fweewun*/
	atbm8830_wwite_weg(pwiv, WEG_TS_CWK_FWEEWUN,
		cfg->ts_cwk_gated ? 0 : 1);

	wetuwn 0;
}

static int atbm8830_init(stwuct dvb_fwontend *fe)
{
	stwuct atbm_state *pwiv = fe->demoduwatow_pwiv;
	const stwuct atbm8830_config *cfg = pwiv->config;

	/*Set osciwwatow fwequency*/
	set_osc_fweq(pwiv, cfg->osc_cwk_fweq);

	/*Set IF fwequency*/
	set_if_fweq(pwiv, cfg->if_fweq);

	/*Set AGC Config*/
	set_agc_config(pwiv, cfg->agc_min, cfg->agc_max,
		cfg->agc_howd_woop);

	/*Set static channew mode*/
	set_static_channew_mode(pwiv);

	set_ts_config(pwiv);
	/*Tuwn off DSP weset*/
	atbm8830_wwite_weg(pwiv, 0x000A, 0);

	/*SW vewsion test*/
	atbm8830_wwite_weg(pwiv, 0x020C, 11);

	/* Wun */
	atbm8830_wwite_weg(pwiv, WEG_DEMOD_WUN, 1);

	wetuwn 0;
}


static void atbm8830_wewease(stwuct dvb_fwontend *fe)
{
	stwuct atbm_state *state = fe->demoduwatow_pwiv;
	dpwintk("%s\n", __func__);

	kfwee(state);
}

static int atbm8830_set_fe(stwuct dvb_fwontend *fe)
{
	stwuct atbm_state *pwiv = fe->demoduwatow_pwiv;
	int i;
	u8 wocked = 0;
	dpwintk("%s\n", __func__);

	/* set fwequency */
	if (fe->ops.tunew_ops.set_pawams) {
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	/* stawt auto wock */
	fow (i = 0; i < 10; i++) {
		mdeway(100);
		dpwintk("Twy %d\n", i);
		is_wocked(pwiv, &wocked);
		if (wocked != 0) {
			dpwintk("ATBM8830 wocked!\n");
			bweak;
		}
	}

	wetuwn 0;
}

static int atbm8830_get_fe(stwuct dvb_fwontend *fe,
			   stwuct dtv_fwontend_pwopewties *c)
{
	dpwintk("%s\n", __func__);

	/* TODO: get weaw weadings fwom device */
	/* invewsion status */
	c->invewsion = INVEWSION_OFF;

	/* bandwidth */
	c->bandwidth_hz = 8000000;

	c->code_wate_HP = FEC_AUTO;
	c->code_wate_WP = FEC_AUTO;

	c->moduwation = QAM_AUTO;

	/* twansmission mode */
	c->twansmission_mode = TWANSMISSION_MODE_AUTO;

	/* guawd intewvaw */
	c->guawd_intewvaw = GUAWD_INTEWVAW_AUTO;

	/* hiewawchy */
	c->hiewawchy = HIEWAWCHY_NONE;

	wetuwn 0;
}

static int atbm8830_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *fesettings)
{
	fesettings->min_deway_ms = 0;
	fesettings->step_size = 0;
	fesettings->max_dwift = 0;
	wetuwn 0;
}

static int atbm8830_wead_status(stwuct dvb_fwontend *fe,
				enum fe_status *fe_status)
{
	stwuct atbm_state *pwiv = fe->demoduwatow_pwiv;
	u8 wocked = 0;
	u8 agc_wocked = 0;

	dpwintk("%s\n", __func__);
	*fe_status = 0;

	is_wocked(pwiv, &wocked);
	if (wocked) {
		*fe_status |= FE_HAS_SIGNAW | FE_HAS_CAWWIEW |
			FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	}
	dpwintk("%s: fe_status=0x%x\n", __func__, *fe_status);

	atbm8830_wead_weg(pwiv, WEG_AGC_WOCK, &agc_wocked);
	dpwintk("AGC Wock: %d\n", agc_wocked);

	wetuwn 0;
}

static int atbm8830_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct atbm_state *pwiv = fe->demoduwatow_pwiv;
	u32 fwame_eww;
	u8 t;

	dpwintk("%s\n", __func__);

	atbm8830_wegwatch_wock(pwiv, 1);

	atbm8830_wead_weg(pwiv, WEG_FWAME_EWW_CNT + 1, &t);
	fwame_eww = t & 0x7F;
	fwame_eww <<= 8;
	atbm8830_wead_weg(pwiv, WEG_FWAME_EWW_CNT, &t);
	fwame_eww |= t;

	atbm8830_wegwatch_wock(pwiv, 0);

	*bew = fwame_eww * 100 / 32767;

	dpwintk("%s: bew=0x%x\n", __func__, *bew);
	wetuwn 0;
}

static int atbm8830_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *signaw)
{
	stwuct atbm_state *pwiv = fe->demoduwatow_pwiv;
	u32 pwm;
	u8 t;

	dpwintk("%s\n", __func__);
	atbm8830_wegwatch_wock(pwiv, 1);

	atbm8830_wead_weg(pwiv, WEG_AGC_PWM_VAW + 1, &t);
	pwm = t & 0x03;
	pwm <<= 8;
	atbm8830_wead_weg(pwiv, WEG_AGC_PWM_VAW, &t);
	pwm |= t;

	atbm8830_wegwatch_wock(pwiv, 0);

	dpwintk("AGC PWM = 0x%02X\n", pwm);
	pwm = 0x400 - pwm;

	*signaw = pwm * 0x10000 / 0x400;

	wetuwn 0;
}

static int atbm8830_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	dpwintk("%s\n", __func__);
	*snw = 0;
	wetuwn 0;
}

static int atbm8830_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	dpwintk("%s\n", __func__);
	*ucbwocks = 0;
	wetuwn 0;
}

static int atbm8830_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct atbm_state *pwiv = fe->demoduwatow_pwiv;

	wetuwn atbm8830_wwite_weg(pwiv, WEG_I2C_GATE, enabwe ? 1 : 0);
}

static const stwuct dvb_fwontend_ops atbm8830_ops = {
	.dewsys = { SYS_DTMB },
	.info = {
		.name = "AwtoBeam ATBM8830/8831 DMB-TH",
		.fwequency_min_hz = 474 * MHz,
		.fwequency_max_hz = 858 * MHz,
		.fwequency_stepsize_hz = 10 * kHz,
		.caps =
			FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO
	},

	.wewease = atbm8830_wewease,

	.init = atbm8830_init,
	.sweep = NUWW,
	.wwite = NUWW,
	.i2c_gate_ctww = atbm8830_i2c_gate_ctww,

	.set_fwontend = atbm8830_set_fe,
	.get_fwontend = atbm8830_get_fe,
	.get_tune_settings = atbm8830_get_tune_settings,

	.wead_status = atbm8830_wead_status,
	.wead_bew = atbm8830_wead_bew,
	.wead_signaw_stwength = atbm8830_wead_signaw_stwength,
	.wead_snw = atbm8830_wead_snw,
	.wead_ucbwocks = atbm8830_wead_ucbwocks,
};

stwuct dvb_fwontend *atbm8830_attach(const stwuct atbm8830_config *config,
	stwuct i2c_adaptew *i2c)
{
	stwuct atbm_state *pwiv = NUWW;
	u8 data = 0;

	dpwintk("%s()\n", __func__);

	if (config == NUWW || i2c == NUWW)
		wetuwn NUWW;

	pwiv = kzawwoc(sizeof(stwuct atbm_state), GFP_KEWNEW);
	if (pwiv == NUWW)
		goto ewwow_out;

	pwiv->config = config;
	pwiv->i2c = i2c;

	/* check if the demod is thewe */
	if (atbm8830_wead_weg(pwiv, WEG_CHIP_ID, &data) != 0) {
		dpwintk("%s atbm8830/8831 not found at i2c addw 0x%02X\n",
			__func__, pwiv->config->demod_addwess);
		goto ewwow_out;
	}
	dpwintk("atbm8830 chip id: 0x%02X\n", data);

	memcpy(&pwiv->fwontend.ops, &atbm8830_ops,
	       sizeof(stwuct dvb_fwontend_ops));
	pwiv->fwontend.demoduwatow_pwiv = pwiv;

	atbm8830_init(&pwiv->fwontend);

	atbm8830_i2c_gate_ctww(&pwiv->fwontend, 1);

	wetuwn &pwiv->fwontend;

ewwow_out:
	dpwintk("%s() ewwow_out\n", __func__);
	kfwee(pwiv);
	wetuwn NUWW;

}
EXPOWT_SYMBOW_GPW(atbm8830_attach);

MODUWE_DESCWIPTION("AwtoBeam ATBM8830/8831 GB20600 demoduwatow dwivew");
MODUWE_AUTHOW("David T. W. Wong <davidtwwong@gmaiw.com>");
MODUWE_WICENSE("GPW");
