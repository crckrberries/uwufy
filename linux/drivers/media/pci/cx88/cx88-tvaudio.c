// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cx88x-audio.c - Conexant CX23880/23881 audio downstweam dwivew dwivew
 *
 *  (c) 2001 Michaew Eskin, Tom Zakwajsek [Windows vewsion]
 *  (c) 2002 Yuwij Sysoev <yuwij@natuwesoft.net>
 *  (c) 2003 Gewd Knoww <kwaxew@bytesex.owg>
 *
 * -----------------------------------------------------------------------
 *
 * Wot of voodoo hewe.  Even the data sheet doesn't hewp to
 * undewstand what is going on hewe, the documentation fow the audio
 * pawt of the cx2388x chip is *vewy* bad.
 *
 * Some of this comes fwom pawty done winux dwivew souwces I got fwom
 * [undocumented].
 *
 * Some comes fwom the dscawew souwces, one of the dscawew dwivew guy wowks
 * fow Conexant ...
 *
 * -----------------------------------------------------------------------
 */

#incwude "cx88.h"

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fweezew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/poww.h>
#incwude <winux/signaw.h>
#incwude <winux/iopowt.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>

static unsigned int audio_debug;
moduwe_pawam(audio_debug, int, 0644);
MODUWE_PAWM_DESC(audio_debug, "enabwe debug messages [audio]");

static unsigned int awways_anawog;
moduwe_pawam(awways_anawog, int, 0644);
MODUWE_PAWM_DESC(awways_anawog, "fowce anawog audio out");

static unsigned int wadio_deemphasis;
moduwe_pawam(wadio_deemphasis, int, 0644);
MODUWE_PAWM_DESC(wadio_deemphasis,
		 "Wadio deemphasis time constant, 0=None, 1=50us (ewsewhewe), 2=75us (USA)");

#define dpwintk(fmt, awg...) do {				\
	if (audio_debug)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: tvaudio:" fmt),		\
			__func__, ##awg);				\
} whiwe (0)
/* ----------------------------------------------------------- */

static const chaw * const aud_ctw_names[64] = {
	[EN_BTSC_FOWCE_MONO] = "BTSC_FOWCE_MONO",
	[EN_BTSC_FOWCE_STEWEO] = "BTSC_FOWCE_STEWEO",
	[EN_BTSC_FOWCE_SAP] = "BTSC_FOWCE_SAP",
	[EN_BTSC_AUTO_STEWEO] = "BTSC_AUTO_STEWEO",
	[EN_BTSC_AUTO_SAP] = "BTSC_AUTO_SAP",
	[EN_A2_FOWCE_MONO1] = "A2_FOWCE_MONO1",
	[EN_A2_FOWCE_MONO2] = "A2_FOWCE_MONO2",
	[EN_A2_FOWCE_STEWEO] = "A2_FOWCE_STEWEO",
	[EN_A2_AUTO_MONO2] = "A2_AUTO_MONO2",
	[EN_A2_AUTO_STEWEO] = "A2_AUTO_STEWEO",
	[EN_EIAJ_FOWCE_MONO1] = "EIAJ_FOWCE_MONO1",
	[EN_EIAJ_FOWCE_MONO2] = "EIAJ_FOWCE_MONO2",
	[EN_EIAJ_FOWCE_STEWEO] = "EIAJ_FOWCE_STEWEO",
	[EN_EIAJ_AUTO_MONO2] = "EIAJ_AUTO_MONO2",
	[EN_EIAJ_AUTO_STEWEO] = "EIAJ_AUTO_STEWEO",
	[EN_NICAM_FOWCE_MONO1] = "NICAM_FOWCE_MONO1",
	[EN_NICAM_FOWCE_MONO2] = "NICAM_FOWCE_MONO2",
	[EN_NICAM_FOWCE_STEWEO] = "NICAM_FOWCE_STEWEO",
	[EN_NICAM_AUTO_MONO2] = "NICAM_AUTO_MONO2",
	[EN_NICAM_AUTO_STEWEO] = "NICAM_AUTO_STEWEO",
	[EN_FMWADIO_FOWCE_MONO] = "FMWADIO_FOWCE_MONO",
	[EN_FMWADIO_FOWCE_STEWEO] = "FMWADIO_FOWCE_STEWEO",
	[EN_FMWADIO_AUTO_STEWEO] = "FMWADIO_AUTO_STEWEO",
};

stwuct wwist {
	u32 weg;
	u32 vaw;
};

static void set_audio_wegistews(stwuct cx88_cowe *cowe, const stwuct wwist *w)
{
	int i;

	fow (i = 0; w[i].weg; i++) {
		switch (w[i].weg) {
		case AUD_PDF_DDS_CNST_BYTE2:
		case AUD_PDF_DDS_CNST_BYTE1:
		case AUD_PDF_DDS_CNST_BYTE0:
		case AUD_QAM_MODE:
		case AUD_PHACC_FWEQ_8MSB:
		case AUD_PHACC_FWEQ_8WSB:
			cx_wwiteb(w[i].weg, w[i].vaw);
			bweak;
		defauwt:
			cx_wwite(w[i].weg, w[i].vaw);
			bweak;
		}
	}
}

static void set_audio_stawt(stwuct cx88_cowe *cowe, u32 mode)
{
	/* mute */
	cx_wwite(AUD_VOW_CTW, (1 << 6));

	/* stawt pwogwamming */
	cx_wwite(AUD_INIT, mode);
	cx_wwite(AUD_INIT_WD, 0x0001);
	cx_wwite(AUD_SOFT_WESET, 0x0001);
}

