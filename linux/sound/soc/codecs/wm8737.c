// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8737.c  --  WM8737 AWSA SoC Audio dwivew
 *
 * Copywight 2010 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wm8737.h"

#define WM8737_NUM_SUPPWIES 4
static const chaw *wm8737_suppwy_names[WM8737_NUM_SUPPWIES] = {
	"DCVDD",
	"DBVDD",
	"AVDD",
	"MVDD",
};

/* codec pwivate data */
stwuct wm8737_pwiv {
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[WM8737_NUM_SUPPWIES];
	unsigned int mcwk;
};

static const stwuct weg_defauwt wm8737_weg_defauwts[] = {
	{  0, 0x00C3 },     /* W0  - Weft PGA vowume */
	{  1, 0x00C3 },     /* W1  - Wight PGA vowume */
	{  2, 0x0007 },     /* W2  - AUDIO path W */
	{  3, 0x0007 },     /* W3  - AUDIO path W */
	{  4, 0x0000 },     /* W4  - 3D Enhance */
	{  5, 0x0000 },     /* W5  - ADC Contwow */
	{  6, 0x0000 },     /* W6  - Powew Management */
	{  7, 0x000A },     /* W7  - Audio Fowmat */
	{  8, 0x0000 },     /* W8  - Cwocking */
	{  9, 0x000F },     /* W9  - MIC Pweamp Contwow */
	{ 10, 0x0003 },     /* W10 - Misc Bias Contwow */
	{ 11, 0x0000 },     /* W11 - Noise Gate */
	{ 12, 0x007C },     /* W12 - AWC1 */
	{ 13, 0x0000 },     /* W13 - AWC2 */
	{ 14, 0x0032 },     /* W14 - AWC3 */
};

static boow wm8737_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8737_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wm8737_weset(stwuct snd_soc_component *component)
{
	wetuwn snd_soc_component_wwite(component, WM8737_WESET, 0);
}

