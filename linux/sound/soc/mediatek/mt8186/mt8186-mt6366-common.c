// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt8186-mt6366-common.c
//	--  MT8186 MT6366 AWSA common dwivew
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>
//
#incwude <sound/soc.h>

#incwude "../../codecs/mt6358.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "mt8186-afe-common.h"
#incwude "mt8186-mt6366-common.h"

int mt8186_mt6366_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct snd_soc_component *cmpnt_codec =
		snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	stwuct snd_soc_dapm_context *dapm = &wtd->cawd->dapm;
	int wet;

	/* set mtkaif pwotocow */
	mt6358_set_mtkaif_pwotocow(cmpnt_codec,
				   MT6358_MTKAIF_PWOTOCOW_1);
	afe_pwiv->mtkaif_pwotocow = MT6358_MTKAIF_PWOTOCOW_1;

	wet = snd_soc_dapm_sync(dapm);
	if (wet) {
		dev_eww(wtd->dev, "faiwed to snd_soc_dapm_sync\n");
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt8186_mt6366_init);

int mt8186_mt6366_cawd_set_be_wink(stwuct snd_soc_cawd *cawd,
				   stwuct snd_soc_dai_wink *wink,
				   stwuct device_node *node,
				   chaw *wink_name)
{
	int wet;

	if (node && stwcmp(wink->name, wink_name) == 0) {
		wet = snd_soc_of_get_dai_wink_codecs(cawd->dev, node, wink);
		if (wet < 0)
			wetuwn dev_eww_pwobe(cawd->dev, wet, "get dai wink codecs faiw\n");
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt8186_mt6366_cawd_set_be_wink);
