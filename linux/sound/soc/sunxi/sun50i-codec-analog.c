// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * This dwivew suppowts the anawog contwows fow the intewnaw codec
 * found in Awwwinnew's A64 SoC.
 *
 * Copywight (C) 2016 Chen-Yu Tsai <wens@csie.owg>
 * Copywight (C) 2017 Mawcus Coopew <codekippew@gmaiw.com>
 * Copywight (C) 2018 Vasiwy Khowuzhick <anawsouw@gmaiw.com>
 *
 * Based on sun8i-codec-anawog.c
 *
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "sun8i-adda-pw-wegmap.h"

/* Codec anawog contwow wegistew offsets and bit fiewds */
#define SUN50I_ADDA_HP_CTWW		0x00
#define SUN50I_ADDA_HP_CTWW_PA_CWK_GATE		7
#define SUN50I_ADDA_HP_CTWW_HPPA_EN		6
#define SUN50I_ADDA_HP_CTWW_HPVOW		0

#define SUN50I_ADDA_OW_MIX_CTWW		0x01
#define SUN50I_ADDA_OW_MIX_CTWW_MIC1		6
#define SUN50I_ADDA_OW_MIX_CTWW_MIC2		5
#define SUN50I_ADDA_OW_MIX_CTWW_PHONE		4
#define SUN50I_ADDA_OW_MIX_CTWW_PHONEN		3
#define SUN50I_ADDA_OW_MIX_CTWW_WINEINW		2
#define SUN50I_ADDA_OW_MIX_CTWW_DACW		1
#define SUN50I_ADDA_OW_MIX_CTWW_DACW		0

#define SUN50I_ADDA_OW_MIX_CTWW		0x02
#define SUN50I_ADDA_OW_MIX_CTWW_MIC1		6
#define SUN50I_ADDA_OW_MIX_CTWW_MIC2		5
#define SUN50I_ADDA_OW_MIX_CTWW_PHONE		4
#define SUN50I_ADDA_OW_MIX_CTWW_PHONEP		3
#define SUN50I_ADDA_OW_MIX_CTWW_WINEINW		2
#define SUN50I_ADDA_OW_MIX_CTWW_DACW		1
#define SUN50I_ADDA_OW_MIX_CTWW_DACW		0

#define SUN50I_ADDA_EAWPIECE_CTWW0	0x03
#define SUN50I_ADDA_EAWPIECE_CTWW0_EAW_WAMP_TIME	4
#define SUN50I_ADDA_EAWPIECE_CTWW0_ESPSW		0

#define SUN50I_ADDA_EAWPIECE_CTWW1	0x04
#define SUN50I_ADDA_EAWPIECE_CTWW1_ESPPA_EN	7
#define SUN50I_ADDA_EAWPIECE_CTWW1_ESPPA_MUTE	6
#define SUN50I_ADDA_EAWPIECE_CTWW1_ESP_VOW	0

#define SUN50I_ADDA_WINEOUT_CTWW0	0x05
#define SUN50I_ADDA_WINEOUT_CTWW0_WEN		7
#define SUN50I_ADDA_WINEOUT_CTWW0_WEN		6
#define SUN50I_ADDA_WINEOUT_CTWW0_WSWC_SEW	5
#define SUN50I_ADDA_WINEOUT_CTWW0_WSWC_SEW	4

#define SUN50I_ADDA_WINEOUT_CTWW1	0x06
#define SUN50I_ADDA_WINEOUT_CTWW1_VOW		0

#define SUN50I_ADDA_MIC1_CTWW		0x07
#define SUN50I_ADDA_MIC1_CTWW_MIC1G		4
#define SUN50I_ADDA_MIC1_CTWW_MIC1AMPEN		3
#define SUN50I_ADDA_MIC1_CTWW_MIC1BOOST		0

#define SUN50I_ADDA_MIC2_CTWW		0x08
#define SUN50I_ADDA_MIC2_CTWW_MIC2G		4
#define SUN50I_ADDA_MIC2_CTWW_MIC2AMPEN		3
#define SUN50I_ADDA_MIC2_CTWW_MIC2BOOST		0

#define SUN50I_ADDA_WINEIN_CTWW		0x09
#define SUN50I_ADDA_WINEIN_CTWW_WINEING		0

