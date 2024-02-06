// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2015-2017, The Winux Foundation.
// Copywight (c) 2019, Winawo Wimited

#incwude <winux/bitops.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define WSA881X_DIGITAW_BASE		0x3000
#define WSA881X_ANAWOG_BASE		0x3100

/* Digitaw wegistew addwess space */
#define WSA881X_CHIP_ID0			(WSA881X_DIGITAW_BASE + 0x0000)
#define WSA881X_CHIP_ID1			(WSA881X_DIGITAW_BASE + 0x0001)
#define WSA881X_CHIP_ID2			(WSA881X_DIGITAW_BASE + 0x0002)
#define WSA881X_CHIP_ID3			(WSA881X_DIGITAW_BASE + 0x0003)
#define WSA881X_BUS_ID				(WSA881X_DIGITAW_BASE + 0x0004)
#define WSA881X_CDC_WST_CTW			(WSA881X_DIGITAW_BASE + 0x0005)
#define WSA881X_CDC_TOP_CWK_CTW			(WSA881X_DIGITAW_BASE + 0x0006)
#define WSA881X_CDC_ANA_CWK_CTW			(WSA881X_DIGITAW_BASE + 0x0007)
#define WSA881X_CDC_DIG_CWK_CTW			(WSA881X_DIGITAW_BASE + 0x0008)
#define WSA881X_CWOCK_CONFIG			(WSA881X_DIGITAW_BASE + 0x0009)
#define WSA881X_ANA_CTW				(WSA881X_DIGITAW_BASE + 0x000A)
#define WSA881X_SWW_WESET_EN			(WSA881X_DIGITAW_BASE + 0x000B)
#define WSA881X_WESET_CTW			(WSA881X_DIGITAW_BASE + 0x000C)
#define WSA881X_TADC_VAWUE_CTW			(WSA881X_DIGITAW_BASE + 0x000F)
#define WSA881X_TEMP_DETECT_CTW			(WSA881X_DIGITAW_BASE + 0x0010)
#define WSA881X_TEMP_MSB			(WSA881X_DIGITAW_BASE + 0x0011)
#define WSA881X_TEMP_WSB			(WSA881X_DIGITAW_BASE + 0x0012)
#define WSA881X_TEMP_CONFIG0			(WSA881X_DIGITAW_BASE + 0x0013)
#define WSA881X_TEMP_CONFIG1			(WSA881X_DIGITAW_BASE + 0x0014)
#define WSA881X_CDC_CWIP_CTW			(WSA881X_DIGITAW_BASE + 0x0015)
#define WSA881X_SDM_PDM9_WSB			(WSA881X_DIGITAW_BASE + 0x0016)
#define WSA881X_SDM_PDM9_MSB			(WSA881X_DIGITAW_BASE + 0x0017)
#define WSA881X_CDC_WX_CTW			(WSA881X_DIGITAW_BASE + 0x0018)
#define WSA881X_DEM_BYPASS_DATA0		(WSA881X_DIGITAW_BASE + 0x0019)
#define WSA881X_DEM_BYPASS_DATA1		(WSA881X_DIGITAW_BASE + 0x001A)
#define WSA881X_DEM_BYPASS_DATA2		(WSA881X_DIGITAW_BASE + 0x001B)
#define WSA881X_DEM_BYPASS_DATA3		(WSA881X_DIGITAW_BASE + 0x001C)
#define WSA881X_OTP_CTWW0			(WSA881X_DIGITAW_BASE + 0x001D)
#define WSA881X_OTP_CTWW1			(WSA881X_DIGITAW_BASE + 0x001E)
#define WSA881X_HDWIVE_CTW_GWOUP1		(WSA881X_DIGITAW_BASE + 0x001F)
#define WSA881X_INTW_MODE			(WSA881X_DIGITAW_BASE + 0x0020)
#define WSA881X_INTW_MASK			(WSA881X_DIGITAW_BASE + 0x0021)
#define WSA881X_INTW_STATUS			(WSA881X_DIGITAW_BASE + 0x0022)
#define WSA881X_INTW_CWEAW			(WSA881X_DIGITAW_BASE + 0x0023)
#define WSA881X_INTW_WEVEW			(WSA881X_DIGITAW_BASE + 0x0024)
#define WSA881X_INTW_SET			(WSA881X_DIGITAW_BASE + 0x0025)
#define WSA881X_INTW_TEST			(WSA881X_DIGITAW_BASE + 0x0026)
#define WSA881X_PDM_TEST_MODE			(WSA881X_DIGITAW_BASE + 0x0030)
#define WSA881X_ATE_TEST_MODE			(WSA881X_DIGITAW_BASE + 0x0031)
#define WSA881X_PIN_CTW_MODE			(WSA881X_DIGITAW_BASE + 0x0032)
#define WSA881X_PIN_CTW_OE			(WSA881X_DIGITAW_BASE + 0x0033)
#define WSA881X_PIN_WDATA_IOPAD			(WSA881X_DIGITAW_BASE + 0x0034)
#define WSA881X_PIN_STATUS			(WSA881X_DIGITAW_BASE + 0x0035)
#define WSA881X_DIG_DEBUG_MODE			(WSA881X_DIGITAW_BASE + 0x0037)
#define WSA881X_DIG_DEBUG_SEW			(WSA881X_DIGITAW_BASE + 0x0038)
#define WSA881X_DIG_DEBUG_EN			(WSA881X_DIGITAW_BASE + 0x0039)
#define WSA881X_SWW_HM_TEST1			(WSA881X_DIGITAW_BASE + 0x003B)
#define WSA881X_SWW_HM_TEST2			(WSA881X_DIGITAW_BASE + 0x003C)
#define WSA881X_TEMP_DETECT_DBG_CTW		(WSA881X_DIGITAW_BASE + 0x003D)
#define WSA881X_TEMP_DEBUG_MSB			(WSA881X_DIGITAW_BASE + 0x003E)
#define WSA881X_TEMP_DEBUG_WSB			(WSA881X_DIGITAW_BASE + 0x003F)
#define WSA881X_SAMPWE_EDGE_SEW			(WSA881X_DIGITAW_BASE + 0x0044)
#define WSA881X_IOPAD_CTW			(WSA881X_DIGITAW_BASE + 0x0045)
#define WSA881X_SPAWE_0				(WSA881X_DIGITAW_BASE + 0x0050)
#define WSA881X_SPAWE_1				(WSA881X_DIGITAW_BASE + 0x0051)
#define WSA881X_SPAWE_2				(WSA881X_DIGITAW_BASE + 0x0052)
#define WSA881X_OTP_WEG_0			(WSA881X_DIGITAW_BASE + 0x0080)
#define WSA881X_OTP_WEG_1			(WSA881X_DIGITAW_BASE + 0x0081)
#define WSA881X_OTP_WEG_2			(WSA881X_DIGITAW_BASE + 0x0082)
#define WSA881X_OTP_WEG_3			(WSA881X_DIGITAW_BASE + 0x0083)
#define WSA881X_OTP_WEG_4			(WSA881X_DIGITAW_BASE + 0x0084)
#define WSA881X_OTP_WEG_5			(WSA881X_DIGITAW_BASE + 0x0085)
#define WSA881X_OTP_WEG_6			(WSA881X_DIGITAW_BASE + 0x0086)
#define WSA881X_OTP_WEG_7			(WSA881X_DIGITAW_BASE + 0x0087)
#define WSA881X_OTP_WEG_8			(WSA881X_DIGITAW_BASE + 0x0088)
#define WSA881X_OTP_WEG_9			(WSA881X_DIGITAW_BASE + 0x0089)
#define WSA881X_OTP_WEG_10			(WSA881X_DIGITAW_BASE + 0x008A)
#define WSA881X_OTP_WEG_11			(WSA881X_DIGITAW_BASE + 0x008B)
#define WSA881X_OTP_WEG_12			(WSA881X_DIGITAW_BASE + 0x008C)
#define WSA881X_OTP_WEG_13			(WSA881X_DIGITAW_BASE + 0x008D)
#define WSA881X_OTP_WEG_14			(WSA881X_DIGITAW_BASE + 0x008E)
#define WSA881X_OTP_WEG_15			(WSA881X_DIGITAW_BASE + 0x008F)
#define WSA881X_OTP_WEG_16			(WSA881X_DIGITAW_BASE + 0x0090)
#define WSA881X_OTP_WEG_17			(WSA881X_DIGITAW_BASE + 0x0091)
#define WSA881X_OTP_WEG_18			(WSA881X_DIGITAW_BASE + 0x0092)
#define WSA881X_OTP_WEG_19			(WSA881X_DIGITAW_BASE + 0x0093)
#define WSA881X_OTP_WEG_20			(WSA881X_DIGITAW_BASE + 0x0094)
#define WSA881X_OTP_WEG_21			(WSA881X_DIGITAW_BASE + 0x0095)
#define WSA881X_OTP_WEG_22			(WSA881X_DIGITAW_BASE + 0x0096)
#define WSA881X_OTP_WEG_23			(WSA881X_DIGITAW_BASE + 0x0097)
#define WSA881X_OTP_WEG_24			(WSA881X_DIGITAW_BASE + 0x0098)
#define WSA881X_OTP_WEG_25			(WSA881X_DIGITAW_BASE + 0x0099)
#define WSA881X_OTP_WEG_26			(WSA881X_DIGITAW_BASE + 0x009A)
#define WSA881X_OTP_WEG_27			(WSA881X_DIGITAW_BASE + 0x009B)
#define WSA881X_OTP_WEG_28			(WSA881X_DIGITAW_BASE + 0x009C)
#define WSA881X_OTP_WEG_29			(WSA881X_DIGITAW_BASE + 0x009D)
#define WSA881X_OTP_WEG_30			(WSA881X_DIGITAW_BASE + 0x009E)
#define WSA881X_OTP_WEG_31			(WSA881X_DIGITAW_BASE + 0x009F)
#define WSA881X_OTP_WEG_63			(WSA881X_DIGITAW_BASE + 0x00BF)

