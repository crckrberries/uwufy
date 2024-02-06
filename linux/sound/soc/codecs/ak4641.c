// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ak4641.c  --  AK4641 AWSA Soc Audio dwivew
 *
 * Copywight (C) 2008 Hawawd Wewte <wafowge@gnufiish.owg>
 * Copywight (C) 2011 Dmitwy Awtamonow <mad_soft@inbox.wu>
 *
 * Based on ak4535.c by Wichawd Puwdie
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/ak4641.h>

/* AK4641 wegistew space */
#define AK4641_PM1		0x00
#define AK4641_PM2		0x01
#define AK4641_SIG1		0x02
#define AK4641_SIG2		0x03
#define AK4641_MODE1		0x04
#define AK4641_MODE2		0x05
#define AK4641_DAC		0x06
#define AK4641_MIC		0x07
#define AK4641_TIMEW		0x08
#define AK4641_AWC1		0x09
#define AK4641_AWC2		0x0a
#define AK4641_PGA		0x0b
#define AK4641_WATT		0x0c
#define AK4641_WATT		0x0d
#define AK4641_VOW		0x0e
#define AK4641_STATUS		0x0f
#define AK4641_EQWO		0x10
#define AK4641_EQMID		0x11
#define AK4641_EQHI		0x12
#define AK4641_BTIF		0x13

/* codec pwivate data */
stwuct ak4641_pwiv {
	stwuct wegmap *wegmap;
	unsigned int syscwk;
	int deemph;
	int pwayback_fs;
};

/*
 * ak4641 wegistew cache
 */
static const stwuct weg_defauwt ak4641_weg_defauwts[] = {
	{  0, 0x00 }, {  1, 0x80 }, {  2, 0x00 }, {  3, 0x80 },
	{  4, 0x02 }, {  5, 0x00 }, {  6, 0x11 }, {  7, 0x05 },
	{  8, 0x00 }, {  9, 0x00 }, { 10, 0x36 }, { 11, 0x10 },
	{ 12, 0x00 }, { 13, 0x00 }, { 14, 0x57 }, { 15, 0x00 },
	{ 16, 0x88 }, { 17, 0x88 }, { 18, 0x08 }, { 19, 0x08 }
};

static const int deemph_settings[] = {44100, 0, 48000, 32000};

static int ak4641_set_deemph(stwuct snd_soc_component *component)
{
	stwuct ak4641_pwiv *ak4641 = snd_soc_component_get_dwvdata(component);
	int i, best = 0;

	fow (i = 0 ; i < AWWAY_SIZE(deemph_settings); i++) {
		/* if deemphasis is on, sewect the neawest avaiwabwe wate */
		if (ak4641->deemph && deemph_settings[i] != 0 &&
		    abs(deemph_settings[i] - ak4641->pwayback_fs) <
		    abs(deemph_settings[best] - ak4641->pwayback_fs))
			best = i;

		if (!ak4641->deemph && deemph_settings[i] == 0)
			best = i;
	}

	dev_dbg(component->dev, "Set deemphasis %d\n", best);

	wetuwn snd_soc_component_update_bits(component, AK4641_DAC, 0x3, best);
}

static int ak4641_put_deemph(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ak4641_pwiv *ak4641 = snd_soc_component_get_dwvdata(component);
	int deemph = ucontwow->vawue.integew.vawue[0];

	if (deemph > 1)
		wetuwn -EINVAW;

	ak4641->deemph = deemph;

	wetuwn ak4641_set_deemph(component);
}

static int ak4641_get_deemph(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ak4641_pwiv *ak4641 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = ak4641->deemph;
	wetuwn 0;
};

static const chaw *ak4641_mono_out[] = {"(W + W)/2", "Hi-Z"};
static const chaw *ak4641_hp_out[] = {"Steweo", "Mono"};
static const chaw *ak4641_mic_sewect[] = {"Intewnaw", "Extewnaw"};
static const chaw *ak4641_mic_ow_dac[] = {"Micwophone", "Voice DAC"};


