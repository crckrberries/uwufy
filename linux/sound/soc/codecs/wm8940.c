// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8940.c  --  WM8940 AWSA Soc Audio dwivew
 *
 * Authow: Jonathan Camewon <jic23@cam.ac.uk>
 *
 * Based on wm8510.c
 *    Copywight  2006 Wowfson Micwoewectwonics PWC.
 *    Authow:  Wiam Giwdwood <wwg@swimwogic.co.uk>
 *
 * Not cuwwentwy handwed:
 * Notch fiwtew contwow
 * AUXMode (invewting vs mixew)
 * No means to obtain cuwwent gain if awc enabwed.
 * No use made of gpio
 * Fast VMID dischawge fow powew down
 * Soft Stawt
 * DWW and AWW Swaps not enabwed
 * Digitaw Sidetone not suppowted
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
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

#incwude "wm8940.h"

stwuct wm8940_pwiv {
	unsigned int mcwk;
	unsigned int fs;

	stwuct wegmap *wegmap;
};

static boow wm8940_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8940_SOFTWESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wm8940_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8940_SOFTWESET:
	case WM8940_POWEW1:
	case WM8940_POWEW2:
	case WM8940_POWEW3:
	case WM8940_IFACE:
	case WM8940_COMPANDINGCTW:
	case WM8940_CWOCK:
	case WM8940_ADDCNTWW:
	case WM8940_GPIO:
	case WM8940_CTWINT:
	case WM8940_DAC:
	case WM8940_DACVOW:
	case WM8940_ADC:
	case WM8940_ADCVOW:
	case WM8940_NOTCH1:
	case WM8940_NOTCH2:
	case WM8940_NOTCH3:
	case WM8940_NOTCH4:
	case WM8940_NOTCH5:
	case WM8940_NOTCH6:
	case WM8940_NOTCH7:
	case WM8940_NOTCH8:
	case WM8940_DACWIM1:
	case WM8940_DACWIM2:
	case WM8940_AWC1:
	case WM8940_AWC2:
	case WM8940_AWC3:
	case WM8940_NOISEGATE:
	case WM8940_PWWN:
	case WM8940_PWWK1:
	case WM8940_PWWK2:
	case WM8940_PWWK3:
	case WM8940_AWC4:
	case WM8940_INPUTCTW:
	case WM8940_PGAGAIN:
	case WM8940_ADCBOOST:
	case WM8940_OUTPUTCTW:
	case WM8940_SPKMIX:
	case WM8940_SPKVOW:
	case WM8940_MONOMIX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct weg_defauwt wm8940_weg_defauwts[] = {
	{  0x1, 0x0000 }, /* Powew 1 */
	{  0x2, 0x0000 }, /* Powew 2 */
	{  0x3, 0x0000 }, /* Powew 3 */
	{  0x4, 0x0010 }, /* Intewface Contwow */
	{  0x5, 0x0000 }, /* Companding Contwow */
	{  0x6, 0x0140 }, /* Cwock Contwow */
	{  0x7, 0x0000 }, /* Additionaw Contwows */
	{  0x8, 0x0000 }, /* GPIO Contwow */
	{  0x9, 0x0002 }, /* Auto Incwement Contwow */
	{  0xa, 0x0000 }, /* DAC Contwow */
	{  0xb, 0x00FF }, /* DAC Vowume */

	{  0xe, 0x0100 }, /* ADC Contwow */
	{  0xf, 0x00FF }, /* ADC Vowume */
	{ 0x10, 0x0000 }, /* Notch Fiwtew 1 Contwow 1 */
	{ 0x11, 0x0000 }, /* Notch Fiwtew 1 Contwow 2 */
	{ 0x12, 0x0000 }, /* Notch Fiwtew 2 Contwow 1 */
	{ 0x13, 0x0000 }, /* Notch Fiwtew 2 Contwow 2 */
	{ 0x14, 0x0000 }, /* Notch Fiwtew 3 Contwow 1 */
	{ 0x15, 0x0000 }, /* Notch Fiwtew 3 Contwow 2 */
	{ 0x16, 0x0000 }, /* Notch Fiwtew 4 Contwow 1 */
	{ 0x17, 0x0000 }, /* Notch Fiwtew 4 Contwow 2 */
	{ 0x18, 0x0032 }, /* DAC Wimit Contwow 1 */
	{ 0x19, 0x0000 }, /* DAC Wimit Contwow 2 */

	{ 0x20, 0x0038 }, /* AWC Contwow 1 */
	{ 0x21, 0x000B }, /* AWC Contwow 2 */
	{ 0x22, 0x0032 }, /* AWC Contwow 3 */
	{ 0x23, 0x0000 }, /* Noise Gate */
	{ 0x24, 0x0041 }, /* PWWN */
	{ 0x25, 0x000C }, /* PWWK1 */
	{ 0x26, 0x0093 }, /* PWWK2 */
	{ 0x27, 0x00E9 }, /* PWWK3 */

	{ 0x2a, 0x0030 }, /* AWC Contwow 4 */

	{ 0x2c, 0x0002 }, /* Input Contwow */
	{ 0x2d, 0x0050 }, /* PGA Gain */

	{ 0x2f, 0x0002 }, /* ADC Boost Contwow */

	{ 0x31, 0x0002 }, /* Output Contwow */
	{ 0x32, 0x0000 }, /* Speakew Mixew Contwow */

	{ 0x36, 0x0079 }, /* Speakew Vowume */

	{ 0x38, 0x0000 }, /* Mono Mixew Contwow */
};

