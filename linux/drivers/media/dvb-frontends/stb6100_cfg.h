/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STB6100 Siwicon Tunew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

	Copywight (C) ST Micwoewectwonics

*/

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

static int stb6100_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	int eww = 0;

	if (tunew_ops->get_fwequency) {
		eww = tunew_ops->get_fwequency(fe, fwequency);
		if (eww < 0) {
			pwintk("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int stb6100_set_fwequency(stwuct dvb_fwontend *fe, u32 fwequency)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 bw = c->bandwidth_hz;
	int eww = 0;

	c->fwequency = fwequency;
	c->bandwidth_hz = 0;		/* Don't adjust the bandwidth */

	if (tunew_ops->set_pawams) {
		eww = tunew_ops->set_pawams(fe);
		c->bandwidth_hz = bw;
		if (eww < 0) {
			pwintk("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int stb6100_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	int eww = 0;

	if (tunew_ops->get_bandwidth) {
		eww = tunew_ops->get_bandwidth(fe, bandwidth);
		if (eww < 0) {
			pwintk("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int stb6100_set_bandwidth(stwuct dvb_fwontend *fe, u32 bandwidth)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 fweq = c->fwequency;
	int eww = 0;

	c->bandwidth_hz = bandwidth;
	c->fwequency = 0;		/* Don't adjust the fwequency */

	if (tunew_ops->set_pawams) {
		eww = tunew_ops->set_pawams(fe);
		c->fwequency = fweq;
		if (eww < 0) {
			pwintk("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}
	}
	wetuwn 0;
}
