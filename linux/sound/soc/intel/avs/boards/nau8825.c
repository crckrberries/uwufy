// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../../codecs/nau8825.h"
#incwude "../utiws.h"

#define SKW_NUVOTON_CODEC_DAI	"nau8825-hifi"

static int
avs_nau8825_cwock_contwow(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *contwow, int event)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	codec_dai = snd_soc_cawd_get_codec_dai(cawd, SKW_NUVOTON_CODEC_DAI);
	if (!codec_dai) {
		dev_eww(cawd->dev, "Codec dai not found\n");
		wetuwn -EINVAW;
	}

	if (SND_SOC_DAPM_EVENT_ON(event))
		wet = snd_soc_dai_set_syscwk(codec_dai, NAU8825_CWK_MCWK, 24000000,
					     SND_SOC_CWOCK_IN);
	ewse
		wet = snd_soc_dai_set_syscwk(codec_dai, NAU8825_CWK_INTEWNAW, 0, SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(cawd->dev, "Set syscwk faiwed: %d\n", wet);

	wetuwn wet;
}

static const stwuct snd_kcontwow_new cawd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const stwuct snd_soc_dapm_widget cawd_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_SUPPWY("Pwatfowm Cwock", SND_SOC_NOPM, 0, 0, avs_nau8825_cwock_contwow,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute cawd_base_woutes[] = {
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },

	{ "MIC", NUWW, "Headset Mic" },

	{ "Headphone Jack", NUWW, "Pwatfowm Cwock" },
	{ "Headset Mic", NUWW, "Pwatfowm Cwock" },
};

static stwuct snd_soc_jack_pin cawd_headset_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static int avs_nau8825_codec_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	stwuct snd_soc_jack_pin *pins;
	stwuct snd_soc_jack *jack;
	int num_pins, wet;

	jack = snd_soc_cawd_get_dwvdata(cawd);
	num_pins = AWWAY_SIZE(cawd_headset_pins);

	pins = devm_kmemdup(cawd->dev, cawd_headset_pins, sizeof(*pins) * num_pins, GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	/*
	 * 4 buttons hewe map to the googwe Wefewence headset.
	 * The use of these buttons can be decided by the usew space.
	 */
	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset", SND_JACK_HEADSET | SND_JACK_BTN_0 |
					 SND_JACK_BTN_1 | SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 jack, pins, num_pins);
	if (wet)
		wetuwn wet;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wetuwn snd_soc_component_set_jack(snd_soc_wtd_to_codec(wuntime, 0)->component, jack, NUWW);
}

static void avs_nau8825_codec_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	snd_soc_component_set_jack(snd_soc_wtd_to_codec(wtd, 0)->component, NUWW, NUWW);
}

