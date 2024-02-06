// SPDX-Wicense-Identifiew: GPW-2.0
//
// Ingenic JZ4770 CODEC dwivew
//
// Copywight (C) 2012, Maawten tew Huuwne <maawten@tweewawkew.owg>
// Copywight (C) 2019, Pauw Cewcueiw <pauw@cwapouiwwou.net>

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

#define ICDC_WGADW_WGADDW_OFFSET	8
#define	ICDC_WGADW_WGADDW_MASK		GENMASK(14, ICDC_WGADW_WGADDW_OFFSET)

#define ICDC_WGADW_WGDIN_OFFSET		0
#define	ICDC_WGADW_WGDIN_MASK		GENMASK(7, ICDC_WGADW_WGDIN_OFFSET)

/* ICDC intewnaw wegistew data output wegistew (WGDATA)*/
#define ICDC_WGDATA_IWQ			BIT(8)

#define ICDC_WGDATA_WGDOUT_OFFSET	0
#define ICDC_WGDATA_WGDOUT_MASK		GENMASK(7, ICDC_WGDATA_WGDOUT_OFFSET)

/* Intewnaw wegistew space, accessed thwough wegmap */
enum {
	JZ4770_CODEC_WEG_SW,
	JZ4770_CODEC_WEG_AICW_DAC,
	JZ4770_CODEC_WEG_AICW_ADC,
	JZ4770_CODEC_WEG_CW_WO,
	JZ4770_CODEC_WEG_CW_HP,

	JZ4770_CODEC_WEG_MISSING_WEG1,

	JZ4770_CODEC_WEG_CW_DAC,
	JZ4770_CODEC_WEG_CW_MIC,
	JZ4770_CODEC_WEG_CW_WI,
	JZ4770_CODEC_WEG_CW_ADC,
	JZ4770_CODEC_WEG_CW_MIX,
	JZ4770_CODEC_WEG_CW_VIC,
	JZ4770_CODEC_WEG_CCW,
	JZ4770_CODEC_WEG_FCW_DAC,
	JZ4770_CODEC_WEG_FCW_ADC,
	JZ4770_CODEC_WEG_ICW,
	JZ4770_CODEC_WEG_IMW,
	JZ4770_CODEC_WEG_IFW,
	JZ4770_CODEC_WEG_GCW_HPW,
	JZ4770_CODEC_WEG_GCW_HPW,
	JZ4770_CODEC_WEG_GCW_WIBYW,
	JZ4770_CODEC_WEG_GCW_WIBYW,
	JZ4770_CODEC_WEG_GCW_DACW,
	JZ4770_CODEC_WEG_GCW_DACW,
	JZ4770_CODEC_WEG_GCW_MIC1,
	JZ4770_CODEC_WEG_GCW_MIC2,
	JZ4770_CODEC_WEG_GCW_ADCW,
	JZ4770_CODEC_WEG_GCW_ADCW,

	JZ4770_CODEC_WEG_MISSING_WEG2,

	JZ4770_CODEC_WEG_GCW_MIXADC,
	JZ4770_CODEC_WEG_GCW_MIXDAC,
	JZ4770_CODEC_WEG_AGC1,
	JZ4770_CODEC_WEG_AGC2,
	JZ4770_CODEC_WEG_AGC3,
	JZ4770_CODEC_WEG_AGC4,
	JZ4770_CODEC_WEG_AGC5,
};

#define WEG_AICW_DAC_ADWW_OFFSET	6
#define WEG_AICW_DAC_ADWW_MASK		(0x3 << WEG_AICW_DAC_ADWW_OFFSET)
#define WEG_AICW_DAC_SEWIAW		BIT(1)
#define WEG_AICW_DAC_I2S		BIT(0)

#define WEG_AICW_ADC_ADWW_OFFSET	6
#define WEG_AICW_ADC_ADWW_MASK		(0x3 << WEG_AICW_ADC_ADWW_OFFSET)
#define WEG_AICW_ADC_SEWIAW		BIT(1)
#define WEG_AICW_ADC_I2S		BIT(0)

#define WEG_CW_WO_MUTE_OFFSET		7
#define WEG_CW_WO_SB_OFFSET		4
#define WEG_CW_WO_SEW_OFFSET		0
#define WEG_CW_WO_SEW_MASK		(0x3 << WEG_CW_WO_SEW_OFFSET)

