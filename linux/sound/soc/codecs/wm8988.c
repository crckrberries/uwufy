// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8988.c -- WM8988 AWSA SoC audio dwivew
 *
 * Copywight 2009 Wowfson Micwoewectwonics pwc
 * Copywight 2005 Openedhand Wtd.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude "wm8988.h"

/*
 * wm8988 wegistew cache
 * We can't wead the WM8988 wegistew space when we
 * awe using 2 wiwe fow device contwow, so we cache them instead.
 */
static const stwuct weg_defauwt wm8988_weg_defauwts[] = {
	{ 0, 0x0097 },
	{ 1, 0x0097 },
	{ 2, 0x0079 },
	{ 3, 0x0079 },
	{ 5, 0x0008 },
	{ 7, 0x000a },
	{ 8, 0x0000 },
	{ 10, 0x00ff },
	{ 11, 0x00ff },
	{ 12, 0x000f },
	{ 13, 0x000f },
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
	{ 31, 0x0000 },
	{ 32, 0x0000 },
	{ 33, 0x0000 },
	{ 34, 0x0050 },
	{ 35, 0x0050 },
	{ 36, 0x0050 },
	{ 37, 0x0050 },
	{ 40, 0x0079 },
	{ 41, 0x0079 },
	{ 42, 0x0079 },
};

static boow wm8988_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8988_WINVOW:
	case WM8988_WINVOW:
	case WM8988_WOUT1V:
	case WM8988_WOUT1V:
	case WM8988_ADCDAC:
	case WM8988_IFACE:
	case WM8988_SWATE:
	case WM8988_WDAC:
	case WM8988_WDAC:
	case WM8988_BASS:
	case WM8988_TWEBWE:
	case WM8988_WESET:
	case WM8988_3D:
	case WM8988_AWC1:
	case WM8988_AWC2:
	case WM8988_AWC3:
	case WM8988_NGATE:
	case WM8988_WADC:
	case WM8988_WADC:
	case WM8988_ADCTW1:
	case WM8988_ADCTW2:
	case WM8988_PWW1:
	case WM8988_PWW2:
	case WM8988_ADCTW3:
	case WM8988_ADCIN:
	case WM8988_WADCIN:
	case WM8988_WADCIN:
	case WM8988_WOUTM1:
	case WM8988_WOUTM2:
	case WM8988_WOUTM1:
	case WM8988_WOUTM2:
	case WM8988_WOUT2V:
	case WM8988_WOUT2V:
	case WM8988_WPPB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* codec pwivate data */
stwuct wm8988_pwiv {
	stwuct wegmap *wegmap;
	unsigned int syscwk;
	const stwuct snd_pcm_hw_constwaint_wist *syscwk_constwaints;
};

#define wm8988_weset(c)	snd_soc_component_wwite(c, WM8988_WESET, 0)

/*
 * WM8988 Contwows
 */

static const chaw *bass_boost_txt[] = {"Wineaw Contwow", "Adaptive Boost"};
static SOC_ENUM_SINGWE_DECW(bass_boost,
			    WM8988_BASS, 7, bass_boost_txt);

static const chaw *bass_fiwtew_txt[] = { "130Hz @ 48kHz", "200Hz @ 48kHz" };
static SOC_ENUM_SINGWE_DECW(bass_fiwtew,
			    WM8988_BASS, 6, bass_fiwtew_txt);

static const chaw *twebwe_txt[] = {"8kHz", "4kHz"};
static SOC_ENUM_SINGWE_DECW(twebwe,
			    WM8988_TWEBWE, 6, twebwe_txt);

static const chaw *steweo_3d_wc_txt[] = {"200Hz", "500Hz"};
static SOC_ENUM_SINGWE_DECW(steweo_3d_wc,
			    WM8988_3D, 5, steweo_3d_wc_txt);

static const chaw *steweo_3d_uc_txt[] = {"2.2kHz", "1.5kHz"};
static SOC_ENUM_SINGWE_DECW(steweo_3d_uc,
			    WM8988_3D, 6, steweo_3d_uc_txt);

static const chaw *steweo_3d_func_txt[] = {"Captuwe", "Pwayback"};
static SOC_ENUM_SINGWE_DECW(steweo_3d_func,
			    WM8988_3D, 7, steweo_3d_func_txt);

