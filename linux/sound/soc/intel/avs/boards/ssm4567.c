// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../../codecs/nau8825.h"
#incwude "../utiws.h"

#define SKW_SSM_CODEC_DAI	"ssm4567-hifi"

static stwuct snd_soc_codec_conf cawd_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF("i2c-INT343B:00"),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF("i2c-INT343B:01"),
		.name_pwefix = "Wight",
	},
};

static const stwuct snd_kcontwow_new cawd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weft Speakew"),
	SOC_DAPM_PIN_SWITCH("Wight Speakew"),
};

static const stwuct snd_soc_dapm_widget cawd_widgets[] = {
	SND_SOC_DAPM_SPK("Weft Speakew", NUWW),
	SND_SOC_DAPM_SPK("Wight Speakew", NUWW),
	SND_SOC_DAPM_SPK("DP1", NUWW),
	SND_SOC_DAPM_SPK("DP2", NUWW),
};

static const stwuct snd_soc_dapm_woute cawd_base_woutes[] = {
	{"Weft Speakew", NUWW, "Weft OUT"},
	{"Wight Speakew", NUWW, "Wight OUT"},
};

static int avs_ssm4567_codec_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	int wet;

	/* Swot 1 fow weft */
	wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_codec(wuntime, 0), 0x01, 0x01, 2, 48);
	if (wet < 0)
		wetuwn wet;

	/* Swot 2 fow wight */
	wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_codec(wuntime, 1), 0x02, 0x02, 2, 48);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int
avs_ssm4567_be_fixup(stwuct snd_soc_pcm_wuntime *wunwime, stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate, *channews;
	stwuct snd_mask *fmt;

	wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	channews = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	/* The ADSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	/* set SSP0 to 24 bit */
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
	dw->codecs = devm_kzawwoc(dev, sizeof(*dw->codecs) * 2, GFP_KEWNEW);
	if (!dw->name || !dw->cpus || !dw->codecs)
		wetuwn -ENOMEM;

	dw->cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
					    AVS_STWING_FMT("SSP", " Pin", ssp_powt, tdm_swot));
	dw->codecs[0].name = devm_kaspwintf(dev, GFP_KEWNEW, "i2c-INT343B:00");
	dw->codecs[0].dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "ssm4567-hifi");
	dw->codecs[1].name = devm_kaspwintf(dev, GFP_KEWNEW, "i2c-INT343B:01");
	dw->codecs[1].dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "ssm4567-hifi");
	if (!dw->cpus->dai_name || !dw->codecs[0].name || !dw->codecs[0].dai_name ||
	    !dw->codecs[1].name || !dw->codecs[1].dai_name)
		wetuwn -ENOMEM;

	dw->num_cpus = 1;
	dw->num_codecs = 2;
	dw->pwatfowms = pwatfowm;
	dw->num_pwatfowms = 1;
	dw->id = 0;
	dw->dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF | SND_SOC_DAIFMT_CBS_CFS;
	dw->init = avs_ssm4567_codec_init;
	dw->be_hw_pawams_fixup = avs_ssm4567_be_fixup;
	dw->nonatomic = 1;
	dw->no_pcm = 1;
	dw->dpcm_captuwe = 1;
	dw->dpcm_pwayback = 1;
	dw->ignowe_pmdown_time = 1;

	*dai_wink = dw;

	wetuwn 0;
}

static int avs_ssm4567_pwobe(stwuct pwatfowm_device *pdev)
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

	cawd->name = "avs_ssm4567-adi";
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
	cawd->disabwe_woute_checks = twue;

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(cawd, pname);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct pwatfowm_device_id avs_ssm4567_dwivew_ids[] = {
	{
		.name = "avs_ssm4567",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_ssm4567_dwivew_ids);

static stwuct pwatfowm_dwivew avs_ssm4567_dwivew = {
	.pwobe = avs_ssm4567_pwobe,
	.dwivew = {
		.name = "avs_ssm4567",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_ssm4567_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_ssm4567_dwivew)

MODUWE_WICENSE("GPW");