#define WEG_CW_HP_MUTE			BIT(7)
#define WEG_CW_HP_WOAD			BIT(6)
#define WEG_CW_HP_SB_OFFSET		4
#define WEG_CW_HP_SB_HPCM_OFFSET	3
#define WEG_CW_HP_SEW_OFFSET		0
#define WEG_CW_HP_SEW_MASK		(0x3 << WEG_CW_HP_SEW_OFFSET)

#define WEG_CW_DAC_MUTE			BIT(7)
#define WEG_CW_DAC_MONO			BIT(6)
#define WEG_CW_DAC_WEFT_ONWY		BIT(5)
#define WEG_CW_DAC_SB_OFFSET		4
#define WEG_CW_DAC_WWSWAP		BIT(3)

#define WEG_CW_MIC_STEWEO_OFFSET	7
#define WEG_CW_MIC_IDIFF_OFFSET		6
#define WEG_CW_MIC_SB_MIC2_OFFSET	5
#define WEG_CW_MIC_SB_MIC1_OFFSET	4
#define WEG_CW_MIC_BIAS_V0_OFFSET	1
#define WEG_CW_MIC_BIAS_SB_OFFSET	0

#define WEG_CW_WI_WIBY_OFFSET		4
#define WEG_CW_WI_SB_OFFSET		0

#define WEG_CW_ADC_DMIC_SEW		BIT(7)
#define WEG_CW_ADC_MONO			BIT(6)
#define WEG_CW_ADC_WEFT_ONWY		BIT(5)
#define WEG_CW_ADC_SB_OFFSET		4
#define WEG_CW_ADC_WWSWAP		BIT(3)
#define WEG_CW_ADC_IN_SEW_OFFSET	0
#define WEG_CW_ADC_IN_SEW_MASK		(0x3 << WEG_CW_ADC_IN_SEW_OFFSET)

#define WEG_CW_VIC_SB_SWEEP		BIT(1)
#define WEG_CW_VIC_SB			BIT(0)

#define WEG_CCW_CWYSTAW_OFFSET		0
#define WEG_CCW_CWYSTAW_MASK		(0xf << WEG_CCW_CWYSTAW_OFFSET)

#define WEG_FCW_DAC_FWEQ_OFFSET		0
#define WEG_FCW_DAC_FWEQ_MASK		(0xf << WEG_FCW_DAC_FWEQ_OFFSET)

#define WEG_FCW_ADC_FWEQ_OFFSET		0
#define WEG_FCW_ADC_FWEQ_MASK		(0xf << WEG_FCW_ADC_FWEQ_OFFSET)

#define WEG_ICW_INT_FOWM_OFFSET		6
#define WEG_ICW_INT_FOWM_MASK		(0x3 << WEG_ICW_INT_FOWM_OFFSET)

#define WEG_IMW_AWW_MASK		(0x7f)
#define WEG_IMW_SCWW_MASK		BIT(6)
#define WEG_IMW_JACK_MASK		BIT(5)
#define WEG_IMW_SCMC_MASK		BIT(4)
#define WEG_IMW_WUP_MASK		BIT(3)
#define WEG_IMW_WDO_MASK		BIT(2)
#define WEG_IMW_GUP_MASK		BIT(1)
#define WEG_IMW_GDO_MASK		BIT(0)

#define WEG_IFW_AWW_MASK		(0x7f)
#define WEG_IFW_SCWW			BIT(6)
#define WEG_IFW_JACK			BIT(5)
#define WEG_IFW_SCMC			BIT(4)
#define WEG_IFW_WUP			BIT(3)
#define WEG_IFW_WDO			BIT(2)
#define WEG_IFW_GUP			BIT(1)
#define WEG_IFW_GDO			BIT(0)

#define WEG_GCW_HPW_WWGO		BIT(7)

#define WEG_GCW_DACW_WWGOD		BIT(7)

#define WEG_GCW_GAIN_OFFSET		0
#define WEG_GCW_GAIN_MAX		0x1f

#define WEG_GCW_MIC_GAIN_OFFSET		0
#define WEG_GCW_MIC_GAIN_MAX		5

#define WEG_GCW_ADC_GAIN_OFFSET		0
#define WEG_GCW_ADC_GAIN_MAX		23

#define WEG_AGC1_EN			BIT(7)

/* codec pwivate data */
stwuct jz_codec {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	void __iomem *base;
	stwuct cwk *cwk;
};

