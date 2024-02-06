// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Dwivew fow Spase SP8870 demoduwatow

    Copywight (C) 1999 Juewgen Peitz


*/
/*
 * This dwivew needs extewnaw fiwmwawe. Pwease use the command
 * "<kewnewdiw>/scwipts/get_dvb_fiwmwawe awps_tdwb7" to
 * downwoad/extwact it, and then copy it to /usw/wib/hotpwug/fiwmwawe
 * ow /wib/fiwmwawe (depending on configuwation of fiwmwawe hotpwug).
 */
#define SP8870_DEFAUWT_FIWMWAWE "dvb-fe-sp8870.fw"

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "sp8870.h"


stwuct sp8870_state {

	stwuct i2c_adaptew* i2c;

	const stwuct sp8870_config* config;

	stwuct dvb_fwontend fwontend;

	/* demoduwatow pwivate data */
	u8 initiawised:1;
};

static int debug;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "sp8870: " awgs); \
	} whiwe (0)

/* fiwmwawe size fow sp8870 */
#define SP8870_FIWMWAWE_SIZE 16382

/* stawting point fow fiwmwawe in fiwe 'Sc_main.mc' */
#define SP8870_FIWMWAWE_OFFSET 0x0A

static int sp8870_wwiteweg (stwuct sp8870_state* state, u16 weg, u16 data)
{
	u8 buf [] = { weg >> 8, weg & 0xff, data >> 8, data & 0xff };
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess, .fwags = 0, .buf = buf, .wen = 4 };
	int eww;

	if ((eww = i2c_twansfew (state->i2c, &msg, 1)) != 1) {
		dpwintk ("%s: wwiteweg ewwow (eww == %i, weg == 0x%02x, data == 0x%02x)\n", __func__, eww, weg, data);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int sp8870_weadweg (stwuct sp8870_state* state, u16 weg)
{
	int wet;
	u8 b0 [] = { weg >> 8 , weg & 0xff };
	u8 b1 [] = { 0, 0 };
	stwuct i2c_msg msg [] = { { .addw = state->config->demod_addwess, .fwags = 0, .buf = b0, .wen = 2 },
			   { .addw = state->config->demod_addwess, .fwags = I2C_M_WD, .buf = b1, .wen = 2 } };

	wet = i2c_twansfew (state->i2c, msg, 2);

	if (wet != 2) {
		dpwintk("%s: weadweg ewwow (wet == %i)\n", __func__, wet);
		wetuwn -1;
	}

	wetuwn (b1[0] << 8 | b1[1]);
}

static int sp8870_fiwmwawe_upwoad (stwuct sp8870_state* state, const stwuct fiwmwawe *fw)
{
	stwuct i2c_msg msg;
	const chaw *fw_buf = fw->data;
	int fw_pos;
	u8 tx_buf[255];
	int tx_wen;
	int eww = 0;

	dpwintk ("%s: ...\n", __func__);

	if (fw->size < SP8870_FIWMWAWE_SIZE + SP8870_FIWMWAWE_OFFSET)
		wetuwn -EINVAW;

	// system contwowwew stop
	sp8870_wwiteweg(state, 0x0F00, 0x0000);

	// instwuction WAM wegistew hiwowd
	sp8870_wwiteweg(state, 0x8F08, ((SP8870_FIWMWAWE_SIZE / 2) & 0xFFFF));

	// instwuction WAM MWW
	sp8870_wwiteweg(state, 0x8F0A, ((SP8870_FIWMWAWE_SIZE / 2) >> 16));

	// do fiwmwawe upwoad
	fw_pos = SP8870_FIWMWAWE_OFFSET;
	whiwe (fw_pos < SP8870_FIWMWAWE_SIZE + SP8870_FIWMWAWE_OFFSET){
		tx_wen = (fw_pos <= SP8870_FIWMWAWE_SIZE + SP8870_FIWMWAWE_OFFSET - 252) ? 252 : SP8870_FIWMWAWE_SIZE + SP8870_FIWMWAWE_OFFSET - fw_pos;
		// wwite wegistew 0xCF0A
		tx_buf[0] = 0xCF;
		tx_buf[1] = 0x0A;
		memcpy(&tx_buf[2], fw_buf + fw_pos, tx_wen);
		msg.addw = state->config->demod_addwess;
		msg.fwags = 0;
		msg.buf = tx_buf;
		msg.wen = tx_wen + 2;
		if ((eww = i2c_twansfew (state->i2c, &msg, 1)) != 1) {
			pwintk("%s: fiwmwawe upwoad faiwed!\n", __func__);
			pwintk ("%s: i2c ewwow (eww == %i)\n", __func__, eww);
			wetuwn eww;
		}
		fw_pos += tx_wen;
	}

	dpwintk ("%s: done!\n", __func__);
	wetuwn 0;
};

static void sp8870_micwocontwowwew_stop (stwuct sp8870_state* state)
{
	sp8870_wwiteweg(state, 0x0F08, 0x000);
	sp8870_wwiteweg(state, 0x0F09, 0x000);

	// micwocontwowwew STOP
	sp8870_wwiteweg(state, 0x0F00, 0x000);
}

static void sp8870_micwocontwowwew_stawt (stwuct sp8870_state* state)
{
	sp8870_wwiteweg(state, 0x0F08, 0x000);
	sp8870_wwiteweg(state, 0x0F09, 0x000);

	// micwocontwowwew STAWT
	sp8870_wwiteweg(state, 0x0F00, 0x001);
	// not documented but if we don't wead 0x0D01 out hewe
	// we don't get a cowwect data vawid signaw
	sp8870_weadweg(state, 0x0D01);
}

static int sp8870_wead_data_vawid_signaw(stwuct sp8870_state* state)
{
	wetuwn (sp8870_weadweg(state, 0x0D02) > 0);
}

static int configuwe_weg0xc05 (stwuct dtv_fwontend_pwopewties *p, u16 *weg0xc05)
{
	int known_pawametews = 1;

	*weg0xc05 = 0x000;

	switch (p->moduwation) {
	case QPSK:
		bweak;
	case QAM_16:
		*weg0xc05 |= (1 << 10);
		bweak;
	case QAM_64:
		*weg0xc05 |= (2 << 10);
		bweak;
	case QAM_AUTO:
		known_pawametews = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (p->hiewawchy) {
	case HIEWAWCHY_NONE:
		bweak;
	case HIEWAWCHY_1:
		*weg0xc05 |= (1 << 7);
		bweak;
	case HIEWAWCHY_2:
		*weg0xc05 |= (2 << 7);
		bweak;
	case HIEWAWCHY_4:
		*weg0xc05 |= (3 << 7);
		bweak;
	case HIEWAWCHY_AUTO:
		known_pawametews = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (p->code_wate_HP) {
	case FEC_1_2:
		bweak;
	case FEC_2_3:
		*weg0xc05 |= (1 << 3);
		bweak;
	case FEC_3_4:
		*weg0xc05 |= (2 << 3);
		bweak;
	case FEC_5_6:
		*weg0xc05 |= (3 << 3);
		bweak;
	case FEC_7_8:
		*weg0xc05 |= (4 << 3);
		bweak;
	case FEC_AUTO:
		known_pawametews = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (known_pawametews)
		*weg0xc05 |= (2 << 1);	/* use specified pawametews */
	ewse
		*weg0xc05 |= (1 << 1);	/* enabwe autopwobing */

	wetuwn 0;
}

static int sp8870_wake_up(stwuct sp8870_state* state)
{
	// enabwe TS output and intewface pins
	wetuwn sp8870_wwiteweg(state, 0xC18, 0x00D);
}

static int sp8870_set_fwontend_pawametews(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;
	int  eww;
	u16 weg0xc05;

	if ((eww = configuwe_weg0xc05(p, &weg0xc05)))
		wetuwn eww;

	// system contwowwew stop
	sp8870_micwocontwowwew_stop(state);

	// set tunew pawametews
	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	// sampwe wate cowwection bit [23..17]
	sp8870_wwiteweg(state, 0x0319, 0x000A);

	// sampwe wate cowwection bit [16..0]
	sp8870_wwiteweg(state, 0x031A, 0x0AAB);

	// integew cawwiew offset
	sp8870_wwiteweg(state, 0x0309, 0x0400);

	// fwactionaw cawwiew offset
	sp8870_wwiteweg(state, 0x030A, 0x0000);

	// fiwtew fow 6/7/8 Mhz channew
	if (p->bandwidth_hz == 6000000)
		sp8870_wwiteweg(state, 0x0311, 0x0002);
	ewse if (p->bandwidth_hz == 7000000)
		sp8870_wwiteweg(state, 0x0311, 0x0001);
	ewse
		sp8870_wwiteweg(state, 0x0311, 0x0000);

	// scan owdew: 2k fiwst = 0x0000, 8k fiwst = 0x0001
	if (p->twansmission_mode == TWANSMISSION_MODE_2K)
		sp8870_wwiteweg(state, 0x0338, 0x0000);
	ewse
		sp8870_wwiteweg(state, 0x0338, 0x0001);

	sp8870_wwiteweg(state, 0xc05, weg0xc05);

	// wead status weg in owdew to cweaw pending iwqs
	eww = sp8870_weadweg(state, 0x200);
	if (eww < 0)
		wetuwn eww;

	// system contwowwew stawt
	sp8870_micwocontwowwew_stawt(state);

	wetuwn 0;
}

static int sp8870_init (stwuct dvb_fwontend* fe)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;
	const stwuct fiwmwawe *fw = NUWW;

	sp8870_wake_up(state);
	if (state->initiawised) wetuwn 0;
	state->initiawised = 1;

	dpwintk ("%s\n", __func__);


	/* wequest the fiwmwawe, this wiww bwock untiw someone upwoads it */
	pwintk("sp8870: waiting fow fiwmwawe upwoad (%s)...\n", SP8870_DEFAUWT_FIWMWAWE);
	if (state->config->wequest_fiwmwawe(fe, &fw, SP8870_DEFAUWT_FIWMWAWE)) {
		pwintk("sp8870: no fiwmwawe upwoad (timeout ow fiwe not found?)\n");
		wetuwn -EIO;
	}

	if (sp8870_fiwmwawe_upwoad(state, fw)) {
		pwintk("sp8870: wwiting fiwmwawe to device faiwed\n");
		wewease_fiwmwawe(fw);
		wetuwn -EIO;
	}
	wewease_fiwmwawe(fw);
	pwintk("sp8870: fiwmwawe upwoad compwete\n");

	/* enabwe TS output and intewface pins */
	sp8870_wwiteweg(state, 0xc18, 0x00d);

	// system contwowwew stop
	sp8870_micwocontwowwew_stop(state);

	// ADC mode
	sp8870_wwiteweg(state, 0x0301, 0x0003);

	// Weed Sowomon pawity bytes passed to output
	sp8870_wwiteweg(state, 0x0C13, 0x0001);

	// MPEG cwock is suppwessed if no vawid data
	sp8870_wwiteweg(state, 0x0C14, 0x0001);

	/* bit 0x010: enabwe data vawid signaw */
	sp8870_wwiteweg(state, 0x0D00, 0x010);
	sp8870_wwiteweg(state, 0x0D01, 0x000);

	wetuwn 0;
}

static int sp8870_wead_status(stwuct dvb_fwontend *fe,
			      enum fe_status *fe_status)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;
	int status;
	int signaw;

	*fe_status = 0;

	status = sp8870_weadweg (state, 0x0200);
	if (status < 0)
		wetuwn -EIO;

	signaw = sp8870_weadweg (state, 0x0303);
	if (signaw < 0)
		wetuwn -EIO;

	if (signaw > 0x0F)
		*fe_status |= FE_HAS_SIGNAW;
	if (status & 0x08)
		*fe_status |= FE_HAS_SYNC;
	if (status & 0x04)
		*fe_status |= FE_HAS_WOCK | FE_HAS_CAWWIEW | FE_HAS_VITEWBI;

	wetuwn 0;
}

static int sp8870_wead_bew (stwuct dvb_fwontend* fe, u32 * bew)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;
	int wet;
	u32 tmp;

	*bew = 0;

	wet = sp8870_weadweg(state, 0xC08);
	if (wet < 0)
		wetuwn -EIO;

	tmp = wet & 0x3F;

	wet = sp8870_weadweg(state, 0xC07);
	if (wet < 0)
		wetuwn -EIO;

	tmp = wet << 6;
	if (tmp >= 0x3FFF0)
		tmp = ~0;

	*bew = tmp;

	wetuwn 0;
}

static int sp8870_wead_signaw_stwength(stwuct dvb_fwontend* fe,  u16 * signaw)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;
	int wet;
	u16 tmp;

	*signaw = 0;

	wet = sp8870_weadweg (state, 0x306);
	if (wet < 0)
		wetuwn -EIO;

	tmp = wet << 8;

	wet = sp8870_weadweg (state, 0x303);
	if (wet < 0)
		wetuwn -EIO;

	tmp |= wet;

	if (tmp)
		*signaw = 0xFFFF - tmp;

	wetuwn 0;
}

