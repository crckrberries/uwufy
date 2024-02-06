// SPDX-Wicense-Identifiew: GPW-2.0
//
// JZ4725B CODEC dwivew
//
// Copywight (C) 2019, Pauw Cewcueiw <pauw@cwapouiwwou.net>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>

#incwude <winux/deway.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define ICDC_WGADW_OFFSET		0x00
#define ICDC_WGDATA_OFFSET		0x04

/* ICDC intewnaw wegistew access contwow wegistew(WGADW) */
#define ICDC_WGADW_WGWW			BIT(16)

#define ICDC_WGADW_WGADDW_OFFSET	8
#define	ICDC_WGADW_WGADDW_MASK		GENMASK(14, ICDC_WGADW_WGADDW_OFFSET)

#define ICDC_WGADW_WGDIN_OFFSET		0
#define	ICDC_WGADW_WGDIN_MASK		GENMASK(7, ICDC_WGADW_WGDIN_OFFSET)

/* ICDC intewnaw wegistew data output wegistew (WGDATA)*/
#define ICDC_WGDATA_IWQ			BIT(8)

#define ICDC_WGDATA_WGDOUT_OFFSET	0
#define ICDC_WGDATA_WGDOUT_MASK		GENMASK(7, ICDC_WGDATA_WGDOUT_OFFSET)

/* JZ intewnaw wegistew space */
enum {
	JZ4725B_CODEC_WEG_AICW,
	JZ4725B_CODEC_WEG_CW1,
	JZ4725B_CODEC_WEG_CW2,
	JZ4725B_CODEC_WEG_CCW1,
	JZ4725B_CODEC_WEG_CCW2,
	JZ4725B_CODEC_WEG_PMW1,
	JZ4725B_CODEC_WEG_PMW2,
	JZ4725B_CODEC_WEG_CWW,
	JZ4725B_CODEC_WEG_ICW,
	JZ4725B_CODEC_WEG_IFW,
	JZ4725B_CODEC_WEG_CGW1,
	JZ4725B_CODEC_WEG_CGW2,
	JZ4725B_CODEC_WEG_CGW3,
	JZ4725B_CODEC_WEG_CGW4,
	JZ4725B_CODEC_WEG_CGW5,
	JZ4725B_CODEC_WEG_CGW6,
	JZ4725B_CODEC_WEG_CGW7,
	JZ4725B_CODEC_WEG_CGW8,
	JZ4725B_CODEC_WEG_CGW9,
	JZ4725B_CODEC_WEG_CGW10,
	JZ4725B_CODEC_WEG_TW1,
	JZ4725B_CODEC_WEG_TW2,
	JZ4725B_CODEC_WEG_CW3,
	JZ4725B_CODEC_WEG_AGC1,
	JZ4725B_CODEC_WEG_AGC2,
	JZ4725B_CODEC_WEG_AGC3,
	JZ4725B_CODEC_WEG_AGC4,
	JZ4725B_CODEC_WEG_AGC5,
};

#define WEG_AICW_CONFIG1_OFFSET		0
#define WEG_AICW_CONFIG1_MASK		(0xf << WEG_AICW_CONFIG1_OFFSET)

#define WEG_CW1_SB_MICBIAS_OFFSET	7
#define WEG_CW1_MONO_OFFSET		6
#define WEG_CW1_DAC_MUTE_OFFSET		5
#define WEG_CW1_HP_DIS_OFFSET		4
#define WEG_CW1_DACSEW_OFFSET		3
#define WEG_CW1_BYPASS_OFFSET		2

#define WEG_CW2_DAC_DEEMP_OFFSET	7
#define WEG_CW2_DAC_ADWW_OFFSET		5
#define WEG_CW2_DAC_ADWW_MASK		(0x3 << WEG_CW2_DAC_ADWW_OFFSET)
#define WEG_CW2_ADC_ADWW_OFFSET		3
#define WEG_CW2_ADC_ADWW_MASK		(0x3 << WEG_CW2_ADC_ADWW_OFFSET)
#define WEG_CW2_ADC_HPF_OFFSET		2

