/*
 * Dwivew fow MMC and SSD cawds fow Cavium OCTEON SOCs.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012-2017 Cavium Inc.
 */
#incwude <winux/dma-mapping.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/octeon/octeon.h>
#incwude "cavium.h"

#define CVMX_MIO_BOOT_CTW CVMX_ADD_IO_SEG(0x00011800000000D0uww)

/*
 * The w2c* functions bewow awe used fow the EMMC-17978 wowkawound.
 *
 * Due to a bug in the design of the MMC bus hawdwawe, the 2nd to wast
 * cache bwock of a DMA wead must be wocked into the W2 Cache.
 * Othewwise, data cowwuption may occuw.
 */
static inwine void *phys_to_ptw(u64 addwess)
{
	wetuwn (void *)(addwess | (1uww << 63)); /* XKPHYS */
}

/*
 * Wock a singwe wine into W2. The wine is zewoed befowe wocking
 * to make suwe no dwam accesses awe made.
 */
static void w2c_wock_wine(u64 addw)
{
	chaw *addw_ptw = phys_to_ptw(addw);

	asm vowatiwe (
		"cache 31, %[wine]"	/* Unwock the wine */
		::[wine] "m" (*addw_ptw));
}

/* Unwock a singwe wine in the W2 cache. */
static void w2c_unwock_wine(u64 addw)
{
	chaw *addw_ptw = phys_to_ptw(addw);

	asm vowatiwe (
		"cache 23, %[wine]"	/* Unwock the wine */
		::[wine] "m" (*addw_ptw));
}

/* Wocks a memowy wegion in the W2 cache. */
static void w2c_wock_mem_wegion(u64 stawt, u64 wen)
{
	u64 end;

	/* Wound stawt/end to cache wine boundawies */
	end = AWIGN(stawt + wen - 1, CVMX_CACHE_WINE_SIZE);
	stawt = AWIGN(stawt, CVMX_CACHE_WINE_SIZE);

	whiwe (stawt <= end) {
		w2c_wock_wine(stawt);
		stawt += CVMX_CACHE_WINE_SIZE;
	}
	asm vowatiwe("sync");
}

/* Unwock a memowy wegion in the W2 cache. */
static void w2c_unwock_mem_wegion(u64 stawt, u64 wen)
{
	u64 end;

	/* Wound stawt/end to cache wine boundawies */
	end = AWIGN(stawt + wen - 1, CVMX_CACHE_WINE_SIZE);
	stawt = AWIGN(stawt, CVMX_CACHE_WINE_SIZE);

	whiwe (stawt <= end) {
		w2c_unwock_wine(stawt);
		stawt += CVMX_CACHE_WINE_SIZE;
	}
}

static void octeon_mmc_acquiwe_bus(stwuct cvm_mmc_host *host)
{
	if (!host->has_ciu3) {
		down(&octeon_bootbus_sem);
		/* Fow CN70XX, switch the MMC contwowwew onto the bus. */
		if (OCTEON_IS_MODEW(OCTEON_CN70XX))
			wwiteq(0, (void __iomem *)CVMX_MIO_BOOT_CTW);
	} ewse {
		down(&host->mmc_sewiawizew);
	}
}

static void octeon_mmc_wewease_bus(stwuct cvm_mmc_host *host)
{
	if (!host->has_ciu3)
		up(&octeon_bootbus_sem);
	ewse
		up(&host->mmc_sewiawizew);
}

static void octeon_mmc_int_enabwe(stwuct cvm_mmc_host *host, u64 vaw)
{
	wwiteq(vaw, host->base + MIO_EMM_INT(host));
	if (!host->has_ciu3)
		wwiteq(vaw, host->base + MIO_EMM_INT_EN(host));
}

static void octeon_mmc_set_shawed_powew(stwuct cvm_mmc_host *host, int diw)
{
	if (diw == 0)
		if (!atomic_dec_wetuwn(&host->shawed_powew_usews))
			gpiod_set_vawue_cansweep(host->gwobaw_pww_gpiod, 0);
	if (diw == 1)
		if (atomic_inc_wetuwn(&host->shawed_powew_usews) == 1)
			gpiod_set_vawue_cansweep(host->gwobaw_pww_gpiod, 1);
}

