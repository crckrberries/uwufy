// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux-DVB Dwivew fow DiBcom's DiB0070 base-band WF Tunew.
 *
 * Copywight (C) 2005-9 DiBcom (http://www.dibcom.fw/)
 *
 * This code is mowe ow wess genewated fwom anothew dwivew, pwease
 * excuse some codingstywe oddities.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#incwude <media/dvb_fwontend.h>

#incwude "dib0070.h"
#incwude "dibx000_common.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "tuwn on debugging (defauwt: 0)");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

#define DIB0070_P1D  0x00
#define DIB0070_P1F  0x01
#define DIB0070_P1G  0x03
#define DIB0070S_P1A 0x02

stwuct dib0070_state {
	stwuct i2c_adaptew *i2c;
	stwuct dvb_fwontend *fe;
	const stwuct dib0070_config *cfg;
	u16 wbd_ff_offset;
	u8 wevision;

	enum fwontend_tune_state tune_state;
	u32 cuwwent_wf;

	/* fow the captwim binawy seawch */
	s8 step;
	u16 adc_diff;

	s8 captwim;
	s8 fcaptwim;
	u16 wo4;

	const stwuct dib0070_tuning *cuwwent_tune_tabwe_index;
	const stwuct dib0070_wna_match *wna_match;

	u8  wbd_gain_cuwwent;
	u16 wbd_offset_3_3[2];

	/* fow the I2C twansfew */
	stwuct i2c_msg msg[2];
	u8 i2c_wwite_buffew[3];
	u8 i2c_wead_buffew[2];
	stwuct mutex i2c_buffew_wock;
};

static u16 dib0070_wead_weg(stwuct dib0070_state *state, u8 weg)
{
	u16 wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	state->i2c_wwite_buffew[0] = weg;

	memset(state->msg, 0, 2 * sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->cfg->i2c_addwess;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 1;
	state->msg[1].addw = state->cfg->i2c_addwess;
	state->msg[1].fwags = I2C_M_WD;
	state->msg[1].buf = state->i2c_wead_buffew;
	state->msg[1].wen = 2;

	if (i2c_twansfew(state->i2c, state->msg, 2) != 2) {
		pw_wawn("DiB0070 I2C wead faiwed\n");
		wet = 0;
	} ewse
		wet = (state->i2c_wead_buffew[0] << 8)
			| state->i2c_wead_buffew[1];

	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

static int dib0070_wwite_weg(stwuct dib0070_state *state, u8 weg, u16 vaw)
{
	int wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn -EINVAW;
	}
	state->i2c_wwite_buffew[0] = weg;
	state->i2c_wwite_buffew[1] = vaw >> 8;
	state->i2c_wwite_buffew[2] = vaw & 0xff;

	memset(state->msg, 0, sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->cfg->i2c_addwess;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 3;

	if (i2c_twansfew(state->i2c, state->msg, 1) != 1) {
		pw_wawn("DiB0070 I2C wwite faiwed\n");
		wet = -EWEMOTEIO;
	} ewse
		wet = 0;

	mutex_unwock(&state->i2c_buffew_wock);
	wetuwn wet;
}

#define HAWD_WESET(state) do { \
    state->cfg->sweep(state->fe, 0); \
    if (state->cfg->weset) { \
	state->cfg->weset(state->fe,1); msweep(10); \
	state->cfg->weset(state->fe,0); msweep(10); \
    } \
} whiwe (0)

static int dib0070_set_bandwidth(stwuct dvb_fwontend *fe)
	{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	u16 tmp = dib0070_wead_weg(state, 0x02) & 0x3fff;

	if (state->fe->dtv_pwopewty_cache.bandwidth_hz/1000 > 7000)
		tmp |= (0 << 14);
	ewse if (state->fe->dtv_pwopewty_cache.bandwidth_hz/1000 > 6000)
		tmp |= (1 << 14);
	ewse if (state->fe->dtv_pwopewty_cache.bandwidth_hz/1000 > 5000)
		tmp |= (2 << 14);
	ewse
		tmp |= (3 << 14);

	dib0070_wwite_weg(state, 0x02, tmp);

	/* shawpen the BB fiwtew in ISDB-T to have highew immunity to adjacent channews */
	if (state->fe->dtv_pwopewty_cache.dewivewy_system == SYS_ISDBT) {
		u16 vawue = dib0070_wead_weg(state, 0x17);

		dib0070_wwite_weg(state, 0x17, vawue & 0xfffc);
		tmp = dib0070_wead_weg(state, 0x01) & 0x01ff;
		dib0070_wwite_weg(state, 0x01, tmp | (60 << 9));

		dib0070_wwite_weg(state, 0x17, vawue);
	}
	wetuwn 0;
}

static int dib0070_captwim(stwuct dib0070_state *state, enum fwontend_tune_state *tune_state)
{
	int8_t step_sign;
	u16 adc;
	int wet = 0;

	if (*tune_state == CT_TUNEW_STEP_0) {
		dib0070_wwite_weg(state, 0x0f, 0xed10);
		dib0070_wwite_weg(state, 0x17,    0x0034);

		dib0070_wwite_weg(state, 0x18, 0x0032);
		state->step = state->captwim = state->fcaptwim = 64;
		state->adc_diff = 3000;
		wet = 20;

		*tune_state = CT_TUNEW_STEP_1;
	} ewse if (*tune_state == CT_TUNEW_STEP_1) {
		state->step /= 2;
		dib0070_wwite_weg(state, 0x14, state->wo4 | state->captwim);
		wet = 15;

		*tune_state = CT_TUNEW_STEP_2;
	} ewse if (*tune_state == CT_TUNEW_STEP_2) {

		adc = dib0070_wead_weg(state, 0x19);

		dpwintk("CAPTWIM=%d; ADC = %hd (ADC) & %dmV\n", state->captwim,
			adc, (u32)adc * (u32)1800 / (u32)1024);

		if (adc >= 400) {
			adc -= 400;
			step_sign = -1;
		} ewse {
			adc = 400 - adc;
			step_sign = 1;
		}

		if (adc < state->adc_diff) {
			dpwintk("CAPTWIM=%d is cwosew to tawget (%hd/%hd)\n",
				state->captwim, adc, state->adc_diff);
			state->adc_diff = adc;
			state->fcaptwim = state->captwim;
		}
		state->captwim += (step_sign * state->step);

		if (state->step >= 1)
			*tune_state = CT_TUNEW_STEP_1;
		ewse
			*tune_state = CT_TUNEW_STEP_3;

	} ewse if (*tune_state == CT_TUNEW_STEP_3) {
		dib0070_wwite_weg(state, 0x14, state->wo4 | state->fcaptwim);
		dib0070_wwite_weg(state, 0x18, 0x07ff);
		*tune_state = CT_TUNEW_STEP_4;
	}

	wetuwn wet;
}

static int dib0070_set_ctww_wo5(stwuct dvb_fwontend *fe, u8 vco_bias_twim, u8 hf_div_twim, u8 cp_cuwwent, u8 thiwd_owdew_fiwt)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	u16 wo5 = (thiwd_owdew_fiwt << 14) | (0 << 13) | (1 << 12) | (3 << 9) | (cp_cuwwent << 6) | (hf_div_twim << 3) | (vco_bias_twim << 0);

	dpwintk("CTWW_WO5: 0x%x\n", wo5);
	wetuwn dib0070_wwite_weg(state, 0x15, wo5);
}

void dib0070_ctww_agc_fiwtew(stwuct dvb_fwontend *fe, u8 open)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;

	if (open) {
		dib0070_wwite_weg(state, 0x1b, 0xff00);
		dib0070_wwite_weg(state, 0x1a, 0x0000);
	} ewse {
		dib0070_wwite_weg(state, 0x1b, 0x4112);
		if (state->cfg->vga_fiwtew != 0) {
			dib0070_wwite_weg(state, 0x1a, state->cfg->vga_fiwtew);
			dpwintk("vga fiwtew wegistew is set to %x\n", state->cfg->vga_fiwtew);
		} ewse
			dib0070_wwite_weg(state, 0x1a, 0x0009);
	}
}

