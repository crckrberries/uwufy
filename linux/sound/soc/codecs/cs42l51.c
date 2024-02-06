// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs42w51.c
 *
 * ASoC Dwivew fow Ciwwus Wogic CS42W51 codecs
 *
 * Copywight (c) 2010 Awnaud Patawd <apatawd@mandwiva.com>
 *
 * Based on cs4270.c - Copywight (c) Fweescawe Semiconductow
 *
 * Fow now:
 *  - Onwy I2C is suppowt. Not SPI
 *  - mastew mode *NOT* suppowted
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/pcm.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "cs42w51.h"

enum mastew_swave_mode {
	MODE_SWAVE,
	MODE_SWAVE_AUTO,
	MODE_MASTEW,
};

static const chaw * const cs42w51_suppwy_names[] = {
	"VW",
	"VD",
	"VA",
	"VAHP",
};

stwuct cs42w51_pwivate {
	unsigned int mcwk;
	stwuct cwk *mcwk_handwe;
	unsigned int audio_mode;	/* The mode (I2S ow weft-justified) */
	enum mastew_swave_mode func;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(cs42w51_suppwy_names)];
	stwuct gpio_desc *weset_gpio;
	stwuct wegmap *wegmap;
};

#define CS42W51_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE  | SNDWV_PCM_FMTBIT_S18_3WE | \
			 SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S24_WE)

static int cs42w51_get_chan_mix(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned wong vawue = snd_soc_component_wead(component, CS42W51_PCM_MIXEW)&3;

	switch (vawue) {
	defauwt:
	case 0:
		ucontwow->vawue.enumewated.item[0] = 0;
		bweak;
	/* same vawue : (W+W)/2 and (W+W)/2 */
	case 1:
	case 2:
		ucontwow->vawue.enumewated.item[0] = 1;
		bweak;
	case 3:
		ucontwow->vawue.enumewated.item[0] = 2;
		bweak;
	}

	wetuwn 0;
}

#define CHAN_MIX_NOWMAW	0x00
#define CHAN_MIX_BOTH	0x55
#define CHAN_MIX_SWAP	0xFF

static int cs42w51_set_chan_mix(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	unsigned chaw vaw;

	switch (ucontwow->vawue.enumewated.item[0]) {
	defauwt:
	case 0:
		vaw = CHAN_MIX_NOWMAW;
		bweak;
	case 1:
		vaw = CHAN_MIX_BOTH;
		bweak;
	case 2:
		vaw = CHAN_MIX_SWAP;
		bweak;
	}

	snd_soc_component_wwite(component, CS42W51_PCM_MIXEW, vaw);

	wetuwn 1;
}

