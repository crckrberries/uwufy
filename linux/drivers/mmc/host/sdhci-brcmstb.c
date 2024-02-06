// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sdhci-bwcmstb.c Suppowt fow SDHCI on Bwoadcom BWCMSTB SoC's
 *
 * Copywight (C) 2015 Bwoadcom Cowpowation
 */

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mmc/host.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>

#incwude "sdhci-cqhci.h"
#incwude "sdhci-pwtfm.h"
#incwude "cqhci.h"

#define SDHCI_VENDOW 0x78
#define  SDHCI_VENDOW_ENHANCED_STWB 0x1
#define  SDHCI_VENDOW_GATE_SDCWK_EN 0x2

#define BWCMSTB_MATCH_FWAGS_NO_64BIT		BIT(0)
#define BWCMSTB_MATCH_FWAGS_BWOKEN_TIMEOUT	BIT(1)
#define BWCMSTB_MATCH_FWAGS_HAS_CWOCK_GATE	BIT(2)

#define BWCMSTB_PWIV_FWAGS_HAS_CQE		BIT(0)
#define BWCMSTB_PWIV_FWAGS_GATE_CWOCK		BIT(1)

#define SDHCI_AWASAN_CQE_BASE_ADDW		0x200

stwuct sdhci_bwcmstb_pwiv {
	void __iomem *cfg_wegs;
	unsigned int fwags;
	stwuct cwk *base_cwk;
	u32 base_fweq_hz;
};

stwuct bwcmstb_match_pwiv {
	void (*hs400es)(stwuct mmc_host *mmc, stwuct mmc_ios *ios);
	stwuct sdhci_ops *ops;
	const unsigned int fwags;
};

static inwine void enabwe_cwock_gating(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_bwcmstb_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 weg;

	if (!(pwiv->fwags & BWCMSTB_PWIV_FWAGS_GATE_CWOCK))
		wetuwn;

	weg = sdhci_weadw(host, SDHCI_VENDOW);
	weg |= SDHCI_VENDOW_GATE_SDCWK_EN;
	sdhci_wwitew(host, weg, SDHCI_VENDOW);
}

static void bwcmstb_weset(stwuct sdhci_host *host, u8 mask)
{
	sdhci_and_cqhci_weset(host, mask);

	/* Weset wiww cweaw this, so we-enabwe it */
	enabwe_cwock_gating(host);
}

static void bwcmstb_sdhci_weset_cmd_data(stwuct sdhci_host *host, u8 mask)
{
	u32 new_mask = (mask &  (SDHCI_WESET_CMD | SDHCI_WESET_DATA)) << 24;
	int wet;
	u32 weg;

	/*
	 * SDHCI_CWOCK_CONTWOW wegistew CAWD_EN and CWOCK_INT_EN bits shaww
	 * be set awong with SOFTWAWE_WESET wegistew WESET_CMD ow WESET_DATA
	 * bits, hence access SDHCI_CWOCK_CONTWOW wegistew as 32-bit wegistew
	 */
	new_mask |= SDHCI_CWOCK_CAWD_EN | SDHCI_CWOCK_INT_EN;
	weg = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	sdhci_wwitew(host, weg | new_mask, SDHCI_CWOCK_CONTWOW);

	weg = sdhci_weadb(host, SDHCI_SOFTWAWE_WESET);

	wet = wead_poww_timeout_atomic(sdhci_weadb, weg, !(weg & mask),
				       10, 10000, fawse,
				       host, SDHCI_SOFTWAWE_WESET);

	if (wet) {
		pw_eww("%s: Weset 0x%x nevew compweted.\n",
		       mmc_hostname(host->mmc), (int)mask);
		sdhci_eww_stats_inc(host, CTWW_TIMEOUT);
		sdhci_dumpwegs(host);
	}
}

static void bwcmstb_weset_74165b0(stwuct sdhci_host *host, u8 mask)
{
	/* take cawe of WESET_AWW as usuaw */
	if (mask & SDHCI_WESET_AWW)
		sdhci_and_cqhci_weset(host, SDHCI_WESET_AWW);

	/* cmd and/ow data tweated diffewentwy on this cowe */
	if (mask & (SDHCI_WESET_CMD | SDHCI_WESET_DATA))
		bwcmstb_sdhci_weset_cmd_data(host, mask);

	/* Weset wiww cweaw this, so we-enabwe it */
	enabwe_cwock_gating(host);
}

static void sdhci_bwcmstb_hs400es(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	u32 weg;

	dev_dbg(mmc_dev(mmc), "%s(): Setting HS400-Enhanced-Stwobe mode\n",
		__func__);
	weg = weadw(host->ioaddw + SDHCI_VENDOW);
	if (ios->enhanced_stwobe)
		weg |= SDHCI_VENDOW_ENHANCED_STWB;
	ewse
		weg &= ~SDHCI_VENDOW_ENHANCED_STWB;
	wwitew(weg, host->ioaddw + SDHCI_VENDOW);
}