static const DECWAWE_TWV_DB_WANGE(micboost_twv,
	0, 0, TWV_DB_SCAWE_ITEM(1300, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(1800, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(2800, 0, 0),
	3, 3, TWV_DB_SCAWE_ITEM(3300, 0, 0)
);
static const DECWAWE_TWV_DB_SCAWE(pga_twv, -9750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -600, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(ng_twv, -7800, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_max_twv, -1200, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_tawget_twv, -1800, 100, 0);

static const chaw *micbias_enum_text[] = {
	"25%",
	"50%",
	"75%",
	"100%",
};

static SOC_ENUM_SINGWE_DECW(micbias_enum,
			    WM8737_MIC_PWEAMP_CONTWOW, 0, micbias_enum_text);

static const chaw *wow_cutoff_text[] = {
	"Wow", "High"
};

static SOC_ENUM_SINGWE_DECW(wow_3d,
			    WM8737_3D_ENHANCE, 6, wow_cutoff_text);

static const chaw *high_cutoff_text[] = {
	"High", "Wow"
};

static SOC_ENUM_SINGWE_DECW(high_3d,
			    WM8737_3D_ENHANCE, 5, high_cutoff_text);

static const chaw *awc_fn_text[] = {
	"Disabwed", "Wight", "Weft", "Steweo"
};

static SOC_ENUM_SINGWE_DECW(awc_fn,
			    WM8737_AWC1, 7, awc_fn_text);

static const chaw *awc_howd_text[] = {
	"0", "2.67ms", "5.33ms", "10.66ms", "21.32ms", "42.64ms", "85.28ms",
	"170.56ms", "341.12ms", "682.24ms", "1.364s", "2.728s", "5.458s",
	"10.916s", "21.832s", "43.691s"
};

static SOC_ENUM_SINGWE_DECW(awc_howd,
			    WM8737_AWC2, 0, awc_howd_text);

static const chaw *awc_atk_text[] = {
	"8.4ms", "16.8ms", "33.6ms", "67.2ms", "134.4ms", "268.8ms", "537.6ms",
	"1.075s", "2.15s", "4.3s", "8.6s"
};

static SOC_ENUM_SINGWE_DECW(awc_atk,
			    WM8737_AWC3, 0, awc_atk_text);

static const chaw *awc_dcy_text[] = {
	"33.6ms", "67.2ms", "134.4ms", "268.8ms", "537.6ms", "1.075s", "2.15s",
	"4.3s", "8.6s", "17.2s", "34.41s"
};

static SOC_ENUM_SINGWE_DECW(awc_dcy,
			    WM8737_AWC3, 4, awc_dcy_text);

static const stwuct snd_kcontwow_new wm8737_snd_contwows[] = {
SOC_DOUBWE_W_TWV("Mic Boost Vowume", WM8737_AUDIO_PATH_W, WM8737_AUDIO_PATH_W,
		 6, 3, 0, micboost_twv),
SOC_DOUBWE_W("Mic Boost Switch", WM8737_AUDIO_PATH_W, WM8737_AUDIO_PATH_W,
	     4, 1, 0),
SOC_DOUBWE("Mic ZC Switch", WM8737_AUDIO_PATH_W, WM8737_AUDIO_PATH_W,
	   3, 1, 0),

SOC_DOUBWE_W_TWV("Captuwe Vowume", WM8737_WEFT_PGA_VOWUME,
		 WM8737_WIGHT_PGA_VOWUME, 0, 255, 0, pga_twv),
SOC_DOUBWE("Captuwe ZC Switch", WM8737_AUDIO_PATH_W, WM8737_AUDIO_PATH_W,
	   2, 1, 0),

SOC_DOUBWE("INPUT1 DC Bias Switch", WM8737_MISC_BIAS_CONTWOW, 0, 1, 1, 0),

SOC_ENUM("Mic PGA Bias", micbias_enum),
SOC_SINGWE("ADC Wow Powew Switch", WM8737_ADC_CONTWOW, 2, 1, 0),
SOC_SINGWE("High Pass Fiwtew Switch", WM8737_ADC_CONTWOW, 0, 1, 1),
SOC_DOUBWE("Powawity Invewt Switch", WM8737_ADC_CONTWOW, 5, 6, 1, 0),

SOC_SINGWE("3D Switch", WM8737_3D_ENHANCE, 0, 1, 0),
SOC_SINGWE("3D Depth", WM8737_3D_ENHANCE, 1, 15, 0),
SOC_ENUM("3D Wow Cut-off", wow_3d),
SOC_ENUM("3D High Cut-off", high_3d),
SOC_SINGWE_TWV("3D ADC Vowume", WM8737_3D_ENHANCE, 7, 1, 1, adc_twv),

SOC_SINGWE("Noise Gate Switch", WM8737_NOISE_GATE, 0, 1, 0),
SOC_SINGWE_TWV("Noise Gate Thweshowd Vowume", WM8737_NOISE_GATE, 2, 7, 0,
	       ng_twv),

SOC_ENUM("AWC", awc_fn),
SOC_SINGWE_TWV("AWC Max Gain Vowume", WM8737_AWC1, 4, 7, 0, awc_max_twv),
SOC_SINGWE_TWV("AWC Tawget Vowume", WM8737_AWC1, 0, 15, 0, awc_tawget_twv),
SOC_ENUM("AWC Howd Time", awc_howd),
SOC_SINGWE("AWC ZC Switch", WM8737_AWC2, 4, 1, 0),
SOC_ENUM("AWC Attack Time", awc_atk),
SOC_ENUM("AWC Decay Time", awc_dcy),
};

static const chaw *winsew_text[] = {
	"WINPUT1", "WINPUT2", "WINPUT3", "WINPUT1 DC",
};

static SOC_ENUM_SINGWE_DECW(winsew_enum,
			    WM8737_AUDIO_PATH_W, 7, winsew_text);

static const stwuct snd_kcontwow_new winsew_mux =
	SOC_DAPM_ENUM("WINSEW", winsew_enum);


static const chaw *winsew_text[] = {
	"WINPUT1", "WINPUT2", "WINPUT3", "WINPUT1 DC",
};

static SOC_ENUM_SINGWE_DECW(winsew_enum,
			    WM8737_AUDIO_PATH_W, 7, winsew_text);

static const stwuct snd_kcontwow_new winsew_mux =
	SOC_DAPM_ENUM("WINSEW", winsew_enum);

static const chaw *bypass_text[] = {
	"Diwect", "Pweamp"
};

static SOC_ENUM_SINGWE_DECW(wbypass_enum,
			    WM8737_MIC_PWEAMP_CONTWOW, 2, bypass_text);

static const stwuct snd_kcontwow_new wbypass_mux =
	SOC_DAPM_ENUM("Weft Bypass", wbypass_enum);


static SOC_ENUM_SINGWE_DECW(wbypass_enum,
			    WM8737_MIC_PWEAMP_CONTWOW, 3, bypass_text);

static const stwuct snd_kcontwow_new wbypass_mux =
	SOC_DAPM_ENUM("Weft Bypass", wbypass_enum);

static const stwuct snd_soc_dapm_widget wm8737_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("WINPUT1"),
SND_SOC_DAPM_INPUT("WINPUT2"),
SND_SOC_DAPM_INPUT("WINPUT3"),
SND_SOC_DAPM_INPUT("WINPUT1"),
SND_SOC_DAPM_INPUT("WINPUT2"),
SND_SOC_DAPM_INPUT("WINPUT3"),
SND_SOC_DAPM_INPUT("WACIN"),
SND_SOC_DAPM_INPUT("WACIN"),

SND_SOC_DAPM_MUX("WINSEW", SND_SOC_NOPM, 0, 0, &winsew_mux),
SND_SOC_DAPM_MUX("WINSEW", SND_SOC_NOPM, 0, 0, &winsew_mux),

SND_SOC_DAPM_MUX("Weft Pweamp Mux", SND_SOC_NOPM, 0, 0, &wbypass_mux),
SND_SOC_DAPM_MUX("Wight Pweamp Mux", SND_SOC_NOPM, 0, 0, &wbypass_mux),

SND_SOC_DAPM_PGA("PGAW", WM8737_POWEW_MANAGEMENT, 5, 0, NUWW, 0),
SND_SOC_DAPM_PGA("PGAW", WM8737_POWEW_MANAGEMENT, 4, 0, NUWW, 0),

SND_SOC_DAPM_DAC("ADCW", NUWW, WM8737_POWEW_MANAGEMENT, 3, 0),
SND_SOC_DAPM_DAC("ADCW", NUWW, WM8737_POWEW_MANAGEMENT, 2, 0),

SND_SOC_DAPM_AIF_OUT("AIF", "Captuwe", 0, WM8737_POWEW_MANAGEMENT, 6, 0),
};

static const stwuct snd_soc_dapm_woute intewcon[] = {
	{ "WINSEW", "WINPUT1", "WINPUT1" },
	{ "WINSEW", "WINPUT2", "WINPUT2" },
	{ "WINSEW", "WINPUT3", "WINPUT3" },
	{ "WINSEW", "WINPUT1 DC", "WINPUT1" },

	{ "WINSEW", "WINPUT1", "WINPUT1" },
	{ "WINSEW", "WINPUT2", "WINPUT2" },
	{ "WINSEW", "WINPUT3", "WINPUT3" },
	{ "WINSEW", "WINPUT1 DC", "WINPUT1" },

	{ "Weft Pweamp Mux", "Pweamp", "WINSEW" },
	{ "Weft Pweamp Mux", "Diwect", "WACIN" },

	{ "Wight Pweamp Mux", "Pweamp", "WINSEW" },
	{ "Wight Pweamp Mux", "Diwect", "WACIN" },

	{ "PGAW", NUWW, "Weft Pweamp Mux" },
	{ "PGAW", NUWW, "Wight Pweamp Mux" },

	{ "ADCW", NUWW, "PGAW" },
	{ "ADCW", NUWW, "PGAW" },

	{ "AIF", NUWW, "ADCW" },
	{ "AIF", NUWW, "ADCW" },
};

/* codec mcwk cwock dividew coefficients */
static const stwuct {
	u32 mcwk;
	u32 wate;
	u8 usb;
	u8 sw;
} coeff_div[] = {
	{ 12288000,  8000, 0,  0x4 },
	{ 12288000, 12000, 0,  0x8 },
	{ 12288000, 16000, 0,  0xa },
	{ 12288000, 24000, 0, 0x1c },
	{ 12288000, 32000, 0,  0xc },
	{ 12288000, 48000, 0,    0 },
	{ 12288000, 96000, 0,  0xe },

	{ 11289600,  8000, 0, 0x14 },
	{ 11289600, 11025, 0, 0x18 },
	{ 11289600, 22050, 0, 0x1a },
	{ 11289600, 44100, 0, 0x10 },
	{ 11289600, 88200, 0, 0x1e },

	{ 18432000,  8000, 0,  0x5 },
	{ 18432000, 12000, 0,  0x9 },
	{ 18432000, 16000, 0,  0xb },
	{ 18432000, 24000, 0, 0x1b },
	{ 18432000, 32000, 0,  0xd },
	{ 18432000, 48000, 0,  0x1 },
	{ 18432000, 96000, 0, 0x1f },

	{ 16934400,  8000, 0, 0x15 },
	{ 16934400, 11025, 0, 0x19 },
	{ 16934400, 22050, 0, 0x1b },
	{ 16934400, 44100, 0, 0x11 },
	{ 16934400, 88200, 0, 0x1f },

	{ 12000000,  8000, 1,  0x4 },
	{ 12000000, 11025, 1, 0x19 },
	{ 12000000, 12000, 1,  0x8 },
	{ 12000000, 16000, 1,  0xa },
	{ 12000000, 22050, 1, 0x1b },
	{ 12000000, 24000, 1, 0x1c },
	{ 12000000, 32000, 1,  0xc },
	{ 12000000, 44100, 1, 0x11 },
	{ 12000000, 48000, 1,  0x0 },
	{ 12000000, 88200, 1, 0x1f },
	{ 12000000, 96000, 1,  0xe },
};

static int wm8737_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8737_pwiv *wm8737 = snd_soc_component_get_dwvdata(component);
	int i;
	u16 cwocking = 0;
	u16 af = 0;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].wate != pawams_wate(pawams))
			continue;

		if (coeff_div[i].mcwk == wm8737->mcwk)
			bweak;

		if (coeff_div[i].mcwk == wm8737->mcwk * 2) {
			cwocking |= WM8737_CWKDIV2;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(coeff_div)) {
		dev_eww(component->dev, "%dHz MCWK can't suppowt %dHz\n",
			wm8737->mcwk, pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	cwocking |= coeff_div[i].usb | (coeff_div[i].sw << WM8737_SW_SHIFT);

	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		af |= 0x8;
		bweak;
	case 24:
		af |= 0x10;
		bweak;
	case 32:
		af |= 0x18;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WM8737_AUDIO_FOWMAT, WM8737_WW_MASK, af);
	snd_soc_component_update_bits(component, WM8737_CWOCKING,
			    WM8737_USB_MODE | WM8737_CWKDIV2 | WM8737_SW_MASK,
			    cwocking);

	wetuwn 0;
}