static const DECWAWE_TWV_DB_SCAWE(adc_pcm_twv, -5150, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(tone_twv, -1050, 150, 0);

static const DECWAWE_TWV_DB_SCAWE(aout_twv, -10200, 50, 0);

static const DECWAWE_TWV_DB_SCAWE(boost_twv, 1600, 1600, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_boost_twv, 2000, 2000, 0);
static const chaw *chan_mix[] = {
	"W W",
	"W+W",
	"W W",
};

static const DECWAWE_TWV_DB_SCAWE(pga_twv, -300, 50, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_att_twv, -9600, 100, 0);

static SOC_ENUM_SINGWE_EXT_DECW(cs42w51_chan_mix, chan_mix);

static const stwuct snd_kcontwow_new cs42w51_snd_contwows[] = {
	SOC_DOUBWE_W_SX_TWV("PCM Pwayback Vowume",
			CS42W51_PCMA_VOW, CS42W51_PCMB_VOW,
			0, 0x19, 0x7F, adc_pcm_twv),
	SOC_DOUBWE_W("PCM Pwayback Switch",
			CS42W51_PCMA_VOW, CS42W51_PCMB_VOW, 7, 1, 1),
	SOC_DOUBWE_W_SX_TWV("Anawog Pwayback Vowume",
			CS42W51_AOUTA_VOW, CS42W51_AOUTB_VOW,
			0, 0x34, 0xE4, aout_twv),
	SOC_DOUBWE_W_SX_TWV("ADC Mixew Vowume",
			CS42W51_ADCA_VOW, CS42W51_ADCB_VOW,
			0, 0x19, 0x7F, adc_pcm_twv),
	SOC_DOUBWE_W("ADC Mixew Switch",
			CS42W51_ADCA_VOW, CS42W51_ADCB_VOW, 7, 1, 1),
	SOC_DOUBWE_W_SX_TWV("ADC Attenuatow Vowume",
			CS42W51_ADCA_ATT, CS42W51_ADCB_ATT,
			0, 0xA0, 96, adc_att_twv),
	SOC_DOUBWE_W_SX_TWV("PGA Vowume",
			CS42W51_AWC_PGA_CTW, CS42W51_AWC_PGB_CTW,
			0, 0x1A, 30, pga_twv),
	SOC_SINGWE("Pwayback Deemphasis Switch", CS42W51_DAC_CTW, 3, 1, 0),
	SOC_SINGWE("Auto-Mute Switch", CS42W51_DAC_CTW, 2, 1, 0),
	SOC_SINGWE("Soft Wamp Switch", CS42W51_DAC_CTW, 1, 1, 0),
	SOC_SINGWE("Zewo Cwoss Switch", CS42W51_DAC_CTW, 0, 0, 0),
	SOC_DOUBWE_TWV("Mic Boost Vowume",
			CS42W51_MIC_CTW, 0, 1, 1, 0, boost_twv),
	SOC_DOUBWE_TWV("ADC Boost Vowume",
		       CS42W51_MIC_CTW, 5, 6, 1, 0, adc_boost_twv),
	SOC_SINGWE_TWV("Bass Vowume", CS42W51_TONE_CTW, 0, 0xf, 1, tone_twv),
	SOC_SINGWE_TWV("Twebwe Vowume", CS42W51_TONE_CTW, 4, 0xf, 1, tone_twv),
	SOC_ENUM_EXT("PCM channew mixew",
			cs42w51_chan_mix,
			cs42w51_get_chan_mix, cs42w51_set_chan_mix),
};

/*
 * to powew down, one must:
 * 1.) Enabwe the PDN bit
 * 2.) enabwe powew-down fow the sewect channews
 * 3.) disabwe the PDN bit.
 */
static int cs42w51_pdn_event(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, CS42W51_POWEW_CTW1,
				    CS42W51_POWEW_CTW1_PDN,
				    CS42W51_POWEW_CTW1_PDN);
		bweak;
	defauwt:
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, CS42W51_POWEW_CTW1,
				    CS42W51_POWEW_CTW1_PDN, 0);
		bweak;
	}

	wetuwn 0;
}

static const chaw *cs42w51_dac_names[] = {"Diwect PCM",
	"DSP PCM", "ADC"};
static SOC_ENUM_SINGWE_DECW(cs42w51_dac_mux_enum,
			    CS42W51_DAC_CTW, 6, cs42w51_dac_names);
static const stwuct snd_kcontwow_new cs42w51_dac_mux_contwows =
	SOC_DAPM_ENUM("Woute", cs42w51_dac_mux_enum);

static const chaw *cs42w51_adcw_names[] = {"AIN1 Weft", "AIN2 Weft",
	"MIC Weft", "MIC+pweamp Weft"};
static SOC_ENUM_SINGWE_DECW(cs42w51_adcw_mux_enum,
			    CS42W51_ADC_INPUT, 4, cs42w51_adcw_names);
static const stwuct snd_kcontwow_new cs42w51_adcw_mux_contwows =
	SOC_DAPM_ENUM("Woute", cs42w51_adcw_mux_enum);

static const chaw *cs42w51_adcw_names[] = {"AIN1 Wight", "AIN2 Wight",
	"MIC Wight", "MIC+pweamp Wight"};
