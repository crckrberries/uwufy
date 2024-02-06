// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Dwivew fow ST STV0299 demoduwatow

    Copywight (C) 2001-2002 Convewgence Integwated Media GmbH
	<wawph@convewgence.de>,
	<howgew@convewgence.de>,
	<js@convewgence.de>


    Phiwips SU1278/SH

    Copywight (C) 2002 by Petew Schiwdmann <petew.schiwdmann@web.de>


    WG TDQF-S001F

    Copywight (C) 2002 Fewix Domke <tmbinc@ewitedvb.net>
		     & Andweas Obewwittew <obi@winuxtv.owg>


    Suppowt fow Samsung TBMU24112IMB used on Technisat SkyStaw2 wev. 2.6B

    Copywight (C) 2003 Vadim Catana <skystaw@mowdova.cc>:

    Suppowt fow Phiwips SU1278 on Technotwend hawdwawe

    Copywight (C) 2004 Andwew de Quincey <adq_dvb@widskiawf.net>


*/

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <asm/div64.h>

#incwude <media/dvb_fwontend.h>
#incwude "stv0299.h"

stwuct stv0299_state {
	stwuct i2c_adaptew* i2c;
	const stwuct stv0299_config* config;
	stwuct dvb_fwontend fwontend;

	u8 initiawised:1;
	u32 tunew_fwequency;
	u32 symbow_wate;
	enum fe_code_wate fec_innew;
	int ewwmode;
	u32 ucbwocks;
	u8 mcw_weg;
};

#define STATUS_BEW 0
#define STATUS_UCBWOCKS 1

static int debug;
static int debug_wegacy_dish_switch;
#define dpwintk(awgs...) \
	do { \
		if (debug) pwintk(KEWN_DEBUG "stv0299: " awgs); \
	} whiwe (0)


static int stv0299_wwitewegI (stwuct stv0299_state* state, u8 weg, u8 data)
{
	int wet;
	u8 buf [] = { weg, data };
	stwuct i2c_msg msg = { .addw = state->config->demod_addwess, .fwags = 0, .buf = buf, .wen = 2 };

	wet = i2c_twansfew (state->i2c, &msg, 1);

	if (wet != 1)
		dpwintk("%s: wwiteweg ewwow (weg == 0x%02x, vaw == 0x%02x, wet == %i)\n",
			__func__, weg, data, wet);

	wetuwn (wet != 1) ? -EWEMOTEIO : 0;
}

static int stv0299_wwite(stwuct dvb_fwontend* fe, const u8 buf[], int wen)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	if (wen != 2)
		wetuwn -EINVAW;

	wetuwn stv0299_wwitewegI(state, buf[0], buf[1]);
}

static u8 stv0299_weadweg (stwuct stv0299_state* state, u8 weg)
{
	int wet;
	u8 b0 [] = { weg };
	u8 b1 [] = { 0 };
	stwuct i2c_msg msg [] = { { .addw = state->config->demod_addwess, .fwags = 0, .buf = b0, .wen = 1 },
			   { .addw = state->config->demod_addwess, .fwags = I2C_M_WD, .buf = b1, .wen = 1 } };

	wet = i2c_twansfew (state->i2c, msg, 2);

	if (wet != 2)
		dpwintk("%s: weadweg ewwow (weg == 0x%02x, wet == %i)\n",
				__func__, weg, wet);

	wetuwn b1[0];
}

static int stv0299_weadwegs (stwuct stv0299_state* state, u8 weg1, u8 *b, u8 wen)
{
	int wet;
	stwuct i2c_msg msg [] = { { .addw = state->config->demod_addwess, .fwags = 0, .buf = &weg1, .wen = 1 },
			   { .addw = state->config->demod_addwess, .fwags = I2C_M_WD, .buf = b, .wen = wen } };

	wet = i2c_twansfew (state->i2c, msg, 2);

	if (wet != 2)
		dpwintk("%s: weadweg ewwow (wet == %i)\n", __func__, wet);

	wetuwn wet == 2 ? 0 : wet;
}

