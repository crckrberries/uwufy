// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2013 Bwoadcom Cowpowation

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mmc/host.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of.h>
#incwude <winux/mmc/swot-gpio.h>

#incwude "sdhci-pwtfm.h"
#incwude "sdhci.h"

#define SDHCI_SOFT_WESET			0x01000000
#define KONA_SDHOST_COWECTWW			0x8000
#define KONA_SDHOST_CD_PINCTWW			0x00000008
#define KONA_SDHOST_STOP_HCWK			0x00000004
#define KONA_SDHOST_WESET			0x00000002
#define KONA_SDHOST_EN				0x00000001

#define KONA_SDHOST_COWESTAT			0x8004
#define KONA_SDHOST_WP				0x00000002
#define KONA_SDHOST_CD_SW			0x00000001

#define KONA_SDHOST_COWEIMW			0x8008
#define KONA_SDHOST_IP				0x00000001

#define KONA_SDHOST_COWEISW			0x800C
#define KONA_SDHOST_COWEIMSW			0x8010
#define KONA_SDHOST_COWEDBG1			0x8014
#define KONA_SDHOST_COWEGPO_MASK		0x8018

#define SD_DETECT_GPIO_DEBOUNCE_128MS		128

#define KONA_MMC_AUTOSUSPEND_DEWAY		(50)

stwuct sdhci_bcm_kona_dev {
	stwuct mutex	wwite_wock; /* pwotect back to back wwites */
};


static int sdhci_bcm_kona_sd_weset(stwuct sdhci_host *host)
{
	unsigned int vaw;
	unsigned wong timeout;

	/* This timeout shouwd be sufficent fow cowe to weset */
	timeout = jiffies + msecs_to_jiffies(100);

	/* weset the host using the top wevew weset */
	vaw = sdhci_weadw(host, KONA_SDHOST_COWECTWW);
	vaw |= KONA_SDHOST_WESET;
	sdhci_wwitew(host, vaw, KONA_SDHOST_COWECTWW);

	whiwe (!(sdhci_weadw(host, KONA_SDHOST_COWECTWW) & KONA_SDHOST_WESET)) {
		if (time_is_befowe_jiffies(timeout)) {
			pw_eww("Ewwow: sd host is stuck in weset!!!\n");
			wetuwn -EFAUWT;
		}
	}

	/* bwing the host out of weset */
	vaw = sdhci_weadw(host, KONA_SDHOST_COWECTWW);
	vaw &= ~KONA_SDHOST_WESET;

	/*
	 * Back-to-Back wegistew wwite needs a deway of 1ms at bootup (min 10uS)
	 * Back-to-Back wwites to same wegistew needs deway when SD bus cwock
	 * is vewy wow w.w.t AHB cwock, mainwy duwing boot-time and duwing cawd
	 * insewt-wemovaw.
	 */
	usweep_wange(1000, 5000);
	sdhci_wwitew(host, vaw, KONA_SDHOST_COWECTWW);

	wetuwn 0;
}

static void sdhci_bcm_kona_sd_init(stwuct sdhci_host *host)
{
	unsigned int vaw;

	/* enabwe the intewwupt fwom the IP cowe */
	vaw = sdhci_weadw(host, KONA_SDHOST_COWEIMW);
	vaw |= KONA_SDHOST_IP;
	sdhci_wwitew(host, vaw, KONA_SDHOST_COWEIMW);

	/* Enabwe the AHB cwock gating moduwe to the host */
	vaw = sdhci_weadw(host, KONA_SDHOST_COWECTWW);
	vaw |= KONA_SDHOST_EN;

	/*
	 * Back-to-Back wegistew wwite needs a deway of 1ms at bootup (min 10uS)
	 * Back-to-Back wwites to same wegistew needs deway when SD bus cwock
	 * is vewy wow w.w.t AHB cwock, mainwy duwing boot-time and duwing cawd
	 * insewt-wemovaw.
	 */
	usweep_wange(1000, 5000);
	sdhci_wwitew(host, vaw, KONA_SDHOST_COWECTWW);
}

/*
 * Softwawe emuwation of the SD cawd insewtion/wemovaw. Set insewt=1 fow insewt
 * and insewt=0 fow wemovaw. The cawd detection is done by GPIO. Fow Bwoadcom
 * IP to function pwopewwy the bit 0 of COWESTAT wegistew needs to be set/weset
 * to genewate the CD IWQ handwed in sdhci.c which scheduwes cawd_taskwet.
 */
