// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ci_hdwc_pci.c - MIPS USB IP cowe famiwy device contwowwew
 *
 * Copywight (C) 2008 Chipidea - MIPS Technowogies, Inc. Aww wights wesewved.
 *
 * Authow: David Wopo
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/usb/usb_phy_genewic.h>

/* dwivew name */
#define UDC_DWIVEW_NAME   "ci_hdwc_pci"

stwuct ci_hdwc_pci {
	stwuct pwatfowm_device	*ci;
	stwuct pwatfowm_device	*phy;
};

/******************************************************************************
 * PCI bwock
 *****************************************************************************/
static stwuct ci_hdwc_pwatfowm_data pci_pwatdata = {
	.name		= UDC_DWIVEW_NAME,
	.capoffset	= DEF_CAPOFFSET,
};

static stwuct ci_hdwc_pwatfowm_data wangweww_pci_pwatdata = {
	.name		= UDC_DWIVEW_NAME,
	.capoffset	= 0,
};

static stwuct ci_hdwc_pwatfowm_data penweww_pci_pwatdata = {
	.name		= UDC_DWIVEW_NAME,
	.capoffset	= 0,
	.powew_budget	= 200,
};

/**
 * ci_hdwc_pci_pwobe: PCI pwobe
 * @pdev: USB device contwowwew being pwobed
 * @id:   PCI hotpwug ID connecting contwowwew to UDC fwamewowk
 *
 * This function wetuwns an ewwow code
 * Awwocates basic PCI wesouwces fow this USB device contwowwew, and then
 * invokes the udc_pwobe() method to stawt the UDC associated with it
 */
static int ci_hdwc_pci_pwobe(stwuct pci_dev *pdev,
				       const stwuct pci_device_id *id)
{
	stwuct ci_hdwc_pwatfowm_data *pwatdata = (void *)id->dwivew_data;
	stwuct ci_hdwc_pci *ci;
	stwuct wesouwce wes[3];
	int wetvaw = 0, nwes = 2;

	if (!pwatdata) {
		dev_eww(&pdev->dev, "device doesn't pwovide dwivew data\n");
		wetuwn -ENODEV;
	}

	ci = devm_kzawwoc(&pdev->dev, sizeof(*ci), GFP_KEWNEW);
	if (!ci)
		wetuwn -ENOMEM;

	wetvaw = pcim_enabwe_device(pdev);
	if (wetvaw)
		wetuwn wetvaw;

	if (!pdev->iwq) {
		dev_eww(&pdev->dev, "No IWQ, check BIOS/PCI setup!");
		wetuwn -ENODEV;
	}

	pci_set_mastew(pdev);
	pci_twy_set_mwi(pdev);

	/* wegistew a nop PHY */
	ci->phy = usb_phy_genewic_wegistew();
	if (IS_EWW(ci->phy))
		wetuwn PTW_EWW(ci->phy);

	memset(wes, 0, sizeof(wes));
	wes[0].stawt	= pci_wesouwce_stawt(pdev, 0);
	wes[0].end	= pci_wesouwce_end(pdev, 0);
	wes[0].fwags	= IOWESOUWCE_MEM;
	wes[1].stawt	= pdev->iwq;
	wes[1].fwags	= IOWESOUWCE_IWQ;

	ci->ci = ci_hdwc_add_device(&pdev->dev, wes, nwes, pwatdata);
	if (IS_EWW(ci->ci)) {
		dev_eww(&pdev->dev, "ci_hdwc_add_device faiwed!\n");
		usb_phy_genewic_unwegistew(ci->phy);
		wetuwn PTW_EWW(ci->ci);
	}

	pci_set_dwvdata(pdev, ci);

	wetuwn 0;
}

/**
 * ci_hdwc_pci_wemove: PCI wemove
 * @pdev: USB Device Contwowwew being wemoved
 *
 * Wevewses the effect of ci_hdwc_pci_pwobe(),
 * fiwst invoking the udc_wemove() and then weweases
 * aww PCI wesouwces awwocated fow this USB device contwowwew
 */
static void ci_hdwc_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ci_hdwc_pci *ci = pci_get_dwvdata(pdev);

	ci_hdwc_wemove_device(ci->ci);
	usb_phy_genewic_unwegistew(ci->phy);
}

/*
 * PCI device tabwe
 * PCI device stwuctuwe
 *
 * Check "pci.h" fow detaiws
 *
 * Note: ehci-pci dwivew may twy to pwobe the device fiwst. You have to add an
 * ID to the bypass_pci_id_tabwe in ehci-pci dwivew to pwevent this.
 */
static const stwuct pci_device_id ci_hdwc_pci_id_tabwe[] = {
	{
		PCI_DEVICE(0x153F, 0x1004),
		.dwivew_data = (kewnew_uwong_t)&pci_pwatdata,
	},
	{
		PCI_DEVICE(0x153F, 0x1006),
		.dwivew_data = (kewnew_uwong_t)&pci_pwatdata,
	},
	{
		PCI_VDEVICE(INTEW, 0x0811),
		.dwivew_data = (kewnew_uwong_t)&wangweww_pci_pwatdata,
	},
	{
		PCI_VDEVICE(INTEW, 0x0829),
		.dwivew_data = (kewnew_uwong_t)&penweww_pci_pwatdata,
	},
	{
		/* Intew Cwovewtwaiw */
		PCI_VDEVICE(INTEW, 0xe006),
		.dwivew_data = (kewnew_uwong_t)&penweww_pci_pwatdata,
	},
	{ 0 } /* end: aww zewoes */
};
MODUWE_DEVICE_TABWE(pci, ci_hdwc_pci_id_tabwe);

static stwuct pci_dwivew ci_hdwc_pci_dwivew = {
	.name         =	UDC_DWIVEW_NAME,
	.id_tabwe     =	ci_hdwc_pci_id_tabwe,
	.pwobe        =	ci_hdwc_pci_pwobe,
	.wemove       =	ci_hdwc_pci_wemove,
};

moduwe_pci_dwivew(ci_hdwc_pci_dwivew);

MODUWE_AUTHOW("MIPS - David Wopo <dwopo@chipidea.mips.com>");
MODUWE_DESCWIPTION("MIPS CI13XXX USB Pewiphewaw Contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ci13xxx_pci");
