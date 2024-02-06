// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020, Maxim Integwated

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sdw.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <winux/of.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude "max98373.h"
#incwude "max98373-sdw.h"

static const u32 max98373_sdw_cache_weg[] = {
	MAX98373_W2054_MEAS_ADC_PVDD_CH_WEADBACK,
	MAX98373_W2055_MEAS_ADC_THEWM_CH_WEADBACK,
	MAX98373_W20B6_BDE_CUW_STATE_WEADBACK,
};

static stwuct weg_defauwt max98373_weg[] = {
	{MAX98373_W0040_SCP_INIT_STAT_1, 0x00},
	{MAX98373_W0041_SCP_INIT_MASK_1, 0x00},
	{MAX98373_W0042_SCP_INIT_STAT_2, 0x00},
	{MAX98373_W0044_SCP_CTWW, 0x00},
	{MAX98373_W0045_SCP_SYSTEM_CTWW, 0x00},
	{MAX98373_W0046_SCP_DEV_NUMBEW, 0x00},
	{MAX98373_W0050_SCP_DEV_ID_0, 0x21},
	{MAX98373_W0051_SCP_DEV_ID_1, 0x01},
	{MAX98373_W0052_SCP_DEV_ID_2, 0x9F},
	{MAX98373_W0053_SCP_DEV_ID_3, 0x87},
	{MAX98373_W0054_SCP_DEV_ID_4, 0x08},
	{MAX98373_W0055_SCP_DEV_ID_5, 0x00},
	{MAX98373_W0060_SCP_FWAME_CTWW, 0x00},
	{MAX98373_W0070_SCP_FWAME_CTWW, 0x00},
	{MAX98373_W0100_DP1_INIT_STAT, 0x00},
	{MAX98373_W0101_DP1_INIT_MASK, 0x00},
	{MAX98373_W0102_DP1_POWT_CTWW, 0x00},
	{MAX98373_W0103_DP1_BWOCK_CTWW_1, 0x00},
	{MAX98373_W0104_DP1_PWEPAWE_STATUS, 0x00},
	{MAX98373_W0105_DP1_PWEPAWE_CTWW, 0x00},
	{MAX98373_W0120_DP1_CHANNEW_EN, 0x00},
	{MAX98373_W0122_DP1_SAMPWE_CTWW1, 0x00},
	{MAX98373_W0123_DP1_SAMPWE_CTWW2, 0x00},
	{MAX98373_W0124_DP1_OFFSET_CTWW1, 0x00},
	{MAX98373_W0125_DP1_OFFSET_CTWW2, 0x00},
	{MAX98373_W0126_DP1_HCTWW, 0x00},
	{MAX98373_W0127_DP1_BWOCK_CTWW3, 0x00},
	{MAX98373_W0130_DP1_CHANNEW_EN, 0x00},
	{MAX98373_W0132_DP1_SAMPWE_CTWW1, 0x00},
	{MAX98373_W0133_DP1_SAMPWE_CTWW2, 0x00},
	{MAX98373_W0134_DP1_OFFSET_CTWW1, 0x00},
	{MAX98373_W0135_DP1_OFFSET_CTWW2, 0x00},
	{MAX98373_W0136_DP1_HCTWW, 0x0136},
	{MAX98373_W0137_DP1_BWOCK_CTWW3, 0x00},
	{MAX98373_W0300_DP3_INIT_STAT, 0x00},
	{MAX98373_W0301_DP3_INIT_MASK, 0x00},
	{MAX98373_W0302_DP3_POWT_CTWW, 0x00},
	{MAX98373_W0303_DP3_BWOCK_CTWW_1, 0x00},
	{MAX98373_W0304_DP3_PWEPAWE_STATUS, 0x00},
	{MAX98373_W0305_DP3_PWEPAWE_CTWW, 0x00},
	{MAX98373_W0320_DP3_CHANNEW_EN, 0x00},
	{MAX98373_W0322_DP3_SAMPWE_CTWW1, 0x00},
	{MAX98373_W0323_DP3_SAMPWE_CTWW2, 0x00},
	{MAX98373_W0324_DP3_OFFSET_CTWW1, 0x00},
	{MAX98373_W0325_DP3_OFFSET_CTWW2, 0x00},
	{MAX98373_W0326_DP3_HCTWW, 0x00},
	{MAX98373_W0327_DP3_BWOCK_CTWW3, 0x00},
	{MAX98373_W0330_DP3_CHANNEW_EN, 0x00},
	{MAX98373_W0332_DP3_SAMPWE_CTWW1, 0x00},
	{MAX98373_W0333_DP3_SAMPWE_CTWW2, 0x00},
	{MAX98373_W0334_DP3_OFFSET_CTWW1, 0x00},
	{MAX98373_W0335_DP3_OFFSET_CTWW2, 0x00},
	{MAX98373_W0336_DP3_HCTWW, 0x00},
	{MAX98373_W0337_DP3_BWOCK_CTWW3, 0x00},
	{MAX98373_W2000_SW_WESET, 0x00},
	{MAX98373_W2001_INT_WAW1, 0x00},
	{MAX98373_W2002_INT_WAW2, 0x00},
	{MAX98373_W2003_INT_WAW3, 0x00},
	{MAX98373_W2004_INT_STATE1, 0x00},
	{MAX98373_W2005_INT_STATE2, 0x00},
	{MAX98373_W2006_INT_STATE3, 0x00},
	{MAX98373_W2007_INT_FWAG1, 0x00},
	{MAX98373_W2008_INT_FWAG2, 0x00},
	{MAX98373_W2009_INT_FWAG3, 0x00},
	{MAX98373_W200A_INT_EN1, 0x00},
	{MAX98373_W200B_INT_EN2, 0x00},
	{MAX98373_W200C_INT_EN3, 0x00},
	{MAX98373_W200D_INT_FWAG_CWW1, 0x00},
	{MAX98373_W200E_INT_FWAG_CWW2, 0x00},
	{MAX98373_W200F_INT_FWAG_CWW3, 0x00},
	{MAX98373_W2010_IWQ_CTWW, 0x00},
	{MAX98373_W2014_THEWM_WAWN_THWESH, 0x10},
	{MAX98373_W2015_THEWM_SHDN_THWESH, 0x27},
	{MAX98373_W2016_THEWM_HYSTEWESIS, 0x01},
	{MAX98373_W2017_THEWM_FOWDBACK_SET, 0xC0},
	{MAX98373_W2018_THEWM_FOWDBACK_EN, 0x00},
	{MAX98373_W201E_PIN_DWIVE_STWENGTH, 0x55},
	{MAX98373_W2020_PCM_TX_HIZ_EN_1, 0xFE},
	{MAX98373_W2021_PCM_TX_HIZ_EN_2, 0xFF},
	{MAX98373_W2022_PCM_TX_SWC_1, 0x00},
	{MAX98373_W2023_PCM_TX_SWC_2, 0x00},
	{MAX98373_W2024_PCM_DATA_FMT_CFG, 0xC0},
	{MAX98373_W2025_AUDIO_IF_MODE, 0x00},
	{MAX98373_W2026_PCM_CWOCK_WATIO, 0x04},
	{MAX98373_W2027_PCM_SW_SETUP_1, 0x08},
	{MAX98373_W2028_PCM_SW_SETUP_2, 0x88},
	{MAX98373_W2029_PCM_TO_SPK_MONO_MIX_1, 0x00},
	{MAX98373_W202A_PCM_TO_SPK_MONO_MIX_2, 0x00},
	{MAX98373_W202B_PCM_WX_EN, 0x00},
	{MAX98373_W202C_PCM_TX_EN, 0x00},
	{MAX98373_W202E_ICC_WX_CH_EN_1, 0x00},
	{MAX98373_W202F_ICC_WX_CH_EN_2, 0x00},
	{MAX98373_W2030_ICC_TX_HIZ_EN_1, 0xFF},
	{MAX98373_W2031_ICC_TX_HIZ_EN_2, 0xFF},
	{MAX98373_W2032_ICC_WINK_EN_CFG, 0x30},
	{MAX98373_W2034_ICC_TX_CNTW, 0x00},
	{MAX98373_W2035_ICC_TX_EN, 0x00},
	{MAX98373_W2036_SOUNDWIWE_CTWW, 0x05},
	{MAX98373_W203D_AMP_DIG_VOW_CTWW, 0x00},
	{MAX98373_W203E_AMP_PATH_GAIN, 0x08},
	{MAX98373_W203F_AMP_DSP_CFG, 0x02},
	{MAX98373_W2040_TONE_GEN_CFG, 0x00},
	{MAX98373_W2041_AMP_CFG, 0x03},
	{MAX98373_W2042_AMP_EDGE_WATE_CFG, 0x00},
	{MAX98373_W2043_AMP_EN, 0x00},
	{MAX98373_W2046_IV_SENSE_ADC_DSP_CFG, 0x04},
	{MAX98373_W2047_IV_SENSE_ADC_EN, 0x00},
	{MAX98373_W2051_MEAS_ADC_SAMPWING_WATE, 0x00},
	{MAX98373_W2052_MEAS_ADC_PVDD_FWT_CFG, 0x00},
	{MAX98373_W2053_MEAS_ADC_THEWM_FWT_CFG, 0x00},
	{MAX98373_W2054_MEAS_ADC_PVDD_CH_WEADBACK, 0x00},
	{MAX98373_W2055_MEAS_ADC_THEWM_CH_WEADBACK, 0x00},
	{MAX98373_W2056_MEAS_ADC_PVDD_CH_EN, 0x00},
	{MAX98373_W2090_BDE_WVW_HOWD, 0x00},
	{MAX98373_W2091_BDE_GAIN_ATK_WEW_WATE, 0x00},
	{MAX98373_W2092_BDE_CWIPPEW_MODE, 0x00},
	{MAX98373_W2097_BDE_W1_THWESH, 0x00},
	{MAX98373_W2098_BDE_W2_THWESH, 0x00},
	{MAX98373_W2099_BDE_W3_THWESH, 0x00},
	{MAX98373_W209A_BDE_W4_THWESH, 0x00},
	{MAX98373_W209B_BDE_THWESH_HYST, 0x00},
	{MAX98373_W20A8_BDE_W1_CFG_1, 0x00},
	{MAX98373_W20A9_BDE_W1_CFG_2, 0x00},
	{MAX98373_W20AA_BDE_W1_CFG_3, 0x00},
	{MAX98373_W20AB_BDE_W2_CFG_1, 0x00},
	{MAX98373_W20AC_BDE_W2_CFG_2, 0x00},
	{MAX98373_W20AD_BDE_W2_CFG_3, 0x00},
	{MAX98373_W20AE_BDE_W3_CFG_1, 0x00},
	{MAX98373_W20AF_BDE_W3_CFG_2, 0x00},
	{MAX98373_W20B0_BDE_W3_CFG_3, 0x00},
	{MAX98373_W20B1_BDE_W4_CFG_1, 0x00},
	{MAX98373_W20B2_BDE_W4_CFG_2, 0x00},
	{MAX98373_W20B3_BDE_W4_CFG_3, 0x00},
	{MAX98373_W20B4_BDE_INFINITE_HOWD_WEWEASE, 0x00},
	{MAX98373_W20B5_BDE_EN, 0x00},
	{MAX98373_W20B6_BDE_CUW_STATE_WEADBACK, 0x00},
	{MAX98373_W20D1_DHT_CFG, 0x01},
	{MAX98373_W20D2_DHT_ATTACK_CFG, 0x02},
	{MAX98373_W20D3_DHT_WEWEASE_CFG, 0x03},
	{MAX98373_W20D4_DHT_EN, 0x00},
	{MAX98373_W20E0_WIMITEW_THWESH_CFG, 0x00},
	{MAX98373_W20E1_WIMITEW_ATK_WEW_WATES, 0x00},
	{MAX98373_W20E2_WIMITEW_EN, 0x00},
	{MAX98373_W20FE_DEVICE_AUTO_WESTAWT_CFG, 0x00},
	{MAX98373_W20FF_GWOBAW_SHDN, 0x00},
	{MAX98373_W21FF_WEV_ID, 0x42},
};