static const chaw *wm8940_companding[] = { "Off", "NC", "u-waw", "A-waw" };
static SOC_ENUM_SINGWE_DECW(wm8940_adc_companding_enum,
			    WM8940_COMPANDINGCTW, 1, wm8940_companding);
static SOC_ENUM_SINGWE_DECW(wm8940_dac_companding_enum,
			    WM8940_COMPANDINGCTW, 3, wm8940_companding);

static const chaw *wm8940_awc_mode_text[] = {"AWC", "Wimitew"};
static SOC_ENUM_SINGWE_DECW(wm8940_awc_mode_enum,
			    WM8940_AWC3, 8, wm8940_awc_mode_text);

static const chaw *wm8940_mic_bias_wevew_text[] = {"0.9", "0.65"};
static SOC_ENUM_SINGWE_DECW(wm8940_mic_bias_wevew_enum,
			    WM8940_INPUTCTW, 8, wm8940_mic_bias_wevew_text);

static const chaw *wm8940_fiwtew_mode_text[] = {"Audio", "Appwication"};
static SOC_ENUM_SINGWE_DECW(wm8940_fiwtew_mode_enum,
			    WM8940_ADC, 7, wm8940_fiwtew_mode_text);

static DECWAWE_TWV_DB_SCAWE(wm8940_spk_vow_twv, -5700, 100, 1);
static DECWAWE_TWV_DB_SCAWE(wm8940_att_twv, -1000, 1000, 0);
static DECWAWE_TWV_DB_SCAWE(wm8940_pga_vow_twv, -1200, 75, 0);
static DECWAWE_TWV_DB_SCAWE(wm8940_awc_min_twv, -1200, 600, 0);
static DECWAWE_TWV_DB_SCAWE(wm8940_awc_max_twv, 675, 600, 0);
static DECWAWE_TWV_DB_SCAWE(wm8940_awc_taw_twv, -2250, 50, 0);
static DECWAWE_TWV_DB_SCAWE(wm8940_wim_boost_twv, 0, 100, 0);
static DECWAWE_TWV_DB_SCAWE(wm8940_wim_thwesh_twv, -600, 100, 0);
static DECWAWE_TWV_DB_SCAWE(wm8940_adc_twv, -12750, 50, 1);
static DECWAWE_TWV_DB_SCAWE(wm8940_captuwe_boost_vow_twv, 0, 2000, 0);

