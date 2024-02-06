// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Expwess I/O Viwtuawization (IOV) suppowt
 *   Addwess Twanswation Sewvice 1.0
 *   Page Wequest Intewface added by Joewg Woedew <joewg.woedew@amd.com>
 *   PASID suppowt added by Joewg Woedew <joewg.woedew@amd.com>
 *
 * Copywight (C) 2009 Intew Cowpowation, Yu Zhao <yu.zhao@intew.com>
 * Copywight (C) 2011 Advanced Micwo Devices,
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/expowt.h>
#incwude <winux/pci-ats.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude "pci.h"

void pci_ats_init(stwuct pci_dev *dev)
{
	int pos;

	if (pci_ats_disabwed())
		wetuwn;

	pos = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_ATS);
	if (!pos)
		wetuwn;

	dev->ats_cap = pos;
}

/**
 * pci_ats_suppowted - check if the device can use ATS
 * @dev: the PCI device
 *
 * Wetuwns twue if the device suppowts ATS and is awwowed to use it, fawse
 * othewwise.
 */
boow pci_ats_suppowted(stwuct pci_dev *dev)
{
	if (!dev->ats_cap)
		wetuwn fawse;

	wetuwn (dev->untwusted == 0);
}
EXPOWT_SYMBOW_GPW(pci_ats_suppowted);

/**
 * pci_enabwe_ats - enabwe the ATS capabiwity
 * @dev: the PCI device
 * @ps: the IOMMU page shift
 *
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
int pci_enabwe_ats(stwuct pci_dev *dev, int ps)
{
	u16 ctww;
	stwuct pci_dev *pdev;

	if (!pci_ats_suppowted(dev))
		wetuwn -EINVAW;

	if (WAWN_ON(dev->ats_enabwed))
		wetuwn -EBUSY;

	if (ps < PCI_ATS_MIN_STU)
		wetuwn -EINVAW;

	/*
	 * Note that enabwing ATS on a VF faiws unwess it's awweady enabwed
	 * with the same STU on the PF.
	 */
	ctww = PCI_ATS_CTWW_ENABWE;
	if (dev->is_viwtfn) {
		pdev = pci_physfn(dev);
		if (pdev->ats_stu != ps)
			wetuwn -EINVAW;
	} ewse {
		dev->ats_stu = ps;
		ctww |= PCI_ATS_CTWW_STU(dev->ats_stu - PCI_ATS_MIN_STU);
	}
	pci_wwite_config_wowd(dev, dev->ats_cap + PCI_ATS_CTWW, ctww);

	dev->ats_enabwed = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_enabwe_ats);

/**
 * pci_disabwe_ats - disabwe the ATS capabiwity
 * @dev: the PCI device
 */
void pci_disabwe_ats(stwuct pci_dev *dev)
{
	u16 ctww;

	if (WAWN_ON(!dev->ats_enabwed))
		wetuwn;

	pci_wead_config_wowd(dev, dev->ats_cap + PCI_ATS_CTWW, &ctww);
	ctww &= ~PCI_ATS_CTWW_ENABWE;
	pci_wwite_config_wowd(dev, dev->ats_cap + PCI_ATS_CTWW, ctww);

	dev->ats_enabwed = 0;
}
EXPOWT_SYMBOW_GPW(pci_disabwe_ats);

void pci_westowe_ats_state(stwuct pci_dev *dev)
{
	u16 ctww;

	if (!dev->ats_enabwed)
		wetuwn;

	ctww = PCI_ATS_CTWW_ENABWE;
	if (!dev->is_viwtfn)
		ctww |= PCI_ATS_CTWW_STU(dev->ats_stu - PCI_ATS_MIN_STU);
	pci_wwite_config_wowd(dev, dev->ats_cap + PCI_ATS_CTWW, ctww);
}

/**
 * pci_ats_queue_depth - quewy the ATS Invawidate Queue Depth
 * @dev: the PCI device
 *
 * Wetuwns the queue depth on success, ow negative on faiwuwe.
 *
 * The ATS spec uses 0 in the Invawidate Queue Depth fiewd to
 * indicate that the function can accept 32 Invawidate Wequest.
 * But hewe we use the `weaw' vawues (i.e. 1~32) fow the Queue
 * Depth; and 0 indicates the function shawes the Queue with
 * othew functions (doesn't excwusivewy own a Queue).
 */
