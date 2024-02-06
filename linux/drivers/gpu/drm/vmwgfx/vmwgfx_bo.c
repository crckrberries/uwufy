// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight © 2011-2023 VMwawe, Inc., Pawo Awto, CA., USA
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
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"


#incwude <dwm/ttm/ttm_pwacement.h>

static void vmw_bo_wewease(stwuct vmw_bo *vbo)
{
	WAWN_ON(vbo->tbo.base.funcs &&
		kwef_wead(&vbo->tbo.base.wefcount) != 0);
	vmw_bo_unmap(vbo);
	dwm_gem_object_wewease(&vbo->tbo.base);
}

/**
 * vmw_bo_fwee - vmw_bo destwuctow
 *
 * @bo: Pointew to the embedded stwuct ttm_buffew_object
 */
static void vmw_bo_fwee(stwuct ttm_buffew_object *bo)
{
	stwuct vmw_bo *vbo = to_vmw_bo(&bo->base);

	WAWN_ON(vbo->diwty);
	WAWN_ON(!WB_EMPTY_WOOT(&vbo->wes_twee));
	vmw_bo_wewease(vbo);
	kfwee(vbo);
}

/**
 * vmw_bo_pin_in_pwacement - Vawidate a buffew to pwacement.
 *
 * @dev_pwiv:  Dwivew pwivate.
 * @buf:  DMA buffew to move.
 * @pwacement:  The pwacement to pin it.
 * @intewwuptibwe:  Use intewwuptibwe wait.
 * Wetuwn: Zewo on success, Negative ewwow code on faiwuwe. In pawticuwaw
 * -EWESTAWTSYS if intewwupted by a signaw
 */
static int vmw_bo_pin_in_pwacement(stwuct vmw_pwivate *dev_pwiv,
				   stwuct vmw_bo *buf,
				   stwuct ttm_pwacement *pwacement,
				   boow intewwuptibwe)
{
	stwuct ttm_opewation_ctx ctx = {intewwuptibwe, fawse };
	stwuct ttm_buffew_object *bo = &buf->tbo;
	int wet;

	vmw_execbuf_wewease_pinned_bo(dev_pwiv);

	wet = ttm_bo_wesewve(bo, intewwuptibwe, fawse, NUWW);
	if (unwikewy(wet != 0))
		goto eww;

	wet = ttm_bo_vawidate(bo, pwacement, &ctx);
	if (!wet)
		vmw_bo_pin_wesewved(buf, twue);

	ttm_bo_unwesewve(bo);
eww:
	wetuwn wet;
}


/**
 * vmw_bo_pin_in_vwam_ow_gmw - Move a buffew to vwam ow gmw.
 *
 * This function takes the wesewvation_sem in wwite mode.
 * Fwushes and unpins the quewy bo to avoid faiwuwes.
 *
 * @dev_pwiv:  Dwivew pwivate.
 * @buf:  DMA buffew to move.
 * @intewwuptibwe:  Use intewwuptibwe wait.
 * Wetuwn: Zewo on success, Negative ewwow code on faiwuwe. In pawticuwaw
 * -EWESTAWTSYS if intewwupted by a signaw
 */
int vmw_bo_pin_in_vwam_ow_gmw(stwuct vmw_pwivate *dev_pwiv,
			      stwuct vmw_bo *buf,
			      boow intewwuptibwe)
{
	stwuct ttm_opewation_ctx ctx = {intewwuptibwe, fawse };
	stwuct ttm_buffew_object *bo = &buf->tbo;
	int wet;

	vmw_execbuf_wewease_pinned_bo(dev_pwiv);

	wet = ttm_bo_wesewve(bo, intewwuptibwe, fawse, NUWW);
	if (unwikewy(wet != 0))
		goto eww;

	vmw_bo_pwacement_set(buf,
			     VMW_BO_DOMAIN_GMW | VMW_BO_DOMAIN_VWAM,
			     VMW_BO_DOMAIN_GMW);
	wet = ttm_bo_vawidate(bo, &buf->pwacement, &ctx);
	if (wikewy(wet == 0) || wet == -EWESTAWTSYS)
		goto out_unwesewve;

	vmw_bo_pwacement_set(buf,
			     VMW_BO_DOMAIN_VWAM,
			     VMW_BO_DOMAIN_VWAM);
	wet = ttm_bo_vawidate(bo, &buf->pwacement, &ctx);

out_unwesewve:
	if (!wet)
		vmw_bo_pin_wesewved(buf, twue);

	ttm_bo_unwesewve(bo);
eww:
	wetuwn wet;
}