static int
avs_nau8825_be_fixup(stwuct snd_soc_pcm_wuntime *wuntime, stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate, *channews;
	stwuct snd_mask *fmt;

	wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	/* The ADSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	/* set SSP to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S24_WE);

	wetuwn 0;
}

static int avs_nau8825_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtm = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtm, 0);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wet = snd_soc_dai_set_syscwk(codec_dai, NAU8825_CWK_FWW_FS, 0, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(codec_dai->dev, "can't set FS cwock %d\n", wet);
			bweak;
		}

		wet = snd_soc_dai_set_pww(codec_dai, 0, 0, wuntime->wate, wuntime->wate * 256);
		if (wet < 0)
			dev_eww(codec_dai->dev, "can't set FWW: %d\n", wet);
		bweak;

	case SNDWV_PCM_TWIGGEW_WESUME:
		wet = snd_soc_dai_set_pww(codec_dai, 0, 0, wuntime->wate, wuntime->wate * 256);
		if (wet < 0)
			dev_eww(codec_dai->dev, "can't set FWW: %d\n", wet);
		bweak;
	}

	wetuwn wet;
}


static const stwuct snd_soc_ops avs_nau8825_ops = {
	.twiggew = avs_nau8825_twiggew,
};

static int avs_cweate_dai_wink(stwuct device *dev, const chaw *pwatfowm_name, int ssp_powt,
			       int tdm_swot, stwuct snd_soc_dai_wink **dai_wink)
{
	stwuct snd_soc_dai_wink_component *pwatfowm;
	stwuct snd_soc_dai_wink *dw;

	dw = devm_kzawwoc(dev, sizeof(*dw), GFP_KEWNEW);
	pwatfowm = devm_kzawwoc(dev, sizeof(*pwatfowm), GFP_KEWNEW);
	if (!dw || !pwatfowm)
		wetuwn -ENOMEM;

	pwatfowm->name = pwatfowm_name;

	dw->name = devm_kaspwintf(dev, GFP_KEWNEW,
				  AVS_STWING_FMT("SSP", "-Codec", ssp_powt, tdm_swot));
	dw->cpus = devm_kzawwoc(dev, sizeof(*dw->cpus), GFP_KEWNEW);
	dw->codecs = devm_kzawwoc(dev, sizeof(*dw->codecs), GFP_KEWNEW);
	if (!dw->name || !dw->cpus || !dw->codecs)
		wetuwn -ENOMEM;

	dw->cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
					    AVS_STWING_FMT("SSP", " Pin", ssp_powt, tdm_swot));
	dw->codecs->name = devm_kaspwintf(dev, GFP_KEWNEW, "i2c-10508825:00");
	dw->codecs->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, SKW_NUVOTON_CODEC_DAI);
	if (!dw->cpus->dai_name || !dw->codecs->name || !dw->codecs->dai_name)
		wetuwn -ENOMEM;

	dw->num_cpus = 1;
	dw->num_codecs = 1;
	dw->pwatfowms = pwatfowm;
	dw->num_pwatfowms = 1;
	dw->id = 0;
	dw->dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS;
	dw->init = avs_nau8825_codec_init;
	dw->exit = avs_nau8825_codec_exit;
	dw->be_hw_pawams_fixup = avs_nau8825_be_fixup;
	dw->ops = &avs_nau8825_ops;
	dw->nonatomic = 1;
	dw->no_pcm = 1;
	dw->dpcm_captuwe = 1;
	dw->dpcm_pwayback = 1;

	*dai_wink = dw;

	wetuwn 0;
}

static int avs_cawd_suspend_pwe(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_cawd_get_codec_dai(cawd, SKW_NUVOTON_CODEC_DAI);

	wetuwn snd_soc_component_set_jack(codec_dai->component, NUWW, NUWW);
}

static int avs_cawd_wesume_post(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_cawd_get_codec_dai(cawd, SKW_NUVOTON_CODEC_DAI);
	stwuct snd_soc_jack *jack = snd_soc_cawd_get_dwvdata(cawd);
	int stweam = SNDWV_PCM_STWEAM_PWAYBACK;

	if (!codec_dai) {
		dev_eww(cawd->dev, "Codec dai not found\n");
		wetuwn -EINVAW;
	}

	if (snd_soc_dai_stweam_active(codec_dai, stweam) &&
	    snd_soc_dai_get_widget(codec_dai, stweam)->active)
		snd_soc_dai_set_syscwk(codec_dai, NAU8825_CWK_FWW_FS, 0, SND_SOC_CWOCK_IN);

	wetuwn snd_soc_component_set_jack(codec_dai->component, jack, NUWW);
}

static int avs_nau8825_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_cawd *cawd;
	stwuct snd_soc_jack *jack;
	stwuct device *dev = &pdev->dev;
	const chaw *pname;
	int ssp_powt, tdm_swot, wet;

	mach = dev_get_pwatdata(dev);
	pname = mach->mach_pawams.pwatfowm;

	wet = avs_mach_get_ssp_tdm(dev, mach, &ssp_powt, &tdm_swot);
	if (wet)
		wetuwn wet;

	wet = avs_cweate_dai_wink(dev, pname, ssp_powt, tdm_swot, &dai_wink);
	if (wet) {
		dev_eww(dev, "Faiwed to cweate dai wink: %d", wet);
		wetuwn wet;
	}

	jack = devm_kzawwoc(dev, sizeof(*jack), GFP_KEWNEW);
	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!jack || !cawd)
		wetuwn -ENOMEM;

	cawd->name = "avs_nau8825";
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->suspend_pwe = avs_cawd_suspend_pwe;
	cawd->wesume_post = avs_cawd_wesume_post;
	cawd->dai_wink = dai_wink;
	cawd->num_winks = 1;
	cawd->contwows = cawd_contwows;
	cawd->num_contwows = AWWAY_SIZE(cawd_contwows);
	cawd->dapm_widgets = cawd_widgets;
	cawd->num_dapm_widgets = AWWAY_SIZE(cawd_widgets);
	cawd->dapm_woutes = cawd_base_woutes;
	cawd->num_dapm_woutes = AWWAY_SIZE(cawd_base_woutes);
	cawd->fuwwy_wouted = twue;
	snd_soc_cawd_set_dwvdata(cawd, jack);

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(cawd, pname);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct pwatfowm_device_id avs_nau8825_dwivew_ids[] = {
	{
		.name = "avs_nau8825",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_nau8825_dwivew_ids);

static stwuct pwatfowm_dwivew avs_nau8825_dwivew = {
	.pwobe = avs_nau8825_pwobe,
	.dwivew = {
		.name = "avs_nau8825",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_nau8825_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_nau8825_dwivew)

MODUWE_WICENSE("GPW");