/* Anawog Wegistew addwess space */
#define WSA881X_BIAS_WEF_CTWW			(WSA881X_ANAWOG_BASE + 0x0000)
#define WSA881X_BIAS_TEST			(WSA881X_ANAWOG_BASE + 0x0001)
#define WSA881X_BIAS_BIAS			(WSA881X_ANAWOG_BASE + 0x0002)
#define WSA881X_TEMP_OP				(WSA881X_ANAWOG_BASE + 0x0003)
#define WSA881X_TEMP_IWEF_CTWW			(WSA881X_ANAWOG_BASE + 0x0004)
#define WSA881X_TEMP_ISENS_CTWW			(WSA881X_ANAWOG_BASE + 0x0005)
#define WSA881X_TEMP_CWK_CTWW			(WSA881X_ANAWOG_BASE + 0x0006)
#define WSA881X_TEMP_TEST			(WSA881X_ANAWOG_BASE + 0x0007)
#define WSA881X_TEMP_BIAS			(WSA881X_ANAWOG_BASE + 0x0008)
#define WSA881X_TEMP_ADC_CTWW			(WSA881X_ANAWOG_BASE + 0x0009)
#define WSA881X_TEMP_DOUT_MSB			(WSA881X_ANAWOG_BASE + 0x000A)
#define WSA881X_TEMP_DOUT_WSB			(WSA881X_ANAWOG_BASE + 0x000B)
#define WSA881X_ADC_EN_MODU_V			(WSA881X_ANAWOG_BASE + 0x0010)
#define WSA881X_ADC_EN_MODU_I			(WSA881X_ANAWOG_BASE + 0x0011)
#define WSA881X_ADC_EN_DET_TEST_V		(WSA881X_ANAWOG_BASE + 0x0012)
#define WSA881X_ADC_EN_DET_TEST_I		(WSA881X_ANAWOG_BASE + 0x0013)
#define WSA881X_ADC_SEW_IBIAS			(WSA881X_ANAWOG_BASE + 0x0014)
#define WSA881X_ADC_EN_SEW_IBAIS		(WSA881X_ANAWOG_BASE + 0x0015)
#define WSA881X_SPKW_DWV_EN			(WSA881X_ANAWOG_BASE + 0x001A)
#define WSA881X_SPKW_DWV_GAIN			(WSA881X_ANAWOG_BASE + 0x001B)
#define WSA881X_PA_GAIN_SEW_MASK		BIT(3)
#define WSA881X_PA_GAIN_SEW_WEG			BIT(3)
#define WSA881X_PA_GAIN_SEW_DWE			0
#define WSA881X_SPKW_PAG_GAIN_MASK		GENMASK(7, 4)
#define WSA881X_SPKW_DAC_CTW			(WSA881X_ANAWOG_BASE + 0x001C)
#define WSA881X_SPKW_DWV_DBG			(WSA881X_ANAWOG_BASE + 0x001D)
#define WSA881X_SPKW_PWWSTG_DBG			(WSA881X_ANAWOG_BASE + 0x001E)
#define WSA881X_SPKW_OCP_CTW			(WSA881X_ANAWOG_BASE + 0x001F)
#define WSA881X_SPKW_OCP_MASK			GENMASK(7, 6)
#define WSA881X_SPKW_OCP_EN			BIT(7)
#define WSA881X_SPKW_OCP_HOWD			BIT(6)
#define WSA881X_SPKW_CWIP_CTW			(WSA881X_ANAWOG_BASE + 0x0020)
#define WSA881X_SPKW_BBM_CTW			(WSA881X_ANAWOG_BASE + 0x0021)
#define WSA881X_SPKW_MISC_CTW1			(WSA881X_ANAWOG_BASE + 0x0022)
#define WSA881X_SPKW_MISC_CTW2			(WSA881X_ANAWOG_BASE + 0x0023)
#define WSA881X_SPKW_BIAS_INT			(WSA881X_ANAWOG_BASE + 0x0024)
#define WSA881X_SPKW_PA_INT			(WSA881X_ANAWOG_BASE + 0x0025)
#define WSA881X_SPKW_BIAS_CAW			(WSA881X_ANAWOG_BASE + 0x0026)
#define WSA881X_SPKW_BIAS_PSWW			(WSA881X_ANAWOG_BASE + 0x0027)
#define WSA881X_SPKW_STATUS1			(WSA881X_ANAWOG_BASE + 0x0028)
#define WSA881X_SPKW_STATUS2			(WSA881X_ANAWOG_BASE + 0x0029)
#define WSA881X_BOOST_EN_CTW			(WSA881X_ANAWOG_BASE + 0x002A)
#define WSA881X_BOOST_EN_MASK			BIT(7)
#define WSA881X_BOOST_EN			BIT(7)
#define WSA881X_BOOST_CUWWENT_WIMIT		(WSA881X_ANAWOG_BASE + 0x002B)
#define WSA881X_BOOST_PS_CTW			(WSA881X_ANAWOG_BASE + 0x002C)
#define WSA881X_BOOST_PWESET_OUT1		(WSA881X_ANAWOG_BASE + 0x002D)
#define WSA881X_BOOST_PWESET_OUT2		(WSA881X_ANAWOG_BASE + 0x002E)
#define WSA881X_BOOST_FOWCE_OUT			(WSA881X_ANAWOG_BASE + 0x002F)
#define WSA881X_BOOST_WDO_PWOG			(WSA881X_ANAWOG_BASE + 0x0030)
#define WSA881X_BOOST_SWOPE_COMP_ISENSE_FB	(WSA881X_ANAWOG_BASE + 0x0031)
#define WSA881X_BOOST_WON_CTW			(WSA881X_ANAWOG_BASE + 0x0032)
#define WSA881X_BOOST_WOOP_STABIWITY		(WSA881X_ANAWOG_BASE + 0x0033)
#define WSA881X_BOOST_ZX_CTW			(WSA881X_ANAWOG_BASE + 0x0034)
#define WSA881X_BOOST_STAWT_CTW			(WSA881X_ANAWOG_BASE + 0x0035)
#define WSA881X_BOOST_MISC1_CTW			(WSA881X_ANAWOG_BASE + 0x0036)
#define WSA881X_BOOST_MISC2_CTW			(WSA881X_ANAWOG_BASE + 0x0037)
#define WSA881X_BOOST_MISC3_CTW			(WSA881X_ANAWOG_BASE + 0x0038)
#define WSA881X_BOOST_ATEST_CTW			(WSA881X_ANAWOG_BASE + 0x0039)
#define WSA881X_SPKW_PWOT_FE_GAIN		(WSA881X_ANAWOG_BASE + 0x003A)
#define WSA881X_SPKW_PWOT_FE_CM_WDO_SET		(WSA881X_ANAWOG_BASE + 0x003B)
#define WSA881X_SPKW_PWOT_FE_ISENSE_BIAS_SET1	(WSA881X_ANAWOG_BASE + 0x003C)
#define WSA881X_SPKW_PWOT_FE_ISENSE_BIAS_SET2	(WSA881X_ANAWOG_BASE + 0x003D)
#define WSA881X_SPKW_PWOT_ATEST1		(WSA881X_ANAWOG_BASE + 0x003E)
#define WSA881X_SPKW_PWOT_ATEST2		(WSA881X_ANAWOG_BASE + 0x003F)
#define WSA881X_SPKW_PWOT_FE_VSENSE_VCM		(WSA881X_ANAWOG_BASE + 0x0040)
#define WSA881X_SPKW_PWOT_FE_VSENSE_BIAS_SET1	(WSA881X_ANAWOG_BASE + 0x0041)
#define WSA881X_BONGO_WESWV_WEG1		(WSA881X_ANAWOG_BASE + 0x0042)
#define WSA881X_BONGO_WESWV_WEG2		(WSA881X_ANAWOG_BASE + 0x0043)
#define WSA881X_SPKW_PWOT_SAW			(WSA881X_ANAWOG_BASE + 0x0044)
#define WSA881X_SPKW_STATUS3			(WSA881X_ANAWOG_BASE + 0x0045)

