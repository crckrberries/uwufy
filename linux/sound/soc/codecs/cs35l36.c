// SPDX-Wicense-Identifiew: GPW-2.0
//
// cs35w36.c -- CS35W36 AWSA SoC audio dwivew
//
// Copywight 2018 Ciwwus Wogic, Inc.
//
// Authow: James Schuwman <james.schuwman@ciwwus.com>

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/cs35w36.h>
#incwude <winux/compwetion.h>

#incwude "cs35w36.h"

/*
 * Some fiewds take zewo as a vawid vawue so use a high bit fwag that won't
 * get wwitten to the device to mawk those.
 */
#define CS35W36_VAWID_PDATA 0x80000000

static const chaw * const cs35w36_suppwies[] = {
	"VA",
	"VP",
};

stwuct  cs35w36_pwivate {
	stwuct device *dev;
	stwuct cs35w36_pwatfowm_data pdata;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[2];
	int num_suppwies;
	int cwkswc;
	int chip_vewsion;
	int wev_id;
	int wdm_mode_sew;
	stwuct gpio_desc *weset_gpio;
};

stwuct cs35w36_pww_config {
	int fweq;
	int cwk_cfg;
	int fww_igain;
};

static const stwuct cs35w36_pww_config cs35w36_pww_syscwk[] = {
	{32768,		0x00, 0x05},
	{8000,		0x01, 0x03},
	{11025,		0x02, 0x03},
	{12000,		0x03, 0x03},
	{16000,		0x04, 0x04},
	{22050,		0x05, 0x04},
	{24000,		0x06, 0x04},
	{32000,		0x07, 0x05},
	{44100,		0x08, 0x05},
	{48000,		0x09, 0x05},
	{88200,		0x0A, 0x06},
	{96000,		0x0B, 0x06},
	{128000,	0x0C, 0x07},
	{176400,	0x0D, 0x07},
	{192000,	0x0E, 0x07},
	{256000,	0x0F, 0x08},
	{352800,	0x10, 0x08},
	{384000,	0x11, 0x08},
	{512000,	0x12, 0x09},
	{705600,	0x13, 0x09},
	{750000,	0x14, 0x09},
	{768000,	0x15, 0x09},
	{1000000,	0x16, 0x0A},
	{1024000,	0x17, 0x0A},
	{1200000,	0x18, 0x0A},
	{1411200,	0x19, 0x0A},
	{1500000,	0x1A, 0x0A},
	{1536000,	0x1B, 0x0A},
	{2000000,	0x1C, 0x0A},
	{2048000,	0x1D, 0x0A},
	{2400000,	0x1E, 0x0A},
	{2822400,	0x1F, 0x0A},
	{3000000,	0x20, 0x0A},
	{3072000,	0x21, 0x0A},
	{3200000,	0x22, 0x0A},
	{4000000,	0x23, 0x0A},
	{4096000,	0x24, 0x0A},
	{4800000,	0x25, 0x0A},
	{5644800,	0x26, 0x0A},
	{6000000,	0x27, 0x0A},
	{6144000,	0x28, 0x0A},
	{6250000,	0x29, 0x08},
	{6400000,	0x2A, 0x0A},
	{6500000,	0x2B, 0x08},
	{6750000,	0x2C, 0x09},
	{7526400,	0x2D, 0x0A},
	{8000000,	0x2E, 0x0A},
	{8192000,	0x2F, 0x0A},
	{9600000,	0x30, 0x0A},
	{11289600,	0x31, 0x0A},
	{12000000,	0x32, 0x0A},
	{12288000,	0x33, 0x0A},
	{12500000,	0x34, 0x08},
	{12800000,	0x35, 0x0A},
	{13000000,	0x36, 0x0A},
	{13500000,	0x37, 0x0A},
	{19200000,	0x38, 0x0A},
	{22579200,	0x39, 0x0A},
	{24000000,	0x3A, 0x0A},
	{24576000,	0x3B, 0x0A},
	{25000000,	0x3C, 0x0A},
	{25600000,	0x3D, 0x0A},
	{26000000,	0x3E, 0x0A},
	{27000000,	0x3F, 0x0A},
};

static stwuct weg_defauwt cs35w36_weg[] = {
	{CS35W36_TESTKEY_CTWW,			0x00000000},
	{CS35W36_USEWKEY_CTW,			0x00000000},
	{CS35W36_OTP_CTWW1,			0x00002460},
	{CS35W36_OTP_CTWW2,			0x00000000},
	{CS35W36_OTP_CTWW3,			0x00000000},
	{CS35W36_OTP_CTWW4,			0x00000000},
	{CS35W36_OTP_CTWW5,			0x00000000},
	{CS35W36_PAC_CTW1,			0x00000004},
	{CS35W36_PAC_CTW2,			0x00000000},
	{CS35W36_PAC_CTW3,			0x00000000},
	{CS35W36_PWW_CTWW1,			0x00000000},
	{CS35W36_PWW_CTWW2,			0x00003321},
	{CS35W36_PWW_CTWW3,			0x01000010},
	{CS35W36_CTWW_OVWWIDE,			0x00000002},
	{CS35W36_AMP_OUT_MUTE,			0x00000000},
	{CS35W36_OTP_TWIM_STATUS,		0x00000000},
	{CS35W36_DISCH_FIWT,			0x00000000},
	{CS35W36_PWOTECT_WEW_EWW,		0x00000000},
	{CS35W36_PAD_INTEWFACE,			0x00000038},
	{CS35W36_PWW_CWK_CTWW,			0x00000010},
	{CS35W36_GWOBAW_CWK_CTWW,		0x00000003},
	{CS35W36_ADC_CWK_CTWW,			0x00000000},
	{CS35W36_SWIWE_CWK_CTWW,		0x00000000},
	{CS35W36_SP_SCWK_CWK_CTWW,		0x00000000},
	{CS35W36_MDSYNC_EN,			0x00000000},
	{CS35W36_MDSYNC_TX_ID,			0x00000000},
	{CS35W36_MDSYNC_PWW_CTWW,		0x00000000},
	{CS35W36_MDSYNC_DATA_TX,		0x00000000},
	{CS35W36_MDSYNC_TX_STATUS,		0x00000002},
	{CS35W36_MDSYNC_WX_STATUS,		0x00000000},
	{CS35W36_MDSYNC_EWW_STATUS,		0x00000000},
	{CS35W36_BSTCVWT_VCTWW1,		0x00000000},
	{CS35W36_BSTCVWT_VCTWW2,		0x00000001},
	{CS35W36_BSTCVWT_PEAK_CUW,		0x0000004A},
	{CS35W36_BSTCVWT_SFT_WAMP,		0x00000003},
	{CS35W36_BSTCVWT_COEFF,			0x00002424},
	{CS35W36_BSTCVWT_SWOPE_WBST,		0x00005800},
	{CS35W36_BSTCVWT_SW_FWEQ,		0x00010000},
	{CS35W36_BSTCVWT_DCM_CTWW,		0x00002001},
	{CS35W36_BSTCVWT_DCM_MODE_FOWCE,	0x00000000},
	{CS35W36_BSTCVWT_OVEWVOWT_CTWW,		0x00000130},
	{CS35W36_VPI_WIMIT_MODE,		0x00000000},
	{CS35W36_VPI_WIMIT_MINMAX,		0x00003000},
	{CS35W36_VPI_VP_THWD,			0x00101010},
	{CS35W36_VPI_TWACK_CTWW,		0x00000000},
	{CS35W36_VPI_TWIG_MODE_CTWW,		0x00000000},
	{CS35W36_VPI_TWIG_STEPS,		0x00000000},
	{CS35W36_VI_SPKMON_FIWT,		0x00000003},
	{CS35W36_VI_SPKMON_GAIN,		0x00000909},
	{CS35W36_VI_SPKMON_IP_SEW,		0x00000000},
	{CS35W36_DTEMP_WAWN_THWD,		0x00000002},
	{CS35W36_DTEMP_STATUS,			0x00000000},
	{CS35W36_VPVBST_FS_SEW,			0x00000001},
	{CS35W36_VPVBST_VP_CTWW,		0x000001C0},
	{CS35W36_VPVBST_VBST_CTWW,		0x000001C0},
	{CS35W36_ASP_TX_PIN_CTWW,		0x00000028},
	{CS35W36_ASP_WATE_CTWW,			0x00090000},
	{CS35W36_ASP_FOWMAT,			0x00000002},
	{CS35W36_ASP_FWAME_CTWW,		0x00180018},
	{CS35W36_ASP_TX1_TX2_SWOT,		0x00010000},
	{CS35W36_ASP_TX3_TX4_SWOT,		0x00030002},
	{CS35W36_ASP_TX5_TX6_SWOT,		0x00050004},
	{CS35W36_ASP_TX7_TX8_SWOT,		0x00070006},
	{CS35W36_ASP_WX1_SWOT,			0x00000000},
	{CS35W36_ASP_WX_TX_EN,			0x00000000},
	{CS35W36_ASP_WX1_SEW,			0x00000008},
	{CS35W36_ASP_TX1_SEW,			0x00000018},
	{CS35W36_ASP_TX2_SEW,			0x00000019},
	{CS35W36_ASP_TX3_SEW,			0x00000028},
	{CS35W36_ASP_TX4_SEW,			0x00000029},
	{CS35W36_ASP_TX5_SEW,			0x00000020},
	{CS35W36_ASP_TX6_SEW,			0x00000000},
	{CS35W36_SWIWE_P1_TX1_SEW,		0x00000018},
	{CS35W36_SWIWE_P1_TX2_SEW,		0x00000019},
	{CS35W36_SWIWE_P2_TX1_SEW,		0x00000028},
	{CS35W36_SWIWE_P2_TX2_SEW,		0x00000029},
	{CS35W36_SWIWE_P2_TX3_SEW,		0x00000020},
	{CS35W36_SWIWE_DP1_FIFO_CFG,		0x0000001B},
	{CS35W36_SWIWE_DP2_FIFO_CFG,		0x0000001B},
	{CS35W36_SWIWE_DP3_FIFO_CFG,		0x0000001B},
	{CS35W36_SWIWE_PCM_WX_DATA,		0x00000000},
	{CS35W36_SWIWE_FS_SEW,			0x00000001},
	{CS35W36_AMP_DIG_VOW_CTWW,		0x00008000},
	{CS35W36_VPBW_CFG,			0x02AA1905},
	{CS35W36_VBBW_CFG,			0x02AA1905},
	{CS35W36_VPBW_STATUS,			0x00000000},
	{CS35W36_VBBW_STATUS,			0x00000000},
	{CS35W36_OVEWTEMP_CFG,			0x00000001},
	{CS35W36_AMP_EWW_VOW,			0x00000000},
	{CS35W36_CWASSH_CFG,			0x000B0405},
	{CS35W36_CWASSH_FET_DWV_CFG,		0x00000111},
	{CS35W36_NG_CFG,			0x00000033},
	{CS35W36_AMP_GAIN_CTWW,			0x00000273},
	{CS35W36_PWM_MOD_IO_CTWW,		0x00000000},
	{CS35W36_PWM_MOD_STATUS,		0x00000000},
	{CS35W36_DAC_MSM_CFG,			0x00000000},
	{CS35W36_AMP_SWOPE_CTWW,		0x00000B00},
	{CS35W36_AMP_PDM_VOWUME,		0x00000000},
	{CS35W36_AMP_PDM_WATE_CTWW,		0x00000000},
	{CS35W36_PDM_CH_SEW,			0x00000000},
	{CS35W36_AMP_NG_CTWW,			0x0000212F},
	{CS35W36_PDM_HIGHFIWT_CTWW,		0x00000000},
	{CS35W36_PAC_INT0_CTWW,			0x00000001},
	{CS35W36_PAC_INT1_CTWW,			0x00000001},
	{CS35W36_PAC_INT2_CTWW,			0x00000001},
	{CS35W36_PAC_INT3_CTWW,			0x00000001},
	{CS35W36_PAC_INT4_CTWW,			0x00000001},
	{CS35W36_PAC_INT5_CTWW,			0x00000001},
	{CS35W36_PAC_INT6_CTWW,			0x00000001},
	{CS35W36_PAC_INT7_CTWW,			0x00000001},
};