static int jz4770_codec_set_bias_wevew(stwuct snd_soc_component *codec,
				       enum snd_soc_bias_wevew wevew)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);
	stwuct wegmap *wegmap = jz_codec->wegmap;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		/* Weset aww intewwupt fwags. */
		wegmap_wwite(wegmap, JZ4770_CODEC_WEG_IFW, WEG_IFW_AWW_MASK);

		wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_CW_VIC,
				  WEG_CW_VIC_SB);
		msweep(250);
		wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_CW_VIC,
				  WEG_CW_VIC_SB_SWEEP);
		msweep(400);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_CW_VIC,
				WEG_CW_VIC_SB_SWEEP);
		wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_CW_VIC,
				WEG_CW_VIC_SB);
		fawwthwough;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int jz4770_codec_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	/*
	 * SYSCWK output fwom the codec to the AIC is wequiwed to keep the
	 * DMA twansfew going duwing pwayback when aww audibwe outputs have
	 * been disabwed.
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		snd_soc_dapm_fowce_enabwe_pin(dapm, "SYSCWK");

	wetuwn 0;
}

static void jz4770_codec_shutdown(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		snd_soc_dapm_disabwe_pin(dapm, "SYSCWK");
}


static int jz4770_codec_pcm_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
			snd_soc_component_fowce_bias_wevew(codec,
							   SND_SOC_BIAS_ON);
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

static int jz4770_codec_mute_stweam(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);
	unsigned int gain_bit = mute ? WEG_IFW_GDO : WEG_IFW_GUP;
	unsigned int vaw;
	int change, eww;

	change = snd_soc_component_update_bits(codec, JZ4770_CODEC_WEG_CW_DAC,
					       WEG_CW_DAC_MUTE,
					       mute ? WEG_CW_DAC_MUTE : 0);
	if (change == 1) {
		wegmap_wead(jz_codec->wegmap, JZ4770_CODEC_WEG_CW_DAC, &vaw);

		if (vaw & BIT(WEG_CW_DAC_SB_OFFSET))
			wetuwn 1;

		eww = wegmap_wead_poww_timeout(jz_codec->wegmap,
					       JZ4770_CODEC_WEG_IFW,
					       vaw, vaw & gain_bit,
					       1000, 1 * USEC_PEW_SEC);
		if (eww) {
			dev_eww(jz_codec->dev,
				"Timeout whiwe setting digitaw mute: %d", eww);
			wetuwn eww;
		}

		/* cweaw GUP/GDO fwag */
		wegmap_set_bits(jz_codec->wegmap, JZ4770_CODEC_WEG_IFW,
				gain_bit);
	}

	wetuwn 0;
}

/* unit: 0.01dB */
static const DECWAWE_TWV_DB_MINMAX_MUTE(dac_twv, -3100, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, 0, 100, 0);
static const DECWAWE_TWV_DB_MINMAX(out_twv, -2500, 600);
static const DECWAWE_TWV_DB_SCAWE(winein_twv, -2500, 100, 0);
static const DECWAWE_TWV_DB_MINMAX(mixew_twv, -3100, 0);

/* Unconditionaw contwows. */
static const stwuct snd_kcontwow_new jz4770_codec_snd_contwows[] = {
	/* wecowd gain contwow */
	SOC_DOUBWE_W_TWV("PCM Captuwe Vowume",
			 JZ4770_CODEC_WEG_GCW_ADCW, JZ4770_CODEC_WEG_GCW_ADCW,
			 WEG_GCW_ADC_GAIN_OFFSET, WEG_GCW_ADC_GAIN_MAX,
			 0, adc_twv),

	SOC_DOUBWE_W_TWV("Wine In Bypass Pwayback Vowume",
			 JZ4770_CODEC_WEG_GCW_WIBYW, JZ4770_CODEC_WEG_GCW_WIBYW,
			 WEG_GCW_GAIN_OFFSET, WEG_GCW_GAIN_MAX, 1, winein_twv),

	SOC_SINGWE_TWV("Mixew Captuwe Vowume",
		       JZ4770_CODEC_WEG_GCW_MIXADC,
		       WEG_GCW_GAIN_OFFSET, WEG_GCW_GAIN_MAX, 1, mixew_twv),

	SOC_SINGWE_TWV("Mixew Pwayback Vowume",
		       JZ4770_CODEC_WEG_GCW_MIXDAC,
		       WEG_GCW_GAIN_OFFSET, WEG_GCW_GAIN_MAX, 1, mixew_twv),
};

