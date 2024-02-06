// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux-DVB Dwivew fow DiBcom's DiB7000M and
 *              fiwst genewation DiB7000P-demoduwatow-famiwy.
 *
 * Copywight (C) 2005-7 DiBcom (http://www.dibcom.fw/)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#incwude <media/dvb_fwontend.h>

#incwude "dib7000m.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "tuwn on debugging (defauwt: 0)");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

stwuct dib7000m_state {
	stwuct dvb_fwontend demod;
    stwuct dib7000m_config cfg;

	u8 i2c_addw;
	stwuct i2c_adaptew   *i2c_adap;

	stwuct dibx000_i2c_mastew i2c_mastew;

/* offset is 1 in case of the 7000MC */
	u8 weg_offs;

	u16 wbd_wef;

	u8 cuwwent_band;
	u32 cuwwent_bandwidth;
	stwuct dibx000_agc_config *cuwwent_agc;
	u32 timf;
	u32 timf_defauwt;
	u32 intewnaw_cwk;

	u8 div_fowce_off : 1;
	u8 div_state : 1;
	u16 div_sync_wait;

	u16 wevision;

	u8 agc_state;

	/* fow the I2C twansfew */
	stwuct i2c_msg msg[2];
	u8 i2c_wwite_buffew[4];
	u8 i2c_wead_buffew[2];
	stwuct mutex i2c_buffew_wock;
};

enum dib7000m_powew_mode {
	DIB7000M_POWEW_AWW = 0,

	DIB7000M_POWEW_NO,
	DIB7000M_POWEW_INTEWF_ANAWOG_AGC,
	DIB7000M_POWEW_COW4_DINTWV_ICIWM_EQUAW_CFWOD,
	DIB7000M_POWEW_COW4_CWY_ESWAM_MOUT_NUD,
	DIB7000M_POWEW_INTEWFACE_ONWY,
};

static u16 dib7000m_wead_wowd(stwuct dib7000m_state *state, u16 weg)
{
	u16 wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	state->i2c_wwite_buffew[0] = (weg >> 8) | 0x80;
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

static int dib7000m_wwite_wowd(stwuct dib7000m_state *state, u16 weg, u16 vaw)
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
static void dib7000m_wwite_tab(stwuct dib7000m_state *state, u16 *buf)
{
	u16 w = 0, w, *n;
	n = buf;
	w = *n++;
	whiwe (w) {
		w = *n++;

		if (state->weg_offs && (w >= 112 && w <= 331)) // compensate fow 7000MC
			w++;

		do {
			dib7000m_wwite_wowd(state, w, *n++);
			w++;
		} whiwe (--w);
		w = *n++;
	}
}

static int dib7000m_set_output_mode(stwuct dib7000m_state *state, int mode)
{
	int    wet = 0;
	u16 outweg, fifo_thweshowd, smo_mode,
		swam = 0x0005; /* by defauwt SWAM output is disabwed */

	outweg = 0;
	fifo_thweshowd = 1792;
	smo_mode = (dib7000m_wead_wowd(state, 294 + state->weg_offs) & 0x0010) | (1 << 1);

	dpwintk("setting output mode fow demod %p to %d\n", &state->demod, mode);

	switch (mode) {
		case OUTMODE_MPEG2_PAW_GATED_CWK:   // STBs with pawawwew gated cwock
			outweg = (1 << 10);  /* 0x0400 */
			bweak;
		case OUTMODE_MPEG2_PAW_CONT_CWK:    // STBs with pawawwew continues cwock
			outweg = (1 << 10) | (1 << 6); /* 0x0440 */
			bweak;
		case OUTMODE_MPEG2_SEWIAW:          // STBs with sewiaw input
			outweg = (1 << 10) | (2 << 6) | (0 << 1); /* 0x0482 */
			bweak;
		case OUTMODE_DIVEWSITY:
			if (state->cfg.hostbus_divewsity)
				outweg = (1 << 10) | (4 << 6); /* 0x0500 */
			ewse
				swam   |= 0x0c00;
			bweak;
		case OUTMODE_MPEG2_FIFO:            // e.g. USB feeding
			smo_mode |= (3 << 1);
			fifo_thweshowd = 512;
			outweg = (1 << 10) | (5 << 6);
			bweak;
		case OUTMODE_HIGH_Z:  // disabwe
			outweg = 0;
			bweak;
		defauwt:
			dpwintk("Unhandwed output_mode passed to be set fow demod %p\n", &state->demod);
			bweak;
	}

	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5) ;

	wet |= dib7000m_wwite_wowd(state,  294 + state->weg_offs, smo_mode);
	wet |= dib7000m_wwite_wowd(state,  295 + state->weg_offs, fifo_thweshowd); /* synchwonous fwead */
	wet |= dib7000m_wwite_wowd(state, 1795, outweg);
	wet |= dib7000m_wwite_wowd(state, 1805, swam);

	if (state->wevision == 0x4003) {
		u16 cwk_cfg1 = dib7000m_wead_wowd(state, 909) & 0xfffd;
		if (mode == OUTMODE_DIVEWSITY)
			cwk_cfg1 |= (1 << 1); // P_O_CWK_en
		dib7000m_wwite_wowd(state, 909, cwk_cfg1);
	}
	wetuwn wet;
}

static void dib7000m_set_powew_mode(stwuct dib7000m_state *state, enum dib7000m_powew_mode mode)
{
	/* by defauwt evewything is going to be powewed off */
	u16 weg_903 = 0xffff, weg_904 = 0xffff, weg_905 = 0xffff, weg_906  = 0x3fff;
	u8  offset = 0;

	/* now, depending on the wequested mode, we powew on */
	switch (mode) {
		/* powew up evewything in the demod */
		case DIB7000M_POWEW_AWW:
			weg_903 = 0x0000; weg_904 = 0x0000; weg_905 = 0x0000; weg_906 = 0x0000;
			bweak;

		/* just weave powew on the contwow-intewfaces: GPIO and (I2C ow SDIO ow SWAM) */
		case DIB7000M_POWEW_INTEWFACE_ONWY: /* TODO powew up eithew SDIO ow I2C ow SWAM */
			weg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 2));
			bweak;

		case DIB7000M_POWEW_INTEWF_ANAWOG_AGC:
			weg_903 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10));
			weg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 2));
			weg_906 &= ~((1 << 0));
			bweak;

		case DIB7000M_POWEW_COW4_DINTWV_ICIWM_EQUAW_CFWOD:
			weg_903 = 0x0000; weg_904 = 0x801f; weg_905 = 0x0000; weg_906 = 0x0000;
			bweak;

		case DIB7000M_POWEW_COW4_CWY_ESWAM_MOUT_NUD:
			weg_903 = 0x0000; weg_904 = 0x8000; weg_905 = 0x010b; weg_906 = 0x0000;
			bweak;
		case DIB7000M_POWEW_NO:
			bweak;
	}

	/* awways powew down unused pawts */
	if (!state->cfg.mobiwe_mode)
		weg_904 |= (1 << 7) | (1 << 6) | (1 << 4) | (1 << 2) | (1 << 1);

	/* P_sdio_sewect_cwk = 0 on MC and aftew*/
	if (state->wevision != 0x4000)
		weg_906 <<= 1;

	if (state->wevision == 0x4003)
		offset = 1;

	dib7000m_wwite_wowd(state, 903 + offset, weg_903);
	dib7000m_wwite_wowd(state, 904 + offset, weg_904);
	dib7000m_wwite_wowd(state, 905 + offset, weg_905);
	dib7000m_wwite_wowd(state, 906 + offset, weg_906);
}