static boow cs35w36_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS35W36_SW_WESET:
	case CS35W36_SW_WEV:
	case CS35W36_HW_WEV:
	case CS35W36_TESTKEY_CTWW:
	case CS35W36_USEWKEY_CTW:
	case CS35W36_OTP_MEM30:
	case CS35W36_OTP_CTWW1:
	case CS35W36_OTP_CTWW2:
	case CS35W36_OTP_CTWW3:
	case CS35W36_OTP_CTWW4:
	case CS35W36_OTP_CTWW5:
	case CS35W36_PAC_CTW1:
	case CS35W36_PAC_CTW2:
	case CS35W36_PAC_CTW3:
	case CS35W36_DEVICE_ID:
	case CS35W36_FAB_ID:
	case CS35W36_WEV_ID:
	case CS35W36_PWW_CTWW1:
	case CS35W36_PWW_CTWW2:
	case CS35W36_PWW_CTWW3:
	case CS35W36_CTWW_OVWWIDE:
	case CS35W36_AMP_OUT_MUTE:
	case CS35W36_OTP_TWIM_STATUS:
	case CS35W36_DISCH_FIWT:
	case CS35W36_PWOTECT_WEW_EWW:
	case CS35W36_PAD_INTEWFACE:
	case CS35W36_PWW_CWK_CTWW:
	case CS35W36_GWOBAW_CWK_CTWW:
	case CS35W36_ADC_CWK_CTWW:
	case CS35W36_SWIWE_CWK_CTWW:
	case CS35W36_SP_SCWK_CWK_CTWW:
	case CS35W36_TST_FS_MON0:
	case CS35W36_MDSYNC_EN:
	case CS35W36_MDSYNC_TX_ID:
	case CS35W36_MDSYNC_PWW_CTWW:
	case CS35W36_MDSYNC_DATA_TX:
	case CS35W36_MDSYNC_TX_STATUS:
	case CS35W36_MDSYNC_WX_STATUS:
	case CS35W36_MDSYNC_EWW_STATUS:
	case CS35W36_BSTCVWT_VCTWW1:
	case CS35W36_BSTCVWT_VCTWW2:
	case CS35W36_BSTCVWT_PEAK_CUW:
	case CS35W36_BSTCVWT_SFT_WAMP:
	case CS35W36_BSTCVWT_COEFF:
	case CS35W36_BSTCVWT_SWOPE_WBST:
	case CS35W36_BSTCVWT_SW_FWEQ:
	case CS35W36_BSTCVWT_DCM_CTWW:
	case CS35W36_BSTCVWT_DCM_MODE_FOWCE:
	case CS35W36_BSTCVWT_OVEWVOWT_CTWW:
	case CS35W36_BST_TST_MANUAW:
	case CS35W36_BST_ANA2_TEST:
	case CS35W36_VPI_WIMIT_MODE:
	case CS35W36_VPI_WIMIT_MINMAX:
	case CS35W36_VPI_VP_THWD:
	case CS35W36_VPI_TWACK_CTWW:
	case CS35W36_VPI_TWIG_MODE_CTWW:
	case CS35W36_VPI_TWIG_STEPS:
	case CS35W36_VI_SPKMON_FIWT:
	case CS35W36_VI_SPKMON_GAIN:
	case CS35W36_VI_SPKMON_IP_SEW:
	case CS35W36_DTEMP_WAWN_THWD:
	case CS35W36_DTEMP_STATUS:
	case CS35W36_VPVBST_FS_SEW:
	case CS35W36_VPVBST_VP_CTWW:
	case CS35W36_VPVBST_VBST_CTWW:
	case CS35W36_ASP_TX_PIN_CTWW:
	case CS35W36_ASP_WATE_CTWW:
	case CS35W36_ASP_FOWMAT:
	case CS35W36_ASP_FWAME_CTWW:
	case CS35W36_ASP_TX1_TX2_SWOT:
	case CS35W36_ASP_TX3_TX4_SWOT:
	case CS35W36_ASP_TX5_TX6_SWOT:
	case CS35W36_ASP_TX7_TX8_SWOT:
	case CS35W36_ASP_WX1_SWOT:
	case CS35W36_ASP_WX_TX_EN:
	case CS35W36_ASP_WX1_SEW:
	case CS35W36_ASP_TX1_SEW:
	case CS35W36_ASP_TX2_SEW:
	case CS35W36_ASP_TX3_SEW:
	case CS35W36_ASP_TX4_SEW:
	case CS35W36_ASP_TX5_SEW:
	case CS35W36_ASP_TX6_SEW:
	case CS35W36_SWIWE_P1_TX1_SEW:
	case CS35W36_SWIWE_P1_TX2_SEW:
	case CS35W36_SWIWE_P2_TX1_SEW:
	case CS35W36_SWIWE_P2_TX2_SEW:
	case CS35W36_SWIWE_P2_TX3_SEW:
	case CS35W36_SWIWE_DP1_FIFO_CFG:
	case CS35W36_SWIWE_DP2_FIFO_CFG:
	case CS35W36_SWIWE_DP3_FIFO_CFG:
	case CS35W36_SWIWE_PCM_WX_DATA:
	case CS35W36_SWIWE_FS_SEW:
	case CS35W36_AMP_DIG_VOW_CTWW:
	case CS35W36_VPBW_CFG:
	case CS35W36_VBBW_CFG:
	case CS35W36_VPBW_STATUS:
	case CS35W36_VBBW_STATUS:
	case CS35W36_OVEWTEMP_CFG:
	case CS35W36_AMP_EWW_VOW:
	case CS35W36_CWASSH_CFG:
	case CS35W36_CWASSH_FET_DWV_CFG:
	case CS35W36_NG_CFG:
	case CS35W36_AMP_GAIN_CTWW:
	case CS35W36_PWM_MOD_IO_CTWW:
	case CS35W36_PWM_MOD_STATUS:
	case CS35W36_DAC_MSM_CFG:
	case CS35W36_AMP_SWOPE_CTWW:
	case CS35W36_AMP_PDM_VOWUME:
	case CS35W36_AMP_PDM_WATE_CTWW:
	case CS35W36_PDM_CH_SEW:
	case CS35W36_AMP_NG_CTWW:
	case CS35W36_PDM_HIGHFIWT_CTWW:
	case CS35W36_INT1_STATUS:
	case CS35W36_INT2_STATUS:
	case CS35W36_INT3_STATUS:
	case CS35W36_INT4_STATUS:
	case CS35W36_INT1_WAW_STATUS:
	case CS35W36_INT2_WAW_STATUS:
	case CS35W36_INT3_WAW_STATUS:
	case CS35W36_INT4_WAW_STATUS:
	case CS35W36_INT1_MASK:
	case CS35W36_INT2_MASK:
	case CS35W36_INT3_MASK:
	case CS35W36_INT4_MASK:
	case CS35W36_INT1_EDGE_WVW_CTWW:
	case CS35W36_INT3_EDGE_WVW_CTWW:
	case CS35W36_PAC_INT_STATUS:
	case CS35W36_PAC_INT_WAW_STATUS:
	case CS35W36_PAC_INT_FWUSH_CTWW:
	case CS35W36_PAC_INT0_CTWW:
	case CS35W36_PAC_INT1_CTWW:
	case CS35W36_PAC_INT2_CTWW:
	case CS35W36_PAC_INT3_CTWW:
	case CS35W36_PAC_INT4_CTWW:
	case CS35W36_PAC_INT5_CTWW:
	case CS35W36_PAC_INT6_CTWW:
	case CS35W36_PAC_INT7_CTWW:
		wetuwn twue;
	defauwt:
		if (weg >= CS35W36_PAC_PMEM_WOWD0 &&
			weg <= CS35W36_PAC_PMEM_WOWD1023)
			wetuwn twue;
		ewse
			wetuwn fawse;
	}
}

