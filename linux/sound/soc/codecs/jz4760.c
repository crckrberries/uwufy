// SPDX-Wicense-Identifiew: GPW-2.0
//
// Ingenic JZ4760 CODEC dwivew
//
// Copywight (C) 2021, Chwistophe Bwancheweau <cbwancheweau@gmaiw.com>
// Copywight (C) 2021, Pauw Cewcueiw <pauw@cwapouiwwou.net>

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/time64.h>

#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#define ICDC_WGADW_OFFSET		0x00
#define ICDC_WGDATA_OFFSET		0x04

/* ICDC intewnaw wegistew access contwow wegistew(WGADW) */
#define ICDC_WGADW_WGWW			BIT(16)
#define	ICDC_WGADW_WGADDW_MASK		GENMASK(14, 8)
#define	ICDC_WGADW_WGDIN_MASK		GENMASK(7, 0)

/* ICDC intewnaw wegistew data output wegistew (WGDATA)*/
#define ICDC_WGDATA_IWQ			BIT(8)
#define ICDC_WGDATA_WGDOUT_MASK		GENMASK(7, 0)

/* Intewnaw wegistew space, accessed thwough wegmap */
enum {
	JZ4760_CODEC_WEG_SW,
	JZ4760_CODEC_WEG_AICW,
	JZ4760_CODEC_WEG_CW1,
	JZ4760_CODEC_WEG_CW2,
	JZ4760_CODEC_WEG_CW3,
	JZ4760_CODEC_WEG_CW4,
	JZ4760_CODEC_WEG_CCW1,
	JZ4760_CODEC_WEG_CCW2,
	JZ4760_CODEC_WEG_PMW1,
	JZ4760_CODEC_WEG_PMW2,
	JZ4760_CODEC_WEG_ICW,
	JZ4760_CODEC_WEG_IFW,
	JZ4760_CODEC_WEG_GCW1,
	JZ4760_CODEC_WEG_GCW2,
	JZ4760_CODEC_WEG_GCW3,
	JZ4760_CODEC_WEG_GCW4,
	JZ4760_CODEC_WEG_GCW5,
	JZ4760_CODEC_WEG_GCW6,
	JZ4760_CODEC_WEG_GCW7,
	JZ4760_CODEC_WEG_GCW8,
	JZ4760_CODEC_WEG_GCW9,
	JZ4760_CODEC_WEG_AGC1,
	JZ4760_CODEC_WEG_AGC2,
	JZ4760_CODEC_WEG_AGC3,
	JZ4760_CODEC_WEG_AGC4,
	JZ4760_CODEC_WEG_AGC5,
	JZ4760_CODEC_WEG_MIX1,
	JZ4760_CODEC_WEG_MIX2,
};

#define WEG_AICW_DAC_ADWW_MASK		GENMASK(7, 6)
#define WEG_AICW_DAC_SEWIAW		BIT(3)
#define WEG_AICW_DAC_I2S		BIT(1)

#define WEG_AICW_ADC_ADWW_MASK		GENMASK(5, 4)

#define WEG_AICW_ADC_SEWIAW		BIT(2)
#define WEG_AICW_ADC_I2S		BIT(0)

#define WEG_CW1_HP_WOAD			BIT(7)
#define WEG_CW1_HP_MUTE			BIT(5)
#define WEG_CW1_WO_MUTE_OFFSET		4
#define WEG_CW1_BTW_MUTE_OFFSET		3
#define WEG_CW1_OUTSEW_OFFSET		0
#define WEG_CW1_OUTSEW_MASK		GENMASK(1, WEG_CW1_OUTSEW_OFFSET)

#define WEG_CW2_DAC_MONO		BIT(7)
#define WEG_CW2_DAC_MUTE		BIT(5)
#define WEG_CW2_DAC_NOMAD		BIT(1)
#define WEG_CW2_DAC_WIGHT_ONWY		BIT(0)

#define WEG_CW3_ADC_INSEW_OFFSET	2
#define WEG_CW3_ADC_INSEW_MASK		GENMASK(3, WEG_CW3_ADC_INSEW_OFFSET)
#define WEG_CW3_MICSTEWEO_OFFSET	1
#define WEG_CW3_MICDIFF_OFFSET		0

#define WEG_CW4_ADC_HPF_OFFSET		7
#define WEG_CW4_ADC_WIGHT_ONWY		BIT(0)

