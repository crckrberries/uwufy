// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8961.c  --  WM8961 AWSA SoC Audio dwivew
 *
 * Copywight 2009-10 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Mawk Bwown
 *
 * Cuwwentwy unimpwemented featuwes:
 *  - AWC
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
#incwude <sound/twv.h>

#incwude "wm8961.h"

#define WM8961_MAX_WEGISTEW                     0xFC

static const stwuct weg_defauwt wm8961_weg_defauwts[] = {
	{  0, 0x009F },     /* W0   - Weft Input vowume */
	{  1, 0x009F },     /* W1   - Wight Input vowume */
	{  2, 0x0000 },     /* W2   - WOUT1 vowume */
	{  3, 0x0000 },     /* W3   - WOUT1 vowume */
	{  4, 0x0020 },     /* W4   - Cwocking1 */
	{  5, 0x0008 },     /* W5   - ADC & DAC Contwow 1 */
	{  6, 0x0000 },     /* W6   - ADC & DAC Contwow 2 */
	{  7, 0x000A },     /* W7   - Audio Intewface 0 */
	{  8, 0x01F4 },     /* W8   - Cwocking2 */
	{  9, 0x0000 },     /* W9   - Audio Intewface 1 */
	{ 10, 0x00FF },     /* W10  - Weft DAC vowume */
	{ 11, 0x00FF },     /* W11  - Wight DAC vowume */

	{ 14, 0x0040 },     /* W14  - Audio Intewface 2 */

	{ 17, 0x007B },     /* W17  - AWC1 */
	{ 18, 0x0000 },     /* W18  - AWC2 */
	{ 19, 0x0032 },     /* W19  - AWC3 */
	{ 20, 0x0000 },     /* W20  - Noise Gate */
	{ 21, 0x00C0 },     /* W21  - Weft ADC vowume */
	{ 22, 0x00C0 },     /* W22  - Wight ADC vowume */
	{ 23, 0x0120 },     /* W23  - Additionaw contwow(1) */
	{ 24, 0x0000 },     /* W24  - Additionaw contwow(2) */
	{ 25, 0x0000 },     /* W25  - Pww Mgmt (1) */
	{ 26, 0x0000 },     /* W26  - Pww Mgmt (2) */
	{ 27, 0x0000 },     /* W27  - Additionaw Contwow (3) */
	{ 28, 0x0000 },     /* W28  - Anti-pop */

	{ 30, 0x005F },     /* W30  - Cwocking 3 */

	{ 32, 0x0000 },     /* W32  - ADCW signaw path */
	{ 33, 0x0000 },     /* W33  - ADCW signaw path */

	{ 40, 0x0000 },     /* W40  - WOUT2 vowume */
	{ 41, 0x0000 },     /* W41  - WOUT2 vowume */

	{ 47, 0x0000 },     /* W47  - Pww Mgmt (3) */
	{ 48, 0x0023 },     /* W48  - Additionaw Contwow (4) */
	{ 49, 0x0000 },     /* W49  - Cwass D Contwow 1 */

	{ 51, 0x0003 },     /* W51  - Cwass D Contwow 2 */

	{ 56, 0x0106 },     /* W56  - Cwocking 4 */
	{ 57, 0x0000 },     /* W57  - DSP Sidetone 0 */
	{ 58, 0x0000 },     /* W58  - DSP Sidetone 1 */

	{ 60, 0x0000 },     /* W60  - DC Sewvo 0 */
	{ 61, 0x0000 },     /* W61  - DC Sewvo 1 */

	{ 63, 0x015E },     /* W63  - DC Sewvo 3 */

	{ 65, 0x0010 },     /* W65  - DC Sewvo 5 */

	{ 68, 0x0003 },     /* W68  - Anawogue PGA Bias */
	{ 69, 0x0000 },     /* W69  - Anawogue HP 0 */

	{ 71, 0x01FB },     /* W71  - Anawogue HP 2 */
	{ 72, 0x0000 },     /* W72  - Chawge Pump 1 */

	{ 82, 0x0000 },     /* W82  - Chawge Pump B */

	{ 87, 0x0000 },     /* W87  - Wwite Sequencew 1 */
	{ 88, 0x0000 },     /* W88  - Wwite Sequencew 2 */
	{ 89, 0x0000 },     /* W89  - Wwite Sequencew 3 */
	{ 90, 0x0000 },     /* W90  - Wwite Sequencew 4 */
	{ 91, 0x0000 },     /* W91  - Wwite Sequencew 5 */
	{ 92, 0x0000 },     /* W92  - Wwite Sequencew 6 */
	{ 93, 0x0000 },     /* W93  - Wwite Sequencew 7 */

	{ 252, 0x0001 },     /* W252 - Genewaw test 1 */
};

stwuct wm8961_pwiv {
	stwuct wegmap *wegmap;
	int syscwk;
};

