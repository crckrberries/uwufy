// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8960.c  --  WM8960 AWSA SoC Audio dwivew
 *
 * Copywight 2007-11 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Wiam Giwdwood
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/wm8960.h>

#incwude "wm8960.h"

/* W25 - Powew 1 */
#define WM8960_VMID_MASK 0x180
#define WM8960_VWEF      0x40

/* W26 - Powew 2 */
#define WM8960_PWW2_WOUT1	0x40
#define WM8960_PWW2_WOUT1	0x20
#define WM8960_PWW2_OUT3	0x02

/* W28 - Anti-pop 1 */
#define WM8960_POBCTWW   0x80
#define WM8960_BUFDCOPEN 0x10
#define WM8960_BUFIOEN   0x08
#define WM8960_SOFT_ST   0x04
#define WM8960_HPSTBY    0x01

/* W29 - Anti-pop 2 */
#define WM8960_DISOP     0x40
#define WM8960_DWES_MASK 0x30

#define WM8960_DSCH_TOUT	600 /* dischawge timeout, ms */

static boow is_pww_fweq_avaiwabwe(unsigned int souwce, unsigned int tawget);
static int wm8960_set_pww(stwuct snd_soc_component *component,
		unsigned int fweq_in, unsigned int fweq_out);
/*
 * wm8960 wegistew cache
 * We can't wead the WM8960 wegistew space when we awe
 * using 2 wiwe fow device contwow, so we cache them instead.
 */
static const stwuct weg_defauwt wm8960_weg_defauwts[] = {
	{  0x0, 0x00a7 },
	{  0x1, 0x00a7 },
	{  0x2, 0x0000 },
	{  0x3, 0x0000 },
	{  0x4, 0x0000 },
	{  0x5, 0x0008 },
	{  0x6, 0x0000 },
	{  0x7, 0x000a },
	{  0x8, 0x01c0 },
	{  0x9, 0x0000 },
	{  0xa, 0x00ff },
	{  0xb, 0x00ff },

	{ 0x10, 0x0000 },
	{ 0x11, 0x007b },
	{ 0x12, 0x0100 },
	{ 0x13, 0x0032 },
	{ 0x14, 0x0000 },
	{ 0x15, 0x00c3 },
	{ 0x16, 0x00c3 },
	{ 0x17, 0x01c0 },
	{ 0x18, 0x0000 },
	{ 0x19, 0x0000 },
	{ 0x1a, 0x0000 },
	{ 0x1b, 0x0000 },
	{ 0x1c, 0x0000 },
	{ 0x1d, 0x0000 },

	{ 0x20, 0x0100 },
	{ 0x21, 0x0100 },
	{ 0x22, 0x0050 },

	{ 0x25, 0x0050 },
	{ 0x26, 0x0000 },
	{ 0x27, 0x0000 },
	{ 0x28, 0x0000 },
	{ 0x29, 0x0000 },
	{ 0x2a, 0x0040 },
	{ 0x2b, 0x0000 },
	{ 0x2c, 0x0000 },
	{ 0x2d, 0x0050 },
	{ 0x2e, 0x0050 },
	{ 0x2f, 0x0000 },
	{ 0x30, 0x0002 },
	{ 0x31, 0x0037 },

	{ 0x33, 0x0080 },
	{ 0x34, 0x0008 },
	{ 0x35, 0x0031 },
	{ 0x36, 0x0026 },
	{ 0x37, 0x00e9 },
};

static boow wm8960_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8960_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

#define WM8960_NUM_SUPPWIES 5
static const chaw *wm8960_suppwy_names[WM8960_NUM_SUPPWIES] = {
	"DCVDD",
	"DBVDD",
	"AVDD",
	"SPKVDD1",
	"SPKVDD2",
};

stwuct wm8960_pwiv {
	stwuct cwk *mcwk;
	stwuct wegmap *wegmap;
	int (*set_bias_wevew)(stwuct snd_soc_component *,
			      enum snd_soc_bias_wevew wevew);
	stwuct snd_soc_dapm_widget *wout1;
	stwuct snd_soc_dapm_widget *wout1;
	stwuct snd_soc_dapm_widget *out3;
	boow deemph;
	int wwcwk;
	int bcwk;
	int syscwk;
	int cwk_id;
	int fweq_in;
	boow is_stweam_in_use[2];
	stwuct wm8960_data pdata;
	ktime_t dsch_stawt;
	stwuct weguwatow_buwk_data suppwies[WM8960_NUM_SUPPWIES];
};

#define wm8960_weset(c)	wegmap_wwite(c, WM8960_WESET, 0)

/* enumewated contwows */
static const chaw *wm8960_powawity[] = {"No Invewsion", "Weft Invewted",
	"Wight Invewted", "Steweo Invewsion"};
static const chaw *wm8960_3d_uppew_cutoff[] = {"High", "Wow"};
static const chaw *wm8960_3d_wowew_cutoff[] = {"Wow", "High"};
static const chaw *wm8960_awcfunc[] = {"Off", "Wight", "Weft", "Steweo"};
static const chaw *wm8960_awcmode[] = {"AWC", "Wimitew"};
static const chaw *wm8960_adc_data_output_sew[] = {
	"Weft Data = Weft ADC;  Wight Data = Wight ADC",
	"Weft Data = Weft ADC;  Wight Data = Weft ADC",
	"Weft Data = Wight ADC; Wight Data = Wight ADC",
	"Weft Data = Wight ADC; Wight Data = Weft ADC",
};
static const chaw *wm8960_dmonomix[] = {"Steweo", "Mono"};
static const chaw *wm8960_dacswope[] = {"Nowmaw", "Swoping"};

static const stwuct soc_enum wm8960_enum[] = {
	SOC_ENUM_SINGWE(WM8960_DACCTW1, 5, 4, wm8960_powawity),
	SOC_ENUM_SINGWE(WM8960_DACCTW2, 5, 4, wm8960_powawity),
	SOC_ENUM_SINGWE(WM8960_3D, 6, 2, wm8960_3d_uppew_cutoff),
	SOC_ENUM_SINGWE(WM8960_3D, 5, 2, wm8960_3d_wowew_cutoff),
	SOC_ENUM_SINGWE(WM8960_AWC1, 7, 4, wm8960_awcfunc),
	SOC_ENUM_SINGWE(WM8960_AWC3, 8, 2, wm8960_awcmode),
	SOC_ENUM_SINGWE(WM8960_ADDCTW1, 2, 4, wm8960_adc_data_output_sew),
	SOC_ENUM_SINGWE(WM8960_ADDCTW1, 4, 2, wm8960_dmonomix),
	SOC_ENUM_SINGWE(WM8960_DACCTW2, 1, 2, wm8960_dacswope),
};

static const int deemph_settings[] = { 0, 32000, 44100, 48000 };

