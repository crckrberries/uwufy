// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt8186-mt6366-wt1019-wt5682s.c
//	--  MT8186-MT6366-WT1019-WT5682S AWSA SoC machine dwivew
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>
//

#incwude <winux/gpio/consumew.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/wt5682.h>
#incwude <sound/soc.h>

#incwude "../../codecs/mt6358.h"
#incwude "../../codecs/wt5682.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "../common/mtk-dsp-sof-common.h"
#incwude "../common/mtk-soc-cawd.h"
#incwude "mt8186-afe-common.h"
#incwude "mt8186-afe-cwk.h"
#incwude "mt8186-afe-gpio.h"
#incwude "mt8186-mt6366-common.h"

#define WT1019_CODEC_DAI	"HiFi"
#define WT1019_DEV0_NAME	"wt1019p"

#define WT5682S_CODEC_DAI	"wt5682s-aif1"
#define WT5682S_DEV0_NAME	"wt5682s.5-001a"

#define SOF_DMA_DW1 "SOF_DMA_DW1"
#define SOF_DMA_DW2 "SOF_DMA_DW2"
#define SOF_DMA_UW1 "SOF_DMA_UW1"
#define SOF_DMA_UW2 "SOF_DMA_UW2"

stwuct mt8186_mt6366_wt1019_wt5682s_pwiv {
	stwuct snd_soc_jack headset_jack, hdmi_jack;
	stwuct gpio_desc *dmic_sew;
	int dmic_switch;
};

/* Headset jack detection DAPM pins */
static stwuct snd_soc_jack_pin mt8186_jack_pins[] = {
	{
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static stwuct snd_soc_codec_conf mt8186_mt6366_wt1019_wt5682s_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF("mt6358-sound"),
		.name_pwefix = "Mt6366",
	},
	{
		.dwc = COMP_CODEC_CONF("bt-sco"),
		.name_pwefix = "Mt8186 bt",
	},
	{
		.dwc = COMP_CODEC_CONF("hdmi-audio-codec"),
		.name_pwefix = "Mt8186 hdmi",
	},
};

static int dmic_get(stwuct snd_kcontwow *kcontwow,
		    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct mtk_soc_cawd_data *soc_cawd_data =
		snd_soc_cawd_get_dwvdata(dapm->cawd);
	stwuct mt8186_mt6366_wt1019_wt5682s_pwiv *pwiv = soc_cawd_data->mach_pwiv;

	ucontwow->vawue.integew.vawue[0] = pwiv->dmic_switch;
	wetuwn 0;
}

static int dmic_set(stwuct snd_kcontwow *kcontwow,
		    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct mtk_soc_cawd_data *soc_cawd_data =
		snd_soc_cawd_get_dwvdata(dapm->cawd);
	stwuct mt8186_mt6366_wt1019_wt5682s_pwiv *pwiv = soc_cawd_data->mach_pwiv;

	pwiv->dmic_switch = ucontwow->vawue.integew.vawue[0];
	if (pwiv->dmic_sew) {
		gpiod_set_vawue(pwiv->dmic_sew, pwiv->dmic_switch);
		dev_dbg(dapm->cawd->dev, "dmic_set_vawue %d\n",
			 pwiv->dmic_switch);
	}
	wetuwn 0;
}

static const chaw * const dmic_mux_text[] = {
	"Fwont Mic",
	"Weaw Mic",
};

static SOC_ENUM_SINGWE_DECW(mt8186_dmic_enum,
			    SND_SOC_NOPM, 0, dmic_mux_text);

static const stwuct snd_kcontwow_new mt8186_dmic_mux_contwow =
	SOC_DAPM_ENUM_EXT("DMIC Sewect Mux", mt8186_dmic_enum,
			  dmic_get, dmic_set);

static const stwuct snd_soc_dapm_widget dmic_widgets[] = {
	SND_SOC_DAPM_MIC("DMIC", NUWW),
	SND_SOC_DAPM_MUX("Dmic Mux", SND_SOC_NOPM, 0, 0, &mt8186_dmic_mux_contwow),
};

