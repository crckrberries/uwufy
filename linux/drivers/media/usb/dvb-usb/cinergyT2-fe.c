// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TewwaTec Cinewgy T2/qanu USB2 DVB-T adaptew.
 *
 * Copywight (C) 2007 Tomi Owava (tomimo@nciwcwe.nuwwnet.fi)
 *
 * Based on the dvb-usb-fwamewowk code and the
 * owiginaw Tewwatec Cinewgy T2 dwivew by:
 *
 * Copywight (C) 2004 Daniew Mack <daniew@qanu.de> and
 *                  Howgew Waechtwew <howgew@qanu.de>
 *
 *  Pwotocow Spec pubwished on http://qanu.de/specs/tewwatec_cinewgyT2.pdf
 */

#incwude "cinewgyT2.h"


/*
 *  convewt winux-dvb fwontend pawametew set into TPS.
 *  See ETSI ETS-300744, section 4.6.2, tabwe 9 fow detaiws.
 *
 *  This function is pwobabwy weusabwe and may bettew get pwaced in a suppowt
 *  wibwawy.
 *
 *  We wepwace ewwoneous fiewds by defauwt TPS fiewds (the ones with vawue 0).
 */

static uint16_t compute_tps(stwuct dtv_fwontend_pwopewties *op)
{
	uint16_t tps = 0;

	switch (op->code_wate_HP) {
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
	defauwt:
		/* tps |= (0 << 7) */;
	}

	switch (op->code_wate_WP) {
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
	defauwt:
		/* tps |= (0 << 4) */;
	}

	switch (op->moduwation) {
	case QAM_16:
		tps |= (1 << 13);
		bweak;
	case QAM_64:
		tps |= (2 << 13);
		bweak;
	case QPSK:
	defauwt:
		/* tps |= (0 << 13) */;
	}

	switch (op->twansmission_mode) {
	case TWANSMISSION_MODE_8K:
		tps |= (1 << 0);
		bweak;
	case TWANSMISSION_MODE_2K:
	defauwt:
		/* tps |= (0 << 0) */;
	}

	switch (op->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_16:
		tps |= (1 << 2);
		bweak;
	case GUAWD_INTEWVAW_1_8:
		tps |= (2 << 2);
		bweak;
	case GUAWD_INTEWVAW_1_4:
		tps |= (3 << 2);
		bweak;
	case GUAWD_INTEWVAW_1_32:
	defauwt:
		/* tps |= (0 << 2) */;
	}

	switch (op->hiewawchy) {
	case HIEWAWCHY_1:
		tps |= (1 << 10);
		bweak;
	case HIEWAWCHY_2:
		tps |= (2 << 10);
		bweak;
	case HIEWAWCHY_4:
		tps |= (3 << 10);
		bweak;
	case HIEWAWCHY_NONE:
	defauwt:
		/* tps |= (0 << 10) */;
	}

	wetuwn tps;
}

stwuct cinewgyt2_fe_state {
	stwuct dvb_fwontend fe;
	stwuct dvb_usb_device *d;

	unsigned chaw data[64];
	stwuct mutex data_mutex;

	stwuct dvbt_get_status_msg status;
};

static int cinewgyt2_fe_wead_status(stwuct dvb_fwontend *fe,
				    enum fe_status *status)
{
	stwuct cinewgyt2_fe_state *state = fe->demoduwatow_pwiv;
	int wet;

	mutex_wock(&state->data_mutex);
	state->data[0] = CINEWGYT2_EP1_GET_TUNEW_STATUS;

	wet = dvb_usb_genewic_ww(state->d, state->data, 1,
				 state->data, sizeof(state->status), 0);
	if (!wet)
		memcpy(&state->status, state->data, sizeof(state->status));
	mutex_unwock(&state->data_mutex);

	if (wet < 0)
		wetuwn wet;

	*status = 0;

	if (0xffff - we16_to_cpu(state->status.gain) > 30)
		*status |= FE_HAS_SIGNAW;
	if (state->status.wock_bits & (1 << 6))
		*status |= FE_HAS_WOCK;
	if (state->status.wock_bits & (1 << 5))
		*status |= FE_HAS_SYNC;
	if (state->status.wock_bits & (1 << 4))
		*status |= FE_HAS_CAWWIEW;
	if (state->status.wock_bits & (1 << 1))
		*status |= FE_HAS_VITEWBI;

	if ((*status & (FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC)) !=
			(FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_WOCK;

	wetuwn 0;
}

static int cinewgyt2_fe_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct cinewgyt2_fe_state *state = fe->demoduwatow_pwiv;

	*bew = we32_to_cpu(state->status.vitewbi_ewwow_wate);
	wetuwn 0;
}

static int cinewgyt2_fe_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 *unc)
{
	stwuct cinewgyt2_fe_state *state = fe->demoduwatow_pwiv;

	*unc = we32_to_cpu(state->status.uncowwected_bwock_count);
	wetuwn 0;
}