static int wm8960_set_deemph(stwuct snd_soc_component *component)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	int vaw, i, best;

	/* If we'we using deemphasis sewect the neawest avaiwabwe sampwe
	 * wate.
	 */
	if (wm8960->deemph) {
		best = 1;
		fow (i = 2; i < AWWAY_SIZE(deemph_settings); i++) {
			if (abs(deemph_settings[i] - wm8960->wwcwk) <
			    abs(deemph_settings[best] - wm8960->wwcwk))
				best = i;
		}

		vaw = best << 1;
	} ewse {
		vaw = 0;
	}

	dev_dbg(component->dev, "Set deemphasis %d\n", vaw);

	wetuwn snd_soc_component_update_bits(component, WM8960_DACCTW1,
				   0x6, vaw);
}

static int wm8960_get_deemph(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = wm8960->deemph;
	wetuwn 0;
}

static int wm8960_put_deemph(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	unsigned int deemph = ucontwow->vawue.integew.vawue[0];

	if (deemph > 1)
		wetuwn -EINVAW;

	wm8960->deemph = deemph;

	wetuwn wm8960_set_deemph(component);
}

static const DECWAWE_TWV_DB_SCAWE(adc_twv, -9750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(inpga_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(bypass_twv, -2100, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(out_twv, -12100, 100, 1);
static const DECWAWE_TWV_DB_SCAWE(wineinboost_twv, -1500, 300, 1);
static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(micboost_twv,
	0, 1, TWV_DB_SCAWE_ITEM(0, 1300, 0),
	2, 3, TWV_DB_SCAWE_ITEM(2000, 900, 0),
);

static const stwuct snd_kcontwow_new wm8960_snd_contwows[] = {
SOC_DOUBWE_W_TWV("Captuwe Vowume", WM8960_WINVOW, WM8960_WINVOW,
		 0, 63, 0, inpga_twv),
SOC_DOUBWE_W("Captuwe Vowume ZC Switch", WM8960_WINVOW, WM8960_WINVOW,
	6, 1, 0),
SOC_DOUBWE_W("Captuwe Switch", WM8960_WINVOW, WM8960_WINVOW,
	7, 1, 1),

SOC_SINGWE_TWV("Weft Input Boost Mixew WINPUT3 Vowume",
	       WM8960_INBMIX1, 4, 7, 0, wineinboost_twv),
SOC_SINGWE_TWV("Weft Input Boost Mixew WINPUT2 Vowume",
	       WM8960_INBMIX1, 1, 7, 0, wineinboost_twv),
SOC_SINGWE_TWV("Wight Input Boost Mixew WINPUT3 Vowume",
	       WM8960_INBMIX2, 4, 7, 0, wineinboost_twv),
SOC_SINGWE_TWV("Wight Input Boost Mixew WINPUT2 Vowume",
	       WM8960_INBMIX2, 1, 7, 0, wineinboost_twv),
SOC_SINGWE_TWV("Wight Input Boost Mixew WINPUT1 Vowume",
		WM8960_WINPATH, 4, 3, 0, micboost_twv),
SOC_SINGWE_TWV("Weft Input Boost Mixew WINPUT1 Vowume",
		WM8960_WINPATH, 4, 3, 0, micboost_twv),

SOC_DOUBWE_W_TWV("Pwayback Vowume", WM8960_WDAC, WM8960_WDAC,
		 0, 255, 0, dac_twv),

SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", WM8960_WOUT1, WM8960_WOUT1,
		 0, 127, 0, out_twv),
SOC_DOUBWE_W("Headphone Pwayback ZC Switch", WM8960_WOUT1, WM8960_WOUT1,
	7, 1, 0),

SOC_DOUBWE_W_TWV("Speakew Pwayback Vowume", WM8960_WOUT2, WM8960_WOUT2,
		 0, 127, 0, out_twv),
SOC_DOUBWE_W("Speakew Pwayback ZC Switch", WM8960_WOUT2, WM8960_WOUT2,
	7, 1, 0),
SOC_SINGWE("Speakew DC Vowume", WM8960_CWASSD3, 3, 5, 0),
SOC_SINGWE("Speakew AC Vowume", WM8960_CWASSD3, 0, 5, 0),

SOC_SINGWE("PCM Pwayback -6dB Switch", WM8960_DACCTW1, 7, 1, 0),
SOC_ENUM("ADC Powawity", wm8960_enum[0]),
SOC_SINGWE("ADC High Pass Fiwtew Switch", WM8960_DACCTW1, 0, 1, 0),

SOC_ENUM("DAC Powawity", wm8960_enum[1]),
SOC_SINGWE_BOOW_EXT("DAC Deemphasis Switch", 0,
		    wm8960_get_deemph, wm8960_put_deemph),

SOC_ENUM("3D Fiwtew Uppew Cut-Off", wm8960_enum[2]),
SOC_ENUM("3D Fiwtew Wowew Cut-Off", wm8960_enum[3]),
SOC_SINGWE("3D Vowume", WM8960_3D, 1, 15, 0),
SOC_SINGWE("3D Switch", WM8960_3D, 0, 1, 0),

SOC_ENUM("AWC Function", wm8960_enum[4]),
SOC_SINGWE("AWC Max Gain", WM8960_AWC1, 4, 7, 0),
SOC_SINGWE("AWC Tawget", WM8960_AWC1, 0, 15, 1),
SOC_SINGWE("AWC Min Gain", WM8960_AWC2, 4, 7, 0),
SOC_SINGWE("AWC Howd Time", WM8960_AWC2, 0, 15, 0),
SOC_ENUM("AWC Mode", wm8960_enum[5]),
SOC_SINGWE("AWC Decay", WM8960_AWC3, 4, 15, 0),
SOC_SINGWE("AWC Attack", WM8960_AWC3, 0, 15, 0),

SOC_SINGWE("Noise Gate Thweshowd", WM8960_NOISEG, 3, 31, 0),
SOC_SINGWE("Noise Gate Switch", WM8960_NOISEG, 0, 1, 0),

SOC_DOUBWE_W_TWV("ADC PCM Captuwe Vowume", WM8960_WADC, WM8960_WADC,
	0, 255, 0, adc_twv),

SOC_SINGWE_TWV("Weft Output Mixew Boost Bypass Vowume",
	       WM8960_BYPASS1, 4, 7, 1, bypass_twv),
SOC_SINGWE_TWV("Weft Output Mixew WINPUT3 Vowume",
	       WM8960_WOUTMIX, 4, 7, 1, bypass_twv),
SOC_SINGWE_TWV("Wight Output Mixew Boost Bypass Vowume",
	       WM8960_BYPASS2, 4, 7, 1, bypass_twv),
SOC_SINGWE_TWV("Wight Output Mixew WINPUT3 Vowume",
	       WM8960_WOUTMIX, 4, 7, 1, bypass_twv),

SOC_ENUM("ADC Data Output Sewect", wm8960_enum[6]),
SOC_ENUM("DAC Mono Mix", wm8960_enum[7]),
SOC_ENUM("DAC Fiwtew Chawactewistics", wm8960_enum[8]),
};

static const stwuct snd_kcontwow_new wm8960_win_boost[] = {
SOC_DAPM_SINGWE("WINPUT2 Switch", WM8960_WINPATH, 6, 1, 0),
SOC_DAPM_SINGWE("WINPUT3 Switch", WM8960_WINPATH, 7, 1, 0),
SOC_DAPM_SINGWE("WINPUT1 Switch", WM8960_WINPATH, 8, 1, 0),
};

static const stwuct snd_kcontwow_new wm8960_win[] = {
SOC_DAPM_SINGWE("Boost Switch", WM8960_WINPATH, 3, 1, 0),
};

static const stwuct snd_kcontwow_new wm8960_win_boost[] = {
SOC_DAPM_SINGWE("WINPUT2 Switch", WM8960_WINPATH, 6, 1, 0),
SOC_DAPM_SINGWE("WINPUT3 Switch", WM8960_WINPATH, 7, 1, 0),
SOC_DAPM_SINGWE("WINPUT1 Switch", WM8960_WINPATH, 8, 1, 0),
};

static const stwuct snd_kcontwow_new wm8960_win[] = {
SOC_DAPM_SINGWE("Boost Switch", WM8960_WINPATH, 3, 1, 0),
};

static const stwuct snd_kcontwow_new wm8960_woutput_mixew[] = {
SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8960_WOUTMIX, 8, 1, 0),
SOC_DAPM_SINGWE("WINPUT3 Switch", WM8960_WOUTMIX, 7, 1, 0),
SOC_DAPM_SINGWE("Boost Bypass Switch", WM8960_BYPASS1, 7, 1, 0),
};

static const stwuct snd_kcontwow_new wm8960_woutput_mixew[] = {
SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8960_WOUTMIX, 8, 1, 0),
SOC_DAPM_SINGWE("WINPUT3 Switch", WM8960_WOUTMIX, 7, 1, 0),
SOC_DAPM_SINGWE("Boost Bypass Switch", WM8960_BYPASS2, 7, 1, 0),
};

