// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8750.c -- WM8750 AWSA SoC audio dwivew
 *
 * Copywight 2005 Openedhand Wtd.
 *
 * Authow: Wichawd Puwdie <wichawd@openedhand.com>
 *
 * Based on WM8753.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude "wm8750.h"

/*
 * wm8750 wegistew cache
 * We can't wead the WM8750 wegistew space when we
 * awe using 2 wiwe fow device contwow, so we cache them instead.
 */
static const stwuct weg_defauwt wm8750_weg_defauwts[] = {
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

/* codec pwivate data */
stwuct wm8750_pwiv {
	unsigned int syscwk;
};

#define wm8750_weset(c)	snd_soc_component_wwite(c, WM8750_WESET, 0)

/*
 * WM8750 Contwows
 */
static const chaw *wm8750_bass[] = {"Wineaw Contwow", "Adaptive Boost"};
static const chaw *wm8750_bass_fiwtew[] = { "130Hz @ 48kHz", "200Hz @ 48kHz" };
static const chaw *wm8750_twebwe[] = {"8kHz", "4kHz"};
static const chaw *wm8750_3d_wc[] = {"200Hz", "500Hz"};
static const chaw *wm8750_3d_uc[] = {"2.2kHz", "1.5kHz"};
static const chaw *wm8750_3d_func[] = {"Captuwe", "Pwayback"};
static const chaw *wm8750_awc_func[] = {"Off", "Wight", "Weft", "Steweo"};
static const chaw *wm8750_ng_type[] = {"Constant PGA Gain",
	"Mute ADC Output"};
static const chaw *wm8750_wine_mux[] = {"Wine 1", "Wine 2", "Wine 3", "PGA",
	"Diffewentiaw"};
static const chaw *wm8750_pga_sew[] = {"Wine 1", "Wine 2", "Wine 3",
	"Diffewentiaw"};
static const chaw *wm8750_out3[] = {"VWEF", "WOUT1 + Vow", "MonoOut",
	"WOUT1"};
static const chaw *wm8750_diff_sew[] = {"Wine 1", "Wine 2"};
static const chaw *wm8750_adcpow[] = {"Nowmaw", "W Invewt", "W Invewt",
	"W + W Invewt"};
static const chaw *wm8750_deemph[] = {"None", "32Khz", "44.1Khz", "48Khz"};
static const chaw *wm8750_mono_mux[] = {"Steweo", "Mono (Weft)",
	"Mono (Wight)", "Digitaw Mono"};

static const stwuct soc_enum wm8750_enum[] = {
SOC_ENUM_SINGWE(WM8750_BASS, 7, 2, wm8750_bass),
SOC_ENUM_SINGWE(WM8750_BASS, 6, 2, wm8750_bass_fiwtew),
SOC_ENUM_SINGWE(WM8750_TWEBWE, 6, 2, wm8750_twebwe),
SOC_ENUM_SINGWE(WM8750_3D, 5, 2, wm8750_3d_wc),
SOC_ENUM_SINGWE(WM8750_3D, 6, 2, wm8750_3d_uc),
SOC_ENUM_SINGWE(WM8750_3D, 7, 2, wm8750_3d_func),
SOC_ENUM_SINGWE(WM8750_AWC1, 7, 4, wm8750_awc_func),
SOC_ENUM_SINGWE(WM8750_NGATE, 1, 2, wm8750_ng_type),
SOC_ENUM_SINGWE(WM8750_WOUTM1, 0, 5, wm8750_wine_mux),
SOC_ENUM_SINGWE(WM8750_WOUTM1, 0, 5, wm8750_wine_mux),
SOC_ENUM_SINGWE(WM8750_WADCIN, 6, 4, wm8750_pga_sew), /* 10 */
SOC_ENUM_SINGWE(WM8750_WADCIN, 6, 4, wm8750_pga_sew),
SOC_ENUM_SINGWE(WM8750_ADCTW2, 7, 4, wm8750_out3),
SOC_ENUM_SINGWE(WM8750_ADCIN, 8, 2, wm8750_diff_sew),
SOC_ENUM_SINGWE(WM8750_ADCDAC, 5, 4, wm8750_adcpow),
SOC_ENUM_SINGWE(WM8750_ADCDAC, 1, 4, wm8750_deemph),
SOC_ENUM_SINGWE(WM8750_ADCIN, 6, 4, wm8750_mono_mux), /* 16 */

};

static const stwuct snd_kcontwow_new wm8750_snd_contwows[] = {

SOC_DOUBWE_W("Captuwe Vowume", WM8750_WINVOW, WM8750_WINVOW, 0, 63, 0),
SOC_DOUBWE_W("Captuwe ZC Switch", WM8750_WINVOW, WM8750_WINVOW, 6, 1, 0),
SOC_DOUBWE_W("Captuwe Switch", WM8750_WINVOW, WM8750_WINVOW, 7, 1, 1),

SOC_DOUBWE_W("Headphone Pwayback ZC Switch", WM8750_WOUT1V,
	WM8750_WOUT1V, 7, 1, 0),
SOC_DOUBWE_W("Speakew Pwayback ZC Switch", WM8750_WOUT2V,
	WM8750_WOUT2V, 7, 1, 0),

SOC_ENUM("Pwayback De-emphasis", wm8750_enum[15]),

SOC_ENUM("Captuwe Powawity", wm8750_enum[14]),
SOC_SINGWE("Pwayback 6dB Attenuate", WM8750_ADCDAC, 7, 1, 0),
SOC_SINGWE("Captuwe 6dB Attenuate", WM8750_ADCDAC, 8, 1, 0),

SOC_DOUBWE_W("PCM Vowume", WM8750_WDAC, WM8750_WDAC, 0, 255, 0),

SOC_ENUM("Bass Boost", wm8750_enum[0]),
SOC_ENUM("Bass Fiwtew", wm8750_enum[1]),
SOC_SINGWE("Bass Vowume", WM8750_BASS, 0, 15, 1),

SOC_SINGWE("Twebwe Vowume", WM8750_TWEBWE, 0, 15, 1),
SOC_ENUM("Twebwe Cut-off", wm8750_enum[2]),

SOC_SINGWE("3D Switch", WM8750_3D, 0, 1, 0),
SOC_SINGWE("3D Vowume", WM8750_3D, 1, 15, 0),
SOC_ENUM("3D Wowew Cut-off", wm8750_enum[3]),
SOC_ENUM("3D Uppew Cut-off", wm8750_enum[4]),
SOC_ENUM("3D Mode", wm8750_enum[5]),

SOC_SINGWE("AWC Captuwe Tawget Vowume", WM8750_AWC1, 0, 7, 0),
SOC_SINGWE("AWC Captuwe Max Vowume", WM8750_AWC1, 4, 7, 0),
SOC_ENUM("AWC Captuwe Function", wm8750_enum[6]),
SOC_SINGWE("AWC Captuwe ZC Switch", WM8750_AWC2, 7, 1, 0),
SOC_SINGWE("AWC Captuwe Howd Time", WM8750_AWC2, 0, 15, 0),
SOC_SINGWE("AWC Captuwe Decay Time", WM8750_AWC3, 4, 15, 0),
SOC_SINGWE("AWC Captuwe Attack Time", WM8750_AWC3, 0, 15, 0),
SOC_SINGWE("AWC Captuwe NG Thweshowd", WM8750_NGATE, 3, 31, 0),
SOC_ENUM("AWC Captuwe NG Type", wm8750_enum[4]),
SOC_SINGWE("AWC Captuwe NG Switch", WM8750_NGATE, 0, 1, 0),

SOC_SINGWE("Weft ADC Captuwe Vowume", WM8750_WADC, 0, 255, 0),
SOC_SINGWE("Wight ADC Captuwe Vowume", WM8750_WADC, 0, 255, 0),

SOC_SINGWE("ZC Timeout Switch", WM8750_ADCTW1, 0, 1, 0),
SOC_SINGWE("Pwayback Invewt Switch", WM8750_ADCTW1, 1, 1, 0),

SOC_SINGWE("Wight Speakew Pwayback Invewt Switch", WM8750_ADCTW2, 4, 1, 0),

/* Unimpwemented */
/* ADCDAC Bit 0 - ADCHPD */
/* ADCDAC Bit 4 - HPOW */
/* ADCTW1 Bit 2,3 - DATSEW */
/* ADCTW1 Bit 4,5 - DMONOMIX */
/* ADCTW1 Bit 6,7 - VSEW */
/* ADCTW2 Bit 2 - WWCM */
/* ADCTW2 Bit 3 - TWI */
/* ADCTW3 Bit 5 - HPFWWEN */
/* ADCTW3 Bit 6 - VWOI */
/* ADCTW3 Bit 7,8 - ADCWWM */
/* ADCIN Bit 4 - WDCM */
/* ADCIN Bit 5 - WDCM */

SOC_DOUBWE_W("Mic Boost", WM8750_WADCIN, WM8750_WADCIN, 4, 3, 0),

SOC_DOUBWE_W("Bypass Weft Pwayback Vowume", WM8750_WOUTM1,
	WM8750_WOUTM2, 4, 7, 1),
SOC_DOUBWE_W("Bypass Wight Pwayback Vowume", WM8750_WOUTM1,
	WM8750_WOUTM2, 4, 7, 1),
SOC_DOUBWE_W("Bypass Mono Pwayback Vowume", WM8750_MOUTM1,
	WM8750_MOUTM2, 4, 7, 1),

SOC_SINGWE("Mono Pwayback ZC Switch", WM8750_MOUTV, 7, 1, 0),

SOC_DOUBWE_W("Headphone Pwayback Vowume", WM8750_WOUT1V, WM8750_WOUT1V,
	0, 127, 0),
SOC_DOUBWE_W("Speakew Pwayback Vowume", WM8750_WOUT2V, WM8750_WOUT2V,
	0, 127, 0),

SOC_SINGWE("Mono Pwayback Vowume", WM8750_MOUTV, 0, 127, 0),

};

/*
 * DAPM Contwows
 */

/* Weft Mixew */
static const stwuct snd_kcontwow_new wm8750_weft_mixew_contwows[] = {
SOC_DAPM_SINGWE("Pwayback Switch", WM8750_WOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Weft Bypass Switch", WM8750_WOUTM1, 7, 1, 0),
SOC_DAPM_SINGWE("Wight Pwayback Switch", WM8750_WOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Wight Bypass Switch", WM8750_WOUTM2, 7, 1, 0),
};

/* Wight Mixew */
static const stwuct snd_kcontwow_new wm8750_wight_mixew_contwows[] = {
SOC_DAPM_SINGWE("Weft Pwayback Switch", WM8750_WOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Weft Bypass Switch", WM8750_WOUTM1, 7, 1, 0),
SOC_DAPM_SINGWE("Pwayback Switch", WM8750_WOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Wight Bypass Switch", WM8750_WOUTM2, 7, 1, 0),
};

/* Mono Mixew */
static const stwuct snd_kcontwow_new wm8750_mono_mixew_contwows[] = {
SOC_DAPM_SINGWE("Weft Pwayback Switch", WM8750_MOUTM1, 8, 1, 0),
SOC_DAPM_SINGWE("Weft Bypass Switch", WM8750_MOUTM1, 7, 1, 0),
SOC_DAPM_SINGWE("Wight Pwayback Switch", WM8750_MOUTM2, 8, 1, 0),
SOC_DAPM_SINGWE("Wight Bypass Switch", WM8750_MOUTM2, 7, 1, 0),
};

/* Weft Wine Mux */
static const stwuct snd_kcontwow_new wm8750_weft_wine_contwows =
SOC_DAPM_ENUM("Woute", wm8750_enum[8]);

/* Wight Wine Mux */
static const stwuct snd_kcontwow_new wm8750_wight_wine_contwows =
SOC_DAPM_ENUM("Woute", wm8750_enum[9]);

/* Weft PGA Mux */
static const stwuct snd_kcontwow_new wm8750_weft_pga_contwows =
SOC_DAPM_ENUM("Woute", wm8750_enum[10]);

/* Wight PGA Mux */
static const stwuct snd_kcontwow_new wm8750_wight_pga_contwows =
SOC_DAPM_ENUM("Woute", wm8750_enum[11]);

/* Out 3 Mux */
static const stwuct snd_kcontwow_new wm8750_out3_contwows =
SOC_DAPM_ENUM("Woute", wm8750_enum[12]);

/* Diffewentiaw Mux */
static const stwuct snd_kcontwow_new wm8750_diffmux_contwows =
SOC_DAPM_ENUM("Woute", wm8750_enum[13]);

/* Mono ADC Mux */
static const stwuct snd_kcontwow_new wm8750_monomux_contwows =
SOC_DAPM_ENUM("Woute", wm8750_enum[16]);

static const stwuct snd_soc_dapm_widget wm8750_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Weft Mixew", SND_SOC_NOPM, 0, 0,
		&wm8750_weft_mixew_contwows[0],
		AWWAY_SIZE(wm8750_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Mixew", SND_SOC_NOPM, 0, 0,
		&wm8750_wight_mixew_contwows[0],
		AWWAY_SIZE(wm8750_wight_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Mono Mixew", WM8750_PWW2, 2, 0,
		&wm8750_mono_mixew_contwows[0],
		AWWAY_SIZE(wm8750_mono_mixew_contwows)),

	SND_SOC_DAPM_PGA("Wight Out 2", WM8750_PWW2, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft Out 2", WM8750_PWW2, 4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Out 1", WM8750_PWW2, 5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft Out 1", WM8750_PWW2, 6, 0, NUWW, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback", WM8750_PWW2, 7, 0),
	SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback", WM8750_PWW2, 8, 0),

	SND_SOC_DAPM_MICBIAS("Mic Bias", WM8750_PWW1, 1, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", WM8750_PWW1, 2, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", WM8750_PWW1, 3, 0),

	SND_SOC_DAPM_MUX("Weft PGA Mux", WM8750_PWW1, 5, 0,
		&wm8750_weft_pga_contwows),
	SND_SOC_DAPM_MUX("Wight PGA Mux", WM8750_PWW1, 4, 0,
		&wm8750_wight_pga_contwows),
	SND_SOC_DAPM_MUX("Weft Wine Mux", SND_SOC_NOPM, 0, 0,
		&wm8750_weft_wine_contwows),
	SND_SOC_DAPM_MUX("Wight Wine Mux", SND_SOC_NOPM, 0, 0,
		&wm8750_wight_wine_contwows),

	SND_SOC_DAPM_MUX("Out3 Mux", SND_SOC_NOPM, 0, 0, &wm8750_out3_contwows),
	SND_SOC_DAPM_PGA("Out 3", WM8750_PWW2, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mono Out 1", WM8750_PWW2, 2, 0, NUWW, 0),

	SND_SOC_DAPM_MUX("Diffewentiaw Mux", SND_SOC_NOPM, 0, 0,
		&wm8750_diffmux_contwows),
	SND_SOC_DAPM_MUX("Weft ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8750_monomux_contwows),
	SND_SOC_DAPM_MUX("Wight ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8750_monomux_contwows),

	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("MONO1"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_VMID("VWEF"),

	SND_SOC_DAPM_INPUT("WINPUT1"),
	SND_SOC_DAPM_INPUT("WINPUT2"),
	SND_SOC_DAPM_INPUT("WINPUT3"),
	SND_SOC_DAPM_INPUT("WINPUT1"),
	SND_SOC_DAPM_INPUT("WINPUT2"),
	SND_SOC_DAPM_INPUT("WINPUT3"),
};

static const stwuct snd_soc_dapm_woute wm8750_dapm_woutes[] = {
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
	{"Mono Out 1", NUWW, "Mono Mixew"},
	{"MONO1", NUWW, "Mono Out 1"},

	/* out 3 */
	{"Out3 Mux", "VWEF", "VWEF"},
	{"Out3 Mux", "WOUT1 + Vow", "WOUT1"},
	{"Out3 Mux", "WOUT1", "Wight Mixew"},
	{"Out3 Mux", "MonoOut", "MONO1"},
	{"Out 3", NUWW, "Out3 Mux"},
	{"OUT3", NUWW, "Out 3"},

	/* Weft Wine Mux */
	{"Weft Wine Mux", "Wine 1", "WINPUT1"},
	{"Weft Wine Mux", "Wine 2", "WINPUT2"},
	{"Weft Wine Mux", "Wine 3", "WINPUT3"},
	{"Weft Wine Mux", "PGA", "Weft PGA Mux"},
	{"Weft Wine Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Wight Wine Mux */
	{"Wight Wine Mux", "Wine 1", "WINPUT1"},
	{"Wight Wine Mux", "Wine 2", "WINPUT2"},
	{"Wight Wine Mux", "Wine 3", "WINPUT3"},
	{"Wight Wine Mux", "PGA", "Wight PGA Mux"},
	{"Wight Wine Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Weft PGA Mux */
	{"Weft PGA Mux", "Wine 1", "WINPUT1"},
	{"Weft PGA Mux", "Wine 2", "WINPUT2"},
	{"Weft PGA Mux", "Wine 3", "WINPUT3"},
	{"Weft PGA Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Wight PGA Mux */
	{"Wight PGA Mux", "Wine 1", "WINPUT1"},
	{"Wight PGA Mux", "Wine 2", "WINPUT2"},
	{"Wight PGA Mux", "Wine 3", "WINPUT3"},
	{"Wight PGA Mux", "Diffewentiaw", "Diffewentiaw Mux"},

	/* Diffewentiaw Mux */
	{"Diffewentiaw Mux", "Wine 1", "WINPUT1"},
	{"Diffewentiaw Mux", "Wine 1", "WINPUT1"},
	{"Diffewentiaw Mux", "Wine 2", "WINPUT2"},
	{"Diffewentiaw Mux", "Wine 2", "WINPUT2"},

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

static inwine int get_coeff(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].wate == wate && coeff_div[i].mcwk == mcwk)
			wetuwn i;
	}

	pwintk(KEWN_EWW "wm8750: couwd not get coeff fow mcwk %d @ wate %d\n",
		mcwk, wate);
	wetuwn -EINVAW;
}

static int wm8750_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8750_pwiv *wm8750 = snd_soc_component_get_dwvdata(component);

	switch (fweq) {
	case 11289600:
	case 12000000:
	case 12288000:
	case 16934400:
	case 18432000:
		wm8750->syscwk = fweq;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int wm8750_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
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

	snd_soc_component_wwite(component, WM8750_IFACE, iface);
	wetuwn 0;
}

static int wm8750_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8750_pwiv *wm8750 = snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8750_IFACE) & 0x1f3;
	u16 swate = snd_soc_component_wead(component, WM8750_SWATE) & 0x1c0;
	int coeff = get_coeff(wm8750->syscwk, pawams_wate(pawams));

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
	snd_soc_component_wwite(component, WM8750_IFACE, iface);
	if (coeff >= 0)
		snd_soc_component_wwite(component, WM8750_SWATE, swate |
			(coeff_div[coeff].sw << 1) | coeff_div[coeff].usb);

	wetuwn 0;
}

static int wm8750_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8750_ADCDAC) & 0xfff7;

	if (mute)
		snd_soc_component_wwite(component, WM8750_ADCDAC, mute_weg | 0x8);
	ewse
		snd_soc_component_wwite(component, WM8750_ADCDAC, mute_weg);
	wetuwn 0;
}

static int wm8750_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	u16 pww_weg = snd_soc_component_wead(component, WM8750_PWW1) & 0xfe3e;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* set vmid to 50k and unmute dac */
		snd_soc_component_wwite(component, WM8750_PWW1, pww_weg | 0x00c0);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			snd_soc_component_cache_sync(component);

			/* Set VMID to 5k */
			snd_soc_component_wwite(component, WM8750_PWW1, pww_weg | 0x01c1);

			/* ...and wamp */
			msweep(1000);
		}

		/* mute dac and set vmid to 500k, enabwe VWEF */
		snd_soc_component_wwite(component, WM8750_PWW1, pww_weg | 0x0141);
		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WM8750_PWW1, 0x0001);
		bweak;
	}
	wetuwn 0;
}

#define WM8750_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
	SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 | SNDWV_PCM_WATE_44100 | \
	SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000)

#define WM8750_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm8750_dai_ops = {
	.hw_pawams	= wm8750_pcm_hw_pawams,
	.mute_stweam	= wm8750_mute,
	.set_fmt	= wm8750_set_dai_fmt,
	.set_syscwk	= wm8750_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8750_dai = {
	.name = "wm8750-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8750_WATES,
		.fowmats = WM8750_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8750_WATES,
		.fowmats = WM8750_FOWMATS,},
	.ops = &wm8750_dai_ops,
};

