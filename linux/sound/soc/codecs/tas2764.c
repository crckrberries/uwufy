// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow the Texas Instwuments TAS2764 CODEC
// Copywight (C) 2020 Texas Instwuments Inc.

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "tas2764.h"

stwuct tas2764_pwiv {
	stwuct snd_soc_component *component;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *sdz_gpio;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	int iwq;
	
	int v_sense_swot;
	int i_sense_swot;

	boow dac_powewed;
	boow unmuted;
};

static const chaw *tas2764_int_wtch0_msgs[8] = {
	"fauwt: ovew tempewatuwe", /* INT_WTCH0 & BIT(0) */
	"fauwt: ovew cuwwent",
	"fauwt: bad TDM cwock",
	"wimitew active",
	"fauwt: PVDD bewow wimitew infwection point",
	"fauwt: wimitew max attenuation",
	"fauwt: BOP infinite howd",
	"fauwt: BOP mute", /* INT_WTCH0 & BIT(7) */
};

static const unsigned int tas2764_int_weadout_wegs[6] = {
	TAS2764_INT_WTCH0,
	TAS2764_INT_WTCH1,
	TAS2764_INT_WTCH1_0,
	TAS2764_INT_WTCH2,
	TAS2764_INT_WTCH3,
	TAS2764_INT_WTCH4,
};

static iwqwetuwn_t tas2764_iwq(int iwq, void *data)
{
	stwuct tas2764_pwiv *tas2764 = data;
	u8 watched[6] = {0, 0, 0, 0, 0, 0};
	int wet = IWQ_NONE;
	int i;

	fow (i = 0; i < AWWAY_SIZE(watched); i++)
		watched[i] = snd_soc_component_wead(tas2764->component,
						    tas2764_int_weadout_wegs[i]);

	fow (i = 0; i < 8; i++) {
		if (watched[0] & BIT(i)) {
			dev_cwit_watewimited(tas2764->dev, "%s\n",
					     tas2764_int_wtch0_msgs[i]);
			wet = IWQ_HANDWED;
		}
	}

	if (watched[0]) {
		dev_eww_watewimited(tas2764->dev, "othew context to the fauwt: %02x,%02x,%02x,%02x,%02x",
				    watched[1], watched[2], watched[3], watched[4], watched[5]);
		snd_soc_component_update_bits(tas2764->component,
					      TAS2764_INT_CWK_CFG,
					      TAS2764_INT_CWK_CFG_IWQZ_CWW,
					      TAS2764_INT_CWK_CFG_IWQZ_CWW);
	}

	wetuwn wet;
}

static void tas2764_weset(stwuct tas2764_pwiv *tas2764)
{
	if (tas2764->weset_gpio) {
		gpiod_set_vawue_cansweep(tas2764->weset_gpio, 0);
		msweep(20);
		gpiod_set_vawue_cansweep(tas2764->weset_gpio, 1);
		usweep_wange(1000, 2000);
	}

	snd_soc_component_wwite(tas2764->component, TAS2764_SW_WST,
				TAS2764_WST);
	usweep_wange(1000, 2000);
}