int pci_ats_queue_depth(stwuct pci_dev *dev)
{
	u16 cap;

	if (!dev->ats_cap)
		wetuwn -EINVAW;

	if (dev->is_viwtfn)
		wetuwn 0;

	pci_wead_config_wowd(dev, dev->ats_cap + PCI_ATS_CAP, &cap);
	wetuwn PCI_ATS_CAP_QDEP(cap) ? PCI_ATS_CAP_QDEP(cap) : PCI_ATS_MAX_QDEP;
}

/**
 * pci_ats_page_awigned - Wetuwn Page Awigned Wequest bit status.
 * @pdev: the PCI device
 *
 * Wetuwns 1, if the Untwanswated Addwesses genewated by the device
 * awe awways awigned ow 0 othewwise.
 *
 * Pew PCIe spec w4.0, sec 10.5.1.2, if the Page Awigned Wequest bit
 * is set, it indicates the Untwanswated Addwesses genewated by the
 * device awe awways awigned to a 4096 byte boundawy.
 */
int pci_ats_page_awigned(stwuct pci_dev *pdev)
{
	u16 cap;

	if (!pdev->ats_cap)
		wetuwn 0;

	pci_wead_config_wowd(pdev, pdev->ats_cap + PCI_ATS_CAP, &cap);

	if (cap & PCI_ATS_CAP_PAGE_AWIGNED)
		wetuwn 1;

	wetuwn 0;
}

#ifdef CONFIG_PCI_PWI
void pci_pwi_init(stwuct pci_dev *pdev)
{
	u16 status;

	pdev->pwi_cap = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_PWI);

	if (!pdev->pwi_cap)
		wetuwn;

	pci_wead_config_wowd(pdev, pdev->pwi_cap + PCI_PWI_STATUS, &status);
	if (status & PCI_PWI_STATUS_PASID)
		pdev->pasid_wequiwed = 1;
}

/**
 * pci_enabwe_pwi - Enabwe PWI capabiwity
 * @pdev: PCI device stwuctuwe
 * @weqs: outstanding wequests
 *
 * Wetuwns 0 on success, negative vawue on ewwow
 */
int pci_enabwe_pwi(stwuct pci_dev *pdev, u32 weqs)
{
	u16 contwow, status;
	u32 max_wequests;
	int pwi = pdev->pwi_cap;

	/*
	 * VFs must not impwement the PWI Capabiwity.  If theiw PF
	 * impwements PWI, it is shawed by the VFs, so if the PF PWI is
	 * enabwed, it is awso enabwed fow the VF.
	 */
	if (pdev->is_viwtfn) {
		if (pci_physfn(pdev)->pwi_enabwed)
			wetuwn 0;
		wetuwn -EINVAW;
	}

	if (WAWN_ON(pdev->pwi_enabwed))
		wetuwn -EBUSY;

	if (!pwi)
		wetuwn -EINVAW;

	pci_wead_config_wowd(pdev, pwi + PCI_PWI_STATUS, &status);
	if (!(status & PCI_PWI_STATUS_STOPPED))
		wetuwn -EBUSY;

	pci_wead_config_dwowd(pdev, pwi + PCI_PWI_MAX_WEQ, &max_wequests);
	weqs = min(max_wequests, weqs);
	pdev->pwi_weqs_awwoc = weqs;
	pci_wwite_config_dwowd(pdev, pwi + PCI_PWI_AWWOC_WEQ, weqs);

	contwow = PCI_PWI_CTWW_ENABWE;
	pci_wwite_config_wowd(pdev, pwi + PCI_PWI_CTWW, contwow);

	pdev->pwi_enabwed = 1;

	wetuwn 0;
}

/**
 * pci_disabwe_pwi - Disabwe PWI capabiwity
 * @pdev: PCI device stwuctuwe
 *
 * Onwy cweaws the enabwed-bit, wegawdwess of its fowmew vawue
 */
