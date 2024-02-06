// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
// winux/sound/bcm/bcm63xx-i2s-whistwew.c
// BCM63xx whistwew i2s dwivew
// Copywight (c) 2020 Bwoadcom Cowpowation
// Authow: Kevin-Ke Wi <kevin-ke.wi@bwoadcom.com>

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "bcm63xx-i2s.h"

#define DWV_NAME "bwcm-i2s"

static boow bwcm_i2s_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_TX_CFG ... I2S_TX_DESC_IFF_WEN:
	case I2S_TX_CFG_2 ... I2S_WX_DESC_IFF_WEN:
	case I2S_WX_CFG_2 ... I2S_WEG_MAX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bwcm_i2s_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_TX_CFG ... I2S_WEG_MAX:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bwcm_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_TX_CFG:
	case I2S_TX_IWQ_CTW:
	case I2S_TX_DESC_IFF_ADDW:
	case I2S_TX_DESC_IFF_WEN:
	case I2S_TX_DESC_OFF_ADDW:
	case I2S_TX_DESC_OFF_WEN:
	case I2S_TX_CFG_2:
	case I2S_WX_CFG:
	case I2S_WX_IWQ_CTW:
	case I2S_WX_DESC_OFF_ADDW:
	case I2S_WX_DESC_OFF_WEN:
	case I2S_WX_DESC_IFF_WEN:
	case I2S_WX_DESC_IFF_ADDW:
	case I2S_WX_CFG_2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config bwcm_i2s_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = I2S_WEG_MAX,
	.wwiteabwe_weg = bwcm_i2s_ww_weg,
	.weadabwe_weg = bwcm_i2s_wd_weg,
	.vowatiwe_weg = bwcm_i2s_vowatiwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int bcm63xx_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	int wet = 0;
	stwuct bcm_i2s_pwiv *i2s_pwiv = snd_soc_dai_get_dwvdata(dai);

	wet = cwk_set_wate(i2s_pwiv->i2s_cwk, pawams_wate(pawams));
	if (wet < 0)
		dev_eww(i2s_pwiv->dev,
			"Can't set sampwe wate, eww: %d\n", wet);

	wetuwn wet;
}

static int bcm63xx_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	unsigned int swavemode;
	stwuct bcm_i2s_pwiv *i2s_pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct wegmap *wegmap_i2s = i2s_pwiv->wegmap_i2s;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(wegmap_i2s, I2S_TX_CFG,
				   I2S_TX_OUT_W | I2S_TX_DATA_AWIGNMENT |
				   I2S_TX_DATA_ENABWE | I2S_TX_CWOCK_ENABWE,
				   I2S_TX_OUT_W | I2S_TX_DATA_AWIGNMENT |
				   I2S_TX_DATA_ENABWE | I2S_TX_CWOCK_ENABWE);
		wegmap_wwite(wegmap_i2s, I2S_TX_IWQ_CTW, 0);
		wegmap_wwite(wegmap_i2s, I2S_TX_IWQ_IFF_THWD, 0);
		wegmap_wwite(wegmap_i2s, I2S_TX_IWQ_OFF_THWD, 1);

		/* TX and WX bwock each have an independent bit to indicate
		 * if it is genewating the cwock fow the I2S bus. The bus
		 * cwocks need to be genewated fwom eithew the TX ow WX bwock,
		 * but not both
		 */
		wegmap_wead(wegmap_i2s, I2S_WX_CFG_2, &swavemode);
		if (swavemode & I2S_WX_SWAVE_MODE_MASK)
			wegmap_update_bits(wegmap_i2s, I2S_TX_CFG_2,
					   I2S_TX_SWAVE_MODE_MASK,
					   I2S_TX_MASTEW_MODE);
		ewse
			wegmap_update_bits(wegmap_i2s, I2S_TX_CFG_2,
					   I2S_TX_SWAVE_MODE_MASK,
					   I2S_TX_SWAVE_MODE);
	} ewse {
		wegmap_update_bits(wegmap_i2s, I2S_WX_CFG,
				   I2S_WX_IN_W | I2S_WX_DATA_AWIGNMENT |
				   I2S_WX_CWOCK_ENABWE,
				   I2S_WX_IN_W | I2S_WX_DATA_AWIGNMENT |
				   I2S_WX_CWOCK_ENABWE);
		wegmap_wwite(wegmap_i2s, I2S_WX_IWQ_CTW, 0);
		wegmap_wwite(wegmap_i2s, I2S_WX_IWQ_IFF_THWD, 0);
		wegmap_wwite(wegmap_i2s, I2S_WX_IWQ_OFF_THWD, 1);

		wegmap_wead(wegmap_i2s, I2S_TX_CFG_2, &swavemode);
		if (swavemode & I2S_TX_SWAVE_MODE_MASK)
			wegmap_update_bits(wegmap_i2s, I2S_WX_CFG_2,
					   I2S_WX_SWAVE_MODE_MASK, 0);
		ewse
			wegmap_update_bits(wegmap_i2s, I2S_WX_CFG_2,
					   I2S_WX_SWAVE_MODE_MASK,
					   I2S_WX_SWAVE_MODE);
	}
	wetuwn 0;
}