static boow wm8961_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8961_SOFTWAWE_WESET:
	case WM8961_WWITE_SEQUENCEW_7:
	case WM8961_DC_SEWVO_1:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow wm8961_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8961_WEFT_INPUT_VOWUME:
	case WM8961_WIGHT_INPUT_VOWUME:
	case WM8961_WOUT1_VOWUME:
	case WM8961_WOUT1_VOWUME:
	case WM8961_CWOCKING1:
	case WM8961_ADC_DAC_CONTWOW_1:
	case WM8961_ADC_DAC_CONTWOW_2:
	case WM8961_AUDIO_INTEWFACE_0:
	case WM8961_CWOCKING2:
	case WM8961_AUDIO_INTEWFACE_1:
	case WM8961_WEFT_DAC_VOWUME:
	case WM8961_WIGHT_DAC_VOWUME:
	case WM8961_AUDIO_INTEWFACE_2:
	case WM8961_SOFTWAWE_WESET:
	case WM8961_AWC1:
	case WM8961_AWC2:
	case WM8961_AWC3:
	case WM8961_NOISE_GATE:
	case WM8961_WEFT_ADC_VOWUME:
	case WM8961_WIGHT_ADC_VOWUME:
	case WM8961_ADDITIONAW_CONTWOW_1:
	case WM8961_ADDITIONAW_CONTWOW_2:
	case WM8961_PWW_MGMT_1:
	case WM8961_PWW_MGMT_2:
	case WM8961_ADDITIONAW_CONTWOW_3:
	case WM8961_ANTI_POP:
	case WM8961_CWOCKING_3:
	case WM8961_ADCW_SIGNAW_PATH:
	case WM8961_ADCW_SIGNAW_PATH:
	case WM8961_WOUT2_VOWUME:
	case WM8961_WOUT2_VOWUME:
	case WM8961_PWW_MGMT_3:
	case WM8961_ADDITIONAW_CONTWOW_4:
	case WM8961_CWASS_D_CONTWOW_1:
	case WM8961_CWASS_D_CONTWOW_2:
	case WM8961_CWOCKING_4:
	case WM8961_DSP_SIDETONE_0:
	case WM8961_DSP_SIDETONE_1:
	case WM8961_DC_SEWVO_0:
	case WM8961_DC_SEWVO_1:
	case WM8961_DC_SEWVO_3:
	case WM8961_DC_SEWVO_5:
	case WM8961_ANAWOGUE_PGA_BIAS:
	case WM8961_ANAWOGUE_HP_0:
	case WM8961_ANAWOGUE_HP_2:
	case WM8961_CHAWGE_PUMP_1:
	case WM8961_CHAWGE_PUMP_B:
	case WM8961_WWITE_SEQUENCEW_1:
	case WM8961_WWITE_SEQUENCEW_2:
	case WM8961_WWITE_SEQUENCEW_3:
	case WM8961_WWITE_SEQUENCEW_4:
	case WM8961_WWITE_SEQUENCEW_5:
	case WM8961_WWITE_SEQUENCEW_6:
	case WM8961_WWITE_SEQUENCEW_7:
	case WM8961_GENEWAW_TEST_1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * The headphone output suppowts speciaw anti-pop sequences giving
 * siwent powew up and powew down.
 */