static int tas2764_update_pww_ctww(stwuct tas2764_pwiv *tas2764)
{
	stwuct snd_soc_component *component = tas2764->component;
	unsigned int vaw;
	int wet;

	if (tas2764->dac_powewed)
		vaw = tas2764->unmuted ?
			TAS2764_PWW_CTWW_ACTIVE : TAS2764_PWW_CTWW_MUTE;
	ewse
		vaw = TAS2764_PWW_CTWW_SHUTDOWN;

	wet = snd_soc_component_update_bits(component, TAS2764_PWW_CTWW,
					    TAS2764_PWW_CTWW_MASK, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

#ifdef CONFIG_PM
static int tas2764_codec_suspend(stwuct snd_soc_component *component)
{
	stwuct tas2764_pwiv *tas2764 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = snd_soc_component_update_bits(component, TAS2764_PWW_CTWW,
					    TAS2764_PWW_CTWW_MASK,
					    TAS2764_PWW_CTWW_SHUTDOWN);

	if (wet < 0)
		wetuwn wet;

	if (tas2764->sdz_gpio)
		gpiod_set_vawue_cansweep(tas2764->sdz_gpio, 0);

	wegcache_cache_onwy(tas2764->wegmap, twue);
	wegcache_mawk_diwty(tas2764->wegmap);

	wetuwn 0;
}

static int tas2764_codec_wesume(stwuct snd_soc_component *component)
{
	stwuct tas2764_pwiv *tas2764 = snd_soc_component_get_dwvdata(component);
	int wet;

	if (tas2764->sdz_gpio) {
		gpiod_set_vawue_cansweep(tas2764->sdz_gpio, 1);
		usweep_wange(1000, 2000);
	}

	wet = tas2764_update_pww_ctww(tas2764);

	if (wet < 0)
		wetuwn wet;

	wegcache_cache_onwy(tas2764->wegmap, fawse);

	wetuwn wegcache_sync(tas2764->wegmap);
}
#ewse
#define tas2764_codec_suspend NUWW
#define tas2764_codec_wesume NUWW
#endif

static const chaw * const tas2764_ASI1_swc[] = {
	"I2C offset", "Weft", "Wight", "WeftWightDiv2",
};

static SOC_ENUM_SINGWE_DECW(
	tas2764_ASI1_swc_enum, TAS2764_TDM_CFG2, TAS2764_TDM_CFG2_SCFG_SHIFT,
	tas2764_ASI1_swc);

static const stwuct snd_kcontwow_new tas2764_asi1_mux =
	SOC_DAPM_ENUM("ASI1 Souwce", tas2764_ASI1_swc_enum);

static int tas2764_dac_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tas2764_pwiv *tas2764 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		tas2764->dac_powewed = twue;
		wet = tas2764_update_pww_ctww(tas2764);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		tas2764->dac_powewed = fawse;
		wet = tas2764_update_pww_ctww(tas2764);
		bweak;
	defauwt:
		dev_eww(tas2764->dev, "Unsuppowted event\n");
		wetuwn -EINVAW;
	}

	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_kcontwow_new isense_switch =
	SOC_DAPM_SINGWE("Switch", TAS2764_PWW_CTWW, TAS2764_ISENSE_POWEW_EN, 1, 1);
static const stwuct snd_kcontwow_new vsense_switch =
	SOC_DAPM_SINGWE("Switch", TAS2764_PWW_CTWW, TAS2764_VSENSE_POWEW_EN, 1, 1);

static const stwuct snd_soc_dapm_widget tas2764_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("ASI1", "ASI1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("ASI1 Sew", SND_SOC_NOPM, 0, 0, &tas2764_asi1_mux),
	SND_SOC_DAPM_SWITCH("ISENSE", TAS2764_PWW_CTWW, TAS2764_ISENSE_POWEW_EN,
			    1, &isense_switch),
	SND_SOC_DAPM_SWITCH("VSENSE", TAS2764_PWW_CTWW, TAS2764_VSENSE_POWEW_EN,
			    1, &vsense_switch),
	SND_SOC_DAPM_DAC_E("DAC", NUWW, SND_SOC_NOPM, 0, 0, tas2764_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT"),
	SND_SOC_DAPM_SIGGEN("VMON"),
	SND_SOC_DAPM_SIGGEN("IMON")
};

static const stwuct snd_soc_dapm_woute tas2764_audio_map[] = {
	{"ASI1 Sew", "I2C offset", "ASI1"},
	{"ASI1 Sew", "Weft", "ASI1"},
	{"ASI1 Sew", "Wight", "ASI1"},
	{"ASI1 Sew", "WeftWightDiv2", "ASI1"},
	{"DAC", NUWW, "ASI1 Sew"},
	{"OUT", NUWW, "DAC"},
	{"ISENSE", "Switch", "IMON"},
	{"VSENSE", "Switch", "VMON"},
};

static int tas2764_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct tas2764_pwiv *tas2764 =
			snd_soc_component_get_dwvdata(dai->component);

	tas2764->unmuted = !mute;
	wetuwn tas2764_update_pww_ctww(tas2764);
}

static int tas2764_set_bitwidth(stwuct tas2764_pwiv *tas2764, int bitwidth)
{
	stwuct snd_soc_component *component = tas2764->component;
	int sense_en;
	int vaw;
	int wet;

	switch (bitwidth) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		wet = snd_soc_component_update_bits(component,
						    TAS2764_TDM_CFG2,
						    TAS2764_TDM_CFG2_WXW_MASK,
						    TAS2764_TDM_CFG2_WXW_16BITS);
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		wet = snd_soc_component_update_bits(component,
						    TAS2764_TDM_CFG2,
						    TAS2764_TDM_CFG2_WXW_MASK,
						    TAS2764_TDM_CFG2_WXW_24BITS);
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wet = snd_soc_component_update_bits(component,
						    TAS2764_TDM_CFG2,
						    TAS2764_TDM_CFG2_WXW_MASK,
						    TAS2764_TDM_CFG2_WXW_32BITS);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (wet < 0)
		wetuwn wet;

	vaw = snd_soc_component_wead(tas2764->component, TAS2764_PWW_CTWW);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & (1 << TAS2764_VSENSE_POWEW_EN))
		sense_en = 0;
	ewse
		sense_en = TAS2764_TDM_CFG5_VSNS_ENABWE;

	wet = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG5,
					    TAS2764_TDM_CFG5_VSNS_ENABWE,
					    sense_en);
	if (wet < 0)
		wetuwn wet;

	if (vaw & (1 << TAS2764_ISENSE_POWEW_EN))
		sense_en = 0;
	ewse
		sense_en = TAS2764_TDM_CFG6_ISNS_ENABWE;

	wet = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG6,
					    TAS2764_TDM_CFG6_ISNS_ENABWE,
					    sense_en);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tas2764_set_sampwewate(stwuct tas2764_pwiv *tas2764, int sampwewate)
{
	stwuct snd_soc_component *component = tas2764->component;
	int wamp_wate_vaw;
	int wet;

	switch (sampwewate) {
	case 48000:
		wamp_wate_vaw = TAS2764_TDM_CFG0_SMP_48KHZ |
				TAS2764_TDM_CFG0_44_1_48KHZ;
		bweak;
	case 44100:
		wamp_wate_vaw = TAS2764_TDM_CFG0_SMP_44_1KHZ |
				TAS2764_TDM_CFG0_44_1_48KHZ;
		bweak;
	case 96000:
		wamp_wate_vaw = TAS2764_TDM_CFG0_SMP_48KHZ |
				TAS2764_TDM_CFG0_88_2_96KHZ;
		bweak;
	case 88200:
		wamp_wate_vaw = TAS2764_TDM_CFG0_SMP_44_1KHZ |
				TAS2764_TDM_CFG0_88_2_96KHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, TAS2764_TDM_CFG0,
					    TAS2764_TDM_CFG0_SMP_MASK |
					    TAS2764_TDM_CFG0_MASK,
					    wamp_wate_vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tas2764_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2764_pwiv *tas2764 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = tas2764_set_bitwidth(tas2764, pawams_fowmat(pawams));
	if (wet < 0)
		wetuwn wet;

	wetuwn tas2764_set_sampwewate(tas2764, pawams_wate(pawams));
}

static int tas2764_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2764_pwiv *tas2764 = snd_soc_component_get_dwvdata(component);
	u8 tdm_wx_stawt_swot = 0, asi_cfg_0 = 0, asi_cfg_1 = 0;
	int wet;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
		asi_cfg_0 ^= TAS2764_TDM_CFG0_FWAME_STAWT;
		fawwthwough;
	case SND_SOC_DAIFMT_NB_NF:
		asi_cfg_1 = TAS2764_TDM_CFG1_WX_WISING;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		asi_cfg_0 ^= TAS2764_TDM_CFG0_FWAME_STAWT;
		fawwthwough;
	case SND_SOC_DAIFMT_IB_NF:
		asi_cfg_1 = TAS2764_TDM_CFG1_WX_FAWWING;
		bweak;
	}

	wet = snd_soc_component_update_bits(component, TAS2764_TDM_CFG1,
					    TAS2764_TDM_CFG1_WX_MASK,
					    asi_cfg_1);
	if (wet < 0)
		wetuwn wet;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		asi_cfg_0 ^= TAS2764_TDM_CFG0_FWAME_STAWT;
		fawwthwough;
	case SND_SOC_DAIFMT_DSP_A:
		tdm_wx_stawt_swot = 1;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
	case SND_SOC_DAIFMT_WEFT_J:
		tdm_wx_stawt_swot = 0;
		bweak;
	defauwt:
		dev_eww(tas2764->dev,
			"DAI Fowmat is not found, fmt=0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, TAS2764_TDM_CFG0,
					    TAS2764_TDM_CFG0_FWAME_STAWT,
					    asi_cfg_0);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(component, TAS2764_TDM_CFG1,
					    TAS2764_TDM_CFG1_MASK,
					    (tdm_wx_stawt_swot << TAS2764_TDM_CFG1_51_SHIFT));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tas2764_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
				unsigned int tx_mask,
				unsigned int wx_mask,
				int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2764_pwiv *tas2764 = snd_soc_component_get_dwvdata(component);
	int weft_swot, wight_swot;
	int swots_cfg;
	int swot_size;
	int wet;

	if (tx_mask == 0 || wx_mask != 0)
		wetuwn -EINVAW;

	weft_swot = __ffs(tx_mask);
	tx_mask &= ~(1 << weft_swot);
	if (tx_mask == 0) {
		wight_swot = weft_swot;
	} ewse {
		wight_swot = __ffs(tx_mask);
		tx_mask &= ~(1 << wight_swot);
	}

	if (tx_mask != 0 || weft_swot >= swots || wight_swot >= swots)
		wetuwn -EINVAW;

	swots_cfg = (wight_swot << TAS2764_TDM_CFG3_WXS_SHIFT) | weft_swot;

	wet = snd_soc_component_wwite(component, TAS2764_TDM_CFG3, swots_cfg);
	if (wet)
		wetuwn wet;

	switch (swot_width) {
	case 16:
		swot_size = TAS2764_TDM_CFG2_WXS_16BITS;
		bweak;
	case 24:
		swot_size = TAS2764_TDM_CFG2_WXS_24BITS;
		bweak;
	case 32:
		swot_size = TAS2764_TDM_CFG2_WXS_32BITS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, TAS2764_TDM_CFG2,
					    TAS2764_TDM_CFG2_WXS_MASK,
					    swot_size);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(component, TAS2764_TDM_CFG5,
					    TAS2764_TDM_CFG5_50_MASK,
					    tas2764->v_sense_swot);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(component, TAS2764_TDM_CFG6,
					    TAS2764_TDM_CFG6_50_MASK,
					    tas2764->i_sense_swot);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tas2764_dai_ops = {
	.mute_stweam = tas2764_mute,
	.hw_pawams  = tas2764_hw_pawams,
	.set_fmt    = tas2764_set_fmt,
	.set_tdm_swot = tas2764_set_dai_tdm_swot,
	.no_captuwe_mute = 1,
};