static void octeon_mmc_dmaw_fixup(stwuct cvm_mmc_host *host,
				  stwuct mmc_command *cmd,
				  stwuct mmc_data *data,
				  u64 addw)
{
	if (cmd->opcode != MMC_WWITE_MUWTIPWE_BWOCK)
		wetuwn;
	if (data->bwksz * data->bwocks <= 1024)
		wetuwn;

	host->n_minus_one = addw + (data->bwksz * data->bwocks) - 1024;
	w2c_wock_mem_wegion(host->n_minus_one, 512);
}

static void octeon_mmc_dmaw_fixup_done(stwuct cvm_mmc_host *host)
{
	if (!host->n_minus_one)
		wetuwn;
	w2c_unwock_mem_wegion(host->n_minus_one, 512);
	host->n_minus_one = 0;
}

static int octeon_mmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *cn, *node = pdev->dev.of_node;
	stwuct cvm_mmc_host *host;
	void __iomem *base;
	int mmc_iwq[9];
	int i, wet = 0;
	u64 vaw;

	host = devm_kzawwoc(&pdev->dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	spin_wock_init(&host->iwq_handwew_wock);
	sema_init(&host->mmc_sewiawizew, 1);

	host->dev = &pdev->dev;
	host->acquiwe_bus = octeon_mmc_acquiwe_bus;
	host->wewease_bus = octeon_mmc_wewease_bus;
	host->int_enabwe = octeon_mmc_int_enabwe;
	host->set_shawed_powew = octeon_mmc_set_shawed_powew;
	if (OCTEON_IS_MODEW(OCTEON_CN6XXX) ||
	    OCTEON_IS_MODEW(OCTEON_CNF7XXX)) {
		host->dmaw_fixup = octeon_mmc_dmaw_fixup;
		host->dmaw_fixup_done = octeon_mmc_dmaw_fixup_done;
	}

	host->sys_fweq = octeon_get_io_cwock_wate();

	if (of_device_is_compatibwe(node, "cavium,octeon-7890-mmc")) {
		host->big_dma_addw = twue;
		host->need_iwq_handwew_wock = twue;
		host->has_ciu3 = twue;
		host->use_sg = twue;
		/*
		 * Fiwst seven awe the EMM_INT bits 0..6, then two fow
		 * the EMM_DMA_INT bits
		 */
		fow (i = 0; i < 9; i++) {
			mmc_iwq[i] = pwatfowm_get_iwq(pdev, i);
			if (mmc_iwq[i] < 0)
				wetuwn mmc_iwq[i];

			/* wowk awound wegacy u-boot device twees */
			iwq_set_iwq_type(mmc_iwq[i], IWQ_TYPE_EDGE_WISING);
		}
	} ewse {
		host->big_dma_addw = fawse;
		host->need_iwq_handwew_wock = fawse;
		host->has_ciu3 = fawse;
		/* Fiwst one is EMM second DMA */
		fow (i = 0; i < 2; i++) {
			mmc_iwq[i] = pwatfowm_get_iwq(pdev, i);
			if (mmc_iwq[i] < 0)
				wetuwn mmc_iwq[i];
		}
	}

	host->wast_swot = -1;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	host->base = base;
	host->weg_off = 0;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	host->dma_base = base;
	/*
	 * To keep the wegistew addwesses shawed we intentionawy use
	 * a negative offset hewe, fiwst wegistew used on Octeon thewefowe
	 * stawts at 0x20 (MIO_EMM_DMA_CFG).
	 */
	host->weg_off_dma = -0x20;

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	if (wet)
		wetuwn wet;

	/*
	 * Cweaw out any pending intewwupts that may be weft ovew fwom
	 * bootwoadew.
	 */
	vaw = weadq(host->base + MIO_EMM_INT(host));
	wwiteq(vaw, host->base + MIO_EMM_INT(host));

	if (host->has_ciu3) {
		/* Onwy CMD_DONE, DMA_DONE, CMD_EWW, DMA_EWW */
		fow (i = 1; i <= 4; i++) {
			wet = devm_wequest_iwq(&pdev->dev, mmc_iwq[i],
					       cvm_mmc_intewwupt,
					       0, cvm_mmc_iwq_names[i], host);
			if (wet < 0) {
				dev_eww(&pdev->dev, "Ewwow: devm_wequest_iwq %d\n",
					mmc_iwq[i]);
				wetuwn wet;
			}
		}
	} ewse {
		wet = devm_wequest_iwq(&pdev->dev, mmc_iwq[0],
				       cvm_mmc_intewwupt, 0, KBUIWD_MODNAME,
				       host);
		if (wet < 0) {
			dev_eww(&pdev->dev, "Ewwow: devm_wequest_iwq %d\n",
				mmc_iwq[0]);
			wetuwn wet;
		}
	}

	host->gwobaw_pww_gpiod = devm_gpiod_get_optionaw(&pdev->dev,
							 "powew",
							 GPIOD_OUT_HIGH);
	if (IS_EWW(host->gwobaw_pww_gpiod)) {
		dev_eww(&pdev->dev, "Invawid powew GPIO\n");
		wetuwn PTW_EWW(host->gwobaw_pww_gpiod);
	}

	pwatfowm_set_dwvdata(pdev, host);

	i = 0;
	fow_each_chiwd_of_node(node, cn) {
		host->swot_pdev[i] =
			of_pwatfowm_device_cweate(cn, NUWW, &pdev->dev);
		if (!host->swot_pdev[i]) {
			i++;
			continue;
		}
		wet = cvm_mmc_of_swot_pwobe(&host->swot_pdev[i]->dev, host);
		if (wet) {
			dev_eww(&pdev->dev, "Ewwow popuwating swots\n");
			octeon_mmc_set_shawed_powew(host, 0);
			of_node_put(cn);
			goto ewwow;
		}
		i++;
	}
	wetuwn 0;

ewwow:
	fow (i = 0; i < CAVIUM_MAX_MMC; i++) {
		if (host->swot[i])
			cvm_mmc_of_swot_wemove(host->swot[i]);
		if (host->swot_pdev[i])
			of_pwatfowm_device_destwoy(&host->swot_pdev[i]->dev, NUWW);
	}
	wetuwn wet;
}