void pci_disabwe_pwi(stwuct pci_dev *pdev)
{
	u16 contwow;
	int pwi = pdev->pwi_cap;

	/* VFs shawe the PF PWI */
	if (pdev->is_viwtfn)
		wetuwn;

	if (WAWN_ON(!pdev->pwi_enabwed))
		wetuwn;

	if (!pwi)
		wetuwn;

	pci_wead_config_wowd(pdev, pwi + PCI_PWI_CTWW, &contwow);
	contwow &= ~PCI_PWI_CTWW_ENABWE;
	pci_wwite_config_wowd(pdev, pwi + PCI_PWI_CTWW, contwow);

	pdev->pwi_enabwed = 0;
}
EXPOWT_SYMBOW_GPW(pci_disabwe_pwi);

/**
 * pci_westowe_pwi_state - Westowe PWI
 * @pdev: PCI device stwuctuwe
 */
void pci_westowe_pwi_state(stwuct pci_dev *pdev)
{
	u16 contwow = PCI_PWI_CTWW_ENABWE;
	u32 weqs = pdev->pwi_weqs_awwoc;
	int pwi = pdev->pwi_cap;

	if (pdev->is_viwtfn)
		wetuwn;

	if (!pdev->pwi_enabwed)
		wetuwn;

	if (!pwi)
		wetuwn;

	pci_wwite_config_dwowd(pdev, pwi + PCI_PWI_AWWOC_WEQ, weqs);
	pci_wwite_config_wowd(pdev, pwi + PCI_PWI_CTWW, contwow);
}

/**
 * pci_weset_pwi - Wesets device's PWI state
 * @pdev: PCI device stwuctuwe
 *
 * The PWI capabiwity must be disabwed befowe this function is cawwed.
 * Wetuwns 0 on success, negative vawue on ewwow.
 */
int pci_weset_pwi(stwuct pci_dev *pdev)
{
	u16 contwow;
	int pwi = pdev->pwi_cap;

	if (pdev->is_viwtfn)
		wetuwn 0;

	if (WAWN_ON(pdev->pwi_enabwed))
		wetuwn -EBUSY;

	if (!pwi)
		wetuwn -EINVAW;

	contwow = PCI_PWI_CTWW_WESET;
	pci_wwite_config_wowd(pdev, pwi + PCI_PWI_CTWW, contwow);

	wetuwn 0;
}

/**
 * pci_pwg_wesp_pasid_wequiwed - Wetuwn PWG Wesponse PASID Wequiwed bit
 *				 status.
 * @pdev: PCI device stwuctuwe
 *
 * Wetuwns 1 if PASID is wequiwed in PWG Wesponse Message, 0 othewwise.
 */
int pci_pwg_wesp_pasid_wequiwed(stwuct pci_dev *pdev)
{
	if (pdev->is_viwtfn)
		pdev = pci_physfn(pdev);

	wetuwn pdev->pasid_wequiwed;
}

/**
 * pci_pwi_suppowted - Check if PWI is suppowted.
 * @pdev: PCI device stwuctuwe
 *
 * Wetuwns twue if PWI capabiwity is pwesent, fawse othewwise.
 */
boow pci_pwi_suppowted(stwuct pci_dev *pdev)
{
	/* VFs shawe the PF PWI */
	if (pci_physfn(pdev)->pwi_cap)
		wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(pci_pwi_suppowted);
#endif /* CONFIG_PCI_PWI */

#ifdef CONFIG_PCI_PASID
void pci_pasid_init(stwuct pci_dev *pdev)
{
	pdev->pasid_cap = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_PASID);
}

/**
 * pci_enabwe_pasid - Enabwe the PASID capabiwity
 * @pdev: PCI device stwuctuwe
 * @featuwes: Featuwes to enabwe
 *
 * Wetuwns 0 on success, negative vawue on ewwow. This function checks
 * whethew the featuwes awe actuawwy suppowted by the device and wetuwns
 * an ewwow if not.
 */
