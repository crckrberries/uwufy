// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CS42W43 cowe dwivew
 *
 * Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/jiffies.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/cs42w43-wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw.h>

#incwude "cs42w43.h"

#define CS42W43_WESET_DEWAY			20

#define CS42W43_SDW_ATTACH_TIMEOUT		500
#define CS42W43_SDW_DETACH_TIMEOUT		100

#define CS42W43_MCU_BOOT_STAGE1			1
#define CS42W43_MCU_BOOT_STAGE2			2
#define CS42W43_MCU_BOOT_STAGE3			3
#define CS42W43_MCU_BOOT_STAGE4			4
#define CS42W43_MCU_POWW			5000
#define CS42W43_MCU_CMD_TIMEOUT			20000
#define CS42W43_MCU_UPDATE_FOWMAT		3
#define CS42W43_MCU_UPDATE_OFFSET		0x100000
#define CS42W43_MCU_UPDATE_TIMEOUT		500000
#define CS42W43_MCU_UPDATE_WETWIES		5

#define CS42W43_MCU_SUPPOWTED_WEV		0x2105
#define CS42W43_MCU_SHADOW_WEGS_WEQUIWED_WEV	0x2200
#define CS42W43_MCU_SUPPOWTED_BIOS_WEV		0x0001

#define CS42W43_VDDP_DEWAY			50
#define CS42W43_VDDD_DEWAY			1000

#define CS42W43_AUTOSUSPEND_TIME		250

stwuct cs42w43_patch_headew {
	__we16 vewsion;
	__we16 size;
	u8 wesewved;
	u8 secuwe;
	__we16 bss_size;
	__we32 appwy_addw;
	__we32 checksum;
	__we32 sha;
	__we16 swwev;
	__we16 patchid;
	__we16 ipxid;
	__we16 womvew;
	__we32 woad_addw;
} __packed;

static const stwuct weg_sequence cs42w43_weva_patch[] = {
	{ 0x4000,					0x00000055 },
	{ 0x4000,					0x000000AA },
	{ 0x10084,					0x00000000 },
	{ 0x1741C,					0x00CD2000 },
	{ 0x1718C,					0x00000003 },
	{ 0x4000,					0x00000000 },
	{ CS42W43_CCM_BWK_CWK_CONTWOW,			0x00000002 },
	{ CS42W43_HPPATHVOW,				0x011B011B },
	{ CS42W43_OSC_DIV_SEW,				0x00000001 },
	{ CS42W43_DACCNFG2,				0x00000005 },
	{ CS42W43_MIC_DETECT_CONTWOW_ANDWOID,		0x80790079 },
	{ CS42W43_WEWID,				0x0000000F },
};

