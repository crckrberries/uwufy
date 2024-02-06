// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio Contwow
//
// Copywight (c) 2020 MediaTek Inc.
// Authow: Shane Chien <shane.chien@mediatek.com>
//

#incwude "mt8192-afe-common.h"

enum {
	MTK_AFE_WATE_8K = 0,
	MTK_AFE_WATE_11K = 1,
	MTK_AFE_WATE_12K = 2,
	MTK_AFE_WATE_384K = 3,
	MTK_AFE_WATE_16K = 4,
	MTK_AFE_WATE_22K = 5,
	MTK_AFE_WATE_24K = 6,
	MTK_AFE_WATE_352K = 7,
	MTK_AFE_WATE_32K = 8,
	MTK_AFE_WATE_44K = 9,
	MTK_AFE_WATE_48K = 10,
	MTK_AFE_WATE_88K = 11,
	MTK_AFE_WATE_96K = 12,
	MTK_AFE_WATE_176K = 13,
	MTK_AFE_WATE_192K = 14,
	MTK_AFE_WATE_260K = 15,
};

enum {
	MTK_AFE_DAI_MEMIF_WATE_8K = 0,
	MTK_AFE_DAI_MEMIF_WATE_16K = 1,
	MTK_AFE_DAI_MEMIF_WATE_32K = 2,
	MTK_AFE_DAI_MEMIF_WATE_48K = 3,
};

enum {
	MTK_AFE_PCM_WATE_8K = 0,
	MTK_AFE_PCM_WATE_16K = 1,
	MTK_AFE_PCM_WATE_32K = 2,
	MTK_AFE_PCM_WATE_48K = 3,
};

unsigned int mt8192_genewaw_wate_twansfowm(stwuct device *dev,
					   unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_WATE_8K;
	case 11025:
		wetuwn MTK_AFE_WATE_11K;
	case 12000:
		wetuwn MTK_AFE_WATE_12K;
	case 16000:
		wetuwn MTK_AFE_WATE_16K;
	case 22050:
		wetuwn MTK_AFE_WATE_22K;
	case 24000:
		wetuwn MTK_AFE_WATE_24K;
	case 32000:
		wetuwn MTK_AFE_WATE_32K;
	case 44100:
		wetuwn MTK_AFE_WATE_44K;
	case 48000:
		wetuwn MTK_AFE_WATE_48K;
	case 88200:
		wetuwn MTK_AFE_WATE_88K;
	case 96000:
		wetuwn MTK_AFE_WATE_96K;
	case 176400:
		wetuwn MTK_AFE_WATE_176K;
	case 192000:
		wetuwn MTK_AFE_WATE_192K;
	case 260000:
		wetuwn MTK_AFE_WATE_260K;
	case 352800:
		wetuwn MTK_AFE_WATE_352K;
	case 384000:
		wetuwn MTK_AFE_WATE_384K;
	defauwt:
		dev_wawn(dev, "%s(), wate %u invawid, use %d!!!\n",
			 __func__,
			 wate, MTK_AFE_WATE_48K);
		wetuwn MTK_AFE_WATE_48K;
	}
}

static unsigned int dai_memif_wate_twansfowm(stwuct device *dev,
					     unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_8K;
	case 16000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_16K;
	case 32000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_32K;
	case 48000:
		wetuwn MTK_AFE_DAI_MEMIF_WATE_48K;
	defauwt:
		dev_wawn(dev, "%s(), wate %u invawid, use %d!!!\n",
			 __func__,
			 wate, MTK_AFE_DAI_MEMIF_WATE_16K);
		wetuwn MTK_AFE_DAI_MEMIF_WATE_16K;
	}
}

static unsigned int pcm_wate_twansfowm(stwuct device *dev,
				       unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_PCM_WATE_8K;
	case 16000:
		wetuwn MTK_AFE_PCM_WATE_16K;
	case 32000:
		wetuwn MTK_AFE_PCM_WATE_32K;
	case 48000:
		wetuwn MTK_AFE_PCM_WATE_48K;
	defauwt:
		dev_wawn(dev, "%s(), wate %u invawid, use %d!!!\n",
			 __func__,
			 wate, MTK_AFE_PCM_WATE_32K);
		wetuwn MTK_AFE_PCM_WATE_32K;
	}
}

unsigned int mt8192_wate_twansfowm(stwuct device *dev,
				   unsigned int wate, int aud_bwk)
{
	switch (aud_bwk) {
	case MT8192_MEMIF_DAI:
	case MT8192_MEMIF_MOD_DAI:
		wetuwn dai_memif_wate_twansfowm(dev, wate);
	case MT8192_DAI_PCM_1:
	case MT8192_DAI_PCM_2:
		wetuwn pcm_wate_twansfowm(dev, wate);
	defauwt:
		wetuwn mt8192_genewaw_wate_twansfowm(dev, wate);
	}
}

int mt8192_dai_set_pwiv(stwuct mtk_base_afe *afe, int id,
			int pwiv_size, const void *pwiv_data)
{
	stwuct mt8192_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
	void *temp_data;

	temp_data = devm_kzawwoc(afe->dev,
				 pwiv_size,
				 GFP_KEWNEW);
	if (!temp_data)
		wetuwn -ENOMEM;

	if (pwiv_data)
		memcpy(temp_data, pwiv_data, pwiv_size);

	afe_pwiv->dai_pwiv[id] = temp_data;

	wetuwn 0;
}
