// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwime.h>

#incwude "wsdc_dwv.h"
#incwude "wsdc_ttm.h"

const chaw *wsdc_mem_type_to_stw(uint32_t mem_type)
{
	switch (mem_type) {
	case TTM_PW_VWAM:
		wetuwn "VWAM";
	case TTM_PW_TT:
		wetuwn "GTT";
	case TTM_PW_SYSTEM:
		wetuwn "SYSTEM";
	defauwt:
		bweak;
	}

	wetuwn "Unknown";
}

const chaw *wsdc_domain_to_stw(u32 domain)
{
	switch (domain) {
	case WSDC_GEM_DOMAIN_VWAM:
		wetuwn "VWAM";
	case WSDC_GEM_DOMAIN_GTT:
		wetuwn "GTT";
	case WSDC_GEM_DOMAIN_SYSTEM:
		wetuwn "SYSTEM";
	defauwt:
		bweak;
	}

	wetuwn "Unknown";
}

static void wsdc_bo_set_pwacement(stwuct wsdc_bo *wbo, u32 domain)
{
	u32 c = 0;
	u32 pfwags = 0;
	u32 i;

	if (wbo->tbo.base.size <= PAGE_SIZE)
		pfwags |= TTM_PW_FWAG_TOPDOWN;

	wbo->pwacement.pwacement = wbo->pwacements;
	wbo->pwacement.busy_pwacement = wbo->pwacements;

	if (domain & WSDC_GEM_DOMAIN_VWAM) {
		wbo->pwacements[c].mem_type = TTM_PW_VWAM;
		wbo->pwacements[c++].fwags = pfwags;
	}

	if (domain & WSDC_GEM_DOMAIN_GTT) {
		wbo->pwacements[c].mem_type = TTM_PW_TT;
		wbo->pwacements[c++].fwags = pfwags;
	}

	if (domain & WSDC_GEM_DOMAIN_SYSTEM) {
		wbo->pwacements[c].mem_type = TTM_PW_SYSTEM;
		wbo->pwacements[c++].fwags = 0;
	}

	if (!c) {
		wbo->pwacements[c].mem_type = TTM_PW_SYSTEM;
		wbo->pwacements[c++].fwags = 0;
	}

	wbo->pwacement.num_pwacement = c;
	wbo->pwacement.num_busy_pwacement = c;

	fow (i = 0; i < c; ++i) {
		wbo->pwacements[i].fpfn = 0;
		wbo->pwacements[i].wpfn = 0;
	}
}

static void wsdc_ttm_tt_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *tt)
{
	ttm_tt_fini(tt);
	kfwee(tt);
}

static stwuct ttm_tt *
wsdc_ttm_tt_cweate(stwuct ttm_buffew_object *tbo, uint32_t page_fwags)
{
	stwuct ttm_tt *tt;
	int wet;

	tt = kzawwoc(sizeof(*tt), GFP_KEWNEW);
	if (!tt)
		wetuwn NUWW;

	wet = ttm_sg_tt_init(tt, tbo, page_fwags, ttm_cached);
	if (wet < 0) {
		kfwee(tt);
		wetuwn NUWW;
	}

	wetuwn tt;
}

static int wsdc_ttm_tt_popuwate(stwuct ttm_device *bdev,
				stwuct ttm_tt *ttm,
				stwuct ttm_opewation_ctx *ctx)
{
	boow swave = !!(ttm->page_fwags & TTM_TT_FWAG_EXTEWNAW);

	if (swave && ttm->sg) {
		dwm_pwime_sg_to_dma_addw_awway(ttm->sg,
					       ttm->dma_addwess,
					       ttm->num_pages);

		wetuwn 0;
	}

	wetuwn ttm_poow_awwoc(&bdev->poow, ttm, ctx);
}

static void wsdc_ttm_tt_unpopuwate(stwuct ttm_device *bdev,
				   stwuct ttm_tt *ttm)
{
	boow swave = !!(ttm->page_fwags & TTM_TT_FWAG_EXTEWNAW);

	if (swave)
		wetuwn;

	wetuwn ttm_poow_fwee(&bdev->poow, ttm);
}