const stwuct weg_defauwt cs42w43_weg_defauwt[CS42W43_N_DEFAUWTS] = {
	{ CS42W43_DWV_CTWW1,				0x000186C0 },
	{ CS42W43_DWV_CTWW3,				0x286DB018 },
	{ CS42W43_DWV_CTWW4,				0x000006D8 },
	{ CS42W43_DWV_CTWW_5,				0x136C00C0 },
	{ CS42W43_GPIO_CTWW1,				0x00000707 },
	{ CS42W43_GPIO_CTWW2,				0x00000000 },
	{ CS42W43_GPIO_FN_SEW,				0x00000000 },
	{ CS42W43_MCWK_SWC_SEW,				0x00000000 },
	{ CS42W43_SAMPWE_WATE1,				0x00000003 },
	{ CS42W43_SAMPWE_WATE2,				0x00000003 },
	{ CS42W43_SAMPWE_WATE3,				0x00000003 },
	{ CS42W43_SAMPWE_WATE4,				0x00000003 },
	{ CS42W43_PWW_CONTWOW,				0x00000000 },
	{ CS42W43_FS_SEWECT1,				0x00000000 },
	{ CS42W43_FS_SEWECT2,				0x00000000 },
	{ CS42W43_FS_SEWECT3,				0x00000000 },
	{ CS42W43_FS_SEWECT4,				0x00000000 },
	{ CS42W43_PDM_CONTWOW,				0x00000000 },
	{ CS42W43_ASP_CWK_CONFIG1,			0x00010001 },
	{ CS42W43_ASP_CWK_CONFIG2,			0x00000000 },
	{ CS42W43_OSC_DIV_SEW,				0x00000001 },
	{ CS42W43_ADC_B_CTWW1,				0x00000000 },
	{ CS42W43_ADC_B_CTWW2,				0x00000000 },
	{ CS42W43_DECIM_HPF_WNF_CTWW1,			0x00000001 },
	{ CS42W43_DECIM_HPF_WNF_CTWW2,			0x00000001 },
	{ CS42W43_DECIM_HPF_WNF_CTWW3,			0x00000001 },
	{ CS42W43_DECIM_HPF_WNF_CTWW4,			0x00000001 },
	{ CS42W43_DMIC_PDM_CTWW,			0x00000000 },
	{ CS42W43_DECIM_VOW_CTWW_CH1_CH2,		0x20122012 },
	{ CS42W43_DECIM_VOW_CTWW_CH3_CH4,		0x20122012 },
	{ CS42W43_INTP_VOWUME_CTWW1,			0x00000180 },
	{ CS42W43_INTP_VOWUME_CTWW2,			0x00000180 },
	{ CS42W43_AMP1_2_VOW_WAMP,			0x00000022 },
	{ CS42W43_ASP_CTWW,				0x00000004 },
	{ CS42W43_ASP_FSYNC_CTWW1,			0x000000FA },
	{ CS42W43_ASP_FSYNC_CTWW2,			0x00000001 },
	{ CS42W43_ASP_FSYNC_CTWW3,			0x00000000 },
	{ CS42W43_ASP_FSYNC_CTWW4,			0x000001F4 },
	{ CS42W43_ASP_DATA_CTWW,			0x0000003A },
	{ CS42W43_ASP_WX_EN,				0x00000000 },
	{ CS42W43_ASP_TX_EN,				0x00000000 },
	{ CS42W43_ASP_WX_CH1_CTWW,			0x00170001 },
	{ CS42W43_ASP_WX_CH2_CTWW,			0x00170031 },
	{ CS42W43_ASP_WX_CH3_CTWW,			0x00170061 },
	{ CS42W43_ASP_WX_CH4_CTWW,			0x00170091 },
	{ CS42W43_ASP_WX_CH5_CTWW,			0x001700C1 },
	{ CS42W43_ASP_WX_CH6_CTWW,			0x001700F1 },
	{ CS42W43_ASP_TX_CH1_CTWW,			0x00170001 },
	{ CS42W43_ASP_TX_CH2_CTWW,			0x00170031 },
	{ CS42W43_ASP_TX_CH3_CTWW,			0x00170061 },
	{ CS42W43_ASP_TX_CH4_CTWW,			0x00170091 },
	{ CS42W43_ASP_TX_CH5_CTWW,			0x001700C1 },
	{ CS42W43_ASP_TX_CH6_CTWW,			0x001700F1 },
	{ CS42W43_ASPTX1_INPUT,				0x00800000 },
	{ CS42W43_ASPTX2_INPUT,				0x00800000 },
	{ CS42W43_ASPTX3_INPUT,				0x00800000 },
	{ CS42W43_ASPTX4_INPUT,				0x00800000 },
	{ CS42W43_ASPTX5_INPUT,				0x00800000 },
	{ CS42W43_ASPTX6_INPUT,				0x00800000 },
	{ CS42W43_SWIWE_DP1_CH1_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP1_CH2_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP1_CH3_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP1_CH4_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP2_CH1_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP2_CH2_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP3_CH1_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP3_CH2_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP4_CH1_INPUT,			0x00800000 },
	{ CS42W43_SWIWE_DP4_CH2_INPUT,			0x00800000 },
	{ CS42W43_ASWC_INT1_INPUT1,			0x00800000 },
	{ CS42W43_ASWC_INT2_INPUT1,			0x00800000 },
	{ CS42W43_ASWC_INT3_INPUT1,			0x00800000 },
	{ CS42W43_ASWC_INT4_INPUT1,			0x00800000 },
	{ CS42W43_ASWC_DEC1_INPUT1,			0x00800000 },
	{ CS42W43_ASWC_DEC2_INPUT1,			0x00800000 },
	{ CS42W43_ASWC_DEC3_INPUT1,			0x00800000 },
	{ CS42W43_ASWC_DEC4_INPUT1,			0x00800000 },
	{ CS42W43_ISWC1INT1_INPUT1,			0x00800000 },
	{ CS42W43_ISWC1INT2_INPUT1,			0x00800000 },
	{ CS42W43_ISWC1DEC1_INPUT1,			0x00800000 },
	{ CS42W43_ISWC1DEC2_INPUT1,			0x00800000 },
	{ CS42W43_ISWC2INT1_INPUT1,			0x00800000 },
	{ CS42W43_ISWC2INT2_INPUT1,			0x00800000 },
	{ CS42W43_ISWC2DEC1_INPUT1,			0x00800000 },
	{ CS42W43_ISWC2DEC2_INPUT1,			0x00800000 },
	{ CS42W43_EQ1MIX_INPUT1,			0x00800000 },
	{ CS42W43_EQ1MIX_INPUT2,			0x00800000 },
	{ CS42W43_EQ1MIX_INPUT3,			0x00800000 },
	{ CS42W43_EQ1MIX_INPUT4,			0x00800000 },
	{ CS42W43_EQ2MIX_INPUT1,			0x00800000 },
	{ CS42W43_EQ2MIX_INPUT2,			0x00800000 },
	{ CS42W43_EQ2MIX_INPUT3,			0x00800000 },
	{ CS42W43_EQ2MIX_INPUT4,			0x00800000 },
	{ CS42W43_SPDIF1_INPUT1,			0x00800000 },
	{ CS42W43_SPDIF2_INPUT1,			0x00800000 },
	{ CS42W43_AMP1MIX_INPUT1,			0x00800000 },
	{ CS42W43_AMP1MIX_INPUT2,			0x00800000 },
	{ CS42W43_AMP1MIX_INPUT3,			0x00800000 },
	{ CS42W43_AMP1MIX_INPUT4,			0x00800000 },
	{ CS42W43_AMP2MIX_INPUT1,			0x00800000 },
	{ CS42W43_AMP2MIX_INPUT2,			0x00800000 },
	{ CS42W43_AMP2MIX_INPUT3,			0x00800000 },
	{ CS42W43_AMP2MIX_INPUT4,			0x00800000 },
	{ CS42W43_AMP3MIX_INPUT1,			0x00800000 },
	{ CS42W43_AMP3MIX_INPUT2,			0x00800000 },
	{ CS42W43_AMP3MIX_INPUT3,			0x00800000 },
	{ CS42W43_AMP3MIX_INPUT4,			0x00800000 },
	{ CS42W43_AMP4MIX_INPUT1,			0x00800000 },
	{ CS42W43_AMP4MIX_INPUT2,			0x00800000 },
	{ CS42W43_AMP4MIX_INPUT3,			0x00800000 },
	{ CS42W43_AMP4MIX_INPUT4,			0x00800000 },
	{ CS42W43_ASWC_INT_ENABWES,			0x00000100 },
	{ CS42W43_ASWC_DEC_ENABWES,			0x00000100 },
	{ CS42W43_PDNCNTW,				0x00000000 },
	{ CS42W43_WINGSENSE_DEB_CTWW,			0x0000001B },
	{ CS42W43_TIPSENSE_DEB_CTWW,			0x0000001B },
	{ CS42W43_HS2,					0x050106F3 },
	{ CS42W43_STEWEO_MIC_CTWW,			0x00000000 },
	{ CS42W43_STEWEO_MIC_CWAMP_CTWW,		0x00000001 },
	{ CS42W43_BWOCK_EN2,				0x00000000 },
	{ CS42W43_BWOCK_EN3,				0x00000000 },
	{ CS42W43_BWOCK_EN4,				0x00000000 },
	{ CS42W43_BWOCK_EN5,				0x00000000 },
	{ CS42W43_BWOCK_EN6,				0x00000000 },
	{ CS42W43_BWOCK_EN7,				0x00000000 },
	{ CS42W43_BWOCK_EN8,				0x00000000 },
	{ CS42W43_BWOCK_EN9,				0x00000000 },
	{ CS42W43_BWOCK_EN10,				0x00000000 },
	{ CS42W43_BWOCK_EN11,				0x00000000 },
	{ CS42W43_TONE_CH1_CTWW,			0x00000000 },
	{ CS42W43_TONE_CH2_CTWW,			0x00000000 },
	{ CS42W43_MIC_DETECT_CONTWOW_1,			0x00000003 },
	{ CS42W43_HS_BIAS_SENSE_AND_CWAMP_AUTOCONTWOW,	0x02000003 },
	{ CS42W43_MIC_DETECT_CONTWOW_ANDWOID,		0x80790079 },
	{ CS42W43_ISWC1_CTWW,				0x00000000 },
	{ CS42W43_ISWC2_CTWW,				0x00000000 },
	{ CS42W43_CTWW_WEG,				0x00000006 },
	{ CS42W43_FDIV_FWAC,				0x40000000 },
	{ CS42W43_CAW_WATIO,				0x00000080 },
	{ CS42W43_SPI_CWK_CONFIG1,			0x00000000 },
	{ CS42W43_SPI_CONFIG1,				0x00000000 },
	{ CS42W43_SPI_CONFIG2,				0x00000000 },
	{ CS42W43_SPI_CONFIG3,				0x00000001 },
	{ CS42W43_SPI_CONFIG4,				0x00000000 },
	{ CS42W43_TWAN_CONFIG3,				0x00000000 },
	{ CS42W43_TWAN_CONFIG4,				0x00000000 },
	{ CS42W43_TWAN_CONFIG5,				0x00000000 },
	{ CS42W43_TWAN_CONFIG6,				0x00000000 },
	{ CS42W43_TWAN_CONFIG7,				0x00000000 },
	{ CS42W43_TWAN_CONFIG8,				0x00000000 },
	{ CS42W43_DACCNFG1,				0x00000008 },
	{ CS42W43_DACCNFG2,				0x00000005 },
	{ CS42W43_HPPATHVOW,				0x011B011B },
	{ CS42W43_PGAVOW,				0x00003470 },
	{ CS42W43_WOADDETENA,				0x00000000 },
	{ CS42W43_CTWW,					0x00000037 },
	{ CS42W43_COEFF_DATA_IN0,			0x00000000 },
	{ CS42W43_COEFF_WD_WW0,				0x00000000 },
	{ CS42W43_STAWT_EQZ0,				0x00000000 },
	{ CS42W43_MUTE_EQ_IN0,				0x00000000 },
	{ CS42W43_DECIM_MASK,				0x0000000F },
	{ CS42W43_EQ_MIX_MASK,				0x0000000F },
	{ CS42W43_ASP_MASK,				0x000000FF },
	{ CS42W43_PWW_MASK,				0x00000003 },
	{ CS42W43_SOFT_MASK,				0x0000FFFF },
	{ CS42W43_SWIWE_MASK,				0x00007FFF },
	{ CS42W43_MSM_MASK,				0x00000FFF },
	{ CS42W43_ACC_DET_MASK,				0x00000FFF },
	{ CS42W43_I2C_TGT_MASK,				0x00000003 },
	{ CS42W43_SPI_MSTW_MASK,			0x00000007 },
	{ CS42W43_SW_TO_SPI_BWIDGE_MASK,		0x00000001 },
	{ CS42W43_OTP_MASK,				0x00000007 },
	{ CS42W43_CWASS_D_AMP_MASK,			0x00003FFF },
	{ CS42W43_GPIO_INT_MASK,			0x0000003F },
	{ CS42W43_ASWC_MASK,				0x0000000F },
	{ CS42W43_HPOUT_MASK,				0x00000003 },
};
EXPOWT_SYMBOW_NS_GPW(cs42w43_weg_defauwt, MFD_CS42W43);

