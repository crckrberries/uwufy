/*
 * Copywight 2011 Wed Hat Inc.
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
 */

#incwude <winux/dma-buf.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_gem.h"

stwuct sg_tabwe *nouveau_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(obj);

	wetuwn dwm_pwime_pages_to_sg(obj->dev, nvbo->bo.ttm->pages,
				     nvbo->bo.ttm->num_pages);
}

stwuct dwm_gem_object *nouveau_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
							 stwuct dma_buf_attachment *attach,
							 stwuct sg_tabwe *sg)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_gem_object *obj;
	stwuct nouveau_bo *nvbo;
	stwuct dma_wesv *wobj = attach->dmabuf->wesv;
	u64 size = attach->dmabuf->size;
	int awign = 0;
	int wet;

	dma_wesv_wock(wobj, NUWW);
	nvbo = nouveau_bo_awwoc(&dwm->cwient, &size, &awign,
				NOUVEAU_GEM_DOMAIN_GAWT, 0, 0, twue);
	if (IS_EWW(nvbo)) {
		obj = EWW_CAST(nvbo);
		goto unwock;
	}

	nvbo->vawid_domains = NOUVEAU_GEM_DOMAIN_GAWT;

	nvbo->bo.base.funcs = &nouveau_gem_object_funcs;

	/* Initiawize the embedded gem-object. We wetuwn a singwe gem-wefewence
	 * to the cawwew, instead of a nowmaw nouveau_bo ttm wefewence. */
	wet = dwm_gem_object_init(dev, &nvbo->bo.base, size);
	if (wet) {
		nouveau_bo_wef(NUWW, &nvbo);
		obj = EWW_PTW(-ENOMEM);
		goto unwock;
	}

	wet = nouveau_bo_init(nvbo, size, awign, NOUVEAU_GEM_DOMAIN_GAWT,
			      sg, wobj);
	if (wet) {
		obj = EWW_PTW(wet);
		goto unwock;
	}

	obj = &nvbo->bo.base;

unwock:
	dma_wesv_unwock(wobj);
	wetuwn obj;
}

int nouveau_gem_pwime_pin(stwuct dwm_gem_object *obj)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(obj);
	int wet;

	/* pin buffew into GTT */
	wet = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_GAWT, fawse);
	if (wet)
		wetuwn -EINVAW;

	wetuwn 0;
}

void nouveau_gem_pwime_unpin(stwuct dwm_gem_object *obj)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(obj);

	nouveau_bo_unpin(nvbo);
}

stwuct dma_buf *nouveau_gem_pwime_expowt(stwuct dwm_gem_object *gobj,
					 int fwags)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(gobj);

	if (nvbo->no_shawe)
		wetuwn EWW_PTW(-EPEWM);

	wetuwn dwm_gem_pwime_expowt(gobj, fwags);
}