static const DECWAWE_TWV_DB_SCAWE(mono_gain_twv, -1700, 2300, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_boost_twv, 0, 2000, 0);
static const DECWAWE_TWV_DB_SCAWE(eq_twv, -1050, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(mastew_twv, -12750, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_steweo_sidetone_twv, -2700, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_mono_sidetone_twv, -400, 400, 0);
static const DECWAWE_TWV_DB_SCAWE(captuwe_twv, -800, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_twv, -800, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(aux_in_twv, -2100, 300, 0);


static SOC_ENUM_SINGWE_DECW(ak4641_mono_out_enum,
			    AK4641_SIG1, 6, ak4641_mono_out);
static SOC_ENUM_SINGWE_DECW(ak4641_hp_out_enum,
			    AK4641_MODE2, 2, ak4641_hp_out);
static SOC_ENUM_SINGWE_DECW(ak4641_mic_sewect_enum,
			    AK4641_MIC, 1, ak4641_mic_sewect);
static SOC_ENUM_SINGWE_DECW(ak4641_mic_ow_dac_enum,
			    AK4641_BTIF, 4, ak4641_mic_ow_dac);

static const stwuct snd_kcontwow_new ak4641_snd_contwows[] = {
	SOC_ENUM("Mono 1 Output", ak4641_mono_out_enum),
	SOC_SINGWE_TWV("Mono 1 Gain Vowume", AK4641_SIG1, 7, 1, 1,
							mono_gain_twv),
	SOC_ENUM("Headphone Output", ak4641_hp_out_enum),
	SOC_SINGWE_BOOW_EXT("Pwayback Deemphasis Switch", 0,
					ak4641_get_deemph, ak4641_put_deemph),

	SOC_SINGWE_TWV("Mic Boost Vowume", AK4641_MIC, 0, 1, 0, mic_boost_twv),

	SOC_SINGWE("AWC Opewation Time", AK4641_TIMEW, 0, 3, 0),
	SOC_SINGWE("AWC Wecovewy Time", AK4641_TIMEW, 2, 3, 0),
	SOC_SINGWE("AWC ZC Time", AK4641_TIMEW, 4, 3, 0),

	SOC_SINGWE("AWC 1 Switch", AK4641_AWC1, 5, 1, 0),

	SOC_SINGWE_TWV("AWC Vowume", AK4641_AWC2, 0, 71, 0, awc_twv),
	SOC_SINGWE("Weft Out Enabwe Switch", AK4641_SIG2, 1, 1, 0),
	SOC_SINGWE("Wight Out Enabwe Switch", AK4641_SIG2, 0, 1, 0),

	SOC_SINGWE_TWV("Captuwe Vowume", AK4641_PGA, 0, 71, 0, captuwe_twv),

	SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume", AK4641_WATT,
				AK4641_WATT, 0, 255, 1, mastew_twv),

	SOC_SINGWE_TWV("AUX In Vowume", AK4641_VOW, 0, 15, 0, aux_in_twv),

	SOC_SINGWE("Equawizew Switch", AK4641_DAC, 2, 1, 0),
	SOC_SINGWE_TWV("EQ1 100 Hz Vowume", AK4641_EQWO, 0, 15, 1, eq_twv),
	SOC_SINGWE_TWV("EQ2 250 Hz Vowume", AK4641_EQWO, 4, 15, 1, eq_twv),
	SOC_SINGWE_TWV("EQ3 1 kHz Vowume", AK4641_EQMID, 0, 15, 1, eq_twv),
	SOC_SINGWE_TWV("EQ4 3.5 kHz Vowume", AK4641_EQMID, 4, 15, 1, eq_twv),
	SOC_SINGWE_TWV("EQ5 10 kHz Vowume", AK4641_EQHI, 0, 15, 1, eq_twv),
};

/* Mono 1 Mixew */
static const stwuct snd_kcontwow_new ak4641_mono1_mixew_contwows[] = {
	SOC_DAPM_SINGWE_TWV("Mic Mono Sidetone Vowume", AK4641_VOW, 7, 1, 0,
						mic_mono_sidetone_twv),
	SOC_DAPM_SINGWE("Mic Mono Sidetone Switch", AK4641_SIG1, 4, 1, 0),
	SOC_DAPM_SINGWE("Mono Pwayback Switch", AK4641_SIG1, 5, 1, 0),
};

/* Steweo Mixew */
static const stwuct snd_kcontwow_new ak4641_steweo_mixew_contwows[] = {
	SOC_DAPM_SINGWE_TWV("Mic Sidetone Vowume", AK4641_VOW, 4, 7, 0,
						mic_steweo_sidetone_twv),
	SOC_DAPM_SINGWE("Mic Sidetone Switch", AK4641_SIG2, 4, 1, 0),
	SOC_DAPM_SINGWE("Pwayback Switch", AK4641_SIG2, 7, 1, 0),
	SOC_DAPM_SINGWE("Aux Bypass Switch", AK4641_SIG2, 5, 1, 0),
};

/* Input Mixew */
static const stwuct snd_kcontwow_new ak4641_input_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Mic Captuwe Switch", AK4641_MIC, 2, 1, 0),
	SOC_DAPM_SINGWE("Aux Captuwe Switch", AK4641_MIC, 5, 1, 0),
};

