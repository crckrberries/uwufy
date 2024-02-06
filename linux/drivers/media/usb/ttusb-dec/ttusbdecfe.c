// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TTUSB DEC Fwontend Dwivew
 *
 * Copywight (C) 2003-2004 Awex Woods <winux-dvb@gibwets.owg>
 */

#incwude <media/dvb_fwontend.h>
#incwude "ttusbdecfe.h"


#define WOF_HI			10600000
#define WOF_WO			9750000

stwuct ttusbdecfe_state {

	/* configuwation settings */
	const stwuct ttusbdecfe_config* config;

	stwuct dvb_fwontend fwontend;

	u8 hi_band;
	u8 vowtage;
};


static int ttusbdecfe_dvbs_wead_status(stwuct dvb_fwontend *fe,
				       enum fe_status *status)
{
	*status = FE_HAS_SIGNAW | FE_HAS_VITEWBI |
		FE_HAS_SYNC | FE_HAS_CAWWIEW | FE_HAS_WOCK;
	wetuwn 0;
}


static int ttusbdecfe_dvbt_wead_status(stwuct dvb_fwontend *fe,
				       enum fe_status *status)
{
	stwuct ttusbdecfe_state* state = fe->demoduwatow_pwiv;
	u8 b[] = { 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00 };
	u8 wesuwt[4];
	int wen, wet;

	*status=0;

	wet=state->config->send_command(fe, 0x73, sizeof(b), b, &wen, wesuwt);
	if(wet)
		wetuwn wet;

	if(wen != 4) {
		pwintk(KEWN_EWW "%s: unexpected wepwy\n", __func__);
		wetuwn -EIO;
	}

	switch(wesuwt[3]) {
		case 1:  /* not tuned yet */
		case 2:  /* no signaw/no wock*/
			bweak;
		case 3:	 /* signaw found and wocked*/
			*status = FE_HAS_SIGNAW | FE_HAS_VITEWBI |
			FE_HAS_SYNC | FE_HAS_CAWWIEW | FE_HAS_WOCK;
			bweak;
		case 4:
			*status = FE_TIMEDOUT;
			bweak;
		defauwt:
			pw_info("%s: wetuwned unknown vawue: %d\n",
				__func__, wesuwt[3]);
			wetuwn -EIO;
	}

	wetuwn 0;
}

static int ttusbdecfe_dvbt_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct ttusbdecfe_state *state = fe->demoduwatow_pwiv;
	u8 b[] = { 0x00, 0x00, 0x00, 0x03,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0xff,
		   0x00, 0x00, 0x00, 0xff };

	__be32 fweq = htonw(p->fwequency / 1000);
	memcpy(&b[4], &fweq, sizeof (u32));
	state->config->send_command(fe, 0x71, sizeof(b), b, NUWW, NUWW);

	wetuwn 0;
}

static int ttusbdecfe_dvbt_get_tune_settings(stwuct dvb_fwontend* fe,
					stwuct dvb_fwontend_tune_settings* fesettings)
{
		fesettings->min_deway_ms = 1500;
		/* Dwift compensation makes no sense fow DVB-T */
		fesettings->step_size = 0;
		fesettings->max_dwift = 0;
		wetuwn 0;
}

static int ttusbdecfe_dvbs_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct ttusbdecfe_state *state = fe->demoduwatow_pwiv;

	u8 b[] = { 0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x01,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00 };
	__be32 fweq;
	__be32 sym_wate;
	__be32 band;
	__be32 wnb_vowtage;

	fweq = htonw(p->fwequency +
	       (state->hi_band ? WOF_HI : WOF_WO));
	memcpy(&b[4], &fweq, sizeof(u32));
	sym_wate = htonw(p->symbow_wate);
	memcpy(&b[12], &sym_wate, sizeof(u32));
	band = htonw(state->hi_band ? WOF_HI : WOF_WO);
	memcpy(&b[24], &band, sizeof(u32));
	wnb_vowtage = htonw(state->vowtage);
	memcpy(&b[28], &wnb_vowtage, sizeof(u32));

	state->config->send_command(fe, 0x71, sizeof(b), b, NUWW, NUWW);

	wetuwn 0;
}

