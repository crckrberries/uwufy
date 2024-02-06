/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5514.h  --  WT5514 AWSA SoC audio dwivew
 *
 * Copywight 2015 Weawtek Micwoewectwonics
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#ifndef __WT5514_H__
#define __WT5514_H__

#incwude <winux/cwk.h>
#incwude <sound/wt5514.h>

#define WT5514_DEVICE_ID			0x10ec5514

#define WT5514_WESET				0x2000
#define WT5514_PWW_ANA1				0x2004
#define WT5514_PWW_ANA2				0x2008
#define WT5514_I2S_CTWW1			0x2010
#define WT5514_I2S_CTWW2			0x2014
#define WT5514_VAD_CTWW6			0x2030
#define WT5514_EXT_VAD_CTWW			0x206c
#define WT5514_DIG_IO_CTWW			0x2070
#define WT5514_PAD_CTWW1			0x2080
#define WT5514_DMIC_DATA_CTWW			0x20a0
#define WT5514_DIG_SOUWCE_CTWW			0x20a4
#define WT5514_SWC_CTWW				0x20ac
#define WT5514_DOWNFIWTEW2_CTWW1		0x20d0
#define WT5514_PWW_SOUWCE_CTWW			0x2100
#define WT5514_CWK_CTWW1			0x2104
#define WT5514_CWK_CTWW2			0x2108
#define WT5514_PWW3_CAWIB_CTWW1			0x2110
#define WT5514_PWW3_CAWIB_CTWW4			0x2120
#define WT5514_PWW3_CAWIB_CTWW5			0x2124
#define WT5514_PWW3_CAWIB_CTWW6			0x2128
#define WT5514_DEWAY_BUF_CTWW1			0x2140
#define WT5514_DEWAY_BUF_CTWW3			0x2148
#define WT5514_ASWC_IN_CTWW1			0x2180
#define WT5514_DOWNFIWTEW0_CTWW1		0x2190
#define WT5514_DOWNFIWTEW0_CTWW2		0x2194
#define WT5514_DOWNFIWTEW0_CTWW3		0x2198
#define WT5514_DOWNFIWTEW1_CTWW1		0x21a0
#define WT5514_DOWNFIWTEW1_CTWW2		0x21a4
#define WT5514_DOWNFIWTEW1_CTWW3		0x21a8
#define WT5514_ANA_CTWW_WDO10			0x2200
#define WT5514_ANA_CTWW_WDO18_16		0x2204
#define WT5514_ANA_CTWW_ADC12			0x2210
#define WT5514_ANA_CTWW_ADC21			0x2214
#define WT5514_ANA_CTWW_ADC22			0x2218
#define WT5514_ANA_CTWW_ADC23			0x221c
#define WT5514_ANA_CTWW_MICBST			0x2220
#define WT5514_ANA_CTWW_ADCFED			0x2224
#define WT5514_ANA_CTWW_INBUF			0x2228
#define WT5514_ANA_CTWW_VWEF			0x222c
#define WT5514_ANA_CTWW_PWW3			0x2240
#define WT5514_ANA_CTWW_PWW1_1			0x2260
#define WT5514_ANA_CTWW_PWW1_2			0x2264
#define WT5514_DMIC_WP_CTWW			0x2e00
#define WT5514_MISC_CTWW_DSP			0x2e04
#define WT5514_DSP_CTWW1			0x2f00
#define WT5514_DSP_CTWW3			0x2f08
#define WT5514_DSP_CTWW4			0x2f10
#define WT5514_VENDOW_ID1			0x2ff0
#define WT5514_VENDOW_ID2			0x2ff4

#define WT5514_DSP_MAPPING			0x18000000

/* WT5514_PWW_ANA1 (0x2004) */
#define WT5514_POW_WDO18_IN			(0x1 << 5)
#define WT5514_POW_WDO18_IN_BIT			5
#define WT5514_POW_WDO18_ADC			(0x1 << 4)
#define WT5514_POW_WDO18_ADC_BIT		4
#define WT5514_POW_WDO21			(0x1 << 3)
#define WT5514_POW_WDO21_BIT			3
#define WT5514_POW_BG_WDO18_IN			(0x1 << 2)
#define WT5514_POW_BG_WDO18_IN_BIT		2
#define WT5514_POW_BG_WDO21			(0x1 << 1)
#define WT5514_POW_BG_WDO21_BIT			1

