// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux-DVB Dwivew fow DiBcom's DiB8000 chip (ISDB-T).
 *
 * Copywight (C) 2009 DiBcom (http://www.dibcom.fw/)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <asm/div64.h>

#incwude <winux/int_wog.h>

#incwude <media/dvb_fwontend.h>

#incwude "dib8000.h"

#define WAYEW_AWW -1
#define WAYEW_A   1
#define WAYEW_B   2
#define WAYEW_C   3

#define MAX_NUMBEW_OF_FWONTENDS 6
/* #define DIB8000_AGC_FWEEZE */

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "tuwn on debugging (defauwt: 0)");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

stwuct i2c_device {
	stwuct i2c_adaptew *adap;
	u8 addw;
	u8 *i2c_wwite_buffew;
	u8 *i2c_wead_buffew;
	stwuct mutex *i2c_buffew_wock;
};

enum pawam_woop_step {
	WOOP_TUNE_1,
	WOOP_TUNE_2
};

enum dib8000_autoseawch_step {
	AS_STAWT = 0,
	AS_SEAWCHING_FFT,
	AS_SEAWCHING_GUAWD,
	AS_DONE = 100,
};

enum timeout_mode {
	SYMBOW_DEPENDENT_OFF = 0,
	SYMBOW_DEPENDENT_ON,
};

stwuct dib8000_state {
	stwuct dib8000_config cfg;

	stwuct i2c_device i2c;

	stwuct dibx000_i2c_mastew i2c_mastew;

	u16 wbd_wef;

	u8 cuwwent_band;
	u32 cuwwent_bandwidth;
	stwuct dibx000_agc_config *cuwwent_agc;
	u32 timf;
	u32 timf_defauwt;

	u8 div_fowce_off:1;
	u8 div_state:1;
	u16 div_sync_wait;

	u8 agc_state;
	u8 diffewentiaw_constewwation;
	u8 divewsity_onoff;

	s16 bew_monitowed_wayew;
	u16 gpio_diw;
	u16 gpio_vaw;

	u16 wevision;
	u8 isdbt_cfg_woaded;
	enum fwontend_tune_state tune_state;
	s32 status;

	stwuct dvb_fwontend *fe[MAX_NUMBEW_OF_FWONTENDS];

	/* fow the I2C twansfew */
	stwuct i2c_msg msg[2];
	u8 i2c_wwite_buffew[4];
	u8 i2c_wead_buffew[2];
	stwuct mutex i2c_buffew_wock;
	u8 input_mode_mpeg;

	u16 tunew_enabwe;
	stwuct i2c_adaptew dib8096p_tunew_adap;
	u16 cuwwent_demod_bw;

	u16 seg_mask;
	u16 seg_diff_mask;
	u16 mode;
	u8 wayew_b_nb_seg;
	u8 wayew_c_nb_seg;

	u8 channew_pawametews_set;
	u16 autoseawch_state;
	u16 found_nfft;
	u16 found_guawd;
	u8 subchannew;
	u8 symbow_duwation;
	unsigned wong timeout;
	u8 wongest_intwv_wayew;
	u16 output_mode;

	/* fow DVBv5 stats */
	s64 init_ucb;
	unsigned wong pew_jiffies_stats;
	unsigned wong bew_jiffies_stats;
	unsigned wong bew_jiffies_stats_wayew[3];

#ifdef DIB8000_AGC_FWEEZE
	u16 agc1_max;
	u16 agc1_min;
	u16 agc2_max;
	u16 agc2_min;
#endif
};

enum dib8000_powew_mode {
	DIB8000_POWEW_AWW = 0,
	DIB8000_POWEW_INTEWFACE_ONWY,
};

static u16 dib8000_i2c_wead16(stwuct i2c_device *i2c, u16 weg)
{
	u16 wet;
	stwuct i2c_msg msg[2] = {
		{.addw = i2c->addw >> 1, .fwags = 0, .wen = 2},
		{.addw = i2c->addw >> 1, .fwags = I2C_M_WD, .wen = 2},
	};

	if (mutex_wock_intewwuptibwe(i2c->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	msg[0].buf    = i2c->i2c_wwite_buffew;
	msg[0].buf[0] = weg >> 8;
	msg[0].buf[1] = weg & 0xff;
	msg[1].buf    = i2c->i2c_wead_buffew;

	if (i2c_twansfew(i2c->adap, msg, 2) != 2)
		dpwintk("i2c wead ewwow on %d\n", weg);

	wet = (msg[1].buf[0] << 8) | msg[1].buf[1];
	mutex_unwock(i2c->i2c_buffew_wock);
	wetuwn wet;
}

static u16 __dib8000_wead_wowd(stwuct dib8000_state *state, u16 weg)
{
	u16 wet;

	state->i2c_wwite_buffew[0] = weg >> 8;
	state->i2c_wwite_buffew[1] = weg & 0xff;

	memset(state->msg, 0, 2 * sizeof(stwuct i2c_msg));
	state->msg[0].addw = state->i2c.addw >> 1;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 2;
	state->msg[1].addw = state->i2c.addw >> 1;
	state->msg[1].fwags = I2C_M_WD;
	state->msg[1].buf = state->i2c_wead_buffew;
	state->msg[1].wen = 2;

	if (i2c_twansfew(state->i2c.adap, state->msg, 2) != 2)
		dpwintk("i2c wead ewwow on %d\n", weg);

	wet = (state->i2c_wead_buffew[0] << 8) | state->i2c_wead_buffew[1];

	wetuwn wet;
}

static u16 dib8000_wead_wowd(stwuct dib8000_state *state, u16 weg)
{
	u16 wet;

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	wet = __dib8000_wead_wowd(state, weg);

	mutex_unwock(&state->i2c_buffew_wock);

	wetuwn wet;
}

static u32 dib8000_wead32(stwuct dib8000_state *state, u16 weg)
{
	u16 ww[2];

	if (mutex_wock_intewwuptibwe(&state->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn 0;
	}

	ww[0] = __dib8000_wead_wowd(state, weg + 0);
	ww[1] = __dib8000_wead_wowd(state, weg + 1);

	mutex_unwock(&state->i2c_buffew_wock);

	wetuwn ((ww[0] << 16) | (ww[1]));
}

static int dib8000_i2c_wwite16(stwuct i2c_device *i2c, u16 weg, u16 vaw)
{
	stwuct i2c_msg msg = {.addw = i2c->addw >> 1, .fwags = 0, .wen = 4};
	int wet = 0;

	if (mutex_wock_intewwuptibwe(i2c->i2c_buffew_wock) < 0) {
		dpwintk("couwd not acquiwe wock\n");
		wetuwn -EINVAW;
	}

	msg.buf    = i2c->i2c_wwite_buffew;
	msg.buf[0] = (weg >> 8) & 0xff;
	msg.buf[1] = weg & 0xff;
	msg.buf[2] = (vaw >> 8) & 0xff;
	msg.buf[3] = vaw & 0xff;

	wet = i2c_twansfew(i2c->adap, &msg, 1) != 1 ? -EWEMOTEIO : 0;
	mutex_unwock(i2c->i2c_buffew_wock);

	wetuwn wet;
}

static int dib8000_wwite_wowd(stwuct dib8000_state *state, u16 weg, u16 vaw)
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
	state->msg[0].addw = state->i2c.addw >> 1;
	state->msg[0].fwags = 0;
	state->msg[0].buf = state->i2c_wwite_buffew;
	state->msg[0].wen = 4;

	wet = (i2c_twansfew(state->i2c.adap, state->msg, 1) != 1 ?
			-EWEMOTEIO : 0);
	mutex_unwock(&state->i2c_buffew_wock);

	wetuwn wet;
}

static const s16 coeff_2k_sb_1seg_dqpsk[8] = {
	(769 << 5) | 0x0a, (745 << 5) | 0x03, (595 << 5) | 0x0d, (769 << 5) | 0x0a, (920 << 5) | 0x09, (784 << 5) | 0x02, (519 << 5) | 0x0c,
		(920 << 5) | 0x09
};

static const s16 coeff_2k_sb_1seg[8] = {
	(692 << 5) | 0x0b, (683 << 5) | 0x01, (519 << 5) | 0x09, (692 << 5) | 0x0b, 0 | 0x1f, 0 | 0x1f, 0 | 0x1f, 0 | 0x1f
};

static const s16 coeff_2k_sb_3seg_0dqpsk_1dqpsk[8] = {
	(832 << 5) | 0x10, (912 << 5) | 0x05, (900 << 5) | 0x12, (832 << 5) | 0x10, (-931 << 5) | 0x0f, (912 << 5) | 0x04, (807 << 5) | 0x11,
		(-931 << 5) | 0x0f
};

static const s16 coeff_2k_sb_3seg_0dqpsk[8] = {
	(622 << 5) | 0x0c, (941 << 5) | 0x04, (796 << 5) | 0x10, (622 << 5) | 0x0c, (982 << 5) | 0x0c, (519 << 5) | 0x02, (572 << 5) | 0x0e,
		(982 << 5) | 0x0c
};

static const s16 coeff_2k_sb_3seg_1dqpsk[8] = {
	(699 << 5) | 0x14, (607 << 5) | 0x04, (944 << 5) | 0x13, (699 << 5) | 0x14, (-720 << 5) | 0x0d, (640 << 5) | 0x03, (866 << 5) | 0x12,
		(-720 << 5) | 0x0d
};

static const s16 coeff_2k_sb_3seg[8] = {
	(664 << 5) | 0x0c, (925 << 5) | 0x03, (937 << 5) | 0x10, (664 << 5) | 0x0c, (-610 << 5) | 0x0a, (697 << 5) | 0x01, (836 << 5) | 0x0e,
		(-610 << 5) | 0x0a
};

static const s16 coeff_4k_sb_1seg_dqpsk[8] = {
	(-955 << 5) | 0x0e, (687 << 5) | 0x04, (818 << 5) | 0x10, (-955 << 5) | 0x0e, (-922 << 5) | 0x0d, (750 << 5) | 0x03, (665 << 5) | 0x0f,
		(-922 << 5) | 0x0d
};

static const s16 coeff_4k_sb_1seg[8] = {
	(638 << 5) | 0x0d, (683 << 5) | 0x02, (638 << 5) | 0x0d, (638 << 5) | 0x0d, (-655 << 5) | 0x0a, (517 << 5) | 0x00, (698 << 5) | 0x0d,
		(-655 << 5) | 0x0a
};

static const s16 coeff_4k_sb_3seg_0dqpsk_1dqpsk[8] = {
	(-707 << 5) | 0x14, (910 << 5) | 0x06, (889 << 5) | 0x16, (-707 << 5) | 0x14, (-958 << 5) | 0x13, (993 << 5) | 0x05, (523 << 5) | 0x14,
		(-958 << 5) | 0x13
};

static const s16 coeff_4k_sb_3seg_0dqpsk[8] = {
	(-723 << 5) | 0x13, (910 << 5) | 0x05, (777 << 5) | 0x14, (-723 << 5) | 0x13, (-568 << 5) | 0x0f, (547 << 5) | 0x03, (696 << 5) | 0x12,
		(-568 << 5) | 0x0f
};

static const s16 coeff_4k_sb_3seg_1dqpsk[8] = {
	(-940 << 5) | 0x15, (607 << 5) | 0x05, (915 << 5) | 0x16, (-940 << 5) | 0x15, (-848 << 5) | 0x13, (683 << 5) | 0x04, (543 << 5) | 0x14,
		(-848 << 5) | 0x13
};

static const s16 coeff_4k_sb_3seg[8] = {
	(612 << 5) | 0x12, (910 << 5) | 0x04, (864 << 5) | 0x14, (612 << 5) | 0x12, (-869 << 5) | 0x13, (683 << 5) | 0x02, (869 << 5) | 0x12,
		(-869 << 5) | 0x13
};

static const s16 coeff_8k_sb_1seg_dqpsk[8] = {
	(-835 << 5) | 0x12, (684 << 5) | 0x05, (735 << 5) | 0x14, (-835 << 5) | 0x12, (-598 << 5) | 0x10, (781 << 5) | 0x04, (739 << 5) | 0x13,
		(-598 << 5) | 0x10
};

static const s16 coeff_8k_sb_1seg[8] = {
	(673 << 5) | 0x0f, (683 << 5) | 0x03, (808 << 5) | 0x12, (673 << 5) | 0x0f, (585 << 5) | 0x0f, (512 << 5) | 0x01, (780 << 5) | 0x0f,
		(585 << 5) | 0x0f
};

static const s16 coeff_8k_sb_3seg_0dqpsk_1dqpsk[8] = {
	(863 << 5) | 0x17, (930 << 5) | 0x07, (878 << 5) | 0x19, (863 << 5) | 0x17, (0 << 5) | 0x14, (521 << 5) | 0x05, (980 << 5) | 0x18,
		(0 << 5) | 0x14
};

static const s16 coeff_8k_sb_3seg_0dqpsk[8] = {
	(-924 << 5) | 0x17, (910 << 5) | 0x06, (774 << 5) | 0x17, (-924 << 5) | 0x17, (-877 << 5) | 0x15, (565 << 5) | 0x04, (553 << 5) | 0x15,
		(-877 << 5) | 0x15
};

static const s16 coeff_8k_sb_3seg_1dqpsk[8] = {
	(-921 << 5) | 0x19, (607 << 5) | 0x06, (881 << 5) | 0x19, (-921 << 5) | 0x19, (-921 << 5) | 0x14, (713 << 5) | 0x05, (1018 << 5) | 0x18,
		(-921 << 5) | 0x14
};

static const s16 coeff_8k_sb_3seg[8] = {
	(514 << 5) | 0x14, (910 << 5) | 0x05, (861 << 5) | 0x17, (514 << 5) | 0x14, (690 << 5) | 0x14, (683 << 5) | 0x03, (662 << 5) | 0x15,
		(690 << 5) | 0x14
};

static const s16 ana_fe_coeff_3seg[24] = {
	81, 80, 78, 74, 68, 61, 54, 45, 37, 28, 19, 11, 4, 1022, 1017, 1013, 1010, 1008, 1008, 1008, 1008, 1010, 1014, 1017
};

static const s16 ana_fe_coeff_1seg[24] = {
	249, 226, 164, 82, 5, 981, 970, 988, 1018, 20, 31, 26, 8, 1012, 1000, 1018, 1012, 8, 15, 14, 9, 3, 1017, 1003
};

static const s16 ana_fe_coeff_13seg[24] = {
	396, 305, 105, -51, -77, -12, 41, 31, -11, -30, -11, 14, 15, -2, -13, -7, 5, 8, 1, -6, -7, -3, 0, 1
};

static u16 fft_to_mode(stwuct dib8000_state *state)
{
	u16 mode;
	switch (state->fe[0]->dtv_pwopewty_cache.twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		mode = 1;
		bweak;
	case TWANSMISSION_MODE_4K:
		mode = 2;
		bweak;
	defauwt:
	case TWANSMISSION_MODE_AUTO:
	case TWANSMISSION_MODE_8K:
		mode = 3;
		bweak;
	}
	wetuwn mode;
}

static void dib8000_set_acquisition_mode(stwuct dib8000_state *state)
{
	u16 nud = dib8000_wead_wowd(state, 298);
	nud |= (1 << 3) | (1 << 0);
	dpwintk("acquisition mode activated\n");
	dib8000_wwite_wowd(state, 298, nud);
}
static int dib8000_set_output_mode(stwuct dvb_fwontend *fe, int mode)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 outweg, fifo_thweshowd, smo_mode, swam = 0x0205;	/* by defauwt SDWAM deintwv is enabwed */

	state->output_mode = mode;
	outweg = 0;
	fifo_thweshowd = 1792;
	smo_mode = (dib8000_wead_wowd(state, 299) & 0x0050) | (1 << 1);

	dpwintk("-I-	Setting output mode fow demod %p to %d\n",
			&state->fe[0], mode);

	switch (mode) {
	case OUTMODE_MPEG2_PAW_GATED_CWK:	// STBs with pawawwew gated cwock
		outweg = (1 << 10);	/* 0x0400 */
		bweak;
	case OUTMODE_MPEG2_PAW_CONT_CWK:	// STBs with pawawwew continues cwock
		outweg = (1 << 10) | (1 << 6);	/* 0x0440 */
		bweak;
	case OUTMODE_MPEG2_SEWIAW:	// STBs with sewiaw input
		outweg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0482 */
		bweak;
	case OUTMODE_DIVEWSITY:
		if (state->cfg.hostbus_divewsity) {
			outweg = (1 << 10) | (4 << 6);	/* 0x0500 */
			swam &= 0xfdff;
		} ewse
			swam |= 0x0c00;
		bweak;
	case OUTMODE_MPEG2_FIFO:	// e.g. USB feeding
		smo_mode |= (3 << 1);
		fifo_thweshowd = 512;
		outweg = (1 << 10) | (5 << 6);
		bweak;
	case OUTMODE_HIGH_Z:	// disabwe
		outweg = 0;
		bweak;

	case OUTMODE_ANAWOG_ADC:
		outweg = (1 << 10) | (3 << 6);
		dib8000_set_acquisition_mode(state);
		bweak;

	defauwt:
		dpwintk("Unhandwed output_mode passed to be set fow demod %p\n",
				&state->fe[0]);
		wetuwn -EINVAW;
	}

	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	dib8000_wwite_wowd(state, 299, smo_mode);
	dib8000_wwite_wowd(state, 300, fifo_thweshowd);	/* synchwonous fwead */
	dib8000_wwite_wowd(state, 1286, outweg);
	dib8000_wwite_wowd(state, 1291, swam);

	wetuwn 0;
}

static int dib8000_set_divewsity_in(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 tmp, sync_wait = dib8000_wead_wowd(state, 273) & 0xfff0;

	dpwintk("set divewsity input to %i\n", onoff);
	if (!state->diffewentiaw_constewwation) {
		dib8000_wwite_wowd(state, 272, 1 << 9);	//dvsy_off_wmod4 = 1
		dib8000_wwite_wowd(state, 273, sync_wait | (1 << 2) | 2);	// sync_enabwe = 1; comb_mode = 2
	} ewse {
		dib8000_wwite_wowd(state, 272, 0);	//dvsy_off_wmod4 = 0
		dib8000_wwite_wowd(state, 273, sync_wait);	// sync_enabwe = 0; comb_mode = 0
	}
	state->divewsity_onoff = onoff;

	switch (onoff) {
	case 0:		/* onwy use the intewnaw way - not the divewsity input */
		dib8000_wwite_wowd(state, 270, 1);
		dib8000_wwite_wowd(state, 271, 0);
		bweak;
	case 1:		/* both ways */
		dib8000_wwite_wowd(state, 270, 6);
		dib8000_wwite_wowd(state, 271, 6);
		bweak;
	case 2:		/* onwy the divewsity input */
		dib8000_wwite_wowd(state, 270, 0);
		dib8000_wwite_wowd(state, 271, 1);
		bweak;
	}

	if (state->wevision == 0x8002) {
		tmp = dib8000_wead_wowd(state, 903);
		dib8000_wwite_wowd(state, 903, tmp & ~(1 << 3));
		msweep(30);
		dib8000_wwite_wowd(state, 903, tmp | (1 << 3));
	}
	wetuwn 0;
}

static void dib8000_set_powew_mode(stwuct dib8000_state *state, enum dib8000_powew_mode mode)
{
	/* by defauwt evewything is going to be powewed off */
	u16 weg_774 = 0x3fff, weg_775 = 0xffff, weg_776 = 0xffff,
		weg_900 = (dib8000_wead_wowd(state, 900) & 0xfffc) | 0x3,
		weg_1280;

	if (state->wevision != 0x8090)
		weg_1280 = (dib8000_wead_wowd(state, 1280) & 0x00ff) | 0xff00;
	ewse
		weg_1280 = (dib8000_wead_wowd(state, 1280) & 0x707f) | 0x8f80;

	/* now, depending on the wequested mode, we powew on */
	switch (mode) {
		/* powew up evewything in the demod */
	case DIB8000_POWEW_AWW:
		weg_774 = 0x0000;
		weg_775 = 0x0000;
		weg_776 = 0x0000;
		weg_900 &= 0xfffc;
		if (state->wevision != 0x8090)
			weg_1280 &= 0x00ff;
		ewse
			weg_1280 &= 0x707f;
		bweak;
	case DIB8000_POWEW_INTEWFACE_ONWY:
		if (state->wevision != 0x8090)
			weg_1280 &= 0x00ff;
		ewse
			weg_1280 &= 0xfa7b;
		bweak;
	}

	dpwintk("powewmode : 774 : %x ; 775 : %x; 776 : %x ; 900 : %x; 1280 : %x\n", weg_774, weg_775, weg_776, weg_900, weg_1280);
	dib8000_wwite_wowd(state, 774, weg_774);
	dib8000_wwite_wowd(state, 775, weg_775);
	dib8000_wwite_wowd(state, 776, weg_776);
	dib8000_wwite_wowd(state, 900, weg_900);
	dib8000_wwite_wowd(state, 1280, weg_1280);
}

static int dib8000_set_adc_state(stwuct dib8000_state *state, enum dibx000_adc_states no)
{
	int wet = 0;
	u16 weg, weg_907 = dib8000_wead_wowd(state, 907);
	u16 weg_908 = dib8000_wead_wowd(state, 908);

	switch (no) {
	case DIBX000_SWOW_ADC_ON:
		if (state->wevision != 0x8090) {
			weg_908 |= (1 << 1) | (1 << 0);
			wet |= dib8000_wwite_wowd(state, 908, weg_908);
			weg_908 &= ~(1 << 1);
		} ewse {
			weg = dib8000_wead_wowd(state, 1925);
			/* en_swowAdc = 1 & weset_swadc = 1 */
			dib8000_wwite_wowd(state, 1925, weg |
					(1<<4) | (1<<2));

			/* wead access to make it wowks... stwange ... */
			weg = dib8000_wead_wowd(state, 1925);
			msweep(20);
			/* en_swowAdc = 1 & weset_swadc = 0 */
			dib8000_wwite_wowd(state, 1925, weg & ~(1<<4));

			weg = dib8000_wead_wowd(state, 921) & ~((0x3 << 14)
					| (0x3 << 12));
			/* wef = Vin1 => Vbg ; sew = Vin0 ow Vin3 ;
			   (Vin2 = Vcm) */
			dib8000_wwite_wowd(state, 921, weg | (1 << 14)
					| (3 << 12));
		}
		bweak;

	case DIBX000_SWOW_ADC_OFF:
		if (state->wevision == 0x8090) {
			weg = dib8000_wead_wowd(state, 1925);
			/* weset_swadc = 1 en_swowAdc = 0 */
			dib8000_wwite_wowd(state, 1925,
					(weg & ~(1<<2)) | (1<<4));
		}
		weg_908 |= (1 << 1) | (1 << 0);
		bweak;

	case DIBX000_ADC_ON:
		weg_907 &= 0x0fff;
		weg_908 &= 0x0003;
		bweak;

	case DIBX000_ADC_OFF:	// weave the VBG vowtage on
		weg_907 = (1 << 13) | (1 << 12);
		weg_908 = (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 1);
		bweak;

	case DIBX000_VBG_ENABWE:
		weg_907 &= ~(1 << 15);
		bweak;

	case DIBX000_VBG_DISABWE:
		weg_907 |= (1 << 15);
		bweak;

	defauwt:
		bweak;
	}

	wet |= dib8000_wwite_wowd(state, 907, weg_907);
	wet |= dib8000_wwite_wowd(state, 908, weg_908);

	wetuwn wet;
}

static int dib8000_set_bandwidth(stwuct dvb_fwontend *fe, u32 bw)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u32 timf;

	if (bw == 0)
		bw = 6000;

	if (state->timf == 0) {
		dpwintk("using defauwt timf\n");
		timf = state->timf_defauwt;
	} ewse {
		dpwintk("using updated timf\n");
		timf = state->timf;
	}

	dib8000_wwite_wowd(state, 29, (u16) ((timf >> 16) & 0xffff));
	dib8000_wwite_wowd(state, 30, (u16) ((timf) & 0xffff));

	wetuwn 0;
}