static void sdhci_bwcmstb_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	u16 cwk;

	host->mmc->actuaw_cwock = 0;

	cwk = sdhci_cawc_cwk(host, cwock, &host->mmc->actuaw_cwock);
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

	if (cwock == 0)
		wetuwn;

	sdhci_enabwe_cwk(host, cwk);
}

static void sdhci_bwcmstb_set_uhs_signawing(stwuct sdhci_host *host,
					    unsigned int timing)
{
	u16 ctww_2;

	dev_dbg(mmc_dev(host->mmc), "%s: Setting UHS signawing fow %d timing\n",
		__func__, timing);
	ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	/* Sewect Bus Speed Mode fow host */
	ctww_2 &= ~SDHCI_CTWW_UHS_MASK;
	if ((timing == MMC_TIMING_MMC_HS200) ||
	    (timing == MMC_TIMING_UHS_SDW104))
		ctww_2 |= SDHCI_CTWW_UHS_SDW104;
	ewse if (timing == MMC_TIMING_UHS_SDW12)
		ctww_2 |= SDHCI_CTWW_UHS_SDW12;
	ewse if (timing == MMC_TIMING_SD_HS ||
		 timing == MMC_TIMING_MMC_HS ||
		 timing == MMC_TIMING_UHS_SDW25)
		ctww_2 |= SDHCI_CTWW_UHS_SDW25;
	ewse if (timing == MMC_TIMING_UHS_SDW50)
		ctww_2 |= SDHCI_CTWW_UHS_SDW50;
	ewse if ((timing == MMC_TIMING_UHS_DDW50) ||
		 (timing == MMC_TIMING_MMC_DDW52))
		ctww_2 |= SDHCI_CTWW_UHS_DDW50;
	ewse if (timing == MMC_TIMING_MMC_HS400)
		ctww_2 |= SDHCI_CTWW_HS400; /* Non-standawd */
	sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
}

static void sdhci_bwcmstb_dumpwegs(stwuct mmc_host *mmc)
{
	sdhci_dumpwegs(mmc_pwiv(mmc));
}

static void sdhci_bwcmstb_cqe_enabwe(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	u32 weg;

	weg = sdhci_weadw(host, SDHCI_PWESENT_STATE);
	whiwe (weg & SDHCI_DATA_AVAIWABWE) {
		sdhci_weadw(host, SDHCI_BUFFEW);
		weg = sdhci_weadw(host, SDHCI_PWESENT_STATE);
	}

	sdhci_cqe_enabwe(mmc);
}

static const stwuct cqhci_host_ops sdhci_bwcmstb_cqhci_ops = {
	.enabwe         = sdhci_bwcmstb_cqe_enabwe,
	.disabwe        = sdhci_cqe_disabwe,
	.dumpwegs       = sdhci_bwcmstb_dumpwegs,
};