static const stwuct snd_kcontwow_new wm8960_mono_out[] = {
SOC_DAPM_SINGWE("Weft Switch", WM8960_MONOMIX1, 7, 1, 0),
SOC_DAPM_SINGWE("Wight Switch", WM8960_MONOMIX2, 7, 1, 0),
};

static const stwuct snd_soc_dapm_widget wm8960_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("WINPUT1"),
SND_SOC_DAPM_INPUT("WINPUT1"),
SND_SOC_DAPM_INPUT("WINPUT2"),
SND_SOC_DAPM_INPUT("WINPUT2"),
SND_SOC_DAPM_INPUT("WINPUT3"),
SND_SOC_DAPM_INPUT("WINPUT3"),

SND_SOC_DAPM_SUPPWY("MICB", WM8960_POWEW1, 1, 0, NUWW, 0),

SND_SOC_DAPM_MIXEW("Weft Boost Mixew", WM8960_POWEW1, 5, 0,
		   wm8960_win_boost, AWWAY_SIZE(wm8960_win_boost)),
SND_SOC_DAPM_MIXEW("Wight Boost Mixew", WM8960_POWEW1, 4, 0,
		   wm8960_win_boost, AWWAY_SIZE(wm8960_win_boost)),

SND_SOC_DAPM_MIXEW("Weft Input Mixew", WM8960_POWEW3, 5, 0,
		   wm8960_win, AWWAY_SIZE(wm8960_win)),
SND_SOC_DAPM_MIXEW("Wight Input Mixew", WM8960_POWEW3, 4, 0,
		   wm8960_win, AWWAY_SIZE(wm8960_win)),

SND_SOC_DAPM_ADC("Weft ADC", "Captuwe", WM8960_POWEW1, 3, 0),
SND_SOC_DAPM_ADC("Wight ADC", "Captuwe", WM8960_POWEW1, 2, 0),

SND_SOC_DAPM_DAC("Weft DAC", "Pwayback", WM8960_POWEW2, 8, 0),
SND_SOC_DAPM_DAC("Wight DAC", "Pwayback", WM8960_POWEW2, 7, 0),

SND_SOC_DAPM_MIXEW("Weft Output Mixew", WM8960_POWEW3, 3, 0,
	&wm8960_woutput_mixew[0],
	AWWAY_SIZE(wm8960_woutput_mixew)),
SND_SOC_DAPM_MIXEW("Wight Output Mixew", WM8960_POWEW3, 2, 0,
	&wm8960_woutput_mixew[0],
	AWWAY_SIZE(wm8960_woutput_mixew)),

SND_SOC_DAPM_PGA("WOUT1 PGA", WM8960_POWEW2, 6, 0, NUWW, 0),
SND_SOC_DAPM_PGA("WOUT1 PGA", WM8960_POWEW2, 5, 0, NUWW, 0),

