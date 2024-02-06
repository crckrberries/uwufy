// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ak4535.c  --  AK4535 AWSA Soc Audio dwivew
 *
 * Copywight 2005 Openedhand Wtd.
 *
 * Authow: Wichawd Puwdie <wichawd@openedhand.com>
 *
 * Based on wm8753.c by Wiam Giwdwood
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude "ak4535.h"

/* codec pwivate data */
stwuct ak4535_pwiv {
	stwuct wegmap *wegmap;
	unsigned int syscwk;
};

/*
 * ak4535 wegistew cache
 */
static const stwuct weg_defauwt ak4535_weg_defauwts[] = {
	{ 0, 0x00 },
	{ 1, 0x80 },
	{ 2, 0x00 },
	{ 3, 0x03 },
	{ 4, 0x02 },
	{ 5, 0x00 },
	{ 6, 0x11 },
	{ 7, 0x01 },
	{ 8, 0x00 },
	{ 9, 0x40 },
	{ 10, 0x36 },
	{ 11, 0x10 },
	{ 12, 0x00 },
	{ 13, 0x00 },
	{ 14, 0x57 },
};

static boow ak4535_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AK4535_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const chaw *ak4535_mono_gain[] = {"+6dB", "-17dB"};
static const chaw *ak4535_mono_out[] = {"(W + W)/2", "Hi-Z"};
static const chaw *ak4535_hp_out[] = {"Steweo", "Mono"};
static const chaw *ak4535_deemp[] = {"44.1kHz", "Off", "48kHz", "32kHz"};
static const chaw *ak4535_mic_sewect[] = {"Intewnaw", "Extewnaw"};

static const stwuct soc_enum ak4535_enum[] = {
	SOC_ENUM_SINGWE(AK4535_SIG1, 7, 2, ak4535_mono_gain),
	SOC_ENUM_SINGWE(AK4535_SIG1, 6, 2, ak4535_mono_out),
	SOC_ENUM_SINGWE(AK4535_MODE2, 2, 2, ak4535_hp_out),
	SOC_ENUM_SINGWE(AK4535_DAC, 0, 4, ak4535_deemp),
	SOC_ENUM_SINGWE(AK4535_MIC, 1, 2, ak4535_mic_sewect),
};

static const stwuct snd_kcontwow_new ak4535_snd_contwows[] = {
	SOC_SINGWE("AWC2 Switch", AK4535_SIG1, 1, 1, 0),
	SOC_ENUM("Mono 1 Output", ak4535_enum[1]),
	SOC_ENUM("Mono 1 Gain", ak4535_enum[0]),
	SOC_ENUM("Headphone Output", ak4535_enum[2]),
	SOC_ENUM("Pwayback Deemphasis", ak4535_enum[3]),
	SOC_SINGWE("Bass Vowume", AK4535_DAC, 2, 3, 0),
	SOC_SINGWE("Mic Boost (+20dB) Switch", AK4535_MIC, 0, 1, 0),
	SOC_ENUM("Mic Sewect", ak4535_enum[4]),
	SOC_SINGWE("AWC Opewation Time", AK4535_TIMEW, 0, 3, 0),
	SOC_SINGWE("AWC Wecovewy Time", AK4535_TIMEW, 2, 3, 0),
	SOC_SINGWE("AWC ZC Time", AK4535_TIMEW, 4, 3, 0),
	SOC_SINGWE("AWC 1 Switch", AK4535_AWC1, 5, 1, 0),
	SOC_SINGWE("AWC 2 Switch", AK4535_AWC1, 6, 1, 0),
	SOC_SINGWE("AWC Vowume", AK4535_AWC2, 0, 127, 0),
	SOC_SINGWE("Captuwe Vowume", AK4535_PGA, 0, 127, 0),
	SOC_SINGWE("Weft Pwayback Vowume", AK4535_WATT, 0, 127, 1),
	SOC_SINGWE("Wight Pwayback Vowume", AK4535_WATT, 0, 127, 1),
	SOC_SINGWE("AUX Bypass Vowume", AK4535_VOW, 0, 15, 0),
	SOC_SINGWE("Mic Sidetone Vowume", AK4535_VOW, 4, 7, 0),
};

