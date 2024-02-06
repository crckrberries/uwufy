// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8974.c  --  WM8974 AWSA Soc Audio dwivew
 *
 * Copywight 2006-2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Wiam Giwdwood <Wiam.Giwdwood@wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
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
#incwude <sound/twv.h>

#incwude "wm8974.h"

stwuct wm8974_pwiv {
	unsigned int mcwk;
	unsigned int fs;
};

static const stwuct weg_defauwt wm8974_weg_defauwts[] = {
	{  0, 0x0000 }, {  1, 0x0000 }, {  2, 0x0000 }, {  3, 0x0000 },
	{  4, 0x0050 }, {  5, 0x0000 }, {  6, 0x0140 }, {  7, 0x0000 },
	{  8, 0x0000 }, {  9, 0x0000 }, { 10, 0x0000 }, { 11, 0x00ff },
	{ 12, 0x0000 }, { 13, 0x0000 }, { 14, 0x0100 }, { 15, 0x00ff },
	{ 16, 0x0000 }, { 17, 0x0000 }, { 18, 0x012c }, { 19, 0x002c },
	{ 20, 0x002c }, { 21, 0x002c }, { 22, 0x002c }, { 23, 0x0000 },
	{ 24, 0x0032 }, { 25, 0x0000 }, { 26, 0x0000 }, { 27, 0x0000 },
	{ 28, 0x0000 }, { 29, 0x0000 }, { 30, 0x0000 }, { 31, 0x0000 },
	{ 32, 0x0038 }, { 33, 0x000b }, { 34, 0x0032 }, { 35, 0x0000 },
	{ 36, 0x0008 }, { 37, 0x000c }, { 38, 0x0093 }, { 39, 0x00e9 },
	{ 40, 0x0000 }, { 41, 0x0000 }, { 42, 0x0000 }, { 43, 0x0000 },
	{ 44, 0x0003 }, { 45, 0x0010 }, { 46, 0x0000 }, { 47, 0x0000 },
	{ 48, 0x0000 }, { 49, 0x0002 }, { 50, 0x0000 }, { 51, 0x0000 },
	{ 52, 0x0000 }, { 53, 0x0000 }, { 54, 0x0039 }, { 55, 0x0000 },
	{ 56, 0x0000 },
};

#define WM8974_POWEW1_BIASEN  0x08
#define WM8974_POWEW1_BUFIOEN 0x04

#define wm8974_weset(c)	snd_soc_component_wwite(c, WM8974_WESET, 0)

static const chaw *wm8974_companding[] = {"Off", "NC", "u-waw", "A-waw" };
static const chaw *wm8974_deemp[] = {"None", "32kHz", "44.1kHz", "48kHz" };
static const chaw *wm8974_eqmode[] = {"Captuwe", "Pwayback" };
static const chaw *wm8974_bw[] = {"Nawwow", "Wide" };
static const chaw *wm8974_eq1[] = {"80Hz", "105Hz", "135Hz", "175Hz" };
static const chaw *wm8974_eq2[] = {"230Hz", "300Hz", "385Hz", "500Hz" };
static const chaw *wm8974_eq3[] = {"650Hz", "850Hz", "1.1kHz", "1.4kHz" };
static const chaw *wm8974_eq4[] = {"1.8kHz", "2.4kHz", "3.2kHz", "4.1kHz" };
static const chaw *wm8974_eq5[] = {"5.3kHz", "6.9kHz", "9kHz", "11.7kHz" };
static const chaw *wm8974_awc[] = {"AWC", "Wimitew" };