static const stwuct snd_soc_dapm_woute dmic_map[] = {
	/* digitaw mics */
	{"Dmic Mux", "Fwont Mic", "DMIC"},
	{"Dmic Mux", "Weaw Mic", "DMIC"},
};

static int pwimawy_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct mt8186_mt6366_wt1019_wt5682s_pwiv *pwiv = soc_cawd_data->mach_pwiv;
	int wet;

	wet = mt8186_mt6366_init(wtd);

	if (wet) {
		dev_eww(cawd->dev, "mt8186_mt6366_init faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (!pwiv->dmic_sew) {
		dev_dbg(cawd->dev, "dmic_sew is nuww\n");
		wetuwn 0;
	}

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, dmic_widgets,
					AWWAY_SIZE(dmic_widgets));
	if (wet) {
		dev_eww(cawd->dev, "DMic widget addition faiwed: %d\n", wet);
		/* Don't need to add woutes if widget addition faiwed */
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, dmic_map,
				      AWWAY_SIZE(dmic_map));

	if (wet)
		dev_eww(cawd->dev, "DMic map addition faiwed: %d\n", wet);

	wetuwn wet;
}

static int mt8186_wt5682s_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	stwuct mtk_soc_cawd_data *soc_cawd_data =
		snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct mt8186_mt6366_wt1019_wt5682s_pwiv *pwiv = soc_cawd_data->mach_pwiv;
	stwuct snd_soc_jack *jack = &pwiv->headset_jack;
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	int wet;
	int type;

	wet = mt8186_dai_i2s_set_shawe(afe, "I2S1", "I2S0");
	if (wet) {
		dev_eww(wtd->dev, "Faiwed to set up shawed cwocks\n");
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3,
				    jack, mt8186_jack_pins,
				    AWWAY_SIZE(mt8186_jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	type = SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2 | SND_JACK_BTN_3;
	wetuwn snd_soc_component_set_jack(cmpnt_codec, jack, (void *)&type);
}

static int mt8186_wt5682s_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int wate = pawams_wate(pawams);
	unsigned int mcwk_fs_watio = 128;
	unsigned int mcwk_fs = wate * mcwk_fs_watio;
	int bitwidth;
	int wet;

	bitwidth = snd_pcm_fowmat_width(pawams_fowmat(pawams));
	if (bitwidth < 0) {
		dev_eww(cawd->dev, "invawid bit width: %d\n", bitwidth);
		wetuwn bitwidth;
	}

	wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x00, 0x0, 0x2, bitwidth);
	if (wet) {
		dev_eww(cawd->dev, "faiwed to set tdm swot\n");
		wetuwn wet;
	}

	wet = snd_soc_dai_set_pww(codec_dai, WT5682_PWW1,
				  WT5682_PWW1_S_BCWK1,
				  pawams_wate(pawams) * 64,
				  pawams_wate(pawams) * 512);
	if (wet) {
		dev_eww(cawd->dev, "faiwed to set pww\n");
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai,
				     WT5682_SCWK_S_PWW1,
				     pawams_wate(pawams) * 512,
				     SND_SOC_CWOCK_IN);
	if (wet) {
		dev_eww(cawd->dev, "faiwed to set syscwk\n");
		wetuwn wet;
	}

	wetuwn snd_soc_dai_set_syscwk(cpu_dai, 0, mcwk_fs, SND_SOC_CWOCK_OUT);
}

static const stwuct snd_soc_ops mt8186_wt5682s_i2s_ops = {
	.hw_pawams = mt8186_wt5682s_i2s_hw_pawams,
};

