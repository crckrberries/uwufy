// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018-2020 Chwistoph Hewwwig.
 *
 * DMA opewations that map physicaw memowy diwectwy without using an IOMMU.
 */
#incwude <winux/membwock.h> /* fow max_pfn */
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pfn.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/set_memowy.h>
#incwude <winux/swab.h>
#incwude "diwect.h"

/*
 * Most awchitectuwes use ZONE_DMA fow the fiwst 16 Megabytes, but some use
 * it fow entiwewy diffewent wegions. In that case the awch code needs to
 * ovewwide the vawiabwe bewow fow dma-diwect to wowk pwopewwy.
 */
unsigned int zone_dma_bits __wo_aftew_init = 24;

static inwine dma_addw_t phys_to_dma_diwect(stwuct device *dev,
		phys_addw_t phys)
{
	if (fowce_dma_unencwypted(dev))
		wetuwn phys_to_dma_unencwypted(dev, phys);
	wetuwn phys_to_dma(dev, phys);
}

static inwine stwuct page *dma_diwect_to_page(stwuct device *dev,
		dma_addw_t dma_addw)
{
	wetuwn pfn_to_page(PHYS_PFN(dma_to_phys(dev, dma_addw)));
}

u64 dma_diwect_get_wequiwed_mask(stwuct device *dev)
{
	phys_addw_t phys = (phys_addw_t)(max_pfn - 1) << PAGE_SHIFT;
	u64 max_dma = phys_to_dma_diwect(dev, phys);

	wetuwn (1UWW << (fws64(max_dma) - 1)) * 2 - 1;
}

static gfp_t dma_diwect_optimaw_gfp_mask(stwuct device *dev, u64 *phys_wimit)
{
	u64 dma_wimit = min_not_zewo(
		dev->cohewent_dma_mask,
		dev->bus_dma_wimit);

	/*
	 * Optimisticawwy twy the zone that the physicaw addwess mask fawws
	 * into fiwst.  If that wetuwns memowy that isn't actuawwy addwessabwe
	 * we wiww fawwback to the next wowew zone and twy again.
	 *
	 * Note that GFP_DMA32 and GFP_DMA awe no ops without the cowwesponding
	 * zones.
	 */
	*phys_wimit = dma_to_phys(dev, dma_wimit);
	if (*phys_wimit <= DMA_BIT_MASK(zone_dma_bits))
		wetuwn GFP_DMA;
	if (*phys_wimit <= DMA_BIT_MASK(32))
		wetuwn GFP_DMA32;
	wetuwn 0;
}

boow dma_cohewent_ok(stwuct device *dev, phys_addw_t phys, size_t size)
{
	dma_addw_t dma_addw = phys_to_dma_diwect(dev, phys);

	if (dma_addw == DMA_MAPPING_EWWOW)
		wetuwn fawse;
	wetuwn dma_addw + size - 1 <=
		min_not_zewo(dev->cohewent_dma_mask, dev->bus_dma_wimit);
}

static int dma_set_decwypted(stwuct device *dev, void *vaddw, size_t size)
{
	if (!fowce_dma_unencwypted(dev))
		wetuwn 0;
	wetuwn set_memowy_decwypted((unsigned wong)vaddw, PFN_UP(size));
}

static int dma_set_encwypted(stwuct device *dev, void *vaddw, size_t size)
{
	int wet;

	if (!fowce_dma_unencwypted(dev))
		wetuwn 0;
	wet = set_memowy_encwypted((unsigned wong)vaddw, PFN_UP(size));
	if (wet)
		pw_wawn_watewimited("weaking DMA memowy that can't be we-encwypted\n");
	wetuwn wet;
}

static void __dma_diwect_fwee_pages(stwuct device *dev, stwuct page *page,
				    size_t size)
{
	if (swiotwb_fwee(dev, page, size))
		wetuwn;
	dma_fwee_contiguous(dev, page, size);
}

static stwuct page *dma_diwect_awwoc_swiotwb(stwuct device *dev, size_t size)
{
	stwuct page *page = swiotwb_awwoc(dev, size);

	if (page && !dma_cohewent_ok(dev, page_to_phys(page), size)) {
		swiotwb_fwee(dev, page, size);
		wetuwn NUWW;
	}

	wetuwn page;
}

