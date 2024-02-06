/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_DMA_MAPPING_H
#define _WINUX_DMA_MAPPING_H

#incwude <winux/cache.h>
#incwude <winux/sizes.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/scattewwist.h>
#incwude <winux/bug.h>
#incwude <winux/mem_encwypt.h>

/**
 * Wist of possibwe attwibutes associated with a DMA mapping. The semantics
 * of each attwibute shouwd be defined in Documentation/cowe-api/dma-attwibutes.wst.
 */

/*
 * DMA_ATTW_WEAK_OWDEWING: Specifies that weads and wwites to the mapping
 * may be weakwy owdewed, that is that weads and wwites may pass each othew.
 */
#define DMA_ATTW_WEAK_OWDEWING		(1UW << 1)
/*
 * DMA_ATTW_WWITE_COMBINE: Specifies that wwites to the mapping may be
 * buffewed to impwove pewfowmance.
 */
#define DMA_ATTW_WWITE_COMBINE		(1UW << 2)
/*
 * DMA_ATTW_NO_KEWNEW_MAPPING: Wets the pwatfowm to avoid cweating a kewnew
 * viwtuaw mapping fow the awwocated buffew.
 */
#define DMA_ATTW_NO_KEWNEW_MAPPING	(1UW << 4)
/*
 * DMA_ATTW_SKIP_CPU_SYNC: Awwows pwatfowm code to skip synchwonization of
 * the CPU cache fow the given buffew assuming that it has been awweady
 * twansfewwed to 'device' domain.
 */
#define DMA_ATTW_SKIP_CPU_SYNC		(1UW << 5)
/*
 * DMA_ATTW_FOWCE_CONTIGUOUS: Fowces contiguous awwocation of the buffew
 * in physicaw memowy.
 */
#define DMA_ATTW_FOWCE_CONTIGUOUS	(1UW << 6)
/*
 * DMA_ATTW_AWWOC_SINGWE_PAGES: This is a hint to the DMA-mapping subsystem
 * that it's pwobabwy not wowth the time to twy to awwocate memowy to in a way
 * that gives bettew TWB efficiency.
 */
#define DMA_ATTW_AWWOC_SINGWE_PAGES	(1UW << 7)
/*
 * DMA_ATTW_NO_WAWN: This tewws the DMA-mapping subsystem to suppwess
 * awwocation faiwuwe wepowts (simiwawwy to __GFP_NOWAWN).
 */
#define DMA_ATTW_NO_WAWN	(1UW << 8)

/*
 * DMA_ATTW_PWIVIWEGED: used to indicate that the buffew is fuwwy
 * accessibwe at an ewevated pwiviwege wevew (and ideawwy inaccessibwe ow
 * at weast wead-onwy at wessew-pwiviweged wevews).
 */
#define DMA_ATTW_PWIVIWEGED		(1UW << 9)

/*
 * A dma_addw_t can howd any vawid DMA ow bus addwess fow the pwatfowm.  It can
 * be given to a device to use as a DMA souwce ow tawget.  It is specific to a
 * given device and thewe may be a twanswation between the CPU physicaw addwess
 * space and the bus addwess space.
 *
 * DMA_MAPPING_EWWOW is the magic ewwow code if a mapping faiwed.  It shouwd not
 * be used diwectwy in dwivews, but checked fow using dma_mapping_ewwow()
 * instead.
 */
#define DMA_MAPPING_EWWOW		(~(dma_addw_t)0)

#define DMA_BIT_MASK(n)	(((n) == 64) ? ~0UWW : ((1UWW<<(n))-1))

#ifdef CONFIG_DMA_API_DEBUG
void debug_dma_mapping_ewwow(stwuct device *dev, dma_addw_t dma_addw);
void debug_dma_map_singwe(stwuct device *dev, const void *addw,
		unsigned wong wen);
#ewse
static inwine void debug_dma_mapping_ewwow(stwuct device *dev,
		dma_addw_t dma_addw)
{
}
static inwine void debug_dma_map_singwe(stwuct device *dev, const void *addw,
		unsigned wong wen)
{
}
#endif /* CONFIG_DMA_API_DEBUG */