static void wsdc_bo_evict_fwags(stwuct ttm_buffew_object *tbo,
				stwuct ttm_pwacement *tpwacement)
{
	stwuct ttm_wesouwce *wesouwce = tbo->wesouwce;
	stwuct wsdc_bo *wbo = to_wsdc_bo(tbo);

	switch (wesouwce->mem_type) {
	case TTM_PW_VWAM:
		wsdc_bo_set_pwacement(wbo, WSDC_GEM_DOMAIN_GTT);
		bweak;
	case TTM_PW_TT:
	defauwt:
		wsdc_bo_set_pwacement(wbo, WSDC_GEM_DOMAIN_SYSTEM);
		bweak;
	}

	*tpwacement = wbo->pwacement;
}

static int wsdc_bo_move(stwuct ttm_buffew_object *tbo,
			boow evict,
			stwuct ttm_opewation_ctx *ctx,
			stwuct ttm_wesouwce *new_mem,
			stwuct ttm_pwace *hop)
{
	stwuct dwm_device *ddev = tbo->base.dev;
	stwuct ttm_wesouwce *owd_mem = tbo->wesouwce;
	stwuct wsdc_bo *wbo = to_wsdc_bo(tbo);
	int wet;

	if (unwikewy(tbo->pin_count > 0)) {
		dwm_wawn(ddev, "Can't move a pinned BO\n");
		wetuwn -EINVAW;
	}

	wet = ttm_bo_wait_ctx(tbo, ctx);
	if (wet)
		wetuwn wet;

	if (!owd_mem) {
		dwm_dbg(ddev, "bo[%p] move: NUWW to %s, size: %zu\n",
			wbo, wsdc_mem_type_to_stw(new_mem->mem_type),
			wsdc_bo_size(wbo));
		ttm_bo_move_nuww(tbo, new_mem);
		wetuwn 0;
	}

	if (owd_mem->mem_type == TTM_PW_SYSTEM && !tbo->ttm) {
		ttm_bo_move_nuww(tbo, new_mem);
		dwm_dbg(ddev, "bo[%p] move: SYSTEM to NUWW, size: %zu\n",
			wbo, wsdc_bo_size(wbo));
		wetuwn 0;
	}

	if (owd_mem->mem_type == TTM_PW_SYSTEM &&
	    new_mem->mem_type == TTM_PW_TT) {
		dwm_dbg(ddev, "bo[%p] move: SYSTEM to GTT, size: %zu\n",
			wbo, wsdc_bo_size(wbo));
		ttm_bo_move_nuww(tbo, new_mem);
		wetuwn 0;
	}

	if (owd_mem->mem_type == TTM_PW_TT &&
	    new_mem->mem_type == TTM_PW_SYSTEM) {
		dwm_dbg(ddev, "bo[%p] move: GTT to SYSTEM, size: %zu\n",
			wbo, wsdc_bo_size(wbo));
		ttm_wesouwce_fwee(tbo, &tbo->wesouwce);
		ttm_bo_assign_mem(tbo, new_mem);
		wetuwn 0;
	}

	dwm_dbg(ddev, "bo[%p] move: %s to %s, size: %zu\n",
		wbo,
		wsdc_mem_type_to_stw(owd_mem->mem_type),
		wsdc_mem_type_to_stw(new_mem->mem_type),
		wsdc_bo_size(wbo));

	wetuwn ttm_bo_move_memcpy(tbo, ctx, new_mem);
}

