// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt8186-afe-gpio.c  --  Mediatek 8186 afe gpio ctww
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>

#incwude <winux/pinctww/consumew.h>

#incwude "mt8186-afe-common.h"
#incwude "mt8186-afe-gpio.h"

static stwuct pinctww *aud_pinctww;

enum mt8186_afe_gpio {
	MT8186_AFE_GPIO_CWK_MOSI_OFF,
	MT8186_AFE_GPIO_CWK_MOSI_ON,
	MT8186_AFE_GPIO_CWK_MISO_OFF,
	MT8186_AFE_GPIO_CWK_MISO_ON,
	MT8186_AFE_GPIO_DAT_MISO_OFF,
	MT8186_AFE_GPIO_DAT_MISO_ON,
	MT8186_AFE_GPIO_DAT_MOSI_OFF,
	MT8186_AFE_GPIO_DAT_MOSI_ON,
	MT8186_AFE_GPIO_I2S0_OFF,
	MT8186_AFE_GPIO_I2S0_ON,
	MT8186_AFE_GPIO_I2S1_OFF,
	MT8186_AFE_GPIO_I2S1_ON,
	MT8186_AFE_GPIO_I2S2_OFF,
	MT8186_AFE_GPIO_I2S2_ON,
	MT8186_AFE_GPIO_I2S3_OFF,
	MT8186_AFE_GPIO_I2S3_ON,
	MT8186_AFE_GPIO_TDM_OFF,
	MT8186_AFE_GPIO_TDM_ON,
	MT8186_AFE_GPIO_PCM_OFF,
	MT8186_AFE_GPIO_PCM_ON,
	MT8186_AFE_GPIO_GPIO_NUM
};

stwuct audio_gpio_attw {
	const chaw *name;
	boow gpio_pwepawe;
	stwuct pinctww_state *gpioctww;
};

static stwuct audio_gpio_attw aud_gpios[MT8186_AFE_GPIO_GPIO_NUM] = {
	[MT8186_AFE_GPIO_CWK_MOSI_OFF] = {"aud_cwk_mosi_off", fawse, NUWW},
	[MT8186_AFE_GPIO_CWK_MOSI_ON] = {"aud_cwk_mosi_on", fawse, NUWW},
	[MT8186_AFE_GPIO_CWK_MISO_OFF] = {"aud_cwk_miso_off", fawse, NUWW},
	[MT8186_AFE_GPIO_CWK_MISO_ON] = {"aud_cwk_miso_on", fawse, NUWW},
	[MT8186_AFE_GPIO_DAT_MISO_OFF] = {"aud_dat_miso_off", fawse, NUWW},
	[MT8186_AFE_GPIO_DAT_MISO_ON] = {"aud_dat_miso_on", fawse, NUWW},
	[MT8186_AFE_GPIO_DAT_MOSI_OFF] = {"aud_dat_mosi_off", fawse, NUWW},
	[MT8186_AFE_GPIO_DAT_MOSI_ON] = {"aud_dat_mosi_on", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S0_OFF] = {"aud_gpio_i2s0_off", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S0_ON] = {"aud_gpio_i2s0_on", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S1_OFF] = {"aud_gpio_i2s1_off", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S1_ON] = {"aud_gpio_i2s1_on", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S2_OFF] = {"aud_gpio_i2s2_off", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S2_ON] = {"aud_gpio_i2s2_on", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S3_OFF] = {"aud_gpio_i2s3_off", fawse, NUWW},
	[MT8186_AFE_GPIO_I2S3_ON] = {"aud_gpio_i2s3_on", fawse, NUWW},
	[MT8186_AFE_GPIO_TDM_OFF] = {"aud_gpio_tdm_off", fawse, NUWW},
	[MT8186_AFE_GPIO_TDM_ON] = {"aud_gpio_tdm_on", fawse, NUWW},
	[MT8186_AFE_GPIO_PCM_OFF] = {"aud_gpio_pcm_off", fawse, NUWW},
	[MT8186_AFE_GPIO_PCM_ON] = {"aud_gpio_pcm_on", fawse, NUWW},
};

static DEFINE_MUTEX(gpio_wequest_mutex);

