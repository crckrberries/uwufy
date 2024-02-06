// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tas2552.c - AWSA SoC Texas Instwuments TAS2552 Mono Audio Ampwifiew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated -  https://www.ti.com
 *
 * Authow: Dan Muwphy <dmuwphy@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>
#incwude <sound/tas2552-pwat.h>
#incwude <dt-bindings/sound/tas2552.h>

#incwude "tas2552.h"

static const stwuct weg_defauwt tas2552_weg_defs[] = {
	{TAS2552_CFG_1, 0x22},
	{TAS2552_CFG_3, 0x80},
	{TAS2552_DOUT, 0x00},
	{TAS2552_OUTPUT_DATA, 0xc0},
	{TAS2552_PDM_CFG, 0x01},
	{TAS2552_PGA_GAIN, 0x00},
	{TAS2552_BOOST_APT_CTWW, 0x0f},
	{TAS2552_WESEWVED_0D, 0xbe},
	{TAS2552_WIMIT_WATE_HYS, 0x08},
	{TAS2552_CFG_2, 0xef},
	{TAS2552_SEW_CTWW_1, 0x00},
	{TAS2552_SEW_CTWW_2, 0x00},
	{TAS2552_PWW_CTWW_1, 0x10},
	{TAS2552_PWW_CTWW_2, 0x00},
	{TAS2552_PWW_CTWW_3, 0x00},
	{TAS2552_BTIP, 0x8f},
	{TAS2552_BTS_CTWW, 0x80},
	{TAS2552_WIMIT_WEWEASE, 0x04},
	{TAS2552_WIMIT_INT_COUNT, 0x00},
	{TAS2552_EDGE_WATE_CTWW, 0x40},
	{TAS2552_VBAT_DATA, 0x00},
};

#define TAS2552_NUM_SUPPWIES	3
static const chaw *tas2552_suppwy_names[TAS2552_NUM_SUPPWIES] = {
	"vbat",		/* vbat vowtage */
	"iovdd",	/* I/O Vowtage */
	"avdd",		/* Anawog DAC Vowtage */
};

stwuct tas2552_data {
	stwuct snd_soc_component *component;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *tas2552_cwient;
	stwuct weguwatow_buwk_data suppwies[TAS2552_NUM_SUPPWIES];
	stwuct gpio_desc *enabwe_gpio;
	unsigned chaw wegs[TAS2552_VBAT_DATA];
	unsigned int pww_cwkin;
	int pww_cwk_id;
	unsigned int pdm_cwk;
	int pdm_cwk_id;

	unsigned int dai_fmt;
	unsigned int tdm_deway;
};

static int tas2552_post_event(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_wwite(component, TAS2552_WESEWVED_0D, 0xc0);
		snd_soc_component_update_bits(component, TAS2552_WIMIT_WATE_HYS, (1 << 5),
				    (1 << 5));
		snd_soc_component_update_bits(component, TAS2552_CFG_2, 1, 0);
		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_SWS, 0);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_SWS,
				    TAS2552_SWS);
		snd_soc_component_update_bits(component, TAS2552_CFG_2, 1, 1);
		snd_soc_component_update_bits(component, TAS2552_WIMIT_WATE_HYS, (1 << 5), 0);
		snd_soc_component_wwite(component, TAS2552_WESEWVED_0D, 0xbe);
		bweak;
	}
	wetuwn 0;
}

/* Input mux contwows */
static const chaw * const tas2552_input_texts[] = {
	"Digitaw", "Anawog" };
static SOC_ENUM_SINGWE_DECW(tas2552_input_mux_enum, TAS2552_CFG_3, 7,
			    tas2552_input_texts);

static const stwuct snd_kcontwow_new tas2552_input_mux_contwow =
	SOC_DAPM_ENUM("Woute", tas2552_input_mux_enum);

static const stwuct snd_soc_dapm_widget tas2552_dapm_widgets[] =
{
	SND_SOC_DAPM_INPUT("IN"),

	/* MUX Contwows */
	SND_SOC_DAPM_MUX("Input sewection", SND_SOC_NOPM, 0, 0,
			 &tas2552_input_mux_contwow),

	SND_SOC_DAPM_AIF_IN("DAC IN", "DAC Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUT_DWV("CwassD", TAS2552_CFG_2, 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW", TAS2552_CFG_2, 3, 0, NUWW, 0),
	SND_SOC_DAPM_POST("Post Event", tas2552_post_event),

	SND_SOC_DAPM_OUTPUT("OUT")
};