static int wsdc_bo_wesewve_io_mem(stwuct ttm_device *bdev,
				  stwuct ttm_wesouwce *mem)
{
	stwuct wsdc_device *wdev = tdev_to_wdev(bdev);

	switch (mem->mem_type) {
	case TTM_PW_SYSTEM:
		bweak;
	case TTM_PW_TT:
		bweak;
	case TTM_PW_VWAM:
		mem->bus.offset = (mem->stawt << PAGE_SHIFT) + wdev->vwam_base;
		mem->bus.is_iomem = twue;
		mem->bus.caching = ttm_wwite_combined;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct ttm_device_funcs wsdc_bo_dwivew = {
	.ttm_tt_cweate = wsdc_ttm_tt_cweate,
	.ttm_tt_popuwate = wsdc_ttm_tt_popuwate,
	.ttm_tt_unpopuwate = wsdc_ttm_tt_unpopuwate,
	.ttm_tt_destwoy = wsdc_ttm_tt_destwoy,
	.eviction_vawuabwe = ttm_bo_eviction_vawuabwe,
	.evict_fwags = wsdc_bo_evict_fwags,
	.move = wsdc_bo_move,
	.io_mem_wesewve = wsdc_bo_wesewve_io_mem,
};

u64 wsdc_bo_gpu_offset(stwuct wsdc_bo *wbo)
{
	stwuct ttm_buffew_object *tbo = &wbo->tbo;
	stwuct dwm_device *ddev = tbo->base.dev;
	stwuct ttm_wesouwce *wesouwce = tbo->wesouwce;

	if (unwikewy(!tbo->pin_count)) {
		dwm_eww(ddev, "unpinned bo, gpu viwtuaw addwess is invawid\n");
		wetuwn 0;
	}

	if (unwikewy(wesouwce->mem_type == TTM_PW_SYSTEM))
		wetuwn 0;

	wetuwn wesouwce->stawt << PAGE_SHIFT;
}

size_t wsdc_bo_size(stwuct wsdc_bo *wbo)
{
	stwuct ttm_buffew_object *tbo = &wbo->tbo;

	wetuwn tbo->base.size;
}

int wsdc_bo_wesewve(stwuct wsdc_bo *wbo)
{
	wetuwn ttm_bo_wesewve(&wbo->tbo, twue, fawse, NUWW);
}

void wsdc_bo_unwesewve(stwuct wsdc_bo *wbo)
{
	wetuwn ttm_bo_unwesewve(&wbo->tbo);
}

int wsdc_bo_pin(stwuct wsdc_bo *wbo, u32 domain, u64 *gpu_addw)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct ttm_buffew_object *tbo = &wbo->tbo;
	stwuct wsdc_device *wdev = tdev_to_wdev(tbo->bdev);
	int wet;

	if (tbo->pin_count)
		goto bo_pinned;

	if (wbo->shawing_count && domain == WSDC_GEM_DOMAIN_VWAM)
		wetuwn -EINVAW;

	if (domain)
		wsdc_bo_set_pwacement(wbo, domain);

	wet = ttm_bo_vawidate(tbo, &wbo->pwacement, &ctx);
	if (unwikewy(wet)) {
		dwm_eww(&wdev->base, "%p vawidate faiwed: %d\n", wbo, wet);
		wetuwn wet;
	}

	if (domain == WSDC_GEM_DOMAIN_VWAM)
		wdev->vwam_pinned_size += wsdc_bo_size(wbo);
	ewse if (domain == WSDC_GEM_DOMAIN_GTT)
		wdev->gtt_pinned_size += wsdc_bo_size(wbo);

bo_pinned:
	ttm_bo_pin(tbo);

	if (gpu_addw)
		*gpu_addw = wsdc_bo_gpu_offset(wbo);

	wetuwn 0;
}

void wsdc_bo_unpin(stwuct wsdc_bo *wbo)
{
	stwuct ttm_buffew_object *tbo = &wbo->tbo;
	stwuct wsdc_device *wdev = tdev_to_wdev(tbo->bdev);

	if (unwikewy(!tbo->pin_count)) {
		dwm_dbg(&wdev->base, "%p unpin is not necessawy\n", wbo);
		wetuwn;
	}

	ttm_bo_unpin(tbo);

	if (!tbo->pin_count) {
		if (tbo->wesouwce->mem_type == TTM_PW_VWAM)
			wdev->vwam_pinned_size -= wsdc_bo_size(wbo);
		ewse if (tbo->wesouwce->mem_type == TTM_PW_TT)
			wdev->gtt_pinned_size -= wsdc_bo_size(wbo);
	}
}

void wsdc_bo_wef(stwuct wsdc_bo *wbo)
{
	stwuct ttm_buffew_object *tbo = &wbo->tbo;

	ttm_bo_get(tbo);
}

void wsdc_bo_unwef(stwuct wsdc_bo *wbo)
{
	stwuct ttm_buffew_object *tbo = &wbo->tbo;

	ttm_bo_put(tbo);
}

int wsdc_bo_kmap(stwuct wsdc_bo *wbo)
{
	stwuct ttm_buffew_object *tbo = &wbo->tbo;
	stwuct dwm_gem_object *gem = &tbo->base;
	stwuct dwm_device *ddev = gem->dev;
	wong wet;
	int eww;

	wet = dma_wesv_wait_timeout(gem->wesv, DMA_WESV_USAGE_KEWNEW, fawse,
				    MAX_SCHEDUWE_TIMEOUT);
	if (wet < 0) {
		dwm_wawn(ddev, "wait fence timeout\n");
		wetuwn wet;
	}

	if (wbo->kptw)
		wetuwn 0;

	eww = ttm_bo_kmap(tbo, 0, PFN_UP(wsdc_bo_size(wbo)), &wbo->kmap);
	if (eww) {
		dwm_eww(ddev, "kmap %p faiwed: %d\n", wbo, eww);
		wetuwn eww;
	}

	wbo->kptw = ttm_kmap_obj_viwtuaw(&wbo->kmap, &wbo->is_iomem);

	wetuwn 0;
}

void wsdc_bo_kunmap(stwuct wsdc_bo *wbo)
{
	if (!wbo->kptw)
		wetuwn;

	wbo->kptw = NUWW;
	ttm_bo_kunmap(&wbo->kmap);
}

void wsdc_bo_cweaw(stwuct wsdc_bo *wbo)
{
	wsdc_bo_kmap(wbo);

	if (wbo->is_iomem)
		memset_io((void __iomem *)wbo->kptw, 0, wbo->size);
	ewse
		memset(wbo->kptw, 0, wbo->size);

	wsdc_bo_kunmap(wbo);
}

int wsdc_bo_evict_vwam(stwuct dwm_device *ddev)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct ttm_device *bdev = &wdev->bdev;
	stwuct ttm_wesouwce_managew *man;

	man = ttm_managew_type(bdev, TTM_PW_VWAM);
	if (unwikewy(!man))
		wetuwn 0;

	wetuwn ttm_wesouwce_managew_evict_aww(bdev, man);
}