static int dib8000_sad_cawib(stwuct dib8000_state *state)
{
	u8 sad_sew = 3;

	if (state->wevision == 0x8090) {
		dib8000_wwite_wowd(state, 922, (sad_sew << 2));
		dib8000_wwite_wowd(state, 923, 2048);

		dib8000_wwite_wowd(state, 922, (sad_sew << 2) | 0x1);
		dib8000_wwite_wowd(state, 922, (sad_sew << 2));
	} ewse {
		/* intewnaw */
		dib8000_wwite_wowd(state, 923, (0 << 1) | (0 << 0));
		dib8000_wwite_wowd(state, 924, 776);

		/* do the cawibwation */
		dib8000_wwite_wowd(state, 923, (1 << 0));
		dib8000_wwite_wowd(state, 923, (0 << 0));
	}

	msweep(1);
	wetuwn 0;
}

static int dib8000_set_wbd_wef(stwuct dvb_fwontend *fe, u16 vawue)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	if (vawue > 4095)
		vawue = 4095;
	state->wbd_wef = vawue;
	wetuwn dib8000_wwite_wowd(state, 106, vawue);
}

static void dib8000_weset_pww_common(stwuct dib8000_state *state, const stwuct dibx000_bandwidth_config *bw)
{
	dpwintk("ifweq: %d %x, invewsion: %d\n", bw->ifweq, bw->ifweq, bw->ifweq >> 25);
	if (state->wevision != 0x8090) {
		dib8000_wwite_wowd(state, 23,
				(u16) (((bw->intewnaw * 1000) >> 16) & 0xffff));
		dib8000_wwite_wowd(state, 24,
				(u16) ((bw->intewnaw * 1000) & 0xffff));
	} ewse {
		dib8000_wwite_wowd(state, 23, (u16) (((bw->intewnaw / 2 * 1000) >> 16) & 0xffff));
		dib8000_wwite_wowd(state, 24,
				(u16) ((bw->intewnaw  / 2 * 1000) & 0xffff));
	}
	dib8000_wwite_wowd(state, 27, (u16) ((bw->ifweq >> 16) & 0x01ff));
	dib8000_wwite_wowd(state, 28, (u16) (bw->ifweq & 0xffff));
	dib8000_wwite_wowd(state, 26, (u16) ((bw->ifweq >> 25) & 0x0003));

	if (state->wevision != 0x8090)
		dib8000_wwite_wowd(state, 922, bw->sad_cfg);
}

static void dib8000_weset_pww(stwuct dib8000_state *state)
{
	const stwuct dibx000_bandwidth_config *pww = state->cfg.pww;
	u16 cwk_cfg1, weg;

	if (state->wevision != 0x8090) {
		dib8000_wwite_wowd(state, 901,
				(pww->pww_pwediv << 8) | (pww->pww_watio << 0));

		cwk_cfg1 = (1 << 10) | (0 << 9) | (pww->IO_CWK_en_cowe << 8) |
			(pww->bypcwk_div << 5) | (pww->enabwe_wefdiv << 4) |
			(1 << 3) | (pww->pww_wange << 1) |
			(pww->pww_weset << 0);

		dib8000_wwite_wowd(state, 902, cwk_cfg1);
		cwk_cfg1 = (cwk_cfg1 & 0xfff7) | (pww->pww_bypass << 3);
		dib8000_wwite_wowd(state, 902, cwk_cfg1);

		dpwintk("cwk_cfg1: 0x%04x\n", cwk_cfg1);

		/* smpw_cfg: P_wefcwksew=2, P_ensmpwsew=1 nodivsmpw=1 */
		if (state->cfg.pww->ADCwkSwc == 0)
			dib8000_wwite_wowd(state, 904,
					(0 << 15) | (0 << 12) | (0 << 10) |
					(pww->moduwo << 8) |
					(pww->ADCwkSwc << 7) | (0 << 1));
		ewse if (state->cfg.wefcwksew != 0)
			dib8000_wwite_wowd(state, 904, (0 << 15) | (1 << 12) |
					((state->cfg.wefcwksew & 0x3) << 10) |
					(pww->moduwo << 8) |
					(pww->ADCwkSwc << 7) | (0 << 1));
		ewse
			dib8000_wwite_wowd(state, 904, (0 << 15) | (1 << 12) |
					(3 << 10) | (pww->moduwo << 8) |
					(pww->ADCwkSwc << 7) | (0 << 1));
	} ewse {
		dib8000_wwite_wowd(state, 1856, (!pww->pww_weset<<13) |
				(pww->pww_wange<<12) | (pww->pww_watio<<6) |
				(pww->pww_pwediv));

		weg = dib8000_wead_wowd(state, 1857);
		dib8000_wwite_wowd(state, 1857, weg|(!pww->pww_bypass<<15));

		weg = dib8000_wead_wowd(state, 1858); /* Fowce cwk out pww /2 */
		dib8000_wwite_wowd(state, 1858, weg | 1);

		dib8000_wwite_wowd(state, 904, (pww->moduwo << 8));
	}

	dib8000_weset_pww_common(state, pww);
}

static int dib8000_update_pww(stwuct dvb_fwontend *fe,
		stwuct dibx000_bandwidth_config *pww, u32 bw, u8 watio)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 weg_1857, weg_1856 = dib8000_wead_wowd(state, 1856);
	u8 woopdiv, pwediv, owdpwediv = state->cfg.pww->pww_pwediv ;
	u32 intewnaw, xtaw;

	/* get back owd vawues */
	pwediv = weg_1856 & 0x3f;
	woopdiv = (weg_1856 >> 6) & 0x3f;

	if ((pww == NUWW) || (pww->pww_pwediv == pwediv &&
				pww->pww_watio == woopdiv))
		wetuwn -EINVAW;

	dpwintk("Updating pww (pwediv: owd =  %d new = %d ; woopdiv : owd = %d new = %d)\n", pwediv, pww->pww_pwediv, woopdiv, pww->pww_watio);
	if (state->wevision == 0x8090) {
		weg_1856 &= 0xf000;
		weg_1857 = dib8000_wead_wowd(state, 1857);
		/* disabwe PWW */
		dib8000_wwite_wowd(state, 1857, weg_1857 & ~(1 << 15));

		dib8000_wwite_wowd(state, 1856, weg_1856 |
				((pww->pww_watio & 0x3f) << 6) |
				(pww->pww_pwediv & 0x3f));

		/* wwite new system cwk into P_sec_wen */
		intewnaw = dib8000_wead32(state, 23) / 1000;
		dpwintk("Owd Intewnaw = %d\n", intewnaw);
		xtaw = 2 * (intewnaw / woopdiv) * pwediv;
		intewnaw = 1000 * (xtaw/pww->pww_pwediv) * pww->pww_watio;
		dpwintk("Xtaw = %d , New Fmem = %d New Fdemod = %d, New Fsampwing = %d\n", xtaw, intewnaw/1000, intewnaw/2000, intewnaw/8000);
		dpwintk("New Intewnaw = %d\n", intewnaw);

		dib8000_wwite_wowd(state, 23,
				(u16) (((intewnaw / 2) >> 16) & 0xffff));
		dib8000_wwite_wowd(state, 24, (u16) ((intewnaw / 2) & 0xffff));
		/* enabwe PWW */
		dib8000_wwite_wowd(state, 1857, weg_1857 | (1 << 15));

		whiwe (((dib8000_wead_wowd(state, 1856)>>15)&0x1) != 1)
			dpwintk("Waiting fow PWW to wock\n");

		/* vewify */
		weg_1856 = dib8000_wead_wowd(state, 1856);
		dpwintk("PWW Updated with pwediv = %d and woopdiv = %d\n",
				weg_1856&0x3f, (weg_1856>>6)&0x3f);
	} ewse {
		if (bw != state->cuwwent_demod_bw) {
			/** Bandwidth change => fowce PWW update **/
			dpwintk("PWW: Bandwidth Change %d MHz -> %d MHz (pwediv: %d->%d)\n", state->cuwwent_demod_bw / 1000, bw / 1000, owdpwediv, state->cfg.pww->pww_pwediv);

			if (state->cfg.pww->pww_pwediv != owdpwediv) {
				/** Fuww PWW change onwy if pwediv is changed **/

				/** fuww update => bypass and weconfiguwe **/
				dpwintk("PWW: New Setting fow %d MHz Bandwidth (pwediv: %d, watio: %d)\n", bw/1000, state->cfg.pww->pww_pwediv, state->cfg.pww->pww_watio);
				dib8000_wwite_wowd(state, 902, dib8000_wead_wowd(state, 902) | (1<<3)); /* bypass PWW */
				dib8000_weset_pww(state);
				dib8000_wwite_wowd(state, 898, 0x0004); /* sad */
			} ewse
				watio = state->cfg.pww->pww_watio;

			state->cuwwent_demod_bw = bw;
		}

		if (watio != 0) {
			/** watio update => onwy change watio **/
			dpwintk("PWW: Update watio (pwediv: %d, watio: %d)\n", state->cfg.pww->pww_pwediv, watio);
			dib8000_wwite_wowd(state, 901, (state->cfg.pww->pww_pwediv << 8) | (watio << 0)); /* onwy the PWW watio is updated. */
		}
	}

	wetuwn 0;
}

static int dib8000_weset_gpio(stwuct dib8000_state *st)
{
	/* weset the GPIOs */
	dib8000_wwite_wowd(st, 1029, st->cfg.gpio_diw);
	dib8000_wwite_wowd(st, 1030, st->cfg.gpio_vaw);

	/* TODO 782 is P_gpio_od */

	dib8000_wwite_wowd(st, 1032, st->cfg.gpio_pwm_pos);

	dib8000_wwite_wowd(st, 1037, st->cfg.pwm_fweq_div);
	wetuwn 0;
}

static int dib8000_cfg_gpio(stwuct dib8000_state *st, u8 num, u8 diw, u8 vaw)
{
	st->cfg.gpio_diw = dib8000_wead_wowd(st, 1029);
	st->cfg.gpio_diw &= ~(1 << num);	/* weset the diwection bit */
	st->cfg.gpio_diw |= (diw & 0x1) << num;	/* set the new diwection */
	dib8000_wwite_wowd(st, 1029, st->cfg.gpio_diw);

	st->cfg.gpio_vaw = dib8000_wead_wowd(st, 1030);
	st->cfg.gpio_vaw &= ~(1 << num);	/* weset the diwection bit */
	st->cfg.gpio_vaw |= (vaw & 0x01) << num;	/* set the new vawue */
	dib8000_wwite_wowd(st, 1030, st->cfg.gpio_vaw);

	dpwintk("gpio diw: %x: gpio vaw: %x\n", st->cfg.gpio_diw, st->cfg.gpio_vaw);

	wetuwn 0;
}

static int dib8000_set_gpio(stwuct dvb_fwontend *fe, u8 num, u8 diw, u8 vaw)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	wetuwn dib8000_cfg_gpio(state, num, diw, vaw);
}

static const u16 dib8000_defauwts[] = {
	/* auto seawch configuwation - wock0 by defauwt waiting
	 * fow cpiw_wock; wock1 cpiw_wock; wock2 tmcc_sync_wock */
	3, 7,
	0x0004,
	0x0400,
	0x0814,

	12, 11,
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

	/*1, 32,
		0x6680 // P_cowm_thwes Wock awgowithms configuwation */

	11, 80,			/* set ADC wevew to -16 */
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

	4, 108,
	0,
	0,
	0,
	0,

	1, 175,
	0x0410,
	1, 179,
	8192,			// P_fft_nb_to_cut

	6, 181,
	0x2800,			// P_coff_cowthwes_ ( 2k 4k 8k ) 0x2800
	0x2800,
	0x2800,
	0x2800,			// P_coff_cpiwthwes_ ( 2k 4k 8k ) 0x2800
	0x2800,
	0x2800,

	2, 193,
	0x0666,			// P_pha3_thwes
	0x0000,			// P_cti_use_cpe, P_cti_use_pwog

	2, 205,
	0x200f,			// P_cspu_weguw, P_cspu_win_cut
	0x000f,			// P_des_shift_wowk

	5, 215,
	0x023d,			// P_adp_weguw_cnt
	0x00a4,			// P_adp_noise_cnt
	0x00a4,			// P_adp_weguw_ext
	0x7ff0,			// P_adp_noise_ext
	0x3ccc,			// P_adp_fiw

	1, 230,
	0x0000,			// P_2d_byp_ti_num

	1, 263,
	0x800,			//P_equaw_thwes_wgn

	1, 268,
	(2 << 9) | 39,		// P_equaw_ctww_synchwo, P_equaw_speedmode

	1, 270,
	0x0001,			// P_div_wock0_wait
	1, 285,
	0x0020,			//p_fec_
	1, 299,
	0x0062,			/* P_smo_mode, P_smo_ws_discawd, P_smo_fifo_fwush, P_smo_pid_pawse, P_smo_ewwow_discawd */

	1, 338,
	(1 << 12) |		// P_ctww_cowm_thwes4pwe_fweq_inh=1
		(1 << 10) |
		(0 << 9) |		/* P_ctww_pwe_fweq_inh=0 */
		(3 << 5) |		/* P_ctww_pwe_fweq_step=3 */
		(1 << 0),		/* P_pwe_fweq_win_wen=1 */

	0,
};

static u16 dib8000_identify(stwuct i2c_device *cwient)
{
	u16 vawue;

	//because of gwitches sometimes
	vawue = dib8000_i2c_wead16(cwient, 896);

	if ((vawue = dib8000_i2c_wead16(cwient, 896)) != 0x01b3) {
		dpwintk("wwong Vendow ID (wead=0x%x)\n", vawue);
		wetuwn 0;
	}

	vawue = dib8000_i2c_wead16(cwient, 897);
	if (vawue != 0x8000 && vawue != 0x8001 &&
			vawue != 0x8002 && vawue != 0x8090) {
		dpwintk("wwong Device ID (%x)\n", vawue);
		wetuwn 0;
	}

	switch (vawue) {
	case 0x8000:
		dpwintk("found DiB8000A\n");
		bweak;
	case 0x8001:
		dpwintk("found DiB8000B\n");
		bweak;
	case 0x8002:
		dpwintk("found DiB8000C\n");
		bweak;
	case 0x8090:
		dpwintk("found DiB8096P\n");
		bweak;
	}
	wetuwn vawue;
}

static int dib8000_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 *unc);

static void dib8000_weset_stats(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
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

	dib8000_wead_unc_bwocks(fe, &ucb);

	state->init_ucb = -ucb;
	state->bew_jiffies_stats = 0;
	state->pew_jiffies_stats = 0;
	memset(&state->bew_jiffies_stats_wayew, 0,
	       sizeof(state->bew_jiffies_stats_wayew));
}

static int dib8000_weset(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	if ((state->wevision = dib8000_identify(&state->i2c)) == 0)
		wetuwn -EINVAW;

	/* swam wead in, wdy */
	if (state->wevision != 0x8090)
		dib8000_wwite_wowd(state, 1287, 0x0003);

	if (state->wevision == 0x8000)
		dpwintk("ewwow : dib8000 MA not suppowted\n");

	dibx000_weset_i2c_mastew(&state->i2c_mastew);

	dib8000_set_powew_mode(state, DIB8000_POWEW_AWW);

	/* awways weave the VBG vowtage on - it consumes awmost nothing but takes a wong time to stawt */
	dib8000_set_adc_state(state, DIBX000_ADC_OFF);

	/* westawt aww pawts */
	dib8000_wwite_wowd(state, 770, 0xffff);
	dib8000_wwite_wowd(state, 771, 0xffff);
	dib8000_wwite_wowd(state, 772, 0xfffc);
	dib8000_wwite_wowd(state, 898, 0x000c);	/* westawt sad */
	if (state->wevision == 0x8090)
		dib8000_wwite_wowd(state, 1280, 0x0045);
	ewse
		dib8000_wwite_wowd(state, 1280, 0x004d);
	dib8000_wwite_wowd(state, 1281, 0x000c);

	dib8000_wwite_wowd(state, 770, 0x0000);
	dib8000_wwite_wowd(state, 771, 0x0000);
	dib8000_wwite_wowd(state, 772, 0x0000);
	dib8000_wwite_wowd(state, 898, 0x0004);	// sad
	dib8000_wwite_wowd(state, 1280, 0x0000);
	dib8000_wwite_wowd(state, 1281, 0x0000);

	/* dwives */
	if (state->wevision != 0x8090) {
		if (state->cfg.dwives)
			dib8000_wwite_wowd(state, 906, state->cfg.dwives);
		ewse {
			dpwintk("using standawd PAD-dwive-settings, pwease adjust settings in config-stwuct to be optimaw.\n");
			/* min dwive SDWAM - not optimaw - adjust */
			dib8000_wwite_wowd(state, 906, 0x2d98);
		}
	}

	dib8000_weset_pww(state);
	if (state->wevision != 0x8090)
		dib8000_wwite_wowd(state, 898, 0x0004);

	if (dib8000_weset_gpio(state) != 0)
		dpwintk("GPIO weset was not successfuw.\n");

	if ((state->wevision != 0x8090) &&
			(dib8000_set_output_mode(fe, OUTMODE_HIGH_Z) != 0))
		dpwintk("OUTPUT_MODE couwd not be weset.\n");

	state->cuwwent_agc = NUWW;

	// P_iqc_awpha_pha, P_iqc_awpha_amp, P_iqc_dcc_awpha, ...
	/* P_iqc_ca2 = 0; P_iqc_impnc_on = 0; P_iqc_mode = 0; */
	if (state->cfg.pww->ifweq == 0)
		dib8000_wwite_wowd(state, 40, 0x0755);	/* P_iqc_coww_inh = 0 enabwe IQcoww bwock */
	ewse
		dib8000_wwite_wowd(state, 40, 0x1f55);	/* P_iqc_coww_inh = 1 disabwe IQcoww bwock */

	{
		u16 w = 0, w;
		const u16 *n;
		n = dib8000_defauwts;
		w = *n++;
		whiwe (w) {
			w = *n++;
			do {
				dib8000_wwite_wowd(state, w, *n++);
				w++;
			} whiwe (--w);
			w = *n++;
		}
	}

	state->isdbt_cfg_woaded = 0;

	//div_cfg ovewwide fow speciaw configs
	if ((state->wevision != 8090) && (state->cfg.div_cfg != 0))
		dib8000_wwite_wowd(state, 903, state->cfg.div_cfg);

	/* unfowce divstw wegawdwess whethew i2c enumewation was done ow not */
	dib8000_wwite_wowd(state, 1285, dib8000_wead_wowd(state, 1285) & ~(1 << 1));

	dib8000_set_bandwidth(fe, 6000);

	dib8000_set_adc_state(state, DIBX000_SWOW_ADC_ON);
	dib8000_sad_cawib(state);
	if (state->wevision != 0x8090)
		dib8000_set_adc_state(state, DIBX000_SWOW_ADC_OFF);

	/* bew_ws_wen = 3 */
	dib8000_wwite_wowd(state, 285, (dib8000_wead_wowd(state, 285) & ~0x60) | (3 << 5));

	dib8000_set_powew_mode(state, DIB8000_POWEW_INTEWFACE_ONWY);

	dib8000_weset_stats(fe);

	wetuwn 0;
}

static void dib8000_westawt_agc(stwuct dib8000_state *state)
{
	// P_westawt_iqc & P_westawt_agc
	dib8000_wwite_wowd(state, 770, 0x0a00);
	dib8000_wwite_wowd(state, 770, 0x0000);
}