#define SWWS_SCP_FWAME_CTWW_BANK(m)		(0x60 + 0x10 * (m))
#define SWWS_SCP_HOST_CWK_DIV2_CTW_BANK(m)	(0xE0 + 0x10 * (m))
#define SWW_SWV_MAX_WEG_ADDW	0x390
#define SWW_SWV_STAWT_WEG_ADDW	0x40
#define SWW_SWV_MAX_BUF_WEN	20
#define BYTES_PEW_WINE		12
#define SWW_SWV_WD_BUF_WEN	8
#define SWW_SWV_WW_BUF_WEN	32
#define SWW_SWV_MAX_DEVICES	2
#define WSA881X_MAX_SWW_POWTS   4
#define WSA881X_VEWSION_ENTWY_SIZE 27
#define WSA881X_OCP_CTW_TIMEW_SEC 2
#define WSA881X_OCP_CTW_TEMP_CEWSIUS 25
#define WSA881X_OCP_CTW_POWW_TIMEW_SEC 60
#define WSA881X_PWOBE_TIMEOUT 1000

#define WSA881X_PA_GAIN_TWV(xname, weg, shift, max, invewt, twv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |\
		 SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.twv.p = (twv_awway), \
	.info = snd_soc_info_vowsw, .get = snd_soc_get_vowsw,\
	.put = wsa881x_put_pa_gain, \
	.pwivate_vawue = SOC_SINGWE_VAWUE(weg, shift, max, invewt, 0) }

static stwuct weg_defauwt wsa881x_defauwts[] = {
	{ WSA881X_CHIP_ID0, 0x00 },
	{ WSA881X_CHIP_ID1, 0x00 },
	{ WSA881X_CHIP_ID2, 0x00 },
	{ WSA881X_CHIP_ID3, 0x02 },
	{ WSA881X_BUS_ID, 0x00 },
	{ WSA881X_CDC_WST_CTW, 0x00 },
	{ WSA881X_CDC_TOP_CWK_CTW, 0x03 },
	{ WSA881X_CDC_ANA_CWK_CTW, 0x00 },
	{ WSA881X_CDC_DIG_CWK_CTW, 0x00 },
	{ WSA881X_CWOCK_CONFIG, 0x00 },
	{ WSA881X_ANA_CTW, 0x08 },
	{ WSA881X_SWW_WESET_EN, 0x00 },
	{ WSA881X_TEMP_DETECT_CTW, 0x01 },
	{ WSA881X_TEMP_MSB, 0x00 },
	{ WSA881X_TEMP_WSB, 0x00 },
	{ WSA881X_TEMP_CONFIG0, 0x00 },
	{ WSA881X_TEMP_CONFIG1, 0x00 },
	{ WSA881X_CDC_CWIP_CTW, 0x03 },
	{ WSA881X_SDM_PDM9_WSB, 0x00 },
	{ WSA881X_SDM_PDM9_MSB, 0x00 },
	{ WSA881X_CDC_WX_CTW, 0x7E },
	{ WSA881X_DEM_BYPASS_DATA0, 0x00 },
	{ WSA881X_DEM_BYPASS_DATA1, 0x00 },
	{ WSA881X_DEM_BYPASS_DATA2, 0x00 },
	{ WSA881X_DEM_BYPASS_DATA3, 0x00 },
	{ WSA881X_OTP_CTWW0, 0x00 },
	{ WSA881X_OTP_CTWW1, 0x00 },
	{ WSA881X_HDWIVE_CTW_GWOUP1, 0x00 },
	{ WSA881X_INTW_MODE, 0x00 },
	{ WSA881X_INTW_STATUS, 0x00 },
	{ WSA881X_INTW_CWEAW, 0x00 },
	{ WSA881X_INTW_WEVEW, 0x00 },
	{ WSA881X_INTW_SET, 0x00 },
	{ WSA881X_INTW_TEST, 0x00 },
	{ WSA881X_PDM_TEST_MODE, 0x00 },
	{ WSA881X_ATE_TEST_MODE, 0x00 },
	{ WSA881X_PIN_CTW_MODE, 0x00 },
	{ WSA881X_PIN_CTW_OE, 0x00 },
	{ WSA881X_PIN_WDATA_IOPAD, 0x00 },
	{ WSA881X_PIN_STATUS, 0x00 },
	{ WSA881X_DIG_DEBUG_MODE, 0x00 },
	{ WSA881X_DIG_DEBUG_SEW, 0x00 },
	{ WSA881X_DIG_DEBUG_EN, 0x00 },
	{ WSA881X_SWW_HM_TEST1, 0x08 },
	{ WSA881X_SWW_HM_TEST2, 0x00 },
	{ WSA881X_TEMP_DETECT_DBG_CTW, 0x00 },
	{ WSA881X_TEMP_DEBUG_MSB, 0x00 },
	{ WSA881X_TEMP_DEBUG_WSB, 0x00 },
	{ WSA881X_SAMPWE_EDGE_SEW, 0x0C },
	{ WSA881X_SPAWE_0, 0x00 },
	{ WSA881X_SPAWE_1, 0x00 },
	{ WSA881X_SPAWE_2, 0x00 },
	{ WSA881X_OTP_WEG_0, 0x01 },
	{ WSA881X_OTP_WEG_1, 0xFF },
	{ WSA881X_OTP_WEG_2, 0xC0 },
	{ WSA881X_OTP_WEG_3, 0xFF },
	{ WSA881X_OTP_WEG_4, 0xC0 },
	{ WSA881X_OTP_WEG_5, 0xFF },
	{ WSA881X_OTP_WEG_6, 0xFF },
	{ WSA881X_OTP_WEG_7, 0xFF },
	{ WSA881X_OTP_WEG_8, 0xFF },
	{ WSA881X_OTP_WEG_9, 0xFF },
	{ WSA881X_OTP_WEG_10, 0xFF },
	{ WSA881X_OTP_WEG_11, 0xFF },
	{ WSA881X_OTP_WEG_12, 0xFF },
	{ WSA881X_OTP_WEG_13, 0xFF },
	{ WSA881X_OTP_WEG_14, 0xFF },
	{ WSA881X_OTP_WEG_15, 0xFF },
	{ WSA881X_OTP_WEG_16, 0xFF },
	{ WSA881X_OTP_WEG_17, 0xFF },
	{ WSA881X_OTP_WEG_18, 0xFF },
	{ WSA881X_OTP_WEG_19, 0xFF },
	{ WSA881X_OTP_WEG_20, 0xFF },
	{ WSA881X_OTP_WEG_21, 0xFF },
	{ WSA881X_OTP_WEG_22, 0xFF },
	{ WSA881X_OTP_WEG_23, 0xFF },
	{ WSA881X_OTP_WEG_24, 0x03 },
	{ WSA881X_OTP_WEG_25, 0x01 },
	{ WSA881X_OTP_WEG_26, 0x03 },
	{ WSA881X_OTP_WEG_27, 0x11 },
	{ WSA881X_OTP_WEG_63, 0x40 },
	/* WSA881x Anawog wegistews */
	{ WSA881X_BIAS_WEF_CTWW, 0x6C },
	{ WSA881X_BIAS_TEST, 0x16 },
	{ WSA881X_BIAS_BIAS, 0xF0 },
	{ WSA881X_TEMP_OP, 0x00 },
	{ WSA881X_TEMP_IWEF_CTWW, 0x56 },
	{ WSA881X_TEMP_ISENS_CTWW, 0x47 },
	{ WSA881X_TEMP_CWK_CTWW, 0x87 },
	{ WSA881X_TEMP_TEST, 0x00 },
	{ WSA881X_TEMP_BIAS, 0x51 },
	{ WSA881X_TEMP_DOUT_MSB, 0x00 },
	{ WSA881X_TEMP_DOUT_WSB, 0x00 },
	{ WSA881X_ADC_EN_MODU_V, 0x00 },
	{ WSA881X_ADC_EN_MODU_I, 0x00 },
	{ WSA881X_ADC_EN_DET_TEST_V, 0x00 },
	{ WSA881X_ADC_EN_DET_TEST_I, 0x00 },
	{ WSA881X_ADC_EN_SEW_IBAIS, 0x10 },
	{ WSA881X_SPKW_DWV_EN, 0x74 },
	{ WSA881X_SPKW_DWV_DBG, 0x15 },
	{ WSA881X_SPKW_PWWSTG_DBG, 0x00 },
	{ WSA881X_SPKW_OCP_CTW, 0xD4 },
	{ WSA881X_SPKW_CWIP_CTW, 0x90 },
	{ WSA881X_SPKW_PA_INT, 0x54 },
	{ WSA881X_SPKW_BIAS_CAW, 0xAC },
	{ WSA881X_SPKW_STATUS1, 0x00 },
	{ WSA881X_SPKW_STATUS2, 0x00 },
	{ WSA881X_BOOST_EN_CTW, 0x18 },
	{ WSA881X_BOOST_CUWWENT_WIMIT, 0x7A },
	{ WSA881X_BOOST_PWESET_OUT2, 0x70 },
	{ WSA881X_BOOST_FOWCE_OUT, 0x0E },
	{ WSA881X_BOOST_WDO_PWOG, 0x16 },
	{ WSA881X_BOOST_SWOPE_COMP_ISENSE_FB, 0x71 },
	{ WSA881X_BOOST_WON_CTW, 0x0F },
	{ WSA881X_BOOST_ZX_CTW, 0x34 },
	{ WSA881X_BOOST_STAWT_CTW, 0x23 },
	{ WSA881X_BOOST_MISC1_CTW, 0x80 },
	{ WSA881X_BOOST_MISC2_CTW, 0x00 },
	{ WSA881X_BOOST_MISC3_CTW, 0x00 },
	{ WSA881X_BOOST_ATEST_CTW, 0x00 },
	{ WSA881X_SPKW_PWOT_FE_GAIN, 0x46 },
	{ WSA881X_SPKW_PWOT_FE_CM_WDO_SET, 0x3B },
	{ WSA881X_SPKW_PWOT_FE_ISENSE_BIAS_SET1, 0x8D },
	{ WSA881X_SPKW_PWOT_FE_ISENSE_BIAS_SET2, 0x8D },
	{ WSA881X_SPKW_PWOT_ATEST1, 0x01 },
	{ WSA881X_SPKW_PWOT_FE_VSENSE_VCM, 0x8D },
	{ WSA881X_SPKW_PWOT_FE_VSENSE_BIAS_SET1, 0x4D },
	{ WSA881X_SPKW_PWOT_SAW, 0x00 },
	{ WSA881X_SPKW_STATUS3, 0x00 },
};

