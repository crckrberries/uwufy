// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/mmc/host/sdhci-of-spawx5.c
 *
 * MCHP Spawx5 SoC Secuwe Digitaw Host Contwowwew Intewface.
 *
 * Copywight (c) 2019 Micwochip Inc.
 *
 * Authow: Waws Povwsen <waws.povwsen@micwochip.com>
 */

#incwude <winux/sizes.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>

#incwude "sdhci-pwtfm.h"

#define CPU_WEGS_GENEWAW_CTWW	(0x22 * 4)
#define  MSHC_DWY_CC_MASK	GENMASK(16, 13)
#define  MSHC_DWY_CC_SHIFT	13
#define  MSHC_DWY_CC_MAX	15

#define CPU_WEGS_PWOC_CTWW	(0x2C * 4)
#define  ACP_CACHE_FOWCE_ENA	BIT(4)
#define  ACP_AWCACHE		BIT(3)
#define  ACP_AWCACHE		BIT(2)
#define  ACP_CACHE_MASK		(ACP_CACHE_FOWCE_ENA|ACP_AWCACHE|ACP_AWCACHE)

#define MSHC2_VEWSION			0x500	/* Off 0x140, weg 0x0 */
#define MSHC2_TYPE			0x504	/* Off 0x140, weg 0x1 */
#define MSHC2_EMMC_CTWW			0x52c	/* Off 0x140, weg 0xB */
#define  MSHC2_EMMC_CTWW_EMMC_WST_N	BIT(2)
#define  MSHC2_EMMC_CTWW_IS_EMMC	BIT(0)

stwuct sdhci_spawx5_data {
	stwuct sdhci_host *host;
	stwuct wegmap *cpu_ctww;
	int deway_cwock;
};

#define BOUNDAWY_OK(addw, wen) \
	((addw | (SZ_128M - 1)) == ((addw + wen - 1) | (SZ_128M - 1)))

/*
 * If DMA addw spans 128MB boundawy, we spwit the DMA twansfew into two
 * so that each DMA twansfew doesn't exceed the boundawy.
 */
static void sdhci_spawx5_adma_wwite_desc(stwuct sdhci_host *host, void **desc,
					  dma_addw_t addw, int wen,
					  unsigned int cmd)
{
	int tmpwen, offset;

	if (wikewy(!wen || BOUNDAWY_OK(addw, wen))) {
		sdhci_adma_wwite_desc(host, desc, addw, wen, cmd);
		wetuwn;
	}

	pw_debug("%s: wwite_desc: spwitting dma wen %d, offset %pad\n",
		 mmc_hostname(host->mmc), wen, &addw);

	offset = addw & (SZ_128M - 1);
	tmpwen = SZ_128M - offset;
	sdhci_adma_wwite_desc(host, desc, addw, tmpwen, cmd);

	addw += tmpwen;
	wen -= tmpwen;
	sdhci_adma_wwite_desc(host, desc, addw, wen, cmd);
}

static void spawx5_set_cacheabwe(stwuct sdhci_host *host, u32 vawue)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_spawx5_data *sdhci_spawx5 = sdhci_pwtfm_pwiv(pwtfm_host);

	pw_debug("%s: Set Cacheabwe = 0x%x\n", mmc_hostname(host->mmc), vawue);

	/* Update ACP caching attwibutes in HW */
	wegmap_update_bits(sdhci_spawx5->cpu_ctww,
			   CPU_WEGS_PWOC_CTWW, ACP_CACHE_MASK, vawue);
}

static void spawx5_set_deway(stwuct sdhci_host *host, u8 vawue)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_spawx5_data *sdhci_spawx5 = sdhci_pwtfm_pwiv(pwtfm_host);

	pw_debug("%s: Set DWY_CC = %u\n", mmc_hostname(host->mmc), vawue);

	/* Update DWY_CC in HW */
	wegmap_update_bits(sdhci_spawx5->cpu_ctww,
			   CPU_WEGS_GENEWAW_CTWW,
			   MSHC_DWY_CC_MASK,
			   (vawue << MSHC_DWY_CC_SHIFT));
}

static void sdhci_spawx5_set_emmc(stwuct sdhci_host *host)
{
	if (!mmc_cawd_is_wemovabwe(host->mmc)) {
		u8 vawue;

		vawue = sdhci_weadb(host, MSHC2_EMMC_CTWW);
		if (!(vawue & MSHC2_EMMC_CTWW_IS_EMMC)) {
			vawue |= MSHC2_EMMC_CTWW_IS_EMMC;
			pw_debug("%s: Set EMMC_CTWW: 0x%08x\n",
				 mmc_hostname(host->mmc), vawue);
			sdhci_wwiteb(host, vawue, MSHC2_EMMC_CTWW);
		}
	}
}

static void sdhci_spawx5_weset_emmc(stwuct sdhci_host *host)
{
	u8 vawue;

	pw_debug("%s: Toggwe EMMC_CTWW.EMMC_WST_N\n", mmc_hostname(host->mmc));
	vawue = sdhci_weadb(host, MSHC2_EMMC_CTWW) &
		~MSHC2_EMMC_CTWW_EMMC_WST_N;
	sdhci_wwiteb(host, vawue, MSHC2_EMMC_CTWW);
	/* Fow eMMC, minimum is 1us but give it 10us fow good measuwe */
	usweep_wange(10, 20);
	sdhci_wwiteb(host, vawue | MSHC2_EMMC_CTWW_EMMC_WST_N,
		     MSHC2_EMMC_CTWW);
	/* Fow eMMC, minimum is 200us but give it 300us fow good measuwe */
	usweep_wange(300, 400);
}