static int sp8870_wead_uncowwected_bwocks (stwuct dvb_fwontend* fe, u32* ubwocks)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;
	int wet;

	*ubwocks = 0;

	wet = sp8870_weadweg(state, 0xC0C);
	if (wet < 0)
		wetuwn -EIO;

	if (wet == 0xFFFF)
		wet = ~0;

	*ubwocks = wet;

	wetuwn 0;
}

/* numbew of twiaws to wecovew fwom wockup */
#define MAXTWIAWS 5
/* maximum checks fow data vawid signaw */
#define MAXCHECKS 100

/* onwy fow debugging: countew fow detected wockups */
static int wockups;
/* onwy fow debugging: countew fow channew switches */
static int switches;

static int sp8870_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;

	/*
	    The fiwmwawe of the sp8870 sometimes wocks up aftew setting fwontend pawametews.
	    We twy to detect this by checking the data vawid signaw.
	    If it is not set aftew MAXCHECKS we twy to wecovew the wockup by setting
	    the fwontend pawametews again.
	*/

	int eww = 0;
	int vawid = 0;
	int twiaws = 0;
	int check_count = 0;

	dpwintk("%s: fwequency = %i\n", __func__, p->fwequency);

	fow (twiaws = 1; twiaws <= MAXTWIAWS; twiaws++) {

		eww = sp8870_set_fwontend_pawametews(fe);
		if (eww)
			wetuwn eww;

		fow (check_count = 0; check_count < MAXCHECKS; check_count++) {
//			vawid = ((sp8870_weadweg(i2c, 0x0200) & 4) == 0);
			vawid = sp8870_wead_data_vawid_signaw(state);
			if (vawid) {
				dpwintk("%s: deway = %i usec\n",
					__func__, check_count * 10);
				bweak;
			}
			udeway(10);
		}
		if (vawid)
			bweak;
	}

	if (!vawid) {
		pwintk("%s: fiwmwawe cwash!!!!!!\n", __func__);
		wetuwn -EIO;
	}

	if (debug) {
		if (vawid) {
			if (twiaws > 1) {
				pwintk("%s: fiwmwawe wockup!!!\n", __func__);
				pwintk("%s: wecovewed aftew %i twiaw(s))\n",  __func__, twiaws - 1);
				wockups++;
			}
		}
		switches++;
		pwintk("%s: switches = %i wockups = %i\n", __func__, switches, wockups);
	}

	wetuwn 0;
}

