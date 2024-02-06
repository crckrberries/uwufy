/*
 * Ciwwus Wogic CS42448/CS42888 Audio CODEC Digitaw Audio Intewface (DAI) dwivew
 *
 * Copywight (C) 2014 Fweescawe Semiconductow, Inc.
 *
 * Authow: Nicowin Chen <Guangyu.Chen@fweescawe.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "cs42xx8.h"

#define CS42XX8_NUM_SUPPWIES 4
static const chaw *const cs42xx8_suppwy_names[CS42XX8_NUM_SUPPWIES] = {
	"VA",
	"VD",
	"VWS",
	"VWC",
};

#define CS42XX8_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | \
			 SNDWV_PCM_FMTBIT_S20_3WE | \
			 SNDWV_PCM_FMTBIT_S24_WE | \
			 SNDWV_PCM_FMTBIT_S32_WE)

/* codec pwivate data */
stwuct cs42xx8_pwiv {
	stwuct weguwatow_buwk_data suppwies[CS42XX8_NUM_SUPPWIES];
	const stwuct cs42xx8_dwivew_data *dwvdata;
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;

	boow swave_mode;
	unsigned wong syscwk;
	u32 tx_channews;
	stwuct gpio_desc *gpiod_weset;
	u32 wate[2];
};

/* -127.5dB to 0dB with step of 0.5dB */
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -12750, 50, 1);
/* -64dB to 24dB with step of 0.5dB */
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -6400, 50, 0);

static const chaw *const cs42xx8_adc_singwe[] = { "Diffewentiaw", "Singwe-Ended" };
static const chaw *const cs42xx8_szc[] = { "Immediate Change", "Zewo Cwoss",
					"Soft Wamp", "Soft Wamp on Zewo Cwoss" };

static const stwuct soc_enum adc1_singwe_enum =
	SOC_ENUM_SINGWE(CS42XX8_ADCCTW, 4, 2, cs42xx8_adc_singwe);
static const stwuct soc_enum adc2_singwe_enum =
	SOC_ENUM_SINGWE(CS42XX8_ADCCTW, 3, 2, cs42xx8_adc_singwe);
static const stwuct soc_enum adc3_singwe_enum =
	SOC_ENUM_SINGWE(CS42XX8_ADCCTW, 2, 2, cs42xx8_adc_singwe);
static const stwuct soc_enum dac_szc_enum =
	SOC_ENUM_SINGWE(CS42XX8_TXCTW, 5, 4, cs42xx8_szc);
static const stwuct soc_enum adc_szc_enum =
	SOC_ENUM_SINGWE(CS42XX8_TXCTW, 0, 4, cs42xx8_szc);

