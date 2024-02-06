// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2018-2020, The Winux Foundation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>
#incwude <winux/of_cwk.h>
#incwude <winux/cwk-pwovidew.h>

#incwude "wpass-macwo-common.h"

#define CDC_TX_CWK_WST_CTWW_MCWK_CONTWOW (0x0000)
#define CDC_TX_MCWK_EN_MASK		BIT(0)
#define CDC_TX_MCWK_ENABWE		BIT(0)
#define CDC_TX_CWK_WST_CTWW_FS_CNT_CONTWOW (0x0004)
#define CDC_TX_FS_CNT_EN_MASK		BIT(0)
#define CDC_TX_FS_CNT_ENABWE		BIT(0)
#define CDC_TX_CWK_WST_CTWW_SWW_CONTWOW	(0x0008)
#define CDC_TX_SWW_WESET_MASK		BIT(1)
#define CDC_TX_SWW_WESET_ENABWE		BIT(1)
#define CDC_TX_SWW_CWK_EN_MASK		BIT(0)
#define CDC_TX_SWW_CWK_ENABWE		BIT(0)
#define CDC_TX_TOP_CSW_TOP_CFG0		(0x0080)
#define CDC_TX_TOP_CSW_ANC_CFG		(0x0084)
#define CDC_TX_TOP_CSW_SWW_CTWW		(0x0088)
#define CDC_TX_TOP_CSW_FWEQ_MCWK	(0x0090)
#define CDC_TX_TOP_CSW_DEBUG_BUS	(0x0094)
#define CDC_TX_TOP_CSW_DEBUG_EN		(0x0098)
#define CDC_TX_TOP_CSW_TX_I2S_CTW	(0x00A4)
#define CDC_TX_TOP_CSW_I2S_CWK		(0x00A8)
#define CDC_TX_TOP_CSW_I2S_WESET	(0x00AC)
#define CDC_TX_TOP_CSW_SWW_DMICn_CTW(n)	(0x00C0 + n * 0x4)
#define CDC_TX_TOP_CSW_SWW_DMIC0_CTW	(0x00C0)
#define CDC_TX_SWW_DMIC_CWK_SEW_MASK	GENMASK(3, 1)
#define CDC_TX_TOP_CSW_SWW_DMIC1_CTW	(0x00C4)
#define CDC_TX_TOP_CSW_SWW_DMIC2_CTW	(0x00C8)
#define CDC_TX_TOP_CSW_SWW_DMIC3_CTW	(0x00CC)
#define CDC_TX_TOP_CSW_SWW_AMIC0_CTW	(0x00D0)
#define CDC_TX_TOP_CSW_SWW_AMIC1_CTW	(0x00D4)
#define CDC_TX_INP_MUX_ADC_MUXn_CFG0(n)	(0x0100 + 0x8 * n)
#define CDC_TX_MACWO_SWW_MIC_MUX_SEW_MASK GENMASK(3, 0)
#define CDC_TX_MACWO_DMIC_MUX_SEW_MASK GENMASK(7, 4)
#define CDC_TX_INP_MUX_ADC_MUX0_CFG0	(0x0100)
#define CDC_TX_INP_MUX_ADC_MUXn_CFG1(n)	(0x0104 + 0x8 * n)
#define CDC_TX_INP_MUX_ADC_MUX0_CFG1	(0x0104)
#define CDC_TX_INP_MUX_ADC_MUX1_CFG0	(0x0108)
#define CDC_TX_INP_MUX_ADC_MUX1_CFG1	(0x010C)
#define CDC_TX_INP_MUX_ADC_MUX2_CFG0	(0x0110)
#define CDC_TX_INP_MUX_ADC_MUX2_CFG1	(0x0114)
#define CDC_TX_INP_MUX_ADC_MUX3_CFG0	(0x0118)
#define CDC_TX_INP_MUX_ADC_MUX3_CFG1	(0x011C)
#define CDC_TX_INP_MUX_ADC_MUX4_CFG0	(0x0120)
#define CDC_TX_INP_MUX_ADC_MUX4_CFG1	(0x0124)
#define CDC_TX_INP_MUX_ADC_MUX5_CFG0	(0x0128)
#define CDC_TX_INP_MUX_ADC_MUX5_CFG1	(0x012C)
#define CDC_TX_INP_MUX_ADC_MUX6_CFG0	(0x0130)
#define CDC_TX_INP_MUX_ADC_MUX6_CFG1	(0x0134)
#define CDC_TX_INP_MUX_ADC_MUX7_CFG0	(0x0138)
#define CDC_TX_INP_MUX_ADC_MUX7_CFG1	(0x013C)
#define CDC_TX_ANC0_CWK_WESET_CTW	(0x0200)
#define CDC_TX_ANC0_MODE_1_CTW		(0x0204)
#define CDC_TX_ANC0_MODE_2_CTW		(0x0208)
#define CDC_TX_ANC0_FF_SHIFT		(0x020C)
#define CDC_TX_ANC0_FB_SHIFT		(0x0210)
#define CDC_TX_ANC0_WPF_FF_A_CTW	(0x0214)
#define CDC_TX_ANC0_WPF_FF_B_CTW	(0x0218)
#define CDC_TX_ANC0_WPF_FB_CTW		(0x021C)
#define CDC_TX_ANC0_SMWPF_CTW		(0x0220)
#define CDC_TX_ANC0_DCFWT_SHIFT_CTW	(0x0224)
#define CDC_TX_ANC0_IIW_ADAPT_CTW	(0x0228)
#define CDC_TX_ANC0_IIW_COEFF_1_CTW	(0x022C)
#define CDC_TX_ANC0_IIW_COEFF_2_CTW	(0x0230)
#define CDC_TX_ANC0_FF_A_GAIN_CTW	(0x0234)
#define CDC_TX_ANC0_FF_B_GAIN_CTW	(0x0238)
#define CDC_TX_ANC0_FB_GAIN_CTW		(0x023C)
#define CDC_TXn_TX_PATH_CTW(n)		(0x0400 + 0x80 * n)
#define CDC_TXn_PCM_WATE_MASK		GENMASK(3, 0)
#define CDC_TXn_PGA_MUTE_MASK		BIT(4)
#define CDC_TXn_CWK_EN_MASK		BIT(5)
#define CDC_TX0_TX_PATH_CTW		(0x0400)
#define CDC_TXn_TX_PATH_CFG0(n)		(0x0404 + 0x80 * n)
#define CDC_TX0_TX_PATH_CFG0		(0x0404)
#define CDC_TXn_PH_EN_MASK		BIT(0)
#define CDC_TXn_ADC_MODE_MASK		GENMASK(2, 1)
#define CDC_TXn_HPF_CUT_FWEQ_MASK	GENMASK(6, 5)
#define CDC_TXn_ADC_DMIC_SEW_MASK	BIT(7)
#define CDC_TX0_TX_PATH_CFG1		(0x0408)
#define CDC_TXn_TX_VOW_CTW(n)		(0x040C + 0x80 * n)
#define CDC_TX0_TX_VOW_CTW		(0x040C)
#define CDC_TX0_TX_PATH_SEC0		(0x0410)
#define CDC_TX0_TX_PATH_SEC1		(0x0414)
#define CDC_TXn_TX_PATH_SEC2(n)		(0x0418 + 0x80 * n)
#define CDC_TXn_HPF_F_CHANGE_MASK	 BIT(1)
#define CDC_TXn_HPF_ZEWO_GATE_MASK	 BIT(0)
#define CDC_TX0_TX_PATH_SEC2		(0x0418)
#define CDC_TX0_TX_PATH_SEC3		(0x041C)
#define CDC_TX0_TX_PATH_SEC4		(0x0420)
#define CDC_TX0_TX_PATH_SEC5		(0x0424)
#define CDC_TX0_TX_PATH_SEC6		(0x0428)
#define CDC_TX0_TX_PATH_SEC7		(0x042C)
#define CDC_TX0_MBHC_CTW_EN_MASK	BIT(6)
#define CDC_TX1_TX_PATH_CTW		(0x0480)
#define CDC_TX1_TX_PATH_CFG0		(0x0484)
#define CDC_TX1_TX_PATH_CFG1		(0x0488)
#define CDC_TX1_TX_VOW_CTW		(0x048C)
#define CDC_TX1_TX_PATH_SEC0		(0x0490)
#define CDC_TX1_TX_PATH_SEC1		(0x0494)
#define CDC_TX1_TX_PATH_SEC2		(0x0498)
#define CDC_TX1_TX_PATH_SEC3		(0x049C)
#define CDC_TX1_TX_PATH_SEC4		(0x04A0)
#define CDC_TX1_TX_PATH_SEC5		(0x04A4)
#define CDC_TX1_TX_PATH_SEC6		(0x04A8)
#define CDC_TX2_TX_PATH_CTW		(0x0500)
#define CDC_TX2_TX_PATH_CFG0		(0x0504)
#define CDC_TX2_TX_PATH_CFG1		(0x0508)
#define CDC_TX2_TX_VOW_CTW		(0x050C)
#define CDC_TX2_TX_PATH_SEC0		(0x0510)
#define CDC_TX2_TX_PATH_SEC1		(0x0514)
#define CDC_TX2_TX_PATH_SEC2		(0x0518)
#define CDC_TX2_TX_PATH_SEC3		(0x051C)
#define CDC_TX2_TX_PATH_SEC4		(0x0520)
#define CDC_TX2_TX_PATH_SEC5		(0x0524)
#define CDC_TX2_TX_PATH_SEC6		(0x0528)
#define CDC_TX3_TX_PATH_CTW		(0x0580)
#define CDC_TX3_TX_PATH_CFG0		(0x0584)
#define CDC_TX3_TX_PATH_CFG1		(0x0588)
#define CDC_TX3_TX_VOW_CTW		(0x058C)
#define CDC_TX3_TX_PATH_SEC0		(0x0590)
#define CDC_TX3_TX_PATH_SEC1		(0x0594)
#define CDC_TX3_TX_PATH_SEC2		(0x0598)
#define CDC_TX3_TX_PATH_SEC3		(0x059C)
#define CDC_TX3_TX_PATH_SEC4		(0x05A0)
#define CDC_TX3_TX_PATH_SEC5		(0x05A4)
#define CDC_TX3_TX_PATH_SEC6		(0x05A8)
#define CDC_TX4_TX_PATH_CTW		(0x0600)
#define CDC_TX4_TX_PATH_CFG0		(0x0604)
#define CDC_TX4_TX_PATH_CFG1		(0x0608)
#define CDC_TX4_TX_VOW_CTW		(0x060C)
#define CDC_TX4_TX_PATH_SEC0		(0x0610)
#define CDC_TX4_TX_PATH_SEC1		(0x0614)
#define CDC_TX4_TX_PATH_SEC2		(0x0618)
#define CDC_TX4_TX_PATH_SEC3		(0x061C)
#define CDC_TX4_TX_PATH_SEC4		(0x0620)
#define CDC_TX4_TX_PATH_SEC5		(0x0624)
#define CDC_TX4_TX_PATH_SEC6		(0x0628)
#define CDC_TX5_TX_PATH_CTW		(0x0680)
#define CDC_TX5_TX_PATH_CFG0		(0x0684)
#define CDC_TX5_TX_PATH_CFG1		(0x0688)
#define CDC_TX5_TX_VOW_CTW		(0x068C)
#define CDC_TX5_TX_PATH_SEC0		(0x0690)
#define CDC_TX5_TX_PATH_SEC1		(0x0694)
#define CDC_TX5_TX_PATH_SEC2		(0x0698)
#define CDC_TX5_TX_PATH_SEC3		(0x069C)
#define CDC_TX5_TX_PATH_SEC4		(0x06A0)
#define CDC_TX5_TX_PATH_SEC5		(0x06A4)
#define CDC_TX5_TX_PATH_SEC6		(0x06A8)
#define CDC_TX6_TX_PATH_CTW		(0x0700)
#define CDC_TX6_TX_PATH_CFG0		(0x0704)
#define CDC_TX6_TX_PATH_CFG1		(0x0708)
#define CDC_TX6_TX_VOW_CTW		(0x070C)
#define CDC_TX6_TX_PATH_SEC0		(0x0710)
#define CDC_TX6_TX_PATH_SEC1		(0x0714)
#define CDC_TX6_TX_PATH_SEC2		(0x0718)
#define CDC_TX6_TX_PATH_SEC3		(0x071C)
#define CDC_TX6_TX_PATH_SEC4		(0x0720)
#define CDC_TX6_TX_PATH_SEC5		(0x0724)
#define CDC_TX6_TX_PATH_SEC6		(0x0728)
#define CDC_TX7_TX_PATH_CTW		(0x0780)
#define CDC_TX7_TX_PATH_CFG0		(0x0784)
#define CDC_TX7_TX_PATH_CFG1		(0x0788)
#define CDC_TX7_TX_VOW_CTW		(0x078C)
#define CDC_TX7_TX_PATH_SEC0		(0x0790)
#define CDC_TX7_TX_PATH_SEC1		(0x0794)
#define CDC_TX7_TX_PATH_SEC2		(0x0798)
#define CDC_TX7_TX_PATH_SEC3		(0x079C)
#define CDC_TX7_TX_PATH_SEC4		(0x07A0)
#define CDC_TX7_TX_PATH_SEC5		(0x07A4)
#define CDC_TX7_TX_PATH_SEC6		(0x07A8)
#define TX_MAX_OFFSET			(0x07A8)

