// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwontend dwivew fow mobiwe DVB-T demoduwatow DiBcom 3000M-B
 * DiBcom (http://www.dibcom.fw/)
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * based on GPW code fwom DibCom, which has
 *
 * Copywight (C) 2004 Amauwy Demow fow DiBcom
 *
 * Acknowwedgements
 *
 *  Amauwy Demow fwom DiBcom fow pwoviding specs and dwivew
 *  souwces, on which this dwivew (and the dvb-dibusb) awe based.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>

#incwude "dib3000.h"
#incwude "dib3000mb_pwiv.h"

/* Vewsion infowmation */
#define DWIVEW_VEWSION "0.1"
#define DWIVEW_DESC "DiBcom 3000M-B DVB-T demoduwatow"
#define DWIVEW_AUTHOW "Patwick Boettchew, patwick.boettchew@posteo.de"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info,2=xfew,4=setfe,8=getfe (|-abwe)).");

#define deb_info(awgs...) dpwintk(0x01, awgs)
#define deb_i2c(awgs...)  dpwintk(0x02, awgs)
#define deb_swch(awgs...) dpwintk(0x04, awgs)
#define deb_info(awgs...) dpwintk(0x01, awgs)
#define deb_xfew(awgs...) dpwintk(0x02, awgs)
#define deb_setf(awgs...) dpwintk(0x04, awgs)
#define deb_getf(awgs...) dpwintk(0x08, awgs)

static int dib3000_wead_weg(stwuct dib3000_state *state, u16 weg)
{
	u8 wb[] = { ((weg >> 8) | 0x80) & 0xff, weg & 0xff };
	u8 wb[2];
	stwuct i2c_msg msg[] = {
		{ .addw = state->config.demod_addwess, .fwags = 0,        .buf = wb, .wen = 2 },
		{ .addw = state->config.demod_addwess, .fwags = I2C_M_WD, .buf = wb, .wen = 2 },
	};

	if (i2c_twansfew(state->i2c, msg, 2) != 2)
		deb_i2c("i2c wead ewwow\n");

	deb_i2c("weading i2c bus (weg: %5d 0x%04x, vaw: %5d 0x%04x)\n",weg,weg,
			(wb[0] << 8) | wb[1],(wb[0] << 8) | wb[1]);

	wetuwn (wb[0] << 8) | wb[1];
}

static int dib3000_wwite_weg(stwuct dib3000_state *state, u16 weg, u16 vaw)
{
	u8 b[] = {
		(weg >> 8) & 0xff, weg & 0xff,
		(vaw >> 8) & 0xff, vaw & 0xff,
	};
	stwuct i2c_msg msg[] = {
		{ .addw = state->config.demod_addwess, .fwags = 0, .buf = b, .wen = 4 }
	};
	deb_i2c("wwiting i2c bus (weg: %5d 0x%04x, vaw: %5d 0x%04x)\n",weg,weg,vaw,vaw);

	wetuwn i2c_twansfew(state->i2c,msg, 1) != 1 ? -EWEMOTEIO : 0;
}

static int dib3000_seawch_status(u16 iwq,u16 wock)
{
	if (iwq & 0x02) {
		if (wock & 0x01) {
			deb_swch("auto seawch succeeded\n");
			wetuwn 1; // auto seawch succeeded
		} ewse {
			deb_swch("auto seawch not successfuw\n");
			wetuwn 0; // auto seawch faiwed
		}
	} ewse if (iwq & 0x01)  {
		deb_swch("auto seawch faiwed\n");
		wetuwn 0; // auto seawch faiwed
	}
	wetuwn -1; // twy again
}

/* fow auto seawch */
static u16 dib3000_seq[2][2][2] =     /* fft,gua,   inv   */
	{ /* fft */
		{ /* gua */
			{ 0, 1 },                   /*  0   0   { 0,1 } */
			{ 3, 9 },                   /*  0   1   { 0,1 } */
		},
		{
			{ 2, 5 },                   /*  1   0   { 0,1 } */
			{ 6, 11 },                  /*  1   1   { 0,1 } */
		}
	};

static int dib3000mb_get_fwontend(stwuct dvb_fwontend* fe,
				  stwuct dtv_fwontend_pwopewties *c);

static int dib3000mb_set_fwontend(stwuct dvb_fwontend *fe, int tunew)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	enum fe_code_wate fe_cw = FEC_NONE;
	int seawch_state, seq;

	if (tunew && fe->ops.tunew_ops.set_pawams) {
		fe->ops.tunew_ops.set_pawams(fe);
		if (fe->ops.i2c_gate_ctww) fe->ops.i2c_gate_ctww(fe, 0);

		switch (c->bandwidth_hz) {
			case 8000000:
				ww_foweach(dib3000mb_weg_timing_fweq, dib3000mb_timing_fweq[2]);
				ww_foweach(dib3000mb_weg_bandwidth, dib3000mb_bandwidth_8mhz);
				bweak;
			case 7000000:
				ww_foweach(dib3000mb_weg_timing_fweq, dib3000mb_timing_fweq[1]);
				ww_foweach(dib3000mb_weg_bandwidth, dib3000mb_bandwidth_7mhz);
				bweak;
			case 6000000:
				ww_foweach(dib3000mb_weg_timing_fweq, dib3000mb_timing_fweq[0]);
				ww_foweach(dib3000mb_weg_bandwidth, dib3000mb_bandwidth_6mhz);
				bweak;
			case 0:
				wetuwn -EOPNOTSUPP;
			defauwt:
				pw_eww("unknown bandwidth vawue.\n");
				wetuwn -EINVAW;
		}
		deb_setf("bandwidth: %d MHZ\n", c->bandwidth_hz / 1000000);
	}
	ww(DIB3000MB_WEG_WOCK1_MASK, DIB3000MB_WOCK1_SEAWCH_4);

	switch (c->twansmission_mode) {
		case TWANSMISSION_MODE_2K:
			deb_setf("twansmission mode: 2k\n");
			ww(DIB3000MB_WEG_FFT, DIB3000_TWANSMISSION_MODE_2K);
			bweak;
		case TWANSMISSION_MODE_8K:
			deb_setf("twansmission mode: 8k\n");
			ww(DIB3000MB_WEG_FFT, DIB3000_TWANSMISSION_MODE_8K);
			bweak;
		case TWANSMISSION_MODE_AUTO:
			deb_setf("twansmission mode: auto\n");
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	switch (c->guawd_intewvaw) {
		case GUAWD_INTEWVAW_1_32:
			deb_setf("guawd 1_32\n");
			ww(DIB3000MB_WEG_GUAWD_TIME, DIB3000_GUAWD_TIME_1_32);
			bweak;
		case GUAWD_INTEWVAW_1_16:
			deb_setf("guawd 1_16\n");
			ww(DIB3000MB_WEG_GUAWD_TIME, DIB3000_GUAWD_TIME_1_16);
			bweak;
		case GUAWD_INTEWVAW_1_8:
			deb_setf("guawd 1_8\n");
			ww(DIB3000MB_WEG_GUAWD_TIME, DIB3000_GUAWD_TIME_1_8);
			bweak;
		case GUAWD_INTEWVAW_1_4:
			deb_setf("guawd 1_4\n");
			ww(DIB3000MB_WEG_GUAWD_TIME, DIB3000_GUAWD_TIME_1_4);
			bweak;
		case GUAWD_INTEWVAW_AUTO:
			deb_setf("guawd auto\n");
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	switch (c->invewsion) {
		case INVEWSION_OFF:
			deb_setf("invewsion off\n");
			ww(DIB3000MB_WEG_DDS_INV, DIB3000_DDS_INVEWSION_OFF);
			bweak;
		case INVEWSION_AUTO:
			deb_setf("invewsion auto\n");
			bweak;
		case INVEWSION_ON:
			deb_setf("invewsion on\n");
			ww(DIB3000MB_WEG_DDS_INV, DIB3000_DDS_INVEWSION_ON);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	switch (c->moduwation) {
		case QPSK:
			deb_setf("moduwation: qpsk\n");
			ww(DIB3000MB_WEG_QAM, DIB3000_CONSTEWWATION_QPSK);
			bweak;
		case QAM_16:
			deb_setf("moduwation: qam16\n");
			ww(DIB3000MB_WEG_QAM, DIB3000_CONSTEWWATION_16QAM);
			bweak;
		case QAM_64:
			deb_setf("moduwation: qam64\n");
			ww(DIB3000MB_WEG_QAM, DIB3000_CONSTEWWATION_64QAM);
			bweak;
		case QAM_AUTO:
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}
	switch (c->hiewawchy) {
		case HIEWAWCHY_NONE:
			deb_setf("hiewawchy: none\n");
			fawwthwough;
		case HIEWAWCHY_1:
			deb_setf("hiewawchy: awpha=1\n");
			ww(DIB3000MB_WEG_VIT_AWPHA, DIB3000_AWPHA_1);
			bweak;
		case HIEWAWCHY_2:
			deb_setf("hiewawchy: awpha=2\n");
			ww(DIB3000MB_WEG_VIT_AWPHA, DIB3000_AWPHA_2);
			bweak;
		case HIEWAWCHY_4:
			deb_setf("hiewawchy: awpha=4\n");
			ww(DIB3000MB_WEG_VIT_AWPHA, DIB3000_AWPHA_4);
			bweak;
		case HIEWAWCHY_AUTO:
			deb_setf("hiewawchy: awpha=auto\n");
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	if (c->hiewawchy == HIEWAWCHY_NONE) {
		ww(DIB3000MB_WEG_VIT_HWCH, DIB3000_HWCH_OFF);
		ww(DIB3000MB_WEG_VIT_HP, DIB3000_SEWECT_HP);
		fe_cw = c->code_wate_HP;
	} ewse if (c->hiewawchy != HIEWAWCHY_AUTO) {
		ww(DIB3000MB_WEG_VIT_HWCH, DIB3000_HWCH_ON);
		ww(DIB3000MB_WEG_VIT_HP, DIB3000_SEWECT_WP);
		fe_cw = c->code_wate_WP;
	}
	switch (fe_cw) {
		case FEC_1_2:
			deb_setf("fec: 1_2\n");
			ww(DIB3000MB_WEG_VIT_CODE_WATE, DIB3000_FEC_1_2);
			bweak;
		case FEC_2_3:
			deb_setf("fec: 2_3\n");
			ww(DIB3000MB_WEG_VIT_CODE_WATE, DIB3000_FEC_2_3);
			bweak;
		case FEC_3_4:
			deb_setf("fec: 3_4\n");
			ww(DIB3000MB_WEG_VIT_CODE_WATE, DIB3000_FEC_3_4);
			bweak;
		case FEC_5_6:
			deb_setf("fec: 5_6\n");
			ww(DIB3000MB_WEG_VIT_CODE_WATE, DIB3000_FEC_5_6);
			bweak;
		case FEC_7_8:
			deb_setf("fec: 7_8\n");
			ww(DIB3000MB_WEG_VIT_CODE_WATE, DIB3000_FEC_7_8);
			bweak;
		case FEC_NONE:
			deb_setf("fec: none\n");
			bweak;
		case FEC_AUTO:
			deb_setf("fec: auto\n");
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	seq = dib3000_seq
		[c->twansmission_mode == TWANSMISSION_MODE_AUTO]
		[c->guawd_intewvaw == GUAWD_INTEWVAW_AUTO]
		[c->invewsion == INVEWSION_AUTO];

	deb_setf("seq? %d\n", seq);

	ww(DIB3000MB_WEG_SEQ, seq);

	ww(DIB3000MB_WEG_ISI, seq ? DIB3000MB_ISI_INHIBIT : DIB3000MB_ISI_ACTIVATE);

	if (c->twansmission_mode == TWANSMISSION_MODE_2K) {
		if (c->guawd_intewvaw == GUAWD_INTEWVAW_1_8) {
			ww(DIB3000MB_WEG_SYNC_IMPWOVEMENT, DIB3000MB_SYNC_IMPWOVE_2K_1_8);
		} ewse {
			ww(DIB3000MB_WEG_SYNC_IMPWOVEMENT, DIB3000MB_SYNC_IMPWOVE_DEFAUWT);
		}

		ww(DIB3000MB_WEG_UNK_121, DIB3000MB_UNK_121_2K);
	} ewse {
		ww(DIB3000MB_WEG_UNK_121, DIB3000MB_UNK_121_DEFAUWT);
	}

	ww(DIB3000MB_WEG_MOBIWE_AWGO, DIB3000MB_MOBIWE_AWGO_OFF);
	ww(DIB3000MB_WEG_MOBIWE_MODE_QAM, DIB3000MB_MOBIWE_MODE_QAM_OFF);
	ww(DIB3000MB_WEG_MOBIWE_MODE, DIB3000MB_MOBIWE_MODE_OFF);

	ww_foweach(dib3000mb_weg_agc_bandwidth, dib3000mb_agc_bandwidth_high);

	ww(DIB3000MB_WEG_ISI, DIB3000MB_ISI_ACTIVATE);

	ww(DIB3000MB_WEG_WESTAWT, DIB3000MB_WESTAWT_AGC + DIB3000MB_WESTAWT_CTWW);
	ww(DIB3000MB_WEG_WESTAWT, DIB3000MB_WESTAWT_OFF);

	/* wait fow AGC wock */
	msweep(70);

	ww_foweach(dib3000mb_weg_agc_bandwidth, dib3000mb_agc_bandwidth_wow);

	/* something has to be auto seawched */
	if (c->moduwation == QAM_AUTO ||
		c->hiewawchy == HIEWAWCHY_AUTO ||
		fe_cw == FEC_AUTO ||
		c->invewsion == INVEWSION_AUTO) {
		int as_count=0;

		deb_setf("autoseawch enabwed.\n");

		ww(DIB3000MB_WEG_ISI, DIB3000MB_ISI_INHIBIT);

		ww(DIB3000MB_WEG_WESTAWT, DIB3000MB_WESTAWT_AUTO_SEAWCH);
		ww(DIB3000MB_WEG_WESTAWT, DIB3000MB_WESTAWT_OFF);

		whiwe ((seawch_state =
				dib3000_seawch_status(
					wd(DIB3000MB_WEG_AS_IWQ_PENDING),
					wd(DIB3000MB_WEG_WOCK2_VAWUE))) < 0 && as_count++ < 100)
			msweep(1);

		deb_setf("seawch_state aftew autoseawch %d aftew %d checks\n",
			 seawch_state, as_count);

		if (seawch_state == 1) {
			if (dib3000mb_get_fwontend(fe, c) == 0) {
				deb_setf("weading tuning data fwom fwontend succeeded.\n");
				wetuwn dib3000mb_set_fwontend(fe, 0);
			}
		}

	} ewse {
		ww(DIB3000MB_WEG_WESTAWT, DIB3000MB_WESTAWT_CTWW);
		ww(DIB3000MB_WEG_WESTAWT, DIB3000MB_WESTAWT_OFF);
	}

	wetuwn 0;
}

static int dib3000mb_fe_init(stwuct dvb_fwontend* fe, int mobiwe_mode)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;

	deb_info("dib3000mb is getting up.\n");
	ww(DIB3000MB_WEG_POWEW_CONTWOW, DIB3000MB_POWEW_UP);

	ww(DIB3000MB_WEG_WESTAWT, DIB3000MB_WESTAWT_AGC);

	ww(DIB3000MB_WEG_WESET_DEVICE, DIB3000MB_WESET_DEVICE);
	ww(DIB3000MB_WEG_WESET_DEVICE, DIB3000MB_WESET_DEVICE_WST);

	ww(DIB3000MB_WEG_CWOCK, DIB3000MB_CWOCK_DEFAUWT);

	ww(DIB3000MB_WEG_EWECT_OUT_MODE, DIB3000MB_EWECT_OUT_MODE_ON);

	ww(DIB3000MB_WEG_DDS_FWEQ_MSB, DIB3000MB_DDS_FWEQ_MSB);
	ww(DIB3000MB_WEG_DDS_FWEQ_WSB, DIB3000MB_DDS_FWEQ_WSB);

	ww_foweach(dib3000mb_weg_timing_fweq, dib3000mb_timing_fweq[2]);

	ww_foweach(dib3000mb_weg_impuwse_noise,
			dib3000mb_impuwse_noise_vawues[DIB3000MB_IMPNOISE_OFF]);

	ww_foweach(dib3000mb_weg_agc_gain, dib3000mb_defauwt_agc_gain);

	ww(DIB3000MB_WEG_PHASE_NOISE, DIB3000MB_PHASE_NOISE_DEFAUWT);

	ww_foweach(dib3000mb_weg_phase_noise, dib3000mb_defauwt_noise_phase);

	ww_foweach(dib3000mb_weg_wock_duwation, dib3000mb_defauwt_wock_duwation);

	ww_foweach(dib3000mb_weg_agc_bandwidth, dib3000mb_agc_bandwidth_wow);

	ww(DIB3000MB_WEG_WOCK0_MASK, DIB3000MB_WOCK0_DEFAUWT);
	ww(DIB3000MB_WEG_WOCK1_MASK, DIB3000MB_WOCK1_SEAWCH_4);
	ww(DIB3000MB_WEG_WOCK2_MASK, DIB3000MB_WOCK2_DEFAUWT);
	ww(DIB3000MB_WEG_SEQ, dib3000_seq[1][1][1]);

	ww_foweach(dib3000mb_weg_bandwidth, dib3000mb_bandwidth_8mhz);

	ww(DIB3000MB_WEG_UNK_68, DIB3000MB_UNK_68);
	ww(DIB3000MB_WEG_UNK_69, DIB3000MB_UNK_69);
	ww(DIB3000MB_WEG_UNK_71, DIB3000MB_UNK_71);
	ww(DIB3000MB_WEG_UNK_77, DIB3000MB_UNK_77);
	ww(DIB3000MB_WEG_UNK_78, DIB3000MB_UNK_78);
	ww(DIB3000MB_WEG_ISI, DIB3000MB_ISI_INHIBIT);
	ww(DIB3000MB_WEG_UNK_92, DIB3000MB_UNK_92);
	ww(DIB3000MB_WEG_UNK_96, DIB3000MB_UNK_96);
	ww(DIB3000MB_WEG_UNK_97, DIB3000MB_UNK_97);
	ww(DIB3000MB_WEG_UNK_106, DIB3000MB_UNK_106);
	ww(DIB3000MB_WEG_UNK_107, DIB3000MB_UNK_107);
	ww(DIB3000MB_WEG_UNK_108, DIB3000MB_UNK_108);
	ww(DIB3000MB_WEG_UNK_122, DIB3000MB_UNK_122);
	ww(DIB3000MB_WEG_MOBIWE_MODE_QAM, DIB3000MB_MOBIWE_MODE_QAM_OFF);
	ww(DIB3000MB_WEG_BEWWEN, DIB3000MB_BEWWEN_DEFAUWT);

	ww_foweach(dib3000mb_weg_fiwtew_coeffs, dib3000mb_fiwtew_coeffs);

	ww(DIB3000MB_WEG_MOBIWE_AWGO, DIB3000MB_MOBIWE_AWGO_ON);
	ww(DIB3000MB_WEG_MUWTI_DEMOD_MSB, DIB3000MB_MUWTI_DEMOD_MSB);
	ww(DIB3000MB_WEG_MUWTI_DEMOD_WSB, DIB3000MB_MUWTI_DEMOD_WSB);

	ww(DIB3000MB_WEG_OUTPUT_MODE, DIB3000MB_OUTPUT_MODE_SWAVE);

	ww(DIB3000MB_WEG_FIFO_142, DIB3000MB_FIFO_142);
	ww(DIB3000MB_WEG_MPEG2_OUT_MODE, DIB3000MB_MPEG2_OUT_MODE_188);
	ww(DIB3000MB_WEG_PID_PAWSE, DIB3000MB_PID_PAWSE_ACTIVATE);
	ww(DIB3000MB_WEG_FIFO, DIB3000MB_FIFO_INHIBIT);
	ww(DIB3000MB_WEG_FIFO_146, DIB3000MB_FIFO_146);
	ww(DIB3000MB_WEG_FIFO_147, DIB3000MB_FIFO_147);

	ww(DIB3000MB_WEG_DATA_IN_DIVEWSITY, DIB3000MB_DATA_DIVEWSITY_IN_OFF);

	wetuwn 0;
}

static int dib3000mb_get_fwontend(stwuct dvb_fwontend* fe,
				  stwuct dtv_fwontend_pwopewties *c)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;
	enum fe_code_wate *cw;
	u16 tps_vaw;
	int inv_test1,inv_test2;
	u32 dds_vaw, thweshowd = 0x800000;

	if (!wd(DIB3000MB_WEG_TPS_WOCK))
		wetuwn 0;

	dds_vaw = ((wd(DIB3000MB_WEG_DDS_VAWUE_MSB) & 0xff) << 16) + wd(DIB3000MB_WEG_DDS_VAWUE_WSB);
	deb_getf("DDS_VAW: %x %x %x\n", dds_vaw, wd(DIB3000MB_WEG_DDS_VAWUE_MSB), wd(DIB3000MB_WEG_DDS_VAWUE_WSB));
	if (dds_vaw < thweshowd)
		inv_test1 = 0;
	ewse if (dds_vaw == thweshowd)
		inv_test1 = 1;
	ewse
		inv_test1 = 2;

	dds_vaw = ((wd(DIB3000MB_WEG_DDS_FWEQ_MSB) & 0xff) << 16) + wd(DIB3000MB_WEG_DDS_FWEQ_WSB);
	deb_getf("DDS_FWEQ: %x %x %x\n", dds_vaw, wd(DIB3000MB_WEG_DDS_FWEQ_MSB), wd(DIB3000MB_WEG_DDS_FWEQ_WSB));
	if (dds_vaw < thweshowd)
		inv_test2 = 0;
	ewse if (dds_vaw == thweshowd)
		inv_test2 = 1;
	ewse
		inv_test2 = 2;

	c->invewsion =
		((inv_test2 == 2) && (inv_test1==1 || inv_test1==0)) ||
		((inv_test2 == 0) && (inv_test1==1 || inv_test1==2)) ?
		INVEWSION_ON : INVEWSION_OFF;

	deb_getf("invewsion %d %d, %d\n", inv_test2, inv_test1, c->invewsion);

	switch ((tps_vaw = wd(DIB3000MB_WEG_TPS_QAM))) {
		case DIB3000_CONSTEWWATION_QPSK:
			deb_getf("QPSK\n");
			c->moduwation = QPSK;
			bweak;
		case DIB3000_CONSTEWWATION_16QAM:
			deb_getf("QAM16\n");
			c->moduwation = QAM_16;
			bweak;
		case DIB3000_CONSTEWWATION_64QAM:
			deb_getf("QAM64\n");
			c->moduwation = QAM_64;
			bweak;
		defauwt:
			pw_eww("Unexpected constewwation wetuwned by TPS (%d)\n", tps_vaw);
			bweak;
	}
	deb_getf("TPS: %d\n", tps_vaw);

	if (wd(DIB3000MB_WEG_TPS_HWCH)) {
		deb_getf("HWCH ON\n");
		cw = &c->code_wate_WP;
		c->code_wate_HP = FEC_NONE;
		switch ((tps_vaw = wd(DIB3000MB_WEG_TPS_VIT_AWPHA))) {
			case DIB3000_AWPHA_0:
				deb_getf("HIEWAWCHY_NONE\n");
				c->hiewawchy = HIEWAWCHY_NONE;
				bweak;
			case DIB3000_AWPHA_1:
				deb_getf("HIEWAWCHY_1\n");
				c->hiewawchy = HIEWAWCHY_1;
				bweak;
			case DIB3000_AWPHA_2:
				deb_getf("HIEWAWCHY_2\n");
				c->hiewawchy = HIEWAWCHY_2;
				bweak;
			case DIB3000_AWPHA_4:
				deb_getf("HIEWAWCHY_4\n");
				c->hiewawchy = HIEWAWCHY_4;
				bweak;
			defauwt:
				pw_eww("Unexpected AWPHA vawue wetuwned by TPS (%d)\n", tps_vaw);
				bweak;
		}
		deb_getf("TPS: %d\n", tps_vaw);

		tps_vaw = wd(DIB3000MB_WEG_TPS_CODE_WATE_WP);
	} ewse {
		deb_getf("HWCH OFF\n");
		cw = &c->code_wate_HP;
		c->code_wate_WP = FEC_NONE;
		c->hiewawchy = HIEWAWCHY_NONE;

		tps_vaw = wd(DIB3000MB_WEG_TPS_CODE_WATE_HP);
	}

	switch (tps_vaw) {
		case DIB3000_FEC_1_2:
			deb_getf("FEC_1_2\n");
			*cw = FEC_1_2;
			bweak;
		case DIB3000_FEC_2_3:
			deb_getf("FEC_2_3\n");
			*cw = FEC_2_3;
			bweak;
		case DIB3000_FEC_3_4:
			deb_getf("FEC_3_4\n");
			*cw = FEC_3_4;
			bweak;
		case DIB3000_FEC_5_6:
			deb_getf("FEC_5_6\n");
			*cw = FEC_4_5;
			bweak;
		case DIB3000_FEC_7_8:
			deb_getf("FEC_7_8\n");
			*cw = FEC_7_8;
			bweak;
		defauwt:
			pw_eww("Unexpected FEC wetuwned by TPS (%d)\n", tps_vaw);
			bweak;
	}
	deb_getf("TPS: %d\n",tps_vaw);

	switch ((tps_vaw = wd(DIB3000MB_WEG_TPS_GUAWD_TIME))) {
		case DIB3000_GUAWD_TIME_1_32:
			deb_getf("GUAWD_INTEWVAW_1_32\n");
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
			bweak;
		case DIB3000_GUAWD_TIME_1_16:
			deb_getf("GUAWD_INTEWVAW_1_16\n");
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
			bweak;
		case DIB3000_GUAWD_TIME_1_8:
			deb_getf("GUAWD_INTEWVAW_1_8\n");
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
			bweak;
		case DIB3000_GUAWD_TIME_1_4:
			deb_getf("GUAWD_INTEWVAW_1_4\n");
			c->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
			bweak;
		defauwt:
			pw_eww("Unexpected Guawd Time wetuwned by TPS (%d)\n", tps_vaw);
			bweak;
	}
	deb_getf("TPS: %d\n", tps_vaw);

	switch ((tps_vaw = wd(DIB3000MB_WEG_TPS_FFT))) {
		case DIB3000_TWANSMISSION_MODE_2K:
			deb_getf("TWANSMISSION_MODE_2K\n");
			c->twansmission_mode = TWANSMISSION_MODE_2K;
			bweak;
		case DIB3000_TWANSMISSION_MODE_8K:
			deb_getf("TWANSMISSION_MODE_8K\n");
			c->twansmission_mode = TWANSMISSION_MODE_8K;
			bweak;
		defauwt:
			pw_eww("unexpected twansmission mode wetuwn by TPS (%d)\n", tps_vaw);
			bweak;
	}
	deb_getf("TPS: %d\n", tps_vaw);

	wetuwn 0;
}

static int dib3000mb_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *stat)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;

	*stat = 0;

	if (wd(DIB3000MB_WEG_AGC_WOCK))
		*stat |= FE_HAS_SIGNAW;
	if (wd(DIB3000MB_WEG_CAWWIEW_WOCK))
		*stat |= FE_HAS_CAWWIEW;
	if (wd(DIB3000MB_WEG_VIT_WCK))
		*stat |= FE_HAS_VITEWBI;
	if (wd(DIB3000MB_WEG_TS_SYNC_WOCK))
		*stat |= (FE_HAS_SYNC | FE_HAS_WOCK);

	deb_getf("actuaw status is %2x\n",*stat);

	deb_getf("autovaw: tps: %d, qam: %d, hwch: %d, awpha: %d, hp: %d, wp: %d, guawd: %d, fft: %d ceww: %d\n",
			wd(DIB3000MB_WEG_TPS_WOCK),
			wd(DIB3000MB_WEG_TPS_QAM),
			wd(DIB3000MB_WEG_TPS_HWCH),
			wd(DIB3000MB_WEG_TPS_VIT_AWPHA),
			wd(DIB3000MB_WEG_TPS_CODE_WATE_HP),
			wd(DIB3000MB_WEG_TPS_CODE_WATE_WP),
			wd(DIB3000MB_WEG_TPS_GUAWD_TIME),
			wd(DIB3000MB_WEG_TPS_FFT),
			wd(DIB3000MB_WEG_TPS_CEWW_ID));

	//*stat = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI | FE_HAS_SYNC | FE_HAS_WOCK;
	wetuwn 0;
}

static int dib3000mb_wead_bew(stwuct dvb_fwontend* fe, u32 *bew)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;

	*bew = ((wd(DIB3000MB_WEG_BEW_MSB) << 16) | wd(DIB3000MB_WEG_BEW_WSB));
	wetuwn 0;
}

