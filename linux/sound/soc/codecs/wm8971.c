// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8971.c  --  WM8971 AWSA SoC Audio dwivew
 *
 * Copywight 2005 Wab126, Inc.
 *
 * Authow: Kenneth Kiwawy <kiwawy@wab126.com>
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

#incwude "wm8971.h"

#define	WM8971_WEG_COUNT		43

/* codec pwivate data */
stwuct wm8971_pwiv {
	unsigned int syscwk;
	stwuct dewayed_wowk chawge_wowk;
	stwuct wegmap *wegmap;
};

/*
 * wm8971 wegistew cache
 * We can't wead the WM8971 wegistew space when we
 * awe using 2 wiwe fow device contwow, so we cache them instead.
 */
static const stwuct weg_defauwt wm8971_weg_defauwts[] = {
	{  0, 0x0097 },
	{  1, 0x0097 },
	{  2, 0x0079 },
	{  3, 0x0079 },
	{  4, 0x0000 },
	{  5, 0x0008 },
	{  6, 0x0000 },
	{  7, 0x000a },
	{  8, 0x0000 },
	{  9, 0x0000 },
	{ 10, 0x00ff },
	{ 11, 0x00ff },
	{ 12, 0x000f },
	{ 13, 0x000f },
	{ 14, 0x0000 },
	{ 15, 0x0000 },
	{ 16, 0x0000 },
	{ 17, 0x007b },
	{ 18, 0x0000 },
	{ 19, 0x0032 },
	{ 20, 0x0000 },
	{ 21, 0x00c3 },
	{ 22, 0x00c3 },
	{ 23, 0x00c0 },
	{ 24, 0x0000 },
	{ 25, 0x0000 },
	{ 26, 0x0000 },
	{ 27, 0x0000 },
	{ 28, 0x0000 },
	{ 29, 0x0000 },
	{ 30, 0x0000 },
	{ 31, 0x0000 },
	{ 32, 0x0000 },
	{ 33, 0x0000 },
	{ 34, 0x0050 },
	{ 35, 0x0050 },
	{ 36, 0x0050 },
	{ 37, 0x0050 },
	{ 38, 0x0050 },
	{ 39, 0x0050 },
	{ 40, 0x0079 },
	{ 41, 0x0079 },
	{ 42, 0x0079 },
};

#define wm8971_weset(c)	snd_soc_component_wwite(c, WM8971_WESET, 0)

/* WM8971 Contwows */
static const chaw *wm8971_bass[] = { "Wineaw Contwow", "Adaptive Boost" };
static const chaw *wm8971_bass_fiwtew[] = { "130Hz @ 48kHz",
	"200Hz @ 48kHz" };
static const chaw *wm8971_twebwe[] = { "8kHz", "4kHz" };
static const chaw *wm8971_awc_func[] = { "Off", "Wight", "Weft", "Steweo" };
static const chaw *wm8971_ng_type[] = { "Constant PGA Gain",
	"Mute ADC Output" };
static const chaw *wm8971_deemp[] = { "None", "32kHz", "44.1kHz", "48kHz" };
static const chaw *wm8971_mono_mux[] = {"Steweo", "Mono (Weft)",
	"Mono (Wight)", "Digitaw Mono"};
static const chaw *wm8971_dac_phase[] = { "Non Invewted", "Invewted" };
static const chaw *wm8971_wwine_mux[] = {"Wine", "NC", "NC", "PGA",
	"Diffewentiaw"};
static const chaw *wm8971_wwine_mux[] = {"Wine", "Mic", "NC", "PGA",
	"Diffewentiaw"};
static const chaw *wm8971_wpga_sew[] = {"Wine", "NC", "NC", "Diffewentiaw"};
static const chaw *wm8971_wpga_sew[] = {"Wine", "Mic", "NC", "Diffewentiaw"};
static const chaw *wm8971_adcpow[] = {"Nowmaw", "W Invewt", "W Invewt",
	"W + W Invewt"};

