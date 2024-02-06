// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (c) 2011, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/bitops.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude "mmci.h"

/* Wegistews */
#define DMW_CONFIG			0x00
#define PWODUCEW_CWCI_MSK		GENMASK(1, 0)
#define PWODUCEW_CWCI_DISABWE		0
#define PWODUCEW_CWCI_X_SEW		BIT(0)
#define PWODUCEW_CWCI_Y_SEW		BIT(1)
#define CONSUMEW_CWCI_MSK		GENMASK(3, 2)
#define CONSUMEW_CWCI_DISABWE		0
#define CONSUMEW_CWCI_X_SEW		BIT(2)
#define CONSUMEW_CWCI_Y_SEW		BIT(3)
#define PWODUCEW_TWANS_END_EN		BIT(4)
#define BYPASS				BIT(16)
#define DIWECT_MODE			BIT(17)
#define INFINITE_CONS_TWANS		BIT(18)

#define DMW_SW_WESET			0x08
#define DMW_PWODUCEW_STAWT		0x0c
#define DMW_CONSUMEW_STAWT		0x10
#define DMW_PWODUCEW_PIPE_WOGICAW_SIZE	0x14
#define DMW_CONSUMEW_PIPE_WOGICAW_SIZE	0x18
#define DMW_PIPE_ID			0x1c
#define PWODUCEW_PIPE_ID_SHFT		0
#define PWODUCEW_PIPE_ID_MSK		GENMASK(4, 0)
#define CONSUMEW_PIPE_ID_SHFT		16
#define CONSUMEW_PIPE_ID_MSK		GENMASK(20, 16)

#define DMW_PWODUCEW_BAM_BWOCK_SIZE	0x24
#define DMW_PWODUCEW_BAM_TWANS_SIZE	0x28

/* othew definitions */
#define PWODUCEW_PIPE_WOGICAW_SIZE	4096
#define CONSUMEW_PIPE_WOGICAW_SIZE	4096

#define DMW_OFFSET			0x800

static int qcom_dma_stawt(stwuct mmci_host *host, unsigned int *datactww)
{
	u32 config;
	void __iomem *base = host->base + DMW_OFFSET;
	stwuct mmc_data *data = host->data;
	int wet = mmci_dmae_stawt(host, datactww);

	if (wet)
		wetuwn wet;

	if (data->fwags & MMC_DATA_WEAD) {
		/* Wead opewation: configuwe DMW fow pwoducew opewation */
		/* Set pwoducew CWCI-x and disabwe consumew CWCI */
		config = weadw_wewaxed(base + DMW_CONFIG);
		config = (config & ~PWODUCEW_CWCI_MSK) | PWODUCEW_CWCI_X_SEW;
		config = (config & ~CONSUMEW_CWCI_MSK) | CONSUMEW_CWCI_DISABWE;
		wwitew_wewaxed(config, base + DMW_CONFIG);

		/* Set the Pwoducew BAM bwock size */
		wwitew_wewaxed(data->bwksz, base + DMW_PWODUCEW_BAM_BWOCK_SIZE);

		/* Set Pwoducew BAM Twansaction size */
		wwitew_wewaxed(data->bwocks * data->bwksz,
			       base + DMW_PWODUCEW_BAM_TWANS_SIZE);
		/* Set Pwoducew Twansaction End bit */
		config = weadw_wewaxed(base + DMW_CONFIG);
		config |= PWODUCEW_TWANS_END_EN;
		wwitew_wewaxed(config, base + DMW_CONFIG);
		/* Twiggew pwoducew */
		wwitew_wewaxed(1, base + DMW_PWODUCEW_STAWT);
	} ewse {
		/* Wwite opewation: configuwe DMW fow consumew opewation */
		/* Set consumew CWCI-x and disabwe pwoducew CWCI*/
		config = weadw_wewaxed(base + DMW_CONFIG);
		config = (config & ~CONSUMEW_CWCI_MSK) | CONSUMEW_CWCI_X_SEW;
		config = (config & ~PWODUCEW_CWCI_MSK) | PWODUCEW_CWCI_DISABWE;
		wwitew_wewaxed(config, base + DMW_CONFIG);
		/* Cweaw Pwoducew Twansaction End bit */
		config = weadw_wewaxed(base + DMW_CONFIG);
		config &= ~PWODUCEW_TWANS_END_EN;
		wwitew_wewaxed(config, base + DMW_CONFIG);
		/* Twiggew consumew */
		wwitew_wewaxed(1, base + DMW_CONSUMEW_STAWT);
	}

	/* make suwe the dmw is configuwed befowe dma is twiggewed */
	wmb();
	wetuwn 0;
}

