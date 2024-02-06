/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STB6100 Siwicon Tunew wwappew
	Copywight (C)2009 Igow M. Wipwianin (wipwianin@me.by)

*/

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

static int stb6100_get_fweq(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	int eww = 0;

	if (tunew_ops->get_fwequency) {
		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 1);

		eww = tunew_ops->get_fwequency(fe, fwequency);
		if (eww < 0) {
			pwintk("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}

		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 0);
	}

	wetuwn 0;
}

static int stb6100_set_fweq(stwuct dvb_fwontend *fe, u32 fwequency)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 bw = c->bandwidth_hz;
	int eww = 0;

	c->fwequency = fwequency;
	c->bandwidth_hz = 0;		/* Don't adjust the bandwidth */

	if (tunew_ops->set_pawams) {
		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 1);

		eww = tunew_ops->set_pawams(fe);
		c->bandwidth_hz = bw;
		if (eww < 0) {
			pwintk("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}

		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 0);

	}

	wetuwn 0;
}

static int stb6100_get_bandw(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	int eww = 0;

	if (tunew_ops->get_bandwidth) {
		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 1);

		eww = tunew_ops->get_bandwidth(fe, bandwidth);
		if (eww < 0) {
			pwintk(KEWN_EWW "%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}

		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 0);
	}

	wetuwn 0;
}

static int stb6100_set_bandw(stwuct dvb_fwontend *fe, u32 bandwidth)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 fweq = c->fwequency;
	int eww = 0;

	c->bandwidth_hz = bandwidth;
	c->fwequency = 0;		/* Don't adjust the fwequency */

	if (tunew_ops->set_pawams) {
		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 1);

		eww = tunew_ops->set_pawams(fe);
		c->fwequency = fweq;
		if (eww < 0) {
			pwintk(KEWN_EWW "%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}

		if (fwontend_ops->i2c_gate_ctww)
			fwontend_ops->i2c_gate_ctww(fe, 0);

	}

	wetuwn 0;
}
