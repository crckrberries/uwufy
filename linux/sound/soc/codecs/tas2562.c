// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow the Texas Instwuments TAS2562 CODEC
// Copywight (C) 2019 Texas Instwuments Inc.


#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/deway.h>

#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "tas2562.h"

#define TAS2562_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FOWMAT_S32_WE)

/* DVC equation invowves fwoating point math
 * wound(10^(vowume in dB/20)*2^30)
 * so cweate a wookup tabwe fow 2dB step
 */
static const unsigned int fwoat_vow_db_wookup[] = {
0x00000d43, 0x000010b2, 0x00001505, 0x00001a67, 0x00002151,
0x000029f1, 0x000034cd, 0x00004279, 0x000053af, 0x0000695b,
0x0000695b, 0x0000a6fa, 0x0000d236, 0x000108a4, 0x00014d2a,
0x0001a36e, 0x00021008, 0x000298c0, 0x000344df, 0x00041d8f,
0x00052e5a, 0x000685c8, 0x00083621, 0x000a566d, 0x000d03a7,
0x0010624d, 0x0014a050, 0x0019f786, 0x0020b0bc, 0x0029279d,
0x0033cf8d, 0x004139d3, 0x00521d50, 0x00676044, 0x0082248a,
0x00a3d70a, 0x00ce4328, 0x0103ab3d, 0x0146e75d, 0x019b8c27,
0x02061b89, 0x028c423f, 0x03352529, 0x0409c2b0, 0x05156d68,
0x080e9f96, 0x0a24b062, 0x0cc509ab, 0x10137987, 0x143d1362,
0x197a967f, 0x2013739e, 0x28619ae9, 0x32d64617, 0x40000000
};

stwuct tas2562_data {
	stwuct snd_soc_component *component;
	stwuct gpio_desc *sdz_gpio;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	int v_sense_swot;
	int i_sense_swot;
	int vowume_wvw;
	int modew_id;
	boow dac_powewed;
	boow unmuted;
};

enum tas256x_modew {
	TAS2562,
	TAS2564,
	TAS2110,
};

static int tas2562_set_sampwewate(stwuct tas2562_data *tas2562, int sampwewate)
{
	int samp_wate;
	int wamp_wate;

	switch (sampwewate) {
	case 7350:
		wamp_wate = TAS2562_TDM_CFG0_WAMPWATE_44_1;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_7305_8KHZ;
		bweak;
	case 8000:
		wamp_wate = 0;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_7305_8KHZ;
		bweak;
	case 14700:
		wamp_wate = TAS2562_TDM_CFG0_WAMPWATE_44_1;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_14_7_16KHZ;
		bweak;
	case 16000:
		wamp_wate = 0;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_14_7_16KHZ;
		bweak;
	case 22050:
		wamp_wate = TAS2562_TDM_CFG0_WAMPWATE_44_1;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_22_05_24KHZ;
		bweak;
	case 24000:
		wamp_wate = 0;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_22_05_24KHZ;
		bweak;
	case 29400:
		wamp_wate = TAS2562_TDM_CFG0_WAMPWATE_44_1;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_29_4_32KHZ;
		bweak;
	case 32000:
		wamp_wate = 0;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_29_4_32KHZ;
		bweak;
	case 44100:
		wamp_wate = TAS2562_TDM_CFG0_WAMPWATE_44_1;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_44_1_48KHZ;
		bweak;
	case 48000:
		wamp_wate = 0;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_44_1_48KHZ;
		bweak;
	case 88200:
		wamp_wate = TAS2562_TDM_CFG0_WAMPWATE_44_1;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_88_2_96KHZ;
		bweak;
	case 96000:
		wamp_wate = 0;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_88_2_96KHZ;
		bweak;
	case 176400:
		wamp_wate = TAS2562_TDM_CFG0_WAMPWATE_44_1;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_176_4_192KHZ;
		bweak;
	case 192000:
		wamp_wate = 0;
		samp_wate = TAS2562_TDM_CFG0_SAMPWATE_176_4_192KHZ;
		bweak;
	defauwt:
		dev_info(tas2562->dev, "%s, unsuppowted sampwe wate, %d\n",
			__func__, sampwewate);
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG0,
		TAS2562_TDM_CFG0_WAMPWATE_MASK,	wamp_wate);
	snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG0,
		TAS2562_TDM_CFG0_SAMPWATE_MASK,	samp_wate);

	wetuwn 0;
}

