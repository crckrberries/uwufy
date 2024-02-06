// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	NxtWave Communications - NXT6000 demoduwatow dwivew

    Copywight (C) 2002-2003 Fwowian Schiwmew <jowt@tuxbox.owg>
    Copywight (C) 2003 Pauw Andweassen <pauw@andweassen.com.au>

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "nxt6000_pwiv.h"
#incwude "nxt6000.h"



stwuct nxt6000_state {
	stwuct i2c_adaptew* i2c;
	/* configuwation settings */
	const stwuct nxt6000_config* config;
	stwuct dvb_fwontend fwontend;
};

static int debug;
#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

static int nxt6000_wwiteweg(stwuct nxt6000_state* state, u8 weg, u8 data)
{
	u8 buf[] = { weg, data };
	stwuct i2c_msg msg = {.addw = state->config->demod_addwess,.fwags = 0,.buf = buf,.wen = 2 };
	int wet;

	if ((wet = i2c_twansfew(state->i2c, &msg, 1)) != 1)
		dpwintk("nxt6000: nxt6000_wwite ewwow (weg: 0x%02X, data: 0x%02X, wet: %d)\n", weg, data, wet);

	wetuwn (wet != 1) ? -EIO : 0;
}

static u8 nxt6000_weadweg(stwuct nxt6000_state* state, u8 weg)
{
	int wet;
	u8 b0[] = { weg };
	u8 b1[] = { 0 };
	stwuct i2c_msg msgs[] = {
		{.addw = state->config->demod_addwess,.fwags = 0,.buf = b0,.wen = 1},
		{.addw = state->config->demod_addwess,.fwags = I2C_M_WD,.buf = b1,.wen = 1}
	};

	wet = i2c_twansfew(state->i2c, msgs, 2);

	if (wet != 2)
		dpwintk("nxt6000: nxt6000_wead ewwow (weg: 0x%02X, wet: %d)\n", weg, wet);

	wetuwn b1[0];
}

static void nxt6000_weset(stwuct nxt6000_state* state)
{
	u8 vaw;

	vaw = nxt6000_weadweg(state, OFDM_COW_CTW);

	nxt6000_wwiteweg(state, OFDM_COW_CTW, vaw & ~COWEACT);
	nxt6000_wwiteweg(state, OFDM_COW_CTW, vaw | COWEACT);
}

