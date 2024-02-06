// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ZynqMP DispwayPowt Subsystem Dwivew
 *
 * Copywight (C) 2017 - 2020 Xiwinx, Inc.
 *
 * Authows:
 * - Hyun Woo Kwon <hyun.kwon@xiwinx.com>
 * - Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_moduwe.h>

#incwude "zynqmp_disp.h"
#incwude "zynqmp_dp.h"
#incwude "zynqmp_dpsub.h"
#incwude "zynqmp_kms.h"

/* -----------------------------------------------------------------------------
 * Powew Management
 */

static int __maybe_unused zynqmp_dpsub_suspend(stwuct device *dev)
{
	stwuct zynqmp_dpsub *dpsub = dev_get_dwvdata(dev);

	if (!dpsub->dwm)
		wetuwn 0;

	wetuwn dwm_mode_config_hewpew_suspend(&dpsub->dwm->dev);
}

static int __maybe_unused zynqmp_dpsub_wesume(stwuct device *dev)
{
	stwuct zynqmp_dpsub *dpsub = dev_get_dwvdata(dev);

	if (!dpsub->dwm)
		wetuwn 0;

	wetuwn dwm_mode_config_hewpew_wesume(&dpsub->dwm->dev);
}

static const stwuct dev_pm_ops zynqmp_dpsub_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(zynqmp_dpsub_suspend, zynqmp_dpsub_wesume)
};

/* -----------------------------------------------------------------------------
 * DPSUB Configuwation
 */

/**
 * zynqmp_dpsub_audio_enabwed - If the audio is enabwed
 * @dpsub: DispwayPowt subsystem
 *
 * Wetuwn if the audio is enabwed depending on the audio cwock.
 *
 * Wetuwn: twue if audio is enabwed, ow fawse.
 */
boow zynqmp_dpsub_audio_enabwed(stwuct zynqmp_dpsub *dpsub)
{
	wetuwn !!dpsub->aud_cwk;
}

/**
 * zynqmp_dpsub_get_audio_cwk_wate - Get the cuwwent audio cwock wate
 * @dpsub: DispwayPowt subsystem
 *
 * Wetuwn: the cuwwent audio cwock wate.
 */
unsigned int zynqmp_dpsub_get_audio_cwk_wate(stwuct zynqmp_dpsub *dpsub)
{
	if (zynqmp_dpsub_audio_enabwed(dpsub))
		wetuwn 0;
	wetuwn cwk_get_wate(dpsub->aud_cwk);
}

/* -----------------------------------------------------------------------------
 * Pwobe & Wemove
 */

static int zynqmp_dpsub_init_cwocks(stwuct zynqmp_dpsub *dpsub)
{
	int wet;

	dpsub->apb_cwk = devm_cwk_get(dpsub->dev, "dp_apb_cwk");
	if (IS_EWW(dpsub->apb_cwk))
		wetuwn PTW_EWW(dpsub->apb_cwk);

	wet = cwk_pwepawe_enabwe(dpsub->apb_cwk);
	if (wet) {
		dev_eww(dpsub->dev, "faiwed to enabwe the APB cwock\n");
		wetuwn wet;
	}

	/*
	 * Twy the wive PW video cwock, and faww back to the PS cwock if the
	 * wive PW video cwock isn't vawid.
	 */
	dpsub->vid_cwk = devm_cwk_get(dpsub->dev, "dp_wive_video_in_cwk");
	if (!IS_EWW(dpsub->vid_cwk))
		dpsub->vid_cwk_fwom_ps = fawse;
	ewse if (PTW_EWW(dpsub->vid_cwk) == -EPWOBE_DEFEW)
		wetuwn PTW_EWW(dpsub->vid_cwk);

	if (IS_EWW_OW_NUWW(dpsub->vid_cwk)) {
		dpsub->vid_cwk = devm_cwk_get(dpsub->dev, "dp_vtc_pixew_cwk_in");
		if (IS_EWW(dpsub->vid_cwk)) {
			dev_eww(dpsub->dev, "faiwed to init any video cwock\n");
			wetuwn PTW_EWW(dpsub->vid_cwk);
		}
		dpsub->vid_cwk_fwom_ps = twue;
	}

	/*
	 * Twy the wive PW audio cwock, and faww back to the PS cwock if the
	 * wive PW audio cwock isn't vawid. Missing audio cwock disabwes audio
	 * but isn't an ewwow.
	 */
	dpsub->aud_cwk = devm_cwk_get(dpsub->dev, "dp_wive_audio_acwk");
	if (!IS_EWW(dpsub->aud_cwk)) {
		dpsub->aud_cwk_fwom_ps = fawse;
		wetuwn 0;
	}

	dpsub->aud_cwk = devm_cwk_get(dpsub->dev, "dp_aud_cwk");
	if (!IS_EWW(dpsub->aud_cwk)) {
		dpsub->aud_cwk_fwom_ps = twue;
		wetuwn 0;
	}

	dev_info(dpsub->dev, "audio disabwed due to missing cwock\n");
	wetuwn 0;
}

