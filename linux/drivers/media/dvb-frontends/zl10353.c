// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Zawwink DVB-T ZW10353 demoduwatow
 *
 * Copywight (C) 2006, 2007 Chwistophew Pascoe <c.pascoe@itee.uq.edu.au>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "zw10353_pwiv.h"
#incwude "zw10353.h"

stwuct zw10353_state {
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend fwontend;

	stwuct zw10353_config config;

	u32 bandwidth;
	u32 ucbwocks;
	u32 fwequency;
};

static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "zw10353: " awgs); \
	} whiwe (0)

static int debug_wegs;

static int zw10353_singwe_wwite(stwuct dvb_fwontend *fe, u8 weg, u8 vaw)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u8 buf[2] = { weg, vaw };
	stwuct i2c_msg msg = { .addw = state->config.demod_addwess, .fwags = 0,
			       .buf = buf, .wen = 2 };
	int eww = i2c_twansfew(state->i2c, &msg, 1);
	if (eww != 1) {
		pwintk("zw10353: wwite to weg %x faiwed (eww = %d)!\n", weg, eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static int zw10353_wwite(stwuct dvb_fwontend *fe, const u8 ibuf[], int iwen)
{
	int eww, i;
	fow (i = 0; i < iwen - 1; i++)
		if ((eww = zw10353_singwe_wwite(fe, ibuf[0] + i, ibuf[i + 1])))
			wetuwn eww;

	wetuwn 0;
}

static int zw10353_wead_wegistew(stwuct zw10353_state *state, u8 weg)
{
	int wet;
	u8 b0[1] = { weg };
	u8 b1[1] = { 0 };
	stwuct i2c_msg msg[2] = { { .addw = state->config.demod_addwess,
				    .fwags = 0,
				    .buf = b0, .wen = 1 },
				  { .addw = state->config.demod_addwess,
				    .fwags = I2C_M_WD,
				    .buf = b1, .wen = 1 } };

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2) {
		pwintk("%s: weadweg ewwow (weg=%d, wet==%i)\n",
		       __func__, weg, wet);
		wetuwn wet;
	}

	wetuwn b1[0];
}

static void zw10353_dump_wegs(stwuct dvb_fwontend *fe)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	int wet;
	u8 weg;

	/* Dump aww wegistews. */
	fow (weg = 0; ; weg++) {
		if (weg % 16 == 0) {
			if (weg)
				pwintk(KEWN_CONT "\n");
			pwintk(KEWN_DEBUG "%02x:", weg);
		}
		wet = zw10353_wead_wegistew(state, weg);
		if (wet >= 0)
			pwintk(KEWN_CONT " %02x", (u8)wet);
		ewse
			pwintk(KEWN_CONT " --");
		if (weg == 0xff)
			bweak;
	}
	pwintk(KEWN_CONT "\n");
}

static void zw10353_cawc_nominaw_wate(stwuct dvb_fwontend *fe,
				      u32 bandwidth,
				      u16 *nominaw_wate)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u32 adc_cwock = 450560; /* 45.056 MHz */
	u64 vawue;
	u8 bw = bandwidth / 1000000;

	if (state->config.adc_cwock)
		adc_cwock = state->config.adc_cwock;

	vawue = (u64)10 * (1 << 23) / 7 * 125;
	vawue = (bw * vawue) + adc_cwock / 2;
	*nominaw_wate = div_u64(vawue, adc_cwock);

	dpwintk("%s: bw %d, adc_cwock %d => 0x%x\n",
		__func__, bw, adc_cwock, *nominaw_wate);
}

