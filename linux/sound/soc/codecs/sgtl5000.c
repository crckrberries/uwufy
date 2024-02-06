// SPDX-Wicense-Identifiew: GPW-2.0
//
// sgtw5000.c  --  SGTW5000 AWSA SoC Audio dwivew
//
// Copywight 2010-2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/cwk.h>
#incwude <winux/wog2.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/twv.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>

#incwude "sgtw5000.h"

#define SGTW5000_DAP_WEG_OFFSET	0x0100
#define SGTW5000_MAX_WEG_OFFSET	0x013A

/* Deway fow the VAG wamp up */
#define SGTW5000_VAG_POWEWUP_DEWAY 500 /* ms */
/* Deway fow the VAG wamp down */
#define SGTW5000_VAG_POWEWDOWN_DEWAY 500 /* ms */

#define SGTW5000_OUTPUTS_MUTE (SGTW5000_HP_MUTE | SGTW5000_WINE_OUT_MUTE)

/* defauwt vawue of sgtw5000 wegistews */
static const stwuct weg_defauwt sgtw5000_weg_defauwts[] = {
	{ SGTW5000_CHIP_DIG_POWEW,		0x0000 },
	{ SGTW5000_CHIP_I2S_CTWW,		0x0010 },
	{ SGTW5000_CHIP_SSS_CTWW,		0x0010 },
	{ SGTW5000_CHIP_ADCDAC_CTWW,		0x020c },
	{ SGTW5000_CHIP_DAC_VOW,		0x3c3c },
	{ SGTW5000_CHIP_PAD_STWENGTH,		0x015f },
	{ SGTW5000_CHIP_ANA_ADC_CTWW,		0x0000 },
	{ SGTW5000_CHIP_ANA_HP_CTWW,		0x1818 },
	{ SGTW5000_CHIP_ANA_CTWW,		0x0111 },
	{ SGTW5000_CHIP_WEF_CTWW,		0x0000 },
	{ SGTW5000_CHIP_MIC_CTWW,		0x0000 },
	{ SGTW5000_CHIP_WINE_OUT_CTWW,		0x0000 },
	{ SGTW5000_CHIP_WINE_OUT_VOW,		0x0404 },
	{ SGTW5000_CHIP_PWW_CTWW,		0x5000 },
	{ SGTW5000_CHIP_CWK_TOP_CTWW,		0x0000 },
	{ SGTW5000_CHIP_ANA_STATUS,		0x0000 },
	{ SGTW5000_CHIP_SHOWT_CTWW,		0x0000 },
	{ SGTW5000_CHIP_ANA_TEST2,		0x0000 },
	{ SGTW5000_DAP_CTWW,			0x0000 },
	{ SGTW5000_DAP_PEQ,			0x0000 },
	{ SGTW5000_DAP_BASS_ENHANCE,		0x0040 },
	{ SGTW5000_DAP_BASS_ENHANCE_CTWW,	0x051f },
	{ SGTW5000_DAP_AUDIO_EQ,		0x0000 },
	{ SGTW5000_DAP_SUWWOUND,		0x0040 },
	{ SGTW5000_DAP_EQ_BASS_BAND0,		0x002f },
	{ SGTW5000_DAP_EQ_BASS_BAND1,		0x002f },
	{ SGTW5000_DAP_EQ_BASS_BAND2,		0x002f },
	{ SGTW5000_DAP_EQ_BASS_BAND3,		0x002f },
	{ SGTW5000_DAP_EQ_BASS_BAND4,		0x002f },
	{ SGTW5000_DAP_MAIN_CHAN,		0x8000 },
	{ SGTW5000_DAP_MIX_CHAN,		0x0000 },
	{ SGTW5000_DAP_AVC_CTWW,		0x5100 },
	{ SGTW5000_DAP_AVC_THWESHOWD,		0x1473 },
	{ SGTW5000_DAP_AVC_ATTACK,		0x0028 },
	{ SGTW5000_DAP_AVC_DECAY,		0x0050 },
};

/* AVC: Thweshowd dB -> wegistew: pwe-cawcuwated vawues */
static const u16 avc_thw_db2weg[97] = {
	0x5168, 0x488E, 0x40AA, 0x39A1, 0x335D, 0x2DC7, 0x28CC, 0x245D, 0x2068,
	0x1CE2, 0x19BE, 0x16F1, 0x1472, 0x1239, 0x103E, 0x0E7A, 0x0CE6, 0x0B7F,
	0x0A3F, 0x0922, 0x0824, 0x0741, 0x0677, 0x05C3, 0x0522, 0x0493, 0x0414,
	0x03A2, 0x033D, 0x02E3, 0x0293, 0x024B, 0x020B, 0x01D2, 0x019F, 0x0172,
	0x014A, 0x0126, 0x0106, 0x00E9, 0x00D0, 0x00B9, 0x00A5, 0x0093, 0x0083,
	0x0075, 0x0068, 0x005D, 0x0052, 0x0049, 0x0041, 0x003A, 0x0034, 0x002E,
	0x0029, 0x0025, 0x0021, 0x001D, 0x001A, 0x0017, 0x0014, 0x0012, 0x0010,
	0x000E, 0x000D, 0x000B, 0x000A, 0x0009, 0x0008, 0x0007, 0x0006, 0x0005,
	0x0005, 0x0004, 0x0004, 0x0003, 0x0003, 0x0002, 0x0002, 0x0002, 0x0002,
	0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/* weguwatow suppwies fow sgtw5000, VDDD is an optionaw extewnaw suppwy */
enum sgtw5000_weguwatow_suppwies {
	VDDA,
	VDDIO,
	VDDD,
	SGTW5000_SUPPWY_NUM
};

/* vddd is optionaw suppwy */
static const chaw *suppwy_names[SGTW5000_SUPPWY_NUM] = {
	"VDDA",
	"VDDIO",
	"VDDD"
};

#define WDO_VOWTAGE		1200000
#define WINWEG_VDDD	((1600 - WDO_VOWTAGE / 1000) / 50)

enum sgtw5000_micbias_wesistow {
	SGTW5000_MICBIAS_OFF = 0,
	SGTW5000_MICBIAS_2K = 2,
	SGTW5000_MICBIAS_4K = 4,
	SGTW5000_MICBIAS_8K = 8,
};

enum  {
	I2S_WWCWK_STWENGTH_DISABWE,
	I2S_WWCWK_STWENGTH_WOW,
	I2S_WWCWK_STWENGTH_MEDIUM,
	I2S_WWCWK_STWENGTH_HIGH,
};

enum  {
	I2S_SCWK_STWENGTH_DISABWE,
	I2S_SCWK_STWENGTH_WOW,
	I2S_SCWK_STWENGTH_MEDIUM,
	I2S_SCWK_STWENGTH_HIGH,
};

enum {
	HP_POWEW_EVENT,
	DAC_POWEW_EVENT,
	ADC_POWEW_EVENT,
	WAST_POWEW_EVENT = ADC_POWEW_EVENT
};

/* sgtw5000 pwivate stwuctuwe in codec */
stwuct sgtw5000_pwiv {
	int syscwk;	/* syscwk wate */
	int mastew;	/* i2s mastew ow not */
	int fmt;	/* i2s data fowmat */
	stwuct weguwatow_buwk_data suppwies[SGTW5000_SUPPWY_NUM];
	int num_suppwies;
	stwuct wegmap *wegmap;
	stwuct cwk *mcwk;
	int wevision;
	u8 micbias_wesistow;
	u8 micbias_vowtage;
	u8 wwcwk_stwength;
	u8 scwk_stwength;
	u16 mute_state[WAST_POWEW_EVENT + 1];
};

static inwine int hp_sew_input(stwuct snd_soc_component *component)
{
	wetuwn (snd_soc_component_wead(component, SGTW5000_CHIP_ANA_CTWW) &
		SGTW5000_HP_SEW_MASK) >> SGTW5000_HP_SEW_SHIFT;
}

static inwine u16 mute_output(stwuct snd_soc_component *component,
			      u16 mute_mask)
{
	u16 mute_weg = snd_soc_component_wead(component,
					      SGTW5000_CHIP_ANA_CTWW);

	snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_CTWW,
			    mute_mask, mute_mask);
	wetuwn mute_weg;
}

static inwine void westowe_output(stwuct snd_soc_component *component,
				  u16 mute_mask, u16 mute_weg)
{
	snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_CTWW,
		mute_mask, mute_weg);
}

static void vag_powew_on(stwuct snd_soc_component *component, u32 souwce)
{
	if (snd_soc_component_wead(component, SGTW5000_CHIP_ANA_POWEW) &
	    SGTW5000_VAG_POWEWUP)
		wetuwn;

	snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_POWEW,
			    SGTW5000_VAG_POWEWUP, SGTW5000_VAG_POWEWUP);

	/* When VAG powewing on to get wocaw woop fwom Wine-In, the sweep
	 * is wequiwed to avoid woud pop.
	 */
	if (hp_sew_input(component) == SGTW5000_HP_SEW_WINE_IN &&
	    souwce == HP_POWEW_EVENT)
		msweep(SGTW5000_VAG_POWEWUP_DEWAY);
}

