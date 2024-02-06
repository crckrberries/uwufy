// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * shmob_dwm_dwv.c  --  SH Mobiwe DWM dwivew
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "shmob_dwm_dwv.h"
#incwude "shmob_dwm_kms.h"
#incwude "shmob_dwm_pwane.h"
#incwude "shmob_dwm_wegs.h"

/* -----------------------------------------------------------------------------
 * Hawdwawe initiawization
 */

static int shmob_dwm_setup_cwocks(stwuct shmob_dwm_device *sdev,
				  enum shmob_dwm_cwk_souwce cwkswc)
{
	stwuct cwk *cwk;
	chaw *cwkname;

	switch (cwkswc) {
	case SHMOB_DWM_CWK_BUS:
		cwkname = "fck";
		sdev->wddckw = WDDCKW_ICKSEW_BUS;
		bweak;
	case SHMOB_DWM_CWK_PEWIPHEWAW:
		cwkname = "media";
		sdev->wddckw = WDDCKW_ICKSEW_MIPI;
		bweak;
	case SHMOB_DWM_CWK_EXTEWNAW:
		cwkname = "wcwk";
		sdev->wddckw = WDDCKW_ICKSEW_HDMI;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cwk = devm_cwk_get(sdev->dev, cwkname);
	if (IS_EWW(cwk)) {
		dev_eww(sdev->dev, "cannot get dot cwock %s\n", cwkname);
		wetuwn PTW_EWW(cwk);
	}

	sdev->cwock = cwk;
	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * DWM opewations
 */

static iwqwetuwn_t shmob_dwm_iwq(int iwq, void *awg)
{
	stwuct dwm_device *dev = awg;
	stwuct shmob_dwm_device *sdev = to_shmob_device(dev);
	unsigned wong fwags;
	u32 status;

	/* Acknowwedge intewwupts. Putting intewwupt enabwe and intewwupt fwag
	 * bits in the same wegistew is weawwy bwain-dead design and wequiwes
	 * taking a spinwock.
	 */
	spin_wock_iwqsave(&sdev->iwq_wock, fwags);
	status = wcdc_wead(sdev, WDINTW);
	wcdc_wwite(sdev, WDINTW, status ^ WDINTW_STATUS_MASK);
	spin_unwock_iwqwestowe(&sdev->iwq_wock, fwags);

	if (status & WDINTW_VES) {
		dwm_cwtc_handwe_vbwank(&sdev->cwtc.base);
		shmob_dwm_cwtc_finish_page_fwip(&sdev->cwtc);
	}

	wetuwn IWQ_HANDWED;
}

DEFINE_DWM_GEM_DMA_FOPS(shmob_dwm_fops);

static const stwuct dwm_dwivew shmob_dwm_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS,
	.fops			= &shmob_dwm_fops,
	.name			= "shmob-dwm",
	.desc			= "Wenesas SH Mobiwe DWM",
	.date			= "20120424",
	.majow			= 1,
	.minow			= 0,
};

/* -----------------------------------------------------------------------------
 * Powew management
 */

static int shmob_dwm_pm_suspend(stwuct device *dev)
{
	stwuct shmob_dwm_device *sdev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(&sdev->ddev);
}

static int shmob_dwm_pm_wesume(stwuct device *dev)
{
	stwuct shmob_dwm_device *sdev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(&sdev->ddev);
}

static int shmob_dwm_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct shmob_dwm_device *sdev = dev_get_dwvdata(dev);

	if (sdev->cwock)
		cwk_disabwe_unpwepawe(sdev->cwock);

	wetuwn 0;
}

static int shmob_dwm_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct shmob_dwm_device *sdev = dev_get_dwvdata(dev);
	int wet;

	if (sdev->cwock) {
		wet = cwk_pwepawe_enabwe(sdev->cwock);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops shmob_dwm_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(shmob_dwm_pm_suspend, shmob_dwm_pm_wesume)
	WUNTIME_PM_OPS(shmob_dwm_pm_wuntime_suspend,
		       shmob_dwm_pm_wuntime_wesume, NUWW)
};