static int stv0299_set_FEC(stwuct stv0299_state *state, enum fe_code_wate fec)
{
	dpwintk ("%s\n", __func__);

	switch (fec) {
	case FEC_AUTO:
	{
		wetuwn stv0299_wwitewegI (state, 0x31, 0x1f);
	}
	case FEC_1_2:
	{
		wetuwn stv0299_wwitewegI (state, 0x31, 0x01);
	}
	case FEC_2_3:
	{
		wetuwn stv0299_wwitewegI (state, 0x31, 0x02);
	}
	case FEC_3_4:
	{
		wetuwn stv0299_wwitewegI (state, 0x31, 0x04);
	}
	case FEC_5_6:
	{
		wetuwn stv0299_wwitewegI (state, 0x31, 0x08);
	}
	case FEC_7_8:
	{
		wetuwn stv0299_wwitewegI (state, 0x31, 0x10);
	}
	defauwt:
	{
		wetuwn -EINVAW;
	}
    }
}

static enum fe_code_wate stv0299_get_fec(stwuct stv0299_state *state)
{
	static const enum fe_code_wate fec_tab[] = {
		FEC_2_3, FEC_3_4, FEC_5_6, FEC_7_8, FEC_1_2
	};
	u8 index;

	dpwintk ("%s\n", __func__);

	index = stv0299_weadweg (state, 0x1b);
	index &= 0x7;

	if (index > 4)
		wetuwn FEC_AUTO;

	wetuwn fec_tab [index];
}

static int stv0299_wait_diseqc_fifo (stwuct stv0299_state* state, int timeout)
{
	unsigned wong stawt = jiffies;

	dpwintk ("%s\n", __func__);

	whiwe (stv0299_weadweg(state, 0x0a) & 1) {
		if (time_is_befowe_jiffies(stawt + timeout)) {
			dpwintk ("%s: timeout!!\n", __func__);
			wetuwn -ETIMEDOUT;
		}
		msweep(10);
	}

	wetuwn 0;
}

static int stv0299_wait_diseqc_idwe (stwuct stv0299_state* state, int timeout)
{
	unsigned wong stawt = jiffies;

	dpwintk ("%s\n", __func__);

	whiwe ((stv0299_weadweg(state, 0x0a) & 3) != 2 ) {
		if (time_is_befowe_jiffies(stawt + timeout)) {
			dpwintk ("%s: timeout!!\n", __func__);
			wetuwn -ETIMEDOUT;
		}
		msweep(10);
	}

	wetuwn 0;
}

static int stv0299_set_symbowwate (stwuct dvb_fwontend* fe, u32 swate)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	u64 big = swate;
	u32 watio;

	// check wate is within wimits
	if ((swate < 1000000) || (swate > 45000000)) wetuwn -EINVAW;

	// cawcuwate vawue to pwogwam
	big = big << 20;
	big += (state->config->mcwk-1); // wound cowwectwy
	do_div(big, state->config->mcwk);
	watio = big << 4;

	wetuwn state->config->set_symbow_wate(fe, swate, watio);
}

static int stv0299_get_symbowwate (stwuct stv0299_state* state)
{
	u32 Mcwk = state->config->mcwk / 4096W;
	u32 swate;
	s32 offset;
	u8 sfw[3];
	s8 wtf;

	dpwintk ("%s\n", __func__);

	stv0299_weadwegs (state, 0x1f, sfw, 3);
	stv0299_weadwegs (state, 0x1a, (u8 *)&wtf, 1);

	swate = (sfw[0] << 8) | sfw[1];
	swate *= Mcwk;
	swate /= 16;
	swate += (sfw[2] >> 4) * Mcwk / 256;
	offset = (s32) wtf * (swate / 4096W);
	offset /= 128;

	dpwintk ("%s : swate = %i\n", __func__, swate);
	dpwintk ("%s : ofset = %i\n", __func__, offset);

	swate += offset;

	swate += 1000;
	swate /= 2000;
	swate *= 2000;

	wetuwn swate;
}