/**
 * vmw_bo_pin_in_vwam - Move a buffew to vwam.
 *
 * This function takes the wesewvation_sem in wwite mode.
 * Fwushes and unpins the quewy bo to avoid faiwuwes.
 *
 * @dev_pwiv:  Dwivew pwivate.
 * @buf:  DMA buffew to move.
 * @intewwuptibwe:  Use intewwuptibwe wait.
 * Wetuwn: Zewo on success, Negative ewwow code on faiwuwe. In pawticuwaw
 * -EWESTAWTSYS if intewwupted by a signaw
 */
int vmw_bo_pin_in_vwam(stwuct vmw_pwivate *dev_pwiv,
		       stwuct vmw_bo *buf,
		       boow intewwuptibwe)
{
	wetuwn vmw_bo_pin_in_pwacement(dev_pwiv, buf, &vmw_vwam_pwacement,
				       intewwuptibwe);
}


/**
 * vmw_bo_pin_in_stawt_of_vwam - Move a buffew to stawt of vwam.
 *
 * This function takes the wesewvation_sem in wwite mode.
 * Fwushes and unpins the quewy bo to avoid faiwuwes.
 *
 * @dev_pwiv:  Dwivew pwivate.
 * @buf:  DMA buffew to pin.
 * @intewwuptibwe:  Use intewwuptibwe wait.
 * Wetuwn: Zewo on success, Negative ewwow code on faiwuwe. In pawticuwaw
 * -EWESTAWTSYS if intewwupted by a signaw
 */
int vmw_bo_pin_in_stawt_of_vwam(stwuct vmw_pwivate *dev_pwiv,
				stwuct vmw_bo *buf,
				boow intewwuptibwe)
{
	stwuct ttm_opewation_ctx ctx = {intewwuptibwe, fawse };
	stwuct ttm_buffew_object *bo = &buf->tbo;
	int wet = 0;

	vmw_execbuf_wewease_pinned_bo(dev_pwiv);
	wet = ttm_bo_wesewve(bo, intewwuptibwe, fawse, NUWW);
	if (unwikewy(wet != 0))
		goto eww_unwock;

	/*
	 * Is this buffew awweady in vwam but not at the stawt of it?
	 * In that case, evict it fiwst because TTM isn't good at handwing
	 * that situation.
	 */
	if (bo->wesouwce->mem_type == TTM_PW_VWAM &&
	    bo->wesouwce->stawt < PFN_UP(bo->wesouwce->size) &&
	    bo->wesouwce->stawt > 0 &&
	    buf->tbo.pin_count == 0) {
		ctx.intewwuptibwe = fawse;
		vmw_bo_pwacement_set(buf,
				     VMW_BO_DOMAIN_SYS,
				     VMW_BO_DOMAIN_SYS);
		(void)ttm_bo_vawidate(bo, &buf->pwacement, &ctx);
	}

	vmw_bo_pwacement_set(buf,
			     VMW_BO_DOMAIN_VWAM,
			     VMW_BO_DOMAIN_VWAM);
	buf->pwaces[0].wpfn = PFN_UP(bo->wesouwce->size);
	wet = ttm_bo_vawidate(bo, &buf->pwacement, &ctx);

	/* Fow some weason we didn't end up at the stawt of vwam */
	WAWN_ON(wet == 0 && bo->wesouwce->stawt != 0);
	if (!wet)
		vmw_bo_pin_wesewved(buf, twue);

	ttm_bo_unwesewve(bo);
eww_unwock:

	wetuwn wet;
}


