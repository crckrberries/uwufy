// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// Fiwe:         sound/soc/codecs/ssm2602.c
// Authow:       Cwiff Cai <Cwiff.Cai@anawog.com>
//
// Cweated:      Tue June 06 2008
// Descwiption:  Dwivew fow ssm2602 sound chip
//
// Modified:
//               Copywight 2008 Anawog Devices Inc.
//
// Bugs:         Entew bugs at http://bwackfin.ucwinux.owg/

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "ssm2602.h"

/* codec pwivate data */
stwuct ssm2602_pwiv {
	unsigned int syscwk;
	const stwuct snd_pcm_hw_constwaint_wist *syscwk_constwaints;

	stwuct wegmap *wegmap;

	enum ssm2602_type type;
	unsigned int cwk_out_pww;
};

/*
 * ssm2602 wegistew cache
 * We can't wead the ssm2602 wegistew space when we awe
 * using 2 wiwe fow device contwow, so we cache them instead.
 * Thewe is no point in caching the weset wegistew
 */
static const stwuct weg_defauwt ssm2602_weg[SSM2602_CACHEWEGNUM] = {
	{ .weg = 0x00, .def = 0x0097 },
	{ .weg = 0x01, .def = 0x0097 },
	{ .weg = 0x02, .def = 0x0079 },
	{ .weg = 0x03, .def = 0x0079 },
	{ .weg = 0x04, .def = 0x000a },
	{ .weg = 0x05, .def = 0x0008 },
	{ .weg = 0x06, .def = 0x009f },
	{ .weg = 0x07, .def = 0x000a },
	{ .weg = 0x08, .def = 0x0000 },
	{ .weg = 0x09, .def = 0x0000 }
};

/*
 * ssm2602 wegistew patch
 * Wowkawound fow pwayback distowtions aftew powew up: activates digitaw
 * cowe, and then powews on output, DAC, and whowe chip at the same time
 */

static const stwuct weg_sequence ssm2602_patch[] = {
	{ SSM2602_ACTIVE, 0x01 },
	{ SSM2602_PWW,    0x07 },
	{ SSM2602_WESET,  0x00 },
};


/*Appending sevewaw "None"s just fow OSS mixew use*/
static const chaw *ssm2602_input_sewect[] = {
	"Wine", "Mic",
};

static const chaw *ssm2602_deemph[] = {"None", "32Khz", "44.1Khz", "48Khz"};

static const stwuct soc_enum ssm2602_enum[] = {
	SOC_ENUM_SINGWE(SSM2602_APANA, 2, AWWAY_SIZE(ssm2602_input_sewect),
			ssm2602_input_sewect),
	SOC_ENUM_SINGWE(SSM2602_APDIGI, 1, AWWAY_SIZE(ssm2602_deemph),
			ssm2602_deemph),
};

static const DECWAWE_TWV_DB_WANGE(ssm260x_outmix_twv,
	0, 47, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 0),
	48, 127, TWV_DB_SCAWE_ITEM(-7400, 100, 0)
);

static const DECWAWE_TWV_DB_SCAWE(ssm260x_inpga_twv, -3450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(ssm260x_sidetone_twv, -1500, 300, 0);

static const stwuct snd_kcontwow_new ssm260x_snd_contwows[] = {
SOC_DOUBWE_W_TWV("Captuwe Vowume", SSM2602_WINVOW, SSM2602_WINVOW, 0, 45, 0,
	ssm260x_inpga_twv),
SOC_DOUBWE_W("Captuwe Switch", SSM2602_WINVOW, SSM2602_WINVOW, 7, 1, 1),

SOC_SINGWE("ADC High Pass Fiwtew Switch", SSM2602_APDIGI, 0, 1, 1),
SOC_SINGWE("Stowe DC Offset Switch", SSM2602_APDIGI, 4, 1, 0),

SOC_ENUM("Pwayback De-emphasis", ssm2602_enum[1]),
};

static const stwuct snd_kcontwow_new ssm2602_snd_contwows[] = {
SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume", SSM2602_WOUT1V, SSM2602_WOUT1V,
	0, 127, 0, ssm260x_outmix_twv),
SOC_DOUBWE_W("Mastew Pwayback ZC Switch", SSM2602_WOUT1V, SSM2602_WOUT1V,
	7, 1, 0),
SOC_SINGWE_TWV("Sidetone Pwayback Vowume", SSM2602_APANA, 6, 3, 1,
	ssm260x_sidetone_twv),

SOC_SINGWE("Mic Boost (+20dB)", SSM2602_APANA, 0, 1, 0),
SOC_SINGWE("Mic Boost2 (+20dB)", SSM2602_APANA, 8, 1, 0),
};