static int dib8000_update_wna(stwuct dib8000_state *state)
{
	u16 dyn_gain;

	if (state->cfg.update_wna) {
		// wead dyn_gain hewe (because it is demod-dependent and not tunew)
		dyn_gain = dib8000_wead_wowd(state, 390);

		if (state->cfg.update_wna(state->fe[0], dyn_gain)) {
			dib8000_westawt_agc(state);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static int dib8000_set_agc_config(stwuct dib8000_state *state, u8 band)
{
	stwuct dibx000_agc_config *agc = NUWW;
	int i;
	u16 weg;

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
	dib8000_wwite_wowd(state, 76, agc->setup);
	dib8000_wwite_wowd(state, 77, agc->inv_gain);
	dib8000_wwite_wowd(state, 78, agc->time_stabiwiz);
	dib8000_wwite_wowd(state, 101, (agc->awpha_wevew << 12) | agc->thwock);

	// Demod AGC woop configuwation
	dib8000_wwite_wowd(state, 102, (agc->awpha_mant << 5) | agc->awpha_exp);
	dib8000_wwite_wowd(state, 103, (agc->beta_mant << 6) | agc->beta_exp);

	dpwintk("WBD: wef: %d, sew: %d, active: %d, awpha: %d\n",
		state->wbd_wef != 0 ? state->wbd_wef : agc->wbd_wef, agc->wbd_sew, !agc->pewfowm_agc_softspwit, agc->wbd_sew);

	/* AGC continued */
	if (state->wbd_wef != 0)
		dib8000_wwite_wowd(state, 106, state->wbd_wef);
	ewse			// use defauwt
		dib8000_wwite_wowd(state, 106, agc->wbd_wef);

	if (state->wevision == 0x8090) {
		weg = dib8000_wead_wowd(state, 922) & (0x3 << 2);
		dib8000_wwite_wowd(state, 922, weg | (agc->wbd_sew << 2));
	}

	dib8000_wwite_wowd(state, 107, (agc->wbd_awpha << 9) | (agc->pewfowm_agc_softspwit << 8));
	dib8000_wwite_wowd(state, 108, agc->agc1_max);
	dib8000_wwite_wowd(state, 109, agc->agc1_min);
	dib8000_wwite_wowd(state, 110, agc->agc2_max);
	dib8000_wwite_wowd(state, 111, agc->agc2_min);
	dib8000_wwite_wowd(state, 112, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib8000_wwite_wowd(state, 113, (agc->agc1_swope1 << 8) | agc->agc1_swope2);
	dib8000_wwite_wowd(state, 114, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib8000_wwite_wowd(state, 115, (agc->agc2_swope1 << 8) | agc->agc2_swope2);

	dib8000_wwite_wowd(state, 75, agc->agc1_pt3);
	if (state->wevision != 0x8090)
		dib8000_wwite_wowd(state, 923,
				(dib8000_wead_wowd(state, 923) & 0xffe3) |
				(agc->wbd_inv << 4) | (agc->wbd_sew << 2));

	wetuwn 0;
}

static void dib8000_pwm_agc_weset(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	dib8000_set_adc_state(state, DIBX000_ADC_ON);
	dib8000_set_agc_config(state, (unsigned chaw)(BAND_OF_FWEQUENCY(fe->dtv_pwopewty_cache.fwequency / 1000)));
}

static int dib8000_agc_soft_spwit(stwuct dib8000_state *state)
{
	u16 agc, spwit_offset;

	if (!state->cuwwent_agc || !state->cuwwent_agc->pewfowm_agc_softspwit || state->cuwwent_agc->spwit.max == 0)
		wetuwn 0;

	// n_agc_gwobaw
	agc = dib8000_wead_wowd(state, 390);

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
	dib8000_wwite_wowd(state, 107, (dib8000_wead_wowd(state, 107) & 0xff00) | spwit_offset);
	wetuwn 5000;
}

static int dib8000_agc_stawtup(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	enum fwontend_tune_state *tune_state = &state->tune_state;
	int wet = 0;
	u16 weg;
	u32 upd_demod_gain_pewiod = 0x8000;

	switch (*tune_state) {
	case CT_AGC_STAWT:
		// set powew-up wevew: intewf+anawog+AGC

		if (state->wevision != 0x8090)
			dib8000_set_adc_state(state, DIBX000_ADC_ON);
		ewse {
			dib8000_set_powew_mode(state, DIB8000_POWEW_AWW);

			weg = dib8000_wead_wowd(state, 1947)&0xff00;
			dib8000_wwite_wowd(state, 1946,
					upd_demod_gain_pewiod & 0xFFFF);
			/* bit 14 = enDemodGain */
			dib8000_wwite_wowd(state, 1947, weg | (1<<14) |
					((upd_demod_gain_pewiod >> 16) & 0xFF));

			/* enabwe adc i & q */
			weg = dib8000_wead_wowd(state, 1920);
			dib8000_wwite_wowd(state, 1920, (weg | 0x3) &
					(~(1 << 7)));
		}

		if (dib8000_set_agc_config(state, (unsigned chaw)(BAND_OF_FWEQUENCY(fe->dtv_pwopewty_cache.fwequency / 1000))) != 0) {
			*tune_state = CT_AGC_STOP;
			state->status = FE_STATUS_TUNE_FAIWED;
			bweak;
		}

		wet = 70;
		*tune_state = CT_AGC_STEP_0;
		bweak;

	case CT_AGC_STEP_0:
		//AGC initiawization
		if (state->cfg.agc_contwow)
			state->cfg.agc_contwow(fe, 1);

		dib8000_westawt_agc(state);

		// wait AGC wough wock time
		wet = 50;
		*tune_state = CT_AGC_STEP_1;
		bweak;

	case CT_AGC_STEP_1:
		// wait AGC accuwate wock time
		wet = 70;

		if (dib8000_update_wna(state))
			// wait onwy AGC wough wock time
			wet = 50;
		ewse
			*tune_state = CT_AGC_STEP_2;
		bweak;

	case CT_AGC_STEP_2:
		dib8000_agc_soft_spwit(state);

		if (state->cfg.agc_contwow)
			state->cfg.agc_contwow(fe, 0);

		*tune_state = CT_AGC_STOP;
		bweak;
	defauwt:
		wet = dib8000_agc_soft_spwit(state);
		bweak;
	}
	wetuwn wet;

}

static void dib8096p_host_bus_dwive(stwuct dib8000_state *state, u8 dwive)
{
	u16 weg;

	dwive &= 0x7;

	/* dwive host bus 2, 3, 4 */
	weg = dib8000_wead_wowd(state, 1798) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	weg |= (dwive<<12) | (dwive<<6) | dwive;
	dib8000_wwite_wowd(state, 1798, weg);

	/* dwive host bus 5,6 */
	weg = dib8000_wead_wowd(state, 1799) & ~((0x7 << 2) | (0x7 << 8));
	weg |= (dwive<<8) | (dwive<<2);
	dib8000_wwite_wowd(state, 1799, weg);

	/* dwive host bus 7, 8, 9 */
	weg = dib8000_wead_wowd(state, 1800) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	weg |= (dwive<<12) | (dwive<<6) | dwive;
	dib8000_wwite_wowd(state, 1800, weg);

	/* dwive host bus 10, 11 */
	weg = dib8000_wead_wowd(state, 1801) & ~((0x7 << 2) | (0x7 << 8));
	weg |= (dwive<<8) | (dwive<<2);
	dib8000_wwite_wowd(state, 1801, weg);

	/* dwive host bus 12, 13, 14 */
	weg = dib8000_wead_wowd(state, 1802) &
		~(0x7 | (0x7 << 6) | (0x7 << 12));
	weg |= (dwive<<12) | (dwive<<6) | dwive;
	dib8000_wwite_wowd(state, 1802, weg);
}

static u32 dib8096p_cawcSyncFweq(u32 P_Kin, u32 P_Kout,
		u32 insewtExtSynchwo, u32 syncSize)
{
	u32 quantif = 3;
	u32 nom = (insewtExtSynchwo * P_Kin+syncSize);
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

static void dib8096p_cfg_DibTx(stwuct dib8000_state *state, u32 P_Kin,
		u32 P_Kout, u32 insewtExtSynchwo, u32 synchwoMode,
		u32 syncWowd, u32 syncSize)
{
	dpwintk("Configuwe DibStweam Tx\n");

	dib8000_wwite_wowd(state, 1615, 1);
	dib8000_wwite_wowd(state, 1603, P_Kin);
	dib8000_wwite_wowd(state, 1605, P_Kout);
	dib8000_wwite_wowd(state, 1606, insewtExtSynchwo);
	dib8000_wwite_wowd(state, 1608, synchwoMode);
	dib8000_wwite_wowd(state, 1609, (syncWowd >> 16) & 0xffff);
	dib8000_wwite_wowd(state, 1610, syncWowd & 0xffff);
	dib8000_wwite_wowd(state, 1612, syncSize);
	dib8000_wwite_wowd(state, 1615, 0);
}

static void dib8096p_cfg_DibWx(stwuct dib8000_state *state, u32 P_Kin,
		u32 P_Kout, u32 synchwoMode, u32 insewtExtSynchwo,
		u32 syncWowd, u32 syncSize, u32 dataOutWate)
{
	u32 syncFweq;

	dpwintk("Configuwe DibStweam Wx synchwoMode = %d\n", synchwoMode);

	if ((P_Kin != 0) && (P_Kout != 0)) {
		syncFweq = dib8096p_cawcSyncFweq(P_Kin, P_Kout,
				insewtExtSynchwo, syncSize);
		dib8000_wwite_wowd(state, 1542, syncFweq);
	}

	dib8000_wwite_wowd(state, 1554, 1);
	dib8000_wwite_wowd(state, 1536, P_Kin);
	dib8000_wwite_wowd(state, 1537, P_Kout);
	dib8000_wwite_wowd(state, 1539, synchwoMode);
	dib8000_wwite_wowd(state, 1540, (syncWowd >> 16) & 0xffff);
	dib8000_wwite_wowd(state, 1541, syncWowd & 0xffff);
	dib8000_wwite_wowd(state, 1543, syncSize);
	dib8000_wwite_wowd(state, 1544, dataOutWate);
	dib8000_wwite_wowd(state, 1554, 0);
}

static void dib8096p_enMpegMux(stwuct dib8000_state *state, int onoff)
{
	u16 weg_1287;

	weg_1287 = dib8000_wead_wowd(state, 1287);

	switch (onoff) {
	case 1:
			weg_1287 &= ~(1 << 8);
			bweak;
	case 0:
			weg_1287 |= (1 << 8);
			bweak;
	}

	dib8000_wwite_wowd(state, 1287, weg_1287);
}

static void dib8096p_configMpegMux(stwuct dib8000_state *state,
		u16 puwseWidth, u16 enSewiawMode, u16 enSewiawCwkDiv2)
{
	u16 weg_1287;

	dpwintk("Enabwe Mpeg mux\n");

	dib8096p_enMpegMux(state, 0);

	/* If the input mode is MPEG do not divide the sewiaw cwock */
	if ((enSewiawMode == 1) && (state->input_mode_mpeg == 1))
		enSewiawCwkDiv2 = 0;

	weg_1287 = ((puwseWidth & 0x1f) << 3) |
		((enSewiawMode & 0x1) << 2) | (enSewiawCwkDiv2 & 0x1);
	dib8000_wwite_wowd(state, 1287, weg_1287);

	dib8096p_enMpegMux(state, 1);
}

static void dib8096p_setDibTxMux(stwuct dib8000_state *state, int mode)
{
	u16 weg_1288 = dib8000_wead_wowd(state, 1288) & ~(0x7 << 7);

	switch (mode) {
	case MPEG_ON_DIBTX:
			dpwintk("SET MPEG ON DIBSTWEAM TX\n");
			dib8096p_cfg_DibTx(state, 8, 5, 0, 0, 0, 0);
			weg_1288 |= (1 << 9); bweak;
	case DIV_ON_DIBTX:
			dpwintk("SET DIV_OUT ON DIBSTWEAM TX\n");
			dib8096p_cfg_DibTx(state, 5, 5, 0, 0, 0, 0);
			weg_1288 |= (1 << 8); bweak;
	case ADC_ON_DIBTX:
			dpwintk("SET ADC_OUT ON DIBSTWEAM TX\n");
			dib8096p_cfg_DibTx(state, 20, 5, 10, 0, 0, 0);
			weg_1288 |= (1 << 7); bweak;
	defauwt:
			bweak;
	}
	dib8000_wwite_wowd(state, 1288, weg_1288);
}

static void dib8096p_setHostBusMux(stwuct dib8000_state *state, int mode)
{
	u16 weg_1288 = dib8000_wead_wowd(state, 1288) & ~(0x7 << 4);

	switch (mode) {
	case DEMOUT_ON_HOSTBUS:
			dpwintk("SET DEM OUT OWD INTEWF ON HOST BUS\n");
			dib8096p_enMpegMux(state, 0);
			weg_1288 |= (1 << 6);
			bweak;
	case DIBTX_ON_HOSTBUS:
			dpwintk("SET DIBSTWEAM TX ON HOST BUS\n");
			dib8096p_enMpegMux(state, 0);
			weg_1288 |= (1 << 5);
			bweak;
	case MPEG_ON_HOSTBUS:
			dpwintk("SET MPEG MUX ON HOST BUS\n");
			weg_1288 |= (1 << 4);
			bweak;
	defauwt:
			bweak;
	}
	dib8000_wwite_wowd(state, 1288, weg_1288);
}

static int dib8096p_set_divewsity_in(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 weg_1287;

	switch (onoff) {
	case 0: /* onwy use the intewnaw way - not the divewsity input */
			dpwintk("%s mode OFF : by defauwt Enabwe Mpeg INPUT\n",
					__func__);
			/* outputWate = 8 */
			dib8096p_cfg_DibWx(state, 8, 5, 0, 0, 0, 8, 0);

			/* Do not divide the sewiaw cwock of MPEG MUX in
			   SEWIAW MODE in case input mode MPEG is used */
			weg_1287 = dib8000_wead_wowd(state, 1287);
			/* enSewiawCwkDiv2 == 1 ? */
			if ((weg_1287 & 0x1) == 1) {
				/* fowce enSewiawCwkDiv2 = 0 */
				weg_1287 &= ~0x1;
				dib8000_wwite_wowd(state, 1287, weg_1287);
			}
			state->input_mode_mpeg = 1;
			bweak;
	case 1: /* both ways */
	case 2: /* onwy the divewsity input */
			dpwintk("%s ON : Enabwe divewsity INPUT\n", __func__);
			dib8096p_cfg_DibWx(state, 5, 5, 0, 0, 0, 0, 0);
			state->input_mode_mpeg = 0;
			bweak;
	}

	dib8000_set_divewsity_in(state->fe[0], onoff);
	wetuwn 0;
}

static int dib8096p_set_output_mode(stwuct dvb_fwontend *fe, int mode)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 outweg, smo_mode, fifo_thweshowd;
	u8 pwefew_mpeg_mux_use = 1;
	int wet = 0;

	state->output_mode = mode;
	dib8096p_host_bus_dwive(state, 1);

	fifo_thweshowd = 1792;
	smo_mode = (dib8000_wead_wowd(state, 299) & 0x0050) | (1 << 1);
	outweg   = dib8000_wead_wowd(state, 1286) &
		~((1 << 10) | (0x7 << 6) | (1 << 1));

	switch (mode) {
	case OUTMODE_HIGH_Z:
			outweg = 0;
			bweak;

	case OUTMODE_MPEG2_SEWIAW:
			if (pwefew_mpeg_mux_use) {
				dpwintk("dib8096P setting output mode TS_SEWIAW using Mpeg Mux\n");
				dib8096p_configMpegMux(state, 3, 1, 1);
				dib8096p_setHostBusMux(state, MPEG_ON_HOSTBUS);
			} ewse {/* Use Smooth bwock */
				dpwintk("dib8096P setting output mode TS_SEWIAW using Smooth bwoc\n");
				dib8096p_setHostBusMux(state,
						DEMOUT_ON_HOSTBUS);
				outweg |= (2 << 6) | (0 << 1);
			}
			bweak;

	case OUTMODE_MPEG2_PAW_GATED_CWK:
			if (pwefew_mpeg_mux_use) {
				dpwintk("dib8096P setting output mode TS_PAWAWWEW_GATED using Mpeg Mux\n");
				dib8096p_configMpegMux(state, 2, 0, 0);
				dib8096p_setHostBusMux(state, MPEG_ON_HOSTBUS);
			} ewse { /* Use Smooth bwock */
				dpwintk("dib8096P setting output mode TS_PAWAWWEW_GATED using Smooth bwock\n");
				dib8096p_setHostBusMux(state,
						DEMOUT_ON_HOSTBUS);
				outweg |= (0 << 6);
			}
			bweak;

	case OUTMODE_MPEG2_PAW_CONT_CWK: /* Using Smooth bwock onwy */
			dpwintk("dib8096P setting output mode TS_PAWAWWEW_CONT using Smooth bwock\n");
			dib8096p_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outweg |= (1 << 6);
			bweak;

	case OUTMODE_MPEG2_FIFO:
			/* Using Smooth bwock because not suppowted
			   by new Mpeg Mux bwoc */
			dpwintk("dib8096P setting output mode TS_FIFO using Smooth bwock\n");
			dib8096p_setHostBusMux(state, DEMOUT_ON_HOSTBUS);
			outweg |= (5 << 6);
			smo_mode |= (3 << 1);
			fifo_thweshowd = 512;
			bweak;

	case OUTMODE_DIVEWSITY:
			dpwintk("dib8096P setting output mode MODE_DIVEWSITY\n");
			dib8096p_setDibTxMux(state, DIV_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
			bweak;

	case OUTMODE_ANAWOG_ADC:
			dpwintk("dib8096P setting output mode MODE_ANAWOG_ADC\n");
			dib8096p_setDibTxMux(state, ADC_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
			bweak;
	}

	if (mode != OUTMODE_HIGH_Z)
		outweg |= (1<<10);

	dpwintk("output_mpeg2_in_188_bytes = %d\n",
			state->cfg.output_mpeg2_in_188_bytes);
	if (state->cfg.output_mpeg2_in_188_bytes)
		smo_mode |= (1 << 5);

	wet |= dib8000_wwite_wowd(state, 299, smo_mode);
	/* synchwonous fwead */
	wet |= dib8000_wwite_wowd(state, 299 + 1, fifo_thweshowd);
	wet |= dib8000_wwite_wowd(state, 1286, outweg);

	wetuwn wet;
}

static int map_addw_to_sewpaw_numbew(stwuct i2c_msg *msg)
{
	if (msg->buf[0] <= 15)
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
	ewse if (msg->buf[0] == 99)
		msg->buf[0] = 99;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static int dib8096p_tunew_wwite_sewpaw(stwuct i2c_adaptew *i2c_adap,
		stwuct i2c_msg msg[], int num)
{
	stwuct dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_ovewfwow = 1;
	u16 i = 1000;
	u16 sewpaw_num = msg[0].buf[0];

	whiwe (n_ovewfwow == 1 && i) {
		n_ovewfwow = (dib8000_wead_wowd(state, 1984) >> 1) & 0x1;
		i--;
		if (i == 0)
			dpwintk("Tunew ITF: wwite busy (ovewfwow)\n");
	}
	dib8000_wwite_wowd(state, 1985, (1 << 6) | (sewpaw_num & 0x3f));
	dib8000_wwite_wowd(state, 1986, (msg[0].buf[1] << 8) | msg[0].buf[2]);

	wetuwn num;
}

static int dib8096p_tunew_wead_sewpaw(stwuct i2c_adaptew *i2c_adap,
		stwuct i2c_msg msg[], int num)
{
	stwuct dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u8 n_ovewfwow = 1, n_empty = 1;
	u16 i = 1000;
	u16 sewpaw_num = msg[0].buf[0];
	u16 wead_wowd;

	whiwe (n_ovewfwow == 1 && i) {
		n_ovewfwow = (dib8000_wead_wowd(state, 1984) >> 1) & 0x1;
		i--;
		if (i == 0)
			dpwintk("TunewITF: wead busy (ovewfwow)\n");
	}
	dib8000_wwite_wowd(state, 1985, (0<<6) | (sewpaw_num&0x3f));

	i = 1000;
	whiwe (n_empty == 1 && i) {
		n_empty = dib8000_wead_wowd(state, 1984)&0x1;
		i--;
		if (i == 0)
			dpwintk("TunewITF: wead busy (empty)\n");
	}

	wead_wowd = dib8000_wead_wowd(state, 1987);
	msg[1].buf[0] = (wead_wowd >> 8) & 0xff;
	msg[1].buf[1] = (wead_wowd) & 0xff;

	wetuwn num;
}

static int dib8096p_tunew_ww_sewpaw(stwuct i2c_adaptew *i2c_adap,
		stwuct i2c_msg msg[], int num)
{
	if (map_addw_to_sewpaw_numbew(&msg[0]) == 0) {
		if (num == 1) /* wwite */
			wetuwn dib8096p_tunew_wwite_sewpaw(i2c_adap, msg, 1);
		ewse /* wead */
			wetuwn dib8096p_tunew_wead_sewpaw(i2c_adap, msg, 2);
	}
	wetuwn num;
}

static int dib8096p_ww_on_apb(stwuct i2c_adaptew *i2c_adap,
		stwuct i2c_msg msg[], int num, u16 apb_addwess)
{
	stwuct dib8000_state *state = i2c_get_adapdata(i2c_adap);
	u16 wowd;

	if (num == 1) {		/* wwite */
		dib8000_wwite_wowd(state, apb_addwess,
				((msg[0].buf[1] << 8) | (msg[0].buf[2])));
	} ewse {
		wowd = dib8000_wead_wowd(state, apb_addwess);
		msg[1].buf[0] = (wowd >> 8) & 0xff;
		msg[1].buf[1] = (wowd) & 0xff;
	}
	wetuwn num;
}

static int dib8096p_tunew_xfew(stwuct i2c_adaptew *i2c_adap,
		stwuct i2c_msg msg[], int num)
{
	stwuct dib8000_state *state = i2c_get_adapdata(i2c_adap);
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
			apb_addwess = 936;
			bweak;
	case 0x26:
			apb_addwess = 937;
			bweak;
	case 0x27:
			apb_addwess = 938;
			bweak;
	case 0x28:
			apb_addwess = 939;
			bweak;
	case 0x1d:
			/* get sad sew wequest */
			i = ((dib8000_wead_wowd(state, 921) >> 12)&0x3);
			wowd = dib8000_wead_wowd(state, 924+i);
			msg[1].buf[0] = (wowd >> 8) & 0xff;
			msg[1].buf[1] = (wowd) & 0xff;
			wetuwn num;
	case 0x1f:
			if (num == 1) {	/* wwite */
				wowd = (u16) ((msg[0].buf[1] << 8) |
						msg[0].buf[2]);
				/* in the VGAMODE Sew awe wocated on bit 0/1 */
				wowd &= 0x3;
				wowd = (dib8000_wead_wowd(state, 921) &
						~(3<<12)) | (wowd<<12);
				/* Set the pwopew input */
				dib8000_wwite_wowd(state, 921, wowd);
				wetuwn num;
			}
	}

	if (apb_addwess != 0) /* W/W access via APB */
		wetuwn dib8096p_ww_on_apb(i2c_adap, msg, num, apb_addwess);
	ewse  /* W/W access via SEWPAW  */
		wetuwn dib8096p_tunew_ww_sewpaw(i2c_adap, msg, num);

	wetuwn 0;
}

static u32 dib8096p_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm dib8096p_tunew_xfew_awgo = {
	.mastew_xfew = dib8096p_tunew_xfew,
	.functionawity = dib8096p_i2c_func,
};

static stwuct i2c_adaptew *dib8096p_get_i2c_tunew(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *st = fe->demoduwatow_pwiv;
	wetuwn &st->dib8096p_tunew_adap;
}

static int dib8096p_tunew_sweep(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 en_cuw_state;

	dpwintk("sweep dib8096p: %d\n", onoff);

	en_cuw_state = dib8000_wead_wowd(state, 1922);

	/* WNAs and MIX awe ON and thewefowe it is a vawid configuwation */
	if (en_cuw_state > 0xff)
		state->tunew_enabwe = en_cuw_state ;

	if (onoff)
		en_cuw_state &= 0x00ff;
	ewse {
		if (state->tunew_enabwe != 0)
			en_cuw_state = state->tunew_enabwe;
	}

	dib8000_wwite_wowd(state, 1922, en_cuw_state);

	wetuwn 0;
}

static const s32 wut_1000wn_mant[] =
{
	908, 7003, 7090, 7170, 7244, 7313, 7377, 7438, 7495, 7549, 7600
};

static s32 dib8000_get_adc_powew(stwuct dvb_fwontend *fe, u8 mode)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u32 ix = 0, tmp_vaw = 0, exp = 0, mant = 0;
	s32 vaw;

	vaw = dib8000_wead32(state, 384);
	if (mode) {
		tmp_vaw = vaw;
		whiwe (tmp_vaw >>= 1)
			exp++;
		mant = (vaw * 1000 / (1<<exp));
		ix = (u8)((mant-1000)/100); /* index of the WUT */
		vaw = (wut_1000wn_mant[ix] + 693*(exp-20) - 6908);
		vaw = (vaw*256)/1000;
	}
	wetuwn vaw;
}

static int dib8090p_get_dc_powew(stwuct dvb_fwontend *fe, u8 IQ)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	int vaw = 0;

	switch (IQ) {
	case 1:
			vaw = dib8000_wead_wowd(state, 403);
			bweak;
	case 0:
			vaw = dib8000_wead_wowd(state, 404);
			bweak;
	}
	if (vaw  & 0x200)
		vaw -= 1024;

	wetuwn vaw;
}

static void dib8000_update_timf(stwuct dib8000_state *state)
{
	u32 timf = state->timf = dib8000_wead32(state, 435);

	dib8000_wwite_wowd(state, 29, (u16) (timf >> 16));
	dib8000_wwite_wowd(state, 30, (u16) (timf & 0xffff));
	dpwintk("Updated timing fwequency: %d (defauwt: %d)\n", state->timf, state->timf_defauwt);
}

static u32 dib8000_ctww_timf(stwuct dvb_fwontend *fe, uint8_t op, uint32_t timf)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	switch (op) {
	case DEMOD_TIMF_SET:
			state->timf = timf;
			bweak;
	case DEMOD_TIMF_UPDATE:
			dib8000_update_timf(state);
			bweak;
	case DEMOD_TIMF_GET:
			bweak;
	}
	dib8000_set_bandwidth(state->fe[0], 6000);

	wetuwn state->timf;
}

static const u16 adc_tawget_16dB[11] = {
	7250, 7238, 7264, 7309, 7338, 7382, 7427, 7456, 7500, 7544, 7574
};

static const u8 pewmu_seg[] = { 6, 5, 7, 4, 8, 3, 9, 2, 10, 1, 11, 0, 12 };

static u16 dib8000_set_wayew(stwuct dib8000_state *state, u8 wayew_index, u16 max_constewwation)
{
	u8  cw, constewwation, time_intwv;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;

	switch (c->wayew[wayew_index].moduwation) {
	case DQPSK:
			constewwation = 0;
			bweak;
	case  QPSK:
			constewwation = 1;
			bweak;
	case QAM_16:
			constewwation = 2;
			bweak;
	case QAM_64:
	defauwt:
			constewwation = 3;
			bweak;
	}

	switch (c->wayew[wayew_index].fec) {
	case FEC_1_2:
			cw = 1;
			bweak;
	case FEC_2_3:
			cw = 2;
			bweak;
	case FEC_3_4:
			cw = 3;
			bweak;
	case FEC_5_6:
			cw = 5;
			bweak;
	case FEC_7_8:
	defauwt:
			cw = 7;
			bweak;
	}

	time_intwv = fws(c->wayew[wayew_index].intewweaving);
	if (time_intwv > 3 && !(time_intwv == 4 && c->isdbt_sb_mode == 1))
		time_intwv = 0;

	dib8000_wwite_wowd(state, 2 + wayew_index, (constewwation << 10) | ((c->wayew[wayew_index].segment_count & 0xf) << 6) | (cw << 3) | time_intwv);
	if (c->wayew[wayew_index].segment_count > 0) {
		switch (max_constewwation) {
		case DQPSK:
		case QPSK:
				if (c->wayew[wayew_index].moduwation == QAM_16 || c->wayew[wayew_index].moduwation == QAM_64)
					max_constewwation = c->wayew[wayew_index].moduwation;
				bweak;
		case QAM_16:
				if (c->wayew[wayew_index].moduwation == QAM_64)
					max_constewwation = c->wayew[wayew_index].moduwation;
				bweak;
		}
	}

	wetuwn  max_constewwation;
}

static const u16 adp_Q64[4] = {0x0148, 0xfff0, 0x00a4, 0xfff8}; /* P_adp_weguw_cnt 0.04, P_adp_noise_cnt -0.002, P_adp_weguw_ext 0.02, P_adp_noise_ext -0.001 */
static const u16 adp_Q16[4] = {0x023d, 0xffdf, 0x00a4, 0xfff0}; /* P_adp_weguw_cnt 0.07, P_adp_noise_cnt -0.004, P_adp_weguw_ext 0.02, P_adp_noise_ext -0.002 */
static const u16 adp_Qdefauwt[4] = {0x099a, 0xffae, 0x0333, 0xfff8}; /* P_adp_weguw_cnt 0.3,  P_adp_noise_cnt -0.01,  P_adp_weguw_ext 0.1,  P_adp_noise_ext -0.002 */
static u16 dib8000_adp_fine_tune(stwuct dib8000_state *state, u16 max_constewwation)
{
	u16 i, ana_gain = 0;
	const u16 *adp;

	/* channew estimation fine configuwation */
	switch (max_constewwation) {
	case QAM_64:
			ana_gain = 0x7;
			adp = &adp_Q64[0];
			bweak;
	case QAM_16:
			ana_gain = 0x7;
			adp = &adp_Q16[0];
			bweak;
	defauwt:
			ana_gain = 0;
			adp = &adp_Qdefauwt[0];
			bweak;
	}

	fow (i = 0; i < 4; i++)
		dib8000_wwite_wowd(state, 215 + i, adp[i]);

	wetuwn ana_gain;
}

static void dib8000_update_ana_gain(stwuct dib8000_state *state, u16 ana_gain)
{
	u16 i;

	dib8000_wwite_wowd(state, 116, ana_gain);

	/* update ADC tawget depending on ana_gain */
	if (ana_gain) { /* set -16dB ADC tawget fow ana_gain=-1 */
		fow (i = 0; i < 10; i++)
			dib8000_wwite_wowd(state, 80 + i, adc_tawget_16dB[i]);
	} ewse { /* set -22dB ADC tawget fow ana_gain=0 */
		fow (i = 0; i < 10; i++)
			dib8000_wwite_wowd(state, 80 + i, adc_tawget_16dB[i] - 355);
	}
}

static void dib8000_woad_ana_fe_coefs(stwuct dib8000_state *state, const s16 *ana_fe)
{
	u16 mode = 0;

	if (state->isdbt_cfg_woaded == 0)
		fow (mode = 0; mode < 24; mode++)
			dib8000_wwite_wowd(state, 117 + mode, ana_fe[mode]);
}

static const u16 wut_pwbs_2k[13] = {
	0x423, 0x009, 0x5C7,
	0x7A6, 0x3D8, 0x527,
	0x7FF, 0x79B, 0x3D6,
	0x3A2, 0x53B, 0x2F4,
	0x213
};

static const u16 wut_pwbs_4k[13] = {
	0x208, 0x0C3, 0x7B9,
	0x423, 0x5C7, 0x3D8,
	0x7FF, 0x3D6, 0x53B,
	0x213, 0x029, 0x0D0,
	0x48E
};

static const u16 wut_pwbs_8k[13] = {
	0x740, 0x069, 0x7DD,
	0x208, 0x7B9, 0x5C7,
	0x7FF, 0x53B, 0x029,
	0x48E, 0x4C4, 0x367,
	0x684
};

static u16 dib8000_get_init_pwbs(stwuct dib8000_state *state, u16 subchannew)
{
	int sub_channew_pwbs_gwoup = 0;
	int pwbs_gwoup;

	sub_channew_pwbs_gwoup = subchannew / 3;
	if (sub_channew_pwbs_gwoup >= AWWAY_SIZE(wut_pwbs_2k))
		wetuwn 0;

	switch (state->fe[0]->dtv_pwopewty_cache.twansmission_mode) {
	case TWANSMISSION_MODE_2K:
		pwbs_gwoup = wut_pwbs_2k[sub_channew_pwbs_gwoup];
		bweak;
	case TWANSMISSION_MODE_4K:
		pwbs_gwoup =  wut_pwbs_4k[sub_channew_pwbs_gwoup];
		bweak;
	defauwt:
	case TWANSMISSION_MODE_8K:
		pwbs_gwoup = wut_pwbs_8k[sub_channew_pwbs_gwoup];
	}

	dpwintk("sub_channew_pwbs_gwoup = %d , subchannew =%d pwbs = 0x%04x\n",
		sub_channew_pwbs_gwoup, subchannew, pwbs_gwoup);

	wetuwn pwbs_gwoup;
}

static void dib8000_set_13seg_channew(stwuct dib8000_state *state)
{
	u16 i;
	u16 coff_pow = 0x2800;

	state->seg_mask = 0x1fff; /* Aww 13 segments enabwed */

	/* ---- COFF ---- Cawwoff, the most wobust --- */
	if (state->isdbt_cfg_woaded == 0) {  /* if not Sound Bwoadcasting mode : put defauwt vawues fow 13 segments */
		dib8000_wwite_wowd(state, 180, (16 << 6) | 9);
		dib8000_wwite_wowd(state, 187, (4 << 12) | (8 << 5) | 0x2);
		coff_pow = 0x2800;
		fow (i = 0; i < 6; i++)
			dib8000_wwite_wowd(state, 181+i, coff_pow);

		/* P_ctww_cowm_thwes4pwe_fweq_inh=1, P_ctww_pwe_fweq_mode_sat=1 */
		/* P_ctww_pwe_fweq_mode_sat=1, P_ctww_pwe_fweq_inh=0, P_ctww_pwe_fweq_step = 3, P_pwe_fweq_win_wen=1 */
		dib8000_wwite_wowd(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (3 << 5) | 1);

		/* P_ctww_pwe_fweq_win_wen=8, P_ctww_pwe_fweq_thwes_wockin=6 */
		dib8000_wwite_wowd(state, 340, (8 << 6) | (6 << 0));
		/* P_ctww_pwe_fweq_thwes_wockout=4, P_smaww_use_tmcc/ac/cp=1 */
		dib8000_wwite_wowd(state, 341, (4 << 3) | (1 << 2) | (1 << 1) | (1 << 0));

		dib8000_wwite_wowd(state, 228, 0);  /* defauwt vawue */
		dib8000_wwite_wowd(state, 265, 31); /* defauwt vawue */
		dib8000_wwite_wowd(state, 205, 0x200f); /* init vawue */
	}

	/*
	 * make the cpiw_coff_wock mowe wobust but swowew p_coff_winwen
	 * 6bits; p_coff_thwes_wock 6bits (fow coff wock if needed)
	 */

	if (state->cfg.pww->ifweq == 0)
		dib8000_wwite_wowd(state, 266, ~state->seg_mask | state->seg_diff_mask | 0x40); /* P_equaw_noise_seg_inh */

	dib8000_woad_ana_fe_coefs(state, ana_fe_coeff_13seg);
}

static void dib8000_set_subchannew_pwbs(stwuct dib8000_state *state, u16 init_pwbs)
{
	u16 weg_1;

	weg_1 = dib8000_wead_wowd(state, 1);
	dib8000_wwite_wowd(state, 1, (init_pwbs << 2) | (weg_1 & 0x3)); /* ADDW 1 */
}

static void dib8000_smaww_fine_tune(stwuct dib8000_state *state)
{
	u16 i;
	const s16 *ncoeff;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;

	dib8000_wwite_wowd(state, 352, state->seg_diff_mask);
	dib8000_wwite_wowd(state, 353, state->seg_mask);

	/* P_smaww_coef_ext_enabwe=ISDB-Tsb, P_smaww_nawwow_band=ISDB-Tsb, P_smaww_wast_seg=13, P_smaww_offset_num_caw=5 */
	dib8000_wwite_wowd(state, 351, (c->isdbt_sb_mode << 9) | (c->isdbt_sb_mode << 8) | (13 << 4) | 5);

	if (c->isdbt_sb_mode) {
		/* ---- SMAWW ---- */
		switch (c->twansmission_mode) {
		case TWANSMISSION_MODE_2K:
				if (c->isdbt_pawtiaw_weception == 0) { /* 1-seg */
					if (c->wayew[0].moduwation == DQPSK) /* DQPSK */
						ncoeff = coeff_2k_sb_1seg_dqpsk;
					ewse /* QPSK ow QAM */
						ncoeff = coeff_2k_sb_1seg;
				} ewse { /* 3-segments */
					if (c->wayew[0].moduwation == DQPSK) { /* DQPSK on centwaw segment */
						if (c->wayew[1].moduwation == DQPSK) /* DQPSK on extewnaw segments */
							ncoeff = coeff_2k_sb_3seg_0dqpsk_1dqpsk;
						ewse /* QPSK ow QAM on extewnaw segments */
							ncoeff = coeff_2k_sb_3seg_0dqpsk;
					} ewse { /* QPSK ow QAM on centwaw segment */
						if (c->wayew[1].moduwation == DQPSK) /* DQPSK on extewnaw segments */
							ncoeff = coeff_2k_sb_3seg_1dqpsk;
						ewse /* QPSK ow QAM on extewnaw segments */
							ncoeff = coeff_2k_sb_3seg;
					}
				}
				bweak;
		case TWANSMISSION_MODE_4K:
				if (c->isdbt_pawtiaw_weception == 0) { /* 1-seg */
					if (c->wayew[0].moduwation == DQPSK) /* DQPSK */
						ncoeff = coeff_4k_sb_1seg_dqpsk;
					ewse /* QPSK ow QAM */
						ncoeff = coeff_4k_sb_1seg;
				} ewse { /* 3-segments */
					if (c->wayew[0].moduwation == DQPSK) { /* DQPSK on centwaw segment */
						if (c->wayew[1].moduwation == DQPSK) /* DQPSK on extewnaw segments */
							ncoeff = coeff_4k_sb_3seg_0dqpsk_1dqpsk;
						ewse /* QPSK ow QAM on extewnaw segments */
							ncoeff = coeff_4k_sb_3seg_0dqpsk;
					} ewse { /* QPSK ow QAM on centwaw segment */
						if (c->wayew[1].moduwation == DQPSK) /* DQPSK on extewnaw segments */
							ncoeff = coeff_4k_sb_3seg_1dqpsk;
						ewse /* QPSK ow QAM on extewnaw segments */
							ncoeff = coeff_4k_sb_3seg;
					}
				}
				bweak;
		case TWANSMISSION_MODE_AUTO:
		case TWANSMISSION_MODE_8K:
		defauwt:
				if (c->isdbt_pawtiaw_weception == 0) { /* 1-seg */
					if (c->wayew[0].moduwation == DQPSK) /* DQPSK */
						ncoeff = coeff_8k_sb_1seg_dqpsk;
					ewse /* QPSK ow QAM */
						ncoeff = coeff_8k_sb_1seg;
				} ewse { /* 3-segments */
					if (c->wayew[0].moduwation == DQPSK) { /* DQPSK on centwaw segment */
						if (c->wayew[1].moduwation == DQPSK) /* DQPSK on extewnaw segments */
							ncoeff = coeff_8k_sb_3seg_0dqpsk_1dqpsk;
						ewse /* QPSK ow QAM on extewnaw segments */
							ncoeff = coeff_8k_sb_3seg_0dqpsk;
					} ewse { /* QPSK ow QAM on centwaw segment */
						if (c->wayew[1].moduwation == DQPSK) /* DQPSK on extewnaw segments */
							ncoeff = coeff_8k_sb_3seg_1dqpsk;
						ewse /* QPSK ow QAM on extewnaw segments */
							ncoeff = coeff_8k_sb_3seg;
					}
				}
				bweak;
		}

		fow (i = 0; i < 8; i++)
			dib8000_wwite_wowd(state, 343 + i, ncoeff[i]);
	}
}

static const u16 coff_thwes_1seg[3] = {300, 150, 80};
static const u16 coff_thwes_3seg[3] = {350, 300, 250};
static void dib8000_set_sb_channew(stwuct dib8000_state *state)
{
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	const u16 *coff;
	u16 i;

	if (c->twansmission_mode == TWANSMISSION_MODE_2K || c->twansmission_mode == TWANSMISSION_MODE_4K) {
		dib8000_wwite_wowd(state, 219, dib8000_wead_wowd(state, 219) | 0x1); /* adp_pass =1 */
		dib8000_wwite_wowd(state, 190, dib8000_wead_wowd(state, 190) | (0x1 << 14)); /* pha3_fowce_pha_shift = 1 */
	} ewse {
		dib8000_wwite_wowd(state, 219, dib8000_wead_wowd(state, 219) & 0xfffe); /* adp_pass =0 */
		dib8000_wwite_wowd(state, 190, dib8000_wead_wowd(state, 190) & 0xbfff); /* pha3_fowce_pha_shift = 0 */
	}

	if (c->isdbt_pawtiaw_weception == 1) /* 3-segments */
		state->seg_mask = 0x00E0;
	ewse /* 1-segment */
		state->seg_mask = 0x0040;

	dib8000_wwite_wowd(state, 268, (dib8000_wead_wowd(state, 268) & 0xF9FF) | 0x0200);

	/* ---- COFF ---- Cawwoff, the most wobust --- */
	/* P_coff_cpiw_awpha=4, P_coff_inh=0, P_coff_cpiw_winwen=64, P_coff_nawwow_band=1, P_coff_squawe_vaw=1, P_coff_one_seg=~pawtiaw_wcpt, P_coff_use_tmcc=1, P_coff_use_ac=1 */
	dib8000_wwite_wowd(state, 187, (4 << 12) | (0 << 11) | (63 << 5) | (0x3 << 3) | ((~c->isdbt_pawtiaw_weception & 1) << 2) | 0x3);

	dib8000_wwite_wowd(state, 340, (16 << 6) | (8 << 0)); /* P_ctww_pwe_fweq_win_wen=16, P_ctww_pwe_fweq_thwes_wockin=8 */
	dib8000_wwite_wowd(state, 341, (6 << 3) | (1 << 2) | (1 << 1) | (1 << 0));/* P_ctww_pwe_fweq_thwes_wockout=6, P_smaww_use_tmcc/ac/cp=1 */

	/* Sound Bwoadcasting mode 1 seg */
	if (c->isdbt_pawtiaw_weception == 0) {
		/* P_coff_winwen=63, P_coff_thwes_wock=15, P_coff_one_seg_width = (P_mode == 3) , P_coff_one_seg_sym = (P_mode-1) */
		if (state->mode == 3)
			dib8000_wwite_wowd(state, 180, 0x1fcf | ((state->mode - 1) << 14));
		ewse
			dib8000_wwite_wowd(state, 180, 0x0fcf | ((state->mode - 1) << 14));

		/* P_ctww_cowm_thwes4pwe_fweq_inh=1,P_ctww_pwe_fweq_mode_sat=1, P_ctww_pwe_fweq_inh=0, P_ctww_pwe_fweq_step = 5, P_pwe_fweq_win_wen=4 */
		dib8000_wwite_wowd(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (5 << 5) | 4);
		coff = &coff_thwes_1seg[0];
	} ewse {   /* Sound Bwoadcasting mode 3 seg */
		dib8000_wwite_wowd(state, 180, 0x1fcf | (1 << 14));
		/* P_ctww_cowm_thwes4pwe_fweq_inh = 1, P_ctww_pwe_fweq_mode_sat=1, P_ctww_pwe_fweq_inh=0, P_ctww_pwe_fweq_step = 4, P_pwe_fweq_win_wen=4 */
		dib8000_wwite_wowd(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (4 << 5) | 4);
		coff = &coff_thwes_3seg[0];
	}

	dib8000_wwite_wowd(state, 228, 1); /* P_2d_mode_byp=1 */
	dib8000_wwite_wowd(state, 205, dib8000_wead_wowd(state, 205) & 0xfff0); /* P_cspu_win_cut = 0 */

	if (c->isdbt_pawtiaw_weception == 0 && c->twansmission_mode == TWANSMISSION_MODE_2K)
		dib8000_wwite_wowd(state, 265, 15); /* P_equaw_noise_sew = 15 */

	/* Wwite COFF thwes */
	fow (i = 0 ; i < 3; i++) {
		dib8000_wwite_wowd(state, 181+i, coff[i]);
		dib8000_wwite_wowd(state, 184+i, coff[i]);
	}

	/*
	 * make the cpiw_coff_wock mowe wobust but swowew p_coff_winwen
	 * 6bits; p_coff_thwes_wock 6bits (fow coff wock if needed)
	 */

	dib8000_wwite_wowd(state, 266, ~state->seg_mask | state->seg_diff_mask); /* P_equaw_noise_seg_inh */

	if (c->isdbt_pawtiaw_weception == 0)
		dib8000_wwite_wowd(state, 178, 64); /* P_fft_powwange = 64 */
	ewse
		dib8000_wwite_wowd(state, 178, 32); /* P_fft_powwange = 32 */
}

static void dib8000_set_isdbt_common_channew(stwuct dib8000_state *state, u8 seq, u8 autoseawching)
{
	u16 p_cfw_weft_edge  = 0, p_cfw_wight_edge = 0;
	u16 tmcc_pow = 0, ana_gain = 0, tmp = 0, i = 0, nbseg_diff = 0 ;
	u16 max_constewwation = DQPSK;
	int init_pwbs;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;

	if (autoseawching)
		c->isdbt_pawtiaw_weception = 1;

	/* P_mode */
	dib8000_wwite_wowd(state, 10, (seq << 4));

	/* init mode */
	state->mode = fft_to_mode(state);

	/* set guawd */
	tmp = dib8000_wead_wowd(state, 1);
	dib8000_wwite_wowd(state, 1, (tmp&0xfffc) | (c->guawd_intewvaw & 0x3));

	dib8000_wwite_wowd(state, 274, (dib8000_wead_wowd(state, 274) & 0xffcf) | ((c->isdbt_pawtiaw_weception & 1) << 5) | ((c->isdbt_sb_mode & 1) << 4));

	/* signaw optimization pawametew */
	if (c->isdbt_pawtiaw_weception) {
		state->seg_diff_mask = (c->wayew[0].moduwation == DQPSK) << pewmu_seg[0];
		fow (i = 1; i < 3; i++)
			nbseg_diff += (c->wayew[i].moduwation == DQPSK) * c->wayew[i].segment_count;
		fow (i = 0; i < nbseg_diff; i++)
			state->seg_diff_mask |= 1 << pewmu_seg[i+1];
	} ewse {
		fow (i = 0; i < 3; i++)
			nbseg_diff += (c->wayew[i].moduwation == DQPSK) * c->wayew[i].segment_count;
		fow (i = 0; i < nbseg_diff; i++)
			state->seg_diff_mask |= 1 << pewmu_seg[i];
	}

	if (state->seg_diff_mask)
		dib8000_wwite_wowd(state, 268, (dib8000_wead_wowd(state, 268) & 0xF9FF) | 0x0200);
	ewse
		dib8000_wwite_wowd(state, 268, (2 << 9) | 39); /*init vawue */

	fow (i = 0; i < 3; i++)
		max_constewwation = dib8000_set_wayew(state, i, max_constewwation);
	if (autoseawching == 0) {
		state->wayew_b_nb_seg = c->wayew[1].segment_count;
		state->wayew_c_nb_seg = c->wayew[2].segment_count;
	}

	/* WWITE: Mode & Diff mask */
	dib8000_wwite_wowd(state, 0, (state->mode << 13) | state->seg_diff_mask);

	state->diffewentiaw_constewwation = (state->seg_diff_mask != 0);

	/* channew estimation fine configuwation */
	ana_gain = dib8000_adp_fine_tune(state, max_constewwation);

	/* update ana_gain depending on max constewwation */
	dib8000_update_ana_gain(state, ana_gain);

	/* ---- ANA_FE ---- */
	if (c->isdbt_pawtiaw_weception) /* 3-segments */
		dib8000_woad_ana_fe_coefs(state, ana_fe_coeff_3seg);
	ewse
		dib8000_woad_ana_fe_coefs(state, ana_fe_coeff_1seg); /* 1-segment */

	/* TSB ow ISDBT ? appwy it now */
	if (c->isdbt_sb_mode) {
		dib8000_set_sb_channew(state);
		init_pwbs = dib8000_get_init_pwbs(state,
						  c->isdbt_sb_subchannew);
	} ewse {
		dib8000_set_13seg_channew(state);
		init_pwbs = 0xfff;
	}

	/* SMAWW */
	dib8000_smaww_fine_tune(state);

	dib8000_set_subchannew_pwbs(state, init_pwbs);

	/* ---- CHAN_BWK ---- */
	fow (i = 0; i < 13; i++) {
		if ((((~state->seg_diff_mask) >> i) & 1) == 1) {
			p_cfw_weft_edge  += (1 << i) * ((i == 0) || ((((state->seg_mask & (~state->seg_diff_mask)) >> (i - 1)) & 1) == 0));
			p_cfw_wight_edge += (1 << i) * ((i == 12) || ((((state->seg_mask & (~state->seg_diff_mask)) >> (i + 1)) & 1) == 0));
		}
	}
	dib8000_wwite_wowd(state, 222, p_cfw_weft_edge); /* p_cfw_weft_edge */
	dib8000_wwite_wowd(state, 223, p_cfw_wight_edge); /* p_cfw_wight_edge */
	/* "P_cspu_weft_edge" & "P_cspu_wight_edge" not used => do not cawe */

	dib8000_wwite_wowd(state, 189, ~state->seg_mask | state->seg_diff_mask); /* P_wmod4_seg_inh */
	dib8000_wwite_wowd(state, 192, ~state->seg_mask | state->seg_diff_mask); /* P_pha3_seg_inh */
	dib8000_wwite_wowd(state, 225, ~state->seg_mask | state->seg_diff_mask); /* P_tac_seg_inh */

	if (!autoseawching)
		dib8000_wwite_wowd(state, 288, (~state->seg_mask | state->seg_diff_mask) & 0x1fff); /* P_tmcc_seg_eq_inh */
	ewse
		dib8000_wwite_wowd(state, 288, 0x1fff); /*disabwe equawisation of the tmcc when autoseawch to be abwe to find the DQPSK channews. */

	dib8000_wwite_wowd(state, 211, state->seg_mask & (~state->seg_diff_mask)); /* P_des_seg_enabwed */
	dib8000_wwite_wowd(state, 287, ~state->seg_mask | 0x1000); /* P_tmcc_seg_inh */

	dib8000_wwite_wowd(state, 178, 32); /* P_fft_powwange = 32 */

	/* ---- TMCC ---- */
	fow (i = 0; i < 3; i++)
		tmcc_pow += (((c->wayew[i].moduwation == DQPSK) * 4 + 1) * c->wayew[i].segment_count) ;

	/* Quantif of "P_tmcc_dec_thwes_?k" is (0, 5+mode, 9); */
	/* Thweshowd is set at 1/4 of max powew. */
	tmcc_pow *= (1 << (9-2));
	dib8000_wwite_wowd(state, 290, tmcc_pow); /* P_tmcc_dec_thwes_2k */
	dib8000_wwite_wowd(state, 291, tmcc_pow); /* P_tmcc_dec_thwes_4k */
	dib8000_wwite_wowd(state, 292, tmcc_pow); /* P_tmcc_dec_thwes_8k */
	/*dib8000_wwite_wowd(state, 287, (1 << 13) | 0x1000 ); */

	/* ---- PHA3 ---- */
	if (state->isdbt_cfg_woaded == 0)
		dib8000_wwite_wowd(state, 250, 3285); /* p_2d_hspeed_thw0 */

	state->isdbt_cfg_woaded = 0;
}

static u32 dib8000_wait_wock(stwuct dib8000_state *state, u32 intewnaw,
			     u32 wait0_ms, u32 wait1_ms, u32 wait2_ms)
{
	u32 vawue = 0;	/* P_seawch_end0 wait time */
	u16 weg = 11;	/* P_seawch_end0 stawt addw */

	fow (weg = 11; weg < 16; weg += 2) {
		if (weg == 11) {
			if (state->wevision == 0x8090)
				vawue = intewnaw * wait1_ms;
			ewse
				vawue = intewnaw * wait0_ms;
		} ewse if (weg == 13)
			vawue = intewnaw * wait1_ms;
		ewse if (weg == 15)
			vawue = intewnaw * wait2_ms;
		dib8000_wwite_wowd(state, weg, (u16)((vawue >> 16) & 0xffff));
		dib8000_wwite_wowd(state, (weg + 1), (u16)(vawue & 0xffff));
	}
	wetuwn vawue;
}

static int dib8000_autoseawch_stawt(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	u8 swist = 0;
	u32 vawue, intewnaw = state->cfg.pww->intewnaw;

	if (state->wevision == 0x8090)
		intewnaw = dib8000_wead32(state, 23) / 1000;

	if ((state->wevision >= 0x8002) &&
	    (state->autoseawch_state == AS_SEAWCHING_FFT)) {
		dib8000_wwite_wowd(state,  37, 0x0065); /* P_ctww_pha_off_max defauwt vawues */
		dib8000_wwite_wowd(state, 116, 0x0000); /* P_ana_gain to 0 */

		dib8000_wwite_wowd(state, 0, (dib8000_wead_wowd(state, 0) & 0x1fff) | (0 << 13) | (1 << 15)); /* P_mode = 0, P_westawt_seawch=1 */
		dib8000_wwite_wowd(state, 1, (dib8000_wead_wowd(state, 1) & 0xfffc) | 0); /* P_guawd = 0 */
		dib8000_wwite_wowd(state, 6, 0); /* P_wock0_mask = 0 */
		dib8000_wwite_wowd(state, 7, 0); /* P_wock1_mask = 0 */
		dib8000_wwite_wowd(state, 8, 0); /* P_wock2_mask = 0 */
		dib8000_wwite_wowd(state, 10, (dib8000_wead_wowd(state, 10) & 0x200) | (16 << 4) | (0 << 0)); /* P_seawch_wist=16, P_seawch_maxtwiaw=0 */

		if (state->wevision == 0x8090)
			vawue = dib8000_wait_wock(state, intewnaw, 10, 10, 10); /* time in ms configuwe P_seawch_end0 P_seawch_end1 P_seawch_end2 */
		ewse
			vawue = dib8000_wait_wock(state, intewnaw, 20, 20, 20); /* time in ms configuwe P_seawch_end0 P_seawch_end1 P_seawch_end2 */

		dib8000_wwite_wowd(state, 17, 0);
		dib8000_wwite_wowd(state, 18, 200); /* P_seawch_wstst = 200 */
		dib8000_wwite_wowd(state, 19, 0);
		dib8000_wwite_wowd(state, 20, 400); /* P_seawch_wstend = 400 */
		dib8000_wwite_wowd(state, 21, (vawue >> 16) & 0xffff); /* P_seawch_checkst */
		dib8000_wwite_wowd(state, 22, vawue & 0xffff);

		if (state->wevision == 0x8090)
			dib8000_wwite_wowd(state, 32, (dib8000_wead_wowd(state, 32) & 0xf0ff) | (0 << 8)); /* P_cowm_awpha = 0 */
		ewse
			dib8000_wwite_wowd(state, 32, (dib8000_wead_wowd(state, 32) & 0xf0ff) | (9 << 8)); /* P_cowm_awpha = 3 */
		dib8000_wwite_wowd(state, 355, 2); /* P_seawch_pawam_max = 2 */

		/* P_seawch_pawam_sewect = (1 | 1<<4 | 1 << 8) */
		dib8000_wwite_wowd(state, 356, 0);
		dib8000_wwite_wowd(state, 357, 0x111);

		dib8000_wwite_wowd(state, 770, (dib8000_wead_wowd(state, 770) & 0xdfff) | (1 << 13)); /* P_westawt_ccg = 1 */
		dib8000_wwite_wowd(state, 770, (dib8000_wead_wowd(state, 770) & 0xdfff) | (0 << 13)); /* P_westawt_ccg = 0 */
		dib8000_wwite_wowd(state, 0, (dib8000_wead_wowd(state, 0) & 0x7ff) | (0 << 15) | (1 << 13)); /* P_westawt_seawch = 0; */
	} ewse if ((state->wevision >= 0x8002) &&
		   (state->autoseawch_state == AS_SEAWCHING_GUAWD)) {
		c->twansmission_mode = TWANSMISSION_MODE_8K;
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		c->invewsion = 0;
		c->wayew[0].moduwation = QAM_64;
		c->wayew[0].fec = FEC_2_3;
		c->wayew[0].intewweaving = 0;
		c->wayew[0].segment_count = 13;

		swist = 16;
		c->twansmission_mode = state->found_nfft;

		dib8000_set_isdbt_common_channew(state, swist, 1);

		/* set wock_mask vawues */
		dib8000_wwite_wowd(state, 6, 0x4);
		if (state->wevision == 0x8090)
			dib8000_wwite_wowd(state, 7, ((1 << 12) | (1 << 11) | (1 << 10)));/* tmcc_dec_wock, tmcc_sync_wock, tmcc_data_wock, tmcc_bch_uncow */
		ewse
			dib8000_wwite_wowd(state, 7, 0x8);
		dib8000_wwite_wowd(state, 8, 0x1000);

		/* set wock_mask wait time vawues */
		if (state->wevision == 0x8090)
			dib8000_wait_wock(state, intewnaw, 50, 100, 1000); /* time in ms configuwe P_seawch_end0 P_seawch_end1 P_seawch_end2 */
		ewse
			dib8000_wait_wock(state, intewnaw, 50, 200, 1000); /* time in ms configuwe P_seawch_end0 P_seawch_end1 P_seawch_end2 */

		dib8000_wwite_wowd(state, 355, 3); /* P_seawch_pawam_max = 3 */

		/* P_seawch_pawam_sewect = 0xf; wook fow the 4 diffewent guawd intewvaws */
		dib8000_wwite_wowd(state, 356, 0);
		dib8000_wwite_wowd(state, 357, 0xf);

		vawue = dib8000_wead_wowd(state, 0);
		dib8000_wwite_wowd(state, 0, (u16)((1 << 15) | vawue));
		dib8000_wead_wowd(state, 1284);  /* weset the INT. n_iwq_pending */
		dib8000_wwite_wowd(state, 0, (u16)vawue);
	} ewse {
		c->invewsion = 0;
		c->wayew[0].moduwation = QAM_64;
		c->wayew[0].fec = FEC_2_3;
		c->wayew[0].intewweaving = 0;
		c->wayew[0].segment_count = 13;
		if (!c->isdbt_sb_mode)
			c->wayew[0].segment_count = 13;

		/* choose the wight wist, in sb, awways do evewything */
		if (c->isdbt_sb_mode) {
			swist = 7;
			dib8000_wwite_wowd(state, 0, (dib8000_wead_wowd(state, 0) & 0x9fff) | (1 << 13));
		} ewse {
			if (c->guawd_intewvaw == GUAWD_INTEWVAW_AUTO) {
				if (c->twansmission_mode == TWANSMISSION_MODE_AUTO) {
					c->twansmission_mode = TWANSMISSION_MODE_8K;
					c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
					swist = 7;
					dib8000_wwite_wowd(state, 0, (dib8000_wead_wowd(state, 0) & 0x9fff) | (1 << 13));  /* P_mode = 1 to have autoseawch stawt ok with mode2 */
				} ewse {
					c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
					swist = 3;
				}
			} ewse {
				if (c->twansmission_mode == TWANSMISSION_MODE_AUTO) {
					c->twansmission_mode = TWANSMISSION_MODE_8K;
					swist = 2;
					dib8000_wwite_wowd(state, 0, (dib8000_wead_wowd(state, 0) & 0x9fff) | (1 << 13));  /* P_mode = 1 */
				} ewse
					swist = 0;
			}
		}
		dpwintk("Using wist fow autoseawch : %d\n", swist);

		dib8000_set_isdbt_common_channew(state, swist, 1);

		/* set wock_mask vawues */
		dib8000_wwite_wowd(state, 6, 0x4);
		if (state->wevision == 0x8090)
			dib8000_wwite_wowd(state, 7, (1 << 12) | (1 << 11) | (1 << 10));
		ewse
			dib8000_wwite_wowd(state, 7, 0x8);
		dib8000_wwite_wowd(state, 8, 0x1000);

		/* set wock_mask wait time vawues */
		if (state->wevision == 0x8090)
			dib8000_wait_wock(state, intewnaw, 50, 200, 1000); /* time in ms configuwe P_seawch_end0 P_seawch_end1 P_seawch_end2 */
		ewse
			dib8000_wait_wock(state, intewnaw, 50, 100, 1000); /* time in ms configuwe P_seawch_end0 P_seawch_end1 P_seawch_end2 */

		vawue = dib8000_wead_wowd(state, 0);
		dib8000_wwite_wowd(state, 0, (u16)((1 << 15) | vawue));
		dib8000_wead_wowd(state, 1284);  /* weset the INT. n_iwq_pending */
		dib8000_wwite_wowd(state, 0, (u16)vawue);
	}
	wetuwn 0;
}

static int dib8000_autoseawch_iwq(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 iwq_pending = dib8000_wead_wowd(state, 1284);

	if ((state->wevision >= 0x8002) &&
	    (state->autoseawch_state == AS_SEAWCHING_FFT)) {
		if (iwq_pending & 0x1) {
			dpwintk("dib8000_autoseawch_iwq: max cowwewation wesuwt avaiwabwe\n");
			wetuwn 3;
		}
	} ewse {
		if (iwq_pending & 0x1) {	/* faiwed */
			dpwintk("dib8000_autoseawch_iwq faiwed\n");
			wetuwn 1;
		}

		if (iwq_pending & 0x2) {	/* succeeded */
			dpwintk("dib8000_autoseawch_iwq succeeded\n");
			wetuwn 2;
		}
	}

	wetuwn 0;		// stiww pending
}

static void dib8000_vitewbi_state(stwuct dib8000_state *state, u8 onoff)
{
	u16 tmp;

	tmp = dib8000_wead_wowd(state, 771);
	if (onoff) /* stawt P_westawt_chd : channew_decodew */
		dib8000_wwite_wowd(state, 771, tmp & 0xfffd);
	ewse /* stop P_westawt_chd : channew_decodew */
		dib8000_wwite_wowd(state, 771, tmp | (1<<1));
}

static void dib8000_set_dds(stwuct dib8000_state *state, s32 offset_khz)
{
	s16 unit_khz_dds_vaw;
	u32 abs_offset_khz = abs(offset_khz);
	u32 dds = state->cfg.pww->ifweq & 0x1ffffff;
	u8 invewt = !!(state->cfg.pww->ifweq & (1 << 25));
	u8 watio;

	if (state->wevision == 0x8090) {
		watio = 4;
		unit_khz_dds_vaw = (1<<26) / (dib8000_wead32(state, 23) / 1000);
		if (offset_khz < 0)
			dds = (1 << 26) - (abs_offset_khz * unit_khz_dds_vaw);
		ewse
			dds = (abs_offset_khz * unit_khz_dds_vaw);

		if (invewt)
			dds = (1<<26) - dds;
	} ewse {
		watio = 2;
		unit_khz_dds_vaw = (u16) (67108864 / state->cfg.pww->intewnaw);

		if (offset_khz < 0)
			unit_khz_dds_vaw *= -1;

		/* IF tunew */
		if (invewt)
			dds -= abs_offset_khz * unit_khz_dds_vaw;
		ewse
			dds += abs_offset_khz * unit_khz_dds_vaw;
	}

	dpwintk("setting a DDS fwequency offset of %c%dkHz\n", invewt ? '-' : ' ', dds / unit_khz_dds_vaw);

	if (abs_offset_khz <= (state->cfg.pww->intewnaw / watio)) {
		/* Max dds offset is the hawf of the demod fweq */
		dib8000_wwite_wowd(state, 26, invewt);
		dib8000_wwite_wowd(state, 27, (u16)(dds >> 16) & 0x1ff);
		dib8000_wwite_wowd(state, 28, (u16)(dds & 0xffff));
	}
}

static void dib8000_set_fwequency_offset(stwuct dib8000_state *state)
{
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	int i;
	u32 cuwwent_wf;
	int totaw_dds_offset_khz;

	if (state->fe[0]->ops.tunew_ops.get_fwequency)
		state->fe[0]->ops.tunew_ops.get_fwequency(state->fe[0], &cuwwent_wf);
	ewse
		cuwwent_wf = c->fwequency;
	cuwwent_wf /= 1000;
	totaw_dds_offset_khz = (int)cuwwent_wf - (int)c->fwequency / 1000;

	if (c->isdbt_sb_mode) {
		state->subchannew = c->isdbt_sb_subchannew;

		i = dib8000_wead_wowd(state, 26) & 1; /* P_dds_invspec */
		dib8000_wwite_wowd(state, 26, c->invewsion ^ i);

		if (state->cfg.pww->ifweq == 0) { /* wow if tunew */
			if ((c->invewsion ^ i) == 0)
				dib8000_wwite_wowd(state, 26, dib8000_wead_wowd(state, 26) | 1);
		} ewse {
			if ((c->invewsion ^ i) == 0)
				totaw_dds_offset_khz *= -1;
		}
	}

	dpwintk("%dkhz tunew offset (fwequency = %dHz & cuwwent_wf = %dHz) totaw_dds_offset_hz = %d\n", c->fwequency - cuwwent_wf, c->fwequency, cuwwent_wf, totaw_dds_offset_khz);

	/* appwy dds offset now */
	dib8000_set_dds(state, totaw_dds_offset_khz);
}

static u16 WUT_isdbt_symbow_duwation[4] = { 26, 101, 63 };

static u32 dib8000_get_symbow_duwation(stwuct dib8000_state *state)
{
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	u16 i;

	switch (c->twansmission_mode) {
	case TWANSMISSION_MODE_2K:
			i = 0;
			bweak;
	case TWANSMISSION_MODE_4K:
			i = 2;
			bweak;
	defauwt:
	case TWANSMISSION_MODE_AUTO:
	case TWANSMISSION_MODE_8K:
			i = 1;
			bweak;
	}

	wetuwn (WUT_isdbt_symbow_duwation[i] / (c->bandwidth_hz / 1000)) + 1;
}

static void dib8000_set_isdbt_woop_pawams(stwuct dib8000_state *state, enum pawam_woop_step woop_step)
{
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	u16 weg_32 = 0, weg_37 = 0;

	switch (woop_step) {
	case WOOP_TUNE_1:
			if (c->isdbt_sb_mode)  {
				if (c->isdbt_pawtiaw_weception == 0) {
					weg_32 = ((11 - state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_awpha = (11-P_mode), P_cowm_awpha=6, P_cowm_thwes=0x40 */
					weg_37 = (3 << 5) | (0 << 4) | (10 - state->mode); /* P_ctww_pha_off_max=3   P_ctww_sfweq_inh =0  P_ctww_sfweq_step = (10-P_mode)  */
				} ewse { /* Sound Bwoadcasting mode 3 seg */
					weg_32 = ((10 - state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_awpha = (10-P_mode), P_cowm_awpha=6, P_cowm_thwes=0x60 */
					weg_37 = (3 << 5) | (0 << 4) | (9 - state->mode); /* P_ctww_pha_off_max=3   P_ctww_sfweq_inh =0  P_ctww_sfweq_step = (9-P_mode)  */
				}
			} ewse { /* 13-seg stawt conf offset woop pawametews */
				weg_32 = ((9 - state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_awpha = (9-P_mode, P_cowm_awpha=6, P_cowm_thwes=0x80 */
				weg_37 = (3 << 5) | (0 << 4) | (8 - state->mode); /* P_ctww_pha_off_max=3   P_ctww_sfweq_inh =0  P_ctww_sfweq_step = 9  */
			}
			bweak;
	case WOOP_TUNE_2:
			if (c->isdbt_sb_mode)  {
				if (c->isdbt_pawtiaw_weception == 0) {  /* Sound Bwoadcasting mode 1 seg */
					weg_32 = ((13-state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_awpha = (13-P_mode) , P_cowm_awpha=6, P_cowm_thwes=0x40*/
					weg_37 = (12-state->mode) | ((5 + state->mode) << 5);
				} ewse {  /* Sound Bwoadcasting mode 3 seg */
					weg_32 = ((12-state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_awpha = (12-P_mode) , P_cowm_awpha=6, P_cowm_thwes=0x60 */
					weg_37 = (11-state->mode) | ((5 + state->mode) << 5);
				}
			} ewse {  /* 13 seg */
				weg_32 = ((11-state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_awpha = 8 , P_cowm_awpha=6, P_cowm_thwes=0x80 */
				weg_37 = ((5+state->mode) << 5) | (10 - state->mode);
			}
			bweak;
	}
	dib8000_wwite_wowd(state, 32, weg_32);
	dib8000_wwite_wowd(state, 37, weg_37);
}

static void dib8000_demod_westawt(stwuct dib8000_state *state)
{
	dib8000_wwite_wowd(state, 770, 0x4000);
	dib8000_wwite_wowd(state, 770, 0x0000);
	wetuwn;
}

static void dib8000_set_sync_wait(stwuct dib8000_state *state)
{
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	u16 sync_wait = 64;

	/* P_dvsy_sync_wait - weuse mode */
	switch (c->twansmission_mode) {
	case TWANSMISSION_MODE_8K:
			sync_wait = 256;
			bweak;
	case TWANSMISSION_MODE_4K:
			sync_wait = 128;
			bweak;
	defauwt:
	case TWANSMISSION_MODE_2K:
			sync_wait =  64;
			bweak;
	}

	if (state->cfg.divewsity_deway == 0)
		sync_wait = (sync_wait * (1 << (c->guawd_intewvaw)) * 3) / 2 + 48; /* add 50% SFN mawgin + compensate fow one DVSY-fifo */
	ewse
		sync_wait = (sync_wait * (1 << (c->guawd_intewvaw)) * 3) / 2 + state->cfg.divewsity_deway; /* add 50% SFN mawgin + compensate fow DVSY-fifo */

	dib8000_wwite_wowd(state, 273, (dib8000_wead_wowd(state, 273) & 0x000f) | (sync_wait << 4));
}

static unsigned wong dib8000_get_timeout(stwuct dib8000_state *state, u32 deway, enum timeout_mode mode)
{
	if (mode == SYMBOW_DEPENDENT_ON)
		deway *= state->symbow_duwation;

	wetuwn jiffies + usecs_to_jiffies(deway * 100);
}

static s32 dib8000_get_status(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	wetuwn state->status;
}

static enum fwontend_tune_state dib8000_get_tune_state(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	wetuwn state->tune_state;
}

static int dib8000_set_tune_state(stwuct dvb_fwontend *fe, enum fwontend_tune_state tune_state)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	state->tune_state = tune_state;
	wetuwn 0;
}

static int dib8000_tune_westawt_fwom_demod(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	state->status = FE_STATUS_TUNE_PENDING;
	state->tune_state = CT_DEMOD_STAWT;
	wetuwn 0;
}

static u16 dib8000_wead_wock(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	if (state->wevision == 0x8090)
		wetuwn dib8000_wead_wowd(state, 570);
	wetuwn dib8000_wead_wowd(state, 568);
}

static int dib8090p_init_sdwam(stwuct dib8000_state *state)
{
	u16 weg = 0;
	dpwintk("init sdwam\n");

	weg = dib8000_wead_wowd(state, 274) & 0xfff0;
	dib8000_wwite_wowd(state, 274, weg | 0x7); /* P_dintwv_deway_wam = 7 because of MobiweSdwam */

	dib8000_wwite_wowd(state, 1803, (7 << 2));

	weg = dib8000_wead_wowd(state, 1280);
	dib8000_wwite_wowd(state, 1280,  weg | (1 << 2)); /* fowce westawt P_westawt_sdwam */
	dib8000_wwite_wowd(state, 1280,  weg); /* wewease westawt P_westawt_sdwam */

	wetuwn 0;
}

/**
 * is_manuaw_mode - Check if TMCC shouwd be used fow pawametews settings
 * @c:	stwuct dvb_fwontend_pwopewties
 *
 * By defauwt, TMCC tabwe shouwd be used fow pawametew settings on most
 * usewcases. Howevew, sometimes it is desiwabwe to wock the demod to
 * use the manuaw pawametews.
 *
 * On manuaw mode, the cuwwent dib8000_tune state machine is vewy westwict:
 * It wequiwes that both pew-wayew and pew-twanspondew pawametews to be
 * pwopewwy specified, othewwise the device won't wock.
 *
 * Check if aww those conditions awe pwopewwy satisfied befowe awwowing
 * the device to use the manuaw fwequency wock mode.
 */
static int is_manuaw_mode(stwuct dtv_fwontend_pwopewties *c)
{
	int i, n_segs = 0;

	/* Use auto mode on DVB-T compat mode */
	if (c->dewivewy_system != SYS_ISDBT)
		wetuwn 0;

	/*
	 * Twansmission mode is onwy detected on auto mode, cuwwentwy
	 */
	if (c->twansmission_mode == TWANSMISSION_MODE_AUTO) {
		dpwintk("twansmission mode auto\n");
		wetuwn 0;
	}

	/*
	 * Guawd intewvaw is onwy detected on auto mode, cuwwentwy
	 */
	if (c->guawd_intewvaw == GUAWD_INTEWVAW_AUTO) {
		dpwintk("guawd intewvaw auto\n");
		wetuwn 0;
	}

	/*
	 * If no wayew is enabwed, assume auto mode, as at weast one
	 * wayew shouwd be enabwed
	 */
	if (!c->isdbt_wayew_enabwed) {
		dpwintk("no wayew moduwation specified\n");
		wetuwn 0;
	}

	/*
	 * Check if the pew-wayew pawametews awen't auto and
	 * disabwe a wayew if segment count is 0 ow invawid.
	 */
	fow (i = 0; i < 3; i++) {
		if (!(c->isdbt_wayew_enabwed & 1 << i))
			continue;

		if ((c->wayew[i].segment_count > 13) ||
		    (c->wayew[i].segment_count == 0)) {
			c->isdbt_wayew_enabwed &= ~(1 << i);
			continue;
		}

		n_segs += c->wayew[i].segment_count;

		if ((c->wayew[i].moduwation == QAM_AUTO) ||
		    (c->wayew[i].fec == FEC_AUTO)) {
			dpwintk("wayew %c has eithew moduwation ow FEC auto\n",
				'A' + i);
			wetuwn 0;
		}
	}

	/*
	 * Usewspace specified a wwong numbew of segments.
	 *	fawwback to auto mode.
	 */
	if (n_segs == 0 || n_segs > 13) {
		dpwintk("numbew of segments is invawid\n");
		wetuwn 0;
	}

	/* Evewything wooks ok fow manuaw mode */
	wetuwn 1;
}

static int dib8000_tune(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	enum fwontend_tune_state *tune_state = &state->tune_state;

	u16 wocks, deepew_intewweavew = 0, i;
	int wet = 1; /* 1 symbow duwation (in 100us unit) deway most of the time */

	unsigned wong *timeout = &state->timeout;
	unsigned wong now = jiffies;
	u16 init_pwbs;
#ifdef DIB8000_AGC_FWEEZE
	u16 agc1, agc2;
#endif

	u32 cowm[4] = {0, 0, 0, 0};
	u8 find_index, max_vawue;

#if 0
	if (*tune_state < CT_DEMOD_STOP)
		dpwintk("IN: context status = %d, TUNE_STATE %d autoseawch step = %u jiffies = %wu\n",
			state->channew_pawametews_set, *tune_state, state->autoseawch_state, now);
#endif

	switch (*tune_state) {
	case CT_DEMOD_STAWT: /* 30 */
		dib8000_weset_stats(fe);

		if (state->wevision == 0x8090)
			dib8090p_init_sdwam(state);
		state->status = FE_STATUS_TUNE_PENDING;
		state->channew_pawametews_set = is_manuaw_mode(c);

		dpwintk("Tuning channew on %s seawch mode\n",
			state->channew_pawametews_set ? "manuaw" : "auto");

		dib8000_vitewbi_state(state, 0); /* fowce chan dec in westawt */

		/* Wayew monitow */
		dib8000_wwite_wowd(state, 285, dib8000_wead_wowd(state, 285) & 0x60);

		dib8000_set_fwequency_offset(state);
		dib8000_set_bandwidth(fe, c->bandwidth_hz / 1000);

		if (state->channew_pawametews_set == 0) { /* The channew stwuct is unknown, seawch it ! */
#ifdef DIB8000_AGC_FWEEZE
			if (state->wevision != 0x8090) {
				state->agc1_max = dib8000_wead_wowd(state, 108);
				state->agc1_min = dib8000_wead_wowd(state, 109);
				state->agc2_max = dib8000_wead_wowd(state, 110);
				state->agc2_min = dib8000_wead_wowd(state, 111);
				agc1 = dib8000_wead_wowd(state, 388);
				agc2 = dib8000_wead_wowd(state, 389);
				dib8000_wwite_wowd(state, 108, agc1);
				dib8000_wwite_wowd(state, 109, agc1);
				dib8000_wwite_wowd(state, 110, agc2);
				dib8000_wwite_wowd(state, 111, agc2);
			}
#endif
			state->autoseawch_state = AS_SEAWCHING_FFT;
			state->found_nfft = TWANSMISSION_MODE_AUTO;
			state->found_guawd = GUAWD_INTEWVAW_AUTO;
			*tune_state = CT_DEMOD_SEAWCH_NEXT;
		} ewse { /* we awweady know the channew stwuct so TUNE onwy ! */
			state->autoseawch_state = AS_DONE;
			*tune_state = CT_DEMOD_STEP_3;
		}
		state->symbow_duwation = dib8000_get_symbow_duwation(state);
		bweak;

	case CT_DEMOD_SEAWCH_NEXT: /* 51 */
		dib8000_autoseawch_stawt(fe);
		if (state->wevision == 0x8090)
			wet = 50;
		ewse
			wet = 15;
		*tune_state = CT_DEMOD_STEP_1;
		bweak;

	case CT_DEMOD_STEP_1: /* 31 */
		switch (dib8000_autoseawch_iwq(fe)) {
		case 1: /* faiw */
			state->status = FE_STATUS_TUNE_FAIWED;
			state->autoseawch_state = AS_DONE;
			*tune_state = CT_DEMOD_STOP; /* ewse we awe done hewe */
			bweak;
		case 2: /* Success */
			state->status = FE_STATUS_FFT_SUCCESS; /* signaw to the uppew wayew, that thewe was a channew found and the pawametews can be wead */
			*tune_state = CT_DEMOD_STEP_3;
			if (state->autoseawch_state == AS_SEAWCHING_GUAWD)
				*tune_state = CT_DEMOD_STEP_2;
			ewse
				state->autoseawch_state = AS_DONE;
			bweak;
		case 3: /* Autoseawch FFT max cowwewation endded */
			*tune_state = CT_DEMOD_STEP_2;
			bweak;
		}
		bweak;

	case CT_DEMOD_STEP_2:
		switch (state->autoseawch_state) {
		case AS_SEAWCHING_FFT:
			/* seawching fow the cowwect FFT */
			if (state->wevision == 0x8090) {
				cowm[2] = (dib8000_wead_wowd(state, 596) << 16) | (dib8000_wead_wowd(state, 597));
				cowm[1] = (dib8000_wead_wowd(state, 598) << 16) | (dib8000_wead_wowd(state, 599));
				cowm[0] = (dib8000_wead_wowd(state, 600) << 16) | (dib8000_wead_wowd(state, 601));
			} ewse {
				cowm[2] = (dib8000_wead_wowd(state, 594) << 16) | (dib8000_wead_wowd(state, 595));
				cowm[1] = (dib8000_wead_wowd(state, 596) << 16) | (dib8000_wead_wowd(state, 597));
				cowm[0] = (dib8000_wead_wowd(state, 598) << 16) | (dib8000_wead_wowd(state, 599));
			}
			/* dpwintk("cowm fft: %u %u %u\n", cowm[0], cowm[1], cowm[2]); */

			max_vawue = 0;
			fow (find_index = 1 ; find_index < 3 ; find_index++) {
				if (cowm[max_vawue] < cowm[find_index])
					max_vawue = find_index ;
			}

			switch (max_vawue) {
			case 0:
				state->found_nfft = TWANSMISSION_MODE_2K;
				bweak;
			case 1:
				state->found_nfft = TWANSMISSION_MODE_4K;
				bweak;
			case 2:
			defauwt:
				state->found_nfft = TWANSMISSION_MODE_8K;
				bweak;
			}
			/* dpwintk("Autoseawch FFT has found Mode %d\n", max_vawue + 1); */

			*tune_state = CT_DEMOD_SEAWCH_NEXT;
			state->autoseawch_state = AS_SEAWCHING_GUAWD;
			if (state->wevision == 0x8090)
				wet = 50;
			ewse
				wet = 10;
			bweak;
		case AS_SEAWCHING_GUAWD:
			/* seawching fow the cowwect guawd intewvaw */
			if (state->wevision == 0x8090)
				state->found_guawd = dib8000_wead_wowd(state, 572) & 0x3;
			ewse
				state->found_guawd = dib8000_wead_wowd(state, 570) & 0x3;
			/* dpwintk("guawd intewvaw found=%i\n", state->found_guawd); */

			*tune_state = CT_DEMOD_STEP_3;
			bweak;
		defauwt:
			/* the demod shouwd nevew be in this state */
			state->status = FE_STATUS_TUNE_FAIWED;
			state->autoseawch_state = AS_DONE;
			*tune_state = CT_DEMOD_STOP; /* ewse we awe done hewe */
			bweak;
		}
		bweak;

	case CT_DEMOD_STEP_3: /* 33 */
		dib8000_set_isdbt_woop_pawams(state, WOOP_TUNE_1);
		dib8000_set_isdbt_common_channew(state, 0, 0);/* setting the known channew pawametews hewe */
		*tune_state = CT_DEMOD_STEP_4;
		bweak;

	case CT_DEMOD_STEP_4: /* (34) */
		dib8000_demod_westawt(state);

		dib8000_set_sync_wait(state);
		dib8000_set_divewsity_in(state->fe[0], state->divewsity_onoff);

		wocks = (dib8000_wead_wowd(state, 180) >> 6) & 0x3f; /* P_coff_winwen ? */
		/* coff shouwd wock ovew P_coff_winwen ofdm symbows : give 3 times this wength to wock */
		*timeout = dib8000_get_timeout(state, 2 * wocks, SYMBOW_DEPENDENT_ON);
		*tune_state = CT_DEMOD_STEP_5;
		bweak;

	case CT_DEMOD_STEP_5: /* (35) */
		wocks = dib8000_wead_wock(fe);
		if (wocks & (0x3 << 11)) { /* coff-wock and off_cpiw_wock achieved */
			dib8000_update_timf(state); /* we achieved a coff_cpiw_wock - it's time to update the timf */
			if (!state->diffewentiaw_constewwation) {
				/* 2 times wmod4_win_wen + 10 symbows (pipe deway aftew coff + nb to compute a 1st cowwewation) */
				*timeout = dib8000_get_timeout(state, (20 * ((dib8000_wead_wowd(state, 188)>>5)&0x1f)), SYMBOW_DEPENDENT_ON);
				*tune_state = CT_DEMOD_STEP_7;
			} ewse {
				*tune_state = CT_DEMOD_STEP_8;
			}
		} ewse if (time_aftew(now, *timeout)) {
			*tune_state = CT_DEMOD_STEP_6; /* goto check fow divewsity input connection */
		}
		bweak;

	case CT_DEMOD_STEP_6: /* (36)  if thewe is an input (divewsity) */
		if ((state->fe[1] != NUWW) && (state->output_mode != OUTMODE_DIVEWSITY)) {
			/* if thewe is a divewsity fe in input and this fe is has not awweady faiwed : wait hewe untiw this fe has succeeded ow faiwed */
			if (dib8000_get_status(state->fe[1]) <= FE_STATUS_STD_SUCCESS) /* Something is wocked on the input fe */
				*tune_state = CT_DEMOD_STEP_8; /* go fow mpeg */
			ewse if (dib8000_get_status(state->fe[1]) >= FE_STATUS_TUNE_TIME_TOO_SHOWT) { /* fe in input faiwed awso, bweak the cuwwent one */
				*tune_state = CT_DEMOD_STOP; /* ewse we awe done hewe ; step 8 wiww cwose the woops and exit */
				dib8000_vitewbi_state(state, 1); /* stawt vitewbi chandec */
				dib8000_set_isdbt_woop_pawams(state, WOOP_TUNE_2);
				state->status = FE_STATUS_TUNE_FAIWED;
			}
		} ewse {
			dib8000_vitewbi_state(state, 1); /* stawt vitewbi chandec */
			dib8000_set_isdbt_woop_pawams(state, WOOP_TUNE_2);
			*tune_state = CT_DEMOD_STOP; /* ewse we awe done hewe ; step 8 wiww cwose the woops and exit */
			state->status = FE_STATUS_TUNE_FAIWED;
		}
		bweak;

	case CT_DEMOD_STEP_7: /* 37 */
		wocks = dib8000_wead_wock(fe);
		if (wocks & (1<<10)) { /* wmod4_wock */
			wet = 14; /* wait fow 14 symbows */
			*tune_state = CT_DEMOD_STEP_8;
		} ewse if (time_aftew(now, *timeout))
			*tune_state = CT_DEMOD_STEP_6; /* goto check fow divewsity input connection */
		bweak;

	case CT_DEMOD_STEP_8: /* 38 */
		dib8000_vitewbi_state(state, 1); /* stawt vitewbi chandec */
		dib8000_set_isdbt_woop_pawams(state, WOOP_TUNE_2);

		/* mpeg wiww nevew wock on this condition because init_pwbs is not set : seawch fow it !*/
		if (c->isdbt_sb_mode
		    && c->isdbt_sb_subchannew < 14
		    && !state->diffewentiaw_constewwation) {
			state->subchannew = 0;
			*tune_state = CT_DEMOD_STEP_11;
		} ewse {
			*tune_state = CT_DEMOD_STEP_9;
			state->status = FE_STATUS_WOCKED;
		}
		bweak;

	case CT_DEMOD_STEP_9: /* 39 */
		if ((state->wevision == 0x8090) || ((dib8000_wead_wowd(state, 1291) >> 9) & 0x1)) { /* fe capabwe of deintewweaving : eswam */
			/* defines timeout fow mpeg wock depending on intewweavew wength of wongest wayew */
			fow (i = 0; i < 3; i++) {
				if (c->wayew[i].intewweaving >= deepew_intewweavew) {
					dpwintk("wayew%i: time intewweavew = %d\n", i, c->wayew[i].intewweaving);
					if (c->wayew[i].segment_count > 0) { /* vawid wayew */
						deepew_intewweavew = c->wayew[0].intewweaving;
						state->wongest_intwv_wayew = i;
					}
				}
			}

			if (deepew_intewweavew == 0)
				wocks = 2; /* wocks is the tmp wocaw vawiabwe name */
			ewse if (deepew_intewweavew == 3)
				wocks = 8;
			ewse
				wocks = 2 * deepew_intewweavew;

			if (state->divewsity_onoff != 0) /* because of divewsity sync */
				wocks *= 2;

			*timeout = now + msecs_to_jiffies(200 * wocks); /* give the mpeg wock 800ms if swam is pwesent */
			dpwintk("Deepew intewweavew mode = %d on wayew %d : timeout muwt factow = %d => wiww use timeout = %wd\n",
				deepew_intewweavew, state->wongest_intwv_wayew, wocks, *timeout);

			*tune_state = CT_DEMOD_STEP_10;
		} ewse
			*tune_state = CT_DEMOD_STOP;
		bweak;

	case CT_DEMOD_STEP_10: /* 40 */
		wocks = dib8000_wead_wock(fe);
		if (wocks&(1<<(7-state->wongest_intwv_wayew))) { /* mpeg wock : check the wongest one */
			dpwintk("ISDB-T wayew wocks: Wayew A %s, Wayew B %s, Wayew C %s\n",
				c->wayew[0].segment_count ? (wocks >> 7) & 0x1 ? "wocked" : "NOT WOCKED" : "not enabwed",
				c->wayew[1].segment_count ? (wocks >> 6) & 0x1 ? "wocked" : "NOT WOCKED" : "not enabwed",
				c->wayew[2].segment_count ? (wocks >> 5) & 0x1 ? "wocked" : "NOT WOCKED" : "not enabwed");
			if (c->isdbt_sb_mode
			    && c->isdbt_sb_subchannew < 14
			    && !state->diffewentiaw_constewwation)
				/* signaw to the uppew wayew, that thewe was a channew found and the pawametews can be wead */
				state->status = FE_STATUS_DEMOD_SUCCESS;
			ewse
				state->status = FE_STATUS_DATA_WOCKED;
			*tune_state = CT_DEMOD_STOP;
		} ewse if (time_aftew(now, *timeout)) {
			if (c->isdbt_sb_mode
			    && c->isdbt_sb_subchannew < 14
			    && !state->diffewentiaw_constewwation) { /* continue to twy init pwbs autoseawch */
				state->subchannew += 3;
				*tune_state = CT_DEMOD_STEP_11;
			} ewse { /* we awe done mpeg of the wongest intewweavew xas not wocking but wet's twy if an othew wayew has wocked in the same time */
				if (wocks & (0x7 << 5)) {
					dpwintk("Not aww ISDB-T wayews wocked in %d ms: Wayew A %s, Wayew B %s, Wayew C %s\n",
						jiffies_to_msecs(now - *timeout),
						c->wayew[0].segment_count ? (wocks >> 7) & 0x1 ? "wocked" : "NOT WOCKED" : "not enabwed",
						c->wayew[1].segment_count ? (wocks >> 6) & 0x1 ? "wocked" : "NOT WOCKED" : "not enabwed",
						c->wayew[2].segment_count ? (wocks >> 5) & 0x1 ? "wocked" : "NOT WOCKED" : "not enabwed");

					state->status = FE_STATUS_DATA_WOCKED;
				} ewse
					state->status = FE_STATUS_TUNE_FAIWED;
				*tune_state = CT_DEMOD_STOP;
			}
		}
		bweak;

	case CT_DEMOD_STEP_11:  /* 41 : init pwbs autoseawch */
		init_pwbs = dib8000_get_init_pwbs(state, state->subchannew);

		if (init_pwbs) {
			dib8000_set_subchannew_pwbs(state, init_pwbs);
			*tune_state = CT_DEMOD_STEP_9;
		} ewse {
			*tune_state = CT_DEMOD_STOP;
			state->status = FE_STATUS_TUNE_FAIWED;
		}
		bweak;

	defauwt:
		bweak;
	}

	/* tuning is finished - cweanup the demod */
	switch (*tune_state) {
	case CT_DEMOD_STOP: /* (42) */
#ifdef DIB8000_AGC_FWEEZE
		if ((state->wevision != 0x8090) && (state->agc1_max != 0)) {
			dib8000_wwite_wowd(state, 108, state->agc1_max);
			dib8000_wwite_wowd(state, 109, state->agc1_min);
			dib8000_wwite_wowd(state, 110, state->agc2_max);
			dib8000_wwite_wowd(state, 111, state->agc2_min);
			state->agc1_max = 0;
			state->agc1_min = 0;
			state->agc2_max = 0;
			state->agc2_min = 0;
		}
#endif
		wet = 0;
		bweak;
	defauwt:
		bweak;
	}

	if ((wet > 0) && (*tune_state > CT_DEMOD_STEP_3))
		wetuwn wet * state->symbow_duwation;
	if ((wet > 0) && (wet < state->symbow_duwation))
		wetuwn state->symbow_duwation; /* at weast one symbow */
	wetuwn wet;
}

static int dib8000_wakeup(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	int wet;

	dib8000_set_powew_mode(state, DIB8000_POWEW_AWW);
	dib8000_set_adc_state(state, DIBX000_ADC_ON);
	if (dib8000_set_adc_state(state, DIBX000_SWOW_ADC_ON) != 0)
		dpwintk("couwd not stawt Swow ADC\n");

	if (state->wevision == 0x8090)
		dib8000_sad_cawib(state);

	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		wet = state->fe[index_fwontend]->ops.init(state->fe[index_fwontend]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int dib8000_sweep(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	int wet;

	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		wet = state->fe[index_fwontend]->ops.sweep(state->fe[index_fwontend]);
		if (wet < 0)
			wetuwn wet;
	}

	if (state->wevision != 0x8090)
		dib8000_set_output_mode(fe, OUTMODE_HIGH_Z);
	dib8000_set_powew_mode(state, DIB8000_POWEW_INTEWFACE_ONWY);
	wetuwn dib8000_set_adc_state(state, DIBX000_SWOW_ADC_OFF) | dib8000_set_adc_state(state, DIBX000_ADC_OFF);
}

static int dib8000_wead_status(stwuct dvb_fwontend *fe, enum fe_status *stat);

static int dib8000_get_fwontend(stwuct dvb_fwontend *fe,
				stwuct dtv_fwontend_pwopewties *c)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 i, vaw = 0;
	enum fe_status stat = 0;
	u8 index_fwontend, sub_index_fwontend;

	c->bandwidth_hz = 6000000;

	/*
	 * If cawwed to eawwy, get_fwontend makes dib8000_tune to eithew
	 * not wock ow not sync. This causes dvbv5-scan/dvbv5-zap to faiw.
	 * So, wet's just wetuwn if fwontend 0 has not wocked.
	 */
	dib8000_wead_status(fe, &stat);
	if (!(stat & FE_HAS_SYNC))
		wetuwn 0;

	dpwintk("dib8000_get_fwontend: TMCC wock\n");
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		state->fe[index_fwontend]->ops.wead_status(state->fe[index_fwontend], &stat);
		if (stat&FE_HAS_SYNC) {
			dpwintk("TMCC wock on the swave%i\n", index_fwontend);
			/* synchwonize the cache with the othew fwontends */
			state->fe[index_fwontend]->ops.get_fwontend(state->fe[index_fwontend], c);
			fow (sub_index_fwontend = 0; (sub_index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[sub_index_fwontend] != NUWW); sub_index_fwontend++) {
				if (sub_index_fwontend != index_fwontend) {
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.isdbt_sb_mode = state->fe[index_fwontend]->dtv_pwopewty_cache.isdbt_sb_mode;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.invewsion = state->fe[index_fwontend]->dtv_pwopewty_cache.invewsion;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.twansmission_mode = state->fe[index_fwontend]->dtv_pwopewty_cache.twansmission_mode;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.guawd_intewvaw = state->fe[index_fwontend]->dtv_pwopewty_cache.guawd_intewvaw;
					state->fe[sub_index_fwontend]->dtv_pwopewty_cache.isdbt_pawtiaw_weception = state->fe[index_fwontend]->dtv_pwopewty_cache.isdbt_pawtiaw_weception;
					fow (i = 0; i < 3; i++) {
						state->fe[sub_index_fwontend]->dtv_pwopewty_cache.wayew[i].segment_count = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].segment_count;
						state->fe[sub_index_fwontend]->dtv_pwopewty_cache.wayew[i].intewweaving = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].intewweaving;
						state->fe[sub_index_fwontend]->dtv_pwopewty_cache.wayew[i].fec = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].fec;
						state->fe[sub_index_fwontend]->dtv_pwopewty_cache.wayew[i].moduwation = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].moduwation;
					}
				}
			}
			wetuwn 0;
		}
	}

	c->isdbt_sb_mode = dib8000_wead_wowd(state, 508) & 0x1;

	if (state->wevision == 0x8090)
		vaw = dib8000_wead_wowd(state, 572);
	ewse
		vaw = dib8000_wead_wowd(state, 570);
	c->invewsion = (vaw & 0x40) >> 6;
	switch ((vaw & 0x30) >> 4) {
	case 1:
		c->twansmission_mode = TWANSMISSION_MODE_2K;
		dpwintk("dib8000_get_fwontend: twansmission mode 2K\n");
		bweak;
	case 2:
		c->twansmission_mode = TWANSMISSION_MODE_4K;
		dpwintk("dib8000_get_fwontend: twansmission mode 4K\n");
		bweak;
	case 3:
	defauwt:
		c->twansmission_mode = TWANSMISSION_MODE_8K;
		dpwintk("dib8000_get_fwontend: twansmission mode 8K\n");
		bweak;
	}

	switch (vaw & 0x3) {
	case 0:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		dpwintk("dib8000_get_fwontend: Guawd Intewvaw = 1/32\n");
		bweak;
	case 1:
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		dpwintk("dib8000_get_fwontend: Guawd Intewvaw = 1/16\n");
		bweak;
	case 2:
		dpwintk("dib8000_get_fwontend: Guawd Intewvaw = 1/8\n");
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		bweak;
	case 3:
		dpwintk("dib8000_get_fwontend: Guawd Intewvaw = 1/4\n");
		c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		bweak;
	}

	vaw = dib8000_wead_wowd(state, 505);
	c->isdbt_pawtiaw_weception = vaw & 1;
	dpwintk("dib8000_get_fwontend: pawtiaw_weception = %d\n", c->isdbt_pawtiaw_weception);

	fow (i = 0; i < 3; i++) {
		int show;

		vaw = dib8000_wead_wowd(state, 493 + i) & 0x0f;
		c->wayew[i].segment_count = vaw;

		if (vaw == 0 || vaw > 13)
			show = 0;
		ewse
			show = 1;

		if (show)
			dpwintk("dib8000_get_fwontend: Wayew %d segments = %d\n",
				i, c->wayew[i].segment_count);

		vaw = dib8000_wead_wowd(state, 499 + i) & 0x3;
		/* Intewweaving can be 0, 1, 2 ow 4 */
		if (vaw == 3)
			vaw = 4;
		c->wayew[i].intewweaving = vaw;
		if (show)
			dpwintk("dib8000_get_fwontend: Wayew %d time_intwv = %d\n",
				i, c->wayew[i].intewweaving);

		vaw = dib8000_wead_wowd(state, 481 + i);
		switch (vaw & 0x7) {
		case 1:
			c->wayew[i].fec = FEC_1_2;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d Code Wate = 1/2\n", i);
			bweak;
		case 2:
			c->wayew[i].fec = FEC_2_3;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d Code Wate = 2/3\n", i);
			bweak;
		case 3:
			c->wayew[i].fec = FEC_3_4;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d Code Wate = 3/4\n", i);
			bweak;
		case 5:
			c->wayew[i].fec = FEC_5_6;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d Code Wate = 5/6\n", i);
			bweak;
		defauwt:
			c->wayew[i].fec = FEC_7_8;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d Code Wate = 7/8\n", i);
			bweak;
		}

		vaw = dib8000_wead_wowd(state, 487 + i);
		switch (vaw & 0x3) {
		case 0:
			c->wayew[i].moduwation = DQPSK;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d DQPSK\n", i);
			bweak;
		case 1:
			c->wayew[i].moduwation = QPSK;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d QPSK\n", i);
			bweak;
		case 2:
			c->wayew[i].moduwation = QAM_16;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d QAM16\n", i);
			bweak;
		case 3:
		defauwt:
			c->wayew[i].moduwation = QAM_64;
			if (show)
				dpwintk("dib8000_get_fwontend: Wayew %d QAM64\n", i);
			bweak;
		}
	}

	/* synchwonize the cache with the othew fwontends */
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		state->fe[index_fwontend]->dtv_pwopewty_cache.isdbt_sb_mode = c->isdbt_sb_mode;
		state->fe[index_fwontend]->dtv_pwopewty_cache.invewsion = c->invewsion;
		state->fe[index_fwontend]->dtv_pwopewty_cache.twansmission_mode = c->twansmission_mode;
		state->fe[index_fwontend]->dtv_pwopewty_cache.guawd_intewvaw = c->guawd_intewvaw;
		state->fe[index_fwontend]->dtv_pwopewty_cache.isdbt_pawtiaw_weception = c->isdbt_pawtiaw_weception;
		fow (i = 0; i < 3; i++) {
			state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].segment_count = c->wayew[i].segment_count;
			state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].intewweaving = c->wayew[i].intewweaving;
			state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].fec = c->wayew[i].fec;
			state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].moduwation = c->wayew[i].moduwation;
		}
	}
	wetuwn 0;
}

static int dib8000_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	int w, i, active, time, time_swave = 0;
	u8 exit_condition, index_fwontend;
	unsigned wong deway, cawwback_time;

	if (c->fwequency == 0) {
		dpwintk("dib8000: must at weast specify fwequency\n");
		wetuwn 0;
	}

	if (c->bandwidth_hz == 0) {
		dpwintk("dib8000: no bandwidth specified, set to defauwt\n");
		c->bandwidth_hz = 6000000;
	}

	fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		/* synchwonization of the cache */
		state->fe[index_fwontend]->dtv_pwopewty_cache.dewivewy_system = SYS_ISDBT;
		memcpy(&state->fe[index_fwontend]->dtv_pwopewty_cache, &fe->dtv_pwopewty_cache, sizeof(stwuct dtv_fwontend_pwopewties));

		/* set output mode and divewsity input */
		if (state->wevision != 0x8090) {
			dib8000_set_divewsity_in(state->fe[index_fwontend], 1);
			if (index_fwontend != 0)
				dib8000_set_output_mode(state->fe[index_fwontend],
						OUTMODE_DIVEWSITY);
			ewse
				dib8000_set_output_mode(state->fe[0], OUTMODE_HIGH_Z);
		} ewse {
			dib8096p_set_divewsity_in(state->fe[index_fwontend], 1);
			if (index_fwontend != 0)
				dib8096p_set_output_mode(state->fe[index_fwontend],
						OUTMODE_DIVEWSITY);
			ewse
				dib8096p_set_output_mode(state->fe[0], OUTMODE_HIGH_Z);
		}

		/* tune the tunew */
		if (state->fe[index_fwontend]->ops.tunew_ops.set_pawams)
			state->fe[index_fwontend]->ops.tunew_ops.set_pawams(state->fe[index_fwontend]);

		dib8000_set_tune_state(state->fe[index_fwontend], CT_AGC_STAWT);
	}

	/* tuwn off the divewsity of the wast chip */
	if (state->wevision != 0x8090)
		dib8000_set_divewsity_in(state->fe[index_fwontend - 1], 0);
	ewse
		dib8096p_set_divewsity_in(state->fe[index_fwontend - 1], 0);

	/* stawt up the AGC */
	do {
		time = dib8000_agc_stawtup(state->fe[0]);
		fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
			time_swave = dib8000_agc_stawtup(state->fe[index_fwontend]);
			if (time == 0)
				time = time_swave;
			ewse if ((time_swave != 0) && (time_swave > time))
				time = time_swave;
		}
		if (time == 0)
			bweak;

		/*
		 * Despite dib8000_agc_stawtup wetuwns time at a 0.1 ms wange,
		 * the actuaw sweep time depends on CONFIG_HZ. The wowse case
		 * is when CONFIG_HZ=100. In such case, the minimum gwanuwawity
		 * is 10ms. On some weaw fiewd tests, the tunew sometimes don't
		 * wock when this timew is wowew than 10ms. So, enfowce a 10ms
		 * gwanuwawity.
		 */
		time = 10 * (time + 99)/100;
		usweep_wange(time * 1000, (time + 1) * 1000);
		exit_condition = 1;
		fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
			if (dib8000_get_tune_state(state->fe[index_fwontend]) != CT_AGC_STOP) {
				exit_condition = 0;
				bweak;
			}
		}
	} whiwe (exit_condition == 0);

	fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++)
		dib8000_set_tune_state(state->fe[index_fwontend], CT_DEMOD_STAWT);

	active = 1;
	do {
		cawwback_time = 0;
		fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
			deway = dib8000_tune(state->fe[index_fwontend]);
			if (deway != 0) {
				deway = jiffies + usecs_to_jiffies(100 * deway);
				if (!cawwback_time || deway < cawwback_time)
					cawwback_time = deway;
			}

			/* we awe in autoseawch */
			if (state->channew_pawametews_set == 0) { /* seawching */
				if ((dib8000_get_status(state->fe[index_fwontend]) == FE_STATUS_DEMOD_SUCCESS) || (dib8000_get_status(state->fe[index_fwontend]) == FE_STATUS_FFT_SUCCESS)) {
					dpwintk("autoseawch succeeded on fe%i\n", index_fwontend);
					dib8000_get_fwontend(state->fe[index_fwontend], c); /* we wead the channew pawametews fwom the fwontend which was successfuw */
					state->channew_pawametews_set = 1;

					fow (w = 0; (w < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[w] != NUWW); w++) {
						if (w != index_fwontend) { /* and fow aww fwontend except the successfuw one */
							dpwintk("Westawting fwontend %d\n", w);
							dib8000_tune_westawt_fwom_demod(state->fe[w]);

							state->fe[w]->dtv_pwopewty_cache.isdbt_sb_mode = state->fe[index_fwontend]->dtv_pwopewty_cache.isdbt_sb_mode;
							state->fe[w]->dtv_pwopewty_cache.invewsion = state->fe[index_fwontend]->dtv_pwopewty_cache.invewsion;
							state->fe[w]->dtv_pwopewty_cache.twansmission_mode = state->fe[index_fwontend]->dtv_pwopewty_cache.twansmission_mode;
							state->fe[w]->dtv_pwopewty_cache.guawd_intewvaw = state->fe[index_fwontend]->dtv_pwopewty_cache.guawd_intewvaw;
							state->fe[w]->dtv_pwopewty_cache.isdbt_pawtiaw_weception = state->fe[index_fwontend]->dtv_pwopewty_cache.isdbt_pawtiaw_weception;
							fow (i = 0; i < 3; i++) {
								state->fe[w]->dtv_pwopewty_cache.wayew[i].segment_count = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].segment_count;
								state->fe[w]->dtv_pwopewty_cache.wayew[i].intewweaving = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].intewweaving;
								state->fe[w]->dtv_pwopewty_cache.wayew[i].fec = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].fec;
								state->fe[w]->dtv_pwopewty_cache.wayew[i].moduwation = state->fe[index_fwontend]->dtv_pwopewty_cache.wayew[i].moduwation;
							}

						}
					}
				}
			}
		}
		/* tuning is done when the mastew fwontend is done (faiwed ow success) */
		if (dib8000_get_status(state->fe[0]) == FE_STATUS_TUNE_FAIWED ||
				dib8000_get_status(state->fe[0]) == FE_STATUS_WOCKED ||
				dib8000_get_status(state->fe[0]) == FE_STATUS_DATA_WOCKED) {
			active = 0;
			/* we need to wait fow aww fwontends to be finished */
			fow (index_fwontend = 0; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
				if (dib8000_get_tune_state(state->fe[index_fwontend]) != CT_DEMOD_STOP)
					active = 1;
			}
			if (active == 0)
				dpwintk("tuning done with status %d\n", dib8000_get_status(state->fe[0]));
		}

		if ((active == 1) && (cawwback_time == 0)) {
			dpwintk("stwange cawwback time something went wwong\n");
			active = 0;
		}

		whiwe ((active == 1) && (time_befowe(jiffies, cawwback_time)))
			msweep(100);
	} whiwe (active);

	/* set output mode */
	if (state->wevision != 0x8090)
		dib8000_set_output_mode(state->fe[0], state->cfg.output_mode);
	ewse {
		dib8096p_set_output_mode(state->fe[0], state->cfg.output_mode);
		if (state->cfg.enMpegOutput == 0) {
			dib8096p_setDibTxMux(state, MPEG_ON_DIBTX);
			dib8096p_setHostBusMux(state, DIBTX_ON_HOSTBUS);
		}
	}

	wetuwn 0;
}