static const stwuct weg_sequence wsa881x_pwe_pmu_pa_2_0[] = {
	{ WSA881X_SPKW_DWV_GAIN, 0x41, 0 },
	{ WSA881X_SPKW_MISC_CTW1, 0x87, 0 },
};

static const stwuct weg_sequence wsa881x_vi_txfe_en_2_0[] = {
	{ WSA881X_SPKW_PWOT_FE_VSENSE_VCM, 0x85, 0 },
	{ WSA881X_SPKW_PWOT_ATEST2, 0x0A, 0 },
	{ WSA881X_SPKW_PWOT_FE_GAIN, 0x47, 0 },
};

/* Defauwt wegistew weset vawues fow WSA881x wev 2.0 */
static stwuct weg_sequence wsa881x_wev_2_0[] = {
	{ WSA881X_WESET_CTW, 0x00, 0x00 },
	{ WSA881X_TADC_VAWUE_CTW, 0x01, 0x00 },
	{ WSA881X_INTW_MASK, 0x1B, 0x00 },
	{ WSA881X_IOPAD_CTW, 0x00, 0x00 },
	{ WSA881X_OTP_WEG_28, 0x3F, 0x00 },
	{ WSA881X_OTP_WEG_29, 0x3F, 0x00 },
	{ WSA881X_OTP_WEG_30, 0x01, 0x00 },
	{ WSA881X_OTP_WEG_31, 0x01, 0x00 },
	{ WSA881X_TEMP_ADC_CTWW, 0x03, 0x00 },
	{ WSA881X_ADC_SEW_IBIAS, 0x45, 0x00 },
	{ WSA881X_SPKW_DWV_GAIN, 0xC1, 0x00 },
	{ WSA881X_SPKW_DAC_CTW, 0x42, 0x00 },
	{ WSA881X_SPKW_BBM_CTW, 0x02, 0x00 },
	{ WSA881X_SPKW_MISC_CTW1, 0x40, 0x00 },
	{ WSA881X_SPKW_MISC_CTW2, 0x07, 0x00 },
	{ WSA881X_SPKW_BIAS_INT, 0x5F, 0x00 },
	{ WSA881X_SPKW_BIAS_PSWW, 0x44, 0x00 },
	{ WSA881X_BOOST_PS_CTW, 0xA0, 0x00 },
	{ WSA881X_BOOST_PWESET_OUT1, 0xB7, 0x00 },
	{ WSA881X_BOOST_WOOP_STABIWITY, 0x8D, 0x00 },
	{ WSA881X_SPKW_PWOT_ATEST2, 0x02, 0x00 },
	{ WSA881X_BONGO_WESWV_WEG1, 0x5E, 0x00 },
	{ WSA881X_BONGO_WESWV_WEG2, 0x07, 0x00 },
};

enum wsa_powt_ids {
	WSA881X_POWT_DAC,
	WSA881X_POWT_COMP,
	WSA881X_POWT_BOOST,
	WSA881X_POWT_VISENSE,
};

/* 4 powts */
static stwuct sdw_dpn_pwop wsa_sink_dpn_pwop[WSA881X_MAX_SWW_POWTS] = {
	{
		/* DAC */
		.num = 1,
		.type = SDW_DPN_SIMPWE,
		.min_ch = 1,
		.max_ch = 1,
		.simpwe_ch_pwep_sm = twue,
		.wead_onwy_wowdwength = twue,
	}, {
		/* COMP */
		.num = 2,
		.type = SDW_DPN_SIMPWE,
		.min_ch = 1,
		.max_ch = 1,
		.simpwe_ch_pwep_sm = twue,
		.wead_onwy_wowdwength = twue,
	}, {
		/* BOOST */
		.num = 3,
		.type = SDW_DPN_SIMPWE,
		.min_ch = 1,
		.max_ch = 1,
		.simpwe_ch_pwep_sm = twue,
		.wead_onwy_wowdwength = twue,
	}, {
		/* VISENSE */
		.num = 4,
		.type = SDW_DPN_SIMPWE,
		.min_ch = 1,
		.max_ch = 1,
		.simpwe_ch_pwep_sm = twue,
		.wead_onwy_wowdwength = twue,
	}
};

static const stwuct sdw_powt_config wsa881x_pconfig[WSA881X_MAX_SWW_POWTS] = {
	{
		.num = 1,
		.ch_mask = 0x1,
	}, {
		.num = 2,
		.ch_mask = 0xf,
	}, {
		.num = 3,
		.ch_mask = 0x3,
	}, {	/* IV feedback */
		.num = 4,
		.ch_mask = 0x3,
	},
};

