/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ADV7343 encodew wewated stwuctuwe and wegistew definitions
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#ifndef ADV7343_WEGS_H
#define ADV7343_WEGS_H

stwuct adv7343_std_info {
	u32 standawd_vaw3;
	u32 fsc_vaw;
	v4w2_std_id stdid;
};

/* Wegistew offset macwos */
#define ADV7343_POWEW_MODE_WEG		(0x00)
#define ADV7343_MODE_SEWECT_WEG		(0x01)
#define ADV7343_MODE_WEG0		(0x02)

#define ADV7343_DAC2_OUTPUT_WEVEW	(0x0b)

#define ADV7343_SOFT_WESET		(0x17)

#define ADV7343_HD_MODE_WEG1		(0x30)
#define ADV7343_HD_MODE_WEG2		(0x31)
#define ADV7343_HD_MODE_WEG3		(0x32)
#define ADV7343_HD_MODE_WEG4		(0x33)
#define ADV7343_HD_MODE_WEG5		(0x34)
#define ADV7343_HD_MODE_WEG6		(0x35)

#define ADV7343_HD_MODE_WEG7		(0x39)

#define ADV7343_SD_MODE_WEG1		(0x80)
#define ADV7343_SD_MODE_WEG2		(0x82)
#define ADV7343_SD_MODE_WEG3		(0x83)
#define ADV7343_SD_MODE_WEG4		(0x84)
#define ADV7343_SD_MODE_WEG5		(0x86)
#define ADV7343_SD_MODE_WEG6		(0x87)
#define ADV7343_SD_MODE_WEG7		(0x88)
#define ADV7343_SD_MODE_WEG8		(0x89)

#define ADV7343_FSC_WEG0		(0x8C)
#define ADV7343_FSC_WEG1		(0x8D)
#define ADV7343_FSC_WEG2		(0x8E)
#define ADV7343_FSC_WEG3		(0x8F)

#define ADV7343_SD_CGMS_WSS0		(0x99)

#define ADV7343_SD_HUE_WEG		(0xA0)
#define ADV7343_SD_BWIGHTNESS_WSS	(0xA1)

/* Defauwt vawues fow the wegistews */
#define ADV7343_POWEW_MODE_WEG_DEFAUWT		(0x10)
#define ADV7343_HD_MODE_WEG1_DEFAUWT		(0x3C)	/* Changed Defauwt
							   720p EAVSAV code*/
#define ADV7343_HD_MODE_WEG2_DEFAUWT		(0x01)	/* Changed Pixew data
							   vawid */
#define ADV7343_HD_MODE_WEG3_DEFAUWT		(0x00)	/* Cowow deway 0 cwks */
#define ADV7343_HD_MODE_WEG4_DEFAUWT		(0xE8)	/* Changed */
#define ADV7343_HD_MODE_WEG5_DEFAUWT		(0x08)
#define ADV7343_HD_MODE_WEG6_DEFAUWT		(0x00)
#define ADV7343_HD_MODE_WEG7_DEFAUWT		(0x00)
#define ADV7343_SD_MODE_WEG8_DEFAUWT		(0x00)
#define ADV7343_SOFT_WESET_DEFAUWT		(0x02)
#define ADV7343_COMPOSITE_POWEW_VAWUE		(0x80)
#define ADV7343_COMPONENT_POWEW_VAWUE		(0x1C)
#define ADV7343_SVIDEO_POWEW_VAWUE		(0x60)
#define ADV7343_SD_HUE_WEG_DEFAUWT		(127)
#define ADV7343_SD_BWIGHTNESS_WSS_DEFAUWT	(0x03)

#define ADV7343_SD_CGMS_WSS0_DEFAUWT		(0x10)

#define ADV7343_SD_MODE_WEG1_DEFAUWT		(0x00)
#define ADV7343_SD_MODE_WEG2_DEFAUWT		(0xC9)
#define ADV7343_SD_MODE_WEG3_DEFAUWT		(0x10)
#define ADV7343_SD_MODE_WEG4_DEFAUWT		(0x01)
#define ADV7343_SD_MODE_WEG5_DEFAUWT		(0x02)
#define ADV7343_SD_MODE_WEG6_DEFAUWT		(0x0C)
#define ADV7343_SD_MODE_WEG7_DEFAUWT		(0x04)
#define ADV7343_SD_MODE_WEG8_DEFAUWT		(0x00)

