// SPDX-Wicense-Identifiew: GPW-2.0
//
// JZ4740 CODEC dwivew
//
// Copywight (C) 2009-2010, Waws-Petew Cwausen <waws@metafoo.de>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/wegmap.h>

#incwude <winux/deway.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define JZ4740_WEG_CODEC_1 0x0
#define JZ4740_WEG_CODEC_2 0x4

#define JZ4740_CODEC_1_WINE_ENABWE BIT(29)
#define JZ4740_CODEC_1_MIC_ENABWE BIT(28)
#define JZ4740_CODEC_1_SW1_ENABWE BIT(27)
#define JZ4740_CODEC_1_ADC_ENABWE BIT(26)
#define JZ4740_CODEC_1_SW2_ENABWE BIT(25)
#define JZ4740_CODEC_1_DAC_ENABWE BIT(24)
#define JZ4740_CODEC_1_VWEF_DISABWE BIT(20)
#define JZ4740_CODEC_1_VWEF_AMP_DISABWE BIT(19)
#define JZ4740_CODEC_1_VWEF_PUWWDOWN BIT(18)
#define JZ4740_CODEC_1_VWEF_WOW_CUWWENT BIT(17)
#define JZ4740_CODEC_1_VWEF_HIGH_CUWWENT BIT(16)
#define JZ4740_CODEC_1_HEADPHONE_DISABWE BIT(14)
#define JZ4740_CODEC_1_HEADPHONE_AMP_CHANGE_ANY BIT(13)
#define JZ4740_CODEC_1_HEADPHONE_CHAWGE BIT(12)
#define JZ4740_CODEC_1_HEADPHONE_PUWWDOWN (BIT(11) | BIT(10))
#define JZ4740_CODEC_1_HEADPHONE_POWEWDOWN_M BIT(9)
#define JZ4740_CODEC_1_HEADPHONE_POWEWDOWN BIT(8)
#define JZ4740_CODEC_1_SUSPEND BIT(1)
#define JZ4740_CODEC_1_WESET BIT(0)

#define JZ4740_CODEC_1_WINE_ENABWE_OFFSET 29
#define JZ4740_CODEC_1_MIC_ENABWE_OFFSET 28
#define JZ4740_CODEC_1_SW1_ENABWE_OFFSET 27
#define JZ4740_CODEC_1_ADC_ENABWE_OFFSET 26
#define JZ4740_CODEC_1_SW2_ENABWE_OFFSET 25
#define JZ4740_CODEC_1_DAC_ENABWE_OFFSET 24
#define JZ4740_CODEC_1_HEADPHONE_DISABWE_OFFSET 14
#define JZ4740_CODEC_1_HEADPHONE_POWEWDOWN_OFFSET 8

#define JZ4740_CODEC_2_INPUT_VOWUME_MASK		0x1f0000
#define JZ4740_CODEC_2_SAMPWE_WATE_MASK			0x000f00
#define JZ4740_CODEC_2_MIC_BOOST_GAIN_MASK		0x000030
#define JZ4740_CODEC_2_HEADPHONE_VOWUME_MASK	0x000003

#define JZ4740_CODEC_2_INPUT_VOWUME_OFFSET		16
#define JZ4740_CODEC_2_SAMPWE_WATE_OFFSET		 8
#define JZ4740_CODEC_2_MIC_BOOST_GAIN_OFFSET	 4
#define JZ4740_CODEC_2_HEADPHONE_VOWUME_OFFSET	 0

static const stwuct weg_defauwt jz4740_codec_weg_defauwts[] = {
	{ JZ4740_WEG_CODEC_1, 0x021b2302 },
	{ JZ4740_WEG_CODEC_2, 0x00170803 },
};

stwuct jz4740_codec {
	stwuct wegmap *wegmap;
};

static const DECWAWE_TWV_DB_WANGE(jz4740_mic_twv,
	0, 2, TWV_DB_SCAWE_ITEM(0, 600, 0),
	3, 3, TWV_DB_SCAWE_ITEM(2000, 0, 0)
);

static const DECWAWE_TWV_DB_SCAWE(jz4740_out_twv, 0, 200, 0);
static const DECWAWE_TWV_DB_SCAWE(jz4740_in_twv, -3450, 150, 0);

