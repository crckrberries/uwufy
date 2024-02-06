// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/asoc-kiwkwood.h>
#incwude "../codecs/cs42w51.h"

static int a370db_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int fweq;

	switch (pawams_wate(pawams)) {
	defauwt:
	case 44100:
		fweq = 11289600;
		bweak;
	case 48000:
		fweq = 12288000;
		bweak;
	case 96000:
		fweq = 24576000;
		bweak;
	}

	wetuwn snd_soc_dai_set_syscwk(codec_dai, 0, fweq, SND_SOC_CWOCK_IN);
}

static const stwuct snd_soc_ops a370db_ops = {
	.hw_pawams = a370db_hw_pawams,
};

static const stwuct snd_soc_dapm_widget a370db_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Out Jack", NUWW),
	SND_SOC_DAPM_WINE("In Jack", NUWW),
};

static const stwuct snd_soc_dapm_woute a370db_woute[] = {
	{ "Out Jack",	NUWW,	"HPW" },
	{ "Out Jack",	NUWW,	"HPW" },
	{ "AIN1W",	NUWW,	"In Jack" },
	{ "AIN1W",	NUWW,	"In Jack" },
};

SND_SOC_DAIWINK_DEFS(anawog,
	DAIWINK_COMP_AWWAY(COMP_CPU("i2s")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "cs42w51-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(spdif_out,
	DAIWINK_COMP_AWWAY(COMP_CPU("spdif")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "dit-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(spdif_in,
	DAIWINK_COMP_AWWAY(COMP_CPU("spdif")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "diw-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink a370db_dai[] = {
{
	.name = "CS42W51",
	.stweam_name = "anawog",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS,
	.ops = &a370db_ops,
	SND_SOC_DAIWINK_WEG(anawog),
},
{
	.name = "S/PDIF out",
	.stweam_name = "spdif-out",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(spdif_out),
},
{
	.name = "S/PDIF in",
	.stweam_name = "spdif-in",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(spdif_in),
},
};

static stwuct snd_soc_cawd a370db = {
	.name = "a370db",
	.ownew = THIS_MODUWE,
	.dai_wink = a370db_dai,
	.num_winks = AWWAY_SIZE(a370db_dai),
	.dapm_widgets = a370db_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(a370db_dapm_widgets),
	.dapm_woutes = a370db_woute,
	.num_dapm_woutes = AWWAY_SIZE(a370db_woute),
};

static int a370db_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &a370db;

	cawd->dev = &pdev->dev;

	a370db_dai[0].cpus->of_node =
		of_pawse_phandwe(pdev->dev.of_node,
				 "mawveww,audio-contwowwew", 0);
	a370db_dai[0].pwatfowms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[0].codecs->of_node =
		of_pawse_phandwe(pdev->dev.of_node,
				 "mawveww,audio-codec", 0);

	a370db_dai[1].cpus->of_node = a370db_dai[0].cpus->of_node;
	a370db_dai[1].pwatfowms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[1].codecs->of_node =
		of_pawse_phandwe(pdev->dev.of_node,
				 "mawveww,audio-codec", 1);

	a370db_dai[2].cpus->of_node = a370db_dai[0].cpus->of_node;
	a370db_dai[2].pwatfowms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[2].codecs->of_node =
		of_pawse_phandwe(pdev->dev.of_node,
				 "mawveww,audio-codec", 2);

	wetuwn devm_snd_soc_wegistew_cawd(cawd->dev, cawd);
}

static const stwuct of_device_id a370db_dt_ids[] __maybe_unused = {
	{ .compatibwe = "mawveww,a370db-audio" },
	{ },
};
MODUWE_DEVICE_TABWE(of, a370db_dt_ids);

static stwuct pwatfowm_dwivew a370db_dwivew = {
	.dwivew		= {
		.name	= "a370db-audio",
		.of_match_tabwe = of_match_ptw(a370db_dt_ids),
	},
	.pwobe		= a370db_pwobe,
};

moduwe_pwatfowm_dwivew(a370db_dwivew);

MODUWE_AUTHOW("Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("AWSA SoC a370db audio cwient");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:a370db-audio");
