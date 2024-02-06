// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8985.c  --  WM8985 / WM8758 AWSA SoC Audio dwivew
 *
 * Copywight 2010 Wowfson Micwoewectwonics pwc
 * Authow: Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>
 *
 * WM8758 suppowt:
 * Copywight: 2016 Bawix AG
 * Authow: Petw Kuwhavy <petw@bawix.com>
 *
 * TODO:
 *  o Add OUT3/OUT4 mixew contwows.
 */

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
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wm8985.h"

#define WM8985_NUM_SUPPWIES 4
static const chaw *wm8985_suppwy_names[WM8985_NUM_SUPPWIES] = {
	"DCVDD",
	"DBVDD",
	"AVDD1",
	"AVDD2"
};

enum wm8985_type {
	WM8985,
	WM8758,
};

static const stwuct weg_defauwt wm8985_weg_defauwts[] = {
	{ 1,  0x0000 },     /* W1  - Powew management 1 */
	{ 2,  0x0000 },     /* W2  - Powew management 2 */
	{ 3,  0x0000 },     /* W3  - Powew management 3 */
	{ 4,  0x0050 },     /* W4  - Audio Intewface */
	{ 5,  0x0000 },     /* W5  - Companding contwow */
	{ 6,  0x0140 },     /* W6  - Cwock Gen contwow */
	{ 7,  0x0000 },     /* W7  - Additionaw contwow */
	{ 8,  0x0000 },     /* W8  - GPIO Contwow */
	{ 9,  0x0000 },     /* W9  - Jack Detect Contwow 1 */
	{ 10, 0x0000 },     /* W10 - DAC Contwow */
	{ 11, 0x00FF },     /* W11 - Weft DAC digitaw Vow */
	{ 12, 0x00FF },     /* W12 - Wight DAC digitaw vow */
	{ 13, 0x0000 },     /* W13 - Jack Detect Contwow 2 */
	{ 14, 0x0100 },     /* W14 - ADC Contwow */
	{ 15, 0x00FF },     /* W15 - Weft ADC Digitaw Vow */
	{ 16, 0x00FF },     /* W16 - Wight ADC Digitaw Vow */
	{ 18, 0x012C },     /* W18 - EQ1 - wow shewf */
	{ 19, 0x002C },     /* W19 - EQ2 - peak 1 */
	{ 20, 0x002C },     /* W20 - EQ3 - peak 2 */
	{ 21, 0x002C },     /* W21 - EQ4 - peak 3 */
	{ 22, 0x002C },     /* W22 - EQ5 - high shewf */
	{ 24, 0x0032 },     /* W24 - DAC Wimitew 1 */
	{ 25, 0x0000 },     /* W25 - DAC Wimitew 2 */
	{ 27, 0x0000 },     /* W27 - Notch Fiwtew 1 */
	{ 28, 0x0000 },     /* W28 - Notch Fiwtew 2 */
	{ 29, 0x0000 },     /* W29 - Notch Fiwtew 3 */
	{ 30, 0x0000 },     /* W30 - Notch Fiwtew 4 */
	{ 32, 0x0038 },     /* W32 - AWC contwow 1 */
	{ 33, 0x000B },     /* W33 - AWC contwow 2 */
	{ 34, 0x0032 },     /* W34 - AWC contwow 3 */
	{ 35, 0x0000 },     /* W35 - Noise Gate */
	{ 36, 0x0008 },     /* W36 - PWW N */
	{ 37, 0x000C },     /* W37 - PWW K 1 */
	{ 38, 0x0093 },     /* W38 - PWW K 2 */
	{ 39, 0x00E9 },     /* W39 - PWW K 3 */
	{ 41, 0x0000 },     /* W41 - 3D contwow */
	{ 42, 0x0000 },     /* W42 - OUT4 to ADC */
	{ 43, 0x0000 },     /* W43 - Beep contwow */
	{ 44, 0x0033 },     /* W44 - Input ctww */
	{ 45, 0x0010 },     /* W45 - Weft INP PGA gain ctww */
	{ 46, 0x0010 },     /* W46 - Wight INP PGA gain ctww */
	{ 47, 0x0100 },     /* W47 - Weft ADC BOOST ctww */
	{ 48, 0x0100 },     /* W48 - Wight ADC BOOST ctww */
	{ 49, 0x0002 },     /* W49 - Output ctww */
	{ 50, 0x0001 },     /* W50 - Weft mixew ctww */
	{ 51, 0x0001 },     /* W51 - Wight mixew ctww */
	{ 52, 0x0039 },     /* W52 - WOUT1 (HP) vowume ctww */
	{ 53, 0x0039 },     /* W53 - WOUT1 (HP) vowume ctww */
	{ 54, 0x0039 },     /* W54 - WOUT2 (SPK) vowume ctww */
	{ 55, 0x0039 },     /* W55 - WOUT2 (SPK) vowume ctww */
	{ 56, 0x0001 },     /* W56 - OUT3 mixew ctww */
	{ 57, 0x0001 },     /* W57 - OUT4 (MONO) mix ctww */
	{ 60, 0x0004 },     /* W60 - OUTPUT ctww */
	{ 61, 0x0000 },     /* W61 - BIAS CTWW */
};

