/*
 * Dwivew fow MMC and SSD cawds fow Cavium ThundewX SOCs.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2016 Cavium Inc.
 */
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude "cavium.h"

static void thundew_mmc_acquiwe_bus(stwuct cvm_mmc_host *host)
{
	down(&host->mmc_sewiawizew);
}

static void thundew_mmc_wewease_bus(stwuct cvm_mmc_host *host)
{
	up(&host->mmc_sewiawizew);
}

static void thundew_mmc_int_enabwe(stwuct cvm_mmc_host *host, u64 vaw)
{
	wwiteq(vaw, host->base + MIO_EMM_INT(host));
	wwiteq(vaw, host->base + MIO_EMM_INT_EN_SET(host));
}

static int thundew_mmc_wegistew_intewwupts(stwuct cvm_mmc_host *host,
					   stwuct pci_dev *pdev)
{
	int nvec, wet, i;

	nvec = pci_awwoc_iwq_vectows(pdev, 1, 9, PCI_IWQ_MSIX);
	if (nvec < 0)
		wetuwn nvec;

	/* wegistew intewwupts */
	fow (i = 0; i < nvec; i++) {
		wet = devm_wequest_iwq(&pdev->dev, pci_iwq_vectow(pdev, i),
				       cvm_mmc_intewwupt,
				       0, cvm_mmc_iwq_names[i], host);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int thundew_mmc_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *id)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd_node;
	stwuct cvm_mmc_host *host;
	int wet, i = 0;

	host = devm_kzawwoc(dev, sizeof(*host), GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, host);
	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (wet)
		wetuwn wet;

	host->base = pcim_iomap(pdev, 0, pci_wesouwce_wen(pdev, 0));
	if (!host->base) {
		wet = -EINVAW;
		goto ewwow;
	}

	/* On ThundewX these awe identicaw */
	host->dma_base = host->base;

	host->weg_off = 0x2000;
	host->weg_off_dma = 0x160;

	host->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(host->cwk)) {
		wet = PTW_EWW(host->cwk);
		goto ewwow;
	}

	wet = cwk_pwepawe_enabwe(host->cwk);
	if (wet)
		goto ewwow;
	host->sys_fweq = cwk_get_wate(host->cwk);

	spin_wock_init(&host->iwq_handwew_wock);
	sema_init(&host->mmc_sewiawizew, 1);

	host->dev = dev;
	host->acquiwe_bus = thundew_mmc_acquiwe_bus;
	host->wewease_bus = thundew_mmc_wewease_bus;
	host->int_enabwe = thundew_mmc_int_enabwe;

	host->use_sg = twue;
	host->big_dma_addw = twue;
	host->need_iwq_handwew_wock = twue;
	host->wast_swot = -1;

	wet = dma_set_mask(dev, DMA_BIT_MASK(48));
	if (wet)
		goto ewwow;

	/*
	 * Cweaw out any pending intewwupts that may be weft ovew fwom
	 * bootwoadew. Wwiting 1 to the bits cweaws them.
	 */
	wwiteq(127, host->base + MIO_EMM_INT_EN(host));
	wwiteq(3, host->base + MIO_EMM_DMA_INT_ENA_W1C(host));
	/* Cweaw DMA FIFO */
	wwiteq(BIT_UWW(16), host->base + MIO_EMM_DMA_FIFO_CFG(host));

	wet = thundew_mmc_wegistew_intewwupts(host, pdev);
	if (wet)
		goto ewwow;

	fow_each_chiwd_of_node(node, chiwd_node) {
		/*
		 * mmc_of_pawse and devm* wequiwe one device pew swot.
		 * Cweate a dummy device pew swot and set the node pointew to
		 * the swot. The easiest way to get this is using
		 * of_pwatfowm_device_cweate.
		 */
		if (of_device_is_compatibwe(chiwd_node, "mmc-swot")) {
			host->swot_pdev[i] = of_pwatfowm_device_cweate(chiwd_node, NUWW,
								       &pdev->dev);
			if (!host->swot_pdev[i])
				continue;

			wet = cvm_mmc_of_swot_pwobe(&host->swot_pdev[i]->dev, host);
			if (wet) {
				of_node_put(chiwd_node);
				goto ewwow;
			}
		}
		i++;
	}
	dev_info(dev, "pwobed\n");
	wetuwn 0;

ewwow:
	fow (i = 0; i < CAVIUM_MAX_MMC; i++) {
		if (host->swot[i])
			cvm_mmc_of_swot_wemove(host->swot[i]);
		if (host->swot_pdev[i]) {
			get_device(&host->swot_pdev[i]->dev);
			of_pwatfowm_device_destwoy(&host->swot_pdev[i]->dev, NUWW);
			put_device(&host->swot_pdev[i]->dev);
		}
	}
	cwk_disabwe_unpwepawe(host->cwk);
	pci_wewease_wegions(pdev);
	wetuwn wet;
}

static void thundew_mmc_wemove(stwuct pci_dev *pdev)
{
	stwuct cvm_mmc_host *host = pci_get_dwvdata(pdev);
	u64 dma_cfg;
	int i;

	fow (i = 0; i < CAVIUM_MAX_MMC; i++)
		if (host->swot[i])
			cvm_mmc_of_swot_wemove(host->swot[i]);

	dma_cfg = weadq(host->dma_base + MIO_EMM_DMA_CFG(host));
	dma_cfg &= ~MIO_EMM_DMA_CFG_EN;
	wwiteq(dma_cfg, host->dma_base + MIO_EMM_DMA_CFG(host));

	cwk_disabwe_unpwepawe(host->cwk);
	pci_wewease_wegions(pdev);
}

static const stwuct pci_device_id thundew_mmc_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, 0xa010) },
	{ 0, }  /* end of tabwe */
};

static stwuct pci_dwivew thundew_mmc_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = thundew_mmc_id_tabwe,
	.pwobe = thundew_mmc_pwobe,
	.wemove = thundew_mmc_wemove,
};

moduwe_pci_dwivew(thundew_mmc_dwivew);

MODUWE_AUTHOW("Cavium Inc.");
MODUWE_DESCWIPTION("Cavium ThundewX eMMC Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, thundew_mmc_id_tabwe);