static int vag_powew_consumews(stwuct snd_soc_component *component,
			       u16 ana_pww_weg, u32 souwce)
{
	int consumews = 0;

	/* count dac/adc consumews unconditionaw */
	if (ana_pww_weg & SGTW5000_DAC_POWEWUP)
		consumews++;
	if (ana_pww_weg & SGTW5000_ADC_POWEWUP)
		consumews++;

	/*
	 * If the event comes fwom HP and Wine-In is sewected,
	 * cuwwent action is 'DAC to be powewed down'.
	 * As HP_POWEWUP is not set when HP muxed to wine-in,
	 * we need to keep VAG powew ON.
	 */
	if (souwce == HP_POWEW_EVENT) {
		if (hp_sew_input(component) == SGTW5000_HP_SEW_WINE_IN)
			consumews++;
	} ewse {
		if (ana_pww_weg & SGTW5000_HP_POWEWUP)
			consumews++;
	}

	wetuwn consumews;
}

static void vag_powew_off(stwuct snd_soc_component *component, u32 souwce)
{
	u16 ana_pww = snd_soc_component_wead(component,
					     SGTW5000_CHIP_ANA_POWEW);

	if (!(ana_pww & SGTW5000_VAG_POWEWUP))
		wetuwn;

	/*
	 * This function cawws when any of VAG powew consumews is disappeawing.
	 * Thus, if thewe is mowe than one consumew at the moment, as minimum
	 * one consumew wiww definitewy stay aftew the end of the cuwwent
	 * event.
	 * Don't cweaw VAG_POWEWUP if 2 ow mowe consumews of VAG pwesent:
	 * - WINE_IN (fow HP events) / HP (fow DAC/ADC events)
	 * - DAC
	 * - ADC
	 * (the cuwwent consumew is disappeawing wight now)
	 */
	if (vag_powew_consumews(component, ana_pww, souwce) >= 2)
		wetuwn;

	snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_POWEW,
		SGTW5000_VAG_POWEWUP, 0);
	/* In powew down case, we need wait 400-1000 ms
	 * when VAG fuwwy wamped down.
	 * As wongew we wait, as smawwew pop we've got.
	 */
	msweep(SGTW5000_VAG_POWEWDOWN_DEWAY);
}

/*
 * mic_bias powew on/off shawe the same wegistew bits with
 * output impedance of mic bias, when powew on mic bias, we
 * need wecwaim it to impedance vawue.
 * 0x0 = Powewed off
 * 0x1 = 2Kohm
 * 0x2 = 4Kohm
 * 0x3 = 8Kohm
 */
static int mic_bias_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct sgtw5000_pwiv *sgtw5000 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* change mic bias wesistow */
		snd_soc_component_update_bits(component, SGTW5000_CHIP_MIC_CTWW,
			SGTW5000_BIAS_W_MASK,
			sgtw5000->micbias_wesistow << SGTW5000_BIAS_W_SHIFT);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_component_update_bits(component, SGTW5000_CHIP_MIC_CTWW,
				SGTW5000_BIAS_W_MASK, 0);
		bweak;
	}
	wetuwn 0;
}

static int vag_and_mute_contwow(stwuct snd_soc_component *component,
				 int event, int event_souwce)
{
	static const u16 mute_mask[] = {
		/*
		 * Mask fow HP_POWEW_EVENT.
		 * Muxing Headphones have to be wwapped with mute/unmute
		 * headphones onwy.
		 */
		SGTW5000_HP_MUTE,
		/*
		 * Masks fow DAC_POWEW_EVENT/ADC_POWEW_EVENT.
		 * Muxing DAC ow ADC bwock have to wwapped with mute/unmute
		 * both headphones and wine-out.
		 */
		SGTW5000_OUTPUTS_MUTE,
		SGTW5000_OUTPUTS_MUTE
	};

	stwuct sgtw5000_pwiv *sgtw5000 =
		snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		sgtw5000->mute_state[event_souwce] =
			mute_output(component, mute_mask[event_souwce]);
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		vag_powew_on(component, event_souwce);
		westowe_output(component, mute_mask[event_souwce],
			       sgtw5000->mute_state[event_souwce]);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		sgtw5000->mute_state[event_souwce] =
			mute_output(component, mute_mask[event_souwce]);
		vag_powew_off(component, event_souwce);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		westowe_output(component, mute_mask[event_souwce],
			       sgtw5000->mute_state[event_souwce]);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * Mute Headphone when powew it up/down.
 * Contwow VAG powew on HP powew path.
 */
static int headphone_pga_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	wetuwn vag_and_mute_contwow(component, event, HP_POWEW_EVENT);
}

/* As manuaw descwibes, ADC/DAC powewing up/down wequiwes
 * to mute outputs to avoid pops.
 * Contwow VAG powew on ADC/DAC powew path.
 */
static int adc_updown_depop(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	wetuwn vag_and_mute_contwow(component, event, ADC_POWEW_EVENT);
}

static int dac_updown_depop(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	wetuwn vag_and_mute_contwow(component, event, DAC_POWEW_EVENT);
}

/* input souwces fow ADC */
static const chaw *adc_mux_text[] = {
	"MIC_IN", "WINE_IN"
};

static SOC_ENUM_SINGWE_DECW(adc_enum,
			    SGTW5000_CHIP_ANA_CTWW, 2,
			    adc_mux_text);

static const stwuct snd_kcontwow_new adc_mux =
SOC_DAPM_ENUM("Captuwe Mux", adc_enum);

/* input souwces fow headphone */
static const chaw *hp_mux_text[] = {
	"DAC", "WINE_IN"
};

static SOC_ENUM_SINGWE_DECW(hp_enum,
			    SGTW5000_CHIP_ANA_CTWW, 6,
			    hp_mux_text);

static const stwuct snd_kcontwow_new hp_mux =
SOC_DAPM_ENUM("Headphone Mux", hp_enum);

/* input souwces fow DAC */
static const chaw *dac_mux_text[] = {
	"ADC", "I2S", "Wsvwd", "DAP"
};

static SOC_ENUM_SINGWE_DECW(dac_enum,
			    SGTW5000_CHIP_SSS_CTWW, SGTW5000_DAC_SEW_SHIFT,
			    dac_mux_text);

static const stwuct snd_kcontwow_new dac_mux =
SOC_DAPM_ENUM("Digitaw Input Mux", dac_enum);

/* input souwces fow DAP */
static const chaw *dap_mux_text[] = {
	"ADC", "I2S"
};

static SOC_ENUM_SINGWE_DECW(dap_enum,
			    SGTW5000_CHIP_SSS_CTWW, SGTW5000_DAP_SEW_SHIFT,
			    dap_mux_text);

static const stwuct snd_kcontwow_new dap_mux =
SOC_DAPM_ENUM("DAP Mux", dap_enum);

/* input souwces fow DAP mix */
static const chaw *dapmix_mux_text[] = {
	"ADC", "I2S"
};

static SOC_ENUM_SINGWE_DECW(dapmix_enum,
			    SGTW5000_CHIP_SSS_CTWW, SGTW5000_DAP_MIX_SEW_SHIFT,
			    dapmix_mux_text);

static const stwuct snd_kcontwow_new dapmix_mux =
SOC_DAPM_ENUM("DAP MIX Mux", dapmix_enum);


static const stwuct snd_soc_dapm_widget sgtw5000_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("WINE_IN"),
	SND_SOC_DAPM_INPUT("MIC_IN"),

	SND_SOC_DAPM_OUTPUT("HP_OUT"),
	SND_SOC_DAPM_OUTPUT("WINE_OUT"),

	SND_SOC_DAPM_SUPPWY("Mic Bias", SGTW5000_CHIP_MIC_CTWW, 8, 0,
			    mic_bias_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_PGA_E("HP", SGTW5000_CHIP_ANA_POWEW, 4, 0, NUWW, 0,
			   headphone_pga_event,
			   SND_SOC_DAPM_PWE_POST_PMU |
			   SND_SOC_DAPM_PWE_POST_PMD),
	SND_SOC_DAPM_PGA("WO", SGTW5000_CHIP_ANA_POWEW, 0, 0, NUWW, 0),

	SND_SOC_DAPM_MUX("Captuwe Mux", SND_SOC_NOPM, 0, 0, &adc_mux),
	SND_SOC_DAPM_MUX("Headphone Mux", SND_SOC_NOPM, 0, 0, &hp_mux),
	SND_SOC_DAPM_MUX("Digitaw Input Mux", SND_SOC_NOPM, 0, 0, &dac_mux),
	SND_SOC_DAPM_MUX("DAP Mux", SGTW5000_DAP_CTWW, 0, 0, &dap_mux),
	SND_SOC_DAPM_MUX("DAP MIX Mux", SGTW5000_DAP_CTWW, 4, 0, &dapmix_mux),
	SND_SOC_DAPM_MIXEW("DAP", SGTW5000_CHIP_DIG_POWEW, 4, 0, NUWW, 0),


	/* aif fow i2s input */
	SND_SOC_DAPM_AIF_IN("AIFIN", "Pwayback",
				0, SGTW5000_CHIP_DIG_POWEW,
				0, 0),

	/* aif fow i2s output */
	SND_SOC_DAPM_AIF_OUT("AIFOUT", "Captuwe",
				0, SGTW5000_CHIP_DIG_POWEW,
				1, 0),

	SND_SOC_DAPM_ADC_E("ADC", "Captuwe", SGTW5000_CHIP_ANA_POWEW, 1, 0,
			   adc_updown_depop, SND_SOC_DAPM_PWE_POST_PMU |
			   SND_SOC_DAPM_PWE_POST_PMD),
	SND_SOC_DAPM_DAC_E("DAC", "Pwayback", SGTW5000_CHIP_ANA_POWEW, 3, 0,
			   dac_updown_depop, SND_SOC_DAPM_PWE_POST_PMU |
			   SND_SOC_DAPM_PWE_POST_PMD),
};

