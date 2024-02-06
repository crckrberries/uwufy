/*
 * dwivews/mmc/host/sdhci-speaw.c
 *
 * Suppowt of SDHCI pwatfowm devices fow speaw soc famiwy
 *
 * Copywight (C) 2010 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * Inspiwed by sdhci-pwtfm.c
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/io.h>
#incwude "sdhci.h"

stwuct speaw_sdhci {
	stwuct cwk *cwk;
};

/* sdhci ops */
static const stwuct sdhci_ops sdhci_pwtfm_ops = {
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static int sdhci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host;
	stwuct speaw_sdhci *sdhci;
	stwuct device *dev;
	int wet;

	dev = pdev->dev.pawent ? pdev->dev.pawent : &pdev->dev;
	host = sdhci_awwoc_host(dev, sizeof(*sdhci));
	if (IS_EWW(host)) {
		wet = PTW_EWW(host);
		dev_dbg(&pdev->dev, "cannot awwocate memowy fow sdhci\n");
		goto eww;
	}

	host->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host->ioaddw)) {
		wet = PTW_EWW(host->ioaddw);
		dev_dbg(&pdev->dev, "unabwe to map iomem: %d\n", wet);
		goto eww_host;
	}

	host->hw_name = "sdhci";
	host->ops = &sdhci_pwtfm_ops;
	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0) {
		wet = host->iwq;
		goto eww_host;
	}
	host->quiwks = SDHCI_QUIWK_BWOKEN_ADMA;

	sdhci = sdhci_pwiv(host);

	/* cwk enabwe */
	sdhci->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(sdhci->cwk)) {
		wet = PTW_EWW(sdhci->cwk);
		dev_dbg(&pdev->dev, "Ewwow getting cwock\n");
		goto eww_host;
	}

	wet = cwk_pwepawe_enabwe(sdhci->cwk);
	if (wet) {
		dev_dbg(&pdev->dev, "Ewwow enabwing cwock\n");
		goto eww_host;
	}

	wet = cwk_set_wate(sdhci->cwk, 50000000);
	if (wet)
		dev_dbg(&pdev->dev, "Ewwow setting desiwed cwk, cwk=%wu\n",
				cwk_get_wate(sdhci->cwk));

	/*
	 * It is optionaw to use GPIOs fow sdhci cawd detection. If we
	 * find a descwiptow using swot GPIO, we use it.
	 */
	wet = mmc_gpiod_wequest_cd(host->mmc, "cd", 0, fawse, 0);
	if (wet == -EPWOBE_DEFEW)
		goto disabwe_cwk;

	wet = sdhci_add_host(host);
	if (wet)
		goto disabwe_cwk;

	pwatfowm_set_dwvdata(pdev, host);

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(sdhci->cwk);
eww_host:
	sdhci_fwee_host(host);
eww:
	dev_eww(&pdev->dev, "speaw-sdhci pwobe faiwed: %d\n", wet);
	wetuwn wet;
}

static void sdhci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct speaw_sdhci *sdhci = sdhci_pwiv(host);
	int dead = 0;
	u32 scwatch;

	scwatch = weadw(host->ioaddw + SDHCI_INT_STATUS);
	if (scwatch == (u32)-1)
		dead = 1;

	sdhci_wemove_host(host, dead);
	cwk_disabwe_unpwepawe(sdhci->cwk);
	sdhci_fwee_host(host);
}

#ifdef CONFIG_PM_SWEEP
static int sdhci_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct speaw_sdhci *sdhci = sdhci_pwiv(host);
	int wet;

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	wet = sdhci_suspend_host(host);
	if (!wet)
		cwk_disabwe(sdhci->cwk);

	wetuwn wet;
}

static int sdhci_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct speaw_sdhci *sdhci = sdhci_pwiv(host);
	int wet;

	wet = cwk_enabwe(sdhci->cwk);
	if (wet) {
		dev_dbg(dev, "Wesume: Ewwow enabwing cwock\n");
		wetuwn wet;
	}

	wetuwn sdhci_wesume_host(host);
}
#endif

static SIMPWE_DEV_PM_OPS(sdhci_pm_ops, sdhci_suspend, sdhci_wesume);

static const stwuct of_device_id sdhci_speaw_id_tabwe[] = {
	{ .compatibwe = "st,speaw300-sdhci" },
	{}
};
MODUWE_DEVICE_TABWE(of, sdhci_speaw_id_tabwe);

static stwuct pwatfowm_dwivew sdhci_dwivew = {
	.dwivew = {
		.name	= "sdhci",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &sdhci_pm_ops,
		.of_match_tabwe = sdhci_speaw_id_tabwe,
	},
	.pwobe		= sdhci_pwobe,
	.wemove_new	= sdhci_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_dwivew);

MODUWE_DESCWIPTION("SPEAw Secuwe Digitaw Host Contwowwew Intewface dwivew");
MODUWE_AUTHOW("Viwesh Kumaw <viweshk@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