static int wm8750_pwobe(stwuct snd_soc_component *component)
{
	int wet;

	wet = wm8750_weset(component);
	if (wet < 0) {
		pwintk(KEWN_EWW "wm8750: faiwed to weset: %d\n", wet);
		wetuwn wet;
	}

	/* set the update bits */
	snd_soc_component_update_bits(component, WM8750_WDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8750_WDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8750_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8750_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8750_WOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8750_WOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8750_WINVOW, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8750_WINVOW, 0x0100, 0x0100);

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8750 = {
	.pwobe			= wm8750_pwobe,
	.set_bias_wevew		= wm8750_set_bias_wevew,
	.contwows		= wm8750_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8750_snd_contwows),
	.dapm_widgets		= wm8750_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8750_dapm_widgets),
	.dapm_woutes		= wm8750_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8750_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8750_of_match[] = {
	{ .compatibwe = "wwf,wm8750", },
	{ .compatibwe = "wwf,wm8987", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8750_of_match);

static const stwuct wegmap_config wm8750_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8750_MOUTV,

	.weg_defauwts = wm8750_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8750_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
};

#if defined(CONFIG_SPI_MASTEW)
static int wm8750_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8750_pwiv *wm8750;
	stwuct wegmap *wegmap;
	int wet;

	wm8750 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8750_pwiv),
			      GFP_KEWNEW);
	if (wm8750 == NUWW)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_spi(spi, &wm8750_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	spi_set_dwvdata(spi, wm8750);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_dev_wm8750, &wm8750_dai, 1);
	wetuwn wet;
}

