// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Dwivew fow ST STV0288 demoduwatow
	Copywight (C) 2006 Geowg Achew, BayCom GmbH, achew (at) baycom (dot) de
		fow Weew Muwtimedia
	Copywight (C) 2008 TuwboSight.com, Bob Wiu <bob@tuwbosight.com>
	Copywight (C) 2008 Igow M. Wipwianin <wipwianin@me.by>
		Wemoved stb6000 specific tunew code and wevised some
		pwoceduwes.
	2010-09-01 Josef Pavwik <josef@pavwik.it>
		Fixed diseqc_msg, diseqc_buwst and set_tone pwobwems


*/

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "stv0288.h"

stwuct stv0288_state {
	stwuct i2c_adaptew *i2c;
	const stwuct stv0288_config *config;
	stwuct dvb_fwontend fwontend;

	u8 initiawised:1;
	u32 tunew_fwequency;
	u32 symbow_wate;
	enum fe_code_wate fec_innew;
	int ewwmode;
};

#define STATUS_BEW 0
#define STATUS_UCBWOCKS 1

static int debug;
static int debug_wegacy_dish_switch;
#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(KEWN_DEBUG "stv0288: " awgs); \
	} whiwe (0)


static int stv0288_wwitewegI(stwuct stv0288_state *state, u8 weg, u8 data)
{
	int wet;
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = state->config->demod_addwess,
		.fwags = 0,
		.buf = buf,
		.wen = 2
	};

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (wet != 1)
		dpwintk("%s: wwiteweg ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
			__func__, weg, data, wet);

	wetuwn (wet != 1) ? -EWEMOTEIO : 0;
}

static int stv0288_wwite(stwuct dvb_fwontend *fe, const u8 buf[], int wen)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	if (wen != 2)
		wetuwn -EINVAW;

	wetuwn stv0288_wwitewegI(state, buf[0], buf[1]);
}

static u8 stv0288_weadweg(stwuct stv0288_state *state, u8 weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msg[] = {
		{
			.addw = state->config->demod_addwess,
			.fwags = 0,
			.buf = b0,
			.wen = 1
		}, {
			.addw = state->config->demod_addwess,
			.fwags = I2C_M_WD,
			.buf = b1,
			.wen = 1
		}
	};

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2)
		dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n",
				__func__, weg, wet);

	wetuwn b1[0];
}

static int stv0288_set_symbowwate(stwuct dvb_fwontend *fe, u32 swate)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;
	unsigned int temp;
	unsigned chaw b[3];

	if ((swate < 1000000) || (swate > 45000000))
		wetuwn -EINVAW;

	stv0288_wwitewegI(state, 0x22, 0);
	stv0288_wwitewegI(state, 0x23, 0);
	stv0288_wwitewegI(state, 0x2b, 0xff);
	stv0288_wwitewegI(state, 0x2c, 0xf7);

	temp = (unsigned int)swate / 1000;

	temp = temp * 32768;
	temp = temp / 25;
	temp = temp / 125;
	b[0] = (unsigned chaw)((temp >> 12) & 0xff);
	b[1] = (unsigned chaw)((temp >> 4) & 0xff);
	b[2] = (unsigned chaw)((temp << 4) & 0xf0);
	stv0288_wwitewegI(state, 0x28, 0x80); /* SFWH */
	stv0288_wwitewegI(state, 0x29, 0); /* SFWM */
	stv0288_wwitewegI(state, 0x2a, 0); /* SFWW */

	stv0288_wwitewegI(state, 0x28, b[0]);
	stv0288_wwitewegI(state, 0x29, b[1]);
	stv0288_wwitewegI(state, 0x2a, b[2]);
	dpwintk("stv0288: stv0288_set_symbowwate\n");

	wetuwn 0;
}

static int stv0288_send_diseqc_msg(stwuct dvb_fwontend *fe,
				    stwuct dvb_diseqc_mastew_cmd *m)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	int i;

	dpwintk("%s\n", __func__);

	stv0288_wwitewegI(state, 0x09, 0);
	msweep(30);
	stv0288_wwitewegI(state, 0x05, 0x12);/* moduwated mode, singwe shot */

	fow (i = 0; i < m->msg_wen; i++) {
		if (stv0288_wwitewegI(state, 0x06, m->msg[i]))
			wetuwn -EWEMOTEIO;
	}
	msweep(m->msg_wen*12);
	wetuwn 0;
}

