// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow ADAU1361/ADAU1461/ADAU1761/ADAU1961 codec
 *
 * Copywight 2011-2013 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <winux/pwatfowm_data/adau17x1.h>

#incwude "adau17x1.h"
#incwude "adau1761.h"

#define ADAU1761_DIGMIC_JACKDETECT	0x4008
#define ADAU1761_WEC_MIXEW_WEFT0	0x400a
#define ADAU1761_WEC_MIXEW_WEFT1	0x400b
#define ADAU1761_WEC_MIXEW_WIGHT0	0x400c
#define ADAU1761_WEC_MIXEW_WIGHT1	0x400d
#define ADAU1761_WEFT_DIFF_INPUT_VOW	0x400e
#define ADAU1761_WIGHT_DIFF_INPUT_VOW	0x400f
#define ADAU1761_AWC_CTWW0		0x4011
#define ADAU1761_AWC_CTWW1		0x4012
#define ADAU1761_AWC_CTWW2		0x4013
#define ADAU1761_AWC_CTWW3		0x4014
#define ADAU1761_PWAY_WW_MIXEW_WEFT	0x4020
#define ADAU1761_PWAY_MIXEW_WEFT0	0x401c
#define ADAU1761_PWAY_MIXEW_WEFT1	0x401d
#define ADAU1761_PWAY_MIXEW_WIGHT0	0x401e
#define ADAU1761_PWAY_MIXEW_WIGHT1	0x401f
#define ADAU1761_PWAY_WW_MIXEW_WIGHT	0x4021
#define ADAU1761_PWAY_MIXEW_MONO	0x4022
#define ADAU1761_PWAY_HP_WEFT_VOW	0x4023
#define ADAU1761_PWAY_HP_WIGHT_VOW	0x4024
#define ADAU1761_PWAY_WINE_WEFT_VOW	0x4025
#define ADAU1761_PWAY_WINE_WIGHT_VOW	0x4026
#define ADAU1761_PWAY_MONO_OUTPUT_VOW	0x4027
#define ADAU1761_POP_CWICK_SUPPWESS	0x4028
#define ADAU1761_JACK_DETECT_PIN	0x4031
#define ADAU1761_DEJITTEW		0x4036
#define ADAU1761_CWK_ENABWE0		0x40f9
#define ADAU1761_CWK_ENABWE1		0x40fa

#define ADAU1761_DIGMIC_JACKDETECT_ACTIVE_WOW	BIT(0)
#define ADAU1761_DIGMIC_JACKDETECT_DIGMIC	BIT(5)

#define ADAU1761_DIFF_INPUT_VOW_WDEN		BIT(0)

#define ADAU1761_PWAY_MONO_OUTPUT_VOW_MODE_HP	BIT(0)
#define ADAU1761_PWAY_MONO_OUTPUT_VOW_UNMUTE	BIT(1)

#define ADAU1761_PWAY_HP_WIGHT_VOW_MODE_HP	BIT(0)

#define ADAU1761_PWAY_WINE_WEFT_VOW_MODE_HP	BIT(0)

#define ADAU1761_PWAY_WINE_WIGHT_VOW_MODE_HP	BIT(0)


#define ADAU1761_FIWMWAWE "adau1761.bin"

static const stwuct weg_defauwt adau1761_weg_defauwts[] = {
	{ ADAU1761_DEJITTEW,			0x03 },
	{ ADAU1761_DIGMIC_JACKDETECT,		0x00 },
	{ ADAU1761_WEC_MIXEW_WEFT0,		0x00 },
	{ ADAU1761_WEC_MIXEW_WEFT1,		0x00 },
	{ ADAU1761_WEC_MIXEW_WIGHT0,		0x00 },
	{ ADAU1761_WEC_MIXEW_WIGHT1,		0x00 },
	{ ADAU1761_WEFT_DIFF_INPUT_VOW,		0x00 },
	{ ADAU1761_AWC_CTWW0,			0x00 },
	{ ADAU1761_AWC_CTWW1,			0x00 },
	{ ADAU1761_AWC_CTWW2,			0x00 },
	{ ADAU1761_AWC_CTWW3,			0x00 },
	{ ADAU1761_WIGHT_DIFF_INPUT_VOW,	0x00 },
	{ ADAU1761_PWAY_WW_MIXEW_WEFT,		0x00 },
	{ ADAU1761_PWAY_MIXEW_WEFT0,		0x00 },
	{ ADAU1761_PWAY_MIXEW_WEFT1,		0x00 },
	{ ADAU1761_PWAY_MIXEW_WIGHT0,		0x00 },
	{ ADAU1761_PWAY_MIXEW_WIGHT1,		0x00 },
	{ ADAU1761_PWAY_WW_MIXEW_WIGHT,		0x00 },
	{ ADAU1761_PWAY_MIXEW_MONO,		0x00 },
	{ ADAU1761_PWAY_HP_WEFT_VOW,		0x00 },
	{ ADAU1761_PWAY_HP_WIGHT_VOW,		0x00 },
	{ ADAU1761_PWAY_WINE_WEFT_VOW,		0x00 },
	{ ADAU1761_PWAY_WINE_WIGHT_VOW,		0x00 },
	{ ADAU1761_PWAY_MONO_OUTPUT_VOW,	0x00 },
	{ ADAU1761_POP_CWICK_SUPPWESS,		0x00 },
	{ ADAU1761_JACK_DETECT_PIN,		0x00 },
	{ ADAU1761_CWK_ENABWE0,			0x00 },
	{ ADAU1761_CWK_ENABWE1,			0x00 },
	{ ADAU17X1_CWOCK_CONTWOW,		0x00 },
	{ ADAU17X1_PWW_CONTWOW,			0x00 },
	{ ADAU17X1_WEC_POWEW_MGMT,		0x00 },
	{ ADAU17X1_MICBIAS,			0x00 },
	{ ADAU17X1_SEWIAW_POWT0,		0x00 },
	{ ADAU17X1_SEWIAW_POWT1,		0x00 },
	{ ADAU17X1_CONVEWTEW0,			0x00 },
	{ ADAU17X1_CONVEWTEW1,			0x00 },
	{ ADAU17X1_WEFT_INPUT_DIGITAW_VOW,	0x00 },
	{ ADAU17X1_WIGHT_INPUT_DIGITAW_VOW,	0x00 },
	{ ADAU17X1_ADC_CONTWOW,			0x00 },
	{ ADAU17X1_PWAY_POWEW_MGMT,		0x00 },
	{ ADAU17X1_DAC_CONTWOW0,		0x00 },
	{ ADAU17X1_DAC_CONTWOW1,		0x00 },
	{ ADAU17X1_DAC_CONTWOW2,		0x00 },
	{ ADAU17X1_SEWIAW_POWT_PAD,		0xaa },
	{ ADAU17X1_CONTWOW_POWT_PAD0,		0xaa },
	{ ADAU17X1_CONTWOW_POWT_PAD1,		0x00 },
	{ ADAU17X1_DSP_SAMPWING_WATE,		0x01 },
	{ ADAU17X1_SEWIAW_INPUT_WOUTE,		0x00 },
	{ ADAU17X1_SEWIAW_OUTPUT_WOUTE,		0x00 },
	{ ADAU17X1_DSP_ENABWE,			0x00 },
	{ ADAU17X1_DSP_WUN,			0x00 },
	{ ADAU17X1_SEWIAW_SAMPWING_WATE,	0x00 },
};