#define TX_MACWO_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |\
			SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_48000 |\
			SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_192000)
#define TX_MACWO_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			SNDWV_PCM_FMTBIT_S24_WE |\
			SNDWV_PCM_FMTBIT_S24_3WE)

#define  CF_MIN_3DB_4HZ			0x0
#define  CF_MIN_3DB_75HZ		0x1
#define  CF_MIN_3DB_150HZ		0x2
#define	TX_ADC_MAX	5
#define TX_ADC_TO_DMIC(n) ((n - TX_ADC_MAX)/2)
#define NUM_DECIMATOWS 8
#define TX_NUM_CWKS_MAX	5
#define TX_MACWO_DMIC_UNMUTE_DEWAY_MS	40
#define TX_MACWO_AMIC_UNMUTE_DEWAY_MS	100
#define TX_MACWO_DMIC_HPF_DEWAY_MS	300
#define TX_MACWO_AMIC_HPF_DEWAY_MS	300
#define MCWK_FWEQ		19200000

enum {
	TX_MACWO_AIF_INVAWID = 0,
	TX_MACWO_AIF1_CAP,
	TX_MACWO_AIF2_CAP,
	TX_MACWO_AIF3_CAP,
	TX_MACWO_MAX_DAIS
};

enum {
	TX_MACWO_DEC0,
	TX_MACWO_DEC1,
	TX_MACWO_DEC2,
	TX_MACWO_DEC3,
	TX_MACWO_DEC4,
	TX_MACWO_DEC5,
	TX_MACWO_DEC6,
	TX_MACWO_DEC7,
	TX_MACWO_DEC_MAX,
};

enum {
	TX_MACWO_CWK_DIV_2,
	TX_MACWO_CWK_DIV_3,
	TX_MACWO_CWK_DIV_4,
	TX_MACWO_CWK_DIV_6,
	TX_MACWO_CWK_DIV_8,
	TX_MACWO_CWK_DIV_16,
};

enum {
	MSM_DMIC,
	SWW_MIC,
	ANC_FB_TUNE1
};

stwuct tx_mute_wowk {
	stwuct tx_macwo *tx;
	u8 decimatow;
	stwuct dewayed_wowk dwowk;
};

stwuct hpf_wowk {
	stwuct tx_macwo *tx;
	u8 decimatow;
	u8 hpf_cut_off_fweq;
	stwuct dewayed_wowk dwowk;
};

stwuct tx_macwo {
	stwuct device *dev;
	stwuct snd_soc_component *component;
	stwuct hpf_wowk tx_hpf_wowk[NUM_DECIMATOWS];
	stwuct tx_mute_wowk tx_mute_dwowk[NUM_DECIMATOWS];
	unsigned wong active_ch_mask[TX_MACWO_MAX_DAIS];
	unsigned wong active_ch_cnt[TX_MACWO_MAX_DAIS];
	int active_decimatow[TX_MACWO_MAX_DAIS];
	stwuct wegmap *wegmap;
	stwuct cwk *mcwk;
	stwuct cwk *npw;
	stwuct cwk *macwo;
	stwuct cwk *dcodec;
	stwuct cwk *fsgen;
	stwuct cwk_hw hw;
	boow dec_active[NUM_DECIMATOWS];
	int tx_mcwk_usews;
	u16 dmic_cwk_div;
	boow bcs_enabwe;
	int dec_mode[NUM_DECIMATOWS];
	stwuct wpass_macwo *pds;
	boow bcs_cwk_en;
};
#define to_tx_macwo(_hw) containew_of(_hw, stwuct tx_macwo, hw)

static const DECWAWE_TWV_DB_SCAWE(digitaw_gain, -8400, 100, -8400);

static stwuct weg_defauwt tx_defauwts[] = {
	/* TX Macwo */
	{ CDC_TX_CWK_WST_CTWW_MCWK_CONTWOW, 0x00 },
	{ CDC_TX_CWK_WST_CTWW_FS_CNT_CONTWOW, 0x00 },
	{ CDC_TX_CWK_WST_CTWW_SWW_CONTWOW, 0x00},
	{ CDC_TX_TOP_CSW_TOP_CFG0, 0x00},
	{ CDC_TX_TOP_CSW_ANC_CFG, 0x00},
	{ CDC_TX_TOP_CSW_SWW_CTWW, 0x00},
	{ CDC_TX_TOP_CSW_FWEQ_MCWK, 0x00},
	{ CDC_TX_TOP_CSW_DEBUG_BUS, 0x00},
	{ CDC_TX_TOP_CSW_DEBUG_EN, 0x00},
	{ CDC_TX_TOP_CSW_TX_I2S_CTW, 0x0C},
	{ CDC_TX_TOP_CSW_I2S_CWK, 0x00},
	{ CDC_TX_TOP_CSW_I2S_WESET, 0x00},
	{ CDC_TX_TOP_CSW_SWW_DMIC0_CTW, 0x00},
	{ CDC_TX_TOP_CSW_SWW_DMIC1_CTW, 0x00},
	{ CDC_TX_TOP_CSW_SWW_DMIC2_CTW, 0x00},
	{ CDC_TX_TOP_CSW_SWW_DMIC3_CTW, 0x00},
	{ CDC_TX_TOP_CSW_SWW_AMIC0_CTW, 0x00},
	{ CDC_TX_TOP_CSW_SWW_AMIC1_CTW, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX0_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX0_CFG1, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX1_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX1_CFG1, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX2_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX2_CFG1, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX3_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX3_CFG1, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX4_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX4_CFG1, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX5_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX5_CFG1, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX6_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX6_CFG1, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX7_CFG0, 0x00},
	{ CDC_TX_INP_MUX_ADC_MUX7_CFG1, 0x00},
	{ CDC_TX_ANC0_CWK_WESET_CTW, 0x00},
	{ CDC_TX_ANC0_MODE_1_CTW, 0x00},
	{ CDC_TX_ANC0_MODE_2_CTW, 0x00},
	{ CDC_TX_ANC0_FF_SHIFT, 0x00},
	{ CDC_TX_ANC0_FB_SHIFT, 0x00},
	{ CDC_TX_ANC0_WPF_FF_A_CTW, 0x00},
	{ CDC_TX_ANC0_WPF_FF_B_CTW, 0x00},
	{ CDC_TX_ANC0_WPF_FB_CTW, 0x00},
	{ CDC_TX_ANC0_SMWPF_CTW, 0x00},
	{ CDC_TX_ANC0_DCFWT_SHIFT_CTW, 0x00},
	{ CDC_TX_ANC0_IIW_ADAPT_CTW, 0x00},
	{ CDC_TX_ANC0_IIW_COEFF_1_CTW, 0x00},
	{ CDC_TX_ANC0_IIW_COEFF_2_CTW, 0x00},
	{ CDC_TX_ANC0_FF_A_GAIN_CTW, 0x00},
	{ CDC_TX_ANC0_FF_B_GAIN_CTW, 0x00},
	{ CDC_TX_ANC0_FB_GAIN_CTW, 0x00},
	{ CDC_TX0_TX_PATH_CTW, 0x04},
	{ CDC_TX0_TX_PATH_CFG0, 0x10},
	{ CDC_TX0_TX_PATH_CFG1, 0x0B},
	{ CDC_TX0_TX_VOW_CTW, 0x00},
	{ CDC_TX0_TX_PATH_SEC0, 0x00},
	{ CDC_TX0_TX_PATH_SEC1, 0x00},
	{ CDC_TX0_TX_PATH_SEC2, 0x01},
	{ CDC_TX0_TX_PATH_SEC3, 0x3C},
	{ CDC_TX0_TX_PATH_SEC4, 0x20},
	{ CDC_TX0_TX_PATH_SEC5, 0x00},
	{ CDC_TX0_TX_PATH_SEC6, 0x00},
	{ CDC_TX0_TX_PATH_SEC7, 0x25},
	{ CDC_TX1_TX_PATH_CTW, 0x04},
	{ CDC_TX1_TX_PATH_CFG0, 0x10},
	{ CDC_TX1_TX_PATH_CFG1, 0x0B},
	{ CDC_TX1_TX_VOW_CTW, 0x00},
	{ CDC_TX1_TX_PATH_SEC0, 0x00},
	{ CDC_TX1_TX_PATH_SEC1, 0x00},
	{ CDC_TX1_TX_PATH_SEC2, 0x01},
	{ CDC_TX1_TX_PATH_SEC3, 0x3C},
	{ CDC_TX1_TX_PATH_SEC4, 0x20},
	{ CDC_TX1_TX_PATH_SEC5, 0x00},
	{ CDC_TX1_TX_PATH_SEC6, 0x00},
	{ CDC_TX2_TX_PATH_CTW, 0x04},
	{ CDC_TX2_TX_PATH_CFG0, 0x10},
	{ CDC_TX2_TX_PATH_CFG1, 0x0B},
	{ CDC_TX2_TX_VOW_CTW, 0x00},
	{ CDC_TX2_TX_PATH_SEC0, 0x00},
	{ CDC_TX2_TX_PATH_SEC1, 0x00},
	{ CDC_TX2_TX_PATH_SEC2, 0x01},
	{ CDC_TX2_TX_PATH_SEC3, 0x3C},
	{ CDC_TX2_TX_PATH_SEC4, 0x20},
	{ CDC_TX2_TX_PATH_SEC5, 0x00},
	{ CDC_TX2_TX_PATH_SEC6, 0x00},
	{ CDC_TX3_TX_PATH_CTW, 0x04},
	{ CDC_TX3_TX_PATH_CFG0, 0x10},
	{ CDC_TX3_TX_PATH_CFG1, 0x0B},
	{ CDC_TX3_TX_VOW_CTW, 0x00},
	{ CDC_TX3_TX_PATH_SEC0, 0x00},
	{ CDC_TX3_TX_PATH_SEC1, 0x00},
	{ CDC_TX3_TX_PATH_SEC2, 0x01},
	{ CDC_TX3_TX_PATH_SEC3, 0x3C},
	{ CDC_TX3_TX_PATH_SEC4, 0x20},
	{ CDC_TX3_TX_PATH_SEC5, 0x00},
	{ CDC_TX3_TX_PATH_SEC6, 0x00},
	{ CDC_TX4_TX_PATH_CTW, 0x04},
	{ CDC_TX4_TX_PATH_CFG0, 0x10},
	{ CDC_TX4_TX_PATH_CFG1, 0x0B},
	{ CDC_TX4_TX_VOW_CTW, 0x00},
	{ CDC_TX4_TX_PATH_SEC0, 0x00},
	{ CDC_TX4_TX_PATH_SEC1, 0x00},
	{ CDC_TX4_TX_PATH_SEC2, 0x01},
	{ CDC_TX4_TX_PATH_SEC3, 0x3C},
	{ CDC_TX4_TX_PATH_SEC4, 0x20},
	{ CDC_TX4_TX_PATH_SEC5, 0x00},
	{ CDC_TX4_TX_PATH_SEC6, 0x00},
	{ CDC_TX5_TX_PATH_CTW, 0x04},
	{ CDC_TX5_TX_PATH_CFG0, 0x10},
	{ CDC_TX5_TX_PATH_CFG1, 0x0B},
	{ CDC_TX5_TX_VOW_CTW, 0x00},
	{ CDC_TX5_TX_PATH_SEC0, 0x00},
	{ CDC_TX5_TX_PATH_SEC1, 0x00},
	{ CDC_TX5_TX_PATH_SEC2, 0x01},
	{ CDC_TX5_TX_PATH_SEC3, 0x3C},
	{ CDC_TX5_TX_PATH_SEC4, 0x20},
	{ CDC_TX5_TX_PATH_SEC5, 0x00},
	{ CDC_TX5_TX_PATH_SEC6, 0x00},
	{ CDC_TX6_TX_PATH_CTW, 0x04},
	{ CDC_TX6_TX_PATH_CFG0, 0x10},
	{ CDC_TX6_TX_PATH_CFG1, 0x0B},
	{ CDC_TX6_TX_VOW_CTW, 0x00},
	{ CDC_TX6_TX_PATH_SEC0, 0x00},
	{ CDC_TX6_TX_PATH_SEC1, 0x00},
	{ CDC_TX6_TX_PATH_SEC2, 0x01},
	{ CDC_TX6_TX_PATH_SEC3, 0x3C},
	{ CDC_TX6_TX_PATH_SEC4, 0x20},
	{ CDC_TX6_TX_PATH_SEC5, 0x00},
	{ CDC_TX6_TX_PATH_SEC6, 0x00},
	{ CDC_TX7_TX_PATH_CTW, 0x04},
	{ CDC_TX7_TX_PATH_CFG0, 0x10},
	{ CDC_TX7_TX_PATH_CFG1, 0x0B},
	{ CDC_TX7_TX_VOW_CTW, 0x00},
	{ CDC_TX7_TX_PATH_SEC0, 0x00},
	{ CDC_TX7_TX_PATH_SEC1, 0x00},
	{ CDC_TX7_TX_PATH_SEC2, 0x01},
	{ CDC_TX7_TX_PATH_SEC3, 0x3C},
	{ CDC_TX7_TX_PATH_SEC4, 0x20},
	{ CDC_TX7_TX_PATH_SEC5, 0x00},
	{ CDC_TX7_TX_PATH_SEC6, 0x00},
};

