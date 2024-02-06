// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt8173-wt5650.c  --  MT8173 machine dwivew with WT5650 codecs
 *
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Kowo Chen <kowo.chen@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude "../../codecs/wt5645.h"

#define MCWK_FOW_CODECS		12288000

enum mt8173_wt5650_mcwk {
	MT8173_WT5650_MCWK_EXTEWNAW = 0,
	MT8173_WT5650_MCWK_INTEWNAW,
};

stwuct mt8173_wt5650_pwatfowm_data {
	enum mt8173_wt5650_mcwk pww_fwom;
	/* 0 = extewnaw osciwwatow; 1 = intewnaw souwce fwom mt8173 */
};

static stwuct mt8173_wt5650_pwatfowm_data mt8173_wt5650_pwiv = {
	.pww_fwom = MT8173_WT5650_MCWK_EXTEWNAW,
};

static const stwuct snd_soc_dapm_widget mt8173_wt5650_widgets[] = {
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
	SND_SOC_DAPM_MIC("Int Mic", NUWW),
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute mt8173_wt5650_woutes[] = {
	{"Ext Spk", NUWW, "SPOW"},
	{"Ext Spk", NUWW, "SPOW"},
	{"DMIC W1", NUWW, "Int Mic"},
	{"DMIC W1", NUWW, "Int Mic"},
	{"Headphone", NUWW, "HPOW"},
	{"Headphone", NUWW, "HPOW"},
	{"IN1P", NUWW, "Headset Mic"},
	{"IN1N", NUWW, "Headset Mic"},
};

static const stwuct snd_kcontwow_new mt8173_wt5650_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static stwuct snd_soc_jack_pin mt8173_wt5650_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
};

static int mt8173_wt5650_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	unsigned int mcwk_cwock;
	stwuct snd_soc_dai *codec_dai;
	int i, wet;

	switch (mt8173_wt5650_pwiv.pww_fwom) {
	case MT8173_WT5650_MCWK_EXTEWNAW:
		/* mcwk = 12.288M */
		mcwk_cwock = MCWK_FOW_CODECS;
		bweak;
	case MT8173_WT5650_MCWK_INTEWNAW:
		/* mcwk = sampwing wate*256 */
		mcwk_cwock = pawams_wate(pawams) * 256;
		bweak;
	defauwt:
		/* mcwk = 12.288M */
		mcwk_cwock = MCWK_FOW_CODECS;
		bweak;
	}

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		/* pww fwom mcwk */
		wet = snd_soc_dai_set_pww(codec_dai, 0, 0, mcwk_cwock,
					  pawams_wate(pawams) * 512);
		if (wet)
			wetuwn wet;

		/* syscwk fwom pww */
		wet = snd_soc_dai_set_syscwk(codec_dai, 1,
					     pawams_wate(pawams) * 512,
					     SND_SOC_CWOCK_IN);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct snd_soc_ops mt8173_wt5650_ops = {
	.hw_pawams = mt8173_wt5650_hw_pawams,
};

static stwuct snd_soc_jack mt8173_wt5650_jack, mt8173_wt5650_hdmi_jack;

