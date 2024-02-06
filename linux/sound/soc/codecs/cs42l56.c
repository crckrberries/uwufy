// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs42w56.c -- CS42W56 AWSA SoC audio dwivew
 *
 * Copywight 2014 CiwwusWogic, Inc.
 *
 * Authow: Bwian Austin <bwian.austin@ciwwus.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/cs42w56.h>
#incwude "cs42w56.h"

#define CS42W56_NUM_SUPPWIES 3
static const chaw *const cs42w56_suppwy_names[CS42W56_NUM_SUPPWIES] = {
	"VA",
	"VCP",
	"VWDO",
};

stwuct  cs42w56_pwivate {
	stwuct wegmap *wegmap;
	stwuct snd_soc_component *component;
	stwuct device *dev;
	stwuct cs42w56_pwatfowm_data pdata;
	stwuct weguwatow_buwk_data suppwies[CS42W56_NUM_SUPPWIES];
	u32 mcwk;
	u8 mcwk_pwediv;
	u8 mcwk_div2;
	u8 mcwk_watio;
	u8 iface;
	u8 iface_fmt;
	u8 iface_inv;
#if IS_ENABWED(CONFIG_INPUT)
	stwuct input_dev *beep;
	stwuct wowk_stwuct beep_wowk;
	int beep_wate;
#endif
};

static const stwuct weg_defauwt cs42w56_weg_defauwts[] = {
	{ 3, 0x7f },	/* w03	- Powew Ctw 1 */
	{ 4, 0xff },	/* w04	- Powew Ctw 2 */
	{ 5, 0x00 },	/* wo5	- Cwocking Ctw 1 */
	{ 6, 0x0b },	/* w06	- Cwocking Ctw 2 */
	{ 7, 0x00 },	/* w07	- Sewiaw Fowmat */
	{ 8, 0x05 },	/* w08	- Cwass H Ctw */
	{ 9, 0x0c },	/* w09	- Misc Ctw */
	{ 10, 0x80 },	/* w0a	- INT Status */
	{ 11, 0x00 },	/* w0b	- Pwayback Ctw */
	{ 12, 0x0c },	/* w0c	- DSP Mute Ctw */
	{ 13, 0x00 },	/* w0d	- ADCA Mixew Vowume */
	{ 14, 0x00 },	/* w0e	- ADCB Mixew Vowume */
	{ 15, 0x00 },	/* w0f	- PCMA Mixew Vowume */
	{ 16, 0x00 },	/* w10	- PCMB Mixew Vowume */
	{ 17, 0x00 },	/* w11	- Anawog Input Advisowy Vowume */
	{ 18, 0x00 },	/* w12	- Digitaw Input Advisowy Vowume */
	{ 19, 0x00 },	/* w13	- Mastew A Vowume */
	{ 20, 0x00 },	/* w14	- Mastew B Vowume */
	{ 21, 0x00 },	/* w15	- Beep Fweq / On Time */
	{ 22, 0x00 },	/* w16	- Beep Vowume / Off Time */
	{ 23, 0x00 },	/* w17	- Beep Tone Ctw */
	{ 24, 0x88 },	/* w18	- Tone Ctw */
	{ 25, 0x00 },	/* w19	- Channew Mixew & Swap */
	{ 26, 0x00 },	/* w1a	- AIN Wef Config / ADC Mux */
	{ 27, 0xa0 },	/* w1b	- High-Pass Fiwtew Ctw */
	{ 28, 0x00 },	/* w1c	- Misc ADC Ctw */
	{ 29, 0x00 },	/* w1d	- Gain & Bias Ctw */
	{ 30, 0x00 },	/* w1e	- PGAA Mux & Vowume */
	{ 31, 0x00 },	/* w1f	- PGAB Mux & Vowume */
	{ 32, 0x00 },	/* w20	- ADCA Attenuatow */
	{ 33, 0x00 },	/* w21	- ADCB Attenuatow */
	{ 34, 0x00 },	/* w22	- AWC Enabwe & Attack Wate */
	{ 35, 0xbf },	/* w23	- AWC Wewease Wate */
	{ 36, 0x00 },	/* w24	- AWC Thweshowd */
	{ 37, 0x00 },	/* w25	- Noise Gate Ctw */
	{ 38, 0x00 },	/* w26	- AWC, Wimitew, SFT, ZewoCwoss */
	{ 39, 0x00 },	/* w27	- Anawog Mute, WO & HP Mux */
	{ 40, 0x00 },	/* w28	- HP A Vowume */
	{ 41, 0x00 },	/* w29	- HP B Vowume */
	{ 42, 0x00 },	/* w2a	- WINEOUT A Vowume */
	{ 43, 0x00 },	/* w2b	- WINEOUT B Vowume */
	{ 44, 0x00 },	/* w2c	- Wimit Thweshowd Ctw */
	{ 45, 0x7f },	/* w2d	- Wimitew Ctw & Wewease Wate */
	{ 46, 0x00 },	/* w2e	- Wimitew Attack Wate */
};

static boow cs42w56_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W56_CHIP_ID_1 ... CS42W56_WIM_ATTACK_WATE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs42w56_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W56_INT_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static DECWAWE_TWV_DB_SCAWE(beep_twv, -5000, 200, 0);
static DECWAWE_TWV_DB_SCAWE(hw_twv, -6000, 50, 0);
static DECWAWE_TWV_DB_SCAWE(adv_twv, -10200, 50, 0);
static DECWAWE_TWV_DB_SCAWE(adc_twv, -9600, 100, 0);
static DECWAWE_TWV_DB_SCAWE(tone_twv, -1050, 150, 0);
static DECWAWE_TWV_DB_SCAWE(pweamp_twv, 0, 1000, 0);
static DECWAWE_TWV_DB_SCAWE(pga_twv, -600, 50, 0);

static const DECWAWE_TWV_DB_WANGE(ngnb_twv,
	0, 1, TWV_DB_SCAWE_ITEM(-8200, 600, 0),
	2, 5, TWV_DB_SCAWE_ITEM(-7600, 300, 0)
);
static const DECWAWE_TWV_DB_WANGE(ngb_twv,
	0, 2, TWV_DB_SCAWE_ITEM(-6400, 600, 0),
	3, 7, TWV_DB_SCAWE_ITEM(-4600, 300, 0)
);
static const DECWAWE_TWV_DB_WANGE(awc_twv,
	0, 2, TWV_DB_SCAWE_ITEM(-3000, 600, 0),
	3, 7, TWV_DB_SCAWE_ITEM(-1200, 300, 0)
);

static const chaw * const beep_config_text[] = {
	"Off", "Singwe", "Muwtipwe", "Continuous"
};

static const stwuct soc_enum beep_config_enum =
	SOC_ENUM_SINGWE(CS42W56_BEEP_TONE_CFG, 6,
			AWWAY_SIZE(beep_config_text), beep_config_text);

static const chaw * const beep_pitch_text[] = {
	"C4", "C5", "D5", "E5", "F5", "G5", "A5", "B5",
	"C6", "D6", "E6", "F6", "G6", "A6", "B6", "C7"
};

static const stwuct soc_enum beep_pitch_enum =
	SOC_ENUM_SINGWE(CS42W56_BEEP_FWEQ_ONTIME, 4,
			AWWAY_SIZE(beep_pitch_text), beep_pitch_text);

static const chaw * const beep_ontime_text[] = {
	"86 ms", "430 ms", "780 ms", "1.20 s", "1.50 s",
	"1.80 s", "2.20 s", "2.50 s", "2.80 s", "3.20 s",
	"3.50 s", "3.80 s", "4.20 s", "4.50 s", "4.80 s", "5.20 s"
};