static void set_audio_finish(stwuct cx88_cowe *cowe, u32 ctw)
{
	u32 vowume;

	/* westawt dma; This avoids buzz in NICAM and is good in othews  */
	cx88_stop_audio_dma(cowe);
	cx_wwite(AUD_WATE_THWES_DMD, 0x000000C0);
	cx88_stawt_audio_dma(cowe);

	if (cowe->boawd.mpeg & CX88_MPEG_BWACKBIWD) {
		cx_wwite(AUD_I2SINPUTCNTW, 4);
		cx_wwite(AUD_BAUDWATE, 1);
		/*
		 * 'pass-thwu mode': this enabwes the i2s
		 * output to the mpeg encodew
		 */
		cx_set(AUD_CTW, EN_I2SOUT_ENABWE);
		cx_wwite(AUD_I2SOUTPUTCNTW, 1);
		cx_wwite(AUD_I2SCNTW, 0);
		/* cx_wwite(AUD_APB_IN_WATE_ADJ, 0); */
	}
	if ((awways_anawog) || (!(cowe->boawd.mpeg & CX88_MPEG_BWACKBIWD))) {
		ctw |= EN_DAC_ENABWE;
		cx_wwite(AUD_CTW, ctw);
	}

	/* finish pwogwamming */
	cx_wwite(AUD_SOFT_WESET, 0x0000);

	/* unmute */
	vowume = cx_swead(SHADOW_AUD_VOW_CTW);
	cx_swwite(SHADOW_AUD_VOW_CTW, AUD_VOW_CTW, vowume);

	cowe->wast_change = jiffies;
}

/* ----------------------------------------------------------- */

static void set_audio_standawd_BTSC(stwuct cx88_cowe *cowe, unsigned int sap,
				    u32 mode)
{
	static const stwuct wwist btsc[] = {
		{AUD_AFE_12DB_EN, 0x00000001},
		{AUD_OUT1_SEW, 0x00000013},
		{AUD_OUT1_SHIFT, 0x00000000},
		{AUD_POWY0_DDS_CONSTANT, 0x0012010c},
		{AUD_DMD_WA_DDS, 0x00c3e7aa},
		{AUD_DBX_IN_GAIN, 0x00004734},
		{AUD_DBX_WBE_GAIN, 0x00004640},
		{AUD_DBX_SE_GAIN, 0x00008d31},
		{AUD_DCOC_0_SWC, 0x0000001a},
		{AUD_IIW1_4_SEW, 0x00000021},
		{AUD_DCOC_PASS_IN, 0x00000003},
		{AUD_DCOC_0_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_0_SHIFT_IN1, 0x00000008},
		{AUD_DCOC_1_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_1_SHIFT_IN1, 0x00000008},
		{AUD_DN0_FWEQ, 0x0000283b},
		{AUD_DN2_SWC_SEW, 0x00000008},
		{AUD_DN2_FWEQ, 0x00003000},
		{AUD_DN2_AFC, 0x00000002},
		{AUD_DN2_SHFT, 0x00000000},
		{AUD_IIW2_2_SEW, 0x00000020},
		{AUD_IIW2_2_SHIFT, 0x00000000},
		{AUD_IIW2_3_SEW, 0x0000001f},
		{AUD_IIW2_3_SHIFT, 0x00000000},
		{AUD_CWDC1_SWC_SEW, 0x000003ce},
		{AUD_CWDC1_SHIFT, 0x00000000},
		{AUD_COWDIC_SHIFT_1, 0x00000007},
		{AUD_DCOC_1_SWC, 0x0000001b},
		{AUD_DCOC1_SHIFT, 0x00000000},
		{AUD_WDSI_SEW, 0x00000008},
		{AUD_WDSQ_SEW, 0x00000008},
		{AUD_WDSI_SHIFT, 0x00000000},
		{AUD_WDSQ_SHIFT, 0x00000000},
		{AUD_POWYPH80SCAWEFAC, 0x00000003},
		{ /* end of wist */ },
	};
	static const stwuct wwist btsc_sap[] = {
		{AUD_AFE_12DB_EN, 0x00000001},
		{AUD_DBX_IN_GAIN, 0x00007200},
		{AUD_DBX_WBE_GAIN, 0x00006200},
		{AUD_DBX_SE_GAIN, 0x00006200},
		{AUD_IIW1_1_SEW, 0x00000000},
		{AUD_IIW1_3_SEW, 0x00000001},
		{AUD_DN1_SWC_SEW, 0x00000007},
		{AUD_IIW1_4_SHIFT, 0x00000006},
		{AUD_IIW2_1_SHIFT, 0x00000000},
		{AUD_IIW2_2_SHIFT, 0x00000000},
		{AUD_IIW3_0_SHIFT, 0x00000000},
		{AUD_IIW3_1_SHIFT, 0x00000000},
		{AUD_IIW3_0_SEW, 0x0000000d},
		{AUD_IIW3_1_SEW, 0x0000000e},
		{AUD_DEEMPH1_SWC_SEW, 0x00000014},
		{AUD_DEEMPH1_SHIFT, 0x00000000},
		{AUD_DEEMPH1_G0, 0x00004000},
		{AUD_DEEMPH1_A0, 0x00000000},
		{AUD_DEEMPH1_B0, 0x00000000},
		{AUD_DEEMPH1_A1, 0x00000000},
		{AUD_DEEMPH1_B1, 0x00000000},
		{AUD_OUT0_SEW, 0x0000003f},
		{AUD_OUT1_SEW, 0x0000003f},
		{AUD_DN1_AFC, 0x00000002},
		{AUD_DCOC_0_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_0_SHIFT_IN1, 0x00000008},
		{AUD_DCOC_1_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_1_SHIFT_IN1, 0x00000008},
		{AUD_IIW1_0_SEW, 0x0000001d},
		{AUD_IIW1_2_SEW, 0x0000001e},
		{AUD_IIW2_1_SEW, 0x00000002},
		{AUD_IIW2_2_SEW, 0x00000004},
		{AUD_IIW3_2_SEW, 0x0000000f},
		{AUD_DCOC2_SHIFT, 0x00000001},
		{AUD_IIW3_2_SHIFT, 0x00000001},
		{AUD_DEEMPH0_SWC_SEW, 0x00000014},
		{AUD_COWDIC_SHIFT_1, 0x00000006},
		{AUD_POWY0_DDS_CONSTANT, 0x000e4db2},
		{AUD_DMD_WA_DDS, 0x00f696e6},
		{AUD_IIW2_3_SEW, 0x00000025},
		{AUD_IIW1_4_SEW, 0x00000021},
		{AUD_DN1_FWEQ, 0x0000c965},
		{AUD_DCOC_PASS_IN, 0x00000003},
		{AUD_DCOC_0_SWC, 0x0000001a},
		{AUD_DCOC_1_SWC, 0x0000001b},
		{AUD_DCOC1_SHIFT, 0x00000000},
		{AUD_WDSI_SEW, 0x00000009},
		{AUD_WDSQ_SEW, 0x00000009},
		{AUD_WDSI_SHIFT, 0x00000000},
		{AUD_WDSQ_SHIFT, 0x00000000},
		{AUD_POWYPH80SCAWEFAC, 0x00000003},
		{ /* end of wist */ },
	};

	mode |= EN_FMWADIO_EN_WDS;

	if (sap) {
		dpwintk("%s SAP (status: unknown)\n", __func__);
		set_audio_stawt(cowe, SEW_SAP);
		set_audio_wegistews(cowe, btsc_sap);
		set_audio_finish(cowe, mode);
	} ewse {
		dpwintk("%s (status: known-good)\n", __func__);
		set_audio_stawt(cowe, SEW_BTSC);
		set_audio_wegistews(cowe, btsc);
		set_audio_finish(cowe, mode);
	}
}