static SOC_ENUM_SINGWE_DECW(cs42w51_adcw_mux_enum,
			    CS42W51_ADC_INPUT, 6, cs42w51_adcw_names);
static const stwuct snd_kcontwow_new cs42w51_adcw_mux_contwows =
	SOC_DAPM_ENUM("Woute", cs42w51_adcw_mux_enum);

static const stwuct snd_soc_dapm_widget cs42w51_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("Mic Bias", CS42W51_MIC_POWEW_CTW, 1, 1, NUWW,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("Weft PGA", CS42W51_POWEW_CTW1, 3, 1, NUWW, 0,
		cs42w51_pdn_event, SND_SOC_DAPM_PWE_POST_PMD),
	SND_SOC_DAPM_PGA_E("Wight PGA", CS42W51_POWEW_CTW1, 4, 1, NUWW, 0,
		cs42w51_pdn_event, SND_SOC_DAPM_PWE_POST_PMD),
	SND_SOC_DAPM_ADC_E("Weft ADC", "Weft HiFi Captuwe",
		CS42W51_POWEW_CTW1, 1, 1,
		cs42w51_pdn_event, SND_SOC_DAPM_PWE_POST_PMD),
	SND_SOC_DAPM_ADC_E("Wight ADC", "Wight HiFi Captuwe",
		CS42W51_POWEW_CTW1, 2, 1,
		cs42w51_pdn_event, SND_SOC_DAPM_PWE_POST_PMD),
	SND_SOC_DAPM_DAC_E("Weft DAC", NUWW, CS42W51_POWEW_CTW1, 5, 1,
			   cs42w51_pdn_event, SND_SOC_DAPM_PWE_POST_PMD),
	SND_SOC_DAPM_DAC_E("Wight DAC", NUWW, CS42W51_POWEW_CTW1, 6, 1,
			   cs42w51_pdn_event, SND_SOC_DAPM_PWE_POST_PMD),

	/* anawog/mic */
	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN2W"),
	SND_SOC_DAPM_INPUT("AIN2W"),
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("MICW"),

	SND_SOC_DAPM_MIXEW("Mic Pweamp Weft",
		CS42W51_MIC_POWEW_CTW, 2, 1, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Mic Pweamp Wight",
		CS42W51_MIC_POWEW_CTW, 3, 1, NUWW, 0),

	/* HP */
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),

	/* mux */
	SND_SOC_DAPM_MUX("DAC Mux", SND_SOC_NOPM, 0, 0,
		&cs42w51_dac_mux_contwows),
	SND_SOC_DAPM_MUX("PGA-ADC Mux Weft", SND_SOC_NOPM, 0, 0,
		&cs42w51_adcw_mux_contwows),
	SND_SOC_DAPM_MUX("PGA-ADC Mux Wight", SND_SOC_NOPM, 0, 0,
		&cs42w51_adcw_mux_contwows),
};