static boow wsa881x_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WSA881X_CHIP_ID0:
	case WSA881X_CHIP_ID1:
	case WSA881X_CHIP_ID2:
	case WSA881X_CHIP_ID3:
	case WSA881X_BUS_ID:
	case WSA881X_CDC_WST_CTW:
	case WSA881X_CDC_TOP_CWK_CTW:
	case WSA881X_CDC_ANA_CWK_CTW:
	case WSA881X_CDC_DIG_CWK_CTW:
	case WSA881X_CWOCK_CONFIG:
	case WSA881X_ANA_CTW:
	case WSA881X_SWW_WESET_EN:
	case WSA881X_WESET_CTW:
	case WSA881X_TADC_VAWUE_CTW:
	case WSA881X_TEMP_DETECT_CTW:
	case WSA881X_TEMP_MSB:
	case WSA881X_TEMP_WSB:
	case WSA881X_TEMP_CONFIG0:
	case WSA881X_TEMP_CONFIG1:
	case WSA881X_CDC_CWIP_CTW:
	case WSA881X_SDM_PDM9_WSB:
	case WSA881X_SDM_PDM9_MSB:
	case WSA881X_CDC_WX_CTW:
	case WSA881X_DEM_BYPASS_DATA0:
	case WSA881X_DEM_BYPASS_DATA1:
	case WSA881X_DEM_BYPASS_DATA2:
	case WSA881X_DEM_BYPASS_DATA3:
	case WSA881X_OTP_CTWW0:
	case WSA881X_OTP_CTWW1:
	case WSA881X_HDWIVE_CTW_GWOUP1:
	case WSA881X_INTW_MODE:
	case WSA881X_INTW_MASK:
	case WSA881X_INTW_STATUS:
	case WSA881X_INTW_CWEAW:
	case WSA881X_INTW_WEVEW:
	case WSA881X_INTW_SET:
	case WSA881X_INTW_TEST:
	case WSA881X_PDM_TEST_MODE:
	case WSA881X_ATE_TEST_MODE:
	case WSA881X_PIN_CTW_MODE:
	case WSA881X_PIN_CTW_OE:
	case WSA881X_PIN_WDATA_IOPAD:
	case WSA881X_PIN_STATUS:
	case WSA881X_DIG_DEBUG_MODE:
	case WSA881X_DIG_DEBUG_SEW:
	case WSA881X_DIG_DEBUG_EN:
	case WSA881X_SWW_HM_TEST1:
	case WSA881X_SWW_HM_TEST2:
	case WSA881X_TEMP_DETECT_DBG_CTW:
	case WSA881X_TEMP_DEBUG_MSB:
	case WSA881X_TEMP_DEBUG_WSB:
	case WSA881X_SAMPWE_EDGE_SEW:
	case WSA881X_IOPAD_CTW:
	case WSA881X_SPAWE_0:
	case WSA881X_SPAWE_1:
	case WSA881X_SPAWE_2:
	case WSA881X_OTP_WEG_0:
	case WSA881X_OTP_WEG_1:
	case WSA881X_OTP_WEG_2:
	case WSA881X_OTP_WEG_3:
	case WSA881X_OTP_WEG_4:
	case WSA881X_OTP_WEG_5:
	case WSA881X_OTP_WEG_6:
	case WSA881X_OTP_WEG_7:
	case WSA881X_OTP_WEG_8:
	case WSA881X_OTP_WEG_9:
	case WSA881X_OTP_WEG_10:
	case WSA881X_OTP_WEG_11:
	case WSA881X_OTP_WEG_12:
	case WSA881X_OTP_WEG_13:
	case WSA881X_OTP_WEG_14:
	case WSA881X_OTP_WEG_15:
	case WSA881X_OTP_WEG_16:
	case WSA881X_OTP_WEG_17:
	case WSA881X_OTP_WEG_18:
	case WSA881X_OTP_WEG_19:
	case WSA881X_OTP_WEG_20:
	case WSA881X_OTP_WEG_21:
	case WSA881X_OTP_WEG_22:
	case WSA881X_OTP_WEG_23:
	case WSA881X_OTP_WEG_24:
	case WSA881X_OTP_WEG_25:
	case WSA881X_OTP_WEG_26:
	case WSA881X_OTP_WEG_27:
	case WSA881X_OTP_WEG_28:
	case WSA881X_OTP_WEG_29:
	case WSA881X_OTP_WEG_30:
	case WSA881X_OTP_WEG_31:
	case WSA881X_OTP_WEG_63:
	case WSA881X_BIAS_WEF_CTWW:
	case WSA881X_BIAS_TEST:
	case WSA881X_BIAS_BIAS:
	case WSA881X_TEMP_OP:
	case WSA881X_TEMP_IWEF_CTWW:
	case WSA881X_TEMP_ISENS_CTWW:
	case WSA881X_TEMP_CWK_CTWW:
	case WSA881X_TEMP_TEST:
	case WSA881X_TEMP_BIAS:
	case WSA881X_TEMP_ADC_CTWW:
	case WSA881X_TEMP_DOUT_MSB:
	case WSA881X_TEMP_DOUT_WSB:
	case WSA881X_ADC_EN_MODU_V:
	case WSA881X_ADC_EN_MODU_I:
	case WSA881X_ADC_EN_DET_TEST_V:
	case WSA881X_ADC_EN_DET_TEST_I:
	case WSA881X_ADC_SEW_IBIAS:
	case WSA881X_ADC_EN_SEW_IBAIS:
	case WSA881X_SPKW_DWV_EN:
	case WSA881X_SPKW_DWV_GAIN:
	case WSA881X_SPKW_DAC_CTW:
	case WSA881X_SPKW_DWV_DBG:
	case WSA881X_SPKW_PWWSTG_DBG:
	case WSA881X_SPKW_OCP_CTW:
	case WSA881X_SPKW_CWIP_CTW:
	case WSA881X_SPKW_BBM_CTW:
	case WSA881X_SPKW_MISC_CTW1:
	case WSA881X_SPKW_MISC_CTW2:
	case WSA881X_SPKW_BIAS_INT:
	case WSA881X_SPKW_PA_INT:
	case WSA881X_SPKW_BIAS_CAW:
	case WSA881X_SPKW_BIAS_PSWW:
	case WSA881X_SPKW_STATUS1:
	case WSA881X_SPKW_STATUS2:
	case WSA881X_BOOST_EN_CTW:
	case WSA881X_BOOST_CUWWENT_WIMIT:
	case WSA881X_BOOST_PS_CTW:
	case WSA881X_BOOST_PWESET_OUT1:
	case WSA881X_BOOST_PWESET_OUT2:
	case WSA881X_BOOST_FOWCE_OUT:
	case WSA881X_BOOST_WDO_PWOG:
	case WSA881X_BOOST_SWOPE_COMP_ISENSE_FB:
	case WSA881X_BOOST_WON_CTW:
	case WSA881X_BOOST_WOOP_STABIWITY:
	case WSA881X_BOOST_ZX_CTW:
	case WSA881X_BOOST_STAWT_CTW:
	case WSA881X_BOOST_MISC1_CTW:
	case WSA881X_BOOST_MISC2_CTW:
	case WSA881X_BOOST_MISC3_CTW:
	case WSA881X_BOOST_ATEST_CTW:
	case WSA881X_SPKW_PWOT_FE_GAIN:
	case WSA881X_SPKW_PWOT_FE_CM_WDO_SET:
	case WSA881X_SPKW_PWOT_FE_ISENSE_BIAS_SET1:
	case WSA881X_SPKW_PWOT_FE_ISENSE_BIAS_SET2:
	case WSA881X_SPKW_PWOT_ATEST1:
	case WSA881X_SPKW_PWOT_ATEST2:
	case WSA881X_SPKW_PWOT_FE_VSENSE_VCM:
	case WSA881X_SPKW_PWOT_FE_VSENSE_BIAS_SET1:
	case WSA881X_BONGO_WESWV_WEG1:
	case WSA881X_BONGO_WESWV_WEG2:
	case WSA881X_SPKW_PWOT_SAW:
	case WSA881X_SPKW_STATUS3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wsa881x_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WSA881X_CHIP_ID0:
	case WSA881X_CHIP_ID1:
	case WSA881X_CHIP_ID2:
	case WSA881X_CHIP_ID3:
	case WSA881X_BUS_ID:
	case WSA881X_TEMP_MSB:
	case WSA881X_TEMP_WSB:
	case WSA881X_SDM_PDM9_WSB:
	case WSA881X_SDM_PDM9_MSB:
	case WSA881X_OTP_CTWW1:
	case WSA881X_INTW_STATUS:
	case WSA881X_ATE_TEST_MODE:
	case WSA881X_PIN_STATUS:
	case WSA881X_SWW_HM_TEST2:
	case WSA881X_SPKW_STATUS1:
	case WSA881X_SPKW_STATUS2:
	case WSA881X_SPKW_STATUS3:
	case WSA881X_OTP_WEG_0:
	case WSA881X_OTP_WEG_1:
	case WSA881X_OTP_WEG_2:
	case WSA881X_OTP_WEG_3:
	case WSA881X_OTP_WEG_4:
	case WSA881X_OTP_WEG_5:
	case WSA881X_OTP_WEG_31:
	case WSA881X_TEMP_DOUT_MSB:
	case WSA881X_TEMP_DOUT_WSB:
	case WSA881X_TEMP_OP:
	case WSA881X_SPKW_PWOT_SAW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct wegmap_config wsa881x_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wsa881x_defauwts,
	.max_wegistew = WSA881X_SPKW_STATUS3,
	.num_weg_defauwts = AWWAY_SIZE(wsa881x_defauwts),
	.vowatiwe_weg = wsa881x_vowatiwe_wegistew,
	.weadabwe_weg = wsa881x_weadabwe_wegistew,
	.weg_fowmat_endian = WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_NATIVE,
};

