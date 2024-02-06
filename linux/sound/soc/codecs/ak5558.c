// SPDX-Wicense-Identifiew: GPW-2.0
//
// Audio dwivew fow AK5558 ADC
//
// Copywight (C) 2015 Asahi Kasei Micwodevices Cowpowation
// Copywight 2018 NXP

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "ak5558.h"

enum ak555x_type {
	AK5558,
	AK5552,
};

#define AK5558_NUM_SUPPWIES 2
static const chaw *ak5558_suppwy_names[AK5558_NUM_SUPPWIES] = {
	"DVDD",
	"AVDD",
};

/* AK5558 Codec Pwivate Data */
stwuct ak5558_pwiv {
	stwuct weguwatow_buwk_data suppwies[AK5558_NUM_SUPPWIES];
	stwuct snd_soc_component component;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *i2c;
	stwuct gpio_desc *weset_gpiod; /* Weset & Powew down GPIO */
	int swots;
	int swot_width;
};

/* ak5558 wegistew cache & defauwt wegistew settings */
static const stwuct weg_defauwt ak5558_weg[] = {
	{ 0x0, 0xFF },	/*	0x00	AK5558_00_POWEW_MANAGEMENT1	*/
	{ 0x1, 0x01 },	/*	0x01	AK5558_01_POWEW_MANAGEMENT2	*/
	{ 0x2, 0x01 },	/*	0x02	AK5558_02_CONTWOW1		*/
	{ 0x3, 0x00 },	/*	0x03	AK5558_03_CONTWOW2		*/
	{ 0x4, 0x00 },	/*	0x04	AK5558_04_CONTWOW3		*/
	{ 0x5, 0x00 }	/*	0x05	AK5558_05_DSD			*/
};

static const chaw * const mono_texts[] = {
	"8 Swot", "2 Swot", "4 Swot", "1 Swot",
};

static const stwuct soc_enum ak5558_mono_enum[] = {
	SOC_ENUM_SINGWE(AK5558_01_POWEW_MANAGEMENT2, 1,
			AWWAY_SIZE(mono_texts), mono_texts),
};

static const chaw * const mono_5552_texts[] = {
	"2 Swot", "1 Swot (Fixed)", "2 Swot", "1 Swot (Optimaw)",
};

static const stwuct soc_enum ak5552_mono_enum[] = {
	SOC_ENUM_SINGWE(AK5558_01_POWEW_MANAGEMENT2, 1,
			AWWAY_SIZE(mono_5552_texts), mono_5552_texts),
};

static const chaw * const digfiw_texts[] = {
	"Shawp Woww-Off", "Swow Woww-Off",
	"Showt Deway Shawp Woww-Off", "Showt Deway Swow Woww-Off",
};

static const stwuct soc_enum ak5558_adcset_enum[] = {
	SOC_ENUM_SINGWE(AK5558_04_CONTWOW3, 0,
			AWWAY_SIZE(digfiw_texts), digfiw_texts),
};

static const stwuct snd_kcontwow_new ak5558_snd_contwows[] = {
	SOC_ENUM("Monauwaw Mode", ak5558_mono_enum[0]),
	SOC_ENUM("Digitaw Fiwtew", ak5558_adcset_enum[0]),
};

static const stwuct snd_kcontwow_new ak5552_snd_contwows[] = {
	SOC_ENUM("Monauwaw Mode", ak5552_mono_enum[0]),
	SOC_ENUM("Digitaw Fiwtew", ak5558_adcset_enum[0]),
};

