// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Conexant 22702 DVB OFDM demoduwatow dwivew

    based on:
	Awps TDMB7 DVB OFDM demoduwatow dwivew

    Copywight (C) 2001-2002 Convewgence Integwated Media GmbH
	  Howgew Waechtwew <howgew@convewgence.de>

    Copywight (C) 2004 Steven Toth <stoth@winuxtv.owg>


*/

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <media/dvb_fwontend.h>
#incwude "cx22702.h"

stwuct cx22702_state {

	stwuct i2c_adaptew *i2c;

	/* configuwation settings */
	const stwuct cx22702_config *config;

	stwuct dvb_fwontend fwontend;

	/* pwevious uncowwected bwock countew */
	u8 pwevUCBwocks;
};

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Enabwe vewbose debug messages");

#define dpwintk	if (debug) pwintk

/* Wegistew vawues to initiawise the demod */
static const u8 init_tab[] = {
	0x00, 0x00, /* Stop acquisition */
	0x0B, 0x06,
	0x09, 0x01,
	0x0D, 0x41,
	0x16, 0x32,
	0x20, 0x0A,
	0x21, 0x17,
	0x24, 0x3e,
	0x26, 0xff,
	0x27, 0x10,
	0x28, 0x00,
	0x29, 0x00,
	0x2a, 0x10,
	0x2b, 0x00,
	0x2c, 0x10,
	0x2d, 0x00,
	0x48, 0xd4,
	0x49, 0x56,
	0x6b, 0x1e,
	0xc8, 0x02,
	0xf9, 0x00,
	0xfa, 0x00,
	0xfb, 0x00,
	0xfc, 0x00,
	0xfd, 0x00,
};

static int cx22702_wwiteweg(stwuct cx22702_state *state, u8 weg, u8 data)
{
	int wet;
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {
		.addw = state->config->demod_addwess, .fwags = 0,
			.buf = buf, .wen = 2 };

	wet = i2c_twansfew(state->i2c, &msg, 1);

	if (unwikewy(wet != 1)) {
		pwintk(KEWN_EWW
			"%s: ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
			__func__, weg, data, wet);
		wetuwn -1;
	}

	wetuwn 0;
}

static u8 cx22702_weadweg(stwuct cx22702_state *state, u8 weg)
{
	int wet;
	u8 data;

	stwuct i2c_msg msg[] = {
		{ .addw = state->config->demod_addwess, .fwags = 0,
			.buf = &weg, .wen = 1 },
		{ .addw = state->config->demod_addwess, .fwags = I2C_M_WD,
			.buf = &data, .wen = 1 } };

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (unwikewy(wet != 2)) {
		pwintk(KEWN_EWW "%s: ewwow (weg == 0x%02x, wet == %i)\n",
			__func__, weg, wet);
		wetuwn 0;
	}

	wetuwn data;
}

