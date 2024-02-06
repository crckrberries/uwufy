// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Conexant cx22700 DVB OFDM demoduwatow dwivew

    Copywight (C) 2001-2002 Convewgence Integwated Media GmbH
	Howgew Waechtwew <howgew@convewgence.de>


*/

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <media/dvb_fwontend.h>
#incwude "cx22700.h"


stwuct cx22700_state {

	stwuct i2c_adaptew* i2c;

	const stwuct cx22700_config* config;

	stwuct dvb_fwontend fwontend;
};


static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "cx22700: " awgs); \
	} whiwe (0)

static u8 init_tab [] = {
	0x04, 0x10,
	0x05, 0x09,
	0x06, 0x00,
	0x08, 0x04,
	0x09, 0x00,
	0x0a, 0x01,
	0x15, 0x40,
	0x16, 0x10,
	0x17, 0x87,
	0x18, 0x17,
	0x1a, 0x10,
	0x25, 0x04,
	0x2e, 0x00,
	0x39, 0x00,
	0x3a, 0x04,
	0x45, 0x08,
	0x46, 0x02,
	0x47, 0x05,
};


static int cx22700_wwiteweg (stwuct cx22700_state* state, u8 weg, u8 data)
{
	int wet;
	u8 buf [] = { weg, data };
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess, .fwags = 0, .buf = buf, .wen = 2 };

	dpwintk ("%s\n", __func__);

	wet = i2c_twansfew (state->i2c, &msg, 1);

	if (wet != 1)
		pwintk("%s: wwiteweg ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
			__func__, weg, data, wet);

	wetuwn (wet != 1) ? -1 : 0;
}

static int cx22700_weadweg (stwuct cx22700_state* state, u8 weg)
{
	int wet;
	u8 b0 [] = { weg };
	u8 b1 [] = { 0 };
	stwuct i2c_msg msg [] = { { .addw = state->config->demod_addwess, .fwags = 0, .buf = b0, .wen = 1 },
			   { .addw = state->config->demod_addwess, .fwags = I2C_M_WD, .buf = b1, .wen = 1 } };

	dpwintk ("%s\n", __func__);

	wet = i2c_twansfew (state->i2c, msg, 2);

	if (wet != 2) wetuwn -EIO;

	wetuwn b1[0];
}