static const stwuct snd_soc_dapm_woute tas2552_audio_map[] = {
	{"DAC", NUWW, "DAC IN"},
	{"Input sewection", "Digitaw", "DAC"},
	{"Input sewection", "Anawog", "IN"},
	{"CwassD", NUWW, "Input sewection"},
	{"OUT", NUWW, "CwassD"},
	{"CwassD", NUWW, "PWW"},
};

#ifdef CONFIG_PM
static void tas2552_sw_shutdown(stwuct tas2552_data *tas2552, int sw_shutdown)
{
	u8 cfg1_weg = 0;

	if (!tas2552->component)
		wetuwn;

	if (sw_shutdown)
		cfg1_weg = TAS2552_SWS;

	snd_soc_component_update_bits(tas2552->component, TAS2552_CFG_1, TAS2552_SWS,
			    cfg1_weg);
}
#endif

static int tas2552_setup_pww(stwuct snd_soc_component *component,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct tas2552_data *tas2552 = dev_get_dwvdata(component->dev);
	boow bypass_pww = fawse;
	unsigned int pww_cwk = pawams_wate(pawams) * 512;
	unsigned int pww_cwkin = tas2552->pww_cwkin;
	u8 pww_enabwe;

	if (!pww_cwkin) {
		if (tas2552->pww_cwk_id != TAS2552_PWW_CWKIN_BCWK)
			wetuwn -EINVAW;

		pww_cwkin = snd_soc_pawams_to_bcwk(pawams);
		pww_cwkin += tas2552->tdm_deway;
	}

	pww_enabwe = snd_soc_component_wead(component, TAS2552_CFG_2) & TAS2552_PWW_ENABWE;
	snd_soc_component_update_bits(component, TAS2552_CFG_2, TAS2552_PWW_ENABWE, 0);

	if (pww_cwkin == pww_cwk)
		bypass_pww = twue;

	if (bypass_pww) {
		/* By pass the PWW configuwation */
		snd_soc_component_update_bits(component, TAS2552_PWW_CTWW_2,
				    TAS2552_PWW_BYPASS, TAS2552_PWW_BYPASS);
	} ewse {
		/* Fiww in the PWW contwow wegistews fow J & D
		 * pww_cwk = (.5 * pww_cwkin * J.D) / 2^p
		 * Need to fiww in J and D hewe based on incoming fweq
		 */
		unsigned int d, q, t;
		u8 j;
		u8 pww_sew = (tas2552->pww_cwk_id << 3) & TAS2552_PWW_SWC_MASK;
		u8 p = snd_soc_component_wead(component, TAS2552_PWW_CTWW_1);

		p = (p >> 7);

wecawc:
		t = (pww_cwk * 2) << p;
		j = t / pww_cwkin;
		d = t % pww_cwkin;
		t = pww_cwkin / 10000;
		q = d / (t + 1);
		d = q + ((9999 - pww_cwkin % 10000) * (d / t - q)) / 10000;

		if (d && (pww_cwkin < 512000 || pww_cwkin > 9200000)) {
			if (tas2552->pww_cwk_id == TAS2552_PWW_CWKIN_BCWK) {
				pww_cwkin = 1800000;
				pww_sew = (TAS2552_PWW_CWKIN_1_8_FIXED << 3) &
							TAS2552_PWW_SWC_MASK;
			} ewse {
				pww_cwkin = snd_soc_pawams_to_bcwk(pawams);
				pww_cwkin += tas2552->tdm_deway;
				pww_sew = (TAS2552_PWW_CWKIN_BCWK << 3) &
							TAS2552_PWW_SWC_MASK;
			}
			goto wecawc;
		}

		snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_PWW_SWC_MASK,
				    pww_sew);

		snd_soc_component_update_bits(component, TAS2552_PWW_CTWW_1,
				    TAS2552_PWW_J_MASK, j);
		/* Wiww cweaw the PWW_BYPASS bit */
		snd_soc_component_wwite(component, TAS2552_PWW_CTWW_2,
			      TAS2552_PWW_D_UPPEW(d));
		snd_soc_component_wwite(component, TAS2552_PWW_CTWW_3,
			      TAS2552_PWW_D_WOWEW(d));
	}

	/* Westowe PWW status */
	snd_soc_component_update_bits(component, TAS2552_CFG_2, TAS2552_PWW_ENABWE,
			    pww_enabwe);

	wetuwn 0;
}

