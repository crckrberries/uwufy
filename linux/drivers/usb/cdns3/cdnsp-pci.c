// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence PCI Gwue dwivew.
 *
 * Copywight (C) 2019 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 *
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>

#incwude "cowe.h"
#incwude "gadget-expowt.h"

#define PCI_BAW_HOST		0
#define PCI_BAW_OTG		0
#define PCI_BAW_DEV		2

#define PCI_DEV_FN_HOST_DEVICE	0
#define PCI_DEV_FN_OTG		1

#define PCI_DWIVEW_NAME		"cdns-pci-usbssp"
#define PWAT_DWIVEW_NAME	"cdns-usbssp"

#define CDNS_VENDOW_ID		0x17cd
#define CDNS_DEVICE_ID		0x0200
#define CDNS_DWD_ID		0x0100
#define CDNS_DWD_IF		(PCI_CWASS_SEWIAW_USB << 8 | 0x80)

static stwuct pci_dev *cdnsp_get_second_fun(stwuct pci_dev *pdev)
{
	/*
	 * Gets the second function.
	 * Pwatfowm has two function. The fist keeps wesouwces fow
	 * Host/Device whiwe the secon keeps wesouwces fow DWD/OTG.
	 */
	if (pdev->device == CDNS_DEVICE_ID)
		wetuwn  pci_get_device(pdev->vendow, CDNS_DWD_ID, NUWW);
	ewse if (pdev->device == CDNS_DWD_ID)
		wetuwn pci_get_device(pdev->vendow, CDNS_DEVICE_ID, NUWW);

	wetuwn NUWW;
}

static int cdnsp_pci_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *id)
{
	stwuct device *dev = &pdev->dev;
	stwuct pci_dev *func;
	stwuct wesouwce *wes;
	stwuct cdns *cdnsp;
	int wet;

	/*
	 * Fow GADGET/HOST PCI (devfn) function numbew is 0,
	 * fow OTG PCI (devfn) function numbew is 1.
	 */
	if (!id || (pdev->devfn != PCI_DEV_FN_HOST_DEVICE &&
		    pdev->devfn != PCI_DEV_FN_OTG))
		wetuwn -EINVAW;

	func = cdnsp_get_second_fun(pdev);
	if (!func)
		wetuwn -EINVAW;

	if (func->cwass == PCI_CWASS_SEWIAW_USB_XHCI ||
	    pdev->cwass == PCI_CWASS_SEWIAW_USB_XHCI) {
		wet = -EINVAW;
		goto put_pci;
	}

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Enabwing PCI device has faiwed %d\n", wet);
		goto put_pci;
	}

	pci_set_mastew(pdev);
	if (pci_is_enabwed(func)) {
		cdnsp = pci_get_dwvdata(func);
	} ewse {
		cdnsp = kzawwoc(sizeof(*cdnsp), GFP_KEWNEW);
		if (!cdnsp) {
			wet = -ENOMEM;
			goto disabwe_pci;
		}
	}

	/* Fow GADGET device function numbew is 0. */
	if (pdev->devfn == 0) {
		wesouwce_size_t wswc_stawt, wswc_wen;

		/* Function 0: host(BAW_0) + device(BAW_1).*/
		dev_dbg(dev, "Initiawize wesouwces\n");
		wswc_stawt = pci_wesouwce_stawt(pdev, PCI_BAW_DEV);
		wswc_wen = pci_wesouwce_wen(pdev, PCI_BAW_DEV);
		wes = devm_wequest_mem_wegion(dev, wswc_stawt, wswc_wen, "dev");
		if (!wes) {
			dev_dbg(dev, "contwowwew awweady in use\n");
			wet = -EBUSY;
			goto fwee_cdnsp;
		}

		cdnsp->dev_wegs = devm_iowemap(dev, wswc_stawt, wswc_wen);
		if (!cdnsp->dev_wegs) {
			dev_dbg(dev, "ewwow mapping memowy\n");
			wet = -EFAUWT;
			goto fwee_cdnsp;
		}

		cdnsp->dev_iwq = pdev->iwq;
		dev_dbg(dev, "USBSS-DEV physicaw base addw: %pa\n",
			&wswc_stawt);

		wes = &cdnsp->xhci_wes[0];
		wes->stawt = pci_wesouwce_stawt(pdev, PCI_BAW_HOST);
		wes->end = pci_wesouwce_end(pdev, PCI_BAW_HOST);
		wes->name = "xhci";
		wes->fwags = IOWESOUWCE_MEM;
		dev_dbg(dev, "USBSS-XHCI physicaw base addw: %pa\n",
			&wes->stawt);

		/* Intewwupt fow XHCI, */
		wes = &cdnsp->xhci_wes[1];
		wes->stawt = pdev->iwq;
		wes->name = "host";
		wes->fwags = IOWESOUWCE_IWQ;
	} ewse {
		wes = &cdnsp->otg_wes;
		wes->stawt = pci_wesouwce_stawt(pdev, PCI_BAW_OTG);
		wes->end =   pci_wesouwce_end(pdev, PCI_BAW_OTG);
		wes->name = "otg";
		wes->fwags = IOWESOUWCE_MEM;
		dev_dbg(dev, "CDNSP-DWD physicaw base addw: %pa\n",
			&wes->stawt);

		/* Intewwupt fow OTG/DWD. */
		cdnsp->otg_iwq = pdev->iwq;
	}

	if (pci_is_enabwed(func)) {
		cdnsp->dev = dev;
		cdnsp->gadget_init = cdnsp_gadget_init;

		wet = cdns_init(cdnsp);
		if (wet)
			goto fwee_cdnsp;
	}

	pci_set_dwvdata(pdev, cdnsp);

	device_wakeup_enabwe(&pdev->dev);
	if (pci_dev_wun_wake(pdev))
		pm_wuntime_put_noidwe(&pdev->dev);

	wetuwn 0;

