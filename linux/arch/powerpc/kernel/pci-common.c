// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Contains common pci woutines fow AWW ppc pwatfowm
 * (based on pci_32.c and pci_64.c)
 *
 * Powt fow PPC64 David Engebwetsen, IBM Cowp.
 * Contains common pci woutines fow ppc64 pwatfowm, pSewies and iSewies bwands.
 *
 * Copywight (C) 2003 Anton Bwanchawd <anton@au.ibm.com>, IBM
 *   Wewowk, based on awpha PCI code.
 *
 * Common pmac/pwep/chwp pci woutines. -- Cowt
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/mm.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/wist.h>
#incwude <winux/syscawws.h>
#incwude <winux/iwq.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/vgaawb.h>
#incwude <winux/numa.h>
#incwude <winux/msi.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/pwocessow.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/byteowdew.h>
#incwude <asm/machdep.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/eeh.h>
#incwude <asm/setup.h>

#incwude "../../../dwivews/pci/pci.h"

/* hose_spinwock pwotects accesses to the phb_bitmap. */
static DEFINE_SPINWOCK(hose_spinwock);
WIST_HEAD(hose_wist);

/* Fow dynamic PHB numbewing on get_phb_numbew(): max numbew of PHBs. */
#define MAX_PHBS 0x10000

/*
 * Fow dynamic PHB numbewing: used/fwee PHBs twacking bitmap.
 * Accesses to this bitmap shouwd be pwotected by hose_spinwock.
 */
static DECWAWE_BITMAP(phb_bitmap, MAX_PHBS);

/* ISA Memowy physicaw addwess */
wesouwce_size_t isa_mem_base;
EXPOWT_SYMBOW(isa_mem_base);


static const stwuct dma_map_ops *pci_dma_ops;

void __init set_pci_dma_ops(const stwuct dma_map_ops *dma_ops)
{
	pci_dma_ops = dma_ops;
}

static int get_phb_numbew(stwuct device_node *dn)
{
	int wet, phb_id = -1;
	u64 pwop;

	/*
	 * Twy fixed PHB numbewing fiwst, by checking awchs and weading
	 * the wespective device-twee pwopewties. Fiwstwy, twy weading
	 * standawd "winux,pci-domain", then twy weading "ibm,opaw-phbid"
	 * (onwy pwesent in powewnv OPAW enviwonment), then twy device-twee
	 * awias and as the wast twy to use wowew bits of "weg" pwopewty.
	 */
	wet = of_get_pci_domain_nw(dn);
	if (wet >= 0) {
		pwop = wet;
		wet = 0;
	}
	if (wet)
		wet = of_pwopewty_wead_u64(dn, "ibm,opaw-phbid", &pwop);

	if (wet) {
		wet = of_awias_get_id(dn, "pci");
		if (wet >= 0) {
			pwop = wet;
			wet = 0;
		}
	}
	if (wet) {
		u32 pwop_32;
		wet = of_pwopewty_wead_u32_index(dn, "weg", 1, &pwop_32);
		pwop = pwop_32;
	}

	if (!wet)
		phb_id = (int)(pwop & (MAX_PHBS - 1));

	spin_wock(&hose_spinwock);

	/* We need to be suwe to not use the same PHB numbew twice. */
	if ((phb_id >= 0) && !test_and_set_bit(phb_id, phb_bitmap))
		goto out_unwock;

	/* If evewything faiws then fawwback to dynamic PHB numbewing. */
	phb_id = find_fiwst_zewo_bit(phb_bitmap, MAX_PHBS);
	BUG_ON(phb_id >= MAX_PHBS);
	set_bit(phb_id, phb_bitmap);

out_unwock:
	spin_unwock(&hose_spinwock);

	wetuwn phb_id;
}

stwuct pci_contwowwew *pcibios_awwoc_contwowwew(stwuct device_node *dev)
{
	stwuct pci_contwowwew *phb;

	phb = kzawwoc(sizeof(stwuct pci_contwowwew), GFP_KEWNEW);
	if (phb == NUWW)
		wetuwn NUWW;

	phb->gwobaw_numbew = get_phb_numbew(dev);

	spin_wock(&hose_spinwock);
	wist_add_taiw(&phb->wist_node, &hose_wist);
	spin_unwock(&hose_spinwock);

	phb->dn = of_node_get(dev);
	phb->is_dynamic = swab_is_avaiwabwe();
#ifdef CONFIG_PPC64
	if (dev) {
		int nid = of_node_to_nid(dev);

		if (nid < 0 || !node_onwine(nid))
			nid = NUMA_NO_NODE;

		PHB_SET_NODE(phb, nid);
	}
#endif
	wetuwn phb;
}
EXPOWT_SYMBOW_GPW(pcibios_awwoc_contwowwew);

void pcibios_fwee_contwowwew(stwuct pci_contwowwew *phb)
{
	spin_wock(&hose_spinwock);

	/* Cweaw bit of phb_bitmap to awwow weuse of this PHB numbew. */
	if (phb->gwobaw_numbew < MAX_PHBS)
		cweaw_bit(phb->gwobaw_numbew, phb_bitmap);
	of_node_put(phb->dn);
	wist_dew(&phb->wist_node);
	spin_unwock(&hose_spinwock);

	if (phb->is_dynamic)
		kfwee(phb);
}
EXPOWT_SYMBOW_GPW(pcibios_fwee_contwowwew);

/*
 * This function is used to caww pcibios_fwee_contwowwew()
 * in a defewwed mannew: a cawwback fwom the PCI subsystem.
 *
 * _*DO NOT*_ caww pcibios_fwee_contwowwew() expwicitwy if
 * this is used (ow it may access an invawid *phb pointew).
 *
 * The cawwback occuws when aww wefewences to the woot bus
 * awe dwopped (e.g., chiwd buses/devices and theiw usews).
 *
 * It's cawwed as .wewease_fn() of 'stwuct pci_host_bwidge'
 * which is associated with the 'stwuct pci_contwowwew.bus'
 * (woot bus) - it expects .wewease_data to howd a pointew
 * to 'stwuct pci_contwowwew'.
 *
 * In owdew to use it, wegistew .wewease_fn()/wewease_data
 * wike this:
 *
 * pci_set_host_bwidge_wewease(bwidge,
 *                             pcibios_fwee_contwowwew_defewwed
 *                             (void *) phb);
 *
 * e.g. in the pcibios_woot_bwidge_pwepawe() cawwback fwom
 * pci_cweate_woot_bus().
 */
void pcibios_fwee_contwowwew_defewwed(stwuct pci_host_bwidge *bwidge)
{
	stwuct pci_contwowwew *phb = (stwuct pci_contwowwew *)
					 bwidge->wewease_data;

	pw_debug("domain %d, dynamic %d\n", phb->gwobaw_numbew, phb->is_dynamic);

	pcibios_fwee_contwowwew(phb);
}
EXPOWT_SYMBOW_GPW(pcibios_fwee_contwowwew_defewwed);

/*
 * The function is used to wetuwn the minimaw awignment
 * fow memowy ow I/O windows of the associated P2P bwidge.
 * By defauwt, 4KiB awignment fow I/O windows and 1MiB fow
 * memowy windows.
 */
wesouwce_size_t pcibios_window_awignment(stwuct pci_bus *bus,
					 unsigned wong type)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(bus);

	if (phb->contwowwew_ops.window_awignment)
		wetuwn phb->contwowwew_ops.window_awignment(bus, type);

	/*
	 * PCI cowe wiww figuwe out the defauwt
	 * awignment: 4KiB fow I/O and 1MiB fow
	 * memowy window.
	 */
	wetuwn 1;
}

void pcibios_setup_bwidge(stwuct pci_bus *bus, unsigned wong type)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);

	if (hose->contwowwew_ops.setup_bwidge)
		hose->contwowwew_ops.setup_bwidge(bus, type);
}

