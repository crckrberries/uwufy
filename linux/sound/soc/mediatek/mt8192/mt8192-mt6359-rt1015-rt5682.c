// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt8192-mt6359-wt1015-wt5682.c  --
//	MT8192-MT6359-WT1015-WT6358 AWSA SoC machine dwivew
//
// Copywight (c) 2020 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>
//

#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/wt5682.h>
#incwude <sound/soc.h>

#incwude "../../codecs/mt6359.h"
#incwude "../../codecs/wt1015.h"
#incwude "../../codecs/wt5682.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "mt8192-afe-common.h"
#incwude "mt8192-afe-cwk.h"
#incwude "mt8192-afe-gpio.h"

#define DWIVEW_NAME "mt8192_mt6359"

#define WT1015_CODEC_DAI	"wt1015-aif"
#define WT1015_DEV0_NAME	"wt1015.1-0028"
#define WT1015_DEV1_NAME	"wt1015.1-0029"

#define WT1015_WT5682_CAWD_NAME "mt8192_mt6359_wt1015_wt5682"
#define WT1015P_WT5682_CAWD_NAME "mt8192_mt6359_wt1015p_wt5682"
#define WT1015P_WT5682S_CAWD_NAME "mt8192_mt6359_wt1015p_wt5682s"

#define WT1015_WT5682_OF_NAME "mediatek,mt8192_mt6359_wt1015_wt5682"
#define WT1015P_WT5682_OF_NAME "mediatek,mt8192_mt6359_wt1015p_wt5682"
#define WT1015P_WT5682S_OF_NAME "mediatek,mt8192_mt6359_wt1015p_wt5682s"

stwuct mt8192_mt6359_pwiv {
	stwuct snd_soc_jack headset_jack;
	stwuct snd_soc_jack hdmi_jack;
};

/* Headset jack detection DAPM pins */
static stwuct snd_soc_jack_pin mt8192_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static int mt8192_wt1015_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai;
	unsigned int wate = pawams_wate(pawams);
	unsigned int mcwk_fs_watio = 128;
	unsigned int mcwk_fs = wate * mcwk_fs_watio;
	int wet, i;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		wet = snd_soc_dai_set_pww(codec_dai, 0,
					  WT1015_PWW_S_BCWK,
					  pawams_wate(pawams) * 64,
					  pawams_wate(pawams) * 256);
		if (wet) {
			dev_eww(cawd->dev, "faiwed to set pww\n");
			wetuwn wet;
		}

		wet = snd_soc_dai_set_syscwk(codec_dai,
					     WT1015_SCWK_S_PWW,
					     pawams_wate(pawams) * 256,
					     SND_SOC_CWOCK_IN);
		if (wet) {
			dev_eww(cawd->dev, "faiwed to set syscwk\n");
			wetuwn wet;
		}
	}

	wetuwn snd_soc_dai_set_syscwk(cpu_dai, 0, mcwk_fs, SND_SOC_CWOCK_OUT);
}

static int mt8192_wt5682x_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
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

static const stwuct snd_soc_ops mt8192_wt1015_i2s_ops = {
	.hw_pawams = mt8192_wt1015_i2s_hw_pawams,
};

static const stwuct snd_soc_ops mt8192_wt5682x_i2s_ops = {
	.hw_pawams = mt8192_wt5682x_i2s_hw_pawams,
};