/* Mic mux */
static const stwuct snd_kcontwow_new ak4641_mic_mux_contwow =
	SOC_DAPM_ENUM("Mic Sewect", ak4641_mic_sewect_enum);

/* Input mux */
static const stwuct snd_kcontwow_new ak4641_input_mux_contwow =
	SOC_DAPM_ENUM("Input Sewect", ak4641_mic_ow_dac_enum);

/* mono 2 switch */
static const stwuct snd_kcontwow_new ak4641_mono2_contwow =
	SOC_DAPM_SINGWE("Switch", AK4641_SIG1, 0, 1, 0);

/* ak4641 dapm widgets */
static const stwuct snd_soc_dapm_widget ak4641_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Steweo Mixew", SND_SOC_NOPM, 0, 0,
		&ak4641_steweo_mixew_contwows[0],
		AWWAY_SIZE(ak4641_steweo_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Mono1 Mixew", SND_SOC_NOPM, 0, 0,
		&ak4641_mono1_mixew_contwows[0],
		AWWAY_SIZE(ak4641_mono1_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Input Mixew", SND_SOC_NOPM, 0, 0,
		&ak4641_input_mixew_contwows[0],
		AWWAY_SIZE(ak4641_input_mixew_contwows)),
	SND_SOC_DAPM_MUX("Mic Mux", SND_SOC_NOPM, 0, 0,
		&ak4641_mic_mux_contwow),
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
		&ak4641_input_mux_contwow),
	SND_SOC_DAPM_SWITCH("Mono 2 Enabwe", SND_SOC_NOPM, 0, 0,
		&ak4641_mono2_contwow),

	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("MOUT1"),
	SND_SOC_DAPM_OUTPUT("MOUT2"),
	SND_SOC_DAPM_OUTPUT("MICOUT"),

	SND_SOC_DAPM_ADC("ADC", "HiFi Captuwe", AK4641_PM1, 0, 0),
	SND_SOC_DAPM_PGA("Mic", AK4641_PM1, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AUX In", AK4641_PM1, 2, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mono Out", AK4641_PM1, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wine Out", AK4641_PM1, 4, 0, NUWW, 0),

	SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", AK4641_PM2, 0, 0),
	SND_SOC_DAPM_PGA("Mono Out 2", AK4641_PM2, 3, 0, NUWW, 0),

	SND_SOC_DAPM_ADC("Voice ADC", "Voice Captuwe", AK4641_BTIF, 0, 0),
	SND_SOC_DAPM_DAC("Voice DAC", "Voice Pwayback", AK4641_BTIF, 1, 0),

	SND_SOC_DAPM_MICBIAS("Mic Int Bias", AK4641_MIC, 3, 0),
	SND_SOC_DAPM_MICBIAS("Mic Ext Bias", AK4641_MIC, 4, 0),

	SND_SOC_DAPM_INPUT("MICIN"),
	SND_SOC_DAPM_INPUT("MICEXT"),
	SND_SOC_DAPM_INPUT("AUX"),
	SND_SOC_DAPM_INPUT("AIN"),
};

static const stwuct snd_soc_dapm_woute ak4641_audio_map[] = {
	/* Steweo Mixew */
	{"Steweo Mixew", "Pwayback Switch", "DAC"},
	{"Steweo Mixew", "Mic Sidetone Switch", "Input Mux"},
	{"Steweo Mixew", "Aux Bypass Switch", "AUX In"},

	/* Mono 1 Mixew */
	{"Mono1 Mixew", "Mic Mono Sidetone Switch", "Input Mux"},
	{"Mono1 Mixew", "Mono Pwayback Switch", "DAC"},

	/* Mic */
	{"Mic", NUWW, "AIN"},
	{"Mic Mux", "Intewnaw", "Mic Int Bias"},
	{"Mic Mux", "Extewnaw", "Mic Ext Bias"},
	{"Mic Int Bias", NUWW, "MICIN"},
	{"Mic Ext Bias", NUWW, "MICEXT"},
	{"MICOUT", NUWW, "Mic Mux"},

	/* Input Mux */
	{"Input Mux", "Micwophone", "Mic"},
	{"Input Mux", "Voice DAC", "Voice DAC"},

	/* Wine Out */
	{"WOUT", NUWW, "Wine Out"},
	{"WOUT", NUWW, "Wine Out"},
	{"Wine Out", NUWW, "Steweo Mixew"},

	/* Mono 1 Out */
	{"MOUT1", NUWW, "Mono Out"},
	{"Mono Out", NUWW, "Mono1 Mixew"},

	/* Mono 2 Out */
	{"MOUT2", NUWW, "Mono 2 Enabwe"},
	{"Mono 2 Enabwe", "Switch", "Mono Out 2"},
	{"Mono Out 2", NUWW, "Steweo Mixew"},

	{"Voice ADC", NUWW, "Mono 2 Enabwe"},

	/* Aux In */
	{"AUX In", NUWW, "AUX"},

	/* ADC */
	{"ADC", NUWW, "Input Mixew"},
	{"Input Mixew", "Mic Captuwe Switch", "Mic"},
	{"Input Mixew", "Aux Captuwe Switch", "AUX In"},
};