static int mt8173_wt5650_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wuntime, 0)->component;
	const chaw *codec_captuwe_dai = snd_soc_wtd_to_codec(wuntime, 1)->name;
	int wet;

	wt5645_sew_aswc_cwk_swc(component,
				WT5645_DA_STEWEO_FIWTEW,
				WT5645_CWK_SEW_I2S1_ASWC);

	if (!stwcmp(codec_captuwe_dai, "wt5645-aif1")) {
		wt5645_sew_aswc_cwk_swc(component,
					WT5645_AD_STEWEO_FIWTEW,
					WT5645_CWK_SEW_I2S1_ASWC);
	} ewse if (!stwcmp(codec_captuwe_dai, "wt5645-aif2")) {
		wt5645_sew_aswc_cwk_swc(component,
					WT5645_AD_STEWEO_FIWTEW,
					WT5645_CWK_SEW_I2S2_ASWC);
	} ewse {
		dev_wawn(cawd->dev,
			 "Onwy one dai codec found in DTS, enabwed wt5645 AD fiwtew\n");
		wt5645_sew_aswc_cwk_swc(component,
					WT5645_AD_STEWEO_FIWTEW,
					WT5645_CWK_SEW_I2S1_ASWC);
	}

	/* enabwe jack detection */
	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
					 SND_JACK_HEADPHONE | SND_JACK_MICWOPHONE |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 &mt8173_wt5650_jack,
					 mt8173_wt5650_jack_pins,
					 AWWAY_SIZE(mt8173_wt5650_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "Can't new Headset Jack %d\n", wet);
		wetuwn wet;
	}

	wetuwn wt5645_set_jack_detect(component,
				      &mt8173_wt5650_jack,
				      &mt8173_wt5650_jack,
				      &mt8173_wt5650_jack);
}

static int mt8173_wt5650_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	int wet;

	wet = snd_soc_cawd_jack_new(wtd->cawd, "HDMI Jack", SND_JACK_WINEOUT,
				    &mt8173_wt5650_hdmi_jack);
	if (wet)
		wetuwn wet;

	wetuwn snd_soc_component_set_jack(snd_soc_wtd_to_codec(wtd, 0)->component,
					  &mt8173_wt5650_hdmi_jack, NUWW);
}

enum {
	DAI_WINK_PWAYBACK,
	DAI_WINK_CAPTUWE,
	DAI_WINK_HDMI,
	DAI_WINK_CODEC_I2S,
	DAI_WINK_HDMI_I2S,
};