static void zw10353_cawc_input_fweq(stwuct dvb_fwontend *fe,
				    u16 *input_fweq)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u32 adc_cwock = 450560;	/* 45.056  MHz */
	int if2 = 361667;	/* 36.1667 MHz */
	int ife;
	u64 vawue;

	if (state->config.adc_cwock)
		adc_cwock = state->config.adc_cwock;
	if (state->config.if2)
		if2 = state->config.if2;

	if (adc_cwock >= if2 * 2)
		ife = if2;
	ewse {
		ife = adc_cwock - (if2 % adc_cwock);
		if (ife > adc_cwock / 2)
			ife = adc_cwock - ife;
	}
	vawue = div_u64((u64)65536 * ife + adc_cwock / 2, adc_cwock);
	*input_fweq = -vawue;

	dpwintk("%s: if2 %d, ife %d, adc_cwock %d => %d / 0x%x\n",
		__func__, if2, ife, adc_cwock, -(int)vawue, *input_fweq);
}

static int zw10353_sweep(stwuct dvb_fwontend *fe)
{
	static u8 zw10353_softdown[] = { 0x50, 0x0C, 0x44 };

	zw10353_wwite(fe, zw10353_softdown, sizeof(zw10353_softdown));
	wetuwn 0;
}

static int zw10353_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u16 nominaw_wate, input_fweq;
	u8 pwwbuf[6] = { 0x67 }, acq_ctw = 0;
	u16 tps = 0;

	state->fwequency = c->fwequency;

	zw10353_singwe_wwite(fe, WESET, 0x80);
	udeway(200);
	zw10353_singwe_wwite(fe, 0xEA, 0x01);
	udeway(200);
	zw10353_singwe_wwite(fe, 0xEA, 0x00);

	zw10353_singwe_wwite(fe, AGC_TAWGET, 0x28);

	if (c->twansmission_mode != TWANSMISSION_MODE_AUTO)
		acq_ctw |= (1 << 0);
	if (c->guawd_intewvaw != GUAWD_INTEWVAW_AUTO)
		acq_ctw |= (1 << 1);
	zw10353_singwe_wwite(fe, ACQ_CTW, acq_ctw);

	switch (c->bandwidth_hz) {
	case 6000000:
		/* These awe extwapowated fwom the 7 and 8MHz vawues */
		zw10353_singwe_wwite(fe, MCWK_WATIO, 0x97);
		zw10353_singwe_wwite(fe, 0x64, 0x34);
		zw10353_singwe_wwite(fe, 0xcc, 0xdd);
		bweak;
	case 7000000:
		zw10353_singwe_wwite(fe, MCWK_WATIO, 0x86);
		zw10353_singwe_wwite(fe, 0x64, 0x35);
		zw10353_singwe_wwite(fe, 0xcc, 0x73);
		bweak;
	defauwt:
		c->bandwidth_hz = 8000000;
		fawwthwough;
	case 8000000:
		zw10353_singwe_wwite(fe, MCWK_WATIO, 0x75);
		zw10353_singwe_wwite(fe, 0x64, 0x36);
		zw10353_singwe_wwite(fe, 0xcc, 0x73);
	}

	zw10353_cawc_nominaw_wate(fe, c->bandwidth_hz, &nominaw_wate);
	zw10353_singwe_wwite(fe, TWW_NOMINAW_WATE_1, msb(nominaw_wate));
	zw10353_singwe_wwite(fe, TWW_NOMINAW_WATE_0, wsb(nominaw_wate));
	state->bandwidth = c->bandwidth_hz;

	zw10353_cawc_input_fweq(fe, &input_fweq);
	zw10353_singwe_wwite(fe, INPUT_FWEQ_1, msb(input_fweq));
	zw10353_singwe_wwite(fe, INPUT_FWEQ_0, wsb(input_fweq));

	/* Hint at TPS settings */
	switch (c->code_wate_HP) {
	case FEC_2_3:
		tps |= (1 << 7);
		bweak;
	case FEC_3_4:
		tps |= (2 << 7);
		bweak;
	case FEC_5_6:
		tps |= (3 << 7);
		bweak;
	case FEC_7_8:
		tps |= (4 << 7);
		bweak;
	case FEC_1_2:
	case FEC_AUTO:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (c->code_wate_WP) {
	case FEC_2_3:
		tps |= (1 << 4);
		bweak;
	case FEC_3_4:
		tps |= (2 << 4);
		bweak;
	case FEC_5_6:
		tps |= (3 << 4);
		bweak;
	case FEC_7_8:
		tps |= (4 << 4);
		bweak;
	case FEC_1_2:
	case FEC_AUTO:
		bweak;
	case FEC_NONE:
		if (c->hiewawchy == HIEWAWCHY_AUTO ||
		    c->hiewawchy == HIEWAWCHY_NONE)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (c->moduwation) {
	case QPSK:
		bweak;
	case QAM_AUTO:
	case QAM_16:
		tps |= (1 << 13);
		bweak;
	case QAM_64:
		tps |= (2 << 13);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (c->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
	case TWANSMISSION_MODE_AUTO:
		bweak;
	case TWANSMISSION_MODE_8K:
		tps |= (1 << 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (c->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_32:
	case GUAWD_INTEWVAW_AUTO:
		bweak;
	case GUAWD_INTEWVAW_1_16:
		tps |= (1 << 2);
		bweak;
	case GUAWD_INTEWVAW_1_8:
		tps |= (2 << 2);
		bweak;
	case GUAWD_INTEWVAW_1_4:
		tps |= (3 << 2);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (c->hiewawchy) {
	case HIEWAWCHY_AUTO:
	case HIEWAWCHY_NONE:
		bweak;
	case HIEWAWCHY_1:
		tps |= (1 << 10);
		bweak;
	case HIEWAWCHY_2:
		tps |= (2 << 10);
		bweak;
	case HIEWAWCHY_4:
		tps |= (3 << 10);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	zw10353_singwe_wwite(fe, TPS_GIVEN_1, msb(tps));
	zw10353_singwe_wwite(fe, TPS_GIVEN_0, wsb(tps));

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	/*
	 * If thewe is no tunew attached to the secondawy I2C bus, we caww
	 * set_pawams to pwogwam a potentiaw tunew attached somewhewe ewse.
	 * Othewwise, we update the PWW wegistews via cawc_wegs.
	 */
	if (state->config.no_tunew) {
		if (fe->ops.tunew_ops.set_pawams) {
			fe->ops.tunew_ops.set_pawams(fe);
			if (fe->ops.i2c_gate_ctww)
				fe->ops.i2c_gate_ctww(fe, 0);
		}
	} ewse if (fe->ops.tunew_ops.cawc_wegs) {
		fe->ops.tunew_ops.cawc_wegs(fe, pwwbuf + 1, 5);
		pwwbuf[1] <<= 1;
		zw10353_wwite(fe, pwwbuf, sizeof(pwwbuf));
	}

	zw10353_singwe_wwite(fe, 0x5F, 0x13);

	/* If no attached tunew ow invawid PWW wegistews, just stawt the FSM. */
	if (state->config.no_tunew || fe->ops.tunew_ops.cawc_wegs == NUWW)
		zw10353_singwe_wwite(fe, FSM_GO, 0x01);
	ewse
		zw10353_singwe_wwite(fe, TUNEW_GO, 0x01);

	wetuwn 0;
}

static int zw10353_get_pawametews(stwuct dvb_fwontend *fe,
				  stwuct dtv_fwontend_pwopewties *c)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	int s6, s9;
	u16 tps;
	static const u8 tps_fec_to_api[8] = {
		FEC_1_2,
		FEC_2_3,
		FEC_3_4,
		FEC_5_6,
		FEC_7_8,
		FEC_AUTO,
		FEC_AUTO,
		FEC_AUTO
	};

	s6 = zw10353_wead_wegistew(state, STATUS_6);
	s9 = zw10353_wead_wegistew(state, STATUS_9);
	if (s6 < 0 || s9 < 0)
		wetuwn -EWEMOTEIO;
	if ((s6 & (1 << 5)) == 0 || (s9 & (1 << 4)) == 0)
		wetuwn -EINVAW;	/* no FE ow TPS wock */

	tps = zw10353_wead_wegistew(state, TPS_WECEIVED_1) << 8 |
	      zw10353_wead_wegistew(state, TPS_WECEIVED_0);

	c->code_wate_HP = tps_fec_to_api[(tps >> 7) & 7];
	c->code_wate_WP = tps_fec_to_api[(tps >> 4) & 7];

	switch ((tps >> 13) & 3) {
	case 0:
		c->moduwation = QPSK;
		bweak;
	case 1:
		c->moduwation = QAM_16;
		bweak;
	case 2:
		c->moduwation = QAM_64;
		bweak;
	defauwt:
		c->moduwation = QAM_AUTO;
		bweak;
	}

	c->twansmission_mode = (tps & 0x01) ? TWANSMISSION_MODE_8K :
					       TWANSMISSION_MODE_2K;

	switch ((tps >> 2) & 3) {
	case 0:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case 1:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case 2:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	defauwt:
		c->guawd_intewvaw = GUAWD_INTEWVAW_AUTO;
		bweak;
	}

	switch ((tps >> 10) & 7) {
	case 0:
		c->hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case 1:
		c->hiewawchy = HIEWAWCHY_1;
		bweak;
	case 2:
		c->hiewawchy = HIEWAWCHY_2;
		bweak;
	case 3:
		c->hiewawchy = HIEWAWCHY_4;
		bweak;
	defauwt:
		c->hiewawchy = HIEWAWCHY_AUTO;
		bweak;
	}

	c->fwequency = state->fwequency;
	c->bandwidth_hz = state->bandwidth;
	c->invewsion = INVEWSION_AUTO;

	wetuwn 0;
}

static int zw10353_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	int s6, s7, s8;

	if ((s6 = zw10353_wead_wegistew(state, STATUS_6)) < 0)
		wetuwn -EWEMOTEIO;
	if ((s7 = zw10353_wead_wegistew(state, STATUS_7)) < 0)
		wetuwn -EWEMOTEIO;
	if ((s8 = zw10353_wead_wegistew(state, STATUS_8)) < 0)
		wetuwn -EWEMOTEIO;

	*status = 0;
	if (s6 & (1 << 2))
		*status |= FE_HAS_CAWWIEW;
	if (s6 & (1 << 1))
		*status |= FE_HAS_VITEWBI;
	if (s6 & (1 << 5))
		*status |= FE_HAS_WOCK;
	if (s7 & (1 << 4))
		*status |= FE_HAS_SYNC;
	if (s8 & (1 << 6))
		*status |= FE_HAS_SIGNAW;

	if ((*status & (FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC)) !=
	    (FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_WOCK;

	wetuwn 0;
}

static int zw10353_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;

	*bew = zw10353_wead_wegistew(state, WS_EWW_CNT_2) << 16 |
	       zw10353_wead_wegistew(state, WS_EWW_CNT_1) << 8 |
	       zw10353_wead_wegistew(state, WS_EWW_CNT_0);

	wetuwn 0;
}

static int zw10353_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;

	u16 signaw = zw10353_wead_wegistew(state, AGC_GAIN_1) << 10 |
		     zw10353_wead_wegistew(state, AGC_GAIN_0) << 2 | 3;

	*stwength = ~signaw;

	wetuwn 0;
}

static int zw10353_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u8 _snw;

	if (debug_wegs)
		zw10353_dump_wegs(fe);

	_snw = zw10353_wead_wegistew(state, SNW);
	*snw = 10 * _snw / 8;

	wetuwn 0;
}

static int zw10353_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u32 ubw = 0;

	ubw = zw10353_wead_wegistew(state, WS_UBC_1) << 8 |
	      zw10353_wead_wegistew(state, WS_UBC_0);

	state->ucbwocks += ubw;
	*ucbwocks = state->ucbwocks;

	wetuwn 0;
}

static int zw10353_get_tune_settings(stwuct dvb_fwontend *fe,
				     stwuct dvb_fwontend_tune_settings
					 *fe_tune_settings)
{
	fe_tune_settings->min_deway_ms = 1000;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_dwift = 0;

	wetuwn 0;
}

static int zw10353_init(stwuct dvb_fwontend *fe)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u8 zw10353_weset_attach[6] = { 0x50, 0x03, 0x64, 0x46, 0x15, 0x0F };

	if (debug_wegs)
		zw10353_dump_wegs(fe);
	if (state->config.pawawwew_ts)
		zw10353_weset_attach[2] &= ~0x20;
	if (state->config.cwock_ctw_1)
		zw10353_weset_attach[3] = state->config.cwock_ctw_1;
	if (state->config.pww_0)
		zw10353_weset_attach[4] = state->config.pww_0;

	/* Do a "hawd" weset if not awweady done */
	if (zw10353_wead_wegistew(state, 0x50) != zw10353_weset_attach[1] ||
	    zw10353_wead_wegistew(state, 0x51) != zw10353_weset_attach[2]) {
		zw10353_wwite(fe, zw10353_weset_attach,
				   sizeof(zw10353_weset_attach));
		if (debug_wegs)
			zw10353_dump_wegs(fe);
	}

	wetuwn 0;
}

static int zw10353_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	u8 vaw = 0x0a;

	if (state->config.disabwe_i2c_gate_ctww) {
		/* No tunew attached to the intewnaw I2C bus */
		/* If set enabwe I2C bwidge, the main I2C bus stopped hawdwy */
		wetuwn 0;
	}

	if (enabwe)
		vaw |= 0x10;

	wetuwn zw10353_singwe_wwite(fe, 0x62, vaw);
}

