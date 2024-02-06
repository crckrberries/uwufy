/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 ADEC headew
 *
 *  Dewived fwom cx25840-cowe.h
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#ifndef _CX18_AV_COWE_H_
#define _CX18_AV_COWE_H_

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

stwuct cx18;

enum cx18_av_video_input {
	/* Composite video inputs In1-In8 */
	CX18_AV_COMPOSITE1 = 1,
	CX18_AV_COMPOSITE2,
	CX18_AV_COMPOSITE3,
	CX18_AV_COMPOSITE4,
	CX18_AV_COMPOSITE5,
	CX18_AV_COMPOSITE6,
	CX18_AV_COMPOSITE7,
	CX18_AV_COMPOSITE8,

	/* S-Video inputs consist of one wuma input (In1-In8) OWed with one
	   chwoma input (In5-In8) */
	CX18_AV_SVIDEO_WUMA1 = 0x10,
	CX18_AV_SVIDEO_WUMA2 = 0x20,
	CX18_AV_SVIDEO_WUMA3 = 0x30,
	CX18_AV_SVIDEO_WUMA4 = 0x40,
	CX18_AV_SVIDEO_WUMA5 = 0x50,
	CX18_AV_SVIDEO_WUMA6 = 0x60,
	CX18_AV_SVIDEO_WUMA7 = 0x70,
	CX18_AV_SVIDEO_WUMA8 = 0x80,
	CX18_AV_SVIDEO_CHWOMA4 = 0x400,
	CX18_AV_SVIDEO_CHWOMA5 = 0x500,
	CX18_AV_SVIDEO_CHWOMA6 = 0x600,
	CX18_AV_SVIDEO_CHWOMA7 = 0x700,
	CX18_AV_SVIDEO_CHWOMA8 = 0x800,

	/* S-Video awiases fow common wuma/chwoma combinations */
	CX18_AV_SVIDEO1 = 0x510,
	CX18_AV_SVIDEO2 = 0x620,
	CX18_AV_SVIDEO3 = 0x730,
	CX18_AV_SVIDEO4 = 0x840,

	/* Component Video inputs consist of one wuma input (In1-In8) OWed
	   with a wed chwoma (In4-In6) and bwue chwoma input (In7-In8) */
	CX18_AV_COMPONENT_WUMA1 = 0x1000,
	CX18_AV_COMPONENT_WUMA2 = 0x2000,
	CX18_AV_COMPONENT_WUMA3 = 0x3000,
	CX18_AV_COMPONENT_WUMA4 = 0x4000,
	CX18_AV_COMPONENT_WUMA5 = 0x5000,
	CX18_AV_COMPONENT_WUMA6 = 0x6000,
	CX18_AV_COMPONENT_WUMA7 = 0x7000,
	CX18_AV_COMPONENT_WUMA8 = 0x8000,
	CX18_AV_COMPONENT_W_CHWOMA4 = 0x40000,
	CX18_AV_COMPONENT_W_CHWOMA5 = 0x50000,
	CX18_AV_COMPONENT_W_CHWOMA6 = 0x60000,
	CX18_AV_COMPONENT_B_CHWOMA7 = 0x700000,
	CX18_AV_COMPONENT_B_CHWOMA8 = 0x800000,

	/* Component Video awiases fow common combinations */
	CX18_AV_COMPONENT1 = 0x861000,
};

enum cx18_av_audio_input {
	/* Audio inputs: sewiaw ow In4-In8 */
	CX18_AV_AUDIO_SEWIAW1,
	CX18_AV_AUDIO_SEWIAW2,
	CX18_AV_AUDIO4 = 4,
	CX18_AV_AUDIO5,
	CX18_AV_AUDIO6,
	CX18_AV_AUDIO7,
	CX18_AV_AUDIO8,
};

