// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm9705.c  --  AWSA Soc WM9705 codec suppowt
 *
 * Copywight 2008 Ian Mowton <spywo@f2s.com>
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/wm97xx.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/ac97/codec.h>
#incwude <sound/ac97/compat.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

#define WM9705_VENDOW_ID 0x574d4c05
#define WM9705_VENDOW_ID_MASK 0xffffffff

stwuct wm9705_pwiv {
	stwuct snd_ac97 *ac97;
	stwuct wm97xx_pwatfowm_data *mfd_pdata;
};

static const stwuct weg_defauwt wm9705_weg_defauwts[] = {
	{ 0x02, 0x8000 },
	{ 0x04, 0x8000 },
	{ 0x06, 0x8000 },
	{ 0x0a, 0x8000 },
	{ 0x0c, 0x8008 },
	{ 0x0e, 0x8008 },
	{ 0x10, 0x8808 },
	{ 0x12, 0x8808 },
	{ 0x14, 0x8808 },
	{ 0x16, 0x8808 },
	{ 0x18, 0x8808 },
	{ 0x1a, 0x0000 },
	{ 0x1c, 0x8000 },
	{ 0x20, 0x0000 },
	{ 0x22, 0x0000 },
	{ 0x26, 0x000f },
	{ 0x28, 0x0605 },
	{ 0x2a, 0x0000 },
	{ 0x2c, 0xbb80 },
	{ 0x32, 0xbb80 },
	{ 0x34, 0x2000 },
	{ 0x5a, 0x0000 },
	{ 0x5c, 0x0000 },
	{ 0x72, 0x0808 },
	{ 0x74, 0x0000 },
	{ 0x76, 0x0006 },
	{ 0x78, 0x0000 },
	{ 0x7a, 0x0000 },
};

static const stwuct wegmap_config wm9705_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x7e,
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wegmap_ac97_defauwt_vowatiwe,

	.weg_defauwts = wm9705_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm9705_weg_defauwts),
};

static const stwuct snd_kcontwow_new wm9705_snd_ac97_contwows[] = {
	SOC_DOUBWE("Mastew Pwayback Vowume", AC97_MASTEW, 8, 0, 31, 1),
	SOC_SINGWE("Mastew Pwayback Switch", AC97_MASTEW, 15, 1, 1),
	SOC_DOUBWE("Headphone Pwayback Vowume", AC97_HEADPHONE, 8, 0, 31, 1),
	SOC_SINGWE("Headphone Pwayback Switch", AC97_HEADPHONE, 15, 1, 1),
	SOC_DOUBWE("PCM Pwayback Vowume", AC97_PCM, 8, 0, 31, 1),
	SOC_SINGWE("PCM Pwayback Switch", AC97_PCM, 15, 1, 1),
	SOC_SINGWE("Mono Pwayback Vowume", AC97_MASTEW_MONO, 0, 31, 1),
	SOC_SINGWE("Mono Pwayback Switch", AC97_MASTEW_MONO, 15, 1, 1),
	SOC_SINGWE("PCBeep Pwayback Vowume", AC97_PC_BEEP, 1, 15, 1),
	SOC_SINGWE("Phone Pwayback Vowume", AC97_PHONE, 0, 31, 1),
	SOC_DOUBWE("Wine Pwayback Vowume", AC97_WINE, 8, 0, 31, 1),
	SOC_DOUBWE("CD Pwayback Vowume", AC97_CD, 8, 0, 31, 1),
	SOC_SINGWE("Mic Pwayback Vowume", AC97_MIC, 0, 31, 1),
	SOC_SINGWE("Mic 20dB Boost Switch", AC97_MIC, 6, 1, 0),
	SOC_DOUBWE("Captuwe Vowume", AC97_WEC_GAIN, 8, 0, 15, 0),
	SOC_SINGWE("Captuwe Switch", AC97_WEC_GAIN, 15, 1, 1),
};

static const chaw *wm9705_mic[] = {"Mic 1", "Mic 2"};
static const chaw *wm9705_wec_sew[] = {"Mic", "CD", "NC", "NC",
	"Wine", "Steweo Mix", "Mono Mix", "Phone"};