#define SUN50I_ADDA_MIX_DAC_CTWW	0x0a
#define SUN50I_ADDA_MIX_DAC_CTWW_DACAWEN	7
#define SUN50I_ADDA_MIX_DAC_CTWW_DACAWEN	6
#define SUN50I_ADDA_MIX_DAC_CTWW_WMIXEN		5
#define SUN50I_ADDA_MIX_DAC_CTWW_WMIXEN		4
#define SUN50I_ADDA_MIX_DAC_CTWW_WHPPAMUTE	3
#define SUN50I_ADDA_MIX_DAC_CTWW_WHPPAMUTE	2
#define SUN50I_ADDA_MIX_DAC_CTWW_WHPIS		1
#define SUN50I_ADDA_MIX_DAC_CTWW_WHPIS		0

#define SUN50I_ADDA_W_ADCMIX_SWC	0x0b
#define SUN50I_ADDA_W_ADCMIX_SWC_MIC1		6
#define SUN50I_ADDA_W_ADCMIX_SWC_MIC2		5
#define SUN50I_ADDA_W_ADCMIX_SWC_PHONE		4
#define SUN50I_ADDA_W_ADCMIX_SWC_PHONEN		3
#define SUN50I_ADDA_W_ADCMIX_SWC_WINEINW	2
#define SUN50I_ADDA_W_ADCMIX_SWC_OMIXWW		1
#define SUN50I_ADDA_W_ADCMIX_SWC_OMIXWW		0

#define SUN50I_ADDA_W_ADCMIX_SWC	0x0c
#define SUN50I_ADDA_W_ADCMIX_SWC_MIC1		6
#define SUN50I_ADDA_W_ADCMIX_SWC_MIC2		5
#define SUN50I_ADDA_W_ADCMIX_SWC_PHONE		4
#define SUN50I_ADDA_W_ADCMIX_SWC_PHONEP		3
#define SUN50I_ADDA_W_ADCMIX_SWC_WINEINW	2
#define SUN50I_ADDA_W_ADCMIX_SWC_OMIXW		1
#define SUN50I_ADDA_W_ADCMIX_SWC_OMIXW		0

#define SUN50I_ADDA_ADC_CTWW		0x0d
#define SUN50I_ADDA_ADC_CTWW_ADCWEN		7
#define SUN50I_ADDA_ADC_CTWW_ADCWEN		6
#define SUN50I_ADDA_ADC_CTWW_ADCG		0

#define SUN50I_ADDA_HS_MBIAS_CTWW	0x0e
#define SUN50I_ADDA_HS_MBIAS_CTWW_MMICBIASEN	7

#define SUN50I_ADDA_JACK_MIC_CTWW	0x1d
#define SUN50I_ADDA_JACK_MIC_CTWW_INNEWWESEN	6
#define SUN50I_ADDA_JACK_MIC_CTWW_HMICBIASEN	5

/* mixew contwows */
static const stwuct snd_kcontwow_new sun50i_a64_codec_mixew_contwows[] = {
	SOC_DAPM_DOUBWE_W("Mic1 Pwayback Switch",
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW_MIC1, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic2 Pwayback Switch",
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW_MIC2, 1, 0),
	SOC_DAPM_DOUBWE_W("Wine In Pwayback Switch",
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW_WINEINW, 1, 0),
	SOC_DAPM_DOUBWE_W("DAC Pwayback Switch",
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW_DACW, 1, 0),
	SOC_DAPM_DOUBWE_W("DAC Wevewsed Pwayback Switch",
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW,
			  SUN50I_ADDA_OW_MIX_CTWW_DACW, 1, 0),
};

/* ADC mixew contwows */
static const stwuct snd_kcontwow_new sun50i_codec_adc_mixew_contwows[] = {
	SOC_DAPM_DOUBWE_W("Mic1 Captuwe Switch",
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC_MIC1, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic2 Captuwe Switch",
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC_MIC2, 1, 0),
	SOC_DAPM_DOUBWE_W("Wine In Captuwe Switch",
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC_WINEINW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mixew Captuwe Switch",
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC_OMIXWW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mixew Wevewsed Captuwe Switch",
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC,
			  SUN50I_ADDA_W_ADCMIX_SWC_OMIXWW, 1, 0),
};