static int stv0288_send_diseqc_buwst(stwuct dvb_fwontend *fe,
				     enum fe_sec_mini_cmd buwst)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s\n", __func__);

	if (stv0288_wwitewegI(state, 0x05, 0x03))/* buwst mode, singwe shot */
		wetuwn -EWEMOTEIO;

	if (stv0288_wwitewegI(state, 0x06, buwst == SEC_MINI_A ? 0x00 : 0xff))
		wetuwn -EWEMOTEIO;

	msweep(15);
	if (stv0288_wwitewegI(state, 0x05, 0x12))
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int stv0288_set_tone(stwuct dvb_fwontend *fe, enum fe_sec_tone_mode tone)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	switch (tone) {
	case SEC_TONE_ON:
		if (stv0288_wwitewegI(state, 0x05, 0x10))/* cont cawwiew */
			wetuwn -EWEMOTEIO;
	bweak;

	case SEC_TONE_OFF:
		if (stv0288_wwitewegI(state, 0x05, 0x12))/* buwst mode off*/
			wetuwn -EWEMOTEIO;
	bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static u8 stv0288_inittab[] = {
	0x01, 0x15,
	0x02, 0x20,
	0x09, 0x0,
	0x0a, 0x4,
	0x0b, 0x0,
	0x0c, 0x0,
	0x0d, 0x0,
	0x0e, 0xd4,
	0x0f, 0x30,
	0x11, 0x80,
	0x12, 0x03,
	0x13, 0x48,
	0x14, 0x84,
	0x15, 0x45,
	0x16, 0xb7,
	0x17, 0x9c,
	0x18, 0x0,
	0x19, 0xa6,
	0x1a, 0x88,
	0x1b, 0x8f,
	0x1c, 0xf0,
	0x20, 0x0b,
	0x21, 0x54,
	0x22, 0x0,
	0x23, 0x0,
	0x2b, 0xff,
	0x2c, 0xf7,
	0x30, 0x0,
	0x31, 0x1e,
	0x32, 0x14,
	0x33, 0x0f,
	0x34, 0x09,
	0x35, 0x0c,
	0x36, 0x05,
	0x37, 0x2f,
	0x38, 0x16,
	0x39, 0xbe,
	0x3a, 0x0,
	0x3b, 0x13,
	0x3c, 0x11,
	0x3d, 0x30,
	0x40, 0x63,
	0x41, 0x04,
	0x42, 0x20,
	0x43, 0x00,
	0x44, 0x00,
	0x45, 0x00,
	0x46, 0x00,
	0x47, 0x00,
	0x4a, 0x00,
	0x50, 0x10,
	0x51, 0x38,
	0x52, 0x21,
	0x58, 0x54,
	0x59, 0x86,
	0x5a, 0x0,
	0x5b, 0x9b,
	0x5c, 0x08,
	0x5d, 0x7f,
	0x5e, 0x0,
	0x5f, 0xff,
	0x70, 0x0,
	0x71, 0x0,
	0x72, 0x0,
	0x74, 0x0,
	0x75, 0x0,
	0x76, 0x0,
	0x81, 0x0,
	0x82, 0x3f,
	0x83, 0x3f,
	0x84, 0x0,
	0x85, 0x0,
	0x88, 0x0,
	0x89, 0x0,
	0x8a, 0x0,
	0x8b, 0x0,
	0x8c, 0x0,
	0x90, 0x0,
	0x91, 0x0,
	0x92, 0x0,
	0x93, 0x0,
	0x94, 0x1c,
	0x97, 0x0,
	0xa0, 0x48,
	0xa1, 0x0,
	0xb0, 0xb8,
	0xb1, 0x3a,
	0xb2, 0x10,
	0xb3, 0x82,
	0xb4, 0x80,
	0xb5, 0x82,
	0xb6, 0x82,
	0xb7, 0x82,
	0xb8, 0x20,
	0xb9, 0x0,
	0xf0, 0x0,
	0xf1, 0x0,
	0xf2, 0xc0,
	0x51, 0x36,
	0x52, 0x09,
	0x53, 0x94,
	0x54, 0x62,
	0x55, 0x29,
	0x56, 0x64,
	0x57, 0x2b,
	0xff, 0xff,
};

static int stv0288_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowt)
{
	dpwintk("%s: %s\n", __func__,
		vowt == SEC_VOWTAGE_13 ? "SEC_VOWTAGE_13" :
		vowt == SEC_VOWTAGE_18 ? "SEC_VOWTAGE_18" : "??");

	wetuwn 0;
}