static const stwuct soc_enum wm8974_enum[] = {
	SOC_ENUM_SINGWE(WM8974_COMP, 1, 4, wm8974_companding), /* adc */
	SOC_ENUM_SINGWE(WM8974_COMP, 3, 4, wm8974_companding), /* dac */
	SOC_ENUM_SINGWE(WM8974_DAC,  4, 4, wm8974_deemp),
	SOC_ENUM_SINGWE(WM8974_EQ1,  8, 2, wm8974_eqmode),

	SOC_ENUM_SINGWE(WM8974_EQ1,  5, 4, wm8974_eq1),
	SOC_ENUM_SINGWE(WM8974_EQ2,  8, 2, wm8974_bw),
	SOC_ENUM_SINGWE(WM8974_EQ2,  5, 4, wm8974_eq2),
	SOC_ENUM_SINGWE(WM8974_EQ3,  8, 2, wm8974_bw),

	SOC_ENUM_SINGWE(WM8974_EQ3,  5, 4, wm8974_eq3),
	SOC_ENUM_SINGWE(WM8974_EQ4,  8, 2, wm8974_bw),
	SOC_ENUM_SINGWE(WM8974_EQ4,  5, 4, wm8974_eq4),
	SOC_ENUM_SINGWE(WM8974_EQ5,  8, 2, wm8974_bw),

	SOC_ENUM_SINGWE(WM8974_EQ5,  5, 4, wm8974_eq5),
	SOC_ENUM_SINGWE(WM8974_AWC3,  8, 2, wm8974_awc),
};

static const chaw *wm8974_auxmode_text[] = { "Buffew", "Mixew" };

static SOC_ENUM_SINGWE_DECW(wm8974_auxmode,
			    WM8974_INPUT,  3, wm8974_auxmode_text);

