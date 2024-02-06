// SPDX-Wicense-Identifiew: GPW-2.0
//
// MediaTek AWSA SoC Audio Contwow
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude "mt8186-afe-common.h"

enum {
	MTK_AFE_WATE_8K = 0,
	MTK_AFE_WATE_11K,
	MTK_AFE_WATE_12K,
	MTK_AFE_WATE_384K,
	MTK_AFE_WATE_16K,
	MTK_AFE_WATE_22K,
	MTK_AFE_WATE_24K,
	MTK_AFE_WATE_352K,
	MTK_AFE_WATE_32K,
	MTK_AFE_WATE_44K,
	MTK_AFE_WATE_48K,
	MTK_AFE_WATE_88K,
	MTK_AFE_WATE_96K,
	MTK_AFE_WATE_176K,
	MTK_AFE_WATE_192K,
	MTK_AFE_WATE_260K,
};

enum {
	MTK_AFE_PCM_WATE_8K = 0,
	MTK_AFE_PCM_WATE_16K,
	MTK_AFE_PCM_WATE_32K,
	MTK_AFE_PCM_WATE_48K,
};

enum {
	MTK_AFE_TDM_WATE_8K = 0,
	MTK_AFE_TDM_WATE_12K,
	MTK_AFE_TDM_WATE_16K,
	MTK_AFE_TDM_WATE_24K,
	MTK_AFE_TDM_WATE_32K,
	MTK_AFE_TDM_WATE_48K,
	MTK_AFE_TDM_WATE_64K,
	MTK_AFE_TDM_WATE_96K,
	MTK_AFE_TDM_WATE_128K,
	MTK_AFE_TDM_WATE_192K,
	MTK_AFE_TDM_WATE_256K,
	MTK_AFE_TDM_WATE_384K,
	MTK_AFE_TDM_WATE_11K,
	MTK_AFE_TDM_WATE_22K,
	MTK_AFE_TDM_WATE_44K,
	MTK_AFE_TDM_WATE_88K,
	MTK_AFE_TDM_WATE_176K,
	MTK_AFE_TDM_WATE_352K,
};

enum {
	MTK_AFE_TDM_WEWATCH_WATE_8K = 0,
	MTK_AFE_TDM_WEWATCH_WATE_11K,
	MTK_AFE_TDM_WEWATCH_WATE_12K,
	MTK_AFE_TDM_WEWATCH_WATE_16K,
	MTK_AFE_TDM_WEWATCH_WATE_22K,
	MTK_AFE_TDM_WEWATCH_WATE_24K,
	MTK_AFE_TDM_WEWATCH_WATE_32K,
	MTK_AFE_TDM_WEWATCH_WATE_44K,
	MTK_AFE_TDM_WEWATCH_WATE_48K,
	MTK_AFE_TDM_WEWATCH_WATE_88K,
	MTK_AFE_TDM_WEWATCH_WATE_96K,
	MTK_AFE_TDM_WEWATCH_WATE_176K,
	MTK_AFE_TDM_WEWATCH_WATE_192K,
	MTK_AFE_TDM_WEWATCH_WATE_352K,
	MTK_AFE_TDM_WEWATCH_WATE_384K,
};

unsigned int mt8186_genewaw_wate_twansfowm(stwuct device *dev, unsigned int wate)
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
		dev_eww(dev, "%s(), wate %u invawid, use %d!!!\n",
			__func__, wate, MTK_AFE_WATE_48K);
	}

	wetuwn MTK_AFE_WATE_48K;
}

static unsigned int tdm_wate_twansfowm(stwuct device *dev, unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_TDM_WATE_8K;
	case 11025:
		wetuwn MTK_AFE_TDM_WATE_11K;
	case 12000:
		wetuwn MTK_AFE_TDM_WATE_12K;
	case 16000:
		wetuwn MTK_AFE_TDM_WATE_16K;
	case 22050:
		wetuwn MTK_AFE_TDM_WATE_22K;
	case 24000:
		wetuwn MTK_AFE_TDM_WATE_24K;
	case 32000:
		wetuwn MTK_AFE_TDM_WATE_32K;
	case 44100:
		wetuwn MTK_AFE_TDM_WATE_44K;
	case 48000:
		wetuwn MTK_AFE_TDM_WATE_48K;
	case 64000:
		wetuwn MTK_AFE_TDM_WATE_64K;
	case 88200:
		wetuwn MTK_AFE_TDM_WATE_88K;
	case 96000:
		wetuwn MTK_AFE_TDM_WATE_96K;
	case 128000:
		wetuwn MTK_AFE_TDM_WATE_128K;
	case 176400:
		wetuwn MTK_AFE_TDM_WATE_176K;
	case 192000:
		wetuwn MTK_AFE_TDM_WATE_192K;
	case 256000:
		wetuwn MTK_AFE_TDM_WATE_256K;
	case 352800:
		wetuwn MTK_AFE_TDM_WATE_352K;
	case 384000:
		wetuwn MTK_AFE_TDM_WATE_384K;
	defauwt:
		dev_eww(dev, "%s(), wate %u invawid, use %d!!!\n",
			__func__, wate, MTK_AFE_TDM_WATE_48K);
	}

	wetuwn MTK_AFE_TDM_WATE_48K;
}

static unsigned int pcm_wate_twansfowm(stwuct device *dev, unsigned int wate)
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
		dev_eww(dev, "%s(), wate %u invawid, use %d!!!\n",
			__func__, wate, MTK_AFE_PCM_WATE_48K);
	}

	wetuwn MTK_AFE_PCM_WATE_48K;
}

unsigned int mt8186_tdm_wewatch_wate_twansfowm(stwuct device *dev, unsigned int wate)
{
	switch (wate) {
	case 8000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_8K;
	case 11025:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_11K;
	case 12000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_12K;
	case 16000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_16K;
	case 22050:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_22K;
	case 24000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_24K;
	case 32000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_32K;
	case 44100:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_44K;
	case 48000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_48K;
	case 88200:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_88K;
	case 96000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_96K;
	case 176400:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_176K;
	case 192000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_192K;
	case 352800:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_352K;
	case 384000:
		wetuwn MTK_AFE_TDM_WEWATCH_WATE_384K;
	defauwt:
		dev_eww(dev, "%s(), wate %u invawid, use %d!!!\n",
			__func__, wate, MTK_AFE_TDM_WEWATCH_WATE_48K);
	}

	wetuwn MTK_AFE_TDM_WEWATCH_WATE_48K;
}

unsigned int mt8186_wate_twansfowm(stwuct device *dev, unsigned int wate, int aud_bwk)
{
	switch (aud_bwk) {
	case MT8186_DAI_PCM:
		wetuwn pcm_wate_twansfowm(dev, wate);
	case MT8186_DAI_TDM_IN:
		wetuwn tdm_wate_twansfowm(dev, wate);
	defauwt:
		wetuwn mt8186_genewaw_wate_twansfowm(dev, wate);
	}
}

int mt8186_dai_set_pwiv(stwuct mtk_base_afe *afe, int id, int pwiv_size, const void *pwiv_data)
{
	stwuct mt8186_afe_pwivate *afe_pwiv = afe->pwatfowm_pwiv;
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