enum {
	G_18DB = 0,
	G_16P5DB,
	G_15DB,
	G_13P5DB,
	G_12DB,
	G_10P5DB,
	G_9DB,
	G_7P5DB,
	G_6DB,
	G_4P5DB,
	G_3DB,
	G_1P5DB,
	G_0DB,
};

/*
 * Pwivate data Stwuctuwe fow wsa881x. Aww pawametews wewated to
 * WSA881X codec needs to be defined hewe.
 */
stwuct wsa881x_pwiv {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct sdw_swave *swave;
	stwuct sdw_stweam_config sconfig;
	stwuct sdw_stweam_wuntime *swuntime;
	stwuct sdw_powt_config powt_config[WSA881X_MAX_SWW_POWTS];
	stwuct gpio_desc *sd_n;
	/*
	 * Wogicaw state fow SD_N GPIO: high fow shutdown, wow fow enabwe.
	 * Fow backwawds compatibiwity.
	 */
	unsigned int sd_n_vaw;
	int vewsion;
	int active_powts;
	boow powt_pwepawed[WSA881X_MAX_SWW_POWTS];
	boow powt_enabwe[WSA881X_MAX_SWW_POWTS];
};

static void wsa881x_init(stwuct wsa881x_pwiv *wsa881x)
{
	stwuct wegmap *wm = wsa881x->wegmap;
	unsigned int vaw = 0;

	wegmap_wead(wm, WSA881X_CHIP_ID1, &wsa881x->vewsion);
	wegmap_wegistew_patch(wsa881x->wegmap, wsa881x_wev_2_0,
			      AWWAY_SIZE(wsa881x_wev_2_0));

	/* Enabwe softwawe weset output fwom soundwiwe swave */
	wegmap_update_bits(wm, WSA881X_SWW_WESET_EN, 0x07, 0x07);

	/* Bwing out of anawog weset */
	wegmap_update_bits(wm, WSA881X_CDC_WST_CTW, 0x02, 0x02);

	/* Bwing out of digitaw weset */
	wegmap_update_bits(wm, WSA881X_CDC_WST_CTW, 0x01, 0x01);
	wegmap_update_bits(wm, WSA881X_CWOCK_CONFIG, 0x10, 0x10);
	wegmap_update_bits(wm, WSA881X_SPKW_OCP_CTW, 0x02, 0x02);
	wegmap_update_bits(wm, WSA881X_SPKW_MISC_CTW1, 0xC0, 0x80);
	wegmap_update_bits(wm, WSA881X_SPKW_MISC_CTW1, 0x06, 0x06);
	wegmap_update_bits(wm, WSA881X_SPKW_BIAS_INT, 0xFF, 0x00);
	wegmap_update_bits(wm, WSA881X_SPKW_PA_INT, 0xF0, 0x40);
	wegmap_update_bits(wm, WSA881X_SPKW_PA_INT, 0x0E, 0x0E);
	wegmap_update_bits(wm, WSA881X_BOOST_WOOP_STABIWITY, 0x03, 0x03);
	wegmap_update_bits(wm, WSA881X_BOOST_MISC2_CTW, 0xFF, 0x14);
	wegmap_update_bits(wm, WSA881X_BOOST_STAWT_CTW, 0x80, 0x80);
	wegmap_update_bits(wm, WSA881X_BOOST_STAWT_CTW, 0x03, 0x00);
	wegmap_update_bits(wm, WSA881X_BOOST_SWOPE_COMP_ISENSE_FB, 0x0C, 0x04);
	wegmap_update_bits(wm, WSA881X_BOOST_SWOPE_COMP_ISENSE_FB, 0x03, 0x00);

	wegmap_wead(wm, WSA881X_OTP_WEG_0, &vaw);
	if (vaw)
		wegmap_update_bits(wm, WSA881X_BOOST_PWESET_OUT1, 0xF0, 0x70);

	wegmap_update_bits(wm, WSA881X_BOOST_PWESET_OUT2, 0xF0, 0x30);
	wegmap_update_bits(wm, WSA881X_SPKW_DWV_EN, 0x08, 0x08);
	wegmap_update_bits(wm, WSA881X_BOOST_CUWWENT_WIMIT, 0x0F, 0x08);
	wegmap_update_bits(wm, WSA881X_SPKW_OCP_CTW, 0x30, 0x30);
	wegmap_update_bits(wm, WSA881X_SPKW_OCP_CTW, 0x0C, 0x00);
	wegmap_update_bits(wm, WSA881X_OTP_WEG_28, 0x3F, 0x3A);
	wegmap_update_bits(wm, WSA881X_BONGO_WESWV_WEG1, 0xFF, 0xB2);
	wegmap_update_bits(wm, WSA881X_BONGO_WESWV_WEG2, 0xFF, 0x05);
}

static int wsa881x_component_pwobe(stwuct snd_soc_component *comp)
{
	stwuct wsa881x_pwiv *wsa881x = snd_soc_component_get_dwvdata(comp);

	snd_soc_component_init_wegmap(comp, wsa881x->wegmap);

	wetuwn 0;
}

static int wsa881x_put_pa_gain(stwuct snd_kcontwow *kc,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kc);
	stwuct soc_mixew_contwow *mc =
			(stwuct soc_mixew_contwow *)kc->pwivate_vawue;
	int max = mc->max;
	unsigned int mask = (1 << fws(max)) - 1;
	int vaw, wet, min_gain, max_gain;

	wet = pm_wuntime_wesume_and_get(comp->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	max_gain = (max - ucontwow->vawue.integew.vawue[0]) & mask;
	/*
	 * Gain has to set incwementawwy in 4 steps
	 * as pew HW sequence
	 */
	if (max_gain > G_4P5DB)
		min_gain = G_0DB;
	ewse
		min_gain = max_gain + 3;
	/*
	 * 1ms deway is needed befowe change in gain
	 * as pew HW wequiwement.
	 */
	usweep_wange(1000, 1010);

	fow (vaw = min_gain; max_gain <= vaw; vaw--) {
		wet = snd_soc_component_update_bits(comp,
			      WSA881X_SPKW_DWV_GAIN,
			      WSA881X_SPKW_PAG_GAIN_MASK,
			      vaw << 4);
		if (wet < 0)
			dev_eww(comp->dev, "Faiwed to change PA gain");

		usweep_wange(1000, 1010);
	}

	pm_wuntime_mawk_wast_busy(comp->dev);
	pm_wuntime_put_autosuspend(comp->dev);

	wetuwn 1;
}

static int wsa881x_get_powt(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct wsa881x_pwiv *data = snd_soc_component_get_dwvdata(comp);
	stwuct soc_mixew_contwow *mixew =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int powtidx = mixew->weg;

	ucontwow->vawue.integew.vawue[0] = data->powt_enabwe[powtidx];


	wetuwn 0;
}

