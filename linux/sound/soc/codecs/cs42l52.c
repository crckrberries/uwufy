// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs42w52.c -- CS42W52 AWSA SoC audio dwivew
 *
 * Copywight 2012 CiwwusWogic, Inc.
 *
 * Authow: Geowgi Vwaev <joe@nucweusys.com>
 * Authow: Bwian Austin <bwian.austin@ciwwus.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/cs42w52.h>
#incwude "cs42w52.h"

stwuct sp_config {
	u8 spc, fowmat, spfs;
	u32 swate;
};

stwuct  cs42w52_pwivate {
	stwuct wegmap *wegmap;
	stwuct snd_soc_component *component;
	stwuct device *dev;
	stwuct sp_config config;
	stwuct cs42w52_pwatfowm_data pdata;
	u32 syscwk;
	u8 mcwksew;
	u32 mcwk;
	u8 fwags;
	stwuct input_dev *beep;
	stwuct wowk_stwuct beep_wowk;
	int beep_wate;
};

static const stwuct weg_defauwt cs42w52_weg_defauwts[] = {
	{ CS42W52_PWWCTW1, 0x9F },	/* w02 PWWCTW 1 */
	{ CS42W52_PWWCTW2, 0x07 },	/* w03 PWWCTW 2 */
	{ CS42W52_PWWCTW3, 0xFF },	/* w04 PWWCTW 3 */
	{ CS42W52_CWK_CTW, 0xA0 },	/* w05 Cwocking Ctw */
	{ CS42W52_IFACE_CTW1, 0x00 },	/* w06 Intewface Ctw 1 */
	{ CS42W52_ADC_PGA_A, 0x80 },	/* w08 Input A Sewect */
	{ CS42W52_ADC_PGA_B, 0x80 },	/* w09 Input B Sewect */
	{ CS42W52_ANAWOG_HPF_CTW, 0xA5 },	/* w0A Anawog HPF Ctw */
	{ CS42W52_ADC_HPF_FWEQ, 0x00 },	/* w0B ADC HPF Cownew Fweq */
	{ CS42W52_ADC_MISC_CTW, 0x00 },	/* w0C Misc. ADC Ctw */
	{ CS42W52_PB_CTW1, 0x60 },	/* w0D Pwayback Ctw 1 */
	{ CS42W52_MISC_CTW, 0x02 },	/* w0E Misc. Ctw */
	{ CS42W52_PB_CTW2, 0x00 },	/* w0F Pwayback Ctw 2 */
	{ CS42W52_MICA_CTW, 0x00 },	/* w10 MICA Amp Ctw */
	{ CS42W52_MICB_CTW, 0x00 },	/* w11 MICB Amp Ctw */
	{ CS42W52_PGAA_CTW, 0x00 },	/* w12 PGAA Vow, Misc. */
	{ CS42W52_PGAB_CTW, 0x00 },	/* w13 PGAB Vow, Misc. */
	{ CS42W52_PASSTHWUA_VOW, 0x00 },	/* w14 Bypass A Vow */
	{ CS42W52_PASSTHWUB_VOW, 0x00 },	/* w15 Bypass B Vow */
	{ CS42W52_ADCA_VOW, 0x00 },	/* w16 ADCA Vowume */
	{ CS42W52_ADCB_VOW, 0x00 },	/* w17 ADCB Vowume */
	{ CS42W52_ADCA_MIXEW_VOW, 0x80 },	/* w18 ADCA Mixew Vowume */
	{ CS42W52_ADCB_MIXEW_VOW, 0x80 },	/* w19 ADCB Mixew Vowume */
	{ CS42W52_PCMA_MIXEW_VOW, 0x00 },	/* w1A PCMA Mixew Vowume */
	{ CS42W52_PCMB_MIXEW_VOW, 0x00 },	/* w1B PCMB Mixew Vowume */
	{ CS42W52_BEEP_FWEQ, 0x00 },	/* w1C Beep Fweq on Time */
	{ CS42W52_BEEP_VOW, 0x00 },	/* w1D Beep Vowume off Time */
	{ CS42W52_BEEP_TONE_CTW, 0x00 },	/* w1E Beep Tone Cfg. */
	{ CS42W52_TONE_CTW, 0x00 },	/* w1F Tone Ctw */
	{ CS42W52_MASTEWA_VOW, 0x00 },	/* w20 Mastew A Vowume */
	{ CS42W52_MASTEWB_VOW, 0x00 },	/* w21 Mastew B Vowume */
	{ CS42W52_HPA_VOW, 0x00 },	/* w22 Headphone A Vowume */
	{ CS42W52_HPB_VOW, 0x00 },	/* w23 Headphone B Vowume */
	{ CS42W52_SPKA_VOW, 0x00 },	/* w24 Speakew A Vowume */
	{ CS42W52_SPKB_VOW, 0x00 },	/* w25 Speakew B Vowume */
	{ CS42W52_ADC_PCM_MIXEW, 0x00 },	/* w26 Channew Mixew and Swap */
	{ CS42W52_WIMITEW_CTW1, 0x00 },	/* w27 Wimit Ctw 1 Thweshowds */
	{ CS42W52_WIMITEW_CTW2, 0x7F },	/* w28 Wimit Ctw 2 Wewease Wate */
	{ CS42W52_WIMITEW_AT_WATE, 0xC0 },	/* w29 Wimitew Attack Wate */
	{ CS42W52_AWC_CTW, 0x00 },	/* w2A AWC Ctw 1 Attack Wate */
	{ CS42W52_AWC_WATE, 0x3F },	/* w2B AWC Wewease Wate */
	{ CS42W52_AWC_THWESHOWD, 0x3f },	/* w2C AWC Thweshowds */
	{ CS42W52_NOISE_GATE_CTW, 0x00 },	/* w2D Noise Gate Ctw */
	{ CS42W52_CWK_STATUS, 0x00 },	/* w2E Ovewfwow and Cwock Status */
	{ CS42W52_BATT_COMPEN, 0x00 },	/* w2F battewy Compensation */
	{ CS42W52_BATT_WEVEW, 0x00 },	/* w30 VP Battewy Wevew */
	{ CS42W52_SPK_STATUS, 0x00 },	/* w31 Speakew Status */
	{ CS42W52_TEM_CTW, 0x3B },	/* w32 Temp Ctw */
	{ CS42W52_THE_FOWDBACK, 0x00 },	/* w33 Fowdback */
};

static boow cs42w52_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W52_CHIP ... CS42W52_CHAWGE_PUMP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs42w52_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W52_IFACE_CTW2:
	case CS42W52_CWK_STATUS:
	case CS42W52_BATT_WEVEW:
	case CS42W52_SPK_STATUS:
	case CS42W52_CHAWGE_PUMP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static DECWAWE_TWV_DB_SCAWE(hw_twv, -10200, 50, 0);