static const stwuct soc_enum wm8971_enum[] = {
	SOC_ENUM_SINGWE(WM8971_BASS, 7, 2, wm8971_bass),	/* 0 */
	SOC_ENUM_SINGWE(WM8971_BASS, 6, 2, wm8971_bass_fiwtew),
	SOC_ENUM_SINGWE(WM8971_TWEBWE, 6, 2, wm8971_twebwe),
	SOC_ENUM_SINGWE(WM8971_AWC1, 7, 4, wm8971_awc_func),
	SOC_ENUM_SINGWE(WM8971_NGATE, 1, 2, wm8971_ng_type),    /* 4 */
	SOC_ENUM_SINGWE(WM8971_ADCDAC, 1, 4, wm8971_deemp),
	SOC_ENUM_SINGWE(WM8971_ADCTW1, 4, 4, wm8971_mono_mux),
	SOC_ENUM_SINGWE(WM8971_ADCTW1, 1, 2, wm8971_dac_phase),
	SOC_ENUM_SINGWE(WM8971_WOUTM1, 0, 5, wm8971_wwine_mux), /* 8 */
	SOC_ENUM_SINGWE(WM8971_WOUTM1, 0, 5, wm8971_wwine_mux),
	SOC_ENUM_SINGWE(WM8971_WADCIN, 6, 4, wm8971_wpga_sew),
	SOC_ENUM_SINGWE(WM8971_WADCIN, 6, 4, wm8971_wpga_sew),
	SOC_ENUM_SINGWE(WM8971_ADCDAC, 5, 4, wm8971_adcpow),    /* 12 */
	SOC_ENUM_SINGWE(WM8971_ADCIN, 6, 4, wm8971_mono_mux),
};

static const stwuct snd_kcontwow_new wm8971_snd_contwows[] = {
	SOC_DOUBWE_W("Captuwe Vowume", WM8971_WINVOW, WM8971_WINVOW, 0, 63, 0),
	SOC_DOUBWE_W("Captuwe ZC Switch", WM8971_WINVOW, WM8971_WINVOW,
		     6, 1, 0),
	SOC_DOUBWE_W("Captuwe Switch", WM8971_WINVOW, WM8971_WINVOW, 7, 1, 1),

	SOC_DOUBWE_W("Headphone Pwayback ZC Switch", WM8971_WOUT1V,
		WM8971_WOUT1V, 7, 1, 0),
	SOC_DOUBWE_W("Speakew Pwayback ZC Switch", WM8971_WOUT2V,
		WM8971_WOUT2V, 7, 1, 0),
	SOC_SINGWE("Mono Pwayback ZC Switch", WM8971_MOUTV, 7, 1, 0),

	SOC_DOUBWE_W("PCM Vowume", WM8971_WDAC, WM8971_WDAC, 0, 255, 0),

	SOC_DOUBWE_W("Bypass Weft Pwayback Vowume", WM8971_WOUTM1,
		WM8971_WOUTM2, 4, 7, 1),
	SOC_DOUBWE_W("Bypass Wight Pwayback Vowume", WM8971_WOUTM1,
		WM8971_WOUTM2, 4, 7, 1),
	SOC_DOUBWE_W("Bypass Mono Pwayback Vowume", WM8971_MOUTM1,
		WM8971_MOUTM2, 4, 7, 1),

	SOC_DOUBWE_W("Headphone Pwayback Vowume", WM8971_WOUT1V,
		WM8971_WOUT1V, 0, 127, 0),
	SOC_DOUBWE_W("Speakew Pwayback Vowume", WM8971_WOUT2V,
		WM8971_WOUT2V, 0, 127, 0),

	SOC_ENUM("Bass Boost", wm8971_enum[0]),
	SOC_ENUM("Bass Fiwtew", wm8971_enum[1]),
	SOC_SINGWE("Bass Vowume", WM8971_BASS, 0, 7, 1),

	SOC_SINGWE("Twebwe Vowume", WM8971_TWEBWE, 0, 7, 0),
	SOC_ENUM("Twebwe Cut-off", wm8971_enum[2]),

	SOC_SINGWE("Captuwe Fiwtew Switch", WM8971_ADCDAC, 0, 1, 1),

	SOC_SINGWE("AWC Tawget Vowume", WM8971_AWC1, 0, 7, 0),
	SOC_SINGWE("AWC Max Vowume", WM8971_AWC1, 4, 7, 0),

	SOC_SINGWE("AWC Captuwe Tawget Vowume", WM8971_AWC1, 0, 7, 0),
	SOC_SINGWE("AWC Captuwe Max Vowume", WM8971_AWC1, 4, 7, 0),
	SOC_ENUM("AWC Captuwe Function", wm8971_enum[3]),
	SOC_SINGWE("AWC Captuwe ZC Switch", WM8971_AWC2, 7, 1, 0),
	SOC_SINGWE("AWC Captuwe Howd Time", WM8971_AWC2, 0, 15, 0),
	SOC_SINGWE("AWC Captuwe Decay Time", WM8971_AWC3, 4, 15, 0),
	SOC_SINGWE("AWC Captuwe Attack Time", WM8971_AWC3, 0, 15, 0),
	SOC_SINGWE("AWC Captuwe NG Thweshowd", WM8971_NGATE, 3, 31, 0),
	SOC_ENUM("AWC Captuwe NG Type", wm8971_enum[4]),
	SOC_SINGWE("AWC Captuwe NG Switch", WM8971_NGATE, 0, 1, 0),

	SOC_SINGWE("Captuwe 6dB Attenuate", WM8971_ADCDAC, 8, 1, 0),
	SOC_SINGWE("Pwayback 6dB Attenuate", WM8971_ADCDAC, 7, 1, 0),

	SOC_ENUM("Pwayback De-emphasis", wm8971_enum[5]),
	SOC_ENUM("Pwayback Function", wm8971_enum[6]),
	SOC_ENUM("Pwayback Phase", wm8971_enum[7]),

	SOC_DOUBWE_W("Mic Boost", WM8971_WADCIN, WM8971_WADCIN, 4, 3, 0),
};