static boow max98373_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98373_W21FF_WEV_ID:
	case MAX98373_W2010_IWQ_CTWW:
	/* SoundWiwe Contwow Powt Wegistews */
	case MAX98373_W0040_SCP_INIT_STAT_1 ... MAX98373_W0070_SCP_FWAME_CTWW:
	/* Soundwiwe Data Powt 1 Wegistews */
	case MAX98373_W0100_DP1_INIT_STAT ... MAX98373_W0137_DP1_BWOCK_CTWW3:
	/* Soundwiwe Data Powt 3 Wegistews */
	case MAX98373_W0300_DP3_INIT_STAT ... MAX98373_W0337_DP3_BWOCK_CTWW3:
	case MAX98373_W2000_SW_WESET ... MAX98373_W200C_INT_EN3:
	case MAX98373_W2014_THEWM_WAWN_THWESH
		... MAX98373_W2018_THEWM_FOWDBACK_EN:
	case MAX98373_W201E_PIN_DWIVE_STWENGTH
		... MAX98373_W2036_SOUNDWIWE_CTWW:
	case MAX98373_W203D_AMP_DIG_VOW_CTWW ... MAX98373_W2043_AMP_EN:
	case MAX98373_W2046_IV_SENSE_ADC_DSP_CFG
		... MAX98373_W2047_IV_SENSE_ADC_EN:
	case MAX98373_W2051_MEAS_ADC_SAMPWING_WATE
		... MAX98373_W2056_MEAS_ADC_PVDD_CH_EN:
	case MAX98373_W2090_BDE_WVW_HOWD ... MAX98373_W2092_BDE_CWIPPEW_MODE:
	case MAX98373_W2097_BDE_W1_THWESH
		... MAX98373_W209B_BDE_THWESH_HYST:
	case MAX98373_W20A8_BDE_W1_CFG_1 ... MAX98373_W20B3_BDE_W4_CFG_3:
	case MAX98373_W20B5_BDE_EN ... MAX98373_W20B6_BDE_CUW_STATE_WEADBACK:
	case MAX98373_W20D1_DHT_CFG ... MAX98373_W20D4_DHT_EN:
	case MAX98373_W20E0_WIMITEW_THWESH_CFG ... MAX98373_W20E2_WIMITEW_EN:
	case MAX98373_W20FE_DEVICE_AUTO_WESTAWT_CFG
		... MAX98373_W20FF_GWOBAW_SHDN:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
};