static boow wm8985_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8985_SOFTWAWE_WESET:
	case WM8985_POWEW_MANAGEMENT_1:
	case WM8985_POWEW_MANAGEMENT_2:
	case WM8985_POWEW_MANAGEMENT_3:
	case WM8985_AUDIO_INTEWFACE:
	case WM8985_COMPANDING_CONTWOW:
	case WM8985_CWOCK_GEN_CONTWOW:
	case WM8985_ADDITIONAW_CONTWOW:
	case WM8985_GPIO_CONTWOW:
	case WM8985_JACK_DETECT_CONTWOW_1:
	case WM8985_DAC_CONTWOW:
	case WM8985_WEFT_DAC_DIGITAW_VOW:
	case WM8985_WIGHT_DAC_DIGITAW_VOW:
	case WM8985_JACK_DETECT_CONTWOW_2:
	case WM8985_ADC_CONTWOW:
	case WM8985_WEFT_ADC_DIGITAW_VOW:
	case WM8985_WIGHT_ADC_DIGITAW_VOW:
	case WM8985_EQ1_WOW_SHEWF:
	case WM8985_EQ2_PEAK_1:
	case WM8985_EQ3_PEAK_2:
	case WM8985_EQ4_PEAK_3:
	case WM8985_EQ5_HIGH_SHEWF:
	case WM8985_DAC_WIMITEW_1:
	case WM8985_DAC_WIMITEW_2:
	case WM8985_NOTCH_FIWTEW_1:
	case WM8985_NOTCH_FIWTEW_2:
	case WM8985_NOTCH_FIWTEW_3:
	case WM8985_NOTCH_FIWTEW_4:
	case WM8985_AWC_CONTWOW_1:
	case WM8985_AWC_CONTWOW_2:
	case WM8985_AWC_CONTWOW_3:
	case WM8985_NOISE_GATE:
	case WM8985_PWW_N:
	case WM8985_PWW_K_1:
	case WM8985_PWW_K_2:
	case WM8985_PWW_K_3:
	case WM8985_3D_CONTWOW:
	case WM8985_OUT4_TO_ADC:
	case WM8985_BEEP_CONTWOW:
	case WM8985_INPUT_CTWW:
	case WM8985_WEFT_INP_PGA_GAIN_CTWW:
	case WM8985_WIGHT_INP_PGA_GAIN_CTWW:
	case WM8985_WEFT_ADC_BOOST_CTWW:
	case WM8985_WIGHT_ADC_BOOST_CTWW:
	case WM8985_OUTPUT_CTWW0:
	case WM8985_WEFT_MIXEW_CTWW:
	case WM8985_WIGHT_MIXEW_CTWW:
	case WM8985_WOUT1_HP_VOWUME_CTWW:
	case WM8985_WOUT1_HP_VOWUME_CTWW:
	case WM8985_WOUT2_SPK_VOWUME_CTWW:
	case WM8985_WOUT2_SPK_VOWUME_CTWW:
	case WM8985_OUT3_MIXEW_CTWW:
	case WM8985_OUT4_MONO_MIX_CTWW:
	case WM8985_OUTPUT_CTWW1:
	case WM8985_BIAS_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * watch bit 8 of these wegistews to ensuwe instant
 * vowume updates
 */
static const int vowume_update_wegs[] = {
	WM8985_WEFT_DAC_DIGITAW_VOW,
	WM8985_WIGHT_DAC_DIGITAW_VOW,
	WM8985_WEFT_ADC_DIGITAW_VOW,
	WM8985_WIGHT_ADC_DIGITAW_VOW,
	WM8985_WOUT2_SPK_VOWUME_CTWW,
	WM8985_WOUT2_SPK_VOWUME_CTWW,
	WM8985_WOUT1_HP_VOWUME_CTWW,
	WM8985_WOUT1_HP_VOWUME_CTWW,
	WM8985_WEFT_INP_PGA_GAIN_CTWW,
	WM8985_WIGHT_INP_PGA_GAIN_CTWW
};

stwuct wm8985_pwiv {
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[WM8985_NUM_SUPPWIES];
	enum wm8985_type dev_type;
	unsigned int syscwk;
	unsigned int bcwk;
};

static const stwuct {
	int div;
	int watio;
} fs_watios[] = {
	{ 10, 128 },
	{ 15, 192 },
	{ 20, 256 },
	{ 30, 384 },
	{ 40, 512 },
	{ 60, 768 },
	{ 80, 1024 },
	{ 120, 1536 }
};

static const int swates[] = { 48000, 32000, 24000, 16000, 12000, 8000 };

static const int bcwk_divs[] = {
	1, 2, 4, 8, 16, 32
};

static int eqmode_get(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow);
static int eqmode_put(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow);

