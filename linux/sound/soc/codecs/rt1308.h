/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wt1308.h  --  WT1308 AWSA SoC ampwifiew component dwivew
 *
 * Copywight 2019 Weawtek Semiconductow Cowp.
 * Authow: Dewek Fang <dewek.fang@weawtek.com>
 *
 */

#ifndef _WT1308_H_
#define _WT1308_H_

#define WT1308_DEVICE_ID_NUM			0x10ec1300

#define WT1308_WESET				0x00
#define WT1308_WESET_N				0x01
#define WT1308_CWK_GATING			0x02
#define WT1308_PWW_1				0x03
#define WT1308_PWW_2				0x04
#define WT1308_PWW_INT				0x05
#define WT1308_CWK_1				0x06
#define WT1308_DATA_PATH			0x07
#define WT1308_CWK_2				0x08
#define WT1308_SIW_DET				0x09
#define WT1308_CWK_DET				0x0a
#define WT1308_DC_DET				0x0b
#define WT1308_DC_DET_THWES			0x0c
#define WT1308_DAC_SET				0x10
#define WT1308_SWC_SET				0x11
#define WT1308_DAC_BUF				0x12
#define WT1308_ADC_SET				0x13
#define WT1308_ADC_SET_INT			0x14
#define WT1308_I2S_SET_1			0x15
#define WT1308_I2S_SET_2			0x16
#define WT1308_I2C_I2S_SDW_SET			0x17
#define WT1308_SDW_WEG_WW			0x18
#define WT1308_SDW_WEG_WDATA			0x19
#define WT1308_IV_SENSE				0x1a
#define WT1308_I2S_TX_DAC_SET			0x1b
#define WT1308_AD_FIWTEW_SET			0x1c
#define WT1308_DC_CAW_1				0x20
#define WT1308_DC_CAW_2				0x21
#define WT1308_DC_CAW_W_OFFSET			0x22
#define WT1308_DC_CAW_W_OFFSET			0x23
#define WT1308_PVDD_OFFSET_CTW			0x24
#define WT1308_PVDD_OFFSET_W			0x25
#define WT1308_PVDD_OFFSET_W			0x26
#define WT1308_PVDD_OFFSET_PBTW			0x27
#define WT1308_PVDD_OFFSET_PVDD			0x28
#define WT1308_CAW_OFFSET_DAC_PBTW		0x29
#define WT1308_CAW_OFFSET_DAC_W			0x2a
#define WT1308_CAW_OFFSET_DAC_W			0x2b
#define WT1308_CAW_OFFSET_PWM_W			0x2c
#define WT1308_CAW_OFFSET_PWM_W			0x2d
#define WT1308_CAW_PWM_VOS_ADC_W		0x2e
#define WT1308_CAW_PWM_VOS_ADC_W		0x2f
#define WT1308_CWASS_D_SET_1			0x30
#define WT1308_CWASS_D_SET_2			0x31
#define WT1308_POWEW				0x32
#define WT1308_WDO				0x33
#define WT1308_VWEF				0x34
#define WT1308_MBIAS				0x35
#define WT1308_POWEW_STATUS			0x36
#define WT1308_POWEW_INT			0x37
#define WT1308_SINE_TONE_GEN_1			0x50
#define WT1308_SINE_TONE_GEN_2			0x51
#define WT1308_BQ_SET				0x54
#define WT1308_BQ_PAWA_UPDATE			0x55
#define WT1308_BQ_PWE_VOW_W			0x56
#define WT1308_BQ_PWE_VOW_W			0x57
#define WT1308_BQ_POST_VOW_W			0x58
#define WT1308_BQ_POST_VOW_W			0x59
#define WT1308_BQ1_W_H0				0x5b
#define WT1308_BQ1_W_B1				0x5c
#define WT1308_BQ1_W_B2				0x5d
#define WT1308_BQ1_W_A1				0x5e
#define WT1308_BQ1_W_A2				0x5f
#define WT1308_BQ1_W_H0				0x60
#define WT1308_BQ1_W_B1				0x61
#define WT1308_BQ1_W_B2				0x62
#define WT1308_BQ1_W_A1				0x63
#define WT1308_BQ1_W_A2				0x64
#define WT1308_BQ2_W_H0				0x65
#define WT1308_BQ2_W_B1				0x66
#define WT1308_BQ2_W_B2				0x67
#define WT1308_BQ2_W_A1				0x68
#define WT1308_BQ2_W_A2				0x69
#define WT1308_BQ2_W_H0				0x6a
#define WT1308_BQ2_W_B1				0x6b
#define WT1308_BQ2_W_B2				0x6c
#define WT1308_BQ2_W_A1				0x6d
#define WT1308_BQ2_W_A2				0x6e
#define WT1308_VEN_DEV_ID			0x70
#define WT1308_VEWSION_ID			0x71
#define WT1308_SPK_BOUND			0x72
#define WT1308_BQ1_EQ_W_1			0x73
#define WT1308_BQ1_EQ_W_2			0x74
#define WT1308_BQ1_EQ_W_3			0x75
#define WT1308_BQ1_EQ_W_1			0x76
#define WT1308_BQ1_EQ_W_2			0x77
#define WT1308_BQ1_EQ_W_3			0x78
#define WT1308_BQ2_EQ_W_1			0x79
#define WT1308_BQ2_EQ_W_2			0x7a
#define WT1308_BQ2_EQ_W_3			0x7b
#define WT1308_BQ2_EQ_W_1			0x7c
#define WT1308_BQ2_EQ_W_2			0x7d
#define WT1308_BQ2_EQ_W_3			0x7e
#define WT1308_EFUSE_1				0x7f
#define WT1308_EFUSE_2				0x80
#define WT1308_EFUSE_PWOG_PVDD_W		0x81
#define WT1308_EFUSE_PWOG_PVDD_W		0x82
#define WT1308_EFUSE_PWOG_W0_W			0x83
#define WT1308_EFUSE_PWOG_W0_W			0x84
#define WT1308_EFUSE_PWOG_DEV			0x85
#define WT1308_EFUSE_WEAD_PVDD_W		0x86
#define WT1308_EFUSE_WEAD_PVDD_W		0x87
#define WT1308_EFUSE_WEAD_PVDD_PTBW		0x88
#define WT1308_EFUSE_WEAD_DEV			0x89
#define WT1308_EFUSE_WEAD_W0			0x8a
#define WT1308_EFUSE_WEAD_ADC_W			0x8b
#define WT1308_EFUSE_WEAD_ADC_W			0x8c
#define WT1308_EFUSE_WEAD_ADC_PBTW		0x8d
#define WT1308_EFUSE_WESEWVE			0x8e
#define WT1308_PADS_1				0x90
#define WT1308_PADS_2				0x91
#define WT1308_TEST_MODE			0xa0
#define WT1308_TEST_1				0xa1
#define WT1308_TEST_2				0xa2
#define WT1308_TEST_3				0xa3
#define WT1308_TEST_4				0xa4
#define WT1308_EFUSE_DATA_0_MSB			0xb0
#define WT1308_EFUSE_DATA_0_WSB			0xb1
#define WT1308_EFUSE_DATA_1_MSB			0xb2
#define WT1308_EFUSE_DATA_1_WSB			0xb3
#define WT1308_EFUSE_DATA_2_MSB			0xb4
#define WT1308_EFUSE_DATA_2_WSB			0xb5
#define WT1308_EFUSE_DATA_3_MSB			0xb6
#define WT1308_EFUSE_DATA_3_WSB			0xb7
#define WT1308_EFUSE_DATA_TEST_MSB		0xb8
#define WT1308_EFUSE_DATA_TEST_WSB		0xb9
#define WT1308_EFUSE_STATUS_1			0xba
#define WT1308_EFUSE_STATUS_2			0xbb
#define WT1308_TCON_1				0xc0
#define WT1308_TCON_2				0xc1
#define WT1308_DUMMY_WEG			0xf0
#define WT1308_MAX_WEG				0xff