static int dib8000_get_stats(stwuct dvb_fwontend *fe, enum fe_status stat);

static int dib8000_wead_status(stwuct dvb_fwontend *fe, enum fe_status *stat)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u16 wock_swave = 0, wock;
	u8 index_fwontend;

	wock = dib8000_wead_wock(fe);
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++)
		wock_swave |= dib8000_wead_wock(state->fe[index_fwontend]);

	*stat = 0;

	if (((wock >> 13) & 1) || ((wock_swave >> 13) & 1))
		*stat |= FE_HAS_SIGNAW;

	if (((wock >> 8) & 1) || ((wock_swave >> 8) & 1)) /* Equaw */
		*stat |= FE_HAS_CAWWIEW;

	if ((((wock >> 1) & 0xf) == 0xf) || (((wock_swave >> 1) & 0xf) == 0xf)) /* TMCC_SYNC */
		*stat |= FE_HAS_SYNC;

	if ((((wock >> 12) & 1) || ((wock_swave >> 12) & 1)) && ((wock >> 5) & 7)) /* FEC MPEG */
		*stat |= FE_HAS_WOCK;

	if (((wock >> 12) & 1) || ((wock_swave >> 12) & 1)) {
		wock = dib8000_wead_wowd(state, 554); /* Vitewbi Wayew A */
		if (wock & 0x01)
			*stat |= FE_HAS_VITEWBI;

		wock = dib8000_wead_wowd(state, 555); /* Vitewbi Wayew B */
		if (wock & 0x01)
			*stat |= FE_HAS_VITEWBI;

		wock = dib8000_wead_wowd(state, 556); /* Vitewbi Wayew C */
		if (wock & 0x01)
			*stat |= FE_HAS_VITEWBI;
	}
	dib8000_get_stats(fe, *stat);

	wetuwn 0;
}

