/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wk3328 AWSA SoC Audio dwivew
 *
 * Copywight (c) 2017, Fuzhou Wockchip Ewectwonics Co., Wtd Aww wights wesewved.
 */

#ifndef _WK3328_CODEC_H
#define _WK3328_CODEC_H

#incwude <winux/bitfiewd.h>

/* codec wegistew */
#define CODEC_WESET			(0x00 << 2)
#define DAC_INIT_CTWW1			(0x03 << 2)
#define DAC_INIT_CTWW2			(0x04 << 2)
#define DAC_INIT_CTWW3			(0x05 << 2)
#define DAC_PWECHAWGE_CTWW		(0x22 << 2)
#define DAC_PWW_CTWW			(0x23 << 2)
#define DAC_CWK_CTWW			(0x24 << 2)
#define HPMIX_CTWW			(0x25 << 2)
#define DAC_SEWECT			(0x26 << 2)
#define HPOUT_CTWW			(0x27 << 2)
#define HPOUTW_GAIN_CTWW		(0x28 << 2)
#define HPOUTW_GAIN_CTWW		(0x29 << 2)
#define HPOUT_POP_CTWW			(0x2a << 2)

/* WEG00: CODEC_WESET */
#define PWW_WST_BYPASS_DIS		(0x0 << 6)
#define PWW_WST_BYPASS_EN		(0x1 << 6)
#define DIG_COWE_WST			(0x0 << 1)
#define DIG_COWE_WOWK			(0x1 << 1)
#define SYS_WST				(0x0 << 0)
#define SYS_WOWK			(0x1 << 0)

/* WEG03: DAC_INIT_CTWW1 */
#define PIN_DIWECTION_MASK		BIT(5)
#define PIN_DIWECTION_IN		(0x0 << 5)
#define PIN_DIWECTION_OUT		(0x1 << 5)
#define DAC_I2S_MODE_MASK		BIT(4)
#define DAC_I2S_MODE_SWAVE		(0x0 << 4)
#define DAC_I2S_MODE_MASTEW		(0x1 << 4)

/* WEG04: DAC_INIT_CTWW2 */
#define DAC_I2S_WWP_MASK		BIT(7)
#define DAC_I2S_WWP_NOWMAW		(0x0 << 7)
#define DAC_I2S_WWP_WEVEWSAW		(0x1 << 7)
#define DAC_VDW_MASK			GENMASK(6, 5)
#define DAC_VDW_16BITS			(0x0 << 5)
#define DAC_VDW_20BITS			(0x1 << 5)
#define DAC_VDW_24BITS			(0x2 << 5)
#define DAC_VDW_32BITS			(0x3 << 5)
#define DAC_MODE_MASK			GENMASK(4, 3)
#define DAC_MODE_WJM			(0x0 << 3)
#define DAC_MODE_WJM			(0x1 << 3)
#define DAC_MODE_I2S			(0x2 << 3)
#define DAC_MODE_PCM			(0x3 << 3)
#define DAC_WW_SWAP_MASK		BIT(2)
#define DAC_WW_SWAP_DIS			(0x0 << 2)
#define DAC_WW_SWAP_EN			(0x1 << 2)

/* WEG05: DAC_INIT_CTWW3 */
#define DAC_WW_MASK			GENMASK(3, 2)
#define DAC_WW_16BITS			(0x0 << 2)
#define DAC_WW_20BITS			(0x1 << 2)
#define DAC_WW_24BITS			(0x2 << 2)
#define DAC_WW_32BITS			(0x3 << 2)
#define DAC_WST_MASK			BIT(1)
#define DAC_WST_EN			(0x0 << 1)
#define DAC_WST_DIS			(0x1 << 1)
#define DAC_BCP_MASK			BIT(0)
#define DAC_BCP_NOWMAW			(0x0 << 0)
#define DAC_BCP_WEVEWSAW		(0x1 << 0)