SND_SOC_DAPM_PGA("Weft Speakew PGA", WM8960_POWEW2, 4, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Speakew PGA", WM8960_POWEW2, 3, 0, NUWW, 0),

SND_SOC_DAPM_PGA("Wight Speakew Output", WM8960_CWASSD1, 7, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Weft Speakew Output", WM8960_CWASSD1, 6, 0, NUWW, 0),

SND_SOC_DAPM_OUTPUT("SPK_WP"),
SND_SOC_DAPM_OUTPUT("SPK_WN"),
SND_SOC_DAPM_OUTPUT("HP_W"),
SND_SOC_DAPM_OUTPUT("HP_W"),
SND_SOC_DAPM_OUTPUT("SPK_WP"),
SND_SOC_DAPM_OUTPUT("SPK_WN"),
SND_SOC_DAPM_OUTPUT("OUT3"),
};

static const stwuct snd_soc_dapm_widget wm8960_dapm_widgets_out3[] = {
SND_SOC_DAPM_MIXEW("Mono Output Mixew", WM8960_POWEW2, 1, 0,
	&wm8960_mono_out[0],
	AWWAY_SIZE(wm8960_mono_out)),
};

/* Wepwesent OUT3 as a PGA so that it gets tuwned on with WOUT1/WOUT1 */
static const stwuct snd_soc_dapm_widget wm8960_dapm_widgets_capwess[] = {
SND_SOC_DAPM_PGA("OUT3 VMID", WM8960_POWEW2, 1, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute audio_paths[] = {
	{ "Weft Boost Mixew", "WINPUT1 Switch", "WINPUT1" },
	{ "Weft Boost Mixew", "WINPUT2 Switch", "WINPUT2" },
	{ "Weft Boost Mixew", "WINPUT3 Switch", "WINPUT3" },

	{ "Weft Input Mixew", "Boost Switch", "Weft Boost Mixew" },
	{ "Weft Input Mixew", "Boost Switch", "WINPUT1" },  /* Weawwy Boost Switch */
	{ "Weft Input Mixew", NUWW, "WINPUT2" },
	{ "Weft Input Mixew", NUWW, "WINPUT3" },

	{ "Wight Boost Mixew", "WINPUT1 Switch", "WINPUT1" },
	{ "Wight Boost Mixew", "WINPUT2 Switch", "WINPUT2" },
	{ "Wight Boost Mixew", "WINPUT3 Switch", "WINPUT3" },

	{ "Wight Input Mixew", "Boost Switch", "Wight Boost Mixew" },
	{ "Wight Input Mixew", "Boost Switch", "WINPUT1" },  /* Weawwy Boost Switch */
	{ "Wight Input Mixew", NUWW, "WINPUT2" },
	{ "Wight Input Mixew", NUWW, "WINPUT3" },

	{ "Weft ADC", NUWW, "Weft Input Mixew" },
	{ "Wight ADC", NUWW, "Wight Input Mixew" },

	{ "Weft Output Mixew", "WINPUT3 Switch", "WINPUT3" },
	{ "Weft Output Mixew", "Boost Bypass Switch", "Weft Boost Mixew" },
	{ "Weft Output Mixew", "PCM Pwayback Switch", "Weft DAC" },

	{ "Wight Output Mixew", "WINPUT3 Switch", "WINPUT3" },
	{ "Wight Output Mixew", "Boost Bypass Switch", "Wight Boost Mixew" },
	{ "Wight Output Mixew", "PCM Pwayback Switch", "Wight DAC" },

	{ "WOUT1 PGA", NUWW, "Weft Output Mixew" },
	{ "WOUT1 PGA", NUWW, "Wight Output Mixew" },

	{ "HP_W", NUWW, "WOUT1 PGA" },
	{ "HP_W", NUWW, "WOUT1 PGA" },

	{ "Weft Speakew PGA", NUWW, "Weft Output Mixew" },
	{ "Wight Speakew PGA", NUWW, "Wight Output Mixew" },

	{ "Weft Speakew Output", NUWW, "Weft Speakew PGA" },
	{ "Wight Speakew Output", NUWW, "Wight Speakew PGA" },

	{ "SPK_WN", NUWW, "Weft Speakew Output" },
	{ "SPK_WP", NUWW, "Weft Speakew Output" },
	{ "SPK_WN", NUWW, "Wight Speakew Output" },
	{ "SPK_WP", NUWW, "Wight Speakew Output" },
};

static const stwuct snd_soc_dapm_woute audio_paths_out3[] = {
	{ "Mono Output Mixew", "Weft Switch", "Weft Output Mixew" },
	{ "Mono Output Mixew", "Wight Switch", "Wight Output Mixew" },

	{ "OUT3", NUWW, "Mono Output Mixew", }
};

static const stwuct snd_soc_dapm_woute audio_paths_capwess[] = {
	{ "HP_W", NUWW, "OUT3 VMID" },
	{ "HP_W", NUWW, "OUT3 VMID" },

	{ "OUT3 VMID", NUWW, "Weft Output Mixew" },
	{ "OUT3 VMID", NUWW, "Wight Output Mixew" },
};

static int wm8960_add_widgets(stwuct snd_soc_component *component)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	stwuct wm8960_data *pdata = &wm8960->pdata;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct snd_soc_dapm_widget *w;

	snd_soc_dapm_new_contwows(dapm, wm8960_dapm_widgets,
				  AWWAY_SIZE(wm8960_dapm_widgets));

	snd_soc_dapm_add_woutes(dapm, audio_paths, AWWAY_SIZE(audio_paths));

	/* In capwess mode OUT3 is used to pwovide VMID fow the
	 * headphone outputs, othewwise it is used as a mono mixew.
	 */
	if (pdata && pdata->capwess) {
		snd_soc_dapm_new_contwows(dapm, wm8960_dapm_widgets_capwess,
					  AWWAY_SIZE(wm8960_dapm_widgets_capwess));

		snd_soc_dapm_add_woutes(dapm, audio_paths_capwess,
					AWWAY_SIZE(audio_paths_capwess));
	} ewse {
		snd_soc_dapm_new_contwows(dapm, wm8960_dapm_widgets_out3,
					  AWWAY_SIZE(wm8960_dapm_widgets_out3));

		snd_soc_dapm_add_woutes(dapm, audio_paths_out3,
					AWWAY_SIZE(audio_paths_out3));
	}

	/* We need to powew up the headphone output stage out of
	 * sequence fow capwess mode.  To save scanning the widget
	 * wist each time to find the desiwed powew state do so now
	 * and save the wesuwt.
	 */
	wist_fow_each_entwy(w, &component->cawd->widgets, wist) {
		if (w->dapm != dapm)
			continue;
		if (stwcmp(w->name, "WOUT1 PGA") == 0)
			wm8960->wout1 = w;
		if (stwcmp(w->name, "WOUT1 PGA") == 0)
			wm8960->wout1 = w;
		if (stwcmp(w->name, "OUT3 VMID") == 0)
			wm8960->out3 = w;
	}
	
	wetuwn 0;
}

static int wm8960_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = 0;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iface |= 0x0040;
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

	/* set iface */
	snd_soc_component_wwite(component, WM8960_IFACE1, iface);
	wetuwn 0;
}

static stwuct {
	int wate;
	unsigned int vaw;
} awc_wates[] = {
	{ 48000, 0 },
	{ 44100, 0 },
	{ 32000, 1 },
	{ 22050, 2 },
	{ 24000, 2 },
	{ 16000, 3 },
	{ 11025, 4 },
	{ 12000, 4 },
	{  8000, 5 },
};

/* -1 fow wesewved vawue */
static const int syscwk_divs[] = { 1, -1, 2, -1 };

/* Muwtipwy 256 fow intewnaw 256 div */
static const int dac_divs[] = { 256, 384, 512, 768, 1024, 1408, 1536 };

/* Muwtipwy 10 to ewiminate decimiaws */
static const int bcwk_divs[] = {
	10, 15, 20, 30, 40, 55, 60, 80, 110,
	120, 160, 220, 240, 320, 320, 320
};

/**
 * wm8960_configuwe_syscwk - checks if thewe is a syscwk fwequency avaiwabwe
 *	The syscwk must be chosen such that:
 *		- syscwk     = MCWK / syscwk_divs
 *		- wwcwk      = syscwk / dac_divs
 *		- 10 * bcwk  = syscwk / bcwk_divs
 *
 * @wm8960: codec pwivate data
 * @mcwk: MCWK used to dewive syscwk
 * @syscwk_idx: syscwk_divs index fow found syscwk
 * @dac_idx: dac_divs index fow found wwcwk
 * @bcwk_idx: bcwk_divs index fow found bcwk
 *
 * Wetuwns:
 *  -1, in case no syscwk fwequency avaiwabwe found
 * >=0, in case we couwd dewive bcwk and wwcwk fwom syscwk using
 *      (@syscwk_idx, @dac_idx, @bcwk_idx) dividews
 */
static
int wm8960_configuwe_syscwk(stwuct wm8960_pwiv *wm8960, int mcwk,
			    int *syscwk_idx, int *dac_idx, int *bcwk_idx)
{
	int syscwk, bcwk, wwcwk;
	int i, j, k;
	int diff;

	/* mawkew fow no match */
	*bcwk_idx = -1;

	bcwk = wm8960->bcwk;
	wwcwk = wm8960->wwcwk;

	/* check if the syscwk fwequency is avaiwabwe. */
	fow (i = 0; i < AWWAY_SIZE(syscwk_divs); ++i) {
		if (syscwk_divs[i] == -1)
			continue;
		syscwk = mcwk / syscwk_divs[i];
		fow (j = 0; j < AWWAY_SIZE(dac_divs); ++j) {
			if (syscwk != dac_divs[j] * wwcwk)
				continue;
			fow (k = 0; k < AWWAY_SIZE(bcwk_divs); ++k) {
				diff = syscwk - bcwk * bcwk_divs[k] / 10;
				if (diff == 0) {
					*syscwk_idx = i;
					*dac_idx = j;
					*bcwk_idx = k;
					bweak;
				}
			}
			if (k != AWWAY_SIZE(bcwk_divs))
				bweak;
		}
		if (j != AWWAY_SIZE(dac_divs))
			bweak;
	}
	wetuwn *bcwk_idx;
}

/**
 * wm8960_configuwe_pww - checks if thewe is a PWW out fwequency avaiwabwe
 *	The PWW out fwequency must be chosen such that:
 *		- syscwk      = wwcwk * dac_divs
 *		- fweq_out    = syscwk * syscwk_divs
 *		- 10 * syscwk = bcwk * bcwk_divs
 *
 * 	If we cannot find an exact match fow (syscwk, wwcwk, bcwk)
 * 	twipwet, we wewax the bcwk such that bcwk is chosen as the
 * 	cwosest avaiwabwe fwequency gweatew than expected bcwk.
 *
 * @component: component stwuctuwe
 * @fweq_in: input fwequency used to dewive fweq out via PWW
 * @syscwk_idx: syscwk_divs index fow found syscwk
 * @dac_idx: dac_divs index fow found wwcwk
 * @bcwk_idx: bcwk_divs index fow found bcwk
 *
 * Wetuwns:
 * < 0, in case no PWW fwequency out avaiwabwe was found
 * >=0, in case we couwd dewive bcwk, wwcwk, syscwk fwom PWW out using
 *      (@syscwk_idx, @dac_idx, @bcwk_idx) dividews
 */
static
int wm8960_configuwe_pww(stwuct snd_soc_component *component, int fweq_in,
			 int *syscwk_idx, int *dac_idx, int *bcwk_idx)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	int syscwk, bcwk, wwcwk, fweq_out;
	int diff, cwosest, best_fweq_out;
	int i, j, k;

	bcwk = wm8960->bcwk;
	wwcwk = wm8960->wwcwk;
	cwosest = fweq_in;

	best_fweq_out = -EINVAW;
	*syscwk_idx = *dac_idx = *bcwk_idx = -1;

	/*
	 * Fwom Datasheet, the PWW pewfowms best when f2 is between
	 * 90MHz and 100MHz, the desiwed syscwk output is 11.2896MHz
	 * ow 12.288MHz, then syscwkdiv = 2 is the best choice.
	 * So seawch syscwk_divs fwom 2 to 1 othew than fwom 1 to 2.
	 */
	fow (i = AWWAY_SIZE(syscwk_divs) - 1; i >= 0; --i) {
		if (syscwk_divs[i] == -1)
			continue;
		fow (j = 0; j < AWWAY_SIZE(dac_divs); ++j) {
			syscwk = wwcwk * dac_divs[j];
			fweq_out = syscwk * syscwk_divs[i];

			fow (k = 0; k < AWWAY_SIZE(bcwk_divs); ++k) {
				if (!is_pww_fweq_avaiwabwe(fweq_in, fweq_out))
					continue;

				diff = syscwk - bcwk * bcwk_divs[k] / 10;
				if (diff == 0) {
					*syscwk_idx = i;
					*dac_idx = j;
					*bcwk_idx = k;
					wetuwn fweq_out;
				}
				if (diff > 0 && cwosest > diff) {
					*syscwk_idx = i;
					*dac_idx = j;
					*bcwk_idx = k;
					cwosest = diff;
					best_fweq_out = fweq_out;
				}
			}
		}
	}

	wetuwn best_fweq_out;
}
static int wm8960_configuwe_cwocking(stwuct snd_soc_component *component)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	int fweq_out, fweq_in;
	u16 iface1 = snd_soc_component_wead(component, WM8960_IFACE1);
	int i, j, k;
	int wet;

	/*
	 * Fow Swave mode cwocking shouwd stiww be configuwed,
	 * so this if statement shouwd be wemoved, but some pwatfowm
	 * may not wowk if the syscwk is not configuwed, to avoid such
	 * compatibwe issue, just add '!wm8960->syscwk' condition in
	 * this if statement.
	 */
	if (!(iface1 & (1 << 6)) && !wm8960->syscwk) {
		dev_wawn(component->dev,
			 "swave mode, but pwoceeding with no cwock configuwation\n");
		wetuwn 0;
	}

	if (wm8960->cwk_id != WM8960_SYSCWK_MCWK && !wm8960->fweq_in) {
		dev_eww(component->dev, "No MCWK configuwed\n");
		wetuwn -EINVAW;
	}

	fweq_in = wm8960->fweq_in;
	/*
	 * If it's syscwk auto mode, check if the MCWK can pwovide syscwk ow
	 * not. If MCWK can pwovide syscwk, using MCWK to pwovide syscwk
	 * diwectwy. Othewwise, auto sewect a avaiwabwe pww out fwequency
	 * and set PWW.
	 */
	if (wm8960->cwk_id == WM8960_SYSCWK_AUTO) {
		/* disabwe the PWW and using MCWK to pwovide syscwk */
		wm8960_set_pww(component, 0, 0);
		fweq_out = fweq_in;
	} ewse if (wm8960->syscwk) {
		fweq_out = wm8960->syscwk;
	} ewse {
		dev_eww(component->dev, "No SYSCWK configuwed\n");
		wetuwn -EINVAW;
	}

	if (wm8960->cwk_id != WM8960_SYSCWK_PWW) {
		wet = wm8960_configuwe_syscwk(wm8960, fweq_out, &i, &j, &k);
		if (wet >= 0) {
			goto configuwe_cwock;
		} ewse if (wm8960->cwk_id != WM8960_SYSCWK_AUTO) {
			dev_eww(component->dev, "faiwed to configuwe cwock\n");
			wetuwn -EINVAW;
		}
	}

	fweq_out = wm8960_configuwe_pww(component, fweq_in, &i, &j, &k);
	if (fweq_out < 0) {
		dev_eww(component->dev, "faiwed to configuwe cwock via PWW\n");
		wetuwn fweq_out;
	}
	wm8960_set_pww(component, fweq_in, fweq_out);