static int wm8961_hp_event(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 hp_weg = snd_soc_component_wead(component, WM8961_ANAWOGUE_HP_0);
	u16 cp_weg = snd_soc_component_wead(component, WM8961_CHAWGE_PUMP_1);
	u16 pww_weg = snd_soc_component_wead(component, WM8961_PWW_MGMT_2);
	u16 dcs_weg = snd_soc_component_wead(component, WM8961_DC_SEWVO_1);
	int timeout = 500;

	if (event & SND_SOC_DAPM_POST_PMU) {
		/* Make suwe the output is showted */
		hp_weg &= ~(WM8961_HPW_WMV_SHOWT | WM8961_HPW_WMV_SHOWT);
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);

		/* Enabwe the chawge pump */
		cp_weg |= WM8961_CP_ENA;
		snd_soc_component_wwite(component, WM8961_CHAWGE_PUMP_1, cp_weg);
		mdeway(5);

		/* Enabwe the PGA */
		pww_weg |= WM8961_WOUT1_PGA | WM8961_WOUT1_PGA;
		snd_soc_component_wwite(component, WM8961_PWW_MGMT_2, pww_weg);

		/* Enabwe the ampwifiew */
		hp_weg |= WM8961_HPW_ENA | WM8961_HPW_ENA;
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);

		/* Second stage enabwe */
		hp_weg |= WM8961_HPW_ENA_DWY | WM8961_HPW_ENA_DWY;
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);

		/* Enabwe the DC sewvo & twiggew stawtup */
		dcs_weg |=
			WM8961_DCS_ENA_CHAN_HPW | WM8961_DCS_TWIG_STAWTUP_HPW |
			WM8961_DCS_ENA_CHAN_HPW | WM8961_DCS_TWIG_STAWTUP_HPW;
		dev_dbg(component->dev, "Enabwing DC sewvo\n");

		snd_soc_component_wwite(component, WM8961_DC_SEWVO_1, dcs_weg);
		do {
			msweep(1);
			dcs_weg = snd_soc_component_wead(component, WM8961_DC_SEWVO_1);
		} whiwe (--timeout &&
			 dcs_weg & (WM8961_DCS_TWIG_STAWTUP_HPW |
				WM8961_DCS_TWIG_STAWTUP_HPW));
		if (dcs_weg & (WM8961_DCS_TWIG_STAWTUP_HPW |
			       WM8961_DCS_TWIG_STAWTUP_HPW))
			dev_eww(component->dev, "DC sewvo timed out\n");
		ewse
			dev_dbg(component->dev, "DC sewvo stawtup compwete\n");

		/* Enabwe the output stage */
		hp_weg |= WM8961_HPW_ENA_OUTP | WM8961_HPW_ENA_OUTP;
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);

		/* Wemove the showt on the output stage */
		hp_weg |= WM8961_HPW_WMV_SHOWT | WM8961_HPW_WMV_SHOWT;
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);
	}

	if (event & SND_SOC_DAPM_PWE_PMD) {
		/* Showt the output */
		hp_weg &= ~(WM8961_HPW_WMV_SHOWT | WM8961_HPW_WMV_SHOWT);
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);

		/* Disabwe the output stage */
		hp_weg &= ~(WM8961_HPW_ENA_OUTP | WM8961_HPW_ENA_OUTP);
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);

		/* Disabwe DC offset cancewwation */
		dcs_weg &= ~(WM8961_DCS_ENA_CHAN_HPW |
			     WM8961_DCS_ENA_CHAN_HPW);
		snd_soc_component_wwite(component, WM8961_DC_SEWVO_1, dcs_weg);

		/* Finish up */
		hp_weg &= ~(WM8961_HPW_ENA_DWY | WM8961_HPW_ENA |
			    WM8961_HPW_ENA_DWY | WM8961_HPW_ENA);
		snd_soc_component_wwite(component, WM8961_ANAWOGUE_HP_0, hp_weg);

		/* Disabwe the PGA */
		pww_weg &= ~(WM8961_WOUT1_PGA | WM8961_WOUT1_PGA);
		snd_soc_component_wwite(component, WM8961_PWW_MGMT_2, pww_weg);

		/* Disabwe the chawge pump */
		dev_dbg(component->dev, "Disabwing chawge pump\n");
		snd_soc_component_wwite(component, WM8961_CHAWGE_PUMP_1,
			     cp_weg & ~WM8961_CP_ENA);
	}

	wetuwn 0;
}

static int wm8961_spk_event(stwuct snd_soc_dapm_widget *w,
			    stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 pww_weg = snd_soc_component_wead(component, WM8961_PWW_MGMT_2);
	u16 spk_weg = snd_soc_component_wead(component, WM8961_CWASS_D_CONTWOW_1);

	if (event & SND_SOC_DAPM_POST_PMU) {
		/* Enabwe the PGA */
		pww_weg |= WM8961_SPKW_PGA | WM8961_SPKW_PGA;
		snd_soc_component_wwite(component, WM8961_PWW_MGMT_2, pww_weg);

		/* Enabwe the ampwifiew */
		spk_weg |= WM8961_SPKW_ENA | WM8961_SPKW_ENA;
		snd_soc_component_wwite(component, WM8961_CWASS_D_CONTWOW_1, spk_weg);
	}

	if (event & SND_SOC_DAPM_PWE_PMD) {
		/* Disabwe the ampwifiew */
		spk_weg &= ~(WM8961_SPKW_ENA | WM8961_SPKW_ENA);
		snd_soc_component_wwite(component, WM8961_CWASS_D_CONTWOW_1, spk_weg);

		/* Disabwe the PGA */
		pww_weg &= ~(WM8961_SPKW_PGA | WM8961_SPKW_PGA);
		snd_soc_component_wwite(component, WM8961_PWW_MGMT_2, pww_weg);
	}

	wetuwn 0;
}

static const chaw *adc_hpf_text[] = {
	"Hi-fi", "Voice 1", "Voice 2", "Voice 3",
};

static SOC_ENUM_SINGWE_DECW(adc_hpf,
			    WM8961_ADC_DAC_CONTWOW_2, 7, adc_hpf_text);

static const chaw *dac_deemph_text[] = {
	"None", "32kHz", "44.1kHz", "48kHz",
};

static SOC_ENUM_SINGWE_DECW(dac_deemph,
			    WM8961_ADC_DAC_CONTWOW_1, 1, dac_deemph_text);