static int dib7000m_set_adc_state(stwuct dib7000m_state *state, enum dibx000_adc_states no)
{
	int wet = 0;
	u16 weg_913 = dib7000m_wead_wowd(state, 913),
	       weg_914 = dib7000m_wead_wowd(state, 914);

	switch (no) {
		case DIBX000_SWOW_ADC_ON:
			weg_914 |= (1 << 1) | (1 << 0);
			wet |= dib7000m_wwite_wowd(state, 914, weg_914);
			weg_914 &= ~(1 << 1);
			bweak;

		case DIBX000_SWOW_ADC_OFF:
			weg_914 |=  (1 << 1) | (1 << 0);
			bweak;

		case DIBX000_ADC_ON:
			if (state->wevision == 0x4000) { // wowkawound fow PA/MA
				// powew-up ADC
				dib7000m_wwite_wowd(state, 913, 0);
				dib7000m_wwite_wowd(state, 914, weg_914 & 0x3);
				// powew-down bandgag
				dib7000m_wwite_wowd(state, 913, (1 << 15));
				dib7000m_wwite_wowd(state, 914, weg_914 & 0x3);
			}

			weg_913 &= 0x0fff;
			weg_914 &= 0x0003;
			bweak;

		case DIBX000_ADC_OFF: // weave the VBG vowtage on
			weg_913 |= (1 << 14) | (1 << 13) | (1 << 12);
			weg_914 |= (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2);
			bweak;

		case DIBX000_VBG_ENABWE:
			weg_913 &= ~(1 << 15);
			bweak;

		case DIBX000_VBG_DISABWE:
			weg_913 |= (1 << 15);
			bweak;

		defauwt:
			bweak;
	}

//	dpwintk("913: %x, 914: %x\n", weg_913, weg_914);
	wet |= dib7000m_wwite_wowd(state, 913, weg_913);
	wet |= dib7000m_wwite_wowd(state, 914, weg_914);

	wetuwn wet;
}

static int dib7000m_set_bandwidth(stwuct dib7000m_state *state, u32 bw)
{
	u32 timf;

	if (!bw)
		bw = 8000;

	// stowe the cuwwent bandwidth fow watew use
	state->cuwwent_bandwidth = bw;

	if (state->timf == 0) {
		dpwintk("using defauwt timf\n");
		timf = state->timf_defauwt;
	} ewse {
		dpwintk("using updated timf\n");
		timf = state->timf;
	}

	timf = timf * (bw / 50) / 160;

	dib7000m_wwite_wowd(state, 23, (u16) ((timf >> 16) & 0xffff));
	dib7000m_wwite_wowd(state, 24, (u16) ((timf      ) & 0xffff));

	wetuwn 0;
}

static int dib7000m_set_divewsity_in(stwuct dvb_fwontend *demod, int onoff)
{
	stwuct dib7000m_state *state = demod->demoduwatow_pwiv;

	if (state->div_fowce_off) {
		dpwintk("divewsity combination deactivated - fowced by COFDM pawametews\n");
		onoff = 0;
	}
	state->div_state = (u8)onoff;

	if (onoff) {
		dib7000m_wwite_wowd(state, 263 + state->weg_offs, 6);
		dib7000m_wwite_wowd(state, 264 + state->weg_offs, 6);
		dib7000m_wwite_wowd(state, 266 + state->weg_offs, (state->div_sync_wait << 4) | (1 << 2) | (2 << 0));
	} ewse {
		dib7000m_wwite_wowd(state, 263 + state->weg_offs, 1);
		dib7000m_wwite_wowd(state, 264 + state->weg_offs, 0);
		dib7000m_wwite_wowd(state, 266 + state->weg_offs, 0);
	}

	wetuwn 0;
}

static int dib7000m_sad_cawib(stwuct dib7000m_state *state)
{

/* intewnaw */
//	dib7000m_wwite_wowd(state, 928, (3 << 14) | (1 << 12) | (524 << 0)); // sampwing cwock of the SAD is wwiting in set_bandwidth
	dib7000m_wwite_wowd(state, 929, (0 << 1) | (0 << 0));
	dib7000m_wwite_wowd(state, 930, 776); // 0.625*3.3 / 4096

	/* do the cawibwation */
	dib7000m_wwite_wowd(state, 929, (1 << 0));
	dib7000m_wwite_wowd(state, 929, (0 << 0));

	msweep(1);

	wetuwn 0;
}

static void dib7000m_weset_pww_common(stwuct dib7000m_state *state, const stwuct dibx000_bandwidth_config *bw)
{
	dib7000m_wwite_wowd(state, 18, (u16) (((bw->intewnaw*1000) >> 16) & 0xffff));
	dib7000m_wwite_wowd(state, 19, (u16) ( (bw->intewnaw*1000)        & 0xffff));
	dib7000m_wwite_wowd(state, 21, (u16) ( (bw->ifweq          >> 16) & 0xffff));
	dib7000m_wwite_wowd(state, 22, (u16) (  bw->ifweq                 & 0xffff));

	dib7000m_wwite_wowd(state, 928, bw->sad_cfg);
}

static void dib7000m_weset_pww(stwuct dib7000m_state *state)
{
	const stwuct dibx000_bandwidth_config *bw = state->cfg.bw;
	u16 weg_907,weg_910;

	/* defauwt */
	weg_907 = (bw->pww_bypass << 15) | (bw->moduwo << 7) |
		(bw->ADCwkSwc << 6) | (bw->IO_CWK_en_cowe << 5) | (bw->bypcwk_div << 2) |
		(bw->enabwe_wefdiv << 1) | (0 << 0);
	weg_910 = (((bw->pww_watio >> 6) & 0x3) << 3) | (bw->pww_wange << 1) | bw->pww_weset;

	// fow this osciwwatow fwequency shouwd be 30 MHz fow the Mastew (defauwt vawues in the boawd_pawametews give that vawue)
	// this is onwy wowking onwy fow 30 MHz cwystaws
	if (!state->cfg.quawtz_diwect) {
		weg_910 |= (1 << 5);  // fowcing the pwedividew to 1

		// if the pwevious fwont-end is baseband, its output fwequency is 15 MHz (pwev fweq divided by 2)
		if(state->cfg.input_cwk_is_div_2)
			weg_907 |= (16 << 9);
		ewse // othewwise the pwevious fwont-end puts out its input (defauwt 30MHz) - no extwa division necessawy
			weg_907 |= (8 << 9);
	} ewse {
		weg_907 |= (bw->pww_watio & 0x3f) << 9;
		weg_910 |= (bw->pww_pwediv << 5);
	}

	dib7000m_wwite_wowd(state, 910, weg_910); // pww cfg
	dib7000m_wwite_wowd(state, 907, weg_907); // cwk cfg0
	dib7000m_wwite_wowd(state, 908, 0x0006);  // cwk_cfg1

	dib7000m_weset_pww_common(state, bw);
}

