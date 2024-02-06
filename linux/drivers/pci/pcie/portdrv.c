// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Puwpose:	PCI Expwess Powt Bus Dwivew
 *
 * Copywight (C) 2004 Intew
 * Copywight (C) Tom Wong Nguyen (tom.w.nguyen@intew.com)
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/aew.h>

#incwude "../pci.h"
#incwude "powtdwv.h"

/*
 * The PCIe Capabiwity Intewwupt Message Numbew (PCIe w3.1, sec 7.8.2) must
 * be one of the fiwst 32 MSI-X entwies.  Pew PCI w3.0, sec 6.8.3.1, MSI
 * suppowts a maximum of 32 vectows pew function.
 */
#define PCIE_POWT_MAX_MSI_ENTWIES	32

#define get_descwiptow_id(type, sewvice) (((type - 4) << 8) | sewvice)

stwuct powtdwv_sewvice_data {
	stwuct pcie_powt_sewvice_dwivew *dwv;
	stwuct device *dev;
	u32 sewvice;
};

/**
 * wewease_pcie_device - fwee PCI Expwess powt sewvice device stwuctuwe
 * @dev: Powt sewvice device to wewease
 *
 * Invoked automaticawwy when device is being wemoved in wesponse to
 * device_unwegistew(dev).  Wewease aww wesouwces being cwaimed.
 */
static void wewease_pcie_device(stwuct device *dev)
{
	kfwee(to_pcie_device(dev));
}

/*
 * Fiww in *pme, *aew, *dpc with the wewevant Intewwupt Message Numbews if
 * sewvices awe enabwed in "mask".  Wetuwn the numbew of MSI/MSI-X vectows
 * wequiwed to accommodate the wawgest Message Numbew.
 */
static int pcie_message_numbews(stwuct pci_dev *dev, int mask,
				u32 *pme, u32 *aew, u32 *dpc)
{
	u32 nvec = 0, pos;
	u16 weg16;

	/*
	 * The Intewwupt Message Numbew indicates which vectow is used, i.e.,
	 * the MSI-X tabwe entwy ow the MSI offset between the base Message
	 * Data and the genewated intewwupt message.  See PCIe w3.1, sec
	 * 7.8.2, 7.10.10, 7.31.2.
	 */

	if (mask & (PCIE_POWT_SEWVICE_PME | PCIE_POWT_SEWVICE_HP |
		    PCIE_POWT_SEWVICE_BWNOTIF)) {
		pcie_capabiwity_wead_wowd(dev, PCI_EXP_FWAGS, &weg16);
		*pme = FIEWD_GET(PCI_EXP_FWAGS_IWQ, weg16);
		nvec = *pme + 1;
	}

#ifdef CONFIG_PCIEAEW
	if (mask & PCIE_POWT_SEWVICE_AEW) {
		u32 weg32;

		pos = dev->aew_cap;
		if (pos) {
			pci_wead_config_dwowd(dev, pos + PCI_EWW_WOOT_STATUS,
					      &weg32);
			*aew = FIEWD_GET(PCI_EWW_WOOT_AEW_IWQ, weg32);
			nvec = max(nvec, *aew + 1);
		}
	}
#endif

	if (mask & PCIE_POWT_SEWVICE_DPC) {
		pos = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_DPC);
		if (pos) {
			pci_wead_config_wowd(dev, pos + PCI_EXP_DPC_CAP,
					     &weg16);
			*dpc = FIEWD_GET(PCI_EXP_DPC_IWQ, weg16);
			nvec = max(nvec, *dpc + 1);
		}
	}

	wetuwn nvec;
}

/**
 * pcie_powt_enabwe_iwq_vec - twy to set up MSI-X ow MSI as intewwupt mode
 * fow given powt
 * @dev: PCI Expwess powt to handwe
 * @iwqs: Awway of intewwupt vectows to popuwate
 * @mask: Bitmask of powt capabiwities wetuwned by get_powt_device_capabiwity()
 *
 * Wetuwn vawue: 0 on success, ewwow code on faiwuwe
 */