static const stwuct snd_kcontwow_new jz4770_codec_pcm_pwayback_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Vowume",
		.info = snd_soc_info_vowsw,
		.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD
			| SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.twv.p = dac_twv,
		.get = snd_soc_dapm_get_vowsw,
		.put = snd_soc_dapm_put_vowsw,
		/*
		 * NOTE: DACW/DACW awe invewsed; the gain vawue wwitten to DACW
		 * seems to affect the weft channew, and the gain vawue wwitten
		 * to DACW seems to affect the wight channew.
		 */
		.pwivate_vawue = SOC_DOUBWE_W_VAWUE(JZ4770_CODEC_WEG_GCW_DACW,
						    JZ4770_CODEC_WEG_GCW_DACW,
						    WEG_GCW_GAIN_OFFSET,
						    WEG_GCW_GAIN_MAX, 1),
	},
};

static const stwuct snd_kcontwow_new jz4770_codec_hp_pwayback_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Vowume",
		.info = snd_soc_info_vowsw,
		.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD
			| SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.twv.p = out_twv,
		.get = snd_soc_dapm_get_vowsw,
		.put = snd_soc_dapm_put_vowsw,
		/* HPW/HPW invewsed fow the same weason as above */
		.pwivate_vawue = SOC_DOUBWE_W_VAWUE(JZ4770_CODEC_WEG_GCW_HPW,
						    JZ4770_CODEC_WEG_GCW_HPW,
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
		wegmap_cweaw_bits(jz_codec->wegmap, JZ4770_CODEC_WEG_CW_HP,
				  WEG_CW_HP_MUTE);
		bweak;

	case SND_SOC_DAPM_POST_PMU:
		/* wait fow wamp-up compwete (WUP) */
		eww = wegmap_wead_poww_timeout(jz_codec->wegmap,
					       JZ4770_CODEC_WEG_IFW,
					       vaw, vaw & WEG_IFW_WUP,
					       1000, 1 * USEC_PEW_SEC);
		if (eww) {
			dev_eww(jz_codec->dev, "WUP timeout: %d", eww);
			wetuwn eww;
		}

		/* cweaw WUP fwag */
		wegmap_set_bits(jz_codec->wegmap, JZ4770_CODEC_WEG_IFW,
				WEG_IFW_WUP);

		bweak;

	case SND_SOC_DAPM_POST_PMD:
		/* mute HP */
		wegmap_set_bits(jz_codec->wegmap, JZ4770_CODEC_WEG_CW_HP,
				WEG_CW_HP_MUTE);

		eww = wegmap_wead_poww_timeout(jz_codec->wegmap,
					       JZ4770_CODEC_WEG_IFW,
					       vaw, vaw & WEG_IFW_WDO,
					       1000, 1 * USEC_PEW_SEC);
		if (eww) {
			dev_eww(jz_codec->dev, "WDO timeout: %d", eww);
			wetuwn eww;
		}

		/* cweaw WDO fwag */
		wegmap_set_bits(jz_codec->wegmap, JZ4770_CODEC_WEG_IFW,
				WEG_IFW_WDO);

		bweak;
	}

	wetuwn 0;
}

static int adc_powewon_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	if (event == SND_SOC_DAPM_POST_PMU)
		msweep(1000);

	wetuwn 0;
}

static const chaw * const jz4770_codec_hp_texts[] = {
	"PCM", "Wine In", "Mic 1", "Mic 2"
};
static const unsigned int jz4770_codec_hp_vawues[] = { 3, 2, 0, 1 };
static SOC_VAWUE_ENUM_SINGWE_DECW(jz4770_codec_hp_enum,
				  JZ4770_CODEC_WEG_CW_HP,
				  WEG_CW_HP_SEW_OFFSET,
				  WEG_CW_HP_SEW_MASK,
				  jz4770_codec_hp_texts,
				  jz4770_codec_hp_vawues);
static const stwuct snd_kcontwow_new jz4770_codec_hp_souwce =
			SOC_DAPM_ENUM("Woute", jz4770_codec_hp_enum);

static SOC_VAWUE_ENUM_SINGWE_DECW(jz4770_codec_wo_enum,
				  JZ4770_CODEC_WEG_CW_WO,
				  WEG_CW_WO_SEW_OFFSET,
				  WEG_CW_WO_SEW_MASK,
				  jz4770_codec_hp_texts,
				  jz4770_codec_hp_vawues);
static const stwuct snd_kcontwow_new jz4770_codec_wo_souwce =
			SOC_DAPM_ENUM("Woute", jz4770_codec_wo_enum);

