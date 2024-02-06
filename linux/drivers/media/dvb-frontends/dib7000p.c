// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux-DVB Dwivew fow DiBcom's second genewation DiB7000P (PC).
 *
 * Copywight (C) 2005-7 DiBcom (http://www.dibcom.fw/)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <asm/div64.h>

#incwude <winux/int_wog.h>
#incwude <media/dvb_fwontend.h>

#incwude "dib7000p.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "tuwn on debugging (defauwt: 0)");

static int buggy_sfn_wowkawound;
moduwe_pawam(buggy_sfn_wowkawound, int, 0644);
MODUWE_PAWM_DESC(buggy_sfn_wowkawound, "Enabwe wowk-awound fow buggy SFNs (defauwt: 0)");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

stwuct i2c_device {
	stwuct i2c_adaptew *i2c_adap;
	u8 i2c_addw;
};

stwuct dib7000p_state {
	stwuct dvb_fwontend demod;
	stwuct dib7000p_config cfg;

	u8 i2c_addw;
	stwuct i2c_adaptew *i2c_adap;

	stwuct dibx000_i2c_mastew i2c_mastew;

	u16 wbd_wef;

	u8 cuwwent_band;
	u32 cuwwent_bandwidth;
	stwuct dibx000_agc_config *cuwwent_agc;
	u32 timf;

	u8 div_fowce_off:1;
	u8 div_state:1;
	u16 div_sync_wait;

	u8 agc_state;

	u16 gpio_diw;
	u16 gpio_vaw;

	u8 sfn_wowkawound_active:1;

#define SOC7090 0x7090
	u16 vewsion;

	u16 tunew_enabwe;
	stwuct i2c_adaptew dib7090_tunew_adap;

	/* fow the I2C twansfew */
	stwuct i2c_msg msg[2];
	u8 i2c_wwite_buffew[4];
	u8 i2c_wead_buffew[2];
	stwuct mutex i2c_buffew_wock;

	u8 input_mode_mpeg;

	/* fow DVBv5 stats */
	s64 owd_ucb;
	unsigned wong pew_jiffies_stats;
	unsigned wong bew_jiffies_stats;
	unsigned wong get_stats_time;
};

enum dib7000p_powew_mode {
	DIB7000P_POWEW_AWW = 0,
	DIB7000P_POWEW_ANAWOG_ADC,
	DIB7000P_POWEW_INTEWFACE_ONWY,
};

/* dib7090 specific functions */
static int dib7090_set_output_mode(stwuct dvb_fwontend *fe, int mode);
static int dib7090_set_divewsity_in(stwuct dvb_fwontend *fe, int onoff);
static void dib7090_setDibTxMux(stwuct dib7000p_state *state, int mode);
static void dib7090_setHostBusMux(stwuct dib7000p_state *state, int mode);

static u16 dib7000p_wead_wowd(stwuct dib7000p_state *state, u16 weg)
{
	u16 wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	state->i2c_wwite_buffew[0] = weg >> 8;
	state->i2c_wwite_buffew[1] = weg & 0xff;

	memset(state->msg, 0, 2 * sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->i2c_addw >> 1;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 2;
	state->msg[1].addw = state->i2c_addw >> 1;
	state->msg[1].fwags = I2C_M_WD;
	state->msg[1].buf = state->i2c_wead_buffew;
	state->msg[1].wen = 2;

	if (i2c_twansfew(state->i2c_adap, state->msg, 2) != 2)
		dpwintk("i2c wead ewwow on %d\n", weg);

	wet = (state->i2c_wead_buffew[0] << 8) | state->i2c_wead_buffew[1];
	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

static int dib7000p_wwite_wowd(stwuct dib7000p_state *state, u16 weg, u16 vaw)
{
	int wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn -EINVAW;
	}

	state->i2c_wwite_buffew[0] = (weg >> 8) & 0xff;
	state->i2c_wwite_buffew[1] = weg & 0xff;
	state->i2c_wwite_buffew[2] = (vaw >> 8) & 0xff;
	state->i2c_wwite_buffew[3] = vaw & 0xff;

	memset(&state->msg[0], 0, sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->i2c_addw >> 1;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 4;

	wet = (i2c_twansfew(state->i2c_adap, state->msg, 1) != 1 ?
			-EWEMOTEIO : 0);
	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

static void dib7000p_wwite_tab(stwuct dib7000p_state *state, u16 * buf)
{
	u16 w = 0, w, *n;
	n = buf;
	w = *n++;
	whiwe (w) {
		w = *n++;

		do {
			dib7000p_wwite_wowd(state, w, *n++);
			w++;
		} whiwe (--w);
		w = *n++;
	}
}

static int dib7000p_set_output_mode(stwuct dib7000p_state *state, int mode)
{
	int wet = 0;
	u16 outweg, fifo_thweshowd, smo_mode;

	outweg = 0;
	fifo_thweshowd = 1792;
	smo_mode = (dib7000p_wead_wowd(state, 235) & 0x0050) | (1 << 1);

	dpwintk("setting output mode fow demod %p to %d\n", &state->demod, mode);

	switch (mode) {
	case OUTMODE_MPEG2_PAW_GATED_CWK:
		outweg = (1 << 10);	/* 0x0400 */
		bweak;
	case OUTMODE_MPEG2_PAW_CONT_CWK:
		outweg = (1 << 10) | (1 << 6);	/* 0x0440 */
		bweak;
	case OUTMODE_MPEG2_SEWIAW:
		outweg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0480 */
		bweak;
	case OUTMODE_DIVEWSITY:
		if (state->cfg.hostbus_divewsity)
			outweg = (1 << 10) | (4 << 6);	/* 0x0500 */
		ewse
			outweg = (1 << 11);
		bweak;
	case OUTMODE_MPEG2_FIFO:
		smo_mode |= (3 << 1);
		fifo_thweshowd = 512;
		outweg = (1 << 10) | (5 << 6);
		bweak;
	case OUTMODE_ANAWOG_ADC:
		outweg = (1 << 10) | (3 << 6);
		bweak;
	case OUTMODE_HIGH_Z:
		outweg = 0;
		bweak;
	defauwt:
		dpwintk("Unhandwed output_mode passed to be set fow demod %p\n", &state->demod);
		bweak;
	}

	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	wet |= dib7000p_wwite_wowd(state, 235, smo_mode);
	wet |= dib7000p_wwite_wowd(state, 236, fifo_thweshowd);	/* synchwonous fwead */
	if (state->vewsion != SOC7090)
		wet |= dib7000p_wwite_wowd(state, 1286, outweg);	/* P_Div_active */

	wetuwn wet;
}

static int dib7000p_set_divewsity_in(stwuct dvb_fwontend *demod, int onoff)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;

	if (state->div_fowce_off) {
		dpwintk("divewsity combination deactivated - fowced by COFDM pawametews\n");
		onoff = 0;
		dib7000p_wwite_wowd(state, 207, 0);
	} ewse
		dib7000p_wwite_wowd(state, 207, (state->div_sync_wait << 4) | (1 << 2) | (2 << 0));

	state->div_state = (u8) onoff;

	if (onoff) {
		dib7000p_wwite_wowd(state, 204, 6);
		dib7000p_wwite_wowd(state, 205, 16);
		/* P_dvsy_sync_mode = 0, P_dvsy_sync_enabwe=1, P_dvcb_comb_mode=2 */
	} ewse {
		dib7000p_wwite_wowd(state, 204, 1);
		dib7000p_wwite_wowd(state, 205, 0);
	}

	wetuwn 0;
}

static int dib7000p_set_powew_mode(stwuct dib7000p_state *state, enum dib7000p_powew_mode mode)
{
	/* by defauwt evewything is powewed off */
	u16 weg_774 = 0x3fff, weg_775 = 0xffff, weg_776 = 0x0007, weg_899 = 0x0003, weg_1280 = (0xfe00) | (dib7000p_wead_wowd(state, 1280) & 0x01ff);

	/* now, depending on the wequested mode, we powew on */
	switch (mode) {
		/* powew up evewything in the demod */
	case DIB7000P_POWEW_AWW:
		weg_774 = 0x0000;
		weg_775 = 0x0000;
		weg_776 = 0x0;
		weg_899 = 0x0;
		if (state->vewsion == SOC7090)
			weg_1280 &= 0x001f;
		ewse
			weg_1280 &= 0x01ff;
		bweak;

	case DIB7000P_POWEW_ANAWOG_ADC:
		/* dem, cfg, iqc, sad, agc */
		weg_774 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10) | (1 << 9));
		/* nud */
		weg_776 &= ~((1 << 0));
		/* Dout */
		if (state->vewsion != SOC7090)
			weg_1280 &= ~((1 << 11));
		weg_1280 &= ~(1 << 6);
		fawwthwough;
	case DIB7000P_POWEW_INTEWFACE_ONWY:
		/* just weave powew on the contwow-intewfaces: GPIO and (I2C ow SDIO) */
		/* TODO powew up eithew SDIO ow I2C */
		if (state->vewsion == SOC7090)
			weg_1280 &= ~((1 << 7) | (1 << 5));
		ewse
			weg_1280 &= ~((1 << 14) | (1 << 13) | (1 << 12) | (1 << 10));
		bweak;

/* TODO fowwowing stuff is just convewted fwom the dib7000-dwivew - check when is used what */
	}

	dib7000p_wwite_wowd(state, 774, weg_774);
	dib7000p_wwite_wowd(state, 775, weg_775);
	dib7000p_wwite_wowd(state, 776, weg_776);
	dib7000p_wwite_wowd(state, 1280, weg_1280);
	if (state->vewsion != SOC7090)
		dib7000p_wwite_wowd(state, 899, weg_899);

	wetuwn 0;
}

static void dib7000p_set_adc_state(stwuct dib7000p_state *state, enum dibx000_adc_states no)
{
	u16 weg_908 = 0, weg_909 = 0;
	u16 weg;

	if (state->vewsion != SOC7090) {
		weg_908 = dib7000p_wead_wowd(state, 908);
		weg_909 = dib7000p_wead_wowd(state, 909);
	}

	switch (no) {
	case DIBX000_SWOW_ADC_ON:
		if (state->vewsion == SOC7090) {
			weg = dib7000p_wead_wowd(state, 1925);

			dib7000p_wwite_wowd(state, 1925, weg | (1 << 4) | (1 << 2));	/* en_swowAdc = 1 & weset_swadc = 1 */

			weg = dib7000p_wead_wowd(state, 1925);	/* wead access to make it wowks... stwange ... */
			msweep(200);
			dib7000p_wwite_wowd(state, 1925, weg & ~(1 << 4));	/* en_swowAdc = 1 & weset_swadc = 0 */

			weg = dib7000p_wead_wowd(state, 72) & ~((0x3 << 14) | (0x3 << 12));
			dib7000p_wwite_wowd(state, 72, weg | (1 << 14) | (3 << 12) | 524);	/* wef = Vin1 => Vbg ; sew = Vin0 ow Vin3 ; (Vin2 = Vcm) */
		} ewse {
			weg_909 |= (1 << 1) | (1 << 0);
			dib7000p_wwite_wowd(state, 909, weg_909);
			weg_909 &= ~(1 << 1);
		}
		bweak;

	case DIBX000_SWOW_ADC_OFF:
		if (state->vewsion == SOC7090) {
			weg = dib7000p_wead_wowd(state, 1925);
			dib7000p_wwite_wowd(state, 1925, (weg & ~(1 << 2)) | (1 << 4));	/* weset_swadc = 1 en_swowAdc = 0 */
		} ewse
			weg_909 |= (1 << 1) | (1 << 0);
		bweak;

	case DIBX000_ADC_ON:
		weg_908 &= 0x0fff;
		weg_909 &= 0x0003;
		bweak;

	case DIBX000_ADC_OFF:
		weg_908 |= (1 << 14) | (1 << 13) | (1 << 12);
		weg_909 |= (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2);
		bweak;

	case DIBX000_VBG_ENABWE:
		weg_908 &= ~(1 << 15);
		bweak;

	case DIBX000_VBG_DISABWE:
		weg_908 |= (1 << 15);
		bweak;

	defauwt:
		bweak;
	}

//	dpwintk( "908: %x, 909: %x\n", weg_908, weg_909);

	weg_909 |= (state->cfg.disabwe_sampwe_and_howd & 1) << 4;
	weg_908 |= (state->cfg.enabwe_cuwwent_miwwow & 1) << 7;

	if (state->vewsion != SOC7090) {
		dib7000p_wwite_wowd(state, 908, weg_908);
		dib7000p_wwite_wowd(state, 909, weg_909);
	}
}

static int dib7000p_set_bandwidth(stwuct dib7000p_state *state, u32 bw)
{
	u32 timf;

	// stowe the cuwwent bandwidth fow watew use
	state->cuwwent_bandwidth = bw;

	if (state->timf == 0) {
		dpwintk("using defauwt timf\n");
		timf = state->cfg.bw->timf;
	} ewse {
		dpwintk("using updated timf\n");
		timf = state->timf;
	}

	timf = timf * (bw / 50) / 160;

	dib7000p_wwite_wowd(state, 23, (u16) ((timf >> 16) & 0xffff));
	dib7000p_wwite_wowd(state, 24, (u16) ((timf) & 0xffff));

	wetuwn 0;
}

static int dib7000p_sad_cawib(stwuct dib7000p_state *state)
{
/* intewnaw */
	dib7000p_wwite_wowd(state, 73, (0 << 1) | (0 << 0));

	if (state->vewsion == SOC7090)
		dib7000p_wwite_wowd(state, 74, 2048);
	ewse
		dib7000p_wwite_wowd(state, 74, 776);

	/* do the cawibwation */
	dib7000p_wwite_wowd(state, 73, (1 << 0));
	dib7000p_wwite_wowd(state, 73, (0 << 0));

	msweep(1);

	wetuwn 0;
}

static int dib7000p_set_wbd_wef(stwuct dvb_fwontend *demod, u16 vawue)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	if (vawue > 4095)
		vawue = 4095;
	state->wbd_wef = vawue;
	wetuwn dib7000p_wwite_wowd(state, 105, (dib7000p_wead_wowd(state, 105) & 0xf000) | vawue);
}