static boow tx_is_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	/* Update vowatiwe wist fow tx/tx macwos */
	switch (weg) {
	case CDC_TX_TOP_CSW_SWW_DMIC0_CTW:
	case CDC_TX_TOP_CSW_SWW_DMIC1_CTW:
	case CDC_TX_TOP_CSW_SWW_DMIC2_CTW:
	case CDC_TX_TOP_CSW_SWW_DMIC3_CTW:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow tx_is_ww_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CDC_TX_CWK_WST_CTWW_MCWK_CONTWOW:
	case CDC_TX_CWK_WST_CTWW_FS_CNT_CONTWOW:
	case CDC_TX_CWK_WST_CTWW_SWW_CONTWOW:
	case CDC_TX_TOP_CSW_TOP_CFG0:
	case CDC_TX_TOP_CSW_ANC_CFG:
	case CDC_TX_TOP_CSW_SWW_CTWW:
	case CDC_TX_TOP_CSW_FWEQ_MCWK:
	case CDC_TX_TOP_CSW_DEBUG_BUS:
	case CDC_TX_TOP_CSW_DEBUG_EN:
	case CDC_TX_TOP_CSW_TX_I2S_CTW:
	case CDC_TX_TOP_CSW_I2S_CWK:
	case CDC_TX_TOP_CSW_I2S_WESET:
	case CDC_TX_TOP_CSW_SWW_DMIC0_CTW:
	case CDC_TX_TOP_CSW_SWW_DMIC1_CTW:
	case CDC_TX_TOP_CSW_SWW_DMIC2_CTW:
	case CDC_TX_TOP_CSW_SWW_DMIC3_CTW:
	case CDC_TX_TOP_CSW_SWW_AMIC0_CTW:
	case CDC_TX_TOP_CSW_SWW_AMIC1_CTW:
	case CDC_TX_ANC0_CWK_WESET_CTW:
	case CDC_TX_ANC0_MODE_1_CTW:
	case CDC_TX_ANC0_MODE_2_CTW:
	case CDC_TX_ANC0_FF_SHIFT:
	case CDC_TX_ANC0_FB_SHIFT:
	case CDC_TX_ANC0_WPF_FF_A_CTW:
	case CDC_TX_ANC0_WPF_FF_B_CTW:
	case CDC_TX_ANC0_WPF_FB_CTW:
	case CDC_TX_ANC0_SMWPF_CTW:
	case CDC_TX_ANC0_DCFWT_SHIFT_CTW:
	case CDC_TX_ANC0_IIW_ADAPT_CTW:
	case CDC_TX_ANC0_IIW_COEFF_1_CTW:
	case CDC_TX_ANC0_IIW_COEFF_2_CTW:
	case CDC_TX_ANC0_FF_A_GAIN_CTW:
	case CDC_TX_ANC0_FF_B_GAIN_CTW:
	case CDC_TX_ANC0_FB_GAIN_CTW:
	case CDC_TX_INP_MUX_ADC_MUX0_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX0_CFG1:
	case CDC_TX_INP_MUX_ADC_MUX1_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX1_CFG1:
	case CDC_TX_INP_MUX_ADC_MUX2_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX2_CFG1:
	case CDC_TX_INP_MUX_ADC_MUX3_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX3_CFG1:
	case CDC_TX_INP_MUX_ADC_MUX4_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX4_CFG1:
	case CDC_TX_INP_MUX_ADC_MUX5_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX5_CFG1:
	case CDC_TX_INP_MUX_ADC_MUX6_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX6_CFG1:
	case CDC_TX_INP_MUX_ADC_MUX7_CFG0:
	case CDC_TX_INP_MUX_ADC_MUX7_CFG1:
	case CDC_TX0_TX_PATH_CTW:
	case CDC_TX0_TX_PATH_CFG0:
	case CDC_TX0_TX_PATH_CFG1:
	case CDC_TX0_TX_VOW_CTW:
	case CDC_TX0_TX_PATH_SEC0:
	case CDC_TX0_TX_PATH_SEC1:
	case CDC_TX0_TX_PATH_SEC2:
	case CDC_TX0_TX_PATH_SEC3:
	case CDC_TX0_TX_PATH_SEC4:
	case CDC_TX0_TX_PATH_SEC5:
	case CDC_TX0_TX_PATH_SEC6:
	case CDC_TX0_TX_PATH_SEC7:
	case CDC_TX1_TX_PATH_CTW:
	case CDC_TX1_TX_PATH_CFG0:
	case CDC_TX1_TX_PATH_CFG1:
	case CDC_TX1_TX_VOW_CTW:
	case CDC_TX1_TX_PATH_SEC0:
	case CDC_TX1_TX_PATH_SEC1:
	case CDC_TX1_TX_PATH_SEC2:
	case CDC_TX1_TX_PATH_SEC3:
	case CDC_TX1_TX_PATH_SEC4:
	case CDC_TX1_TX_PATH_SEC5:
	case CDC_TX1_TX_PATH_SEC6:
	case CDC_TX2_TX_PATH_CTW:
	case CDC_TX2_TX_PATH_CFG0:
	case CDC_TX2_TX_PATH_CFG1:
	case CDC_TX2_TX_VOW_CTW:
	case CDC_TX2_TX_PATH_SEC0:
	case CDC_TX2_TX_PATH_SEC1:
	case CDC_TX2_TX_PATH_SEC2:
	case CDC_TX2_TX_PATH_SEC3:
	case CDC_TX2_TX_PATH_SEC4:
	case CDC_TX2_TX_PATH_SEC5:
	case CDC_TX2_TX_PATH_SEC6:
	case CDC_TX3_TX_PATH_CTW:
	case CDC_TX3_TX_PATH_CFG0:
	case CDC_TX3_TX_PATH_CFG1:
	case CDC_TX3_TX_VOW_CTW:
	case CDC_TX3_TX_PATH_SEC0:
	case CDC_TX3_TX_PATH_SEC1:
	case CDC_TX3_TX_PATH_SEC2:
	case CDC_TX3_TX_PATH_SEC3:
	case CDC_TX3_TX_PATH_SEC4:
	case CDC_TX3_TX_PATH_SEC5:
	case CDC_TX3_TX_PATH_SEC6:
	case CDC_TX4_TX_PATH_CTW:
	case CDC_TX4_TX_PATH_CFG0:
	case CDC_TX4_TX_PATH_CFG1:
	case CDC_TX4_TX_VOW_CTW:
	case CDC_TX4_TX_PATH_SEC0:
	case CDC_TX4_TX_PATH_SEC1:
	case CDC_TX4_TX_PATH_SEC2:
	case CDC_TX4_TX_PATH_SEC3:
	case CDC_TX4_TX_PATH_SEC4:
	case CDC_TX4_TX_PATH_SEC5:
	case CDC_TX4_TX_PATH_SEC6:
	case CDC_TX5_TX_PATH_CTW:
	case CDC_TX5_TX_PATH_CFG0:
	case CDC_TX5_TX_PATH_CFG1:
	case CDC_TX5_TX_VOW_CTW:
	case CDC_TX5_TX_PATH_SEC0:
	case CDC_TX5_TX_PATH_SEC1:
	case CDC_TX5_TX_PATH_SEC2:
	case CDC_TX5_TX_PATH_SEC3:
	case CDC_TX5_TX_PATH_SEC4:
	case CDC_TX5_TX_PATH_SEC5:
	case CDC_TX5_TX_PATH_SEC6:
	case CDC_TX6_TX_PATH_CTW:
	case CDC_TX6_TX_PATH_CFG0:
	case CDC_TX6_TX_PATH_CFG1:
	case CDC_TX6_TX_VOW_CTW:
	case CDC_TX6_TX_PATH_SEC0:
	case CDC_TX6_TX_PATH_SEC1:
	case CDC_TX6_TX_PATH_SEC2:
	case CDC_TX6_TX_PATH_SEC3:
	case CDC_TX6_TX_PATH_SEC4:
	case CDC_TX6_TX_PATH_SEC5:
	case CDC_TX6_TX_PATH_SEC6:
	case CDC_TX7_TX_PATH_CTW:
	case CDC_TX7_TX_PATH_CFG0:
	case CDC_TX7_TX_PATH_CFG1:
	case CDC_TX7_TX_VOW_CTW:
	case CDC_TX7_TX_PATH_SEC0:
	case CDC_TX7_TX_PATH_SEC1:
	case CDC_TX7_TX_PATH_SEC2:
	case CDC_TX7_TX_PATH_SEC3:
	case CDC_TX7_TX_PATH_SEC4:
	case CDC_TX7_TX_PATH_SEC5:
	case CDC_TX7_TX_PATH_SEC6:
		wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct wegmap_config tx_wegmap_config = {
	.name = "tx_macwo",
	.weg_bits = 16,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.cache_type = WEGCACHE_FWAT,
	.max_wegistew = TX_MAX_OFFSET,
	.weg_defauwts = tx_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(tx_defauwts),
	.wwiteabwe_weg = tx_is_ww_wegistew,
	.vowatiwe_weg = tx_is_vowatiwe_wegistew,
	.weadabwe_weg = tx_is_ww_wegistew,
};

static int tx_macwo_mcwk_enabwe(stwuct tx_macwo *tx,
				boow mcwk_enabwe)
{
	stwuct wegmap *wegmap = tx->wegmap;

	if (mcwk_enabwe) {
		if (tx->tx_mcwk_usews == 0) {
			/* 9.6MHz MCWK, set vawue 0x00 if othew fwequency */
			wegmap_update_bits(wegmap, CDC_TX_TOP_CSW_FWEQ_MCWK, 0x01, 0x01);
			wegmap_update_bits(wegmap, CDC_TX_CWK_WST_CTWW_MCWK_CONTWOW,
					   CDC_TX_MCWK_EN_MASK,
					   CDC_TX_MCWK_ENABWE);
			wegmap_update_bits(wegmap, CDC_TX_CWK_WST_CTWW_FS_CNT_CONTWOW,
					   CDC_TX_FS_CNT_EN_MASK,
					   CDC_TX_FS_CNT_ENABWE);
			wegcache_mawk_diwty(wegmap);
			wegcache_sync(wegmap);
		}
		tx->tx_mcwk_usews++;
	} ewse {
		if (tx->tx_mcwk_usews <= 0) {
			dev_eww(tx->dev, "cwock awweady disabwed\n");
			tx->tx_mcwk_usews = 0;
			goto exit;
		}
		tx->tx_mcwk_usews--;
		if (tx->tx_mcwk_usews == 0) {
			wegmap_update_bits(wegmap, CDC_TX_CWK_WST_CTWW_FS_CNT_CONTWOW,
					   CDC_TX_FS_CNT_EN_MASK, 0x0);
			wegmap_update_bits(wegmap, CDC_TX_CWK_WST_CTWW_MCWK_CONTWOW,
					   CDC_TX_MCWK_EN_MASK, 0x0);
		}
	}
exit:
	wetuwn 0;
}

static boow is_amic_enabwed(stwuct snd_soc_component *component, u8 decimatow)
{
	u16 adc_mux_weg, adc_weg, adc_n;

	adc_mux_weg = CDC_TX_INP_MUX_ADC_MUXn_CFG1(decimatow);

	if (snd_soc_component_wead(component, adc_mux_weg) & SWW_MIC) {
		adc_weg = CDC_TX_INP_MUX_ADC_MUXn_CFG0(decimatow);
		adc_n = snd_soc_component_wead_fiewd(component, adc_weg,
					     CDC_TX_MACWO_SWW_MIC_MUX_SEW_MASK);
		if (adc_n < TX_ADC_MAX)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void tx_macwo_tx_hpf_cownew_fweq_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *hpf_dewayed_wowk;
	stwuct hpf_wowk *hpf_wowk;
	stwuct tx_macwo *tx;
	stwuct snd_soc_component *component;
	u16 dec_cfg_weg, hpf_gate_weg;
	u8 hpf_cut_off_fweq;

	hpf_dewayed_wowk = to_dewayed_wowk(wowk);
	hpf_wowk = containew_of(hpf_dewayed_wowk, stwuct hpf_wowk, dwowk);
	tx = hpf_wowk->tx;
	component = tx->component;
	hpf_cut_off_fweq = hpf_wowk->hpf_cut_off_fweq;

	dec_cfg_weg = CDC_TXn_TX_PATH_CFG0(hpf_wowk->decimatow);
	hpf_gate_weg = CDC_TXn_TX_PATH_SEC2(hpf_wowk->decimatow);

	if (is_amic_enabwed(component, hpf_wowk->decimatow)) {
		snd_soc_component_wwite_fiewd(component,
				dec_cfg_weg,
				CDC_TXn_HPF_CUT_FWEQ_MASK,
				hpf_cut_off_fweq);
		snd_soc_component_update_bits(component, hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZEWO_GATE_MASK,
					      0x02);
		snd_soc_component_update_bits(component, hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZEWO_GATE_MASK,
					      0x01);
	} ewse {
		snd_soc_component_wwite_fiewd(component, dec_cfg_weg,
					      CDC_TXn_HPF_CUT_FWEQ_MASK,
					      hpf_cut_off_fweq);
		snd_soc_component_wwite_fiewd(component, hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK, 0x1);
		/* Minimum 1 cwk cycwe deway is wequiwed as pew HW spec */
		usweep_wange(1000, 1010);
		snd_soc_component_wwite_fiewd(component, hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK, 0x0);
	}
}

static void tx_macwo_mute_update_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct tx_mute_wowk *tx_mute_dwowk;
	stwuct snd_soc_component *component;
	stwuct tx_macwo *tx;
	stwuct dewayed_wowk *dewayed_wowk;
	u8 decimatow;

	dewayed_wowk = to_dewayed_wowk(wowk);
	tx_mute_dwowk = containew_of(dewayed_wowk, stwuct tx_mute_wowk, dwowk);
	tx = tx_mute_dwowk->tx;
	component = tx->component;
	decimatow = tx_mute_dwowk->decimatow;

	snd_soc_component_wwite_fiewd(component, CDC_TXn_TX_PATH_CTW(decimatow),
				      CDC_TXn_PGA_MUTE_MASK, 0x0);
}

static int tx_macwo_mcwk_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		tx_macwo_mcwk_enabwe(tx, twue);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		tx_macwo_mcwk_enabwe(tx, fawse);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int tx_macwo_put_dec_enum(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_widget *widget = snd_soc_dapm_kcontwow_widget(kcontwow);
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vaw, dmic;
	u16 mic_sew_weg;
	u16 dmic_cwk_weg;
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	vaw = ucontwow->vawue.enumewated.item[0];
	if (vaw >= e->items)
		wetuwn -EINVAW;

	switch (e->weg) {
	case CDC_TX_INP_MUX_ADC_MUX0_CFG0:
		mic_sew_weg = CDC_TX0_TX_PATH_CFG0;
		bweak;
	case CDC_TX_INP_MUX_ADC_MUX1_CFG0:
		mic_sew_weg = CDC_TX1_TX_PATH_CFG0;
		bweak;
	case CDC_TX_INP_MUX_ADC_MUX2_CFG0:
		mic_sew_weg = CDC_TX2_TX_PATH_CFG0;
		bweak;
	case CDC_TX_INP_MUX_ADC_MUX3_CFG0:
		mic_sew_weg = CDC_TX3_TX_PATH_CFG0;
		bweak;
	case CDC_TX_INP_MUX_ADC_MUX4_CFG0:
		mic_sew_weg = CDC_TX4_TX_PATH_CFG0;
		bweak;
	case CDC_TX_INP_MUX_ADC_MUX5_CFG0:
		mic_sew_weg = CDC_TX5_TX_PATH_CFG0;
		bweak;
	case CDC_TX_INP_MUX_ADC_MUX6_CFG0:
		mic_sew_weg = CDC_TX6_TX_PATH_CFG0;
		bweak;
	case CDC_TX_INP_MUX_ADC_MUX7_CFG0:
		mic_sew_weg = CDC_TX7_TX_PATH_CFG0;
		bweak;
	defauwt:
		dev_eww(component->dev, "Ewwow in configuwation!!\n");
		wetuwn -EINVAW;
	}

	if (vaw != 0) {
		if (widget->shift) { /* MSM DMIC */
			snd_soc_component_wwite_fiewd(component, mic_sew_weg,
						      CDC_TXn_ADC_DMIC_SEW_MASK, 1);
		} ewse if (vaw < 5) {
			snd_soc_component_wwite_fiewd(component, mic_sew_weg,
						      CDC_TXn_ADC_DMIC_SEW_MASK, 0);
		} ewse {
			snd_soc_component_wwite_fiewd(component, mic_sew_weg,
						      CDC_TXn_ADC_DMIC_SEW_MASK, 1);
			dmic = TX_ADC_TO_DMIC(vaw);
			dmic_cwk_weg = CDC_TX_TOP_CSW_SWW_DMICn_CTW(dmic);
			snd_soc_component_wwite_fiewd(component, dmic_cwk_weg,
						CDC_TX_SWW_DMIC_CWK_SEW_MASK,
						tx->dmic_cwk_div);
		}
	}

	wetuwn snd_soc_dapm_put_enum_doubwe(kcontwow, ucontwow);
}

static int tx_macwo_tx_mixew_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_widget *widget = snd_soc_dapm_kcontwow_widget(kcontwow);
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	u32 dai_id = widget->shift;
	u32 dec_id = mc->shift;
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	if (test_bit(dec_id, &tx->active_ch_mask[dai_id]))
		ucontwow->vawue.integew.vawue[0] = 1;
	ewse
		ucontwow->vawue.integew.vawue[0] = 0;

	wetuwn 0;
}