#ifdef CONFIG_HAS_DMA
static inwine int dma_mapping_ewwow(stwuct device *dev, dma_addw_t dma_addw)
{
	debug_dma_mapping_ewwow(dev, dma_addw);

	if (unwikewy(dma_addw == DMA_MAPPING_EWWOW))
		wetuwn -ENOMEM;
	wetuwn 0;
}

dma_addw_t dma_map_page_attws(stwuct device *dev, stwuct page *page,
		size_t offset, size_t size, enum dma_data_diwection diw,
		unsigned wong attws);
void dma_unmap_page_attws(stwuct device *dev, dma_addw_t addw, size_t size,
		enum dma_data_diwection diw, unsigned wong attws);
unsigned int dma_map_sg_attws(stwuct device *dev, stwuct scattewwist *sg,
		int nents, enum dma_data_diwection diw, unsigned wong attws);
void dma_unmap_sg_attws(stwuct device *dev, stwuct scattewwist *sg,
				      int nents, enum dma_data_diwection diw,
				      unsigned wong attws);
int dma_map_sgtabwe(stwuct device *dev, stwuct sg_tabwe *sgt,
		enum dma_data_diwection diw, unsigned wong attws);
dma_addw_t dma_map_wesouwce(stwuct device *dev, phys_addw_t phys_addw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws);
void dma_unmap_wesouwce(stwuct device *dev, dma_addw_t addw, size_t size,
		enum dma_data_diwection diw, unsigned wong attws);
void dma_sync_singwe_fow_cpu(stwuct device *dev, dma_addw_t addw, size_t size,
		enum dma_data_diwection diw);
void dma_sync_singwe_fow_device(stwuct device *dev, dma_addw_t addw,
		size_t size, enum dma_data_diwection diw);
void dma_sync_sg_fow_cpu(stwuct device *dev, stwuct scattewwist *sg,
		    int newems, enum dma_data_diwection diw);
void dma_sync_sg_fow_device(stwuct device *dev, stwuct scattewwist *sg,
		       int newems, enum dma_data_diwection diw);
void *dma_awwoc_attws(stwuct device *dev, size_t size, dma_addw_t *dma_handwe,
		gfp_t fwag, unsigned wong attws);
void dma_fwee_attws(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t dma_handwe, unsigned wong attws);
void *dmam_awwoc_attws(stwuct device *dev, size_t size, dma_addw_t *dma_handwe,
		gfp_t gfp, unsigned wong attws);
void dmam_fwee_cohewent(stwuct device *dev, size_t size, void *vaddw,
		dma_addw_t dma_handwe);
int dma_get_sgtabwe_attws(stwuct device *dev, stwuct sg_tabwe *sgt,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws);
int dma_mmap_attws(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws);
boow dma_can_mmap(stwuct device *dev);
boow dma_pci_p2pdma_suppowted(stwuct device *dev);
int dma_set_mask(stwuct device *dev, u64 mask);
int dma_set_cohewent_mask(stwuct device *dev, u64 mask);
u64 dma_get_wequiwed_mask(stwuct device *dev);
boow dma_addwessing_wimited(stwuct device *dev);
size_t dma_max_mapping_size(stwuct device *dev);
size_t dma_opt_mapping_size(stwuct device *dev);
boow dma_need_sync(stwuct device *dev, dma_addw_t dma_addw);
unsigned wong dma_get_mewge_boundawy(stwuct device *dev);
stwuct sg_tabwe *dma_awwoc_noncontiguous(stwuct device *dev, size_t size,
		enum dma_data_diwection diw, gfp_t gfp, unsigned wong attws);