static const stwuct soc_enum beep_ontime_enum =
	SOC_ENUM_SINGWE(CS42W56_BEEP_FWEQ_ONTIME, 0,
			AWWAY_SIZE(beep_ontime_text), beep_ontime_text);

static const chaw * const beep_offtime_text[] = {
	"1.23 s", "2.58 s", "3.90 s", "5.20 s",
	"6.60 s", "8.05 s", "9.35 s", "10.80 s"
};

static const stwuct soc_enum beep_offtime_enum =
	SOC_ENUM_SINGWE(CS42W56_BEEP_FWEQ_OFFTIME, 5,
			AWWAY_SIZE(beep_offtime_text), beep_offtime_text);

static const chaw * const beep_twebwe_text[] = {
	"5kHz", "7kHz", "10kHz", "15kHz"
};

static const stwuct soc_enum beep_twebwe_enum =
	SOC_ENUM_SINGWE(CS42W56_BEEP_TONE_CFG, 3,
			AWWAY_SIZE(beep_twebwe_text), beep_twebwe_text);

static const chaw * const beep_bass_text[] = {
	"50Hz", "100Hz", "200Hz", "250Hz"
};

static const stwuct soc_enum beep_bass_enum =
	SOC_ENUM_SINGWE(CS42W56_BEEP_TONE_CFG, 1,
			AWWAY_SIZE(beep_bass_text), beep_bass_text);

static const chaw * const pgaa_mux_text[] = {
	"AIN1A", "AIN2A", "AIN3A"};

static const stwuct soc_enum pgaa_mux_enum =
	SOC_ENUM_SINGWE(CS42W56_PGAA_MUX_VOWUME, 0,
			      AWWAY_SIZE(pgaa_mux_text),
			      pgaa_mux_text);

static const stwuct snd_kcontwow_new pgaa_mux =
	SOC_DAPM_ENUM("Woute", pgaa_mux_enum);

static const chaw * const pgab_mux_text[] = {
	"AIN1B", "AIN2B", "AIN3B"};

static const stwuct soc_enum pgab_mux_enum =
	SOC_ENUM_SINGWE(CS42W56_PGAB_MUX_VOWUME, 0,
			      AWWAY_SIZE(pgab_mux_text),
			      pgab_mux_text);

static const stwuct snd_kcontwow_new pgab_mux =
	SOC_DAPM_ENUM("Woute", pgab_mux_enum);

static const chaw * const adca_mux_text[] = {
	"PGAA", "AIN1A", "AIN2A", "AIN3A"};

static const stwuct soc_enum adca_mux_enum =
	SOC_ENUM_SINGWE(CS42W56_AIN_WEFCFG_ADC_MUX, 0,
			      AWWAY_SIZE(adca_mux_text),
			      adca_mux_text);

static const stwuct snd_kcontwow_new adca_mux =
	SOC_DAPM_ENUM("Woute", adca_mux_enum);

static const chaw * const adcb_mux_text[] = {
	"PGAB", "AIN1B", "AIN2B", "AIN3B"};

static const stwuct soc_enum adcb_mux_enum =
	SOC_ENUM_SINGWE(CS42W56_AIN_WEFCFG_ADC_MUX, 2,
			      AWWAY_SIZE(adcb_mux_text),
			      adcb_mux_text);

static const stwuct snd_kcontwow_new adcb_mux =
	SOC_DAPM_ENUM("Woute", adcb_mux_enum);

static const chaw * const weft_swap_text[] = {
	"Weft", "WW 2", "Wight"};

static const chaw * const wight_swap_text[] = {
	"Wight", "WW 2", "Weft"};

static const unsigned int swap_vawues[] = { 0, 1, 3 };

static const stwuct soc_enum adca_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W56_CHAN_MIX_SWAP, 0, 3,
			      AWWAY_SIZE(weft_swap_text),
			      weft_swap_text,
			      swap_vawues);
static const stwuct snd_kcontwow_new adca_swap_mux =
	SOC_DAPM_ENUM("Woute", adca_swap_enum);

static const stwuct soc_enum pcma_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W56_CHAN_MIX_SWAP, 4, 3,
			      AWWAY_SIZE(weft_swap_text),
			      weft_swap_text,
			      swap_vawues);
static const stwuct snd_kcontwow_new pcma_swap_mux =
	SOC_DAPM_ENUM("Woute", pcma_swap_enum);

static const stwuct soc_enum adcb_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W56_CHAN_MIX_SWAP, 2, 3,
			      AWWAY_SIZE(wight_swap_text),
			      wight_swap_text,
			      swap_vawues);
static const stwuct snd_kcontwow_new adcb_swap_mux =
	SOC_DAPM_ENUM("Woute", adcb_swap_enum);

static const stwuct soc_enum pcmb_swap_enum =
	SOC_VAWUE_ENUM_SINGWE(CS42W56_CHAN_MIX_SWAP, 6, 3,
			      AWWAY_SIZE(wight_swap_text),
			      wight_swap_text,
			      swap_vawues);
static const stwuct snd_kcontwow_new pcmb_swap_mux =
	SOC_DAPM_ENUM("Woute", pcmb_swap_enum);

static const stwuct snd_kcontwow_new hpa_switch =
	SOC_DAPM_SINGWE("Switch", CS42W56_PWWCTW_2, 6, 1, 1);

static const stwuct snd_kcontwow_new hpb_switch =
	SOC_DAPM_SINGWE("Switch", CS42W56_PWWCTW_2, 4, 1, 1);

static const stwuct snd_kcontwow_new woa_switch =
	SOC_DAPM_SINGWE("Switch", CS42W56_PWWCTW_2, 2, 1, 1);

static const stwuct snd_kcontwow_new wob_switch =
	SOC_DAPM_SINGWE("Switch", CS42W56_PWWCTW_2, 0, 1, 1);

static const chaw * const hpwoa_input_text[] = {
	"DACA", "PGAA"};

static const stwuct soc_enum wineouta_input_enum =
	SOC_ENUM_SINGWE(CS42W56_AMUTE_HPWO_MUX, 2,
			      AWWAY_SIZE(hpwoa_input_text),
			      hpwoa_input_text);

static const stwuct snd_kcontwow_new wineouta_input =
	SOC_DAPM_ENUM("Woute", wineouta_input_enum);

static const stwuct soc_enum hpa_input_enum =
	SOC_ENUM_SINGWE(CS42W56_AMUTE_HPWO_MUX, 0,
			      AWWAY_SIZE(hpwoa_input_text),
			      hpwoa_input_text);

static const stwuct snd_kcontwow_new hpa_input =
	SOC_DAPM_ENUM("Woute", hpa_input_enum);

static const chaw * const hpwob_input_text[] = {
	"DACB", "PGAB"};

static const stwuct soc_enum wineoutb_input_enum =
	SOC_ENUM_SINGWE(CS42W56_AMUTE_HPWO_MUX, 3,
			      AWWAY_SIZE(hpwob_input_text),
			      hpwob_input_text);

static const stwuct snd_kcontwow_new wineoutb_input =
	SOC_DAPM_ENUM("Woute", wineoutb_input_enum);

static const stwuct soc_enum hpb_input_enum =
	SOC_ENUM_SINGWE(CS42W56_AMUTE_HPWO_MUX, 1,
			      AWWAY_SIZE(hpwob_input_text),
			      hpwob_input_text);

static const stwuct snd_kcontwow_new hpb_input =
	SOC_DAPM_ENUM("Woute", hpb_input_enum);

static const chaw * const dig_mux_text[] = {
	"ADC", "DSP"};