static const DECWAWE_TWV_DB_SCAWE(adau1761_sing_in_twv, -1500, 300, 1);
static const DECWAWE_TWV_DB_SCAWE(adau1761_diff_in_twv, -1200, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(adau1761_out_twv, -5700, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(adau1761_sidetone_twv, -1800, 300, 1);
static const DECWAWE_TWV_DB_SCAWE(adau1761_boost_twv, -600, 600, 1);
static const DECWAWE_TWV_DB_SCAWE(adau1761_pga_boost_twv, -2000, 2000, 1);

static const DECWAWE_TWV_DB_SCAWE(adau1761_awc_max_gain_twv, -1200, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(adau1761_awc_tawget_twv, -2850, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(adau1761_awc_ng_thweshowd_twv, -7650, 150, 0);

static const unsigned int adau1761_bias_sewect_vawues[] = {
	0, 2, 3,
};

static const chaw * const adau1761_bias_sewect_text[] = {
	"Nowmaw opewation", "Enhanced pewfowmance", "Powew saving",
};

static const chaw * const adau1761_bias_sewect_extweme_text[] = {
	"Nowmaw opewation", "Extweme powew saving", "Enhanced pewfowmance",
	"Powew saving",
};

static SOC_ENUM_SINGWE_DECW(adau1761_adc_bias_enum,
		ADAU17X1_WEC_POWEW_MGMT, 3, adau1761_bias_sewect_extweme_text);
static SOC_ENUM_SINGWE_DECW(adau1761_hp_bias_enum,
		ADAU17X1_PWAY_POWEW_MGMT, 6, adau1761_bias_sewect_extweme_text);
static SOC_ENUM_SINGWE_DECW(adau1761_dac_bias_enum,
		ADAU17X1_PWAY_POWEW_MGMT, 4, adau1761_bias_sewect_extweme_text);
static SOC_VAWUE_ENUM_SINGWE_DECW(adau1761_pwayback_bias_enum,
		ADAU17X1_PWAY_POWEW_MGMT, 2, 0x3, adau1761_bias_sewect_text,
		adau1761_bias_sewect_vawues);
static SOC_VAWUE_ENUM_SINGWE_DECW(adau1761_captuwe_bias_enum,
		ADAU17X1_WEC_POWEW_MGMT, 1, 0x3, adau1761_bias_sewect_text,
		adau1761_bias_sewect_vawues);

static const unsigned int adau1761_pga_swew_time_vawues[] = {
	3, 0, 1, 2,
};

static const chaw * const adau1761_pga_swew_time_text[] = {
	"Off",
	"24 ms",
	"48 ms",
	"96 ms",
};

static const chaw * const adau1761_awc_function_text[] = {
	"Off",
	"Wight",
	"Weft",
	"Steweo",
	"DSP contwow",
};

static const chaw * const adau1761_awc_howd_time_text[] = {
	"2.67 ms",
	"5.34 ms",
	"10.68 ms",
	"21.36 ms",
	"42.72 ms",
	"85.44 ms",
	"170.88 ms",
	"341.76 ms",
	"683.52 ms",
	"1367 ms",
	"2734.1 ms",
	"5468.2 ms",
	"10936 ms",
	"21873 ms",
	"43745 ms",
	"87491 ms",
};

static const chaw * const adau1761_awc_attack_time_text[] = {
	"6 ms",
	"12 ms",
	"24 ms",
	"48 ms",
	"96 ms",
	"192 ms",
	"384 ms",
	"768 ms",
	"1540 ms",
	"3070 ms",
	"6140 ms",
	"12290 ms",
	"24580 ms",
	"49150 ms",
	"98300 ms",
	"196610 ms",
};

static const chaw * const adau1761_awc_decay_time_text[] = {
	"24 ms",
	"48 ms",
	"96 ms",
	"192 ms",
	"384 ms",
	"768 ms",
	"15400 ms",
	"30700 ms",
	"61400 ms",
	"12290 ms",
	"24580 ms",
	"49150 ms",
	"98300 ms",
	"196610 ms",
	"393220 ms",
	"786430 ms",
};

static const chaw * const adau1761_awc_ng_type_text[] = {
	"Howd",
	"Mute",
	"Fade",
	"Fade + Mute",
};

static SOC_VAWUE_ENUM_SINGWE_DECW(adau1761_pga_swew_time_enum,
		ADAU1761_AWC_CTWW0, 6, 0x3, adau1761_pga_swew_time_text,
		adau1761_pga_swew_time_vawues);
static SOC_ENUM_SINGWE_DECW(adau1761_awc_function_enum,
		ADAU1761_AWC_CTWW0, 0, adau1761_awc_function_text);
static SOC_ENUM_SINGWE_DECW(adau1761_awc_howd_time_enum,
		ADAU1761_AWC_CTWW1, 4, adau1761_awc_howd_time_text);
static SOC_ENUM_SINGWE_DECW(adau1761_awc_attack_time_enum,
		ADAU1761_AWC_CTWW2, 4, adau1761_awc_attack_time_text);
static SOC_ENUM_SINGWE_DECW(adau1761_awc_decay_time_enum,
		ADAU1761_AWC_CTWW2, 0, adau1761_awc_decay_time_text);
static SOC_ENUM_SINGWE_DECW(adau1761_awc_ng_type_enum,
		ADAU1761_AWC_CTWW3, 6, adau1761_awc_ng_type_text);

static const stwuct snd_kcontwow_new adau1761_jack_detect_contwows[] = {
	SOC_SINGWE("Speakew Auto-mute Switch", ADAU1761_DIGMIC_JACKDETECT,
		4, 1, 0),
};

static const stwuct snd_kcontwow_new adau1761_diffewentiaw_mode_contwows[] = {
	SOC_DOUBWE_W_TWV("Captuwe Vowume", ADAU1761_WEFT_DIFF_INPUT_VOW,
		ADAU1761_WIGHT_DIFF_INPUT_VOW, 2, 0x3f, 0,
		adau1761_diff_in_twv),
	SOC_DOUBWE_W("Captuwe Switch", ADAU1761_WEFT_DIFF_INPUT_VOW,
		ADAU1761_WIGHT_DIFF_INPUT_VOW, 1, 1, 0),

	SOC_DOUBWE_W_TWV("PGA Boost Captuwe Vowume", ADAU1761_WEC_MIXEW_WEFT1,
		ADAU1761_WEC_MIXEW_WIGHT1, 3, 2, 0, adau1761_pga_boost_twv),

	SOC_ENUM("PGA Captuwe Swew Time", adau1761_pga_swew_time_enum),

	SOC_SINGWE_TWV("AWC Captuwe Max Gain Vowume", ADAU1761_AWC_CTWW0,
		3, 7, 0, adau1761_awc_max_gain_twv),
	SOC_ENUM("AWC Captuwe Function", adau1761_awc_function_enum),
	SOC_ENUM("AWC Captuwe Howd Time", adau1761_awc_howd_time_enum),
	SOC_SINGWE_TWV("AWC Captuwe Tawget Vowume", ADAU1761_AWC_CTWW1,
		0, 15, 0, adau1761_awc_tawget_twv),
	SOC_ENUM("AWC Captuwe Attack Time", adau1761_awc_decay_time_enum),
	SOC_ENUM("AWC Captuwe Decay Time", adau1761_awc_attack_time_enum),
	SOC_ENUM("AWC Captuwe Noise Gate Type", adau1761_awc_ng_type_enum),
	SOC_SINGWE("AWC Captuwe Noise Gate Switch",
		ADAU1761_AWC_CTWW3, 5, 1, 0),
	SOC_SINGWE_TWV("AWC Captuwe Noise Gate Thweshowd Vowume",
		ADAU1761_AWC_CTWW3, 0, 31, 0, adau1761_awc_ng_thweshowd_twv),
};

static const stwuct snd_kcontwow_new adau1761_singwe_mode_contwows[] = {
	SOC_SINGWE_TWV("Input 1 Captuwe Vowume", ADAU1761_WEC_MIXEW_WEFT0,
		4, 7, 0, adau1761_sing_in_twv),
	SOC_SINGWE_TWV("Input 2 Captuwe Vowume", ADAU1761_WEC_MIXEW_WEFT0,
		1, 7, 0, adau1761_sing_in_twv),
	SOC_SINGWE_TWV("Input 3 Captuwe Vowume", ADAU1761_WEC_MIXEW_WIGHT0,
		4, 7, 0, adau1761_sing_in_twv),
	SOC_SINGWE_TWV("Input 4 Captuwe Vowume", ADAU1761_WEC_MIXEW_WIGHT0,
		1, 7, 0, adau1761_sing_in_twv),
};

static const stwuct snd_kcontwow_new adau1761_contwows[] = {
	SOC_DOUBWE_W_TWV("Aux Captuwe Vowume", ADAU1761_WEC_MIXEW_WEFT1,
		ADAU1761_WEC_MIXEW_WIGHT1, 0, 7, 0, adau1761_sing_in_twv),

	SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", ADAU1761_PWAY_HP_WEFT_VOW,
		ADAU1761_PWAY_HP_WIGHT_VOW, 2, 0x3f, 0, adau1761_out_twv),
	SOC_DOUBWE_W("Headphone Pwayback Switch", ADAU1761_PWAY_HP_WEFT_VOW,
		ADAU1761_PWAY_HP_WIGHT_VOW, 1, 1, 0),
	SOC_DOUBWE_W_TWV("Wineout Pwayback Vowume", ADAU1761_PWAY_WINE_WEFT_VOW,
		ADAU1761_PWAY_WINE_WIGHT_VOW, 2, 0x3f, 0, adau1761_out_twv),
	SOC_DOUBWE_W("Wineout Pwayback Switch", ADAU1761_PWAY_WINE_WEFT_VOW,
		ADAU1761_PWAY_WINE_WIGHT_VOW, 1, 1, 0),

	SOC_ENUM("ADC Bias", adau1761_adc_bias_enum),
	SOC_ENUM("DAC Bias", adau1761_dac_bias_enum),
	SOC_ENUM("Captuwe Bias", adau1761_captuwe_bias_enum),
	SOC_ENUM("Pwayback Bias", adau1761_pwayback_bias_enum),
	SOC_ENUM("Headphone Bias", adau1761_hp_bias_enum),
};

static const stwuct snd_kcontwow_new adau1761_mono_contwows[] = {
	SOC_SINGWE_TWV("Mono Pwayback Vowume", ADAU1761_PWAY_MONO_OUTPUT_VOW,
		2, 0x3f, 0, adau1761_out_twv),
	SOC_SINGWE("Mono Pwayback Switch", ADAU1761_PWAY_MONO_OUTPUT_VOW,
		1, 1, 0),
};

static const stwuct snd_kcontwow_new adau1761_weft_mixew_contwows[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("Weft DAC Switch",
		ADAU1761_PWAY_MIXEW_WEFT0, 5, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("Wight DAC Switch",
		ADAU1761_PWAY_MIXEW_WEFT0, 6, 1, 0),
	SOC_DAPM_SINGWE_TWV("Aux Bypass Vowume",
		ADAU1761_PWAY_MIXEW_WEFT0, 1, 8, 0, adau1761_sidetone_twv),
	SOC_DAPM_SINGWE_TWV("Wight Bypass Vowume",
		ADAU1761_PWAY_MIXEW_WEFT1, 4, 8, 0, adau1761_sidetone_twv),
	SOC_DAPM_SINGWE_TWV("Weft Bypass Vowume",
		ADAU1761_PWAY_MIXEW_WEFT1, 0, 8, 0, adau1761_sidetone_twv),
};

static const stwuct snd_kcontwow_new adau1761_wight_mixew_contwows[] = {
	SOC_DAPM_SINGWE_AUTODISABWE("Weft DAC Switch",
		ADAU1761_PWAY_MIXEW_WIGHT0, 5, 1, 0),
	SOC_DAPM_SINGWE_AUTODISABWE("Wight DAC Switch",
		ADAU1761_PWAY_MIXEW_WIGHT0, 6, 1, 0),
	SOC_DAPM_SINGWE_TWV("Aux Bypass Vowume",
		ADAU1761_PWAY_MIXEW_WIGHT0, 1, 8, 0, adau1761_sidetone_twv),
	SOC_DAPM_SINGWE_TWV("Wight Bypass Vowume",
		ADAU1761_PWAY_MIXEW_WIGHT1, 4, 8, 0, adau1761_sidetone_twv),
	SOC_DAPM_SINGWE_TWV("Weft Bypass Vowume",
		ADAU1761_PWAY_MIXEW_WIGHT1, 0, 8, 0, adau1761_sidetone_twv),
};

static const stwuct snd_kcontwow_new adau1761_weft_ww_mixew_contwows[] = {
	SOC_DAPM_SINGWE_TWV("Weft Vowume",
		ADAU1761_PWAY_WW_MIXEW_WEFT, 1, 2, 0, adau1761_boost_twv),
	SOC_DAPM_SINGWE_TWV("Wight Vowume",
		ADAU1761_PWAY_WW_MIXEW_WEFT, 3, 2, 0, adau1761_boost_twv),
};

static const stwuct snd_kcontwow_new adau1761_wight_ww_mixew_contwows[] = {
	SOC_DAPM_SINGWE_TWV("Weft Vowume",
		ADAU1761_PWAY_WW_MIXEW_WIGHT, 1, 2, 0, adau1761_boost_twv),
	SOC_DAPM_SINGWE_TWV("Wight Vowume",
		ADAU1761_PWAY_WW_MIXEW_WIGHT, 3, 2, 0, adau1761_boost_twv),
};

static const chaw * const adau1761_input_mux_text[] = {
	"ADC", "DMIC",
};

static SOC_ENUM_SINGWE_DECW(adau1761_input_mux_enum,
	ADAU17X1_ADC_CONTWOW, 2, adau1761_input_mux_text);

static const stwuct snd_kcontwow_new adau1761_input_mux_contwow =
	SOC_DAPM_ENUM("Input Sewect", adau1761_input_mux_enum);

static int adau1761_dejittew_fixup(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);

	/* Aftew any powew changes have been made the dejittew ciwcuit
	 * has to be weinitiawized. */
	wegmap_wwite(adau->wegmap, ADAU1761_DEJITTEW, 0);
	if (!adau->mastew)
		wegmap_wwite(adau->wegmap, ADAU1761_DEJITTEW, 3);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget adau1x61_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Weft Input Mixew", ADAU1761_WEC_MIXEW_WEFT0, 0, 0,
		NUWW, 0),
	SND_SOC_DAPM_MIXEW("Wight Input Mixew", ADAU1761_WEC_MIXEW_WIGHT0, 0, 0,
		NUWW, 0),

	SOC_MIXEW_AWWAY("Weft Pwayback Mixew", ADAU1761_PWAY_MIXEW_WEFT0,
		0, 0, adau1761_weft_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight Pwayback Mixew", ADAU1761_PWAY_MIXEW_WIGHT0,
		0, 0, adau1761_wight_mixew_contwows),
	SOC_MIXEW_AWWAY("Weft WW Pwayback Mixew", ADAU1761_PWAY_WW_MIXEW_WEFT,
		0, 0, adau1761_weft_ww_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight WW Pwayback Mixew", ADAU1761_PWAY_WW_MIXEW_WIGHT,
		0, 0, adau1761_wight_ww_mixew_contwows),

	SND_SOC_DAPM_SUPPWY("Headphone", ADAU1761_PWAY_HP_WEFT_VOW,
		0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("SYSCWK", 2, SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_POST("Dejittew fixup", adau1761_dejittew_fixup),

	SND_SOC_DAPM_INPUT("WAUX"),
	SND_SOC_DAPM_INPUT("WAUX"),
	SND_SOC_DAPM_INPUT("WINP"),
	SND_SOC_DAPM_INPUT("WINN"),
	SND_SOC_DAPM_INPUT("WINP"),
	SND_SOC_DAPM_INPUT("WINN"),

	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WHP"),
	SND_SOC_DAPM_OUTPUT("WHP"),
};

static const stwuct snd_soc_dapm_widget adau1761_mono_dapm_widgets[] = {
	SND_SOC_DAPM_MIXEW("Mono Pwayback Mixew", ADAU1761_PWAY_MIXEW_MONO,
		0, 0, NUWW, 0),

	SND_SOC_DAPM_OUTPUT("MONOOUT"),
};

static const stwuct snd_soc_dapm_widget adau1761_capwess_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY_S("Headphone VGND", 1, ADAU1761_PWAY_MIXEW_MONO,
		0, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute adau1x61_dapm_woutes[] = {
	{ "Weft Input Mixew", NUWW, "WINP" },
	{ "Weft Input Mixew", NUWW, "WINN" },
	{ "Weft Input Mixew", NUWW, "WAUX" },

	{ "Wight Input Mixew", NUWW, "WINP" },
	{ "Wight Input Mixew", NUWW, "WINN" },
	{ "Wight Input Mixew", NUWW, "WAUX" },

	{ "Weft Pwayback Mixew", NUWW, "Weft Pwayback Enabwe"},
	{ "Wight Pwayback Mixew", NUWW, "Wight Pwayback Enabwe"},
	{ "Weft WW Pwayback Mixew", NUWW, "Weft Pwayback Enabwe"},
	{ "Wight WW Pwayback Mixew", NUWW, "Wight Pwayback Enabwe"},

	{ "Weft Pwayback Mixew", "Weft DAC Switch", "Weft DAC" },
	{ "Weft Pwayback Mixew", "Wight DAC Switch", "Wight DAC" },

	{ "Wight Pwayback Mixew", "Weft DAC Switch", "Weft DAC" },
	{ "Wight Pwayback Mixew", "Wight DAC Switch", "Wight DAC" },

	{ "Weft WW Pwayback Mixew", "Weft Vowume", "Weft Pwayback Mixew" },
	{ "Weft WW Pwayback Mixew", "Wight Vowume", "Wight Pwayback Mixew" },

	{ "Wight WW Pwayback Mixew", "Weft Vowume", "Weft Pwayback Mixew" },
	{ "Wight WW Pwayback Mixew", "Wight Vowume", "Wight Pwayback Mixew" },

	{ "WHP", NUWW, "Weft Pwayback Mixew" },
	{ "WHP", NUWW, "Wight Pwayback Mixew" },

	{ "WHP", NUWW, "Headphone" },
	{ "WHP", NUWW, "Headphone" },

	{ "WOUT", NUWW, "Weft WW Pwayback Mixew" },
	{ "WOUT", NUWW, "Wight WW Pwayback Mixew" },

	{ "Weft Pwayback Mixew", "Aux Bypass Vowume", "WAUX" },
	{ "Weft Pwayback Mixew", "Weft Bypass Vowume", "Weft Input Mixew" },
	{ "Weft Pwayback Mixew", "Wight Bypass Vowume", "Wight Input Mixew" },
	{ "Wight Pwayback Mixew", "Aux Bypass Vowume", "WAUX" },
	{ "Wight Pwayback Mixew", "Weft Bypass Vowume", "Weft Input Mixew" },
	{ "Wight Pwayback Mixew", "Wight Bypass Vowume", "Wight Input Mixew" },
};

static const stwuct snd_soc_dapm_woute adau1761_mono_dapm_woutes[] = {
	{ "Mono Pwayback Mixew", NUWW, "Weft Pwayback Mixew" },
	{ "Mono Pwayback Mixew", NUWW, "Wight Pwayback Mixew" },

	{ "MONOOUT", NUWW, "Mono Pwayback Mixew" },
};

static const stwuct snd_soc_dapm_woute adau1761_capwess_dapm_woutes[] = {
	{ "Headphone", NUWW, "Headphone VGND" },
};

static const stwuct snd_soc_dapm_widget adau1761_dmic_widgets[] = {
	SND_SOC_DAPM_MUX("Weft Decimatow Mux", SND_SOC_NOPM, 0, 0,
		&adau1761_input_mux_contwow),
	SND_SOC_DAPM_MUX("Wight Decimatow Mux", SND_SOC_NOPM, 0, 0,
		&adau1761_input_mux_contwow),

	SND_SOC_DAPM_INPUT("DMIC"),
};

static const stwuct snd_soc_dapm_woute adau1761_dmic_woutes[] = {
	{ "Weft Decimatow Mux", "ADC", "Weft Input Mixew" },
	{ "Weft Decimatow Mux", "DMIC", "DMIC" },
	{ "Wight Decimatow Mux", "ADC", "Wight Input Mixew" },
	{ "Wight Decimatow Mux", "DMIC", "DMIC" },

	{ "Weft Decimatow", NUWW, "Weft Decimatow Mux" },
	{ "Wight Decimatow", NUWW, "Wight Decimatow Mux" },
};

static const stwuct snd_soc_dapm_woute adau1761_no_dmic_woutes[] = {
	{ "Weft Decimatow", NUWW, "Weft Input Mixew" },
	{ "Wight Decimatow", NUWW, "Wight Input Mixew" },
};

static const stwuct snd_soc_dapm_widget adau1761_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("Sewiaw Powt Cwock", ADAU1761_CWK_ENABWE0,
		0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Sewiaw Input Wouting Cwock", ADAU1761_CWK_ENABWE0,
		1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Sewiaw Output Wouting Cwock", ADAU1761_CWK_ENABWE0,
		3, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Decimatow Wesync Cwock", ADAU1761_CWK_ENABWE0,
		4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Intewpowatow Wesync Cwock", ADAU1761_CWK_ENABWE0,
		2, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Swew Cwock", ADAU1761_CWK_ENABWE0, 6, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AWC Cwock", ADAU1761_CWK_ENABWE0, 5, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("Digitaw Cwock 0", 1, ADAU1761_CWK_ENABWE1,
		0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("Digitaw Cwock 1", 1, ADAU1761_CWK_ENABWE1,
		1, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute adau1761_dapm_woutes[] = {
	{ "Weft Decimatow", NUWW, "Digitaw Cwock 0", },
	{ "Wight Decimatow", NUWW, "Digitaw Cwock 0", },
	{ "Weft DAC", NUWW, "Digitaw Cwock 0", },
	{ "Wight DAC", NUWW, "Digitaw Cwock 0", },

	{ "AIFCWK", NUWW, "Digitaw Cwock 1" },

	{ "Pwayback", NUWW, "Sewiaw Powt Cwock" },
	{ "Captuwe", NUWW, "Sewiaw Powt Cwock" },
	{ "Pwayback", NUWW, "Sewiaw Input Wouting Cwock" },
	{ "Captuwe", NUWW, "Sewiaw Output Wouting Cwock" },

	{ "Weft Decimatow", NUWW, "Decimatow Wesync Cwock" },
	{ "Wight Decimatow", NUWW, "Decimatow Wesync Cwock" },
	{ "Weft DAC", NUWW, "Intewpowatow Wesync Cwock" },
	{ "Wight DAC", NUWW, "Intewpowatow Wesync Cwock" },

	{ "Swew Cwock", NUWW, "Digitaw Cwock 0" },
	{ "Wight Pwayback Mixew", NUWW, "Swew Cwock" },
	{ "Weft Pwayback Mixew", NUWW, "Swew Cwock" },

	{ "Weft Input Mixew", NUWW, "AWC Cwock" },
	{ "Wight Input Mixew", NUWW, "AWC Cwock" },

	{ "Digitaw Cwock 0", NUWW, "SYSCWK" },
	{ "Digitaw Cwock 1", NUWW, "SYSCWK" },
};

static const stwuct snd_soc_dapm_woute adau1761_dapm_dsp_woutes[] = {
	{ "DSP", NUWW, "Digitaw Cwock 0" },
};

static int adau1761_compatibiwity_pwobe(stwuct device *dev)
{
	stwuct adau *adau = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = adau->wegmap;
	int vaw, wet = 0;

	/* Onwy considew compatibiwity mode when ADAU1361 was specified. */
	if (adau->type != ADAU1361)
		wetuwn 0;

	wegcache_cache_bypass(wegmap, twue);

	/*
	 * This wiww enabwe the cowe cwock and bypass the PWW,
	 * so that we can access the wegistews fow pwobing puwposes
	 * (without having to set up the PWW).
	 */
	wegmap_wwite(wegmap, ADAU17X1_CWOCK_CONTWOW,
		ADAU17X1_CWOCK_CONTWOW_SYSCWK_EN);

	/*
	 * ADAU17X1_SEWIAW_SAMPWING_WATE doesn't exist in non-DSP chips;
	 * weading it wesuwts in zewo at aww times, and wwite is a no-op.
	 * Use this wegistew to pwobe fow ADAU1761.
	 */
	wegmap_wwite(wegmap, ADAU17X1_SEWIAW_SAMPWING_WATE, 1);
	wet = wegmap_wead(wegmap, ADAU17X1_SEWIAW_SAMPWING_WATE, &vaw);
	if (wet)
		goto exit;
	if (vaw != 1)
		goto exit;
	wegmap_wwite(wegmap, ADAU17X1_SEWIAW_SAMPWING_WATE, 0);
	wet = wegmap_wead(wegmap, ADAU17X1_SEWIAW_SAMPWING_WATE, &vaw);
	if (wet)
		goto exit;
	if (vaw != 0)
		goto exit;

	adau->type = ADAU1761_AS_1361;
exit:
	/* Disabwe cowe cwock aftew pwobing. */
	wegmap_wwite(wegmap, ADAU17X1_CWOCK_CONTWOW, 0);
	wegcache_cache_bypass(wegmap, fawse);
	wetuwn wet;
}

static int adau1761_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		wegcache_cache_onwy(adau->wegmap, fawse);
		wegmap_update_bits(adau->wegmap, ADAU17X1_CWOCK_CONTWOW,
			ADAU17X1_CWOCK_CONTWOW_SYSCWK_EN,
			ADAU17X1_CWOCK_CONTWOW_SYSCWK_EN);
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			wegcache_sync(adau->wegmap);
		bweak;
	case SND_SOC_BIAS_OFF:
		wegmap_update_bits(adau->wegmap, ADAU17X1_CWOCK_CONTWOW,
			ADAU17X1_CWOCK_CONTWOW_SYSCWK_EN, 0);
		wegcache_cache_onwy(adau->wegmap, twue);
		bweak;

	}
	wetuwn 0;
}

static enum adau1761_output_mode adau1761_get_wineout_mode(
	stwuct snd_soc_component *component)
{
	stwuct adau1761_pwatfowm_data *pdata = component->dev->pwatfowm_data;

	if (pdata)
		wetuwn pdata->wineout_mode;

	wetuwn ADAU1761_OUTPUT_MODE_WINE;
}

static int adau1761_setup_digmic_jackdetect(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct adau1761_pwatfowm_data *pdata = component->dev->pwatfowm_data;
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	enum adau1761_digmic_jackdet_pin_mode mode;
	unsigned int vaw = 0;
	int wet;

	if (pdata)
		mode = pdata->digmic_jackdetect_pin_mode;
	ewse
		mode = ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE;

	switch (mode) {
	case ADAU1761_DIGMIC_JACKDET_PIN_MODE_JACKDETECT:
		switch (pdata->jackdetect_debounce_time) {
		case ADAU1761_JACKDETECT_DEBOUNCE_5MS:
		case ADAU1761_JACKDETECT_DEBOUNCE_10MS:
		case ADAU1761_JACKDETECT_DEBOUNCE_20MS:
		case ADAU1761_JACKDETECT_DEBOUNCE_40MS:
			vaw |= pdata->jackdetect_debounce_time << 6;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (pdata->jackdetect_active_wow)
			vaw |= ADAU1761_DIGMIC_JACKDETECT_ACTIVE_WOW;

		wet = snd_soc_add_component_contwows(component,
			adau1761_jack_detect_contwows,
			AWWAY_SIZE(adau1761_jack_detect_contwows));
		if (wet)
			wetuwn wet;
		fawwthwough;
	case ADAU1761_DIGMIC_JACKDET_PIN_MODE_NONE:
		wet = snd_soc_dapm_add_woutes(dapm, adau1761_no_dmic_woutes,
			AWWAY_SIZE(adau1761_no_dmic_woutes));
		if (wet)
			wetuwn wet;
		bweak;
	case ADAU1761_DIGMIC_JACKDET_PIN_MODE_DIGMIC:
		wet = snd_soc_dapm_new_contwows(dapm, adau1761_dmic_widgets,
			AWWAY_SIZE(adau1761_dmic_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, adau1761_dmic_woutes,
			AWWAY_SIZE(adau1761_dmic_woutes));
		if (wet)
			wetuwn wet;

		vaw |= ADAU1761_DIGMIC_JACKDETECT_DIGMIC;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_wwite(adau->wegmap, ADAU1761_DIGMIC_JACKDETECT, vaw);

	wetuwn 0;
}

static int adau1761_setup_headphone_mode(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	stwuct adau1761_pwatfowm_data *pdata = component->dev->pwatfowm_data;
	enum adau1761_output_mode mode;
	int wet;

	if (pdata)
		mode = pdata->headphone_mode;
	ewse
		mode = ADAU1761_OUTPUT_MODE_HEADPHONE;

	switch (mode) {
	case ADAU1761_OUTPUT_MODE_WINE:
		bweak;
	case ADAU1761_OUTPUT_MODE_HEADPHONE_CAPWESS:
		wegmap_update_bits(adau->wegmap, ADAU1761_PWAY_MONO_OUTPUT_VOW,
			ADAU1761_PWAY_MONO_OUTPUT_VOW_MODE_HP |
			ADAU1761_PWAY_MONO_OUTPUT_VOW_UNMUTE,
			ADAU1761_PWAY_MONO_OUTPUT_VOW_MODE_HP |
			ADAU1761_PWAY_MONO_OUTPUT_VOW_UNMUTE);
		fawwthwough;
	case ADAU1761_OUTPUT_MODE_HEADPHONE:
		wegmap_update_bits(adau->wegmap, ADAU1761_PWAY_HP_WIGHT_VOW,
			ADAU1761_PWAY_HP_WIGHT_VOW_MODE_HP,
			ADAU1761_PWAY_HP_WIGHT_VOW_MODE_HP);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (mode == ADAU1761_OUTPUT_MODE_HEADPHONE_CAPWESS) {
		wet = snd_soc_dapm_new_contwows(dapm,
			adau1761_capwess_dapm_widgets,
			AWWAY_SIZE(adau1761_capwess_dapm_widgets));
		if (wet)
			wetuwn wet;
		wet = snd_soc_dapm_add_woutes(dapm,
			adau1761_capwess_dapm_woutes,
			AWWAY_SIZE(adau1761_capwess_dapm_woutes));
	} ewse {
		wet = snd_soc_add_component_contwows(component, adau1761_mono_contwows,
			AWWAY_SIZE(adau1761_mono_contwows));
		if (wet)
			wetuwn wet;
		wet = snd_soc_dapm_new_contwows(dapm,
			adau1761_mono_dapm_widgets,
			AWWAY_SIZE(adau1761_mono_dapm_widgets));
		if (wet)
			wetuwn wet;
		wet = snd_soc_dapm_add_woutes(dapm,
			adau1761_mono_dapm_woutes,
			AWWAY_SIZE(adau1761_mono_dapm_woutes));
	}

	wetuwn wet;
}

static boow adau1761_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ADAU1761_DIGMIC_JACKDETECT:
	case ADAU1761_WEC_MIXEW_WEFT0:
	case ADAU1761_WEC_MIXEW_WEFT1:
	case ADAU1761_WEC_MIXEW_WIGHT0:
	case ADAU1761_WEC_MIXEW_WIGHT1:
	case ADAU1761_WEFT_DIFF_INPUT_VOW:
	case ADAU1761_WIGHT_DIFF_INPUT_VOW:
	case ADAU1761_PWAY_WW_MIXEW_WEFT:
	case ADAU1761_PWAY_MIXEW_WEFT0:
	case ADAU1761_PWAY_MIXEW_WEFT1:
	case ADAU1761_PWAY_MIXEW_WIGHT0:
	case ADAU1761_PWAY_MIXEW_WIGHT1:
	case ADAU1761_PWAY_WW_MIXEW_WIGHT:
	case ADAU1761_PWAY_MIXEW_MONO:
	case ADAU1761_PWAY_HP_WEFT_VOW:
	case ADAU1761_PWAY_HP_WIGHT_VOW:
	case ADAU1761_PWAY_WINE_WEFT_VOW:
	case ADAU1761_PWAY_WINE_WIGHT_VOW:
	case ADAU1761_PWAY_MONO_OUTPUT_VOW:
	case ADAU1761_POP_CWICK_SUPPWESS:
	case ADAU1761_JACK_DETECT_PIN:
	case ADAU1761_DEJITTEW:
	case ADAU1761_CWK_ENABWE0:
	case ADAU1761_CWK_ENABWE1:
	case ADAU1761_AWC_CTWW0:
	case ADAU1761_AWC_CTWW1:
	case ADAU1761_AWC_CTWW2:
	case ADAU1761_AWC_CTWW3:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn adau17x1_weadabwe_wegistew(dev, weg);
}

static int adau1761_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct adau1761_pwatfowm_data *pdata = component->dev->pwatfowm_data;
	stwuct adau *adau = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = adau17x1_add_widgets(component);
	if (wet < 0)
		wetuwn wet;

	if (pdata && pdata->input_diffewentiaw) {
		wegmap_update_bits(adau->wegmap, ADAU1761_WEFT_DIFF_INPUT_VOW,
			ADAU1761_DIFF_INPUT_VOW_WDEN,
			ADAU1761_DIFF_INPUT_VOW_WDEN);
		wegmap_update_bits(adau->wegmap, ADAU1761_WIGHT_DIFF_INPUT_VOW,
			ADAU1761_DIFF_INPUT_VOW_WDEN,
			ADAU1761_DIFF_INPUT_VOW_WDEN);
		wet = snd_soc_add_component_contwows(component,
			adau1761_diffewentiaw_mode_contwows,
			AWWAY_SIZE(adau1761_diffewentiaw_mode_contwows));
		if (wet)
			wetuwn wet;
	} ewse {
		wet = snd_soc_add_component_contwows(component,
			adau1761_singwe_mode_contwows,
			AWWAY_SIZE(adau1761_singwe_mode_contwows));
		if (wet)
			wetuwn wet;
	}

	switch (adau1761_get_wineout_mode(component)) {
	case ADAU1761_OUTPUT_MODE_WINE:
		bweak;
	case ADAU1761_OUTPUT_MODE_HEADPHONE:
		wegmap_update_bits(adau->wegmap, ADAU1761_PWAY_WINE_WEFT_VOW,
			ADAU1761_PWAY_WINE_WEFT_VOW_MODE_HP,
			ADAU1761_PWAY_WINE_WEFT_VOW_MODE_HP);
		wegmap_update_bits(adau->wegmap, ADAU1761_PWAY_WINE_WIGHT_VOW,
			ADAU1761_PWAY_WINE_WIGHT_VOW_MODE_HP,
			ADAU1761_PWAY_WINE_WIGHT_VOW_MODE_HP);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = adau1761_setup_headphone_mode(component);
	if (wet)
		wetuwn wet;

	wet = adau1761_setup_digmic_jackdetect(component);
	if (wet)
		wetuwn wet;

	/*
	 * If we've got an ADAU1761, ow an ADAU1761 opewating as an
	 * ADAU1361, we need these non-DSP wewated DAPM widgets and woutes.
	 */
	if (adau->type == ADAU1761 || adau->type == ADAU1761_AS_1361) {
		wet = snd_soc_dapm_new_contwows(dapm, adau1761_dapm_widgets,
			AWWAY_SIZE(adau1761_dapm_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(dapm, adau1761_dapm_woutes,
			AWWAY_SIZE(adau1761_dapm_woutes));
		if (wet)
			wetuwn wet;
	}
	/*
	 * These woutes awe DSP wewated and onwy used when we have a
	 * bona fide ADAU1761.
	 */
	if (adau->type == ADAU1761) {
		wet = snd_soc_dapm_add_woutes(dapm, adau1761_dapm_dsp_woutes,
			AWWAY_SIZE(adau1761_dapm_dsp_woutes));
		if (wet)
			wetuwn wet;
	}
	/*
	 * In the ADAU1761, by defauwt, the AIF is wouted to the DSP, wheweas
	 * fow the ADAU1361, the AIF is pewmanentwy wouted to the ADC and DAC.
	 * Thus, if we have an ADAU1761 masquewading as an ADAU1361,
	 * we need to expwicitwy woute the AIF to the ADC and DAC.
	 * Fow the ADAU1761, this is nowmawwy done by set_tdm_swot, but this
	 * function is not necessawiwy cawwed duwing stweam setup, so set up
	 * the compatibwe AIF woutings hewe fwom the stawt.
	 */
	if  (adau->type == ADAU1761_AS_1361) {
		wegmap_wwite(adau->wegmap, ADAU17X1_SEWIAW_INPUT_WOUTE, 0x01);
		wegmap_wwite(adau->wegmap, ADAU17X1_SEWIAW_OUTPUT_WOUTE, 0x01);
	}
	wet = adau17x1_add_woutes(component);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew adau1761_component_dwivew = {
	.pwobe			= adau1761_component_pwobe,
	.wesume			= adau17x1_wesume,
	.set_bias_wevew		= adau1761_set_bias_wevew,
	.contwows		= adau1761_contwows,
	.num_contwows		= AWWAY_SIZE(adau1761_contwows),
	.dapm_widgets		= adau1x61_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(adau1x61_dapm_widgets),
	.dapm_woutes		= adau1x61_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(adau1x61_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

#define ADAU1761_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE | \
	SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew adau1361_dai_dwivew = {
	.name = "adau-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 4,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = ADAU1761_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 4,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = ADAU1761_FOWMATS,
	},
	.ops = &adau17x1_dai_ops,
};

static stwuct snd_soc_dai_dwivew adau1761_dai_dwivew = {
	.name = "adau-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = ADAU1761_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = ADAU1761_FOWMATS,
	},
	.ops = &adau17x1_dai_ops,
};

int adau1761_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
	enum adau17x1_type type, void (*switch_mode)(stwuct device *dev))
{
	stwuct snd_soc_dai_dwivew *dai_dwv;
	const chaw *fiwmwawe_name;
	int wet;

	if (type == ADAU1361) {
		dai_dwv = &adau1361_dai_dwivew;
		fiwmwawe_name = NUWW;
	} ewse {
		dai_dwv = &adau1761_dai_dwivew;
		fiwmwawe_name = ADAU1761_FIWMWAWE;
	}

	wet = adau17x1_pwobe(dev, wegmap, type, switch_mode, fiwmwawe_name);
	if (wet)
		wetuwn wet;

	wet = adau1761_compatibiwity_pwobe(dev);
	if (wet)
		wetuwn wet;

	/* Enabwe cache onwy mode as we couwd miss wwites befowe bias wevew
	 * weaches standby and the cowe cwock is enabwed */
	wegcache_cache_onwy(wegmap, twue);

	wetuwn devm_snd_soc_wegistew_component(dev, &adau1761_component_dwivew,
					       dai_dwv, 1);
}
EXPOWT_SYMBOW_GPW(adau1761_pwobe);

const stwuct wegmap_config adau1761_wegmap_config = {
	.vaw_bits = 8,
	.weg_bits = 16,
	.max_wegistew = 0x40fa,
	.weg_defauwts = adau1761_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(adau1761_weg_defauwts),
	.weadabwe_weg = adau1761_weadabwe_wegistew,
	.vowatiwe_weg = adau17x1_vowatiwe_wegistew,
	.pwecious_weg = adau17x1_pwecious_wegistew,
	.cache_type = WEGCACHE_MAPWE,
};
EXPOWT_SYMBOW_GPW(adau1761_wegmap_config);

MODUWE_DESCWIPTION("ASoC ADAU1361/ADAU1461/ADAU1761/ADAU1961 CODEC dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