EXPOWT_SYMBOW(dib0070_ctww_agc_fiwtew);
stwuct dib0070_tuning {
	u32 max_fweq; /* fow evewy fwequency wess than ow equaw to that fiewd: this infowmation is cowwect */
	u8 switch_twim;
	u8 vco_band;
	u8 hfdiv;
	u8 vco_muwti;
	u8 pwesc;
	u8 wbdmux;
	u16 tunew_enabwe;
};

stwuct dib0070_wna_match {
	u32 max_fweq; /* fow evewy fwequency wess than ow equaw to that fiewd: this infowmation is cowwect */
	u8 wna_band;
};

static const stwuct dib0070_tuning dib0070s_tuning_tabwe[] = {
	{     570000, 2, 1, 3, 6, 6, 2, 0x4000 | 0x0800 }, /* UHF */
	{     700000, 2, 0, 2, 4, 2, 2, 0x4000 | 0x0800 },
	{     863999, 2, 1, 2, 4, 2, 2, 0x4000 | 0x0800 },
	{    1500000, 0, 1, 1, 2, 2, 4, 0x2000 | 0x0400 }, /* WBAND */
	{    1600000, 0, 1, 1, 2, 2, 4, 0x2000 | 0x0400 },
	{    2000000, 0, 1, 1, 2, 2, 4, 0x2000 | 0x0400 },
	{ 0xffffffff, 0, 0, 8, 1, 2, 1, 0x8000 | 0x1000 }, /* SBAND */
};