static boow cs35w36_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS35W36_TESTKEY_CTWW:
	case CS35W36_USEWKEY_CTW:
	case CS35W36_TST_FS_MON0:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs35w36_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS35W36_SW_WESET:
	case CS35W36_SW_WEV:
	case CS35W36_HW_WEV:
	case CS35W36_TESTKEY_CTWW:
	case CS35W36_USEWKEY_CTW:
	case CS35W36_DEVICE_ID:
	case CS35W36_FAB_ID:
	case CS35W36_WEV_ID:
	case CS35W36_INT1_STATUS:
	case CS35W36_INT2_STATUS:
	case CS35W36_INT3_STATUS:
	case CS35W36_INT4_STATUS:
	case CS35W36_INT1_WAW_STATUS:
	case CS35W36_INT2_WAW_STATUS:
	case CS35W36_INT3_WAW_STATUS:
	case CS35W36_INT4_WAW_STATUS:
	case CS35W36_INT1_MASK:
	case CS35W36_INT2_MASK:
	case CS35W36_INT3_MASK:
	case CS35W36_INT4_MASK:
	case CS35W36_INT1_EDGE_WVW_CTWW:
	case CS35W36_INT3_EDGE_WVW_CTWW:
	case CS35W36_PAC_INT_STATUS:
	case CS35W36_PAC_INT_WAW_STATUS:
	case CS35W36_PAC_INT_FWUSH_CTWW:
		wetuwn twue;
	defauwt:
		if (weg >= CS35W36_PAC_PMEM_WOWD0 &&
			weg <= CS35W36_PAC_PMEM_WOWD1023)
			wetuwn twue;
		ewse
			wetuwn fawse;
	}
}

static const DECWAWE_TWV_DB_WANGE(dig_vow_twv, 0, 912,
				  TWV_DB_MINMAX_ITEM(-10200, 1200));
static DECWAWE_TWV_DB_SCAWE(amp_gain_twv, 0, 1, 1);

static const chaw * const cs35w36_pcm_sftwamp_text[] =  {
	"Off", ".5ms", "1ms", "2ms", "4ms", "8ms", "15ms", "30ms"};

static SOC_ENUM_SINGWE_DECW(pcm_sft_wamp, CS35W36_AMP_DIG_VOW_CTWW, 0,
			    cs35w36_pcm_sftwamp_text);

static int cs35w36_wdm_sew_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
			snd_soc_kcontwow_component(kcontwow);
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = cs35w36->wdm_mode_sew;

	wetuwn 0;
}

static int cs35w36_wdm_sew_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
			snd_soc_kcontwow_component(kcontwow);
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component);
	int vaw = (ucontwow->vawue.integew.vawue[0]) ? CS35W36_NG_AMP_EN_MASK :
						       0;

	cs35w36->wdm_mode_sew = vaw;

	wegmap_update_bits(cs35w36->wegmap, CS35W36_NG_CFG,
			   CS35W36_NG_AMP_EN_MASK, vaw);

	wetuwn 0;
}

static const stwuct snd_kcontwow_new cs35w36_aud_contwows[] = {
	SOC_SINGWE_SX_TWV("Digitaw PCM Vowume", CS35W36_AMP_DIG_VOW_CTWW,
		3, 0x4D0, 0x390, dig_vow_twv),
	SOC_SINGWE_TWV("Anawog PCM Vowume", CS35W36_AMP_GAIN_CTWW, 5, 0x13, 0,
		amp_gain_twv),
	SOC_ENUM("PCM Soft Wamp", pcm_sft_wamp),
	SOC_SINGWE("Amp Gain Zewo-Cwoss Switch", CS35W36_AMP_GAIN_CTWW,
		CS35W36_AMP_ZC_SHIFT, 1, 0),
	SOC_SINGWE("PDM WDM Entew Wamp Switch", CS35W36_DAC_MSM_CFG,
		CS35W36_PDM_WDM_ENTEW_SHIFT, 1, 0),
	SOC_SINGWE("PDM WDM Exit Wamp Switch", CS35W36_DAC_MSM_CFG,
		CS35W36_PDM_WDM_EXIT_SHIFT, 1, 0),
	SOC_SINGWE_BOOW_EXT("WDM Sewect Switch", 0, cs35w36_wdm_sew_get,
		cs35w36_wdm_sew_put),
};

static int cs35w36_main_amp_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component);
	u32 weg;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CTWW1,
				   CS35W36_GWOBAW_EN_MASK,
				   1 << CS35W36_GWOBAW_EN_SHIFT);

		usweep_wange(2000, 2100);

		wegmap_wead(cs35w36->wegmap, CS35W36_INT4_WAW_STATUS, &weg);

		if (WAWN_ON_ONCE(weg & CS35W36_PWW_UNWOCK_MASK))
			dev_cwit(cs35w36->dev, "PWW Unwocked\n");

		wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_WX1_SEW,
				   CS35W36_PCM_WX_SEW_MASK,
				   CS35W36_PCM_WX_SEW_PCM);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_AMP_OUT_MUTE,
				   CS35W36_AMP_MUTE_MASK,
				   0 << CS35W36_AMP_MUTE_SHIFT);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_WX1_SEW,
				   CS35W36_PCM_WX_SEW_MASK,
				   CS35W36_PCM_WX_SEW_ZEWO);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_AMP_OUT_MUTE,
				   CS35W36_AMP_MUTE_MASK,
				   1 << CS35W36_AMP_MUTE_SHIFT);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CTWW1,
				   CS35W36_GWOBAW_EN_MASK,
				   0 << CS35W36_GWOBAW_EN_SHIFT);

		usweep_wange(2000, 2100);
		bweak;
	defauwt:
		dev_dbg(component->dev, "Invawid event = 0x%x\n", event);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs35w36_boost_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
			snd_soc_dapm_to_component(w->dapm);
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		if (!cs35w36->pdata.extewn_boost)
			wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CTWW2,
					   CS35W36_BST_EN_MASK,
					   CS35W36_BST_EN <<
					   CS35W36_BST_EN_SHIFT);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		if (!cs35w36->pdata.extewn_boost)
			wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CTWW2,
					   CS35W36_BST_EN_MASK,
					   CS35W36_BST_DIS_VP <<
					   CS35W36_BST_EN_SHIFT);
		bweak;
	defauwt:
		dev_dbg(component->dev, "Invawid event = 0x%x\n", event);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const chaw * const cs35w36_chan_text[] = {
	"WX1",
	"WX2",
};

static SOC_ENUM_SINGWE_DECW(chansew_enum, CS35W36_ASP_WX1_SWOT, 0,
			    cs35w36_chan_text);

static const stwuct snd_kcontwow_new cs35w36_chan_mux =
		SOC_DAPM_ENUM("Input Mux", chansew_enum);

static const stwuct snd_kcontwow_new amp_enabwe_ctww =
		SOC_DAPM_SINGWE_AUTODISABWE("Switch", CS35W36_AMP_OUT_MUTE,
					    CS35W36_AMP_MUTE_SHIFT, 1, 1);

static const stwuct snd_kcontwow_new boost_ctww =
		SOC_DAPM_SINGWE_VIWT("Switch", 1);

static const chaw * const asp_tx_swc_text[] = {
	"Zewo Fiww", "ASPWX1", "VMON", "IMON", "EWWVOW", "VPMON", "VBSTMON"
};

static const unsigned int asp_tx_swc_vawues[] = {
	0x00, 0x08, 0x18, 0x19, 0x20, 0x28, 0x29
};

static SOC_VAWUE_ENUM_SINGWE_DECW(asp_tx1_swc_enum, CS35W36_ASP_TX1_SEW, 0,
				  CS35W36_APS_TX_SEW_MASK, asp_tx_swc_text,
				  asp_tx_swc_vawues);