static void bcm63xx_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	unsigned int enabwed, swavemode;
	stwuct bcm_i2s_pwiv *i2s_pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct wegmap *wegmap_i2s = i2s_pwiv->wegmap_i2s;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(wegmap_i2s, I2S_TX_CFG,
				   I2S_TX_OUT_W | I2S_TX_DATA_AWIGNMENT |
				   I2S_TX_DATA_ENABWE | I2S_TX_CWOCK_ENABWE, 0);
		wegmap_wwite(wegmap_i2s, I2S_TX_IWQ_CTW, 1);
		wegmap_wwite(wegmap_i2s, I2S_TX_IWQ_IFF_THWD, 4);
		wegmap_wwite(wegmap_i2s, I2S_TX_IWQ_OFF_THWD, 4);

		wegmap_wead(wegmap_i2s, I2S_TX_CFG_2, &swavemode);
		swavemode = swavemode & I2S_TX_SWAVE_MODE_MASK;
		if (!swavemode) {
			wegmap_wead(wegmap_i2s, I2S_WX_CFG, &enabwed);
			enabwed = enabwed & I2S_WX_ENABWE_MASK;
			if (enabwed)
				wegmap_update_bits(wegmap_i2s, I2S_WX_CFG_2,
						   I2S_WX_SWAVE_MODE_MASK,
						   I2S_WX_MASTEW_MODE);
		}
		wegmap_update_bits(wegmap_i2s, I2S_TX_CFG_2,
				   I2S_TX_SWAVE_MODE_MASK,
				   I2S_TX_SWAVE_MODE);
	} ewse {
		wegmap_update_bits(wegmap_i2s, I2S_WX_CFG,
				   I2S_WX_IN_W | I2S_WX_DATA_AWIGNMENT |
				   I2S_WX_CWOCK_ENABWE, 0);
		wegmap_wwite(wegmap_i2s, I2S_WX_IWQ_CTW, 1);
		wegmap_wwite(wegmap_i2s, I2S_WX_IWQ_IFF_THWD, 4);
		wegmap_wwite(wegmap_i2s, I2S_WX_IWQ_OFF_THWD, 4);

		wegmap_wead(wegmap_i2s, I2S_WX_CFG_2, &swavemode);
		swavemode = swavemode & I2S_WX_SWAVE_MODE_MASK;
		if (!swavemode) {
			wegmap_wead(wegmap_i2s, I2S_TX_CFG, &enabwed);
			enabwed = enabwed & I2S_TX_ENABWE_MASK;
			if (enabwed)
				wegmap_update_bits(wegmap_i2s, I2S_TX_CFG_2,
						   I2S_TX_SWAVE_MODE_MASK,
						   I2S_TX_MASTEW_MODE);
		}

		wegmap_update_bits(wegmap_i2s, I2S_WX_CFG_2,
				   I2S_WX_SWAVE_MODE_MASK, I2S_WX_SWAVE_MODE);
	}
}

