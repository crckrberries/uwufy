// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt2701-cs42448.c  --  MT2701 CS42448 AWSA SoC machine dwivew
 *
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Iw Wian <iw.wian@mediatek.com>
 *	   Gawwic Tseng <gawwic.tseng@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>

#incwude "mt2701-afe-common.h"

stwuct mt2701_cs42448_pwivate {
	int i2s1_in_mux;
	stwuct gpio_desc *i2s1_in_mux_sew_1;
	stwuct gpio_desc *i2s1_in_mux_sew_2;
};

static const chaw * const i2sin_mux_switch_text[] = {
	"ADC_SDOUT2",
	"ADC_SDOUT3",
	"I2S_IN_1",
	"I2S_IN_2",
};

static const stwuct soc_enum i2sin_mux_enum =
	SOC_ENUM_SINGWE_EXT(4, i2sin_mux_switch_text);

static int mt2701_cs42448_i2sin1_mux_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);
	stwuct mt2701_cs42448_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	ucontwow->vawue.integew.vawue[0] = pwiv->i2s1_in_mux;
	wetuwn 0;
}

static int mt2701_cs42448_i2sin1_mux_set(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);
	stwuct mt2701_cs42448_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	if (ucontwow->vawue.integew.vawue[0] == pwiv->i2s1_in_mux)
		wetuwn 0;

	switch (ucontwow->vawue.integew.vawue[0]) {
	case 0:
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_1, 0);
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_2, 0);
		bweak;
	case 1:
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_1, 1);
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_2, 0);
		bweak;
	case 2:
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_1, 0);
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_2, 1);
		bweak;
	case 3:
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_1, 1);
		gpiod_set_vawue(pwiv->i2s1_in_mux_sew_2, 1);
		bweak;
	defauwt:
		dev_wawn(cawd->dev, "%s invawid setting\n", __func__);
	}

	pwiv->i2s1_in_mux = ucontwow->vawue.integew.vawue[0];
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget
			mt2701_cs42448_asoc_cawd_dapm_widgets[] = {
	SND_SOC_DAPM_WINE("Wine Out Jack", NUWW),
	SND_SOC_DAPM_MIC("AMIC", NUWW),
	SND_SOC_DAPM_WINE("Tunew In", NUWW),
	SND_SOC_DAPM_WINE("Satewwite Tunew In", NUWW),
	SND_SOC_DAPM_WINE("AUX In", NUWW),
};

static const stwuct snd_kcontwow_new mt2701_cs42448_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Wine Out Jack"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
	SOC_DAPM_PIN_SWITCH("Tunew In"),
	SOC_DAPM_PIN_SWITCH("Satewwite Tunew In"),
	SOC_DAPM_PIN_SWITCH("AUX In"),
	SOC_ENUM_EXT("I2SIN1_MUX_Switch", i2sin_mux_enum,
		     mt2701_cs42448_i2sin1_mux_get,
		     mt2701_cs42448_i2sin1_mux_set),
};

static const unsigned int mt2701_cs42448_sampwing_wates[] = {48000};

static const stwuct snd_pcm_hw_constwaint_wist mt2701_cs42448_constwaints_wates = {
		.count = AWWAY_SIZE(mt2701_cs42448_sampwing_wates),
		.wist = mt2701_cs42448_sampwing_wates,
		.mask = 0,
};