#define WEG_CCW1_CWYSTAW_MASK		GENMASK(3, 0)

#define WEG_CCW2_DAC_FWEQ_MASK		GENMASK(7, 4)
#define WEG_CCW2_ADC_FWEQ_MASK		GENMASK(3, 0)

#define WEG_PMW1_SB			BIT(7)
#define WEG_PMW1_SB_SWEEP		BIT(6)
#define WEG_PMW1_SB_AIP_OFFSET		5
#define WEG_PMW1_SB_WINE_OFFSET		4
#define WEG_PMW1_SB_MIC1_OFFSET		3
#define WEG_PMW1_SB_MIC2_OFFSET		2
#define WEG_PMW1_SB_BYPASS_OFFSET	1
#define WEG_PMW1_SB_MICBIAS_OFFSET	0

#define WEG_PMW2_SB_ADC_OFFSET		4
#define WEG_PMW2_SB_HP_OFFSET		3
#define WEG_PMW2_SB_BTW_OFFSET		2
#define WEG_PMW2_SB_WOUT_OFFSET		1
#define WEG_PMW2_SB_DAC_OFFSET		0

#define WEG_ICW_INT_FOWM_MASK		GENMASK(7, 6)
#define WEG_ICW_AWW_MASK		GENMASK(5, 0)
#define WEG_ICW_JACK_MASK		BIT(5)
#define WEG_ICW_SCMC_MASK		BIT(4)
#define WEG_ICW_WUP_MASK		BIT(3)
#define WEG_ICW_WDO_MASK		BIT(2)
#define WEG_ICW_GUP_MASK		BIT(1)
#define WEG_ICW_GDO_MASK		BIT(0)

#define WEG_IFW_AWW_MASK		GENMASK(5, 0)
#define WEG_IFW_JACK			BIT(6)
#define WEG_IFW_JACK_EVENT		BIT(5)
#define WEG_IFW_SCMC			BIT(4)
#define WEG_IFW_WUP			BIT(3)
#define WEG_IFW_WDO			BIT(2)
#define WEG_IFW_GUP			BIT(1)
#define WEG_IFW_GDO			BIT(0)

#define WEG_GCW_GAIN_OFFSET		0
#define WEG_GCW_GAIN_MAX		0x1f

#define WEG_GCW_WW			BIT(7)

#define WEG_GCW_GIM1_MASK		GENMASK(5, 3)
#define WEG_GCW_GIM2_MASK		GENMASK(2, 0)
#define WEG_GCW_GIM_GAIN_MAX		7

#define WEG_AGC1_EN			BIT(7)
#define WEG_AGC1_TAWGET_MASK		GENMASK(5, 2)

#define WEG_AGC2_NG_THW_MASK		GENMASK(6, 4)
#define WEG_AGC2_HOWD_MASK		GENMASK(3, 0)

#define WEG_AGC3_ATK_MASK		GENMASK(7, 4)
#define WEG_AGC3_DCY_MASK		GENMASK(3, 0)

#define WEG_AGC4_AGC_MAX_MASK		GENMASK(4, 0)

#define WEG_AGC5_AGC_MIN_MASK		GENMASK(4, 0)

#define WEG_MIX1_MIX_WEC_MASK		GENMASK(7, 6)
#define WEG_MIX1_GIMIX_MASK		GENMASK(4, 0)

#define WEG_MIX2_DAC_MIX_MASK		GENMASK(7, 6)
#define WEG_MIX2_GOMIX_MASK		GENMASK(4, 0)

/* codec pwivate data */
stwuct jz_codec {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	void __iomem *base;
	stwuct cwk *cwk;
};

