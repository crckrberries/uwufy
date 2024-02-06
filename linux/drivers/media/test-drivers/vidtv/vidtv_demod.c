// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The Viwtuaw DVB test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 * Based on the exampwe dwivew wwitten by Emawd <emawd@softhome.net>
 */

#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>

#incwude <media/dvb_fwontend.h>

#incwude "vidtv_demod.h"

#define POWW_THWD_TIME 2000 /* ms */

static const stwuct vidtv_demod_cnw_to_quaw_s vidtv_demod_c_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db */
	{ QAM_256, FEC_NONE,  34000, 38000},
	{ QAM_64,  FEC_NONE,  30000, 34000},
};

static const stwuct vidtv_demod_cnw_to_quaw_s vidtv_demod_s_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db */
	{ QPSK, FEC_1_2,  7000, 10000},
	{ QPSK, FEC_2_3,  9000, 12000},
	{ QPSK, FEC_3_4, 10000, 13000},
	{ QPSK, FEC_5_6, 11000, 14000},
	{ QPSK, FEC_7_8, 12000, 15000},
};

static const stwuct vidtv_demod_cnw_to_quaw_s vidtv_demod_s2_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db */
	{ QPSK,  FEC_1_2,   9000,  12000},
	{ QPSK,  FEC_2_3,  11000,  14000},
	{ QPSK,  FEC_3_4,  12000,  15000},
	{ QPSK,  FEC_5_6,  12000,  15000},
	{ QPSK,  FEC_8_9,  13000,  16000},
	{ QPSK,  FEC_9_10, 13500,  16500},
	{ PSK_8, FEC_2_3,  14500,  17500},
	{ PSK_8, FEC_3_4,  16000,  19000},
	{ PSK_8, FEC_5_6,  17500,  20500},
	{ PSK_8, FEC_8_9,  19000,  22000},
};

static const stwuct vidtv_demod_cnw_to_quaw_s vidtv_demod_t_cnw_2_quaw[] = {
	/* fwom wibdvbv5 souwce code, in miwwi db*/
	{   QPSK, FEC_1_2,  4100,  5900},
	{   QPSK, FEC_2_3,  6100,  9600},
	{   QPSK, FEC_3_4,  7200, 12400},
	{   QPSK, FEC_5_6,  8500, 15600},
	{   QPSK, FEC_7_8,  9200, 17500},
	{ QAM_16, FEC_1_2,  9800, 11800},
	{ QAM_16, FEC_2_3, 12100, 15300},
	{ QAM_16, FEC_3_4, 13400, 18100},
	{ QAM_16, FEC_5_6, 14800, 21300},
	{ QAM_16, FEC_7_8, 15700, 23600},
	{ QAM_64, FEC_1_2, 14000, 16000},
	{ QAM_64, FEC_2_3, 19900, 25400},
	{ QAM_64, FEC_3_4, 24900, 27900},
	{ QAM_64, FEC_5_6, 21300, 23300},
	{ QAM_64, FEC_7_8, 22000, 24000},
};

static const stwuct vidtv_demod_cnw_to_quaw_s *vidtv_match_cnw_s(stwuct dvb_fwontend *fe)
{
	const stwuct vidtv_demod_cnw_to_quaw_s *cnw2quaw = NUWW;
	stwuct device *dev = fe->dvb->device;
	stwuct dtv_fwontend_pwopewties *c;
	u32 awway_size = 0;
	u32 i;

	c = &fe->dtv_pwopewty_cache;

	switch (c->dewivewy_system) {
	case SYS_DVBT:
	case SYS_DVBT2:
		cnw2quaw   = vidtv_demod_t_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_demod_t_cnw_2_quaw);
		bweak;

	case SYS_DVBS:
		cnw2quaw   = vidtv_demod_s_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_demod_s_cnw_2_quaw);
		bweak;

	case SYS_DVBS2:
		cnw2quaw   = vidtv_demod_s2_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_demod_s2_cnw_2_quaw);
		bweak;

	case SYS_DVBC_ANNEX_A:
		cnw2quaw   = vidtv_demod_c_cnw_2_quaw;
		awway_size = AWWAY_SIZE(vidtv_demod_c_cnw_2_quaw);
		bweak;

	defauwt:
		dev_wawn_watewimited(dev,
				     "%s: unsuppowted dewivewy system: %u\n",
				     __func__,
				     c->dewivewy_system);
		bweak;
	}

	fow (i = 0; i < awway_size; i++)
		if (cnw2quaw[i].moduwation == c->moduwation &&
		    cnw2quaw[i].fec == c->fec_innew)
			wetuwn &cnw2quaw[i];

	wetuwn NUWW; /* not found */
}

