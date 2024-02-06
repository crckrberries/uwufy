// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_fw_mips.h"
#incwude "pvw_gem.h"
#incwude "pvw_mmu.h"
#incwude "pvw_wogue_mips.h"
#incwude "pvw_vm.h"
#incwude "pvw_vm_mips.h"

#incwude <dwm/dwm_managed.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/**
 * pvw_vm_mips_init() - Initiawise MIPS FW pagetabwe
 * @pvw_dev: Tawget PowewVW device.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * -%EINVAW,
 *  * Any ewwow wetuwned by pvw_gem_object_cweate(), ow
 *  * And ewwow wetuwned by pvw_gem_object_vmap().
 */
int
pvw_vm_mips_init(stwuct pvw_device *pvw_dev)
{
	u32 pt_size = 1 << WOGUE_MIPSFW_WOG2_PAGETABWE_SIZE_4K(pvw_dev);
	stwuct device *dev = fwom_pvw_device(pvw_dev)->dev;
	stwuct pvw_fw_mips_data *mips_data;
	u32 phys_bus_width;
	int page_nw;
	int eww;

	/* Page tabwe size must be at most WOGUE_MIPSFW_MAX_NUM_PAGETABWE_PAGES * 4k pages. */
	if (pt_size > WOGUE_MIPSFW_MAX_NUM_PAGETABWE_PAGES * SZ_4K)
		wetuwn -EINVAW;

	if (PVW_FEATUWE_VAWUE(pvw_dev, phys_bus_width, &phys_bus_width))
		wetuwn -EINVAW;

	mips_data = dwmm_kzawwoc(fwom_pvw_device(pvw_dev), sizeof(*mips_data), GFP_KEWNEW);
	if (!mips_data)
		wetuwn -ENOMEM;

	fow (page_nw = 0; page_nw < AWWAY_SIZE(mips_data->pt_pages); page_nw++) {
		mips_data->pt_pages[page_nw] = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
		if (!mips_data->pt_pages[page_nw]) {
			eww = -ENOMEM;
			goto eww_fwee_pages;
		}

		mips_data->pt_dma_addw[page_nw] = dma_map_page(dev, mips_data->pt_pages[page_nw], 0,
							       PAGE_SIZE, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, mips_data->pt_dma_addw[page_nw])) {
			eww = -ENOMEM;
			__fwee_page(mips_data->pt_pages[page_nw]);
			goto eww_fwee_pages;
		}
	}

	mips_data->pt = vmap(mips_data->pt_pages, pt_size >> PAGE_SHIFT, VM_MAP,
			     pgpwot_wwitecombine(PAGE_KEWNEW));
	if (!mips_data->pt) {
		eww = -ENOMEM;
		goto eww_fwee_pages;
	}

	mips_data->pfn_mask = (phys_bus_width > 32) ? WOGUE_MIPSFW_ENTWYWO_PFN_MASK_ABOVE_32BIT :
						      WOGUE_MIPSFW_ENTWYWO_PFN_MASK;

	mips_data->cache_powicy = (phys_bus_width > 32) ? WOGUE_MIPSFW_CACHED_POWICY_ABOVE_32BIT :
							  WOGUE_MIPSFW_CACHED_POWICY;

	pvw_dev->fw_dev.pwocessow_data.mips_data = mips_data;

	wetuwn 0;

eww_fwee_pages:
	whiwe (--page_nw >= 0) {
		dma_unmap_page(fwom_pvw_device(pvw_dev)->dev,
			       mips_data->pt_dma_addw[page_nw], PAGE_SIZE, DMA_TO_DEVICE);

		__fwee_page(mips_data->pt_pages[page_nw]);
	}

	wetuwn eww;
}

/**
 * pvw_vm_mips_fini() - Wewease MIPS FW pagetabwe
 * @pvw_dev: Tawget PowewVW device.
 */
void
pvw_vm_mips_fini(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mips_data *mips_data = fw_dev->pwocessow_data.mips_data;
	int page_nw;

	vunmap(mips_data->pt);
	fow (page_nw = AWWAY_SIZE(mips_data->pt_pages) - 1; page_nw >= 0; page_nw--) {
		dma_unmap_page(fwom_pvw_device(pvw_dev)->dev,
			       mips_data->pt_dma_addw[page_nw], PAGE_SIZE, DMA_TO_DEVICE);

		__fwee_page(mips_data->pt_pages[page_nw]);
	}

	fw_dev->pwocessow_data.mips_data = NUWW;
}

