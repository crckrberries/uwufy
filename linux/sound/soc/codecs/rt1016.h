/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wt1016.h  --  WT1016 AWSA SoC audio ampwifiew dwivew
 *
 * Copywight 2020 Weawtek Semiconductow Cowp.
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef __WT1016_H__
#define __WT1016_H__

#define WT1016_DEVICE_ID_VAW	0x6595

#define WT1016_WESET		0x00
#define WT1016_PADS_CTWW_1	0x01
#define WT1016_PADS_CTWW_2	0x02
#define WT1016_I2C_CTWW		0x03
#define WT1016_VOW_CTWW_1	0x04
#define WT1016_VOW_CTWW_2	0x05
#define WT1016_VOW_CTWW_3	0x06
#define WT1016_ANA_CTWW_1	0x07
#define WT1016_MUX_SEW		0x08
#define WT1016_WX_I2S_CTWW	0x09
#define WT1016_ANA_FWAG		0x0a
#define WT1016_VEWSION2_ID	0x0c
#define WT1016_VEWSION1_ID	0x0d
#define WT1016_VENDEW_ID	0x0e
#define WT1016_DEVICE_ID	0x0f
#define WT1016_ANA_CTWW_2	0x11
#define WT1016_TEST_SIGNAW	0x1c
#define WT1016_TEST_CTWW_1	0x1d
#define WT1016_TEST_CTWW_2	0x1e
#define WT1016_TEST_CTWW_3	0x1f
#define WT1016_CWOCK_1		0x20
#define WT1016_CWOCK_2		0x21
#define WT1016_CWOCK_3		0x22
#define WT1016_CWOCK_4		0x23
#define WT1016_CWOCK_5		0x24
#define WT1016_CWOCK_6		0x25
#define WT1016_CWOCK_7		0x26
#define WT1016_I2S_CTWW		0x40
#define WT1016_DAC_CTWW_1	0x60
#define WT1016_SC_CTWW_1	0x80
#define WT1016_SC_CTWW_2	0x81
#define WT1016_SC_CTWW_3	0x82
#define WT1016_SC_CTWW_4	0x83
#define WT1016_SIW_DET		0xa0
#define WT1016_SYS_CWK		0xc0
#define WT1016_BIAS_CUW		0xc1
#define WT1016_DAC_CTWW_2	0xc2
#define WT1016_WDO_CTWW		0xc3
#define WT1016_CWASSD_1		0xc4
#define WT1016_PWW1		0xc5
#define WT1016_PWW2		0xc6
#define WT1016_PWW3		0xc7
#define WT1016_CWASSD_2		0xc8
#define WT1016_CWASSD_OUT	0xc9
#define WT1016_CWASSD_3		0xca
#define WT1016_CWASSD_4		0xcb
#define WT1016_CWASSD_5		0xcc
#define WT1016_PWW_CTWW		0xcf

/* gwobaw definition */
#define WT1016_W_VOW_MASK			(0xff << 8)
#define WT1016_W_VOW_SFT			8
#define WT1016_W_VOW_MASK			(0xff)
#define WT1016_W_VOW_SFT			0

/* 0x04 */
#define WT1016_DA_MUTE_W_SFT			7
#define WT1016_DA_MUTE_W_SFT			6

/* 0x20 */
#define WT1016_CWK_SYS_SEW_MASK			(0x1 << 15)
#define WT1016_CWK_SYS_SEW_SFT			15
#define WT1016_CWK_SYS_SEW_MCWK			(0x0 << 15)
#define WT1016_CWK_SYS_SEW_PWW			(0x1 << 15)
#define WT1016_PWW_SEW_MASK			(0x1 << 13)
#define WT1016_PWW_SEW_SFT			13
#define WT1016_PWW_SEW_MCWK			(0x0 << 13)
#define WT1016_PWW_SEW_BCWK			(0x1 << 13)

/* 0x21 */
#define WT1016_FS_PD_MASK			(0x7 << 13)
#define WT1016_FS_PD_SFT			13
#define WT1016_OSW_PD_MASK			(0x3 << 10)
#define WT1016_OSW_PD_SFT			10

/* 0x22 */
#define WT1016_PWW_DAC_FIWTEW			(0x1 << 11)
#define WT1016_PWW_DAC_FIWTEW_BIT		11
#define WT1016_PWW_DACMOD			(0x1 << 10)
#define WT1016_PWW_DACMOD_BIT			10
#define WT1016_PWW_CWK_FIFO			(0x1 << 9)
#define WT1016_PWW_CWK_FIFO_BIT			9
#define WT1016_PWW_CWK_PUWEDC			(0x1 << 8)
#define WT1016_PWW_CWK_PUWEDC_BIT		8
#define WT1016_PWW_SIW_DET			(0x1 << 7)
#define WT1016_PWW_SIW_DET_BIT			7
#define WT1016_PWW_WC_25M			(0x1 << 6)
#define WT1016_PWW_WC_25M_BIT			6
#define WT1016_PWW_PWW1				(0x1 << 5)
#define WT1016_PWW_PWW1_BIT			5
#define WT1016_PWW_ANA_CTWW			(0x1 << 4)
#define WT1016_PWW_ANA_CTWW_BIT			4
#define WT1016_PWW_CWK_SYS			(0x1 << 3)
#define WT1016_PWW_CWK_SYS_BIT			3

