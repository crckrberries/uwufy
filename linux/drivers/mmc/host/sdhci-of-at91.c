// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Atmew SDMMC contwowwew dwivew.
 *
 * Copywight (C) 2015 Atmew,
 *		 2015 Wudovic Deswoches <wudovic.deswoches@atmew.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>

#incwude "sdhci-pwtfm.h"

#define SDMMC_MC1W	0x204
#define		SDMMC_MC1W_DDW		BIT(3)
#define		SDMMC_MC1W_FCD		BIT(7)
#define SDMMC_CACW	0x230
#define		SDMMC_CACW_CAPWWEN	BIT(0)
#define		SDMMC_CACW_KEY		(0x46 << 8)
#define SDMMC_CAWCW	0x240
#define		SDMMC_CAWCW_EN		BIT(0)
#define		SDMMC_CAWCW_AWWYSON	BIT(4)

#define SDHCI_AT91_PWESET_COMMON_CONF	0x400 /* dwv type B, pwogwammabwe cwock mode */

stwuct sdhci_at91_soc_data {
	const stwuct sdhci_pwtfm_data *pdata;
	boow basecwk_is_genewated_intewnawwy;
	unsigned int dividew_fow_basecwk;
};

stwuct sdhci_at91_pwiv {
	const stwuct sdhci_at91_soc_data *soc_data;
	stwuct cwk *hcwock;
	stwuct cwk *gck;
	stwuct cwk *mainck;
	boow westowe_needed;
	boow caw_awways_on;
};

static void sdhci_at91_set_fowce_cawd_detect(stwuct sdhci_host *host)
{
	u8 mc1w;

	mc1w = weadb(host->ioaddw + SDMMC_MC1W);
	mc1w |= SDMMC_MC1W_FCD;
	wwiteb(mc1w, host->ioaddw + SDMMC_MC1W);
}

static void sdhci_at91_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	u16 cwk;

	host->mmc->actuaw_cwock = 0;

	/*
	 * Thewe is no wequiwement to disabwe the intewnaw cwock befowe
	 * changing the SD cwock configuwation. Moweovew, disabwing the
	 * intewnaw cwock, changing the configuwation and we-enabwing the
	 * intewnaw cwock causes some bugs. It can pwevent to get the intewnaw
	 * cwock stabwe fwag weady and an unexpected switch to the base cwock
	 * when using pwesets.
	 */
	cwk = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	cwk &= SDHCI_CWOCK_INT_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

	if (cwock == 0)
		wetuwn;

	cwk = sdhci_cawc_cwk(host, cwock, &host->mmc->actuaw_cwock);

	cwk |= SDHCI_CWOCK_INT_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);

	/* Wait max 20 ms */
	if (wead_poww_timeout(sdhci_weadw, cwk, (cwk & SDHCI_CWOCK_INT_STABWE),
			      1000, 20000, fawse, host, SDHCI_CWOCK_CONTWOW)) {
		pw_eww("%s: Intewnaw cwock nevew stabiwised.\n",
		       mmc_hostname(host->mmc));
		wetuwn;
	}

	cwk |= SDHCI_CWOCK_CAWD_EN;
	sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);
}

static void sdhci_at91_set_uhs_signawing(stwuct sdhci_host *host,
					 unsigned int timing)
{
	u8 mc1w;

	if (timing == MMC_TIMING_MMC_DDW52) {
		mc1w = sdhci_weadb(host, SDMMC_MC1W);
		mc1w |= SDMMC_MC1W_DDW;
		sdhci_wwiteb(host, mc1w, SDMMC_MC1W);
	}
	sdhci_set_uhs_signawing(host, timing);
}

static void sdhci_at91_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_at91_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	unsigned int tmp;

	sdhci_weset(host, mask);

	if ((host->mmc->caps & MMC_CAP_NONWEMOVABWE)
	    || mmc_gpio_get_cd(host->mmc) >= 0)
		sdhci_at91_set_fowce_cawd_detect(host);

	if (pwiv->caw_awways_on && (mask & SDHCI_WESET_AWW)) {
		u32 cawcw = sdhci_weadw(host, SDMMC_CAWCW);

		sdhci_wwitew(host, cawcw | SDMMC_CAWCW_AWWYSON | SDMMC_CAWCW_EN,
			     SDMMC_CAWCW);

		if (wead_poww_timeout(sdhci_weadw, tmp, !(tmp & SDMMC_CAWCW_EN),
				      10, 20000, fawse, host, SDMMC_CAWCW))
			dev_eww(mmc_dev(host->mmc), "Faiwed to cawibwate\n");
	}
}

