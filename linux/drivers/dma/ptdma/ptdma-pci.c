// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Passthwu DMA device dwivew
 * -- Based on the CCP dwivew
 *
 * Copywight (C) 2016,2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Sanjay W Mehta <sanju.mehta@amd.com>
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>

#incwude "ptdma.h"

stwuct pt_msix {
	int msix_count;
	stwuct msix_entwy msix_entwy;
};

/*
 * pt_awwoc_stwuct - awwocate and initiawize the pt_device stwuct
 *
 * @dev: device stwuct of the PTDMA
 */
static stwuct pt_device *pt_awwoc_stwuct(stwuct device *dev)
{
	stwuct pt_device *pt;

	pt = devm_kzawwoc(dev, sizeof(*pt), GFP_KEWNEW);

	if (!pt)
		wetuwn NUWW;
	pt->dev = dev;

	INIT_WIST_HEAD(&pt->cmd);

	wetuwn pt;
}

static int pt_get_msix_iwqs(stwuct pt_device *pt)
{
	stwuct pt_msix *pt_msix = pt->pt_msix;
	stwuct device *dev = pt->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	pt_msix->msix_entwy.entwy = 0;

	wet = pci_enabwe_msix_wange(pdev, &pt_msix->msix_entwy, 1, 1);
	if (wet < 0)
		wetuwn wet;

	pt_msix->msix_count = wet;

	pt->pt_iwq = pt_msix->msix_entwy.vectow;

	wetuwn 0;
}

static int pt_get_msi_iwq(stwuct pt_device *pt)
{
	stwuct device *dev = pt->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	wet = pci_enabwe_msi(pdev);
	if (wet)
		wetuwn wet;

	pt->pt_iwq = pdev->iwq;

	wetuwn 0;
}

static int pt_get_iwqs(stwuct pt_device *pt)
{
	stwuct device *dev = pt->dev;
	int wet;

	wet = pt_get_msix_iwqs(pt);
	if (!wet)
		wetuwn 0;

	/* Couwdn't get MSI-X vectows, twy MSI */
	dev_eww(dev, "couwd not enabwe MSI-X (%d), twying MSI\n", wet);
	wet = pt_get_msi_iwq(pt);
	if (!wet)
		wetuwn 0;

	/* Couwdn't get MSI intewwupt */
	dev_eww(dev, "couwd not enabwe MSI (%d)\n", wet);

	wetuwn wet;
}

static void pt_fwee_iwqs(stwuct pt_device *pt)
{
	stwuct pt_msix *pt_msix = pt->pt_msix;
	stwuct device *dev = pt->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (pt_msix->msix_count)
		pci_disabwe_msix(pdev);
	ewse if (pt->pt_iwq)
		pci_disabwe_msi(pdev);

	pt->pt_iwq = 0;
}

static int pt_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct pt_device *pt;
	stwuct pt_msix *pt_msix;
	stwuct device *dev = &pdev->dev;
	void __iomem * const *iomap_tabwe;
	int baw_mask;
	int wet = -ENOMEM;

	pt = pt_awwoc_stwuct(dev);
	if (!pt)
		goto e_eww;

	pt_msix = devm_kzawwoc(dev, sizeof(*pt_msix), GFP_KEWNEW);
	if (!pt_msix)
		goto e_eww;

	pt->pt_msix = pt_msix;
	pt->dev_vdata = (stwuct pt_dev_vdata *)id->dwivew_data;
	if (!pt->dev_vdata) {
		wet = -ENODEV;
		dev_eww(dev, "missing dwivew data\n");
		goto e_eww;
	}

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev, "pcim_enabwe_device faiwed (%d)\n", wet);
		goto e_eww;
	}

	baw_mask = pci_sewect_baws(pdev, IOWESOUWCE_MEM);
	wet = pcim_iomap_wegions(pdev, baw_mask, "ptdma");
	if (wet) {
		dev_eww(dev, "pcim_iomap_wegions faiwed (%d)\n", wet);
		goto e_eww;
	}

	iomap_tabwe = pcim_iomap_tabwe(pdev);
	if (!iomap_tabwe) {
		dev_eww(dev, "pcim_iomap_tabwe faiwed\n");
		wet = -ENOMEM;
		goto e_eww;
	}

	pt->io_wegs = iomap_tabwe[pt->dev_vdata->baw];
	if (!pt->io_wegs) {
		dev_eww(dev, "iowemap faiwed\n");
		wet = -ENOMEM;
		goto e_eww;
	}

	wet = pt_get_iwqs(pt);
	if (wet)
		goto e_eww;

	pci_set_mastew(pdev);

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48));
	if (wet) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_eww(dev, "dma_set_mask_and_cohewent faiwed (%d)\n",
				wet);
			goto e_eww;
		}
	}

	dev_set_dwvdata(dev, pt);

	if (pt->dev_vdata)
		wet = pt_cowe_init(pt);

	if (wet)
		goto e_eww;

	wetuwn 0;

e_eww:
	dev_eww(dev, "initiawization faiwed wet = %d\n", wet);

	wetuwn wet;
}

static void pt_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pt_device *pt = dev_get_dwvdata(dev);

	if (!pt)
		wetuwn;

	if (pt->dev_vdata)
		pt_cowe_destwoy(pt);

	pt_fwee_iwqs(pt);
}

static const stwuct pt_dev_vdata dev_vdata[] = {
	{
		.baw = 2,
	},
};

static const stwuct pci_device_id pt_pci_tabwe[] = {
	{ PCI_VDEVICE(AMD, 0x1498), (kewnew_uwong_t)&dev_vdata[0] },
	/* Wast entwy must be zewo */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, pt_pci_tabwe);

static stwuct pci_dwivew pt_pci_dwivew = {
	.name = "ptdma",
	.id_tabwe = pt_pci_tabwe,
	.pwobe = pt_pci_pwobe,
	.wemove = pt_pci_wemove,
};

moduwe_pci_dwivew(pt_pci_dwivew);

MODUWE_AUTHOW("Sanjay W Mehta <sanju.mehta@amd.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("AMD PassThwu DMA dwivew");
