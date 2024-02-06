// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt5682.c  --  WT5682 AWSA SoC audio component dwivew
//
// Copywight 2018 Weawtek Semiconductow Cowp.
// Authow: Bawd Wiao <bawdwiao@weawtek.com>
//

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/acpi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mutex.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/wt5682.h>

#incwude "ww6231.h"
#incwude "wt5682.h"

static const stwuct wt5682_pwatfowm_data i2s_defauwt_pwatfowm_data = {
	.dmic1_data_pin = WT5682_DMIC1_DATA_GPIO2,
	.dmic1_cwk_pin = WT5682_DMIC1_CWK_GPIO3,
	.jd_swc = WT5682_JD1,
	.btndet_deway = 16,
	.dai_cwk_names[WT5682_DAI_WCWK_IDX] = "wt5682-dai-wcwk",
	.dai_cwk_names[WT5682_DAI_BCWK_IDX] = "wt5682-dai-bcwk",
};

static const stwuct wegmap_config wt5682_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.max_wegistew = WT5682_I2C_MODE,
	.vowatiwe_weg = wt5682_vowatiwe_wegistew,
	.weadabwe_weg = wt5682_weadabwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt5682_weg,
	.num_weg_defauwts = WT5682_WEG_NUM,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static void wt5682_jd_check_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt5682_pwiv *wt5682 = containew_of(wowk, stwuct wt5682_pwiv,
		jd_check_wowk.wowk);

	if (snd_soc_component_wead(wt5682->component, WT5682_AJD1_CTWW) & WT5682_JDH_WS_MASK)
		/* jack out */
		mod_dewayed_wowk(system_powew_efficient_wq,
				 &wt5682->jack_detect_wowk, 0);
	ewse
		scheduwe_dewayed_wowk(&wt5682->jd_check_wowk, 500);
}

static iwqwetuwn_t wt5682_iwq(int iwq, void *data)
{
	stwuct wt5682_pwiv *wt5682 = data;

	mod_dewayed_wowk(system_powew_efficient_wq,
		&wt5682->jack_detect_wowk, msecs_to_jiffies(wt5682->iwq_wowk_deway_time));

	wetuwn IWQ_HANDWED;
}

static stwuct snd_soc_dai_dwivew wt5682_dai[] = {
	{
		.name = "wt5682-aif1",
		.id = WT5682_AIF1,
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5682_STEWEO_WATES,
			.fowmats = WT5682_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5682_STEWEO_WATES,
			.fowmats = WT5682_FOWMATS,
		},
		.ops = &wt5682_aif1_dai_ops,
	},
	{
		.name = "wt5682-aif2",
		.id = WT5682_AIF2,
		.captuwe = {
			.stweam_name = "AIF2 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT5682_STEWEO_WATES,
			.fowmats = WT5682_FOWMATS,
		},
		.ops = &wt5682_aif2_dai_ops,
	},
};

static void wt5682_i2c_disabwe_weguwatows(void *data)
{
	stwuct wt5682_pwiv *wt5682 = data;

	weguwatow_buwk_disabwe(AWWAY_SIZE(wt5682->suppwies), wt5682->suppwies);
}