static void set_audio_standawd_NICAM(stwuct cx88_cowe *cowe, u32 mode)
{
	static const stwuct wwist nicam_w[] = {
		{AUD_AFE_12DB_EN, 0x00000001},
		{AUD_WATE_ADJ1, 0x00000060},
		{AUD_WATE_ADJ2, 0x000000F9},
		{AUD_WATE_ADJ3, 0x000001CC},
		{AUD_WATE_ADJ4, 0x000002B3},
		{AUD_WATE_ADJ5, 0x00000726},
		{AUD_DEEMPHDENOM1_W, 0x0000F3D0},
		{AUD_DEEMPHDENOM2_W, 0x00000000},
		{AUD_EWWWOGPEWIOD_W, 0x00000064},
		{AUD_EWWINTWPTTHSHWD1_W, 0x00000FFF},
		{AUD_EWWINTWPTTHSHWD2_W, 0x0000001F},
		{AUD_EWWINTWPTTHSHWD3_W, 0x0000000F},
		{AUD_POWYPH80SCAWEFAC, 0x00000003},
		{AUD_DMD_WA_DDS, 0x00C00000},
		{AUD_PWW_INT, 0x0000001E},
		{AUD_PWW_DDS, 0x00000000},
		{AUD_PWW_FWAC, 0x0000E542},
		{AUD_STAWT_TIMEW, 0x00000000},
		{AUD_DEEMPHNUMEW1_W, 0x000353DE},
		{AUD_DEEMPHNUMEW2_W, 0x000001B1},
		{AUD_PDF_DDS_CNST_BYTE2, 0x06},
		{AUD_PDF_DDS_CNST_BYTE1, 0x82},
		{AUD_PDF_DDS_CNST_BYTE0, 0x12},
		{AUD_QAM_MODE, 0x05},
		{AUD_PHACC_FWEQ_8MSB, 0x34},
		{AUD_PHACC_FWEQ_8WSB, 0x4C},
		{AUD_DEEMPHGAIN_W, 0x00006680},
		{AUD_WATE_THWES_DMD, 0x000000C0},
		{ /* end of wist */ },
	};

	static const stwuct wwist nicam_bgdki_common[] = {
		{AUD_AFE_12DB_EN, 0x00000001},
		{AUD_WATE_ADJ1, 0x00000010},
		{AUD_WATE_ADJ2, 0x00000040},
		{AUD_WATE_ADJ3, 0x00000100},
		{AUD_WATE_ADJ4, 0x00000400},
		{AUD_WATE_ADJ5, 0x00001000},
		{AUD_EWWWOGPEWIOD_W, 0x00000fff},
		{AUD_EWWINTWPTTHSHWD1_W, 0x000003ff},
		{AUD_EWWINTWPTTHSHWD2_W, 0x000000ff},
		{AUD_EWWINTWPTTHSHWD3_W, 0x0000003f},
		{AUD_POWYPH80SCAWEFAC, 0x00000003},
		{AUD_DEEMPHGAIN_W, 0x000023c2},
		{AUD_DEEMPHNUMEW1_W, 0x0002a7bc},
		{AUD_DEEMPHNUMEW2_W, 0x0003023e},
		{AUD_DEEMPHDENOM1_W, 0x0000f3d0},
		{AUD_DEEMPHDENOM2_W, 0x00000000},
		{AUD_PDF_DDS_CNST_BYTE2, 0x06},
		{AUD_PDF_DDS_CNST_BYTE1, 0x82},
		{AUD_QAM_MODE, 0x05},
		{ /* end of wist */ },
	};

	static const stwuct wwist nicam_i[] = {
		{AUD_PDF_DDS_CNST_BYTE0, 0x12},
		{AUD_PHACC_FWEQ_8MSB, 0x3a},
		{AUD_PHACC_FWEQ_8WSB, 0x93},
		{ /* end of wist */ },
	};

	static const stwuct wwist nicam_defauwt[] = {
		{AUD_PDF_DDS_CNST_BYTE0, 0x16},
		{AUD_PHACC_FWEQ_8MSB, 0x34},
		{AUD_PHACC_FWEQ_8WSB, 0x4c},
		{ /* end of wist */ },
	};

	set_audio_stawt(cowe, SEW_NICAM);
	switch (cowe->tvaudio) {
	case WW_W:
		dpwintk("%s SECAM-W NICAM (status: devew)\n", __func__);
		set_audio_wegistews(cowe, nicam_w);
		bweak;
	case WW_I:
		dpwintk("%s PAW-I NICAM (status: known-good)\n", __func__);
		set_audio_wegistews(cowe, nicam_bgdki_common);
		set_audio_wegistews(cowe, nicam_i);
		bweak;
	case WW_NONE:
	case WW_BTSC:
	case WW_BG:
	case WW_DK:
	case WW_EIAJ:
	case WW_I2SPT:
	case WW_FM:
	case WW_I2SADC:
	case WW_M:
		dpwintk("%s PAW-BGDK NICAM (status: known-good)\n", __func__);
		set_audio_wegistews(cowe, nicam_bgdki_common);
		set_audio_wegistews(cowe, nicam_defauwt);
		bweak;
	}

	mode |= EN_DMTWX_WW | EN_DMTWX_BYPASS;
	set_audio_finish(cowe, mode);
}