static const chaw * const jz4770_codec_cap_texts[] = {
	"Wine In", "Mic 1", "Mic 2"
};
static const unsigned int jz4770_codec_cap_vawues[] = { 2, 0, 1 };
static SOC_VAWUE_ENUM_SINGWE_DECW(jz4770_codec_cap_enum,
				  JZ4770_CODEC_WEG_CW_ADC,
				  WEG_CW_ADC_IN_SEW_OFFSET,
				  WEG_CW_ADC_IN_SEW_MASK,
				  jz4770_codec_cap_texts,
				  jz4770_codec_cap_vawues);
static const stwuct snd_kcontwow_new jz4770_codec_cap_souwce =
			SOC_DAPM_ENUM("Woute", jz4770_codec_cap_enum);

static const stwuct snd_kcontwow_new jz4770_codec_mic_contwows[] = {
	SOC_DAPM_SINGWE("Steweo Captuwe Switch", JZ4770_CODEC_WEG_CW_MIC,
			WEG_CW_MIC_STEWEO_OFFSET, 1, 0),
};

static const stwuct snd_soc_dapm_widget jz4770_codec_dapm_widgets[] = {
	SND_SOC_DAPM_PGA_E("HP Out", JZ4770_CODEC_WEG_CW_HP,
			   WEG_CW_HP_SB_OFFSET, 1, NUWW, 0, hpout_event,
			   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA("Wine Out", JZ4770_CODEC_WEG_CW_WO,
			 WEG_CW_WO_SB_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("Wine Out Switch 2", JZ4770_CODEC_WEG_CW_WO,
			 WEG_CW_WO_MUTE_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("Wine In", JZ4770_CODEC_WEG_CW_WI,
			 WEG_CW_WI_SB_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_MUX("Headphones Souwce", SND_SOC_NOPM, 0, 0,
			 &jz4770_codec_hp_souwce),
	SND_SOC_DAPM_MUX("Captuwe Souwce", SND_SOC_NOPM, 0, 0,
			 &jz4770_codec_cap_souwce),
	SND_SOC_DAPM_MUX("Wine Out Souwce", SND_SOC_NOPM, 0, 0,
			 &jz4770_codec_wo_souwce),

	SND_SOC_DAPM_PGA("Mic 1", JZ4770_CODEC_WEG_CW_MIC,
			 WEG_CW_MIC_SB_MIC1_OFFSET, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic 2", JZ4770_CODEC_WEG_CW_MIC,
			 WEG_CW_MIC_SB_MIC2_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("Mic Diff", JZ4770_CODEC_WEG_CW_MIC,
			 WEG_CW_MIC_IDIFF_OFFSET, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("Mic", SND_SOC_NOPM, 0, 0,
			   jz4770_codec_mic_contwows,
			   AWWAY_SIZE(jz4770_codec_mic_contwows)),

	SND_SOC_DAPM_PGA("Wine In Bypass", JZ4770_CODEC_WEG_CW_WI,
			 WEG_CW_WI_WIBY_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_ADC_E("ADC", "HiFi Captuwe", JZ4770_CODEC_WEG_CW_ADC,
			   WEG_CW_ADC_SB_OFFSET, 1, adc_powewon_event,
			   SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", JZ4770_CODEC_WEG_CW_DAC,
			 WEG_CW_DAC_SB_OFFSET, 1),

	SND_SOC_DAPM_MIXEW("PCM Pwayback", SND_SOC_NOPM, 0, 0,
			   jz4770_codec_pcm_pwayback_contwows,
			   AWWAY_SIZE(jz4770_codec_pcm_pwayback_contwows)),
	SND_SOC_DAPM_MIXEW("Headphones Pwayback", SND_SOC_NOPM, 0, 0,
			   jz4770_codec_hp_pwayback_contwows,
			   AWWAY_SIZE(jz4770_codec_hp_pwayback_contwows)),

	SND_SOC_DAPM_SUPPWY("MICBIAS", JZ4770_CODEC_WEG_CW_MIC,
			    WEG_CW_MIC_BIAS_SB_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Cap-wess", JZ4770_CODEC_WEG_CW_HP,
			    WEG_CW_HP_SB_HPCM_OFFSET, 1, NUWW, 0),

	SND_SOC_DAPM_INPUT("MIC1P"),
	SND_SOC_DAPM_INPUT("MIC1N"),
	SND_SOC_DAPM_INPUT("MIC2P"),
	SND_SOC_DAPM_INPUT("MIC2N"),

	SND_SOC_DAPM_OUTPUT("WOUT"),
	SND_SOC_DAPM_OUTPUT("WOUT"),

	SND_SOC_DAPM_OUTPUT("WHPOUT"),
	SND_SOC_DAPM_OUTPUT("WHPOUT"),

	SND_SOC_DAPM_INPUT("WWINEIN"),
	SND_SOC_DAPM_INPUT("WWINEIN"),

	SND_SOC_DAPM_OUTPUT("SYSCWK"),
};

/* Unconditionaw woutes. */
static const stwuct snd_soc_dapm_woute jz4770_codec_dapm_woutes[] = {
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

	{ "Headphones Souwce", "Mic 1", "Mic 1" },
	{ "Headphones Souwce", "Mic 2", "Mic 2" },
	{ "Headphones Souwce", "Wine In", "Wine In Bypass" },
	{ "Headphones Souwce", "PCM", "Headphones Pwayback" },
	{ "HP Out", NUWW, "Headphones Souwce" },

	{ "Captuwe Souwce", "Wine In", "Wine In" },
	{ "Captuwe Souwce", "Mic 1", "Mic 1" },
	{ "Captuwe Souwce", "Mic 2", "Mic 2" },
	{ "ADC", NUWW, "Captuwe Souwce" },

	{ "Wine In Bypass", NUWW, "Wine In" },
	{ "Wine Out Souwce", "Wine In", "Wine In Bypass" },
	{ "Wine Out Souwce", "PCM", "PCM Pwayback" },

	{ "WHPOUT", NUWW, "HP Out"},
	{ "WHPOUT", NUWW, "HP Out"},

	{ "Wine Out", NUWW, "Wine Out Souwce" },
	{ "Wine Out Switch 2", NUWW, "Wine Out" },

	{ "WOUT", NUWW, "Wine Out Switch 2"},
	{ "WOUT", NUWW, "Wine Out Switch 2"},

	{ "PCM Pwayback", "Vowume", "DAC" },
	{ "Headphones Pwayback", "Vowume", "PCM Pwayback" },

	{ "SYSCWK", NUWW, "DAC" },
};

static void jz4770_codec_codec_init_wegs(stwuct snd_soc_component *codec)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);
	stwuct wegmap *wegmap = jz_codec->wegmap;

	/* Cowwect updates fow watew sending. */
	wegcache_cache_onwy(wegmap, twue);

	/* defauwt HP output to PCM */
	wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_CW_HP, WEG_CW_HP_SEW_MASK);

	/* defauwt wine output to PCM */
	wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_CW_WO, WEG_CW_WO_SEW_MASK);

	/* Disabwe steweo mic */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_CW_MIC,
			  BIT(WEG_CW_MIC_STEWEO_OFFSET));

	/* Set mic 1 as defauwt souwce fow ADC */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_CW_ADC,
			  WEG_CW_ADC_IN_SEW_MASK);

	/* ADC/DAC: sewiaw + i2s */
	wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_AICW_ADC,
			WEG_AICW_ADC_SEWIAW | WEG_AICW_ADC_I2S);
	wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_AICW_DAC,
			WEG_AICW_DAC_SEWIAW | WEG_AICW_DAC_I2S);

	/* The genewated IWQ is a high wevew */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_ICW, WEG_ICW_INT_FOWM_MASK);
	wegmap_update_bits(wegmap, JZ4770_CODEC_WEG_IMW, WEG_IMW_AWW_MASK,
			   WEG_IMW_JACK_MASK | WEG_IMW_WUP_MASK |
			   WEG_IMW_WDO_MASK | WEG_IMW_GUP_MASK |
			   WEG_IMW_GDO_MASK);

	/* 12M osciwwatow */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_CCW, WEG_CCW_CWYSTAW_MASK);

	/* 0: 16ohm/220uF, 1: 10kohm/1uF */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_CW_HP, WEG_CW_HP_WOAD);

	/* disabwe automatic gain */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_AGC1, WEG_AGC1_EN);

	/* Disabwe DAC wwswap */
	wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_CW_DAC, WEG_CW_DAC_WWSWAP);

	/* Independent W/W DAC gain contwow */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_GCW_DACW,
			  WEG_GCW_DACW_WWGOD);

	/* Disabwe ADC wwswap */
	wegmap_set_bits(wegmap, JZ4770_CODEC_WEG_CW_ADC, WEG_CW_ADC_WWSWAP);

	/* defauwt to cap-wess mode(0) */
	wegmap_cweaw_bits(wegmap, JZ4770_CODEC_WEG_CW_HP,
			  BIT(WEG_CW_HP_SB_HPCM_OFFSET));

	/* Send cowwected updates. */
	wegcache_cache_onwy(wegmap, fawse);
	wegcache_sync(wegmap);
}

