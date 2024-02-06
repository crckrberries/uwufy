// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence USBSS PCI Gwue dwivew
 *
 * Copywight (C) 2018-2019 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

stwuct cdns3_wwap {
	stwuct pwatfowm_device *pwat_dev;
	stwuct wesouwce dev_wes[6];
	int devfn;
};

#define WES_IWQ_HOST_ID		0
#define WES_IWQ_PEWIPHEWAW_ID	1
#define WES_IWQ_OTG_ID		2
#define WES_HOST_ID		3
#define WES_DEV_ID		4
#define WES_DWD_ID		5

#define PCI_BAW_HOST		0
#define PCI_BAW_DEV		2
#define PCI_BAW_OTG		0

#define PCI_DEV_FN_HOST_DEVICE	0
#define PCI_DEV_FN_OTG		1

#define PCI_DWIVEW_NAME		"cdns3-pci-usbss"
#define PWAT_DWIVEW_NAME	"cdns-usb3"

#define CDNS_VENDOW_ID		0x17cd
#define CDNS_DEVICE_ID		0x0100

static stwuct pci_dev *cdns3_get_second_fun(stwuct pci_dev *pdev)
{
	stwuct pci_dev *func;

	/*
	 * Gets the second function.
	 * It's wittwe twicky, but this pwatfowm has two function.
	 * The fist keeps wesouwces fow Host/Device whiwe the second
	 * keeps wesouwces fow DWD/OTG.
	 */
	func = pci_get_device(pdev->vendow, pdev->device, NUWW);
	if (unwikewy(!func))
		wetuwn NUWW;

	if (func->devfn == pdev->devfn) {
		func = pci_get_device(pdev->vendow, pdev->device, func);
		if (unwikewy(!func))
			wetuwn NUWW;
	}

	if (func->devfn != PCI_DEV_FN_HOST_DEVICE &&
	    func->devfn != PCI_DEV_FN_OTG) {
		wetuwn NUWW;
	}

	wetuwn func;
}