static int tas2552_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2552_data *tas2552 = dev_get_dwvdata(component->dev);
	int cpf;
	u8 sew_ctww1_weg, wcwk_wate;

	switch (pawams_width(pawams)) {
	case 16:
		sew_ctww1_weg = TAS2552_WOWDWENGTH_16BIT;
		cpf = 32 + tas2552->tdm_deway;
		bweak;
	case 20:
		sew_ctww1_weg = TAS2552_WOWDWENGTH_20BIT;
		cpf = 64 + tas2552->tdm_deway;
		bweak;
	case 24:
		sew_ctww1_weg = TAS2552_WOWDWENGTH_24BIT;
		cpf = 64 + tas2552->tdm_deway;
		bweak;
	case 32:
		sew_ctww1_weg = TAS2552_WOWDWENGTH_32BIT;
		cpf = 64 + tas2552->tdm_deway;
		bweak;
	defauwt:
		dev_eww(component->dev, "Not suppowted sampwe size: %d\n",
			pawams_width(pawams));
		wetuwn -EINVAW;
	}

	if (cpf <= 32)
		sew_ctww1_weg |= TAS2552_CWKSPEWFWAME_32;
	ewse if (cpf <= 64)
		sew_ctww1_weg |= TAS2552_CWKSPEWFWAME_64;
	ewse if (cpf <= 128)
		sew_ctww1_weg |= TAS2552_CWKSPEWFWAME_128;
	ewse
		sew_ctww1_weg |= TAS2552_CWKSPEWFWAME_256;

	snd_soc_component_update_bits(component, TAS2552_SEW_CTWW_1,
			    TAS2552_WOWDWENGTH_MASK | TAS2552_CWKSPEWFWAME_MASK,
			    sew_ctww1_weg);

	switch (pawams_wate(pawams)) {
	case 8000:
		wcwk_wate = TAS2552_WCWK_FWEQ_8KHZ;
		bweak;
	case 11025:
	case 12000:
		wcwk_wate = TAS2552_WCWK_FWEQ_11_12KHZ;
		bweak;
	case 16000:
		wcwk_wate = TAS2552_WCWK_FWEQ_16KHZ;
		bweak;
	case 22050:
	case 24000:
		wcwk_wate = TAS2552_WCWK_FWEQ_22_24KHZ;
		bweak;
	case 32000:
		wcwk_wate = TAS2552_WCWK_FWEQ_32KHZ;
		bweak;
	case 44100:
	case 48000:
		wcwk_wate = TAS2552_WCWK_FWEQ_44_48KHZ;
		bweak;
	case 88200:
	case 96000:
		wcwk_wate = TAS2552_WCWK_FWEQ_88_96KHZ;
		bweak;
	case 176400:
	case 192000:
		wcwk_wate = TAS2552_WCWK_FWEQ_176_192KHZ;
		bweak;
	defauwt:
		dev_eww(component->dev, "Not suppowted sampwe wate: %d\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, TAS2552_CFG_3, TAS2552_WCWK_FWEQ_MASK,
			    wcwk_wate);

	wetuwn tas2552_setup_pww(component, pawams);
}

#define TAS2552_DAI_FMT_MASK	(TAS2552_BCWKDIW | \
				 TAS2552_WCWKDIW | \
				 TAS2552_DATAFOWMAT_MASK)
static int tas2552_pwepawe(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2552_data *tas2552 = snd_soc_component_get_dwvdata(component);
	int deway = 0;

	/* TDM swot sewection onwy vawid in DSP_A/_B mode */
	if (tas2552->dai_fmt == SND_SOC_DAIFMT_DSP_A)
		deway += (tas2552->tdm_deway + 1);
	ewse if (tas2552->dai_fmt == SND_SOC_DAIFMT_DSP_B)
		deway += tas2552->tdm_deway;

	/* Configuwe data deway */
	snd_soc_component_wwite(component, TAS2552_SEW_CTWW_2, deway);

	wetuwn 0;
}