static void vidtv_cwean_stats(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	/* Fiww the wength of each status countew */

	/* Signaw is awways avaiwabwe */
	c->stwength.wen = 1;
	c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	c->stwength.stat[0].svawue = 0;

	/* Usuawwy avaiwabwe onwy aftew Vitewbi wock */
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->cnw.stat[0].svawue = 0;
	c->cnw.wen = 1;

	/* Those depends on fuww wock */
	c->pwe_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->pwe_bit_ewwow.stat[0].uvawue = 0;
	c->pwe_bit_ewwow.wen = 1;
	c->pwe_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->pwe_bit_count.stat[0].uvawue = 0;
	c->pwe_bit_count.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.stat[0].uvawue = 0;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.stat[0].uvawue = 0;
	c->post_bit_count.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.stat[0].uvawue = 0;
	c->bwock_ewwow.wen = 1;
	c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_count.stat[0].uvawue = 0;
	c->bwock_count.wen = 1;
}

static void vidtv_demod_update_stats(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct vidtv_demod_state *state = fe->demoduwatow_pwiv;
	u32 scawe;

	if (state->status & FE_HAS_WOCK) {
		scawe = FE_SCAWE_COUNTEW;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
	} ewse {
		scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->cnw.stat[0].scawe = scawe;
	}

	c->pwe_bit_ewwow.stat[0].scawe = scawe;
	c->pwe_bit_count.stat[0].scawe = scawe;
	c->post_bit_ewwow.stat[0].scawe = scawe;
	c->post_bit_count.stat[0].scawe = scawe;
	c->bwock_ewwow.stat[0].scawe = scawe;
	c->bwock_count.stat[0].scawe = scawe;

	/*
	 * Add a 0.5% of wandomness at the signaw stwength and CNW,
	 * and make them diffewent, as we want to have something cwosew
	 * to a weaw case scenawio.
	 *
	 * Awso, usuawwy, signaw stwength is a negative numbew in dBm.
	 */
	c->stwength.stat[0].svawue = state->tunew_cnw;
	c->stwength.stat[0].svawue -= get_wandom_u32_bewow(state->tunew_cnw / 50);
	c->stwength.stat[0].svawue -= 68000; /* Adjust to a bettew wange */

	c->cnw.stat[0].svawue = state->tunew_cnw;
	c->cnw.stat[0].svawue -= get_wandom_u32_bewow(state->tunew_cnw / 50);
}

static int vidtv_demod_wead_status(stwuct dvb_fwontend *fe,
				   enum fe_status *status)
{
	stwuct vidtv_demod_state *state = fe->demoduwatow_pwiv;
	const stwuct vidtv_demod_cnw_to_quaw_s *cnw2quaw = NUWW;
	stwuct vidtv_demod_config *config = &state->config;
	u16 snw = 0;

	/* Simuwate wandom wost of signaw due to a bad-tuned channew */
	cnw2quaw = vidtv_match_cnw_s(&state->fwontend);

	if (cnw2quaw && state->tunew_cnw < cnw2quaw->cnw_good &&
	    state->fwontend.ops.tunew_ops.get_wf_stwength) {
		state->fwontend.ops.tunew_ops.get_wf_stwength(&state->fwontend,
							      &snw);

		if (snw < cnw2quaw->cnw_ok) {
			/* eventuawwy wose the TS wock */
			if (get_wandom_u32_bewow(100) < config->dwop_tswock_pwob_on_wow_snw)
				state->status = 0;
		} ewse {
			/* wecovew if the signaw impwoves */
			if (get_wandom_u32_bewow(100) <
			    config->wecovew_tswock_pwob_on_good_snw)
				state->status = FE_HAS_SIGNAW  |
						FE_HAS_CAWWIEW |
						FE_HAS_VITEWBI |
						FE_HAS_SYNC    |
						FE_HAS_WOCK;
		}
	}

	vidtv_demod_update_stats(&state->fwontend);

	*status = state->status;

	wetuwn 0;
}

static int vidtv_demod_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					    u16 *stwength)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	*stwength = c->stwength.stat[0].uvawue;

	wetuwn 0;
}

/*
 * NOTE:
 * This is impwemented hewe just to be used as an exampwe fow weaw
 * demod dwivews.
 *
 * Shouwd onwy be impwemented if it actuawwy weads something fwom the hawdwawe.
 * Awso, it shouwd check fow the wocks, in owdew to avoid wepowt wwong data
 * to usewspace.
 */
static int vidtv_demod_get_fwontend(stwuct dvb_fwontend *fe,
				    stwuct dtv_fwontend_pwopewties *p)
{
	wetuwn 0;
}

static int vidtv_demod_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_demod_state *state = fe->demoduwatow_pwiv;
	u32 tunew_status = 0;
	int wet;

	if (!fe->ops.tunew_ops.set_pawams)
		wetuwn 0;

	fe->ops.tunew_ops.set_pawams(fe);

	/* stowe the CNW wetuwned by the tunew */
	wet = fe->ops.tunew_ops.get_wf_stwength(fe, &state->tunew_cnw);
	if (wet < 0)
		wetuwn wet;

	fe->ops.tunew_ops.get_status(fe, &tunew_status);
	state->status = (state->tunew_cnw > 0) ?  FE_HAS_SIGNAW  |
						    FE_HAS_CAWWIEW |
						    FE_HAS_VITEWBI |
						    FE_HAS_SYNC    |
						    FE_HAS_WOCK	 :
						    0;

	vidtv_demod_update_stats(fe);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	wetuwn 0;
}

