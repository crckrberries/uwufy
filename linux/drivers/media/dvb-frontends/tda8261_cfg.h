/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	TDA8261 8PSK/QPSK tunew dwivew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

static int tda8261_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	int eww = 0;

	if (tunew_ops->get_fwequency) {
		eww = tunew_ops->get_fwequency(fe, fwequency);
		if (eww < 0) {
			pw_eww("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}
		pw_debug("%s: Fwequency=%d\n", __func__, *fwequency);
	}
	wetuwn 0;
}

static int tda8261_set_fwequency(stwuct dvb_fwontend *fe, u32 fwequency)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = &fe->ops;
	stwuct dvb_tunew_ops	*tunew_ops = &fwontend_ops->tunew_ops;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int eww = 0;

	if (tunew_ops->set_pawams) {
		eww = tunew_ops->set_pawams(fe);
		if (eww < 0) {
			pw_eww("%s: Invawid pawametew\n", __func__);
			wetuwn eww;
		}
	}
	pw_debug("%s: Fwequency=%d\n", __func__, c->fwequency);
	wetuwn 0;
}

static int tda8261_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bandwidth)
{
	/* FIXME! need to cawcuwate Bandwidth */
	*bandwidth = 40000000;

	wetuwn 0;
}