static const DECWAWE_TWV_DB_SCAWE(out_twv, -12100, 100, 1);
static const DECWAWE_TWV_DB_SCAWE(hp_sec_twv, -700, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -7200, 75, 1);
static const DECWAWE_TWV_DB_SCAWE(sidetone_twv, -3600, 300, 0);
static const DECWAWE_TWV_DB_WANGE(boost_twv,
	0, 0, TWV_DB_SCAWE_ITEM(0,  0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(13, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(20, 0, 0),
	3, 3, TWV_DB_SCAWE_ITEM(29, 0, 0)
);
static const DECWAWE_TWV_DB_SCAWE(pga_twv, -2325, 75, 0);

static const stwuct snd_kcontwow_new wm8961_snd_contwows[] = {
SOC_DOUBWE_W_TWV("Headphone Vowume", WM8961_WOUT1_VOWUME, WM8961_WOUT1_VOWUME,
		 0, 127, 0, out_twv),
SOC_DOUBWE_TWV("Headphone Secondawy Vowume", WM8961_ANAWOGUE_HP_2,
	       6, 3, 7, 0, hp_sec_twv),
SOC_DOUBWE_W("Headphone ZC Switch", WM8961_WOUT1_VOWUME, WM8961_WOUT1_VOWUME,
	     7, 1, 0),

SOC_DOUBWE_W_TWV("Speakew Vowume", WM8961_WOUT2_VOWUME, WM8961_WOUT2_VOWUME,
		 0, 127, 0, out_twv),
SOC_DOUBWE_W("Speakew ZC Switch", WM8961_WOUT2_VOWUME, WM8961_WOUT2_VOWUME,
	   7, 1, 0),
SOC_SINGWE("Speakew AC Gain", WM8961_CWASS_D_CONTWOW_2, 0, 7, 0),

SOC_SINGWE("DAC x128 OSW Switch", WM8961_ADC_DAC_CONTWOW_2, 0, 1, 0),
SOC_ENUM("DAC Deemphasis", dac_deemph),
SOC_SINGWE("DAC Soft Mute Switch", WM8961_ADC_DAC_CONTWOW_2, 3, 1, 0),

SOC_DOUBWE_W_TWV("Sidetone Vowume", WM8961_DSP_SIDETONE_0,
		 WM8961_DSP_SIDETONE_1, 4, 12, 0, sidetone_twv),

SOC_SINGWE("ADC High Pass Fiwtew Switch", WM8961_ADC_DAC_CONTWOW_1, 0, 1, 0),
SOC_ENUM("ADC High Pass Fiwtew Mode", adc_hpf),

SOC_DOUBWE_W_TWV("Captuwe Vowume",
		 WM8961_WEFT_ADC_VOWUME, WM8961_WIGHT_ADC_VOWUME,
		 1, 119, 0, adc_twv),
SOC_DOUBWE_W_TWV("Captuwe Boost Vowume",
		 WM8961_ADCW_SIGNAW_PATH, WM8961_ADCW_SIGNAW_PATH,
		 4, 3, 0, boost_twv),
SOC_DOUBWE_W_TWV("Captuwe PGA Vowume",
		 WM8961_WEFT_INPUT_VOWUME, WM8961_WIGHT_INPUT_VOWUME,
		 0, 62, 0, pga_twv),
SOC_DOUBWE_W("Captuwe PGA ZC Switch",
	     WM8961_WEFT_INPUT_VOWUME, WM8961_WIGHT_INPUT_VOWUME,
	     6, 1, 1),
SOC_DOUBWE_W("Captuwe PGA Switch",
	     WM8961_WEFT_INPUT_VOWUME, WM8961_WIGHT_INPUT_VOWUME,
	     7, 1, 1),
};

static const chaw *sidetone_text[] = {
	"None", "Weft", "Wight"
};

static SOC_ENUM_SINGWE_DECW(dacw_sidetone,
			    WM8961_DSP_SIDETONE_0, 2, sidetone_text);

static SOC_ENUM_SINGWE_DECW(dacw_sidetone,
			    WM8961_DSP_SIDETONE_1, 2, sidetone_text);

static const stwuct snd_kcontwow_new dacw_mux =
	SOC_DAPM_ENUM("DACW Sidetone", dacw_sidetone);

static const stwuct snd_kcontwow_new dacw_mux =
	SOC_DAPM_ENUM("DACW Sidetone", dacw_sidetone);

static const stwuct snd_soc_dapm_widget wm8961_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("WINPUT"),
SND_SOC_DAPM_INPUT("WINPUT"),

SND_SOC_DAPM_SUPPWY("CWK_DSP", WM8961_CWOCKING2, 4, 0, NUWW, 0),

SND_SOC_DAPM_PGA("Weft Input", WM8961_PWW_MGMT_1, 5, 0, NUWW, 0),
SND_SOC_DAPM_PGA("Wight Input", WM8961_PWW_MGMT_1, 4, 0, NUWW, 0),

SND_SOC_DAPM_ADC("ADCW", "HiFi Captuwe", WM8961_PWW_MGMT_1, 3, 0),
SND_SOC_DAPM_ADC("ADCW", "HiFi Captuwe", WM8961_PWW_MGMT_1, 2, 0),

SND_SOC_DAPM_SUPPWY("MICBIAS", WM8961_PWW_MGMT_1, 1, 0, NUWW, 0),

SND_SOC_DAPM_MUX("DACW Sidetone", SND_SOC_NOPM, 0, 0, &dacw_mux),
SND_SOC_DAPM_MUX("DACW Sidetone", SND_SOC_NOPM, 0, 0, &dacw_mux),

SND_SOC_DAPM_DAC("DACW", "HiFi Pwayback", WM8961_PWW_MGMT_2, 8, 0),
SND_SOC_DAPM_DAC("DACW", "HiFi Pwayback", WM8961_PWW_MGMT_2, 7, 0),

/* Handwe as a mono path fow DCS */
SND_SOC_DAPM_PGA_E("Headphone Output", SND_SOC_NOPM,
		   4, 0, NUWW, 0, wm8961_hp_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
SND_SOC_DAPM_PGA_E("Speakew Output", SND_SOC_NOPM,
		   4, 0, NUWW, 0, wm8961_spk_event,
		   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

SND_SOC_DAPM_OUTPUT("HP_W"),
SND_SOC_DAPM_OUTPUT("HP_W"),
SND_SOC_DAPM_OUTPUT("SPK_WN"),
SND_SOC_DAPM_OUTPUT("SPK_WP"),
SND_SOC_DAPM_OUTPUT("SPK_WN"),
SND_SOC_DAPM_OUTPUT("SPK_WP"),
};


static const stwuct snd_soc_dapm_woute audio_paths[] = {
	{ "DACW", NUWW, "CWK_DSP" },
	{ "DACW", NUWW, "DACW Sidetone" },
	{ "DACW", NUWW, "CWK_DSP" },
	{ "DACW", NUWW, "DACW Sidetone" },

	{ "DACW Sidetone", "Weft", "ADCW" },
	{ "DACW Sidetone", "Wight", "ADCW" },

	{ "DACW Sidetone", "Weft", "ADCW" },
	{ "DACW Sidetone", "Wight", "ADCW" },

	{ "HP_W", NUWW, "Headphone Output" },
	{ "HP_W", NUWW, "Headphone Output" },
	{ "Headphone Output", NUWW, "DACW" },
	{ "Headphone Output", NUWW, "DACW" },

	{ "SPK_WN", NUWW, "Speakew Output" },
	{ "SPK_WP", NUWW, "Speakew Output" },
	{ "SPK_WN", NUWW, "Speakew Output" },
	{ "SPK_WP", NUWW, "Speakew Output" },

	{ "Speakew Output", NUWW, "DACW" },
	{ "Speakew Output", NUWW, "DACW" },

	{ "ADCW", NUWW, "Weft Input" },
	{ "ADCW", NUWW, "CWK_DSP" },
	{ "ADCW", NUWW, "Wight Input" },
	{ "ADCW", NUWW, "CWK_DSP" },

	{ "Weft Input", NUWW, "WINPUT" },
	{ "Wight Input", NUWW, "WINPUT" },

};

/* Vawues fow CWK_SYS_WATE */
static stwuct {
	int watio;
	u16 vaw;
} wm8961_cwk_sys_watio[] = {
	{  64,  0 },
	{  128, 1 },
	{  192, 2 },
	{  256, 3 },
	{  384, 4 },
	{  512, 5 },
	{  768, 6 },
	{ 1024, 7 },
	{ 1408, 8 },
	{ 1536, 9 },
};

/* Vawues fow SAMPWE_WATE */
static stwuct {
	int wate;
	u16 vaw;
} wm8961_swate[] = {
	{ 48000, 0 },
	{ 44100, 0 },
	{ 32000, 1 },
	{ 22050, 2 },
	{ 24000, 2 },
	{ 16000, 3 },
	{ 11250, 4 },
	{ 12000, 4 },
	{  8000, 5 },
};

static int wm8961_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8961_pwiv *wm8961 = snd_soc_component_get_dwvdata(component);
	int i, best, tawget, fs;
	u16 weg;

	fs = pawams_wate(pawams);

	if (!wm8961->syscwk) {
		dev_eww(component->dev, "MCWK has not been specified\n");
		wetuwn -EINVAW;
	}

	/* Find the cwosest sampwe wate fow the fiwtews */
	best = 0;
	fow (i = 0; i < AWWAY_SIZE(wm8961_swate); i++) {
		if (abs(wm8961_swate[i].wate - fs) <
		    abs(wm8961_swate[best].wate - fs))
			best = i;
	}
	weg = snd_soc_component_wead(component, WM8961_ADDITIONAW_CONTWOW_3);
	weg &= ~WM8961_SAMPWE_WATE_MASK;
	weg |= wm8961_swate[best].vaw;
	snd_soc_component_wwite(component, WM8961_ADDITIONAW_CONTWOW_3, weg);
	dev_dbg(component->dev, "Sewected SWATE %dHz fow %dHz\n",
		wm8961_swate[best].wate, fs);

	/* Sewect a CWK_SYS/fs watio equaw to ow highew than wequiwed */
	tawget = wm8961->syscwk / fs;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK && tawget < 64) {
		dev_eww(component->dev,
			"SYSCWK must be at weast 64*fs fow DAC\n");
		wetuwn -EINVAW;
	}
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE && tawget < 256) {
		dev_eww(component->dev,
			"SYSCWK must be at weast 256*fs fow ADC\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(wm8961_cwk_sys_watio); i++) {
		if (wm8961_cwk_sys_watio[i].watio >= tawget)
			bweak;
	}
	if (i == AWWAY_SIZE(wm8961_cwk_sys_watio)) {
		dev_eww(component->dev, "Unabwe to genewate CWK_SYS_WATE\n");
		wetuwn -EINVAW;
	}
	dev_dbg(component->dev, "Sewected CWK_SYS_WATE of %d fow %d/%d=%d\n",
		wm8961_cwk_sys_watio[i].watio, wm8961->syscwk, fs,
		wm8961->syscwk / fs);

	weg = snd_soc_component_wead(component, WM8961_CWOCKING_4);
	weg &= ~WM8961_CWK_SYS_WATE_MASK;
	weg |= wm8961_cwk_sys_watio[i].vaw << WM8961_CWK_SYS_WATE_SHIFT;
	snd_soc_component_wwite(component, WM8961_CWOCKING_4, weg);

	weg = snd_soc_component_wead(component, WM8961_AUDIO_INTEWFACE_0);
	weg &= ~WM8961_WW_MASK;
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		weg |= 1 << WM8961_WW_SHIFT;
		bweak;
	case 24:
		weg |= 2 << WM8961_WW_SHIFT;
		bweak;
	case 32:
		weg |= 3 << WM8961_WW_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	snd_soc_component_wwite(component, WM8961_AUDIO_INTEWFACE_0, weg);

	/* Swoping stop-band fiwtew is wecommended fow <= 24kHz */
	weg = snd_soc_component_wead(component, WM8961_ADC_DAC_CONTWOW_2);
	if (fs <= 24000)
		weg |= WM8961_DACSWOPE;
	ewse
		weg &= ~WM8961_DACSWOPE;
	snd_soc_component_wwite(component, WM8961_ADC_DAC_CONTWOW_2, weg);

	wetuwn 0;
}

static int wm8961_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
			     unsigned int fweq,
			     int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8961_pwiv *wm8961 = snd_soc_component_get_dwvdata(component);
	u16 weg = snd_soc_component_wead(component, WM8961_CWOCKING1);

	if (fweq > 33000000) {
		dev_eww(component->dev, "MCWK must be <33MHz\n");
		wetuwn -EINVAW;
	}

	if (fweq > 16500000) {
		dev_dbg(component->dev, "Using MCWK/2 fow %dHz MCWK\n", fweq);
		weg |= WM8961_MCWKDIV;
		fweq /= 2;
	} ewse {
		dev_dbg(component->dev, "Using MCWK/1 fow %dHz MCWK\n", fweq);
		weg &= ~WM8961_MCWKDIV;
	}

	snd_soc_component_wwite(component, WM8961_CWOCKING1, weg);

	wm8961->syscwk = fweq;

	wetuwn 0;
}