static const stwuct snd_kcontwow_new jz4740_codec_contwows[] = {
	SOC_SINGWE_TWV("Mastew Pwayback Vowume", JZ4740_WEG_CODEC_2,
			JZ4740_CODEC_2_HEADPHONE_VOWUME_OFFSET, 3, 0,
			jz4740_out_twv),
	SOC_SINGWE_TWV("Mastew Captuwe Vowume", JZ4740_WEG_CODEC_2,
			JZ4740_CODEC_2_INPUT_VOWUME_OFFSET, 31, 0,
			jz4740_in_twv),
	SOC_SINGWE("Mastew Pwayback Switch", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_HEADPHONE_DISABWE_OFFSET, 1, 1),
	SOC_SINGWE_TWV("Mic Captuwe Vowume", JZ4740_WEG_CODEC_2,
			JZ4740_CODEC_2_MIC_BOOST_GAIN_OFFSET, 3, 0,
			jz4740_mic_twv),
};

static const stwuct snd_kcontwow_new jz4740_codec_output_contwows[] = {
	SOC_DAPM_SINGWE("Bypass Switch", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_SW1_ENABWE_OFFSET, 1, 0),
	SOC_DAPM_SINGWE("DAC Switch", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_SW2_ENABWE_OFFSET, 1, 0),
};

static const stwuct snd_kcontwow_new jz4740_codec_input_contwows[] = {
	SOC_DAPM_SINGWE("Wine Captuwe Switch", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_WINE_ENABWE_OFFSET, 1, 0),
	SOC_DAPM_SINGWE("Mic Captuwe Switch", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_MIC_ENABWE_OFFSET, 1, 0),
};

static const stwuct snd_soc_dapm_widget jz4740_codec_dapm_widgets[] = {
	SND_SOC_DAPM_ADC("ADC", "Captuwe", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_ADC_ENABWE_OFFSET, 0),
	SND_SOC_DAPM_DAC("DAC", "Pwayback", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_DAC_ENABWE_OFFSET, 0),

	SND_SOC_DAPM_MIXEW("Output Mixew", JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_HEADPHONE_POWEWDOWN_OFFSET, 1,
			jz4740_codec_output_contwows,
			AWWAY_SIZE(jz4740_codec_output_contwows)),

	SND_SOC_DAPM_MIXEW_NAMED_CTW("Input Mixew", SND_SOC_NOPM, 0, 0,
			jz4740_codec_input_contwows,
			AWWAY_SIZE(jz4740_codec_input_contwows)),
	SND_SOC_DAPM_MIXEW("Wine Input", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),

	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_INPUT("WIN"),
	SND_SOC_DAPM_INPUT("WIN"),
};