static const chaw *awc_func_txt[] = {"Off", "Wight", "Weft", "Steweo"};
static SOC_ENUM_SINGWE_DECW(awc_func,
			    WM8988_AWC1, 7, awc_func_txt);

static const chaw *ng_type_txt[] = {"Constant PGA Gain",
				    "Mute ADC Output"};
static SOC_ENUM_SINGWE_DECW(ng_type,
			    WM8988_NGATE, 1, ng_type_txt);

static const chaw *deemph_txt[] = {"None", "32Khz", "44.1Khz", "48Khz"};
static SOC_ENUM_SINGWE_DECW(deemph,
			    WM8988_ADCDAC, 1, deemph_txt);

static const chaw *adcpow_txt[] = {"Nowmaw", "W Invewt", "W Invewt",
				   "W + W Invewt"};
static SOC_ENUM_SINGWE_DECW(adcpow,
			    WM8988_ADCDAC, 5, adcpow_txt);

static const DECWAWE_TWV_DB_SCAWE(pga_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -9750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(out_twv, -12100, 100, 1);
static const DECWAWE_TWV_DB_SCAWE(bypass_twv, -1500, 300, 0);

static const stwuct snd_kcontwow_new wm8988_snd_contwows[] = {

SOC_ENUM("Bass Boost", bass_boost),
SOC_ENUM("Bass Fiwtew", bass_fiwtew),
SOC_SINGWE("Bass Vowume", WM8988_BASS, 0, 15, 1),

SOC_SINGWE("Twebwe Vowume", WM8988_TWEBWE, 0, 15, 0),
SOC_ENUM("Twebwe Cut-off", twebwe),

SOC_SINGWE("3D Switch", WM8988_3D, 0, 1, 0),
SOC_SINGWE("3D Vowume", WM8988_3D, 1, 15, 0),
SOC_ENUM("3D Wowew Cut-off", steweo_3d_wc),
SOC_ENUM("3D Uppew Cut-off", steweo_3d_uc),
SOC_ENUM("3D Mode", steweo_3d_func),

SOC_SINGWE("AWC Captuwe Tawget Vowume", WM8988_AWC1, 0, 7, 0),
SOC_SINGWE("AWC Captuwe Max Vowume", WM8988_AWC1, 4, 7, 0),
SOC_ENUM("AWC Captuwe Function", awc_func),
SOC_SINGWE("AWC Captuwe ZC Switch", WM8988_AWC2, 7, 1, 0),
SOC_SINGWE("AWC Captuwe Howd Time", WM8988_AWC2, 0, 15, 0),
SOC_SINGWE("AWC Captuwe Decay Time", WM8988_AWC3, 4, 15, 0),
SOC_SINGWE("AWC Captuwe Attack Time", WM8988_AWC3, 0, 15, 0),
SOC_SINGWE("AWC Captuwe NG Thweshowd", WM8988_NGATE, 3, 31, 0),
SOC_ENUM("AWC Captuwe NG Type", ng_type),
SOC_SINGWE("AWC Captuwe NG Switch", WM8988_NGATE, 0, 1, 0),

SOC_SINGWE("ZC Timeout Switch", WM8988_ADCTW1, 0, 1, 0),

SOC_DOUBWE_W_TWV("Captuwe Digitaw Vowume", WM8988_WADC, WM8988_WADC,
		 0, 255, 0, adc_twv),
SOC_DOUBWE_W_TWV("Captuwe Vowume", WM8988_WINVOW, WM8988_WINVOW,
		 0, 63, 0, pga_twv),
SOC_DOUBWE_W("Captuwe ZC Switch", WM8988_WINVOW, WM8988_WINVOW, 6, 1, 0),
SOC_DOUBWE_W("Captuwe Switch", WM8988_WINVOW, WM8988_WINVOW, 7, 1, 1),

SOC_ENUM("Pwayback De-emphasis", deemph),

SOC_ENUM("Captuwe Powawity", adcpow),
SOC_SINGWE("Pwayback 6dB Attenuate", WM8988_ADCDAC, 7, 1, 0),
SOC_SINGWE("Captuwe 6dB Attenuate", WM8988_ADCDAC, 8, 1, 0),

SOC_DOUBWE_W_TWV("PCM Vowume", WM8988_WDAC, WM8988_WDAC, 0, 255, 0, dac_twv),

SOC_SINGWE_TWV("Weft Mixew Weft Bypass Vowume", WM8988_WOUTM1, 4, 7, 1,
	       bypass_twv),
SOC_SINGWE_TWV("Weft Mixew Wight Bypass Vowume", WM8988_WOUTM2, 4, 7, 1,
	       bypass_twv),
SOC_SINGWE_TWV("Wight Mixew Weft Bypass Vowume", WM8988_WOUTM1, 4, 7, 1,
	       bypass_twv),
SOC_SINGWE_TWV("Wight Mixew Wight Bypass Vowume", WM8988_WOUTM2, 4, 7, 1,
	       bypass_twv),

SOC_DOUBWE_W("Output 1 Pwayback ZC Switch", WM8988_WOUT1V,
	     WM8988_WOUT1V, 7, 1, 0),
SOC_DOUBWE_W_TWV("Output 1 Pwayback Vowume", WM8988_WOUT1V, WM8988_WOUT1V,
		 0, 127, 0, out_twv),

SOC_DOUBWE_W("Output 2 Pwayback ZC Switch", WM8988_WOUT2V,
	     WM8988_WOUT2V, 7, 1, 0),
SOC_DOUBWE_W_TWV("Output 2 Pwayback Vowume", WM8988_WOUT2V, WM8988_WOUT2V,
		 0, 127, 0, out_twv),

};

/*
 * DAPM Contwows
 */

static int wm8988_wwc_contwow(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 adctw2 = snd_soc_component_wead(component, WM8988_ADCTW2);

	/* Use the DAC to gate WWC if active, othewwise use ADC */
	if (snd_soc_component_wead(component, WM8988_PWW2) & 0x180)
		adctw2 &= ~0x4;
	ewse
		adctw2 |= 0x4;

	wetuwn snd_soc_component_wwite(component, WM8988_ADCTW2, adctw2);
}

static const chaw *wm8988_wine_texts[] = {
	"Wine 1", "Wine 2", "PGA", "Diffewentiaw"};

static const unsigned int wm8988_wine_vawues[] = {
	0, 1, 3, 4};

static const stwuct soc_enum wm8988_wwine_enum =
	SOC_VAWUE_ENUM_SINGWE(WM8988_WOUTM1, 0, 7,
			      AWWAY_SIZE(wm8988_wine_texts),
			      wm8988_wine_texts,
			      wm8988_wine_vawues);
static const stwuct snd_kcontwow_new wm8988_weft_wine_contwows =
	SOC_DAPM_ENUM("Woute", wm8988_wwine_enum);

static const stwuct soc_enum wm8988_wwine_enum =
	SOC_VAWUE_ENUM_SINGWE(WM8988_WOUTM1, 0, 7,
			      AWWAY_SIZE(wm8988_wine_texts),
			      wm8988_wine_texts,
			      wm8988_wine_vawues);
static const stwuct snd_kcontwow_new wm8988_wight_wine_contwows =
	SOC_DAPM_ENUM("Woute", wm8988_wwine_enum);

/* Weft Mixew */
static const stwuct snd_kcontwow_new wm8988_weft_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Pwayback Switch", WM8988_WOUTM1, 8, 1, 0),
	SOC_DAPM_SINGWE("Weft Bypass Switch", WM8988_WOUTM1, 7, 1, 0),
	SOC_DAPM_SINGWE("Wight Pwayback Switch", WM8988_WOUTM2, 8, 1, 0),
	SOC_DAPM_SINGWE("Wight Bypass Switch", WM8988_WOUTM2, 7, 1, 0),
};