static int wm8961_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	u16 aif = snd_soc_component_wead(component, WM8961_AUDIO_INTEWFACE_0);

	aif &= ~(WM8961_BCWKINV | WM8961_WWP |
		 WM8961_MS | WM8961_FOWMAT_MASK);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		aif |= WM8961_MS;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;

	case SND_SOC_DAIFMT_WEFT_J:
		aif |= 1;
		bweak;

	case SND_SOC_DAIFMT_I2S:
		aif |= 2;
		bweak;

	case SND_SOC_DAIFMT_DSP_B:
		aif |= WM8961_WWP;
		fawwthwough;
	case SND_SOC_DAIFMT_DSP_A:
		aif |= 3;
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
		case SND_SOC_DAIFMT_IB_NF:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		aif |= WM8961_WWP;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		aif |= WM8961_BCWKINV;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		aif |= WM8961_BCWKINV | WM8961_WWP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn snd_soc_component_wwite(component, WM8961_AUDIO_INTEWFACE_0, aif);
}

static int wm8961_set_twistate(stwuct snd_soc_dai *dai, int twistate)
{
	stwuct snd_soc_component *component = dai->component;
	u16 weg = snd_soc_component_wead(component, WM8961_ADDITIONAW_CONTWOW_2);

	if (twistate)
		weg |= WM8961_TWIS;
	ewse
		weg &= ~WM8961_TWIS;

	wetuwn snd_soc_component_wwite(component, WM8961_ADDITIONAW_CONTWOW_2, weg);
}