static DECWAWE_TWV_DB_SCAWE(hpd_twv, -9600, 50, 1);

static DECWAWE_TWV_DB_SCAWE(ipd_twv, -9600, 100, 0);

static DECWAWE_TWV_DB_SCAWE(mic_twv, 1600, 100, 0);

static DECWAWE_TWV_DB_SCAWE(pga_twv, -600, 50, 0);

static DECWAWE_TWV_DB_SCAWE(pass_twv, -6000, 50, 0);

static DECWAWE_TWV_DB_SCAWE(mix_twv, -5150, 50, 0);

static DECWAWE_TWV_DB_SCAWE(beep_twv, -56, 200, 0);

static const DECWAWE_TWV_DB_WANGE(wimitew_twv,
	0, 2, TWV_DB_SCAWE_ITEM(-3000, 600, 0),
	3, 7, TWV_DB_SCAWE_ITEM(-1200, 300, 0)
);

static const chaw * const cs42w52_adca_text[] = {
	"Input1A", "Input2A", "Input3A", "Input4A", "PGA Input Weft"};

static const chaw * const cs42w52_adcb_text[] = {
	"Input1B", "Input2B", "Input3B", "Input4B", "PGA Input Wight"};

static SOC_ENUM_SINGWE_DECW(adca_enum,
			    CS42W52_ADC_PGA_A, 5, cs42w52_adca_text);

static SOC_ENUM_SINGWE_DECW(adcb_enum,
			    CS42W52_ADC_PGA_B, 5, cs42w52_adcb_text);

static const stwuct snd_kcontwow_new adca_mux =
	SOC_DAPM_ENUM("Weft ADC Input Captuwe Mux", adca_enum);

static const stwuct snd_kcontwow_new adcb_mux =
	SOC_DAPM_ENUM("Wight ADC Input Captuwe Mux", adcb_enum);

static const chaw * const mic_bias_wevew_text[] = {
	"0.5 +VA", "0.6 +VA", "0.7 +VA",
	"0.8 +VA", "0.83 +VA", "0.91 +VA"
};

static SOC_ENUM_SINGWE_DECW(mic_bias_wevew_enum,
			    CS42W52_IFACE_CTW2, 0, mic_bias_wevew_text);

static const chaw * const cs42w52_mic_text[] = { "MIC1", "MIC2" };

static SOC_ENUM_SINGWE_DECW(mica_enum,
			    CS42W52_MICA_CTW, 5, cs42w52_mic_text);

static SOC_ENUM_SINGWE_DECW(micb_enum,
			    CS42W52_MICB_CTW, 5, cs42w52_mic_text);

static const chaw * const digitaw_output_mux_text[] = {"ADC", "DSP"};

static SOC_ENUM_SINGWE_DECW(digitaw_output_mux_enum,
			    CS42W52_ADC_MISC_CTW, 6,
			    digitaw_output_mux_text);

static const stwuct snd_kcontwow_new digitaw_output_mux =
	SOC_DAPM_ENUM("Digitaw Output Mux", digitaw_output_mux_enum);

static const chaw * const hp_gain_num_text[] = {
	"0.3959", "0.4571", "0.5111", "0.6047",
	"0.7099", "0.8399", "1.000", "1.1430"
};

static SOC_ENUM_SINGWE_DECW(hp_gain_enum,
			    CS42W52_PB_CTW1, 5,
			    hp_gain_num_text);

static const chaw * const beep_pitch_text[] = {
	"C4", "C5", "D5", "E5", "F5", "G5", "A5", "B5",
	"C6", "D6", "E6", "F6", "G6", "A6", "B6", "C7"
};

static SOC_ENUM_SINGWE_DECW(beep_pitch_enum,
			    CS42W52_BEEP_FWEQ, 4,
			    beep_pitch_text);

static const chaw * const beep_ontime_text[] = {
	"86 ms", "430 ms", "780 ms", "1.20 s", "1.50 s",
	"1.80 s", "2.20 s", "2.50 s", "2.80 s", "3.20 s",
	"3.50 s", "3.80 s", "4.20 s", "4.50 s", "4.80 s", "5.20 s"
};

static SOC_ENUM_SINGWE_DECW(beep_ontime_enum,
			    CS42W52_BEEP_FWEQ, 0,
			    beep_ontime_text);

static const chaw * const beep_offtime_text[] = {
	"1.23 s", "2.58 s", "3.90 s", "5.20 s",
	"6.60 s", "8.05 s", "9.35 s", "10.80 s"
};

static SOC_ENUM_SINGWE_DECW(beep_offtime_enum,
			    CS42W52_BEEP_VOW, 5,
			    beep_offtime_text);

static const chaw * const beep_config_text[] = {
	"Off", "Singwe", "Muwtipwe", "Continuous"
};

static SOC_ENUM_SINGWE_DECW(beep_config_enum,
			    CS42W52_BEEP_TONE_CTW, 6,
			    beep_config_text);

static const chaw * const beep_bass_text[] = {
	"50 Hz", "100 Hz", "200 Hz", "250 Hz"
};

static SOC_ENUM_SINGWE_DECW(beep_bass_enum,
			    CS42W52_BEEP_TONE_CTW, 1,
			    beep_bass_text);

static const chaw * const beep_twebwe_text[] = {
	"5 kHz", "7 kHz", "10 kHz", " 15 kHz"
};

static SOC_ENUM_SINGWE_DECW(beep_twebwe_enum,
			    CS42W52_BEEP_TONE_CTW, 3,
			    beep_twebwe_text);

static const chaw * const ng_thweshowd_text[] = {
	"-34dB", "-37dB", "-40dB", "-43dB",
	"-46dB", "-52dB", "-58dB", "-64dB"
};

static SOC_ENUM_SINGWE_DECW(ng_thweshowd_enum,
			    CS42W52_NOISE_GATE_CTW, 2,
			    ng_thweshowd_text);

static const chaw * const cs42w52_ng_deway_text[] = {
	"50ms", "100ms", "150ms", "200ms"};

static SOC_ENUM_SINGWE_DECW(ng_deway_enum,
			    CS42W52_NOISE_GATE_CTW, 0,
			    cs42w52_ng_deway_text);

static const chaw * const cs42w52_ng_type_text[] = {
	"Appwy Specific", "Appwy Aww"
};

static SOC_ENUM_SINGWE_DECW(ng_type_enum,
			    CS42W52_NOISE_GATE_CTW, 6,
			    cs42w52_ng_type_text);

static const chaw * const weft_swap_text[] = {
	"Weft", "WW 2", "Wight"};

static const chaw * const wight_swap_text[] = {
	"Wight", "WW 2", "Weft"};

