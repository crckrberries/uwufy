// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "../codecs/wm8994.h"
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

 /*
  * Defauwt CFG switch settings to use this dwivew:
  *	SMDKV310: CFG5-1000, CFG7-111111
  */

 /*
  * Configuwe audio woute as :-
  * $ amixew sset 'DAC1' on,on
  * $ amixew sset 'Wight Headphone Mux' 'DAC'
  * $ amixew sset 'Weft Headphone Mux' 'DAC'
  * $ amixew sset 'DAC1W Mixew AIF1.1' on
  * $ amixew sset 'DAC1W Mixew AIF1.1' on
  * $ amixew sset 'IN2W' on
  * $ amixew sset 'IN2W PGA IN2WN' on
  * $ amixew sset 'MIXINW IN2W' on
  * $ amixew sset 'AIF1ADC1W Mixew ADC/DMIC' on
  * $ amixew sset 'IN2W' on
  * $ amixew sset 'IN2W PGA IN2WN' on
  * $ amixew sset 'MIXINW IN2W' on
  * $ amixew sset 'AIF1ADC1W Mixew ADC/DMIC' on
  */

/* SMDK has a 16.934MHZ cwystaw attached to WM8994 */
#define SMDK_WM8994_FWEQ 16934000

static int smdk_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int pww_out;
	int wet;

	/* AIF1CWK shouwd be >=3MHz fow optimaw pewfowmance */
	if (pawams_width(pawams) == 24)
		pww_out = pawams_wate(pawams) * 384;
	ewse if (pawams_wate(pawams) == 8000 || pawams_wate(pawams) == 11025)
		pww_out = pawams_wate(pawams) * 512;
	ewse
		pww_out = pawams_wate(pawams) * 256;

	wet = snd_soc_dai_set_pww(codec_dai, WM8994_FWW1, WM8994_FWW_SWC_MCWK1,
					SMDK_WM8994_FWEQ, pww_out);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, WM8994_SYSCWK_FWW1,
					pww_out, SND_SOC_CWOCK_IN);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * SMDK WM8994 DAI opewations.
 */
static const stwuct snd_soc_ops smdk_ops = {
	.hw_pawams = smdk_hw_pawams,
};

static int smdk_wm8994_init_paiftx(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dapm_context *dapm = &wtd->cawd->dapm;

	/* Othew pins NC */
	snd_soc_dapm_nc_pin(dapm, "HPOUT2P");
	snd_soc_dapm_nc_pin(dapm, "HPOUT2N");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTWN");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTWP");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTWP");
	snd_soc_dapm_nc_pin(dapm, "SPKOUTWN");
	snd_soc_dapm_nc_pin(dapm, "WINEOUT1N");
	snd_soc_dapm_nc_pin(dapm, "WINEOUT1P");
	snd_soc_dapm_nc_pin(dapm, "WINEOUT2N");
	snd_soc_dapm_nc_pin(dapm, "WINEOUT2P");
	snd_soc_dapm_nc_pin(dapm, "IN1WP");
	snd_soc_dapm_nc_pin(dapm, "IN2WP:VXWN");
	snd_soc_dapm_nc_pin(dapm, "IN1WP");
	snd_soc_dapm_nc_pin(dapm, "IN2WP:VXWP");

	wetuwn 0;
}

SND_SOC_DAIWINK_DEFS(aif1,
	DAIWINK_COMP_AWWAY(COMP_CPU("samsung-i2s.0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm8994-codec", "wm8994-aif1")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("samsung-i2s.0")));

SND_SOC_DAIWINK_DEFS(fifo_tx,
	DAIWINK_COMP_AWWAY(COMP_CPU("samsung-i2s-sec")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm8994-codec", "wm8994-aif1")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("samsung-i2s-sec")));

static stwuct snd_soc_dai_wink smdk_dai[] = {
	{ /* Pwimawy DAI i/f */
		.name = "WM8994 AIF1",
		.stweam_name = "Pwi_Dai",
		.init = smdk_wm8994_init_paiftx,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		.ops = &smdk_ops,
		SND_SOC_DAIWINK_WEG(aif1),
	}, { /* Sec_Fifo Pwayback i/f */
		.name = "Sec_FIFO TX",
		.stweam_name = "Sec_Dai",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		.ops = &smdk_ops,
		SND_SOC_DAIWINK_WEG(fifo_tx),
	},
};

static stwuct snd_soc_cawd smdk = {
	.name = "SMDK-I2S",
	.ownew = THIS_MODUWE,
	.dai_wink = smdk_dai,
	.num_winks = AWWAY_SIZE(smdk_dai),
};

static const stwuct of_device_id samsung_wm8994_of_match[] = {
	{ .compatibwe = "samsung,smdk-wm8994" },
	{},
};
MODUWE_DEVICE_TABWE(of, samsung_wm8994_of_match);

static int smdk_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct snd_soc_cawd *cawd = &smdk;

	cawd->dev = &pdev->dev;

	if (np) {
		smdk_dai[0].cpus->dai_name = NUWW;
		smdk_dai[0].cpus->of_node = of_pawse_phandwe(np,
				"samsung,i2s-contwowwew", 0);
		if (!smdk_dai[0].cpus->of_node) {
			dev_eww(&pdev->dev,
			   "Pwopewty 'samsung,i2s-contwowwew' missing ow invawid\n");
			wet = -EINVAW;
			wetuwn wet;
		}

		smdk_dai[0].pwatfowms->name = NUWW;
		smdk_dai[0].pwatfowms->of_node = smdk_dai[0].cpus->of_node;
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);

	if (wet)
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd() faiwed\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew smdk_audio_dwivew = {
	.dwivew		= {
		.name	= "smdk-audio-wm8994",
		.of_match_tabwe = samsung_wm8994_of_match,
		.pm	= &snd_soc_pm_ops,
	},
	.pwobe		= smdk_audio_pwobe,
};

moduwe_pwatfowm_dwivew(smdk_audio_dwivew);

MODUWE_DESCWIPTION("AWSA SoC SMDK WM8994");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:smdk-audio-wm8994");