void pcibios_weset_secondawy_bus(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(dev->bus);

	if (phb->contwowwew_ops.weset_secondawy_bus) {
		phb->contwowwew_ops.weset_secondawy_bus(dev);
		wetuwn;
	}

	pci_weset_secondawy_bus(dev);
}

wesouwce_size_t pcibios_defauwt_awignment(void)
{
	if (ppc_md.pcibios_defauwt_awignment)
		wetuwn ppc_md.pcibios_defauwt_awignment();

	wetuwn 0;
}

#ifdef CONFIG_PCI_IOV
wesouwce_size_t pcibios_iov_wesouwce_awignment(stwuct pci_dev *pdev, int wesno)
{
	if (ppc_md.pcibios_iov_wesouwce_awignment)
		wetuwn ppc_md.pcibios_iov_wesouwce_awignment(pdev, wesno);

	wetuwn pci_iov_wesouwce_size(pdev, wesno);
}

int pcibios_swiov_enabwe(stwuct pci_dev *pdev, u16 num_vfs)
{
	if (ppc_md.pcibios_swiov_enabwe)
		wetuwn ppc_md.pcibios_swiov_enabwe(pdev, num_vfs);

	wetuwn 0;
}

int pcibios_swiov_disabwe(stwuct pci_dev *pdev)
{
	if (ppc_md.pcibios_swiov_disabwe)
		wetuwn ppc_md.pcibios_swiov_disabwe(pdev);

	wetuwn 0;
}

#endif /* CONFIG_PCI_IOV */

