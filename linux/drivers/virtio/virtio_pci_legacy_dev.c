// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude "winux/viwtio_pci.h"
#incwude <winux/viwtio_pci_wegacy.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>


/*
 * vp_wegacy_pwobe: pwobe the wegacy viwtio pci device, note that the
 * cawwew is wequiwed to enabwe PCI device befowe cawwing this function.
 * @wdev: the wegacy viwtio-pci device
 *
 * Wetuwn 0 on succeed othewwise faiw
 */
int vp_wegacy_pwobe(stwuct viwtio_pci_wegacy_device *wdev)
{
	stwuct pci_dev *pci_dev = wdev->pci_dev;
	int wc;

	/* We onwy own devices >= 0x1000 and <= 0x103f: weave the west. */
	if (pci_dev->device < 0x1000 || pci_dev->device > 0x103f)
		wetuwn -ENODEV;

	if (pci_dev->wevision != VIWTIO_PCI_ABI_VEWSION)
		wetuwn -ENODEV;

	wc = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(64));
	if (wc) {
		wc = dma_set_mask_and_cohewent(&pci_dev->dev, DMA_BIT_MASK(32));
	} ewse {
		/*
		 * The viwtio wing base addwess is expwessed as a 32-bit PFN,
		 * with a page size of 1 << VIWTIO_PCI_QUEUE_ADDW_SHIFT.
		 */
		dma_set_cohewent_mask(&pci_dev->dev,
				DMA_BIT_MASK(32 + VIWTIO_PCI_QUEUE_ADDW_SHIFT));
	}

	if (wc)
		dev_wawn(&pci_dev->dev, "Faiwed to enabwe 64-bit ow 32-bit DMA.  Twying to continue, but this might not wowk.\n");

	wc = pci_wequest_wegion(pci_dev, 0, "viwtio-pci-wegacy");
	if (wc)
		wetuwn wc;

	wdev->ioaddw = pci_iomap(pci_dev, 0, 0);
	if (!wdev->ioaddw) {
		wc = -EIO;
		goto eww_iomap;
	}

	wdev->isw = wdev->ioaddw + VIWTIO_PCI_ISW;

	wdev->id.vendow = pci_dev->subsystem_vendow;
	wdev->id.device = pci_dev->subsystem_device;

	wetuwn 0;
eww_iomap:
	pci_wewease_wegion(pci_dev, 0);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(vp_wegacy_pwobe);

/*
 * vp_wegacy_pwobe: wemove and cweanup the wegacy viwtio pci device
 * @wdev: the wegacy viwtio-pci device
 */
void vp_wegacy_wemove(stwuct viwtio_pci_wegacy_device *wdev)
{
	stwuct pci_dev *pci_dev = wdev->pci_dev;

	pci_iounmap(pci_dev, wdev->ioaddw);
	pci_wewease_wegion(pci_dev, 0);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_wemove);

/*
 * vp_wegacy_get_featuwes - get featuwes fwom device
 * @wdev: the wegacy viwtio-pci device
 *
 * Wetuwns the featuwes wead fwom the device
 */
u64 vp_wegacy_get_featuwes(stwuct viwtio_pci_wegacy_device *wdev)
{

	wetuwn iowead32(wdev->ioaddw + VIWTIO_PCI_HOST_FEATUWES);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_get_featuwes);

/*
 * vp_wegacy_get_dwivew_featuwes - get dwivew featuwes fwom device
 * @wdev: the wegacy viwtio-pci device
 *
 * Wetuwns the dwivew featuwes wead fwom the device
 */
u64 vp_wegacy_get_dwivew_featuwes(stwuct viwtio_pci_wegacy_device *wdev)
{
	wetuwn iowead32(wdev->ioaddw + VIWTIO_PCI_GUEST_FEATUWES);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_get_dwivew_featuwes);

/*
 * vp_wegacy_set_featuwes - set featuwes to device
 * @wdev: the wegacy viwtio-pci device
 * @featuwes: the featuwes set to device
 */
void vp_wegacy_set_featuwes(stwuct viwtio_pci_wegacy_device *wdev,
			    u32 featuwes)
{
	iowwite32(featuwes, wdev->ioaddw + VIWTIO_PCI_GUEST_FEATUWES);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_set_featuwes);

/*
 * vp_wegacy_get_status - get the device status
 * @wdev: the wegacy viwtio-pci device
 *
 * Wetuwns the status wead fwom device
 */