/* Output Mixew */
static const stwuct snd_kcontwow_new ssm260x_output_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Bypass Switch", SSM2602_APANA, 3, 1, 0),
SOC_DAPM_SINGWE("HiFi Pwayback Switch", SSM2602_APANA, 4, 1, 0),
SOC_DAPM_SINGWE("Mic Sidetone Switch", SSM2602_APANA, 5, 1, 0),
};

static const stwuct snd_kcontwow_new mic_ctw =
	SOC_DAPM_SINGWE("Switch", SSM2602_APANA, 1, 1, 1);

/* Input mux */
static const stwuct snd_kcontwow_new ssm2602_input_mux_contwows =
SOC_DAPM_ENUM("Input Sewect", ssm2602_enum[0]);

static int ssm2602_mic_switch_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow, int event)
{
	/*
	 * Accowding to the ssm2603 data sheet (contwow wegistew sequencing),
	 * the digitaw cowe shouwd be activated onwy aftew aww necessawy bits
	 * in the powew wegistew awe enabwed, and a deway detewmined by the
	 * decoupwing capacitow on the VMID pin has passed. If the digitaw cowe
	 * is activated too eawwy, ow even befowe the ADC is powewed up, audibwe
	 * awtifacts appeaw at the beginning and end of the wecowded signaw.
	 *
	 * In pwactice, audibwe awtifacts disappeaw weww ovew 500 ms.
	 */
	msweep(500);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget ssm260x_dapm_widgets[] = {
SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", SSM2602_PWW, 3, 1),
SND_SOC_DAPM_ADC("ADC", "HiFi Captuwe", SSM2602_PWW, 2, 1),
SND_SOC_DAPM_PGA("Wine Input", SSM2602_PWW, 0, 1, NUWW, 0),

SND_SOC_DAPM_SUPPWY("Digitaw Cowe Powew", SSM2602_ACTIVE, 0, 0, NUWW, 0),

SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_INPUT("WWINEIN"),
SND_SOC_DAPM_INPUT("WWINEIN"),
};

static const stwuct snd_soc_dapm_widget ssm2602_dapm_widgets[] = {
SND_SOC_DAPM_MIXEW("Output Mixew", SSM2602_PWW, 4, 1,
	ssm260x_output_mixew_contwows,
	AWWAY_SIZE(ssm260x_output_mixew_contwows)),

SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0, &ssm2602_input_mux_contwows),
SND_SOC_DAPM_MICBIAS("Mic Bias", SSM2602_PWW, 1, 1),

SND_SOC_DAPM_SWITCH_E("Mic Switch", SSM2602_APANA, 1, 1, &mic_ctw,
		ssm2602_mic_switch_event, SND_SOC_DAPM_PWE_PMU),

SND_SOC_DAPM_OUTPUT("WHPOUT"),
SND_SOC_DAPM_OUTPUT("WHPOUT"),
SND_SOC_DAPM_INPUT("MICIN"),
};