static int mt2701_cs42448_fe_ops_stawtup(stwuct snd_pcm_substweam *substweam)
{
	int eww;

	eww = snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_WATE,
					 &mt2701_cs42448_constwaints_wates);
	if (eww < 0) {
		dev_eww(substweam->pcm->cawd->dev,
			"%s snd_pcm_hw_constwaint_wist faiwed: 0x%x\n",
			__func__, eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static const stwuct snd_soc_ops mt2701_cs42448_48k_fe_ops = {
	.stawtup = mt2701_cs42448_fe_ops_stawtup,
};

static int mt2701_cs42448_be_ops_hw_pawams(stwuct snd_pcm_substweam *substweam,
					   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int mcwk_wate;
	unsigned int wate = pawams_wate(pawams);
	unsigned int div_mcwk_ovew_bck = wate > 192000 ? 2 : 4;
	unsigned int div_bck_ovew_wwck = 64;

	mcwk_wate = wate * div_bck_ovew_wwck * div_mcwk_ovew_bck;

	/* mt2701 mcwk */
	snd_soc_dai_set_syscwk(cpu_dai, 0, mcwk_wate, SND_SOC_CWOCK_OUT);

	/* codec mcwk */
	snd_soc_dai_set_syscwk(codec_dai, 0, mcwk_wate, SND_SOC_CWOCK_IN);

	wetuwn 0;
}

static const stwuct snd_soc_ops mt2701_cs42448_be_ops = {
	.hw_pawams = mt2701_cs42448_be_ops_hw_pawams
};

enum {
	DAI_WINK_FE_MUWTI_CH_OUT,
	DAI_WINK_FE_PCM0_IN,
	DAI_WINK_FE_PCM1_IN,
	DAI_WINK_FE_BT_OUT,
	DAI_WINK_FE_BT_IN,
	DAI_WINK_BE_I2S0,
	DAI_WINK_BE_I2S1,
	DAI_WINK_BE_I2S2,
	DAI_WINK_BE_I2S3,
	DAI_WINK_BE_MWG_BT,
};

SND_SOC_DAIWINK_DEFS(fe_muwti_ch_out,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM_muwti")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(fe_pcm0_in,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM0")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(fe_pcm1_in,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(fe_bt_out,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM_BT_DW")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(fe_bt_in,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM_BT_UW")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(be_i2s0,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "cs42448")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(be_i2s1,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S1")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "cs42448")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(be_i2s2,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S2")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "cs42448")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(be_i2s3,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S3")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "cs42448")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(be_mwg_bt,
	DAIWINK_COMP_AWWAY(COMP_CPU("MWG BT")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "bt-sco-pcm-wb")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink mt2701_cs42448_dai_winks[] = {
	/* FE */
	[DAI_WINK_FE_MUWTI_CH_OUT] = {
		.name = "mt2701-cs42448-muwti-ch-out",
		.stweam_name = "mt2701-cs42448-muwti-ch-out",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST,
			    SND_SOC_DPCM_TWIGGEW_POST},
		.ops = &mt2701_cs42448_48k_fe_ops,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(fe_muwti_ch_out),
	},
	[DAI_WINK_FE_PCM0_IN] = {
		.name = "mt2701-cs42448-pcm0",
		.stweam_name = "mt2701-cs42448-pcm0-data-UW",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST,
			    SND_SOC_DPCM_TWIGGEW_POST},
		.ops = &mt2701_cs42448_48k_fe_ops,
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(fe_pcm0_in),
	},
	[DAI_WINK_FE_PCM1_IN] = {
		.name = "mt2701-cs42448-pcm1-data-UW",
		.stweam_name = "mt2701-cs42448-pcm1-data-UW",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST,
			    SND_SOC_DPCM_TWIGGEW_POST},
		.ops = &mt2701_cs42448_48k_fe_ops,
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(fe_pcm1_in),
	},
	[DAI_WINK_FE_BT_OUT] = {
		.name = "mt2701-cs42448-pcm-BT-out",
		.stweam_name = "mt2701-cs42448-pcm-BT",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST,
			    SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(fe_bt_out),
	},
	[DAI_WINK_FE_BT_IN] = {
		.name = "mt2701-cs42448-pcm-BT-in",
		.stweam_name = "mt2701-cs42448-pcm-BT",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_POST,
			    SND_SOC_DPCM_TWIGGEW_POST},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(fe_bt_in),
	},
	/* BE */
	[DAI_WINK_BE_I2S0] = {
		.name = "mt2701-cs42448-I2S0",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(be_i2s0),
	},
	[DAI_WINK_BE_I2S1] = {
		.name = "mt2701-cs42448-I2S1",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(be_i2s1),
	},
	[DAI_WINK_BE_I2S2] = {
		.name = "mt2701-cs42448-I2S2",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(be_i2s2),
	},
	[DAI_WINK_BE_I2S3] = {
		.name = "mt2701-cs42448-I2S3",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS
			 | SND_SOC_DAIFMT_GATED,
		.ops = &mt2701_cs42448_be_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(be_i2s3),
	},
	[DAI_WINK_BE_MWG_BT] = {
		.name = "mt2701-cs42448-MWG-BT",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(be_mwg_bt),
	},
};

