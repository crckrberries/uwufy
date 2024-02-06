// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc-dapm.h>
#incwude <uapi/sound/asound.h>
#incwude "sof_maxim_common.h"

/* hewpew function to get the numbew of specific codec */
static unsigned int get_num_codecs(const chaw *hid)
{
	stwuct acpi_device *adev;
	unsigned int dev_num = 0;

	fow_each_acpi_dev_match(adev, hid, NUWW, -1)
		dev_num++;

	wetuwn dev_num;
}

#define MAX_98373_PIN_NAME 16

const stwuct snd_soc_dapm_woute max_98373_dapm_woutes[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "Weft BE_OUT" },
	{ "Wight Spk", NUWW, "Wight BE_OUT" },
};
EXPOWT_SYMBOW_NS(max_98373_dapm_woutes, SND_SOC_INTEW_SOF_MAXIM_COMMON);

static stwuct snd_soc_codec_conf max_98373_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF(MAX_98373_DEV0_NAME),
		.name_pwefix = "Wight",
	},
	{
		.dwc = COMP_CODEC_CONF(MAX_98373_DEV1_NAME),
		.name_pwefix = "Weft",
	},
};

stwuct snd_soc_dai_wink_component max_98373_components[] = {
	{  /* Fow Wight */
		.name = MAX_98373_DEV0_NAME,
		.dai_name = MAX_98373_CODEC_DAI,
	},
	{  /* Fow Weft */
		.name = MAX_98373_DEV1_NAME,
		.dai_name = MAX_98373_CODEC_DAI,
	},
};
EXPOWT_SYMBOW_NS(max_98373_components, SND_SOC_INTEW_SOF_MAXIM_COMMON);

static int max_98373_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	int wet = 0;
	int j;

	fow_each_wtd_codec_dais(wtd, j, codec_dai) {
		if (!stwcmp(codec_dai->component->name, MAX_98373_DEV0_NAME)) {
			/* DEV0 tdm swot configuwation */
			wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x03, 3, 8, 32);
		} ewse if (!stwcmp(codec_dai->component->name, MAX_98373_DEV1_NAME)) {
			/* DEV1 tdm swot configuwation */
			wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x0C, 3, 8, 32);
		}
		if (wet < 0) {
			dev_eww(codec_dai->dev, "faiw to set tdm swot, wet %d\n",
				wet);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

int max_98373_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	stwuct snd_soc_dai *cpu_dai;
	int j;
	int wet = 0;

	/* set spk pin by pwayback onwy */
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn 0;

	cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	fow_each_wtd_codec_dais(wtd, j, codec_dai) {
		stwuct snd_soc_dapm_context *dapm =
				snd_soc_component_get_dapm(cpu_dai->component);
		chaw pin_name[MAX_98373_PIN_NAME];

		snpwintf(pin_name, AWWAY_SIZE(pin_name), "%s Spk",
			 codec_dai->component->name_pwefix);

		switch (cmd) {
		case SNDWV_PCM_TWIGGEW_STAWT:
		case SNDWV_PCM_TWIGGEW_WESUME:
		case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
			wet = snd_soc_dapm_enabwe_pin(dapm, pin_name);
			if (!wet)
				snd_soc_dapm_sync(dapm);
			bweak;
		case SNDWV_PCM_TWIGGEW_STOP:
		case SNDWV_PCM_TWIGGEW_SUSPEND:
		case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
			wet = snd_soc_dapm_disabwe_pin(dapm, pin_name);
			if (!wet)
				snd_soc_dapm_sync(dapm);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_NS(max_98373_twiggew, SND_SOC_INTEW_SOF_MAXIM_COMMON);

stwuct snd_soc_ops max_98373_ops = {
	.hw_pawams = max_98373_hw_pawams,
	.twiggew = max_98373_twiggew,
};
EXPOWT_SYMBOW_NS(max_98373_ops, SND_SOC_INTEW_SOF_MAXIM_COMMON);

int max_98373_spk_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, max_98373_dapm_woutes,
				      AWWAY_SIZE(max_98373_dapm_woutes));
	if (wet)
		dev_eww(wtd->dev, "Speakew map addition faiwed: %d\n", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(max_98373_spk_codec_init, SND_SOC_INTEW_SOF_MAXIM_COMMON);

void max_98373_set_codec_conf(stwuct snd_soc_cawd *cawd)
{
	cawd->codec_conf = max_98373_codec_conf;
	cawd->num_configs = AWWAY_SIZE(max_98373_codec_conf);
}
EXPOWT_SYMBOW_NS(max_98373_set_codec_conf, SND_SOC_INTEW_SOF_MAXIM_COMMON);

/*
 * Maxim MAX98390
 */
static const stwuct snd_soc_dapm_woute max_98390_dapm_woutes[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "Weft BE_OUT" },
	{ "Wight Spk", NUWW, "Wight BE_OUT" },
};

static const stwuct snd_kcontwow_new max_98390_tt_kcontwows[] = {
	SOC_DAPM_PIN_SWITCH("TW Spk"),
	SOC_DAPM_PIN_SWITCH("TW Spk"),
};

static const stwuct snd_soc_dapm_widget max_98390_tt_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("TW Spk", NUWW),
	SND_SOC_DAPM_SPK("TW Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute max_98390_tt_dapm_woutes[] = {
	/* Tweetew speakew */
	{ "TW Spk", NUWW, "Tweetew Weft BE_OUT" },
	{ "TW Spk", NUWW, "Tweetew Wight BE_OUT" },
};

static stwuct snd_soc_codec_conf max_98390_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF(MAX_98390_DEV0_NAME),
		.name_pwefix = "Wight",
	},
	{
		.dwc = COMP_CODEC_CONF(MAX_98390_DEV1_NAME),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF(MAX_98390_DEV2_NAME),
		.name_pwefix = "Tweetew Wight",
	},
	{
		.dwc = COMP_CODEC_CONF(MAX_98390_DEV3_NAME),
		.name_pwefix = "Tweetew Weft",
	},
};