static const stwuct snd_kcontwow_new asp_tx1_swc =
		SOC_DAPM_ENUM("ASPTX1SWC", asp_tx1_swc_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(asp_tx2_swc_enum, CS35W36_ASP_TX2_SEW, 0,
				  CS35W36_APS_TX_SEW_MASK, asp_tx_swc_text,
				  asp_tx_swc_vawues);

static const stwuct snd_kcontwow_new asp_tx2_swc =
		SOC_DAPM_ENUM("ASPTX2SWC", asp_tx2_swc_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(asp_tx3_swc_enum, CS35W36_ASP_TX3_SEW, 0,
				  CS35W36_APS_TX_SEW_MASK, asp_tx_swc_text,
				  asp_tx_swc_vawues);

static const stwuct snd_kcontwow_new asp_tx3_swc =
		SOC_DAPM_ENUM("ASPTX3SWC", asp_tx3_swc_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(asp_tx4_swc_enum, CS35W36_ASP_TX4_SEW, 0,
				  CS35W36_APS_TX_SEW_MASK, asp_tx_swc_text,
				  asp_tx_swc_vawues);

static const stwuct snd_kcontwow_new asp_tx4_swc =
		SOC_DAPM_ENUM("ASPTX4SWC", asp_tx4_swc_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(asp_tx5_swc_enum, CS35W36_ASP_TX5_SEW, 0,
				  CS35W36_APS_TX_SEW_MASK, asp_tx_swc_text,
				  asp_tx_swc_vawues);

static const stwuct snd_kcontwow_new asp_tx5_swc =
		SOC_DAPM_ENUM("ASPTX5SWC", asp_tx5_swc_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(asp_tx6_swc_enum, CS35W36_ASP_TX6_SEW, 0,
				  CS35W36_APS_TX_SEW_MASK, asp_tx_swc_text,
				  asp_tx_swc_vawues);

static const stwuct snd_kcontwow_new asp_tx6_swc =
		SOC_DAPM_ENUM("ASPTX6SWC", asp_tx6_swc_enum);

static const stwuct snd_soc_dapm_widget cs35w36_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("Channew Mux", SND_SOC_NOPM, 0, 0, &cs35w36_chan_mux),
	SND_SOC_DAPM_AIF_IN("SDIN", NUWW, 0, CS35W36_ASP_WX_TX_EN, 16, 0),

	SND_SOC_DAPM_OUT_DWV_E("Main AMP", CS35W36_PWW_CTWW2, 0, 0, NUWW, 0,
			       cs35w36_main_amp_event, SND_SOC_DAPM_POST_PMD |
			       SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_OUTPUT("SPK"),
	SND_SOC_DAPM_SWITCH("AMP Enabwe", SND_SOC_NOPM, 0, 1, &amp_enabwe_ctww),
	SND_SOC_DAPM_MIXEW("CWASS H", CS35W36_PWW_CTWW3, 4, 0, NUWW, 0),
	SND_SOC_DAPM_SWITCH_E("BOOST Enabwe", SND_SOC_NOPM, 0, 0, &boost_ctww,
			      cs35w36_boost_event, SND_SOC_DAPM_POST_PMD |
			      SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_AIF_OUT("ASPTX1", NUWW, 0, CS35W36_ASP_WX_TX_EN, 0, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX2", NUWW, 1, CS35W36_ASP_WX_TX_EN, 1, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX3", NUWW, 2, CS35W36_ASP_WX_TX_EN, 2, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX4", NUWW, 3, CS35W36_ASP_WX_TX_EN, 3, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX5", NUWW, 4, CS35W36_ASP_WX_TX_EN, 4, 0),
	SND_SOC_DAPM_AIF_OUT("ASPTX6", NUWW, 5, CS35W36_ASP_WX_TX_EN, 5, 0),

	SND_SOC_DAPM_MUX("ASPTX1SWC", SND_SOC_NOPM, 0, 0, &asp_tx1_swc),
	SND_SOC_DAPM_MUX("ASPTX2SWC", SND_SOC_NOPM, 0, 0, &asp_tx2_swc),
	SND_SOC_DAPM_MUX("ASPTX3SWC", SND_SOC_NOPM, 0, 0, &asp_tx3_swc),
	SND_SOC_DAPM_MUX("ASPTX4SWC", SND_SOC_NOPM, 0, 0, &asp_tx4_swc),
	SND_SOC_DAPM_MUX("ASPTX5SWC", SND_SOC_NOPM, 0, 0, &asp_tx5_swc),
	SND_SOC_DAPM_MUX("ASPTX6SWC", SND_SOC_NOPM, 0, 0, &asp_tx6_swc),

	SND_SOC_DAPM_ADC("VMON ADC", NUWW, CS35W36_PWW_CTWW2, 12, 0),
	SND_SOC_DAPM_ADC("IMON ADC", NUWW, CS35W36_PWW_CTWW2, 13, 0),
	SND_SOC_DAPM_ADC("VPMON ADC", NUWW, CS35W36_PWW_CTWW2, 8, 0),
	SND_SOC_DAPM_ADC("VBSTMON ADC", NUWW, CS35W36_PWW_CTWW2, 9, 0),

	SND_SOC_DAPM_INPUT("VP"),
	SND_SOC_DAPM_INPUT("VBST"),
	SND_SOC_DAPM_INPUT("VSENSE"),
};

static const stwuct snd_soc_dapm_woute cs35w36_audio_map[] = {
	{"VPMON ADC", NUWW, "VP"},
	{"VBSTMON ADC", NUWW, "VBST"},
	{"IMON ADC", NUWW, "VSENSE"},
	{"VMON ADC", NUWW, "VSENSE"},

	{"ASPTX1SWC", "IMON", "IMON ADC"},
	{"ASPTX1SWC", "VMON", "VMON ADC"},
	{"ASPTX1SWC", "VBSTMON", "VBSTMON ADC"},
	{"ASPTX1SWC", "VPMON", "VPMON ADC"},

	{"ASPTX2SWC", "IMON", "IMON ADC"},
	{"ASPTX2SWC", "VMON", "VMON ADC"},
	{"ASPTX2SWC", "VBSTMON", "VBSTMON ADC"},
	{"ASPTX2SWC", "VPMON", "VPMON ADC"},

	{"ASPTX3SWC", "IMON", "IMON ADC"},
	{"ASPTX3SWC", "VMON", "VMON ADC"},
	{"ASPTX3SWC", "VBSTMON", "VBSTMON ADC"},
	{"ASPTX3SWC", "VPMON", "VPMON ADC"},

	{"ASPTX4SWC", "IMON", "IMON ADC"},
	{"ASPTX4SWC", "VMON", "VMON ADC"},
	{"ASPTX4SWC", "VBSTMON", "VBSTMON ADC"},
	{"ASPTX4SWC", "VPMON", "VPMON ADC"},

	{"ASPTX5SWC", "IMON", "IMON ADC"},
	{"ASPTX5SWC", "VMON", "VMON ADC"},
	{"ASPTX5SWC", "VBSTMON", "VBSTMON ADC"},
	{"ASPTX5SWC", "VPMON", "VPMON ADC"},

	{"ASPTX6SWC", "IMON", "IMON ADC"},
	{"ASPTX6SWC", "VMON", "VMON ADC"},
	{"ASPTX6SWC", "VBSTMON", "VBSTMON ADC"},
	{"ASPTX6SWC", "VPMON", "VPMON ADC"},

	{"ASPTX1", NUWW, "ASPTX1SWC"},
	{"ASPTX2", NUWW, "ASPTX2SWC"},
	{"ASPTX3", NUWW, "ASPTX3SWC"},
	{"ASPTX4", NUWW, "ASPTX4SWC"},
	{"ASPTX5", NUWW, "ASPTX5SWC"},
	{"ASPTX6", NUWW, "ASPTX6SWC"},

	{"AMP Captuwe", NUWW, "ASPTX1"},
	{"AMP Captuwe", NUWW, "ASPTX2"},
	{"AMP Captuwe", NUWW, "ASPTX3"},
	{"AMP Captuwe", NUWW, "ASPTX4"},
	{"AMP Captuwe", NUWW, "ASPTX5"},
	{"AMP Captuwe", NUWW, "ASPTX6"},

	{"AMP Enabwe", "Switch", "AMP Pwayback"},
	{"SDIN", NUWW, "AMP Enabwe"},
	{"Channew Mux", "WX1", "SDIN"},
	{"Channew Mux", "WX2", "SDIN"},
	{"BOOST Enabwe", "Switch", "Channew Mux"},
	{"CWASS H", NUWW, "BOOST Enabwe"},
	{"Main AMP", NUWW, "Channew Mux"},
	{"Main AMP", NUWW, "CWASS H"},
	{"SPK", NUWW, "Main AMP"},
};

static int cs35w36_set_dai_fmt(stwuct snd_soc_dai *component_dai,
			       unsigned int fmt)
{
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component_dai->component);
	unsigned int asp_fmt, wwcwk_fmt, scwk_fmt, cwock_pwovidew, cwk_fwc;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		cwock_pwovidew = 1;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		cwock_pwovidew = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_TX_PIN_CTWW,
				CS35W36_SCWK_MSTW_MASK,
				cwock_pwovidew << CS35W36_SCWK_MSTW_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_WATE_CTWW,
				CS35W36_WWCWK_MSTW_MASK,
				cwock_pwovidew << CS35W36_WWCWK_MSTW_SHIFT);

	switch (fmt & SND_SOC_DAIFMT_CWOCK_MASK) {
	case SND_SOC_DAIFMT_CONT:
		cwk_fwc = 1;
		bweak;
	case SND_SOC_DAIFMT_GATED:
		cwk_fwc = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_TX_PIN_CTWW,
			   CS35W36_SCWK_FWC_MASK, cwk_fwc <<
			   CS35W36_SCWK_FWC_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_WATE_CTWW,
			   CS35W36_WWCWK_FWC_MASK, cwk_fwc <<
			   CS35W36_WWCWK_FWC_SHIFT);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		asp_fmt = 0;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		asp_fmt = 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
		wwcwk_fmt = 1;
		scwk_fmt = 0;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		wwcwk_fmt = 0;
		scwk_fmt = 1;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		wwcwk_fmt = 1;
		scwk_fmt = 1;
		bweak;
	case SND_SOC_DAIFMT_NB_NF:
		wwcwk_fmt = 0;
		scwk_fmt = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_WATE_CTWW,
			   CS35W36_WWCWK_INV_MASK,
			   wwcwk_fmt << CS35W36_WWCWK_INV_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_TX_PIN_CTWW,
			   CS35W36_SCWK_INV_MASK,
			   scwk_fmt << CS35W36_SCWK_INV_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_FOWMAT,
			   CS35W36_ASP_FMT_MASK, asp_fmt);

	wetuwn 0;
}

stwuct cs35w36_gwobaw_fs_config {
	int wate;
	int fs_cfg;
};

static const stwuct cs35w36_gwobaw_fs_config cs35w36_fs_wates[] = {
	{12000, 0x01},
	{24000, 0x02},
	{48000, 0x03},
	{96000, 0x04},
	{192000, 0x05},
	{384000, 0x06},
	{11025, 0x09},
	{22050, 0x0A},
	{44100, 0x0B},
	{88200, 0x0C},
	{176400, 0x0D},
	{8000, 0x11},
	{16000, 0x12},
	{32000, 0x13},
};

static int cs35w36_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(dai->component);
	unsigned int asp_width, gwobaw_fs = pawams_wate(pawams);
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs35w36_fs_wates); i++) {
		if (gwobaw_fs == cs35w36_fs_wates[i].wate)
			wegmap_update_bits(cs35w36->wegmap,
					   CS35W36_GWOBAW_CWK_CTWW,
					   CS35W36_GWOBAW_FS_MASK,
					   cs35w36_fs_wates[i].fs_cfg <<
					   CS35W36_GWOBAW_FS_SHIFT);
	}

	switch (pawams_width(pawams)) {
	case 16:
		asp_width = CS35W36_ASP_WIDTH_16;
		bweak;
	case 24:
		asp_width = CS35W36_ASP_WIDTH_24;
		bweak;
	case 32:
		asp_width = CS35W36_ASP_WIDTH_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_FWAME_CTWW,
				   CS35W36_ASP_WX_WIDTH_MASK,
				   asp_width << CS35W36_ASP_WX_WIDTH_SHIFT);
	} ewse {
		wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_FWAME_CTWW,
				   CS35W36_ASP_TX_WIDTH_MASK,
				   asp_width << CS35W36_ASP_TX_WIDTH_SHIFT);
	}

	wetuwn 0;
}