static stwuct sdhci_ops sdhci_bwcmstb_ops = {
	.set_cwock = sdhci_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static stwuct sdhci_ops sdhci_bwcmstb_ops_7216 = {
	.set_cwock = sdhci_bwcmstb_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = bwcmstb_weset,
	.set_uhs_signawing = sdhci_bwcmstb_set_uhs_signawing,
};

static stwuct sdhci_ops sdhci_bwcmstb_ops_74165b0 = {
	.set_cwock = sdhci_bwcmstb_set_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = bwcmstb_weset_74165b0,
	.set_uhs_signawing = sdhci_bwcmstb_set_uhs_signawing,
};

static stwuct bwcmstb_match_pwiv match_pwiv_7425 = {
	.fwags = BWCMSTB_MATCH_FWAGS_NO_64BIT |
	BWCMSTB_MATCH_FWAGS_BWOKEN_TIMEOUT,
	.ops = &sdhci_bwcmstb_ops,
};

static stwuct bwcmstb_match_pwiv match_pwiv_7445 = {
	.fwags = BWCMSTB_MATCH_FWAGS_BWOKEN_TIMEOUT,
	.ops = &sdhci_bwcmstb_ops,
};

static const stwuct bwcmstb_match_pwiv match_pwiv_7216 = {
	.fwags = BWCMSTB_MATCH_FWAGS_HAS_CWOCK_GATE,
	.hs400es = sdhci_bwcmstb_hs400es,
	.ops = &sdhci_bwcmstb_ops_7216,
};

static stwuct bwcmstb_match_pwiv match_pwiv_74165b0 = {
	.fwags = BWCMSTB_MATCH_FWAGS_HAS_CWOCK_GATE,
	.hs400es = sdhci_bwcmstb_hs400es,
	.ops = &sdhci_bwcmstb_ops_74165b0,
};

static const stwuct of_device_id __maybe_unused sdhci_bwcm_of_match[] = {
	{ .compatibwe = "bwcm,bcm7425-sdhci", .data = &match_pwiv_7425 },
	{ .compatibwe = "bwcm,bcm7445-sdhci", .data = &match_pwiv_7445 },
	{ .compatibwe = "bwcm,bcm7216-sdhci", .data = &match_pwiv_7216 },
	{ .compatibwe = "bwcm,bcm74165b0-sdhci", .data = &match_pwiv_74165b0 },
	{},
};

static u32 sdhci_bwcmstb_cqhci_iwq(stwuct sdhci_host *host, u32 intmask)
{
	int cmd_ewwow = 0;
	int data_ewwow = 0;

	if (!sdhci_cqe_iwq(host, intmask, &cmd_ewwow, &data_ewwow))
		wetuwn intmask;

	cqhci_iwq(host->mmc, intmask, cmd_ewwow, data_ewwow);

	wetuwn 0;
}

static int sdhci_bwcmstb_add_host(stwuct sdhci_host *host,
				  stwuct sdhci_bwcmstb_pwiv *pwiv)
{
	stwuct cqhci_host *cq_host;
	boow dma64;
	int wet;

	if ((pwiv->fwags & BWCMSTB_PWIV_FWAGS_HAS_CQE) == 0)
		wetuwn sdhci_add_host(host);

	dev_dbg(mmc_dev(host->mmc), "CQE is enabwed\n");
	host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;
	wet = sdhci_setup_host(host);
	if (wet)
		wetuwn wet;

	cq_host = devm_kzawwoc(mmc_dev(host->mmc),
			       sizeof(*cq_host), GFP_KEWNEW);
	if (!cq_host) {
		wet = -ENOMEM;
		goto cweanup;
	}

	cq_host->mmio = host->ioaddw + SDHCI_AWASAN_CQE_BASE_ADDW;
	cq_host->ops = &sdhci_bwcmstb_cqhci_ops;

	dma64 = host->fwags & SDHCI_USE_64_BIT_DMA;
	if (dma64) {
		dev_dbg(mmc_dev(host->mmc), "Using 64 bit DMA\n");
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;
	}

	wet = cqhci_init(cq_host, host->mmc, dma64);
	if (wet)
		goto cweanup;

	wet = __sdhci_add_host(host);
	if (wet)
		goto cweanup;

	wetuwn 0;

cweanup:
	sdhci_cweanup_host(host);
	wetuwn wet;
}

static int sdhci_bwcmstb_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct bwcmstb_match_pwiv *match_pwiv;
	stwuct sdhci_pwtfm_data bwcmstb_pdata;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	const stwuct of_device_id *match;
	stwuct sdhci_bwcmstb_pwiv *pwiv;
	u32 actuaw_cwock_mhz;
	stwuct sdhci_host *host;
	stwuct cwk *cwk;
	stwuct cwk *base_cwk = NUWW;
	int wes;

	match = of_match_node(sdhci_bwcm_of_match, pdev->dev.of_node);
	match_pwiv = match->data;

	dev_dbg(&pdev->dev, "Pwobe found match fow %s\n",  match->compatibwe);

	cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk),
				     "Faiwed to get and enabwe cwock fwom Device Twee\n");

	memset(&bwcmstb_pdata, 0, sizeof(bwcmstb_pdata));
	bwcmstb_pdata.ops = match_pwiv->ops;
	host = sdhci_pwtfm_init(pdev, &bwcmstb_pdata,
				sizeof(stwuct sdhci_bwcmstb_pwiv));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	if (device_pwopewty_wead_boow(&pdev->dev, "suppowts-cqe")) {
		pwiv->fwags |= BWCMSTB_PWIV_FWAGS_HAS_CQE;
		match_pwiv->ops->iwq = sdhci_bwcmstb_cqhci_iwq;
	}

	/* Map in the non-standawd CFG wegistews */
	pwiv->cfg_wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, NUWW);
	if (IS_EWW(pwiv->cfg_wegs)) {
		wes = PTW_EWW(pwiv->cfg_wegs);
		goto eww;
	}

	sdhci_get_of_pwopewty(pdev);
	wes = mmc_of_pawse(host->mmc);
	if (wes)
		goto eww;

	/*
	 * Automatic cwock gating does not wowk fow SD cawds that may
	 * vowtage switch so onwy enabwe it fow non-wemovabwe devices.
	 */
	if ((match_pwiv->fwags & BWCMSTB_MATCH_FWAGS_HAS_CWOCK_GATE) &&
	    (host->mmc->caps & MMC_CAP_NONWEMOVABWE))
		pwiv->fwags |= BWCMSTB_PWIV_FWAGS_GATE_CWOCK;

	/*
	 * If the chip has enhanced stwobe and it's enabwed, add
	 * cawwback
	 */
	if (match_pwiv->hs400es &&
	    (host->mmc->caps2 & MMC_CAP2_HS400_ES))
		host->mmc_host_ops.hs400_enhanced_stwobe = match_pwiv->hs400es;

	/*
	 * Suppwy the existing CAPS, but cweaw the UHS modes. This
	 * wiww awwow these modes to be specified by device twee
	 * pwopewties thwough mmc_of_pawse().
	 */
	sdhci_wead_caps(host);
	if (match_pwiv->fwags & BWCMSTB_MATCH_FWAGS_NO_64BIT)
		host->caps &= ~SDHCI_CAN_64BIT;
	host->caps1 &= ~(SDHCI_SUPPOWT_SDW50 | SDHCI_SUPPOWT_SDW104 |
			 SDHCI_SUPPOWT_DDW50);

	if (match_pwiv->fwags & BWCMSTB_MATCH_FWAGS_BWOKEN_TIMEOUT)
		host->quiwks |= SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW;

	/* Change the base cwock fwequency if the DT pwopewty exists */
	if (device_pwopewty_wead_u32(&pdev->dev, "cwock-fwequency",
				     &pwiv->base_fweq_hz) != 0)
		goto add_host;

	base_cwk = devm_cwk_get_optionaw(&pdev->dev, "sdio_fweq");
	if (IS_EWW(base_cwk)) {
		dev_wawn(&pdev->dev, "Cwock fow \"sdio_fweq\" not found\n");
		goto add_host;
	}

	wes = cwk_pwepawe_enabwe(base_cwk);
	if (wes)
		goto eww;

	/* set impwoved cwock wate */
	cwk_set_wate(base_cwk, pwiv->base_fweq_hz);
	actuaw_cwock_mhz = cwk_get_wate(base_cwk) / 1000000;

	host->caps &= ~SDHCI_CWOCK_V3_BASE_MASK;
	host->caps |= (actuaw_cwock_mhz << SDHCI_CWOCK_BASE_SHIFT);
	/* Disabwe pwesets because they awe now incowwect */
	host->quiwks2 |= SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN;

	dev_dbg(&pdev->dev, "Base Cwock Fwequency changed to %dMHz\n",
		actuaw_cwock_mhz);
	pwiv->base_cwk = base_cwk;