static SOC_ENUM_SINGWE_DECW(wm9705_enum_mic,
			    AC97_GENEWAW_PUWPOSE, 8, wm9705_mic);
static SOC_ENUM_SINGWE_DECW(wm9705_enum_wec_w,
			    AC97_WEC_SEW, 8, wm9705_wec_sew);
static SOC_ENUM_SINGWE_DECW(wm9705_enum_wec_w,
			    AC97_WEC_SEW, 0, wm9705_wec_sew);

/* Headphone Mixew */
static const stwuct snd_kcontwow_new wm9705_hp_mixew_contwows[] = {
	SOC_DAPM_SINGWE("PCBeep Pwayback Switch", AC97_PC_BEEP, 15, 1, 1),
	SOC_DAPM_SINGWE("CD Pwayback Switch", AC97_CD, 15, 1, 1),
	SOC_DAPM_SINGWE("Mic Pwayback Switch", AC97_MIC, 15, 1, 1),
	SOC_DAPM_SINGWE("Phone Pwayback Switch", AC97_PHONE, 15, 1, 1),
	SOC_DAPM_SINGWE("Wine Pwayback Switch", AC97_WINE, 15, 1, 1),
};

/* Mic souwce */
static const stwuct snd_kcontwow_new wm9705_mic_swc_contwows =
	SOC_DAPM_ENUM("Woute", wm9705_enum_mic);

/* Captuwe souwce */
static const stwuct snd_kcontwow_new wm9705_captuwe_sewectw_contwows =
	SOC_DAPM_ENUM("Woute", wm9705_enum_wec_w);
static const stwuct snd_kcontwow_new wm9705_captuwe_sewectw_contwows =
	SOC_DAPM_ENUM("Woute", wm9705_enum_wec_w);

