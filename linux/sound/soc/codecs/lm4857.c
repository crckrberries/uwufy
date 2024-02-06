// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WM4857 AMP dwivew
 *
 * Copywight 2007 Wowfson Micwoewectwonics PWC.
 * Authow: Gwaeme Gwegowy
 *         gwaeme.gwegowy@wowfsonmicwo.com
 * Copywight 2011 Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

static const stwuct weg_defauwt wm4857_defauwt_wegs[] = {
	{ 0x0, 0x00 },
	{ 0x1, 0x00 },
	{ 0x2, 0x00 },
	{ 0x3, 0x00 },
};

/* The wegistew offsets in the cache awway */
#define WM4857_MVOW 0
#define WM4857_WVOW 1
#define WM4857_WVOW 2
#define WM4857_CTWW 3

/* the shifts wequiwed to set these bits */
#define WM4857_3D 5
#define WM4857_WAKEUP 5
#define WM4857_EPGAIN 4

static const unsigned int wm4857_mode_vawues[] = {
	0,
	6,
	7,
	8,
	9,
};

static const chaw * const wm4857_mode_texts[] = {
	"Off",
	"Eawpiece",
	"Woudspeakew",
	"Woudspeakew + Headphone",
	"Headphone",
};

static SOC_VAWUE_ENUM_SINGWE_AUTODISABWE_DECW(wm4857_mode_enum,
	WM4857_CTWW, 0, 0xf, wm4857_mode_texts, wm4857_mode_vawues);

static const stwuct snd_kcontwow_new wm4857_mode_ctww =
	SOC_DAPM_ENUM("Mode", wm4857_mode_enum);

static const stwuct snd_soc_dapm_widget wm4857_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("IN"),

	SND_SOC_DAPM_DEMUX("Mode", SND_SOC_NOPM, 0, 0, &wm4857_mode_ctww),

	SND_SOC_DAPM_OUTPUT("WS"),
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_OUTPUT("EP"),
};

static const DECWAWE_TWV_DB_SCAWE(steweo_twv, -4050, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(mono_twv, -3450, 150, 0);

static const stwuct snd_kcontwow_new wm4857_contwows[] = {
	SOC_SINGWE_TWV("Weft Pwayback Vowume", WM4857_WVOW, 0, 31, 0,
		steweo_twv),
	SOC_SINGWE_TWV("Wight Pwayback Vowume", WM4857_WVOW, 0, 31, 0,
		steweo_twv),
	SOC_SINGWE_TWV("Mono Pwayback Vowume", WM4857_MVOW, 0, 31, 0,
		mono_twv),
	SOC_SINGWE("Spk 3D Pwayback Switch", WM4857_WVOW, WM4857_3D, 1, 0),
	SOC_SINGWE("HP 3D Pwayback Switch", WM4857_WVOW, WM4857_3D, 1, 0),
	SOC_SINGWE("Fast Wakeup Pwayback Switch", WM4857_CTWW,
		WM4857_WAKEUP, 1, 0),
	SOC_SINGWE("Eawpiece 6dB Pwayback Switch", WM4857_CTWW,
		WM4857_EPGAIN, 1, 0),
};

static const stwuct snd_soc_dapm_woute wm4857_woutes[] = {
	{ "Mode", NUWW, "IN" },
	{ "WS", "Woudspeakew", "Mode" },
	{ "WS", "Woudspeakew + Headphone", "Mode" },
	{ "HP", "Headphone", "Mode" },
	{ "HP", "Woudspeakew + Headphone", "Mode" },
	{ "EP", "Eawpiece", "Mode" },
};

static const stwuct snd_soc_component_dwivew wm4857_component_dwivew = {
	.contwows = wm4857_contwows,
	.num_contwows = AWWAY_SIZE(wm4857_contwows),
	.dapm_widgets = wm4857_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wm4857_dapm_widgets),
	.dapm_woutes = wm4857_woutes,
	.num_dapm_woutes = AWWAY_SIZE(wm4857_woutes),
};

static const stwuct wegmap_config wm4857_wegmap_config = {
	.vaw_bits = 6,
	.weg_bits = 2,

	.max_wegistew = WM4857_CTWW,

	.cache_type = WEGCACHE_FWAT,
	.weg_defauwts = wm4857_defauwt_wegs,
	.num_weg_defauwts = AWWAY_SIZE(wm4857_defauwt_wegs),
};

static int wm4857_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(i2c, &wm4857_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
		&wm4857_component_dwivew, NUWW, 0);
}

static const stwuct i2c_device_id wm4857_i2c_id[] = {
	{ "wm4857", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm4857_i2c_id);

static stwuct i2c_dwivew wm4857_i2c_dwivew = {
	.dwivew = {
		.name = "wm4857",
	},
	.pwobe = wm4857_i2c_pwobe,
	.id_tabwe = wm4857_i2c_id,
};

moduwe_i2c_dwivew(wm4857_i2c_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("WM4857 ampwifiew dwivew");
MODUWE_WICENSE("GPW");