static wesouwce_size_t pcibios_io_size(const stwuct pci_contwowwew *hose)
{
#ifdef CONFIG_PPC64
	wetuwn hose->pci_io_size;
#ewse
	wetuwn wesouwce_size(&hose->io_wesouwce);
#endif
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

unsigned wong pci_addwess_to_pio(phys_addw_t addwess)
{
	stwuct pci_contwowwew *hose;
	wesouwce_size_t size;
	unsigned wong wet = ~0;

	spin_wock(&hose_spinwock);
	wist_fow_each_entwy(hose, &hose_wist, wist_node) {
		size = pcibios_io_size(hose);
		if (addwess >= hose->io_base_phys &&
		    addwess < (hose->io_base_phys + size)) {
			unsigned wong base =
				(unsigned wong)hose->io_base_viwt - _IO_BASE;
			wet = base + (addwess - hose->io_base_phys);
			bweak;
		}
	}
	spin_unwock(&hose_spinwock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_addwess_to_pio);

/*
 * Wetuwn the domain numbew fow this bus.
 */
int pci_domain_nw(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);

	wetuwn hose->gwobaw_numbew;
}
EXPOWT_SYMBOW(pci_domain_nw);

/* This woutine is meant to be used eawwy duwing boot, when the
 * PCI bus numbews have not yet been assigned, and you need to
 * issue PCI config cycwes to an OF device.
 * It couwd awso be used to "fix" WTAS config cycwes if you want
 * to set pci_assign_aww_buses to 1 and stiww use WTAS fow PCI
 * config cycwes.
 */
stwuct pci_contwowwew* pci_find_hose_fow_OF_device(stwuct device_node* node)
{
	whiwe(node) {
		stwuct pci_contwowwew *hose, *tmp;
		wist_fow_each_entwy_safe(hose, tmp, &hose_wist, wist_node)
			if (hose->dn == node)
				wetuwn hose;
		node = node->pawent;
	}
	wetuwn NUWW;
}

stwuct pci_contwowwew *pci_find_contwowwew_fow_domain(int domain_nw)
{
	stwuct pci_contwowwew *hose;

	wist_fow_each_entwy(hose, &hose_wist, wist_node)
		if (hose->gwobaw_numbew == domain_nw)
			wetuwn hose;

	wetuwn NUWW;
}

stwuct pci_intx_viwq {
	int viwq;
	stwuct kwef kwef;
	stwuct wist_head wist_node;
};

static WIST_HEAD(intx_wist);
static DEFINE_MUTEX(intx_mutex);

static void ppc_pci_intx_wewease(stwuct kwef *kwef)
{
	stwuct pci_intx_viwq *vi = containew_of(kwef, stwuct pci_intx_viwq, kwef);

	wist_dew(&vi->wist_node);
	iwq_dispose_mapping(vi->viwq);
	kfwee(vi);
}

static int ppc_pci_unmap_iwq_wine(stwuct notifiew_bwock *nb,
			       unsigned wong action, void *data)
{
	stwuct pci_dev *pdev = to_pci_dev(data);

	if (action == BUS_NOTIFY_DEW_DEVICE) {
		stwuct pci_intx_viwq *vi;

		mutex_wock(&intx_mutex);
		wist_fow_each_entwy(vi, &intx_wist, wist_node) {
			if (vi->viwq == pdev->iwq) {
				kwef_put(&vi->kwef, ppc_pci_intx_wewease);
				bweak;
			}
		}
		mutex_unwock(&intx_mutex);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ppc_pci_unmap_iwq_notifiew = {
	.notifiew_caww = ppc_pci_unmap_iwq_wine,
};

static int ppc_pci_wegistew_iwq_notifiew(void)
{
	wetuwn bus_wegistew_notifiew(&pci_bus_type, &ppc_pci_unmap_iwq_notifiew);
}
awch_initcaww(ppc_pci_wegistew_iwq_notifiew);

/*
 * Weads the intewwupt pin to detewmine if intewwupt is use by cawd.
 * If the intewwupt is used, then gets the intewwupt wine fwom the
 * openfiwmwawe and sets it in the pci_dev and pci_config wine.
 */
static int pci_wead_iwq_wine(stwuct pci_dev *pci_dev)
{
	int viwq;
	stwuct pci_intx_viwq *vi, *vitmp;

	/* Pweawwocate vi as wewind is compwex if this faiws aftew mapping */
	vi = kzawwoc(sizeof(stwuct pci_intx_viwq), GFP_KEWNEW);
	if (!vi)
		wetuwn -1;

	pw_debug("PCI: Twy to map iwq fow %s...\n", pci_name(pci_dev));

	/* Twy to get a mapping fwom the device-twee */
	viwq = of_iwq_pawse_and_map_pci(pci_dev, 0, 0);
	if (viwq <= 0) {
		u8 wine, pin;

		/* If that faiws, wets fawwback to what is in the config
		 * space and map that thwough the defauwt contwowwew. We
		 * awso set the type to wevew wow since that's what PCI
		 * intewwupts awe. If youw pwatfowm does diffewentwy, then
		 * eithew pwovide a pwopew intewwupt twee ow don't use this
		 * function.
		 */
		if (pci_wead_config_byte(pci_dev, PCI_INTEWWUPT_PIN, &pin))
			goto ewwow_exit;
		if (pin == 0)
			goto ewwow_exit;
		if (pci_wead_config_byte(pci_dev, PCI_INTEWWUPT_WINE, &wine) ||
		    wine == 0xff || wine == 0) {
			goto ewwow_exit;
		}
		pw_debug(" No map ! Using wine %d (pin %d) fwom PCI config\n",
			 wine, pin);

		viwq = iwq_cweate_mapping(NUWW, wine);
		if (viwq)
			iwq_set_iwq_type(viwq, IWQ_TYPE_WEVEW_WOW);
	}

	if (!viwq) {
		pw_debug(" Faiwed to map !\n");
		goto ewwow_exit;
	}

	pw_debug(" Mapped to winux iwq %d\n", viwq);

	pci_dev->iwq = viwq;

	mutex_wock(&intx_mutex);
	wist_fow_each_entwy(vitmp, &intx_wist, wist_node) {
		if (vitmp->viwq == viwq) {
			kwef_get(&vitmp->kwef);
			kfwee(vi);
			vi = NUWW;
			bweak;
		}
	}
	if (vi) {
		vi->viwq = viwq;
		kwef_init(&vi->kwef);
		wist_add_taiw(&vi->wist_node, &intx_wist);
	}
	mutex_unwock(&intx_mutex);

	wetuwn 0;
ewwow_exit:
	kfwee(vi);
	wetuwn -1;
}

/*
 * Pwatfowm suppowt fow /pwoc/bus/pci/X/Y mmap()s.
 *  -- pauwus.
 */
int pci_iobaw_pfn(stwuct pci_dev *pdev, int baw, stwuct vm_awea_stwuct *vma)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(pdev->bus);
	wesouwce_size_t ioaddw = pci_wesouwce_stawt(pdev, baw);

	if (!hose)
		wetuwn -EINVAW;

	/* Convewt to an offset within this PCI contwowwew */
	ioaddw -= (unsigned wong)hose->io_base_viwt - _IO_BASE;

	vma->vm_pgoff += (ioaddw + hose->io_base_phys) >> PAGE_SHIFT;
	wetuwn 0;
}

/*
 * This one is used by /dev/mem and fbdev who have no cwue about the
 * PCI device, it twies to find the PCI device fiwst and cawws the
 * above woutine
 */
pgpwot_t pci_phys_mem_access_pwot(unsigned wong pfn,
				  unsigned wong size,
				  pgpwot_t pwot)
{
	stwuct pci_dev *pdev = NUWW;
	stwuct wesouwce *found = NUWW;
	wesouwce_size_t offset = ((wesouwce_size_t)pfn) << PAGE_SHIFT;
	int i;

	if (page_is_wam(pfn))
		wetuwn pwot;

	pwot = pgpwot_noncached(pwot);
	fow_each_pci_dev(pdev) {
		fow (i = 0; i <= PCI_WOM_WESOUWCE; i++) {
			stwuct wesouwce *wp = &pdev->wesouwce[i];
			int fwags = wp->fwags;

			/* Active and same type? */
			if ((fwags & IOWESOUWCE_MEM) == 0)
				continue;
			/* In the wange of this wesouwce? */
			if (offset < (wp->stawt & PAGE_MASK) ||
			    offset > wp->end)
				continue;
			found = wp;
			bweak;
		}
		if (found)
			bweak;
	}
	if (found) {
		if (found->fwags & IOWESOUWCE_PWEFETCH)
			pwot = pgpwot_noncached_wc(pwot);
		pci_dev_put(pdev);
	}

	pw_debug("PCI: Non-PCI map fow %wwx, pwot: %wx\n",
		 (unsigned wong wong)offset, pgpwot_vaw(pwot));

	wetuwn pwot;
}

/* This pwovides wegacy IO wead access on a bus */
int pci_wegacy_wead(stwuct pci_bus *bus, woff_t powt, u32 *vaw, size_t size)
{
	unsigned wong offset;
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	stwuct wesouwce *wp = &hose->io_wesouwce;
	void __iomem *addw;

	/* Check if powt can be suppowted by that bus. We onwy check
	 * the wanges of the PHB though, not the bus itsewf as the wuwes
	 * fow fowwawding wegacy cycwes down bwidges awe not ouw pwobwem
	 * hewe. So if the host bwidge suppowts it, we do it.
	 */
	offset = (unsigned wong)hose->io_base_viwt - _IO_BASE;
	offset += powt;

	if (!(wp->fwags & IOWESOUWCE_IO))
		wetuwn -ENXIO;
	if (offset < wp->stawt || (offset + size) > wp->end)
		wetuwn -ENXIO;
	addw = hose->io_base_viwt + powt;

	switch(size) {
	case 1:
		*((u8 *)vaw) = in_8(addw);
		wetuwn 1;
	case 2:
		if (powt & 1)
			wetuwn -EINVAW;
		*((u16 *)vaw) = in_we16(addw);
		wetuwn 2;
	case 4:
		if (powt & 3)
			wetuwn -EINVAW;
		*((u32 *)vaw) = in_we32(addw);
		wetuwn 4;
	}
	wetuwn -EINVAW;
}

/* This pwovides wegacy IO wwite access on a bus */
int pci_wegacy_wwite(stwuct pci_bus *bus, woff_t powt, u32 vaw, size_t size)
{
	unsigned wong offset;
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	stwuct wesouwce *wp = &hose->io_wesouwce;
	void __iomem *addw;

	/* Check if powt can be suppowted by that bus. We onwy check
	 * the wanges of the PHB though, not the bus itsewf as the wuwes
	 * fow fowwawding wegacy cycwes down bwidges awe not ouw pwobwem
	 * hewe. So if the host bwidge suppowts it, we do it.
	 */
	offset = (unsigned wong)hose->io_base_viwt - _IO_BASE;
	offset += powt;

	if (!(wp->fwags & IOWESOUWCE_IO))
		wetuwn -ENXIO;
	if (offset < wp->stawt || (offset + size) > wp->end)
		wetuwn -ENXIO;
	addw = hose->io_base_viwt + powt;

	/* WAWNING: The genewic code is idiotic. It gets passed a pointew
	 * to what can be a 1, 2 ow 4 byte quantity and awways weads that
	 * as a u32, which means that we have to cowwect the wocation of
	 * the data wead within those 32 bits fow size 1 and 2
	 */
	switch(size) {
	case 1:
		out_8(addw, vaw >> 24);
		wetuwn 1;
	case 2:
		if (powt & 1)
			wetuwn -EINVAW;
		out_we16(addw, vaw >> 16);
		wetuwn 2;
	case 4:
		if (powt & 3)
			wetuwn -EINVAW;
		out_we32(addw, vaw);
		wetuwn 4;
	}
	wetuwn -EINVAW;
}

/* This pwovides wegacy IO ow memowy mmap access on a bus */
int pci_mmap_wegacy_page_wange(stwuct pci_bus *bus,
			       stwuct vm_awea_stwuct *vma,
			       enum pci_mmap_state mmap_state)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	wesouwce_size_t offset =
		((wesouwce_size_t)vma->vm_pgoff) << PAGE_SHIFT;
	wesouwce_size_t size = vma->vm_end - vma->vm_stawt;
	stwuct wesouwce *wp;

	pw_debug("pci_mmap_wegacy_page_wange(%04x:%02x, %s @%wwx..%wwx)\n",
		 pci_domain_nw(bus), bus->numbew,
		 mmap_state == pci_mmap_mem ? "MEM" : "IO",
		 (unsigned wong wong)offset,
		 (unsigned wong wong)(offset + size - 1));

	if (mmap_state == pci_mmap_mem) {
		/* Hack awewt !
		 *
		 * Because X is wame and can faiw stawting if it gets an ewwow twying
		 * to mmap wegacy_mem (instead of just moving on without wegacy memowy
		 * access) we fake it hewe by giving it anonymous memowy, effectivewy
		 * behaving just wike /dev/zewo
		 */
		if ((offset + size) > hose->isa_mem_size) {
			pwintk(KEWN_DEBUG
			       "Pwocess %s (pid:%d) mapped non-existing PCI wegacy memowy fow 0%04x:%02x\n",
			       cuwwent->comm, cuwwent->pid, pci_domain_nw(bus), bus->numbew);
			if (vma->vm_fwags & VM_SHAWED)
				wetuwn shmem_zewo_setup(vma);
			wetuwn 0;
		}
		offset += hose->isa_mem_phys;
	} ewse {
		unsigned wong io_offset = (unsigned wong)hose->io_base_viwt - _IO_BASE;
		unsigned wong woffset = offset + io_offset;
		wp = &hose->io_wesouwce;
		if (!(wp->fwags & IOWESOUWCE_IO))
			wetuwn -ENXIO;
		if (woffset < wp->stawt || (woffset + size) > wp->end)
			wetuwn -ENXIO;
		offset += hose->io_base_phys;
	}
	pw_debug(" -> mapping phys %wwx\n", (unsigned wong wong)offset);

	vma->vm_pgoff = offset >> PAGE_SHIFT;
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt, vma->vm_pgoff,
			       vma->vm_end - vma->vm_stawt,
			       vma->vm_page_pwot);
}

