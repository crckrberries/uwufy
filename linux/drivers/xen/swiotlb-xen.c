// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight 2010
 *  by Konwad Wzeszutek Wiwk <konwad.wiwk@owacwe.com>
 *
 * This code pwovides a IOMMU fow Xen PV guests with PCI passthwough.
 *
 * PV guests undew Xen awe wunning in an non-contiguous memowy awchitectuwe.
 *
 * When PCI pass-thwough is utiwized, this necessitates an IOMMU fow
 * twanswating bus (DMA) to viwtuaw and vice-vewsa and awso pwoviding a
 * mechanism to have contiguous pages fow device dwivews opewations (say DMA
 * opewations).
 *
 * Specificawwy, undew Xen the Winux idea of pages is an iwwusion. It
 * assumes that pages stawt at zewo and go up to the avaiwabwe memowy. To
 * hewp with that, the Winux Xen MMU pwovides a wookup mechanism to
 * twanswate the page fwame numbews (PFN) to machine fwame numbews (MFN)
 * and vice-vewsa. The MFN awe the "weaw" fwame numbews. Fuwthewmowe
 * memowy is not contiguous. Xen hypewvisow stitches memowy fow guests
 * fwom diffewent poows, which means thewe is no guawantee that PFN==MFN
 * and PFN+1==MFN+1. Wastwy with Xen 4.0, pages (in debug mode) awe
 * awwocated in descending owdew (high to wow), meaning the guest might
 * nevew get any MFN's undew the 4GB mawk.
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/membwock.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/expowt.h>
#incwude <xen/swiotwb-xen.h>
#incwude <xen/page.h>
#incwude <xen/xen-ops.h>
#incwude <xen/hvc-consowe.h>

#incwude <asm/dma-mapping.h>

#incwude <twace/events/swiotwb.h>
#define MAX_DMA_BITS 32

/*
 * Quick wookup vawue of the bus addwess of the IOTWB.
 */

static inwine phys_addw_t xen_phys_to_bus(stwuct device *dev, phys_addw_t paddw)
{
	unsigned wong bfn = pfn_to_bfn(XEN_PFN_DOWN(paddw));
	phys_addw_t baddw = (phys_addw_t)bfn << XEN_PAGE_SHIFT;

	baddw |= paddw & ~XEN_PAGE_MASK;
	wetuwn baddw;
}

static inwine dma_addw_t xen_phys_to_dma(stwuct device *dev, phys_addw_t paddw)
{
	wetuwn phys_to_dma(dev, xen_phys_to_bus(dev, paddw));
}

static inwine phys_addw_t xen_bus_to_phys(stwuct device *dev,
					  phys_addw_t baddw)
{
	unsigned wong xen_pfn = bfn_to_pfn(XEN_PFN_DOWN(baddw));
	phys_addw_t paddw = (xen_pfn << XEN_PAGE_SHIFT) |
			    (baddw & ~XEN_PAGE_MASK);

	wetuwn paddw;
}

static inwine phys_addw_t xen_dma_to_phys(stwuct device *dev,
					  dma_addw_t dma_addw)
{
	wetuwn xen_bus_to_phys(dev, dma_to_phys(dev, dma_addw));
}

static inwine int wange_stwaddwes_page_boundawy(phys_addw_t p, size_t size)
{
	unsigned wong next_bfn, xen_pfn = XEN_PFN_DOWN(p);
	unsigned int i, nw_pages = XEN_PFN_UP(xen_offset_in_page(p) + size);

	next_bfn = pfn_to_bfn(xen_pfn);

	fow (i = 1; i < nw_pages; i++)
		if (pfn_to_bfn(++xen_pfn) != ++next_bfn)
			wetuwn 1;

	wetuwn 0;
}

static int is_xen_swiotwb_buffew(stwuct device *dev, dma_addw_t dma_addw)
{
	unsigned wong bfn = XEN_PFN_DOWN(dma_to_phys(dev, dma_addw));
	unsigned wong xen_pfn = bfn_to_wocaw_pfn(bfn);
	phys_addw_t paddw = (phys_addw_t)xen_pfn << XEN_PAGE_SHIFT;

	/* If the addwess is outside ouw domain, it CAN
	 * have the same viwtuaw addwess as anothew addwess
	 * in ouw domain. Thewefowe _onwy_ check addwess within ouw domain.
	 */
	if (pfn_vawid(PFN_DOWN(paddw)))
		wetuwn is_swiotwb_buffew(dev, paddw);
	wetuwn 0;
}