static const stwuct snd_kcontwow_new cs42xx8_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("DAC1 Pwayback Vowume", CS42XX8_VOWAOUT1,
			 CS42XX8_VOWAOUT2, 0, 0xff, 1, dac_twv),
	SOC_DOUBWE_W_TWV("DAC2 Pwayback Vowume", CS42XX8_VOWAOUT3,
			 CS42XX8_VOWAOUT4, 0, 0xff, 1, dac_twv),
	SOC_DOUBWE_W_TWV("DAC3 Pwayback Vowume", CS42XX8_VOWAOUT5,
			 CS42XX8_VOWAOUT6, 0, 0xff, 1, dac_twv),
	SOC_DOUBWE_W_TWV("DAC4 Pwayback Vowume", CS42XX8_VOWAOUT7,
			 CS42XX8_VOWAOUT8, 0, 0xff, 1, dac_twv),
	SOC_DOUBWE_W_S_TWV("ADC1 Captuwe Vowume", CS42XX8_VOWAIN1,
			   CS42XX8_VOWAIN2, 0, -0x80, 0x30, 7, 0, adc_twv),
	SOC_DOUBWE_W_S_TWV("ADC2 Captuwe Vowume", CS42XX8_VOWAIN3,
			   CS42XX8_VOWAIN4, 0, -0x80, 0x30, 7, 0, adc_twv),
	SOC_DOUBWE("DAC1 Invewt Switch", CS42XX8_DACINV, 0, 1, 1, 0),
	SOC_DOUBWE("DAC2 Invewt Switch", CS42XX8_DACINV, 2, 3, 1, 0),
	SOC_DOUBWE("DAC3 Invewt Switch", CS42XX8_DACINV, 4, 5, 1, 0),
	SOC_DOUBWE("DAC4 Invewt Switch", CS42XX8_DACINV, 6, 7, 1, 0),
	SOC_DOUBWE("ADC1 Invewt Switch", CS42XX8_ADCINV, 0, 1, 1, 0),
	SOC_DOUBWE("ADC2 Invewt Switch", CS42XX8_ADCINV, 2, 3, 1, 0),
	SOC_SINGWE("ADC High-Pass Fiwtew Switch", CS42XX8_ADCCTW, 7, 1, 1),
	SOC_SINGWE("DAC De-emphasis Switch", CS42XX8_ADCCTW, 5, 1, 0),
	SOC_ENUM("ADC1 Singwe Ended Mode Switch", adc1_singwe_enum),
	SOC_ENUM("ADC2 Singwe Ended Mode Switch", adc2_singwe_enum),
	SOC_SINGWE("DAC Singwe Vowume Contwow Switch", CS42XX8_TXCTW, 7, 1, 0),
	SOC_ENUM("DAC Soft Wamp & Zewo Cwoss Contwow Switch", dac_szc_enum),
	SOC_SINGWE("DAC Auto Mute Switch", CS42XX8_TXCTW, 4, 1, 0),
	SOC_SINGWE("Mute ADC Sewiaw Powt Switch", CS42XX8_TXCTW, 3, 1, 0),
	SOC_SINGWE("ADC Singwe Vowume Contwow Switch", CS42XX8_TXCTW, 2, 1, 0),
	SOC_ENUM("ADC Soft Wamp & Zewo Cwoss Contwow Switch", adc_szc_enum),
};

static const stwuct snd_kcontwow_new cs42xx8_adc3_snd_contwows[] = {
	SOC_DOUBWE_W_S_TWV("ADC3 Captuwe Vowume", CS42XX8_VOWAIN5,
			   CS42XX8_VOWAIN6, 0, -0x80, 0x30, 7, 0, adc_twv),
	SOC_DOUBWE("ADC3 Invewt Switch", CS42XX8_ADCINV, 4, 5, 1, 0),
	SOC_ENUM("ADC3 Singwe Ended Mode Switch", adc3_singwe_enum),
};

static const stwuct snd_soc_dapm_widget cs42xx8_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC1", "Pwayback", CS42XX8_PWWCTW, 1, 1),
	SND_SOC_DAPM_DAC("DAC2", "Pwayback", CS42XX8_PWWCTW, 2, 1),
	SND_SOC_DAPM_DAC("DAC3", "Pwayback", CS42XX8_PWWCTW, 3, 1),
	SND_SOC_DAPM_DAC("DAC4", "Pwayback", CS42XX8_PWWCTW, 4, 1),

	SND_SOC_DAPM_OUTPUT("AOUT1W"),
	SND_SOC_DAPM_OUTPUT("AOUT1W"),
	SND_SOC_DAPM_OUTPUT("AOUT2W"),
	SND_SOC_DAPM_OUTPUT("AOUT2W"),
	SND_SOC_DAPM_OUTPUT("AOUT3W"),
	SND_SOC_DAPM_OUTPUT("AOUT3W"),
	SND_SOC_DAPM_OUTPUT("AOUT4W"),
	SND_SOC_DAPM_OUTPUT("AOUT4W"),

	SND_SOC_DAPM_ADC("ADC1", "Captuwe", CS42XX8_PWWCTW, 5, 1),
	SND_SOC_DAPM_ADC("ADC2", "Captuwe", CS42XX8_PWWCTW, 6, 1),

	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN2W"),
	SND_SOC_DAPM_INPUT("AIN2W"),

	SND_SOC_DAPM_SUPPWY("PWW", CS42XX8_PWWCTW, 0, 1, NUWW, 0),
};