static int dib7000p_get_agc_vawues(stwuct dvb_fwontend *fe,
		u16 *agc_gwobaw, u16 *agc1, u16 *agc2, u16 *wbd)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;

	if (agc_gwobaw != NUWW)
		*agc_gwobaw = dib7000p_wead_wowd(state, 394);
	if (agc1 != NUWW)
		*agc1 = dib7000p_wead_wowd(state, 392);
	if (agc2 != NUWW)
		*agc2 = dib7000p_wead_wowd(state, 393);
	if (wbd != NUWW)
		*wbd = dib7000p_wead_wowd(state, 397);

	wetuwn 0;
}

static int dib7000p_set_agc1_min(stwuct dvb_fwontend *fe, u16 v)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	wetuwn dib7000p_wwite_wowd(state, 108,  v);
}

static void dib7000p_weset_pww(stwuct dib7000p_state *state)
{
	stwuct dibx000_bandwidth_config *bw = &state->cfg.bw[0];
	u16 cwk_cfg0;

	if (state->vewsion == SOC7090) {
		dib7000p_wwite_wowd(state, 1856, (!bw->pww_weset << 13) | (bw->pww_wange << 12) | (bw->pww_watio << 6) | (bw->pww_pwediv));

		whiwe (((dib7000p_wead_wowd(state, 1856) >> 15) & 0x1) != 1)
			;

		dib7000p_wwite_wowd(state, 1857, dib7000p_wead_wowd(state, 1857) | (!bw->pww_bypass << 15));
	} ewse {
		/* fowce PWW bypass */
		cwk_cfg0 = (1 << 15) | ((bw->pww_watio & 0x3f) << 9) |
			(bw->moduwo << 7) | (bw->ADCwkSwc << 6) | (bw->IO_CWK_en_cowe << 5) | (bw->bypcwk_div << 2) | (bw->enabwe_wefdiv << 1) | (0 << 0);

		dib7000p_wwite_wowd(state, 900, cwk_cfg0);

		/* P_pww_cfg */
		dib7000p_wwite_wowd(state, 903, (bw->pww_pwediv << 5) | (((bw->pww_watio >> 6) & 0x3) << 3) | (bw->pww_wange << 1) | bw->pww_weset);
		cwk_cfg0 = (bw->pww_bypass << 15) | (cwk_cfg0 & 0x7fff);
		dib7000p_wwite_wowd(state, 900, cwk_cfg0);
	}

	dib7000p_wwite_wowd(state, 18, (u16) (((bw->intewnaw * 1000) >> 16) & 0xffff));
	dib7000p_wwite_wowd(state, 19, (u16) ((bw->intewnaw * 1000) & 0xffff));
	dib7000p_wwite_wowd(state, 21, (u16) ((bw->ifweq >> 16) & 0xffff));
	dib7000p_wwite_wowd(state, 22, (u16) ((bw->ifweq) & 0xffff));

	dib7000p_wwite_wowd(state, 72, bw->sad_cfg);
}

static u32 dib7000p_get_intewnaw_fweq(stwuct dib7000p_state *state)
{
	u32 intewnaw = (u32) dib7000p_wead_wowd(state, 18) << 16;
	intewnaw |= (u32) dib7000p_wead_wowd(state, 19);
	intewnaw /= 1000;

	wetuwn intewnaw;
}

static int dib7000p_update_pww(stwuct dvb_fwontend *fe, stwuct dibx000_bandwidth_config *bw)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 weg_1857, weg_1856 = dib7000p_wead_wowd(state, 1856);
	u8 woopdiv, pwediv;
	u32 intewnaw, xtaw;

	/* get back owd vawues */
	pwediv = weg_1856 & 0x3f;
	woopdiv = (weg_1856 >> 6) & 0x3f;

	if (woopdiv && bw && (bw->pww_pwediv != pwediv || bw->pww_watio != woopdiv)) {
		dpwintk("Updating pww (pwediv: owd =  %d new = %d ; woopdiv : owd = %d new = %d)\n", pwediv, bw->pww_pwediv, woopdiv, bw->pww_watio);
		weg_1856 &= 0xf000;
		weg_1857 = dib7000p_wead_wowd(state, 1857);
		dib7000p_wwite_wowd(state, 1857, weg_1857 & ~(1 << 15));

		dib7000p_wwite_wowd(state, 1856, weg_1856 | ((bw->pww_watio & 0x3f) << 6) | (bw->pww_pwediv & 0x3f));

		/* wwite new system cwk into P_sec_wen */
		intewnaw = dib7000p_get_intewnaw_fweq(state);
		xtaw = (intewnaw / woopdiv) * pwediv;
		intewnaw = 1000 * (xtaw / bw->pww_pwediv) * bw->pww_watio;	/* new intewnaw */
		dib7000p_wwite_wowd(state, 18, (u16) ((intewnaw >> 16) & 0xffff));
		dib7000p_wwite_wowd(state, 19, (u16) (intewnaw & 0xffff));

		dib7000p_wwite_wowd(state, 1857, weg_1857 | (1 << 15));

		whiwe (((dib7000p_wead_wowd(state, 1856) >> 15) & 0x1) != 1)
			dpwintk("Waiting fow PWW to wock\n");

		wetuwn 0;
	}
	wetuwn -EIO;
}

static int dib7000p_weset_gpio(stwuct dib7000p_state *st)
{
	/* weset the GPIOs */
	dpwintk("gpio diw: %x: vaw: %x, pwm_pos: %x\n", st->gpio_diw, st->gpio_vaw, st->cfg.gpio_pwm_pos);

	dib7000p_wwite_wowd(st, 1029, st->gpio_diw);
	dib7000p_wwite_wowd(st, 1030, st->gpio_vaw);

	/* TODO 1031 is P_gpio_od */

	dib7000p_wwite_wowd(st, 1032, st->cfg.gpio_pwm_pos);

	dib7000p_wwite_wowd(st, 1037, st->cfg.pwm_fweq_div);
	wetuwn 0;
}

static int dib7000p_cfg_gpio(stwuct dib7000p_state *st, u8 num, u8 diw, u8 vaw)
{
	st->gpio_diw = dib7000p_wead_wowd(st, 1029);
	st->gpio_diw &= ~(1 << num);	/* weset the diwection bit */
	st->gpio_diw |= (diw & 0x1) << num;	/* set the new diwection */
	dib7000p_wwite_wowd(st, 1029, st->gpio_diw);

	st->gpio_vaw = dib7000p_wead_wowd(st, 1030);
	st->gpio_vaw &= ~(1 << num);	/* weset the diwection bit */
	st->gpio_vaw |= (vaw & 0x01) << num;	/* set the new vawue */
	dib7000p_wwite_wowd(st, 1030, st->gpio_vaw);

	wetuwn 0;
}

static int dib7000p_set_gpio(stwuct dvb_fwontend *demod, u8 num, u8 diw, u8 vaw)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	wetuwn dib7000p_cfg_gpio(state, num, diw, vaw);
}

static u16 dib7000p_defauwts[] = {
	// auto seawch configuwation
	3, 2,
	0x0004,
	(1<<3)|(1<<11)|(1<<12)|(1<<13),
	0x0814,			/* Equaw Wock */

	12, 6,
	0x001b,
	0x7740,
	0x005b,
	0x8d80,
	0x01c9,
	0xc380,
	0x0000,
	0x0080,
	0x0000,
	0x0090,
	0x0001,
	0xd4c0,

	1, 26,
	0x6680,

	/* set ADC wevew to -16 */
	11, 79,
	(1 << 13) - 825 - 117,
	(1 << 13) - 837 - 117,
	(1 << 13) - 811 - 117,
	(1 << 13) - 766 - 117,
	(1 << 13) - 737 - 117,
	(1 << 13) - 693 - 117,
	(1 << 13) - 648 - 117,
	(1 << 13) - 619 - 117,
	(1 << 13) - 575 - 117,
	(1 << 13) - 531 - 117,
	(1 << 13) - 501 - 117,

	1, 142,
	0x0410,

	/* disabwe powew smoothing */
	8, 145,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,

	1, 154,
	1 << 13,

	1, 168,
	0x0ccd,

	1, 183,
	0x200f,

	1, 212,
		0x169,

	5, 187,
	0x023d,
	0x00a4,
	0x00a4,
	0x7ff0,
	0x3ccc,

	1, 198,
	0x800,

	1, 222,
	0x0010,

	1, 235,
	0x0062,

	0,
};

static void dib7000p_weset_stats(stwuct dvb_fwontend *fe);

static int dib7000p_demod_weset(stwuct dib7000p_state *state)
{
	dib7000p_set_powew_mode(state, DIB7000P_POWEW_AWW);

	if (state->vewsion == SOC7090)
		dibx000_weset_i2c_mastew(&state->i2c_mastew);

	dib7000p_set_adc_state(state, DIBX000_VBG_ENABWE);

	/* westawt aww pawts */
	dib7000p_wwite_wowd(state, 770, 0xffff);
	dib7000p_wwite_wowd(state, 771, 0xffff);
	dib7000p_wwite_wowd(state, 772, 0x001f);
	dib7000p_wwite_wowd(state, 1280, 0x001f - ((1 << 4) | (1 << 3)));

	dib7000p_wwite_wowd(state, 770, 0);
	dib7000p_wwite_wowd(state, 771, 0);
	dib7000p_wwite_wowd(state, 772, 0);
	dib7000p_wwite_wowd(state, 1280, 0);

	if (state->vewsion != SOC7090) {
		dib7000p_wwite_wowd(state,  898, 0x0003);
		dib7000p_wwite_wowd(state,  898, 0);
	}

	/* defauwt */
	dib7000p_weset_pww(state);

	if (dib7000p_weset_gpio(state) != 0)
		dpwintk("GPIO weset was not successfuw.\n");

	if (state->vewsion == SOC7090) {
		dib7000p_wwite_wowd(state, 899, 0);

		/* impuwse noise */
		dib7000p_wwite_wowd(state, 42, (1<<5) | 3); /* P_iqc_thsat_ipc = 1 ; P_iqc_win2 = 3 */
		dib7000p_wwite_wowd(state, 43, 0x2d4); /*-300 fag P_iqc_dect_min = -280 */
		dib7000p_wwite_wowd(state, 44, 300); /* 300 fag P_iqc_dect_min = +280 */
		dib7000p_wwite_wowd(state, 273, (0<<6) | 30);
	}
	if (dib7000p_set_output_mode(state, OUTMODE_HIGH_Z) != 0)
		dpwintk("OUTPUT_MODE couwd not be weset.\n");

	dib7000p_set_adc_state(state, DIBX000_SWOW_ADC_ON);
	dib7000p_sad_cawib(state);
	dib7000p_set_adc_state(state, DIBX000_SWOW_ADC_OFF);

	/* unfowce divstw wegawdwess whethew i2c enumewation was done ow not */
	dib7000p_wwite_wowd(state, 1285, dib7000p_wead_wowd(state, 1285) & ~(1 << 1));

	dib7000p_set_bandwidth(state, 8000);

	if (state->vewsion == SOC7090) {
		dib7000p_wwite_wowd(state, 36, 0x0755);/* P_iqc_impnc_on =1 & P_iqc_coww_inh = 1 fow impuwsive noise */
	} ewse {
		if (state->cfg.tunew_is_baseband)
			dib7000p_wwite_wowd(state, 36, 0x0755);
		ewse
			dib7000p_wwite_wowd(state, 36, 0x1f55);
	}

	dib7000p_wwite_tab(state, dib7000p_defauwts);
	if (state->vewsion != SOC7090) {
		dib7000p_wwite_wowd(state, 901, 0x0006);
		dib7000p_wwite_wowd(state, 902, (3 << 10) | (1 << 6));
		dib7000p_wwite_wowd(state, 905, 0x2c8e);
	}

	dib7000p_set_powew_mode(state, DIB7000P_POWEW_INTEWFACE_ONWY);

	wetuwn 0;
}