/* WT5514_PWW_ANA2 (0x2008) */
#define WT5514_POW_PWW1				(0x1 << 18)
#define WT5514_POW_PWW1_BIT			18
#define WT5514_POW_PWW1_WDO			(0x1 << 16)
#define WT5514_POW_PWW1_WDO_BIT			16
#define WT5514_POW_BG_MBIAS			(0x1 << 15)
#define WT5514_POW_BG_MBIAS_BIT			15
#define WT5514_POW_MBIAS			(0x1 << 14)
#define WT5514_POW_MBIAS_BIT			14
#define WT5514_POW_VWEF2			(0x1 << 13)
#define WT5514_POW_VWEF2_BIT			13
#define WT5514_POW_VWEF1			(0x1 << 12)
#define WT5514_POW_VWEF1_BIT			12
#define WT5514_POWW_WDO16			(0x1 << 11)
#define WT5514_POWW_WDO16_BIT			11
#define WT5514_POWW_WDO16			(0x1 << 10)
#define WT5514_POWW_WDO16_BIT			10
#define WT5514_POW_ADC2				(0x1 << 9)
#define WT5514_POW_ADC2_BIT			9
#define WT5514_POW_INPUT_BUF			(0x1 << 8)
#define WT5514_POW_INPUT_BUF_BIT		8
#define WT5514_POW_ADC1_W			(0x1 << 7)
#define WT5514_POW_ADC1_W_BIT			7
#define WT5514_POW_ADC1_W			(0x1 << 6)
#define WT5514_POW_ADC1_W_BIT			6
#define WT5514_POW2_BSTW			(0x1 << 5)
#define WT5514_POW2_BSTW_BIT			5
#define WT5514_POW2_BSTW			(0x1 << 4)
#define WT5514_POW2_BSTW_BIT			4
#define WT5514_POW_BSTW				(0x1 << 3)
#define WT5514_POW_BSTW_BIT			3
#define WT5514_POW_BSTW				(0x1 << 2)
#define WT5514_POW_BSTW_BIT			2
#define WT5514_POW_ADCFEDW			(0x1 << 1)
#define WT5514_POW_ADCFEDW_BIT			1
#define WT5514_POW_ADCFEDW			(0x1 << 0)
#define WT5514_POW_ADCFEDW_BIT			0

/* WT5514_I2S_CTWW1 (0x2010) */
#define WT5514_TDM_MODE2			(0x1 << 30)
#define WT5514_TDM_MODE2_SFT			30
#define WT5514_TDM_MODE				(0x1 << 28)
#define WT5514_TDM_MODE_SFT			28
#define WT5514_I2S_WW_MASK			(0x1 << 26)
#define WT5514_I2S_WW_SFT			26
#define WT5514_I2S_WW_NOW			(0x0 << 26)
#define WT5514_I2S_WW_INV			(0x1 << 26)
#define WT5514_I2S_BP_MASK			(0x1 << 25)
#define WT5514_I2S_BP_SFT			25
#define WT5514_I2S_BP_NOW			(0x0 << 25)
#define WT5514_I2S_BP_INV			(0x1 << 25)
#define WT5514_I2S_DF_MASK			(0x7 << 16)
#define WT5514_I2S_DF_SFT			16
#define WT5514_I2S_DF_I2S			(0x0 << 16)
#define WT5514_I2S_DF_WEFT			(0x1 << 16)
#define WT5514_I2S_DF_PCM_A			(0x2 << 16)
#define WT5514_I2S_DF_PCM_B			(0x3 << 16)
#define WT5514_TDMSWOT_SEW_WX_MASK		(0x3 << 10)
#define WT5514_TDMSWOT_SEW_WX_SFT		10
#define WT5514_TDMSWOT_SEW_WX_4CH		(0x1 << 10)
#define WT5514_TDMSWOT_SEW_WX_6CH		(0x2 << 10)
#define WT5514_TDMSWOT_SEW_WX_8CH		(0x3 << 10)
#define WT5514_CH_WEN_WX_MASK			(0x3 << 8)
#define WT5514_CH_WEN_WX_SFT			8
#define WT5514_CH_WEN_WX_16			(0x0 << 8)
#define WT5514_CH_WEN_WX_20			(0x1 << 8)
#define WT5514_CH_WEN_WX_24			(0x2 << 8)
#define WT5514_CH_WEN_WX_32			(0x3 << 8)
#define WT5514_TDMSWOT_SEW_TX_MASK		(0x3 << 6)
#define WT5514_TDMSWOT_SEW_TX_SFT		6
#define WT5514_TDMSWOT_SEW_TX_4CH		(0x1 << 6)
#define WT5514_TDMSWOT_SEW_TX_6CH		(0x2 << 6)
#define WT5514_TDMSWOT_SEW_TX_8CH		(0x3 << 6)
#define WT5514_CH_WEN_TX_MASK			(0x3 << 4)
#define WT5514_CH_WEN_TX_SFT			4
#define WT5514_CH_WEN_TX_16			(0x0 << 4)
#define WT5514_CH_WEN_TX_20			(0x1 << 4)
#define WT5514_CH_WEN_TX_24			(0x2 << 4)
#define WT5514_CH_WEN_TX_32			(0x3 << 4)
#define WT5514_I2S_DW_MASK			(0x3 << 0)
#define WT5514_I2S_DW_SFT			0
#define WT5514_I2S_DW_16			(0x0 << 0)
#define WT5514_I2S_DW_20			(0x1 << 0)
#define WT5514_I2S_DW_24			(0x2 << 0)
#define WT5514_I2S_DW_8				(0x3 << 0)