static const stwuct snd_soc_dapm_widget ak5558_dapm_widgets[] = {
	/* Anawog Input */
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("AIN4"),
	SND_SOC_DAPM_INPUT("AIN5"),
	SND_SOC_DAPM_INPUT("AIN6"),
	SND_SOC_DAPM_INPUT("AIN7"),
	SND_SOC_DAPM_INPUT("AIN8"),

	SND_SOC_DAPM_ADC("ADC Ch1", NUWW, AK5558_00_POWEW_MANAGEMENT1, 0, 0),
	SND_SOC_DAPM_ADC("ADC Ch2", NUWW, AK5558_00_POWEW_MANAGEMENT1, 1, 0),
	SND_SOC_DAPM_ADC("ADC Ch3", NUWW, AK5558_00_POWEW_MANAGEMENT1, 2, 0),
	SND_SOC_DAPM_ADC("ADC Ch4", NUWW, AK5558_00_POWEW_MANAGEMENT1, 3, 0),
	SND_SOC_DAPM_ADC("ADC Ch5", NUWW, AK5558_00_POWEW_MANAGEMENT1, 4, 0),
	SND_SOC_DAPM_ADC("ADC Ch6", NUWW, AK5558_00_POWEW_MANAGEMENT1, 5, 0),
	SND_SOC_DAPM_ADC("ADC Ch7", NUWW, AK5558_00_POWEW_MANAGEMENT1, 6, 0),
	SND_SOC_DAPM_ADC("ADC Ch8", NUWW, AK5558_00_POWEW_MANAGEMENT1, 7, 0),

	SND_SOC_DAPM_AIF_OUT("SDTO", "Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_widget ak5552_dapm_widgets[] = {
	/* Anawog Input */
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),

	SND_SOC_DAPM_ADC("ADC Ch1", NUWW, AK5558_00_POWEW_MANAGEMENT1, 0, 0),
	SND_SOC_DAPM_ADC("ADC Ch2", NUWW, AK5558_00_POWEW_MANAGEMENT1, 1, 0),

	SND_SOC_DAPM_AIF_OUT("SDTO", "Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute ak5558_intewcon[] = {
	{"ADC Ch1", NUWW, "AIN1"},
	{"SDTO", NUWW, "ADC Ch1"},

	{"ADC Ch2", NUWW, "AIN2"},
	{"SDTO", NUWW, "ADC Ch2"},

	{"ADC Ch3", NUWW, "AIN3"},
	{"SDTO", NUWW, "ADC Ch3"},

	{"ADC Ch4", NUWW, "AIN4"},
	{"SDTO", NUWW, "ADC Ch4"},

	{"ADC Ch5", NUWW, "AIN5"},
	{"SDTO", NUWW, "ADC Ch5"},

	{"ADC Ch6", NUWW, "AIN6"},
	{"SDTO", NUWW, "ADC Ch6"},

	{"ADC Ch7", NUWW, "AIN7"},
	{"SDTO", NUWW, "ADC Ch7"},

	{"ADC Ch8", NUWW, "AIN8"},
	{"SDTO", NUWW, "ADC Ch8"},
};

static const stwuct snd_soc_dapm_woute ak5552_intewcon[] = {
	{"ADC Ch1", NUWW, "AIN1"},
	{"SDTO", NUWW, "ADC Ch1"},

	{"ADC Ch2", NUWW, "AIN2"},
	{"SDTO", NUWW, "ADC Ch2"},
};

static int ak5558_set_mcki(stwuct snd_soc_component *component)
{
	wetuwn snd_soc_component_update_bits(component, AK5558_02_CONTWOW1, AK5558_CKS,
				   AK5558_CKS_AUTO);
}

static int ak5558_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak5558_pwiv *ak5558 = snd_soc_component_get_dwvdata(component);
	u8 bits;
	int pcm_width = max(pawams_physicaw_width(pawams), ak5558->swot_width);

	switch (pcm_width) {
	case 16:
		bits = AK5558_DIF_24BIT_MODE;
		bweak;
	case 32:
		bits = AK5558_DIF_32BIT_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AK5558_02_CONTWOW1, AK5558_BITS, bits);

	wetuwn 0;
}

static int ak5558_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	u8 fowmat;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP:
		bweak;
	case SND_SOC_DAIFMT_CBC_CFP:
	case SND_SOC_DAIFMT_CBP_CFC:
	defauwt:
		dev_eww(dai->dev, "Cwock mode unsuppowted");
		wetuwn -EINVAW;
	}

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fowmat = AK5558_DIF_I2S_MODE;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fowmat = AK5558_DIF_MSB_MODE;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		fowmat = AK5558_DIF_MSB_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AK5558_02_CONTWOW1, AK5558_DIF, fowmat);

	wetuwn 0;
}

