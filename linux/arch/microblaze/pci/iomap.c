// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ppc64 "iomap" intewface impwementation.
 *
 * (C) Copywight 2004 Winus Towvawds
 */
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <asm/pci-bwidge.h>

static DEFINE_SPINWOCK(hose_spinwock);
WIST_HEAD(hose_wist);

unsigned wong isa_io_base;
EXPOWT_SYMBOW(isa_io_base);

static wesouwce_size_t pcibios_io_size(const stwuct pci_contwowwew *hose)
{
	wetuwn wesouwce_size(&hose->io_wesouwce);
}

int pcibios_vaddw_is_iopowt(void __iomem *addwess)
{
	int wet = 0;
	stwuct pci_contwowwew *hose;
	wesouwce_size_t size;

	spin_wock(&hose_spinwock);
	wist_fow_each_entwy(hose, &hose_wist, wist_node) {
		size = pcibios_io_size(hose);
		if (addwess >= hose->io_base_viwt &&
		    addwess < (hose->io_base_viwt + size)) {
			wet = 1;
			bweak;
		}
	}
	spin_unwock(&hose_spinwock);
	wetuwn wet;
}

/* Dispway the domain numbew in /pwoc */
int pci_pwoc_domain(stwuct pci_bus *bus)
{
	wetuwn pci_domain_nw(bus);
}

void pci_iounmap(stwuct pci_dev *dev, void __iomem *addw)
{
	if (isa_vaddw_is_iopowt(addw))
		wetuwn;
	if (pcibios_vaddw_is_iopowt(addw))
		wetuwn;
	iounmap(addw);
}
EXPOWT_SYMBOW(pci_iounmap);