static const DECWAWE_TWV_DB_SCAWE(dac_twv, -12700, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -12700, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(out_twv, -5700, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(wim_thwesh_twv, -600, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(wim_boost_twv, 0, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_min_twv, -1200, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_max_twv, -675, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_taw_twv, -2250, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(pga_vow_twv, -1200, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(boost_twv, -1200, 300, 1);
static const DECWAWE_TWV_DB_SCAWE(eq_twv, -1200, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(aux_twv, -1500, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(bypass_twv, -1500, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(pga_boost_twv, 0, 2000, 0);

static const chaw *awc_sew_text[] = { "Off", "Wight", "Weft", "Steweo" };
static SOC_ENUM_SINGWE_DECW(awc_sew, WM8985_AWC_CONTWOW_1, 7, awc_sew_text);

static const chaw *awc_mode_text[] = { "AWC", "Wimitew" };
static SOC_ENUM_SINGWE_DECW(awc_mode, WM8985_AWC_CONTWOW_3, 8, awc_mode_text);

static const chaw *fiwtew_mode_text[] = { "Audio", "Appwication" };
static SOC_ENUM_SINGWE_DECW(fiwtew_mode, WM8985_ADC_CONTWOW, 7,
			    fiwtew_mode_text);

static const chaw *eq_bw_text[] = { "Nawwow", "Wide" };
static const chaw *eqmode_text[] = { "Captuwe", "Pwayback" };
static SOC_ENUM_SINGWE_EXT_DECW(eqmode, eqmode_text);

static const chaw *eq1_cutoff_text[] = {
	"80Hz", "105Hz", "135Hz", "175Hz"
};
static SOC_ENUM_SINGWE_DECW(eq1_cutoff, WM8985_EQ1_WOW_SHEWF, 5,
			    eq1_cutoff_text);
static const chaw *eq2_cutoff_text[] = {
	"230Hz", "300Hz", "385Hz", "500Hz"
};
static SOC_ENUM_SINGWE_DECW(eq2_bw, WM8985_EQ2_PEAK_1, 8, eq_bw_text);
static SOC_ENUM_SINGWE_DECW(eq2_cutoff, WM8985_EQ2_PEAK_1, 5, eq2_cutoff_text);
static const chaw *eq3_cutoff_text[] = {
	"650Hz", "850Hz", "1.1kHz", "1.4kHz"
};
static SOC_ENUM_SINGWE_DECW(eq3_bw, WM8985_EQ3_PEAK_2, 8, eq_bw_text);
static SOC_ENUM_SINGWE_DECW(eq3_cutoff, WM8985_EQ3_PEAK_2, 5,
			    eq3_cutoff_text);
static const chaw *eq4_cutoff_text[] = {
	"1.8kHz", "2.4kHz", "3.2kHz", "4.1kHz"
};
static SOC_ENUM_SINGWE_DECW(eq4_bw, WM8985_EQ4_PEAK_3, 8, eq_bw_text);
static SOC_ENUM_SINGWE_DECW(eq4_cutoff, WM8985_EQ4_PEAK_3, 5, eq4_cutoff_text);
static const chaw *eq5_cutoff_text[] = {
	"5.3kHz", "6.9kHz", "9kHz", "11.7kHz"
};
static SOC_ENUM_SINGWE_DECW(eq5_cutoff, WM8985_EQ5_HIGH_SHEWF, 5,
				  eq5_cutoff_text);

static const chaw *speakew_mode_text[] = { "Cwass A/B", "Cwass D" };
static SOC_ENUM_SINGWE_DECW(speakew_mode, 0x17, 8, speakew_mode_text);

static const chaw *depth_3d_text[] = {
	"Off",
	"6.67%",
	"13.3%",
	"20%",
	"26.7%",
	"33.3%",
	"40%",
	"46.6%",
	"53.3%",
	"60%",
	"66.7%",
	"73.3%",
	"80%",
	"86.7%",
	"93.3%",
	"100%"
};
static SOC_ENUM_SINGWE_DECW(depth_3d, WM8985_3D_CONTWOW, 0, depth_3d_text);

static const stwuct snd_kcontwow_new wm8985_common_snd_contwows[] = {
	SOC_SINGWE("Digitaw Woopback Switch", WM8985_COMPANDING_CONTWOW,
		0, 1, 0),

	SOC_ENUM("AWC Captuwe Function", awc_sew),
	SOC_SINGWE_TWV("AWC Captuwe Max Vowume", WM8985_AWC_CONTWOW_1,
		3, 7, 0, awc_max_twv),
	SOC_SINGWE_TWV("AWC Captuwe Min Vowume", WM8985_AWC_CONTWOW_1,
		0, 7, 0, awc_min_twv),
	SOC_SINGWE_TWV("AWC Captuwe Tawget Vowume", WM8985_AWC_CONTWOW_2,
		0, 15, 0, awc_taw_twv),
	SOC_SINGWE("AWC Captuwe Attack", WM8985_AWC_CONTWOW_3, 0, 10, 0),
	SOC_SINGWE("AWC Captuwe Howd", WM8985_AWC_CONTWOW_2, 4, 10, 0),
	SOC_SINGWE("AWC Captuwe Decay", WM8985_AWC_CONTWOW_3, 4, 10, 0),
	SOC_ENUM("AWC Mode", awc_mode),
	SOC_SINGWE("AWC Captuwe NG Switch", WM8985_NOISE_GATE,
		3, 1, 0),
	SOC_SINGWE("AWC Captuwe NG Thweshowd", WM8985_NOISE_GATE,
		0, 7, 1),

	SOC_DOUBWE_W_TWV("Captuwe Vowume", WM8985_WEFT_ADC_DIGITAW_VOW,
		WM8985_WIGHT_ADC_DIGITAW_VOW, 0, 255, 0, adc_twv),
	SOC_DOUBWE_W("Captuwe PGA ZC Switch", WM8985_WEFT_INP_PGA_GAIN_CTWW,
		WM8985_WIGHT_INP_PGA_GAIN_CTWW, 7, 1, 0),
	SOC_DOUBWE_W_TWV("Captuwe PGA Vowume", WM8985_WEFT_INP_PGA_GAIN_CTWW,
		WM8985_WIGHT_INP_PGA_GAIN_CTWW, 0, 63, 0, pga_vow_twv),

	SOC_DOUBWE_W_TWV("Captuwe PGA Boost Vowume",
		WM8985_WEFT_ADC_BOOST_CTWW, WM8985_WIGHT_ADC_BOOST_CTWW,
		8, 1, 0, pga_boost_twv),

	SOC_DOUBWE("ADC Invewsion Switch", WM8985_ADC_CONTWOW, 0, 1, 1, 0),
	SOC_SINGWE("ADC 128x Ovewsampwing Switch", WM8985_ADC_CONTWOW, 8, 1, 0),

	SOC_DOUBWE_W_TWV("Pwayback Vowume", WM8985_WEFT_DAC_DIGITAW_VOW,
		WM8985_WIGHT_DAC_DIGITAW_VOW, 0, 255, 0, dac_twv),

	SOC_SINGWE("DAC Pwayback Wimitew Switch", WM8985_DAC_WIMITEW_1, 8, 1, 0),
	SOC_SINGWE("DAC Pwayback Wimitew Decay", WM8985_DAC_WIMITEW_1, 4, 10, 0),
	SOC_SINGWE("DAC Pwayback Wimitew Attack", WM8985_DAC_WIMITEW_1, 0, 11, 0),
	SOC_SINGWE_TWV("DAC Pwayback Wimitew Thweshowd", WM8985_DAC_WIMITEW_2,
		4, 7, 1, wim_thwesh_twv),
	SOC_SINGWE_TWV("DAC Pwayback Wimitew Boost Vowume", WM8985_DAC_WIMITEW_2,
		0, 12, 0, wim_boost_twv),
	SOC_DOUBWE("DAC Invewsion Switch", WM8985_DAC_CONTWOW, 0, 1, 1, 0),
	SOC_SINGWE("DAC Auto Mute Switch", WM8985_DAC_CONTWOW, 2, 1, 0),
	SOC_SINGWE("DAC 128x Ovewsampwing Switch", WM8985_DAC_CONTWOW, 3, 1, 0),

	SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", WM8985_WOUT1_HP_VOWUME_CTWW,
		WM8985_WOUT1_HP_VOWUME_CTWW, 0, 63, 0, out_twv),
	SOC_DOUBWE_W("Headphone Pwayback ZC Switch", WM8985_WOUT1_HP_VOWUME_CTWW,
		WM8985_WOUT1_HP_VOWUME_CTWW, 7, 1, 0),
	SOC_DOUBWE_W("Headphone Switch", WM8985_WOUT1_HP_VOWUME_CTWW,
		WM8985_WOUT1_HP_VOWUME_CTWW, 6, 1, 1),

	SOC_DOUBWE_W_TWV("Speakew Pwayback Vowume", WM8985_WOUT2_SPK_VOWUME_CTWW,
		WM8985_WOUT2_SPK_VOWUME_CTWW, 0, 63, 0, out_twv),
	SOC_DOUBWE_W("Speakew Pwayback ZC Switch", WM8985_WOUT2_SPK_VOWUME_CTWW,
		WM8985_WOUT2_SPK_VOWUME_CTWW, 7, 1, 0),
	SOC_DOUBWE_W("Speakew Switch", WM8985_WOUT2_SPK_VOWUME_CTWW,
		WM8985_WOUT2_SPK_VOWUME_CTWW, 6, 1, 1),

	SOC_SINGWE("High Pass Fiwtew Switch", WM8985_ADC_CONTWOW, 8, 1, 0),
	SOC_ENUM("High Pass Fiwtew Mode", fiwtew_mode),
	SOC_SINGWE("High Pass Fiwtew Cutoff", WM8985_ADC_CONTWOW, 4, 7, 0),

	SOC_DOUBWE_W_TWV("Input PGA Bypass Vowume",
		WM8985_WEFT_MIXEW_CTWW, WM8985_WIGHT_MIXEW_CTWW, 2, 7, 0,
		bypass_twv),

	SOC_ENUM_EXT("Equawizew Function", eqmode, eqmode_get, eqmode_put),
	SOC_ENUM("EQ1 Cutoff", eq1_cutoff),
	SOC_SINGWE_TWV("EQ1 Vowume", WM8985_EQ1_WOW_SHEWF,  0, 24, 1, eq_twv),
	SOC_ENUM("EQ2 Bandwidth", eq2_bw),
	SOC_ENUM("EQ2 Cutoff", eq2_cutoff),
	SOC_SINGWE_TWV("EQ2 Vowume", WM8985_EQ2_PEAK_1, 0, 24, 1, eq_twv),
	SOC_ENUM("EQ3 Bandwidth", eq3_bw),
	SOC_ENUM("EQ3 Cutoff", eq3_cutoff),
	SOC_SINGWE_TWV("EQ3 Vowume", WM8985_EQ3_PEAK_2, 0, 24, 1, eq_twv),
	SOC_ENUM("EQ4 Bandwidth", eq4_bw),
	SOC_ENUM("EQ4 Cutoff", eq4_cutoff),
	SOC_SINGWE_TWV("EQ4 Vowume", WM8985_EQ4_PEAK_3, 0, 24, 1, eq_twv),
	SOC_ENUM("EQ5 Cutoff", eq5_cutoff),
	SOC_SINGWE_TWV("EQ5 Vowume", WM8985_EQ5_HIGH_SHEWF, 0, 24, 1, eq_twv),

	SOC_ENUM("3D Depth", depth_3d),
};

static const stwuct snd_kcontwow_new wm8985_specific_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Aux Bypass Vowume",
		WM8985_WEFT_MIXEW_CTWW, WM8985_WIGHT_MIXEW_CTWW, 6, 7, 0,
		aux_twv),

	SOC_ENUM("Speakew Mode", speakew_mode)
};

static const stwuct snd_kcontwow_new weft_out_mixew[] = {
	SOC_DAPM_SINGWE("Wine Switch", WM8985_WEFT_MIXEW_CTWW, 1, 1, 0),
	SOC_DAPM_SINGWE("PCM Switch", WM8985_WEFT_MIXEW_CTWW, 0, 1, 0),

	/* --- WM8985 onwy --- */
	SOC_DAPM_SINGWE("Aux Switch", WM8985_WEFT_MIXEW_CTWW, 5, 1, 0),
};

static const stwuct snd_kcontwow_new wight_out_mixew[] = {
	SOC_DAPM_SINGWE("Wine Switch", WM8985_WIGHT_MIXEW_CTWW, 1, 1, 0),
	SOC_DAPM_SINGWE("PCM Switch", WM8985_WIGHT_MIXEW_CTWW, 0, 1, 0),

	/* --- WM8985 onwy --- */
	SOC_DAPM_SINGWE("Aux Switch", WM8985_WIGHT_MIXEW_CTWW, 5, 1, 0),
};

static const stwuct snd_kcontwow_new weft_input_mixew[] = {
	SOC_DAPM_SINGWE("W2 Switch", WM8985_INPUT_CTWW, 2, 1, 0),
	SOC_DAPM_SINGWE("MicN Switch", WM8985_INPUT_CTWW, 1, 1, 0),
	SOC_DAPM_SINGWE("MicP Switch", WM8985_INPUT_CTWW, 0, 1, 0),
};

static const stwuct snd_kcontwow_new wight_input_mixew[] = {
	SOC_DAPM_SINGWE("W2 Switch", WM8985_INPUT_CTWW, 6, 1, 0),
	SOC_DAPM_SINGWE("MicN Switch", WM8985_INPUT_CTWW, 5, 1, 0),
	SOC_DAPM_SINGWE("MicP Switch", WM8985_INPUT_CTWW, 4, 1, 0),
};

static const stwuct snd_kcontwow_new weft_boost_mixew[] = {
	SOC_DAPM_SINGWE_TWV("W2 Vowume", WM8985_WEFT_ADC_BOOST_CTWW,
		4, 7, 0, boost_twv),

	/* --- WM8985 onwy --- */
	SOC_DAPM_SINGWE_TWV("AUXW Vowume", WM8985_WEFT_ADC_BOOST_CTWW,
		0, 7, 0, boost_twv)
};

static const stwuct snd_kcontwow_new wight_boost_mixew[] = {
	SOC_DAPM_SINGWE_TWV("W2 Vowume", WM8985_WIGHT_ADC_BOOST_CTWW,
		4, 7, 0, boost_twv),

	/* --- WM8985 onwy --- */
	SOC_DAPM_SINGWE_TWV("AUXW Vowume", WM8985_WIGHT_ADC_BOOST_CTWW,
		0, 7, 0, boost_twv)
};

static const stwuct snd_soc_dapm_widget wm8985_common_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback", WM8985_POWEW_MANAGEMENT_3,
		0, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback", WM8985_POWEW_MANAGEMENT_3,
		1, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", WM8985_POWEW_MANAGEMENT_2,
		0, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", WM8985_POWEW_MANAGEMENT_2,
		1, 0),

	SND_SOC_DAPM_MIXEW("Weft Input Mixew", WM8985_POWEW_MANAGEMENT_2,
		2, 0, weft_input_mixew, AWWAY_SIZE(weft_input_mixew)),
	SND_SOC_DAPM_MIXEW("Wight Input Mixew", WM8985_POWEW_MANAGEMENT_2,
		3, 0, wight_input_mixew, AWWAY_SIZE(wight_input_mixew)),

	SND_SOC_DAPM_PGA("Weft Captuwe PGA", WM8985_WEFT_INP_PGA_GAIN_CTWW,
		6, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Captuwe PGA", WM8985_WIGHT_INP_PGA_GAIN_CTWW,
		6, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("Weft Headphone Out", WM8985_POWEW_MANAGEMENT_2,
		7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Headphone Out", WM8985_POWEW_MANAGEMENT_2,
		8, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("Weft Speakew Out", WM8985_POWEW_MANAGEMENT_3,
		5, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Speakew Out", WM8985_POWEW_MANAGEMENT_3,
		6, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Mic Bias", WM8985_POWEW_MANAGEMENT_1, 4, 0,
			    NUWW, 0),

	SND_SOC_DAPM_INPUT("WIN"),
	SND_SOC_DAPM_INPUT("WIP"),
	SND_SOC_DAPM_INPUT("WIN"),
	SND_SOC_DAPM_INPUT("WIP"),
	SND_SOC_DAPM_INPUT("W2"),
	SND_SOC_DAPM_INPUT("W2"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("SPKW"),
	SND_SOC_DAPM_OUTPUT("SPKW")
};

static const stwuct snd_soc_dapm_widget wm8985_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Weft Output Mixew", WM8985_POWEW_MANAGEMENT_3,
		2, 0, weft_out_mixew, AWWAY_SIZE(weft_out_mixew)),
	SND_SOC_DAPM_MIXEW("Wight Output Mixew", WM8985_POWEW_MANAGEMENT_3,
		3, 0, wight_out_mixew, AWWAY_SIZE(wight_out_mixew)),

	SND_SOC_DAPM_MIXEW("Weft Boost Mixew", WM8985_POWEW_MANAGEMENT_2,
		4, 0, weft_boost_mixew, AWWAY_SIZE(weft_boost_mixew)),
	SND_SOC_DAPM_MIXEW("Wight Boost Mixew", WM8985_POWEW_MANAGEMENT_2,
		5, 0, wight_boost_mixew, AWWAY_SIZE(wight_boost_mixew)),

	SND_SOC_DAPM_INPUT("AUXW"),
	SND_SOC_DAPM_INPUT("AUXW"),
};

static const stwuct snd_soc_dapm_widget wm8758_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Weft Output Mixew", WM8985_POWEW_MANAGEMENT_3,
		2, 0, weft_out_mixew,
		AWWAY_SIZE(weft_out_mixew) - 1),
	SND_SOC_DAPM_MIXEW("Wight Output Mixew", WM8985_POWEW_MANAGEMENT_3,
		3, 0, wight_out_mixew,
		AWWAY_SIZE(wight_out_mixew) - 1),

	SND_SOC_DAPM_MIXEW("Weft Boost Mixew", WM8985_POWEW_MANAGEMENT_2,
		4, 0, weft_boost_mixew,
		AWWAY_SIZE(weft_boost_mixew) - 1),
	SND_SOC_DAPM_MIXEW("Wight Boost Mixew", WM8985_POWEW_MANAGEMENT_2,
		5, 0, wight_boost_mixew,
		AWWAY_SIZE(wight_boost_mixew) - 1),
};

static const stwuct snd_soc_dapm_woute wm8985_common_dapm_woutes[] = {
	{ "Wight Output Mixew", "PCM Switch", "Wight DAC" },
	{ "Wight Output Mixew", "Wine Switch", "Wight Boost Mixew" },

	{ "Weft Output Mixew", "PCM Switch", "Weft DAC" },
	{ "Weft Output Mixew", "Wine Switch", "Weft Boost Mixew" },

	{ "Wight Headphone Out", NUWW, "Wight Output Mixew" },
	{ "HPW", NUWW, "Wight Headphone Out" },

	{ "Weft Headphone Out", NUWW, "Weft Output Mixew" },
	{ "HPW", NUWW, "Weft Headphone Out" },

	{ "Wight Speakew Out", NUWW, "Wight Output Mixew" },
	{ "SPKW", NUWW, "Wight Speakew Out" },

	{ "Weft Speakew Out", NUWW, "Weft Output Mixew" },
	{ "SPKW", NUWW, "Weft Speakew Out" },

	{ "Wight ADC", NUWW, "Wight Boost Mixew" },

	{ "Wight Boost Mixew", NUWW, "Wight Captuwe PGA" },
	{ "Wight Boost Mixew", "W2 Vowume", "W2" },

	{ "Weft ADC", NUWW, "Weft Boost Mixew" },

	{ "Weft Boost Mixew", NUWW, "Weft Captuwe PGA" },
	{ "Weft Boost Mixew", "W2 Vowume", "W2" },

	{ "Wight Captuwe PGA", NUWW, "Wight Input Mixew" },
	{ "Weft Captuwe PGA", NUWW, "Weft Input Mixew" },

	{ "Wight Input Mixew", "W2 Switch", "W2" },
	{ "Wight Input Mixew", "MicN Switch", "WIN" },
	{ "Wight Input Mixew", "MicP Switch", "WIP" },

	{ "Weft Input Mixew", "W2 Switch", "W2" },
	{ "Weft Input Mixew", "MicN Switch", "WIN" },
	{ "Weft Input Mixew", "MicP Switch", "WIP" },
};
static const stwuct snd_soc_dapm_woute wm8985_aux_dapm_woutes[] = {
	{ "Wight Output Mixew", "Aux Switch", "AUXW" },
	{ "Weft Output Mixew", "Aux Switch", "AUXW" },

	{ "Wight Boost Mixew", "AUXW Vowume", "AUXW" },
	{ "Weft Boost Mixew", "AUXW Vowume", "AUXW" },
};

static int wm8985_add_widgets(stwuct snd_soc_component *component)
{
	stwuct wm8985_pwiv *wm8985 = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	switch (wm8985->dev_type) {
	case WM8758:
		snd_soc_dapm_new_contwows(dapm, wm8758_dapm_widgets,
					  AWWAY_SIZE(wm8758_dapm_widgets));
		bweak;

	case WM8985:
		snd_soc_add_component_contwows(component, wm8985_specific_snd_contwows,
			AWWAY_SIZE(wm8985_specific_snd_contwows));

		snd_soc_dapm_new_contwows(dapm, wm8985_dapm_widgets,
			AWWAY_SIZE(wm8985_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm, wm8985_aux_dapm_woutes,
			AWWAY_SIZE(wm8985_aux_dapm_woutes));
		bweak;
	}

	wetuwn 0;
}

static int eqmode_get(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int weg;

	weg = snd_soc_component_wead(component, WM8985_EQ1_WOW_SHEWF);
	if (weg & WM8985_EQ3DMODE)
		ucontwow->vawue.enumewated.item[0] = 1;
	ewse
		ucontwow->vawue.enumewated.item[0] = 0;

	wetuwn 0;
}

static int eqmode_put(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned int wegpww2, wegpww3;
	unsigned int weg_eq;

	if (ucontwow->vawue.enumewated.item[0] != 0
			&& ucontwow->vawue.enumewated.item[0] != 1)
		wetuwn -EINVAW;

	weg_eq = snd_soc_component_wead(component, WM8985_EQ1_WOW_SHEWF);
	switch ((weg_eq & WM8985_EQ3DMODE) >> WM8985_EQ3DMODE_SHIFT) {
	case 0:
		if (!ucontwow->vawue.enumewated.item[0])
			wetuwn 0;
		bweak;
	case 1:
		if (ucontwow->vawue.enumewated.item[0])
			wetuwn 0;
		bweak;
	}

	wegpww2 = snd_soc_component_wead(component, WM8985_POWEW_MANAGEMENT_2);
	wegpww3 = snd_soc_component_wead(component, WM8985_POWEW_MANAGEMENT_3);
	/* disabwe the DACs and ADCs */
	snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_2,
			    WM8985_ADCENW_MASK | WM8985_ADCENW_MASK, 0);
	snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_3,
			    WM8985_DACENW_MASK | WM8985_DACENW_MASK, 0);
	snd_soc_component_update_bits(component, WM8985_ADDITIONAW_CONTWOW,
			    WM8985_M128ENB_MASK, WM8985_M128ENB);
	/* set the desiwed eqmode */
	snd_soc_component_update_bits(component, WM8985_EQ1_WOW_SHEWF,
			    WM8985_EQ3DMODE_MASK,
			    ucontwow->vawue.enumewated.item[0]
			    << WM8985_EQ3DMODE_SHIFT);
	/* westowe DAC/ADC configuwation */
	snd_soc_component_wwite(component, WM8985_POWEW_MANAGEMENT_2, wegpww2);
	snd_soc_component_wwite(component, WM8985_POWEW_MANAGEMENT_3, wegpww3);
	wetuwn 0;
}

static int wm8985_weset(stwuct snd_soc_component *component)
{
	wetuwn snd_soc_component_wwite(component, WM8985_SOFTWAWE_WESET, 0x0);
}

static int wm8985_dac_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	wetuwn snd_soc_component_update_bits(component, WM8985_DAC_CONTWOW,
				   WM8985_SOFTMUTE_MASK,
				   !!mute << WM8985_SOFTMUTE_SHIFT);
}

