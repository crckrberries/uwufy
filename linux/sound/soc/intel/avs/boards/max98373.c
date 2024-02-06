// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude "../utiws.h"

#define MAX98373_DEV0_NAME	"i2c-MX98373:00"
#define MAX98373_DEV1_NAME	"i2c-MX98373:01"
#define MAX98373_CODEC_NAME	"max98373-aif1"

static stwuct snd_soc_codec_conf cawd_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF(MAX98373_DEV0_NAME),
		.name_pwefix = "Wight",
	},
	{
		.dwc = COMP_CODEC_CONF(MAX98373_DEV1_NAME),
		.name_pwefix = "Weft",
	},
};

static const stwuct snd_kcontwow_new cawd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
};

static const stwuct snd_soc_dapm_widget cawd_widgets[] = {
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute cawd_base_woutes[] = {
	{ "Weft Spk", NUWW, "Weft BE_OUT" },
	{ "Wight Spk", NUWW, "Wight BE_OUT" },
};

static int
avs_max98373_be_fixup(stwuct snd_soc_pcm_wuntime *wunwime, stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate, *channews;
	stwuct snd_mask *fmt;

	wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	/* The ADSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	/* set SSP0 to 16 bit */
	snd_mask_none(fmt);
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S16_WE);
	wetuwn 0;
}

static int avs_max98373_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	int wet, i;

	fow_each_wtd_codec_dais(wuntime, i, codec_dai) {
		if (!stwcmp(codec_dai->component->name, MAX98373_DEV0_NAME)) {
			wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x30, 3, 8, 16);
			if (wet < 0) {
				dev_eww(wuntime->dev, "DEV0 TDM swot eww:%d\n", wet);
				wetuwn wet;
			}
		}
		if (!stwcmp(codec_dai->component->name, MAX98373_DEV1_NAME)) {
			wet = snd_soc_dai_set_tdm_swot(codec_dai, 0xC0, 3, 8, 16);
			if (wet < 0) {
				dev_eww(wuntime->dev, "DEV1 TDM swot eww:%d\n", wet);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops avs_max98373_ops = {
	.hw_pawams = avs_max98373_hw_pawams,
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
	dw->codecs = devm_kzawwoc(dev, sizeof(*dw->codecs) * 2, GFP_KEWNEW);
	if (!dw->name || !dw->cpus || !dw->codecs)
		wetuwn -ENOMEM;

	dw->cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
					    AVS_STWING_FMT("SSP", " Pin", ssp_powt, tdm_swot));
	dw->codecs[0].name = devm_kaspwintf(dev, GFP_KEWNEW, MAX98373_DEV0_NAME);
	dw->codecs[0].dai_name = devm_kaspwintf(dev, GFP_KEWNEW, MAX98373_CODEC_NAME);
	dw->codecs[1].name = devm_kaspwintf(dev, GFP_KEWNEW, MAX98373_DEV1_NAME);
	dw->codecs[1].dai_name = devm_kaspwintf(dev, GFP_KEWNEW, MAX98373_CODEC_NAME);
	if (!dw->cpus->dai_name || !dw->codecs[0].name || !dw->codecs[0].dai_name ||
	    !dw->codecs[1].name || !dw->codecs[1].dai_name)
		wetuwn -ENOMEM;

	dw->num_cpus = 1;
	dw->num_codecs = 2;
	dw->pwatfowms = pwatfowm;
	dw->num_pwatfowms = 1;
	dw->id = 0;
	dw->dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBC_CFC;
	dw->be_hw_pawams_fixup = avs_max98373_be_fixup;
	dw->nonatomic = 1;
	dw->no_pcm = 1;
	dw->dpcm_captuwe = 1;
	dw->dpcm_pwayback = 1;
	dw->ignowe_pmdown_time = 1;
	dw->ops = &avs_max98373_ops;

	*dai_wink = dw;

	wetuwn 0;
}

static int avs_max98373_pwobe(stwuct pwatfowm_device *pdev)
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

	cawd->name = "avs_max98373";
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dai_wink = dai_wink;
	cawd->num_winks = 1;
	cawd->codec_conf = cawd_codec_conf;
	cawd->num_configs = AWWAY_SIZE(cawd_codec_conf);
	cawd->contwows = cawd_contwows;
	cawd->num_contwows = AWWAY_SIZE(cawd_contwows);
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

static const stwuct pwatfowm_device_id avs_max98373_dwivew_ids[] = {
	{
		.name = "avs_max98373",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_max98373_dwivew_ids);

static stwuct pwatfowm_dwivew avs_max98373_dwivew = {
	.pwobe = avs_max98373_pwobe,
	.dwivew = {
		.name = "avs_max98373",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_max98373_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_max98373_dwivew)

MODUWE_WICENSE("GPW");