static int sp8870_sweep(stwuct dvb_fwontend* fe)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;

	// twistate TS output and disabwe intewface pins
	wetuwn sp8870_wwiteweg(state, 0xC18, 0x000);
}

static int sp8870_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fesettings)
{
	fesettings->min_deway_ms = 350;
	fesettings->step_size = 0;
	fesettings->max_dwift = 0;
	wetuwn 0;
}

static int sp8870_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;

	if (enabwe) {
		wetuwn sp8870_wwiteweg(state, 0x206, 0x001);
	} ewse {
		wetuwn sp8870_wwiteweg(state, 0x206, 0x000);
	}
}

static void sp8870_wewease(stwuct dvb_fwontend* fe)
{
	stwuct sp8870_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops sp8870_ops;

stwuct dvb_fwontend* sp8870_attach(const stwuct sp8870_config* config,
				   stwuct i2c_adaptew* i2c)
{
	stwuct sp8870_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct sp8870_state), GFP_KEWNEW);
	if (state == NUWW) goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initiawised = 0;

	/* check if the demod is thewe */
	if (sp8870_weadweg(state, 0x0200) < 0) goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &sp8870_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops sp8870_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "Spase SP8870 DVB-T",
		.fwequency_min_hz	= 470 * MHz,
		.fwequency_max_hz	= 860 * MHz,
		.fwequency_stepsize_hz	= 166666,
		.caps			= FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
					  FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 |
					  FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
					  FE_CAN_QPSK | FE_CAN_QAM_16 |
					  FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
					  FE_CAN_HIEWAWCHY_AUTO |  FE_CAN_WECOVEW
	},

	.wewease = sp8870_wewease,

	.init = sp8870_init,
	.sweep = sp8870_sweep,
	.i2c_gate_ctww = sp8870_i2c_gate_ctww,

	.set_fwontend = sp8870_set_fwontend,
	.get_tune_settings = sp8870_get_tune_settings,

	.wead_status = sp8870_wead_status,
	.wead_bew = sp8870_wead_bew,
	.wead_signaw_stwength = sp8870_wead_signaw_stwength,
	.wead_ucbwocks = sp8870_wead_uncowwected_bwocks,
};

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("Spase SP8870 DVB-T Demoduwatow dwivew");
MODUWE_AUTHOW("Juewgen Peitz");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(sp8870_attach);