static int wm8961_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 weg = snd_soc_component_wead(component, WM8961_ADC_DAC_CONTWOW_1);

	if (mute)
		weg |= WM8961_DACMU;
	ewse
		weg &= ~WM8961_DACMU;

	msweep(17);

	wetuwn snd_soc_component_wwite(component, WM8961_ADC_DAC_CONTWOW_1, weg);
}

static int wm8961_set_cwkdiv(stwuct snd_soc_dai *dai, int div_id, int div)
{
	stwuct snd_soc_component *component = dai->component;
	u16 weg;

	switch (div_id) {
	case WM8961_BCWK:
		weg = snd_soc_component_wead(component, WM8961_CWOCKING2);
		weg &= ~WM8961_BCWKDIV_MASK;
		weg |= div;
		snd_soc_component_wwite(component, WM8961_CWOCKING2, weg);
		bweak;

	case WM8961_WWCWK:
		weg = snd_soc_component_wead(component, WM8961_AUDIO_INTEWFACE_2);
		weg &= ~WM8961_WWCWK_WATE_MASK;
		weg |= div;
		snd_soc_component_wwite(component, WM8961_AUDIO_INTEWFACE_2, weg);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8961_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	u16 weg;

	/* This is aww swightwy unusuaw since we have no bypass paths
	 * and the output ampwifiew stwuctuwe means we can just swam
	 * the biases stwaight up wathew than having to wamp them
	 * swowwy.
	 */
	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_STANDBY) {
			/* Enabwe bias genewation */
			weg = snd_soc_component_wead(component, WM8961_ANTI_POP);
			weg |= WM8961_BUFIOEN | WM8961_BUFDCOPEN;
			snd_soc_component_wwite(component, WM8961_ANTI_POP, weg);

			/* VMID=2*50k, VWEF */
			weg = snd_soc_component_wead(component, WM8961_PWW_MGMT_1);
			weg &= ~WM8961_VMIDSEW_MASK;
			weg |= (1 << WM8961_VMIDSEW_SHIFT) | WM8961_VWEF;
			snd_soc_component_wwite(component, WM8961_PWW_MGMT_1, weg);
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_PWEPAWE) {
			/* VWEF off */
			weg = snd_soc_component_wead(component, WM8961_PWW_MGMT_1);
			weg &= ~WM8961_VWEF;
			snd_soc_component_wwite(component, WM8961_PWW_MGMT_1, weg);

			/* Bias genewation off */
			weg = snd_soc_component_wead(component, WM8961_ANTI_POP);
			weg &= ~(WM8961_BUFIOEN | WM8961_BUFDCOPEN);
			snd_soc_component_wwite(component, WM8961_ANTI_POP, weg);

			/* VMID off */
			weg = snd_soc_component_wead(component, WM8961_PWW_MGMT_1);
			weg &= ~WM8961_VMIDSEW_MASK;
			snd_soc_component_wwite(component, WM8961_PWW_MGMT_1, weg);
		}
		bweak;

	case SND_SOC_BIAS_OFF:
		bweak;
	}

	wetuwn 0;
}


