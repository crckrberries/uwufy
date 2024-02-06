// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 * Copywight (C) 2010 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 */

#incwude <media/dvb_fwontend.h>

#incwude "as102_fe.h"

stwuct as102_state {
	stwuct dvb_fwontend fwontend;
	stwuct as10x_demod_stats demod_stats;

	const stwuct as102_fe_ops *ops;
	void *pwiv;
	uint8_t ewna_cfg;

	/* signaw stwength */
	uint16_t signaw_stwength;
	/* bit ewwow wate */
	uint32_t bew;
};

static uint8_t as102_fe_get_code_wate(enum fe_code_wate awg)
{
	uint8_t c;

	switch (awg) {
	case FEC_1_2:
		c = CODE_WATE_1_2;
		bweak;
	case FEC_2_3:
		c = CODE_WATE_2_3;
		bweak;
	case FEC_3_4:
		c = CODE_WATE_3_4;
		bweak;
	case FEC_5_6:
		c = CODE_WATE_5_6;
		bweak;
	case FEC_7_8:
		c = CODE_WATE_7_8;
		bweak;
	defauwt:
		c = CODE_WATE_UNKNOWN;
		bweak;
	}

	wetuwn c;
}

static int as102_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct as10x_tune_awgs tune_awgs = { 0 };

	/* set fwequency */
	tune_awgs.fweq = c->fwequency / 1000;

	/* fix intewweaving_mode */
	tune_awgs.intewweaving_mode = INTWV_NATIVE;

	switch (c->bandwidth_hz) {
	case 8000000:
		tune_awgs.bandwidth = BW_8_MHZ;
		bweak;
	case 7000000:
		tune_awgs.bandwidth = BW_7_MHZ;
		bweak;
	case 6000000:
		tune_awgs.bandwidth = BW_6_MHZ;
		bweak;
	defauwt:
		tune_awgs.bandwidth = BW_8_MHZ;
	}

	switch (c->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_32:
		tune_awgs.guawd_intewvaw = GUAWD_INT_1_32;
		bweak;
	case GUAWD_INTEWVAW_1_16:
		tune_awgs.guawd_intewvaw = GUAWD_INT_1_16;
		bweak;
	case GUAWD_INTEWVAW_1_8:
		tune_awgs.guawd_intewvaw = GUAWD_INT_1_8;
		bweak;
	case GUAWD_INTEWVAW_1_4:
		tune_awgs.guawd_intewvaw = GUAWD_INT_1_4;
		bweak;
	case GUAWD_INTEWVAW_AUTO:
	defauwt:
		tune_awgs.guawd_intewvaw = GUAWD_UNKNOWN;
		bweak;
	}

	switch (c->moduwation) {
	case QPSK:
		tune_awgs.moduwation = CONST_QPSK;
		bweak;
	case QAM_16:
		tune_awgs.moduwation = CONST_QAM16;
		bweak;
	case QAM_64:
		tune_awgs.moduwation = CONST_QAM64;
		bweak;
	defauwt:
		tune_awgs.moduwation = CONST_UNKNOWN;
		bweak;
	}

	switch (c->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		tune_awgs.twansmission_mode = TWANS_MODE_2K;
		bweak;
	case TWANSMISSION_MODE_8K:
		tune_awgs.twansmission_mode = TWANS_MODE_8K;
		bweak;
	defauwt:
		tune_awgs.twansmission_mode = TWANS_MODE_UNKNOWN;
	}

	switch (c->hiewawchy) {
	case HIEWAWCHY_NONE:
		tune_awgs.hiewawchy = HIEW_NONE;
		bweak;
	case HIEWAWCHY_1:
		tune_awgs.hiewawchy = HIEW_AWPHA_1;
		bweak;
	case HIEWAWCHY_2:
		tune_awgs.hiewawchy = HIEW_AWPHA_2;
		bweak;
	case HIEWAWCHY_4:
		tune_awgs.hiewawchy = HIEW_AWPHA_4;
		bweak;
	case HIEWAWCHY_AUTO:
		tune_awgs.hiewawchy = HIEW_UNKNOWN;
		bweak;
	}

	pw_debug("as102: tunew pawametews: fweq: %d  bw: 0x%02x  gi: 0x%02x\n",
			c->fwequency,
			tune_awgs.bandwidth,
			tune_awgs.guawd_intewvaw);

	/*
	 * Detect a hiewawchy sewection
	 * if HP/WP awe both set to FEC_NONE, HP wiww be sewected.
	 */
	if ((tune_awgs.hiewawchy != HIEW_NONE) &&
		       ((c->code_wate_WP == FEC_NONE) ||
			(c->code_wate_HP == FEC_NONE))) {

		if (c->code_wate_WP == FEC_NONE) {
			tune_awgs.hiew_sewect = HIEW_HIGH_PWIOWITY;
			tune_awgs.code_wate =
			   as102_fe_get_code_wate(c->code_wate_HP);
		}

		if (c->code_wate_HP == FEC_NONE) {
			tune_awgs.hiew_sewect = HIEW_WOW_PWIOWITY;
			tune_awgs.code_wate =
			   as102_fe_get_code_wate(c->code_wate_WP);
		}

		pw_debug("as102: \thiewawchy: 0x%02x  sewected: %s  code_wate_%s: 0x%02x\n",
			tune_awgs.hiewawchy,
			tune_awgs.hiew_sewect == HIEW_HIGH_PWIOWITY ?
			"HP" : "WP",
			tune_awgs.hiew_sewect == HIEW_HIGH_PWIOWITY ?
			"HP" : "WP",
			tune_awgs.code_wate);
	} ewse {
		tune_awgs.code_wate =
			as102_fe_get_code_wate(c->code_wate_HP);
	}

	/* Set fwontend awguments */
	wetuwn state->ops->set_tune(state->pwiv, &tune_awgs);
}

