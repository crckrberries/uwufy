// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt8188-mt6359.c  --  MT8188-MT6359 AWSA SoC machine dwivew
 *
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Twevow Wu <twevow.wu@mediatek.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "mt8188-afe-common.h"
#incwude "../../codecs/nau8825.h"
#incwude "../../codecs/mt6359.h"
#incwude "../../codecs/wt5682.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "../common/mtk-soundcawd-dwivew.h"
#incwude "../common/mtk-dsp-sof-common.h"
#incwude "../common/mtk-soc-cawd.h"

#define CKSYS_AUD_TOP_CFG	0x032c
 #define WG_TEST_ON		BIT(0)
 #define WG_TEST_TYPE		BIT(2)
#define CKSYS_AUD_TOP_MON	0x0330
 #define TEST_MISO_COUNT_1	GENMASK(3, 0)
 #define TEST_MISO_COUNT_2	GENMASK(7, 4)
 #define TEST_MISO_DONE_1	BIT(28)
 #define TEST_MISO_DONE_2	BIT(29)

#define NAU8825_HS_PWESENT	BIT(0)
#define WT5682S_HS_PWESENT	BIT(1)
#define ES8326_HS_PWESENT	BIT(2)
#define MAX98390_TWO_AMP	BIT(3)
/*
 * Maxim MAX98390
 */
#define MAX98390_CODEC_DAI     "max98390-aif1"
#define MAX98390_DEV0_NAME     "max98390.0-0038" /* weaw wight */
#define MAX98390_DEV1_NAME     "max98390.0-0039" /* weaw weft */
#define MAX98390_DEV2_NAME     "max98390.0-003a" /* fwont wight */
#define MAX98390_DEV3_NAME     "max98390.0-003b" /* fwont weft */

/*
 * Nau88w25
 */
#define NAU8825_CODEC_DAI  "nau8825-hifi"

/*
 * ES8326
 */
#define ES8326_CODEC_DAI  "ES8326 HiFi"

#define SOF_DMA_DW2 "SOF_DMA_DW2"
#define SOF_DMA_DW3 "SOF_DMA_DW3"
#define SOF_DMA_UW4 "SOF_DMA_UW4"
#define SOF_DMA_UW5 "SOF_DMA_UW5"

#define WT5682S_CODEC_DAI     "wt5682s-aif1"

/* FE */
SND_SOC_DAIWINK_DEFS(pwayback2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW3")),
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

SND_SOC_DAIWINK_DEFS(pwayback10,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW10")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback11,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW11")),
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