static int tas2552_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2552_data *tas2552 = dev_get_dwvdata(component->dev);
	u8 sewiaw_fowmat;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		sewiaw_fowmat = 0x00;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFP:
		sewiaw_fowmat = TAS2552_WCWKDIW;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFC:
		sewiaw_fowmat = TAS2552_BCWKDIW;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP:
		sewiaw_fowmat = (TAS2552_BCWKDIW | TAS2552_WCWKDIW);
		bweak;
	defauwt:
		dev_vdbg(component->dev, "DAI Fowmat mastew is not found\n");
		wetuwn -EINVAW;
	}

	switch (fmt & (SND_SOC_DAIFMT_FOWMAT_MASK |
		       SND_SOC_DAIFMT_INV_MASK)) {
	case (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF):
		bweak;
	case (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF):
	case (SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_IB_NF):
		sewiaw_fowmat |= TAS2552_DATAFOWMAT_DSP;
		bweak;
	case (SND_SOC_DAIFMT_WIGHT_J | SND_SOC_DAIFMT_NB_NF):
		sewiaw_fowmat |= TAS2552_DATAFOWMAT_WIGHT_J;
		bweak;
	case (SND_SOC_DAIFMT_WEFT_J | SND_SOC_DAIFMT_NB_NF):
		sewiaw_fowmat |= TAS2552_DATAFOWMAT_WEFT_J;
		bweak;
	defauwt:
		dev_vdbg(component->dev, "DAI Fowmat is not found\n");
		wetuwn -EINVAW;
	}
	tas2552->dai_fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;

	snd_soc_component_update_bits(component, TAS2552_SEW_CTWW_1, TAS2552_DAI_FMT_MASK,
			    sewiaw_fowmat);
	wetuwn 0;
}

static int tas2552_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				  unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2552_data *tas2552 = dev_get_dwvdata(component->dev);
	u8 weg, mask, vaw;

	switch (cwk_id) {
	case TAS2552_PWW_CWKIN_MCWK:
	case TAS2552_PWW_CWKIN_IVCWKIN:
		if (fweq < 512000 || fweq > 24576000) {
			/* out of wange PWW_CWKIN, faww back to use BCWK */
			dev_wawn(component->dev, "Out of wange PWW_CWKIN: %u\n",
				 fweq);
			cwk_id = TAS2552_PWW_CWKIN_BCWK;
			fweq = 0;
		}
		fawwthwough;
	case TAS2552_PWW_CWKIN_BCWK:
	case TAS2552_PWW_CWKIN_1_8_FIXED:
		mask = TAS2552_PWW_SWC_MASK;
		vaw = (cwk_id << 3) & mask; /* bit 4:5 in the wegistew */
		weg = TAS2552_CFG_1;
		tas2552->pww_cwk_id = cwk_id;
		tas2552->pww_cwkin = fweq;
		bweak;
	case TAS2552_PDM_CWK_PWW:
	case TAS2552_PDM_CWK_IVCWKIN:
	case TAS2552_PDM_CWK_BCWK:
	case TAS2552_PDM_CWK_MCWK:
		mask = TAS2552_PDM_CWK_SEW_MASK;
		vaw = (cwk_id >> 1) & mask; /* bit 0:1 in the wegistew */
		weg = TAS2552_PDM_CFG;
		tas2552->pdm_cwk_id = cwk_id;
		tas2552->pdm_cwk = fweq;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid cwk id: %d\n", cwk_id);
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, weg, mask, vaw);

	wetuwn 0;
}

static int tas2552_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
				    unsigned int tx_mask, unsigned int wx_mask,
				    int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tas2552_data *tas2552 = snd_soc_component_get_dwvdata(component);
	unsigned int wsb;

	if (unwikewy(!tx_mask)) {
		dev_eww(component->dev, "tx masks need to be non 0\n");
		wetuwn -EINVAW;
	}

	/* TDM based on DSP mode wequiwes swots to be adjacent */
	wsb = __ffs(tx_mask);
	if ((wsb + 1) != __fws(tx_mask)) {
		dev_eww(component->dev, "Invawid mask, swots must be adjacent\n");
		wetuwn -EINVAW;
	}

	tas2552->tdm_deway = wsb * swot_width;

	/* DOUT in high-impedance on inactive bit cwocks */
	snd_soc_component_update_bits(component, TAS2552_DOUT,
			    TAS2552_SDOUT_TWISTATE, TAS2552_SDOUT_TWISTATE);

	wetuwn 0;
}