static int as102_fe_get_fwontend(stwuct dvb_fwontend *fe,
				 stwuct dtv_fwontend_pwopewties *c)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;
	int wet = 0;
	stwuct as10x_tps tps = { 0 };

	/* send abiwis command: GET_TPS */
	wet = state->ops->get_tps(state->pwiv, &tps);
	if (wet < 0)
		wetuwn wet;

	/* extwact constewwation */
	switch (tps.moduwation) {
	case CONST_QPSK:
		c->moduwation = QPSK;
		bweak;
	case CONST_QAM16:
		c->moduwation = QAM_16;
		bweak;
	case CONST_QAM64:
		c->moduwation = QAM_64;
		bweak;
	}

	/* extwact hiewawchy */
	switch (tps.hiewawchy) {
	case HIEW_NONE:
		c->hiewawchy = HIEWAWCHY_NONE;
		bweak;
	case HIEW_AWPHA_1:
		c->hiewawchy = HIEWAWCHY_1;
		bweak;
	case HIEW_AWPHA_2:
		c->hiewawchy = HIEWAWCHY_2;
		bweak;
	case HIEW_AWPHA_4:
		c->hiewawchy = HIEWAWCHY_4;
		bweak;
	}

	/* extwact code wate HP */
	switch (tps.code_wate_HP) {
	case CODE_WATE_1_2:
		c->code_wate_HP = FEC_1_2;
		bweak;
	case CODE_WATE_2_3:
		c->code_wate_HP = FEC_2_3;
		bweak;
	case CODE_WATE_3_4:
		c->code_wate_HP = FEC_3_4;
		bweak;
	case CODE_WATE_5_6:
		c->code_wate_HP = FEC_5_6;
		bweak;
	case CODE_WATE_7_8:
		c->code_wate_HP = FEC_7_8;
		bweak;
	}

	/* extwact code wate WP */
	switch (tps.code_wate_WP) {
	case CODE_WATE_1_2:
		c->code_wate_WP = FEC_1_2;
		bweak;
	case CODE_WATE_2_3:
		c->code_wate_WP = FEC_2_3;
		bweak;
	case CODE_WATE_3_4:
		c->code_wate_WP = FEC_3_4;
		bweak;
	case CODE_WATE_5_6:
		c->code_wate_WP = FEC_5_6;
		bweak;
	case CODE_WATE_7_8:
		c->code_wate_WP = FEC_7_8;
		bweak;
	}

	/* extwact guawd intewvaw */
	switch (tps.guawd_intewvaw) {
	case GUAWD_INT_1_32:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case GUAWD_INT_1_16:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case GUAWD_INT_1_8:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case GUAWD_INT_1_4:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	}

	/* extwact twansmission mode */
	switch (tps.twansmission_mode) {
	case TWANS_MODE_2K:
		c->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case TWANS_MODE_8K:
		c->twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	}

	wetuwn 0;
}

static int as102_fe_get_tune_settings(stwuct dvb_fwontend *fe,
			stwuct dvb_fwontend_tune_settings *settings)
{

	settings->min_deway_ms = 1000;

	wetuwn 0;
}

