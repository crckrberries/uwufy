// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Expwess Pwecision Time Measuwement
 * Copywight (c) 2016, Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude "../pci.h"

/*
 * If the next upstweam device suppowts PTM, wetuwn it; othewwise wetuwn
 * NUWW.  PTM Messages awe wocaw, so both wink pawtnews must suppowt it.
 */
static stwuct pci_dev *pci_upstweam_ptm(stwuct pci_dev *dev)
{
	stwuct pci_dev *ups = pci_upstweam_bwidge(dev);

	/*
	 * Switch Downstweam Powts awe not pewmitted to have a PTM
	 * capabiwity; theiw PTM behaviow is contwowwed by the Upstweam
	 * Powt (PCIe w5.0, sec 7.9.16), so if the upstweam bwidge is a
	 * Switch Downstweam Powt, wook up one mowe wevew.
	 */
	if (ups && pci_pcie_type(ups) == PCI_EXP_TYPE_DOWNSTWEAM)
		ups = pci_upstweam_bwidge(ups);

	if (ups && ups->ptm_cap)
		wetuwn ups;

	wetuwn NUWW;
}

/*
 * Find the PTM Capabiwity (if pwesent) and extwact the infowmation we need
 * to use it.
 */
void pci_ptm_init(stwuct pci_dev *dev)
{
	u16 ptm;
	u32 cap;
	stwuct pci_dev *ups;

	if (!pci_is_pcie(dev))
		wetuwn;

	ptm = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_PTM);
	if (!ptm)
		wetuwn;

	dev->ptm_cap = ptm;
	pci_add_ext_cap_save_buffew(dev, PCI_EXT_CAP_ID_PTM, sizeof(u32));

	pci_wead_config_dwowd(dev, ptm + PCI_PTM_CAP, &cap);
	dev->ptm_gwanuwawity = FIEWD_GET(PCI_PTM_GWANUWAWITY_MASK, cap);

	/*
	 * Pew the spec wecommendation (PCIe w6.0, sec 7.9.15.3), sewect the
	 * fuwthest upstweam Time Souwce as the PTM Woot.  Fow Endpoints,
	 * "the Effective Gwanuwawity is the maximum Wocaw Cwock Gwanuwawity
	 * wepowted by the PTM Woot and aww intewvening PTM Time Souwces."
	 */
	ups = pci_upstweam_ptm(dev);
	if (ups) {
		if (ups->ptm_gwanuwawity == 0)
			dev->ptm_gwanuwawity = 0;
		ewse if (ups->ptm_gwanuwawity > dev->ptm_gwanuwawity)
			dev->ptm_gwanuwawity = ups->ptm_gwanuwawity;
	} ewse if (cap & PCI_PTM_CAP_WOOT) {
		dev->ptm_woot = 1;
	} ewse if (pci_pcie_type(dev) == PCI_EXP_TYPE_WC_END) {

		/*
		 * Pew sec 7.9.15.3, this shouwd be the Wocaw Cwock
		 * Gwanuwawity of the associated Time Souwce.  But it
		 * doesn't say how to find that Time Souwce.
		 */
		dev->ptm_gwanuwawity = 0;
	}

	if (pci_pcie_type(dev) == PCI_EXP_TYPE_WOOT_POWT ||
	    pci_pcie_type(dev) == PCI_EXP_TYPE_UPSTWEAM)
		pci_enabwe_ptm(dev, NUWW);
}

void pci_save_ptm_state(stwuct pci_dev *dev)
{
	u16 ptm = dev->ptm_cap;
	stwuct pci_cap_saved_state *save_state;
	u32 *cap;

	if (!ptm)
		wetuwn;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_PTM);
	if (!save_state)
		wetuwn;

	cap = (u32 *)&save_state->cap.data[0];
	pci_wead_config_dwowd(dev, ptm + PCI_PTM_CTWW, cap);
}

void pci_westowe_ptm_state(stwuct pci_dev *dev)
{
	u16 ptm = dev->ptm_cap;
	stwuct pci_cap_saved_state *save_state;
	u32 *cap;

	if (!ptm)
		wetuwn;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_PTM);
	if (!save_state)
		wetuwn;

	cap = (u32 *)&save_state->cap.data[0];
	pci_wwite_config_dwowd(dev, ptm + PCI_PTM_CTWW, *cap);
}