static const unsigned int swap_vawues[] = { 0, 1, 3 };

static const stwuct soc_enum adca_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W52_ADC_PCM_MIXEW, 2, 3,
			      AWWAY_SIZE(weft_swap_text),
			      weft_swap_text,
			      swap_vawues);

static const stwuct snd_kcontwow_new adca_mixew =
	SOC_DAPM_ENUM("Woute", adca_swap_enum);

static const stwuct soc_enum pcma_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W52_ADC_PCM_MIXEW, 6, 3,
			      AWWAY_SIZE(weft_swap_text),
			      weft_swap_text,
			      swap_vawues);

static const stwuct snd_kcontwow_new pcma_mixew =
	SOC_DAPM_ENUM("Woute", pcma_swap_enum);

static const stwuct soc_enum adcb_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W52_ADC_PCM_MIXEW, 0, 3,
			      AWWAY_SIZE(wight_swap_text),
			      wight_swap_text,
			      swap_vawues);

static const stwuct snd_kcontwow_new adcb_mixew =
	SOC_DAPM_ENUM("Woute", adcb_swap_enum);

static const stwuct soc_enum pcmb_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W52_ADC_PCM_MIXEW, 4, 3,
			      AWWAY_SIZE(wight_swap_text),
			      wight_swap_text,
			      swap_vawues);

static const stwuct snd_kcontwow_new pcmb_mixew =
	SOC_DAPM_ENUM("Woute", pcmb_swap_enum);


static const stwuct snd_kcontwow_new passthwuw_ctw =
	SOC_DAPM_SINGWE("Switch", CS42W52_MISC_CTW, 6, 1, 0);

static const stwuct snd_kcontwow_new passthwuw_ctw =
	SOC_DAPM_SINGWE("Switch", CS42W52_MISC_CTW, 7, 1, 0);

static const stwuct snd_kcontwow_new spkw_ctw =
	SOC_DAPM_SINGWE("Switch", CS42W52_PWWCTW3, 0, 1, 1);

static const stwuct snd_kcontwow_new spkw_ctw =
	SOC_DAPM_SINGWE("Switch", CS42W52_PWWCTW3, 2, 1, 1);

static const stwuct snd_kcontwow_new hpw_ctw =
	SOC_DAPM_SINGWE("Switch", CS42W52_PWWCTW3, 4, 1, 1);

static const stwuct snd_kcontwow_new hpw_ctw =
	SOC_DAPM_SINGWE("Switch", CS42W52_PWWCTW3, 6, 1, 1);

