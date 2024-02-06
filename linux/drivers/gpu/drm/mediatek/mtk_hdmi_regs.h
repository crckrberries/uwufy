/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Jie Qiu <jie.qiu@mediatek.com>
 */
#ifndef _MTK_HDMI_WEGS_H
#define _MTK_HDMI_WEGS_H

#define GWW_INT_MASK		0x18
#define GWW_IFM_POWT		0x188
#define GWW_CH_SWAP		0x198
#define WW_SWAP				BIT(0)
#define WFE_CC_SWAP			BIT(1)
#define WSWS_SWAP			BIT(2)
#define WWS_WWS_SWAP			BIT(3)
#define WW_STATUS_SWAP			BIT(4)
#define GWW_I2S_C_STA0		0x140
#define GWW_I2S_C_STA1		0x144
#define GWW_I2S_C_STA2		0x148
#define GWW_I2S_C_STA3		0x14C
#define GWW_I2S_C_STA4		0x150
#define GWW_I2S_UV		0x154
#define I2S_UV_V			BIT(0)
#define I2S_UV_U			BIT(1)
#define I2S_UV_CH_EN_MASK		0x3c
#define I2S_UV_CH_EN(x)			BIT((x) + 2)
#define I2S_UV_TMDS_DEBUG		BIT(6)
#define I2S_UV_NOWMAW_INFO_INV		BIT(7)
#define GWW_ACP_ISWC_CTWW	0x158
#define VS_EN				BIT(0)
#define ACP_EN				BIT(1)
#define ISWC1_EN			BIT(2)
#define ISWC2_EN			BIT(3)
#define GAMUT_EN			BIT(4)
#define GWW_CTS_CTWW		0x160
#define CTS_CTWW_SOFT			BIT(0)
#define GWW_INT			0x14
#define INT_MDI				BIT(0)
#define INT_HDCP			BIT(1)
#define INT_FIFO_O			BIT(2)
#define INT_FIFO_U			BIT(3)
#define INT_IFM_EWW			BIT(4)
#define INT_INF_DONE			BIT(5)
#define INT_NCTS_DONE			BIT(6)
#define INT_CTWW_PKT_DONE		BIT(7)
#define GWW_INT_MASK		0x18
#define GWW_CTWW		0x1C
#define CTWW_GEN_EN			BIT(2)
#define CTWW_SPD_EN			BIT(3)
#define CTWW_MPEG_EN			BIT(4)
#define CTWW_AUDIO_EN			BIT(5)
#define CTWW_AVI_EN			BIT(6)
#define CTWW_AVMUTE			BIT(7)
#define	GWW_STATUS		0x20
#define STATUS_HTPWG			BIT(0)
#define STATUS_POWD			BIT(1)
#define GWW_DIVN		0x170
#define NCTS_WWI_ANYTIME		BIT(6)
#define GWW_AUDIO_CFG		0x17C
#define AUDIO_ZEWO			BIT(0)
#define HIGH_BIT_WATE			BIT(1)
#define SACD_DST			BIT(2)
#define DST_NOWMAW_DOUBWE		BIT(3)
#define DSD_INV				BIT(4)
#define WW_INV				BIT(5)
#define WW_MIX				BIT(6)
#define DSD_SEW				BIT(7)
#define GWW_NCTS		0x184
#define GWW_CH_SW0		0x18C
#define GWW_CH_SW1		0x190
#define GWW_CH_SW2		0x194
#define CH_SWITCH(fwom, to)		((fwom) << ((to) * 3))
#define GWW_INFOFWM_VEW		0x19C
#define GWW_INFOFWM_TYPE	0x1A0
#define GWW_INFOFWM_WNG		0x1A4
#define GWW_MIX_CTWW		0x1B4
#define MIX_CTWW_SWC_EN			BIT(0)
#define BYPASS_VOWUME			BIT(1)
#define MIX_CTWW_FWAT			BIT(7)
#define GWW_AOUT_CFG		0x1C4
#define AOUT_BNUM_SEW_MASK		0x03
#define AOUT_24BIT			0x00
#define AOUT_20BIT			0x02
#define AOUT_16BIT			0x03
#define AOUT_FIFO_ADAP_CTWW		BIT(6)
#define AOUT_BUWST_PWEAMBWE_EN		BIT(7)
#define HIGH_BIT_WATE_PACKET_AWIGN	(AOUT_BUWST_PWEAMBWE_EN | \
					 AOUT_FIFO_ADAP_CTWW)