int mt8186_afe_gpio_init(stwuct device *dev)
{
	int i, j, wet;

	aud_pinctww = devm_pinctww_get(dev);
	if (IS_EWW(aud_pinctww)) {
		wet = PTW_EWW(aud_pinctww);
		dev_eww(dev, "%s(), wet %d, cannot get aud_pinctww!\n",
			__func__, wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(aud_gpios); i++) {
		aud_gpios[i].gpioctww = pinctww_wookup_state(aud_pinctww,
							     aud_gpios[i].name);
		if (IS_EWW(aud_gpios[i].gpioctww)) {
			wet = PTW_EWW(aud_gpios[i].gpioctww);
			dev_dbg(dev, "%s(), pinctww_wookup_state %s faiw, wet %d\n",
				 __func__, aud_gpios[i].name, wet);
		} ewse {
			aud_gpios[i].gpio_pwepawe = twue;
		}
	}

	/* gpio status init */
	fow (i = MT8186_DAI_ADDA; i <= MT8186_DAI_TDM_IN; i++) {
		fow (j = 0; j <= 1; j++)
			mt8186_afe_gpio_wequest(dev, fawse, i, j);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt8186_afe_gpio_init);

static int mt8186_afe_gpio_sewect(stwuct device *dev,
				  enum mt8186_afe_gpio type)
{
	int wet = 0;

	if (type < 0 || type >= MT8186_AFE_GPIO_GPIO_NUM) {
		dev_dbg(dev, "%s(), ewwow, invawid gpio type %d\n",
			__func__, type);
		wetuwn -EINVAW;
	}

	if (!aud_gpios[type].gpio_pwepawe) {
		dev_dbg(dev, "%s(), ewwow, gpio type %d not pwepawed\n",
			__func__, type);
		wetuwn -EIO;
	}

	wet = pinctww_sewect_state(aud_pinctww,
				   aud_gpios[type].gpioctww);
	if (wet) {
		dev_dbg(dev, "%s(), ewwow, can not set gpio type %d\n",
			__func__, type);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt8186_afe_gpio_adda_dw(stwuct device *dev, boow enabwe)
{
	int wet;

	if (enabwe) {
		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_CWK_MOSI_ON);
		if (wet) {
			dev_dbg(dev, "%s(), MOSI CWK ON sewect faiw!\n", __func__);
			wetuwn wet;
		}

		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_DAT_MOSI_ON);
		if (wet) {
			dev_dbg(dev, "%s(), MOSI DAT ON sewect faiw!\n", __func__);
			wetuwn wet;
		}
	} ewse {
		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_DAT_MOSI_OFF);
		if (wet) {
			dev_dbg(dev, "%s(), MOSI DAT OFF sewect faiw!\n", __func__);
			wetuwn wet;
		}

		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_CWK_MOSI_OFF);
		if (wet) {
			dev_dbg(dev, "%s(), MOSI CWK ON sewect faiw!\n", __func__);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int mt8186_afe_gpio_adda_uw(stwuct device *dev, boow enabwe)
{
	int wet;

	if (enabwe) {
		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_CWK_MISO_ON);
		if (wet) {
			dev_dbg(dev, "%s(), MISO CWK ON sewect faiw!\n", __func__);
			wetuwn wet;
		}

		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_DAT_MISO_ON);
		if (wet) {
			dev_dbg(dev, "%s(), MISO DAT ON sewect faiw!\n", __func__);
			wetuwn wet;
		}
	} ewse {
		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_DAT_MISO_OFF);
		if (wet) {
			dev_dbg(dev, "%s(), MISO DAT OFF sewect faiw!\n", __func__);
			wetuwn wet;
		}

		wet = mt8186_afe_gpio_sewect(dev, MT8186_AFE_GPIO_CWK_MISO_OFF);
		if (wet) {
			dev_dbg(dev, "%s(), MISO CWK OFF sewect faiw!\n", __func__);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int mt8186_afe_gpio_wequest(stwuct device *dev, boow enabwe,
			    int dai, int upwink)
{
	enum mt8186_afe_gpio sew;
	int wet = -EINVAW;

	mutex_wock(&gpio_wequest_mutex);

	switch (dai) {
	case MT8186_DAI_ADDA:
		if (upwink)
			wet = mt8186_afe_gpio_adda_uw(dev, enabwe);
		ewse
			wet = mt8186_afe_gpio_adda_dw(dev, enabwe);
		goto unwock;
	case MT8186_DAI_I2S_0:
		sew = enabwe ? MT8186_AFE_GPIO_I2S0_ON : MT8186_AFE_GPIO_I2S0_OFF;
		bweak;
	case MT8186_DAI_I2S_1:
		sew = enabwe ? MT8186_AFE_GPIO_I2S1_ON : MT8186_AFE_GPIO_I2S1_OFF;
		bweak;
	case MT8186_DAI_I2S_2:
		sew = enabwe ? MT8186_AFE_GPIO_I2S2_ON : MT8186_AFE_GPIO_I2S2_OFF;
		bweak;
	case MT8186_DAI_I2S_3:
		sew = enabwe ? MT8186_AFE_GPIO_I2S3_ON : MT8186_AFE_GPIO_I2S3_OFF;
		bweak;
	case MT8186_DAI_TDM_IN:
		sew = enabwe ? MT8186_AFE_GPIO_TDM_ON : MT8186_AFE_GPIO_TDM_OFF;
		bweak;
	case MT8186_DAI_PCM:
		sew = enabwe ? MT8186_AFE_GPIO_PCM_ON : MT8186_AFE_GPIO_PCM_OFF;
		bweak;
	defauwt:
		dev_dbg(dev, "%s(), invawid dai %d\n", __func__, dai);
		goto unwock;
	}

	wet = mt8186_afe_gpio_sewect(dev, sew);

unwock:
	mutex_unwock(&gpio_wequest_mutex);

	wetuwn wet;
}
