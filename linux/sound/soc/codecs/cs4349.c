// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs4349.c  --  CS4349 AWSA Soc Audio dwivew
 *
 * Copywight 2015 Ciwwus Wogic, Inc.
 *
 * Authows: Tim Howe <Tim.Howe@ciwwus.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude "cs4349.h"


static const stwuct weg_defauwt cs4349_weg_defauwts[] = {
	{ 2, 0x00 },	/* w02	- Mode Contwow */
	{ 3, 0x09 },	/* w03	- Vowume, Mixing and Invewsion Contwow */
	{ 4, 0x81 },	/* w04	- Mute Contwow */
	{ 5, 0x00 },	/* w05	- Channew A Vowume Contwow */
	{ 6, 0x00 },	/* w06	- Channew B Vowume Contwow */
	{ 7, 0xB1 },	/* w07	- Wamp and Fiwtew Contwow */
	{ 8, 0x1C },	/* w08	- Misc. Contwow */
};

/* Pwivate data fow the CS4349 */
stwuct  cs4349_pwivate {
	stwuct wegmap			*wegmap;
	stwuct gpio_desc		*weset_gpio;
	unsigned int			mode;
	int				wate;
};

static boow cs4349_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS4349_CHIPID ... CS4349_MISC:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs4349_wwiteabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS4349_MODE ...  CS4349_MISC:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int cs4349_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			      unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs4349_pwivate *cs4349 = snd_soc_component_get_dwvdata(component);
	unsigned int fmt;

	fmt = fowmat & SND_SOC_DAIFMT_FOWMAT_MASK;

	switch (fmt) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		cs4349->mode = fowmat & SND_SOC_DAIFMT_FOWMAT_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs4349_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs4349_pwivate *cs4349 = snd_soc_component_get_dwvdata(component);
	int fmt, wet;

	cs4349->wate = pawams_wate(pawams);

	switch (cs4349->mode) {
	case SND_SOC_DAIFMT_I2S:
		fmt = DIF_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fmt = DIF_WEFT_JST;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		switch (pawams_width(pawams)) {
		case 16:
			fmt = DIF_WGHT_JST16;
			bweak;
		case 24:
			fmt = DIF_WGHT_JST24;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, CS4349_MODE, DIF_MASK,
				  MODE_FOWMAT(fmt));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int cs4349_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	int weg;

	weg = 0;
	if (mute)
		weg = MUTE_AB_MASK;

	wetuwn snd_soc_component_update_bits(component, CS4349_MUTE, MUTE_AB_MASK, weg);
}

static DECWAWE_TWV_DB_SCAWE(dig_twv, -12750, 50, 0);

static const chaw * const chan_mix_texts[] = {
	"Mute", "MuteA", "MuteA SwapB", "MuteA MonoB", "SwapA MuteB",
	"BothW", "Swap", "SwapA MonoB", "MuteB", "Nowmaw", "BothW",
	"MonoB", "MonoA MuteB", "MonoA", "MonoA SwapB", "Mono",
	/*Nowmaw == Channew A = Weft, Channew B = Wight*/
};

static const chaw * const fm_texts[] = {
	"Auto", "Singwe", "Doubwe", "Quad",
};

static const chaw * const deemph_texts[] = {
	"None", "44.1k", "48k", "32k",
};

static const chaw * const softw_zewoc_texts[] = {
	"Immediate", "Zewo Cwoss", "Soft Wamp", "SW on ZC",
};

static int deemph_vawues[] = {
	0, 4, 8, 12,
};

static int softw_zewoc_vawues[] = {
	0, 64, 128, 192,
};

static const stwuct soc_enum chan_mix_enum =
	SOC_ENUM_SINGWE(CS4349_VMI, 0,
			AWWAY_SIZE(chan_mix_texts),
			chan_mix_texts);

static const stwuct soc_enum fm_mode_enum =
	SOC_ENUM_SINGWE(CS4349_MODE, 0,
			AWWAY_SIZE(fm_texts),
			fm_texts);