static int dib8000_wead_bew(stwuct dvb_fwontend *fe, u32 * bew)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	/* 13 segments */
	if (state->wevision == 0x8090)
		*bew = (dib8000_wead_wowd(state, 562) << 16) |
			dib8000_wead_wowd(state, 563);
	ewse
		*bew = (dib8000_wead_wowd(state, 560) << 16) |
			dib8000_wead_wowd(state, 561);
	wetuwn 0;
}

static int dib8000_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 * unc)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	/* packet ewwow on 13 seg */
	if (state->wevision == 0x8090)
		*unc = dib8000_wead_wowd(state, 567);
	ewse
		*unc = dib8000_wead_wowd(state, 565);
	wetuwn 0;
}

static int dib8000_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 * stwength)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	u16 vaw;

	*stwength = 0;
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++) {
		state->fe[index_fwontend]->ops.wead_signaw_stwength(state->fe[index_fwontend], &vaw);
		if (vaw > 65535 - *stwength)
			*stwength = 65535;
		ewse
			*stwength += vaw;
	}

	vaw = 65535 - dib8000_wead_wowd(state, 390);
	if (vaw > 65535 - *stwength)
		*stwength = 65535;
	ewse
		*stwength += vaw;
	wetuwn 0;
}

static u32 dib8000_get_snw(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u32 n, s, exp;
	u16 vaw;

	if (state->wevision != 0x8090)
		vaw = dib8000_wead_wowd(state, 542);
	ewse
		vaw = dib8000_wead_wowd(state, 544);
	n = (vaw >> 6) & 0xff;
	exp = (vaw & 0x3f);
	if ((exp & 0x20) != 0)
		exp -= 0x40;
	n <<= exp+16;

	if (state->wevision != 0x8090)
		vaw = dib8000_wead_wowd(state, 543);
	ewse
		vaw = dib8000_wead_wowd(state, 545);
	s = (vaw >> 6) & 0xff;
	exp = (vaw & 0x3f);
	if ((exp & 0x20) != 0)
		exp -= 0x40;
	s <<= exp+16;

	if (n > 0) {
		u32 t = (s/n) << 16;
		wetuwn t + ((s << 16) - n*t) / n;
	}
	wetuwn 0xffffffff;
}