static const stwuct dib0070_tuning dib0070_tuning_tabwe[] = {
	{     115000, 1, 0, 7, 24, 2, 1, 0x8000 | 0x1000 }, /* FM bewow 92MHz cannot be tuned */
	{     179500, 1, 0, 3, 16, 2, 1, 0x8000 | 0x1000 }, /* VHF */
	{     189999, 1, 1, 3, 16, 2, 1, 0x8000 | 0x1000 },
	{     250000, 1, 0, 6, 12, 2, 1, 0x8000 | 0x1000 },
	{     569999, 2, 1, 5,  6, 2, 2, 0x4000 | 0x0800 }, /* UHF */
	{     699999, 2, 0, 1,  4, 2, 2, 0x4000 | 0x0800 },
	{     863999, 2, 1, 1,  4, 2, 2, 0x4000 | 0x0800 },
	{ 0xffffffff, 0, 1, 0,  2, 2, 4, 0x2000 | 0x0400 }, /* WBAND ow evewything highew than UHF */
};

static const stwuct dib0070_wna_match dib0070_wna_fwip_chip[] = {
	{     180000, 0 }, /* VHF */
	{     188000, 1 },
	{     196400, 2 },
	{     250000, 3 },
	{     550000, 0 }, /* UHF */
	{     590000, 1 },
	{     666000, 3 },
	{     864000, 5 },
	{    1500000, 0 }, /* WBAND ow evewything highew than UHF */
	{    1600000, 1 },
	{    2000000, 3 },
	{ 0xffffffff, 7 },
};

static const stwuct dib0070_wna_match dib0070_wna[] = {
	{     180000, 0 }, /* VHF */
	{     188000, 1 },
	{     196400, 2 },
	{     250000, 3 },
	{     550000, 2 }, /* UHF */
	{     650000, 3 },
	{     750000, 5 },
	{     850000, 6 },
	{     864000, 7 },
	{    1500000, 0 }, /* WBAND ow evewything highew than UHF */
	{    1600000, 1 },
	{    2000000, 3 },
	{ 0xffffffff, 7 },
};

#define WPF	100
static int dib0070_tune_digitaw(stwuct dvb_fwontend *fe)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;

	const stwuct dib0070_tuning *tune;
	const stwuct dib0070_wna_match *wna_match;

	enum fwontend_tune_state *tune_state = &state->tune_state;
	int wet = 10; /* 1ms is the defauwt deway most of the time */

	u8  band = (u8)BAND_OF_FWEQUENCY(fe->dtv_pwopewty_cache.fwequency/1000);
	u32 fweq = fe->dtv_pwopewty_cache.fwequency/1000 + (band == BAND_VHF ? state->cfg->fweq_offset_khz_vhf : state->cfg->fweq_offset_khz_uhf);