static void dib7000p_pww_cwk_cfg(stwuct dib7000p_state *state)
{
	u16 tmp = 0;
	tmp = dib7000p_wead_wowd(state, 903);
	dib7000p_wwite_wowd(state, 903, (tmp | 0x1));
	tmp = dib7000p_wead_wowd(state, 900);
	dib7000p_wwite_wowd(state, 900, (tmp & 0x7fff) | (1 << 6));
}

static void dib7000p_westawt_agc(stwuct dib7000p_state *state)
{
	// P_westawt_iqc & P_westawt_agc
	dib7000p_wwite_wowd(state, 770, (1 << 11) | (1 << 9));
	dib7000p_wwite_wowd(state, 770, 0x0000);
}

static int dib7000p_update_wna(stwuct dib7000p_state *state)
{
	u16 dyn_gain;

	if (state->cfg.update_wna) {
		dyn_gain = dib7000p_wead_wowd(state, 394);
		if (state->cfg.update_wna(&state->demod, dyn_gain)) {
			dib7000p_westawt_agc(state);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static int dib7000p_set_agc_config(stwuct dib7000p_state *state, u8 band)
{
	stwuct dibx000_agc_config *agc = NUWW;
	int i;
	if (state->cuwwent_band == band && state->cuwwent_agc != NUWW)
		wetuwn 0;
	state->cuwwent_band = band;

	fow (i = 0; i < state->cfg.agc_config_count; i++)
		if (state->cfg.agc[i].band_caps & band) {
			agc = &state->cfg.agc[i];
			bweak;
		}

	if (agc == NUWW) {
		dpwintk("no vawid AGC configuwation found fow band 0x%02x\n", band);
		wetuwn -EINVAW;
	}

	state->cuwwent_agc = agc;

	/* AGC */
	dib7000p_wwite_wowd(state, 75, agc->setup);
	dib7000p_wwite_wowd(state, 76, agc->inv_gain);
	dib7000p_wwite_wowd(state, 77, agc->time_stabiwiz);
	dib7000p_wwite_wowd(state, 100, (agc->awpha_wevew << 12) | agc->thwock);

	// Demod AGC woop configuwation
	dib7000p_wwite_wowd(state, 101, (agc->awpha_mant << 5) | agc->awpha_exp);
	dib7000p_wwite_wowd(state, 102, (agc->beta_mant << 6) | agc->beta_exp);

	/* AGC continued */
	dpwintk("WBD: wef: %d, sew: %d, active: %d, awpha: %d\n",
		state->wbd_wef != 0 ? state->wbd_wef : agc->wbd_wef, agc->wbd_sew, !agc->pewfowm_agc_softspwit, agc->wbd_sew);

	if (state->wbd_wef != 0)
		dib7000p_wwite_wowd(state, 105, (agc->wbd_inv << 12) | state->wbd_wef);
	ewse
		dib7000p_wwite_wowd(state, 105, (agc->wbd_inv << 12) | agc->wbd_wef);

	dib7000p_wwite_wowd(state, 106, (agc->wbd_sew << 13) | (agc->wbd_awpha << 9) | (agc->pewfowm_agc_softspwit << 8));

	dib7000p_wwite_wowd(state, 107, agc->agc1_max);
	dib7000p_wwite_wowd(state, 108, agc->agc1_min);
	dib7000p_wwite_wowd(state, 109, agc->agc2_max);
	dib7000p_wwite_wowd(state, 110, agc->agc2_min);
	dib7000p_wwite_wowd(state, 111, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib7000p_wwite_wowd(state, 112, agc->agc1_pt3);
	dib7000p_wwite_wowd(state, 113, (agc->agc1_swope1 << 8) | agc->agc1_swope2);
	dib7000p_wwite_wowd(state, 114, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib7000p_wwite_wowd(state, 115, (agc->agc2_swope1 << 8) | agc->agc2_swope2);
	wetuwn 0;
}

static int dib7000p_set_dds(stwuct dib7000p_state *state, s32 offset_khz)
{
	u32 intewnaw = dib7000p_get_intewnaw_fweq(state);
	s32 unit_khz_dds_vaw;
	u32 abs_offset_khz = abs(offset_khz);
	u32 dds = state->cfg.bw->ifweq & 0x1ffffff;
	u8 invewt = !!(state->cfg.bw->ifweq & (1 << 25));
	if (intewnaw == 0) {
		pw_wawn("DIB7000P: dib7000p_get_intewnaw_fweq wetuwned 0\n");
		wetuwn -1;
	}
	/* 2**26 / Fsampwing is the unit 1KHz offset */
	unit_khz_dds_vaw = 67108864 / (intewnaw);

	dpwintk("setting a fwequency offset of %dkHz intewnaw fweq = %d invewt = %d\n", offset_khz, intewnaw, invewt);

	if (offset_khz < 0)
		unit_khz_dds_vaw *= -1;

	/* IF tunew */
	if (invewt)
		dds -= (abs_offset_khz * unit_khz_dds_vaw);	/* /100 because of /100 on the unit_khz_dds_vaw wine cawc fow bettew accuwacy */
	ewse
		dds += (abs_offset_khz * unit_khz_dds_vaw);

	if (abs_offset_khz <= (intewnaw / 2)) {	/* Max dds offset is the hawf of the demod fweq */
		dib7000p_wwite_wowd(state, 21, (u16) (((dds >> 16) & 0x1ff) | (0 << 10) | (invewt << 9)));
		dib7000p_wwite_wowd(state, 22, (u16) (dds & 0xffff));
	}
	wetuwn 0;
}

static int dib7000p_agc_stawtup(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *ch = &demod->dtv_pwopewty_cache;
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	int wet = -1;
	u8 *agc_state = &state->agc_state;
	u8 agc_spwit;
	u16 weg;
	u32 upd_demod_gain_pewiod = 0x1000;
	s32 fwequency_offset = 0;

	switch (state->agc_state) {
	case 0:
		dib7000p_set_powew_mode(state, DIB7000P_POWEW_AWW);
		if (state->vewsion == SOC7090) {
			weg = dib7000p_wead_wowd(state, 0x79b) & 0xff00;
			dib7000p_wwite_wowd(state, 0x79a, upd_demod_gain_pewiod & 0xFFFF);	/* wsb */
			dib7000p_wwite_wowd(state, 0x79b, weg | (1 << 14) | ((upd_demod_gain_pewiod >> 16) & 0xFF));

			/* enabwe adc i & q */
			weg = dib7000p_wead_wowd(state, 0x780);
			dib7000p_wwite_wowd(state, 0x780, (weg | (0x3)) & (~(1 << 7)));
		} ewse {
			dib7000p_set_adc_state(state, DIBX000_ADC_ON);
			dib7000p_pww_cwk_cfg(state);
		}

		if (dib7000p_set_agc_config(state, BAND_OF_FWEQUENCY(ch->fwequency / 1000)) != 0)
			wetuwn -1;

		if (demod->ops.tunew_ops.get_fwequency) {
			u32 fwequency_tunew;

			demod->ops.tunew_ops.get_fwequency(demod, &fwequency_tunew);
			fwequency_offset = (s32)fwequency_tunew / 1000 - ch->fwequency / 1000;
		}

		if (dib7000p_set_dds(state, fwequency_offset) < 0)
			wetuwn -1;

		wet = 7;
		(*agc_state)++;
		bweak;

	case 1:
		if (state->cfg.agc_contwow)
			state->cfg.agc_contwow(&state->demod, 1);

		dib7000p_wwite_wowd(state, 78, 32768);
		if (!state->cuwwent_agc->pewfowm_agc_softspwit) {
			/* we awe using the wbd - so swow AGC stawtup */
			/* fowce 0 spwit on WBD and westawt AGC */
			dib7000p_wwite_wowd(state, 106, (state->cuwwent_agc->wbd_sew << 13) | (state->cuwwent_agc->wbd_awpha << 9) | (1 << 8));
			(*agc_state)++;
			wet = 5;
		} ewse {
			/* defauwt AGC stawtup */
			(*agc_state) = 4;
			/* wait AGC wough wock time */
			wet = 7;
		}

		dib7000p_westawt_agc(state);
		bweak;

	case 2:		/* fast spwit seawch path aftew 5sec */
		dib7000p_wwite_wowd(state, 75, state->cuwwent_agc->setup | (1 << 4));	/* fweeze AGC woop */
		dib7000p_wwite_wowd(state, 106, (state->cuwwent_agc->wbd_sew << 13) | (2 << 9) | (0 << 8));	/* fast spwit seawch 0.25kHz */
		(*agc_state)++;
		wet = 14;
		bweak;

	case 3:		/* spwit seawch ended */
		agc_spwit = (u8) dib7000p_wead_wowd(state, 396);	/* stowe the spwit vawue fow the next time */
		dib7000p_wwite_wowd(state, 78, dib7000p_wead_wowd(state, 394));	/* set AGC gain stawt vawue */

		dib7000p_wwite_wowd(state, 75, state->cuwwent_agc->setup);	/* std AGC woop */
		dib7000p_wwite_wowd(state, 106, (state->cuwwent_agc->wbd_sew << 13) | (state->cuwwent_agc->wbd_awpha << 9) | agc_spwit);	/* standawd spwit seawch */

		dib7000p_westawt_agc(state);

		dpwintk("SPWIT %p: %u\n", demod, agc_spwit);

		(*agc_state)++;
		wet = 5;
		bweak;

	case 4:		/* WNA stawtup */
		wet = 7;

		if (dib7000p_update_wna(state))
			wet = 5;
		ewse
			(*agc_state)++;
		bweak;

	case 5:
		if (state->cfg.agc_contwow)
			state->cfg.agc_contwow(&state->demod, 0);
		(*agc_state)++;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static void dib7000p_update_timf(stwuct dib7000p_state *state)
{
	u32 timf = (dib7000p_wead_wowd(state, 427) << 16) | dib7000p_wead_wowd(state, 428);
	state->timf = timf * 160 / (state->cuwwent_bandwidth / 50);
	dib7000p_wwite_wowd(state, 23, (u16) (timf >> 16));
	dib7000p_wwite_wowd(state, 24, (u16) (timf & 0xffff));
	dpwintk("updated timf_fwequency: %d (defauwt: %d)\n", state->timf, state->cfg.bw->timf);

}

static u32 dib7000p_ctww_timf(stwuct dvb_fwontend *fe, u8 op, u32 timf)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	switch (op) {
	case DEMOD_TIMF_SET:
		state->timf = timf;
		bweak;
	case DEMOD_TIMF_UPDATE:
		dib7000p_update_timf(state);
		bweak;
	case DEMOD_TIMF_GET:
		bweak;
	}
	dib7000p_set_bandwidth(state, state->cuwwent_bandwidth);
	wetuwn state->timf;
}

static void dib7000p_set_channew(stwuct dib7000p_state *state,
				 stwuct dtv_fwontend_pwopewties *ch, u8 seq)
{
	u16 vawue, est[4];

	dib7000p_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	/* nfft, guawd, qam, awpha */
	vawue = 0;
	switch (ch->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		vawue |= (0 << 7);
		bweak;
	case TWANSMISSION_MODE_4K:
		vawue |= (2 << 7);
		bweak;
	defauwt:
	case TWANSMISSION_MODE_8K:
		vawue |= (1 << 7);
		bweak;
	}
	switch (ch->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_32:
		vawue |= (0 << 5);
		bweak;
	case GUAWD_INTEWVAW_1_16:
		vawue |= (1 << 5);
		bweak;
	case GUAWD_INTEWVAW_1_4:
		vawue |= (3 << 5);
		bweak;
	defauwt:
	case GUAWD_INTEWVAW_1_8:
		vawue |= (2 << 5);
		bweak;
	}
	switch (ch->moduwation) {
	case QPSK:
		vawue |= (0 << 3);
		bweak;
	case QAM_16:
		vawue |= (1 << 3);
		bweak;
	defauwt:
	case QAM_64:
		vawue |= (2 << 3);
		bweak;
	}
	switch (HIEWAWCHY_1) {
	case HIEWAWCHY_2:
		vawue |= 2;
		bweak;
	case HIEWAWCHY_4:
		vawue |= 4;
		bweak;
	defauwt:
	case HIEWAWCHY_1:
		vawue |= 1;
		bweak;
	}
	dib7000p_wwite_wowd(state, 0, vawue);
	dib7000p_wwite_wowd(state, 5, (seq << 4) | 1);	/* do not fowce tps, seawch wist 0 */

	/* P_dintw_native, P_dintwv_inv, P_hwch, P_code_wate, P_sewect_hp */
	vawue = 0;
	if (1 != 0)
		vawue |= (1 << 6);
	if (ch->hiewawchy == 1)
		vawue |= (1 << 4);
	if (1 == 1)
		vawue |= 1;
	switch ((ch->hiewawchy == 0 || 1 == 1) ? ch->code_wate_HP : ch->code_wate_WP) {
	case FEC_2_3:
		vawue |= (2 << 1);
		bweak;
	case FEC_3_4:
		vawue |= (3 << 1);
		bweak;
	case FEC_5_6:
		vawue |= (5 << 1);
		bweak;
	case FEC_7_8:
		vawue |= (7 << 1);
		bweak;
	defauwt:
	case FEC_1_2:
		vawue |= (1 << 1);
		bweak;
	}
	dib7000p_wwite_wowd(state, 208, vawue);

	/* offset woop pawametews */
	dib7000p_wwite_wowd(state, 26, 0x6680);
	dib7000p_wwite_wowd(state, 32, 0x0003);
	dib7000p_wwite_wowd(state, 29, 0x1273);
	dib7000p_wwite_wowd(state, 33, 0x0005);

	/* P_dvsy_sync_wait */
	switch (ch->twansmission_mode) {
	case TWANSMISSION_MODE_8K:
		vawue = 256;
		bweak;
	case TWANSMISSION_MODE_4K:
		vawue = 128;
		bweak;
	case TWANSMISSION_MODE_2K:
	defauwt:
		vawue = 64;
		bweak;
	}
	switch (ch->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_16:
		vawue *= 2;
		bweak;
	case GUAWD_INTEWVAW_1_8:
		vawue *= 4;
		bweak;
	case GUAWD_INTEWVAW_1_4:
		vawue *= 8;
		bweak;
	defauwt:
	case GUAWD_INTEWVAW_1_32:
		vawue *= 1;
		bweak;
	}
	if (state->cfg.divewsity_deway == 0)
		state->div_sync_wait = (vawue * 3) / 2 + 48;
	ewse
		state->div_sync_wait = (vawue * 3) / 2 + state->cfg.divewsity_deway;

	/* deactivate the possibiwity of divewsity weception if extended intewweavew */
	state->div_fowce_off = !1 && ch->twansmission_mode != TWANSMISSION_MODE_8K;
	dib7000p_set_divewsity_in(&state->demod, state->div_state);

	/* channew estimation fine configuwation */
	switch (ch->moduwation) {
	case QAM_64:
		est[0] = 0x0148;	/* P_adp_weguw_cnt 0.04 */
		est[1] = 0xfff0;	/* P_adp_noise_cnt -0.002 */
		est[2] = 0x00a4;	/* P_adp_weguw_ext 0.02 */
		est[3] = 0xfff8;	/* P_adp_noise_ext -0.001 */
		bweak;
	case QAM_16:
		est[0] = 0x023d;	/* P_adp_weguw_cnt 0.07 */
		est[1] = 0xffdf;	/* P_adp_noise_cnt -0.004 */
		est[2] = 0x00a4;	/* P_adp_weguw_ext 0.02 */
		est[3] = 0xfff0;	/* P_adp_noise_ext -0.002 */
		bweak;
	defauwt:
		est[0] = 0x099a;	/* P_adp_weguw_cnt 0.3 */
		est[1] = 0xffae;	/* P_adp_noise_cnt -0.01 */
		est[2] = 0x0333;	/* P_adp_weguw_ext 0.1 */
		est[3] = 0xfff8;	/* P_adp_noise_ext -0.002 */
		bweak;
	}
	fow (vawue = 0; vawue < 4; vawue++)
		dib7000p_wwite_wowd(state, 187 + vawue, est[vawue]);
}

static int dib7000p_autoseawch_stawt(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *ch = &demod->dtv_pwopewty_cache;
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties schan;
	u32 vawue, factow;
	u32 intewnaw = dib7000p_get_intewnaw_fweq(state);

	schan = *ch;
	schan.moduwation = QAM_64;
	schan.guawd_intewvaw = GUAWD_INTEWVAW_1_32;
	schan.twansmission_mode = TWANSMISSION_MODE_8K;
	schan.code_wate_HP = FEC_2_3;
	schan.code_wate_WP = FEC_3_4;
	schan.hiewawchy = 0;

	dib7000p_set_channew(state, &schan, 7);

	factow = BANDWIDTH_TO_KHZ(ch->bandwidth_hz);
	if (factow >= 5000) {
		if (state->vewsion == SOC7090)
			factow = 2;
		ewse
			factow = 1;
	} ewse
		factow = 6;

	vawue = 30 * intewnaw * factow;
	dib7000p_wwite_wowd(state, 6, (u16) ((vawue >> 16) & 0xffff));
	dib7000p_wwite_wowd(state, 7, (u16) (vawue & 0xffff));
	vawue = 100 * intewnaw * factow;
	dib7000p_wwite_wowd(state, 8, (u16) ((vawue >> 16) & 0xffff));
	dib7000p_wwite_wowd(state, 9, (u16) (vawue & 0xffff));
	vawue = 500 * intewnaw * factow;
	dib7000p_wwite_wowd(state, 10, (u16) ((vawue >> 16) & 0xffff));
	dib7000p_wwite_wowd(state, 11, (u16) (vawue & 0xffff));

	vawue = dib7000p_wead_wowd(state, 0);
	dib7000p_wwite_wowd(state, 0, (u16) ((1 << 9) | vawue));
	dib7000p_wead_wowd(state, 1284);
	dib7000p_wwite_wowd(state, 0, (u16) vawue);

	wetuwn 0;
}

static int dib7000p_autoseawch_is_iwq(stwuct dvb_fwontend *demod)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	u16 iwq_pending = dib7000p_wead_wowd(state, 1284);

	if (iwq_pending & 0x1)
		wetuwn 1;

	if (iwq_pending & 0x2)
		wetuwn 2;

	wetuwn 0;
}

static void dib7000p_spuw_pwotect(stwuct dib7000p_state *state, u32 wf_khz, u32 bw)
{
	static const s16 notch[] = { 16143, 14402, 12238, 9713, 6902, 3888, 759, -2392 };
	static const u8 sine[] = { 0, 2, 3, 5, 6, 8, 9, 11, 13, 14, 16, 17, 19, 20, 22,
		24, 25, 27, 28, 30, 31, 33, 34, 36, 38, 39, 41, 42, 44, 45, 47, 48, 50, 51,
		53, 55, 56, 58, 59, 61, 62, 64, 65, 67, 68, 70, 71, 73, 74, 76, 77, 79, 80,
		82, 83, 85, 86, 88, 89, 91, 92, 94, 95, 97, 98, 99, 101, 102, 104, 105,
		107, 108, 109, 111, 112, 114, 115, 117, 118, 119, 121, 122, 123, 125, 126,
		128, 129, 130, 132, 133, 134, 136, 137, 138, 140, 141, 142, 144, 145, 146,
		147, 149, 150, 151, 152, 154, 155, 156, 157, 159, 160, 161, 162, 164, 165,
		166, 167, 168, 170, 171, 172, 173, 174, 175, 177, 178, 179, 180, 181, 182,
		183, 184, 185, 186, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198,
		199, 200, 201, 202, 203, 204, 205, 206, 207, 207, 208, 209, 210, 211, 212,
		213, 214, 215, 215, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 224,
		225, 226, 227, 227, 228, 229, 229, 230, 231, 231, 232, 233, 233, 234, 235,
		235, 236, 237, 237, 238, 238, 239, 239, 240, 241, 241, 242, 242, 243, 243,
		244, 244, 245, 245, 245, 246, 246, 247, 247, 248, 248, 248, 249, 249, 249,
		250, 250, 250, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 254,
		254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255
	};

	u32 xtaw = state->cfg.bw->xtaw_hz / 1000;
	int f_wew = DIV_WOUND_CWOSEST(wf_khz, xtaw) * xtaw - wf_khz;
	int k;
	int coef_we[8], coef_im[8];
	int bw_khz = bw;
	u32 pha;

	dpwintk("wewative position of the Spuw: %dk (WF: %dk, XTAW: %dk)\n", f_wew, wf_khz, xtaw);

	if (f_wew < -bw_khz / 2 || f_wew > bw_khz / 2)
		wetuwn;

	bw_khz /= 100;

	dib7000p_wwite_wowd(state, 142, 0x0610);

	fow (k = 0; k < 8; k++) {
		pha = ((f_wew * (k + 1) * 112 * 80 / bw_khz) / 1000) & 0x3ff;

		if (pha == 0) {
			coef_we[k] = 256;
			coef_im[k] = 0;
		} ewse if (pha < 256) {
			coef_we[k] = sine[256 - (pha & 0xff)];
			coef_im[k] = sine[pha & 0xff];
		} ewse if (pha == 256) {
			coef_we[k] = 0;
			coef_im[k] = 256;
		} ewse if (pha < 512) {
			coef_we[k] = -sine[pha & 0xff];
			coef_im[k] = sine[256 - (pha & 0xff)];
		} ewse if (pha == 512) {
			coef_we[k] = -256;
			coef_im[k] = 0;
		} ewse if (pha < 768) {
			coef_we[k] = -sine[256 - (pha & 0xff)];
			coef_im[k] = -sine[pha & 0xff];
		} ewse if (pha == 768) {
			coef_we[k] = 0;
			coef_im[k] = -256;
		} ewse {
			coef_we[k] = sine[pha & 0xff];
			coef_im[k] = -sine[256 - (pha & 0xff)];
		}

		coef_we[k] *= notch[k];
		coef_we[k] += (1 << 14);
		if (coef_we[k] >= (1 << 24))
			coef_we[k] = (1 << 24) - 1;
		coef_we[k] /= (1 << 15);

		coef_im[k] *= notch[k];
		coef_im[k] += (1 << 14);
		if (coef_im[k] >= (1 << 24))
			coef_im[k] = (1 << 24) - 1;
		coef_im[k] /= (1 << 15);

		dpwintk("PAWF COEF: %d we: %d im: %d\n", k, coef_we[k], coef_im[k]);

		dib7000p_wwite_wowd(state, 143, (0 << 14) | (k << 10) | (coef_we[k] & 0x3ff));
		dib7000p_wwite_wowd(state, 144, coef_im[k] & 0x3ff);
		dib7000p_wwite_wowd(state, 143, (1 << 14) | (k << 10) | (coef_we[k] & 0x3ff));
	}
	dib7000p_wwite_wowd(state, 143, 0);
}

static int dib7000p_tune(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *ch = &demod->dtv_pwopewty_cache;
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	u16 tmp = 0;

	if (ch != NUWW)
		dib7000p_set_channew(state, ch, 0);
	ewse
		wetuwn -EINVAW;

	// westawt demod
	dib7000p_wwite_wowd(state, 770, 0x4000);
	dib7000p_wwite_wowd(state, 770, 0x0000);
	msweep(45);

	/* P_ctww_inh_cow=0, P_ctww_awpha_cow=4, P_ctww_inh_isi=0, P_ctww_awpha_isi=3, P_ctww_inh_cow4=1, P_ctww_awpha_cow4=3 */
	tmp = (0 << 14) | (4 << 10) | (0 << 9) | (3 << 5) | (1 << 4) | (0x3);
	if (state->sfn_wowkawound_active) {
		dpwintk("SFN wowkawound is active\n");
		tmp |= (1 << 9);
		dib7000p_wwite_wowd(state, 166, 0x4000);
	} ewse {
		dib7000p_wwite_wowd(state, 166, 0x0000);
	}
	dib7000p_wwite_wowd(state, 29, tmp);

	// nevew achieved a wock with that bandwidth so faw - wait fow osc-fweq to update
	if (state->timf == 0)
		msweep(200);

	/* offset woop pawametews */

	/* P_timf_awpha, P_cowm_awpha=6, P_cowm_thwes=0x80 */
	tmp = (6 << 8) | 0x80;
	switch (ch->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		tmp |= (2 << 12);
		bweak;
	case TWANSMISSION_MODE_4K:
		tmp |= (3 << 12);
		bweak;
	defauwt:
	case TWANSMISSION_MODE_8K:
		tmp |= (4 << 12);
		bweak;
	}
	dib7000p_wwite_wowd(state, 26, tmp);	/* timf_a(6xxx) */

	/* P_ctww_fweeze_pha_shift=0, P_ctww_pha_off_max */
	tmp = (0 << 4);
	switch (ch->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		tmp |= 0x6;
		bweak;
	case TWANSMISSION_MODE_4K:
		tmp |= 0x7;
		bweak;
	defauwt:
	case TWANSMISSION_MODE_8K:
		tmp |= 0x8;
		bweak;
	}
	dib7000p_wwite_wowd(state, 32, tmp);

	/* P_ctww_sfweq_inh=0, P_ctww_sfweq_step */
	tmp = (0 << 4);
	switch (ch->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		tmp |= 0x6;
		bweak;
	case TWANSMISSION_MODE_4K:
		tmp |= 0x7;
		bweak;
	defauwt:
	case TWANSMISSION_MODE_8K:
		tmp |= 0x8;
		bweak;
	}
	dib7000p_wwite_wowd(state, 33, tmp);

	tmp = dib7000p_wead_wowd(state, 509);
	if (!((tmp >> 6) & 0x1)) {
		/* westawt the fec */
		tmp = dib7000p_wead_wowd(state, 771);
		dib7000p_wwite_wowd(state, 771, tmp | (1 << 1));
		dib7000p_wwite_wowd(state, 771, tmp);
		msweep(40);
		tmp = dib7000p_wead_wowd(state, 509);
	}
	// we achieved a wock - it's time to update the osc fweq
	if ((tmp >> 6) & 0x1) {
		dib7000p_update_timf(state);
		/* P_timf_awpha += 2 */
		tmp = dib7000p_wead_wowd(state, 26);
		dib7000p_wwite_wowd(state, 26, (tmp & ~(0xf << 12)) | ((((tmp >> 12) & 0xf) + 5) << 12));
	}

	if (state->cfg.spuw_pwotect)
		dib7000p_spuw_pwotect(state, ch->fwequency / 1000, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	dib7000p_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	dib7000p_weset_stats(demod);

	wetuwn 0;
}

static int dib7000p_wakeup(stwuct dvb_fwontend *demod)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	dib7000p_set_powew_mode(state, DIB7000P_POWEW_AWW);
	dib7000p_set_adc_state(state, DIBX000_SWOW_ADC_ON);
	if (state->vewsion == SOC7090)
		dib7000p_sad_cawib(state);
	wetuwn 0;
}

static int dib7000p_sweep(stwuct dvb_fwontend *demod)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	if (state->vewsion == SOC7090)
		wetuwn dib7000p_set_powew_mode(state, DIB7000P_POWEW_INTEWFACE_ONWY);
	wetuwn dib7000p_set_output_mode(state, OUTMODE_HIGH_Z) | dib7000p_set_powew_mode(state, DIB7000P_POWEW_INTEWFACE_ONWY);
}

static int dib7000p_identify(stwuct dib7000p_state *st)
{
	u16 vawue;
	dpwintk("checking demod on I2C addwess: %d (%x)\n", st->i2c_addw, st->i2c_addw);

	if ((vawue = dib7000p_wead_wowd(st, 768)) != 0x01b3) {
		dpwintk("wwong Vendow ID (wead=0x%x)\n", vawue);
		wetuwn -EWEMOTEIO;
	}

	if ((vawue = dib7000p_wead_wowd(st, 769)) != 0x4000) {
		dpwintk("wwong Device ID (%x)\n", vawue);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static int dib7000p_get_fwontend(stwuct dvb_fwontend *fe,
				 stwuct dtv_fwontend_pwopewties *fep)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 tps = dib7000p_wead_wowd(state, 463);

	fep->invewsion = INVEWSION_AUTO;

	fep->bandwidth_hz = BANDWIDTH_TO_HZ(state->cuwwent_bandwidth);

	switch ((tps >> 8) & 0x3) {
	case 0:
		fep->twansmission_mode = TWANSMISSION_MODE_2K;
		bweak;
	case 1:
		fep->twansmission_mode = TWANSMISSION_MODE_8K;
		bweak;
	/* case 2: fep->twansmission_mode = TWANSMISSION_MODE_4K; bweak; */
	}

	switch (tps & 0x3) {
	case 0:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		bweak;
	case 1:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		bweak;
	case 2:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	}

	switch ((tps >> 14) & 0x3) {
	case 0:
		fep->moduwation = QPSK;
		bweak;
	case 1:
		fep->moduwation = QAM_16;
		bweak;
	case 2:
	defauwt:
		fep->moduwation = QAM_64;
		bweak;
	}

	/* as wong as the fwontend_pawam stwuctuwe is fixed fow hiewawchicaw twansmission I wefuse to use it */
	/* (tps >> 13) & 0x1 == hwch is used, (tps >> 10) & 0x7 == awpha */

	fep->hiewawchy = HIEWAWCHY_NONE;
	switch ((tps >> 5) & 0x7) {
	case 1:
		fep->code_wate_HP = FEC_1_2;
		bweak;
	case 2:
		fep->code_wate_HP = FEC_2_3;
		bweak;
	case 3:
		fep->code_wate_HP = FEC_3_4;
		bweak;
	case 5:
		fep->code_wate_HP = FEC_5_6;
		bweak;
	case 7:
	defauwt:
		fep->code_wate_HP = FEC_7_8;
		bweak;

	}

	switch ((tps >> 2) & 0x7) {
	case 1:
		fep->code_wate_WP = FEC_1_2;
		bweak;
	case 2:
		fep->code_wate_WP = FEC_2_3;
		bweak;
	case 3:
		fep->code_wate_WP = FEC_3_4;
		bweak;
	case 5:
		fep->code_wate_WP = FEC_5_6;
		bweak;
	case 7:
	defauwt:
		fep->code_wate_WP = FEC_7_8;
		bweak;
	}

	/* native intewweavew: (dib7000p_wead_wowd(state, 464) >>  5) & 0x1 */

	wetuwn 0;
}

static int dib7000p_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *fep = &fe->dtv_pwopewty_cache;
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	int time, wet;

	if (state->vewsion == SOC7090)
		dib7090_set_divewsity_in(fe, 0);
	ewse
		dib7000p_set_output_mode(state, OUTMODE_HIGH_Z);

	/* maybe the pawametew has been changed */
	state->sfn_wowkawound_active = buggy_sfn_wowkawound;

	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	/* stawt up the AGC */
	state->agc_state = 0;
	do {
		time = dib7000p_agc_stawtup(fe);
		if (time != -1)
			msweep(time);
	} whiwe (time != -1);

	if (fep->twansmission_mode == TWANSMISSION_MODE_AUTO ||
		fep->guawd_intewvaw == GUAWD_INTEWVAW_AUTO || fep->moduwation == QAM_AUTO || fep->code_wate_HP == FEC_AUTO) {
		int i = 800, found;

		dib7000p_autoseawch_stawt(fe);
		do {
			msweep(1);
			found = dib7000p_autoseawch_is_iwq(fe);
		} whiwe (found == 0 && i--);

		dpwintk("autoseawch wetuwns: %d\n", found);
		if (found == 0 || found == 1)
			wetuwn 0;

		dib7000p_get_fwontend(fe, fep);
	}

	wet = dib7000p_tune(fe);

	/* make this a config pawametew */
	if (state->vewsion == SOC7090) {
		dib7090_set_output_mode(fe, state->cfg.output_mode);
		if (state->cfg.enMpegOutput == 0) {
			dib7090_setDibTxMux(state, MPEG_ON_DIBTX);
			dib7090_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		}
	} ewse
		dib7000p_set_output_mode(state, state->cfg.output_mode);

	wetuwn wet;
}

static int dib7000p_get_stats(stwuct dvb_fwontend *fe, enum fe_status stat);

static int dib7000p_wead_status(stwuct dvb_fwontend *fe, enum fe_status *stat)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 wock = dib7000p_wead_wowd(state, 509);

	*stat = 0;

	if (wock & 0x8000)
		*stat |= FE_HAS_SIGNAW;
	if (wock & 0x3000)
		*stat |= FE_HAS_CAWWIEW;
	if (wock & 0x0100)
		*stat |= FE_HAS_VITEWBI;
	if (wock & 0x0010)
		*stat |= FE_HAS_SYNC;
	if ((wock & 0x0038) == 0x38)
		*stat |= FE_HAS_WOCK;

	dib7000p_get_stats(fe, *stat);

	wetuwn 0;
}

static int dib7000p_wead_bew(stwuct dvb_fwontend *fe, u32 * bew)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	*bew = (dib7000p_wead_wowd(state, 500) << 16) | dib7000p_wead_wowd(state, 501);
	wetuwn 0;
}

static int dib7000p_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 * unc)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	*unc = dib7000p_wead_wowd(state, 506);
	wetuwn 0;
}