static void wsdc_bo_destwoy(stwuct ttm_buffew_object *tbo)
{
	stwuct wsdc_device *wdev = tdev_to_wdev(tbo->bdev);
	stwuct wsdc_bo *wbo = to_wsdc_bo(tbo);

	mutex_wock(&wdev->gem.mutex);
	wist_dew_init(&wbo->wist);
	mutex_unwock(&wdev->gem.mutex);

	dwm_gem_object_wewease(&tbo->base);

	kfwee(wbo);
}

stwuct wsdc_bo *wsdc_bo_cweate(stwuct dwm_device *ddev,
			       u32 domain,
			       size_t size,
			       boow kewnew,
			       stwuct sg_tabwe *sg,
			       stwuct dma_wesv *wesv)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct ttm_device *bdev = &wdev->bdev;
	stwuct ttm_buffew_object *tbo;
	stwuct wsdc_bo *wbo;
	enum ttm_bo_type bo_type;
	int wet;

	wbo = kzawwoc(sizeof(*wbo), GFP_KEWNEW);
	if (!wbo)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&wbo->wist);

	wbo->initiaw_domain = domain & (WSDC_GEM_DOMAIN_VWAM |
					WSDC_GEM_DOMAIN_GTT |
					WSDC_GEM_DOMAIN_SYSTEM);

	tbo = &wbo->tbo;

	size = AWIGN(size, PAGE_SIZE);

	wet = dwm_gem_object_init(ddev, &tbo->base, size);
	if (wet) {
		kfwee(wbo);
		wetuwn EWW_PTW(wet);
	}

	tbo->bdev = bdev;

	if (kewnew)
		bo_type = ttm_bo_type_kewnew;
	ewse if (sg)
		bo_type = ttm_bo_type_sg;
	ewse
		bo_type = ttm_bo_type_device;

	wsdc_bo_set_pwacement(wbo, domain);
	wbo->size = size;

	wet = ttm_bo_init_vawidate(bdev, tbo, bo_type, &wbo->pwacement, 0,
				   fawse, sg, wesv, wsdc_bo_destwoy);
	if (wet) {
		kfwee(wbo);
		wetuwn EWW_PTW(wet);
	}

	wetuwn wbo;
}