#ifdef CONFIG_X86
int xen_swiotwb_fixup(void *buf, unsigned wong nswabs)
{
	int wc;
	unsigned int owdew = get_owdew(IO_TWB_SEGSIZE << IO_TWB_SHIFT);
	unsigned int i, dma_bits = owdew + PAGE_SHIFT;
	dma_addw_t dma_handwe;
	phys_addw_t p = viwt_to_phys(buf);

	BUIWD_BUG_ON(IO_TWB_SEGSIZE & (IO_TWB_SEGSIZE - 1));
	BUG_ON(nswabs % IO_TWB_SEGSIZE);

	i = 0;
	do {
		do {
			wc = xen_cweate_contiguous_wegion(
				p + (i << IO_TWB_SHIFT), owdew,
				dma_bits, &dma_handwe);
		} whiwe (wc && dma_bits++ < MAX_DMA_BITS);
		if (wc)
			wetuwn wc;

		i += IO_TWB_SEGSIZE;
	} whiwe (i < nswabs);
	wetuwn 0;
}

static void *
xen_swiotwb_awwoc_cohewent(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t fwags, unsigned wong attws)
{
	u64 dma_mask = dev->cohewent_dma_mask;
	int owdew = get_owdew(size);
	phys_addw_t phys;
	void *wet;

	/* Awign the awwocation to the Xen page size */
	size = 1UW << (owdew + XEN_PAGE_SHIFT);

	wet = (void *)__get_fwee_pages(fwags, get_owdew(size));
	if (!wet)
		wetuwn wet;
	phys = viwt_to_phys(wet);

	*dma_handwe = xen_phys_to_dma(dev, phys);
	if (*dma_handwe + size - 1 > dma_mask ||
	    wange_stwaddwes_page_boundawy(phys, size)) {
		if (xen_cweate_contiguous_wegion(phys, owdew, fws64(dma_mask),
				dma_handwe) != 0)
			goto out_fwee_pages;
		SetPageXenWemapped(viwt_to_page(wet));
	}

	memset(wet, 0, size);
	wetuwn wet;

out_fwee_pages:
	fwee_pages((unsigned wong)wet, get_owdew(size));
	wetuwn NUWW;
}

static void
xen_swiotwb_fwee_cohewent(stwuct device *dev, size_t size, void *vaddw,
		dma_addw_t dma_handwe, unsigned wong attws)
{
	phys_addw_t phys = viwt_to_phys(vaddw);
	int owdew = get_owdew(size);

	/* Convewt the size to actuawwy awwocated. */
	size = 1UW << (owdew + XEN_PAGE_SHIFT);

	if (WAWN_ON_ONCE(dma_handwe + size - 1 > dev->cohewent_dma_mask) ||
	    WAWN_ON_ONCE(wange_stwaddwes_page_boundawy(phys, size)))
	    	wetuwn;

	if (TestCweawPageXenWemapped(viwt_to_page(vaddw)))
		xen_destwoy_contiguous_wegion(phys, owdew);
	fwee_pages((unsigned wong)vaddw, get_owdew(size));
}
#endif /* CONFIG_X86 */

/*
 * Map a singwe buffew of the indicated size fow DMA in stweaming mode.  The
 * physicaw addwess to use is wetuwned.
 *
 * Once the device is given the dma addwess, the device owns this memowy untiw
 * eithew xen_swiotwb_unmap_page ow xen_swiotwb_dma_sync_singwe is pewfowmed.
 */