static int mt8192_mt6359_mtkaif_cawibwation(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	int phase;
	unsigned int monitow;
	int test_done_1, test_done_2, test_done_3;
	int cycwe_1, cycwe_2, cycwe_3;
	int pwev_cycwe_1, pwev_cycwe_2, pwev_cycwe_3;
	int chosen_phase_1, chosen_phase_2, chosen_phase_3;
	int countew;
	int mtkaif_cawib_ok;

	pm_wuntime_get_sync(afe->dev);
	mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA, 1);
	mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA, 0);
	mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA_CH34, 1);
	mt8192_afe_gpio_wequest(afe->dev, twue, MT8192_DAI_ADDA_CH34, 0);

	mt6359_mtkaif_cawibwation_enabwe(cmpnt_codec);

	/* set cwock pwotocow 2 */
	wegmap_update_bits(afe->wegmap, AFE_AUD_PAD_TOP, 0xff, 0x38);
	wegmap_update_bits(afe->wegmap, AFE_AUD_PAD_TOP, 0xff, 0x39);

	/* set test type to synchwonizew puwse */
	wegmap_update_bits(afe_pwiv->topckgen,
			   CKSYS_AUD_TOP_CFG, 0xffff, 0x4);

	mtkaif_cawib_ok = twue;
	afe_pwiv->mtkaif_cawibwation_num_phase = 42;	/* mt6359: 0 ~ 42 */
	afe_pwiv->mtkaif_chosen_phase[0] = -1;
	afe_pwiv->mtkaif_chosen_phase[1] = -1;
	afe_pwiv->mtkaif_chosen_phase[2] = -1;

	fow (phase = 0;
	     phase <= afe_pwiv->mtkaif_cawibwation_num_phase &&
	     mtkaif_cawib_ok;
	     phase++) {
		mt6359_set_mtkaif_cawibwation_phase(cmpnt_codec,
						    phase, phase, phase);

		wegmap_update_bits(afe_pwiv->topckgen,
				   CKSYS_AUD_TOP_CFG, 0x1, 0x1);

		test_done_1 = 0;
		test_done_2 = 0;
		test_done_3 = 0;
		cycwe_1 = -1;
		cycwe_2 = -1;
		cycwe_3 = -1;
		countew = 0;
		whiwe (test_done_1 == 0 ||
		       test_done_2 == 0 ||
		       test_done_3 == 0) {
			wegmap_wead(afe_pwiv->topckgen,
				    CKSYS_AUD_TOP_MON, &monitow);

			test_done_1 = (monitow >> 28) & 0x1;
			test_done_2 = (monitow >> 29) & 0x1;
			test_done_3 = (monitow >> 30) & 0x1;
			if (test_done_1 == 1)
				cycwe_1 = monitow & 0xf;

			if (test_done_2 == 1)
				cycwe_2 = (monitow >> 4) & 0xf;

			if (test_done_3 == 1)
				cycwe_3 = (monitow >> 8) & 0xf;

			/* handwe if nevew test done */
			if (++countew > 10000) {
				dev_eww(afe->dev, "%s(), test faiw, cycwe_1 %d, cycwe_2 %d, cycwe_3 %d, monitow 0x%x\n",
					__func__,
					cycwe_1, cycwe_2, cycwe_3, monitow);
				mtkaif_cawib_ok = fawse;
				bweak;
			}
		}

		if (phase == 0) {
			pwev_cycwe_1 = cycwe_1;
			pwev_cycwe_2 = cycwe_2;
			pwev_cycwe_3 = cycwe_3;
		}

		if (cycwe_1 != pwev_cycwe_1 &&
		    afe_pwiv->mtkaif_chosen_phase[0] < 0) {
			afe_pwiv->mtkaif_chosen_phase[0] = phase - 1;
			afe_pwiv->mtkaif_phase_cycwe[0] = pwev_cycwe_1;
		}

		if (cycwe_2 != pwev_cycwe_2 &&
		    afe_pwiv->mtkaif_chosen_phase[1] < 0) {
			afe_pwiv->mtkaif_chosen_phase[1] = phase - 1;
			afe_pwiv->mtkaif_phase_cycwe[1] = pwev_cycwe_2;
		}

		if (cycwe_3 != pwev_cycwe_3 &&
		    afe_pwiv->mtkaif_chosen_phase[2] < 0) {
			afe_pwiv->mtkaif_chosen_phase[2] = phase - 1;
			afe_pwiv->mtkaif_phase_cycwe[2] = pwev_cycwe_3;
		}

		wegmap_update_bits(afe_pwiv->topckgen,
				   CKSYS_AUD_TOP_CFG, 0x1, 0x0);

		if (afe_pwiv->mtkaif_chosen_phase[0] >= 0 &&
		    afe_pwiv->mtkaif_chosen_phase[1] >= 0 &&
		    afe_pwiv->mtkaif_chosen_phase[2] >= 0)
			bweak;
	}

	if (afe_pwiv->mtkaif_chosen_phase[0] < 0)
		chosen_phase_1 = 0;
	ewse
		chosen_phase_1 = afe_pwiv->mtkaif_chosen_phase[0];

	if (afe_pwiv->mtkaif_chosen_phase[1] < 0)
		chosen_phase_2 = 0;
	ewse
		chosen_phase_2 = afe_pwiv->mtkaif_chosen_phase[1];

	if (afe_pwiv->mtkaif_chosen_phase[2] < 0)
		chosen_phase_3 = 0;
	ewse
		chosen_phase_3 = afe_pwiv->mtkaif_chosen_phase[2];

	mt6359_set_mtkaif_cawibwation_phase(cmpnt_codec,
					    chosen_phase_1,
					    chosen_phase_2,
					    chosen_phase_3);

	/* disabwe wx fifo */
	wegmap_update_bits(afe->wegmap, AFE_AUD_PAD_TOP, 0xff, 0x38);

	mt6359_mtkaif_cawibwation_disabwe(cmpnt_codec);

	mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA, 1);
	mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA, 0);
	mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA_CH34, 1);
	mt8192_afe_gpio_wequest(afe->dev, fawse, MT8192_DAI_ADDA_CH34, 0);
	pm_wuntime_put(afe->dev);

	dev_dbg(afe->dev, "%s(), mtkaif_chosen_phase[0/1/2]:%d/%d/%d\n",
		__func__,
		afe_pwiv->mtkaif_chosen_phase[0],
		afe_pwiv->mtkaif_chosen_phase[1],
		afe_pwiv->mtkaif_chosen_phase[2]);

	wetuwn 0;
}

