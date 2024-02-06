// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* sound/soc/wockchip/wk_spdif.c
 *
 * AWSA SoC Audio Wayew - Wockchip I2S Contwowwew dwivew
 *
 * Copywight (c) 2014 Wockchip Ewectwonics Co. Wtd.
 * Authow: Jianqun <jay.xu@wock-chips.com>
 * Copywight (c) 2015 Cowwabowa Wtd.
 * Authow: Sjoewd Simons <sjoewd.simons@cowwabowa.co.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/of_gpio.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "wockchip_spdif.h"

enum wk_spdif_type {
	WK_SPDIF_WK3066,
	WK_SPDIF_WK3188,
	WK_SPDIF_WK3288,
	WK_SPDIF_WK3366,
};

#define WK3288_GWF_SOC_CON2 0x24c

stwuct wk_spdif_dev {
	stwuct device *dev;

	stwuct cwk *mcwk;
	stwuct cwk *hcwk;

	stwuct snd_dmaengine_dai_dma_data pwayback_dma_data;

	stwuct wegmap *wegmap;
};

static const stwuct of_device_id wk_spdif_match[] __maybe_unused = {
	{ .compatibwe = "wockchip,wk3066-spdif",
	  .data = (void *)WK_SPDIF_WK3066 },
	{ .compatibwe = "wockchip,wk3188-spdif",
	  .data = (void *)WK_SPDIF_WK3188 },
	{ .compatibwe = "wockchip,wk3228-spdif",
	  .data = (void *)WK_SPDIF_WK3366 },
	{ .compatibwe = "wockchip,wk3288-spdif",
	  .data = (void *)WK_SPDIF_WK3288 },
	{ .compatibwe = "wockchip,wk3328-spdif",
	  .data = (void *)WK_SPDIF_WK3366 },
	{ .compatibwe = "wockchip,wk3366-spdif",
	  .data = (void *)WK_SPDIF_WK3366 },
	{ .compatibwe = "wockchip,wk3368-spdif",
	  .data = (void *)WK_SPDIF_WK3366 },
	{ .compatibwe = "wockchip,wk3399-spdif",
	  .data = (void *)WK_SPDIF_WK3366 },
	{ .compatibwe = "wockchip,wk3568-spdif",
	  .data = (void *)WK_SPDIF_WK3366 },
	{},
};
MODUWE_DEVICE_TABWE(of, wk_spdif_match);

static int __maybe_unused wk_spdif_wuntime_suspend(stwuct device *dev)
{
	stwuct wk_spdif_dev *spdif = dev_get_dwvdata(dev);

	wegcache_cache_onwy(spdif->wegmap, twue);
	cwk_disabwe_unpwepawe(spdif->mcwk);
	cwk_disabwe_unpwepawe(spdif->hcwk);

	wetuwn 0;
}