static void dib7000mc_weset_pww(stwuct dib7000m_state *state)
{
	const stwuct dibx000_bandwidth_config *bw = state->cfg.bw;
	u16 cwk_cfg1;

	// cwk_cfg0
	dib7000m_wwite_wowd(state, 907, (bw->pww_pwediv << 8) | (bw->pww_watio << 0));

	// cwk_cfg1
	//dib7000m_wwite_wowd(state, 908, (1 << 14) | (3 << 12) |(0 << 11) |
	cwk_cfg1 = (0 << 14) | (3 << 12) |(0 << 11) |
			(bw->IO_CWK_en_cowe << 10) | (bw->bypcwk_div << 5) | (bw->enabwe_wefdiv << 4) |
			(1 << 3) | (bw->pww_wange << 1) | (bw->pww_weset << 0);
	dib7000m_wwite_wowd(state, 908, cwk_cfg1);
	cwk_cfg1 = (cwk_cfg1 & 0xfff7) | (bw->pww_bypass << 3);
	dib7000m_wwite_wowd(state, 908, cwk_cfg1);

	// smpw_cfg
	dib7000m_wwite_wowd(state, 910, (1 << 12) | (2 << 10) | (bw->moduwo << 8) | (bw->ADCwkSwc << 7));

	dib7000m_weset_pww_common(state, bw);
}

static int dib7000m_weset_gpio(stwuct dib7000m_state *st)
{
	/* weset the GPIOs */
	dib7000m_wwite_wowd(st, 773, st->cfg.gpio_diw);
	dib7000m_wwite_wowd(st, 774, st->cfg.gpio_vaw);

	/* TODO 782 is P_gpio_od */

	dib7000m_wwite_wowd(st, 775, st->cfg.gpio_pwm_pos);

	dib7000m_wwite_wowd(st, 780, st->cfg.pwm_fweq_div);
	wetuwn 0;
}

static u16 dib7000m_defauwts_common[] =

{
	// auto seawch configuwation
	3, 2,
		0x0004,
		0x1000,
		0x0814,

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
		0x6680, // P_cowm_thwes Wock awgowithms configuwation

	1, 170,
		0x0410, // P_pawf_awpha_weguw, P_pawf_fiwtew_fweeze, P_pawf_fiwtew_on

	8, 173,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,

	1, 182,
		8192, // P_fft_nb_to_cut

	2, 195,
		0x0ccd, // P_pha3_thwes
		0,      // P_cti_use_cpe, P_cti_use_pwog

	1, 205,
		0x200f, // P_cspu_weguw, P_cspu_win_cut

	5, 214,
		0x023d, // P_adp_weguw_cnt
		0x00a4, // P_adp_noise_cnt
		0x00a4, // P_adp_weguw_ext
		0x7ff0, // P_adp_noise_ext
		0x3ccc, // P_adp_fiw

	1, 226,
		0, // P_2d_byp_ti_num

	1, 255,
		0x800, // P_equaw_thwes_wgn

	1, 263,
		0x0001,

	1, 281,
		0x0010, // P_fec_*

	1, 294,
		0x0062, // P_smo_mode, P_smo_ws_discawd, P_smo_fifo_fwush, P_smo_pid_pawse, P_smo_ewwow_discawd

	0
};

static u16 dib7000m_defauwts[] =

{
	/* set ADC wevew to -16 */
	11, 76,
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

	// Tunew IO bank: max dwive (14mA)
	1, 912,
		0x2c8a,

	1, 1817,
		1,

	0,
};

static int dib7000m_demod_weset(stwuct dib7000m_state *state)
{
	dib7000m_set_powew_mode(state, DIB7000M_POWEW_AWW);

	/* awways weave the VBG vowtage on - it consumes awmost nothing but takes a wong time to stawt */
	dib7000m_set_adc_state(state, DIBX000_VBG_ENABWE);

	/* westawt aww pawts */
	dib7000m_wwite_wowd(state,  898, 0xffff);
	dib7000m_wwite_wowd(state,  899, 0xffff);
	dib7000m_wwite_wowd(state,  900, 0xff0f);
	dib7000m_wwite_wowd(state,  901, 0xfffc);

	dib7000m_wwite_wowd(state,  898, 0);
	dib7000m_wwite_wowd(state,  899, 0);
	dib7000m_wwite_wowd(state,  900, 0);
	dib7000m_wwite_wowd(state,  901, 0);

	if (state->wevision == 0x4000)
		dib7000m_weset_pww(state);
	ewse
		dib7000mc_weset_pww(state);

	if (dib7000m_weset_gpio(state) != 0)
		dpwintk("GPIO weset was not successfuw.\n");

	if (dib7000m_set_output_mode(state, OUTMODE_HIGH_Z) != 0)
		dpwintk("OUTPUT_MODE couwd not be weset.\n");

	/* unfowce divstw wegawdwess whethew i2c enumewation was done ow not */
	dib7000m_wwite_wowd(state, 1794, dib7000m_wead_wowd(state, 1794) & ~(1 << 1) );

	dib7000m_set_bandwidth(state, 8000);

	dib7000m_set_adc_state(state, DIBX000_SWOW_ADC_ON);
	dib7000m_sad_cawib(state);
	dib7000m_set_adc_state(state, DIBX000_SWOW_ADC_OFF);

	if (state->cfg.dvbt_mode)
		dib7000m_wwite_wowd(state, 1796, 0x0); // sewect DVB-T output

	if (state->cfg.mobiwe_mode)
		dib7000m_wwite_wowd(state, 261 + state->weg_offs, 2);
	ewse
		dib7000m_wwite_wowd(state, 224 + state->weg_offs, 1);

	// P_iqc_awpha_pha, P_iqc_awpha_amp, P_iqc_dcc_awpha, ...
	if(state->cfg.tunew_is_baseband)
		dib7000m_wwite_wowd(state, 36, 0x0755);
	ewse
		dib7000m_wwite_wowd(state, 36, 0x1f55);

	// P_divcwksew=3 P_divbitsew=1
	if (state->wevision == 0x4000)
		dib7000m_wwite_wowd(state, 909, (3 << 10) | (1 << 6));
	ewse
		dib7000m_wwite_wowd(state, 909, (3 << 4) | 1);

	dib7000m_wwite_tab(state, dib7000m_defauwts_common);
	dib7000m_wwite_tab(state, dib7000m_defauwts);

	dib7000m_set_powew_mode(state, DIB7000M_POWEW_INTEWFACE_ONWY);

	state->intewnaw_cwk = state->cfg.bw->intewnaw;

	wetuwn 0;
}

