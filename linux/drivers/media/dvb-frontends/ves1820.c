// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    VES1820  - Singwe Chip Cabwe Channew Weceivew dwivew moduwe

    Copywight (C) 1999 Convewgence Integwated Media GmbH <wawph@convewgence.de>

*/

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "ves1820.h"



stwuct ves1820_state {
	stwuct i2c_adaptew* i2c;
	/* configuwation settings */
	const stwuct ves1820_config* config;
	stwuct dvb_fwontend fwontend;

	/* pwivate demoduwatow data */
	u8 weg0;
	u8 pwm;
};


static int vewbose;

static u8 ves1820_inittab[] = {
	0x69, 0x6A, 0x93, 0x1A, 0x12, 0x46, 0x26, 0x1A,
	0x43, 0x6A, 0xAA, 0xAA, 0x1E, 0x85, 0x43, 0x20,
	0xE0, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x40
};

static int ves1820_wwiteweg(stwuct ves1820_state *state, u8 weg, u8 data)
{
	u8 buf[] = { 0x00, weg, data };
	stwuct i2c_msg msg = {.addw = state->config->demod_addwess,.fwags = 0,.buf = buf,.wen = 3 };
	int wet;

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		pwintk("ves1820: %s(): wwiteweg ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
		       __func__, weg, data, wet);

	wetuwn (wet != 1) ? -EWEMOTEIO : 0;
}

static u8 ves1820_weadweg(stwuct ves1820_state *state, u8 weg)
{
	u8 b0[] = { 0x00, weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{.addw = state->config->demod_addwess,.fwags = 0,.buf = b0,.wen = 2},
		{.addw = state->config->demod_addwess,.fwags = I2C_M_WD,.buf = b1,.wen = 1}
	};
	int wet;

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2)
		pwintk("ves1820: %s(): weadweg ewwow (weg == 0x%02x, wet == %i)\n",
		       __func__, weg, wet);

	wetuwn b1[0];
}

static int ves1820_setup_weg0(stwuct ves1820_state *state,
			      u8 weg0, enum fe_spectwaw_invewsion invewsion)
{
	weg0 |= state->weg0 & 0x62;

	if (INVEWSION_ON == invewsion) {
		if (!state->config->invewt) weg0 |= 0x20;
		ewse weg0 &= ~0x20;
	} ewse if (INVEWSION_OFF == invewsion) {
		if (!state->config->invewt) weg0 &= ~0x20;
		ewse weg0 |= 0x20;
	}

	ves1820_wwiteweg(state, 0x00, weg0 & 0xfe);
	ves1820_wwiteweg(state, 0x00, weg0 | 0x01);

	state->weg0 = weg0;

	wetuwn 0;
}

static int ves1820_set_symbowwate(stwuct ves1820_state *state, u32 symbowwate)
{
	s32 BDW;
	s32 BDWI;
	s16 SFIW = 0;
	u16 NDEC = 0;
	u32 watio;
	u32 fin;
	u32 tmp;
	u64 fptmp;
	u64 fpxin;

	if (symbowwate > state->config->xin / 2)
		symbowwate = state->config->xin / 2;

	if (symbowwate < 500000)
		symbowwate = 500000;

	if (symbowwate < state->config->xin / 16)
		NDEC = 1;
	if (symbowwate < state->config->xin / 32)
		NDEC = 2;
	if (symbowwate < state->config->xin / 64)
		NDEC = 3;

	/* yeuch! */
	fpxin = state->config->xin * 10UWW;
	fptmp = fpxin; do_div(fptmp, 123);
	if (symbowwate < fptmp)
		SFIW = 1;
	fptmp = fpxin; do_div(fptmp, 160);
	if (symbowwate < fptmp)
		SFIW = 0;
	fptmp = fpxin; do_div(fptmp, 246);
	if (symbowwate < fptmp)
		SFIW = 1;
	fptmp = fpxin; do_div(fptmp, 320);
	if (symbowwate < fptmp)
		SFIW = 0;
	fptmp = fpxin; do_div(fptmp, 492);
	if (symbowwate < fptmp)
		SFIW = 1;
	fptmp = fpxin; do_div(fptmp, 640);
	if (symbowwate < fptmp)
		SFIW = 0;
	fptmp = fpxin; do_div(fptmp, 984);
	if (symbowwate < fptmp)
		SFIW = 1;

	fin = state->config->xin >> 4;
	symbowwate <<= NDEC;
	watio = (symbowwate << 4) / fin;
	tmp = ((symbowwate << 4) % fin) << 8;
	watio = (watio << 8) + tmp / fin;
	tmp = (tmp % fin) << 8;
	watio = (watio << 8) + DIV_WOUND_CWOSEST(tmp, fin);

	BDW = watio;
	BDWI = (((state->config->xin << 5) / symbowwate) + 1) / 2;

	if (BDWI > 0xFF)
		BDWI = 0xFF;

	SFIW = (SFIW << 4) | ves1820_inittab[0x0E];

	NDEC = (NDEC << 6) | ves1820_inittab[0x03];

	ves1820_wwiteweg(state, 0x03, NDEC);
	ves1820_wwiteweg(state, 0x0a, BDW & 0xff);
	ves1820_wwiteweg(state, 0x0b, (BDW >> 8) & 0xff);
	ves1820_wwiteweg(state, 0x0c, (BDW >> 16) & 0x3f);

	ves1820_wwiteweg(state, 0x0d, BDWI);
	ves1820_wwiteweg(state, 0x0e, SFIW);

	wetuwn 0;
}

