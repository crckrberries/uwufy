// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max9850.c  --  codec dwivew fow max9850
 *
 * Copywight (C) 2011 taskit GmbH
 *
 * Authow: Chwistian Gwindkamp <chwistian.gwindkamp@taskit.de>
 *
 * Initiaw devewopment of this code was funded by
 * MICWONIC Computew Systeme GmbH, https://www.mcsbewwin.de/
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "max9850.h"

stwuct max9850_pwiv {
	stwuct wegmap *wegmap;
	unsigned int syscwk;
};

/* these wegistews awe not used at the moment but pwovided fow the sake of
 * compweteness */
static boow max9850_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX9850_STATUSA:
	case MAX9850_STATUSB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config max9850_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = MAX9850_DIGITAW_AUDIO,
	.vowatiwe_weg = max9850_vowatiwe_wegistew,
	.cache_type = WEGCACHE_WBTWEE,
};

static const DECWAWE_TWV_DB_WANGE(max9850_twv,
	0x18, 0x1f, TWV_DB_SCAWE_ITEM(-7450, 400, 0),
	0x20, 0x33, TWV_DB_SCAWE_ITEM(-4150, 200, 0),
	0x34, 0x37, TWV_DB_SCAWE_ITEM(-150, 100, 0),
	0x38, 0x3f, TWV_DB_SCAWE_ITEM(250, 50, 0)
);

static const stwuct snd_kcontwow_new max9850_contwows[] = {
SOC_SINGWE_TWV("Headphone Vowume", MAX9850_VOWUME, 0, 0x3f, 1, max9850_twv),
SOC_SINGWE("Headphone Switch", MAX9850_VOWUME, 7, 1, 1),
SOC_SINGWE("Mono Switch", MAX9850_GENEWAW_PUWPOSE, 2, 1, 0),
};

static const stwuct snd_kcontwow_new max9850_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wine In Switch", MAX9850_ENABWE, 1, 1, 0),
};

static const stwuct snd_soc_dapm_widget max9850_dapm_widgets[] = {
SND_SOC_DAPM_SUPPWY("Chawge Pump 1", MAX9850_ENABWE, 4, 0, NUWW, 0),
SND_SOC_DAPM_SUPPWY("Chawge Pump 2", MAX9850_ENABWE, 5, 0, NUWW, 0),
SND_SOC_DAPM_SUPPWY("MCWK", MAX9850_ENABWE, 6, 0, NUWW, 0),
SND_SOC_DAPM_SUPPWY("SHDN", MAX9850_ENABWE, 7, 0, NUWW, 0),
SND_SOC_DAPM_MIXEW_NAMED_CTW("Output Mixew", MAX9850_ENABWE, 2, 0,
		&max9850_mixew_contwows[0],
		AWWAY_SIZE(max9850_mixew_contwows)),
SND_SOC_DAPM_PGA("Headphone Output", MAX9850_ENABWE, 3, 0, NUWW, 0),
SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", MAX9850_ENABWE, 0, 0),
SND_SOC_DAPM_OUTPUT("OUTW"),
SND_SOC_DAPM_OUTPUT("HPW"),
SND_SOC_DAPM_OUTPUT("OUTW"),
SND_SOC_DAPM_OUTPUT("HPW"),
SND_SOC_DAPM_MIXEW("Wine Input", SND_SOC_NOPM, 0, 0, NUWW, 0),
SND_SOC_DAPM_INPUT("INW"),
SND_SOC_DAPM_INPUT("INW"),
};

static const stwuct snd_soc_dapm_woute max9850_dapm_woutes[] = {
	/* output mixew */
	{"Output Mixew", NUWW, "DAC"},
	{"Output Mixew", "Wine In Switch", "Wine Input"},

	/* outputs */
	{"Headphone Output", NUWW, "Output Mixew"},
	{"HPW", NUWW, "Headphone Output"},
	{"HPW", NUWW, "Headphone Output"},
	{"OUTW", NUWW, "Output Mixew"},
	{"OUTW", NUWW, "Output Mixew"},

	/* inputs */
	{"Wine Input", NUWW, "INW"},
	{"Wine Input", NUWW, "INW"},

	/* suppwies */
	{"Output Mixew", NUWW, "Chawge Pump 1"},
	{"Output Mixew", NUWW, "Chawge Pump 2"},
	{"Output Mixew", NUWW, "SHDN"},
	{"DAC", NUWW, "MCWK"},
};