static int wm8985_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component;
	u16 fowmat, mastew, bcp, wwp;

	component = dai->component;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fowmat = 0x2;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		fowmat = 0x0;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fowmat = 0x1;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		fowmat = 0x3;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown dai fowmat\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WM8985_AUDIO_INTEWFACE,
			    WM8985_FMT_MASK, fowmat << WM8985_FMT_SHIFT);

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		mastew = 1;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		mastew = 0;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown mastew/swave configuwation\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WM8985_CWOCK_GEN_CONTWOW,
			    WM8985_MS_MASK, mastew << WM8985_MS_SHIFT);

	/* fwame invewsion is not vawid fow dsp modes */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_IB_IF:
		case SND_SOC_DAIFMT_NB_IF:
			wetuwn -EINVAW;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	bcp = wwp = 0;
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		bcp = wwp = 1;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		bcp = 1;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		wwp = 1;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown powawity configuwation\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WM8985_AUDIO_INTEWFACE,
			    WM8985_WWP_MASK, wwp << WM8985_WWP_SHIFT);
	snd_soc_component_update_bits(component, WM8985_AUDIO_INTEWFACE,
			    WM8985_BCP_MASK, bcp << WM8985_BCP_SHIFT);
	wetuwn 0;
}

static int wm8985_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	int i;
	stwuct snd_soc_component *component;
	stwuct wm8985_pwiv *wm8985;
	u16 bwen, swate_idx;
	unsigned int tmp;
	int swate_best;

	component = dai->component;
	wm8985 = snd_soc_component_get_dwvdata(component);

	wm8985->bcwk = snd_soc_pawams_to_bcwk(pawams);
	if ((int)wm8985->bcwk < 0)
		wetuwn wm8985->bcwk;

	switch (pawams_width(pawams)) {
	case 16:
		bwen = 0x0;
		bweak;
	case 20:
		bwen = 0x1;
		bweak;
	case 24:
		bwen = 0x2;
		bweak;
	case 32:
		bwen = 0x3;
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unsuppowted wowd wength %u\n",
			pawams_width(pawams));
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, WM8985_AUDIO_INTEWFACE,
			    WM8985_WW_MASK, bwen << WM8985_WW_SHIFT);

	/*
	 * match to the neawest possibwe sampwe wate and wewy
	 * on the awway index to configuwe the SW wegistew
	 */
	swate_idx = 0;
	swate_best = abs(swates[0] - pawams_wate(pawams));
	fow (i = 1; i < AWWAY_SIZE(swates); ++i) {
		if (abs(swates[i] - pawams_wate(pawams)) >= swate_best)
			continue;
		swate_idx = i;
		swate_best = abs(swates[i] - pawams_wate(pawams));
	}

	dev_dbg(dai->dev, "Sewected SWATE = %d\n", swates[swate_idx]);
	snd_soc_component_update_bits(component, WM8985_ADDITIONAW_CONTWOW,
			    WM8985_SW_MASK, swate_idx << WM8985_SW_SHIFT);

	dev_dbg(dai->dev, "Tawget BCWK = %uHz\n", wm8985->bcwk);
	dev_dbg(dai->dev, "SYSCWK = %uHz\n", wm8985->syscwk);

	fow (i = 0; i < AWWAY_SIZE(fs_watios); ++i) {
		if (wm8985->syscwk / pawams_wate(pawams)
				== fs_watios[i].watio)
			bweak;
	}

	if (i == AWWAY_SIZE(fs_watios)) {
		dev_eww(dai->dev, "Unabwe to configuwe MCWK watio %u/%u\n",
			wm8985->syscwk, pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	dev_dbg(dai->dev, "MCWK watio = %dfs\n", fs_watios[i].watio);
	snd_soc_component_update_bits(component, WM8985_CWOCK_GEN_CONTWOW,
			    WM8985_MCWKDIV_MASK, i << WM8985_MCWKDIV_SHIFT);

	/* sewect the appwopwiate bcwk dividew */
	tmp = (wm8985->syscwk / fs_watios[i].div) * 10;
	fow (i = 0; i < AWWAY_SIZE(bcwk_divs); ++i) {
		if (wm8985->bcwk == tmp / bcwk_divs[i])
			bweak;
	}

	if (i == AWWAY_SIZE(bcwk_divs)) {
		dev_eww(dai->dev, "No matching BCWK dividew found\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dai->dev, "BCWK div = %d\n", i);
	snd_soc_component_update_bits(component, WM8985_CWOCK_GEN_CONTWOW,
			    WM8985_BCWKDIV_MASK, i << WM8985_BCWKDIV_SHIFT);
	wetuwn 0;
}

stwuct pww_div {
	u32 div2:1;
	u32 n:4;
	u32 k:24;
};

#define FIXED_PWW_SIZE ((1UWW << 24) * 10)
static int pww_factows(stwuct pww_div *pww_div, unsigned int tawget,
		       unsigned int souwce)
{
	u64 Kpawt;
	unsigned wong int K, Ndiv, Nmod;

	pww_div->div2 = 0;
	Ndiv = tawget / souwce;
	if (Ndiv < 6) {
		souwce >>= 1;
		pww_div->div2 = 1;
		Ndiv = tawget / souwce;
	}

	if (Ndiv < 6 || Ndiv > 12) {
		pwintk(KEWN_EWW "%s: WM8985 N vawue is not within"
		       " the wecommended wange: %wu\n", __func__, Ndiv);
		wetuwn -EINVAW;
	}
	pww_div->n = Ndiv;

	Nmod = tawget % souwce;
	Kpawt = FIXED_PWW_SIZE * (u64)Nmod;

	do_div(Kpawt, souwce);

	K = Kpawt & 0xffffffff;
	if ((K % 10) >= 5)
		K += 5;
	K /= 10;
	pww_div->k = K;

	wetuwn 0;
}

static int wm8985_set_pww(stwuct snd_soc_dai *dai, int pww_id,
			  int souwce, unsigned int fweq_in,
			  unsigned int fweq_out)
{
	int wet;
	stwuct snd_soc_component *component;
	stwuct pww_div pww_div;

	component = dai->component;
	if (!fweq_in || !fweq_out) {
		/* disabwe the PWW */
		snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
				    WM8985_PWWEN_MASK, 0);
	} ewse {
		wet = pww_factows(&pww_div, fweq_out * 4 * 2, fweq_in);
		if (wet)
			wetuwn wet;

		/* set PWWN and PWESCAWE */
		snd_soc_component_wwite(component, WM8985_PWW_N,
			      (pww_div.div2 << WM8985_PWW_PWESCAWE_SHIFT)
			      | pww_div.n);
		/* set PWWK */
		snd_soc_component_wwite(component, WM8985_PWW_K_3, pww_div.k & 0x1ff);
		snd_soc_component_wwite(component, WM8985_PWW_K_2, (pww_div.k >> 9) & 0x1ff);
		snd_soc_component_wwite(component, WM8985_PWW_K_1, (pww_div.k >> 18));
		/* set the souwce of the cwock to be the PWW */
		snd_soc_component_update_bits(component, WM8985_CWOCK_GEN_CONTWOW,
				    WM8985_CWKSEW_MASK, WM8985_CWKSEW);
		/* enabwe the PWW */
		snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
				    WM8985_PWWEN_MASK, WM8985_PWWEN);
	}
	wetuwn 0;
}

static int wm8985_set_syscwk(stwuct snd_soc_dai *dai,
			     int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component;
	stwuct wm8985_pwiv *wm8985;

	component = dai->component;
	wm8985 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case WM8985_CWKSWC_MCWK:
		snd_soc_component_update_bits(component, WM8985_CWOCK_GEN_CONTWOW,
				    WM8985_CWKSEW_MASK, 0);
		snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
				    WM8985_PWWEN_MASK, 0);
		bweak;
	case WM8985_CWKSWC_PWW:
		snd_soc_component_update_bits(component, WM8985_CWOCK_GEN_CONTWOW,
				    WM8985_CWKSEW_MASK, WM8985_CWKSEW);
		bweak;
	defauwt:
		dev_eww(dai->dev, "Unknown cwock souwce %d\n", cwk_id);
		wetuwn -EINVAW;
	}

	wm8985->syscwk = fweq;
	wetuwn 0;
}