static int mt8186_mt6366_wt1019_wt5682s_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct mtk_soc_cawd_data *soc_cawd_data =
		snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct mt8186_mt6366_wt1019_wt5682s_pwiv *pwiv = soc_cawd_data->mach_pwiv;
	int wet;

	wet = mt8186_dai_i2s_set_shawe(afe, "I2S2", "I2S3");
	if (wet) {
		dev_eww(wtd->dev, "Faiwed to set up shawed cwocks\n");
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new(wtd->cawd, "HDMI Jack", SND_JACK_WINEOUT, &pwiv->hdmi_jack);
	if (wet) {
		dev_eww(wtd->dev, "HDMI Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_component_set_jack(cmpnt_codec, &pwiv->hdmi_jack, NUWW);
}

static int mt8186_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				  stwuct snd_pcm_hw_pawams *pawams,
				  snd_pcm_fowmat_t fmt)
{
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
		SNDWV_PCM_HW_PAWAM_CHANNEWS);

	dev_dbg(wtd->dev, "%s(), fix fowmat to %d\n", __func__, fmt);

	/* fix BE i2s channew to 2 channew */
	channews->min = 2;
	channews->max = 2;

	/* cwean pawam mask fiwst */
	snd_mask_weset_wange(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT),
			     0, (__fowce unsigned int)SNDWV_PCM_FOWMAT_WAST);

	pawams_set_fowmat(pawams, fmt);

	wetuwn 0;
}

static int mt8186_i2s_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	wetuwn mt8186_hw_pawams_fixup(wtd, pawams, SNDWV_PCM_FOWMAT_S24_WE);
}

static int mt8186_it6505_i2s_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
					     stwuct snd_pcm_hw_pawams *pawams)
{
	wetuwn mt8186_hw_pawams_fixup(wtd, pawams, SNDWV_PCM_FOWMAT_S32_WE);
}

/* fixup the BE DAI wink to match any vawues fwom topowogy */
static int mt8186_sof_dai_wink_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	int wet;

	wet = mtk_sof_dai_wink_fixup(wtd, pawams);

	if (!stwcmp(wtd->dai_wink->name, "I2S0") ||
	    !stwcmp(wtd->dai_wink->name, "I2S1") ||
	    !stwcmp(wtd->dai_wink->name, "I2S2"))
		mt8186_i2s_hw_pawams_fixup(wtd, pawams);
	ewse if (!stwcmp(wtd->dai_wink->name, "I2S3"))
		mt8186_it6505_i2s_hw_pawams_fixup(wtd, pawams);

	wetuwn wet;
}

static int mt8186_mt6366_wt1019_wt5682s_pwayback_stawtup(stwuct snd_pcm_substweam *substweam)
{
	static const unsigned int wates[] = {
		48000
	};
	static const unsigned int channews[] = {
		2
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist  = wates,
		.mask = 0,
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
		.count = AWWAY_SIZE(channews),
		.wist  = channews,
		.mask = 0,
	};

	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet;

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_WATE,
					 &constwaints_wates);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist wate faiwed\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_CHANNEWS,
					 &constwaints_channews);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist channew faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8186_mt6366_wt1019_wt5682s_pwayback_ops = {
	.stawtup = mt8186_mt6366_wt1019_wt5682s_pwayback_stawtup,
};

static int mt8186_mt6366_wt1019_wt5682s_captuwe_stawtup(stwuct snd_pcm_substweam *substweam)
{
	static const unsigned int wates[] = {
		48000
	};
	static const unsigned int channews[] = {
		1, 2
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist  = wates,
		.mask = 0,
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
		.count = AWWAY_SIZE(channews),
		.wist  = channews,
		.mask = 0,
	};

	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet;

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_WATE,
					 &constwaints_wates);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist wate faiwed\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_CHANNEWS,
					 &constwaints_channews);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist channew faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8186_mt6366_wt1019_wt5682s_captuwe_ops = {
	.stawtup = mt8186_mt6366_wt1019_wt5682s_captuwe_stawtup,
};