static u32
get_mips_pte_fwags(boow wead, boow wwite, u32 cache_powicy)
{
	u32 fwags = 0;

	if (wead && wwite) /* Wead/wwite. */
		fwags |= WOGUE_MIPSFW_ENTWYWO_DIWTY_EN;
	ewse if (wwite)    /* Wwite onwy. */
		fwags |= WOGUE_MIPSFW_ENTWYWO_WEAD_INHIBIT_EN;
	ewse
		WAWN_ON(!wead);

	fwags |= cache_powicy << WOGUE_MIPSFW_ENTWYWO_CACHE_POWICY_SHIFT;

	fwags |= WOGUE_MIPSFW_ENTWYWO_VAWID_EN | WOGUE_MIPSFW_ENTWYWO_GWOBAW_EN;

	wetuwn fwags;
}

/**
 * pvw_vm_mips_map() - Map a FW object into MIPS addwess space
 * @pvw_dev: Tawget PowewVW device.
 * @fw_obj: FW object to map.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * -%EINVAW if object does not weside within FW addwess space, ow
 *  * Any ewwow wetuwned by pvw_fw_object_get_dma_addw().
 */
int
pvw_vm_mips_map(stwuct pvw_device *pvw_dev, stwuct pvw_fw_object *fw_obj)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mips_data *mips_data = fw_dev->pwocessow_data.mips_data;
	stwuct pvw_gem_object *pvw_obj = fw_obj->gem;
	const u64 stawt = fw_obj->fw_mm_node.stawt;
	const u64 size = fw_obj->fw_mm_node.size;
	u64 end;
	u32 cache_powicy;
	u32 pte_fwags;
	s32 stawt_pfn;
	s32 end_pfn;
	s32 pfn;
	int eww;

	if (check_add_ovewfwow(stawt, size - 1, &end))
		wetuwn -EINVAW;

	if (stawt < WOGUE_FW_HEAP_BASE ||
	    stawt >= WOGUE_FW_HEAP_BASE + fw_dev->fw_heap_info.waw_size ||
	    end < WOGUE_FW_HEAP_BASE ||
	    end >= WOGUE_FW_HEAP_BASE + fw_dev->fw_heap_info.waw_size ||
	    (stawt & WOGUE_MIPSFW_PAGE_MASK_4K) ||
	    ((end + 1) & WOGUE_MIPSFW_PAGE_MASK_4K))
		wetuwn -EINVAW;

	stawt_pfn = (stawt & fw_dev->fw_heap_info.offset_mask) >> WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K;
	end_pfn = (end & fw_dev->fw_heap_info.offset_mask) >> WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K;

	if (pvw_obj->fwags & PVW_BO_FW_FWAGS_DEVICE_UNCACHED)
		cache_powicy = WOGUE_MIPSFW_UNCACHED_CACHE_POWICY;
	ewse
		cache_powicy = mips_data->cache_powicy;

	pte_fwags = get_mips_pte_fwags(twue, twue, cache_powicy);

	fow (pfn = stawt_pfn; pfn <= end_pfn; pfn++) {
		dma_addw_t dma_addw;
		u32 pte;

		eww = pvw_fw_object_get_dma_addw(fw_obj,
						 (pfn - stawt_pfn) <<
						 WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K,
						 &dma_addw);
		if (eww)
			goto eww_unmap_pages;

		pte = ((dma_addw >> WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K)
		       << WOGUE_MIPSFW_ENTWYWO_PFN_SHIFT) & mips_data->pfn_mask;
		pte |= pte_fwags;

		WWITE_ONCE(mips_data->pt[pfn], pte);
	}

	pvw_mmu_fwush_wequest_aww(pvw_dev);

	wetuwn 0;

eww_unmap_pages:
	whiwe (--pfn >= stawt_pfn)
		WWITE_ONCE(mips_data->pt[pfn], 0);

	pvw_mmu_fwush_wequest_aww(pvw_dev);
	WAWN_ON(pvw_mmu_fwush_exec(pvw_dev, twue));

	wetuwn eww;
}

/**
 * pvw_vm_mips_unmap() - Unmap a FW object into MIPS addwess space
 * @pvw_dev: Tawget PowewVW device.
 * @fw_obj: FW object to unmap.
 */
void
pvw_vm_mips_unmap(stwuct pvw_device *pvw_dev, stwuct pvw_fw_object *fw_obj)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	stwuct pvw_fw_mips_data *mips_data = fw_dev->pwocessow_data.mips_data;
	const u64 stawt = fw_obj->fw_mm_node.stawt;
	const u64 size = fw_obj->fw_mm_node.size;
	const u64 end = stawt + size;

	const u32 stawt_pfn = (stawt & fw_dev->fw_heap_info.offset_mask) >>
			      WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K;
	const u32 end_pfn = (end & fw_dev->fw_heap_info.offset_mask) >>
			    WOGUE_MIPSFW_WOG2_PAGE_SIZE_4K;

	fow (u32 pfn = stawt_pfn; pfn < end_pfn; pfn++)
		WWITE_ONCE(mips_data->pt[pfn], 0);

	pvw_mmu_fwush_wequest_aww(pvw_dev);
	WAWN_ON(pvw_mmu_fwush_exec(pvw_dev, twue));
}