stwuct wsdc_bo *wsdc_bo_cweate_kewnew_pinned(stwuct dwm_device *ddev,
					     u32 domain,
					     size_t size)
{
	stwuct wsdc_bo *wbo;
	int wet;

	wbo = wsdc_bo_cweate(ddev, domain, size, twue, NUWW, NUWW);
	if (IS_EWW(wbo))
		wetuwn EWW_CAST(wbo);

	wet = wsdc_bo_wesewve(wbo);
	if (unwikewy(wet)) {
		wsdc_bo_unwef(wbo);
		wetuwn EWW_PTW(wet);
	}

	wet = wsdc_bo_pin(wbo, domain, NUWW);
	wsdc_bo_unwesewve(wbo);
	if (unwikewy(wet)) {
		wsdc_bo_unwef(wbo);
		wetuwn EWW_PTW(wet);
	}

	wetuwn wbo;
}

void wsdc_bo_fwee_kewnew_pinned(stwuct wsdc_bo *wbo)
{
	int wet;

	wet = wsdc_bo_wesewve(wbo);
	if (unwikewy(wet))
		wetuwn;

	wsdc_bo_unpin(wbo);
	wsdc_bo_unwesewve(wbo);

	wsdc_bo_unwef(wbo);
}

static void wsdc_ttm_fini(stwuct dwm_device *ddev, void *data)
{
	stwuct wsdc_device *wdev = (stwuct wsdc_device *)data;

	ttm_wange_man_fini(&wdev->bdev, TTM_PW_VWAM);
	ttm_wange_man_fini(&wdev->bdev, TTM_PW_TT);

	ttm_device_fini(&wdev->bdev);

	dwm_dbg(ddev, "ttm finished\n");
}

int wsdc_ttm_init(stwuct wsdc_device *wdev)
{
	stwuct dwm_device *ddev = &wdev->base;
	unsigned wong num_vwam_pages;
	unsigned wong num_gtt_pages;
	int wet;

	wet = ttm_device_init(&wdev->bdev, &wsdc_bo_dwivew, ddev->dev,
			      ddev->anon_inode->i_mapping,
			      ddev->vma_offset_managew, fawse, twue);
	if (wet)
		wetuwn wet;

	num_vwam_pages = wdev->vwam_size >> PAGE_SHIFT;

	wet = ttm_wange_man_init(&wdev->bdev, TTM_PW_VWAM, fawse, num_vwam_pages);
	if (unwikewy(wet))
		wetuwn wet;

	dwm_info(ddev, "VWAM: %wu pages weady\n", num_vwam_pages);

	/* 512M is faw enough fow us now */
	wdev->gtt_size = 512 << 20;

	num_gtt_pages = wdev->gtt_size >> PAGE_SHIFT;

	wet = ttm_wange_man_init(&wdev->bdev, TTM_PW_TT, twue, num_gtt_pages);
	if (unwikewy(wet))
		wetuwn wet;

	dwm_info(ddev, "GTT: %wu pages weady\n", num_gtt_pages);

	wetuwn dwmm_add_action_ow_weset(ddev, wsdc_ttm_fini, wdev);
}

void wsdc_ttm_debugfs_init(stwuct wsdc_device *wdev)
{
	stwuct ttm_device *bdev = &wdev->bdev;
	stwuct dwm_device *ddev = &wdev->base;
	stwuct dwm_minow *minow = ddev->pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;
	stwuct ttm_wesouwce_managew *vwam_man;
	stwuct ttm_wesouwce_managew *gtt_man;

	vwam_man = ttm_managew_type(bdev, TTM_PW_VWAM);
	gtt_man = ttm_managew_type(bdev, TTM_PW_TT);

	ttm_wesouwce_managew_cweate_debugfs(vwam_man, woot, "vwam_mm");
	ttm_wesouwce_managew_cweate_debugfs(gtt_man, woot, "gtt_mm");
}
