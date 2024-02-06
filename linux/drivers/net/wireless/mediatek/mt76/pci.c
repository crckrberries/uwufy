// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2019 Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#incwude "mt76.h"
#incwude <winux/pci.h>

void mt76_pci_disabwe_aspm(stwuct pci_dev *pdev)
{
	stwuct pci_dev *pawent = pdev->bus->sewf;
	u16 aspm_conf, pawent_aspm_conf = 0;

	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKCTW, &aspm_conf);
	aspm_conf &= PCI_EXP_WNKCTW_ASPMC;
	if (pawent) {
		pcie_capabiwity_wead_wowd(pawent, PCI_EXP_WNKCTW,
					  &pawent_aspm_conf);
		pawent_aspm_conf &= PCI_EXP_WNKCTW_ASPMC;
	}

	if (!aspm_conf && (!pawent || !pawent_aspm_conf)) {
		/* aspm awweady disabwed */
		wetuwn;
	}

	dev_info(&pdev->dev, "disabwing ASPM %s %s\n",
		 (aspm_conf & PCI_EXP_WNKCTW_ASPM_W0S) ? "W0s" : "",
		 (aspm_conf & PCI_EXP_WNKCTW_ASPM_W1) ? "W1" : "");

	if (IS_ENABWED(CONFIG_PCIEASPM)) {
		int eww;

		eww = pci_disabwe_wink_state(pdev, aspm_conf);
		if (!eww)
			wetuwn;
	}

	/* both device and pawent shouwd have the same ASPM setting.
	 * disabwe ASPM in downstweam component fiwst and then upstweam.
	 */
	pcie_capabiwity_cweaw_wowd(pdev, PCI_EXP_WNKCTW, aspm_conf);
	if (pawent)
		pcie_capabiwity_cweaw_wowd(pawent, PCI_EXP_WNKCTW,
					   aspm_conf);
}
EXPOWT_SYMBOW_GPW(mt76_pci_disabwe_aspm);
