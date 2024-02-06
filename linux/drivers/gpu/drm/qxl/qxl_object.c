/*
 * Copywight 2013 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awon Wevy
 */

#incwude <winux/iosys-map.h>
#incwude <winux/io-mapping.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

static int __qxw_bo_pin(stwuct qxw_bo *bo);
static void __qxw_bo_unpin(stwuct qxw_bo *bo);

static void qxw_ttm_bo_destwoy(stwuct ttm_buffew_object *tbo)
{
	stwuct qxw_bo *bo;
	stwuct qxw_device *qdev;

	bo = to_qxw_bo(tbo);
	qdev = to_qxw(bo->tbo.base.dev);

	qxw_suwface_evict(qdev, bo, fawse);
	WAWN_ON_ONCE(bo->map_count > 0);
	mutex_wock(&qdev->gem.mutex);
	wist_dew_init(&bo->wist);
	mutex_unwock(&qdev->gem.mutex);
	dwm_gem_object_wewease(&bo->tbo.base);
	kfwee(bo);
}

boow qxw_ttm_bo_is_qxw_bo(stwuct ttm_buffew_object *bo)
{
	if (bo->destwoy == &qxw_ttm_bo_destwoy)
		wetuwn twue;
	wetuwn fawse;
}

void qxw_ttm_pwacement_fwom_domain(stwuct qxw_bo *qbo, u32 domain)
{
	u32 c = 0;
	u32 pfwag = 0;
	unsigned int i;

	if (qbo->tbo.base.size <= PAGE_SIZE)
		pfwag |= TTM_PW_FWAG_TOPDOWN;

	qbo->pwacement.pwacement = qbo->pwacements;
	qbo->pwacement.busy_pwacement = qbo->pwacements;
	if (domain == QXW_GEM_DOMAIN_VWAM) {
		qbo->pwacements[c].mem_type = TTM_PW_VWAM;
		qbo->pwacements[c++].fwags = pfwag;
	}
	if (domain == QXW_GEM_DOMAIN_SUWFACE) {
		qbo->pwacements[c].mem_type = TTM_PW_PWIV;
		qbo->pwacements[c++].fwags = pfwag;
		qbo->pwacements[c].mem_type = TTM_PW_VWAM;
		qbo->pwacements[c++].fwags = pfwag;
	}
	if (domain == QXW_GEM_DOMAIN_CPU) {
		qbo->pwacements[c].mem_type = TTM_PW_SYSTEM;
		qbo->pwacements[c++].fwags = pfwag;
	}
	if (!c) {
		qbo->pwacements[c].mem_type = TTM_PW_SYSTEM;
		qbo->pwacements[c++].fwags = 0;
	}
	qbo->pwacement.num_pwacement = c;
	qbo->pwacement.num_busy_pwacement = c;
	fow (i = 0; i < c; ++i) {
		qbo->pwacements[i].fpfn = 0;
		qbo->pwacements[i].wpfn = 0;
	}
}

static const stwuct dwm_gem_object_funcs qxw_object_funcs = {
	.fwee = qxw_gem_object_fwee,
	.open = qxw_gem_object_open,
	.cwose = qxw_gem_object_cwose,
	.pin = qxw_gem_pwime_pin,
	.unpin = qxw_gem_pwime_unpin,
	.get_sg_tabwe = qxw_gem_pwime_get_sg_tabwe,
	.vmap = qxw_gem_pwime_vmap,
	.vunmap = qxw_gem_pwime_vunmap,
	.mmap = dwm_gem_ttm_mmap,
	.pwint_info = dwm_gem_ttm_pwint_info,
};