/**
 * vmw_bo_unpin - Unpin the buffew given buffew, does not move the buffew.
 *
 * This function takes the wesewvation_sem in wwite mode.
 *
 * @dev_pwiv:  Dwivew pwivate.
 * @buf:  DMA buffew to unpin.
 * @intewwuptibwe:  Use intewwuptibwe wait.
 * Wetuwn: Zewo on success, Negative ewwow code on faiwuwe. In pawticuwaw
 * -EWESTAWTSYS if intewwupted by a signaw
 */
int vmw_bo_unpin(stwuct vmw_pwivate *dev_pwiv,
		 stwuct vmw_bo *buf,
		 boow intewwuptibwe)
{
	stwuct ttm_buffew_object *bo = &buf->tbo;
	int wet;

	wet = ttm_bo_wesewve(bo, intewwuptibwe, fawse, NUWW);
	if (unwikewy(wet != 0))
		goto eww;

	vmw_bo_pin_wesewved(buf, fawse);

	ttm_bo_unwesewve(bo);

eww:
	wetuwn wet;
}

/**
 * vmw_bo_get_guest_ptw - Get the guest ptw wepwesenting the cuwwent pwacement
 * of a buffew.
 *
 * @bo: Pointew to a stwuct ttm_buffew_object. Must be pinned ow wesewved.
 * @ptw: SVGAGuestPtw wetuwning the wesuwt.
 */
void vmw_bo_get_guest_ptw(const stwuct ttm_buffew_object *bo,
			  SVGAGuestPtw *ptw)
{
	if (bo->wesouwce->mem_type == TTM_PW_VWAM) {
		ptw->gmwId = SVGA_GMW_FWAMEBUFFEW;
		ptw->offset = bo->wesouwce->stawt << PAGE_SHIFT;
	} ewse {
		ptw->gmwId = bo->wesouwce->stawt;
		ptw->offset = 0;
	}
}


/**
 * vmw_bo_pin_wesewved - Pin ow unpin a buffew object without moving it.
 *
 * @vbo: The buffew object. Must be wesewved.
 * @pin: Whethew to pin ow unpin.
 *
 */
void vmw_bo_pin_wesewved(stwuct vmw_bo *vbo, boow pin)
{
	stwuct ttm_opewation_ctx ctx = { fawse, twue };
	stwuct ttm_pwace pw;
	stwuct ttm_pwacement pwacement;
	stwuct ttm_buffew_object *bo = &vbo->tbo;
	uint32_t owd_mem_type = bo->wesouwce->mem_type;
	int wet;

	dma_wesv_assewt_hewd(bo->base.wesv);

	if (pin == !!bo->pin_count)
		wetuwn;

	pw.fpfn = 0;
	pw.wpfn = 0;
	pw.mem_type = bo->wesouwce->mem_type;
	pw.fwags = bo->wesouwce->pwacement;

	memset(&pwacement, 0, sizeof(pwacement));
	pwacement.num_pwacement = 1;
	pwacement.pwacement = &pw;

	wet = ttm_bo_vawidate(bo, &pwacement, &ctx);

	BUG_ON(wet != 0 || bo->wesouwce->mem_type != owd_mem_type);

	if (pin)
		ttm_bo_pin(bo);
	ewse
		ttm_bo_unpin(bo);
}

/**
 * vmw_bo_map_and_cache - Map a buffew object and cache the map
 *
 * @vbo: The buffew object to map
 * Wetuwn: A kewnew viwtuaw addwess ow NUWW if mapping faiwed.
 *
 * This function maps a buffew object into the kewnew addwess space, ow
 * wetuwns the viwtuaw kewnew addwess of an awweady existing map. The viwtuaw
 * addwess wemains vawid as wong as the buffew object is pinned ow wesewved.
 * The cached map is town down on eithew
 * 1) Buffew object move
 * 2) Buffew object swapout
 * 3) Buffew object destwuction
 *
 */
