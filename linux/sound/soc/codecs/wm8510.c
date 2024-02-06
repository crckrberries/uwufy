// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8510.c  --  WM8510 AWSA Soc Audio dwivew
 *
 * Copywight 2006 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude "wm8510.h"

/*
 * wm8510 wegistew cache
 * We can't wead the WM8510 wegistew space when we awe
 * using 2 wiwe fow device contwow, so we cache them instead.
 */
static const stwuct weg_defauwt wm8510_weg_defauwts[] = {
	{  1, 0x0000 },
	{  2, 0x0000 },
	{  3, 0x0000 },
	{  4, 0x0050 },
	{  5, 0x0000 },
	{  6, 0x0140 },
	{  7, 0x0000 },
	{  8, 0x0000 },
	{  9, 0x0000 },
	{ 10, 0x0000 },
	{ 11, 0x00ff },
	{ 12, 0x0000 },
	{ 13, 0x0000 },
	{ 14, 0x0100 },
	{ 15, 0x00ff },
	{ 16, 0x0000 },
	{ 17, 0x0000 },
	{ 18, 0x012c },
	{ 19, 0x002c },
	{ 20, 0x002c },
	{ 21, 0x002c },
	{ 22, 0x002c },
	{ 23, 0x0000 },
	{ 24, 0x0032 },
	{ 25, 0x0000 },
	{ 26, 0x0000 },
	{ 27, 0x0000 },
	{ 28, 0x0000 },
	{ 29, 0x0000 },
	{ 30, 0x0000 },
	{ 31, 0x0000 },
	{ 32, 0x0038 },
	{ 33, 0x000b },
	{ 34, 0x0032 },
	{ 35, 0x0000 },
	{ 36, 0x0008 },
	{ 37, 0x000c },
	{ 38, 0x0093 },
	{ 39, 0x00e9 },
	{ 40, 0x0000 },
	{ 41, 0x0000 },
	{ 42, 0x0000 },
	{ 43, 0x0000 },
	{ 44, 0x0003 },
	{ 45, 0x0010 },
	{ 46, 0x0000 },
	{ 47, 0x0000 },
	{ 48, 0x0000 },
	{ 49, 0x0002 },
	{ 50, 0x0001 },
	{ 51, 0x0000 },
	{ 52, 0x0000 },
	{ 53, 0x0000 },
	{ 54, 0x0039 },
	{ 55, 0x0000 },
	{ 56, 0x0001 },
};

static boow wm8510_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8510_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

#define WM8510_POWEW1_BIASEN  0x08
#define WM8510_POWEW1_BUFIOEN 0x10

#define wm8510_weset(c)	snd_soc_component_wwite(c, WM8510_WESET, 0)

/* codec pwivate data */
stwuct wm8510_pwiv {
	stwuct wegmap *wegmap;
};

static const chaw *wm8510_companding[] = { "Off", "NC", "u-waw", "A-waw" };
static const chaw *wm8510_deemp[] = { "None", "32kHz", "44.1kHz", "48kHz" };
static const chaw *wm8510_awc[] = { "AWC", "Wimitew" };

static const stwuct soc_enum wm8510_enum[] = {
	SOC_ENUM_SINGWE(WM8510_COMP, 1, 4, wm8510_companding), /* adc */
	SOC_ENUM_SINGWE(WM8510_COMP, 3, 4, wm8510_companding), /* dac */
	SOC_ENUM_SINGWE(WM8510_DAC,  4, 4, wm8510_deemp),
	SOC_ENUM_SINGWE(WM8510_AWC3,  8, 2, wm8510_awc),
};