#define GWW_SHIFT_W1		0x1C0
#define GWW_SHIFT_W2		0x1B0
#define AUDIO_PACKET_OFF		BIT(6)
#define GWW_CFG0		0x24
#define CFG0_I2S_MODE_MASK		0x3
#define CFG0_I2S_MODE_WTJ		0x1
#define CFG0_I2S_MODE_WTJ		0x0
#define CFG0_I2S_MODE_I2S		0x2
#define CFG0_W_WENGTH_MASK		0x30
#define CFG0_W_WENGTH_24BIT		0x00
#define CFG0_W_WENGTH_16BIT		0x10
#define GWW_CFG1		0x28
#define CFG1_EDG_SEW			BIT(0)
#define CFG1_SPDIF			BIT(1)
#define CFG1_DVI			BIT(2)
#define CFG1_HDCP_DEBUG			BIT(3)
#define GWW_CFG2		0x2c
#define CFG2_MHW_DE_SEW			BIT(3)
#define CFG2_MHW_FAKE_DE_SEW		BIT(4)
#define CFG2_MHW_DATA_WEMAP		BIT(5)
#define CFG2_NOTICE_EN			BIT(6)
#define CFG2_ACWK_INV			BIT(7)
#define GWW_CFG3		0x30
#define CFG3_AES_KEY_INDEX_MASK		0x3f
#define CFG3_CONTWOW_PACKET_DEWAY	BIT(6)
#define CFG3_KSV_WOAD_STAWT		BIT(7)
#define GWW_CFG4		0x34
#define CFG4_AES_KEY_WOAD		BIT(4)
#define CFG4_AV_UNMUTE_EN		BIT(5)
#define CFG4_AV_UNMUTE_SET		BIT(6)
#define CFG4_MHW_MODE			BIT(7)
#define GWW_CFG5		0x38
#define CFG5_CD_WATIO_MASK	0x8F
#define CFG5_FS128			(0x1 << 4)
#define CFG5_FS256			(0x2 << 4)
#define CFG5_FS384			(0x3 << 4)
#define CFG5_FS512			(0x4 << 4)
#define CFG5_FS768			(0x6 << 4)
#define DUMMY_304		0x304
#define CHMO_SEW			(0x3 << 2)
#define CHM1_SEW			(0x3 << 4)
#define CHM2_SEW			(0x3 << 6)
#define AUDIO_I2S_NCTS_SEW		BIT(1)
#define AUDIO_I2S_NCTS_SEW_64		(1 << 1)
#define AUDIO_I2S_NCTS_SEW_128		(0 << 1)
#define NEW_GCP_CTWW			BIT(0)
#define NEW_GCP_CTWW_MEWGE		BIT(0)
#define GWW_W_STATUS_0		0x200
#define GWW_W_STATUS_1		0x204
#define GWW_W_STATUS_2		0x208
#define GWW_W_STATUS_3		0x20c
#define GWW_W_STATUS_4		0x210
#define GWW_W_STATUS_5		0x214
#define GWW_W_STATUS_6		0x218
#define GWW_W_STATUS_7		0x21c
#define GWW_W_STATUS_8		0x220
#define GWW_W_STATUS_9		0x224
#define GWW_W_STATUS_10		0x228
#define GWW_W_STATUS_11		0x22c
#define GWW_W_STATUS_12		0x230
#define GWW_W_STATUS_13		0x234
#define GWW_W_STATUS_14		0x238
#define GWW_W_STATUS_15		0x23c
#define GWW_W_STATUS_16		0x240
#define GWW_W_STATUS_17		0x244
#define GWW_W_STATUS_18		0x248
#define GWW_W_STATUS_19		0x24c
#define GWW_W_STATUS_20		0x250
#define GWW_W_STATUS_21		0x254
#define GWW_W_STATUS_22		0x258
#define GWW_W_STATUS_23		0x25c
#define GWW_W_STATUS_0		0x260
#define GWW_W_STATUS_1		0x264
#define GWW_W_STATUS_2		0x268
#define GWW_W_STATUS_3		0x26c
#define GWW_W_STATUS_4		0x270
#define GWW_W_STATUS_5		0x274
#define GWW_W_STATUS_6		0x278
#define GWW_W_STATUS_7		0x27c
#define GWW_W_STATUS_8		0x280
#define GWW_W_STATUS_9		0x284
#define GWW_W_STATUS_10		0x288
#define GWW_W_STATUS_11		0x28c
#define GWW_W_STATUS_12		0x290
#define GWW_W_STATUS_13		0x294
#define GWW_W_STATUS_14		0x298
#define GWW_W_STATUS_15		0x29c
#define GWW_W_STATUS_16		0x2a0
#define GWW_W_STATUS_17		0x2a4
#define GWW_W_STATUS_18		0x2a8
#define GWW_W_STATUS_19		0x2ac
#define GWW_W_STATUS_20		0x2b0
#define GWW_W_STATUS_21		0x2b4
#define GWW_W_STATUS_22		0x2b8
#define GWW_W_STATUS_23		0x2bc
#define GWW_ABIST_CTWW0		0x2D4
#define GWW_ABIST_CTWW1		0x2D8
#define ABIST_EN			BIT(7)
#define ABIST_DATA_FMT			(0x7 << 0)
#define VIDEO_CFG_0		0x380
#define VIDEO_CFG_1		0x384
#define VIDEO_CFG_2		0x388
#define VIDEO_CFG_3		0x38c
#define VIDEO_CFG_4		0x390
#define VIDEO_SOUWCE_SEW		BIT(7)
#define NOWMAW_PATH			(1 << 7)
#define GEN_WGB				(0 << 7)

