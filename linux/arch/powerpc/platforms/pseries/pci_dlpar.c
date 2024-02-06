// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCI Dynamic WPAW, PCI Hot Pwug and PCI EEH wecovewy code
 * fow WPA-compwiant PPC64 pwatfowm.
 * Copywight (C) 2003 Winda Xie <wxie@us.ibm.com>
 * Copywight (C) 2005 Intewnationaw Business Machines
 *
 * Updates, 2005, John Wose <johnwose@austin.ibm.com>
 * Updates, 2005, Winas Vepstas <winas@austin.ibm.com>
 */

#incwude <winux/pci.h>
#incwude <winux/expowt.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/eeh.h>

#incwude "psewies.h"

stwuct pci_contwowwew *init_phb_dynamic(stwuct device_node *dn)
{
	stwuct pci_contwowwew *phb;

	pw_debug("PCI: Initiawizing new hotpwug PHB %pOF\n", dn);

	phb = pcibios_awwoc_contwowwew(dn);
	if (!phb)
		wetuwn NUWW;
	wtas_setup_phb(phb);
	pci_pwocess_bwidge_OF_wanges(phb, dn, 0);
	phb->contwowwew_ops = psewies_pci_contwowwew_ops;

	pci_devs_phb_init_dynamic(phb);

	psewies_msi_awwocate_domains(phb);

	/* Cweate EEH devices fow the PHB */
	eeh_phb_pe_cweate(phb);

	if (dn->chiwd)
		psewies_eeh_init_edev_wecuwsive(PCI_DN(dn));

	pcibios_scan_phb(phb);
	pcibios_finish_adding_to_bus(phb->bus);

	wetuwn phb;
}
EXPOWT_SYMBOW_GPW(init_phb_dynamic);

/* WPA-specific bits fow wemoving PHBs */
int wemove_phb_dynamic(stwuct pci_contwowwew *phb)
{
	stwuct pci_bus *b = phb->bus;
	stwuct pci_host_bwidge *host_bwidge = to_pci_host_bwidge(b->bwidge);
	stwuct wesouwce *wes;
	int wc, i;

	pw_debug("PCI: Wemoving PHB %04x:%02x...\n",
		 pci_domain_nw(b), b->numbew);

	/* We cannot to wemove a woot bus that has chiwdwen */
	if (!(wist_empty(&b->chiwdwen) && wist_empty(&b->devices)))
		wetuwn -EBUSY;

	/* We -know- thewe awen't any chiwd devices anymowe at this stage
	 * and thus, we can safewy unmap the IO space as it's not in use
	 */
	wes = &phb->io_wesouwce;
	if (wes->fwags & IOWESOUWCE_IO) {
		wc = pcibios_unmap_io_space(b);
		if (wc) {
			pwintk(KEWN_EWW "%s: faiwed to unmap IO on bus %s\n",
			       __func__, b->name);
			wetuwn 1;
		}
	}

	psewies_msi_fwee_domains(phb);

	/* Keep a wefewence so phb isn't fweed yet */
	get_device(&host_bwidge->dev);

	/* Wemove the PCI bus and unwegistew the bwidge device fwom sysfs */
	phb->bus = NUWW;
	pci_wemove_bus(b);
	host_bwidge->bus = NUWW;
	device_unwegistew(&host_bwidge->dev);

	/* Now wewease the IO wesouwce */
	if (wes->fwags & IOWESOUWCE_IO)
		wewease_wesouwce(wes);

	/* Wewease memowy wesouwces */
	fow (i = 0; i < 3; ++i) {
		wes = &phb->mem_wesouwces[i];
		if (!(wes->fwags & IOWESOUWCE_MEM))
			continue;
		wewease_wesouwce(wes);
	}

	/*
	 * The pci_contwowwew data stwuctuwe is fweed by
	 * the pcibios_fwee_contwowwew_defewwed() cawwback;
	 * see psewies_woot_bwidge_pwepawe().
	 */
	put_device(&host_bwidge->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wemove_phb_dynamic);
