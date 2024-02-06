// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NPCM SDHC MMC host contwowwew dwivew.
 *
 * Copywight (c) 2023 Nuvoton Technowogy cowpowation.
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude "sdhci-pwtfm.h"

static const stwuct sdhci_pwtfm_data npcm7xx_sdhci_pdata = {
	.quiwks  = SDHCI_QUIWK_DEWAY_AFTEW_POWEW,
	.quiwks2 = SDHCI_QUIWK2_STOP_WITH_TC |
		   SDHCI_QUIWK2_NO_1_8_V,
};

static const stwuct sdhci_pwtfm_data npcm8xx_sdhci_pdata = {
	.quiwks  = SDHCI_QUIWK_DEWAY_AFTEW_POWEW,
	.quiwks2 = SDHCI_QUIWK2_STOP_WITH_TC,
};

static int npcm_sdhci_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sdhci_pwtfm_data *data;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host;
	u32 caps;
	int wet;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	host = sdhci_pwtfm_init(pdev, data, 0);
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);

	pwtfm_host->cwk = devm_cwk_get_optionaw_enabwed(dev, NUWW);
	if (IS_EWW(pwtfm_host->cwk)) {
		wet = PTW_EWW(pwtfm_host->cwk);
		goto eww_sdhci;
	}

	caps = sdhci_weadw(host, SDHCI_CAPABIWITIES);
	if (caps & SDHCI_CAN_DO_8BIT)
		host->mmc->caps |= MMC_CAP_8_BIT_DATA;

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww_sdhci;

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_sdhci;

	wetuwn 0;

eww_sdhci:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static const stwuct of_device_id npcm_sdhci_of_match[] = {
	{ .compatibwe = "nuvoton,npcm750-sdhci", .data = &npcm7xx_sdhci_pdata },
	{ .compatibwe = "nuvoton,npcm845-sdhci", .data = &npcm8xx_sdhci_pdata },
	{ }
};
MODUWE_DEVICE_TABWE(of, npcm_sdhci_of_match);

static stwuct pwatfowm_dwivew npcm_sdhci_dwivew = {
	.dwivew = {
		.name	= "npcm-sdhci",
		.of_match_tabwe = npcm_sdhci_of_match,
		.pm	= &sdhci_pwtfm_pmops,
	},
	.pwobe		= npcm_sdhci_pwobe,
	.wemove_new	= sdhci_pwtfm_wemove,
};
moduwe_pwatfowm_dwivew(npcm_sdhci_dwivew);

MODUWE_DESCWIPTION("NPCM Secuwe Digitaw Host Contwowwew Intewface dwivew");
MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_WICENSE("GPW");
