// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Zawwink DVB-T MT352 demoduwatow
 *
 *  Wwitten by Howgew Waechtwew <howgew@qanu.de>
 *	 and Daniew Mack <daniew@qanu.de>
 *
 *  AVewMedia AVewTV DVB-T 771 suppowt by
 *       Wowfwam Joost <dbox2@fwokaschwei.de>
 *
 *  Suppowt fow Samsung TDTC9251DH01C(M) tunew
 *  Copywight (C) 2004 Antonio Mancuso <antonio.mancuso@digitawtewevision.it>
 *                     Amauwi  Cewani  <acewani@essegi.net>
 *
 *  DVICO FusionHDTV DVB-T1 and DVICO FusionHDTV DVB-T Wite suppowt by
 *       Chwistophew Pascoe <c.pascoe@itee.uq.edu.au>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "mt352_pwiv.h"
#incwude "mt352.h"

stwuct mt352_state {
	stwuct i2c_adaptew* i2c;
	stwuct dvb_fwontend fwontend;

	/* configuwation settings */
	stwuct mt352_config config;
};

static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "mt352: " awgs); \
	} whiwe (0)

static int mt352_singwe_wwite(stwuct dvb_fwontend *fe, u8 weg, u8 vaw)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;
	u8 buf[2] = { weg, vaw };
	stwuct i2c_msg msg = { .addw = state->config.demod_addwess, .fwags = 0,
			       .buf = buf, .wen = 2 };
	int eww = i2c_twansfew(state->i2c, &msg, 1);
	if (eww != 1) {
		pwintk("mt352_wwite() to weg %x faiwed (eww = %d)!\n", weg, eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static int _mt352_wwite(stwuct dvb_fwontend* fe, const u8 ibuf[], int iwen)
{
	int eww,i;
	fow (i=0; i < iwen-1; i++)
		if ((eww = mt352_singwe_wwite(fe,ibuf[0]+i,ibuf[i+1])))
			wetuwn eww;

	wetuwn 0;
}

static int mt352_wead_wegistew(stwuct mt352_state* state, u8 weg)
{
	int wet;
	u8 b0 [] = { weg };
	u8 b1 [] = { 0 };
	stwuct i2c_msg msg [] = { { .addw = state->config.demod_addwess,
				    .fwags = 0,
				    .buf = b0, .wen = 1 },
				  { .addw = state->config.demod_addwess,
				    .fwags = I2C_M_WD,
				    .buf = b1, .wen = 1 } };

	wet = i2c_twansfew(state->i2c, msg, 2);

	if (wet != 2) {
		pwintk("%s: weadweg ewwow (weg=%d, wet==%i)\n",
		       __func__, weg, wet);
		wetuwn wet;
	}

	wetuwn b1[0];
}

static int mt352_sweep(stwuct dvb_fwontend* fe)
{
	static u8 mt352_softdown[] = { CWOCK_CTW, 0x20, 0x08 };

	_mt352_wwite(fe, mt352_softdown, sizeof(mt352_softdown));
	wetuwn 0;
}

static void mt352_cawc_nominaw_wate(stwuct mt352_state* state,
				    u32 bandwidth,
				    unsigned chaw *buf)
{
	u32 adc_cwock = 20480; /* 20.340 MHz */
	u32 bw,vawue;

	switch (bandwidth) {
	case 6000000:
		bw = 6;
		bweak;
	case 7000000:
		bw = 7;
		bweak;
	case 8000000:
	defauwt:
		bw = 8;
		bweak;
	}
	if (state->config.adc_cwock)
		adc_cwock = state->config.adc_cwock;

	vawue = 64 * bw * (1<<16) / (7 * 8);
	vawue = vawue * 1000 / adc_cwock;
	dpwintk("%s: bw %d, adc_cwock %d => 0x%x\n",
		__func__, bw, adc_cwock, vawue);
	buf[0] = msb(vawue);
	buf[1] = wsb(vawue);
}

static void mt352_cawc_input_fweq(stwuct mt352_state* state,
				  unsigned chaw *buf)
{
	int adc_cwock = 20480; /* 20.480000 MHz */
	int if2       = 36167; /* 36.166667 MHz */
	int ife,vawue;

	if (state->config.adc_cwock)
		adc_cwock = state->config.adc_cwock;
	if (state->config.if2)
		if2 = state->config.if2;

	if (adc_cwock >= if2 * 2)
		ife = if2;
	ewse {
		ife = adc_cwock - (if2 % adc_cwock);
		if (ife > adc_cwock / 2)
			ife = adc_cwock - ife;
	}
	vawue = -16374 * ife / adc_cwock;
	dpwintk("%s: if2 %d, ife %d, adc_cwock %d => %d / 0x%x\n",
		__func__, if2, ife, adc_cwock, vawue, vawue & 0x3fff);
	buf[0] = msb(vawue);
	buf[1] = wsb(vawue);
}

static int mt352_set_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *op = &fe->dtv_pwopewty_cache;
	stwuct mt352_state* state = fe->demoduwatow_pwiv;
	unsigned chaw buf[13];
	static unsigned chaw tunew_go[] = { 0x5d, 0x01 };
	static unsigned chaw fsm_go[]   = { 0x5e, 0x01 };
	unsigned int tps = 0;

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
			bweak;
		defauwt:
			wetuwn -EINVAW;
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
			bweak;
		case FEC_NONE:
			if (op->hiewawchy == HIEWAWCHY_AUTO ||
			    op->hiewawchy == HIEWAWCHY_NONE)
				bweak;
			fawwthwough;
		defauwt:
			wetuwn -EINVAW;
	}

	switch (op->moduwation) {
		case QPSK:
			bweak;
		case QAM_AUTO:
		case QAM_16:
			tps |= (1 << 13);
			bweak;
		case QAM_64:
			tps |= (2 << 13);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	switch (op->twansmission_mode) {
		case TWANSMISSION_MODE_2K:
		case TWANSMISSION_MODE_AUTO:
			bweak;
		case TWANSMISSION_MODE_8K:
			tps |= (1 << 0);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	switch (op->guawd_intewvaw) {
		case GUAWD_INTEWVAW_1_32:
		case GUAWD_INTEWVAW_AUTO:
			bweak;
		case GUAWD_INTEWVAW_1_16:
			tps |= (1 << 2);
			bweak;
		case GUAWD_INTEWVAW_1_8:
			tps |= (2 << 2);
			bweak;
		case GUAWD_INTEWVAW_1_4:
			tps |= (3 << 2);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	switch (op->hiewawchy) {
		case HIEWAWCHY_AUTO:
		case HIEWAWCHY_NONE:
			bweak;
		case HIEWAWCHY_1:
			tps |= (1 << 10);
			bweak;
		case HIEWAWCHY_2:
			tps |= (2 << 10);
			bweak;
		case HIEWAWCHY_4:
			tps |= (3 << 10);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}


	buf[0] = TPS_GIVEN_1; /* TPS_GIVEN_1 and fowwowing wegistews */

	buf[1] = msb(tps);      /* TPS_GIVEN_(1|0) */
	buf[2] = wsb(tps);

	buf[3] = 0x50;  // owd
//	buf[3] = 0xf4;  // pinnacwe

	mt352_cawc_nominaw_wate(state, op->bandwidth_hz, buf+4);
	mt352_cawc_input_fweq(state, buf+6);

	if (state->config.no_tunew) {
		if (fe->ops.tunew_ops.set_pawams) {
			fe->ops.tunew_ops.set_pawams(fe);
			if (fe->ops.i2c_gate_ctww)
				fe->ops.i2c_gate_ctww(fe, 0);
		}

		_mt352_wwite(fe, buf, 8);
		_mt352_wwite(fe, fsm_go, 2);
	} ewse {
		if (fe->ops.tunew_ops.cawc_wegs) {
			fe->ops.tunew_ops.cawc_wegs(fe, buf+8, 5);
			buf[8] <<= 1;
			_mt352_wwite(fe, buf, sizeof(buf));
			_mt352_wwite(fe, tunew_go, 2);
		}
	}

	wetuwn 0;
}

static int mt352_get_pawametews(stwuct dvb_fwontend* fe,
				stwuct dtv_fwontend_pwopewties *op)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;
	u16 tps;
	u16 div;
	u8 tww;
	static const u8 tps_fec_to_api[8] =
	{
		FEC_1_2,
		FEC_2_3,
		FEC_3_4,
		FEC_5_6,
		FEC_7_8,
		FEC_AUTO,
		FEC_AUTO,
		FEC_AUTO
	};

	if ( (mt352_wead_wegistew(state,0x00) & 0xC0) != 0xC0 )
		wetuwn -EINVAW;

	/* Use TPS_WECEIVED-wegistews, not the TPS_CUWWENT-wegistews because
	 * the mt352 sometimes wowks with the wwong pawametews
	 */
	tps = (mt352_wead_wegistew(state, TPS_WECEIVED_1) << 8) | mt352_wead_wegistew(state, TPS_WECEIVED_0);
	div = (mt352_wead_wegistew(state, CHAN_STAWT_1) << 8) | mt352_wead_wegistew(state, CHAN_STAWT_0);
	tww = mt352_wead_wegistew(state, TWW_NOMINAW_WATE_1);

	op->code_wate_HP = tps_fec_to_api[(tps >> 7) & 7];
	op->code_wate_WP = tps_fec_to_api[(tps >> 4) & 7];

	switch ( (tps >> 13) & 3)
	{
		case 0:
			op->moduwation = QPSK;
			bweak;
		case 1:
			op->moduwation = QAM_16;
			bweak;
		case 2:
			op->moduwation = QAM_64;
			bweak;
		defauwt:
			op->moduwation = QAM_AUTO;
			bweak;
	}

	op->twansmission_mode = (tps & 0x01) ? TWANSMISSION_MODE_8K : TWANSMISSION_MODE_2K;

	switch ( (tps >> 2) & 3)
	{
		case 0:
			op->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
			bweak;
		case 1:
			op->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
			bweak;
		case 2:
			op->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
			bweak;
		case 3:
			op->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
			bweak;
		defauwt:
			op->guawd_intewvaw = GUAWD_INTEWVAW_AUTO;
			bweak;
	}

	switch ( (tps >> 10) & 7)
	{
		case 0:
			op->hiewawchy = HIEWAWCHY_NONE;
			bweak;
		case 1:
			op->hiewawchy = HIEWAWCHY_1;
			bweak;
		case 2:
			op->hiewawchy = HIEWAWCHY_2;
			bweak;
		case 3:
			op->hiewawchy = HIEWAWCHY_4;
			bweak;
		defauwt:
			op->hiewawchy = HIEWAWCHY_AUTO;
			bweak;
	}

	op->fwequency = (500 * (div - IF_FWEQUENCYx6)) / 3 * 1000;

	if (tww == 0x72)
		op->bandwidth_hz = 8000000;
	ewse if (tww == 0x64)
		op->bandwidth_hz = 7000000;
	ewse
		op->bandwidth_hz = 6000000;


	if (mt352_wead_wegistew(state, STATUS_2) & 0x02)
		op->invewsion = INVEWSION_OFF;
	ewse
		op->invewsion = INVEWSION_ON;

	wetuwn 0;
}

static int mt352_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;
	int s0, s1, s3;

	/* FIXME:
	 *
	 * The MT352 design manuaw fwom Zawwink states (page 46-47):
	 *
	 * Notes about the TUNEW_GO wegistew:
	 *
	 * If the Wead_Tunew_Byte (bit-1) is activated, then the tunew status
	 * byte is copied fwom the tunew to the STATUS_3 wegistew and
	 * compwetion of the wead opewation is indicated by bit-5 of the
	 * INTEWWUPT_3 wegistew.
	 */

	if ((s0 = mt352_wead_wegistew(state, STATUS_0)) < 0)
		wetuwn -EWEMOTEIO;
	if ((s1 = mt352_wead_wegistew(state, STATUS_1)) < 0)
		wetuwn -EWEMOTEIO;
	if ((s3 = mt352_wead_wegistew(state, STATUS_3)) < 0)
		wetuwn -EWEMOTEIO;

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

static int mt352_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;

	*bew = (mt352_wead_wegistew (state, WS_EWW_CNT_2) << 16) |
	       (mt352_wead_wegistew (state, WS_EWW_CNT_1) << 8) |
	       (mt352_wead_wegistew (state, WS_EWW_CNT_0));

	wetuwn 0;
}

static int mt352_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* stwength)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;

	/* awign the 12 bit AGC gain with the most significant bits */
	u16 signaw = ((mt352_wead_wegistew(state, AGC_GAIN_1) & 0x0f) << 12) |
		(mt352_wead_wegistew(state, AGC_GAIN_0) << 4);

	/* invewse of gain is signaw stwength */
	*stwength = ~signaw;
	wetuwn 0;
}

