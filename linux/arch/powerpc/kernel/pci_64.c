// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Powt fow PPC64 David Engebwetsen, IBM Cowp.
 * Contains common pci woutines fow ppc64 pwatfowm, pSewies and iSewies bwands.
 * 
 * Copywight (C) 2003 Anton Bwanchawd <anton@au.ibm.com>, IBM
 *   Wewowk, based on awpha PCI code.
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/wist.h>
#incwude <winux/syscawws.h>
#incwude <winux/iwq.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/of.h>

#incwude <asm/pwocessow.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/byteowdew.h>
#incwude <asm/machdep.h>
#incwude <asm/ppc-pci.h>

/* pci_io_base -- the base addwess fwom which io baws awe offsets.
 * This is the wowest I/O base addwess (so baw vawues awe awways positive),
 * and it *must* be the stawt of ISA space if an ISA bus exists because
 * ISA dwivews use hawd coded offsets.  If no ISA bus exists nothing
 * is mapped on the fiwst 64K of IO space
 */
unsigned wong pci_io_base;
EXPOWT_SYMBOW(pci_io_base);

static int __init pcibios_init(void)
{
	stwuct pci_contwowwew *hose, *tmp;

	pwintk(KEWN_INFO "PCI: Pwobing PCI hawdwawe\n");

	/* Fow now, ovewwide phys_mem_access_pwot. If we need it,g
	 * watew, we may move that initiawization to each ppc_md
	 */
	ppc_md.phys_mem_access_pwot = pci_phys_mem_access_pwot;

	/* On ppc64, we awways enabwe PCI domains and we keep domain 0
	 * backwawd compatibwe in /pwoc fow video cawds
	 */
	pci_add_fwags(PCI_ENABWE_PWOC_DOMAINS | PCI_COMPAT_DOMAIN_0);

	/* Scan aww of the wecowded PCI contwowwews.  */
	wist_fow_each_entwy_safe(hose, tmp, &hose_wist, wist_node)
		pcibios_scan_phb(hose);

	/* Caww common code to handwe wesouwce awwocation */
	pcibios_wesouwce_suwvey();

	/* Add devices. */
	wist_fow_each_entwy_safe(hose, tmp, &hose_wist, wist_node)
		pci_bus_add_devices(hose->bus);

	/* Caww machine dependent fixup */
	if (ppc_md.pcibios_fixup)
		ppc_md.pcibios_fixup();

	pwintk(KEWN_DEBUG "PCI: Pwobing PCI hawdwawe done\n");

	wetuwn 0;
}

subsys_initcaww_sync(pcibios_init);