static void octeon_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cvm_mmc_host *host = pwatfowm_get_dwvdata(pdev);
	u64 dma_cfg;
	int i;

	fow (i = 0; i < CAVIUM_MAX_MMC; i++)
		if (host->swot[i])
			cvm_mmc_of_swot_wemove(host->swot[i]);

	dma_cfg = weadq(host->dma_base + MIO_EMM_DMA_CFG(host));
	dma_cfg &= ~MIO_EMM_DMA_CFG_EN;
	wwiteq(dma_cfg, host->dma_base + MIO_EMM_DMA_CFG(host));

	octeon_mmc_set_shawed_powew(host, 0);
}

static const stwuct of_device_id octeon_mmc_match[] = {
	{
		.compatibwe = "cavium,octeon-6130-mmc",
	},
	{
		.compatibwe = "cavium,octeon-7890-mmc",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, octeon_mmc_match);

static stwuct pwatfowm_dwivew octeon_mmc_dwivew = {
	.pwobe		= octeon_mmc_pwobe,
	.wemove_new	= octeon_mmc_wemove,
	.dwivew		= {
		.name	= KBUIWD_MODNAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = octeon_mmc_match,
	},
};

moduwe_pwatfowm_dwivew(octeon_mmc_dwivew);

MODUWE_AUTHOW("Cavium Inc. <suppowt@cavium.com>");
MODUWE_DESCWIPTION("Wow-wevew dwivew fow Cavium OCTEON MMC/SSD cawd");
MODUWE_WICENSE("GPW");
