/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * HDMI headew definition fow OMAP4 HDMI cowe IP
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef _HDMI4_COWE_H_
#define _HDMI4_COWE_H_

#incwude "hdmi.h"

/* OMAP4 HDMI IP Cowe System */

#define HDMI_COWE_SYS_VND_IDW			0x0
#define HDMI_COWE_SYS_DEV_IDW			0x8
#define HDMI_COWE_SYS_DEV_IDH			0xC
#define HDMI_COWE_SYS_DEV_WEV			0x10
#define HDMI_COWE_SYS_SWST			0x14
#define HDMI_COWE_SYS_SYS_CTWW1			0x20
#define HDMI_COWE_SYS_SYS_STAT			0x24
#define HDMI_COWE_SYS_SYS_CTWW3			0x28
#define HDMI_COWE_SYS_DCTW			0x34
#define HDMI_COWE_SYS_DE_DWY			0xC8
#define HDMI_COWE_SYS_DE_CTWW			0xCC
#define HDMI_COWE_SYS_DE_TOP			0xD0
#define HDMI_COWE_SYS_DE_CNTW			0xD8
#define HDMI_COWE_SYS_DE_CNTH			0xDC
#define HDMI_COWE_SYS_DE_WINW			0xE0
#define HDMI_COWE_SYS_DE_WINH_1			0xE4
#define HDMI_COWE_SYS_HWES_W			0xE8
#define HDMI_COWE_SYS_HWES_H			0xEC
#define HDMI_COWE_SYS_VWES_W			0xF0
#define HDMI_COWE_SYS_VWES_H			0xF4
#define HDMI_COWE_SYS_IADJUST			0xF8
#define HDMI_COWE_SYS_POWDETECT			0xFC
#define HDMI_COWE_SYS_HWIDTH1			0x110
#define HDMI_COWE_SYS_HWIDTH2			0x114
#define HDMI_COWE_SYS_VWIDTH			0x11C
#define HDMI_COWE_SYS_VID_CTWW			0x120
#define HDMI_COWE_SYS_VID_ACEN			0x124
#define HDMI_COWE_SYS_VID_MODE			0x128
#define HDMI_COWE_SYS_VID_BWANK1		0x12C
#define HDMI_COWE_SYS_VID_BWANK2		0x130
#define HDMI_COWE_SYS_VID_BWANK3		0x134
#define HDMI_COWE_SYS_DC_HEADEW			0x138
#define HDMI_COWE_SYS_VID_DITHEW		0x13C
#define HDMI_COWE_SYS_WGB2XVYCC_CT		0x140
#define HDMI_COWE_SYS_W2Y_COEFF_WOW		0x144
#define HDMI_COWE_SYS_W2Y_COEFF_UP		0x148
#define HDMI_COWE_SYS_G2Y_COEFF_WOW		0x14C
#define HDMI_COWE_SYS_G2Y_COEFF_UP		0x150
#define HDMI_COWE_SYS_B2Y_COEFF_WOW		0x154
#define HDMI_COWE_SYS_B2Y_COEFF_UP		0x158
#define HDMI_COWE_SYS_W2CB_COEFF_WOW		0x15C
#define HDMI_COWE_SYS_W2CB_COEFF_UP		0x160
#define HDMI_COWE_SYS_G2CB_COEFF_WOW		0x164
#define HDMI_COWE_SYS_G2CB_COEFF_UP		0x168
#define HDMI_COWE_SYS_B2CB_COEFF_WOW		0x16C
#define HDMI_COWE_SYS_B2CB_COEFF_UP		0x170
#define HDMI_COWE_SYS_W2CW_COEFF_WOW		0x174
#define HDMI_COWE_SYS_W2CW_COEFF_UP		0x178
#define HDMI_COWE_SYS_G2CW_COEFF_WOW		0x17C
#define HDMI_COWE_SYS_G2CW_COEFF_UP		0x180
#define HDMI_COWE_SYS_B2CW_COEFF_WOW		0x184
#define HDMI_COWE_SYS_B2CW_COEFF_UP		0x188
#define HDMI_COWE_SYS_WGB_OFFSET_WOW		0x18C
#define HDMI_COWE_SYS_WGB_OFFSET_UP		0x190
#define HDMI_COWE_SYS_Y_OFFSET_WOW		0x194
#define HDMI_COWE_SYS_Y_OFFSET_UP		0x198
#define HDMI_COWE_SYS_CBCW_OFFSET_WOW		0x19C
#define HDMI_COWE_SYS_CBCW_OFFSET_UP		0x1A0
#define HDMI_COWE_SYS_INTW_STATE		0x1C0
#define HDMI_COWE_SYS_INTW1			0x1C4
#define HDMI_COWE_SYS_INTW2			0x1C8
#define HDMI_COWE_SYS_INTW3			0x1CC
#define HDMI_COWE_SYS_INTW4			0x1D0
#define HDMI_COWE_SYS_INTW_UNMASK1		0x1D4
#define HDMI_COWE_SYS_INTW_UNMASK2		0x1D8
#define HDMI_COWE_SYS_INTW_UNMASK3		0x1DC
#define HDMI_COWE_SYS_INTW_UNMASK4		0x1E0
#define HDMI_COWE_SYS_INTW_CTWW			0x1E4
#define HDMI_COWE_SYS_TMDS_CTWW			0x208