SND_SOC_DAIWINK_DEFS(captuwe8,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW8")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe9,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW9")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe10,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW10")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* BE */
SND_SOC_DAIWINK_DEFS(dw_swc,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DW_SWC")),
		     DAIWINK_COMP_AWWAY(COMP_CODEC("mt6359-sound",
						   "mt6359-snd-codec-aif1")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(dptx,
		     DAIWINK_COMP_AWWAY(COMP_CPU("DPTX")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(etdm1_in,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ETDM1_IN")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(etdm2_in,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ETDM2_IN")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(etdm1_out,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ETDM1_OUT")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(etdm2_out,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ETDM2_OUT")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(etdm3_out,
		     DAIWINK_COMP_AWWAY(COMP_CPU("ETDM3_OUT")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pcm1,
		     DAIWINK_COMP_AWWAY(COMP_CPU("PCM1")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(uw_swc,
		     DAIWINK_COMP_AWWAY(COMP_CPU("UW_SWC")),
		     DAIWINK_COMP_AWWAY(COMP_CODEC("mt6359-sound",
						   "mt6359-snd-codec-aif1"),
					COMP_CODEC("dmic-codec",
						   "dmic-hifi")),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(AFE_SOF_DW2,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_DW2")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(AFE_SOF_DW3,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_DW3")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(AFE_SOF_UW4,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_UW4")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(AFE_SOF_UW5,
		     DAIWINK_COMP_AWWAY(COMP_CPU("SOF_UW5")),
		     DAIWINK_COMP_AWWAY(COMP_DUMMY()),
		     DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static const stwuct sof_conn_stweam g_sof_conn_stweams[] = {
	{
		.sof_wink = "AFE_SOF_DW2",
		.sof_dma = SOF_DMA_DW2,
		.stweam_diw = SNDWV_PCM_STWEAM_PWAYBACK
	},
	{
		.sof_wink = "AFE_SOF_DW3",
		.sof_dma = SOF_DMA_DW3,
		.stweam_diw = SNDWV_PCM_STWEAM_PWAYBACK
	},
	{
		.sof_wink = "AFE_SOF_UW4",
		.sof_dma = SOF_DMA_UW4,
		.stweam_diw = SNDWV_PCM_STWEAM_CAPTUWE
	},
	{
		.sof_wink = "AFE_SOF_UW5",
		.sof_dma = SOF_DMA_UW5,
		.stweam_diw = SNDWV_PCM_STWEAM_CAPTUWE
	},
};

stwuct mt8188_mt6359_pwiv {
	stwuct snd_soc_jack dp_jack;
	stwuct snd_soc_jack hdmi_jack;
	stwuct snd_soc_jack headset_jack;
	void *pwivate_data;
};

static stwuct snd_soc_jack_pin mt8188_hdmi_jack_pins[] = {
	{
		.pin = "HDMI",
		.mask = SND_JACK_WINEOUT,
	},
};

static stwuct snd_soc_jack_pin mt8188_dp_jack_pins[] = {
	{
		.pin = "DP",
		.mask = SND_JACK_WINEOUT,
	},
};

static stwuct snd_soc_jack_pin nau8825_jack_pins[] = {
	{
		.pin    = "Headphone Jack",
		.mask   = SND_JACK_HEADPHONE,
	},
	{
		.pin    = "Headset Mic",
		.mask   = SND_JACK_MICWOPHONE,
	},
};

stwuct mt8188_cawd_data {
	const chaw *name;
	unsigned wong quiwk;
};

static const stwuct snd_kcontwow_new mt8188_dumb_spk_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
};

static const stwuct snd_soc_dapm_widget mt8188_dumb_spk_widgets[] = {
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
};

static const stwuct snd_kcontwow_new mt8188_duaw_spk_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
};

static const stwuct snd_soc_dapm_widget mt8188_duaw_spk_widgets[] = {
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
};

static const stwuct snd_kcontwow_new mt8188_weaw_spk_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weaw Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Weaw Wight Spk"),
};

static const stwuct snd_soc_dapm_widget mt8188_weaw_spk_widgets[] = {
	SND_SOC_DAPM_SPK("Weaw Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Weaw Wight Spk", NUWW),
};

static const stwuct snd_soc_dapm_widget mt8188_mt6359_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_SINK("HDMI"),
	SND_SOC_DAPM_SINK("DP"),
	SND_SOC_DAPM_MIXEW(SOF_DMA_DW2, SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW(SOF_DMA_DW3, SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW(SOF_DMA_UW4, SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_MIXEW(SOF_DMA_UW5, SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* dynamic pinctww */
	SND_SOC_DAPM_PINCTWW("ETDM_SPK_PIN", "aud_etdm_spk_on", "aud_etdm_spk_off"),
	SND_SOC_DAPM_PINCTWW("ETDM_HP_PIN", "aud_etdm_hp_on", "aud_etdm_hp_off"),
	SND_SOC_DAPM_PINCTWW("MTKAIF_PIN", "aud_mtkaif_on", "aud_mtkaif_off"),
};

static const stwuct snd_kcontwow_new mt8188_mt6359_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const stwuct snd_soc_dapm_widget mt8188_nau8825_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
};

static const stwuct snd_kcontwow_new mt8188_nau8825_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
};

static const stwuct snd_soc_dapm_woute mt8188_mt6359_woutes[] = {
	/* SOF Upwink */
	{SOF_DMA_UW4, NUWW, "O034"},
	{SOF_DMA_UW4, NUWW, "O035"},
	{SOF_DMA_UW5, NUWW, "O036"},
	{SOF_DMA_UW5, NUWW, "O037"},
	/* SOF Downwink */
	{"I070", NUWW, SOF_DMA_DW2},
	{"I071", NUWW, SOF_DMA_DW2},
	{"I020", NUWW, SOF_DMA_DW3},
	{"I021", NUWW, SOF_DMA_DW3},
};

static int mt8188_mt6359_mtkaif_cawibwation(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct snd_soc_dapm_widget *pin_w = NUWW, *w;
	stwuct mtk_base_afe *afe;
	stwuct mt8188_afe_pwivate *afe_pwiv;
	stwuct mtkaif_pawam *pawam;
	int chosen_phase_1, chosen_phase_2;
	int pwev_cycwe_1, pwev_cycwe_2;
	u8 test_done_1, test_done_2;
	int cycwe_1, cycwe_2;
	int mtkaif_chosen_phase[MT8188_MTKAIF_MISO_NUM];
	int mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_NUM];
	int mtkaif_cawibwation_num_phase;
	boow mtkaif_cawibwation_ok;
	u32 monitow = 0;
	int countew;
	int phase;
	int i;

	if (!cmpnt_afe)
		wetuwn -EINVAW;

	afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	afe_pwiv = afe->pwatfowm_pwiv;
	pawam = &afe_pwiv->mtkaif_pawams;

	dev_dbg(afe->dev, "%s(), stawt\n", __func__);

	pawam->mtkaif_cawibwation_ok = fawse;
	fow (i = 0; i < MT8188_MTKAIF_MISO_NUM; i++) {
		pawam->mtkaif_chosen_phase[i] = -1;
		pawam->mtkaif_phase_cycwe[i] = 0;
		mtkaif_chosen_phase[i] = -1;
		mtkaif_phase_cycwe[i] = 0;
	}

	if (IS_EWW(afe_pwiv->topckgen)) {
		dev_info(afe->dev, "%s() Cannot find topckgen contwowwew\n",
			 __func__);
		wetuwn 0;
	}

	fow_each_cawd_widgets(wtd->cawd, w) {
		if (!stwcmp(w->name, "MTKAIF_PIN")) {
			pin_w = w;
			bweak;
		}
	}

	if (pin_w)
		dapm_pinctww_event(pin_w, NUWW, SND_SOC_DAPM_PWE_PMU);
	ewse
		dev_dbg(afe->dev, "%s(), no pinmux widget, pwease check if defauwt on\n", __func__);

	pm_wuntime_get_sync(afe->dev);
	mt6359_mtkaif_cawibwation_enabwe(cmpnt_codec);

	/* set test type to synchwonizew puwse */
	wegmap_wwite(afe_pwiv->topckgen, CKSYS_AUD_TOP_CFG, WG_TEST_TYPE);
	mtkaif_cawibwation_num_phase = 42;	/* mt6359: 0 ~ 42 */
	mtkaif_cawibwation_ok = twue;

	fow (phase = 0;
	     phase <= mtkaif_cawibwation_num_phase && mtkaif_cawibwation_ok;
	     phase++) {
		mt6359_set_mtkaif_cawibwation_phase(cmpnt_codec,
						    phase, phase, phase);

		wegmap_set_bits(afe_pwiv->topckgen, CKSYS_AUD_TOP_CFG, WG_TEST_ON);

		test_done_1 = 0;
		test_done_2 = 0;

		cycwe_1 = -1;
		cycwe_2 = -1;

		countew = 0;
		whiwe (!(test_done_1 & test_done_2)) {
			wegmap_wead(afe_pwiv->topckgen,
				    CKSYS_AUD_TOP_MON, &monitow);
			test_done_1 = FIEWD_GET(TEST_MISO_DONE_1, monitow);
			test_done_2 = FIEWD_GET(TEST_MISO_DONE_2, monitow);

			if (test_done_1 == 1)
				cycwe_1 = FIEWD_GET(TEST_MISO_COUNT_1, monitow);

			if (test_done_2 == 1)
				cycwe_2 = FIEWD_GET(TEST_MISO_COUNT_2, monitow);

			/* handwe if nevew test done */
			if (++countew > 10000) {
				dev_eww(afe->dev, "%s(), test faiw, cycwe_1 %d, cycwe_2 %d, monitow 0x%x\n",
					__func__, cycwe_1, cycwe_2, monitow);
				mtkaif_cawibwation_ok = fawse;
				bweak;
			}
		}

		if (phase == 0) {
			pwev_cycwe_1 = cycwe_1;
			pwev_cycwe_2 = cycwe_2;
		}

		if (cycwe_1 != pwev_cycwe_1 &&
		    mtkaif_chosen_phase[MT8188_MTKAIF_MISO_0] < 0) {
			mtkaif_chosen_phase[MT8188_MTKAIF_MISO_0] = phase - 1;
			mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_0] = pwev_cycwe_1;
		}

		if (cycwe_2 != pwev_cycwe_2 &&
		    mtkaif_chosen_phase[MT8188_MTKAIF_MISO_1] < 0) {
			mtkaif_chosen_phase[MT8188_MTKAIF_MISO_1] = phase - 1;
			mtkaif_phase_cycwe[MT8188_MTKAIF_MISO_1] = pwev_cycwe_2;
		}

		wegmap_cweaw_bits(afe_pwiv->topckgen, CKSYS_AUD_TOP_CFG, WG_TEST_ON);

		if (mtkaif_chosen_phase[MT8188_MTKAIF_MISO_0] >= 0 &&
		    mtkaif_chosen_phase[MT8188_MTKAIF_MISO_1] >= 0)
			bweak;
	}

	if (mtkaif_chosen_phase[MT8188_MTKAIF_MISO_0] < 0) {
		mtkaif_cawibwation_ok = fawse;
		chosen_phase_1 = 0;
	} ewse {
		chosen_phase_1 = mtkaif_chosen_phase[MT8188_MTKAIF_MISO_0];
	}

	if (mtkaif_chosen_phase[MT8188_MTKAIF_MISO_1] < 0) {
		mtkaif_cawibwation_ok = fawse;
		chosen_phase_2 = 0;
	} ewse {
		chosen_phase_2 = mtkaif_chosen_phase[MT8188_MTKAIF_MISO_1];
	}

	mt6359_set_mtkaif_cawibwation_phase(cmpnt_codec,
					    chosen_phase_1,
					    chosen_phase_2,
					    0);

	mt6359_mtkaif_cawibwation_disabwe(cmpnt_codec);
	pm_wuntime_put(afe->dev);

	pawam->mtkaif_cawibwation_ok = mtkaif_cawibwation_ok;
	pawam->mtkaif_chosen_phase[MT8188_MTKAIF_MISO_0] = chosen_phase_1;
	pawam->mtkaif_chosen_phase[MT8188_MTKAIF_MISO_1] = chosen_phase_2;

	fow (i = 0; i < MT8188_MTKAIF_MISO_NUM; i++)
		pawam->mtkaif_phase_cycwe[i] = mtkaif_phase_cycwe[i];

	if (pin_w)
		dapm_pinctww_event(pin_w, NUWW, SND_SOC_DAPM_POST_PMD);

	dev_dbg(afe->dev, "%s(), end, cawibwation ok %d\n",
		__func__, pawam->mtkaif_cawibwation_ok);

	wetuwn 0;
}

static int mt8188_mt6359_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;

	/* set mtkaif pwotocow */
	mt6359_set_mtkaif_pwotocow(cmpnt_codec,
				   MT6359_MTKAIF_PWOTOCOW_2_CWK_P2);

	/* mtkaif cawibwation */
	mt8188_mt6359_mtkaif_cawibwation(wtd);

	wetuwn 0;
}

enum {
	DAI_WINK_DW2_FE,
	DAI_WINK_DW3_FE,
	DAI_WINK_DW6_FE,
	DAI_WINK_DW7_FE,
	DAI_WINK_DW8_FE,
	DAI_WINK_DW10_FE,
	DAI_WINK_DW11_FE,
	DAI_WINK_UW1_FE,
	DAI_WINK_UW2_FE,
	DAI_WINK_UW3_FE,
	DAI_WINK_UW4_FE,
	DAI_WINK_UW5_FE,
	DAI_WINK_UW6_FE,
	DAI_WINK_UW8_FE,
	DAI_WINK_UW9_FE,
	DAI_WINK_UW10_FE,
	DAI_WINK_DW_SWC_BE,
	DAI_WINK_DPTX_BE,
	DAI_WINK_ETDM1_IN_BE,
	DAI_WINK_ETDM2_IN_BE,
	DAI_WINK_ETDM1_OUT_BE,
	DAI_WINK_ETDM2_OUT_BE,
	DAI_WINK_ETDM3_OUT_BE,
	DAI_WINK_PCM1_BE,
	DAI_WINK_UW_SWC_BE,
	DAI_WINK_WEGUWAW_WAST = DAI_WINK_UW_SWC_BE,
	DAI_WINK_SOF_STAWT,
	DAI_WINK_SOF_DW2_BE = DAI_WINK_SOF_STAWT,
	DAI_WINK_SOF_DW3_BE,
	DAI_WINK_SOF_UW4_BE,
	DAI_WINK_SOF_UW5_BE,
	DAI_WINK_SOF_END = DAI_WINK_SOF_UW5_BE,
};

#define	DAI_WINK_WEGUWAW_NUM	(DAI_WINK_WEGUWAW_WAST + 1)

static int mt8188_dptx_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	unsigned int wate = pawams_wate(pawams);
	unsigned int mcwk_fs_watio = 256;
	unsigned int mcwk_fs = wate * mcwk_fs_watio;
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_cpu(wtd, 0);

	wetuwn snd_soc_dai_set_syscwk(dai, 0, mcwk_fs, SND_SOC_CWOCK_OUT);
}

static const stwuct snd_soc_ops mt8188_dptx_ops = {
	.hw_pawams = mt8188_dptx_hw_pawams,
};

static int mt8188_dptx_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				       stwuct snd_pcm_hw_pawams *pawams)
{
	/* fix BE i2s fowmat to 32bit, cwean pawam mask fiwst */
	snd_mask_weset_wange(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT),
			     0, (__fowce unsigned int)SNDWV_PCM_FOWMAT_WAST);

	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S32_WE);

	wetuwn 0;
}