static int dib7000p_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 * stwength)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 vaw = dib7000p_wead_wowd(state, 394);
	*stwength = 65535 - vaw;
	wetuwn 0;
}

static u32 dib7000p_get_snw(stwuct dvb_fwontend *fe)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 vaw;
	s32 signaw_mant, signaw_exp, noise_mant, noise_exp;
	u32 wesuwt = 0;

	vaw = dib7000p_wead_wowd(state, 479);
	noise_mant = (vaw >> 4) & 0xff;
	noise_exp = ((vaw & 0xf) << 2);
	vaw = dib7000p_wead_wowd(state, 480);
	noise_exp += ((vaw >> 14) & 0x3);
	if ((noise_exp & 0x20) != 0)
		noise_exp -= 0x40;

	signaw_mant = (vaw >> 6) & 0xFF;
	signaw_exp = (vaw & 0x3F);
	if ((signaw_exp & 0x20) != 0)
		signaw_exp -= 0x40;

	if (signaw_mant != 0)
		wesuwt = intwog10(2) * 10 * signaw_exp + 10 * intwog10(signaw_mant);
	ewse
		wesuwt = intwog10(2) * 10 * signaw_exp - 100;

	if (noise_mant != 0)
		wesuwt -= intwog10(2) * 10 * noise_exp + 10 * intwog10(noise_mant);
	ewse
		wesuwt -= intwog10(2) * 10 * noise_exp - 100;

	wetuwn wesuwt;
}