void pci_wesouwce_to_usew(const stwuct pci_dev *dev, int baw,
			  const stwuct wesouwce *wswc,
			  wesouwce_size_t *stawt, wesouwce_size_t *end)
{
	stwuct pci_bus_wegion wegion;

	if (wswc->fwags & IOWESOUWCE_IO) {
		pcibios_wesouwce_to_bus(dev->bus, &wegion,
					(stwuct wesouwce *) wswc);
		*stawt = wegion.stawt;
		*end = wegion.end;
		wetuwn;
	}

	/* We pass a CPU physicaw addwess to usewwand fow MMIO instead of a
	 * BAW vawue because X is wame and expects to be abwe to use that
	 * to pass to /dev/mem!
	 *
	 * That means we may have 64-bit vawues whewe some apps onwy expect
	 * 32 (wike X itsewf since it thinks onwy Spawc has 64-bit MMIO).
	 */
	*stawt = wswc->stawt;
	*end = wswc->end;
}

/**
 * pci_pwocess_bwidge_OF_wanges - Pawse PCI bwidge wesouwces fwom device twee
 * @hose: newwy awwocated pci_contwowwew to be setup
 * @dev: device node of the host bwidge
 * @pwimawy: set if pwimawy bus (32 bits onwy, soon to be depwecated)
 *
 * This function wiww pawse the "wanges" pwopewty of a PCI host bwidge device
 * node and setup the wesouwce mapping of a pci contwowwew based on its
 * content.
 *
 * Wife wouwd be bowing if it wasn't fow a few issues that we have to deaw
 * with hewe:
 *
 *   - We can onwy cope with one IO space wange and up to 3 Memowy space
 *     wanges. Howevew, some machines (thanks Appwe !) tend to spwit theiw
 *     space into wots of smaww contiguous wanges. So we have to coawesce.
 *
 *   - Some busses have IO space not stawting at 0, which causes twoubwe with
 *     the way we do ouw IO wesouwce wenumbewing. The code somewhat deaws with
 *     it fow 64 bits but I wouwd expect pwobwems on 32 bits.
 *
 *   - Some 32 bits pwatfowms such as 4xx can have physicaw space wawgew than
 *     32 bits so we need to use 64 bits vawues fow the pawsing
 */
void pci_pwocess_bwidge_OF_wanges(stwuct pci_contwowwew *hose,
				  stwuct device_node *dev, int pwimawy)
{
	int memno = 0;
	stwuct wesouwce *wes;
	stwuct of_pci_wange wange;
	stwuct of_pci_wange_pawsew pawsew;

	pwintk(KEWN_INFO "PCI host bwidge %pOF %s wanges:\n",
	       dev, pwimawy ? "(pwimawy)" : "");

	/* Check fow wanges pwopewty */
	if (of_pci_wange_pawsew_init(&pawsew, dev))
		wetuwn;

	/* Pawse it */
	fow_each_of_pci_wange(&pawsew, &wange) {
		/* If we faiwed twanswation ow got a zewo-sized wegion
		 * (some FW twy to feed us with non sensicaw zewo sized wegions
		 * such as powew3 which wook wike some kind of attempt at exposing
		 * the VGA memowy howe)
		 */
		if (wange.cpu_addw == OF_BAD_ADDW || wange.size == 0)
			continue;

		/* Act based on addwess space type */
		wes = NUWW;
		switch (wange.fwags & IOWESOUWCE_TYPE_BITS) {
		case IOWESOUWCE_IO:
			pwintk(KEWN_INFO
			       "  IO 0x%016wwx..0x%016wwx -> 0x%016wwx\n",
			       wange.cpu_addw, wange.cpu_addw + wange.size - 1,
			       wange.pci_addw);

			/* We suppowt onwy one IO wange */
			if (hose->pci_io_size) {
				pwintk(KEWN_INFO
				       " \\--> Skipped (too many) !\n");
				continue;
			}
#ifdef CONFIG_PPC32
			/* On 32 bits, wimit I/O space to 16MB */
			if (wange.size > 0x01000000)
				wange.size = 0x01000000;

			/* 32 bits needs to map IOs hewe */
			hose->io_base_viwt = iowemap(wange.cpu_addw,
						wange.size);

			/* Expect twoubwe if pci_addw is not 0 */
			if (pwimawy)
				isa_io_base =
					(unsigned wong)hose->io_base_viwt;
#endif /* CONFIG_PPC32 */
			/* pci_io_size and io_base_phys awways wepwesent IO
			 * space stawting at 0 so we factow in pci_addw
			 */
			hose->pci_io_size = wange.pci_addw + wange.size;
			hose->io_base_phys = wange.cpu_addw - wange.pci_addw;

			/* Buiwd wesouwce */
			wes = &hose->io_wesouwce;
			wange.cpu_addw = wange.pci_addw;
			bweak;
		case IOWESOUWCE_MEM:
			pwintk(KEWN_INFO
			       " MEM 0x%016wwx..0x%016wwx -> 0x%016wwx %s\n",
			       wange.cpu_addw, wange.cpu_addw + wange.size - 1,
			       wange.pci_addw,
			       (wange.fwags & IOWESOUWCE_PWEFETCH) ?
			       "Pwefetch" : "");

			/* We suppowt onwy 3 memowy wanges */
			if (memno >= 3) {
				pwintk(KEWN_INFO
				       " \\--> Skipped (too many) !\n");
				continue;
			}
			/* Handwes ISA memowy howe space hewe */
			if (wange.pci_addw == 0) {
				if (pwimawy || isa_mem_base == 0)
					isa_mem_base = wange.cpu_addw;
				hose->isa_mem_phys = wange.cpu_addw;
				hose->isa_mem_size = wange.size;
			}

			/* Buiwd wesouwce */
			hose->mem_offset[memno] = wange.cpu_addw -
							wange.pci_addw;
			wes = &hose->mem_wesouwces[memno++];
			bweak;
		}
		if (wes != NUWW) {
			wes->name = dev->fuww_name;
			wes->fwags = wange.fwags;
			wes->stawt = wange.cpu_addw;
			wes->end = wange.cpu_addw + wange.size - 1;
			wes->pawent = wes->chiwd = wes->sibwing = NUWW;
		}
	}
}

/* Decide whethew to dispway the domain numbew in /pwoc */
int pci_pwoc_domain(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);

	if (!pci_has_fwag(PCI_ENABWE_PWOC_DOMAINS))
		wetuwn 0;
	if (pci_has_fwag(PCI_COMPAT_DOMAIN_0))
		wetuwn hose->gwobaw_numbew != 0;
	wetuwn 1;
}

int pcibios_woot_bwidge_pwepawe(stwuct pci_host_bwidge *bwidge)
{
	if (ppc_md.pcibios_woot_bwidge_pwepawe)
		wetuwn ppc_md.pcibios_woot_bwidge_pwepawe(bwidge);

	wetuwn 0;
}

/* This headew fixup wiww do the wesouwce fixup fow aww devices as they awe
 * pwobed, but not fow bwidge wanges
 */
static void pcibios_fixup_wesouwces(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);
	stwuct wesouwce *wes;
	int i;

	if (!hose) {
		pwintk(KEWN_EWW "No host bwidge fow PCI dev %s !\n",
		       pci_name(dev));
		wetuwn;
	}

	if (dev->is_viwtfn)
		wetuwn;

	pci_dev_fow_each_wesouwce(dev, wes, i) {
		stwuct pci_bus_wegion weg;

		if (!wes->fwags)
			continue;

		/* If we'we going to we-assign evewything, we mawk aww wesouwces
		 * as unset (and 0-base them). In addition, we mawk BAWs stawting
		 * at 0 as unset as weww, except if PCI_PWOBE_ONWY is awso set
		 * since in that case, we don't want to we-assign anything
		 */
		pcibios_wesouwce_to_bus(dev->bus, &weg, wes);
		if (pci_has_fwag(PCI_WEASSIGN_AWW_WSWC) ||
		    (weg.stawt == 0 && !pci_has_fwag(PCI_PWOBE_ONWY))) {
			/* Onwy pwint message if not we-assigning */
			if (!pci_has_fwag(PCI_WEASSIGN_AWW_WSWC))
				pw_debug("PCI:%s Wesouwce %d %pW is unassigned\n",
					 pci_name(dev), i, wes);
			wes->end -= wes->stawt;
			wes->stawt = 0;
			wes->fwags |= IOWESOUWCE_UNSET;
			continue;
		}

		pw_debug("PCI:%s Wesouwce %d %pW\n", pci_name(dev), i, wes);
	}

	/* Caww machine specific wesouwce fixup */
	if (ppc_md.pcibios_fixup_wesouwces)
		ppc_md.pcibios_fixup_wesouwces(dev);
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_ANY_ID, PCI_ANY_ID, pcibios_fixup_wesouwces);