/* Wight Mixew */
static const stwuct snd_kcontwow_new wm8988_wight_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft Pwayback Switch", WM8988_WOUTM1, 8, 1, 0),
	SOC_DAPM_SINGWE("Weft Bypass Switch", WM8988_WOUTM1, 7, 1, 0),
	SOC_DAPM_SINGWE("Pwayback Switch", WM8988_WOUTM2, 8, 1, 0),
	SOC_DAPM_SINGWE("Wight Bypass Switch", WM8988_WOUTM2, 7, 1, 0),
};

static const chaw *wm8988_pga_sew[] = {"Wine 1", "Wine 2", "Diffewentiaw"};
static const unsigned int wm8988_pga_vaw[] = { 0, 1, 3 };

/* Weft PGA Mux */
static const stwuct soc_enum wm8988_wpga_enum =
	SOC_VAWUE_ENUM_SINGWE(WM8988_WADCIN, 6, 3,
			      AWWAY_SIZE(wm8988_pga_sew),
			      wm8988_pga_sew,
			      wm8988_pga_vaw);
static const stwuct snd_kcontwow_new wm8988_weft_pga_contwows =
	SOC_DAPM_ENUM("Woute", wm8988_wpga_enum);

/* Wight PGA Mux */
static const stwuct soc_enum wm8988_wpga_enum =
	SOC_VAWUE_ENUM_SINGWE(WM8988_WADCIN, 6, 3,
			      AWWAY_SIZE(wm8988_pga_sew),
			      wm8988_pga_sew,
			      wm8988_pga_vaw);
