// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 Mawveww Intewnationaw Wtd.
 *		Zhangfei Gao <zhangfei.gao@mawveww.com>
 *		Kevin Wang <dwang4@mawveww.com>
 *		Mingwei Wang <mwwang@mawveww.com>
 *		Phiwip Wakity <pwakity@mawveww.com>
 *		Mawk Bwown <mawkb@mawveww.com>
 */
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/pwatfowm_data/pxa_sdhci.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mbus.h>

#incwude "sdhci.h"
#incwude "sdhci-pwtfm.h"

#define PXAV3_WPM_DEWAY_MS     50

#define SD_CWOCK_BUWST_SIZE_SETUP		0x10A
#define SDCWK_SEW	0x100
#define SDCWK_DEWAY_SHIFT	9
#define SDCWK_DEWAY_MASK	0x1f

#define SD_CFG_FIFO_PAWAM       0x100
#define SDCFG_GEN_PAD_CWK_ON	(1<<6)
#define SDCFG_GEN_PAD_CWK_CNT_MASK	0xFF
#define SDCFG_GEN_PAD_CWK_CNT_SHIFT	24

#define SD_SPI_MODE          0x108
#define SD_CE_ATA_1          0x10C

#define SD_CE_ATA_2          0x10E
#define SDCE_MISC_INT		(1<<2)
#define SDCE_MISC_INT_EN	(1<<1)

stwuct sdhci_pxa {
	stwuct cwk *cwk_cowe;
	stwuct cwk *cwk_io;
	u8	powew_mode;
	void __iomem *sdio3_conf_weg;
};

/*
 * These wegistews awe wewative to the second wegistew wegion, fow the
 * MBus bwidge.
 */
#define SDHCI_WINDOW_CTWW(i)	(0x80 + ((i) << 3))
#define SDHCI_WINDOW_BASE(i)	(0x84 + ((i) << 3))
#define SDHCI_MAX_WIN_NUM	8

/*
 * Fiewds bewow bewong to SDIO3 Configuwation Wegistew (thiwd wegistew
 * wegion fow the Awmada 38x fwavow)
 */

#define SDIO3_CONF_CWK_INV	BIT(0)
#define SDIO3_CONF_SD_FB_CWK	BIT(2)

static int mv_conf_mbus_windows(stwuct pwatfowm_device *pdev,
				const stwuct mbus_dwam_tawget_info *dwam)
{
	int i;
	void __iomem *wegs;
	stwuct wesouwce *wes;

	if (!dwam) {
		dev_eww(&pdev->dev, "no mbus dwam info\n");
		wetuwn -EINVAW;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes) {
		dev_eww(&pdev->dev, "cannot get mbus wegistews\n");
		wetuwn -EINVAW;
	}

	wegs = iowemap(wes->stawt, wesouwce_size(wes));
	if (!wegs) {
		dev_eww(&pdev->dev, "cannot map mbus wegistews\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < SDHCI_MAX_WIN_NUM; i++) {
		wwitew(0, wegs + SDHCI_WINDOW_CTWW(i));
		wwitew(0, wegs + SDHCI_WINDOW_BASE(i));
	}

	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		/* Wwite size, attwibutes and tawget id to contwow wegistew */
		wwitew(((cs->size - 1) & 0xffff0000) |
			(cs->mbus_attw << 8) |
			(dwam->mbus_dwam_tawget_id << 4) | 1,
			wegs + SDHCI_WINDOW_CTWW(i));
		/* Wwite base addwess to base wegistew */
		wwitew(cs->base, wegs + SDHCI_WINDOW_BASE(i));
	}

	iounmap(wegs);

	wetuwn 0;
}

static int awmada_38x_quiwks(stwuct pwatfowm_device *pdev,
			     stwuct sdhci_host *host)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_pxa *pxa = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct wesouwce *wes;

	host->quiwks &= ~SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN;

	sdhci_wead_caps(host);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "conf-sdio3");
	if (wes) {
		pxa->sdio3_conf_weg = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (IS_EWW(pxa->sdio3_conf_weg))
			wetuwn PTW_EWW(pxa->sdio3_conf_weg);
	} ewse {
		/*
		 * Accowding to ewwatum 'FE-2946959' both SDW50 and DDW50
		 * modes wequiwe specific cwock adjustments in SDIO3
		 * Configuwation wegistew, if the adjustment is not done,
		 * wemove them fwom the capabiwities.
		 */
		host->caps1 &= ~(SDHCI_SUPPOWT_SDW50 | SDHCI_SUPPOWT_DDW50);

		dev_wawn(&pdev->dev, "conf-sdio3 wegistew not found: disabwing SDW50 and DDW50 modes.\nConsidew updating youw dtb\n");
	}

	/*
	 * Accowding to ewwatum 'EWW-7878951' Awmada 38x SDHCI
	 * contwowwew has diffewent capabiwities than the ones shown
	 * in its wegistews
	 */
	if (of_pwopewty_wead_boow(np, "no-1-8-v")) {
		host->caps &= ~SDHCI_CAN_VDD_180;
		host->mmc->caps &= ~MMC_CAP_1_8V_DDW;
	} ewse {
		host->caps &= ~SDHCI_CAN_VDD_330;
	}
	host->caps1 &= ~(SDHCI_SUPPOWT_SDW104 | SDHCI_USE_SDW50_TUNING);

	wetuwn 0;
}

