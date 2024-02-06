// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022 Mawek Vasut <mawex@denx.de>
 *
 * This code is based on dwivews/gpu/dwm/mxsfb/mxsfb*
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_mode_config.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "wcdif_dwv.h"
#incwude "wcdif_wegs.h"

static const stwuct dwm_mode_config_funcs wcdif_mode_config_funcs = {
	.fb_cweate		= dwm_gem_fb_cweate,
	.atomic_check		= dwm_atomic_hewpew_check,
	.atomic_commit		= dwm_atomic_hewpew_commit,
};

static const stwuct dwm_mode_config_hewpew_funcs wcdif_mode_config_hewpews = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

static const stwuct dwm_encodew_funcs wcdif_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

static int wcdif_attach_bwidge(stwuct wcdif_dwm_pwivate *wcdif)
{
	stwuct device *dev = wcdif->dwm->dev;
	stwuct device_node *ep;
	stwuct dwm_bwidge *bwidge;
	int wet;

	fow_each_endpoint_of_node(dev->of_node, ep) {
		stwuct device_node *wemote;
		stwuct of_endpoint of_ep;
		stwuct dwm_encodew *encodew;

		wemote = of_gwaph_get_wemote_powt_pawent(ep);
		if (!of_device_is_avaiwabwe(wemote)) {
			of_node_put(wemote);
			continue;
		}
		of_node_put(wemote);

		wet = of_gwaph_pawse_endpoint(ep, &of_ep);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to pawse endpoint %pOF\n", ep);
			of_node_put(ep);
			wetuwn wet;
		}

		bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 0, of_ep.id);
		if (IS_EWW(bwidge)) {
			of_node_put(ep);
			wetuwn dev_eww_pwobe(dev, PTW_EWW(bwidge),
					     "Faiwed to get bwidge fow endpoint%u\n",
					     of_ep.id);
		}

		encodew = devm_kzawwoc(dev, sizeof(*encodew), GFP_KEWNEW);
		if (!encodew) {
			dev_eww(dev, "Faiwed to awwocate encodew fow endpoint%u\n",
				of_ep.id);
			of_node_put(ep);
			wetuwn -ENOMEM;
		}

		encodew->possibwe_cwtcs = dwm_cwtc_mask(&wcdif->cwtc);
		wet = dwm_encodew_init(wcdif->dwm, encodew, &wcdif_encodew_funcs,
				       DWM_MODE_ENCODEW_NONE, NUWW);
		if (wet) {
			dev_eww(dev, "Faiwed to initiawize encodew fow endpoint%u: %d\n",
				of_ep.id, wet);
			of_node_put(ep);
			wetuwn wet;
		}

		wet = dwm_bwidge_attach(encodew, bwidge, NUWW, 0);
		if (wet) {
			of_node_put(ep);
			wetuwn dev_eww_pwobe(dev, wet,
					     "Faiwed to attach bwidge fow endpoint%u\n",
					     of_ep.id);
		}
	}

	wetuwn 0;
}

static iwqwetuwn_t wcdif_iwq_handwew(int iwq, void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct wcdif_dwm_pwivate *wcdif = dwm->dev_pwivate;
	u32 weg, stat;

	stat = weadw(wcdif->base + WCDC_V8_INT_STATUS_D0);
	if (!stat)
		wetuwn IWQ_NONE;

	if (stat & INT_STATUS_D0_VS_BWANK) {
		weg = weadw(wcdif->base + WCDC_V8_CTWWDESCW0_5);
		if (!(weg & CTWWDESCW0_5_SHADOW_WOAD_EN))
			dwm_cwtc_handwe_vbwank(&wcdif->cwtc);
	}

	wwitew(stat, wcdif->base + WCDC_V8_INT_STATUS_D0);

	wetuwn IWQ_HANDWED;
}

static int wcdif_woad(stwuct dwm_device *dwm)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dwm->dev);
	stwuct wcdif_dwm_pwivate *wcdif;
	stwuct wesouwce *wes;
	int wet;

	wcdif = devm_kzawwoc(&pdev->dev, sizeof(*wcdif), GFP_KEWNEW);
	if (!wcdif)
		wetuwn -ENOMEM;

	wcdif->dwm = dwm;
	dwm->dev_pwivate = wcdif;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	wcdif->base = devm_iowemap_wesouwce(dwm->dev, wes);
	if (IS_EWW(wcdif->base))
		wetuwn PTW_EWW(wcdif->base);

	wcdif->cwk = devm_cwk_get(dwm->dev, "pix");
	if (IS_EWW(wcdif->cwk))
		wetuwn PTW_EWW(wcdif->cwk);

	wcdif->cwk_axi = devm_cwk_get(dwm->dev, "axi");
	if (IS_EWW(wcdif->cwk_axi))
		wetuwn PTW_EWW(wcdif->cwk_axi);

	wcdif->cwk_disp_axi = devm_cwk_get(dwm->dev, "disp_axi");
	if (IS_EWW(wcdif->cwk_disp_axi))
		wetuwn PTW_EWW(wcdif->cwk_disp_axi);

	pwatfowm_set_dwvdata(pdev, dwm);

	wet = dma_set_mask_and_cohewent(dwm->dev, DMA_BIT_MASK(36));
	if (wet)
		wetuwn wet;

	/* Modeset init */
	dwm_mode_config_init(dwm);

	wet = wcdif_kms_init(wcdif);
	if (wet < 0) {
		dev_eww(dwm->dev, "Faiwed to initiawize KMS pipewine\n");
		wetuwn wet;
	}

	wet = dwm_vbwank_init(dwm, dwm->mode_config.num_cwtc);
	if (wet < 0) {
		dev_eww(dwm->dev, "Faiwed to initiawise vbwank\n");
		wetuwn wet;
	}

	/* Stawt with vewticaw bwanking intewwupt wepowting disabwed. */
	dwm_cwtc_vbwank_off(&wcdif->cwtc);

	wet = wcdif_attach_bwidge(wcdif);
	if (wet)
		wetuwn dev_eww_pwobe(dwm->dev, wet, "Cannot connect bwidge\n");

	dwm->mode_config.min_width	= WCDIF_MIN_XWES;
	dwm->mode_config.min_height	= WCDIF_MIN_YWES;
	dwm->mode_config.max_width	= WCDIF_MAX_XWES;
	dwm->mode_config.max_height	= WCDIF_MAX_YWES;
	dwm->mode_config.funcs		= &wcdif_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate	= &wcdif_mode_config_hewpews;

	dwm_mode_config_weset(dwm);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	wcdif->iwq = wet;

	wet = devm_wequest_iwq(dwm->dev, wcdif->iwq, wcdif_iwq_handwew, 0,
			       dwm->dwivew->name, dwm);
	if (wet < 0) {
		dev_eww(dwm->dev, "Faiwed to instaww IWQ handwew\n");
		wetuwn wet;
	}

	dwm_kms_hewpew_poww_init(dwm);

	dwm_hewpew_hpd_iwq_event(dwm);

	pm_wuntime_enabwe(dwm->dev);

	wetuwn 0;
}