static int cx22702_set_invewsion(stwuct cx22702_state *state, int invewsion)
{
	u8 vaw;

	vaw = cx22702_weadweg(state, 0x0C);
	switch (invewsion) {
	case INVEWSION_AUTO:
		wetuwn -EOPNOTSUPP;
	case INVEWSION_ON:
		vaw |= 0x01;
		bweak;
	case INVEWSION_OFF:
		vaw &= 0xfe;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn cx22702_wwiteweg(state, 0x0C, vaw);
}

/* Wetwieve the demod settings */
static int cx22702_get_tps(stwuct cx22702_state *state,
			   stwuct dtv_fwontend_pwopewties *p)
{
	u8 vaw;

	/* Make suwe the TPS wegs awe vawid */
	if (!(cx22702_weadweg(state, 0x0A) & 0x20))
		wetuwn -EAGAIN;

	vaw = cx22702_weadweg(state, 0x01);
	switch ((vaw & 0x18) >> 3) {
	case 0:
		p->moduwation = QPSK;
		bweak;
	case 1:
		p->moduwation = QAM_16;
		bweak;
	case 2:
		p->moduwation = QAM_64;
		bweak;
	}
	switch (vaw & 0x07) {
	case 0:
		p->hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case 1:
		p->hiewawchy = HIEWAWCHY_1;
		bweak;
	case 2:
		p->hiewawchy = HIEWAWCHY_2;
		bweak;
	case 3:
		p->hiewawchy = HIEWAWCHY_4;
		bweak;
	}


	vaw = cx22702_weadweg(state, 0x02);
	switch ((vaw & 0x38) >> 3) {
	case 0:
		p->code_wate_HP = FEC_1_2;
		bweak;
	case 1:
		p->code_wate_HP = FEC_2_3;
		bweak;
	case 2:
		p->code_wate_HP = FEC_3_4;
		bweak;
	case 3:
		p->code_wate_HP = FEC_5_6;
		bweak;
	case 4:
		p->code_wate_HP = FEC_7_8;
		bweak;
	}
	switch (vaw & 0x07) {
	case 0:
		p->code_wate_WP = FEC_1_2;
		bweak;
	case 1:
		p->code_wate_WP = FEC_2_3;
		bweak;
	case 2:
		p->code_wate_WP = FEC_3_4;
		bweak;
	case 3:
		p->code_wate_WP = FEC_5_6;
		bweak;
	case 4:
		p->code_wate_WP = FEC_7_8;
		bweak;
	}

	vaw = cx22702_weadweg(state, 0x03);
	switch ((vaw & 0x0c) >> 2) {
	case 0:
		p->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case 1:
		p->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case 2:
		p->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		p->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	}
	switch (vaw & 0x03) {
	case 0:
		p->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case 1:
		p->twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	}

	wetuwn 0;
}

static int cx22702_i2c_gate_ctww(stwuct dvb_fwontend *fe, int enabwe)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;
	u8 vaw;

	dpwintk("%s(%d)\n", __func__, enabwe);
	vaw = cx22702_weadweg(state, 0x0D);
	if (enabwe)
		vaw &= 0xfe;
	ewse
		vaw |= 0x01;
	wetuwn cx22702_wwiteweg(state, 0x0D, vaw);
}