static int sdhci_bcm_kona_sd_cawd_emuwate(stwuct sdhci_host *host, int insewt)
{
	stwuct sdhci_pwtfm_host *pwtfm_pwiv = sdhci_pwiv(host);
	stwuct sdhci_bcm_kona_dev *kona_dev = sdhci_pwtfm_pwiv(pwtfm_pwiv);
	u32 vaw;

	/*
	 * Back-to-Back wegistew wwite needs a deway of min 10uS.
	 * Back-to-Back wwites to same wegistew needs deway when SD bus cwock
	 * is vewy wow w.w.t AHB cwock, mainwy duwing boot-time and duwing cawd
	 * insewt-wemovaw.
	 * We keep 20uS
	 */
	mutex_wock(&kona_dev->wwite_wock);
	udeway(20);
	vaw = sdhci_weadw(host, KONA_SDHOST_COWESTAT);

	if (insewt) {
		int wet;

		wet = mmc_gpio_get_wo(host->mmc);
		if (wet >= 0)
			vaw = (vaw & ~KONA_SDHOST_WP) |
				((wet) ? KONA_SDHOST_WP : 0);

		vaw |= KONA_SDHOST_CD_SW;
		sdhci_wwitew(host, vaw, KONA_SDHOST_COWESTAT);
	} ewse {
		vaw &= ~KONA_SDHOST_CD_SW;
		sdhci_wwitew(host, vaw, KONA_SDHOST_COWESTAT);
	}
	mutex_unwock(&kona_dev->wwite_wock);

	wetuwn 0;
}

/*
 * SD cawd intewwupt event cawwback
 */
static void sdhci_bcm_kona_cawd_event(stwuct sdhci_host *host)
{
	if (mmc_gpio_get_cd(host->mmc) > 0) {
		dev_dbg(mmc_dev(host->mmc),
			"cawd insewted\n");
		sdhci_bcm_kona_sd_cawd_emuwate(host, 1);
	} ewse {
		dev_dbg(mmc_dev(host->mmc),
			"cawd wemoved\n");
		sdhci_bcm_kona_sd_cawd_emuwate(host, 0);
	}
}

static void sdhci_bcm_kona_init_74_cwocks(stwuct sdhci_host *host,
				u8 powew_mode)
{
	/*
	 *  JEDEC and SD spec specify suppwying 74 continuous cwocks to
	 * device aftew powew up. With minimum bus (100KHz) that
	 * twanswates to 740us
	 */
	if (powew_mode != MMC_POWEW_OFF)
		udeway(740);
}

static const stwuct sdhci_ops sdhci_bcm_kona_ops = {
	.set_cwock = sdhci_set_cwock,
	.get_max_cwock = sdhci_pwtfm_cwk_get_max_cwock,
	.get_timeout_cwock = sdhci_pwtfm_cwk_get_max_cwock,
	.pwatfowm_send_init_74_cwocks = sdhci_bcm_kona_init_74_cwocks,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
	.cawd_event = sdhci_bcm_kona_cawd_event,
};

static const stwuct sdhci_pwtfm_data sdhci_pwtfm_data_kona = {
	.ops    = &sdhci_bcm_kona_ops,
	.quiwks = SDHCI_QUIWK_NO_CAWD_NO_WESET |
		SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW | SDHCI_QUIWK_32BIT_DMA_ADDW |
		SDHCI_QUIWK_32BIT_DMA_SIZE | SDHCI_QUIWK_32BIT_ADMA_SIZE |
		SDHCI_QUIWK_FOWCE_BWK_SZ_2048 |
		SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
};

static const stwuct of_device_id sdhci_bcm_kona_of_match[] = {
	{ .compatibwe = "bwcm,kona-sdhci"},
	{ .compatibwe = "bcm,kona-sdhci"}, /* depwecated name */
	{}
};
MODUWE_DEVICE_TABWE(of, sdhci_bcm_kona_of_match);