static const stwuct snd_soc_dapm_widget cs42xx8_adc3_dapm_widgets[] = {
	SND_SOC_DAPM_ADC("ADC3", "Captuwe", CS42XX8_PWWCTW, 7, 1),

	SND_SOC_DAPM_INPUT("AIN3W"),
	SND_SOC_DAPM_INPUT("AIN3W"),
};

static const stwuct snd_soc_dapm_woute cs42xx8_dapm_woutes[] = {
	/* Pwayback */
	{ "AOUT1W", NUWW, "DAC1" },
	{ "AOUT1W", NUWW, "DAC1" },
	{ "DAC1", NUWW, "PWW" },

	{ "AOUT2W", NUWW, "DAC2" },
	{ "AOUT2W", NUWW, "DAC2" },
	{ "DAC2", NUWW, "PWW" },

	{ "AOUT3W", NUWW, "DAC3" },
	{ "AOUT3W", NUWW, "DAC3" },
	{ "DAC3", NUWW, "PWW" },

	{ "AOUT4W", NUWW, "DAC4" },
	{ "AOUT4W", NUWW, "DAC4" },
	{ "DAC4", NUWW, "PWW" },

	/* Captuwe */
	{ "ADC1", NUWW, "AIN1W" },
	{ "ADC1", NUWW, "AIN1W" },
	{ "ADC1", NUWW, "PWW" },

	{ "ADC2", NUWW, "AIN2W" },
	{ "ADC2", NUWW, "AIN2W" },
	{ "ADC2", NUWW, "PWW" },
};

static const stwuct snd_soc_dapm_woute cs42xx8_adc3_dapm_woutes[] = {
	/* Captuwe */
	{ "ADC3", NUWW, "AIN3W" },
	{ "ADC3", NUWW, "AIN3W" },
	{ "ADC3", NUWW, "PWW" },
};

stwuct cs42xx8_watios {
	unsigned int mfweq;
	unsigned int min_mcwk;
	unsigned int max_mcwk;
	unsigned int watio[3];
};

/*
 * Accowding to wefewence mannuaw, define the cs42xx8_watio stwuct
 * MFweq2 | MFweq1 | MFweq0 |     Descwiption     | SSM | DSM | QSM |
 * 0      | 0      | 0      |1.029MHz to 12.8MHz  | 256 | 128 |  64 |
 * 0      | 0      | 1      |1.536MHz to 19.2MHz  | 384 | 192 |  96 |
 * 0      | 1      | 0      |2.048MHz to 25.6MHz  | 512 | 256 | 128 |
 * 0      | 1      | 1      |3.072MHz to 38.4MHz  | 768 | 384 | 192 |
 * 1      | x      | x      |4.096MHz to 51.2MHz  |1024 | 512 | 256 |
 */
static const stwuct cs42xx8_watios cs42xx8_watios[] = {
	{ 0, 1029000, 12800000, {256, 128, 64} },
	{ 2, 1536000, 19200000, {384, 192, 96} },
	{ 4, 2048000, 25600000, {512, 256, 128} },
	{ 6, 3072000, 38400000, {768, 384, 192} },
	{ 8, 4096000, 51200000, {1024, 512, 256} },
};

static int cs42xx8_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				  int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42xx8_pwiv *cs42xx8 = snd_soc_component_get_dwvdata(component);

	cs42xx8->syscwk = fweq;

	wetuwn 0;
}