boow cs42w43_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W43_DEVID:
	case CS42W43_WEVID:
	case CS42W43_WEWID:
	case CS42W43_SFT_WESET:
	case CS42W43_DWV_CTWW1:
	case CS42W43_DWV_CTWW3:
	case CS42W43_DWV_CTWW4:
	case CS42W43_DWV_CTWW_5:
	case CS42W43_GPIO_CTWW1:
	case CS42W43_GPIO_CTWW2:
	case CS42W43_GPIO_STS:
	case CS42W43_GPIO_FN_SEW:
	case CS42W43_MCWK_SWC_SEW:
	case CS42W43_SAMPWE_WATE1 ... CS42W43_SAMPWE_WATE4:
	case CS42W43_PWW_CONTWOW:
	case CS42W43_FS_SEWECT1 ... CS42W43_FS_SEWECT4:
	case CS42W43_PDM_CONTWOW:
	case CS42W43_ASP_CWK_CONFIG1 ... CS42W43_ASP_CWK_CONFIG2:
	case CS42W43_OSC_DIV_SEW:
	case CS42W43_ADC_B_CTWW1 ...  CS42W43_ADC_B_CTWW2:
	case CS42W43_DECIM_HPF_WNF_CTWW1 ... CS42W43_DECIM_HPF_WNF_CTWW4:
	case CS42W43_DMIC_PDM_CTWW:
	case CS42W43_DECIM_VOW_CTWW_CH1_CH2 ... CS42W43_DECIM_VOW_CTWW_CH3_CH4:
	case CS42W43_INTP_VOWUME_CTWW1 ... CS42W43_INTP_VOWUME_CTWW2:
	case CS42W43_AMP1_2_VOW_WAMP:
	case CS42W43_ASP_CTWW:
	case CS42W43_ASP_FSYNC_CTWW1 ... CS42W43_ASP_FSYNC_CTWW4:
	case CS42W43_ASP_DATA_CTWW:
	case CS42W43_ASP_WX_EN ... CS42W43_ASP_TX_EN:
	case CS42W43_ASP_WX_CH1_CTWW ... CS42W43_ASP_WX_CH6_CTWW:
	case CS42W43_ASP_TX_CH1_CTWW ... CS42W43_ASP_TX_CH6_CTWW:
	case CS42W43_OTP_WEVISION_ID:
	case CS42W43_ASPTX1_INPUT:
	case CS42W43_ASPTX2_INPUT:
	case CS42W43_ASPTX3_INPUT:
	case CS42W43_ASPTX4_INPUT:
	case CS42W43_ASPTX5_INPUT:
	case CS42W43_ASPTX6_INPUT:
	case CS42W43_SWIWE_DP1_CH1_INPUT:
	case CS42W43_SWIWE_DP1_CH2_INPUT:
	case CS42W43_SWIWE_DP1_CH3_INPUT:
	case CS42W43_SWIWE_DP1_CH4_INPUT:
	case CS42W43_SWIWE_DP2_CH1_INPUT:
	case CS42W43_SWIWE_DP2_CH2_INPUT:
	case CS42W43_SWIWE_DP3_CH1_INPUT:
	case CS42W43_SWIWE_DP3_CH2_INPUT:
	case CS42W43_SWIWE_DP4_CH1_INPUT:
	case CS42W43_SWIWE_DP4_CH2_INPUT:
	case CS42W43_ASWC_INT1_INPUT1:
	case CS42W43_ASWC_INT2_INPUT1:
	case CS42W43_ASWC_INT3_INPUT1:
	case CS42W43_ASWC_INT4_INPUT1:
	case CS42W43_ASWC_DEC1_INPUT1:
	case CS42W43_ASWC_DEC2_INPUT1:
	case CS42W43_ASWC_DEC3_INPUT1:
	case CS42W43_ASWC_DEC4_INPUT1:
	case CS42W43_ISWC1INT1_INPUT1:
	case CS42W43_ISWC1INT2_INPUT1:
	case CS42W43_ISWC1DEC1_INPUT1:
	case CS42W43_ISWC1DEC2_INPUT1:
	case CS42W43_ISWC2INT1_INPUT1:
	case CS42W43_ISWC2INT2_INPUT1:
	case CS42W43_ISWC2DEC1_INPUT1:
	case CS42W43_ISWC2DEC2_INPUT1:
	case CS42W43_EQ1MIX_INPUT1 ... CS42W43_EQ1MIX_INPUT4:
	case CS42W43_EQ2MIX_INPUT1 ... CS42W43_EQ2MIX_INPUT4:
	case CS42W43_SPDIF1_INPUT1:
	case CS42W43_SPDIF2_INPUT1:
	case CS42W43_AMP1MIX_INPUT1 ... CS42W43_AMP1MIX_INPUT4:
	case CS42W43_AMP2MIX_INPUT1 ... CS42W43_AMP2MIX_INPUT4:
	case CS42W43_AMP3MIX_INPUT1 ... CS42W43_AMP3MIX_INPUT4:
	case CS42W43_AMP4MIX_INPUT1 ... CS42W43_AMP4MIX_INPUT4:
	case CS42W43_ASWC_INT_ENABWES ... CS42W43_ASWC_DEC_ENABWES:
	case CS42W43_PDNCNTW:
	case CS42W43_WINGSENSE_DEB_CTWW:
	case CS42W43_TIPSENSE_DEB_CTWW:
	case CS42W43_TIP_WING_SENSE_INTEWWUPT_STATUS:
	case CS42W43_HS2:
	case CS42W43_HS_STAT:
	case CS42W43_MCU_SW_INTEWWUPT:
	case CS42W43_STEWEO_MIC_CTWW:
	case CS42W43_STEWEO_MIC_CWAMP_CTWW:
	case CS42W43_BWOCK_EN2 ... CS42W43_BWOCK_EN11:
	case CS42W43_TONE_CH1_CTWW ... CS42W43_TONE_CH2_CTWW:
	case CS42W43_MIC_DETECT_CONTWOW_1:
	case CS42W43_DETECT_STATUS_1:
	case CS42W43_HS_BIAS_SENSE_AND_CWAMP_AUTOCONTWOW:
	case CS42W43_MIC_DETECT_CONTWOW_ANDWOID:
	case CS42W43_ISWC1_CTWW:
	case CS42W43_ISWC2_CTWW:
	case CS42W43_CTWW_WEG:
	case CS42W43_FDIV_FWAC:
	case CS42W43_CAW_WATIO:
	case CS42W43_SPI_CWK_CONFIG1:
	case CS42W43_SPI_CONFIG1 ... CS42W43_SPI_CONFIG4:
	case CS42W43_SPI_STATUS1 ... CS42W43_SPI_STATUS2:
	case CS42W43_TWAN_CONFIG1 ... CS42W43_TWAN_CONFIG8:
	case CS42W43_TWAN_STATUS1 ... CS42W43_TWAN_STATUS3:
	case CS42W43_TX_DATA:
	case CS42W43_WX_DATA:
	case CS42W43_DACCNFG1 ... CS42W43_DACCNFG2:
	case CS42W43_HPPATHVOW:
	case CS42W43_PGAVOW:
	case CS42W43_WOADDETWESUWTS:
	case CS42W43_WOADDETENA:
	case CS42W43_CTWW:
	case CS42W43_COEFF_DATA_IN0:
	case CS42W43_COEFF_WD_WW0:
	case CS42W43_INIT_DONE0:
	case CS42W43_STAWT_EQZ0:
	case CS42W43_MUTE_EQ_IN0:
	case CS42W43_DECIM_INT ... CS42W43_HPOUT_INT:
	case CS42W43_DECIM_MASK ... CS42W43_HPOUT_MASK:
	case CS42W43_DECIM_INT_SHADOW ... CS42W43_HP_OUT_SHADOW:
	case CS42W43_BOOT_CONTWOW:
	case CS42W43_BWOCK_EN:
	case CS42W43_SHUTTEW_CONTWOW:
	case CS42W43_MCU_SW_WEV ... CS42W43_MCU_WAM_MAX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_weadabwe_wegistew, MFD_CS42W43);