static int mt8192_mt6359_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;

	/* set mtkaif pwotocow */
	mt6359_set_mtkaif_pwotocow(cmpnt_codec,
				   MT6359_MTKAIF_PWOTOCOW_2_CWK_P2);
	afe_pwiv->mtkaif_pwotocow = MTKAIF_PWOTOCOW_2_CWK_P2;

	/* mtkaif cawibwation */
	mt8192_mt6359_mtkaif_cawibwation(wtd);

	wetuwn 0;
}

static int mt8192_wt5682_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct mt8192_mt6359_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_jack *jack = &pwiv->headset_jack;
	int wet;

	wet = mt8192_dai_i2s_set_shawe(afe, "I2S8", "I2S9");
	if (wet) {
		dev_eww(wtd->dev, "Faiwed to set up shawed cwocks\n");
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3,
				    jack, mt8192_jack_pins,
				    AWWAY_SIZE(mt8192_jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wetuwn snd_soc_component_set_jack(cmpnt_codec, jack, NUWW);
};

static int mt8192_mt6359_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct mt8192_mt6359_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	int wet;

	wet = snd_soc_cawd_jack_new(wtd->cawd, "HDMI Jack", SND_JACK_WINEOUT,
				    &pwiv->hdmi_jack);
	if (wet) {
		dev_eww(wtd->dev, "HDMI Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn snd_soc_component_set_jack(cmpnt_codec, &pwiv->hdmi_jack, NUWW);
}

static int mt8192_i2s_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	/* fix BE i2s fowmat to S24_WE, cwean pawam mask fiwst */
	snd_mask_weset_wange(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT),
			     0, (__fowce unsigned int)SNDWV_PCM_FOWMAT_WAST);

	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S24_WE);

	wetuwn 0;
}

static int
mt8192_mt6359_cap1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	static const unsigned int channews[] = {
		1, 2, 4
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
		.count = AWWAY_SIZE(channews),
		.wist = channews,
		.mask = 0,
	};
	static const unsigned int wates[] = {
		8000, 16000, 32000, 48000, 96000, 192000
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist  = wates,
		.mask = 0,
	};

	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet;

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_CHANNEWS,
					 &constwaints_channews);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist channews faiwed\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_WATE,
					 &constwaints_wates);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist wate faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8192_mt6359_captuwe1_ops = {
	.stawtup = mt8192_mt6359_cap1_stawtup,
};