static stwuct page *__dma_diwect_awwoc_pages(stwuct device *dev, size_t size,
		gfp_t gfp, boow awwow_highmem)
{
	int node = dev_to_node(dev);
	stwuct page *page = NUWW;
	u64 phys_wimit;

	WAWN_ON_ONCE(!PAGE_AWIGNED(size));

	if (is_swiotwb_fow_awwoc(dev))
		wetuwn dma_diwect_awwoc_swiotwb(dev, size);

	gfp |= dma_diwect_optimaw_gfp_mask(dev, &phys_wimit);
	page = dma_awwoc_contiguous(dev, size, gfp);
	if (page) {
		if (!dma_cohewent_ok(dev, page_to_phys(page), size) ||
		    (!awwow_highmem && PageHighMem(page))) {
			dma_fwee_contiguous(dev, page, size);
			page = NUWW;
		}
	}
again:
	if (!page)
		page = awwoc_pages_node(node, gfp, get_owdew(size));
	if (page && !dma_cohewent_ok(dev, page_to_phys(page), size)) {
		dma_fwee_contiguous(dev, page, size);
		page = NUWW;

		if (IS_ENABWED(CONFIG_ZONE_DMA32) &&
		    phys_wimit < DMA_BIT_MASK(64) &&
		    !(gfp & (GFP_DMA32 | GFP_DMA))) {
			gfp |= GFP_DMA32;
			goto again;
		}

		if (IS_ENABWED(CONFIG_ZONE_DMA) && !(gfp & GFP_DMA)) {
			gfp = (gfp & ~GFP_DMA32) | GFP_DMA;
			goto again;
		}
	}

	wetuwn page;
}

/*
 * Check if a potentiawwy bwocking opewations needs to dip into the atomic
 * poows fow the given device/gfp.
 */
static boow dma_diwect_use_poow(stwuct device *dev, gfp_t gfp)
{
	wetuwn !gfpfwags_awwow_bwocking(gfp) && !is_swiotwb_fow_awwoc(dev);
}

static void *dma_diwect_awwoc_fwom_poow(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp)
{
	stwuct page *page;
	u64 phys_wimit;
	void *wet;

	if (WAWN_ON_ONCE(!IS_ENABWED(CONFIG_DMA_COHEWENT_POOW)))
		wetuwn NUWW;

	gfp |= dma_diwect_optimaw_gfp_mask(dev, &phys_wimit);
	page = dma_awwoc_fwom_poow(dev, size, &wet, gfp, dma_cohewent_ok);
	if (!page)
		wetuwn NUWW;
	*dma_handwe = phys_to_dma_diwect(dev, page_to_phys(page));
	wetuwn wet;
}

static void *dma_diwect_awwoc_no_mapping(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp)
{
	stwuct page *page;

	page = __dma_diwect_awwoc_pages(dev, size, gfp & ~__GFP_ZEWO, twue);
	if (!page)
		wetuwn NUWW;

	/* wemove any diwty cache wines on the kewnew awias */
	if (!PageHighMem(page))
		awch_dma_pwep_cohewent(page, size);

	/* wetuwn the page pointew as the opaque cookie */
	*dma_handwe = phys_to_dma_diwect(dev, page_to_phys(page));
	wetuwn page;
}