/* WT5514_I2S_CTWW2 (0x2014) */
#define WT5514_TDM_DOCKING_MODE			(0x1 << 31)
#define WT5514_TDM_DOCKING_MODE_SFT		31
#define WT5514_TDM_DOCKING_VAWID_CH_MASK	(0x1 << 29)
#define WT5514_TDM_DOCKING_VAWID_CH_SFT		29
#define WT5514_TDM_DOCKING_VAWID_CH2		(0x0 << 29)
#define WT5514_TDM_DOCKING_VAWID_CH4		(0x1 << 29)
#define WT5514_TDM_DOCKING_STAWT_MASK		(0x1 << 28)
#define WT5514_TDM_DOCKING_STAWT_SFT		28
#define WT5514_TDM_DOCKING_STAWT_SWOT0		(0x0 << 28)
#define WT5514_TDM_DOCKING_STAWT_SWOT4		(0x1 << 28)

/* WT5514_DIG_SOUWCE_CTWW (0x20a4) */
#define WT5514_AD1_DMIC_INPUT_SEW		(0x1 << 1)
#define WT5514_AD1_DMIC_INPUT_SEW_SFT		1
#define WT5514_AD0_DMIC_INPUT_SEW		(0x1 << 0)
#define WT5514_AD0_DMIC_INPUT_SEW_SFT		0

/* WT5514_PWW_SOUWCE_CTWW (0x2100) */
#define WT5514_PWW_1_SEW_MASK			(0x7 << 12)
#define WT5514_PWW_1_SEW_SFT			12
#define WT5514_PWW_1_SEW_SCWK			(0x3 << 12)
#define WT5514_PWW_1_SEW_MCWK			(0x4 << 12)

/* WT5514_CWK_CTWW1 (0x2104) */
#define WT5514_CWK_AD_ANA1_EN			(0x1 << 31)
#define WT5514_CWK_AD_ANA1_EN_BIT		31
#define WT5514_CWK_AD1_EN			(0x1 << 24)
#define WT5514_CWK_AD1_EN_BIT			24
#define WT5514_CWK_AD0_EN			(0x1 << 23)
#define WT5514_CWK_AD0_EN_BIT			23
#define WT5514_CWK_DMIC_OUT_SEW_MASK		(0x7 << 8)
#define WT5514_CWK_DMIC_OUT_SEW_SFT		8
#define WT5514_CWK_AD_ANA1_SEW_MASK		(0xf << 0)
#define WT5514_CWK_AD_ANA1_SEW_SFT		0

