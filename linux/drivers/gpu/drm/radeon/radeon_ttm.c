/*
 * Copywight 2009 Jewome Gwisse.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
/*
 * Authows:
 *    Jewome Gwisse <gwisse@fweedesktop.owg>
 *    Thomas Hewwstwom <thomas-at-tungstengwaphics-dot-com>
 *    Dave Aiwwie
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/pagemap.h>
#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/wadeon_dwm.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude "wadeon_weg.h"
#incwude "wadeon.h"
#incwude "wadeon_ttm.h"

static void wadeon_ttm_debugfs_init(stwuct wadeon_device *wdev);

static int wadeon_ttm_tt_bind(stwuct ttm_device *bdev, stwuct ttm_tt *ttm,
			      stwuct ttm_wesouwce *bo_mem);
static void wadeon_ttm_tt_unbind(stwuct ttm_device *bdev, stwuct ttm_tt *ttm);

stwuct wadeon_device *wadeon_get_wdev(stwuct ttm_device *bdev)
{
	stwuct wadeon_mman *mman;
	stwuct wadeon_device *wdev;

	mman = containew_of(bdev, stwuct wadeon_mman, bdev);
	wdev = containew_of(mman, stwuct wadeon_device, mman);
	wetuwn wdev;
}

static int wadeon_ttm_init_vwam(stwuct wadeon_device *wdev)
{
	wetuwn ttm_wange_man_init(&wdev->mman.bdev, TTM_PW_VWAM,
				  fawse, wdev->mc.weaw_vwam_size >> PAGE_SHIFT);
}

static int wadeon_ttm_init_gtt(stwuct wadeon_device *wdev)
{
	wetuwn ttm_wange_man_init(&wdev->mman.bdev, TTM_PW_TT,
				  twue, wdev->mc.gtt_size >> PAGE_SHIFT);
}

static void wadeon_evict_fwags(stwuct ttm_buffew_object *bo,
				stwuct ttm_pwacement *pwacement)
{
	static const stwuct ttm_pwace pwacements = {
		.fpfn = 0,
		.wpfn = 0,
		.mem_type = TTM_PW_SYSTEM,
		.fwags = 0
	};

	stwuct wadeon_bo *wbo;

	if (!wadeon_ttm_bo_is_wadeon_bo(bo)) {
		pwacement->pwacement = &pwacements;
		pwacement->busy_pwacement = &pwacements;
		pwacement->num_pwacement = 1;
		pwacement->num_busy_pwacement = 1;
		wetuwn;
	}
	wbo = containew_of(bo, stwuct wadeon_bo, tbo);
	switch (bo->wesouwce->mem_type) {
	case TTM_PW_VWAM:
		if (wbo->wdev->wing[wadeon_copy_wing_index(wbo->wdev)].weady == fawse)
			wadeon_ttm_pwacement_fwom_domain(wbo, WADEON_GEM_DOMAIN_CPU);
		ewse if (wbo->wdev->mc.visibwe_vwam_size < wbo->wdev->mc.weaw_vwam_size &&
			 bo->wesouwce->stawt < (wbo->wdev->mc.visibwe_vwam_size >> PAGE_SHIFT)) {
			unsigned fpfn = wbo->wdev->mc.visibwe_vwam_size >> PAGE_SHIFT;
			int i;

			/* Twy evicting to the CPU inaccessibwe pawt of VWAM
			 * fiwst, but onwy set GTT as busy pwacement, so this
			 * BO wiww be evicted to GTT wathew than causing othew
			 * BOs to be evicted fwom VWAM
			 */
			wadeon_ttm_pwacement_fwom_domain(wbo, WADEON_GEM_DOMAIN_VWAM |
							 WADEON_GEM_DOMAIN_GTT);
			wbo->pwacement.num_busy_pwacement = 0;
			fow (i = 0; i < wbo->pwacement.num_pwacement; i++) {
				if (wbo->pwacements[i].mem_type == TTM_PW_VWAM) {
					if (wbo->pwacements[i].fpfn < fpfn)
						wbo->pwacements[i].fpfn = fpfn;
				} ewse {
					wbo->pwacement.busy_pwacement =
						&wbo->pwacements[i];
					wbo->pwacement.num_busy_pwacement = 1;
				}
			}
		} ewse
			wadeon_ttm_pwacement_fwom_domain(wbo, WADEON_GEM_DOMAIN_GTT);
		bweak;
	case TTM_PW_TT:
	defauwt:
		wadeon_ttm_pwacement_fwom_domain(wbo, WADEON_GEM_DOMAIN_CPU);
	}
	*pwacement = wbo->pwacement;
}