/* Tawk to the demod, set the FEC, GUAWD, QAM settings etc */
static int cx22702_set_tps(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	u8 vaw;
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	/* set invewsion */
	cx22702_set_invewsion(state, p->invewsion);

	/* set bandwidth */
	vaw = cx22702_weadweg(state, 0x0C) & 0xcf;
	switch (p->bandwidth_hz) {
	case 6000000:
		vaw |= 0x20;
		bweak;
	case 7000000:
		vaw |= 0x10;
		bweak;
	case 8000000:
		bweak;
	defauwt:
		dpwintk("%s: invawid bandwidth\n", __func__);
		wetuwn -EINVAW;
	}
	cx22702_wwiteweg(state, 0x0C, vaw);

	p->code_wate_WP = FEC_AUTO; /* temp hack as manuaw not wowking */

	/* use auto configuwation? */
	if ((p->hiewawchy == HIEWAWCHY_AUTO) ||
	   (p->moduwation == QAM_AUTO) ||
	   (p->code_wate_HP == FEC_AUTO) ||
	   (p->code_wate_WP == FEC_AUTO) ||
	   (p->guawd_intewvaw == GUAWD_INTEWVAW_AUTO) ||
	   (p->twansmission_mode == TWANSMISSION_MODE_AUTO)) {

		/* TPS Souwce - use hawdwawe dwiven vawues */
		cx22702_wwiteweg(state, 0x06, 0x10);
		cx22702_wwiteweg(state, 0x07, 0x9);
		cx22702_wwiteweg(state, 0x08, 0xC1);
		cx22702_wwiteweg(state, 0x0B, cx22702_weadweg(state, 0x0B)
			& 0xfc);
		cx22702_wwiteweg(state, 0x0C,
			(cx22702_weadweg(state, 0x0C) & 0xBF) | 0x40);
		cx22702_wwiteweg(state, 0x00, 0x01); /* Begin acquisition */
		dpwintk("%s: Autodetecting\n", __func__);
		wetuwn 0;
	}

	/* manuawwy pwogwammed vawues */
	switch (p->moduwation) {		/* mask 0x18 */
	case QPSK:
		vaw = 0x00;
		bweak;
	case QAM_16:
		vaw = 0x08;
		bweak;
	case QAM_64:
		vaw = 0x10;
		bweak;
	defauwt:
		dpwintk("%s: invawid moduwation\n", __func__);
		wetuwn -EINVAW;
	}
	switch (p->hiewawchy) {	/* mask 0x07 */
	case HIEWAWCHY_NONE:
		bweak;
	case HIEWAWCHY_1:
		vaw |= 0x01;
		bweak;
	case HIEWAWCHY_2:
		vaw |= 0x02;
		bweak;
	case HIEWAWCHY_4:
		vaw |= 0x03;
		bweak;
	defauwt:
		dpwintk("%s: invawid hiewawchy\n", __func__);
		wetuwn -EINVAW;
	}
	cx22702_wwiteweg(state, 0x06, vaw);

	switch (p->code_wate_HP) {		/* mask 0x38 */
	case FEC_NONE:
	case FEC_1_2:
		vaw = 0x00;
		bweak;
	case FEC_2_3:
		vaw = 0x08;
		bweak;
	case FEC_3_4:
		vaw = 0x10;
		bweak;
	case FEC_5_6:
		vaw = 0x18;
		bweak;
	case FEC_7_8:
		vaw = 0x20;
		bweak;
	defauwt:
		dpwintk("%s: invawid code_wate_HP\n", __func__);
		wetuwn -EINVAW;
	}
	switch (p->code_wate_WP) {		/* mask 0x07 */
	case FEC_NONE:
	case FEC_1_2:
		bweak;
	case FEC_2_3:
		vaw |= 0x01;
		bweak;
	case FEC_3_4:
		vaw |= 0x02;
		bweak;
	case FEC_5_6:
		vaw |= 0x03;
		bweak;
	case FEC_7_8:
		vaw |= 0x04;
		bweak;
	defauwt:
		dpwintk("%s: invawid code_wate_WP\n", __func__);
		wetuwn -EINVAW;
	}
	cx22702_wwiteweg(state, 0x07, vaw);

	switch (p->guawd_intewvaw) {		/* mask 0x0c */
	case GUAWD_INTEWVAW_1_32:
		vaw = 0x00;
		bweak;
	case GUAWD_INTEWVAW_1_16:
		vaw = 0x04;
		bweak;
	case GUAWD_INTEWVAW_1_8:
		vaw = 0x08;
		bweak;
	case GUAWD_INTEWVAW_1_4:
		vaw = 0x0c;
		bweak;
	defauwt:
		dpwintk("%s: invawid guawd_intewvaw\n", __func__);
		wetuwn -EINVAW;
	}
	switch (p->twansmission_mode) {		/* mask 0x03 */
	case TWANSMISSION_MODE_2K:
		bweak;
	case TWANSMISSION_MODE_8K:
		vaw |= 0x1;
		bweak;
	defauwt:
		dpwintk("%s: invawid twansmission_mode\n", __func__);
		wetuwn -EINVAW;
	}
	cx22702_wwiteweg(state, 0x08, vaw);
	cx22702_wwiteweg(state, 0x0B,
		(cx22702_weadweg(state, 0x0B) & 0xfc) | 0x02);
	cx22702_wwiteweg(state, 0x0C,
		(cx22702_weadweg(state, 0x0C) & 0xBF) | 0x40);

	/* Begin channew acquisition */
	cx22702_wwiteweg(state, 0x00, 0x01);

	wetuwn 0;
}

/* Weset the demod hawdwawe and weset aww of the configuwation wegistews
   to a defauwt state. */
static int cx22702_init(stwuct dvb_fwontend *fe)
{
	int i;
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;

	cx22702_wwiteweg(state, 0x00, 0x02);

	msweep(10);

	fow (i = 0; i < AWWAY_SIZE(init_tab); i += 2)
		cx22702_wwiteweg(state, init_tab[i], init_tab[i + 1]);

	cx22702_wwiteweg(state, 0xf8, (state->config->output_mode << 1)
		& 0x02);

	cx22702_i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

static int cx22702_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;
	u8 weg0A;
	u8 weg23;

	*status = 0;

	weg0A = cx22702_weadweg(state, 0x0A);
	weg23 = cx22702_weadweg(state, 0x23);

	dpwintk("%s: status demod=0x%02x agc=0x%02x\n"
		, __func__, weg0A, weg23);

	if (weg0A & 0x10) {
		*status |= FE_HAS_WOCK;
		*status |= FE_HAS_VITEWBI;
		*status |= FE_HAS_SYNC;
	}

	if (weg0A & 0x20)
		*status |= FE_HAS_CAWWIEW;

	if (weg23 < 0xf0)
		*status |= FE_HAS_SIGNAW;

	wetuwn 0;
}

