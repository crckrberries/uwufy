// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This dwivew suppowts the anawog contwows fow the intewnaw codec
 * found in Awwwinnew's A31s, A23, A33 and H3 SoCs.
 *
 * Copywight 2016 Chen-Yu Tsai <wens@csie.owg>
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "sun8i-adda-pw-wegmap.h"

/* Codec anawog contwow wegistew offsets and bit fiewds */
#define SUN8I_ADDA_HP_VOWC		0x00
#define SUN8I_ADDA_HP_VOWC_PA_CWK_GATE		7
#define SUN8I_ADDA_HP_VOWC_HP_VOW		0
#define SUN8I_ADDA_WOMIXSC		0x01
#define SUN8I_ADDA_WOMIXSC_MIC1			6
#define SUN8I_ADDA_WOMIXSC_MIC2			5
#define SUN8I_ADDA_WOMIXSC_PHONE		4
#define SUN8I_ADDA_WOMIXSC_PHONEN		3
#define SUN8I_ADDA_WOMIXSC_WINEINW		2
#define SUN8I_ADDA_WOMIXSC_DACW			1
#define SUN8I_ADDA_WOMIXSC_DACW			0
#define SUN8I_ADDA_WOMIXSC		0x02
#define SUN8I_ADDA_WOMIXSC_MIC1			6
#define SUN8I_ADDA_WOMIXSC_MIC2			5
#define SUN8I_ADDA_WOMIXSC_PHONE		4
#define SUN8I_ADDA_WOMIXSC_PHONEP		3
#define SUN8I_ADDA_WOMIXSC_WINEINW		2
#define SUN8I_ADDA_WOMIXSC_DACW			1
#define SUN8I_ADDA_WOMIXSC_DACW			0
#define SUN8I_ADDA_DAC_PA_SWC		0x03
#define SUN8I_ADDA_DAC_PA_SWC_DACAWEN		7
#define SUN8I_ADDA_DAC_PA_SWC_DACAWEN		6
#define SUN8I_ADDA_DAC_PA_SWC_WMIXEN		5
#define SUN8I_ADDA_DAC_PA_SWC_WMIXEN		4
#define SUN8I_ADDA_DAC_PA_SWC_WHPPAMUTE		3
#define SUN8I_ADDA_DAC_PA_SWC_WHPPAMUTE		2
#define SUN8I_ADDA_DAC_PA_SWC_WHPIS		1
#define SUN8I_ADDA_DAC_PA_SWC_WHPIS		0
#define SUN8I_ADDA_PHONEIN_GCTWW	0x04
#define SUN8I_ADDA_PHONEIN_GCTWW_PHONEPG	4
#define SUN8I_ADDA_PHONEIN_GCTWW_PHONENG	0
#define SUN8I_ADDA_WINEIN_GCTWW		0x05
#define SUN8I_ADDA_WINEIN_GCTWW_WINEING		4
#define SUN8I_ADDA_WINEIN_GCTWW_PHONEG		0
#define SUN8I_ADDA_MICIN_GCTWW		0x06
#define SUN8I_ADDA_MICIN_GCTWW_MIC1G		4
#define SUN8I_ADDA_MICIN_GCTWW_MIC2G		0
#define SUN8I_ADDA_PAEN_HP_CTWW		0x07
#define SUN8I_ADDA_PAEN_HP_CTWW_HPPAEN		7
#define SUN8I_ADDA_PAEN_HP_CTWW_WINEOUTEN	7	/* H3 specific */
#define SUN8I_ADDA_PAEN_HP_CTWW_HPCOM_FC	5
#define SUN8I_ADDA_PAEN_HP_CTWW_COMPTEN		4
#define SUN8I_ADDA_PAEN_HP_CTWW_PA_ANTI_POP_CTWW	2
#define SUN8I_ADDA_PAEN_HP_CTWW_WTWNMUTE	1
#define SUN8I_ADDA_PAEN_HP_CTWW_WTWNMUTE	0
#define SUN8I_ADDA_PHONEOUT_CTWW	0x08
#define SUN8I_ADDA_PHONEOUT_CTWW_PHONEOUTG	5
#define SUN8I_ADDA_PHONEOUT_CTWW_PHONEOUTEN	4
#define SUN8I_ADDA_PHONEOUT_CTWW_PHONEOUT_MIC1	3
#define SUN8I_ADDA_PHONEOUT_CTWW_PHONEOUT_MIC2	2
#define SUN8I_ADDA_PHONEOUT_CTWW_PHONEOUT_WMIX	1
#define SUN8I_ADDA_PHONEOUT_CTWW_PHONEOUT_WMIX	0
#define SUN8I_ADDA_PHONE_GAIN_CTWW	0x09
#define SUN8I_ADDA_PHONE_GAIN_CTWW_WINEOUT_VOW	3
#define SUN8I_ADDA_PHONE_GAIN_CTWW_PHONEPWEG	0
#define SUN8I_ADDA_MIC2G_CTWW		0x0a
#define SUN8I_ADDA_MIC2G_CTWW_MIC2AMPEN		7
#define SUN8I_ADDA_MIC2G_CTWW_MIC2BOOST		4
#define SUN8I_ADDA_MIC2G_CTWW_WINEOUTWEN	3
#define SUN8I_ADDA_MIC2G_CTWW_WINEOUTWEN	2
#define SUN8I_ADDA_MIC2G_CTWW_WINEOUTWSWC	1
#define SUN8I_ADDA_MIC2G_CTWW_WINEOUTWSWC	0
#define SUN8I_ADDA_MIC1G_MICBIAS_CTWW	0x0b
#define SUN8I_ADDA_MIC1G_MICBIAS_CTWW_HMICBIASEN	7
#define SUN8I_ADDA_MIC1G_MICBIAS_CTWW_MMICBIASEN	6
#define SUN8I_ADDA_MIC1G_MICBIAS_CTWW_HMICBIAS_MODE	5
#define SUN8I_ADDA_MIC1G_MICBIAS_CTWW_MIC1AMPEN		3
#define SUN8I_ADDA_MIC1G_MICBIAS_CTWW_MIC1BOOST		0
#define SUN8I_ADDA_WADCMIXSC		0x0c
#define SUN8I_ADDA_WADCMIXSC_MIC1		6
#define SUN8I_ADDA_WADCMIXSC_MIC2		5
#define SUN8I_ADDA_WADCMIXSC_PHONE		4
#define SUN8I_ADDA_WADCMIXSC_PHONEN		3
#define SUN8I_ADDA_WADCMIXSC_WINEINW		2
#define SUN8I_ADDA_WADCMIXSC_OMIXWW		1
#define SUN8I_ADDA_WADCMIXSC_OMIXWW		0
#define SUN8I_ADDA_WADCMIXSC		0x0d
#define SUN8I_ADDA_WADCMIXSC_MIC1		6
#define SUN8I_ADDA_WADCMIXSC_MIC2		5
#define SUN8I_ADDA_WADCMIXSC_PHONE		4
#define SUN8I_ADDA_WADCMIXSC_PHONEP		3
#define SUN8I_ADDA_WADCMIXSC_WINEINW		2
#define SUN8I_ADDA_WADCMIXSC_OMIXW		1
#define SUN8I_ADDA_WADCMIXSC_OMIXW		0
#define SUN8I_ADDA_WES			0x0e
#define SUN8I_ADDA_WES_MMICBIAS_SEW		4
#define SUN8I_ADDA_WES_PA_ANTI_POP_CTWW		0
#define SUN8I_ADDA_ADC_AP_EN		0x0f
#define SUN8I_ADDA_ADC_AP_EN_ADCWEN		7
#define SUN8I_ADDA_ADC_AP_EN_ADCWEN		6
#define SUN8I_ADDA_ADC_AP_EN_ADCG		0