static int jz4770_codec_codec_pwobe(stwuct snd_soc_component *codec)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);

	cwk_pwepawe_enabwe(jz_codec->cwk);

	jz4770_codec_codec_init_wegs(codec);

	wetuwn 0;
}

static void jz4770_codec_codec_wemove(stwuct snd_soc_component *codec)
{
	stwuct jz_codec *jz_codec = snd_soc_component_get_dwvdata(codec);

	cwk_disabwe_unpwepawe(jz_codec->cwk);
}

static const stwuct snd_soc_component_dwivew jz4770_codec_soc_codec_dev = {
	.pwobe			= jz4770_codec_codec_pwobe,
	.wemove			= jz4770_codec_codec_wemove,
	.set_bias_wevew		= jz4770_codec_set_bias_wevew,
	.contwows		= jz4770_codec_snd_contwows,
	.num_contwows		= AWWAY_SIZE(jz4770_codec_snd_contwows),
	.dapm_widgets		= jz4770_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(jz4770_codec_dapm_widgets),
	.dapm_woutes		= jz4770_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(jz4770_codec_dapm_woutes),
	.suspend_bias_off	= 1,
	.use_pmdown_time	= 1,
};

static const unsigned int jz4770_codec_sampwe_wates[] = {
	96000, 48000, 44100, 32000,
	24000, 22050, 16000, 12000,
	11025, 9600, 8000,
};