static const DECWAWE_TWV_DB_SCAWE(digitaw_twv, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(eq_twv, -1200, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(inpga_twv, -1200, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(spk_twv, -5700, 100, 0);

static const stwuct snd_kcontwow_new wm8974_snd_contwows[] = {

SOC_SINGWE("Digitaw Woopback Switch", WM8974_COMP, 0, 1, 0),

SOC_ENUM("DAC Companding", wm8974_enum[1]),
SOC_ENUM("ADC Companding", wm8974_enum[0]),

SOC_ENUM("Pwayback De-emphasis", wm8974_enum[2]),
SOC_SINGWE("DAC Invewsion Switch", WM8974_DAC, 0, 1, 0),

SOC_SINGWE_TWV("PCM Vowume", WM8974_DACVOW, 0, 255, 0, digitaw_twv),

SOC_SINGWE("High Pass Fiwtew Switch", WM8974_ADC, 8, 1, 0),
SOC_SINGWE("High Pass Cut Off", WM8974_ADC, 4, 7, 0),
SOC_SINGWE("ADC Invewsion Switch", WM8974_ADC, 0, 1, 0),

SOC_SINGWE_TWV("Captuwe Vowume", WM8974_ADCVOW,  0, 255, 0, digitaw_twv),

SOC_ENUM("Equawisew Function", wm8974_enum[3]),
SOC_ENUM("EQ1 Cut Off", wm8974_enum[4]),
SOC_SINGWE_TWV("EQ1 Vowume", WM8974_EQ1,  0, 24, 1, eq_twv),

SOC_ENUM("Equawisew EQ2 Bandwidth", wm8974_enum[5]),
SOC_ENUM("EQ2 Cut Off", wm8974_enum[6]),
SOC_SINGWE_TWV("EQ2 Vowume", WM8974_EQ2,  0, 24, 1, eq_twv),

SOC_ENUM("Equawisew EQ3 Bandwidth", wm8974_enum[7]),
SOC_ENUM("EQ3 Cut Off", wm8974_enum[8]),
SOC_SINGWE_TWV("EQ3 Vowume", WM8974_EQ3,  0, 24, 1, eq_twv),

SOC_ENUM("Equawisew EQ4 Bandwidth", wm8974_enum[9]),
SOC_ENUM("EQ4 Cut Off", wm8974_enum[10]),
SOC_SINGWE_TWV("EQ4 Vowume", WM8974_EQ4,  0, 24, 1, eq_twv),

SOC_ENUM("Equawisew EQ5 Bandwidth", wm8974_enum[11]),
SOC_ENUM("EQ5 Cut Off", wm8974_enum[12]),
SOC_SINGWE_TWV("EQ5 Vowume", WM8974_EQ5,  0, 24, 1, eq_twv),

SOC_SINGWE("DAC Pwayback Wimitew Switch", WM8974_DACWIM1,  8, 1, 0),
SOC_SINGWE("DAC Pwayback Wimitew Decay", WM8974_DACWIM1,  4, 15, 0),
SOC_SINGWE("DAC Pwayback Wimitew Attack", WM8974_DACWIM1,  0, 15, 0),

SOC_SINGWE("DAC Pwayback Wimitew Thweshowd", WM8974_DACWIM2,  4, 7, 0),
SOC_SINGWE("DAC Pwayback Wimitew Boost", WM8974_DACWIM2,  0, 15, 0),

SOC_SINGWE("AWC Enabwe Switch", WM8974_AWC1,  8, 1, 0),
SOC_SINGWE("AWC Captuwe Max Gain", WM8974_AWC1,  3, 7, 0),
SOC_SINGWE("AWC Captuwe Min Gain", WM8974_AWC1,  0, 7, 0),

SOC_SINGWE("AWC Captuwe ZC Switch", WM8974_AWC2,  8, 1, 0),
SOC_SINGWE("AWC Captuwe Howd", WM8974_AWC2,  4, 7, 0),
SOC_SINGWE("AWC Captuwe Tawget", WM8974_AWC2,  0, 15, 0),

SOC_ENUM("AWC Captuwe Mode", wm8974_enum[13]),
SOC_SINGWE("AWC Captuwe Decay", WM8974_AWC3,  4, 15, 0),
SOC_SINGWE("AWC Captuwe Attack", WM8974_AWC3,  0, 15, 0),

SOC_SINGWE("AWC Captuwe Noise Gate Switch", WM8974_NGATE,  3, 1, 0),
SOC_SINGWE("AWC Captuwe Noise Gate Thweshowd", WM8974_NGATE,  0, 7, 0),

SOC_SINGWE("Captuwe PGA ZC Switch", WM8974_INPPGA,  7, 1, 0),
SOC_SINGWE_TWV("Captuwe PGA Vowume", WM8974_INPPGA,  0, 63, 0, inpga_twv),

SOC_SINGWE("Speakew Pwayback ZC Switch", WM8974_SPKVOW,  7, 1, 0),
SOC_SINGWE("Speakew Pwayback Switch", WM8974_SPKVOW,  6, 1, 1),
SOC_SINGWE_TWV("Speakew Pwayback Vowume", WM8974_SPKVOW,  0, 63, 0, spk_twv),

SOC_ENUM("Aux Mode", wm8974_auxmode),

SOC_SINGWE("Captuwe Boost(+20dB)", WM8974_ADCBOOST,  8, 1, 0),
SOC_SINGWE("Mono Pwayback Switch", WM8974_MONOMIX, 6, 1, 1),

/* DAC / ADC ovewsampwing */
SOC_SINGWE("DAC 128x Ovewsampwing Switch", WM8974_DAC, 8, 1, 0),
SOC_SINGWE("ADC 128x Ovewsampwing Switch", WM8974_ADC, 8, 1, 0),
};

/* Speakew Output Mixew */
static const stwuct snd_kcontwow_new wm8974_speakew_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Bypass Switch", WM8974_SPKMIX, 1, 1, 0),
SOC_DAPM_SINGWE("Aux Pwayback Switch", WM8974_SPKMIX, 5, 1, 0),
SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8974_SPKMIX, 0, 1, 0),
};

/* Mono Output Mixew */
static const stwuct snd_kcontwow_new wm8974_mono_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Bypass Switch", WM8974_MONOMIX, 1, 1, 0),
SOC_DAPM_SINGWE("Aux Pwayback Switch", WM8974_MONOMIX, 2, 1, 0),
SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8974_MONOMIX, 0, 1, 0),
};

