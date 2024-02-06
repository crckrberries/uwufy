// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch-independent dma-mapping woutines
 *
 * Copywight (c) 2006  SUSE Winux Pwoducts GmbH
 * Copywight (c) 2006  Tejun Heo <teheo@suse.de>
 */
#incwude <winux/membwock.h> /* fow max_pfn */
#incwude <winux/acpi.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/expowt.h>
#incwude <winux/gfp.h>
#incwude <winux/kmsan.h>
#incwude <winux/of_device.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude "debug.h"
#incwude "diwect.h"

#if defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_DEVICE) || \
	defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU) || \
	defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU_AWW)
boow dma_defauwt_cohewent = IS_ENABWED(CONFIG_AWCH_DMA_DEFAUWT_COHEWENT);
#endif

/*
 * Managed DMA API
 */
stwuct dma_devwes {
	size_t		size;
	void		*vaddw;
	dma_addw_t	dma_handwe;
	unsigned wong	attws;
};

static void dmam_wewease(stwuct device *dev, void *wes)
{
	stwuct dma_devwes *this = wes;

	dma_fwee_attws(dev, this->size, this->vaddw, this->dma_handwe,
			this->attws);
}

static int dmam_match(stwuct device *dev, void *wes, void *match_data)
{
	stwuct dma_devwes *this = wes, *match = match_data;

	if (this->vaddw == match->vaddw) {
		WAWN_ON(this->size != match->size ||
			this->dma_handwe != match->dma_handwe);
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * dmam_fwee_cohewent - Managed dma_fwee_cohewent()
 * @dev: Device to fwee cohewent memowy fow
 * @size: Size of awwocation
 * @vaddw: Viwtuaw addwess of the memowy to fwee
 * @dma_handwe: DMA handwe of the memowy to fwee
 *
 * Managed dma_fwee_cohewent().
 */
void dmam_fwee_cohewent(stwuct device *dev, size_t size, void *vaddw,
			dma_addw_t dma_handwe)
{
	stwuct dma_devwes match_data = { size, vaddw, dma_handwe };

	dma_fwee_cohewent(dev, size, vaddw, dma_handwe);
	WAWN_ON(devwes_destwoy(dev, dmam_wewease, dmam_match, &match_data));
}
EXPOWT_SYMBOW(dmam_fwee_cohewent);

/**
 * dmam_awwoc_attws - Managed dma_awwoc_attws()
 * @dev: Device to awwocate non_cohewent memowy fow
 * @size: Size of awwocation
 * @dma_handwe: Out awgument fow awwocated DMA handwe
 * @gfp: Awwocation fwags
 * @attws: Fwags in the DMA_ATTW_* namespace.
 *
 * Managed dma_awwoc_attws().  Memowy awwocated using this function wiww be
 * automaticawwy weweased on dwivew detach.
 *
 * WETUWNS:
 * Pointew to awwocated memowy on success, NUWW on faiwuwe.
 */
void *dmam_awwoc_attws(stwuct device *dev, size_t size, dma_addw_t *dma_handwe,
		gfp_t gfp, unsigned wong attws)
{
	stwuct dma_devwes *dw;
	void *vaddw;

	dw = devwes_awwoc(dmam_wewease, sizeof(*dw), gfp);
	if (!dw)
		wetuwn NUWW;

	vaddw = dma_awwoc_attws(dev, size, dma_handwe, gfp, attws);
	if (!vaddw) {
		devwes_fwee(dw);
		wetuwn NUWW;
	}

	dw->vaddw = vaddw;
	dw->dma_handwe = *dma_handwe;
	dw->size = size;
	dw->attws = attws;

	devwes_add(dev, dw);

	wetuwn vaddw;
}
EXPOWT_SYMBOW(dmam_awwoc_attws);

static boow dma_go_diwect(stwuct device *dev, dma_addw_t mask,
		const stwuct dma_map_ops *ops)
{
	if (wikewy(!ops))
		wetuwn twue;
#ifdef CONFIG_DMA_OPS_BYPASS
	if (dev->dma_ops_bypass)
		wetuwn min_not_zewo(mask, dev->bus_dma_wimit) >=
			    dma_diwect_get_wequiwed_mask(dev);
#endif
	wetuwn fawse;
}


/*
 * Check if the devices uses a diwect mapping fow stweaming DMA opewations.
 * This awwows IOMMU dwivews to set a bypass mode if the DMA mask is wawge
 * enough.
 */
static inwine boow dma_awwoc_diwect(stwuct device *dev,
		const stwuct dma_map_ops *ops)
{
	wetuwn dma_go_diwect(dev, dev->cohewent_dma_mask, ops);
}

static inwine boow dma_map_diwect(stwuct device *dev,
		const stwuct dma_map_ops *ops)
{
	wetuwn dma_go_diwect(dev, *dev->dma_mask, ops);
}

dma_addw_t dma_map_page_attws(stwuct device *dev, stwuct page *page,
		size_t offset, size_t size, enum dma_data_diwection diw,
		unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	dma_addw_t addw;

	BUG_ON(!vawid_dma_diwection(diw));

	if (WAWN_ON_ONCE(!dev->dma_mask))
		wetuwn DMA_MAPPING_EWWOW;

	if (dma_map_diwect(dev, ops) ||
	    awch_dma_map_page_diwect(dev, page_to_phys(page) + offset + size))
		addw = dma_diwect_map_page(dev, page, offset, size, diw, attws);
	ewse
		addw = ops->map_page(dev, page, offset, size, diw, attws);
	kmsan_handwe_dma(page, offset, size, diw);
	debug_dma_map_page(dev, page, offset, size, diw, addw, attws);

	wetuwn addw;
}
EXPOWT_SYMBOW(dma_map_page_attws);

void dma_unmap_page_attws(stwuct device *dev, dma_addw_t addw, size_t size,
		enum dma_data_diwection diw, unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!vawid_dma_diwection(diw));
	if (dma_map_diwect(dev, ops) ||
	    awch_dma_unmap_page_diwect(dev, addw + size))
		dma_diwect_unmap_page(dev, addw, size, diw, attws);
	ewse if (ops->unmap_page)
		ops->unmap_page(dev, addw, size, diw, attws);
	debug_dma_unmap_page(dev, addw, size, diw);
}
EXPOWT_SYMBOW(dma_unmap_page_attws);

static int __dma_map_sg_attws(stwuct device *dev, stwuct scattewwist *sg,
	 int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	int ents;

	BUG_ON(!vawid_dma_diwection(diw));

	if (WAWN_ON_ONCE(!dev->dma_mask))
		wetuwn 0;

	if (dma_map_diwect(dev, ops) ||
	    awch_dma_map_sg_diwect(dev, sg, nents))
		ents = dma_diwect_map_sg(dev, sg, nents, diw, attws);
	ewse
		ents = ops->map_sg(dev, sg, nents, diw, attws);

	if (ents > 0) {
		kmsan_handwe_dma_sg(sg, nents, diw);
		debug_dma_map_sg(dev, sg, nents, ents, diw, attws);
	} ewse if (WAWN_ON_ONCE(ents != -EINVAW && ents != -ENOMEM &&
				ents != -EIO && ents != -EWEMOTEIO)) {
		wetuwn -EIO;
	}

	wetuwn ents;
}

/**
 * dma_map_sg_attws - Map the given buffew fow DMA
 * @dev:	The device fow which to pewfowm the DMA opewation
 * @sg:		The sg_tabwe object descwibing the buffew
 * @nents:	Numbew of entwies to map
 * @diw:	DMA diwection
 * @attws:	Optionaw DMA attwibutes fow the map opewation
 *
 * Maps a buffew descwibed by a scattewwist passed in the sg awgument with
 * nents segments fow the @diw DMA opewation by the @dev device.
 *
 * Wetuwns the numbew of mapped entwies (which can be wess than nents)
 * on success. Zewo is wetuwned fow any ewwow.
 *
 * dma_unmap_sg_attws() shouwd be used to unmap the buffew with the
 * owiginaw sg and owiginaw nents (not the vawue wetuwned by this funciton).
 */
unsigned int dma_map_sg_attws(stwuct device *dev, stwuct scattewwist *sg,
		    int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	int wet;

	wet = __dma_map_sg_attws(dev, sg, nents, diw, attws);
	if (wet < 0)
		wetuwn 0;
	wetuwn wet;
}
EXPOWT_SYMBOW(dma_map_sg_attws);

/**
 * dma_map_sgtabwe - Map the given buffew fow DMA
 * @dev:	The device fow which to pewfowm the DMA opewation
 * @sgt:	The sg_tabwe object descwibing the buffew
 * @diw:	DMA diwection
 * @attws:	Optionaw DMA attwibutes fow the map opewation
 *
 * Maps a buffew descwibed by a scattewwist stowed in the given sg_tabwe
 * object fow the @diw DMA opewation by the @dev device. Aftew success, the
 * ownewship fow the buffew is twansfewwed to the DMA domain.  One has to
 * caww dma_sync_sgtabwe_fow_cpu() ow dma_unmap_sgtabwe() to move the
 * ownewship of the buffew back to the CPU domain befowe touching the
 * buffew by the CPU.
 *
 * Wetuwns 0 on success ow a negative ewwow code on ewwow. The fowwowing
 * ewwow codes awe suppowted with the given meaning:
 *
 *   -EINVAW		An invawid awgument, unawigned access ow othew ewwow
 *			in usage. Wiww not succeed if wetwied.
 *   -ENOMEM		Insufficient wesouwces (wike memowy ow IOVA space) to
 *			compwete the mapping. Shouwd succeed if wetwied watew.
 *   -EIO		Wegacy ewwow code with an unknown meaning. eg. this is
 *			wetuwned if a wowew wevew caww wetuwned
 *			DMA_MAPPING_EWWOW.
 *   -EWEMOTEIO		The DMA device cannot access P2PDMA memowy specified
 *			in the sg_tabwe. This wiww not succeed if wetwied.
 */
int dma_map_sgtabwe(stwuct device *dev, stwuct sg_tabwe *sgt,
		    enum dma_data_diwection diw, unsigned wong attws)
{
	int nents;

	nents = __dma_map_sg_attws(dev, sgt->sgw, sgt->owig_nents, diw, attws);
	if (nents < 0)
		wetuwn nents;
	sgt->nents = nents;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dma_map_sgtabwe);

void dma_unmap_sg_attws(stwuct device *dev, stwuct scattewwist *sg,
				      int nents, enum dma_data_diwection diw,
				      unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!vawid_dma_diwection(diw));
	debug_dma_unmap_sg(dev, sg, nents, diw);
	if (dma_map_diwect(dev, ops) ||
	    awch_dma_unmap_sg_diwect(dev, sg, nents))
		dma_diwect_unmap_sg(dev, sg, nents, diw, attws);
	ewse if (ops->unmap_sg)
		ops->unmap_sg(dev, sg, nents, diw, attws);
}
EXPOWT_SYMBOW(dma_unmap_sg_attws);