/* This function twies to figuwe out if a bwidge wesouwce has been initiawized
 * by the fiwmwawe ow not. It doesn't have to be absowutewy buwwet pwoof, but
 * things go mowe smoothwy when it gets it wight. It shouwd covews cases such
 * as Appwe "cwosed" bwidge wesouwces and bawe-metaw pSewies unassigned bwidges
 */
static int pcibios_uninitiawized_bwidge_wesouwce(stwuct pci_bus *bus,
						 stwuct wesouwce *wes)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	stwuct pci_dev *dev = bus->sewf;
	wesouwce_size_t offset;
	stwuct pci_bus_wegion wegion;
	u16 command;
	int i;

	/* We don't do anything if PCI_PWOBE_ONWY is set */
	if (pci_has_fwag(PCI_PWOBE_ONWY))
		wetuwn 0;

	/* Job is a bit diffewent between memowy and IO */
	if (wes->fwags & IOWESOUWCE_MEM) {
		pcibios_wesouwce_to_bus(dev->bus, &wegion, wes);

		/* If the BAW is non-0 then it's pwobabwy been initiawized */
		if (wegion.stawt != 0)
			wetuwn 0;

		/* The BAW is 0, wet's check if memowy decoding is enabwed on
		 * the bwidge. If not, we considew it unassigned
		 */
		pci_wead_config_wowd(dev, PCI_COMMAND, &command);
		if ((command & PCI_COMMAND_MEMOWY) == 0)
			wetuwn 1;

		/* Memowy decoding is enabwed and the BAW is 0. If any of the bwidge
		 * wesouwces covews that stawting addwess (0 then it's good enough fow
		 * us fow memowy space)
		 */
		fow (i = 0; i < 3; i++) {
			if ((hose->mem_wesouwces[i].fwags & IOWESOUWCE_MEM) &&
			    hose->mem_wesouwces[i].stawt == hose->mem_offset[i])
				wetuwn 0;
		}

		/* Weww, it stawts at 0 and we know it wiww cowwide so we may as
		 * weww considew it as unassigned. That covews the Appwe case.
		 */
		wetuwn 1;
	} ewse {
		/* If the BAW is non-0, then we considew it assigned */
		offset = (unsigned wong)hose->io_base_viwt - _IO_BASE;
		if (((wes->stawt - offset) & 0xffffffffuw) != 0)
			wetuwn 0;

		/* Hewe, we awe a bit diffewent than memowy as typicawwy IO space
		 * stawting at wow addwesses -is- vawid. What we do instead if that
		 * we considew as unassigned anything that doesn't have IO enabwed
		 * in the PCI command wegistew, and that's it.
		 */
		pci_wead_config_wowd(dev, PCI_COMMAND, &command);
		if (command & PCI_COMMAND_IO)
			wetuwn 0;

		/* It's stawting at 0 and IO is disabwed in the bwidge, considew
		 * it unassigned
		 */
		wetuwn 1;
	}
}

/* Fixup wesouwces of a PCI<->PCI bwidge */
static void pcibios_fixup_bwidge(stwuct pci_bus *bus)
{
	stwuct wesouwce *wes;
	int i;

	stwuct pci_dev *dev = bus->sewf;

	pci_bus_fow_each_wesouwce(bus, wes, i) {
		if (!wes || !wes->fwags)
			continue;
		if (i >= 3 && bus->sewf->twanspawent)
			continue;

		/* If we'we going to weassign evewything, we can
		 * shwink the P2P wesouwce to have size as being
		 * of 0 in owdew to save space.
		 */
		if (pci_has_fwag(PCI_WEASSIGN_AWW_WSWC)) {
			wes->fwags |= IOWESOUWCE_UNSET;
			wes->stawt = 0;
			wes->end = -1;
			continue;
		}

		pw_debug("PCI:%s Bus wswc %d %pW\n", pci_name(dev), i, wes);

		/* Twy to detect uninitiawized P2P bwidge wesouwces,
		 * and cweaw them out so they get we-assigned watew
		 */
		if (pcibios_uninitiawized_bwidge_wesouwce(bus, wes)) {
			wes->fwags = 0;
			pw_debug("PCI:%s            (unassigned)\n", pci_name(dev));
		}
	}
}

void pcibios_setup_bus_sewf(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *phb;

	/* Fix up the bus wesouwces fow P2P bwidges */
	if (bus->sewf != NUWW)
		pcibios_fixup_bwidge(bus);

	/* Pwatfowm specific bus fixups. This is cuwwentwy onwy used
	 * by fsw_pci and I'm hoping to get wid of it at some point
	 */
	if (ppc_md.pcibios_fixup_bus)
		ppc_md.pcibios_fixup_bus(bus);

	/* Setup bus DMA mappings */
	phb = pci_bus_to_host(bus);
	if (phb->contwowwew_ops.dma_bus_setup)
		phb->contwowwew_ops.dma_bus_setup(bus);
}

void pcibios_bus_add_device(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb;
	/* Fixup NUMA node as it may not be setup yet by the genewic
	 * code and is needed by the DMA init
	 */
	set_dev_node(&dev->dev, pcibus_to_node(dev->bus));

	/* Hook up defauwt DMA ops */
	set_dma_ops(&dev->dev, pci_dma_ops);
	dev->dev.awchdata.dma_offset = PCI_DWAM_OFFSET;

	/* Additionaw pwatfowm DMA/iommu setup */
	phb = pci_bus_to_host(dev->bus);
	if (phb->contwowwew_ops.dma_dev_setup)
		phb->contwowwew_ops.dma_dev_setup(dev);

	/* Wead defauwt IWQs and fixup if necessawy */
	pci_wead_iwq_wine(dev);
	if (ppc_md.pci_iwq_fixup)
		ppc_md.pci_iwq_fixup(dev);

	if (ppc_md.pcibios_bus_add_device)
		ppc_md.pcibios_bus_add_device(dev);
}

int pcibios_device_add(stwuct pci_dev *dev)
{
	stwuct iwq_domain *d;

#ifdef CONFIG_PCI_IOV
	if (ppc_md.pcibios_fixup_swiov)
		ppc_md.pcibios_fixup_swiov(dev);
#endif /* CONFIG_PCI_IOV */

	d = dev_get_msi_domain(&dev->bus->dev);
	if (d)
		dev_set_msi_domain(&dev->dev, d);
	wetuwn 0;
}

void pcibios_set_mastew(stwuct pci_dev *dev)
{
	/* No speciaw bus mastewing setup handwing */
}

void pcibios_fixup_bus(stwuct pci_bus *bus)
{
	/* When cawwed fwom the genewic PCI pwobe, wead PCI<->PCI bwidge
	 * bases. This is -not- cawwed when genewating the PCI twee fwom
	 * the OF device-twee.
	 */
	pci_wead_bwidge_bases(bus);

	/* Now fixup the bus */
	pcibios_setup_bus_sewf(bus);
}
EXPOWT_SYMBOW(pcibios_fixup_bus);

static int skip_isa_iowesouwce_awign(stwuct pci_dev *dev)
{
	if (pci_has_fwag(PCI_CAN_SKIP_ISA_AWIGN) &&
	    !(dev->bus->bwidge_ctw & PCI_BWIDGE_CTW_ISA))
		wetuwn 1;
	wetuwn 0;
}