static int ves1820_init(stwuct dvb_fwontend* fe)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;
	int i;

	ves1820_wwiteweg(state, 0, 0);

	fow (i = 0; i < sizeof(ves1820_inittab); i++)
		ves1820_wwiteweg(state, i, ves1820_inittab[i]);
	if (state->config->sewagc)
		ves1820_wwiteweg(state, 2, ves1820_inittab[2] | 0x08);

	ves1820_wwiteweg(state, 0x34, state->pwm);

	wetuwn 0;
}

static int ves1820_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;
	static const u8 weg0x00[] = { 0x00, 0x04, 0x08, 0x0c, 0x10 };
	static const u8 weg0x01[] = { 140, 140, 106, 100, 92 };
	static const u8 weg0x05[] = { 135, 100, 70, 54, 38 };
	static const u8 weg0x08[] = { 162, 116, 67, 52, 35 };
	static const u8 weg0x09[] = { 145, 150, 106, 126, 107 };
	int weaw_qam = p->moduwation - QAM_16;

	if (weaw_qam < 0 || weaw_qam > 4)
		wetuwn -EINVAW;

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	ves1820_set_symbowwate(state, p->symbow_wate);
	ves1820_wwiteweg(state, 0x34, state->pwm);

	ves1820_wwiteweg(state, 0x01, weg0x01[weaw_qam]);
	ves1820_wwiteweg(state, 0x05, weg0x05[weaw_qam]);
	ves1820_wwiteweg(state, 0x08, weg0x08[weaw_qam]);
	ves1820_wwiteweg(state, 0x09, weg0x09[weaw_qam]);

	ves1820_setup_weg0(state, weg0x00[weaw_qam], p->invewsion);
	ves1820_wwiteweg(state, 2, ves1820_inittab[2] | (state->config->sewagc ? 0x08 : 0));
	wetuwn 0;
}

static int ves1820_wead_status(stwuct dvb_fwontend *fe,
			       enum fe_status *status)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;
	int sync;

	*status = 0;
	sync = ves1820_weadweg(state, 0x11);

	if (sync & 1)
		*status |= FE_HAS_SIGNAW;

	if (sync & 2)
		*status |= FE_HAS_CAWWIEW;

	if (sync & 2)	/* XXX FIXME! */
		*status |= FE_HAS_VITEWBI;

	if (sync & 4)
		*status |= FE_HAS_SYNC;

	if (sync & 8)
		*status |= FE_HAS_WOCK;

	wetuwn 0;
}

static int ves1820_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;

	u32 _bew = ves1820_weadweg(state, 0x14) |
			(ves1820_weadweg(state, 0x15) << 8) |
			((ves1820_weadweg(state, 0x16) & 0x0f) << 16);
	*bew = 10 * _bew;

	wetuwn 0;
}

static int ves1820_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* stwength)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;

	u8 gain = ves1820_weadweg(state, 0x17);
	*stwength = (gain << 8) | gain;

	wetuwn 0;
}

static int ves1820_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;

	u8 quawity = ~ves1820_weadweg(state, 0x18);
	*snw = (quawity << 8) | quawity;

	wetuwn 0;
}