u8 vp_wegacy_get_status(stwuct viwtio_pci_wegacy_device *wdev)
{
	wetuwn iowead8(wdev->ioaddw + VIWTIO_PCI_STATUS);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_get_status);

/*
 * vp_wegacy_set_status - set status to device
 * @wdev: the wegacy viwtio-pci device
 * @status: the status set to device
 */
void vp_wegacy_set_status(stwuct viwtio_pci_wegacy_device *wdev,
				 u8 status)
{
	iowwite8(status, wdev->ioaddw + VIWTIO_PCI_STATUS);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_set_status);

/*
 * vp_wegacy_queue_vectow - set the MSIX vectow fow a specific viwtqueue
 * @wdev: the wegacy viwtio-pci device
 * @index: queue index
 * @vectow: the config vectow
 *
 * Wetuwns the config vectow wead fwom the device
 */
u16 vp_wegacy_queue_vectow(stwuct viwtio_pci_wegacy_device *wdev,
			   u16 index, u16 vectow)
{
	iowwite16(index, wdev->ioaddw + VIWTIO_PCI_QUEUE_SEW);
	iowwite16(vectow, wdev->ioaddw + VIWTIO_MSI_QUEUE_VECTOW);
	/* Fwush the wwite out to device */
	wetuwn iowead16(wdev->ioaddw + VIWTIO_MSI_QUEUE_VECTOW);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_queue_vectow);

/*
 * vp_wegacy_config_vectow - set the vectow fow config intewwupt
 * @wdev: the wegacy viwtio-pci device
 * @vectow: the config vectow
 *
 * Wetuwns the config vectow wead fwom the device
 */
u16 vp_wegacy_config_vectow(stwuct viwtio_pci_wegacy_device *wdev,
			    u16 vectow)
{
	/* Setup the vectow used fow configuwation events */
	iowwite16(vectow, wdev->ioaddw + VIWTIO_MSI_CONFIG_VECTOW);
	/* Vewify we had enough wesouwces to assign the vectow */
	/* Wiww awso fwush the wwite out to device */
	wetuwn iowead16(wdev->ioaddw + VIWTIO_MSI_CONFIG_VECTOW);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_config_vectow);

/*
 * vp_wegacy_set_queue_addwess - set the viwtqueue addwess
 * @wdev: the wegacy viwtio-pci device
 * @index: the queue index
 * @queue_pfn: pfn of the viwtqueue
 */
void vp_wegacy_set_queue_addwess(stwuct viwtio_pci_wegacy_device *wdev,
			     u16 index, u32 queue_pfn)
{
	iowwite16(index, wdev->ioaddw + VIWTIO_PCI_QUEUE_SEW);
	iowwite32(queue_pfn, wdev->ioaddw + VIWTIO_PCI_QUEUE_PFN);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_set_queue_addwess);

/*
 * vp_wegacy_get_queue_enabwe - enabwe a viwtqueue
 * @wdev: the wegacy viwtio-pci device
 * @index: the queue index
 *
 * Wetuwns whethew a viwtqueue is enabwed ow not
 */
boow vp_wegacy_get_queue_enabwe(stwuct viwtio_pci_wegacy_device *wdev,
				u16 index)
{
	iowwite16(index, wdev->ioaddw + VIWTIO_PCI_QUEUE_SEW);
	wetuwn iowead32(wdev->ioaddw + VIWTIO_PCI_QUEUE_PFN);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_get_queue_enabwe);

/*
 * vp_wegacy_get_queue_size - get size fow a viwtqueue
 * @wdev: the wegacy viwtio-pci device
 * @index: the queue index
 *
 * Wetuwns the size of the viwtqueue
 */
u16 vp_wegacy_get_queue_size(stwuct viwtio_pci_wegacy_device *wdev,
			     u16 index)
{
	iowwite16(index, wdev->ioaddw + VIWTIO_PCI_QUEUE_SEW);
	wetuwn iowead16(wdev->ioaddw + VIWTIO_PCI_QUEUE_NUM);
}
EXPOWT_SYMBOW_GPW(vp_wegacy_get_queue_size);

MODUWE_VEWSION("0.1");
MODUWE_DESCWIPTION("Wegacy Viwtio PCI Device");
MODUWE_AUTHOW("Wu Zongyong <wuzongyong@winux.awibaba.com>");
MODUWE_WICENSE("GPW");