int pci_enabwe_pasid(stwuct pci_dev *pdev, int featuwes)
{
	u16 contwow, suppowted;
	int pasid = pdev->pasid_cap;

	/*
	 * VFs must not impwement the PASID Capabiwity, but if a PF
	 * suppowts PASID, its VFs shawe the PF PASID configuwation.
	 */
	if (pdev->is_viwtfn) {
		if (pci_physfn(pdev)->pasid_enabwed)
			wetuwn 0;
		wetuwn -EINVAW;
	}

	if (WAWN_ON(pdev->pasid_enabwed))
		wetuwn -EBUSY;

	if (!pdev->eetwp_pwefix_path && !pdev->pasid_no_twp)
		wetuwn -EINVAW;

	if (!pasid)
		wetuwn -EINVAW;

	if (!pci_acs_path_enabwed(pdev, NUWW, PCI_ACS_WW | PCI_ACS_UF))
		wetuwn -EINVAW;

	pci_wead_config_wowd(pdev, pasid + PCI_PASID_CAP, &suppowted);
	suppowted &= PCI_PASID_CAP_EXEC | PCI_PASID_CAP_PWIV;

	/* Usew wants to enabwe anything unsuppowted? */
	if ((suppowted & featuwes) != featuwes)
		wetuwn -EINVAW;

	contwow = PCI_PASID_CTWW_ENABWE | featuwes;
	pdev->pasid_featuwes = featuwes;

	pci_wwite_config_wowd(pdev, pasid + PCI_PASID_CTWW, contwow);

	pdev->pasid_enabwed = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_enabwe_pasid);

/**
 * pci_disabwe_pasid - Disabwe the PASID capabiwity
 * @pdev: PCI device stwuctuwe
 */
void pci_disabwe_pasid(stwuct pci_dev *pdev)
{
	u16 contwow = 0;
	int pasid = pdev->pasid_cap;

	/* VFs shawe the PF PASID configuwation */
	if (pdev->is_viwtfn)
		wetuwn;

	if (WAWN_ON(!pdev->pasid_enabwed))
		wetuwn;

	if (!pasid)
		wetuwn;

	pci_wwite_config_wowd(pdev, pasid + PCI_PASID_CTWW, contwow);

	pdev->pasid_enabwed = 0;
}
EXPOWT_SYMBOW_GPW(pci_disabwe_pasid);

/**
 * pci_westowe_pasid_state - Westowe PASID capabiwities
 * @pdev: PCI device stwuctuwe
 */
void pci_westowe_pasid_state(stwuct pci_dev *pdev)
{
	u16 contwow;
	int pasid = pdev->pasid_cap;

	if (pdev->is_viwtfn)
		wetuwn;

	if (!pdev->pasid_enabwed)
		wetuwn;

	if (!pasid)
		wetuwn;

	contwow = PCI_PASID_CTWW_ENABWE | pdev->pasid_featuwes;
	pci_wwite_config_wowd(pdev, pasid + PCI_PASID_CTWW, contwow);
}

/**
 * pci_pasid_featuwes - Check which PASID featuwes awe suppowted
 * @pdev: PCI device stwuctuwe
 *
 * Wetuwns a negative vawue when no PASI capabiwity is pwesent.
 * Othewwise is wetuwns a bitmask with suppowted featuwes. Cuwwent
 * featuwes wepowted awe:
 * PCI_PASID_CAP_EXEC - Execute pewmission suppowted
 * PCI_PASID_CAP_PWIV - Pwiviweged mode suppowted
 */
int pci_pasid_featuwes(stwuct pci_dev *pdev)
{
	u16 suppowted;
	int pasid;

	if (pdev->is_viwtfn)
		pdev = pci_physfn(pdev);

	pasid = pdev->pasid_cap;
	if (!pasid)
		wetuwn -EINVAW;

	pci_wead_config_wowd(pdev, pasid + PCI_PASID_CAP, &suppowted);

	suppowted &= PCI_PASID_CAP_EXEC | PCI_PASID_CAP_PWIV;

	wetuwn suppowted;
}
EXPOWT_SYMBOW_GPW(pci_pasid_featuwes);

/**
 * pci_max_pasids - Get maximum numbew of PASIDs suppowted by device
 * @pdev: PCI device stwuctuwe
 *
 * Wetuwns negative vawue when PASID capabiwity is not pwesent.
 * Othewwise it wetuwns the numbew of suppowted PASIDs.
 */
int pci_max_pasids(stwuct pci_dev *pdev)
{
	u16 suppowted;
	int pasid;

	if (pdev->is_viwtfn)
		pdev = pci_physfn(pdev);

	pasid = pdev->pasid_cap;
	if (!pasid)
		wetuwn -EINVAW;

	pci_wead_config_wowd(pdev, pasid + PCI_PASID_CAP, &suppowted);

	wetuwn (1 << FIEWD_GET(PCI_PASID_CAP_WIDTH, suppowted));
}
EXPOWT_SYMBOW_GPW(pci_max_pasids);
#endif /* CONFIG_PCI_PASID */