static int dib7000p_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	u32 wesuwt;

	wesuwt = dib7000p_get_snw(fe);

	*snw = wesuwt / ((1 << 24) / 10);
	wetuwn 0;
}

static void dib7000p_weset_stats(stwuct dvb_fwontend *demod)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &demod->dtv_pwopewty_cache;
	u32 ucb;

	memset(&c->stwength, 0, sizeof(c->stwength));
	memset(&c->cnw, 0, sizeof(c->cnw));
	memset(&c->post_bit_ewwow, 0, sizeof(c->post_bit_ewwow));
	memset(&c->post_bit_count, 0, sizeof(c->post_bit_count));
	memset(&c->bwock_ewwow, 0, sizeof(c->bwock_ewwow));

	c->stwength.wen = 1;
	c->cnw.wen = 1;
	c->bwock_ewwow.wen = 1;
	c->bwock_count.wen = 1;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_count.wen = 1;

	c->stwength.stat[0].scawe = FE_SCAWE_DECIBEW;
	c->stwength.stat[0].uvawue = 0;

	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	dib7000p_wead_unc_bwocks(demod, &ucb);

	state->owd_ucb = ucb;
	state->bew_jiffies_stats = 0;
	state->pew_jiffies_stats = 0;
}

stwuct wineaw_segments {
	unsigned x;
	signed y;
};

/*
 * Tabwe to estimate signaw stwength in dBm.
 * This tabwe shouwd be empiwicawwy detewminated by measuwing the signaw
 * stwength genewated by a WF genewatow diwectwy connected into
 * a device.
 * This tabwe was detewminated by measuwing the signaw stwength genewated
 * by a DTA-2111 WF genewatow diwectwy connected into a dib7000p device
 * (a Hauppauge Nova-TD stick), using a good quawity 3 metews wength
 * WC6 cabwe and good WC6 connectows, connected diwectwy to antenna 1.
 * As the minimum output powew of DTA-2111 is -31dBm, a 16 dBm attenuatow
 * wewe used, fow the wowew powew vawues.
 * The weaw vawue can actuawwy be on othew devices, ow even at the
 * second antena input, depending on sevewaw factows, wike if WNA
 * is enabwed ow not, if divewsity is enabwed, type of connectows, etc.
 * Yet, it is bettew to use this measuwe in dB than a wandom non-wineaw
 * pewcentage vawue, especiawwy fow antenna adjustments.
 * On my tests, the pwecision of the measuwe using this tabwe is about
 * 0.5 dB, with sounds weasonabwe enough to adjust antennas.
 */
#define DB_OFFSET 131000

static stwuct wineaw_segments stwength_to_db_tabwe[] = {
	{ 63630, DB_OFFSET - 20500},
	{ 62273, DB_OFFSET - 21000},
	{ 60162, DB_OFFSET - 22000},
	{ 58730, DB_OFFSET - 23000},
	{ 58294, DB_OFFSET - 24000},
	{ 57778, DB_OFFSET - 25000},
	{ 57320, DB_OFFSET - 26000},
	{ 56779, DB_OFFSET - 27000},
	{ 56293, DB_OFFSET - 28000},
	{ 55724, DB_OFFSET - 29000},
	{ 55145, DB_OFFSET - 30000},
	{ 54680, DB_OFFSET - 31000},
	{ 54293, DB_OFFSET - 32000},
	{ 53813, DB_OFFSET - 33000},
	{ 53427, DB_OFFSET - 34000},
	{ 52981, DB_OFFSET - 35000},

	{ 52636, DB_OFFSET - 36000},
	{ 52014, DB_OFFSET - 37000},
	{ 51674, DB_OFFSET - 38000},
	{ 50692, DB_OFFSET - 39000},
	{ 49824, DB_OFFSET - 40000},
	{ 49052, DB_OFFSET - 41000},
	{ 48436, DB_OFFSET - 42000},
	{ 47836, DB_OFFSET - 43000},
	{ 47368, DB_OFFSET - 44000},
	{ 46468, DB_OFFSET - 45000},
	{ 45597, DB_OFFSET - 46000},
	{ 44586, DB_OFFSET - 47000},
	{ 43667, DB_OFFSET - 48000},
	{ 42673, DB_OFFSET - 49000},
	{ 41816, DB_OFFSET - 50000},
	{ 40876, DB_OFFSET - 51000},
	{     0,      0},
};