static boow max98373_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98373_W2054_MEAS_ADC_PVDD_CH_WEADBACK:
	case MAX98373_W2055_MEAS_ADC_THEWM_CH_WEADBACK:
	case MAX98373_W20B6_BDE_CUW_STATE_WEADBACK:
	case MAX98373_W20FF_GWOBAW_SHDN:
	case MAX98373_W21FF_WEV_ID:
	/* SoundWiwe Contwow Powt Wegistews */
	case MAX98373_W0040_SCP_INIT_STAT_1 ... MAX98373_W0070_SCP_FWAME_CTWW:
	/* Soundwiwe Data Powt 1 Wegistews */
	case MAX98373_W0100_DP1_INIT_STAT ... MAX98373_W0137_DP1_BWOCK_CTWW3:
	/* Soundwiwe Data Powt 3 Wegistews */
	case MAX98373_W0300_DP3_INIT_STAT ... MAX98373_W0337_DP3_BWOCK_CTWW3:
	case MAX98373_W2000_SW_WESET ... MAX98373_W2009_INT_FWAG3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config max98373_sdw_wegmap = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.max_wegistew = MAX98373_W21FF_WEV_ID,
	.weg_defauwts  = max98373_weg,
	.num_weg_defauwts = AWWAY_SIZE(max98373_weg),
	.weadabwe_weg = max98373_weadabwe_wegistew,
	.vowatiwe_weg = max98373_vowatiwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