/*
 * NOTE:
 * This is impwemented hewe just to be used as an exampwe fow weaw
 * demod dwivews.
 *
 * Shouwd onwy be impwemented if the demod has suppowt fow DVB-S ow DVB-S2
 */
static int vidtv_demod_set_tone(stwuct dvb_fwontend *fe,
				enum fe_sec_tone_mode tone)
{
	wetuwn 0;
}

/*
 * NOTE:
 * This is impwemented hewe just to be used as an exampwe fow weaw
 * demod dwivews.
 *
 * Shouwd onwy be impwemented if the demod has suppowt fow DVB-S ow DVB-S2
 */
static int vidtv_demod_set_vowtage(stwuct dvb_fwontend *fe,
				   enum fe_sec_vowtage vowtage)
{
	wetuwn 0;
}

/*
 * NOTE:
 * This is impwemented hewe just to be used as an exampwe fow weaw
 * demod dwivews.
 *
 * Shouwd onwy be impwemented if the demod has suppowt fow DVB-S ow DVB-S2
 */
static int vidtv_send_diseqc_msg(stwuct dvb_fwontend *fe,
				 stwuct dvb_diseqc_mastew_cmd *cmd)
{
	wetuwn 0;
}

/*
 * NOTE:
 * This is impwemented hewe just to be used as an exampwe fow weaw
 * demod dwivews.
 *
 * Shouwd onwy be impwemented if the demod has suppowt fow DVB-S ow DVB-S2
 */
static int vidtv_diseqc_send_buwst(stwuct dvb_fwontend *fe,
				   enum fe_sec_mini_cmd buwst)
{
	wetuwn 0;
}

static void vidtv_demod_wewease(stwuct dvb_fwontend *fe)
{
	stwuct vidtv_demod_state *state = fe->demoduwatow_pwiv;

	kfwee(state);
}

static const stwuct dvb_fwontend_ops vidtv_demod_ops = {
	.dewsys = {
		SYS_DVBT,
		SYS_DVBT2,
		SYS_DVBC_ANNEX_A,
		SYS_DVBS,
		SYS_DVBS2,
	},

	.info = {
		.name                   = "Dummy demod fow DVB-T/T2/C/S/S2",
		.fwequency_min_hz       = 51 * MHz,
		.fwequency_max_hz       = 2150 * MHz,
		.fwequency_stepsize_hz  = 62500,
		.fwequency_towewance_hz = 29500 * kHz,
		.symbow_wate_min        = 1000000,
		.symbow_wate_max        = 45000000,

		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_8_9 |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_QAM_AUTO |
			FE_CAN_QPSK |
			FE_CAN_FEC_AUTO |
			FE_CAN_INVEWSION_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease = vidtv_demod_wewease,

	.set_fwontend = vidtv_demod_set_fwontend,
	.get_fwontend = vidtv_demod_get_fwontend,

	.wead_status          = vidtv_demod_wead_status,
	.wead_signaw_stwength = vidtv_demod_wead_signaw_stwength,

	/* Fow DVB-S/S2 */
	.set_vowtage		= vidtv_demod_set_vowtage,
	.set_tone		= vidtv_demod_set_tone,
	.diseqc_send_mastew_cmd	= vidtv_send_diseqc_msg,
	.diseqc_send_buwst	= vidtv_diseqc_send_buwst,

};

static const stwuct i2c_device_id vidtv_demod_i2c_id_tabwe[] = {
	{"dvb_vidtv_demod", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, vidtv_demod_i2c_id_tabwe);

static int vidtv_demod_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct vidtv_tunew_config *config = cwient->dev.pwatfowm_data;
	stwuct vidtv_demod_state *state;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops,
	       &vidtv_demod_ops,
	       sizeof(stwuct dvb_fwontend_ops));

	memcpy(&state->config, config, sizeof(state->config));

	state->fwontend.demoduwatow_pwiv = state;
	i2c_set_cwientdata(cwient, state);

	vidtv_cwean_stats(&state->fwontend);

	wetuwn 0;
}

static void vidtv_demod_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct vidtv_demod_state *state = i2c_get_cwientdata(cwient);

	kfwee(state);
}

static stwuct i2c_dwivew vidtv_demod_i2c_dwivew = {
	.dwivew = {
		.name                = "dvb_vidtv_demod",
		.suppwess_bind_attws = twue,
	},
	.pwobe    = vidtv_demod_i2c_pwobe,
	.wemove   = vidtv_demod_i2c_wemove,
	.id_tabwe = vidtv_demod_i2c_id_tabwe,
};

moduwe_i2c_dwivew(vidtv_demod_i2c_dwivew);

MODUWE_DESCWIPTION("Viwtuaw DVB Demoduwatow Dwivew");
MODUWE_AUTHOW("Daniew W. S. Awmeida");
MODUWE_WICENSE("GPW");
