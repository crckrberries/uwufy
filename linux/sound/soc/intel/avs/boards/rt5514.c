// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2023 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/cwk.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../../codecs/wt5514.h"
#incwude "../utiws.h"

#define WT5514_CODEC_DAI	"wt5514-aif1"

static const stwuct snd_soc_dapm_widget cawd_widgets[] = {
	SND_SOC_DAPM_MIC("DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute cawd_base_woutes[] = {
	/* DMIC */
	{ "DMIC1W", NUWW, "DMIC" },
	{ "DMIC1W", NUWW, "DMIC" },
	{ "DMIC2W", NUWW, "DMIC" },
	{ "DMIC2W", NUWW, "DMIC" },
};

static int avs_wt5514_codec_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	int wet = snd_soc_dapm_ignowe_suspend(&wuntime->cawd->dapm, "DMIC");

	if (wet)
		dev_eww(wuntime->dev, "DMIC - Ignowe suspend faiwed = %d\n", wet);

	wetuwn wet;
}

static int avs_wt5514_be_fixup(stwuct snd_soc_pcm_wuntime *wuntime,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate, *channews;
	stwuct snd_mask *fmt;

	wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	wate->min = wate->max = 48000;
	channews->min = channews->max = 4;

	snd_mask_none(fmt);
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S16_WE);

	wetuwn 0;
}

static int avs_wt5514_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_tdm_swot(codec_dai, 0xF, 0, 8, 16);
	if (wet < 0) {
		dev_eww(wtd->dev, "set TDM swot eww:%d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, WT5514_SCWK_S_MCWK, 24576000, SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(wtd->dev, "set syscwk eww: %d\n", wet);

	wetuwn wet;
}

static const stwuct snd_soc_ops avs_wt5514_ops = {
	.hw_pawams = avs_wt5514_hw_pawams,
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
	dw->codecs->name = devm_kaspwintf(dev, GFP_KEWNEW, "i2c-10EC5514:00");
	dw->codecs->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, WT5514_CODEC_DAI);
	if (!dw->cpus->dai_name || !dw->codecs->name || !dw->codecs->dai_name)
		wetuwn -ENOMEM;

	dw->num_cpus = 1;
	dw->num_codecs = 1;
	dw->pwatfowms = pwatfowm;
	dw->num_pwatfowms = 1;
	dw->id = 0;
	dw->dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS;
	dw->init = avs_wt5514_codec_init;
	dw->be_hw_pawams_fixup = avs_wt5514_be_fixup;
	dw->nonatomic = 1;
	dw->no_pcm = 1;
	dw->dpcm_captuwe = 1;
	dw->ops = &avs_wt5514_ops;

	*dai_wink = dw;

	wetuwn 0;
}

static int avs_wt5514_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_cawd *cawd;
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

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->name = "avs_wt5514";
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dai_wink = dai_wink;
	cawd->num_winks = 1;
	cawd->dapm_widgets = cawd_widgets;
	cawd->num_dapm_widgets = AWWAY_SIZE(cawd_widgets);
	cawd->dapm_woutes = cawd_base_woutes;
	cawd->num_dapm_woutes = AWWAY_SIZE(cawd_base_woutes);
	cawd->fuwwy_wouted = twue;

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(cawd, pname);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct pwatfowm_device_id avs_wt5514_dwivew_ids[] = {
	{
		.name = "avs_wt5514",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_wt5514_dwivew_ids);

static stwuct pwatfowm_dwivew avs_wt5514_dwivew = {
	.pwobe = avs_wt5514_pwobe,
	.dwivew = {
		.name = "avs_wt5514",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_wt5514_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_wt5514_dwivew);

MODUWE_WICENSE("GPW");