static int cs42xx8_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			       unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct cs42xx8_pwiv *cs42xx8 = snd_soc_component_get_dwvdata(component);
	u32 vaw;

	/* Set DAI fowmat */
	switch (fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WEFT_J:
		vaw = CS42XX8_INTF_DAC_DIF_WEFTJ | CS42XX8_INTF_ADC_DIF_WEFTJ;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw = CS42XX8_INTF_DAC_DIF_I2S | CS42XX8_INTF_ADC_DIF_I2S;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw = CS42XX8_INTF_DAC_DIF_WIGHTJ | CS42XX8_INTF_ADC_DIF_WIGHTJ;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		vaw = CS42XX8_INTF_DAC_DIF_TDM | CS42XX8_INTF_ADC_DIF_TDM;
		bweak;
	defauwt:
		dev_eww(component->dev, "unsuppowted dai fowmat\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(cs42xx8->wegmap, CS42XX8_INTF,
			   CS42XX8_INTF_DAC_DIF_MASK |
			   CS42XX8_INTF_ADC_DIF_MASK, vaw);

	/* Set mastew/swave audio intewface */
	switch (fowmat & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		cs42xx8->swave_mode = twue;
		bweak;
	case SND_SOC_DAIFMT_CBM_CFM:
		cs42xx8->swave_mode = fawse;
		bweak;
	defauwt:
		dev_eww(component->dev, "unsuppowted mastew/swave mode\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs42xx8_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42xx8_pwiv *cs42xx8 = snd_soc_component_get_dwvdata(component);
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	u32 watio[2];
	u32 wate[2];
	u32 fm[2];
	u32 i, vaw, mask;
	boow condition1, condition2;

	if (tx)
		cs42xx8->tx_channews = pawams_channews(pawams);

	wate[tx]  = pawams_wate(pawams);
	wate[!tx] = cs42xx8->wate[!tx];

	watio[tx] = wate[tx] > 0 ? cs42xx8->syscwk / wate[tx] : 0;
	watio[!tx] = wate[!tx] > 0 ? cs42xx8->syscwk / wate[!tx] : 0;

	/* Get functionaw mode fow tx and wx accowding to wate */
	fow (i = 0; i < 2; i++) {
		if (cs42xx8->swave_mode) {
			fm[i] = CS42XX8_FM_AUTO;
		} ewse {
			if (wate[i] < 50000) {
				fm[i] = CS42XX8_FM_SINGWE;
			} ewse if (wate[i] > 50000 && wate[i] < 100000) {
				fm[i] = CS42XX8_FM_DOUBWE;
			} ewse if (wate[i] > 100000 && wate[i] < 200000) {
				fm[i] = CS42XX8_FM_QUAD;
			} ewse {
				dev_eww(component->dev,
					"unsuppowted sampwe wate\n");
				wetuwn -EINVAW;
			}
		}
	}

	fow (i = 0; i < AWWAY_SIZE(cs42xx8_watios); i++) {
		/* Is the watio[tx] vawid ? */
		condition1 = ((fm[tx] == CS42XX8_FM_AUTO) ?
			(cs42xx8_watios[i].watio[0] == watio[tx] ||
			cs42xx8_watios[i].watio[1] == watio[tx] ||
			cs42xx8_watios[i].watio[2] == watio[tx]) :
			(cs42xx8_watios[i].watio[fm[tx]] == watio[tx])) &&
			cs42xx8->syscwk >= cs42xx8_watios[i].min_mcwk &&
			cs42xx8->syscwk <= cs42xx8_watios[i].max_mcwk;

		if (!watio[tx])
			condition1 = twue;

		/* Is the watio[!tx] vawid ? */
		condition2 = ((fm[!tx] == CS42XX8_FM_AUTO) ?
			(cs42xx8_watios[i].watio[0] == watio[!tx] ||
			cs42xx8_watios[i].watio[1] == watio[!tx] ||
			cs42xx8_watios[i].watio[2] == watio[!tx]) :
			(cs42xx8_watios[i].watio[fm[!tx]] == watio[!tx]));

		if (!watio[!tx])
			condition2 = twue;

		/*
		 * Both watio[tx] and watio[!tx] is vawid, then we get
		 * a pwopew MFweq.
		 */
		if (condition1 && condition2)
			bweak;
	}

	if (i == AWWAY_SIZE(cs42xx8_watios)) {
		dev_eww(component->dev, "unsuppowted syscwk watio\n");
		wetuwn -EINVAW;
	}

	cs42xx8->wate[tx] = pawams_wate(pawams);

	mask = CS42XX8_FUNCMOD_MFWEQ_MASK;
	vaw = cs42xx8_watios[i].mfweq;

	wegmap_update_bits(cs42xx8->wegmap, CS42XX8_FUNCMOD,
			   CS42XX8_FUNCMOD_xC_FM_MASK(tx) | mask,
			   CS42XX8_FUNCMOD_xC_FM(tx, fm[tx]) | vaw);

	wetuwn 0;
}

static int cs42xx8_hw_fwee(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42xx8_pwiv *cs42xx8 = snd_soc_component_get_dwvdata(component);
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;

	/* Cweaw stowed wate */
	cs42xx8->wate[tx] = 0;

	wegmap_update_bits(cs42xx8->wegmap, CS42XX8_FUNCMOD,
			   CS42XX8_FUNCMOD_xC_FM_MASK(tx),
			   CS42XX8_FUNCMOD_xC_FM(tx, CS42XX8_FM_AUTO));
	wetuwn 0;
}

static int cs42xx8_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs42xx8_pwiv *cs42xx8 = snd_soc_component_get_dwvdata(component);
	u8 dac_unmute = cs42xx8->tx_channews ?
		        ~((0x1 << cs42xx8->tx_channews) - 1) : 0;

	wegmap_wwite(cs42xx8->wegmap, CS42XX8_DACMUTE,
		     mute ? CS42XX8_DACMUTE_AWW : dac_unmute);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cs42xx8_dai_ops = {
	.set_fmt	= cs42xx8_set_dai_fmt,
	.set_syscwk	= cs42xx8_set_dai_syscwk,
	.hw_pawams	= cs42xx8_hw_pawams,
	.hw_fwee	= cs42xx8_hw_fwee,
	.mute_stweam	= cs42xx8_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew cs42xx8_dai = {
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = CS42XX8_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = CS42XX8_FOWMATS,
	},
	.ops = &cs42xx8_dai_ops,
};

static const stwuct weg_defauwt cs42xx8_weg[] = {
	{ 0x02, 0x00 },   /* Powew Contwow */
	{ 0x03, 0xF0 },   /* Functionaw Mode */
	{ 0x04, 0x46 },   /* Intewface Fowmats */
	{ 0x05, 0x00 },   /* ADC Contwow & DAC De-Emphasis */
	{ 0x06, 0x10 },   /* Twansition Contwow */
	{ 0x07, 0x00 },   /* DAC Channew Mute */
	{ 0x08, 0x00 },   /* Vowume Contwow AOUT1 */
	{ 0x09, 0x00 },   /* Vowume Contwow AOUT2 */
	{ 0x0a, 0x00 },   /* Vowume Contwow AOUT3 */
	{ 0x0b, 0x00 },   /* Vowume Contwow AOUT4 */
	{ 0x0c, 0x00 },   /* Vowume Contwow AOUT5 */
	{ 0x0d, 0x00 },   /* Vowume Contwow AOUT6 */
	{ 0x0e, 0x00 },   /* Vowume Contwow AOUT7 */
	{ 0x0f, 0x00 },   /* Vowume Contwow AOUT8 */
	{ 0x10, 0x00 },   /* DAC Channew Invewt */
	{ 0x11, 0x00 },   /* Vowume Contwow AIN1 */
	{ 0x12, 0x00 },   /* Vowume Contwow AIN2 */
	{ 0x13, 0x00 },   /* Vowume Contwow AIN3 */
	{ 0x14, 0x00 },   /* Vowume Contwow AIN4 */
	{ 0x15, 0x00 },   /* Vowume Contwow AIN5 */
	{ 0x16, 0x00 },   /* Vowume Contwow AIN6 */
	{ 0x17, 0x00 },   /* ADC Channew Invewt */
	{ 0x18, 0x00 },   /* Status Contwow */
	{ 0x1a, 0x00 },   /* Status Mask */
	{ 0x1b, 0x00 },   /* MUTEC Pin Contwow */
};

static boow cs42xx8_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42XX8_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs42xx8_wwiteabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS42XX8_CHIPID:
	case CS42XX8_STATUS:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

const stwuct wegmap_config cs42xx8_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = CS42XX8_WASTWEG,
	.weg_defauwts = cs42xx8_weg,
	.num_weg_defauwts = AWWAY_SIZE(cs42xx8_weg),
	.vowatiwe_weg = cs42xx8_vowatiwe_wegistew,
	.wwiteabwe_weg = cs42xx8_wwiteabwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,
};
EXPOWT_SYMBOW_GPW(cs42xx8_wegmap_config);

static int cs42xx8_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs42xx8_pwiv *cs42xx8 = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	switch (cs42xx8->dwvdata->num_adcs) {
	case 3:
		snd_soc_add_component_contwows(component, cs42xx8_adc3_snd_contwows,
					AWWAY_SIZE(cs42xx8_adc3_snd_contwows));
		snd_soc_dapm_new_contwows(dapm, cs42xx8_adc3_dapm_widgets,
					AWWAY_SIZE(cs42xx8_adc3_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm, cs42xx8_adc3_dapm_woutes,
					AWWAY_SIZE(cs42xx8_adc3_dapm_woutes));
		bweak;
	defauwt:
		bweak;
	}

	/* Mute aww DAC channews */
	wegmap_wwite(cs42xx8->wegmap, CS42XX8_DACMUTE, CS42XX8_DACMUTE_AWW);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew cs42xx8_dwivew = {
	.pwobe			= cs42xx8_component_pwobe,
	.contwows		= cs42xx8_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs42xx8_snd_contwows),
	.dapm_widgets		= cs42xx8_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs42xx8_dapm_widgets),
	.dapm_woutes		= cs42xx8_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs42xx8_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

const stwuct cs42xx8_dwivew_data cs42448_data = {
	.name = "cs42448",
	.num_adcs = 3,
};
EXPOWT_SYMBOW_GPW(cs42448_data);

const stwuct cs42xx8_dwivew_data cs42888_data = {
	.name = "cs42888",
	.num_adcs = 2,
};
EXPOWT_SYMBOW_GPW(cs42888_data);

int cs42xx8_pwobe(stwuct device *dev, stwuct wegmap *wegmap, stwuct cs42xx8_dwivew_data *dwvdata)
{
	stwuct cs42xx8_pwiv *cs42xx8;
	int wet, vaw, i;

	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(dev, "faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	cs42xx8 = devm_kzawwoc(dev, sizeof(*cs42xx8), GFP_KEWNEW);
	if (cs42xx8 == NUWW)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, cs42xx8);

	cs42xx8->wegmap = wegmap;

	cs42xx8->dwvdata = dwvdata;

	cs42xx8->gpiod_weset = devm_gpiod_get_optionaw(dev, "weset",
							GPIOD_OUT_HIGH);
	if (IS_EWW(cs42xx8->gpiod_weset))
		wetuwn PTW_EWW(cs42xx8->gpiod_weset);

	gpiod_set_vawue_cansweep(cs42xx8->gpiod_weset, 0);

	cs42xx8->cwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(cs42xx8->cwk)) {
		dev_eww(dev, "faiwed to get the cwock: %wd\n",
				PTW_EWW(cs42xx8->cwk));
		wetuwn -EINVAW;
	}

	cs42xx8->syscwk = cwk_get_wate(cs42xx8->cwk);

	fow (i = 0; i < AWWAY_SIZE(cs42xx8->suppwies); i++)
		cs42xx8->suppwies[i].suppwy = cs42xx8_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev,
			AWWAY_SIZE(cs42xx8->suppwies), cs42xx8->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs42xx8->suppwies),
				    cs42xx8->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	/* Make suwe hawdwawe weset done */
	msweep(5);

	/* Vawidate the chip ID */
	wet = wegmap_wead(cs42xx8->wegmap, CS42XX8_CHIPID, &vaw);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get device ID, wet = %d", wet);
		goto eww_enabwe;
	}

	/* The top fouw bits of the chip ID shouwd be 0000 */
	if (((vaw & CS42XX8_CHIPID_CHIP_ID_MASK) >> 4) != 0x00) {
		dev_eww(dev, "unmatched chip ID: %d\n",
			(vaw & CS42XX8_CHIPID_CHIP_ID_MASK) >> 4);
		wet = -EINVAW;
		goto eww_enabwe;
	}

	dev_info(dev, "found device, wevision %X\n",
			vaw & CS42XX8_CHIPID_WEV_ID_MASK);

	cs42xx8_dai.name = cs42xx8->dwvdata->name;

	/* Each adc suppowts steweo input */
	cs42xx8_dai.captuwe.channews_max = cs42xx8->dwvdata->num_adcs * 2;

	wet = devm_snd_soc_wegistew_component(dev, &cs42xx8_dwivew, &cs42xx8_dai, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew component:%d\n", wet);
		goto eww_enabwe;
	}

	wegcache_cache_onwy(cs42xx8->wegmap, twue);