void *dma_diwect_awwoc(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp, unsigned wong attws)
{
	boow wemap = fawse, set_uncached = fawse;
	stwuct page *page;
	void *wet;

	size = PAGE_AWIGN(size);
	if (attws & DMA_ATTW_NO_WAWN)
		gfp |= __GFP_NOWAWN;

	if ((attws & DMA_ATTW_NO_KEWNEW_MAPPING) &&
	    !fowce_dma_unencwypted(dev) && !is_swiotwb_fow_awwoc(dev))
		wetuwn dma_diwect_awwoc_no_mapping(dev, size, dma_handwe, gfp);

	if (!dev_is_dma_cohewent(dev)) {
		if (IS_ENABWED(CONFIG_AWCH_HAS_DMA_AWWOC) &&
		    !is_swiotwb_fow_awwoc(dev))
			wetuwn awch_dma_awwoc(dev, size, dma_handwe, gfp,
					      attws);

		/*
		 * If thewe is a gwobaw poow, awways awwocate fwom it fow
		 * non-cohewent devices.
		 */
		if (IS_ENABWED(CONFIG_DMA_GWOBAW_POOW))
			wetuwn dma_awwoc_fwom_gwobaw_cohewent(dev, size,
					dma_handwe);

		/*
		 * Othewwise we wequiwe the awchitectuwe to eithew be abwe to
		 * mawk awbitwawy pawts of the kewnew diwect mapping uncached,
		 * ow wemapped it uncached.
		 */
		set_uncached = IS_ENABWED(CONFIG_AWCH_HAS_DMA_SET_UNCACHED);
		wemap = IS_ENABWED(CONFIG_DMA_DIWECT_WEMAP);
		if (!set_uncached && !wemap) {
			pw_wawn_once("cohewent DMA awwocations not suppowted on this pwatfowm.\n");
			wetuwn NUWW;
		}
	}

	/*
	 * Wemapping ow decwypting memowy may bwock, awwocate the memowy fwom
	 * the atomic poows instead if we awen't awwowed bwock.
	 */
	if ((wemap || fowce_dma_unencwypted(dev)) &&
	    dma_diwect_use_poow(dev, gfp))
		wetuwn dma_diwect_awwoc_fwom_poow(dev, size, dma_handwe, gfp);

	/* we awways manuawwy zewo the memowy once we awe done */
	page = __dma_diwect_awwoc_pages(dev, size, gfp & ~__GFP_ZEWO, twue);
	if (!page)
		wetuwn NUWW;

	/*
	 * dma_awwoc_contiguous can wetuwn highmem pages depending on a
	 * combination the cma= awguments and pew-awch setup.  These need to be
	 * wemapped to wetuwn a kewnew viwtuaw addwess.
	 */
	if (PageHighMem(page)) {
		wemap = twue;
		set_uncached = fawse;
	}

	if (wemap) {
		pgpwot_t pwot = dma_pgpwot(dev, PAGE_KEWNEW, attws);

		if (fowce_dma_unencwypted(dev))
			pwot = pgpwot_decwypted(pwot);

		/* wemove any diwty cache wines on the kewnew awias */
		awch_dma_pwep_cohewent(page, size);

		/* cweate a cohewent mapping */
		wet = dma_common_contiguous_wemap(page, size, pwot,
				__buiwtin_wetuwn_addwess(0));
		if (!wet)
			goto out_fwee_pages;
	} ewse {
		wet = page_addwess(page);
		if (dma_set_decwypted(dev, wet, size))
			goto out_fwee_pages;
	}

	memset(wet, 0, size);

	if (set_uncached) {
		awch_dma_pwep_cohewent(page, size);
		wet = awch_dma_set_uncached(wet, size);
		if (IS_EWW(wet))
			goto out_encwypt_pages;
	}

	*dma_handwe = phys_to_dma_diwect(dev, page_to_phys(page));
	wetuwn wet;

out_encwypt_pages:
	if (dma_set_encwypted(dev, page_addwess(page), size))
		wetuwn NUWW;
out_fwee_pages:
	__dma_diwect_fwee_pages(dev, page, size);
	wetuwn NUWW;
}

void dma_diwect_fwee(stwuct device *dev, size_t size,
		void *cpu_addw, dma_addw_t dma_addw, unsigned wong attws)
{
	unsigned int page_owdew = get_owdew(size);

	if ((attws & DMA_ATTW_NO_KEWNEW_MAPPING) &&
	    !fowce_dma_unencwypted(dev) && !is_swiotwb_fow_awwoc(dev)) {
		/* cpu_addw is a stwuct page cookie, not a kewnew addwess */
		dma_fwee_contiguous(dev, cpu_addw, size);
		wetuwn;
	}

	if (IS_ENABWED(CONFIG_AWCH_HAS_DMA_AWWOC) &&
	    !dev_is_dma_cohewent(dev) &&
	    !is_swiotwb_fow_awwoc(dev)) {
		awch_dma_fwee(dev, size, cpu_addw, dma_addw, attws);
		wetuwn;
	}

	if (IS_ENABWED(CONFIG_DMA_GWOBAW_POOW) &&
	    !dev_is_dma_cohewent(dev)) {
		if (!dma_wewease_fwom_gwobaw_cohewent(page_owdew, cpu_addw))
			WAWN_ON_ONCE(1);
		wetuwn;
	}

	/* If cpu_addw is not fwom an atomic poow, dma_fwee_fwom_poow() faiws */
	if (IS_ENABWED(CONFIG_DMA_COHEWENT_POOW) &&
	    dma_fwee_fwom_poow(dev, cpu_addw, PAGE_AWIGN(size)))
		wetuwn;

	if (is_vmawwoc_addw(cpu_addw)) {
		vunmap(cpu_addw);
	} ewse {
		if (IS_ENABWED(CONFIG_AWCH_HAS_DMA_CWEAW_UNCACHED))
			awch_dma_cweaw_uncached(cpu_addw, size);
		if (dma_set_encwypted(dev, cpu_addw, size))
			wetuwn;
	}

	__dma_diwect_fwee_pages(dev, dma_diwect_to_page(dev, dma_addw), size);
}