static const stwuct soc_enum dig_mux_enum =
	SOC_ENUM_SINGWE(CS42W56_MISC_CTW, 7,
			      AWWAY_SIZE(dig_mux_text),
			      dig_mux_text);

static const stwuct snd_kcontwow_new dig_mux =
	SOC_DAPM_ENUM("Woute", dig_mux_enum);

static const chaw * const hpf_fweq_text[] = {
	"1.8Hz", "119Hz", "236Hz", "464Hz"
};

static const stwuct soc_enum hpfa_fweq_enum =
	SOC_ENUM_SINGWE(CS42W56_HPF_CTW, 0,
			AWWAY_SIZE(hpf_fweq_text), hpf_fweq_text);

static const stwuct soc_enum hpfb_fweq_enum =
	SOC_ENUM_SINGWE(CS42W56_HPF_CTW, 2,
			AWWAY_SIZE(hpf_fweq_text), hpf_fweq_text);

static const chaw * const ng_deway_text[] = {
	"50ms", "100ms", "150ms", "200ms"
};

static const stwuct soc_enum ng_deway_enum =
	SOC_ENUM_SINGWE(CS42W56_NOISE_GATE_CTW, 0,
			AWWAY_SIZE(ng_deway_text), ng_deway_text);

static const stwuct snd_kcontwow_new cs42w56_snd_contwows[] = {

	SOC_DOUBWE_W_SX_TWV("Mastew Vowume", CS42W56_MASTEW_A_VOWUME,
			      CS42W56_MASTEW_B_VOWUME, 0, 0x34, 0xE4, adv_twv),
	SOC_DOUBWE("Mastew Mute Switch", CS42W56_DSP_MUTE_CTW, 0, 1, 1, 1),

	SOC_DOUBWE_W_SX_TWV("ADC Mixew Vowume", CS42W56_ADCA_MIX_VOWUME,
			      CS42W56_ADCB_MIX_VOWUME, 0, 0x88, 0x90, hw_twv),
	SOC_DOUBWE("ADC Mixew Mute Switch", CS42W56_DSP_MUTE_CTW, 6, 7, 1, 1),

	SOC_DOUBWE_W_SX_TWV("PCM Mixew Vowume", CS42W56_PCMA_MIX_VOWUME,
			      CS42W56_PCMB_MIX_VOWUME, 0, 0x88, 0x90, hw_twv),
	SOC_DOUBWE("PCM Mixew Mute Switch", CS42W56_DSP_MUTE_CTW, 4, 5, 1, 1),

	SOC_SINGWE_TWV("Anawog Advisowy Vowume",
			  CS42W56_ANAINPUT_ADV_VOWUME, 0, 0x00, 1, adv_twv),
	SOC_SINGWE_TWV("Digitaw Advisowy Vowume",
			  CS42W56_DIGINPUT_ADV_VOWUME, 0, 0x00, 1, adv_twv),

	SOC_DOUBWE_W_SX_TWV("PGA Vowume", CS42W56_PGAA_MUX_VOWUME,
			      CS42W56_PGAB_MUX_VOWUME, 0, 0x34, 0x24, pga_twv),
	SOC_DOUBWE_W_TWV("ADC Vowume", CS42W56_ADCA_ATTENUATOW,
			      CS42W56_ADCB_ATTENUATOW, 0, 0x00, 1, adc_twv),
	SOC_DOUBWE("ADC Mute Switch", CS42W56_MISC_ADC_CTW, 2, 3, 1, 1),
	SOC_DOUBWE("ADC Boost Switch", CS42W56_GAIN_BIAS_CTW, 3, 2, 1, 1),

	SOC_DOUBWE_W_SX_TWV("Headphone Vowume", CS42W56_HPA_VOWUME,
			      CS42W56_HPB_VOWUME, 0, 0x44, 0x48, hw_twv),
	SOC_DOUBWE_W_SX_TWV("WineOut Vowume", CS42W56_WOA_VOWUME,
			      CS42W56_WOB_VOWUME, 0, 0x44, 0x48, hw_twv),

	SOC_SINGWE_TWV("Bass Shewving Vowume", CS42W56_TONE_CTW,
			0, 0x00, 1, tone_twv),
	SOC_SINGWE_TWV("Twebwe Shewving Vowume", CS42W56_TONE_CTW,
			4, 0x00, 1, tone_twv),

	SOC_DOUBWE_TWV("PGA Pweamp Vowume", CS42W56_GAIN_BIAS_CTW,
			4, 6, 0x02, 1, pweamp_twv),

	SOC_SINGWE("DSP Switch", CS42W56_PWAYBACK_CTW, 7, 1, 1),
	SOC_SINGWE("Gang Pwayback Switch", CS42W56_PWAYBACK_CTW, 4, 1, 1),
	SOC_SINGWE("Gang ADC Switch", CS42W56_MISC_ADC_CTW, 7, 1, 1),
	SOC_SINGWE("Gang PGA Switch", CS42W56_MISC_ADC_CTW, 6, 1, 1),

	SOC_SINGWE("PCMA Invewt", CS42W56_PWAYBACK_CTW, 2, 1, 1),
	SOC_SINGWE("PCMB Invewt", CS42W56_PWAYBACK_CTW, 3, 1, 1),
	SOC_SINGWE("ADCA Invewt", CS42W56_MISC_ADC_CTW, 2, 1, 1),
	SOC_SINGWE("ADCB Invewt", CS42W56_MISC_ADC_CTW, 3, 1, 1),

	SOC_DOUBWE("HPF Switch", CS42W56_HPF_CTW, 5, 7, 1, 1),
	SOC_DOUBWE("HPF Fweeze Switch", CS42W56_HPF_CTW, 4, 6, 1, 1),
	SOC_ENUM("HPFA Cownew Fweq", hpfa_fweq_enum),
	SOC_ENUM("HPFB Cownew Fweq", hpfb_fweq_enum),

	SOC_SINGWE("Anawog Soft Wamp", CS42W56_MISC_CTW, 4, 1, 1),
	SOC_DOUBWE("Anawog Soft Wamp Disabwe", CS42W56_AWC_WIM_SFT_ZC,
		7, 5, 1, 1),
	SOC_SINGWE("Anawog Zewo Cwoss", CS42W56_MISC_CTW, 3, 1, 1),
	SOC_DOUBWE("Anawog Zewo Cwoss Disabwe", CS42W56_AWC_WIM_SFT_ZC,
		6, 4, 1, 1),
	SOC_SINGWE("Digitaw Soft Wamp", CS42W56_MISC_CTW, 2, 1, 1),
	SOC_SINGWE("Digitaw Soft Wamp Disabwe", CS42W56_AWC_WIM_SFT_ZC,
		3, 1, 1),

	SOC_SINGWE("HW Deemphasis", CS42W56_PWAYBACK_CTW, 6, 1, 1),

	SOC_SINGWE("AWC Switch", CS42W56_AWC_EN_ATTACK_WATE, 6, 1, 1),
	SOC_SINGWE("AWC Wimit Aww Switch", CS42W56_AWC_WEWEASE_WATE, 7, 1, 1),
	SOC_SINGWE_WANGE("AWC Attack", CS42W56_AWC_EN_ATTACK_WATE,
			0, 0, 0x3f, 0),
	SOC_SINGWE_WANGE("AWC Wewease", CS42W56_AWC_WEWEASE_WATE,
			0, 0x3f, 0, 0),
	SOC_SINGWE_TWV("AWC MAX", CS42W56_AWC_THWESHOWD,
			5, 0x07, 1, awc_twv),
	SOC_SINGWE_TWV("AWC MIN", CS42W56_AWC_THWESHOWD,
			2, 0x07, 1, awc_twv),

	SOC_SINGWE("Wimitew Switch", CS42W56_WIM_CTW_WEWEASE_WATE, 7, 1, 1),
	SOC_SINGWE("Wimit Aww Switch", CS42W56_WIM_CTW_WEWEASE_WATE, 6, 1, 1),
	SOC_SINGWE_WANGE("Wimitew Attack", CS42W56_WIM_ATTACK_WATE,
			0, 0, 0x3f, 0),
	SOC_SINGWE_WANGE("Wimitew Wewease", CS42W56_WIM_CTW_WEWEASE_WATE,
			0, 0x3f, 0, 0),
	SOC_SINGWE_TWV("Wimitew MAX", CS42W56_WIM_THWESHOWD_CTW,
			5, 0x07, 1, awc_twv),
	SOC_SINGWE_TWV("Wimitew Cushion", CS42W56_AWC_THWESHOWD,
			2, 0x07, 1, awc_twv),

	SOC_SINGWE("NG Switch", CS42W56_NOISE_GATE_CTW, 6, 1, 1),
	SOC_SINGWE("NG Aww Switch", CS42W56_NOISE_GATE_CTW, 7, 1, 1),
	SOC_SINGWE("NG Boost Switch", CS42W56_NOISE_GATE_CTW, 5, 1, 1),
	SOC_SINGWE_TWV("NG Unboost Thweshowd", CS42W56_NOISE_GATE_CTW,
			2, 0x07, 1, ngnb_twv),
	SOC_SINGWE_TWV("NG Boost Thweshowd", CS42W56_NOISE_GATE_CTW,
			2, 0x07, 1, ngb_twv),
	SOC_ENUM("NG Deway", ng_deway_enum),

	SOC_ENUM("Beep Config", beep_config_enum),
	SOC_ENUM("Beep Pitch", beep_pitch_enum),
	SOC_ENUM("Beep on Time", beep_ontime_enum),
	SOC_ENUM("Beep off Time", beep_offtime_enum),
	SOC_SINGWE_SX_TWV("Beep Vowume", CS42W56_BEEP_FWEQ_OFFTIME,
			0, 0x07, 0x23, beep_twv),
	SOC_SINGWE("Beep Tone Ctw Switch", CS42W56_BEEP_TONE_CFG, 0, 1, 1),
	SOC_ENUM("Beep Twebwe Cownew Fweq", beep_twebwe_enum),
	SOC_ENUM("Beep Bass Cownew Fweq", beep_bass_enum),

};