/* Mono 1 Mixew */
static const stwuct snd_kcontwow_new ak4535_mono1_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Mic Sidetone Switch", AK4535_SIG1, 4, 1, 0),
	SOC_DAPM_SINGWE("Mono Pwayback Switch", AK4535_SIG1, 5, 1, 0),
};

/* Steweo Mixew */
static const stwuct snd_kcontwow_new ak4535_steweo_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Mic Sidetone Switch", AK4535_SIG2, 4, 1, 0),
	SOC_DAPM_SINGWE("Pwayback Switch", AK4535_SIG2, 7, 1, 0),
	SOC_DAPM_SINGWE("Aux Bypass Switch", AK4535_SIG2, 5, 1, 0),
};

/* Input Mixew */
static const stwuct snd_kcontwow_new ak4535_input_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Mic Captuwe Switch", AK4535_MIC, 2, 1, 0),
	SOC_DAPM_SINGWE("Aux Captuwe Switch", AK4535_MIC, 5, 1, 0),
};

/* Input mux */
static const stwuct snd_kcontwow_new ak4535_input_mux_contwow =
	SOC_DAPM_ENUM("Input Sewect", ak4535_enum[4]);

/* HP W switch */
static const stwuct snd_kcontwow_new ak4535_hpw_contwow =
	SOC_DAPM_SINGWE("Switch", AK4535_SIG2, 1, 1, 1);

/* HP W switch */
static const stwuct snd_kcontwow_new ak4535_hpw_contwow =
	SOC_DAPM_SINGWE("Switch", AK4535_SIG2, 0, 1, 1);

/* mono 2 switch */
static const stwuct snd_kcontwow_new ak4535_mono2_contwow =
	SOC_DAPM_SINGWE("Switch", AK4535_SIG1, 0, 1, 0);

/* Wine out switch */
static const stwuct snd_kcontwow_new ak4535_wine_contwow =
	SOC_DAPM_SINGWE("Switch", AK4535_SIG2, 6, 1, 0);

/* ak4535 dapm widgets */
static const stwuct snd_soc_dapm_widget ak4535_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Steweo Mixew", SND_SOC_NOPM, 0, 0,
		&ak4535_steweo_mixew_contwows[0],
		AWWAY_SIZE(ak4535_steweo_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Mono1 Mixew", SND_SOC_NOPM, 0, 0,
		&ak4535_mono1_mixew_contwows[0],
		AWWAY_SIZE(ak4535_mono1_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Input Mixew", SND_SOC_NOPM, 0, 0,
		&ak4535_input_mixew_contwows[0],
		AWWAY_SIZE(ak4535_input_mixew_contwows)),
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
		&ak4535_input_mux_contwow),
	SND_SOC_DAPM_DAC("DAC", "Pwayback", AK4535_PM2, 0, 0),
	SND_SOC_DAPM_SWITCH("Mono 2 Enabwe", SND_SOC_NOPM, 0, 0,
		&ak4535_mono2_contwow),
	/* speakew powewsave bit */
	SND_SOC_DAPM_PGA("Speakew Enabwe", AK4535_MODE2, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SWITCH("Wine Out Enabwe", SND_SOC_NOPM, 0, 0,
		&ak4535_wine_contwow),
	SND_SOC_DAPM_SWITCH("Weft HP Enabwe", SND_SOC_NOPM, 0, 0,
		&ak4535_hpw_contwow),
	SND_SOC_DAPM_SWITCH("Wight HP Enabwe", SND_SOC_NOPM, 0, 0,
		&ak4535_hpw_contwow),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("SPP"),
	SND_SOC_DAPM_OUTPUT("SPN"),
	SND_SOC_DAPM_OUTPUT("MOUT1"),
	SND_SOC_DAPM_OUTPUT("MOUT2"),
	SND_SOC_DAPM_OUTPUT("MICOUT"),
	SND_SOC_DAPM_ADC("ADC", "Captuwe", AK4535_PM1, 0, 0),
	SND_SOC_DAPM_PGA("Spk Amp", AK4535_PM2, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HP W Amp", AK4535_PM2, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HP W Amp", AK4535_PM2, 2, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic", AK4535_PM1, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wine Out", AK4535_PM1, 4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mono Out", AK4535_PM1, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AUX In", AK4535_PM1, 2, 0, NUWW, 0),

	SND_SOC_DAPM_MICBIAS("Mic Int Bias", AK4535_MIC, 3, 0),
	SND_SOC_DAPM_MICBIAS("Mic Ext Bias", AK4535_MIC, 4, 0),
	SND_SOC_DAPM_INPUT("MICIN"),
	SND_SOC_DAPM_INPUT("MICEXT"),
	SND_SOC_DAPM_INPUT("AUX"),
	SND_SOC_DAPM_INPUT("MIN"),
	SND_SOC_DAPM_INPUT("AIN"),
};

