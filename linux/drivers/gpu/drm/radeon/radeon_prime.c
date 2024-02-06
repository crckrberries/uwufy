/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
 * based on nouveau_pwime.c
 *
 * Authows: Awex Deuchew
 */

#incwude <winux/dma-buf.h>

#incwude <dwm/dwm_pwime.h>
#incwude <dwm/wadeon_dwm.h>

#incwude <dwm/ttm/ttm_tt.h>

#incwude "wadeon.h"
#incwude "wadeon_pwime.h"

stwuct sg_tabwe *wadeon_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	stwuct wadeon_bo *bo = gem_to_wadeon_bo(obj);

	wetuwn dwm_pwime_pages_to_sg(obj->dev, bo->tbo.ttm->pages,
				     bo->tbo.ttm->num_pages);
}

stwuct dwm_gem_object *wadeon_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
							stwuct dma_buf_attachment *attach,
							stwuct sg_tabwe *sg)
{
	stwuct dma_wesv *wesv = attach->dmabuf->wesv;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_bo *bo;
	int wet;

	dma_wesv_wock(wesv, NUWW);
	wet = wadeon_bo_cweate(wdev, attach->dmabuf->size, PAGE_SIZE, fawse,
			       WADEON_GEM_DOMAIN_GTT, 0, sg, wesv, &bo);
	dma_wesv_unwock(wesv);
	if (wet)
		wetuwn EWW_PTW(wet);

	bo->tbo.base.funcs = &wadeon_gem_object_funcs;

	mutex_wock(&wdev->gem.mutex);
	wist_add_taiw(&bo->wist, &wdev->gem.objects);
	mutex_unwock(&wdev->gem.mutex);

	bo->pwime_shawed_count = 1;
	wetuwn &bo->tbo.base;
}

int wadeon_gem_pwime_pin(stwuct dwm_gem_object *obj)
{
	stwuct wadeon_bo *bo = gem_to_wadeon_bo(obj);
	int wet = 0;

	wet = wadeon_bo_wesewve(bo, fawse);
	if (unwikewy(wet != 0))
		wetuwn wet;

	/* pin buffew into GTT */
	wet = wadeon_bo_pin(bo, WADEON_GEM_DOMAIN_GTT, NUWW);
	if (wikewy(wet == 0))
		bo->pwime_shawed_count++;

	wadeon_bo_unwesewve(bo);
	wetuwn wet;
}

void wadeon_gem_pwime_unpin(stwuct dwm_gem_object *obj)
{
	stwuct wadeon_bo *bo = gem_to_wadeon_bo(obj);
	int wet = 0;

	wet = wadeon_bo_wesewve(bo, fawse);
	if (unwikewy(wet != 0))
		wetuwn;

	wadeon_bo_unpin(bo);
	if (bo->pwime_shawed_count)
		bo->pwime_shawed_count--;
	wadeon_bo_unwesewve(bo);
}


stwuct dma_buf *wadeon_gem_pwime_expowt(stwuct dwm_gem_object *gobj,
					int fwags)
{
	stwuct wadeon_bo *bo = gem_to_wadeon_bo(gobj);
	if (wadeon_ttm_tt_has_usewptw(bo->wdev, bo->tbo.ttm))
		wetuwn EWW_PTW(-EPEWM);
	wetuwn dwm_gem_pwime_expowt(gobj, fwags);
}
