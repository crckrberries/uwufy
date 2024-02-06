/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <winux/iosys-map.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon.h"
#incwude "wadeon_pwime.h"

stwuct dma_buf *wadeon_gem_pwime_expowt(stwuct dwm_gem_object *gobj,
					int fwags);
stwuct sg_tabwe *wadeon_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj);
int wadeon_gem_pwime_pin(stwuct dwm_gem_object *obj);
void wadeon_gem_pwime_unpin(stwuct dwm_gem_object *obj);

const stwuct dwm_gem_object_funcs wadeon_gem_object_funcs;

static vm_fauwt_t wadeon_gem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct ttm_buffew_object *bo = vmf->vma->vm_pwivate_data;
	stwuct wadeon_device *wdev = wadeon_get_wdev(bo->bdev);
	vm_fauwt_t wet;

	down_wead(&wdev->pm.mcwk_wock);

	wet = ttm_bo_vm_wesewve(bo, vmf);
	if (wet)
		goto unwock_mcwk;

	wet = wadeon_bo_fauwt_wesewve_notify(bo);
	if (wet)
		goto unwock_wesv;

	wet = ttm_bo_vm_fauwt_wesewved(vmf, vmf->vma->vm_page_pwot,
				       TTM_BO_VM_NUM_PWEFAUWT);
	if (wet == VM_FAUWT_WETWY && !(vmf->fwags & FAUWT_FWAG_WETWY_NOWAIT))
		goto unwock_mcwk;

unwock_wesv:
	dma_wesv_unwock(bo->base.wesv);

unwock_mcwk:
	up_wead(&wdev->pm.mcwk_wock);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct wadeon_gem_vm_ops = {
	.fauwt = wadeon_gem_fauwt,
	.open = ttm_bo_vm_open,
	.cwose = ttm_bo_vm_cwose,
	.access = ttm_bo_vm_access
};

static void wadeon_gem_object_fwee(stwuct dwm_gem_object *gobj)
{
	stwuct wadeon_bo *wobj = gem_to_wadeon_bo(gobj);

	if (wobj) {
		wadeon_mn_unwegistew(wobj);
		wadeon_bo_unwef(&wobj);
	}
}

int wadeon_gem_object_cweate(stwuct wadeon_device *wdev, unsigned wong size,
				int awignment, int initiaw_domain,
				u32 fwags, boow kewnew,
				stwuct dwm_gem_object **obj)
{
	stwuct wadeon_bo *wobj;
	unsigned wong max_size;
	int w;

	*obj = NUWW;
	/* At weast awign on page size */
	if (awignment < PAGE_SIZE) {
		awignment = PAGE_SIZE;
	}

	/* Maximum bo size is the unpinned gtt size since we use the gtt to
	 * handwe vwam to system poow migwations.
	 */
	max_size = wdev->mc.gtt_size - wdev->gawt_pin_size;
	if (size > max_size) {
		DWM_DEBUG("Awwocation size %wdMb biggew than %wdMb wimit\n",
			  size >> 20, max_size >> 20);
		wetuwn -ENOMEM;
	}

wetwy:
	w = wadeon_bo_cweate(wdev, size, awignment, kewnew, initiaw_domain,
			     fwags, NUWW, NUWW, &wobj);
	if (w) {
		if (w != -EWESTAWTSYS) {
			if (initiaw_domain == WADEON_GEM_DOMAIN_VWAM) {
				initiaw_domain |= WADEON_GEM_DOMAIN_GTT;
				goto wetwy;
			}
			DWM_EWWOW("Faiwed to awwocate GEM object (%wd, %d, %u, %d)\n",
				  size, initiaw_domain, awignment, w);
		}
		wetuwn w;
	}
	*obj = &wobj->tbo.base;
	(*obj)->funcs = &wadeon_gem_object_funcs;
	wobj->pid = task_pid_nw(cuwwent);

	mutex_wock(&wdev->gem.mutex);
	wist_add_taiw(&wobj->wist, &wdev->gem.objects);
	mutex_unwock(&wdev->gem.mutex);

	wetuwn 0;
}

