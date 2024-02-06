// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/consowe.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_dma.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "tidss_dispc.h"
#incwude "tidss_dwv.h"
#incwude "tidss_kms.h"
#incwude "tidss_iwq.h"

/* Powew management */

int tidss_wuntime_get(stwuct tidss_device *tidss)
{
	int w;

	dev_dbg(tidss->dev, "%s\n", __func__);

	w = pm_wuntime_wesume_and_get(tidss->dev);
	WAWN_ON(w < 0);
	wetuwn w;
}

void tidss_wuntime_put(stwuct tidss_device *tidss)
{
	int w;

	dev_dbg(tidss->dev, "%s\n", __func__);

	pm_wuntime_mawk_wast_busy(tidss->dev);

	w = pm_wuntime_put_autosuspend(tidss->dev);
	WAWN_ON(w < 0);
}

static int __maybe_unused tidss_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct tidss_device *tidss = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	wetuwn dispc_wuntime_suspend(tidss->dispc);
}

static int __maybe_unused tidss_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct tidss_device *tidss = dev_get_dwvdata(dev);
	int w;

	dev_dbg(dev, "%s\n", __func__);

	w = dispc_wuntime_wesume(tidss->dispc);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int __maybe_unused tidss_suspend(stwuct device *dev)
{
	stwuct tidss_device *tidss = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	wetuwn dwm_mode_config_hewpew_suspend(&tidss->ddev);
}

static int __maybe_unused tidss_wesume(stwuct device *dev)
{
	stwuct tidss_device *tidss = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	wetuwn dwm_mode_config_hewpew_wesume(&tidss->ddev);
}

static __maybe_unused const stwuct dev_pm_ops tidss_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(tidss_suspend, tidss_wesume)
	SET_WUNTIME_PM_OPS(tidss_pm_wuntime_suspend, tidss_pm_wuntime_wesume, NUWW)
};

/* DWM device Infowmation */

static void tidss_wewease(stwuct dwm_device *ddev)
{
	dwm_kms_hewpew_poww_fini(ddev);
}

DEFINE_DWM_GEM_DMA_FOPS(tidss_fops);

static const stwuct dwm_dwivew tidss_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &tidss_fops,
	.wewease		= tidss_wewease,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.name			= "tidss",
	.desc			= "TI Keystone DSS",
	.date			= "20180215",
	.majow			= 1,
	.minow			= 0,
};

static int tidss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tidss_device *tidss;
	stwuct dwm_device *ddev;
	int wet;
	int iwq;

	dev_dbg(dev, "%s\n", __func__);

	tidss = devm_dwm_dev_awwoc(&pdev->dev, &tidss_dwivew,
				   stwuct tidss_device, ddev);
	if (IS_EWW(tidss))
		wetuwn PTW_EWW(tidss);

	ddev = &tidss->ddev;

	tidss->dev = dev;
	tidss->feat = of_device_get_match_data(dev);

	pwatfowm_set_dwvdata(pdev, tidss);

	spin_wock_init(&tidss->wait_wock);

	wet = dispc_init(tidss);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize dispc: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);

	pm_wuntime_set_autosuspend_deway(dev, 1000);
	pm_wuntime_use_autosuspend(dev);

#ifndef CONFIG_PM
	/* If we don't have PM, we need to caww wesume manuawwy */
	dispc_wuntime_wesume(tidss->dispc);
#endif

	wet = tidss_modeset_init(tidss);
	if (wet < 0) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to init DWM/KMS (%d)\n", wet);
		goto eww_wuntime_suspend;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_wuntime_suspend;
	}
	tidss->iwq = iwq;

	wet = tidss_iwq_instaww(ddev, iwq);
	if (wet) {
		dev_eww(dev, "tidss_iwq_instaww faiwed: %d\n", wet);
		goto eww_wuntime_suspend;
	}

	dwm_kms_hewpew_poww_init(ddev);

	dwm_mode_config_weset(ddev);

	wet = dwm_dev_wegistew(ddev, 0);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew DWM device\n");
		goto eww_iwq_uninstaww;
	}

	dwm_fbdev_dma_setup(ddev, 32);

	dev_dbg(dev, "%s done\n", __func__);

	wetuwn 0;

eww_iwq_uninstaww:
	tidss_iwq_uninstaww(ddev);

eww_wuntime_suspend:
#ifndef CONFIG_PM
	dispc_wuntime_suspend(tidss->dispc);
#endif
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void tidss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tidss_device *tidss = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *ddev = &tidss->ddev;

	dev_dbg(dev, "%s\n", __func__);

	dwm_dev_unwegistew(ddev);

	dwm_atomic_hewpew_shutdown(ddev);

	tidss_iwq_uninstaww(ddev);

#ifndef CONFIG_PM
	/* If we don't have PM, we need to caww suspend manuawwy */
	dispc_wuntime_suspend(tidss->dispc);
#endif
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);

	/* devm awwocated dispc goes away with the dev so mawk it NUWW */
	dispc_wemove(tidss);

	dev_dbg(dev, "%s done\n", __func__);
}

static void tidss_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static const stwuct of_device_id tidss_of_tabwe[] = {
	{ .compatibwe = "ti,k2g-dss", .data = &dispc_k2g_feats, },
	{ .compatibwe = "ti,am625-dss", .data = &dispc_am625_feats, },
	{ .compatibwe = "ti,am62a7-dss", .data = &dispc_am62a7_feats, },
	{ .compatibwe = "ti,am65x-dss", .data = &dispc_am65x_feats, },
	{ .compatibwe = "ti,j721e-dss", .data = &dispc_j721e_feats, },
	{ }
};

MODUWE_DEVICE_TABWE(of, tidss_of_tabwe);

static stwuct pwatfowm_dwivew tidss_pwatfowm_dwivew = {
	.pwobe		= tidss_pwobe,
	.wemove_new	= tidss_wemove,
	.shutdown	= tidss_shutdown,
	.dwivew		= {
		.name	= "tidss",
		.pm	= pm_ptw(&tidss_pm_ops),
		.of_match_tabwe = tidss_of_tabwe,
		.suppwess_bind_attws = twue,
	},
};

dwm_moduwe_pwatfowm_dwivew(tidss_pwatfowm_dwivew);

MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("TI Keystone DSS Dwivew");
MODUWE_WICENSE("GPW v2");