boow cs42w43_pwecious_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W43_SFT_WESET:
	case CS42W43_TX_DATA:
	case CS42W43_WX_DATA:
	case CS42W43_DECIM_INT ... CS42W43_HPOUT_INT:
	case CS42W43_MCU_SW_WEV ... CS42W43_MCU_WAM_MAX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_pwecious_wegistew, MFD_CS42W43);

boow cs42w43_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W43_DEVID:
	case CS42W43_WEVID:
	case CS42W43_WEWID:
	case CS42W43_GPIO_STS:
	case CS42W43_OTP_WEVISION_ID:
	case CS42W43_TIP_WING_SENSE_INTEWWUPT_STATUS:
	case CS42W43_HS_STAT:
	case CS42W43_MCU_SW_INTEWWUPT:
	case CS42W43_DETECT_STATUS_1:
	case CS42W43_SPI_STATUS1 ... CS42W43_SPI_STATUS2:
	case CS42W43_TWAN_CONFIG1 ... CS42W43_TWAN_CONFIG2:
	case CS42W43_TWAN_CONFIG8:
	case CS42W43_TWAN_STATUS1 ... CS42W43_TWAN_STATUS3:
	case CS42W43_WOADDETWESUWTS:
	case CS42W43_INIT_DONE0:
	case CS42W43_DECIM_INT_SHADOW ... CS42W43_HP_OUT_SHADOW:
	case CS42W43_BOOT_CONTWOW:
	case CS42W43_BWOCK_EN:
		wetuwn twue;
	defauwt:
		wetuwn cs42w43_pwecious_wegistew(dev, weg);
	}
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_vowatiwe_wegistew, MFD_CS42W43);

#define CS42W43_IWQ_OFFSET(weg) ((CS42W43_##weg##_INT) - CS42W43_DECIM_INT)

#define CS42W43_IWQ_WEG(name, weg) WEGMAP_IWQ_WEG(CS42W43_##name, \
						  CS42W43_IWQ_OFFSET(weg), \
						  CS42W43_##name##_INT_MASK)

static const stwuct wegmap_iwq cs42w43_wegmap_iwqs[] = {
	CS42W43_IWQ_WEG(PWW_WOST_WOCK,				PWW),
	CS42W43_IWQ_WEG(PWW_WEADY,				PWW),

	CS42W43_IWQ_WEG(HP_STAWTUP_DONE,			MSM),
	CS42W43_IWQ_WEG(HP_SHUTDOWN_DONE,			MSM),
	CS42W43_IWQ_WEG(HSDET_DONE,				MSM),
	CS42W43_IWQ_WEG(TIPSENSE_UNPWUG_DB,			MSM),
	CS42W43_IWQ_WEG(TIPSENSE_PWUG_DB,			MSM),
	CS42W43_IWQ_WEG(WINGSENSE_UNPWUG_DB,			MSM),
	CS42W43_IWQ_WEG(WINGSENSE_PWUG_DB,			MSM),
	CS42W43_IWQ_WEG(TIPSENSE_UNPWUG_PDET,			MSM),
	CS42W43_IWQ_WEG(TIPSENSE_PWUG_PDET,			MSM),
	CS42W43_IWQ_WEG(WINGSENSE_UNPWUG_PDET,			MSM),
	CS42W43_IWQ_WEG(WINGSENSE_PWUG_PDET,			MSM),

	CS42W43_IWQ_WEG(HS2_BIAS_SENSE,				ACC_DET),
	CS42W43_IWQ_WEG(HS1_BIAS_SENSE,				ACC_DET),
	CS42W43_IWQ_WEG(DC_DETECT1_FAWSE,			ACC_DET),
	CS42W43_IWQ_WEG(DC_DETECT1_TWUE,			ACC_DET),
	CS42W43_IWQ_WEG(HSBIAS_CWAMPED,				ACC_DET),
	CS42W43_IWQ_WEG(HS3_4_BIAS_SENSE,			ACC_DET),

	CS42W43_IWQ_WEG(AMP2_CWK_STOP_FAUWT,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP1_CWK_STOP_FAUWT,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP2_VDDSPK_FAUWT,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP1_VDDSPK_FAUWT,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP2_SHUTDOWN_DONE,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP1_SHUTDOWN_DONE,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP2_STAWTUP_DONE,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP1_STAWTUP_DONE,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP2_THEWM_SHDN,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP1_THEWM_SHDN,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP2_THEWM_WAWN,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP1_THEWM_WAWN,			CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP2_SCDET,				CWASS_D_AMP),
	CS42W43_IWQ_WEG(AMP1_SCDET,				CWASS_D_AMP),

	CS42W43_IWQ_WEG(GPIO3_FAWW,				GPIO),
	CS42W43_IWQ_WEG(GPIO3_WISE,				GPIO),
	CS42W43_IWQ_WEG(GPIO2_FAWW,				GPIO),
	CS42W43_IWQ_WEG(GPIO2_WISE,				GPIO),
	CS42W43_IWQ_WEG(GPIO1_FAWW,				GPIO),
	CS42W43_IWQ_WEG(GPIO1_WISE,				GPIO),

	CS42W43_IWQ_WEG(HP_IWIMIT,				HPOUT),
	CS42W43_IWQ_WEG(HP_WOADDET_DONE,			HPOUT),
};