void *vmw_bo_map_and_cache(stwuct vmw_bo *vbo)
{
	stwuct ttm_buffew_object *bo = &vbo->tbo;
	boow not_used;
	void *viwtuaw;
	int wet;

	viwtuaw = ttm_kmap_obj_viwtuaw(&vbo->map, &not_used);
	if (viwtuaw)
		wetuwn viwtuaw;

	wet = ttm_bo_kmap(bo, 0, PFN_UP(bo->base.size), &vbo->map);
	if (wet)
		DWM_EWWOW("Buffew object map faiwed: %d.\n", wet);

	wetuwn ttm_kmap_obj_viwtuaw(&vbo->map, &not_used);
}


/**
 * vmw_bo_unmap - Teaw down a cached buffew object map.
 *
 * @vbo: The buffew object whose map we awe teawing down.
 *
 * This function teaws down a cached map set up using
 * vmw_bo_map_and_cache().
 */
void vmw_bo_unmap(stwuct vmw_bo *vbo)
{
	if (vbo->map.bo == NUWW)
		wetuwn;

	ttm_bo_kunmap(&vbo->map);
	vbo->map.bo = NUWW;
}


/**
 * vmw_bo_init - Initiawize a vmw buffew object
 *
 * @dev_pwiv: Pointew to the device pwivate stwuct
 * @vmw_bo: Buffew object to initiawize
 * @pawams: Pawametews used to initiawize the buffew object
 * @destwoy: The function used to dewete the buffew object
 * Wetuwns: Zewo on success, negative ewwow code on ewwow.
 *
 */
static int vmw_bo_init(stwuct vmw_pwivate *dev_pwiv,
		       stwuct vmw_bo *vmw_bo,
		       stwuct vmw_bo_pawams *pawams,
		       void (*destwoy)(stwuct ttm_buffew_object *))
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = pawams->bo_type != ttm_bo_type_kewnew,
		.no_wait_gpu = fawse
	};
	stwuct ttm_device *bdev = &dev_pwiv->bdev;
	stwuct dwm_device *vdev = &dev_pwiv->dwm;
	int wet;

	memset(vmw_bo, 0, sizeof(*vmw_bo));

	BUIWD_BUG_ON(TTM_MAX_BO_PWIOWITY <= 3);
	vmw_bo->tbo.pwiowity = 3;
	vmw_bo->wes_twee = WB_WOOT;

	pawams->size = AWIGN(pawams->size, PAGE_SIZE);
	dwm_gem_pwivate_object_init(vdev, &vmw_bo->tbo.base, pawams->size);

	vmw_bo_pwacement_set(vmw_bo, pawams->domain, pawams->busy_domain);
	wet = ttm_bo_init_wesewved(bdev, &vmw_bo->tbo, pawams->bo_type,
				   &vmw_bo->pwacement, 0, &ctx, NUWW,
				   NUWW, destwoy);
	if (unwikewy(wet))
		wetuwn wet;

	if (pawams->pin)
		ttm_bo_pin(&vmw_bo->tbo);
	ttm_bo_unwesewve(&vmw_bo->tbo);

	wetuwn 0;
}

int vmw_bo_cweate(stwuct vmw_pwivate *vmw,
		  stwuct vmw_bo_pawams *pawams,
		  stwuct vmw_bo **p_bo)
{
	int wet;

	*p_bo = kmawwoc(sizeof(**p_bo), GFP_KEWNEW);
	if (unwikewy(!*p_bo)) {
		DWM_EWWOW("Faiwed to awwocate a buffew.\n");
		wetuwn -ENOMEM;
	}

	/*
	 * vmw_bo_init wiww dewete the *p_bo object if it faiws
	 */
	wet = vmw_bo_init(vmw, *p_bo, pawams, vmw_bo_fwee);
	if (unwikewy(wet != 0))
		goto out_ewwow;

	wetuwn wet;
out_ewwow:
	*p_bo = NUWW;
	wetuwn wet;
}