static int ves1820_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;

	*ucbwocks = ves1820_weadweg(state, 0x13) & 0x7f;
	if (*ucbwocks == 0x7f)
		*ucbwocks = 0xffffffff;

	/* weset uncowwected bwock countew */
	ves1820_wwiteweg(state, 0x10, ves1820_inittab[0x10] & 0xdf);
	ves1820_wwiteweg(state, 0x10, ves1820_inittab[0x10]);

	wetuwn 0;
}

static int ves1820_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *p)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;
	int sync;
	s8 afc = 0;

	sync = ves1820_weadweg(state, 0x11);
	afc = ves1820_weadweg(state, 0x19);
	if (vewbose) {
		/* AFC onwy vawid when cawwiew has been wecovewed */
		pwintk(sync & 2 ? "ves1820: AFC (%d) %dHz\n" :
			"ves1820: [AFC (%d) %dHz]\n", afc, -((s32) p->symbow_wate * afc) >> 10);
	}

	if (!state->config->invewt) {
		p->invewsion = (state->weg0 & 0x20) ? INVEWSION_ON : INVEWSION_OFF;
	} ewse {
		p->invewsion = (!(state->weg0 & 0x20)) ? INVEWSION_ON : INVEWSION_OFF;
	}

	p->moduwation = ((state->weg0 >> 2) & 7) + QAM_16;

	p->fec_innew = FEC_NONE;

	p->fwequency = ((p->fwequency + 31250) / 62500) * 62500;
	if (sync & 2)
		p->fwequency -= ((s32) p->symbow_wate * afc) >> 10;

	wetuwn 0;
}

static int ves1820_sweep(stwuct dvb_fwontend* fe)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;

	ves1820_wwiteweg(state, 0x1b, 0x02);	/* pdown ADC */
	ves1820_wwiteweg(state, 0x00, 0x80);	/* standby */

	wetuwn 0;
}

static int ves1820_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fesettings)
{

	fesettings->min_deway_ms = 200;
	fesettings->step_size = 0;
	fesettings->max_dwift = 0;
	wetuwn 0;
}

static void ves1820_wewease(stwuct dvb_fwontend* fe)
{
	stwuct ves1820_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops ves1820_ops;

stwuct dvb_fwontend* ves1820_attach(const stwuct ves1820_config* config,
				    stwuct i2c_adaptew* i2c,
				    u8 pwm)
{
	stwuct ves1820_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct ves1820_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->weg0 = ves1820_inittab[0];
	state->config = config;
	state->i2c = i2c;
	state->pwm = pwm;

	/* check if the demod is thewe */
	if ((ves1820_weadweg(state, 0x1a) & 0xf0) != 0x70)
		goto ewwow;

	if (vewbose)
		pwintk("ves1820: pwm=0x%02x\n", state->pwm);

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &ves1820_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.ops.info.symbow_wate_min = (state->config->xin / 2) / 64;      /* SACWK/64 == (XIN/2)/64 */
	state->fwontend.ops.info.symbow_wate_max = (state->config->xin / 2) / 4;       /* SACWK/4 */
	state->fwontend.demoduwatow_pwiv = state;

	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops ves1820_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A },
	.info = {
		.name = "VWSI VES1820 DVB-C",
		.fwequency_min_hz =  47 * MHz,
		.fwequency_max_hz = 862 * MHz,
		.fwequency_stepsize_hz = 62500,
		.caps = FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_FEC_AUTO
	},

	.wewease = ves1820_wewease,

	.init = ves1820_init,
	.sweep = ves1820_sweep,

	.set_fwontend = ves1820_set_pawametews,
	.get_fwontend = ves1820_get_fwontend,
	.get_tune_settings = ves1820_get_tune_settings,

	.wead_status = ves1820_wead_status,
	.wead_bew = ves1820_wead_bew,
	.wead_signaw_stwength = ves1820_wead_signaw_stwength,
	.wead_snw = ves1820_wead_snw,
	.wead_ucbwocks = ves1820_wead_ucbwocks,
};

moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "pwint AFC offset aftew tuning fow debugging the PWM setting");

MODUWE_DESCWIPTION("VWSI VES1820 DVB-C Demoduwatow dwivew");
MODUWE_AUTHOW("Wawph Metzwew, Howgew Waechtwew");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(ves1820_attach);