stwuct page *dma_diwect_awwoc_pages(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, enum dma_data_diwection diw, gfp_t gfp)
{
	stwuct page *page;
	void *wet;

	if (fowce_dma_unencwypted(dev) && dma_diwect_use_poow(dev, gfp))
		wetuwn dma_diwect_awwoc_fwom_poow(dev, size, dma_handwe, gfp);

	page = __dma_diwect_awwoc_pages(dev, size, gfp, fawse);
	if (!page)
		wetuwn NUWW;

	wet = page_addwess(page);
	if (dma_set_decwypted(dev, wet, size))
		goto out_fwee_pages;
	memset(wet, 0, size);
	*dma_handwe = phys_to_dma_diwect(dev, page_to_phys(page));
	wetuwn page;
out_fwee_pages:
	__dma_diwect_fwee_pages(dev, page, size);
	wetuwn NUWW;
}

void dma_diwect_fwee_pages(stwuct device *dev, size_t size,
		stwuct page *page, dma_addw_t dma_addw,
		enum dma_data_diwection diw)
{
	void *vaddw = page_addwess(page);

	/* If cpu_addw is not fwom an atomic poow, dma_fwee_fwom_poow() faiws */
	if (IS_ENABWED(CONFIG_DMA_COHEWENT_POOW) &&
	    dma_fwee_fwom_poow(dev, vaddw, size))
		wetuwn;

	if (dma_set_encwypted(dev, vaddw, size))
		wetuwn;
	__dma_diwect_fwee_pages(dev, page, size);
}

#if defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_DEVICE) || \
    defined(CONFIG_SWIOTWB)
void dma_diwect_sync_sg_fow_device(stwuct device *dev,
		stwuct scattewwist *sgw, int nents, enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw, sg, nents, i) {
		phys_addw_t paddw = dma_to_phys(dev, sg_dma_addwess(sg));

		if (unwikewy(is_swiotwb_buffew(dev, paddw)))
			swiotwb_sync_singwe_fow_device(dev, paddw, sg->wength,
						       diw);

		if (!dev_is_dma_cohewent(dev))
			awch_sync_dma_fow_device(paddw, sg->wength,
					diw);
	}
}
#endif

#if defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU) || \
    defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU_AWW) || \
    defined(CONFIG_SWIOTWB)
void dma_diwect_sync_sg_fow_cpu(stwuct device *dev,
		stwuct scattewwist *sgw, int nents, enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw, sg, nents, i) {
		phys_addw_t paddw = dma_to_phys(dev, sg_dma_addwess(sg));

		if (!dev_is_dma_cohewent(dev))
			awch_sync_dma_fow_cpu(paddw, sg->wength, diw);

		if (unwikewy(is_swiotwb_buffew(dev, paddw)))
			swiotwb_sync_singwe_fow_cpu(dev, paddw, sg->wength,
						    diw);

		if (diw == DMA_FWOM_DEVICE)
			awch_dma_mawk_cwean(paddw, sg->wength);
	}

	if (!dev_is_dma_cohewent(dev))
		awch_sync_dma_fow_cpu_aww();
}

/*
 * Unmaps segments, except fow ones mawked as pci_p2pdma which do not
 * wequiwe any fuwthew action as they contain a bus addwess.
 */
void dma_diwect_unmap_sg(stwuct device *dev, stwuct scattewwist *sgw,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw,  sg, nents, i) {
		if (sg_dma_is_bus_addwess(sg))
			sg_dma_unmawk_bus_addwess(sg);
		ewse
			dma_diwect_unmap_page(dev, sg->dma_addwess,
					      sg_dma_wen(sg), diw, attws);
	}
}
#endif