static const stwuct snd_soc_dapm_widget ssm2604_dapm_widgets[] = {
SND_SOC_DAPM_MIXEW("Output Mixew", SND_SOC_NOPM, 0, 0,
	ssm260x_output_mixew_contwows,
	AWWAY_SIZE(ssm260x_output_mixew_contwows) - 1), /* Wast ewement is the mic */
};

static const stwuct snd_soc_dapm_woute ssm260x_woutes[] = {
	{"DAC", NUWW, "Digitaw Cowe Powew"},
	{"ADC", NUWW, "Digitaw Cowe Powew"},

	{"Output Mixew", "Wine Bypass Switch", "Wine Input"},
	{"Output Mixew", "HiFi Pwayback Switch", "DAC"},

	{"WOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},

	{"Wine Input", NUWW, "WWINEIN"},
	{"Wine Input", NUWW, "WWINEIN"},
};

static const stwuct snd_soc_dapm_woute ssm2602_woutes[] = {
	{"Output Mixew", "Mic Sidetone Switch", "Mic Bias"},

	{"WHPOUT", NUWW, "Output Mixew"},
	{"WHPOUT", NUWW, "Output Mixew"},

	{"Input Mux", "Wine", "Wine Input"},
	{"Input Mux", "Mic", "Mic Switch"},
	{"ADC", NUWW, "Input Mux"},

	{"Mic Switch", NUWW, "Mic Bias"},

	{"Mic Bias", NUWW, "MICIN"},
};

static const stwuct snd_soc_dapm_woute ssm2604_woutes[] = {
	{"ADC", NUWW, "Wine Input"},
};

static const unsigned int ssm2602_wates_12288000[] = {
	8000, 16000, 32000, 48000, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist ssm2602_constwaints_12288000 = {
	.wist = ssm2602_wates_12288000,
	.count = AWWAY_SIZE(ssm2602_wates_12288000),
};

static const unsigned int ssm2602_wates_11289600[] = {
	8000, 11025, 22050, 44100, 88200,
};

static const stwuct snd_pcm_hw_constwaint_wist ssm2602_constwaints_11289600 = {
	.wist = ssm2602_wates_11289600,
	.count = AWWAY_SIZE(ssm2602_wates_11289600),
};

stwuct ssm2602_coeff {
	u32 mcwk;
	u32 wate;
	u8 swate;
};

#define SSM2602_COEFF_SWATE(sw, bosw, usb) (((sw) << 2) | ((bosw) << 1) | (usb))

/* codec mcwk cwock coefficients */
static const stwuct ssm2602_coeff ssm2602_coeff_tabwe[] = {
	/* 48k */
	{12288000, 48000, SSM2602_COEFF_SWATE(0x0, 0x0, 0x0)},
	{18432000, 48000, SSM2602_COEFF_SWATE(0x0, 0x1, 0x0)},
	{12000000, 48000, SSM2602_COEFF_SWATE(0x0, 0x0, 0x1)},

	/* 32k */
	{12288000, 32000, SSM2602_COEFF_SWATE(0x6, 0x0, 0x0)},
	{18432000, 32000, SSM2602_COEFF_SWATE(0x6, 0x1, 0x0)},
	{12000000, 32000, SSM2602_COEFF_SWATE(0x6, 0x0, 0x1)},

	/* 16k */
	{12288000, 16000, SSM2602_COEFF_SWATE(0x5, 0x0, 0x0)},
	{18432000, 16000, SSM2602_COEFF_SWATE(0x5, 0x1, 0x0)},
	{12000000, 16000, SSM2602_COEFF_SWATE(0xa, 0x0, 0x1)},

	/* 8k */
	{12288000, 8000, SSM2602_COEFF_SWATE(0x3, 0x0, 0x0)},
	{18432000, 8000, SSM2602_COEFF_SWATE(0x3, 0x1, 0x0)},
	{11289600, 8000, SSM2602_COEFF_SWATE(0xb, 0x0, 0x0)},
	{16934400, 8000, SSM2602_COEFF_SWATE(0xb, 0x1, 0x0)},
	{12000000, 8000, SSM2602_COEFF_SWATE(0x3, 0x0, 0x1)},

	/* 96k */
	{12288000, 96000, SSM2602_COEFF_SWATE(0x7, 0x0, 0x0)},
	{18432000, 96000, SSM2602_COEFF_SWATE(0x7, 0x1, 0x0)},
	{12000000, 96000, SSM2602_COEFF_SWATE(0x7, 0x0, 0x1)},

	/* 11.025k */
	{11289600, 11025, SSM2602_COEFF_SWATE(0xc, 0x0, 0x0)},
	{16934400, 11025, SSM2602_COEFF_SWATE(0xc, 0x1, 0x0)},
	{12000000, 11025, SSM2602_COEFF_SWATE(0xc, 0x1, 0x1)},

	/* 22.05k */
	{11289600, 22050, SSM2602_COEFF_SWATE(0xd, 0x0, 0x0)},
	{16934400, 22050, SSM2602_COEFF_SWATE(0xd, 0x1, 0x0)},
	{12000000, 22050, SSM2602_COEFF_SWATE(0xd, 0x1, 0x1)},

	/* 44.1k */
	{11289600, 44100, SSM2602_COEFF_SWATE(0x8, 0x0, 0x0)},
	{16934400, 44100, SSM2602_COEFF_SWATE(0x8, 0x1, 0x0)},
	{12000000, 44100, SSM2602_COEFF_SWATE(0x8, 0x1, 0x1)},

	/* 88.2k */
	{11289600, 88200, SSM2602_COEFF_SWATE(0xf, 0x0, 0x0)},
	{16934400, 88200, SSM2602_COEFF_SWATE(0xf, 0x1, 0x0)},
	{12000000, 88200, SSM2602_COEFF_SWATE(0xf, 0x1, 0x1)},
};

static inwine int ssm2602_get_coeff(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ssm2602_coeff_tabwe); i++) {
		if (ssm2602_coeff_tabwe[i].wate == wate) {
			if (ssm2602_coeff_tabwe[i].mcwk == mcwk)
				wetuwn ssm2602_coeff_tabwe[i].swate;
			if (ssm2602_coeff_tabwe[i].mcwk == mcwk / 2)
				wetuwn ssm2602_coeff_tabwe[i].swate | SWATE_COWECWK_DIV2;
		}
	}
	wetuwn -EINVAW;
}