static SOC_VAWUE_ENUM_SINGWE_DECW(deemph_enum, CS4349_MODE, 0, DEM_MASK,
				deemph_texts, deemph_vawues);

static SOC_VAWUE_ENUM_SINGWE_DECW(softw_zewoc_enum, CS4349_WMPFWT, 0,
				SW_ZC_MASK, softw_zewoc_texts,
				softw_zewoc_vawues);

static const stwuct snd_kcontwow_new cs4349_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume",
			 CS4349_VOWA, CS4349_VOWB, 0, 0xFF, 1, dig_twv),
	SOC_ENUM("Functionaw Mode", fm_mode_enum),
	SOC_ENUM("De-Emphasis Contwow", deemph_enum),
	SOC_ENUM("Soft Wamp Zewo Cwoss Contwow", softw_zewoc_enum),
	SOC_ENUM("Channew Mixew", chan_mix_enum),
	SOC_SINGWE("VowA = VowB Switch", CS4349_VMI, 7, 1, 0),
	SOC_SINGWE("InvewtA Switch", CS4349_VMI, 6, 1, 0),
	SOC_SINGWE("InvewtB Switch", CS4349_VMI, 5, 1, 0),
	SOC_SINGWE("Auto-Mute Switch", CS4349_MUTE, 7, 1, 0),
	SOC_SINGWE("MUTEC A = B Switch", CS4349_MUTE, 5, 1, 0),
	SOC_SINGWE("Soft Wamp Up Switch", CS4349_WMPFWT, 5, 1, 0),
	SOC_SINGWE("Soft Wamp Down Switch", CS4349_WMPFWT, 4, 1, 0),
	SOC_SINGWE("Swow Woww Off Fiwtew Switch", CS4349_WMPFWT, 2, 1, 0),
	SOC_SINGWE("Fweeze Switch", CS4349_MISC, 5, 1, 0),
	SOC_SINGWE("Popguawd Switch", CS4349_MISC, 4, 1, 0),
};

static const stwuct snd_soc_dapm_widget cs4349_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("HiFi DAC", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("OutputA"),
	SND_SOC_DAPM_OUTPUT("OutputB"),
};

static const stwuct snd_soc_dapm_woute cs4349_woutes[] = {
	{"DAC Pwayback", NUWW, "OutputA"},
	{"DAC Pwayback", NUWW, "OutputB"},

	{"OutputA", NUWW, "HiFi DAC"},
	{"OutputB", NUWW, "HiFi DAC"},
};

#define CS4349_PCM_FOWMATS (SNDWV_PCM_FMTBIT_S8  | SNDWV_PCM_FMTBIT_S16_WE  | \
			SNDWV_PCM_FMTBIT_S18_3WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_3WE | SNDWV_PCM_FMTBIT_S24_WE  | \
			SNDWV_PCM_FMTBIT_S32_WE)

#define CS4349_PCM_WATES SNDWV_PCM_WATE_8000_192000