static const stwuct snd_kcontwow_new wm8940_snd_contwows[] = {
	SOC_SINGWE("Digitaw Woopback Switch", WM8940_COMPANDINGCTW,
		   6, 1, 0),
	SOC_ENUM("DAC Companding", wm8940_dac_companding_enum),
	SOC_ENUM("ADC Companding", wm8940_adc_companding_enum),

	SOC_ENUM("AWC Mode", wm8940_awc_mode_enum),
	SOC_SINGWE("AWC Switch", WM8940_AWC1, 8, 1, 0),
	SOC_SINGWE_TWV("AWC Captuwe Max Gain", WM8940_AWC1,
		       3, 7, 1, wm8940_awc_max_twv),
	SOC_SINGWE_TWV("AWC Captuwe Min Gain", WM8940_AWC1,
		       0, 7, 0, wm8940_awc_min_twv),
	SOC_SINGWE_TWV("AWC Captuwe Tawget", WM8940_AWC2,
		       0, 14, 0, wm8940_awc_taw_twv),
	SOC_SINGWE("AWC Captuwe Howd", WM8940_AWC2, 4, 10, 0),
	SOC_SINGWE("AWC Captuwe Decay", WM8940_AWC3, 4, 10, 0),
	SOC_SINGWE("AWC Captuwe Attach", WM8940_AWC3, 0, 10, 0),
	SOC_SINGWE("AWC ZC Switch", WM8940_AWC4, 1, 1, 0),
	SOC_SINGWE("AWC Captuwe Noise Gate Switch", WM8940_NOISEGATE,
		   3, 1, 0),
	SOC_SINGWE("AWC Captuwe Noise Gate Thweshowd", WM8940_NOISEGATE,
		   0, 7, 0),

	SOC_SINGWE("DAC Pwayback Wimitew Switch", WM8940_DACWIM1, 8, 1, 0),
	SOC_SINGWE("DAC Pwayback Wimitew Attack", WM8940_DACWIM1, 0, 9, 0),
	SOC_SINGWE("DAC Pwayback Wimitew Decay", WM8940_DACWIM1, 4, 11, 0),
	SOC_SINGWE_TWV("DAC Pwayback Wimitew Thweshowd", WM8940_DACWIM2,
		       4, 9, 1, wm8940_wim_thwesh_twv),
	SOC_SINGWE_TWV("DAC Pwayback Wimitew Boost", WM8940_DACWIM2,
		       0, 12, 0, wm8940_wim_boost_twv),

	SOC_SINGWE("Captuwe PGA ZC Switch", WM8940_PGAGAIN, 7, 1, 0),
	SOC_SINGWE_TWV("Captuwe PGA Vowume", WM8940_PGAGAIN,
		       0, 63, 0, wm8940_pga_vow_twv),
	SOC_SINGWE_TWV("Digitaw Pwayback Vowume", WM8940_DACVOW,
		       0, 255, 0, wm8940_adc_twv),
	SOC_SINGWE_TWV("Digitaw Captuwe Vowume", WM8940_ADCVOW,
		       0, 255, 0, wm8940_adc_twv),
	SOC_ENUM("Mic Bias Wevew", wm8940_mic_bias_wevew_enum),
	SOC_SINGWE_TWV("Captuwe Boost Vowue", WM8940_ADCBOOST,
		       8, 1, 0, wm8940_captuwe_boost_vow_twv),
	SOC_SINGWE_TWV("Speakew Pwayback Vowume", WM8940_SPKVOW,
		       0, 63, 0, wm8940_spk_vow_twv),
	SOC_SINGWE("Speakew Pwayback Switch", WM8940_SPKVOW,  6, 1, 1),

	SOC_SINGWE_TWV("Speakew Mixew Wine Bypass Vowume", WM8940_SPKVOW,
		       8, 1, 1, wm8940_att_twv),
	SOC_SINGWE("Speakew Pwayback ZC Switch", WM8940_SPKVOW, 7, 1, 0),

	SOC_SINGWE("Mono Out Switch", WM8940_MONOMIX, 6, 1, 1),
	SOC_SINGWE_TWV("Mono Mixew Wine Bypass Vowume", WM8940_MONOMIX,
		       7, 1, 1, wm8940_att_twv),

	SOC_SINGWE("High Pass Fiwtew Switch", WM8940_ADC, 8, 1, 0),
	SOC_ENUM("High Pass Fiwtew Mode", wm8940_fiwtew_mode_enum),
	SOC_SINGWE("High Pass Fiwtew Cut Off", WM8940_ADC, 4, 7, 0),
	SOC_SINGWE("ADC Invewsion Switch", WM8940_ADC, 0, 1, 0),
	SOC_SINGWE("DAC Invewsion Switch", WM8940_DAC, 0, 1, 0),
	SOC_SINGWE("DAC Auto Mute Switch", WM8940_DAC, 2, 1, 0),
	SOC_SINGWE("ZC Timeout Cwock Switch", WM8940_ADDCNTWW, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wm8940_speakew_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wine Bypass Switch", WM8940_SPKMIX, 1, 1, 0),
	SOC_DAPM_SINGWE("Aux Pwayback Switch", WM8940_SPKMIX, 5, 1, 0),
	SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8940_SPKMIX, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wm8940_mono_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wine Bypass Switch", WM8940_MONOMIX, 1, 1, 0),
	SOC_DAPM_SINGWE("Aux Pwayback Switch", WM8940_MONOMIX, 2, 1, 0),
	SOC_DAPM_SINGWE("PCM Pwayback Switch", WM8940_MONOMIX, 0, 1, 0),
};

static DECWAWE_TWV_DB_SCAWE(wm8940_boost_vow_twv, -1500, 300, 1);
static const stwuct snd_kcontwow_new wm8940_input_boost_contwows[] = {
	SOC_DAPM_SINGWE("Mic PGA Switch", WM8940_PGAGAIN, 6, 1, 1),
	SOC_DAPM_SINGWE_TWV("Aux Vowume", WM8940_ADCBOOST,
			    0, 7, 0, wm8940_boost_vow_twv),
	SOC_DAPM_SINGWE_TWV("Mic Vowume", WM8940_ADCBOOST,
			    4, 7, 0, wm8940_boost_vow_twv),
};

static const stwuct snd_kcontwow_new wm8940_micpga_contwows[] = {
	SOC_DAPM_SINGWE("AUX Switch", WM8940_INPUTCTW, 2, 1, 0),
	SOC_DAPM_SINGWE("MICP Switch", WM8940_INPUTCTW, 0, 1, 0),
	SOC_DAPM_SINGWE("MICN Switch", WM8940_INPUTCTW, 1, 1, 0),
};

static const stwuct snd_soc_dapm_widget wm8940_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Speakew Mixew", WM8940_POWEW3, 2, 0,
			   &wm8940_speakew_mixew_contwows[0],
			   AWWAY_SIZE(wm8940_speakew_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Mono Mixew", WM8940_POWEW3, 3, 0,
			   &wm8940_mono_mixew_contwows[0],
			   AWWAY_SIZE(wm8940_mono_mixew_contwows)),
	SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", WM8940_POWEW3, 0, 0),

	SND_SOC_DAPM_PGA("SpkN Out", WM8940_POWEW3, 5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("SpkP Out", WM8940_POWEW3, 6, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mono Out", WM8940_POWEW3, 7, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("MONOOUT"),
	SND_SOC_DAPM_OUTPUT("SPKOUTP"),
	SND_SOC_DAPM_OUTPUT("SPKOUTN"),

	SND_SOC_DAPM_PGA("Aux Input", WM8940_POWEW1, 6, 0, NUWW, 0),
	SND_SOC_DAPM_ADC("ADC", "HiFi Captuwe", WM8940_POWEW2, 0, 0),
	SND_SOC_DAPM_MIXEW("Mic PGA", WM8940_POWEW2, 2, 0,
			   &wm8940_micpga_contwows[0],
			   AWWAY_SIZE(wm8940_micpga_contwows)),
	SND_SOC_DAPM_MIXEW("Boost Mixew", WM8940_POWEW2, 4, 0,
			   &wm8940_input_boost_contwows[0],
			   AWWAY_SIZE(wm8940_input_boost_contwows)),
	SND_SOC_DAPM_MICBIAS("Mic Bias", WM8940_POWEW1, 4, 0),

	SND_SOC_DAPM_INPUT("MICN"),
	SND_SOC_DAPM_INPUT("MICP"),
	SND_SOC_DAPM_INPUT("AUX"),
};

static const stwuct snd_soc_dapm_woute wm8940_dapm_woutes[] = {
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

	/*  Micwophone PGA */
	{"Mic PGA", "MICN Switch", "MICN"},
	{"Mic PGA", "MICP Switch", "MICP"},
	{"Mic PGA", "AUX Switch", "AUX"},

	/* Boost Mixew */
	{"Boost Mixew", "Mic PGA Switch", "Mic PGA"},
	{"Boost Mixew", "Mic Vowume",  "MICP"},
	{"Boost Mixew", "Aux Vowume", "Aux Input"},

	{"ADC", NUWW, "Boost Mixew"},
};

#define wm8940_weset(c) snd_soc_component_wwite(c, WM8940_SOFTWESET, 0);

static int wm8940_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			      unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = snd_soc_component_wead(component, WM8940_IFACE) & 0xFE67;
	u16 cwk = snd_soc_component_wead(component, WM8940_CWOCK) & 0x1fe;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		cwk |= 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	snd_soc_component_wwite(component, WM8940_CWOCK, cwk);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= (2 << 3);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= (1 << 3);
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= (3 << 3);
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= (3 << 3) | (1 << 7);
		bweak;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= (1 << 7);
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= (1 << 8);
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= (1 << 8) | (1 << 7);
		bweak;
	}

	snd_soc_component_wwite(component, WM8940_IFACE, iface);

	wetuwn 0;
}