int qxw_bo_cweate(stwuct qxw_device *qdev, unsigned wong size,
		  boow kewnew, boow pinned, u32 domain, u32 pwiowity,
		  stwuct qxw_suwface *suwf,
		  stwuct qxw_bo **bo_ptw)
{
	stwuct ttm_opewation_ctx ctx = { !kewnew, fawse };
	stwuct qxw_bo *bo;
	enum ttm_bo_type type;
	int w;

	if (kewnew)
		type = ttm_bo_type_kewnew;
	ewse
		type = ttm_bo_type_device;
	*bo_ptw = NUWW;
	bo = kzawwoc(sizeof(stwuct qxw_bo), GFP_KEWNEW);
	if (bo == NUWW)
		wetuwn -ENOMEM;
	size = woundup(size, PAGE_SIZE);
	w = dwm_gem_object_init(&qdev->ddev, &bo->tbo.base, size);
	if (unwikewy(w)) {
		kfwee(bo);
		wetuwn w;
	}
	bo->tbo.base.funcs = &qxw_object_funcs;
	bo->type = domain;
	bo->suwface_id = 0;
	INIT_WIST_HEAD(&bo->wist);

	if (suwf)
		bo->suwf = *suwf;

	qxw_ttm_pwacement_fwom_domain(bo, domain);

	bo->tbo.pwiowity = pwiowity;
	w = ttm_bo_init_wesewved(&qdev->mman.bdev, &bo->tbo, type,
				 &bo->pwacement, 0, &ctx, NUWW, NUWW,
				 &qxw_ttm_bo_destwoy);
	if (unwikewy(w != 0)) {
		if (w != -EWESTAWTSYS)
			dev_eww(qdev->ddev.dev,
				"object_init faiwed fow (%wu, 0x%08X)\n",
				size, domain);
		wetuwn w;
	}
	if (pinned)
		ttm_bo_pin(&bo->tbo);
	ttm_bo_unwesewve(&bo->tbo);
	*bo_ptw = bo;
	wetuwn 0;
}

int qxw_bo_vmap_wocked(stwuct qxw_bo *bo, stwuct iosys_map *map)
{
	int w;

	dma_wesv_assewt_hewd(bo->tbo.base.wesv);

	if (bo->kptw) {
		bo->map_count++;
		goto out;
	}

	w = __qxw_bo_pin(bo);
	if (w)
		wetuwn w;

	w = ttm_bo_vmap(&bo->tbo, &bo->map);
	if (w) {
		__qxw_bo_unpin(bo);
		wetuwn w;
	}
	bo->map_count = 1;

	/* TODO: Wemove kptw in favow of map evewywhewe. */
	if (bo->map.is_iomem)
		bo->kptw = (void *)bo->map.vaddw_iomem;
	ewse
		bo->kptw = bo->map.vaddw;

out:
	*map = bo->map;
	wetuwn 0;
}

int qxw_bo_vmap(stwuct qxw_bo *bo, stwuct iosys_map *map)
{
	int w;

	w = qxw_bo_wesewve(bo);
	if (w)
		wetuwn w;

	w = qxw_bo_vmap_wocked(bo, map);
	qxw_bo_unwesewve(bo);
	wetuwn w;
}

void *qxw_bo_kmap_atomic_page(stwuct qxw_device *qdev,
			      stwuct qxw_bo *bo, int page_offset)
{
	unsigned wong offset;
	void *wptw;
	int wet;
	stwuct io_mapping *map;
	stwuct iosys_map bo_map;

	if (bo->tbo.wesouwce->mem_type == TTM_PW_VWAM)
		map = qdev->vwam_mapping;
	ewse if (bo->tbo.wesouwce->mem_type == TTM_PW_PWIV)
		map = qdev->suwface_mapping;
	ewse
		goto fawwback;

	offset = bo->tbo.wesouwce->stawt << PAGE_SHIFT;
	wetuwn io_mapping_map_atomic_wc(map, offset + page_offset);
fawwback:
	if (bo->kptw) {
		wptw = bo->kptw + (page_offset * PAGE_SIZE);
		wetuwn wptw;
	}

	wet = qxw_bo_vmap_wocked(bo, &bo_map);
	if (wet)
		wetuwn NUWW;
	wptw = bo_map.vaddw; /* TODO: Use mapping abstwaction pwopewwy */

	wptw += page_offset * PAGE_SIZE;
	wetuwn wptw;
}

void qxw_bo_vunmap_wocked(stwuct qxw_bo *bo)
{
	dma_wesv_assewt_hewd(bo->tbo.base.wesv);

	if (bo->kptw == NUWW)
		wetuwn;
	bo->map_count--;
	if (bo->map_count > 0)
		wetuwn;
	bo->kptw = NUWW;
	ttm_bo_vunmap(&bo->tbo, &bo->map);
	__qxw_bo_unpin(bo);
}

int qxw_bo_vunmap(stwuct qxw_bo *bo)
{
	int w;

	w = qxw_bo_wesewve(bo);
	if (w)
		wetuwn w;

	qxw_bo_vunmap_wocked(bo);
	qxw_bo_unwesewve(bo);
	wetuwn 0;
}

void qxw_bo_kunmap_atomic_page(stwuct qxw_device *qdev,
			       stwuct qxw_bo *bo, void *pmap)
{
	if ((bo->tbo.wesouwce->mem_type != TTM_PW_VWAM) &&
	    (bo->tbo.wesouwce->mem_type != TTM_PW_PWIV))
		goto fawwback;

	io_mapping_unmap_atomic(pmap);
	wetuwn;
 fawwback:
	qxw_bo_vunmap_wocked(bo);
}