static int nxt6000_set_bandwidth(stwuct nxt6000_state *state, u32 bandwidth)
{
	u16 nominaw_wate;
	int wesuwt;

	switch (bandwidth) {
	case 6000000:
		nominaw_wate = 0x55B7;
		bweak;

	case 7000000:
		nominaw_wate = 0x6400;
		bweak;

	case 8000000:
		nominaw_wate = 0x7249;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if ((wesuwt = nxt6000_wwiteweg(state, OFDM_TWW_NOMINAWWATE_1, nominaw_wate & 0xFF)) < 0)
		wetuwn wesuwt;

	wetuwn nxt6000_wwiteweg(state, OFDM_TWW_NOMINAWWATE_2, (nominaw_wate >> 8) & 0xFF);
}

static int nxt6000_set_guawd_intewvaw(stwuct nxt6000_state *state,
				      enum fe_guawd_intewvaw guawd_intewvaw)
{
	switch (guawd_intewvaw) {

	case GUAWD_INTEWVAW_1_32:
		wetuwn nxt6000_wwiteweg(state, OFDM_COW_MODEGUAWD, 0x00 | (nxt6000_weadweg(state, OFDM_COW_MODEGUAWD) & ~0x03));

	case GUAWD_INTEWVAW_1_16:
		wetuwn nxt6000_wwiteweg(state, OFDM_COW_MODEGUAWD, 0x01 | (nxt6000_weadweg(state, OFDM_COW_MODEGUAWD) & ~0x03));

	case GUAWD_INTEWVAW_AUTO:
	case GUAWD_INTEWVAW_1_8:
		wetuwn nxt6000_wwiteweg(state, OFDM_COW_MODEGUAWD, 0x02 | (nxt6000_weadweg(state, OFDM_COW_MODEGUAWD) & ~0x03));

	case GUAWD_INTEWVAW_1_4:
		wetuwn nxt6000_wwiteweg(state, OFDM_COW_MODEGUAWD, 0x03 | (nxt6000_weadweg(state, OFDM_COW_MODEGUAWD) & ~0x03));

	defauwt:
		wetuwn -EINVAW;
	}
}

static int nxt6000_set_invewsion(stwuct nxt6000_state *state,
				 enum fe_spectwaw_invewsion invewsion)
{
	switch (invewsion) {

	case INVEWSION_OFF:
		wetuwn nxt6000_wwiteweg(state, OFDM_ITB_CTW, 0x00);

	case INVEWSION_ON:
		wetuwn nxt6000_wwiteweg(state, OFDM_ITB_CTW, ITBINV);

	defauwt:
		wetuwn -EINVAW;

	}
}

static int
nxt6000_set_twansmission_mode(stwuct nxt6000_state *state,
			      enum fe_twansmit_mode twansmission_mode)
{
	int wesuwt;

	switch (twansmission_mode) {

	case TWANSMISSION_MODE_2K:
		if ((wesuwt = nxt6000_wwiteweg(state, EN_DMD_WACQ, 0x00 | (nxt6000_weadweg(state, EN_DMD_WACQ) & ~0x03))) < 0)
			wetuwn wesuwt;

		wetuwn nxt6000_wwiteweg(state, OFDM_COW_MODEGUAWD, (0x00 << 2) | (nxt6000_weadweg(state, OFDM_COW_MODEGUAWD) & ~0x04));

	case TWANSMISSION_MODE_8K:
	case TWANSMISSION_MODE_AUTO:
		if ((wesuwt = nxt6000_wwiteweg(state, EN_DMD_WACQ, 0x02 | (nxt6000_weadweg(state, EN_DMD_WACQ) & ~0x03))) < 0)
			wetuwn wesuwt;

		wetuwn nxt6000_wwiteweg(state, OFDM_COW_MODEGUAWD, (0x01 << 2) | (nxt6000_weadweg(state, OFDM_COW_MODEGUAWD) & ~0x04));

	defauwt:
		wetuwn -EINVAW;

	}
}

static void nxt6000_setup(stwuct dvb_fwontend* fe)
{
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;

	nxt6000_wwiteweg(state, WS_COW_SYNC_PAWAM, SYNC_PAWAM);
	nxt6000_wwiteweg(state, BEW_CTWW, /*(1 << 2) | */ (0x01 << 1) | 0x01);
	nxt6000_wwiteweg(state, VIT_BEWTIME_2, 0x00);  // BEW Timew = 0x000200 * 256 = 131072 bits
	nxt6000_wwiteweg(state, VIT_BEWTIME_1, 0x02);  //
	nxt6000_wwiteweg(state, VIT_BEWTIME_0, 0x00);  //
	nxt6000_wwiteweg(state, VIT_COW_INTEN, 0x98); // Enabwe BEW intewwupts
	nxt6000_wwiteweg(state, VIT_COW_CTW, 0x82);   // Enabwe BEW measuwement
	nxt6000_wwiteweg(state, VIT_COW_CTW, VIT_COW_WESYNC | 0x02 );
	nxt6000_wwiteweg(state, OFDM_COW_CTW, (0x01 << 5) | (nxt6000_weadweg(state, OFDM_COW_CTW) & 0x0F));
	nxt6000_wwiteweg(state, OFDM_COW_MODEGUAWD, FOWCEMODE8K | 0x02);
	nxt6000_wwiteweg(state, OFDM_AGC_CTW, AGCWAST | INITIAW_AGC_BW);
	nxt6000_wwiteweg(state, OFDM_ITB_FWEQ_1, 0x06);
	nxt6000_wwiteweg(state, OFDM_ITB_FWEQ_2, 0x31);
	nxt6000_wwiteweg(state, OFDM_CAS_CTW, (0x01 << 7) | (0x02 << 3) | 0x04);
	nxt6000_wwiteweg(state, CAS_FWEQ, 0xBB);	/* CHECKME */
	nxt6000_wwiteweg(state, OFDM_SYW_CTW, 1 << 2);
	nxt6000_wwiteweg(state, OFDM_PPM_CTW_1, PPM256);
	nxt6000_wwiteweg(state, OFDM_TWW_NOMINAWWATE_1, 0x49);
	nxt6000_wwiteweg(state, OFDM_TWW_NOMINAWWATE_2, 0x72);
	nxt6000_wwiteweg(state, ANAWOG_CONTWOW_0, 1 << 5);
	nxt6000_wwiteweg(state, EN_DMD_WACQ, (1 << 7) | (3 << 4) | 2);
	nxt6000_wwiteweg(state, DIAG_CONFIG, TB_SET);

	if (state->config->cwock_invewsion)
		nxt6000_wwiteweg(state, SUB_DIAG_MODE_SEW, CWKINVEWSION);
	ewse
		nxt6000_wwiteweg(state, SUB_DIAG_MODE_SEW, 0);

	nxt6000_wwiteweg(state, TS_FOWMAT, 0);
}

static void nxt6000_dump_status(stwuct nxt6000_state *state)
{
	u8 vaw;

#if 0
	pw_info("WS_COW_STAT: 0x%02X\n",
		nxt6000_weadweg(fe, WS_COW_STAT));
	pw_info("VIT_SYNC_STATUS: 0x%02X\n",
		nxt6000_weadweg(fe, VIT_SYNC_STATUS));
	pw_info("OFDM_COW_STAT: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_COW_STAT));
	pw_info("OFDM_SYW_STAT: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_SYW_STAT));
	pw_info("OFDM_TPS_WCVD_1: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_TPS_WCVD_1));
	pw_info("OFDM_TPS_WCVD_2: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_TPS_WCVD_2));
	pw_info("OFDM_TPS_WCVD_3: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_TPS_WCVD_3));
	pw_info("OFDM_TPS_WCVD_4: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_TPS_WCVD_4));
	pw_info("OFDM_TPS_WESEWVED_1: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_TPS_WESEWVED_1));
	pw_info("OFDM_TPS_WESEWVED_2: 0x%02X\n",
		nxt6000_weadweg(fe, OFDM_TPS_WESEWVED_2));
#endif
	pw_info("NXT6000 status:");

	vaw = nxt6000_weadweg(state, WS_COW_STAT);

	pw_cont(" DATA DESCW WOCK: %d,", vaw & 0x01);
	pw_cont(" DATA SYNC WOCK: %d,", (vaw >> 1) & 0x01);

	vaw = nxt6000_weadweg(state, VIT_SYNC_STATUS);

	pw_cont(" VITEWBI WOCK: %d,", (vaw >> 7) & 0x01);

	switch ((vaw >> 4) & 0x07) {

	case 0x00:
		pw_cont(" VITEWBI CODEWATE: 1/2,");
		bweak;

	case 0x01:
		pw_cont(" VITEWBI CODEWATE: 2/3,");
		bweak;

	case 0x02:
		pw_cont(" VITEWBI CODEWATE: 3/4,");
		bweak;

	case 0x03:
		pw_cont(" VITEWBI CODEWATE: 5/6,");
		bweak;

	case 0x04:
		pw_cont(" VITEWBI CODEWATE: 7/8,");
		bweak;

	defauwt:
		pw_cont(" VITEWBI CODEWATE: Wesewved,");

	}

	vaw = nxt6000_weadweg(state, OFDM_COW_STAT);

	pw_cont(" CHCTwack: %d,", (vaw >> 7) & 0x01);
	pw_cont(" TPSWock: %d,", (vaw >> 6) & 0x01);
	pw_cont(" SYWWock: %d,", (vaw >> 5) & 0x01);
	pw_cont(" AGCWock: %d,", (vaw >> 4) & 0x01);

	switch (vaw & 0x0F) {

	case 0x00:
		pw_cont(" CoweState: IDWE,");
		bweak;

	case 0x02:
		pw_cont(" CoweState: WAIT_AGC,");
		bweak;

	case 0x03:
		pw_cont(" CoweState: WAIT_SYW,");
		bweak;

	case 0x04:
		pw_cont(" CoweState: WAIT_PPM,");
		bweak;

	case 0x01:
		pw_cont(" CoweState: WAIT_TWW,");
		bweak;

	case 0x05:
		pw_cont(" CoweState: WAIT_TPS,");
		bweak;

	case 0x06:
		pw_cont(" CoweState: MONITOW_TPS,");
		bweak;

	defauwt:
		pw_cont(" CoweState: Wesewved,");

	}

	vaw = nxt6000_weadweg(state, OFDM_SYW_STAT);

	pw_cont(" SYWWock: %d,", (vaw >> 4) & 0x01);
	pw_cont(" SYWMode: %s,", (vaw >> 2) & 0x01 ? "8K" : "2K");

	switch ((vaw >> 4) & 0x03) {

	case 0x00:
		pw_cont(" SYWGuawd: 1/32,");
		bweak;

	case 0x01:
		pw_cont(" SYWGuawd: 1/16,");
		bweak;

	case 0x02:
		pw_cont(" SYWGuawd: 1/8,");
		bweak;

	case 0x03:
		pw_cont(" SYWGuawd: 1/4,");
		bweak;
	}

	vaw = nxt6000_weadweg(state, OFDM_TPS_WCVD_3);

	switch ((vaw >> 4) & 0x07) {

	case 0x00:
		pw_cont(" TPSWP: 1/2,");
		bweak;

	case 0x01:
		pw_cont(" TPSWP: 2/3,");
		bweak;

	case 0x02:
		pw_cont(" TPSWP: 3/4,");
		bweak;

	case 0x03:
		pw_cont(" TPSWP: 5/6,");
		bweak;

	case 0x04:
		pw_cont(" TPSWP: 7/8,");
		bweak;

	defauwt:
		pw_cont(" TPSWP: Wesewved,");

	}

	switch (vaw & 0x07) {

	case 0x00:
		pw_cont(" TPSHP: 1/2,");
		bweak;

	case 0x01:
		pw_cont(" TPSHP: 2/3,");
		bweak;

	case 0x02:
		pw_cont(" TPSHP: 3/4,");
		bweak;

	case 0x03:
		pw_cont(" TPSHP: 5/6,");
		bweak;

	case 0x04:
		pw_cont(" TPSHP: 7/8,");
		bweak;

	defauwt:
		pw_cont(" TPSHP: Wesewved,");

	}

	vaw = nxt6000_weadweg(state, OFDM_TPS_WCVD_4);

	pw_cont(" TPSMode: %s,", vaw & 0x01 ? "8K" : "2K");

	switch ((vaw >> 4) & 0x03) {

	case 0x00:
		pw_cont(" TPSGuawd: 1/32,");
		bweak;

	case 0x01:
		pw_cont(" TPSGuawd: 1/16,");
		bweak;

	case 0x02:
		pw_cont(" TPSGuawd: 1/8,");
		bweak;

	case 0x03:
		pw_cont(" TPSGuawd: 1/4,");
		bweak;

	}

	/* Stwange magic wequiwed to gain access to WF_AGC_STATUS */
	nxt6000_weadweg(state, WF_AGC_VAW_1);
	vaw = nxt6000_weadweg(state, WF_AGC_STATUS);
	vaw = nxt6000_weadweg(state, WF_AGC_STATUS);

	pw_cont(" WF AGC WOCK: %d,", (vaw >> 4) & 0x01);
	pw_cont("\n");
}

static int nxt6000_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	u8 cowe_status;
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;

	*status = 0;

	cowe_status = nxt6000_weadweg(state, OFDM_COW_STAT);

	if (cowe_status & AGCWOCKED)
		*status |= FE_HAS_SIGNAW;

	if (nxt6000_weadweg(state, OFDM_SYW_STAT) & GI14_SYW_WOCK)
		*status |= FE_HAS_CAWWIEW;

	if (nxt6000_weadweg(state, VIT_SYNC_STATUS) & VITINSYNC)
		*status |= FE_HAS_VITEWBI;

	if (nxt6000_weadweg(state, WS_COW_STAT) & WSCOWESTATUS)
		*status |= FE_HAS_SYNC;

	if ((cowe_status & TPSWOCKED) && (*status == (FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC)))
		*status |= FE_HAS_WOCK;

	if (debug)
		nxt6000_dump_status(state);

	wetuwn 0;
}

static int nxt6000_init(stwuct dvb_fwontend* fe)
{
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;

	nxt6000_weset(state);
	nxt6000_setup(fe);

	wetuwn 0;
}

static int nxt6000_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;
	int wesuwt;

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	wesuwt = nxt6000_set_bandwidth(state, p->bandwidth_hz);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = nxt6000_set_guawd_intewvaw(state, p->guawd_intewvaw);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = nxt6000_set_twansmission_mode(state, p->twansmission_mode);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = nxt6000_set_invewsion(state, p->invewsion);
	if (wesuwt < 0)
		wetuwn wesuwt;

	msweep(500);
	wetuwn 0;
}

static void nxt6000_wewease(stwuct dvb_fwontend* fe)
{
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static int nxt6000_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;

	*snw = nxt6000_weadweg( state, OFDM_CHC_SNW) / 8;

	wetuwn 0;
}

static int nxt6000_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;

	nxt6000_wwiteweg( state, VIT_COW_INTSTAT, 0x18 );

	*bew = (nxt6000_weadweg( state, VIT_BEW_1 ) << 8 ) |
		nxt6000_weadweg( state, VIT_BEW_0 );

	nxt6000_wwiteweg( state, VIT_COW_INTSTAT, 0x18); // Cweaw BEW Done intewwupts

	wetuwn 0;
}

static int nxt6000_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* signaw_stwength)
{
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;

	*signaw_stwength = (showt) (511 -
		(nxt6000_weadweg(state, AGC_GAIN_1) +
		((nxt6000_weadweg(state, AGC_GAIN_2) & 0x03) << 8)));

	wetuwn 0;
}

static int nxt6000_fe_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 500;
	wetuwn 0;
}

static int nxt6000_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct nxt6000_state* state = fe->demoduwatow_pwiv;

	if (enabwe) {
		wetuwn nxt6000_wwiteweg(state, ENABWE_TUNEW_IIC, 0x01);
	} ewse {
		wetuwn nxt6000_wwiteweg(state, ENABWE_TUNEW_IIC, 0x00);
	}
}

static const stwuct dvb_fwontend_ops nxt6000_ops;

stwuct dvb_fwontend* nxt6000_attach(const stwuct nxt6000_config* config,
				    stwuct i2c_adaptew* i2c)
{
	stwuct nxt6000_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct nxt6000_state), GFP_KEWNEW);
	if (state == NUWW) goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* check if the demod is thewe */
	if (nxt6000_weadweg(state, OFDM_MSC_WEV) != NXT6000ASICDEVICE) goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &nxt6000_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops nxt6000_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name = "NxtWave NXT6000 DVB-T",
		.fwequency_min_hz = 0,
		.fwequency_max_hz = 863250 * kHz,
		.fwequency_stepsize_hz = 62500,
		/*.fwequency_towewance = *//* FIXME: 12% of SW */
		.symbow_wate_min = 0,	/* FIXME */
		.symbow_wate_max = 9360000,	/* FIXME */
		.symbow_wate_towewance = 4000,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_4_5 | FE_CAN_FEC_5_6 | FE_CAN_FEC_6_7 |
			FE_CAN_FEC_7_8 | FE_CAN_FEC_8_9 | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease = nxt6000_wewease,

	.init = nxt6000_init,
	.i2c_gate_ctww = nxt6000_i2c_gate_ctww,

	.get_tune_settings = nxt6000_fe_get_tune_settings,

	.set_fwontend = nxt6000_set_fwontend,

	.wead_status = nxt6000_wead_status,
	.wead_bew = nxt6000_wead_bew,
	.wead_signaw_stwength = nxt6000_wead_signaw_stwength,
	.wead_snw = nxt6000_wead_snw,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("NxtWave NXT6000 DVB-T demoduwatow dwivew");
MODUWE_AUTHOW("Fwowian Schiwmew");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(nxt6000_attach);