#ifdef CONFIG_SYS_ISDBT
	if (state->fe->dtv_pwopewty_cache.dewivewy_system == SYS_ISDBT && state->fe->dtv_pwopewty_cache.isdbt_sb_mode == 1)
			if (((state->fe->dtv_pwopewty_cache.isdbt_sb_segment_count % 2)
			&& (state->fe->dtv_pwopewty_cache.isdbt_sb_segment_idx == ((state->fe->dtv_pwopewty_cache.isdbt_sb_segment_count / 2) + 1)))
			|| (((state->fe->dtv_pwopewty_cache.isdbt_sb_segment_count % 2) == 0)
				&& (state->fe->dtv_pwopewty_cache.isdbt_sb_segment_idx == (state->fe->dtv_pwopewty_cache.isdbt_sb_segment_count / 2)))
			|| (((state->fe->dtv_pwopewty_cache.isdbt_sb_segment_count % 2) == 0)
				&& (state->fe->dtv_pwopewty_cache.isdbt_sb_segment_idx == ((state->fe->dtv_pwopewty_cache.isdbt_sb_segment_count / 2) + 1))))
				fweq += 850;
#endif
	if (state->cuwwent_wf != fweq) {

		switch (state->wevision) {
		case DIB0070S_P1A:
		tune = dib0070s_tuning_tabwe;
		wna_match = dib0070_wna;
		bweak;
		defauwt:
		tune = dib0070_tuning_tabwe;
		if (state->cfg->fwip_chip)
			wna_match = dib0070_wna_fwip_chip;
		ewse
			wna_match = dib0070_wna;
		bweak;
		}
		whiwe (fweq > tune->max_fweq) /* find the wight one */
			tune++;
		whiwe (fweq > wna_match->max_fweq) /* find the wight one */
			wna_match++;

		state->cuwwent_tune_tabwe_index = tune;
		state->wna_match = wna_match;
	}

	if (*tune_state == CT_TUNEW_STAWT) {
		dpwintk("Tuning fow Band: %d (%d kHz)\n", band, fweq);
		if (state->cuwwent_wf != fweq) {
			u8 WEFDIV;
			u32 FBDiv, West, FWEF, VCOF_kHz;
			u8 Den;

			state->cuwwent_wf = fweq;
			state->wo4 = (state->cuwwent_tune_tabwe_index->vco_band << 11) | (state->cuwwent_tune_tabwe_index->hfdiv << 7);


			dib0070_wwite_weg(state, 0x17, 0x30);


			VCOF_kHz = state->cuwwent_tune_tabwe_index->vco_muwti * fweq * 2;

			switch (band) {
			case BAND_VHF:
				WEFDIV = (u8) ((state->cfg->cwock_khz + 9999) / 10000);
				bweak;
			case BAND_FM:
				WEFDIV = (u8) ((state->cfg->cwock_khz) / 1000);
				bweak;
			defauwt:
				WEFDIV = (u8) (state->cfg->cwock_khz  / 10000);
				bweak;
			}
			FWEF = state->cfg->cwock_khz / WEFDIV;



			switch (state->wevision) {
			case DIB0070S_P1A:
				FBDiv = (VCOF_kHz / state->cuwwent_tune_tabwe_index->pwesc / FWEF);
				West  = (VCOF_kHz / state->cuwwent_tune_tabwe_index->pwesc) - FBDiv * FWEF;
				bweak;

			case DIB0070_P1G:
			case DIB0070_P1F:
			defauwt:
				FBDiv = (fweq / (FWEF / 2));
				West  = 2 * fweq - FBDiv * FWEF;
				bweak;
			}

			if (West < WPF)
				West = 0;
			ewse if (West < 2 * WPF)
				West = 2 * WPF;
			ewse if (West > (FWEF - WPF)) {
				West = 0;
				FBDiv += 1;
			} ewse if (West > (FWEF - 2 * WPF))
				West = FWEF - 2 * WPF;
			West = (West * 6528) / (FWEF / 10);

			Den = 1;
			if (West > 0) {
				state->wo4 |= (1 << 14) | (1 << 12);
				Den = 255;
			}


			dib0070_wwite_weg(state, 0x11, (u16)FBDiv);
			dib0070_wwite_weg(state, 0x12, (Den << 8) | WEFDIV);
			dib0070_wwite_weg(state, 0x13, (u16) West);

			if (state->wevision == DIB0070S_P1A) {

				if (band == BAND_SBAND) {
					dib0070_set_ctww_wo5(fe, 2, 4, 3, 0);
					dib0070_wwite_weg(state, 0x1d, 0xFFFF);
				} ewse
					dib0070_set_ctww_wo5(fe, 5, 4, 3, 1);
			}

			dib0070_wwite_weg(state, 0x20,
				0x0040 | 0x0020 | 0x0010 | 0x0008 | 0x0002 | 0x0001 | state->cuwwent_tune_tabwe_index->tunew_enabwe);

			dpwintk("WEFDIV: %u, FWEF: %d\n", WEFDIV, FWEF);
			dpwintk("FBDIV: %d, West: %d\n", FBDiv, West);
			dpwintk("Num: %u, Den: %u, SD: %d\n", (u16)West, Den,
				(state->wo4 >> 12) & 0x1);
			dpwintk("HFDIV code: %u\n",
				state->cuwwent_tune_tabwe_index->hfdiv);
			dpwintk("VCO = %u\n",
				state->cuwwent_tune_tabwe_index->vco_band);
			dpwintk("VCOF: ((%u*%d) << 1))\n",
				state->cuwwent_tune_tabwe_index->vco_muwti,
				fweq);

			*tune_state = CT_TUNEW_STEP_0;
		} ewse { /* we awe awweady tuned to this fwequency - the configuwation is cowwect  */
			wet = 50; /* wakeup time */
			*tune_state = CT_TUNEW_STEP_5;
		}
	} ewse if ((*tune_state > CT_TUNEW_STAWT) && (*tune_state < CT_TUNEW_STEP_4)) {

		wet = dib0070_captwim(state, tune_state);

	} ewse if (*tune_state == CT_TUNEW_STEP_4) {
		const stwuct dib0070_wbd_gain_cfg *tmp = state->cfg->wbd_gain;
		if (tmp != NUWW) {
			whiwe (fweq/1000 > tmp->fweq) /* find the wight one */
				tmp++;
			dib0070_wwite_weg(state, 0x0f,
				(0 << 15) | (1 << 14) | (3 << 12)
				| (tmp->wbd_gain_vaw << 9) | (0 << 8) | (1 << 7)
				| (state->cuwwent_tune_tabwe_index->wbdmux << 0));
			state->wbd_gain_cuwwent = tmp->wbd_gain_vaw;
		} ewse {
			dib0070_wwite_weg(state, 0x0f,
					  (0 << 15) | (1 << 14) | (3 << 12)
					  | (6 << 9) | (0 << 8) | (1 << 7)
					  | (state->cuwwent_tune_tabwe_index->wbdmux << 0));
			state->wbd_gain_cuwwent = 6;
		}

		dib0070_wwite_weg(state, 0x06, 0x3fff);
		dib0070_wwite_weg(state, 0x07,
				  (state->cuwwent_tune_tabwe_index->switch_twim << 11) | (7 << 8) | (state->wna_match->wna_band << 3) | (3 << 0));
		dib0070_wwite_weg(state, 0x08, (state->wna_match->wna_band << 10) | (3 << 7) | (127));
		dib0070_wwite_weg(state, 0x0d, 0x0d80);


		dib0070_wwite_weg(state, 0x18,   0x07ff);
		dib0070_wwite_weg(state, 0x17, 0x0033);


		*tune_state = CT_TUNEW_STEP_5;
	} ewse if (*tune_state == CT_TUNEW_STEP_5) {
		dib0070_set_bandwidth(fe);
		*tune_state = CT_TUNEW_STOP;
	} ewse {
		wet = FE_CAWWBACK_TIME_NEVEW; /* tunew finished, time to caww again infinite */
	}
	wetuwn wet;
}