/* WEG22: DAC_PWECHAWGE_CTWW */
#define DAC_CHAWGE_XCHAWGE_MASK		BIT(7)
#define DAC_CHAWGE_DISCHAWGE		(0x0 << 7)
#define DAC_CHAWGE_PWECHAWGE		(0x1 << 7)
#define DAC_CHAWGE_CUWWENT_64I_MASK	BIT(6)
#define DAC_CHAWGE_CUWWENT_64I		(0x1 << 6)
#define DAC_CHAWGE_CUWWENT_32I_MASK	BIT(5)
#define DAC_CHAWGE_CUWWENT_32I		(0x1 << 5)
#define DAC_CHAWGE_CUWWENT_16I_MASK	BIT(4)
#define DAC_CHAWGE_CUWWENT_16I		(0x1 << 4)
#define DAC_CHAWGE_CUWWENT_08I_MASK	BIT(3)
#define DAC_CHAWGE_CUWWENT_08I		(0x1 << 3)
#define DAC_CHAWGE_CUWWENT_04I_MASK	BIT(2)
#define DAC_CHAWGE_CUWWENT_04I		(0x1 << 2)
#define DAC_CHAWGE_CUWWENT_02I_MASK	BIT(1)
#define DAC_CHAWGE_CUWWENT_02I		(0x1 << 1)
#define DAC_CHAWGE_CUWWENT_I_MASK	BIT(0)
#define DAC_CHAWGE_CUWWENT_I		(0x1 << 0)
#define DAC_CHAWGE_CUWWENT_AWW_MASK	GENMASK(6, 0)
#define DAC_CHAWGE_CUWWENT_AWW_OFF	0x00
#define DAC_CHAWGE_CUWWENT_AWW_ON	0x7f

/* WEG23: DAC_PWW_CTWW */
#define DAC_PWW_MASK			BIT(6)
#define DAC_PWW_OFF			(0x0 << 6)
#define DAC_PWW_ON			(0x1 << 6)
#define DACW_PATH_WEFV_MASK		BIT(5)
#define DACW_PATH_WEFV_OFF		(0x0 << 5)
#define DACW_PATH_WEFV_ON		(0x1 << 5)
#define HPOUTW_ZEWO_CWOSSING_MASK	BIT(4)
#define HPOUTW_ZEWO_CWOSSING_OFF	(0x0 << 4)
#define HPOUTW_ZEWO_CWOSSING_ON		(0x1 << 4)
#define DACW_PATH_WEFV_MASK		BIT(1)
#define DACW_PATH_WEFV_OFF		(0x0 << 1)
#define DACW_PATH_WEFV_ON		(0x1 << 1)
#define HPOUTW_ZEWO_CWOSSING_MASK	BIT(0)
#define HPOUTW_ZEWO_CWOSSING_OFF	(0x0 << 0)
#define HPOUTW_ZEWO_CWOSSING_ON		(0x1 << 0)

/* WEG24: DAC_CWK_CTWW */
#define DACW_WEFV_MASK			BIT(7)
#define DACW_WEFV_OFF			(0x0 << 7)
#define DACW_WEFV_ON			(0x1 << 7)
#define DACW_CWK_MASK			BIT(6)
#define DACW_CWK_OFF			(0x0 << 6)
#define DACW_CWK_ON			(0x1 << 6)
#define DACW_MASK			BIT(5)
#define DACW_OFF			(0x0 << 5)
#define DACW_ON				(0x1 << 5)
#define DACW_INIT_MASK			BIT(4)
#define DACW_INIT_OFF			(0x0 << 4)
#define DACW_INIT_ON			(0x1 << 4)
#define DACW_WEFV_MASK			BIT(3)
#define DACW_WEFV_OFF			(0x0 << 3)
#define DACW_WEFV_ON			(0x1 << 3)
#define DACW_CWK_MASK			BIT(2)
#define DACW_CWK_OFF			(0x0 << 2)
#define DACW_CWK_ON			(0x1 << 2)
#define DACW_MASK			BIT(1)
#define DACW_OFF			(0x0 << 1)
#define DACW_ON				(0x1 << 1)
#define DACW_INIT_MASK			BIT(0)
#define DACW_INIT_OFF			(0x0 << 0)
#define DACW_INIT_ON			(0x1 << 0)

