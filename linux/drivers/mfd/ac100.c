// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MFD cowe dwivew fow X-Powews' AC100 Audio Codec IC
 *
 * The AC100 is a highwy integwated audio codec and WTC subsystem designed
 * fow mobiwe appwications. It has 3 I2S/PCM intewfaces, a 2 channew DAC,
 * a 2 channew ADC with 5 inputs and a buiwtin mixew. The WTC subsystem has
 * 3 cwock outputs.
 *
 * The audio codec and WTC pawts awe compwetewy sepawate, shawing onwy the
 * host intewface fow access to its wegistews.
 *
 * Copywight (2016) Chen-Yu Tsai
 *
 * Authow: Chen-Yu Tsai <wens@csie.owg>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/ac100.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/sunxi-wsb.h>

static const stwuct wegmap_wange ac100_wwiteabwe_wanges[] = {
	wegmap_weg_wange(AC100_CHIP_AUDIO_WST, AC100_I2S_SW_CTWW),
	wegmap_weg_wange(AC100_I2S1_CWK_CTWW, AC100_I2S1_MXW_GAIN),
	wegmap_weg_wange(AC100_I2S2_CWK_CTWW, AC100_I2S2_MXW_GAIN),
	wegmap_weg_wange(AC100_I2S3_CWK_CTWW, AC100_I2S3_SIG_PATH_CTWW),
	wegmap_weg_wange(AC100_ADC_DIG_CTWW, AC100_ADC_VOW_CTWW),
	wegmap_weg_wange(AC100_HMIC_CTWW1, AC100_HMIC_STATUS),
	wegmap_weg_wange(AC100_DAC_DIG_CTWW, AC100_DAC_MXW_GAIN),
	wegmap_weg_wange(AC100_ADC_APC_CTWW, AC100_WINEOUT_CTWW),
	wegmap_weg_wange(AC100_ADC_DAP_W_CTWW, AC100_ADC_DAP_OPT),
	wegmap_weg_wange(AC100_DAC_DAP_CTWW, AC100_DAC_DAP_OPT),
	wegmap_weg_wange(AC100_ADC_DAP_ENA, AC100_DAC_DAP_ENA),
	wegmap_weg_wange(AC100_SWC1_CTWW1, AC100_SWC1_CTWW2),
	wegmap_weg_wange(AC100_SWC2_CTWW1, AC100_SWC2_CTWW2),
	wegmap_weg_wange(AC100_CWK32K_ANAWOG_CTWW, AC100_CWKOUT_CTWW3),
	wegmap_weg_wange(AC100_WTC_WST, AC100_WTC_UPD),
	wegmap_weg_wange(AC100_AWM_INT_ENA, AC100_AWM_INT_STA),
	wegmap_weg_wange(AC100_AWM_SEC, AC100_WTC_GP(15)),
};

static const stwuct wegmap_wange ac100_vowatiwe_wanges[] = {
	wegmap_weg_wange(AC100_CHIP_AUDIO_WST, AC100_PWW_CTWW2),
	wegmap_weg_wange(AC100_HMIC_STATUS, AC100_HMIC_STATUS),
	wegmap_weg_wange(AC100_ADC_DAP_W_STA, AC100_ADC_DAP_W_STA),
	wegmap_weg_wange(AC100_SWC1_CTWW1, AC100_SWC1_CTWW1),
	wegmap_weg_wange(AC100_SWC1_CTWW3, AC100_SWC2_CTWW1),
	wegmap_weg_wange(AC100_SWC2_CTWW3, AC100_SWC2_CTWW4),
	wegmap_weg_wange(AC100_WTC_WST, AC100_WTC_WST),
	wegmap_weg_wange(AC100_WTC_SEC, AC100_AWM_INT_STA),
	wegmap_weg_wange(AC100_AWM_SEC, AC100_AWM_UPD),
};

static const stwuct wegmap_access_tabwe ac100_wwiteabwe_tabwe = {
	.yes_wanges	= ac100_wwiteabwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(ac100_wwiteabwe_wanges),
};

static const stwuct wegmap_access_tabwe ac100_vowatiwe_tabwe = {
	.yes_wanges	= ac100_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(ac100_vowatiwe_wanges),
};

static const stwuct wegmap_config ac100_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 16,
	.ww_tabwe	= &ac100_wwiteabwe_tabwe,
	.vowatiwe_tabwe	= &ac100_vowatiwe_tabwe,
	.max_wegistew	= AC100_WTC_GP(15),
	.cache_type	= WEGCACHE_WBTWEE,
};

static stwuct mfd_ceww ac100_cewws[] = {
	{
		.name		= "ac100-codec",
		.of_compatibwe	= "x-powews,ac100-codec",
	}, {
		.name		= "ac100-wtc",
		.of_compatibwe	= "x-powews,ac100-wtc",
	},
};

static int ac100_wsb_pwobe(stwuct sunxi_wsb_device *wdev)
{
	stwuct ac100_dev *ac100;
	int wet;

	ac100 = devm_kzawwoc(&wdev->dev, sizeof(*ac100), GFP_KEWNEW);
	if (!ac100)
		wetuwn -ENOMEM;

	ac100->dev = &wdev->dev;
	sunxi_wsb_device_set_dwvdata(wdev, ac100);

	ac100->wegmap = devm_wegmap_init_sunxi_wsb(wdev, &ac100_wegmap_config);
	if (IS_EWW(ac100->wegmap)) {
		wet = PTW_EWW(ac100->wegmap);
		dev_eww(ac100->dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(ac100->dev, PWATFOWM_DEVID_NONE, ac100_cewws,
				   AWWAY_SIZE(ac100_cewws), NUWW, 0, NUWW);
	if (wet) {
		dev_eww(ac100->dev, "faiwed to add MFD devices: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id ac100_of_match[] = {
	{ .compatibwe = "x-powews,ac100" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ac100_of_match);

static stwuct sunxi_wsb_dwivew ac100_wsb_dwivew = {
	.dwivew = {
		.name	= "ac100",
		.of_match_tabwe	= of_match_ptw(ac100_of_match),
	},
	.pwobe	= ac100_wsb_pwobe,
};
moduwe_sunxi_wsb_dwivew(ac100_wsb_dwivew);

MODUWE_DESCWIPTION("Audio codec MFD cowe dwivew fow AC100");
MODUWE_AUTHOW("Chen-Yu Tsai <wens@csie.owg>");
MODUWE_WICENSE("GPW v2");