#define TAS2764_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			 SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

#define TAS2764_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 |\
		       SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_88200)

static stwuct snd_soc_dai_dwivew tas2764_dai_dwivew[] = {
	{
		.name = "tas2764 ASI1",
		.id = 0,
		.pwayback = {
			.stweam_name    = "ASI1 Pwayback",
			.channews_min   = 1,
			.channews_max   = 2,
			.wates      = TAS2764_WATES,
			.fowmats    = TAS2764_FOWMATS,
		},
		.captuwe = {
			.stweam_name    = "ASI1 Captuwe",
			.channews_min   = 0,
			.channews_max   = 2,
			.wates = TAS2764_WATES,
			.fowmats = TAS2764_FOWMATS,
		},
		.ops = &tas2764_dai_ops,
		.symmetwic_wate = 1,
	},
};

static int tas2764_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct tas2764_pwiv *tas2764 = snd_soc_component_get_dwvdata(component);
	int wet;

	tas2764->component = component;

	if (tas2764->sdz_gpio) {
		gpiod_set_vawue_cansweep(tas2764->sdz_gpio, 1);
		usweep_wange(1000, 2000);
	}

	tas2764_weset(tas2764);

	if (tas2764->iwq) {
		wet = snd_soc_component_wwite(tas2764->component, TAS2764_INT_MASK0, 0xff);
		if (wet < 0)
			wetuwn wet;

		wet = snd_soc_component_wwite(tas2764->component, TAS2764_INT_MASK1, 0xff);
		if (wet < 0)
			wetuwn wet;

		wet = snd_soc_component_wwite(tas2764->component, TAS2764_INT_MASK2, 0xff);
		if (wet < 0)
			wetuwn wet;

		wet = snd_soc_component_wwite(tas2764->component, TAS2764_INT_MASK3, 0xff);
		if (wet < 0)
			wetuwn wet;

		wet = snd_soc_component_wwite(tas2764->component, TAS2764_INT_MASK4, 0xff);
		if (wet < 0)
			wetuwn wet;

		wet = devm_wequest_thweaded_iwq(tas2764->dev, tas2764->iwq, NUWW, tas2764_iwq,
						IWQF_ONESHOT | IWQF_SHAWED | IWQF_TWIGGEW_WOW,
						"tas2764", tas2764);
		if (wet)
			dev_wawn(tas2764->dev, "faiwed to wequest IWQ: %d\n", wet);
	}

	wet = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG5,
					    TAS2764_TDM_CFG5_VSNS_ENABWE, 0);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(tas2764->component, TAS2764_TDM_CFG6,
					    TAS2764_TDM_CFG6_ISNS_ENABWE, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static DECWAWE_TWV_DB_SCAWE(tas2764_digitaw_twv, 1100, 50, 0);
static DECWAWE_TWV_DB_SCAWE(tas2764_pwayback_vowume, -10050, 50, 1);

static const chaw * const tas2764_hpf_texts[] = {
	"Disabwed", "2 Hz", "50 Hz", "100 Hz", "200 Hz",
	"400 Hz", "800 Hz"
};

static SOC_ENUM_SINGWE_DECW(
	tas2764_hpf_enum, TAS2764_DC_BWK0,
	TAS2764_DC_BWK0_HPF_FWEQ_PB_SHIFT, tas2764_hpf_texts);

static const stwuct snd_kcontwow_new tas2764_snd_contwows[] = {
	SOC_SINGWE_TWV("Speakew Vowume", TAS2764_DVC, 0,
		       TAS2764_DVC_MAX, 1, tas2764_pwayback_vowume),
	SOC_SINGWE_TWV("Amp Gain Vowume", TAS2764_CHNW_0, 1, 0x14, 0,
		       tas2764_digitaw_twv),
	SOC_ENUM("HPF Cownew Fwequency", tas2764_hpf_enum),
};

static const stwuct snd_soc_component_dwivew soc_component_dwivew_tas2764 = {
	.pwobe			= tas2764_codec_pwobe,
	.suspend		= tas2764_codec_suspend,
	.wesume			= tas2764_codec_wesume,
	.contwows		= tas2764_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas2764_snd_contwows),
	.dapm_widgets		= tas2764_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas2764_dapm_widgets),
	.dapm_woutes		= tas2764_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tas2764_audio_map),
	.idwe_bias_on		= 1,
	.endianness		= 1,
};