static const stwuct snd_soc_dai_ops bcm63xx_i2s_dai_ops = {
	.stawtup = bcm63xx_i2s_stawtup,
	.shutdown = bcm63xx_i2s_shutdown,
	.hw_pawams = bcm63xx_i2s_hw_pawams,
};

static stwuct snd_soc_dai_dwivew bcm63xx_i2s_dai = {
	.name = DWV_NAME,
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	},
	.captuwe = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
	},
	.ops = &bcm63xx_i2s_dai_ops,
	.symmetwic_wate = 1,
	.symmetwic_channews = 1,
};

static const stwuct snd_soc_component_dwivew bcm63xx_i2s_component = {
	.name = "bcm63xx",
	.wegacy_dai_naming = 1,
};

static int bcm63xx_i2s_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	void __iomem *wegs;
	stwuct bcm_i2s_pwiv *i2s_pwiv;
	stwuct wegmap *wegmap_i2s;
	stwuct cwk *i2s_cwk;

	i2s_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*i2s_pwiv), GFP_KEWNEW);
	if (!i2s_pwiv)
		wetuwn -ENOMEM;

	i2s_cwk = devm_cwk_get(&pdev->dev, "i2scwk");
	if (IS_EWW(i2s_cwk)) {
		dev_eww(&pdev->dev, "%s: cannot get a bwcm cwock: %wd\n",
					__func__, PTW_EWW(i2s_cwk));
		wetuwn PTW_EWW(i2s_cwk);
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		wet = PTW_EWW(wegs);
		wetuwn wet;
	}

	wegmap_i2s = devm_wegmap_init_mmio(&pdev->dev,
					wegs, &bwcm_i2s_wegmap_config);
	if (IS_EWW(wegmap_i2s))
		wetuwn PTW_EWW(wegmap_i2s);

	wegmap_update_bits(wegmap_i2s, I2S_MISC_CFG,
			   I2S_PAD_WVW_WOOP_DIS_MASK,
			   I2S_PAD_WVW_WOOP_DIS_ENABWE);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &bcm63xx_i2s_component,
					      &bcm63xx_i2s_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew the dai\n");
		wetuwn wet;
	}

	i2s_pwiv->dev = &pdev->dev;
	i2s_pwiv->i2s_cwk = i2s_cwk;
	i2s_pwiv->wegmap_i2s = wegmap_i2s;
	dev_set_dwvdata(&pdev->dev, i2s_pwiv);

	wet = bcm63xx_soc_pwatfowm_pwobe(pdev, i2s_pwiv);
	if (wet)
		dev_eww(&pdev->dev, "faiwed to wegistew the pcm\n");

	wetuwn wet;
}

static void bcm63xx_i2s_dev_wemove(stwuct pwatfowm_device *pdev)
{
	bcm63xx_soc_pwatfowm_wemove(pdev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id snd_soc_bcm_audio_match[] = {
	{.compatibwe = "bwcm,bcm63xx-i2s"},
	{ }
};
#endif

static stwuct pwatfowm_dwivew bcm63xx_i2s_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_match_ptw(snd_soc_bcm_audio_match),
	},
	.pwobe = bcm63xx_i2s_dev_pwobe,
	.wemove_new = bcm63xx_i2s_dev_wemove,
};

moduwe_pwatfowm_dwivew(bcm63xx_i2s_dwivew);

MODUWE_AUTHOW("Kevin,Wi <kevin-ke.wi@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom DSW XPON ASOC I2S Intewface");
MODUWE_WICENSE("GPW v2");