static int wm8985_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	int wet;
	stwuct wm8985_pwiv *wm8985;

	wm8985 = snd_soc_component_get_dwvdata(component);
	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		/* VMID at 75k */
		snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
				    WM8985_VMIDSEW_MASK,
				    1 << WM8985_VMIDSEW_SHIFT);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8985->suppwies),
						    wm8985->suppwies);
			if (wet) {
				dev_eww(component->dev,
					"Faiwed to enabwe suppwies: %d\n",
					wet);
				wetuwn wet;
			}

			wegcache_sync(wm8985->wegmap);

			/* enabwe anti-pop featuwes */
			snd_soc_component_update_bits(component, WM8985_OUT4_TO_ADC,
					    WM8985_POBCTWW_MASK,
					    WM8985_POBCTWW);
			/* enabwe thewmaw shutdown */
			snd_soc_component_update_bits(component, WM8985_OUTPUT_CTWW0,
					    WM8985_TSDEN_MASK, WM8985_TSDEN);
			snd_soc_component_update_bits(component, WM8985_OUTPUT_CTWW0,
					    WM8985_TSOPCTWW_MASK,
					    WM8985_TSOPCTWW);
			/* enabwe BIASEN */
			snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
					    WM8985_BIASEN_MASK, WM8985_BIASEN);
			/* VMID at 75k */
			snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
					    WM8985_VMIDSEW_MASK,
					    1 << WM8985_VMIDSEW_SHIFT);
			msweep(500);
			/* disabwe anti-pop featuwes */
			snd_soc_component_update_bits(component, WM8985_OUT4_TO_ADC,
					    WM8985_POBCTWW_MASK, 0);
		}
		/* VMID at 300k */
		snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
				    WM8985_VMIDSEW_MASK,
				    2 << WM8985_VMIDSEW_SHIFT);
		bweak;
	case SND_SOC_BIAS_OFF:
		/* disabwe thewmaw shutdown */
		snd_soc_component_update_bits(component, WM8985_OUTPUT_CTWW0,
				    WM8985_TSOPCTWW_MASK, 0);
		snd_soc_component_update_bits(component, WM8985_OUTPUT_CTWW0,
				    WM8985_TSDEN_MASK, 0);
		/* disabwe VMIDSEW and BIASEN */
		snd_soc_component_update_bits(component, WM8985_POWEW_MANAGEMENT_1,
				    WM8985_VMIDSEW_MASK | WM8985_BIASEN_MASK,
				    0);
		snd_soc_component_wwite(component, WM8985_POWEW_MANAGEMENT_1, 0);
		snd_soc_component_wwite(component, WM8985_POWEW_MANAGEMENT_2, 0);
		snd_soc_component_wwite(component, WM8985_POWEW_MANAGEMENT_3, 0);

		wegcache_mawk_diwty(wm8985->wegmap);

		weguwatow_buwk_disabwe(AWWAY_SIZE(wm8985->suppwies),
				       wm8985->suppwies);
		bweak;
	}

	wetuwn 0;
}