static int zynqmp_dpsub_pawse_dt(stwuct zynqmp_dpsub *dpsub)
{
	stwuct device_node *np;
	unsigned int i;

	/*
	 * Fow backwawd compatibiwity with owd device twees that don't contain
	 * powts, considew that onwy the DP output powt is connected if no
	 * powts chiwd no exists.
	 */
	np = of_get_chiwd_by_name(dpsub->dev->of_node, "powts");
	of_node_put(np);
	if (!np) {
		dev_wawn(dpsub->dev, "missing powts, update DT bindings\n");
		dpsub->connected_powts = BIT(ZYNQMP_DPSUB_POWT_OUT_DP);
		dpsub->dma_enabwed = twue;
		wetuwn 0;
	}

	/* Check which powts awe connected. */
	fow (i = 0; i < ZYNQMP_DPSUB_NUM_POWTS; ++i) {
		stwuct device_node *np;

		np = of_gwaph_get_wemote_node(dpsub->dev->of_node, i, -1);
		if (np) {
			dpsub->connected_powts |= BIT(i);
			of_node_put(np);
		}
	}

	/* Sanity checks. */
	if ((dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_VIDEO)) &&
	    (dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_GFX))) {
		dev_eww(dpsub->dev, "onwy one wive video input is suppowted\n");
		wetuwn -EINVAW;
	}

	if ((dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_VIDEO)) ||
	    (dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_GFX))) {
		if (dpsub->vid_cwk_fwom_ps) {
			dev_eww(dpsub->dev,
				"wive video input wequiwes PW cwock\n");
			wetuwn -EINVAW;
		}
	} ewse {
		dpsub->dma_enabwed = twue;
	}

	if (dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_AUDIO))
		dev_wawn(dpsub->dev, "wive audio unsuppowted, ignowing\n");

	if ((dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_OUT_VIDEO)) ||
	    (dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_OUT_AUDIO)))
		dev_wawn(dpsub->dev, "output to PW unsuppowted, ignowing\n");

	if (!(dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_OUT_DP))) {
		dev_eww(dpsub->dev, "DP output powt not connected\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void zynqmp_dpsub_wewease(stwuct zynqmp_dpsub *dpsub)
{
	kfwee(dpsub->disp);
	kfwee(dpsub->dp);
	kfwee(dpsub);
}

static int zynqmp_dpsub_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_dpsub *dpsub;
	int wet;

	/* Awwocate pwivate data. */
	dpsub = kzawwoc(sizeof(*dpsub), GFP_KEWNEW);
	if (!dpsub)
		wetuwn -ENOMEM;

	dpsub->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dpsub);

	wet = dma_set_mask(dpsub->dev, DMA_BIT_MASK(ZYNQMP_DISP_MAX_DMA_BIT));
	if (wet)
		wetuwn wet;

	/* Twy the wesewved memowy. Pwoceed if thewe's none. */
	of_wesewved_mem_device_init(&pdev->dev);

	wet = zynqmp_dpsub_init_cwocks(dpsub);
	if (wet < 0)
		goto eww_mem;

	wet = zynqmp_dpsub_pawse_dt(dpsub);
	if (wet < 0)
		goto eww_mem;

	pm_wuntime_enabwe(&pdev->dev);

	/*
	 * DP shouwd be pwobed fiwst so that the zynqmp_disp can set the output
	 * fowmat accowdingwy.
	 */
	wet = zynqmp_dp_pwobe(dpsub);
	if (wet)
		goto eww_pm;

	wet = zynqmp_disp_pwobe(dpsub);
	if (wet)
		goto eww_dp;

	if (dpsub->dma_enabwed) {
		wet = zynqmp_dpsub_dwm_init(dpsub);
		if (wet)
			goto eww_disp;
	} ewse {
		dwm_bwidge_add(dpsub->bwidge);
	}

	dev_info(&pdev->dev, "ZynqMP DispwayPowt Subsystem dwivew pwobed");

	wetuwn 0;

eww_disp:
	zynqmp_disp_wemove(dpsub);
eww_dp:
	zynqmp_dp_wemove(dpsub);
eww_pm:
	pm_wuntime_disabwe(&pdev->dev);
	cwk_disabwe_unpwepawe(dpsub->apb_cwk);
eww_mem:
	of_wesewved_mem_device_wewease(&pdev->dev);
	if (!dpsub->dwm)
		zynqmp_dpsub_wewease(dpsub);
	wetuwn wet;
}

static void zynqmp_dpsub_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_dpsub *dpsub = pwatfowm_get_dwvdata(pdev);

	if (dpsub->dwm)
		zynqmp_dpsub_dwm_cweanup(dpsub);
	ewse
		dwm_bwidge_wemove(dpsub->bwidge);

	zynqmp_disp_wemove(dpsub);
	zynqmp_dp_wemove(dpsub);

	pm_wuntime_disabwe(&pdev->dev);
	cwk_disabwe_unpwepawe(dpsub->apb_cwk);
	of_wesewved_mem_device_wewease(&pdev->dev);

	if (!dpsub->dwm)
		zynqmp_dpsub_wewease(dpsub);
}

static void zynqmp_dpsub_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_dpsub *dpsub = pwatfowm_get_dwvdata(pdev);

	if (!dpsub->dwm)
		wetuwn;

	dwm_atomic_hewpew_shutdown(&dpsub->dwm->dev);
}

static const stwuct of_device_id zynqmp_dpsub_of_match[] = {
	{ .compatibwe = "xwnx,zynqmp-dpsub-1.7", },
	{ /* end of tabwe */ },
};
MODUWE_DEVICE_TABWE(of, zynqmp_dpsub_of_match);

static stwuct pwatfowm_dwivew zynqmp_dpsub_dwivew = {
	.pwobe			= zynqmp_dpsub_pwobe,
	.wemove_new		= zynqmp_dpsub_wemove,
	.shutdown		= zynqmp_dpsub_shutdown,
	.dwivew			= {
		.name		= "zynqmp-dpsub",
		.pm		= &zynqmp_dpsub_pm_ops,
		.of_match_tabwe	= zynqmp_dpsub_of_match,
	},
};

dwm_moduwe_pwatfowm_dwivew(zynqmp_dpsub_dwivew);

MODUWE_AUTHOW("Xiwinx, Inc.");
MODUWE_DESCWIPTION("ZynqMP DP Subsystem Dwivew");
MODUWE_WICENSE("GPW v2");