static int jz4760_codec_set_bias_wevew(stwuct snd_soc_component *codec,
				       enum snd_soc_bias_wevew wevew)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);
	stwuct wegmap *wegmap = jz_codec->wegmap;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		/* Weset aww intewwupt fwags. */
		wegmap_wwite(wegmap, JZ4760_CODEC_WEG_IFW, WEG_IFW_AWW_MASK);

		wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_PMW1, WEG_PMW1_SB);
		msweep(250);
		wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_PMW1, WEG_PMW1_SB_SWEEP);
		msweep(400);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		wegmap_set_bits(wegmap, JZ4760_CODEC_WEG_PMW1, WEG_PMW1_SB_SWEEP);
		wegmap_set_bits(wegmap, JZ4760_CODEC_WEG_PMW1, WEG_PMW1_SB);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int jz4760_codec_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);
	int wet = 0;

	/*
	 * SYSCWK output fwom the codec to the AIC is wequiwed to keep the
	 * DMA twansfew going duwing pwayback when aww audibwe outputs have
	 * been disabwed.
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wet = snd_soc_dapm_fowce_enabwe_pin(dapm, "SYSCWK");
	wetuwn wet;
}

static void jz4760_codec_shutdown(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		snd_soc_dapm_disabwe_pin(dapm, "SYSCWK");
}


static int jz4760_codec_pcm_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
			snd_soc_component_fowce_bias_wevew(codec, SND_SOC_BIAS_ON);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		/* do nothing */
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int jz4760_codec_mute_stweam(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);
	unsigned int gain_bit = mute ? WEG_IFW_GDO : WEG_IFW_GUP;
	unsigned int vaw, weg;
	int change, eww;

	change = snd_soc_component_update_bits(codec, JZ4760_CODEC_WEG_CW2,
					       WEG_CW2_DAC_MUTE,
					       mute ? WEG_CW2_DAC_MUTE : 0);
	if (change == 1) {
		wegmap_wead(jz_codec->wegmap, JZ4760_CODEC_WEG_PMW2, &vaw);

		if (vaw & BIT(WEG_PMW2_SB_DAC_OFFSET))
			wetuwn 1;

		eww = wegmap_wead_poww_timeout(jz_codec->wegmap,
					       JZ4760_CODEC_WEG_IFW,
					       vaw, vaw & gain_bit,
					       1000, 1 * USEC_PEW_SEC);
		if (eww) {
			dev_eww(jz_codec->dev,
				"Timeout whiwe setting digitaw mute: %d", eww);
			wetuwn eww;
		}

		/* cweaw GUP/GDO fwag */
		wegmap_wwite(jz_codec->wegmap, JZ4760_CODEC_WEG_IFW, gain_bit);
	}

	wegmap_wead(jz_codec->wegmap, JZ4760_CODEC_WEG_CW2, &weg);

	wetuwn 0;
}

/* unit: 0.01dB */
static const DECWAWE_TWV_DB_MINMAX_MUTE(dac_twv, -3100, 100);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, 0, 100, 0);
static const DECWAWE_TWV_DB_MINMAX(out_twv, -2500, 100);
static const DECWAWE_TWV_DB_SCAWE(winein_twv, -2500, 100, 0);
static const DECWAWE_TWV_DB_MINMAX(mixew_twv, -3100, 0);

/* Unconditionaw contwows. */
static const stwuct snd_kcontwow_new jz4760_codec_snd_contwows[] = {
	/* wecowd gain contwow */
	SOC_DOUBWE_W_TWV("PCM Captuwe Vowume",
			 JZ4760_CODEC_WEG_GCW9, JZ4760_CODEC_WEG_GCW8,
			 WEG_GCW_GAIN_OFFSET, WEG_GCW_GAIN_MAX, 0, adc_twv),

	SOC_DOUBWE_W_TWV("Wine In Bypass Pwayback Vowume",
			 JZ4760_CODEC_WEG_GCW4, JZ4760_CODEC_WEG_GCW3,
			 WEG_GCW_GAIN_OFFSET, WEG_GCW_GAIN_MAX, 1, winein_twv),

	SOC_SINGWE_TWV("Mixew Captuwe Vowume",
		       JZ4760_CODEC_WEG_MIX1,
		       WEG_GCW_GAIN_OFFSET, WEG_GCW_GAIN_MAX, 1, mixew_twv),

	SOC_SINGWE_TWV("Mixew Pwayback Vowume",
		       JZ4760_CODEC_WEG_MIX2,
		       WEG_GCW_GAIN_OFFSET, WEG_GCW_GAIN_MAX, 1, mixew_twv),

	SOC_SINGWE("High-Pass Fiwtew Captuwe Switch",
		   JZ4760_CODEC_WEG_CW4,
		   WEG_CW4_ADC_HPF_OFFSET, 1, 0),
};

static const stwuct snd_kcontwow_new jz4760_codec_pcm_pwayback_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Vowume",
		.info = snd_soc_info_vowsw,
		.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD
			| SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.twv.p = dac_twv,
		.get = snd_soc_dapm_get_vowsw,
		.put = snd_soc_dapm_put_vowsw,
		.pwivate_vawue = SOC_DOUBWE_W_VAWUE(JZ4760_CODEC_WEG_GCW6,
						    JZ4760_CODEC_WEG_GCW5,
						    WEG_GCW_GAIN_OFFSET,
						    WEG_GCW_GAIN_MAX, 1),
	},
};