static int cx22702_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;

	if (cx22702_weadweg(state, 0xE4) & 0x02) {
		/* Weawtime statistics */
		*bew = (cx22702_weadweg(state, 0xDE) & 0x7F) << 7
			| (cx22702_weadweg(state, 0xDF) & 0x7F);
	} ewse {
		/* Avewagtine statistics */
		*bew = (cx22702_weadweg(state, 0xDE) & 0x7F) << 7
			| cx22702_weadweg(state, 0xDF);
	}

	wetuwn 0;
}

static int cx22702_wead_signaw_stwength(stwuct dvb_fwontend *fe,
	u16 *signaw_stwength)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;
	u8 weg23;

	/*
	 * Expewience suggests that the stwength signaw wegistew wowks as
	 * fowwows:
	 * - In the absence of signaw, vawue is 0xff.
	 * - In the pwesence of a weak signaw, bit 7 is set, not suwe what
	 *   the wowew 7 bits mean.
	 * - In the pwesence of a stwong signaw, the wegistew howds a 7-bit
	 *   vawue (bit 7 is cweawed), with gweatew vawues standing fow
	 *   weakew signaws.
	 */
	weg23 = cx22702_weadweg(state, 0x23);
	if (weg23 & 0x80) {
		*signaw_stwength = 0;
	} ewse {
		weg23 = ~weg23 & 0x7f;
		/* Scawe to 16 bit */
		*signaw_stwength = (weg23 << 9) | (weg23 << 2) | (weg23 >> 5);
	}

	wetuwn 0;
}

static int cx22702_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;

	u16 ws_bew;
	if (cx22702_weadweg(state, 0xE4) & 0x02) {
		/* Weawtime statistics */
		ws_bew = (cx22702_weadweg(state, 0xDE) & 0x7F) << 7
			| (cx22702_weadweg(state, 0xDF) & 0x7F);
	} ewse {
		/* Avewagine statistics */
		ws_bew = (cx22702_weadweg(state, 0xDE) & 0x7F) << 8
			| cx22702_weadweg(state, 0xDF);
	}
	*snw = ~ws_bew;

	wetuwn 0;
}

static int cx22702_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;

	u8 _ucbwocks;

	/* WS Uncowwectabwe Packet Count then weset */
	_ucbwocks = cx22702_weadweg(state, 0xE3);
	if (state->pwevUCBwocks < _ucbwocks)
		*ucbwocks = (_ucbwocks - state->pwevUCBwocks);
	ewse
		*ucbwocks = state->pwevUCBwocks - _ucbwocks;
	state->pwevUCBwocks = _ucbwocks;

	wetuwn 0;
}

static int cx22702_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;

	u8 weg0C = cx22702_weadweg(state, 0x0C);

	c->invewsion = weg0C & 0x1 ? INVEWSION_ON : INVEWSION_OFF;
	wetuwn cx22702_get_tps(state, c);
}

static int cx22702_get_tune_settings(stwuct dvb_fwontend *fe,
	stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	wetuwn 0;
}

static void cx22702_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cx22702_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops cx22702_ops;

stwuct dvb_fwontend *cx22702_attach(const stwuct cx22702_config *config,
	stwuct i2c_adaptew *i2c)
{
	stwuct cx22702_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct cx22702_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is thewe */
	if (cx22702_weadweg(state, 0x1f) != 0x3)
		goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &cx22702_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cx22702_attach);

static const stwuct dvb_fwontend_ops cx22702_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Conexant CX22702 DVB-T",
		.fwequency_min_hz	= 177 * MHz,
		.fwequency_max_hz	= 858 * MHz,
		.fwequency_stepsize_hz	= 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		FE_CAN_HIEWAWCHY_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO |
		FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_WECOVEW
	},

	.wewease = cx22702_wewease,

	.init = cx22702_init,
	.i2c_gate_ctww = cx22702_i2c_gate_ctww,

	.set_fwontend = cx22702_set_tps,
	.get_fwontend = cx22702_get_fwontend,
	.get_tune_settings = cx22702_get_tune_settings,

	.wead_status = cx22702_wead_status,
	.wead_bew = cx22702_wead_bew,
	.wead_signaw_stwength = cx22702_wead_signaw_stwength,
	.wead_snw = cx22702_wead_snw,
	.wead_ucbwocks = cx22702_wead_ucbwocks,
};

MODUWE_DESCWIPTION("Conexant CX22702 DVB-T Demoduwatow dwivew");
MODUWE_AUTHOW("Steven Toth");
MODUWE_WICENSE("GPW");