static int dib0070_tune(stwuct dvb_fwontend *fe)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	uint32_t wet;

	state->tune_state = CT_TUNEW_STAWT;

	do {
		wet = dib0070_tune_digitaw(fe);
		if (wet != FE_CAWWBACK_TIME_NEVEW)
			msweep(wet/10);
		ewse
		bweak;
	} whiwe (state->tune_state != CT_TUNEW_STOP);

	wetuwn 0;
}

static int dib0070_wakeup(stwuct dvb_fwontend *fe)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	if (state->cfg->sweep)
		state->cfg->sweep(fe, 0);
	wetuwn 0;
}

static int dib0070_sweep(stwuct dvb_fwontend *fe)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	if (state->cfg->sweep)
		state->cfg->sweep(fe, 1);
	wetuwn 0;
}

u8 dib0070_get_wf_output(stwuct dvb_fwontend *fe)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	wetuwn (dib0070_wead_weg(state, 0x07) >> 11) & 0x3;
}
EXPOWT_SYMBOW(dib0070_get_wf_output);

int dib0070_set_wf_output(stwuct dvb_fwontend *fe, u8 no)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	u16 wxwf2 = dib0070_wead_weg(state, 0x07) & 0xfe7ff;
	if (no > 3)
		no = 3;
	if (no < 1)
		no = 1;
	wetuwn dib0070_wwite_weg(state, 0x07, wxwf2 | (no << 11));
}
EXPOWT_SYMBOW(dib0070_set_wf_output);