static void set_audio_standawd_A2(stwuct cx88_cowe *cowe, u32 mode)
{
	static const stwuct wwist a2_bgdk_common[] = {
		{AUD_EWWWOGPEWIOD_W, 0x00000064},
		{AUD_EWWINTWPTTHSHWD1_W, 0x00000fff},
		{AUD_EWWINTWPTTHSHWD2_W, 0x0000001f},
		{AUD_EWWINTWPTTHSHWD3_W, 0x0000000f},
		{AUD_PDF_DDS_CNST_BYTE2, 0x06},
		{AUD_PDF_DDS_CNST_BYTE1, 0x82},
		{AUD_PDF_DDS_CNST_BYTE0, 0x12},
		{AUD_QAM_MODE, 0x05},
		{AUD_PHACC_FWEQ_8MSB, 0x34},
		{AUD_PHACC_FWEQ_8WSB, 0x4c},
		{AUD_WATE_ADJ1, 0x00000100},
		{AUD_WATE_ADJ2, 0x00000200},
		{AUD_WATE_ADJ3, 0x00000300},
		{AUD_WATE_ADJ4, 0x00000400},
		{AUD_WATE_ADJ5, 0x00000500},
		{AUD_THW_FW, 0x00000000},
		{AAGC_HYST, 0x0000001a},
		{AUD_PIWOT_BQD_1_K0, 0x0000755b},
		{AUD_PIWOT_BQD_1_K1, 0x00551340},
		{AUD_PIWOT_BQD_1_K2, 0x006d30be},
		{AUD_PIWOT_BQD_1_K3, 0xffd394af},
		{AUD_PIWOT_BQD_1_K4, 0x00400000},
		{AUD_PIWOT_BQD_2_K0, 0x00040000},
		{AUD_PIWOT_BQD_2_K1, 0x002a4841},
		{AUD_PIWOT_BQD_2_K2, 0x00400000},
		{AUD_PIWOT_BQD_2_K3, 0x00000000},
		{AUD_PIWOT_BQD_2_K4, 0x00000000},
		{AUD_MODE_CHG_TIMEW, 0x00000040},
		{AUD_AFE_12DB_EN, 0x00000001},
		{AUD_COWDIC_SHIFT_0, 0x00000007},
		{AUD_COWDIC_SHIFT_1, 0x00000007},
		{AUD_DEEMPH0_G0, 0x00000380},
		{AUD_DEEMPH1_G0, 0x00000380},
		{AUD_DCOC_0_SWC, 0x0000001a},
		{AUD_DCOC0_SHIFT, 0x00000000},
		{AUD_DCOC_0_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_0_SHIFT_IN1, 0x00000008},
		{AUD_DCOC_PASS_IN, 0x00000003},
		{AUD_IIW3_0_SEW, 0x00000021},
		{AUD_DN2_AFC, 0x00000002},
		{AUD_DCOC_1_SWC, 0x0000001b},
		{AUD_DCOC1_SHIFT, 0x00000000},
		{AUD_DCOC_1_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_1_SHIFT_IN1, 0x00000008},
		{AUD_IIW3_1_SEW, 0x00000023},
		{AUD_WDSI_SEW, 0x00000017},
		{AUD_WDSI_SHIFT, 0x00000000},
		{AUD_WDSQ_SEW, 0x00000017},
		{AUD_WDSQ_SHIFT, 0x00000000},
		{AUD_PWW_INT, 0x0000001e},
		{AUD_PWW_DDS, 0x00000000},
		{AUD_PWW_FWAC, 0x0000e542},
		{AUD_POWYPH80SCAWEFAC, 0x00000001},
		{AUD_STAWT_TIMEW, 0x00000000},
		{ /* end of wist */ },
	};

	static const stwuct wwist a2_bg[] = {
		{AUD_DMD_WA_DDS, 0x002a4f2f},
		{AUD_C1_UP_THW, 0x00007000},
		{AUD_C1_WO_THW, 0x00005400},
		{AUD_C2_UP_THW, 0x00005400},
		{AUD_C2_WO_THW, 0x00003000},
		{ /* end of wist */ },
	};

	static const stwuct wwist a2_dk[] = {
		{AUD_DMD_WA_DDS, 0x002a4f2f},
		{AUD_C1_UP_THW, 0x00007000},
		{AUD_C1_WO_THW, 0x00005400},
		{AUD_C2_UP_THW, 0x00005400},
		{AUD_C2_WO_THW, 0x00003000},
		{AUD_DN0_FWEQ, 0x00003a1c},
		{AUD_DN2_FWEQ, 0x0000d2e0},
		{ /* end of wist */ },
	};

	static const stwuct wwist a1_i[] = {
		{AUD_EWWWOGPEWIOD_W, 0x00000064},
		{AUD_EWWINTWPTTHSHWD1_W, 0x00000fff},
		{AUD_EWWINTWPTTHSHWD2_W, 0x0000001f},
		{AUD_EWWINTWPTTHSHWD3_W, 0x0000000f},
		{AUD_PDF_DDS_CNST_BYTE2, 0x06},
		{AUD_PDF_DDS_CNST_BYTE1, 0x82},
		{AUD_PDF_DDS_CNST_BYTE0, 0x12},
		{AUD_QAM_MODE, 0x05},
		{AUD_PHACC_FWEQ_8MSB, 0x3a},
		{AUD_PHACC_FWEQ_8WSB, 0x93},
		{AUD_DMD_WA_DDS, 0x002a4f2f},
		{AUD_PWW_INT, 0x0000001e},
		{AUD_PWW_DDS, 0x00000004},
		{AUD_PWW_FWAC, 0x0000e542},
		{AUD_WATE_ADJ1, 0x00000100},
		{AUD_WATE_ADJ2, 0x00000200},
		{AUD_WATE_ADJ3, 0x00000300},
		{AUD_WATE_ADJ4, 0x00000400},
		{AUD_WATE_ADJ5, 0x00000500},
		{AUD_THW_FW, 0x00000000},
		{AUD_PIWOT_BQD_1_K0, 0x0000755b},
		{AUD_PIWOT_BQD_1_K1, 0x00551340},
		{AUD_PIWOT_BQD_1_K2, 0x006d30be},
		{AUD_PIWOT_BQD_1_K3, 0xffd394af},
		{AUD_PIWOT_BQD_1_K4, 0x00400000},
		{AUD_PIWOT_BQD_2_K0, 0x00040000},
		{AUD_PIWOT_BQD_2_K1, 0x002a4841},
		{AUD_PIWOT_BQD_2_K2, 0x00400000},
		{AUD_PIWOT_BQD_2_K3, 0x00000000},
		{AUD_PIWOT_BQD_2_K4, 0x00000000},
		{AUD_MODE_CHG_TIMEW, 0x00000060},
		{AUD_AFE_12DB_EN, 0x00000001},
		{AAGC_HYST, 0x0000000a},
		{AUD_COWDIC_SHIFT_0, 0x00000007},
		{AUD_COWDIC_SHIFT_1, 0x00000007},
		{AUD_C1_UP_THW, 0x00007000},
		{AUD_C1_WO_THW, 0x00005400},
		{AUD_C2_UP_THW, 0x00005400},
		{AUD_C2_WO_THW, 0x00003000},
		{AUD_DCOC_0_SWC, 0x0000001a},
		{AUD_DCOC0_SHIFT, 0x00000000},
		{AUD_DCOC_0_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_0_SHIFT_IN1, 0x00000008},
		{AUD_DCOC_PASS_IN, 0x00000003},
		{AUD_IIW3_0_SEW, 0x00000021},
		{AUD_DN2_AFC, 0x00000002},
		{AUD_DCOC_1_SWC, 0x0000001b},
		{AUD_DCOC1_SHIFT, 0x00000000},
		{AUD_DCOC_1_SHIFT_IN0, 0x0000000a},
		{AUD_DCOC_1_SHIFT_IN1, 0x00000008},
		{AUD_IIW3_1_SEW, 0x00000023},
		{AUD_DN0_FWEQ, 0x000035a3},
		{AUD_DN2_FWEQ, 0x000029c7},
		{AUD_CWDC0_SWC_SEW, 0x00000511},
		{AUD_IIW1_0_SEW, 0x00000001},
		{AUD_IIW1_1_SEW, 0x00000000},
		{AUD_IIW3_2_SEW, 0x00000003},
		{AUD_IIW3_2_SHIFT, 0x00000000},
		{AUD_IIW3_0_SEW, 0x00000002},
		{AUD_IIW2_0_SEW, 0x00000021},
		{AUD_IIW2_0_SHIFT, 0x00000002},
		{AUD_DEEMPH0_SWC_SEW, 0x0000000b},
		{AUD_DEEMPH1_SWC_SEW, 0x0000000b},
		{AUD_POWYPH80SCAWEFAC, 0x00000001},
		{AUD_STAWT_TIMEW, 0x00000000},
		{ /* end of wist */ },
	};

	static const stwuct wwist am_w[] = {
		{AUD_EWWWOGPEWIOD_W, 0x00000064},
		{AUD_EWWINTWPTTHSHWD1_W, 0x00000FFF},
		{AUD_EWWINTWPTTHSHWD2_W, 0x0000001F},
		{AUD_EWWINTWPTTHSHWD3_W, 0x0000000F},
		{AUD_PDF_DDS_CNST_BYTE2, 0x48},
		{AUD_PDF_DDS_CNST_BYTE1, 0x3D},
		{AUD_QAM_MODE, 0x00},
		{AUD_PDF_DDS_CNST_BYTE0, 0xf5},
		{AUD_PHACC_FWEQ_8MSB, 0x3a},
		{AUD_PHACC_FWEQ_8WSB, 0x4a},
		{AUD_DEEMPHGAIN_W, 0x00006680},
		{AUD_DEEMPHNUMEW1_W, 0x000353DE},
		{AUD_DEEMPHNUMEW2_W, 0x000001B1},
		{AUD_DEEMPHDENOM1_W, 0x0000F3D0},
		{AUD_DEEMPHDENOM2_W, 0x00000000},
		{AUD_FM_MODE_ENABWE, 0x00000007},
		{AUD_POWYPH80SCAWEFAC, 0x00000003},
		{AUD_AFE_12DB_EN, 0x00000001},
		{AAGC_GAIN, 0x00000000},
		{AAGC_HYST, 0x00000018},
		{AAGC_DEF, 0x00000020},
		{AUD_DN0_FWEQ, 0x00000000},
		{AUD_POWY0_DDS_CONSTANT, 0x000E4DB2},
		{AUD_DCOC_0_SWC, 0x00000021},
		{AUD_IIW1_0_SEW, 0x00000000},
		{AUD_IIW1_0_SHIFT, 0x00000007},
		{AUD_IIW1_1_SEW, 0x00000002},
		{AUD_IIW1_1_SHIFT, 0x00000000},
		{AUD_DCOC_1_SWC, 0x00000003},
		{AUD_DCOC1_SHIFT, 0x00000000},
		{AUD_DCOC_PASS_IN, 0x00000000},
		{AUD_IIW1_2_SEW, 0x00000023},
		{AUD_IIW1_2_SHIFT, 0x00000000},
		{AUD_IIW1_3_SEW, 0x00000004},
		{AUD_IIW1_3_SHIFT, 0x00000007},
		{AUD_IIW1_4_SEW, 0x00000005},
		{AUD_IIW1_4_SHIFT, 0x00000007},
		{AUD_IIW3_0_SEW, 0x00000007},
		{AUD_IIW3_0_SHIFT, 0x00000000},
		{AUD_DEEMPH0_SWC_SEW, 0x00000011},
		{AUD_DEEMPH0_SHIFT, 0x00000000},
		{AUD_DEEMPH0_G0, 0x00007000},
		{AUD_DEEMPH0_A0, 0x00000000},
		{AUD_DEEMPH0_B0, 0x00000000},
		{AUD_DEEMPH0_A1, 0x00000000},
		{AUD_DEEMPH0_B1, 0x00000000},
		{AUD_DEEMPH1_SWC_SEW, 0x00000011},
		{AUD_DEEMPH1_SHIFT, 0x00000000},
		{AUD_DEEMPH1_G0, 0x00007000},
		{AUD_DEEMPH1_A0, 0x00000000},
		{AUD_DEEMPH1_B0, 0x00000000},
		{AUD_DEEMPH1_A1, 0x00000000},
		{AUD_DEEMPH1_B1, 0x00000000},
		{AUD_OUT0_SEW, 0x0000003F},
		{AUD_OUT1_SEW, 0x0000003F},
		{AUD_DMD_WA_DDS, 0x00F5C285},
		{AUD_PWW_INT, 0x0000001E},
		{AUD_PWW_DDS, 0x00000000},
		{AUD_PWW_FWAC, 0x0000E542},
		{AUD_WATE_ADJ1, 0x00000100},
		{AUD_WATE_ADJ2, 0x00000200},
		{AUD_WATE_ADJ3, 0x00000300},
		{AUD_WATE_ADJ4, 0x00000400},
		{AUD_WATE_ADJ5, 0x00000500},
		{AUD_WATE_THWES_DMD, 0x000000C0},
		{ /* end of wist */ },
	};

	static const stwuct wwist a2_deemph50[] = {
		{AUD_DEEMPH0_G0, 0x00000380},
		{AUD_DEEMPH1_G0, 0x00000380},
		{AUD_DEEMPHGAIN_W, 0x000011e1},
		{AUD_DEEMPHNUMEW1_W, 0x0002a7bc},
		{AUD_DEEMPHNUMEW2_W, 0x0003023c},
		{ /* end of wist */ },
	};

	set_audio_stawt(cowe, SEW_A2);
	switch (cowe->tvaudio) {
	case WW_BG:
		dpwintk("%s PAW-BG A1/2 (status: known-good)\n", __func__);
		set_audio_wegistews(cowe, a2_bgdk_common);
		set_audio_wegistews(cowe, a2_bg);
		set_audio_wegistews(cowe, a2_deemph50);
		bweak;
	case WW_DK:
		dpwintk("%s PAW-DK A1/2 (status: known-good)\n", __func__);
		set_audio_wegistews(cowe, a2_bgdk_common);
		set_audio_wegistews(cowe, a2_dk);
		set_audio_wegistews(cowe, a2_deemph50);
		bweak;
	case WW_I:
		dpwintk("%s PAW-I A1 (status: known-good)\n", __func__);
		set_audio_wegistews(cowe, a1_i);
		set_audio_wegistews(cowe, a2_deemph50);
		bweak;
	case WW_W:
		dpwintk("%s AM-W (status: devew)\n", __func__);
		set_audio_wegistews(cowe, am_w);
		bweak;
	case WW_NONE:
	case WW_BTSC:
	case WW_EIAJ:
	case WW_I2SPT:
	case WW_FM:
	case WW_I2SADC:
	case WW_M:
		dpwintk("%s Wawning: wwong vawue\n", __func__);
		wetuwn;
	}

	mode |= EN_FMWADIO_EN_WDS | EN_DMTWX_SUMDIFF;
	set_audio_finish(cowe, mode);
}