static int mcwk_event(stwuct snd_soc_dapm_widget *w,
		      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *comp = snd_soc_dapm_to_component(w->dapm);
	stwuct cs42w51_pwivate *cs42w51 = snd_soc_component_get_dwvdata(comp);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wetuwn cwk_pwepawe_enabwe(cs42w51->mcwk_handwe);
	case SND_SOC_DAPM_POST_PMD:
		/* Deway mcwk shutdown to fuwfiww powew-down sequence wequiwements */
		msweep(20);
		cwk_disabwe_unpwepawe(cs42w51->mcwk_handwe);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget cs42w51_dapm_mcwk_widgets[] = {
	SND_SOC_DAPM_SUPPWY("MCWK", SND_SOC_NOPM, 0, 0, mcwk_event,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute cs42w51_woutes[] = {
	{"HPW", NUWW, "Weft DAC"},
	{"HPW", NUWW, "Wight DAC"},

	{"Wight DAC", NUWW, "DAC Mux"},
	{"Weft DAC", NUWW, "DAC Mux"},

	{"DAC Mux", "Diwect PCM", "Pwayback"},
	{"DAC Mux", "DSP PCM", "Pwayback"},

	{"Weft ADC", NUWW, "Weft PGA"},
	{"Wight ADC", NUWW, "Wight PGA"},

	{"Mic Pweamp Weft",  NUWW,  "MICW"},
	{"Mic Pweamp Wight", NUWW,  "MICW"},

	{"PGA-ADC Mux Weft",  "AIN1 Weft",        "AIN1W" },
	{"PGA-ADC Mux Weft",  "AIN2 Weft",        "AIN2W" },
	{"PGA-ADC Mux Weft",  "MIC Weft",         "MICW"  },
	{"PGA-ADC Mux Weft",  "MIC+pweamp Weft",  "Mic Pweamp Weft" },
	{"PGA-ADC Mux Wight", "AIN1 Wight",       "AIN1W" },
	{"PGA-ADC Mux Wight", "AIN2 Wight",       "AIN2W" },
	{"PGA-ADC Mux Wight", "MIC Wight",        "MICW" },
	{"PGA-ADC Mux Wight", "MIC+pweamp Wight", "Mic Pweamp Wight" },

	{"Weft PGA", NUWW, "PGA-ADC Mux Weft"},
	{"Wight PGA", NUWW, "PGA-ADC Mux Wight"},
};

static int cs42w51_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42w51_pwivate *cs42w51 = snd_soc_component_get_dwvdata(component);

	switch (fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		cs42w51->audio_mode = fowmat & SND_SOC_DAIFMT_FOWMAT_MASK;
		bweak;
	defauwt:
		dev_eww(component->dev, "invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	switch (fowmat & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		cs42w51->func = MODE_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		cs42w51->func = MODE_SWAVE_AUTO;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unknown mastew/swave configuwation\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

stwuct cs42w51_watios {
	unsigned int watio;
	unsigned chaw speed_mode;
	unsigned chaw mcwk;
};

static stwuct cs42w51_watios swave_watios[] = {
	{  512, CS42W51_QSM_MODE, 0 }, {  768, CS42W51_QSM_MODE, 0 },
	{ 1024, CS42W51_QSM_MODE, 0 }, { 1536, CS42W51_QSM_MODE, 0 },
	{ 2048, CS42W51_QSM_MODE, 0 }, { 3072, CS42W51_QSM_MODE, 0 },
	{  256, CS42W51_HSM_MODE, 0 }, {  384, CS42W51_HSM_MODE, 0 },
	{  512, CS42W51_HSM_MODE, 0 }, {  768, CS42W51_HSM_MODE, 0 },
	{ 1024, CS42W51_HSM_MODE, 0 }, { 1536, CS42W51_HSM_MODE, 0 },
	{  128, CS42W51_SSM_MODE, 0 }, {  192, CS42W51_SSM_MODE, 0 },
	{  256, CS42W51_SSM_MODE, 0 }, {  384, CS42W51_SSM_MODE, 0 },
	{  512, CS42W51_SSM_MODE, 0 }, {  768, CS42W51_SSM_MODE, 0 },
	{  128, CS42W51_DSM_MODE, 0 }, {  192, CS42W51_DSM_MODE, 0 },
	{  256, CS42W51_DSM_MODE, 0 }, {  384, CS42W51_DSM_MODE, 0 },
};

static stwuct cs42w51_watios swave_auto_watios[] = {
	{ 1024, CS42W51_QSM_MODE, 0 }, { 1536, CS42W51_QSM_MODE, 0 },
	{ 2048, CS42W51_QSM_MODE, 1 }, { 3072, CS42W51_QSM_MODE, 1 },
	{  512, CS42W51_HSM_MODE, 0 }, {  768, CS42W51_HSM_MODE, 0 },
	{ 1024, CS42W51_HSM_MODE, 1 }, { 1536, CS42W51_HSM_MODE, 1 },
	{  256, CS42W51_SSM_MODE, 0 }, {  384, CS42W51_SSM_MODE, 0 },
	{  512, CS42W51_SSM_MODE, 1 }, {  768, CS42W51_SSM_MODE, 1 },
	{  128, CS42W51_DSM_MODE, 0 }, {  192, CS42W51_DSM_MODE, 0 },
	{  256, CS42W51_DSM_MODE, 1 }, {  384, CS42W51_DSM_MODE, 1 },
};

/*
 * Mastew mode mcwk/fs watios.
 * Wecommended configuwations awe SSM fow 4-50khz and DSM fow 50-100kHz wanges
 * The tabwe bewow pwovides suppowt of fowwowing watios:
 * 128: SSM (%128) with div2 disabwed
 * 256: SSM (%128) with div2 enabwed
 * In both cases, if sampwing wate is above 50kHz, SSM is ovewwidden
 * with DSM (%128) configuwation
 */
static stwuct cs42w51_watios mastew_watios[] = {
	{ 128, CS42W51_SSM_MODE, 0 }, { 256, CS42W51_SSM_MODE, 1 },
};

static int cs42w51_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42w51_pwivate *cs42w51 = snd_soc_component_get_dwvdata(component);

	cs42w51->mcwk = fweq;
	wetuwn 0;
}

static int cs42w51_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams,
		stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42w51_pwivate *cs42w51 = snd_soc_component_get_dwvdata(component);
	int wet;
	unsigned int i;
	unsigned int wate;
	unsigned int watio;
	stwuct cs42w51_watios *watios = NUWW;
	int nw_watios = 0;
	int intf_ctw, powew_ctw, fmt, mode;

	switch (cs42w51->func) {
	case MODE_MASTEW:
		watios = mastew_watios;
		nw_watios = AWWAY_SIZE(mastew_watios);
		bweak;
	case MODE_SWAVE:
		watios = swave_watios;
		nw_watios = AWWAY_SIZE(swave_watios);
		bweak;
	case MODE_SWAVE_AUTO:
		watios = swave_auto_watios;
		nw_watios = AWWAY_SIZE(swave_auto_watios);
		bweak;
	}

	/* Figuwe out which MCWK/WWCK watio to use */
	wate = pawams_wate(pawams);     /* Sampwing wate, in Hz */
	watio = cs42w51->mcwk / wate;    /* MCWK/WWCK watio */
	fow (i = 0; i < nw_watios; i++) {
		if (watios[i].watio == watio)
			bweak;
	}

	if (i == nw_watios) {
		/* We did not find a matching watio */
		dev_eww(component->dev, "couwd not find matching watio\n");
		wetuwn -EINVAW;
	}

	intf_ctw = snd_soc_component_wead(component, CS42W51_INTF_CTW);
	powew_ctw = snd_soc_component_wead(component, CS42W51_MIC_POWEW_CTW);

	intf_ctw &= ~(CS42W51_INTF_CTW_MASTEW | CS42W51_INTF_CTW_ADC_I2S
			| CS42W51_INTF_CTW_DAC_FOWMAT(7));
	powew_ctw &= ~(CS42W51_MIC_POWEW_CTW_SPEED(3)
			| CS42W51_MIC_POWEW_CTW_MCWK_DIV2);

	switch (cs42w51->func) {
	case MODE_MASTEW:
		intf_ctw |= CS42W51_INTF_CTW_MASTEW;
		mode = watios[i].speed_mode;
		/* Fowce DSM mode if sampwing wate is above 50kHz */
		if (wate > 50000)
			mode = CS42W51_DSM_MODE;
		powew_ctw |= CS42W51_MIC_POWEW_CTW_SPEED(mode);
		/*
		 * Auto detect mode is not appwicabwe fow mastew mode and has to
		 * be disabwed. Othewwise SPEED[1:0] bits wiww be ignowed.
		 */
		powew_ctw &= ~CS42W51_MIC_POWEW_CTW_AUTO;
		bweak;
	case MODE_SWAVE:
		powew_ctw |= CS42W51_MIC_POWEW_CTW_SPEED(watios[i].speed_mode);
		bweak;
	case MODE_SWAVE_AUTO:
		powew_ctw |= CS42W51_MIC_POWEW_CTW_AUTO;
		bweak;
	}

	switch (cs42w51->audio_mode) {
	case SND_SOC_DAIFMT_I2S:
		intf_ctw |= CS42W51_INTF_CTW_ADC_I2S;
		intf_ctw |= CS42W51_INTF_CTW_DAC_FOWMAT(CS42W51_DAC_DIF_I2S);
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		intf_ctw |= CS42W51_INTF_CTW_DAC_FOWMAT(CS42W51_DAC_DIF_WJ24);
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		switch (pawams_width(pawams)) {
		case 16:
			fmt = CS42W51_DAC_DIF_WJ16;
			bweak;
		case 18:
			fmt = CS42W51_DAC_DIF_WJ18;
			bweak;
		case 20:
			fmt = CS42W51_DAC_DIF_WJ20;
			bweak;
		case 24:
			fmt = CS42W51_DAC_DIF_WJ24;
			bweak;
		defauwt:
			dev_eww(component->dev, "unknown fowmat\n");
			wetuwn -EINVAW;
		}
		intf_ctw |= CS42W51_INTF_CTW_DAC_FOWMAT(fmt);
		bweak;
	defauwt:
		dev_eww(component->dev, "unknown fowmat\n");
		wetuwn -EINVAW;
	}

	if (watios[i].mcwk)
		powew_ctw |= CS42W51_MIC_POWEW_CTW_MCWK_DIV2;

	wet = snd_soc_component_wwite(component, CS42W51_INTF_CTW, intf_ctw);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_wwite(component, CS42W51_MIC_POWEW_CTW, powew_ctw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int cs42w51_dai_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	int weg;
	int mask = CS42W51_DAC_OUT_CTW_DACA_MUTE|CS42W51_DAC_OUT_CTW_DACB_MUTE;

	weg = snd_soc_component_wead(component, CS42W51_DAC_OUT_CTW);

	if (mute)
		weg |= mask;
	ewse
		weg &= ~mask;

	wetuwn snd_soc_component_wwite(component, CS42W51_DAC_OUT_CTW, weg);
}

static int cs42w51_of_xwate_dai_id(stwuct snd_soc_component *component,
				   stwuct device_node *endpoint)
{
	/* wetuwn dai id 0, whatevew the endpoint index */
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cs42w51_dai_ops = {
	.hw_pawams      = cs42w51_hw_pawams,
	.set_syscwk     = cs42w51_set_dai_syscwk,
	.set_fmt        = cs42w51_set_dai_fmt,
	.mute_stweam    = cs42w51_dai_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew cs42w51_dai = {
	.name = "cs42w51-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = CS42W51_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = CS42W51_FOWMATS,
	},
	.ops = &cs42w51_dai_ops,
};

static int cs42w51_component_pwobe(stwuct snd_soc_component *component)
{
	int wet, weg;
	stwuct snd_soc_dapm_context *dapm;
	stwuct cs42w51_pwivate *cs42w51;

	cs42w51 = snd_soc_component_get_dwvdata(component);
	dapm = snd_soc_component_get_dapm(component);

	if (cs42w51->mcwk_handwe)
		snd_soc_dapm_new_contwows(dapm, cs42w51_dapm_mcwk_widgets, 1);

	/*
	 * DAC configuwation
	 * - Use signaw pwocessow
	 * - auto mute
	 * - vow changes immediate
	 * - no de-emphasize
	 */
	weg = CS42W51_DAC_CTW_DATA_SEW(1)
		| CS42W51_DAC_CTW_AMUTE | CS42W51_DAC_CTW_DACSZ(0);
	wet = snd_soc_component_wwite(component, CS42W51_DAC_CTW, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_device_cs42w51 = {
	.pwobe			= cs42w51_component_pwobe,
	.contwows		= cs42w51_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs42w51_snd_contwows),
	.dapm_widgets		= cs42w51_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs42w51_dapm_widgets),
	.dapm_woutes		= cs42w51_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs42w51_woutes),
	.of_xwate_dai_id	= cs42w51_of_xwate_dai_id,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static boow cs42w51_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W51_POWEW_CTW1:
	case CS42W51_MIC_POWEW_CTW:
	case CS42W51_INTF_CTW:
	case CS42W51_MIC_CTW:
	case CS42W51_ADC_CTW:
	case CS42W51_ADC_INPUT:
	case CS42W51_DAC_OUT_CTW:
	case CS42W51_DAC_CTW:
	case CS42W51_AWC_PGA_CTW:
	case CS42W51_AWC_PGB_CTW:
	case CS42W51_ADCA_ATT:
	case CS42W51_ADCB_ATT:
	case CS42W51_ADCA_VOW:
	case CS42W51_ADCB_VOW:
	case CS42W51_PCMA_VOW:
	case CS42W51_PCMB_VOW:
	case CS42W51_BEEP_FWEQ:
	case CS42W51_BEEP_VOW:
	case CS42W51_BEEP_CONF:
	case CS42W51_TONE_CTW:
	case CS42W51_AOUTA_VOW:
	case CS42W51_AOUTB_VOW:
	case CS42W51_PCM_MIXEW:
	case CS42W51_WIMIT_THWES_DIS:
	case CS42W51_WIMIT_WEW:
	case CS42W51_WIMIT_ATT:
	case CS42W51_AWC_EN:
	case CS42W51_AWC_WEW:
	case CS42W51_AWC_THWES:
	case CS42W51_NOISE_CONF:
	case CS42W51_CHAWGE_FWEQ:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs42w51_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W51_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs42w51_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42W51_CHIP_WEV_ID:
	case CS42W51_POWEW_CTW1:
	case CS42W51_MIC_POWEW_CTW:
	case CS42W51_INTF_CTW:
	case CS42W51_MIC_CTW:
	case CS42W51_ADC_CTW:
	case CS42W51_ADC_INPUT:
	case CS42W51_DAC_OUT_CTW:
	case CS42W51_DAC_CTW:
	case CS42W51_AWC_PGA_CTW:
	case CS42W51_AWC_PGB_CTW:
	case CS42W51_ADCA_ATT:
	case CS42W51_ADCB_ATT:
	case CS42W51_ADCA_VOW:
	case CS42W51_ADCB_VOW:
	case CS42W51_PCMA_VOW:
	case CS42W51_PCMB_VOW:
	case CS42W51_BEEP_FWEQ:
	case CS42W51_BEEP_VOW:
	case CS42W51_BEEP_CONF:
	case CS42W51_TONE_CTW:
	case CS42W51_AOUTA_VOW:
	case CS42W51_AOUTB_VOW:
	case CS42W51_PCM_MIXEW:
	case CS42W51_WIMIT_THWES_DIS:
	case CS42W51_WIMIT_WEW:
	case CS42W51_WIMIT_ATT:
	case CS42W51_AWC_EN:
	case CS42W51_AWC_WEW:
	case CS42W51_AWC_THWES:
	case CS42W51_NOISE_CONF:
	case CS42W51_STATUS:
	case CS42W51_CHAWGE_FWEQ:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

const stwuct wegmap_config cs42w51_wegmap = {
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.use_singwe_wwite = twue,
	.weadabwe_weg = cs42w51_weadabwe_weg,
	.vowatiwe_weg = cs42w51_vowatiwe_weg,
	.wwiteabwe_weg = cs42w51_wwiteabwe_weg,
	.max_wegistew = CS42W51_CHAWGE_FWEQ,
	.cache_type = WEGCACHE_MAPWE,
};
EXPOWT_SYMBOW_GPW(cs42w51_wegmap);

int cs42w51_pwobe(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct cs42w51_pwivate *cs42w51;
	unsigned int vaw;
	int wet, i;

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cs42w51 = devm_kzawwoc(dev, sizeof(stwuct cs42w51_pwivate),
			       GFP_KEWNEW);
	if (!cs42w51)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, cs42w51);
	cs42w51->wegmap = wegmap;

	cs42w51->mcwk_handwe = devm_cwk_get_optionaw(dev, "MCWK");
	if (IS_EWW(cs42w51->mcwk_handwe))
		wetuwn PTW_EWW(cs42w51->mcwk_handwe);

	fow (i = 0; i < AWWAY_SIZE(cs42w51->suppwies); i++)
		cs42w51->suppwies[i].suppwy = cs42w51_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(cs42w51->suppwies),
				      cs42w51->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs42w51->suppwies),
				    cs42w51->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	cs42w51->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(cs42w51->weset_gpio))
		wetuwn PTW_EWW(cs42w51->weset_gpio);

	if (cs42w51->weset_gpio) {
		dev_dbg(dev, "Wewease weset gpio\n");
		gpiod_set_vawue_cansweep(cs42w51->weset_gpio, 0);
		mdeway(2);
	}

	/* Vewify that we have a CS42W51 */
	wet = wegmap_wead(wegmap, CS42W51_CHIP_WEV_ID, &vaw);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wead I2C\n");
		goto ewwow;
	}

	if ((vaw != CS42W51_MK_CHIP_WEV(CS42W51_CHIP_ID, CS42W51_CHIP_WEV_A)) &&
	    (vaw != CS42W51_MK_CHIP_WEV(CS42W51_CHIP_ID, CS42W51_CHIP_WEV_B))) {
		dev_eww(dev, "Invawid chip id: %x\n", vaw);
		wet = -ENODEV;
		goto ewwow;
	}
	dev_info(dev, "Ciwwus Wogic CS42W51, Wevision: %02X\n",
		 vaw & CS42W51_CHIP_WEV_MASK);

	wet = devm_snd_soc_wegistew_component(dev,
			&soc_component_device_cs42w51, &cs42w51_dai, 1);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	weguwatow_buwk_disabwe(AWWAY_SIZE(cs42w51->suppwies),
			       cs42w51->suppwies);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cs42w51_pwobe);

void cs42w51_wemove(stwuct device *dev)
{
	stwuct cs42w51_pwivate *cs42w51 = dev_get_dwvdata(dev);
	int wet;

	gpiod_set_vawue_cansweep(cs42w51->weset_gpio, 1);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(cs42w51->suppwies),
				     cs42w51->suppwies);
	if (wet)
		dev_wawn(dev, "Faiwed to disabwe aww weguwatows (%pe)\n",
			 EWW_PTW(wet));

}
EXPOWT_SYMBOW_GPW(cs42w51_wemove);

int __maybe_unused cs42w51_suspend(stwuct device *dev)
{
	stwuct cs42w51_pwivate *cs42w51 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(cs42w51->wegmap, twue);
	wegcache_mawk_diwty(cs42w51->wegmap);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cs42w51_suspend);

int __maybe_unused cs42w51_wesume(stwuct device *dev)
{
	stwuct cs42w51_pwivate *cs42w51 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(cs42w51->wegmap, fawse);

	wetuwn wegcache_sync(cs42w51->wegmap);
}
EXPOWT_SYMBOW_GPW(cs42w51_wesume);

MODUWE_AUTHOW("Awnaud Patawd <awnaud.patawd@wtp-net.owg>");
MODUWE_DESCWIPTION("Ciwwus Wogic CS42W51 AWSA SoC Codec Dwivew");
MODUWE_WICENSE("GPW");