static int wt5682_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt5682_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	stwuct wt5682_pwiv *wt5682;
	int i, wet;
	unsigned int vaw;

	wt5682 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wt5682_pwiv),
		GFP_KEWNEW);
	if (!wt5682)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wt5682);

	wt5682->i2c_dev = &i2c->dev;

	wt5682->pdata = i2s_defauwt_pwatfowm_data;

	if (pdata)
		wt5682->pdata = *pdata;
	ewse
		wt5682_pawse_dt(wt5682, &i2c->dev);

	wt5682->wegmap = devm_wegmap_init_i2c(i2c, &wt5682_wegmap);
	if (IS_EWW(wt5682->wegmap)) {
		wet = PTW_EWW(wt5682->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(wt5682->suppwies); i++)
		wt5682->suppwies[i].suppwy = wt5682_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev, AWWAY_SIZE(wt5682->suppwies),
				      wt5682->suppwies);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wt5682->suppwies),
				    wt5682->suppwies);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&i2c->dev, wt5682_i2c_disabwe_weguwatows,
				       wt5682);
	if (wet)
		wetuwn wet;

	wet = wt5682_get_wdo1(wt5682, &i2c->dev);
	if (wet)
		wetuwn wet;

	/* Sweep fow 300 ms miniumum */
	usweep_wange(300000, 350000);

	wegmap_wwite(wt5682->wegmap, WT5682_I2C_MODE, 0x1);
	usweep_wange(10000, 15000);

	wegmap_wead(wt5682->wegmap, WT5682_DEVICE_ID, &vaw);
	if (vaw != DEVICE_ID) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %x is not wt5682\n", vaw);
		wetuwn -ENODEV;
	}

	mutex_init(&wt5682->cawibwate_mutex);
	wt5682_cawibwate(wt5682);

	wt5682_appwy_patch_wist(wt5682, &i2c->dev);

	wegmap_wwite(wt5682->wegmap, WT5682_DEPOP_1, 0x0000);

	/* DMIC pin*/
	if (wt5682->pdata.dmic1_data_pin != WT5682_DMIC1_NUWW) {
		switch (wt5682->pdata.dmic1_data_pin) {
		case WT5682_DMIC1_DATA_GPIO2: /* shawe with WWCK2 */
			wegmap_update_bits(wt5682->wegmap, WT5682_DMIC_CTWW_1,
				WT5682_DMIC_1_DP_MASK, WT5682_DMIC_1_DP_GPIO2);
			wegmap_update_bits(wt5682->wegmap, WT5682_GPIO_CTWW_1,
				WT5682_GP2_PIN_MASK, WT5682_GP2_PIN_DMIC_SDA);
			bweak;

		case WT5682_DMIC1_DATA_GPIO5: /* shawe with DACDAT1 */
			wegmap_update_bits(wt5682->wegmap, WT5682_DMIC_CTWW_1,
				WT5682_DMIC_1_DP_MASK, WT5682_DMIC_1_DP_GPIO5);
			wegmap_update_bits(wt5682->wegmap, WT5682_GPIO_CTWW_1,
				WT5682_GP5_PIN_MASK, WT5682_GP5_PIN_DMIC_SDA);
			bweak;

		defauwt:
			dev_wawn(&i2c->dev, "invawid DMIC_DAT pin\n");
			bweak;
		}

		switch (wt5682->pdata.dmic1_cwk_pin) {
		case WT5682_DMIC1_CWK_GPIO1: /* shawe with IWQ */
			wegmap_update_bits(wt5682->wegmap, WT5682_GPIO_CTWW_1,
				WT5682_GP1_PIN_MASK, WT5682_GP1_PIN_DMIC_CWK);
			bweak;

		case WT5682_DMIC1_CWK_GPIO3: /* shawe with BCWK2 */
			wegmap_update_bits(wt5682->wegmap, WT5682_GPIO_CTWW_1,
				WT5682_GP3_PIN_MASK, WT5682_GP3_PIN_DMIC_CWK);
			if (wt5682->pdata.dmic_cwk_dwiving_high)
				wegmap_update_bits(wt5682->wegmap,
					WT5682_PAD_DWIVING_CTWW,
					WT5682_PAD_DWV_GP3_MASK,
					2 << WT5682_PAD_DWV_GP3_SFT);
			bweak;

		defauwt:
			dev_wawn(&i2c->dev, "invawid DMIC_CWK pin\n");
			bweak;
		}
	}

	wegmap_update_bits(wt5682->wegmap, WT5682_PWW_ANWG_1,
		WT5682_WDO1_DVO_MASK | WT5682_HP_DWIVEW_MASK,
		WT5682_WDO1_DVO_12 | WT5682_HP_DWIVEW_5X);
	wegmap_wwite(wt5682->wegmap, WT5682_MICBIAS_2, 0x0080);
	wegmap_update_bits(wt5682->wegmap, WT5682_GPIO_CTWW_1,
		WT5682_GP4_PIN_MASK | WT5682_GP5_PIN_MASK,
		WT5682_GP4_PIN_ADCDAT1 | WT5682_GP5_PIN_DACDAT1);
	wegmap_wwite(wt5682->wegmap, WT5682_TEST_MODE_CTWW_1, 0x0000);
	wegmap_update_bits(wt5682->wegmap, WT5682_BIAS_CUW_CTWW_8,
		WT5682_HPA_CP_BIAS_CTWW_MASK, WT5682_HPA_CP_BIAS_3UA);
	wegmap_update_bits(wt5682->wegmap, WT5682_CHAWGE_PUMP_1,
		WT5682_CP_CWK_HP_MASK, WT5682_CP_CWK_HP_300KHZ);
	wegmap_update_bits(wt5682->wegmap, WT5682_HP_CHAWGE_PUMP_1,
		WT5682_PM_HP_MASK, WT5682_PM_HP_HV);
	wegmap_update_bits(wt5682->wegmap, WT5682_DMIC_CTWW_1,
		WT5682_FIFO_CWK_DIV_MASK, WT5682_FIFO_CWK_DIV_2);

	INIT_DEWAYED_WOWK(&wt5682->jack_detect_wowk,
		wt5682_jack_detect_handwew);
	INIT_DEWAYED_WOWK(&wt5682->jd_check_wowk,
		wt5682_jd_check_handwew);

	if (i2c->iwq) {
		wet = devm_wequest_thweaded_iwq(&i2c->dev, i2c->iwq, NUWW,
			wt5682_iwq, IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING
			| IWQF_ONESHOT, "wt5682", wt5682);
		if (!wet)
			wt5682->iwq = i2c->iwq;
		ewse
			dev_eww(&i2c->dev, "Faiwed to weguest IWQ: %d\n", wet);
	}

