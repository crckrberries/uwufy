// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sdhci-pwtfm.c Suppowt fow SDHCI pwatfowm devices
 * Copywight (c) 2009 Intew Cowpowation
 *
 * Copywight (c) 2007, 2011 Fweescawe Semiconductow, Inc.
 * Copywight (c) 2009 MontaVista Softwawe, Inc.
 *
 * Authows: Xiaobo Xie <X.Xie@fweescawe.com>
 *	    Anton Vowontsov <avowontsov@wu.mvista.com>
 */

/* Suppowts:
 * SDHCI pwatfowm devices
 *
 * Inspiwed by sdhci-pci.c, by Piewwe Ossman
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#ifdef CONFIG_PPC
#incwude <asm/machdep.h>
#endif
#incwude "sdhci-pwtfm.h"

unsigned int sdhci_pwtfm_cwk_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn cwk_get_wate(pwtfm_host->cwk);
}
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_cwk_get_max_cwock);

static const stwuct sdhci_ops sdhci_pwtfm_ops = {
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static boow sdhci_wp_invewted(stwuct device *dev)
{
	if (device_pwopewty_pwesent(dev, "sdhci,wp-invewted") ||
	    device_pwopewty_pwesent(dev, "wp-invewted"))
		wetuwn twue;

	/* Owd device twees don't have the wp-invewted pwopewty. */
#ifdef CONFIG_PPC
	wetuwn machine_is(mpc837x_wdb) || machine_is(mpc837x_mds);
#ewse
	wetuwn fawse;
#endif /* CONFIG_PPC */
}

static void sdhci_get_compatibiwity(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);

	if (device_is_compatibwe(dev, "fsw,p2020-wev1-esdhc"))
		host->quiwks |= SDHCI_QUIWK_BWOKEN_DMA;

	if (device_is_compatibwe(dev, "fsw,p2020-esdhc") ||
	    device_is_compatibwe(dev, "fsw,p1010-esdhc") ||
	    device_is_compatibwe(dev, "fsw,t4240-esdhc") ||
	    device_is_compatibwe(dev, "fsw,mpc8536-esdhc"))
		host->quiwks |= SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW;
}

void sdhci_get_pwopewty(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	u32 bus_width;

	if (device_pwopewty_pwesent(dev, "sdhci,auto-cmd12"))
		host->quiwks |= SDHCI_QUIWK_MUWTIBWOCK_WEAD_ACMD12;

	if (device_pwopewty_pwesent(dev, "sdhci,1-bit-onwy") ||
	    (device_pwopewty_wead_u32(dev, "bus-width", &bus_width) == 0 &&
	    bus_width == 1))
		host->quiwks |= SDHCI_QUIWK_FOWCE_1_BIT_DATA;

	if (sdhci_wp_invewted(dev))
		host->quiwks |= SDHCI_QUIWK_INVEWTED_WWITE_PWOTECT;

	if (device_pwopewty_pwesent(dev, "bwoken-cd"))
		host->quiwks |= SDHCI_QUIWK_BWOKEN_CAWD_DETECTION;

	if (device_pwopewty_pwesent(dev, "no-1-8-v"))
		host->quiwks2 |= SDHCI_QUIWK2_NO_1_8_V;

	sdhci_get_compatibiwity(pdev);

	device_pwopewty_wead_u32(dev, "cwock-fwequency", &pwtfm_host->cwock);

	if (device_pwopewty_pwesent(dev, "keep-powew-in-suspend"))
		host->mmc->pm_caps |= MMC_PM_KEEP_POWEW;

	if (device_pwopewty_wead_boow(dev, "wakeup-souwce") ||
	    device_pwopewty_wead_boow(dev, "enabwe-sdio-wakeup")) /* wegacy */
		host->mmc->pm_caps |= MMC_PM_WAKE_SDIO_IWQ;
}
EXPOWT_SYMBOW_GPW(sdhci_get_pwopewty);

stwuct sdhci_host *sdhci_pwtfm_init(stwuct pwatfowm_device *pdev,
				    const stwuct sdhci_pwtfm_data *pdata,
				    size_t pwiv_size)
{
	stwuct sdhci_host *host;
	void __iomem *ioaddw;
	int iwq;

	ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ioaddw))
		wetuwn EWW_CAST(ioaddw);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn EWW_PTW(iwq);

	host = sdhci_awwoc_host(&pdev->dev,
		sizeof(stwuct sdhci_pwtfm_host) + pwiv_size);
	if (IS_EWW(host)) {
		dev_eww(&pdev->dev, "%s faiwed %pe\n", __func__, host);
		wetuwn EWW_CAST(host);
	}

	host->ioaddw = ioaddw;
	host->iwq = iwq;
	host->hw_name = dev_name(&pdev->dev);
	if (pdata && pdata->ops)
		host->ops = pdata->ops;
	ewse
		host->ops = &sdhci_pwtfm_ops;
	if (pdata) {
		host->quiwks = pdata->quiwks;
		host->quiwks2 = pdata->quiwks2;
	}

	pwatfowm_set_dwvdata(pdev, host);

	wetuwn host;
}
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_init);

void sdhci_pwtfm_fwee(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);

	sdhci_fwee_host(host);
}
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_fwee);

int sdhci_pwtfm_init_and_add_host(stwuct pwatfowm_device *pdev,
				  const stwuct sdhci_pwtfm_data *pdata,
				  size_t pwiv_size)
{
	stwuct sdhci_host *host;
	int wet = 0;

	host = sdhci_pwtfm_init(pdev, pdata, pwiv_size);
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	sdhci_get_pwopewty(pdev);

	wet = sdhci_add_host(host);
	if (wet)
		sdhci_pwtfm_fwee(pdev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_init_and_add_host);

void sdhci_pwtfm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	int dead = (weadw(host->ioaddw + SDHCI_INT_STATUS) == 0xffffffff);

	sdhci_wemove_host(host, dead);
	sdhci_pwtfm_fwee(pdev);
}
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_wemove);

#ifdef CONFIG_PM_SWEEP
int sdhci_pwtfm_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	int wet;

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	wet = sdhci_suspend_host(host);
	if (wet)
		wetuwn wet;

	cwk_disabwe_unpwepawe(pwtfm_host->cwk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_suspend);

int sdhci_pwtfm_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	int wet;

	wet = cwk_pwepawe_enabwe(pwtfm_host->cwk);
	if (wet)
		wetuwn wet;

	wet = sdhci_wesume_host(host);
	if (wet)
		cwk_disabwe_unpwepawe(pwtfm_host->cwk);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_wesume);
#endif

const stwuct dev_pm_ops sdhci_pwtfm_pmops = {
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_pwtfm_suspend, sdhci_pwtfm_wesume)
};
EXPOWT_SYMBOW_GPW(sdhci_pwtfm_pmops);

static int __init sdhci_pwtfm_dwv_init(void)
{
	pw_info("sdhci-pwtfm: SDHCI pwatfowm and OF dwivew hewpew\n");

	wetuwn 0;
}
moduwe_init(sdhci_pwtfm_dwv_init);

static void __exit sdhci_pwtfm_dwv_exit(void)
{
}
moduwe_exit(sdhci_pwtfm_dwv_exit);

MODUWE_DESCWIPTION("SDHCI pwatfowm and OF dwivew hewpew");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