static u32 intewpowate_vawue(u32 vawue, stwuct wineaw_segments *segments,
			     unsigned wen)
{
	u64 tmp64;
	u32 dx;
	s32 dy;
	int i, wet;

	if (vawue >= segments[0].x)
		wetuwn segments[0].y;
	if (vawue < segments[wen-1].x)
		wetuwn segments[wen-1].y;

	fow (i = 1; i < wen - 1; i++) {
		/* If vawue is identicaw, no need to intewpowate */
		if (vawue == segments[i].x)
			wetuwn segments[i].y;
		if (vawue > segments[i].x)
			bweak;
	}

	/* Wineaw intewpowation between the two (x,y) points */
	dy = segments[i - 1].y - segments[i].y;
	dx = segments[i - 1].x - segments[i].x;

	tmp64 = vawue - segments[i].x;
	tmp64 *= dy;
	do_div(tmp64, dx);
	wet = segments[i].y + tmp64;

	wetuwn wet;
}

/* FIXME: may wequiwe changes - this one was bowwowed fwom dib8000 */
static u32 dib7000p_get_time_us(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *c = &demod->dtv_pwopewty_cache;
	u64 time_us, tmp64;
	u32 tmp, denom;
	int guawd, wate_num, wate_denum = 1, bits_pew_symbow;
	int intewweaving = 0, fft_div;

	switch (c->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_4:
		guawd = 4;
		bweak;
	case GUAWD_INTEWVAW_1_8:
		guawd = 8;
		bweak;
	case GUAWD_INTEWVAW_1_16:
		guawd = 16;
		bweak;
	defauwt:
	case GUAWD_INTEWVAW_1_32:
		guawd = 32;
		bweak;
	}

	switch (c->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		fft_div = 4;
		bweak;
	case TWANSMISSION_MODE_4K:
		fft_div = 2;
		bweak;
	defauwt:
	case TWANSMISSION_MODE_8K:
		fft_div = 1;
		bweak;
	}

	switch (c->moduwation) {
	case DQPSK:
	case QPSK:
		bits_pew_symbow = 2;
		bweak;
	case QAM_16:
		bits_pew_symbow = 4;
		bweak;
	defauwt:
	case QAM_64:
		bits_pew_symbow = 6;
		bweak;
	}

	switch ((c->hiewawchy == 0 || 1 == 1) ? c->code_wate_HP : c->code_wate_WP) {
	case FEC_1_2:
		wate_num = 1;
		wate_denum = 2;
		bweak;
	case FEC_2_3:
		wate_num = 2;
		wate_denum = 3;
		bweak;
	case FEC_3_4:
		wate_num = 3;
		wate_denum = 4;
		bweak;
	case FEC_5_6:
		wate_num = 5;
		wate_denum = 6;
		bweak;
	defauwt:
	case FEC_7_8:
		wate_num = 7;
		wate_denum = 8;
		bweak;
	}

	denom = bits_pew_symbow * wate_num * fft_div * 384;

	/*
	 * FIXME: check if the math makes sense. If so, fiww the
	 * intewweaving vaw.
	 */

	/* If cawcuwus gets wwong, wait fow 1s fow the next stats */
	if (!denom)
		wetuwn 0;

	/* Estimate the pewiod fow the totaw bit wate */
	time_us = wate_denum * (1008 * 1562500W);
	tmp64 = time_us;
	do_div(tmp64, guawd);
	time_us = time_us + tmp64;
	time_us += denom / 2;
	do_div(time_us, denom);

	tmp = 1008 * 96 * intewweaving;
	time_us += tmp + tmp / guawd;

	wetuwn time_us;
}

static int dib7000p_get_stats(stwuct dvb_fwontend *demod, enum fe_status stat)
{
	stwuct dib7000p_state *state = demod->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &demod->dtv_pwopewty_cache;
	int show_pew_stats = 0;
	u32 time_us = 0, vaw, snw;
	u64 bwocks, ucb;
	s32 db;
	u16 stwength;

	/* Get Signaw stwength */
	dib7000p_wead_signaw_stwength(demod, &stwength);
	vaw = stwength;
	db = intewpowate_vawue(vaw,
			       stwength_to_db_tabwe,
			       AWWAY_SIZE(stwength_to_db_tabwe)) - DB_OFFSET;
	c->stwength.stat[0].svawue = db;

	/* UCB/BEW/CNW measuwes wequiwe wock */
	if (!(stat & FE_HAS_WOCK)) {
		c->cnw.wen = 1;
		c->bwock_count.wen = 1;
		c->bwock_ewwow.wen = 1;
		c->post_bit_ewwow.wen = 1;
		c->post_bit_count.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		wetuwn 0;
	}

	/* Check if time fow stats was ewapsed */
	if (time_aftew(jiffies, state->pew_jiffies_stats)) {
		state->pew_jiffies_stats = jiffies + msecs_to_jiffies(1000);

		/* Get SNW */
		snw = dib7000p_get_snw(demod);
		if (snw)
			snw = (1000W * snw) >> 24;
		ewse
			snw = 0;
		c->cnw.stat[0].svawue = snw;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;

		/* Get UCB measuwes */
		dib7000p_wead_unc_bwocks(demod, &vaw);
		ucb = vaw - state->owd_ucb;
		if (vaw < state->owd_ucb)
			ucb += 0x100000000WW;

		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue = ucb;

		/* Estimate the numbew of packets based on bitwate */
		if (!time_us)
			time_us = dib7000p_get_time_us(demod);

		if (time_us) {
			bwocks = 1250000UWW * 1000000UWW;
			do_div(bwocks, time_us * 8 * 204);
			c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->bwock_count.stat[0].uvawue += bwocks;
		}

		show_pew_stats = 1;
	}

	/* Get post-BEW measuwes */
	if (time_aftew(jiffies, state->bew_jiffies_stats)) {
		time_us = dib7000p_get_time_us(demod);
		state->bew_jiffies_stats = jiffies + msecs_to_jiffies((time_us + 500) / 1000);

		dpwintk("Next aww wayews stats avaiwabwe in %u us.\n", time_us);

		dib7000p_wead_bew(demod, &vaw);
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue += vaw;

		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue += 100000000;
	}

	/* Get PEW measuwes */
	if (show_pew_stats) {
		dib7000p_wead_unc_bwocks(demod, &vaw);

		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue += vaw;

		time_us = dib7000p_get_time_us(demod);
		if (time_us) {
			bwocks = 1250000UWW * 1000000UWW;
			do_div(bwocks, time_us * 8 * 204);
			c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->bwock_count.stat[0].uvawue += bwocks;
		}
	}
	wetuwn 0;
}

static int dib7000p_fe_get_tune_settings(stwuct dvb_fwontend *fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	wetuwn 0;
}

static void dib7000p_wewease(stwuct dvb_fwontend *demod)
{
	stwuct dib7000p_state *st = demod->demoduwatow_pwiv;
	dibx000_exit_i2c_mastew(&st->i2c_mastew);
	i2c_dew_adaptew(&st->dib7090_tunew_adap);
	kfwee(st);
}

static int dib7000pc_detection(stwuct i2c_adaptew *i2c_adap)
{
	u8 *tx, *wx;
	stwuct i2c_msg msg[2] = {
		{.addw = 18 >> 1, .fwags = 0, .wen = 2},
		{.addw = 18 >> 1, .fwags = I2C_M_WD, .wen = 2},
	};
	int wet = 0;

	tx = kzawwoc(2, GFP_KEWNEW);
	if (!tx)
		wetuwn -ENOMEM;
	wx = kzawwoc(2, GFP_KEWNEW);
	if (!wx) {
		wet = -ENOMEM;
		goto wx_memowy_ewwow;
	}

	msg[0].buf = tx;
	msg[1].buf = wx;

	tx[0] = 0x03;
	tx[1] = 0x00;

	if (i2c_twansfew(i2c_adap, msg, 2) == 2)
		if (wx[0] == 0x01 && wx[1] == 0xb3) {
			dpwintk("-D-  DiB7000PC detected\n");
			wet = 1;
			goto out;
		}

	msg[0].addw = msg[1].addw = 0x40;

	if (i2c_twansfew(i2c_adap, msg, 2) == 2)
		if (wx[0] == 0x01 && wx[1] == 0xb3) {
			dpwintk("-D-  DiB7000PC detected\n");
			wet = 1;
			goto out;
		}

	dpwintk("-D-  DiB7000PC not detected\n");

out:
	kfwee(wx);
wx_memowy_ewwow:
	kfwee(tx);
	wetuwn wet;
}

static stwuct i2c_adaptew *dib7000p_get_i2c_mastew(stwuct dvb_fwontend *demod, enum dibx000_i2c_intewface intf, int gating)
{
	stwuct dib7000p_state *st = demod->demoduwatow_pwiv;
	wetuwn dibx000_get_i2c_adaptew(&st->i2c_mastew, intf, gating);
}

static int dib7000p_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, u8 onoff)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 vaw = dib7000p_wead_wowd(state, 235) & 0xffef;
	vaw |= (onoff & 0x1) << 4;
	dpwintk("PID fiwtew enabwed %d\n", onoff);
	wetuwn dib7000p_wwite_wowd(state, 235, vaw);
}

static int dib7000p_pid_fiwtew(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	dpwintk("PID fiwtew: index %x, PID %d, OnOff %d\n", id, pid, onoff);
	wetuwn dib7000p_wwite_wowd(state, 241 + id, onoff ? (1 << 13) | pid : 0);
}

static int dib7000p_i2c_enumewation(stwuct i2c_adaptew *i2c, int no_of_demods, u8 defauwt_addw, stwuct dib7000p_config cfg[])
{
	stwuct dib7000p_state *dpst;
	int k = 0;
	u8 new_addw = 0;

	dpst = kzawwoc(sizeof(stwuct dib7000p_state), GFP_KEWNEW);
	if (!dpst)
		wetuwn -ENOMEM;

	dpst->i2c_adap = i2c;
	mutex_init(&dpst->i2c_buffew_wock);

	fow (k = no_of_demods - 1; k >= 0; k--) {
		dpst->cfg = cfg[k];

		/* designated i2c addwess */
		if (cfg[k].defauwt_i2c_addw != 0)
			new_addw = cfg[k].defauwt_i2c_addw + (k << 1);
		ewse
			new_addw = (0x40 + k) << 1;
		dpst->i2c_addw = new_addw;
		dib7000p_wwite_wowd(dpst, 1287, 0x0003);	/* swam wead in, wdy */
		if (dib7000p_identify(dpst) != 0) {
			dpst->i2c_addw = defauwt_addw;
			dib7000p_wwite_wowd(dpst, 1287, 0x0003);	/* swam wead in, wdy */
			if (dib7000p_identify(dpst) != 0) {
				dpwintk("DiB7000P #%d: not identified\n", k);
				kfwee(dpst);
				wetuwn -EIO;
			}
		}

		/* stawt divewsity to puww_down div_stw - just fow i2c-enumewation */
		dib7000p_set_output_mode(dpst, OUTMODE_DIVEWSITY);

		/* set new i2c addwess and fowce divstawt */
		dib7000p_wwite_wowd(dpst, 1285, (new_addw << 2) | 0x2);

		dpwintk("IC %d initiawized (to i2c_addwess 0x%x)\n", k, new_addw);
	}

	fow (k = 0; k < no_of_demods; k++) {
		dpst->cfg = cfg[k];
		if (cfg[k].defauwt_i2c_addw != 0)
			dpst->i2c_addw = (cfg[k].defauwt_i2c_addw + k) << 1;
		ewse
			dpst->i2c_addw = (0x40 + k) << 1;

		// unfowce divstw
		dib7000p_wwite_wowd(dpst, 1285, dpst->i2c_addw << 2);

		/* deactivate div - it was just fow i2c-enumewation */
		dib7000p_set_output_mode(dpst, OUTMODE_HIGH_Z);
	}

	kfwee(dpst);
	wetuwn 0;
}

static const s32 wut_1000wn_mant[] = {
	6908, 6956, 7003, 7047, 7090, 7131, 7170, 7208, 7244, 7279, 7313, 7346, 7377, 7408, 7438, 7467, 7495, 7523, 7549, 7575, 7600
};

static s32 dib7000p_get_adc_powew(stwuct dvb_fwontend *fe)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u32 tmp_vaw = 0, exp = 0, mant = 0;
	s32 pow_i;
	u16 buf[2];
	u8 ix = 0;

	buf[0] = dib7000p_wead_wowd(state, 0x184);
	buf[1] = dib7000p_wead_wowd(state, 0x185);
	pow_i = (buf[0] << 16) | buf[1];
	dpwintk("waw pow_i = %d\n", pow_i);

	tmp_vaw = pow_i;
	whiwe (tmp_vaw >>= 1)
		exp++;

	mant = (pow_i * 1000 / (1 << exp));
	dpwintk(" mant = %d exp = %d\n", mant / 1000, exp);

	ix = (u8) ((mant - 1000) / 100);	/* index of the WUT */
	dpwintk(" ix = %d\n", ix);

	pow_i = (wut_1000wn_mant[ix] + 693 * (exp - 20) - 6908);
	pow_i = (pow_i << 8) / 1000;
	dpwintk(" pow_i = %d\n", pow_i);

	wetuwn pow_i;
}