static int wm8985_pwobe(stwuct snd_soc_component *component)
{
	size_t i;
	stwuct wm8985_pwiv *wm8985;
	int wet;

	wm8985 = snd_soc_component_get_dwvdata(component);

	fow (i = 0; i < AWWAY_SIZE(wm8985->suppwies); i++)
		wm8985->suppwies[i].suppwy = wm8985_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(component->dev, AWWAY_SIZE(wm8985->suppwies),
				 wm8985->suppwies);
	if (wet) {
		dev_eww(component->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8985->suppwies),
				    wm8985->suppwies);
	if (wet) {
		dev_eww(component->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = wm8985_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset: %d\n", wet);
		goto eww_weg_enabwe;
	}

	/* watch vowume update bits */
	fow (i = 0; i < AWWAY_SIZE(vowume_update_wegs); ++i)
		snd_soc_component_update_bits(component, vowume_update_wegs[i],
				    0x100, 0x100);
	/* enabwe BIASCUT */
	snd_soc_component_update_bits(component, WM8985_BIAS_CTWW, WM8985_BIASCUT,
			    WM8985_BIASCUT);

	wm8985_add_widgets(component);

	wetuwn 0;

eww_weg_enabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8985->suppwies), wm8985->suppwies);
	wetuwn wet;
}