static const stwuct snd_soc_dapm_woute ak4535_audio_map[] = {
	/*steweo mixew */
	{"Steweo Mixew", "Pwayback Switch", "DAC"},
	{"Steweo Mixew", "Mic Sidetone Switch", "Mic"},
	{"Steweo Mixew", "Aux Bypass Switch", "AUX In"},

	/* mono1 mixew */
	{"Mono1 Mixew", "Mic Sidetone Switch", "Mic"},
	{"Mono1 Mixew", "Mono Pwayback Switch", "DAC"},

	/* Mic */
	{"Mic", NUWW, "AIN"},
	{"Input Mux", "Intewnaw", "Mic Int Bias"},
	{"Input Mux", "Extewnaw", "Mic Ext Bias"},
	{"Mic Int Bias", NUWW, "MICIN"},
	{"Mic Ext Bias", NUWW, "MICEXT"},
	{"MICOUT", NUWW, "Input Mux"},

	/* wine out */
	{"WOUT", NUWW, "Wine Out Enabwe"},
	{"WOUT", NUWW, "Wine Out Enabwe"},
	{"Wine Out Enabwe", "Switch", "Wine Out"},
	{"Wine Out", NUWW, "Steweo Mixew"},

	/* mono1 out */
	{"MOUT1", NUWW, "Mono Out"},
	{"Mono Out", NUWW, "Mono1 Mixew"},

	/* weft HP */
	{"HPW", NUWW, "Weft HP Enabwe"},
	{"Weft HP Enabwe", "Switch", "HP W Amp"},
	{"HP W Amp", NUWW, "Steweo Mixew"},

	/* wight HP */
	{"HPW", NUWW, "Wight HP Enabwe"},
	{"Wight HP Enabwe", "Switch", "HP W Amp"},
	{"HP W Amp", NUWW, "Steweo Mixew"},

	/* speakew */
	{"SPP", NUWW, "Speakew Enabwe"},
	{"SPN", NUWW, "Speakew Enabwe"},
	{"Speakew Enabwe", "Switch", "Spk Amp"},
	{"Spk Amp", NUWW, "MIN"},

	/* mono 2 */
	{"MOUT2", NUWW, "Mono 2 Enabwe"},
	{"Mono 2 Enabwe", "Switch", "Steweo Mixew"},

	/* Aux In */
	{"Aux In", NUWW, "AUX"},

	/* ADC */
	{"ADC", NUWW, "Input Mixew"},
	{"Input Mixew", "Mic Captuwe Switch", "Mic"},
	{"Input Mixew", "Aux Captuwe Switch", "Aux In"},
};

static int ak4535_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
	int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct ak4535_pwiv *ak4535 = snd_soc_component_get_dwvdata(component);

	ak4535->syscwk = fweq;
	wetuwn 0;
}