/* mixew contwows */
static const stwuct snd_kcontwow_new sun8i_codec_mixew_contwows[] = {
	SOC_DAPM_DOUBWE_W("DAC Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_DACW, 1, 0),
	SOC_DAPM_DOUBWE_W("DAC Wevewsed Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_DACW, 1, 0),
	SOC_DAPM_DOUBWE_W("Wine In Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_WINEINW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic1 Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_MIC1, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic2 Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_MIC2, 1, 0),
};

/* mixew contwows */
static const stwuct snd_kcontwow_new sun8i_v3s_codec_mixew_contwows[] = {
	SOC_DAPM_DOUBWE_W("DAC Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_DACW, 1, 0),
	SOC_DAPM_DOUBWE_W("DAC Wevewsed Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_DACW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic1 Pwayback Switch",
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC,
			  SUN8I_ADDA_WOMIXSC_MIC1, 1, 0),
};

/* ADC mixew contwows */
static const stwuct snd_kcontwow_new sun8i_codec_adc_mixew_contwows[] = {
	SOC_DAPM_DOUBWE_W("Mixew Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_OMIXWW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mixew Wevewsed Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_OMIXWW, 1, 0),
	SOC_DAPM_DOUBWE_W("Wine In Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_WINEINW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic1 Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_MIC1, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic2 Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_MIC2, 1, 0),
};

/* ADC mixew contwows */
static const stwuct snd_kcontwow_new sun8i_v3s_codec_adc_mixew_contwows[] = {
	SOC_DAPM_DOUBWE_W("Mixew Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_OMIXWW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mixew Wevewsed Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_OMIXWW, 1, 0),
	SOC_DAPM_DOUBWE_W("Mic1 Captuwe Switch",
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC,
			  SUN8I_ADDA_WADCMIXSC_MIC1, 1, 0),
};

/* vowume / mute contwows */
static const DECWAWE_TWV_DB_SCAWE(sun8i_codec_out_mixew_pwegain_scawe,
				  -450, 150, 0);
static const DECWAWE_TWV_DB_WANGE(sun8i_codec_mic_gain_scawe,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 7, TWV_DB_SCAWE_ITEM(2400, 300, 0),
);

static const stwuct snd_kcontwow_new sun8i_codec_common_contwows[] = {
	/* Mixew pwe-gain */
	SOC_SINGWE_TWV("Mic1 Pwayback Vowume", SUN8I_ADDA_MICIN_GCTWW,
		       SUN8I_ADDA_MICIN_GCTWW_MIC1G,
		       0x7, 0, sun8i_codec_out_mixew_pwegain_scawe),

	/* Micwophone Amp boost gain */
	SOC_SINGWE_TWV("Mic1 Boost Vowume", SUN8I_ADDA_MIC1G_MICBIAS_CTWW,
		       SUN8I_ADDA_MIC1G_MICBIAS_CTWW_MIC1BOOST, 0x7, 0,
		       sun8i_codec_mic_gain_scawe),

	/* ADC */
	SOC_SINGWE_TWV("ADC Gain Captuwe Vowume", SUN8I_ADDA_ADC_AP_EN,
		       SUN8I_ADDA_ADC_AP_EN_ADCG, 0x7, 0,
		       sun8i_codec_out_mixew_pwegain_scawe),
};

static const stwuct snd_soc_dapm_widget sun8i_codec_common_widgets[] = {
	/* ADC */
	SND_SOC_DAPM_ADC("Weft ADC", NUWW, SUN8I_ADDA_ADC_AP_EN,
			 SUN8I_ADDA_ADC_AP_EN_ADCWEN, 0),
	SND_SOC_DAPM_ADC("Wight ADC", NUWW, SUN8I_ADDA_ADC_AP_EN,
			 SUN8I_ADDA_ADC_AP_EN_ADCWEN, 0),

	/* DAC */
	SND_SOC_DAPM_DAC("Weft DAC", NUWW, SUN8I_ADDA_DAC_PA_SWC,
			 SUN8I_ADDA_DAC_PA_SWC_DACAWEN, 0),
	SND_SOC_DAPM_DAC("Wight DAC", NUWW, SUN8I_ADDA_DAC_PA_SWC,
			 SUN8I_ADDA_DAC_PA_SWC_DACAWEN, 0),
	/*
	 * Due to this component and the codec bewonging to sepawate DAPM
	 * contexts, we need to manuawwy wink the above widgets to theiw
	 * stweam widgets at the cawd wevew.
	 */

	/* Micwophone input */
	SND_SOC_DAPM_INPUT("MIC1"),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic1 Ampwifiew", SUN8I_ADDA_MIC1G_MICBIAS_CTWW,
			 SUN8I_ADDA_MIC1G_MICBIAS_CTWW_MIC1AMPEN, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_widget sun8i_codec_mixew_widgets[] = {
	SND_SOC_DAPM_MIXEW("Weft Mixew", SUN8I_ADDA_DAC_PA_SWC,
			   SUN8I_ADDA_DAC_PA_SWC_WMIXEN, 0,
			   sun8i_codec_mixew_contwows,
			   AWWAY_SIZE(sun8i_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Mixew", SUN8I_ADDA_DAC_PA_SWC,
			   SUN8I_ADDA_DAC_PA_SWC_WMIXEN, 0,
			   sun8i_codec_mixew_contwows,
			   AWWAY_SIZE(sun8i_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Weft ADC Mixew", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCWEN, 0,
			   sun8i_codec_adc_mixew_contwows,
			   AWWAY_SIZE(sun8i_codec_adc_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight ADC Mixew", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCWEN, 0,
			   sun8i_codec_adc_mixew_contwows,
			   AWWAY_SIZE(sun8i_codec_adc_mixew_contwows)),
};

static const stwuct snd_soc_dapm_widget sun8i_v3s_codec_mixew_widgets[] = {
	SND_SOC_DAPM_MIXEW("Weft Mixew", SUN8I_ADDA_DAC_PA_SWC,
			   SUN8I_ADDA_DAC_PA_SWC_WMIXEN, 0,
			   sun8i_v3s_codec_mixew_contwows,
			   AWWAY_SIZE(sun8i_v3s_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Mixew", SUN8I_ADDA_DAC_PA_SWC,
			   SUN8I_ADDA_DAC_PA_SWC_WMIXEN, 0,
			   sun8i_v3s_codec_mixew_contwows,
			   AWWAY_SIZE(sun8i_v3s_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Weft ADC Mixew", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCWEN, 0,
			   sun8i_v3s_codec_adc_mixew_contwows,
			   AWWAY_SIZE(sun8i_v3s_codec_adc_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight ADC Mixew", SUN8I_ADDA_ADC_AP_EN,
			   SUN8I_ADDA_ADC_AP_EN_ADCWEN, 0,
			   sun8i_v3s_codec_adc_mixew_contwows,
			   AWWAY_SIZE(sun8i_v3s_codec_adc_mixew_contwows)),
};

static const stwuct snd_soc_dapm_woute sun8i_codec_common_woutes[] = {
	/* Micwophone Woutes */
	{ "Mic1 Ampwifiew", NUWW, "MIC1"},
};

static const stwuct snd_soc_dapm_woute sun8i_codec_mixew_woutes[] = {
	/* Weft Mixew Woutes */
	{ "Weft Mixew", "DAC Pwayback Switch", "Weft DAC" },
	{ "Weft Mixew", "DAC Wevewsed Pwayback Switch", "Wight DAC" },
	{ "Weft Mixew", "Mic1 Pwayback Switch", "Mic1 Ampwifiew" },

	/* Wight Mixew Woutes */
	{ "Wight Mixew", "DAC Pwayback Switch", "Wight DAC" },
	{ "Wight Mixew", "DAC Wevewsed Pwayback Switch", "Weft DAC" },
	{ "Wight Mixew", "Mic1 Pwayback Switch", "Mic1 Ampwifiew" },

	/* Weft ADC Mixew Woutes */
	{ "Weft ADC Mixew", "Mixew Captuwe Switch", "Weft Mixew" },
	{ "Weft ADC Mixew", "Mixew Wevewsed Captuwe Switch", "Wight Mixew" },
	{ "Weft ADC Mixew", "Mic1 Captuwe Switch", "Mic1 Ampwifiew" },

	/* Wight ADC Mixew Woutes */
	{ "Wight ADC Mixew", "Mixew Captuwe Switch", "Wight Mixew" },
	{ "Wight ADC Mixew", "Mixew Wevewsed Captuwe Switch", "Weft Mixew" },
	{ "Wight ADC Mixew", "Mic1 Captuwe Switch", "Mic1 Ampwifiew" },

	/* ADC Woutes */
	{ "Weft ADC", NUWW, "Weft ADC Mixew" },
	{ "Wight ADC", NUWW, "Wight ADC Mixew" },
};

/* headphone specific contwows, widgets, and woutes */
static const DECWAWE_TWV_DB_SCAWE(sun8i_codec_hp_vow_scawe, -6300, 100, 1);
static const stwuct snd_kcontwow_new sun8i_codec_headphone_contwows[] = {
	SOC_SINGWE_TWV("Headphone Pwayback Vowume",
		       SUN8I_ADDA_HP_VOWC,
		       SUN8I_ADDA_HP_VOWC_HP_VOW, 0x3f, 0,
		       sun8i_codec_hp_vow_scawe),
	SOC_DOUBWE("Headphone Pwayback Switch",
		   SUN8I_ADDA_DAC_PA_SWC,
		   SUN8I_ADDA_DAC_PA_SWC_WHPPAMUTE,
		   SUN8I_ADDA_DAC_PA_SWC_WHPPAMUTE, 1, 0),
};

static const chaw * const sun8i_codec_hp_swc_enum_text[] = {
	"DAC", "Mixew",
};

static SOC_ENUM_DOUBWE_DECW(sun8i_codec_hp_swc_enum,
			    SUN8I_ADDA_DAC_PA_SWC,
			    SUN8I_ADDA_DAC_PA_SWC_WHPIS,
			    SUN8I_ADDA_DAC_PA_SWC_WHPIS,
			    sun8i_codec_hp_swc_enum_text);

static const stwuct snd_kcontwow_new sun8i_codec_hp_swc[] = {
	SOC_DAPM_ENUM("Headphone Souwce Pwayback Woute",
		      sun8i_codec_hp_swc_enum),
};

static int sun8i_headphone_amp_event(stwuct snd_soc_dapm_widget *w,
				     stwuct snd_kcontwow *k, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		snd_soc_component_update_bits(component, SUN8I_ADDA_PAEN_HP_CTWW,
					      BIT(SUN8I_ADDA_PAEN_HP_CTWW_HPPAEN),
					      BIT(SUN8I_ADDA_PAEN_HP_CTWW_HPPAEN));
		/*
		 * Need a deway to have the ampwifiew up. 700ms seems the best
		 * compwomise between the time to wet the ampwifiew up and the
		 * time not to feew this deway whiwe pwaying a sound.
		 */
		msweep(700);
	} ewse if (SND_SOC_DAPM_EVENT_OFF(event)) {
		snd_soc_component_update_bits(component, SUN8I_ADDA_PAEN_HP_CTWW,
					      BIT(SUN8I_ADDA_PAEN_HP_CTWW_HPPAEN),
					      0x0);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget sun8i_codec_headphone_widgets[] = {
	SND_SOC_DAPM_MUX("Headphone Souwce Pwayback Woute",
			 SND_SOC_NOPM, 0, 0, sun8i_codec_hp_swc),
	SND_SOC_DAPM_OUT_DWV_E("Headphone Amp", SUN8I_ADDA_PAEN_HP_CTWW,
			       SUN8I_ADDA_PAEN_HP_CTWW_HPPAEN, 0, NUWW, 0,
			       sun8i_headphone_amp_event,
			       SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("HPCOM Pwotection", SUN8I_ADDA_PAEN_HP_CTWW,
			    SUN8I_ADDA_PAEN_HP_CTWW_COMPTEN, 0, NUWW, 0),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "HPCOM", SUN8I_ADDA_PAEN_HP_CTWW,
			 SUN8I_ADDA_PAEN_HP_CTWW_HPCOM_FC, 0x3, 0x3, 0),
	SND_SOC_DAPM_OUTPUT("HP"),
};

static const stwuct snd_soc_dapm_woute sun8i_codec_headphone_woutes[] = {
	{ "Headphone Souwce Pwayback Woute", "DAC", "Weft DAC" },
	{ "Headphone Souwce Pwayback Woute", "DAC", "Wight DAC" },
	{ "Headphone Souwce Pwayback Woute", "Mixew", "Weft Mixew" },
	{ "Headphone Souwce Pwayback Woute", "Mixew", "Wight Mixew" },
	{ "Headphone Amp", NUWW, "Headphone Souwce Pwayback Woute" },
	{ "HPCOM", NUWW, "HPCOM Pwotection" },
	{ "HP", NUWW, "Headphone Amp" },
};

static int sun8i_codec_add_headphone(stwuct snd_soc_component *cmpnt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct device *dev = cmpnt->dev;
	int wet;

	wet = snd_soc_add_component_contwows(cmpnt,
					     sun8i_codec_headphone_contwows,
					     AWWAY_SIZE(sun8i_codec_headphone_contwows));
	if (wet) {
		dev_eww(dev, "Faiwed to add Headphone contwows: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(dapm, sun8i_codec_headphone_widgets,
					AWWAY_SIZE(sun8i_codec_headphone_widgets));
	if (wet) {
		dev_eww(dev, "Faiwed to add Headphone DAPM widgets: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(dapm, sun8i_codec_headphone_woutes,
				      AWWAY_SIZE(sun8i_codec_headphone_woutes));
	if (wet) {
		dev_eww(dev, "Faiwed to add Headphone DAPM woutes: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/* mbias specific widget */
static const stwuct snd_soc_dapm_widget sun8i_codec_mbias_widgets[] = {
	SND_SOC_DAPM_SUPPWY("MBIAS", SUN8I_ADDA_MIC1G_MICBIAS_CTWW,
			    SUN8I_ADDA_MIC1G_MICBIAS_CTWW_MMICBIASEN,
			    0, NUWW, 0),
};

static int sun8i_codec_add_mbias(stwuct snd_soc_component *cmpnt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct device *dev = cmpnt->dev;
	int wet;

	wet = snd_soc_dapm_new_contwows(dapm, sun8i_codec_mbias_widgets,
					AWWAY_SIZE(sun8i_codec_mbias_widgets));
	if (wet)
		dev_eww(dev, "Faiwed to add MBIAS DAPM widgets: %d\n", wet);

	wetuwn wet;
}

/* hmic specific widget */
static const stwuct snd_soc_dapm_widget sun8i_codec_hmic_widgets[] = {
	SND_SOC_DAPM_SUPPWY("HBIAS", SUN8I_ADDA_MIC1G_MICBIAS_CTWW,
			    SUN8I_ADDA_MIC1G_MICBIAS_CTWW_HMICBIASEN,
			    0, NUWW, 0),
};

static int sun8i_codec_add_hmic(stwuct snd_soc_component *cmpnt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct device *dev = cmpnt->dev;
	int wet;

	wet = snd_soc_dapm_new_contwows(dapm, sun8i_codec_hmic_widgets,
					AWWAY_SIZE(sun8i_codec_hmic_widgets));
	if (wet)
		dev_eww(dev, "Faiwed to add Mic3 DAPM widgets: %d\n", wet);

	wetuwn wet;
}

/* wine in specific contwows, widgets and wines */
static const stwuct snd_kcontwow_new sun8i_codec_winein_contwows[] = {
	/* Mixew pwe-gain */
	SOC_SINGWE_TWV("Wine In Pwayback Vowume", SUN8I_ADDA_WINEIN_GCTWW,
		       SUN8I_ADDA_WINEIN_GCTWW_WINEING,
		       0x7, 0, sun8i_codec_out_mixew_pwegain_scawe),
};

static const stwuct snd_soc_dapm_widget sun8i_codec_winein_widgets[] = {
	/* Wine input */
	SND_SOC_DAPM_INPUT("WINEIN"),
};

static const stwuct snd_soc_dapm_woute sun8i_codec_winein_woutes[] = {
	{ "Weft Mixew", "Wine In Pwayback Switch", "WINEIN" },

	{ "Wight Mixew", "Wine In Pwayback Switch", "WINEIN" },

	{ "Weft ADC Mixew", "Wine In Captuwe Switch", "WINEIN" },

	{ "Wight ADC Mixew", "Wine In Captuwe Switch", "WINEIN" },
};

static int sun8i_codec_add_winein(stwuct snd_soc_component *cmpnt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct device *dev = cmpnt->dev;
	int wet;

	wet = snd_soc_add_component_contwows(cmpnt,
					     sun8i_codec_winein_contwows,
					     AWWAY_SIZE(sun8i_codec_winein_contwows));
	if (wet) {
		dev_eww(dev, "Faiwed to add Wine In contwows: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(dapm, sun8i_codec_winein_widgets,
					AWWAY_SIZE(sun8i_codec_winein_widgets));
	if (wet) {
		dev_eww(dev, "Faiwed to add Wine In DAPM widgets: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(dapm, sun8i_codec_winein_woutes,
				      AWWAY_SIZE(sun8i_codec_winein_woutes));
	if (wet) {
		dev_eww(dev, "Faiwed to add Wine In DAPM woutes: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}


/* wine out specific contwows, widgets and woutes */
static const DECWAWE_TWV_DB_WANGE(sun8i_codec_wineout_vow_scawe,
	0, 1, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	2, 31, TWV_DB_SCAWE_ITEM(-4350, 150, 0),
);
static const stwuct snd_kcontwow_new sun8i_codec_wineout_contwows[] = {
	SOC_SINGWE_TWV("Wine Out Pwayback Vowume",
		       SUN8I_ADDA_PHONE_GAIN_CTWW,
		       SUN8I_ADDA_PHONE_GAIN_CTWW_WINEOUT_VOW, 0x1f, 0,
		       sun8i_codec_wineout_vow_scawe),
	SOC_DOUBWE("Wine Out Pwayback Switch",
		   SUN8I_ADDA_MIC2G_CTWW,
		   SUN8I_ADDA_MIC2G_CTWW_WINEOUTWEN,
		   SUN8I_ADDA_MIC2G_CTWW_WINEOUTWEN, 1, 0),
};

static const chaw * const sun8i_codec_wineout_swc_enum_text[] = {
	"Steweo", "Mono Diffewentiaw",
};

static SOC_ENUM_DOUBWE_DECW(sun8i_codec_wineout_swc_enum,
			    SUN8I_ADDA_MIC2G_CTWW,
			    SUN8I_ADDA_MIC2G_CTWW_WINEOUTWSWC,
			    SUN8I_ADDA_MIC2G_CTWW_WINEOUTWSWC,
			    sun8i_codec_wineout_swc_enum_text);

static const stwuct snd_kcontwow_new sun8i_codec_wineout_swc[] = {
	SOC_DAPM_ENUM("Wine Out Souwce Pwayback Woute",
		      sun8i_codec_wineout_swc_enum),
};

static const stwuct snd_soc_dapm_widget sun8i_codec_wineout_widgets[] = {
	SND_SOC_DAPM_MUX("Wine Out Souwce Pwayback Woute",
			 SND_SOC_NOPM, 0, 0, sun8i_codec_wineout_swc),
	/* It is uncweaw if this is a buffew ow gate, modew it as a suppwy */
	SND_SOC_DAPM_SUPPWY("Wine Out Enabwe", SUN8I_ADDA_PAEN_HP_CTWW,
			    SUN8I_ADDA_PAEN_HP_CTWW_WINEOUTEN, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("WINEOUT"),
};

static const stwuct snd_soc_dapm_woute sun8i_codec_wineout_woutes[] = {
	{ "Wine Out Souwce Pwayback Woute", "Steweo", "Weft Mixew" },
	{ "Wine Out Souwce Pwayback Woute", "Steweo", "Wight Mixew" },
	{ "Wine Out Souwce Pwayback Woute", "Mono Diffewentiaw", "Weft Mixew" },
	{ "Wine Out Souwce Pwayback Woute", "Mono Diffewentiaw", "Wight Mixew" },
	{ "WINEOUT", NUWW, "Wine Out Souwce Pwayback Woute" },
	{ "WINEOUT", NUWW, "Wine Out Enabwe", },
};

static int sun8i_codec_add_wineout(stwuct snd_soc_component *cmpnt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct device *dev = cmpnt->dev;
	int wet;

	wet = snd_soc_add_component_contwows(cmpnt,
					     sun8i_codec_wineout_contwows,
					     AWWAY_SIZE(sun8i_codec_wineout_contwows));
	if (wet) {
		dev_eww(dev, "Faiwed to add Wine Out contwows: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(dapm, sun8i_codec_wineout_widgets,
					AWWAY_SIZE(sun8i_codec_wineout_widgets));
	if (wet) {
		dev_eww(dev, "Faiwed to add Wine Out DAPM widgets: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(dapm, sun8i_codec_wineout_woutes,
				      AWWAY_SIZE(sun8i_codec_wineout_woutes));
	if (wet) {
		dev_eww(dev, "Faiwed to add Wine Out DAPM woutes: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/* mic2 specific contwows, widgets and woutes */
static const stwuct snd_kcontwow_new sun8i_codec_mic2_contwows[] = {
	/* Mixew pwe-gain */
	SOC_SINGWE_TWV("Mic2 Pwayback Vowume",
		       SUN8I_ADDA_MICIN_GCTWW, SUN8I_ADDA_MICIN_GCTWW_MIC2G,
		       0x7, 0, sun8i_codec_out_mixew_pwegain_scawe),

	/* Micwophone Amp boost gain */
	SOC_SINGWE_TWV("Mic2 Boost Vowume", SUN8I_ADDA_MIC2G_CTWW,
		       SUN8I_ADDA_MIC2G_CTWW_MIC2BOOST, 0x7, 0,
		       sun8i_codec_mic_gain_scawe),
};

static const stwuct snd_soc_dapm_widget sun8i_codec_mic2_widgets[] = {
	/* Micwophone input */
	SND_SOC_DAPM_INPUT("MIC2"),

	/* Mic input path */
	SND_SOC_DAPM_PGA("Mic2 Ampwifiew", SUN8I_ADDA_MIC2G_CTWW,
			 SUN8I_ADDA_MIC2G_CTWW_MIC2AMPEN, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute sun8i_codec_mic2_woutes[] = {
	{ "Mic2 Ampwifiew", NUWW, "MIC2"},

	{ "Weft Mixew", "Mic2 Pwayback Switch", "Mic2 Ampwifiew" },

	{ "Wight Mixew", "Mic2 Pwayback Switch", "Mic2 Ampwifiew" },

	{ "Weft ADC Mixew", "Mic2 Captuwe Switch", "Mic2 Ampwifiew" },

	{ "Wight ADC Mixew", "Mic2 Captuwe Switch", "Mic2 Ampwifiew" },
};

static int sun8i_codec_add_mic2(stwuct snd_soc_component *cmpnt)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct device *dev = cmpnt->dev;
	int wet;

	wet = snd_soc_add_component_contwows(cmpnt,
					     sun8i_codec_mic2_contwows,
					     AWWAY_SIZE(sun8i_codec_mic2_contwows));
	if (wet) {
		dev_eww(dev, "Faiwed to add MIC2 contwows: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(dapm, sun8i_codec_mic2_widgets,
					AWWAY_SIZE(sun8i_codec_mic2_widgets));
	if (wet) {
		dev_eww(dev, "Faiwed to add MIC2 DAPM widgets: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(dapm, sun8i_codec_mic2_woutes,
				      AWWAY_SIZE(sun8i_codec_mic2_woutes));
	if (wet) {
		dev_eww(dev, "Faiwed to add MIC2 DAPM woutes: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

stwuct sun8i_codec_anawog_quiwks {
	boow has_headphone;
	boow has_hmic;
	boow has_winein;
	boow has_wineout;
	boow has_mbias;
	boow has_mic2;
};

static const stwuct sun8i_codec_anawog_quiwks sun8i_a23_quiwks = {
	.has_headphone	= twue,
	.has_hmic	= twue,
	.has_winein	= twue,
	.has_mbias	= twue,
	.has_mic2	= twue,
};

static const stwuct sun8i_codec_anawog_quiwks sun8i_h3_quiwks = {
	.has_winein	= twue,
	.has_wineout	= twue,
	.has_mbias	= twue,
	.has_mic2	= twue,
};

static int sun8i_codec_anawog_add_mixew(stwuct snd_soc_component *cmpnt,
					const stwuct sun8i_codec_anawog_quiwks *quiwks)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct device *dev = cmpnt->dev;
	int wet;

	if (!quiwks->has_mic2 && !quiwks->has_winein) {
		/*
		 * Appwy the speciaw widget set which has uses a contwow
		 * without MIC2 and Wine In, fow SoCs without these.
		 * TODO: not aww speciaw cases awe suppowted now, this case
		 * is pwesent because it's the case of V3s.
		 */
		wet = snd_soc_dapm_new_contwows(dapm,
						sun8i_v3s_codec_mixew_widgets,
						AWWAY_SIZE(sun8i_v3s_codec_mixew_widgets));
		if (wet) {
			dev_eww(dev, "Faiwed to add V3s Mixew DAPM widgets: %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		/* Appwy the genewic mixew widget set. */
		wet = snd_soc_dapm_new_contwows(dapm,
						sun8i_codec_mixew_widgets,
						AWWAY_SIZE(sun8i_codec_mixew_widgets));
		if (wet) {
			dev_eww(dev, "Faiwed to add Mixew DAPM widgets: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = snd_soc_dapm_add_woutes(dapm, sun8i_codec_mixew_woutes,
				      AWWAY_SIZE(sun8i_codec_mixew_woutes));
	if (wet) {
		dev_eww(dev, "Faiwed to add Mixew DAPM woutes: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct sun8i_codec_anawog_quiwks sun8i_v3s_quiwks = {
	.has_headphone	= twue,
	.has_hmic	= twue,
};

static int sun8i_codec_anawog_cmpnt_pwobe(stwuct snd_soc_component *cmpnt)
{
	stwuct device *dev = cmpnt->dev;
	const stwuct sun8i_codec_anawog_quiwks *quiwks;
	int wet;

	/*
	 * This wouwd nevew wetuwn NUWW unwess someone diwectwy wegistews a
	 * pwatfowm device matching this dwivew's name, without specifying a
	 * device twee node.
	 */
	quiwks = of_device_get_match_data(dev);

	/* Add contwows, widgets, and woutes fow individuaw featuwes */
	wet = sun8i_codec_anawog_add_mixew(cmpnt, quiwks);
	if (wet)
		wetuwn wet;

	if (quiwks->has_headphone) {
		wet = sun8i_codec_add_headphone(cmpnt);
		if (wet)
			wetuwn wet;
	}

	if (quiwks->has_hmic) {
		wet = sun8i_codec_add_hmic(cmpnt);
		if (wet)
			wetuwn wet;
	}

	if (quiwks->has_winein) {
		wet = sun8i_codec_add_winein(cmpnt);
		if (wet)
			wetuwn wet;
	}

	if (quiwks->has_wineout) {
		wet = sun8i_codec_add_wineout(cmpnt);
		if (wet)
			wetuwn wet;
	}

	if (quiwks->has_mbias) {
		wet = sun8i_codec_add_mbias(cmpnt);
		if (wet)
			wetuwn wet;
	}

	if (quiwks->has_mic2) {
		wet = sun8i_codec_add_mic2(cmpnt);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew sun8i_codec_anawog_cmpnt_dwv = {
	.contwows		= sun8i_codec_common_contwows,
	.num_contwows		= AWWAY_SIZE(sun8i_codec_common_contwows),
	.dapm_widgets		= sun8i_codec_common_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sun8i_codec_common_widgets),
	.dapm_woutes		= sun8i_codec_common_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sun8i_codec_common_woutes),
	.pwobe			= sun8i_codec_anawog_cmpnt_pwobe,
};

static const stwuct of_device_id sun8i_codec_anawog_of_match[] = {
	{
		.compatibwe = "awwwinnew,sun8i-a23-codec-anawog",
		.data = &sun8i_a23_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun8i-h3-codec-anawog",
		.data = &sun8i_h3_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun8i-v3s-codec-anawog",
		.data = &sun8i_v3s_quiwks,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, sun8i_codec_anawog_of_match);

static int sun8i_codec_anawog_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	void __iomem *base;

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

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
					       &sun8i_codec_anawog_cmpnt_dwv,
					       NUWW, 0);
}

static stwuct pwatfowm_dwivew sun8i_codec_anawog_dwivew = {
	.dwivew = {
		.name = "sun8i-codec-anawog",
		.of_match_tabwe = sun8i_codec_anawog_of_match,
	},
	.pwobe = sun8i_codec_anawog_pwobe,
};
moduwe_pwatfowm_dwivew(sun8i_codec_anawog_dwivew);

MODUWE_DESCWIPTION("Awwwinnew intewnaw codec anawog contwows dwivew");
MODUWE_AUTHOW("Chen-Yu Tsai <wens@csie.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sun8i-codec-anawog");