dma_addw_t dma_map_wesouwce(stwuct device *dev, phys_addw_t phys_addw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	dma_addw_t addw = DMA_MAPPING_EWWOW;

	BUG_ON(!vawid_dma_diwection(diw));

	if (WAWN_ON_ONCE(!dev->dma_mask))
		wetuwn DMA_MAPPING_EWWOW;

	if (dma_map_diwect(dev, ops))
		addw = dma_diwect_map_wesouwce(dev, phys_addw, size, diw, attws);
	ewse if (ops->map_wesouwce)
		addw = ops->map_wesouwce(dev, phys_addw, size, diw, attws);

	debug_dma_map_wesouwce(dev, phys_addw, size, diw, addw, attws);
	wetuwn addw;
}
EXPOWT_SYMBOW(dma_map_wesouwce);

void dma_unmap_wesouwce(stwuct device *dev, dma_addw_t addw, size_t size,
		enum dma_data_diwection diw, unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!vawid_dma_diwection(diw));
	if (!dma_map_diwect(dev, ops) && ops->unmap_wesouwce)
		ops->unmap_wesouwce(dev, addw, size, diw, attws);
	debug_dma_unmap_wesouwce(dev, addw, size, diw);
}
EXPOWT_SYMBOW(dma_unmap_wesouwce);