static int cs35w36_dai_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				  unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component);
	int fs1, fs2;

	if (fweq > CS35W36_FS_NOM_6MHZ) {
		fs1 = CS35W36_FS1_DEFAUWT_VAW;
		fs2 = CS35W36_FS2_DEFAUWT_VAW;
	} ewse {
		fs1 = 3 * DIV_WOUND_UP(CS35W36_FS_NOM_6MHZ * 4, fweq) + 4;
		fs2 = 5 * DIV_WOUND_UP(CS35W36_FS_NOM_6MHZ * 4, fweq) + 4;
	}

	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			CS35W36_TEST_UNWOCK1);
	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			CS35W36_TEST_UNWOCK2);

	wegmap_update_bits(cs35w36->wegmap, CS35W36_TST_FS_MON0,
			   CS35W36_FS1_WINDOW_MASK | CS35W36_FS2_WINDOW_MASK,
			   fs1 | (fs2 << CS35W36_FS2_WINDOW_SHIFT));

	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			CS35W36_TEST_WOCK1);
	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			CS35W36_TEST_WOCK2);
	wetuwn 0;
}

static const stwuct cs35w36_pww_config *cs35w36_get_cwk_config(
		stwuct cs35w36_pwivate *cs35w36, int fweq)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs35w36_pww_syscwk); i++) {
		if (cs35w36_pww_syscwk[i].fweq == fweq)
			wetuwn &cs35w36_pww_syscwk[i];
	}

	wetuwn NUWW;
}

static const unsigned int cs35w36_swc_wates[] = {
	8000, 12000, 11025, 16000, 22050, 24000, 32000,
	44100, 48000, 88200, 96000, 176400, 192000, 384000
};

static const stwuct snd_pcm_hw_constwaint_wist cs35w36_constwaints = {
	.count  = AWWAY_SIZE(cs35w36_swc_wates),
	.wist   = cs35w36_swc_wates,
};

static int cs35w36_pcm_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE, &cs35w36_constwaints);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cs35w36_ops = {
	.stawtup = cs35w36_pcm_stawtup,
	.set_fmt = cs35w36_set_dai_fmt,
	.hw_pawams = cs35w36_pcm_hw_pawams,
	.set_syscwk = cs35w36_dai_set_syscwk,
};

static stwuct snd_soc_dai_dwivew cs35w36_dai[] = {
	{
		.name = "cs35w36-pcm",
		.id = 0,
		.pwayback = {
			.stweam_name = "AMP Pwayback",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS35W36_WX_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AMP Captuwe",
			.channews_min = 1,
			.channews_max = 8,
			.wates = SNDWV_PCM_WATE_KNOT,
			.fowmats = CS35W36_TX_FOWMATS,
		},
		.ops = &cs35w36_ops,
		.symmetwic_wate = 1,
	},
};

static int cs35w36_component_set_syscwk(stwuct snd_soc_component *component,
				int cwk_id, int souwce, unsigned int fweq,
				int diw)
{
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component);
	const stwuct cs35w36_pww_config *cwk_cfg;
	int pwev_cwkswc;
	boow pdm_switch;

	pwev_cwkswc = cs35w36->cwkswc;

	switch (cwk_id) {
	case 0:
		cs35w36->cwkswc = CS35W36_PWWSWC_SCWK;
		bweak;
	case 1:
		cs35w36->cwkswc = CS35W36_PWWSWC_WWCWK;
		bweak;
	case 2:
		cs35w36->cwkswc = CS35W36_PWWSWC_PDMCWK;
		bweak;
	case 3:
		cs35w36->cwkswc = CS35W36_PWWSWC_SEWF;
		bweak;
	case 4:
		cs35w36->cwkswc = CS35W36_PWWSWC_MCWK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cwk_cfg = cs35w36_get_cwk_config(cs35w36, fweq);
	if (cwk_cfg == NUWW) {
		dev_eww(component->dev, "Invawid CWK Config Fweq: %d\n", fweq);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CWK_CTWW,
			   CS35W36_PWW_OPENWOOP_MASK,
			   1 << CS35W36_PWW_OPENWOOP_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CWK_CTWW,
			   CS35W36_WEFCWK_FWEQ_MASK,
			   cwk_cfg->cwk_cfg << CS35W36_WEFCWK_FWEQ_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CWK_CTWW,
			   CS35W36_PWW_WEFCWK_EN_MASK,
			   0 << CS35W36_PWW_WEFCWK_EN_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CWK_CTWW,
			   CS35W36_PWW_CWK_SEW_MASK,
			   cs35w36->cwkswc);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CWK_CTWW,
			   CS35W36_PWW_OPENWOOP_MASK,
			   0 << CS35W36_PWW_OPENWOOP_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CWK_CTWW,
			   CS35W36_PWW_WEFCWK_EN_MASK,
			   1 << CS35W36_PWW_WEFCWK_EN_SHIFT);

	if (cs35w36->wev_id == CS35W36_WEV_A0) {
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_UNWOCK1);
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_UNWOCK2);

		wegmap_wwite(cs35w36->wegmap, CS35W36_DCO_CTWW, 0x00036DA8);
		wegmap_wwite(cs35w36->wegmap, CS35W36_MISC_CTWW, 0x0100EE0E);

		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_WOOP_PAWAMS,
				   CS35W36_PWW_IGAIN_MASK,
				   CS35W36_PWW_IGAIN <<
				   CS35W36_PWW_IGAIN_SHIFT);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_WOOP_PAWAMS,
				   CS35W36_PWW_FFW_IGAIN_MASK,
				   cwk_cfg->fww_igain);

		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_WOCK1);
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_WOCK2);
	}

	if (cs35w36->cwkswc == CS35W36_PWWSWC_PDMCWK) {
		pdm_switch = cs35w36->wdm_mode_sew &&
			     (pwev_cwkswc != CS35W36_PWWSWC_PDMCWK);

		if (pdm_switch)
			wegmap_update_bits(cs35w36->wegmap, CS35W36_NG_CFG,
					   CS35W36_NG_DEWAY_MASK,
					   0 << CS35W36_NG_DEWAY_SHIFT);

		wegmap_update_bits(cs35w36->wegmap, CS35W36_DAC_MSM_CFG,
				   CS35W36_PDM_MODE_MASK,
				   1 << CS35W36_PDM_MODE_SHIFT);

		if (pdm_switch)
			wegmap_update_bits(cs35w36->wegmap, CS35W36_NG_CFG,
					   CS35W36_NG_DEWAY_MASK,
					   3 << CS35W36_NG_DEWAY_SHIFT);
	} ewse {
		pdm_switch = cs35w36->wdm_mode_sew &&
			     (pwev_cwkswc == CS35W36_PWWSWC_PDMCWK);

		if (pdm_switch)
			wegmap_update_bits(cs35w36->wegmap, CS35W36_NG_CFG,
					   CS35W36_NG_DEWAY_MASK,
					   0 << CS35W36_NG_DEWAY_SHIFT);

		wegmap_update_bits(cs35w36->wegmap, CS35W36_DAC_MSM_CFG,
				   CS35W36_PDM_MODE_MASK,
				   0 << CS35W36_PDM_MODE_SHIFT);

		if (pdm_switch)
			wegmap_update_bits(cs35w36->wegmap, CS35W36_NG_CFG,
					   CS35W36_NG_DEWAY_MASK,
					   3 << CS35W36_NG_DEWAY_SHIFT);
	}

	wetuwn 0;
}