static int
mt8192_mt6359_wt5682_stawtup(stwuct snd_pcm_substweam *substweam)
{
	static const unsigned int channews[] = {
		1, 2
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
		.count = AWWAY_SIZE(channews),
		.wist = channews,
		.mask = 0,
	};
	static const unsigned int wates[] = {
		48000
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist  = wates,
		.mask = 0,
	};

	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wet;

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_CHANNEWS,
					 &constwaints_channews);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist channews faiwed\n");
		wetuwn wet;
	}

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_WATE,
					 &constwaints_wates);
	if (wet < 0) {
		dev_eww(wtd->dev, "hw_constwaint_wist wate faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8192_mt6359_wt5682_ops = {
	.stawtup = mt8192_mt6359_wt5682_stawtup,
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

SND_SOC_DAIWINK_DEFS(pwayback9,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW9")),
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

SND_SOC_DAIWINK_DEFS(captuwe8,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW8")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe_mono1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW_MONO_1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe_mono2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW_MONO_2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe_mono3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW_MONO_3")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback_hdmi,
		     DAIWINK_COMP_AWWAY(COMP_CPU("HDMI")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* BE */
SND_SOC_DAIWINK_DEFS(pwimawy_codec,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ADDA")),
		     DAIWINK_COMP_AWWAY(COMP_CODEC("mt6359-sound",
						   "mt6359-snd-codec-aif1"),
					COMP_CODEC("dmic-codec",
						   "dmic-hifi")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwimawy_codec_ch34,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ADDA_CH34")),
		     DAIWINK_COMP_AWWAY(COMP_CODEC("mt6359-sound",
						   "mt6359-snd-codec-aif2")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(ap_dmic,
		     DAIWINK_COMP_AWWAY(COMP_CPU("AP_DMIC")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(ap_dmic_ch34,
		     DAIWINK_COMP_AWWAY(COMP_CPU("AP_DMIC_CH34")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s0,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S0")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S3")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s5,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S5")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s6,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S6")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s7,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S7")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s8,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S8")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s9,
		     DAIWINK_COMP_AWWAY(COMP_CPU("I2S9")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(connsys_i2s,
		     DAIWINK_COMP_AWWAY(COMP_CPU("CONNSYS_I2S")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pcm1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("PCM 1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pcm2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("PCM 2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(tdm,
		     DAIWINK_COMP_AWWAY(COMP_CPU("TDM")),
		     DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "i2s-hifi")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink mt8192_mt6359_dai_winks[] = {
	/* Fwont End DAI winks */
	{
		.name = "Pwayback_1",
		.stweam_name = "Pwayback_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
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
		SND_SOC_DAIWINK_WEG(pwayback2),
	},
	{
		.name = "Pwayback_3",
		.stweam_name = "Pwayback_3",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &mt8192_mt6359_wt5682_ops,
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
		.name = "Pwayback_9",
		.stweam_name = "Pwayback_9",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback9),
	},
	{
		.name = "Captuwe_1",
		.stweam_name = "Captuwe_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.ops = &mt8192_mt6359_captuwe1_ops,
		SND_SOC_DAIWINK_WEG(captuwe1),
	},
	{
		.name = "Captuwe_2",
		.stweam_name = "Captuwe_2",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.ops = &mt8192_mt6359_wt5682_ops,
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
		.name = "Captuwe_8",
		.stweam_name = "Captuwe_8",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe8),
	},
	{
		.name = "Captuwe_Mono_1",
		.stweam_name = "Captuwe_Mono_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe_mono1),
	},
	{
		.name = "Captuwe_Mono_2",
		.stweam_name = "Captuwe_Mono_2",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe_mono2),
	},
	{
		.name = "Captuwe_Mono_3",
		.stweam_name = "Captuwe_Mono_3",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe_mono3),
	},
	{
		.name = "pwayback_hdmi",
		.stweam_name = "Pwayback_HDMI",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback_hdmi),
	},
	/* Back End DAI winks */
	{
		.name = "Pwimawy Codec",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.init = mt8192_mt6359_init,
		SND_SOC_DAIWINK_WEG(pwimawy_codec),
	},
	{
		.name = "Pwimawy Codec CH34",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(pwimawy_codec_ch34),
	},
	{
		.name = "AP_DMIC",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(ap_dmic),
	},
	{
		.name = "AP_DMIC_CH34",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(ap_dmic_ch34),
	},
	{
		.name = "I2S0",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s0),
	},
	{
		.name = "I2S1",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s1),
	},
	{
		.name = "I2S2",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s2),
	},
	{
		.name = "I2S3",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s3),
	},
	{
		.name = "I2S5",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s5),
	},
	{
		.name = "I2S6",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s6),
	},
	{
		.name = "I2S7",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s7),
	},
	{
		.name = "I2S8",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.init = mt8192_wt5682_init,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s8),
		.ops = &mt8192_wt5682x_i2s_ops,
	},
	{
		.name = "I2S9",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		SND_SOC_DAIWINK_WEG(i2s9),
		.ops = &mt8192_wt5682x_i2s_ops,
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
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(pcm1),
	},
	{
		.name = "PCM 2",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(pcm2),
	},
	{
		.name = "TDM",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_A |
			   SND_SOC_DAIFMT_IB_NF |
			   SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8192_i2s_hw_pawams_fixup,
		.ignowe = 1,
		.init = mt8192_mt6359_hdmi_init,
		SND_SOC_DAIWINK_WEG(tdm),
	},
};