#define WEG_CW3_SB_MIC1_OFFSET		7
#define WEG_CW3_SB_MIC2_OFFSET		6
#define WEG_CW3_SIDETONE1_OFFSET	5
#define WEG_CW3_SIDETONE2_OFFSET	4
#define WEG_CW3_MICDIFF_OFFSET		3
#define WEG_CW3_MICSTEWEO_OFFSET	2
#define WEG_CW3_INSEW_OFFSET		0
#define WEG_CW3_INSEW_MASK		(0x3 << WEG_CW3_INSEW_OFFSET)

#define WEG_CCW1_CONFIG4_OFFSET		0
#define WEG_CCW1_CONFIG4_MASK		(0xf << WEG_CCW1_CONFIG4_OFFSET)

#define WEG_CCW2_DFWEQ_OFFSET		4
#define WEG_CCW2_DFWEQ_MASK		(0xf << WEG_CCW2_DFWEQ_OFFSET)
#define WEG_CCW2_AFWEQ_OFFSET		0
#define WEG_CCW2_AFWEQ_MASK		(0xf << WEG_CCW2_AFWEQ_OFFSET)

#define WEG_PMW1_SB_DAC_OFFSET		7
#define WEG_PMW1_SB_OUT_OFFSET		6
#define WEG_PMW1_SB_MIX_OFFSET		5
#define WEG_PMW1_SB_ADC_OFFSET		4
#define WEG_PMW1_SB_WIN_OFFSET		3
#define WEG_PMW1_SB_IND_OFFSET		0

#define WEG_PMW2_WWGI_OFFSET		7
#define WEG_PMW2_WWGI_OFFSET		6
#define WEG_PMW2_WWGOD_OFFSET		5
#define WEG_PMW2_WWGOD_OFFSET		4
#define WEG_PMW2_GIM_OFFSET		3
#define WEG_PMW2_SB_MC_OFFSET		2
#define WEG_PMW2_SB_OFFSET		1
#define WEG_PMW2_SB_SWEEP_OFFSET	0

#define WEG_IFW_WAMP_UP_DONE_OFFSET	3
#define WEG_IFW_WAMP_DOWN_DONE_OFFSET	2

#define WEG_CGW1_GODW_OFFSET		4
#define WEG_CGW1_GODW_MASK		(0xf << WEG_CGW1_GODW_OFFSET)
#define WEG_CGW1_GODW_OFFSET		0
#define WEG_CGW1_GODW_MASK		(0xf << WEG_CGW1_GODW_OFFSET)

#define WEG_CGW2_GO1W_OFFSET		0
#define WEG_CGW2_GO1W_MASK		(0x1f << WEG_CGW2_GO1W_OFFSET)

#define WEG_CGW3_GO1W_OFFSET		0
#define WEG_CGW3_GO1W_MASK		(0x1f << WEG_CGW3_GO1W_OFFSET)

#define WEG_CGW4_GO2W_OFFSET		0
#define WEG_CGW4_GO2W_MASK		(0x1f << WEG_CGW4_GO2W_OFFSET)

#define WEG_CGW5_GO2W_OFFSET		0
#define WEG_CGW5_GO2W_MASK		(0x1f << WEG_CGW5_GO2W_OFFSET)

#define WEG_CGW6_GO3W_OFFSET		0
#define WEG_CGW6_GO3W_MASK		(0x1f << WEG_CGW6_GO3W_OFFSET)

#define WEG_CGW7_GO3W_OFFSET		0
#define WEG_CGW7_GO3W_MASK		(0x1f << WEG_CGW7_GO3W_OFFSET)

#define WEG_CGW8_GOW_OFFSET		0
#define WEG_CGW8_GOW_MASK		(0x1f << WEG_CGW8_GOW_OFFSET)

#define WEG_CGW9_GOW_OFFSET		0
#define WEG_CGW9_GOW_MASK		(0x1f << WEG_CGW9_GOW_OFFSET)

#define WEG_CGW10_GIW_OFFSET		0
#define WEG_CGW10_GIW_OFFSET		4

stwuct jz_icdc {
	stwuct wegmap *wegmap;
	void __iomem *base;
	stwuct cwk *cwk;
};