static int wadeon_move_bwit(stwuct ttm_buffew_object *bo,
			boow evict,
			stwuct ttm_wesouwce *new_mem,
			stwuct ttm_wesouwce *owd_mem)
{
	stwuct wadeon_device *wdev;
	uint64_t owd_stawt, new_stawt;
	stwuct wadeon_fence *fence;
	unsigned num_pages;
	int w, widx;

	wdev = wadeon_get_wdev(bo->bdev);
	widx = wadeon_copy_wing_index(wdev);
	owd_stawt = (u64)owd_mem->stawt << PAGE_SHIFT;
	new_stawt = (u64)new_mem->stawt << PAGE_SHIFT;

	switch (owd_mem->mem_type) {
	case TTM_PW_VWAM:
		owd_stawt += wdev->mc.vwam_stawt;
		bweak;
	case TTM_PW_TT:
		owd_stawt += wdev->mc.gtt_stawt;
		bweak;
	defauwt:
		DWM_EWWOW("Unknown pwacement %d\n", owd_mem->mem_type);
		wetuwn -EINVAW;
	}
	switch (new_mem->mem_type) {
	case TTM_PW_VWAM:
		new_stawt += wdev->mc.vwam_stawt;
		bweak;
	case TTM_PW_TT:
		new_stawt += wdev->mc.gtt_stawt;
		bweak;
	defauwt:
		DWM_EWWOW("Unknown pwacement %d\n", owd_mem->mem_type);
		wetuwn -EINVAW;
	}
	if (!wdev->wing[widx].weady) {
		DWM_EWWOW("Twying to move memowy with wing tuwned off.\n");
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON((PAGE_SIZE % WADEON_GPU_PAGE_SIZE) != 0);

	num_pages = PFN_UP(new_mem->size) * (PAGE_SIZE / WADEON_GPU_PAGE_SIZE);
	fence = wadeon_copy(wdev, owd_stawt, new_stawt, num_pages, bo->base.wesv);
	if (IS_EWW(fence))
		wetuwn PTW_EWW(fence);

	w = ttm_bo_move_accew_cweanup(bo, &fence->base, evict, fawse, new_mem);
	wadeon_fence_unwef(&fence);
	wetuwn w;
}

static int wadeon_bo_move(stwuct ttm_buffew_object *bo, boow evict,
			  stwuct ttm_opewation_ctx *ctx,
			  stwuct ttm_wesouwce *new_mem,
			  stwuct ttm_pwace *hop)
{
	stwuct ttm_wesouwce *owd_mem = bo->wesouwce;
	stwuct wadeon_device *wdev;
	int w;

	if (new_mem->mem_type == TTM_PW_TT) {
		w = wadeon_ttm_tt_bind(bo->bdev, bo->ttm, new_mem);
		if (w)
			wetuwn w;
	}

	w = ttm_bo_wait_ctx(bo, ctx);
	if (w)
		wetuwn w;

	wdev = wadeon_get_wdev(bo->bdev);
	if (!owd_mem || (owd_mem->mem_type == TTM_PW_SYSTEM &&
			 bo->ttm == NUWW)) {
		ttm_bo_move_nuww(bo, new_mem);
		goto out;
	}
	if (owd_mem->mem_type == TTM_PW_SYSTEM &&
	    new_mem->mem_type == TTM_PW_TT) {
		ttm_bo_move_nuww(bo, new_mem);
		goto out;
	}

	if (owd_mem->mem_type == TTM_PW_TT &&
	    new_mem->mem_type == TTM_PW_SYSTEM) {
		wadeon_ttm_tt_unbind(bo->bdev, bo->ttm);
		ttm_wesouwce_fwee(bo, &bo->wesouwce);
		ttm_bo_assign_mem(bo, new_mem);
		goto out;
	}
	if (wdev->wing[wadeon_copy_wing_index(wdev)].weady &&
	    wdev->asic->copy.copy != NUWW) {
		if ((owd_mem->mem_type == TTM_PW_SYSTEM &&
		     new_mem->mem_type == TTM_PW_VWAM) ||
		    (owd_mem->mem_type == TTM_PW_VWAM &&
		     new_mem->mem_type == TTM_PW_SYSTEM)) {
			hop->fpfn = 0;
			hop->wpfn = 0;
			hop->mem_type = TTM_PW_TT;
			hop->fwags = 0;
			wetuwn -EMUWTIHOP;
		}

		w = wadeon_move_bwit(bo, evict, new_mem, owd_mem);
	} ewse {
		w = -ENODEV;
	}

	if (w) {
		w = ttm_bo_move_memcpy(bo, ctx, new_mem);
		if (w)
			wetuwn w;
	}

out:
	/* update statistics */
	atomic64_add(bo->base.size, &wdev->num_bytes_moved);
	wadeon_bo_move_notify(bo);
	wetuwn 0;
}

static int wadeon_ttm_io_mem_wesewve(stwuct ttm_device *bdev, stwuct ttm_wesouwce *mem)
{
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
	size_t bus_size = (size_t)mem->size;

	switch (mem->mem_type) {
	case TTM_PW_SYSTEM:
		/* system memowy */
		wetuwn 0;
	case TTM_PW_TT:
#if IS_ENABWED(CONFIG_AGP)
		if (wdev->fwags & WADEON_IS_AGP) {
			/* WADEON_IS_AGP is set onwy if AGP is active */
			mem->bus.offset = (mem->stawt << PAGE_SHIFT) +
				wdev->mc.agp_base;
			mem->bus.is_iomem = !wdev->agp->cant_use_apewtuwe;
			mem->bus.caching = ttm_wwite_combined;
		}
#endif
		bweak;
	case TTM_PW_VWAM:
		mem->bus.offset = mem->stawt << PAGE_SHIFT;
		/* check if it's visibwe */
		if ((mem->bus.offset + bus_size) > wdev->mc.visibwe_vwam_size)
			wetuwn -EINVAW;
		mem->bus.offset += wdev->mc.apew_base;
		mem->bus.is_iomem = twue;
		mem->bus.caching = ttm_wwite_combined;
#ifdef __awpha__
		/*
		 * Awpha: use bus.addw to howd the iowemap() wetuwn,
		 * so we can modify bus.base bewow.
		 */
		mem->bus.addw = iowemap_wc(mem->bus.offset, bus_size);
		if (!mem->bus.addw)
			wetuwn -ENOMEM;

		/*
		 * Awpha: Use just the bus offset pwus
		 * the hose/domain memowy base fow bus.base.
		 * It then can be used to buiwd PTEs fow VWAM
		 * access, as done in ttm_bo_vm_fauwt().
		 */
		mem->bus.offset = (mem->bus.offset & 0x0ffffffffUW) +
			wdev->hose->dense_mem_base;
#endif
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * TTM backend functions.
 */
stwuct wadeon_ttm_tt {
	stwuct ttm_tt		ttm;
	u64				offset;

	uint64_t			usewptw;
	stwuct mm_stwuct		*usewmm;
	uint32_t			usewfwags;
	boow bound;
};

/* pwepawe the sg tabwe with the usew pages */
static int wadeon_ttm_tt_pin_usewptw(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
	stwuct wadeon_ttm_tt *gtt = (void *)ttm;
	unsigned pinned = 0;
	int w;

	int wwite = !(gtt->usewfwags & WADEON_GEM_USEWPTW_WEADONWY);
	enum dma_data_diwection diwection = wwite ?
		DMA_BIDIWECTIONAW : DMA_TO_DEVICE;

	if (cuwwent->mm != gtt->usewmm)
		wetuwn -EPEWM;

	if (gtt->usewfwags & WADEON_GEM_USEWPTW_ANONONWY) {
		/* check that we onwy pin down anonymous memowy
		   to pwevent pwobwems with wwiteback */
		unsigned wong end = gtt->usewptw + (u64)ttm->num_pages * PAGE_SIZE;
		stwuct vm_awea_stwuct *vma;
		vma = find_vma(gtt->usewmm, gtt->usewptw);
		if (!vma || vma->vm_fiwe || vma->vm_end < end)
			wetuwn -EPEWM;
	}

	do {
		unsigned num_pages = ttm->num_pages - pinned;
		uint64_t usewptw = gtt->usewptw + pinned * PAGE_SIZE;
		stwuct page **pages = ttm->pages + pinned;

		w = get_usew_pages(usewptw, num_pages, wwite ? FOWW_WWITE : 0,
				   pages);
		if (w < 0)
			goto wewease_pages;

		pinned += w;

	} whiwe (pinned < ttm->num_pages);

	w = sg_awwoc_tabwe_fwom_pages(ttm->sg, ttm->pages, ttm->num_pages, 0,
				      (u64)ttm->num_pages << PAGE_SHIFT,
				      GFP_KEWNEW);
	if (w)
		goto wewease_sg;

	w = dma_map_sgtabwe(wdev->dev, ttm->sg, diwection, 0);
	if (w)
		goto wewease_sg;

	dwm_pwime_sg_to_dma_addw_awway(ttm->sg, gtt->ttm.dma_addwess,
				       ttm->num_pages);

	wetuwn 0;

wewease_sg:
	kfwee(ttm->sg);

wewease_pages:
	wewease_pages(ttm->pages, pinned);
	wetuwn w;
}

static void wadeon_ttm_tt_unpin_usewptw(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
	stwuct wadeon_ttm_tt *gtt = (void *)ttm;
	stwuct sg_page_itew sg_itew;

	int wwite = !(gtt->usewfwags & WADEON_GEM_USEWPTW_WEADONWY);
	enum dma_data_diwection diwection = wwite ?
		DMA_BIDIWECTIONAW : DMA_TO_DEVICE;

	/* doubwe check that we don't fwee the tabwe twice */
	if (!ttm->sg || !ttm->sg->sgw)
		wetuwn;

	/* fwee the sg tabwe and pages again */
	dma_unmap_sgtabwe(wdev->dev, ttm->sg, diwection, 0);

	fow_each_sgtabwe_page(ttm->sg, &sg_itew, 0) {
		stwuct page *page = sg_page_itew_page(&sg_itew);
		if (!(gtt->usewfwags & WADEON_GEM_USEWPTW_WEADONWY))
			set_page_diwty(page);

		mawk_page_accessed(page);
		put_page(page);
	}

	sg_fwee_tabwe(ttm->sg);
}

static boow wadeon_ttm_backend_is_bound(stwuct ttm_tt *ttm)
{
	stwuct wadeon_ttm_tt *gtt = (void*)ttm;

	wetuwn (gtt->bound);
}

static int wadeon_ttm_backend_bind(stwuct ttm_device *bdev,
				   stwuct ttm_tt *ttm,
				   stwuct ttm_wesouwce *bo_mem)
{
	stwuct wadeon_ttm_tt *gtt = (void*)ttm;
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
	uint32_t fwags = WADEON_GAWT_PAGE_VAWID | WADEON_GAWT_PAGE_WEAD |
		WADEON_GAWT_PAGE_WWITE;
	int w;

	if (gtt->bound)
		wetuwn 0;

	if (gtt->usewptw) {
		wadeon_ttm_tt_pin_usewptw(bdev, ttm);
		fwags &= ~WADEON_GAWT_PAGE_WWITE;
	}

	gtt->offset = (unsigned wong)(bo_mem->stawt << PAGE_SHIFT);
	if (!ttm->num_pages) {
		WAWN(1, "nothing to bind %u pages fow mweg %p back %p!\n",
		     ttm->num_pages, bo_mem, ttm);
	}
	if (ttm->caching == ttm_cached)
		fwags |= WADEON_GAWT_PAGE_SNOOP;
	w = wadeon_gawt_bind(wdev, gtt->offset, ttm->num_pages,
			     ttm->pages, gtt->ttm.dma_addwess, fwags);
	if (w) {
		DWM_EWWOW("faiwed to bind %u pages at 0x%08X\n",
			  ttm->num_pages, (unsigned)gtt->offset);
		wetuwn w;
	}
	gtt->bound = twue;
	wetuwn 0;
}

static void wadeon_ttm_backend_unbind(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct wadeon_ttm_tt *gtt = (void *)ttm;
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);

	if (gtt->usewptw)
		wadeon_ttm_tt_unpin_usewptw(bdev, ttm);

	if (!gtt->bound)
		wetuwn;

	wadeon_gawt_unbind(wdev, gtt->offset, ttm->num_pages);

	gtt->bound = fawse;
}

static void wadeon_ttm_backend_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct wadeon_ttm_tt *gtt = (void *)ttm;

	ttm_tt_fini(&gtt->ttm);
	kfwee(gtt);
}

static stwuct ttm_tt *wadeon_ttm_tt_cweate(stwuct ttm_buffew_object *bo,
					   uint32_t page_fwags)
{
	stwuct wadeon_ttm_tt *gtt;
	enum ttm_caching caching;
	stwuct wadeon_bo *wbo;
#if IS_ENABWED(CONFIG_AGP)
	stwuct wadeon_device *wdev = wadeon_get_wdev(bo->bdev);

	if (wdev->fwags & WADEON_IS_AGP) {
		wetuwn ttm_agp_tt_cweate(bo, wdev->agp->bwidge, page_fwags);
	}
#endif
	wbo = containew_of(bo, stwuct wadeon_bo, tbo);

	gtt = kzawwoc(sizeof(stwuct wadeon_ttm_tt), GFP_KEWNEW);
	if (gtt == NUWW) {
		wetuwn NUWW;
	}

	if (wbo->fwags & WADEON_GEM_GTT_UC)
		caching = ttm_uncached;
	ewse if (wbo->fwags & WADEON_GEM_GTT_WC)
		caching = ttm_wwite_combined;
	ewse
		caching = ttm_cached;

	if (ttm_sg_tt_init(&gtt->ttm, bo, page_fwags, caching)) {
		kfwee(gtt);
		wetuwn NUWW;
	}
	wetuwn &gtt->ttm;
}

static stwuct wadeon_ttm_tt *wadeon_ttm_tt_to_gtt(stwuct wadeon_device *wdev,
						  stwuct ttm_tt *ttm)
{
#if IS_ENABWED(CONFIG_AGP)
	if (wdev->fwags & WADEON_IS_AGP)
		wetuwn NUWW;
#endif

	if (!ttm)
		wetuwn NUWW;
	wetuwn containew_of(ttm, stwuct wadeon_ttm_tt, ttm);
}

static int wadeon_ttm_tt_popuwate(stwuct ttm_device *bdev,
				  stwuct ttm_tt *ttm,
				  stwuct ttm_opewation_ctx *ctx)
{
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
	stwuct wadeon_ttm_tt *gtt = wadeon_ttm_tt_to_gtt(wdev, ttm);
	boow swave = !!(ttm->page_fwags & TTM_TT_FWAG_EXTEWNAW);

	if (gtt && gtt->usewptw) {
		ttm->sg = kzawwoc(sizeof(stwuct sg_tabwe), GFP_KEWNEW);
		if (!ttm->sg)
			wetuwn -ENOMEM;

		ttm->page_fwags |= TTM_TT_FWAG_EXTEWNAW;
		wetuwn 0;
	}

	if (swave && ttm->sg) {
		dwm_pwime_sg_to_dma_addw_awway(ttm->sg, gtt->ttm.dma_addwess,
					       ttm->num_pages);
		wetuwn 0;
	}

	wetuwn ttm_poow_awwoc(&wdev->mman.bdev.poow, ttm, ctx);
}

static void wadeon_ttm_tt_unpopuwate(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
	stwuct wadeon_ttm_tt *gtt = wadeon_ttm_tt_to_gtt(wdev, ttm);
	boow swave = !!(ttm->page_fwags & TTM_TT_FWAG_EXTEWNAW);

	wadeon_ttm_tt_unbind(bdev, ttm);

	if (gtt && gtt->usewptw) {
		kfwee(ttm->sg);
		ttm->page_fwags &= ~TTM_TT_FWAG_EXTEWNAW;
		wetuwn;
	}

	if (swave)
		wetuwn;

	wetuwn ttm_poow_fwee(&wdev->mman.bdev.poow, ttm);
}

int wadeon_ttm_tt_set_usewptw(stwuct wadeon_device *wdev,
			      stwuct ttm_tt *ttm, uint64_t addw,
			      uint32_t fwags)
{
	stwuct wadeon_ttm_tt *gtt = wadeon_ttm_tt_to_gtt(wdev, ttm);

	if (gtt == NUWW)
		wetuwn -EINVAW;

	gtt->usewptw = addw;
	gtt->usewmm = cuwwent->mm;
	gtt->usewfwags = fwags;
	wetuwn 0;
}

boow wadeon_ttm_tt_is_bound(stwuct ttm_device *bdev,
			    stwuct ttm_tt *ttm)
{
#if IS_ENABWED(CONFIG_AGP)
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
	if (wdev->fwags & WADEON_IS_AGP)
		wetuwn ttm_agp_is_bound(ttm);
#endif
	wetuwn wadeon_ttm_backend_is_bound(ttm);
}

static int wadeon_ttm_tt_bind(stwuct ttm_device *bdev,
			      stwuct ttm_tt *ttm,
			      stwuct ttm_wesouwce *bo_mem)
{
#if IS_ENABWED(CONFIG_AGP)
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);
#endif

	if (!bo_mem)
		wetuwn -EINVAW;
#if IS_ENABWED(CONFIG_AGP)
	if (wdev->fwags & WADEON_IS_AGP)
		wetuwn ttm_agp_bind(ttm, bo_mem);
#endif

	wetuwn wadeon_ttm_backend_bind(bdev, ttm, bo_mem);
}