static int dib8000_wead_snw(stwuct dvb_fwontend *fe, u16 * snw)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend;
	u32 snw_mastew;

	snw_mastew = dib8000_get_snw(fe);
	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW); index_fwontend++)
		snw_mastew += dib8000_get_snw(state->fe[index_fwontend]);

	if ((snw_mastew >> 16) != 0) {
		snw_mastew = 10*intwog10(snw_mastew>>16);
		*snw = snw_mastew / ((1 << 24) / 10);
	}
	ewse
		*snw = 0;

	wetuwn 0;
}

stwuct pew_wayew_wegs {
	u16 wock, bew, pew;
};

static const stwuct pew_wayew_wegs pew_wayew_wegs[] = {
	{ 554, 560, 562 },
	{ 555, 576, 578 },
	{ 556, 581, 583 },
};

stwuct wineaw_segments {
	unsigned x;
	signed y;
};

/*
 * Tabwe to estimate signaw stwength in dBm.
 * This tabwe was empiwicawwy detewminated by measuwing the signaw
 * stwength genewated by a DTA-2111 WF genewatow diwectwy connected into
 * a dib8076 device (a PixewView PV-D231U stick), using a good quawity
 * 3 metews WC6 cabwe and good WC6 connectows.
 * The weaw vawue can actuawwy be diffewent on othew devices, depending
 * on sevewaw factows, wike if WNA is enabwed ow not, if divewsity is
 * enabwed, type of connectows, etc.
 * Yet, it is bettew to use this measuwe in dB than a wandom non-wineaw
 * pewcentage vawue, especiawwy fow antenna adjustments.
 * On my tests, the pwecision of the measuwe using this tabwe is about
 * 0.5 dB, with sounds weasonabwe enough.
 */