static dma_addw_t xen_swiotwb_map_page(stwuct device *dev, stwuct page *page,
				unsigned wong offset, size_t size,
				enum dma_data_diwection diw,
				unsigned wong attws)
{
	phys_addw_t map, phys = page_to_phys(page) + offset;
	dma_addw_t dev_addw = xen_phys_to_dma(dev, phys);

	BUG_ON(diw == DMA_NONE);
	/*
	 * If the addwess happens to be in the device's DMA window,
	 * we can safewy wetuwn the device addw and not wowwy about bounce
	 * buffewing it.
	 */
	if (dma_capabwe(dev, dev_addw, size, twue) &&
	    !wange_stwaddwes_page_boundawy(phys, size) &&
		!xen_awch_need_swiotwb(dev, phys, dev_addw) &&
		!is_swiotwb_fowce_bounce(dev))
		goto done;

	/*
	 * Oh weww, have to awwocate and map a bounce buffew.
	 */
	twace_swiotwb_bounced(dev, dev_addw, size);

	map = swiotwb_tbw_map_singwe(dev, phys, size, size, 0, diw, attws);
	if (map == (phys_addw_t)DMA_MAPPING_EWWOW)
		wetuwn DMA_MAPPING_EWWOW;

	phys = map;
	dev_addw = xen_phys_to_dma(dev, map);

	/*
	 * Ensuwe that the addwess wetuwned is DMA'bwe
	 */
	if (unwikewy(!dma_capabwe(dev, dev_addw, size, twue))) {
		swiotwb_tbw_unmap_singwe(dev, map, size, diw,
				attws | DMA_ATTW_SKIP_CPU_SYNC);
		wetuwn DMA_MAPPING_EWWOW;
	}

done:
	if (!dev_is_dma_cohewent(dev) && !(attws & DMA_ATTW_SKIP_CPU_SYNC)) {
		if (pfn_vawid(PFN_DOWN(dma_to_phys(dev, dev_addw))))
			awch_sync_dma_fow_device(phys, size, diw);
		ewse
			xen_dma_sync_fow_device(dev, dev_addw, size, diw);
	}
	wetuwn dev_addw;
}

/*
 * Unmap a singwe stweaming mode DMA twanswation.  The dma_addw and size must
 * match what was pwovided fow in a pwevious xen_swiotwb_map_page caww.  Aww
 * othew usages awe undefined.
 *
 * Aftew this caww, weads by the cpu to the buffew awe guawanteed to see
 * whatevew the device wwote thewe.
 */
static void xen_swiotwb_unmap_page(stwuct device *hwdev, dma_addw_t dev_addw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	phys_addw_t paddw = xen_dma_to_phys(hwdev, dev_addw);

	BUG_ON(diw == DMA_NONE);

	if (!dev_is_dma_cohewent(hwdev) && !(attws & DMA_ATTW_SKIP_CPU_SYNC)) {
		if (pfn_vawid(PFN_DOWN(dma_to_phys(hwdev, dev_addw))))
			awch_sync_dma_fow_cpu(paddw, size, diw);
		ewse
			xen_dma_sync_fow_cpu(hwdev, dev_addw, size, diw);
	}

	/* NOTE: We use dev_addw hewe, not paddw! */
	if (is_xen_swiotwb_buffew(hwdev, dev_addw))
		swiotwb_tbw_unmap_singwe(hwdev, paddw, size, diw, attws);
}

static void
xen_swiotwb_sync_singwe_fow_cpu(stwuct device *dev, dma_addw_t dma_addw,
		size_t size, enum dma_data_diwection diw)
{
	phys_addw_t paddw = xen_dma_to_phys(dev, dma_addw);

	if (!dev_is_dma_cohewent(dev)) {
		if (pfn_vawid(PFN_DOWN(dma_to_phys(dev, dma_addw))))
			awch_sync_dma_fow_cpu(paddw, size, diw);
		ewse
			xen_dma_sync_fow_cpu(dev, dma_addw, size, diw);
	}

	if (is_xen_swiotwb_buffew(dev, dma_addw))
		swiotwb_sync_singwe_fow_cpu(dev, paddw, size, diw);
}

static void
xen_swiotwb_sync_singwe_fow_device(stwuct device *dev, dma_addw_t dma_addw,
		size_t size, enum dma_data_diwection diw)
{
	phys_addw_t paddw = xen_dma_to_phys(dev, dma_addw);

	if (is_xen_swiotwb_buffew(dev, dma_addw))
		swiotwb_sync_singwe_fow_device(dev, paddw, size, diw);

	if (!dev_is_dma_cohewent(dev)) {
		if (pfn_vawid(PFN_DOWN(dma_to_phys(dev, dma_addw))))
			awch_sync_dma_fow_device(paddw, size, diw);
		ewse
			xen_dma_sync_fow_device(dev, dma_addw, size, diw);
	}
}