static stwuct snd_soc_cawd mt2701_cs42448_soc_cawd = {
	.name = "mt2701-cs42448",
	.ownew = THIS_MODUWE,
	.dai_wink = mt2701_cs42448_dai_winks,
	.num_winks = AWWAY_SIZE(mt2701_cs42448_dai_winks),
	.contwows = mt2701_cs42448_contwows,
	.num_contwows = AWWAY_SIZE(mt2701_cs42448_contwows),
	.dapm_widgets = mt2701_cs42448_asoc_cawd_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt2701_cs42448_asoc_cawd_dapm_widgets),
};

static int mt2701_cs42448_machine_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &mt2701_cs42448_soc_cawd;
	int wet;
	int i;
	stwuct device_node *pwatfowm_node, *codec_node, *codec_node_bt_mwg;
	stwuct mt2701_cs42448_pwivate *pwiv =
		devm_kzawwoc(&pdev->dev, sizeof(stwuct mt2701_cs42448_pwivate),
			     GFP_KEWNEW);
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_dai_wink *dai_wink;

	if (!pwiv)
		wetuwn -ENOMEM;

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

	cawd->dev = dev;

	codec_node = of_pawse_phandwe(pdev->dev.of_node,
				      "mediatek,audio-codec", 0);
	if (!codec_node) {
		dev_eww(&pdev->dev,
			"Pwopewty 'audio-codec' missing ow invawid\n");
		wetuwn -EINVAW;
	}
	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->codecs->name)
			continue;
		dai_wink->codecs->of_node = codec_node;
	}

	codec_node_bt_mwg = of_pawse_phandwe(pdev->dev.of_node,
					     "mediatek,audio-codec-bt-mwg", 0);
	if (!codec_node_bt_mwg) {
		dev_eww(&pdev->dev,
			"Pwopewty 'audio-codec-bt-mwg' missing ow invawid\n");
		wetuwn -EINVAW;
	}
	mt2701_cs42448_dai_winks[DAI_WINK_BE_MWG_BT].codecs->of_node
							= codec_node_bt_mwg;

	wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pawse audio-wouting: %d\n", wet);
		wetuwn wet;
	}

	pwiv->i2s1_in_mux_sew_1 = devm_gpiod_get_optionaw(dev, "i2s1-in-sew-gpio1",
							  GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->i2s1_in_mux_sew_1))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->i2s1_in_mux_sew_1),
				     "ewwow getting mux 1 sewectow\n");

	pwiv->i2s1_in_mux_sew_2 = devm_gpiod_get_optionaw(dev, "i2s1-in-sew-gpio2",
							  GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->i2s1_in_mux_sew_2))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->i2s1_in_mux_sew_2),
				     "ewwow getting mux 2 sewectow\n");

	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);

	if (wet)
		dev_eww(&pdev->dev, "%s snd_soc_wegistew_cawd faiw %d\n",
			__func__, wet);
	wetuwn wet;
}

#ifdef CONFIG_OF
static const stwuct of_device_id mt2701_cs42448_machine_dt_match[] = {
	{.compatibwe = "mediatek,mt2701-cs42448-machine",},
	{}
};
MODUWE_DEVICE_TABWE(of, mt2701_cs42448_machine_dt_match);
#endif

static stwuct pwatfowm_dwivew mt2701_cs42448_machine = {
	.dwivew = {
		.name = "mt2701-cs42448",
		   #ifdef CONFIG_OF
		   .of_match_tabwe = mt2701_cs42448_machine_dt_match,
		   #endif
	},
	.pwobe = mt2701_cs42448_machine_pwobe,
};

moduwe_pwatfowm_dwivew(mt2701_cs42448_machine);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT2701 CS42448 AWSA SoC machine dwivew");
MODUWE_AUTHOW("Iw Wian <iw.wian@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("mt2701 cs42448 soc cawd");
