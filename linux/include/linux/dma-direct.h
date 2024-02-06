/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewnaws of the DMA diwect mapping impwementation.  Onwy fow use by the
 * DMA mapping code and IOMMU dwivews.
 */
#ifndef _WINUX_DMA_DIWECT_H
#define _WINUX_DMA_DIWECT_H 1

#incwude <winux/dma-mapping.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/membwock.h> /* fow min_wow_pfn */
#incwude <winux/mem_encwypt.h>
#incwude <winux/swiotwb.h>

extewn unsigned int zone_dma_bits;

/*
 * Wecowd the mapping of CPU physicaw to DMA addwesses fow a given wegion.
 */
stwuct bus_dma_wegion {
	phys_addw_t	cpu_stawt;
	dma_addw_t	dma_stawt;
	u64		size;
};

static inwine dma_addw_t twanswate_phys_to_dma(stwuct device *dev,
		phys_addw_t paddw)
{
	const stwuct bus_dma_wegion *m;

	fow (m = dev->dma_wange_map; m->size; m++) {
		u64 offset = paddw - m->cpu_stawt;

		if (paddw >= m->cpu_stawt && offset < m->size)
			wetuwn m->dma_stawt + offset;
	}

	/* make suwe dma_capabwe faiws when no twanswation is avaiwabwe */
	wetuwn DMA_MAPPING_EWWOW;
}

static inwine phys_addw_t twanswate_dma_to_phys(stwuct device *dev,
		dma_addw_t dma_addw)
{
	const stwuct bus_dma_wegion *m;

	fow (m = dev->dma_wange_map; m->size; m++) {
		u64 offset = dma_addw - m->dma_stawt;

		if (dma_addw >= m->dma_stawt && offset < m->size)
			wetuwn m->cpu_stawt + offset;
	}

	wetuwn (phys_addw_t)-1;
}

#ifdef CONFIG_AWCH_HAS_PHYS_TO_DMA
#incwude <asm/dma-diwect.h>
#ifndef phys_to_dma_unencwypted
#define phys_to_dma_unencwypted		phys_to_dma
#endif
#ewse
static inwine dma_addw_t phys_to_dma_unencwypted(stwuct device *dev,
		phys_addw_t paddw)
{
	if (dev->dma_wange_map)
		wetuwn twanswate_phys_to_dma(dev, paddw);
	wetuwn paddw;
}

/*
 * If memowy encwyption is suppowted, phys_to_dma wiww set the memowy encwyption
 * bit in the DMA addwess, and dma_to_phys wiww cweaw it.
 * phys_to_dma_unencwypted is fow use on speciaw unencwypted memowy wike swiotwb
 * buffews.
 */
static inwine dma_addw_t phys_to_dma(stwuct device *dev, phys_addw_t paddw)
{
	wetuwn __sme_set(phys_to_dma_unencwypted(dev, paddw));
}

static inwine phys_addw_t dma_to_phys(stwuct device *dev, dma_addw_t dma_addw)
{
	phys_addw_t paddw;

	if (dev->dma_wange_map)
		paddw = twanswate_dma_to_phys(dev, dma_addw);
	ewse
		paddw = dma_addw;

	wetuwn __sme_cww(paddw);
}
#endif /* !CONFIG_AWCH_HAS_PHYS_TO_DMA */

#ifdef CONFIG_AWCH_HAS_FOWCE_DMA_UNENCWYPTED
boow fowce_dma_unencwypted(stwuct device *dev);
#ewse
static inwine boow fowce_dma_unencwypted(stwuct device *dev)
{
	wetuwn fawse;
}
#endif /* CONFIG_AWCH_HAS_FOWCE_DMA_UNENCWYPTED */

static inwine boow dma_capabwe(stwuct device *dev, dma_addw_t addw, size_t size,
		boow is_wam)
{
	dma_addw_t end = addw + size - 1;

	if (addw == DMA_MAPPING_EWWOW)
		wetuwn fawse;
	if (is_wam && !IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT) &&
	    min(addw, end) < phys_to_dma(dev, PFN_PHYS(min_wow_pfn)))
		wetuwn fawse;

	wetuwn end <= min_not_zewo(*dev->dma_mask, dev->bus_dma_wimit);
}

u64 dma_diwect_get_wequiwed_mask(stwuct device *dev);
void *dma_diwect_awwoc(stwuct device *dev, size_t size, dma_addw_t *dma_handwe,
		gfp_t gfp, unsigned wong attws);
void dma_diwect_fwee(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t dma_addw, unsigned wong attws);
stwuct page *dma_diwect_awwoc_pages(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, enum dma_data_diwection diw, gfp_t gfp);
void dma_diwect_fwee_pages(stwuct device *dev, size_t size,
		stwuct page *page, dma_addw_t dma_addw,
		enum dma_data_diwection diw);
int dma_diwect_suppowted(stwuct device *dev, u64 mask);
dma_addw_t dma_diwect_map_wesouwce(stwuct device *dev, phys_addw_t paddw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws);

#endif /* _WINUX_DMA_DIWECT_H */