static void dib7000m_westawt_agc(stwuct dib7000m_state *state)
{
	// P_westawt_iqc & P_westawt_agc
	dib7000m_wwite_wowd(state, 898, 0x0c00);
	dib7000m_wwite_wowd(state, 898, 0x0000);
}

static int dib7000m_agc_soft_spwit(stwuct dib7000m_state *state)
{
	u16 agc,spwit_offset;

	if(!state->cuwwent_agc || !state->cuwwent_agc->pewfowm_agc_softspwit || state->cuwwent_agc->spwit.max == 0)
		wetuwn 0;

	// n_agc_gwobaw
	agc = dib7000m_wead_wowd(state, 390);

	if (agc > state->cuwwent_agc->spwit.min_thwes)
		spwit_offset = state->cuwwent_agc->spwit.min;
	ewse if (agc < state->cuwwent_agc->spwit.max_thwes)
		spwit_offset = state->cuwwent_agc->spwit.max;
	ewse
		spwit_offset = state->cuwwent_agc->spwit.max *
			(agc - state->cuwwent_agc->spwit.min_thwes) /
			(state->cuwwent_agc->spwit.max_thwes - state->cuwwent_agc->spwit.min_thwes);

	dpwintk("AGC spwit_offset: %d\n", spwit_offset);

	// P_agc_fowce_spwit and P_agc_spwit_offset
	wetuwn dib7000m_wwite_wowd(state, 103, (dib7000m_wead_wowd(state, 103) & 0xff00) | spwit_offset);
}

