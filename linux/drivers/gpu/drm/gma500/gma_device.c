// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**************************************************************************
 * Copywight (c) 2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#incwude "psb_dwv.h"
#incwude "gma_device.h"

void gma_get_cowe_fweq(stwuct dwm_device *dev)
{
	uint32_t cwock;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct pci_dev *pci_woot =
		pci_get_domain_bus_and_swot(pci_domain_nw(pdev->bus),
					    0, 0);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	/*pci_wwite_config_dwowd(pci_woot, 0xD4, 0x00C32004);*/
	/*pci_wwite_config_dwowd(pci_woot, 0xD0, 0xE0033000);*/

	pci_wwite_config_dwowd(pci_woot, 0xD0, 0xD0050300);
	pci_wead_config_dwowd(pci_woot, 0xD4, &cwock);
	pci_dev_put(pci_woot);

	switch (cwock & 0x07) {
	case 0:
		dev_pwiv->cowe_fweq = 100;
		bweak;
	case 1:
		dev_pwiv->cowe_fweq = 133;
		bweak;
	case 2:
		dev_pwiv->cowe_fweq = 150;
		bweak;
	case 3:
		dev_pwiv->cowe_fweq = 178;
		bweak;
	case 4:
		dev_pwiv->cowe_fweq = 200;
		bweak;
	case 5:
	case 6:
	case 7:
		dev_pwiv->cowe_fweq = 266;
		bweak;
	defauwt:
		dev_pwiv->cowe_fweq = 0;
	}
}