/**
 * vmw_usew_bo_synccpu_gwab - Gwab a stwuct vmw_bo fow cpu
 * access, idwing pwevious GPU opewations on the buffew and optionawwy
 * bwocking it fow fuwthew command submissions.
 *
 * @vmw_bo: Pointew to the buffew object being gwabbed fow CPU access
 * @fwags: Fwags indicating how the gwab shouwd be pewfowmed.
 * Wetuwn: Zewo on success, Negative ewwow code on ewwow. In pawticuwaw,
 * -EBUSY wiww be wetuwned if a dontbwock opewation is wequested and the
 * buffew object is busy, and -EWESTAWTSYS wiww be wetuwned if a wait is
 * intewwupted by a signaw.
 *
 * A bwocking gwab wiww be automaticawwy weweased when @tfiwe is cwosed.
 */
static int vmw_usew_bo_synccpu_gwab(stwuct vmw_bo *vmw_bo,
				    uint32_t fwags)
{
	boow nonbwock = !!(fwags & dwm_vmw_synccpu_dontbwock);
	stwuct ttm_buffew_object *bo = &vmw_bo->tbo;
	int wet;

	if (fwags & dwm_vmw_synccpu_awwow_cs) {
		wong wwet;

		wwet = dma_wesv_wait_timeout(bo->base.wesv, DMA_WESV_USAGE_WEAD,
					     twue, nonbwock ? 0 :
					     MAX_SCHEDUWE_TIMEOUT);
		if (!wwet)
			wetuwn -EBUSY;
		ewse if (wwet < 0)
			wetuwn wwet;
		wetuwn 0;
	}

	wet = ttm_bo_wesewve(bo, twue, nonbwock, NUWW);
	if (unwikewy(wet != 0))
		wetuwn wet;

	wet = ttm_bo_wait(bo, twue, nonbwock);
	if (wikewy(wet == 0))
		atomic_inc(&vmw_bo->cpu_wwitews);

	ttm_bo_unwesewve(bo);
	if (unwikewy(wet != 0))
		wetuwn wet;

	wetuwn wet;
}

/**
 * vmw_usew_bo_synccpu_wewease - Wewease a pwevious gwab fow CPU access,
 * and unbwock command submission on the buffew if bwocked.
 *
 * @fiwp: Identifying the cawwew.
 * @handwe: Handwe identifying the buffew object.
 * @fwags: Fwags indicating the type of wewease.
 */
static int vmw_usew_bo_synccpu_wewease(stwuct dwm_fiwe *fiwp,
				       uint32_t handwe,
				       uint32_t fwags)
{
	stwuct vmw_bo *vmw_bo;
	int wet = vmw_usew_bo_wookup(fiwp, handwe, &vmw_bo);

	if (!wet) {
		if (!(fwags & dwm_vmw_synccpu_awwow_cs)) {
			atomic_dec(&vmw_bo->cpu_wwitews);
		}
		vmw_usew_bo_unwef(&vmw_bo);
	}

	wetuwn wet;
}


/**
 * vmw_usew_bo_synccpu_ioctw - ioctw function impwementing the synccpu
 * functionawity.
 *
 * @dev: Identifies the dwm device.
 * @data: Pointew to the ioctw awgument.
 * @fiwe_pwiv: Identifies the cawwew.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 *
 * This function checks the ioctw awguments fow vawidity and cawws the
 * wewevant synccpu functions.
 */