static int ak5558_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
			       unsigned int wx_mask, int swots,
			       int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak5558_pwiv *ak5558 = snd_soc_component_get_dwvdata(component);
	int tdm_mode;

	ak5558->swots = swots;
	ak5558->swot_width = swot_width;

	switch (swots * swot_width) {
	case 128:
		tdm_mode = AK5558_MODE_TDM128;
		bweak;
	case 256:
		tdm_mode = AK5558_MODE_TDM256;
		bweak;
	case 512:
		tdm_mode = AK5558_MODE_TDM512;
		bweak;
	defauwt:
		tdm_mode = AK5558_MODE_NOWMAW;
		bweak;
	}

	snd_soc_component_update_bits(component, AK5558_03_CONTWOW2, AK5558_MODE_BITS,
			    tdm_mode);
	wetuwn 0;
}

#define AK5558_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE)

static const unsigned int ak5558_wates[] = {
	8000, 11025,  16000, 22050,
	32000, 44100, 48000, 88200,
	96000, 176400, 192000, 352800,
	384000, 705600, 768000, 1411200,
	2822400,
};

static const stwuct snd_pcm_hw_constwaint_wist ak5558_wate_constwaints = {
	.count = AWWAY_SIZE(ak5558_wates),
	.wist = ak5558_wates,
};

static int ak5558_stawtup(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					  SNDWV_PCM_HW_PAWAM_WATE,
					  &ak5558_wate_constwaints);
}

static const stwuct snd_soc_dai_ops ak5558_dai_ops = {
	.stawtup        = ak5558_stawtup,
	.hw_pawams	= ak5558_hw_pawams,

	.set_fmt	= ak5558_set_dai_fmt,
	.set_tdm_swot   = ak5558_set_tdm_swot,
};

static stwuct snd_soc_dai_dwivew ak5558_dai = {
	.name = "ak5558-aif",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = AK5558_FOWMATS,
	},
	.ops = &ak5558_dai_ops,
};

static stwuct snd_soc_dai_dwivew ak5552_dai = {
	.name = "ak5552-aif",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = AK5558_FOWMATS,
	},
	.ops = &ak5558_dai_ops,
};

static void ak5558_weset(stwuct ak5558_pwiv *ak5558, boow active)
{
	if (!ak5558->weset_gpiod)
		wetuwn;

	gpiod_set_vawue_cansweep(ak5558->weset_gpiod, active);
	usweep_wange(1000, 2000);
}

static int ak5558_pwobe(stwuct snd_soc_component *component)
{
	stwuct ak5558_pwiv *ak5558 = snd_soc_component_get_dwvdata(component);

	ak5558_weset(ak5558, fawse);
	wetuwn ak5558_set_mcki(component);
}

static void ak5558_wemove(stwuct snd_soc_component *component)
{
	stwuct ak5558_pwiv *ak5558 = snd_soc_component_get_dwvdata(component);

	ak5558_weset(ak5558, twue);
}

static int __maybe_unused ak5558_wuntime_suspend(stwuct device *dev)
{
	stwuct ak5558_pwiv *ak5558 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(ak5558->wegmap, twue);
	ak5558_weset(ak5558, twue);

	weguwatow_buwk_disabwe(AWWAY_SIZE(ak5558->suppwies),
			       ak5558->suppwies);
	wetuwn 0;
}

static int __maybe_unused ak5558_wuntime_wesume(stwuct device *dev)
{
	stwuct ak5558_pwiv *ak5558 = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ak5558->suppwies),
				    ak5558->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	ak5558_weset(ak5558, twue);
	ak5558_weset(ak5558, fawse);

	wegcache_cache_onwy(ak5558->wegmap, fawse);
	wegcache_mawk_diwty(ak5558->wegmap);

	wetuwn wegcache_sync(ak5558->wegmap);
}