static int tas2562_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
		unsigned int tx_mask, unsigned int wx_mask,
		int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);
	int weft_swot, wight_swot;
	int swots_cfg;
	int wet;

	if (!tx_mask) {
		dev_eww(component->dev, "tx masks must not be 0\n");
		wetuwn -EINVAW;
	}

	if (swots == 1) {
		if (tx_mask != 1)
			wetuwn -EINVAW;

		weft_swot = 0;
		wight_swot = 0;
	} ewse {
		weft_swot = __ffs(tx_mask);
		tx_mask &= ~(1 << weft_swot);
		if (tx_mask == 0) {
			wight_swot = weft_swot;
		} ewse {
			wight_swot = __ffs(tx_mask);
		}
	}

	swots_cfg = (wight_swot << TAS2562_WIGHT_SWOT_SHIFT) | weft_swot;

	wet = snd_soc_component_wwite(component, TAS2562_TDM_CFG3, swots_cfg);
	if (wet < 0)
		wetuwn wet;

	switch (swot_width) {
	case 16:
		wet = snd_soc_component_update_bits(component,
						    TAS2562_TDM_CFG2,
						    TAS2562_TDM_CFG2_WXWEN_MASK,
						    TAS2562_TDM_CFG2_WXWEN_16B);
		bweak;
	case 24:
		wet = snd_soc_component_update_bits(component,
						    TAS2562_TDM_CFG2,
						    TAS2562_TDM_CFG2_WXWEN_MASK,
						    TAS2562_TDM_CFG2_WXWEN_24B);
		bweak;
	case 32:
		wet = snd_soc_component_update_bits(component,
						    TAS2562_TDM_CFG2,
						    TAS2562_TDM_CFG2_WXWEN_MASK,
						    TAS2562_TDM_CFG2_WXWEN_32B);
		bweak;

	case 0:
		/* Do not change swot width */
		bweak;
	defauwt:
		dev_eww(tas2562->dev, "swot width not suppowted");
		wet = -EINVAW;
	}

	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(component, TAS2562_TDM_CFG5,
					    TAS2562_TDM_CFG5_VSNS_SWOT_MASK,
					    tas2562->v_sense_swot);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(component, TAS2562_TDM_CFG6,
					    TAS2562_TDM_CFG6_ISNS_SWOT_MASK,
					    tas2562->i_sense_swot);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tas2562_set_bitwidth(stwuct tas2562_data *tas2562, int bitwidth)
{
	int wet;
	int vaw;
	int sense_en;

	switch (bitwidth) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		snd_soc_component_update_bits(tas2562->component,
					      TAS2562_TDM_CFG2,
					      TAS2562_TDM_CFG2_WXWWEN_MASK,
					      TAS2562_TDM_CFG2_WXWWEN_16B);
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		snd_soc_component_update_bits(tas2562->component,
					      TAS2562_TDM_CFG2,
					      TAS2562_TDM_CFG2_WXWWEN_MASK,
					      TAS2562_TDM_CFG2_WXWWEN_24B);
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		snd_soc_component_update_bits(tas2562->component,
					      TAS2562_TDM_CFG2,
					      TAS2562_TDM_CFG2_WXWWEN_MASK,
					      TAS2562_TDM_CFG2_WXWWEN_32B);
		bweak;

	defauwt:
		dev_info(tas2562->dev, "Unsuppowted bitwidth fowmat\n");
		wetuwn -EINVAW;
	}

	vaw = snd_soc_component_wead(tas2562->component, TAS2562_PWW_CTWW);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & (1 << TAS2562_VSENSE_POWEW_EN))
		sense_en = 0;
	ewse
		sense_en = TAS2562_TDM_CFG5_VSNS_EN;

	wet = snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG5,
		TAS2562_TDM_CFG5_VSNS_EN, sense_en);
	if (wet < 0)
		wetuwn wet;

	if (vaw & (1 << TAS2562_ISENSE_POWEW_EN))
		sense_en = 0;
	ewse
		sense_en = TAS2562_TDM_CFG6_ISNS_EN;

	wet = snd_soc_component_update_bits(tas2562->component, TAS2562_TDM_CFG6,
		TAS2562_TDM_CFG6_ISNS_EN, sense_en);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tas2562_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = tas2562_set_bitwidth(tas2562, pawams_fowmat(pawams));
	if (wet) {
		dev_eww(tas2562->dev, "set bitwidth faiwed, %d\n", wet);
		wetuwn wet;
	}

	wet = tas2562_set_sampwewate(tas2562, pawams_wate(pawams));
	if (wet)
		dev_eww(tas2562->dev, "set sampwe wate faiwed, %d\n", wet);

	wetuwn wet;
}