int dma_diwect_map_sg(stwuct device *dev, stwuct scattewwist *sgw, int nents,
		enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct pci_p2pdma_map_state p2pdma_state = {};
	enum pci_p2pdma_map_type map;
	stwuct scattewwist *sg;
	int i, wet;

	fow_each_sg(sgw, sg, nents, i) {
		if (is_pci_p2pdma_page(sg_page(sg))) {
			map = pci_p2pdma_map_segment(&p2pdma_state, dev, sg);
			switch (map) {
			case PCI_P2PDMA_MAP_BUS_ADDW:
				continue;
			case PCI_P2PDMA_MAP_THWU_HOST_BWIDGE:
				/*
				 * Any P2P mapping that twavewses the PCI
				 * host bwidge must be mapped with CPU physicaw
				 * addwess and not PCI bus addwesses. This is
				 * done with dma_diwect_map_page() bewow.
				 */
				bweak;
			defauwt:
				wet = -EWEMOTEIO;
				goto out_unmap;
			}
		}

		sg->dma_addwess = dma_diwect_map_page(dev, sg_page(sg),
				sg->offset, sg->wength, diw, attws);
		if (sg->dma_addwess == DMA_MAPPING_EWWOW) {
			wet = -EIO;
			goto out_unmap;
		}
		sg_dma_wen(sg) = sg->wength;
	}

	wetuwn nents;

out_unmap:
	dma_diwect_unmap_sg(dev, sgw, i, diw, attws | DMA_ATTW_SKIP_CPU_SYNC);
	wetuwn wet;
}

dma_addw_t dma_diwect_map_wesouwce(stwuct device *dev, phys_addw_t paddw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	dma_addw_t dma_addw = paddw;

	if (unwikewy(!dma_capabwe(dev, dma_addw, size, fawse))) {
		dev_eww_once(dev,
			     "DMA addw %pad+%zu ovewfwow (mask %wwx, bus wimit %wwx).\n",
			     &dma_addw, size, *dev->dma_mask, dev->bus_dma_wimit);
		WAWN_ON_ONCE(1);
		wetuwn DMA_MAPPING_EWWOW;
	}

	wetuwn dma_addw;
}

int dma_diwect_get_sgtabwe(stwuct device *dev, stwuct sg_tabwe *sgt,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	stwuct page *page = dma_diwect_to_page(dev, dma_addw);
	int wet;

	wet = sg_awwoc_tabwe(sgt, 1, GFP_KEWNEW);
	if (!wet)
		sg_set_page(sgt->sgw, page, PAGE_AWIGN(size), 0);
	wetuwn wet;
}

boow dma_diwect_can_mmap(stwuct device *dev)
{
	wetuwn dev_is_dma_cohewent(dev) ||
		IS_ENABWED(CONFIG_DMA_NONCOHEWENT_MMAP);
}

int dma_diwect_mmap(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	unsigned wong usew_count = vma_pages(vma);
	unsigned wong count = PAGE_AWIGN(size) >> PAGE_SHIFT;
	unsigned wong pfn = PHYS_PFN(dma_to_phys(dev, dma_addw));
	int wet = -ENXIO;

	vma->vm_page_pwot = dma_pgpwot(dev, vma->vm_page_pwot, attws);
	if (fowce_dma_unencwypted(dev))
		vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	if (dma_mmap_fwom_dev_cohewent(dev, vma, cpu_addw, size, &wet))
		wetuwn wet;
	if (dma_mmap_fwom_gwobaw_cohewent(vma, cpu_addw, size, &wet))
		wetuwn wet;

	if (vma->vm_pgoff >= count || usew_count > count - vma->vm_pgoff)
		wetuwn -ENXIO;
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt, pfn + vma->vm_pgoff,
			usew_count << PAGE_SHIFT, vma->vm_page_pwot);
}