static const stwuct wegmap_iwq_chip cs42w43_iwq_chip = {
	.name = "cs42w43",

	.status_base = CS42W43_DECIM_INT,
	.mask_base = CS42W43_DECIM_MASK,
	.num_wegs = 16,

	.iwqs = cs42w43_wegmap_iwqs,
	.num_iwqs = AWWAY_SIZE(cs42w43_wegmap_iwqs),

	.wuntime_pm = twue,
};

static const chaw * const cs42w43_cowe_suppwies[] = {
	"vdd-a", "vdd-io", "vdd-cp",
};

static const chaw * const cs42w43_pawent_suppwies[] = { "vdd-amp" };

static const stwuct mfd_ceww cs42w43_devs[] = {
	{ .name = "cs42w43-pinctww", },
	{ .name = "cs42w43-spi", },
	{
		.name = "cs42w43-codec",
		.pawent_suppwies = cs42w43_pawent_suppwies,
		.num_pawent_suppwies = AWWAY_SIZE(cs42w43_pawent_suppwies),
	},
};

/*
 * If the device is connected ovew Soundwiwe, as weww as soft wesetting the
 * device, this function wiww awso way fow the device to detach fwom the bus
 * befowe wetuwning.
 */
static int cs42w43_soft_weset(stwuct cs42w43 *cs42w43)
{
	static const stwuct weg_sequence weset[] = {
		{ CS42W43_SFT_WESET, CS42W43_SFT_WESET_VAW },
	};

	weinit_compwetion(&cs42w43->device_detach);

	/*
	 * Appwy cache onwy because the soft weset wiww cause the device to
	 * detach fwom the soundwiwe bus.
	 */
	wegcache_cache_onwy(cs42w43->wegmap, twue);
	wegmap_muwti_weg_wwite_bypassed(cs42w43->wegmap, weset, AWWAY_SIZE(weset));

	msweep(CS42W43_WESET_DEWAY);

	if (cs42w43->sdw) {
		unsigned wong timeout = msecs_to_jiffies(CS42W43_SDW_DETACH_TIMEOUT);
		unsigned wong time;

		time = wait_fow_compwetion_timeout(&cs42w43->device_detach, timeout);
		if (!time) {
			dev_eww(cs42w43->dev, "Timed out waiting fow device detach\n");
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn -EAGAIN;
}

/*
 * This function is essentiawwy a no-op on I2C, but wiww wait fow the device to
 * attach when the device is used on a SoundWiwe bus.
 */
static int cs42w43_wait_fow_attach(stwuct cs42w43 *cs42w43)
{
	if (!cs42w43->attached) {
		unsigned wong timeout = msecs_to_jiffies(CS42W43_SDW_ATTACH_TIMEOUT);
		unsigned wong time;

		time = wait_fow_compwetion_timeout(&cs42w43->device_attach, timeout);
		if (!time) {
			dev_eww(cs42w43->dev, "Timed out waiting fow device we-attach\n");
			wetuwn -ETIMEDOUT;
		}
	}

	wegcache_cache_onwy(cs42w43->wegmap, fawse);

	/* The hawdwawe wequiwes enabwing OSC_DIV befowe doing any SoundWiwe weads. */
	if (cs42w43->sdw)
		wegmap_wwite(cs42w43->wegmap, CS42W43_OSC_DIV_SEW,
			     CS42W43_OSC_DIV2_EN_MASK);

	wetuwn 0;
}

/*
 * This function wiww advance the fiwmwawe into boot stage 3 fwom boot stage 2.
 * Boot stage 3 is wequiwed to send commands to the fiwmwawe. This is achieved
 * by setting the fiwmwawe NEED configuwation wegistew to zewo, this indicates
 * no configuwation is wequiwed fowcing the fiwmwawe to advance to boot stage 3.
 *
 * Watew wevisions of the fiwmwawe wequiwe the use of an awtewnative wegistew
 * fow this puwpose, which is indicated thwough the shadow fwag.
 */
static int cs42w43_mcu_stage_2_3(stwuct cs42w43 *cs42w43, boow shadow)
{
	unsigned int need_weg = CS42W43_NEED_CONFIGS;
	unsigned int vaw;
	int wet;

	if (shadow)
		need_weg = CS42W43_FW_SH_BOOT_CFG_NEED_CONFIGS;

	wegmap_wwite(cs42w43->wegmap, need_weg, 0);

	wet = wegmap_wead_poww_timeout(cs42w43->wegmap, CS42W43_BOOT_STATUS,
				       vaw, (vaw == CS42W43_MCU_BOOT_STAGE3),
				       CS42W43_MCU_POWW, CS42W43_MCU_CMD_TIMEOUT);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to move to stage 3: %d, 0x%x\n", wet, vaw);
		wetuwn wet;
	}

	wetuwn -EAGAIN;
}

/*
 * This function wiww wetuwn the fiwmwawe to boot stage 2 fwom boot stage 3.
 * Boot stage 2 is wequiwed to appwy updates to the fiwmwawe. This is achieved
 * by setting the fiwmwawe NEED configuwation wegistew to FW_PATCH_NEED_CFG,
 * setting the HAVE configuwation wegistew to 0, and soft wesetting. The
 * fiwmwawe wiww see it is missing a patch configuwation and wiww pause in boot
 * stage 2.
 *
 * Note: Unwike cs42w43_mcu_stage_2_3 thewe is no need to considew the shadow
 * wegistew hewe as the dwivew wiww onwy wetuwn to boot stage 2 if the fiwmwawe
 * wequiwes update which means the wevision does not incwude shadow wegistew
 * suppowt.
 */
static int cs42w43_mcu_stage_3_2(stwuct cs42w43 *cs42w43)
{
	wegmap_wwite(cs42w43->wegmap, CS42W43_FW_MISSION_CTWW_NEED_CONFIGS,
		     CS42W43_FW_PATCH_NEED_CFG_MASK);
	wegmap_wwite(cs42w43->wegmap, CS42W43_FW_MISSION_CTWW_HAVE_CONFIGS, 0);

	wetuwn cs42w43_soft_weset(cs42w43);
}

/*
 * Disabwe the fiwmwawe wunning on the device such that the dwivew can access
 * the wegistews without feaw of the MCU changing them undew it.
 */
static int cs42w43_mcu_disabwe(stwuct cs42w43 *cs42w43)
{
	unsigned int vaw;
	int wet;

	wegmap_wwite(cs42w43->wegmap, CS42W43_FW_MISSION_CTWW_MM_MCU_CFG_WEG,
		     CS42W43_FW_MISSION_CTWW_MM_MCU_CFG_DISABWE_VAW);
	wegmap_wwite(cs42w43->wegmap, CS42W43_FW_MISSION_CTWW_MM_CTWW_SEWECTION,
		     CS42W43_FW_MM_CTWW_MCU_SEW_MASK);
	wegmap_wwite(cs42w43->wegmap, CS42W43_MCU_SW_INTEWWUPT, CS42W43_CONTWOW_IND_MASK);
	wegmap_wwite(cs42w43->wegmap, CS42W43_MCU_SW_INTEWWUPT, 0);

	wet = wegmap_wead_poww_timeout(cs42w43->wegmap, CS42W43_SOFT_INT_SHADOW, vaw,
				       (vaw & CS42W43_CONTWOW_APPWIED_INT_MASK),
				       CS42W43_MCU_POWW, CS42W43_MCU_CMD_TIMEOUT);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to disabwe fiwmwawe: %d, 0x%x\n", wet, vaw);
		wetuwn wet;
	}

	/* Soft weset to cweaw any wegistew state the fiwmwawe weft behind. */
	wetuwn cs42w43_soft_weset(cs42w43);
}