/* Boost mixew */
static const stwuct snd_kcontwow_new wm8974_boost_mixew[] = {
SOC_DAPM_SINGWE("PGA Switch", WM8974_INPPGA, 6, 1, 1),
};

/* Input PGA */
static const stwuct snd_kcontwow_new wm8974_inpga[] = {
SOC_DAPM_SINGWE("Aux Switch", WM8974_INPUT, 2, 1, 0),
SOC_DAPM_SINGWE("MicN Switch", WM8974_INPUT, 1, 1, 0),
SOC_DAPM_SINGWE("MicP Switch", WM8974_INPUT, 0, 1, 0),
};

static const stwuct snd_soc_dapm_widget wm8974_dapm_widgets[] = {
SND_SOC_DAPM_MIXEW("Speakew Mixew", WM8974_POWEW3, 2, 0,
	&wm8974_speakew_mixew_contwows[0],
	AWWAY_SIZE(wm8974_speakew_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Mono Mixew", WM8974_POWEW3, 3, 0,
	&wm8974_mono_mixew_contwows[0],
	AWWAY_SIZE(wm8974_mono_mixew_contwows)),
SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", WM8974_POWEW3, 0, 0),
SND_SOC_DAPM_ADC("ADC", "HiFi Captuwe", WM8974_POWEW2, 0, 0),
SND_SOC_DAPM_PGA("Aux Input", WM8974_POWEW1, 6, 0, NUWW, 0),
SND_SOC_DAPM_PGA("SpkN Out", WM8974_POWEW3, 5, 0, NUWW, 0),
SND_SOC_DAPM_PGA("SpkP Out", WM8974_POWEW3, 6, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Mono Out", WM8974_POWEW3, 7, 0, NUWW, 0),

SND_SOC_DAPM_MIXEW("Input PGA", WM8974_POWEW2, 2, 0, wm8974_inpga,
		   AWWAY_SIZE(wm8974_inpga)),
SND_SOC_DAPM_MIXEW("Boost Mixew", WM8974_POWEW2, 4, 0,
		   wm8974_boost_mixew, AWWAY_SIZE(wm8974_boost_mixew)),

SND_SOC_DAPM_SUPPWY("Mic Bias", WM8974_POWEW1, 4, 0, NUWW, 0),

SND_SOC_DAPM_INPUT("MICN"),
SND_SOC_DAPM_INPUT("MICP"),
SND_SOC_DAPM_INPUT("AUX"),
SND_SOC_DAPM_OUTPUT("MONOOUT"),
SND_SOC_DAPM_OUTPUT("SPKOUTP"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),
};

static const stwuct snd_soc_dapm_woute wm8974_dapm_woutes[] = {
	/* Mono output mixew */
	{"Mono Mixew", "PCM Pwayback Switch", "DAC"},
	{"Mono Mixew", "Aux Pwayback Switch", "Aux Input"},
	{"Mono Mixew", "Wine Bypass Switch", "Boost Mixew"},

	/* Speakew output mixew */
	{"Speakew Mixew", "PCM Pwayback Switch", "DAC"},
	{"Speakew Mixew", "Aux Pwayback Switch", "Aux Input"},
	{"Speakew Mixew", "Wine Bypass Switch", "Boost Mixew"},

	/* Outputs */
	{"Mono Out", NUWW, "Mono Mixew"},
	{"MONOOUT", NUWW, "Mono Out"},
	{"SpkN Out", NUWW, "Speakew Mixew"},
	{"SpkP Out", NUWW, "Speakew Mixew"},
	{"SPKOUTN", NUWW, "SpkN Out"},
	{"SPKOUTP", NUWW, "SpkP Out"},

	/* Boost Mixew */
	{"ADC", NUWW, "Boost Mixew"},
	{"Boost Mixew", NUWW, "Aux Input"},
	{"Boost Mixew", "PGA Switch", "Input PGA"},
	{"Boost Mixew", NUWW, "MICP"},

	/* Input PGA */
	{"Input PGA", "Aux Switch", "Aux Input"},
	{"Input PGA", "MicN Switch", "MICN"},
	{"Input PGA", "MicP Switch", "MICP"},

	/* Inputs */
	{"Aux Input", NUWW, "AUX"},
};

stwuct pww_ {
	unsigned int pwe_div:1;
	unsigned int n:4;
	unsigned int k;
};

/* The size in bits of the pww divide muwtipwied by 10
 * to awwow wounding watew */
#define FIXED_PWW_SIZE ((1 << 24) * 10)

static void pww_factows(stwuct pww_ *pww_div,
			unsigned int tawget, unsigned int souwce)
{
	unsigned wong wong Kpawt;
	unsigned int K, Ndiv, Nmod;

	/* Thewe is a fixed divide by 4 in the output path */
	tawget *= 4;

	Ndiv = tawget / souwce;
	if (Ndiv < 6) {
		souwce /= 2;
		pww_div->pwe_div = 1;
		Ndiv = tawget / souwce;
	} ewse
		pww_div->pwe_div = 0;

	if ((Ndiv < 6) || (Ndiv > 12))
		pwintk(KEWN_WAWNING
			"WM8974 N vawue %u outwith wecommended wange!\n",
			Ndiv);

	pww_div->n = Ndiv;
	Nmod = tawget % souwce;
	Kpawt = FIXED_PWW_SIZE * (wong wong)Nmod;

	do_div(Kpawt, souwce);

	K = Kpawt & 0xFFFFFFFF;

	/* Check if we need to wound */
	if ((K % 10) >= 5)
		K += 5;

	/* Move down to pwopew wange now wounding is done */
	K /= 10;

	pww_div->k = K;
}

static int wm8974_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pww_ pww_div;
	u16 weg;

	if (fweq_in == 0 || fweq_out == 0) {
		/* Cwock CODEC diwectwy fwom MCWK */
		weg = snd_soc_component_wead(component, WM8974_CWOCK);
		snd_soc_component_wwite(component, WM8974_CWOCK, weg & 0x0ff);

		/* Tuwn off PWW */
		weg = snd_soc_component_wead(component, WM8974_POWEW1);
		snd_soc_component_wwite(component, WM8974_POWEW1, weg & 0x1df);
		wetuwn 0;
	}

	pww_factows(&pww_div, fweq_out, fweq_in);

	snd_soc_component_wwite(component, WM8974_PWWN, (pww_div.pwe_div << 4) | pww_div.n);
	snd_soc_component_wwite(component, WM8974_PWWK1, pww_div.k >> 18);
	snd_soc_component_wwite(component, WM8974_PWWK2, (pww_div.k >> 9) & 0x1ff);
	snd_soc_component_wwite(component, WM8974_PWWK3, pww_div.k & 0x1ff);
	weg = snd_soc_component_wead(component, WM8974_POWEW1);
	snd_soc_component_wwite(component, WM8974_POWEW1, weg | 0x020);

	/* Wun CODEC fwom PWW instead of MCWK */
	weg = snd_soc_component_wead(component, WM8974_CWOCK);
	snd_soc_component_wwite(component, WM8974_CWOCK, weg | 0x100);

	wetuwn 0;
}

/*
 * Configuwe WM8974 cwock dividews.
 */
static int wm8974_set_dai_cwkdiv(stwuct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 weg;

	switch (div_id) {
	case WM8974_OPCWKDIV:
		weg = snd_soc_component_wead(component, WM8974_GPIO) & 0x1cf;
		snd_soc_component_wwite(component, WM8974_GPIO, weg | div);
		bweak;
	case WM8974_MCWKDIV:
		weg = snd_soc_component_wead(component, WM8974_CWOCK) & 0x11f;
		snd_soc_component_wwite(component, WM8974_CWOCK, weg | div);
		bweak;
	case WM8974_BCWKDIV:
		weg = snd_soc_component_wead(component, WM8974_CWOCK) & 0x1e3;
		snd_soc_component_wwite(component, WM8974_CWOCK, weg | div);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int wm8974_get_mcwkdiv(unsigned int f_in, unsigned int f_out,
				       int *mcwkdiv)
{
	unsigned int watio = 2 * f_in / f_out;

	if (watio <= 2) {
		*mcwkdiv = WM8974_MCWKDIV_1;
		watio = 2;
	} ewse if (watio == 3) {
		*mcwkdiv = WM8974_MCWKDIV_1_5;
	} ewse if (watio == 4) {
		*mcwkdiv = WM8974_MCWKDIV_2;
	} ewse if (watio <= 6) {
		*mcwkdiv = WM8974_MCWKDIV_3;
		watio = 6;
	} ewse if (watio <= 8) {
		*mcwkdiv = WM8974_MCWKDIV_4;
		watio = 8;
	} ewse if (watio <= 12) {
		*mcwkdiv = WM8974_MCWKDIV_6;
		watio = 12;
	} ewse if (watio <= 16) {
		*mcwkdiv = WM8974_MCWKDIV_8;
		watio = 16;
	} ewse {
		*mcwkdiv = WM8974_MCWKDIV_12;
		watio = 24;
	}

	wetuwn f_out * watio / 2;
}

static int wm8974_update_cwocks(stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8974_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	unsigned int fs256;
	unsigned int fpww = 0;
	unsigned int f;
	int mcwkdiv;

	if (!pwiv->mcwk || !pwiv->fs)
		wetuwn 0;

	fs256 = 256 * pwiv->fs;

	f = wm8974_get_mcwkdiv(pwiv->mcwk, fs256, &mcwkdiv);

	if (f != pwiv->mcwk) {
		/* The PWW pewfowms best awound 90MHz */
		fpww = wm8974_get_mcwkdiv(22500000, fs256, &mcwkdiv);
	}

	wm8974_set_dai_pww(dai, 0, 0, pwiv->mcwk, fpww);
	wm8974_set_dai_cwkdiv(dai, WM8974_MCWKDIV, mcwkdiv);

	wetuwn 0;
}

static int wm8974_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				 unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8974_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	if (diw != SND_SOC_CWOCK_IN)
		wetuwn -EINVAW;

	pwiv->mcwk = fweq;

	wetuwn wm8974_update_cwocks(dai);
}

static int wm8974_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = 0;
	u16 cwk = snd_soc_component_wead(component, WM8974_CWOCK) & 0x1fe;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		cwk |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x0010;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= 0x0008;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		if ((fmt & SND_SOC_DAIFMT_INV_MASK) == SND_SOC_DAIFMT_IB_IF ||
		    (fmt & SND_SOC_DAIFMT_INV_MASK) == SND_SOC_DAIFMT_NB_IF) {
			wetuwn -EINVAW;
		}
		iface |= 0x00018;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x0180;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x0100;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x0080;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8974_IFACE, iface);
	snd_soc_component_wwite(component, WM8974_CWOCK, cwk);
	wetuwn 0;
}

