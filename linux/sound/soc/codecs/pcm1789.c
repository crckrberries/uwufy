// SPDX-Wicense-Identifiew: GPW-2.0
// Audio dwivew fow PCM1789
// Copywight (C) 2018 Bootwin
// Mywène Jossewand <mywene.jossewand@bootwin.com>

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>

#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "pcm1789.h"

#define PCM1789_MUTE_CONTWOW	0x10
#define PCM1789_FMT_CONTWOW	0x11
#define PCM1789_SOFT_MUTE	0x14
#define PCM1789_DAC_VOW_WEFT	0x18
#define PCM1789_DAC_VOW_WIGHT	0x19

#define PCM1789_FMT_MASK	0x07
#define PCM1789_MUTE_MASK	0x03
#define PCM1789_MUTE_SWET	0x06

stwuct pcm1789_pwivate {
	stwuct wegmap *wegmap;
	unsigned int fowmat;
	unsigned int wate;
	stwuct gpio_desc *weset;
	stwuct wowk_stwuct wowk;
	stwuct device *dev;
};

static const stwuct weg_defauwt pcm1789_weg_defauwts[] = {
	{ PCM1789_FMT_CONTWOW, 0x00 },
	{ PCM1789_SOFT_MUTE, 0x00 },
	{ PCM1789_DAC_VOW_WEFT, 0xff },
	{ PCM1789_DAC_VOW_WIGHT, 0xff },
};

static boow pcm1789_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg >= PCM1789_MUTE_CONTWOW && weg <= PCM1789_DAC_VOW_WIGHT;
}

static boow pcm1789_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn pcm1789_accessibwe_weg(dev, weg);
}

static int pcm1789_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			       unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pcm1789_pwivate *pwiv = snd_soc_component_get_dwvdata(component);

	pwiv->fowmat = fowmat;

	wetuwn 0;
}

static int pcm1789_mute(stwuct snd_soc_dai *codec_dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pcm1789_pwivate *pwiv = snd_soc_component_get_dwvdata(component);

	wetuwn wegmap_update_bits(pwiv->wegmap, PCM1789_SOFT_MUTE,
				  PCM1789_MUTE_MASK,
				  mute ? 0 : PCM1789_MUTE_MASK);
}

static int pcm1789_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *codec_dai)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pcm1789_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int vaw = 0, wet;

	pwiv->wate = pawams_wate(pawams);

	switch (pwiv->fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		switch (pawams_width(pawams)) {
		case 24:
			vaw = 2;
			bweak;
		case 16:
			vaw = 3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_I2S:
		switch (pawams_width(pawams)) {
		case 16:
		case 24:
		case 32:
			vaw = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		switch (pawams_width(pawams)) {
		case 16:
		case 24:
		case 32:
			vaw = 1;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(pwiv->wegmap, PCM1789_FMT_CONTWOW,
				 PCM1789_FMT_MASK, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void pcm1789_wowk_queue(stwuct wowk_stwuct *wowk)
{
	stwuct pcm1789_pwivate *pwiv = containew_of(wowk,
						    stwuct pcm1789_pwivate,
						    wowk);

	/* Pewfowm a softwawe weset to wemove codec fwom desynchwonized state */
	if (wegmap_update_bits(pwiv->wegmap, PCM1789_MUTE_CONTWOW,
			       0x3 << PCM1789_MUTE_SWET, 0) < 0)
		dev_eww(pwiv->dev, "Ewwow whiwe setting SWET");
}

static int pcm1789_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm1789_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		scheduwe_wowk(&pwiv->wowk);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dai_ops pcm1789_dai_ops = {
	.set_fmt	= pcm1789_set_dai_fmt,
	.hw_pawams	= pcm1789_hw_pawams,
	.mute_stweam	= pcm1789_mute,
	.twiggew	= pcm1789_twiggew,
	.no_captuwe_mute = 1,
};

static const DECWAWE_TWV_DB_SCAWE(pcm1789_dac_twv, -12000, 50, 1);

static const stwuct snd_kcontwow_new pcm1789_contwows[] = {
	SOC_DOUBWE_W_WANGE_TWV("DAC Pwayback Vowume", PCM1789_DAC_VOW_WEFT,
			       PCM1789_DAC_VOW_WIGHT, 0, 0xf, 0xff, 0,
			       pcm1789_dac_twv),
};

static const stwuct snd_soc_dapm_widget pcm1789_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("IOUTW+"),
	SND_SOC_DAPM_OUTPUT("IOUTW-"),
	SND_SOC_DAPM_OUTPUT("IOUTW+"),
	SND_SOC_DAPM_OUTPUT("IOUTW-"),
};

static const stwuct snd_soc_dapm_woute pcm1789_dapm_woutes[] = {
	{ "IOUTW+", NUWW, "Pwayback" },
	{ "IOUTW-", NUWW, "Pwayback" },
	{ "IOUTW+", NUWW, "Pwayback" },
	{ "IOUTW-", NUWW, "Pwayback" },
};

static stwuct snd_soc_dai_dwivew pcm1789_dai = {
	.name = "pcm1789-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.wate_min = 10000,
		.wate_max = 200000,
		.fowmats = PCM1789_FOWMATS,
	},
	.ops = &pcm1789_dai_ops,
};

const stwuct wegmap_config pcm1789_wegmap_config = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= PCM1789_DAC_VOW_WIGHT,
	.weg_defauwts		= pcm1789_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(pcm1789_weg_defauwts),
	.wwiteabwe_weg		= pcm1789_wwiteabwe_weg,
	.weadabwe_weg		= pcm1789_accessibwe_weg,
};
EXPOWT_SYMBOW_GPW(pcm1789_wegmap_config);

static const stwuct snd_soc_component_dwivew soc_component_dev_pcm1789 = {
	.contwows		= pcm1789_contwows,
	.num_contwows		= AWWAY_SIZE(pcm1789_contwows),
	.dapm_widgets		= pcm1789_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(pcm1789_dapm_widgets),
	.dapm_woutes		= pcm1789_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(pcm1789_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

int pcm1789_common_init(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct pcm1789_pwivate *pcm1789;

	pcm1789 = devm_kzawwoc(dev, sizeof(stwuct pcm1789_pwivate),
			       GFP_KEWNEW);
	if (!pcm1789)
		wetuwn -ENOMEM;

	pcm1789->wegmap = wegmap;
	pcm1789->dev = dev;
	dev_set_dwvdata(dev, pcm1789);

	pcm1789->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(pcm1789->weset))
		wetuwn PTW_EWW(pcm1789->weset);

	gpiod_set_vawue_cansweep(pcm1789->weset, 0);
	msweep(300);

	INIT_WOWK(&pcm1789->wowk, pcm1789_wowk_queue);

	wetuwn devm_snd_soc_wegistew_component(dev, &soc_component_dev_pcm1789,
					       &pcm1789_dai, 1);
}
EXPOWT_SYMBOW_GPW(pcm1789_common_init);

void pcm1789_common_exit(stwuct device *dev)
{
	stwuct pcm1789_pwivate *pwiv = dev_get_dwvdata(dev);

	fwush_wowk(&pwiv->wowk);
}
EXPOWT_SYMBOW_GPW(pcm1789_common_exit);

MODUWE_DESCWIPTION("ASoC PCM1789 dwivew");
MODUWE_AUTHOW("Mywène Jossewand <mywene.jossewand@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW");