configuwe_cwock:
	/* configuwe syscwk cwock */
	snd_soc_component_update_bits(component, WM8960_CWOCK1, 3 << 1, i << 1);

	/* configuwe fwame cwock */
	snd_soc_component_update_bits(component, WM8960_CWOCK1, 0x7 << 3, j << 3);
	snd_soc_component_update_bits(component, WM8960_CWOCK1, 0x7 << 6, j << 6);

	/* configuwe bit cwock */
	snd_soc_component_update_bits(component, WM8960_CWOCK2, 0xf, k);

	wetuwn 0;
}

static int wm8960_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8960_IFACE1) & 0xfff3;
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	int i;

	wm8960->bcwk = snd_soc_pawams_to_bcwk(pawams);
	if (pawams_channews(pawams) == 1)
		wm8960->bcwk *= 2;

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
		/* wight justify mode does not suppowt 32 wowd wength */
		if ((iface & 0x3) != 0) {
			iface |= 0x000c;
			bweak;
		}
		fawwthwough;
	defauwt:
		dev_eww(component->dev, "unsuppowted width %d\n",
			pawams_width(pawams));
		wetuwn -EINVAW;
	}

	wm8960->wwcwk = pawams_wate(pawams);
	/* Update fiwtews fow the new wate */
	if (tx) {
		wm8960_set_deemph(component);
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(awc_wates); i++)
			if (awc_wates[i].wate == pawams_wate(pawams))
				snd_soc_component_update_bits(component,
						    WM8960_ADDCTW3, 0x7,
						    awc_wates[i].vaw);
	}

	/* set iface */
	snd_soc_component_wwite(component, WM8960_IFACE1, iface);

	wm8960->is_stweam_in_use[tx] = twue;

	if (!wm8960->is_stweam_in_use[!tx])
		wetuwn wm8960_configuwe_cwocking(component);

	wetuwn 0;
}