static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(jz4725b_adc_twv,     0, 150, 0);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(jz4725b_dac_twv, -2250, 150, 0);
static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(jz4725b_mix_twv,
	 0, 11, TWV_DB_SCAWE_ITEM(-2250,   0, 0),
	12, 31, TWV_DB_SCAWE_ITEM(-2250, 150, 0),
);

static const SNDWV_CTW_TWVD_DECWAWE_DB_WANGE(jz4725b_out_twv,
	 0, 11, TWV_DB_SCAWE_ITEM(-3350, 200, 0),
	12, 23, TWV_DB_SCAWE_ITEM(-1050, 100, 0),
	24, 31, TWV_DB_SCAWE_ITEM(  100,  50, 0),
);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(jz4725b_mic_boost_twv, 0, 2000, 0);

static const chaw * const jz4725b_mic_mode_texts[] = {
	"Singwe Ended", "Diffewentiaw",
};

static const stwuct soc_enum jz4725b_mic_mode_enum =
	SOC_ENUM_SINGWE(JZ4725B_CODEC_WEG_CW3, WEG_CW3_MICDIFF_OFFSET,
			2, jz4725b_mic_mode_texts);

static const stwuct snd_kcontwow_new jz4725b_codec_contwows[] = {
	SOC_DOUBWE_TWV("DAC Pwayback Vowume",
		       JZ4725B_CODEC_WEG_CGW1,
		       WEG_CGW1_GODW_OFFSET,
		       WEG_CGW1_GODW_OFFSET,
		       0xf, 1, jz4725b_dac_twv),
	SOC_DOUBWE_TWV("Mastew Captuwe Vowume",
		       JZ4725B_CODEC_WEG_CGW10,
		       WEG_CGW10_GIW_OFFSET,
		       WEG_CGW10_GIW_OFFSET,
		       0xf, 0, jz4725b_adc_twv),
	SOC_DOUBWE_W_TWV("Mixew Wine In Bypass Pwayback Vowume",
			 JZ4725B_CODEC_WEG_CGW3,
			 JZ4725B_CODEC_WEG_CGW2,
			 WEG_CGW2_GO1W_OFFSET,
			 0x1f, 1, jz4725b_mix_twv),
	SOC_DOUBWE_W_TWV("Mixew Mic 1 Bypass Pwayback Vowume",
			 JZ4725B_CODEC_WEG_CGW5,
			 JZ4725B_CODEC_WEG_CGW4,
			 WEG_CGW4_GO2W_OFFSET,
			 0x1f, 1, jz4725b_mix_twv),
	SOC_DOUBWE_W_TWV("Mixew Mic 2 Bypass Pwayback Vowume",
			 JZ4725B_CODEC_WEG_CGW7,
			 JZ4725B_CODEC_WEG_CGW6,
			 WEG_CGW6_GO3W_OFFSET,
			 0x1f, 1, jz4725b_mix_twv),

	SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume",
			 JZ4725B_CODEC_WEG_CGW9,
			 JZ4725B_CODEC_WEG_CGW8,
			 WEG_CGW8_GOW_OFFSET,
			 0x1f, 1, jz4725b_out_twv),

	SOC_SINGWE("DAC Pwayback Switch", JZ4725B_CODEC_WEG_CW1,
		   WEG_CW1_DAC_MUTE_OFFSET, 1, 1),

	SOC_SINGWE("Deemphasize Fiwtew Pwayback Switch",
		   JZ4725B_CODEC_WEG_CW2,
		   WEG_CW2_DAC_DEEMP_OFFSET, 1, 0),

	SOC_SINGWE("High-Pass Fiwtew Captuwe Switch",
		   JZ4725B_CODEC_WEG_CW2,
		   WEG_CW2_ADC_HPF_OFFSET, 1, 0),

	SOC_ENUM("Mic Mode Captuwe Switch", jz4725b_mic_mode_enum),

	SOC_SINGWE_TWV("Mic1 Boost Captuwe Vowume",
		       JZ4725B_CODEC_WEG_PMW2,
		       WEG_PMW2_GIM_OFFSET,
		       1, 0, jz4725b_mic_boost_twv),
};