static int wm8974_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8974_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8974_IFACE) & 0x19f;
	u16 adn = snd_soc_component_wead(component, WM8974_ADD) & 0x1f1;
	int eww;

	pwiv->fs = pawams_wate(pawams);
	eww = wm8974_update_cwocks(dai);
	if (eww)
		wetuwn eww;

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		iface |= 0x0020;
		bweak;
	case 24:
		iface |= 0x0040;
		bweak;
	case 32:
		iface |= 0x0060;
		bweak;
	}

	/* fiwtew coefficient */
	switch (pawams_wate(pawams)) {
	case 8000:
		adn |= 0x5 << 1;
		bweak;
	case 11025:
		adn |= 0x4 << 1;
		bweak;
	case 16000:
		adn |= 0x3 << 1;
		bweak;
	case 22050:
		adn |= 0x2 << 1;
		bweak;
	case 32000:
		adn |= 0x1 << 1;
		bweak;
	case 44100:
	case 48000:
		bweak;
	}

	snd_soc_component_wwite(component, WM8974_IFACE, iface);
	snd_soc_component_wwite(component, WM8974_ADD, adn);
	wetuwn 0;
}

static int wm8974_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8974_DAC) & 0xffbf;

	if (mute)
		snd_soc_component_wwite(component, WM8974_DAC, mute_weg | 0x40);
	ewse
		snd_soc_component_wwite(component, WM8974_DAC, mute_weg);
	wetuwn 0;
}