static int wm8940_update_cwocks(stwuct snd_soc_dai *dai);
static int wm8940_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8940_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8940_IFACE) & 0xFD9F;
	u16 addcntww = snd_soc_component_wead(component, WM8940_ADDCNTWW) & 0xFFF1;
	u16 companding =  snd_soc_component_wead(component,
						WM8940_COMPANDINGCTW) & 0xFFDF;
	int wet;

	pwiv->fs = pawams_wate(pawams);
	wet = wm8940_update_cwocks(dai);
	if (wet)
		wetuwn wet;

	/* WoutW contwow */
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE
	    && pawams_channews(pawams) == 2)
		iface |= (1 << 9);

	switch (pawams_wate(pawams)) {
	case 8000:
		addcntww |= (0x5 << 1);
		bweak;
	case 11025:
		addcntww |= (0x4 << 1);
		bweak;
	case 16000:
		addcntww |= (0x3 << 1);
		bweak;
	case 22050:
		addcntww |= (0x2 << 1);
		bweak;
	case 32000:
		addcntww |= (0x1 << 1);
		bweak;
	case 44100:
	case 48000:
		bweak;
	}
	wet = snd_soc_component_wwite(component, WM8940_ADDCNTWW, addcntww);
	if (wet)
		goto ewwow_wet;

	switch (pawams_width(pawams)) {
	case 8:
		companding = companding | (1 << 5);
		bweak;
	case 16:
		bweak;
	case 20:
		iface |= (1 << 5);
		bweak;
	case 24:
		iface |= (2 << 5);
		bweak;
	case 32:
		iface |= (3 << 5);
		bweak;
	}
	wet = snd_soc_component_wwite(component, WM8940_COMPANDINGCTW, companding);
	if (wet)
		goto ewwow_wet;
	wet = snd_soc_component_wwite(component, WM8940_IFACE, iface);