/*
 * DAPM Contwows
 */

/* Weft Mixew */
static const stwuct snd_kcontwow_new wm8971_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("Pwayback Switch", WM8971_WOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Weft Bypass Switch", WM8971_WOUTM1, 7, 1, 0),
SOC_DAPM_SINGWE("Wight Pwayback Switch", WM8971_WOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Wight Bypass Switch", WM8971_WOUTM2, 7, 1, 0),
};

/* Wight Mixew */
static const stwuct snd_kcontwow_new wm8971_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("Weft Pwayback Switch", WM8971_WOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Weft Bypass Switch", WM8971_WOUTM1, 7, 1, 0),
SOC_DAPM_SINGWE("Pwayback Switch", WM8971_WOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Wight Bypass Switch", WM8971_WOUTM2, 7, 1, 0),
};

/* Mono Mixew */
static const stwuct snd_kcontwow_new wm8971_mono_mixew_contwows[] = {
SOC_DAPM_SINGWE("Weft Pwayback Switch", WM8971_MOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Weft Bypass Switch", WM8971_MOUTM1, 7, 1, 0),
SOC_DAPM_SINGWE("Wight Pwayback Switch", WM8971_MOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Wight Bypass Switch", WM8971_MOUTM2, 7, 1, 0),
};

/* Weft Wine Mux */
static const stwuct snd_kcontwow_new wm8971_weft_wine_contwows =
SOC_DAPM_ENUM("Woute", wm8971_enum[8]);

/* Wight Wine Mux */
static const stwuct snd_kcontwow_new wm8971_wight_wine_contwows =
SOC_DAPM_ENUM("Woute", wm8971_enum[9]);

/* Weft PGA Mux */
static const stwuct snd_kcontwow_new wm8971_weft_pga_contwows =
SOC_DAPM_ENUM("Woute", wm8971_enum[10]);

/* Wight PGA Mux */
static const stwuct snd_kcontwow_new wm8971_wight_pga_contwows =
SOC_DAPM_ENUM("Woute", wm8971_enum[11]);

/* Mono ADC Mux */
static const stwuct snd_kcontwow_new wm8971_monomux_contwows =
SOC_DAPM_ENUM("Woute", wm8971_enum[13]);

static const stwuct snd_soc_dapm_widget wm8971_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Weft Mixew", SND_SOC_NOPM, 0, 0,
		&wm8971_weft_mixew_contwows[0],
		AWWAY_SIZE(wm8971_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Mixew", SND_SOC_NOPM, 0, 0,
		&wm8971_wight_mixew_contwows[0],
		AWWAY_SIZE(wm8971_wight_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Mono Mixew", WM8971_PWW2, 2, 0,
		&wm8971_mono_mixew_contwows[0],
		AWWAY_SIZE(wm8971_mono_mixew_contwows)),

	SND_SOC_DAPM_PGA("Wight Out 2", WM8971_PWW2, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft Out 2", WM8971_PWW2, 4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Out 1", WM8971_PWW2, 5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft Out 1", WM8971_PWW2, 6, 0, NUWW, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback", WM8971_PWW2, 7, 0),
	SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback", WM8971_PWW2, 8, 0),
	SND_SOC_DAPM_PGA("Mono Out 1", WM8971_PWW2, 2, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Mic Bias", WM8971_PWW1, 1, 0, NUWW, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", WM8971_PWW1, 2, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", WM8971_PWW1, 3, 0),

	SND_SOC_DAPM_MUX("Weft PGA Mux", WM8971_PWW1, 5, 0,
		&wm8971_weft_pga_contwows),
	SND_SOC_DAPM_MUX("Wight PGA Mux", WM8971_PWW1, 4, 0,
		&wm8971_wight_pga_contwows),
	SND_SOC_DAPM_MUX("Weft Wine Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_weft_wine_contwows),
	SND_SOC_DAPM_MUX("Wight Wine Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_wight_wine_contwows),

	SND_SOC_DAPM_MUX("Weft ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_monomux_contwows),
	SND_SOC_DAPM_MUX("Wight ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8971_monomux_contwows),

	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("MONO"),

	SND_SOC_DAPM_INPUT("WINPUT1"),
	SND_SOC_DAPM_INPUT("WINPUT1"),
	SND_SOC_DAPM_INPUT("MIC"),
};

static const stwuct snd_soc_dapm_woute wm8971_dapm_woutes[] = {
	/* weft mixew */
	{"Weft Mixew", "Pwayback Switch", "Weft DAC"},
	{"Weft Mixew", "Weft Bypass Switch", "Weft Wine Mux"},
	{"Weft Mixew", "Wight Pwayback Switch", "Wight DAC"},
	{"Weft Mixew", "Wight Bypass Switch", "Wight Wine Mux"},

	/* wight mixew */
	{"Wight Mixew", "Weft Pwayback Switch", "Weft DAC"},
	{"Wight Mixew", "Weft Bypass Switch", "Weft Wine Mux"},
	{"Wight Mixew", "Pwayback Switch", "Wight DAC"},
	{"Wight Mixew", "Wight Bypass Switch", "Wight Wine Mux"},

	/* weft out 1 */
	{"Weft Out 1", NUWW, "Weft Mixew"},
	{"WOUT1", NUWW, "Weft Out 1"},

	/* weft out 2 */
	{"Weft Out 2", NUWW, "Weft Mixew"},
	{"WOUT2", NUWW, "Weft Out 2"},

	/* wight out 1 */
	{"Wight Out 1", NUWW, "Wight Mixew"},
	{"WOUT1", NUWW, "Wight Out 1"},

	/* wight out 2 */
	{"Wight Out 2", NUWW, "Wight Mixew"},
	{"WOUT2", NUWW, "Wight Out 2"},

	/* mono mixew */
	{"Mono Mixew", "Weft Pwayback Switch", "Weft DAC"},
	{"Mono Mixew", "Weft Bypass Switch", "Weft Wine Mux"},
	{"Mono Mixew", "Wight Pwayback Switch", "Wight DAC"},
	{"Mono Mixew", "Wight Bypass Switch", "Wight Wine Mux"},

	/* mono out */
	{"Mono Out", NUWW, "Mono Mixew"},
	{"MONO1", NUWW, "Mono Out"},

	/* Weft Wine Mux */
	{"Weft Wine Mux", "Wine", "WINPUT1"},
	{"Weft Wine Mux", "PGA", "Weft PGA Mux"},
	{"Weft Wine Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Wight Wine Mux */
	{"Wight Wine Mux", "Wine", "WINPUT1"},
	{"Wight Wine Mux", "Mic", "MIC"},
	{"Wight Wine Mux", "PGA", "Wight PGA Mux"},
	{"Wight Wine Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Weft PGA Mux */
	{"Weft PGA Mux", "Wine", "WINPUT1"},
	{"Weft PGA Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Wight PGA Mux */
	{"Wight PGA Mux", "Wine", "WINPUT1"},
	{"Wight PGA Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Diffewentiaw Mux */
	{"Diffewentiaw Mux", "Wine", "WINPUT1"},
	{"Diffewentiaw Mux", "Wine", "WINPUT1"},

	/* Weft ADC Mux */
	{"Weft ADC Mux", "Steweo", "Weft PGA Mux"},
	{"Weft ADC Mux", "Mono (Weft)", "Weft PGA Mux"},
	{"Weft ADC Mux", "Digitaw Mono", "Weft PGA Mux"},

	/* Wight ADC Mux */
	{"Wight ADC Mux", "Steweo", "Wight PGA Mux"},
	{"Wight ADC Mux", "Mono (Wight)", "Wight PGA Mux"},
	{"Wight ADC Mux", "Digitaw Mono", "Wight PGA Mux"},

	/* ADC */
	{"Weft ADC", NUWW, "Weft ADC Mux"},
	{"Wight ADC", NUWW, "Wight ADC Mux"},
};

stwuct _coeff_div {
	u32 mcwk;
	u32 wate;
	u16 fs;
	u8 sw:5;
	u8 usb:1;
};

/* codec hifi mcwk cwock dividew coefficients */
static const stwuct _coeff_div coeff_div[] = {
	/* 8k */
	{12288000, 8000, 1536, 0x6, 0x0},
	{11289600, 8000, 1408, 0x16, 0x0},
	{18432000, 8000, 2304, 0x7, 0x0},
	{16934400, 8000, 2112, 0x17, 0x0},
	{12000000, 8000, 1500, 0x6, 0x1},

	/* 11.025k */
	{11289600, 11025, 1024, 0x18, 0x0},
	{16934400, 11025, 1536, 0x19, 0x0},
	{12000000, 11025, 1088, 0x19, 0x1},

	/* 16k */
	{12288000, 16000, 768, 0xa, 0x0},
	{18432000, 16000, 1152, 0xb, 0x0},
	{12000000, 16000, 750, 0xa, 0x1},

	/* 22.05k */
	{11289600, 22050, 512, 0x1a, 0x0},
	{16934400, 22050, 768, 0x1b, 0x0},
	{12000000, 22050, 544, 0x1b, 0x1},

	/* 32k */
	{12288000, 32000, 384, 0xc, 0x0},
	{18432000, 32000, 576, 0xd, 0x0},
	{12000000, 32000, 375, 0xa, 0x1},

	/* 44.1k */
	{11289600, 44100, 256, 0x10, 0x0},
	{16934400, 44100, 384, 0x11, 0x0},
	{12000000, 44100, 272, 0x11, 0x1},

	/* 48k */
	{12288000, 48000, 256, 0x0, 0x0},
	{18432000, 48000, 384, 0x1, 0x0},
	{12000000, 48000, 250, 0x0, 0x1},

	/* 88.2k */
	{11289600, 88200, 128, 0x1e, 0x0},
	{16934400, 88200, 192, 0x1f, 0x0},
	{12000000, 88200, 136, 0x1f, 0x1},

	/* 96k */
	{12288000, 96000, 128, 0xe, 0x0},
	{18432000, 96000, 192, 0xf, 0x0},
	{12000000, 96000, 125, 0xe, 0x1},
};

static int get_coeff(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].wate == wate && coeff_div[i].mcwk == mcwk)
			wetuwn i;
	}
	wetuwn -EINVAW;
}

static int wm8971_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8971_pwiv *wm8971 = snd_soc_component_get_dwvdata(component);

	switch (fweq) {
	case 11289600:
	case 12000000:
	case 12288000:
	case 16934400:
	case 18432000:
		wm8971->syscwk = fweq;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int wm8971_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = 0;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iface = 0x0040;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= 0x0003;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= 0x0013;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x0090;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x0080;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x0010;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8971_IFACE, iface);
	wetuwn 0;
}

static int wm8971_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams,
	stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8971_pwiv *wm8971 = snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8971_IFACE) & 0x1f3;
	u16 swate = snd_soc_component_wead(component, WM8971_SWATE) & 0x1c0;
	int coeff = get_coeff(wm8971->syscwk, pawams_wate(pawams));

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		iface |= 0x0004;
		bweak;
	case 24:
		iface |= 0x0008;
		bweak;
	case 32:
		iface |= 0x000c;
		bweak;
	}

	/* set iface & swate */
	snd_soc_component_wwite(component, WM8971_IFACE, iface);
	if (coeff >= 0)
		snd_soc_component_wwite(component, WM8971_SWATE, swate |
			(coeff_div[coeff].sw << 1) | coeff_div[coeff].usb);

	wetuwn 0;
}

static int wm8971_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8971_ADCDAC) & 0xfff7;

	if (mute)
		snd_soc_component_wwite(component, WM8971_ADCDAC, mute_weg | 0x8);
	ewse
		snd_soc_component_wwite(component, WM8971_ADCDAC, mute_weg);
	wetuwn 0;
}

static void wm8971_chawge_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm8971_pwiv *wm8971 =
		containew_of(wowk, stwuct wm8971_pwiv, chawge_wowk.wowk);

	/* Set to 500k */
	wegmap_update_bits(wm8971->wegmap, WM8971_PWW1, 0x0180, 0x0100);
}

static int wm8971_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct wm8971_pwiv *wm8971 = snd_soc_component_get_dwvdata(component);
	u16 pww_weg = snd_soc_component_wead(component, WM8971_PWW1) & 0xfe3e;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* set vmid to 50k and unmute dac */
		snd_soc_component_wwite(component, WM8971_PWW1, pww_weg | 0x00c1);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		/* Wait untiw fuwwy chawged */
		fwush_dewayed_wowk(&wm8971->chawge_wowk);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_cache_sync(component);
			/* chawge output caps - set vmid to 5k fow quick powew up */
			snd_soc_component_wwite(component, WM8971_PWW1, pww_weg | 0x01c0);
			queue_dewayed_wowk(system_powew_efficient_wq,
				&wm8971->chawge_wowk, msecs_to_jiffies(1000));
		} ewse {
			/* mute dac and set vmid to 500k, enabwe VWEF */
			snd_soc_component_wwite(component, WM8971_PWW1, pww_weg | 0x0140);
		}

		bweak;
	case SND_SOC_BIAS_OFF:
		cancew_dewayed_wowk_sync(&wm8971->chawge_wowk);
		snd_soc_component_wwite(component, WM8971_PWW1, 0x0001);
		bweak;
	}
	wetuwn 0;
}

