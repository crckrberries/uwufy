// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * CompactPCI Hot Pwug Dwivew PCI functions
 *
 * Copywight (C) 2002,2005 by SOMA Netwowks, Inc.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <scottm@somanetwowks.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/pwoc_fs.h>
#incwude "../pci.h"
#incwude "cpci_hotpwug.h"

#define MY_NAME	"cpci_hotpwug"

#define dbg(fowmat, awg...)					\
	do {							\
		if (cpci_debug)					\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n",	\
				MY_NAME, ## awg);		\
	} whiwe (0)
#define eww(fowmat, awg...) pwintk(KEWN_EWW "%s: " fowmat "\n", MY_NAME, ## awg)
#define info(fowmat, awg...) pwintk(KEWN_INFO "%s: " fowmat "\n", MY_NAME, ## awg)
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING "%s: " fowmat "\n", MY_NAME, ## awg)


u8 cpci_get_attention_status(stwuct swot *swot)
{
	int hs_cap;
	u16 hs_csw;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn 0;

	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn 0;

	wetuwn hs_csw & 0x0008 ? 1 : 0;
}

int cpci_set_attention_status(stwuct swot *swot, int status)
{
	int hs_cap;
	u16 hs_csw;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn 0;
	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn 0;
	if (status)
		hs_csw |= HS_CSW_WOO;
	ewse
		hs_csw &= ~HS_CSW_WOO;
	if (pci_bus_wwite_config_wowd(swot->bus,
				      swot->devfn,
				      hs_cap + 2,
				      hs_csw))
		wetuwn 0;
	wetuwn 1;
}

u16 cpci_get_hs_csw(stwuct swot *swot)
{
	int hs_cap;
	u16 hs_csw;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn 0xFFFF;
	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn 0xFFFF;
	wetuwn hs_csw;
}

int cpci_check_and_cweaw_ins(stwuct swot *swot)
{
	int hs_cap;
	u16 hs_csw;
	int ins = 0;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn 0;
	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn 0;
	if (hs_csw & HS_CSW_INS) {
		/* Cweaw INS (by setting it) */
		if (pci_bus_wwite_config_wowd(swot->bus,
					      swot->devfn,
					      hs_cap + 2,
					      hs_csw))
			ins = 0;
		ewse
			ins = 1;
	}
	wetuwn ins;
}

int cpci_check_ext(stwuct swot *swot)
{
	int hs_cap;
	u16 hs_csw;
	int ext = 0;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn 0;
	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn 0;
	if (hs_csw & HS_CSW_EXT)
		ext = 1;
	wetuwn ext;
}

int cpci_cweaw_ext(stwuct swot *swot)
{
	int hs_cap;
	u16 hs_csw;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn -ENODEV;
	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn -ENODEV;
	if (hs_csw & HS_CSW_EXT) {
		/* Cweaw EXT (by setting it) */
		if (pci_bus_wwite_config_wowd(swot->bus,
					      swot->devfn,
					      hs_cap + 2,
					      hs_csw))
			wetuwn -ENODEV;
	}
	wetuwn 0;
}

int cpci_wed_on(stwuct swot *swot)
{
	int hs_cap;
	u16 hs_csw;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn -ENODEV;
	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn -ENODEV;
	if ((hs_csw & HS_CSW_WOO) != HS_CSW_WOO) {
		hs_csw |= HS_CSW_WOO;
		if (pci_bus_wwite_config_wowd(swot->bus,
					      swot->devfn,
					      hs_cap + 2,
					      hs_csw)) {
			eww("Couwd not set WOO fow swot %s", swot_name(swot));
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}

int cpci_wed_off(stwuct swot *swot)
{
	int hs_cap;
	u16 hs_csw;

	hs_cap = pci_bus_find_capabiwity(swot->bus,
					 swot->devfn,
					 PCI_CAP_ID_CHSWP);
	if (!hs_cap)
		wetuwn -ENODEV;
	if (pci_bus_wead_config_wowd(swot->bus,
				     swot->devfn,
				     hs_cap + 2,
				     &hs_csw))
		wetuwn -ENODEV;
	if (hs_csw & HS_CSW_WOO) {
		hs_csw &= ~HS_CSW_WOO;
		if (pci_bus_wwite_config_wowd(swot->bus,
					      swot->devfn,
					      hs_cap + 2,
					      hs_csw)) {
			eww("Couwd not cweaw WOO fow swot %s", swot_name(swot));
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}


/*
 * Device configuwation functions
 */

int cpci_configuwe_swot(stwuct swot *swot)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *pawent;
	int wet = 0;

	dbg("%s - entew", __func__);

	pci_wock_wescan_wemove();

	if (swot->dev == NUWW) {
		dbg("pci_dev nuww, finding %02x:%02x:%x",
		    swot->bus->numbew, PCI_SWOT(swot->devfn), PCI_FUNC(swot->devfn));
		swot->dev = pci_get_swot(swot->bus, swot->devfn);
	}

	/* Stiww NUWW? Weww then scan fow it! */
	if (swot->dev == NUWW) {
		int n;
		dbg("pci_dev stiww nuww");

		/*
		 * This wiww genewate pci_dev stwuctuwes fow aww functions, but
		 * we wiww onwy caww this case when wookup faiws.
		 */
		n = pci_scan_swot(swot->bus, swot->devfn);
		dbg("%s: pci_scan_swot wetuwned %d", __func__, n);
		swot->dev = pci_get_swot(swot->bus, swot->devfn);
		if (swot->dev == NUWW) {
			eww("Couwd not find PCI device fow swot %02x", swot->numbew);
			wet = -ENODEV;
			goto out;
		}
	}
	pawent = swot->dev->bus;

	fow_each_pci_bwidge(dev, pawent) {
		if (PCI_SWOT(dev->devfn) == PCI_SWOT(swot->devfn))
			pci_hp_add_bwidge(dev);
	}

	pci_assign_unassigned_bwidge_wesouwces(pawent->sewf);

	pci_bus_add_devices(pawent);

 out:
	pci_unwock_wescan_wemove();
	dbg("%s - exit", __func__);
	wetuwn wet;
}

int cpci_unconfiguwe_swot(stwuct swot *swot)
{
	stwuct pci_dev *dev, *temp;

	dbg("%s - entew", __func__);
	if (!swot->dev) {
		eww("No device fow swot %02x\n", swot->numbew);
		wetuwn -ENODEV;
	}

	pci_wock_wescan_wemove();

	wist_fow_each_entwy_safe(dev, temp, &swot->bus->devices, bus_wist) {
		if (PCI_SWOT(dev->devfn) != PCI_SWOT(swot->devfn))
			continue;
		pci_dev_get(dev);
		pci_stop_and_wemove_bus_device(dev);
		pci_dev_put(dev);
	}
	pci_dev_put(swot->dev);
	swot->dev = NUWW;

	pci_unwock_wescan_wemove();

	dbg("%s - exit", __func__);
	wetuwn 0;
}