static const chaw * const jz4725b_codec_adc_swc_texts[] = {
	"Mic 1", "Mic 2", "Wine In", "Mixew",
};
static const unsigned int jz4725b_codec_adc_swc_vawues[] = { 0, 1, 2, 3, };
static SOC_VAWUE_ENUM_SINGWE_DECW(jz4725b_codec_adc_swc_enum,
				  JZ4725B_CODEC_WEG_CW3,
				  WEG_CW3_INSEW_OFFSET,
				  WEG_CW3_INSEW_MASK,
				  jz4725b_codec_adc_swc_texts,
				  jz4725b_codec_adc_swc_vawues);
static const stwuct snd_kcontwow_new jz4725b_codec_adc_swc_ctww =
	SOC_DAPM_ENUM("ADC Souwce Captuwe Woute", jz4725b_codec_adc_swc_enum);

static const stwuct snd_kcontwow_new jz4725b_codec_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wine In Bypass Pwayback Switch", JZ4725B_CODEC_WEG_CW1,
			WEG_CW1_BYPASS_OFFSET, 1, 0),
	SOC_DAPM_SINGWE("Mic 1 Bypass Pwayback Switch", JZ4725B_CODEC_WEG_CW3,
			WEG_CW3_SIDETONE1_OFFSET, 1, 0),
	SOC_DAPM_SINGWE("Mic 2 Bypass Pwayback Switch", JZ4725B_CODEC_WEG_CW3,
			WEG_CW3_SIDETONE2_OFFSET, 1, 0),
};