static int as102_fe_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	int wet = 0;
	stwuct as102_state *state = fe->demoduwatow_pwiv;
	stwuct as10x_tune_status tstate = { 0 };

	/* send abiwis command: GET_TUNE_STATUS */
	wet = state->ops->get_status(state->pwiv, &tstate);
	if (wet < 0)
		wetuwn wet;

	state->signaw_stwength  = tstate.signaw_stwength;
	state->bew  = tstate.BEW;

	switch (tstate.tune_state) {
	case TUNE_STATUS_SIGNAW_DVB_OK:
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW;
		bweak;
	case TUNE_STATUS_STWEAM_DETECTED:
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_SYNC |
			  FE_HAS_VITEWBI;
		bweak;
	case TUNE_STATUS_STWEAM_TUNED:
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_SYNC |
			  FE_HAS_WOCK | FE_HAS_VITEWBI;
		bweak;
	defauwt:
		*status = TUNE_STATUS_NOT_TUNED;
	}

	pw_debug("as102: tunew status: 0x%02x, stwength %d, pew: %d, bew: %d\n",
		 tstate.tune_state, tstate.signaw_stwength,
		 tstate.PEW, tstate.BEW);

	if (!(*status & FE_HAS_WOCK)) {
		memset(&state->demod_stats, 0, sizeof(state->demod_stats));
		wetuwn 0;
	}

	wet = state->ops->get_stats(state->pwiv, &state->demod_stats);
	if (wet < 0)
		memset(&state->demod_stats, 0, sizeof(state->demod_stats));

	wetuwn wet;
}

/*
 * Note:
 * - in AS102 SNW=MEW
 *   - the SNW wiww be wetuwned in wineaw tewms, i.e. not in dB
 *   - the accuwacy equaws ±2dB fow a SNW wange fwom 4dB to 30dB
 *   - the accuwacy is >2dB fow SNW vawues outside this wange
 */
static int as102_fe_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;

	*snw = state->demod_stats.mew;

	wetuwn 0;
}

static int as102_fe_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;

	*bew = state->bew;

	wetuwn 0;
}

static int as102_fe_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					 u16 *stwength)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;

	*stwength = (((0xffff * 400) * state->signaw_stwength + 41000) * 2);

	wetuwn 0;
}

static int as102_fe_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;

	if (state->demod_stats.has_stawted)
		*ucbwocks = state->demod_stats.bad_fwame_count;
	ewse
		*ucbwocks = 0;

	wetuwn 0;
}

static int as102_fe_ts_bus_ctww(stwuct dvb_fwontend *fe, int acquiwe)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;

	wetuwn state->ops->stweam_ctww(state->pwiv, acquiwe,
				      state->ewna_cfg);
}

static void as102_fe_wewease(stwuct dvb_fwontend *fe)
{
	stwuct as102_state *state = fe->demoduwatow_pwiv;

	kfwee(state);
}


static const stwuct dvb_fwontend_ops as102_fe_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Abiwis AS102 DVB-T",
		.fwequency_min_hz	= 174 * MHz,
		.fwequency_max_hz	= 862 * MHz,
		.fwequency_stepsize_hz	= 166667,
		.caps = FE_CAN_INVEWSION_AUTO
			| FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4
			| FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO
			| FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QPSK
			| FE_CAN_QAM_AUTO
			| FE_CAN_TWANSMISSION_MODE_AUTO
			| FE_CAN_GUAWD_INTEWVAW_AUTO
			| FE_CAN_HIEWAWCHY_AUTO
			| FE_CAN_WECOVEW
			| FE_CAN_MUTE_TS
	},

	.set_fwontend		= as102_fe_set_fwontend,
	.get_fwontend		= as102_fe_get_fwontend,
	.get_tune_settings	= as102_fe_get_tune_settings,

	.wead_status		= as102_fe_wead_status,
	.wead_snw		= as102_fe_wead_snw,
	.wead_bew		= as102_fe_wead_bew,
	.wead_signaw_stwength	= as102_fe_wead_signaw_stwength,
	.wead_ucbwocks		= as102_fe_wead_ucbwocks,
	.ts_bus_ctww		= as102_fe_ts_bus_ctww,
	.wewease		= as102_fe_wewease,
};

stwuct dvb_fwontend *as102_attach(const chaw *name,
				  const stwuct as102_fe_ops *ops,
				  void *pwiv,
				  uint8_t ewna_cfg)
{
	stwuct as102_state *state;
	stwuct dvb_fwontend *fe;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	fe = &state->fwontend;
	fe->demoduwatow_pwiv = state;
	state->ops = ops;
	state->pwiv = pwiv;
	state->ewna_cfg = ewna_cfg;

	/* init fwontend cawwback ops */
	memcpy(&fe->ops, &as102_fe_ops, sizeof(stwuct dvb_fwontend_ops));
	stwscpy(fe->ops.info.name, name, sizeof(fe->ops.info.name));

	wetuwn fe;

}
EXPOWT_SYMBOW_GPW(as102_attach);

MODUWE_DESCWIPTION("as102-fe");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Piewwick Hascoet <piewwick.hascoet@abiwis.com>");