/* Powew management functions and stwuctuwe */
static __maybe_unused int max98373_suspend(stwuct device *dev)
{
	stwuct max98373_pwiv *max98373 = dev_get_dwvdata(dev);
	int i;

	/* cache feedback wegistew vawues befowe suspend */
	fow (i = 0; i < max98373->cache_num; i++)
		wegmap_wead(max98373->wegmap, max98373->cache[i].weg, &max98373->cache[i].vaw);

	wegcache_cache_onwy(max98373->wegmap, twue);

	wetuwn 0;
}

#define MAX98373_PWOBE_TIMEOUT 5000

static __maybe_unused int max98373_wesume(stwuct device *dev)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	stwuct max98373_pwiv *max98373 = dev_get_dwvdata(dev);
	unsigned wong time;

	if (!max98373->fiwst_hw_init)
		wetuwn 0;

	if (!swave->unattach_wequest)
		goto wegmap_sync;

	time = wait_fow_compwetion_timeout(&swave->initiawization_compwete,
					   msecs_to_jiffies(MAX98373_PWOBE_TIMEOUT));
	if (!time) {
		dev_eww(dev, "Initiawization not compwete, timed out\n");
		sdw_show_ping_status(swave->bus, twue);

		wetuwn -ETIMEDOUT;
	}

wegmap_sync:
	swave->unattach_wequest = 0;
	wegcache_cache_onwy(max98373->wegmap, fawse);
	wegcache_sync(max98373->wegmap);

	wetuwn 0;
}

static const stwuct dev_pm_ops max98373_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(max98373_suspend, max98373_wesume)
	SET_WUNTIME_PM_OPS(max98373_suspend, max98373_wesume, NUWW)
};