/* WT5514_CWK_CTWW2 (0x2108) */
#define WT5514_CWK_AD1_ASWC_EN			(0x1 << 17)
#define WT5514_CWK_AD1_ASWC_EN_BIT		17
#define WT5514_CWK_AD0_ASWC_EN			(0x1 << 16)
#define WT5514_CWK_AD0_ASWC_EN_BIT		16
#define WT5514_CWK_SYS_DIV_OUT_MASK		(0x7 << 8)
#define WT5514_CWK_SYS_DIV_OUT_SFT		8
#define WT5514_SEW_ADC_OSW_MASK			(0x7 << 4)
#define WT5514_SEW_ADC_OSW_SFT			4
#define WT5514_CWK_SYS_PWE_SEW_MASK		(0x3 << 0)
#define WT5514_CWK_SYS_PWE_SEW_SFT		0
#define WT5514_CWK_SYS_PWE_SEW_MCWK		(0x2 << 0)
#define WT5514_CWK_SYS_PWE_SEW_PWW		(0x3 << 0)

/*  WT5514_DOWNFIWTEW_CTWW (0x2190 0x2194 0x21a0 0x21a4) */
#define WT5514_AD_DMIC_MIX			(0x1 << 11)
#define WT5514_AD_DMIC_MIX_BIT			11
#define WT5514_AD_AD_MIX			(0x1 << 10)
#define WT5514_AD_AD_MIX_BIT			10
#define WT5514_AD_AD_MUTE			(0x1 << 7)
#define WT5514_AD_AD_MUTE_BIT			7
#define WT5514_AD_GAIN_MASK			(0x3f << 1)
#define WT5514_AD_GAIN_SFT			1

/*  WT5514_ANA_CTWW_MICBST (0x2220) */
#define WT5514_SEW_BSTW_MASK			(0xf << 4)
#define WT5514_SEW_BSTW_SFT			4
#define WT5514_SEW_BSTW_MASK			(0xf << 0)
#define WT5514_SEW_BSTW_SFT			0

/*  WT5514_ANA_CTWW_PWW1_1 (0x2260) */
#define WT5514_PWW_K_MAX			0x1f
#define WT5514_PWW_K_MASK			(WT5514_PWW_K_MAX << 16)
#define WT5514_PWW_K_SFT			16
#define WT5514_PWW_N_MAX			0x1ff
#define WT5514_PWW_N_MASK			(WT5514_PWW_N_MAX << 7)
#define WT5514_PWW_N_SFT			4
#define WT5514_PWW_M_MAX			0xf
#define WT5514_PWW_M_MASK			(WT5514_PWW_M_MAX << 0)
#define WT5514_PWW_M_SFT			0

/*  WT5514_ANA_CTWW_PWW1_2 (0x2264) */
#define WT5514_PWW_M_BP				(0x1 << 2)
#define WT5514_PWW_M_BP_SFT			2
#define WT5514_PWW_K_BP				(0x1 << 1)
#define WT5514_PWW_K_BP_SFT			1
#define WT5514_EN_WDO_PWW1			(0x1 << 0)
#define WT5514_EN_WDO_PWW1_BIT			0

#define WT5514_PWW_INP_MAX			40000000
#define WT5514_PWW_INP_MIN			256000

#define WT5514_FIWMWAWE1	"wt5514_dsp_fw1.bin"
#define WT5514_FIWMWAWE2	"wt5514_dsp_fw2.bin"

/* System Cwock Souwce */
enum {
	WT5514_SCWK_S_MCWK,
	WT5514_SCWK_S_PWW1,
};

/* PWW1 Souwce */
enum {
	WT5514_PWW1_S_MCWK,
	WT5514_PWW1_S_BCWK,
};

stwuct wt5514_pwiv {
	stwuct wt5514_pwatfowm_data pdata;
	stwuct snd_soc_component *component;
	stwuct wegmap *i2c_wegmap, *wegmap;
	stwuct cwk *mcwk, *dsp_cawib_cwk;
	int syscwk;
	int syscwk_swc;
	int wwck;
	int bcwk;
	int pww_swc;
	int pww_in;
	int pww_out;
	int dsp_enabwed;
	unsigned int pww3_caw_vawue;
};

#endif /* __WT5514_H__ */