static int wm8737_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8737_pwiv *wm8737 = snd_soc_component_get_dwvdata(component);
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (fweq == coeff_div[i].mcwk ||
		    fweq == coeff_div[i].mcwk * 2) {
			wm8737->mcwk = fweq;
			wetuwn 0;
		}
	}

	dev_eww(component->dev, "MCWK wate %dHz not suppowted\n", fweq);

	wetuwn -EINVAW;
}


static int wm8737_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 af = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		af |= WM8737_MS;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		af |= 0x2;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		af |= 0x1;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		af |= 0x3;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		af |= 0x13;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		af |= WM8737_WWP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WM8737_AUDIO_FOWMAT,
			    WM8737_FOWMAT_MASK | WM8737_WWP | WM8737_MS, af);

	wetuwn 0;
}

static int wm8737_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8737_pwiv *wm8737 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		/* VMID at 2*75k */
		snd_soc_component_update_bits(component, WM8737_MISC_BIAS_CONTWOW,
				    WM8737_VMIDSEW_MASK, 0);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8737->suppwies),
						    wm8737->suppwies);
			if (wet != 0) {
				dev_eww(component->dev,
					"Faiwed to enabwe suppwies: %d\n",
					wet);
				wetuwn wet;
			}

			wegcache_sync(wm8737->wegmap);

			/* Fast VMID wamp at 2*2.5k */
			snd_soc_component_update_bits(component, WM8737_MISC_BIAS_CONTWOW,
					    WM8737_VMIDSEW_MASK,
					    2 << WM8737_VMIDSEW_SHIFT);

			/* Bwing VMID up */
			snd_soc_component_update_bits(component, WM8737_POWEW_MANAGEMENT,
					    WM8737_VMID_MASK |
					    WM8737_VWEF_MASK,
					    WM8737_VMID_MASK |
					    WM8737_VWEF_MASK);

			msweep(500);
		}

		/* VMID at 2*300k */
		snd_soc_component_update_bits(component, WM8737_MISC_BIAS_CONTWOW,
				    WM8737_VMIDSEW_MASK,
				    1 << WM8737_VMIDSEW_SHIFT);

		bweak;

	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8737_POWEW_MANAGEMENT,
				    WM8737_VMID_MASK | WM8737_VWEF_MASK, 0);

		weguwatow_buwk_disabwe(AWWAY_SIZE(wm8737->suppwies),
				       wm8737->suppwies);
		bweak;
	}

	wetuwn 0;
}