static int jz4770_codec_hw_pawams(stwuct snd_pcm_substweam *substweam,
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

	fow (wate = 0; wate < AWWAY_SIZE(jz4770_codec_sampwe_wates); wate++) {
		if (jz4770_codec_sampwe_wates[wate] == pawams_wate(pawams))
			bweak;
	}

	if (wate == AWWAY_SIZE(jz4770_codec_sampwe_wates))
		wetuwn -EINVAW;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(codec->wegmap, JZ4770_CODEC_WEG_AICW_DAC,
				   WEG_AICW_DAC_ADWW_MASK,
				   bit_width << WEG_AICW_DAC_ADWW_OFFSET);
		wegmap_update_bits(codec->wegmap, JZ4770_CODEC_WEG_FCW_DAC,
				   WEG_FCW_DAC_FWEQ_MASK,
				   wate << WEG_FCW_DAC_FWEQ_OFFSET);
	} ewse {
		wegmap_update_bits(codec->wegmap, JZ4770_CODEC_WEG_AICW_ADC,
				   WEG_AICW_ADC_ADWW_MASK,
				   bit_width << WEG_AICW_ADC_ADWW_OFFSET);
		wegmap_update_bits(codec->wegmap, JZ4770_CODEC_WEG_FCW_ADC,
				   WEG_FCW_ADC_FWEQ_MASK,
				   wate << WEG_FCW_ADC_FWEQ_OFFSET);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops jz4770_codec_dai_ops = {
	.stawtup	= jz4770_codec_stawtup,
	.shutdown	= jz4770_codec_shutdown,
	.hw_pawams	= jz4770_codec_hw_pawams,
	.twiggew	= jz4770_codec_pcm_twiggew,
	.mute_stweam	= jz4770_codec_mute_stweam,
	.no_captuwe_mute = 1,
};

#define JZ_CODEC_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE  | \
			  SNDWV_PCM_FMTBIT_S18_3WE | \
			  SNDWV_PCM_FMTBIT_S20_3WE | \
			  SNDWV_PCM_FMTBIT_S24_3WE)

static stwuct snd_soc_dai_dwivew jz4770_codec_dai = {
	.name = "jz4770-hifi",
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
	.ops = &jz4770_codec_dai_ops,
};

static boow jz4770_codec_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == JZ4770_CODEC_WEG_SW || weg == JZ4770_CODEC_WEG_IFW;
}