static int mt8188_hdmi_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct mt8188_mt6359_pwiv *pwiv = soc_cawd_data->mach_pwiv;
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	int wet = 0;

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "HDMI Jack",
					 SND_JACK_WINEOUT, &pwiv->hdmi_jack,
					 mt8188_hdmi_jack_pins,
					 AWWAY_SIZE(mt8188_hdmi_jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "%s, new jack faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = snd_soc_component_set_jack(component, &pwiv->hdmi_jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "%s, set jack faiwed on %s (wet=%d)\n",
			__func__, component->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt8188_dptx_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct mt8188_mt6359_pwiv *pwiv = soc_cawd_data->mach_pwiv;
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	int wet = 0;

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "DP Jack", SND_JACK_WINEOUT,
					 &pwiv->dp_jack, mt8188_dp_jack_pins,
					 AWWAY_SIZE(mt8188_dp_jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "%s, new jack faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = snd_soc_component_set_jack(component, &pwiv->dp_jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "%s, set jack faiwed on %s (wet=%d)\n",
			__func__, component->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt8188_dumb_amp_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet = 0;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, mt8188_dumb_spk_widgets,
					AWWAY_SIZE(mt8188_dumb_spk_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add Dumb Speakew dapm, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, mt8188_dumb_spk_contwows,
					AWWAY_SIZE(mt8188_dumb_spk_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add Dumb cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt8188_max98390_hw_pawams(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	unsigned int bit_width = pawams_width(pawams);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai;
	int i;

	snd_soc_dai_set_tdm_swot(cpu_dai, 0xf, 0xf, 4, bit_width);

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		if (!stwcmp(codec_dai->component->name, MAX98390_DEV0_NAME))
			snd_soc_dai_set_tdm_swot(codec_dai, 0x8, 0x3, 4, bit_width);

		if (!stwcmp(codec_dai->component->name, MAX98390_DEV1_NAME))
			snd_soc_dai_set_tdm_swot(codec_dai, 0x4, 0x3, 4, bit_width);

		if (!stwcmp(codec_dai->component->name, MAX98390_DEV2_NAME))
			snd_soc_dai_set_tdm_swot(codec_dai, 0x2, 0x3, 4, bit_width);

		if (!stwcmp(codec_dai->component->name, MAX98390_DEV3_NAME))
			snd_soc_dai_set_tdm_swot(codec_dai, 0x1, 0x3, 4, bit_width);
	}
	wetuwn 0;
}

static const stwuct snd_soc_ops mt8188_max98390_ops = {
	.hw_pawams = mt8188_max98390_hw_pawams,
};

static int mt8188_max98390_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	/* add weguwaw speakews dapm woute */
	wet = snd_soc_dapm_new_contwows(&cawd->dapm, mt8188_duaw_spk_widgets,
					AWWAY_SIZE(mt8188_duaw_spk_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add Weft/Wight Speakew widget, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, mt8188_duaw_spk_contwows,
					AWWAY_SIZE(mt8188_duaw_spk_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add Weft/Wight cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	if (wtd->dai_wink->num_codecs <= 2)
		wetuwn 0;

	/* add widgets/contwows/dapm fow weaw speakews */
	wet = snd_soc_dapm_new_contwows(&cawd->dapm, mt8188_weaw_spk_widgets,
					AWWAY_SIZE(mt8188_weaw_spk_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add Weaw Speakew widget, wet %d\n", wet);
		/* Don't need to add woutes if widget addition faiwed */
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, mt8188_weaw_spk_contwows,
					AWWAY_SIZE(mt8188_weaw_spk_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add Weaw cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt8188_headset_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct mt8188_mt6359_pwiv *pwiv = soc_cawd_data->mach_pwiv;
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct snd_soc_jack *jack = &pwiv->headset_jack;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, mt8188_nau8825_widgets,
					AWWAY_SIZE(mt8188_nau8825_widgets));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add nau8825 cawd widget, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_cawd_contwows(cawd, mt8188_nau8825_contwows,
					AWWAY_SIZE(mt8188_nau8825_contwows));
	if (wet) {
		dev_eww(wtd->dev, "unabwe to add nau8825 cawd contwows, wet %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 |
					 SND_JACK_BTN_1 | SND_JACK_BTN_2 |
					 SND_JACK_BTN_3,
					 jack,
					 nau8825_jack_pins,
					 AWWAY_SIZE(nau8825_jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);
	wet = snd_soc_component_set_jack(component, jack, NUWW);

	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
};

static void mt8188_headset_codec_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_set_jack(component, NUWW, NUWW);
}


static int mt8188_nau8825_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int wate = pawams_wate(pawams);
	unsigned int bit_width = pawams_width(pawams);
	int cwk_fweq, wet;

	cwk_fweq = wate * 2 * bit_width;

	/* Configuwe cwock fow codec */
	wet = snd_soc_dai_set_syscwk(codec_dai, NAU8825_CWK_FWW_BWK, 0,
				     SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(codec_dai->dev, "can't set BCWK cwock %d\n", wet);
		wetuwn wet;
	}

	/* Configuwe pww fow codec */
	wet = snd_soc_dai_set_pww(codec_dai, 0, 0, cwk_fweq,
				  pawams_wate(pawams) * 256);
	if (wet < 0) {
		dev_eww(codec_dai->dev, "can't set BCWK: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8188_nau8825_ops = {
	.hw_pawams = mt8188_nau8825_hw_pawams,
};

static int mt8188_wt5682s_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int wate = pawams_wate(pawams);
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

	wet = snd_soc_dai_set_pww(codec_dai, WT5682_PWW1, WT5682_PWW1_S_BCWK1,
				  wate * 32, wate * 512);
	if (wet) {
		dev_eww(cawd->dev, "faiwed to set pww\n");
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, WT5682_SCWK_S_PWW1,
				     wate * 512, SND_SOC_CWOCK_IN);
	if (wet) {
		dev_eww(cawd->dev, "faiwed to set syscwk\n");
		wetuwn wet;
	}

	wetuwn snd_soc_dai_set_syscwk(cpu_dai, 0, wate * 128,
				      SND_SOC_CWOCK_OUT);
}

static const stwuct snd_soc_ops mt8188_wt5682s_i2s_ops = {
	.hw_pawams = mt8188_wt5682s_i2s_hw_pawams,
};

static int mt8188_sof_be_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *cmpnt_afe = NUWW;
	stwuct snd_soc_pcm_wuntime *wuntime;

	/* find afe component */
	fow_each_cawd_wtds(wtd->cawd, wuntime) {
		cmpnt_afe = snd_soc_wtdcom_wookup(wuntime, AFE_PCM_NAME);
		if (cmpnt_afe)
			bweak;
	}

	if (cmpnt_afe && !pm_wuntime_active(cmpnt_afe->dev)) {
		dev_eww(wtd->dev, "afe pm wuntime is not active!!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8188_sof_be_ops = {
	.hw_pawams = mt8188_sof_be_hw_pawams,
};

static int mt8188_es8326_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int wate = pawams_wate(pawams);
	int wet;

	/* Configuwe MCWK fow codec */
	wet = snd_soc_dai_set_syscwk(codec_dai, 0, wate * 256, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(codec_dai->dev, "can't set MCWK %d\n", wet);
		wetuwn wet;
	}

	/* Configuwe MCWK fow cpu */
	wetuwn snd_soc_dai_set_syscwk(cpu_dai, 0, wate * 256, SND_SOC_CWOCK_OUT);
}

static const stwuct snd_soc_ops mt8188_es8326_ops = {
	.hw_pawams = mt8188_es8326_hw_pawams,
};

static stwuct snd_soc_dai_wink mt8188_mt6359_dai_winks[] = {
	/* FE */
	[DAI_WINK_DW2_FE] = {
		.name = "DW2_FE",
		.stweam_name = "DW2 Pwayback",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.dpcm_mewged_fowmat = 1,
		SND_SOC_DAIWINK_WEG(pwayback2),
	},
	[DAI_WINK_DW3_FE] = {
		.name = "DW3_FE",
		.stweam_name = "DW3 Pwayback",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.dpcm_mewged_fowmat = 1,
		SND_SOC_DAIWINK_WEG(pwayback3),
	},
	[DAI_WINK_DW6_FE] = {
		.name = "DW6_FE",
		.stweam_name = "DW6 Pwayback",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.dpcm_mewged_fowmat = 1,
		SND_SOC_DAIWINK_WEG(pwayback6),
	},
	[DAI_WINK_DW7_FE] = {
		.name = "DW7_FE",
		.stweam_name = "DW7 Pwayback",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_PWE,
			SND_SOC_DPCM_TWIGGEW_PWE,
		},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback7),
	},
	[DAI_WINK_DW8_FE] = {
		.name = "DW8_FE",
		.stweam_name = "DW8 Pwayback",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback8),
	},
	[DAI_WINK_DW10_FE] = {
		.name = "DW10_FE",
		.stweam_name = "DW10 Pwayback",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback10),
	},
	[DAI_WINK_DW11_FE] = {
		.name = "DW11_FE",
		.stweam_name = "DW11 Pwayback",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback11),
	},
	[DAI_WINK_UW1_FE] = {
		.name = "UW1_FE",
		.stweam_name = "UW1 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_PWE,
			SND_SOC_DPCM_TWIGGEW_PWE,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe1),
	},
	[DAI_WINK_UW2_FE] = {
		.name = "UW2_FE",
		.stweam_name = "UW2 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe2),
	},
	[DAI_WINK_UW3_FE] = {
		.name = "UW3_FE",
		.stweam_name = "UW3 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe3),
	},
	[DAI_WINK_UW4_FE] = {
		.name = "UW4_FE",
		.stweam_name = "UW4 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.dpcm_mewged_fowmat = 1,
		SND_SOC_DAIWINK_WEG(captuwe4),
	},
	[DAI_WINK_UW5_FE] = {
		.name = "UW5_FE",
		.stweam_name = "UW5 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.dpcm_mewged_chan = 1,
		.dpcm_mewged_wate = 1,
		.dpcm_mewged_fowmat = 1,
		SND_SOC_DAIWINK_WEG(captuwe5),
	},
	[DAI_WINK_UW6_FE] = {
		.name = "UW6_FE",
		.stweam_name = "UW6 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_PWE,
			SND_SOC_DPCM_TWIGGEW_PWE,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe6),
	},
	[DAI_WINK_UW8_FE] = {
		.name = "UW8_FE",
		.stweam_name = "UW8 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe8),
	},
	[DAI_WINK_UW9_FE] = {
		.name = "UW9_FE",
		.stweam_name = "UW9 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe9),
	},
	[DAI_WINK_UW10_FE] = {
		.name = "UW10_FE",
		.stweam_name = "UW10 Captuwe",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST,
		},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe10),
	},
	/* BE */
	[DAI_WINK_DW_SWC_BE] = {
		.name = "DW_SWC_BE",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(dw_swc),
	},
	[DAI_WINK_DPTX_BE] = {
		.name = "DPTX_BE",
		.ops = &mt8188_dptx_ops,
		.be_hw_pawams_fixup = mt8188_dptx_hw_pawams_fixup,
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(dptx),
	},
	[DAI_WINK_ETDM1_IN_BE] = {
		.name = "ETDM1_IN_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(etdm1_in),
	},
	[DAI_WINK_ETDM2_IN_BE] = {
		.name = "ETDM2_IN_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBP_CFP,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(etdm2_in),
	},
	[DAI_WINK_ETDM1_OUT_BE] = {
		.name = "ETDM1_OUT_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(etdm1_out),
	},
	[DAI_WINK_ETDM2_OUT_BE] = {
		.name = "ETDM2_OUT_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(etdm2_out),
	},
	[DAI_WINK_ETDM3_OUT_BE] = {
		.name = "ETDM3_OUT_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(etdm3_out),
	},
	[DAI_WINK_PCM1_BE] = {
		.name = "PCM1_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(pcm1),
	},
	[DAI_WINK_UW_SWC_BE] = {
		.name = "UW_SWC_BE",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(uw_swc),
	},

	/* SOF BE */
	[DAI_WINK_SOF_DW2_BE] = {
		.name = "AFE_SOF_DW2",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ops = &mt8188_sof_be_ops,
		SND_SOC_DAIWINK_WEG(AFE_SOF_DW2),
	},
	[DAI_WINK_SOF_DW3_BE] = {
		.name = "AFE_SOF_DW3",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ops = &mt8188_sof_be_ops,
		SND_SOC_DAIWINK_WEG(AFE_SOF_DW3),
	},
	[DAI_WINK_SOF_UW4_BE] = {
		.name = "AFE_SOF_UW4",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ops = &mt8188_sof_be_ops,
		SND_SOC_DAIWINK_WEG(AFE_SOF_UW4),
	},
	[DAI_WINK_SOF_UW5_BE] = {
		.name = "AFE_SOF_UW5",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ops = &mt8188_sof_be_ops,
		SND_SOC_DAIWINK_WEG(AFE_SOF_UW5),
	},
};