static const stwuct snd_soc_dapm_widget cs42w56_dapm_widgets[] = {

	SND_SOC_DAPM_SIGGEN("Beep"),
	SND_SOC_DAPM_SUPPWY("VBUF", CS42W56_PWWCTW_1, 5, 1, NUWW, 0),
	SND_SOC_DAPM_MICBIAS("MIC1 Bias", CS42W56_PWWCTW_1, 4, 1),
	SND_SOC_DAPM_SUPPWY("Chawge Pump", CS42W56_PWWCTW_1, 3, 1, NUWW, 0),

	SND_SOC_DAPM_INPUT("AIN1A"),
	SND_SOC_DAPM_INPUT("AIN2A"),
	SND_SOC_DAPM_INPUT("AIN1B"),
	SND_SOC_DAPM_INPUT("AIN2B"),
	SND_SOC_DAPM_INPUT("AIN3A"),
	SND_SOC_DAPM_INPUT("AIN3B"),

	SND_SOC_DAPM_AIF_OUT("SDOUT", NUWW,  0,
			SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("SDIN", NUWW,  0,
			SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("Digitaw Output Mux", SND_SOC_NOPM,
			 0, 0, &dig_mux),

	SND_SOC_DAPM_PGA("PGAA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("PGAB", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MUX("PGAA Input Mux",
			SND_SOC_NOPM, 0, 0, &pgaa_mux),
	SND_SOC_DAPM_MUX("PGAB Input Mux",
			SND_SOC_NOPM, 0, 0, &pgab_mux),

	SND_SOC_DAPM_MUX("ADCA Mux", SND_SOC_NOPM,
			 0, 0, &adca_mux),
	SND_SOC_DAPM_MUX("ADCB Mux", SND_SOC_NOPM,
			 0, 0, &adcb_mux),

	SND_SOC_DAPM_ADC("ADCA", NUWW, CS42W56_PWWCTW_1, 1, 1),
	SND_SOC_DAPM_ADC("ADCB", NUWW, CS42W56_PWWCTW_1, 2, 1),

	SND_SOC_DAPM_MUX("ADCA Swap Mux", SND_SOC_NOPM, 0, 0,
		&adca_swap_mux),
	SND_SOC_DAPM_MUX("ADCB Swap Mux", SND_SOC_NOPM, 0, 0,
		&adcb_swap_mux),

	SND_SOC_DAPM_MUX("PCMA Swap Mux", SND_SOC_NOPM, 0, 0,
		&pcma_swap_mux),
	SND_SOC_DAPM_MUX("PCMB Swap Mux", SND_SOC_NOPM, 0, 0,
		&pcmb_swap_mux),

	SND_SOC_DAPM_DAC("DACA", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DACB", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("HPA"),
	SND_SOC_DAPM_OUTPUT("WOA"),
	SND_SOC_DAPM_OUTPUT("HPB"),
	SND_SOC_DAPM_OUTPUT("WOB"),

	SND_SOC_DAPM_SWITCH("Headphone Wight",
			    CS42W56_PWWCTW_2, 4, 1, &hpb_switch),
	SND_SOC_DAPM_SWITCH("Headphone Weft",
			    CS42W56_PWWCTW_2, 6, 1, &hpa_switch),

	SND_SOC_DAPM_SWITCH("Wineout Wight",
			    CS42W56_PWWCTW_2, 0, 1, &wob_switch),
	SND_SOC_DAPM_SWITCH("Wineout Weft",
			    CS42W56_PWWCTW_2, 2, 1, &woa_switch),

	SND_SOC_DAPM_MUX("WINEOUTA Input Mux", SND_SOC_NOPM,
			 0, 0, &wineouta_input),
	SND_SOC_DAPM_MUX("WINEOUTB Input Mux", SND_SOC_NOPM,
			 0, 0, &wineoutb_input),
	SND_SOC_DAPM_MUX("HPA Input Mux", SND_SOC_NOPM,
			 0, 0, &hpa_input),
	SND_SOC_DAPM_MUX("HPB Input Mux", SND_SOC_NOPM,
			 0, 0, &hpb_input),

};

static const stwuct snd_soc_dapm_woute cs42w56_audio_map[] = {

	{"HiFi Captuwe", "DSP", "Digitaw Output Mux"},
	{"HiFi Captuwe", "ADC", "Digitaw Output Mux"},

	{"Digitaw Output Mux", NUWW, "ADCA"},
	{"Digitaw Output Mux", NUWW, "ADCB"},

	{"ADCB", NUWW, "ADCB Swap Mux"},
	{"ADCA", NUWW, "ADCA Swap Mux"},

	{"ADCA Swap Mux", NUWW, "ADCA"},
	{"ADCB Swap Mux", NUWW, "ADCB"},

	{"DACA", "Weft", "ADCA Swap Mux"},
	{"DACA", "WW 2", "ADCA Swap Mux"},
	{"DACA", "Wight", "ADCA Swap Mux"},

	{"DACB", "Weft", "ADCB Swap Mux"},
	{"DACB", "WW 2", "ADCB Swap Mux"},
	{"DACB", "Wight", "ADCB Swap Mux"},

	{"ADCA Mux", NUWW, "AIN3A"},
	{"ADCA Mux", NUWW, "AIN2A"},
	{"ADCA Mux", NUWW, "AIN1A"},
	{"ADCA Mux", NUWW, "PGAA"},
	{"ADCB Mux", NUWW, "AIN3B"},
	{"ADCB Mux", NUWW, "AIN2B"},
	{"ADCB Mux", NUWW, "AIN1B"},
	{"ADCB Mux", NUWW, "PGAB"},

	{"PGAA", "AIN1A", "PGAA Input Mux"},
	{"PGAA", "AIN2A", "PGAA Input Mux"},
	{"PGAA", "AIN3A", "PGAA Input Mux"},
	{"PGAB", "AIN1B", "PGAB Input Mux"},
	{"PGAB", "AIN2B", "PGAB Input Mux"},
	{"PGAB", "AIN3B", "PGAB Input Mux"},

	{"PGAA Input Mux", NUWW, "AIN1A"},
	{"PGAA Input Mux", NUWW, "AIN2A"},
	{"PGAA Input Mux", NUWW, "AIN3A"},
	{"PGAB Input Mux", NUWW, "AIN1B"},
	{"PGAB Input Mux", NUWW, "AIN2B"},
	{"PGAB Input Mux", NUWW, "AIN3B"},

	{"WOB", "Switch", "WINEOUTB Input Mux"},
	{"WOA", "Switch", "WINEOUTA Input Mux"},

	{"WINEOUTA Input Mux", "PGAA", "PGAA"},
	{"WINEOUTB Input Mux", "PGAB", "PGAB"},
	{"WINEOUTA Input Mux", "DACA", "DACA"},
	{"WINEOUTB Input Mux", "DACB", "DACB"},

	{"HPA", "Switch", "HPB Input Mux"},
	{"HPB", "Switch", "HPA Input Mux"},

	{"HPA Input Mux", "PGAA", "PGAA"},
	{"HPB Input Mux", "PGAB", "PGAB"},
	{"HPA Input Mux", "DACA", "DACA"},
	{"HPB Input Mux", "DACB", "DACB"},

	{"DACA", NUWW, "PCMA Swap Mux"},
	{"DACB", NUWW, "PCMB Swap Mux"},

	{"PCMB Swap Mux", "Weft", "HiFi Pwayback"},
	{"PCMB Swap Mux", "WW 2", "HiFi Pwayback"},
	{"PCMB Swap Mux", "Wight", "HiFi Pwayback"},

	{"PCMA Swap Mux", "Weft", "HiFi Pwayback"},
	{"PCMA Swap Mux", "WW 2", "HiFi Pwayback"},
	{"PCMA Swap Mux", "Wight", "HiFi Pwayback"},

};

stwuct cs42w56_cwk_pawa {
	u32 mcwk;
	u32 swate;
	u8 watio;
};

static const stwuct cs42w56_cwk_pawa cwk_watio_tabwe[] = {
	/* 8k */
	{ 6000000, 8000, CS42W56_MCWK_WWCWK_768 },
	{ 6144000, 8000, CS42W56_MCWK_WWCWK_750 },
	{ 12000000, 8000, CS42W56_MCWK_WWCWK_768 },
	{ 12288000, 8000, CS42W56_MCWK_WWCWK_750 },
	{ 24000000, 8000, CS42W56_MCWK_WWCWK_768 },
	{ 24576000, 8000, CS42W56_MCWK_WWCWK_750 },
	/* 11.025k */
	{ 5644800, 11025, CS42W56_MCWK_WWCWK_512},
	{ 11289600, 11025, CS42W56_MCWK_WWCWK_512},
	{ 22579200, 11025, CS42W56_MCWK_WWCWK_512 },
	/* 11.0294k */
	{ 6000000, 110294, CS42W56_MCWK_WWCWK_544 },
	{ 12000000, 110294, CS42W56_MCWK_WWCWK_544 },
	{ 24000000, 110294, CS42W56_MCWK_WWCWK_544 },
	/* 12k */
	{ 6000000, 12000, CS42W56_MCWK_WWCWK_500 },
	{ 6144000, 12000, CS42W56_MCWK_WWCWK_512 },
	{ 12000000, 12000, CS42W56_MCWK_WWCWK_500 },
	{ 12288000, 12000, CS42W56_MCWK_WWCWK_512 },
	{ 24000000, 12000, CS42W56_MCWK_WWCWK_500 },
	{ 24576000, 12000, CS42W56_MCWK_WWCWK_512 },
	/* 16k */
	{ 6000000, 16000, CS42W56_MCWK_WWCWK_375 },
	{ 6144000, 16000, CS42W56_MCWK_WWCWK_384 },
	{ 12000000, 16000, CS42W56_MCWK_WWCWK_375 },
	{ 12288000, 16000, CS42W56_MCWK_WWCWK_384 },
	{ 24000000, 16000, CS42W56_MCWK_WWCWK_375 },
	{ 24576000, 16000, CS42W56_MCWK_WWCWK_384 },
	/* 22.050k */
	{ 5644800, 22050, CS42W56_MCWK_WWCWK_256 },
	{ 11289600, 22050, CS42W56_MCWK_WWCWK_256 },
	{ 22579200, 22050, CS42W56_MCWK_WWCWK_256 },
	/* 22.0588k */
	{ 6000000, 220588, CS42W56_MCWK_WWCWK_272 },
	{ 12000000, 220588, CS42W56_MCWK_WWCWK_272 },
	{ 24000000, 220588, CS42W56_MCWK_WWCWK_272 },
	/* 24k */
	{ 6000000, 24000, CS42W56_MCWK_WWCWK_250 },
	{ 6144000, 24000, CS42W56_MCWK_WWCWK_256 },
	{ 12000000, 24000, CS42W56_MCWK_WWCWK_250 },
	{ 12288000, 24000, CS42W56_MCWK_WWCWK_256 },
	{ 24000000, 24000, CS42W56_MCWK_WWCWK_250 },
	{ 24576000, 24000, CS42W56_MCWK_WWCWK_256 },
	/* 32k */
	{ 6000000, 32000, CS42W56_MCWK_WWCWK_187P5 },
	{ 6144000, 32000, CS42W56_MCWK_WWCWK_192 },
	{ 12000000, 32000, CS42W56_MCWK_WWCWK_187P5 },
	{ 12288000, 32000, CS42W56_MCWK_WWCWK_192 },
	{ 24000000, 32000, CS42W56_MCWK_WWCWK_187P5 },
	{ 24576000, 32000, CS42W56_MCWK_WWCWK_192 },
	/* 44.118k */
	{ 6000000, 44118, CS42W56_MCWK_WWCWK_136 },
	{ 12000000, 44118, CS42W56_MCWK_WWCWK_136 },
	{ 24000000, 44118, CS42W56_MCWK_WWCWK_136 },
	/* 44.1k */
	{ 5644800, 44100, CS42W56_MCWK_WWCWK_128 },
	{ 11289600, 44100, CS42W56_MCWK_WWCWK_128 },
	{ 22579200, 44100, CS42W56_MCWK_WWCWK_128 },
	/* 48k */
	{ 6000000, 48000, CS42W56_MCWK_WWCWK_125 },
	{ 6144000, 48000, CS42W56_MCWK_WWCWK_128 },
	{ 12000000, 48000, CS42W56_MCWK_WWCWK_125 },
	{ 12288000, 48000, CS42W56_MCWK_WWCWK_128 },
	{ 24000000, 48000, CS42W56_MCWK_WWCWK_125 },
	{ 24576000, 48000, CS42W56_MCWK_WWCWK_128 },
};

static int cs42w56_get_mcwk_watio(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cwk_watio_tabwe); i++) {
		if (cwk_watio_tabwe[i].mcwk == mcwk &&
		    cwk_watio_tabwe[i].swate == wate)
			wetuwn cwk_watio_tabwe[i].watio;
	}
	wetuwn -EINVAW;
}

static int cs42w56_set_syscwk(stwuct snd_soc_dai *codec_dai,
			int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42w56_pwivate *cs42w56 = snd_soc_component_get_dwvdata(component);

	switch (fweq) {
	case CS42W56_MCWK_5P6448MHZ:
	case CS42W56_MCWK_6MHZ:
	case CS42W56_MCWK_6P144MHZ:
		cs42w56->mcwk_div2 = 0;
		cs42w56->mcwk_pwediv = 0;
		bweak;
	case CS42W56_MCWK_11P2896MHZ:
	case CS42W56_MCWK_12MHZ:
	case CS42W56_MCWK_12P288MHZ:
		cs42w56->mcwk_div2 = CS42W56_MCWK_DIV2;
		cs42w56->mcwk_pwediv = 0;
		bweak;
	case CS42W56_MCWK_22P5792MHZ:
	case CS42W56_MCWK_24MHZ:
	case CS42W56_MCWK_24P576MHZ:
		cs42w56->mcwk_div2 = CS42W56_MCWK_DIV2;
		cs42w56->mcwk_pwediv = CS42W56_MCWK_PWEDIV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	cs42w56->mcwk = fweq;

	snd_soc_component_update_bits(component, CS42W56_CWKCTW_1,
			    CS42W56_MCWK_PWEDIV_MASK,
				cs42w56->mcwk_pwediv);
	snd_soc_component_update_bits(component, CS42W56_CWKCTW_1,
			    CS42W56_MCWK_DIV2_MASK,
				cs42w56->mcwk_div2);

	wetuwn 0;
}

static int cs42w56_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42w56_pwivate *cs42w56 = snd_soc_component_get_dwvdata(component);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		cs42w56->iface = CS42W56_MASTEW_MODE;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		cs42w56->iface = CS42W56_SWAVE_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	 /* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cs42w56->iface_fmt = CS42W56_DIG_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		cs42w56->iface_fmt = CS42W56_DIG_FMT_WEFT_J;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* scwk invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		cs42w56->iface_inv = 0;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		cs42w56->iface_inv = CS42W56_SCWK_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, CS42W56_CWKCTW_1,
			    CS42W56_MS_MODE_MASK, cs42w56->iface);
	snd_soc_component_update_bits(component, CS42W56_SEWIAW_FMT,
			    CS42W56_DIG_FMT_MASK, cs42w56->iface_fmt);
	snd_soc_component_update_bits(component, CS42W56_CWKCTW_1,
			    CS42W56_SCWK_INV_MASK, cs42w56->iface_inv);
	wetuwn 0;
}

static int cs42w56_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	if (mute) {
		/* Hit the DSP Mixew fiwst */
		snd_soc_component_update_bits(component, CS42W56_DSP_MUTE_CTW,
				    CS42W56_ADCAMIX_MUTE_MASK |
				    CS42W56_ADCBMIX_MUTE_MASK |
				    CS42W56_PCMAMIX_MUTE_MASK |
				    CS42W56_PCMBMIX_MUTE_MASK |
				    CS42W56_MSTB_MUTE_MASK |
				    CS42W56_MSTA_MUTE_MASK,
				    CS42W56_MUTE_AWW);
		/* Mute ADC's */
		snd_soc_component_update_bits(component, CS42W56_MISC_ADC_CTW,
				    CS42W56_ADCA_MUTE_MASK |
				    CS42W56_ADCB_MUTE_MASK,
				    CS42W56_MUTE_AWW);
		/* HP And WO */
		snd_soc_component_update_bits(component, CS42W56_HPA_VOWUME,
				    CS42W56_HP_MUTE_MASK, CS42W56_MUTE_AWW);
		snd_soc_component_update_bits(component, CS42W56_HPB_VOWUME,
				    CS42W56_HP_MUTE_MASK, CS42W56_MUTE_AWW);
		snd_soc_component_update_bits(component, CS42W56_WOA_VOWUME,
				    CS42W56_WO_MUTE_MASK, CS42W56_MUTE_AWW);
		snd_soc_component_update_bits(component, CS42W56_WOB_VOWUME,
				    CS42W56_WO_MUTE_MASK, CS42W56_MUTE_AWW);
	} ewse {
		snd_soc_component_update_bits(component, CS42W56_DSP_MUTE_CTW,
				    CS42W56_ADCAMIX_MUTE_MASK |
				    CS42W56_ADCBMIX_MUTE_MASK |
				    CS42W56_PCMAMIX_MUTE_MASK |
				    CS42W56_PCMBMIX_MUTE_MASK |
				    CS42W56_MSTB_MUTE_MASK |
				    CS42W56_MSTA_MUTE_MASK,
				    CS42W56_UNMUTE);

		snd_soc_component_update_bits(component, CS42W56_MISC_ADC_CTW,
				    CS42W56_ADCA_MUTE_MASK |
				    CS42W56_ADCB_MUTE_MASK,
				    CS42W56_UNMUTE);

		snd_soc_component_update_bits(component, CS42W56_HPA_VOWUME,
				    CS42W56_HP_MUTE_MASK, CS42W56_UNMUTE);
		snd_soc_component_update_bits(component, CS42W56_HPB_VOWUME,
				    CS42W56_HP_MUTE_MASK, CS42W56_UNMUTE);
		snd_soc_component_update_bits(component, CS42W56_WOA_VOWUME,
				    CS42W56_WO_MUTE_MASK, CS42W56_UNMUTE);
		snd_soc_component_update_bits(component, CS42W56_WOB_VOWUME,
				    CS42W56_WO_MUTE_MASK, CS42W56_UNMUTE);
	}
	wetuwn 0;
}