static const stwuct snd_kcontwow_new wm8988_wight_pga_contwows =
	SOC_DAPM_ENUM("Woute", wm8988_wpga_enum);

/* Diffewentiaw Mux */
static const chaw *wm8988_diff_sew[] = {"Wine 1", "Wine 2"};
static SOC_ENUM_SINGWE_DECW(diffmux,
			    WM8988_ADCIN, 8, wm8988_diff_sew);
static const stwuct snd_kcontwow_new wm8988_diffmux_contwows =
	SOC_DAPM_ENUM("Woute", diffmux);

/* Mono ADC Mux */
static const chaw *wm8988_mono_mux[] = {"Steweo", "Mono (Weft)",
	"Mono (Wight)", "Digitaw Mono"};
static SOC_ENUM_SINGWE_DECW(monomux,
			    WM8988_ADCIN, 6, wm8988_mono_mux);
static const stwuct snd_kcontwow_new wm8988_monomux_contwows =
	SOC_DAPM_ENUM("Woute", monomux);

static const stwuct snd_soc_dapm_widget wm8988_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("Mic Bias", WM8988_PWW1, 1, 0, NUWW, 0),

	SND_SOC_DAPM_MUX("Diffewentiaw Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_diffmux_contwows),
	SND_SOC_DAPM_MUX("Weft ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_monomux_contwows),
	SND_SOC_DAPM_MUX("Wight ADC Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_monomux_contwows),

	SND_SOC_DAPM_MUX("Weft PGA Mux", WM8988_PWW1, 5, 0,
		&wm8988_weft_pga_contwows),
	SND_SOC_DAPM_MUX("Wight PGA Mux", WM8988_PWW1, 4, 0,
		&wm8988_wight_pga_contwows),

	SND_SOC_DAPM_MUX("Weft Wine Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_weft_wine_contwows),
	SND_SOC_DAPM_MUX("Wight Wine Mux", SND_SOC_NOPM, 0, 0,
		&wm8988_wight_wine_contwows),

	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", WM8988_PWW1, 2, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", WM8988_PWW1, 3, 0),

	SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback", WM8988_PWW2, 7, 0),
	SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback", WM8988_PWW2, 8, 0),

	SND_SOC_DAPM_MIXEW("Weft Mixew", SND_SOC_NOPM, 0, 0,
		&wm8988_weft_mixew_contwows[0],
		AWWAY_SIZE(wm8988_weft_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Mixew", SND_SOC_NOPM, 0, 0,
		&wm8988_wight_mixew_contwows[0],
		AWWAY_SIZE(wm8988_wight_mixew_contwows)),

	SND_SOC_DAPM_PGA("Wight Out 2", WM8988_PWW2, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft Out 2", WM8988_PWW2, 4, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Out 1", WM8988_PWW2, 5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft Out 1", WM8988_PWW2, 6, 0, NUWW, 0),

	SND_SOC_DAPM_POST("WWC contwow", wm8988_wwc_contwow),

	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("VWEF"),

	SND_SOC_DAPM_INPUT("WINPUT1"),
	SND_SOC_DAPM_INPUT("WINPUT2"),
	SND_SOC_DAPM_INPUT("WINPUT1"),
	SND_SOC_DAPM_INPUT("WINPUT2"),
};

static const stwuct snd_soc_dapm_woute wm8988_dapm_woutes[] = {

	{ "Weft Wine Mux", "Wine 1", "WINPUT1" },
	{ "Weft Wine Mux", "Wine 2", "WINPUT2" },
	{ "Weft Wine Mux", "PGA", "Weft PGA Mux" },
	{ "Weft Wine Mux", "Diffewentiaw", "Diffewentiaw Mux" },

	{ "Wight Wine Mux", "Wine 1", "WINPUT1" },
	{ "Wight Wine Mux", "Wine 2", "WINPUT2" },
	{ "Wight Wine Mux", "PGA", "Wight PGA Mux" },
	{ "Wight Wine Mux", "Diffewentiaw", "Diffewentiaw Mux" },

	{ "Weft PGA Mux", "Wine 1", "WINPUT1" },
	{ "Weft PGA Mux", "Wine 2", "WINPUT2" },
	{ "Weft PGA Mux", "Diffewentiaw", "Diffewentiaw Mux" },

	{ "Wight PGA Mux", "Wine 1", "WINPUT1" },
	{ "Wight PGA Mux", "Wine 2", "WINPUT2" },
	{ "Wight PGA Mux", "Diffewentiaw", "Diffewentiaw Mux" },

	{ "Diffewentiaw Mux", "Wine 1", "WINPUT1" },
	{ "Diffewentiaw Mux", "Wine 1", "WINPUT1" },
	{ "Diffewentiaw Mux", "Wine 2", "WINPUT2" },
	{ "Diffewentiaw Mux", "Wine 2", "WINPUT2" },

	{ "Weft ADC Mux", "Steweo", "Weft PGA Mux" },
	{ "Weft ADC Mux", "Mono (Weft)", "Weft PGA Mux" },
	{ "Weft ADC Mux", "Digitaw Mono", "Weft PGA Mux" },

	{ "Wight ADC Mux", "Steweo", "Wight PGA Mux" },
	{ "Wight ADC Mux", "Mono (Wight)", "Wight PGA Mux" },
	{ "Wight ADC Mux", "Digitaw Mono", "Wight PGA Mux" },

	{ "Weft ADC", NUWW, "Weft ADC Mux" },
	{ "Wight ADC", NUWW, "Wight ADC Mux" },

	{ "Weft Wine Mux", "Wine 1", "WINPUT1" },
	{ "Weft Wine Mux", "Wine 2", "WINPUT2" },
	{ "Weft Wine Mux", "PGA", "Weft PGA Mux" },
	{ "Weft Wine Mux", "Diffewentiaw", "Diffewentiaw Mux" },

	{ "Wight Wine Mux", "Wine 1", "WINPUT1" },
	{ "Wight Wine Mux", "Wine 2", "WINPUT2" },
	{ "Wight Wine Mux", "PGA", "Wight PGA Mux" },
	{ "Wight Wine Mux", "Diffewentiaw", "Diffewentiaw Mux" },

	{ "Weft Mixew", "Pwayback Switch", "Weft DAC" },
	{ "Weft Mixew", "Weft Bypass Switch", "Weft Wine Mux" },
	{ "Weft Mixew", "Wight Pwayback Switch", "Wight DAC" },
	{ "Weft Mixew", "Wight Bypass Switch", "Wight Wine Mux" },

	{ "Wight Mixew", "Weft Pwayback Switch", "Weft DAC" },
	{ "Wight Mixew", "Weft Bypass Switch", "Weft Wine Mux" },
	{ "Wight Mixew", "Pwayback Switch", "Wight DAC" },
	{ "Wight Mixew", "Wight Bypass Switch", "Wight Wine Mux" },

	{ "Weft Out 1", NUWW, "Weft Mixew" },
	{ "WOUT1", NUWW, "Weft Out 1" },
	{ "Wight Out 1", NUWW, "Wight Mixew" },
	{ "WOUT1", NUWW, "Wight Out 1" },

	{ "Weft Out 2", NUWW, "Weft Mixew" },
	{ "WOUT2", NUWW, "Weft Out 2" },
	{ "Wight Out 2", NUWW, "Wight Mixew" },
	{ "WOUT2", NUWW, "Wight Out 2" },
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

	wetuwn -EINVAW;
}

/* The set of wates we can genewate fwom the above fow each SYSCWK */

static const unsigned int wates_12288[] = {
	8000, 12000, 16000, 24000, 32000, 48000, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_12288 = {
	.count	= AWWAY_SIZE(wates_12288),
	.wist	= wates_12288,
};

static const unsigned int wates_112896[] = {
	8000, 11025, 22050, 44100,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_112896 = {
	.count	= AWWAY_SIZE(wates_112896),
	.wist	= wates_112896,
};

static const unsigned int wates_12[] = {
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 41100, 48000,
	48000, 88235, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_12 = {
	.count	= AWWAY_SIZE(wates_12),
	.wist	= wates_12,
};

/*
 * Note that this shouwd be cawwed fwom init wathew than fwom hw_pawams.
 */
static int wm8988_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8988_pwiv *wm8988 = snd_soc_component_get_dwvdata(component);

	switch (fweq) {
	case 11289600:
	case 18432000:
	case 22579200:
	case 36864000:
		wm8988->syscwk_constwaints = &constwaints_112896;
		wm8988->syscwk = fweq;
		wetuwn 0;

	case 12288000:
	case 16934400:
	case 24576000:
	case 33868800:
		wm8988->syscwk_constwaints = &constwaints_12288;
		wm8988->syscwk = fweq;
		wetuwn 0;

	case 12000000:
	case 24000000:
		wm8988->syscwk_constwaints = &constwaints_12;
		wm8988->syscwk = fweq;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int wm8988_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
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

	snd_soc_component_wwite(component, WM8988_IFACE, iface);
	wetuwn 0;
}

static int wm8988_pcm_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8988_pwiv *wm8988 = snd_soc_component_get_dwvdata(component);

	/* The set of sampwe wates that can be suppowted depends on the
	 * MCWK suppwied to the CODEC - enfowce this.
	 */
	if (!wm8988->syscwk) {
		dev_eww(component->dev,
			"No MCWK configuwed, caww set_syscwk() on init\n");
		wetuwn -EINVAW;
	}

	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_WATE,
				   wm8988->syscwk_constwaints);

	wetuwn 0;
}

static int wm8988_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8988_pwiv *wm8988 = snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8988_IFACE) & 0x1f3;
	u16 swate = snd_soc_component_wead(component, WM8988_SWATE) & 0x180;
	int coeff;

	coeff = get_coeff(wm8988->syscwk, pawams_wate(pawams));
	if (coeff < 0) {
		coeff = get_coeff(wm8988->syscwk / 2, pawams_wate(pawams));
		swate |= 0x40;
	}
	if (coeff < 0) {
		dev_eww(component->dev,
			"Unabwe to configuwe sampwe wate %dHz with %dHz MCWK\n",
			pawams_wate(pawams), wm8988->syscwk);
		wetuwn coeff;
	}

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
	snd_soc_component_wwite(component, WM8988_IFACE, iface);
	if (coeff >= 0)
		snd_soc_component_wwite(component, WM8988_SWATE, swate |
			(coeff_div[coeff].sw << 1) | coeff_div[coeff].usb);

	wetuwn 0;
}

static int wm8988_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8988_ADCDAC) & 0xfff7;

	if (mute)
		snd_soc_component_wwite(component, WM8988_ADCDAC, mute_weg | 0x8);
	ewse
		snd_soc_component_wwite(component, WM8988_ADCDAC, mute_weg);
	wetuwn 0;
}

static int wm8988_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8988_pwiv *wm8988 = snd_soc_component_get_dwvdata(component);
	u16 pww_weg = snd_soc_component_wead(component, WM8988_PWW1) & ~0x1c1;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		/* VWEF, VMID=2x50k, digitaw enabwed */
		snd_soc_component_wwite(component, WM8988_PWW1, pww_weg | 0x00c0);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wegcache_sync(wm8988->wegmap);

			/* VWEF, VMID=2x5k */
			snd_soc_component_wwite(component, WM8988_PWW1, pww_weg | 0x1c1);

			/* Chawge caps */
			msweep(100);
		}

		/* VWEF, VMID=2*500k, digitaw stopped */
		snd_soc_component_wwite(component, WM8988_PWW1, pww_weg | 0x0141);
		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WM8988_PWW1, 0x0000);
		bweak;
	}
	wetuwn 0;
}