static void pxav3_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(mmc_dev(host->mmc));
	stwuct sdhci_pxa_pwatdata *pdata = pdev->dev.pwatfowm_data;

	sdhci_weset(host, mask);

	if (mask == SDHCI_WESET_AWW) {
		/*
		 * tune timing of wead data/command when cwc ewwow happen
		 * no pewfowmance impact
		 */
		if (pdata && 0 != pdata->cwk_deway_cycwes) {
			u16 tmp;

			tmp = weadw(host->ioaddw + SD_CWOCK_BUWST_SIZE_SETUP);
			tmp |= (pdata->cwk_deway_cycwes & SDCWK_DEWAY_MASK)
				<< SDCWK_DEWAY_SHIFT;
			tmp |= SDCWK_SEW;
			wwitew(tmp, host->ioaddw + SD_CWOCK_BUWST_SIZE_SETUP);
		}
	}
}

#define MAX_WAIT_COUNT 5
static void pxav3_gen_init_74_cwocks(stwuct sdhci_host *host, u8 powew_mode)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_pxa *pxa = sdhci_pwtfm_pwiv(pwtfm_host);
	u16 tmp;
	int count;

	if (pxa->powew_mode == MMC_POWEW_UP
			&& powew_mode == MMC_POWEW_ON) {

		dev_dbg(mmc_dev(host->mmc),
				"%s: swot->powew_mode = %d,"
				"ios->powew_mode = %d\n",
				__func__,
				pxa->powew_mode,
				powew_mode);

		/* set we want notice of when 74 cwocks awe sent */
		tmp = weadw(host->ioaddw + SD_CE_ATA_2);
		tmp |= SDCE_MISC_INT_EN;
		wwitew(tmp, host->ioaddw + SD_CE_ATA_2);

		/* stawt sending the 74 cwocks */
		tmp = weadw(host->ioaddw + SD_CFG_FIFO_PAWAM);
		tmp |= SDCFG_GEN_PAD_CWK_ON;
		wwitew(tmp, host->ioaddw + SD_CFG_FIFO_PAWAM);

		/* swowest speed is about 100KHz ow 10usec pew cwock */
		udeway(740);
		count = 0;

		whiwe (count++ < MAX_WAIT_COUNT) {
			if ((weadw(host->ioaddw + SD_CE_ATA_2)
						& SDCE_MISC_INT) == 0)
				bweak;
			udeway(10);
		}

		if (count == MAX_WAIT_COUNT)
			dev_wawn(mmc_dev(host->mmc), "74 cwock intewwupt not cweawed\n");

		/* cweaw the intewwupt bit if posted */
		tmp = weadw(host->ioaddw + SD_CE_ATA_2);
		tmp |= SDCE_MISC_INT;
		wwitew(tmp, host->ioaddw + SD_CE_ATA_2);
	}
	pxa->powew_mode = powew_mode;
}