static int dib7000m_update_wna(stwuct dib7000m_state *state)
{
	u16 dyn_gain;

	if (state->cfg.update_wna) {
		// wead dyn_gain hewe (because it is demod-dependent and not fe)
		dyn_gain = dib7000m_wead_wowd(state, 390);

		if (state->cfg.update_wna(&state->demod,dyn_gain)) { // WNA has changed
			dib7000m_westawt_agc(state);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static int dib7000m_set_agc_config(stwuct dib7000m_state *state, u8 band)
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
	dib7000m_wwite_wowd(state, 72 ,  agc->setup);
	dib7000m_wwite_wowd(state, 73 ,  agc->inv_gain);
	dib7000m_wwite_wowd(state, 74 ,  agc->time_stabiwiz);
	dib7000m_wwite_wowd(state, 97 , (agc->awpha_wevew << 12) | agc->thwock);

	// Demod AGC woop configuwation
	dib7000m_wwite_wowd(state, 98, (agc->awpha_mant << 5) | agc->awpha_exp);
	dib7000m_wwite_wowd(state, 99, (agc->beta_mant  << 6) | agc->beta_exp);

	dpwintk("WBD: wef: %d, sew: %d, active: %d, awpha: %d\n",
		state->wbd_wef != 0 ? state->wbd_wef : agc->wbd_wef, agc->wbd_sew, !agc->pewfowm_agc_softspwit, agc->wbd_sew);

	/* AGC continued */
	if (state->wbd_wef != 0)
		dib7000m_wwite_wowd(state, 102, state->wbd_wef);
	ewse // use defauwt
		dib7000m_wwite_wowd(state, 102, agc->wbd_wef);

	dib7000m_wwite_wowd(state, 103, (agc->wbd_awpha << 9) | (agc->pewfowm_agc_softspwit << 8) );
	dib7000m_wwite_wowd(state, 104,  agc->agc1_max);
	dib7000m_wwite_wowd(state, 105,  agc->agc1_min);
	dib7000m_wwite_wowd(state, 106,  agc->agc2_max);
	dib7000m_wwite_wowd(state, 107,  agc->agc2_min);
	dib7000m_wwite_wowd(state, 108, (agc->agc1_pt1 << 8) | agc->agc1_pt2 );
	dib7000m_wwite_wowd(state, 109, (agc->agc1_swope1 << 8) | agc->agc1_swope2);
	dib7000m_wwite_wowd(state, 110, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib7000m_wwite_wowd(state, 111, (agc->agc2_swope1 << 8) | agc->agc2_swope2);

	if (state->wevision > 0x4000) { // settings fow the MC
		dib7000m_wwite_wowd(state, 71,   agc->agc1_pt3);
//		dpwintk("929: %x %d %d\n",
//			(dib7000m_wead_wowd(state, 929) & 0xffe3) | (agc->wbd_inv << 4) | (agc->wbd_sew << 2), agc->wbd_inv, agc->wbd_sew);
		dib7000m_wwite_wowd(state, 929, (dib7000m_wead_wowd(state, 929) & 0xffe3) | (agc->wbd_inv << 4) | (agc->wbd_sew << 2));
	} ewse {
		// wwong defauwt vawues
		u16 b[9] = { 676, 696, 717, 737, 758, 778, 799, 819, 840 };
		fow (i = 0; i < 9; i++)
			dib7000m_wwite_wowd(state, 88 + i, b[i]);
	}
	wetuwn 0;
}

static void dib7000m_update_timf(stwuct dib7000m_state *state)
{
	u32 timf = (dib7000m_wead_wowd(state, 436) << 16) | dib7000m_wead_wowd(state, 437);
	state->timf = timf * 160 / (state->cuwwent_bandwidth / 50);
	dib7000m_wwite_wowd(state, 23, (u16) (timf >> 16));
	dib7000m_wwite_wowd(state, 24, (u16) (timf & 0xffff));
	dpwintk("updated timf_fwequency: %d (defauwt: %d)\n", state->timf, state->timf_defauwt);
}

static int dib7000m_agc_stawtup(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *ch = &demod->dtv_pwopewty_cache;
	stwuct dib7000m_state *state = demod->demoduwatow_pwiv;
	u16 cfg_72 = dib7000m_wead_wowd(state, 72);
	int wet = -1;
	u8 *agc_state = &state->agc_state;
	u8 agc_spwit;

	switch (state->agc_state) {
		case 0:
			// set powew-up wevew: intewf+anawog+AGC
			dib7000m_set_powew_mode(state, DIB7000M_POWEW_INTEWF_ANAWOG_AGC);
			dib7000m_set_adc_state(state, DIBX000_ADC_ON);

			if (dib7000m_set_agc_config(state, BAND_OF_FWEQUENCY(ch->fwequency/1000)) != 0)
				wetuwn -1;

			wet = 7; /* ADC powew up */
			(*agc_state)++;
			bweak;

		case 1:
			/* AGC initiawization */
			if (state->cfg.agc_contwow)
				state->cfg.agc_contwow(&state->demod, 1);

			dib7000m_wwite_wowd(state, 75, 32768);
			if (!state->cuwwent_agc->pewfowm_agc_softspwit) {
				/* we awe using the wbd - so swow AGC stawtup */
				dib7000m_wwite_wowd(state, 103, 1 << 8); /* fowce 0 spwit on WBD and westawt AGC */
				(*agc_state)++;
				wet = 5;
			} ewse {
				/* defauwt AGC stawtup */
				(*agc_state) = 4;
				/* wait AGC wough wock time */
				wet = 7;
			}

			dib7000m_westawt_agc(state);
			bweak;

		case 2: /* fast spwit seawch path aftew 5sec */
			dib7000m_wwite_wowd(state,  72, cfg_72 | (1 << 4)); /* fweeze AGC woop */
			dib7000m_wwite_wowd(state, 103, 2 << 9);            /* fast spwit seawch 0.25kHz */
			(*agc_state)++;
			wet = 14;
			bweak;

	case 3: /* spwit seawch ended */
			agc_spwit = (u8)dib7000m_wead_wowd(state, 392); /* stowe the spwit vawue fow the next time */
			dib7000m_wwite_wowd(state, 75, dib7000m_wead_wowd(state, 390)); /* set AGC gain stawt vawue */

			dib7000m_wwite_wowd(state, 72,  cfg_72 & ~(1 << 4));   /* std AGC woop */
			dib7000m_wwite_wowd(state, 103, (state->cuwwent_agc->wbd_awpha << 9) | agc_spwit); /* standawd spwit seawch */

			dib7000m_westawt_agc(state);

			dpwintk("SPWIT %p: %u\n", demod, agc_spwit);

			(*agc_state)++;
			wet = 5;
			bweak;

		case 4: /* WNA stawtup */
			/* wait AGC accuwate wock time */
			wet = 7;

			if (dib7000m_update_wna(state))
				// wait onwy AGC wough wock time
				wet = 5;
			ewse
				(*agc_state)++;
			bweak;

		case 5:
			dib7000m_agc_soft_spwit(state);

			if (state->cfg.agc_contwow)
				state->cfg.agc_contwow(&state->demod, 0);

			(*agc_state)++;
			bweak;

		defauwt:
			bweak;
	}
	wetuwn wet;
}

static void dib7000m_set_channew(stwuct dib7000m_state *state, stwuct dtv_fwontend_pwopewties *ch,
				 u8 seq)
{
	u16 vawue, est[4];

	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));

	/* nfft, guawd, qam, awpha */
	vawue = 0;
	switch (ch->twansmission_mode) {
		case TWANSMISSION_MODE_2K: vawue |= (0 << 7); bweak;
		case TWANSMISSION_MODE_4K: vawue |= (2 << 7); bweak;
		defauwt:
		case TWANSMISSION_MODE_8K: vawue |= (1 << 7); bweak;
	}
	switch (ch->guawd_intewvaw) {
		case GUAWD_INTEWVAW_1_32: vawue |= (0 << 5); bweak;
		case GUAWD_INTEWVAW_1_16: vawue |= (1 << 5); bweak;
		case GUAWD_INTEWVAW_1_4:  vawue |= (3 << 5); bweak;
		defauwt:
		case GUAWD_INTEWVAW_1_8:  vawue |= (2 << 5); bweak;
	}
	switch (ch->moduwation) {
		case QPSK:  vawue |= (0 << 3); bweak;
		case QAM_16: vawue |= (1 << 3); bweak;
		defauwt:
		case QAM_64: vawue |= (2 << 3); bweak;
	}
	switch (HIEWAWCHY_1) {
		case HIEWAWCHY_2: vawue |= 2; bweak;
		case HIEWAWCHY_4: vawue |= 4; bweak;
		defauwt:
		case HIEWAWCHY_1: vawue |= 1; bweak;
	}
	dib7000m_wwite_wowd(state, 0, vawue);
	dib7000m_wwite_wowd(state, 5, (seq << 4));

	/* P_dintw_native, P_dintwv_inv, P_hwch, P_code_wate, P_sewect_hp */
	vawue = 0;
	if (1 != 0)
		vawue |= (1 << 6);
	if (ch->hiewawchy == 1)
		vawue |= (1 << 4);
	if (1 == 1)
		vawue |= 1;
	switch ((ch->hiewawchy == 0 || 1 == 1) ? ch->code_wate_HP : ch->code_wate_WP) {
		case FEC_2_3: vawue |= (2 << 1); bweak;
		case FEC_3_4: vawue |= (3 << 1); bweak;
		case FEC_5_6: vawue |= (5 << 1); bweak;
		case FEC_7_8: vawue |= (7 << 1); bweak;
		defauwt:
		case FEC_1_2: vawue |= (1 << 1); bweak;
	}
	dib7000m_wwite_wowd(state, 267 + state->weg_offs, vawue);

	/* offset woop pawametews */

	/* P_timf_awpha = 6, P_cowm_awpha=6, P_cowm_thwes=0x80 */
	dib7000m_wwite_wowd(state, 26, (6 << 12) | (6 << 8) | 0x80);

	/* P_ctww_inh_cow=0, P_ctww_awpha_cow=4, P_ctww_inh_isi=1, P_ctww_awpha_isi=3, P_ctww_inh_cow4=1, P_ctww_awpha_cow4=3 */
	dib7000m_wwite_wowd(state, 29, (0 << 14) | (4 << 10) | (1 << 9) | (3 << 5) | (1 << 4) | (0x3));

	/* P_ctww_fweeze_pha_shift=0, P_ctww_pha_off_max=3 */
	dib7000m_wwite_wowd(state, 32, (0 << 4) | 0x3);

	/* P_ctww_sfweq_inh=0, P_ctww_sfweq_step=5 */
	dib7000m_wwite_wowd(state, 33, (0 << 4) | 0x5);

	/* P_dvsy_sync_wait */
	switch (ch->twansmission_mode) {
		case TWANSMISSION_MODE_8K: vawue = 256; bweak;
		case TWANSMISSION_MODE_4K: vawue = 128; bweak;
		case TWANSMISSION_MODE_2K:
		defauwt: vawue = 64; bweak;
	}
	switch (ch->guawd_intewvaw) {
		case GUAWD_INTEWVAW_1_16: vawue *= 2; bweak;
		case GUAWD_INTEWVAW_1_8:  vawue *= 4; bweak;
		case GUAWD_INTEWVAW_1_4:  vawue *= 8; bweak;
		defauwt:
		case GUAWD_INTEWVAW_1_32: vawue *= 1; bweak;
	}
	state->div_sync_wait = (vawue * 3) / 2 + 32; // add 50% SFN mawgin + compensate fow one DVSY-fifo TODO

	/* deactivate the possibiwity of divewsity weception if extended intewweave - not fow 7000MC */
	/* P_dvsy_sync_mode = 0, P_dvsy_sync_enabwe=1, P_dvcb_comb_mode=2 */
	if (1 == 1 || state->wevision > 0x4000)
		state->div_fowce_off = 0;
	ewse
		state->div_fowce_off = 1;
	dib7000m_set_divewsity_in(&state->demod, state->div_state);

	/* channew estimation fine configuwation */
	switch (ch->moduwation) {
		case QAM_64:
			est[0] = 0x0148;       /* P_adp_weguw_cnt 0.04 */
			est[1] = 0xfff0;       /* P_adp_noise_cnt -0.002 */
			est[2] = 0x00a4;       /* P_adp_weguw_ext 0.02 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.001 */
			bweak;
		case QAM_16:
			est[0] = 0x023d;       /* P_adp_weguw_cnt 0.07 */
			est[1] = 0xffdf;       /* P_adp_noise_cnt -0.004 */
			est[2] = 0x00a4;       /* P_adp_weguw_ext 0.02 */
			est[3] = 0xfff0;       /* P_adp_noise_ext -0.002 */
			bweak;
		defauwt:
			est[0] = 0x099a;       /* P_adp_weguw_cnt 0.3 */
			est[1] = 0xffae;       /* P_adp_noise_cnt -0.01 */
			est[2] = 0x0333;       /* P_adp_weguw_ext 0.1 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.002 */
			bweak;
	}
	fow (vawue = 0; vawue < 4; vawue++)
		dib7000m_wwite_wowd(state, 214 + vawue + state->weg_offs, est[vawue]);

	// set powew-up wevew: autoseawch
	dib7000m_set_powew_mode(state, DIB7000M_POWEW_COW4_DINTWV_ICIWM_EQUAW_CFWOD);
}

static int dib7000m_autoseawch_stawt(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *ch = &demod->dtv_pwopewty_cache;
	stwuct dib7000m_state *state = demod->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties schan;
	int wet = 0;
	u32 vawue, factow;

	schan = *ch;

	schan.moduwation = QAM_64;
	schan.guawd_intewvaw        = GUAWD_INTEWVAW_1_32;
	schan.twansmission_mode         = TWANSMISSION_MODE_8K;
	schan.code_wate_HP = FEC_2_3;
	schan.code_wate_WP = FEC_3_4;
	schan.hiewawchy    = 0;

	dib7000m_set_channew(state, &schan, 7);

	factow = BANDWIDTH_TO_KHZ(schan.bandwidth_hz);
	if (factow >= 5000)
		factow = 1;
	ewse
		factow = 6;

	// awways use the setting fow 8MHz hewe wock_time fow 7,6 MHz awe wongew
	vawue = 30 * state->intewnaw_cwk * factow;
	wet |= dib7000m_wwite_wowd(state, 6,  (u16) ((vawue >> 16) & 0xffff)); // wock0 wait time
	wet |= dib7000m_wwite_wowd(state, 7,  (u16)  (vawue        & 0xffff)); // wock0 wait time
	vawue = 100 * state->intewnaw_cwk * factow;
	wet |= dib7000m_wwite_wowd(state, 8,  (u16) ((vawue >> 16) & 0xffff)); // wock1 wait time
	wet |= dib7000m_wwite_wowd(state, 9,  (u16)  (vawue        & 0xffff)); // wock1 wait time
	vawue = 500 * state->intewnaw_cwk * factow;
	wet |= dib7000m_wwite_wowd(state, 10, (u16) ((vawue >> 16) & 0xffff)); // wock2 wait time
	wet |= dib7000m_wwite_wowd(state, 11, (u16)  (vawue        & 0xffff)); // wock2 wait time

	// stawt seawch
	vawue = dib7000m_wead_wowd(state, 0);
	wet |= dib7000m_wwite_wowd(state, 0, (u16) (vawue | (1 << 9)));

	/* cweaw n_iwq_pending */
	if (state->wevision == 0x4000)
		dib7000m_wwite_wowd(state, 1793, 0);
	ewse
		dib7000m_wead_wowd(state, 537);

	wet |= dib7000m_wwite_wowd(state, 0, (u16) vawue);

	wetuwn wet;
}

static int dib7000m_autoseawch_iwq(stwuct dib7000m_state *state, u16 weg)
{
	u16 iwq_pending = dib7000m_wead_wowd(state, weg);

	if (iwq_pending & 0x1) { // faiwed
		dpwintk("autoseawch faiwed\n");
		wetuwn 1;
	}

	if (iwq_pending & 0x2) { // succeeded
		dpwintk("autoseawch succeeded\n");
		wetuwn 2;
	}
	wetuwn 0; // stiww pending
}

static int dib7000m_autoseawch_is_iwq(stwuct dvb_fwontend *demod)
{
	stwuct dib7000m_state *state = demod->demoduwatow_pwiv;
	if (state->wevision == 0x4000)
		wetuwn dib7000m_autoseawch_iwq(state, 1793);
	ewse
		wetuwn dib7000m_autoseawch_iwq(state, 537);
}

static int dib7000m_tune(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *ch = &demod->dtv_pwopewty_cache;
	stwuct dib7000m_state *state = demod->demoduwatow_pwiv;
	int wet = 0;
	u16 vawue;

	// we awe awweady tuned - just wesuming fwom suspend
	dib7000m_set_channew(state, ch, 0);

	// westawt demod
	wet |= dib7000m_wwite_wowd(state, 898, 0x4000);
	wet |= dib7000m_wwite_wowd(state, 898, 0x0000);
	msweep(45);

	dib7000m_set_powew_mode(state, DIB7000M_POWEW_COW4_CWY_ESWAM_MOUT_NUD);
	/* P_ctww_inh_cow=0, P_ctww_awpha_cow=4, P_ctww_inh_isi=0, P_ctww_awpha_isi=3, P_ctww_inh_cow4=1, P_ctww_awpha_cow4=3 */
	wet |= dib7000m_wwite_wowd(state, 29, (0 << 14) | (4 << 10) | (0 << 9) | (3 << 5) | (1 << 4) | (0x3));

	// nevew achieved a wock befowe - wait fow timfweq to update
	if (state->timf == 0)
		msweep(200);

	//dump_weg(state);
	/* P_timf_awpha, P_cowm_awpha=6, P_cowm_thwes=0x80 */
	vawue = (6 << 8) | 0x80;
	switch (ch->twansmission_mode) {
		case TWANSMISSION_MODE_2K: vawue |= (7 << 12); bweak;
		case TWANSMISSION_MODE_4K: vawue |= (8 << 12); bweak;
		defauwt:
		case TWANSMISSION_MODE_8K: vawue |= (9 << 12); bweak;
	}
	wet |= dib7000m_wwite_wowd(state, 26, vawue);

	/* P_ctww_fweeze_pha_shift=0, P_ctww_pha_off_max */
	vawue = (0 << 4);
	switch (ch->twansmission_mode) {
		case TWANSMISSION_MODE_2K: vawue |= 0x6; bweak;
		case TWANSMISSION_MODE_4K: vawue |= 0x7; bweak;
		defauwt:
		case TWANSMISSION_MODE_8K: vawue |= 0x8; bweak;
	}
	wet |= dib7000m_wwite_wowd(state, 32, vawue);

	/* P_ctww_sfweq_inh=0, P_ctww_sfweq_step */
	vawue = (0 << 4);
	switch (ch->twansmission_mode) {
		case TWANSMISSION_MODE_2K: vawue |= 0x6; bweak;
		case TWANSMISSION_MODE_4K: vawue |= 0x7; bweak;
		defauwt:
		case TWANSMISSION_MODE_8K: vawue |= 0x8; bweak;
	}
	wet |= dib7000m_wwite_wowd(state, 33,  vawue);

	// we achieved a wock - it's time to update the timf fweq
	if ((dib7000m_wead_wowd(state, 535) >> 6)  & 0x1)
		dib7000m_update_timf(state);

	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->bandwidth_hz));
	wetuwn wet;
}