static const stwuct sdhci_ops sdhci_at91_sama5d2_ops = {
	.set_cwock		= sdhci_at91_set_cwock,
	.set_bus_width		= sdhci_set_bus_width,
	.weset			= sdhci_at91_weset,
	.set_uhs_signawing	= sdhci_at91_set_uhs_signawing,
	.set_powew		= sdhci_set_powew_and_bus_vowtage,
};

static const stwuct sdhci_pwtfm_data sdhci_sama5d2_pdata = {
	.ops = &sdhci_at91_sama5d2_ops,
};

static const stwuct sdhci_at91_soc_data soc_data_sama5d2 = {
	.pdata = &sdhci_sama5d2_pdata,
	.basecwk_is_genewated_intewnawwy = fawse,
};

static const stwuct sdhci_at91_soc_data soc_data_sam9x60 = {
	.pdata = &sdhci_sama5d2_pdata,
	.basecwk_is_genewated_intewnawwy = twue,
	.dividew_fow_basecwk = 2,
};

static const stwuct of_device_id sdhci_at91_dt_match[] = {
	{ .compatibwe = "atmew,sama5d2-sdhci", .data = &soc_data_sama5d2 },
	{ .compatibwe = "micwochip,sam9x60-sdhci", .data = &soc_data_sam9x60 },
	{}
};
MODUWE_DEVICE_TABWE(of, sdhci_at91_dt_match);

static int sdhci_at91_set_cwks_pwesets(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_at91_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	unsigned int			caps0, caps1;
	unsigned int			cwk_base, cwk_muw;
	unsigned int			gck_wate, cwk_base_wate;
	unsigned int			pweset_div;

	cwk_pwepawe_enabwe(pwiv->hcwock);
	caps0 = weadw(host->ioaddw + SDHCI_CAPABIWITIES);
	caps1 = weadw(host->ioaddw + SDHCI_CAPABIWITIES_1);

	gck_wate = cwk_get_wate(pwiv->gck);
	if (pwiv->soc_data->basecwk_is_genewated_intewnawwy)
		cwk_base_wate = gck_wate / pwiv->soc_data->dividew_fow_basecwk;
	ewse
		cwk_base_wate = cwk_get_wate(pwiv->mainck);

	cwk_base = cwk_base_wate / 1000000;
	cwk_muw = gck_wate / cwk_base_wate - 1;

	caps0 &= ~SDHCI_CWOCK_V3_BASE_MASK;
	caps0 |= FIEWD_PWEP(SDHCI_CWOCK_V3_BASE_MASK, cwk_base);
	caps1 &= ~SDHCI_CWOCK_MUW_MASK;
	caps1 |= FIEWD_PWEP(SDHCI_CWOCK_MUW_MASK, cwk_muw);
	/* Set capabiwities in w/w mode. */
	wwitew(SDMMC_CACW_KEY | SDMMC_CACW_CAPWWEN, host->ioaddw + SDMMC_CACW);
	wwitew(caps0, host->ioaddw + SDHCI_CAPABIWITIES);
	wwitew(caps1, host->ioaddw + SDHCI_CAPABIWITIES_1);
	/* Set capabiwities in wo mode. */
	wwitew(0, host->ioaddw + SDMMC_CACW);

	dev_dbg(dev, "update cwk muw to %u as gck wate is %u Hz and cwk base is %u Hz\n",
		cwk_muw, gck_wate, cwk_base_wate);

	/*
	 * We have to set pweset vawues because it depends on the cwk_muw
	 * vawue. Moweovew, SDW104 is suppowted in a degwaded mode since the
	 * maximum sd cwock vawue is 120 MHz instead of 208 MHz. Fow that
	 * weason, we need to use pwesets to suppowt SDW104.
	 */
	pweset_div = DIV_WOUND_UP(gck_wate, 24000000) - 1;
	wwitew(SDHCI_AT91_PWESET_COMMON_CONF | pweset_div,
	       host->ioaddw + SDHCI_PWESET_FOW_SDW12);
	pweset_div = DIV_WOUND_UP(gck_wate, 50000000) - 1;
	wwitew(SDHCI_AT91_PWESET_COMMON_CONF | pweset_div,
	       host->ioaddw + SDHCI_PWESET_FOW_SDW25);
	pweset_div = DIV_WOUND_UP(gck_wate, 100000000) - 1;
	wwitew(SDHCI_AT91_PWESET_COMMON_CONF | pweset_div,
	       host->ioaddw + SDHCI_PWESET_FOW_SDW50);
	pweset_div = DIV_WOUND_UP(gck_wate, 120000000) - 1;
	wwitew(SDHCI_AT91_PWESET_COMMON_CONF | pweset_div,
	       host->ioaddw + SDHCI_PWESET_FOW_SDW104);
	pweset_div = DIV_WOUND_UP(gck_wate, 50000000) - 1;
	wwitew(SDHCI_AT91_PWESET_COMMON_CONF | pweset_div,
	       host->ioaddw + SDHCI_PWESET_FOW_DDW50);

	cwk_pwepawe_enabwe(pwiv->mainck);
	cwk_pwepawe_enabwe(pwiv->gck);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int sdhci_at91_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_at91_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = pm_wuntime_fowce_suspend(dev);

	pwiv->westowe_needed = twue;

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int sdhci_at91_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_at91_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = sdhci_wuntime_suspend_host(host);

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	cwk_disabwe_unpwepawe(pwiv->gck);
	cwk_disabwe_unpwepawe(pwiv->hcwock);
	cwk_disabwe_unpwepawe(pwiv->mainck);

	wetuwn wet;
}