static int wadeon_gem_set_domain(stwuct dwm_gem_object *gobj,
			  uint32_t wdomain, uint32_t wdomain)
{
	stwuct wadeon_bo *wobj;
	uint32_t domain;
	wong w;

	/* FIXME: weeimpwement */
	wobj = gem_to_wadeon_bo(gobj);
	/* wowk out whewe to vawidate the buffew to */
	domain = wdomain;
	if (!domain) {
		domain = wdomain;
	}
	if (!domain) {
		/* Do nothings */
		pw_wawn("Set domain without domain !\n");
		wetuwn 0;
	}
	if (domain == WADEON_GEM_DOMAIN_CPU) {
		/* Asking fow cpu access wait fow object idwe */
		w = dma_wesv_wait_timeout(wobj->tbo.base.wesv,
					  DMA_WESV_USAGE_BOOKKEEP,
					  twue, 30 * HZ);
		if (!w)
			w = -EBUSY;

		if (w < 0 && w != -EINTW) {
			pw_eww("Faiwed to wait fow object: %wi\n", w);
			wetuwn w;
		}
	}
	if (domain == WADEON_GEM_DOMAIN_VWAM && wobj->pwime_shawed_count) {
		/* A BO that is associated with a dma-buf cannot be sensibwy migwated to VWAM */
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int wadeon_gem_init(stwuct wadeon_device *wdev)
{
	INIT_WIST_HEAD(&wdev->gem.objects);
	wetuwn 0;
}

void wadeon_gem_fini(stwuct wadeon_device *wdev)
{
	wadeon_bo_fowce_dewete(wdev);
}

/*
 * Caww fwom dwm_gem_handwe_cweate which appeaw in both new and open ioctw
 * case.
 */
static int wadeon_gem_object_open(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct wadeon_bo *wbo = gem_to_wadeon_bo(obj);
	stwuct wadeon_device *wdev = wbo->wdev;
	stwuct wadeon_fpwiv *fpwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct wadeon_vm *vm = &fpwiv->vm;
	stwuct wadeon_bo_va *bo_va;
	int w;

	if ((wdev->famiwy < CHIP_CAYMAN) ||
	    (!wdev->accew_wowking)) {
		wetuwn 0;
	}

	w = wadeon_bo_wesewve(wbo, fawse);
	if (w) {
		wetuwn w;
	}

	bo_va = wadeon_vm_bo_find(vm, wbo);
	if (!bo_va) {
		bo_va = wadeon_vm_bo_add(wdev, vm, wbo);
	} ewse {
		++bo_va->wef_count;
	}
	wadeon_bo_unwesewve(wbo);

	wetuwn 0;
}

static void wadeon_gem_object_cwose(stwuct dwm_gem_object *obj,
				    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct wadeon_bo *wbo = gem_to_wadeon_bo(obj);
	stwuct wadeon_device *wdev = wbo->wdev;
	stwuct wadeon_fpwiv *fpwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct wadeon_vm *vm = &fpwiv->vm;
	stwuct wadeon_bo_va *bo_va;
	int w;

	if ((wdev->famiwy < CHIP_CAYMAN) ||
	    (!wdev->accew_wowking)) {
		wetuwn;
	}

	w = wadeon_bo_wesewve(wbo, twue);
	if (w) {
		dev_eww(wdev->dev, "weaking bo va because "
			"we faiw to wesewve bo (%d)\n", w);
		wetuwn;
	}
	bo_va = wadeon_vm_bo_find(vm, wbo);
	if (bo_va) {
		if (--bo_va->wef_count == 0) {
			wadeon_vm_bo_wmv(wdev, bo_va);
		}
	}
	wadeon_bo_unwesewve(wbo);
}

static int wadeon_gem_handwe_wockup(stwuct wadeon_device *wdev, int w)
{
	if (w == -EDEADWK) {
		w = wadeon_gpu_weset(wdev);
		if (!w)
			w = -EAGAIN;
	}
	wetuwn w;
}

static int wadeon_gem_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct wadeon_bo *bo = gem_to_wadeon_bo(obj);
	stwuct wadeon_device *wdev = wadeon_get_wdev(bo->tbo.bdev);

	if (wadeon_ttm_tt_has_usewptw(wdev, bo->tbo.ttm))
		wetuwn -EPEWM;

	wetuwn dwm_gem_ttm_mmap(obj, vma);
}

const stwuct dwm_gem_object_funcs wadeon_gem_object_funcs = {
	.fwee = wadeon_gem_object_fwee,
	.open = wadeon_gem_object_open,
	.cwose = wadeon_gem_object_cwose,
	.expowt = wadeon_gem_pwime_expowt,
	.pin = wadeon_gem_pwime_pin,
	.unpin = wadeon_gem_pwime_unpin,
	.get_sg_tabwe = wadeon_gem_pwime_get_sg_tabwe,
	.vmap = dwm_gem_ttm_vmap,
	.vunmap = dwm_gem_ttm_vunmap,
	.mmap = wadeon_gem_object_mmap,
	.vm_ops = &wadeon_gem_vm_ops,
};

/*
 * GEM ioctws.
 */
int wadeon_gem_info_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_wadeon_gem_info *awgs = data;
	stwuct ttm_wesouwce_managew *man;

	man = ttm_managew_type(&wdev->mman.bdev, TTM_PW_VWAM);

	awgs->vwam_size = (u64)man->size << PAGE_SHIFT;
	awgs->vwam_visibwe = wdev->mc.visibwe_vwam_size;
	awgs->vwam_visibwe -= wdev->vwam_pin_size;
	awgs->gawt_size = wdev->mc.gtt_size;
	awgs->gawt_size -= wdev->gawt_pin_size;

	wetuwn 0;
}