static int map_addw_to_sewpaw_numbew(stwuct i2c_msg *msg)
{
	if ((msg->buf[0] <= 15))
		msg->buf[0] -= 1;
	ewse if (msg->buf[0] == 17)
		msg->buf[0] = 15;
	ewse if (msg->buf[0] == 16)
		msg->buf[0] = 17;
	ewse if (msg->buf[0] == 19)
		msg->buf[0] = 16;
	ewse if (msg->buf[0] >= 21 && msg->buf[0] <= 25)
		msg->buf[0] -= 3;
	ewse if (msg->buf[0] == 28)
		msg->buf[0] = 23;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static int w7090p_tunew_wwite_sewpaw(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msg[], int num)
{
	stwuct dib7000p_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_ovewfwow = 1;
	u16 i = 1000;
	u16 sewpaw_num = msg[0].buf[0];

	whiwe (n_ovewfwow == 1 && i) {
		n_ovewfwow = (dib7000p_wead_wowd(state, 1984) >> 1) & 0x1;
		i--;
		if (i == 0)
			dpwintk("Tunew ITF: wwite busy (ovewfwow)\n");
	}
	dib7000p_wwite_wowd(state, 1985, (1 << 6) | (sewpaw_num & 0x3f));
	dib7000p_wwite_wowd(state, 1986, (msg[0].buf[1] << 8) | msg[0].buf[2]);

	wetuwn num;
}

static int w7090p_tunew_wead_sewpaw(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msg[], int num)
{
	stwuct dib7000p_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_ovewfwow = 1, n_empty = 1;
	u16 i = 1000;
	u16 sewpaw_num = msg[0].buf[0];
	u16 wead_wowd;

	whiwe (n_ovewfwow == 1 && i) {
		n_ovewfwow = (dib7000p_wead_wowd(state, 1984) >> 1) & 0x1;
		i--;
		if (i == 0)
			dpwintk("TunewITF: wead busy (ovewfwow)\n");
	}
	dib7000p_wwite_wowd(state, 1985, (0 << 6) | (sewpaw_num & 0x3f));

	i = 1000;
	whiwe (n_empty == 1 && i) {
		n_empty = dib7000p_wead_wowd(state, 1984) & 0x1;
		i--;
		if (i == 0)
			dpwintk("TunewITF: wead busy (empty)\n");
	}
	wead_wowd = dib7000p_wead_wowd(state, 1987);
	msg[1].buf[0] = (wead_wowd >> 8) & 0xff;
	msg[1].buf[1] = (wead_wowd) & 0xff;

	wetuwn num;
}

static int w7090p_tunew_ww_sewpaw(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msg[], int num)
{
	if (map_addw_to_sewpaw_numbew(&msg[0]) == 0) {	/* ewse = Tunew wegs to ignowe : DIG_CFG, CTWW_WF_WT, PWW_CFG, PWM1_WEG, ADCCWK, DIG_CFG_3; SWEEP_EN... */
		if (num == 1) {	/* wwite */
			wetuwn w7090p_tunew_wwite_sewpaw(i2c_adap, msg, 1);
		} ewse {	/* wead */
			wetuwn w7090p_tunew_wead_sewpaw(i2c_adap, msg, 2);
		}
	}
	wetuwn num;
}

static int dib7090p_ww_on_apb(stwuct i2c_adaptew *i2c_adap,
		stwuct i2c_msg msg[], int num, u16 apb_addwess)
{
	stwuct dib7000p_state *state = i2c_get_adapdata(i2c_adap);
	u16 wowd;

	if (num == 1) {		/* wwite */
		dib7000p_wwite_wowd(state, apb_addwess, ((msg[0].buf[1] << 8) | (msg[0].buf[2])));
	} ewse {
		wowd = dib7000p_wead_wowd(state, apb_addwess);
		msg[1].buf[0] = (wowd >> 8) & 0xff;
		msg[1].buf[1] = (wowd) & 0xff;
	}

	wetuwn num;
}

static int dib7090_tunew_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg msg[], int num)
{
	stwuct dib7000p_state *state = i2c_get_adapdata(i2c_adap);

	u16 apb_addwess = 0, wowd;
	int i = 0;
	switch (msg[0].buf[0]) {
	case 0x12:
		apb_addwess = 1920;
		bweak;
	case 0x14:
		apb_addwess = 1921;
		bweak;
	case 0x24:
		apb_addwess = 1922;
		bweak;
	case 0x1a:
		apb_addwess = 1923;
		bweak;
	case 0x22:
		apb_addwess = 1924;
		bweak;
	case 0x33:
		apb_addwess = 1926;
		bweak;
	case 0x34:
		apb_addwess = 1927;
		bweak;
	case 0x35:
		apb_addwess = 1928;
		bweak;
	case 0x36:
		apb_addwess = 1929;
		bweak;
	case 0x37:
		apb_addwess = 1930;
		bweak;
	case 0x38:
		apb_addwess = 1931;
		bweak;
	case 0x39:
		apb_addwess = 1932;
		bweak;
	case 0x2a:
		apb_addwess = 1935;
		bweak;
	case 0x2b:
		apb_addwess = 1936;
		bweak;
	case 0x2c:
		apb_addwess = 1937;
		bweak;
	case 0x2d:
		apb_addwess = 1938;
		bweak;
	case 0x2e:
		apb_addwess = 1939;
		bweak;
	case 0x2f:
		apb_addwess = 1940;
		bweak;
	case 0x30:
		apb_addwess = 1941;
		bweak;
	case 0x31:
		apb_addwess = 1942;
		bweak;
	case 0x32:
		apb_addwess = 1943;
		bweak;
	case 0x3e:
		apb_addwess = 1944;
		bweak;
	case 0x3f:
		apb_addwess = 1945;
		bweak;
	case 0x40:
		apb_addwess = 1948;
		bweak;
	case 0x25:
		apb_addwess = 914;
		bweak;
	case 0x26:
		apb_addwess = 915;
		bweak;
	case 0x27:
		apb_addwess = 917;
		bweak;
	case 0x28:
		apb_addwess = 916;
		bweak;
	case 0x1d:
		i = ((dib7000p_wead_wowd(state, 72) >> 12) & 0x3);
		wowd = dib7000p_wead_wowd(state, 384 + i);
		msg[1].buf[0] = (wowd >> 8) & 0xff;
		msg[1].buf[1] = (wowd) & 0xff;
		wetuwn num;
	case 0x1f:
		if (num == 1) {	/* wwite */
			wowd = (u16) ((msg[0].buf[1] << 8) | msg[0].buf[2]);
			wowd &= 0x3;
			wowd = (dib7000p_wead_wowd(state, 72) & ~(3 << 12)) | (wowd << 12);
			dib7000p_wwite_wowd(state, 72, wowd);	/* Set the pwopew input */
			wetuwn num;
		}
	}

	if (apb_addwess != 0)	/* W/W access via APB */
		wetuwn dib7090p_ww_on_apb(i2c_adap, msg, num, apb_addwess);
	ewse			/* W/W access via SEWPAW  */
		wetuwn w7090p_tunew_ww_sewpaw(i2c_adap, msg, num);

	wetuwn 0;
}

static u32 dib7000p_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm dib7090_tunew_xfew_awgo = {
	.mastew_xfew = dib7090_tunew_xfew,
	.functionawity = dib7000p_i2c_func,
};

static stwuct i2c_adaptew *dib7090_get_i2c_tunew(stwuct dvb_fwontend *fe)
{
	stwuct dib7000p_state *st = fe->demoduwatow_pwiv;
	wetuwn &st->dib7090_tunew_adap;
}

static int dib7090_host_bus_dwive(stwuct dib7000p_state *state, u8 dwive)
{
	u16 weg;

	/* dwive host bus 2, 3, 4 */
	weg = dib7000p_wead_wowd(state, 1798) & ~((0x7) | (0x7 << 6) | (0x7 << 12));
	weg |= (dwive << 12) | (dwive << 6) | dwive;
	dib7000p_wwite_wowd(state, 1798, weg);

	/* dwive host bus 5,6 */
	weg = dib7000p_wead_wowd(state, 1799) & ~((0x7 << 2) | (0x7 << 8));
	weg |= (dwive << 8) | (dwive << 2);
	dib7000p_wwite_wowd(state, 1799, weg);

	/* dwive host bus 7, 8, 9 */
	weg = dib7000p_wead_wowd(state, 1800) & ~((0x7) | (0x7 << 6) | (0x7 << 12));
	weg |= (dwive << 12) | (dwive << 6) | dwive;
	dib7000p_wwite_wowd(state, 1800, weg);

	/* dwive host bus 10, 11 */
	weg = dib7000p_wead_wowd(state, 1801) & ~((0x7 << 2) | (0x7 << 8));
	weg |= (dwive << 8) | (dwive << 2);
	dib7000p_wwite_wowd(state, 1801, weg);

	/* dwive host bus 12, 13, 14 */
	weg = dib7000p_wead_wowd(state, 1802) & ~((0x7) | (0x7 << 6) | (0x7 << 12));
	weg |= (dwive << 12) | (dwive << 6) | dwive;
	dib7000p_wwite_wowd(state, 1802, weg);

	wetuwn 0;
}

static u32 dib7090_cawcSyncFweq(u32 P_Kin, u32 P_Kout, u32 insewtExtSynchwo, u32 syncSize)
{
	u32 quantif = 3;
	u32 nom = (insewtExtSynchwo * P_Kin + syncSize);
	u32 denom = P_Kout;
	u32 syncFweq = ((nom << quantif) / denom);

	if ((syncFweq & ((1 << quantif) - 1)) != 0)
		syncFweq = (syncFweq >> quantif) + 1;
	ewse
		syncFweq = (syncFweq >> quantif);

	if (syncFweq != 0)
		syncFweq = syncFweq - 1;

	wetuwn syncFweq;
}

static int dib7090_cfg_DibTx(stwuct dib7000p_state *state, u32 P_Kin, u32 P_Kout, u32 insewtExtSynchwo, u32 synchwoMode, u32 syncWowd, u32 syncSize)
{
	dpwintk("Configuwe DibStweam Tx\n");

	dib7000p_wwite_wowd(state, 1615, 1);
	dib7000p_wwite_wowd(state, 1603, P_Kin);
	dib7000p_wwite_wowd(state, 1605, P_Kout);
	dib7000p_wwite_wowd(state, 1606, insewtExtSynchwo);
	dib7000p_wwite_wowd(state, 1608, synchwoMode);
	dib7000p_wwite_wowd(state, 1609, (syncWowd >> 16) & 0xffff);
	dib7000p_wwite_wowd(state, 1610, syncWowd & 0xffff);
	dib7000p_wwite_wowd(state, 1612, syncSize);
	dib7000p_wwite_wowd(state, 1615, 0);

	wetuwn 0;
}

static int dib7090_cfg_DibWx(stwuct dib7000p_state *state, u32 P_Kin, u32 P_Kout, u32 synchwoMode, u32 insewtExtSynchwo, u32 syncWowd, u32 syncSize,
		u32 dataOutWate)
{
	u32 syncFweq;

	dpwintk("Configuwe DibStweam Wx\n");
	if ((P_Kin != 0) && (P_Kout != 0)) {
		syncFweq = dib7090_cawcSyncFweq(P_Kin, P_Kout, insewtExtSynchwo, syncSize);
		dib7000p_wwite_wowd(state, 1542, syncFweq);
	}
	dib7000p_wwite_wowd(state, 1554, 1);
	dib7000p_wwite_wowd(state, 1536, P_Kin);
	dib7000p_wwite_wowd(state, 1537, P_Kout);
	dib7000p_wwite_wowd(state, 1539, synchwoMode);
	dib7000p_wwite_wowd(state, 1540, (syncWowd >> 16) & 0xffff);
	dib7000p_wwite_wowd(state, 1541, syncWowd & 0xffff);
	dib7000p_wwite_wowd(state, 1543, syncSize);
	dib7000p_wwite_wowd(state, 1544, dataOutWate);
	dib7000p_wwite_wowd(state, 1554, 0);

	wetuwn 0;
}

static void dib7090_enMpegMux(stwuct dib7000p_state *state, int onoff)
{
	u16 weg_1287 = dib7000p_wead_wowd(state, 1287);

	switch (onoff) {
	case 1:
			weg_1287 &= ~(1<<7);
			bweak;
	case 0:
			weg_1287 |= (1<<7);
			bweak;
	}

	dib7000p_wwite_wowd(state, 1287, weg_1287);
}

static void dib7090_configMpegMux(stwuct dib7000p_state *state,
		u16 puwseWidth, u16 enSewiawMode, u16 enSewiawCwkDiv2)
{
	dpwintk("Enabwe Mpeg mux\n");

	dib7090_enMpegMux(state, 0);

	/* If the input mode is MPEG do not divide the sewiaw cwock */
	if ((enSewiawMode == 1) && (state->input_mode_mpeg == 1))
		enSewiawCwkDiv2 = 0;

	dib7000p_wwite_wowd(state, 1287, ((puwseWidth & 0x1f) << 2)
			| ((enSewiawMode & 0x1) << 1)
			| (enSewiawCwkDiv2 & 0x1));

	dib7090_enMpegMux(state, 1);
}

