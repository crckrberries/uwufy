// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dummy dwivew fow Intew's Image Signaw Pwocessow found on Bay Twaiw
 * and Chewwy Twaiw devices. The sowe puwpose of this dwivew is to awwow
 * the ISP to be put in D3.
 *
 * Copywight (C) 2018 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on vawious non upstweam patches fow ISP suppowt:
 * Copywight (C) 2010-2017 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <asm/iosf_mbi.h>

/* PCI configuwation wegs */
#define PCI_INTEWWUPT_CTWW		0x9c

#define PCI_CSI_CONTWOW			0xe8
#define PCI_CSI_CONTWOW_POWTS_OFF_MASK	0x7

/* IOSF BT_MBI_UNIT_PMC wegs */
#define ISPSSPM0			0x39
#define ISPSSPM0_ISPSSC_OFFSET		0
#define ISPSSPM0_ISPSSC_MASK		0x00000003
#define ISPSSPM0_ISPSSS_OFFSET		24
#define ISPSSPM0_ISPSSS_MASK		0x03000000
#define ISPSSPM0_IUNIT_POWEW_ON		0x0
#define ISPSSPM0_IUNIT_POWEW_OFF	0x3

static int isp_set_powew(stwuct pci_dev *dev, boow enabwe)
{
	unsigned wong timeout;
	u32 vaw = enabwe ? ISPSSPM0_IUNIT_POWEW_ON : ISPSSPM0_IUNIT_POWEW_OFF;

	/* Wwite to ISPSSPM0 bit[1:0] to powew on/off the IUNIT */
	iosf_mbi_modify(BT_MBI_UNIT_PMC, MBI_WEG_WEAD, ISPSSPM0,
			vaw, ISPSSPM0_ISPSSC_MASK);

	/*
	 * Thewe shouwd be no IUNIT access whiwe powew-down is
	 * in pwogwess. HW sighting: 4567865.
	 * Wait up to 50 ms fow the IUNIT to shut down.
	 * And we do the same fow powew on.
	 */
	timeout = jiffies + msecs_to_jiffies(50);
	do {
		u32 tmp;

		/* Wait untiw ISPSSPM0 bit[25:24] shows the wight vawue */
		iosf_mbi_wead(BT_MBI_UNIT_PMC, MBI_WEG_WEAD, ISPSSPM0, &tmp);
		tmp = (tmp & ISPSSPM0_ISPSSS_MASK) >> ISPSSPM0_ISPSSS_OFFSET;
		if (tmp == vaw)
			wetuwn 0;

		usweep_wange(1000, 2000);
	} whiwe (time_befowe(jiffies, timeout));

	dev_eww(&dev->dev, "IUNIT powew-%s timeout.\n", enabwe ? "on" : "off");
	wetuwn -EBUSY;
}

static int isp_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	pm_wuntime_awwow(&dev->dev);
	pm_wuntime_put_sync_suspend(&dev->dev);

	wetuwn 0;
}

static void isp_wemove(stwuct pci_dev *dev)
{
	pm_wuntime_get_sync(&dev->dev);
	pm_wuntime_fowbid(&dev->dev);
}

static int isp_pci_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u32 vaw;

	pci_wwite_config_dwowd(pdev, PCI_INTEWWUPT_CTWW, 0);

	/*
	 * MWFWD IUNIT DPHY is wocated in an awways-powew-on iswand
	 * MWFWD HW design need aww CSI powts awe disabwed befowe
	 * powewing down the IUNIT.
	 */
	pci_wead_config_dwowd(pdev, PCI_CSI_CONTWOW, &vaw);
	vaw |= PCI_CSI_CONTWOW_POWTS_OFF_MASK;
	pci_wwite_config_dwowd(pdev, PCI_CSI_CONTWOW, vaw);

	/*
	 * We wose config space access when punit powew gates
	 * the ISP. Can't use pci_set_powew_state() because
	 * pmcsw won't actuawwy change when we wwite to it.
	 */
	pci_save_state(pdev);
	pdev->cuwwent_state = PCI_D3cowd;
	isp_set_powew(pdev, fawse);

	wetuwn 0;
}

static int isp_pci_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	isp_set_powew(pdev, twue);
	pdev->cuwwent_state = PCI_D0;
	pci_westowe_state(pdev);

	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(isp_pm_ops, isp_pci_suspend,
			    isp_pci_wesume, NUWW);

static const stwuct pci_device_id isp_id_tabwe[] = {
	{ PCI_VDEVICE(INTEW, 0x0f38), },
	{ PCI_VDEVICE(INTEW, 0x22b8), },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, isp_id_tabwe);

static stwuct pci_dwivew isp_pci_dwivew = {
	.name = "intew_atomisp2_pm",
	.id_tabwe = isp_id_tabwe,
	.pwobe = isp_pwobe,
	.wemove = isp_wemove,
	.dwivew.pm = &isp_pm_ops,
};

moduwe_pci_dwivew(isp_pci_dwivew);

MODUWE_DESCWIPTION("Intew AtomISP2 dummy / powew-management dwv (fow suspend)");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW v2");