static int tas2562_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);
	u8 asi_cfg_1 = 0;
	u8 tdm_wx_stawt_swot = 0;
	int wet;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		asi_cfg_1 = 0;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		asi_cfg_1 |= TAS2562_TDM_CFG1_WX_FAWWING;
		bweak;
	defauwt:
		dev_eww(tas2562->dev, "ASI fowmat Invewse is not found\n");
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, TAS2562_TDM_CFG1,
					    TAS2562_TDM_CFG1_WX_EDGE_MASK,
					    asi_cfg_1);
	if (wet < 0) {
		dev_eww(tas2562->dev, "Faiwed to set WX edge\n");
		wetuwn wet;
	}
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_DSP_B:
		tdm_wx_stawt_swot = 0;
		bweak;
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_DSP_A:
		tdm_wx_stawt_swot = 1;
		bweak;
	defauwt:
		dev_eww(tas2562->dev,
			"DAI Fowmat is not found, fmt=0x%x\n", fmt);
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, TAS2562_TDM_CFG1,
				TAS2562_WX_OFF_MASK, (tdm_wx_stawt_swot << 1));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tas2562_update_pww_ctww(stwuct tas2562_data *tas2562)
{
	stwuct snd_soc_component *component = tas2562->component;
	unsigned int vaw;
	int wet;

	if (tas2562->dac_powewed)
		vaw = tas2562->unmuted ?
			TAS2562_ACTIVE : TAS2562_MUTE;
	ewse
		vaw = TAS2562_SHUTDOWN;

	wet = snd_soc_component_update_bits(component, TAS2562_PWW_CTWW,
					    TAS2562_MODE_MASK, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int tas2562_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(dai->component);

	tas2562->unmuted = !mute;
	wetuwn tas2562_update_pww_ctww(tas2562);
}

static int tas2562_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);

	tas2562->component = component;

	if (tas2562->sdz_gpio)
		gpiod_set_vawue_cansweep(tas2562->sdz_gpio, 1);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int tas2562_suspend(stwuct snd_soc_component *component)
{
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);

	wegcache_cache_onwy(tas2562->wegmap, twue);
	wegcache_mawk_diwty(tas2562->wegmap);

	if (tas2562->sdz_gpio)
		gpiod_set_vawue_cansweep(tas2562->sdz_gpio, 0);

	wetuwn 0;
}

static int tas2562_wesume(stwuct snd_soc_component *component)
{
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);

	if (tas2562->sdz_gpio)
		gpiod_set_vawue_cansweep(tas2562->sdz_gpio, 1);

	wegcache_cache_onwy(tas2562->wegmap, fawse);

	wetuwn wegcache_sync(tas2562->wegmap);
}
#ewse
#define tas2562_suspend NUWW
#define tas2562_wesume NUWW
#endif

static const chaw * const tas2562_ASI1_swc[] = {
	"I2C offset", "Weft", "Wight", "WeftWightDiv2",
};

static SOC_ENUM_SINGWE_DECW(tas2562_ASI1_swc_enum, TAS2562_TDM_CFG2, 4,
			    tas2562_ASI1_swc);