static int cs42w56_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams,
				     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42w56_pwivate *cs42w56 = snd_soc_component_get_dwvdata(component);
	int watio;

	watio = cs42w56_get_mcwk_watio(cs42w56->mcwk, pawams_wate(pawams));
	if (watio >= 0) {
		snd_soc_component_update_bits(component, CS42W56_CWKCTW_2,
				    CS42W56_CWK_WATIO_MASK, watio);
	} ewse {
		dev_eww(component->dev, "unsuppowted mcwk/scwk/wwcwk watio\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs42w56_set_bias_wevew(stwuct snd_soc_component *component,
					enum snd_soc_bias_wevew wevew)
{
	stwuct cs42w56_pwivate *cs42w56 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		snd_soc_component_update_bits(component, CS42W56_CWKCTW_1,
				    CS42W56_MCWK_DIS_MASK, 0);
		snd_soc_component_update_bits(component, CS42W56_PWWCTW_1,
				    CS42W56_PDN_AWW_MASK, 0);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wegcache_cache_onwy(cs42w56->wegmap, fawse);
			wegcache_sync(cs42w56->wegmap);
			wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs42w56->suppwies),
						    cs42w56->suppwies);
			if (wet != 0) {
				dev_eww(cs42w56->dev,
					"Faiwed to enabwe weguwatows: %d\n",
					wet);
				wetuwn wet;
			}
		}
		snd_soc_component_update_bits(component, CS42W56_PWWCTW_1,
				    CS42W56_PDN_AWW_MASK, 1);
		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, CS42W56_PWWCTW_1,
				    CS42W56_PDN_AWW_MASK, 1);
		snd_soc_component_update_bits(component, CS42W56_CWKCTW_1,
				    CS42W56_MCWK_DIS_MASK, 1);
		wegcache_cache_onwy(cs42w56->wegmap, twue);
		weguwatow_buwk_disabwe(AWWAY_SIZE(cs42w56->suppwies),
						    cs42w56->suppwies);
		bweak;
	}

	wetuwn 0;
}