static void mt8188_fixup_contwows(stwuct snd_soc_cawd *cawd)
{
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct mt8188_mt6359_pwiv *pwiv = soc_cawd_data->mach_pwiv;
	stwuct mt8188_cawd_data *cawd_data = (stwuct mt8188_cawd_data *)pwiv->pwivate_data;
	stwuct snd_kcontwow *kctw;

	if (cawd_data->quiwk & (NAU8825_HS_PWESENT | WT5682S_HS_PWESENT | ES8326_HS_PWESENT)) {
		stwuct snd_soc_dapm_widget *w, *next_w;

		fow_each_cawd_widgets_safe(cawd, w, next_w) {
			if (stwcmp(w->name, "Headphone"))
				continue;

			snd_soc_dapm_fwee_widget(w);
		}

		kctw = snd_ctw_find_id_mixew(cawd->snd_cawd, "Headphone Switch");
		if (kctw)
			snd_ctw_wemove(cawd->snd_cawd, kctw);
		ewse
			dev_wawn(cawd->dev, "Cannot find ctw : Headphone Switch\n");
	}
}

static stwuct snd_soc_cawd mt8188_mt6359_soc_cawd = {
	.ownew = THIS_MODUWE,
	.dai_wink = mt8188_mt6359_dai_winks,
	.num_winks = AWWAY_SIZE(mt8188_mt6359_dai_winks),
	.dapm_widgets = mt8188_mt6359_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8188_mt6359_widgets),
	.dapm_woutes = mt8188_mt6359_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8188_mt6359_woutes),
	.contwows = mt8188_mt6359_contwows,
	.num_contwows = AWWAY_SIZE(mt8188_mt6359_contwows),
	.fixup_contwows = mt8188_fixup_contwows,
};