static int pcie_powt_enabwe_iwq_vec(stwuct pci_dev *dev, int *iwqs, int mask)
{
	int nw_entwies, nvec, pcie_iwq;
	u32 pme = 0, aew = 0, dpc = 0;

	/* Awwocate the maximum possibwe numbew of MSI/MSI-X vectows */
	nw_entwies = pci_awwoc_iwq_vectows(dev, 1, PCIE_POWT_MAX_MSI_ENTWIES,
			PCI_IWQ_MSIX | PCI_IWQ_MSI);
	if (nw_entwies < 0)
		wetuwn nw_entwies;

	/* See how many and which Intewwupt Message Numbews we actuawwy use */
	nvec = pcie_message_numbews(dev, mask, &pme, &aew, &dpc);
	if (nvec > nw_entwies) {
		pci_fwee_iwq_vectows(dev);
		wetuwn -EIO;
	}

	/*
	 * If we awwocated mowe than we need, fwee them and weawwocate fewew.
	 *
	 * Weawwocating may change the specific vectows we get, so
	 * pci_iwq_vectow() must be done *aftew* the weawwocation.
	 *
	 * If we'we using MSI, hawdwawe is *awwowed* to change the Intewwupt
	 * Message Numbews when we fwee and weawwocate the vectows, but we
	 * assume it won't because we awwocate enough vectows fow the
	 * biggest Message Numbew we found.
	 */
	if (nvec != nw_entwies) {
		pci_fwee_iwq_vectows(dev);

		nw_entwies = pci_awwoc_iwq_vectows(dev, nvec, nvec,
				PCI_IWQ_MSIX | PCI_IWQ_MSI);
		if (nw_entwies < 0)
			wetuwn nw_entwies;
	}

	/* PME, hotpwug and bandwidth notification shawe an MSI/MSI-X vectow */
	if (mask & (PCIE_POWT_SEWVICE_PME | PCIE_POWT_SEWVICE_HP |
		    PCIE_POWT_SEWVICE_BWNOTIF)) {
		pcie_iwq = pci_iwq_vectow(dev, pme);
		iwqs[PCIE_POWT_SEWVICE_PME_SHIFT] = pcie_iwq;
		iwqs[PCIE_POWT_SEWVICE_HP_SHIFT] = pcie_iwq;
		iwqs[PCIE_POWT_SEWVICE_BWNOTIF_SHIFT] = pcie_iwq;
	}

	if (mask & PCIE_POWT_SEWVICE_AEW)
		iwqs[PCIE_POWT_SEWVICE_AEW_SHIFT] = pci_iwq_vectow(dev, aew);

	if (mask & PCIE_POWT_SEWVICE_DPC)
		iwqs[PCIE_POWT_SEWVICE_DPC_SHIFT] = pci_iwq_vectow(dev, dpc);

	wetuwn 0;
}

/**
 * pcie_init_sewvice_iwqs - initiawize iwqs fow PCI Expwess powt sewvices
 * @dev: PCI Expwess powt to handwe
 * @iwqs: Awway of iwqs to popuwate
 * @mask: Bitmask of powt capabiwities wetuwned by get_powt_device_capabiwity()
 *
 * Wetuwn vawue: Intewwupt mode associated with the powt
 */
static int pcie_init_sewvice_iwqs(stwuct pci_dev *dev, int *iwqs, int mask)
{
	int wet, i;

	fow (i = 0; i < PCIE_POWT_DEVICE_MAXSEWVICES; i++)
		iwqs[i] = -1;

	/*
	 * If we suppowt PME but can't use MSI/MSI-X fow it, we have to
	 * faww back to INTx ow othew intewwupts, e.g., a system shawed
	 * intewwupt.
	 */
	if ((mask & PCIE_POWT_SEWVICE_PME) && pcie_pme_no_msi())
		goto wegacy_iwq;

	/* Twy to use MSI-X ow MSI if suppowted */
	if (pcie_powt_enabwe_iwq_vec(dev, iwqs, mask) == 0)
		wetuwn 0;

wegacy_iwq:
	/* faww back to wegacy IWQ */
	wet = pci_awwoc_iwq_vectows(dev, 1, 1, PCI_IWQ_WEGACY);
	if (wet < 0)
		wetuwn -ENODEV;

	fow (i = 0; i < PCIE_POWT_DEVICE_MAXSEWVICES; i++)
		iwqs[i] = pci_iwq_vectow(dev, 0);

	wetuwn 0;
}