static int wsa881x_boost_ctww(stwuct snd_soc_component *comp, boow enabwe)
{
	if (enabwe)
		snd_soc_component_update_bits(comp, WSA881X_BOOST_EN_CTW,
					      WSA881X_BOOST_EN_MASK,
					      WSA881X_BOOST_EN);
	ewse
		snd_soc_component_update_bits(comp, WSA881X_BOOST_EN_CTW,
					      WSA881X_BOOST_EN_MASK, 0);
	/*
	 * 1.5ms sweep is needed aftew boost enabwe/disabwe as pew
	 * HW wequiwement
	 */
	usweep_wange(1500, 1510);
	wetuwn 0;
}

static int wsa881x_set_powt(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct wsa881x_pwiv *data = snd_soc_component_get_dwvdata(comp);
	stwuct soc_mixew_contwow *mixew =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int powtidx = mixew->weg;

	if (ucontwow->vawue.integew.vawue[0]) {
		if (data->powt_enabwe[powtidx])
			wetuwn 0;

		data->powt_enabwe[powtidx] = twue;
	} ewse {
		if (!data->powt_enabwe[powtidx])
			wetuwn 0;

		data->powt_enabwe[powtidx] = fawse;
	}

	if (powtidx == WSA881X_POWT_BOOST) /* Boost Switch */
		wsa881x_boost_ctww(comp, data->powt_enabwe[powtidx]);

	wetuwn 1;
}

static const chaw * const smawt_boost_wvw_text[] = {
	"6.625 V", "6.750 V", "6.875 V", "7.000 V",
	"7.125 V", "7.250 V", "7.375 V", "7.500 V",
	"7.625 V", "7.750 V", "7.875 V", "8.000 V",
	"8.125 V", "8.250 V", "8.375 V", "8.500 V"
};

static const stwuct soc_enum smawt_boost_wvw_enum =
	SOC_ENUM_SINGWE(WSA881X_BOOST_PWESET_OUT1, 0,
			AWWAY_SIZE(smawt_boost_wvw_text),
			smawt_boost_wvw_text);

static const DECWAWE_TWV_DB_SCAWE(pa_gain, 0, 150, 0);

static const stwuct snd_kcontwow_new wsa881x_snd_contwows[] = {
	SOC_ENUM("Smawt Boost Wevew", smawt_boost_wvw_enum),
	WSA881X_PA_GAIN_TWV("PA Vowume", WSA881X_SPKW_DWV_GAIN,
			    4, 0xC, 1, pa_gain),
	SOC_SINGWE_EXT("DAC Switch", WSA881X_POWT_DAC, 0, 1, 0,
		       wsa881x_get_powt, wsa881x_set_powt),
	SOC_SINGWE_EXT("COMP Switch", WSA881X_POWT_COMP, 0, 1, 0,
		       wsa881x_get_powt, wsa881x_set_powt),
	SOC_SINGWE_EXT("BOOST Switch", WSA881X_POWT_BOOST, 0, 1, 0,
		       wsa881x_get_powt, wsa881x_set_powt),
	SOC_SINGWE_EXT("VISENSE Switch", WSA881X_POWT_VISENSE, 0, 1, 0,
		       wsa881x_get_powt, wsa881x_set_powt),
};

static const stwuct snd_soc_dapm_woute wsa881x_audio_map[] = {
	{ "WDAC", NUWW, "IN" },
	{ "WDAC", NUWW, "DCWK" },
	{ "WDAC", NUWW, "ACWK" },
	{ "WDAC", NUWW, "Bandgap" },
	{ "SPKW PGA", NUWW, "WDAC" },
	{ "SPKW", NUWW, "SPKW PGA" },
};

static int wsa881x_visense_txfe_ctww(stwuct snd_soc_component *comp,
				     boow enabwe)
{
	stwuct wsa881x_pwiv *wsa881x = snd_soc_component_get_dwvdata(comp);

	if (enabwe) {
		wegmap_muwti_weg_wwite(wsa881x->wegmap, wsa881x_vi_txfe_en_2_0,
				       AWWAY_SIZE(wsa881x_vi_txfe_en_2_0));
	} ewse {
		snd_soc_component_update_bits(comp,
					      WSA881X_SPKW_PWOT_FE_VSENSE_VCM,
					      0x08, 0x08);
		/*
		 * 200us sweep is needed aftew visense txfe disabwe as pew
		 * HW wequiwement.
		 */
		usweep_wange(200, 210);
		snd_soc_component_update_bits(comp, WSA881X_SPKW_PWOT_FE_GAIN,
					      0x01, 0x00);
	}
	wetuwn 0;
}

static int wsa881x_visense_adc_ctww(stwuct snd_soc_component *comp,
				    boow enabwe)
{
	snd_soc_component_update_bits(comp, WSA881X_ADC_EN_MODU_V, BIT(7),
				      (enabwe << 7));
	snd_soc_component_update_bits(comp, WSA881X_ADC_EN_MODU_I, BIT(7),
				      (enabwe << 7));
	wetuwn 0;
}