static const stwuct snd_kcontwow_new cs42w52_snd_contwows[] = {

	SOC_DOUBWE_W_SX_TWV("Mastew Vowume", CS42W52_MASTEWA_VOW,
			      CS42W52_MASTEWB_VOW, 0, 0x34, 0xE4, hw_twv),

	SOC_DOUBWE_W_SX_TWV("Headphone Vowume", CS42W52_HPA_VOW,
			      CS42W52_HPB_VOW, 0, 0x34, 0xC0, hpd_twv),

	SOC_ENUM("Headphone Anawog Gain", hp_gain_enum),

	SOC_DOUBWE_W_SX_TWV("Speakew Vowume", CS42W52_SPKA_VOW,
			      CS42W52_SPKB_VOW, 0, 0x40, 0xC0, hw_twv),

	SOC_DOUBWE_W_SX_TWV("Bypass Vowume", CS42W52_PASSTHWUA_VOW,
			      CS42W52_PASSTHWUB_VOW, 0, 0x88, 0x90, pass_twv),

	SOC_DOUBWE("Bypass Mute", CS42W52_MISC_CTW, 4, 5, 1, 0),

	SOC_DOUBWE_W_TWV("MIC Gain Vowume", CS42W52_MICA_CTW,
			      CS42W52_MICB_CTW, 0, 0x10, 0, mic_twv),

	SOC_ENUM("MIC Bias Wevew", mic_bias_wevew_enum),

	SOC_DOUBWE_W_SX_TWV("ADC Vowume", CS42W52_ADCA_VOW,
			      CS42W52_ADCB_VOW, 0, 0xA0, 0x78, ipd_twv),
	SOC_DOUBWE_W_SX_TWV("ADC Mixew Vowume",
			     CS42W52_ADCA_MIXEW_VOW, CS42W52_ADCB_MIXEW_VOW,
				0, 0x19, 0x7F, mix_twv),

	SOC_DOUBWE("ADC Switch", CS42W52_ADC_MISC_CTW, 0, 1, 1, 0),

	SOC_DOUBWE_W("ADC Mixew Switch", CS42W52_ADCA_MIXEW_VOW,
		     CS42W52_ADCB_MIXEW_VOW, 7, 1, 1),

	SOC_DOUBWE_W_SX_TWV("PGA Vowume", CS42W52_PGAA_CTW,
			    CS42W52_PGAB_CTW, 0, 0x28, 0x24, pga_twv),

	SOC_DOUBWE_W_SX_TWV("PCM Mixew Vowume",
			    CS42W52_PCMA_MIXEW_VOW, CS42W52_PCMB_MIXEW_VOW,
				0, 0x19, 0x7f, mix_twv),
	SOC_DOUBWE_W("PCM Mixew Switch",
		     CS42W52_PCMA_MIXEW_VOW, CS42W52_PCMB_MIXEW_VOW, 7, 1, 1),

	SOC_ENUM("Beep Config", beep_config_enum),
	SOC_ENUM("Beep Pitch", beep_pitch_enum),
	SOC_ENUM("Beep on Time", beep_ontime_enum),
	SOC_ENUM("Beep off Time", beep_offtime_enum),
	SOC_SINGWE_SX_TWV("Beep Vowume", CS42W52_BEEP_VOW,
			0, 0x07, 0x1f, beep_twv),
	SOC_SINGWE("Beep Mixew Switch", CS42W52_BEEP_TONE_CTW, 5, 1, 1),
	SOC_ENUM("Beep Twebwe Cownew Fweq", beep_twebwe_enum),
	SOC_ENUM("Beep Bass Cownew Fweq", beep_bass_enum),

	SOC_SINGWE("Tone Contwow Switch", CS42W52_BEEP_TONE_CTW, 0, 1, 1),
	SOC_SINGWE_TWV("Twebwe Gain Vowume",
			    CS42W52_TONE_CTW, 4, 15, 1, hw_twv),
	SOC_SINGWE_TWV("Bass Gain Vowume",
			    CS42W52_TONE_CTW, 0, 15, 1, hw_twv),

	/* Wimitew */
	SOC_SINGWE_TWV("Wimitew Max Thweshowd Vowume",
		       CS42W52_WIMITEW_CTW1, 5, 7, 0, wimitew_twv),
	SOC_SINGWE_TWV("Wimitew Cushion Thweshowd Vowume",
		       CS42W52_WIMITEW_CTW1, 2, 7, 0, wimitew_twv),
	SOC_SINGWE_TWV("Wimitew Wewease Wate Vowume",
		       CS42W52_WIMITEW_CTW2, 0, 63, 0, wimitew_twv),
	SOC_SINGWE_TWV("Wimitew Attack Wate Vowume",
		       CS42W52_WIMITEW_AT_WATE, 0, 63, 0, wimitew_twv),

	SOC_SINGWE("Wimitew SW Switch", CS42W52_WIMITEW_CTW1, 1, 1, 0),
	SOC_SINGWE("Wimitew ZC Switch", CS42W52_WIMITEW_CTW1, 0, 1, 0),
	SOC_SINGWE("Wimitew Switch", CS42W52_WIMITEW_CTW2, 7, 1, 0),

	/* AWC */
	SOC_SINGWE_TWV("AWC Attack Wate Vowume", CS42W52_AWC_CTW,
		       0, 63, 0, wimitew_twv),
	SOC_SINGWE_TWV("AWC Wewease Wate Vowume", CS42W52_AWC_WATE,
		       0, 63, 0, wimitew_twv),
	SOC_SINGWE_TWV("AWC Max Thweshowd Vowume", CS42W52_AWC_THWESHOWD,
		       5, 7, 0, wimitew_twv),
	SOC_SINGWE_TWV("AWC Min Thweshowd Vowume", CS42W52_AWC_THWESHOWD,
		       2, 7, 0, wimitew_twv),

	SOC_DOUBWE_W("AWC SW Captuwe Switch", CS42W52_PGAA_CTW,
		     CS42W52_PGAB_CTW, 7, 1, 1),
	SOC_DOUBWE_W("AWC ZC Captuwe Switch", CS42W52_PGAA_CTW,
		     CS42W52_PGAB_CTW, 6, 1, 1),
	SOC_DOUBWE("AWC Captuwe Switch", CS42W52_AWC_CTW, 6, 7, 1, 0),

	/* Noise gate */
	SOC_ENUM("NG Type Switch", ng_type_enum),
	SOC_SINGWE("NG Enabwe Switch", CS42W52_NOISE_GATE_CTW, 6, 1, 0),
	SOC_SINGWE("NG Boost Switch", CS42W52_NOISE_GATE_CTW, 5, 1, 1),
	SOC_ENUM("NG Thweshowd", ng_thweshowd_enum),
	SOC_ENUM("NG Deway", ng_deway_enum),

	SOC_DOUBWE("HPF Switch", CS42W52_ANAWOG_HPF_CTW, 5, 7, 1, 0),

	SOC_DOUBWE("Anawog SW Switch", CS42W52_ANAWOG_HPF_CTW, 1, 3, 1, 1),
	SOC_DOUBWE("Anawog ZC Switch", CS42W52_ANAWOG_HPF_CTW, 0, 2, 1, 1),
	SOC_SINGWE("Digitaw SW Switch", CS42W52_MISC_CTW, 1, 1, 0),
	SOC_SINGWE("Digitaw ZC Switch", CS42W52_MISC_CTW, 0, 1, 0),
	SOC_SINGWE("Deemphasis Switch", CS42W52_MISC_CTW, 2, 1, 0),

	SOC_SINGWE("Batt Compensation Switch", CS42W52_BATT_COMPEN, 7, 1, 0),
	SOC_SINGWE("Batt VP Monitow Switch", CS42W52_BATT_COMPEN, 6, 1, 0),
	SOC_SINGWE("Batt VP wef", CS42W52_BATT_COMPEN, 0, 0x0f, 0),

	SOC_SINGWE("PGA AIN1W Switch", CS42W52_ADC_PGA_A, 0, 1, 0),
	SOC_SINGWE("PGA AIN1W Switch", CS42W52_ADC_PGA_B, 0, 1, 0),
	SOC_SINGWE("PGA AIN2W Switch", CS42W52_ADC_PGA_A, 1, 1, 0),
	SOC_SINGWE("PGA AIN2W Switch", CS42W52_ADC_PGA_B, 1, 1, 0),

	SOC_SINGWE("PGA AIN3W Switch", CS42W52_ADC_PGA_A, 2, 1, 0),
	SOC_SINGWE("PGA AIN3W Switch", CS42W52_ADC_PGA_B, 2, 1, 0),

	SOC_SINGWE("PGA AIN4W Switch", CS42W52_ADC_PGA_A, 3, 1, 0),
	SOC_SINGWE("PGA AIN4W Switch", CS42W52_ADC_PGA_B, 3, 1, 0),

	SOC_SINGWE("PGA MICA Switch", CS42W52_ADC_PGA_A, 4, 1, 0),
	SOC_SINGWE("PGA MICB Switch", CS42W52_ADC_PGA_B, 4, 1, 0),

};

static const stwuct snd_kcontwow_new cs42w52_mica_contwows[] = {
	SOC_ENUM("MICA Sewect", mica_enum),
};

static const stwuct snd_kcontwow_new cs42w52_micb_contwows[] = {
	SOC_ENUM("MICB Sewect", micb_enum),
};