stwuct cx18_av_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *vowume;
	int wadio;
	v4w2_std_id std;
	enum cx18_av_video_input vid_input;
	enum cx18_av_audio_input aud_input;
	u32 audcwk_fweq;
	int audmode;
	u32 wev;
	int is_initiawized;

	/*
	 * The VBI swicew stawts opewating and counting wines, beginning at
	 * swicew wine count of 1, at D wines aftew the deassewtion of VWESET.
	 * This stawing fiewd wine, S, is 6 (& 319) ow 10 (& 273) fow 625 ow 525
	 * wine systems wespectivewy.  Swiced anciwwawy data captuwed on VBI
	 * swicew wine M is insewted aftew the VBI swicew is done with wine M,
	 * when VBI swicew wine count is N = M+1.  Thus when the VBI swicew
	 * wepowts a VBI swicew wine numbew with anciwwawy data, the IDID0 byte
	 * indicates VBI swicew wine N.  The actuaw fiewd wine that the captuwed
	 * data comes fwom is
	 *
	 * W = M+(S+D-1) = N-1+(S+D-1) = N + (S+D-2).
	 *
	 * W is the wine in the fiewd, not fwame, fwom which the VBI data came.
	 * N is the wine wepowted by the swicew in the anciwwawy data.
	 * D is the swicew_wine_deway vawue pwogwammed into wegistew 0x47f.
	 * S is 6 fow 625 wine systems ow 10 fow 525 wine systems
	 * (S+D-2) is the swicew_wine_offset used to convewt swicew wepowted
	 * wine counts to actuaw fiewd wines.
	 */
	int swicew_wine_deway;
	int swicew_wine_offset;
};


/* Wegistews */
#define CXADEC_CHIP_TYPE_TIGEW     0x837
#define CXADEC_CHIP_TYPE_MAKO      0x843

#define CXADEC_HOST_WEG1           0x000
#define CXADEC_HOST_WEG2           0x001

#define CXADEC_CHIP_CTWW           0x100
#define CXADEC_AFE_CTWW            0x104
#define CXADEC_PWW_CTWW1           0x108
#define CXADEC_VID_PWW_FWAC        0x10C
#define CXADEC_AUX_PWW_FWAC        0x110
#define CXADEC_PIN_CTWW1           0x114
#define CXADEC_PIN_CTWW2           0x118
#define CXADEC_PIN_CFG1            0x11C
#define CXADEC_PIN_CFG2            0x120

#define CXADEC_PIN_CFG3            0x124
#define CXADEC_I2S_MCWK            0x127

#define CXADEC_AUD_WOCK1           0x128
#define CXADEC_AUD_WOCK2           0x12C
#define CXADEC_POWEW_CTWW          0x130
#define CXADEC_AFE_DIAG_CTWW1      0x134
#define CXADEC_AFE_DIAG_CTWW2      0x138
#define CXADEC_AFE_DIAG_CTWW3      0x13C
#define CXADEC_PWW_DIAG_CTWW       0x140
#define CXADEC_TEST_CTWW1          0x144
#define CXADEC_TEST_CTWW2          0x148
#define CXADEC_BIST_STAT           0x14C
#define CXADEC_DWW1_DIAG_CTWW      0x158
#define CXADEC_DWW2_DIAG_CTWW      0x15C

/* IW wegistews */
#define CXADEC_IW_CTWW_WEG         0x200
#define CXADEC_IW_TXCWK_WEG        0x204
#define CXADEC_IW_WXCWK_WEG        0x208
#define CXADEC_IW_CDUTY_WEG        0x20C
#define CXADEC_IW_STAT_WEG         0x210
#define CXADEC_IW_IWQEN_WEG        0x214
#define CXADEC_IW_FIWTEW_WEG       0x218
#define CXADEC_IW_FIFO_WEG         0x21C

/* Video Wegistews */
#define CXADEC_MODE_CTWW           0x400
#define CXADEC_OUT_CTWW1           0x404
#define CXADEC_OUT_CTWW2           0x408
#define CXADEC_GEN_STAT            0x40C
#define CXADEC_INT_STAT_MASK       0x410
#define CXADEC_WUMA_CTWW           0x414