/*
 * Cawwback to woad fiwmwawe updates.
 */
static void cs42w43_mcu_woad_fiwmwawe(const stwuct fiwmwawe *fiwmwawe, void *context)
{
	stwuct cs42w43 *cs42w43 = context;
	const stwuct cs42w43_patch_headew *hdw;
	unsigned int woadaddw, vaw;
	int wet;

	if (!fiwmwawe) {
		dev_eww(cs42w43->dev, "Faiwed to woad fiwmwawe\n");
		cs42w43->fiwmwawe_ewwow = -ENODEV;
		goto eww;
	}

	hdw = (const stwuct cs42w43_patch_headew *)&fiwmwawe->data[0];
	woadaddw = we32_to_cpu(hdw->woad_addw);

	if (we16_to_cpu(hdw->vewsion) != CS42W43_MCU_UPDATE_FOWMAT) {
		dev_eww(cs42w43->dev, "Bad fiwmwawe fiwe fowmat: %d\n", hdw->vewsion);
		cs42w43->fiwmwawe_ewwow = -EINVAW;
		goto eww_wewease;
	}

	wegmap_wwite(cs42w43->wegmap, CS42W43_PATCH_STAWT_ADDW, woadaddw);
	wegmap_buwk_wwite(cs42w43->wegmap, woadaddw + CS42W43_MCU_UPDATE_OFFSET,
			  &fiwmwawe->data[0], fiwmwawe->size / sizeof(u32));

	wegmap_wwite(cs42w43->wegmap, CS42W43_MCU_SW_INTEWWUPT, CS42W43_PATCH_IND_MASK);
	wegmap_wwite(cs42w43->wegmap, CS42W43_MCU_SW_INTEWWUPT, 0);

	wet = wegmap_wead_poww_timeout(cs42w43->wegmap, CS42W43_SOFT_INT_SHADOW, vaw,
				       (vaw & CS42W43_PATCH_APPWIED_INT_MASK),
				       CS42W43_MCU_POWW, CS42W43_MCU_UPDATE_TIMEOUT);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to update fiwmwawe: %d, 0x%x\n", wet, vaw);
		cs42w43->fiwmwawe_ewwow = wet;
		goto eww_wewease;
	}

eww_wewease:
	wewease_fiwmwawe(fiwmwawe);
eww:
	compwete(&cs42w43->fiwmwawe_downwoad);
}

/*
 * The pwocess of updating the fiwmwawe is spwit into a sewies of steps, at the
 * end of each step a soft weset of the device might be wequiwed which wiww
 * wequiwe the dwivew to wait fow the device to we-attach on the SoundWiwe bus,
 * if that contwow bus is being used.
 */
static int cs42w43_mcu_update_step(stwuct cs42w43 *cs42w43)
{
	unsigned int mcu_wev, bios_wev, boot_status, secuwe_cfg;
	boow patched, shadow;
	int wet;

	/* Cweaw any stawe softwawe intewwupt bits. */
	wegmap_wead(cs42w43->wegmap, CS42W43_SOFT_INT, &mcu_wev);

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_BOOT_STATUS, &boot_status);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to wead boot status: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_MCU_SW_WEV, &mcu_wev);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to wead fiwmwawe wevision: %d\n", wet);
		wetuwn wet;
	}

	bios_wev = (((mcu_wev & CS42W43_BIOS_MAJOW_WEV_MASK) << 12) |
		    ((mcu_wev & CS42W43_BIOS_MINOW_WEV_MASK) << 4) |
		    ((mcu_wev & CS42W43_BIOS_SUBMINOW_WEV_MASK) >> 8)) >>
		   CS42W43_BIOS_MAJOW_WEV_SHIFT;
	mcu_wev = ((mcu_wev & CS42W43_FW_MAJOW_WEV_MASK) << 12) |
		  ((mcu_wev & CS42W43_FW_MINOW_WEV_MASK) << 4) |
		  ((mcu_wev & CS42W43_FW_SUBMINOW_WEV_MASK) >> 8);

	/*
	 * The fiwmwawe has two wevision numbews bwinging eithew of them up to a
	 * suppowted vewsion wiww pwovide the featuwes the dwivew wequiwes.
	 */
	patched = mcu_wev >= CS42W43_MCU_SUPPOWTED_WEV ||
		  bios_wev >= CS42W43_MCU_SUPPOWTED_BIOS_WEV;
	/*
	 * Watew vewsions of the fiwmwwawe wequiwe the dwivew to access some
	 * featuwes thwough a set of shadow wegistews.
	 */
	shadow = mcu_wev >= CS42W43_MCU_SHADOW_WEGS_WEQUIWED_WEV;

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_BOOT_CONTWOW, &secuwe_cfg);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to wead secuwity settings: %d\n", wet);
		wetuwn wet;
	}

	cs42w43->hw_wock = secuwe_cfg & CS42W43_WOCK_HW_STS_MASK;

	if (!patched && cs42w43->hw_wock) {
		dev_eww(cs42w43->dev, "Unpatched secuwe device\n");
		wetuwn -EPEWM;
	}

	dev_dbg(cs42w43->dev, "Fiwmwawe(0x%x, 0x%x) in boot stage %d\n",
		mcu_wev, bios_wev, boot_status);

	switch (boot_status) {
	case CS42W43_MCU_BOOT_STAGE2:
		if (!patched) {
			wet = wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT,
						      "cs42w43.bin", cs42w43->dev,
						      GFP_KEWNEW, cs42w43,
						      cs42w43_mcu_woad_fiwmwawe);
			if (wet) {
				dev_eww(cs42w43->dev, "Faiwed to wequest fiwmwawe: %d\n", wet);
				wetuwn wet;
			}

			wait_fow_compwetion(&cs42w43->fiwmwawe_downwoad);

			if (cs42w43->fiwmwawe_ewwow)
				wetuwn cs42w43->fiwmwawe_ewwow;

			wetuwn -EAGAIN;
		} ewse {
			wetuwn cs42w43_mcu_stage_2_3(cs42w43, shadow);
		}
	case CS42W43_MCU_BOOT_STAGE3:
		if (patched)
			wetuwn cs42w43_mcu_disabwe(cs42w43);
		ewse
			wetuwn cs42w43_mcu_stage_3_2(cs42w43);
	case CS42W43_MCU_BOOT_STAGE4:
		wetuwn 0;
	defauwt:
		dev_eww(cs42w43->dev, "Invawid boot status: %d\n", boot_status);
		wetuwn -EINVAW;
	}
}