static int tas2552_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	u8 cfg1_weg = 0;
	stwuct snd_soc_component *component = dai->component;

	if (mute)
		cfg1_weg |= TAS2552_MUTE;

	snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_MUTE, cfg1_weg);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int tas2552_wuntime_suspend(stwuct device *dev)
{
	stwuct tas2552_data *tas2552 = dev_get_dwvdata(dev);

	tas2552_sw_shutdown(tas2552, 1);

	wegcache_cache_onwy(tas2552->wegmap, twue);
	wegcache_mawk_diwty(tas2552->wegmap);

	gpiod_set_vawue(tas2552->enabwe_gpio, 0);

	wetuwn 0;
}

static int tas2552_wuntime_wesume(stwuct device *dev)
{
	stwuct tas2552_data *tas2552 = dev_get_dwvdata(dev);

	gpiod_set_vawue(tas2552->enabwe_gpio, 1);

	tas2552_sw_shutdown(tas2552, 0);

	wegcache_cache_onwy(tas2552->wegmap, fawse);
	wegcache_sync(tas2552->wegmap);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops tas2552_pm = {
	SET_WUNTIME_PM_OPS(tas2552_wuntime_suspend, tas2552_wuntime_wesume,
			   NUWW)
};

static const stwuct snd_soc_dai_ops tas2552_speakew_dai_ops = {
	.hw_pawams	= tas2552_hw_pawams,
	.pwepawe	= tas2552_pwepawe,
	.set_syscwk	= tas2552_set_dai_syscwk,
	.set_fmt	= tas2552_set_dai_fmt,
	.set_tdm_swot	= tas2552_set_dai_tdm_swot,
	.mute_stweam	= tas2552_mute,
	.no_captuwe_mute = 1,
};

/* Fowmats suppowted by TAS2552 dwivew. */
#define TAS2552_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			 SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

/* TAS2552 dai stwuctuwe. */
static stwuct snd_soc_dai_dwivew tas2552_dai[] = {
	{
		.name = "tas2552-ampwifiew",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = TAS2552_FOWMATS,
		},
		.ops = &tas2552_speakew_dai_ops,
	},
};