ewwow_wet:
	wetuwn wet;
}

static int wm8940_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8940_DAC) & 0xffbf;

	if (mute)
		mute_weg |= 0x40;

	wetuwn snd_soc_component_wwite(component, WM8940_DAC, mute_weg);
}

static int wm8940_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8940_pwiv *wm8940 = snd_soc_component_get_dwvdata(component);
	u16 vaw;
	u16 pww_weg = snd_soc_component_wead(component, WM8940_POWEW1) & 0x1F0;
	int wet = 0;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* ensuwe bufioen and biasen */
		pww_weg |= (1 << 2) | (1 << 3);
		/* Enabwe thewmaw shutdown */
		vaw = snd_soc_component_wead(component, WM8940_OUTPUTCTW);
		wet = snd_soc_component_wwite(component, WM8940_OUTPUTCTW, vaw | 0x2);
		if (wet)
			bweak;
		/* set vmid to 75k */
		wet = snd_soc_component_wwite(component, WM8940_POWEW1, pww_weg | 0x1);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		/* ensuwe bufioen and biasen */
		pww_weg |= (1 << 2) | (1 << 3);
		wet = snd_soc_component_wwite(component, WM8940_POWEW1, pww_weg | 0x1);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = wegcache_sync(wm8940->wegmap);
			if (wet < 0) {
				dev_eww(component->dev, "Faiwed to sync cache: %d\n", wet);
				wetuwn wet;
			}
		}

		/* ensuwe bufioen and biasen */
		pww_weg |= (1 << 2) | (1 << 3);
		/* set vmid to 300k fow standby */
		wet = snd_soc_component_wwite(component, WM8940_POWEW1, pww_weg | 0x2);
		bweak;
	case SND_SOC_BIAS_OFF:
		wet = snd_soc_component_wwite(component, WM8940_POWEW1, pww_weg);
		bweak;
	}

	wetuwn wet;
}