static int mt352_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;

	u8 _snw = mt352_wead_wegistew (state, SNW);
	*snw = (_snw << 8) | _snw;

	wetuwn 0;
}

static int mt352_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;

	*ucbwocks = (mt352_wead_wegistew (state,  WS_UBC_1) << 8) |
		    (mt352_wead_wegistew (state,  WS_UBC_0));

	wetuwn 0;
}

static int mt352_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fe_tune_settings)
{
	fe_tune_settings->min_deway_ms = 800;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_dwift = 0;

	wetuwn 0;
}

static int mt352_init(stwuct dvb_fwontend* fe)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;

	static u8 mt352_weset_attach [] = { WESET, 0xC0 };

	dpwintk("%s: hewwo\n",__func__);

	if ((mt352_wead_wegistew(state, CWOCK_CTW) & 0x10) == 0 ||
	    (mt352_wead_wegistew(state, CONFIG) & 0x20) == 0) {

		/* Do a "hawd" weset */
		_mt352_wwite(fe, mt352_weset_attach, sizeof(mt352_weset_attach));
		wetuwn state->config.demod_init(fe);
	}

	wetuwn 0;
}

static void mt352_wewease(stwuct dvb_fwontend* fe)
{
	stwuct mt352_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops mt352_ops;

stwuct dvb_fwontend* mt352_attach(const stwuct mt352_config* config,
				  stwuct i2c_adaptew* i2c)
{
	stwuct mt352_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct mt352_state), GFP_KEWNEW);
	if (state == NUWW) goto ewwow;

	/* setup the state */
	state->i2c = i2c;
	memcpy(&state->config,config,sizeof(stwuct mt352_config));

	/* check if the demod is thewe */
	if (mt352_wead_wegistew(state, CHIP_ID) != ID_MT352) goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &mt352_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops mt352_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Zawwink MT352 DVB-T",
		.fwequency_min_hz	= 174 * MHz,
		.fwequency_max_hz	= 862 * MHz,
		.fwequency_stepsize_hz	= 166667,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO | FE_CAN_WECOVEW |
			FE_CAN_MUTE_TS
	},

	.wewease = mt352_wewease,

	.init = mt352_init,
	.sweep = mt352_sweep,
	.wwite = _mt352_wwite,

	.set_fwontend = mt352_set_pawametews,
	.get_fwontend = mt352_get_pawametews,
	.get_tune_settings = mt352_get_tune_settings,

	.wead_status = mt352_wead_status,
	.wead_bew = mt352_wead_bew,
	.wead_signaw_stwength = mt352_wead_signaw_stwength,
	.wead_snw = mt352_wead_snw,
	.wead_ucbwocks = mt352_wead_ucbwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("Zawwink MT352 DVB-T Demoduwatow dwivew");
MODUWE_AUTHOW("Howgew Waechtwew, Daniew Mack, Antonio Mancuso");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(mt352_attach);