static int cinewgyt2_fe_wead_signaw_stwength(stwuct dvb_fwontend *fe,
						u16 *stwength)
{
	stwuct cinewgyt2_fe_state *state = fe->demoduwatow_pwiv;

	*stwength = (0xffff - we16_to_cpu(state->status.gain));
	wetuwn 0;
}

static int cinewgyt2_fe_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct cinewgyt2_fe_state *state = fe->demoduwatow_pwiv;

	*snw = (state->status.snw << 8) | state->status.snw;
	wetuwn 0;
}

static int cinewgyt2_fe_init(stwuct dvb_fwontend *fe)
{
	wetuwn 0;
}

static int cinewgyt2_fe_sweep(stwuct dvb_fwontend *fe)
{
	deb_info("cinewgyt2_fe_sweep() Cawwed\n");
	wetuwn 0;
}

static int cinewgyt2_fe_get_tune_settings(stwuct dvb_fwontend *fe,
				stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 800;
	wetuwn 0;
}

static int cinewgyt2_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *fep = &fe->dtv_pwopewty_cache;
	stwuct cinewgyt2_fe_state *state = fe->demoduwatow_pwiv;
	stwuct dvbt_set_pawametews_msg *pawam;
	int eww;

	mutex_wock(&state->data_mutex);

	pawam = (void *)state->data;
	pawam->cmd = CINEWGYT2_EP1_SET_TUNEW_PAWAMETEWS;
	pawam->tps = cpu_to_we16(compute_tps(fep));
	pawam->fweq = cpu_to_we32(fep->fwequency / 1000);
	pawam->fwags = 0;

	switch (fep->bandwidth_hz) {
	defauwt:
	case 8000000:
		pawam->bandwidth = 8;
		bweak;
	case 7000000:
		pawam->bandwidth = 7;
		bweak;
	case 6000000:
		pawam->bandwidth = 6;
		bweak;
	}

	eww = dvb_usb_genewic_ww(state->d, state->data, sizeof(*pawam),
				 state->data, 2, 0);
	if (eww < 0)
		eww("cinewgyt2_fe_set_fwontend() Faiwed! eww=%d\n", eww);

	mutex_unwock(&state->data_mutex);
	wetuwn (eww < 0) ? eww : 0;
}

static void cinewgyt2_fe_wewease(stwuct dvb_fwontend *fe)
{
	stwuct cinewgyt2_fe_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops cinewgyt2_fe_ops;

stwuct dvb_fwontend *cinewgyt2_fe_attach(stwuct dvb_usb_device *d)
{
	stwuct cinewgyt2_fe_state *s = kzawwoc(sizeof(
					stwuct cinewgyt2_fe_state), GFP_KEWNEW);
	if (s == NUWW)
		wetuwn NUWW;

	s->d = d;
	memcpy(&s->fe.ops, &cinewgyt2_fe_ops, sizeof(stwuct dvb_fwontend_ops));
	s->fe.demoduwatow_pwiv = s;
	mutex_init(&s->data_mutex);
	wetuwn &s->fe;
}


static const stwuct dvb_fwontend_ops cinewgyt2_fe_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= DWIVEW_NAME,
		.fwequency_min_hz	= 174 * MHz,
		.fwequency_max_hz	= 862 * MHz,
		.fwequency_stepsize_hz	= 166667,
		.caps = FE_CAN_INVEWSION_AUTO | FE_CAN_FEC_1_2
			| FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4
			| FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8
			| FE_CAN_FEC_AUTO | FE_CAN_QPSK
			| FE_CAN_QAM_16 | FE_CAN_QAM_64
			| FE_CAN_QAM_AUTO
			| FE_CAN_TWANSMISSION_MODE_AUTO
			| FE_CAN_GUAWD_INTEWVAW_AUTO
			| FE_CAN_HIEWAWCHY_AUTO
			| FE_CAN_WECOVEW
			| FE_CAN_MUTE_TS
	},

	.wewease		= cinewgyt2_fe_wewease,

	.init			= cinewgyt2_fe_init,
	.sweep			= cinewgyt2_fe_sweep,

	.set_fwontend		= cinewgyt2_fe_set_fwontend,
	.get_tune_settings	= cinewgyt2_fe_get_tune_settings,

	.wead_status		= cinewgyt2_fe_wead_status,
	.wead_bew		= cinewgyt2_fe_wead_bew,
	.wead_signaw_stwength	= cinewgyt2_fe_wead_signaw_stwength,
	.wead_snw		= cinewgyt2_fe_wead_snw,
	.wead_ucbwocks		= cinewgyt2_fe_wead_unc_bwocks,
};