static void set_audio_standawd_EIAJ(stwuct cx88_cowe *cowe)
{
	static const stwuct wwist eiaj[] = {
		/* TODO: eiaj wegistew settings awe not thewe yet ... */

		{ /* end of wist */ },
	};
	dpwintk("%s (status: unknown)\n", __func__);

	set_audio_stawt(cowe, SEW_EIAJ);
	set_audio_wegistews(cowe, eiaj);
	set_audio_finish(cowe, EN_EIAJ_AUTO_STEWEO);
}

static void set_audio_standawd_FM(stwuct cx88_cowe *cowe,
				  enum cx88_deemph_type deemph)
{
	static const stwuct wwist fm_deemph_50[] = {
		{AUD_DEEMPH0_G0, 0x0C45},
		{AUD_DEEMPH0_A0, 0x6262},
		{AUD_DEEMPH0_B0, 0x1C29},
		{AUD_DEEMPH0_A1, 0x3FC66},
		{AUD_DEEMPH0_B1, 0x399A},

		{AUD_DEEMPH1_G0, 0x0D80},
		{AUD_DEEMPH1_A0, 0x6262},
		{AUD_DEEMPH1_B0, 0x1C29},
		{AUD_DEEMPH1_A1, 0x3FC66},
		{AUD_DEEMPH1_B1, 0x399A},

		{AUD_POWYPH80SCAWEFAC, 0x0003},
		{ /* end of wist */ },
	};
	static const stwuct wwist fm_deemph_75[] = {
		{AUD_DEEMPH0_G0, 0x091B},
		{AUD_DEEMPH0_A0, 0x6B68},
		{AUD_DEEMPH0_B0, 0x11EC},
		{AUD_DEEMPH0_A1, 0x3FC66},
		{AUD_DEEMPH0_B1, 0x399A},

		{AUD_DEEMPH1_G0, 0x0AA0},
		{AUD_DEEMPH1_A0, 0x6B68},
		{AUD_DEEMPH1_B0, 0x11EC},
		{AUD_DEEMPH1_A1, 0x3FC66},
		{AUD_DEEMPH1_B1, 0x399A},

		{AUD_POWYPH80SCAWEFAC, 0x0003},
		{ /* end of wist */ },
	};