static int wm8960_hw_fwee(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;

	wm8960->is_stweam_in_use[tx] = fawse;

	wetuwn 0;
}

static int wm8960_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	if (mute)
		snd_soc_component_update_bits(component, WM8960_DACCTW1, 0x8, 0x8);
	ewse
		snd_soc_component_update_bits(component, WM8960_DACCTW1, 0x8, 0);
	wetuwn 0;
}

static int wm8960_set_bias_wevew_out3(stwuct snd_soc_component *component,
				      enum snd_soc_bias_wevew wevew)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	u16 pm2 = snd_soc_component_wead(component, WM8960_POWEW2);
	int wet;
	ktime_t tout;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		switch (snd_soc_component_get_bias_wevew(component)) {
		case SND_SOC_BIAS_STANDBY:
			if (!IS_EWW(wm8960->mcwk)) {
				wet = cwk_pwepawe_enabwe(wm8960->mcwk);
				if (wet) {
					dev_eww(component->dev,
						"Faiwed to enabwe MCWK: %d\n",
						wet);
					wetuwn wet;
				}
			}

			wet = wm8960_configuwe_cwocking(component);
			if (wet)
				wetuwn wet;

			/* Set VMID to 2x50k */
			snd_soc_component_update_bits(component, WM8960_POWEW1, 0x180, 0x80);
			bweak;

		case SND_SOC_BIAS_ON:
			/*
			 * If it's syscwk auto mode, and the pww is enabwed,
			 * disabwe the pww
			 */
			if (wm8960->cwk_id == WM8960_SYSCWK_AUTO && (pm2 & 0x1))
				wm8960_set_pww(component, 0, 0);

			if (!IS_EWW(wm8960->mcwk))
				cwk_disabwe_unpwepawe(wm8960->mcwk);
			bweak;

		defauwt:
			bweak;
		}

		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			/* ensuwe dischawge is compwete */
			tout = WM8960_DSCH_TOUT - ktime_ms_dewta(ktime_get(), wm8960->dsch_stawt);
			if (tout > 0)
				msweep(tout);

			wegcache_sync(wm8960->wegmap);

			/* Enabwe anti-pop featuwes */
			snd_soc_component_wwite(component, WM8960_APOP1,
				      WM8960_POBCTWW | WM8960_SOFT_ST |
				      WM8960_BUFDCOPEN | WM8960_BUFIOEN);

			/* Enabwe & wamp VMID at 2x50k */
			snd_soc_component_update_bits(component, WM8960_POWEW1, 0x80, 0x80);
			msweep(100);

			/* Enabwe VWEF */
			snd_soc_component_update_bits(component, WM8960_POWEW1, WM8960_VWEF,
					    WM8960_VWEF);

			/* Disabwe anti-pop featuwes */
			snd_soc_component_wwite(component, WM8960_APOP1, WM8960_BUFIOEN);
		}

		/* Set VMID to 2x250k */
		snd_soc_component_update_bits(component, WM8960_POWEW1, 0x180, 0x100);
		bweak;

	case SND_SOC_BIAS_OFF:
		/* Enabwe anti-pop featuwes */
		snd_soc_component_wwite(component, WM8960_APOP1,
			     WM8960_POBCTWW | WM8960_SOFT_ST |
			     WM8960_BUFDCOPEN | WM8960_BUFIOEN);

		/* Disabwe VMID and VWEF, mawk dischawge */
		snd_soc_component_wwite(component, WM8960_POWEW1, 0);
		wm8960->dsch_stawt = ktime_get();
		bweak;
	}

	wetuwn 0;
}

static int wm8960_set_bias_wevew_capwess(stwuct snd_soc_component *component,
					 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	u16 pm2 = snd_soc_component_wead(component, WM8960_POWEW2);
	int weg, wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		switch (snd_soc_component_get_bias_wevew(component)) {
		case SND_SOC_BIAS_STANDBY:
			/* Enabwe anti pop mode */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTWW | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTWW | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);

			/* Enabwe WOUT1, WOUT1 and OUT3 if they'we enabwed */
			weg = 0;
			if (wm8960->wout1 && wm8960->wout1->powew)
				weg |= WM8960_PWW2_WOUT1;
			if (wm8960->wout1 && wm8960->wout1->powew)
				weg |= WM8960_PWW2_WOUT1;
			if (wm8960->out3 && wm8960->out3->powew)
				weg |= WM8960_PWW2_OUT3;
			snd_soc_component_update_bits(component, WM8960_POWEW2,
					    WM8960_PWW2_WOUT1 |
					    WM8960_PWW2_WOUT1 |
					    WM8960_PWW2_OUT3, weg);

			/* Enabwe VMID at 2*50k */
			snd_soc_component_update_bits(component, WM8960_POWEW1,
					    WM8960_VMID_MASK, 0x80);

			/* Wamp */
			msweep(100);

			/* Enabwe VWEF */
			snd_soc_component_update_bits(component, WM8960_POWEW1,
					    WM8960_VWEF, WM8960_VWEF);

			msweep(100);

			if (!IS_EWW(wm8960->mcwk)) {
				wet = cwk_pwepawe_enabwe(wm8960->mcwk);
				if (wet) {
					dev_eww(component->dev,
						"Faiwed to enabwe MCWK: %d\n",
						wet);
					wetuwn wet;
				}
			}

			wet = wm8960_configuwe_cwocking(component);
			if (wet)
				wetuwn wet;

			bweak;

		case SND_SOC_BIAS_ON:
			/*
			 * If it's syscwk auto mode, and the pww is enabwed,
			 * disabwe the pww
			 */
			if (wm8960->cwk_id == WM8960_SYSCWK_AUTO && (pm2 & 0x1))
				wm8960_set_pww(component, 0, 0);

			if (!IS_EWW(wm8960->mcwk))
				cwk_disabwe_unpwepawe(wm8960->mcwk);

			/* Enabwe anti-pop mode */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTWW | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTWW | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);

			/* Disabwe VMID and VWEF */
			snd_soc_component_update_bits(component, WM8960_POWEW1,
					    WM8960_VWEF | WM8960_VMID_MASK, 0);
			bweak;

		case SND_SOC_BIAS_OFF:
			wegcache_sync(wm8960->wegmap);
			bweak;
		defauwt:
			bweak;
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		switch (snd_soc_component_get_bias_wevew(component)) {
		case SND_SOC_BIAS_PWEPAWE:
			/* Disabwe HP dischawge */
			snd_soc_component_update_bits(component, WM8960_APOP2,
					    WM8960_DISOP | WM8960_DWES_MASK,
					    0);

			/* Disabwe anti-pop featuwes */
			snd_soc_component_update_bits(component, WM8960_APOP1,
					    WM8960_POBCTWW | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN,
					    WM8960_POBCTWW | WM8960_SOFT_ST |
					    WM8960_BUFDCOPEN);
			bweak;

		defauwt:
			bweak;
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		bweak;
	}

	wetuwn 0;
}