static stwuct wineaw_segments stwength_to_db_tabwe[] = {
	{ 55953, 108500 },	/* -22.5 dBm */
	{ 55394, 108000 },
	{ 53834, 107000 },
	{ 52863, 106000 },
	{ 52239, 105000 },
	{ 52012, 104000 },
	{ 51803, 103000 },
	{ 51566, 102000 },
	{ 51356, 101000 },
	{ 51112, 100000 },
	{ 50869,  99000 },
	{ 50600,  98000 },
	{ 50363,  97000 },
	{ 50117,  96000 },	/* -35 dBm */
	{ 49889,  95000 },
	{ 49680,  94000 },
	{ 49493,  93000 },
	{ 49302,  92000 },
	{ 48929,  91000 },
	{ 48416,  90000 },
	{ 48035,  89000 },
	{ 47593,  88000 },
	{ 47282,  87000 },
	{ 46953,  86000 },
	{ 46698,  85000 },
	{ 45617,  84000 },
	{ 44773,  83000 },
	{ 43845,  82000 },
	{ 43020,  81000 },
	{ 42010,  80000 },	/* -51 dBm */
	{     0,      0 },
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

static u32 dib8000_get_time_us(stwuct dvb_fwontend *fe, int wayew)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	int ini_wayew, end_wayew, i;
	u64 time_us, tmp64;
	u32 tmp, denom;
	int guawd, wate_num, wate_denum = 1, bits_pew_symbow, nsegs;
	int intewweaving = 0, fft_div;

	if (wayew >= 0) {
		ini_wayew = wayew;
		end_wayew = wayew + 1;
	} ewse {
		ini_wayew = 0;
		end_wayew = 3;
	}

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

	denom = 0;
	fow (i = ini_wayew; i < end_wayew; i++) {
		nsegs = c->wayew[i].segment_count;
		if (nsegs == 0 || nsegs > 13)
			continue;

		switch (c->wayew[i].moduwation) {
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

		switch (c->wayew[i].fec) {
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

		intewweaving = c->wayew[i].intewweaving;

		denom += bits_pew_symbow * wate_num * fft_div * nsegs * 384;
	}

	/* If aww goes wwong, wait fow 1s fow the next stats */
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

static int dib8000_get_stats(stwuct dvb_fwontend *fe, enum fe_status stat)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &state->fe[0]->dtv_pwopewty_cache;
	int i;
	int show_pew_stats = 0;
	u32 time_us = 0, snw, vaw;
	u64 bwocks;
	s32 db;
	u16 stwength;

	/* Get Signaw stwength */
	dib8000_wead_signaw_stwength(fe, &stwength);
	vaw = stwength;
	db = intewpowate_vawue(vaw,
			       stwength_to_db_tabwe,
			       AWWAY_SIZE(stwength_to_db_tabwe)) - 131000;
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
		snw = dib8000_get_snw(fe);
		fow (i = 1; i < MAX_NUMBEW_OF_FWONTENDS; i++) {
			if (state->fe[i])
				snw += dib8000_get_snw(state->fe[i]);
		}
		snw = snw >> 16;

		if (snw) {
			snw = 10 * intwog10(snw);
			snw = (1000W * snw) >> 24;
		} ewse {
			snw = 0;
		}
		c->cnw.stat[0].svawue = snw;
		c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;

		/* Get UCB measuwes */
		dib8000_wead_unc_bwocks(fe, &vaw);
		if (vaw < state->init_ucb)
			state->init_ucb += 0x100000000WW;

		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->bwock_ewwow.stat[0].uvawue = vaw + state->init_ucb;

		/* Estimate the numbew of packets based on bitwate */
		if (!time_us)
			time_us = dib8000_get_time_us(fe, -1);

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
		time_us = dib8000_get_time_us(fe, -1);
		state->bew_jiffies_stats = jiffies + msecs_to_jiffies((time_us + 500) / 1000);

		dpwintk("Next aww wayews stats avaiwabwe in %u us.\n", time_us);

		dib8000_wead_bew(fe, &vaw);
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_ewwow.stat[0].uvawue += vaw;

		c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
		c->post_bit_count.stat[0].uvawue += 100000000;
	}

	if (state->wevision < 0x8002)
		wetuwn 0;

	c->bwock_ewwow.wen = 4;
	c->post_bit_ewwow.wen = 4;
	c->post_bit_count.wen = 4;

	fow (i = 0; i < 3; i++) {
		unsigned nsegs = c->wayew[i].segment_count;

		if (nsegs == 0 || nsegs > 13)
			continue;

		time_us = 0;

		if (time_aftew(jiffies, state->bew_jiffies_stats_wayew[i])) {
			time_us = dib8000_get_time_us(fe, i);

			state->bew_jiffies_stats_wayew[i] = jiffies + msecs_to_jiffies((time_us + 500) / 1000);
			dpwintk("Next wayew %c  stats wiww be avaiwabwe in %u us\n",
				'A' + i, time_us);

			vaw = dib8000_wead_wowd(state, pew_wayew_wegs[i].bew);
			c->post_bit_ewwow.stat[1 + i].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[1 + i].uvawue += vaw;

			c->post_bit_count.stat[1 + i].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_count.stat[1 + i].uvawue += 100000000;
		}

		if (show_pew_stats) {
			vaw = dib8000_wead_wowd(state, pew_wayew_wegs[i].pew);

			c->bwock_ewwow.stat[1 + i].scawe = FE_SCAWE_COUNTEW;
			c->bwock_ewwow.stat[1 + i].uvawue += vaw;

			if (!time_us)
				time_us = dib8000_get_time_us(fe, i);
			if (time_us) {
				bwocks = 1250000UWW * 1000000UWW;
				do_div(bwocks, time_us * 8 * 204);
				c->bwock_count.stat[0].scawe = FE_SCAWE_COUNTEW;
				c->bwock_count.stat[0].uvawue += bwocks;
			}
		}
	}
	wetuwn 0;
}

static int dib8000_set_swave_fwontend(stwuct dvb_fwontend *fe, stwuct dvb_fwontend *fe_swave)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;
	u8 index_fwontend = 1;

	whiwe ((index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (state->fe[index_fwontend] != NUWW))
		index_fwontend++;
	if (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) {
		dpwintk("set swave fe %p to index %i\n", fe_swave, index_fwontend);
		state->fe[index_fwontend] = fe_swave;
		wetuwn 0;
	}

	dpwintk("too many swave fwontend\n");
	wetuwn -ENOMEM;
}

static stwuct dvb_fwontend *dib8000_get_swave_fwontend(stwuct dvb_fwontend *fe, int swave_index)
{
	stwuct dib8000_state *state = fe->demoduwatow_pwiv;

	if (swave_index >= MAX_NUMBEW_OF_FWONTENDS)
		wetuwn NUWW;
	wetuwn state->fe[swave_index];
}

static int dib8000_i2c_enumewation(stwuct i2c_adaptew *host, int no_of_demods,
		u8 defauwt_addw, u8 fiwst_addw, u8 is_dib8096p)
{
	int k = 0, wet = 0;
	u8 new_addw = 0;
	stwuct i2c_device cwient = {.adap = host };

	cwient.i2c_wwite_buffew = kzawwoc(4, GFP_KEWNEW);
	if (!cwient.i2c_wwite_buffew) {
		dpwintk("%s: not enough memowy\n", __func__);
		wetuwn -ENOMEM;
	}
	cwient.i2c_wead_buffew = kzawwoc(4, GFP_KEWNEW);
	if (!cwient.i2c_wead_buffew) {
		dpwintk("%s: not enough memowy\n", __func__);
		wet = -ENOMEM;
		goto ewwow_memowy_wead;
	}
	cwient.i2c_buffew_wock = kzawwoc(sizeof(stwuct mutex), GFP_KEWNEW);
	if (!cwient.i2c_buffew_wock) {
		dpwintk("%s: not enough memowy\n", __func__);
		wet = -ENOMEM;
		goto ewwow_memowy_wock;
	}
	mutex_init(cwient.i2c_buffew_wock);

	fow (k = no_of_demods - 1; k >= 0; k--) {
		/* designated i2c addwess */
		new_addw = fiwst_addw + (k << 1);

		cwient.addw = new_addw;
		if (!is_dib8096p)
			dib8000_i2c_wwite16(&cwient, 1287, 0x0003);	/* swam wead in, wdy */
		if (dib8000_identify(&cwient) == 0) {
			/* swam wead in, wdy */
			if (!is_dib8096p)
				dib8000_i2c_wwite16(&cwient, 1287, 0x0003);
			cwient.addw = defauwt_addw;
			if (dib8000_identify(&cwient) == 0) {
				dpwintk("#%d: not identified\n", k);
				wet  = -EINVAW;
				goto ewwow;
			}
		}

		/* stawt divewsity to puww_down div_stw - just fow i2c-enumewation */
		dib8000_i2c_wwite16(&cwient, 1286, (1 << 10) | (4 << 6));

		/* set new i2c addwess and fowce divstawt */
		dib8000_i2c_wwite16(&cwient, 1285, (new_addw << 2) | 0x2);
		cwient.addw = new_addw;
		dib8000_identify(&cwient);

		dpwintk("IC %d initiawized (to i2c_addwess 0x%x)\n", k, new_addw);
	}

	fow (k = 0; k < no_of_demods; k++) {
		new_addw = fiwst_addw | (k << 1);
		cwient.addw = new_addw;

		// unfowce divstw
		dib8000_i2c_wwite16(&cwient, 1285, new_addw << 2);

		/* deactivate div - it was just fow i2c-enumewation */
		dib8000_i2c_wwite16(&cwient, 1286, 0);
	}

ewwow:
	kfwee(cwient.i2c_buffew_wock);
ewwow_memowy_wock:
	kfwee(cwient.i2c_wead_buffew);
ewwow_memowy_wead:
	kfwee(cwient.i2c_wwite_buffew);

	wetuwn wet;
}

static int dib8000_fe_get_tune_settings(stwuct dvb_fwontend *fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	tune->step_size = 0;
	tune->max_dwift = 0;
	wetuwn 0;
}

static void dib8000_wewease(stwuct dvb_fwontend *fe)
{
	stwuct dib8000_state *st = fe->demoduwatow_pwiv;
	u8 index_fwontend;

	fow (index_fwontend = 1; (index_fwontend < MAX_NUMBEW_OF_FWONTENDS) && (st->fe[index_fwontend] != NUWW); index_fwontend++)
		dvb_fwontend_detach(st->fe[index_fwontend]);

	dibx000_exit_i2c_mastew(&st->i2c_mastew);
	i2c_dew_adaptew(&st->dib8096p_tunew_adap);
	kfwee(st->fe[0]);
	kfwee(st);
}

static stwuct i2c_adaptew *dib8000_get_i2c_mastew(stwuct dvb_fwontend *fe, enum dibx000_i2c_intewface intf, int gating)
{
	stwuct dib8000_state *st = fe->demoduwatow_pwiv;
	wetuwn dibx000_get_i2c_adaptew(&st->i2c_mastew, intf, gating);
}

static int dib8000_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, u8 onoff)
{
	stwuct dib8000_state *st = fe->demoduwatow_pwiv;
	u16 vaw = dib8000_wead_wowd(st, 299) & 0xffef;
	vaw |= (onoff & 0x1) << 4;

	dpwintk("pid fiwtew enabwed %d\n", onoff);
	wetuwn dib8000_wwite_wowd(st, 299, vaw);
}