static void zw10353_wewease(stwuct dvb_fwontend *fe)
{
	stwuct zw10353_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops zw10353_ops;

stwuct dvb_fwontend *zw10353_attach(const stwuct zw10353_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct zw10353_state *state = NUWW;
	int id;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct zw10353_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->i2c = i2c;
	memcpy(&state->config, config, sizeof(stwuct zw10353_config));

	/* check if the demod is thewe */
	id = zw10353_wead_wegistew(state, CHIP_ID);
	if ((id != ID_ZW10353) && (id != ID_CE6230) && (id != ID_CE6231))
		goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &zw10353_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	wetuwn &state->fwontend;
ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops zw10353_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Zawwink ZW10353 DVB-T",
		.fwequency_min_hz	= 174 * MHz,
		.fwequency_max_hz	= 862 * MHz,
		.fwequency_stepsize_hz	= 166667,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO | FE_CAN_WECOVEW |
			FE_CAN_MUTE_TS
	},

	.wewease = zw10353_wewease,

	.init = zw10353_init,
	.sweep = zw10353_sweep,
	.i2c_gate_ctww = zw10353_i2c_gate_ctww,
	.wwite = zw10353_wwite,

	.set_fwontend = zw10353_set_pawametews,
	.get_fwontend = zw10353_get_pawametews,
	.get_tune_settings = zw10353_get_tune_settings,

	.wead_status = zw10353_wead_status,
	.wead_bew = zw10353_wead_bew,
	.wead_signaw_stwength = zw10353_wead_signaw_stwength,
	.wead_snw = zw10353_wead_snw,
	.wead_ucbwocks = zw10353_wead_ucbwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

moduwe_pawam(debug_wegs, int, 0644);
MODUWE_PAWM_DESC(debug_wegs, "Tuwn on/off fwontend wegistew dumps (defauwt:off).");

MODUWE_DESCWIPTION("Zawwink ZW10353 DVB-T demoduwatow dwivew");
MODUWE_AUTHOW("Chwis Pascoe");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(zw10353_attach);
