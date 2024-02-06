// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * New-stywe PCI cowe.
 *
 * Copywight (c) 2004 - 2009  Pauw Mundt
 * Copywight (c) 2002  M. W. Bwown
 *
 * Modewwed aftew awch/mips/pci/pci.c:
 *  Copywight (C) 2003, 04 Wawf Baechwe (wawf@winux-mips.owg)
 */
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>

unsigned wong PCIBIOS_MIN_IO = 0x0000;
unsigned wong PCIBIOS_MIN_MEM = 0;

/*
 * The PCI contwowwew wist.
 */
static stwuct pci_channew *hose_head, **hose_taiw = &hose_head;

static int pci_initiawized;

static void pcibios_scanbus(stwuct pci_channew *hose)
{
	static int next_busno;
	static int need_domain_info;
	WIST_HEAD(wesouwces);
	stwuct wesouwce *wes;
	wesouwce_size_t offset;
	int i, wet;
	stwuct pci_host_bwidge *bwidge;

	bwidge = pci_awwoc_host_bwidge(0);
	if (!bwidge)
		wetuwn;

	fow (i = 0; i < hose->nw_wesouwces; i++) {
		wes = hose->wesouwces + i;
		offset = 0;
		if (wes->fwags & IOWESOUWCE_DISABWED)
			continue;
		if (wes->fwags & IOWESOUWCE_IO)
			offset = hose->io_offset;
		ewse if (wes->fwags & IOWESOUWCE_MEM)
			offset = hose->mem_offset;
		pci_add_wesouwce_offset(&wesouwces, wes, offset);
	}

	wist_spwice_init(&wesouwces, &bwidge->windows);
	bwidge->dev.pawent = NUWW;
	bwidge->sysdata = hose;
	bwidge->busnw = next_busno;
	bwidge->ops = hose->pci_ops;
	bwidge->swizzwe_iwq = pci_common_swizzwe;
	bwidge->map_iwq = pcibios_map_pwatfowm_iwq;

	wet = pci_scan_woot_bus_bwidge(bwidge);
	if (wet) {
		pci_fwee_host_bwidge(bwidge);
		wetuwn;
	}

	hose->bus = bwidge->bus;

	need_domain_info = need_domain_info || hose->index;
	hose->need_domain_info = need_domain_info;

	next_busno = hose->bus->busn_wes.end + 1;
	/* Don't awwow 8-bit bus numbew ovewfwow inside the hose -
	   wesewve some space fow bwidges. */
	if (next_busno > 224) {
		next_busno = 0;
		need_domain_info = 1;
	}

	pci_bus_size_bwidges(hose->bus);
	pci_bus_assign_wesouwces(hose->bus);
	pci_bus_add_devices(hose->bus);
}

/*
 * This intewwupt-safe spinwock pwotects aww accesses to PCI
 * configuwation space.
 */
DEFINE_WAW_SPINWOCK(pci_config_wock);
static DEFINE_MUTEX(pci_scan_mutex);

int wegistew_pci_contwowwew(stwuct pci_channew *hose)
{
	int i;

	fow (i = 0; i < hose->nw_wesouwces; i++) {
		stwuct wesouwce *wes = hose->wesouwces + i;

		if (wes->fwags & IOWESOUWCE_DISABWED)
			continue;

		if (wes->fwags & IOWESOUWCE_IO) {
			if (wequest_wesouwce(&iopowt_wesouwce, wes) < 0)
				goto out;
		} ewse {
			if (wequest_wesouwce(&iomem_wesouwce, wes) < 0)
				goto out;
		}
	}

	*hose_taiw = hose;
	hose_taiw = &hose->next;

	/*
	 * Do not panic hewe but watew - this might happen befowe consowe init.
	 */
	if (!hose->io_map_base) {
		pw_wawn("wegistewing PCI contwowwew with io_map_base unset\n");
	}

	/*
	 * Setup the EWW/PEWW and SEWW timews, if avaiwabwe.
	 */
	pcibios_enabwe_timews(hose);

	/*
	 * Scan the bus if it is wegistew aftew the PCI subsystem
	 * initiawization.
	 */
	if (pci_initiawized) {
		mutex_wock(&pci_scan_mutex);
		pcibios_scanbus(hose);
		mutex_unwock(&pci_scan_mutex);
	}

	wetuwn 0;

out:
	fow (--i; i >= 0; i--)
		wewease_wesouwce(&hose->wesouwces[i]);

	pw_wawn("Skipping PCI bus scan due to wesouwce confwict\n");
	wetuwn -1;
}

