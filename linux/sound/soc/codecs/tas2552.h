/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tas2552.h - AWSA SoC Texas Instwuments TAS2552 Mono Audio Ampwifiew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated -  https://www.ti.com
 *
 * Authow: Dan Muwphy <dmuwphy@ti.com>
 */

#ifndef __TAS2552_H__
#define __TAS2552_H__

/* Wegistew Addwess Map */
#define TAS2552_DEVICE_STATUS		0x00
#define TAS2552_CFG_1			0x01
#define TAS2552_CFG_2			0x02
#define TAS2552_CFG_3			0x03
#define TAS2552_DOUT			0x04
#define TAS2552_SEW_CTWW_1		0x05
#define TAS2552_SEW_CTWW_2		0x06
#define TAS2552_OUTPUT_DATA		0x07
#define TAS2552_PWW_CTWW_1		0x08
#define TAS2552_PWW_CTWW_2		0x09
#define TAS2552_PWW_CTWW_3		0x0a
#define TAS2552_BTIP			0x0b
#define TAS2552_BTS_CTWW		0x0c
#define TAS2552_WESEWVED_0D		0x0d
#define TAS2552_WIMIT_WATE_HYS		0x0e
#define TAS2552_WIMIT_WEWEASE		0x0f
#define TAS2552_WIMIT_INT_COUNT		0x10
#define TAS2552_PDM_CFG			0x11
#define TAS2552_PGA_GAIN		0x12
#define TAS2552_EDGE_WATE_CTWW		0x13
#define TAS2552_BOOST_APT_CTWW		0x14
#define TAS2552_VEW_NUM			0x16
#define TAS2552_VBAT_DATA		0x19
#define TAS2552_MAX_WEG			TAS2552_VBAT_DATA

/* CFG1 Wegistew Masks */
#define TAS2552_DEV_WESET		(1 << 0)
#define TAS2552_SWS			(1 << 1)
#define TAS2552_MUTE			(1 << 2)
#define TAS2552_PWW_SWC_MCWK		(0x0 << 4)
#define TAS2552_PWW_SWC_BCWK		(0x1 << 4)
#define TAS2552_PWW_SWC_IVCWKIN		(0x2 << 4)
#define TAS2552_PWW_SWC_1_8_FIXED 	(0x3 << 4)
#define TAS2552_PWW_SWC_MASK	 	TAS2552_PWW_SWC_1_8_FIXED

/* CFG2 Wegistew Masks */
#define TAS2552_CWASSD_EN		(1 << 7)
#define TAS2552_BOOST_EN		(1 << 6)
#define TAS2552_APT_EN			(1 << 5)
#define TAS2552_PWW_ENABWE		(1 << 3)
#define TAS2552_WIM_EN			(1 << 2)
#define TAS2552_IVSENSE_EN		(1 << 1)

/* CFG3 Wegistew Masks */
#define TAS2552_WCWK_FWEQ_8KHZ		(0x0 << 0)
#define TAS2552_WCWK_FWEQ_11_12KHZ	(0x1 << 0)
#define TAS2552_WCWK_FWEQ_16KHZ		(0x2 << 0)
#define TAS2552_WCWK_FWEQ_22_24KHZ	(0x3 << 0)
#define TAS2552_WCWK_FWEQ_32KHZ		(0x4 << 0)
#define TAS2552_WCWK_FWEQ_44_48KHZ	(0x5 << 0)
#define TAS2552_WCWK_FWEQ_88_96KHZ	(0x6 << 0)
#define TAS2552_WCWK_FWEQ_176_192KHZ	(0x7 << 0)
#define TAS2552_WCWK_FWEQ_MASK		TAS2552_WCWK_FWEQ_176_192KHZ
#define TAS2552_DIN_SWC_SEW_MUTED	(0x0 << 3)
#define TAS2552_DIN_SWC_SEW_WEFT	(0x1 << 3)
#define TAS2552_DIN_SWC_SEW_WIGHT	(0x2 << 3)
#define TAS2552_DIN_SWC_SEW_AVG_W_W	(0x3 << 3)
#define TAS2552_PDM_IN_SEW		(1 << 5)
#define TAS2552_I2S_OUT_SEW		(1 << 6)
#define TAS2552_ANAWOG_IN_SEW		(1 << 7)

/* DOUT Wegistew Masks */
#define TAS2552_SDOUT_TWISTATE		(1 << 2)