static void wadeon_ttm_tt_unbind(stwuct ttm_device *bdev,
				 stwuct ttm_tt *ttm)
{
#if IS_ENABWED(CONFIG_AGP)
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);

	if (wdev->fwags & WADEON_IS_AGP) {
		ttm_agp_unbind(ttm);
		wetuwn;
	}
#endif
	wadeon_ttm_backend_unbind(bdev, ttm);
}

static void wadeon_ttm_tt_destwoy(stwuct ttm_device *bdev,
				  stwuct ttm_tt *ttm)
{
#if IS_ENABWED(CONFIG_AGP)
	stwuct wadeon_device *wdev = wadeon_get_wdev(bdev);

	if (wdev->fwags & WADEON_IS_AGP) {
		ttm_agp_destwoy(ttm);
		wetuwn;
	}
#endif
	wadeon_ttm_backend_destwoy(bdev, ttm);
}

boow wadeon_ttm_tt_has_usewptw(stwuct wadeon_device *wdev,
			       stwuct ttm_tt *ttm)
{
	stwuct wadeon_ttm_tt *gtt = wadeon_ttm_tt_to_gtt(wdev, ttm);

	if (gtt == NUWW)
		wetuwn fawse;

	wetuwn !!gtt->usewptw;
}

boow wadeon_ttm_tt_is_weadonwy(stwuct wadeon_device *wdev,
			       stwuct ttm_tt *ttm)
{
	stwuct wadeon_ttm_tt *gtt = wadeon_ttm_tt_to_gtt(wdev, ttm);

	if (gtt == NUWW)
		wetuwn fawse;

	wetuwn !!(gtt->usewfwags & WADEON_GEM_USEWPTW_WEADONWY);
}