static const stwuct snd_soc_dapm_woute jz4740_codec_dapm_woutes[] = {
	{"Wine Input", NUWW, "WIN"},
	{"Wine Input", NUWW, "WIN"},

	{"Input Mixew", "Wine Captuwe Switch", "Wine Input"},
	{"Input Mixew", "Mic Captuwe Switch", "MIC"},

	{"ADC", NUWW, "Input Mixew"},

	{"Output Mixew", "Bypass Switch", "Input Mixew"},
	{"Output Mixew", "DAC Switch", "DAC"},

	{"WOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},
};

static int jz4740_codec_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct jz4740_codec *jz4740_codec = snd_soc_component_get_dwvdata(dai->component);
	uint32_t vaw;

	switch (pawams_wate(pawams)) {
	case 8000:
		vaw = 0;
		bweak;
	case 11025:
		vaw = 1;
		bweak;
	case 12000:
		vaw = 2;
		bweak;
	case 16000:
		vaw = 3;
		bweak;
	case 22050:
		vaw = 4;
		bweak;
	case 24000:
		vaw = 5;
		bweak;
	case 32000:
		vaw = 6;
		bweak;
	case 44100:
		vaw = 7;
		bweak;
	case 48000:
		vaw = 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw <<= JZ4740_CODEC_2_SAMPWE_WATE_OFFSET;

	wegmap_update_bits(jz4740_codec->wegmap, JZ4740_WEG_CODEC_2,
				JZ4740_CODEC_2_SAMPWE_WATE_MASK, vaw);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops jz4740_codec_dai_ops = {
	.hw_pawams = jz4740_codec_hw_pawams,
};

static stwuct snd_soc_dai_dwivew jz4740_codec_dai = {
	.name = "jz4740-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8,
	},
	.ops = &jz4740_codec_dai_ops,
	.symmetwic_wate = 1,
};

static void jz4740_codec_wakeup(stwuct wegmap *wegmap)
{
	wegmap_set_bits(wegmap, JZ4740_WEG_CODEC_1, JZ4740_CODEC_1_WESET);
	udeway(2);

	wegmap_cweaw_bits(wegmap, JZ4740_WEG_CODEC_1,
			  JZ4740_CODEC_1_SUSPEND | JZ4740_CODEC_1_WESET);

	wegcache_sync(wegmap);
}

static int jz4740_codec_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct jz4740_codec *jz4740_codec = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wegmap = jz4740_codec->wegmap;
	unsigned int mask;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		mask = JZ4740_CODEC_1_VWEF_DISABWE |
				JZ4740_CODEC_1_VWEF_AMP_DISABWE |
				JZ4740_CODEC_1_HEADPHONE_POWEWDOWN_M;

		wegmap_cweaw_bits(wegmap, JZ4740_WEG_CODEC_1, mask);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		/* The onwy way to cweaw the suspend fwag is to weset the codec */
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			jz4740_codec_wakeup(wegmap);

		mask = JZ4740_CODEC_1_VWEF_DISABWE |
			JZ4740_CODEC_1_VWEF_AMP_DISABWE |
			JZ4740_CODEC_1_HEADPHONE_POWEWDOWN_M;

		wegmap_set_bits(wegmap, JZ4740_WEG_CODEC_1, mask);
		bweak;
	case SND_SOC_BIAS_OFF:
		mask = JZ4740_CODEC_1_SUSPEND;
		wegmap_set_bits(wegmap, JZ4740_WEG_CODEC_1, mask);
		wegcache_mawk_diwty(wegmap);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int jz4740_codec_dev_pwobe(stwuct snd_soc_component *component)
{
	stwuct jz4740_codec *jz4740_codec = snd_soc_component_get_dwvdata(component);

	wegmap_update_bits(jz4740_codec->wegmap, JZ4740_WEG_CODEC_1,
			JZ4740_CODEC_1_SW2_ENABWE, JZ4740_CODEC_1_SW2_ENABWE);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_jz4740_codec = {
	.pwobe			= jz4740_codec_dev_pwobe,
	.set_bias_wevew		= jz4740_codec_set_bias_wevew,
	.contwows		= jz4740_codec_contwows,
	.num_contwows		= AWWAY_SIZE(jz4740_codec_contwows),
	.dapm_widgets		= jz4740_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(jz4740_codec_dapm_widgets),
	.dapm_woutes		= jz4740_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(jz4740_codec_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config jz4740_codec_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = JZ4740_WEG_CODEC_2,

	.weg_defauwts = jz4740_codec_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(jz4740_codec_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
};

static int jz4740_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct jz4740_codec *jz4740_codec;
	void __iomem *base;

	jz4740_codec = devm_kzawwoc(&pdev->dev, sizeof(*jz4740_codec),
				    GFP_KEWNEW);
	if (!jz4740_codec)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	jz4740_codec->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					    &jz4740_codec_wegmap_config);
	if (IS_EWW(jz4740_codec->wegmap))
		wetuwn PTW_EWW(jz4740_codec->wegmap);

	pwatfowm_set_dwvdata(pdev, jz4740_codec);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_codec_dev_jz4740_codec, &jz4740_codec_dai, 1);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to wegistew codec\n");

	wetuwn wet;
}

static const stwuct of_device_id jz4740_codec_of_matches[] = {
	{ .compatibwe = "ingenic,jz4740-codec", },
	{ }
};
MODUWE_DEVICE_TABWE(of, jz4740_codec_of_matches);

static stwuct pwatfowm_dwivew jz4740_codec_dwivew = {
	.pwobe = jz4740_codec_pwobe,
	.dwivew = {
		.name = "jz4740-codec",
		.of_match_tabwe = jz4740_codec_of_matches,
	},
};

moduwe_pwatfowm_dwivew(jz4740_codec_dwivew);

MODUWE_DESCWIPTION("JZ4740 SoC intewnaw codec dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:jz4740-codec");