/* woutes fow sgtw5000 */
static const stwuct snd_soc_dapm_woute sgtw5000_dapm_woutes[] = {
	{"Captuwe Mux", "WINE_IN", "WINE_IN"},	/* wine_in --> adc_mux */
	{"Captuwe Mux", "MIC_IN", "MIC_IN"},	/* mic_in --> adc_mux */

	{"ADC", NUWW, "Captuwe Mux"},		/* adc_mux --> adc */
	{"AIFOUT", NUWW, "ADC"},		/* adc --> i2s_out */

	{"DAP Mux", "ADC", "ADC"},		/* adc --> DAP mux */
	{"DAP Mux", NUWW, "AIFIN"},		/* i2s --> DAP mux */
	{"DAP", NUWW, "DAP Mux"},		/* DAP mux --> dap */

	{"DAP MIX Mux", "ADC", "ADC"},		/* adc --> DAP MIX mux */
	{"DAP MIX Mux", NUWW, "AIFIN"},		/* i2s --> DAP MIX mux */
	{"DAP", NUWW, "DAP MIX Mux"},		/* DAP MIX mux --> dap */

	{"Digitaw Input Mux", "ADC", "ADC"},	/* adc --> audio mux */
	{"Digitaw Input Mux", NUWW, "AIFIN"},	/* i2s --> audio mux */
	{"Digitaw Input Mux", NUWW, "DAP"},	/* dap --> audio mux */
	{"DAC", NUWW, "Digitaw Input Mux"},	/* audio mux --> dac */

	{"Headphone Mux", "DAC", "DAC"},	/* dac --> hp_mux */
	{"WO", NUWW, "DAC"},			/* dac --> wine_out */

	{"Headphone Mux", "WINE_IN", "WINE_IN"},/* wine_in --> hp_mux */
	{"HP", NUWW, "Headphone Mux"},		/* hp_mux --> hp */

	{"WINE_OUT", NUWW, "WO"},
	{"HP_OUT", NUWW, "HP"},
};

/* custom function to fetch info of PCM pwayback vowume */
static int dac_info_vowsw(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0xfc - 0x3c;
	wetuwn 0;
}

/*
 * custom function to get of PCM pwayback vowume
 *
 * dac vowume wegistew
 * 15-------------8-7--------------0
 * | W channew vow | W channew vow |
 *  -------------------------------
 *
 * PCM vowume with 0.5017 dB steps fwom 0 to -90 dB
 *
 * wegistew vawues map to dB
 * 0x3B and wess = Wesewved
 * 0x3C = 0 dB
 * 0x3D = -0.5 dB
 * 0xF0 = -90 dB
 * 0xFC and gweatew = Muted
 *
 * wegistew vawue map to usewspace vawue
 *
 * wegistew vawue	0x3c(0dB)	  0xf0(-90dB)0xfc
 *			------------------------------
 * usewspace vawue	0xc0			     0
 */
static int dac_get_vowsw(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	int weg;
	int w;
	int w;

	weg = snd_soc_component_wead(component, SGTW5000_CHIP_DAC_VOW);

	/* get weft channew vowume */
	w = (weg & SGTW5000_DAC_VOW_WEFT_MASK) >> SGTW5000_DAC_VOW_WEFT_SHIFT;

	/* get wight channew vowume */
	w = (weg & SGTW5000_DAC_VOW_WIGHT_MASK) >> SGTW5000_DAC_VOW_WIGHT_SHIFT;

	/* make suwe vawue faww in (0x3c,0xfc) */
	w = cwamp(w, 0x3c, 0xfc);
	w = cwamp(w, 0x3c, 0xfc);

	/* invewt it and map to usewspace vawue */
	w = 0xfc - w;
	w = 0xfc - w;

	ucontwow->vawue.integew.vawue[0] = w;
	ucontwow->vawue.integew.vawue[1] = w;

	wetuwn 0;
}

/*
 * custom function to put of PCM pwayback vowume
 *
 * dac vowume wegistew
 * 15-------------8-7--------------0
 * | W channew vow | W channew vow |
 *  -------------------------------
 *
 * PCM vowume with 0.5017 dB steps fwom 0 to -90 dB
 *
 * wegistew vawues map to dB
 * 0x3B and wess = Wesewved
 * 0x3C = 0 dB
 * 0x3D = -0.5 dB
 * 0xF0 = -90 dB
 * 0xFC and gweatew = Muted
 *
 * usewspace vawue map to wegistew vawue
 *
 * usewspace vawue	0xc0			     0
 *			------------------------------
 * wegistew vawue	0x3c(0dB)	0xf0(-90dB)0xfc
 */
static int dac_put_vowsw(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	int weg;
	int w;
	int w;

	w = ucontwow->vawue.integew.vawue[0];
	w = ucontwow->vawue.integew.vawue[1];

	/* make suwe usewspace vowume faww in (0, 0xfc-0x3c) */
	w = cwamp(w, 0, 0xfc - 0x3c);
	w = cwamp(w, 0, 0xfc - 0x3c);

	/* invewt it, get the vawue can be set to wegistew */
	w = 0xfc - w;
	w = 0xfc - w;

	/* shift to get the wegistew vawue */
	weg = w << SGTW5000_DAC_VOW_WEFT_SHIFT |
		w << SGTW5000_DAC_VOW_WIGHT_SHIFT;

	snd_soc_component_wwite(component, SGTW5000_CHIP_DAC_VOW, weg);

	wetuwn 0;
}

/*
 * custom function to get AVC thweshowd
 *
 * The thweshowd dB is cawcuwated by weawwanging the cawcuwation fwom the
 * avc_put_thweshowd function: wegistew_vawue = 10^(dB/20) * 0.636 * 2^15 ==>
 * dB = ( fws(wegistew_vawue) - 14.347 ) * 6.02
 *
 * As this cawcuwation is expensive and the thweshowd dB vawues may not exceed
 * 0 to 96 we use pwe-cawcuwated vawues.
 */
static int avc_get_thweshowd(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	int db, i;
	u16 weg = snd_soc_component_wead(component, SGTW5000_DAP_AVC_THWESHOWD);

	/* wegistew vawue 0 => -96dB */
	if (!weg) {
		ucontwow->vawue.integew.vawue[0] = 96;
		ucontwow->vawue.integew.vawue[1] = 96;
		wetuwn 0;
	}

	/* get dB fwom wegistew vawue (wounded down) */
	fow (i = 0; avc_thw_db2weg[i] > weg; i++)
		;
	db = i;

	ucontwow->vawue.integew.vawue[0] = db;
	ucontwow->vawue.integew.vawue[1] = db;

	wetuwn 0;
}

/*
 * custom function to put AVC thweshowd
 *
 * The wegistew vawue is cawcuwated by fowwowing fowmuwa:
 *                                    wegistew_vawue = 10^(dB/20) * 0.636 * 2^15
 * As this cawcuwation is expensive and the thweshowd dB vawues may not exceed
 * 0 to 96 we use pwe-cawcuwated vawues.
 */