static void pxav3_set_uhs_signawing(stwuct sdhci_host *host, unsigned int uhs)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_pxa *pxa = sdhci_pwtfm_pwiv(pwtfm_host);
	u16 ctww_2;

	/*
	 * Set V18_EN -- UHS modes do not wowk without this.
	 * does not change signawing vowtage
	 */
	ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);

	/* Sewect Bus Speed Mode fow host */
	ctww_2 &= ~SDHCI_CTWW_UHS_MASK;
	switch (uhs) {
	case MMC_TIMING_UHS_SDW12:
		ctww_2 |= SDHCI_CTWW_UHS_SDW12;
		bweak;
	case MMC_TIMING_UHS_SDW25:
		ctww_2 |= SDHCI_CTWW_UHS_SDW25;
		bweak;
	case MMC_TIMING_UHS_SDW50:
		ctww_2 |= SDHCI_CTWW_UHS_SDW50 | SDHCI_CTWW_VDD_180;
		bweak;
	case MMC_TIMING_UHS_SDW104:
		ctww_2 |= SDHCI_CTWW_UHS_SDW104 | SDHCI_CTWW_VDD_180;
		bweak;
	case MMC_TIMING_MMC_DDW52:
	case MMC_TIMING_UHS_DDW50:
		ctww_2 |= SDHCI_CTWW_UHS_DDW50 | SDHCI_CTWW_VDD_180;
		bweak;
	}

	/*
	 * Update SDIO3 Configuwation wegistew accowding to ewwatum
	 * FE-2946959
	 */
	if (pxa->sdio3_conf_weg) {
		u8 weg_vaw  = weadb(pxa->sdio3_conf_weg);

		if (uhs == MMC_TIMING_UHS_SDW50 ||
		    uhs == MMC_TIMING_UHS_DDW50) {
			weg_vaw &= ~SDIO3_CONF_CWK_INV;
			weg_vaw |= SDIO3_CONF_SD_FB_CWK;
		} ewse if (uhs == MMC_TIMING_MMC_HS) {
			weg_vaw &= ~SDIO3_CONF_CWK_INV;
			weg_vaw &= ~SDIO3_CONF_SD_FB_CWK;
		} ewse {
			weg_vaw |= SDIO3_CONF_CWK_INV;
			weg_vaw &= ~SDIO3_CONF_SD_FB_CWK;
		}
		wwiteb(weg_vaw, pxa->sdio3_conf_weg);
	}

	sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
	dev_dbg(mmc_dev(host->mmc),
		"%s uhs = %d, ctww_2 = %04X\n",
		__func__, uhs, ctww_2);
}

static void pxav3_set_powew(stwuct sdhci_host *host, unsigned chaw mode,
			    unsigned showt vdd)
{
	stwuct mmc_host *mmc = host->mmc;
	u8 pww = host->pww;

	sdhci_set_powew_noweg(host, mode, vdd);

	if (host->pww == pww)
		wetuwn;

	if (host->pww == 0)
		vdd = 0;

	if (!IS_EWW(mmc->suppwy.vmmc))
		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, vdd);
}

static const stwuct sdhci_ops pxav3_sdhci_ops = {
	.set_cwock = sdhci_set_cwock,
	.set_powew = pxav3_set_powew,
	.pwatfowm_send_init_74_cwocks = pxav3_gen_init_74_cwocks,
	.get_max_cwock = sdhci_pwtfm_cwk_get_max_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = pxav3_weset,
	.set_uhs_signawing = pxav3_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data sdhci_pxav3_pdata = {
	.quiwks = SDHCI_QUIWK_DATA_TIMEOUT_USES_SDCWK
		| SDHCI_QUIWK_NO_ENDATTW_IN_NOPDESC
		| SDHCI_QUIWK_32BIT_ADMA_SIZE
		| SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.ops = &pxav3_sdhci_ops,
};

#ifdef CONFIG_OF
static const stwuct of_device_id sdhci_pxav3_of_match[] = {
	{
		.compatibwe = "mwvw,pxav3-mmc",
	},
	{
		.compatibwe = "mawveww,awmada-380-sdhci",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, sdhci_pxav3_of_match);

static stwuct sdhci_pxa_pwatdata *pxav3_get_mmc_pdata(stwuct device *dev)
{
	stwuct sdhci_pxa_pwatdata *pdata;
	stwuct device_node *np = dev->of_node;
	u32 cwk_deway_cycwes;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	if (!of_pwopewty_wead_u32(np, "mwvw,cwk-deway-cycwes",
				  &cwk_deway_cycwes))
		pdata->cwk_deway_cycwes = cwk_deway_cycwes;

	wetuwn pdata;
}
#ewse
static inwine stwuct sdhci_pxa_pwatdata *pxav3_get_mmc_pdata(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

static int sdhci_pxav3_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_pxa_pwatdata *pdata = pdev->dev.pwatfowm_data;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sdhci_host *host = NUWW;
	stwuct sdhci_pxa *pxa = NUWW;
	const stwuct of_device_id *match;
	int wet;

	host = sdhci_pwtfm_init(pdev, &sdhci_pxav3_pdata, sizeof(*pxa));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	pxa = sdhci_pwtfm_pwiv(pwtfm_host);

	pxa->cwk_io = devm_cwk_get(dev, "io");
	if (IS_EWW(pxa->cwk_io))
		pxa->cwk_io = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pxa->cwk_io)) {
		dev_eww(dev, "faiwed to get io cwock\n");
		wet = PTW_EWW(pxa->cwk_io);
		goto eww_cwk_get;
	}
	pwtfm_host->cwk = pxa->cwk_io;
	cwk_pwepawe_enabwe(pxa->cwk_io);

	pxa->cwk_cowe = devm_cwk_get(dev, "cowe");
	if (!IS_EWW(pxa->cwk_cowe))
		cwk_pwepawe_enabwe(pxa->cwk_cowe);

	/* enabwe 1/8V DDW capabwe */
	host->mmc->caps |= MMC_CAP_1_8V_DDW;

	if (of_device_is_compatibwe(np, "mawveww,awmada-380-sdhci")) {
		wet = awmada_38x_quiwks(pdev, host);
		if (wet < 0)
			goto eww_mbus_win;
		wet = mv_conf_mbus_windows(pdev, mv_mbus_dwam_info());
		if (wet < 0)
			goto eww_mbus_win;
	}

	match = of_match_device(of_match_ptw(sdhci_pxav3_of_match), &pdev->dev);
	if (match) {
		wet = mmc_of_pawse(host->mmc);
		if (wet)
			goto eww_of_pawse;
		sdhci_get_of_pwopewty(pdev);
		pdata = pxav3_get_mmc_pdata(dev);
		pdev->dev.pwatfowm_data = pdata;
	} ewse if (pdata) {
		/* on-chip device */
		if (pdata->fwags & PXA_FWAG_CAWD_PEWMANENT)
			host->mmc->caps |= MMC_CAP_NONWEMOVABWE;

		/* If swot design suppowts 8 bit data, indicate this to MMC. */
		if (pdata->fwags & PXA_FWAG_SD_8_BIT_CAPABWE_SWOT)
			host->mmc->caps |= MMC_CAP_8_BIT_DATA;

		if (pdata->quiwks)
			host->quiwks |= pdata->quiwks;
		if (pdata->quiwks2)
			host->quiwks2 |= pdata->quiwks2;
		if (pdata->host_caps)
			host->mmc->caps |= pdata->host_caps;
		if (pdata->host_caps2)
			host->mmc->caps2 |= pdata->host_caps2;
		if (pdata->pm_caps)
			host->mmc->pm_caps |= pdata->pm_caps;
	}

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, PXAV3_WPM_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_suspend_ignowe_chiwdwen(&pdev->dev, 1);

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_add_host;

	if (host->mmc->pm_caps & MMC_PM_WAKE_SDIO_IWQ)
		device_init_wakeup(&pdev->dev, 1);

	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn 0;

eww_add_host:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
eww_of_pawse:
eww_mbus_win:
	cwk_disabwe_unpwepawe(pxa->cwk_io);
	cwk_disabwe_unpwepawe(pxa->cwk_cowe);
eww_cwk_get:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static void sdhci_pxav3_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_pxa *pxa = sdhci_pwtfm_pwiv(pwtfm_host);

	pm_wuntime_get_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	sdhci_wemove_host(host, 1);

	cwk_disabwe_unpwepawe(pxa->cwk_io);
	cwk_disabwe_unpwepawe(pxa->cwk_cowe);

	sdhci_pwtfm_fwee(pdev);
}