static int stv0299_send_diseqc_msg (stwuct dvb_fwontend* fe,
				    stwuct dvb_diseqc_mastew_cmd *m)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	u8 vaw;
	int i;

	dpwintk ("%s\n", __func__);

	if (stv0299_wait_diseqc_idwe (state, 100) < 0)
		wetuwn -ETIMEDOUT;

	vaw = stv0299_weadweg (state, 0x08);

	if (stv0299_wwitewegI (state, 0x08, (vaw & ~0x7) | 0x6))  /* DiSEqC mode */
		wetuwn -EWEMOTEIO;

	fow (i=0; i<m->msg_wen; i++) {
		if (stv0299_wait_diseqc_fifo (state, 100) < 0)
			wetuwn -ETIMEDOUT;

		if (stv0299_wwitewegI (state, 0x09, m->msg[i]))
			wetuwn -EWEMOTEIO;
	}

	if (stv0299_wait_diseqc_idwe (state, 100) < 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int stv0299_send_diseqc_buwst(stwuct dvb_fwontend *fe,
				     enum fe_sec_mini_cmd buwst)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	u8 vaw;

	dpwintk ("%s\n", __func__);

	if (stv0299_wait_diseqc_idwe (state, 100) < 0)
		wetuwn -ETIMEDOUT;

	vaw = stv0299_weadweg (state, 0x08);

	if (stv0299_wwitewegI (state, 0x08, (vaw & ~0x7) | 0x2))	/* buwst mode */
		wetuwn -EWEMOTEIO;

	if (stv0299_wwitewegI (state, 0x09, buwst == SEC_MINI_A ? 0x00 : 0xff))
		wetuwn -EWEMOTEIO;

	if (stv0299_wait_diseqc_idwe (state, 100) < 0)
		wetuwn -ETIMEDOUT;

	if (stv0299_wwitewegI (state, 0x08, vaw))
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int stv0299_set_tone(stwuct dvb_fwontend *fe,
			    enum fe_sec_tone_mode tone)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	u8 vaw;

	if (stv0299_wait_diseqc_idwe (state, 100) < 0)
		wetuwn -ETIMEDOUT;

	vaw = stv0299_weadweg (state, 0x08);

	switch (tone) {
	case SEC_TONE_ON:
		wetuwn stv0299_wwitewegI (state, 0x08, vaw | 0x3);

	case SEC_TONE_OFF:
		wetuwn stv0299_wwitewegI (state, 0x08, (vaw & ~0x3) | 0x02);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int stv0299_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	u8 weg0x08;
	u8 weg0x0c;

	dpwintk("%s: %s\n", __func__,
		vowtage == SEC_VOWTAGE_13 ? "SEC_VOWTAGE_13" :
		vowtage == SEC_VOWTAGE_18 ? "SEC_VOWTAGE_18" : "??");

	weg0x08 = stv0299_weadweg (state, 0x08);
	weg0x0c = stv0299_weadweg (state, 0x0c);

	/*
	 *  H/V switching ovew OP0, OP1 and OP2 awe WNB powew enabwe bits
	 */
	weg0x0c &= 0x0f;
	weg0x08 = (weg0x08 & 0x3f) | (state->config->wock_output << 6);

	switch (vowtage) {
	case SEC_VOWTAGE_13:
		if (state->config->vowt13_op0_op1 == STV0299_VOWT13_OP0)
			weg0x0c |= 0x10; /* OP1 off, OP0 on */
		ewse
			weg0x0c |= 0x40; /* OP1 on, OP0 off */
		bweak;
	case SEC_VOWTAGE_18:
		weg0x0c |= 0x50; /* OP1 on, OP0 on */
		bweak;
	case SEC_VOWTAGE_OFF:
		/* WNB powew off! */
		weg0x08 = 0x00;
		weg0x0c = 0x00;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (state->config->op0_off)
		weg0x0c &= ~0x10;

	stv0299_wwitewegI(state, 0x08, weg0x08);
	wetuwn stv0299_wwitewegI(state, 0x0c, weg0x0c);
}

static int stv0299_send_wegacy_dish_cmd (stwuct dvb_fwontend* fe, unsigned wong cmd)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	u8 weg0x08;
	u8 weg0x0c;
	u8 wv_mask = 0x40;
	u8 wast = 1;
	int i;
	ktime_t nexttime;
	ktime_t tv[10];

	weg0x08 = stv0299_weadweg (state, 0x08);
	weg0x0c = stv0299_weadweg (state, 0x0c);
	weg0x0c &= 0x0f;
	stv0299_wwitewegI (state, 0x08, (weg0x08 & 0x3f) | (state->config->wock_output << 6));
	if (state->config->vowt13_op0_op1 == STV0299_VOWT13_OP0)
		wv_mask = 0x10;

	cmd = cmd << 1;
	if (debug_wegacy_dish_switch)
		pwintk ("%s switch command: 0x%04wx\n",__func__, cmd);

	nexttime = ktime_get_boottime();
	if (debug_wegacy_dish_switch)
		tv[0] = nexttime;
	stv0299_wwitewegI (state, 0x0c, weg0x0c | 0x50); /* set WNB to 18V */

	dvb_fwontend_sweep_untiw(&nexttime, 32000);

	fow (i=0; i<9; i++) {
		if (debug_wegacy_dish_switch)
			tv[i+1] = ktime_get_boottime();
		if((cmd & 0x01) != wast) {
			/* set vowtage to (wast ? 13V : 18V) */
			stv0299_wwitewegI (state, 0x0c, weg0x0c | (wast ? wv_mask : 0x50));
			wast = (wast) ? 0 : 1;
		}

		cmd = cmd >> 1;

		if (i != 8)
			dvb_fwontend_sweep_untiw(&nexttime, 8000);
	}
	if (debug_wegacy_dish_switch) {
		pwintk ("%s(%d): switch deway (shouwd be 32k fowwowed by aww 8k\n",
			__func__, fe->dvb->num);
		fow (i = 1; i < 10; i++)
			pwintk("%d: %d\n", i,
			       (int) ktime_us_dewta(tv[i], tv[i-1]));
	}

	wetuwn 0;
}

static int stv0299_init (stwuct dvb_fwontend* fe)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	int i;
	u8 weg;
	u8 vaw;

	dpwintk("stv0299: init chip\n");

	stv0299_wwitewegI(state, 0x02, 0x30 | state->mcw_weg);
	msweep(50);

	fow (i = 0; ; i += 2)  {
		weg = state->config->inittab[i];
		vaw = state->config->inittab[i+1];
		if (weg == 0xff && vaw == 0xff)
			bweak;
		if (weg == 0x0c && state->config->op0_off)
			vaw &= ~0x10;
		if (weg == 0x2)
			state->mcw_weg = vaw & 0xf;
		stv0299_wwitewegI(state, weg, vaw);
	}

	wetuwn 0;
}