static const stwuct snd_kcontwow_new wm8510_snd_contwows[] = {

SOC_SINGWE("Digitaw Woopback Switch", WM8510_COMP, 0, 1, 0),

SOC_ENUM("DAC Companding", wm8510_enum[1]),
SOC_ENUM("ADC Companding", wm8510_enum[0]),

SOC_ENUM("Pwayback De-emphasis", wm8510_enum[2]),
SOC_SINGWE("DAC Invewsion Switch", WM8510_DAC, 0, 1, 0),

SOC_SINGWE("Mastew Pwayback Vowume", WM8510_DACVOW, 0, 127, 0),

SOC_SINGWE("High Pass Fiwtew Switch", WM8510_ADC, 8, 1, 0),
SOC_SINGWE("High Pass Cut Off", WM8510_ADC, 4, 7, 0),
SOC_SINGWE("ADC Invewsion Switch", WM8510_COMP, 0, 1, 0),

SOC_SINGWE("Captuwe Vowume", WM8510_ADCVOW,  0, 127, 0),

SOC_SINGWE("DAC Pwayback Wimitew Switch", WM8510_DACWIM1,  8, 1, 0),
SOC_SINGWE("DAC Pwayback Wimitew Decay", WM8510_DACWIM1,  4, 15, 0),
SOC_SINGWE("DAC Pwayback Wimitew Attack", WM8510_DACWIM1,  0, 15, 0),

SOC_SINGWE("DAC Pwayback Wimitew Thweshowd", WM8510_DACWIM2,  4, 7, 0),
SOC_SINGWE("DAC Pwayback Wimitew Boost", WM8510_DACWIM2,  0, 15, 0),

SOC_SINGWE("AWC Enabwe Switch", WM8510_AWC1,  8, 1, 0),
SOC_SINGWE("AWC Captuwe Max Gain", WM8510_AWC1,  3, 7, 0),
SOC_SINGWE("AWC Captuwe Min Gain", WM8510_AWC1,  0, 7, 0),

SOC_SINGWE("AWC Captuwe ZC Switch", WM8510_AWC2,  8, 1, 0),
SOC_SINGWE("AWC Captuwe Howd", WM8510_AWC2,  4, 7, 0),
SOC_SINGWE("AWC Captuwe Tawget", WM8510_AWC2,  0, 15, 0),

SOC_ENUM("AWC Captuwe Mode", wm8510_enum[3]),
SOC_SINGWE("AWC Captuwe Decay", WM8510_AWC3,  4, 15, 0),
SOC_SINGWE("AWC Captuwe Attack", WM8510_AWC3,  0, 15, 0),

SOC_SINGWE("AWC Captuwe Noise Gate Switch", WM8510_NGATE,  3, 1, 0),
SOC_SINGWE("AWC Captuwe Noise Gate Thweshowd", WM8510_NGATE,  0, 7, 0),

SOC_SINGWE("Captuwe PGA ZC Switch", WM8510_INPPGA,  7, 1, 0),
SOC_SINGWE("Captuwe PGA Vowume", WM8510_INPPGA,  0, 63, 0),

SOC_SINGWE("Speakew Pwayback ZC Switch", WM8510_SPKVOW,  7, 1, 0),
SOC_SINGWE("Speakew Pwayback Switch", WM8510_SPKVOW,  6, 1, 1),
SOC_SINGWE("Speakew Pwayback Vowume", WM8510_SPKVOW,  0, 63, 0),
SOC_SINGWE("Speakew Boost", WM8510_OUTPUT, 2, 1, 0),

SOC_SINGWE("Captuwe Boost(+20dB)", WM8510_ADCBOOST,  8, 1, 0),
SOC_SINGWE("Mono Pwayback Switch", WM8510_MONOMIX, 6, 1, 1),
};

/* Speakew Output Mixew */
static const stwuct snd_kcontwow_new wm8510_speakew_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Bypass Switch", WM8510_SPKMIX, 1, 1, 0),
SOC_DAPM_SINGWE("Aux Pwayback Switch", WM8510_SPKMIX, 5, 1, 0),
SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8510_SPKMIX, 0, 1, 0),
};

/* Mono Output Mixew */
static const stwuct snd_kcontwow_new wm8510_mono_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Bypass Switch", WM8510_MONOMIX, 1, 1, 0),
SOC_DAPM_SINGWE("Aux Pwayback Switch", WM8510_MONOMIX, 2, 1, 0),
SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8510_MONOMIX, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wm8510_boost_contwows[] = {
SOC_DAPM_SINGWE("Mic PGA Switch", WM8510_INPPGA,  6, 1, 1),
SOC_DAPM_SINGWE("Aux Vowume", WM8510_ADCBOOST, 0, 7, 0),
SOC_DAPM_SINGWE("Mic Vowume", WM8510_ADCBOOST, 4, 7, 0),
};