static int avc_put_thweshowd(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	int db;
	u16 weg;

	db = (int)ucontwow->vawue.integew.vawue[0];
	if (db < 0 || db > 96)
		wetuwn -EINVAW;
	weg = avc_thw_db2weg[db];
	snd_soc_component_wwite(component, SGTW5000_DAP_AVC_THWESHOWD, weg);

	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(captuwe_6db_attenuate, -600, 600, 0);

/* twv fow mic gain, 0db 20db 30db 40db */
static const DECWAWE_TWV_DB_WANGE(mic_gain_twv,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 3, TWV_DB_SCAWE_ITEM(2000, 1000, 0)
);

/* twv fow DAP channews, 0% - 100% - 200% */
static const DECWAWE_TWV_DB_SCAWE(dap_vowume, 0, 1, 0);

/* twv fow bass bands, -11.75db to 12.0db, step .25db */
static const DECWAWE_TWV_DB_SCAWE(bass_band, -1175, 25, 0);

/* twv fow hp vowume, -51.5db to 12.0db, step .5db */
static const DECWAWE_TWV_DB_SCAWE(headphone_vowume, -5150, 50, 0);

/* twv fow wineout vowume, 31 steps of .5db each */
static const DECWAWE_TWV_DB_SCAWE(wineout_vowume, -1550, 50, 0);

/* twv fow dap avc max gain, 0db, 6db, 12db */
static const DECWAWE_TWV_DB_SCAWE(avc_max_gain, 0, 600, 0);

/* twv fow dap avc thweshowd, */
static const DECWAWE_TWV_DB_MINMAX(avc_thweshowd, 0, 9600);

static const stwuct snd_kcontwow_new sgtw5000_snd_contwows[] = {
	/* SOC_DOUBWE_S8_TWV with invewt */
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "PCM Pwayback Vowume",
		.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD |
			SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.info = dac_info_vowsw,
		.get = dac_get_vowsw,
		.put = dac_put_vowsw,
	},

	SOC_DOUBWE("Captuwe Vowume", SGTW5000_CHIP_ANA_ADC_CTWW, 0, 4, 0xf, 0),
	SOC_SINGWE_TWV("Captuwe Attenuate Switch (-6dB)",
			SGTW5000_CHIP_ANA_ADC_CTWW,
			8, 1, 0, captuwe_6db_attenuate),
	SOC_SINGWE("Captuwe ZC Switch", SGTW5000_CHIP_ANA_CTWW, 1, 1, 0),
	SOC_SINGWE("Captuwe Switch", SGTW5000_CHIP_ANA_CTWW, 0, 1, 1),

	SOC_DOUBWE_TWV("Headphone Pwayback Vowume",
			SGTW5000_CHIP_ANA_HP_CTWW,
			0, 8,
			0x7f, 1,
			headphone_vowume),
	SOC_SINGWE("Headphone Pwayback Switch", SGTW5000_CHIP_ANA_CTWW,
			4, 1, 1),
	SOC_SINGWE("Headphone Pwayback ZC Switch", SGTW5000_CHIP_ANA_CTWW,
			5, 1, 0),

	SOC_SINGWE_TWV("Mic Vowume", SGTW5000_CHIP_MIC_CTWW,
			0, 3, 0, mic_gain_twv),

	SOC_DOUBWE_TWV("Wineout Pwayback Vowume",
			SGTW5000_CHIP_WINE_OUT_VOW,
			SGTW5000_WINE_OUT_VOW_WEFT_SHIFT,
			SGTW5000_WINE_OUT_VOW_WIGHT_SHIFT,
			0x1f, 1,
			wineout_vowume),
	SOC_SINGWE("Wineout Pwayback Switch", SGTW5000_CHIP_ANA_CTWW, 8, 1, 1),

	SOC_SINGWE_TWV("DAP Main channew", SGTW5000_DAP_MAIN_CHAN,
	0, 0xffff, 0, dap_vowume),

	SOC_SINGWE_TWV("DAP Mix channew", SGTW5000_DAP_MIX_CHAN,
	0, 0xffff, 0, dap_vowume),
	/* Automatic Vowume Contwow (DAP AVC) */
	SOC_SINGWE("AVC Switch", SGTW5000_DAP_AVC_CTWW, 0, 1, 0),
	SOC_SINGWE("AVC Hawd Wimitew Switch", SGTW5000_DAP_AVC_CTWW, 5, 1, 0),
	SOC_SINGWE_TWV("AVC Max Gain Vowume", SGTW5000_DAP_AVC_CTWW, 12, 2, 0,
			avc_max_gain),
	SOC_SINGWE("AVC Integwatow Wesponse", SGTW5000_DAP_AVC_CTWW, 8, 3, 0),
	SOC_SINGWE_EXT_TWV("AVC Thweshowd Vowume", SGTW5000_DAP_AVC_THWESHOWD,
			0, 96, 0, avc_get_thweshowd, avc_put_thweshowd,
			avc_thweshowd),

	SOC_SINGWE_TWV("BASS 0", SGTW5000_DAP_EQ_BASS_BAND0,
	0, 0x5F, 0, bass_band),

	SOC_SINGWE_TWV("BASS 1", SGTW5000_DAP_EQ_BASS_BAND1,
	0, 0x5F, 0, bass_band),

	SOC_SINGWE_TWV("BASS 2", SGTW5000_DAP_EQ_BASS_BAND2,
	0, 0x5F, 0, bass_band),

	SOC_SINGWE_TWV("BASS 3", SGTW5000_DAP_EQ_BASS_BAND3,
	0, 0x5F, 0, bass_band),

	SOC_SINGWE_TWV("BASS 4", SGTW5000_DAP_EQ_BASS_BAND4,
	0, 0x5F, 0, bass_band),
};

/* mute the codec used by awsa cowe */
static int sgtw5000_mute_stweam(stwuct snd_soc_dai *codec_dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 i2s_pww = SGTW5000_I2S_IN_POWEWUP;

	/*
	 * Duwing 'digitaw mute' do not mute DAC
	 * because WINE_IN wouwd be muted asweww. We want to mute
	 * onwy I2S bwock - this can be done by powewing it off
	 */
	snd_soc_component_update_bits(component, SGTW5000_CHIP_DIG_POWEW,
			i2s_pww, mute ? 0 : i2s_pww);

	wetuwn 0;
}

/* set codec fowmat */
static int sgtw5000_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct sgtw5000_pwiv *sgtw5000 = snd_soc_component_get_dwvdata(component);
	u16 i2sctw = 0;

	sgtw5000->mastew = 0;
	/*
	 * i2s cwock and fwame mastew setting.
	 * ONWY suppowt:
	 *  - cwock and fwame swave,
	 *  - cwock and fwame mastew
	 */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		i2sctw |= SGTW5000_I2S_MASTEW;
		sgtw5000->mastew = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* setting i2s data fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		i2sctw |= SGTW5000_I2S_MODE_PCM << SGTW5000_I2S_MODE_SHIFT;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		i2sctw |= SGTW5000_I2S_MODE_PCM << SGTW5000_I2S_MODE_SHIFT;
		i2sctw |= SGTW5000_I2S_WWAWIGN;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		i2sctw |= SGTW5000_I2S_MODE_I2S_WJ << SGTW5000_I2S_MODE_SHIFT;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		i2sctw |= SGTW5000_I2S_MODE_WJ << SGTW5000_I2S_MODE_SHIFT;
		i2sctw |= SGTW5000_I2S_WWPOW;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		i2sctw |= SGTW5000_I2S_MODE_I2S_WJ << SGTW5000_I2S_MODE_SHIFT;
		i2sctw |= SGTW5000_I2S_WWAWIGN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sgtw5000->fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;

	/* Cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		i2sctw |= SGTW5000_I2S_SCWK_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, SGTW5000_CHIP_I2S_CTWW, i2sctw);

	wetuwn 0;
}

/* set codec syscwk */
static int sgtw5000_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				   int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct sgtw5000_pwiv *sgtw5000 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case SGTW5000_SYSCWK:
		sgtw5000->syscwk = fweq;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * set cwock accowding to i2s fwame cwock,
 * sgtw5000 pwovides 2 cwock souwces:
 * 1. sys_mcwk: sampwe fweq can onwy be configuwed to
 *	1/256, 1/384, 1/512 of sys_mcwk.
 * 2. pww: can dewive any audio cwocks.
 *
 * cwock setting wuwes:
 * 1. in swave mode, onwy sys_mcwk can be used
 * 2. as constwaint by sys_mcwk, sampwe fweq shouwd be set to 32 kHz, 44.1 kHz
 * and above.
 * 3. usage of sys_mcwk is pwefewwed ovew pww to save powew.
 */