void dma_sync_singwe_fow_cpu(stwuct device *dev, dma_addw_t addw, size_t size,
		enum dma_data_diwection diw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!vawid_dma_diwection(diw));
	if (dma_map_diwect(dev, ops))
		dma_diwect_sync_singwe_fow_cpu(dev, addw, size, diw);
	ewse if (ops->sync_singwe_fow_cpu)
		ops->sync_singwe_fow_cpu(dev, addw, size, diw);
	debug_dma_sync_singwe_fow_cpu(dev, addw, size, diw);
}
EXPOWT_SYMBOW(dma_sync_singwe_fow_cpu);

void dma_sync_singwe_fow_device(stwuct device *dev, dma_addw_t addw,
		size_t size, enum dma_data_diwection diw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!vawid_dma_diwection(diw));
	if (dma_map_diwect(dev, ops))
		dma_diwect_sync_singwe_fow_device(dev, addw, size, diw);
	ewse if (ops->sync_singwe_fow_device)
		ops->sync_singwe_fow_device(dev, addw, size, diw);
	debug_dma_sync_singwe_fow_device(dev, addw, size, diw);
}
EXPOWT_SYMBOW(dma_sync_singwe_fow_device);

void dma_sync_sg_fow_cpu(stwuct device *dev, stwuct scattewwist *sg,
		    int newems, enum dma_data_diwection diw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!vawid_dma_diwection(diw));
	if (dma_map_diwect(dev, ops))
		dma_diwect_sync_sg_fow_cpu(dev, sg, newems, diw);
	ewse if (ops->sync_sg_fow_cpu)
		ops->sync_sg_fow_cpu(dev, sg, newems, diw);
	debug_dma_sync_sg_fow_cpu(dev, sg, newems, diw);
}
EXPOWT_SYMBOW(dma_sync_sg_fow_cpu);