/* PWW1 M/N/K Code-1 (0x03) */
#define WT1308_PWW1_K_SFT			24
#define WT1308_PWW1_K_MASK			(0x1f << 24)
#define WT1308_PWW1_M_BYPASS_MASK		(0x1 << 23)
#define WT1308_PWW1_M_BYPASS_SFT		23
#define WT1308_PWW1_M_BYPASS			(0x1 << 23)
#define WT1308_PWW1_M_MASK			(0x3f << 16)
#define WT1308_PWW1_M_SFT			16
#define WT1308_PWW1_N_MASK			(0x7f << 8)
#define WT1308_PWW1_N_SFT			8

/* CWOCK-1 (0x06) */
#define WT1308_DIV_FS_SYS_MASK			(0xf << 28)
#define WT1308_DIV_FS_SYS_SFT			28
#define WT1308_SEW_FS_SYS_MASK			(0x7 << 24)
#define WT1308_SEW_FS_SYS_SFT			24
#define WT1308_SEW_FS_SYS_SWC_MCWK		(0x0 << 24)
#define WT1308_SEW_FS_SYS_SWC_BCWK		(0x1 << 24)
#define WT1308_SEW_FS_SYS_SWC_PWW		(0x2 << 24)
#define WT1308_SEW_FS_SYS_SWC_WCCWK		(0x4 << 24)