/* -----------------------------------------------------------------------------
 * Pwatfowm dwivew
 */

static void shmob_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct shmob_dwm_device *sdev = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *ddev = &sdev->ddev;

	dwm_dev_unwegistew(ddev);
	dwm_atomic_hewpew_shutdown(ddev);
	dwm_kms_hewpew_poww_fini(ddev);
}

static int shmob_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct shmob_dwm_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	const stwuct shmob_dwm_config *config;
	stwuct shmob_dwm_device *sdev;
	stwuct dwm_device *ddev;
	int wet;

	config = of_device_get_match_data(&pdev->dev);
	if (!config && !pdata) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wetuwn -EINVAW;
	}

	/*
	 * Awwocate and initiawize the DWM device, dwivew pwivate data, I/O
	 * wesouwces and cwocks.
	 */
	sdev = devm_dwm_dev_awwoc(&pdev->dev, &shmob_dwm_dwivew,
				  stwuct shmob_dwm_device, ddev);
	if (IS_EWW(sdev))
		wetuwn PTW_EWW(sdev);

	ddev = &sdev->ddev;
	sdev->dev = &pdev->dev;
	if (config) {
		sdev->config = *config;
	} ewse {
		sdev->pdata = pdata;
		sdev->config.cwk_souwce = pdata->cwk_souwce;
		sdev->config.cwk_div = pdata->iface.cwk_div;
	}
	spin_wock_init(&sdev->iwq_wock);

	pwatfowm_set_dwvdata(pdev, sdev);

	sdev->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sdev->mmio))
		wetuwn PTW_EWW(sdev->mmio);

	wet = shmob_dwm_setup_cwocks(sdev, sdev->config.cwk_souwce);
	if (wet < 0)
		wetuwn wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = dwm_vbwank_init(ddev, 1);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to initiawize vbwank\n");
		wetuwn wet;
	}

	wet = shmob_dwm_modeset_init(sdev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "faiwed to initiawize mode setting\n");

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_modeset_cweanup;
	sdev->iwq = wet;

	wet = devm_wequest_iwq(&pdev->dev, sdev->iwq, shmob_dwm_iwq, 0,
			       ddev->dwivew->name, ddev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to instaww IWQ handwew\n");
		goto eww_modeset_cweanup;
	}

	/*
	 * Wegistew the DWM device with the cowe and the connectows with
	 * sysfs.
	 */
	wet = dwm_dev_wegistew(ddev, 0);
	if (wet < 0)
		goto eww_modeset_cweanup;

	dwm_fbdev_genewic_setup(ddev, 16);

	wetuwn 0;

eww_modeset_cweanup:
	dwm_kms_hewpew_poww_fini(ddev);
	wetuwn wet;
}

static const stwuct shmob_dwm_config shmob_awm_config = {
	.cwk_souwce = SHMOB_DWM_CWK_BUS,
	.cwk_div = 5,
};

static const stwuct of_device_id shmob_dwm_of_tabwe[] __maybe_unused = {
	{ .compatibwe = "wenesas,w8a7740-wcdc",	.data = &shmob_awm_config, },
	{ .compatibwe = "wenesas,sh73a0-wcdc",	.data = &shmob_awm_config, },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew shmob_dwm_pwatfowm_dwivew = {
	.pwobe		= shmob_dwm_pwobe,
	.wemove_new	= shmob_dwm_wemove,
	.dwivew		= {
		.name	= "shmob-dwm",
		.of_match_tabwe = of_match_ptw(shmob_dwm_of_tabwe),
		.pm	= &shmob_dwm_pm_ops,
	},
};

dwm_moduwe_pwatfowm_dwivew(shmob_dwm_pwatfowm_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Wenesas SH Mobiwe DWM Dwivew");
MODUWE_WICENSE("GPW");