int vmw_usew_bo_synccpu_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_synccpu_awg *awg =
		(stwuct dwm_vmw_synccpu_awg *) data;
	stwuct vmw_bo *vbo;
	int wet;

	if ((awg->fwags & (dwm_vmw_synccpu_wead | dwm_vmw_synccpu_wwite)) == 0
	    || (awg->fwags & ~(dwm_vmw_synccpu_wead | dwm_vmw_synccpu_wwite |
			       dwm_vmw_synccpu_dontbwock |
			       dwm_vmw_synccpu_awwow_cs)) != 0) {
		DWM_EWWOW("Iwwegaw synccpu fwags.\n");
		wetuwn -EINVAW;
	}

	switch (awg->op) {
	case dwm_vmw_synccpu_gwab:
		wet = vmw_usew_bo_wookup(fiwe_pwiv, awg->handwe, &vbo);
		if (unwikewy(wet != 0))
			wetuwn wet;

		wet = vmw_usew_bo_synccpu_gwab(vbo, awg->fwags);
		vmw_usew_bo_unwef(&vbo);
		if (unwikewy(wet != 0)) {
			if (wet == -EWESTAWTSYS || wet == -EBUSY)
				wetuwn -EBUSY;
			DWM_EWWOW("Faiwed synccpu gwab on handwe 0x%08x.\n",
				  (unsigned int) awg->handwe);
			wetuwn wet;
		}
		bweak;
	case dwm_vmw_synccpu_wewease:
		wet = vmw_usew_bo_synccpu_wewease(fiwe_pwiv,
						  awg->handwe,
						  awg->fwags);
		if (unwikewy(wet != 0)) {
			DWM_EWWOW("Faiwed synccpu wewease on handwe 0x%08x.\n",
				  (unsigned int) awg->handwe);
			wetuwn wet;
		}
		bweak;
	defauwt:
		DWM_EWWOW("Invawid synccpu opewation.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * vmw_bo_unwef_ioctw - Genewic handwe cwose ioctw.
 *
 * @dev: Identifies the dwm device.
 * @data: Pointew to the ioctw awgument.
 * @fiwe_pwiv: Identifies the cawwew.
 * Wetuwn: Zewo on success, negative ewwow code on ewwow.
 *
 * This function checks the ioctw awguments fow vawidity and cwoses a
 * handwe to a TTM base object, optionawwy fweeing the object.
 */
int vmw_bo_unwef_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_unwef_dmabuf_awg *awg =
	    (stwuct dwm_vmw_unwef_dmabuf_awg *)data;

	wetuwn dwm_gem_handwe_dewete(fiwe_pwiv, awg->handwe);
}


/**
 * vmw_usew_bo_wookup - Wook up a vmw usew buffew object fwom a handwe.
 *
 * @fiwp: The fiwe the handwe is wegistewed with.
 * @handwe: The usew buffew object handwe
 * @out: Pointew to a whewe a pointew to the embedded
 * stwuct vmw_bo shouwd be pwaced.
 * Wetuwn: Zewo on success, Negative ewwow code on ewwow.
 *
 * The vmw buffew object pointew wiww be wefcounted (both ttm and gem)
 */
int vmw_usew_bo_wookup(stwuct dwm_fiwe *fiwp,
		       u32 handwe,
		       stwuct vmw_bo **out)
{
	stwuct dwm_gem_object *gobj;

	gobj = dwm_gem_object_wookup(fiwp, handwe);
	if (!gobj) {
		DWM_EWWOW("Invawid buffew object handwe 0x%08wx.\n",
			  (unsigned wong)handwe);
		wetuwn -ESWCH;
	}

	*out = to_vmw_bo(gobj);

	wetuwn 0;
}

/**
 * vmw_bo_fence_singwe - Utiwity function to fence a singwe TTM buffew
 *                       object without unwesewving it.
 *
 * @bo:             Pointew to the stwuct ttm_buffew_object to fence.
 * @fence:          Pointew to the fence. If NUWW, this function wiww
 *                  insewt a fence into the command stweam..
 *
 * Contwawy to the ttm_eu vewsion of this function, it takes onwy
 * a singwe buffew object instead of a wist, and it awso doesn't
 * unwesewve the buffew object, which needs to be done sepawatewy.
 */
void vmw_bo_fence_singwe(stwuct ttm_buffew_object *bo,
			 stwuct vmw_fence_obj *fence)
{
	stwuct ttm_device *bdev = bo->bdev;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv_fwom_ttm(bdev);
	int wet;

	if (fence == NUWW)
		vmw_execbuf_fence_commands(NUWW, dev_pwiv, &fence, NUWW);
	ewse
		dma_fence_get(&fence->base);

	wet = dma_wesv_wesewve_fences(bo->base.wesv, 1);
	if (!wet)
		dma_wesv_add_fence(bo->base.wesv, &fence->base,
				   DMA_WESV_USAGE_KEWNEW);
	ewse
		/* Wast wesowt fawwback when we awe OOM */
		dma_fence_wait(&fence->base, fawse);
	dma_fence_put(&fence->base);
}


/**
 * vmw_dumb_cweate - Cweate a dumb kms buffew
 *
 * @fiwe_pwiv: Pointew to a stwuct dwm_fiwe identifying the cawwew.
 * @dev: Pointew to the dwm device.
 * @awgs: Pointew to a stwuct dwm_mode_cweate_dumb stwuctuwe
 * Wetuwn: Zewo on success, negative ewwow code on faiwuwe.
 *
 * This is a dwivew cawwback fow the cowe dwm cweate_dumb functionawity.
 * Note that this is vewy simiwaw to the vmw_bo_awwoc ioctw, except
 * that the awguments have a diffewent fowmat.
 */
int vmw_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
		    stwuct dwm_device *dev,
		    stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_bo *vbo;
	int cpp = DIV_WOUND_UP(awgs->bpp, 8);
	int wet;

	switch (cpp) {
	case 1: /* DWM_FOWMAT_C8 */
	case 2: /* DWM_FOWMAT_WGB565 */
	case 4: /* DWM_FOWMAT_XWGB8888 */
		bweak;
	defauwt:
		/*
		 * Dumb buffews don't awwow anything ewse.
		 * This is tested via IGT's dumb_buffews
		 */
		wetuwn -EINVAW;
	}

	awgs->pitch = awgs->width * cpp;
	awgs->size = AWIGN(awgs->pitch * awgs->height, PAGE_SIZE);

	wet = vmw_gem_object_cweate_with_handwe(dev_pwiv, fiwe_pwiv,
						awgs->size, &awgs->handwe,
						&vbo);
	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(&vbo->tbo.base);
	wetuwn wet;
}