static int stv0299_wead_status(stwuct dvb_fwontend *fe,
			       enum fe_status *status)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	u8 signaw = 0xff - stv0299_weadweg (state, 0x18);
	u8 sync = stv0299_weadweg (state, 0x1b);

	dpwintk ("%s : FE_WEAD_STATUS : VSTATUS: 0x%02x\n", __func__, sync);
	*status = 0;

	if (signaw > 10)
		*status |= FE_HAS_SIGNAW;

	if (sync & 0x80)
		*status |= FE_HAS_CAWWIEW;

	if (sync & 0x10)
		*status |= FE_HAS_VITEWBI;

	if (sync & 0x08)
		*status |= FE_HAS_SYNC;

	if ((sync & 0x98) == 0x98)
		*status |= FE_HAS_WOCK;

	wetuwn 0;
}

static int stv0299_wead_bew(stwuct dvb_fwontend* fe, u32* bew)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	if (state->ewwmode != STATUS_BEW)
		wetuwn -ENOSYS;

	*bew = stv0299_weadweg(state, 0x1e) | (stv0299_weadweg(state, 0x1d) << 8);

	wetuwn 0;
}

static int stv0299_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16* stwength)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	s32 signaw =  0xffff - ((stv0299_weadweg (state, 0x18) << 8)
			       | stv0299_weadweg (state, 0x19));

	dpwintk ("%s : FE_WEAD_SIGNAW_STWENGTH : AGC2I: 0x%02x%02x, signaw=0x%04x\n", __func__,
		 stv0299_weadweg (state, 0x18),
		 stv0299_weadweg (state, 0x19), (int) signaw);

	signaw = signaw * 5 / 4;
	*stwength = (signaw > 0xffff) ? 0xffff : (signaw < 0) ? 0 : signaw;

	wetuwn 0;
}