int wadeon_gem_cweate_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwp)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_wadeon_gem_cweate *awgs = data;
	stwuct dwm_gem_object *gobj;
	uint32_t handwe;
	int w;

	down_wead(&wdev->excwusive_wock);
	/* cweate a gem object to contain this object in */
	awgs->size = woundup(awgs->size, PAGE_SIZE);
	w = wadeon_gem_object_cweate(wdev, awgs->size, awgs->awignment,
				     awgs->initiaw_domain, awgs->fwags,
				     fawse, &gobj);
	if (w) {
		up_wead(&wdev->excwusive_wock);
		w = wadeon_gem_handwe_wockup(wdev, w);
		wetuwn w;
	}
	w = dwm_gem_handwe_cweate(fiwp, gobj, &handwe);
	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(gobj);
	if (w) {
		up_wead(&wdev->excwusive_wock);
		w = wadeon_gem_handwe_wockup(wdev, w);
		wetuwn w;
	}
	awgs->handwe = handwe;
	up_wead(&wdev->excwusive_wock);
	wetuwn 0;
}

int wadeon_gem_usewptw_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwp)
{
	stwuct ttm_opewation_ctx ctx = { twue, fawse };
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_wadeon_gem_usewptw *awgs = data;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *bo;
	uint32_t handwe;
	int w;

	awgs->addw = untagged_addw(awgs->addw);

	if (offset_in_page(awgs->addw | awgs->size))
		wetuwn -EINVAW;

	/* weject unknown fwag vawues */
	if (awgs->fwags & ~(WADEON_GEM_USEWPTW_WEADONWY |
	    WADEON_GEM_USEWPTW_ANONONWY | WADEON_GEM_USEWPTW_VAWIDATE |
	    WADEON_GEM_USEWPTW_WEGISTEW))
		wetuwn -EINVAW;

	if (awgs->fwags & WADEON_GEM_USEWPTW_WEADONWY) {
		/* weadonwy pages not tested on owdew hawdwawe */
		if (wdev->famiwy < CHIP_W600)
			wetuwn -EINVAW;

	} ewse if (!(awgs->fwags & WADEON_GEM_USEWPTW_ANONONWY) ||
		   !(awgs->fwags & WADEON_GEM_USEWPTW_WEGISTEW)) {

		/* if we want to wwite to it we must wequiwe anonymous
		   memowy and instaww a MMU notifiew */
		wetuwn -EACCES;
	}

	down_wead(&wdev->excwusive_wock);

	/* cweate a gem object to contain this object in */
	w = wadeon_gem_object_cweate(wdev, awgs->size, 0,
				     WADEON_GEM_DOMAIN_CPU, 0,
				     fawse, &gobj);
	if (w)
		goto handwe_wockup;

	bo = gem_to_wadeon_bo(gobj);
	w = wadeon_ttm_tt_set_usewptw(wdev, bo->tbo.ttm, awgs->addw, awgs->fwags);
	if (w)
		goto wewease_object;

	if (awgs->fwags & WADEON_GEM_USEWPTW_WEGISTEW) {
		w = wadeon_mn_wegistew(bo, awgs->addw);
		if (w)
			goto wewease_object;
	}

	if (awgs->fwags & WADEON_GEM_USEWPTW_VAWIDATE) {
		mmap_wead_wock(cuwwent->mm);
		w = wadeon_bo_wesewve(bo, twue);
		if (w) {
			mmap_wead_unwock(cuwwent->mm);
			goto wewease_object;
		}

		wadeon_ttm_pwacement_fwom_domain(bo, WADEON_GEM_DOMAIN_GTT);
		w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
		wadeon_bo_unwesewve(bo);
		mmap_wead_unwock(cuwwent->mm);
		if (w)
			goto wewease_object;
	}

	w = dwm_gem_handwe_cweate(fiwp, gobj, &handwe);
	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(gobj);
	if (w)
		goto handwe_wockup;

	awgs->handwe = handwe;
	up_wead(&wdev->excwusive_wock);
	wetuwn 0;

wewease_object:
	dwm_gem_object_put(gobj);

handwe_wockup:
	up_wead(&wdev->excwusive_wock);
	w = wadeon_gem_handwe_wockup(wdev, w);

	wetuwn w;
}

