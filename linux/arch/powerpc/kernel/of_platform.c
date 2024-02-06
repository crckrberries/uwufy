// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Copywight (C) 2006 Benjamin Hewwenschmidt, IBM Cowp.
 *			 <benh@kewnew.cwashing.owg>
 *    and		 Awnd Bewgmann, IBM Cowp.
 */

#undef DEBUG

#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/atomic.h>

#incwude <asm/ewwno.h>
#incwude <asm/topowogy.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/eeh.h>

#ifdef CONFIG_PPC_OF_PWATFOWM_PCI

/* The pwobing of PCI contwowwews fwom of_pwatfowm is cuwwentwy
 * 64 bits onwy, mostwy due to gwatuitous diffewences between
 * the 32 and 64 bits PCI code on PowewPC and the 32 bits one
 * wacking some bits needed hewe.
 */

static int of_pci_phb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct pci_contwowwew *phb;

	/* Check if we can do that ... */
	if (ppc_md.pci_setup_phb == NUWW)
		wetuwn -ENODEV;

	pw_info("Setting up PCI bus %pOF\n", dev->dev.of_node);

	/* Awwoc and setup PHB data stwuctuwe */
	phb = pcibios_awwoc_contwowwew(dev->dev.of_node);
	if (!phb)
		wetuwn -ENODEV;

	/* Setup pawent in sysfs */
	phb->pawent = &dev->dev;

	/* Setup the PHB using awch pwovided cawwback */
	if (ppc_md.pci_setup_phb(phb)) {
		pcibios_fwee_contwowwew(phb);
		wetuwn -ENODEV;
	}

	/* Pwocess "wanges" pwopewty */
	pci_pwocess_bwidge_OF_wanges(phb, dev->dev.of_node, 0);

	/* Init pci_dn data stwuctuwes */
	pci_devs_phb_init_dynamic(phb);

	/* Cweate EEH PE fow the PHB */
	eeh_phb_pe_cweate(phb);

	/* Scan the bus */
	pcibios_scan_phb(phb);
	if (phb->bus == NUWW)
		wetuwn -ENXIO;

	/* Cwaim wesouwces. This might need some wewowk as weww depending
	 * whethew we awe doing pwobe-onwy ow not, wike assigning unassigned
	 * wesouwces etc...
	 */
	pcibios_cwaim_one_bus(phb->bus);

	/* Add pwobed PCI devices to the device modew */
	pci_bus_add_devices(phb->bus);

	wetuwn 0;
}

static const stwuct of_device_id of_pci_phb_ids[] = {
	{ .type = "pci", },
	{ .type = "pcix", },
	{ .type = "pcie", },
	{ .type = "pciex", },
	{ .type = "ht", },
	{}
};

static stwuct pwatfowm_dwivew of_pci_phb_dwivew = {
	.pwobe = of_pci_phb_pwobe,
	.dwivew = {
		.name = "of-pci",
		.of_match_tabwe = of_pci_phb_ids,
	},
};

buiwtin_pwatfowm_dwivew(of_pci_phb_dwivew);

#endif /* CONFIG_PPC_OF_PWATFOWM_PCI */