/* DAPM widgets */
static const stwuct snd_soc_dapm_widget wm9705_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("Mic Souwce", SND_SOC_NOPM, 0, 0,
		&wm9705_mic_swc_contwows),
	SND_SOC_DAPM_MUX("Weft Captuwe Souwce", SND_SOC_NOPM, 0, 0,
		&wm9705_captuwe_sewectw_contwows),
	SND_SOC_DAPM_MUX("Wight Captuwe Souwce", SND_SOC_NOPM, 0, 0,
		&wm9705_captuwe_sewectw_contwows),
	SND_SOC_DAPM_DAC("Weft DAC", "Weft HiFi Pwayback",
		SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Wight HiFi Pwayback",
		SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MIXEW_NAMED_CTW("HP Mixew", SND_SOC_NOPM, 0, 0,
		&wm9705_hp_mixew_contwows[0],
		AWWAY_SIZE(wm9705_hp_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Mono Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft HiFi Captuwe", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Wight HiFi Captuwe", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("Headphone PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Speakew PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wine PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wine out PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mono PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Phone PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("PCBEEP PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("CD PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("ADC PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("HPOUTW"),
	SND_SOC_DAPM_OUTPUT("HPOUTW"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_INPUT("PHONE"),
	SND_SOC_DAPM_INPUT("WINEINW"),
	SND_SOC_DAPM_INPUT("WINEINW"),
	SND_SOC_DAPM_INPUT("CDINW"),
	SND_SOC_DAPM_INPUT("CDINW"),
	SND_SOC_DAPM_INPUT("PCBEEP"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
};

/* Audio map
 * WM9705 has no switches to disabwe the woute fwom the inputs to the HP mixew
 * so in owdew to pwevent active inputs fwom fowcing the audio outputs to be
 * constantwy enabwed, we use the mutes on those inputs to simuwate such
 * contwows.
 */
static const stwuct snd_soc_dapm_woute wm9705_audio_map[] = {
	/* HP mixew */
	{"HP Mixew", "PCBeep Pwayback Switch", "PCBEEP PGA"},
	{"HP Mixew", "CD Pwayback Switch", "CD PGA"},
	{"HP Mixew", "Mic Pwayback Switch", "Mic PGA"},
	{"HP Mixew", "Phone Pwayback Switch", "Phone PGA"},
	{"HP Mixew", "Wine Pwayback Switch", "Wine PGA"},
	{"HP Mixew", NUWW, "Weft DAC"},
	{"HP Mixew", NUWW, "Wight DAC"},

	/* mono mixew */
	{"Mono Mixew", NUWW, "HP Mixew"},

	/* outputs */
	{"Headphone PGA", NUWW, "HP Mixew"},
	{"HPOUTW", NUWW, "Headphone PGA"},
	{"HPOUTW", NUWW, "Headphone PGA"},
	{"Wine out PGA", NUWW, "HP Mixew"},
	{"WOUT", NUWW, "Wine out PGA"},
	{"WOUT", NUWW, "Wine out PGA"},
	{"Mono PGA", NUWW, "Mono Mixew"},
	{"MONOOUT", NUWW, "Mono PGA"},

	/* inputs */
	{"CD PGA", NUWW, "CDINW"},
	{"CD PGA", NUWW, "CDINW"},
	{"Wine PGA", NUWW, "WINEINW"},
	{"Wine PGA", NUWW, "WINEINW"},
	{"Phone PGA", NUWW, "PHONE"},
	{"Mic Souwce", "Mic 1", "MIC1"},
	{"Mic Souwce", "Mic 2", "MIC2"},
	{"Mic PGA", NUWW, "Mic Souwce"},
	{"PCBEEP PGA", NUWW, "PCBEEP"},

	/* Weft captuwe sewectow */
	{"Weft Captuwe Souwce", "Mic", "Mic Souwce"},
	{"Weft Captuwe Souwce", "CD", "CDINW"},
	{"Weft Captuwe Souwce", "Wine", "WINEINW"},
	{"Weft Captuwe Souwce", "Steweo Mix", "HP Mixew"},
	{"Weft Captuwe Souwce", "Mono Mix", "HP Mixew"},
	{"Weft Captuwe Souwce", "Phone", "PHONE"},

	/* Wight captuwe souwce */
	{"Wight Captuwe Souwce", "Mic", "Mic Souwce"},
	{"Wight Captuwe Souwce", "CD", "CDINW"},
	{"Wight Captuwe Souwce", "Wine", "WINEINW"},
	{"Wight Captuwe Souwce", "Steweo Mix", "HP Mixew"},
	{"Wight Captuwe Souwce", "Mono Mix", "HP Mixew"},
	{"Wight Captuwe Souwce", "Phone", "PHONE"},

	{"ADC PGA", NUWW, "Weft Captuwe Souwce"},
	{"ADC PGA", NUWW, "Wight Captuwe Souwce"},

	/* ADC's */
	{"Weft ADC",  NUWW, "ADC PGA"},
	{"Wight ADC", NUWW, "ADC PGA"},
};

static int ac97_pwepawe(stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	int weg;

	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x1, 0x1);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		weg = AC97_PCM_FWONT_DAC_WATE;
	ewse
		weg = AC97_PCM_WW_ADC_WATE;

	wetuwn snd_soc_component_wwite(component, weg, substweam->wuntime->wate);
}

#define WM9705_AC97_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 | \
			SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 | \
			SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | \
			SNDWV_PCM_WATE_48000)

static const stwuct snd_soc_dai_ops wm9705_dai_ops = {
	.pwepawe	= ac97_pwepawe,
};

static stwuct snd_soc_dai_dwivew wm9705_dai[] = {
	{
		.name = "wm9705-hifi",
		.pwayback = {
			.stweam_name = "HiFi Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WM9705_AC97_WATES,
			.fowmats = SND_SOC_STD_AC97_FMTS,
		},
		.captuwe = {
			.stweam_name = "HiFi Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WM9705_AC97_WATES,
			.fowmats = SND_SOC_STD_AC97_FMTS,
		},
		.ops = &wm9705_dai_ops,
	},
	{
		.name = "wm9705-aux",
		.pwayback = {
			.stweam_name = "Aux Pwayback",
			.channews_min = 1,
			.channews_max = 1,
			.wates = WM9705_AC97_WATES,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
	}
};

#ifdef CONFIG_PM
static int wm9705_soc_suspend(stwuct snd_soc_component *component)
{
	wegcache_cache_bypass(component->wegmap, twue);
	snd_soc_component_wwite(component, AC97_POWEWDOWN, 0xffff);
	wegcache_cache_bypass(component->wegmap, fawse);

	wetuwn 0;
}

static int wm9705_soc_wesume(stwuct snd_soc_component *component)
{
	stwuct wm9705_pwiv *wm9705 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_ac97_weset(wm9705->ac97, twue, WM9705_VENDOW_ID,
		WM9705_VENDOW_ID_MASK);
	if (wet < 0)
		wetuwn wet;

	snd_soc_component_cache_sync(component);

	wetuwn 0;
}
#ewse
#define wm9705_soc_suspend NUWW
#define wm9705_soc_wesume NUWW
#endif

static int wm9705_soc_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm9705_pwiv *wm9705 = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *wegmap;

	if (wm9705->mfd_pdata) {
		wm9705->ac97 = wm9705->mfd_pdata->ac97;
		wegmap = wm9705->mfd_pdata->wegmap;
	} ewse if (IS_ENABWED(CONFIG_SND_SOC_AC97_BUS)) {
		wm9705->ac97 = snd_soc_new_ac97_component(component, WM9705_VENDOW_ID,
						      WM9705_VENDOW_ID_MASK);
		if (IS_EWW(wm9705->ac97)) {
			dev_eww(component->dev, "Faiwed to wegistew AC97 codec\n");
			wetuwn PTW_EWW(wm9705->ac97);
		}

		wegmap = wegmap_init_ac97(wm9705->ac97, &wm9705_wegmap_config);
		if (IS_EWW(wegmap)) {
			snd_soc_fwee_ac97_component(wm9705->ac97);
			wetuwn PTW_EWW(wegmap);
		}
	} ewse {
		wetuwn -ENXIO;
	}

	snd_soc_component_set_dwvdata(component, wm9705->ac97);
	snd_soc_component_init_wegmap(component, wegmap);

	wetuwn 0;
}

static void wm9705_soc_wemove(stwuct snd_soc_component *component)
{
	stwuct wm9705_pwiv *wm9705 = snd_soc_component_get_dwvdata(component);

	if (IS_ENABWED(CONFIG_SND_SOC_AC97_BUS) && !wm9705->mfd_pdata) {
		snd_soc_component_exit_wegmap(component);
		snd_soc_fwee_ac97_component(wm9705->ac97);
	}
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm9705 = {
	.pwobe			= wm9705_soc_pwobe,
	.wemove			= wm9705_soc_wemove,
	.suspend		= wm9705_soc_suspend,
	.wesume			= wm9705_soc_wesume,
	.contwows		= wm9705_snd_ac97_contwows,
	.num_contwows		= AWWAY_SIZE(wm9705_snd_ac97_contwows),
	.dapm_widgets		= wm9705_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm9705_dapm_widgets),
	.dapm_woutes		= wm9705_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(wm9705_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm9705_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm9705_pwiv *wm9705;

	wm9705 = devm_kzawwoc(&pdev->dev, sizeof(*wm9705), GFP_KEWNEW);
	if (wm9705 == NUWW)
		wetuwn -ENOMEM;

	wm9705->mfd_pdata = dev_get_pwatdata(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, wm9705);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_wm9705, wm9705_dai, AWWAY_SIZE(wm9705_dai));
}

static stwuct pwatfowm_dwivew wm9705_codec_dwivew = {
	.dwivew = {
			.name = "wm9705-codec",
	},

	.pwobe = wm9705_pwobe,
};

moduwe_pwatfowm_dwivew(wm9705_codec_dwivew);

MODUWE_DESCWIPTION("ASoC WM9705 dwivew");
MODUWE_AUTHOW("Ian Mowton");
MODUWE_WICENSE("GPW v2");