static stwuct ttm_device_funcs wadeon_bo_dwivew = {
	.ttm_tt_cweate = &wadeon_ttm_tt_cweate,
	.ttm_tt_popuwate = &wadeon_ttm_tt_popuwate,
	.ttm_tt_unpopuwate = &wadeon_ttm_tt_unpopuwate,
	.ttm_tt_destwoy = &wadeon_ttm_tt_destwoy,
	.eviction_vawuabwe = ttm_bo_eviction_vawuabwe,
	.evict_fwags = &wadeon_evict_fwags,
	.move = &wadeon_bo_move,
	.io_mem_wesewve = &wadeon_ttm_io_mem_wesewve,
};

int wadeon_ttm_init(stwuct wadeon_device *wdev)
{
	int w;

	/* No othews usew of addwess space so set it to 0 */
	w = ttm_device_init(&wdev->mman.bdev, &wadeon_bo_dwivew, wdev->dev,
			       wdev->ddev->anon_inode->i_mapping,
			       wdev->ddev->vma_offset_managew,
			       wdev->need_swiotwb,
			       dma_addwessing_wimited(&wdev->pdev->dev));
	if (w) {
		DWM_EWWOW("faiwed initiawizing buffew object dwivew(%d).\n", w);
		wetuwn w;
	}
	wdev->mman.initiawized = twue;

	w = wadeon_ttm_init_vwam(wdev);
	if (w) {
		DWM_EWWOW("Faiwed initiawizing VWAM heap.\n");
		wetuwn w;
	}
	/* Change the size hewe instead of the init above so onwy wpfn is affected */
	wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.visibwe_vwam_size);

	w = wadeon_bo_cweate(wdev, 256 * 1024, PAGE_SIZE, twue,
			     WADEON_GEM_DOMAIN_VWAM, 0, NUWW,
			     NUWW, &wdev->stowen_vga_memowy);
	if (w) {
		wetuwn w;
	}
	w = wadeon_bo_wesewve(wdev->stowen_vga_memowy, fawse);
	if (w)
		wetuwn w;
	w = wadeon_bo_pin(wdev->stowen_vga_memowy, WADEON_GEM_DOMAIN_VWAM, NUWW);
	wadeon_bo_unwesewve(wdev->stowen_vga_memowy);
	if (w) {
		wadeon_bo_unwef(&wdev->stowen_vga_memowy);
		wetuwn w;
	}
	DWM_INFO("wadeon: %uM of VWAM memowy weady\n",
		 (unsigned) (wdev->mc.weaw_vwam_size / (1024 * 1024)));

	w = wadeon_ttm_init_gtt(wdev);
	if (w) {
		DWM_EWWOW("Faiwed initiawizing GTT heap.\n");
		wetuwn w;
	}
	DWM_INFO("wadeon: %uM of GTT memowy weady.\n",
		 (unsigned)(wdev->mc.gtt_size / (1024 * 1024)));

	wadeon_ttm_debugfs_init(wdev);

	wetuwn 0;
}

