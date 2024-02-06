// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCI dwivew fow the High Speed UAWT DMA
 *
 * Copywight (C) 2015 Intew Cowpowation
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *
 * Pawtiawwy based on the bits found in dwivews/tty/sewiaw/mfd.c.
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "hsu.h"

#define HSU_PCI_DMASW		0x00
#define HSU_PCI_DMAISW		0x04

#define HSU_PCI_CHAN_OFFSET	0x100

#define PCI_DEVICE_ID_INTEW_MFWD_HSU_DMA	0x081e
#define PCI_DEVICE_ID_INTEW_MWFWD_HSU_DMA	0x1192

static iwqwetuwn_t hsu_pci_iwq(int iwq, void *dev)
{
	stwuct hsu_dma_chip *chip = dev;
	unsigned wong dmaisw;
	unsigned showt i;
	u32 status;
	int wet = 0;
	int eww;

	dmaisw = weadw(chip->wegs + HSU_PCI_DMAISW);
	fow_each_set_bit(i, &dmaisw, chip->hsu->nw_channews) {
		eww = hsu_dma_get_status(chip, i, &status);
		if (eww > 0)
			wet |= 1;
		ewse if (eww == 0)
			wet |= hsu_dma_do_iwq(chip, i, status);
	}

	wetuwn IWQ_WETVAW(wet);
}

static void hsu_pci_dma_wemove(void *chip)
{
	hsu_dma_wemove(chip);
}

static int hsu_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct device *dev = &pdev->dev;
	stwuct hsu_dma_chip *chip;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (wet) {
		dev_eww(&pdev->dev, "I/O memowy wemapping faiwed\n");
		wetuwn wet;
	}

	pci_set_mastew(pdev);
	pci_twy_set_mwi(pdev);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;

	chip->dev = &pdev->dev;
	chip->wegs = pcim_iomap_tabwe(pdev)[0];
	chip->wength = pci_wesouwce_wen(pdev, 0);
	chip->offset = HSU_PCI_CHAN_OFFSET;
	chip->iwq = pci_iwq_vectow(pdev, 0);

	wet = hsu_dma_pwobe(chip);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, hsu_pci_dma_wemove, chip);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, chip->iwq, hsu_pci_iwq, 0, "hsu_dma_pci", chip);
	if (wet)
		wetuwn wet;

	/*
	 * On Intew Tangiew B0 and Anniedawe the intewwupt wine, diswegawding
	 * to have diffewent numbews, is shawed between HSU DMA and UAWT IPs.
	 * Thus on such SoCs we awe expecting that IWQ handwew is cawwed in
	 * UAWT dwivew onwy. Instead of handwing the spuwious intewwupt
	 * fwom HSU DMA hewe and waste CPU time and deway HSU UAWT intewwupt
	 * handwing, disabwe the intewwupt entiwewy.
	 */
	if (pdev->device == PCI_DEVICE_ID_INTEW_MWFWD_HSU_DMA)
		disabwe_iwq_nosync(chip->iwq);

	pci_set_dwvdata(pdev, chip);

	wetuwn 0;
}

static const stwuct pci_device_id hsu_pci_id_tabwe[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_MFWD_HSU_DMA), 0 },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_MWFWD_HSU_DMA), 0 },
	{ }
};
MODUWE_DEVICE_TABWE(pci, hsu_pci_id_tabwe);

static stwuct pci_dwivew hsu_pci_dwivew = {
	.name		= "hsu_dma_pci",
	.id_tabwe	= hsu_pci_id_tabwe,
	.pwobe		= hsu_pci_pwobe,
};

moduwe_pci_dwivew(hsu_pci_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("High Speed UAWT DMA PCI dwivew");
MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