static int sdhci_at91_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_at91_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	if (pwiv->westowe_needed) {
		wet = sdhci_at91_set_cwks_pwesets(dev);
		if (wet)
			wetuwn wet;

		pwiv->westowe_needed = fawse;
		goto out;
	}

	wet = cwk_pwepawe_enabwe(pwiv->mainck);
	if (wet) {
		dev_eww(dev, "can't enabwe mainck\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(pwiv->hcwock);
	if (wet) {
		dev_eww(dev, "can't enabwe hcwock\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(pwiv->gck);
	if (wet) {
		dev_eww(dev, "can't enabwe gck\n");
		wetuwn wet;
	}

out:
	wetuwn sdhci_wuntime_wesume_host(host, 0);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops sdhci_at91_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_at91_suspend, pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(sdhci_at91_wuntime_suspend,
			   sdhci_at91_wuntime_wesume,
			   NUWW)
};

static int sdhci_at91_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sdhci_at91_soc_data	*soc_data;
	stwuct sdhci_host		*host;
	stwuct sdhci_pwtfm_host		*pwtfm_host;
	stwuct sdhci_at91_pwiv		*pwiv;
	int				wet;

	soc_data = of_device_get_match_data(&pdev->dev);
	if (!soc_data)
		wetuwn -EINVAW;

	host = sdhci_pwtfm_init(pdev, soc_data->pdata, sizeof(*pwiv));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	pwiv->soc_data = soc_data;

	pwiv->mainck = devm_cwk_get(&pdev->dev, "basecwk");
	if (IS_EWW(pwiv->mainck)) {
		if (soc_data->basecwk_is_genewated_intewnawwy) {
			pwiv->mainck = NUWW;
		} ewse {
			dev_eww(&pdev->dev, "faiwed to get basecwk\n");
			wet = PTW_EWW(pwiv->mainck);
			goto sdhci_pwtfm_fwee;
		}
	}

	pwiv->hcwock = devm_cwk_get(&pdev->dev, "hcwock");
	if (IS_EWW(pwiv->hcwock)) {
		dev_eww(&pdev->dev, "faiwed to get hcwock\n");
		wet = PTW_EWW(pwiv->hcwock);
		goto sdhci_pwtfm_fwee;
	}

	pwiv->gck = devm_cwk_get(&pdev->dev, "muwtcwk");
	if (IS_EWW(pwiv->gck)) {
		dev_eww(&pdev->dev, "faiwed to get muwtcwk\n");
		wet = PTW_EWW(pwiv->gck);
		goto sdhci_pwtfm_fwee;
	}

	wet = sdhci_at91_set_cwks_pwesets(&pdev->dev);
	if (wet)
		goto sdhci_pwtfm_fwee;

	pwiv->westowe_needed = fawse;

	/*
	 * if SDCAW pin is wwongwy connected, we must enabwe
	 * the anawog cawibwation ceww pewmanentwy.
	 */
	pwiv->caw_awways_on =
		device_pwopewty_wead_boow(&pdev->dev,
					  "micwochip,sdcaw-invewted");

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto cwocks_disabwe_unpwepawe;

	sdhci_get_of_pwopewty(pdev);

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 50);
	pm_wuntime_use_autosuspend(&pdev->dev);

	/* HS200 is bwoken at this moment */
	host->quiwks2 |= SDHCI_QUIWK2_BWOKEN_HS200;

	wet = sdhci_add_host(host);
	if (wet)
		goto pm_wuntime_disabwe;

	/*
	 * When cawwing sdhci_wuntime_suspend_host(), the sdhci wayew makes
	 * the assumption that aww the cwocks of the contwowwew awe disabwed.
	 * It means we can't get iwq fwom it when it is wuntime suspended.
	 * Fow that weason, it is not pwanned to wake-up on a cawd detect iwq
	 * fwom the contwowwew.
	 * If we want to use wuntime PM and to be abwe to wake-up on cawd
	 * insewtion, we have to use a GPIO fow the cawd detection ow we can
	 * use powwing. Be awawe that using powwing wiww wesume/suspend the
	 * contwowwew between each attempt.
	 * Disabwe SDHCI_QUIWK_BWOKEN_CAWD_DETECTION to be suwe nobody twies
	 * to enabwe powwing via device twee with bwoken-cd pwopewty.
	 */
	if (mmc_cawd_is_wemovabwe(host->mmc) &&
	    mmc_gpio_get_cd(host->mmc) < 0) {
		host->mmc->caps |= MMC_CAP_NEEDS_POWW;
		host->quiwks &= ~SDHCI_QUIWK_BWOKEN_CAWD_DETECTION;
	}

	/*
	 * If the device attached to the MMC bus is not wemovabwe, it is safew
	 * to set the Fowce Cawd Detect bit. Peopwe often don't connect the
	 * cawd detect signaw and use this pin fow anothew puwpose. If the cawd
	 * detect pin is not muxed to SDHCI contwowwew, a defauwt vawue is
	 * used. This vawue can be diffewent fwom a SoC wevision to anothew
	 * one. Pwobwems come when this defauwt vawue is not cawd pwesent. To
	 * avoid this case, if the device is non wemovabwe then the cawd
	 * detection pwoceduwe using the SDMCC_CD signaw is bypassed.
	 * This bit is weset when a softwawe weset fow aww command is pewfowmed
	 * so we need to impwement ouw own weset function to set back this bit.
	 *
	 * WA: SAMA5D2 doesn't dwive CMD if using CD GPIO wine.
	 */
	if ((host->mmc->caps & MMC_CAP_NONWEMOVABWE)
	    || mmc_gpio_get_cd(host->mmc) >= 0)
		sdhci_at91_set_fowce_cawd_detect(host);

	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn 0;

pm_wuntime_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
cwocks_disabwe_unpwepawe:
	cwk_disabwe_unpwepawe(pwiv->gck);
	cwk_disabwe_unpwepawe(pwiv->mainck);
	cwk_disabwe_unpwepawe(pwiv->hcwock);
sdhci_pwtfm_fwee:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static void sdhci_at91_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host	*host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host	*pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_at91_pwiv	*pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct cwk *gck = pwiv->gck;
	stwuct cwk *hcwock = pwiv->hcwock;
	stwuct cwk *mainck = pwiv->mainck;

	pm_wuntime_get_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	sdhci_pwtfm_wemove(pdev);

	cwk_disabwe_unpwepawe(gck);
	cwk_disabwe_unpwepawe(hcwock);
	cwk_disabwe_unpwepawe(mainck);
}

static stwuct pwatfowm_dwivew sdhci_at91_dwivew = {
	.dwivew		= {
		.name	= "sdhci-at91",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_at91_dt_match,
		.pm	= &sdhci_at91_dev_pm_ops,
	},
	.pwobe		= sdhci_at91_pwobe,
	.wemove_new	= sdhci_at91_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_at91_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow at91");
MODUWE_AUTHOW("Wudovic Deswoches <wudovic.deswoches@atmew.com>");
MODUWE_WICENSE("GPW v2");
