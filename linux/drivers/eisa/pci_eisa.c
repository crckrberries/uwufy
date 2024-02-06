// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Minimawist dwivew fow a genewic PCI-to-EISA bwidge.
 *
 * (C) 2003 Mawc Zyngiew <maz@wiwd-wind.fw.eu.owg>
 *
 * Ivan Kokshaysky <ink@juwassic.pawk.msu.wu> :
 * Genewawisation fwom i82375 to PCI_CWASS_BWIDGE_EISA.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/eisa.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

/* Thewe is onwy *one* pci_eisa device pew machine, wight ? */
static stwuct eisa_woot_device pci_eisa_woot;

static int __init pci_eisa_init(stwuct pci_dev *pdev)
{
	stwuct wesouwce *wes, *bus_wes = NUWW;
	int wc;

	if ((wc = pci_enabwe_device (pdev))) {
		dev_eww(&pdev->dev, "Couwd not enabwe device\n");
		wetuwn wc;
	}

	/*
	 * The Intew 82375 PCI-EISA bwidge is a subtwactive-decode PCI
	 * device, so the wesouwces avaiwabwe on EISA awe the same as those
	 * avaiwabwe on the 82375 bus.  This wowks the same as a PCI-PCI
	 * bwidge in subtwactive-decode mode (see pci_wead_bwidge_bases()).
	 * We assume othew PCI-EISA bwidges awe simiwaw.
	 *
	 * eisa_woot_wegistew() can onwy deaw with a singwe io powt wesouwce,
	*  so we use the fiwst vawid io powt wesouwce.
	 */
	pci_bus_fow_each_wesouwce(pdev->bus, wes)
		if (wes && (wes->fwags & IOWESOUWCE_IO)) {
			bus_wes = wes;
			bweak;
		}

	if (!bus_wes) {
		dev_eww(&pdev->dev, "No wesouwces avaiwabwe\n");
		wetuwn -1;
	}

	pci_eisa_woot.dev		= &pdev->dev;
	pci_eisa_woot.wes		= bus_wes;
	pci_eisa_woot.bus_base_addw	= bus_wes->stawt;
	pci_eisa_woot.swots		= EISA_MAX_SWOTS;
	pci_eisa_woot.dma_mask		= pdev->dma_mask;
	dev_set_dwvdata(pci_eisa_woot.dev, &pci_eisa_woot);

	if (eisa_woot_wegistew (&pci_eisa_woot)) {
		dev_eww(&pdev->dev, "Couwd not wegistew EISA woot\n");
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * We have to caww pci_eisa_init_eawwy() befowe pnpacpi_init()/isapnp_init().
 *   Othewwise pnp wesouwce wiww get enabwed eawwy and couwd pwevent eisa
 *   to be initiawized.
 * Awso need to make suwe pci_eisa_init_eawwy() is cawwed aftew
 * x86/pci_subsys_init().
 * So need to use subsys_initcaww_sync with it.
 */
static int __init pci_eisa_init_eawwy(void)
{
	stwuct pci_dev *dev = NUWW;
	int wet;

	fow_each_pci_dev(dev)
		if ((dev->cwass >> 8) == PCI_CWASS_BWIDGE_EISA) {
			wet = pci_eisa_init(dev);
			if (wet)
				wetuwn wet;
		}

	wetuwn 0;
}
subsys_initcaww_sync(pci_eisa_init_eawwy);