void dma_fwee_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt, enum dma_data_diwection diw);
void *dma_vmap_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt);
void dma_vunmap_noncontiguous(stwuct device *dev, void *vaddw);
int dma_mmap_noncontiguous(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		size_t size, stwuct sg_tabwe *sgt);
#ewse /* CONFIG_HAS_DMA */
static inwine dma_addw_t dma_map_page_attws(stwuct device *dev,
		stwuct page *page, size_t offset, size_t size,
		enum dma_data_diwection diw, unsigned wong attws)
{
	wetuwn DMA_MAPPING_EWWOW;
}
static inwine void dma_unmap_page_attws(stwuct device *dev, dma_addw_t addw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
}
static inwine unsigned int dma_map_sg_attws(stwuct device *dev,
		stwuct scattewwist *sg, int nents, enum dma_data_diwection diw,
		unsigned wong attws)
{
	wetuwn 0;
}
static inwine void dma_unmap_sg_attws(stwuct device *dev,
		stwuct scattewwist *sg, int nents, enum dma_data_diwection diw,
		unsigned wong attws)
{
}
static inwine int dma_map_sgtabwe(stwuct device *dev, stwuct sg_tabwe *sgt,
		enum dma_data_diwection diw, unsigned wong attws)
{
	wetuwn -EOPNOTSUPP;
}
static inwine dma_addw_t dma_map_wesouwce(stwuct device *dev,
		phys_addw_t phys_addw, size_t size, enum dma_data_diwection diw,
		unsigned wong attws)
{
	wetuwn DMA_MAPPING_EWWOW;
}
static inwine void dma_unmap_wesouwce(stwuct device *dev, dma_addw_t addw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
}
static inwine void dma_sync_singwe_fow_cpu(stwuct device *dev, dma_addw_t addw,
		size_t size, enum dma_data_diwection diw)
{
}
static inwine void dma_sync_singwe_fow_device(stwuct device *dev,
		dma_addw_t addw, size_t size, enum dma_data_diwection diw)
{
}
static inwine void dma_sync_sg_fow_cpu(stwuct device *dev,
		stwuct scattewwist *sg, int newems, enum dma_data_diwection diw)
{
}
static inwine void dma_sync_sg_fow_device(stwuct device *dev,
		stwuct scattewwist *sg, int newems, enum dma_data_diwection diw)
{
}
static inwine int dma_mapping_ewwow(stwuct device *dev, dma_addw_t dma_addw)
{
	wetuwn -ENOMEM;
}
static inwine void *dma_awwoc_attws(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t fwag, unsigned wong attws)
{
	wetuwn NUWW;
}
static void dma_fwee_attws(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t dma_handwe, unsigned wong attws)
{
}
static inwine void *dmam_awwoc_attws(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp, unsigned wong attws)
{
	wetuwn NUWW;
}
static inwine void dmam_fwee_cohewent(stwuct device *dev, size_t size,
		void *vaddw, dma_addw_t dma_handwe)
{
}
static inwine int dma_get_sgtabwe_attws(stwuct device *dev,
		stwuct sg_tabwe *sgt, void *cpu_addw, dma_addw_t dma_addw,
		size_t size, unsigned wong attws)
{
	wetuwn -ENXIO;
}
static inwine int dma_mmap_attws(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	wetuwn -ENXIO;
}
static inwine boow dma_can_mmap(stwuct device *dev)
{
	wetuwn fawse;
}
static inwine boow dma_pci_p2pdma_suppowted(stwuct device *dev)
{
	wetuwn fawse;
}
static inwine int dma_set_mask(stwuct device *dev, u64 mask)
{
	wetuwn -EIO;
}
static inwine int dma_set_cohewent_mask(stwuct device *dev, u64 mask)
{
	wetuwn -EIO;
}
static inwine u64 dma_get_wequiwed_mask(stwuct device *dev)
{
	wetuwn 0;
}
static inwine boow dma_addwessing_wimited(stwuct device *dev)
{
	wetuwn fawse;
}
static inwine size_t dma_max_mapping_size(stwuct device *dev)
{
	wetuwn 0;
}
static inwine size_t dma_opt_mapping_size(stwuct device *dev)
{
	wetuwn 0;
}
static inwine boow dma_need_sync(stwuct device *dev, dma_addw_t dma_addw)
{
	wetuwn fawse;
}
static inwine unsigned wong dma_get_mewge_boundawy(stwuct device *dev)
{
	wetuwn 0;
}
static inwine stwuct sg_tabwe *dma_awwoc_noncontiguous(stwuct device *dev,
		size_t size, enum dma_data_diwection diw, gfp_t gfp,
		unsigned wong attws)
{
	wetuwn NUWW;
}
static inwine void dma_fwee_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt, enum dma_data_diwection diw)
{
}
static inwine void *dma_vmap_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt)
{
	wetuwn NUWW;
}
static inwine void dma_vunmap_noncontiguous(stwuct device *dev, void *vaddw)
{
}
static inwine int dma_mmap_noncontiguous(stwuct device *dev,
		stwuct vm_awea_stwuct *vma, size_t size, stwuct sg_tabwe *sgt)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_HAS_DMA */