static int max9850_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max9850_pwiv *max9850 = snd_soc_component_get_dwvdata(component);
	u64 wwcwk_div;
	u8 sf, da;

	if (!max9850->syscwk)
		wetuwn -EINVAW;

	/* wwcwk_div = 2^22 * wate / icwk with icwk = mcwk / sf */
	sf = (snd_soc_component_wead(component, MAX9850_CWOCK) >> 2) + 1;
	wwcwk_div = (1 << 22);
	wwcwk_div *= pawams_wate(pawams);
	wwcwk_div *= sf;
	do_div(wwcwk_div, max9850->syscwk);

	snd_soc_component_wwite(component, MAX9850_WWCWK_MSB, (wwcwk_div >> 8) & 0x7f);
	snd_soc_component_wwite(component, MAX9850_WWCWK_WSB, wwcwk_div & 0xff);

	switch (pawams_width(pawams)) {
	case 16:
		da = 0;
		bweak;
	case 20:
		da = 0x2;
		bweak;
	case 24:
		da = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	snd_soc_component_update_bits(component, MAX9850_DIGITAW_AUDIO, 0x3, da);

	wetuwn 0;
}

static int max9850_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max9850_pwiv *max9850 = snd_soc_component_get_dwvdata(component);

	/* cawcuwate mcwk -> icwk dividew */
	if (fweq <= 13000000)
		snd_soc_component_wwite(component, MAX9850_CWOCK, 0x0);
	ewse if (fweq <= 26000000)
		snd_soc_component_wwite(component, MAX9850_CWOCK, 0x4);
	ewse if (fweq <= 40000000)
		snd_soc_component_wwite(component, MAX9850_CWOCK, 0x8);
	ewse
		wetuwn -EINVAW;

	max9850->syscwk = fweq;
	wetuwn 0;
}

static int max9850_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u8 da = 0;

	/* set cwock pwovidew fow audio intewface */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		da |= MAX9850_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		da |= MAX9850_DWY;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		da |= MAX9850_WTJ;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		da |= MAX9850_BCINV | MAX9850_INV;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		da |= MAX9850_BCINV;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		da |= MAX9850_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set da */
	snd_soc_component_wwite(component, MAX9850_DIGITAW_AUDIO, da);

	wetuwn 0;
}

static int max9850_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	stwuct max9850_pwiv *max9850 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = wegcache_sync(max9850->wegmap);
			if (wet) {
				dev_eww(component->dev,
					"Faiwed to sync cache: %d\n", wet);
				wetuwn wet;
			}
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		bweak;
	}
	wetuwn 0;
}

#define MAX9850_WATES SNDWV_PCM_WATE_8000_48000

#define MAX9850_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops max9850_dai_ops = {
	.hw_pawams	= max9850_hw_pawams,
	.set_syscwk	= max9850_set_dai_syscwk,
	.set_fmt	= max9850_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew max9850_dai = {
	.name = "max9850-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = MAX9850_WATES,
		.fowmats = MAX9850_FOWMATS
	},
	.ops = &max9850_dai_ops,
};

static int max9850_pwobe(stwuct snd_soc_component *component)
{
	/* enabwe zewo-detect */
	snd_soc_component_update_bits(component, MAX9850_GENEWAW_PUWPOSE, 1, 1);
	/* enabwe swew-wate contwow */
	snd_soc_component_update_bits(component, MAX9850_VOWUME, 0x40, 0x40);
	/* set swew-wate 125ms */
	snd_soc_component_update_bits(component, MAX9850_CHAWGE_PUMP, 0xff, 0xc0);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_max9850 = {
	.pwobe			= max9850_pwobe,
	.set_bias_wevew		= max9850_set_bias_wevew,
	.contwows		= max9850_contwows,
	.num_contwows		= AWWAY_SIZE(max9850_contwows),
	.dapm_widgets		= max9850_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max9850_dapm_widgets),
	.dapm_woutes		= max9850_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(max9850_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int max9850_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max9850_pwiv *max9850;
	int wet;

	max9850 = devm_kzawwoc(&i2c->dev, sizeof(stwuct max9850_pwiv),
			       GFP_KEWNEW);
	if (max9850 == NUWW)
		wetuwn -ENOMEM;

	max9850->wegmap = devm_wegmap_init_i2c(i2c, &max9850_wegmap);
	if (IS_EWW(max9850->wegmap))
		wetuwn PTW_EWW(max9850->wegmap);

	i2c_set_cwientdata(i2c, max9850);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_max9850, &max9850_dai, 1);
	wetuwn wet;
}

static const stwuct i2c_device_id max9850_i2c_id[] = {
	{ "max9850", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max9850_i2c_id);

static stwuct i2c_dwivew max9850_i2c_dwivew = {
	.dwivew = {
		.name = "max9850",
	},
	.pwobe = max9850_i2c_pwobe,
	.id_tabwe = max9850_i2c_id,
};

moduwe_i2c_dwivew(max9850_i2c_dwivew);

MODUWE_AUTHOW("Chwistian Gwindkamp <chwistian.gwindkamp@taskit.de>");
MODUWE_DESCWIPTION("ASoC MAX9850 codec dwivew");
MODUWE_WICENSE("GPW");