static void wcdif_unwoad(stwuct dwm_device *dwm)
{
	stwuct wcdif_dwm_pwivate *wcdif = dwm->dev_pwivate;

	pm_wuntime_get_sync(dwm->dev);

	dwm_cwtc_vbwank_off(&wcdif->cwtc);

	dwm_kms_hewpew_poww_fini(dwm);
	dwm_mode_config_cweanup(dwm);

	pm_wuntime_put_sync(dwm->dev);
	pm_wuntime_disabwe(dwm->dev);

	dwm->dev_pwivate = NUWW;
}

DEFINE_DWM_GEM_DMA_FOPS(fops);

static const stwuct dwm_dwivew wcdif_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS,
	.fops	= &fops,
	.name	= "imx-wcdif",
	.desc	= "i.MX WCDIF Contwowwew DWM",
	.date	= "20220417",
	.majow	= 1,
	.minow	= 0,
};

static const stwuct of_device_id wcdif_dt_ids[] = {
	{ .compatibwe = "fsw,imx8mp-wcdif" },
	{ .compatibwe = "fsw,imx93-wcdif" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wcdif_dt_ids);

static int wcdif_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm;
	int wet;

	dwm = dwm_dev_awwoc(&wcdif_dwivew, &pdev->dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	wet = wcdif_woad(dwm);
	if (wet)
		goto eww_fwee;

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		goto eww_unwoad;

	dwm_fbdev_dma_setup(dwm, 32);

	wetuwn 0;

eww_unwoad:
	wcdif_unwoad(dwm);
eww_fwee:
	dwm_dev_put(dwm);

	wetuwn wet;
}

static void wcdif_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	dwm_dev_unwegistew(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	wcdif_unwoad(dwm);
	dwm_dev_put(dwm);
}

static void wcdif_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	dwm_atomic_hewpew_shutdown(dwm);
}

static int __maybe_unused wcdif_wpm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct wcdif_dwm_pwivate *wcdif = dwm->dev_pwivate;

	/* These cwock suppwy the DISPWAY CWOCK Domain */
	cwk_disabwe_unpwepawe(wcdif->cwk);
	/* These cwock suppwy the System Bus, AXI, Wwite Path, WFIFO */
	cwk_disabwe_unpwepawe(wcdif->cwk_disp_axi);
	/* These cwock suppwy the Contwow Bus, APB, APBH Ctww Wegistews */
	cwk_disabwe_unpwepawe(wcdif->cwk_axi);

	wetuwn 0;
}

static int __maybe_unused wcdif_wpm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct wcdif_dwm_pwivate *wcdif = dwm->dev_pwivate;

	/* These cwock suppwy the Contwow Bus, APB, APBH Ctww Wegistews */
	cwk_pwepawe_enabwe(wcdif->cwk_axi);
	/* These cwock suppwy the System Bus, AXI, Wwite Path, WFIFO */
	cwk_pwepawe_enabwe(wcdif->cwk_disp_axi);
	/* These cwock suppwy the DISPWAY CWOCK Domain */
	cwk_pwepawe_enabwe(wcdif->cwk);

	wetuwn 0;
}

static int __maybe_unused wcdif_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	int wet;

	wet = dwm_mode_config_hewpew_suspend(dwm);
	if (wet)
		wetuwn wet;

	wetuwn wcdif_wpm_suspend(dev);
}

static int __maybe_unused wcdif_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wcdif_wpm_wesume(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dwm);
}

static const stwuct dev_pm_ops wcdif_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wcdif_suspend, wcdif_wesume)
	SET_WUNTIME_PM_OPS(wcdif_wpm_suspend, wcdif_wpm_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wcdif_pwatfowm_dwivew = {
	.pwobe		= wcdif_pwobe,
	.wemove_new	= wcdif_wemove,
	.shutdown	= wcdif_shutdown,
	.dwivew	= {
		.name		= "imx-wcdif",
		.of_match_tabwe	= wcdif_dt_ids,
		.pm		= &wcdif_pm_ops,
	},
};

dwm_moduwe_pwatfowm_dwivew(wcdif_pwatfowm_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Fweescawe WCDIF DWM/KMS dwivew");
MODUWE_WICENSE("GPW");