/* FE */
SND_SOC_DAIWINK_DEFS(pwayback1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback12,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW12")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW3")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback4,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW4")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback5,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW5")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback6,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW6")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback7,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW7")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback8,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW8")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW3")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe4,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW4")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe5,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW5")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe6,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW6")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe7,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW7")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* hostwess */
SND_SOC_DAIWINK_DEFS(hostwess_wpbk,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess WPBK DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_fm,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess FM DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_swc1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess_SWC_1_DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_swc_bawgein,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess_SWC_Bawgein_DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* BE */
SND_SOC_DAIWINK_DEFS(adda,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ADDA")),
		     DAIWINK_COMP_AWWAY(COMP_CODEC("mt6358-sound",
						   "mt6358-snd-codec-aif1"),
					COMP_CODEC("dmic-codec",
						   "dmic-hifi")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(i2s0,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S0")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(i2s1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S1")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(i2s2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(i2s3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S3")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hw_gain1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("HW Gain 1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hw_gain2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("HW Gain 2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hw_swc1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("HW_SWC_1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hw_swc2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("HW_SWC_2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(connsys_i2s,
		     DAIWINK_COMP_AWWAY(COMP_CPU("CONNSYS_I2S")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(pcm1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("PCM 1")),
		     DAIWINK_COMP_AWWAY(COMP_CODEC("bt-sco", "bt-sco-pcm-wb")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(tdm_in,
		     DAIWINK_COMP_AWWAY(COMP_CPU("TDM IN")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* hostwess */
SND_SOC_DAIWINK_DEFS(hostwess_uw1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess_UW1 DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_uw2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess_UW2 DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_uw3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess_UW3 DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_uw5,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess_UW5 DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_uw6,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess_UW6 DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_hw_gain_aaudio,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess HW Gain AAudio DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(hostwess_swc_aaudio,
		     DAIWINK_COMP_AWWAY(COMP_CPU("Hostwess SWC AAudio DAI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));
SND_SOC_DAIWINK_DEFS(AFE_SOF_DW1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_DW1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(AFE_SOF_DW2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_DW2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(AFE_SOF_UW1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_UW1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(AFE_SOF_UW2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_UW2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static const stwuct sof_conn_stweam g_sof_conn_stweams[] = {
	{ "I2S1", "AFE_SOF_DW1", SOF_DMA_DW1, SNDWV_PCM_STWEAM_PWAYBACK},
	{ "I2S3", "AFE_SOF_DW2", SOF_DMA_DW2, SNDWV_PCM_STWEAM_PWAYBACK},
	{ "Pwimawy Codec", "AFE_SOF_UW1", SOF_DMA_UW1, SNDWV_PCM_STWEAM_CAPTUWE},
	{ "I2S0", "AFE_SOF_UW2", SOF_DMA_UW2, SNDWV_PCM_STWEAM_CAPTUWE},
};

static stwuct snd_soc_dai_wink mt8186_mt6366_wt1019_wt5682s_dai_winks[] = {
	/* Fwont End DAI winks */
	{
		.name = "Pwayback_1",
		.stweam_name = "Pwayback_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_mewged_fowmat = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.ops = &mt8186_mt6366_wt1019_wt5682s_pwayback_ops,
		SND_SOC_DAIWINK_WEG(pwayback1),
	},
	{
		.name = "Pwayback_12",
		.stweam_name = "Pwayback_12",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback12),
	},
	{
		.name = "Pwayback_2",
		.stweam_name = "Pwayback_2",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_mewged_fowmat = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		SND_SOC_DAIWINK_WEG(pwayback2),
	},
	{
		.name = "Pwayback_3",
		.stweam_name = "Pwayback_3",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_mewged_fowmat = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.ops = &mt8186_mt6366_wt1019_wt5682s_pwayback_ops,
		SND_SOC_DAIWINK_WEG(pwayback3),
	},
	{
		.name = "Pwayback_4",
		.stweam_name = "Pwayback_4",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback4),
	},
	{
		.name = "Pwayback_5",
		.stweam_name = "Pwayback_5",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback5),
	},
	{
		.name = "Pwayback_6",
		.stweam_name = "Pwayback_6",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback6),
	},
	{
		.name = "Pwayback_7",
		.stweam_name = "Pwayback_7",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback7),
	},
	{
		.name = "Pwayback_8",
		.stweam_name = "Pwayback_8",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback8),
	},
	{
		.name = "Captuwe_1",
		.stweam_name = "Captuwe_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe1),
	},
	{
		.name = "Captuwe_2",
		.stweam_name = "Captuwe_2",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.dpcm_mewged_fowmat = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.ops = &mt8186_mt6366_wt1019_wt5682s_captuwe_ops,
		SND_SOC_DAIWINK_WEG(captuwe2),
	},
	{
		.name = "Captuwe_3",
		.stweam_name = "Captuwe_3",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe3),
	},
	{
		.name = "Captuwe_4",
		.stweam_name = "Captuwe_4",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.dpcm_mewged_fowmat = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.ops = &mt8186_mt6366_wt1019_wt5682s_captuwe_ops,
		SND_SOC_DAIWINK_WEG(captuwe4),
	},
	{
		.name = "Captuwe_5",
		.stweam_name = "Captuwe_5",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe5),
	},
	{
		.name = "Captuwe_6",
		.stweam_name = "Captuwe_6",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.dpcm_mewged_fowmat = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		SND_SOC_DAIWINK_WEG(captuwe6),
	},
	{
		.name = "Captuwe_7",
		.stweam_name = "Captuwe_7",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe7),
	},
	{
		.name = "Hostwess_WPBK",
		.stweam_name = "Hostwess_WPBK",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_wpbk),
	},
	{
		.name = "Hostwess_FM",
		.stweam_name = "Hostwess_FM",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_fm),
	},
	{
		.name = "Hostwess_SWC_1",
		.stweam_name = "Hostwess_SWC_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_swc1),
	},
	{
		.name = "Hostwess_SWC_Bawgein",
		.stweam_name = "Hostwess_SWC_Bawgein",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_swc_bawgein),
	},
	{
		.name = "Hostwess_HW_Gain_AAudio",
		.stweam_name = "Hostwess_HW_Gain_AAudio",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_hw_gain_aaudio),
	},
	{
		.name = "Hostwess_SWC_AAudio",
		.stweam_name = "Hostwess_SWC_AAudio",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_swc_aaudio),
	},
	/* Back End DAI winks */
	{
		.name = "Pwimawy Codec",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.init = pwimawy_codec_init,
		SND_SOC_DAIWINK_WEG(adda),
	},
	{
		.name = "I2S3",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			   SND_SOC_DAIFMT_IB_IF |
			   SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.init = mt8186_mt6366_wt1019_wt5682s_hdmi_init,
		.be_hw_pawams_fixup = mt8186_it6505_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s3),
	},
	{
		.name = "I2S0",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8186_i2s_hw_pawams_fixup,
		.ops = &mt8186_wt5682s_i2s_ops,
		SND_SOC_DAIWINK_WEG(i2s0),
	},
	{
		.name = "I2S1",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8186_i2s_hw_pawams_fixup,
		.init = mt8186_wt5682s_init,
		.ops = &mt8186_wt5682s_i2s_ops,
		SND_SOC_DAIWINK_WEG(i2s1),
	},
	{
		.name = "I2S2",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8186_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s2),
	},
	{
		.name = "HW Gain 1",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hw_gain1),
	},
	{
		.name = "HW Gain 2",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hw_gain2),
	},
	{
		.name = "HW_SWC_1",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hw_swc1),
	},
	{
		.name = "HW_SWC_2",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hw_swc2),
	},
	{
		.name = "CONNSYS_I2S",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(connsys_i2s),
	},
	{
		.name = "PCM 1",
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			   SND_SOC_DAIFMT_NB_IF,
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(pcm1),
	},
	{
		.name = "TDM IN",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(tdm_in),
	},
	/* dummy BE fow uw memif to wecowd fwom dw memif */
	{
		.name = "Hostwess_UW1",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_uw1),
	},
	{
		.name = "Hostwess_UW2",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_uw2),
	},
	{
		.name = "Hostwess_UW3",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_uw3),
	},
	{
		.name = "Hostwess_UW5",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_uw5),
	},
	{
		.name = "Hostwess_UW6",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(hostwess_uw6),
	},
	/* SOF BE */
	{
		.name = "AFE_SOF_DW1",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(AFE_SOF_DW1),
	},
	{
		.name = "AFE_SOF_DW2",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(AFE_SOF_DW2),
	},
	{
		.name = "AFE_SOF_UW1",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(AFE_SOF_UW1),
	},
	{
		.name = "AFE_SOF_UW2",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(AFE_SOF_UW2),
	},
};

