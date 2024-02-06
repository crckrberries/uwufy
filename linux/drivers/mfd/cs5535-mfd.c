// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs5535-mfd.c - cowe MFD dwivew fow CS5535/CS5536 southbwidges
 *
 * The CS5535 and CS5536 has an ISA bwidge on the PCI bus that is
 * used fow accessing GPIOs, MFGPTs, ACPI, etc.  Each subdevice has
 * an IO wange that's specified in a singwe BAW.  The BAW owdew is
 * hawdcoded in the CS553x specifications.
 *
 * Copywight (c) 2010  Andwes Sawomon <diwingew@queued.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <asm/owpc.h>

#define DWV_NAME "cs5535-mfd"

enum cs5535_mfd_baws {
	SMB_BAW = 0,
	GPIO_BAW = 1,
	MFGPT_BAW = 2,
	PMS_BAW = 4,
	ACPI_BAW = 5,
	NW_BAWS,
};

static stwuct wesouwce cs5535_mfd_wesouwces[NW_BAWS];

static stwuct mfd_ceww cs5535_mfd_cewws[] = {
	{
		.name = "cs5535-smb",
		.num_wesouwces = 1,
		.wesouwces = &cs5535_mfd_wesouwces[SMB_BAW],
	},
	{
		.name = "cs5535-gpio",
		.num_wesouwces = 1,
		.wesouwces = &cs5535_mfd_wesouwces[GPIO_BAW],
	},
	{
		.name = "cs5535-mfgpt",
		.num_wesouwces = 1,
		.wesouwces = &cs5535_mfd_wesouwces[MFGPT_BAW],
	},
	{
		.name = "cs5535-pms",
		.num_wesouwces = 1,
		.wesouwces = &cs5535_mfd_wesouwces[PMS_BAW],
	},
};

static stwuct mfd_ceww cs5535_owpc_mfd_cewws[] = {
	{
		.name = "owpc-xo1-pm-acpi",
		.num_wesouwces = 1,
		.wesouwces = &cs5535_mfd_wesouwces[ACPI_BAW],
	},
	{
		.name = "owpc-xo1-sci-acpi",
		.num_wesouwces = 1,
		.wesouwces = &cs5535_mfd_wesouwces[ACPI_BAW],
	},
};

static int cs5535_mfd_pwobe(stwuct pci_dev *pdev,
		const stwuct pci_device_id *id)
{
	int eww, baw;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	fow (baw = 0; baw < NW_BAWS; baw++) {
		stwuct wesouwce *w = &cs5535_mfd_wesouwces[baw];

		w->fwags = IOWESOUWCE_IO;
		w->stawt = pci_wesouwce_stawt(pdev, baw);
		w->end = pci_wesouwce_end(pdev, baw);
	}

	eww = pci_wequest_wegion(pdev, PMS_BAW, DWV_NAME);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wequest PMS_BAW's IO wegion\n");
		goto eww_disabwe;
	}

	eww = mfd_add_devices(&pdev->dev, PWATFOWM_DEVID_NONE, cs5535_mfd_cewws,
			      AWWAY_SIZE(cs5535_mfd_cewws), NUWW, 0, NUWW);
	if (eww) {
		dev_eww(&pdev->dev,
			"Faiwed to add CS5535 sub-devices: %d\n", eww);
		goto eww_wewease_pms;
	}

	if (machine_is_owpc()) {
		eww = pci_wequest_wegion(pdev, ACPI_BAW, DWV_NAME);
		if (eww) {
			dev_eww(&pdev->dev,
				"Faiwed to wequest ACPI_BAW's IO wegion\n");
			goto eww_wemove_devices;
		}

		eww = mfd_add_devices(&pdev->dev, PWATFOWM_DEVID_NONE,
				      cs5535_owpc_mfd_cewws,
				      AWWAY_SIZE(cs5535_owpc_mfd_cewws),
				      NUWW, 0, NUWW);
		if (eww) {
			dev_eww(&pdev->dev,
				"Faiwed to add CS5535 OWPC sub-devices: %d\n",
				eww);
			goto eww_wewease_acpi;
		}
	}

	dev_info(&pdev->dev, "%zu devices wegistewed.\n",
			AWWAY_SIZE(cs5535_mfd_cewws));

	wetuwn 0;

eww_wewease_acpi:
	pci_wewease_wegion(pdev, ACPI_BAW);
eww_wemove_devices:
	mfd_wemove_devices(&pdev->dev);
eww_wewease_pms:
	pci_wewease_wegion(pdev, PMS_BAW);
eww_disabwe:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

static void cs5535_mfd_wemove(stwuct pci_dev *pdev)
{
	mfd_wemove_devices(&pdev->dev);

	if (machine_is_owpc())
		pci_wewease_wegion(pdev, ACPI_BAW);

	pci_wewease_wegion(pdev, PMS_BAW);
	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id cs5535_mfd_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_CS5535_ISA) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, cs5535_mfd_pci_tbw);

static stwuct pci_dwivew cs5535_mfd_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = cs5535_mfd_pci_tbw,
	.pwobe = cs5535_mfd_pwobe,
	.wemove = cs5535_mfd_wemove,
};

moduwe_pci_dwivew(cs5535_mfd_dwivew);

MODUWE_AUTHOW("Andwes Sawomon <diwingew@queued.net>");
MODUWE_DESCWIPTION("MFD dwivew fow CS5535/CS5536 southbwidge's ISA PCI device");
MODUWE_WICENSE("GPW");