#define WM8737_WATES SNDWV_PCM_WATE_8000_96000

#define WM8737_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8737_dai_ops = {
	.hw_pawams	= wm8737_hw_pawams,
	.set_syscwk	= wm8737_set_dai_syscwk,
	.set_fmt	= wm8737_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew wm8737_dai = {
	.name = "wm8737",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,  /* Mono modes not yet suppowted */
		.channews_max = 2,
		.wates = WM8737_WATES,
		.fowmats = WM8737_FOWMATS,
	},
	.ops = &wm8737_dai_ops,
};

static int wm8737_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8737_pwiv *wm8737 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8737->suppwies),
				    wm8737->suppwies);
	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		goto eww_get;
	}

	wet = wm8737_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset\n");
		goto eww_enabwe;
	}

	snd_soc_component_update_bits(component, WM8737_WEFT_PGA_VOWUME, WM8737_WVU,
			    WM8737_WVU);
	snd_soc_component_update_bits(component, WM8737_WIGHT_PGA_VOWUME, WM8737_WVU,
			    WM8737_WVU);

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	/* Bias wevew configuwation wiww have done an extwa enabwe */
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8737->suppwies), wm8737->suppwies);

	wetuwn 0;

eww_enabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8737->suppwies), wm8737->suppwies);
eww_get:
	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8737 = {
	.pwobe			= wm8737_pwobe,
	.set_bias_wevew		= wm8737_set_bias_wevew,
	.contwows		= wm8737_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8737_snd_contwows),
	.dapm_widgets		= wm8737_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8737_dapm_widgets),
	.dapm_woutes		= intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(intewcon),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8737_of_match[] = {
	{ .compatibwe = "wwf,wm8737", },
	{ }
};

