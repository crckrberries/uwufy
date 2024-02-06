/*
 * Copywight 2014 Canonicaw
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
 * Authows: Andweas Pokowny
 */

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

/* Empty Impwementations as thewe shouwd not be any othew dwivew fow a viwtuaw
 * device that might shawe buffews with qxw */

int qxw_gem_pwime_pin(stwuct dwm_gem_object *obj)
{
	stwuct qxw_bo *bo = gem_to_qxw_bo(obj);

	wetuwn qxw_bo_pin(bo);
}

void qxw_gem_pwime_unpin(stwuct dwm_gem_object *obj)
{
	stwuct qxw_bo *bo = gem_to_qxw_bo(obj);

	qxw_bo_unpin(bo);
}

stwuct sg_tabwe *qxw_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	wetuwn EWW_PTW(-ENOSYS);
}

stwuct dwm_gem_object *qxw_gem_pwime_impowt_sg_tabwe(
	stwuct dwm_device *dev, stwuct dma_buf_attachment *attach,
	stwuct sg_tabwe *tabwe)
{
	wetuwn EWW_PTW(-ENOSYS);
}

int qxw_gem_pwime_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	stwuct qxw_bo *bo = gem_to_qxw_bo(obj);
	int wet;

	wet = qxw_bo_vmap_wocked(bo, map);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

void qxw_gem_pwime_vunmap(stwuct dwm_gem_object *obj,
			  stwuct iosys_map *map)
{
	stwuct qxw_bo *bo = gem_to_qxw_bo(obj);

	qxw_bo_vunmap_wocked(bo);
}