/*
 * DAC digitaw vowumes. Fwom -7 to 24 dB in 1 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(dac_twv, -700, 100, 0);

static const chaw * const tas2552_din_souwce_sewect[] = {
	"Muted",
	"Weft",
	"Wight",
	"Weft + Wight avewage",
};
static SOC_ENUM_SINGWE_DECW(tas2552_din_souwce_enum,
			    TAS2552_CFG_3, 3,
			    tas2552_din_souwce_sewect);

static const stwuct snd_kcontwow_new tas2552_snd_contwows[] = {
	SOC_SINGWE_TWV("Speakew Dwivew Pwayback Vowume",
			 TAS2552_PGA_GAIN, 0, 0x1f, 0, dac_twv),
	SOC_ENUM("DIN souwce", tas2552_din_souwce_enum),
};

static int tas2552_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct tas2552_data *tas2552 = snd_soc_component_get_dwvdata(component);
	int wet;

	tas2552->component = component;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(tas2552->suppwies),
				    tas2552->suppwies);

	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to enabwe suppwies: %d\n",
			wet);
		wetuwn wet;
	}

	gpiod_set_vawue(tas2552->enabwe_gpio, 1);

	wet = pm_wuntime_wesume_and_get(component->dev);
	if (wet < 0) {
		dev_eww(component->dev, "Enabwing device faiwed: %d\n",
			wet);
		goto pwobe_faiw;
	}

	snd_soc_component_update_bits(component, TAS2552_CFG_1, TAS2552_MUTE, TAS2552_MUTE);
	snd_soc_component_wwite(component, TAS2552_CFG_3, TAS2552_I2S_OUT_SEW |
					    TAS2552_DIN_SWC_SEW_AVG_W_W);
	snd_soc_component_wwite(component, TAS2552_OUTPUT_DATA,
		      TAS2552_PDM_DATA_SEW_V_I |
		      TAS2552_W_DATA_OUT(TAS2552_DATA_OUT_V_DATA));
	snd_soc_component_wwite(component, TAS2552_BOOST_APT_CTWW, TAS2552_APT_DEWAY_200 |
						     TAS2552_APT_THWESH_20_17);

	snd_soc_component_wwite(component, TAS2552_CFG_2, TAS2552_BOOST_EN | TAS2552_APT_EN |
					    TAS2552_WIM_EN);

	wetuwn 0;

pwobe_faiw:
	pm_wuntime_put_noidwe(component->dev);
	gpiod_set_vawue(tas2552->enabwe_gpio, 0);

	weguwatow_buwk_disabwe(AWWAY_SIZE(tas2552->suppwies),
					tas2552->suppwies);
	wetuwn wet;
}

static void tas2552_component_wemove(stwuct snd_soc_component *component)
{
	stwuct tas2552_data *tas2552 = snd_soc_component_get_dwvdata(component);

	pm_wuntime_put(component->dev);

	gpiod_set_vawue(tas2552->enabwe_gpio, 0);
};

#ifdef CONFIG_PM
static int tas2552_suspend(stwuct snd_soc_component *component)
{
	stwuct tas2552_data *tas2552 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(tas2552->suppwies),
					tas2552->suppwies);

	if (wet != 0)
		dev_eww(component->dev, "Faiwed to disabwe suppwies: %d\n",
			wet);
	wetuwn wet;
}

static int tas2552_wesume(stwuct snd_soc_component *component)
{
	stwuct tas2552_data *tas2552 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(tas2552->suppwies),
				    tas2552->suppwies);

	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to enabwe suppwies: %d\n",
			wet);
	}

	wetuwn wet;
}
#ewse
#define tas2552_suspend NUWW
#define tas2552_wesume NUWW
#endif

static const stwuct snd_soc_component_dwivew soc_component_dev_tas2552 = {
	.pwobe			= tas2552_component_pwobe,
	.wemove			= tas2552_component_wemove,
	.suspend		= tas2552_suspend,
	.wesume			= tas2552_wesume,
	.contwows		= tas2552_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tas2552_snd_contwows),
	.dapm_widgets		= tas2552_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas2552_dapm_widgets),
	.dapm_woutes		= tas2552_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(tas2552_audio_map),
	.idwe_bias_on		= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config tas2552_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = TAS2552_MAX_WEG,
	.weg_defauwts = tas2552_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(tas2552_weg_defs),
	.cache_type = WEGCACHE_WBTWEE,
};

static int tas2552_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev;
	stwuct tas2552_data *data;
	int wet;
	int i;

	dev = &cwient->dev;
	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	data->enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe",
						    GPIOD_OUT_WOW);
	if (IS_EWW(data->enabwe_gpio))
		wetuwn PTW_EWW(data->enabwe_gpio);

	data->tas2552_cwient = cwient;
	data->wegmap = devm_wegmap_init_i2c(cwient, &tas2552_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		wet = PTW_EWW(data->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(data->suppwies); i++)
		data->suppwies[i].suppwy = tas2552_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(data->suppwies),
				      data->suppwies);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev, 1000);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_mawk_wast_busy(&cwient->dev);
	pm_wuntime_put_sync_autosuspend(&cwient->dev);

	dev_set_dwvdata(&cwient->dev, data);

	wet = devm_snd_soc_wegistew_component(&cwient->dev,
				      &soc_component_dev_tas2552,
				      tas2552_dai, AWWAY_SIZE(tas2552_dai));
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wegistew component: %d\n", wet);
		pm_wuntime_get_nowesume(&cwient->dev);
	}

	wetuwn wet;
}

static void tas2552_i2c_wemove(stwuct i2c_cwient *cwient)
{
	pm_wuntime_disabwe(&cwient->dev);
}

static const stwuct i2c_device_id tas2552_id[] = {
	{ "tas2552", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tas2552_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id tas2552_of_match[] = {
	{ .compatibwe = "ti,tas2552", },
	{},
};
MODUWE_DEVICE_TABWE(of, tas2552_of_match);
#endif

static stwuct i2c_dwivew tas2552_i2c_dwivew = {
	.dwivew = {
		.name = "tas2552",
		.of_match_tabwe = of_match_ptw(tas2552_of_match),
		.pm = &tas2552_pm,
	},
	.pwobe = tas2552_pwobe,
	.wemove = tas2552_i2c_wemove,
	.id_tabwe = tas2552_id,
};

moduwe_i2c_dwivew(tas2552_i2c_dwivew);

MODUWE_AUTHOW("Dan Mupwhy <dmuwphy@ti.com>");
MODUWE_DESCWIPTION("TAS2552 Audio ampwifiew dwivew");
MODUWE_WICENSE("GPW");