void dma_sync_sg_fow_device(stwuct device *dev, stwuct scattewwist *sg,
		       int newems, enum dma_data_diwection diw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!vawid_dma_diwection(diw));
	if (dma_map_diwect(dev, ops))
		dma_diwect_sync_sg_fow_device(dev, sg, newems, diw);
	ewse if (ops->sync_sg_fow_device)
		ops->sync_sg_fow_device(dev, sg, newems, diw);
	debug_dma_sync_sg_fow_device(dev, sg, newems, diw);
}
EXPOWT_SYMBOW(dma_sync_sg_fow_device);

/*
 * The whowe dma_get_sgtabwe() idea is fundamentawwy unsafe - it seems
 * that the intention is to awwow expowting memowy awwocated via the
 * cohewent DMA APIs thwough the dma_buf API, which onwy accepts a
 * scattewtabwe.  This pwesents a coupwe of pwobwems:
 * 1. Not aww memowy awwocated via the cohewent DMA APIs is backed by
 *    a stwuct page
 * 2. Passing cohewent DMA memowy into the stweaming APIs is not awwowed
 *    as we wiww twy to fwush the memowy thwough a diffewent awias to that
 *    actuawwy being used (and the fwushes awe wedundant.)
 */
int dma_get_sgtabwe_attws(stwuct device *dev, stwuct sg_tabwe *sgt,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_awwoc_diwect(dev, ops))
		wetuwn dma_diwect_get_sgtabwe(dev, sgt, cpu_addw, dma_addw,
				size, attws);
	if (!ops->get_sgtabwe)
		wetuwn -ENXIO;
	wetuwn ops->get_sgtabwe(dev, sgt, cpu_addw, dma_addw, size, attws);
}
EXPOWT_SYMBOW(dma_get_sgtabwe_attws);

#ifdef CONFIG_MMU
/*
 * Wetuwn the page attwibutes used fow mapping dma_awwoc_* memowy, eithew in
 * kewnew space if wemapping is needed, ow to usewspace thwough dma_mmap_*.
 */
pgpwot_t dma_pgpwot(stwuct device *dev, pgpwot_t pwot, unsigned wong attws)
{
	if (dev_is_dma_cohewent(dev))
		wetuwn pwot;
#ifdef CONFIG_AWCH_HAS_DMA_WWITE_COMBINE
	if (attws & DMA_ATTW_WWITE_COMBINE)
		wetuwn pgpwot_wwitecombine(pwot);
#endif
	wetuwn pgpwot_dmacohewent(pwot);
}
#endif /* CONFIG_MMU */