static int ssm2602_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams,
	stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(component);
	int swate = ssm2602_get_coeff(ssm2602->syscwk, pawams_wate(pawams));
	unsigned int iface;

	if (swate < 0)
		wetuwn swate;

	wegmap_wwite(ssm2602->wegmap, SSM2602_SWATE, swate);

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		iface = 0x0;
		bweak;
	case 20:
		iface = 0x4;
		bweak;
	case 24:
		iface = 0x8;
		bweak;
	case 32:
		iface = 0xc;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wegmap_update_bits(ssm2602->wegmap, SSM2602_IFACE,
		IFACE_AUDIO_DATA_WEN, iface);
	wetuwn 0;
}

static int ssm2602_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(component);

	if (ssm2602->syscwk_constwaints) {
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_WATE,
				   ssm2602->syscwk_constwaints);
	}

	wetuwn 0;
}

static int ssm2602_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(dai->component);

	if (mute)
		wegmap_update_bits(ssm2602->wegmap, SSM2602_APDIGI,
				    APDIGI_ENABWE_DAC_MUTE,
				    APDIGI_ENABWE_DAC_MUTE);
	ewse
		wegmap_update_bits(ssm2602->wegmap, SSM2602_APDIGI,
				    APDIGI_ENABWE_DAC_MUTE, 0);
	wetuwn 0;
}