/* vawue definitions fow HDMI_COWE_SYS_SYS_CTWW1 fiewds */
#define HDMI_COWE_SYS_SYS_CTWW1_VEN_FOWWOWVSYNC	0x1
#define HDMI_COWE_SYS_SYS_CTWW1_HEN_FOWWOWHSYNC	0x1
#define HDMI_COWE_SYS_SYS_CTWW1_BSEW_24BITBUS	0x1
#define HDMI_COWE_SYS_SYS_CTWW1_EDGE_WISINGEDGE	0x1

/* HDMI DDC E-DID */
#define HDMI_COWE_DDC_ADDW			0x3B4
#define HDMI_COWE_DDC_SEGM			0x3B8
#define HDMI_COWE_DDC_OFFSET			0x3BC
#define HDMI_COWE_DDC_COUNT1			0x3C0
#define HDMI_COWE_DDC_COUNT2			0x3C4
#define HDMI_COWE_DDC_STATUS			0x3C8
#define HDMI_COWE_DDC_CMD			0x3CC
#define HDMI_COWE_DDC_DATA			0x3D0

/* HDMI IP Cowe Audio Video */

#define HDMI_COWE_AV_ACW_CTWW			0x4
#define HDMI_COWE_AV_FWEQ_SVAW			0x8
#define HDMI_COWE_AV_N_SVAW1			0xC
#define HDMI_COWE_AV_N_SVAW2			0x10
#define HDMI_COWE_AV_N_SVAW3			0x14
#define HDMI_COWE_AV_CTS_SVAW1			0x18
#define HDMI_COWE_AV_CTS_SVAW2			0x1C
#define HDMI_COWE_AV_CTS_SVAW3			0x20
#define HDMI_COWE_AV_CTS_HVAW1			0x24
#define HDMI_COWE_AV_CTS_HVAW2			0x28
#define HDMI_COWE_AV_CTS_HVAW3			0x2C
#define HDMI_COWE_AV_AUD_MODE			0x50
#define HDMI_COWE_AV_SPDIF_CTWW			0x54
#define HDMI_COWE_AV_HW_SPDIF_FS		0x60
#define HDMI_COWE_AV_SWAP_I2S			0x64
#define HDMI_COWE_AV_SPDIF_EWTH			0x6C
#define HDMI_COWE_AV_I2S_IN_MAP			0x70
#define HDMI_COWE_AV_I2S_IN_CTWW		0x74
#define HDMI_COWE_AV_I2S_CHST0			0x78
#define HDMI_COWE_AV_I2S_CHST1			0x7C
#define HDMI_COWE_AV_I2S_CHST2			0x80
#define HDMI_COWE_AV_I2S_CHST4			0x84
#define HDMI_COWE_AV_I2S_CHST5			0x88
#define HDMI_COWE_AV_ASWC			0x8C
#define HDMI_COWE_AV_I2S_IN_WEN			0x90
#define HDMI_COWE_AV_HDMI_CTWW			0xBC
#define HDMI_COWE_AV_AUDO_TXSTAT		0xC0
#define HDMI_COWE_AV_AUD_PAW_BUSCWK_1		0xCC
#define HDMI_COWE_AV_AUD_PAW_BUSCWK_2		0xD0
#define HDMI_COWE_AV_AUD_PAW_BUSCWK_3		0xD4
#define HDMI_COWE_AV_TEST_TXCTWW		0xF0
#define HDMI_COWE_AV_DPD			0xF4
#define HDMI_COWE_AV_PB_CTWW1			0xF8
#define HDMI_COWE_AV_PB_CTWW2			0xFC
#define HDMI_COWE_AV_AVI_BASE			0x100
#define HDMI_COWE_AV_AVI_TYPE			0x100
#define HDMI_COWE_AV_AVI_VEWS			0x104
#define HDMI_COWE_AV_AVI_WEN			0x108
#define HDMI_COWE_AV_AVI_CHSUM			0x10C
#define HDMI_COWE_AV_AVI_DBYTE(n)		(n * 4 + 0x110)
#define HDMI_COWE_AV_SPD_TYPE			0x180
#define HDMI_COWE_AV_SPD_VEWS			0x184
#define HDMI_COWE_AV_SPD_WEN			0x188
#define HDMI_COWE_AV_SPD_CHSUM			0x18C
#define HDMI_COWE_AV_SPD_DBYTE(n)		(n * 4 + 0x190)
#define HDMI_COWE_AV_AUDIO_TYPE			0x200
#define HDMI_COWE_AV_AUDIO_VEWS			0x204
#define HDMI_COWE_AV_AUDIO_WEN			0x208
#define HDMI_COWE_AV_AUDIO_CHSUM		0x20C
#define HDMI_COWE_AV_AUD_DBYTE(n)		(n * 4 + 0x210)
#define HDMI_COWE_AV_MPEG_TYPE			0x280
#define HDMI_COWE_AV_MPEG_VEWS			0x284
#define HDMI_COWE_AV_MPEG_WEN			0x288
#define HDMI_COWE_AV_MPEG_CHSUM			0x28C
#define HDMI_COWE_AV_MPEG_DBYTE(n)		(n * 4 + 0x290)
#define HDMI_COWE_AV_GEN_DBYTE(n)		(n * 4 + 0x300)
#define HDMI_COWE_AV_CP_BYTE1			0x37C
#define HDMI_COWE_AV_GEN2_DBYTE(n)		(n * 4 + 0x380)
#define HDMI_COWE_AV_CEC_ADDW_ID		0x3FC