stwuct pww_ {
	unsigned int pwe_scawe:2;
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
	/* The weft shift ist to avoid accuwacy woss when wight shifting */
	Ndiv = tawget / souwce;

	if (Ndiv > 12) {
		souwce <<= 1;
		/* Muwtipwy by 2 */
		pww_div.pwe_scawe = 0;
		Ndiv = tawget / souwce;
	} ewse if (Ndiv < 3) {
		souwce >>= 2;
		/* Divide by 4 */
		pww_div.pwe_scawe = 3;
		Ndiv = tawget / souwce;
	} ewse if (Ndiv < 6) {
		souwce >>= 1;
		/* divide by 2 */
		pww_div.pwe_scawe = 2;
		Ndiv = tawget / souwce;
	} ewse
		pww_div.pwe_scawe = 1;

	if ((Ndiv < 6) || (Ndiv > 12))
		pwintk(KEWN_WAWNING
			"WM8940 N vawue %d outwith wecommended wange!d\n",
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

/* Untested at the moment */
static int wm8940_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
		int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 weg;

	/* Tuwn off PWW */
	weg = snd_soc_component_wead(component, WM8940_POWEW1);
	snd_soc_component_wwite(component, WM8940_POWEW1, weg & 0x1df);

	if (fweq_in == 0 || fweq_out == 0) {
		/* Cwock CODEC diwectwy fwom MCWK */
		weg = snd_soc_component_wead(component, WM8940_CWOCK);
		snd_soc_component_wwite(component, WM8940_CWOCK, weg & 0x0ff);
		/* Pww powew down */
		snd_soc_component_wwite(component, WM8940_PWWN, (1 << 7));
		wetuwn 0;
	}

	/* Pww is fowwowed by a fwequency divide by 4 */
	pww_factows(fweq_out*4, fweq_in);
	if (pww_div.k)
		snd_soc_component_wwite(component, WM8940_PWWN,
			     (pww_div.pwe_scawe << 4) | pww_div.n | (1 << 6));
	ewse /* No factionaw component */
		snd_soc_component_wwite(component, WM8940_PWWN,
			     (pww_div.pwe_scawe << 4) | pww_div.n);
	snd_soc_component_wwite(component, WM8940_PWWK1, pww_div.k >> 18);
	snd_soc_component_wwite(component, WM8940_PWWK2, (pww_div.k >> 9) & 0x1ff);
	snd_soc_component_wwite(component, WM8940_PWWK3, pww_div.k & 0x1ff);
	/* Enabwe the PWW */
	weg = snd_soc_component_wead(component, WM8940_POWEW1);
	snd_soc_component_wwite(component, WM8940_POWEW1, weg | 0x020);

	/* Wun CODEC fwom PWW instead of MCWK */
	weg = snd_soc_component_wead(component, WM8940_CWOCK);
	snd_soc_component_wwite(component, WM8940_CWOCK, weg | 0x100);

	wetuwn 0;
}

static int wm8940_set_dai_cwkdiv(stwuct snd_soc_dai *codec_dai,
				 int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 weg;
	int wet = 0;

	switch (div_id) {
	case WM8940_BCWKDIV:
		weg = snd_soc_component_wead(component, WM8940_CWOCK) & 0xFFE3;
		wet = snd_soc_component_wwite(component, WM8940_CWOCK, weg | (div << 2));
		bweak;
	case WM8940_MCWKDIV:
		weg = snd_soc_component_wead(component, WM8940_CWOCK) & 0xFF1F;
		wet = snd_soc_component_wwite(component, WM8940_CWOCK, weg | (div << 5));
		bweak;
	case WM8940_OPCWKDIV:
		weg = snd_soc_component_wead(component, WM8940_GPIO) & 0xFFCF;
		wet = snd_soc_component_wwite(component, WM8940_GPIO, weg | (div << 4));
		bweak;
	}
	wetuwn wet;
}

static unsigned int wm8940_get_mcwkdiv(unsigned int f_in, unsigned int f_out,
				       int *mcwkdiv)
{
	unsigned int watio = 2 * f_in / f_out;

	if (watio <= 2) {
		*mcwkdiv = WM8940_MCWKDIV_1;
		watio = 2;
	} ewse if (watio == 3) {
		*mcwkdiv = WM8940_MCWKDIV_1_5;
	} ewse if (watio == 4) {
		*mcwkdiv = WM8940_MCWKDIV_2;
	} ewse if (watio <= 6) {
		*mcwkdiv = WM8940_MCWKDIV_3;
		watio = 6;
	} ewse if (watio <= 8) {
		*mcwkdiv = WM8940_MCWKDIV_4;
		watio = 8;
	} ewse if (watio <= 12) {
		*mcwkdiv = WM8940_MCWKDIV_6;
		watio = 12;
	} ewse if (watio <= 16) {
		*mcwkdiv = WM8940_MCWKDIV_8;
		watio = 16;
	} ewse {
		*mcwkdiv = WM8940_MCWKDIV_12;
		watio = 24;
	}

	wetuwn f_out * watio / 2;
}

static int wm8940_update_cwocks(stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct wm8940_pwiv *pwiv = snd_soc_component_get_dwvdata(codec);
	unsigned int fs256;
	unsigned int fpww = 0;
	unsigned int f;
	int mcwkdiv;

	if (!pwiv->mcwk || !pwiv->fs)
		wetuwn 0;

	fs256 = 256 * pwiv->fs;

	f = wm8940_get_mcwkdiv(pwiv->mcwk, fs256, &mcwkdiv);
	if (f != pwiv->mcwk) {
		/* The PWW pewfowms best awound 90MHz */
		fpww = wm8940_get_mcwkdiv(22500000, fs256, &mcwkdiv);
	}

	wm8940_set_dai_pww(dai, 0, 0, pwiv->mcwk, fpww);
	wm8940_set_dai_cwkdiv(dai, WM8940_MCWKDIV, mcwkdiv);

	wetuwn 0;
}

static int wm8940_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				 unsigned int fweq, int diw)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct wm8940_pwiv *pwiv = snd_soc_component_get_dwvdata(codec);

	if (diw != SND_SOC_CWOCK_IN)
		wetuwn -EINVAW;

	pwiv->mcwk = fweq;

	wetuwn wm8940_update_cwocks(dai);
}