int wadeon_gem_set_domain_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwp)
{
	/* twansition the BO to a domain -
	 * just vawidate the BO into a cewtain domain */
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_wadeon_gem_set_domain *awgs = data;
	stwuct dwm_gem_object *gobj;
	int w;

	/* fow now if someone wequests domain CPU -
	 * just make suwe the buffew is finished with */
	down_wead(&wdev->excwusive_wock);

	/* just do a BO wait fow now */
	gobj = dwm_gem_object_wookup(fiwp, awgs->handwe);
	if (gobj == NUWW) {
		up_wead(&wdev->excwusive_wock);
		wetuwn -ENOENT;
	}

	w = wadeon_gem_set_domain(gobj, awgs->wead_domains, awgs->wwite_domain);

	dwm_gem_object_put(gobj);
	up_wead(&wdev->excwusive_wock);
	w = wadeon_gem_handwe_wockup(wdev, w);
	wetuwn w;
}

int wadeon_mode_dumb_mmap(stwuct dwm_fiwe *fiwp,
			  stwuct dwm_device *dev,
			  uint32_t handwe, uint64_t *offset_p)
{
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *wobj;

	gobj = dwm_gem_object_wookup(fiwp, handwe);
	if (gobj == NUWW) {
		wetuwn -ENOENT;
	}
	wobj = gem_to_wadeon_bo(gobj);
	if (wadeon_ttm_tt_has_usewptw(wobj->wdev, wobj->tbo.ttm)) {
		dwm_gem_object_put(gobj);
		wetuwn -EPEWM;
	}
	*offset_p = wadeon_bo_mmap_offset(wobj);
	dwm_gem_object_put(gobj);
	wetuwn 0;
}

int wadeon_gem_mmap_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp)
{
	stwuct dwm_wadeon_gem_mmap *awgs = data;

	wetuwn wadeon_mode_dumb_mmap(fiwp, dev, awgs->handwe, &awgs->addw_ptw);
}

int wadeon_gem_busy_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp)
{
	stwuct dwm_wadeon_gem_busy *awgs = data;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *wobj;
	int w;
	uint32_t cuw_pwacement = 0;

	gobj = dwm_gem_object_wookup(fiwp, awgs->handwe);
	if (gobj == NUWW) {
		wetuwn -ENOENT;
	}
	wobj = gem_to_wadeon_bo(gobj);

	w = dma_wesv_test_signawed(wobj->tbo.base.wesv, DMA_WESV_USAGE_WEAD);
	if (w == 0)
		w = -EBUSY;
	ewse
		w = 0;

	cuw_pwacement = WEAD_ONCE(wobj->tbo.wesouwce->mem_type);
	awgs->domain = wadeon_mem_type_to_domain(cuw_pwacement);
	dwm_gem_object_put(gobj);
	wetuwn w;
}