MODUWE_DEVICE_TABWE(of, wm8737_of_match);

static const stwuct wegmap_config wm8737_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8737_MAX_WEGISTEW,

	.weg_defauwts = wm8737_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8737_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wm8737_vowatiwe,
};

#if IS_ENABWED(CONFIG_I2C)
static int wm8737_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8737_pwiv *wm8737;
	int wet, i;

	wm8737 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8737_pwiv),
			      GFP_KEWNEW);
	if (wm8737 == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(wm8737->suppwies); i++)
		wm8737->suppwies[i].suppwy = wm8737_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev, AWWAY_SIZE(wm8737->suppwies),
				      wm8737->suppwies);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wm8737->wegmap = devm_wegmap_init_i2c(i2c, &wm8737_wegmap);
	if (IS_EWW(wm8737->wegmap))
		wetuwn PTW_EWW(wm8737->wegmap);

	i2c_set_cwientdata(i2c, wm8737);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				&soc_component_dev_wm8737, &wm8737_dai, 1);

	wetuwn wet;

}

static const stwuct i2c_device_id wm8737_i2c_id[] = {
	{ "wm8737", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8737_i2c_id);

static stwuct i2c_dwivew wm8737_i2c_dwivew = {
	.dwivew = {
		.name = "wm8737",
		.of_match_tabwe = wm8737_of_match,
	},
	.pwobe = wm8737_i2c_pwobe,
	.id_tabwe = wm8737_i2c_id,
};
#endif

#if defined(CONFIG_SPI_MASTEW)
static int wm8737_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8737_pwiv *wm8737;
	int wet, i;

	wm8737 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8737_pwiv),
			      GFP_KEWNEW);
	if (wm8737 == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(wm8737->suppwies); i++)
		wm8737->suppwies[i].suppwy = wm8737_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&spi->dev, AWWAY_SIZE(wm8737->suppwies),
				      wm8737->suppwies);
	if (wet != 0) {
		dev_eww(&spi->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wm8737->wegmap = devm_wegmap_init_spi(spi, &wm8737_wegmap);
	if (IS_EWW(wm8737->wegmap))
		wetuwn PTW_EWW(wm8737->wegmap);

	spi_set_dwvdata(spi, wm8737);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
				&soc_component_dev_wm8737, &wm8737_dai, 1);

	wetuwn wet;
}

static stwuct spi_dwivew wm8737_spi_dwivew = {
	.dwivew = {
		.name	= "wm8737",
		.of_match_tabwe = wm8737_of_match,
	},
	.pwobe		= wm8737_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

static int __init wm8737_modinit(void)
{
	int wet;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8737_i2c_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8737 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8737_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8737 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn 0;
}
moduwe_init(wm8737_modinit);

static void __exit wm8737_exit(void)
{
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8737_spi_dwivew);
#endif
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8737_i2c_dwivew);
#endif
}
moduwe_exit(wm8737_exit);

MODUWE_DESCWIPTION("ASoC WM8737 dwivew");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