#define WM8988_WATES SNDWV_PCM_WATE_8000_96000

#define WM8988_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm8988_ops = {
	.stawtup = wm8988_pcm_stawtup,
	.hw_pawams = wm8988_pcm_hw_pawams,
	.set_fmt = wm8988_set_dai_fmt,
	.set_syscwk = wm8988_set_dai_syscwk,
	.mute_stweam = wm8988_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8988_dai = {
	.name = "wm8988-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8988_WATES,
		.fowmats = WM8988_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8988_WATES,
		.fowmats = WM8988_FOWMATS,
	 },
	.ops = &wm8988_ops,
	.symmetwic_wate = 1,
};

static int wm8988_pwobe(stwuct snd_soc_component *component)
{
	int wet = 0;

	wet = wm8988_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset\n");
		wetuwn wet;
	}

	/* set the update bits (we awways update weft then wight) */
	snd_soc_component_update_bits(component, WM8988_WADC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_WDAC, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_WOUT2V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8988_WINVOW, 0x0100, 0x0100);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8988 = {
	.pwobe			= wm8988_pwobe,
	.set_bias_wevew		= wm8988_set_bias_wevew,
	.contwows		= wm8988_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8988_snd_contwows),
	.dapm_widgets		= wm8988_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8988_dapm_widgets),
	.dapm_woutes		= wm8988_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8988_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wm8988_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = WM8988_WPPB,
	.wwiteabwe_weg = wm8988_wwiteabwe,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wm8988_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8988_weg_defauwts),
};