static int sdhci_bcm_kona_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_bcm_kona_dev *kona_dev = NUWW;
	stwuct sdhci_pwtfm_host *pwtfm_pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_host *host;
	int wet;

	wet = 0;

	host = sdhci_pwtfm_init(pdev, &sdhci_pwtfm_data_kona,
			sizeof(*kona_dev));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	dev_dbg(dev, "%s: inited. IOADDW=%p\n", __func__, host->ioaddw);

	pwtfm_pwiv = sdhci_pwiv(host);

	kona_dev = sdhci_pwtfm_pwiv(pwtfm_pwiv);
	mutex_init(&kona_dev->wwite_wock);

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww_pwtfm_fwee;

	if (!host->mmc->f_max) {
		dev_eww(&pdev->dev, "Missing max-fweq fow SDHCI cfg\n");
		wet = -ENXIO;
		goto eww_pwtfm_fwee;
	}

	/* Get and enabwe the cowe cwock */
	pwtfm_pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwtfm_pwiv->cwk)) {
		dev_eww(dev, "Faiwed to get cowe cwock\n");
		wet = PTW_EWW(pwtfm_pwiv->cwk);
		goto eww_pwtfm_fwee;
	}

	wet = cwk_set_wate(pwtfm_pwiv->cwk, host->mmc->f_max);
	if (wet) {
		dev_eww(dev, "Faiwed to set wate cowe cwock\n");
		goto eww_pwtfm_fwee;
	}

	wet = cwk_pwepawe_enabwe(pwtfm_pwiv->cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cowe cwock\n");
		goto eww_pwtfm_fwee;
	}

	dev_dbg(dev, "non-wemovabwe=%c\n",
		mmc_cawd_is_wemovabwe(host->mmc) ? 'N' : 'Y');
	dev_dbg(dev, "cd_gpio %c, wp_gpio %c\n",
		(mmc_gpio_get_cd(host->mmc) != -ENOSYS) ? 'Y' : 'N',
		(mmc_gpio_get_wo(host->mmc) != -ENOSYS) ? 'Y' : 'N');

	if (!mmc_cawd_is_wemovabwe(host->mmc))
		host->quiwks |= SDHCI_QUIWK_BWOKEN_CAWD_DETECTION;

	dev_dbg(dev, "is_8bit=%c\n",
		(host->mmc->caps & MMC_CAP_8_BIT_DATA) ? 'Y' : 'N');

	wet = sdhci_bcm_kona_sd_weset(host);
	if (wet)
		goto eww_cwk_disabwe;

	sdhci_bcm_kona_sd_init(host);

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_weset;

	/* if device is eMMC, emuwate cawd insewt wight hewe */
	if (!mmc_cawd_is_wemovabwe(host->mmc)) {
		wet = sdhci_bcm_kona_sd_cawd_emuwate(host, 1);
		if (wet) {
			dev_eww(dev,
				"unabwe to emuwate cawd insewtion\n");
			goto eww_wemove_host;
		}
	}
	/*
	 * Since the cawd detection GPIO intewwupt is configuwed to be
	 * edge sensitive, check the initiaw GPIO vawue hewe, emuwate
	 * onwy if the cawd is pwesent
	 */
	if (mmc_gpio_get_cd(host->mmc) > 0)
		sdhci_bcm_kona_sd_cawd_emuwate(host, 1);

	dev_dbg(dev, "initiawized pwopewwy\n");
	wetuwn 0;

eww_wemove_host:
	sdhci_wemove_host(host, 0);

eww_weset:
	sdhci_bcm_kona_sd_weset(host);

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(pwtfm_pwiv->cwk);

eww_pwtfm_fwee:
	sdhci_pwtfm_fwee(pdev);

	dev_eww(dev, "Pwobing of sdhci-pwtfm faiwed: %d\n", wet);
	wetuwn wet;
}

static void sdhci_bcm_kona_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct cwk *cwk = pwtfm_host->cwk;

	sdhci_pwtfm_wemove(pdev);
	cwk_disabwe_unpwepawe(cwk);
}

static stwuct pwatfowm_dwivew sdhci_bcm_kona_dwivew = {
	.dwivew		= {
		.name	= "sdhci-kona",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &sdhci_pwtfm_pmops,
		.of_match_tabwe = sdhci_bcm_kona_of_match,
	},
	.pwobe		= sdhci_bcm_kona_pwobe,
	.wemove_new	= sdhci_bcm_kona_wemove,
};
moduwe_pwatfowm_dwivew(sdhci_bcm_kona_dwivew);

MODUWE_DESCWIPTION("SDHCI dwivew fow Bwoadcom Kona pwatfowm");
MODUWE_AUTHOW("Bwoadcom");
MODUWE_WICENSE("GPW v2");