#define HDMI_SYS_CFG1C		0x000
#define HDMI_ON				BIT(0)
#define HDMI_WST			BIT(1)
#define ANWG_ON				BIT(2)
#define CFG10_DVI			BIT(3)
#define HDMI_TST			BIT(3)
#define SYS_KEYMASK1			(0xff << 8)
#define SYS_KEYMASK2			(0xff << 16)
#define AUD_OUTSYNC_EN			BIT(24)
#define AUD_OUTSYNC_PWE_EN		BIT(25)
#define I2CM_ON				BIT(26)
#define E2PWOM_TYPE_8BIT		BIT(27)
#define MCM_E2PWOM_ON			BIT(28)
#define EXT_E2PWOM_ON			BIT(29)
#define HTPWG_PIN_SEW_OFF		BIT(30)
#define AES_EFUSE_ENABWE		BIT(31)
#define HDMI_SYS_CFG20		0x004
#define DEEP_COWOW_MODE_MASK		(3 << 1)
#define COWOW_8BIT_MODE			(0 << 1)
#define COWOW_10BIT_MODE		(1 << 1)
#define COWOW_12BIT_MODE		(2 << 1)
#define COWOW_16BIT_MODE		(3 << 1)
#define DEEP_COWOW_EN			BIT(0)
#define HDMI_AUDIO_TEST_SEW		BIT(8)
#define HDMI2P0_EN			BIT(11)
#define HDMI_OUT_FIFO_EN		BIT(16)
#define HDMI_OUT_FIFO_CWK_INV		BIT(17)
#define MHW_MODE_ON			BIT(28)
#define MHW_PP_MODE			BIT(29)
#define MHW_SYNC_AUTO_EN		BIT(30)
#define HDMI_PCWK_FWEE_WUN		BIT(31)

#define MTK_SIP_SET_AUTHOWIZED_SECUWE_WEG 0x82000001
#endif