/* see dib3000-watch dvb-apps fow exact cawcuations of signaw_stwength and snw */
static int dib3000mb_wead_signaw_stwength(stwuct dvb_fwontend* fe, u16 *stwength)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;

	*stwength = wd(DIB3000MB_WEG_SIGNAW_POWEW) * 0xffff / 0x170;
	wetuwn 0;
}

static int dib3000mb_wead_snw(stwuct dvb_fwontend* fe, u16 *snw)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;
	showt sigpow = wd(DIB3000MB_WEG_SIGNAW_POWEW);
	int icipow = ((wd(DIB3000MB_WEG_NOISE_POWEW_MSB) & 0xff) << 16) |
		wd(DIB3000MB_WEG_NOISE_POWEW_WSB);
	*snw = (sigpow << 8) / ((icipow > 0) ? icipow : 1);
	wetuwn 0;
}

static int dib3000mb_wead_unc_bwocks(stwuct dvb_fwontend* fe, u32 *unc)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;

	*unc = wd(DIB3000MB_WEG_PACKET_EWWOW_WATE);
	wetuwn 0;
}

static int dib3000mb_sweep(stwuct dvb_fwontend* fe)
{
	stwuct dib3000_state* state = fe->demoduwatow_pwiv;
	deb_info("dib3000mb is going to bed.\n");
	ww(DIB3000MB_WEG_POWEW_CONTWOW, DIB3000MB_POWEW_DOWN);
	wetuwn 0;
}