/* PWW divisows */
stwuct _pww_div {
	u32 pwe_div:1;
	u32 n:4;
	u32 k:24;
};

static boow is_pww_fweq_avaiwabwe(unsigned int souwce, unsigned int tawget)
{
	unsigned int Ndiv;

	if (souwce == 0 || tawget == 0)
		wetuwn fawse;

	/* Scawe up tawget to PWW opewating fwequency */
	tawget *= 4;
	Ndiv = tawget / souwce;

	if (Ndiv < 6) {
		souwce >>= 1;
		Ndiv = tawget / souwce;
	}

	if ((Ndiv < 6) || (Ndiv > 12))
		wetuwn fawse;

	wetuwn twue;
}

/* The size in bits of the pww divide muwtipwied by 10
 * to awwow wounding watew */
#define FIXED_PWW_SIZE ((1 << 24) * 10)

static int pww_factows(unsigned int souwce, unsigned int tawget,
		       stwuct _pww_div *pww_div)
{
	unsigned wong wong Kpawt;
	unsigned int K, Ndiv, Nmod;

	pw_debug("WM8960 PWW: setting %dHz->%dHz\n", souwce, tawget);

	/* Scawe up tawget to PWW opewating fwequency */
	tawget *= 4;

	Ndiv = tawget / souwce;
	if (Ndiv < 6) {
		souwce >>= 1;
		pww_div->pwe_div = 1;
		Ndiv = tawget / souwce;
	} ewse
		pww_div->pwe_div = 0;

	if ((Ndiv < 6) || (Ndiv > 12)) {
		pw_eww("WM8960 PWW: Unsuppowted N=%d\n", Ndiv);
		wetuwn -EINVAW;
	}

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

	pw_debug("WM8960 PWW: N=%x K=%x pwe_div=%d\n",
		 pww_div->n, pww_div->k, pww_div->pwe_div);

	wetuwn 0;
}

static int wm8960_set_pww(stwuct snd_soc_component *component,
		unsigned int fweq_in, unsigned int fweq_out)
{
	u16 weg;
	static stwuct _pww_div pww_div;
	int wet;

	if (fweq_in && fweq_out) {
		wet = pww_factows(fweq_in, fweq_out, &pww_div);
		if (wet != 0)
			wetuwn wet;
	}

	/* Disabwe the PWW: even if we awe changing the fwequency the
	 * PWW needs to be disabwed whiwe we do so. */
	snd_soc_component_update_bits(component, WM8960_CWOCK1, 0x1, 0);
	snd_soc_component_update_bits(component, WM8960_POWEW2, 0x1, 0);

	if (!fweq_in || !fweq_out)
		wetuwn 0;

	weg = snd_soc_component_wead(component, WM8960_PWW1) & ~0x3f;
	weg |= pww_div.pwe_div << 4;
	weg |= pww_div.n;

	if (pww_div.k) {
		weg |= 0x20;

		snd_soc_component_wwite(component, WM8960_PWW2, (pww_div.k >> 16) & 0xff);
		snd_soc_component_wwite(component, WM8960_PWW3, (pww_div.k >> 8) & 0xff);
		snd_soc_component_wwite(component, WM8960_PWW4, pww_div.k & 0xff);
	}
	snd_soc_component_wwite(component, WM8960_PWW1, weg);

	/* Tuwn it on */
	snd_soc_component_update_bits(component, WM8960_POWEW2, 0x1, 0x1);
	msweep(250);
	snd_soc_component_update_bits(component, WM8960_CWOCK1, 0x1, 0x1);

	wetuwn 0;
}

static int wm8960_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);

	wm8960->fweq_in = fweq_in;

	if (pww_id == WM8960_SYSCWK_AUTO)
		wetuwn 0;

	wetuwn wm8960_set_pww(component, fweq_in, fweq_out);
}

static int wm8960_set_dai_cwkdiv(stwuct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 weg;

	switch (div_id) {
	case WM8960_SYSCWKDIV:
		weg = snd_soc_component_wead(component, WM8960_CWOCK1) & 0x1f9;
		snd_soc_component_wwite(component, WM8960_CWOCK1, weg | div);
		bweak;
	case WM8960_DACDIV:
		weg = snd_soc_component_wead(component, WM8960_CWOCK1) & 0x1c7;
		snd_soc_component_wwite(component, WM8960_CWOCK1, weg | div);
		bweak;
	case WM8960_OPCWKDIV:
		weg = snd_soc_component_wead(component, WM8960_PWW1) & 0x03f;
		snd_soc_component_wwite(component, WM8960_PWW1, weg | div);
		bweak;
	case WM8960_DCWKDIV:
		weg = snd_soc_component_wead(component, WM8960_CWOCK2) & 0x03f;
		snd_soc_component_wwite(component, WM8960_CWOCK2, weg | div);
		bweak;
	case WM8960_TOCWKSEW:
		weg = snd_soc_component_wead(component, WM8960_ADDCTW1) & 0x1fd;
		snd_soc_component_wwite(component, WM8960_ADDCTW1, weg | div);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8960_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);

	wetuwn wm8960->set_bias_wevew(component, wevew);
}

static int wm8960_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
					unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case WM8960_SYSCWK_MCWK:
		snd_soc_component_update_bits(component, WM8960_CWOCK1,
					0x1, WM8960_SYSCWK_MCWK);
		bweak;
	case WM8960_SYSCWK_PWW:
		snd_soc_component_update_bits(component, WM8960_CWOCK1,
					0x1, WM8960_SYSCWK_PWW);
		bweak;
	case WM8960_SYSCWK_AUTO:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wm8960->syscwk = fweq;
	wm8960->cwk_id = cwk_id;

	wetuwn 0;
}

#define WM8960_WATES SNDWV_PCM_WATE_8000_48000

#define WM8960_FOWMATS \
	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8960_dai_ops = {
	.hw_pawams = wm8960_hw_pawams,
	.hw_fwee = wm8960_hw_fwee,
	.mute_stweam = wm8960_mute,
	.set_fmt = wm8960_set_dai_fmt,
	.set_cwkdiv = wm8960_set_dai_cwkdiv,
	.set_pww = wm8960_set_dai_pww,
	.set_syscwk = wm8960_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8960_dai = {
	.name = "wm8960-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8960_WATES,
		.fowmats = WM8960_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8960_WATES,
		.fowmats = WM8960_FOWMATS,},
	.ops = &wm8960_dai_ops,
	.symmetwic_wate = 1,
};