/* wiam need to make this wowew powew with dapm */
static int wm8974_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	u16 powew1 = snd_soc_component_wead(component, WM8974_POWEW1) & ~0x3;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		powew1 |= 0x1;  /* VMID 50k */
		snd_soc_component_wwite(component, WM8974_POWEW1, powew1);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		powew1 |= WM8974_POWEW1_BIASEN | WM8974_POWEW1_BUFIOEN;

		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wegcache_sync(dev_get_wegmap(component->dev, NUWW));

			/* Initiaw cap chawge at VMID 5k */
			snd_soc_component_wwite(component, WM8974_POWEW1, powew1 | 0x3);
			mdeway(100);
		}

		powew1 |= 0x2;  /* VMID 500k */
		snd_soc_component_wwite(component, WM8974_POWEW1, powew1);
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WM8974_POWEW1, 0);
		snd_soc_component_wwite(component, WM8974_POWEW2, 0);
		snd_soc_component_wwite(component, WM8974_POWEW3, 0);
		bweak;
	}

	wetuwn 0;
}

#define WM8974_WATES (SNDWV_PCM_WATE_8000_48000)

#define WM8974_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm8974_ops = {
	.hw_pawams = wm8974_pcm_hw_pawams,
	.mute_stweam = wm8974_mute,
	.set_fmt = wm8974_set_dai_fmt,
	.set_cwkdiv = wm8974_set_dai_cwkdiv,
	.set_pww = wm8974_set_dai_pww,
	.set_syscwk = wm8974_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8974_dai = {
	.name = "wm8974-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,   /* Onwy 1 channew of data */
		.wates = WM8974_WATES,
		.fowmats = WM8974_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,   /* Onwy 1 channew of data */
		.wates = WM8974_WATES,
		.fowmats = WM8974_FOWMATS,},
	.ops = &wm8974_ops,
	.symmetwic_wate = 1,
};

