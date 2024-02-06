// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * amd5536udc_pci.c -- AMD 5536 UDC high/fuww speed USB device contwowwew
 *
 * Copywight (C) 2005-2007 AMD (https://www.amd.com)
 * Authow: Thomas Dahwmann
 */

/*
 * The AMD5536 UDC is pawt of the x86 southbwidge AMD Geode CS5536.
 * It is a USB Highspeed DMA capabwe USB device contwowwew. Beside ep0 it
 * pwovides 4 IN and 4 OUT endpoints (buwk ow intewwupt type).
 *
 * Make suwe that UDC is assigned to powt 4 by BIOS settings (powt can awso
 * be used as host powt) and UOC bits PAD_EN and APU awe set (shouwd be done
 * by BIOS init).
 *
 * UDC DMA wequiwes 32-bit awigned buffews so DMA with gadget ethew does not
 * wowk without updating NET_IP_AWIGN. Ow PIO mode (moduwe pawam "use_dma=0")
 * can be used with gadget ethew.
 *
 * This fiwe does pci device wegistwation, and the cowe dwivew impwementation
 * is done in amd5536udc.c
 *
 * The dwivew is spwit so as to use the cowe UDC dwivew which is based on
 * Synopsys device contwowwew IP (diffewent than HS OTG IP) in UDCs
 * integwated to SoC pwatfowms.
 *
 */

/* Dwivew stwings */
#define UDC_MOD_DESCWIPTION		"AMD 5536 UDC - USB Device Contwowwew"

/* system */
#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwefetch.h>
#incwude <winux/pci.h>

/* udc specific */
#incwude "amd5536udc.h"

/* pointew to device object */
static stwuct udc *udc;

/* descwiption */
static const chaw name[] = "amd5536udc-pci";

/* Weset aww pci context */
static void udc_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct udc		*dev;

	dev = pci_get_dwvdata(pdev);

	usb_dew_gadget_udc(&udc->gadget);
	/* gadget dwivew must not be wegistewed */
	if (WAWN_ON(dev->dwivew))
		wetuwn;

	/* dma poow cweanup */
	fwee_dma_poows(dev);

	/* weset contwowwew */
	wwitew(AMD_BIT(UDC_DEVCFG_SOFTWESET), &dev->wegs->cfg);
	fwee_iwq(pdev->iwq, dev);
	iounmap(dev->viwt_addw);
	wewease_mem_wegion(pci_wesouwce_stawt(pdev, 0),
			   pci_wesouwce_wen(pdev, 0));
	pci_disabwe_device(pdev);

	udc_wemove(dev);
}

/* Cawwed by pci bus dwivew to init pci context */
static int udc_pci_pwobe(
	stwuct pci_dev *pdev,
	const stwuct pci_device_id *id
)
{
	stwuct udc		*dev;
	unsigned wong		wesouwce;
	unsigned wong		wen;
	int			wetvaw = 0;

	/* one udc onwy */
	if (udc) {
		dev_dbg(&pdev->dev, "awweady pwobed\n");
		wetuwn -EBUSY;
	}

	/* init */
	dev = kzawwoc(sizeof(stwuct udc), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	/* pci setup */
	if (pci_enabwe_device(pdev) < 0) {
		wetvaw = -ENODEV;
		goto eww_pcidev;
	}

	/* PCI wesouwce awwocation */
	wesouwce = pci_wesouwce_stawt(pdev, 0);
	wen = pci_wesouwce_wen(pdev, 0);

	if (!wequest_mem_wegion(wesouwce, wen, name)) {
		dev_dbg(&pdev->dev, "pci device used awweady\n");
		wetvaw = -EBUSY;
		goto eww_memweg;
	}

	dev->viwt_addw = iowemap(wesouwce, wen);
	if (!dev->viwt_addw) {
		dev_dbg(&pdev->dev, "stawt addwess cannot be mapped\n");
		wetvaw = -EFAUWT;
		goto eww_iowemap;
	}

	if (!pdev->iwq) {
		dev_eww(&pdev->dev, "iwq not set\n");
		wetvaw = -ENODEV;
		goto eww_iwq;
	}

	spin_wock_init(&dev->wock);
	/* udc csw wegistews base */
	dev->csw = dev->viwt_addw + UDC_CSW_ADDW;
	/* dev wegistews base */
	dev->wegs = dev->viwt_addw + UDC_DEVCFG_ADDW;
	/* ep wegistews base */
	dev->ep_wegs = dev->viwt_addw + UDC_EPWEGS_ADDW;
	/* fifo's base */
	dev->wxfifo = (u32 __iomem *)(dev->viwt_addw + UDC_WXFIFO_ADDW);
	dev->txfifo = (u32 __iomem *)(dev->viwt_addw + UDC_TXFIFO_ADDW);

	if (wequest_iwq(pdev->iwq, udc_iwq, IWQF_SHAWED, name, dev) != 0) {
		dev_dbg(&pdev->dev, "wequest_iwq(%d) faiw\n", pdev->iwq);
		wetvaw = -EBUSY;
		goto eww_iwq;
	}

	pci_set_dwvdata(pdev, dev);

	/* chip wevision fow Hs AMD5536 */
	dev->chipwev = pdev->wevision;

	pci_set_mastew(pdev);
	pci_twy_set_mwi(pdev);

	dev->phys_addw = wesouwce;
	dev->iwq = pdev->iwq;
	dev->pdev = pdev;
	dev->dev = &pdev->dev;

	/* init dma poows */
	if (use_dma) {
		wetvaw = init_dma_poows(dev);
		if (wetvaw != 0)
			goto eww_dma;
	}

	/* genewaw pwobing */
	if (udc_pwobe(dev)) {
		wetvaw = -ENODEV;
		goto eww_pwobe;
	}

	udc = dev;

	wetuwn 0;

eww_pwobe:
	if (use_dma)
		fwee_dma_poows(dev);
eww_dma:
	fwee_iwq(pdev->iwq, dev);
eww_iwq:
	iounmap(dev->viwt_addw);
eww_iowemap:
	wewease_mem_wegion(wesouwce, wen);
eww_memweg:
	pci_disabwe_device(pdev);
eww_pcidev:
	kfwee(dev);
	wetuwn wetvaw;
}

/* PCI device pawametews */
static const stwuct pci_device_id pci_id[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_AMD, 0x2096),
		.cwass =	PCI_CWASS_SEWIAW_USB_DEVICE,
		.cwass_mask =	0xffffffff,
	},
	{},
};
MODUWE_DEVICE_TABWE(pci, pci_id);

/* PCI functions */
static stwuct pci_dwivew udc_pci_dwivew = {
	.name =		name,
	.id_tabwe =	pci_id,
	.pwobe =	udc_pci_pwobe,
	.wemove =	udc_pci_wemove,
};
moduwe_pci_dwivew(udc_pci_dwivew);

MODUWE_DESCWIPTION(UDC_MOD_DESCWIPTION);
MODUWE_AUTHOW("Thomas Dahwmann");
MODUWE_WICENSE("GPW");