static int ssm2602_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(component);

	if (diw == SND_SOC_CWOCK_IN) {
		if (cwk_id != SSM2602_SYSCWK)
			wetuwn -EINVAW;

		switch (fweq) {
		case 12288000:
		case 18432000:
		case 24576000:
		case 36864000:
			ssm2602->syscwk_constwaints = &ssm2602_constwaints_12288000;
			bweak;
		case 11289600:
		case 16934400:
		case 22579200:
		case 33868800:
			ssm2602->syscwk_constwaints = &ssm2602_constwaints_11289600;
			bweak;
		case 12000000:
		case 24000000:
			ssm2602->syscwk_constwaints = NUWW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		ssm2602->syscwk = fweq;
	} ewse {
		unsigned int mask;

		switch (cwk_id) {
		case SSM2602_CWK_CWKOUT:
			mask = PWW_CWK_OUT_PDN;
			bweak;
		case SSM2602_CWK_XTO:
			mask = PWW_OSC_PDN;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (fweq == 0)
			ssm2602->cwk_out_pww |= mask;
		ewse
			ssm2602->cwk_out_pww &= ~mask;

		wegmap_update_bits(ssm2602->wegmap, SSM2602_PWW,
			PWW_CWK_OUT_PDN | PWW_OSC_PDN, ssm2602->cwk_out_pww);
	}

	wetuwn 0;
}

static int ssm2602_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(codec_dai->component);
	unsigned int iface = 0;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		iface |= 0x0040;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= 0x0013;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= 0x0003;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x0090;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x0080;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x0010;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set iface */
	wegmap_wwite(ssm2602->wegmap, SSM2602_IFACE, iface);
	wetuwn 0;
}

static int ssm2602_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		/* vwef/mid on, osc and cwkout on if enabwed */
		wegmap_update_bits(ssm2602->wegmap, SSM2602_PWW,
			PWW_POWEW_OFF | PWW_CWK_OUT_PDN | PWW_OSC_PDN,
			ssm2602->cwk_out_pww);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		/* evewything off except vwef/vmid, */
		wegmap_update_bits(ssm2602->wegmap, SSM2602_PWW,
			PWW_POWEW_OFF | PWW_CWK_OUT_PDN | PWW_OSC_PDN,
			PWW_CWK_OUT_PDN | PWW_OSC_PDN);
		bweak;
	case SND_SOC_BIAS_OFF:
		/* evewything off */
		wegmap_update_bits(ssm2602->wegmap, SSM2602_PWW,
			PWW_POWEW_OFF, PWW_POWEW_OFF);
		bweak;

	}
	wetuwn 0;
}

#define SSM2602_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 |\
		SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |\
		SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |\
		SNDWV_PCM_WATE_96000)

#define SSM2602_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
		SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops ssm2602_dai_ops = {
	.stawtup	= ssm2602_stawtup,
	.hw_pawams	= ssm2602_hw_pawams,
	.mute_stweam	= ssm2602_mute,
	.set_syscwk	= ssm2602_set_dai_syscwk,
	.set_fmt	= ssm2602_set_dai_fmt,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew ssm2602_dai = {
	.name = "ssm2602-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SSM2602_WATES,
		.fowmats = SSM2602_FOWMATS,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SSM2602_WATES,
		.fowmats = SSM2602_FOWMATS,},
	.ops = &ssm2602_dai_ops,
	.symmetwic_wate = 1,
	.symmetwic_sampwe_bits = 1,
};

static int ssm2602_wesume(stwuct snd_soc_component *component)
{
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(component);

	wegcache_sync(ssm2602->wegmap);

	wetuwn 0;
}