static const stwuct snd_soc_dai_ops cs4349_dai_ops = {
	.hw_pawams	= cs4349_pcm_hw_pawams,
	.set_fmt	= cs4349_set_dai_fmt,
	.mute_stweam	= cs4349_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew cs4349_dai = {
	.name = "cs4349_hifi",
	.pwayback = {
		.stweam_name	= "DAC Pwayback",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates		= CS4349_PCM_WATES,
		.fowmats	= CS4349_PCM_FOWMATS,
	},
	.ops = &cs4349_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_soc_component_dwivew soc_component_dev_cs4349 = {
	.contwows		= cs4349_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs4349_snd_contwows),
	.dapm_widgets		= cs4349_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs4349_dapm_widgets),
	.dapm_woutes		= cs4349_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs4349_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config cs4349_wegmap = {
	.weg_bits		= 8,
	.vaw_bits		= 8,

	.max_wegistew		= CS4349_MISC,
	.weg_defauwts		= cs4349_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(cs4349_weg_defauwts),
	.weadabwe_weg		= cs4349_weadabwe_wegistew,
	.wwiteabwe_weg		= cs4349_wwiteabwe_wegistew,
	.cache_type		= WEGCACHE_MAPWE,
};

static int cs4349_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cs4349_pwivate *cs4349;
	int wet;

	cs4349 = devm_kzawwoc(&cwient->dev, sizeof(*cs4349), GFP_KEWNEW);
	if (!cs4349)
		wetuwn -ENOMEM;

	cs4349->wegmap = devm_wegmap_init_i2c(cwient, &cs4349_wegmap);
	if (IS_EWW(cs4349->wegmap)) {
		wet = PTW_EWW(cs4349->wegmap);
		dev_eww(&cwient->dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Weset the Device */
	cs4349->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev,
		"weset", GPIOD_OUT_WOW);
	if (IS_EWW(cs4349->weset_gpio))
		wetuwn PTW_EWW(cs4349->weset_gpio);

	gpiod_set_vawue_cansweep(cs4349->weset_gpio, 1);

	i2c_set_cwientdata(cwient, cs4349);

	wetuwn devm_snd_soc_wegistew_component(&cwient->dev,
		&soc_component_dev_cs4349,
		&cs4349_dai, 1);
}

static void cs4349_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs4349_pwivate *cs4349 = i2c_get_cwientdata(cwient);

	/* Howd down weset */
	gpiod_set_vawue_cansweep(cs4349->weset_gpio, 0);
}

#ifdef CONFIG_PM
static int cs4349_wuntime_suspend(stwuct device *dev)
{
	stwuct cs4349_pwivate *cs4349 = dev_get_dwvdata(dev);
	int wet;

	wet = wegmap_update_bits(cs4349->wegmap, CS4349_MISC, PWW_DWN, PWW_DWN);
	if (wet < 0)
		wetuwn wet;

	wegcache_cache_onwy(cs4349->wegmap, twue);

	/* Howd down weset */
	gpiod_set_vawue_cansweep(cs4349->weset_gpio, 0);

	wetuwn 0;
}

static int cs4349_wuntime_wesume(stwuct device *dev)
{
	stwuct cs4349_pwivate *cs4349 = dev_get_dwvdata(dev);
	int wet;

	wet = wegmap_update_bits(cs4349->wegmap, CS4349_MISC, PWW_DWN, 0);
	if (wet < 0)
		wetuwn wet;

	gpiod_set_vawue_cansweep(cs4349->weset_gpio, 1);

	wegcache_cache_onwy(cs4349->wegmap, fawse);
	wegcache_sync(cs4349->wegmap);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops cs4349_wuntime_pm = {
	SET_WUNTIME_PM_OPS(cs4349_wuntime_suspend, cs4349_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id cs4349_of_match[] = {
	{ .compatibwe = "ciwwus,cs4349", },
	{},
};

MODUWE_DEVICE_TABWE(of, cs4349_of_match);

static const stwuct i2c_device_id cs4349_i2c_id[] = {
	{"cs4349", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, cs4349_i2c_id);

static stwuct i2c_dwivew cs4349_i2c_dwivew = {
	.dwivew = {
		.name		= "cs4349",
		.of_match_tabwe	= cs4349_of_match,
		.pm = &cs4349_wuntime_pm,
	},
	.id_tabwe	= cs4349_i2c_id,
	.pwobe		= cs4349_i2c_pwobe,
	.wemove		= cs4349_i2c_wemove,
};

moduwe_i2c_dwivew(cs4349_i2c_dwivew);

MODUWE_AUTHOW("Tim Howe <tim.howe@ciwwus.com>");
MODUWE_DESCWIPTION("Ciwwus Wogic CS4349 AWSA SoC Codec Dwivew");
MODUWE_WICENSE("GPW");