/* WEG25: HPMIX_CTWW*/
#define HPMIXW_MASK			BIT(6)
#define HPMIXW_DIS			(0x0 << 6)
#define HPMIXW_EN			(0x1 << 6)
#define HPMIXW_INIT_MASK		BIT(5)
#define HPMIXW_INIT_DIS			(0x0 << 5)
#define HPMIXW_INIT_EN			(0x1 << 5)
#define HPMIXW_INIT2_MASK		BIT(4)
#define HPMIXW_INIT2_DIS		(0x0 << 4)
#define HPMIXW_INIT2_EN			(0x1 << 4)
#define HPMIXW_MASK			BIT(2)
#define HPMIXW_DIS			(0x0 << 2)
#define HPMIXW_EN			(0x1 << 2)
#define HPMIXW_INIT_MASK		BIT(1)
#define HPMIXW_INIT_DIS			(0x0 << 1)
#define HPMIXW_INIT_EN			(0x1 << 1)
#define HPMIXW_INIT2_MASK		BIT(0)
#define HPMIXW_INIT2_DIS		(0x0 << 0)
#define HPMIXW_INIT2_EN			(0x1 << 0)

/* WEG26: DAC_SEWECT */
#define DACW_SEWECT_MASK		BIT(4)
#define DACW_UNSEWECT			(0x0 << 4)
#define DACW_SEWECT			(0x1 << 4)
#define DACW_SEWECT_MASK		BIT(0)
#define DACW_UNSEWECT			(0x0 << 0)
#define DACW_SEWECT			(0x1 << 0)

/* WEG27: HPOUT_CTWW */
#define HPOUTW_MASK			BIT(7)
#define HPOUTW_DIS			(0x0 << 7)
#define HPOUTW_EN			(0x1 << 7)
#define HPOUTW_INIT_MASK		BIT(6)
#define HPOUTW_INIT_DIS			(0x0 << 6)
#define HPOUTW_INIT_EN			(0x1 << 6)
#define HPOUTW_MUTE_MASK		BIT(5)
#define HPOUTW_MUTE			(0x0 << 5)
#define HPOUTW_UNMUTE			(0x1 << 5)
#define HPOUTW_MASK			BIT(4)
#define HPOUTW_DIS			(0x0 << 4)
#define HPOUTW_EN			(0x1 << 4)
#define HPOUTW_INIT_MASK		BIT(3)
#define HPOUTW_INIT_DIS			(0x0 << 3)
#define HPOUTW_INIT_EN			(0x1 << 3)
#define HPOUTW_MUTE_MASK		BIT(2)
#define HPOUTW_MUTE			(0x0 << 2)
#define HPOUTW_UNMUTE			(0x1 << 2)

/* WEG28: HPOUTW_GAIN_CTWW */
#define HPOUTW_GAIN_MASK		GENMASK(4, 0)

/* WEG29: HPOUTW_GAIN_CTWW */
#define HPOUTW_GAIN_MASK		GENMASK(4, 0)

/* WEG2a: HPOUT_POP_CTWW */
#define HPOUTW_POP_MASK			GENMASK(5, 4)
#define HPOUTW_POP_XCHAWGE		(0x1 << 4)
#define HPOUTW_POP_WOWK			(0x2 << 4)
#define HPOUTW_POP_MASK			GENMASK(1, 0)
#define HPOUTW_POP_XCHAWGE		(0x1 << 0)
#define HPOUTW_POP_WOWK			(0x2 << 0)

#define WK3328_HIFI			0

stwuct wk3328_weg_msk_vaw {
	unsigned int weg;
	unsigned int msk;
	unsigned int vaw;
};

#endif