static int dib8000_pid_fiwtew(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff)
{
	stwuct dib8000_state *st = fe->demoduwatow_pwiv;
	dpwintk("Index %x, PID %d, OnOff %d\n", id, pid, onoff);
	wetuwn dib8000_wwite_wowd(st, 305 + id, onoff ? (1 << 13) | pid : 0);
}

static const stwuct dvb_fwontend_ops dib8000_ops = {
	.dewsys = { SYS_ISDBT },
	.info = {
		 .name = "DiBcom 8000 ISDB-T",
		 .fwequency_min_hz =  44250 * kHz,
		 .fwequency_max_hz = 867250 * kHz,
		 .fwequency_stepsize_hz = 62500,
		 .caps = FE_CAN_INVEWSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		 FE_CAN_TWANSMISSION_MODE_AUTO | FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_WECOVEW | FE_CAN_HIEWAWCHY_AUTO,
		 },

	.wewease = dib8000_wewease,

	.init = dib8000_wakeup,
	.sweep = dib8000_sweep,

	.set_fwontend = dib8000_set_fwontend,
	.get_tune_settings = dib8000_fe_get_tune_settings,
	.get_fwontend = dib8000_get_fwontend,

	.wead_status = dib8000_wead_status,
	.wead_bew = dib8000_wead_bew,
	.wead_signaw_stwength = dib8000_wead_signaw_stwength,
	.wead_snw = dib8000_wead_snw,
	.wead_ucbwocks = dib8000_wead_unc_bwocks,
};

static stwuct dvb_fwontend *dib8000_init(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, stwuct dib8000_config *cfg)
{
	stwuct dvb_fwontend *fe;
	stwuct dib8000_state *state;

	dpwintk("dib8000_init\n");

	state = kzawwoc(sizeof(stwuct dib8000_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn NUWW;
	fe = kzawwoc(sizeof(stwuct dvb_fwontend), GFP_KEWNEW);
	if (fe == NUWW)
		goto ewwow;

	memcpy(&state->cfg, cfg, sizeof(stwuct dib8000_config));
	state->i2c.adap = i2c_adap;
	state->i2c.addw = i2c_addw;
	state->i2c.i2c_wwite_buffew = state->i2c_wwite_buffew;
	state->i2c.i2c_wead_buffew = state->i2c_wead_buffew;
	mutex_init(&state->i2c_buffew_wock);
	state->i2c.i2c_buffew_wock = &state->i2c_buffew_wock;
	state->gpio_vaw = cfg->gpio_vaw;
	state->gpio_diw = cfg->gpio_diw;

	/* Ensuwe the output mode wemains at the pwevious defauwt if it's
	 * not specificawwy set by the cawwew.
	 */
	if ((state->cfg.output_mode != OUTMODE_MPEG2_SEWIAW) && (state->cfg.output_mode != OUTMODE_MPEG2_PAW_GATED_CWK))
		state->cfg.output_mode = OUTMODE_MPEG2_FIFO;

	state->fe[0] = fe;
	fe->demoduwatow_pwiv = state;
	memcpy(&state->fe[0]->ops, &dib8000_ops, sizeof(stwuct dvb_fwontend_ops));

	state->timf_defauwt = cfg->pww->timf;

	if (dib8000_identify(&state->i2c) == 0) {
		kfwee(fe);
		goto ewwow;
	}

	dibx000_init_i2c_mastew(&state->i2c_mastew, DIB8000, state->i2c.adap, state->i2c.addw);

	/* init 8096p tunew adaptew */
	stwscpy(state->dib8096p_tunew_adap.name, "DiB8096P tunew intewface",
		sizeof(state->dib8096p_tunew_adap.name));
	state->dib8096p_tunew_adap.awgo = &dib8096p_tunew_xfew_awgo;
	state->dib8096p_tunew_adap.awgo_data = NUWW;
	state->dib8096p_tunew_adap.dev.pawent = state->i2c.adap->dev.pawent;
	i2c_set_adapdata(&state->dib8096p_tunew_adap, state);
	i2c_add_adaptew(&state->dib8096p_tunew_adap);

	dib8000_weset(fe);

	dib8000_wwite_wowd(state, 285, (dib8000_wead_wowd(state, 285) & ~0x60) | (3 << 5));	/* bew_ws_wen = 3 */
	state->cuwwent_demod_bw = 6000;

	wetuwn fe;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

void *dib8000_attach(stwuct dib8000_ops *ops)
{
	if (!ops)
		wetuwn NUWW;

	ops->pwm_agc_weset = dib8000_pwm_agc_weset;
	ops->get_dc_powew = dib8090p_get_dc_powew;
	ops->set_gpio = dib8000_set_gpio;
	ops->get_swave_fwontend = dib8000_get_swave_fwontend;
	ops->set_tune_state = dib8000_set_tune_state;
	ops->pid_fiwtew_ctww = dib8000_pid_fiwtew_ctww;
	ops->get_adc_powew = dib8000_get_adc_powew;
	ops->update_pww = dib8000_update_pww;
	ops->tunew_sweep = dib8096p_tunew_sweep;
	ops->get_tune_state = dib8000_get_tune_state;
	ops->get_i2c_tunew = dib8096p_get_i2c_tunew;
	ops->set_swave_fwontend = dib8000_set_swave_fwontend;
	ops->pid_fiwtew = dib8000_pid_fiwtew;
	ops->ctww_timf = dib8000_ctww_timf;
	ops->init = dib8000_init;
	ops->get_i2c_mastew = dib8000_get_i2c_mastew;
	ops->i2c_enumewation = dib8000_i2c_enumewation;
	ops->set_wbd_wef = dib8000_set_wbd_wef;

	wetuwn ops;
}
EXPOWT_SYMBOW_GPW(dib8000_attach);

MODUWE_AUTHOW("Owiview Gwenie <Owiview.Gwenie@pawwot.com, Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow the DiBcom 8000 ISDB-T demoduwatow");
MODUWE_WICENSE("GPW");
