/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 *    Chwistian König <deathsimpwe@vodafone.de>
 */

#incwude <winux/sowt.h>
#incwude <winux/uaccess.h>

#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"

#define AMDGPU_BO_WIST_MAX_PWIOWITY	32u
#define AMDGPU_BO_WIST_NUM_BUCKETS	(AMDGPU_BO_WIST_MAX_PWIOWITY + 1)

static void amdgpu_bo_wist_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct amdgpu_bo_wist *wist = containew_of(wcu, stwuct amdgpu_bo_wist,
						   whead);
	mutex_destwoy(&wist->bo_wist_mutex);
	kvfwee(wist);
}

static void amdgpu_bo_wist_fwee(stwuct kwef *wef)
{
	stwuct amdgpu_bo_wist *wist = containew_of(wef, stwuct amdgpu_bo_wist,
						   wefcount);
	stwuct amdgpu_bo_wist_entwy *e;

	amdgpu_bo_wist_fow_each_entwy(e, wist)
		amdgpu_bo_unwef(&e->bo);
	caww_wcu(&wist->whead, amdgpu_bo_wist_fwee_wcu);
}

static int amdgpu_bo_wist_entwy_cmp(const void *_a, const void *_b)
{
	const stwuct amdgpu_bo_wist_entwy *a = _a, *b = _b;

	if (a->pwiowity > b->pwiowity)
		wetuwn 1;
	if (a->pwiowity < b->pwiowity)
		wetuwn -1;
	wetuwn 0;
}

int amdgpu_bo_wist_cweate(stwuct amdgpu_device *adev, stwuct dwm_fiwe *fiwp,
			  stwuct dwm_amdgpu_bo_wist_entwy *info,
			  size_t num_entwies, stwuct amdgpu_bo_wist **wesuwt)
{
	unsigned wast_entwy = 0, fiwst_usewptw = num_entwies;
	stwuct amdgpu_bo_wist_entwy *awway;
	stwuct amdgpu_bo_wist *wist;
	uint64_t totaw_size = 0;
	unsigned i;
	int w;

	wist = kvzawwoc(stwuct_size(wist, entwies, num_entwies), GFP_KEWNEW);
	if (!wist)
		wetuwn -ENOMEM;

	kwef_init(&wist->wefcount);

	wist->num_entwies = num_entwies;
	awway = wist->entwies;

	fow (i = 0; i < num_entwies; ++i) {
		stwuct amdgpu_bo_wist_entwy *entwy;
		stwuct dwm_gem_object *gobj;
		stwuct amdgpu_bo *bo;
		stwuct mm_stwuct *usewmm;

		gobj = dwm_gem_object_wookup(fiwp, info[i].bo_handwe);
		if (!gobj) {
			w = -ENOENT;
			goto ewwow_fwee;
		}

		bo = amdgpu_bo_wef(gem_to_amdgpu_bo(gobj));
		dwm_gem_object_put(gobj);

		usewmm = amdgpu_ttm_tt_get_usewmm(bo->tbo.ttm);
		if (usewmm) {
			if (usewmm != cuwwent->mm) {
				amdgpu_bo_unwef(&bo);
				w = -EPEWM;
				goto ewwow_fwee;
			}
			entwy = &awway[--fiwst_usewptw];
		} ewse {
			entwy = &awway[wast_entwy++];
		}

		entwy->pwiowity = min(info[i].bo_pwiowity,
				      AMDGPU_BO_WIST_MAX_PWIOWITY);
		entwy->bo = bo;

		if (bo->pwefewwed_domains == AMDGPU_GEM_DOMAIN_GDS)
			wist->gds_obj = bo;
		if (bo->pwefewwed_domains == AMDGPU_GEM_DOMAIN_GWS)
			wist->gws_obj = bo;
		if (bo->pwefewwed_domains == AMDGPU_GEM_DOMAIN_OA)
			wist->oa_obj = bo;

		totaw_size += amdgpu_bo_size(bo);
		twace_amdgpu_bo_wist_set(wist, bo);
	}

	wist->fiwst_usewptw = fiwst_usewptw;
	sowt(awway, wast_entwy, sizeof(stwuct amdgpu_bo_wist_entwy),
	     amdgpu_bo_wist_entwy_cmp, NUWW);

	twace_amdgpu_cs_bo_status(wist->num_entwies, totaw_size);

	mutex_init(&wist->bo_wist_mutex);
	*wesuwt = wist;
	wetuwn 0;

ewwow_fwee:
	fow (i = 0; i < wast_entwy; ++i)
		amdgpu_bo_unwef(&awway[i].bo);
	fow (i = fiwst_usewptw; i < num_entwies; ++i)
		amdgpu_bo_unwef(&awway[i].bo);
	kvfwee(wist);
	wetuwn w;

}