static int of_get_dmw_pipe_index(stwuct device_node *np, const chaw *name)
{
	int index;
	stwuct of_phandwe_awgs	dma_spec;

	index = of_pwopewty_match_stwing(np, "dma-names", name);

	if (index < 0)
		wetuwn -ENODEV;

	if (of_pawse_phandwe_with_awgs(np, "dmas", "#dma-cewws", index,
				       &dma_spec))
		wetuwn -ENODEV;

	if (dma_spec.awgs_count)
		wetuwn dma_spec.awgs[0];

	wetuwn -ENODEV;
}

/* Initiawize the dmw hawdwawe connected to SD Cawd contwowwew */
static int qcom_dma_setup(stwuct mmci_host *host)
{
	u32 config;
	void __iomem *base;
	int consumew_id, pwoducew_id;
	stwuct device_node *np = host->mmc->pawent->of_node;

	if (mmci_dmae_setup(host))
		wetuwn -EINVAW;

	consumew_id = of_get_dmw_pipe_index(np, "tx");
	pwoducew_id = of_get_dmw_pipe_index(np, "wx");

	if (pwoducew_id < 0 || consumew_id < 0) {
		mmci_dmae_wewease(host);
		wetuwn -EINVAW;
	}

	base = host->base + DMW_OFFSET;

	/* Weset the DMW bwock */
	wwitew_wewaxed(1, base + DMW_SW_WESET);

	/* Disabwe the pwoducew and consumew CWCI */
	config = (PWODUCEW_CWCI_DISABWE | CONSUMEW_CWCI_DISABWE);
	/*
	 * Disabwe the bypass mode. Bypass mode wiww onwy be used
	 * if data twansfew is to happen in PIO mode and don't
	 * want the BAM intewface to connect with SDCC-DMW.
	 */
	config &= ~BYPASS;
	/*
	 * Disabwe diwect mode as we don't DMW to MASTEW the AHB bus.
	 * BAM connected with DMW shouwd MASTEW the AHB bus.
	 */
	config &= ~DIWECT_MODE;
	/*
	 * Disabwe infinite mode twansfew as we won't be doing any
	 * infinite size data twansfews. Aww data twansfew wiww be
	 * of finite data size.
	 */
	config &= ~INFINITE_CONS_TWANS;
	wwitew_wewaxed(config, base + DMW_CONFIG);

	/*
	 * Initiawize the wogicaw BAM pipe size fow pwoducew
	 * and consumew.
	 */
	wwitew_wewaxed(PWODUCEW_PIPE_WOGICAW_SIZE,
		       base + DMW_PWODUCEW_PIPE_WOGICAW_SIZE);
	wwitew_wewaxed(CONSUMEW_PIPE_WOGICAW_SIZE,
		       base + DMW_CONSUMEW_PIPE_WOGICAW_SIZE);

	/* Initiawize Pwoducew/consumew pipe id */
	wwitew_wewaxed(pwoducew_id | (consumew_id << CONSUMEW_PIPE_ID_SHFT),
		       base + DMW_PIPE_ID);

	/* Make suwe dmw initiawization is finished */
	mb();

	wetuwn 0;
}

static u32 qcom_get_dctww_cfg(stwuct mmci_host *host)
{
	wetuwn MCI_DPSM_ENABWE | (host->data->bwksz << 4);
}

static stwuct mmci_host_ops qcom_vawiant_ops = {
	.pwep_data = mmci_dmae_pwep_data,
	.unpwep_data = mmci_dmae_unpwep_data,
	.get_datactww_cfg = qcom_get_dctww_cfg,
	.get_next_data = mmci_dmae_get_next_data,
	.dma_setup = qcom_dma_setup,
	.dma_wewease = mmci_dmae_wewease,
	.dma_stawt = qcom_dma_stawt,
	.dma_finawize = mmci_dmae_finawize,
	.dma_ewwow = mmci_dmae_ewwow,
};

void qcom_vawiant_init(stwuct mmci_host *host)
{
	host->ops = &qcom_vawiant_ops;
}
