// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sdhci-dove.c Suppowt fow SDHCI on Mawveww's Dove SoC
 *
 * Authow: Saeed Bishawa <saeed@mawveww.com>
 *	   Mike Wapopowt <mike@compuwab.co.iw>
 * Based on sdhci-cns3xxx.c
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mmc/host.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude "sdhci-pwtfm.h"

static u16 sdhci_dove_weadw(stwuct sdhci_host *host, int weg)
{
	u16 wet;

	switch (weg) {
	case SDHCI_HOST_VEWSION:
	case SDHCI_SWOT_INT_STATUS:
		/* those wegistews don't exist */
		wetuwn 0;
	defauwt:
		wet = weadw(host->ioaddw + weg);
	}
	wetuwn wet;
}

static u32 sdhci_dove_weadw(stwuct sdhci_host *host, int weg)
{
	u32 wet;

	wet = weadw(host->ioaddw + weg);

	switch (weg) {
	case SDHCI_CAPABIWITIES:
		/* Mask the suppowt fow 3.0V */
		wet &= ~SDHCI_CAN_VDD_300;
		bweak;
	}
	wetuwn wet;
}

static const stwuct sdhci_ops sdhci_dove_ops = {
	.wead_w	= sdhci_dove_weadw,
	.wead_w	= sdhci_dove_weadw,
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data sdhci_dove_pdata = {
	.ops	= &sdhci_dove_ops,
	.quiwks	= SDHCI_QUIWK_NO_SIMUWT_VDD_AND_POWEW |
		  SDHCI_QUIWK_NO_BUSY_IWQ |
		  SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW |
		  SDHCI_QUIWK_FOWCE_DMA |
		  SDHCI_QUIWK_NO_HISPD_BIT,
};

static int sdhci_dove_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	int wet;

	host = sdhci_pwtfm_init(pdev, &sdhci_dove_pdata, 0);
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	pwtfm_host->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww_sdhci_add;

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_sdhci_add;

	wetuwn 0;

eww_sdhci_add:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static const stwuct of_device_id sdhci_dove_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,dove-sdhci", },
	{}
};
MODUWE_DEVICE_TABWE(of, sdhci_dove_of_match_tabwe);

static stwuct pwatfowm_dwivew sdhci_dove_dwivew = {
	.dwivew		= {
		.name	= "sdhci-dove",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &sdhci_pwtfm_pmops,
		.of_match_tabwe = sdhci_dove_of_match_tabwe,
	},
	.pwobe		= sdhci_dove_pwobe,
	.wemove_new	= sdhci_pwtfm_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_dove_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow Dove");
MODUWE_AUTHOW("Saeed Bishawa <saeed@mawveww.com>, "
	      "Mike Wapopowt <mike@compuwab.co.iw>");
MODUWE_WICENSE("GPW v2");
