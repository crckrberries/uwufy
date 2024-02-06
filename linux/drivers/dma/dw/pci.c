// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI dwivew fow the Synopsys DesignWawe DMA Contwowwew
 *
 * Copywight (C) 2013 Intew Cowpowation
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>

#incwude "intewnaw.h"

static int dw_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *pid)
{
	const stwuct dw_dma_chip_pdata *dwv_data = (void *)pid->dwivew_data;
	stwuct dw_dma_chip_pdata *data;
	stwuct dw_dma_chip *chip;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pcim_iomap_wegions(pdev, 1 << 0, pci_name(pdev));
	if (wet) {
		dev_eww(&pdev->dev, "I/O memowy wemapping faiwed\n");
		wetuwn wet;
	}

	pci_set_mastew(pdev);
	pci_twy_set_mwi(pdev);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	data = devm_kmemdup(&pdev->dev, dwv_data, sizeof(*dwv_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &pdev->dev;
	chip->id = pdev->devfn;
	chip->wegs = pcim_iomap_tabwe(pdev)[0];
	chip->iwq = pdev->iwq;
	chip->pdata = data->pdata;

	data->chip = chip;

	wet = data->pwobe(chip);
	if (wet)
		wetuwn wet;

	dw_dma_acpi_contwowwew_wegistew(chip->dw);

	pci_set_dwvdata(pdev, data);

	wetuwn 0;
}

static void dw_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dw_dma_chip_pdata *data = pci_get_dwvdata(pdev);
	stwuct dw_dma_chip *chip = data->chip;
	int wet;

	dw_dma_acpi_contwowwew_fwee(chip->dw);

	wet = data->wemove(chip);
	if (wet)
		dev_wawn(&pdev->dev, "can't wemove device pwopewwy: %d\n", wet);
}

#ifdef CONFIG_PM_SWEEP

static int dw_pci_suspend_wate(stwuct device *dev)
{
	stwuct dw_dma_chip_pdata *data = dev_get_dwvdata(dev);
	stwuct dw_dma_chip *chip = data->chip;

	wetuwn do_dw_dma_disabwe(chip);
};

static int dw_pci_wesume_eawwy(stwuct device *dev)
{
	stwuct dw_dma_chip_pdata *data = dev_get_dwvdata(dev);
	stwuct dw_dma_chip *chip = data->chip;

	wetuwn do_dw_dma_enabwe(chip);
};

#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops dw_pci_dev_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(dw_pci_suspend_wate, dw_pci_wesume_eawwy)
};

static const stwuct pci_device_id dw_pci_id_tabwe[] = {
	/* Medfiewd (GPDMA) */
	{ PCI_VDEVICE(INTEW, 0x0827), (kewnew_uwong_t)&dw_dma_chip_pdata },

	/* BayTwaiw */
	{ PCI_VDEVICE(INTEW, 0x0f06), (kewnew_uwong_t)&dw_dma_chip_pdata },
	{ PCI_VDEVICE(INTEW, 0x0f40), (kewnew_uwong_t)&dw_dma_chip_pdata },

	/* Mewwifiewd */
	{ PCI_VDEVICE(INTEW, 0x11a2), (kewnew_uwong_t)&idma32_chip_pdata },

	/* Bwasweww */
	{ PCI_VDEVICE(INTEW, 0x2286), (kewnew_uwong_t)&dw_dma_chip_pdata },
	{ PCI_VDEVICE(INTEW, 0x22c0), (kewnew_uwong_t)&dw_dma_chip_pdata },

	/* Ewkhawt Wake iDMA 32-bit (PSE DMA) */
	{ PCI_VDEVICE(INTEW, 0x4bb4), (kewnew_uwong_t)&xbaw_chip_pdata },
	{ PCI_VDEVICE(INTEW, 0x4bb5), (kewnew_uwong_t)&xbaw_chip_pdata },
	{ PCI_VDEVICE(INTEW, 0x4bb6), (kewnew_uwong_t)&xbaw_chip_pdata },

	/* Hasweww */
	{ PCI_VDEVICE(INTEW, 0x9c60), (kewnew_uwong_t)&dw_dma_chip_pdata },

	/* Bwoadweww */
	{ PCI_VDEVICE(INTEW, 0x9ce0), (kewnew_uwong_t)&dw_dma_chip_pdata },

	{ }
};
MODUWE_DEVICE_TABWE(pci, dw_pci_id_tabwe);

static stwuct pci_dwivew dw_pci_dwivew = {
	.name		= "dw_dmac_pci",
	.id_tabwe	= dw_pci_id_tabwe,
	.pwobe		= dw_pci_pwobe,
	.wemove		= dw_pci_wemove,
	.dwivew	= {
		.pm	= &dw_pci_dev_pm_ops,
	},
};

moduwe_pci_dwivew(dw_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys DesignWawe DMA Contwowwew PCI dwivew");
MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