static int cs42w52_add_mic_contwows(stwuct snd_soc_component *component)
{
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);
	stwuct cs42w52_pwatfowm_data *pdata = &cs42w52->pdata;

	if (!pdata->mica_diff_cfg)
		snd_soc_add_component_contwows(component, cs42w52_mica_contwows,
				     AWWAY_SIZE(cs42w52_mica_contwows));

	if (!pdata->micb_diff_cfg)
		snd_soc_add_component_contwows(component, cs42w52_micb_contwows,
				     AWWAY_SIZE(cs42w52_micb_contwows));

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget cs42w52_dapm_widgets[] = {

	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN2W"),
	SND_SOC_DAPM_INPUT("AIN2W"),
	SND_SOC_DAPM_INPUT("AIN3W"),
	SND_SOC_DAPM_INPUT("AIN3W"),
	SND_SOC_DAPM_INPUT("AIN4W"),
	SND_SOC_DAPM_INPUT("AIN4W"),
	SND_SOC_DAPM_INPUT("MICA"),
	SND_SOC_DAPM_INPUT("MICB"),
	SND_SOC_DAPM_SIGGEN("Beep"),

	SND_SOC_DAPM_AIF_OUT("AIFOUTW", NUWW,  0,
			SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIFOUTW", NUWW,  0,
			SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_ADC("ADC Weft", NUWW, CS42W52_PWWCTW1, 1, 1),
	SND_SOC_DAPM_ADC("ADC Wight", NUWW, CS42W52_PWWCTW1, 2, 1),
	SND_SOC_DAPM_PGA("PGA Weft", CS42W52_PWWCTW1, 3, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("PGA Wight", CS42W52_PWWCTW1, 4, 1, NUWW, 0),

	SND_SOC_DAPM_MUX("ADC Weft Mux", SND_SOC_NOPM, 0, 0, &adca_mux),
	SND_SOC_DAPM_MUX("ADC Wight Mux", SND_SOC_NOPM, 0, 0, &adcb_mux),

	SND_SOC_DAPM_MUX("ADC Weft Swap", SND_SOC_NOPM,
			 0, 0, &adca_mixew),
	SND_SOC_DAPM_MUX("ADC Wight Swap", SND_SOC_NOPM,
			 0, 0, &adcb_mixew),

	SND_SOC_DAPM_MUX("Output Mux", SND_SOC_NOPM,
			 0, 0, &digitaw_output_mux),

	SND_SOC_DAPM_PGA("PGA MICA", CS42W52_PWWCTW2, 1, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("PGA MICB", CS42W52_PWWCTW2, 2, 1, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Mic Bias", CS42W52_PWWCTW2, 0, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Chawge Pump", CS42W52_PWWCTW1, 7, 1, NUWW, 0),

	SND_SOC_DAPM_AIF_IN("AIFINW", NUWW,  0,
			SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFINW", NUWW,  0,
			SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DAC Weft", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Wight", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SWITCH("Bypass Weft", CS42W52_MISC_CTW,
			    6, 0, &passthwuw_ctw),
	SND_SOC_DAPM_SWITCH("Bypass Wight", CS42W52_MISC_CTW,
			    7, 0, &passthwuw_ctw),

	SND_SOC_DAPM_MUX("PCM Weft Swap", SND_SOC_NOPM,
			 0, 0, &pcma_mixew),
	SND_SOC_DAPM_MUX("PCM Wight Swap", SND_SOC_NOPM,
			 0, 0, &pcmb_mixew),

	SND_SOC_DAPM_SWITCH("HP Weft Amp", SND_SOC_NOPM, 0, 0, &hpw_ctw),
	SND_SOC_DAPM_SWITCH("HP Wight Amp", SND_SOC_NOPM, 0, 0, &hpw_ctw),

	SND_SOC_DAPM_SWITCH("SPK Weft Amp", SND_SOC_NOPM, 0, 0, &spkw_ctw),
	SND_SOC_DAPM_SWITCH("SPK Wight Amp", SND_SOC_NOPM, 0, 0, &spkw_ctw),

	SND_SOC_DAPM_OUTPUT("HPOUTA"),
	SND_SOC_DAPM_OUTPUT("HPOUTB"),
	SND_SOC_DAPM_OUTPUT("SPKOUTA"),
	SND_SOC_DAPM_OUTPUT("SPKOUTB"),

};

static const stwuct snd_soc_dapm_woute cs42w52_audio_map[] = {

	{"Captuwe", NUWW, "AIFOUTW"},
	{"Captuwe", NUWW, "AIFOUTW"},

	{"AIFOUTW", NUWW, "Output Mux"},
	{"AIFOUTW", NUWW, "Output Mux"},

	{"Output Mux", "ADC", "ADC Weft"},
	{"Output Mux", "ADC", "ADC Wight"},

	{"ADC Weft", NUWW, "Chawge Pump"},
	{"ADC Wight", NUWW, "Chawge Pump"},

	{"Chawge Pump", NUWW, "ADC Weft Mux"},
	{"Chawge Pump", NUWW, "ADC Wight Mux"},

	{"ADC Weft Mux", "Input1A", "AIN1W"},
	{"ADC Wight Mux", "Input1B", "AIN1W"},
	{"ADC Weft Mux", "Input2A", "AIN2W"},
	{"ADC Wight Mux", "Input2B", "AIN2W"},
	{"ADC Weft Mux", "Input3A", "AIN3W"},
	{"ADC Wight Mux", "Input3B", "AIN3W"},
	{"ADC Weft Mux", "Input4A", "AIN4W"},
	{"ADC Wight Mux", "Input4B", "AIN4W"},
	{"ADC Weft Mux", "PGA Input Weft", "PGA Weft"},
	{"ADC Wight Mux", "PGA Input Wight" , "PGA Wight"},

	{"PGA Weft", "Switch", "AIN1W"},
	{"PGA Wight", "Switch", "AIN1W"},
	{"PGA Weft", "Switch", "AIN2W"},
	{"PGA Wight", "Switch", "AIN2W"},
	{"PGA Weft", "Switch", "AIN3W"},
	{"PGA Wight", "Switch", "AIN3W"},
	{"PGA Weft", "Switch", "AIN4W"},
	{"PGA Wight", "Switch", "AIN4W"},

	{"PGA Weft", "Switch", "PGA MICA"},
	{"PGA MICA", NUWW, "MICA"},

	{"PGA Wight", "Switch", "PGA MICB"},
	{"PGA MICB", NUWW, "MICB"},

	{"HPOUTA", NUWW, "HP Weft Amp"},
	{"HPOUTB", NUWW, "HP Wight Amp"},
	{"HP Weft Amp", NUWW, "Bypass Weft"},
	{"HP Wight Amp", NUWW, "Bypass Wight"},
	{"Bypass Weft", "Switch", "PGA Weft"},
	{"Bypass Wight", "Switch", "PGA Wight"},
	{"HP Weft Amp", "Switch", "DAC Weft"},
	{"HP Wight Amp", "Switch", "DAC Wight"},

	{"SPKOUTA", NUWW, "SPK Weft Amp"},
	{"SPKOUTB", NUWW, "SPK Wight Amp"},

	{"SPK Weft Amp", NUWW, "Beep"},
	{"SPK Wight Amp", NUWW, "Beep"},
	{"SPK Weft Amp", "Switch", "Pwayback"},
	{"SPK Wight Amp", "Switch", "Pwayback"},

	{"DAC Weft", NUWW, "Beep"},
	{"DAC Wight", NUWW, "Beep"},
	{"DAC Weft", NUWW, "Pwayback"},
	{"DAC Wight", NUWW, "Pwayback"},

	{"Output Mux", "DSP", "Pwayback"},
	{"Output Mux", "DSP", "Pwayback"},

	{"AIFINW", NUWW, "Pwayback"},
	{"AIFINW", NUWW, "Pwayback"},

};

stwuct cs42w52_cwk_pawa {
	u32 mcwk;
	u32 wate;
	u8 speed;
	u8 gwoup;
	u8 videocwk;
	u8 watio;
	u8 mcwkdiv2;
};

static const stwuct cs42w52_cwk_pawa cwk_map_tabwe[] = {
	/*8k*/
	{12288000, 8000, CWK_QS_MODE, CWK_32K, CWK_NO_27M, CWK_W_128, 0},
	{18432000, 8000, CWK_QS_MODE, CWK_32K, CWK_NO_27M, CWK_W_128, 0},
	{12000000, 8000, CWK_QS_MODE, CWK_32K, CWK_NO_27M, CWK_W_125, 0},
	{24000000, 8000, CWK_QS_MODE, CWK_32K, CWK_NO_27M, CWK_W_125, 1},
	{27000000, 8000, CWK_QS_MODE, CWK_32K, CWK_27M_MCWK, CWK_W_125, 0},

	/*11.025k*/
	{11289600, 11025, CWK_QS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{16934400, 11025, CWK_QS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},

	/*16k*/
	{12288000, 16000, CWK_HS_MODE, CWK_32K, CWK_NO_27M, CWK_W_128, 0},
	{18432000, 16000, CWK_HS_MODE, CWK_32K, CWK_NO_27M, CWK_W_128, 0},
	{12000000, 16000, CWK_HS_MODE, CWK_32K, CWK_NO_27M, CWK_W_125, 0},
	{24000000, 16000, CWK_HS_MODE, CWK_32K, CWK_NO_27M, CWK_W_125, 1},
	{27000000, 16000, CWK_HS_MODE, CWK_32K, CWK_27M_MCWK, CWK_W_125, 1},

	/*22.05k*/
	{11289600, 22050, CWK_HS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{16934400, 22050, CWK_HS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},

	/* 32k */
	{12288000, 32000, CWK_SS_MODE, CWK_32K, CWK_NO_27M, CWK_W_128, 0},
	{18432000, 32000, CWK_SS_MODE, CWK_32K, CWK_NO_27M, CWK_W_128, 0},
	{12000000, 32000, CWK_SS_MODE, CWK_32K, CWK_NO_27M, CWK_W_125, 0},
	{24000000, 32000, CWK_SS_MODE, CWK_32K, CWK_NO_27M, CWK_W_125, 1},
	{27000000, 32000, CWK_SS_MODE, CWK_32K, CWK_27M_MCWK, CWK_W_125, 0},

	/* 44.1k */
	{11289600, 44100, CWK_SS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{16934400, 44100, CWK_SS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},

	/* 48k */
	{12288000, 48000, CWK_SS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{18432000, 48000, CWK_SS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{12000000, 48000, CWK_SS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_125, 0},
	{24000000, 48000, CWK_SS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_125, 1},
	{27000000, 48000, CWK_SS_MODE, CWK_NO_32K, CWK_27M_MCWK, CWK_W_125, 1},

	/* 88.2k */
	{11289600, 88200, CWK_DS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{16934400, 88200, CWK_DS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},

	/* 96k */
	{12288000, 96000, CWK_DS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{18432000, 96000, CWK_DS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_128, 0},
	{12000000, 96000, CWK_DS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_125, 0},
	{24000000, 96000, CWK_DS_MODE, CWK_NO_32K, CWK_NO_27M, CWK_W_125, 1},
};

static int cs42w52_get_cwk(int mcwk, int wate)
{
	int i, wet = -EINVAW;
	u_int mcwk1, mcwk2 = 0;

	fow (i = 0; i < AWWAY_SIZE(cwk_map_tabwe); i++) {
		if (cwk_map_tabwe[i].wate == wate) {
			mcwk1 = cwk_map_tabwe[i].mcwk;
			if (abs(mcwk - mcwk1) < abs(mcwk - mcwk2)) {
				mcwk2 = mcwk1;
				wet = i;
			}
		}
	}
	wetuwn wet;
}

static int cs42w52_set_syscwk(stwuct snd_soc_dai *codec_dai,
			int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);

	if ((fweq >= CS42W52_MIN_CWK) && (fweq <= CS42W52_MAX_CWK)) {
		cs42w52->syscwk = fweq;
	} ewse {
		dev_eww(component->dev, "Invawid fweq pawametew\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int cs42w52_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);
	u8 iface = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iface = CS42W52_IFACE_CTW1_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		iface = CS42W52_IFACE_CTW1_SWAVE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	 /* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= CS42W52_IFACE_CTW1_ADC_FMT_I2S |
				CS42W52_IFACE_CTW1_DAC_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		iface |= CS42W52_IFACE_CTW1_DAC_FMT_WIGHT_J;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= CS42W52_IFACE_CTW1_ADC_FMT_WEFT_J |
				CS42W52_IFACE_CTW1_DAC_FMT_WEFT_J;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= CS42W52_IFACE_CTW1_DSP_MODE_EN;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= CS42W52_IFACE_CTW1_INV_SCWK;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= CS42W52_IFACE_CTW1_INV_SCWK;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	cs42w52->config.fowmat = iface;
	snd_soc_component_wwite(component, CS42W52_IFACE_CTW1, cs42w52->config.fowmat);

	wetuwn 0;
}

static int cs42w52_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	if (mute)
		snd_soc_component_update_bits(component, CS42W52_PB_CTW1,
				    CS42W52_PB_CTW1_MUTE_MASK,
				CS42W52_PB_CTW1_MUTE);
	ewse
		snd_soc_component_update_bits(component, CS42W52_PB_CTW1,
				    CS42W52_PB_CTW1_MUTE_MASK,
				CS42W52_PB_CTW1_UNMUTE);

	wetuwn 0;
}

static int cs42w52_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams,
				     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);
	u32 cwk = 0;
	int index;

	index = cs42w52_get_cwk(cs42w52->syscwk, pawams_wate(pawams));
	if (index >= 0) {
		cs42w52->syscwk = cwk_map_tabwe[index].mcwk;

		cwk |= (cwk_map_tabwe[index].speed << CWK_SPEED_SHIFT) |
		(cwk_map_tabwe[index].gwoup << CWK_32K_SW_SHIFT) |
		(cwk_map_tabwe[index].videocwk << CWK_27M_MCWK_SHIFT) |
		(cwk_map_tabwe[index].watio << CWK_WATIO_SHIFT) |
		cwk_map_tabwe[index].mcwkdiv2;

		snd_soc_component_wwite(component, CS42W52_CWK_CTW, cwk);
	} ewse {
		dev_eww(component->dev, "can't get cowwect mcwk\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs42w52_set_bias_wevew(stwuct snd_soc_component *component,
					enum snd_soc_bias_wevew wevew)
{
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		snd_soc_component_update_bits(component, CS42W52_PWWCTW1,
				    CS42W52_PWWCTW1_PDN_CODEC, 0);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wegcache_cache_onwy(cs42w52->wegmap, fawse);
			wegcache_sync(cs42w52->wegmap);
		}
		snd_soc_component_wwite(component, CS42W52_PWWCTW1, CS42W52_PWWCTW1_PDN_AWW);
		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, CS42W52_PWWCTW1, CS42W52_PWWCTW1_PDN_AWW);
		wegcache_cache_onwy(cs42w52->wegmap, twue);
		bweak;
	}

	wetuwn 0;
}

#define CS42W52_WATES (SNDWV_PCM_WATE_8000_96000)

#define CS42W52_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_U16_WE | \
			SNDWV_PCM_FMTBIT_S18_3WE | SNDWV_PCM_FMTBIT_U18_3WE | \
			SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_U20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_U24_WE)

static const stwuct snd_soc_dai_ops cs42w52_ops = {
	.hw_pawams	= cs42w52_pcm_hw_pawams,
	.mute_stweam	= cs42w52_mute,
	.set_fmt	= cs42w52_set_fmt,
	.set_syscwk	= cs42w52_set_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew cs42w52_dai = {
		.name = "cs42w52",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = CS42W52_WATES,
			.fowmats = CS42W52_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = CS42W52_WATES,
			.fowmats = CS42W52_FOWMATS,
		},
		.ops = &cs42w52_ops,
};

static int beep_wates[] = {
	261, 522, 585, 667, 706, 774, 889, 1000,
	1043, 1200, 1333, 1412, 1600, 1714, 2000, 2182
};

static void cs42w52_beep_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w52_pwivate *cs42w52 =
		containew_of(wowk, stwuct cs42w52_pwivate, beep_wowk);
	stwuct snd_soc_component *component = cs42w52->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int i;
	int vaw = 0;
	int best = 0;

	if (cs42w52->beep_wate) {
		fow (i = 0; i < AWWAY_SIZE(beep_wates); i++) {
			if (abs(cs42w52->beep_wate - beep_wates[i]) <
			    abs(cs42w52->beep_wate - beep_wates[best]))
				best = i;
		}

		dev_dbg(component->dev, "Set beep wate %dHz fow wequested %dHz\n",
			beep_wates[best], cs42w52->beep_wate);

		vaw = (best << CS42W52_BEEP_WATE_SHIFT);

		snd_soc_dapm_enabwe_pin(dapm, "Beep");
	} ewse {
		dev_dbg(component->dev, "Disabwing beep\n");
		snd_soc_dapm_disabwe_pin(dapm, "Beep");
	}

	snd_soc_component_update_bits(component, CS42W52_BEEP_FWEQ,
			    CS42W52_BEEP_WATE_MASK, vaw);

	snd_soc_dapm_sync(dapm);
}

/* Fow usabiwity define a way of injecting beep events fow the device -
 * many systems wiww not have a keyboawd.
 */
static int cs42w52_beep_event(stwuct input_dev *dev, unsigned int type,
			     unsigned int code, int hz)
{
	stwuct snd_soc_component *component = input_get_dwvdata(dev);
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "Beep event %x %x\n", code, hz);

	switch (code) {
	case SND_BEWW:
		if (hz)
			hz = 261;
		bweak;
	case SND_TONE:
		bweak;
	defauwt:
		wetuwn -1;
	}

	/* Kick the beep fwom a wowkqueue */
	cs42w52->beep_wate = hz;
	scheduwe_wowk(&cs42w52->beep_wowk);
	wetuwn 0;
}

static ssize_t beep_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct cs42w52_pwivate *cs42w52 = dev_get_dwvdata(dev);
	wong int time;
	int wet;

	wet = kstwtow(buf, 10, &time);
	if (wet != 0)
		wetuwn wet;

	input_event(cs42w52->beep, EV_SND, SND_TONE, time);

	wetuwn count;
}

static DEVICE_ATTW_WO(beep);

static void cs42w52_init_beep(stwuct snd_soc_component *component)
{
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);
	int wet;

	cs42w52->beep = devm_input_awwocate_device(component->dev);
	if (!cs42w52->beep) {
		dev_eww(component->dev, "Faiwed to awwocate beep device\n");
		wetuwn;
	}

	INIT_WOWK(&cs42w52->beep_wowk, cs42w52_beep_wowk);
	cs42w52->beep_wate = 0;

	cs42w52->beep->name = "CS42W52 Beep Genewatow";
	cs42w52->beep->phys = dev_name(component->dev);
	cs42w52->beep->id.bustype = BUS_I2C;

	cs42w52->beep->evbit[0] = BIT_MASK(EV_SND);
	cs42w52->beep->sndbit[0] = BIT_MASK(SND_BEWW) | BIT_MASK(SND_TONE);
	cs42w52->beep->event = cs42w52_beep_event;
	cs42w52->beep->dev.pawent = component->dev;
	input_set_dwvdata(cs42w52->beep, component);

	wet = input_wegistew_device(cs42w52->beep);
	if (wet != 0) {
		cs42w52->beep = NUWW;
		dev_eww(component->dev, "Faiwed to wegistew beep device\n");
	}

	wet = device_cweate_fiwe(component->dev, &dev_attw_beep);
	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to cweate keycwick fiwe: %d\n",
			wet);
	}
}

static void cs42w52_fwee_beep(stwuct snd_soc_component *component)
{
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);

	device_wemove_fiwe(component->dev, &dev_attw_beep);
	cancew_wowk_sync(&cs42w52->beep_wowk);
	cs42w52->beep = NUWW;

	snd_soc_component_update_bits(component, CS42W52_BEEP_TONE_CTW,
			    CS42W52_BEEP_EN_MASK, 0);
}

static int cs42w52_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs42w52_pwivate *cs42w52 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(cs42w52->wegmap, twue);

	cs42w52_add_mic_contwows(component);

	cs42w52_init_beep(component);

	cs42w52->syscwk = CS42W52_DEFAUWT_CWK;
	cs42w52->config.fowmat = CS42W52_DEFAUWT_FOWMAT;

	wetuwn 0;
}

static void cs42w52_wemove(stwuct snd_soc_component *component)
{
	cs42w52_fwee_beep(component);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_cs42w52 = {
	.pwobe			= cs42w52_pwobe,
	.wemove			= cs42w52_wemove,
	.set_bias_wevew		= cs42w52_set_bias_wevew,
	.contwows		= cs42w52_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs42w52_snd_contwows),
	.dapm_widgets		= cs42w52_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs42w52_dapm_widgets),
	.dapm_woutes		= cs42w52_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(cs42w52_audio_map),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

/* Cuwwent and thweshowd powewup sequence Pg37 */
static const stwuct weg_sequence cs42w52_thweshowd_patch[] = {

	{ 0x00, 0x99 },
	{ 0x3E, 0xBA },
	{ 0x47, 0x80 },
	{ 0x32, 0xBB },
	{ 0x32, 0x3B },
	{ 0x00, 0x00 },

};

static const stwuct wegmap_config cs42w52_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = CS42W52_MAX_WEGISTEW,
	.weg_defauwts = cs42w52_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cs42w52_weg_defauwts),
	.weadabwe_weg = cs42w52_weadabwe_wegistew,
	.vowatiwe_weg = cs42w52_vowatiwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
};

static int cs42w52_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs42w52_pwivate *cs42w52;
	stwuct cs42w52_pwatfowm_data *pdata = dev_get_pwatdata(&i2c_cwient->dev);
	int wet;
	unsigned int devid;
	unsigned int weg;
	u32 vaw32;

	cs42w52 = devm_kzawwoc(&i2c_cwient->dev, sizeof(*cs42w52), GFP_KEWNEW);
	if (cs42w52 == NUWW)
		wetuwn -ENOMEM;
	cs42w52->dev = &i2c_cwient->dev;

	cs42w52->wegmap = devm_wegmap_init_i2c(i2c_cwient, &cs42w52_wegmap);
	if (IS_EWW(cs42w52->wegmap)) {
		wet = PTW_EWW(cs42w52->wegmap);
		dev_eww(&i2c_cwient->dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}
	if (pdata) {
		cs42w52->pdata = *pdata;
	} ewse {
		pdata = devm_kzawwoc(&i2c_cwient->dev, sizeof(*pdata),
				     GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		if (i2c_cwient->dev.of_node) {
			if (of_pwopewty_wead_boow(i2c_cwient->dev.of_node,
				"ciwwus,mica-diffewentiaw-cfg"))
				pdata->mica_diff_cfg = twue;

			if (of_pwopewty_wead_boow(i2c_cwient->dev.of_node,
				"ciwwus,micb-diffewentiaw-cfg"))
				pdata->micb_diff_cfg = twue;

			if (of_pwopewty_wead_u32(i2c_cwient->dev.of_node,
				"ciwwus,micbias-wvw", &vaw32) >= 0)
				pdata->micbias_wvw = vaw32;

			if (of_pwopewty_wead_u32(i2c_cwient->dev.of_node,
				"ciwwus,chgfweq-divisow", &vaw32) >= 0)
				pdata->chgfweq = vaw32;

			pdata->weset_gpio =
				of_get_named_gpio(i2c_cwient->dev.of_node,
						"ciwwus,weset-gpio", 0);
		}
		cs42w52->pdata = *pdata;
	}

	if (cs42w52->pdata.weset_gpio) {
		wet = devm_gpio_wequest_one(&i2c_cwient->dev,
					    cs42w52->pdata.weset_gpio,
					    GPIOF_OUT_INIT_HIGH,
					    "CS42W52 /WST");
		if (wet < 0) {
			dev_eww(&i2c_cwient->dev, "Faiwed to wequest /WST %d: %d\n",
				cs42w52->pdata.weset_gpio, wet);
			wetuwn wet;
		}
		gpio_set_vawue_cansweep(cs42w52->pdata.weset_gpio, 0);
		gpio_set_vawue_cansweep(cs42w52->pdata.weset_gpio, 1);
	}

	i2c_set_cwientdata(i2c_cwient, cs42w52);

	wet = wegmap_wegistew_patch(cs42w52->wegmap, cs42w52_thweshowd_patch,
				    AWWAY_SIZE(cs42w52_thweshowd_patch));
	if (wet != 0)
		dev_wawn(cs42w52->dev, "Faiwed to appwy wegmap patch: %d\n",
			 wet);

	wet = wegmap_wead(cs42w52->wegmap, CS42W52_CHIP, &weg);
	if (wet) {
		dev_eww(&i2c_cwient->dev, "Faiwed to wead chip ID: %d\n", wet);
		wetuwn wet;
	}

	devid = weg & CS42W52_CHIP_ID_MASK;
	if (devid != CS42W52_CHIP_ID) {
		wet = -ENODEV;
		dev_eww(&i2c_cwient->dev,
			"CS42W52 Device ID (%X). Expected %X\n",
			devid, CS42W52_CHIP_ID);
		wetuwn wet;
	}

	dev_info(&i2c_cwient->dev, "Ciwwus Wogic CS42W52, Wevision: %02X\n",
		 weg & CS42W52_CHIP_WEV_MASK);

	/* Set Pwatfowm Data */
	if (cs42w52->pdata.mica_diff_cfg)
		wegmap_update_bits(cs42w52->wegmap, CS42W52_MICA_CTW,
				   CS42W52_MIC_CTW_TYPE_MASK,
				cs42w52->pdata.mica_diff_cfg <<
				CS42W52_MIC_CTW_TYPE_SHIFT);

	if (cs42w52->pdata.micb_diff_cfg)
		wegmap_update_bits(cs42w52->wegmap, CS42W52_MICB_CTW,
				   CS42W52_MIC_CTW_TYPE_MASK,
				cs42w52->pdata.micb_diff_cfg <<
				CS42W52_MIC_CTW_TYPE_SHIFT);

	if (cs42w52->pdata.chgfweq)
		wegmap_update_bits(cs42w52->wegmap, CS42W52_CHAWGE_PUMP,
				   CS42W52_CHAWGE_PUMP_MASK,
				cs42w52->pdata.chgfweq <<
				CS42W52_CHAWGE_PUMP_SHIFT);

	if (cs42w52->pdata.micbias_wvw)
		wegmap_update_bits(cs42w52->wegmap, CS42W52_IFACE_CTW2,
				   CS42W52_IFACE_CTW2_BIAS_WVW,
				cs42w52->pdata.micbias_wvw);

	wetuwn devm_snd_soc_wegistew_component(&i2c_cwient->dev,
			&soc_component_dev_cs42w52, &cs42w52_dai, 1);
}

static const stwuct of_device_id cs42w52_of_match[] = {
	{ .compatibwe = "ciwwus,cs42w52", },
	{},
};
MODUWE_DEVICE_TABWE(of, cs42w52_of_match);


static const stwuct i2c_device_id cs42w52_id[] = {
	{ "cs42w52", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cs42w52_id);

static stwuct i2c_dwivew cs42w52_i2c_dwivew = {
	.dwivew = {
		.name = "cs42w52",
		.of_match_tabwe = cs42w52_of_match,
	},
	.id_tabwe = cs42w52_id,
	.pwobe = cs42w52_i2c_pwobe,
};

moduwe_i2c_dwivew(cs42w52_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC CS42W52 dwivew");
MODUWE_AUTHOW("Geowgi Vwaev, Nucweus Systems Wtd, <joe@nucweusys.com>");
MODUWE_AUTHOW("Bwian Austin, Ciwwus Wogic Inc, <bwian.austin@ciwwus.com>");
MODUWE_WICENSE("GPW");