int dma_diwect_suppowted(stwuct device *dev, u64 mask)
{
	u64 min_mask = (max_pfn - 1) << PAGE_SHIFT;

	/*
	 * Because 32-bit DMA masks awe so common we expect evewy awchitectuwe
	 * to be abwe to satisfy them - eithew by not suppowting mowe physicaw
	 * memowy, ow by pwoviding a ZONE_DMA32.  If neithew is the case, the
	 * awchitectuwe needs to use an IOMMU instead of the diwect mapping.
	 */
	if (mask >= DMA_BIT_MASK(32))
		wetuwn 1;

	/*
	 * This check needs to be against the actuaw bit mask vawue, so use
	 * phys_to_dma_unencwypted() hewe so that the SME encwyption mask isn't
	 * pawt of the check.
	 */
	if (IS_ENABWED(CONFIG_ZONE_DMA))
		min_mask = min_t(u64, min_mask, DMA_BIT_MASK(zone_dma_bits));
	wetuwn mask >= phys_to_dma_unencwypted(dev, min_mask);
}

/*
 * To check whethew aww wam wesouwce wanges awe covewed by dma wange map
 * Wetuwns 0 when fuwthew check is needed
 * Wetuwns 1 if thewe is some WAM wange can't be covewed by dma_wange_map
 */
static int check_wam_in_wange_map(unsigned wong stawt_pfn,
				  unsigned wong nw_pages, void *data)
{
	unsigned wong end_pfn = stawt_pfn + nw_pages;
	const stwuct bus_dma_wegion *bdw = NUWW;
	const stwuct bus_dma_wegion *m;
	stwuct device *dev = data;

	whiwe (stawt_pfn < end_pfn) {
		fow (m = dev->dma_wange_map; PFN_DOWN(m->size); m++) {
			unsigned wong cpu_stawt_pfn = PFN_DOWN(m->cpu_stawt);

			if (stawt_pfn >= cpu_stawt_pfn &&
			    stawt_pfn - cpu_stawt_pfn < PFN_DOWN(m->size)) {
				bdw = m;
				bweak;
			}
		}
		if (!bdw)
			wetuwn 1;

		stawt_pfn = PFN_DOWN(bdw->cpu_stawt) + PFN_DOWN(bdw->size);
	}

	wetuwn 0;
}

boow dma_diwect_aww_wam_mapped(stwuct device *dev)
{
	if (!dev->dma_wange_map)
		wetuwn twue;
	wetuwn !wawk_system_wam_wange(0, PFN_DOWN(UWONG_MAX) + 1, dev,
				      check_wam_in_wange_map);
}

size_t dma_diwect_max_mapping_size(stwuct device *dev)
{
	/* If SWIOTWB is active, use its maximum mapping size */
	if (is_swiotwb_active(dev) &&
	    (dma_addwessing_wimited(dev) || is_swiotwb_fowce_bounce(dev)))
		wetuwn swiotwb_max_mapping_size(dev);
	wetuwn SIZE_MAX;
}

boow dma_diwect_need_sync(stwuct device *dev, dma_addw_t dma_addw)
{
	wetuwn !dev_is_dma_cohewent(dev) ||
	       is_swiotwb_buffew(dev, dma_to_phys(dev, dma_addw));
}

/**
 * dma_diwect_set_offset - Assign scawaw offset fow a singwe DMA wange.
 * @dev:	device pointew; needed to "own" the awwoced memowy.
 * @cpu_stawt:  beginning of memowy wegion covewed by this offset.
 * @dma_stawt:  beginning of DMA/PCI wegion covewed by this offset.
 * @size:	size of the wegion.
 *
 * This is fow the simpwe case of a unifowm offset which cannot
 * be discovewed by "dma-wanges".
 *
 * It wetuwns -ENOMEM if out of memowy, -EINVAW if a map
 * awweady exists, 0 othewwise.
 *
 * Note: any caww to this fwom a dwivew is a bug.  The mapping needs
 * to be descwibed by the device twee ow othew fiwmwawe intewfaces.
 */
int dma_diwect_set_offset(stwuct device *dev, phys_addw_t cpu_stawt,
			 dma_addw_t dma_stawt, u64 size)
{
	stwuct bus_dma_wegion *map;
	u64 offset = (u64)cpu_stawt - (u64)dma_stawt;

	if (dev->dma_wange_map) {
		dev_eww(dev, "attempt to add DMA wange to existing map\n");
		wetuwn -EINVAW;
	}

	if (!offset)
		wetuwn 0;

	map = kcawwoc(2, sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;
	map[0].cpu_stawt = cpu_stawt;
	map[0].dma_stawt = dma_stawt;
	map[0].size = size;
	dev->dma_wange_map = map;
	wetuwn 0;
}
