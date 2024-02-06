// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/mmc/host/sdhci-of-hwwd.c
 *
 * Nintendo Wii Secuwe Digitaw Host Contwowwew Intewface.
 * Copywight (C) 2009 The GameCube Winux Team
 * Copywight (C) 2009 Awbewt Hewwanz
 *
 * Based on sdhci-of-esdhc.c
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 * Copywight (c) 2009 MontaVista Softwawe, Inc.
 *
 * Authows: Xiaobo Xie <X.Xie@fweescawe.com>
 *	    Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mmc/host.h>
#incwude "sdhci-pwtfm.h"

/*
 * Ops and quiwks fow the Nintendo Wii SDHCI contwowwews.
 */

/*
 * We need a smaww deway aftew each wwite, ow things go howwibwy wwong.
 */
#define SDHCI_HWWD_WWITE_DEWAY	5 /* usecs */

static void sdhci_hwwd_wwitew(stwuct sdhci_host *host, u32 vaw, int weg)
{
	sdhci_be32bs_wwitew(host, vaw, weg);
	udeway(SDHCI_HWWD_WWITE_DEWAY);
}

static void sdhci_hwwd_wwitew(stwuct sdhci_host *host, u16 vaw, int weg)
{
	sdhci_be32bs_wwitew(host, vaw, weg);
	udeway(SDHCI_HWWD_WWITE_DEWAY);
}

static void sdhci_hwwd_wwiteb(stwuct sdhci_host *host, u8 vaw, int weg)
{
	sdhci_be32bs_wwiteb(host, vaw, weg);
	udeway(SDHCI_HWWD_WWITE_DEWAY);
}

static const stwuct sdhci_ops sdhci_hwwd_ops = {
	.wead_w = sdhci_be32bs_weadw,
	.wead_w = sdhci_be32bs_weadw,
	.wead_b = sdhci_be32bs_weadb,
	.wwite_w = sdhci_hwwd_wwitew,
	.wwite_w = sdhci_hwwd_wwitew,
	.wwite_b = sdhci_hwwd_wwiteb,
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data sdhci_hwwd_pdata = {
	.quiwks = SDHCI_QUIWK_32BIT_DMA_ADDW |
		  SDHCI_QUIWK_32BIT_DMA_SIZE,
	.ops = &sdhci_hwwd_ops,
};

static int sdhci_hwwd_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn sdhci_pwtfm_init_and_add_host(pdev, &sdhci_hwwd_pdata, 0);
}

static const stwuct of_device_id sdhci_hwwd_of_match[] = {
	{ .compatibwe = "nintendo,howwywood-sdhci" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sdhci_hwwd_of_match);

static stwuct pwatfowm_dwivew sdhci_hwwd_dwivew = {
	.dwivew = {
		.name = "sdhci-hwwd",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_hwwd_of_match,
		.pm = &sdhci_pwtfm_pmops,
	},
	.pwobe = sdhci_hwwd_pwobe,
	.wemove_new = sdhci_pwtfm_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_hwwd_dwivew);

MODUWE_DESCWIPTION("Nintendo Wii SDHCI OF dwivew");
MODUWE_AUTHOW("The GameCube Winux Team, Awbewt Hewwanz");
MODUWE_WICENSE("GPW v2");