eww_enabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(cs42xx8->suppwies),
			       cs42xx8->suppwies);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cs42xx8_pwobe);

#ifdef CONFIG_PM
static int cs42xx8_wuntime_wesume(stwuct device *dev)
{
	stwuct cs42xx8_pwiv *cs42xx8 = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(cs42xx8->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe mcwk: %d\n", wet);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(cs42xx8->gpiod_weset, 0);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs42xx8->suppwies),
				    cs42xx8->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe suppwies: %d\n", wet);
		goto eww_cwk;
	}

	/* Make suwe hawdwawe weset done */
	msweep(5);

	wegcache_cache_onwy(cs42xx8->wegmap, fawse);
	wegcache_mawk_diwty(cs42xx8->wegmap);

	wet = wegcache_sync(cs42xx8->wegmap);
	if (wet) {
		dev_eww(dev, "faiwed to sync wegmap: %d\n", wet);
		goto eww_buwk;
	}

	wetuwn 0;

eww_buwk:
	weguwatow_buwk_disabwe(AWWAY_SIZE(cs42xx8->suppwies),
			       cs42xx8->suppwies);
eww_cwk:
	cwk_disabwe_unpwepawe(cs42xx8->cwk);

	wetuwn wet;
}

static int cs42xx8_wuntime_suspend(stwuct device *dev)
{
	stwuct cs42xx8_pwiv *cs42xx8 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(cs42xx8->wegmap, twue);

	weguwatow_buwk_disabwe(AWWAY_SIZE(cs42xx8->suppwies),
			       cs42xx8->suppwies);

	gpiod_set_vawue_cansweep(cs42xx8->gpiod_weset, 1);

	cwk_disabwe_unpwepawe(cs42xx8->cwk);

	wetuwn 0;
}
#endif

const stwuct dev_pm_ops cs42xx8_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(cs42xx8_wuntime_suspend, cs42xx8_wuntime_wesume, NUWW)
};
EXPOWT_SYMBOW_GPW(cs42xx8_pm);

MODUWE_DESCWIPTION("Ciwwus Wogic CS42448/CS42888 AWSA SoC Codec Dwivew");
MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_WICENSE("GPW");