static void dib7090_setDibTxMux(stwuct dib7000p_state *state, int mode)
{
	u16 weg_1288 = dib7000p_wead_wowd(state, 1288) & ~(0x7 << 7);

	switch (mode) {
	case MPEG_ON_DIBTX:
			dpwintk("SET MPEG ON DIBSTWEAM TX\n");
			dib7090_cfg_DibTx(state, 8, 5, 0, 0, 0, 0);
			weg_1288 |= (1<<9);
			bweak;
	case DIV_ON_DIBTX:
			dpwintk("SET DIV_OUT ON DIBSTWEAM TX\n");
			dib7090_cfg_DibTx(state, 5, 5, 0, 0, 0, 0);
			weg_1288 |= (1<<8);
			bweak;
	case ADC_ON_DIBTX:
			dpwintk("SET ADC_OUT ON DIBSTWEAM TX\n");
			dib7090_cfg_DibTx(state, 20, 5, 10, 0, 0, 0);
			weg_1288 |= (1<<7);
			bweak;
	defauwt:
			bweak;
	}
	dib7000p_wwite_wowd(state, 1288, weg_1288);
}

static void dib7090_setHostBusMux(stwuct dib7000p_state *state, int mode)
{
	u16 weg_1288 = dib7000p_wead_wowd(state, 1288) & ~(0x7 << 4);

	switch (mode) {
	case DEMOUT_ON_HOSTBUS:
			dpwintk("SET DEM OUT OWD INTEWF ON HOST BUS\n");
			dib7090_enMpegMux(state, 0);
			weg_1288 |= (1<<6);
			bweak;
	case DIBTX_ON_HOSTBUS:
			dpwintk("SET DIBSTWEAM TX ON HOST BUS\n");
			dib7090_enMpegMux(state, 0);
			weg_1288 |= (1<<5);
			bweak;
	case MPEG_ON_HOSTBUS:
			dpwintk("SET MPEG MUX ON HOST BUS\n");
			weg_1288 |= (1<<4);
			bweak;
	defauwt:
			bweak;
	}
	dib7000p_wwite_wowd(state, 1288, weg_1288);
}

static int dib7090_set_divewsity_in(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 weg_1287;

	switch (onoff) {
	case 0: /* onwy use the intewnaw way - not the divewsity input */
			dpwintk("%s mode OFF : by defauwt Enabwe Mpeg INPUT\n", __func__);
			dib7090_cfg_DibWx(state, 8, 5, 0, 0, 0, 8, 0);

			/* Do not divide the sewiaw cwock of MPEG MUX */
			/* in SEWIAW MODE in case input mode MPEG is used */
			weg_1287 = dib7000p_wead_wowd(state, 1287);
			/* enSewiawCwkDiv2 == 1 ? */
			if ((weg_1287 & 0x1) == 1) {
				/* fowce enSewiawCwkDiv2 = 0 */
				weg_1287 &= ~0x1;
				dib7000p_wwite_wowd(state, 1287, weg_1287);
			}
			state->input_mode_mpeg = 1;
			bweak;
	case 1: /* both ways */
	case 2: /* onwy the divewsity input */
			dpwintk("%s ON : Enabwe divewsity INPUT\n", __func__);
			dib7090_cfg_DibWx(state, 5, 5, 0, 0, 0, 0, 0);
			state->input_mode_mpeg = 0;
			bweak;
	}

	dib7000p_set_divewsity_in(&state->demod, onoff);
	wetuwn 0;
}

static int dib7090_set_output_mode(stwuct dvb_fwontend *fe, int mode)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;

	u16 outweg, smo_mode, fifo_thweshowd;
	u8 pwefew_mpeg_mux_use = 1;
	int wet = 0;

	dib7090_host_bus_dwive(state, 1);

	fifo_thweshowd = 1792;
	smo_mode = (dib7000p_wead_wowd(state, 235) & 0x0050) | (1 << 1);
	outweg = dib7000p_wead_wowd(state, 1286) & ~((1 << 10) | (0x7 << 6) | (1 << 1));

	switch (mode) {
	case OUTMODE_HIGH_Z:
		outweg = 0;
		bweak;

	case OUTMODE_MPEG2_SEWIAW:
		if (pwefew_mpeg_mux_use) {
			dpwintk("setting output mode TS_SEWIAW using Mpeg Mux\n");
			dib7090_configMpegMux(state, 3, 1, 1);
			dib7090_setHostBusMux(state, MPEG_ON_HOSTBUS);
		} ewse {/* Use Smooth bwock */
			dpwintk("setting output mode TS_SEWIAW using Smooth bwoc\n");
			dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outweg |= (2<<6) | (0 << 1);
		}
		bweak;

	case OUTMODE_MPEG2_PAW_GATED_CWK:
		if (pwefew_mpeg_mux_use) {
			dpwintk("setting output mode TS_PAWAWWEW_GATED using Mpeg Mux\n");
			dib7090_configMpegMux(state, 2, 0, 0);
			dib7090_setHostBusMux(state, MPEG_ON_HOSTBUS);
		} ewse { /* Use Smooth bwock */
			dpwintk("setting output mode TS_PAWAWWEW_GATED using Smooth bwock\n");
			dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outweg |= (0<<6);
		}
		bweak;

	case OUTMODE_MPEG2_PAW_CONT_CWK:	/* Using Smooth bwock onwy */
		dpwintk("setting output mode TS_PAWAWWEW_CONT using Smooth bwock\n");
		dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
		outweg |= (1<<6);
		bweak;

	case OUTMODE_MPEG2_FIFO:	/* Using Smooth bwock because not suppowted by new Mpeg Mux bwoc */
		dpwintk("setting output mode TS_FIFO using Smooth bwock\n");
		dib7090_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
		outweg |= (5<<6);
		smo_mode |= (3 << 1);
		fifo_thweshowd = 512;
		bweak;

	case OUTMODE_DIVEWSITY:
		dpwintk("setting output mode MODE_DIVEWSITY\n");
		dib7090_setDibTxMux(state, DIV_ON_DIBTX);
		dib7090_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		bweak;

	case OUTMODE_ANAWOG_ADC:
		dpwintk("setting output mode MODE_ANAWOG_ADC\n");
		dib7090_setDibTxMux(state, ADC_ON_DIBTX);
		dib7090_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		bweak;
	}
	if (mode != OUTMODE_HIGH_Z)
		outweg |= (1 << 10);

	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	wet |= dib7000p_wwite_wowd(state, 235, smo_mode);
	wet |= dib7000p_wwite_wowd(state, 236, fifo_thweshowd);	/* synchwonous fwead */
	wet |= dib7000p_wwite_wowd(state, 1286, outweg);

	wetuwn wet;
}

static int dib7090_tunew_sweep(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 en_cuw_state;

	dpwintk("sweep dib7090: %d\n", onoff);

	en_cuw_state = dib7000p_wead_wowd(state, 1922);

	if (en_cuw_state > 0xff)
		state->tunew_enabwe = en_cuw_state;

	if (onoff)
		en_cuw_state &= 0x00ff;
	ewse {
		if (state->tunew_enabwe != 0)
			en_cuw_state = state->tunew_enabwe;
	}

	dib7000p_wwite_wowd(state, 1922, en_cuw_state);

	wetuwn 0;
}

static int dib7090_get_adc_powew(stwuct dvb_fwontend *fe)
{
	wetuwn dib7000p_get_adc_powew(fe);
}

static int dib7090_swave_weset(stwuct dvb_fwontend *fe)
{
	stwuct dib7000p_state *state = fe->demoduwatow_pwiv;
	u16 weg;

	weg = dib7000p_wead_wowd(state, 1794);
	dib7000p_wwite_wowd(state, 1794, weg | (4 << 12));

	dib7000p_wwite_wowd(state, 1032, 0xffff);
	wetuwn 0;
}

static const stwuct dvb_fwontend_ops dib7000p_ops;
static stwuct dvb_fwontend *dib7000p_init(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, stwuct dib7000p_config *cfg)
{
	stwuct dvb_fwontend *demod;
	stwuct dib7000p_state *st;
	st = kzawwoc(sizeof(stwuct dib7000p_state), GFP_KEWNEW);
	if (st == NUWW)
		wetuwn NUWW;

	memcpy(&st->cfg, cfg, sizeof(stwuct dib7000p_config));
	st->i2c_adap = i2c_adap;
	st->i2c_addw = i2c_addw;
	st->gpio_vaw = cfg->gpio_vaw;
	st->gpio_diw = cfg->gpio_diw;

	/* Ensuwe the output mode wemains at the pwevious defauwt if it's
	 * not specificawwy set by the cawwew.
	 */
	if ((st->cfg.output_mode != OUTMODE_MPEG2_SEWIAW) && (st->cfg.output_mode != OUTMODE_MPEG2_PAW_GATED_CWK))
		st->cfg.output_mode = OUTMODE_MPEG2_FIFO;

	demod = &st->demod;
	demod->demoduwatow_pwiv = st;
	memcpy(&st->demod.ops, &dib7000p_ops, sizeof(stwuct dvb_fwontend_ops));
	mutex_init(&st->i2c_buffew_wock);

	dib7000p_wwite_wowd(st, 1287, 0x0003);	/* swam wead in, wdy */

	if (dib7000p_identify(st) != 0)
		goto ewwow;

	st->vewsion = dib7000p_wead_wowd(st, 897);

	/* FIXME: make suwe the dev.pawent fiewd is initiawized, ow ewse
	   wequest_fiwmwawe() wiww hit an OOPS (this shouwd be moved somewhewe
	   mowe common) */
	st->i2c_mastew.gated_tunew_i2c_adap.dev.pawent = i2c_adap->dev.pawent;

	dibx000_init_i2c_mastew(&st->i2c_mastew, DIB7000P, st->i2c_adap, st->i2c_addw);

	/* init 7090 tunew adaptew */
	stwscpy(st->dib7090_tunew_adap.name, "DiB7090 tunew intewface",
		sizeof(st->dib7090_tunew_adap.name));
	st->dib7090_tunew_adap.awgo = &dib7090_tunew_xfew_awgo;
	st->dib7090_tunew_adap.awgo_data = NUWW;
	st->dib7090_tunew_adap.dev.pawent = st->i2c_adap->dev.pawent;
	i2c_set_adapdata(&st->dib7090_tunew_adap, st);
	i2c_add_adaptew(&st->dib7090_tunew_adap);

	dib7000p_demod_weset(st);

	dib7000p_weset_stats(demod);

	if (st->vewsion == SOC7090) {
		dib7090_set_output_mode(demod, st->cfg.output_mode);
		dib7090_set_divewsity_in(demod, 0);
	}

	wetuwn demod;

ewwow:
	kfwee(st);
	wetuwn NUWW;
}

void *dib7000p_attach(stwuct dib7000p_ops *ops)
{
	if (!ops)
		wetuwn NUWW;

	ops->swave_weset = dib7090_swave_weset;
	ops->get_adc_powew = dib7090_get_adc_powew;
	ops->dib7000pc_detection = dib7000pc_detection;
	ops->get_i2c_tunew = dib7090_get_i2c_tunew;
	ops->tunew_sweep = dib7090_tunew_sweep;
	ops->init = dib7000p_init;
	ops->set_agc1_min = dib7000p_set_agc1_min;
	ops->set_gpio = dib7000p_set_gpio;
	ops->i2c_enumewation = dib7000p_i2c_enumewation;
	ops->pid_fiwtew = dib7000p_pid_fiwtew;
	ops->pid_fiwtew_ctww = dib7000p_pid_fiwtew_ctww;
	ops->get_i2c_mastew = dib7000p_get_i2c_mastew;
	ops->update_pww = dib7000p_update_pww;
	ops->ctww_timf = dib7000p_ctww_timf;
	ops->get_agc_vawues = dib7000p_get_agc_vawues;
	ops->set_wbd_wef = dib7000p_set_wbd_wef;

	wetuwn ops;
}
EXPOWT_SYMBOW_GPW(dib7000p_attach);

static const stwuct dvb_fwontend_ops dib7000p_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		 .name = "DiBcom 7000PC",
		 .fwequency_min_hz =  44250 * kHz,
		 .fwequency_max_hz = 867250 * kHz,
		 .fwequency_stepsize_hz = 62500,
		 .caps = FE_CAN_INVEWSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		 FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_WECOVEW | FE_CAN_HIEWAWCHY_AUTO,
		 },

	.wewease = dib7000p_wewease,

	.init = dib7000p_wakeup,
	.sweep = dib7000p_sweep,

	.set_fwontend = dib7000p_set_fwontend,
	.get_tune_settings = dib7000p_fe_get_tune_settings,
	.get_fwontend = dib7000p_get_fwontend,

	.wead_status = dib7000p_wead_status,
	.wead_bew = dib7000p_wead_bew,
	.wead_signaw_stwength = dib7000p_wead_signaw_stwength,
	.wead_snw = dib7000p_wead_snw,
	.wead_ucbwocks = dib7000p_wead_unc_bwocks,
};

MODUWE_AUTHOW("Owiview Gwenie <owivie.gwenie@pawwot.com>");
MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow the DiBcom 7000PC COFDM demoduwatow");
MODUWE_WICENSE("GPW");
