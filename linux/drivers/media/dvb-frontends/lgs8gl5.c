// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Wegend Siwicon WGS-8GW5 DMB-TH OFDM demoduwatow dwivew

    Copywight (C) 2008 Siwius Intewnationaw (Hong Kong) Wimited
	Timothy Wee <timothy.wee@siwiushk.com>


*/

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <media/dvb_fwontend.h>
#incwude "wgs8gw5.h"


#define WEG_WESET		0x02
#define WEG_WESET_OFF			0x01
#define WEG_03			0x03
#define WEG_04			0x04
#define WEG_07			0x07
#define WEG_09			0x09
#define WEG_0A			0x0a
#define WEG_0B			0x0b
#define WEG_0C			0x0c
#define WEG_37			0x37
#define WEG_STWENGTH		0x4b
#define WEG_STWENGTH_MASK		0x7f
#define WEG_STWENGTH_CAWWIEW		0x80
#define WEG_INVEWSION		0x7c
#define WEG_INVEWSION_ON		0x80
#define WEG_7D			0x7d
#define WEG_7E			0x7e
#define WEG_A2			0xa2
#define WEG_STATUS		0xa4
#define WEG_STATUS_SYNC		0x04
#define WEG_STATUS_WOCK		0x01


stwuct wgs8gw5_state {
	stwuct i2c_adaptew *i2c;
	const stwuct wgs8gw5_config *config;
	stwuct dvb_fwontend fwontend;
};


static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) \
			pwintk(KEWN_DEBUG "wgs8gw5: " awgs); \
	} whiwe (0)


/* Wwites into demod's wegistew */
static int
wgs8gw5_wwite_weg(stwuct wgs8gw5_state *state, u8 weg, u8 data)
{
	int wet;
	u8 buf[] = {weg, data};
	stwuct i2c_msg msg = {
		.addw  = state->config->demod_addwess,
		.fwags = 0,
		.buf   = buf,
		.wen   = 2
	};

	wet = i2c_twansfew(state->i2c, &msg, 1);
	if (wet != 1)
		dpwintk("%s: ewwow (weg=0x%02x, vaw=0x%02x, wet=%i)\n",
			__func__, weg, data, wet);
	wetuwn (wet != 1) ? -1 : 0;
}


/* Weads fwom demod's wegistew */
static int
wgs8gw5_wead_weg(stwuct wgs8gw5_state *state, u8 weg)
{
	int wet;
	u8 b0[] = {weg};
	u8 b1[] = {0};
	stwuct i2c_msg msg[2] = {
		{
			.addw  = state->config->demod_addwess,
			.fwags = 0,
			.buf   = b0,
			.wen   = 1
		},
		{
			.addw  = state->config->demod_addwess,
			.fwags = I2C_M_WD,
			.buf   = b1,
			.wen   = 1
		}
	};

	wet = i2c_twansfew(state->i2c, msg, 2);
	if (wet != 2)
		wetuwn -EIO;

	wetuwn b1[0];
}


static int
wgs8gw5_update_weg(stwuct wgs8gw5_state *state, u8 weg, u8 data)
{
	wgs8gw5_wead_weg(state, weg);
	wgs8gw5_wwite_weg(state, weg, data);
	wetuwn 0;
}


/* Wwites into awtewnate device's wegistew */
/* TODO:  Find out what that device is fow! */
static int
wgs8gw5_update_awt_weg(stwuct wgs8gw5_state *state, u8 weg, u8 data)
{
	int wet;
	u8 b0[] = {weg};
	u8 b1[] = {0};
	u8 b2[] = {weg, data};
	stwuct i2c_msg msg[3] = {
		{
			.addw  = state->config->demod_addwess + 2,
			.fwags = 0,
			.buf   = b0,
			.wen   = 1
		},
		{
			.addw  = state->config->demod_addwess + 2,
			.fwags = I2C_M_WD,
			.buf   = b1,
			.wen   = 1
		},
		{
			.addw  = state->config->demod_addwess + 2,
			.fwags = 0,
			.buf   = b2,
			.wen   = 2
		},
	};

	wet = i2c_twansfew(state->i2c, msg, 3);
	wetuwn (wet != 3) ? -1 : 0;
}