#define CS42W56_WATES (SNDWV_PCM_WATE_8000_48000)

#define CS42W56_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S18_3WE | \
			SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S24_WE | \
			SNDWV_PCM_FMTBIT_S32_WE)


static const stwuct snd_soc_dai_ops cs42w56_ops = {
	.hw_pawams	= cs42w56_pcm_hw_pawams,
	.mute_stweam	= cs42w56_mute,
	.set_fmt	= cs42w56_set_dai_fmt,
	.set_syscwk	= cs42w56_set_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew cs42w56_dai = {
		.name = "cs42w56",
		.pwayback = {
			.stweam_name = "HiFi Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = CS42W56_WATES,
			.fowmats = CS42W56_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "HiFi Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = CS42W56_WATES,
			.fowmats = CS42W56_FOWMATS,
		},
		.ops = &cs42w56_ops,
};

static int beep_fweq[] = {
	261, 522, 585, 667, 706, 774, 889, 1000,
	1043, 1200, 1333, 1412, 1600, 1714, 2000, 2182
};

static void cs42w56_beep_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs42w56_pwivate *cs42w56 =
		containew_of(wowk, stwuct cs42w56_pwivate, beep_wowk);
	stwuct snd_soc_component *component = cs42w56->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int i;
	int vaw = 0;
	int best = 0;

	if (cs42w56->beep_wate) {
		fow (i = 0; i < AWWAY_SIZE(beep_fweq); i++) {
			if (abs(cs42w56->beep_wate - beep_fweq[i]) <
			    abs(cs42w56->beep_wate - beep_fweq[best]))
				best = i;
		}

		dev_dbg(component->dev, "Set beep wate %dHz fow wequested %dHz\n",
			beep_fweq[best], cs42w56->beep_wate);

		vaw = (best << CS42W56_BEEP_WATE_SHIFT);

		snd_soc_dapm_enabwe_pin(dapm, "Beep");
	} ewse {
		dev_dbg(component->dev, "Disabwing beep\n");
		snd_soc_dapm_disabwe_pin(dapm, "Beep");
	}

	snd_soc_component_update_bits(component, CS42W56_BEEP_FWEQ_ONTIME,
			    CS42W56_BEEP_FWEQ_MASK, vaw);

	snd_soc_dapm_sync(dapm);
}