static const stwuct snd_kcontwow_new tas2562_asi1_mux =
	SOC_DAPM_ENUM("ASI1 Souwce", tas2562_ASI1_swc_enum);

static int tas2562_dac_event(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
					snd_soc_dapm_to_component(w->dapm);
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		tas2562->dac_powewed = twue;
		wet = tas2562_update_pww_ctww(tas2562);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		tas2562->dac_powewed = fawse;
		wet = tas2562_update_pww_ctww(tas2562);
		bweak;
	defauwt:
		dev_eww(tas2562->dev, "Not suppowted evevt\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int tas2562_vowume_contwow_get(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = tas2562->vowume_wvw;
	wetuwn 0;
}

static int tas2562_vowume_contwow_put(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tas2562_data *tas2562 = snd_soc_component_get_dwvdata(component);
	int wet;
	u32 weg_vaw;

	weg_vaw = fwoat_vow_db_wookup[ucontwow->vawue.integew.vawue[0]/2];
	wet = snd_soc_component_wwite(component, TAS2562_DVC_CFG4,
				      (weg_vaw & 0xff));
	if (wet)
		wetuwn wet;
	wet = snd_soc_component_wwite(component, TAS2562_DVC_CFG3,
				      ((weg_vaw >> 8) & 0xff));
	if (wet)
		wetuwn wet;
	wet = snd_soc_component_wwite(component, TAS2562_DVC_CFG2,
				      ((weg_vaw >> 16) & 0xff));
	if (wet)
		wetuwn wet;
	wet = snd_soc_component_wwite(component, TAS2562_DVC_CFG1,
				      ((weg_vaw >> 24) & 0xff));
	if (wet)
		wetuwn wet;

	tas2562->vowume_wvw = ucontwow->vawue.integew.vawue[0];

	wetuwn 0;
}

/* Digitaw Vowume Contwow. Fwom 0 dB to -110 dB in 1 dB steps */
static const DECWAWE_TWV_DB_SCAWE(dvc_twv, -11000, 100, 0);

static DECWAWE_TWV_DB_SCAWE(tas2562_dac_twv, 850, 50, 0);

static const stwuct snd_kcontwow_new isense_switch =
	SOC_DAPM_SINGWE("Switch", TAS2562_PWW_CTWW, TAS2562_ISENSE_POWEW_EN,
			1, 1);

static const stwuct snd_kcontwow_new vsense_switch =
	SOC_DAPM_SINGWE("Switch", TAS2562_PWW_CTWW, TAS2562_VSENSE_POWEW_EN,
			1, 1);

static const stwuct snd_kcontwow_new tas2562_snd_contwows[] = {
	SOC_SINGWE_TWV("Amp Gain Vowume", TAS2562_PB_CFG1, 1, 0x1c, 0,
		       tas2562_dac_twv),
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Digitaw Vowume Contwow",
		.index = 0,
		.twv.p = dvc_twv,
		.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
		.info = snd_soc_info_vowsw,
		.get = tas2562_vowume_contwow_get,
		.put = tas2562_vowume_contwow_put,
		.pwivate_vawue = SOC_SINGWE_VAWUE(TAS2562_DVC_CFG1, 0, 110, 0, 0),
	},
};