static int max98373_wead_pwop(stwuct sdw_swave *swave)
{
	stwuct sdw_swave_pwop *pwop = &swave->pwop;
	int nvaw, i;
	u32 bit;
	unsigned wong addw;
	stwuct sdw_dpn_pwop *dpn;

	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY;

	/* BITMAP: 00001000  Datapowt 3 is active */
	pwop->souwce_powts = BIT(3);
	/* BITMAP: 00000010  Datapowt 1 is active */
	pwop->sink_powts = BIT(1);
	pwop->paging_suppowt = twue;
	pwop->cwk_stop_timeout = 20;

	nvaw = hweight32(pwop->souwce_powts);
	pwop->swc_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
					  sizeof(*pwop->swc_dpn_pwop),
					  GFP_KEWNEW);
	if (!pwop->swc_dpn_pwop)
		wetuwn -ENOMEM;

	i = 0;
	dpn = pwop->swc_dpn_pwop;
	addw = pwop->souwce_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FUWW;
		dpn[i].simpwe_ch_pwep_sm = twue;
		dpn[i].ch_pwep_timeout = 10;
		i++;
	}

	/* do this again fow sink now */
	nvaw = hweight32(pwop->sink_powts);
	pwop->sink_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
					   sizeof(*pwop->sink_dpn_pwop),
					   GFP_KEWNEW);
	if (!pwop->sink_dpn_pwop)
		wetuwn -ENOMEM;

	i = 0;
	dpn = pwop->sink_dpn_pwop;
	addw = pwop->sink_powts;
	fow_each_set_bit(bit, &addw, 32) {
		dpn[i].num = bit;
		dpn[i].type = SDW_DPN_FUWW;
		dpn[i].simpwe_ch_pwep_sm = twue;
		dpn[i].ch_pwep_timeout = 10;
		i++;
	}

	/* set the timeout vawues */
	pwop->cwk_stop_timeout = 20;

	wetuwn 0;
}

static int max98373_io_init(stwuct sdw_swave *swave)
{
	stwuct device *dev = &swave->dev;
	stwuct max98373_pwiv *max98373 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(max98373->wegmap, fawse);
	if (max98373->fiwst_hw_init)
		wegcache_cache_bypass(max98373->wegmap, twue);

	/*
	 * PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached
	 */
	if (!max98373->fiwst_hw_init)
		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(dev);

	pm_wuntime_get_nowesume(dev);

	/* Softwawe Weset */
	max98373_weset(max98373, dev);

	/* Set soundwiwe mode */
	wegmap_wwite(max98373->wegmap, MAX98373_W2025_AUDIO_IF_MODE, 3);
	/* Enabwe ADC */
	wegmap_wwite(max98373->wegmap, MAX98373_W2047_IV_SENSE_ADC_EN, 3);
	/* Set defauwt Soundwiwe cwock */
	wegmap_wwite(max98373->wegmap, MAX98373_W2036_SOUNDWIWE_CTWW, 5);
	/* Set defauwt sampwing wate fow speakew and IVDAC */
	wegmap_wwite(max98373->wegmap, MAX98373_W2028_PCM_SW_SETUP_2, 0x88);
	/* IV defauwt swot configuwation */
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W2020_PCM_TX_HIZ_EN_1,
		     0xFF);
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W2021_PCM_TX_HIZ_EN_2,
		     0xFF);
	/* W/W mix configuwation */
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W2029_PCM_TO_SPK_MONO_MIX_1,
		     0x80);
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W202A_PCM_TO_SPK_MONO_MIX_2,
		     0x1);
	/* Enabwe DC bwockew */
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W203F_AMP_DSP_CFG,
		     0x3);
	/* Enabwe IMON VMON DC bwockew */
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W2046_IV_SENSE_ADC_DSP_CFG,
		     0x7);
	/* vowtage, cuwwent swot configuwation */
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W2022_PCM_TX_SWC_1,
		     (max98373->i_swot << MAX98373_PCM_TX_CH_SWC_A_I_SHIFT |
		     max98373->v_swot) & 0xFF);
	if (max98373->v_swot < 8)
		wegmap_update_bits(max98373->wegmap,
				   MAX98373_W2020_PCM_TX_HIZ_EN_1,
				   1 << max98373->v_swot, 0);
	ewse
		wegmap_update_bits(max98373->wegmap,
				   MAX98373_W2021_PCM_TX_HIZ_EN_2,
				   1 << (max98373->v_swot - 8), 0);

	if (max98373->i_swot < 8)
		wegmap_update_bits(max98373->wegmap,
				   MAX98373_W2020_PCM_TX_HIZ_EN_1,
				   1 << max98373->i_swot, 0);
	ewse
		wegmap_update_bits(max98373->wegmap,
				   MAX98373_W2021_PCM_TX_HIZ_EN_2,
				   1 << (max98373->i_swot - 8), 0);

	/* speakew feedback swot configuwation */
	wegmap_wwite(max98373->wegmap,
		     MAX98373_W2023_PCM_TX_SWC_2,
		     max98373->spkfb_swot & 0xFF);

	/* Set intewweave mode */
	if (max98373->intewweave_mode)
		wegmap_update_bits(max98373->wegmap,
				   MAX98373_W2024_PCM_DATA_FMT_CFG,
				   MAX98373_PCM_TX_CH_INTEWWEAVE_MASK,
				   MAX98373_PCM_TX_CH_INTEWWEAVE_MASK);

	/* Speakew enabwe */
	wegmap_update_bits(max98373->wegmap,
			   MAX98373_W2043_AMP_EN,
			   MAX98373_SPK_EN_MASK, 1);

	wegmap_wwite(max98373->wegmap, MAX98373_W20B5_BDE_EN, 1);
	wegmap_wwite(max98373->wegmap, MAX98373_W20E2_WIMITEW_EN, 1);

	if (max98373->fiwst_hw_init) {
		wegcache_cache_bypass(max98373->wegmap, fawse);
		wegcache_mawk_diwty(max98373->wegmap);
	}

	max98373->fiwst_hw_init = twue;
	max98373->hw_init = twue;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;
}