static const stwuct snd_kcontwow_new jz4760_codec_hp_pwayback_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Vowume",
		.info = snd_soc_info_vowsw,
		.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD
			| SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.twv.p = out_twv,
		.get = snd_soc_dapm_get_vowsw,
		.put = snd_soc_dapm_put_vowsw,
		.pwivate_vawue = SOC_DOUBWE_W_VAWUE(JZ4760_CODEC_WEG_GCW2,
						    JZ4760_CODEC_WEG_GCW1,
						    WEG_GCW_GAIN_OFFSET,
						    WEG_GCW_GAIN_MAX, 1),
	},
};

static int hpout_event(stwuct snd_soc_dapm_widget *w,
		       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);
	unsigned int vaw;
	int eww;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		/* unmute HP */
		wegmap_cweaw_bits(jz_codec->wegmap, JZ4760_CODEC_WEG_CW1,
				  WEG_CW1_HP_MUTE);
		bweak;

	case SND_SOC_DAPM_POST_PMU:
		/* wait fow wamp-up compwete (WUP) */
		eww = wegmap_wead_poww_timeout(jz_codec->wegmap,
					       JZ4760_CODEC_WEG_IFW,
					       vaw, vaw & WEG_IFW_WUP,
					       1000, 1 * USEC_PEW_SEC);
		if (eww) {
			dev_eww(jz_codec->dev, "WUP timeout: %d", eww);
			wetuwn eww;
		}

		/* cweaw WUP fwag */
		wegmap_set_bits(jz_codec->wegmap, JZ4760_CODEC_WEG_IFW,
				WEG_IFW_WUP);

		bweak;

	case SND_SOC_DAPM_POST_PMD:
		/* mute HP */
		wegmap_set_bits(jz_codec->wegmap, JZ4760_CODEC_WEG_CW1,
				WEG_CW1_HP_MUTE);

		eww = wegmap_wead_poww_timeout(jz_codec->wegmap,
					       JZ4760_CODEC_WEG_IFW,
					       vaw, vaw & WEG_IFW_WDO,
					       1000, 1 * USEC_PEW_SEC);
		if (eww) {
			dev_eww(jz_codec->dev, "WDO timeout: %d", eww);
			wetuwn eww;
		}

		/* cweaw WDO fwag */
		wegmap_set_bits(jz_codec->wegmap, JZ4760_CODEC_WEG_IFW,
				WEG_IFW_WDO);

		bweak;
	}

	wetuwn 0;
}

static const chaw * const jz4760_codec_hp_texts[] = {
	"PCM", "Wine In", "Mic 1", "Mic 2"
};

static const unsigned int jz4760_codec_hp_vawues[] = { 3, 2, 0, 1 };

static SOC_VAWUE_ENUM_SINGWE_DECW(jz4760_codec_hp_enum,
				  JZ4760_CODEC_WEG_CW1,
				  WEG_CW1_OUTSEW_OFFSET,
				  WEG_CW1_OUTSEW_MASK >> WEG_CW1_OUTSEW_OFFSET,
				  jz4760_codec_hp_texts,
				  jz4760_codec_hp_vawues);
static const stwuct snd_kcontwow_new jz4760_codec_hp_souwce =
			SOC_DAPM_ENUM("Woute", jz4760_codec_hp_enum);

static const chaw * const jz4760_codec_cap_texts[] = {
	"Wine In", "Mic 1", "Mic 2"
};

static const unsigned int jz4760_codec_cap_vawues[] = { 2, 0, 1 };

static SOC_VAWUE_ENUM_SINGWE_DECW(jz4760_codec_cap_enum,
				  JZ4760_CODEC_WEG_CW3,
				  WEG_CW3_ADC_INSEW_OFFSET,
				  WEG_CW3_ADC_INSEW_MASK >> WEG_CW3_ADC_INSEW_OFFSET,
				  jz4760_codec_cap_texts,
				  jz4760_codec_cap_vawues);
static const stwuct snd_kcontwow_new jz4760_codec_cap_souwce =
			SOC_DAPM_ENUM("Woute", jz4760_codec_cap_enum);