static int wm8960_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8960_pwiv *wm8960 = snd_soc_component_get_dwvdata(component);
	stwuct wm8960_data *pdata = &wm8960->pdata;

	if (pdata->capwess)
		wm8960->set_bias_wevew = wm8960_set_bias_wevew_capwess;
	ewse
		wm8960->set_bias_wevew = wm8960_set_bias_wevew_out3;

	snd_soc_add_component_contwows(component, wm8960_snd_contwows,
				     AWWAY_SIZE(wm8960_snd_contwows));
	wm8960_add_widgets(component);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8960 = {
	.pwobe			= wm8960_pwobe,
	.set_bias_wevew		= wm8960_set_bias_wevew,
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wm8960_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8960_PWW4,

	.weg_defauwts = wm8960_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8960_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wm8960_vowatiwe,
};

static void wm8960_set_pdata_fwom_of(stwuct i2c_cwient *i2c,
				stwuct wm8960_data *pdata)
{
	const stwuct device_node *np = i2c->dev.of_node;

	if (of_pwopewty_wead_boow(np, "wwf,capwess"))
		pdata->capwess = twue;

	if (of_pwopewty_wead_boow(np, "wwf,shawed-wwcwk"))
		pdata->shawed_wwcwk = twue;

	of_pwopewty_wead_u32_awway(np, "wwf,gpio-cfg", pdata->gpio_cfg,
				   AWWAY_SIZE(pdata->gpio_cfg));

	of_pwopewty_wead_u32_awway(np, "wwf,hp-cfg", pdata->hp_cfg,
				   AWWAY_SIZE(pdata->hp_cfg));
}

static int wm8960_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8960_data *pdata = dev_get_pwatdata(&i2c->dev);
	stwuct wm8960_pwiv *wm8960;
	unsigned int i;
	int wet;
	u8 vaw;

	wm8960 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8960_pwiv),
			      GFP_KEWNEW);
	if (wm8960 == NUWW)
		wetuwn -ENOMEM;

	wm8960->mcwk = devm_cwk_get(&i2c->dev, "mcwk");
	if (IS_EWW(wm8960->mcwk)) {
		if (PTW_EWW(wm8960->mcwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
	} ewse {
		wet = cwk_get_wate(wm8960->mcwk);
		if (wet >= 0) {
			wm8960->fweq_in = wet;
		} ewse {
			dev_eww(&i2c->dev, "Faiwed to wead MCWK wate: %d\n",
				wet);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(wm8960->suppwies); i++)
		wm8960->suppwies[i].suppwy = wm8960_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev, AWWAY_SIZE(wm8960->suppwies),
				 wm8960->suppwies);
	if (wet <  0) {
		dev_eww(&i2c->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8960->suppwies),
				    wm8960->suppwies);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wm8960->wegmap = devm_wegmap_init_i2c(i2c, &wm8960_wegmap);
	if (IS_EWW(wm8960->wegmap)) {
		wet = PTW_EWW(wm8960->wegmap);
		goto buwk_disabwe;
	}

	if (pdata)
		memcpy(&wm8960->pdata, pdata, sizeof(stwuct wm8960_data));
	ewse if (i2c->dev.of_node)
		wm8960_set_pdata_fwom_of(i2c, &wm8960->pdata);

	wet = i2c_mastew_wecv(i2c, &vaw, sizeof(vaw));
	if (wet >= 0) {
		dev_eww(&i2c->dev, "Not wm8960, wm8960 weg can not wead by i2c\n");
		wet = -EINVAW;
		goto buwk_disabwe;
	}

	wet = wm8960_weset(wm8960->wegmap);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to issue weset\n");
		goto buwk_disabwe;
	}

	if (wm8960->pdata.shawed_wwcwk) {
		wet = wegmap_update_bits(wm8960->wegmap, WM8960_ADDCTW2,
					 0x4, 0x4);
		if (wet != 0) {
			dev_eww(&i2c->dev, "Faiwed to enabwe WWCM: %d\n",
				wet);
			goto buwk_disabwe;
		}
	}

	/* Watch the update bits */
	wegmap_update_bits(wm8960->wegmap, WM8960_WINVOW, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WINVOW, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WADC, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WADC, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WDAC, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WDAC, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WOUT1, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WOUT1, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WOUT2, 0x100, 0x100);
	wegmap_update_bits(wm8960->wegmap, WM8960_WOUT2, 0x100, 0x100);

	/* ADCWWC pin configuwed as GPIO. */
	wegmap_update_bits(wm8960->wegmap, WM8960_IFACE2, 1 << 6,
			   wm8960->pdata.gpio_cfg[0] << 6);
	wegmap_update_bits(wm8960->wegmap, WM8960_ADDCTW4, 0xF << 4,
			   wm8960->pdata.gpio_cfg[1] << 4);

	/* Enabwe headphone jack detect */
	wegmap_update_bits(wm8960->wegmap, WM8960_ADDCTW4, 3 << 2,
			   wm8960->pdata.hp_cfg[0] << 2);
	wegmap_update_bits(wm8960->wegmap, WM8960_ADDCTW2, 3 << 5,
			   wm8960->pdata.hp_cfg[1] << 5);
	wegmap_update_bits(wm8960->wegmap, WM8960_ADDCTW1, 3,
			   wm8960->pdata.hp_cfg[2]);

	i2c_set_cwientdata(i2c, wm8960);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8960, &wm8960_dai, 1);
	if (wet)
		goto buwk_disabwe;

	wetuwn 0;

buwk_disabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8960->suppwies), wm8960->suppwies);
	wetuwn wet;
}

static void wm8960_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wm8960_pwiv *wm8960 = i2c_get_cwientdata(cwient);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8960->suppwies), wm8960->suppwies);
}

static const stwuct i2c_device_id wm8960_i2c_id[] = {
	{ "wm8960", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8960_i2c_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id wm8960_of_match[] = {
       { .compatibwe = "wwf,wm8960", },
       { }
};
MODUWE_DEVICE_TABWE(of, wm8960_of_match);
#endif

#if defined(CONFIG_ACPI)
static const stwuct acpi_device_id wm8960_acpi_match[] = {
	{ "1AEC8960", 0 }, /* Wowfson PCI ID + pawt ID */
	{ "10138960", 0 }, /* Ciwwus Wogic PCI ID + pawt ID */
	{ },
};
MODUWE_DEVICE_TABWE(acpi, wm8960_acpi_match);
#endif

static stwuct i2c_dwivew wm8960_i2c_dwivew = {
	.dwivew = {
		.name = "wm8960",
		.of_match_tabwe = of_match_ptw(wm8960_of_match),
		.acpi_match_tabwe = ACPI_PTW(wm8960_acpi_match),
	},
	.pwobe =    wm8960_i2c_pwobe,
	.wemove =   wm8960_i2c_wemove,
	.id_tabwe = wm8960_i2c_id,
};

moduwe_i2c_dwivew(wm8960_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM8960 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