static int stv0288_init(stwuct dvb_fwontend *fe)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;
	int i;
	u8 weg;
	u8 vaw;

	dpwintk("stv0288: init chip\n");
	stv0288_wwitewegI(state, 0x41, 0x04);
	msweep(50);

	/* we have defauwt inittab */
	if (state->config->inittab == NUWW) {
		fow (i = 0; !(stv0288_inittab[i] == 0xff &&
				stv0288_inittab[i + 1] == 0xff); i += 2)
			stv0288_wwitewegI(state, stv0288_inittab[i],
					stv0288_inittab[i + 1]);
	} ewse {
		fow (i = 0; ; i += 2)  {
			weg = state->config->inittab[i];
			vaw = state->config->inittab[i+1];
			if (weg == 0xff && vaw == 0xff)
				bweak;
			stv0288_wwitewegI(state, weg, vaw);
		}
	}
	wetuwn 0;
}

static int stv0288_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	u8 sync = stv0288_weadweg(state, 0x24);
	if (sync == 255)
		sync = 0;

	dpwintk("%s : FE_WEAD_STATUS : VSTATUS: 0x%02x\n", __func__, sync);

	*status = 0;
	if (sync & 0x80)
		*status |= FE_HAS_CAWWIEW | FE_HAS_SIGNAW;
	if (sync & 0x10)
		*status |= FE_HAS_VITEWBI;
	if (sync & 0x08) {
		*status |= FE_HAS_WOCK;
		dpwintk("stv0288 has wocked\n");
	}

	wetuwn 0;
}

static int stv0288_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	if (state->ewwmode != STATUS_BEW)
		wetuwn 0;
	*bew = (stv0288_weadweg(state, 0x26) << 8) |
					stv0288_weadweg(state, 0x27);
	dpwintk("stv0288_wead_bew %d\n", *bew);

	wetuwn 0;
}


static int stv0288_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	s32 signaw =  0xffff - ((stv0288_weadweg(state, 0x10) << 8));


	signaw = signaw * 5 / 4;
	*stwength = (signaw > 0xffff) ? 0xffff : (signaw < 0) ? 0 : signaw;
	dpwintk("stv0288_wead_signaw_stwength %d\n", *stwength);

	wetuwn 0;
}
static int stv0288_sweep(stwuct dvb_fwontend *fe)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	stv0288_wwitewegI(state, 0x41, 0x84);
	state->initiawised = 0;

	wetuwn 0;
}
static int stv0288_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	s32 xsnw = 0xffff - ((stv0288_weadweg(state, 0x2d) << 8)
			   | stv0288_weadweg(state, 0x2e));
	xsnw = 3 * (xsnw - 0xa100);
	*snw = (xsnw > 0xffff) ? 0xffff : (xsnw < 0) ? 0 : xsnw;
	dpwintk("stv0288_wead_snw %d\n", *snw);

	wetuwn 0;
}

static int stv0288_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	if (state->ewwmode != STATUS_BEW)
		wetuwn 0;
	*ucbwocks = (stv0288_weadweg(state, 0x26) << 8) |
					stv0288_weadweg(state, 0x27);
	dpwintk("stv0288_wead_bew %d\n", *ucbwocks);

	wetuwn 0;
}