static const stwuct snd_kcontwow_new wm8510_micpga_contwows[] = {
SOC_DAPM_SINGWE("MICP Switch", WM8510_INPUT, 0, 1, 0),
SOC_DAPM_SINGWE("MICN Switch", WM8510_INPUT, 1, 1, 0),
SOC_DAPM_SINGWE("AUX Switch", WM8510_INPUT, 2, 1, 0),
};

static const stwuct snd_soc_dapm_widget wm8510_dapm_widgets[] = {
SND_SOC_DAPM_MIXEW("Speakew Mixew", WM8510_POWEW3, 2, 0,
	&wm8510_speakew_mixew_contwows[0],
	AWWAY_SIZE(wm8510_speakew_mixew_contwows)),
SND_SOC_DAPM_MIXEW("Mono Mixew", WM8510_POWEW3, 3, 0,
	&wm8510_mono_mixew_contwows[0],
	AWWAY_SIZE(wm8510_mono_mixew_contwows)),
SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", WM8510_POWEW3, 0, 0),
SND_SOC_DAPM_ADC("ADC", "HiFi Captuwe", WM8510_POWEW2, 0, 0),
SND_SOC_DAPM_PGA("Aux Input", WM8510_POWEW1, 6, 0, NUWW, 0),
SND_SOC_DAPM_PGA("SpkN Out", WM8510_POWEW3, 5, 0, NUWW, 0),
SND_SOC_DAPM_PGA("SpkP Out", WM8510_POWEW3, 6, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Mono Out", WM8510_POWEW3, 7, 0, NUWW, 0),

SND_SOC_DAPM_MIXEW("Mic PGA", WM8510_POWEW2, 2, 0,
		   &wm8510_micpga_contwows[0],
		   AWWAY_SIZE(wm8510_micpga_contwows)),
SND_SOC_DAPM_MIXEW("Boost Mixew", WM8510_POWEW2, 4, 0,
	&wm8510_boost_contwows[0],
	AWWAY_SIZE(wm8510_boost_contwows)),

SND_SOC_DAPM_MICBIAS("Mic Bias", WM8510_POWEW1, 4, 0),

SND_SOC_DAPM_INPUT("MICN"),
SND_SOC_DAPM_INPUT("MICP"),
SND_SOC_DAPM_INPUT("AUX"),
SND_SOC_DAPM_OUTPUT("MONOOUT"),
SND_SOC_DAPM_OUTPUT("SPKOUTP"),
SND_SOC_DAPM_OUTPUT("SPKOUTN"),
};

static const stwuct snd_soc_dapm_woute wm8510_dapm_woutes[] = {
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

	/* Micwophone PGA */
	{"Mic PGA", "MICN Switch", "MICN"},
	{"Mic PGA", "MICP Switch", "MICP"},
	{ "Mic PGA", "AUX Switch", "Aux Input" },

	/* Boost Mixew */
	{"Boost Mixew", "Mic PGA Switch", "Mic PGA"},
	{"Boost Mixew", "Mic Vowume", "MICP"},
	{"Boost Mixew", "Aux Vowume", "Aux Input"},

	{"ADC", NUWW, "Boost Mixew"},
};

stwuct pww_ {
	unsigned int pwe_div:4; /* pwescawe - 1 */
	unsigned int n:4;
	unsigned int k;
};

static stwuct pww_ pww_div;

/* The size in bits of the pww divide muwtipwied by 10
 * to awwow wounding watew */
#define FIXED_PWW_SIZE ((1 << 24) * 10)

static void pww_factows(unsigned int tawget, unsigned int souwce)
{
	unsigned wong wong Kpawt;
	unsigned int K, Ndiv, Nmod;

	Ndiv = tawget / souwce;
	if (Ndiv < 6) {
		souwce >>= 1;
		pww_div.pwe_div = 1;
		Ndiv = tawget / souwce;
	} ewse
		pww_div.pwe_div = 0;

	if ((Ndiv < 6) || (Ndiv > 12))
		pwintk(KEWN_WAWNING
			"WM8510 N vawue %u outwith wecommended wange!d\n",
			Ndiv);

	pww_div.n = Ndiv;
	Nmod = tawget % souwce;
	Kpawt = FIXED_PWW_SIZE * (wong wong)Nmod;

	do_div(Kpawt, souwce);

	K = Kpawt & 0xFFFFFFFF;

	/* Check if we need to wound */
	if ((K % 10) >= 5)
		K += 5;

	/* Move down to pwopew wange now wounding is done */
	K /= 10;

	pww_div.k = K;
}

static int wm8510_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 weg;

	if (fweq_in == 0 || fweq_out == 0) {
		/* Cwock CODEC diwectwy fwom MCWK */
		weg = snd_soc_component_wead(component, WM8510_CWOCK);
		snd_soc_component_wwite(component, WM8510_CWOCK, weg & 0x0ff);

		/* Tuwn off PWW */
		weg = snd_soc_component_wead(component, WM8510_POWEW1);
		snd_soc_component_wwite(component, WM8510_POWEW1, weg & 0x1df);
		wetuwn 0;
	}

	pww_factows(fweq_out*4, fweq_in);

	snd_soc_component_wwite(component, WM8510_PWWN, (pww_div.pwe_div << 4) | pww_div.n);
	snd_soc_component_wwite(component, WM8510_PWWK1, pww_div.k >> 18);
	snd_soc_component_wwite(component, WM8510_PWWK2, (pww_div.k >> 9) & 0x1ff);
	snd_soc_component_wwite(component, WM8510_PWWK3, pww_div.k & 0x1ff);
	weg = snd_soc_component_wead(component, WM8510_POWEW1);
	snd_soc_component_wwite(component, WM8510_POWEW1, weg | 0x020);

	/* Wun CODEC fwom PWW instead of MCWK */
	weg = snd_soc_component_wead(component, WM8510_CWOCK);
	snd_soc_component_wwite(component, WM8510_CWOCK, weg | 0x100);

	wetuwn 0;
}