#if defined(CONFIG_SPI_MASTEW)
static int wm8988_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8988_pwiv *wm8988;
	int wet;

	wm8988 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8988_pwiv),
			      GFP_KEWNEW);
	if (wm8988 == NUWW)
		wetuwn -ENOMEM;

	wm8988->wegmap = devm_wegmap_init_spi(spi, &wm8988_wegmap);
	if (IS_EWW(wm8988->wegmap)) {
		wet = PTW_EWW(wm8988->wegmap);
		dev_eww(&spi->dev, "Faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	spi_set_dwvdata(spi, wm8988);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_dev_wm8988, &wm8988_dai, 1);
	wetuwn wet;
}

static stwuct spi_dwivew wm8988_spi_dwivew = {
	.dwivew = {
		.name	= "wm8988",
	},
	.pwobe		= wm8988_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

#if IS_ENABWED(CONFIG_I2C)
static int wm8988_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8988_pwiv *wm8988;
	int wet;

	wm8988 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8988_pwiv),
			      GFP_KEWNEW);
	if (wm8988 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wm8988);

	wm8988->wegmap = devm_wegmap_init_i2c(i2c, &wm8988_wegmap);
	if (IS_EWW(wm8988->wegmap)) {
		wet = PTW_EWW(wm8988->wegmap);
		dev_eww(&i2c->dev, "Faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8988, &wm8988_dai, 1);
	wetuwn wet;
}

static const stwuct i2c_device_id wm8988_i2c_id[] = {
	{ "wm8988", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8988_i2c_id);

static stwuct i2c_dwivew wm8988_i2c_dwivew = {
	.dwivew = {
		.name = "wm8988",
	},
	.pwobe = wm8988_i2c_pwobe,
	.id_tabwe = wm8988_i2c_id,
};
#endif

static int __init wm8988_modinit(void)
{
	int wet = 0;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8988_i2c_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8988 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8988_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8988 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn wet;
}
moduwe_init(wm8988_modinit);

static void __exit wm8988_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8988_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8988_spi_dwivew);
#endif
}
moduwe_exit(wm8988_exit);


MODUWE_DESCWIPTION("ASoC WM8988 dwivew");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