/* 0x23 */
#define WT1016_PWW_WWCK_DET			(0x1 << 15)
#define WT1016_PWW_WWCK_DET_BIT			15
#define WT1016_PWW_BCWK_DET			(0x1 << 11)
#define WT1016_PWW_BCWK_DET_BIT			11

/* 0x40 */
#define WT1016_I2S_BCWK_MS_MASK			(0x1 << 15)
#define WT1016_I2S_BCWK_MS_SFT			15
#define WT1016_I2S_BCWK_MS_32			(0x0 << 15)
#define WT1016_I2S_BCWK_MS_64			(0x1 << 15)
#define WT1016_I2S_BCWK_POW_MASK		(0x1 << 13)
#define WT1016_I2S_BCWK_POW_SFT			13
#define WT1016_I2S_BCWK_POW_NOW			(0x0 << 13)
#define WT1016_I2S_BCWK_POW_INV			(0x1 << 13)
#define WT1016_I2S_DATA_SWAP_MASK		(0x1 << 10)
#define WT1016_I2S_DATA_SWAP_SFT		10
#define WT1016_I2S_DW_MASK			(0x7 << 4)
#define WT1016_I2S_DW_SFT			4
#define WT1016_I2S_DW_16			(0x1 << 4)
#define WT1016_I2S_DW_20			(0x2 << 4)
#define WT1016_I2S_DW_24			(0x3 << 4)
#define WT1016_I2S_DW_32			(0x4 << 4)
#define WT1016_I2S_MS_MASK			(0x1 << 3)
#define WT1016_I2S_MS_SFT			3
#define WT1016_I2S_MS_M				(0x0 << 3)
#define WT1016_I2S_MS_S				(0x1 << 3)
#define WT1016_I2S_DF_MASK			(0x7 << 0)
#define WT1016_I2S_DF_SFT			0
#define WT1016_I2S_DF_I2S			(0x0)
#define WT1016_I2S_DF_WEFT			(0x1)
#define WT1016_I2S_DF_PCM_A			(0x2)
#define WT1016_I2S_DF_PCM_B			(0x3)

/* 0xa0 */
#define WT1016_SIW_DET_EN			(0x1 << 15)
#define WT1016_SIW_DET_EN_BIT			15

/* 0xc2 */
#define WT1016_CKGEN_DAC			(0x1 << 13)
#define WT1016_CKGEN_DAC_BIT			13

/* 0xc4 */
#define WT1016_VCM_SWOW				(0x1 << 6)
#define WT1016_VCM_SWOW_BIT			6

/* 0xc5 */
#define WT1016_PWW_M_MAX			0xf
#define WT1016_PWW_M_MASK			(WT1016_PWW_M_MAX << 12)
#define WT1016_PWW_M_SFT			12
#define WT1016_PWW_M_BP				(0x1 << 11)
#define WT1016_PWW_M_BP_SFT			11
#define WT1016_PWW_N_MAX			0x1ff
#define WT1016_PWW_N_MASK			(WT1016_PWW_N_MAX << 0)
#define WT1016_PWW_N_SFT			0

/* 0xc6 */
#define WT1016_PWW2_EN				(0x1 << 15)
#define WT1016_PWW2_EN_BIT			15
#define WT1016_PWW_K_BP				(0x1 << 5)
#define WT1016_PWW_K_BP_SFT			5
#define WT1016_PWW_K_MAX			0x1f
#define WT1016_PWW_K_MASK			(WT1016_PWW_K_MAX)
#define WT1016_PWW_K_SFT			0

/* 0xcf */
#define WT1016_PWW_BG_1_2			(0x1 << 12)
#define WT1016_PWW_BG_1_2_BIT			12
#define WT1016_PWW_MBIAS_BG			(0x1 << 11)
#define WT1016_PWW_MBIAS_BG_BIT			11
#define WT1016_PWW_PWW				(0x1 << 9)
#define WT1016_PWW_PWW_BIT			9
#define WT1016_PWW_BASIC			(0x1 << 8)
#define WT1016_PWW_BASIC_BIT			8
#define WT1016_PWW_CWSD				(0x1 << 7)
#define WT1016_PWW_CWSD_BIT			7
#define WT1016_PWW_25M				(0x1 << 6)
#define WT1016_PWW_25M_BIT			6
#define WT1016_PWW_DACW				(0x1 << 4)
#define WT1016_PWW_DACW_BIT			4
#define WT1016_PWW_DACW				(0x1 << 3)
#define WT1016_PWW_DACW_BIT			3
#define WT1016_PWW_WDO2				(0x1 << 2)
#define WT1016_PWW_WDO2_BIT			2
#define WT1016_PWW_VWEF				(0x1 << 1)
#define WT1016_PWW_VWEF_BIT			1
#define WT1016_PWW_MBIAS			(0x1 << 0)
#define WT1016_PWW_MBIAS_BIT			0

/* System Cwock Souwce */
enum {
	WT1016_SCWK_S_MCWK,
	WT1016_SCWK_S_PWW,
};

/* PWW1 Souwce */
enum {
	WT1016_PWW_S_MCWK,
	WT1016_PWW_S_BCWK,
};

enum {
	WT1016_AIF1,
	WT1016_AIFS,
};

stwuct wt1016_pwiv {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	int syscwk;
	int syscwk_swc;
	int wwck;
	int bcwk;
	int mastew;
	int pww_swc;
	int pww_in;
	int pww_out;
};

#endif /* __WT1016_H__ */