static const stwuct spi_device_id wm8750_spi_ids[] = {
	{ "wm8750", 0 },
	{ "wm8987", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, wm8750_spi_ids);

static stwuct spi_dwivew wm8750_spi_dwivew = {
	.dwivew = {
		.name	= "wm8750",
		.of_match_tabwe = wm8750_of_match,
	},
	.id_tabwe	= wm8750_spi_ids,
	.pwobe		= wm8750_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

#if IS_ENABWED(CONFIG_I2C)
static int wm8750_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8750_pwiv *wm8750;
	stwuct wegmap *wegmap;
	int wet;

	wm8750 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8750_pwiv),
			      GFP_KEWNEW);
	if (wm8750 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wm8750);

	wegmap = devm_wegmap_init_i2c(i2c, &wm8750_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8750, &wm8750_dai, 1);
	wetuwn wet;
}

static const stwuct i2c_device_id wm8750_i2c_id[] = {
	{ "wm8750", 0 },
	{ "wm8987", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8750_i2c_id);

static stwuct i2c_dwivew wm8750_i2c_dwivew = {
	.dwivew = {
		.name = "wm8750",
		.of_match_tabwe = wm8750_of_match,
	},
	.pwobe = wm8750_i2c_pwobe,
	.id_tabwe = wm8750_i2c_id,
};
#endif

static int __init wm8750_modinit(void)
{
	int wet = 0;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8750_i2c_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8750 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8750_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8750 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn wet;
}
moduwe_init(wm8750_modinit);

static void __exit wm8750_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8750_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8750_spi_dwivew);
#endif
}
moduwe_exit(wm8750_exit);

MODUWE_DESCWIPTION("ASoC WM8750 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