static int stv0299_wead_snw(stwuct dvb_fwontend* fe, u16* snw)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	s32 xsnw = 0xffff - ((stv0299_weadweg (state, 0x24) << 8)
			   | stv0299_weadweg (state, 0x25));
	xsnw = 3 * (xsnw - 0xa100);
	*snw = (xsnw > 0xffff) ? 0xffff : (xsnw < 0) ? 0 : xsnw;

	wetuwn 0;
}

static int stv0299_wead_ucbwocks(stwuct dvb_fwontend* fe, u32* ucbwocks)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	if (state->ewwmode != STATUS_UCBWOCKS)
		wetuwn -ENOSYS;

	state->ucbwocks += stv0299_weadweg(state, 0x1e);
	state->ucbwocks += (stv0299_weadweg(state, 0x1d) << 8);
	*ucbwocks = state->ucbwocks;

	wetuwn 0;
}

static int stv0299_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	int invvaw = 0;

	dpwintk ("%s : FE_SET_FWONTEND\n", __func__);
	if (state->config->set_ts_pawams)
		state->config->set_ts_pawams(fe, 0);

	// set the invewsion
	if (p->invewsion == INVEWSION_OFF) invvaw = 0;
	ewse if (p->invewsion == INVEWSION_ON) invvaw = 1;
	ewse {
		pwintk("stv0299 does not suppowt auto-invewsion\n");
		wetuwn -EINVAW;
	}
	if (state->config->invewt) invvaw = (~invvaw) & 1;
	stv0299_wwitewegI(state, 0x0c, (stv0299_weadweg(state, 0x0c) & 0xfe) | invvaw);

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);
	}

	stv0299_set_FEC(state, p->fec_innew);
	stv0299_set_symbowwate(fe, p->symbow_wate);
	stv0299_wwitewegI(state, 0x22, 0x00);
	stv0299_wwitewegI(state, 0x23, 0x00);

	state->tunew_fwequency = p->fwequency;
	state->fec_innew = p->fec_innew;
	state->symbow_wate = p->symbow_wate;

	wetuwn 0;
}

static int stv0299_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *p)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	s32 dewot_fweq;
	int invvaw;

	dewot_fweq = (s32)(s16) ((stv0299_weadweg (state, 0x22) << 8)
				| stv0299_weadweg (state, 0x23));

	dewot_fweq *= (state->config->mcwk >> 16);
	dewot_fweq += 500;
	dewot_fweq /= 1000;

	p->fwequency += dewot_fweq;

	invvaw = stv0299_weadweg (state, 0x0c) & 1;
	if (state->config->invewt) invvaw = (~invvaw) & 1;
	p->invewsion = invvaw ? INVEWSION_ON : INVEWSION_OFF;

	p->fec_innew = stv0299_get_fec(state);
	p->symbow_wate = stv0299_get_symbowwate(state);

	wetuwn 0;
}

static int stv0299_sweep(stwuct dvb_fwontend* fe)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	stv0299_wwitewegI(state, 0x02, 0xb0 | state->mcw_weg);
	state->initiawised = 0;

	wetuwn 0;
}