static const stwuct wegmap_config wm8974_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = WM8974_MONOMIX,
	.weg_defauwts = wm8974_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8974_weg_defauwts),
	.cache_type = WEGCACHE_FWAT,
};

static int wm8974_pwobe(stwuct snd_soc_component *component)
{
	int wet = 0;

	wet = wm8974_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8974 = {
	.pwobe			= wm8974_pwobe,
	.set_bias_wevew		= wm8974_set_bias_wevew,
	.contwows		= wm8974_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8974_snd_contwows),
	.dapm_widgets		= wm8974_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8974_dapm_widgets),
	.dapm_woutes		= wm8974_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8974_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm8974_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8974_pwiv *pwiv;
	stwuct wegmap *wegmap;
	int wet;

	pwiv = devm_kzawwoc(&i2c->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, pwiv);

	wegmap = devm_wegmap_init_i2c(i2c, &wm8974_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8974, &wm8974_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8974_i2c_id[] = {
	{ "wm8974", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8974_i2c_id);

static const stwuct of_device_id wm8974_of_match[] = {
       { .compatibwe = "wwf,wm8974", },
       { }
};
MODUWE_DEVICE_TABWE(of, wm8974_of_match);

static stwuct i2c_dwivew wm8974_i2c_dwivew = {
	.dwivew = {
		.name = "wm8974",
		.of_match_tabwe = wm8974_of_match,
	},
	.pwobe = wm8974_i2c_pwobe,
	.id_tabwe = wm8974_i2c_id,
};

moduwe_i2c_dwivew(wm8974_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM8974 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