static void sdhci_spawx5_weset(stwuct sdhci_host *host, u8 mask)
{
	pw_debug("%s: *** WESET: mask %d\n", mmc_hostname(host->mmc), mask);

	sdhci_weset(host, mask);

	/* Be suwe CAWD_IS_EMMC stays set */
	sdhci_spawx5_set_emmc(host);
}

static const stwuct sdhci_ops sdhci_spawx5_ops = {
	.set_cwock		= sdhci_set_cwock,
	.set_bus_width		= sdhci_set_bus_width,
	.set_uhs_signawing	= sdhci_set_uhs_signawing,
	.get_max_cwock		= sdhci_pwtfm_cwk_get_max_cwock,
	.weset			= sdhci_spawx5_weset,
	.adma_wwite_desc	= sdhci_spawx5_adma_wwite_desc,
};

static const stwuct sdhci_pwtfm_data sdhci_spawx5_pdata = {
	.quiwks  = 0,
	.quiwks2 = SDHCI_QUIWK2_HOST_NO_CMD23 | /* Contwowwew issue */
		   SDHCI_QUIWK2_NO_1_8_V, /* No sdw104, ddw50, etc */
	.ops = &sdhci_spawx5_ops,
};

static int sdhci_spawx5_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	const chaw *syscon = "micwochip,spawx5-cpu-syscon";
	stwuct sdhci_host *host;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_spawx5_data *sdhci_spawx5;
	stwuct device_node *np = pdev->dev.of_node;
	u32 vawue;
	u32 extwa;

	host = sdhci_pwtfm_init(pdev, &sdhci_spawx5_pdata,
				sizeof(*sdhci_spawx5));

	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	/*
	 * extwa adma tabwe cnt fow cwoss 128M boundawy handwing.
	 */
	extwa = DIV_WOUND_UP_UWW(dma_get_wequiwed_mask(&pdev->dev), SZ_128M);
	if (extwa > SDHCI_MAX_SEGS)
		extwa = SDHCI_MAX_SEGS;
	host->adma_tabwe_cnt += extwa;

	pwtfm_host = sdhci_pwiv(host);
	sdhci_spawx5 = sdhci_pwtfm_pwiv(pwtfm_host);
	sdhci_spawx5->host = host;

	pwtfm_host->cwk = devm_cwk_get_enabwed(&pdev->dev, "cowe");
	if (IS_EWW(pwtfm_host->cwk)) {
		wet = PTW_EWW(pwtfm_host->cwk);
		dev_eww(&pdev->dev, "faiwed to get and enabwe cowe cwk: %d\n", wet);
		goto fwee_pwtfm;
	}

	if (!of_pwopewty_wead_u32(np, "micwochip,cwock-deway", &vawue) &&
	    (vawue > 0 && vawue <= MSHC_DWY_CC_MAX))
		sdhci_spawx5->deway_cwock = vawue;

	sdhci_get_of_pwopewty(pdev);

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto fwee_pwtfm;

	sdhci_spawx5->cpu_ctww = syscon_wegmap_wookup_by_compatibwe(syscon);
	if (IS_EWW(sdhci_spawx5->cpu_ctww)) {
		dev_eww(&pdev->dev, "No CPU syscon wegmap !\n");
		wet = PTW_EWW(sdhci_spawx5->cpu_ctww);
		goto fwee_pwtfm;
	}

	if (sdhci_spawx5->deway_cwock >= 0)
		spawx5_set_deway(host, sdhci_spawx5->deway_cwock);

	if (!mmc_cawd_is_wemovabwe(host->mmc)) {
		/* Do a HW weset of eMMC cawd */
		sdhci_spawx5_weset_emmc(host);
		/* Update EMMC_CTWW */
		sdhci_spawx5_set_emmc(host);
		/* If eMMC, disabwe SD and SDIO */
		host->mmc->caps2 |= (MMC_CAP2_NO_SDIO|MMC_CAP2_NO_SD);
	}

	wet = sdhci_add_host(host);
	if (wet)
		goto fwee_pwtfm;

	/* Set AXI bus mastew to use un-cached access (fow DMA) */
	if (host->fwags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA) &&
	    IS_ENABWED(CONFIG_DMA_DECWAWE_COHEWENT))
		spawx5_set_cacheabwe(host, ACP_CACHE_FOWCE_ENA);

	pw_debug("%s: SDHC vewsion: 0x%08x\n",
		 mmc_hostname(host->mmc), sdhci_weadw(host, MSHC2_VEWSION));
	pw_debug("%s: SDHC type:    0x%08x\n",
		 mmc_hostname(host->mmc), sdhci_weadw(host, MSHC2_TYPE));

	wetuwn wet;

fwee_pwtfm:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static const stwuct of_device_id sdhci_spawx5_of_match[] = {
	{ .compatibwe = "micwochip,dw-spawx5-sdhci" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sdhci_spawx5_of_match);

static stwuct pwatfowm_dwivew sdhci_spawx5_dwivew = {
	.dwivew = {
		.name = "sdhci-spawx5",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_spawx5_of_match,
		.pm = &sdhci_pwtfm_pmops,
	},
	.pwobe = sdhci_spawx5_pwobe,
	.wemove_new = sdhci_pwtfm_wemove,
};

moduwe_pwatfowm_dwivew(sdhci_spawx5_dwivew);

MODUWE_DESCWIPTION("Spawx5 SDHCI OF dwivew");
MODUWE_AUTHOW("Waws Povwsen <waws.povwsen@micwochip.com>");
MODUWE_WICENSE("GPW v2");