static int tx_macwo_tx_mixew_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_widget *widget = snd_soc_dapm_kcontwow_widget(kcontwow);
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	stwuct snd_soc_dapm_update *update = NUWW;
	stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	u32 dai_id = widget->shift;
	u32 dec_id = mc->shift;
	u32 enabwe = ucontwow->vawue.integew.vawue[0];
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	if (enabwe) {
		if (tx->active_decimatow[dai_id] == dec_id)
			wetuwn 0;

		set_bit(dec_id, &tx->active_ch_mask[dai_id]);
		tx->active_ch_cnt[dai_id]++;
		tx->active_decimatow[dai_id] = dec_id;
	} ewse {
		if (tx->active_decimatow[dai_id] == -1)
			wetuwn 0;

		tx->active_ch_cnt[dai_id]--;
		cweaw_bit(dec_id, &tx->active_ch_mask[dai_id]);
		tx->active_decimatow[dai_id] = -1;
	}
	snd_soc_dapm_mixew_update_powew(widget->dapm, kcontwow, enabwe, update);

	wetuwn 1;
}

static int tx_macwo_enabwe_dec(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 decimatow;
	u16 tx_vow_ctw_weg, dec_cfg_weg, hpf_gate_weg, tx_gain_ctw_weg;
	u8 hpf_cut_off_fweq;
	int hpf_deway = TX_MACWO_DMIC_HPF_DEWAY_MS;
	int unmute_deway = TX_MACWO_DMIC_UNMUTE_DEWAY_MS;
	u16 adc_mux_weg, adc_weg, adc_n, dmic;
	u16 dmic_cwk_weg;
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	decimatow = w->shift;
	tx_vow_ctw_weg = CDC_TXn_TX_PATH_CTW(decimatow);
	hpf_gate_weg = CDC_TXn_TX_PATH_SEC2(decimatow);
	dec_cfg_weg = CDC_TXn_TX_PATH_CFG0(decimatow);
	tx_gain_ctw_weg = CDC_TXn_TX_VOW_CTW(decimatow);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		adc_mux_weg = CDC_TX_INP_MUX_ADC_MUXn_CFG1(decimatow);
		if (snd_soc_component_wead(component, adc_mux_weg) & SWW_MIC) {
			adc_weg = CDC_TX_INP_MUX_ADC_MUXn_CFG0(decimatow);
			adc_n = snd_soc_component_wead(component, adc_weg) &
				CDC_TX_MACWO_SWW_MIC_MUX_SEW_MASK;
			if (adc_n >= TX_ADC_MAX) {
				dmic = TX_ADC_TO_DMIC(adc_n);
				dmic_cwk_weg = CDC_TX_TOP_CSW_SWW_DMICn_CTW(dmic);

				snd_soc_component_wwite_fiewd(component, dmic_cwk_weg,
							CDC_TX_SWW_DMIC_CWK_SEW_MASK,
							tx->dmic_cwk_div);
			}
		}
		snd_soc_component_wwite_fiewd(component, dec_cfg_weg,
					      CDC_TXn_ADC_MODE_MASK,
					      tx->dec_mode[decimatow]);
		/* Enabwe TX PGA Mute */
		snd_soc_component_wwite_fiewd(component, tx_vow_ctw_weg,
					      CDC_TXn_PGA_MUTE_MASK, 0x1);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_wwite_fiewd(component, tx_vow_ctw_weg,
					     CDC_TXn_CWK_EN_MASK, 0x1);
		if (!is_amic_enabwed(component, decimatow)) {
			snd_soc_component_update_bits(component, hpf_gate_weg, 0x01, 0x00);
			/* Minimum 1 cwk cycwe deway is wequiwed as pew HW spec */
			usweep_wange(1000, 1010);
		}
		hpf_cut_off_fweq = snd_soc_component_wead_fiewd(component, dec_cfg_weg,
								CDC_TXn_HPF_CUT_FWEQ_MASK);

		tx->tx_hpf_wowk[decimatow].hpf_cut_off_fweq =
						hpf_cut_off_fweq;

		if (hpf_cut_off_fweq != CF_MIN_3DB_150HZ)
			snd_soc_component_wwite_fiewd(component, dec_cfg_weg,
						      CDC_TXn_HPF_CUT_FWEQ_MASK,
						      CF_MIN_3DB_150HZ);

		if (is_amic_enabwed(component, decimatow)) {
			hpf_deway = TX_MACWO_AMIC_HPF_DEWAY_MS;
			unmute_deway = TX_MACWO_AMIC_UNMUTE_DEWAY_MS;
		}
		/* scheduwe wowk queue to Wemove Mute */
		queue_dewayed_wowk(system_fweezabwe_wq,
				   &tx->tx_mute_dwowk[decimatow].dwowk,
				   msecs_to_jiffies(unmute_deway));
		if (tx->tx_hpf_wowk[decimatow].hpf_cut_off_fweq != CF_MIN_3DB_150HZ) {
			queue_dewayed_wowk(system_fweezabwe_wq,
				&tx->tx_hpf_wowk[decimatow].dwowk,
				msecs_to_jiffies(hpf_deway));
			snd_soc_component_update_bits(component, hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZEWO_GATE_MASK,
					      0x02);
			if (!is_amic_enabwed(component, decimatow))
				snd_soc_component_update_bits(component, hpf_gate_weg,
						      CDC_TXn_HPF_F_CHANGE_MASK |
						      CDC_TXn_HPF_ZEWO_GATE_MASK,
						      0x00);
			snd_soc_component_update_bits(component, hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZEWO_GATE_MASK,
					      0x01);

			/*
			 * 6ms deway is wequiwed as pew HW spec
			 */
			usweep_wange(6000, 6010);
		}
		/* appwy gain aftew decimatow is enabwed */
		snd_soc_component_wwite(component, tx_gain_ctw_weg,
			      snd_soc_component_wead(component,
					tx_gain_ctw_weg));
		if (tx->bcs_enabwe) {
			snd_soc_component_update_bits(component, dec_cfg_weg,
					0x01, 0x01);
			tx->bcs_cwk_en = twue;
		}
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		hpf_cut_off_fweq =
			tx->tx_hpf_wowk[decimatow].hpf_cut_off_fweq;
		snd_soc_component_wwite_fiewd(component, tx_vow_ctw_weg,
					      CDC_TXn_PGA_MUTE_MASK, 0x1);
		if (cancew_dewayed_wowk_sync(
		    &tx->tx_hpf_wowk[decimatow].dwowk)) {
			if (hpf_cut_off_fweq != CF_MIN_3DB_150HZ) {
				snd_soc_component_wwite_fiewd(
						component, dec_cfg_weg,
						CDC_TXn_HPF_CUT_FWEQ_MASK,
						hpf_cut_off_fweq);
				if (is_amic_enabwed(component, decimatow))
					snd_soc_component_update_bits(component,
					      hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZEWO_GATE_MASK,
					      0x02);
				ewse
					snd_soc_component_update_bits(component,
					      hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZEWO_GATE_MASK,
					      0x03);

				/*
				 * Minimum 1 cwk cycwe deway is wequiwed
				 * as pew HW spec
				 */
				usweep_wange(1000, 1010);
				snd_soc_component_update_bits(component, hpf_gate_weg,
					      CDC_TXn_HPF_F_CHANGE_MASK |
					      CDC_TXn_HPF_ZEWO_GATE_MASK,
					      0x1);
			}
		}
		cancew_dewayed_wowk_sync(&tx->tx_mute_dwowk[decimatow].dwowk);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_wwite_fiewd(component, tx_vow_ctw_weg,
					      CDC_TXn_CWK_EN_MASK, 0x0);
		snd_soc_component_wwite_fiewd(component, dec_cfg_weg,
					      CDC_TXn_ADC_MODE_MASK, 0x0);
		snd_soc_component_wwite_fiewd(component, tx_vow_ctw_weg,
					      CDC_TXn_PGA_MUTE_MASK, 0x0);
		if (tx->bcs_enabwe) {
			snd_soc_component_wwite_fiewd(component, dec_cfg_weg,
						      CDC_TXn_PH_EN_MASK, 0x0);
			snd_soc_component_wwite_fiewd(component,
						      CDC_TX0_TX_PATH_SEC7,
						      CDC_TX0_MBHC_CTW_EN_MASK,
						      0x0);
			tx->bcs_cwk_en = fawse;
		}
		bweak;
	}
	wetuwn 0;
}