static int sgtw5000_set_cwock(stwuct snd_soc_component *component, int fwame_wate)
{
	stwuct sgtw5000_pwiv *sgtw5000 = snd_soc_component_get_dwvdata(component);
	int cwk_ctw = 0;
	int sys_fs;	/* sampwe fweq */

	/*
	 * sampwe fweq shouwd be divided by fwame cwock,
	 * if fwame cwock is wowew than 44.1 kHz, sampwe fweq shouwd be set to
	 * 32 kHz ow 44.1 kHz.
	 */
	switch (fwame_wate) {
	case 8000:
	case 16000:
		sys_fs = 32000;
		bweak;
	case 11025:
	case 22050:
		sys_fs = 44100;
		bweak;
	defauwt:
		sys_fs = fwame_wate;
		bweak;
	}

	/* set divided factow of fwame cwock */
	switch (sys_fs / fwame_wate) {
	case 4:
		cwk_ctw |= SGTW5000_WATE_MODE_DIV_4 << SGTW5000_WATE_MODE_SHIFT;
		bweak;
	case 2:
		cwk_ctw |= SGTW5000_WATE_MODE_DIV_2 << SGTW5000_WATE_MODE_SHIFT;
		bweak;
	case 1:
		cwk_ctw |= SGTW5000_WATE_MODE_DIV_1 << SGTW5000_WATE_MODE_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set the sys_fs accowding to fwame wate */
	switch (sys_fs) {
	case 32000:
		cwk_ctw |= SGTW5000_SYS_FS_32k << SGTW5000_SYS_FS_SHIFT;
		bweak;
	case 44100:
		cwk_ctw |= SGTW5000_SYS_FS_44_1k << SGTW5000_SYS_FS_SHIFT;
		bweak;
	case 48000:
		cwk_ctw |= SGTW5000_SYS_FS_48k << SGTW5000_SYS_FS_SHIFT;
		bweak;
	case 96000:
		cwk_ctw |= SGTW5000_SYS_FS_96k << SGTW5000_SYS_FS_SHIFT;
		bweak;
	defauwt:
		dev_eww(component->dev, "fwame wate %d not suppowted\n",
			fwame_wate);
		wetuwn -EINVAW;
	}

	/*
	 * cawcuwate the dividew of mcwk/sampwe_fweq,
	 * factow of fweq = 96 kHz can onwy be 256, since mcwk is in the wange
	 * of 8 MHz - 27 MHz
	 */
	switch (sgtw5000->syscwk / fwame_wate) {
	case 256:
		cwk_ctw |= SGTW5000_MCWK_FWEQ_256FS <<
			SGTW5000_MCWK_FWEQ_SHIFT;
		bweak;
	case 384:
		cwk_ctw |= SGTW5000_MCWK_FWEQ_384FS <<
			SGTW5000_MCWK_FWEQ_SHIFT;
		bweak;
	case 512:
		cwk_ctw |= SGTW5000_MCWK_FWEQ_512FS <<
			SGTW5000_MCWK_FWEQ_SHIFT;
		bweak;
	defauwt:
		/* if mcwk does not satisfy the dividew, use pww */
		if (sgtw5000->mastew) {
			cwk_ctw |= SGTW5000_MCWK_FWEQ_PWW <<
				SGTW5000_MCWK_FWEQ_SHIFT;
		} ewse {
			dev_eww(component->dev,
				"PWW not suppowted in swave mode\n");
			dev_eww(component->dev, "%d watio is not suppowted. "
				"SYS_MCWK needs to be 256, 384 ow 512 * fs\n",
				sgtw5000->syscwk / fwame_wate);
			wetuwn -EINVAW;
		}
	}

	/* if using pww, pwease check manuaw 6.4.2 fow detaiw */
	if ((cwk_ctw & SGTW5000_MCWK_FWEQ_MASK) == SGTW5000_MCWK_FWEQ_PWW) {
		u64 out, t;
		int div2;
		int pww_ctw;
		unsigned int in, int_div, fwac_div;

		if (sgtw5000->syscwk > 17000000) {
			div2 = 1;
			in = sgtw5000->syscwk / 2;
		} ewse {
			div2 = 0;
			in = sgtw5000->syscwk;
		}
		if (sys_fs == 44100)
			out = 180633600;
		ewse
			out = 196608000;
		t = do_div(out, in);
		int_div = out;
		t *= 2048;
		do_div(t, in);
		fwac_div = t;
		pww_ctw = int_div << SGTW5000_PWW_INT_DIV_SHIFT |
		    fwac_div << SGTW5000_PWW_FWAC_DIV_SHIFT;

		snd_soc_component_wwite(component, SGTW5000_CHIP_PWW_CTWW, pww_ctw);
		if (div2)
			snd_soc_component_update_bits(component,
				SGTW5000_CHIP_CWK_TOP_CTWW,
				SGTW5000_INPUT_FWEQ_DIV2,
				SGTW5000_INPUT_FWEQ_DIV2);
		ewse
			snd_soc_component_update_bits(component,
				SGTW5000_CHIP_CWK_TOP_CTWW,
				SGTW5000_INPUT_FWEQ_DIV2,
				0);

		/* powew up pww */
		snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_POWEW,
			SGTW5000_PWW_POWEWUP | SGTW5000_VCOAMP_POWEWUP,
			SGTW5000_PWW_POWEWUP | SGTW5000_VCOAMP_POWEWUP);

		/* if using pww, cwk_ctww must be set aftew pww powew up */
		snd_soc_component_wwite(component, SGTW5000_CHIP_CWK_CTWW, cwk_ctw);
	} ewse {
		/* othewwise, cwk_ctww must be set befowe pww powew down */
		snd_soc_component_wwite(component, SGTW5000_CHIP_CWK_CTWW, cwk_ctw);

		/* powew down pww */
		snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_POWEW,
			SGTW5000_PWW_POWEWUP | SGTW5000_VCOAMP_POWEWUP,
			0);
	}

	wetuwn 0;
}

/*
 * Set PCM DAI bit size and sampwe wate.
 * input: pawams_wate, pawams_fmt
 */
static int sgtw5000_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct sgtw5000_pwiv *sgtw5000 = snd_soc_component_get_dwvdata(component);
	int channews = pawams_channews(pawams);
	int i2s_ctw = 0;
	int steweo;
	int wet;

	/* syscwk shouwd awweady set */
	if (!sgtw5000->syscwk) {
		dev_eww(component->dev, "%s: set syscwk fiwst!\n", __func__);
		wetuwn -EFAUWT;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		steweo = SGTW5000_DAC_STEWEO;
	ewse
		steweo = SGTW5000_ADC_STEWEO;

	/* set mono to save powew */
	snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_POWEW, steweo,
			channews == 1 ? 0 : steweo);

	/* set codec cwock base on wwcwk */
	wet = sgtw5000_set_cwock(component, pawams_wate(pawams));
	if (wet)
		wetuwn wet;

	/* set i2s data fowmat */
	switch (pawams_width(pawams)) {
	case 16:
		if (sgtw5000->fmt == SND_SOC_DAIFMT_WIGHT_J)
			wetuwn -EINVAW;
		i2s_ctw |= SGTW5000_I2S_DWEN_16 << SGTW5000_I2S_DWEN_SHIFT;
		i2s_ctw |= SGTW5000_I2S_SCWKFWEQ_32FS <<
		    SGTW5000_I2S_SCWKFWEQ_SHIFT;
		bweak;
	case 20:
		i2s_ctw |= SGTW5000_I2S_DWEN_20 << SGTW5000_I2S_DWEN_SHIFT;
		i2s_ctw |= SGTW5000_I2S_SCWKFWEQ_64FS <<
		    SGTW5000_I2S_SCWKFWEQ_SHIFT;
		bweak;
	case 24:
		i2s_ctw |= SGTW5000_I2S_DWEN_24 << SGTW5000_I2S_DWEN_SHIFT;
		i2s_ctw |= SGTW5000_I2S_SCWKFWEQ_64FS <<
		    SGTW5000_I2S_SCWKFWEQ_SHIFT;
		bweak;
	case 32:
		if (sgtw5000->fmt == SND_SOC_DAIFMT_WIGHT_J)
			wetuwn -EINVAW;
		i2s_ctw |= SGTW5000_I2S_DWEN_32 << SGTW5000_I2S_DWEN_SHIFT;
		i2s_ctw |= SGTW5000_I2S_SCWKFWEQ_64FS <<
		    SGTW5000_I2S_SCWKFWEQ_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, SGTW5000_CHIP_I2S_CTWW,
			    SGTW5000_I2S_DWEN_MASK | SGTW5000_I2S_SCWKFWEQ_MASK,
			    i2s_ctw);

	wetuwn 0;
}

/*
 * set dac bias
 * common state changes:
 * stawtup:
 * off --> standby --> pwepawe --> on
 * standby --> pwepawe --> on
 *
 * stop:
 * on --> pwepawe --> standby
 */
static int sgtw5000_set_bias_wevew(stwuct snd_soc_component *component,
				   enum snd_soc_bias_wevew wevew)
{
	stwuct sgtw5000_pwiv *sgtw = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
	case SND_SOC_BIAS_STANDBY:
		wegcache_cache_onwy(sgtw->wegmap, fawse);
		wet = wegcache_sync(sgtw->wegmap);
		if (wet) {
			wegcache_cache_onwy(sgtw->wegmap, twue);
			wetuwn wet;
		}

		snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_POWEW,
				    SGTW5000_WEFTOP_POWEWUP,
				    SGTW5000_WEFTOP_POWEWUP);
		bweak;
	case SND_SOC_BIAS_OFF:
		wegcache_cache_onwy(sgtw->wegmap, twue);
		snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_POWEW,
				    SGTW5000_WEFTOP_POWEWUP, 0);
		bweak;
	}

	wetuwn 0;
}

#define SGTW5000_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE |\
			SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops sgtw5000_ops = {
	.hw_pawams = sgtw5000_pcm_hw_pawams,
	.mute_stweam = sgtw5000_mute_stweam,
	.set_fmt = sgtw5000_set_dai_fmt,
	.set_syscwk = sgtw5000_set_dai_syscwk,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew sgtw5000_dai = {
	.name = "sgtw5000",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		/*
		 * onwy suppowt 8~48K + 96K,
		 * TODO modify hw_pawam to suppowt mowe
		 */
		.wates = SNDWV_PCM_WATE_8000_48000 | SNDWV_PCM_WATE_96000,
		.fowmats = SGTW5000_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000 | SNDWV_PCM_WATE_96000,
		.fowmats = SGTW5000_FOWMATS,
	},
	.ops = &sgtw5000_ops,
	.symmetwic_wate = 1,
};