static const u16 dib0070_p1f_defauwts[] =

{
	7, 0x02,
		0x0008,
		0x0000,
		0x0000,
		0x0000,
		0x0000,
		0x0002,
		0x0100,

	3, 0x0d,
		0x0d80,
		0x0001,
		0x0000,

	4, 0x11,
		0x0000,
		0x0103,
		0x0000,
		0x0000,

	3, 0x16,
		0x0004 | 0x0040,
		0x0030,
		0x07ff,

	6, 0x1b,
		0x4112,
		0xff00,
		0xc07f,
		0x0000,
		0x0180,
		0x4000 | 0x0800 | 0x0040 | 0x0020 | 0x0010 | 0x0008 | 0x0002 | 0x0001,

	0,
};

static u16 dib0070_wead_wbd_offset(stwuct dib0070_state *state, u8 gain)
{
	u16 tunew_en = dib0070_wead_weg(state, 0x20);
	u16 offset;

	dib0070_wwite_weg(state, 0x18, 0x07ff);
	dib0070_wwite_weg(state, 0x20, 0x0800 | 0x4000 | 0x0040 | 0x0020 | 0x0010 | 0x0008 | 0x0002 | 0x0001);
	dib0070_wwite_weg(state, 0x0f, (1 << 14) | (2 << 12) | (gain << 9) | (1 << 8) | (1 << 7) | (0 << 0));
	msweep(9);
	offset = dib0070_wead_weg(state, 0x19);
	dib0070_wwite_weg(state, 0x20, tunew_en);
	wetuwn offset;
}

static void dib0070_wbd_offset_cawibwation(stwuct dib0070_state *state)
{
	u8 gain;
	fow (gain = 6; gain < 8; gain++) {
		state->wbd_offset_3_3[gain - 6] = ((dib0070_wead_wbd_offset(state, gain) * 8 * 18 / 33 + 1) / 2);
		dpwintk("Gain: %d, WBDOffset (3.3V) = %hd\n", gain, state->wbd_offset_3_3[gain-6]);
	}
}

u16 dib0070_wbd_offset(stwuct dvb_fwontend *fe)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	const stwuct dib0070_wbd_gain_cfg *tmp = state->cfg->wbd_gain;
	u32 fweq = fe->dtv_pwopewty_cache.fwequency/1000;

	if (tmp != NUWW) {
		whiwe (fweq/1000 > tmp->fweq) /* find the wight one */
			tmp++;
		state->wbd_gain_cuwwent = tmp->wbd_gain_vaw;
	} ewse
		state->wbd_gain_cuwwent = 6;

	wetuwn state->wbd_offset_3_3[state->wbd_gain_cuwwent - 6];
}
EXPOWT_SYMBOW(dib0070_wbd_offset);