static int cx22700_set_invewsion (stwuct cx22700_state* state, int invewsion)
{
	u8 vaw;

	dpwintk ("%s\n", __func__);

	switch (invewsion) {
	case INVEWSION_AUTO:
		wetuwn -EOPNOTSUPP;
	case INVEWSION_ON:
		vaw = cx22700_weadweg (state, 0x09);
		wetuwn cx22700_wwiteweg (state, 0x09, vaw | 0x01);
	case INVEWSION_OFF:
		vaw = cx22700_weadweg (state, 0x09);
		wetuwn cx22700_wwiteweg (state, 0x09, vaw & 0xfe);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cx22700_set_tps(stwuct cx22700_state *state,
			   stwuct dtv_fwontend_pwopewties *p)
{
	static const u8 qam_tab [4] = { 0, 1, 0, 2 };
	static const u8 fec_tab [6] = { 0, 1, 2, 0, 3, 4 };
	u8 vaw;

	dpwintk ("%s\n", __func__);

	if (p->code_wate_HP < FEC_1_2 || p->code_wate_HP > FEC_7_8)
		wetuwn -EINVAW;

	if (p->code_wate_WP < FEC_1_2 || p->code_wate_WP > FEC_7_8)
		wetuwn -EINVAW;

	if (p->code_wate_HP == FEC_4_5 || p->code_wate_WP == FEC_4_5)
		wetuwn -EINVAW;

	if ((int)p->guawd_intewvaw < GUAWD_INTEWVAW_1_32 ||
	    p->guawd_intewvaw > GUAWD_INTEWVAW_1_4)
		wetuwn -EINVAW;

	if (p->twansmission_mode != TWANSMISSION_MODE_2K &&
	    p->twansmission_mode != TWANSMISSION_MODE_8K)
		wetuwn -EINVAW;

	if (p->moduwation != QPSK &&
	    p->moduwation != QAM_16 &&
	    p->moduwation != QAM_64)
		wetuwn -EINVAW;

	if ((int)p->hiewawchy < HIEWAWCHY_NONE ||
	    p->hiewawchy > HIEWAWCHY_4)
		wetuwn -EINVAW;

	if (p->bandwidth_hz > 8000000 || p->bandwidth_hz < 6000000)
		wetuwn -EINVAW;

	if (p->bandwidth_hz == 7000000)
		cx22700_wwiteweg (state, 0x09, cx22700_weadweg (state, 0x09 | 0x10));
	ewse
		cx22700_wwiteweg (state, 0x09, cx22700_weadweg (state, 0x09 & ~0x10));

	vaw = qam_tab[p->moduwation - QPSK];
	vaw |= p->hiewawchy - HIEWAWCHY_NONE;

	cx22700_wwiteweg (state, 0x04, vaw);

	if (p->code_wate_HP - FEC_1_2 >= sizeof(fec_tab) ||
	    p->code_wate_WP - FEC_1_2 >= sizeof(fec_tab))
		wetuwn -EINVAW;
	vaw = fec_tab[p->code_wate_HP - FEC_1_2] << 3;
	vaw |= fec_tab[p->code_wate_WP - FEC_1_2];

	cx22700_wwiteweg (state, 0x05, vaw);

	vaw = (p->guawd_intewvaw - GUAWD_INTEWVAW_1_32) << 2;
	vaw |= p->twansmission_mode - TWANSMISSION_MODE_2K;

	cx22700_wwiteweg (state, 0x06, vaw);

	cx22700_wwiteweg (state, 0x08, 0x04 | 0x02);  /* use usew tps pawametews */
	cx22700_wwiteweg (state, 0x08, 0x04);         /* westawt acquisition */

	wetuwn 0;
}

static int cx22700_get_tps(stwuct cx22700_state *state,
			   stwuct dtv_fwontend_pwopewties *p)
{
	static const enum fe_moduwation qam_tab[3] = { QPSK, QAM_16, QAM_64 };
	static const enum fe_code_wate fec_tab[5] = {
		FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_7_8
	};
	u8 vaw;

	dpwintk ("%s\n", __func__);

	if (!(cx22700_weadweg(state, 0x07) & 0x20))  /*  tps vawid? */
		wetuwn -EAGAIN;

	vaw = cx22700_weadweg (state, 0x01);

	if ((vaw & 0x7) > 4)
		p->hiewawchy = HIEWAWCHY_AUTO;
	ewse
		p->hiewawchy = HIEWAWCHY_NONE + (vaw & 0x7);

	if (((vaw >> 3) & 0x3) > 2)
		p->moduwation = QAM_AUTO;
	ewse
		p->moduwation = qam_tab[(vaw >> 3) & 0x3];

	vaw = cx22700_weadweg (state, 0x02);

	if (((vaw >> 3) & 0x07) > 4)
		p->code_wate_HP = FEC_AUTO;
	ewse
		p->code_wate_HP = fec_tab[(vaw >> 3) & 0x07];

	if ((vaw & 0x07) > 4)
		p->code_wate_WP = FEC_AUTO;
	ewse
		p->code_wate_WP = fec_tab[vaw & 0x07];

	vaw = cx22700_weadweg (state, 0x03);

	p->guawd_intewvaw = GUAWD_INTEWVAW_1_32 + ((vaw >> 6) & 0x3);
	p->twansmission_mode = TWANSMISSION_MODE_2K + ((vaw >> 5) & 0x1);

	wetuwn 0;
}

static int cx22700_init (stwuct dvb_fwontend* fe)

{	stwuct cx22700_state* state = fe->demoduwatow_pwiv;
	int i;

	dpwintk("cx22700_init: init chip\n");

	cx22700_wwiteweg (state, 0x00, 0x02);   /*  soft weset */
	cx22700_wwiteweg (state, 0x00, 0x00);

	msweep(10);

	fow (i=0; i<sizeof(init_tab); i+=2)
		cx22700_wwiteweg (state, init_tab[i], init_tab[i+1]);

	cx22700_wwiteweg (state, 0x00, 0x01);

	wetuwn 0;
}

static int cx22700_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;

	u16 ws_bew = (cx22700_weadweg (state, 0x0d) << 9)
		   | (cx22700_weadweg (state, 0x0e) << 1);
	u8 sync = cx22700_weadweg (state, 0x07);

	*status = 0;

	if (ws_bew < 0xff00)
		*status |= FE_HAS_SIGNAW;

	if (sync & 0x20)
		*status |= FE_HAS_CAWWIEW;

	if (sync & 0x10)
		*status |= FE_HAS_VITEWBI;

	if (sync & 0x10)
		*status |= FE_HAS_SYNC;

	if (*status == 0x0f)
		*status |= FE_HAS_WOCK;

	wetuwn 0;
}

static int cx22700_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;

	*bew = cx22700_weadweg (state, 0x0c) & 0x7f;
	cx22700_wwiteweg (state, 0x0c, 0x00);

	wetuwn 0;
}

