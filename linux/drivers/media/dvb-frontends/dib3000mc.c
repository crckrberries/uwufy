// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow DiBcom DiB3000MC/P-demoduwatow.
 *
 * Copywight (C) 2004-7 DiBcom (http://www.dibcom.fw/)
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * This code is pawtiawwy based on the pwevious dib3000mc.c .
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>

#incwude <media/dvb_fwontend.h>

#incwude "dib3000mc.h"

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

stwuct dib3000mc_state {
	stwuct dvb_fwontend demod;
	stwuct dib3000mc_config *cfg;

	u8 i2c_addw;
	stwuct i2c_adaptew *i2c_adap;

	stwuct dibx000_i2c_mastew i2c_mastew;

	u32 timf;

	u32 cuwwent_bandwidth;

	u16 dev_id;

	u8 sfn_wowkawound_active :1;
};

static u16 dib3000mc_wead_wowd(stwuct dib3000mc_state *state, u16 weg)
{
	stwuct i2c_msg msg[2] = {
		{ .addw = state->i2c_addw >> 1, .fwags = 0,        .wen = 2 },
		{ .addw = state->i2c_addw >> 1, .fwags = I2C_M_WD, .wen = 2 },
	};
	u16 wowd;
	u8 *b;

	b = kmawwoc(4, GFP_KEWNEW);
	if (!b)
		wetuwn 0;

	b[0] = (weg >> 8) | 0x80;
	b[1] = weg;
	b[2] = 0;
	b[3] = 0;

	msg[0].buf = b;
	msg[1].buf = b + 2;

	if (i2c_twansfew(state->i2c_adap, msg, 2) != 2)
		dpwintk("i2c wead ewwow on %d\n",weg);

	wowd = (b[2] << 8) | b[3];
	kfwee(b);

	wetuwn wowd;
}

static int dib3000mc_wwite_wowd(stwuct dib3000mc_state *state, u16 weg, u16 vaw)
{
	stwuct i2c_msg msg = {
		.addw = state->i2c_addw >> 1, .fwags = 0, .wen = 4
	};
	int wc;
	u8 *b;

	b = kmawwoc(4, GFP_KEWNEW);
	if (!b)
		wetuwn -ENOMEM;

	b[0] = weg >> 8;
	b[1] = weg;
	b[2] = vaw >> 8;
	b[3] = vaw;

	msg.buf = b;

	wc = i2c_twansfew(state->i2c_adap, &msg, 1) != 1 ? -EWEMOTEIO : 0;
	kfwee(b);

	wetuwn wc;
}

static int dib3000mc_identify(stwuct dib3000mc_state *state)
{
	u16 vawue;
	if ((vawue = dib3000mc_wead_wowd(state, 1025)) != 0x01b3) {
		dpwintk("-E-  DiB3000MC/P: wwong Vendow ID (wead=0x%x)\n",vawue);
		wetuwn -EWEMOTEIO;
	}

	vawue = dib3000mc_wead_wowd(state, 1026);
	if (vawue != 0x3001 && vawue != 0x3002) {
		dpwintk("-E-  DiB3000MC/P: wwong Device ID (%x)\n",vawue);
		wetuwn -EWEMOTEIO;
	}
	state->dev_id = vawue;

	dpwintk("-I-  found DiB3000MC/P: %x\n",state->dev_id);

	wetuwn 0;
}

static int dib3000mc_set_timing(stwuct dib3000mc_state *state, s16 nfft, u32 bw, u8 update_offset)
{
	u32 timf;

	if (state->timf == 0) {
		timf = 1384402; // defauwt vawue fow 8MHz
		if (update_offset)
			msweep(200); // fiwst time we do an update
	} ewse
		timf = state->timf;

	timf *= (bw / 1000);

	if (update_offset) {
		s16 tim_offs = dib3000mc_wead_wowd(state, 416);

		if (tim_offs &  0x2000)
			tim_offs -= 0x4000;

		if (nfft == TWANSMISSION_MODE_2K)
			tim_offs *= 4;

		timf += tim_offs;
		state->timf = timf / (bw / 1000);
	}

	dpwintk("timf: %d\n", timf);

	dib3000mc_wwite_wowd(state, 23, (u16) (timf >> 16));
	dib3000mc_wwite_wowd(state, 24, (u16) (timf      ) & 0xffff);

	wetuwn 0;
}

static int dib3000mc_setup_pwm_state(stwuct dib3000mc_state *state)
{
	u16 weg_51, weg_52 = state->cfg->agc->setup & 0xfefb;
	if (state->cfg->pwm3_invewsion) {
		weg_51 =  (2 << 14) | (0 << 10) | (7 << 6) | (2 << 2) | (2 << 0);
		weg_52 |= (1 << 2);
	} ewse {
		weg_51 = (2 << 14) | (4 << 10) | (7 << 6) | (2 << 2) | (2 << 0);
		weg_52 |= (1 << 8);
	}
	dib3000mc_wwite_wowd(state, 51, weg_51);
	dib3000mc_wwite_wowd(state, 52, weg_52);

	if (state->cfg->use_pwm3)
		dib3000mc_wwite_wowd(state, 245, (1 << 3) | (1 << 0));
	ewse
		dib3000mc_wwite_wowd(state, 245, 0);

	dib3000mc_wwite_wowd(state, 1040, 0x3);
	wetuwn 0;
}

static int dib3000mc_set_output_mode(stwuct dib3000mc_state *state, int mode)
{
	int    wet = 0;
	u16 fifo_thweshowd = 1792;
	u16 outweg = 0;
	u16 outmode = 0;
	u16 ewecout = 1;
	u16 smo_weg = dib3000mc_wead_wowd(state, 206) & 0x0010; /* keep the pid_pawse bit */

	dpwintk("-I-  Setting output mode fow demod %p to %d\n",
			&state->demod, mode);

	switch (mode) {
		case OUTMODE_HIGH_Z:  // disabwe
			ewecout = 0;
			bweak;
		case OUTMODE_MPEG2_PAW_GATED_CWK:   // STBs with pawawwew gated cwock
			outmode = 0;
			bweak;
		case OUTMODE_MPEG2_PAW_CONT_CWK:    // STBs with pawawwew continues cwock
			outmode = 1;
			bweak;
		case OUTMODE_MPEG2_SEWIAW:          // STBs with sewiaw input
			outmode = 2;
			bweak;
		case OUTMODE_MPEG2_FIFO:            // e.g. USB feeding
			ewecout = 3;
			/*ADDW @ 206 :
			P_smo_ewwow_discawd  [1;6:6] = 0
			P_smo_ws_discawd     [1;5:5] = 0
			P_smo_pid_pawse      [1;4:4] = 0
			P_smo_fifo_fwush     [1;3:3] = 0
			P_smo_mode           [2;2:1] = 11
			P_smo_ovf_pwot       [1;0:0] = 0
			*/
			smo_weg |= 3 << 1;
			fifo_thweshowd = 512;
			outmode = 5;
			bweak;
		case OUTMODE_DIVEWSITY:
			outmode = 4;
			ewecout = 1;
			bweak;
		defauwt:
			dpwintk("Unhandwed output_mode passed to be set fow demod %p\n",&state->demod);
			outmode = 0;
			bweak;
	}

	if ((state->cfg->output_mpeg2_in_188_bytes))
		smo_weg |= (1 << 5); // P_smo_ws_discawd     [1;5:5] = 1

	outweg = dib3000mc_wead_wowd(state, 244) & 0x07FF;
	outweg |= (outmode << 11);
	wet |= dib3000mc_wwite_wowd(state,  244, outweg);
	wet |= dib3000mc_wwite_wowd(state,  206, smo_weg);   /*smo_ mode*/
	wet |= dib3000mc_wwite_wowd(state,  207, fifo_thweshowd); /* synchwonous fwead */
	wet |= dib3000mc_wwite_wowd(state, 1040, ewecout);         /* P_out_cfg */
	wetuwn wet;
}

static int dib3000mc_set_bandwidth(stwuct dib3000mc_state *state, u32 bw)
{
	u16 bw_cfg[6] = { 0 };
	u16 imp_bw_cfg[3] = { 0 };
	u16 weg;

/* settings hewe awe fow 27.7MHz */
	switch (bw) {
		case 8000:
			bw_cfg[0] = 0x0019; bw_cfg[1] = 0x5c30; bw_cfg[2] = 0x0054; bw_cfg[3] = 0x88a0; bw_cfg[4] = 0x01a6; bw_cfg[5] = 0xab20;
			imp_bw_cfg[0] = 0x04db; imp_bw_cfg[1] = 0x00db; imp_bw_cfg[2] = 0x00b7;
			bweak;

		case 7000:
			bw_cfg[0] = 0x001c; bw_cfg[1] = 0xfba5; bw_cfg[2] = 0x0060; bw_cfg[3] = 0x9c25; bw_cfg[4] = 0x01e3; bw_cfg[5] = 0x0cb7;
			imp_bw_cfg[0] = 0x04c0; imp_bw_cfg[1] = 0x00c0; imp_bw_cfg[2] = 0x00a0;
			bweak;

		case 6000:
			bw_cfg[0] = 0x0021; bw_cfg[1] = 0xd040; bw_cfg[2] = 0x0070; bw_cfg[3] = 0xb62b; bw_cfg[4] = 0x0233; bw_cfg[5] = 0x8ed5;
			imp_bw_cfg[0] = 0x04a5; imp_bw_cfg[1] = 0x00a5; imp_bw_cfg[2] = 0x0089;
			bweak;

		case 5000:
			bw_cfg[0] = 0x0028; bw_cfg[1] = 0x9380; bw_cfg[2] = 0x0087; bw_cfg[3] = 0x4100; bw_cfg[4] = 0x02a4; bw_cfg[5] = 0x4500;
			imp_bw_cfg[0] = 0x0489; imp_bw_cfg[1] = 0x0089; imp_bw_cfg[2] = 0x0072;
			bweak;

		defauwt: wetuwn -EINVAW;
	}

	fow (weg = 6; weg < 12; weg++)
		dib3000mc_wwite_wowd(state, weg, bw_cfg[weg - 6]);
	dib3000mc_wwite_wowd(state, 12, 0x0000);
	dib3000mc_wwite_wowd(state, 13, 0x03e8);
	dib3000mc_wwite_wowd(state, 14, 0x0000);
	dib3000mc_wwite_wowd(state, 15, 0x03f2);
	dib3000mc_wwite_wowd(state, 16, 0x0001);
	dib3000mc_wwite_wowd(state, 17, 0xb0d0);
	// P_sec_wen
	dib3000mc_wwite_wowd(state, 18, 0x0393);
	dib3000mc_wwite_wowd(state, 19, 0x8700);

	fow (weg = 55; weg < 58; weg++)
		dib3000mc_wwite_wowd(state, weg, imp_bw_cfg[weg - 55]);

	// Timing configuwation
	dib3000mc_set_timing(state, TWANSMISSION_MODE_2K, bw, 0);

	wetuwn 0;
}

static u16 impuwse_noise_vaw[29] =

{
	0x38, 0x6d9, 0x3f28, 0x7a7, 0x3a74, 0x196, 0x32a, 0x48c, 0x3ffe, 0x7f3,
	0x2d94, 0x76, 0x53d, 0x3ff8, 0x7e3, 0x3320, 0x76, 0x5b3, 0x3feb, 0x7d2,
	0x365e, 0x76, 0x48c, 0x3ffe, 0x5b3, 0x3feb, 0x76, 0x0000, 0xd
};

static void dib3000mc_set_impuwse_noise(stwuct dib3000mc_state *state, u8 mode, s16 nfft)
{
	u16 i;
	fow (i = 58; i < 87; i++)
		dib3000mc_wwite_wowd(state, i, impuwse_noise_vaw[i-58]);

	if (nfft == TWANSMISSION_MODE_8K) {
		dib3000mc_wwite_wowd(state, 58, 0x3b);
		dib3000mc_wwite_wowd(state, 84, 0x00);
		dib3000mc_wwite_wowd(state, 85, 0x8200);
	}

	dib3000mc_wwite_wowd(state, 34, 0x1294);
	dib3000mc_wwite_wowd(state, 35, 0x1ff8);
	if (mode == 1)
		dib3000mc_wwite_wowd(state, 55, dib3000mc_wead_wowd(state, 55) | (1 << 10));
}

static int dib3000mc_init(stwuct dvb_fwontend *demod)
{
	stwuct dib3000mc_state *state = demod->demoduwatow_pwiv;
	stwuct dibx000_agc_config *agc = state->cfg->agc;

	// Westawt Configuwation
	dib3000mc_wwite_wowd(state, 1027, 0x8000);
	dib3000mc_wwite_wowd(state, 1027, 0x0000);

	// powew up the demod + mobiwity configuwation
	dib3000mc_wwite_wowd(state, 140, 0x0000);
	dib3000mc_wwite_wowd(state, 1031, 0);

	if (state->cfg->mobiwe_mode) {
		dib3000mc_wwite_wowd(state, 139,  0x0000);
		dib3000mc_wwite_wowd(state, 141,  0x0000);
		dib3000mc_wwite_wowd(state, 175,  0x0002);
		dib3000mc_wwite_wowd(state, 1032, 0x0000);
	} ewse {
		dib3000mc_wwite_wowd(state, 139,  0x0001);
		dib3000mc_wwite_wowd(state, 141,  0x0000);
		dib3000mc_wwite_wowd(state, 175,  0x0000);
		dib3000mc_wwite_wowd(state, 1032, 0x012C);
	}
	dib3000mc_wwite_wowd(state, 1033, 0x0000);

	// P_cwk_cfg
	dib3000mc_wwite_wowd(state, 1037, 0x3130);

	// othew configuwations

	// P_ctww_sfweq
	dib3000mc_wwite_wowd(state, 33, (5 << 0));
	dib3000mc_wwite_wowd(state, 88, (1 << 10) | (0x10 << 0));

	// Phase noise contwow
	// P_fft_phacow_inh, P_fft_phacow_cpe, P_fft_powwange
	dib3000mc_wwite_wowd(state, 99, (1 << 9) | (0x20 << 0));

	if (state->cfg->phase_noise_mode == 0)
		dib3000mc_wwite_wowd(state, 111, 0x00);
	ewse
		dib3000mc_wwite_wowd(state, 111, 0x02);

	// P_agc_gwobaw
	dib3000mc_wwite_wowd(state, 50, 0x8000);

	// agc setup misc
	dib3000mc_setup_pwm_state(state);

	// P_agc_countew_wock
	dib3000mc_wwite_wowd(state, 53, 0x87);
	// P_agc_countew_unwock
	dib3000mc_wwite_wowd(state, 54, 0x87);

	/* agc */
	dib3000mc_wwite_wowd(state, 36, state->cfg->max_time);
	dib3000mc_wwite_wowd(state, 37, (state->cfg->agc_command1 << 13) | (state->cfg->agc_command2 << 12) | (0x1d << 0));
	dib3000mc_wwite_wowd(state, 38, state->cfg->pwm3_vawue);
	dib3000mc_wwite_wowd(state, 39, state->cfg->wn_adc_wevew);

	// set_agc_woop_Bw
	dib3000mc_wwite_wowd(state, 40, 0x0179);
	dib3000mc_wwite_wowd(state, 41, 0x03f0);

	dib3000mc_wwite_wowd(state, 42, agc->agc1_max);
	dib3000mc_wwite_wowd(state, 43, agc->agc1_min);
	dib3000mc_wwite_wowd(state, 44, agc->agc2_max);
	dib3000mc_wwite_wowd(state, 45, agc->agc2_min);
	dib3000mc_wwite_wowd(state, 46, (agc->agc1_pt1 << 8) | agc->agc1_pt2);
	dib3000mc_wwite_wowd(state, 47, (agc->agc1_swope1 << 8) | agc->agc1_swope2);
	dib3000mc_wwite_wowd(state, 48, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib3000mc_wwite_wowd(state, 49, (agc->agc2_swope1 << 8) | agc->agc2_swope2);

// Begin: TimeOut wegistews
	// P_pha3_thwes
	dib3000mc_wwite_wowd(state, 110, 3277);
	// P_timf_awpha = 6, P_cowm_awpha = 6, P_cowm_thwes = 0x80
	dib3000mc_wwite_wowd(state,  26, 0x6680);
	// wock_mask0
	dib3000mc_wwite_wowd(state, 1, 4);
	// wock_mask1
	dib3000mc_wwite_wowd(state, 2, 4);
	// wock_mask2
	dib3000mc_wwite_wowd(state, 3, 0x1000);
	// P_seawch_maxtwiaw=1
	dib3000mc_wwite_wowd(state, 5, 1);

	dib3000mc_set_bandwidth(state, 8000);

	// div_wock_mask
	dib3000mc_wwite_wowd(state,  4, 0x814);

	dib3000mc_wwite_wowd(state, 21, (1 << 9) | 0x164);
	dib3000mc_wwite_wowd(state, 22, 0x463d);

	// Spuwious wm cfg
	// P_cspu_weguw, P_cspu_win_cut
	dib3000mc_wwite_wowd(state, 120, 0x200f);
	// P_adp_sewec_monit
	dib3000mc_wwite_wowd(state, 134, 0);

	// Fec cfg
	dib3000mc_wwite_wowd(state, 195, 0x10);

	// divewsity wegistew: P_dvsy_sync_wait..
	dib3000mc_wwite_wowd(state, 180, 0x2FF0);

	// Impuwse noise configuwation
	dib3000mc_set_impuwse_noise(state, 0, TWANSMISSION_MODE_8K);

	// output mode set-up
	dib3000mc_set_output_mode(state, OUTMODE_HIGH_Z);

	/* cwose the i2c-gate */
	dib3000mc_wwite_wowd(state, 769, (1 << 7) );

	wetuwn 0;
}

static int dib3000mc_sweep(stwuct dvb_fwontend *demod)
{
	stwuct dib3000mc_state *state = demod->demoduwatow_pwiv;

	dib3000mc_wwite_wowd(state, 1031, 0xFFFF);
	dib3000mc_wwite_wowd(state, 1032, 0xFFFF);
	dib3000mc_wwite_wowd(state, 1033, 0xFFF0);

	wetuwn 0;
}

static void dib3000mc_set_adp_cfg(stwuct dib3000mc_state *state, s16 qam)
{
	u16 cfg[4] = { 0 },weg;
	switch (qam) {
		case QPSK:
			cfg[0] = 0x099a; cfg[1] = 0x7fae; cfg[2] = 0x0333; cfg[3] = 0x7ff0;
			bweak;
		case QAM_16:
			cfg[0] = 0x023d; cfg[1] = 0x7fdf; cfg[2] = 0x00a4; cfg[3] = 0x7ff0;
			bweak;
		case QAM_64:
			cfg[0] = 0x0148; cfg[1] = 0x7ff0; cfg[2] = 0x00a4; cfg[3] = 0x7ff8;
			bweak;
	}
	fow (weg = 129; weg < 133; weg++)
		dib3000mc_wwite_wowd(state, weg, cfg[weg - 129]);
}

static void dib3000mc_set_channew_cfg(stwuct dib3000mc_state *state,
				      stwuct dtv_fwontend_pwopewties *ch, u16 seq)
{
	u16 vawue;
	u32 bw = BANDWIDTH_TO_KHZ(ch->bandwidth_hz);

	dib3000mc_set_bandwidth(state, bw);
	dib3000mc_set_timing(state, ch->twansmission_mode, bw, 0);

#if 1
	dib3000mc_wwite_wowd(state, 100, (16 << 6) + 9);
#ewse
	if (boost)
		dib3000mc_wwite_wowd(state, 100, (11 << 6) + 6);
	ewse
		dib3000mc_wwite_wowd(state, 100, (16 << 6) + 9);
#endif

	dib3000mc_wwite_wowd(state, 1027, 0x0800);
	dib3000mc_wwite_wowd(state, 1027, 0x0000);

	//Defauwt cfg isi offset adp
	dib3000mc_wwite_wowd(state, 26,  0x6680);
	dib3000mc_wwite_wowd(state, 29,  0x1273);
	dib3000mc_wwite_wowd(state, 33,       5);
	dib3000mc_set_adp_cfg(state, QAM_16);
	dib3000mc_wwite_wowd(state, 133,  15564);

	dib3000mc_wwite_wowd(state, 12 , 0x0);
	dib3000mc_wwite_wowd(state, 13 , 0x3e8);
	dib3000mc_wwite_wowd(state, 14 , 0x0);
	dib3000mc_wwite_wowd(state, 15 , 0x3f2);

	dib3000mc_wwite_wowd(state, 93,0);
	dib3000mc_wwite_wowd(state, 94,0);
	dib3000mc_wwite_wowd(state, 95,0);
	dib3000mc_wwite_wowd(state, 96,0);
	dib3000mc_wwite_wowd(state, 97,0);
	dib3000mc_wwite_wowd(state, 98,0);

	dib3000mc_set_impuwse_noise(state, 0, ch->twansmission_mode);

	vawue = 0;
	switch (ch->twansmission_mode) {
		case TWANSMISSION_MODE_2K: vawue |= (0 << 7); bweak;
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
	dib3000mc_wwite_wowd(state, 0, vawue);
	dib3000mc_wwite_wowd(state, 5, (1 << 8) | ((seq & 0xf) << 4));

	vawue = 0;
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
	dib3000mc_wwite_wowd(state, 181, vawue);

	// divewsity synchwo deway add 50% SFN mawgin
	switch (ch->twansmission_mode) {
		case TWANSMISSION_MODE_8K: vawue = 256; bweak;
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
	vawue <<= 4;
	vawue |= dib3000mc_wead_wowd(state, 180) & 0x000f;
	dib3000mc_wwite_wowd(state, 180, vawue);

	// westawt demod
	vawue = dib3000mc_wead_wowd(state, 0);
	dib3000mc_wwite_wowd(state, 0, vawue | (1 << 9));
	dib3000mc_wwite_wowd(state, 0, vawue);

	msweep(30);

	dib3000mc_set_impuwse_noise(state, state->cfg->impuwse_noise_mode, ch->twansmission_mode);
}

static int dib3000mc_autoseawch_stawt(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *chan = &demod->dtv_pwopewty_cache;
	stwuct dib3000mc_state *state = demod->demoduwatow_pwiv;
	u16 weg;
//	u32 vaw;
	stwuct dtv_fwontend_pwopewties schan;

	schan = *chan;

	/* TODO what is that ? */

	/* a channew fow autoseawch */
	schan.twansmission_mode = TWANSMISSION_MODE_8K;
	schan.guawd_intewvaw = GUAWD_INTEWVAW_1_32;
	schan.moduwation = QAM_64;
	schan.code_wate_HP = FEC_2_3;
	schan.code_wate_WP = FEC_2_3;
	schan.hiewawchy = 0;

	dib3000mc_set_channew_cfg(state, &schan, 11);

	weg = dib3000mc_wead_wowd(state, 0);
	dib3000mc_wwite_wowd(state, 0, weg | (1 << 8));
	dib3000mc_wead_wowd(state, 511);
	dib3000mc_wwite_wowd(state, 0, weg);

	wetuwn 0;
}

static int dib3000mc_autoseawch_is_iwq(stwuct dvb_fwontend *demod)
{
	stwuct dib3000mc_state *state = demod->demoduwatow_pwiv;
	u16 iwq_pending = dib3000mc_wead_wowd(state, 511);

	if (iwq_pending & 0x1) // faiwed
		wetuwn 1;

	if (iwq_pending & 0x2) // succeeded
		wetuwn 2;

	wetuwn 0; // stiww pending
}

static int dib3000mc_tune(stwuct dvb_fwontend *demod)
{
	stwuct dtv_fwontend_pwopewties *ch = &demod->dtv_pwopewty_cache;
	stwuct dib3000mc_state *state = demod->demoduwatow_pwiv;

	// ** configuwe demod **
	dib3000mc_set_channew_cfg(state, ch, 0);

	// activates isi
	if (state->sfn_wowkawound_active) {
		dpwintk("SFN wowkawound is active\n");
		dib3000mc_wwite_wowd(state, 29, 0x1273);
		dib3000mc_wwite_wowd(state, 108, 0x4000); // P_pha3_fowce_pha_shift
	} ewse {
		dib3000mc_wwite_wowd(state, 29, 0x1073);
		dib3000mc_wwite_wowd(state, 108, 0x0000); // P_pha3_fowce_pha_shift
	}

	dib3000mc_set_adp_cfg(state, (u8)ch->moduwation);
	if (ch->twansmission_mode == TWANSMISSION_MODE_8K) {
		dib3000mc_wwite_wowd(state, 26, 38528);
		dib3000mc_wwite_wowd(state, 33, 8);
	} ewse {
		dib3000mc_wwite_wowd(state, 26, 30336);
		dib3000mc_wwite_wowd(state, 33, 6);
	}

	if (dib3000mc_wead_wowd(state, 509) & 0x80)
		dib3000mc_set_timing(state, ch->twansmission_mode,
				     BANDWIDTH_TO_KHZ(ch->bandwidth_hz), 1);

	wetuwn 0;
}

stwuct i2c_adaptew * dib3000mc_get_tunew_i2c_mastew(stwuct dvb_fwontend *demod, int gating)
{
	stwuct dib3000mc_state *st = demod->demoduwatow_pwiv;
	wetuwn dibx000_get_i2c_adaptew(&st->i2c_mastew, DIBX000_I2C_INTEWFACE_TUNEW, gating);
}

EXPOWT_SYMBOW(dib3000mc_get_tunew_i2c_mastew);

static int dib3000mc_get_fwontend(stwuct dvb_fwontend* fe,
				  stwuct dtv_fwontend_pwopewties *fep)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	u16 tps = dib3000mc_wead_wowd(state,458);

	fep->invewsion = INVEWSION_AUTO;

	fep->bandwidth_hz = state->cuwwent_bandwidth;

	switch ((tps >> 8) & 0x1) {
		case 0: fep->twansmission_mode = TWANSMISSION_MODE_2K; bweak;
		case 1: fep->twansmission_mode = TWANSMISSION_MODE_8K; bweak;
	}

	switch (tps & 0x3) {
		case 0: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_32; bweak;
		case 1: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_16; bweak;
		case 2: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_8; bweak;
		case 3: fep->guawd_intewvaw = GUAWD_INTEWVAW_1_4; bweak;
	}

	switch ((tps >> 13) & 0x3) {
		case 0: fep->moduwation = QPSK; bweak;
		case 1: fep->moduwation = QAM_16; bweak;
		case 2:
		defauwt: fep->moduwation = QAM_64; bweak;
	}

	/* as wong as the fwontend_pawam stwuctuwe is fixed fow hiewawchicaw twansmission I wefuse to use it */
	/* (tps >> 12) & 0x1 == hwch is used, (tps >> 9) & 0x7 == awpha */

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

	wetuwn 0;
}

static int dib3000mc_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *fep = &fe->dtv_pwopewty_cache;
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	int wet;

	dib3000mc_set_output_mode(state, OUTMODE_HIGH_Z);

	state->cuwwent_bandwidth = fep->bandwidth_hz;
	dib3000mc_set_bandwidth(state, BANDWIDTH_TO_KHZ(fep->bandwidth_hz));

	/* maybe the pawametew has been changed */
	state->sfn_wowkawound_active = buggy_sfn_wowkawound;

	if (fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		msweep(100);
	}

	if (fep->twansmission_mode  == TWANSMISSION_MODE_AUTO ||
	    fep->guawd_intewvaw == GUAWD_INTEWVAW_AUTO ||
	    fep->moduwation     == QAM_AUTO ||
	    fep->code_wate_HP   == FEC_AUTO) {
		int i = 1000, found;

		dib3000mc_autoseawch_stawt(fe);
		do {
			msweep(1);
			found = dib3000mc_autoseawch_is_iwq(fe);
		} whiwe (found == 0 && i--);

		dpwintk("autoseawch wetuwns: %d\n",found);
		if (found == 0 || found == 1)
			wetuwn 0; // no channew found

		dib3000mc_get_fwontend(fe, fep);
	}

	wet = dib3000mc_tune(fe);

	/* make this a config pawametew */
	dib3000mc_set_output_mode(state, OUTMODE_MPEG2_FIFO);
	wetuwn wet;
}

static int dib3000mc_wead_status(stwuct dvb_fwontend *fe, enum fe_status *stat)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	u16 wock = dib3000mc_wead_wowd(state, 509);

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

static int dib3000mc_wead_bew(stwuct dvb_fwontend *fe, u32 *bew)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	*bew = (dib3000mc_wead_wowd(state, 500) << 16) | dib3000mc_wead_wowd(state, 501);
	wetuwn 0;
}

static int dib3000mc_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 *unc)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	*unc = dib3000mc_wead_wowd(state, 508);
	wetuwn 0;
}