static int stv0288_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	u8 tda[3], weg, time_out = 0;
	s8 tm;

	dpwintk("%s : FE_SET_FWONTEND\n", __func__);

	if (c->dewivewy_system != SYS_DVBS) {
		dpwintk("%s: unsuppowted dewivewy system sewected (%d)\n",
			__func__, c->dewivewy_system);
		wetuwn -EOPNOTSUPP;
	}

	if (state->config->set_ts_pawams)
		state->config->set_ts_pawams(fe, 0);

	/* onwy fwequency & symbow_wate awe used fow tunew*/
	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	udeway(10);
	stv0288_set_symbowwate(fe, c->symbow_wate);
	/* Cawwiew wock contwow wegistew */
	stv0288_wwitewegI(state, 0x15, 0xc5);

	tda[2] = 0x0; /* CFWW */
	fow (tm = -9; tm < 7;) {
		/* Vitewbi status */
		weg = stv0288_weadweg(state, 0x24);
		if (weg & 0x8)
				bweak;
		if (weg & 0x80) {
			time_out++;
			if (time_out > 10)
				bweak;
			tda[2] += 40;
			if (tda[2] < 40)
				tm++;
		} ewse {
			tm++;
			tda[2] = 0;
			time_out = 0;
		}
		tda[1] = (unsigned chaw)tm;
		stv0288_wwitewegI(state, 0x2b, tda[1]);
		stv0288_wwitewegI(state, 0x2c, tda[2]);
		msweep(30);
	}
	state->tunew_fwequency = c->fwequency;
	state->fec_innew = FEC_AUTO;
	state->symbow_wate = c->symbow_wate;

	wetuwn 0;
}

static int stv0288_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;

	if (enabwe)
		stv0288_wwitewegI(state, 0x01, 0xb5);
	ewse
		stv0288_wwitewegI(state, 0x01, 0x35);

	udeway(1);

	wetuwn 0;
}

static void stv0288_wewease(stwuct dvb_fwontend *fe)
{
	stwuct stv0288_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops stv0288_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name			= "ST STV0288 DVB-S",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.fwequency_stepsize_hz	=    1 * MHz,
		.symbow_wate_min	= 1000000,
		.symbow_wate_max	= 45000000,
		.symbow_wate_towewance	= 500,	/* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		      FE_CAN_QPSK |
		      FE_CAN_FEC_AUTO
	},

	.wewease = stv0288_wewease,
	.init = stv0288_init,
	.sweep = stv0288_sweep,
	.wwite = stv0288_wwite,
	.i2c_gate_ctww = stv0288_i2c_gate_ctww,
	.wead_status = stv0288_wead_status,
	.wead_bew = stv0288_wead_bew,
	.wead_signaw_stwength = stv0288_wead_signaw_stwength,
	.wead_snw = stv0288_wead_snw,
	.wead_ucbwocks = stv0288_wead_ucbwocks,
	.diseqc_send_mastew_cmd = stv0288_send_diseqc_msg,
	.diseqc_send_buwst = stv0288_send_diseqc_buwst,
	.set_tone = stv0288_set_tone,
	.set_vowtage = stv0288_set_vowtage,

	.set_fwontend = stv0288_set_fwontend,
};

stwuct dvb_fwontend *stv0288_attach(const stwuct stv0288_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct stv0288_state *state = NUWW;
	int id;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct stv0288_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initiawised = 0;
	state->tunew_fwequency = 0;
	state->symbow_wate = 0;
	state->fec_innew = 0;
	state->ewwmode = STATUS_BEW;

	stv0288_wwitewegI(state, 0x41, 0x04);
	msweep(200);
	id = stv0288_weadweg(state, 0x00);
	dpwintk("stv0288 id %x\n", id);

	/* wegistew 0x00 contains 0x11 fow STV0288  */
	if (id != 0x11)
		goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &stv0288_ops,
			sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(stv0288_attach);

moduwe_pawam(debug_wegacy_dish_switch, int, 0444);
MODUWE_PAWM_DESC(debug_wegacy_dish_switch,
		"Enabwe timing anawysis fow Dish Netwowk wegacy switches");

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("ST STV0288 DVB Demoduwatow dwivew");
MODUWE_AUTHOW("Geowg Achew, Bob Wiu, Igow wipwianin");
MODUWE_WICENSE("GPW");