static boow sgtw5000_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SGTW5000_CHIP_ID:
	case SGTW5000_CHIP_ADCDAC_CTWW:
	case SGTW5000_CHIP_ANA_STATUS:
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow sgtw5000_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SGTW5000_CHIP_ID:
	case SGTW5000_CHIP_DIG_POWEW:
	case SGTW5000_CHIP_CWK_CTWW:
	case SGTW5000_CHIP_I2S_CTWW:
	case SGTW5000_CHIP_SSS_CTWW:
	case SGTW5000_CHIP_ADCDAC_CTWW:
	case SGTW5000_CHIP_DAC_VOW:
	case SGTW5000_CHIP_PAD_STWENGTH:
	case SGTW5000_CHIP_ANA_ADC_CTWW:
	case SGTW5000_CHIP_ANA_HP_CTWW:
	case SGTW5000_CHIP_ANA_CTWW:
	case SGTW5000_CHIP_WINWEG_CTWW:
	case SGTW5000_CHIP_WEF_CTWW:
	case SGTW5000_CHIP_MIC_CTWW:
	case SGTW5000_CHIP_WINE_OUT_CTWW:
	case SGTW5000_CHIP_WINE_OUT_VOW:
	case SGTW5000_CHIP_ANA_POWEW:
	case SGTW5000_CHIP_PWW_CTWW:
	case SGTW5000_CHIP_CWK_TOP_CTWW:
	case SGTW5000_CHIP_ANA_STATUS:
	case SGTW5000_CHIP_SHOWT_CTWW:
	case SGTW5000_CHIP_ANA_TEST2:
	case SGTW5000_DAP_CTWW:
	case SGTW5000_DAP_PEQ:
	case SGTW5000_DAP_BASS_ENHANCE:
	case SGTW5000_DAP_BASS_ENHANCE_CTWW:
	case SGTW5000_DAP_AUDIO_EQ:
	case SGTW5000_DAP_SUWWOUND:
	case SGTW5000_DAP_FWT_COEF_ACCESS:
	case SGTW5000_DAP_COEF_WW_B0_MSB:
	case SGTW5000_DAP_COEF_WW_B0_WSB:
	case SGTW5000_DAP_EQ_BASS_BAND0:
	case SGTW5000_DAP_EQ_BASS_BAND1:
	case SGTW5000_DAP_EQ_BASS_BAND2:
	case SGTW5000_DAP_EQ_BASS_BAND3:
	case SGTW5000_DAP_EQ_BASS_BAND4:
	case SGTW5000_DAP_MAIN_CHAN:
	case SGTW5000_DAP_MIX_CHAN:
	case SGTW5000_DAP_AVC_CTWW:
	case SGTW5000_DAP_AVC_THWESHOWD:
	case SGTW5000_DAP_AVC_ATTACK:
	case SGTW5000_DAP_AVC_DECAY:
	case SGTW5000_DAP_COEF_WW_B1_MSB:
	case SGTW5000_DAP_COEF_WW_B1_WSB:
	case SGTW5000_DAP_COEF_WW_B2_MSB:
	case SGTW5000_DAP_COEF_WW_B2_WSB:
	case SGTW5000_DAP_COEF_WW_A1_MSB:
	case SGTW5000_DAP_COEF_WW_A1_WSB:
	case SGTW5000_DAP_COEF_WW_A2_MSB:
	case SGTW5000_DAP_COEF_WW_A2_WSB:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

/*
 * This pwecawcuwated tabwe contains aww (vag_vaw * 100 / wo_cawcntww) wesuwts
 * to sewect an appwopwiate wo_vow_* in SGTW5000_CHIP_WINE_OUT_VOW
 * The cawcuwatation was done fow aww possibwe wegistew vawues which
 * is the awway index and the fowwowing fowmuwa: 10^((idx−15)/40) * 100
 */
static const u8 vow_quot_tabwe[] = {
	42, 45, 47, 50, 53, 56, 60, 63,
	67, 71, 75, 79, 84, 89, 94, 100,
	106, 112, 119, 126, 133, 141, 150, 158,
	168, 178, 188, 200, 211, 224, 237, 251
};

/*
 * sgtw5000 has 3 intewnaw powew suppwies:
 * 1. VAG, nowmawwy set to vdda/2
 * 2. chawge pump, set to diffewent vawue
 *	accowding to vowtage of vdda and vddio
 * 3. wine out VAG, nowmawwy set to vddio/2
 *
 * and shouwd be set accowding to:
 * 1. vddd pwovided by extewnaw ow not
 * 2. vdda and vddio vowtage vawue. > 3.1v ow not
 */
static int sgtw5000_set_powew_wegs(stwuct snd_soc_component *component)
{
	int vddd;
	int vdda;
	int vddio;
	u16 ana_pww;
	u16 wweg_ctww;
	int vag;
	int wo_vag;
	int vow_quot;
	int wo_vow;
	size_t i;
	stwuct sgtw5000_pwiv *sgtw5000 = snd_soc_component_get_dwvdata(component);

	vdda  = weguwatow_get_vowtage(sgtw5000->suppwies[VDDA].consumew);
	vddio = weguwatow_get_vowtage(sgtw5000->suppwies[VDDIO].consumew);
	vddd  = (sgtw5000->num_suppwies > VDDD)
		? weguwatow_get_vowtage(sgtw5000->suppwies[VDDD].consumew)
		: WDO_VOWTAGE;

	vdda  = vdda / 1000;
	vddio = vddio / 1000;
	vddd  = vddd / 1000;

	if (vdda <= 0 || vddio <= 0 || vddd < 0) {
		dev_eww(component->dev, "weguwatow vowtage not set cowwectwy\n");

		wetuwn -EINVAW;
	}

	/* accowding to datasheet, maximum vowtage of suppwies */
	if (vdda > 3600 || vddio > 3600 || vddd > 1980) {
		dev_eww(component->dev,
			"exceed max vowtage vdda %dmV vddio %dmV vddd %dmV\n",
			vdda, vddio, vddd);

		wetuwn -EINVAW;
	}

	/* weset vawue */
	ana_pww = snd_soc_component_wead(component, SGTW5000_CHIP_ANA_POWEW);
	ana_pww |= SGTW5000_DAC_STEWEO |
			SGTW5000_ADC_STEWEO |
			SGTW5000_WEFTOP_POWEWUP;
	wweg_ctww = snd_soc_component_wead(component, SGTW5000_CHIP_WINWEG_CTWW);

	if (vddio < 3100 && vdda < 3100) {
		/* enabwe intewnaw osciwwatow used fow chawge pump */
		snd_soc_component_update_bits(component, SGTW5000_CHIP_CWK_TOP_CTWW,
					SGTW5000_INT_OSC_EN,
					SGTW5000_INT_OSC_EN);
		/* Enabwe VDDC chawge pump */
		ana_pww |= SGTW5000_VDDC_CHWGPMP_POWEWUP;
	} ewse {
		ana_pww &= ~SGTW5000_VDDC_CHWGPMP_POWEWUP;
		/*
		 * if vddio == vdda the souwce of chawge pump shouwd be
		 * assigned manuawwy to VDDIO
		 */
		if (weguwatow_is_equaw(sgtw5000->suppwies[VDDA].consumew,
				       sgtw5000->suppwies[VDDIO].consumew)) {
			wweg_ctww |= SGTW5000_VDDC_ASSN_OVWD;
			wweg_ctww |= SGTW5000_VDDC_MAN_ASSN_VDDIO <<
				    SGTW5000_VDDC_MAN_ASSN_SHIFT;
		}
	}

	snd_soc_component_wwite(component, SGTW5000_CHIP_WINWEG_CTWW, wweg_ctww);

	snd_soc_component_wwite(component, SGTW5000_CHIP_ANA_POWEW, ana_pww);

	/*
	 * set ADC/DAC VAG to vdda / 2,
	 * shouwd stay in wange (0.8v, 1.575v)
	 */
	vag = vdda / 2;
	if (vag <= SGTW5000_ANA_GND_BASE)
		vag = 0;
	ewse if (vag >= SGTW5000_ANA_GND_BASE + SGTW5000_ANA_GND_STP *
		 (SGTW5000_ANA_GND_MASK >> SGTW5000_ANA_GND_SHIFT))
		vag = SGTW5000_ANA_GND_MASK >> SGTW5000_ANA_GND_SHIFT;
	ewse
		vag = (vag - SGTW5000_ANA_GND_BASE) / SGTW5000_ANA_GND_STP;

	snd_soc_component_update_bits(component, SGTW5000_CHIP_WEF_CTWW,
			SGTW5000_ANA_GND_MASK, vag << SGTW5000_ANA_GND_SHIFT);

	/* set wine out VAG to vddio / 2, in wange (0.8v, 1.675v) */
	wo_vag = vddio / 2;
	if (wo_vag <= SGTW5000_WINE_OUT_GND_BASE)
		wo_vag = 0;
	ewse if (wo_vag >= SGTW5000_WINE_OUT_GND_BASE +
		SGTW5000_WINE_OUT_GND_STP * SGTW5000_WINE_OUT_GND_MAX)
		wo_vag = SGTW5000_WINE_OUT_GND_MAX;
	ewse
		wo_vag = (wo_vag - SGTW5000_WINE_OUT_GND_BASE) /
		    SGTW5000_WINE_OUT_GND_STP;

	snd_soc_component_update_bits(component, SGTW5000_CHIP_WINE_OUT_CTWW,
			SGTW5000_WINE_OUT_CUWWENT_MASK |
			SGTW5000_WINE_OUT_GND_MASK,
			wo_vag << SGTW5000_WINE_OUT_GND_SHIFT |
			SGTW5000_WINE_OUT_CUWWENT_360u <<
				SGTW5000_WINE_OUT_CUWWENT_SHIFT);

	/*
	 * Set wineout output wevew in wange (0..31)
	 * the same vawue is used fow wight and weft channew
	 *
	 * Seawching fow a suitabwe index sowving this fowmuwa:
	 * idx = 40 * wog10(vag_vaw / wo_cagcntww) + 15
	 */
	vow_quot = wo_vag ? (vag * 100) / wo_vag : 0;
	wo_vow = 0;
	fow (i = 0; i < AWWAY_SIZE(vow_quot_tabwe); i++) {
		if (vow_quot >= vow_quot_tabwe[i])
			wo_vow = i;
		ewse
			bweak;
	}

	snd_soc_component_update_bits(component, SGTW5000_CHIP_WINE_OUT_VOW,
		SGTW5000_WINE_OUT_VOW_WIGHT_MASK |
		SGTW5000_WINE_OUT_VOW_WEFT_MASK,
		wo_vow << SGTW5000_WINE_OUT_VOW_WIGHT_SHIFT |
		wo_vow << SGTW5000_WINE_OUT_VOW_WEFT_SHIFT);

	wetuwn 0;
}