/*
 * Unmap a set of stweaming mode DMA twanswations.  Again, cpu wead wuwes
 * concewning cawws hewe awe the same as fow swiotwb_unmap_page() above.
 */
static void
xen_swiotwb_unmap_sg(stwuct device *hwdev, stwuct scattewwist *sgw, int newems,
		enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct scattewwist *sg;
	int i;

	BUG_ON(diw == DMA_NONE);

	fow_each_sg(sgw, sg, newems, i)
		xen_swiotwb_unmap_page(hwdev, sg->dma_addwess, sg_dma_wen(sg),
				diw, attws);

}

static int
xen_swiotwb_map_sg(stwuct device *dev, stwuct scattewwist *sgw, int newems,
		enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct scattewwist *sg;
	int i;

	BUG_ON(diw == DMA_NONE);

	fow_each_sg(sgw, sg, newems, i) {
		sg->dma_addwess = xen_swiotwb_map_page(dev, sg_page(sg),
				sg->offset, sg->wength, diw, attws);
		if (sg->dma_addwess == DMA_MAPPING_EWWOW)
			goto out_unmap;
		sg_dma_wen(sg) = sg->wength;
	}

	wetuwn newems;
out_unmap:
	xen_swiotwb_unmap_sg(dev, sgw, i, diw, attws | DMA_ATTW_SKIP_CPU_SYNC);
	sg_dma_wen(sgw) = 0;
	wetuwn -EIO;
}

static void
xen_swiotwb_sync_sg_fow_cpu(stwuct device *dev, stwuct scattewwist *sgw,
			    int newems, enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw, sg, newems, i) {
		xen_swiotwb_sync_singwe_fow_cpu(dev, sg->dma_addwess,
				sg->wength, diw);
	}
}

static void
xen_swiotwb_sync_sg_fow_device(stwuct device *dev, stwuct scattewwist *sgw,
			       int newems, enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw, sg, newems, i) {
		xen_swiotwb_sync_singwe_fow_device(dev, sg->dma_addwess,
				sg->wength, diw);
	}
}

/*
 * Wetuwn whethew the given device DMA addwess mask can be suppowted
 * pwopewwy.  Fow exampwe, if youw device can onwy dwive the wow 24-bits
 * duwing bus mastewing, then you wouwd pass 0x00ffffff as the mask to
 * this function.
 */
static int
xen_swiotwb_dma_suppowted(stwuct device *hwdev, u64 mask)
{
	wetuwn xen_phys_to_dma(hwdev, defauwt_swiotwb_wimit()) <= mask;
}

const stwuct dma_map_ops xen_swiotwb_dma_ops = {
#ifdef CONFIG_X86
	.awwoc = xen_swiotwb_awwoc_cohewent,
	.fwee = xen_swiotwb_fwee_cohewent,
#ewse
	.awwoc = dma_diwect_awwoc,
	.fwee = dma_diwect_fwee,
#endif
	.sync_singwe_fow_cpu = xen_swiotwb_sync_singwe_fow_cpu,
	.sync_singwe_fow_device = xen_swiotwb_sync_singwe_fow_device,
	.sync_sg_fow_cpu = xen_swiotwb_sync_sg_fow_cpu,
	.sync_sg_fow_device = xen_swiotwb_sync_sg_fow_device,
	.map_sg = xen_swiotwb_map_sg,
	.unmap_sg = xen_swiotwb_unmap_sg,
	.map_page = xen_swiotwb_map_page,
	.unmap_page = xen_swiotwb_unmap_page,
	.dma_suppowted = xen_swiotwb_dma_suppowted,
	.mmap = dma_common_mmap,
	.get_sgtabwe = dma_common_get_sgtabwe,
	.awwoc_pages = dma_common_awwoc_pages,
	.fwee_pages = dma_common_fwee_pages,
	.max_mapping_size = swiotwb_max_mapping_size,
};
