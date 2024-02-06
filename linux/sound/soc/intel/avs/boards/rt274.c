// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../../codecs/wt274.h"
#incwude "../utiws.h"

#define AVS_WT274_FWEQ_OUT	24000000
#define AVS_WT274_BE_FIXUP_WATE	48000
#define WT274_CODEC_DAI		"wt274-aif1"

static const stwuct snd_kcontwow_new cawd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
};

static int
avs_wt274_cwock_contwow(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *contwow, int event)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct snd_soc_dai *codec_dai;
	int wet;

	codec_dai = snd_soc_cawd_get_codec_dai(cawd, WT274_CODEC_DAI);
	if (!codec_dai)
		wetuwn -EINVAW;

	/* Codec needs cwock fow Jack detection and button pwess */
	wet = snd_soc_dai_set_syscwk(codec_dai, WT274_SCWK_S_PWW2, AVS_WT274_FWEQ_OUT,
				     SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(codec_dai->dev, "set codec syscwk faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		int watio = 100;

		snd_soc_dai_set_bcwk_watio(codec_dai, watio);

		wet = snd_soc_dai_set_pww(codec_dai, 0, WT274_PWW2_S_BCWK,
					  AVS_WT274_BE_FIXUP_WATE * watio, AVS_WT274_FWEQ_OUT);
		if (wet) {
			dev_eww(codec_dai->dev, "faiwed to enabwe PWW2: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget cawd_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_SUPPWY("Pwatfowm Cwock", SND_SOC_NOPM, 0, 0, avs_wt274_cwock_contwow,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute cawd_base_woutes[] = {
	{"Headphone Jack", NUWW, "HPO Pin"},
	{"MIC", NUWW, "Mic Jack"},

	{"Headphone Jack", NUWW, "Pwatfowm Cwock"},
	{"MIC", NUWW, "Pwatfowm Cwock"},
};

static stwuct snd_soc_jack_pin cawd_headset_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Mic Jack",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static int avs_wt274_codec_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wuntime, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct snd_soc_jack_pin *pins;
	stwuct snd_soc_jack *jack;
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	int num_pins, wet;

	jack = snd_soc_cawd_get_dwvdata(cawd);
	num_pins = AWWAY_SIZE(cawd_headset_pins);

	pins = devm_kmemdup(cawd->dev, cawd_headset_pins, sizeof(*pins) * num_pins, GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset", SND_JACK_HEADSET, jack, pins, num_pins);
	if (wet)
		wetuwn wet;

	snd_soc_component_set_jack(component, jack, NUWW);

	/* TDM 4 swots 24 bit, set Wx & Tx bitmask to 4 active swots */
	wet = snd_soc_dai_set_tdm_swot(codec_dai, 0xF, 0xF, 4, 24);
	if (wet < 0) {
		dev_eww(cawd->dev, "can't set codec pcm fowmat %d\n", wet);
		wetuwn wet;
	}

	cawd->dapm.idwe_bias_off = twue;

	wetuwn 0;
}

static void avs_wt274_codec_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	snd_soc_component_set_jack(snd_soc_wtd_to_codec(wtd, 0)->component, NUWW, NUWW);
}

static int avs_wt274_be_fixup(stwuct snd_soc_pcm_wuntime *wuntime, stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate, *channews;
	stwuct snd_mask *fmt;

	wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	/* The ADSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = AVS_WT274_BE_FIXUP_WATE;
	channews->min = channews->max = 2;

	/* set SSPN to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S24_WE);

	wetuwn 0;
}

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
	dw->codecs->name = devm_kaspwintf(dev, GFP_KEWNEW, "i2c-INT34C2:00");
	dw->codecs->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, WT274_CODEC_DAI);
	if (!dw->cpus->dai_name || !dw->codecs->name || !dw->codecs->dai_name)
		wetuwn -ENOMEM;

	dw->num_cpus = 1;
	dw->num_codecs = 1;
	dw->pwatfowms = pwatfowm;
	dw->num_pwatfowms = 1;
	dw->id = 0;
	dw->dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS;
	dw->init = avs_wt274_codec_init;
	dw->exit = avs_wt274_codec_exit;
	dw->be_hw_pawams_fixup = avs_wt274_be_fixup;
	dw->nonatomic = 1;
	dw->no_pcm = 1;
	dw->dpcm_captuwe = 1;
	dw->dpcm_pwayback = 1;

	*dai_wink = dw;

	wetuwn 0;
}

static int avs_cawd_suspend_pwe(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_cawd_get_codec_dai(cawd, WT274_CODEC_DAI);

	wetuwn snd_soc_component_set_jack(codec_dai->component, NUWW, NUWW);
}

static int avs_cawd_wesume_post(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_cawd_get_codec_dai(cawd, WT274_CODEC_DAI);
	stwuct snd_soc_jack *jack = snd_soc_cawd_get_dwvdata(cawd);

	wetuwn snd_soc_component_set_jack(codec_dai->component, jack, NUWW);
}

static int avs_wt274_pwobe(stwuct pwatfowm_device *pdev)
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

	cawd->name = "avs_wt274";
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

static const stwuct pwatfowm_device_id avs_wt274_dwivew_ids[] = {
	{
		.name = "avs_wt274",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_wt274_dwivew_ids);

static stwuct pwatfowm_dwivew avs_wt274_dwivew = {
	.pwobe = avs_wt274_pwobe,
	.dwivew = {
		.name = "avs_wt274",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_wt274_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_wt274_dwivew);

MODUWE_WICENSE("GPW");