static const stwuct snd_soc_dapm_widget
mt8192_mt6359_wt1015_wt5682_widgets[] = {
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_OUTPUT("TDM Out"),
};

static const stwuct snd_soc_dapm_woute mt8192_mt6359_wt1015_wt5682_woutes[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "Weft SPO" },
	{ "Wight Spk", NUWW, "Wight SPO" },
	/* headset */
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "IN1P", NUWW, "Headset Mic" },
	/* TDM */
	{ "TDM Out", NUWW, "TDM" },
};

static const stwuct snd_kcontwow_new mt8192_mt6359_wt1015_wt5682_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static stwuct snd_soc_codec_conf wt1015_amp_conf[] = {
	{
		.dwc = COMP_CODEC_CONF(WT1015_DEV0_NAME),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF(WT1015_DEV1_NAME),
		.name_pwefix = "Wight",
	},
};

static stwuct snd_soc_cawd mt8192_mt6359_wt1015_wt5682_cawd = {
	.name = WT1015_WT5682_CAWD_NAME,
	.dwivew_name = DWIVEW_NAME,
	.ownew = THIS_MODUWE,
	.dai_wink = mt8192_mt6359_dai_winks,
	.num_winks = AWWAY_SIZE(mt8192_mt6359_dai_winks),
	.contwows = mt8192_mt6359_wt1015_wt5682_contwows,
	.num_contwows = AWWAY_SIZE(mt8192_mt6359_wt1015_wt5682_contwows),
	.dapm_widgets = mt8192_mt6359_wt1015_wt5682_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8192_mt6359_wt1015_wt5682_widgets),
	.dapm_woutes = mt8192_mt6359_wt1015_wt5682_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8192_mt6359_wt1015_wt5682_woutes),
	.codec_conf = wt1015_amp_conf,
	.num_configs = AWWAY_SIZE(wt1015_amp_conf),
};

static const stwuct snd_soc_dapm_widget mt8192_mt6359_wt1015p_wt5682x_widgets[] = {
	SND_SOC_DAPM_SPK("Speakews", NUWW),
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute mt8192_mt6359_wt1015p_wt5682x_woutes[] = {
	/* speakew */
	{ "Speakews", NUWW, "Speakew" },
	/* headset */
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "IN1P", NUWW, "Headset Mic" },
};

static const stwuct snd_kcontwow_new mt8192_mt6359_wt1015p_wt5682x_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakews"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static stwuct snd_soc_cawd mt8192_mt6359_wt1015p_wt5682x_cawd = {
	.dwivew_name = DWIVEW_NAME,
	.ownew = THIS_MODUWE,
	.dai_wink = mt8192_mt6359_dai_winks,
	.num_winks = AWWAY_SIZE(mt8192_mt6359_dai_winks),
	.contwows = mt8192_mt6359_wt1015p_wt5682x_contwows,
	.num_contwows = AWWAY_SIZE(mt8192_mt6359_wt1015p_wt5682x_contwows),
	.dapm_widgets = mt8192_mt6359_wt1015p_wt5682x_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8192_mt6359_wt1015p_wt5682x_widgets),
	.dapm_woutes = mt8192_mt6359_wt1015p_wt5682x_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8192_mt6359_wt1015p_wt5682x_woutes),
};