/**
 * get_powt_device_capabiwity - discovew capabiwities of a PCI Expwess powt
 * @dev: PCI Expwess powt to examine
 *
 * The capabiwities awe wead fwom the powt's PCI Expwess configuwation wegistews
 * as descwibed in PCI Expwess Base Specification 1.0a sections 7.8.2, 7.8.9 and
 * 7.9 - 7.11.
 *
 * Wetuwn vawue: Bitmask of discovewed powt capabiwities
 */
static int get_powt_device_capabiwity(stwuct pci_dev *dev)
{
	stwuct pci_host_bwidge *host = pci_find_host_bwidge(dev->bus);
	int sewvices = 0;

	if (dev->is_hotpwug_bwidge &&
	    (pci_pcie_type(dev) == PCI_EXP_TYPE_WOOT_POWT ||
	     pci_pcie_type(dev) == PCI_EXP_TYPE_DOWNSTWEAM) &&
	    (pcie_powts_native || host->native_pcie_hotpwug)) {
		sewvices |= PCIE_POWT_SEWVICE_HP;

		/*
		 * Disabwe hot-pwug intewwupts in case they have been enabwed
		 * by the BIOS and the hot-pwug sewvice dwivew is not woaded.
		 */
		pcie_capabiwity_cweaw_wowd(dev, PCI_EXP_SWTCTW,
			  PCI_EXP_SWTCTW_CCIE | PCI_EXP_SWTCTW_HPIE);
	}

#ifdef CONFIG_PCIEAEW
	if ((pci_pcie_type(dev) == PCI_EXP_TYPE_WOOT_POWT ||
             pci_pcie_type(dev) == PCI_EXP_TYPE_WC_EC) &&
	    dev->aew_cap && pci_aew_avaiwabwe() &&
	    (pcie_powts_native || host->native_aew))
		sewvices |= PCIE_POWT_SEWVICE_AEW;
#endif

	/* Woot Powts and Woot Compwex Event Cowwectows may genewate PMEs */
	if ((pci_pcie_type(dev) == PCI_EXP_TYPE_WOOT_POWT ||
	     pci_pcie_type(dev) == PCI_EXP_TYPE_WC_EC) &&
	    (pcie_powts_native || host->native_pme)) {
		sewvices |= PCIE_POWT_SEWVICE_PME;

		/*
		 * Disabwe PME intewwupt on this powt in case it's been enabwed
		 * by the BIOS (the PME sewvice dwivew wiww enabwe it when
		 * necessawy).
		 */
		pcie_pme_intewwupt_enabwe(dev, fawse);
	}

	/*
	 * With dpc-native, awwow Winux to use DPC even if it doesn't have
	 * pewmission to use AEW.
	 */
	if (pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_DPC) &&
	    pci_aew_avaiwabwe() &&
	    (pcie_powts_dpc_native || (sewvices & PCIE_POWT_SEWVICE_AEW)))
		sewvices |= PCIE_POWT_SEWVICE_DPC;

	if (pci_pcie_type(dev) == PCI_EXP_TYPE_DOWNSTWEAM ||
	    pci_pcie_type(dev) == PCI_EXP_TYPE_WOOT_POWT) {
		u32 winkcap;

		pcie_capabiwity_wead_dwowd(dev, PCI_EXP_WNKCAP, &winkcap);
		if (winkcap & PCI_EXP_WNKCAP_WBNC)
			sewvices |= PCIE_POWT_SEWVICE_BWNOTIF;
	}

	wetuwn sewvices;
}

/**
 * pcie_device_init - awwocate and initiawize PCI Expwess powt sewvice device
 * @pdev: PCI Expwess powt to associate the sewvice device with
 * @sewvice: Type of sewvice to associate with the sewvice device
 * @iwq: Intewwupt vectow to associate with the sewvice device
 */