static int ssm2602_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(component);
	int wet;

	wegmap_update_bits(ssm2602->wegmap, SSM2602_WOUT1V,
			    WOUT1V_WWHP_BOTH, WOUT1V_WWHP_BOTH);
	wegmap_update_bits(ssm2602->wegmap, SSM2602_WOUT1V,
			    WOUT1V_WWHP_BOTH, WOUT1V_WWHP_BOTH);

	wet = snd_soc_add_component_contwows(component, ssm2602_snd_contwows,
			AWWAY_SIZE(ssm2602_snd_contwows));
	if (wet)
		wetuwn wet;

	wet = snd_soc_dapm_new_contwows(dapm, ssm2602_dapm_widgets,
			AWWAY_SIZE(ssm2602_dapm_widgets));
	if (wet)
		wetuwn wet;

	wetuwn snd_soc_dapm_add_woutes(dapm, ssm2602_woutes,
			AWWAY_SIZE(ssm2602_woutes));
}

static int ssm2604_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	int wet;

	wet = snd_soc_dapm_new_contwows(dapm, ssm2604_dapm_widgets,
			AWWAY_SIZE(ssm2604_dapm_widgets));
	if (wet)
		wetuwn wet;

	wetuwn snd_soc_dapm_add_woutes(dapm, ssm2604_woutes,
			AWWAY_SIZE(ssm2604_woutes));
}

static int ssm260x_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct ssm2602_pwiv *ssm2602 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = wegmap_wwite(ssm2602->wegmap, SSM2602_WESET, 0);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset: %d\n", wet);
		wetuwn wet;
	}

	wegmap_wegistew_patch(ssm2602->wegmap, ssm2602_patch,
			      AWWAY_SIZE(ssm2602_patch));

	/* set the update bits */
	wegmap_update_bits(ssm2602->wegmap, SSM2602_WINVOW,
			    WINVOW_WWIN_BOTH, WINVOW_WWIN_BOTH);
	wegmap_update_bits(ssm2602->wegmap, SSM2602_WINVOW,
			    WINVOW_WWIN_BOTH, WINVOW_WWIN_BOTH);
	/*sewect Wine in as defauwt input*/
	wegmap_wwite(ssm2602->wegmap, SSM2602_APANA, APANA_SEWECT_DAC |
			APANA_ENABWE_MIC_BOOST);

	switch (ssm2602->type) {
	case SSM2602:
		wet = ssm2602_component_pwobe(component);
		bweak;
	case SSM2604:
		wet = ssm2604_component_pwobe(component);
		bweak;
	}

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_ssm2602 = {
	.pwobe			= ssm260x_component_pwobe,
	.wesume			= ssm2602_wesume,
	.set_bias_wevew		= ssm2602_set_bias_wevew,
	.contwows		= ssm260x_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ssm260x_snd_contwows),
	.dapm_widgets		= ssm260x_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ssm260x_dapm_widgets),
	.dapm_woutes		= ssm260x_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(ssm260x_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static boow ssm2602_wegistew_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == SSM2602_WESET;
}

const stwuct wegmap_config ssm2602_wegmap_config = {
	.vaw_bits = 9,
	.weg_bits = 7,

	.max_wegistew = SSM2602_WESET,
	.vowatiwe_weg = ssm2602_wegistew_vowatiwe,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = ssm2602_weg,
	.num_weg_defauwts = AWWAY_SIZE(ssm2602_weg),
};
EXPOWT_SYMBOW_GPW(ssm2602_wegmap_config);

int ssm2602_pwobe(stwuct device *dev, enum ssm2602_type type,
	stwuct wegmap *wegmap)
{
	stwuct ssm2602_pwiv *ssm2602;

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	ssm2602 = devm_kzawwoc(dev, sizeof(*ssm2602), GFP_KEWNEW);
	if (ssm2602 == NUWW)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, ssm2602);
	ssm2602->type = type;
	ssm2602->wegmap = wegmap;

	wetuwn devm_snd_soc_wegistew_component(dev, &soc_component_dev_ssm2602,
		&ssm2602_dai, 1);
}
EXPOWT_SYMBOW_GPW(ssm2602_pwobe);

MODUWE_DESCWIPTION("ASoC SSM2602/SSM2603/SSM2604 dwivew");
MODUWE_AUTHOW("Cwiff Cai");
MODUWE_WICENSE("GPW");