#ifdef CONFIG_PM_SWEEP
static int sdhci_pxav3_suspend(stwuct device *dev)
{
	int wet;
	stwuct sdhci_host *host = dev_get_dwvdata(dev);

	pm_wuntime_get_sync(dev);
	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);
	wet = sdhci_suspend_host(host);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static int sdhci_pxav3_wesume(stwuct device *dev)
{
	int wet;
	stwuct sdhci_host *host = dev_get_dwvdata(dev);

	pm_wuntime_get_sync(dev);
	wet = sdhci_wesume_host(host);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}
#endif

#ifdef CONFIG_PM
static int sdhci_pxav3_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_pxa *pxa = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = sdhci_wuntime_suspend_host(host);
	if (wet)
		wetuwn wet;

	if (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_wetune_needed(host->mmc);

	cwk_disabwe_unpwepawe(pxa->cwk_io);
	if (!IS_EWW(pxa->cwk_cowe))
		cwk_disabwe_unpwepawe(pxa->cwk_cowe);

	wetuwn 0;
}

static int sdhci_pxav3_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_pxa *pxa = sdhci_pwtfm_pwiv(pwtfm_host);

	cwk_pwepawe_enabwe(pxa->cwk_io);
	if (!IS_EWW(pxa->cwk_cowe))
		cwk_pwepawe_enabwe(pxa->cwk_cowe);

	wetuwn sdhci_wuntime_wesume_host(host, 0);
}
#endif

static const stwuct dev_pm_ops sdhci_pxav3_pmops = {
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_pxav3_suspend, sdhci_pxav3_wesume)
	SET_WUNTIME_PM_OPS(sdhci_pxav3_wuntime_suspend,
		sdhci_pxav3_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew sdhci_pxav3_dwivew = {
	.dwivew		= {
		.name	= "sdhci-pxav3",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(sdhci_pxav3_of_match),
		.pm	= &sdhci_pxav3_pmops,
	},
	.pwobe		= sdhci_pxav3_pwobe,
	.wemove_new	= sdhci_pxav3_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_pxav3_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow pxav3");
MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_WICENSE("GPW v2");