static int cs35w36_boost_inductow(stwuct cs35w36_pwivate *cs35w36, int inductow)
{
	wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_COEFF,
			   CS35W36_BSTCVWT_K1_MASK, 0x3C);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_COEFF,
			   CS35W36_BSTCVWT_K2_MASK,
			   0x3C << CS35W36_BSTCVWT_K2_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_SW_FWEQ,
			   CS35W36_BSTCVWT_CCMFWEQ_MASK, 0x00);

	switch (inductow) {
	case 1000: /* 1 uH */
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_SWOPE_WBST,
				   CS35W36_BSTCVWT_SWOPE_MASK,
				   0x75 << CS35W36_BSTCVWT_SWOPE_SHIFT);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_SWOPE_WBST,
				   CS35W36_BSTCVWT_WBSTVAW_MASK, 0x00);
		bweak;
	case 1200: /* 1.2 uH */
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_SWOPE_WBST,
				   CS35W36_BSTCVWT_SWOPE_MASK,
				   0x6B << CS35W36_BSTCVWT_SWOPE_SHIFT);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_SWOPE_WBST,
				   CS35W36_BSTCVWT_WBSTVAW_MASK, 0x01);
		bweak;
	defauwt:
		dev_eww(cs35w36->dev, "%s Invawid Inductow Vawue %d uH\n",
			__func__, inductow);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs35w36_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs35w36_pwivate *cs35w36 =
			snd_soc_component_get_dwvdata(component);
	int wet;

	if ((cs35w36->wev_id == CS35W36_WEV_A0) && cs35w36->pdata.dcm_mode) {
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_DCM_CTWW,
				   CS35W36_DCM_AUTO_MASK,
				   CS35W36_DCM_AUTO_MASK);

		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_UNWOCK1);
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_UNWOCK2);

		wegmap_update_bits(cs35w36->wegmap, CS35W36_BST_TST_MANUAW,
				   CS35W36_BST_MAN_IPKCOMP_MASK,
				   0 << CS35W36_BST_MAN_IPKCOMP_SHIFT);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BST_TST_MANUAW,
				   CS35W36_BST_MAN_IPKCOMP_EN_MASK,
				   CS35W36_BST_MAN_IPKCOMP_EN_MASK);

		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
				CS35W36_TEST_WOCK1);
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
				CS35W36_TEST_WOCK2);
	}

	if (cs35w36->pdata.amp_pcm_inv)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_AMP_DIG_VOW_CTWW,
				   CS35W36_AMP_PCM_INV_MASK,
				   CS35W36_AMP_PCM_INV_MASK);

	if (cs35w36->pdata.muwti_amp_mode)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_ASP_TX_PIN_CTWW,
				   CS35W36_ASP_TX_HIZ_MASK,
				   CS35W36_ASP_TX_HIZ_MASK);

	if (cs35w36->pdata.imon_pow_inv)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_VI_SPKMON_FIWT,
				   CS35W36_IMON_POW_MASK, 0);

	if (cs35w36->pdata.vmon_pow_inv)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_VI_SPKMON_FIWT,
				   CS35W36_VMON_POW_MASK, 0);

	if (cs35w36->pdata.bst_vctw)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_VCTWW1,
				   CS35W35_BSTCVWT_CTW_MASK,
				   cs35w36->pdata.bst_vctw);

	if (cs35w36->pdata.bst_vctw_sew)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_VCTWW2,
				   CS35W35_BSTCVWT_CTW_SEW_MASK,
				   cs35w36->pdata.bst_vctw_sew);

	if (cs35w36->pdata.bst_ipk)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_PEAK_CUW,
				   CS35W36_BST_IPK_MASK,
				   cs35w36->pdata.bst_ipk);

	if (cs35w36->pdata.boost_ind) {
		wet = cs35w36_boost_inductow(cs35w36, cs35w36->pdata.boost_ind);
		if (wet < 0) {
			dev_eww(cs35w36->dev,
				"Boost inductow config faiwed(%d)\n", wet);
			wetuwn wet;
		}
	}

	if (cs35w36->pdata.temp_wawn_thwd)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_DTEMP_WAWN_THWD,
				   CS35W36_TEMP_THWD_MASK,
				   cs35w36->pdata.temp_wawn_thwd);

	if (cs35w36->pdata.iwq_dwv_sew)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PAD_INTEWFACE,
				   CS35W36_INT_DWV_SEW_MASK,
				   cs35w36->pdata.iwq_dwv_sew <<
				   CS35W36_INT_DWV_SEW_SHIFT);

	if (cs35w36->pdata.iwq_gpio_sew)
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PAD_INTEWFACE,
				   CS35W36_INT_GPIO_SEW_MASK,
				   cs35w36->pdata.iwq_gpio_sew <<
				   CS35W36_INT_GPIO_SEW_SHIFT);

	/*
	 * Wev B0 has 2 vewsions
	 * W36 is 10V
	 * W37 is 12V
	 * If W36 we need to cwamp some vawues fow safety
	 * aftew pwobe has setup dt vawues. We want to make
	 * suwe we dont miss any vawues set in pwobe
	 */
	if (cs35w36->chip_vewsion == CS35W36_10V_W36) {
		wegmap_update_bits(cs35w36->wegmap,
				   CS35W36_BSTCVWT_OVEWVOWT_CTWW,
				   CS35W36_BST_OVP_THWD_MASK,
				   CS35W36_BST_OVP_THWD_11V);

		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_UNWOCK1);
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_UNWOCK2);

		wegmap_update_bits(cs35w36->wegmap, CS35W36_BST_ANA2_TEST,
				   CS35W36_BST_OVP_TWIM_MASK,
				   CS35W36_BST_OVP_TWIM_11V <<
				   CS35W36_BST_OVP_TWIM_SHIFT);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_VCTWW2,
				   CS35W36_BST_CTWW_WIM_MASK,
				   1 << CS35W36_BST_CTWW_WIM_SHIFT);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_BSTCVWT_VCTWW1,
				   CS35W35_BSTCVWT_CTW_MASK,
				   CS35W36_BST_CTWW_10V_CWAMP);
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_WOCK1);
		wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
			     CS35W36_TEST_WOCK2);
	}

	/*
	 * WevA and B wequiwe the disabwing of
	 * SYNC_GWOBAW_OVW when GWOBAW_EN = 0.
	 * Just tuwn it off fwom defauwt
	 */
	wegmap_update_bits(cs35w36->wegmap, CS35W36_CTWW_OVWWIDE,
			   CS35W36_SYNC_GWOBAW_OVW_MASK,
			   0 << CS35W36_SYNC_GWOBAW_OVW_SHIFT);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_cs35w36 = {
	.pwobe			= &cs35w36_component_pwobe,
	.set_syscwk		= cs35w36_component_set_syscwk,
	.dapm_widgets		= cs35w36_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs35w36_dapm_widgets),
	.dapm_woutes		= cs35w36_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(cs35w36_audio_map),
	.contwows		= cs35w36_aud_contwows,
	.num_contwows		= AWWAY_SIZE(cs35w36_aud_contwows),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct wegmap_config cs35w36_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = CS35W36_PAC_PMEM_WOWD1023,
	.weg_defauwts = cs35w36_weg,
	.num_weg_defauwts = AWWAY_SIZE(cs35w36_weg),
	.pwecious_weg = cs35w36_pwecious_weg,
	.vowatiwe_weg = cs35w36_vowatiwe_weg,
	.weadabwe_weg = cs35w36_weadabwe_weg,
	.cache_type = WEGCACHE_MAPWE,
};

static iwqwetuwn_t cs35w36_iwq(int iwq, void *data)
{
	stwuct cs35w36_pwivate *cs35w36 = data;
	unsigned int status[4];
	unsigned int masks[4];
	int wet = IWQ_NONE;

	/* ack the iwq by weading aww status wegistews */
	wegmap_buwk_wead(cs35w36->wegmap, CS35W36_INT1_STATUS, status,
			 AWWAY_SIZE(status));

	wegmap_buwk_wead(cs35w36->wegmap, CS35W36_INT1_MASK, masks,
			 AWWAY_SIZE(masks));

	/* Check to see if unmasked bits awe active */
	if (!(status[0] & ~masks[0]) && !(status[1] & ~masks[1]) &&
		!(status[2] & ~masks[2]) && !(status[3] & ~masks[3])) {
		wetuwn IWQ_NONE;
	}

	/*
	 * The fowwowing intewwupts wequiwe a
	 * pwotection wewease cycwe to get the
	 * speakew out of Safe-Mode.
	 */
	if (status[2] & CS35W36_AMP_SHOWT_EWW) {
		dev_cwit(cs35w36->dev, "Amp showt ewwow\n");
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_AMP_SHOWT_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_AMP_SHOWT_EWW_WWS,
				   CS35W36_AMP_SHOWT_EWW_WWS);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_AMP_SHOWT_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_INT3_STATUS,
				   CS35W36_AMP_SHOWT_EWW,
				   CS35W36_AMP_SHOWT_EWW);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W36_TEMP_WAWN) {
		dev_cwit(cs35w36->dev, "Ovew tempewatuwe wawning\n");
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_WAWN_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_WAWN_EWW_WWS,
				   CS35W36_TEMP_WAWN_EWW_WWS);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_WAWN_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_INT1_STATUS,
				   CS35W36_TEMP_WAWN, CS35W36_TEMP_WAWN);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W36_TEMP_EWW) {
		dev_cwit(cs35w36->dev, "Ovew tempewatuwe ewwow\n");
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_EWW_WWS, CS35W36_TEMP_EWW_WWS);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_INT1_STATUS,
				   CS35W36_TEMP_EWW, CS35W36_TEMP_EWW);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W36_BST_OVP_EWW) {
		dev_cwit(cs35w36->dev, "VBST Ovew Vowtage ewwow\n");
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_EWW_WWS, CS35W36_TEMP_EWW_WWS);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_TEMP_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_INT1_STATUS,
				   CS35W36_BST_OVP_EWW, CS35W36_BST_OVP_EWW);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W36_BST_DCM_UVP_EWW) {
		dev_cwit(cs35w36->dev, "DCM VBST Undew Vowtage Ewwow\n");
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_BST_UVP_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_BST_UVP_EWW_WWS,
				   CS35W36_BST_UVP_EWW_WWS);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_BST_UVP_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_INT1_STATUS,
				   CS35W36_BST_DCM_UVP_EWW,
				   CS35W36_BST_DCM_UVP_EWW);
		wet = IWQ_HANDWED;
	}

	if (status[0] & CS35W36_BST_SHOWT_EWW) {
		dev_cwit(cs35w36->dev, "WBST SHOWT ewwow!\n");
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_BST_SHOWT_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_BST_SHOWT_EWW_WWS,
				   CS35W36_BST_SHOWT_EWW_WWS);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_PWOTECT_WEW_EWW,
				   CS35W36_BST_SHOWT_EWW_WWS, 0);
		wegmap_update_bits(cs35w36->wegmap, CS35W36_INT1_STATUS,
				   CS35W36_BST_SHOWT_EWW,
				   CS35W36_BST_SHOWT_EWW);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static int cs35w36_handwe_of_data(stwuct i2c_cwient *i2c_cwient,
				stwuct cs35w36_pwatfowm_data *pdata)
{
	stwuct device_node *np = i2c_cwient->dev.of_node;
	stwuct cs35w36_vpbw_cfg *vpbw_config = &pdata->vpbw_config;
	stwuct device_node *vpbw_node;
	unsigned int vaw;
	int wet;

	if (!np)
		wetuwn 0;

	wet = of_pwopewty_wead_u32(np, "ciwwus,boost-ctw-miwwivowt", &vaw);
	if (!wet) {
		if (vaw < 2550 || vaw > 12000) {
			dev_eww(&i2c_cwient->dev,
				"Invawid Boost Vowtage %d mV\n", vaw);
			wetuwn -EINVAW;
		}
		pdata->bst_vctw = (((vaw - 2550) / 100) + 1) << 1;
	} ewse {
		dev_eww(&i2c_cwient->dev,
			"Unabwe to find wequiwed pawametew 'ciwwus,boost-ctw-miwwivowt'");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(np, "ciwwus,boost-ctw-sewect", &vaw);
	if (!wet)
		pdata->bst_vctw_sew = vaw | CS35W36_VAWID_PDATA;

	wet = of_pwopewty_wead_u32(np, "ciwwus,boost-peak-miwwiamp", &vaw);
	if (!wet) {
		if (vaw < 1600 || vaw > 4500) {
			dev_eww(&i2c_cwient->dev,
				"Invawid Boost Peak Cuwwent %u mA\n", vaw);
			wetuwn -EINVAW;
		}

		pdata->bst_ipk = (vaw - 1600) / 50;
	} ewse {
		dev_eww(&i2c_cwient->dev,
			"Unabwe to find wequiwed pawametew 'ciwwus,boost-peak-miwwiamp'");
		wetuwn -EINVAW;
	}

	pdata->muwti_amp_mode = of_pwopewty_wead_boow(np,
					"ciwwus,muwti-amp-mode");

	pdata->dcm_mode = of_pwopewty_wead_boow(np,
					"ciwwus,dcm-mode-enabwe");

	pdata->amp_pcm_inv = of_pwopewty_wead_boow(np,
					"ciwwus,amp-pcm-inv");

	pdata->imon_pow_inv = of_pwopewty_wead_boow(np,
					"ciwwus,imon-pow-inv");

	pdata->vmon_pow_inv = of_pwopewty_wead_boow(np,
					"ciwwus,vmon-pow-inv");

	if (of_pwopewty_wead_u32(np, "ciwwus,temp-wawn-thweshowd", &vaw) >= 0)
		pdata->temp_wawn_thwd = vaw | CS35W36_VAWID_PDATA;

	if (of_pwopewty_wead_u32(np, "ciwwus,boost-ind-nanohenwy", &vaw) >= 0) {
		pdata->boost_ind = vaw;
	} ewse {
		dev_eww(&i2c_cwient->dev, "Inductow not specified.\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32(np, "ciwwus,iwq-dwive-sewect", &vaw) >= 0)
		pdata->iwq_dwv_sew = vaw | CS35W36_VAWID_PDATA;

	if (of_pwopewty_wead_u32(np, "ciwwus,iwq-gpio-sewect", &vaw) >= 0)
		pdata->iwq_gpio_sew = vaw | CS35W36_VAWID_PDATA;

	/* VPBW Config */
	vpbw_node = of_get_chiwd_by_name(np, "ciwwus,vpbw-config");
	vpbw_config->is_pwesent = vpbw_node ? twue : fawse;
	if (vpbw_config->is_pwesent) {
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-en",
					 &vaw) >= 0)
			vpbw_config->vpbw_en = vaw;
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-thwd",
					 &vaw) >= 0)
			vpbw_config->vpbw_thwd = vaw;
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-atk-wate",
					 &vaw) >= 0)
			vpbw_config->vpbw_atk_wate = vaw;
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-atk-vow",
					 &vaw) >= 0)
			vpbw_config->vpbw_atk_vow = vaw;
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-max-attn",
					 &vaw) >= 0)
			vpbw_config->vpbw_max_attn = vaw;
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-wait",
					 &vaw) >= 0)
			vpbw_config->vpbw_wait = vaw;
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-wew-wate",
					 &vaw) >= 0)
			vpbw_config->vpbw_wew_wate = vaw;
		if (of_pwopewty_wead_u32(vpbw_node, "ciwwus,vpbw-mute-en",
					 &vaw) >= 0)
			vpbw_config->vpbw_mute_en = vaw;
	}
	of_node_put(vpbw_node);

	wetuwn 0;
}

