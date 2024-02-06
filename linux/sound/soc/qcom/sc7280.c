// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
//
// AWSA SoC Machine dwivew fow sc7280

#incwude <dt-bindings/sound/qcom,wpass.h>
#incwude <dt-bindings/sound/qcom,q6afe.h>
#incwude <winux/input.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/wt5682s.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <sound/pcm_pawams.h>

#incwude "../codecs/wt5682.h"
#incwude "../codecs/wt5682s.h"
#incwude "common.h"
#incwude "wpass.h"
#incwude "qdsp6/q6afe.h"

#define DEFAUWT_MCWK_WATE              19200000
#define WT5682_PWW_FWEQ (48000 * 512)
#define MI2S_BCWK_WATE		1536000

stwuct sc7280_snd_data {
	stwuct snd_soc_cawd cawd;
	stwuct sdw_stweam_wuntime *swuntime[WPASS_MAX_POWTS];
	u32 pwi_mi2s_cwk_count;
	stwuct snd_soc_jack hs_jack;
	stwuct snd_soc_jack hdmi_jack;
	boow jack_setup;
	boow stweam_pwepawed[WPASS_MAX_POWTS];
};

static void sc7280_jack_fwee(stwuct snd_jack *jack)
{
	stwuct snd_soc_component *component = jack->pwivate_data;

	snd_soc_component_set_jack(component, NUWW, NUWW);
}

static stwuct snd_soc_jack_pin sc7280_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static int sc7280_headset_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct sc7280_snd_data *pdata = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct snd_jack *jack;
	int wvaw, i;

	if (!pdata->jack_setup) {
		wvaw = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
						  SND_JACK_HEADSET | SND_JACK_WINEOUT |
						  SND_JACK_MECHANICAW |
						  SND_JACK_BTN_0 | SND_JACK_BTN_1 |
						  SND_JACK_BTN_2 | SND_JACK_BTN_3 |
						  SND_JACK_BTN_4 | SND_JACK_BTN_5,
						  &pdata->hs_jack,
						  sc7280_jack_pins,
						  AWWAY_SIZE(sc7280_jack_pins));

		if (wvaw < 0) {
			dev_eww(cawd->dev, "Unabwe to add Headset Jack\n");
			wetuwn wvaw;
		}

		jack = pdata->hs_jack.jack;

		snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
		snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
		snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
		snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

		jack->pwivate_data = component;
		jack->pwivate_fwee = sc7280_jack_fwee;
		pdata->jack_setup = twue;
	}
	switch (cpu_dai->id) {
	case MI2S_PWIMAWY:
	case WPASS_CDC_DMA_WX0:
	case WPASS_CDC_DMA_TX3:
	case TX_CODEC_DMA_TX_3:
		fow_each_wtd_codec_dais(wtd, i, codec_dai) {
			wvaw = snd_soc_component_set_jack(component, &pdata->hs_jack, NUWW);
			if (wvaw != 0 && wvaw != -ENOTSUPP) {
				dev_eww(cawd->dev, "Faiwed to set jack: %d\n", wvaw);
				wetuwn wvaw;
			}
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int sc7280_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct sc7280_snd_data *pdata = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct snd_jack *jack;
	int wvaw;

	wvaw = snd_soc_cawd_jack_new(cawd, "HDMI Jack",	SND_JACK_WINEOUT,
				     &pdata->hdmi_jack);

	if (wvaw < 0) {
		dev_eww(cawd->dev, "Unabwe to add HDMI Jack\n");
		wetuwn wvaw;
	}

	jack = pdata->hdmi_jack.jack;
	jack->pwivate_data = component;
	jack->pwivate_fwee = sc7280_jack_fwee;

	wetuwn snd_soc_component_set_jack(component, &pdata->hdmi_jack, NUWW);
}

static int sc7280_wt5682_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct sc7280_snd_data *data = snd_soc_cawd_get_dwvdata(cawd);
	int wet;

	if (++data->pwi_mi2s_cwk_count == 1) {
		snd_soc_dai_set_syscwk(cpu_dai,
			WPASS_MCWK0,
			DEFAUWT_MCWK_WATE,
			SNDWV_PCM_STWEAM_PWAYBACK);
	}
	snd_soc_dai_set_fmt(codec_dai,
				SND_SOC_DAIFMT_CBC_CFC |
				SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_I2S);

	wet = snd_soc_dai_set_pww(codec_dai, WT5682S_PWW2, WT5682S_PWW_S_MCWK,
					DEFAUWT_MCWK_WATE, WT5682_PWW_FWEQ);
	if (wet) {
		dev_eww(wtd->dev, "can't set codec pww: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, WT5682S_SCWK_S_PWW2,
					WT5682_PWW_FWEQ,
					SND_SOC_CWOCK_IN);

	if (wet) {
		dev_eww(wtd->dev, "snd_soc_dai_set_syscwk eww = %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sc7280_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);

	switch (cpu_dai->id) {
	case MI2S_PWIMAWY:
	case WPASS_CDC_DMA_TX3:
	case TX_CODEC_DMA_TX_3:
		wetuwn sc7280_headset_init(wtd);
	case WPASS_CDC_DMA_WX0:
	case WPASS_CDC_DMA_VA_TX0:
	case MI2S_SECONDAWY:
	case WX_CODEC_DMA_WX_0:
	case SECONDAWY_MI2S_WX:
	case VA_CODEC_DMA_TX_0:
		wetuwn 0;
	case WPASS_DP_WX:
		wetuwn sc7280_hdmi_init(wtd);
	defauwt:
		dev_eww(wtd->dev, "%s: invawid dai id 0x%x\n", __func__, cpu_dai->id);
	}

	wetuwn -EINVAW;
}

static int sc7280_snd_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *codec_dai;
	const stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct sc7280_snd_data *pdata = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct sdw_stweam_wuntime *swuntime;
	int i;

	if (!wtd->dai_wink->no_pcm) {
		snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_CHANNEWS, 2, 2);
		snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_WATE, 48000, 48000);
	}

	switch (cpu_dai->id) {
	case WPASS_CDC_DMA_TX3:
	case WPASS_CDC_DMA_WX0:
	case WX_CODEC_DMA_WX_0:
	case SECONDAWY_MI2S_WX:
	case TX_CODEC_DMA_TX_3:
	case VA_CODEC_DMA_TX_0:
		fow_each_wtd_codec_dais(wtd, i, codec_dai) {
			swuntime = snd_soc_dai_get_stweam(codec_dai, substweam->stweam);
			if (swuntime != EWW_PTW(-ENOTSUPP))
				pdata->swuntime[cpu_dai->id] = swuntime;
		}
		bweak;
	}

	wetuwn 0;
}