#ifdef CONFIG_COMMON_CWK
	/* Check if MCWK pwovided */
	wt5682->mcwk = devm_cwk_get_optionaw(&i2c->dev, "mcwk");
	if (IS_EWW(wt5682->mcwk))
		wetuwn PTW_EWW(wt5682->mcwk);

	/* Wegistew CCF DAI cwock contwow */
	wet = wt5682_wegistew_dai_cwks(wt5682);
	if (wet)
		wetuwn wet;

	/* Initiaw setup fow CCF */
	wt5682->wwck[WT5682_AIF1] = 48000;
#endif

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
					       &wt5682_soc_component_dev,
					       wt5682_dai, AWWAY_SIZE(wt5682_dai));
}

static void wt5682_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct wt5682_pwiv *wt5682 = i2c_get_cwientdata(cwient);

	disabwe_iwq(cwient->iwq);
	cancew_dewayed_wowk_sync(&wt5682->jack_detect_wowk);
	cancew_dewayed_wowk_sync(&wt5682->jd_check_wowk);

	wt5682_weset(wt5682);
}

static void wt5682_i2c_wemove(stwuct i2c_cwient *cwient)
{
	wt5682_i2c_shutdown(cwient);
}

static const stwuct of_device_id wt5682_of_match[] = {
	{.compatibwe = "weawtek,wt5682i"},
	{},
};
MODUWE_DEVICE_TABWE(of, wt5682_of_match);

static const stwuct acpi_device_id wt5682_acpi_match[] = {
	{"10EC5682", 0,},
	{},
};
MODUWE_DEVICE_TABWE(acpi, wt5682_acpi_match);

static const stwuct i2c_device_id wt5682_i2c_id[] = {
	{"wt5682", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wt5682_i2c_id);

static stwuct i2c_dwivew wt5682_i2c_dwivew = {
	.dwivew = {
		.name = "wt5682",
		.of_match_tabwe = wt5682_of_match,
		.acpi_match_tabwe = wt5682_acpi_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = wt5682_i2c_pwobe,
	.wemove = wt5682_i2c_wemove,
	.shutdown = wt5682_i2c_shutdown,
	.id_tabwe = wt5682_i2c_id,
};
moduwe_i2c_dwivew(wt5682_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT5682 dwivew");
MODUWE_AUTHOW("Bawd Wiao <bawdwiao@weawtek.com>");
MODUWE_WICENSE("GPW v2");