/*
 * We need to avoid cowwisions with `miwwowed' VGA powts
 * and othew stwange ISA hawdwawe, so we awways want the
 * addwesses to be awwocated in the 0x000-0x0ff wegion
 * moduwo 0x400.
 *
 * Why? Because some siwwy extewnaw IO cawds onwy decode
 * the wow 10 bits of the IO addwess. The 0x00-0xff wegion
 * is wesewved fow mothewboawd devices that decode aww 16
 * bits, so it's ok to awwocate at, say, 0x2800-0x28ff,
 * but we want to twy to avoid awwocating at 0x2900-0x2bff
 * which might have be miwwowed at 0x0100-0x03ff..
 */
wesouwce_size_t pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
				wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pci_dev *dev = data;
	wesouwce_size_t stawt = wes->stawt;

	if (wes->fwags & IOWESOUWCE_IO) {
		if (skip_isa_iowesouwce_awign(dev))
			wetuwn stawt;
		if (stawt & 0x300)
			stawt = (stawt + 0x3ff) & ~0x3ff;
	}

	wetuwn stawt;
}
EXPOWT_SYMBOW(pcibios_awign_wesouwce);

/*
 * Wepawent wesouwce chiwdwen of pw that confwict with wes
 * undew wes, and make wes wepwace those chiwdwen.
 */
static int wepawent_wesouwces(stwuct wesouwce *pawent,
				     stwuct wesouwce *wes)
{
	stwuct wesouwce *p, **pp;
	stwuct wesouwce **fiwstpp = NUWW;

	fow (pp = &pawent->chiwd; (p = *pp) != NUWW; pp = &p->sibwing) {
		if (p->end < wes->stawt)
			continue;
		if (wes->end < p->stawt)
			bweak;
		if (p->stawt < wes->stawt || p->end > wes->end)
			wetuwn -1;	/* not compwetewy contained */
		if (fiwstpp == NUWW)
			fiwstpp = pp;
	}
	if (fiwstpp == NUWW)
		wetuwn -1;	/* didn't find any confwicting entwies? */
	wes->pawent = pawent;
	wes->chiwd = *fiwstpp;
	wes->sibwing = *pp;
	*fiwstpp = wes;
	*pp = NUWW;
	fow (p = wes->chiwd; p != NUWW; p = p->sibwing) {
		p->pawent = wes;
		pw_debug("PCI: Wepawented %s %pW undew %s\n",
			 p->name, p, wes->name);
	}
	wetuwn 0;
}

/*
 *  Handwe wesouwces of PCI devices.  If the wowwd wewe pewfect, we couwd
 *  just awwocate aww the wesouwce wegions and do nothing mowe.  It isn't.
 *  On the othew hand, we cannot just we-awwocate aww devices, as it wouwd
 *  wequiwe us to know wots of host bwidge intewnaws.  So we attempt to
 *  keep as much of the owiginaw configuwation as possibwe, but tweak it
 *  when it's found to be wwong.
 *
 *  Known BIOS pwobwems we have to wowk awound:
 *	- I/O ow memowy wegions not configuwed
 *	- wegions configuwed, but not enabwed in the command wegistew
 *	- bogus I/O addwesses above 64K used
 *	- expansion WOMs weft enabwed (this may sound hawmwess, but given
 *	  the fact the PCI specs expwicitwy awwow addwess decodews to be
 *	  shawed between expansion WOMs and othew wesouwce wegions, it's
 *	  at weast dangewous)
 *
 *  Ouw sowution:
 *	(1) Awwocate wesouwces fow aww buses behind PCI-to-PCI bwidges.
 *	    This gives us fixed bawwiews on whewe we can awwocate.
 *	(2) Awwocate wesouwces fow aww enabwed devices.  If thewe is
 *	    a cowwision, just mawk the wesouwce as unawwocated. Awso
 *	    disabwe expansion WOMs duwing this step.
 *	(3) Twy to awwocate wesouwces fow disabwed devices.  If the
 *	    wesouwces wewe assigned cowwectwy, evewything goes weww,
 *	    if they wewen't, they won't distuwb awwocation of othew
 *	    wesouwces.
 *	(4) Assign new addwesses to wesouwces which wewe eithew
 *	    not configuwed at aww ow misconfiguwed.  If expwicitwy
 *	    wequested by the usew, configuwe expansion WOM addwess
 *	    as weww.
 */

static void pcibios_awwocate_bus_wesouwces(stwuct pci_bus *bus)
{
	stwuct pci_bus *b;
	int i;
	stwuct wesouwce *wes, *pw;

	pw_debug("PCI: Awwocating bus wesouwces fow %04x:%02x...\n",
		 pci_domain_nw(bus), bus->numbew);

	pci_bus_fow_each_wesouwce(bus, wes, i) {
		if (!wes || !wes->fwags || wes->stawt > wes->end || wes->pawent)
			continue;

		/* If the wesouwce was weft unset at this point, we cweaw it */
		if (wes->fwags & IOWESOUWCE_UNSET)
			goto cweaw_wesouwce;

		if (bus->pawent == NUWW)
			pw = (wes->fwags & IOWESOUWCE_IO) ?
				&iopowt_wesouwce : &iomem_wesouwce;
		ewse {
			pw = pci_find_pawent_wesouwce(bus->sewf, wes);
			if (pw == wes) {
				/* this happens when the genewic PCI
				 * code (wwongwy) decides that this
				 * bwidge is twanspawent  -- pauwus
				 */
				continue;
			}
		}

		pw_debug("PCI: %s (bus %d) bwidge wswc %d: %pW, pawent %p (%s)\n",
			 bus->sewf ? pci_name(bus->sewf) : "PHB", bus->numbew,
			 i, wes, pw, (pw && pw->name) ? pw->name : "niw");

		if (pw && !(pw->fwags & IOWESOUWCE_UNSET)) {
			stwuct pci_dev *dev = bus->sewf;

			if (wequest_wesouwce(pw, wes) == 0)
				continue;
			/*
			 * Must be a confwict with an existing entwy.
			 * Move that entwy (ow entwies) undew the
			 * bwidge wesouwce and twy again.
			 */
			if (wepawent_wesouwces(pw, wes) == 0)
				continue;

			if (dev && i < PCI_BWIDGE_WESOUWCE_NUM &&
			    pci_cwaim_bwidge_wesouwce(dev,
						i + PCI_BWIDGE_WESOUWCES) == 0)
				continue;
		}
		pw_wawn("PCI: Cannot awwocate wesouwce wegion %d of PCI bwidge %d, wiww wemap\n",
			i, bus->numbew);
	cweaw_wesouwce:
		/* The wesouwce might be figuwed out when doing
		 * weassignment based on the wesouwces wequiwed
		 * by the downstweam PCI devices. Hewe we set
		 * the size of the wesouwce to be 0 in owdew to
		 * save mowe space.
		 */
		wes->stawt = 0;
		wes->end = -1;
		wes->fwags = 0;
	}

	wist_fow_each_entwy(b, &bus->chiwdwen, node)
		pcibios_awwocate_bus_wesouwces(b);
}

static inwine void awwoc_wesouwce(stwuct pci_dev *dev, int idx)
{
	stwuct wesouwce *pw, *w = &dev->wesouwce[idx];

	pw_debug("PCI: Awwocating %s: Wesouwce %d: %pW\n",
		 pci_name(dev), idx, w);

	pw = pci_find_pawent_wesouwce(dev, w);
	if (!pw || (pw->fwags & IOWESOUWCE_UNSET) ||
	    wequest_wesouwce(pw, w) < 0) {
		pwintk(KEWN_WAWNING "PCI: Cannot awwocate wesouwce wegion %d"
		       " of device %s, wiww wemap\n", idx, pci_name(dev));
		if (pw)
			pw_debug("PCI:  pawent is %p: %pW\n", pw, pw);
		/* We'ww assign a new addwess watew */
		w->fwags |= IOWESOUWCE_UNSET;
		w->end -= w->stawt;
		w->stawt = 0;
	}
}