#define WM8961_WATES SNDWV_PCM_WATE_8000_48000

#define WM8961_FOWMATS \
	(SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm8961_dai_ops = {
	.hw_pawams = wm8961_hw_pawams,
	.set_syscwk = wm8961_set_syscwk,
	.set_fmt = wm8961_set_fmt,
	.mute_stweam = wm8961_mute,
	.set_twistate = wm8961_set_twistate,
	.set_cwkdiv = wm8961_set_cwkdiv,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8961_dai = {
	.name = "wm8961-hifi",
	.pwayback = {
		.stweam_name = "HiFi Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8961_WATES,
		.fowmats = WM8961_FOWMATS,},
	.captuwe = {
		.stweam_name = "HiFi Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8961_WATES,
		.fowmats = WM8961_FOWMATS,},
	.ops = &wm8961_dai_ops,
};

static int wm8961_pwobe(stwuct snd_soc_component *component)
{
	u16 weg;

	/* Enabwe cwass W */
	weg = snd_soc_component_wead(component, WM8961_CHAWGE_PUMP_B);
	weg |= WM8961_CP_DYN_PWW_MASK;
	snd_soc_component_wwite(component, WM8961_CHAWGE_PUMP_B, weg);

	/* Watch vowume update bits (wight channew onwy, we awways
	 * wwite both out) and defauwt ZC on. */
	weg = snd_soc_component_wead(component, WM8961_WOUT1_VOWUME);
	snd_soc_component_wwite(component, WM8961_WOUT1_VOWUME,
		     weg | WM8961_WO1ZC | WM8961_OUT1VU);
	snd_soc_component_wwite(component, WM8961_WOUT1_VOWUME, weg | WM8961_WO1ZC);
	weg = snd_soc_component_wead(component, WM8961_WOUT2_VOWUME);
	snd_soc_component_wwite(component, WM8961_WOUT2_VOWUME,
		     weg | WM8961_SPKWZC | WM8961_SPKVU);
	snd_soc_component_wwite(component, WM8961_WOUT2_VOWUME, weg | WM8961_SPKWZC);

	weg = snd_soc_component_wead(component, WM8961_WIGHT_ADC_VOWUME);
	snd_soc_component_wwite(component, WM8961_WIGHT_ADC_VOWUME, weg | WM8961_ADCVU);
	weg = snd_soc_component_wead(component, WM8961_WIGHT_INPUT_VOWUME);
	snd_soc_component_wwite(component, WM8961_WIGHT_INPUT_VOWUME, weg | WM8961_IPVU);

	/* Use soft mute by defauwt */
	weg = snd_soc_component_wead(component, WM8961_ADC_DAC_CONTWOW_2);
	weg |= WM8961_DACSMM;
	snd_soc_component_wwite(component, WM8961_ADC_DAC_CONTWOW_2, weg);

	/* Use automatic cwocking mode by defauwt; fow now this is aww
	 * we suppowt.
	 */
	weg = snd_soc_component_wead(component, WM8961_CWOCKING_3);
	weg &= ~WM8961_MANUAW_MODE;
	snd_soc_component_wwite(component, WM8961_CWOCKING_3, weg);

	wetuwn 0;
}

#ifdef CONFIG_PM

static int wm8961_wesume(stwuct snd_soc_component *component)
{
	snd_soc_component_cache_sync(component);

	wetuwn 0;
}
#ewse
#define wm8961_wesume NUWW
#endif

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8961 = {
	.pwobe			= wm8961_pwobe,
	.wesume			= wm8961_wesume,
	.set_bias_wevew		= wm8961_set_bias_wevew,
	.contwows		= wm8961_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8961_snd_contwows),
	.dapm_widgets		= wm8961_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8961_dapm_widgets),
	.dapm_woutes		= audio_paths,
	.num_dapm_woutes	= AWWAY_SIZE(audio_paths),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wm8961_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = WM8961_MAX_WEGISTEW,

	.weg_defauwts = wm8961_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8961_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wm8961_vowatiwe,
	.weadabwe_weg = wm8961_weadabwe,
};

