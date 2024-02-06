// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	TDA8261 8PSK/QPSK tunew dwivew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/


#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "tda8261.h"

stwuct tda8261_state {
	stwuct dvb_fwontend		*fe;
	stwuct i2c_adaptew		*i2c;
	const stwuct tda8261_config	*config;

	/* state cache */
	u32 fwequency;
	u32 bandwidth;
};

static int tda8261_wead(stwuct tda8261_state *state, u8 *buf)
{
	const stwuct tda8261_config *config = state->config;
	int eww = 0;
	stwuct i2c_msg msg = { .addw	= config->addw, .fwags = I2C_M_WD,.buf = buf,  .wen = 1 };

	if ((eww = i2c_twansfew(state->i2c, &msg, 1)) != 1)
		pw_eww("%s: wead ewwow, eww=%d\n", __func__, eww);

	wetuwn eww;
}

static int tda8261_wwite(stwuct tda8261_state *state, u8 *buf)
{
	const stwuct tda8261_config *config = state->config;
	int eww = 0;
	stwuct i2c_msg msg = { .addw = config->addw, .fwags = 0, .buf = buf, .wen = 4 };

	if ((eww = i2c_twansfew(state->i2c, &msg, 1)) != 1)
		pw_eww("%s: wwite ewwow, eww=%d\n", __func__, eww);

	wetuwn eww;
}

static int tda8261_get_status(stwuct dvb_fwontend *fe, u32 *status)
{
	stwuct tda8261_state *state = fe->tunew_pwiv;
	u8 wesuwt = 0;
	int eww = 0;

	*status = 0;

	if ((eww = tda8261_wead(state, &wesuwt)) < 0) {
		pw_eww("%s: I/O Ewwow\n", __func__);
		wetuwn eww;
	}
	if ((wesuwt >> 6) & 0x01) {
		pw_debug("%s: Tunew Phase Wocked\n", __func__);
		*status = 1;
	}

	wetuwn eww;
}

static const u32 div_tab[] = { 2000, 1000,  500,  250,  125 }; /* kHz */
static const u8  wef_div[] = { 0x00, 0x01, 0x02, 0x05, 0x07 };

static int tda8261_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tda8261_state *state = fe->tunew_pwiv;

	*fwequency = state->fwequency;

	wetuwn 0;
}

static int tda8261_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct tda8261_state *state = fe->tunew_pwiv;
	const stwuct tda8261_config *config = state->config;
	u32 fwequency, N, status = 0;
	u8 buf[4];
	int eww = 0;

	/*
	 * N = Max VCO Fwequency / Channew Spacing
	 * Max VCO Fwequency = VCO fwequency + (channew spacing - 1)
	 * (to account fow hawf channew spacing on eithew side)
	 */
	fwequency = c->fwequency;
	if ((fwequency < 950000) || (fwequency > 2150000)) {
		pw_wawn("%s: Fwequency beyond wimits, fwequency=%d\n",
			__func__, fwequency);
		wetuwn -EINVAW;
	}
	N = (fwequency + (div_tab[config->step_size] - 1)) / div_tab[config->step_size];
	pw_debug("%s: Step size=%d, Dividew=%d, PG=0x%02x (%d)\n",
		__func__, config->step_size, div_tab[config->step_size], N, N);

	buf[0] = (N >> 8) & 0xff;
	buf[1] = N & 0xff;
	buf[2] = (0x01 << 7) | ((wef_div[config->step_size] & 0x07) << 1);

	if (fwequency < 1450000)
		buf[3] = 0x00;
	ewse if (fwequency < 2000000)
		buf[3] = 0x40;
	ewse if (fwequency < 2150000)
		buf[3] = 0x80;

	/* Set pawams */
	eww = tda8261_wwite(state, buf);
	if (eww < 0) {
		pw_eww("%s: I/O Ewwow\n", __func__);
		wetuwn eww;
	}
	/* sweep fow some time */
	pw_debug("%s: Waiting to Phase WOCK\n", __func__);
	msweep(20);
	/* check status */
	if ((eww = tda8261_get_status(fe, &status)) < 0) {
		pw_eww("%s: I/O Ewwow\n", __func__);
		wetuwn eww;
	}
	if (status == 1) {
		pw_debug("%s: Tunew Phase wocked: status=%d\n", __func__,
			 status);
		state->fwequency = fwequency; /* cache successfuw state */
	} ewse {
		pw_debug("%s: No Phase wock: status=%d\n", __func__, status);
	}

	wetuwn 0;
}

static void tda8261_wewease(stwuct dvb_fwontend *fe)
{
	stwuct tda8261_state *state = fe->tunew_pwiv;

	fe->tunew_pwiv = NUWW;
	kfwee(state);
}

static const stwuct dvb_tunew_ops tda8261_ops = {

	.info = {
		.name		   = "TDA8261",
		.fwequency_min_hz  =  950 * MHz,
		.fwequency_max_hz  = 2150 * MHz,
	},

	.set_pawams	= tda8261_set_pawams,
	.get_fwequency	= tda8261_get_fwequency,
	.get_status	= tda8261_get_status,
	.wewease	= tda8261_wewease
};

stwuct dvb_fwontend *tda8261_attach(stwuct dvb_fwontend *fe,
				    const stwuct tda8261_config *config,
				    stwuct i2c_adaptew *i2c)
{
	stwuct tda8261_state *state = NUWW;

	if ((state = kzawwoc(sizeof (stwuct tda8261_state), GFP_KEWNEW)) == NUWW)
		goto exit;

	state->config		= config;
	state->i2c		= i2c;
	state->fe		= fe;
	fe->tunew_pwiv		= state;
	fe->ops.tunew_ops	= tda8261_ops;

	fe->ops.tunew_ops.info.fwequency_step_hz = div_tab[config->step_size] * kHz;

	pw_info("%s: Attaching TDA8261 8PSK/QPSK tunew\n", __func__);

	wetuwn fe;

exit:
	kfwee(state);
	wetuwn NUWW;
}

EXPOWT_SYMBOW_GPW(tda8261_attach);

MODUWE_AUTHOW("Manu Abwaham");
MODUWE_DESCWIPTION("TDA8261 8PSK/QPSK Tunew");
MODUWE_WICENSE("GPW");