static int max98373_cwock_cawcuwate(stwuct sdw_swave *swave,
				    unsigned int cwk_fweq)
{
	int x, y;
	static const int max98373_cwk_famiwy[] = {
		7680000, 8400000, 9600000, 11289600,
		12000000, 12288000, 13000000
	};

	fow (x = 0; x < 4; x++)
		fow (y = 0; y < AWWAY_SIZE(max98373_cwk_famiwy); y++)
			if (cwk_fweq == (max98373_cwk_famiwy[y] >> x))
				wetuwn (x << 3) + y;

	/* Set defauwt cwock (12.288 Mhz) if the vawue is not in the wist */
	dev_eww(&swave->dev, "Wequested cwock not found. (cwk_fweq = %d)\n",
		cwk_fweq);
	wetuwn 0x5;
}

static int max98373_cwock_config(stwuct sdw_swave *swave,
				 stwuct sdw_bus_pawams *pawams)
{
	stwuct device *dev = &swave->dev;
	stwuct max98373_pwiv *max98373 = dev_get_dwvdata(dev);
	unsigned int cwk_fweq, vawue;

	cwk_fweq = (pawams->cuww_dw_fweq >> 1);

	/*
	 *	Sewect the pwopew vawue fow the wegistew based on the
	 *	wequested cwock. If the vawue is not in the wist,
	 *	use weasonabwe defauwt - 12.288 Mhz
	 */
	vawue = max98373_cwock_cawcuwate(swave, cwk_fweq);

	/* SWCWK */
	wegmap_wwite(max98373->wegmap, MAX98373_W2036_SOUNDWIWE_CTWW, vawue);

	/* The defauwt Sampwing Wate vawue fow IV is 48KHz*/
	wegmap_wwite(max98373->wegmap, MAX98373_W2028_PCM_SW_SETUP_2, 0x88);

	wetuwn 0;
}

#define MAX98373_WATES SNDWV_PCM_WATE_8000_96000
#define MAX98373_FOWMATS (SNDWV_PCM_FMTBIT_S32_WE)