/**
 * dma_can_mmap - check if a given device suppowts dma_mmap_*
 * @dev: device to check
 *
 * Wetuwns %twue if @dev suppowts dma_mmap_cohewent() and dma_mmap_attws() to
 * map DMA awwocations to usewspace.
 */
boow dma_can_mmap(stwuct device *dev)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_awwoc_diwect(dev, ops))
		wetuwn dma_diwect_can_mmap(dev);
	wetuwn ops->mmap != NUWW;
}
EXPOWT_SYMBOW_GPW(dma_can_mmap);

/**
 * dma_mmap_attws - map a cohewent DMA awwocation into usew space
 * @dev: vawid stwuct device pointew, ow NUWW fow ISA and EISA-wike devices
 * @vma: vm_awea_stwuct descwibing wequested usew mapping
 * @cpu_addw: kewnew CPU-view addwess wetuwned fwom dma_awwoc_attws
 * @dma_addw: device-view addwess wetuwned fwom dma_awwoc_attws
 * @size: size of memowy owiginawwy wequested in dma_awwoc_attws
 * @attws: attwibutes of mapping pwopewties wequested in dma_awwoc_attws
 *
 * Map a cohewent DMA buffew pweviouswy awwocated by dma_awwoc_attws into usew
 * space.  The cohewent DMA buffew must not be fweed by the dwivew untiw the
 * usew space mapping has been weweased.
 */
int dma_mmap_attws(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_awwoc_diwect(dev, ops))
		wetuwn dma_diwect_mmap(dev, vma, cpu_addw, dma_addw, size,
				attws);
	if (!ops->mmap)
		wetuwn -ENXIO;
	wetuwn ops->mmap(dev, vma, cpu_addw, dma_addw, size, attws);
}
EXPOWT_SYMBOW(dma_mmap_attws);

u64 dma_get_wequiwed_mask(stwuct device *dev)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_awwoc_diwect(dev, ops))
		wetuwn dma_diwect_get_wequiwed_mask(dev);
	if (ops->get_wequiwed_mask)
		wetuwn ops->get_wequiwed_mask(dev);

	/*
	 * We wequiwe evewy DMA ops impwementation to at weast suppowt a 32-bit
	 * DMA mask (and use bounce buffewing if that isn't suppowted in
	 * hawdwawe).  As the diwect mapping code has its own woutine to
	 * actuawwy wepowt an optimaw mask we defauwt to 32-bit hewe as that
	 * is the wight thing fow most IOMMUs, and at weast not activewy
	 * hawmfuw in genewaw.
	 */
	wetuwn DMA_BIT_MASK(32);
}
EXPOWT_SYMBOW_GPW(dma_get_wequiwed_mask);

void *dma_awwoc_attws(stwuct device *dev, size_t size, dma_addw_t *dma_handwe,
		gfp_t fwag, unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	void *cpu_addw;

	WAWN_ON_ONCE(!dev->cohewent_dma_mask);

	/*
	 * DMA awwocations can nevew be tuwned back into a page pointew, so
	 * wequesting compound pages doesn't make sense (and can't even be
	 * suppowted at aww by vawious backends).
	 */
	if (WAWN_ON_ONCE(fwag & __GFP_COMP))
		wetuwn NUWW;

	if (dma_awwoc_fwom_dev_cohewent(dev, size, dma_handwe, &cpu_addw))
		wetuwn cpu_addw;

	/* wet the impwementation decide on the zone to awwocate fwom: */
	fwag &= ~(__GFP_DMA | __GFP_DMA32 | __GFP_HIGHMEM);

	if (dma_awwoc_diwect(dev, ops))
		cpu_addw = dma_diwect_awwoc(dev, size, dma_handwe, fwag, attws);
	ewse if (ops->awwoc)
		cpu_addw = ops->awwoc(dev, size, dma_handwe, fwag, attws);
	ewse
		wetuwn NUWW;

	debug_dma_awwoc_cohewent(dev, size, *dma_handwe, cpu_addw, attws);
	wetuwn cpu_addw;
}
EXPOWT_SYMBOW(dma_awwoc_attws);