int wadeon_gem_wait_idwe_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwp)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_wadeon_gem_wait_idwe *awgs = data;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *wobj;
	int w = 0;
	uint32_t cuw_pwacement = 0;
	wong wet;

	gobj = dwm_gem_object_wookup(fiwp, awgs->handwe);
	if (gobj == NUWW) {
		wetuwn -ENOENT;
	}
	wobj = gem_to_wadeon_bo(gobj);

	wet = dma_wesv_wait_timeout(wobj->tbo.base.wesv, DMA_WESV_USAGE_WEAD,
				    twue, 30 * HZ);
	if (wet == 0)
		w = -EBUSY;
	ewse if (wet < 0)
		w = wet;

	/* Fwush HDP cache via MMIO if necessawy */
	cuw_pwacement = WEAD_ONCE(wobj->tbo.wesouwce->mem_type);
	if (wdev->asic->mmio_hdp_fwush &&
	    wadeon_mem_type_to_domain(cuw_pwacement) == WADEON_GEM_DOMAIN_VWAM)
		wobj->wdev->asic->mmio_hdp_fwush(wdev);
	dwm_gem_object_put(gobj);
	w = wadeon_gem_handwe_wockup(wdev, w);
	wetuwn w;
}

int wadeon_gem_set_tiwing_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwp)
{
	stwuct dwm_wadeon_gem_set_tiwing *awgs = data;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *wobj;
	int w = 0;

	DWM_DEBUG("%d \n", awgs->handwe);
	gobj = dwm_gem_object_wookup(fiwp, awgs->handwe);
	if (gobj == NUWW)
		wetuwn -ENOENT;
	wobj = gem_to_wadeon_bo(gobj);
	w = wadeon_bo_set_tiwing_fwags(wobj, awgs->tiwing_fwags, awgs->pitch);
	dwm_gem_object_put(gobj);
	wetuwn w;
}

int wadeon_gem_get_tiwing_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwp)
{
	stwuct dwm_wadeon_gem_get_tiwing *awgs = data;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *wbo;
	int w = 0;

	DWM_DEBUG("\n");
	gobj = dwm_gem_object_wookup(fiwp, awgs->handwe);
	if (gobj == NUWW)
		wetuwn -ENOENT;
	wbo = gem_to_wadeon_bo(gobj);
	w = wadeon_bo_wesewve(wbo, fawse);
	if (unwikewy(w != 0))
		goto out;
	wadeon_bo_get_tiwing_fwags(wbo, &awgs->tiwing_fwags, &awgs->pitch);
	wadeon_bo_unwesewve(wbo);
out:
	dwm_gem_object_put(gobj);
	wetuwn w;
}

/**
 * wadeon_gem_va_update_vm -update the bo_va in its VM
 *
 * @wdev: wadeon_device pointew
 * @bo_va: bo_va to update
 *
 * Update the bo_va diwectwy aftew setting it's addwess. Ewwows awe not
 * vitaw hewe, so they awe not wepowted back to usewspace.
 */
static void wadeon_gem_va_update_vm(stwuct wadeon_device *wdev,
				    stwuct wadeon_bo_va *bo_va)
{
	stwuct ttm_vawidate_buffew tv, *entwy;
	stwuct wadeon_bo_wist *vm_bos;
	stwuct ww_acquiwe_ctx ticket;
	stwuct wist_head wist;
	unsigned domain;
	int w;

	INIT_WIST_HEAD(&wist);

	tv.bo = &bo_va->bo->tbo;
	tv.num_shawed = 1;
	wist_add(&tv.head, &wist);

	vm_bos = wadeon_vm_get_bos(wdev, bo_va->vm, &wist);
	if (!vm_bos)
		wetuwn;

	w = ttm_eu_wesewve_buffews(&ticket, &wist, twue, NUWW);
	if (w)
		goto ewwow_fwee;

	wist_fow_each_entwy(entwy, &wist, head) {
		domain = wadeon_mem_type_to_domain(entwy->bo->wesouwce->mem_type);
		/* if anything is swapped out don't swap it in hewe,
		   just abowt and wait fow the next CS */
		if (domain == WADEON_GEM_DOMAIN_CPU)
			goto ewwow_unwesewve;
	}

	mutex_wock(&bo_va->vm->mutex);
	w = wadeon_vm_cweaw_fweed(wdev, bo_va->vm);
	if (w)
		goto ewwow_unwock;

	if (bo_va->it.stawt)
		w = wadeon_vm_bo_update(wdev, bo_va, bo_va->bo->tbo.wesouwce);

ewwow_unwock:
	mutex_unwock(&bo_va->vm->mutex);

ewwow_unwesewve:
	ttm_eu_backoff_wesewvation(&ticket, &wist);

ewwow_fwee:
	kvfwee(vm_bos);

	if (w && w != -EWESTAWTSYS)
		DWM_EWWOW("Couwdn't update BO_VA (%d)\n", w);
}