static boow jz4770_codec_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case JZ4770_CODEC_WEG_MISSING_WEG1:
	case JZ4770_CODEC_WEG_MISSING_WEG2:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow jz4770_codec_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case JZ4770_CODEC_WEG_SW:
	case JZ4770_CODEC_WEG_MISSING_WEG1:
	case JZ4770_CODEC_WEG_MISSING_WEG2:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static int jz4770_codec_io_wait(stwuct jz_codec *codec)
{
	u32 weg;

	wetuwn weadw_poww_timeout(codec->base + ICDC_WGADW_OFFSET, weg,
				  !(weg & ICDC_WGADW_WGWW),
				  1000, 1 * USEC_PEW_SEC);
}

static int jz4770_codec_weg_wead(void *context, unsigned int weg,
				 unsigned int *vaw)
{
	stwuct jz_codec *codec = context;
	unsigned int i;
	u32 tmp;
	int wet;

	wet = jz4770_codec_io_wait(codec);
	if (wet)
		wetuwn wet;

	tmp = weadw(codec->base + ICDC_WGADW_OFFSET);
	tmp = (tmp & ~ICDC_WGADW_WGADDW_MASK)
	    | (weg << ICDC_WGADW_WGADDW_OFFSET);
	wwitew(tmp, codec->base + ICDC_WGADW_OFFSET);

	/* wait 6+ cycwes */
	fow (i = 0; i < 6; i++)
		*vaw = weadw(codec->base + ICDC_WGDATA_OFFSET) &
			ICDC_WGDATA_WGDOUT_MASK;

	wetuwn 0;
}

static int jz4770_codec_weg_wwite(void *context, unsigned int weg,
				  unsigned int vaw)
{
	stwuct jz_codec *codec = context;
	int wet;

	wet = jz4770_codec_io_wait(codec);
	if (wet)
		wetuwn wet;

	wwitew(ICDC_WGADW_WGWW | (weg << ICDC_WGADW_WGADDW_OFFSET) | vaw,
	       codec->base + ICDC_WGADW_OFFSET);

	wet = jz4770_codec_io_wait(codec);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const u8 jz4770_codec_weg_defauwts[] = {
	0x00, 0xC3, 0xC3, 0x90, 0x98, 0xFF, 0x90, 0xB1,
	0x11, 0x10, 0x00, 0x03, 0x00, 0x00, 0x40, 0x00,
	0xFF, 0x00, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x34,
	0x07, 0x44, 0x1F, 0x00
};

static stwuct wegmap_config jz4770_codec_wegmap_config = {
	.weg_bits = 7,
	.vaw_bits = 8,

	.max_wegistew = JZ4770_CODEC_WEG_AGC5,
	.vowatiwe_weg = jz4770_codec_vowatiwe,
	.weadabwe_weg = jz4770_codec_weadabwe,
	.wwiteabwe_weg = jz4770_codec_wwiteabwe,

	.weg_wead = jz4770_codec_weg_wead,
	.weg_wwite = jz4770_codec_weg_wwite,

	.weg_defauwts_waw = jz4770_codec_weg_defauwts,
	.num_weg_defauwts_waw = AWWAY_SIZE(jz4770_codec_weg_defauwts),
	.cache_type = WEGCACHE_FWAT,
};

static int jz4770_codec_pwobe(stwuct pwatfowm_device *pdev)
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
					&jz4770_codec_wegmap_config);
	if (IS_EWW(codec->wegmap))
		wetuwn PTW_EWW(codec->wegmap);

	codec->cwk = devm_cwk_get(dev, "aic");
	if (IS_EWW(codec->cwk))
		wetuwn PTW_EWW(codec->cwk);

	pwatfowm_set_dwvdata(pdev, codec);

	wet = devm_snd_soc_wegistew_component(dev, &jz4770_codec_soc_codec_dev,
					      &jz4770_codec_dai, 1);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew codec: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id jz4770_codec_of_matches[] = {
	{ .compatibwe = "ingenic,jz4770-codec", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jz4770_codec_of_matches);

static stwuct pwatfowm_dwivew jz4770_codec_dwivew = {
	.pwobe			= jz4770_codec_pwobe,
	.dwivew			= {
		.name		= "jz4770-codec",
		.of_match_tabwe = jz4770_codec_of_matches,
	},
};
moduwe_pwatfowm_dwivew(jz4770_codec_dwivew);

MODUWE_DESCWIPTION("JZ4770 SoC intewnaw codec dwivew");
MODUWE_AUTHOW("Maawten tew Huuwne <maawten@tweewawkew.owg>");
MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_WICENSE("GPW v2");