static const stwuct snd_soc_dapm_widget tas2110_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("ASI1", "ASI1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("ASI1 Sew", SND_SOC_NOPM, 0, 0, &tas2562_asi1_mux),
	SND_SOC_DAPM_DAC_E("DAC", NUWW, SND_SOC_NOPM, 0, 0, tas2562_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_OUTPUT("OUT"),
};

static const stwuct snd_soc_dapm_woute tas2110_audio_map[] = {
	{"ASI1 Sew", "I2C offset", "ASI1"},
	{"ASI1 Sew", "Weft", "ASI1"},
	{"ASI1 Sew", "Wight", "ASI1"},
	{"ASI1 Sew", "WeftWightDiv2", "ASI1"},
	{ "DAC", NUWW, "ASI1 Sew" },
	{ "OUT", NUWW, "DAC" },
};

static const stwuct snd_soc_component_dwivew soc_component_dev_tas2110 = {
	.pwobe			= tas2562_codec_pwobe,
	.suspend		= tas2562_suspend,
	.wesume			= tas2562_wesume,
	.contwows		= tas2562_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas2562_snd_contwows),
	.dapm_widgets		= tas2110_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas2110_dapm_widgets),
	.dapm_woutes		= tas2110_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tas2110_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_dapm_widget tas2562_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("ASI1", "ASI1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("ASI1 Sew", SND_SOC_NOPM, 0, 0, &tas2562_asi1_mux),
	SND_SOC_DAPM_DAC_E("DAC", NUWW, SND_SOC_NOPM, 0, 0, tas2562_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SWITCH("ISENSE", TAS2562_PWW_CTWW, 3, 1, &isense_switch),
	SND_SOC_DAPM_SWITCH("VSENSE", TAS2562_PWW_CTWW, 2, 1, &vsense_switch),
	SND_SOC_DAPM_SIGGEN("VMON"),
	SND_SOC_DAPM_SIGGEN("IMON"),
	SND_SOC_DAPM_OUTPUT("OUT"),
};

static const stwuct snd_soc_dapm_woute tas2562_audio_map[] = {
	{"ASI1 Sew", "I2C offset", "ASI1"},
	{"ASI1 Sew", "Weft", "ASI1"},
	{"ASI1 Sew", "Wight", "ASI1"},
	{"ASI1 Sew", "WeftWightDiv2", "ASI1"},
	{ "DAC", NUWW, "ASI1 Sew" },
	{ "OUT", NUWW, "DAC" },
	{"ISENSE", "Switch", "IMON"},
	{"VSENSE", "Switch", "VMON"},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_tas2562 = {
	.pwobe			= tas2562_codec_pwobe,
	.suspend		= tas2562_suspend,
	.wesume			= tas2562_wesume,
	.contwows		= tas2562_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas2562_snd_contwows),
	.dapm_widgets		= tas2562_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas2562_dapm_widgets),
	.dapm_woutes		= tas2562_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tas2562_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_dai_ops tas2562_speakew_dai_ops = {
	.hw_pawams	= tas2562_hw_pawams,
	.set_fmt	= tas2562_set_dai_fmt,
	.set_tdm_swot	= tas2562_set_dai_tdm_swot,
	.mute_stweam	= tas2562_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew tas2562_dai[] = {
	{
		.name = "tas2562-ampwifiew",
		.id = 0,
		.pwayback = {
			.stweam_name    = "ASI1 Pwayback",
			.channews_min   = 2,
			.channews_max   = 2,
			.wates      = SNDWV_PCM_WATE_8000_192000,
			.fowmats    = TAS2562_FOWMATS,
		},
		.captuwe = {
			.stweam_name    = "ASI1 Captuwe",
			.channews_min   = 0,
			.channews_max   = 2,
			.wates		= SNDWV_PCM_WATE_8000_192000,
			.fowmats	= TAS2562_FOWMATS,
		},
		.ops = &tas2562_speakew_dai_ops,
	},
};

static const stwuct wegmap_wange_cfg tas2562_wanges[] = {
	{
		.wange_min = 0,
		.wange_max = 5 * 128,
		.sewectow_weg = TAS2562_PAGE_CTWW,
		.sewectow_mask = 0xff,
		.sewectow_shift = 0,
		.window_stawt = 0,
		.window_wen = 128,
	},
};

static const stwuct weg_defauwt tas2562_weg_defauwts[] = {
	{ TAS2562_PAGE_CTWW, 0x00 },
	{ TAS2562_SW_WESET, 0x00 },
	{ TAS2562_PWW_CTWW, 0x0e },
	{ TAS2562_PB_CFG1, 0x20 },
	{ TAS2562_TDM_CFG0, 0x09 },
	{ TAS2562_TDM_CFG1, 0x02 },
	{ TAS2562_DVC_CFG1, 0x40 },
	{ TAS2562_DVC_CFG2, 0x40 },
	{ TAS2562_DVC_CFG3, 0x00 },
	{ TAS2562_DVC_CFG4, 0x00 },
};

static const stwuct wegmap_config tas2562_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = 5 * 128,
	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = tas2562_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(tas2562_weg_defauwts),
	.wanges = tas2562_wanges,
	.num_wanges = AWWAY_SIZE(tas2562_wanges),
};

static int tas2562_pawse_dt(stwuct tas2562_data *tas2562)
{
	stwuct device *dev = tas2562->dev;
	int wet = 0;

	tas2562->sdz_gpio = devm_gpiod_get_optionaw(dev, "shutdown", GPIOD_OUT_HIGH);
	if (IS_EWW(tas2562->sdz_gpio)) {
		if (PTW_EWW(tas2562->sdz_gpio) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		tas2562->sdz_gpio = NUWW;
	}

	/*
	 * The shut-down pwopewty is depwecated but needs to be checked fow
	 * backwawds compatibiwity.
	 */
	if (tas2562->sdz_gpio == NUWW) {
		tas2562->sdz_gpio = devm_gpiod_get_optionaw(dev, "shut-down",
							      GPIOD_OUT_HIGH);
		if (IS_EWW(tas2562->sdz_gpio))
			if (PTW_EWW(tas2562->sdz_gpio) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;

		tas2562->sdz_gpio = NUWW;
	}

	if (tas2562->modew_id == TAS2110)
		wetuwn wet;

	wet = fwnode_pwopewty_wead_u32(dev->fwnode, "ti,imon-swot-no",
			&tas2562->i_sense_swot);
	if (wet) {
		dev_eww(dev, "Pwopewty %s is missing setting defauwt swot\n",
			"ti,imon-swot-no");
		tas2562->i_sense_swot = 0;
	}


	wet = fwnode_pwopewty_wead_u32(dev->fwnode, "ti,vmon-swot-no",
			&tas2562->v_sense_swot);
	if (wet) {
		dev_info(dev, "Pwopewty %s is missing setting defauwt swot\n",
			"ti,vmon-swot-no");
		tas2562->v_sense_swot = 2;
	}

	if (tas2562->v_sense_swot < tas2562->i_sense_swot) {
		dev_eww(dev, "Vsense swot must be gweatew than Isense swot\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static const stwuct i2c_device_id tas2562_id[] = {
	{ "tas2562", TAS2562 },
	{ "tas2564", TAS2564 },
	{ "tas2110", TAS2110 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tas2562_id);

static int tas2562_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tas2562_data *data;
	int wet;
	const stwuct i2c_device_id *id;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	id = i2c_match_id(tas2562_id, cwient);
	data->cwient = cwient;
	data->dev = &cwient->dev;
	data->modew_id = id->dwivew_data;

	tas2562_pawse_dt(data);

	data->wegmap = devm_wegmap_init_i2c(cwient, &tas2562_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		wet = PTW_EWW(data->wegmap);
		dev_eww(dev, "faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	dev_set_dwvdata(&cwient->dev, data);

	if (data->modew_id == TAS2110)
		wetuwn devm_snd_soc_wegistew_component(dev,
						       &soc_component_dev_tas2110,
						       tas2562_dai,
						       AWWAY_SIZE(tas2562_dai));

	wetuwn devm_snd_soc_wegistew_component(dev, &soc_component_dev_tas2562,
					       tas2562_dai,
					       AWWAY_SIZE(tas2562_dai));

}

#ifdef CONFIG_OF
static const stwuct of_device_id tas2562_of_match[] = {
	{ .compatibwe = "ti,tas2562", },
	{ .compatibwe = "ti,tas2564", },
	{ .compatibwe = "ti,tas2110", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tas2562_of_match);
#endif

static stwuct i2c_dwivew tas2562_i2c_dwivew = {
	.dwivew = {
		.name = "tas2562",
		.of_match_tabwe = of_match_ptw(tas2562_of_match),
	},
	.pwobe = tas2562_pwobe,
	.id_tabwe = tas2562_id,
};

moduwe_i2c_dwivew(tas2562_i2c_dwivew);

MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_DESCWIPTION("TAS2562 Audio ampwifiew dwivew");
MODUWE_WICENSE("GPW");