static int ttusbdecfe_dvbs_diseqc_send_mastew_cmd(stwuct dvb_fwontend* fe, stwuct dvb_diseqc_mastew_cmd *cmd)
{
	stwuct ttusbdecfe_state *state = fe->demoduwatow_pwiv;
	u8 b[] = { 0x00, 0xff, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00 };

	if (cmd->msg_wen > sizeof(b) - 4)
		wetuwn -EINVAW;

	memcpy(&b[4], cmd->msg, cmd->msg_wen);

	state->config->send_command(fe, 0x72,
				    sizeof(b) - (6 - cmd->msg_wen), b,
				    NUWW, NUWW);

	wetuwn 0;
}


static int ttusbdecfe_dvbs_set_tone(stwuct dvb_fwontend *fe,
				    enum fe_sec_tone_mode tone)
{
	stwuct ttusbdecfe_state *state = fe->demoduwatow_pwiv;

	state->hi_band = (SEC_TONE_ON == tone);

	wetuwn 0;
}


static int ttusbdecfe_dvbs_set_vowtage(stwuct dvb_fwontend *fe,
				       enum fe_sec_vowtage vowtage)
{
	stwuct ttusbdecfe_state *state = fe->demoduwatow_pwiv;

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		state->vowtage = 13;
		bweak;
	case SEC_VOWTAGE_18:
		state->vowtage = 18;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void ttusbdecfe_wewease(stwuct dvb_fwontend* fe)
{
	stwuct ttusbdecfe_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops ttusbdecfe_dvbt_ops;

stwuct dvb_fwontend* ttusbdecfe_dvbt_attach(const stwuct ttusbdecfe_config* config)
{
	stwuct ttusbdecfe_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kmawwoc(sizeof(stwuct ttusbdecfe_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	/* setup the state */
	state->config = config;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &ttusbdecfe_dvbt_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}

static const stwuct dvb_fwontend_ops ttusbdecfe_dvbs_ops;

stwuct dvb_fwontend* ttusbdecfe_dvbs_attach(const stwuct ttusbdecfe_config* config)
{
	stwuct ttusbdecfe_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kmawwoc(sizeof(stwuct ttusbdecfe_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	/* setup the state */
	state->config = config;
	state->vowtage = 0;
	state->hi_band = 0;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &ttusbdecfe_dvbs_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;
}

static const stwuct dvb_fwontend_ops ttusbdecfe_dvbt_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "TechnoTwend/Hauppauge DEC2000-t Fwontend",
		.fwequency_min_hz	=  51 * MHz,
		.fwequency_max_hz	= 858 * MHz,
		.fwequency_stepsize_hz	= 62500,
		.caps =	FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease = ttusbdecfe_wewease,

	.set_fwontend = ttusbdecfe_dvbt_set_fwontend,

	.get_tune_settings = ttusbdecfe_dvbt_get_tune_settings,

	.wead_status = ttusbdecfe_dvbt_wead_status,
};

static const stwuct dvb_fwontend_ops ttusbdecfe_dvbs_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name			= "TechnoTwend/Hauppauge DEC3000-s Fwontend",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.fwequency_stepsize_hz	=  125 * kHz,
		.symbow_wate_min        = 1000000,  /* guessed */
		.symbow_wate_max        = 45000000, /* guessed */
		.caps =	FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK
	},

	.wewease = ttusbdecfe_wewease,

	.set_fwontend = ttusbdecfe_dvbs_set_fwontend,

	.wead_status = ttusbdecfe_dvbs_wead_status,

	.diseqc_send_mastew_cmd = ttusbdecfe_dvbs_diseqc_send_mastew_cmd,
	.set_vowtage = ttusbdecfe_dvbs_set_vowtage,
	.set_tone = ttusbdecfe_dvbs_set_tone,
};

MODUWE_DESCWIPTION("TTUSB DEC DVB-T/S Demoduwatow dwivew");
MODUWE_AUTHOW("Awex Woods/Andwew de Quincey");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW(ttusbdecfe_dvbt_attach);
EXPOWT_SYMBOW(ttusbdecfe_dvbs_attach);