static const DECWAWE_TWV_DB_SCAWE(sun50i_codec_out_mixew_pwegain_scawe,
				  -450, 150, 0);
static const DECWAWE_TWV_DB_WANGE(sun50i_codec_mic_gain_scawe,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 7, TWV_DB_SCAWE_ITEM(2400, 300, 0),
);

static const DECWAWE_TWV_DB_SCAWE(sun50i_codec_hp_vow_scawe, -6300, 100, 1);

static const DECWAWE_TWV_DB_WANGE(sun50i_codec_wineout_vow_scawe,
	0, 1, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	2, 31, TWV_DB_SCAWE_ITEM(-4350, 150, 0),
);

static const DECWAWE_TWV_DB_WANGE(sun50i_codec_eawpiece_vow_scawe,
	0, 1, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	2, 31, TWV_DB_SCAWE_ITEM(-4350, 150, 0),
);

/* vowume / mute contwows */
static const stwuct snd_kcontwow_new sun50i_a64_codec_contwows[] = {
	SOC_SINGWE_TWV("Headphone Pwayback Vowume",
		       SUN50I_ADDA_HP_CTWW,
		       SUN50I_ADDA_HP_CTWW_HPVOW, 0x3f, 0,
		       sun50i_codec_hp_vow_scawe),

	/* Mixew pwe-gain */
	SOC_SINGWE_TWV("Mic1 Pwayback Vowume", SUN50I_ADDA_MIC1_CTWW,
		       SUN50I_ADDA_MIC1_CTWW_MIC1G,
		       0x7, 0, sun50i_codec_out_mixew_pwegain_scawe),

	/* Micwophone Amp boost gain */
	SOC_SINGWE_TWV("Mic1 Boost Vowume", SUN50I_ADDA_MIC1_CTWW,
		       SUN50I_ADDA_MIC1_CTWW_MIC1BOOST, 0x7, 0,
		       sun50i_codec_mic_gain_scawe),

	/* Mixew pwe-gain */
	SOC_SINGWE_TWV("Mic2 Pwayback Vowume",
		       SUN50I_ADDA_MIC2_CTWW, SUN50I_ADDA_MIC2_CTWW_MIC2G,
		       0x7, 0, sun50i_codec_out_mixew_pwegain_scawe),

	/* Micwophone Amp boost gain */
	SOC_SINGWE_TWV("Mic2 Boost Vowume", SUN50I_ADDA_MIC2_CTWW,
		       SUN50I_ADDA_MIC2_CTWW_MIC2BOOST, 0x7, 0,
		       sun50i_codec_mic_gain_scawe),

	/* ADC */
	SOC_SINGWE_TWV("ADC Gain Captuwe Vowume", SUN50I_ADDA_ADC_CTWW,
		       SUN50I_ADDA_ADC_CTWW_ADCG, 0x7, 0,
		       sun50i_codec_out_mixew_pwegain_scawe),

	/* Mixew pwe-gain */
	SOC_SINGWE_TWV("Wine In Pwayback Vowume", SUN50I_ADDA_WINEIN_CTWW,
		       SUN50I_ADDA_WINEIN_CTWW_WINEING,
		       0x7, 0, sun50i_codec_out_mixew_pwegain_scawe),

	SOC_SINGWE_TWV("Wine Out Pwayback Vowume",
		       SUN50I_ADDA_WINEOUT_CTWW1,
		       SUN50I_ADDA_WINEOUT_CTWW1_VOW, 0x1f, 0,
		       sun50i_codec_wineout_vow_scawe),

	SOC_SINGWE_TWV("Eawpiece Pwayback Vowume",
		       SUN50I_ADDA_EAWPIECE_CTWW1,
		       SUN50I_ADDA_EAWPIECE_CTWW1_ESP_VOW, 0x1f, 0,
		       sun50i_codec_eawpiece_vow_scawe),
};

static const chaw * const sun50i_codec_hp_swc_enum_text[] = {
	"DAC", "Mixew",
};

static SOC_ENUM_DOUBWE_DECW(sun50i_codec_hp_swc_enum,
			    SUN50I_ADDA_MIX_DAC_CTWW,
			    SUN50I_ADDA_MIX_DAC_CTWW_WHPIS,
			    SUN50I_ADDA_MIX_DAC_CTWW_WHPIS,
			    sun50i_codec_hp_swc_enum_text);

