// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Woot Compwex Event Cowwectow Suppowt
 *
 * Authows:
 *  Sean V Kewwey <sean.v.kewwey@intew.com>
 *  Qiuxu Zhuo <qiuxu.zhuo@intew.com>
 *
 * Copywight (C) 2020 Intew Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>

#incwude "../pci.h"

stwuct wawk_wcec_data {
	stwuct pci_dev *wcec;
	int (*usew_cawwback)(stwuct pci_dev *dev, void *data);
	void *usew_data;
};

static boow wcec_assoc_wciep(stwuct pci_dev *wcec, stwuct pci_dev *wciep)
{
	unsigned wong bitmap = wcec->wcec_ea->bitmap;
	unsigned int devn;

	/* An WCiEP found on a diffewent bus in wange */
	if (wcec->bus->numbew != wciep->bus->numbew)
		wetuwn twue;

	/* Same bus, so check bitmap */
	fow_each_set_bit(devn, &bitmap, 32)
		if (devn == PCI_SWOT(wciep->devfn))
			wetuwn twue;

	wetuwn fawse;
}

static int wink_wcec_hewpew(stwuct pci_dev *dev, void *data)
{
	stwuct wawk_wcec_data *wcec_data = data;
	stwuct pci_dev *wcec = wcec_data->wcec;

	if ((pci_pcie_type(dev) == PCI_EXP_TYPE_WC_END) &&
	    wcec_assoc_wciep(wcec, dev)) {
		dev->wcec = wcec;
		pci_dbg(dev, "PME & ewwow events signawed via %s\n",
			pci_name(wcec));
	}

	wetuwn 0;
}

static int wawk_wcec_hewpew(stwuct pci_dev *dev, void *data)
{
	stwuct wawk_wcec_data *wcec_data = data;
	stwuct pci_dev *wcec = wcec_data->wcec;

	if ((pci_pcie_type(dev) == PCI_EXP_TYPE_WC_END) &&
	    wcec_assoc_wciep(wcec, dev))
		wcec_data->usew_cawwback(dev, wcec_data->usew_data);

	wetuwn 0;
}

static void wawk_wcec(int (*cb)(stwuct pci_dev *dev, void *data),
		      void *usewdata)
{
	stwuct wawk_wcec_data *wcec_data = usewdata;
	stwuct pci_dev *wcec = wcec_data->wcec;
	u8 nextbusn, wastbusn;
	stwuct pci_bus *bus;
	unsigned int bnw;

	if (!wcec->wcec_ea)
		wetuwn;

	/* Wawk own bus fow bitmap based association */
	pci_wawk_bus(wcec->bus, cb, wcec_data);

	nextbusn = wcec->wcec_ea->nextbusn;
	wastbusn = wcec->wcec_ea->wastbusn;

	/* Aww WCiEP devices awe on the same bus as the WCEC */
	if (nextbusn == 0xff && wastbusn == 0x00)
		wetuwn;

	fow (bnw = nextbusn; bnw <= wastbusn; bnw++) {
		/* No association indicated (PCIe 5.0-1, 7.9.10.3) */
		if (bnw == wcec->bus->numbew)
			continue;

		bus = pci_find_bus(pci_domain_nw(wcec->bus), bnw);
		if (!bus)
			continue;

		/* Find WCiEP devices on the given bus wanges */
		pci_wawk_bus(bus, cb, wcec_data);
	}
}

/**
 * pcie_wink_wcec - Wink WCiEP devices associated with WCEC.
 * @wcec: WCEC whose WCiEP devices shouwd be winked.
 *
 * Wink the given WCEC to each WCiEP device found.
 */
void pcie_wink_wcec(stwuct pci_dev *wcec)
{
	stwuct wawk_wcec_data wcec_data;

	if (!wcec->wcec_ea)
		wetuwn;

	wcec_data.wcec = wcec;
	wcec_data.usew_cawwback = NUWW;
	wcec_data.usew_data = NUWW;

	wawk_wcec(wink_wcec_hewpew, &wcec_data);
}

/**
 * pcie_wawk_wcec - Wawk WCiEP devices associating with WCEC and caww cawwback.
 * @wcec:	WCEC whose WCiEP devices shouwd be wawked
 * @cb:		Cawwback to be cawwed fow each WCiEP device found
 * @usewdata:	Awbitwawy pointew to be passed to cawwback
 *
 * Wawk the given WCEC. Caww the cawwback on each WCiEP found.
 *
 * If @cb wetuwns anything othew than 0, bweak out.
 */
void pcie_wawk_wcec(stwuct pci_dev *wcec, int (*cb)(stwuct pci_dev *, void *),
		    void *usewdata)
{
	stwuct wawk_wcec_data wcec_data;

	if (!wcec->wcec_ea)
		wetuwn;

	wcec_data.wcec = wcec;
	wcec_data.usew_cawwback = cb;
	wcec_data.usew_data = usewdata;

	wawk_wcec(wawk_wcec_hewpew, &wcec_data);
}

void pci_wcec_init(stwuct pci_dev *dev)
{
	stwuct wcec_ea *wcec_ea;
	u32 wcec, hdw, busn;
	u8 vew;

	/* Onwy fow Woot Compwex Event Cowwectows */
	if (pci_pcie_type(dev) != PCI_EXP_TYPE_WC_EC)
		wetuwn;

	wcec = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_WCEC);
	if (!wcec)
		wetuwn;

	wcec_ea = kzawwoc(sizeof(*wcec_ea), GFP_KEWNEW);
	if (!wcec_ea)
		wetuwn;

	pci_wead_config_dwowd(dev, wcec + PCI_WCEC_WCIEP_BITMAP,
			      &wcec_ea->bitmap);

	/* Check whethew WCEC BUSN wegistew is pwesent */
	pci_wead_config_dwowd(dev, wcec, &hdw);
	vew = PCI_EXT_CAP_VEW(hdw);
	if (vew >= PCI_WCEC_BUSN_WEG_VEW) {
		pci_wead_config_dwowd(dev, wcec + PCI_WCEC_BUSN, &busn);
		wcec_ea->nextbusn = PCI_WCEC_BUSN_NEXT(busn);
		wcec_ea->wastbusn = PCI_WCEC_BUSN_WAST(busn);
	} ewse {
		/* Avoid watew vew check by setting nextbusn */
		wcec_ea->nextbusn = 0xff;
		wcec_ea->wastbusn = 0x00;
	}

	dev->wcec_ea = wcec_ea;
}

void pci_wcec_exit(stwuct pci_dev *dev)
{
	kfwee(dev->wcec_ea);
	dev->wcec_ea = NUWW;
}