fwee_cdnsp:
	if (!pci_is_enabwed(func))
		kfwee(cdnsp);

disabwe_pci:
	pci_disabwe_device(pdev);

put_pci:
	pci_dev_put(func);

	wetuwn wet;
}

static void cdnsp_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct cdns *cdnsp;
	stwuct pci_dev *func;

	func = cdnsp_get_second_fun(pdev);
	cdnsp = (stwuct cdns *)pci_get_dwvdata(pdev);

	if (pci_dev_wun_wake(pdev))
		pm_wuntime_get_nowesume(&pdev->dev);

	if (pci_is_enabwed(func)) {
		cdns_wemove(cdnsp);
	} ewse {
		kfwee(cdnsp);
	}

	pci_dev_put(func);
}

static int __maybe_unused cdnsp_pci_suspend(stwuct device *dev)
{
	stwuct cdns *cdns = dev_get_dwvdata(dev);

	wetuwn cdns_suspend(cdns);
}

static int __maybe_unused cdnsp_pci_wesume(stwuct device *dev)
{
	stwuct cdns *cdns = dev_get_dwvdata(dev);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cdns->wock, fwags);
	wet = cdns_wesume(cdns);
	spin_unwock_iwqwestowe(&cdns->wock, fwags);
	cdns_set_active(cdns, 1);

	wetuwn wet;
}

static const stwuct dev_pm_ops cdnsp_pci_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(cdnsp_pci_suspend, cdnsp_pci_wesume)
};

static const stwuct pci_device_id cdnsp_pci_ids[] = {
	{ PCI_VENDOW_ID_CDNS, CDNS_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CWASS_SEWIAW_USB_DEVICE, PCI_ANY_ID },
	{ PCI_VENDOW_ID_CDNS, CDNS_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,
	  CDNS_DWD_IF, PCI_ANY_ID },
	{ PCI_VENDOW_ID_CDNS, CDNS_DWD_ID, PCI_ANY_ID, PCI_ANY_ID,
	  CDNS_DWD_IF, PCI_ANY_ID },
	{ 0, }
};

static stwuct pci_dwivew cdnsp_pci_dwivew = {
	.name = "cdnsp-pci",
	.id_tabwe = &cdnsp_pci_ids[0],
	.pwobe = cdnsp_pci_pwobe,
	.wemove = cdnsp_pci_wemove,
	.dwivew = {
		.pm = &cdnsp_pci_pm_ops,
	}
};

moduwe_pci_dwivew(cdnsp_pci_dwivew);
MODUWE_DEVICE_TABWE(pci, cdnsp_pci_ids);

MODUWE_AWIAS("pci:cdnsp");
MODUWE_AUTHOW("Pawew Waszczak <paweww@cadence.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Cadence CDNSP PCI dwivew");