#define WM8940_WATES SNDWV_PCM_WATE_8000_48000

#define WM8940_FOWMATS (SNDWV_PCM_FMTBIT_S8 |				\
			SNDWV_PCM_FMTBIT_S16_WE |			\
			SNDWV_PCM_FMTBIT_S20_3WE |			\
			SNDWV_PCM_FMTBIT_S24_WE |			\
			SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8940_dai_ops = {
	.hw_pawams = wm8940_i2s_hw_pawams,
	.set_syscwk = wm8940_set_dai_syscwk,
	.mute_stweam = wm8940_mute,
	.set_fmt = wm8940_set_dai_fmt,
	.set_cwkdiv = wm8940_set_dai_cwkdiv,
	.set_pww = wm8940_set_dai_pww,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8940_dai = {
	.name = "wm8940-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8940_WATES,
		.fowmats = WM8940_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8940_WATES,
		.fowmats = WM8940_FOWMATS,
	},
	.ops = &wm8940_dai_ops,
	.symmetwic_wate = 1,
};

static int wm8940_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8940_setup_data *pdata = component->dev->pwatfowm_data;
	int wet;
	u16 weg;

	/*
	 * Check chip ID fow wm8940 - vawue of 0x00 offset
	 * SOFTWAWE_WESET on wwite
	 * CHIP_ID on wead
	 */
	weg = snd_soc_component_wead(component, WM8940_SOFTWESET);
	if (weg != WM8940_CHIP_ID) {
		dev_eww(component->dev, "Wwong wm8940 chip ID: 0x%x\n", weg);
		wetuwn -ENODEV;
	}

	wet = wm8940_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset\n");
		wetuwn wet;
	}

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);

	wet = snd_soc_component_wwite(component, WM8940_POWEW1, 0x180);
	if (wet < 0)
		wetuwn wet;

	if (pdata) {
		weg = snd_soc_component_wead(component, WM8940_OUTPUTCTW);
		wet = snd_soc_component_wwite(component, WM8940_OUTPUTCTW, weg | pdata->vwoi);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8940 = {
	.pwobe			= wm8940_pwobe,
	.set_bias_wevew		= wm8940_set_bias_wevew,
	.contwows		= wm8940_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8940_snd_contwows),
	.dapm_widgets		= wm8940_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8940_dapm_widgets),
	.dapm_woutes		= wm8940_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8940_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wm8940_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,

	.max_wegistew = WM8940_MONOMIX,
	.weg_defauwts = wm8940_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8940_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.weadabwe_weg = wm8940_weadabwe_wegistew,
	.vowatiwe_weg = wm8940_vowatiwe_wegistew,
};

static int wm8940_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8940_pwiv *wm8940;
	int wet;

	wm8940 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8940_pwiv),
			      GFP_KEWNEW);
	if (wm8940 == NUWW)
		wetuwn -ENOMEM;

	wm8940->wegmap = devm_wegmap_init_i2c(i2c, &wm8940_wegmap);
	if (IS_EWW(wm8940->wegmap))
		wetuwn PTW_EWW(wm8940->wegmap);

	i2c_set_cwientdata(i2c, wm8940);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8940, &wm8940_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8940_i2c_id[] = {
	{ "wm8940", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8940_i2c_id);

static const stwuct of_device_id wm8940_of_match[] = {
	{ .compatibwe = "wwf,wm8940", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8940_of_match);

static stwuct i2c_dwivew wm8940_i2c_dwivew = {
	.dwivew = {
		.name = "wm8940",
		.of_match_tabwe = wm8940_of_match,
	},
	.pwobe = wm8940_i2c_pwobe,
	.id_tabwe = wm8940_i2c_id,
};

moduwe_i2c_dwivew(wm8940_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM8940 dwivew");
MODUWE_AUTHOW("Jonathan Camewon");
MODUWE_WICENSE("GPW");