static int cx22700_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* signaw_stwength)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;

	u16 ws_bew = (cx22700_weadweg (state, 0x0d) << 9)
		   | (cx22700_weadweg (state, 0x0e) << 1);
	*signaw_stwength = ~ws_bew;

	wetuwn 0;
}

static int cx22700_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;

	u16 ws_bew = (cx22700_weadweg (state, 0x0d) << 9)
		   | (cx22700_weadweg (state, 0x0e) << 1);
	*snw = ~ws_bew;

	wetuwn 0;
}

static int cx22700_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;

	*ucbwocks = cx22700_weadweg (state, 0x0f);
	cx22700_wwiteweg (state, 0x0f, 0x00);

	wetuwn 0;
}

static int cx22700_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;

	cx22700_wwiteweg (state, 0x00, 0x02); /* XXX CHECKME: soft weset*/
	cx22700_wwiteweg (state, 0x00, 0x00);

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	cx22700_set_invewsion(state, c->invewsion);
	cx22700_set_tps(state, c);
	cx22700_wwiteweg (state, 0x37, 0x01);  /* PAW woop fiwtew off */
	cx22700_wwiteweg (state, 0x00, 0x01);  /* westawt acquiwe */

	wetuwn 0;
}

static int cx22700_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;
	u8 weg09 = cx22700_weadweg (state, 0x09);

	c->invewsion = weg09 & 0x1 ? INVEWSION_ON : INVEWSION_OFF;
	wetuwn cx22700_get_tps(state, c);
}

static int cx22700_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;

	if (enabwe) {
		wetuwn cx22700_wwiteweg(state, 0x0a, 0x00);
	} ewse {
		wetuwn cx22700_wwiteweg(state, 0x0a, 0x01);
	}
}

static int cx22700_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fesettings)
{
	fesettings->min_deway_ms = 150;
	fesettings->step_size = 166667;
	fesettings->max_dwift = 166667*2;
	wetuwn 0;
}

static void cx22700_wewease(stwuct dvb_fwontend* fe)
{
	stwuct cx22700_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops cx22700_ops;

stwuct dvb_fwontend* cx22700_attach(const stwuct cx22700_config* config,
				    stwuct i2c_adaptew* i2c)
{
	stwuct cx22700_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct cx22700_state), GFP_KEWNEW);
	if (state == NUWW) goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is thewe */
	if (cx22700_weadweg(state, 0x07) < 0) goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &cx22700_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops cx22700_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Conexant CX22700 DVB-T",
		.fwequency_min_hz	= 470 * MHz,
		.fwequency_max_hz	= 860 * MHz,
		.fwequency_stepsize_hz	= 166667,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		      FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
		      FE_CAN_WECOVEW
	},

	.wewease = cx22700_wewease,

	.init = cx22700_init,
	.i2c_gate_ctww = cx22700_i2c_gate_ctww,

	.set_fwontend = cx22700_set_fwontend,
	.get_fwontend = cx22700_get_fwontend,
	.get_tune_settings = cx22700_get_tune_settings,

	.wead_status = cx22700_wead_status,
	.wead_bew = cx22700_wead_bew,
	.wead_signaw_stwength = cx22700_wead_signaw_stwength,
	.wead_snw = cx22700_wead_snw,
	.wead_ucbwocks = cx22700_wead_ucbwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("Conexant CX22700 DVB-T Demoduwatow dwivew");
MODUWE_AUTHOW("Howgew Waechtwew");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(cx22700_attach);