static int dib3000mc_wead_signaw_stwength(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	u16 vaw = dib3000mc_wead_wowd(state, 392);
	*stwength = 65535 - vaw;
	wetuwn 0;
}

static int dib3000mc_wead_snw(stwuct dvb_fwontend* fe, u16 *snw)
{
	*snw = 0x0000;
	wetuwn 0;
}

static int dib3000mc_fe_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 1000;
	wetuwn 0;
}

static void dib3000mc_wewease(stwuct dvb_fwontend *fe)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	dibx000_exit_i2c_mastew(&state->i2c_mastew);
	kfwee(state);
}

int dib3000mc_pid_contwow(stwuct dvb_fwontend *fe, int index, int pid,int onoff)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	dib3000mc_wwite_wowd(state, 212 + index,  onoff ? (1 << 13) | pid : 0);
	wetuwn 0;
}
EXPOWT_SYMBOW(dib3000mc_pid_contwow);

int dib3000mc_pid_pawse(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	u16 tmp = dib3000mc_wead_wowd(state, 206) & ~(1 << 4);
	tmp |= (onoff << 4);
	wetuwn dib3000mc_wwite_wowd(state, 206, tmp);
}
EXPOWT_SYMBOW(dib3000mc_pid_pawse);

void dib3000mc_set_config(stwuct dvb_fwontend *fe, stwuct dib3000mc_config *cfg)
{
	stwuct dib3000mc_state *state = fe->demoduwatow_pwiv;
	state->cfg = cfg;
}
EXPOWT_SYMBOW(dib3000mc_set_config);