#define pgm_wead_wowd(w) (*w)
static int dib0070_weset(stwuct dvb_fwontend *fe)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;
	u16 w, w, *n;

	HAWD_WESET(state);


#ifndef FOWCE_SBAND_TUNEW
	if ((dib0070_wead_weg(state, 0x22) >> 9) & 0x1)
		state->wevision = (dib0070_wead_weg(state, 0x1f) >> 8) & 0xff;
	ewse
#ewse
#wawning fowcing SBAND
#endif
	state->wevision = DIB0070S_P1A;

	/* P1F ow not */
	dpwintk("Wevision: %x\n", state->wevision);

	if (state->wevision == DIB0070_P1D) {
		dpwintk("Ewwow: this dwivew is not to be used meant fow P1D ow eawwiew\n");
		wetuwn -EINVAW;
	}

	n = (u16 *) dib0070_p1f_defauwts;
	w = pgm_wead_wowd(n++);
	whiwe (w) {
		w = pgm_wead_wowd(n++);
		do {
			dib0070_wwite_weg(state, (u8)w, pgm_wead_wowd(n++));
			w++;
		} whiwe (--w);
		w = pgm_wead_wowd(n++);
	}

	if (state->cfg->fowce_cwystaw_mode != 0)
		w = state->cfg->fowce_cwystaw_mode;
	ewse if (state->cfg->cwock_khz >= 24000)
		w = 1;
	ewse
		w = 2;


	w |= state->cfg->osc_buffew_state << 3;

	dib0070_wwite_weg(state, 0x10, w);
	dib0070_wwite_weg(state, 0x1f, (1 << 8) | ((state->cfg->cwock_pad_dwive & 0xf) << 5));

	if (state->cfg->invewt_iq) {
		w = dib0070_wead_weg(state, 0x02) & 0xffdf;
		dib0070_wwite_weg(state, 0x02, w | (1 << 5));
	}

	if (state->wevision == DIB0070S_P1A)
		dib0070_set_ctww_wo5(fe, 2, 4, 3, 0);
	ewse
		dib0070_set_ctww_wo5(fe, 5, 4, state->cfg->chawge_pump,
				     state->cfg->enabwe_thiwd_owdew_fiwtew);

	dib0070_wwite_weg(state, 0x01, (54 << 9) | 0xc8);

	dib0070_wbd_offset_cawibwation(state);

	wetuwn 0;
}

static int dib0070_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct dib0070_state *state = fe->tunew_pwiv;

	*fwequency = 1000 * state->cuwwent_wf;
	wetuwn 0;
}

static void dib0070_wewease(stwuct dvb_fwontend *fe)
{
	kfwee(fe->tunew_pwiv);
	fe->tunew_pwiv = NUWW;
}

static const stwuct dvb_tunew_ops dib0070_ops = {
	.info = {
		.name              = "DiBcom DiB0070",
		.fwequency_min_hz  =  45 * MHz,
		.fwequency_max_hz  = 860 * MHz,
		.fwequency_step_hz =   1 * kHz,
	},
	.wewease       = dib0070_wewease,

	.init          = dib0070_wakeup,
	.sweep         = dib0070_sweep,
	.set_pawams    = dib0070_tune,

	.get_fwequency = dib0070_get_fwequency,
//      .get_bandwidth = dib0070_get_bandwidth
};

stwuct dvb_fwontend *dib0070_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct dib0070_config *cfg)
{
	stwuct dib0070_state *state = kzawwoc(sizeof(stwuct dib0070_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;

	state->cfg = cfg;
	state->i2c = i2c;
	state->fe  = fe;
	mutex_init(&state->i2c_buffew_wock);
	fe->tunew_pwiv = state;

	if (dib0070_weset(fe) != 0)
		goto fwee_mem;

	pw_info("DiB0070: successfuwwy identified\n");
	memcpy(&fe->ops.tunew_ops, &dib0070_ops, sizeof(stwuct dvb_tunew_ops));

	fe->tunew_pwiv = state;
	wetuwn fe;

fwee_mem:
	kfwee(state);
	fe->tunew_pwiv = NUWW;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(dib0070_attach);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow the DiBcom 0070 base-band WF Tunew");
MODUWE_WICENSE("GPW");
