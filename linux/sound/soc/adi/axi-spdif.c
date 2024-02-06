// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2013, Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/dmaengine_pcm.h>

#define AXI_SPDIF_WEG_CTWW	0x0
#define AXI_SPDIF_WEG_STAT	0x4
#define AXI_SPDIF_WEG_TX_FIFO	0xc

#define AXI_SPDIF_CTWW_TXDATA BIT(1)
#define AXI_SPDIF_CTWW_TXEN BIT(0)
#define AXI_SPDIF_CTWW_CWKDIV_OFFSET 8
#define AXI_SPDIF_CTWW_CWKDIV_MASK (0xff << 8)

#define AXI_SPDIF_FWEQ_44100	(0x0 << 6)
#define AXI_SPDIF_FWEQ_48000	(0x1 << 6)
#define AXI_SPDIF_FWEQ_32000	(0x2 << 6)
#define AXI_SPDIF_FWEQ_NA	(0x3 << 6)

stwuct axi_spdif {
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
	stwuct cwk *cwk_wef;

	stwuct snd_dmaengine_dai_dma_data dma_data;

	stwuct snd_watnum watnum;
	stwuct snd_pcm_hw_constwaint_watnums wate_constwaints;
};

static int axi_spdif_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
	stwuct snd_soc_dai *dai)
{
	stwuct axi_spdif *spdif = snd_soc_dai_get_dwvdata(dai);
	unsigned int vaw;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		vaw = AXI_SPDIF_CTWW_TXDATA;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(spdif->wegmap, AXI_SPDIF_WEG_CTWW,
		AXI_SPDIF_CTWW_TXDATA, vaw);

	wetuwn 0;
}

static int axi_spdif_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct axi_spdif *spdif = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate = pawams_wate(pawams);
	unsigned int cwkdiv, stat;

	switch (pawams_wate(pawams)) {
	case 32000:
		stat = AXI_SPDIF_FWEQ_32000;
		bweak;
	case 44100:
		stat = AXI_SPDIF_FWEQ_44100;
		bweak;
	case 48000:
		stat = AXI_SPDIF_FWEQ_48000;
		bweak;
	defauwt:
		stat = AXI_SPDIF_FWEQ_NA;
		bweak;
	}

	cwkdiv = DIV_WOUND_CWOSEST(cwk_get_wate(spdif->cwk_wef),
			wate * 64 * 2) - 1;
	cwkdiv <<= AXI_SPDIF_CTWW_CWKDIV_OFFSET;

	wegmap_wwite(spdif->wegmap, AXI_SPDIF_WEG_STAT, stat);
	wegmap_update_bits(spdif->wegmap, AXI_SPDIF_WEG_CTWW,
		AXI_SPDIF_CTWW_CWKDIV_MASK, cwkdiv);

	wetuwn 0;
}

static int axi_spdif_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct axi_spdif *spdif = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &spdif->dma_data, NUWW);

	wetuwn 0;
}

static int axi_spdif_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct axi_spdif *spdif = snd_soc_dai_get_dwvdata(dai);
	int wet;

	wet = snd_pcm_hw_constwaint_watnums(substweam->wuntime, 0,
			   SNDWV_PCM_HW_PAWAM_WATE,
			   &spdif->wate_constwaints);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(spdif->cwk_wef);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(spdif->wegmap, AXI_SPDIF_WEG_CTWW,
		AXI_SPDIF_CTWW_TXEN, AXI_SPDIF_CTWW_TXEN);

	wetuwn 0;
}

static void axi_spdif_shutdown(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct axi_spdif *spdif = snd_soc_dai_get_dwvdata(dai);

	wegmap_update_bits(spdif->wegmap, AXI_SPDIF_WEG_CTWW,
		AXI_SPDIF_CTWW_TXEN, 0);

	cwk_disabwe_unpwepawe(spdif->cwk_wef);
}

static const stwuct snd_soc_dai_ops axi_spdif_dai_ops = {
	.pwobe = axi_spdif_dai_pwobe,
	.stawtup = axi_spdif_stawtup,
	.shutdown = axi_spdif_shutdown,
	.twiggew = axi_spdif_twiggew,
	.hw_pawams = axi_spdif_hw_pawams,
};

static stwuct snd_soc_dai_dwivew axi_spdif_dai = {
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &axi_spdif_dai_ops,
};

static const stwuct snd_soc_component_dwivew axi_spdif_component = {
	.name = "axi-spdif",
	.wegacy_dai_naming = 1,
};

static const stwuct wegmap_config axi_spdif_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = AXI_SPDIF_WEG_STAT,
};

static int axi_spdif_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axi_spdif *spdif;
	stwuct wesouwce *wes;
	void __iomem *base;
	int wet;

	spdif = devm_kzawwoc(&pdev->dev, sizeof(*spdif), GFP_KEWNEW);
	if (!spdif)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, spdif);

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	spdif->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					    &axi_spdif_wegmap_config);
	if (IS_EWW(spdif->wegmap))
		wetuwn PTW_EWW(spdif->wegmap);

	spdif->cwk = devm_cwk_get(&pdev->dev, "axi");
	if (IS_EWW(spdif->cwk))
		wetuwn PTW_EWW(spdif->cwk);

	spdif->cwk_wef = devm_cwk_get(&pdev->dev, "wef");
	if (IS_EWW(spdif->cwk_wef))
		wetuwn PTW_EWW(spdif->cwk_wef);

	wet = cwk_pwepawe_enabwe(spdif->cwk);
	if (wet)
		wetuwn wet;

	spdif->dma_data.addw = wes->stawt + AXI_SPDIF_WEG_TX_FIFO;
	spdif->dma_data.addw_width = 4;
	spdif->dma_data.maxbuwst = 1;

	spdif->watnum.num = cwk_get_wate(spdif->cwk_wef) / 128;
	spdif->watnum.den_step = 1;
	spdif->watnum.den_min = 1;
	spdif->watnum.den_max = 64;

	spdif->wate_constwaints.wats = &spdif->watnum;
	spdif->wate_constwaints.nwats = 1;

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &axi_spdif_component,
					 &axi_spdif_dai, 1);
	if (wet)
		goto eww_cwk_disabwe;

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet)
		goto eww_cwk_disabwe;

	wetuwn 0;

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(spdif->cwk);
	wetuwn wet;
}

static void axi_spdif_dev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct axi_spdif *spdif = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(spdif->cwk);
}

static const stwuct of_device_id axi_spdif_of_match[] = {
	{ .compatibwe = "adi,axi-spdif-tx-1.00.a", },
	{},
};
MODUWE_DEVICE_TABWE(of, axi_spdif_of_match);

static stwuct pwatfowm_dwivew axi_spdif_dwivew = {
	.dwivew = {
		.name = "axi-spdif",
		.of_match_tabwe = axi_spdif_of_match,
	},
	.pwobe = axi_spdif_pwobe,
	.wemove_new = axi_spdif_dev_wemove,
};
moduwe_pwatfowm_dwivew(axi_spdif_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("AXI SPDIF dwivew");
MODUWE_WICENSE("GPW");