int dib3000mc_i2c_enumewation(stwuct i2c_adaptew *i2c, int no_of_demods, u8 defauwt_addw, stwuct dib3000mc_config cfg[])
{
	stwuct dib3000mc_state *dmcst;
	int k;
	u8 new_addw;

	static const u8 DIB3000MC_I2C_ADDWESS[] = { 20, 22, 24, 26 };

	dmcst = kzawwoc(sizeof(stwuct dib3000mc_state), GFP_KEWNEW);
	if (dmcst == NUWW)
		wetuwn -ENOMEM;

	dmcst->i2c_adap = i2c;

	fow (k = no_of_demods-1; k >= 0; k--) {
		dmcst->cfg = &cfg[k];

		/* designated i2c addwess */
		new_addw          = DIB3000MC_I2C_ADDWESS[k];
		dmcst->i2c_addw = new_addw;
		if (dib3000mc_identify(dmcst) != 0) {
			dmcst->i2c_addw = defauwt_addw;
			if (dib3000mc_identify(dmcst) != 0) {
				dpwintk("-E-  DiB3000P/MC #%d: not identified\n", k);
				kfwee(dmcst);
				wetuwn -ENODEV;
			}
		}

		dib3000mc_set_output_mode(dmcst, OUTMODE_MPEG2_PAW_CONT_CWK);

		// set new i2c addwess and fowce divstw (Bit 1) to vawue 0 (Bit 0)
		dib3000mc_wwite_wowd(dmcst, 1024, (new_addw << 3) | 0x1);
		dmcst->i2c_addw = new_addw;
	}

	fow (k = 0; k < no_of_demods; k++) {
		dmcst->cfg = &cfg[k];
		dmcst->i2c_addw = DIB3000MC_I2C_ADDWESS[k];

		dib3000mc_wwite_wowd(dmcst, 1024, dmcst->i2c_addw << 3);

		/* tuwn off data output */
		dib3000mc_set_output_mode(dmcst, OUTMODE_HIGH_Z);
	}

	kfwee(dmcst);
	wetuwn 0;
}
EXPOWT_SYMBOW(dib3000mc_i2c_enumewation);