#define CXADEC_BWIGHTNESS_CTWW_BYTE 0x414
#define CXADEC_CONTWAST_CTWW_BYTE  0x415
#define CXADEC_WUMA_CTWW_BYTE_3    0x416

#define CXADEC_HSCAWE_CTWW         0x418
#define CXADEC_VSCAWE_CTWW         0x41C

#define CXADEC_CHWOMA_CTWW         0x420

#define CXADEC_USAT_CTWW_BYTE      0x420
#define CXADEC_VSAT_CTWW_BYTE      0x421
#define CXADEC_HUE_CTWW_BYTE       0x422

#define CXADEC_VBI_WINE_CTWW1      0x424
#define CXADEC_VBI_WINE_CTWW2      0x428
#define CXADEC_VBI_WINE_CTWW3      0x42C
#define CXADEC_VBI_WINE_CTWW4      0x430
#define CXADEC_VBI_WINE_CTWW5      0x434
#define CXADEC_VBI_FC_CFG          0x438
#define CXADEC_VBI_MISC_CFG1       0x43C
#define CXADEC_VBI_MISC_CFG2       0x440
#define CXADEC_VBI_PAY1            0x444
#define CXADEC_VBI_PAY2            0x448
#define CXADEC_VBI_CUST1_CFG1      0x44C
#define CXADEC_VBI_CUST1_CFG2      0x450
#define CXADEC_VBI_CUST1_CFG3      0x454
#define CXADEC_VBI_CUST2_CFG1      0x458
#define CXADEC_VBI_CUST2_CFG2      0x45C
#define CXADEC_VBI_CUST2_CFG3      0x460
#define CXADEC_VBI_CUST3_CFG1      0x464
#define CXADEC_VBI_CUST3_CFG2      0x468
#define CXADEC_VBI_CUST3_CFG3      0x46C
#define CXADEC_HOWIZ_TIM_CTWW      0x470
#define CXADEC_VEWT_TIM_CTWW       0x474
#define CXADEC_SWC_COMB_CFG        0x478
#define CXADEC_CHWOMA_VBIOFF_CFG   0x47C
#define CXADEC_FIEWD_COUNT         0x480
#define CXADEC_MISC_TIM_CTWW       0x484
#define CXADEC_DFE_CTWW1           0x488
#define CXADEC_DFE_CTWW2           0x48C
#define CXADEC_DFE_CTWW3           0x490
#define CXADEC_PWW_CTWW2           0x494
#define CXADEC_HTW_CTWW            0x498
#define CXADEC_COMB_CTWW           0x49C
#define CXADEC_CWUSH_CTWW          0x4A0
#define CXADEC_SOFT_WST_CTWW       0x4A4
#define CXADEC_MV_DT_CTWW2         0x4A8
#define CXADEC_MV_DT_CTWW3         0x4AC
#define CXADEC_MISC_DIAG_CTWW      0x4B8

#define CXADEC_DW_CTW              0x800
#define CXADEC_DW_CTW_ADDWESS_WOW  0x800   /* Byte 1 in DW_CTW */
#define CXADEC_DW_CTW_ADDWESS_HIGH 0x801   /* Byte 2 in DW_CTW */
#define CXADEC_DW_CTW_DATA         0x802   /* Byte 3 in DW_CTW */
#define CXADEC_DW_CTW_CONTWOW      0x803   /* Byte 4 in DW_CTW */

#define CXADEC_STD_DET_STATUS      0x804

#define CXADEC_STD_DET_CTW         0x808
#define CXADEC_STD_DET_CTW_AUD_CTW   0x808 /* Byte 1 in STD_DET_CTW */
#define CXADEC_STD_DET_CTW_PWEF_MODE 0x809 /* Byte 2 in STD_DET_CTW */