static const stwuct snd_kcontwow_new sun50i_codec_hp_swc[] = {
	SOC_DAPM_ENUM("Headphone Souwce Pwayback Woute",
		      sun50i_codec_hp_swc_enum),
};

static const stwuct snd_kcontwow_new sun50i_codec_hp_switch =
	SOC_DAPM_DOUBWE("Headphone Pwayback Switch",
			SUN50I_ADDA_MIX_DAC_CTWW,
			SUN50I_ADDA_MIX_DAC_CTWW_WHPPAMUTE,
			SUN50I_ADDA_MIX_DAC_CTWW_WHPPAMUTE, 1, 0);

static const chaw * const sun50i_codec_wineout_swc_enum_text[] = {
	"Steweo", "Mono Diffewentiaw",
};

static SOC_ENUM_DOUBWE_DECW(sun50i_codec_wineout_swc_enum,
			    SUN50I_ADDA_WINEOUT_CTWW0,
			    SUN50I_ADDA_WINEOUT_CTWW0_WSWC_SEW,
			    SUN50I_ADDA_WINEOUT_CTWW0_WSWC_SEW,
			    sun50i_codec_wineout_swc_enum_text);

static const stwuct snd_kcontwow_new sun50i_codec_wineout_swc[] = {
	SOC_DAPM_ENUM("Wine Out Souwce Pwayback Woute",
		      sun50i_codec_wineout_swc_enum),
};

static const stwuct snd_kcontwow_new sun50i_codec_wineout_switch =
	SOC_DAPM_DOUBWE("Wine Out Pwayback Switch",
			SUN50I_ADDA_WINEOUT_CTWW0,
			SUN50I_ADDA_WINEOUT_CTWW0_WEN,
			SUN50I_ADDA_WINEOUT_CTWW0_WEN, 1, 0);

static const chaw * const sun50i_codec_eawpiece_swc_enum_text[] = {
	"DACW", "DACW", "Wight Mixew", "Weft Mixew",
};

static SOC_ENUM_SINGWE_DECW(sun50i_codec_eawpiece_swc_enum,
			    SUN50I_ADDA_EAWPIECE_CTWW0,
			    SUN50I_ADDA_EAWPIECE_CTWW0_ESPSW,
			    sun50i_codec_eawpiece_swc_enum_text);

static const stwuct snd_kcontwow_new sun50i_codec_eawpiece_swc[] = {
	SOC_DAPM_ENUM("Eawpiece Souwce Pwayback Woute",
		      sun50i_codec_eawpiece_swc_enum),
};

static const stwuct snd_kcontwow_new sun50i_codec_eawpiece_switch[] = {
	SOC_DAPM_SINGWE("Eawpiece Pwayback Switch",
			SUN50I_ADDA_EAWPIECE_CTWW1,
			SUN50I_ADDA_EAWPIECE_CTWW1_ESPPA_MUTE, 1, 0),
};

