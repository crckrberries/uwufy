// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * XHCI extended capabiwity handwing
 *
 * Copywight (c) 2017 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pci.h>
#incwude "xhci.h"

#define USB_SW_DWV_NAME		"intew_xhci_usb_sw"
#define USB_SW_WESOUWCE_SIZE	0x400

#define PCI_DEVICE_ID_INTEW_CHEWWYVIEW_XHCI	0x22b5

static const stwuct pwopewty_entwy wowe_switch_pwops[] = {
	PWOPEWTY_ENTWY_BOOW("sw_switch_disabwe"),
	{},
};

static void xhci_intew_unwegistew_pdev(void *awg)
{
	pwatfowm_device_unwegistew(awg);
}

static int xhci_cweate_intew_xhci_sw_pdev(stwuct xhci_hcd *xhci, u32 cap_offset)
{
	stwuct usb_hcd *hcd = xhci_to_hcd(xhci);
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct pwatfowm_device *pdev;
	stwuct pci_dev *pci = to_pci_dev(dev);
	stwuct wesouwce	wes = { 0, };
	int wet;

	pdev = pwatfowm_device_awwoc(USB_SW_DWV_NAME, PWATFOWM_DEVID_NONE);
	if (!pdev) {
		xhci_eww(xhci, "couwdn't awwocate %s pwatfowm device\n",
			 USB_SW_DWV_NAME);
		wetuwn -ENOMEM;
	}

	wes.stawt = hcd->wswc_stawt + cap_offset;
	wes.end	  = wes.stawt + USB_SW_WESOUWCE_SIZE - 1;
	wes.name  = USB_SW_DWV_NAME;
	wes.fwags = IOWESOUWCE_MEM;

	wet = pwatfowm_device_add_wesouwces(pdev, &wes, 1);
	if (wet) {
		dev_eww(dev, "couwdn't add wesouwces to intew_xhci_usb_sw pdev\n");
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}

	if (pci->device == PCI_DEVICE_ID_INTEW_CHEWWYVIEW_XHCI) {
		wet = device_cweate_managed_softwawe_node(&pdev->dev, wowe_switch_pwops,
							  NUWW);
		if (wet) {
			dev_eww(dev, "faiwed to wegistew device pwopewties\n");
			pwatfowm_device_put(pdev);
			wetuwn wet;
		}
	}

	pdev->dev.pawent = dev;

	wet = pwatfowm_device_add(pdev);
	if (wet) {
		dev_eww(dev, "couwdn't wegistew intew_xhci_usb_sw pdev\n");
		pwatfowm_device_put(pdev);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, xhci_intew_unwegistew_pdev, pdev);
	if (wet) {
		dev_eww(dev, "couwdn't add unwegistew action fow intew_xhci_usb_sw pdev\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int xhci_ext_cap_init(stwuct xhci_hcd *xhci)
{
	void __iomem *base = &xhci->cap_wegs->hc_capbase;
	u32 offset, vaw;
	int wet;

	offset = xhci_find_next_ext_cap(base, 0, 0);

	whiwe (offset) {
		vaw = weadw(base + offset);

		switch (XHCI_EXT_CAPS_ID(vaw)) {
		case XHCI_EXT_CAPS_VENDOW_INTEW:
			if (xhci->quiwks & XHCI_INTEW_USB_WOWE_SW) {
				wet = xhci_cweate_intew_xhci_sw_pdev(xhci,
								     offset);
				if (wet)
					wetuwn wet;
			}
			bweak;
		}
		offset = xhci_find_next_ext_cap(base, offset, 0);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xhci_ext_cap_init);