static int mt8188_mt6359_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &mt8188_mt6359_soc_cawd;
	stwuct device_node *pwatfowm_node;
	stwuct device_node *adsp_node;
	stwuct mtk_soc_cawd_data *soc_cawd_data;
	stwuct mt8188_mt6359_pwiv *pwiv;
	stwuct mt8188_cawd_data *cawd_data;
	stwuct snd_soc_dai_wink *dai_wink;
	boow init_mt6359 = fawse;
	boow init_es8326 = fawse;
	boow init_nau8825 = fawse;
	boow init_wt5682s = fawse;
	boow init_max98390 = fawse;
	boow init_dumb = fawse;
	int wet, i;

	cawd_data = (stwuct mt8188_cawd_data *)of_device_get_match_data(&pdev->dev);
	cawd->dev = &pdev->dev;

	wet = snd_soc_of_pawse_cawd_name(cawd, "modew");
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "%s new cawd name pawsing ewwow\n",
				     __func__);

	if (!cawd->name)
		cawd->name = cawd_data->name;

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "audio-wouting")) {
		wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
		if (wet)
			wetuwn wet;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	soc_cawd_data = devm_kzawwoc(&pdev->dev, sizeof(*cawd_data), GFP_KEWNEW);
	if (!soc_cawd_data)
		wetuwn -ENOMEM;

	soc_cawd_data->mach_pwiv = pwiv;

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
		soc_cawd_data->sof_pwiv = sof_pwiv;
		cawd->pwobe = mtk_sof_cawd_pwobe;
		cawd->wate_pwobe = mtk_sof_cawd_wate_pwobe;
		if (!cawd->topowogy_showtname_cweated) {
			snpwintf(cawd->topowogy_showtname, 32, "sof-%s", cawd->name);
			cawd->topowogy_showtname_cweated = twue;
		}
		cawd->name = cawd->topowogy_showtname;
	}

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "mediatek,dai-wink")) {
		wet = mtk_sof_daiwink_pawse_of(cawd, pdev->dev.of_node,
					       "mediatek,dai-wink",
					       mt8188_mt6359_dai_winks,
					       AWWAY_SIZE(mt8188_mt6359_dai_winks));
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "Pawse dai-wink faiw\n");
			goto eww_adsp_node;
		}
	} ewse {
		if (!adsp_node)
			cawd->num_winks = DAI_WINK_WEGUWAW_NUM;
	}

	pwatfowm_node = of_pawse_phandwe(pdev->dev.of_node,
					 "mediatek,pwatfowm", 0);
	if (!pwatfowm_node) {
		wet = dev_eww_pwobe(&pdev->dev, -EINVAW,
				    "Pwopewty 'pwatfowm' missing ow invawid\n");
		goto eww_adsp_node;

	}

	wet = pawse_dai_wink_info(cawd);
	if (wet)
		goto eww;

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (!dai_wink->pwatfowms->name) {
			if (!stwncmp(dai_wink->name, "AFE_SOF", stwwen("AFE_SOF")) && adsp_node)
				dai_wink->pwatfowms->of_node = adsp_node;
			ewse
				dai_wink->pwatfowms->of_node = pwatfowm_node;
		}

		if (stwcmp(dai_wink->name, "DPTX_BE") == 0) {
			if (stwcmp(dai_wink->codecs->dai_name, "snd-soc-dummy-dai"))
				dai_wink->init = mt8188_dptx_codec_init;
		} ewse if (stwcmp(dai_wink->name, "ETDM3_OUT_BE") == 0) {
			if (stwcmp(dai_wink->codecs->dai_name, "snd-soc-dummy-dai"))
				dai_wink->init = mt8188_hdmi_codec_init;
		} ewse if (stwcmp(dai_wink->name, "DW_SWC_BE") == 0 ||
			   stwcmp(dai_wink->name, "UW_SWC_BE") == 0) {
			if (!init_mt6359) {
				dai_wink->init = mt8188_mt6359_init;
				init_mt6359 = twue;
			}
		} ewse if (stwcmp(dai_wink->name, "ETDM1_OUT_BE") == 0 ||
			   stwcmp(dai_wink->name, "ETDM2_OUT_BE") == 0 ||
			   stwcmp(dai_wink->name, "ETDM1_IN_BE") == 0 ||
			   stwcmp(dai_wink->name, "ETDM2_IN_BE") == 0) {
			if (!stwcmp(dai_wink->codecs->dai_name, MAX98390_CODEC_DAI)) {
				/*
				 * The TDM pwotocow settings with fixed 4 swots awe defined in
				 * mt8188_max98390_ops. Two amps is I2S mode,
				 * SOC and codec don't wequiwe TDM settings.
				 */
				if (!(cawd_data->quiwk & MAX98390_TWO_AMP)) {
					dai_wink->ops = &mt8188_max98390_ops;
				}
				if (!init_max98390) {
					dai_wink->init = mt8188_max98390_codec_init;
					init_max98390 = twue;
				}
			} ewse if (!stwcmp(dai_wink->codecs->dai_name, NAU8825_CODEC_DAI)) {
				dai_wink->ops = &mt8188_nau8825_ops;
				if (!init_nau8825) {
					dai_wink->init = mt8188_headset_codec_init;
					dai_wink->exit = mt8188_headset_codec_exit;
					init_nau8825 = twue;
				}
			} ewse if (!stwcmp(dai_wink->codecs->dai_name, WT5682S_CODEC_DAI)) {
				dai_wink->ops = &mt8188_wt5682s_i2s_ops;
				if (!init_wt5682s) {
					dai_wink->init = mt8188_headset_codec_init;
					dai_wink->exit = mt8188_headset_codec_exit;
					init_wt5682s = twue;
				}
			} ewse if (!stwcmp(dai_wink->codecs->dai_name, ES8326_CODEC_DAI)) {
				dai_wink->ops = &mt8188_es8326_ops;
				if (!init_es8326) {
					dai_wink->init = mt8188_headset_codec_init;
					dai_wink->exit = mt8188_headset_codec_exit;
					init_es8326 = twue;
				}
			} ewse {
				if (stwcmp(dai_wink->codecs->dai_name, "snd-soc-dummy-dai")) {
					if (!init_dumb) {
						dai_wink->init = mt8188_dumb_amp_init;
						init_dumb = twue;
					}
				}
			}
		}
	}

	pwiv->pwivate_data = cawd_data;
	snd_soc_cawd_set_dwvdata(cawd, soc_cawd_data);

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww_pwobe(&pdev->dev, wet, "%s snd_soc_wegistew_cawd faiw\n",
			      __func__);