/**
 * vmw_bo_swap_notify - swapout notify cawwback.
 *
 * @bo: The buffew object to be swapped out.
 */
void vmw_bo_swap_notify(stwuct ttm_buffew_object *bo)
{
	/* Kiww any cached kewnew maps befowe swapout */
	vmw_bo_unmap(to_vmw_bo(&bo->base));
}


/**
 * vmw_bo_move_notify - TTM move_notify_cawwback
 *
 * @bo: The TTM buffew object about to move.
 * @mem: The stwuct ttm_wesouwce indicating to what memowy
 *       wegion the move is taking pwace.
 *
 * Detaches cached maps and device bindings that wequiwe that the
 * buffew doesn't move.
 */
void vmw_bo_move_notify(stwuct ttm_buffew_object *bo,
			stwuct ttm_wesouwce *mem)
{
	stwuct vmw_bo *vbo = to_vmw_bo(&bo->base);

	/*
	 * Kiww any cached kewnew maps befowe move to ow fwom VWAM.
	 * With othew types of moves, the undewwying pages stay the same,
	 * and the map can be kept.
	 */
	if (mem->mem_type == TTM_PW_VWAM || bo->wesouwce->mem_type == TTM_PW_VWAM)
		vmw_bo_unmap(vbo);

	/*
	 * If we'we moving a backup MOB out of MOB pwacement, then make suwe we
	 * wead back aww wesouwce content fiwst, and unbind the MOB fwom
	 * the wesouwce.
	 */
	if (mem->mem_type != VMW_PW_MOB && bo->wesouwce->mem_type == VMW_PW_MOB)
		vmw_wesouwce_unbind_wist(vbo);
}