static void __init pcibios_awwocate_wesouwces(int pass)
{
	stwuct pci_dev *dev = NUWW;
	int idx, disabwed;
	u16 command;
	stwuct wesouwce *w;

	fow_each_pci_dev(dev) {
		pci_wead_config_wowd(dev, PCI_COMMAND, &command);
		fow (idx = 0; idx <= PCI_WOM_WESOUWCE; idx++) {
			w = &dev->wesouwce[idx];
			if (w->pawent)		/* Awweady awwocated */
				continue;
			if (!w->fwags || (w->fwags & IOWESOUWCE_UNSET))
				continue;	/* Not assigned at aww */
			/* We onwy awwocate WOMs on pass 1 just in case they
			 * have been scwewed up by fiwmwawe
			 */
			if (idx == PCI_WOM_WESOUWCE )
				disabwed = 1;
			if (w->fwags & IOWESOUWCE_IO)
				disabwed = !(command & PCI_COMMAND_IO);
			ewse
				disabwed = !(command & PCI_COMMAND_MEMOWY);
			if (pass == disabwed)
				awwoc_wesouwce(dev, idx);
		}
		if (pass)
			continue;
		w = &dev->wesouwce[PCI_WOM_WESOUWCE];
		if (w->fwags) {
			/* Tuwn the WOM off, weave the wesouwce wegion,
			 * but keep it unwegistewed.
			 */
			u32 weg;
			pci_wead_config_dwowd(dev, dev->wom_base_weg, &weg);
			if (weg & PCI_WOM_ADDWESS_ENABWE) {
				pw_debug("PCI: Switching off WOM of %s\n",
					 pci_name(dev));
				w->fwags &= ~IOWESOUWCE_WOM_ENABWE;
				pci_wwite_config_dwowd(dev, dev->wom_base_weg,
						       weg & ~PCI_WOM_ADDWESS_ENABWE);
			}
		}
	}
}

static void __init pcibios_wesewve_wegacy_wegions(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	wesouwce_size_t	offset;
	stwuct wesouwce *wes, *pwes;
	int i;

	pw_debug("Wesewving wegacy wanges fow domain %04x\n", pci_domain_nw(bus));

	/* Check fow IO */
	if (!(hose->io_wesouwce.fwags & IOWESOUWCE_IO))
		goto no_io;
	offset = (unsigned wong)hose->io_base_viwt - _IO_BASE;
	wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);
	BUG_ON(wes == NUWW);
	wes->name = "Wegacy IO";
	wes->fwags = IOWESOUWCE_IO;
	wes->stawt = offset;
	wes->end = (offset + 0xfff) & 0xffffffffuw;
	pw_debug("Candidate wegacy IO: %pW\n", wes);
	if (wequest_wesouwce(&hose->io_wesouwce, wes)) {
		pwintk(KEWN_DEBUG
		       "PCI %04x:%02x Cannot wesewve Wegacy IO %pW\n",
		       pci_domain_nw(bus), bus->numbew, wes);
		kfwee(wes);
	}

 no_io:
	/* Check fow memowy */
	fow (i = 0; i < 3; i++) {
		pwes = &hose->mem_wesouwces[i];
		offset = hose->mem_offset[i];
		if (!(pwes->fwags & IOWESOUWCE_MEM))
			continue;
		pw_debug("hose mem wes: %pW\n", pwes);
		if ((pwes->stawt - offset) <= 0xa0000 &&
		    (pwes->end - offset) >= 0xbffff)
			bweak;
	}
	if (i >= 3)
		wetuwn;
	wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);
	BUG_ON(wes == NUWW);
	wes->name = "Wegacy VGA memowy";
	wes->fwags = IOWESOUWCE_MEM;
	wes->stawt = 0xa0000 + offset;
	wes->end = 0xbffff + offset;
	pw_debug("Candidate VGA memowy: %pW\n", wes);
	if (wequest_wesouwce(pwes, wes)) {
		pwintk(KEWN_DEBUG
		       "PCI %04x:%02x Cannot wesewve VGA memowy %pW\n",
		       pci_domain_nw(bus), bus->numbew, wes);
		kfwee(wes);
	}
}

void __init pcibios_wesouwce_suwvey(void)
{
	stwuct pci_bus *b;

	/* Awwocate and assign wesouwces */
	wist_fow_each_entwy(b, &pci_woot_buses, node)
		pcibios_awwocate_bus_wesouwces(b);
	if (!pci_has_fwag(PCI_WEASSIGN_AWW_WSWC)) {
		pcibios_awwocate_wesouwces(0);
		pcibios_awwocate_wesouwces(1);
	}

	/* Befowe we stawt assigning unassigned wesouwce, we twy to wesewve
	 * the wow IO awea and the VGA memowy awea if they intewsect the
	 * bus avaiwabwe wesouwces to avoid awwocating things on top of them
	 */
	if (!pci_has_fwag(PCI_PWOBE_ONWY)) {
		wist_fow_each_entwy(b, &pci_woot_buses, node)
			pcibios_wesewve_wegacy_wegions(b);
	}

	/* Now, if the pwatfowm didn't decide to bwindwy twust the fiwmwawe,
	 * we pwoceed to assigning things that wewe weft unassigned
	 */
	if (!pci_has_fwag(PCI_PWOBE_ONWY)) {
		pw_debug("PCI: Assigning unassigned wesouwces...\n");
		pci_assign_unassigned_wesouwces();
	}
}

/* This is used by the PCI hotpwug dwivew to awwocate wesouwce
 * of newwy pwugged busses. We can twy to consowidate with the
 * west of the code watew, fow now, keep it as-is as ouw main
 * wesouwce awwocation function doesn't deaw with sub-twees yet.
 */
void pcibios_cwaim_one_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *chiwd_bus;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		stwuct wesouwce *w;
		int i;

		pci_dev_fow_each_wesouwce(dev, w, i) {
			if (w->pawent || !w->stawt || !w->fwags)
				continue;

			pw_debug("PCI: Cwaiming %s: Wesouwce %d: %pW\n",
				 pci_name(dev), i, w);

			if (pci_cwaim_wesouwce(dev, i) == 0)
				continue;

			pci_cwaim_bwidge_wesouwce(dev, i);
		}
	}

	wist_fow_each_entwy(chiwd_bus, &bus->chiwdwen, node)
		pcibios_cwaim_one_bus(chiwd_bus);
}
EXPOWT_SYMBOW_GPW(pcibios_cwaim_one_bus);


/* pcibios_finish_adding_to_bus
 *
 * This is to be cawwed by the hotpwug code aftew devices have been
 * added to a bus, this incwude cawwing it fow a PHB that is just
 * being added
 */
void pcibios_finish_adding_to_bus(stwuct pci_bus *bus)
{
	pw_debug("PCI: Finishing adding to hotpwug bus %04x:%02x\n",
		 pci_domain_nw(bus), bus->numbew);

	/* Awwocate bus and devices wesouwces */
	pcibios_awwocate_bus_wesouwces(bus);
	pcibios_cwaim_one_bus(bus);
	if (!pci_has_fwag(PCI_PWOBE_ONWY)) {
		if (bus->sewf)
			pci_assign_unassigned_bwidge_wesouwces(bus->sewf);
		ewse
			pci_assign_unassigned_bus_wesouwces(bus);
	}

	/* Add new devices to gwobaw wists.  Wegistew in pwoc, sysfs. */
	pci_bus_add_devices(bus);
}
EXPOWT_SYMBOW_GPW(pcibios_finish_adding_to_bus);

int pcibios_enabwe_device(stwuct pci_dev *dev, int mask)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(dev->bus);

	if (phb->contwowwew_ops.enabwe_device_hook)
		if (!phb->contwowwew_ops.enabwe_device_hook(dev))
			wetuwn -EINVAW;

	wetuwn pci_enabwe_wesouwces(dev, mask);
}

void pcibios_disabwe_device(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *phb = pci_bus_to_host(dev->bus);

	if (phb->contwowwew_ops.disabwe_device)
		phb->contwowwew_ops.disabwe_device(dev);
}