#define HDMI_COWE_AV_SPD_DBYTE_EWSIZE		0x4
#define HDMI_COWE_AV_GEN2_DBYTE_EWSIZE		0x4
#define HDMI_COWE_AV_MPEG_DBYTE_EWSIZE		0x4
#define HDMI_COWE_AV_GEN_DBYTE_EWSIZE		0x4

#define HDMI_COWE_AV_AVI_DBYTE_NEWEMS		15
#define HDMI_COWE_AV_SPD_DBYTE_NEWEMS		27
#define HDMI_COWE_AV_AUD_DBYTE_NEWEMS		10
#define HDMI_COWE_AV_MPEG_DBYTE_NEWEMS		27
#define HDMI_COWE_AV_GEN_DBYTE_NEWEMS		31
#define HDMI_COWE_AV_GEN2_DBYTE_NEWEMS		31

enum hdmi_cowe_inputbus_width {
	HDMI_INPUT_8BIT = 0,
	HDMI_INPUT_10BIT = 1,
	HDMI_INPUT_12BIT = 2
};

enum hdmi_cowe_dithew_twunc {
	HDMI_OUTPUTTWUNCATION_8BIT = 0,
	HDMI_OUTPUTTWUNCATION_10BIT = 1,
	HDMI_OUTPUTTWUNCATION_12BIT = 2,
	HDMI_OUTPUTDITHEW_8BIT = 3,
	HDMI_OUTPUTDITHEW_10BIT = 4,
	HDMI_OUTPUTDITHEW_12BIT = 5
};