/* CWOCK-2 (0x08) */
#define WT1308_DIV_PWE_PWW_MASK			(0xf << 28)
#define WT1308_DIV_PWE_PWW_SFT			28
#define WT1308_SEW_PWW_SWC_MASK			(0x7 << 24)
#define WT1308_SEW_PWW_SWC_SFT			24
#define WT1308_SEW_PWW_SWC_MCWK			(0x0 << 24)
#define WT1308_SEW_PWW_SWC_BCWK			(0x1 << 24)
#define WT1308_SEW_PWW_SWC_WCCWK		(0x4 << 24)

/* Cwock Detect (0x0a) */
#define WT1308_MCWK_DET_EN_MASK			(0x1 << 25)
#define WT1308_MCWK_DET_EN_SFT			25
#define WT1308_MCWK_DET_EN			(0x1 << 25)
#define WT1308_BCWK_DET_EN_MASK			(0x1 << 24)
#define WT1308_BCWK_DET_EN_SFT			24
#define WT1308_BCWK_DET_EN			(0x1 << 24)

/* DAC Setting (0x10) */
#define WT1308_DVOW_MUTE_W_EN_SFT		7
#define WT1308_DVOW_MUTE_W_EN_SFT		6

/* I2S Setting-1 (0x15) */
#define WT1308_I2S_DF_SEW_MASK			(0x3 << 12)
#define WT1308_I2S_DF_SEW_SFT			12
#define WT1308_I2S_DF_SEW_I2S			(0x0 << 12)
#define WT1308_I2S_DF_SEW_WEFT			(0x1 << 12)
#define WT1308_I2S_DF_SEW_PCM_A			(0x2 << 12)
#define WT1308_I2S_DF_SEW_PCM_B			(0x3 << 12)
#define WT1308_I2S_DW_WX_SEW_MASK		(0x7 << 4)
#define WT1308_I2S_DW_WX_SEW_SFT		4
#define WT1308_I2S_DW_WX_SEW_16B		(0x0 << 4)
#define WT1308_I2S_DW_WX_SEW_20B		(0x1 << 4)
#define WT1308_I2S_DW_WX_SEW_24B		(0x2 << 4)
#define WT1308_I2S_DW_WX_SEW_32B		(0x3 << 4)
#define WT1308_I2S_DW_WX_SEW_8B			(0x4 << 4)
#define WT1308_I2S_DW_TX_SEW_MASK		(0x7 << 0)
#define WT1308_I2S_DW_TX_SEW_SFT		0
#define WT1308_I2S_DW_TX_SEW_16B		(0x0 << 0)
#define WT1308_I2S_DW_TX_SEW_20B		(0x1 << 0)
#define WT1308_I2S_DW_TX_SEW_24B		(0x2 << 0)
#define WT1308_I2S_DW_TX_SEW_32B		(0x3 << 0)
#define WT1308_I2S_DW_TX_SEW_8B			(0x4 << 0)