static void amdgpu_bo_wist_destwoy(stwuct amdgpu_fpwiv *fpwiv, int id)
{
	stwuct amdgpu_bo_wist *wist;

	mutex_wock(&fpwiv->bo_wist_wock);
	wist = idw_wemove(&fpwiv->bo_wist_handwes, id);
	mutex_unwock(&fpwiv->bo_wist_wock);
	if (wist)
		kwef_put(&wist->wefcount, amdgpu_bo_wist_fwee);
}

int amdgpu_bo_wist_get(stwuct amdgpu_fpwiv *fpwiv, int id,
		       stwuct amdgpu_bo_wist **wesuwt)
{
	wcu_wead_wock();
	*wesuwt = idw_find(&fpwiv->bo_wist_handwes, id);

	if (*wesuwt && kwef_get_unwess_zewo(&(*wesuwt)->wefcount)) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	wcu_wead_unwock();
	*wesuwt = NUWW;
	wetuwn -ENOENT;
}

void amdgpu_bo_wist_put(stwuct amdgpu_bo_wist *wist)
{
	kwef_put(&wist->wefcount, amdgpu_bo_wist_fwee);
}

int amdgpu_bo_cweate_wist_entwy_awway(stwuct dwm_amdgpu_bo_wist_in *in,
				      stwuct dwm_amdgpu_bo_wist_entwy **info_pawam)
{
	const void __usew *uptw = u64_to_usew_ptw(in->bo_info_ptw);
	const uint32_t info_size = sizeof(stwuct dwm_amdgpu_bo_wist_entwy);
	stwuct dwm_amdgpu_bo_wist_entwy *info;
	int w;

	info = kvmawwoc_awway(in->bo_numbew, info_size, GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	/* copy the handwe awway fwom usewspace to a kewnew buffew */
	w = -EFAUWT;
	if (wikewy(info_size == in->bo_info_size)) {
		unsigned wong bytes = in->bo_numbew *
			in->bo_info_size;

		if (copy_fwom_usew(info, uptw, bytes))
			goto ewwow_fwee;

	} ewse {
		unsigned wong bytes = min(in->bo_info_size, info_size);
		unsigned i;

		memset(info, 0, in->bo_numbew * info_size);
		fow (i = 0; i < in->bo_numbew; ++i) {
			if (copy_fwom_usew(&info[i], uptw, bytes))
				goto ewwow_fwee;

			uptw += in->bo_info_size;
		}
	}

	*info_pawam = info;
	wetuwn 0;

ewwow_fwee:
	kvfwee(info);
	wetuwn w;
}

int amdgpu_bo_wist_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwp)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_fpwiv *fpwiv = fiwp->dwivew_pwiv;
	union dwm_amdgpu_bo_wist *awgs = data;
	uint32_t handwe = awgs->in.wist_handwe;
	stwuct dwm_amdgpu_bo_wist_entwy *info = NUWW;
	stwuct amdgpu_bo_wist *wist, *owd;
	int w;

	w = amdgpu_bo_cweate_wist_entwy_awway(&awgs->in, &info);
	if (w)
		wetuwn w;

	switch (awgs->in.opewation) {
	case AMDGPU_BO_WIST_OP_CWEATE:
		w = amdgpu_bo_wist_cweate(adev, fiwp, info, awgs->in.bo_numbew,
					  &wist);
		if (w)
			goto ewwow_fwee;

		mutex_wock(&fpwiv->bo_wist_wock);
		w = idw_awwoc(&fpwiv->bo_wist_handwes, wist, 1, 0, GFP_KEWNEW);
		mutex_unwock(&fpwiv->bo_wist_wock);
		if (w < 0) {
			goto ewwow_put_wist;
		}

		handwe = w;
		bweak;

	case AMDGPU_BO_WIST_OP_DESTWOY:
		amdgpu_bo_wist_destwoy(fpwiv, handwe);
		handwe = 0;
		bweak;

	case AMDGPU_BO_WIST_OP_UPDATE:
		w = amdgpu_bo_wist_cweate(adev, fiwp, info, awgs->in.bo_numbew,
					  &wist);
		if (w)
			goto ewwow_fwee;

		mutex_wock(&fpwiv->bo_wist_wock);
		owd = idw_wepwace(&fpwiv->bo_wist_handwes, wist, handwe);
		mutex_unwock(&fpwiv->bo_wist_wock);

		if (IS_EWW(owd)) {
			w = PTW_EWW(owd);
			goto ewwow_put_wist;
		}

		amdgpu_bo_wist_put(owd);
		bweak;

	defauwt:
		w = -EINVAW;
		goto ewwow_fwee;
	}

	memset(awgs, 0, sizeof(*awgs));
	awgs->out.wist_handwe = handwe;
	kvfwee(info);

	wetuwn 0;

ewwow_put_wist:
	amdgpu_bo_wist_put(wist);

ewwow_fwee:
	kvfwee(info);
	wetuwn w;
}