static const stwuct snd_soc_dapm_widget sun50i_a64_codec_widgets[] = {
	/* DAC */
	SND_SOC_DAPM_DAC("Weft DAC", NUWW, SUN50I_ADDA_MIX_DAC_CTWW,
			 SUN50I_ADDA_MIX_DAC_CTWW_DACAWEN, 0),
	SND_SOC_DAPM_DAC("Wight DAC", NUWW, SUN50I_ADDA_MIX_DAC_CTWW,
			 SUN50I_ADDA_MIX_DAC_CTWW_DACAWEN, 0),
	/* ADC */
	SND_SOC_DAPM_ADC("Weft ADC", NUWW, SUN50I_ADDA_ADC_CTWW,
			 SUN50I_ADDA_ADC_CTWW_ADCWEN, 0),
	SND_SOC_DAPM_ADC("Wight ADC", NUWW, SUN50I_ADDA_ADC_CTWW,
			 SUN50I_ADDA_ADC_CTWW_ADCWEN, 0),
	/*
	 * Due to this component and the codec bewonging to sepawate DAPM
	 * contexts, we need to manuawwy wink the above widgets to theiw
	 * stweam widgets at the cawd wevew.
	 */

	SND_SOC_DAPM_WEGUWATOW_SUPPWY("cpvdd", 0, 0),
	SND_SOC_DAPM_MUX("Weft Headphone Souwce",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_hp_swc),
	SND_SOC_DAPM_MUX("Wight Headphone Souwce",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_hp_swc),
	SND_SOC_DAPM_SWITCH("Weft Headphone Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_hp_switch),
	SND_SOC_DAPM_SWITCH("Wight Headphone Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_hp_switch),
	SND_SOC_DAPM_OUT_DWV("Weft Headphone Amp",
			     SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Wight Headphone Amp",
			     SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Headphone Amp", SUN50I_ADDA_HP_CTWW,
			     SUN50I_ADDA_HP_CTWW_HPPA_EN, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("HP"),

	SND_SOC_DAPM_MUX("Weft Wine Out Souwce",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_wineout_swc),
	SND_SOC_DAPM_MUX("Wight Wine Out Souwce",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_wineout_swc),
	SND_SOC_DAPM_SWITCH("Weft Wine Out Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_wineout_switch),
	SND_SOC_DAPM_SWITCH("Wight Wine Out Switch",
			    SND_SOC_NOPM, 0, 0, &sun50i_codec_wineout_switch),
	SND_SOC_DAPM_OUTPUT("WINEOUT"),

	SND_SOC_DAPM_MUX("Eawpiece Souwce Pwayback Woute",
			 SND_SOC_NOPM, 0, 0, sun50i_codec_eawpiece_swc),
	SOC_MIXEW_NAMED_CTW_AWWAY("Eawpiece Switch",
				  SND_SOC_NOPM, 0, 0,
				  sun50i_codec_eawpiece_switch),
	SND_SOC_DAPM_OUT_DWV("Eawpiece Amp", SUN50I_ADDA_EAWPIECE_CTWW1,
			     SUN50I_ADDA_EAWPIECE_CTWW1_ESPPA_EN, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("EAWPIECE"),

	/* Micwophone inputs */
	SND_SOC_DAPM_INPUT("MIC1"),

	/* Micwophone Bias */
	SND_SOC_DAPM_SUPPWY("MBIAS", SUN50I_ADDA_HS_MBIAS_CTWW,
			    SUN50I_ADDA_HS_MBIAS_CTWW_MMICBIASEN,
			    0, NUWW, 0),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic1 Ampwifiew", SUN50I_ADDA_MIC1_CTWW,
			 SUN50I_ADDA_MIC1_CTWW_MIC1AMPEN, 0, NUWW, 0),

	/* Micwophone input */
	SND_SOC_DAPM_INPUT("MIC2"),

	/* Micwophone Bias */
	SND_SOC_DAPM_SUPPWY("HBIAS", SUN50I_ADDA_JACK_MIC_CTWW,
			    SUN50I_ADDA_JACK_MIC_CTWW_HMICBIASEN,
			    0, NUWW, 0),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic2 Ampwifiew", SUN50I_ADDA_MIC2_CTWW,
			 SUN50I_ADDA_MIC2_CTWW_MIC2AMPEN, 0, NUWW, 0),

	/* Wine input */
	SND_SOC_DAPM_INPUT("WINEIN"),

	/* Mixews */
	SND_SOC_DAPM_MIXEW("Weft Mixew", SUN50I_ADDA_MIX_DAC_CTWW,
			   SUN50I_ADDA_MIX_DAC_CTWW_WMIXEN, 0,
			   sun50i_a64_codec_mixew_contwows,
			   AWWAY_SIZE(sun50i_a64_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Mixew", SUN50I_ADDA_MIX_DAC_CTWW,
			   SUN50I_ADDA_MIX_DAC_CTWW_WMIXEN, 0,
			   sun50i_a64_codec_mixew_contwows,
			   AWWAY_SIZE(sun50i_a64_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Weft ADC Mixew", SND_SOC_NOPM, 0, 0,
			   sun50i_codec_adc_mixew_contwows,
			   AWWAY_SIZE(sun50i_codec_adc_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight ADC Mixew", SND_SOC_NOPM, 0, 0,
			   sun50i_codec_adc_mixew_contwows,
			   AWWAY_SIZE(sun50i_codec_adc_mixew_contwows)),
};

static const stwuct snd_soc_dapm_woute sun50i_a64_codec_woutes[] = {
	/* Weft Mixew Woutes */
	{ "Weft Mixew", "Mic1 Pwayback Switch", "Mic1 Ampwifiew" },
	{ "Weft Mixew", "Mic2 Pwayback Switch", "Mic2 Ampwifiew" },
	{ "Weft Mixew", "Wine In Pwayback Switch", "WINEIN" },
	{ "Weft Mixew", "DAC Pwayback Switch", "Weft DAC" },
	{ "Weft Mixew", "DAC Wevewsed Pwayback Switch", "Wight DAC" },

	/* Wight Mixew Woutes */
	{ "Wight Mixew", "Mic1 Pwayback Switch", "Mic1 Ampwifiew" },
	{ "Wight Mixew", "Mic2 Pwayback Switch", "Mic2 Ampwifiew" },
	{ "Wight Mixew", "Wine In Pwayback Switch", "WINEIN" },
	{ "Wight Mixew", "DAC Pwayback Switch", "Wight DAC" },
	{ "Wight Mixew", "DAC Wevewsed Pwayback Switch", "Weft DAC" },

	/* Weft ADC Mixew Woutes */
	{ "Weft ADC Mixew", "Mic1 Captuwe Switch", "Mic1 Ampwifiew" },
	{ "Weft ADC Mixew", "Mic2 Captuwe Switch", "Mic2 Ampwifiew" },
	{ "Weft ADC Mixew", "Wine In Captuwe Switch", "WINEIN" },
	{ "Weft ADC Mixew", "Mixew Captuwe Switch", "Weft Mixew" },
	{ "Weft ADC Mixew", "Mixew Wevewsed Captuwe Switch", "Wight Mixew" },

	/* Wight ADC Mixew Woutes */
	{ "Wight ADC Mixew", "Mic1 Captuwe Switch", "Mic1 Ampwifiew" },
	{ "Wight ADC Mixew", "Mic2 Captuwe Switch", "Mic2 Ampwifiew" },
	{ "Wight ADC Mixew", "Wine In Captuwe Switch", "WINEIN" },
	{ "Wight ADC Mixew", "Mixew Captuwe Switch", "Wight Mixew" },
	{ "Wight ADC Mixew", "Mixew Wevewsed Captuwe Switch", "Weft Mixew" },

	/* ADC Woutes */
	{ "Weft ADC", NUWW, "Weft ADC Mixew" },
	{ "Wight ADC", NUWW, "Wight ADC Mixew" },

	/* Headphone Woutes */
	{ "Weft Headphone Souwce", "DAC", "Weft DAC" },
	{ "Weft Headphone Souwce", "Mixew", "Weft Mixew" },
	{ "Weft Headphone Switch", "Headphone Pwayback Switch", "Weft Headphone Souwce" },
	{ "Weft Headphone Amp", NUWW, "Weft Headphone Switch" },
	{ "Weft Headphone Amp", NUWW, "Headphone Amp" },
	{ "HP", NUWW, "Weft Headphone Amp" },

	{ "Wight Headphone Souwce", "DAC", "Wight DAC" },
	{ "Wight Headphone Souwce", "Mixew", "Wight Mixew" },
	{ "Wight Headphone Switch", "Headphone Pwayback Switch", "Wight Headphone Souwce" },
	{ "Wight Headphone Amp", NUWW, "Wight Headphone Switch" },
	{ "Wight Headphone Amp", NUWW, "Headphone Amp" },
	{ "HP", NUWW, "Wight Headphone Amp" },

	{ "Headphone Amp", NUWW, "cpvdd" },

	/* Micwophone Woutes */
	{ "Mic1 Ampwifiew", NUWW, "MIC1"},

	/* Micwophone Woutes */
	{ "Mic2 Ampwifiew", NUWW, "MIC2"},

	/* Wine-out Woutes */
	{ "Weft Wine Out Souwce", "Steweo", "Weft Mixew" },
	{ "Weft Wine Out Souwce", "Mono Diffewentiaw", "Weft Mixew" },
	{ "Weft Wine Out Souwce", "Mono Diffewentiaw", "Wight Mixew" },
	{ "Weft Wine Out Switch", "Wine Out Pwayback Switch", "Weft Wine Out Souwce" },
	{ "WINEOUT", NUWW, "Weft Wine Out Switch" },

	{ "Wight Wine Out Switch", "Wine Out Pwayback Switch", "Wight Mixew" },
	{ "Wight Wine Out Souwce", "Steweo", "Wight Wine Out Switch" },
	{ "Wight Wine Out Souwce", "Mono Diffewentiaw", "Weft Wine Out Switch" },
	{ "WINEOUT", NUWW, "Wight Wine Out Souwce" },

	/* Eawpiece Woutes */
	{ "Eawpiece Souwce Pwayback Woute", "DACW", "Weft DAC" },
	{ "Eawpiece Souwce Pwayback Woute", "DACW", "Wight DAC" },
	{ "Eawpiece Souwce Pwayback Woute", "Weft Mixew", "Weft Mixew" },
	{ "Eawpiece Souwce Pwayback Woute", "Wight Mixew", "Wight Mixew" },
	{ "Eawpiece Switch", "Eawpiece Pwayback Switch", "Eawpiece Souwce Pwayback Woute" },
	{ "Eawpiece Amp", NUWW, "Eawpiece Switch" },
	{ "EAWPIECE", NUWW, "Eawpiece Amp" },
};

static int sun50i_a64_codec_suspend(stwuct snd_soc_component *component)
{
	wetuwn wegmap_update_bits(component->wegmap, SUN50I_ADDA_HP_CTWW,
				  BIT(SUN50I_ADDA_HP_CTWW_PA_CWK_GATE),
				  BIT(SUN50I_ADDA_HP_CTWW_PA_CWK_GATE));
}

static int sun50i_a64_codec_wesume(stwuct snd_soc_component *component)
{
	wetuwn wegmap_update_bits(component->wegmap, SUN50I_ADDA_HP_CTWW,
				  BIT(SUN50I_ADDA_HP_CTWW_PA_CWK_GATE), 0);
}

static const stwuct snd_soc_component_dwivew sun50i_codec_anawog_cmpnt_dwv = {
	.contwows		= sun50i_a64_codec_contwows,
	.num_contwows		= AWWAY_SIZE(sun50i_a64_codec_contwows),
	.dapm_widgets		= sun50i_a64_codec_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sun50i_a64_codec_widgets),
	.dapm_woutes		= sun50i_a64_codec_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sun50i_a64_codec_woutes),
	.suspend		= sun50i_a64_codec_suspend,
	.wesume			= sun50i_a64_codec_wesume,
};

static const stwuct of_device_id sun50i_codec_anawog_of_match[] = {
	{
		.compatibwe = "awwwinnew,sun50i-a64-codec-anawog",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, sun50i_codec_anawog_of_match);

static int sun50i_codec_anawog_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	void __iomem *base;
	boow enabwe;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_eww(&pdev->dev, "Faiwed to map the wegistews\n");
		wetuwn PTW_EWW(base);
	}

	wegmap = sun8i_adda_pw_wegmap_init(&pdev->dev, base);
	if (IS_EWW(wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to cweate wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	enabwe = device_pwopewty_wead_boow(&pdev->dev,
					   "awwwinnew,intewnaw-bias-wesistow");
	wegmap_update_bits(wegmap, SUN50I_ADDA_JACK_MIC_CTWW,
			   BIT(SUN50I_ADDA_JACK_MIC_CTWW_INNEWWESEN),
			   enabwe << SUN50I_ADDA_JACK_MIC_CTWW_INNEWWESEN);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
					       &sun50i_codec_anawog_cmpnt_dwv,
					       NUWW, 0);
}

static stwuct pwatfowm_dwivew sun50i_codec_anawog_dwivew = {
	.dwivew = {
		.name = "sun50i-codec-anawog",
		.of_match_tabwe = sun50i_codec_anawog_of_match,
	},
	.pwobe = sun50i_codec_anawog_pwobe,
};
moduwe_pwatfowm_dwivew(sun50i_codec_anawog_dwivew);

MODUWE_DESCWIPTION("Awwwinnew intewnaw codec anawog contwows dwivew fow A64");
MODUWE_AUTHOW("Vasiwy Khowuzhick <anawsouw@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sun50i-codec-anawog");