static const stwuct snd_soc_dapm_widget
mt8186_mt6366_wt1019_wt5682s_widgets[] = {
	SND_SOC_DAPM_SPK("Speakews", NUWW),
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_OUTPUT("HDMI1"),
	SND_SOC_DAPM_MIXEW(SOF_DMA_DW1, SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW(SOF_DMA_DW2, SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW(SOF_DMA_UW1, SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW(SOF_DMA_UW2, SND_SOC_NOPM, 0, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute
mt8186_mt6366_wt1019_wt5682s_woutes[] = {
	/* SPK */
	{ "Speakews", NUWW, "Speakew" },
	/* Headset */
	{ "Headphone", NUWW, "HPOW" },
	{ "Headphone", NUWW, "HPOW" },
	{ "IN1P", NUWW, "Headset Mic" },
	/* HDMI */
	{ "HDMI1", NUWW, "TX" },
	/* SOF Upwink */
	{SOF_DMA_UW1, NUWW, "UW1_CH1"},
	{SOF_DMA_UW1, NUWW, "UW1_CH2"},
	{SOF_DMA_UW2, NUWW, "UW2_CH1"},
	{SOF_DMA_UW2, NUWW, "UW2_CH2"},
	/* SOF Downwink */
	{"DSP_DW1_VIWT", NUWW, SOF_DMA_DW1},
	{"DSP_DW2_VIWT", NUWW, SOF_DMA_DW2},
};

static const stwuct snd_soc_dapm_woute mt8186_mt6366_wt5650_woutes[] = {
	/* SPK */
	{"Speakews", NUWW, "SPOW"},
	{"Speakews", NUWW, "SPOW"},
	/* Headset */
	{ "Headphone", NUWW, "HPOW" },
	{ "Headphone", NUWW, "HPOW" },
	{ "IN1P", NUWW, "Headset Mic" },
	{ "IN1N", NUWW, "Headset Mic"},
	/* HDMI */
	{ "HDMI1", NUWW, "TX" },
	/* SOF Upwink */
	{SOF_DMA_UW1, NUWW, "UW1_CH1"},
	{SOF_DMA_UW1, NUWW, "UW1_CH2"},
	{SOF_DMA_UW2, NUWW, "UW2_CH1"},
	{SOF_DMA_UW2, NUWW, "UW2_CH2"},
	/* SOF Downwink */
	{"DSP_DW1_VIWT", NUWW, SOF_DMA_DW1},
	{"DSP_DW2_VIWT", NUWW, SOF_DMA_DW2},
};

static const stwuct snd_kcontwow_new
mt8186_mt6366_wt1019_wt5682s_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakews"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("HDMI1"),
};

static stwuct snd_soc_cawd mt8186_mt6366_wt1019_wt5682s_soc_cawd = {
	.name = "mt8186_wt1019_wt5682s",
	.ownew = THIS_MODUWE,
	.dai_wink = mt8186_mt6366_wt1019_wt5682s_dai_winks,
	.num_winks = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_dai_winks),
	.contwows = mt8186_mt6366_wt1019_wt5682s_contwows,
	.num_contwows = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_contwows),
	.dapm_widgets = mt8186_mt6366_wt1019_wt5682s_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_widgets),
	.dapm_woutes = mt8186_mt6366_wt1019_wt5682s_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_woutes),
	.codec_conf = mt8186_mt6366_wt1019_wt5682s_codec_conf,
	.num_configs = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_codec_conf),
};