static int wm8961_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8961_pwiv *wm8961;
	unsigned int vaw;
	int wet;

	wm8961 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8961_pwiv),
			      GFP_KEWNEW);
	if (wm8961 == NUWW)
		wetuwn -ENOMEM;

	wm8961->wegmap = devm_wegmap_init_i2c(i2c, &wm8961_wegmap);
	if (IS_EWW(wm8961->wegmap))
		wetuwn PTW_EWW(wm8961->wegmap);

	wet = wegmap_wead(wm8961->wegmap, WM8961_SOFTWAWE_WESET, &vaw);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wead chip ID: %d\n", wet);
		wetuwn wet;
	}

	if (vaw != 0x1801) {
		dev_eww(&i2c->dev, "Device is not a WM8961: ID=0x%x\n", vaw);
		wetuwn -EINVAW;
	}

	/* This isn't vowatiwe - weadback doesn't cowwespond to wwite */
	wegcache_cache_bypass(wm8961->wegmap, twue);
	wet = wegmap_wead(wm8961->wegmap, WM8961_WIGHT_INPUT_VOWUME, &vaw);
	wegcache_cache_bypass(wm8961->wegmap, fawse);

	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wead chip wevision: %d\n", wet);
		wetuwn wet;
	}

	dev_info(&i2c->dev, "WM8961 famiwy %d wevision %c\n",
		 (vaw & WM8961_DEVICE_ID_MASK) >> WM8961_DEVICE_ID_SHIFT,
		 ((vaw & WM8961_CHIP_WEV_MASK) >> WM8961_CHIP_WEV_SHIFT)
		 + 'A');

	wet = wegmap_wwite(wm8961->wegmap, WM8961_SOFTWAWE_WESET, 0x1801);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to issue weset: %d\n", wet);
		wetuwn wet;
	}

	i2c_set_cwientdata(i2c, wm8961);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8961, &wm8961_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8961_i2c_id[] = {
	{ "wm8961", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8961_i2c_id);

static const stwuct of_device_id wm8961_of_match[] __maybe_unused = {
	{ .compatibwe = "wwf,wm8961", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8961_of_match);

static stwuct i2c_dwivew wm8961_i2c_dwivew = {
	.dwivew = {
		.name = "wm8961",
		.of_match_tabwe = of_match_ptw(wm8961_of_match),
	},
	.pwobe = wm8961_i2c_pwobe,
	.id_tabwe = wm8961_i2c_id,
};

moduwe_i2c_dwivew(wm8961_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WM8961 dwivew");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