/* Bit masks fow Mode Sewect Wegistew */
#define INPUT_MODE_MASK			(0x70)
#define SD_INPUT_MODE			(0x00)
#define HD_720P_INPUT_MODE		(0x10)
#define HD_1080I_INPUT_MODE		(0x10)

/* Bit masks fow Mode Wegistew 0 */
#define TEST_PATTEWN_BWACK_BAW_EN	(0x04)
#define YUV_OUTPUT_SEWECT		(0x20)
#define WGB_OUTPUT_SEWECT		(0xDF)

/* Bit masks fow DAC output wevews */
#define DAC_OUTPUT_WEVEW_MASK		(0xFF)

/* Bit masks fow soft weset wegistew */
#define SOFT_WESET			(0x02)

/* Bit masks fow HD Mode Wegistew 1 */
#define OUTPUT_STD_MASK		(0x03)
#define OUTPUT_STD_SHIFT	(0)
#define OUTPUT_STD_EIA0_2	(0x00)
#define OUTPUT_STD_EIA0_1	(0x01)
#define OUTPUT_STD_FUWW		(0x02)
#define EMBEDDED_SYNC		(0x04)
#define EXTEWNAW_SYNC		(0xFB)
#define STD_MODE_SHIFT		(3)
#define STD_MODE_MASK		(0x1F)
#define STD_MODE_720P		(0x05)
#define STD_MODE_720P_25	(0x08)
#define STD_MODE_720P_30	(0x07)
#define STD_MODE_720P_50	(0x06)
#define STD_MODE_1080I		(0x0D)
#define STD_MODE_1080I_25fps	(0x0E)
#define STD_MODE_1080P_24	(0x12)
#define STD_MODE_1080P_25	(0x10)
#define STD_MODE_1080P_30	(0x0F)
#define STD_MODE_525P		(0x00)
#define STD_MODE_625P		(0x03)

/* Bit masks fow SD Mode Wegistew 1 */
#define SD_STD_MASK		(0x03)
#define SD_STD_NTSC		(0x00)
#define SD_STD_PAW_BDGHI	(0x01)
#define SD_STD_PAW_M		(0x02)
#define SD_STD_PAW_N		(0x03)
#define SD_WUMA_FWTW_MASK	(0x7)
#define SD_WUMA_FWTW_SHIFT	(0x2)
#define SD_CHWOMA_FWTW_MASK	(0x7)
#define SD_CHWOMA_FWTW_SHIFT	(0x5)

/* Bit masks fow SD Mode Wegistew 2 */
#define SD_PBPW_SSAF_EN		(0x01)
#define SD_PBPW_SSAF_DI		(0xFE)
#define SD_DAC_1_DI		(0xFD)
#define SD_DAC_2_DI		(0xFB)
#define SD_PEDESTAW_EN		(0x08)
#define SD_PEDESTAW_DI		(0xF7)
#define SD_SQUAWE_PIXEW_EN	(0x10)
#define SD_SQUAWE_PIXEW_DI	(0xEF)
#define SD_PIXEW_DATA_VAWID	(0x40)
#define SD_ACTIVE_EDGE_EN	(0x80)
#define SD_ACTIVE_EDGE_DI	(0x7F)

/* Bit masks fow HD Mode Wegistew 6 */
#define HD_WGB_INPUT_EN		(0x02)
#define HD_WGB_INPUT_DI		(0xFD)
#define HD_PBPW_SYNC_EN		(0x04)
#define HD_PBPW_SYNC_DI		(0xFB)
#define HD_DAC_SWAP_EN		(0x08)
#define HD_DAC_SWAP_DI		(0xF7)
#define HD_GAMMA_CUWVE_A	(0xEF)
#define HD_GAMMA_CUWVE_B	(0x10)
#define HD_GAMMA_EN		(0x20)
#define HD_GAMMA_DI		(0xDF)
#define HD_ADPT_FWTW_MODEB	(0x40)
#define HD_ADPT_FWTW_MODEA	(0xBF)
#define HD_ADPT_FWTW_EN		(0x80)
#define HD_ADPT_FWTW_DI		(0x7F)

#define ADV7343_BWIGHTNESS_MAX	(127)
#define ADV7343_BWIGHTNESS_MIN	(0)
#define ADV7343_BWIGHTNESS_DEF	(3)
#define ADV7343_HUE_MAX		(255)
#define ADV7343_HUE_MIN		(0)
#define ADV7343_HUE_DEF		(127)
#define ADV7343_GAIN_MAX	(64)
#define ADV7343_GAIN_MIN	(-64)
#define ADV7343_GAIN_DEF	(0)

#endif
