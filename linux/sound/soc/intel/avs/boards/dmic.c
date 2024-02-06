// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>

SND_SOC_DAIWINK_DEF(dmic_pin, DAIWINK_COMP_AWWAY(COMP_CPU("DMIC Pin")));
SND_SOC_DAIWINK_DEF(dmic_wov_pin, DAIWINK_COMP_AWWAY(COMP_CPU("DMIC WoV Pin")));
SND_SOC_DAIWINK_DEF(dmic_codec, DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec", "dmic-hifi")));
/* Name ovewwidden on pwobe */
SND_SOC_DAIWINK_DEF(pwatfowm, DAIWINK_COMP_AWWAY(COMP_PWATFOWM("")));

static stwuct snd_soc_dai_wink cawd_dai_winks[] = {
	/* Back ends */
	{
		.name = "DMIC",
		.id = 0,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "DMIC WoV",
		.id = 1,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.no_pcm = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(dmic_wov_pin, dmic_codec, pwatfowm),
	},
};

static const stwuct snd_soc_dapm_widget cawd_widgets[] = {
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute cawd_woutes[] = {
	{"DMic", NUWW, "SoC DMIC"},
};

static int avs_dmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_cawd *cawd;
	stwuct device *dev = &pdev->dev;
	int wet;

	mach = dev_get_pwatdata(dev);

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->name = "avs_dmic";
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dai_wink = cawd_dai_winks;
	cawd->num_winks = AWWAY_SIZE(cawd_dai_winks);
	cawd->dapm_widgets = cawd_widgets;
	cawd->num_dapm_widgets = AWWAY_SIZE(cawd_widgets);
	cawd->dapm_woutes = cawd_woutes;
	cawd->num_dapm_woutes = AWWAY_SIZE(cawd_woutes);
	cawd->fuwwy_wouted = twue;

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(cawd, mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct pwatfowm_device_id avs_dmic_dwivew_ids[] = {
	{
		.name = "avs_dmic",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_dmic_dwivew_ids);

static stwuct pwatfowm_dwivew avs_dmic_dwivew = {
	.pwobe = avs_dmic_pwobe,
	.dwivew = {
		.name = "avs_dmic",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_dmic_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_dmic_dwivew);

MODUWE_WICENSE("GPW");