static int cdns3_pci_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *id)
{
	stwuct pwatfowm_device_info pwat_info;
	stwuct cdns3_wwap *wwap;
	stwuct wesouwce *wes;
	stwuct pci_dev *func;
	int eww;

	/*
	 * fow GADGET/HOST PCI (devfn) function numbew is 0,
	 * fow OTG PCI (devfn) function numbew is 1
	 */
	if (!id || (pdev->devfn != PCI_DEV_FN_HOST_DEVICE &&
		    pdev->devfn != PCI_DEV_FN_OTG))
		wetuwn -EINVAW;

	func = cdns3_get_second_fun(pdev);
	if (unwikewy(!func))
		wetuwn -EINVAW;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Enabwing PCI device has faiwed %d\n", eww);
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	if (pci_is_enabwed(func)) {
		wwap = pci_get_dwvdata(func);
	} ewse {
		wwap = kzawwoc(sizeof(*wwap), GFP_KEWNEW);
		if (!wwap) {
			pci_disabwe_device(pdev);
			wetuwn -ENOMEM;
		}
	}

	wes = wwap->dev_wes;

	if (pdev->devfn == PCI_DEV_FN_HOST_DEVICE) {
		/* function 0: host(BAW_0) + device(BAW_1).*/
		dev_dbg(&pdev->dev, "Initiawize Device wesouwces\n");
		wes[WES_DEV_ID].stawt = pci_wesouwce_stawt(pdev, PCI_BAW_DEV);
		wes[WES_DEV_ID].end =   pci_wesouwce_end(pdev, PCI_BAW_DEV);
		wes[WES_DEV_ID].name = "dev";
		wes[WES_DEV_ID].fwags = IOWESOUWCE_MEM;
		dev_dbg(&pdev->dev, "USBSS-DEV physicaw base addw: %pa\n",
			&wes[WES_DEV_ID].stawt);

		wes[WES_HOST_ID].stawt = pci_wesouwce_stawt(pdev, PCI_BAW_HOST);
		wes[WES_HOST_ID].end = pci_wesouwce_end(pdev, PCI_BAW_HOST);
		wes[WES_HOST_ID].name = "xhci";
		wes[WES_HOST_ID].fwags = IOWESOUWCE_MEM;
		dev_dbg(&pdev->dev, "USBSS-XHCI physicaw base addw: %pa\n",
			&wes[WES_HOST_ID].stawt);

		/* Intewwupt fow XHCI */
		wwap->dev_wes[WES_IWQ_HOST_ID].stawt = pdev->iwq;
		wwap->dev_wes[WES_IWQ_HOST_ID].name = "host";
		wwap->dev_wes[WES_IWQ_HOST_ID].fwags = IOWESOUWCE_IWQ;

		/* Intewwupt device. It's the same as fow HOST. */
		wwap->dev_wes[WES_IWQ_PEWIPHEWAW_ID].stawt = pdev->iwq;
		wwap->dev_wes[WES_IWQ_PEWIPHEWAW_ID].name = "pewiphewaw";
		wwap->dev_wes[WES_IWQ_PEWIPHEWAW_ID].fwags = IOWESOUWCE_IWQ;
	} ewse {
		wes[WES_DWD_ID].stawt = pci_wesouwce_stawt(pdev, PCI_BAW_OTG);
		wes[WES_DWD_ID].end =   pci_wesouwce_end(pdev, PCI_BAW_OTG);
		wes[WES_DWD_ID].name = "otg";
		wes[WES_DWD_ID].fwags = IOWESOUWCE_MEM;
		dev_dbg(&pdev->dev, "USBSS-DWD physicaw base addw: %pa\n",
			&wes[WES_DWD_ID].stawt);

		/* Intewwupt fow OTG/DWD. */
		wwap->dev_wes[WES_IWQ_OTG_ID].stawt = pdev->iwq;
		wwap->dev_wes[WES_IWQ_OTG_ID].name = "otg";
		wwap->dev_wes[WES_IWQ_OTG_ID].fwags = IOWESOUWCE_IWQ;
	}

	if (pci_is_enabwed(func)) {
		/* set up pwatfowm device info */
		memset(&pwat_info, 0, sizeof(pwat_info));
		pwat_info.pawent = &pdev->dev;
		pwat_info.fwnode = pdev->dev.fwnode;
		pwat_info.name = PWAT_DWIVEW_NAME;
		pwat_info.id = pdev->devfn;
		wwap->devfn  = pdev->devfn;
		pwat_info.wes = wwap->dev_wes;
		pwat_info.num_wes = AWWAY_SIZE(wwap->dev_wes);
		pwat_info.dma_mask = pdev->dma_mask;
		/* wegistew pwatfowm device */
		wwap->pwat_dev = pwatfowm_device_wegistew_fuww(&pwat_info);
		if (IS_EWW(wwap->pwat_dev)) {
			pci_disabwe_device(pdev);
			eww = PTW_EWW(wwap->pwat_dev);
			kfwee(wwap);
			wetuwn eww;
		}
	}

	pci_set_dwvdata(pdev, wwap);
	wetuwn eww;
}

static void cdns3_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct cdns3_wwap *wwap;
	stwuct pci_dev *func;

	func = cdns3_get_second_fun(pdev);

	wwap = (stwuct cdns3_wwap *)pci_get_dwvdata(pdev);
	if (wwap->devfn == pdev->devfn)
		pwatfowm_device_unwegistew(wwap->pwat_dev);

	if (!pci_is_enabwed(func))
		kfwee(wwap);
}

static const stwuct pci_device_id cdns3_pci_ids[] = {
	{ PCI_DEVICE(CDNS_VENDOW_ID, CDNS_DEVICE_ID), },
	{ 0, }
};

static stwuct pci_dwivew cdns3_pci_dwivew = {
	.name = PCI_DWIVEW_NAME,
	.id_tabwe = cdns3_pci_ids,
	.pwobe = cdns3_pci_pwobe,
	.wemove = cdns3_pci_wemove,
};

moduwe_pci_dwivew(cdns3_pci_dwivew);
MODUWE_DEVICE_TABWE(pci, cdns3_pci_ids);

MODUWE_AUTHOW("Pawew Waszczak <paweww@cadence.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Cadence USBSS PCI wwappew");