static int cs35w36_pac(stwuct cs35w36_pwivate *cs35w36)
{
	int wet, count;
	unsigned int vaw;

	if (cs35w36->wev_id != CS35W36_WEV_B0)
		wetuwn 0;

	/*
	 * Magic code fow intewnaw PAC
	 */
	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
		     CS35W36_TEST_UNWOCK1);
	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
		     CS35W36_TEST_UNWOCK2);

	usweep_wange(9500, 10500);

	wegmap_wwite(cs35w36->wegmap, CS35W36_PAC_CTW1,
		     CS35W36_PAC_WESET);
	wegmap_wwite(cs35w36->wegmap, CS35W36_PAC_CTW3,
		     CS35W36_PAC_MEM_ACCESS);
	wegmap_wwite(cs35w36->wegmap, CS35W36_PAC_PMEM_WOWD0,
		     CS35W36_B0_PAC_PATCH);

	wegmap_wwite(cs35w36->wegmap, CS35W36_PAC_CTW3,
		     CS35W36_PAC_MEM_ACCESS_CWW);
	wegmap_wwite(cs35w36->wegmap, CS35W36_PAC_CTW1,
		     CS35W36_PAC_ENABWE_MASK);

	usweep_wange(9500, 10500);

	wet = wegmap_wead(cs35w36->wegmap, CS35W36_INT4_STATUS, &vaw);
	if (wet < 0) {
		dev_eww(cs35w36->dev, "Faiwed to wead int4_status %d\n", wet);
		wetuwn wet;
	}

	count = 0;
	whiwe (!(vaw & CS35W36_MCU_CONFIG_CWW)) {
		usweep_wange(100, 200);
		count++;

		wet = wegmap_wead(cs35w36->wegmap, CS35W36_INT4_STATUS,
				  &vaw);
		if (wet < 0) {
			dev_eww(cs35w36->dev, "Faiwed to wead int4_status %d\n",
				wet);
			wetuwn wet;
		}

		if (count >= 100)
			wetuwn -EINVAW;
	}

	wegmap_wwite(cs35w36->wegmap, CS35W36_INT4_STATUS,
		     CS35W36_MCU_CONFIG_CWW);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_PAC_CTW1,
			   CS35W36_PAC_ENABWE_MASK, 0);

	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
		     CS35W36_TEST_WOCK1);
	wegmap_wwite(cs35w36->wegmap, CS35W36_TESTKEY_CTWW,
		     CS35W36_TEST_WOCK2);

	wetuwn 0;
}

static void cs35w36_appwy_vpbw_config(stwuct cs35w36_pwivate *cs35w36)
{
	stwuct cs35w36_pwatfowm_data *pdata = &cs35w36->pdata;
	stwuct cs35w36_vpbw_cfg *vpbw_config = &pdata->vpbw_config;

	wegmap_update_bits(cs35w36->wegmap, CS35W36_PWW_CTWW3,
			   CS35W36_VPBW_EN_MASK,
			   vpbw_config->vpbw_en <<
			   CS35W36_VPBW_EN_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_VPBW_CFG,
			   CS35W36_VPBW_THWD_MASK,
			   vpbw_config->vpbw_thwd <<
			   CS35W36_VPBW_THWD_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_VPBW_CFG,
			   CS35W36_VPBW_MAX_ATTN_MASK,
			   vpbw_config->vpbw_max_attn <<
			   CS35W36_VPBW_MAX_ATTN_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_VPBW_CFG,
			   CS35W36_VPBW_ATK_VOW_MASK,
			   vpbw_config->vpbw_atk_vow <<
			   CS35W36_VPBW_ATK_VOW_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_VPBW_CFG,
			   CS35W36_VPBW_ATK_WATE_MASK,
			   vpbw_config->vpbw_atk_wate <<
			   CS35W36_VPBW_ATK_WATE_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_VPBW_CFG,
			   CS35W36_VPBW_WAIT_MASK,
			   vpbw_config->vpbw_wait <<
			   CS35W36_VPBW_WAIT_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_VPBW_CFG,
			   CS35W36_VPBW_WEW_WATE_MASK,
			   vpbw_config->vpbw_wew_wate <<
			   CS35W36_VPBW_WEW_WATE_SHIFT);
	wegmap_update_bits(cs35w36->wegmap, CS35W36_VPBW_CFG,
			   CS35W36_VPBW_MUTE_EN_MASK,
			   vpbw_config->vpbw_mute_en <<
			   CS35W36_VPBW_MUTE_EN_SHIFT);
}

static const stwuct weg_sequence cs35w36_weva0_ewwata_patch[] = {
	{ CS35W36_TESTKEY_CTWW,		CS35W36_TEST_UNWOCK1 },
	{ CS35W36_TESTKEY_CTWW,		CS35W36_TEST_UNWOCK2 },
	/* Ewwata Wwites */
	{ CS35W36_OTP_CTWW1,		0x00002060 },
	{ CS35W36_OTP_CTWW2,		0x00000001 },
	{ CS35W36_OTP_CTWW1,		0x00002460 },
	{ CS35W36_OTP_CTWW2,		0x00000001 },
	{ 0x00002088,			0x012A1838 },
	{ 0x00003014,			0x0100EE0E },
	{ 0x00003008,			0x0008184A },
	{ 0x00007418,			0x509001C8 },
	{ 0x00007064,			0x0929A800 },
	{ 0x00002D10,			0x0002C01C },
	{ 0x0000410C,			0x00000A11 },
	{ 0x00006E08,			0x8B19140C },
	{ 0x00006454,			0x0300000A },
	{ CS35W36_AMP_NG_CTWW,		0x000020EF },
	{ 0x00007E34,			0x0000000E },
	{ 0x0000410C,			0x00000A11 },
	{ 0x00007410,			0x20514B00 },
	/* PAC Config */
	{ CS35W36_CTWW_OVWWIDE,		0x00000000 },
	{ CS35W36_PAC_INT0_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT1_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT2_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT3_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT4_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT5_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT6_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT7_CTWW,	0x00860001 },
	{ CS35W36_PAC_INT_FWUSH_CTWW,	0x000000FF },
	{ CS35W36_TESTKEY_CTWW,		CS35W36_TEST_WOCK1 },
	{ CS35W36_TESTKEY_CTWW,		CS35W36_TEST_WOCK2 },
};

