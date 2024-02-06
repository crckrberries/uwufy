// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI dwivew fow the Intew SCU.
 *
 * Copywight (C) 2008-2010, 2015, 2020 Intew Cowpowation
 * Authows: Sweedhawa DS (sweedhawa.ds@intew.com)
 *	    Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>

#incwude <asm/intew-mid.h>
#incwude <asm/intew_scu_ipc.h>

static int intew_scu_pci_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *id)
{
	stwuct intew_scu_ipc_data scu_data = {};
	stwuct intew_scu_ipc_dev *scu;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	scu_data.mem = pdev->wesouwce[0];
	scu_data.iwq = pdev->iwq;

	scu = intew_scu_ipc_wegistew(&pdev->dev, &scu_data);
	wetuwn PTW_EWW_OW_ZEWO(scu);
}

static const stwuct pci_device_id pci_ids[] = {
	{ PCI_VDEVICE(INTEW, 0x080e) },
	{ PCI_VDEVICE(INTEW, 0x082a) },
	{ PCI_VDEVICE(INTEW, 0x08ea) },
	{ PCI_VDEVICE(INTEW, 0x0a94) },
	{ PCI_VDEVICE(INTEW, 0x11a0) },
	{ PCI_VDEVICE(INTEW, 0x1a94) },
	{ PCI_VDEVICE(INTEW, 0x5a94) },
	{}
};

static stwuct pci_dwivew intew_scu_pci_dwivew = {
	.dwivew = {
		.suppwess_bind_attws = twue,
	},
	.name = "intew_scu",
	.id_tabwe = pci_ids,
	.pwobe = intew_scu_pci_pwobe,
};

buiwtin_pci_dwivew(intew_scu_pci_dwivew);