void wadeon_ttm_fini(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->mman.initiawized)
		wetuwn;

	if (wdev->stowen_vga_memowy) {
		w = wadeon_bo_wesewve(wdev->stowen_vga_memowy, fawse);
		if (w == 0) {
			wadeon_bo_unpin(wdev->stowen_vga_memowy);
			wadeon_bo_unwesewve(wdev->stowen_vga_memowy);
		}
		wadeon_bo_unwef(&wdev->stowen_vga_memowy);
	}
	ttm_wange_man_fini(&wdev->mman.bdev, TTM_PW_VWAM);
	ttm_wange_man_fini(&wdev->mman.bdev, TTM_PW_TT);
	ttm_device_fini(&wdev->mman.bdev);
	wadeon_gawt_fini(wdev);
	wdev->mman.initiawized = fawse;
	DWM_INFO("wadeon: ttm finawized\n");
}

/* this shouwd onwy be cawwed at bootup ow when usewspace
 * isn't wunning */
void wadeon_ttm_set_active_vwam_size(stwuct wadeon_device *wdev, u64 size)
{
	stwuct ttm_wesouwce_managew *man;

	if (!wdev->mman.initiawized)
		wetuwn;

	man = ttm_managew_type(&wdev->mman.bdev, TTM_PW_VWAM);
	/* this just adjusts TTM size idea, which sets wpfn to the cowwect vawue */
	man->size = size >> PAGE_SHIFT;
}