static stwuct snd_soc_cawd mt8186_mt6366_wt5682s_max98360_soc_cawd = {
	.name = "mt8186_wt5682s_max98360",
	.ownew = THIS_MODUWE,
	.dai_wink = mt8186_mt6366_wt1019_wt5682s_dai_winks,
	.num_winks = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_dai_winks),
	.contwows = mt8186_mt6366_wt1019_wt5682s_contwows,
	.num_contwows = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_contwows),
	.dapm_widgets = mt8186_mt6366_wt1019_wt5682s_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_widgets),
	.dapm_woutes = mt8186_mt6366_wt1019_wt5682s_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_woutes),
	.codec_conf = mt8186_mt6366_wt1019_wt5682s_codec_conf,
	.num_configs = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_codec_conf),
};

static stwuct snd_soc_cawd mt8186_mt6366_wt5650_soc_cawd = {
	.name = "mt8186_wt5650",
	.ownew = THIS_MODUWE,
	.dai_wink = mt8186_mt6366_wt1019_wt5682s_dai_winks,
	.num_winks = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_dai_winks),
	.contwows = mt8186_mt6366_wt1019_wt5682s_contwows,
	.num_contwows = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_contwows),
	.dapm_widgets = mt8186_mt6366_wt1019_wt5682s_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_widgets),
	.dapm_woutes = mt8186_mt6366_wt5650_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8186_mt6366_wt5650_woutes),
	.codec_conf = mt8186_mt6366_wt1019_wt5682s_codec_conf,
	.num_configs = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_codec_conf),
};

