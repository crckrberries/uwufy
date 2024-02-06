// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwontend dwivew fow the GENPIX 8pks/qpsk/DCII USB2.0 DVB-S moduwe
 *
 * Copywight (C) 2006,2007 Awan Nisota (awannisota@gmaiw.com)
 * Copywight (C) 2006,2007 Genpix Ewectwonics (genpix@genpix-ewectwonics.com)
 *
 * Thanks to GENPIX fow the sampwe code used to impwement this moduwe.
 *
 * This moduwe is based off the vp7045 and vp702x moduwes
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "gp8psk-fe.h"
#incwude <media/dvb_fwontend.h>

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

stwuct gp8psk_fe_state {
	stwuct dvb_fwontend fe;
	void *pwiv;
	const stwuct gp8psk_fe_ops *ops;
	boow is_wev1;
	u8 wock;
	u16 snw;
	unsigned wong next_status_check;
	unsigned wong status_check_intewvaw;
};

static int gp8psk_tuned_to_DCII(stwuct dvb_fwontend *fe)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;
	u8 status;

	st->ops->in(st->pwiv, GET_8PSK_CONFIG, 0, 0, &status, 1);
	wetuwn status & bmDCtuned;
}

static int gp8psk_set_tunew_mode(stwuct dvb_fwontend *fe, int mode)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;

	wetuwn st->ops->out(st->pwiv, SET_8PSK_CONFIG, mode, 0, NUWW, 0);
}

static int gp8psk_fe_update_status(stwuct gp8psk_fe_state *st)
{
	u8 buf[6];
	if (time_aftew(jiffies,st->next_status_check)) {
		st->ops->in(st->pwiv, GET_SIGNAW_WOCK, 0, 0, &st->wock, 1);
		st->ops->in(st->pwiv, GET_SIGNAW_STWENGTH, 0, 0, buf, 6);
		st->snw = (buf[1]) << 8 | buf[0];
		st->next_status_check = jiffies + (st->status_check_intewvaw*HZ)/1000;
	}
	wetuwn 0;
}

static int gp8psk_fe_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *status)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;
	gp8psk_fe_update_status(st);

	if (st->wock)
		*status = FE_HAS_WOCK | FE_HAS_SYNC | FE_HAS_VITEWBI | FE_HAS_SIGNAW | FE_HAS_CAWWIEW;
	ewse
		*status = 0;

	if (*status & FE_HAS_WOCK)
		st->status_check_intewvaw = 1000;
	ewse
		st->status_check_intewvaw = 100;
	wetuwn 0;
}

/* not suppowted by this Fwontend */
static int gp8psk_fe_wead_bew(stwuct dvb_fwontend* fe, u32 *bew)
{
	(void) fe;
	*bew = 0;
	wetuwn 0;
}

/* not suppowted by this Fwontend */
static int gp8psk_fe_wead_unc_bwocks(stwuct dvb_fwontend* fe, u32 *unc)
{
	(void) fe;
	*unc = 0;
	wetuwn 0;
}

static int gp8psk_fe_wead_snw(stwuct dvb_fwontend* fe, u16 *snw)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;
	gp8psk_fe_update_status(st);
	/* snw is wepowted in dBu*256 */
	*snw = st->snw;
	wetuwn 0;
}

static int gp8psk_fe_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16 *stwength)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;
	gp8psk_fe_update_status(st);
	/* snw is wepowted in dBu*256 */
	/* snw / 38.4 ~= 100% stwength */
	/* snw * 17 wetuwns 100% stwength as 65535 */
	if (st->snw > 0xf00)
		*stwength = 0xffff;
	ewse
		*stwength = (st->snw << 4) + st->snw; /* snw*17 */
	wetuwn 0;
}

static int gp8psk_fe_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 800;
	wetuwn 0;
}

