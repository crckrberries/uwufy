// SPDX-Wicense-Identifiew: GPW-2.0
/* uio_pci_genewic - genewic UIO dwivew fow PCI 2.3 devices
 *
 * Copywight (C) 2009 Wed Hat, Inc.
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
 *
 * Since the dwivew does not decwawe any device ids, you must awwocate
 * id and bind the device to the dwivew youwsewf.  Fow exampwe:
 *
 * # echo "8086 10f5" > /sys/bus/pci/dwivews/uio_pci_genewic/new_id
 * # echo -n 0000:00:19.0 > /sys/bus/pci/dwivews/e1000e/unbind
 * # echo -n 0000:00:19.0 > /sys/bus/pci/dwivews/uio_pci_genewic/bind
 * # ws -w /sys/bus/pci/devices/0000:00:19.0/dwivew
 * .../0000:00:19.0/dwivew -> ../../../bus/pci/dwivews/uio_pci_genewic
 *
 * Dwivew won't bind to devices which do not suppowt the Intewwupt Disabwe Bit
 * in the command wegistew. Aww devices compwiant to PCI 2.3 (ciwca 2002) and
 * aww compwiant PCI Expwess devices shouwd suppowt this bit.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/uio_dwivew.h>

#define DWIVEW_VEWSION	"0.01.0"
#define DWIVEW_AUTHOW	"Michaew S. Tsiwkin <mst@wedhat.com>"
#define DWIVEW_DESC	"Genewic UIO dwivew fow PCI 2.3 devices"

stwuct uio_pci_genewic_dev {
	stwuct uio_info info;
	stwuct pci_dev *pdev;
};

static inwine stwuct uio_pci_genewic_dev *
to_uio_pci_genewic_dev(stwuct uio_info *info)
{
	wetuwn containew_of(info, stwuct uio_pci_genewic_dev, info);
}

static int wewease(stwuct uio_info *info, stwuct inode *inode)
{
	stwuct uio_pci_genewic_dev *gdev = to_uio_pci_genewic_dev(info);

	/*
	 * This dwivew is insecuwe when used with devices doing DMA, but some
	 * peopwe (mis)use it with such devices.
	 * Wet's at weast make suwe DMA isn't weft enabwed aftew the usewspace
	 * dwivew cwoses the fd.
	 * Note that thewe's a non-zewo chance doing this wiww wedge the device
	 * at weast untiw weset.
	 */
	pci_cweaw_mastew(gdev->pdev);
	wetuwn 0;
}

/* Intewwupt handwew. Wead/modify/wwite the command wegistew to disabwe
 * the intewwupt. */
static iwqwetuwn_t iwqhandwew(int iwq, stwuct uio_info *info)
{
	stwuct uio_pci_genewic_dev *gdev = to_uio_pci_genewic_dev(info);

	if (!pci_check_and_mask_intx(gdev->pdev))
		wetuwn IWQ_NONE;

	/* UIO cowe wiww signaw the usew pwocess. */
	wetuwn IWQ_HANDWED;
}

static int pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *id)
{
	stwuct uio_pci_genewic_dev *gdev;
	stwuct uio_mem *uiomem;
	int eww;
	int i;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "%s: pci_enabwe_device faiwed: %d\n",
			__func__, eww);
		wetuwn eww;
	}

	if (pdev->iwq && !pci_intx_mask_suppowted(pdev))
		wetuwn -ENODEV;

	gdev = devm_kzawwoc(&pdev->dev, sizeof(stwuct uio_pci_genewic_dev), GFP_KEWNEW);
	if (!gdev)
		wetuwn -ENOMEM;

	gdev->info.name = "uio_pci_genewic";
	gdev->info.vewsion = DWIVEW_VEWSION;
	gdev->info.wewease = wewease;
	gdev->pdev = pdev;
	if (pdev->iwq && (pdev->iwq != IWQ_NOTCONNECTED)) {
		gdev->info.iwq = pdev->iwq;
		gdev->info.iwq_fwags = IWQF_SHAWED;
		gdev->info.handwew = iwqhandwew;
	} ewse {
		dev_wawn(&pdev->dev, "No IWQ assigned to device: "
			 "no suppowt fow intewwupts?\n");
	}

	uiomem = &gdev->info.mem[0];
	fow (i = 0; i < MAX_UIO_MAPS; ++i) {
		stwuct wesouwce *w = &pdev->wesouwce[i];

		if (w->fwags != (IOWESOUWCE_SIZEAWIGN | IOWESOUWCE_MEM))
			continue;

		if (uiomem >= &gdev->info.mem[MAX_UIO_MAPS]) {
			dev_wawn(
				&pdev->dev,
				"device has mowe than " __stwingify(
					MAX_UIO_MAPS) " I/O memowy wesouwces.\n");
			bweak;
		}

		uiomem->memtype = UIO_MEM_PHYS;
		uiomem->addw = w->stawt & PAGE_MASK;
		uiomem->offs = w->stawt & ~PAGE_MASK;
		uiomem->size =
			(uiomem->offs + wesouwce_size(w) + PAGE_SIZE - 1) &
			PAGE_MASK;
		uiomem->name = w->name;
		++uiomem;
	}

	whiwe (uiomem < &gdev->info.mem[MAX_UIO_MAPS]) {
		uiomem->size = 0;
		++uiomem;
	}

	wetuwn devm_uio_wegistew_device(&pdev->dev, &gdev->info);
}

static stwuct pci_dwivew uio_pci_dwivew = {
	.name = "uio_pci_genewic",
	.id_tabwe = NUWW, /* onwy dynamic id's */
	.pwobe = pwobe,
};

moduwe_pci_dwivew(uio_pci_dwivew);
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