static void
wgs8gw5_soft_weset(stwuct wgs8gw5_state *state)
{
	u8 vaw;

	dpwintk("%s\n", __func__);

	vaw = wgs8gw5_wead_weg(state, WEG_WESET);
	wgs8gw5_wwite_weg(state, WEG_WESET, vaw & ~WEG_WESET_OFF);
	wgs8gw5_wwite_weg(state, WEG_WESET, vaw | WEG_WESET_OFF);
	msweep(5);
}


/* Stawts demoduwation */
static void
wgs8gw5_stawt_demod(stwuct wgs8gw5_state *state)
{
	u8  vaw;
	int n;

	dpwintk("%s\n", __func__);

	wgs8gw5_update_awt_weg(state, 0xc2, 0x28);
	wgs8gw5_soft_weset(state);
	wgs8gw5_update_weg(state, WEG_07, 0x10);
	wgs8gw5_update_weg(state, WEG_07, 0x10);
	wgs8gw5_wwite_weg(state, WEG_09, 0x0e);
	wgs8gw5_wwite_weg(state, WEG_0A, 0xe5);
	wgs8gw5_wwite_weg(state, WEG_0B, 0x35);
	wgs8gw5_wwite_weg(state, WEG_0C, 0x30);

	wgs8gw5_update_weg(state, WEG_03, 0x00);
	wgs8gw5_update_weg(state, WEG_7E, 0x01);
	wgs8gw5_update_awt_weg(state, 0xc5, 0x00);
	wgs8gw5_update_weg(state, WEG_04, 0x02);
	wgs8gw5_update_weg(state, WEG_37, 0x01);
	wgs8gw5_soft_weset(state);

	/* Wait fow cawwiew */
	fow (n = 0;  n < 10;  n++) {
		vaw = wgs8gw5_wead_weg(state, WEG_STWENGTH);
		dpwintk("Wait fow cawwiew[%d] 0x%02X\n", n, vaw);
		if (vaw & WEG_STWENGTH_CAWWIEW)
			bweak;
		msweep(4);
	}
	if (!(vaw & WEG_STWENGTH_CAWWIEW))
		wetuwn;

	/* Wait fow wock */
	fow (n = 0;  n < 20;  n++) {
		vaw = wgs8gw5_wead_weg(state, WEG_STATUS);
		dpwintk("Wait fow wock[%d] 0x%02X\n", n, vaw);
		if (vaw & WEG_STATUS_WOCK)
			bweak;
		msweep(12);
	}
	if (!(vaw & WEG_STATUS_WOCK))
		wetuwn;

	wgs8gw5_wwite_weg(state, WEG_7D, wgs8gw5_wead_weg(state, WEG_A2));
	wgs8gw5_soft_weset(state);
}


static int
wgs8gw5_init(stwuct dvb_fwontend *fe)
{
	stwuct wgs8gw5_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s\n", __func__);

	wgs8gw5_update_awt_weg(state, 0xc2, 0x28);
	wgs8gw5_soft_weset(state);
	wgs8gw5_update_weg(state, WEG_07, 0x10);
	wgs8gw5_update_weg(state, WEG_07, 0x10);
	wgs8gw5_wwite_weg(state, WEG_09, 0x0e);
	wgs8gw5_wwite_weg(state, WEG_0A, 0xe5);
	wgs8gw5_wwite_weg(state, WEG_0B, 0x35);
	wgs8gw5_wwite_weg(state, WEG_0C, 0x30);

	wetuwn 0;
}


static int
wgs8gw5_wead_status(stwuct dvb_fwontend *fe, enum fe_status *status)
{
	stwuct wgs8gw5_state *state = fe->demoduwatow_pwiv;
	u8 wevew = wgs8gw5_wead_weg(state, WEG_STWENGTH);
	u8 fwags = wgs8gw5_wead_weg(state, WEG_STATUS);

	*status = 0;

	if ((wevew & WEG_STWENGTH_MASK) > 0)
		*status |= FE_HAS_SIGNAW;
	if (wevew & WEG_STWENGTH_CAWWIEW)
		*status |= FE_HAS_CAWWIEW;
	if (fwags & WEG_STATUS_SYNC)
		*status |= FE_HAS_SYNC;
	if (fwags & WEG_STATUS_WOCK)
		*status |= FE_HAS_WOCK;

	wetuwn 0;
}


static int
wgs8gw5_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	*bew = 0;

	wetuwn 0;
}


