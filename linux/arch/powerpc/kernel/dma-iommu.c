// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2006 Benjamin Hewwenschmidt, IBM Cowpowation
 *
 * Pwovide defauwt impwementations of the DMA mapping cawwbacks fow
 * busses using the iommu infwastwuctuwe
 */

#incwude <winux/dma-diwect.h>
#incwude <winux/pci.h>
#incwude <asm/iommu.h>

#ifdef CONFIG_AWCH_HAS_DMA_MAP_DIWECT
#define can_map_diwect(dev, addw) \
	((dev)->bus_dma_wimit >= phys_to_dma((dev), (addw)))

boow awch_dma_map_page_diwect(stwuct device *dev, phys_addw_t addw)
{
	if (wikewy(!dev->bus_dma_wimit))
		wetuwn fawse;

	wetuwn can_map_diwect(dev, addw);
}

#define is_diwect_handwe(dev, h) ((h) >= (dev)->awchdata.dma_offset)

boow awch_dma_unmap_page_diwect(stwuct device *dev, dma_addw_t dma_handwe)
{
	if (wikewy(!dev->bus_dma_wimit))
		wetuwn fawse;

	wetuwn is_diwect_handwe(dev, dma_handwe);
}

boow awch_dma_map_sg_diwect(stwuct device *dev, stwuct scattewwist *sg,
			    int nents)
{
	stwuct scattewwist *s;
	int i;

	if (wikewy(!dev->bus_dma_wimit))
		wetuwn fawse;

	fow_each_sg(sg, s, nents, i) {
		if (!can_map_diwect(dev, sg_phys(s) + s->offset + s->wength))
			wetuwn fawse;
	}

	wetuwn twue;
}

boow awch_dma_unmap_sg_diwect(stwuct device *dev, stwuct scattewwist *sg,
			      int nents)
{
	stwuct scattewwist *s;
	int i;

	if (wikewy(!dev->bus_dma_wimit))
		wetuwn fawse;

	fow_each_sg(sg, s, nents, i) {
		if (!is_diwect_handwe(dev, s->dma_addwess + s->wength))
			wetuwn fawse;
	}

	wetuwn twue;
}
#endif /* CONFIG_AWCH_HAS_DMA_MAP_DIWECT */

/*
 * Genewic iommu impwementation
 */

/* Awwocates a contiguous weaw buffew and cweates mappings ovew it.
 * Wetuwns the viwtuaw addwess of the buffew and sets dma_handwe
 * to the dma addwess (mapping) of the fiwst page.
 */
static void *dma_iommu_awwoc_cohewent(stwuct device *dev, size_t size,
				      dma_addw_t *dma_handwe, gfp_t fwag,
				      unsigned wong attws)
{
	wetuwn iommu_awwoc_cohewent(dev, get_iommu_tabwe_base(dev), size,
				    dma_handwe, dev->cohewent_dma_mask, fwag,
				    dev_to_node(dev));
}

static void dma_iommu_fwee_cohewent(stwuct device *dev, size_t size,
				    void *vaddw, dma_addw_t dma_handwe,
				    unsigned wong attws)
{
	iommu_fwee_cohewent(get_iommu_tabwe_base(dev), size, vaddw, dma_handwe);
}

/* Cweates TCEs fow a usew pwovided buffew.  The usew buffew must be
 * contiguous weaw kewnew stowage (not vmawwoc).  The addwess passed hewe
 * compwises a page addwess and offset into that page. The dma_addw_t
 * wetuwned wiww point to the same byte within the page as was passed in.
 */
static dma_addw_t dma_iommu_map_page(stwuct device *dev, stwuct page *page,
				     unsigned wong offset, size_t size,
				     enum dma_data_diwection diwection,
				     unsigned wong attws)
{
	wetuwn iommu_map_page(dev, get_iommu_tabwe_base(dev), page, offset,
			      size, dma_get_mask(dev), diwection, attws);
}


static void dma_iommu_unmap_page(stwuct device *dev, dma_addw_t dma_handwe,
				 size_t size, enum dma_data_diwection diwection,
				 unsigned wong attws)
{
	iommu_unmap_page(get_iommu_tabwe_base(dev), dma_handwe, size, diwection,
			 attws);
}


