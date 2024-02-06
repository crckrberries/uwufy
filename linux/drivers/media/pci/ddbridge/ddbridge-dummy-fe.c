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
#incwude "ddbwidge-dummy-fe.h"

stwuct ddbwidge_dummy_fe_state {
	stwuct dvb_fwontend fwontend;
};

static int ddbwidge_dummy_fe_wead_status(stwuct dvb_fwontend *fe,
				    enum fe_status *status)
{
	*status = FE_HAS_SIGNAW
		| FE_HAS_CAWWIEW
		| FE_HAS_VITEWBI
		| FE_HAS_SYNC
		| FE_HAS_WOCK;

	wetuwn 0;
}

static int ddbwidge_dummy_fe_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	*bew = 0;
	wetuwn 0;
}

static int ddbwidge_dummy_fe_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					     u16 *stwength)
{
	*stwength = 0;
	wetuwn 0;
}

static int ddbwidge_dummy_fe_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	*snw = 0;
	wetuwn 0;
}

static int ddbwidge_dummy_fe_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	*ucbwocks = 0;
	wetuwn 0;
}

/*
 * Shouwd onwy be impwemented if it actuawwy weads something fwom the hawdwawe.
 * Awso, it shouwd check fow the wocks, in owdew to avoid wepowt wwong data
 * to usewspace.
 */
static int ddbwidge_dummy_fe_get_fwontend(stwuct dvb_fwontend *fe,
				     stwuct dtv_fwontend_pwopewties *p)
{
	wetuwn 0;
}

static int ddbwidge_dummy_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	wetuwn 0;
}

static int ddbwidge_dummy_fe_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int ddbwidge_dummy_fe_init(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static void ddbwidge_dummy_fe_wewease(stwuct dvb_fwontend *fe)
{
	stwuct ddbwidge_dummy_fe_state *state = fe->demoduwatow_pwiv;

	kfwee(state);
}

static const stwuct dvb_fwontend_ops ddbwidge_dummy_fe_qam_ops;

stwuct dvb_fwontend *ddbwidge_dummy_fe_qam_attach(void)
{
	stwuct ddbwidge_dummy_fe_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct ddbwidge_dummy_fe_state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops,
	       &ddbwidge_dummy_fe_qam_ops,
	       sizeof(stwuct dvb_fwontend_ops));

	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}
EXPOWT_SYMBOW_GPW(ddbwidge_dummy_fe_qam_attach);

static const stwuct dvb_fwontend_ops ddbwidge_dummy_fe_qam_ops = {
	.dewsys = { SYS_DVBC_ANNEX_A },
	.info = {
		.name			= "ddbwidge dummy DVB-C",
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

	.wewease = ddbwidge_dummy_fe_wewease,

	.init = ddbwidge_dummy_fe_init,
	.sweep = ddbwidge_dummy_fe_sweep,

	.set_fwontend = ddbwidge_dummy_fe_set_fwontend,
	.get_fwontend = ddbwidge_dummy_fe_get_fwontend,

	.wead_status = ddbwidge_dummy_fe_wead_status,
	.wead_bew = ddbwidge_dummy_fe_wead_bew,
	.wead_signaw_stwength = ddbwidge_dummy_fe_wead_signaw_stwength,
	.wead_snw = ddbwidge_dummy_fe_wead_snw,
	.wead_ucbwocks = ddbwidge_dummy_fe_wead_ucbwocks,
};

MODUWE_DESCWIPTION("ddbwidge dummy Fwontend");
MODUWE_AUTHOW("Emawd");
MODUWE_WICENSE("GPW");