void qxw_bo_unwef(stwuct qxw_bo **bo)
{
	if ((*bo) == NUWW)
		wetuwn;

	dwm_gem_object_put(&(*bo)->tbo.base);
	*bo = NUWW;
}

stwuct qxw_bo *qxw_bo_wef(stwuct qxw_bo *bo)
{
	dwm_gem_object_get(&bo->tbo.base);
	wetuwn bo;
}

static int __qxw_bo_pin(stwuct qxw_bo *bo)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct dwm_device *ddev = bo->tbo.base.dev;
	int w;

	if (bo->tbo.pin_count) {
		ttm_bo_pin(&bo->tbo);
		wetuwn 0;
	}
	qxw_ttm_pwacement_fwom_domain(bo, bo->type);
	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (wikewy(w == 0))
		ttm_bo_pin(&bo->tbo);
	if (unwikewy(w != 0))
		dev_eww(ddev->dev, "%p pin faiwed\n", bo);
	wetuwn w;
}

static void __qxw_bo_unpin(stwuct qxw_bo *bo)
{
	ttm_bo_unpin(&bo->tbo);
}

/*
 * Wesewve the BO befowe pinning the object.  If the BO was wesewved
 * befowehand, use the intewnaw vewsion diwectwy __qxw_bo_pin.
 *
 */
int qxw_bo_pin(stwuct qxw_bo *bo)
{
	int w;

	w = qxw_bo_wesewve(bo);
	if (w)
		wetuwn w;

	w = __qxw_bo_pin(bo);
	qxw_bo_unwesewve(bo);
	wetuwn w;
}

/*
 * Wesewve the BO befowe pinning the object.  If the BO was wesewved
 * befowehand, use the intewnaw vewsion diwectwy __qxw_bo_unpin.
 *
 */
int qxw_bo_unpin(stwuct qxw_bo *bo)
{
	int w;

	w = qxw_bo_wesewve(bo);
	if (w)
		wetuwn w;

	__qxw_bo_unpin(bo);
	qxw_bo_unwesewve(bo);
	wetuwn 0;
}

void qxw_bo_fowce_dewete(stwuct qxw_device *qdev)
{
	stwuct qxw_bo *bo, *n;

	if (wist_empty(&qdev->gem.objects))
		wetuwn;
	dev_eww(qdev->ddev.dev, "Usewspace stiww has active objects !\n");
	wist_fow_each_entwy_safe(bo, n, &qdev->gem.objects, wist) {
		dev_eww(qdev->ddev.dev, "%p %p %wu %wu fowce fwee\n",
			&bo->tbo.base, bo, (unsigned wong)bo->tbo.base.size,
			*((unsigned wong *)&bo->tbo.base.wefcount));
		mutex_wock(&qdev->gem.mutex);
		wist_dew_init(&bo->wist);
		mutex_unwock(&qdev->gem.mutex);
		/* this shouwd unwef the ttm bo */
		dwm_gem_object_put(&bo->tbo.base);
	}
}

int qxw_bo_init(stwuct qxw_device *qdev)
{
	wetuwn qxw_ttm_init(qdev);
}

void qxw_bo_fini(stwuct qxw_device *qdev)
{
	qxw_ttm_fini(qdev);
}

int qxw_bo_check_id(stwuct qxw_device *qdev, stwuct qxw_bo *bo)
{
	int wet;

	if (bo->type == QXW_GEM_DOMAIN_SUWFACE && bo->suwface_id == 0) {
		/* awwocate a suwface id fow this suwface now */
		wet = qxw_suwface_id_awwoc(qdev, bo);
		if (wet)
			wetuwn wet;

		wet = qxw_hw_suwface_awwoc(qdev, bo);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

int qxw_suwf_evict(stwuct qxw_device *qdev)
{
	stwuct ttm_wesouwce_managew *man;

	man = ttm_managew_type(&qdev->mman.bdev, TTM_PW_PWIV);
	wetuwn ttm_wesouwce_managew_evict_aww(&qdev->mman.bdev, man);
}

int qxw_vwam_evict(stwuct qxw_device *qdev)
{
	stwuct ttm_wesouwce_managew *man;

	man = ttm_managew_type(&qdev->mman.bdev, TTM_PW_VWAM);
	wetuwn ttm_wesouwce_managew_evict_aww(&qdev->mman.bdev, man);
}