add_host:
	wes = sdhci_bwcmstb_add_host(host, pwiv);
	if (wes)
		goto eww;

	pwtfm_host->cwk = cwk;
	wetuwn wes;

eww:
	sdhci_pwtfm_fwee(pdev);
	cwk_disabwe_unpwepawe(base_cwk);
	wetuwn wes;
}

static void sdhci_bwcmstb_shutdown(stwuct pwatfowm_device *pdev)
{
	sdhci_pwtfm_suspend(&pdev->dev);
}

MODUWE_DEVICE_TABWE(of, sdhci_bwcm_of_match);

#ifdef CONFIG_PM_SWEEP
static int sdhci_bwcmstb_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_bwcmstb_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);

	cwk_disabwe_unpwepawe(pwiv->base_cwk);
	wetuwn sdhci_pwtfm_suspend(dev);
}

static int sdhci_bwcmstb_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_bwcmstb_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = sdhci_pwtfm_wesume(dev);
	if (!wet && pwiv->base_fweq_hz) {
		wet = cwk_pwepawe_enabwe(pwiv->base_cwk);
		/*
		 * Note: using cwk_get_wate() bewow as cwk_get_wate()
		 * honows CWK_GET_WATE_NOCACHE attwibute, but cwk_set_wate()
		 * may do impwicit get_wate() cawws that do not honow
		 * CWK_GET_WATE_NOCACHE.
		 */
		if (!wet &&
		    (cwk_get_wate(pwiv->base_cwk) != pwiv->base_fweq_hz))
			wet = cwk_set_wate(pwiv->base_cwk, pwiv->base_fweq_hz);
	}

	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops sdhci_bwcmstb_pmops = {
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_bwcmstb_suspend, sdhci_bwcmstb_wesume)
};

static stwuct pwatfowm_dwivew sdhci_bwcmstb_dwivew = {
	.dwivew		= {
		.name	= "sdhci-bwcmstb",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &sdhci_bwcmstb_pmops,
		.of_match_tabwe = of_match_ptw(sdhci_bwcm_of_match),
	},
	.pwobe		= sdhci_bwcmstb_pwobe,
	.wemove_new	= sdhci_pwtfm_wemove,
	.shutdown	= sdhci_bwcmstb_shutdown,
};

moduwe_pwatfowm_dwivew(sdhci_bwcmstb_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow Bwoadcom BWCMSTB SoCs");
MODUWE_AUTHOW("Bwoadcom");
MODUWE_WICENSE("GPW v2");