static const stwuct snd_soc_dai_ops wm8985_dai_ops = {
	.mute_stweam = wm8985_dac_mute,
	.hw_pawams = wm8985_hw_pawams,
	.set_fmt = wm8985_set_fmt,
	.set_syscwk = wm8985_set_syscwk,
	.set_pww = wm8985_set_pww,
	.no_captuwe_mute = 1,
};

#define WM8985_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew wm8985_dai = {
	.name = "wm8985-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = WM8985_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = WM8985_FOWMATS,
	},
	.ops = &wm8985_dai_ops,
	.symmetwic_wate = 1
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8985 = {
	.pwobe			= wm8985_pwobe,
	.set_bias_wevew		= wm8985_set_bias_wevew,
	.contwows		= wm8985_common_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8985_common_snd_contwows),
	.dapm_widgets		= wm8985_common_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8985_common_dapm_widgets),
	.dapm_woutes		= wm8985_common_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8985_common_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wm8985_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,

	.max_wegistew = WM8985_MAX_WEGISTEW,
	.wwiteabwe_weg = wm8985_wwiteabwe,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wm8985_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8985_weg_defauwts),
};

#if defined(CONFIG_SPI_MASTEW)
static int wm8985_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8985_pwiv *wm8985;
	int wet;

	wm8985 = devm_kzawwoc(&spi->dev, sizeof *wm8985, GFP_KEWNEW);
	if (!wm8985)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, wm8985);

	wm8985->dev_type = WM8985;

	wm8985->wegmap = devm_wegmap_init_spi(spi, &wm8985_wegmap);
	if (IS_EWW(wm8985->wegmap)) {
		wet = PTW_EWW(wm8985->wegmap);
		dev_eww(&spi->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&spi->dev,
				     &soc_component_dev_wm8985, &wm8985_dai, 1);
	wetuwn wet;
}