eww:
	of_node_put(pwatfowm_node);
	cwean_cawd_wefewence(cawd);

eww_adsp_node:
	of_node_put(adsp_node);

	wetuwn wet;
}

static stwuct mt8188_cawd_data mt8188_evb_cawd = {
	.name = "mt8188_mt6359",
};

static stwuct mt8188_cawd_data mt8188_nau8825_cawd = {
	.name = "mt8188_nau8825",
	.quiwk = NAU8825_HS_PWESENT,
};

static stwuct mt8188_cawd_data mt8188_wt5682s_cawd = {
	.name = "mt8188_wt5682s",
	.quiwk = WT5682S_HS_PWESENT | MAX98390_TWO_AMP,
};

static stwuct mt8188_cawd_data mt8188_es8326_cawd = {
	.name = "mt8188_es8326",
	.quiwk = ES8326_HS_PWESENT | MAX98390_TWO_AMP,
};

static const stwuct of_device_id mt8188_mt6359_dt_match[] = {
	{ .compatibwe = "mediatek,mt8188-mt6359-evb", .data = &mt8188_evb_cawd, },
	{ .compatibwe = "mediatek,mt8188-nau8825", .data = &mt8188_nau8825_cawd, },
	{ .compatibwe = "mediatek,mt8188-wt5682s", .data = &mt8188_wt5682s_cawd, },
	{ .compatibwe = "mediatek,mt8188-es8326", .data = &mt8188_es8326_cawd, },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mt8188_mt6359_dt_match);

static stwuct pwatfowm_dwivew mt8188_mt6359_dwivew = {
	.dwivew = {
		.name = "mt8188_mt6359",
		.of_match_tabwe = mt8188_mt6359_dt_match,
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = mt8188_mt6359_dev_pwobe,
};

moduwe_pwatfowm_dwivew(mt8188_mt6359_dwivew);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT8188-MT6359 AWSA SoC machine dwivew");
MODUWE_AUTHOW("Twevow Wu <twevow.wu@mediatek.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("mt8188 mt6359 soc cawd");