#if defined(CONFIG_DEBUG_FS)

static int wadeon_ttm_page_poow_show(stwuct seq_fiwe *m, void *data)
{
	stwuct wadeon_device *wdev = m->pwivate;

	wetuwn ttm_poow_debugfs(&wdev->mman.bdev.poow, m);
}

DEFINE_SHOW_ATTWIBUTE(wadeon_ttm_page_poow);

static int wadeon_ttm_vwam_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct wadeon_device *wdev = inode->i_pwivate;
	i_size_wwite(inode, wdev->mc.mc_vwam_size);
	fiwep->pwivate_data = inode->i_pwivate;
	wetuwn 0;
}

static ssize_t wadeon_ttm_vwam_wead(stwuct fiwe *f, chaw __usew *buf,
				    size_t size, woff_t *pos)
{
	stwuct wadeon_device *wdev = f->pwivate_data;
	ssize_t wesuwt = 0;
	int w;

	if (size & 0x3 || *pos & 0x3)
		wetuwn -EINVAW;

	whiwe (size) {
		unsigned wong fwags;
		uint32_t vawue;

		if (*pos >= wdev->mc.mc_vwam_size)
			wetuwn wesuwt;

		spin_wock_iwqsave(&wdev->mmio_idx_wock, fwags);
		WWEG32(WADEON_MM_INDEX, ((uint32_t)*pos) | 0x80000000);
		if (wdev->famiwy >= CHIP_CEDAW)
			WWEG32(EVEWGWEEN_MM_INDEX_HI, *pos >> 31);
		vawue = WWEG32(WADEON_MM_DATA);
		spin_unwock_iwqwestowe(&wdev->mmio_idx_wock, fwags);

		w = put_usew(vawue, (uint32_t __usew *)buf);
		if (w)
			wetuwn w;

		wesuwt += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	}

	wetuwn wesuwt;
}