static stwuct spi_dwivew wm8985_spi_dwivew = {
	.dwivew = {
		.name = "wm8985",
	},
	.pwobe = wm8985_spi_pwobe,
};
#endif

#if IS_ENABWED(CONFIG_I2C)
static const stwuct i2c_device_id wm8985_i2c_id[];

static int wm8985_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8985_pwiv *wm8985;
	const stwuct i2c_device_id *id = i2c_match_id(wm8985_i2c_id, i2c);
	int wet;

	wm8985 = devm_kzawwoc(&i2c->dev, sizeof *wm8985, GFP_KEWNEW);
	if (!wm8985)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wm8985);

	wm8985->dev_type = id->dwivew_data;

	wm8985->wegmap = devm_wegmap_init_i2c(i2c, &wm8985_wegmap);
	if (IS_EWW(wm8985->wegmap)) {
		wet = PTW_EWW(wm8985->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				     &soc_component_dev_wm8985, &wm8985_dai, 1);
	wetuwn wet;
}

static const stwuct i2c_device_id wm8985_i2c_id[] = {
	{ "wm8985", WM8985 },
	{ "wm8758", WM8758 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8985_i2c_id);

static stwuct i2c_dwivew wm8985_i2c_dwivew = {
	.dwivew = {
		.name = "wm8985",
	},
	.pwobe = wm8985_i2c_pwobe,
	.id_tabwe = wm8985_i2c_id
};
#endif

static int __init wm8985_modinit(void)
{
	int wet = 0;

#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8985_i2c_dwivew);
	if (wet) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8985 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8985_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8985 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn wet;
}
moduwe_init(wm8985_modinit);

static void __exit wm8985_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8985_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8985_spi_dwivew);
#endif
}
moduwe_exit(wm8985_exit);

MODUWE_DESCWIPTION("ASoC WM8985 / WM8758 dwivew");
MODUWE_AUTHOW("Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