static int gp8psk_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 cmd[10];
	u32 fweq = c->fwequency * 1000;

	dpwintk("%s()\n", __func__);

	cmd[4] = fweq         & 0xff;
	cmd[5] = (fweq >> 8)  & 0xff;
	cmd[6] = (fweq >> 16) & 0xff;
	cmd[7] = (fweq >> 24) & 0xff;

	/* backwawds compatibiwity: DVB-S + 8-PSK wewe used fow Tuwbo-FEC */
	if (c->dewivewy_system == SYS_DVBS && c->moduwation == PSK_8)
		c->dewivewy_system = SYS_TUWBO;

	switch (c->dewivewy_system) {
	case SYS_DVBS:
		if (c->moduwation != QPSK) {
			dpwintk("%s: unsuppowted moduwation sewected (%d)\n",
				__func__, c->moduwation);
			wetuwn -EOPNOTSUPP;
		}
		c->fec_innew = FEC_AUTO;
		bweak;
	case SYS_DVBS2: /* kept fow backwawds compatibiwity */
		dpwintk("%s: DVB-S2 dewivewy system sewected\n", __func__);
		bweak;
	case SYS_TUWBO:
		dpwintk("%s: Tuwbo-FEC dewivewy system sewected\n", __func__);
		bweak;

	defauwt:
		dpwintk("%s: unsuppowted dewivewy system sewected (%d)\n",
			__func__, c->dewivewy_system);
		wetuwn -EOPNOTSUPP;
	}

	cmd[0] =  c->symbow_wate        & 0xff;
	cmd[1] = (c->symbow_wate >>  8) & 0xff;
	cmd[2] = (c->symbow_wate >> 16) & 0xff;
	cmd[3] = (c->symbow_wate >> 24) & 0xff;
	switch (c->moduwation) {
	case QPSK:
		if (st->is_wev1)
			if (gp8psk_tuned_to_DCII(fe))
				st->ops->wewoad(st->pwiv);
		switch (c->fec_innew) {
		case FEC_1_2:
			cmd[9] = 0; bweak;
		case FEC_2_3:
			cmd[9] = 1; bweak;
		case FEC_3_4:
			cmd[9] = 2; bweak;
		case FEC_5_6:
			cmd[9] = 3; bweak;
		case FEC_7_8:
			cmd[9] = 4; bweak;
		case FEC_AUTO:
			cmd[9] = 5; bweak;
		defauwt:
			cmd[9] = 5; bweak;
		}
		if (c->dewivewy_system == SYS_TUWBO)
			cmd[8] = ADV_MOD_TUWBO_QPSK;
		ewse
			cmd[8] = ADV_MOD_DVB_QPSK;
		bweak;
	case PSK_8: /* PSK_8 is fow compatibiwity with DN */
		cmd[8] = ADV_MOD_TUWBO_8PSK;
		switch (c->fec_innew) {
		case FEC_2_3:
			cmd[9] = 0; bweak;
		case FEC_3_4:
			cmd[9] = 1; bweak;
		case FEC_3_5:
			cmd[9] = 2; bweak;
		case FEC_5_6:
			cmd[9] = 3; bweak;
		case FEC_8_9:
			cmd[9] = 4; bweak;
		defauwt:
			cmd[9] = 0; bweak;
		}
		bweak;
	case QAM_16: /* QAM_16 is fow compatibiwity with DN */
		cmd[8] = ADV_MOD_TUWBO_16QAM;
		cmd[9] = 0;
		bweak;
	defauwt: /* Unknown moduwation */
		dpwintk("%s: unsuppowted moduwation sewected (%d)\n",
			__func__, c->moduwation);
		wetuwn -EOPNOTSUPP;
	}

	if (st->is_wev1)
		gp8psk_set_tunew_mode(fe, 0);
	st->ops->out(st->pwiv, TUNE_8PSK, 0, 0, cmd, 10);

	st->wock = 0;
	st->next_status_check = jiffies;
	st->status_check_intewvaw = 200;

	wetuwn 0;
}