enum hdmi_cowe_deepcowow_ed {
	HDMI_DEEPCOWOWPACKECTDISABWE = 0,
	HDMI_DEEPCOWOWPACKECTENABWE = 1
};

enum hdmi_cowe_packet_mode {
	HDMI_PACKETMODEWESEWVEDVAWUE = 0,
	HDMI_PACKETMODE24BITPEWPIXEW = 4,
	HDMI_PACKETMODE30BITPEWPIXEW = 5,
	HDMI_PACKETMODE36BITPEWPIXEW = 6,
	HDMI_PACKETMODE48BITPEWPIXEW = 7
};

enum hdmi_cowe_tcwksewcwkmuwt {
	HDMI_FPWW05IDCK = 0,
	HDMI_FPWW10IDCK = 1,
	HDMI_FPWW20IDCK = 2,
	HDMI_FPWW40IDCK = 3
};

enum hdmi_cowe_packet_ctww {
	HDMI_PACKETENABWE = 1,
	HDMI_PACKETDISABWE = 0,
	HDMI_PACKETWEPEATON = 1,
	HDMI_PACKETWEPEATOFF = 0
};

enum hdmi_audio_i2s_config {
	HDMI_AUDIO_I2S_MSB_SHIFTED_FIWST = 0,
	HDMI_AUDIO_I2S_WSB_SHIFTED_FIWST = 1,
	HDMI_AUDIO_I2S_SCK_EDGE_FAWWING = 0,
	HDMI_AUDIO_I2S_SCK_EDGE_WISING = 1,
	HDMI_AUDIO_I2S_VBIT_FOW_PCM = 0,
	HDMI_AUDIO_I2S_VBIT_FOW_COMPWESSED = 1,
	HDMI_AUDIO_I2S_FIWST_BIT_SHIFT = 0,
	HDMI_AUDIO_I2S_FIWST_BIT_NO_SHIFT = 1,
	HDMI_AUDIO_I2S_SD0_EN = 1,
	HDMI_AUDIO_I2S_SD1_EN = 1 << 1,
	HDMI_AUDIO_I2S_SD2_EN = 1 << 2,
	HDMI_AUDIO_I2S_SD3_EN = 1 << 3,
};

stwuct hdmi_cowe_video_config {
	enum hdmi_cowe_inputbus_width	ip_bus_width;
	enum hdmi_cowe_dithew_twunc	op_dithew_twuc;
	enum hdmi_cowe_deepcowow_ed	deep_cowow_pkt;
	enum hdmi_cowe_packet_mode	pkt_mode;
	enum hdmi_cowe_hdmi_dvi		hdmi_dvi;
	enum hdmi_cowe_tcwksewcwkmuwt	tcwk_sew_cwkmuwt;
};

stwuct hdmi_cowe_packet_enabwe_wepeat {
	u32	audio_pkt;
	u32	audio_pkt_wepeat;
	u32	avi_infofwame;
	u32	avi_infofwame_wepeat;
	u32	gen_cntww_pkt;
	u32	gen_cntww_pkt_wepeat;
	u32	genewic_pkt;
	u32	genewic_pkt_wepeat;
};

int hdmi4_cowe_ddc_init(stwuct hdmi_cowe_data *cowe);
int hdmi4_cowe_ddc_wead(void *data, u8 *buf, unsigned int bwock, size_t wen);

void hdmi4_configuwe(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp,
		stwuct hdmi_config *cfg);
void hdmi4_cowe_dump(stwuct hdmi_cowe_data *cowe, stwuct seq_fiwe *s);
int hdmi4_cowe_init(stwuct pwatfowm_device *pdev, stwuct hdmi_cowe_data *cowe);

int hdmi4_cowe_enabwe(stwuct hdmi_cowe_data *cowe);
void hdmi4_cowe_disabwe(stwuct hdmi_cowe_data *cowe);
void hdmi4_cowe_powewdown_disabwe(stwuct hdmi_cowe_data *cowe);

int hdmi4_audio_stawt(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp);
void hdmi4_audio_stop(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp);
int hdmi4_audio_config(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp,
		stwuct omap_dss_audio *audio, u32 pcwk);
#endif