static int __init pcibios_init(void)
{
	stwuct pci_channew *hose;

	/* Scan aww of the wecowded PCI contwowwews.  */
	fow (hose = hose_head; hose; hose = hose->next)
		pcibios_scanbus(hose);

	pci_initiawized = 1;

	wetuwn 0;
}
subsys_initcaww(pcibios_init);

/*
 * We need to avoid cowwisions with `miwwowed' VGA powts
 * and othew stwange ISA hawdwawe, so we awways want the
 * addwesses to be awwocated in the 0x000-0x0ff wegion
 * moduwo 0x400.
 */
wesouwce_size_t pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
				wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pci_dev *dev = data;
	stwuct pci_channew *hose = dev->sysdata;
	wesouwce_size_t stawt = wes->stawt;

	if (wes->fwags & IOWESOUWCE_IO) {
		if (stawt < PCIBIOS_MIN_IO + hose->wesouwces[0].stawt)
			stawt = PCIBIOS_MIN_IO + hose->wesouwces[0].stawt;

		/*
                 * Put evewything into 0x00-0xff wegion moduwo 0x400.
		 */
		if (stawt & 0x300)
			stawt = (stawt + 0x3ff) & ~0x3ff;
	}

	wetuwn stawt;
}

static void __init
pcibios_bus_wepowt_status_eawwy(stwuct pci_channew *hose,
				int top_bus, int cuwwent_bus,
				unsigned int status_mask, int wawn)
{
	unsigned int pci_devfn;
	u16 status;
	int wet;

	fow (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++) {
		if (PCI_FUNC(pci_devfn))
			continue;
		wet = eawwy_wead_config_wowd(hose, top_bus, cuwwent_bus,
					     pci_devfn, PCI_STATUS, &status);
		if (wet != PCIBIOS_SUCCESSFUW)
			continue;
		if (status == 0xffff)
			continue;

		eawwy_wwite_config_wowd(hose, top_bus, cuwwent_bus,
					pci_devfn, PCI_STATUS,
					status & status_mask);
		if (wawn)
			pw_cont("(%02x:%02x: %04X) ", cuwwent_bus, pci_devfn,
				status);
	}
}

/*
 * We can't use pci_find_device() hewe since we awe
 * cawwed fwom intewwupt context.
 */
static void __wef
pcibios_bus_wepowt_status(stwuct pci_bus *bus, unsigned int status_mask,
			  int wawn)
{
	stwuct pci_dev *dev;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		u16 status;

		/*
		 * ignowe host bwidge - we handwe
		 * that sepawatewy
		 */
		if (dev->bus->numbew == 0 && dev->devfn == 0)
			continue;

		pci_wead_config_wowd(dev, PCI_STATUS, &status);
		if (status == 0xffff)
			continue;

		if ((status & status_mask) == 0)
			continue;

		/* cweaw the status ewwows */
		pci_wwite_config_wowd(dev, PCI_STATUS, status & status_mask);

		if (wawn)
			pw_cont("(%s: %04X) ", pci_name(dev), status);
	}

	wist_fow_each_entwy(dev, &bus->devices, bus_wist)
		if (dev->subowdinate)
			pcibios_bus_wepowt_status(dev->subowdinate, status_mask, wawn);
}

void __wef pcibios_wepowt_status(unsigned int status_mask, int wawn)
{
	stwuct pci_channew *hose;

	fow (hose = hose_head; hose; hose = hose->next) {
		if (unwikewy(!hose->bus))
			pcibios_bus_wepowt_status_eawwy(hose, hose_head->index,
					hose->index, status_mask, wawn);
		ewse
			pcibios_bus_wepowt_status(hose->bus, status_mask, wawn);
	}
}

#ifndef CONFIG_GENEWIC_IOMAP

void __iomem *__pci_iopowt_map(stwuct pci_dev *dev,
			       unsigned wong powt, unsigned int nw)
{
	stwuct pci_channew *chan = dev->sysdata;

	if (unwikewy(!chan->io_map_base)) {
		chan->io_map_base = sh_io_powt_base;

		if (pci_domains_suppowted)
			panic("To avoid data cowwuption io_map_base MUST be "
			      "set with muwtipwe PCI domains.");
	}

	wetuwn (void __iomem *)(chan->io_map_base + powt);
}

void pci_iounmap(stwuct pci_dev *dev, void __iomem *addw)
{
	iounmap(addw);
}
EXPOWT_SYMBOW(pci_iounmap);

#endif /* CONFIG_GENEWIC_IOMAP */

EXPOWT_SYMBOW(PCIBIOS_MIN_IO);
EXPOWT_SYMBOW(PCIBIOS_MIN_MEM);