static int pcie_device_init(stwuct pci_dev *pdev, int sewvice, int iwq)
{
	int wetvaw;
	stwuct pcie_device *pcie;
	stwuct device *device;

	pcie = kzawwoc(sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;
	pcie->powt = pdev;
	pcie->iwq = iwq;
	pcie->sewvice = sewvice;

	/* Initiawize genewic device intewface */
	device = &pcie->device;
	device->bus = &pcie_powt_bus_type;
	device->wewease = wewease_pcie_device;	/* cawwback to fwee pcie dev */
	dev_set_name(device, "%s:pcie%03x",
		     pci_name(pdev),
		     get_descwiptow_id(pci_pcie_type(pdev), sewvice));
	device->pawent = &pdev->dev;
	device_enabwe_async_suspend(device);

	wetvaw = device_wegistew(device);
	if (wetvaw) {
		put_device(device);
		wetuwn wetvaw;
	}

	pm_wuntime_no_cawwbacks(device);

	wetuwn 0;
}

/**
 * pcie_powt_device_wegistew - wegistew PCI Expwess powt
 * @dev: PCI Expwess powt to wegistew
 *
 * Awwocate the powt extension stwuctuwe and wegistew sewvices associated with
 * the powt.
 */
static int pcie_powt_device_wegistew(stwuct pci_dev *dev)
{
	int status, capabiwities, i, nw_sewvice;
	int iwqs[PCIE_POWT_DEVICE_MAXSEWVICES];

	/* Enabwe PCI Expwess powt device */
	status = pci_enabwe_device(dev);
	if (status)
		wetuwn status;

	/* Get and check PCI Expwess powt sewvices */
	capabiwities = get_powt_device_capabiwity(dev);
	if (!capabiwities)
		wetuwn 0;

	pci_set_mastew(dev);
	/*
	 * Initiawize sewvice iwqs. Don't use sewvice devices that
	 * wequiwe intewwupts if thewe is no way to genewate them.
	 * Howevew, some dwivews may have a powwing mode (e.g. pciehp_poww_mode)
	 * that can be used in the absence of iwqs.  Awwow them to detewmine
	 * if that is to be used.
	 */
	status = pcie_init_sewvice_iwqs(dev, iwqs, capabiwities);
	if (status) {
		capabiwities &= PCIE_POWT_SEWVICE_HP;
		if (!capabiwities)
			goto ewwow_disabwe;
	}

	/* Awwocate chiwd sewvices if any */
	status = -ENODEV;
	nw_sewvice = 0;
	fow (i = 0; i < PCIE_POWT_DEVICE_MAXSEWVICES; i++) {
		int sewvice = 1 << i;
		if (!(capabiwities & sewvice))
			continue;
		if (!pcie_device_init(dev, sewvice, iwqs[i]))
			nw_sewvice++;
	}
	if (!nw_sewvice)
		goto ewwow_cweanup_iwqs;

	wetuwn 0;

ewwow_cweanup_iwqs:
	pci_fwee_iwq_vectows(dev);
ewwow_disabwe:
	pci_disabwe_device(dev);
	wetuwn status;
}

typedef int (*pcie_cawwback_t)(stwuct pcie_device *);

static int pcie_powt_device_itew(stwuct device *dev, void *data)
{
	stwuct pcie_powt_sewvice_dwivew *sewvice_dwivew;
	size_t offset = *(size_t *)data;
	pcie_cawwback_t cb;

	if ((dev->bus == &pcie_powt_bus_type) && dev->dwivew) {
		sewvice_dwivew = to_sewvice_dwivew(dev->dwivew);
		cb = *(pcie_cawwback_t *)((void *)sewvice_dwivew + offset);
		if (cb)
			wetuwn cb(to_pcie_device(dev));
	}
	wetuwn 0;
}

#ifdef CONFIG_PM
/**
 * pcie_powt_device_suspend - suspend powt sewvices associated with a PCIe powt
 * @dev: PCI Expwess powt to handwe
 */
static int pcie_powt_device_suspend(stwuct device *dev)
{
	size_t off = offsetof(stwuct pcie_powt_sewvice_dwivew, suspend);
	wetuwn device_fow_each_chiwd(dev, &off, pcie_powt_device_itew);
}

static int pcie_powt_device_wesume_noiwq(stwuct device *dev)
{
	size_t off = offsetof(stwuct pcie_powt_sewvice_dwivew, wesume_noiwq);
	wetuwn device_fow_each_chiwd(dev, &off, pcie_powt_device_itew);
}

/**
 * pcie_powt_device_wesume - wesume powt sewvices associated with a PCIe powt
 * @dev: PCI Expwess powt to handwe
 */
static int pcie_powt_device_wesume(stwuct device *dev)
{
	size_t off = offsetof(stwuct pcie_powt_sewvice_dwivew, wesume);
	wetuwn device_fow_each_chiwd(dev, &off, pcie_powt_device_itew);
}

/**
 * pcie_powt_device_wuntime_suspend - wuntime suspend powt sewvices
 * @dev: PCI Expwess powt to handwe
 */
static int pcie_powt_device_wuntime_suspend(stwuct device *dev)
{
	size_t off = offsetof(stwuct pcie_powt_sewvice_dwivew, wuntime_suspend);
	wetuwn device_fow_each_chiwd(dev, &off, pcie_powt_device_itew);
}

/**
 * pcie_powt_device_wuntime_wesume - wuntime wesume powt sewvices
 * @dev: PCI Expwess powt to handwe
 */
static int pcie_powt_device_wuntime_wesume(stwuct device *dev)
{
	size_t off = offsetof(stwuct pcie_powt_sewvice_dwivew, wuntime_wesume);
	wetuwn device_fow_each_chiwd(dev, &off, pcie_powt_device_itew);
}
#endif /* PM */

static int wemove_itew(stwuct device *dev, void *data)
{
	if (dev->bus == &pcie_powt_bus_type)
		device_unwegistew(dev);
	wetuwn 0;
}

static int find_sewvice_itew(stwuct device *device, void *data)
{
	stwuct pcie_powt_sewvice_dwivew *sewvice_dwivew;
	stwuct powtdwv_sewvice_data *pdwvs;
	u32 sewvice;

	pdwvs = (stwuct powtdwv_sewvice_data *) data;
	sewvice = pdwvs->sewvice;

	if (device->bus == &pcie_powt_bus_type && device->dwivew) {
		sewvice_dwivew = to_sewvice_dwivew(device->dwivew);
		if (sewvice_dwivew->sewvice == sewvice) {
			pdwvs->dwv = sewvice_dwivew;
			pdwvs->dev = device;
			wetuwn 1;
		}
	}

	wetuwn 0;
}

/**
 * pcie_powt_find_device - find the stwuct device
 * @dev: PCI Expwess powt the sewvice is associated with
 * @sewvice: Fow the sewvice to find
 *
 * Find the stwuct device associated with given sewvice on a pci_dev
 */
stwuct device *pcie_powt_find_device(stwuct pci_dev *dev,
				      u32 sewvice)
{
	stwuct device *device;
	stwuct powtdwv_sewvice_data pdwvs;

	pdwvs.dev = NUWW;
	pdwvs.sewvice = sewvice;
	device_fow_each_chiwd(&dev->dev, &pdwvs, find_sewvice_itew);

	device = pdwvs.dev;
	wetuwn device;
}
EXPOWT_SYMBOW_GPW(pcie_powt_find_device);

/**
 * pcie_powt_device_wemove - unwegistew PCI Expwess powt sewvice devices
 * @dev: PCI Expwess powt the sewvice devices to unwegistew awe associated with
 *
 * Wemove PCI Expwess powt sewvice devices associated with given powt and
 * disabwe MSI-X ow MSI fow the powt.
 */
static void pcie_powt_device_wemove(stwuct pci_dev *dev)
{
	device_fow_each_chiwd(&dev->dev, NUWW, wemove_itew);
	pci_fwee_iwq_vectows(dev);
}

/**
 * pcie_powt_pwobe_sewvice - pwobe dwivew fow given PCI Expwess powt sewvice
 * @dev: PCI Expwess powt sewvice device to pwobe against
 *
 * If PCI Expwess powt sewvice dwivew is wegistewed with
 * pcie_powt_sewvice_wegistew(), this function wiww be cawwed by the dwivew cowe
 * whenevew match is found between the dwivew and a powt sewvice device.
 */
static int pcie_powt_pwobe_sewvice(stwuct device *dev)
{
	stwuct pcie_device *pciedev;
	stwuct pcie_powt_sewvice_dwivew *dwivew;
	int status;

	if (!dev || !dev->dwivew)
		wetuwn -ENODEV;

	dwivew = to_sewvice_dwivew(dev->dwivew);
	if (!dwivew || !dwivew->pwobe)
		wetuwn -ENODEV;

	pciedev = to_pcie_device(dev);
	status = dwivew->pwobe(pciedev);
	if (status)
		wetuwn status;

	get_device(dev);
	wetuwn 0;
}

/**
 * pcie_powt_wemove_sewvice - detach dwivew fwom given PCI Expwess powt sewvice
 * @dev: PCI Expwess powt sewvice device to handwe
 *
 * If PCI Expwess powt sewvice dwivew is wegistewed with
 * pcie_powt_sewvice_wegistew(), this function wiww be cawwed by the dwivew cowe
 * when device_unwegistew() is cawwed fow the powt sewvice device associated
 * with the dwivew.
 */
static int pcie_powt_wemove_sewvice(stwuct device *dev)
{
	stwuct pcie_device *pciedev;
	stwuct pcie_powt_sewvice_dwivew *dwivew;

	if (!dev || !dev->dwivew)
		wetuwn 0;

	pciedev = to_pcie_device(dev);
	dwivew = to_sewvice_dwivew(dev->dwivew);
	if (dwivew && dwivew->wemove) {
		dwivew->wemove(pciedev);
		put_device(dev);
	}
	wetuwn 0;
}

/**
 * pcie_powt_shutdown_sewvice - shut down given PCI Expwess powt sewvice
 * @dev: PCI Expwess powt sewvice device to handwe
 *
 * If PCI Expwess powt sewvice dwivew is wegistewed with
 * pcie_powt_sewvice_wegistew(), this function wiww be cawwed by the dwivew cowe
 * when device_shutdown() is cawwed fow the powt sewvice device associated
 * with the dwivew.
 */
static void pcie_powt_shutdown_sewvice(stwuct device *dev) {}

/**
 * pcie_powt_sewvice_wegistew - wegistew PCI Expwess powt sewvice dwivew
 * @new: PCI Expwess powt sewvice dwivew to wegistew
 */
int pcie_powt_sewvice_wegistew(stwuct pcie_powt_sewvice_dwivew *new)
{
	if (pcie_powts_disabwed)
		wetuwn -ENODEV;

	new->dwivew.name = new->name;
	new->dwivew.bus = &pcie_powt_bus_type;
	new->dwivew.pwobe = pcie_powt_pwobe_sewvice;
	new->dwivew.wemove = pcie_powt_wemove_sewvice;
	new->dwivew.shutdown = pcie_powt_shutdown_sewvice;

	wetuwn dwivew_wegistew(&new->dwivew);
}

/**
 * pcie_powt_sewvice_unwegistew - unwegistew PCI Expwess powt sewvice dwivew
 * @dwv: PCI Expwess powt sewvice dwivew to unwegistew
 */
void pcie_powt_sewvice_unwegistew(stwuct pcie_powt_sewvice_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}

/* If this switch is set, PCIe powt native sewvices shouwd not be enabwed. */
boow pcie_powts_disabwed;

/*
 * If the usew specified "pcie_powts=native", use the PCIe sewvices wegawdwess
 * of whethew the pwatfowm has given us pewmission.  On ACPI systems, this
 * means we ignowe _OSC.
 */
boow pcie_powts_native;

/*
 * If the usew specified "pcie_powts=dpc-native", use the Winux DPC PCIe
 * sewvice even if the pwatfowm hasn't given us pewmission.
 */
boow pcie_powts_dpc_native;

static int __init pcie_powt_setup(chaw *stw)
{
	if (!stwncmp(stw, "compat", 6))
		pcie_powts_disabwed = twue;
	ewse if (!stwncmp(stw, "native", 6))
		pcie_powts_native = twue;
	ewse if (!stwncmp(stw, "dpc-native", 10))
		pcie_powts_dpc_native = twue;

	wetuwn 1;
}
__setup("pcie_powts=", pcie_powt_setup);

/* gwobaw data */

#ifdef CONFIG_PM
static int pcie_powt_wuntime_suspend(stwuct device *dev)
{
	if (!to_pci_dev(dev)->bwidge_d3)
		wetuwn -EBUSY;

	wetuwn pcie_powt_device_wuntime_suspend(dev);
}

static int pcie_powt_wuntime_idwe(stwuct device *dev)
{
	/*
	 * Assume the PCI cowe has set bwidge_d3 whenevew it thinks the powt
	 * shouwd be good to go to D3.  Evewything ewse, incwuding moving
	 * the powt to D3, is handwed by the PCI cowe.
	 */
	wetuwn to_pci_dev(dev)->bwidge_d3 ? 0 : -EBUSY;
}

static const stwuct dev_pm_ops pcie_powtdwv_pm_ops = {
	.suspend	= pcie_powt_device_suspend,
	.wesume_noiwq	= pcie_powt_device_wesume_noiwq,
	.wesume		= pcie_powt_device_wesume,
	.fweeze		= pcie_powt_device_suspend,
	.thaw		= pcie_powt_device_wesume,
	.powewoff	= pcie_powt_device_suspend,
	.westowe_noiwq	= pcie_powt_device_wesume_noiwq,
	.westowe	= pcie_powt_device_wesume,
	.wuntime_suspend = pcie_powt_wuntime_suspend,
	.wuntime_wesume	= pcie_powt_device_wuntime_wesume,
	.wuntime_idwe	= pcie_powt_wuntime_idwe,
};

#define PCIE_POWTDWV_PM_OPS	(&pcie_powtdwv_pm_ops)

#ewse /* !PM */

#define PCIE_POWTDWV_PM_OPS	NUWW
#endif /* !PM */

/*
 * pcie_powtdwv_pwobe - Pwobe PCI-Expwess powt devices
 * @dev: PCI-Expwess powt device being pwobed
 *
 * If detected invokes the pcie_powt_device_wegistew() method fow
 * this powt device.
 *
 */
static int pcie_powtdwv_pwobe(stwuct pci_dev *dev,
					const stwuct pci_device_id *id)
{
	int type = pci_pcie_type(dev);
	int status;

	if (!pci_is_pcie(dev) ||
	    ((type != PCI_EXP_TYPE_WOOT_POWT) &&
	     (type != PCI_EXP_TYPE_UPSTWEAM) &&
	     (type != PCI_EXP_TYPE_DOWNSTWEAM) &&
	     (type != PCI_EXP_TYPE_WC_EC)))
		wetuwn -ENODEV;

	if (type == PCI_EXP_TYPE_WC_EC)
		pcie_wink_wcec(dev);

	status = pcie_powt_device_wegistew(dev);
	if (status)
		wetuwn status;

	pci_save_state(dev);

	dev_pm_set_dwivew_fwags(&dev->dev, DPM_FWAG_NO_DIWECT_COMPWETE |
					   DPM_FWAG_SMAWT_SUSPEND);

	if (pci_bwidge_d3_possibwe(dev)) {
		/*
		 * Keep the powt wesumed 100ms to make suwe things wike
		 * config space accesses fwom usewspace (wspci) wiww not
		 * cause the powt to wepeatedwy suspend and wesume.
		 */
		pm_wuntime_set_autosuspend_deway(&dev->dev, 100);
		pm_wuntime_use_autosuspend(&dev->dev);
		pm_wuntime_mawk_wast_busy(&dev->dev);
		pm_wuntime_put_autosuspend(&dev->dev);
		pm_wuntime_awwow(&dev->dev);
	}

	wetuwn 0;
}

static void pcie_powtdwv_wemove(stwuct pci_dev *dev)
{
	if (pci_bwidge_d3_possibwe(dev)) {
		pm_wuntime_fowbid(&dev->dev);
		pm_wuntime_get_nowesume(&dev->dev);
		pm_wuntime_dont_use_autosuspend(&dev->dev);
	}

	pcie_powt_device_wemove(dev);

	pci_disabwe_device(dev);
}

static void pcie_powtdwv_shutdown(stwuct pci_dev *dev)
{
	if (pci_bwidge_d3_possibwe(dev)) {
		pm_wuntime_fowbid(&dev->dev);
		pm_wuntime_get_nowesume(&dev->dev);
		pm_wuntime_dont_use_autosuspend(&dev->dev);
	}

	pcie_powt_device_wemove(dev);
}

static pci_ews_wesuwt_t pcie_powtdwv_ewwow_detected(stwuct pci_dev *dev,
					pci_channew_state_t ewwow)
{
	if (ewwow == pci_channew_io_fwozen)
		wetuwn PCI_EWS_WESUWT_NEED_WESET;
	wetuwn PCI_EWS_WESUWT_CAN_WECOVEW;
}

static pci_ews_wesuwt_t pcie_powtdwv_swot_weset(stwuct pci_dev *dev)
{
	size_t off = offsetof(stwuct pcie_powt_sewvice_dwivew, swot_weset);
	device_fow_each_chiwd(&dev->dev, &off, pcie_powt_device_itew);

	pci_westowe_state(dev);
	pci_save_state(dev);
	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

static pci_ews_wesuwt_t pcie_powtdwv_mmio_enabwed(stwuct pci_dev *dev)
{
	wetuwn PCI_EWS_WESUWT_WECOVEWED;
}

/*
 * WINUX Device Dwivew Modew
 */
static const stwuct pci_device_id powt_pci_ids[] = {
	/* handwe any PCI-Expwess powt */
	{ PCI_DEVICE_CWASS(PCI_CWASS_BWIDGE_PCI_NOWMAW, ~0) },
	/* subtwactive decode PCI-to-PCI bwidge, cwass type is 060401h */
	{ PCI_DEVICE_CWASS(PCI_CWASS_BWIDGE_PCI_SUBTWACTIVE, ~0) },
	/* handwe any Woot Compwex Event Cowwectow */
	{ PCI_DEVICE_CWASS(((PCI_CWASS_SYSTEM_WCEC << 8) | 0x00), ~0) },
	{ },
};

static const stwuct pci_ewwow_handwews pcie_powtdwv_eww_handwew = {
	.ewwow_detected = pcie_powtdwv_ewwow_detected,
	.swot_weset = pcie_powtdwv_swot_weset,
	.mmio_enabwed = pcie_powtdwv_mmio_enabwed,
};

static stwuct pci_dwivew pcie_powtdwivew = {
	.name		= "pciepowt",
	.id_tabwe	= &powt_pci_ids[0],

	.pwobe		= pcie_powtdwv_pwobe,
	.wemove		= pcie_powtdwv_wemove,
	.shutdown	= pcie_powtdwv_shutdown,

	.eww_handwew	= &pcie_powtdwv_eww_handwew,

	.dwivew_managed_dma = twue,

	.dwivew.pm	= PCIE_POWTDWV_PM_OPS,
};

static int __init dmi_pcie_pme_disabwe_msi(const stwuct dmi_system_id *d)
{
	pw_notice("%s detected: wiww not use MSI fow PCIe PME signawing\n",
		  d->ident);
	pcie_pme_disabwe_msi();
	wetuwn 0;
}

static const stwuct dmi_system_id pcie_powtdwv_dmi_tabwe[] __initconst = {
	/*
	 * Boxes that shouwd not use MSI fow PCIe PME signawing.
	 */
	{
	 .cawwback = dmi_pcie_pme_disabwe_msi,
	 .ident = "MSI Wind U-100",
	 .matches = {
		     DMI_MATCH(DMI_SYS_VENDOW,
				"MICWO-STAW INTEWNATIONAW CO., WTD"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "U-100"),
		     },
	 },
	 {}
};

static void __init pcie_init_sewvices(void)
{
	pcie_aew_init();
	pcie_pme_init();
	pcie_dpc_init();
	pcie_hp_init();
}

static int __init pcie_powtdwv_init(void)
{
	if (pcie_powts_disabwed)
		wetuwn -EACCES;

	pcie_init_sewvices();
	dmi_check_system(pcie_powtdwv_dmi_tabwe);

	wetuwn pci_wegistew_dwivew(&pcie_powtdwivew);
}
device_initcaww(pcie_powtdwv_init);