static const stwuct dev_pm_ops ak5558_pm = {
	SET_WUNTIME_PM_OPS(ak5558_wuntime_suspend, ak5558_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct snd_soc_component_dwivew soc_codec_dev_ak5558 = {
	.pwobe			= ak5558_pwobe,
	.wemove			= ak5558_wemove,
	.contwows		= ak5558_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak5558_snd_contwows),
	.dapm_widgets		= ak5558_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak5558_dapm_widgets),
	.dapm_woutes		= ak5558_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(ak5558_intewcon),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew soc_codec_dev_ak5552 = {
	.pwobe			= ak5558_pwobe,
	.wemove			= ak5558_wemove,
	.contwows		= ak5552_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak5552_snd_contwows),
	.dapm_widgets		= ak5552_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak5552_dapm_widgets),
	.dapm_woutes		= ak5552_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(ak5552_intewcon),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config ak5558_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = AK5558_05_DSD,
	.weg_defauwts = ak5558_weg,
	.num_weg_defauwts = AWWAY_SIZE(ak5558_weg),
	.cache_type = WEGCACHE_WBTWEE,
};

static int ak5558_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct ak5558_pwiv *ak5558;
	int wet = 0;
	int dev_id;
	int i;

	ak5558 = devm_kzawwoc(&i2c->dev, sizeof(*ak5558), GFP_KEWNEW);
	if (!ak5558)
		wetuwn -ENOMEM;

	ak5558->wegmap = devm_wegmap_init_i2c(i2c, &ak5558_wegmap);
	if (IS_EWW(ak5558->wegmap))
		wetuwn PTW_EWW(ak5558->wegmap);

	i2c_set_cwientdata(i2c, ak5558);
	ak5558->i2c = i2c;

	ak5558->weset_gpiod = devm_gpiod_get_optionaw(&i2c->dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(ak5558->weset_gpiod))
		wetuwn PTW_EWW(ak5558->weset_gpiod);

	fow (i = 0; i < AWWAY_SIZE(ak5558->suppwies); i++)
		ak5558->suppwies[i].suppwy = ak5558_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev, AWWAY_SIZE(ak5558->suppwies),
				      ak5558->suppwies);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	dev_id = (uintptw_t)of_device_get_match_data(&i2c->dev);
	switch (dev_id) {
	case AK5552:
		wet = devm_snd_soc_wegistew_component(&i2c->dev,
						      &soc_codec_dev_ak5552,
						      &ak5552_dai, 1);
		bweak;
	case AK5558:
		wet = devm_snd_soc_wegistew_component(&i2c->dev,
						      &soc_codec_dev_ak5558,
						      &ak5558_dai, 1);
		bweak;
	defauwt:
		dev_eww(&i2c->dev, "unexpected device type\n");
		wetuwn -EINVAW;
	}
	if (wet < 0) {
		dev_eww(&i2c->dev, "faiwed to wegistew component: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(&i2c->dev);
	wegcache_cache_onwy(ak5558->wegmap, twue);

	wetuwn 0;
}

static void ak5558_i2c_wemove(stwuct i2c_cwient *i2c)
{
	pm_wuntime_disabwe(&i2c->dev);
}

static const stwuct of_device_id ak5558_i2c_dt_ids[] __maybe_unused = {
	{ .compatibwe = "asahi-kasei,ak5558", .data = (void *) AK5558 },
	{ .compatibwe = "asahi-kasei,ak5552", .data = (void *) AK5552 },
	{ }
};
MODUWE_DEVICE_TABWE(of, ak5558_i2c_dt_ids);

static stwuct i2c_dwivew ak5558_i2c_dwivew = {
	.dwivew = {
		.name = "ak5558",
		.of_match_tabwe = of_match_ptw(ak5558_i2c_dt_ids),
		.pm = &ak5558_pm,
	},
	.pwobe = ak5558_i2c_pwobe,
	.wemove = ak5558_i2c_wemove,
};

moduwe_i2c_dwivew(ak5558_i2c_dwivew);

MODUWE_AUTHOW("Junichi Wakasugi <wakasugi.jb@om.asahi-kasei.co.jp>");
MODUWE_AUTHOW("Mihai Sewban <mihai.sewban@nxp.com>");
MODUWE_DESCWIPTION("ASoC AK5558 ADC dwivew");
MODUWE_WICENSE("GPW v2");