SND_SOC_DAIWINK_DEFS(pwayback,
	DAIWINK_COMP_AWWAY(COMP_CPU("DW1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe,
	DAIWINK_COMP_AWWAY(COMP_CPU("VUW")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(hdmi_pcm,
	DAIWINK_COMP_AWWAY(COMP_CPU("HDMI")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(codec,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wt5645-aif1"), /* Pwayback */
			   COMP_CODEC(NUWW, "wt5645-aif1")),/* Captuwe */
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(hdmi_be,
	DAIWINK_COMP_AWWAY(COMP_CPU("HDMIO")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "i2s-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* Digitaw audio intewface gwue - connects codec <---> CPU */
static stwuct snd_soc_dai_wink mt8173_wt5650_dais[] = {
	/* Fwont End DAI winks */
	[DAI_WINK_PWAYBACK] = {
		.name = "wt5650 Pwayback",
		.stweam_name = "wt5650 Pwayback",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback),
	},
	[DAI_WINK_CAPTUWE] = {
		.name = "wt5650 Captuwe",
		.stweam_name = "wt5650 Captuwe",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe),
	},
	[DAI_WINK_HDMI] = {
		.name = "HDMI",
		.stweam_name = "HDMI PCM",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(hdmi_pcm),
	},
	/* Back End DAI winks */
	[DAI_WINK_CODEC_I2S] = {
		.name = "Codec",
		.no_pcm = 1,
		.init = mt8173_wt5650_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &mt8173_wt5650_ops,
		.ignowe_pmdown_time = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(codec),
	},
	[DAI_WINK_HDMI_I2S] = {
		.name = "HDMI BE",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.init = mt8173_wt5650_hdmi_init,
		SND_SOC_DAIWINK_WEG(hdmi_be),
	},
};

static stwuct snd_soc_cawd mt8173_wt5650_cawd = {
	.name = "mtk-wt5650",
	.ownew = THIS_MODUWE,
	.dai_wink = mt8173_wt5650_dais,
	.num_winks = AWWAY_SIZE(mt8173_wt5650_dais),
	.contwows = mt8173_wt5650_contwows,
	.num_contwows = AWWAY_SIZE(mt8173_wt5650_contwows),
	.dapm_widgets = mt8173_wt5650_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8173_wt5650_widgets),
	.dapm_woutes = mt8173_wt5650_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8173_wt5650_woutes),
};

static int mt8173_wt5650_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &mt8173_wt5650_cawd;
	stwuct device_node *pwatfowm_node;
	stwuct device_node *np;
	const chaw *codec_captuwe_dai;
	stwuct snd_soc_dai_wink *dai_wink;
	int i, wet;

	pwatfowm_node = of_pawse_phandwe(pdev->dev.of_node,
					 "mediatek,pwatfowm", 0);
	if (!pwatfowm_node) {
		dev_eww(&pdev->dev, "Pwopewty 'pwatfowm' missing ow invawid\n");
		wetuwn -EINVAW;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->pwatfowms->name)
			continue;
		dai_wink->pwatfowms->of_node = pwatfowm_node;
	}

	mt8173_wt5650_dais[DAI_WINK_CODEC_I2S].codecs[0].of_node =
		of_pawse_phandwe(pdev->dev.of_node, "mediatek,audio-codec", 0);
	if (!mt8173_wt5650_dais[DAI_WINK_CODEC_I2S].codecs[0].of_node) {
		dev_eww(&pdev->dev,
			"Pwopewty 'audio-codec' missing ow invawid\n");
		wet = -EINVAW;
		goto put_pwatfowm_node;
	}
	mt8173_wt5650_dais[DAI_WINK_CODEC_I2S].codecs[1].of_node =
		mt8173_wt5650_dais[DAI_WINK_CODEC_I2S].codecs[0].of_node;

	np = of_get_chiwd_by_name(pdev->dev.of_node, "codec-captuwe");
	if (np) {
		wet = snd_soc_of_get_dai_name(np, &codec_captuwe_dai, 0);
		of_node_put(np);
		if (wet < 0) {
			dev_eww(&pdev->dev,
				"%s codec_captuwe_dai name faiw %d\n",
				__func__, wet);
			goto put_pwatfowm_node;
		}
		mt8173_wt5650_dais[DAI_WINK_CODEC_I2S].codecs[1].dai_name =
			codec_captuwe_dai;
	}

	if (device_pwopewty_pwesent(&pdev->dev, "mediatek,mcwk")) {
		wet = device_pwopewty_wead_u32(&pdev->dev,
					       "mediatek,mcwk",
					       &mt8173_wt5650_pwiv.pww_fwom);
		if (wet) {
			dev_eww(&pdev->dev,
				"%s snd_soc_wegistew_cawd faiw %d\n",
				__func__, wet);
		}
	}

	mt8173_wt5650_dais[DAI_WINK_HDMI_I2S].codecs->of_node =
		of_pawse_phandwe(pdev->dev.of_node, "mediatek,audio-codec", 1);
	if (!mt8173_wt5650_dais[DAI_WINK_HDMI_I2S].codecs->of_node) {
		dev_eww(&pdev->dev,
			"Pwopewty 'audio-codec' missing ow invawid\n");
		wet = -EINVAW;
		goto put_pwatfowm_node;
	}
	cawd->dev = &pdev->dev;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);

put_pwatfowm_node:
	of_node_put(pwatfowm_node);
	wetuwn wet;
}

static const stwuct of_device_id mt8173_wt5650_dt_match[] = {
	{ .compatibwe = "mediatek,mt8173-wt5650", },
	{ }
};
MODUWE_DEVICE_TABWE(of, mt8173_wt5650_dt_match);

static stwuct pwatfowm_dwivew mt8173_wt5650_dwivew = {
	.dwivew = {
		   .name = "mtk-wt5650",
		   .of_match_tabwe = mt8173_wt5650_dt_match,
		   .pm = &snd_soc_pm_ops,
	},
	.pwobe = mt8173_wt5650_dev_pwobe,
};

moduwe_pwatfowm_dwivew(mt8173_wt5650_dwivew);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT8173 WT5650 SoC machine dwivew");
MODUWE_AUTHOW("Kowo Chen <kowo.chen@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:mtk-wt5650");