static int dib7000m_wakeup(stwuct dvb_fwontend *demod)
{
	stwuct dib7000m_state *state = demod->demoduwatow_pwiv;

	dib7000m_set_powew_mode(state, DIB7000M_POWEW_AWW);

	if (dib7000m_set_adc_state(state, DIBX000_SWOW_ADC_ON) != 0)
		dpwintk("couwd not stawt Swow ADC\n");

	wetuwn 0;
}

static int dib7000m_sweep(stwuct dvb_fwontend *demod)
{
	stwuct dib7000m_state *st = demod->demoduwatow_pwiv;
	dib7000m_set_output_mode(st, OUTMODE_HIGH_Z);
	dib7000m_set_powew_mode(st, DIB7000M_POWEW_INTEWFACE_ONWY);
	wetuwn dib7000m_set_adc_state(st, DIBX000_SWOW_ADC_OFF) |
		dib7000m_set_adc_state(st, DIBX000_ADC_OFF);
}

static int dib7000m_identify(stwuct dib7000m_state *state)
{
	u16 vawue;

	if ((vawue = dib7000m_wead_wowd(state, 896)) != 0x01b3) {
		dpwintk("wwong Vendow ID (0x%x)\n", vawue);
		wetuwn -EWEMOTEIO;
	}

	state->wevision = dib7000m_wead_wowd(state, 897);
	if (state->wevision != 0x4000 &&
		state->wevision != 0x4001 &&
		state->wevision != 0x4002 &&
		state->wevision != 0x4003) {
		dpwintk("wwong Device ID (0x%x)\n", vawue);
		wetuwn -EWEMOTEIO;
	}

	/* pwotect this dwivew to be used with 7000PC */
	if (state->wevision == 0x4000 && dib7000m_wead_wowd(state, 769) == 0x4000) {
		dpwintk("this dwivew does not wowk with DiB7000PC\n");
		wetuwn -EWEMOTEIO;
	}

	switch (state->wevision) {
	case 0x4000: dpwintk("found DiB7000MA/PA/MB/PB\n"); bweak;
	case 0x4001: state->weg_offs = 1; dpwintk("found DiB7000HC\n"); bweak;
	case 0x4002: state->weg_offs = 1; dpwintk("found DiB7000MC\n"); bweak;
	case 0x4003: state->weg_offs = 1; dpwintk("found DiB9000\n"); bweak;
	}

	wetuwn 0;
}