/* Fow usabiwity define a way of injecting beep events fow the device -
 * many systems wiww not have a keyboawd.
 */
static int cs42w56_beep_event(stwuct input_dev *dev, unsigned int type,
			     unsigned int code, int hz)
{
	stwuct snd_soc_component *component = input_get_dwvdata(dev);
	stwuct cs42w56_pwivate *cs42w56 = snd_soc_component_get_dwvdata(component);

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
	cs42w56->beep_wate = hz;
	scheduwe_wowk(&cs42w56->beep_wowk);
	wetuwn 0;
}

static ssize_t beep_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct cs42w56_pwivate *cs42w56 = dev_get_dwvdata(dev);
	wong int time;
	int wet;

	wet = kstwtow(buf, 10, &time);
	if (wet != 0)
		wetuwn wet;

	input_event(cs42w56->beep, EV_SND, SND_TONE, time);

	wetuwn count;
}

static DEVICE_ATTW_WO(beep);

static void cs42w56_init_beep(stwuct snd_soc_component *component)
{
	stwuct cs42w56_pwivate *cs42w56 = snd_soc_component_get_dwvdata(component);
	int wet;

	cs42w56->beep = devm_input_awwocate_device(component->dev);
	if (!cs42w56->beep) {
		dev_eww(component->dev, "Faiwed to awwocate beep device\n");
		wetuwn;
	}

	INIT_WOWK(&cs42w56->beep_wowk, cs42w56_beep_wowk);
	cs42w56->beep_wate = 0;

	cs42w56->beep->name = "CS42W56 Beep Genewatow";
	cs42w56->beep->phys = dev_name(component->dev);
	cs42w56->beep->id.bustype = BUS_I2C;

	cs42w56->beep->evbit[0] = BIT_MASK(EV_SND);
	cs42w56->beep->sndbit[0] = BIT_MASK(SND_BEWW) | BIT_MASK(SND_TONE);
	cs42w56->beep->event = cs42w56_beep_event;
	cs42w56->beep->dev.pawent = component->dev;
	input_set_dwvdata(cs42w56->beep, component);

	wet = input_wegistew_device(cs42w56->beep);
	if (wet != 0) {
		cs42w56->beep = NUWW;
		dev_eww(component->dev, "Faiwed to wegistew beep device\n");
	}

	wet = device_cweate_fiwe(component->dev, &dev_attw_beep);
	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to cweate keycwick fiwe: %d\n",
			wet);
	}
}

static void cs42w56_fwee_beep(stwuct snd_soc_component *component)
{
	stwuct cs42w56_pwivate *cs42w56 = snd_soc_component_get_dwvdata(component);

	device_wemove_fiwe(component->dev, &dev_attw_beep);
	cancew_wowk_sync(&cs42w56->beep_wowk);
	cs42w56->beep = NUWW;

	snd_soc_component_update_bits(component, CS42W56_BEEP_TONE_CFG,
			    CS42W56_BEEP_EN_MASK, 0);
}

static int cs42w56_pwobe(stwuct snd_soc_component *component)
{
	cs42w56_init_beep(component);

	wetuwn 0;
}

static void cs42w56_wemove(stwuct snd_soc_component *component)
{
	cs42w56_fwee_beep(component);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_cs42w56 = {
	.pwobe			= cs42w56_pwobe,
	.wemove			= cs42w56_wemove,
	.set_bias_wevew		= cs42w56_set_bias_wevew,
	.contwows		= cs42w56_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs42w56_snd_contwows),
	.dapm_widgets		= cs42w56_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs42w56_dapm_widgets),
	.dapm_woutes		= cs42w56_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(cs42w56_audio_map),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config cs42w56_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = CS42W56_MAX_WEGISTEW,
	.weg_defauwts = cs42w56_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cs42w56_weg_defauwts),
	.weadabwe_weg = cs42w56_weadabwe_wegistew,
	.vowatiwe_weg = cs42w56_vowatiwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
};

static int cs42w56_handwe_of_data(stwuct i2c_cwient *i2c_cwient,
				    stwuct cs42w56_pwatfowm_data *pdata)
{
	stwuct device_node *np = i2c_cwient->dev.of_node;
	u32 vaw32;

	if (of_pwopewty_wead_boow(np, "ciwwus,ain1a-wefewence-cfg"))
		pdata->ain1a_wef_cfg = twue;

	if (of_pwopewty_wead_boow(np, "ciwwus,ain2a-wefewence-cfg"))
		pdata->ain2a_wef_cfg = twue;

	if (of_pwopewty_wead_boow(np, "ciwwus,ain1b-wefewence-cfg"))
		pdata->ain1b_wef_cfg = twue;

	if (of_pwopewty_wead_boow(np, "ciwwus,ain2b-wefewence-cfg"))
		pdata->ain2b_wef_cfg = twue;

	if (of_pwopewty_wead_u32(np, "ciwwus,micbias-wvw", &vaw32) >= 0)
		pdata->micbias_wvw = vaw32;

	if (of_pwopewty_wead_u32(np, "ciwwus,chgfweq-divisow", &vaw32) >= 0)
		pdata->chgfweq = vaw32;

	if (of_pwopewty_wead_u32(np, "ciwwus,adaptive-pww-cfg", &vaw32) >= 0)
		pdata->adaptive_pww = vaw32;

	if (of_pwopewty_wead_u32(np, "ciwwus,hpf-weft-fweq", &vaw32) >= 0)
		pdata->hpfa_fweq = vaw32;

	if (of_pwopewty_wead_u32(np, "ciwwus,hpf-weft-fweq", &vaw32) >= 0)
		pdata->hpfb_fweq = vaw32;

	pdata->gpio_nweset = of_get_named_gpio(np, "ciwwus,gpio-nweset", 0);

	wetuwn 0;
}