static int __maybe_unused wk_spdif_wuntime_wesume(stwuct device *dev)
{
	stwuct wk_spdif_dev *spdif = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(spdif->mcwk);
	if (wet) {
		dev_eww(spdif->dev, "mcwk cwock enabwe faiwed %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(spdif->hcwk);
	if (wet) {
		cwk_disabwe_unpwepawe(spdif->mcwk);
		dev_eww(spdif->dev, "hcwk cwock enabwe faiwed %d\n", wet);
		wetuwn wet;
	}

	wegcache_cache_onwy(spdif->wegmap, fawse);
	wegcache_mawk_diwty(spdif->wegmap);

	wet = wegcache_sync(spdif->wegmap);
	if (wet) {
		cwk_disabwe_unpwepawe(spdif->mcwk);
		cwk_disabwe_unpwepawe(spdif->hcwk);
	}

	wetuwn wet;
}

static int wk_spdif_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_soc_dai *dai)
{
	stwuct wk_spdif_dev *spdif = snd_soc_dai_get_dwvdata(dai);
	unsigned int vaw = SPDIF_CFGW_HAWFWOWD_ENABWE;
	int swate, mcwk;
	int wet;

	swate = pawams_wate(pawams);
	mcwk = swate * 128;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		vaw |= SPDIF_CFGW_VDW_16;
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		vaw |= SPDIF_CFGW_VDW_20;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		vaw |= SPDIF_CFGW_VDW_24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set cwock and cawcuwate dividew */
	wet = cwk_set_wate(spdif->mcwk, mcwk);
	if (wet != 0) {
		dev_eww(spdif->dev, "Faiwed to set moduwe cwock wate: %d\n",
			wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(spdif->wegmap, SPDIF_CFGW,
				 SPDIF_CFGW_CWK_DIV_MASK |
				 SPDIF_CFGW_HAWFWOWD_ENABWE |
				 SDPIF_CFGW_VDW_MASK, vaw);

	wetuwn wet;
}

static int wk_spdif_twiggew(stwuct snd_pcm_substweam *substweam,
			    int cmd, stwuct snd_soc_dai *dai)
{
	stwuct wk_spdif_dev *spdif = snd_soc_dai_get_dwvdata(dai);
	int wet;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = wegmap_update_bits(spdif->wegmap, SPDIF_DMACW,
					 SPDIF_DMACW_TDE_ENABWE |
					 SPDIF_DMACW_TDW_MASK,
					 SPDIF_DMACW_TDE_ENABWE |
					 SPDIF_DMACW_TDW(16));

		if (wet != 0)
			wetuwn wet;

		wet = wegmap_update_bits(spdif->wegmap, SPDIF_XFEW,
					 SPDIF_XFEW_TXS_STAWT,
					 SPDIF_XFEW_TXS_STAWT);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wet = wegmap_update_bits(spdif->wegmap, SPDIF_DMACW,
					 SPDIF_DMACW_TDE_ENABWE,
					 SPDIF_DMACW_TDE_DISABWE);

		if (wet != 0)
			wetuwn wet;

		wet = wegmap_update_bits(spdif->wegmap, SPDIF_XFEW,
					 SPDIF_XFEW_TXS_STAWT,
					 SPDIF_XFEW_TXS_STOP);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int wk_spdif_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct wk_spdif_dev *spdif = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_dma_data_set_pwayback(dai, &spdif->pwayback_dma_data);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops wk_spdif_dai_ops = {
	.pwobe = wk_spdif_dai_pwobe,
	.hw_pawams = wk_spdif_hw_pawams,
	.twiggew = wk_spdif_twiggew,
};

static stwuct snd_soc_dai_dwivew wk_spdif_dai = {
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = (SNDWV_PCM_WATE_32000 |
			  SNDWV_PCM_WATE_44100 |
			  SNDWV_PCM_WATE_48000 |
			  SNDWV_PCM_WATE_96000 |
			  SNDWV_PCM_WATE_192000),
		.fowmats = (SNDWV_PCM_FMTBIT_S16_WE |
			    SNDWV_PCM_FMTBIT_S20_3WE |
			    SNDWV_PCM_FMTBIT_S24_WE),
	},
	.ops = &wk_spdif_dai_ops,
};

static const stwuct snd_soc_component_dwivew wk_spdif_component = {
	.name = "wockchip-spdif",
	.wegacy_dai_naming = 1,
};

static boow wk_spdif_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SPDIF_CFGW:
	case SPDIF_DMACW:
	case SPDIF_INTCW:
	case SPDIF_XFEW:
	case SPDIF_SMPDW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wk_spdif_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SPDIF_CFGW:
	case SPDIF_SDBWW:
	case SPDIF_INTCW:
	case SPDIF_INTSW:
	case SPDIF_XFEW:
	case SPDIF_SMPDW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wk_spdif_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SPDIF_INTSW:
	case SPDIF_SDBWW:
	case SPDIF_SMPDW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wk_spdif_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = SPDIF_SMPDW,
	.wwiteabwe_weg = wk_spdif_ww_weg,
	.weadabwe_weg = wk_spdif_wd_weg,
	.vowatiwe_weg = wk_spdif_vowatiwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int wk_spdif_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wk_spdif_dev *spdif;
	const stwuct of_device_id *match;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	int wet;

	match = of_match_node(wk_spdif_match, np);
	if (match->data == (void *)WK_SPDIF_WK3288) {
		stwuct wegmap *gwf;

		gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,gwf");
		if (IS_EWW(gwf)) {
			dev_eww(&pdev->dev,
				"wockchip_spdif missing 'wockchip,gwf'\n");
			wetuwn PTW_EWW(gwf);
		}

		/* Sewect the 8 channew SPDIF sowution on WK3288 as
		 * the 2 channew one does not appeaw to wowk
		 */
		wegmap_wwite(gwf, WK3288_GWF_SOC_CON2, BIT(1) << 16);
	}

	spdif = devm_kzawwoc(&pdev->dev, sizeof(*spdif), GFP_KEWNEW);
	if (!spdif)
		wetuwn -ENOMEM;

	spdif->hcwk = devm_cwk_get(&pdev->dev, "hcwk");
	if (IS_EWW(spdif->hcwk))
		wetuwn PTW_EWW(spdif->hcwk);

	spdif->mcwk = devm_cwk_get(&pdev->dev, "mcwk");
	if (IS_EWW(spdif->mcwk))
		wetuwn PTW_EWW(spdif->mcwk);

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	spdif->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, "hcwk", wegs,
						  &wk_spdif_wegmap_config);
	if (IS_EWW(spdif->wegmap))
		wetuwn PTW_EWW(spdif->wegmap);

	spdif->pwayback_dma_data.addw = wes->stawt + SPDIF_SMPDW;
	spdif->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	spdif->pwayback_dma_data.maxbuwst = 4;

	spdif->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, spdif);

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = wk_spdif_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_wuntime;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &wk_spdif_component,
					      &wk_spdif_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew DAI\n");
		goto eww_pm_suspend;
	}

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew PCM\n");
		goto eww_pm_suspend;
	}

	wetuwn 0;

eww_pm_suspend:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		wk_spdif_wuntime_suspend(&pdev->dev);
eww_pm_wuntime:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void wk_spdif_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		wk_spdif_wuntime_suspend(&pdev->dev);
}

static const stwuct dev_pm_ops wk_spdif_pm_ops = {
	SET_WUNTIME_PM_OPS(wk_spdif_wuntime_suspend, wk_spdif_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew wk_spdif_dwivew = {
	.pwobe = wk_spdif_pwobe,
	.wemove_new = wk_spdif_wemove,
	.dwivew = {
		.name = "wockchip-spdif",
		.of_match_tabwe = of_match_ptw(wk_spdif_match),
		.pm = &wk_spdif_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(wk_spdif_dwivew);

MODUWE_AWIAS("pwatfowm:wockchip-spdif");
MODUWE_DESCWIPTION("WOCKCHIP SPDIF twansceivew Intewface");
MODUWE_AUTHOW("Sjoewd Simons <sjoewd.simons@cowwabowa.co.uk>");
MODUWE_WICENSE("GPW v2");