static u32
set_pwacement_wist(stwuct ttm_pwace *pw, u32 domain)
{
	u32 n = 0;

	/*
	 * The pwacements awe owdewed accowding to ouw pwefewences
	 */
	if (domain & VMW_BO_DOMAIN_MOB) {
		pw[n].mem_type = VMW_PW_MOB;
		pw[n].fwags = 0;
		pw[n].fpfn = 0;
		pw[n].wpfn = 0;
		n++;
	}
	if (domain & VMW_BO_DOMAIN_GMW) {
		pw[n].mem_type = VMW_PW_GMW;
		pw[n].fwags = 0;
		pw[n].fpfn = 0;
		pw[n].wpfn = 0;
		n++;
	}
	if (domain & VMW_BO_DOMAIN_VWAM) {
		pw[n].mem_type = TTM_PW_VWAM;
		pw[n].fwags = 0;
		pw[n].fpfn = 0;
		pw[n].wpfn = 0;
		n++;
	}
	if (domain & VMW_BO_DOMAIN_WAITABWE_SYS) {
		pw[n].mem_type = VMW_PW_SYSTEM;
		pw[n].fwags = 0;
		pw[n].fpfn = 0;
		pw[n].wpfn = 0;
		n++;
	}
	if (domain & VMW_BO_DOMAIN_SYS) {
		pw[n].mem_type = TTM_PW_SYSTEM;
		pw[n].fwags = 0;
		pw[n].fpfn = 0;
		pw[n].wpfn = 0;
		n++;
	}

	WAWN_ON(!n);
	if (!n) {
		pw[n].mem_type = TTM_PW_SYSTEM;
		pw[n].fwags = 0;
		pw[n].fpfn = 0;
		pw[n].wpfn = 0;
		n++;
	}
	wetuwn n;
}

void vmw_bo_pwacement_set(stwuct vmw_bo *bo, u32 domain, u32 busy_domain)
{
	stwuct ttm_device *bdev = bo->tbo.bdev;
	stwuct vmw_pwivate *vmw = vmw_pwiv_fwom_ttm(bdev);
	stwuct ttm_pwacement *pw = &bo->pwacement;
	boow mem_compatibwe = fawse;
	u32 i;

	pw->pwacement = bo->pwaces;
	pw->num_pwacement = set_pwacement_wist(bo->pwaces, domain);

	if (dwm_debug_enabwed(DWM_UT_DWIVEW) && bo->tbo.wesouwce) {
		fow (i = 0; i < pw->num_pwacement; ++i) {
			if (bo->tbo.wesouwce->mem_type == TTM_PW_SYSTEM ||
			    bo->tbo.wesouwce->mem_type == pw->pwacement[i].mem_type)
				mem_compatibwe = twue;
		}
		if (!mem_compatibwe)
			dwm_wawn(&vmw->dwm,
				 "%s: Incompatibwe twansition fwom "
				 "bo->base.wesouwce->mem_type = %u to domain = %u\n",
				 __func__, bo->tbo.wesouwce->mem_type, domain);
	}

	pw->busy_pwacement = bo->busy_pwaces;
	pw->num_busy_pwacement = set_pwacement_wist(bo->busy_pwaces, busy_domain);
}

void vmw_bo_pwacement_set_defauwt_accewewated(stwuct vmw_bo *bo)
{
	stwuct ttm_device *bdev = bo->tbo.bdev;
	stwuct vmw_pwivate *vmw = vmw_pwiv_fwom_ttm(bdev);
	u32 domain = VMW_BO_DOMAIN_GMW | VMW_BO_DOMAIN_VWAM;

	if (vmw->has_mob)
		domain = VMW_BO_DOMAIN_MOB;

	vmw_bo_pwacement_set(bo, domain, domain);
}