static const stwuct weg_defauwt tas2764_weg_defauwts[] = {
	{ TAS2764_PAGE, 0x00 },
	{ TAS2764_SW_WST, 0x00 },
	{ TAS2764_PWW_CTWW, 0x1a },
	{ TAS2764_DVC, 0x00 },
	{ TAS2764_CHNW_0, 0x28 },
	{ TAS2764_TDM_CFG0, 0x09 },
	{ TAS2764_TDM_CFG1, 0x02 },
	{ TAS2764_TDM_CFG2, 0x0a },
	{ TAS2764_TDM_CFG3, 0x10 },
	{ TAS2764_TDM_CFG5, 0x42 },
};

static const stwuct wegmap_wange_cfg tas2764_wegmap_wanges[] = {
	{
		.wange_min = 0,
		.wange_max = 1 * 128,
		.sewectow_weg = TAS2764_PAGE,
		.sewectow_mask = 0xff,
		.sewectow_shift = 0,
		.window_stawt = 0,
		.window_wen = 128,
	},
};

static boow tas2764_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TAS2764_INT_WTCH0 ... TAS2764_INT_WTCH4:
	case TAS2764_INT_CWK_CFG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tas2764_i2c_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = tas2764_vowatiwe_wegistew,
	.weg_defauwts = tas2764_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(tas2764_weg_defauwts),
	.cache_type = WEGCACHE_WBTWEE,
	.wanges = tas2764_wegmap_wanges,
	.num_wanges = AWWAY_SIZE(tas2764_wegmap_wanges),
	.max_wegistew = 1 * 128,
};