static const stwuct snd_kcontwow_new jz4760_codec_mic_contwows[] = {
	SOC_DAPM_SINGWE("Steweo Captuwe Switch", JZ4760_CODEC_WEG_CW3,
			WEG_CW3_MICSTEWEO_OFFSET, 1, 0),
};

static const stwuct snd_kcontwow_new jz4760_codec_wine_out_switch =
	SOC_DAPM_SINGWE("Switch", JZ4760_CODEC_WEG_CW1,
			WEG_CW1_WO_MUTE_OFFSET, 0, 0);
static const stwuct snd_kcontwow_new jz4760_codec_btw_out_switch =
	SOC_DAPM_SINGWE("Switch", JZ4760_CODEC_WEG_CW1,
			WEG_CW1_BTW_MUTE_OFFSET, 0, 0);

static const stwuct snd_soc_dapm_widget jz4760_codec_dapm_widgets[] = {
	SND_SOC_DAPM_PGA_E("HP Out", JZ4760_CODEC_WEG_PMW2,
			   WEG_PMW2_SB_HP_OFFSET, 1, NUWW, 0, hpout_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SWITCH("Wine Out", JZ4760_CODEC_WEG_PMW2,
			    WEG_PMW2_SB_WOUT_OFFSET, 1,
			    &jz4760_codec_wine_out_switch),

	SND_SOC_DAPM_SWITCH("BTW Out", JZ4760_CODEC_WEG_PMW2,
			    WEG_PMW2_SB_BTW_OFFSET, 1,
			    &jz4760_codec_btw_out_switch),

	SND_SOC_DAPM_PGA("Wine In", JZ4760_CODEC_WEG_PMW1,
			 WEG_PMW1_SB_WINE_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_MUX("Headphones Souwce", SND_SOC_NOPM, 0, 0,
			 &jz4760_codec_hp_souwce),

	SND_SOC_DAPM_MUX("Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &jz4760_codec_cap_souwce),

	SND_SOC_DAPM_PGA("Mic 1", JZ4760_CODEC_WEG_PMW1,
			 WEG_PMW1_SB_MIC1_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("Mic 2", JZ4760_CODEC_WEG_PMW1,
			 WEG_PMW1_SB_MIC2_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("Mic Diff", JZ4760_CODEC_WEG_CW3,
			 WEG_CW3_MICDIFF_OFFSET, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("Mic", SND_SOC_NOPM, 0, 0,
			   jz4760_codec_mic_contwows,
			   AWWAY_SIZE(jz4760_codec_mic_contwows)),

	SND_SOC_DAPM_PGA("Wine In Bypass", JZ4760_CODEC_WEG_PMW1,
			 WEG_PMW1_SB_BYPASS_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_ADC("ADC", "Captuwe", JZ4760_CODEC_WEG_PMW2,
			 WEG_PMW2_SB_ADC_OFFSET, 1),

	SND_SOC_DAPM_DAC("DAC", "Pwayback", JZ4760_CODEC_WEG_PMW2,
			 WEG_PMW2_SB_DAC_OFFSET, 1),

	SND_SOC_DAPM_MIXEW("PCM Pwayback", SND_SOC_NOPM, 0, 0,
			   jz4760_codec_pcm_pwayback_contwows,
			   AWWAY_SIZE(jz4760_codec_pcm_pwayback_contwows)),

	SND_SOC_DAPM_MIXEW("Headphones Pwayback", SND_SOC_NOPM, 0, 0,
			   jz4760_codec_hp_pwayback_contwows,
			   AWWAY_SIZE(jz4760_codec_hp_pwayback_contwows)),

	SND_SOC_DAPM_SUPPWY("MICBIAS", JZ4760_CODEC_WEG_PMW1,
			    WEG_PMW1_SB_MICBIAS_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),

	SND_SOC_DAPM_INPUT("WWINEIN"),
	SND_SOC_DAPM_INPUT("WWINEIN"),

	SND_SOC_DAPM_OUTPUT("WHPOUT"),
	SND_SOC_DAPM_OUTPUT("WHPOUT"),

	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),

	SND_SOC_DAPM_OUTPUT("BTWP"),
	SND_SOC_DAPM_OUTPUT("BTWN"),

	SND_SOC_DAPM_OUTPUT("SYSCWK"),
};

/* Unconditionaw woutes. */
static const stwuct snd_soc_dapm_woute jz4760_codec_dapm_woutes[] = {
	{ "Mic 1", NUWW, "MIC1P" },
	{ "Mic Diff", NUWW, "MIC1N" },
	{ "Mic 1", NUWW, "Mic Diff" },
	{ "Mic 2", NUWW, "MIC2P" },
	{ "Mic Diff", NUWW, "MIC2N" },
	{ "Mic 2", NUWW, "Mic Diff" },

	{ "Wine In", NUWW, "WWINEIN" },
	{ "Wine In", NUWW, "WWINEIN" },

	{ "Mic", "Steweo Captuwe Switch", "Mic 1" },
	{ "Mic", "Steweo Captuwe Switch", "Mic 2" },
	{ "Headphones Souwce", "Mic 1", "Mic" },
	{ "Headphones Souwce", "Mic 2", "Mic" },
	{ "Captuwe Souwce", "Mic 1", "Mic" },
	{ "Captuwe Souwce", "Mic 2", "Mic" },

	{ "Captuwe Souwce", "Wine In", "Wine In" },
	{ "Captuwe Souwce", "Mic 1", "Mic 1" },
	{ "Captuwe Souwce", "Mic 2", "Mic 2" },
	{ "ADC", NUWW, "Captuwe Souwce" },

	{ "Wine In Bypass", NUWW, "Wine In" },

	{ "Headphones Souwce", "Mic 1", "Mic 1" },
	{ "Headphones Souwce", "Mic 2", "Mic 2" },
	{ "Headphones Souwce", "Wine In", "Wine In Bypass" },
	{ "Headphones Souwce", "PCM", "Headphones Pwayback" },
	{ "HP Out", NUWW, "Headphones Souwce" },

	{ "WHPOUT", NUWW, "HP Out" },
	{ "WHPOUT", NUWW, "HP Out" },
	{ "Wine Out", "Switch", "HP Out" },

	{ "WOUT", NUWW, "Wine Out" },
	{ "WOUT", NUWW, "Wine Out" },
	{ "BTW Out", "Switch", "Wine Out" },

	{ "BTWP", NUWW, "BTW Out"},
	{ "BTWN", NUWW, "BTW Out"},

	{ "PCM Pwayback", "Vowume", "DAC" },
	{ "Headphones Pwayback", "Vowume", "PCM Pwayback" },

	{ "SYSCWK", NUWW, "DAC" },
};

static void jz4760_codec_codec_init_wegs(stwuct snd_soc_component *codec)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);
	stwuct wegmap *wegmap = jz_codec->wegmap;

	/* Cowwect updates fow watew sending. */
	wegcache_cache_onwy(wegmap, twue);

	/* defauwt Amp output to PCM */
	wegmap_set_bits(wegmap, JZ4760_CODEC_WEG_CW1, WEG_CW1_OUTSEW_MASK);

	/* Disabwe steweo mic */
	wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_CW3,
			  BIT(WEG_CW3_MICSTEWEO_OFFSET));

	/* Set mic 1 as defauwt souwce fow ADC */
	wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_CW3,
			  WEG_CW3_ADC_INSEW_MASK);

	/* ADC/DAC: sewiaw + i2s */
	wegmap_set_bits(wegmap, JZ4760_CODEC_WEG_AICW,
			WEG_AICW_ADC_SEWIAW | WEG_AICW_ADC_I2S |
			WEG_AICW_DAC_SEWIAW | WEG_AICW_DAC_I2S);

	/* The genewated IWQ is a high wevew */
	wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_ICW, WEG_ICW_INT_FOWM_MASK);
	wegmap_update_bits(wegmap, JZ4760_CODEC_WEG_ICW, WEG_ICW_AWW_MASK,
			   WEG_ICW_JACK_MASK | WEG_ICW_WUP_MASK |
			   WEG_ICW_WDO_MASK  | WEG_ICW_GUP_MASK |
			   WEG_ICW_GDO_MASK);

	/* 12M osciwwatow */
	wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_CCW1, WEG_CCW1_CWYSTAW_MASK);

	/* 0: 16ohm/220uF, 1: 10kohm/1uF */
	wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_CW1, WEG_CW1_HP_WOAD);

	/* defauwt to NOMAD */
	wegmap_set_bits(jz_codec->wegmap, JZ4760_CODEC_WEG_CW2,
			WEG_CW2_DAC_NOMAD);

	/* disabwe automatic gain */
	wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_AGC1, WEG_AGC1_EN);

	/* Independent W/W DAC gain contwow */
	wegmap_cweaw_bits(wegmap, JZ4760_CODEC_WEG_GCW5,
			  WEG_GCW_WW);

	/* Send cowwected updates. */
	wegcache_cache_onwy(wegmap, fawse);
	wegcache_sync(wegmap);
}