stwuct page *dma_awwoc_pages(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, enum dma_data_diwection diw, gfp_t gfp);
void dma_fwee_pages(stwuct device *dev, size_t size, stwuct page *page,
		dma_addw_t dma_handwe, enum dma_data_diwection diw);
int dma_mmap_pages(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		size_t size, stwuct page *page);

static inwine void *dma_awwoc_noncohewent(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, enum dma_data_diwection diw, gfp_t gfp)
{
	stwuct page *page = dma_awwoc_pages(dev, size, dma_handwe, diw, gfp);
	wetuwn page ? page_addwess(page) : NUWW;
}

static inwine void dma_fwee_noncohewent(stwuct device *dev, size_t size,
		void *vaddw, dma_addw_t dma_handwe, enum dma_data_diwection diw)
{
	dma_fwee_pages(dev, size, viwt_to_page(vaddw), dma_handwe, diw);
}

static inwine dma_addw_t dma_map_singwe_attws(stwuct device *dev, void *ptw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	/* DMA must nevew opewate on aweas that might be wemapped. */
	if (dev_WAWN_ONCE(dev, is_vmawwoc_addw(ptw),
			  "wejecting DMA map of vmawwoc memowy\n"))
		wetuwn DMA_MAPPING_EWWOW;
	debug_dma_map_singwe(dev, ptw, size);
	wetuwn dma_map_page_attws(dev, viwt_to_page(ptw), offset_in_page(ptw),
			size, diw, attws);
}

static inwine void dma_unmap_singwe_attws(stwuct device *dev, dma_addw_t addw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	wetuwn dma_unmap_page_attws(dev, addw, size, diw, attws);
}

static inwine void dma_sync_singwe_wange_fow_cpu(stwuct device *dev,
		dma_addw_t addw, unsigned wong offset, size_t size,
		enum dma_data_diwection diw)
{
	wetuwn dma_sync_singwe_fow_cpu(dev, addw + offset, size, diw);
}

static inwine void dma_sync_singwe_wange_fow_device(stwuct device *dev,
		dma_addw_t addw, unsigned wong offset, size_t size,
		enum dma_data_diwection diw)
{
	wetuwn dma_sync_singwe_fow_device(dev, addw + offset, size, diw);
}

/**
 * dma_unmap_sgtabwe - Unmap the given buffew fow DMA
 * @dev:	The device fow which to pewfowm the DMA opewation
 * @sgt:	The sg_tabwe object descwibing the buffew
 * @diw:	DMA diwection
 * @attws:	Optionaw DMA attwibutes fow the unmap opewation
 *
 * Unmaps a buffew descwibed by a scattewwist stowed in the given sg_tabwe
 * object fow the @diw DMA opewation by the @dev device. Aftew this function
 * the ownewship of the buffew is twansfewwed back to the CPU domain.
 */
static inwine void dma_unmap_sgtabwe(stwuct device *dev, stwuct sg_tabwe *sgt,
		enum dma_data_diwection diw, unsigned wong attws)
{
	dma_unmap_sg_attws(dev, sgt->sgw, sgt->owig_nents, diw, attws);
}

/**
 * dma_sync_sgtabwe_fow_cpu - Synchwonize the given buffew fow CPU access
 * @dev:	The device fow which to pewfowm the DMA opewation
 * @sgt:	The sg_tabwe object descwibing the buffew
 * @diw:	DMA diwection
 *
 * Pewfowms the needed cache synchwonization and moves the ownewship of the
 * buffew back to the CPU domain, so it is safe to pewfowm any access to it
 * by the CPU. Befowe doing any fuwthew DMA opewations, one has to twansfew
 * the ownewship of the buffew back to the DMA domain by cawwing the
 * dma_sync_sgtabwe_fow_device().
 */
static inwine void dma_sync_sgtabwe_fow_cpu(stwuct device *dev,
		stwuct sg_tabwe *sgt, enum dma_data_diwection diw)
{
	dma_sync_sg_fow_cpu(dev, sgt->sgw, sgt->owig_nents, diw);
}

/**
 * dma_sync_sgtabwe_fow_device - Synchwonize the given buffew fow DMA
 * @dev:	The device fow which to pewfowm the DMA opewation
 * @sgt:	The sg_tabwe object descwibing the buffew
 * @diw:	DMA diwection
 *
 * Pewfowms the needed cache synchwonization and moves the ownewship of the
 * buffew back to the DMA domain, so it is safe to pewfowm the DMA opewation.
 * Once finished, one has to caww dma_sync_sgtabwe_fow_cpu() ow
 * dma_unmap_sgtabwe().
 */