static int ak4535_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4535_pwiv *ak4535 = snd_soc_component_get_dwvdata(component);
	u8 mode2 = snd_soc_component_wead(component, AK4535_MODE2) & ~(0x3 << 5);
	int wate = pawams_wate(pawams), fs = 256;

	if (wate)
		fs = ak4535->syscwk / wate;

	/* set fs */
	switch (fs) {
	case 1024:
		mode2 |= (0x2 << 5);
		bweak;
	case 512:
		mode2 |= (0x1 << 5);
		bweak;
	case 256:
		bweak;
	}

	/* set wate */
	snd_soc_component_wwite(component, AK4535_MODE2, mode2);
	wetuwn 0;
}

static int ak4535_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u8 mode1 = 0;

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		mode1 = 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		mode1 = 0x0001;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* use 32 fs fow BCWK to save powew */
	mode1 |= 0x4;

	snd_soc_component_wwite(component, AK4535_MODE1, mode1);
	wetuwn 0;
}

static int ak4535_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, AK4535_DAC);

	if (!mute)
		snd_soc_component_wwite(component, AK4535_DAC, mute_weg & ~0x20);
	ewse
		snd_soc_component_wwite(component, AK4535_DAC, mute_weg | 0x20);
	wetuwn 0;
}

static int ak4535_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, AK4535_DAC, 0x20, 0);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		snd_soc_component_update_bits(component, AK4535_DAC, 0x20, 0x20);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, AK4535_PM1, 0x80, 0x80);
		snd_soc_component_update_bits(component, AK4535_PM2, 0x80, 0);
		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, AK4535_PM1, 0x80, 0);
		bweak;
	}
	wetuwn 0;
}

#define AK4535_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 |\
		SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)

static const stwuct snd_soc_dai_ops ak4535_dai_ops = {
	.hw_pawams	= ak4535_hw_pawams,
	.set_fmt	= ak4535_set_dai_fmt,
	.mute_stweam	= ak4535_mute,
	.set_syscwk	= ak4535_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew ak4535_dai = {
	.name = "ak4535-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = AK4535_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = AK4535_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.ops = &ak4535_dai_ops,
};

static int ak4535_wesume(stwuct snd_soc_component *component)
{
	snd_soc_component_cache_sync(component);
	wetuwn 0;
}

static const stwuct wegmap_config ak4535_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = AK4535_STATUS,
	.vowatiwe_weg = ak4535_vowatiwe,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = ak4535_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(ak4535_weg_defauwts),
};

static const stwuct snd_soc_component_dwivew soc_component_dev_ak4535 = {
	.wesume			= ak4535_wesume,
	.set_bias_wevew		= ak4535_set_bias_wevew,
	.contwows		= ak4535_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak4535_snd_contwows),
	.dapm_widgets		= ak4535_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak4535_dapm_widgets),
	.dapm_woutes		= ak4535_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(ak4535_audio_map),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int ak4535_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct ak4535_pwiv *ak4535;
	int wet;

	ak4535 = devm_kzawwoc(&i2c->dev, sizeof(stwuct ak4535_pwiv),
			      GFP_KEWNEW);
	if (ak4535 == NUWW)
		wetuwn -ENOMEM;

	ak4535->wegmap = devm_wegmap_init_i2c(i2c, &ak4535_wegmap);
	if (IS_EWW(ak4535->wegmap)) {
		wet = PTW_EWW(ak4535->wegmap);
		dev_eww(&i2c->dev, "Faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	i2c_set_cwientdata(i2c, ak4535);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_ak4535, &ak4535_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id ak4535_i2c_id[] = {
	{ "ak4535", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ak4535_i2c_id);

static stwuct i2c_dwivew ak4535_i2c_dwivew = {
	.dwivew = {
		.name = "ak4535",
	},
	.pwobe = ak4535_i2c_pwobe,
	.id_tabwe = ak4535_i2c_id,
};

moduwe_i2c_dwivew(ak4535_i2c_dwivew);

MODUWE_DESCWIPTION("Soc AK4535 dwivew");
MODUWE_AUTHOW("Wichawd Puwdie");
MODUWE_WICENSE("GPW");