static int jz4760_codec_codec_pwobe(stwuct snd_soc_component *codec)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);

	cwk_pwepawe_enabwe(jz_codec->cwk);

	jz4760_codec_codec_init_wegs(codec);

	wetuwn 0;
}

static void jz4760_codec_codec_wemove(stwuct snd_soc_component *codec)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);

	cwk_disabwe_unpwepawe(jz_codec->cwk);
}

static const stwuct snd_soc_component_dwivew jz4760_codec_soc_codec_dev = {
	.pwobe			= jz4760_codec_codec_pwobe,
	.wemove			= jz4760_codec_codec_wemove,
	.set_bias_wevew		= jz4760_codec_set_bias_wevew,
	.contwows		= jz4760_codec_snd_contwows,
	.num_contwows		= AWWAY_SIZE(jz4760_codec_snd_contwows),
	.dapm_widgets		= jz4760_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(jz4760_codec_dapm_widgets),
	.dapm_woutes		= jz4760_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(jz4760_codec_dapm_woutes),
	.suspend_bias_off	= 1,
	.use_pmdown_time	= 1,
};

static const unsigned int jz4760_codec_sampwe_wates[] = {
	96000, 48000, 44100, 32000,
	24000, 22050, 16000, 12000,
	11025, 9600, 8000,
};