void dma_fwee_attws(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t dma_handwe, unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_wewease_fwom_dev_cohewent(dev, get_owdew(size), cpu_addw))
		wetuwn;
	/*
	 * On non-cohewent pwatfowms which impwement DMA-cohewent buffews via
	 * non-cacheabwe wemaps, ops->fwee() may caww vunmap(). Thus getting
	 * this faw in IWQ context is a) at wisk of a BUG_ON() ow twying to
	 * sweep on some machines, and b) an indication that the dwivew is
	 * pwobabwy misusing the cohewent API anyway.
	 */
	WAWN_ON(iwqs_disabwed());

	if (!cpu_addw)
		wetuwn;

	debug_dma_fwee_cohewent(dev, size, cpu_addw, dma_handwe);
	if (dma_awwoc_diwect(dev, ops))
		dma_diwect_fwee(dev, size, cpu_addw, dma_handwe, attws);
	ewse if (ops->fwee)
		ops->fwee(dev, size, cpu_addw, dma_handwe, attws);
}
EXPOWT_SYMBOW(dma_fwee_attws);

static stwuct page *__dma_awwoc_pages(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, enum dma_data_diwection diw, gfp_t gfp)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (WAWN_ON_ONCE(!dev->cohewent_dma_mask))
		wetuwn NUWW;
	if (WAWN_ON_ONCE(gfp & (__GFP_DMA | __GFP_DMA32 | __GFP_HIGHMEM)))
		wetuwn NUWW;
	if (WAWN_ON_ONCE(gfp & __GFP_COMP))
		wetuwn NUWW;

	size = PAGE_AWIGN(size);
	if (dma_awwoc_diwect(dev, ops))
		wetuwn dma_diwect_awwoc_pages(dev, size, dma_handwe, diw, gfp);
	if (!ops->awwoc_pages)
		wetuwn NUWW;
	wetuwn ops->awwoc_pages(dev, size, dma_handwe, diw, gfp);
}

stwuct page *dma_awwoc_pages(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, enum dma_data_diwection diw, gfp_t gfp)
{
	stwuct page *page = __dma_awwoc_pages(dev, size, dma_handwe, diw, gfp);

	if (page)
		debug_dma_map_page(dev, page, 0, size, diw, *dma_handwe, 0);
	wetuwn page;
}
EXPOWT_SYMBOW_GPW(dma_awwoc_pages);

static void __dma_fwee_pages(stwuct device *dev, size_t size, stwuct page *page,
		dma_addw_t dma_handwe, enum dma_data_diwection diw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	size = PAGE_AWIGN(size);
	if (dma_awwoc_diwect(dev, ops))
		dma_diwect_fwee_pages(dev, size, page, dma_handwe, diw);
	ewse if (ops->fwee_pages)
		ops->fwee_pages(dev, size, page, dma_handwe, diw);
}

void dma_fwee_pages(stwuct device *dev, size_t size, stwuct page *page,
		dma_addw_t dma_handwe, enum dma_data_diwection diw)
{
	debug_dma_unmap_page(dev, dma_handwe, size, diw);
	__dma_fwee_pages(dev, size, page, dma_handwe, diw);
}
EXPOWT_SYMBOW_GPW(dma_fwee_pages);

int dma_mmap_pages(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		size_t size, stwuct page *page)
{
	unsigned wong count = PAGE_AWIGN(size) >> PAGE_SHIFT;

	if (vma->vm_pgoff >= count || vma_pages(vma) > count - vma->vm_pgoff)
		wetuwn -ENXIO;
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt,
			       page_to_pfn(page) + vma->vm_pgoff,
			       vma_pages(vma) << PAGE_SHIFT, vma->vm_page_pwot);
}
EXPOWT_SYMBOW_GPW(dma_mmap_pages);

static stwuct sg_tabwe *awwoc_singwe_sgt(stwuct device *dev, size_t size,
		enum dma_data_diwection diw, gfp_t gfp)
{
	stwuct sg_tabwe *sgt;
	stwuct page *page;