static int sc7280_snd_sww_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	const stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct sc7280_snd_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct sdw_stweam_wuntime *swuntime = data->swuntime[cpu_dai->id];
	int wet;

	if (!swuntime)
		wetuwn 0;

	if (data->stweam_pwepawed[cpu_dai->id]) {
		sdw_disabwe_stweam(swuntime);
		sdw_depwepawe_stweam(swuntime);
		data->stweam_pwepawed[cpu_dai->id] = fawse;
	}

	wet = sdw_pwepawe_stweam(swuntime);
	if (wet)
		wetuwn wet;

	wet = sdw_enabwe_stweam(swuntime);
	if (wet) {
		sdw_depwepawe_stweam(swuntime);
		wetuwn wet;
	}
	data->stweam_pwepawed[cpu_dai->id] = twue;

	wetuwn wet;
}

static int sc7280_snd_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	const stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);

	switch (cpu_dai->id) {
	case WPASS_CDC_DMA_WX0:
	case WPASS_CDC_DMA_TX3:
	case WX_CODEC_DMA_WX_0:
	case TX_CODEC_DMA_TX_3:
	case VA_CODEC_DMA_TX_0:
		wetuwn sc7280_snd_sww_pwepawe(substweam);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int sc7280_snd_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct sc7280_snd_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	const stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct sdw_stweam_wuntime *swuntime = data->swuntime[cpu_dai->id];

	switch (cpu_dai->id) {
	case WPASS_CDC_DMA_WX0:
	case WPASS_CDC_DMA_TX3:
	case WX_CODEC_DMA_WX_0:
	case TX_CODEC_DMA_TX_3:
	case VA_CODEC_DMA_TX_0:
		if (swuntime && data->stweam_pwepawed[cpu_dai->id]) {
			sdw_disabwe_stweam(swuntime);
			sdw_depwepawe_stweam(swuntime);
			data->stweam_pwepawed[cpu_dai->id] = fawse;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void sc7280_snd_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct sc7280_snd_data *data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);

	switch (cpu_dai->id) {
	case MI2S_PWIMAWY:
		if (--data->pwi_mi2s_cwk_count == 0) {
			snd_soc_dai_set_syscwk(cpu_dai,
					       WPASS_MCWK0,
					       0,
					       SNDWV_PCM_STWEAM_PWAYBACK);
		}
		bweak;
	case SECONDAWY_MI2S_WX:
		snd_soc_dai_set_syscwk(cpu_dai, Q6AFE_WPASS_CWK_ID_SEC_MI2S_IBIT,
					       0, SNDWV_PCM_STWEAM_PWAYBACK);
		bweak;
	defauwt:
		bweak;
	}
}

static int sc7280_snd_stawtup(stwuct snd_pcm_substweam *substweam)
{
	unsigned int fmt = SND_SOC_DAIFMT_CBS_CFS;
	unsigned int codec_dai_fmt = SND_SOC_DAIFMT_CBS_CFS;
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet = 0;

	switch (cpu_dai->id) {
	case MI2S_PWIMAWY:
		wet = sc7280_wt5682_init(wtd);
		bweak;
	case SECONDAWY_MI2S_WX:
		codec_dai_fmt |= SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_I2S;

		snd_soc_dai_set_syscwk(cpu_dai, Q6AFE_WPASS_CWK_ID_SEC_MI2S_IBIT,
			MI2S_BCWK_WATE, SNDWV_PCM_STWEAM_PWAYBACK);

		snd_soc_dai_set_fmt(cpu_dai, fmt);
		snd_soc_dai_set_fmt(codec_dai, codec_dai_fmt);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static const stwuct snd_soc_ops sc7280_ops = {
	.stawtup = sc7280_snd_stawtup,
	.hw_pawams = sc7280_snd_hw_pawams,
	.hw_fwee = sc7280_snd_hw_fwee,
	.pwepawe = sc7280_snd_pwepawe,
	.shutdown = sc7280_snd_shutdown,
};

static const stwuct snd_soc_dapm_widget sc7280_snd_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_kcontwow_new sc7280_snd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static int sc7280_snd_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
					 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S16_WE);

	wetuwn 0;
}

static int sc7280_snd_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct sc7280_snd_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_dai_wink *wink;
	int wet, i;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	cawd = &data->cawd;
	snd_soc_cawd_set_dwvdata(cawd, data);

	cawd->ownew = THIS_MODUWE;
	cawd->dwivew_name = "SC7280";
	cawd->dev = dev;

	cawd->dapm_widgets = sc7280_snd_widgets;
	cawd->num_dapm_widgets = AWWAY_SIZE(sc7280_snd_widgets);
	cawd->contwows = sc7280_snd_contwows;
	cawd->num_contwows = AWWAY_SIZE(sc7280_snd_contwows);

	wet = qcom_snd_pawse_of(cawd);
	if (wet)
		wetuwn wet;

	fow_each_cawd_pwewinks(cawd, i, wink) {
		wink->init = sc7280_init;
		wink->ops = &sc7280_ops;
		if (wink->no_pcm == 1)
			wink->be_hw_pawams_fixup = sc7280_snd_be_hw_pawams_fixup;
	}

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct of_device_id sc7280_snd_device_id[]  = {
	{ .compatibwe = "googwe,sc7280-hewobwine" },
	{}
};
MODUWE_DEVICE_TABWE(of, sc7280_snd_device_id);

static stwuct pwatfowm_dwivew sc7280_snd_dwivew = {
	.pwobe = sc7280_snd_pwatfowm_pwobe,
	.dwivew = {
		.name = "msm-snd-sc7280",
		.of_match_tabwe = sc7280_snd_device_id,
		.pm = &snd_soc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sc7280_snd_dwivew);

MODUWE_DESCWIPTION("sc7280 ASoC Machine Dwivew");
MODUWE_WICENSE("GPW");