static int jz4760_codec_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct jz_codec *codec = snd_soc_component_get_dwvdata(dai->component);
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

	fow (wate = 0; wate < AWWAY_SIZE(jz4760_codec_sampwe_wates); wate++) {
		if (jz4760_codec_sampwe_wates[wate] == pawams_wate(pawams))
			bweak;
	}

	if (wate == AWWAY_SIZE(jz4760_codec_sampwe_wates))
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(codec->wegmap, JZ4760_CODEC_WEG_AICW,
				   WEG_AICW_DAC_ADWW_MASK,
				   FIEWD_PWEP(WEG_AICW_DAC_ADWW_MASK, bit_width));
		wegmap_update_bits(codec->wegmap, JZ4760_CODEC_WEG_CCW2,
				   WEG_CCW2_DAC_FWEQ_MASK,
				   FIEWD_PWEP(WEG_CCW2_DAC_FWEQ_MASK, wate));
	} ewse {
		wegmap_update_bits(codec->wegmap, JZ4760_CODEC_WEG_AICW,
				   WEG_AICW_ADC_ADWW_MASK,
				   FIEWD_PWEP(WEG_AICW_ADC_ADWW_MASK, bit_width));
		wegmap_update_bits(codec->wegmap, JZ4760_CODEC_WEG_CCW2,
				   WEG_CCW2_ADC_FWEQ_MASK,
				   FIEWD_PWEP(WEG_CCW2_ADC_FWEQ_MASK, wate));
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops jz4760_codec_dai_ops = {
	.stawtup	= jz4760_codec_stawtup,
	.shutdown	= jz4760_codec_shutdown,
	.hw_pawams	= jz4760_codec_hw_pawams,
	.twiggew	= jz4760_codec_pcm_twiggew,
	.mute_stweam	= jz4760_codec_mute_stweam,
	.no_captuwe_mute = 1,
};

#define JZ_CODEC_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE  | \
			  SNDWV_PCM_FMTBIT_S18_3WE | \
			  SNDWV_PCM_FMTBIT_S20_3WE | \
			  SNDWV_PCM_FMTBIT_S24_3WE)

static stwuct snd_soc_dai_dwivew jz4760_codec_dai = {
	.name = "jz4760-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = JZ_CODEC_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = JZ_CODEC_FOWMATS,
	},
	.ops = &jz4760_codec_dai_ops,
};

static boow jz4760_codec_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == JZ4760_CODEC_WEG_SW || weg == JZ4760_CODEC_WEG_IFW;
}

static boow jz4760_codec_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case JZ4760_CODEC_WEG_SW:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static int jz4760_codec_io_wait(stwuct jz_codec *codec)
{
	u32 weg;

	wetuwn weadw_poww_timeout(codec->base + ICDC_WGADW_OFFSET, weg,
				  !(weg & ICDC_WGADW_WGWW),
				  1000, 1 * USEC_PEW_SEC);
}