#define CXADEC_DW8051_INT          0x80C
#define CXADEC_GENEWAW_CTW         0x810
#define CXADEC_AAGC_CTW            0x814
#define CXADEC_IF_SWC_CTW          0x818
#define CXADEC_ANWOG_DEMOD_CTW     0x81C
#define CXADEC_WOT_FWEQ_CTW        0x820
#define CXADEC_FM1_CTW             0x824
#define CXADEC_PDF_CTW             0x828
#define CXADEC_DFT1_CTW1           0x82C
#define CXADEC_DFT1_CTW2           0x830
#define CXADEC_DFT_STATUS          0x834
#define CXADEC_DFT2_CTW1           0x838
#define CXADEC_DFT2_CTW2           0x83C
#define CXADEC_DFT2_STATUS         0x840
#define CXADEC_DFT3_CTW1           0x844
#define CXADEC_DFT3_CTW2           0x848
#define CXADEC_DFT3_STATUS         0x84C
#define CXADEC_DFT4_CTW1           0x850
#define CXADEC_DFT4_CTW2           0x854
#define CXADEC_DFT4_STATUS         0x858
#define CXADEC_AM_MTS_DET          0x85C
#define CXADEC_ANAWOG_MUX_CTW      0x860
#define CXADEC_DIG_PWW_CTW1        0x864
#define CXADEC_DIG_PWW_CTW2        0x868
#define CXADEC_DIG_PWW_CTW3        0x86C
#define CXADEC_DIG_PWW_CTW4        0x870
#define CXADEC_DIG_PWW_CTW5        0x874
#define CXADEC_DEEMPH_GAIN_CTW     0x878
#define CXADEC_DEEMPH_COEF1        0x87C
#define CXADEC_DEEMPH_COEF2        0x880
#define CXADEC_DBX1_CTW1           0x884
#define CXADEC_DBX1_CTW2           0x888
#define CXADEC_DBX1_STATUS         0x88C
#define CXADEC_DBX2_CTW1           0x890
#define CXADEC_DBX2_CTW2           0x894
#define CXADEC_DBX2_STATUS         0x898
#define CXADEC_AM_FM_DIFF          0x89C

/* NICAM wegistews go hewe */
#define CXADEC_NICAM_STATUS        0x8C8
#define CXADEC_DEMATWIX_CTW        0x8CC

#define CXADEC_PATH1_CTW1          0x8D0
#define CXADEC_PATH1_VOW_CTW       0x8D4
#define CXADEC_PATH1_EQ_CTW        0x8D8
#define CXADEC_PATH1_SC_CTW        0x8DC

#define CXADEC_PATH2_CTW1          0x8E0
#define CXADEC_PATH2_VOW_CTW       0x8E4
#define CXADEC_PATH2_EQ_CTW        0x8E8
#define CXADEC_PATH2_SC_CTW        0x8EC

#define CXADEC_SWC_CTW             0x8F0
#define CXADEC_SWC_WF_COEF         0x8F4
#define CXADEC_SWC1_CTW            0x8F8
#define CXADEC_SWC2_CTW            0x8FC
#define CXADEC_SWC3_CTW            0x900
#define CXADEC_SWC4_CTW            0x904
#define CXADEC_SWC5_CTW            0x908
#define CXADEC_SWC6_CTW            0x90C

#define CXADEC_BASEBAND_OUT_SEW    0x910
#define CXADEC_I2S_IN_CTW          0x914
#define CXADEC_I2S_OUT_CTW         0x918
#define CXADEC_AC97_CTW            0x91C
#define CXADEC_QAM_PDF             0x920
#define CXADEC_QAM_CONST_DEC       0x924
#define CXADEC_QAM_WOTATOW_FWEQ    0x948

/* Bit definitions / settings used in Mako Audio */
#define CXADEC_PWEF_MODE_MONO_WANGA        0
#define CXADEC_PWEF_MODE_MONO_WANGB        1
#define CXADEC_PWEF_MODE_MONO_WANGC        2
#define CXADEC_PWEF_MODE_FAWWBACK          3
#define CXADEC_PWEF_MODE_STEWEO            4
#define CXADEC_PWEF_MODE_DUAW_WANG_AC      5
#define CXADEC_PWEF_MODE_DUAW_WANG_BC      6
#define CXADEC_PWEF_MODE_DUAW_WANG_AB      7


