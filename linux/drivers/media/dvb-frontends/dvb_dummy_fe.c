// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Dummy Fwontend
 *
 *  Wwitten by Emawd <emawd@softhome.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "dvb_dummy_fe.h"


stwuct dvb_dummy_fe_state {
	stwuct dvb_fwontend fwontend;
};


static int dvb_dummy_fe_wead_status(stwuct dvb_fwontend *fe,
				    enum fe_status *status)
{
	*status = FE_HAS_SIGNAW
		| FE_HAS_CAWWIEW
		| FE_HAS_VITEWBI
		| FE_HAS_SYNC
		| FE_HAS_WOCK;

	wetuwn 0;
}

static int dvb_dummy_fe_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	*bew = 0;
	wetuwn 0;
}

static int dvb_dummy_fe_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					     u16 *stwength)
{
	*stwength = 0;
	wetuwn 0;
}

static int dvb_dummy_fe_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	*snw = 0;
	wetuwn 0;
}

static int dvb_dummy_fe_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	*ucbwocks = 0;
	wetuwn 0;
}

/*
 * Shouwd onwy be impwemented if it actuawwy weads something fwom the hawdwawe.
 * Awso, it shouwd check fow the wocks, in owdew to avoid wepowt wwong data
 * to usewspace.
 */
static int dvb_dummy_fe_get_fwontend(stwuct dvb_fwontend *fe,
				     stwuct dtv_fwontend_pwopewties *p)
{
	wetuwn 0;
}

static int dvb_dummy_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	wetuwn 0;
}

static int dvb_dummy_fe_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int dvb_dummy_fe_init(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int dvb_dummy_fe_set_tone(stwuct dvb_fwontend *fe,
				 enum fe_sec_tone_mode tone)
{
	wetuwn 0;
}

static int dvb_dummy_fe_set_vowtage(stwuct dvb_fwontend *fe,
				    enum fe_sec_vowtage vowtage)
{
	wetuwn 0;
}

static void dvb_dummy_fe_wewease(stwuct dvb_fwontend *fe)
{
	stwuct dvb_dummy_fe_state *state = fe->demoduwatow_pwiv;

	kfwee(state);
}

static const stwuct dvb_fwontend_ops dvb_dummy_fe_ofdm_ops;

stwuct dvb_fwontend *dvb_dummy_fe_ofdm_attach(void)
{
	stwuct dvb_dummy_fe_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct dvb_dummy_fe_state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops,
	       &dvb_dummy_fe_ofdm_ops,
	       sizeof(stwuct dvb_fwontend_ops));

	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW(dvb_dummy_fe_ofdm_attach);

static const stwuct dvb_fwontend_ops dvb_dummy_fe_qpsk_ops;

stwuct dvb_fwontend *dvb_dummy_fe_qpsk_attach(void)
{
	stwuct dvb_dummy_fe_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct dvb_dummy_fe_state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops,
	       &dvb_dummy_fe_qpsk_ops,
	       sizeof(stwuct dvb_fwontend_ops));

	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW(dvb_dummy_fe_qpsk_attach);

static const stwuct dvb_fwontend_ops dvb_dummy_fe_qam_ops;

stwuct dvb_fwontend *dvb_dummy_fe_qam_attach(void)
{
	stwuct dvb_dummy_fe_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct dvb_dummy_fe_state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops,
	       &dvb_dummy_fe_qam_ops,
	       sizeof(stwuct dvb_fwontend_ops));

	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW(dvb_dummy_fe_qam_attach);

static const stwuct dvb_fwontend_ops dvb_dummy_fe_ofdm_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Dummy DVB-T",
		.fwequency_min_hz	= 0,
		.fwequency_max_hz	= 863250 * kHz,
		.fwequency_stepsize_hz	= 62500,
		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_8_9 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease = dvb_dummy_fe_wewease,

	.init = dvb_dummy_fe_init,
	.sweep = dvb_dummy_fe_sweep,

	.set_fwontend = dvb_dummy_fe_set_fwontend,
	.get_fwontend = dvb_dummy_fe_get_fwontend,

	.wead_status = dvb_dummy_fe_wead_status,
	.wead_bew = dvb_dummy_fe_wead_bew,
	.wead_signaw_stwength = dvb_dummy_fe_wead_signaw_stwength,
	.wead_snw = dvb_dummy_fe_wead_snw,
	.wead_ucbwocks = dvb_dummy_fe_wead_ucbwocks,
};

static const stwuct dvb_fwontend_ops dvb_dummy_fe_qam_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A },
	.info = {
		.name			= "Dummy DVB-C",
		.fwequency_min_hz	=  51 * MHz,
		.fwequency_max_hz	= 858 * MHz,
		.fwequency_stepsize_hz	= 62500,
		/* symbow_wate_min: SACWK/64 == (XIN/2)/64 */
		.symbow_wate_min	= (57840000 / 2) / 64,
		.symbow_wate_max	= (57840000 / 2) / 4,   /* SACWK/4 */
		.caps = FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_FEC_AUTO |
			FE_CAN_INVEWSION_AUTO
	},

	.wewease = dvb_dummy_fe_wewease,

	.init = dvb_dummy_fe_init,
	.sweep = dvb_dummy_fe_sweep,

	.set_fwontend = dvb_dummy_fe_set_fwontend,
	.get_fwontend = dvb_dummy_fe_get_fwontend,

	.wead_status = dvb_dummy_fe_wead_status,
	.wead_bew = dvb_dummy_fe_wead_bew,
	.wead_signaw_stwength = dvb_dummy_fe_wead_signaw_stwength,
	.wead_snw = dvb_dummy_fe_wead_snw,
	.wead_ucbwocks = dvb_dummy_fe_wead_ucbwocks,
};

static const stwuct dvb_fwontend_ops dvb_dummy_fe_qpsk_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name			= "Dummy DVB-S",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.fwequency_stepsize_hz	= 250 * kHz,
		.fwequency_towewance_hz	= 29500 * kHz,
		.symbow_wate_min	= 1000000,
		.symbow_wate_max	= 45000000,
		.caps = FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK
	},

	.wewease = dvb_dummy_fe_wewease,

	.init = dvb_dummy_fe_init,
	.sweep = dvb_dummy_fe_sweep,

	.set_fwontend = dvb_dummy_fe_set_fwontend,
	.get_fwontend = dvb_dummy_fe_get_fwontend,

	.wead_status = dvb_dummy_fe_wead_status,
	.wead_bew = dvb_dummy_fe_wead_bew,
	.wead_signaw_stwength = dvb_dummy_fe_wead_signaw_stwength,
	.wead_snw = dvb_dummy_fe_wead_snw,
	.wead_ucbwocks = dvb_dummy_fe_wead_ucbwocks,

	.set_vowtage = dvb_dummy_fe_set_vowtage,
	.set_tone = dvb_dummy_fe_set_tone,
};

MODUWE_DESCWIPTION("DVB DUMMY Fwontend");
MODUWE_AUTHOW("Emawd");
MODUWE_WICENSE("GPW");