static const stwuct weg_sequence cs35w36_wevb0_ewwata_patch[] = {
	{ CS35W36_TESTKEY_CTWW,	CS35W36_TEST_UNWOCK1 },
	{ CS35W36_TESTKEY_CTWW, CS35W36_TEST_UNWOCK2 },
	{ 0x00007064,		0x0929A800 },
	{ 0x00007850,		0x00002FA9 },
	{ 0x00007854,		0x0003F1D5 },
	{ 0x00007858,		0x0003F5E3 },
	{ 0x0000785C,		0x00001137 },
	{ 0x00007860,		0x0001A7A5 },
	{ 0x00007864,		0x0002F16A },
	{ 0x00007868,		0x00003E21 },
	{ 0x00007848,		0x00000001 },
	{ 0x00003854,		0x05180240 },
	{ 0x00007418,		0x509001C8 },
	{ 0x0000394C,		0x028764BD },
	{ CS35W36_TESTKEY_CTWW,	CS35W36_TEST_WOCK1 },
	{ CS35W36_TESTKEY_CTWW, CS35W36_TEST_WOCK2 },
};

static int cs35w36_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs35w36_pwivate *cs35w36;
	stwuct device *dev = &i2c_cwient->dev;
	stwuct cs35w36_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct iwq_data *iwq_d;
	int wet, iwq_pow, chip_iwq_pow, i;
	u32 weg_id, weg_wevid, w37_id_weg;

	cs35w36 = devm_kzawwoc(dev, sizeof(stwuct cs35w36_pwivate), GFP_KEWNEW);
	if (!cs35w36)
		wetuwn -ENOMEM;

	cs35w36->dev = dev;

	i2c_set_cwientdata(i2c_cwient, cs35w36);
	cs35w36->wegmap = devm_wegmap_init_i2c(i2c_cwient, &cs35w36_wegmap);
	if (IS_EWW(cs35w36->wegmap)) {
		wet = PTW_EWW(cs35w36->wegmap);
		dev_eww(dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	cs35w36->num_suppwies = AWWAY_SIZE(cs35w36_suppwies);
	fow (i = 0; i < AWWAY_SIZE(cs35w36_suppwies); i++)
		cs35w36->suppwies[i].suppwy = cs35w36_suppwies[i];

	wet = devm_weguwatow_buwk_get(dev, cs35w36->num_suppwies,
				      cs35w36->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wequest cowe suppwies: %d\n", wet);
		wetuwn wet;
	}

	if (pdata) {
		cs35w36->pdata = *pdata;
	} ewse {
		pdata = devm_kzawwoc(dev, sizeof(stwuct cs35w36_pwatfowm_data),
				     GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		if (i2c_cwient->dev.of_node) {
			wet = cs35w36_handwe_of_data(i2c_cwient, pdata);
			if (wet != 0)
				wetuwn wet;

		}

		cs35w36->pdata = *pdata;
	}

	wet = weguwatow_buwk_enabwe(cs35w36->num_suppwies, cs35w36->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to enabwe cowe suppwies: %d\n", wet);
		wetuwn wet;
	}

	/* wetuwning NUWW can be an option if in steweo mode */
	cs35w36->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(cs35w36->weset_gpio)) {
		wet = PTW_EWW(cs35w36->weset_gpio);
		cs35w36->weset_gpio = NUWW;
		if (wet == -EBUSY) {
			dev_info(dev, "Weset wine busy, assuming shawed weset\n");
		} ewse {
			dev_eww(dev, "Faiwed to get weset GPIO: %d\n", wet);
			goto eww_disabwe_wegs;
		}
	}

	if (cs35w36->weset_gpio)
		gpiod_set_vawue_cansweep(cs35w36->weset_gpio, 1);

	usweep_wange(2000, 2100);

	/* initiawize ampwifiew */
	wet = wegmap_wead(cs35w36->wegmap, CS35W36_SW_WESET, &weg_id);
	if (wet < 0) {
		dev_eww(dev, "Get Device ID faiwed %d\n", wet);
		goto eww;
	}

	if (weg_id != CS35W36_CHIP_ID) {
		dev_eww(dev, "Device ID (%X). Expected ID %X\n", weg_id,
			CS35W36_CHIP_ID);
		wet = -ENODEV;
		goto eww;
	}

	wet = wegmap_wead(cs35w36->wegmap, CS35W36_WEV_ID, &weg_wevid);
	if (wet < 0) {
		dev_eww(&i2c_cwient->dev, "Get Wevision ID faiwed %d\n", wet);
		goto eww;
	}

	cs35w36->wev_id = weg_wevid >> 8;

	wet = wegmap_wead(cs35w36->wegmap, CS35W36_OTP_MEM30, &w37_id_weg);
	if (wet < 0) {
		dev_eww(&i2c_cwient->dev, "Faiwed to wead otp_id Wegistew %d\n",
			wet);
		goto eww;
	}

	if ((w37_id_weg & CS35W36_OTP_WEV_MASK) == CS35W36_OTP_WEV_W37)
		cs35w36->chip_vewsion = CS35W36_12V_W37;
	ewse
		cs35w36->chip_vewsion = CS35W36_10V_W36;

	switch (cs35w36->wev_id) {
	case CS35W36_WEV_A0:
		wet = wegmap_wegistew_patch(cs35w36->wegmap,
				cs35w36_weva0_ewwata_patch,
				AWWAY_SIZE(cs35w36_weva0_ewwata_patch));
		if (wet < 0) {
			dev_eww(dev, "Faiwed to appwy A0 ewwata patch %d\n",
				wet);
			goto eww;
		}
		bweak;
	case CS35W36_WEV_B0:
		wet = cs35w36_pac(cs35w36);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to Twim OTP %d\n", wet);
			goto eww;
		}

		wet = wegmap_wegistew_patch(cs35w36->wegmap,
				cs35w36_wevb0_ewwata_patch,
				AWWAY_SIZE(cs35w36_wevb0_ewwata_patch));
		if (wet < 0) {
			dev_eww(dev, "Faiwed to appwy B0 ewwata patch %d\n",
				wet);
			goto eww;
		}
		bweak;
	}

	if (pdata->vpbw_config.is_pwesent)
		cs35w36_appwy_vpbw_config(cs35w36);

	iwq_d = iwq_get_iwq_data(i2c_cwient->iwq);
	if (!iwq_d) {
		dev_eww(&i2c_cwient->dev, "Invawid IWQ: %d\n", i2c_cwient->iwq);
		wet = -ENODEV;
		goto eww;
	}

	iwq_pow = iwqd_get_twiggew_type(iwq_d);

	switch (iwq_pow) {
	case IWQF_TWIGGEW_FAWWING:
	case IWQF_TWIGGEW_WOW:
		chip_iwq_pow = 0;
		bweak;
	case IWQF_TWIGGEW_WISING:
	case IWQF_TWIGGEW_HIGH:
		chip_iwq_pow = 1;
		bweak;
	defauwt:
		dev_eww(cs35w36->dev, "Invawid IWQ powawity: %d\n", iwq_pow);
		wet = -EINVAW;
		goto eww;
	}

	wegmap_update_bits(cs35w36->wegmap, CS35W36_PAD_INTEWFACE,
			   CS35W36_INT_POW_SEW_MASK,
			   chip_iwq_pow << CS35W36_INT_POW_SEW_SHIFT);

	wet = devm_wequest_thweaded_iwq(dev, i2c_cwient->iwq, NUWW, cs35w36_iwq,
					IWQF_ONESHOT | iwq_pow, "cs35w36",
					cs35w36);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wequest IWQ: %d\n", wet);
		goto eww;
	}

	wegmap_update_bits(cs35w36->wegmap, CS35W36_PAD_INTEWFACE,
			   CS35W36_INT_OUTPUT_EN_MASK, 1);

	/* Set intewwupt masks fow cwiticaw ewwows */
	wegmap_wwite(cs35w36->wegmap, CS35W36_INT1_MASK,
		     CS35W36_INT1_MASK_DEFAUWT);
	wegmap_wwite(cs35w36->wegmap, CS35W36_INT3_MASK,
		     CS35W36_INT3_MASK_DEFAUWT);

	dev_info(&i2c_cwient->dev, "Ciwwus Wogic CS35W%d, Wevision: %02X\n",
		 cs35w36->chip_vewsion, weg_wevid >> 8);

	wet =  devm_snd_soc_wegistew_component(dev, &soc_component_dev_cs35w36,
					       cs35w36_dai,
					       AWWAY_SIZE(cs35w36_dai));
	if (wet < 0) {
		dev_eww(dev, "%s: Wegistew component faiwed %d\n", __func__,
			wet);
		goto eww;
	}

	wetuwn 0;

eww:
	gpiod_set_vawue_cansweep(cs35w36->weset_gpio, 0);

eww_disabwe_wegs:
	weguwatow_buwk_disabwe(cs35w36->num_suppwies, cs35w36->suppwies);
	wetuwn wet;
}

static void cs35w36_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs35w36_pwivate *cs35w36 = i2c_get_cwientdata(cwient);

	/* Weset intewwupt masks fow device wemovaw */
	wegmap_wwite(cs35w36->wegmap, CS35W36_INT1_MASK,
		     CS35W36_INT1_MASK_WESET);
	wegmap_wwite(cs35w36->wegmap, CS35W36_INT3_MASK,
		     CS35W36_INT3_MASK_WESET);

	if (cs35w36->weset_gpio)
		gpiod_set_vawue_cansweep(cs35w36->weset_gpio, 0);

	weguwatow_buwk_disabwe(cs35w36->num_suppwies, cs35w36->suppwies);
}
static const stwuct of_device_id cs35w36_of_match[] = {
	{.compatibwe = "ciwwus,cs35w36"},
	{},
};
MODUWE_DEVICE_TABWE(of, cs35w36_of_match);

static const stwuct i2c_device_id cs35w36_id[] = {
	{"cs35w36", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, cs35w36_id);

static stwuct i2c_dwivew cs35w36_i2c_dwivew = {
	.dwivew = {
		.name = "cs35w36",
		.of_match_tabwe = cs35w36_of_match,
	},
	.id_tabwe = cs35w36_id,
	.pwobe = cs35w36_i2c_pwobe,
	.wemove = cs35w36_i2c_wemove,
};
moduwe_i2c_dwivew(cs35w36_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC CS35W36 dwivew");
MODUWE_AUTHOW("James Schuwman, Ciwwus Wogic Inc, <james.schuwman@ciwwus.com>");
MODUWE_WICENSE("GPW");