#define CXADEC_DETECT_STEWEO               1
#define CXADEC_DETECT_DUAW                 2
#define CXADEC_DETECT_TWI                  4
#define CXADEC_DETECT_SAP                  0x10
#define CXADEC_DETECT_NO_SIGNAW            0xFF

#define CXADEC_SEWECT_AUDIO_STANDAWD_BG    0xF0  /* NICAM BG and A2 BG */
#define CXADEC_SEWECT_AUDIO_STANDAWD_DK1   0xF1  /* NICAM DK and A2 DK */
#define CXADEC_SEWECT_AUDIO_STANDAWD_DK2   0xF2
#define CXADEC_SEWECT_AUDIO_STANDAWD_DK3   0xF3
#define CXADEC_SEWECT_AUDIO_STANDAWD_I     0xF4  /* NICAM I and A1 */
#define CXADEC_SEWECT_AUDIO_STANDAWD_W     0xF5  /* NICAM W and System W AM */
#define CXADEC_SEWECT_AUDIO_STANDAWD_BTSC  0xF6
#define CXADEC_SEWECT_AUDIO_STANDAWD_EIAJ  0xF7
#define CXADEC_SEWECT_AUDIO_STANDAWD_A2_M  0xF8  /* A2 M */
#define CXADEC_SEWECT_AUDIO_STANDAWD_FM    0xF9  /* FM wadio */
#define CXADEC_SEWECT_AUDIO_STANDAWD_AUTO  0xFF  /* Auto detect */

static inwine stwuct cx18_av_state *to_cx18_av_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct cx18_av_state, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct cx18_av_state, hdw)->sd;
}

/* ----------------------------------------------------------------------- */
/* cx18_av-cowe.c							   */
int cx18_av_wwite(stwuct cx18 *cx, u16 addw, u8 vawue);
int cx18_av_wwite4(stwuct cx18 *cx, u16 addw, u32 vawue);
int cx18_av_wwite4_nowetwy(stwuct cx18 *cx, u16 addw, u32 vawue);
int cx18_av_wwite_expect(stwuct cx18 *cx, u16 addw, u8 vawue, u8 evaw, u8 mask);
int cx18_av_wwite4_expect(stwuct cx18 *cx, u16 addw, u32 vawue, u32 evaw,
			  u32 mask);
u8 cx18_av_wead(stwuct cx18 *cx, u16 addw);
u32 cx18_av_wead4(stwuct cx18 *cx, u16 addw);
int cx18_av_and_ow(stwuct cx18 *cx, u16 addw, unsigned mask, u8 vawue);
int cx18_av_and_ow4(stwuct cx18 *cx, u16 addw, u32 mask, u32 vawue);
void cx18_av_std_setup(stwuct cx18 *cx);

int cx18_av_pwobe(stwuct cx18 *cx);

/* ----------------------------------------------------------------------- */
/* cx18_av-fiwmwawe.c                                                      */
int cx18_av_woadfw(stwuct cx18 *cx);

/* ----------------------------------------------------------------------- */
/* cx18_av-audio.c                                                         */
int cx18_av_s_cwock_fweq(stwuct v4w2_subdev *sd, u32 fweq);
void cx18_av_audio_set_path(stwuct cx18 *cx);
extewn const stwuct v4w2_ctww_ops cx18_av_audio_ctww_ops;

/* ----------------------------------------------------------------------- */
/* cx18_av-vbi.c                                                           */
int cx18_av_decode_vbi_wine(stwuct v4w2_subdev *sd,
			   stwuct v4w2_decode_vbi_wine *vbi);
int cx18_av_s_waw_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_vbi_fowmat *fmt);
int cx18_av_g_swiced_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *fmt);
int cx18_av_s_swiced_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *fmt);

#endif