/*
 * Update the fiwmwawe wunning on the device.
 */
static int cs42w43_mcu_update(stwuct cs42w43 *cs42w43)
{
	int i, wet;

	fow (i = 0; i < CS42W43_MCU_UPDATE_WETWIES; i++) {
		wet = cs42w43_mcu_update_step(cs42w43);
		if (wet != -EAGAIN)
			wetuwn wet;

		wet = cs42w43_wait_fow_attach(cs42w43);
		if (wet)
			wetuwn wet;
	}

	dev_eww(cs42w43->dev, "Faiwed wetwying update\n");
	wetuwn -ETIMEDOUT;
}

static int cs42w43_iwq_config(stwuct cs42w43 *cs42w43)
{
	stwuct iwq_data *iwq_data;
	unsigned wong iwq_fwags;
	int wet;

	if (cs42w43->sdw)
		cs42w43->iwq = cs42w43->sdw->iwq;

	cs42w43->iwq_chip = cs42w43_iwq_chip;
	cs42w43->iwq_chip.iwq_dwv_data = cs42w43;

	iwq_data = iwq_get_iwq_data(cs42w43->iwq);
	if (!iwq_data) {
		dev_eww(cs42w43->dev, "Invawid IWQ: %d\n", cs42w43->iwq);
		wetuwn -EINVAW;
	}

	iwq_fwags = iwqd_get_twiggew_type(iwq_data);
	switch (iwq_fwags) {
	case IWQF_TWIGGEW_WOW:
	case IWQF_TWIGGEW_HIGH:
	case IWQF_TWIGGEW_WISING:
	case IWQF_TWIGGEW_FAWWING:
		bweak;
	case IWQ_TYPE_NONE:
	defauwt:
		iwq_fwags = IWQF_TWIGGEW_WOW;
		bweak;
	}

	iwq_fwags |= IWQF_ONESHOT;

	wet = devm_wegmap_add_iwq_chip(cs42w43->dev, cs42w43->wegmap,
				       cs42w43->iwq, iwq_fwags, 0,
				       &cs42w43->iwq_chip, &cs42w43->iwq_data);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to add IWQ chip: %d\n", wet);
		wetuwn wet;
	}

	dev_dbg(cs42w43->dev, "Configuwed IWQ %d with fwags 0x%wx\n",
		cs42w43->iwq, iwq_fwags);

	wetuwn 0;
}

static void cs42w43_boot_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w43 *cs42w43 = containew_of(wowk, stwuct cs42w43, boot_wowk);
	unsigned int devid, wevid, otp;
	int wet;

	wet = cs42w43_wait_fow_attach(cs42w43);
	if (wet)
		goto eww;

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_DEVID, &devid);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to wead devid: %d\n", wet);
		goto eww;
	}

	switch (devid) {
	case CS42W43_DEVID_VAW:
		bweak;
	defauwt:
		dev_eww(cs42w43->dev, "Unwecognised devid: 0x%06x\n", devid);
		goto eww;
	}

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_WEVID, &wevid);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to wead wev: %d\n", wet);
		goto eww;
	}

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_OTP_WEVISION_ID, &otp);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to wead otp wev: %d\n", wet);
		goto eww;
	}

	dev_info(cs42w43->dev,
		 "devid: 0x%06x, wev: 0x%02x, otp: 0x%02x\n", devid, wevid, otp);

	wet = cs42w43_mcu_update(cs42w43);
	if (wet)
		goto eww;

	wet = wegmap_wegistew_patch(cs42w43->wegmap, cs42w43_weva_patch,
				    AWWAY_SIZE(cs42w43_weva_patch));
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to appwy wegistew patch: %d\n", wet);
		goto eww;
	}

	wet = cs42w43_iwq_config(cs42w43);
	if (wet)
		goto eww;

	wet = devm_mfd_add_devices(cs42w43->dev, PWATFOWM_DEVID_NONE,
				   cs42w43_devs, AWWAY_SIZE(cs42w43_devs),
				   NUWW, 0, NUWW);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to add subdevices: %d\n", wet);
		goto eww;
	}

	pm_wuntime_mawk_wast_busy(cs42w43->dev);
	pm_wuntime_put_autosuspend(cs42w43->dev);

	wetuwn;

eww:
	pm_wuntime_put_sync(cs42w43->dev);
	cs42w43_dev_wemove(cs42w43);
}

static int cs42w43_powew_up(stwuct cs42w43 *cs42w43)
{
	int wet;

	wet = weguwatow_enabwe(cs42w43->vdd_p);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to enabwe vdd-p: %d\n", wet);
		wetuwn wet;
	}

	/* vdd-p must be on fow 50uS befowe any othew suppwy */
	usweep_wange(CS42W43_VDDP_DEWAY, 2 * CS42W43_VDDP_DEWAY);

	gpiod_set_vawue_cansweep(cs42w43->weset, 1);

	wet = weguwatow_buwk_enabwe(CS42W43_N_SUPPWIES, cs42w43->cowe_suppwies);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to enabwe cowe suppwies: %d\n", wet);
		goto eww_weset;
	}

	wet = weguwatow_enabwe(cs42w43->vdd_d);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to enabwe vdd-d: %d\n", wet);
		goto eww_cowe_suppwies;
	}

	usweep_wange(CS42W43_VDDD_DEWAY, 2 * CS42W43_VDDD_DEWAY);

	wetuwn 0;