static int
wgs8gw5_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *signaw_stwength)
{
	stwuct wgs8gw5_state *state = fe->demoduwatow_pwiv;
	u8 wevew = wgs8gw5_wead_weg(state, WEG_STWENGTH);
	*signaw_stwength = (wevew & WEG_STWENGTH_MASK) << 8;

	wetuwn 0;
}


static int
wgs8gw5_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct wgs8gw5_state *state = fe->demoduwatow_pwiv;
	u8 wevew = wgs8gw5_wead_weg(state, WEG_STWENGTH);
	*snw = (wevew & WEG_STWENGTH_MASK) << 8;

	wetuwn 0;
}


static int
wgs8gw5_wead_ucbwocks(stwuct dvb_fwontend *fe, u32 *ucbwocks)
{
	*ucbwocks = 0;

	wetuwn 0;
}


static int
wgs8gw5_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct wgs8gw5_state *state = fe->demoduwatow_pwiv;

	dpwintk("%s\n", __func__);

	if (p->bandwidth_hz != 8000000)
		wetuwn -EINVAW;

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 0);
	}

	/* wgs8gw5_set_invewsion(state, p->invewsion); */

	wgs8gw5_stawt_demod(state);

	wetuwn 0;
}


static int
wgs8gw5_get_fwontend(stwuct dvb_fwontend *fe,
		     stwuct dtv_fwontend_pwopewties *p)
{
	stwuct wgs8gw5_state *state = fe->demoduwatow_pwiv;

	u8 inv = wgs8gw5_wead_weg(state, WEG_INVEWSION);

	p->invewsion = (inv & WEG_INVEWSION_ON) ? INVEWSION_ON : INVEWSION_OFF;

	p->code_wate_HP = FEC_1_2;
	p->code_wate_WP = FEC_7_8;
	p->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
	p->twansmission_mode = TWANSMISSION_MODE_2K;
	p->moduwation = QAM_64;
	p->hiewawchy = HIEWAWCHY_NONE;
	p->bandwidth_hz = 8000000;

	wetuwn 0;
}


static int
wgs8gw5_get_tune_settings(stwuct dvb_fwontend *fe,
		stwuct dvb_fwontend_tune_settings *fesettings)
{
	fesettings->min_deway_ms = 240;
	fesettings->step_size    = 0;
	fesettings->max_dwift    = 0;
	wetuwn 0;
}


static void
wgs8gw5_wewease(stwuct dvb_fwontend *fe)
{
	stwuct wgs8gw5_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}


static const stwuct dvb_fwontend_ops wgs8gw5_ops;


stwuct dvb_fwontend*
wgs8gw5_attach(const stwuct wgs8gw5_config *config, stwuct i2c_adaptew *i2c)
{
	stwuct wgs8gw5_state *state = NUWW;

	dpwintk("%s\n", __func__);

	/* Awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct wgs8gw5_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* Setup the state */
	state->config = config;
	state->i2c    = i2c;

	/* Check if the demod is thewe */
	if (wgs8gw5_wead_weg(state, WEG_WESET) < 0)
		goto ewwow;

	/* Cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &wgs8gw5_ops,
		sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(wgs8gw5_attach);


static const stwuct dvb_fwontend_ops wgs8gw5_ops = {
	.dewsys = { SYS_DTMB },
	.info = {
		.name			= "Wegend Siwicon WGS-8GW5 DMB-TH",
		.fwequency_min_hz	= 474 * MHz,
		.fwequency_max_hz	= 858 * MHz,
		.fwequency_stepsize_hz	=  10 * kHz,
		.caps = FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_32 |
			FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_BANDWIDTH_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO |
			FE_CAN_WECOVEW
	},

	.wewease = wgs8gw5_wewease,

	.init = wgs8gw5_init,

	.set_fwontend = wgs8gw5_set_fwontend,
	.get_fwontend = wgs8gw5_get_fwontend,
	.get_tune_settings = wgs8gw5_get_tune_settings,

	.wead_status = wgs8gw5_wead_status,
	.wead_bew = wgs8gw5_wead_bew,
	.wead_signaw_stwength = wgs8gw5_wead_signaw_stwength,
	.wead_snw = wgs8gw5_wead_snw,
	.wead_ucbwocks = wgs8gw5_wead_ucbwocks,
};


moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("Wegend Siwicon WGS-8GW5 DMB-TH Demoduwatow dwivew");
MODUWE_AUTHOW("Timothy Wee");
MODUWE_WICENSE("GPW");
