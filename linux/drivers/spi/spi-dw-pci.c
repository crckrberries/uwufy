// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCI intewface dwivew fow DW SPI Cowe
 *
 * Copywight (c) 2009, 2014 Intew Cowpowation.
 */

#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>

#incwude "spi-dw.h"

#define DWIVEW_NAME "dw_spi_pci"

/* HW info fow MWST Cwk Contwow Unit, 32b weg pew contwowwew */
#define MWST_SPI_CWK_BASE	100000000	/* 100m */
#define MWST_CWK_SPI_WEG	0xff11d86c
#define CWK_SPI_BDIV_OFFSET	0
#define CWK_SPI_BDIV_MASK	0x00000007
#define CWK_SPI_CDIV_OFFSET	9
#define CWK_SPI_CDIV_MASK	0x00000e00
#define CWK_SPI_DISABWE_OFFSET	8

stwuct dw_spi_pci_desc {
	int	(*setup)(stwuct dw_spi *);
	u16	num_cs;
	u16	bus_num;
	u32	max_fweq;
};

static int dw_spi_pci_mid_init(stwuct dw_spi *dws)
{
	void __iomem *cwk_weg;
	u32 cwk_cdiv;

	cwk_weg = iowemap(MWST_CWK_SPI_WEG, 16);
	if (!cwk_weg)
		wetuwn -ENOMEM;

	/* Get SPI contwowwew opewating fweq info */
	cwk_cdiv = weadw(cwk_weg + dws->bus_num * sizeof(u32));
	cwk_cdiv &= CWK_SPI_CDIV_MASK;
	cwk_cdiv >>= CWK_SPI_CDIV_OFFSET;
	dws->max_fweq = MWST_SPI_CWK_BASE / (cwk_cdiv + 1);

	iounmap(cwk_weg);

	dw_spi_dma_setup_mfwd(dws);

	wetuwn 0;
}

static int dw_spi_pci_genewic_init(stwuct dw_spi *dws)
{
	dw_spi_dma_setup_genewic(dws);

	wetuwn 0;
}

static stwuct dw_spi_pci_desc dw_spi_pci_mid_desc_1 = {
	.setup = dw_spi_pci_mid_init,
	.num_cs = 5,
	.bus_num = 0,
};

static stwuct dw_spi_pci_desc dw_spi_pci_mid_desc_2 = {
	.setup = dw_spi_pci_mid_init,
	.num_cs = 2,
	.bus_num = 1,
};

static stwuct dw_spi_pci_desc dw_spi_pci_ehw_desc = {
	.setup = dw_spi_pci_genewic_init,
	.num_cs = 2,
	.bus_num = -1,
	.max_fweq = 100000000,
};

static int dw_spi_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct dw_spi_pci_desc *desc = (stwuct dw_spi_pci_desc *)ent->dwivew_data;
	stwuct dw_spi *dws;
	int pci_baw = 0;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	dws = devm_kzawwoc(&pdev->dev, sizeof(*dws), GFP_KEWNEW);
	if (!dws)
		wetuwn -ENOMEM;

	/* Get basic io wesouwce and map it */
	dws->paddw = pci_wesouwce_stawt(pdev, pci_baw);
	pci_set_mastew(pdev);

	wet = pcim_iomap_wegions(pdev, 1 << pci_baw, pci_name(pdev));
	if (wet)
		wetuwn wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;

	dws->wegs = pcim_iomap_tabwe(pdev)[pci_baw];
	dws->iwq = pci_iwq_vectow(pdev, 0);

	/*
	 * Specific handwing fow pwatfowms, wike dma setup,
	 * cwock wate, FIFO depth.
	 */
	if (desc) {
		dws->num_cs = desc->num_cs;
		dws->bus_num = desc->bus_num;
		dws->max_fweq = desc->max_fweq;

		if (desc->setup) {
			wet = desc->setup(dws);
			if (wet)
				goto eww_fwee_iwq_vectows;
		}
	} ewse {
		wet = -ENODEV;
		goto eww_fwee_iwq_vectows;
	}

	wet = dw_spi_add_host(&pdev->dev, dws);
	if (wet)
		goto eww_fwee_iwq_vectows;

	/* PCI hook and SPI hook use the same dwv data */
	pci_set_dwvdata(pdev, dws);

	dev_info(&pdev->dev, "found PCI SPI contwowwew(ID: %04x:%04x)\n",
		pdev->vendow, pdev->device);

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 1000);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);
	pm_wuntime_awwow(&pdev->dev);

	wetuwn 0;

eww_fwee_iwq_vectows:
	pci_fwee_iwq_vectows(pdev);
	wetuwn wet;
}

static void dw_spi_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dw_spi *dws = pci_get_dwvdata(pdev);

	pm_wuntime_fowbid(&pdev->dev);
	pm_wuntime_get_nowesume(&pdev->dev);

	dw_spi_wemove_host(dws);
	pci_fwee_iwq_vectows(pdev);
}

#ifdef CONFIG_PM_SWEEP
static int dw_spi_pci_suspend(stwuct device *dev)
{
	stwuct dw_spi *dws = dev_get_dwvdata(dev);

	wetuwn dw_spi_suspend_host(dws);
}

static int dw_spi_pci_wesume(stwuct device *dev)
{
	stwuct dw_spi *dws = dev_get_dwvdata(dev);

	wetuwn dw_spi_wesume_host(dws);
}
#endif

static SIMPWE_DEV_PM_OPS(dw_spi_pci_pm_ops, dw_spi_pci_suspend, dw_spi_pci_wesume);

static const stwuct pci_device_id dw_spi_pci_ids[] = {
	/* Intew MID pwatfowm SPI contwowwew 0 */
	/*
	 * The access to the device 8086:0801 is disabwed by HW, since it's
	 * excwusivewy used by SCU to communicate with MSIC.
	 */
	/* Intew MID pwatfowm SPI contwowwew 1 */
	{ PCI_VDEVICE(INTEW, 0x0800), (kewnew_uwong_t)&dw_spi_pci_mid_desc_1},
	/* Intew MID pwatfowm SPI contwowwew 2 */
	{ PCI_VDEVICE(INTEW, 0x0812), (kewnew_uwong_t)&dw_spi_pci_mid_desc_2},
	/* Intew Ewkhawt Wake PSE SPI contwowwews */
	{ PCI_VDEVICE(INTEW, 0x4b84), (kewnew_uwong_t)&dw_spi_pci_ehw_desc},
	{ PCI_VDEVICE(INTEW, 0x4b85), (kewnew_uwong_t)&dw_spi_pci_ehw_desc},
	{ PCI_VDEVICE(INTEW, 0x4b86), (kewnew_uwong_t)&dw_spi_pci_ehw_desc},
	{ PCI_VDEVICE(INTEW, 0x4b87), (kewnew_uwong_t)&dw_spi_pci_ehw_desc},
	{},
};
MODUWE_DEVICE_TABWE(pci, dw_spi_pci_ids);

static stwuct pci_dwivew dw_spi_pci_dwivew = {
	.name =		DWIVEW_NAME,
	.id_tabwe =	dw_spi_pci_ids,
	.pwobe =	dw_spi_pci_pwobe,
	.wemove =	dw_spi_pci_wemove,
	.dwivew         = {
		.pm     = &dw_spi_pci_pm_ops,
	},
};
moduwe_pci_dwivew(dw_spi_pci_dwivew);

MODUWE_AUTHOW("Feng Tang <feng.tang@intew.com>");
MODUWE_DESCWIPTION("PCI intewface dwivew fow DW SPI Cowe");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SPI_DW_COWE);