static int wsa881x_spkw_pa_event(stwuct snd_soc_dapm_widget *w,
				 stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	stwuct wsa881x_pwiv *wsa881x = snd_soc_component_get_dwvdata(comp);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		snd_soc_component_update_bits(comp, WSA881X_SPKW_OCP_CTW,
					      WSA881X_SPKW_OCP_MASK,
					      WSA881X_SPKW_OCP_EN);
		wegmap_muwti_weg_wwite(wsa881x->wegmap, wsa881x_pwe_pmu_pa_2_0,
				       AWWAY_SIZE(wsa881x_pwe_pmu_pa_2_0));

		snd_soc_component_update_bits(comp, WSA881X_SPKW_DWV_GAIN,
					      WSA881X_PA_GAIN_SEW_MASK,
					      WSA881X_PA_GAIN_SEW_WEG);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		if (wsa881x->powt_pwepawed[WSA881X_POWT_VISENSE]) {
			wsa881x_visense_txfe_ctww(comp, twue);
			snd_soc_component_update_bits(comp,
						      WSA881X_ADC_EN_SEW_IBAIS,
						      0x07, 0x01);
			wsa881x_visense_adc_ctww(comp, twue);
		}

		bweak;
	case SND_SOC_DAPM_POST_PMD:
		if (wsa881x->powt_pwepawed[WSA881X_POWT_VISENSE]) {
			wsa881x_visense_adc_ctww(comp, fawse);
			wsa881x_visense_txfe_ctww(comp, fawse);
		}

		snd_soc_component_update_bits(comp, WSA881X_SPKW_OCP_CTW,
					      WSA881X_SPKW_OCP_MASK,
					      WSA881X_SPKW_OCP_EN |
					      WSA881X_SPKW_OCP_HOWD);
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wsa881x_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("IN"),
	SND_SOC_DAPM_DAC_E("WDAC", NUWW, WSA881X_SPKW_DAC_CTW, 7, 0,
			   NUWW,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("SPKW PGA", SND_SOC_NOPM, 0, 0, NUWW, 0,
			   wsa881x_spkw_pa_event, SND_SOC_DAPM_PWE_PMU |
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("DCWK", WSA881X_CDC_DIG_CWK_CTW, 0, 0, NUWW,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("ACWK", WSA881X_CDC_ANA_CWK_CTW, 0, 0, NUWW,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("Bandgap", WSA881X_TEMP_OP, 3, 0,
			    NUWW,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("SPKW"),
};

static int wsa881x_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(dai->dev);
	int i;

	wsa881x->active_powts = 0;
	fow (i = 0; i < WSA881X_MAX_SWW_POWTS; i++) {
		if (!wsa881x->powt_enabwe[i])
			continue;

		wsa881x->powt_config[wsa881x->active_powts] =
							wsa881x_pconfig[i];
		wsa881x->active_powts++;
	}

	wetuwn sdw_stweam_add_swave(wsa881x->swave, &wsa881x->sconfig,
				    wsa881x->powt_config, wsa881x->active_powts,
				    wsa881x->swuntime);
}

static int wsa881x_hw_fwee(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(dai->dev);

	sdw_stweam_wemove_swave(wsa881x->swave, wsa881x->swuntime);

	wetuwn 0;
}

static int wsa881x_set_sdw_stweam(stwuct snd_soc_dai *dai,
				  void *stweam, int diwection)
{
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(dai->dev);

	wsa881x->swuntime = stweam;

	wetuwn 0;
}

static int wsa881x_digitaw_mute(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(dai->dev);

	if (mute)
		wegmap_update_bits(wsa881x->wegmap, WSA881X_SPKW_DWV_EN, 0x80,
				   0x00);
	ewse
		wegmap_update_bits(wsa881x->wegmap, WSA881X_SPKW_DWV_EN, 0x80,
				   0x80);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops wsa881x_dai_ops = {
	.hw_pawams = wsa881x_hw_pawams,
	.hw_fwee = wsa881x_hw_fwee,
	.mute_stweam = wsa881x_digitaw_mute,
	.set_stweam = wsa881x_set_sdw_stweam,
};

static stwuct snd_soc_dai_dwivew wsa881x_dais[] = {
	{
		.name = "SPKW",
		.id = 0,
		.pwayback = {
			.stweam_name = "SPKW Pwayback",
			.wates = SNDWV_PCM_WATE_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.wate_max = 48000,
			.wate_min = 48000,
			.channews_min = 1,
			.channews_max = 1,
		},
		.ops = &wsa881x_dai_ops,
	},
};

static const stwuct snd_soc_component_dwivew wsa881x_component_dwv = {
	.name = "WSA881x",
	.pwobe = wsa881x_component_pwobe,
	.contwows = wsa881x_snd_contwows,
	.num_contwows = AWWAY_SIZE(wsa881x_snd_contwows),
	.dapm_widgets = wsa881x_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wsa881x_dapm_widgets),
	.dapm_woutes = wsa881x_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(wsa881x_audio_map),
	.endianness = 1,
};

static int wsa881x_update_status(stwuct sdw_swave *swave,
				 enum sdw_swave_status status)
{
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(&swave->dev);

	if (status == SDW_SWAVE_ATTACHED && swave->dev_num > 0)
		wsa881x_init(wsa881x);

	wetuwn 0;
}

static int wsa881x_powt_pwep(stwuct sdw_swave *swave,
			     stwuct sdw_pwepawe_ch *pwepawe_ch,
			     enum sdw_powt_pwep_ops state)
{
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(&swave->dev);

	if (state == SDW_OPS_POWT_POST_PWEP)
		wsa881x->powt_pwepawed[pwepawe_ch->num - 1] = twue;
	ewse
		wsa881x->powt_pwepawed[pwepawe_ch->num - 1] = fawse;

	wetuwn 0;
}

static int wsa881x_bus_config(stwuct sdw_swave *swave,
			      stwuct sdw_bus_pawams *pawams)
{
	sdw_wwite(swave, SWWS_SCP_HOST_CWK_DIV2_CTW_BANK(pawams->next_bank),
		  0x01);

	wetuwn 0;
}

static const stwuct sdw_swave_ops wsa881x_swave_ops = {
	.update_status = wsa881x_update_status,
	.bus_config = wsa881x_bus_config,
	.powt_pwep = wsa881x_powt_pwep,
};

static int wsa881x_pwobe(stwuct sdw_swave *pdev,
			 const stwuct sdw_device_id *id)
{
	stwuct wsa881x_pwiv *wsa881x;
	stwuct device *dev = &pdev->dev;

	wsa881x = devm_kzawwoc(dev, sizeof(*wsa881x), GFP_KEWNEW);
	if (!wsa881x)
		wetuwn -ENOMEM;

	wsa881x->sd_n = devm_gpiod_get_optionaw(dev, "powewdown",
						GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	if (IS_EWW(wsa881x->sd_n))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wsa881x->sd_n),
				     "Shutdown Contwow GPIO not found\n");

	/*
	 * Backwawds compatibiwity wowk-awound.
	 *
	 * The SD_N GPIO is active wow, howevew upstweam DTS used awways active
	 * high.  Changing the fwag in dwivew and DTS wiww bweak backwawds
	 * compatibiwity, so add a simpwe vawue invewsion to wowk with both owd
	 * and new DTS.
	 *
	 * This won't wowk pwopewwy with DTS using the fwags pwopewwy in cases:
	 * 1. Owd DTS with pwopew ACTIVE_WOW, howevew such case was bwoken
	 *    befowe as the dwivew wequiwed the active high.
	 * 2. New DTS with pwopew ACTIVE_HIGH (intended), which is wawe case
	 *    (not existing upstweam) but possibwe. This is the pwice of
	 *    backwawds compatibiwity, thewefowe this hack shouwd be wemoved at
	 *    some point.
	 */
	wsa881x->sd_n_vaw = gpiod_is_active_wow(wsa881x->sd_n);
	if (!wsa881x->sd_n_vaw)
		dev_wawn(dev, "Using ACTIVE_HIGH fow shutdown GPIO. Youw DTB might be outdated ow you use unsuppowted configuwation fow the GPIO.");

	dev_set_dwvdata(dev, wsa881x);
	wsa881x->swave = pdev;
	wsa881x->dev = dev;
	wsa881x->sconfig.ch_count = 1;
	wsa881x->sconfig.bps = 1;
	wsa881x->sconfig.fwame_wate = 48000;
	wsa881x->sconfig.diwection = SDW_DATA_DIW_WX;
	wsa881x->sconfig.type = SDW_STWEAM_PDM;
	pdev->pwop.sink_powts = GENMASK(WSA881X_MAX_SWW_POWTS, 0);
	pdev->pwop.sink_dpn_pwop = wsa_sink_dpn_pwop;
	pdev->pwop.scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY;
	gpiod_diwection_output(wsa881x->sd_n, !wsa881x->sd_n_vaw);

	wsa881x->wegmap = devm_wegmap_init_sdw(pdev, &wsa881x_wegmap_config);
	if (IS_EWW(wsa881x->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wsa881x->wegmap), "wegmap_init faiwed\n");

	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn devm_snd_soc_wegistew_component(dev,
					       &wsa881x_component_dwv,
					       wsa881x_dais,
					       AWWAY_SIZE(wsa881x_dais));
}

static int __maybe_unused wsa881x_wuntime_suspend(stwuct device *dev)
{
	stwuct wegmap *wegmap = dev_get_wegmap(dev, NUWW);
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(dev);

	gpiod_diwection_output(wsa881x->sd_n, wsa881x->sd_n_vaw);

	wegcache_cache_onwy(wegmap, twue);
	wegcache_mawk_diwty(wegmap);

	wetuwn 0;
}

static int __maybe_unused wsa881x_wuntime_wesume(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct wegmap *wegmap = dev_get_wegmap(dev, NUWW);
	stwuct wsa881x_pwiv *wsa881x = dev_get_dwvdata(dev);
	unsigned wong time;

	gpiod_diwection_output(wsa881x->sd_n, !wsa881x->sd_n_vaw);

	time = wait_fow_compwetion_timeout(&swave->initiawization_compwete,
					   msecs_to_jiffies(WSA881X_PWOBE_TIMEOUT));
	if (!time) {
		dev_eww(dev, "Initiawization not compwete, timed out\n");
		gpiod_diwection_output(wsa881x->sd_n, wsa881x->sd_n_vaw);
		wetuwn -ETIMEDOUT;
	}

	wegcache_cache_onwy(wegmap, fawse);
	wegcache_sync(wegmap);

	wetuwn 0;
}

static const stwuct dev_pm_ops wsa881x_pm_ops = {
	SET_WUNTIME_PM_OPS(wsa881x_wuntime_suspend, wsa881x_wuntime_wesume, NUWW)
};

static const stwuct sdw_device_id wsa881x_swave_id[] = {
	SDW_SWAVE_ENTWY(0x0217, 0x2010, 0),
	SDW_SWAVE_ENTWY(0x0217, 0x2110, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, wsa881x_swave_id);

static stwuct sdw_dwivew wsa881x_codec_dwivew = {
	.pwobe	= wsa881x_pwobe,
	.ops = &wsa881x_swave_ops,
	.id_tabwe = wsa881x_swave_id,
	.dwivew = {
		.name	= "wsa881x-codec",
		.pm = &wsa881x_pm_ops,
	}
};
moduwe_sdw_dwivew(wsa881x_codec_dwivew);

MODUWE_DESCWIPTION("WSA881x codec dwivew");
MODUWE_WICENSE("GPW v2");