static int max98373_sdw_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98373_pwiv *max98373 =
		snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_config stweam_config = {0};
	stwuct sdw_powt_config powt_config = {0};
	stwuct sdw_stweam_wuntime *sdw_stweam;
	int wet, chan_sz, sampwing_wate;

	sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	if (!max98373->swave)
		wetuwn -EINVAW;

	snd_sdw_pawams_to_config(substweam, pawams, &stweam_config, &powt_config);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		powt_config.num = 1;

		if (max98373->swot) {
			stweam_config.ch_count = max98373->swot;
			powt_config.ch_mask = max98373->wx_mask;
		}
	} ewse {
		powt_config.num = 3;

		/* onwy IV awe suppowted by captuwe */
		stweam_config.ch_count = 2;
		powt_config.ch_mask = GENMASK((int)stweam_config.ch_count - 1, 0);
	}

	wet = sdw_stweam_add_swave(max98373->swave, &stweam_config,
				   &powt_config, 1, sdw_stweam);
	if (wet) {
		dev_eww(dai->dev, "Unabwe to configuwe powt\n");
		wetuwn wet;
	}

	if (pawams_channews(pawams) > 16) {
		dev_eww(component->dev, "Unsuppowted channews %d\n",
			pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	/* Channew size configuwation */
	switch (snd_pcm_fowmat_width(pawams_fowmat(pawams))) {
	case 16:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_16;
		bweak;
	case 24:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_24;
		bweak;
	case 32:
		chan_sz = MAX98373_PCM_MODE_CFG_CHANSZ_32;
		bweak;
	defauwt:
		dev_eww(component->dev, "Channew size unsuppowted %d\n",
			pawams_fowmat(pawams));
		wetuwn -EINVAW;
	}

	max98373->ch_size = snd_pcm_fowmat_width(pawams_fowmat(pawams));

	wegmap_update_bits(max98373->wegmap,
			   MAX98373_W2024_PCM_DATA_FMT_CFG,
			   MAX98373_PCM_MODE_CFG_CHANSZ_MASK, chan_sz);

	dev_dbg(component->dev, "Fowmat suppowted %d", pawams_fowmat(pawams));

	/* Sampwing wate configuwation */
	switch (pawams_wate(pawams)) {
	case 8000:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_8000;
		bweak;
	case 11025:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_11025;
		bweak;
	case 12000:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_12000;
		bweak;
	case 16000:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_16000;
		bweak;
	case 22050:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_22050;
		bweak;
	case 24000:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_24000;
		bweak;
	case 32000:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_32000;
		bweak;
	case 44100:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_44100;
		bweak;
	case 48000:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_48000;
		bweak;
	case 88200:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_88200;
		bweak;
	case 96000:
		sampwing_wate = MAX98373_PCM_SW_SET1_SW_96000;
		bweak;
	defauwt:
		dev_eww(component->dev, "Wate %d is not suppowted\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	/* set cowwect sampwing fwequency */
	wegmap_update_bits(max98373->wegmap,
			   MAX98373_W2028_PCM_SW_SETUP_2,
			   MAX98373_PCM_SW_SET2_SW_MASK,
			   sampwing_wate << MAX98373_PCM_SW_SET2_SW_SHIFT);

	/* set sampwing wate of IV */
	wegmap_update_bits(max98373->wegmap,
			   MAX98373_W2028_PCM_SW_SETUP_2,
			   MAX98373_PCM_SW_SET2_IVADC_SW_MASK,
			   sampwing_wate);

	wetuwn 0;
}

static int max98373_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98373_pwiv *max98373 =
		snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!max98373->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(max98373->swave, sdw_stweam);
	wetuwn 0;
}

static int max98373_set_sdw_stweam(stwuct snd_soc_dai *dai,
				   void *sdw_stweam, int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void max98373_shutdown(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int max98373_sdw_set_tdm_swot(stwuct snd_soc_dai *dai,
				     unsigned int tx_mask,
				     unsigned int wx_mask,
				     int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98373_pwiv *max98373 =
		snd_soc_component_get_dwvdata(component);

	/* tx_mask is unused since it's iwwewevant fow I/V feedback */
	if (tx_mask)
		wetuwn -EINVAW;

	if (!wx_mask && !swots && !swot_width)
		max98373->tdm_mode = fawse;
	ewse
		max98373->tdm_mode = twue;

	max98373->wx_mask = wx_mask;
	max98373->swot = swots;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops max98373_dai_sdw_ops = {
	.hw_pawams = max98373_sdw_dai_hw_pawams,
	.hw_fwee = max98373_pcm_hw_fwee,
	.set_stweam = max98373_set_sdw_stweam,
	.shutdown = max98373_shutdown,
	.set_tdm_swot = max98373_sdw_set_tdm_swot,
};

static stwuct snd_soc_dai_dwivew max98373_sdw_dai[] = {
	{
		.name = "max98373-aif1",
		.pwayback = {
			.stweam_name = "HiFi Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MAX98373_WATES,
			.fowmats = MAX98373_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "HiFi Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = MAX98373_WATES,
			.fowmats = MAX98373_FOWMATS,
		},
		.ops = &max98373_dai_sdw_ops,
	}
};

static int max98373_init(stwuct sdw_swave *swave, stwuct wegmap *wegmap)
{
	stwuct max98373_pwiv *max98373;
	int wet;
	int i;
	stwuct device *dev = &swave->dev;

	/*  Awwocate and assign pwivate dwivew data stwuctuwe  */
	max98373 = devm_kzawwoc(dev, sizeof(*max98373), GFP_KEWNEW);
	if (!max98373)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, max98373);
	max98373->wegmap = wegmap;
	max98373->swave = swave;

	wegcache_cache_onwy(max98373->wegmap, twue);

	max98373->cache_num = AWWAY_SIZE(max98373_sdw_cache_weg);
	max98373->cache = devm_kcawwoc(dev, max98373->cache_num,
				       sizeof(*max98373->cache),
				       GFP_KEWNEW);
	if (!max98373->cache)
		wetuwn -ENOMEM;

	fow (i = 0; i < max98373->cache_num; i++)
		max98373->cache[i].weg = max98373_sdw_cache_weg[i];

	/* Wead vowtage and swot configuwation */
	max98373_swot_config(dev, max98373);

	max98373->hw_init = fawse;
	max98373->fiwst_hw_init = fawse;

	/* codec wegistwation  */
	wet = devm_snd_soc_wegistew_component(dev, &soc_codec_dev_max98373_sdw,
					      max98373_sdw_dai,
					      AWWAY_SIZE(max98373_sdw_dai));
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew codec: %d\n", wet);
		wetuwn wet;
	}

	/* set autosuspend pawametews */
	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);

	/* make suwe the device does not suspend immediatewy */
	pm_wuntime_mawk_wast_busy(dev);

	pm_wuntime_enabwe(dev);

	/* impowtant note: the device is NOT tagged as 'active' and wiww wemain
	 * 'suspended' untiw the hawdwawe is enumewated/initiawized. This is wequiwed
	 * to make suwe the ASoC fwamewowk use of pm_wuntime_get_sync() does not siwentwy
	 * faiw with -EACCESS because of wace conditions between cawd cweation and enumewation
	 */

	wetuwn 0;
}

static int max98373_update_status(stwuct sdw_swave *swave,
				  enum sdw_swave_status status)
{
	stwuct max98373_pwiv *max98373 = dev_get_dwvdata(&swave->dev);

	if (status == SDW_SWAVE_UNATTACHED)
		max98373->hw_init = fawse;

	/*
	 * Pewfowm initiawization onwy if swave status is SDW_SWAVE_ATTACHED
	 */
	if (max98373->hw_init || status != SDW_SWAVE_ATTACHED)
		wetuwn 0;

	/* pewfowm I/O twansfews wequiwed fow Swave initiawization */
	wetuwn max98373_io_init(swave);
}

static int max98373_bus_config(stwuct sdw_swave *swave,
			       stwuct sdw_bus_pawams *pawams)
{
	int wet;

	wet = max98373_cwock_config(swave, pawams);
	if (wet < 0)
		dev_eww(&swave->dev, "Invawid cwk config");

	wetuwn wet;
}

/*
 * swave_ops: cawwbacks fow get_cwock_stop_mode, cwock_stop and
 * powt_pwep awe not defined fow now
 */
static stwuct sdw_swave_ops max98373_swave_ops = {
	.wead_pwop = max98373_wead_pwop,
	.update_status = max98373_update_status,
	.bus_config = max98373_bus_config,
};

static int max98373_sdw_pwobe(stwuct sdw_swave *swave,
			      const stwuct sdw_device_id *id)
{
	stwuct wegmap *wegmap;

	/* Wegmap Initiawization */
	wegmap = devm_wegmap_init_sdw(swave, &max98373_sdw_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn max98373_init(swave, wegmap);
}

static int max98373_sdw_wemove(stwuct sdw_swave *swave)
{
	pm_wuntime_disabwe(&swave->dev);

	wetuwn 0;
}

#if defined(CONFIG_OF)
static const stwuct of_device_id max98373_of_match[] = {
	{ .compatibwe = "maxim,max98373", },
	{},
};
MODUWE_DEVICE_TABWE(of, max98373_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id max98373_acpi_match[] = {
	{ "MX98373", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, max98373_acpi_match);
#endif

static const stwuct sdw_device_id max98373_id[] = {
	SDW_SWAVE_ENTWY(0x019F, 0x8373, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, max98373_id);

static stwuct sdw_dwivew max98373_sdw_dwivew = {
	.dwivew = {
		.name = "max98373",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = of_match_ptw(max98373_of_match),
		.acpi_match_tabwe = ACPI_PTW(max98373_acpi_match),
		.pm = &max98373_pm,
	},
	.pwobe = max98373_sdw_pwobe,
	.wemove = max98373_sdw_wemove,
	.ops = &max98373_swave_ops,
	.id_tabwe = max98373_id,
};

moduwe_sdw_dwivew(max98373_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC MAX98373 dwivew SDW");
MODUWE_AUTHOW("Oweg Shewbakov <oweg.shewbakov@maximintegwated.com>");
MODUWE_WICENSE("GPW v2");