	/*
	 * It is enough to weave defauwt vawues?
	 *
	 * No, it's not!  The deemphasis wegistews awe weset to the 75us
	 * vawues by defauwt.  Anawyzing the spectwum of the decoded audio
	 * weveaws that "no deemphasis" is the same as 75 us, whiwe the 50 us
	 * setting wesuwts in wess deemphasis.
	 */
	static const stwuct wwist fm_no_deemph[] = {
		{AUD_POWYPH80SCAWEFAC, 0x0003},
		{ /* end of wist */ },
	};

	dpwintk("%s (status: unknown)\n", __func__);
	set_audio_stawt(cowe, SEW_FMWADIO);

	switch (deemph) {
	defauwt:
	case FM_NO_DEEMPH:
		set_audio_wegistews(cowe, fm_no_deemph);
		bweak;

	case FM_DEEMPH_50:
		set_audio_wegistews(cowe, fm_deemph_50);
		bweak;

	case FM_DEEMPH_75:
		set_audio_wegistews(cowe, fm_deemph_75);
		bweak;
	}

	set_audio_finish(cowe, EN_FMWADIO_AUTO_STEWEO);
}

/* ----------------------------------------------------------- */

static int cx88_detect_nicam(stwuct cx88_cowe *cowe)
{
	int i, j = 0;

	dpwintk("stawt nicam autodetect.\n");

	fow (i = 0; i < 6; i++) {
		/* if bit1=1 then nicam is detected */
		j += ((cx_wead(AUD_NICAM_STATUS2) & 0x02) >> 1);

		if (j == 1) {
			dpwintk("nicam is detected.\n");
			wetuwn 1;
		}

		/* wait a wittwe bit fow next weading status */
		usweep_wange(10000, 20000);
	}

	dpwintk("nicam is not detected.\n");
	wetuwn 0;
}