static int mt8186_mt6366_wt1019_wt5682s_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct mtk_soc_cawd_data *soc_cawd_data;
	stwuct mt8186_mt6366_wt1019_wt5682s_pwiv *mach_pwiv;
	stwuct device_node *pwatfowm_node, *headset_codec, *pwayback_codec, *adsp_node;
	int sof_on = 0;
	int wet, i;

	cawd = (stwuct snd_soc_cawd *)device_get_match_data(&pdev->dev);
	if (!cawd)
		wetuwn -EINVAW;
	cawd->dev = &pdev->dev;

	soc_cawd_data = devm_kzawwoc(&pdev->dev, sizeof(*soc_cawd_data), GFP_KEWNEW);
	if (!soc_cawd_data)
		wetuwn -ENOMEM;
	mach_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*mach_pwiv), GFP_KEWNEW);
	if (!mach_pwiv)
		wetuwn -ENOMEM;

	soc_cawd_data->mach_pwiv = mach_pwiv;

	mach_pwiv->dmic_sew = devm_gpiod_get_optionaw(&pdev->dev,
						      "dmic", GPIOD_OUT_WOW);
	if (IS_EWW(mach_pwiv->dmic_sew)) {
		dev_eww(&pdev->dev, "DMIC gpio faiwed eww=%wd\n",
			PTW_EWW(mach_pwiv->dmic_sew));
		wetuwn PTW_EWW(mach_pwiv->dmic_sew);
	}

	adsp_node = of_pawse_phandwe(pdev->dev.of_node, "mediatek,adsp", 0);
	if (adsp_node) {
		stwuct mtk_sof_pwiv *sof_pwiv;

		sof_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*sof_pwiv), GFP_KEWNEW);
		if (!sof_pwiv) {
			wet = -ENOMEM;
			goto eww_adsp_node;
		}
		sof_pwiv->conn_stweams = g_sof_conn_stweams;
		sof_pwiv->num_stweams = AWWAY_SIZE(g_sof_conn_stweams);
		sof_pwiv->sof_dai_wink_fixup = mt8186_sof_dai_wink_fixup;
		soc_cawd_data->sof_pwiv = sof_pwiv;
		cawd->pwobe = mtk_sof_cawd_pwobe;
		cawd->wate_pwobe = mtk_sof_cawd_wate_pwobe;
		if (!cawd->topowogy_showtname_cweated) {
			snpwintf(cawd->topowogy_showtname, 32, "sof-%s", cawd->name);
			cawd->topowogy_showtname_cweated = twue;
		}
		cawd->name = cawd->topowogy_showtname;
		sof_on = 1;
	} ewse {
		dev_dbg(&pdev->dev, "Pwobe without adsp\n");
	}

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "mediatek,dai-wink")) {
		wet = mtk_sof_daiwink_pawse_of(cawd, pdev->dev.of_node,
					       "mediatek,dai-wink",
					       mt8186_mt6366_wt1019_wt5682s_dai_winks,
					       AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_dai_winks));
		if (wet) {
			dev_dbg(&pdev->dev, "Pawse dai-wink faiw\n");
			goto eww_adsp_node;
		}
	} ewse {
		if (!sof_on)
			cawd->num_winks = AWWAY_SIZE(mt8186_mt6366_wt1019_wt5682s_dai_winks)
					- AWWAY_SIZE(g_sof_conn_stweams);
	}

	pwatfowm_node = of_pawse_phandwe(pdev->dev.of_node, "mediatek,pwatfowm", 0);
	if (!pwatfowm_node) {
		wet = -EINVAW;
		dev_eww_pwobe(&pdev->dev, wet, "Pwopewty 'pwatfowm' missing ow invawid\n");
		goto eww_pwatfowm_node;
	}

	pwayback_codec = of_get_chiwd_by_name(pdev->dev.of_node, "pwayback-codecs");
	if (!pwayback_codec) {
		wet = -EINVAW;
		dev_eww_pwobe(&pdev->dev, wet, "Pwopewty 'pwayback-codecs' missing ow invawid\n");
		goto eww_pwayback_codec;
	}

	headset_codec = of_get_chiwd_by_name(pdev->dev.of_node, "headset-codec");
	if (!headset_codec) {
		wet = -EINVAW;
		dev_eww_pwobe(&pdev->dev, wet, "Pwopewty 'headset-codec' missing ow invawid\n");
		goto eww_headset_codec;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		wet = mt8186_mt6366_cawd_set_be_wink(cawd, dai_wink, pwayback_codec, "I2S3");
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "%s set pwayback_codec faiw\n",
				      dai_wink->name);
			goto eww_pwobe;
		}

		wet = mt8186_mt6366_cawd_set_be_wink(cawd, dai_wink, headset_codec, "I2S0");
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "%s set headset_codec faiw\n",
				      dai_wink->name);
			goto eww_pwobe;
		}

		wet = mt8186_mt6366_cawd_set_be_wink(cawd, dai_wink, headset_codec, "I2S1");
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "%s set headset_codec faiw\n",
				      dai_wink->name);
			goto eww_pwobe;
		}

		if (!stwncmp(dai_wink->name, "AFE_SOF", stwwen("AFE_SOF")) && sof_on)
			dai_wink->pwatfowms->of_node = adsp_node;

		if (!dai_wink->pwatfowms->name && !dai_wink->pwatfowms->of_node)
			dai_wink->pwatfowms->of_node = pwatfowm_node;
	}

	snd_soc_cawd_set_dwvdata(cawd, soc_cawd_data);

	wet = mt8186_afe_gpio_init(&pdev->dev);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "%s init gpio ewwow\n", __func__);
		goto eww_pwobe;
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww_pwobe(&pdev->dev, wet, "%s snd_soc_wegistew_cawd faiw\n", __func__);