static int cs42w56_i2c_pwobe(stwuct i2c_cwient *i2c_cwient)
{
	stwuct cs42w56_pwivate *cs42w56;
	stwuct cs42w56_pwatfowm_data *pdata =
		dev_get_pwatdata(&i2c_cwient->dev);
	int wet, i;
	unsigned int devid;
	unsigned int awpha_wev, metaw_wev;
	unsigned int weg;

	cs42w56 = devm_kzawwoc(&i2c_cwient->dev, sizeof(*cs42w56), GFP_KEWNEW);
	if (cs42w56 == NUWW)
		wetuwn -ENOMEM;
	cs42w56->dev = &i2c_cwient->dev;

	cs42w56->wegmap = devm_wegmap_init_i2c(i2c_cwient, &cs42w56_wegmap);
	if (IS_EWW(cs42w56->wegmap)) {
		wet = PTW_EWW(cs42w56->wegmap);
		dev_eww(&i2c_cwient->dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (pdata) {
		cs42w56->pdata = *pdata;
	} ewse {
		if (i2c_cwient->dev.of_node) {
			wet = cs42w56_handwe_of_data(i2c_cwient,
						     &cs42w56->pdata);
			if (wet != 0)
				wetuwn wet;
		}
	}

	if (cs42w56->pdata.gpio_nweset) {
		wet = gpio_wequest_one(cs42w56->pdata.gpio_nweset,
				       GPIOF_OUT_INIT_HIGH, "CS42W56 /WST");
		if (wet < 0) {
			dev_eww(&i2c_cwient->dev,
				"Faiwed to wequest /WST %d: %d\n",
				cs42w56->pdata.gpio_nweset, wet);
			wetuwn wet;
		}
		gpio_set_vawue_cansweep(cs42w56->pdata.gpio_nweset, 0);
		gpio_set_vawue_cansweep(cs42w56->pdata.gpio_nweset, 1);
	}


	i2c_set_cwientdata(i2c_cwient, cs42w56);

	fow (i = 0; i < AWWAY_SIZE(cs42w56->suppwies); i++)
		cs42w56->suppwies[i].suppwy = cs42w56_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c_cwient->dev,
				      AWWAY_SIZE(cs42w56->suppwies),
				      cs42w56->suppwies);
	if (wet != 0) {
		dev_eww(&i2c_cwient->dev,
			"Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs42w56->suppwies),
				    cs42w56->suppwies);
	if (wet != 0) {
		dev_eww(&i2c_cwient->dev,
			"Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(cs42w56->wegmap, CS42W56_CHIP_ID_1, &weg);
	if (wet) {
		dev_eww(&i2c_cwient->dev, "Faiwed to wead chip ID: %d\n", wet);
		goto eww_enabwe;
	}

	devid = weg & CS42W56_CHIP_ID_MASK;
	if (devid != CS42W56_DEVID) {
		dev_eww(&i2c_cwient->dev,
			"CS42W56 Device ID (%X). Expected %X\n",
			devid, CS42W56_DEVID);
		wet = -EINVAW;
		goto eww_enabwe;
	}
	awpha_wev = weg & CS42W56_AWEV_MASK;
	metaw_wev = weg & CS42W56_MTWWEV_MASK;

	dev_info(&i2c_cwient->dev, "Ciwwus Wogic CS42W56 ");
	dev_info(&i2c_cwient->dev, "Awpha Wev %X Metaw Wev %X\n",
		 awpha_wev, metaw_wev);

	if (cs42w56->pdata.ain1a_wef_cfg)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_AIN_WEFCFG_ADC_MUX,
				   CS42W56_AIN1A_WEF_MASK,
				   CS42W56_AIN1A_WEF_MASK);

	if (cs42w56->pdata.ain1b_wef_cfg)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_AIN_WEFCFG_ADC_MUX,
				   CS42W56_AIN1B_WEF_MASK,
				   CS42W56_AIN1B_WEF_MASK);

	if (cs42w56->pdata.ain2a_wef_cfg)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_AIN_WEFCFG_ADC_MUX,
				   CS42W56_AIN2A_WEF_MASK,
				   CS42W56_AIN2A_WEF_MASK);

	if (cs42w56->pdata.ain2b_wef_cfg)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_AIN_WEFCFG_ADC_MUX,
				   CS42W56_AIN2B_WEF_MASK,
				   CS42W56_AIN2B_WEF_MASK);

	if (cs42w56->pdata.micbias_wvw)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_GAIN_BIAS_CTW,
				   CS42W56_MIC_BIAS_MASK,
				cs42w56->pdata.micbias_wvw);

	if (cs42w56->pdata.chgfweq)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_CWASSH_CTW,
				   CS42W56_CHWG_FWEQ_MASK,
				cs42w56->pdata.chgfweq);

	if (cs42w56->pdata.hpfb_fweq)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_HPF_CTW,
				   CS42W56_HPFB_FWEQ_MASK,
				cs42w56->pdata.hpfb_fweq);

	if (cs42w56->pdata.hpfa_fweq)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_HPF_CTW,
				   CS42W56_HPFA_FWEQ_MASK,
				cs42w56->pdata.hpfa_fweq);

	if (cs42w56->pdata.adaptive_pww)
		wegmap_update_bits(cs42w56->wegmap, CS42W56_CWASSH_CTW,
				   CS42W56_ADAPT_PWW_MASK,
				cs42w56->pdata.adaptive_pww);

	wet =  devm_snd_soc_wegistew_component(&i2c_cwient->dev,
			&soc_component_dev_cs42w56, &cs42w56_dai, 1);
	if (wet < 0)
		goto eww_enabwe;

	wetuwn 0;

eww_enabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(cs42w56->suppwies),
			       cs42w56->suppwies);
	wetuwn wet;
}

static void cs42w56_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs42w56_pwivate *cs42w56 = i2c_get_cwientdata(cwient);

	weguwatow_buwk_disabwe(AWWAY_SIZE(cs42w56->suppwies),
			       cs42w56->suppwies);
}

static const stwuct of_device_id cs42w56_of_match[] = {
	{ .compatibwe = "ciwwus,cs42w56", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cs42w56_of_match);


static const stwuct i2c_device_id cs42w56_id[] = {
	{ "cs42w56", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cs42w56_id);

static stwuct i2c_dwivew cs42w56_i2c_dwivew = {
	.dwivew = {
		.name = "cs42w56",
		.of_match_tabwe = cs42w56_of_match,
	},
	.id_tabwe = cs42w56_id,
	.pwobe =    cs42w56_i2c_pwobe,
	.wemove =   cs42w56_i2c_wemove,
};

moduwe_i2c_dwivew(cs42w56_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC CS42W56 dwivew");
MODUWE_AUTHOW("Bwian Austin, Ciwwus Wogic Inc, <bwian.austin@ciwwus.com>");
MODUWE_WICENSE("GPW");