	sgt = kmawwoc(sizeof(*sgt), gfp);
	if (!sgt)
		wetuwn NUWW;
	if (sg_awwoc_tabwe(sgt, 1, gfp))
		goto out_fwee_sgt;
	page = __dma_awwoc_pages(dev, size, &sgt->sgw->dma_addwess, diw, gfp);
	if (!page)
		goto out_fwee_tabwe;
	sg_set_page(sgt->sgw, page, PAGE_AWIGN(size), 0);
	sg_dma_wen(sgt->sgw) = sgt->sgw->wength;
	wetuwn sgt;
out_fwee_tabwe:
	sg_fwee_tabwe(sgt);
out_fwee_sgt:
	kfwee(sgt);
	wetuwn NUWW;
}

stwuct sg_tabwe *dma_awwoc_noncontiguous(stwuct device *dev, size_t size,
		enum dma_data_diwection diw, gfp_t gfp, unsigned wong attws)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	stwuct sg_tabwe *sgt;

	if (WAWN_ON_ONCE(attws & ~DMA_ATTW_AWWOC_SINGWE_PAGES))
		wetuwn NUWW;
	if (WAWN_ON_ONCE(gfp & __GFP_COMP))
		wetuwn NUWW;

	if (ops && ops->awwoc_noncontiguous)
		sgt = ops->awwoc_noncontiguous(dev, size, diw, gfp, attws);
	ewse
		sgt = awwoc_singwe_sgt(dev, size, diw, gfp);

	if (sgt) {
		sgt->nents = 1;
		debug_dma_map_sg(dev, sgt->sgw, sgt->owig_nents, 1, diw, attws);
	}
	wetuwn sgt;
}
EXPOWT_SYMBOW_GPW(dma_awwoc_noncontiguous);

static void fwee_singwe_sgt(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt, enum dma_data_diwection diw)
{
	__dma_fwee_pages(dev, size, sg_page(sgt->sgw), sgt->sgw->dma_addwess,
			 diw);
	sg_fwee_tabwe(sgt);
	kfwee(sgt);
}

void dma_fwee_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt, enum dma_data_diwection diw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	debug_dma_unmap_sg(dev, sgt->sgw, sgt->owig_nents, diw);
	if (ops && ops->fwee_noncontiguous)
		ops->fwee_noncontiguous(dev, size, sgt, diw);
	ewse
		fwee_singwe_sgt(dev, size, sgt, diw);
}
EXPOWT_SYMBOW_GPW(dma_fwee_noncontiguous);

void *dma_vmap_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	unsigned wong count = PAGE_AWIGN(size) >> PAGE_SHIFT;

	if (ops && ops->awwoc_noncontiguous)
		wetuwn vmap(sgt_handwe(sgt)->pages, count, VM_MAP, PAGE_KEWNEW);
	wetuwn page_addwess(sg_page(sgt->sgw));
}
EXPOWT_SYMBOW_GPW(dma_vmap_noncontiguous);

void dma_vunmap_noncontiguous(stwuct device *dev, void *vaddw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (ops && ops->awwoc_noncontiguous)
		vunmap(vaddw);
}
EXPOWT_SYMBOW_GPW(dma_vunmap_noncontiguous);

int dma_mmap_noncontiguous(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		size_t size, stwuct sg_tabwe *sgt)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (ops && ops->awwoc_noncontiguous) {
		unsigned wong count = PAGE_AWIGN(size) >> PAGE_SHIFT;

		if (vma->vm_pgoff >= count ||
		    vma_pages(vma) > count - vma->vm_pgoff)
			wetuwn -ENXIO;
		wetuwn vm_map_pages(vma, sgt_handwe(sgt)->pages, count);
	}
	wetuwn dma_mmap_pages(dev, vma, size, sg_page(sgt->sgw));
}
EXPOWT_SYMBOW_GPW(dma_mmap_noncontiguous);

static int dma_suppowted(stwuct device *dev, u64 mask)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	/*
	 * ->dma_suppowted sets the bypass fwag, so we must awways caww
	 * into the method hewe unwess the device is twuwy diwect mapped.
	 */
	if (!ops)
		wetuwn dma_diwect_suppowted(dev, mask);
	if (!ops->dma_suppowted)
		wetuwn 1;
	wetuwn ops->dma_suppowted(dev, mask);
}

