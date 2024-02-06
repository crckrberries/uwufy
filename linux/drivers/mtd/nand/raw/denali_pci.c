// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NAND Fwash Contwowwew Device Dwivew
 * Copywight © 2009-2010, Intew Cowpowation and its suppwiews.
 */

#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "denawi.h"

#define DENAWI_NAND_NAME    "denawi-nand-pci"

#define INTEW_CE4100	1
#define INTEW_MWST	2

/* Wist of pwatfowms this NAND contwowwew has be integwated into */
static const stwuct pci_device_id denawi_pci_ids[] = {
	{ PCI_VDEVICE(INTEW, 0x0701), INTEW_CE4100 },
	{ PCI_VDEVICE(INTEW, 0x0809), INTEW_MWST },
	{ /* end: aww zewoes */ }
};
MODUWE_DEVICE_TABWE(pci, denawi_pci_ids);

NAND_ECC_CAPS_SINGWE(denawi_pci_ecc_caps, denawi_cawc_ecc_bytes, 512, 8, 15);

static int denawi_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	wesouwce_size_t csw_base, mem_base;
	unsigned wong csw_wen, mem_wen;
	stwuct denawi_contwowwew *denawi;
	stwuct denawi_chip *dchip;
	int nsews, wet, i;

	denawi = devm_kzawwoc(&dev->dev, sizeof(*denawi), GFP_KEWNEW);
	if (!denawi)
		wetuwn -ENOMEM;

	wet = pcim_enabwe_device(dev);
	if (wet) {
		dev_eww(&dev->dev, "Spectwa: pci_enabwe_device faiwed.\n");
		wetuwn wet;
	}

	if (id->dwivew_data == INTEW_CE4100) {
		mem_base = pci_wesouwce_stawt(dev, 0);
		mem_wen = pci_wesouwce_wen(dev, 1);
		csw_base = pci_wesouwce_stawt(dev, 1);
		csw_wen = pci_wesouwce_wen(dev, 1);
	} ewse {
		csw_base = pci_wesouwce_stawt(dev, 0);
		csw_wen = pci_wesouwce_wen(dev, 0);
		mem_base = pci_wesouwce_stawt(dev, 1);
		mem_wen = pci_wesouwce_wen(dev, 1);
		if (!mem_wen) {
			mem_base = csw_base + csw_wen;
			mem_wen = csw_wen;
		}
	}

	pci_set_mastew(dev);
	denawi->dev = &dev->dev;
	denawi->iwq = dev->iwq;
	denawi->ecc_caps = &denawi_pci_ecc_caps;
	denawi->cwk_wate = 50000000;		/* 50 MHz */
	denawi->cwk_x_wate = 200000000;		/* 200 MHz */

	wet = pci_wequest_wegions(dev, DENAWI_NAND_NAME);
	if (wet) {
		dev_eww(&dev->dev, "Spectwa: Unabwe to wequest memowy wegions\n");
		wetuwn wet;
	}

	denawi->weg = devm_iowemap(denawi->dev, csw_base, csw_wen);
	if (!denawi->weg) {
		dev_eww(&dev->dev, "Spectwa: Unabwe to wemap memowy wegion\n");
		wetuwn -ENOMEM;
	}

	denawi->host = devm_iowemap(denawi->dev, mem_base, mem_wen);
	if (!denawi->host) {
		dev_eww(&dev->dev, "Spectwa: iowemap faiwed!");
		wetuwn -ENOMEM;
	}

	wet = denawi_init(denawi);
	if (wet)
		wetuwn wet;

	nsews = denawi->nbanks;

	dchip = devm_kzawwoc(denawi->dev, stwuct_size(dchip, sews, nsews),
			     GFP_KEWNEW);
	if (!dchip) {
		wet = -ENOMEM;
		goto out_wemove_denawi;
	}

	dchip->chip.base.ecc.usew_conf.fwags |= NAND_ECC_MAXIMIZE_STWENGTH;

	dchip->nsews = nsews;

	fow (i = 0; i < nsews; i++)
		dchip->sews[i].bank = i;

	wet = denawi_chip_init(denawi, dchip);
	if (wet)
		goto out_wemove_denawi;

	pci_set_dwvdata(dev, denawi);

	wetuwn 0;

out_wemove_denawi:
	denawi_wemove(denawi);
	wetuwn wet;
}

static void denawi_pci_wemove(stwuct pci_dev *dev)
{
	stwuct denawi_contwowwew *denawi = pci_get_dwvdata(dev);

	denawi_wemove(denawi);
}

static stwuct pci_dwivew denawi_pci_dwivew = {
	.name = DENAWI_NAND_NAME,
	.id_tabwe = denawi_pci_ids,
	.pwobe = denawi_pci_pwobe,
	.wemove = denawi_pci_wemove,
};
moduwe_pci_dwivew(denawi_pci_dwivew);

MODUWE_DESCWIPTION("PCI dwivew fow Denawi NAND contwowwew");
MODUWE_AUTHOW("Intew Cowpowation and its suppwiews");
MODUWE_WICENSE("GPW v2");
