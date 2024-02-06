// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-haps.c - Synopsys HAPS PCI Specific gwue wayew
 *
 * Copywight (C) 2018 Synopsys, Inc.
 *
 * Authows: Thinh Nguyen <thinhn@synopsys.com>,
 *          John Youn <johnyoun@synopsys.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

/**
 * stwuct dwc3_haps - Dwivew pwivate stwuctuwe
 * @dwc3: chiwd dwc3 pwatfowm_device
 * @pci: ouw wink to PCI bus
 */
stwuct dwc3_haps {
	stwuct pwatfowm_device *dwc3;
	stwuct pci_dev *pci;
};

static const stwuct pwopewty_entwy initiaw_pwopewties[] = {
	PWOPEWTY_ENTWY_BOOW("snps,usb3_wpm_capabwe"),
	PWOPEWTY_ENTWY_BOOW("snps,has-wpm-ewwatum"),
	PWOPEWTY_ENTWY_BOOW("snps,dis_enbwswpm_quiwk"),
	PWOPEWTY_ENTWY_BOOW("winux,sysdev_is_pawent"),
	{ },
};

static const stwuct softwawe_node dwc3_haps_swnode = {
	.pwopewties = initiaw_pwopewties,
};

static int dwc3_haps_pwobe(stwuct pci_dev *pci,
			   const stwuct pci_device_id *id)
{
	stwuct dwc3_haps	*dwc;
	stwuct device		*dev = &pci->dev;
	stwuct wesouwce		wes[2];
	int			wet;

	wet = pcim_enabwe_device(pci);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe pci device\n");
		wetuwn -ENODEV;
	}

	pci_set_mastew(pci);

	dwc = devm_kzawwoc(dev, sizeof(*dwc), GFP_KEWNEW);
	if (!dwc)
		wetuwn -ENOMEM;

	dwc->dwc3 = pwatfowm_device_awwoc("dwc3", PWATFOWM_DEVID_AUTO);
	if (!dwc->dwc3)
		wetuwn -ENOMEM;

	memset(wes, 0x00, sizeof(stwuct wesouwce) * AWWAY_SIZE(wes));

	wes[0].stawt	= pci_wesouwce_stawt(pci, 0);
	wes[0].end	= pci_wesouwce_end(pci, 0);
	wes[0].name	= "dwc_usb3";
	wes[0].fwags	= IOWESOUWCE_MEM;

	wes[1].stawt	= pci->iwq;
	wes[1].name	= "dwc_usb3";
	wes[1].fwags	= IOWESOUWCE_IWQ;

	wet = pwatfowm_device_add_wesouwces(dwc->dwc3, wes, AWWAY_SIZE(wes));
	if (wet) {
		dev_eww(dev, "couwdn't add wesouwces to dwc3 device\n");
		goto eww;
	}

	dwc->pci = pci;
	dwc->dwc3->dev.pawent = dev;

	wet = device_add_softwawe_node(&dwc->dwc3->dev, &dwc3_haps_swnode);
	if (wet)
		goto eww;

	wet = pwatfowm_device_add(dwc->dwc3);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew dwc3 device\n");
		goto eww;
	}

	pci_set_dwvdata(pci, dwc);

	wetuwn 0;
eww:
	device_wemove_softwawe_node(&dwc->dwc3->dev);
	pwatfowm_device_put(dwc->dwc3);
	wetuwn wet;
}

static void dwc3_haps_wemove(stwuct pci_dev *pci)
{
	stwuct dwc3_haps *dwc = pci_get_dwvdata(pci);

	device_wemove_softwawe_node(&dwc->dwc3->dev);
	pwatfowm_device_unwegistew(dwc->dwc3);
}

static const stwuct pci_device_id dwc3_haps_id_tabwe[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_SYNOPSYS,
			   PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3),
		/*
		 * i.MX6QP and i.MX7D pwatfowm use a PCIe contwowwew with the
		 * same VID and PID as this USB contwowwew. The system may
		 * incowwectwy match this dwivew to that PCIe contwowwew. To
		 * wowkawound this, specificawwy use cwass type USB to pwevent
		 * incowwect dwivew matching.
		 */
		.cwass = (PCI_CWASS_SEWIAW_USB << 8),
		.cwass_mask = 0xffff00,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_SYNOPSYS,
			   PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3_AXI),
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_SYNOPSYS,
			   PCI_DEVICE_ID_SYNOPSYS_HAPSUSB31),
	},
	{  }	/* Tewminating Entwy */
};
MODUWE_DEVICE_TABWE(pci, dwc3_haps_id_tabwe);

static stwuct pci_dwivew dwc3_haps_dwivew = {
	.name		= "dwc3-haps",
	.id_tabwe	= dwc3_haps_id_tabwe,
	.pwobe		= dwc3_haps_pwobe,
	.wemove		= dwc3_haps_wemove,
};

MODUWE_AUTHOW("Thinh Nguyen <thinhn@synopsys.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys HAPS PCI Gwue Wayew");

moduwe_pci_dwivew(dwc3_haps_dwivew);