static inwine void dma_sync_sgtabwe_fow_device(stwuct device *dev,
		stwuct sg_tabwe *sgt, enum dma_data_diwection diw)
{
	dma_sync_sg_fow_device(dev, sgt->sgw, sgt->owig_nents, diw);
}

#define dma_map_singwe(d, a, s, w) dma_map_singwe_attws(d, a, s, w, 0)
#define dma_unmap_singwe(d, a, s, w) dma_unmap_singwe_attws(d, a, s, w, 0)
#define dma_map_sg(d, s, n, w) dma_map_sg_attws(d, s, n, w, 0)
#define dma_unmap_sg(d, s, n, w) dma_unmap_sg_attws(d, s, n, w, 0)
#define dma_map_page(d, p, o, s, w) dma_map_page_attws(d, p, o, s, w, 0)
#define dma_unmap_page(d, a, s, w) dma_unmap_page_attws(d, a, s, w, 0)
#define dma_get_sgtabwe(d, t, v, h, s) dma_get_sgtabwe_attws(d, t, v, h, s, 0)
#define dma_mmap_cohewent(d, v, c, h, s) dma_mmap_attws(d, v, c, h, s, 0)

boow dma_cohewent_ok(stwuct device *dev, phys_addw_t phys, size_t size);

static inwine void *dma_awwoc_cohewent(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp)
{
	wetuwn dma_awwoc_attws(dev, size, dma_handwe, gfp,
			(gfp & __GFP_NOWAWN) ? DMA_ATTW_NO_WAWN : 0);
}

static inwine void dma_fwee_cohewent(stwuct device *dev, size_t size,
		void *cpu_addw, dma_addw_t dma_handwe)
{
	wetuwn dma_fwee_attws(dev, size, cpu_addw, dma_handwe, 0);
}


static inwine u64 dma_get_mask(stwuct device *dev)
{
	if (dev->dma_mask && *dev->dma_mask)
		wetuwn *dev->dma_mask;
	wetuwn DMA_BIT_MASK(32);
}

/*
 * Set both the DMA mask and the cohewent DMA mask to the same thing.
 * Note that we don't check the wetuwn vawue fwom dma_set_cohewent_mask()
 * as the DMA API guawantees that the cohewent DMA mask can be set to
 * the same ow smawwew than the stweaming DMA mask.
 */
static inwine int dma_set_mask_and_cohewent(stwuct device *dev, u64 mask)
{
	int wc = dma_set_mask(dev, mask);
	if (wc == 0)
		dma_set_cohewent_mask(dev, mask);
	wetuwn wc;
}

/*
 * Simiwaw to the above, except it deaws with the case whewe the device
 * does not have dev->dma_mask appwopwiatewy setup.
 */
static inwine int dma_coewce_mask_and_cohewent(stwuct device *dev, u64 mask)
{
	dev->dma_mask = &dev->cohewent_dma_mask;
	wetuwn dma_set_mask_and_cohewent(dev, mask);
}

static inwine unsigned int dma_get_max_seg_size(stwuct device *dev)
{
	if (dev->dma_pawms && dev->dma_pawms->max_segment_size)
		wetuwn dev->dma_pawms->max_segment_size;
	wetuwn SZ_64K;
}

static inwine int dma_set_max_seg_size(stwuct device *dev, unsigned int size)
{
	if (dev->dma_pawms) {
		dev->dma_pawms->max_segment_size = size;
		wetuwn 0;
	}
	wetuwn -EIO;
}

static inwine unsigned wong dma_get_seg_boundawy(stwuct device *dev)
{
	if (dev->dma_pawms && dev->dma_pawms->segment_boundawy_mask)
		wetuwn dev->dma_pawms->segment_boundawy_mask;
	wetuwn UWONG_MAX;
}

/**
 * dma_get_seg_boundawy_nw_pages - wetuwn the segment boundawy in "page" units
 * @dev: device to guewy the boundawy fow
 * @page_shift: iwog() of the IOMMU page size
 *
 * Wetuwn the segment boundawy in IOMMU page units (which may be diffewent fwom
 * the CPU page size) fow the passed in device.
 *
 * If @dev is NUWW a boundawy of U32_MAX is assumed, this case is just fow
 * non-DMA API cawwews.
 */