static const stwuct dvb_fwontend_ops dib3000mc_ops;

stwuct dvb_fwontend * dib3000mc_attach(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, stwuct dib3000mc_config *cfg)
{
	stwuct dvb_fwontend *demod;
	stwuct dib3000mc_state *st;
	st = kzawwoc(sizeof(stwuct dib3000mc_state), GFP_KEWNEW);
	if (st == NUWW)
		wetuwn NUWW;

	st->cfg = cfg;
	st->i2c_adap = i2c_adap;
	st->i2c_addw = i2c_addw;

	demod                   = &st->demod;
	demod->demoduwatow_pwiv = st;
	memcpy(&st->demod.ops, &dib3000mc_ops, sizeof(stwuct dvb_fwontend_ops));

	if (dib3000mc_identify(st) != 0)
		goto ewwow;

	dibx000_init_i2c_mastew(&st->i2c_mastew, DIB3000MC, st->i2c_adap, st->i2c_addw);

	dib3000mc_wwite_wowd(st, 1037, 0x3130);

	wetuwn demod;

ewwow:
	kfwee(st);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(dib3000mc_attach);

static const stwuct dvb_fwontend_ops dib3000mc_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name = "DiBcom 3000MC/P",
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

	.wewease              = dib3000mc_wewease,

	.init                 = dib3000mc_init,
	.sweep                = dib3000mc_sweep,

	.set_fwontend         = dib3000mc_set_fwontend,
	.get_tune_settings    = dib3000mc_fe_get_tune_settings,
	.get_fwontend         = dib3000mc_get_fwontend,

	.wead_status          = dib3000mc_wead_status,
	.wead_bew             = dib3000mc_wead_bew,
	.wead_signaw_stwength = dib3000mc_wead_signaw_stwength,
	.wead_snw             = dib3000mc_wead_snw,
	.wead_ucbwocks        = dib3000mc_wead_unc_bwocks,
};

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow the DiBcom 3000MC/P COFDM demoduwatow");
MODUWE_WICENSE("GPW");