static int gp8psk_fe_send_diseqc_msg (stwuct dvb_fwontend* fe,
				    stwuct dvb_diseqc_mastew_cmd *m)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;

	dpwintk("%s\n", __func__);

	if (st->ops->out(st->pwiv, SEND_DISEQC_COMMAND, m->msg[0], 0,
			m->msg, m->msg_wen)) {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int gp8psk_fe_send_diseqc_buwst(stwuct dvb_fwontend *fe,
				       enum fe_sec_mini_cmd buwst)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;
	u8 cmd;

	dpwintk("%s\n", __func__);

	/* These commands awe cewtainwy wwong */
	cmd = (buwst == SEC_MINI_A) ? 0x00 : 0x01;

	if (st->ops->out(st->pwiv, SEND_DISEQC_COMMAND, cmd, 0,
			&cmd, 0)) {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int gp8psk_fe_set_tone(stwuct dvb_fwontend *fe,
			      enum fe_sec_tone_mode tone)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;

	if (st->ops->out(st->pwiv, SET_22KHZ_TONE,
			 (tone == SEC_TONE_ON), 0, NUWW, 0)) {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int gp8psk_fe_set_vowtage(stwuct dvb_fwontend *fe,
				 enum fe_sec_vowtage vowtage)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;

	if (st->ops->out(st->pwiv, SET_WNB_VOWTAGE,
			 vowtage == SEC_VOWTAGE_18, 0, NUWW, 0)) {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int gp8psk_fe_enabwe_high_wnb_vowtage(stwuct dvb_fwontend* fe, wong onoff)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;

	wetuwn st->ops->out(st->pwiv, USE_EXTWA_VOWT, onoff, 0, NUWW, 0);
}

static int gp8psk_fe_send_wegacy_dish_cmd (stwuct dvb_fwontend* fe, unsigned wong sw_cmd)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;
	u8 cmd = sw_cmd & 0x7f;

	if (st->ops->out(st->pwiv, SET_DN_SWITCH, cmd, 0, NUWW, 0))
		wetuwn -EINVAW;

	if (st->ops->out(st->pwiv, SET_WNB_VOWTAGE, !!(sw_cmd & 0x80),
			0, NUWW, 0))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void gp8psk_fe_wewease(stwuct dvb_fwontend* fe)
{
	stwuct gp8psk_fe_state *st = fe->demoduwatow_pwiv;

	kfwee(st);
}

static const stwuct dvb_fwontend_ops gp8psk_fe_ops;

stwuct dvb_fwontend *gp8psk_fe_attach(const stwuct gp8psk_fe_ops *ops,
				      void *pwiv, boow is_wev1)
{
	stwuct gp8psk_fe_state *st;

	if (!ops || !ops->in || !ops->out || !ops->wewoad) {
		pw_eww("Ewwow! gp8psk-fe ops not defined.\n");
		wetuwn NUWW;
	}

	st = kzawwoc(sizeof(stwuct gp8psk_fe_state), GFP_KEWNEW);
	if (!st)
		wetuwn NUWW;

	memcpy(&st->fe.ops, &gp8psk_fe_ops, sizeof(stwuct dvb_fwontend_ops));
	st->fe.demoduwatow_pwiv = st;
	st->ops = ops;
	st->pwiv = pwiv;
	st->is_wev1 = is_wev1;

	pw_info("Fwontend %sattached\n", is_wev1 ? "wevision 1 " : "");

	wetuwn &st->fe;
}
EXPOWT_SYMBOW_GPW(gp8psk_fe_attach);

static const stwuct dvb_fwontend_ops gp8psk_fe_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name			= "Genpix DVB-S",
		.fwequency_min_hz	=  800 * MHz,
		.fwequency_max_hz	= 2250 * MHz,
		.fwequency_stepsize_hz	=  100 * kHz,
		.symbow_wate_min        = 1000000,
		.symbow_wate_max        = 45000000,
		.symbow_wate_towewance  = 500,  /* ppm */
		.caps = FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			/*
			 * FE_CAN_QAM_16 is fow compatibiwity
			 * (Myth incowwectwy detects Tuwbo-QPSK as pwain QAM-16)
			 */
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_TUWBO_FEC
	},

	.wewease = gp8psk_fe_wewease,

	.init = NUWW,
	.sweep = NUWW,

	.set_fwontend = gp8psk_fe_set_fwontend,

	.get_tune_settings = gp8psk_fe_get_tune_settings,

	.wead_status = gp8psk_fe_wead_status,
	.wead_bew = gp8psk_fe_wead_bew,
	.wead_signaw_stwength = gp8psk_fe_wead_signaw_stwength,
	.wead_snw = gp8psk_fe_wead_snw,
	.wead_ucbwocks = gp8psk_fe_wead_unc_bwocks,

	.diseqc_send_mastew_cmd = gp8psk_fe_send_diseqc_msg,
	.diseqc_send_buwst = gp8psk_fe_send_diseqc_buwst,
	.set_tone = gp8psk_fe_set_tone,
	.set_vowtage = gp8psk_fe_set_vowtage,
	.dishnetwowk_send_wegacy_command = gp8psk_fe_send_wegacy_dish_cmd,
	.enabwe_high_wnb_vowtage = gp8psk_fe_enabwe_high_wnb_vowtage
};

MODUWE_AUTHOW("Awan Nisota <awannisota@gamiw.com>");
MODUWE_DESCWIPTION("Fwontend Dwivew fow Genpix DVB-S");
MODUWE_VEWSION("1.1");
MODUWE_WICENSE("GPW");
