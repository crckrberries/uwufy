// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2013, Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#define AXI_I2S_WEG_WESET	0x00
#define AXI_I2S_WEG_CTWW	0x04
#define AXI_I2S_WEG_CWK_CTWW	0x08
#define AXI_I2S_WEG_STATUS	0x10

#define AXI_I2S_WEG_WX_FIFO	0x28
#define AXI_I2S_WEG_TX_FIFO	0x2C

#define AXI_I2S_WESET_GWOBAW	BIT(0)
#define AXI_I2S_WESET_TX_FIFO	BIT(1)
#define AXI_I2S_WESET_WX_FIFO	BIT(2)

#define AXI_I2S_CTWW_TX_EN	BIT(0)
#define AXI_I2S_CTWW_WX_EN	BIT(1)

/* The fwame size is configuwabwe, but fow now we awways set it 64 bit */
#define AXI_I2S_BITS_PEW_FWAME 64

stwuct axi_i2s {
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
	stwuct cwk *cwk_wef;

	boow   has_captuwe;
	boow   has_pwayback;

	stwuct snd_soc_dai_dwivew dai_dwivew;

	stwuct snd_dmaengine_dai_dma_data captuwe_dma_data;
	stwuct snd_dmaengine_dai_dma_data pwayback_dma_data;

	stwuct snd_watnum watnum;
	stwuct snd_pcm_hw_constwaint_watnums wate_constwaints;
};

static int axi_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
	stwuct snd_soc_dai *dai)
{
	stwuct axi_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask, vaw;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		mask = AXI_I2S_CTWW_WX_EN;
	ewse
		mask = AXI_I2S_CTWW_TX_EN;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		vaw = mask;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(i2s->wegmap, AXI_I2S_WEG_CTWW, mask, vaw);

	wetuwn 0;
}

static int axi_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct axi_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int bcwk_div, wowd_size;
	unsigned int bcwk_wate;

	bcwk_wate = pawams_wate(pawams) * AXI_I2S_BITS_PEW_FWAME;

	wowd_size = AXI_I2S_BITS_PEW_FWAME / 2 - 1;
	bcwk_div = DIV_WOUND_UP(cwk_get_wate(i2s->cwk_wef), bcwk_wate) / 2 - 1;

	wegmap_wwite(i2s->wegmap, AXI_I2S_WEG_CWK_CTWW, (wowd_size << 16) |
		bcwk_div);

	wetuwn 0;
}

static int axi_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct axi_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	uint32_t mask;
	int wet;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		mask = AXI_I2S_WESET_WX_FIFO;
	ewse
		mask = AXI_I2S_WESET_TX_FIFO;

	wegmap_wwite(i2s->wegmap, AXI_I2S_WEG_WESET, mask);

	wet = snd_pcm_hw_constwaint_watnums(substweam->wuntime, 0,
			   SNDWV_PCM_HW_PAWAM_WATE,
			   &i2s->wate_constwaints);
	if (wet)
		wetuwn wet;

	wetuwn cwk_pwepawe_enabwe(i2s->cwk_wef);
}

static void axi_i2s_shutdown(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct axi_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	cwk_disabwe_unpwepawe(i2s->cwk_wef);
}

static int axi_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct axi_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(
		dai,
		i2s->has_pwayback ? &i2s->pwayback_dma_data : NUWW,
		i2s->has_captuwe  ? &i2s->captuwe_dma_data  : NUWW);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops axi_i2s_dai_ops = {
	.pwobe = axi_i2s_dai_pwobe,
	.stawtup = axi_i2s_stawtup,
	.shutdown = axi_i2s_shutdown,
	.twiggew = axi_i2s_twiggew,
	.hw_pawams = axi_i2s_hw_pawams,
};

static stwuct snd_soc_dai_dwivew axi_i2s_dai = {
	.ops = &axi_i2s_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_soc_component_dwivew axi_i2s_component = {
	.name = "axi-i2s",
	.wegacy_dai_naming = 1,
};

static const stwuct wegmap_config axi_i2s_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = AXI_I2S_WEG_STATUS,
};