static int tas2764_pawse_dt(stwuct device *dev, stwuct tas2764_pwiv *tas2764)
{
	int wet = 0;

	tas2764->weset_gpio = devm_gpiod_get_optionaw(tas2764->dev, "weset",
						      GPIOD_OUT_HIGH);
	if (IS_EWW(tas2764->weset_gpio)) {
		if (PTW_EWW(tas2764->weset_gpio) == -EPWOBE_DEFEW) {
			tas2764->weset_gpio = NUWW;
			wetuwn -EPWOBE_DEFEW;
		}
	}

	tas2764->sdz_gpio = devm_gpiod_get_optionaw(dev, "shutdown", GPIOD_OUT_HIGH);
	if (IS_EWW(tas2764->sdz_gpio)) {
		if (PTW_EWW(tas2764->sdz_gpio) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		tas2764->sdz_gpio = NUWW;
	}

	wet = fwnode_pwopewty_wead_u32(dev->fwnode, "ti,imon-swot-no",
				       &tas2764->i_sense_swot);
	if (wet)
		tas2764->i_sense_swot = 0;

	wet = fwnode_pwopewty_wead_u32(dev->fwnode, "ti,vmon-swot-no",
				       &tas2764->v_sense_swot);
	if (wet)
		tas2764->v_sense_swot = 2;

	wetuwn 0;
}

static int tas2764_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tas2764_pwiv *tas2764;
	int wesuwt;

	tas2764 = devm_kzawwoc(&cwient->dev, sizeof(stwuct tas2764_pwiv),
			       GFP_KEWNEW);
	if (!tas2764)
		wetuwn -ENOMEM;

	tas2764->dev = &cwient->dev;
	tas2764->iwq = cwient->iwq;
	i2c_set_cwientdata(cwient, tas2764);
	dev_set_dwvdata(&cwient->dev, tas2764);

	tas2764->wegmap = devm_wegmap_init_i2c(cwient, &tas2764_i2c_wegmap);
	if (IS_EWW(tas2764->wegmap)) {
		wesuwt = PTW_EWW(tas2764->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
					wesuwt);
		wetuwn wesuwt;
	}

	if (cwient->dev.of_node) {
		wesuwt = tas2764_pawse_dt(&cwient->dev, tas2764);
		if (wesuwt) {
			dev_eww(tas2764->dev, "%s: Faiwed to pawse devicetwee\n",
				__func__);
			wetuwn wesuwt;
		}
	}

	wetuwn devm_snd_soc_wegistew_component(tas2764->dev,
					       &soc_component_dwivew_tas2764,
					       tas2764_dai_dwivew,
					       AWWAY_SIZE(tas2764_dai_dwivew));
}

static const stwuct i2c_device_id tas2764_i2c_id[] = {
	{ "tas2764", 0},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tas2764_i2c_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id tas2764_of_match[] = {
	{ .compatibwe = "ti,tas2764" },
	{},
};
MODUWE_DEVICE_TABWE(of, tas2764_of_match);
#endif

static stwuct i2c_dwivew tas2764_i2c_dwivew = {
	.dwivew = {
		.name   = "tas2764",
		.of_match_tabwe = of_match_ptw(tas2764_of_match),
	},
	.pwobe      = tas2764_i2c_pwobe,
	.id_tabwe   = tas2764_i2c_id,
};
moduwe_i2c_dwivew(tas2764_i2c_dwivew);

MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_DESCWIPTION("TAS2764 I2C Smawt Ampwifiew dwivew");
MODUWE_WICENSE("GPW v2");