static int mt8192_mt6359_cawd_set_be_wink(stwuct snd_soc_cawd *cawd,
					  stwuct snd_soc_dai_wink *wink,
					  stwuct device_node *node,
					  chaw *wink_name)
{
	int wet;

	if (node && stwcmp(wink->name, wink_name) == 0) {
		wet = snd_soc_of_get_dai_wink_codecs(cawd->dev, node, wink);
		if (wet < 0) {
			dev_eww_pwobe(cawd->dev, wet, "get dai wink codecs faiw\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int mt8192_mt6359_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct device_node *pwatfowm_node, *hdmi_codec, *headset_codec, *speakew_codec;
	int wet, i;
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct mt8192_mt6359_pwiv *pwiv;

	cawd = (stwuct snd_soc_cawd *)of_device_get_match_data(&pdev->dev);
	if (!cawd)
		wetuwn -EINVAW;
	cawd->dev = &pdev->dev;

	if (of_device_is_compatibwe(pdev->dev.of_node, WT1015P_WT5682_OF_NAME))
		cawd->name = WT1015P_WT5682_CAWD_NAME;
	ewse if (of_device_is_compatibwe(pdev->dev.of_node, WT1015P_WT5682S_OF_NAME))
		cawd->name = WT1015P_WT5682S_CAWD_NAME;
	ewse
		dev_dbg(&pdev->dev, "No need to set cawd name\n");

	hdmi_codec = of_pawse_phandwe(pdev->dev.of_node, "mediatek,hdmi-codec", 0);
	if (!hdmi_codec)
		dev_dbg(&pdev->dev, "The machine has no hdmi-codec\n");

	pwatfowm_node = of_pawse_phandwe(pdev->dev.of_node, "mediatek,pwatfowm", 0);
	if (!pwatfowm_node) {
		wet = -EINVAW;
		dev_eww_pwobe(&pdev->dev, wet, "Pwopewty 'pwatfowm' missing ow invawid\n");
		goto eww_pwatfowm_node;
	}

	speakew_codec = of_get_chiwd_by_name(pdev->dev.of_node, "speakew-codecs");
	if (!speakew_codec) {
		wet = -EINVAW;
		dev_eww_pwobe(&pdev->dev, wet, "Pwopewty 'speakew-codecs' missing ow invawid\n");
		goto eww_speakew_codec;
	}

	headset_codec = of_get_chiwd_by_name(pdev->dev.of_node, "headset-codec");
	if (!headset_codec) {
		wet = -EINVAW;
		dev_eww_pwobe(&pdev->dev, wet, "Pwopewty 'headset-codec' missing ow invawid\n");
		goto eww_headset_codec;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		wet = mt8192_mt6359_cawd_set_be_wink(cawd, dai_wink, speakew_codec, "I2S3");
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "%s set speakew_codec faiw\n",
				      dai_wink->name);
			goto eww_pwobe;
		}

		wet = mt8192_mt6359_cawd_set_be_wink(cawd, dai_wink, headset_codec, "I2S8");
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "%s set headset_codec faiw\n",
				      dai_wink->name);
			goto eww_pwobe;
		}

		wet = mt8192_mt6359_cawd_set_be_wink(cawd, dai_wink, headset_codec, "I2S9");
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "%s set headset_codec faiw\n",
				      dai_wink->name);
			goto eww_pwobe;
		}

		if (hdmi_codec && stwcmp(dai_wink->name, "TDM") == 0) {
			dai_wink->codecs->of_node = hdmi_codec;
			dai_wink->ignowe = 0;
		}

		if (dai_wink->num_codecs && dai_wink->codecs[0].dai_name &&
		    stwcmp(dai_wink->codecs[0].dai_name, WT1015_CODEC_DAI) == 0)
			dai_wink->ops = &mt8192_wt1015_i2s_ops;

		if (!dai_wink->pwatfowms->name)
			dai_wink->pwatfowms->of_node = pwatfowm_node;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto eww_pwobe;
	}
	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	wet = mt8192_afe_gpio_init(&pdev->dev);
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
	of_node_put(speakew_codec);
eww_speakew_codec:
	of_node_put(pwatfowm_node);
eww_pwatfowm_node:
	of_node_put(hdmi_codec);
	wetuwn wet;
}

#ifdef CONFIG_OF
static const stwuct of_device_id mt8192_mt6359_dt_match[] = {
	{
		.compatibwe = WT1015_WT5682_OF_NAME,
		.data = &mt8192_mt6359_wt1015_wt5682_cawd,
	},
	{
		.compatibwe = WT1015P_WT5682_OF_NAME,
		.data = &mt8192_mt6359_wt1015p_wt5682x_cawd,
	},
	{
		.compatibwe = WT1015P_WT5682S_OF_NAME,
		.data = &mt8192_mt6359_wt1015p_wt5682x_cawd,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, mt8192_mt6359_dt_match);
#endif

static const stwuct dev_pm_ops mt8192_mt6359_pm_ops = {
	.powewoff = snd_soc_powewoff,
	.westowe = snd_soc_wesume,
};

static stwuct pwatfowm_dwivew mt8192_mt6359_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
#ifdef CONFIG_OF
		.of_match_tabwe = mt8192_mt6359_dt_match,
#endif
		.pm = &mt8192_mt6359_pm_ops,
	},
	.pwobe = mt8192_mt6359_dev_pwobe,
};

moduwe_pwatfowm_dwivew(mt8192_mt6359_dwivew);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT8192-MT6359 AWSA SoC machine dwivew");
MODUWE_AUTHOW("Jiaxin Yu <jiaxin.yu@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("mt8192_mt6359 soc cawd");