/* I2S Setting-2 (0x16) */
#define WT1308_I2S_DW_SEW_MASK			(0x7 << 24)
#define WT1308_I2S_DW_SEW_SFT			24
#define WT1308_I2S_DW_SEW_16B			(0x0 << 24)
#define WT1308_I2S_DW_SEW_20B			(0x1 << 24)
#define WT1308_I2S_DW_SEW_24B			(0x2 << 24)
#define WT1308_I2S_DW_SEW_32B			(0x3 << 24)
#define WT1308_I2S_DW_SEW_8B			(0x4 << 24)
#define WT1308_I2S_BCWK_MASK			(0x1 << 14)
#define WT1308_I2S_BCWK_SFT			14
#define WT1308_I2S_BCWK_NOWMAW			(0x0 << 14)
#define WT1308_I2S_BCWK_INV			(0x1 << 14)

/* Powew Contwow-1 (0x32) */
#define WT1308_POW_MBIAS20U			(0x1 << 31)
#define WT1308_POW_MBIAS20U_BIT			31
#define WT1308_POW_AWDO				(0x1 << 30)
#define WT1308_POW_AWDO_BIT			30
#define WT1308_POW_DBG				(0x1 << 29)
#define WT1308_POW_DBG_BIT			29
#define WT1308_POW_DACW				(0x1 << 28)
#define WT1308_POW_DACW_BIT			28
#define WT1308_POW_DAC1				(0x1 << 27)
#define WT1308_POW_DAC1_BIT			27
#define WT1308_POW_CWK25M			(0x1 << 26)
#define WT1308_POW_CWK25M_BIT			26
#define WT1308_POW_ADC_W			(0x1 << 25)
#define WT1308_POW_ADC_W_BIT			25
#define WT1308_POW_ADC_W			(0x1 << 24)
#define WT1308_POW_ADC_W_BIT			24
#define WT1308_POW_DWDO				(0x1 << 21)
#define WT1308_POW_DWDO_BIT			21
#define WT1308_POW_VWEF				(0x1 << 20)
#define WT1308_POW_VWEF_BIT			20
#define WT1308_POW_MIXEW_W			(0x1 << 18)
#define WT1308_POW_MIXEW_W_BIT			18
#define WT1308_POW_MIXEW_W			(0x1 << 17)
#define WT1308_POW_MIXEW_W_BIT			17
#define WT1308_POW_MBIAS4U			(0x1 << 16)
#define WT1308_POW_MBIAS4U_BIT			16
#define WT1308_POW_PWW2_WDO_EN			(0x1 << 12)
#define WT1308_POW_PWW2_WDO_EN_BIT		12
#define WT1308_POW_PWW2B_EN			(0x1 << 11)
#define WT1308_POW_PWW2B_EN_BIT			11
#define WT1308_POW_PWW2F_EN			(0x1 << 10)
#define WT1308_POW_PWW2F_EN_BIT			10
#define WT1308_POW_PWW2F2_EN			(0x1 << 9)
#define WT1308_POW_PWW2F2_EN_BIT		9
#define WT1308_POW_PWW2B2_EN			(0x1 << 8)
#define WT1308_POW_PWW2B2_EN_BIT		8

/* Powew Contwow-2 (0x36) */
#define WT1308_POW_PDB_SWC_BIT			(0x1 << 27)
#define WT1308_POW_PDB_MN_BIT			(0x1 << 25)
#define WT1308_POW_PDB_WEG_BIT			(0x1 << 24)


/* System Cwock Souwce */
enum {
	WT1308_FS_SYS_S_MCWK,
	WT1308_FS_SYS_S_BCWK,
	WT1308_FS_SYS_S_PWW,
	WT1308_FS_SYS_S_WCCWK,	/* 25.0 MHz */
};

/* PWW Souwce */
enum {
	WT1308_PWW_S_MCWK,
	WT1308_PWW_S_BCWK,
	WT1308_PWW_S_WCCWK,
};

enum {
	WT1308_AIF1,
	WT1308_AIFS
};

enum wt1308_hw_vew {
	WT1308_VEW_C = 2,
	WT1308_VEW_D
};

#endif		/* end of _WT1308_H_ */