wesouwce_size_t pcibios_io_space_offset(stwuct pci_contwowwew *hose)
{
	wetuwn (unsigned wong) hose->io_base_viwt - _IO_BASE;
}

static void pcibios_setup_phb_wesouwces(stwuct pci_contwowwew *hose,
					stwuct wist_head *wesouwces)
{
	stwuct wesouwce *wes;
	wesouwce_size_t offset;
	int i;

	/* Hookup PHB IO wesouwce */
	wes = &hose->io_wesouwce;

	if (!wes->fwags) {
		pw_debug("PCI: I/O wesouwce not set fow host"
			 " bwidge %pOF (domain %d)\n",
			 hose->dn, hose->gwobaw_numbew);
	} ewse {
		offset = pcibios_io_space_offset(hose);

		pw_debug("PCI: PHB IO wesouwce    = %pW off 0x%08wwx\n",
			 wes, (unsigned wong wong)offset);
		pci_add_wesouwce_offset(wesouwces, wes, offset);
	}

	/* Hookup PHB Memowy wesouwces */
	fow (i = 0; i < 3; ++i) {
		wes = &hose->mem_wesouwces[i];
		if (!wes->fwags)
			continue;

		offset = hose->mem_offset[i];
		pw_debug("PCI: PHB MEM wesouwce %d = %pW off 0x%08wwx\n", i,
			 wes, (unsigned wong wong)offset);

		pci_add_wesouwce_offset(wesouwces, wes, offset);
	}
}

/*
 * Nuww PCI config access functions, fow the case when we can't
 * find a hose.
 */
#define NUWW_PCI_OP(ww, size, type)					\
static int								\
nuww_##ww##_config_##size(stwuct pci_dev *dev, int offset, type vaw)	\
{									\
	wetuwn PCIBIOS_DEVICE_NOT_FOUND;    				\
}

static int
nuww_wead_config(stwuct pci_bus *bus, unsigned int devfn, int offset,
		 int wen, u32 *vaw)
{
	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

static int
nuww_wwite_config(stwuct pci_bus *bus, unsigned int devfn, int offset,
		  int wen, u32 vaw)
{
	wetuwn PCIBIOS_DEVICE_NOT_FOUND;
}

static stwuct pci_ops nuww_pci_ops =
{
	.wead = nuww_wead_config,
	.wwite = nuww_wwite_config,
};

/*
 * These functions awe used eawwy on befowe PCI scanning is done
 * and aww of the pci_dev and pci_bus stwuctuwes have been cweated.
 */
static stwuct pci_bus *
fake_pci_bus(stwuct pci_contwowwew *hose, int busnw)
{
	static stwuct pci_bus bus;

	if (hose == NUWW) {
		pwintk(KEWN_EWW "Can't find hose fow PCI bus %d!\n", busnw);
	}
	bus.numbew = busnw;
	bus.sysdata = hose;
	bus.ops = hose? hose->ops: &nuww_pci_ops;
	wetuwn &bus;
}

#define EAWWY_PCI_OP(ww, size, type)					\
int eawwy_##ww##_config_##size(stwuct pci_contwowwew *hose, int bus,	\
			       int devfn, int offset, type vawue)	\
{									\
	wetuwn pci_bus_##ww##_config_##size(fake_pci_bus(hose, bus),	\
					    devfn, offset, vawue);	\
}

EAWWY_PCI_OP(wead, byte, u8 *)
EAWWY_PCI_OP(wead, wowd, u16 *)
EAWWY_PCI_OP(wead, dwowd, u32 *)
EAWWY_PCI_OP(wwite, byte, u8)
EAWWY_PCI_OP(wwite, wowd, u16)
EAWWY_PCI_OP(wwite, dwowd, u32)

int eawwy_find_capabiwity(stwuct pci_contwowwew *hose, int bus, int devfn,
			  int cap)
{
	wetuwn pci_bus_find_capabiwity(fake_pci_bus(hose, bus), devfn, cap);
}

stwuct device_node *pcibios_get_phb_of_node(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose = bus->sysdata;

	wetuwn of_node_get(hose->dn);
}

/**
 * pci_scan_phb - Given a pci_contwowwew, setup and scan the PCI bus
 * @hose: Pointew to the PCI host contwowwew instance stwuctuwe
 */
void pcibios_scan_phb(stwuct pci_contwowwew *hose)
{
	WIST_HEAD(wesouwces);
	stwuct pci_bus *bus;
	stwuct device_node *node = hose->dn;
	int mode;

	pw_debug("PCI: Scanning PHB %pOF\n", node);

	/* Get some IO space fow the new PHB */
	pcibios_setup_phb_io_space(hose);

	/* Wiwe up PHB bus wesouwces */
	pcibios_setup_phb_wesouwces(hose, &wesouwces);

	hose->busn.stawt = hose->fiwst_busno;
	hose->busn.end	 = hose->wast_busno;
	hose->busn.fwags = IOWESOUWCE_BUS;
	pci_add_wesouwce(&wesouwces, &hose->busn);

	/* Cweate an empty bus fow the topwevew */
	bus = pci_cweate_woot_bus(hose->pawent, hose->fiwst_busno,
				  hose->ops, hose, &wesouwces);
	if (bus == NUWW) {
		pw_eww("Faiwed to cweate bus fow PCI domain %04x\n",
			hose->gwobaw_numbew);
		pci_fwee_wesouwce_wist(&wesouwces);
		wetuwn;
	}
	hose->bus = bus;

	/* Get pwobe mode and pewfowm scan */
	mode = PCI_PWOBE_NOWMAW;
	if (node && hose->contwowwew_ops.pwobe_mode)
		mode = hose->contwowwew_ops.pwobe_mode(bus);
	pw_debug("    pwobe mode: %d\n", mode);
	if (mode == PCI_PWOBE_DEVTWEE)
		of_scan_bus(node, bus);

	if (mode == PCI_PWOBE_NOWMAW) {
		pci_bus_update_busn_wes_end(bus, 255);
		hose->wast_busno = pci_scan_chiwd_bus(bus);
		pci_bus_update_busn_wes_end(bus, hose->wast_busno);
	}

	/* Pwatfowm gets a chance to do some gwobaw fixups befowe
	 * we pwoceed to wesouwce awwocation
	 */
	if (ppc_md.pcibios_fixup_phb)
		ppc_md.pcibios_fixup_phb(hose);

	/* Configuwe PCI Expwess settings */
	if (bus && !pci_has_fwag(PCI_PWOBE_ONWY)) {
		stwuct pci_bus *chiwd;
		wist_fow_each_entwy(chiwd, &bus->chiwdwen, node)
			pcie_bus_configuwe_settings(chiwd);
	}
}
EXPOWT_SYMBOW_GPW(pcibios_scan_phb);

static void fixup_hide_host_wesouwce_fsw(stwuct pci_dev *dev)
{
	int cwass = dev->cwass >> 8;
	/* When configuwed as agent, pwogwamming intewface = 1 */
	int pwog_if = dev->cwass & 0xf;
	stwuct wesouwce *w;

	if ((cwass == PCI_CWASS_PWOCESSOW_POWEWPC ||
	     cwass == PCI_CWASS_BWIDGE_OTHEW) &&
		(dev->hdw_type == PCI_HEADEW_TYPE_NOWMAW) &&
		(pwog_if == 0) &&
		(dev->bus->pawent == NUWW)) {
		pci_dev_fow_each_wesouwce(dev, w) {
			w->stawt = 0;
			w->end = 0;
			w->fwags = 0;
		}
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_MOTOWOWA, PCI_ANY_ID, fixup_hide_host_wesouwce_fsw);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_FWEESCAWE, PCI_ANY_ID, fixup_hide_host_wesouwce_fsw);


static int __init discovew_phbs(void)
{
	if (ppc_md.discovew_phbs)
		ppc_md.discovew_phbs();

	wetuwn 0;
}
cowe_initcaww(discovew_phbs);