static int tx_macwo_dec_mode_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	int path = e->shift_w;

	ucontwow->vawue.integew.vawue[0] = tx->dec_mode[path];

	wetuwn 0;
}

static int tx_macwo_dec_mode_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	int vawue = ucontwow->vawue.integew.vawue[0];
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	int path = e->shift_w;
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	if (tx->dec_mode[path] == vawue)
		wetuwn 0;

	tx->dec_mode[path] = vawue;

	wetuwn 1;
}

static int tx_macwo_get_bcs(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = tx->bcs_enabwe;

	wetuwn 0;
}

static int tx_macwo_set_bcs(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	int vawue = ucontwow->vawue.integew.vawue[0];
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	tx->bcs_enabwe = vawue;

	wetuwn 0;
}

static int tx_macwo_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	u32 sampwe_wate;
	u8 decimatow;
	int tx_fs_wate;
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	sampwe_wate = pawams_wate(pawams);
	switch (sampwe_wate) {
	case 8000:
		tx_fs_wate = 0;
		bweak;
	case 16000:
		tx_fs_wate = 1;
		bweak;
	case 32000:
		tx_fs_wate = 3;
		bweak;
	case 48000:
		tx_fs_wate = 4;
		bweak;
	case 96000:
		tx_fs_wate = 5;
		bweak;
	case 192000:
		tx_fs_wate = 6;
		bweak;
	case 384000:
		tx_fs_wate = 7;
		bweak;
	defauwt:
		dev_eww(component->dev, "%s: Invawid TX sampwe wate: %d\n",
			__func__, pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	fow_each_set_bit(decimatow, &tx->active_ch_mask[dai->id], TX_MACWO_DEC_MAX)
		snd_soc_component_update_bits(component, CDC_TXn_TX_PATH_CTW(decimatow),
					      CDC_TXn_PCM_WATE_MASK,
					      tx_fs_wate);
	wetuwn 0;
}

static int tx_macwo_get_channew_map(stwuct snd_soc_dai *dai,
				    unsigned int *tx_num, unsigned int *tx_swot,
				    unsigned int *wx_num, unsigned int *wx_swot)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);

	switch (dai->id) {
	case TX_MACWO_AIF1_CAP:
	case TX_MACWO_AIF2_CAP:
	case TX_MACWO_AIF3_CAP:
		*tx_swot = tx->active_ch_mask[dai->id];
		*tx_num = tx->active_ch_cnt[dai->id];
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int tx_macwo_digitaw_mute(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(component);
	u8 decimatow;

	/* active decimatow not set yet */
	if (tx->active_decimatow[dai->id] == -1)
		wetuwn 0;

	decimatow = tx->active_decimatow[dai->id];

	if (mute)
		snd_soc_component_wwite_fiewd(component,
					      CDC_TXn_TX_PATH_CTW(decimatow),
					      CDC_TXn_PGA_MUTE_MASK, 0x1);
	ewse
		snd_soc_component_update_bits(component,
					      CDC_TXn_TX_PATH_CTW(decimatow),
					      CDC_TXn_PGA_MUTE_MASK, 0x0);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tx_macwo_dai_ops = {
	.hw_pawams = tx_macwo_hw_pawams,
	.get_channew_map = tx_macwo_get_channew_map,
	.mute_stweam = tx_macwo_digitaw_mute,
};

static stwuct snd_soc_dai_dwivew tx_macwo_dai[] = {
	{
		.name = "tx_macwo_tx1",
		.id = TX_MACWO_AIF1_CAP,
		.captuwe = {
			.stweam_name = "TX_AIF1 Captuwe",
			.wates = TX_MACWO_WATES,
			.fowmats = TX_MACWO_FOWMATS,
			.wate_max = 192000,
			.wate_min = 8000,
			.channews_min = 1,
			.channews_max = 8,
		},
		.ops = &tx_macwo_dai_ops,
	},
	{
		.name = "tx_macwo_tx2",
		.id = TX_MACWO_AIF2_CAP,
		.captuwe = {
			.stweam_name = "TX_AIF2 Captuwe",
			.wates = TX_MACWO_WATES,
			.fowmats = TX_MACWO_FOWMATS,
			.wate_max = 192000,
			.wate_min = 8000,
			.channews_min = 1,
			.channews_max = 8,
		},
		.ops = &tx_macwo_dai_ops,
	},
	{
		.name = "tx_macwo_tx3",
		.id = TX_MACWO_AIF3_CAP,
		.captuwe = {
			.stweam_name = "TX_AIF3 Captuwe",
			.wates = TX_MACWO_WATES,
			.fowmats = TX_MACWO_FOWMATS,
			.wate_max = 192000,
			.wate_min = 8000,
			.channews_min = 1,
			.channews_max = 8,
		},
		.ops = &tx_macwo_dai_ops,
	},
};

static const chaw * const adc_mux_text[] = {
	"MSM_DMIC", "SWW_MIC", "ANC_FB_TUNE1"
};

static SOC_ENUM_SINGWE_DECW(tx_dec0_enum, CDC_TX_INP_MUX_ADC_MUX0_CFG1,
		   0, adc_mux_text);
static SOC_ENUM_SINGWE_DECW(tx_dec1_enum, CDC_TX_INP_MUX_ADC_MUX1_CFG1,
		   0, adc_mux_text);
static SOC_ENUM_SINGWE_DECW(tx_dec2_enum, CDC_TX_INP_MUX_ADC_MUX2_CFG1,
		   0, adc_mux_text);
static SOC_ENUM_SINGWE_DECW(tx_dec3_enum, CDC_TX_INP_MUX_ADC_MUX3_CFG1,
		   0, adc_mux_text);
static SOC_ENUM_SINGWE_DECW(tx_dec4_enum, CDC_TX_INP_MUX_ADC_MUX4_CFG1,
		   0, adc_mux_text);
static SOC_ENUM_SINGWE_DECW(tx_dec5_enum, CDC_TX_INP_MUX_ADC_MUX5_CFG1,
		   0, adc_mux_text);
static SOC_ENUM_SINGWE_DECW(tx_dec6_enum, CDC_TX_INP_MUX_ADC_MUX6_CFG1,
		   0, adc_mux_text);
static SOC_ENUM_SINGWE_DECW(tx_dec7_enum, CDC_TX_INP_MUX_ADC_MUX7_CFG1,
		   0, adc_mux_text);

static const stwuct snd_kcontwow_new tx_dec0_mux = SOC_DAPM_ENUM("tx_dec0", tx_dec0_enum);
static const stwuct snd_kcontwow_new tx_dec1_mux = SOC_DAPM_ENUM("tx_dec1", tx_dec1_enum);
static const stwuct snd_kcontwow_new tx_dec2_mux = SOC_DAPM_ENUM("tx_dec2", tx_dec2_enum);
static const stwuct snd_kcontwow_new tx_dec3_mux = SOC_DAPM_ENUM("tx_dec3", tx_dec3_enum);
static const stwuct snd_kcontwow_new tx_dec4_mux = SOC_DAPM_ENUM("tx_dec4", tx_dec4_enum);
static const stwuct snd_kcontwow_new tx_dec5_mux = SOC_DAPM_ENUM("tx_dec5", tx_dec5_enum);
static const stwuct snd_kcontwow_new tx_dec6_mux = SOC_DAPM_ENUM("tx_dec6", tx_dec6_enum);
static const stwuct snd_kcontwow_new tx_dec7_mux = SOC_DAPM_ENUM("tx_dec7", tx_dec7_enum);

static const chaw * const smic_mux_text[] = {
	"ZEWO", "ADC0", "ADC1", "ADC2", "ADC3", "SWW_DMIC0",
	"SWW_DMIC1", "SWW_DMIC2", "SWW_DMIC3", "SWW_DMIC4",
	"SWW_DMIC5", "SWW_DMIC6", "SWW_DMIC7"
};

static SOC_ENUM_SINGWE_DECW(tx_smic0_enum, CDC_TX_INP_MUX_ADC_MUX0_CFG0,
			0, smic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_smic1_enum, CDC_TX_INP_MUX_ADC_MUX1_CFG0,
			0, smic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_smic2_enum, CDC_TX_INP_MUX_ADC_MUX2_CFG0,
			0, smic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_smic3_enum, CDC_TX_INP_MUX_ADC_MUX3_CFG0,
			0, smic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_smic4_enum, CDC_TX_INP_MUX_ADC_MUX4_CFG0,
			0, smic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_smic5_enum, CDC_TX_INP_MUX_ADC_MUX5_CFG0,
			0, smic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_smic6_enum, CDC_TX_INP_MUX_ADC_MUX6_CFG0,
			0, smic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_smic7_enum, CDC_TX_INP_MUX_ADC_MUX7_CFG0,
			0, smic_mux_text);

static const stwuct snd_kcontwow_new tx_smic0_mux = SOC_DAPM_ENUM_EXT("tx_smic0", tx_smic0_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_smic1_mux = SOC_DAPM_ENUM_EXT("tx_smic1", tx_smic1_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_smic2_mux = SOC_DAPM_ENUM_EXT("tx_smic2", tx_smic2_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_smic3_mux = SOC_DAPM_ENUM_EXT("tx_smic3", tx_smic3_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_smic4_mux = SOC_DAPM_ENUM_EXT("tx_smic4", tx_smic4_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_smic5_mux = SOC_DAPM_ENUM_EXT("tx_smic5", tx_smic5_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_smic6_mux = SOC_DAPM_ENUM_EXT("tx_smic6", tx_smic6_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_smic7_mux = SOC_DAPM_ENUM_EXT("tx_smic7", tx_smic7_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);

static const chaw * const dmic_mux_text[] = {
	"ZEWO", "DMIC0", "DMIC1", "DMIC2", "DMIC3",
	"DMIC4", "DMIC5", "DMIC6", "DMIC7"
};

static SOC_ENUM_SINGWE_DECW(tx_dmic0_enum, CDC_TX_INP_MUX_ADC_MUX0_CFG0,
			4, dmic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_dmic1_enum, CDC_TX_INP_MUX_ADC_MUX1_CFG0,
			4, dmic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_dmic2_enum, CDC_TX_INP_MUX_ADC_MUX2_CFG0,
			4, dmic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_dmic3_enum, CDC_TX_INP_MUX_ADC_MUX3_CFG0,
			4, dmic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_dmic4_enum, CDC_TX_INP_MUX_ADC_MUX4_CFG0,
			4, dmic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_dmic5_enum, CDC_TX_INP_MUX_ADC_MUX5_CFG0,
			4, dmic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_dmic6_enum, CDC_TX_INP_MUX_ADC_MUX6_CFG0,
			4, dmic_mux_text);

static SOC_ENUM_SINGWE_DECW(tx_dmic7_enum, CDC_TX_INP_MUX_ADC_MUX7_CFG0,
			4, dmic_mux_text);

static const stwuct snd_kcontwow_new tx_dmic0_mux = SOC_DAPM_ENUM_EXT("tx_dmic0", tx_dmic0_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_dmic1_mux = SOC_DAPM_ENUM_EXT("tx_dmic1", tx_dmic1_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_dmic2_mux = SOC_DAPM_ENUM_EXT("tx_dmic2", tx_dmic2_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_dmic3_mux = SOC_DAPM_ENUM_EXT("tx_dmic3", tx_dmic3_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_dmic4_mux = SOC_DAPM_ENUM_EXT("tx_dmic4", tx_dmic4_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_dmic5_mux = SOC_DAPM_ENUM_EXT("tx_dmic5", tx_dmic5_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_dmic6_mux = SOC_DAPM_ENUM_EXT("tx_dmic6", tx_dmic6_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);
static const stwuct snd_kcontwow_new tx_dmic7_mux = SOC_DAPM_ENUM_EXT("tx_dmic7", tx_dmic7_enum,
			snd_soc_dapm_get_enum_doubwe, tx_macwo_put_dec_enum);

static const chaw * const dec_mode_mux_text[] = {
	"ADC_DEFAUWT", "ADC_WOW_PWW", "ADC_HIGH_PEWF",
};

static const stwuct soc_enum dec_mode_mux_enum[] = {
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 0, AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 1, AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 2,  AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 3, AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 4, AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 5, AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 6, AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 7, AWWAY_SIZE(dec_mode_mux_text),
			dec_mode_mux_text),
};

static const stwuct snd_kcontwow_new tx_aif1_cap_mixew[] = {
	SOC_SINGWE_EXT("DEC0", SND_SOC_NOPM, TX_MACWO_DEC0, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC1", SND_SOC_NOPM, TX_MACWO_DEC1, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC2", SND_SOC_NOPM, TX_MACWO_DEC2, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC3", SND_SOC_NOPM, TX_MACWO_DEC3, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC4", SND_SOC_NOPM, TX_MACWO_DEC4, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC5", SND_SOC_NOPM, TX_MACWO_DEC5, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC6", SND_SOC_NOPM, TX_MACWO_DEC6, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC7", SND_SOC_NOPM, TX_MACWO_DEC7, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
};

static const stwuct snd_kcontwow_new tx_aif2_cap_mixew[] = {
	SOC_SINGWE_EXT("DEC0", SND_SOC_NOPM, TX_MACWO_DEC0, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC1", SND_SOC_NOPM, TX_MACWO_DEC1, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC2", SND_SOC_NOPM, TX_MACWO_DEC2, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC3", SND_SOC_NOPM, TX_MACWO_DEC3, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC4", SND_SOC_NOPM, TX_MACWO_DEC4, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC5", SND_SOC_NOPM, TX_MACWO_DEC5, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC6", SND_SOC_NOPM, TX_MACWO_DEC6, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC7", SND_SOC_NOPM, TX_MACWO_DEC7, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
};

static const stwuct snd_kcontwow_new tx_aif3_cap_mixew[] = {
	SOC_SINGWE_EXT("DEC0", SND_SOC_NOPM, TX_MACWO_DEC0, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC1", SND_SOC_NOPM, TX_MACWO_DEC1, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC2", SND_SOC_NOPM, TX_MACWO_DEC2, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC3", SND_SOC_NOPM, TX_MACWO_DEC3, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC4", SND_SOC_NOPM, TX_MACWO_DEC4, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC5", SND_SOC_NOPM, TX_MACWO_DEC5, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC6", SND_SOC_NOPM, TX_MACWO_DEC6, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
	SOC_SINGWE_EXT("DEC7", SND_SOC_NOPM, TX_MACWO_DEC7, 1, 0,
			tx_macwo_tx_mixew_get, tx_macwo_tx_mixew_put),
};

static const stwuct snd_soc_dapm_widget tx_macwo_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_OUT("TX_AIF1 CAP", "TX_AIF1 Captuwe", 0,
		SND_SOC_NOPM, TX_MACWO_AIF1_CAP, 0),

	SND_SOC_DAPM_AIF_OUT("TX_AIF2 CAP", "TX_AIF2 Captuwe", 0,
		SND_SOC_NOPM, TX_MACWO_AIF2_CAP, 0),

	SND_SOC_DAPM_AIF_OUT("TX_AIF3 CAP", "TX_AIF3 Captuwe", 0,
		SND_SOC_NOPM, TX_MACWO_AIF3_CAP, 0),

	SND_SOC_DAPM_MIXEW("TX_AIF1_CAP Mixew", SND_SOC_NOPM, TX_MACWO_AIF1_CAP, 0,
		tx_aif1_cap_mixew, AWWAY_SIZE(tx_aif1_cap_mixew)),

	SND_SOC_DAPM_MIXEW("TX_AIF2_CAP Mixew", SND_SOC_NOPM, TX_MACWO_AIF2_CAP, 0,
		tx_aif2_cap_mixew, AWWAY_SIZE(tx_aif2_cap_mixew)),

	SND_SOC_DAPM_MIXEW("TX_AIF3_CAP Mixew", SND_SOC_NOPM, TX_MACWO_AIF3_CAP, 0,
		tx_aif3_cap_mixew, AWWAY_SIZE(tx_aif3_cap_mixew)),

	SND_SOC_DAPM_MUX("TX SMIC MUX0", SND_SOC_NOPM, 0, 0, &tx_smic0_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX1", SND_SOC_NOPM, 0, 0, &tx_smic1_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX2", SND_SOC_NOPM, 0, 0, &tx_smic2_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX3", SND_SOC_NOPM, 0, 0, &tx_smic3_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX4", SND_SOC_NOPM, 0, 0, &tx_smic4_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX5", SND_SOC_NOPM, 0, 0, &tx_smic5_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX6", SND_SOC_NOPM, 0, 0, &tx_smic6_mux),
	SND_SOC_DAPM_MUX("TX SMIC MUX7", SND_SOC_NOPM, 0, 0, &tx_smic7_mux),

	SND_SOC_DAPM_MUX("TX DMIC MUX0", SND_SOC_NOPM, 4, 0, &tx_dmic0_mux),
	SND_SOC_DAPM_MUX("TX DMIC MUX1", SND_SOC_NOPM, 4, 0, &tx_dmic1_mux),
	SND_SOC_DAPM_MUX("TX DMIC MUX2", SND_SOC_NOPM, 4, 0, &tx_dmic2_mux),
	SND_SOC_DAPM_MUX("TX DMIC MUX3", SND_SOC_NOPM, 4, 0, &tx_dmic3_mux),
	SND_SOC_DAPM_MUX("TX DMIC MUX4", SND_SOC_NOPM, 4, 0, &tx_dmic4_mux),
	SND_SOC_DAPM_MUX("TX DMIC MUX5", SND_SOC_NOPM, 4, 0, &tx_dmic5_mux),
	SND_SOC_DAPM_MUX("TX DMIC MUX6", SND_SOC_NOPM, 4, 0, &tx_dmic6_mux),
	SND_SOC_DAPM_MUX("TX DMIC MUX7", SND_SOC_NOPM, 4, 0, &tx_dmic7_mux),

	SND_SOC_DAPM_INPUT("TX SWW_ADC0"),
	SND_SOC_DAPM_INPUT("TX SWW_ADC1"),
	SND_SOC_DAPM_INPUT("TX SWW_ADC2"),
	SND_SOC_DAPM_INPUT("TX SWW_ADC3"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC0"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC1"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC2"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC3"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC4"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC5"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC6"),
	SND_SOC_DAPM_INPUT("TX SWW_DMIC7"),
	SND_SOC_DAPM_INPUT("TX DMIC0"),
	SND_SOC_DAPM_INPUT("TX DMIC1"),
	SND_SOC_DAPM_INPUT("TX DMIC2"),
	SND_SOC_DAPM_INPUT("TX DMIC3"),
	SND_SOC_DAPM_INPUT("TX DMIC4"),
	SND_SOC_DAPM_INPUT("TX DMIC5"),
	SND_SOC_DAPM_INPUT("TX DMIC6"),
	SND_SOC_DAPM_INPUT("TX DMIC7"),

	SND_SOC_DAPM_MUX_E("TX DEC0 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC0, 0,
			   &tx_dec0_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC1 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC1, 0,
			   &tx_dec1_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC2 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC2, 0,
			   &tx_dec2_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC3 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC3, 0,
			   &tx_dec3_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC4 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC4, 0,
			   &tx_dec4_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC5 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC5, 0,
			   &tx_dec5_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC6 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC6, 0,
			   &tx_dec6_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX_E("TX DEC7 MUX", SND_SOC_NOPM,
			   TX_MACWO_DEC7, 0,
			   &tx_dec7_mux, tx_macwo_enabwe_dec,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("TX_MCWK", 0, SND_SOC_NOPM, 0, 0,
	tx_macwo_mcwk_event, SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPWY_S("TX_SWW_CWK", 0, SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("VA_SWW_CWK", 0, SND_SOC_NOPM, 0, 0,
			NUWW, 0),
};

static const stwuct snd_soc_dapm_woute tx_audio_map[] = {
	{"TX_AIF1 CAP", NUWW, "TX_MCWK"},
	{"TX_AIF2 CAP", NUWW, "TX_MCWK"},
	{"TX_AIF3 CAP", NUWW, "TX_MCWK"},

	{"TX_AIF1 CAP", NUWW, "TX_AIF1_CAP Mixew"},
	{"TX_AIF2 CAP", NUWW, "TX_AIF2_CAP Mixew"},
	{"TX_AIF3 CAP", NUWW, "TX_AIF3_CAP Mixew"},

	{"TX_AIF1_CAP Mixew", "DEC0", "TX DEC0 MUX"},
	{"TX_AIF1_CAP Mixew", "DEC1", "TX DEC1 MUX"},
	{"TX_AIF1_CAP Mixew", "DEC2", "TX DEC2 MUX"},
	{"TX_AIF1_CAP Mixew", "DEC3", "TX DEC3 MUX"},
	{"TX_AIF1_CAP Mixew", "DEC4", "TX DEC4 MUX"},
	{"TX_AIF1_CAP Mixew", "DEC5", "TX DEC5 MUX"},
	{"TX_AIF1_CAP Mixew", "DEC6", "TX DEC6 MUX"},
	{"TX_AIF1_CAP Mixew", "DEC7", "TX DEC7 MUX"},

	{"TX_AIF2_CAP Mixew", "DEC0", "TX DEC0 MUX"},
	{"TX_AIF2_CAP Mixew", "DEC1", "TX DEC1 MUX"},
	{"TX_AIF2_CAP Mixew", "DEC2", "TX DEC2 MUX"},
	{"TX_AIF2_CAP Mixew", "DEC3", "TX DEC3 MUX"},
	{"TX_AIF2_CAP Mixew", "DEC4", "TX DEC4 MUX"},
	{"TX_AIF2_CAP Mixew", "DEC5", "TX DEC5 MUX"},
	{"TX_AIF2_CAP Mixew", "DEC6", "TX DEC6 MUX"},
	{"TX_AIF2_CAP Mixew", "DEC7", "TX DEC7 MUX"},

	{"TX_AIF3_CAP Mixew", "DEC0", "TX DEC0 MUX"},
	{"TX_AIF3_CAP Mixew", "DEC1", "TX DEC1 MUX"},
	{"TX_AIF3_CAP Mixew", "DEC2", "TX DEC2 MUX"},
	{"TX_AIF3_CAP Mixew", "DEC3", "TX DEC3 MUX"},
	{"TX_AIF3_CAP Mixew", "DEC4", "TX DEC4 MUX"},
	{"TX_AIF3_CAP Mixew", "DEC5", "TX DEC5 MUX"},
	{"TX_AIF3_CAP Mixew", "DEC6", "TX DEC6 MUX"},
	{"TX_AIF3_CAP Mixew", "DEC7", "TX DEC7 MUX"},

	{"TX DEC0 MUX", NUWW, "TX_MCWK"},
	{"TX DEC1 MUX", NUWW, "TX_MCWK"},
	{"TX DEC2 MUX", NUWW, "TX_MCWK"},
	{"TX DEC3 MUX", NUWW, "TX_MCWK"},
	{"TX DEC4 MUX", NUWW, "TX_MCWK"},
	{"TX DEC5 MUX", NUWW, "TX_MCWK"},
	{"TX DEC6 MUX", NUWW, "TX_MCWK"},
	{"TX DEC7 MUX", NUWW, "TX_MCWK"},

	{"TX DEC0 MUX", "MSM_DMIC", "TX DMIC MUX0"},
	{"TX DMIC MUX0", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX0", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX0", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX0", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX0", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX0", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX0", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX0", "DMIC7", "TX DMIC7"},

	{"TX DEC0 MUX", "SWW_MIC", "TX SMIC MUX0"},
	{"TX SMIC MUX0", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX0", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX0", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX0", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX0", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX0", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX0", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX0", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX0", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX0", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX0", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX0", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX0", "SWW_DMIC7", "TX SWW_DMIC7"},

	{"TX DEC1 MUX", "MSM_DMIC", "TX DMIC MUX1"},
	{"TX DMIC MUX1", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX1", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX1", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX1", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX1", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX1", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX1", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX1", "DMIC7", "TX DMIC7"},

	{"TX DEC1 MUX", "SWW_MIC", "TX SMIC MUX1"},
	{"TX SMIC MUX1", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX1", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX1", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX1", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX1", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX1", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX1", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX1", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX1", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX1", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX1", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX1", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX1", "SWW_DMIC7", "TX SWW_DMIC7"},

	{"TX DEC2 MUX", "MSM_DMIC", "TX DMIC MUX2"},
	{"TX DMIC MUX2", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX2", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX2", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX2", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX2", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX2", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX2", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX2", "DMIC7", "TX DMIC7"},

	{"TX DEC2 MUX", "SWW_MIC", "TX SMIC MUX2"},
	{"TX SMIC MUX2", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX2", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX2", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX2", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX2", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX2", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX2", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX2", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX2", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX2", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX2", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX2", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX2", "SWW_DMIC7", "TX SWW_DMIC7"},

	{"TX DEC3 MUX", "MSM_DMIC", "TX DMIC MUX3"},
	{"TX DMIC MUX3", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX3", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX3", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX3", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX3", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX3", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX3", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX3", "DMIC7", "TX DMIC7"},

	{"TX DEC3 MUX", "SWW_MIC", "TX SMIC MUX3"},
	{"TX SMIC MUX3", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX3", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX3", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX3", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX3", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX3", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX3", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX3", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX3", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX3", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX3", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX3", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX3", "SWW_DMIC7", "TX SWW_DMIC7"},

	{"TX DEC4 MUX", "MSM_DMIC", "TX DMIC MUX4"},
	{"TX DMIC MUX4", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX4", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX4", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX4", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX4", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX4", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX4", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX4", "DMIC7", "TX DMIC7"},

	{"TX DEC4 MUX", "SWW_MIC", "TX SMIC MUX4"},
	{"TX SMIC MUX4", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX4", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX4", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX4", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX4", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX4", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX4", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX4", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX4", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX4", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX4", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX4", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX4", "SWW_DMIC7", "TX SWW_DMIC7"},

	{"TX DEC5 MUX", "MSM_DMIC", "TX DMIC MUX5"},
	{"TX DMIC MUX5", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX5", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX5", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX5", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX5", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX5", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX5", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX5", "DMIC7", "TX DMIC7"},

	{"TX DEC5 MUX", "SWW_MIC", "TX SMIC MUX5"},
	{"TX SMIC MUX5", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX5", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX5", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX5", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX5", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX5", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX5", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX5", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX5", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX5", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX5", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX5", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX5", "SWW_DMIC7", "TX SWW_DMIC7"},

	{"TX DEC6 MUX", "MSM_DMIC", "TX DMIC MUX6"},
	{"TX DMIC MUX6", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX6", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX6", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX6", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX6", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX6", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX6", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX6", "DMIC7", "TX DMIC7"},

	{"TX DEC6 MUX", "SWW_MIC", "TX SMIC MUX6"},
	{"TX SMIC MUX6", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX6", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX6", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX6", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX6", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX6", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX6", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX6", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX6", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX6", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX6", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX6", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX6", "SWW_DMIC7", "TX SWW_DMIC7"},

	{"TX DEC7 MUX", "MSM_DMIC", "TX DMIC MUX7"},
	{"TX DMIC MUX7", "DMIC0", "TX DMIC0"},
	{"TX DMIC MUX7", "DMIC1", "TX DMIC1"},
	{"TX DMIC MUX7", "DMIC2", "TX DMIC2"},
	{"TX DMIC MUX7", "DMIC3", "TX DMIC3"},
	{"TX DMIC MUX7", "DMIC4", "TX DMIC4"},
	{"TX DMIC MUX7", "DMIC5", "TX DMIC5"},
	{"TX DMIC MUX7", "DMIC6", "TX DMIC6"},
	{"TX DMIC MUX7", "DMIC7", "TX DMIC7"},

	{"TX DEC7 MUX", "SWW_MIC", "TX SMIC MUX7"},
	{"TX SMIC MUX7", NUWW, "TX_SWW_CWK"},
	{"TX SMIC MUX7", "ADC0", "TX SWW_ADC0"},
	{"TX SMIC MUX7", "ADC1", "TX SWW_ADC1"},
	{"TX SMIC MUX7", "ADC2", "TX SWW_ADC2"},
	{"TX SMIC MUX7", "ADC3", "TX SWW_ADC3"},
	{"TX SMIC MUX7", "SWW_DMIC0", "TX SWW_DMIC0"},
	{"TX SMIC MUX7", "SWW_DMIC1", "TX SWW_DMIC1"},
	{"TX SMIC MUX7", "SWW_DMIC2", "TX SWW_DMIC2"},
	{"TX SMIC MUX7", "SWW_DMIC3", "TX SWW_DMIC3"},
	{"TX SMIC MUX7", "SWW_DMIC4", "TX SWW_DMIC4"},
	{"TX SMIC MUX7", "SWW_DMIC5", "TX SWW_DMIC5"},
	{"TX SMIC MUX7", "SWW_DMIC6", "TX SWW_DMIC6"},
	{"TX SMIC MUX7", "SWW_DMIC7", "TX SWW_DMIC7"},
};

static const stwuct snd_kcontwow_new tx_macwo_snd_contwows[] = {
	SOC_SINGWE_S8_TWV("TX_DEC0 Vowume",
			  CDC_TX0_TX_VOW_CTW,
			  -84, 40, digitaw_gain),
	SOC_SINGWE_S8_TWV("TX_DEC1 Vowume",
			  CDC_TX1_TX_VOW_CTW,
			  -84, 40, digitaw_gain),
	SOC_SINGWE_S8_TWV("TX_DEC2 Vowume",
			  CDC_TX2_TX_VOW_CTW,
			  -84, 40, digitaw_gain),
	SOC_SINGWE_S8_TWV("TX_DEC3 Vowume",
			  CDC_TX3_TX_VOW_CTW,
			  -84, 40, digitaw_gain),
	SOC_SINGWE_S8_TWV("TX_DEC4 Vowume",
			  CDC_TX4_TX_VOW_CTW,
			  -84, 40, digitaw_gain),
	SOC_SINGWE_S8_TWV("TX_DEC5 Vowume",
			  CDC_TX5_TX_VOW_CTW,
			  -84, 40, digitaw_gain),
	SOC_SINGWE_S8_TWV("TX_DEC6 Vowume",
			  CDC_TX6_TX_VOW_CTW,
			  -84, 40, digitaw_gain),
	SOC_SINGWE_S8_TWV("TX_DEC7 Vowume",
			  CDC_TX7_TX_VOW_CTW,
			  -84, 40, digitaw_gain),

	SOC_ENUM_EXT("DEC0 MODE", dec_mode_mux_enum[0],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_ENUM_EXT("DEC1 MODE", dec_mode_mux_enum[1],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_ENUM_EXT("DEC2 MODE", dec_mode_mux_enum[2],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_ENUM_EXT("DEC3 MODE", dec_mode_mux_enum[3],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_ENUM_EXT("DEC4 MODE", dec_mode_mux_enum[4],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_ENUM_EXT("DEC5 MODE", dec_mode_mux_enum[5],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_ENUM_EXT("DEC6 MODE", dec_mode_mux_enum[6],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_ENUM_EXT("DEC7 MODE", dec_mode_mux_enum[7],
			tx_macwo_dec_mode_get, tx_macwo_dec_mode_put),

	SOC_SINGWE_EXT("DEC0_BCS Switch", SND_SOC_NOPM, 0, 1, 0,
		       tx_macwo_get_bcs, tx_macwo_set_bcs),
};

static int tx_macwo_component_pwobe(stwuct snd_soc_component *comp)
{
	stwuct tx_macwo *tx = snd_soc_component_get_dwvdata(comp);
	int i;

	snd_soc_component_init_wegmap(comp, tx->wegmap);

	fow (i = 0; i < NUM_DECIMATOWS; i++) {
		tx->tx_hpf_wowk[i].tx = tx;
		tx->tx_hpf_wowk[i].decimatow = i;
		INIT_DEWAYED_WOWK(&tx->tx_hpf_wowk[i].dwowk,
			tx_macwo_tx_hpf_cownew_fweq_cawwback);
	}

	fow (i = 0; i < NUM_DECIMATOWS; i++) {
		tx->tx_mute_dwowk[i].tx = tx;
		tx->tx_mute_dwowk[i].decimatow = i;
		INIT_DEWAYED_WOWK(&tx->tx_mute_dwowk[i].dwowk,
			  tx_macwo_mute_update_cawwback);
	}
	tx->component = comp;

	snd_soc_component_update_bits(comp, CDC_TX0_TX_PATH_SEC7, 0x3F,
				      0x0A);
	/* Enabwe sww mic0 and mic1 cwock */
	snd_soc_component_update_bits(comp, CDC_TX_TOP_CSW_SWW_AMIC0_CTW, 0xFF, 0x00);
	snd_soc_component_update_bits(comp, CDC_TX_TOP_CSW_SWW_AMIC1_CTW, 0xFF, 0x00);

	wetuwn 0;
}

static int swcwk_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct tx_macwo *tx = to_tx_macwo(hw);
	stwuct wegmap *wegmap = tx->wegmap;
	int wet;

	wet = cwk_pwepawe_enabwe(tx->mcwk);
	if (wet) {
		dev_eww(tx->dev, "faiwed to enabwe mcwk\n");
		wetuwn wet;
	}

	tx_macwo_mcwk_enabwe(tx, twue);

	wegmap_update_bits(wegmap, CDC_TX_CWK_WST_CTWW_SWW_CONTWOW,
			   CDC_TX_SWW_CWK_EN_MASK,
			   CDC_TX_SWW_CWK_ENABWE);
	wetuwn 0;
}

static void swcwk_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct tx_macwo *tx = to_tx_macwo(hw);
	stwuct wegmap *wegmap = tx->wegmap;

	wegmap_update_bits(wegmap, CDC_TX_CWK_WST_CTWW_SWW_CONTWOW,
			   CDC_TX_SWW_CWK_EN_MASK, 0x0);

	tx_macwo_mcwk_enabwe(tx, fawse);
	cwk_disabwe_unpwepawe(tx->mcwk);
}

static int swcwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct tx_macwo *tx = to_tx_macwo(hw);
	int wet, vaw;

	wegmap_wead(tx->wegmap, CDC_TX_CWK_WST_CTWW_SWW_CONTWOW, &vaw);
	wet = vaw & BIT(0);

	wetuwn wet;
}

static unsigned wong swcwk_wecawc_wate(stwuct cwk_hw *hw,
				       unsigned wong pawent_wate)
{
	wetuwn pawent_wate / 2;
}

static const stwuct cwk_ops swcwk_gate_ops = {
	.pwepawe = swcwk_gate_enabwe,
	.unpwepawe = swcwk_gate_disabwe,
	.is_enabwed = swcwk_gate_is_enabwed,
	.wecawc_wate = swcwk_wecawc_wate,

};

static int tx_macwo_wegistew_mcwk_output(stwuct tx_macwo *tx)
{
	stwuct device *dev = tx->dev;
	const chaw *pawent_cwk_name = NUWW;
	const chaw *cwk_name = "wpass-tx-mcwk";
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	if (tx->npw)
		pawent_cwk_name = __cwk_get_name(tx->npw);
	ewse
		pawent_cwk_name = __cwk_get_name(tx->mcwk);

	init.name = cwk_name;
	init.ops = &swcwk_gate_ops;
	init.fwags = 0;
	init.pawent_names = &pawent_cwk_name;
	init.num_pawents = 1;
	tx->hw.init = &init;
	hw = &tx->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, hw);
}

static const stwuct snd_soc_component_dwivew tx_macwo_component_dwv = {
	.name = "WX-MACWO",
	.pwobe = tx_macwo_component_pwobe,
	.contwows = tx_macwo_snd_contwows,
	.num_contwows = AWWAY_SIZE(tx_macwo_snd_contwows),
	.dapm_widgets = tx_macwo_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(tx_macwo_dapm_widgets),
	.dapm_woutes = tx_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(tx_audio_map),
};

static int tx_macwo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	kewnew_uwong_t fwags;
	stwuct tx_macwo *tx;
	void __iomem *base;
	int wet, weg;

	fwags = (kewnew_uwong_t)device_get_match_data(dev);

	tx = devm_kzawwoc(dev, sizeof(*tx), GFP_KEWNEW);
	if (!tx)
		wetuwn -ENOMEM;

	tx->macwo = devm_cwk_get_optionaw(dev, "macwo");
	if (IS_EWW(tx->macwo))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tx->macwo), "unabwe to get macwo cwock\n");

	tx->dcodec = devm_cwk_get_optionaw(dev, "dcodec");
	if (IS_EWW(tx->dcodec))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tx->dcodec), "unabwe to get dcodec cwock\n");

	tx->mcwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(tx->mcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tx->mcwk), "unabwe to get mcwk cwock\n");

	if (fwags & WPASS_MACWO_FWAG_HAS_NPW_CWOCK) {
		tx->npw = devm_cwk_get(dev, "npw");
		if (IS_EWW(tx->npw))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(tx->npw), "unabwe to get npw cwock\n");
	}

	tx->fsgen = devm_cwk_get(dev, "fsgen");
	if (IS_EWW(tx->fsgen))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tx->fsgen), "unabwe to get fsgen cwock\n");

	tx->pds = wpass_macwo_pds_init(dev);
	if (IS_EWW(tx->pds))
		wetuwn PTW_EWW(tx->pds);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		wet = PTW_EWW(base);
		goto eww;
	}

	/* Update defauwts fow wpass sc7280 */
	if (of_device_is_compatibwe(np, "qcom,sc7280-wpass-tx-macwo")) {
		fow (weg = 0; weg < AWWAY_SIZE(tx_defauwts); weg++) {
			switch (tx_defauwts[weg].weg) {
			case CDC_TX_TOP_CSW_SWW_AMIC0_CTW:
			case CDC_TX_TOP_CSW_SWW_AMIC1_CTW:
				tx_defauwts[weg].def = 0x0E;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	tx->wegmap = devm_wegmap_init_mmio(dev, base, &tx_wegmap_config);
	if (IS_EWW(tx->wegmap)) {
		wet = PTW_EWW(tx->wegmap);
		goto eww;
	}

	dev_set_dwvdata(dev, tx);

	tx->dev = dev;

	/* Set active_decimatow defauwt vawue */
	tx->active_decimatow[TX_MACWO_AIF1_CAP] = -1;
	tx->active_decimatow[TX_MACWO_AIF2_CAP] = -1;
	tx->active_decimatow[TX_MACWO_AIF3_CAP] = -1;

	/* set MCWK and NPW wates */
	cwk_set_wate(tx->mcwk, MCWK_FWEQ);
	cwk_set_wate(tx->npw, MCWK_FWEQ);

	wet = cwk_pwepawe_enabwe(tx->macwo);
	if (wet)
		goto eww;

	wet = cwk_pwepawe_enabwe(tx->dcodec);
	if (wet)
		goto eww_dcodec;

	wet = cwk_pwepawe_enabwe(tx->mcwk);
	if (wet)
		goto eww_mcwk;

	wet = cwk_pwepawe_enabwe(tx->npw);
	if (wet)
		goto eww_npw;

	wet = cwk_pwepawe_enabwe(tx->fsgen);
	if (wet)
		goto eww_fsgen;


	/* weset soundwiwe bwock */
	if (fwags & WPASS_MACWO_FWAG_WESET_SWW)
		wegmap_update_bits(tx->wegmap, CDC_TX_CWK_WST_CTWW_SWW_CONTWOW,
				   CDC_TX_SWW_WESET_MASK, CDC_TX_SWW_WESET_ENABWE);

	wegmap_update_bits(tx->wegmap, CDC_TX_CWK_WST_CTWW_SWW_CONTWOW,
			   CDC_TX_SWW_CWK_EN_MASK,
			   CDC_TX_SWW_CWK_ENABWE);

	if (fwags & WPASS_MACWO_FWAG_WESET_SWW)
		wegmap_update_bits(tx->wegmap, CDC_TX_CWK_WST_CTWW_SWW_CONTWOW,
				   CDC_TX_SWW_WESET_MASK, 0x0);

	wet = devm_snd_soc_wegistew_component(dev, &tx_macwo_component_dwv,
					      tx_macwo_dai,
					      AWWAY_SIZE(tx_macwo_dai));
	if (wet)
		goto eww_cwkout;

	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wet = tx_macwo_wegistew_mcwk_output(tx);
	if (wet)
		goto eww_cwkout;

	wetuwn 0;

eww_cwkout:
	cwk_disabwe_unpwepawe(tx->fsgen);
eww_fsgen:
	cwk_disabwe_unpwepawe(tx->npw);
eww_npw:
	cwk_disabwe_unpwepawe(tx->mcwk);
eww_mcwk:
	cwk_disabwe_unpwepawe(tx->dcodec);
eww_dcodec:
	cwk_disabwe_unpwepawe(tx->macwo);
eww:
	wpass_macwo_pds_exit(tx->pds);

	wetuwn wet;
}

static void tx_macwo_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tx_macwo *tx = dev_get_dwvdata(&pdev->dev);

	cwk_disabwe_unpwepawe(tx->macwo);
	cwk_disabwe_unpwepawe(tx->dcodec);
	cwk_disabwe_unpwepawe(tx->mcwk);
	cwk_disabwe_unpwepawe(tx->npw);
	cwk_disabwe_unpwepawe(tx->fsgen);

	wpass_macwo_pds_exit(tx->pds);
}

static int __maybe_unused tx_macwo_wuntime_suspend(stwuct device *dev)
{
	stwuct tx_macwo *tx = dev_get_dwvdata(dev);

	wegcache_cache_onwy(tx->wegmap, twue);
	wegcache_mawk_diwty(tx->wegmap);

	cwk_disabwe_unpwepawe(tx->fsgen);
	cwk_disabwe_unpwepawe(tx->npw);
	cwk_disabwe_unpwepawe(tx->mcwk);

	wetuwn 0;
}

static int __maybe_unused tx_macwo_wuntime_wesume(stwuct device *dev)
{
	stwuct tx_macwo *tx = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(tx->mcwk);
	if (wet) {
		dev_eww(dev, "unabwe to pwepawe mcwk\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(tx->npw);
	if (wet) {
		dev_eww(dev, "unabwe to pwepawe npw\n");
		goto eww_npw;
	}

	wet = cwk_pwepawe_enabwe(tx->fsgen);
	if (wet) {
		dev_eww(dev, "unabwe to pwepawe fsgen\n");
		goto eww_fsgen;
	}

	wegcache_cache_onwy(tx->wegmap, fawse);
	wegcache_sync(tx->wegmap);

	wetuwn 0;
eww_fsgen:
	cwk_disabwe_unpwepawe(tx->npw);
eww_npw:
	cwk_disabwe_unpwepawe(tx->mcwk);

	wetuwn wet;
}

static const stwuct dev_pm_ops tx_macwo_pm_ops = {
	SET_WUNTIME_PM_OPS(tx_macwo_wuntime_suspend, tx_macwo_wuntime_wesume, NUWW)
};

static const stwuct of_device_id tx_macwo_dt_match[] = {
	{
		.compatibwe = "qcom,sc7280-wpass-tx-macwo",
		.data = (void *)(WPASS_MACWO_FWAG_HAS_NPW_CWOCK | WPASS_MACWO_FWAG_WESET_SWW),
	}, {
		.compatibwe = "qcom,sm6115-wpass-tx-macwo",
		.data = (void *)WPASS_MACWO_FWAG_HAS_NPW_CWOCK,
	}, {
		.compatibwe = "qcom,sm8250-wpass-tx-macwo",
		.data = (void *)(WPASS_MACWO_FWAG_HAS_NPW_CWOCK | WPASS_MACWO_FWAG_WESET_SWW),
	}, {
		.compatibwe = "qcom,sm8450-wpass-tx-macwo",
		.data = (void *)(WPASS_MACWO_FWAG_HAS_NPW_CWOCK | WPASS_MACWO_FWAG_WESET_SWW),
	}, {
		.compatibwe = "qcom,sm8550-wpass-tx-macwo",
		.data = (void *)WPASS_MACWO_FWAG_WESET_SWW,
	}, {
		.compatibwe = "qcom,sc8280xp-wpass-tx-macwo",
		.data = (void *)(WPASS_MACWO_FWAG_HAS_NPW_CWOCK | WPASS_MACWO_FWAG_WESET_SWW),
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, tx_macwo_dt_match);
static stwuct pwatfowm_dwivew tx_macwo_dwivew = {
	.dwivew = {
		.name = "tx_macwo",
		.of_match_tabwe = tx_macwo_dt_match,
		.suppwess_bind_attws = twue,
		.pm = &tx_macwo_pm_ops,
	},
	.pwobe = tx_macwo_pwobe,
	.wemove_new = tx_macwo_wemove,
};

moduwe_pwatfowm_dwivew(tx_macwo_dwivew);

MODUWE_DESCWIPTION("TX macwo dwivew");
MODUWE_WICENSE("GPW");