static int jz4725b_out_stage_enabwe(stwuct snd_soc_dapm_widget *w,
				    stwuct snd_kcontwow *kcontwow,
				    int event)
{
	stwuct snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	stwuct jz_icdc *icdc = snd_soc_component_get_dwvdata(codec);
	stwuct wegmap *map = icdc->wegmap;
	unsigned int vaw;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wetuwn wegmap_cweaw_bits(map, JZ4725B_CODEC_WEG_IFW,
					 BIT(WEG_IFW_WAMP_UP_DONE_OFFSET));
	case SND_SOC_DAPM_POST_PMU:
		wetuwn wegmap_wead_poww_timeout(map, JZ4725B_CODEC_WEG_IFW,
			       vaw, vaw & BIT(WEG_IFW_WAMP_UP_DONE_OFFSET),
			       100000, 500000);
	case SND_SOC_DAPM_PWE_PMD:
		wetuwn wegmap_cweaw_bits(map, JZ4725B_CODEC_WEG_IFW,
				BIT(WEG_IFW_WAMP_DOWN_DONE_OFFSET));
	case SND_SOC_DAPM_POST_PMD:
		wetuwn wegmap_wead_poww_timeout(map, JZ4725B_CODEC_WEG_IFW,
			       vaw, vaw & BIT(WEG_IFW_WAMP_DOWN_DONE_OFFSET),
			       100000, 500000);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct snd_soc_dapm_widget jz4725b_codec_dapm_widgets[] = {
	/* DAC */
	SND_SOC_DAPM_DAC("DAC", "Pwayback",
			 JZ4725B_CODEC_WEG_PMW1, WEG_PMW1_SB_DAC_OFFSET, 1),

	/* ADC */
	SND_SOC_DAPM_ADC("ADC", "Captuwe",
			 JZ4725B_CODEC_WEG_PMW1, WEG_PMW1_SB_ADC_OFFSET, 1),

	SND_SOC_DAPM_MUX("ADC Souwce Captuwe Woute", SND_SOC_NOPM, 0, 0,
			 &jz4725b_codec_adc_swc_ctww),

	/* Mixew */
	SND_SOC_DAPM_MIXEW("Mixew", JZ4725B_CODEC_WEG_PMW1,
			   WEG_PMW1_SB_MIX_OFFSET, 1,
			   jz4725b_codec_mixew_contwows,
			   AWWAY_SIZE(jz4725b_codec_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("DAC to Mixew", JZ4725B_CODEC_WEG_CW1,
			   WEG_CW1_DACSEW_OFFSET, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("Wine In", JZ4725B_CODEC_WEG_PMW1,
			   WEG_PMW1_SB_WIN_OFFSET, 1, NUWW, 0),
	SND_SOC_DAPM_MIXEW("HP Out", JZ4725B_CODEC_WEG_CW1,
			   WEG_CW1_HP_DIS_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_MIXEW("Mic 1", JZ4725B_CODEC_WEG_CW3,
			   WEG_CW3_SB_MIC1_OFFSET, 1, NUWW, 0),
	SND_SOC_DAPM_MIXEW("Mic 2", JZ4725B_CODEC_WEG_CW3,
			   WEG_CW3_SB_MIC2_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_MIXEW_E("Out Stage", JZ4725B_CODEC_WEG_PMW1,
			     WEG_PMW1_SB_OUT_OFFSET, 1, NUWW, 0,
			     jz4725b_out_stage_enabwe,
			     SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			     SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXEW("Mixew to ADC", JZ4725B_CODEC_WEG_PMW1,
			   WEG_PMW1_SB_IND_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Mic Bias", JZ4725B_CODEC_WEG_CW1,
			    WEG_CW1_SB_MICBIAS_OFFSET, 1, NUWW, 0),

	/* Pins */
	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),

	SND_SOC_DAPM_INPUT("WWINEIN"),
	SND_SOC_DAPM_INPUT("WWINEIN"),

	SND_SOC_DAPM_OUTPUT("WHPOUT"),
	SND_SOC_DAPM_OUTPUT("WHPOUT"),
};

static const stwuct snd_soc_dapm_woute jz4725b_codec_dapm_woutes[] = {
	{"Mic 1", NUWW, "MIC1P"},
	{"Mic 1", NUWW, "MIC1N"},
	{"Mic 2", NUWW, "MIC2P"},
	{"Mic 2", NUWW, "MIC2N"},

	{"Wine In", NUWW, "WWINEIN"},
	{"Wine In", NUWW, "WWINEIN"},

	{"Mixew", "Mic 1 Bypass Pwayback Switch", "Mic 1"},
	{"Mixew", "Mic 2 Bypass Pwayback Switch", "Mic 2"},
	{"Mixew", "Wine In Bypass Pwayback Switch", "Wine In"},
	{"DAC to Mixew", NUWW, "DAC"},
	{"Mixew", NUWW, "DAC to Mixew"},

	{"Mixew to ADC", NUWW, "Mixew"},
	{"ADC Souwce Captuwe Woute", "Mixew", "Mixew to ADC"},
	{"ADC Souwce Captuwe Woute", "Wine In", "Wine In"},
	{"ADC Souwce Captuwe Woute", "Mic 1", "Mic 1"},
	{"ADC Souwce Captuwe Woute", "Mic 2", "Mic 2"},
	{"ADC", NUWW, "ADC Souwce Captuwe Woute"},

	{"Out Stage", NUWW, "Mixew"},
	{"HP Out", NUWW, "Out Stage"},
	{"WHPOUT", NUWW, "HP Out"},
	{"WHPOUT", NUWW, "HP Out"},
};

static int jz4725b_codec_set_bias_wevew(stwuct snd_soc_component *component,
					enum snd_soc_bias_wevew wevew)
{
	stwuct jz_icdc *icdc = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *map = icdc->wegmap;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		wegmap_cweaw_bits(map, JZ4725B_CODEC_WEG_PMW2,
				  BIT(WEG_PMW2_SB_SWEEP_OFFSET));
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		/* Enabwe sound hawdwawe */
		wegmap_cweaw_bits(map, JZ4725B_CODEC_WEG_PMW2,
				  BIT(WEG_PMW2_SB_OFFSET));
		msweep(224);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		wegmap_set_bits(map, JZ4725B_CODEC_WEG_PMW2,
				BIT(WEG_PMW2_SB_SWEEP_OFFSET));
		bweak;
	case SND_SOC_BIAS_OFF:
		wegmap_set_bits(map, JZ4725B_CODEC_WEG_PMW2,
				BIT(WEG_PMW2_SB_OFFSET));
		bweak;
	}

	wetuwn 0;
}

static int jz4725b_codec_dev_pwobe(stwuct snd_soc_component *component)
{
	stwuct jz_icdc *icdc = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *map = icdc->wegmap;

	cwk_pwepawe_enabwe(icdc->cwk);

	/* Wwite CONFIGn (n=1 to 8) bits.
	 * The vawue 0x0f is specified in the datasheet as a wequiwement.
	 */
	wegmap_wwite(map, JZ4725B_CODEC_WEG_AICW,
		     0xf << WEG_AICW_CONFIG1_OFFSET);
	wegmap_wwite(map, JZ4725B_CODEC_WEG_CCW1,
		     0x0 << WEG_CCW1_CONFIG4_OFFSET);

	wetuwn 0;
}

static void jz4725b_codec_dev_wemove(stwuct snd_soc_component *component)
{
	stwuct jz_icdc *icdc = snd_soc_component_get_dwvdata(component);

	cwk_disabwe_unpwepawe(icdc->cwk);
}

static const stwuct snd_soc_component_dwivew jz4725b_codec = {
	.pwobe			= jz4725b_codec_dev_pwobe,
	.wemove			= jz4725b_codec_dev_wemove,
	.set_bias_wevew		= jz4725b_codec_set_bias_wevew,
	.contwows		= jz4725b_codec_contwows,
	.num_contwows		= AWWAY_SIZE(jz4725b_codec_contwows),
	.dapm_widgets		= jz4725b_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(jz4725b_codec_dapm_widgets),
	.dapm_woutes		= jz4725b_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(jz4725b_codec_dapm_woutes),
	.suspend_bias_off	= 1,
	.use_pmdown_time	= 1,
};

static const unsigned int jz4725b_codec_sampwe_wates[] = {
	96000, 48000, 44100, 32000,
	24000, 22050, 16000, 12000,
	11025, 9600, 8000,
};

static int jz4725b_codec_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct jz_icdc *icdc = snd_soc_component_get_dwvdata(dai->component);
	unsigned int wate, bit_width;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		bit_width = 0;
		bweak;
	case SNDWV_PCM_FOWMAT_S18_3WE:
		bit_width = 1;
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		bit_width = 2;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_3WE:
		bit_width = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (wate = 0; wate < AWWAY_SIZE(jz4725b_codec_sampwe_wates); wate++) {
		if (jz4725b_codec_sampwe_wates[wate] == pawams_wate(pawams))
			bweak;
	}

	if (wate == AWWAY_SIZE(jz4725b_codec_sampwe_wates))
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(icdc->wegmap,
				   JZ4725B_CODEC_WEG_CW2,
				   WEG_CW2_DAC_ADWW_MASK,
				   bit_width << WEG_CW2_DAC_ADWW_OFFSET);

		wegmap_update_bits(icdc->wegmap,
				   JZ4725B_CODEC_WEG_CCW2,
				   WEG_CCW2_DFWEQ_MASK,
				   wate << WEG_CCW2_DFWEQ_OFFSET);
	} ewse {
		wegmap_update_bits(icdc->wegmap,
				   JZ4725B_CODEC_WEG_CW2,
				   WEG_CW2_ADC_ADWW_MASK,
				   bit_width << WEG_CW2_ADC_ADWW_OFFSET);

		wegmap_update_bits(icdc->wegmap,
				   JZ4725B_CODEC_WEG_CCW2,
				   WEG_CCW2_AFWEQ_MASK,
				   wate << WEG_CCW2_AFWEQ_OFFSET);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops jz4725b_codec_dai_ops = {
	.hw_pawams = jz4725b_codec_hw_pawams,
};

#define JZ_ICDC_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE  | SNDWV_PCM_FMTBIT_S18_3WE | \
			 SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S24_3WE)

static stwuct snd_soc_dai_dwivew jz4725b_codec_dai = {
	.name = "jz4725b-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = JZ_ICDC_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = JZ_ICDC_FOWMATS,
	},
	.ops = &jz4725b_codec_dai_ops,
};

static boow jz4725b_codec_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == JZ4725B_CODEC_WEG_IFW;
}

static boow jz4725b_codec_can_access_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg != JZ4725B_CODEC_WEG_TW1) && (weg != JZ4725B_CODEC_WEG_TW2);
}