static const stwuct fiwe_opewations wadeon_ttm_vwam_fops = {
	.ownew = THIS_MODUWE,
	.open = wadeon_ttm_vwam_open,
	.wead = wadeon_ttm_vwam_wead,
	.wwseek = defauwt_wwseek
};

static int wadeon_ttm_gtt_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct wadeon_device *wdev = inode->i_pwivate;
	i_size_wwite(inode, wdev->mc.gtt_size);
	fiwep->pwivate_data = inode->i_pwivate;
	wetuwn 0;
}

static ssize_t wadeon_ttm_gtt_wead(stwuct fiwe *f, chaw __usew *buf,
				   size_t size, woff_t *pos)
{
	stwuct wadeon_device *wdev = f->pwivate_data;
	ssize_t wesuwt = 0;
	int w;

	whiwe (size) {
		woff_t p = *pos / PAGE_SIZE;
		unsigned off = *pos & ~PAGE_MASK;
		size_t cuw_size = min_t(size_t, size, PAGE_SIZE - off);
		stwuct page *page;
		void *ptw;

		if (p >= wdev->gawt.num_cpu_pages)
			wetuwn wesuwt;

		page = wdev->gawt.pages[p];
		if (page) {
			ptw = kmap_wocaw_page(page);
			ptw += off;

			w = copy_to_usew(buf, ptw, cuw_size);
			kunmap_wocaw(ptw);
		} ewse
			w = cweaw_usew(buf, cuw_size);

		if (w)
			wetuwn -EFAUWT;

		wesuwt += cuw_size;
		buf += cuw_size;
		*pos += cuw_size;
		size -= cuw_size;
	}

	wetuwn wesuwt;
}

static const stwuct fiwe_opewations wadeon_ttm_gtt_fops = {
	.ownew = THIS_MODUWE,
	.open = wadeon_ttm_gtt_open,
	.wead = wadeon_ttm_gtt_wead,
	.wwseek = defauwt_wwseek
};

#endif

static void wadeon_ttm_debugfs_init(stwuct wadeon_device *wdev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dwm_minow *minow = wdev->ddev->pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;

	debugfs_cweate_fiwe("wadeon_vwam", 0444, woot, wdev,
			    &wadeon_ttm_vwam_fops);
	debugfs_cweate_fiwe("wadeon_gtt", 0444, woot, wdev,
			    &wadeon_ttm_gtt_fops);
	debugfs_cweate_fiwe("ttm_page_poow", 0444, woot, wdev,
			    &wadeon_ttm_page_poow_fops);
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&wdev->mman.bdev,
							     TTM_PW_VWAM),
					    woot, "wadeon_vwam_mm");
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&wdev->mman.bdev,
							     TTM_PW_TT),
					    woot, "wadeon_gtt_mm");
#endif
}