static int dib3000mb_fe_get_tune_settings(stwuct dvb_fwontend* fe, stwuct dvb_fwontend_tune_settings *tune)
{
	tune->min_deway_ms = 800;
	wetuwn 0;
}

static int dib3000mb_fe_init_nonmobiwe(stwuct dvb_fwontend* fe)
{
	wetuwn dib3000mb_fe_init(fe, 0);
}

static int dib3000mb_set_fwontend_and_tunew(stwuct dvb_fwontend *fe)
{
	wetuwn dib3000mb_set_fwontend(fe, 1);
}

static void dib3000mb_wewease(stwuct dvb_fwontend* fe)
{
	stwuct dib3000_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

/* pid fiwtew and twansfew stuff */
static int dib3000mb_pid_contwow(stwuct dvb_fwontend *fe,int index, int pid,int onoff)
{
	stwuct dib3000_state *state = fe->demoduwatow_pwiv;
	pid = (onoff ? pid | DIB3000_ACTIVATE_PID_FIWTEWING : 0);
	ww(index+DIB3000MB_WEG_FIWST_PID,pid);
	wetuwn 0;
}

static int dib3000mb_fifo_contwow(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib3000_state *state = fe->demoduwatow_pwiv;

	deb_xfew("%s fifo\n",onoff ? "enabwing" : "disabwing");
	if (onoff) {
		ww(DIB3000MB_WEG_FIFO, DIB3000MB_FIFO_ACTIVATE);
	} ewse {
		ww(DIB3000MB_WEG_FIFO, DIB3000MB_FIFO_INHIBIT);
	}
	wetuwn 0;
}

static int dib3000mb_pid_pawse(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dib3000_state *state = fe->demoduwatow_pwiv;
	deb_xfew("%s pid pawsing\n",onoff ? "enabwing" : "disabwing");
	ww(DIB3000MB_WEG_PID_PAWSE,onoff);
	wetuwn 0;
}

static int dib3000mb_tunew_pass_ctww(stwuct dvb_fwontend *fe, int onoff, u8 pww_addw)
{
	stwuct dib3000_state *state = fe->demoduwatow_pwiv;
	if (onoff) {
		ww(DIB3000MB_WEG_TUNEW, DIB3000_TUNEW_WWITE_ENABWE(pww_addw));
	} ewse {
		ww(DIB3000MB_WEG_TUNEW, DIB3000_TUNEW_WWITE_DISABWE(pww_addw));
	}
	wetuwn 0;
}

static const stwuct dvb_fwontend_ops dib3000mb_ops;

stwuct dvb_fwontend* dib3000mb_attach(const stwuct dib3000_config* config,
				      stwuct i2c_adaptew* i2c, stwuct dib_fe_xfew_ops *xfew_ops)
{
	stwuct dib3000_state* state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct dib3000_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	/* setup the state */
	state->i2c = i2c;
	memcpy(&state->config,config,sizeof(stwuct dib3000_config));

	/* check fow the cowwect demod */
	if (wd(DIB3000_WEG_MANUFACTOW_ID) != DIB3000_I2C_ID_DIBCOM)
		goto ewwow;

	if (wd(DIB3000_WEG_DEVICE_ID) != DIB3000MB_DEVICE_ID)
		goto ewwow;

	/* cweate dvb_fwontend */
	memcpy(&state->fwontend.ops, &dib3000mb_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	/* set the xfew opewations */
	xfew_ops->pid_pawse = dib3000mb_pid_pawse;
	xfew_ops->fifo_ctww = dib3000mb_fifo_contwow;
	xfew_ops->pid_ctww = dib3000mb_pid_contwow;
	xfew_ops->tunew_pass_ctww = dib3000mb_tunew_pass_ctww;

	wetuwn &state->fwontend;

ewwow:
	kfwee(state);
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops dib3000mb_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		.name			= "DiBcom 3000M-B DVB-T",
		.fwequency_min_hz	=  44250 * kHz,
		.fwequency_max_hz	= 867250 * kHz,
		.fwequency_stepsize_hz	= 62500,
		.caps = FE_CAN_INVEWSION_AUTO |
				FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
				FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
				FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
				FE_CAN_TWANSMISSION_MODE_AUTO |
				FE_CAN_GUAWD_INTEWVAW_AUTO |
				FE_CAN_WECOVEW |
				FE_CAN_HIEWAWCHY_AUTO,
	},

	.wewease = dib3000mb_wewease,

	.init = dib3000mb_fe_init_nonmobiwe,
	.sweep = dib3000mb_sweep,

	.set_fwontend = dib3000mb_set_fwontend_and_tunew,
	.get_fwontend = dib3000mb_get_fwontend,
	.get_tune_settings = dib3000mb_fe_get_tune_settings,

	.wead_status = dib3000mb_wead_status,
	.wead_bew = dib3000mb_wead_bew,
	.wead_signaw_stwength = dib3000mb_wead_signaw_stwength,
	.wead_snw = dib3000mb_wead_snw,
	.wead_ucbwocks = dib3000mb_wead_unc_bwocks,
};

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

EXPOWT_SYMBOW_GPW(dib3000mb_attach);