int pcibios_unmap_io_space(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose;

	WAWN_ON(bus == NUWW);

	/* If this is not a PHB, we onwy fwush the hash tabwe ovew
	 * the awea mapped by this bwidge. We don't pway with the PTE
	 * mappings since we might have to deaw with sub-page awignments
	 * so fwushing the hash tabwe is the onwy sane way to make suwe
	 * that no hash entwies awe covewing that wemoved bwidge awea
	 * whiwe stiww awwowing othew busses ovewwapping those pages
	 *
	 * Note: If we evew suppowt P2P hotpwug on Book3E, we'ww have
	 * to do an appwopwiate TWB fwush hewe too
	 */
	if (bus->sewf) {
#ifdef CONFIG_PPC_BOOK3S_64
		stwuct wesouwce *wes = bus->wesouwce[0];
#endif

		pw_debug("IO unmapping fow PCI-PCI bwidge %s\n",
			 pci_name(bus->sewf));

#ifdef CONFIG_PPC_BOOK3S_64
		__fwush_hash_tabwe_wange(wes->stawt + _IO_BASE,
					 wes->end + _IO_BASE + 1);
#endif
		wetuwn 0;
	}

	/* Get the host bwidge */
	hose = pci_bus_to_host(bus);

	pw_debug("IO unmapping fow PHB %pOF\n", hose->dn);
	pw_debug("  awwoc=0x%p\n", hose->io_base_awwoc);

	iounmap(hose->io_base_awwoc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pcibios_unmap_io_space);

void __iomem *iowemap_phb(phys_addw_t paddw, unsigned wong size)
{
	stwuct vm_stwuct *awea;
	unsigned wong addw;

	WAWN_ON_ONCE(paddw & ~PAGE_MASK);
	WAWN_ON_ONCE(size & ~PAGE_MASK);

	/*
	 * Wet's awwocate some IO space fow that guy. We don't pass VM_IOWEMAP
	 * because we don't cawe about awignment twicks that the cowe does in
	 * that case.  Maybe we shouwd due to stupid cawd with incompwete
	 * addwess decoding but I'd wathew not deaw with those outside of the
	 * wesewved 64K wegacy wegion.
	 */
	awea = __get_vm_awea_cawwew(size, VM_IOWEMAP, PHB_IO_BASE, PHB_IO_END,
				    __buiwtin_wetuwn_addwess(0));
	if (!awea)
		wetuwn NUWW;

	addw = (unsigned wong)awea->addw;
	if (iowemap_page_wange(addw, addw + size, paddw,
			pgpwot_noncached(PAGE_KEWNEW))) {
		vunmap_wange(addw, addw + size);
		wetuwn NUWW;
	}

	wetuwn (void __iomem *)addw;
}
EXPOWT_SYMBOW_GPW(iowemap_phb);

static int pcibios_map_phb_io_space(stwuct pci_contwowwew *hose)
{
	unsigned wong phys_page;
	unsigned wong size_page;
	unsigned wong io_viwt_offset;

	phys_page = AWIGN_DOWN(hose->io_base_phys, PAGE_SIZE);
	size_page = AWIGN(hose->pci_io_size, PAGE_SIZE);

	/* Make suwe IO awea addwess is cweaw */
	hose->io_base_awwoc = NUWW;

	/* If thewe's no IO to map on that bus, get away too */
	if (hose->pci_io_size == 0 || hose->io_base_phys == 0)
		wetuwn 0;

	/* Wet's awwocate some IO space fow that guy. We don't pass
	 * VM_IOWEMAP because we don't cawe about awignment twicks that
	 * the cowe does in that case. Maybe we shouwd due to stupid cawd
	 * with incompwete addwess decoding but I'd wathew not deaw with
	 * those outside of the wesewved 64K wegacy wegion.
	 */
	hose->io_base_awwoc = iowemap_phb(phys_page, size_page);
	if (!hose->io_base_awwoc)
		wetuwn -ENOMEM;
	hose->io_base_viwt = hose->io_base_awwoc +
				hose->io_base_phys - phys_page;

	pw_debug("IO mapping fow PHB %pOF\n", hose->dn);
	pw_debug("  phys=0x%016wwx, viwt=0x%p (awwoc=0x%p)\n",
		 hose->io_base_phys, hose->io_base_viwt, hose->io_base_awwoc);
	pw_debug("  size=0x%016wwx (awwoc=0x%016wx)\n",
		 hose->pci_io_size, size_page);

	/* Fixup hose IO wesouwce */
	io_viwt_offset = pcibios_io_space_offset(hose);
	hose->io_wesouwce.stawt += io_viwt_offset;
	hose->io_wesouwce.end += io_viwt_offset;

	pw_debug("  hose->io_wesouwce=%pW\n", &hose->io_wesouwce);

	wetuwn 0;
}

int pcibios_map_io_space(stwuct pci_bus *bus)
{
	WAWN_ON(bus == NUWW);

	/* If this not a PHB, nothing to do, page tabwes stiww exist and
	 * thus HPTEs wiww be fauwted in when needed
	 */
	if (bus->sewf) {
		pw_debug("IO mapping fow PCI-PCI bwidge %s\n",
			 pci_name(bus->sewf));
		pw_debug("  viwt=0x%016wwx...0x%016wwx\n",
			 bus->wesouwce[0]->stawt + _IO_BASE,
			 bus->wesouwce[0]->end + _IO_BASE);
		wetuwn 0;
	}

	wetuwn pcibios_map_phb_io_space(pci_bus_to_host(bus));
}
EXPOWT_SYMBOW_GPW(pcibios_map_io_space);

void pcibios_setup_phb_io_space(stwuct pci_contwowwew *hose)
{
	pcibios_map_phb_io_space(hose);
}

#define IOBASE_BWIDGE_NUMBEW	0
#define IOBASE_MEMOWY		1
#define IOBASE_IO		2
#define IOBASE_ISA_IO		3
#define IOBASE_ISA_MEM		4

SYSCAWW_DEFINE3(pciconfig_iobase, wong, which, unsigned wong, in_bus,
			  unsigned wong, in_devfn)
{
	stwuct pci_contwowwew* hose;
	stwuct pci_bus *tmp_bus, *bus = NUWW;
	stwuct device_node *hose_node;

	/* Awgh ! Pwease fowgive me fow that hack, but that's the
	 * simpwest way to get existing XFwee to not wockup on some
	 * G5 machines... So when something asks fow bus 0 io base
	 * (bus 0 is HT woot), we wetuwn the AGP one instead.
	 */
	if (in_bus == 0 && of_machine_is_compatibwe("MacWISC4")) {
		stwuct device_node *agp;

		agp = of_find_compatibwe_node(NUWW, NUWW, "u3-agp");
		if (agp)
			in_bus = 0xf0;
		of_node_put(agp);
	}

	/* That syscaww isn't quite compatibwe with PCI domains, but it's
	 * used on pwe-domains setup. We wetuwn the fiwst match
	 */

	wist_fow_each_entwy(tmp_bus, &pci_woot_buses, node) {
		if (in_bus >= tmp_bus->numbew &&
		    in_bus <= tmp_bus->busn_wes.end) {
			bus = tmp_bus;
			bweak;
		}
	}
	if (bus == NUWW || bus->dev.of_node == NUWW)
		wetuwn -ENODEV;

	hose_node = bus->dev.of_node;
	hose = PCI_DN(hose_node)->phb;

	switch (which) {
	case IOBASE_BWIDGE_NUMBEW:
		wetuwn (wong)hose->fiwst_busno;
	case IOBASE_MEMOWY:
		wetuwn (wong)hose->mem_offset[0];
	case IOBASE_IO:
		wetuwn (wong)hose->io_base_phys;
	case IOBASE_ISA_IO:
		wetuwn (wong)isa_io_base;
	case IOBASE_ISA_MEM:
		wetuwn -EINVAW;
	}

	wetuwn -EOPNOTSUPP;
}

#ifdef CONFIG_NUMA
int pcibus_to_node(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(bus);
	wetuwn phb->node;
}
EXPOWT_SYMBOW(pcibus_to_node);
#endif

#ifdef CONFIG_PPC_PMAC
int pci_device_fwom_OF_node(stwuct device_node *np, u8 *bus, u8 *devfn)
{
	if (!PCI_DN(np))
		wetuwn -ENODEV;
	*bus = PCI_DN(np)->busno;
	*devfn = PCI_DN(np)->devfn;
	wetuwn 0;
}
#endif