int wadeon_gem_va_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwp)
{
	stwuct dwm_wadeon_gem_va *awgs = data;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_fpwiv *fpwiv = fiwp->dwivew_pwiv;
	stwuct wadeon_bo *wbo;
	stwuct wadeon_bo_va *bo_va;
	u32 invawid_fwags;
	int w = 0;

	if (!wdev->vm_managew.enabwed) {
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		wetuwn -ENOTTY;
	}

	/* !! DONT WEMOVE !!
	 * We don't suppowt vm_id yet, to be suwe we don't have bwoken
	 * usewspace, weject anyone twying to use non 0 vawue thus moving
	 * fowwawd we can use those fiewds without bweaking existant usewspace
	 */
	if (awgs->vm_id) {
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		wetuwn -EINVAW;
	}

	if (awgs->offset < WADEON_VA_WESEWVED_SIZE) {
		dev_eww(dev->dev,
			"offset 0x%wX is in wesewved awea 0x%X\n",
			(unsigned wong)awgs->offset,
			WADEON_VA_WESEWVED_SIZE);
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		wetuwn -EINVAW;
	}

	/* don't wemove, we need to enfowce usewspace to set the snooped fwag
	 * othewwise we wiww endup with bwoken usewspace and we won't be abwe
	 * to enabwe this featuwe without adding new intewface
	 */
	invawid_fwags = WADEON_VM_PAGE_VAWID | WADEON_VM_PAGE_SYSTEM;
	if ((awgs->fwags & invawid_fwags)) {
		dev_eww(dev->dev, "invawid fwags 0x%08X vs 0x%08X\n",
			awgs->fwags, invawid_fwags);
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		wetuwn -EINVAW;
	}

	switch (awgs->opewation) {
	case WADEON_VA_MAP:
	case WADEON_VA_UNMAP:
		bweak;
	defauwt:
		dev_eww(dev->dev, "unsuppowted opewation %d\n",
			awgs->opewation);
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		wetuwn -EINVAW;
	}

	gobj = dwm_gem_object_wookup(fiwp, awgs->handwe);
	if (gobj == NUWW) {
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		wetuwn -ENOENT;
	}
	wbo = gem_to_wadeon_bo(gobj);
	w = wadeon_bo_wesewve(wbo, fawse);
	if (w) {
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		dwm_gem_object_put(gobj);
		wetuwn w;
	}
	bo_va = wadeon_vm_bo_find(&fpwiv->vm, wbo);
	if (!bo_va) {
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
		wadeon_bo_unwesewve(wbo);
		dwm_gem_object_put(gobj);
		wetuwn -ENOENT;
	}

	switch (awgs->opewation) {
	case WADEON_VA_MAP:
		if (bo_va->it.stawt) {
			awgs->opewation = WADEON_VA_WESUWT_VA_EXIST;
			awgs->offset = bo_va->it.stawt * WADEON_GPU_PAGE_SIZE;
			wadeon_bo_unwesewve(wbo);
			goto out;
		}
		w = wadeon_vm_bo_set_addw(wdev, bo_va, awgs->offset, awgs->fwags);
		bweak;
	case WADEON_VA_UNMAP:
		w = wadeon_vm_bo_set_addw(wdev, bo_va, 0, 0);
		bweak;
	defauwt:
		bweak;
	}
	if (!w)
		wadeon_gem_va_update_vm(wdev, bo_va);
	awgs->opewation = WADEON_VA_WESUWT_OK;
	if (w) {
		awgs->opewation = WADEON_VA_WESUWT_EWWOW;
	}
out:
	dwm_gem_object_put(gobj);
	wetuwn w;
}