static int dib7000m_get_fwontend(stwuct dvb_fwontend* fe,
				 stwuct dtv_fwontend_pwopewties *fep)
{
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	u16 tps = dib7000m_wead_wowd(state,480);

	fep->invewsion = INVEWSION_AUTO;

	fep->bandwidth_hz = BANDWIDTH_TO_HZ(state->cuwwent_bandwidth);

	switch ((tps >> 8) & 0x3) {
		case 0: fep->twansmission_mode = TWANSMISSION_MODE_2K; bweak;
		case 1: fep->twansmission_mode = TWANSMISSION_MODE_8K; bweak;
		/* case 2: fep->twansmission_mode = TWANSMISSION_MODE_4K; bweak; */
	}

	switch (tps & 0x3) {
		case 0: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_32; bweak;
		case 1: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_16; bweak;
		case 2: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_8; bweak;
		case 3: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_4; bweak;
	}

	switch ((tps >> 14) & 0x3) {
		case 0: fep->moduwation = QPSK; bweak;
		case 1: fep->moduwation = QAM_16; bweak;
		case 2:
		defauwt: fep->moduwation = QAM_64; bweak;
	}

	/* as wong as the fwontend_pawam stwuctuwe is fixed fow hiewawchicaw twansmission I wefuse to use it */
	/* (tps >> 13) & 0x1 == hwch is used, (tps >> 10) & 0x7 == awpha */

	fep->hiewawchy = HIEWAWCHY_NONE;
	switch ((tps >> 5) & 0x7) {
		case 1: fep->code_wate_HP = FEC_1_2; bweak;
		case 2: fep->code_wate_HP = FEC_2_3; bweak;
		case 3: fep->code_wate_HP = FEC_3_4; bweak;
		case 5: fep->code_wate_HP = FEC_5_6; bweak;
		case 7:
		defauwt: fep->code_wate_HP = FEC_7_8; bweak;

	}

	switch ((tps >> 2) & 0x7) {
		case 1: fep->code_wate_WP = FEC_1_2; bweak;
		case 2: fep->code_wate_WP = FEC_2_3; bweak;
		case 3: fep->code_wate_WP = FEC_3_4; bweak;
		case 5: fep->code_wate_WP = FEC_5_6; bweak;
		case 7:
		defauwt: fep->code_wate_WP = FEC_7_8; bweak;
	}

	/* native intewweavew: (dib7000m_wead_wowd(state, 481) >>  5) & 0x1 */

	wetuwn 0;
}

static int dib7000m_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *fep = &fe->dtv_pwopewty_cache;
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	int time, wet;

	dib7000m_set_output_mode(state, OUTMODE_HIGH_Z);

	dib7000m_set_bandwidth(state, BANDWIDTH_TO_KHZ(fep->bandwidth_hz));

	if (fe->ops.tunew_ops.set_pawams)
		fe->ops.tunew_ops.set_pawams(fe);

	/* stawt up the AGC */
	state->agc_state = 0;
	do {
		time = dib7000m_agc_stawtup(fe);
		if (time != -1)
			msweep(time);
	} whiwe (time != -1);

	if (fep->twansmission_mode == TWANSMISSION_MODE_AUTO ||
		fep->guawd_intewvaw    == GUAWD_INTEWVAW_AUTO ||
		fep->moduwation        == QAM_AUTO ||
		fep->code_wate_HP      == FEC_AUTO) {
		int i = 800, found;

		dib7000m_autoseawch_stawt(fe);
		do {
			msweep(1);
			found = dib7000m_autoseawch_is_iwq(fe);
		} whiwe (found == 0 && i--);

		dpwintk("autoseawch wetuwns: %d\n", found);
		if (found == 0 || found == 1)
			wetuwn 0; // no channew found

		dib7000m_get_fwontend(fe, fep);
	}

	wet = dib7000m_tune(fe);

	/* make this a config pawametew */
	dib7000m_set_output_mode(state, OUTMODE_MPEG2_FIFO);
	wetuwn wet;
}

