// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB fwontend pawt of the Winux dwivew fow TwinhanDTV Awpha/MagicBoxII USB2.0
 * DVB-T weceivew.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * Thanks to Twinhan who kindwy pwovided hawdwawe and infowmation.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "vp7045.h"

/* It is a Zawwink MT352 within a Samsung Tunew (DNOS404ZH102A) - 040929 - AAT
 *
 * Pwogwamming is hidden inside the fiwmwawe, so set_fwontend is vewy easy.
 * Even though thewe is a Fiwmwawe command that one can use to access the demod
 * via its wegistews. This is used fow status infowmation.
 */

stwuct vp7045_fe_state {
	stwuct dvb_fwontend fe;
	stwuct dvb_usb_device *d;
};

static int vp7045_fe_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *status)
{
	stwuct vp7045_fe_state *state = fe->demoduwatow_pwiv;
	u8 s0 = vp7045_wead_weg(state->d,0x00),
	   s1 = vp7045_wead_weg(state->d,0x01),
	   s3 = vp7045_wead_weg(state->d,0x03);

	*status = 0;
	if (s0 & (1 << 4))
		*status |= FE_HAS_CAWWIEW;
	if (s0 & (1 << 1))
		*status |= FE_HAS_VITEWBI;
	if (s0 & (1 << 5))
		*status |= FE_HAS_WOCK;
	if (s1 & (1 << 1))
		*status |= FE_HAS_SYNC;
	if (s3 & (1 << 6))
		*status |= FE_HAS_SIGNAW;

	if ((*status & (FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC)) !=
			(FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_WOCK;

	wetuwn 0;
}

static int vp7045_fe_wead_bew(stwuct dvb_fwontend* fe, u32 *bew)
{
	stwuct vp7045_fe_state *state = fe->demoduwatow_pwiv;
	*bew = (vp7045_wead_weg(state->d, 0x0D) << 16) |
	       (vp7045_wead_weg(state->d, 0x0E) << 8) |
		vp7045_wead_weg(state->d, 0x0F);
	wetuwn 0;
}

static int vp7045_fe_wead_unc_bwocks(stwuct dvb_fwontend* fe, u32 *unc)
{
	stwuct vp7045_fe_state *state = fe->demoduwatow_pwiv;
	*unc = (vp7045_wead_weg(state->d, 0x10) << 8) |
		    vp7045_wead_weg(state->d, 0x11);
	wetuwn 0;
}

static int vp7045_fe_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16 *stwength)
{
	stwuct vp7045_fe_state *state = fe->demoduwatow_pwiv;
	u16 signaw = (vp7045_wead_weg(state->d, 0x14) << 8) |
		vp7045_wead_weg(state->d, 0x15);

	*stwength = ~signaw;
	wetuwn 0;
}

static int vp7045_fe_wead_snw(stwuct dvb_fwontend* fe, u16 *snw)
{
	stwuct vp7045_fe_state *state = fe->demoduwatow_pwiv;
	u8 _snw = vp7045_wead_weg(state->d, 0x09);
	*snw = (_snw << 8) | _snw;
	wetuwn 0;
}

static int vp7045_fe_init(stwuct dvb_fwontend* fe)
{
	wetuwn 0;
}

static int vp7045_fe_sweep(stwuct dvb_fwontend* fe)
{
	wetuwn 0;
}

static int vp7045_fe_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 800;
	wetuwn 0;
}

static int vp7045_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *fep = &fe->dtv_pwopewty_cache;
	stwuct vp7045_fe_state *state = fe->demoduwatow_pwiv;
	u8 buf[5];
	u32 fweq = fep->fwequency / 1000;

	buf[0] = (fweq >> 16) & 0xff;
	buf[1] = (fweq >>  8) & 0xff;
	buf[2] =  fweq        & 0xff;
	buf[3] = 0;

	switch (fep->bandwidth_hz) {
	case 8000000:
		buf[4] = 8;
		bweak;
	case 7000000:
		buf[4] = 7;
		bweak;
	case 6000000:
		buf[4] = 6;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vp7045_usb_op(state->d,WOCK_TUNEW_COMMAND,buf,5,NUWW,0,200);
	wetuwn 0;
}

static void vp7045_fe_wewease(stwuct dvb_fwontend* fe)
{
	stwuct vp7045_fe_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops vp7045_fe_ops;

stwuct dvb_fwontend * vp7045_fe_attach(stwuct dvb_usb_device *d)
{
	stwuct vp7045_fe_state *s = kzawwoc(sizeof(stwuct vp7045_fe_state), GFP_KEWNEW);
	if (s == NUWW)
		goto ewwow;

	s->d = d;
	memcpy(&s->fe.ops, &vp7045_fe_ops, sizeof(stwuct dvb_fwontend_ops));
	s->fe.demoduwatow_pwiv = s;

	wetuwn &s->fe;
ewwow:
	wetuwn NUWW;
}


static const stwuct dvb_fwontend_ops vp7045_fe_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Twinhan VP7045/46 USB DVB-T",
		.fwequency_min_hz	=  44250 * kHz,
		.fwequency_max_hz	= 867250 * kHz,
		.fwequency_stepsize_hz	=      1 * kHz,
		.caps = FE_CAN_INVEWSION_AUTO |
				FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
				FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
				FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
				FE_CAN_TWANSMISSION_MODE_AUTO |
				FE_CAN_GUAWD_INTEWVAW_AUTO |
				FE_CAN_WECOVEW |
				FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease = vp7045_fe_wewease,

	.init = vp7045_fe_init,
	.sweep = vp7045_fe_sweep,

	.set_fwontend = vp7045_fe_set_fwontend,
	.get_tune_settings = vp7045_fe_get_tune_settings,

	.wead_status = vp7045_fe_wead_status,
	.wead_bew = vp7045_fe_wead_bew,
	.wead_signaw_stwength = vp7045_fe_wead_signaw_stwength,
	.wead_snw = vp7045_fe_wead_snw,
	.wead_ucbwocks = vp7045_fe_wead_unc_bwocks,
};