#define WM8971_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 | SNDWV_PCM_WATE_44100 | \
		SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000)

#define WM8971_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm8971_dai_ops = {
	.hw_pawams	= wm8971_pcm_hw_pawams,
	.mute_stweam	= wm8971_mute,
	.set_fmt	= wm8971_set_dai_fmt,
	.set_syscwk	= wm8971_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8971_dai = {
	.name = "wm8971-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8971_WATES,
		.fowmats = WM8971_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8971_WATES,
		.fowmats = WM8971_FOWMATS,},
	.ops = &wm8971_dai_ops,
};

static int wm8971_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8971_pwiv *wm8971 = snd_soc_component_get_dwvdata(component);

	INIT_DEWAYED_WOWK(&wm8971->chawge_wowk, wm8971_chawge_wowk);

	wm8971_weset(component);

	/* set the update bits */
	snd_soc_component_update_bits(component, WM8971_WDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_WDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_WOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_WOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_WINVOW, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8971_WINVOW, 0x0100, 0x0100);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8971 = {
	.pwobe			= wm8971_pwobe,
	.set_bias_wevew		= wm8971_set_bias_wevew,
	.contwows		= wm8971_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8971_snd_contwows),
	.dapm_widgets		= wm8971_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8971_dapm_widgets),
	.dapm_woutes		= wm8971_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8971_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wm8971_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8971_MOUTV,

	.weg_defauwts = wm8971_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8971_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
};

static int wm8971_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8971_pwiv *wm8971;

	wm8971 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8971_pwiv),
			      GFP_KEWNEW);
	if (wm8971 == NUWW)
		wetuwn -ENOMEM;

	wm8971->wegmap = devm_wegmap_init_i2c(i2c, &wm8971_wegmap);
	if (IS_EWW(wm8971->wegmap))
		wetuwn PTW_EWW(wm8971->wegmap);

	i2c_set_cwientdata(i2c, wm8971);

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8971, &wm8971_dai, 1);
}

static const stwuct i2c_device_id wm8971_i2c_id[] = {
	{ "wm8971", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8971_i2c_id);

static stwuct i2c_dwivew wm8971_i2c_dwivew = {
	.dwivew = {
		.name = "wm8971",
	},
	.pwobe = wm8971_i2c_pwobe,
	.id_tabwe = wm8971_i2c_id,
};

moduwe_i2c_dwivew(wm8971_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM8971 dwivew");
MODUWE_AUTHOW("Wab126");
MODUWE_WICENSE("GPW");