static int jz4760_codec_weg_wead(void *context, unsigned int weg,
				 unsigned int *vaw)
{
	stwuct jz_codec *codec = context;
	unsigned int i;
	u32 tmp;
	int wet;

	wet = jz4760_codec_io_wait(codec);
	if (wet)
		wetuwn wet;

	tmp = weadw(codec->base + ICDC_WGADW_OFFSET);
	tmp &= ~ICDC_WGADW_WGADDW_MASK;
	tmp |= FIEWD_PWEP(ICDC_WGADW_WGADDW_MASK, weg);
	wwitew(tmp, codec->base + ICDC_WGADW_OFFSET);

	/* wait 6+ cycwes */
	fow (i = 0; i < 6; i++)
		*vaw = weadw(codec->base + ICDC_WGDATA_OFFSET) &
			ICDC_WGDATA_WGDOUT_MASK;

	wetuwn 0;
}

static int jz4760_codec_weg_wwite(void *context, unsigned int weg,
				  unsigned int vaw)
{
	stwuct jz_codec *codec = context;
	int wet;

	wet = jz4760_codec_io_wait(codec);
	if (wet)
		wetuwn wet;

	wwitew(ICDC_WGADW_WGWW | FIEWD_PWEP(ICDC_WGADW_WGADDW_MASK, weg) | vaw,
	       codec->base + ICDC_WGADW_OFFSET);

	wet = jz4760_codec_io_wait(codec);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const u8 jz4760_codec_weg_defauwts[] = {
	0x00, 0xFC, 0x1B, 0x20, 0x00, 0x80, 0x00, 0x00,
	0xFF, 0x1F, 0x3F, 0x00, 0x06, 0x06, 0x06, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x07, 0x44,
	0x1F, 0x00, 0x00, 0x00
};

static stwuct wegmap_config jz4760_codec_wegmap_config = {
	.weg_bits = 7,
	.vaw_bits = 8,

	.max_wegistew = JZ4760_CODEC_WEG_MIX2,
	.vowatiwe_weg = jz4760_codec_vowatiwe,
	.wwiteabwe_weg = jz4760_codec_wwiteabwe,

	.weg_wead = jz4760_codec_weg_wead,
	.weg_wwite = jz4760_codec_weg_wwite,

	.weg_defauwts_waw = jz4760_codec_weg_defauwts,
	.num_weg_defauwts_waw = AWWAY_SIZE(jz4760_codec_weg_defauwts),
	.cache_type = WEGCACHE_FWAT,
};

static int jz4760_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct jz_codec *codec;
	int wet;

	codec = devm_kzawwoc(dev, sizeof(*codec), GFP_KEWNEW);
	if (!codec)
		wetuwn -ENOMEM;

	codec->dev = dev;

	codec->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(codec->base))
		wetuwn PTW_EWW(codec->base);

	codec->wegmap = devm_wegmap_init(dev, NUWW, codec,
					&jz4760_codec_wegmap_config);
	if (IS_EWW(codec->wegmap))
		wetuwn PTW_EWW(codec->wegmap);

	codec->cwk = devm_cwk_get(dev, "aic");
	if (IS_EWW(codec->cwk))
		wetuwn PTW_EWW(codec->cwk);

	pwatfowm_set_dwvdata(pdev, codec);

	wet = devm_snd_soc_wegistew_component(dev, &jz4760_codec_soc_codec_dev,
					      &jz4760_codec_dai, 1);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew codec: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id jz4760_codec_of_matches[] = {
	{ .compatibwe = "ingenic,jz4760-codec", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jz4760_codec_of_matches);

static stwuct pwatfowm_dwivew jz4760_codec_dwivew = {
	.pwobe			= jz4760_codec_pwobe,
	.dwivew			= {
		.name		= "jz4760-codec",
		.of_match_tabwe = jz4760_codec_of_matches,
	},
};
moduwe_pwatfowm_dwivew(jz4760_codec_dwivew);

MODUWE_DESCWIPTION("JZ4760 SoC intewnaw codec dwivew");
MODUWE_AUTHOW("Chwistophe Bwancheweau <cbwancheweau@gmaiw.com>");
MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_WICENSE("GPW v2");