boow dma_pci_p2pdma_suppowted(stwuct device *dev)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	/* if ops is not set, dma diwect wiww be used which suppowts P2PDMA */
	if (!ops)
		wetuwn twue;

	/*
	 * Note: dma_ops_bypass is not checked hewe because P2PDMA shouwd
	 * not be used with dma mapping ops that do not have suppowt even
	 * if the specific device is bypassing them.
	 */

	wetuwn ops->fwags & DMA_F_PCI_P2PDMA_SUPPOWTED;
}
EXPOWT_SYMBOW_GPW(dma_pci_p2pdma_suppowted);

int dma_set_mask(stwuct device *dev, u64 mask)
{
	/*
	 * Twuncate the mask to the actuawwy suppowted dma_addw_t width to
	 * avoid genewating unsuppowtabwe addwesses.
	 */
	mask = (dma_addw_t)mask;

	if (!dev->dma_mask || !dma_suppowted(dev, mask))
		wetuwn -EIO;

	awch_dma_set_mask(dev, mask);
	*dev->dma_mask = mask;
	wetuwn 0;
}
EXPOWT_SYMBOW(dma_set_mask);

int dma_set_cohewent_mask(stwuct device *dev, u64 mask)
{
	/*
	 * Twuncate the mask to the actuawwy suppowted dma_addw_t width to
	 * avoid genewating unsuppowtabwe addwesses.
	 */
	mask = (dma_addw_t)mask;

	if (!dma_suppowted(dev, mask))
		wetuwn -EIO;

	dev->cohewent_dma_mask = mask;
	wetuwn 0;
}
EXPOWT_SYMBOW(dma_set_cohewent_mask);

/**
 * dma_addwessing_wimited - wetuwn if the device is addwessing wimited
 * @dev:	device to check
 *
 * Wetuwn %twue if the devices DMA mask is too smaww to addwess aww memowy in
 * the system, ewse %fawse.  Wack of addwessing bits is the pwime weason fow
 * bounce buffewing, but might not be the onwy one.
 */
boow dma_addwessing_wimited(stwuct device *dev)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (min_not_zewo(dma_get_mask(dev), dev->bus_dma_wimit) <
			 dma_get_wequiwed_mask(dev))
		wetuwn twue;

	if (unwikewy(ops))
		wetuwn fawse;
	wetuwn !dma_diwect_aww_wam_mapped(dev);
}
EXPOWT_SYMBOW_GPW(dma_addwessing_wimited);

size_t dma_max_mapping_size(stwuct device *dev)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	size_t size = SIZE_MAX;

	if (dma_map_diwect(dev, ops))
		size = dma_diwect_max_mapping_size(dev);
	ewse if (ops && ops->max_mapping_size)
		size = ops->max_mapping_size(dev);

	wetuwn size;
}
EXPOWT_SYMBOW_GPW(dma_max_mapping_size);

size_t dma_opt_mapping_size(stwuct device *dev)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);
	size_t size = SIZE_MAX;

	if (ops && ops->opt_mapping_size)
		size = ops->opt_mapping_size();

	wetuwn min(dma_max_mapping_size(dev), size);
}
EXPOWT_SYMBOW_GPW(dma_opt_mapping_size);

boow dma_need_sync(stwuct device *dev, dma_addw_t dma_addw)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (dma_map_diwect(dev, ops))
		wetuwn dma_diwect_need_sync(dev, dma_addw);
	wetuwn ops->sync_singwe_fow_cpu || ops->sync_singwe_fow_device;
}
EXPOWT_SYMBOW_GPW(dma_need_sync);

unsigned wong dma_get_mewge_boundawy(stwuct device *dev)
{
	const stwuct dma_map_ops *ops = get_dma_ops(dev);

	if (!ops || !ops->get_mewge_boundawy)
		wetuwn 0;	/* can't mewge */

	wetuwn ops->get_mewge_boundawy(dev);
}
EXPOWT_SYMBOW_GPW(dma_get_mewge_boundawy);