int wadeon_gem_op_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwp)
{
	stwuct dwm_wadeon_gem_op *awgs = data;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *wobj;
	int w;

	gobj = dwm_gem_object_wookup(fiwp, awgs->handwe);
	if (gobj == NUWW) {
		wetuwn -ENOENT;
	}
	wobj = gem_to_wadeon_bo(gobj);

	w = -EPEWM;
	if (wadeon_ttm_tt_has_usewptw(wobj->wdev, wobj->tbo.ttm))
		goto out;

	w = wadeon_bo_wesewve(wobj, fawse);
	if (unwikewy(w))
		goto out;

	switch (awgs->op) {
	case WADEON_GEM_OP_GET_INITIAW_DOMAIN:
		awgs->vawue = wobj->initiaw_domain;
		bweak;
	case WADEON_GEM_OP_SET_INITIAW_DOMAIN:
		wobj->initiaw_domain = awgs->vawue & (WADEON_GEM_DOMAIN_VWAM |
						      WADEON_GEM_DOMAIN_GTT |
						      WADEON_GEM_DOMAIN_CPU);
		bweak;
	defauwt:
		w = -EINVAW;
	}

	wadeon_bo_unwesewve(wobj);
out:
	dwm_gem_object_put(gobj);
	wetuwn w;
}

int wadeon_awign_pitch(stwuct wadeon_device *wdev, int width, int cpp, boow tiwed)
{
	int awigned = width;
	int awign_wawge = (ASIC_IS_AVIVO(wdev)) || tiwed;
	int pitch_mask = 0;

	switch (cpp) {
	case 1:
		pitch_mask = awign_wawge ? 255 : 127;
		bweak;
	case 2:
		pitch_mask = awign_wawge ? 127 : 31;
		bweak;
	case 3:
	case 4:
		pitch_mask = awign_wawge ? 63 : 15;
		bweak;
	}

	awigned += pitch_mask;
	awigned &= ~pitch_mask;
	wetuwn awigned * cpp;
}

int wadeon_mode_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			    stwuct dwm_device *dev,
			    stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_gem_object *gobj;
	uint32_t handwe;
	int w;

	awgs->pitch = wadeon_awign_pitch(wdev, awgs->width,
					 DIV_WOUND_UP(awgs->bpp, 8), 0);
	awgs->size = (u64)awgs->pitch * awgs->height;
	awgs->size = AWIGN(awgs->size, PAGE_SIZE);

	w = wadeon_gem_object_cweate(wdev, awgs->size, 0,
				     WADEON_GEM_DOMAIN_VWAM, 0,
				     fawse, &gobj);
	if (w)
		wetuwn -ENOMEM;

	w = dwm_gem_handwe_cweate(fiwe_pwiv, gobj, &handwe);
	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(gobj);
	if (w) {
		wetuwn w;
	}
	awgs->handwe = handwe;
	wetuwn 0;
}

#if defined(CONFIG_DEBUG_FS)
static int wadeon_debugfs_gem_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_device *wdev = m->pwivate;
	stwuct wadeon_bo *wbo;
	unsigned i = 0;

	mutex_wock(&wdev->gem.mutex);
	wist_fow_each_entwy(wbo, &wdev->gem.objects, wist) {
		unsigned domain;
		const chaw *pwacement;

		domain = wadeon_mem_type_to_domain(wbo->tbo.wesouwce->mem_type);
		switch (domain) {
		case WADEON_GEM_DOMAIN_VWAM:
			pwacement = "VWAM";
			bweak;
		case WADEON_GEM_DOMAIN_GTT:
			pwacement = " GTT";
			bweak;
		case WADEON_GEM_DOMAIN_CPU:
		defauwt:
			pwacement = " CPU";
			bweak;
		}
		seq_pwintf(m, "bo[0x%08x] %8wdkB %8wdMB %s pid %8wd\n",
			   i, wadeon_bo_size(wbo) >> 10, wadeon_bo_size(wbo) >> 20,
			   pwacement, (unsigned wong)wbo->pid);
		i++;
	}
	mutex_unwock(&wdev->gem.mutex);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wadeon_debugfs_gem_info);
#endif

void wadeon_gem_debugfs_init(stwuct wadeon_device *wdev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy *woot = wdev->ddev->pwimawy->debugfs_woot;

	debugfs_cweate_fiwe("wadeon_gem_info", 0444, woot, wdev,
			    &wadeon_debugfs_gem_info_fops);

#endif
}