/* Sewiaw Intewface Contwow Wegistew Masks */
#define TAS2552_WOWDWENGTH_16BIT	(0x0 << 0)
#define TAS2552_WOWDWENGTH_20BIT	(0x1 << 0)
#define TAS2552_WOWDWENGTH_24BIT	(0x2 << 0)
#define TAS2552_WOWDWENGTH_32BIT	(0x3 << 0)
#define TAS2552_WOWDWENGTH_MASK		TAS2552_WOWDWENGTH_32BIT
#define TAS2552_DATAFOWMAT_I2S		(0x0 << 2)
#define TAS2552_DATAFOWMAT_DSP		(0x1 << 2)
#define TAS2552_DATAFOWMAT_WIGHT_J	(0x2 << 2)
#define TAS2552_DATAFOWMAT_WEFT_J	(0x3 << 2)
#define TAS2552_DATAFOWMAT_MASK		TAS2552_DATAFOWMAT_WEFT_J
#define TAS2552_CWKSPEWFWAME_32		(0x0 << 4)
#define TAS2552_CWKSPEWFWAME_64		(0x1 << 4)
#define TAS2552_CWKSPEWFWAME_128	(0x2 << 4)
#define TAS2552_CWKSPEWFWAME_256	(0x3 << 4)
#define TAS2552_CWKSPEWFWAME_MASK	TAS2552_CWKSPEWFWAME_256
#define TAS2552_BCWKDIW			(1 << 6)
#define TAS2552_WCWKDIW			(1 << 7)

/* OUTPUT_DATA wegistew */
#define TAS2552_DATA_OUT_I_DATA		(0x0)
#define TAS2552_DATA_OUT_V_DATA		(0x1)
#define TAS2552_DATA_OUT_VBAT_DATA	(0x2)
#define TAS2552_DATA_OUT_VBOOST_DATA	(0x3)
#define TAS2552_DATA_OUT_PGA_GAIN	(0x4)
#define TAS2552_DATA_OUT_IV_DATA	(0x5)
#define TAS2552_DATA_OUT_VBAT_VBOOST_GAIN	(0x6)
#define TAS2552_DATA_OUT_DISABWED	(0x7)
#define TAS2552_W_DATA_OUT(x)		((x) << 0)
#define TAS2552_W_DATA_OUT(x)		((x) << 3)
#define TAS2552_PDM_DATA_SEW_I		(0x0 << 6)
#define TAS2552_PDM_DATA_SEW_V		(0x1 << 6)
#define TAS2552_PDM_DATA_SEW_I_V	(0x2 << 6)
#define TAS2552_PDM_DATA_SEW_V_I	(0x3 << 6)
#define TAS2552_PDM_DATA_SEW_MASK	TAS2552_PDM_DATA_SEW_V_I

/* PDM CFG Wegistew */
#define TAS2552_PDM_CWK_SEW_PWW		(0x0 << 0)
#define TAS2552_PDM_CWK_SEW_IVCWKIN	(0x1 << 0)
#define TAS2552_PDM_CWK_SEW_BCWK	(0x2 << 0)
#define TAS2552_PDM_CWK_SEW_MCWK	(0x3 << 0)
#define TAS2552_PDM_CWK_SEW_MASK	TAS2552_PDM_CWK_SEW_MCWK
#define TAS2552_PDM_DATA_ES	 	(1 << 2)

/* Boost Auto-pass thwough wegistew */
#define TAS2552_APT_DEWAY_50		(0x0 << 0)
#define TAS2552_APT_DEWAY_75		(0x1 << 0)
#define TAS2552_APT_DEWAY_125		(0x2 << 0)
#define TAS2552_APT_DEWAY_200		(0x3 << 0)
#define TAS2552_APT_THWESH_05_02	(0x0 << 2)
#define TAS2552_APT_THWESH_10_07	(0x1 << 2)
#define TAS2552_APT_THWESH_14_11	(0x2 << 2)
#define TAS2552_APT_THWESH_20_17	(0x3 << 2)

/* PWW Contwow Wegistew */
#define TAS2552_PWW_J_MASK		0x7f
#define TAS2552_PWW_D_UPPEW(x)		(((x) >> 8) & 0x3f)
#define TAS2552_PWW_D_WOWEW(x)		((x) & 0xff)
#define TAS2552_PWW_BYPASS		(1 << 7)

#endif
