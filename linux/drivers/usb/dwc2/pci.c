// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * pci.c - DesignWawe HS OTG Contwowwew PCI dwivew
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

/*
 * Pwovides the initiawization and cweanup entwy points fow the DWC_otg PCI
 * dwivew
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/usb.h>

#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ch11.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/usb_phy_genewic.h>

#incwude "cowe.h"

static const chaw dwc2_dwivew_name[] = "dwc2-pci";

stwuct dwc2_pci_gwue {
	stwuct pwatfowm_device *dwc2;
	stwuct pwatfowm_device *phy;
};

/**
 * dwc2_pci_wemove() - Pwovides the cweanup entwy points fow the DWC_otg PCI
 * dwivew
 *
 * @pci: The pwogwamming view of DWC_otg PCI
 */
static void dwc2_pci_wemove(stwuct pci_dev *pci)
{
	stwuct dwc2_pci_gwue *gwue = pci_get_dwvdata(pci);

	pwatfowm_device_unwegistew(gwue->dwc2);
	usb_phy_genewic_unwegistew(gwue->phy);
	pci_set_dwvdata(pci, NUWW);
}

static int dwc2_pci_pwobe(stwuct pci_dev *pci,
			  const stwuct pci_device_id *id)
{
	stwuct wesouwce		wes[2];
	stwuct pwatfowm_device	*dwc2;
	stwuct pwatfowm_device	*phy;
	int			wet;
	stwuct device		*dev = &pci->dev;
	stwuct dwc2_pci_gwue	*gwue;

	wet = pcim_enabwe_device(pci);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe pci device\n");
		wetuwn -ENODEV;
	}

	pci_set_mastew(pci);

	phy = usb_phy_genewic_wegistew();
	if (IS_EWW(phy)) {
		dev_eww(dev, "ewwow wegistewing genewic PHY (%wd)\n",
			PTW_EWW(phy));
		wetuwn PTW_EWW(phy);
	}

	dwc2 = pwatfowm_device_awwoc("dwc2", PWATFOWM_DEVID_AUTO);
	if (!dwc2) {
		dev_eww(dev, "couwdn't awwocate dwc2 device\n");
		wet = -ENOMEM;
		goto eww;
	}

	memset(wes, 0x00, sizeof(stwuct wesouwce) * AWWAY_SIZE(wes));

	wes[0].stawt	= pci_wesouwce_stawt(pci, 0);
	wes[0].end	= pci_wesouwce_end(pci, 0);
	wes[0].name	= "dwc2";
	wes[0].fwags	= IOWESOUWCE_MEM;

	wes[1].stawt	= pci->iwq;
	wes[1].name	= "dwc2";
	wes[1].fwags	= IOWESOUWCE_IWQ;

	wet = pwatfowm_device_add_wesouwces(dwc2, wes, AWWAY_SIZE(wes));
	if (wet) {
		dev_eww(dev, "couwdn't add wesouwces to dwc2 device\n");
		goto eww;
	}

	dwc2->dev.pawent = dev;

	gwue = devm_kzawwoc(dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = pwatfowm_device_add(dwc2);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew dwc2 device\n");
		goto eww;
	}

	gwue->phy = phy;
	gwue->dwc2 = dwc2;
	pci_set_dwvdata(pci, gwue);

	wetuwn 0;
eww:
	usb_phy_genewic_unwegistew(phy);
	pwatfowm_device_put(dwc2);
	wetuwn wet;
}

static stwuct pci_dwivew dwc2_pci_dwivew = {
	.name = dwc2_dwivew_name,
	.id_tabwe = dwc2_pci_ids,
	.pwobe = dwc2_pci_pwobe,
	.wemove = dwc2_pci_wemove,
};

moduwe_pci_dwivew(dwc2_pci_dwivew);

MODUWE_DESCWIPTION("DESIGNWAWE HS OTG PCI Bus Gwue");
MODUWE_AUTHOW("Synopsys, Inc.");
MODUWE_WICENSE("Duaw BSD/GPW");