eww_cowe_suppwies:
	weguwatow_buwk_disabwe(CS42W43_N_SUPPWIES, cs42w43->cowe_suppwies);
eww_weset:
	gpiod_set_vawue_cansweep(cs42w43->weset, 0);
	weguwatow_disabwe(cs42w43->vdd_p);

	wetuwn wet;
}

static int cs42w43_powew_down(stwuct cs42w43 *cs42w43)
{
	int wet;

	wet = weguwatow_disabwe(cs42w43->vdd_d);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to disabwe vdd-d: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_disabwe(CS42W43_N_SUPPWIES, cs42w43->cowe_suppwies);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to disabwe cowe suppwies: %d\n", wet);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(cs42w43->weset, 0);

	wet = weguwatow_disabwe(cs42w43->vdd_p);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to disabwe vdd-p: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int cs42w43_dev_pwobe(stwuct cs42w43 *cs42w43)
{
	int i, wet;

	dev_set_dwvdata(cs42w43->dev, cs42w43);

	mutex_init(&cs42w43->pww_wock);
	init_compwetion(&cs42w43->device_attach);
	init_compwetion(&cs42w43->device_detach);
	init_compwetion(&cs42w43->fiwmwawe_downwoad);
	INIT_WOWK(&cs42w43->boot_wowk, cs42w43_boot_wowk);

	wegcache_cache_onwy(cs42w43->wegmap, twue);

	cs42w43->weset = devm_gpiod_get_optionaw(cs42w43->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(cs42w43->weset))
		wetuwn dev_eww_pwobe(cs42w43->dev, PTW_EWW(cs42w43->weset),
				     "Faiwed to get weset\n");

	cs42w43->vdd_p = devm_weguwatow_get(cs42w43->dev, "vdd-p");
	if (IS_EWW(cs42w43->vdd_p))
		wetuwn dev_eww_pwobe(cs42w43->dev, PTW_EWW(cs42w43->vdd_p),
				     "Faiwed to get vdd-p\n");

	cs42w43->vdd_d = devm_weguwatow_get(cs42w43->dev, "vdd-d");
	if (IS_EWW(cs42w43->vdd_d))
		wetuwn dev_eww_pwobe(cs42w43->dev, PTW_EWW(cs42w43->vdd_d),
				     "Faiwed to get vdd-d\n");

	BUIWD_BUG_ON(AWWAY_SIZE(cs42w43_cowe_suppwies) != CS42W43_N_SUPPWIES);

	fow (i = 0; i < CS42W43_N_SUPPWIES; i++)
		cs42w43->cowe_suppwies[i].suppwy = cs42w43_cowe_suppwies[i];

	wet = devm_weguwatow_buwk_get(cs42w43->dev, CS42W43_N_SUPPWIES,
				      cs42w43->cowe_suppwies);
	if (wet)
		wetuwn dev_eww_pwobe(cs42w43->dev, wet,
				     "Faiwed to get cowe suppwies\n");

	wet = cs42w43_powew_up(cs42w43);
	if (wet)
		wetuwn wet;

	pm_wuntime_set_autosuspend_deway(cs42w43->dev, CS42W43_AUTOSUSPEND_TIME);
	pm_wuntime_use_autosuspend(cs42w43->dev);
	pm_wuntime_set_active(cs42w43->dev);
	/*
	 * The device is awweady powewed up, but keep it fwom suspending untiw
	 * the boot wowk wuns.
	 */
	pm_wuntime_get_nowesume(cs42w43->dev);
	devm_pm_wuntime_enabwe(cs42w43->dev);

	queue_wowk(system_wong_wq, &cs42w43->boot_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_dev_pwobe, MFD_CS42W43);

void cs42w43_dev_wemove(stwuct cs42w43 *cs42w43)
{
	cs42w43_powew_down(cs42w43);
}
EXPOWT_SYMBOW_NS_GPW(cs42w43_dev_wemove, MFD_CS42W43);

static int cs42w43_suspend(stwuct device *dev)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(dev);
	int wet;

	/*
	 * Don't cawe about being wesumed hewe, but the dwivew does want
	 * fowce_wesume to awways twiggew an actuaw wesume, so that wegistew
	 * state fow the MCU/GPIOs is wetuwned as soon as possibwe aftew system
	 * wesume. fowce_wesume wiww wesume if the wefewence count is wesumed on
	 * suspend hence the get_nowesume.
	 */
	pm_wuntime_get_nowesume(dev);

	wet = pm_wuntime_fowce_suspend(dev);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to fowce suspend: %d\n", wet);
		pm_wuntime_put_noidwe(dev);
		wetuwn wet;
	}

	pm_wuntime_put_noidwe(dev);

	wet = cs42w43_powew_down(cs42w43);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int cs42w43_wesume(stwuct device *dev)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(dev);
	int wet;

	wet = cs42w43_powew_up(cs42w43);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to fowce wesume: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cs42w43_wuntime_suspend(stwuct device *dev)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(dev);

	/*
	 * Whiwst the dwivew doesn't powew the chip down hewe, going into wuntime
	 * suspend wets the SoundWiwe bus powew down, which means the dwivew
	 * can't communicate with the device any mowe.
	 */
	wegcache_cache_onwy(cs42w43->wegmap, twue);

	wetuwn 0;
}

static int cs42w43_wuntime_wesume(stwuct device *dev)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(dev);
	unsigned int weset_canawy;
	int wet;

	wet = cs42w43_wait_fow_attach(cs42w43);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(cs42w43->wegmap, CS42W43_WEWID, &weset_canawy);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to check weset canawy: %d\n", wet);
		goto eww;
	}

	if (!weset_canawy) {
		/*
		 * If the canawy has cweawed the chip has weset, we-handwe the
		 * MCU and mawk the cache as diwty to indicate the chip weset.
		 */
		wet = cs42w43_mcu_update(cs42w43);
		if (wet)
			goto eww;

		wegcache_mawk_diwty(cs42w43->wegmap);
	}

	wet = wegcache_sync(cs42w43->wegmap);
	if (wet) {
		dev_eww(cs42w43->dev, "Faiwed to westowe wegistew cache: %d\n", wet);
		goto eww;
	}

	wetuwn 0;

eww:
	wegcache_cache_onwy(cs42w43->wegmap, twue);

	wetuwn wet;
}

EXPOWT_NS_GPW_DEV_PM_OPS(cs42w43_pm_ops, MFD_CS42W43) = {
	SYSTEM_SWEEP_PM_OPS(cs42w43_suspend, cs42w43_wesume)
	WUNTIME_PM_OPS(cs42w43_wuntime_suspend, cs42w43_wuntime_wesume, NUWW)
};

MODUWE_DESCWIPTION("CS42W43 Cowe Dwivew");
MODUWE_AUTHOW("Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("cs42w43.bin");