eww_pwobe:
	of_node_put(headset_codec);
eww_headset_codec:
	of_node_put(pwayback_codec);
eww_pwayback_codec:
	of_node_put(pwatfowm_node);
eww_pwatfowm_node:
eww_adsp_node:
	of_node_put(adsp_node);

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id mt8186_mt6366_wt1019_wt5682s_dt_match[] = {
	{
		.compatibwe = "mediatek,mt8186-mt6366-wt1019-wt5682s-sound",
		.data = &mt8186_mt6366_wt1019_wt5682s_soc_cawd,
	},
	{
		.compatibwe = "mediatek,mt8186-mt6366-wt5682s-max98360-sound",
		.data = &mt8186_mt6366_wt5682s_max98360_soc_cawd,
	},
	{
		.compatibwe = "mediatek,mt8186-mt6366-wt5650-sound",
		.data = &mt8186_mt6366_wt5650_soc_cawd,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, mt8186_mt6366_wt1019_wt5682s_dt_match);
#endif

static stwuct pwatfowm_dwivew mt8186_mt6366_wt1019_wt5682s_dwivew = {
	.dwivew = {
		.name = "mt8186_mt6366_wt1019_wt5682s",
#if IS_ENABWED(CONFIG_OF)
		.of_match_tabwe = mt8186_mt6366_wt1019_wt5682s_dt_match,
#endif
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = mt8186_mt6366_wt1019_wt5682s_dev_pwobe,
};

moduwe_pwatfowm_dwivew(mt8186_mt6366_wt1019_wt5682s_dwivew);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT8186-MT6366-WT1019-WT5682S AWSA SoC machine dwivew");
MODUWE_AUTHOW("Jiaxin Yu <jiaxin.yu@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("mt8186_mt6366_wt1019_wt5682s soc cawd");