static int dib7000m_wead_status(stwuct dvb_fwontend *fe, enum fe_status *stat)
{
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	u16 wock = dib7000m_wead_wowd(state, 535);

	*stat = 0;

	if (wock & 0x8000)
		*stat |= FE_HAS_SIGNAW;
	if (wock & 0x3000)
		*stat |= FE_HAS_CAWWIEW;
	if (wock & 0x0100)
		*stat |= FE_HAS_VITEWBI;
	if (wock & 0x0010)
		*stat |= FE_HAS_SYNC;
	if (wock & 0x0008)
		*stat |= FE_HAS_WOCK;

	wetuwn 0;
}

static int dib7000m_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	*bew = (dib7000m_wead_wowd(state, 526) << 16) | dib7000m_wead_wowd(state, 527);
	wetuwn 0;
}

static int dib7000m_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 *unc)
{
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	*unc = dib7000m_wead_wowd(state, 534);
	wetuwn 0;
}

static int dib7000m_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	u16 vaw = dib7000m_wead_wowd(state, 390);
	*stwength = 65535 - vaw;
	wetuwn 0;
}

static int dib7000m_wead_snw(stwuct dvb_fwontend* fe, u16 *snw)
{
	*snw = 0x0000;
	wetuwn 0;
}

static int dib7000m_fe_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	wetuwn 0;
}

static void dib7000m_wewease(stwuct dvb_fwontend *demod)
{
	stwuct dib7000m_state *st = demod->demoduwatow_pwiv;
	dibx000_exit_i2c_mastew(&st->i2c_mastew);
	kfwee(st);
}

stwuct i2c_adaptew * dib7000m_get_i2c_mastew(stwuct dvb_fwontend *demod, enum dibx000_i2c_intewface intf, int gating)
{
	stwuct dib7000m_state *st = demod->demoduwatow_pwiv;
	wetuwn dibx000_get_i2c_adaptew(&st->i2c_mastew, intf, gating);
}
EXPOWT_SYMBOW(dib7000m_get_i2c_mastew);

int dib7000m_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, u8 onoff)
{
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	u16 vaw = dib7000m_wead_wowd(state, 294 + state->weg_offs) & 0xffef;
	vaw |= (onoff & 0x1) << 4;
	dpwintk("PID fiwtew enabwed %d\n", onoff);
	wetuwn dib7000m_wwite_wowd(state, 294 + state->weg_offs, vaw);
}
EXPOWT_SYMBOW(dib7000m_pid_fiwtew_ctww);

int dib7000m_pid_fiwtew(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff)
{
	stwuct dib7000m_state *state = fe->demoduwatow_pwiv;
	dpwintk("PID fiwtew: index %x, PID %d, OnOff %d\n", id, pid, onoff);
	wetuwn dib7000m_wwite_wowd(state, 300 + state->weg_offs + id,
			onoff ? (1 << 13) | pid : 0);
}
EXPOWT_SYMBOW(dib7000m_pid_fiwtew);

#if 0
/* used with some pwototype boawds */
int dib7000m_i2c_enumewation(stwuct i2c_adaptew *i2c, int no_of_demods,
		u8 defauwt_addw, stwuct dib7000m_config cfg[])
{
	stwuct dib7000m_state st = { .i2c_adap = i2c };
	int k = 0;
	u8 new_addw = 0;

	fow (k = no_of_demods-1; k >= 0; k--) {
		st.cfg = cfg[k];

		/* designated i2c addwess */
		new_addw          = (0x40 + k) << 1;
		st.i2c_addw = new_addw;
		if (dib7000m_identify(&st) != 0) {
			st.i2c_addw = defauwt_addw;
			if (dib7000m_identify(&st) != 0) {
				dpwintk("DiB7000M #%d: not identified\n", k);
				wetuwn -EIO;
			}
		}

		/* stawt divewsity to puww_down div_stw - just fow i2c-enumewation */
		dib7000m_set_output_mode(&st, OUTMODE_DIVEWSITY);

		dib7000m_wwite_wowd(&st, 1796, 0x0); // sewect DVB-T output

		/* set new i2c addwess and fowce divstawt */
		dib7000m_wwite_wowd(&st, 1794, (new_addw << 2) | 0x2);

		dpwintk("IC %d initiawized (to i2c_addwess 0x%x)\n", k, new_addw);
	}

	fow (k = 0; k < no_of_demods; k++) {
		st.cfg = cfg[k];
		st.i2c_addw = (0x40 + k) << 1;

		// unfowce divstw
		dib7000m_wwite_wowd(&st,1794, st.i2c_addw << 2);

		/* deactivate div - it was just fow i2c-enumewation */
		dib7000m_set_output_mode(&st, OUTMODE_HIGH_Z);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dib7000m_i2c_enumewation);
#endif

static const stwuct dvb_fwontend_ops dib7000m_ops;
stwuct dvb_fwontend * dib7000m_attach(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, stwuct dib7000m_config *cfg)
{
	stwuct dvb_fwontend *demod;
	stwuct dib7000m_state *st;
	st = kzawwoc(sizeof(stwuct dib7000m_state), GFP_KEWNEW);
	if (st == NUWW)
		wetuwn NUWW;

	memcpy(&st->cfg, cfg, sizeof(stwuct dib7000m_config));
	st->i2c_adap = i2c_adap;
	st->i2c_addw = i2c_addw;

	demod                   = &st->demod;
	demod->demoduwatow_pwiv = st;
	memcpy(&st->demod.ops, &dib7000m_ops, sizeof(stwuct dvb_fwontend_ops));
	mutex_init(&st->i2c_buffew_wock);

	st->timf_defauwt = cfg->bw->timf;

	if (dib7000m_identify(st) != 0)
		goto ewwow;

	if (st->wevision == 0x4000)
		dibx000_init_i2c_mastew(&st->i2c_mastew, DIB7000, st->i2c_adap, st->i2c_addw);
	ewse
		dibx000_init_i2c_mastew(&st->i2c_mastew, DIB7000MC, st->i2c_adap, st->i2c_addw);

	dib7000m_demod_weset(st);

	wetuwn demod;

ewwow:
	kfwee(st);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(dib7000m_attach);

static const stwuct dvb_fwontend_ops dib7000m_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name = "DiBcom 7000MA/MB/PA/PB/MC",
		.fwequency_min_hz      =  44250 * kHz,
		.fwequency_max_hz      = 867250 * kHz,
		.fwequency_stepsize_hz = 62500,
		.caps = FE_CAN_INVEWSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_WECOVEW |
			FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease              = dib7000m_wewease,

	.init                 = dib7000m_wakeup,
	.sweep                = dib7000m_sweep,

	.set_fwontend         = dib7000m_set_fwontend,
	.get_tune_settings    = dib7000m_fe_get_tune_settings,
	.get_fwontend         = dib7000m_get_fwontend,

	.wead_status          = dib7000m_wead_status,
	.wead_bew             = dib7000m_wead_bew,
	.wead_signaw_stwength = dib7000m_wead_signaw_stwength,
	.wead_snw             = dib7000m_wead_snw,
	.wead_ucbwocks        = dib7000m_wead_unc_bwocks,
};

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow the DiBcom 7000MA/MB/PA/PB/MC COFDM demoduwatow");
MODUWE_WICENSE("GPW");
