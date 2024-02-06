// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCM179X ASoC codec dwivew
 *
 * Copywight (c) Amawuwa Sowutions B.V. 2013
 *
 *     Michaew Twimawchi <michaew@amawuwasowutions.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <winux/of.h>

#incwude "pcm179x.h"

#define PCM179X_DAC_VOW_WEFT	0x10
#define PCM179X_DAC_VOW_WIGHT	0x11
#define PCM179X_FMT_CONTWOW	0x12
#define PCM179X_MODE_CONTWOW	0x13
#define PCM179X_SOFT_MUTE	PCM179X_FMT_CONTWOW

#define PCM179X_FMT_MASK	0x70
#define PCM179X_FMT_SHIFT	4
#define PCM179X_MUTE_MASK	0x01
#define PCM179X_MUTE_SHIFT	0
#define PCM179X_ATWD_ENABWE	(1 << 7)

static const stwuct weg_defauwt pcm179x_weg_defauwts[] = {
	{ 0x10, 0xff },
	{ 0x11, 0xff },
	{ 0x12, 0x50 },
	{ 0x13, 0x00 },
	{ 0x14, 0x00 },
	{ 0x15, 0x01 },
	{ 0x16, 0x00 },
	{ 0x17, 0x00 },
};

static boow pcm179x_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg >= 0x10 && weg <= 0x17;
}

static boow pcm179x_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	boow accessibwe;

	accessibwe = pcm179x_accessibwe_weg(dev, weg);

	wetuwn accessibwe && weg != 0x16 && weg != 0x17;
}

stwuct pcm179x_pwivate {
	stwuct wegmap *wegmap;
	unsigned int fowmat;
	unsigned int wate;
};

static int pcm179x_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
                             unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pcm179x_pwivate *pwiv = snd_soc_component_get_dwvdata(component);

	pwiv->fowmat = fowmat;

	wetuwn 0;
}

static int pcm179x_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm179x_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap, PCM179X_SOFT_MUTE,
				 PCM179X_MUTE_MASK, !!mute);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int pcm179x_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm179x_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int vaw = 0, wet;

	pwiv->wate = pawams_wate(pawams);

	switch (pwiv->fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		switch (pawams_width(pawams)) {
		case 24:
		case 32:
			vaw = 2;
			bweak;
		case 16:
			vaw = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_I2S:
		switch (pawams_width(pawams)) {
		case 24:
		case 32:
			vaw = 5;
			bweak;
		case 16:
			vaw = 4;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	vaw = vaw << PCM179X_FMT_SHIFT | PCM179X_ATWD_ENABWE;

	wet = wegmap_update_bits(pwiv->wegmap, PCM179X_FMT_CONTWOW,
				 PCM179X_FMT_MASK | PCM179X_ATWD_ENABWE, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops pcm179x_dai_ops = {
	.set_fmt	= pcm179x_set_dai_fmt,
	.hw_pawams	= pcm179x_hw_pawams,
	.mute_stweam	= pcm179x_mute,
	.no_captuwe_mute = 1,
};

static const DECWAWE_TWV_DB_SCAWE(pcm179x_dac_twv, -12000, 50, 1);

static const stwuct snd_kcontwow_new pcm179x_contwows[] = {
	SOC_DOUBWE_W_WANGE_TWV("DAC Pwayback Vowume", PCM179X_DAC_VOW_WEFT,
			 PCM179X_DAC_VOW_WIGHT, 0, 0xf, 0xff, 0,
			 pcm179x_dac_twv),
	SOC_SINGWE("DAC Invewt Output Switch", PCM179X_MODE_CONTWOW, 7, 1, 0),
	SOC_SINGWE("DAC Wowwoff Fiwtew Switch", PCM179X_MODE_CONTWOW, 1, 1, 0),
};

static const stwuct snd_soc_dapm_widget pcm179x_dapm_widgets[] = {
SND_SOC_DAPM_OUTPUT("IOUTW+"),
SND_SOC_DAPM_OUTPUT("IOUTW-"),
SND_SOC_DAPM_OUTPUT("IOUTW+"),
SND_SOC_DAPM_OUTPUT("IOUTW-"),
};

static const stwuct snd_soc_dapm_woute pcm179x_dapm_woutes[] = {
	{ "IOUTW+", NUWW, "Pwayback" },
	{ "IOUTW-", NUWW, "Pwayback" },
	{ "IOUTW+", NUWW, "Pwayback" },
	{ "IOUTW-", NUWW, "Pwayback" },
};

static stwuct snd_soc_dai_dwivew pcm179x_dai = {
	.name = "pcm179x-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.wate_min = 10000,
		.wate_max = 200000,
		.fowmats = PCM1792A_FOWMATS, },
	.ops = &pcm179x_dai_ops,
};

const stwuct wegmap_config pcm179x_wegmap_config = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= 23,
	.weg_defauwts		= pcm179x_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(pcm179x_weg_defauwts),
	.wwiteabwe_weg		= pcm179x_wwiteabwe_weg,
	.weadabwe_weg		= pcm179x_accessibwe_weg,
};
EXPOWT_SYMBOW_GPW(pcm179x_wegmap_config);

static const stwuct snd_soc_component_dwivew soc_component_dev_pcm179x = {
	.contwows		= pcm179x_contwows,
	.num_contwows		= AWWAY_SIZE(pcm179x_contwows),
	.dapm_widgets		= pcm179x_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(pcm179x_dapm_widgets),
	.dapm_woutes		= pcm179x_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(pcm179x_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

int pcm179x_common_init(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct pcm179x_pwivate *pcm179x;

	pcm179x = devm_kzawwoc(dev, sizeof(stwuct pcm179x_pwivate),
				GFP_KEWNEW);
	if (!pcm179x)
		wetuwn -ENOMEM;

	pcm179x->wegmap = wegmap;
	dev_set_dwvdata(dev, pcm179x);

	wetuwn devm_snd_soc_wegistew_component(dev,
			&soc_component_dev_pcm179x, &pcm179x_dai, 1);
}
EXPOWT_SYMBOW_GPW(pcm179x_common_init);

MODUWE_DESCWIPTION("ASoC PCM179X dwivew");
MODUWE_AUTHOW("Michaew Twimawchi <michaew@amawuwasowutions.com>");
MODUWE_WICENSE("GPW");