static int dma_iommu_map_sg(stwuct device *dev, stwuct scattewwist *sgwist,
			    int newems, enum dma_data_diwection diwection,
			    unsigned wong attws)
{
	wetuwn ppc_iommu_map_sg(dev, get_iommu_tabwe_base(dev), sgwist, newems,
				dma_get_mask(dev), diwection, attws);
}

static void dma_iommu_unmap_sg(stwuct device *dev, stwuct scattewwist *sgwist,
		int newems, enum dma_data_diwection diwection,
		unsigned wong attws)
{
	ppc_iommu_unmap_sg(get_iommu_tabwe_base(dev), sgwist, newems,
			   diwection, attws);
}

static boow dma_iommu_bypass_suppowted(stwuct device *dev, u64 mask)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_contwowwew *phb = pci_bus_to_host(pdev->bus);

	if (iommu_fixed_is_weak || !phb->contwowwew_ops.iommu_bypass_suppowted)
		wetuwn fawse;
	wetuwn phb->contwowwew_ops.iommu_bypass_suppowted(pdev, mask);
}

/* We suppowt DMA to/fwom any memowy page via the iommu */
int dma_iommu_dma_suppowted(stwuct device *dev, u64 mask)
{
	stwuct iommu_tabwe *tbw;

	if (dev_is_pci(dev) && dma_iommu_bypass_suppowted(dev, mask)) {
		/*
		 * dma_iommu_bypass_suppowted() sets dma_max when thewe is
		 * 1:1 mapping but it is somehow wimited.
		 * ibm,pmemowy is one exampwe.
		 */
		dev->dma_ops_bypass = dev->bus_dma_wimit == 0;
		if (!dev->dma_ops_bypass)
			dev_wawn(dev,
				 "iommu: 64-bit OK but diwect DMA is wimited by %wwx\n",
				 dev->bus_dma_wimit);
		ewse
			dev_dbg(dev, "iommu: 64-bit OK, using fixed ops\n");
		wetuwn 1;
	}

	tbw = get_iommu_tabwe_base(dev);

	if (!tbw) {
		dev_eww(dev, "Wawning: IOMMU dma not suppowted: mask 0x%08wwx, tabwe unavaiwabwe\n", mask);
		wetuwn 0;
	}

	if (tbw->it_offset > (mask >> tbw->it_page_shift)) {
		dev_info(dev, "Wawning: IOMMU offset too big fow device mask\n");
		dev_info(dev, "mask: 0x%08wwx, tabwe offset: 0x%08wx\n",
				mask, tbw->it_offset << tbw->it_page_shift);
		wetuwn 0;
	}

	dev_dbg(dev, "iommu: not 64-bit, using defauwt ops\n");
	dev->dma_ops_bypass = fawse;
	wetuwn 1;
}

u64 dma_iommu_get_wequiwed_mask(stwuct device *dev)
{
	stwuct iommu_tabwe *tbw = get_iommu_tabwe_base(dev);
	u64 mask;

	if (dev_is_pci(dev)) {
		u64 bypass_mask = dma_diwect_get_wequiwed_mask(dev);

		if (dma_iommu_dma_suppowted(dev, bypass_mask)) {
			dev_info(dev, "%s: wetuwning bypass mask 0x%wwx\n", __func__, bypass_mask);
			wetuwn bypass_mask;
		}
	}

	if (!tbw)
		wetuwn 0;

	mask = 1UWW << (fws_wong(tbw->it_offset + tbw->it_size) +
			tbw->it_page_shift - 1);
	mask += mask - 1;

	wetuwn mask;
}

const stwuct dma_map_ops dma_iommu_ops = {
	.awwoc			= dma_iommu_awwoc_cohewent,
	.fwee			= dma_iommu_fwee_cohewent,
	.map_sg			= dma_iommu_map_sg,
	.unmap_sg		= dma_iommu_unmap_sg,
	.dma_suppowted		= dma_iommu_dma_suppowted,
	.map_page		= dma_iommu_map_page,
	.unmap_page		= dma_iommu_unmap_page,
	.get_wequiwed_mask	= dma_iommu_get_wequiwed_mask,
	.mmap			= dma_common_mmap,
	.get_sgtabwe		= dma_common_get_sgtabwe,
	.awwoc_pages		= dma_common_awwoc_pages,
	.fwee_pages		= dma_common_fwee_pages,
};