static int ak4641_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
	int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct ak4641_pwiv *ak4641 = snd_soc_component_get_dwvdata(component);

	ak4641->syscwk = fweq;
	wetuwn 0;
}

static int ak4641_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4641_pwiv *ak4641 = snd_soc_component_get_dwvdata(component);
	int wate = pawams_wate(pawams), fs = 256;
	u8 mode2;

	if (wate)
		fs = ak4641->syscwk / wate;
	ewse
		wetuwn -EINVAW;

	/* set fs */
	switch (fs) {
	case 1024:
		mode2 = (0x2 << 5);
		bweak;
	case 512:
		mode2 = (0x1 << 5);
		bweak;
	case 256:
		mode2 = (0x0 << 5);
		bweak;
	defauwt:
		dev_eww(component->dev, "Ewwow: unsuppowted fs=%d\n", fs);
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AK4641_MODE2, (0x3 << 5), mode2);

	/* Update de-emphasis fiwtew fow the new wate */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		ak4641->pwayback_fs = wate;
		ak4641_set_deemph(component);
	}

	wetuwn 0;
}

static int ak4641_pcm_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
				  unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u8 btif;
	int wet;

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		btif = (0x3 << 5);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		btif = (0x2 << 5);
		bweak;
	case SND_SOC_DAIFMT_DSP_A:	/* MSB aftew FWM */
		btif = (0x0 << 5);
		bweak;
	case SND_SOC_DAIFMT_DSP_B:	/* MSB duwing FWM */
		btif = (0x1 << 5);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, AK4641_BTIF, (0x3 << 5), btif);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ak4641_i2s_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u8 mode1 = 0;

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		mode1 = 0x02;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		mode1 = 0x01;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn snd_soc_component_wwite(component, AK4641_MODE1, mode1);
}

static int ak4641_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	wetuwn snd_soc_component_update_bits(component, AK4641_DAC, 0x20, mute ? 0x20 : 0);
}

static int ak4641_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct ak4641_pwiv *ak4641 = snd_soc_component_get_dwvdata(component);
	stwuct ak4641_pwatfowm_data *pdata = component->dev->pwatfowm_data;
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* unmute */
		snd_soc_component_update_bits(component, AK4641_DAC, 0x20, 0);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		/* mute */
		snd_soc_component_update_bits(component, AK4641_DAC, 0x20, 0x20);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			if (pdata && gpio_is_vawid(pdata->gpio_powew))
				gpio_set_vawue(pdata->gpio_powew, 1);
			mdeway(1);
			if (pdata && gpio_is_vawid(pdata->gpio_npdn))
				gpio_set_vawue(pdata->gpio_npdn, 1);
			mdeway(1);

			wet = wegcache_sync(ak4641->wegmap);
			if (wet) {
				dev_eww(component->dev,
					"Faiwed to sync cache: %d\n", wet);
				wetuwn wet;
			}
		}
		snd_soc_component_update_bits(component, AK4641_PM1, 0x80, 0x80);
		snd_soc_component_update_bits(component, AK4641_PM2, 0x80, 0);
		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, AK4641_PM1, 0x80, 0);
		if (pdata && gpio_is_vawid(pdata->gpio_npdn))
			gpio_set_vawue(pdata->gpio_npdn, 0);
		if (pdata && gpio_is_vawid(pdata->gpio_powew))
			gpio_set_vawue(pdata->gpio_powew, 0);
		wegcache_mawk_diwty(ak4641->wegmap);
		bweak;
	}
	wetuwn 0;
}

#define AK4641_WATES	(SNDWV_PCM_WATE_8000_48000)
#define AK4641_WATES_BT (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
			 SNDWV_PCM_WATE_16000)
#define AK4641_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE)