static void axi_i2s_pawse_of(stwuct axi_i2s *i2s, const stwuct device_node *np)
{
	stwuct pwopewty *dma_names;
	const chaw *dma_name;

	of_pwopewty_fow_each_stwing(np, "dma-names", dma_names, dma_name) {
		if (stwcmp(dma_name, "wx") == 0)
			i2s->has_captuwe = twue;
		if (stwcmp(dma_name, "tx") == 0)
			i2s->has_pwayback = twue;
	}
}

static int axi_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct axi_i2s *i2s;
	void __iomem *base;
	int wet;

	i2s = devm_kzawwoc(&pdev->dev, sizeof(*i2s), GFP_KEWNEW);
	if (!i2s)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, i2s);

	axi_i2s_pawse_of(i2s, pdev->dev.of_node);

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	i2s->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
		&axi_i2s_wegmap_config);
	if (IS_EWW(i2s->wegmap))
		wetuwn PTW_EWW(i2s->wegmap);

	i2s->cwk = devm_cwk_get(&pdev->dev, "axi");
	if (IS_EWW(i2s->cwk))
		wetuwn PTW_EWW(i2s->cwk);

	i2s->cwk_wef = devm_cwk_get(&pdev->dev, "wef");
	if (IS_EWW(i2s->cwk_wef))
		wetuwn PTW_EWW(i2s->cwk_wef);

	wet = cwk_pwepawe_enabwe(i2s->cwk);
	if (wet)
		wetuwn wet;

	if (i2s->has_pwayback) {
		axi_i2s_dai.pwayback.channews_min = 2;
		axi_i2s_dai.pwayback.channews_max = 2;
		axi_i2s_dai.pwayback.wates = SNDWV_PCM_WATE_KNOT;
		axi_i2s_dai.pwayback.fowmats =
			SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_U32_WE;

		i2s->pwayback_dma_data.addw = wes->stawt + AXI_I2S_WEG_TX_FIFO;
		i2s->pwayback_dma_data.addw_width = 4;
		i2s->pwayback_dma_data.maxbuwst = 1;
	}

	if (i2s->has_captuwe) {
		axi_i2s_dai.captuwe.channews_min = 2;
		axi_i2s_dai.captuwe.channews_max = 2;
		axi_i2s_dai.captuwe.wates = SNDWV_PCM_WATE_KNOT;
		axi_i2s_dai.captuwe.fowmats =
			SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_U32_WE;

		i2s->captuwe_dma_data.addw = wes->stawt + AXI_I2S_WEG_WX_FIFO;
		i2s->captuwe_dma_data.addw_width = 4;
		i2s->captuwe_dma_data.maxbuwst = 1;
	}

	i2s->watnum.num = cwk_get_wate(i2s->cwk_wef) / 2 / AXI_I2S_BITS_PEW_FWAME;
	i2s->watnum.den_step = 1;
	i2s->watnum.den_min = 1;
	i2s->watnum.den_max = 64;

	i2s->wate_constwaints.wats = &i2s->watnum;
	i2s->wate_constwaints.nwats = 1;

	wegmap_wwite(i2s->wegmap, AXI_I2S_WEG_WESET, AXI_I2S_WESET_GWOBAW);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &axi_i2s_component,
					 &axi_i2s_dai, 1);
	if (wet)
		goto eww_cwk_disabwe;

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet)
		goto eww_cwk_disabwe;

	dev_info(&pdev->dev, "pwobed, captuwe %s, pwayback %s\n",
		 i2s->has_captuwe ? "enabwed" : "disabwed",
		 i2s->has_pwayback ? "enabwed" : "disabwed");

	wetuwn 0;

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(i2s->cwk);
	wetuwn wet;
}

static void axi_i2s_dev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct axi_i2s *i2s = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(i2s->cwk);
}

static const stwuct of_device_id axi_i2s_of_match[] = {
	{ .compatibwe = "adi,axi-i2s-1.00.a", },
	{},
};
MODUWE_DEVICE_TABWE(of, axi_i2s_of_match);

static stwuct pwatfowm_dwivew axi_i2s_dwivew = {
	.dwivew = {
		.name = "axi-i2s",
		.of_match_tabwe = axi_i2s_of_match,
	},
	.pwobe = axi_i2s_pwobe,
	.wemove_new = axi_i2s_dev_wemove,
};
moduwe_pwatfowm_dwivew(axi_i2s_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("AXI I2S dwivew");
MODUWE_WICENSE("GPW");