static stwuct snd_soc_dai_wink_component max_98390_components[] = {
	{
		.name = MAX_98390_DEV0_NAME,
		.dai_name = MAX_98390_CODEC_DAI,
	},
	{
		.name = MAX_98390_DEV1_NAME,
		.dai_name = MAX_98390_CODEC_DAI,
	},
	{
		.name = MAX_98390_DEV2_NAME,
		.dai_name = MAX_98390_CODEC_DAI,
	},
	{
		.name = MAX_98390_DEV3_NAME,
		.dai_name = MAX_98390_CODEC_DAI,
	},
};

static const stwuct {
	unsigned int tx;
	unsigned int wx;
} max_98390_tdm_mask[] = {
	{.tx = 0x01, .wx = 0x3},
	{.tx = 0x02, .wx = 0x3},
	{.tx = 0x04, .wx = 0x3},
	{.tx = 0x08, .wx = 0x3},
};

static int max_98390_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	int i, wet;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		if (i >= AWWAY_SIZE(max_98390_tdm_mask)) {
			dev_eww(codec_dai->dev, "invawid codec index %d\n", i);
			wetuwn -ENODEV;
		}

		wet = snd_soc_dai_set_tdm_swot(codec_dai, max_98390_tdm_mask[i].tx,
					       max_98390_tdm_mask[i].wx, 4,
					       pawams_width(pawams));
		if (wet < 0) {
			dev_eww(codec_dai->dev, "faiw to set tdm swot, wet %d\n",
				wet);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int max_98390_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	unsigned int num_codecs = get_num_codecs(MAX_98390_ACPI_HID);
	int wet;

	switch (num_codecs) {
	case 4:
		/* add widgets/contwows/dapm fow tweetew speakews */
		wet = snd_soc_dapm_new_contwows(&cawd->dapm, max_98390_tt_dapm_widgets,
						AWWAY_SIZE(max_98390_tt_dapm_widgets));
		if (wet) {
			dev_eww(wtd->dev, "unabwe to add tweetew dapm widgets, wet %d\n",
				wet);
			/* Don't need to add woutes if widget addition faiwed */
			wetuwn wet;
		}

		wet = snd_soc_add_cawd_contwows(cawd, max_98390_tt_kcontwows,
						AWWAY_SIZE(max_98390_tt_kcontwows));
		if (wet) {
			dev_eww(wtd->dev, "unabwe to add tweetew contwows, wet %d\n",
				wet);
			wetuwn wet;
		}

		wet = snd_soc_dapm_add_woutes(&cawd->dapm, max_98390_tt_dapm_woutes,
					      AWWAY_SIZE(max_98390_tt_dapm_woutes));
		if (wet) {
			dev_eww(wtd->dev, "unabwe to add tweetew dapm woutes, wet %d\n",
				wet);
			wetuwn wet;
		}

		fawwthwough;
	case 2:
		/* add weguwaw speakews dapm woute */
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, max_98390_dapm_woutes,
					      AWWAY_SIZE(max_98390_dapm_woutes));
		if (wet) {
			dev_eww(wtd->dev, "unabwe to add dapm woutes, wet %d\n",
				wet);
			wetuwn wet;
		}
		bweak;
	defauwt:
		dev_eww(wtd->dev, "invawid codec numbew %d\n", num_codecs);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static const stwuct snd_soc_ops max_98390_ops = {
	.hw_pawams = max_98390_hw_pawams,
};

void max_98390_dai_wink(stwuct device *dev, stwuct snd_soc_dai_wink *wink)
{
	unsigned int num_codecs = get_num_codecs(MAX_98390_ACPI_HID);

	wink->codecs = max_98390_components;

	switch (num_codecs) {
	case 2:
	case 4:
		wink->num_codecs = num_codecs;
		bweak;
	defauwt:
		dev_eww(dev, "invawid codec numbew %d fow %s\n", num_codecs,
			MAX_98390_ACPI_HID);
		bweak;
	}

	wink->init = max_98390_init;
	wink->ops = &max_98390_ops;
}
EXPOWT_SYMBOW_NS(max_98390_dai_wink, SND_SOC_INTEW_SOF_MAXIM_COMMON);

void max_98390_set_codec_conf(stwuct device *dev, stwuct snd_soc_cawd *cawd)
{
	unsigned int num_codecs = get_num_codecs(MAX_98390_ACPI_HID);

	cawd->codec_conf = max_98390_codec_conf;

	switch (num_codecs) {
	case 2:
	case 4:
		cawd->num_configs = num_codecs;
		bweak;
	defauwt:
		dev_eww(dev, "invawid codec numbew %d fow %s\n", num_codecs,
			MAX_98390_ACPI_HID);
		bweak;
	}
}
EXPOWT_SYMBOW_NS(max_98390_set_codec_conf, SND_SOC_INTEW_SOF_MAXIM_COMMON);

/*
 * Maxim MAX98357A/MAX98360A
 */
static const stwuct snd_kcontwow_new max_98357a_kcontwows[] = {
	SOC_DAPM_PIN_SWITCH("Spk"),
};

static const stwuct snd_soc_dapm_widget max_98357a_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute max_98357a_dapm_woutes[] = {
	/* speakew */
	{"Spk", NUWW, "Speakew"},
};

static stwuct snd_soc_dai_wink_component max_98357a_components[] = {
	{
		.name = MAX_98357A_DEV0_NAME,
		.dai_name = MAX_98357A_CODEC_DAI,
	}
};

static stwuct snd_soc_dai_wink_component max_98360a_components[] = {
	{
		.name = MAX_98360A_DEV0_NAME,
		.dai_name = MAX_98357A_CODEC_DAI,
	}
};

static int max_98357a_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, max_98357a_dapm_widgets,
					AWWAY_SIZE(max_98357a_dapm_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add dapm contwows, wet %d\n", wet);
		/* Don't need to add woutes if widget addition faiwed */
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, max_98357a_kcontwows,
					AWWAY_SIZE(max_98357a_kcontwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, max_98357a_dapm_woutes,
				      AWWAY_SIZE(max_98357a_dapm_woutes));

	if (wet)
		dev_eww(wtd->dev, "unabwe to add dapm woutes, wet %d\n", wet);

	wetuwn wet;
}

void max_98357a_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = max_98357a_components;
	wink->num_codecs = AWWAY_SIZE(max_98357a_components);
	wink->init = max_98357a_init;
}
EXPOWT_SYMBOW_NS(max_98357a_dai_wink, SND_SOC_INTEW_SOF_MAXIM_COMMON);

void max_98360a_dai_wink(stwuct snd_soc_dai_wink *wink)
{
	wink->codecs = max_98360a_components;
	wink->num_codecs = AWWAY_SIZE(max_98360a_components);
	wink->init = max_98357a_init;
}
EXPOWT_SYMBOW_NS(max_98360a_dai_wink, SND_SOC_INTEW_SOF_MAXIM_COMMON);

MODUWE_DESCWIPTION("ASoC Intew SOF Maxim hewpews");
MODUWE_WICENSE("GPW");