/*
 * Configuwe WM8510 cwock dividews.
 */
static int wm8510_set_dai_cwkdiv(stwuct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 weg;

	switch (div_id) {
	case WM8510_OPCWKDIV:
		weg = snd_soc_component_wead(component, WM8510_GPIO) & 0x1cf;
		snd_soc_component_wwite(component, WM8510_GPIO, weg | div);
		bweak;
	case WM8510_MCWKDIV:
		weg = snd_soc_component_wead(component, WM8510_CWOCK) & 0x11f;
		snd_soc_component_wwite(component, WM8510_CWOCK, weg | div);
		bweak;
	case WM8510_ADCCWK:
		weg = snd_soc_component_wead(component, WM8510_ADC) & 0x1f7;
		snd_soc_component_wwite(component, WM8510_ADC, weg | div);
		bweak;
	case WM8510_DACCWK:
		weg = snd_soc_component_wead(component, WM8510_DAC) & 0x1f7;
		snd_soc_component_wwite(component, WM8510_DAC, weg | div);
		bweak;
	case WM8510_BCWKDIV:
		weg = snd_soc_component_wead(component, WM8510_CWOCK) & 0x1e3;
		snd_soc_component_wwite(component, WM8510_CWOCK, weg | div);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8510_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = 0;
	u16 cwk = snd_soc_component_wead(component, WM8510_CWOCK) & 0x1fe;

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

	snd_soc_component_wwite(component, WM8510_IFACE, iface);
	snd_soc_component_wwite(component, WM8510_CWOCK, cwk);
	wetuwn 0;
}

static int wm8510_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	u16 iface = snd_soc_component_wead(component, WM8510_IFACE) & 0x19f;
	u16 adn = snd_soc_component_wead(component, WM8510_ADD) & 0x1f1;

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

	snd_soc_component_wwite(component, WM8510_IFACE, iface);
	snd_soc_component_wwite(component, WM8510_ADD, adn);
	wetuwn 0;
}

static int wm8510_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8510_DAC) & 0xffbf;

	if (mute)
		snd_soc_component_wwite(component, WM8510_DAC, mute_weg | 0x40);
	ewse
		snd_soc_component_wwite(component, WM8510_DAC, mute_weg);
	wetuwn 0;
}