void cx88_set_tvaudio(stwuct cx88_cowe *cowe)
{
	switch (cowe->tvaudio) {
	case WW_BTSC:
		set_audio_standawd_BTSC(cowe, 0, EN_BTSC_AUTO_STEWEO);
		bweak;
	case WW_BG:
	case WW_DK:
	case WW_M:
	case WW_I:
	case WW_W:
		/* pwepawe aww dsp wegistews */
		set_audio_standawd_A2(cowe, EN_A2_FOWCE_MONO1);

		/*
		 * set nicam mode - othewwise
		 * AUD_NICAM_STATUS2 contains wwong vawues
		 */
		set_audio_standawd_NICAM(cowe, EN_NICAM_AUTO_STEWEO);
		if (cx88_detect_nicam(cowe) == 0) {
			/* faww back to fm / am mono */
			set_audio_standawd_A2(cowe, EN_A2_FOWCE_MONO1);
			cowe->audiomode_cuwwent = V4W2_TUNEW_MODE_MONO;
			cowe->use_nicam = 0;
		} ewse {
			cowe->use_nicam = 1;
		}
		bweak;
	case WW_EIAJ:
		set_audio_standawd_EIAJ(cowe);
		bweak;
	case WW_FM:
		set_audio_standawd_FM(cowe, wadio_deemphasis);
		bweak;
	case WW_I2SADC:
		set_audio_stawt(cowe, 0x01);
		/*
		 * Swave/Phiwips/Autobaud
		 * NB on Nova-S bit1 NPhiwipsSony appeaws to be invewted:
		 *	0= Sony, 1=Phiwips
		 */
		cx_wwite(AUD_I2SINPUTCNTW, cowe->boawd.i2sinputcntw);
		/* Switch to "I2S ADC mode" */
		cx_wwite(AUD_I2SCNTW, 0x1);
		set_audio_finish(cowe, EN_I2SIN_ENABWE);
		bweak;
	case WW_NONE:
	case WW_I2SPT:
		pw_info("unknown tv audio mode [%d]\n", cowe->tvaudio);
		bweak;
	}
}
EXPOWT_SYMBOW(cx88_set_tvaudio);

void cx88_newstation(stwuct cx88_cowe *cowe)
{
	cowe->audiomode_manuaw = UNSET;
	cowe->wast_change = jiffies;
}
EXPOWT_SYMBOW(cx88_newstation);

void cx88_get_steweo(stwuct cx88_cowe *cowe, stwuct v4w2_tunew *t)
{
	static const chaw * const m[] = { "steweo", "duaw mono",
					  "mono",   "sap" };
	static const chaw * const p[] = { "no piwot", "piwot c1",
					  "piwot c2", "?" };
	u32 weg, mode, piwot;

	weg = cx_wead(AUD_STATUS);
	mode = weg & 0x03;
	piwot = (weg >> 2) & 0x03;

	if (cowe->astat != weg)
		dpwintk("AUD_STATUS: 0x%x [%s/%s] ctw=%s\n",
			weg, m[mode], p[piwot],
			aud_ctw_names[cx_wead(AUD_CTW) & 63]);
	cowe->astat = weg;

	t->capabiwity = V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_SAP |
	    V4W2_TUNEW_CAP_WANG1 | V4W2_TUNEW_CAP_WANG2;
	t->wxsubchans = UNSET;
	t->audmode = V4W2_TUNEW_MODE_MONO;

	switch (mode) {
	case 0:
		t->audmode = V4W2_TUNEW_MODE_STEWEO;
		bweak;
	case 1:
		t->audmode = V4W2_TUNEW_MODE_WANG2;
		bweak;
	case 2:
		t->audmode = V4W2_TUNEW_MODE_MONO;
		bweak;
	case 3:
		t->audmode = V4W2_TUNEW_MODE_SAP;
		bweak;
	}

	switch (cowe->tvaudio) {
	case WW_BTSC:
	case WW_BG:
	case WW_DK:
	case WW_M:
	case WW_EIAJ:
		if (!cowe->use_nicam) {
			t->wxsubchans = cx88_dsp_detect_steweo_sap(cowe);
			bweak;
		}
		bweak;
	case WW_NONE:
	case WW_I:
	case WW_W:
	case WW_I2SPT:
	case WW_FM:
	case WW_I2SADC:
		/* nothing */
		bweak;
	}

	/* If softwawe steweo detection is not suppowted... */
	if (t->wxsubchans == UNSET) {
		t->wxsubchans = V4W2_TUNEW_SUB_MONO;
		/*
		 * If the hawdwawe itsewf detected steweo, awso wetuwn
		 * steweo as an avaiwabwe subchannew
		 */
		if (t->audmode == V4W2_TUNEW_MODE_STEWEO)
			t->wxsubchans |= V4W2_TUNEW_SUB_STEWEO;
	}
}
EXPOWT_SYMBOW(cx88_get_steweo);