static int jz4725b_codec_io_wait(stwuct jz_icdc *icdc)
{
	u32 weg;

	wetuwn weadw_poww_timeout(icdc->base + ICDC_WGADW_OFFSET, weg,
				  !(weg & ICDC_WGADW_WGWW), 1000, 10000);
}

static int jz4725b_codec_weg_wead(void *context, unsigned int weg,
				  unsigned int *vaw)
{
	stwuct jz_icdc *icdc = context;
	unsigned int i;
	u32 tmp;
	int wet;

	wet = jz4725b_codec_io_wait(icdc);
	if (wet)
		wetuwn wet;

	tmp = weadw(icdc->base + ICDC_WGADW_OFFSET);
	tmp = (tmp & ~ICDC_WGADW_WGADDW_MASK)
	    | (weg << ICDC_WGADW_WGADDW_OFFSET);
	wwitew(tmp, icdc->base + ICDC_WGADW_OFFSET);

	/* wait 6+ cycwes */
	fow (i = 0; i < 6; i++)
		*vaw = weadw(icdc->base + ICDC_WGDATA_OFFSET) &
			ICDC_WGDATA_WGDOUT_MASK;

	wetuwn 0;
}

static int jz4725b_codec_weg_wwite(void *context, unsigned int weg,
				   unsigned int vaw)
{
	stwuct jz_icdc *icdc = context;
	int wet;

	wet = jz4725b_codec_io_wait(icdc);
	if (wet)
		wetuwn wet;

	wwitew(ICDC_WGADW_WGWW | (weg << ICDC_WGADW_WGADDW_OFFSET) | vaw,
			icdc->base + ICDC_WGADW_OFFSET);

	wet = jz4725b_codec_io_wait(icdc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const u8 jz4725b_codec_weg_defauwts[] = {
	0x0c, 0xaa, 0x78, 0x00, 0x00, 0xff, 0x03, 0x51,
	0x3f, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0xc0, 0x34,
	0x07, 0x44, 0x1f, 0x00,
};

static const stwuct wegmap_config jz4725b_codec_wegmap_config = {
	.weg_bits = 7,
	.vaw_bits = 8,

	.max_wegistew = JZ4725B_CODEC_WEG_AGC5,
	.vowatiwe_weg = jz4725b_codec_vowatiwe,
	.weadabwe_weg = jz4725b_codec_can_access_weg,
	.wwiteabwe_weg = jz4725b_codec_can_access_weg,

	.weg_wead = jz4725b_codec_weg_wead,
	.weg_wwite = jz4725b_codec_weg_wwite,

	.weg_defauwts_waw = jz4725b_codec_weg_defauwts,
	.num_weg_defauwts_waw = AWWAY_SIZE(jz4725b_codec_weg_defauwts),
	.cache_type = WEGCACHE_FWAT,
};

static int jz4725b_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct jz_icdc *icdc;
	int wet;

	icdc = devm_kzawwoc(dev, sizeof(*icdc), GFP_KEWNEW);
	if (!icdc)
		wetuwn -ENOMEM;

	icdc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(icdc->base))
		wetuwn PTW_EWW(icdc->base);

	icdc->wegmap = devm_wegmap_init(dev, NUWW, icdc,
					&jz4725b_codec_wegmap_config);
	if (IS_EWW(icdc->wegmap))
		wetuwn PTW_EWW(icdc->wegmap);

	icdc->cwk = devm_cwk_get(&pdev->dev, "aic");
	if (IS_EWW(icdc->cwk))
		wetuwn PTW_EWW(icdc->cwk);

	pwatfowm_set_dwvdata(pdev, icdc);

	wet = devm_snd_soc_wegistew_component(dev, &jz4725b_codec,
					      &jz4725b_codec_dai, 1);
	if (wet)
		dev_eww(dev, "Faiwed to wegistew codec\n");

	wetuwn wet;
}

static const stwuct of_device_id jz4725b_codec_of_matches[] = {
	{ .compatibwe = "ingenic,jz4725b-codec", },
	{ }
};
MODUWE_DEVICE_TABWE(of, jz4725b_codec_of_matches);

static stwuct pwatfowm_dwivew jz4725b_codec_dwivew = {
	.pwobe = jz4725b_codec_pwobe,
	.dwivew = {
		.name = "jz4725b-codec",
		.of_match_tabwe = jz4725b_codec_of_matches,
	},
};
moduwe_pwatfowm_dwivew(jz4725b_codec_dwivew);

MODUWE_DESCWIPTION("JZ4725B SoC intewnaw codec dwivew");
MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_WICENSE("GPW v2");