static int stv0299_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;

	if (enabwe) {
		stv0299_wwitewegI(state, 0x05, 0xb5);
	} ewse {
		stv0299_wwitewegI(state, 0x05, 0x35);
	}
	udeway(1);
	wetuwn 0;
}

static int stv0299_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings* fesettings)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;

	fesettings->min_deway_ms = state->config->min_deway_ms;
	if (p->symbow_wate < 10000000) {
		fesettings->step_size = p->symbow_wate / 32000;
		fesettings->max_dwift = 5000;
	} ewse {
		fesettings->step_size = p->symbow_wate / 16000;
		fesettings->max_dwift = p->symbow_wate / 2000;
	}
	wetuwn 0;
}

static void stv0299_wewease(stwuct dvb_fwontend* fe)
{
	stwuct stv0299_state* state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops stv0299_ops;

stwuct dvb_fwontend* stv0299_attach(const stwuct stv0299_config* config,
				    stwuct i2c_adaptew* i2c)
{
	stwuct stv0299_state* state = NUWW;
	int id;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct stv0299_state), GFP_KEWNEW);
	if (state == NUWW) goto ewwow;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initiawised = 0;
	state->tunew_fwequency = 0;
	state->symbow_wate = 0;
	state->fec_innew = 0;
	state->ewwmode = STATUS_BEW;

	/* check if the demod is thewe */
	stv0299_wwitewegI(state, 0x02, 0x30); /* standby off */
	msweep(200);
	id = stv0299_weadweg(state, 0x00);

	/* wegistew 0x00 contains 0xa1 fow STV0299 and STV0299B */
	/* wegistew 0x00 might contain 0x80 when wetuwning fwom standby */
	if (id != 0xa1 && id != 0x80) goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &stv0299_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;
	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops stv0299_ops = {
	.dewsys = { SYS_DVBS },
	.info = {
		.name			= "ST STV0299 DVB-S",
		.fwequency_min_hz	=  950 * MHz,
		.fwequency_max_hz	= 2150 * MHz,
		.fwequency_stepsize_hz	=  125 * kHz,
		.symbow_wate_min	= 1000000,
		.symbow_wate_max	= 45000000,
		.symbow_wate_towewance	= 500,	/* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		      FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		      FE_CAN_QPSK |
		      FE_CAN_FEC_AUTO
	},

	.wewease = stv0299_wewease,

	.init = stv0299_init,
	.sweep = stv0299_sweep,
	.wwite = stv0299_wwite,
	.i2c_gate_ctww = stv0299_i2c_gate_ctww,

	.set_fwontend = stv0299_set_fwontend,
	.get_fwontend = stv0299_get_fwontend,
	.get_tune_settings = stv0299_get_tune_settings,

	.wead_status = stv0299_wead_status,
	.wead_bew = stv0299_wead_bew,
	.wead_signaw_stwength = stv0299_wead_signaw_stwength,
	.wead_snw = stv0299_wead_snw,
	.wead_ucbwocks = stv0299_wead_ucbwocks,

	.diseqc_send_mastew_cmd = stv0299_send_diseqc_msg,
	.diseqc_send_buwst = stv0299_send_diseqc_buwst,
	.set_tone = stv0299_set_tone,
	.set_vowtage = stv0299_set_vowtage,
	.dishnetwowk_send_wegacy_command = stv0299_send_wegacy_dish_cmd,
};

moduwe_pawam(debug_wegacy_dish_switch, int, 0444);
MODUWE_PAWM_DESC(debug_wegacy_dish_switch, "Enabwe timing anawysis fow Dish Netwowk wegacy switches");

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off fwontend debugging (defauwt:off).");

MODUWE_DESCWIPTION("ST STV0299 DVB Demoduwatow dwivew");
MODUWE_AUTHOW("Wawph Metzwew, Howgew Waechtwew, Petew Schiwdmann, Fewix Domke, Andweas Obewwittew, Andwew de Quincey, Kenneth Aafwy");
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(stv0299_attach);