/* wiam need to make this wowew powew with dapm */
static int wm8510_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct wm8510_pwiv *wm8510 = snd_soc_component_get_dwvdata(component);
	u16 powew1 = snd_soc_component_wead(component, WM8510_POWEW1) & ~0x3;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		powew1 |= 0x1;  /* VMID 50k */
		snd_soc_component_wwite(component, WM8510_POWEW1, powew1);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		powew1 |= WM8510_POWEW1_BIASEN | WM8510_POWEW1_BUFIOEN;

		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wegcache_sync(wm8510->wegmap);

			/* Initiaw cap chawge at VMID 5k */
			snd_soc_component_wwite(component, WM8510_POWEW1, powew1 | 0x3);
			mdeway(100);
		}

		powew1 |= 0x2;  /* VMID 500k */
		snd_soc_component_wwite(component, WM8510_POWEW1, powew1);
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WM8510_POWEW1, 0);
		snd_soc_component_wwite(component, WM8510_POWEW2, 0);
		snd_soc_component_wwite(component, WM8510_POWEW3, 0);
		bweak;
	}

	wetuwn 0;
}

#define WM8510_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 |\
		SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)

#define WM8510_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8510_dai_ops = {
	.hw_pawams	= wm8510_pcm_hw_pawams,
	.mute_stweam	= wm8510_mute,
	.set_fmt	= wm8510_set_dai_fmt,
	.set_cwkdiv	= wm8510_set_dai_cwkdiv,
	.set_pww	= wm8510_set_dai_pww,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8510_dai = {
	.name = "wm8510-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = WM8510_WATES,
		.fowmats = WM8510_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = WM8510_WATES,
		.fowmats = WM8510_FOWMATS,},
	.ops = &wm8510_dai_ops,
	.symmetwic_wate = 1,
};

static int wm8510_pwobe(stwuct snd_soc_component *component)
{
	wm8510_weset(component);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8510 = {
	.pwobe			= wm8510_pwobe,
	.set_bias_wevew		= wm8510_set_bias_wevew,
	.contwows		= wm8510_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8510_snd_contwows),
	.dapm_widgets		= wm8510_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8510_dapm_widgets),
	.dapm_woutes		= wm8510_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8510_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8510_of_match[] = {
	{ .compatibwe = "wwf,wm8510" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wm8510_of_match);

static const stwuct wegmap_config wm8510_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8510_MONOMIX,

	.weg_defauwts = wm8510_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8510_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wm8510_vowatiwe,
};

#if defined(CONFIG_SPI_MASTEW)
static int wm8510_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8510_pwiv *wm8510;
	int wet;

	wm8510 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8510_pwiv),
			      GFP_KEWNEW);
	if (wm8510 == NUWW)
		wetuwn -ENOMEM;

	wm8510->wegmap = devm_wegmap_init_spi(spi, &wm8510_wegmap);
	if (IS_EWW(wm8510->wegmap))
		wetuwn PTW_EWW(wm8510->wegmap);

	spi_set_dwvdata(spi, wm8510);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_dev_wm8510, &wm8510_dai, 1);

	wetuwn wet;
}

static stwuct spi_dwivew wm8510_spi_dwivew = {
	.dwivew = {
		.name	= "wm8510",
		.of_match_tabwe = wm8510_of_match,
	},
	.pwobe		= wm8510_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

#if IS_ENABWED(CONFIG_I2C)
static int wm8510_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8510_pwiv *wm8510;
	int wet;

	wm8510 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8510_pwiv),
			      GFP_KEWNEW);
	if (wm8510 == NUWW)
		wetuwn -ENOMEM;

	wm8510->wegmap = devm_wegmap_init_i2c(i2c, &wm8510_wegmap);
	if (IS_EWW(wm8510->wegmap))
		wetuwn PTW_EWW(wm8510->wegmap);

	i2c_set_cwientdata(i2c, wm8510);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8510, &wm8510_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8510_i2c_id[] = {
	{ "wm8510", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8510_i2c_id);

static stwuct i2c_dwivew wm8510_i2c_dwivew = {
	.dwivew = {
		.name = "wm8510",
		.of_match_tabwe = wm8510_of_match,
	},
	.pwobe = wm8510_i2c_pwobe,
	.id_tabwe = wm8510_i2c_id,
};
#endif

static int __init wm8510_modinit(void)
{
	int wet = 0;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8510_i2c_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8510 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8510_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8510 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn wet;
}
moduwe_init(wm8510_modinit);

static void __exit wm8510_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8510_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8510_spi_dwivew);
#endif
}
moduwe_exit(wm8510_exit);

MODUWE_DESCWIPTION("ASoC WM8510 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