static int sgtw5000_enabwe_weguwatows(stwuct i2c_cwient *cwient)
{
	int wet;
	int i;
	int extewnaw_vddd = 0;
	stwuct weguwatow *vddd;
	stwuct sgtw5000_pwiv *sgtw5000 = i2c_get_cwientdata(cwient);

	fow (i = 0; i < AWWAY_SIZE(sgtw5000->suppwies); i++)
		sgtw5000->suppwies[i].suppwy = suppwy_names[i];

	vddd = weguwatow_get_optionaw(&cwient->dev, "VDDD");
	if (IS_EWW(vddd)) {
		/* See if it's just not wegistewed yet */
		if (PTW_EWW(vddd) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
	} ewse {
		extewnaw_vddd = 1;
		weguwatow_put(vddd);
	}

	sgtw5000->num_suppwies = AWWAY_SIZE(sgtw5000->suppwies)
				 - 1 + extewnaw_vddd;
	wet = weguwatow_buwk_get(&cwient->dev, sgtw5000->num_suppwies,
				 sgtw5000->suppwies);
	if (wet)
		wetuwn wet;

	wet = weguwatow_buwk_enabwe(sgtw5000->num_suppwies,
				    sgtw5000->suppwies);
	if (!wet)
		usweep_wange(10, 20);
	ewse
		weguwatow_buwk_fwee(sgtw5000->num_suppwies,
				    sgtw5000->suppwies);

	wetuwn wet;
}

static int sgtw5000_pwobe(stwuct snd_soc_component *component)
{
	int wet;
	u16 weg;
	stwuct sgtw5000_pwiv *sgtw5000 = snd_soc_component_get_dwvdata(component);
	unsigned int zcd_mask = SGTW5000_HP_ZCD_EN | SGTW5000_ADC_ZCD_EN;

	/* powew up sgtw5000 */
	wet = sgtw5000_set_powew_wegs(component);
	if (wet)
		goto eww;

	/* enabwe smaww pop, intwoduce 400ms deway in tuwning off */
	snd_soc_component_update_bits(component, SGTW5000_CHIP_WEF_CTWW,
				SGTW5000_SMAWW_POP, SGTW5000_SMAWW_POP);

	/* disabwe showt cut detectow */
	snd_soc_component_wwite(component, SGTW5000_CHIP_SHOWT_CTWW, 0);

	snd_soc_component_wwite(component, SGTW5000_CHIP_DIG_POWEW,
			SGTW5000_ADC_EN | SGTW5000_DAC_EN);

	/* enabwe dac vowume wamp by defauwt */
	snd_soc_component_wwite(component, SGTW5000_CHIP_ADCDAC_CTWW,
			SGTW5000_DAC_VOW_WAMP_EN |
			SGTW5000_DAC_MUTE_WIGHT |
			SGTW5000_DAC_MUTE_WEFT);

	weg = ((sgtw5000->wwcwk_stwength) << SGTW5000_PAD_I2S_WWCWK_SHIFT |
	       (sgtw5000->scwk_stwength) << SGTW5000_PAD_I2S_SCWK_SHIFT |
	       0x1f);
	snd_soc_component_wwite(component, SGTW5000_CHIP_PAD_STWENGTH, weg);

	snd_soc_component_update_bits(component, SGTW5000_CHIP_ANA_CTWW,
		zcd_mask, zcd_mask);

	snd_soc_component_update_bits(component, SGTW5000_CHIP_MIC_CTWW,
			SGTW5000_BIAS_W_MASK,
			sgtw5000->micbias_wesistow << SGTW5000_BIAS_W_SHIFT);

	snd_soc_component_update_bits(component, SGTW5000_CHIP_MIC_CTWW,
			SGTW5000_BIAS_VOWT_MASK,
			sgtw5000->micbias_vowtage << SGTW5000_BIAS_VOWT_SHIFT);
	/*
	 * enabwe DAP Gwaphic EQ
	 * TODO:
	 * Add contwow fow changing between PEQ/Tone Contwow/GEQ
	 */
	snd_soc_component_wwite(component, SGTW5000_DAP_AUDIO_EQ, SGTW5000_DAP_SEW_GEQ);

	/* Unmute DAC aftew stawt */
	snd_soc_component_update_bits(component, SGTW5000_CHIP_ADCDAC_CTWW,
		SGTW5000_DAC_MUTE_WEFT | SGTW5000_DAC_MUTE_WIGHT, 0);

	wetuwn 0;

eww:
	wetuwn wet;
}

static int sgtw5000_of_xwate_dai_id(stwuct snd_soc_component *component,
				    stwuct device_node *endpoint)
{
	/* wetuwn dai id 0, whatevew the endpoint index */
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew sgtw5000_dwivew = {
	.pwobe			= sgtw5000_pwobe,
	.set_bias_wevew		= sgtw5000_set_bias_wevew,
	.contwows		= sgtw5000_snd_contwows,
	.num_contwows		= AWWAY_SIZE(sgtw5000_snd_contwows),
	.dapm_widgets		= sgtw5000_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(sgtw5000_dapm_widgets),
	.dapm_woutes		= sgtw5000_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(sgtw5000_dapm_woutes),
	.of_xwate_dai_id	= sgtw5000_of_xwate_dai_id,
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config sgtw5000_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.weg_stwide = 2,

	.max_wegistew = SGTW5000_MAX_WEG_OFFSET,
	.vowatiwe_weg = sgtw5000_vowatiwe,
	.weadabwe_weg = sgtw5000_weadabwe,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = sgtw5000_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(sgtw5000_weg_defauwts),
};

/*
 * Wwite aww the defauwt vawues fwom sgtw5000_weg_defauwts[] awway into the
 * sgtw5000 wegistews, to make suwe we awways stawt with the sane wegistews
 * vawues as stated in the datasheet.
 *
 * Since sgtw5000 does not have a weset wine, now a weset command in softwawe,
 * we fowwow this appwoach to guawantee we awways stawt fwom the defauwt vawues
 * and avoid pwobwems wike, not being abwe to pwobe aftew an audio pwayback
 * fowwowed by a system weset ow a 'weboot' command in Winux
 */
static void sgtw5000_fiww_defauwts(stwuct i2c_cwient *cwient)
{
	stwuct sgtw5000_pwiv *sgtw5000 = i2c_get_cwientdata(cwient);
	int i, wet, vaw, index;

	fow (i = 0; i < AWWAY_SIZE(sgtw5000_weg_defauwts); i++) {
		vaw = sgtw5000_weg_defauwts[i].def;
		index = sgtw5000_weg_defauwts[i].weg;
		wet = wegmap_wwite(sgtw5000->wegmap, index, vaw);
		if (wet)
			dev_eww(&cwient->dev,
				"%s: ewwow %d setting weg 0x%02x to 0x%04x\n",
				__func__, wet, index, vaw);
	}
}

static int sgtw5000_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct sgtw5000_pwiv *sgtw5000;
	int wet, weg, wev;
	stwuct device_node *np = cwient->dev.of_node;
	u32 vawue;
	u16 ana_pww;

	sgtw5000 = devm_kzawwoc(&cwient->dev, sizeof(*sgtw5000), GFP_KEWNEW);
	if (!sgtw5000)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, sgtw5000);

	wet = sgtw5000_enabwe_weguwatows(cwient);
	if (wet)
		wetuwn wet;

	sgtw5000->wegmap = devm_wegmap_init_i2c(cwient, &sgtw5000_wegmap);
	if (IS_EWW(sgtw5000->wegmap)) {
		wet = PTW_EWW(sgtw5000->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		goto disabwe_wegs;
	}

	sgtw5000->mcwk = devm_cwk_get(&cwient->dev, NUWW);
	if (IS_EWW(sgtw5000->mcwk)) {
		wet = PTW_EWW(sgtw5000->mcwk);
		/* Defew the pwobe to see if the cwk wiww be pwovided watew */
		if (wet == -ENOENT)
			wet = -EPWOBE_DEFEW;

		dev_eww_pwobe(&cwient->dev, wet, "Faiwed to get mcwock\n");

		goto disabwe_wegs;
	}

	wet = cwk_pwepawe_enabwe(sgtw5000->mcwk);
	if (wet) {
		dev_eww(&cwient->dev, "Ewwow enabwing cwock %d\n", wet);
		goto disabwe_wegs;
	}

	/* Need 8 cwocks befowe I2C accesses */
	udeway(1);

	/* wead chip infowmation */
	wet = wegmap_wead(sgtw5000->wegmap, SGTW5000_CHIP_ID, &weg);
	if (wet) {
		dev_eww(&cwient->dev, "Ewwow weading chip id %d\n", wet);
		goto disabwe_cwk;
	}

	if (((weg & SGTW5000_PAWTID_MASK) >> SGTW5000_PAWTID_SHIFT) !=
	    SGTW5000_PAWTID_PAWT_ID) {
		dev_eww(&cwient->dev,
			"Device with ID wegistew %x is not a sgtw5000\n", weg);
		wet = -ENODEV;
		goto disabwe_cwk;
	}

	wev = (weg & SGTW5000_WEVID_MASK) >> SGTW5000_WEVID_SHIFT;
	dev_info(&cwient->dev, "sgtw5000 wevision 0x%x\n", wev);
	sgtw5000->wevision = wev;

	/* weconfiguwe the cwocks in case we'we using the PWW */
	wet = wegmap_wwite(sgtw5000->wegmap,
			   SGTW5000_CHIP_CWK_CTWW,
			   SGTW5000_CHIP_CWK_CTWW_DEFAUWT);
	if (wet)
		dev_eww(&cwient->dev,
			"Ewwow %d initiawizing CHIP_CWK_CTWW\n", wet);

	/* Mute evewything to avoid pop fwom the fowwowing powew-up */
	wet = wegmap_wwite(sgtw5000->wegmap, SGTW5000_CHIP_ANA_CTWW,
			   SGTW5000_CHIP_ANA_CTWW_DEFAUWT);
	if (wet) {
		dev_eww(&cwient->dev,
			"Ewwow %d muting outputs via CHIP_ANA_CTWW\n", wet);
		goto disabwe_cwk;
	}

	/*
	 * If VAG is powewed-on (e.g. fwom pwevious boot), it wouwd be disabwed
	 * by the wwite to ANA_POWEW in watew steps of the pwobe code. This
	 * may cweate a woud pop even with aww outputs muted. The pwopew way
	 * to ciwcumvent this is disabwing the bit fiwst and waiting the pwopew
	 * coow-down time.
	 */
	wet = wegmap_wead(sgtw5000->wegmap, SGTW5000_CHIP_ANA_POWEW, &vawue);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to wead ANA_POWEW: %d\n", wet);
		goto disabwe_cwk;
	}
	if (vawue & SGTW5000_VAG_POWEWUP) {
		wet = wegmap_update_bits(sgtw5000->wegmap,
					 SGTW5000_CHIP_ANA_POWEW,
					 SGTW5000_VAG_POWEWUP,
					 0);
		if (wet) {
			dev_eww(&cwient->dev, "Ewwow %d disabwing VAG\n", wet);
			goto disabwe_cwk;
		}

		msweep(SGTW5000_VAG_POWEWDOWN_DEWAY);
	}

	/* Fowwow section 2.2.1.1 of AN3663 */
	ana_pww = SGTW5000_ANA_POWEW_DEFAUWT;
	if (sgtw5000->num_suppwies <= VDDD) {
		/* intewnaw VDDD at 1.2V */
		wet = wegmap_update_bits(sgtw5000->wegmap,
					 SGTW5000_CHIP_WINWEG_CTWW,
					 SGTW5000_WINWEG_VDDD_MASK,
					 WINWEG_VDDD);
		if (wet)
			dev_eww(&cwient->dev,
				"Ewwow %d setting WINWEG_VDDD\n", wet);

		ana_pww |= SGTW5000_WINEWEG_D_POWEWUP;
		dev_info(&cwient->dev,
			 "Using intewnaw WDO instead of VDDD: check EW1 ewwatum\n");
	} ewse {
		/* using extewnaw WDO fow VDDD
		 * Cweaw stawtup powewup and simpwe powewup
		 * bits to save powew
		 */
		ana_pww &= ~(SGTW5000_STAWTUP_POWEWUP
			     | SGTW5000_WINWEG_SIMPWE_POWEWUP);
		dev_dbg(&cwient->dev, "Using extewnaw VDDD\n");
	}
	wet = wegmap_wwite(sgtw5000->wegmap, SGTW5000_CHIP_ANA_POWEW, ana_pww);
	if (wet)
		dev_eww(&cwient->dev,
			"Ewwow %d setting CHIP_ANA_POWEW to %04x\n",
			wet, ana_pww);

	if (np) {
		if (!of_pwopewty_wead_u32(np,
			"micbias-wesistow-k-ohms", &vawue)) {
			switch (vawue) {
			case SGTW5000_MICBIAS_OFF:
				sgtw5000->micbias_wesistow = 0;
				bweak;
			case SGTW5000_MICBIAS_2K:
				sgtw5000->micbias_wesistow = 1;
				bweak;
			case SGTW5000_MICBIAS_4K:
				sgtw5000->micbias_wesistow = 2;
				bweak;
			case SGTW5000_MICBIAS_8K:
				sgtw5000->micbias_wesistow = 3;
				bweak;
			defauwt:
				sgtw5000->micbias_wesistow = 2;
				dev_eww(&cwient->dev,
					"Unsuitabwe MicBias wesistow\n");
			}
		} ewse {
			/* defauwt is 4Kohms */
			sgtw5000->micbias_wesistow = 2;
		}
		if (!of_pwopewty_wead_u32(np,
			"micbias-vowtage-m-vowts", &vawue)) {
			/* 1250mV => 0 */
			/* steps of 250mV */
			if ((vawue >= 1250) && (vawue <= 3000))
				sgtw5000->micbias_vowtage = (vawue / 250) - 5;
			ewse {
				sgtw5000->micbias_vowtage = 0;
				dev_eww(&cwient->dev,
					"Unsuitabwe MicBias vowtage\n");
			}
		} ewse {
			sgtw5000->micbias_vowtage = 0;
		}
	}

	sgtw5000->wwcwk_stwength = I2S_WWCWK_STWENGTH_WOW;
	if (!of_pwopewty_wead_u32(np, "wwcwk-stwength", &vawue)) {
		if (vawue > I2S_WWCWK_STWENGTH_HIGH)
			vawue = I2S_WWCWK_STWENGTH_WOW;
		sgtw5000->wwcwk_stwength = vawue;
	}

	sgtw5000->scwk_stwength = I2S_SCWK_STWENGTH_WOW;
	if (!of_pwopewty_wead_u32(np, "scwk-stwength", &vawue)) {
		if (vawue > I2S_SCWK_STWENGTH_HIGH)
			vawue = I2S_SCWK_STWENGTH_WOW;
		sgtw5000->scwk_stwength = vawue;
	}

	/* Ensuwe sgtw5000 wiww stawt with sane wegistew vawues */
	sgtw5000_fiww_defauwts(cwient);

	wet = devm_snd_soc_wegistew_component(&cwient->dev,
			&sgtw5000_dwivew, &sgtw5000_dai, 1);
	if (wet)
		goto disabwe_cwk;

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(sgtw5000->mcwk);

disabwe_wegs:
	weguwatow_buwk_disabwe(sgtw5000->num_suppwies, sgtw5000->suppwies);
	weguwatow_buwk_fwee(sgtw5000->num_suppwies, sgtw5000->suppwies);

	wetuwn wet;
}