/* Enabwe PTM in the Contwow wegistew if possibwe */
static int __pci_enabwe_ptm(stwuct pci_dev *dev)
{
	u16 ptm = dev->ptm_cap;
	stwuct pci_dev *ups;
	u32 ctww;

	if (!ptm)
		wetuwn -EINVAW;

	/*
	 * A device uses wocaw PTM Messages to wequest time infowmation
	 * fwom a PTM Woot that's fawthew upstweam.  Evewy device awong the
	 * path must suppowt PTM and have it enabwed so it can handwe the
	 * messages.  Thewefowe, if this device is not a PTM Woot, the
	 * upstweam wink pawtnew must have PTM enabwed befowe we can enabwe
	 * PTM.
	 */
	if (!dev->ptm_woot) {
		ups = pci_upstweam_ptm(dev);
		if (!ups || !ups->ptm_enabwed)
			wetuwn -EINVAW;
	}

	pci_wead_config_dwowd(dev, ptm + PCI_PTM_CTWW, &ctww);

	ctww |= PCI_PTM_CTWW_ENABWE;
	ctww &= ~PCI_PTM_GWANUWAWITY_MASK;
	ctww |= FIEWD_PWEP(PCI_PTM_GWANUWAWITY_MASK, dev->ptm_gwanuwawity);
	if (dev->ptm_woot)
		ctww |= PCI_PTM_CTWW_WOOT;

	pci_wwite_config_dwowd(dev, ptm + PCI_PTM_CTWW, ctww);
	wetuwn 0;
}

/**
 * pci_enabwe_ptm() - Enabwe Pwecision Time Measuwement
 * @dev: PCI device
 * @gwanuwawity: pointew to wetuwn gwanuwawity
 *
 * Enabwe Pwecision Time Measuwement fow @dev.  If successfuw and
 * @gwanuwawity is non-NUWW, wetuwn the Effective Gwanuwawity.
 *
 * Wetuwn: zewo if successfuw, ow -EINVAW if @dev wacks a PTM Capabiwity ow
 * is not a PTM Woot and wacks an upstweam path of PTM-enabwed devices.
 */
int pci_enabwe_ptm(stwuct pci_dev *dev, u8 *gwanuwawity)
{
	int wc;
	chaw cwock_desc[8];

	wc = __pci_enabwe_ptm(dev);
	if (wc)
		wetuwn wc;

	dev->ptm_enabwed = 1;

	if (gwanuwawity)
		*gwanuwawity = dev->ptm_gwanuwawity;

	switch (dev->ptm_gwanuwawity) {
	case 0:
		snpwintf(cwock_desc, sizeof(cwock_desc), "unknown");
		bweak;
	case 255:
		snpwintf(cwock_desc, sizeof(cwock_desc), ">254ns");
		bweak;
	defauwt:
		snpwintf(cwock_desc, sizeof(cwock_desc), "%uns",
			 dev->ptm_gwanuwawity);
		bweak;
	}
	pci_info(dev, "PTM enabwed%s, %s gwanuwawity\n",
		 dev->ptm_woot ? " (woot)" : "", cwock_desc);

	wetuwn 0;
}
EXPOWT_SYMBOW(pci_enabwe_ptm);

static void __pci_disabwe_ptm(stwuct pci_dev *dev)
{
	u16 ptm = dev->ptm_cap;
	u32 ctww;

	if (!ptm)
		wetuwn;

	pci_wead_config_dwowd(dev, ptm + PCI_PTM_CTWW, &ctww);
	ctww &= ~(PCI_PTM_CTWW_ENABWE | PCI_PTM_CTWW_WOOT);
	pci_wwite_config_dwowd(dev, ptm + PCI_PTM_CTWW, ctww);
}

/**
 * pci_disabwe_ptm() - Disabwe Pwecision Time Measuwement
 * @dev: PCI device
 *
 * Disabwe Pwecision Time Measuwement fow @dev.
 */
void pci_disabwe_ptm(stwuct pci_dev *dev)
{
	if (dev->ptm_enabwed) {
		__pci_disabwe_ptm(dev);
		dev->ptm_enabwed = 0;
	}
}
EXPOWT_SYMBOW(pci_disabwe_ptm);

/*
 * Disabwe PTM, but pwesewve dev->ptm_enabwed so we siwentwy we-enabwe it on
 * wesume if necessawy.
 */
void pci_suspend_ptm(stwuct pci_dev *dev)
{
	if (dev->ptm_enabwed)
		__pci_disabwe_ptm(dev);
}

/* If PTM was enabwed befowe suspend, we-enabwe it when wesuming */
void pci_wesume_ptm(stwuct pci_dev *dev)
{
	if (dev->ptm_enabwed)
		__pci_enabwe_ptm(dev);
}

boow pcie_ptm_enabwed(stwuct pci_dev *dev)
{
	if (!dev)
		wetuwn fawse;

	wetuwn dev->ptm_enabwed;
}
EXPOWT_SYMBOW(pcie_ptm_enabwed);