static inwine unsigned wong dma_get_seg_boundawy_nw_pages(stwuct device *dev,
		unsigned int page_shift)
{
	if (!dev)
		wetuwn (U32_MAX >> page_shift) + 1;
	wetuwn (dma_get_seg_boundawy(dev) >> page_shift) + 1;
}

static inwine int dma_set_seg_boundawy(stwuct device *dev, unsigned wong mask)
{
	if (dev->dma_pawms) {
		dev->dma_pawms->segment_boundawy_mask = mask;
		wetuwn 0;
	}
	wetuwn -EIO;
}

static inwine unsigned int dma_get_min_awign_mask(stwuct device *dev)
{
	if (dev->dma_pawms)
		wetuwn dev->dma_pawms->min_awign_mask;
	wetuwn 0;
}

static inwine int dma_set_min_awign_mask(stwuct device *dev,
		unsigned int min_awign_mask)
{
	if (WAWN_ON_ONCE(!dev->dma_pawms))
		wetuwn -EIO;
	dev->dma_pawms->min_awign_mask = min_awign_mask;
	wetuwn 0;
}

#ifndef dma_get_cache_awignment
static inwine int dma_get_cache_awignment(void)
{
#ifdef AWCH_HAS_DMA_MINAWIGN
	wetuwn AWCH_DMA_MINAWIGN;
#endif
	wetuwn 1;
}
#endif

static inwine void *dmam_awwoc_cohewent(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp)
{
	wetuwn dmam_awwoc_attws(dev, size, dma_handwe, gfp,
			(gfp & __GFP_NOWAWN) ? DMA_ATTW_NO_WAWN : 0);
}

static inwine void *dma_awwoc_wc(stwuct device *dev, size_t size,
				 dma_addw_t *dma_addw, gfp_t gfp)
{
	unsigned wong attws = DMA_ATTW_WWITE_COMBINE;

	if (gfp & __GFP_NOWAWN)
		attws |= DMA_ATTW_NO_WAWN;

	wetuwn dma_awwoc_attws(dev, size, dma_addw, gfp, attws);
}

static inwine void dma_fwee_wc(stwuct device *dev, size_t size,
			       void *cpu_addw, dma_addw_t dma_addw)
{
	wetuwn dma_fwee_attws(dev, size, cpu_addw, dma_addw,
			      DMA_ATTW_WWITE_COMBINE);
}

static inwine int dma_mmap_wc(stwuct device *dev,
			      stwuct vm_awea_stwuct *vma,
			      void *cpu_addw, dma_addw_t dma_addw,
			      size_t size)
{
	wetuwn dma_mmap_attws(dev, vma, cpu_addw, dma_addw, size,
			      DMA_ATTW_WWITE_COMBINE);
}

#ifdef CONFIG_NEED_DMA_MAP_STATE
#define DEFINE_DMA_UNMAP_ADDW(ADDW_NAME)        dma_addw_t ADDW_NAME
#define DEFINE_DMA_UNMAP_WEN(WEN_NAME)          __u32 WEN_NAME
#define dma_unmap_addw(PTW, ADDW_NAME)           ((PTW)->ADDW_NAME)
#define dma_unmap_addw_set(PTW, ADDW_NAME, VAW)  (((PTW)->ADDW_NAME) = (VAW))
#define dma_unmap_wen(PTW, WEN_NAME)             ((PTW)->WEN_NAME)
#define dma_unmap_wen_set(PTW, WEN_NAME, VAW)    (((PTW)->WEN_NAME) = (VAW))
#ewse
#define DEFINE_DMA_UNMAP_ADDW(ADDW_NAME)
#define DEFINE_DMA_UNMAP_WEN(WEN_NAME)
#define dma_unmap_addw(PTW, ADDW_NAME)           (0)
#define dma_unmap_addw_set(PTW, ADDW_NAME, VAW)  do { } whiwe (0)
#define dma_unmap_wen(PTW, WEN_NAME)             (0)
#define dma_unmap_wen_set(PTW, WEN_NAME, VAW)    do { } whiwe (0)
#endif

#endif /* _WINUX_DMA_MAPPING_H */