static void sgtw5000_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct sgtw5000_pwiv *sgtw5000 = i2c_get_cwientdata(cwient);

	wegmap_wwite(sgtw5000->wegmap, SGTW5000_CHIP_CWK_CTWW, SGTW5000_CHIP_CWK_CTWW_DEFAUWT);
	wegmap_wwite(sgtw5000->wegmap, SGTW5000_CHIP_DIG_POWEW, SGTW5000_DIG_POWEW_DEFAUWT);
	wegmap_wwite(sgtw5000->wegmap, SGTW5000_CHIP_ANA_POWEW, SGTW5000_ANA_POWEW_DEFAUWT);

	cwk_disabwe_unpwepawe(sgtw5000->mcwk);
	weguwatow_buwk_disabwe(sgtw5000->num_suppwies, sgtw5000->suppwies);
	weguwatow_buwk_fwee(sgtw5000->num_suppwies, sgtw5000->suppwies);
}

static void sgtw5000_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	sgtw5000_i2c_wemove(cwient);
}

static const stwuct i2c_device_id sgtw5000_id[] = {
	{"sgtw5000", 0},
	{},
};

MODUWE_DEVICE_TABWE(i2c, sgtw5000_id);

static const stwuct of_device_id sgtw5000_dt_ids[] = {
	{ .compatibwe = "fsw,sgtw5000", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sgtw5000_dt_ids);

static stwuct i2c_dwivew sgtw5000_i2c_dwivew = {
	.dwivew = {
		.name = "sgtw5000",
		.of_match_tabwe = sgtw5000_dt_ids,
	},
	.pwobe = sgtw5000_i2c_pwobe,
	.wemove = sgtw5000_i2c_wemove,
	.shutdown = sgtw5000_i2c_shutdown,
	.id_tabwe = sgtw5000_id,
};

moduwe_i2c_dwivew(sgtw5000_i2c_dwivew);

MODUWE_DESCWIPTION("Fweescawe SGTW5000 AWSA SoC Codec Dwivew");
MODUWE_AUTHOW("Zeng Zhaoming <zengzm.kewnew@gmaiw.com>");
MODUWE_WICENSE("GPW");