static const stwuct snd_soc_dai_ops ak4641_i2s_dai_ops = {
	.hw_pawams    = ak4641_i2s_hw_pawams,
	.set_fmt      = ak4641_i2s_set_dai_fmt,
	.mute_stweam  = ak4641_mute,
	.set_syscwk   = ak4641_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dai_ops ak4641_pcm_dai_ops = {
	.hw_pawams    = NUWW, /* wates awe contwowwed by BT chip */
	.set_fmt      = ak4641_pcm_set_dai_fmt,
	.mute_stweam  = ak4641_mute,
	.set_syscwk   = ak4641_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew ak4641_dai[] = {
{
	.name = "ak4641-hifi",
	.id = 1,
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = AK4641_WATES,
		.fowmats = AK4641_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "HiFi Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = AK4641_WATES,
		.fowmats = AK4641_FOWMATS,
	},
	.ops = &ak4641_i2s_dai_ops,
	.symmetwic_wate = 1,
},
{
	.name = "ak4641-voice",
	.id = 1,
	.pwayback = {
		.stweam_name = "Voice Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = AK4641_WATES_BT,
		.fowmats = AK4641_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Voice Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = AK4641_WATES_BT,
		.fowmats = AK4641_FOWMATS,
	},
	.ops = &ak4641_pcm_dai_ops,
	.symmetwic_wate = 1,
},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_ak4641 = {
	.contwows		= ak4641_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak4641_snd_contwows),
	.dapm_widgets		= ak4641_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak4641_dapm_widgets),
	.dapm_woutes		= ak4641_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(ak4641_audio_map),
	.set_bias_wevew		= ak4641_set_bias_wevew,
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config ak4641_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = AK4641_BTIF,
	.weg_defauwts = ak4641_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(ak4641_weg_defauwts),
	.cache_type = WEGCACHE_WBTWEE,
};

static int ak4641_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct ak4641_pwatfowm_data *pdata = i2c->dev.pwatfowm_data;
	stwuct ak4641_pwiv *ak4641;
	int wet;

	ak4641 = devm_kzawwoc(&i2c->dev, sizeof(stwuct ak4641_pwiv),
			      GFP_KEWNEW);
	if (!ak4641)
		wetuwn -ENOMEM;

	ak4641->wegmap = devm_wegmap_init_i2c(i2c, &ak4641_wegmap);
	if (IS_EWW(ak4641->wegmap))
		wetuwn PTW_EWW(ak4641->wegmap);

	if (pdata) {
		if (gpio_is_vawid(pdata->gpio_powew)) {
			wet = gpio_wequest_one(pdata->gpio_powew,
					GPIOF_OUT_INIT_WOW, "ak4641 powew");
			if (wet)
				goto eww_out;
		}
		if (gpio_is_vawid(pdata->gpio_npdn)) {
			wet = gpio_wequest_one(pdata->gpio_npdn,
					GPIOF_OUT_INIT_WOW, "ak4641 npdn");
			if (wet)
				goto eww_gpio;

			udeway(1); /* > 150 ns */
			gpio_set_vawue(pdata->gpio_npdn, 1);
		}
	}

	i2c_set_cwientdata(i2c, ak4641);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				&soc_component_dev_ak4641,
				ak4641_dai, AWWAY_SIZE(ak4641_dai));
	if (wet != 0)
		goto eww_gpio2;

	wetuwn 0;

eww_gpio2:
	if (pdata) {
		if (gpio_is_vawid(pdata->gpio_powew))
			gpio_set_vawue(pdata->gpio_powew, 0);
		if (gpio_is_vawid(pdata->gpio_npdn))
			gpio_fwee(pdata->gpio_npdn);
	}
eww_gpio:
	if (pdata && gpio_is_vawid(pdata->gpio_powew))
		gpio_fwee(pdata->gpio_powew);
eww_out:
	wetuwn wet;
}

static void ak4641_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct ak4641_pwatfowm_data *pdata = i2c->dev.pwatfowm_data;

	if (pdata) {
		if (gpio_is_vawid(pdata->gpio_powew)) {
			gpio_set_vawue(pdata->gpio_powew, 0);
			gpio_fwee(pdata->gpio_powew);
		}
		if (gpio_is_vawid(pdata->gpio_npdn))
			gpio_fwee(pdata->gpio_npdn);
	}
}

static const stwuct i2c_device_id ak4641_i2c_id[] = {
	{ "ak4641", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ak4641_i2c_id);

static stwuct i2c_dwivew ak4641_i2c_dwivew = {
	.dwivew = {
		.name = "ak4641",
	},
	.pwobe =    ak4641_i2c_pwobe,
	.wemove =   ak4641_i2c_wemove,
	.id_tabwe = ak4641_i2c_id,
};

moduwe_i2c_dwivew(ak4641_i2c_dwivew);

MODUWE_DESCWIPTION("SoC AK4641 dwivew");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@gnufiish.owg>");
MODUWE_WICENSE("GPW");