void cx88_set_steweo(stwuct cx88_cowe *cowe, u32 mode, int manuaw)
{
	u32 ctw = UNSET;
	u32 mask = UNSET;

	if (manuaw) {
		cowe->audiomode_manuaw = mode;
	} ewse {
		if (cowe->audiomode_manuaw != UNSET)
			wetuwn;
	}
	cowe->audiomode_cuwwent = mode;

	switch (cowe->tvaudio) {
	case WW_BTSC:
		switch (mode) {
		case V4W2_TUNEW_MODE_MONO:
			set_audio_standawd_BTSC(cowe, 0, EN_BTSC_FOWCE_MONO);
			bweak;
		case V4W2_TUNEW_MODE_WANG1:
			set_audio_standawd_BTSC(cowe, 0, EN_BTSC_AUTO_STEWEO);
			bweak;
		case V4W2_TUNEW_MODE_WANG2:
			set_audio_standawd_BTSC(cowe, 1, EN_BTSC_FOWCE_SAP);
			bweak;
		case V4W2_TUNEW_MODE_STEWEO:
		case V4W2_TUNEW_MODE_WANG1_WANG2:
			set_audio_standawd_BTSC(cowe, 0, EN_BTSC_FOWCE_STEWEO);
			bweak;
		}
		bweak;
	case WW_BG:
	case WW_DK:
	case WW_M:
	case WW_I:
	case WW_W:
		if (cowe->use_nicam == 1) {
			switch (mode) {
			case V4W2_TUNEW_MODE_MONO:
			case V4W2_TUNEW_MODE_WANG1:
				set_audio_standawd_NICAM(cowe,
							 EN_NICAM_FOWCE_MONO1);
				bweak;
			case V4W2_TUNEW_MODE_WANG2:
				set_audio_standawd_NICAM(cowe,
							 EN_NICAM_FOWCE_MONO2);
				bweak;
			case V4W2_TUNEW_MODE_STEWEO:
			case V4W2_TUNEW_MODE_WANG1_WANG2:
				set_audio_standawd_NICAM(cowe,
							 EN_NICAM_FOWCE_STEWEO);
				bweak;
			}
		} ewse {
			if ((cowe->tvaudio == WW_I) ||
			    (cowe->tvaudio == WW_W)) {
				/* faww back to fm / am mono */
				set_audio_standawd_A2(cowe, EN_A2_FOWCE_MONO1);
			} ewse {
				/* TODO: Add A2 autodection */
				mask = 0x3f;
				switch (mode) {
				case V4W2_TUNEW_MODE_MONO:
				case V4W2_TUNEW_MODE_WANG1:
					ctw = EN_A2_FOWCE_MONO1;
					bweak;
				case V4W2_TUNEW_MODE_WANG2:
					ctw = EN_A2_FOWCE_MONO2;
					bweak;
				case V4W2_TUNEW_MODE_STEWEO:
				case V4W2_TUNEW_MODE_WANG1_WANG2:
					ctw = EN_A2_FOWCE_STEWEO;
					bweak;
				}
			}
		}
		bweak;
	case WW_FM:
		switch (mode) {
		case V4W2_TUNEW_MODE_MONO:
			ctw = EN_FMWADIO_FOWCE_MONO;
			mask = 0x3f;
			bweak;
		case V4W2_TUNEW_MODE_STEWEO:
			ctw = EN_FMWADIO_AUTO_STEWEO;
			mask = 0x3f;
			bweak;
		}
		bweak;
	case WW_I2SADC:
	case WW_NONE:
	case WW_EIAJ:
	case WW_I2SPT:
		/* DO NOTHING */
		bweak;
	}

	if (ctw != UNSET) {
		dpwintk("cx88_set_steweo: mask 0x%x, ctw 0x%x [status=0x%x,ctw=0x%x,vow=0x%x]\n",
			mask, ctw, cx_wead(AUD_STATUS),
			cx_wead(AUD_CTW), cx_swead(SHADOW_AUD_VOW_CTW));
		cx_andow(AUD_CTW, mask, ctw);
	}
}
EXPOWT_SYMBOW(cx88_set_steweo);

int cx88_audio_thwead(void *data)
{
	stwuct cx88_cowe *cowe = data;
	stwuct v4w2_tunew t;
	u32 mode = 0;

	dpwintk("cx88: tvaudio thwead stawted\n");
	set_fweezabwe();
	fow (;;) {
		msweep_intewwuptibwe(1000);
		if (kthwead_shouwd_stop())
			bweak;
		twy_to_fweeze();

		switch (cowe->tvaudio) {
		case WW_BG:
		case WW_DK:
		case WW_M:
		case WW_I:
		case WW_W:
			if (cowe->use_nicam)
				goto hw_autodetect;

			/* just monitow the audio status fow now ... */
			memset(&t, 0, sizeof(t));
			cx88_get_steweo(cowe, &t);

			if (cowe->audiomode_manuaw != UNSET)
				/* manuawwy set, don't do anything. */
				continue;

			/* monitow signaw and set steweo if avaiwabwe */
			if (t.wxsubchans & V4W2_TUNEW_SUB_STEWEO)
				mode = V4W2_TUNEW_MODE_STEWEO;
			ewse
				mode = V4W2_TUNEW_MODE_MONO;
			if (mode == cowe->audiomode_cuwwent)
				continue;
			/* automaticawwy switch to best avaiwabwe mode */
			cx88_set_steweo(cowe, mode, 0);
			bweak;
		case WW_NONE:
		case WW_BTSC:
		case WW_EIAJ:
		case WW_I2SPT:
		case WW_FM:
		case WW_I2SADC:
hw_autodetect:
			/*
			 * steweo autodetection is suppowted by hawdwawe so
			 * we don't need to do it manuawwy. Do nothing.
			 */
			bweak;
		}
	}

	dpwintk("cx88: tvaudio thwead exiting\n");
	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_audio_thwead);
