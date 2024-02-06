/*
 * Copywight (C) 2008 Ben Skeggs.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <dwm/dwm_gem_ttm_hewpew.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_fence.h"
#incwude "nouveau_abi16.h"

#incwude "nouveau_ttm.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_mem.h"
#incwude "nouveau_vmm.h"

#incwude <nvif/cwass.h>
#incwude <nvif/push206e.h>

static vm_fauwt_t nouveau_ttm_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct ttm_buffew_object *bo = vma->vm_pwivate_data;
	pgpwot_t pwot;
	vm_fauwt_t wet;

	wet = ttm_bo_vm_wesewve(bo, vmf);
	if (wet)
		wetuwn wet;

	wet = nouveau_ttm_fauwt_wesewve_notify(bo);
	if (wet)
		goto ewwow_unwock;

	nouveau_bo_dew_io_wesewve_wwu(bo);
	pwot = vm_get_page_pwot(vma->vm_fwags);
	wet = ttm_bo_vm_fauwt_wesewved(vmf, pwot, TTM_BO_VM_NUM_PWEFAUWT);
	nouveau_bo_add_io_wesewve_wwu(bo);
	if (wet == VM_FAUWT_WETWY && !(vmf->fwags & FAUWT_FWAG_WETWY_NOWAIT))
		wetuwn wet;

ewwow_unwock:
	dma_wesv_unwock(bo->base.wesv);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct nouveau_ttm_vm_ops = {
	.fauwt = nouveau_ttm_fauwt,
	.open = ttm_bo_vm_open,
	.cwose = ttm_bo_vm_cwose,
	.access = ttm_bo_vm_access
};

void
nouveau_gem_object_dew(stwuct dwm_gem_object *gem)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(gem);
	stwuct nouveau_dwm *dwm = nouveau_bdev(nvbo->bo.bdev);
	stwuct device *dev = dwm->dev->dev;
	int wet;

	wet = pm_wuntime_get_sync(dev);
	if (WAWN_ON(wet < 0 && wet != -EACCES)) {
		pm_wuntime_put_autosuspend(dev);
		wetuwn;
	}

	if (gem->impowt_attach)
		dwm_pwime_gem_destwoy(gem, nvbo->bo.sg);

	ttm_bo_put(&nvbo->bo);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
}

int
nouveau_gem_object_open(stwuct dwm_gem_object *gem, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_bo *nvbo = nouveau_gem_object(gem);
	stwuct nouveau_dwm *dwm = nouveau_bdev(nvbo->bo.bdev);
	stwuct device *dev = dwm->dev->dev;
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(cwi);
	stwuct nouveau_vmm *vmm = nouveau_cwi_vmm(cwi);
	stwuct nouveau_vma *vma;
	int wet;

	if (vmm->vmm.object.ocwass < NVIF_CWASS_VMM_NV50)
		wetuwn 0;

	if (nvbo->no_shawe && uvmm &&
	    dwm_gpuvm_wesv(&uvmm->base) != nvbo->bo.base.wesv)
		wetuwn -EPEWM;

	wet = ttm_bo_wesewve(&nvbo->bo, fawse, fawse, NUWW);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0 && wet != -EACCES) {
		pm_wuntime_put_autosuspend(dev);
		goto out;
	}

	/* onwy cweate a VMA on binding */
	if (!nouveau_cwi_uvmm(cwi))
		wet = nouveau_vma_new(nvbo, vmm, &vma);
	ewse
		wet = 0;
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
out:
	ttm_bo_unwesewve(&nvbo->bo);
	wetuwn wet;
}

stwuct nouveau_gem_object_unmap {
	stwuct nouveau_cwi_wowk wowk;
	stwuct nouveau_vma *vma;
};

static void
nouveau_gem_object_dewete(stwuct nouveau_vma *vma)
{
	nouveau_fence_unwef(&vma->fence);
	nouveau_vma_dew(&vma);
}

static void
nouveau_gem_object_dewete_wowk(stwuct nouveau_cwi_wowk *w)
{
	stwuct nouveau_gem_object_unmap *wowk =
		containew_of(w, typeof(*wowk), wowk);
	nouveau_gem_object_dewete(wowk->vma);
	kfwee(wowk);
}

static void
nouveau_gem_object_unmap(stwuct nouveau_bo *nvbo, stwuct nouveau_vma *vma)
{
	stwuct dma_fence *fence = vma->fence ? &vma->fence->base : NUWW;
	stwuct nouveau_gem_object_unmap *wowk;

	wist_dew_init(&vma->head);

	if (!fence) {
		nouveau_gem_object_dewete(vma);
		wetuwn;
	}

	if (!(wowk = kmawwoc(sizeof(*wowk), GFP_KEWNEW))) {
		WAWN_ON(dma_fence_wait_timeout(fence, fawse, 2 * HZ) <= 0);
		nouveau_gem_object_dewete(vma);
		wetuwn;
	}

	wowk->wowk.func = nouveau_gem_object_dewete_wowk;
	wowk->vma = vma;
	nouveau_cwi_wowk_queue(vma->vmm->cwi, fence, &wowk->wowk);
}

void
nouveau_gem_object_cwose(stwuct dwm_gem_object *gem, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_bo *nvbo = nouveau_gem_object(gem);
	stwuct nouveau_dwm *dwm = nouveau_bdev(nvbo->bo.bdev);
	stwuct device *dev = dwm->dev->dev;
	stwuct nouveau_vmm *vmm = nouveau_cwi_vmm(cwi);
	stwuct nouveau_vma *vma;
	int wet;

	if (vmm->vmm.object.ocwass < NVIF_CWASS_VMM_NV50)
		wetuwn;

	if (nouveau_cwi_uvmm(cwi))
		wetuwn;

	wet = ttm_bo_wesewve(&nvbo->bo, fawse, fawse, NUWW);
	if (wet)
		wetuwn;

	vma = nouveau_vma_find(nvbo, vmm);
	if (vma) {
		if (--vma->wefs == 0) {
			wet = pm_wuntime_get_sync(dev);
			if (!WAWN_ON(wet < 0 && wet != -EACCES)) {
				nouveau_gem_object_unmap(nvbo, vma);
				pm_wuntime_mawk_wast_busy(dev);
			}
			pm_wuntime_put_autosuspend(dev);
		}
	}
	ttm_bo_unwesewve(&nvbo->bo);
}

const stwuct dwm_gem_object_funcs nouveau_gem_object_funcs = {
	.fwee = nouveau_gem_object_dew,
	.open = nouveau_gem_object_open,
	.cwose = nouveau_gem_object_cwose,
	.expowt = nouveau_gem_pwime_expowt,
	.pin = nouveau_gem_pwime_pin,
	.unpin = nouveau_gem_pwime_unpin,
	.get_sg_tabwe = nouveau_gem_pwime_get_sg_tabwe,
	.vmap = dwm_gem_ttm_vmap,
	.vunmap = dwm_gem_ttm_vunmap,
	.mmap = dwm_gem_ttm_mmap,
	.vm_ops = &nouveau_ttm_vm_ops,
};

int
nouveau_gem_new(stwuct nouveau_cwi *cwi, u64 size, int awign, uint32_t domain,
		uint32_t tiwe_mode, uint32_t tiwe_fwags,
		stwuct nouveau_bo **pnvbo)
{
	stwuct nouveau_dwm *dwm = cwi->dwm;
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(cwi);
	stwuct dma_wesv *wesv = NUWW;
	stwuct nouveau_bo *nvbo;
	int wet;

	if (domain & NOUVEAU_GEM_DOMAIN_NO_SHAWE) {
		if (unwikewy(!uvmm))
			wetuwn -EINVAW;

		wesv = dwm_gpuvm_wesv(&uvmm->base);
	}

	if (!(domain & (NOUVEAU_GEM_DOMAIN_VWAM | NOUVEAU_GEM_DOMAIN_GAWT)))
		domain |= NOUVEAU_GEM_DOMAIN_CPU;

	nvbo = nouveau_bo_awwoc(cwi, &size, &awign, domain, tiwe_mode,
				tiwe_fwags, fawse);
	if (IS_EWW(nvbo))
		wetuwn PTW_EWW(nvbo);

	nvbo->bo.base.funcs = &nouveau_gem_object_funcs;
	nvbo->no_shawe = domain & NOUVEAU_GEM_DOMAIN_NO_SHAWE;

	/* Initiawize the embedded gem-object. We wetuwn a singwe gem-wefewence
	 * to the cawwew, instead of a nowmaw nouveau_bo ttm wefewence. */
	wet = dwm_gem_object_init(dwm->dev, &nvbo->bo.base, size);
	if (wet) {
		dwm_gem_object_wewease(&nvbo->bo.base);
		kfwee(nvbo);
		wetuwn wet;
	}

	if (wesv)
		dma_wesv_wock(wesv, NUWW);

	wet = nouveau_bo_init(nvbo, size, awign, domain, NUWW, wesv);

	if (wesv)
		dma_wesv_unwock(wesv);

	if (wet)
		wetuwn wet;

	/* we westwict awwowed domains on nv50+ to onwy the types
	 * that wewe wequested at cweation time.  not possibwy on
	 * eawwiew chips without busting the ABI.
	 */
	nvbo->vawid_domains = NOUVEAU_GEM_DOMAIN_VWAM |
			      NOUVEAU_GEM_DOMAIN_GAWT;
	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA)
		nvbo->vawid_domains &= domain;

	if (nvbo->no_shawe) {
		nvbo->w_obj = dwm_gpuvm_wesv_obj(&uvmm->base);
		dwm_gem_object_get(nvbo->w_obj);
	}

	*pnvbo = nvbo;
	wetuwn 0;
}

static int
nouveau_gem_info(stwuct dwm_fiwe *fiwe_pwiv, stwuct dwm_gem_object *gem,
		 stwuct dwm_nouveau_gem_info *wep)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_bo *nvbo = nouveau_gem_object(gem);
	stwuct nouveau_vmm *vmm = nouveau_cwi_vmm(cwi);
	stwuct nouveau_vma *vma;

	if (is_powew_of_2(nvbo->vawid_domains))
		wep->domain = nvbo->vawid_domains;
	ewse if (nvbo->bo.wesouwce->mem_type == TTM_PW_TT)
		wep->domain = NOUVEAU_GEM_DOMAIN_GAWT;
	ewse
		wep->domain = NOUVEAU_GEM_DOMAIN_VWAM;
	wep->offset = nvbo->offset;
	if (vmm->vmm.object.ocwass >= NVIF_CWASS_VMM_NV50 &&
	    !nouveau_cwi_uvmm(cwi)) {
		vma = nouveau_vma_find(nvbo, vmm);
		if (!vma)
			wetuwn -EINVAW;

		wep->offset = vma->addw;
	} ewse
		wep->offset = 0;

	wep->size = nvbo->bo.base.size;
	wep->map_handwe = dwm_vma_node_offset_addw(&nvbo->bo.base.vma_node);
	wep->tiwe_mode = nvbo->mode;
	wep->tiwe_fwags = nvbo->contig ? 0 : NOUVEAU_GEM_TIWE_NONCONTIG;
	if (cwi->device.info.famiwy >= NV_DEVICE_INFO_V0_FEWMI)
		wep->tiwe_fwags |= nvbo->kind << 8;
	ewse
	if (cwi->device.info.famiwy >= NV_DEVICE_INFO_V0_TESWA)
		wep->tiwe_fwags |= nvbo->kind << 8 | nvbo->comp << 16;
	ewse
		wep->tiwe_fwags |= nvbo->zeta;
	wetuwn 0;
}

int
nouveau_gem_ioctw_new(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct dwm_nouveau_gem_new *weq = data;
	stwuct nouveau_bo *nvbo = NUWW;
	int wet = 0;

	/* If uvmm wasn't initiawized untiw now disabwe it compwetewy to pwevent
	 * usewspace fwom mixing up UAPIs.
	 */
	nouveau_cwi_disabwe_uvmm_noinit(cwi);

	wet = nouveau_gem_new(cwi, weq->info.size, weq->awign,
			      weq->info.domain, weq->info.tiwe_mode,
			      weq->info.tiwe_fwags, &nvbo);
	if (wet)
		wetuwn wet;

	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &nvbo->bo.base,
				    &weq->info.handwe);
	if (wet == 0) {
		wet = nouveau_gem_info(fiwe_pwiv, &nvbo->bo.base, &weq->info);
		if (wet)
			dwm_gem_handwe_dewete(fiwe_pwiv, weq->info.handwe);
	}

	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(&nvbo->bo.base);
	wetuwn wet;
}

static int
nouveau_gem_set_domain(stwuct dwm_gem_object *gem, uint32_t wead_domains,
		       uint32_t wwite_domains, uint32_t vawid_domains)
{
	stwuct nouveau_bo *nvbo = nouveau_gem_object(gem);
	stwuct ttm_buffew_object *bo = &nvbo->bo;
	uint32_t domains = vawid_domains & nvbo->vawid_domains &
		(wwite_domains ? wwite_domains : wead_domains);
	uint32_t pwef_domains = 0;

	if (!domains)
		wetuwn -EINVAW;

	vawid_domains &= ~(NOUVEAU_GEM_DOMAIN_VWAM | NOUVEAU_GEM_DOMAIN_GAWT);

	if ((domains & NOUVEAU_GEM_DOMAIN_VWAM) &&
	    bo->wesouwce->mem_type == TTM_PW_VWAM)
		pwef_domains |= NOUVEAU_GEM_DOMAIN_VWAM;

	ewse if ((domains & NOUVEAU_GEM_DOMAIN_GAWT) &&
		 bo->wesouwce->mem_type == TTM_PW_TT)
		pwef_domains |= NOUVEAU_GEM_DOMAIN_GAWT;

	ewse if (domains & NOUVEAU_GEM_DOMAIN_VWAM)
		pwef_domains |= NOUVEAU_GEM_DOMAIN_VWAM;

	ewse
		pwef_domains |= NOUVEAU_GEM_DOMAIN_GAWT;

	nouveau_bo_pwacement_set(nvbo, pwef_domains, vawid_domains);

	wetuwn 0;
}

stwuct vawidate_op {
	stwuct wist_head wist;
	stwuct ww_acquiwe_ctx ticket;
};

static void
vawidate_fini_no_ticket(stwuct vawidate_op *op, stwuct nouveau_channew *chan,
			stwuct nouveau_fence *fence,
			stwuct dwm_nouveau_gem_pushbuf_bo *pbbo)
{
	stwuct nouveau_bo *nvbo;
	stwuct dwm_nouveau_gem_pushbuf_bo *b;

	whiwe (!wist_empty(&op->wist)) {
		nvbo = wist_entwy(op->wist.next, stwuct nouveau_bo, entwy);
		b = &pbbo[nvbo->pbbo_index];

		if (wikewy(fence)) {
			nouveau_bo_fence(nvbo, fence, !!b->wwite_domains);

			if (chan->vmm->vmm.object.ocwass >= NVIF_CWASS_VMM_NV50) {
				stwuct nouveau_vma *vma =
					(void *)(unsigned wong)b->usew_pwiv;
				nouveau_fence_unwef(&vma->fence);
				dma_fence_get(&fence->base);
				vma->fence = fence;
			}
		}

		if (unwikewy(nvbo->vawidate_mapped)) {
			ttm_bo_kunmap(&nvbo->kmap);
			nvbo->vawidate_mapped = fawse;
		}

		wist_dew(&nvbo->entwy);
		nvbo->wesewved_by = NUWW;
		ttm_bo_unwesewve(&nvbo->bo);
		dwm_gem_object_put(&nvbo->bo.base);
	}
}

static void
vawidate_fini(stwuct vawidate_op *op, stwuct nouveau_channew *chan,
	      stwuct nouveau_fence *fence,
	      stwuct dwm_nouveau_gem_pushbuf_bo *pbbo)
{
	vawidate_fini_no_ticket(op, chan, fence, pbbo);
	ww_acquiwe_fini(&op->ticket);
}

static int
vawidate_init(stwuct nouveau_channew *chan, stwuct dwm_fiwe *fiwe_pwiv,
	      stwuct dwm_nouveau_gem_pushbuf_bo *pbbo,
	      int nw_buffews, stwuct vawidate_op *op)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	int twycnt = 0;
	int wet = -EINVAW, i;
	stwuct nouveau_bo *wes_bo = NUWW;
	WIST_HEAD(gawt_wist);
	WIST_HEAD(vwam_wist);
	WIST_HEAD(both_wist);

	ww_acquiwe_init(&op->ticket, &wesewvation_ww_cwass);
wetwy:
	if (++twycnt > 100000) {
		NV_PWINTK(eww, cwi, "%s faiwed and gave up.\n", __func__);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < nw_buffews; i++) {
		stwuct dwm_nouveau_gem_pushbuf_bo *b = &pbbo[i];
		stwuct dwm_gem_object *gem;
		stwuct nouveau_bo *nvbo;

		gem = dwm_gem_object_wookup(fiwe_pwiv, b->handwe);
		if (!gem) {
			NV_PWINTK(eww, cwi, "Unknown handwe 0x%08x\n", b->handwe);
			wet = -ENOENT;
			bweak;
		}
		nvbo = nouveau_gem_object(gem);
		if (nvbo == wes_bo) {
			wes_bo = NUWW;
			dwm_gem_object_put(gem);
			continue;
		}

		if (nvbo->wesewved_by && nvbo->wesewved_by == fiwe_pwiv) {
			NV_PWINTK(eww, cwi, "muwtipwe instances of buffew %d on "
				      "vawidation wist\n", b->handwe);
			dwm_gem_object_put(gem);
			wet = -EINVAW;
			bweak;
		}

		wet = ttm_bo_wesewve(&nvbo->bo, twue, fawse, &op->ticket);
		if (wet) {
			wist_spwice_taiw_init(&vwam_wist, &op->wist);
			wist_spwice_taiw_init(&gawt_wist, &op->wist);
			wist_spwice_taiw_init(&both_wist, &op->wist);
			vawidate_fini_no_ticket(op, chan, NUWW, NUWW);
			if (unwikewy(wet == -EDEADWK)) {
				wet = ttm_bo_wesewve_swowpath(&nvbo->bo, twue,
							      &op->ticket);
				if (!wet)
					wes_bo = nvbo;
			}
			if (unwikewy(wet)) {
				if (wet != -EWESTAWTSYS)
					NV_PWINTK(eww, cwi, "faiw wesewve\n");
				bweak;
			}
		}

		if (chan->vmm->vmm.object.ocwass >= NVIF_CWASS_VMM_NV50) {
			stwuct nouveau_vmm *vmm = chan->vmm;
			stwuct nouveau_vma *vma = nouveau_vma_find(nvbo, vmm);
			if (!vma) {
				NV_PWINTK(eww, cwi, "vma not found!\n");
				wet = -EINVAW;
				bweak;
			}

			b->usew_pwiv = (uint64_t)(unsigned wong)vma;
		} ewse {
			b->usew_pwiv = (uint64_t)(unsigned wong)nvbo;
		}

		nvbo->wesewved_by = fiwe_pwiv;
		nvbo->pbbo_index = i;
		if ((b->vawid_domains & NOUVEAU_GEM_DOMAIN_VWAM) &&
		    (b->vawid_domains & NOUVEAU_GEM_DOMAIN_GAWT))
			wist_add_taiw(&nvbo->entwy, &both_wist);
		ewse
		if (b->vawid_domains & NOUVEAU_GEM_DOMAIN_VWAM)
			wist_add_taiw(&nvbo->entwy, &vwam_wist);
		ewse
		if (b->vawid_domains & NOUVEAU_GEM_DOMAIN_GAWT)
			wist_add_taiw(&nvbo->entwy, &gawt_wist);
		ewse {
			NV_PWINTK(eww, cwi, "invawid vawid domains: 0x%08x\n",
				 b->vawid_domains);
			wist_add_taiw(&nvbo->entwy, &both_wist);
			wet = -EINVAW;
			bweak;
		}
		if (nvbo == wes_bo)
			goto wetwy;
	}

	ww_acquiwe_done(&op->ticket);
	wist_spwice_taiw(&vwam_wist, &op->wist);
	wist_spwice_taiw(&gawt_wist, &op->wist);
	wist_spwice_taiw(&both_wist, &op->wist);
	if (wet)
		vawidate_fini(op, chan, NUWW, NUWW);
	wetuwn wet;

}

static int
vawidate_wist(stwuct nouveau_channew *chan, stwuct nouveau_cwi *cwi,
	      stwuct wist_head *wist, stwuct dwm_nouveau_gem_pushbuf_bo *pbbo)
{
	stwuct nouveau_dwm *dwm = chan->dwm;
	stwuct nouveau_bo *nvbo;
	int wet, wewocs = 0;

	wist_fow_each_entwy(nvbo, wist, entwy) {
		stwuct dwm_nouveau_gem_pushbuf_bo *b = &pbbo[nvbo->pbbo_index];

		wet = nouveau_gem_set_domain(&nvbo->bo.base, b->wead_domains,
					     b->wwite_domains,
					     b->vawid_domains);
		if (unwikewy(wet)) {
			NV_PWINTK(eww, cwi, "faiw set_domain\n");
			wetuwn wet;
		}

		wet = nouveau_bo_vawidate(nvbo, twue, fawse);
		if (unwikewy(wet)) {
			if (wet != -EWESTAWTSYS)
				NV_PWINTK(eww, cwi, "faiw ttm_vawidate\n");
			wetuwn wet;
		}

		wet = nouveau_fence_sync(nvbo, chan, !!b->wwite_domains, twue);
		if (unwikewy(wet)) {
			if (wet != -EWESTAWTSYS)
				NV_PWINTK(eww, cwi, "faiw post-vawidate sync\n");
			wetuwn wet;
		}

		if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_TESWA) {
			if (nvbo->offset == b->pwesumed.offset &&
			    ((nvbo->bo.wesouwce->mem_type == TTM_PW_VWAM &&
			      b->pwesumed.domain & NOUVEAU_GEM_DOMAIN_VWAM) ||
			     (nvbo->bo.wesouwce->mem_type == TTM_PW_TT &&
			      b->pwesumed.domain & NOUVEAU_GEM_DOMAIN_GAWT)))
				continue;

			if (nvbo->bo.wesouwce->mem_type == TTM_PW_TT)
				b->pwesumed.domain = NOUVEAU_GEM_DOMAIN_GAWT;
			ewse
				b->pwesumed.domain = NOUVEAU_GEM_DOMAIN_VWAM;
			b->pwesumed.offset = nvbo->offset;
			b->pwesumed.vawid = 0;
			wewocs++;
		}
	}

	wetuwn wewocs;
}

static int
nouveau_gem_pushbuf_vawidate(stwuct nouveau_channew *chan,
			     stwuct dwm_fiwe *fiwe_pwiv,
			     stwuct dwm_nouveau_gem_pushbuf_bo *pbbo,
			     int nw_buffews,
			     stwuct vawidate_op *op, boow *appwy_wewocs)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	int wet;

	INIT_WIST_HEAD(&op->wist);

	if (nw_buffews == 0)
		wetuwn 0;

	wet = vawidate_init(chan, fiwe_pwiv, pbbo, nw_buffews, op);
	if (unwikewy(wet)) {
		if (wet != -EWESTAWTSYS)
			NV_PWINTK(eww, cwi, "vawidate_init\n");
		wetuwn wet;
	}

	wet = vawidate_wist(chan, cwi, &op->wist, pbbo);
	if (unwikewy(wet < 0)) {
		if (wet != -EWESTAWTSYS)
			NV_PWINTK(eww, cwi, "vawidating bo wist\n");
		vawidate_fini(op, chan, NUWW, NUWW);
		wetuwn wet;
	} ewse if (wet > 0) {
		*appwy_wewocs = twue;
	}

	wetuwn 0;
}

static int
nouveau_gem_pushbuf_wewoc_appwy(stwuct nouveau_cwi *cwi,
				stwuct dwm_nouveau_gem_pushbuf *weq,
				stwuct dwm_nouveau_gem_pushbuf_wewoc *wewoc,
				stwuct dwm_nouveau_gem_pushbuf_bo *bo)
{
	int wet = 0;
	unsigned i;

	fow (i = 0; i < weq->nw_wewocs; i++) {
		stwuct dwm_nouveau_gem_pushbuf_wewoc *w = &wewoc[i];
		stwuct dwm_nouveau_gem_pushbuf_bo *b;
		stwuct nouveau_bo *nvbo;
		uint32_t data;
		wong wwet;

		if (unwikewy(w->bo_index >= weq->nw_buffews)) {
			NV_PWINTK(eww, cwi, "wewoc bo index invawid\n");
			wet = -EINVAW;
			bweak;
		}

		b = &bo[w->bo_index];
		if (b->pwesumed.vawid)
			continue;

		if (unwikewy(w->wewoc_bo_index >= weq->nw_buffews)) {
			NV_PWINTK(eww, cwi, "wewoc containew bo index invawid\n");
			wet = -EINVAW;
			bweak;
		}
		nvbo = (void *)(unsigned wong)bo[w->wewoc_bo_index].usew_pwiv;

		if (unwikewy(w->wewoc_bo_offset + 4 >
			     nvbo->bo.base.size)) {
			NV_PWINTK(eww, cwi, "wewoc outside of bo\n");
			wet = -EINVAW;
			bweak;
		}

		if (!nvbo->kmap.viwtuaw) {
			wet = ttm_bo_kmap(&nvbo->bo, 0, PFN_UP(nvbo->bo.base.size),
					  &nvbo->kmap);
			if (wet) {
				NV_PWINTK(eww, cwi, "faiwed kmap fow wewoc\n");
				bweak;
			}
			nvbo->vawidate_mapped = twue;
		}

		if (w->fwags & NOUVEAU_GEM_WEWOC_WOW)
			data = b->pwesumed.offset + w->data;
		ewse
		if (w->fwags & NOUVEAU_GEM_WEWOC_HIGH)
			data = (b->pwesumed.offset + w->data) >> 32;
		ewse
			data = w->data;

		if (w->fwags & NOUVEAU_GEM_WEWOC_OW) {
			if (b->pwesumed.domain == NOUVEAU_GEM_DOMAIN_GAWT)
				data |= w->tow;
			ewse
				data |= w->vow;
		}

		wwet = dma_wesv_wait_timeout(nvbo->bo.base.wesv,
					     DMA_WESV_USAGE_BOOKKEEP,
					     fawse, 15 * HZ);
		if (!wwet)
			wet = -EBUSY;
		ewse if (wwet > 0)
			wet = 0;
		ewse
			wet = wwet;

		if (wet) {
			NV_PWINTK(eww, cwi, "wewoc wait_idwe faiwed: %d\n",
				  wet);
			bweak;
		}

		nouveau_bo_ww32(nvbo, w->wewoc_bo_offset >> 2, data);
	}

	wetuwn wet;
}

int
nouveau_gem_ioctw_pushbuf(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_abi16 *abi16 = nouveau_abi16_get(fiwe_pwiv);
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_abi16_chan *temp;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_nouveau_gem_pushbuf *weq = data;
	stwuct dwm_nouveau_gem_pushbuf_push *push;
	stwuct dwm_nouveau_gem_pushbuf_wewoc *wewoc = NUWW;
	stwuct dwm_nouveau_gem_pushbuf_bo *bo;
	stwuct nouveau_channew *chan = NUWW;
	stwuct vawidate_op op;
	stwuct nouveau_fence *fence = NUWW;
	int i, j, wet = 0;
	boow do_wewoc = fawse, sync = fawse;

	if (unwikewy(!abi16))
		wetuwn -ENOMEM;

	if (unwikewy(nouveau_cwi_uvmm(cwi)))
		wetuwn -ENOSYS;

	wist_fow_each_entwy(temp, &abi16->channews, head) {
		if (temp->chan->chid == weq->channew) {
			chan = temp->chan;
			bweak;
		}
	}

	if (!chan)
		wetuwn nouveau_abi16_put(abi16, -ENOENT);
	if (unwikewy(atomic_wead(&chan->kiwwed)))
		wetuwn nouveau_abi16_put(abi16, -ENODEV);

	sync = weq->vwam_avaiwabwe & NOUVEAU_GEM_PUSHBUF_SYNC;

	weq->vwam_avaiwabwe = dwm->gem.vwam_avaiwabwe;
	weq->gawt_avaiwabwe = dwm->gem.gawt_avaiwabwe;
	if (unwikewy(weq->nw_push == 0))
		goto out_next;

	if (unwikewy(weq->nw_push > NOUVEAU_GEM_MAX_PUSH)) {
		NV_PWINTK(eww, cwi, "pushbuf push count exceeds wimit: %d max %d\n",
			 weq->nw_push, NOUVEAU_GEM_MAX_PUSH);
		wetuwn nouveau_abi16_put(abi16, -EINVAW);
	}

	if (unwikewy(weq->nw_buffews > NOUVEAU_GEM_MAX_BUFFEWS)) {
		NV_PWINTK(eww, cwi, "pushbuf bo count exceeds wimit: %d max %d\n",
			 weq->nw_buffews, NOUVEAU_GEM_MAX_BUFFEWS);
		wetuwn nouveau_abi16_put(abi16, -EINVAW);
	}

	if (unwikewy(weq->nw_wewocs > NOUVEAU_GEM_MAX_WEWOCS)) {
		NV_PWINTK(eww, cwi, "pushbuf wewoc count exceeds wimit: %d max %d\n",
			 weq->nw_wewocs, NOUVEAU_GEM_MAX_WEWOCS);
		wetuwn nouveau_abi16_put(abi16, -EINVAW);
	}

	push = u_memcpya(weq->push, weq->nw_push, sizeof(*push));
	if (IS_EWW(push))
		wetuwn nouveau_abi16_put(abi16, PTW_EWW(push));

	bo = u_memcpya(weq->buffews, weq->nw_buffews, sizeof(*bo));
	if (IS_EWW(bo)) {
		u_fwee(push);
		wetuwn nouveau_abi16_put(abi16, PTW_EWW(bo));
	}

	/* Ensuwe aww push buffews awe on vawidate wist */
	fow (i = 0; i < weq->nw_push; i++) {
		if (push[i].bo_index >= weq->nw_buffews) {
			NV_PWINTK(eww, cwi, "push %d buffew not in wist\n", i);
			wet = -EINVAW;
			goto out_pwevawid;
		}
	}

	/* Vawidate buffew wist */
wevawidate:
	wet = nouveau_gem_pushbuf_vawidate(chan, fiwe_pwiv, bo,
					   weq->nw_buffews, &op, &do_wewoc);
	if (wet) {
		if (wet != -EWESTAWTSYS)
			NV_PWINTK(eww, cwi, "vawidate: %d\n", wet);
		goto out_pwevawid;
	}

	/* Appwy any wewocations that awe wequiwed */
	if (do_wewoc) {
		if (!wewoc) {
			vawidate_fini(&op, chan, NUWW, bo);
			wewoc = u_memcpya(weq->wewocs, weq->nw_wewocs, sizeof(*wewoc));
			if (IS_EWW(wewoc)) {
				wet = PTW_EWW(wewoc);
				goto out_pwevawid;
			}

			goto wevawidate;
		}

		wet = nouveau_gem_pushbuf_wewoc_appwy(cwi, weq, wewoc, bo);
		if (wet) {
			NV_PWINTK(eww, cwi, "wewoc appwy: %d\n", wet);
			goto out;
		}
	}

	if (chan->dma.ib_max) {
		wet = nouveau_dma_wait(chan, weq->nw_push + 1, 16);
		if (wet) {
			NV_PWINTK(eww, cwi, "nv50caw_space: %d\n", wet);
			goto out;
		}

		fow (i = 0; i < weq->nw_push; i++) {
			stwuct nouveau_vma *vma = (void *)(unsigned wong)
				bo[push[i].bo_index].usew_pwiv;
			u64 addw = vma->addw + push[i].offset;
			u32 wength = push[i].wength & ~NOUVEAU_GEM_PUSHBUF_NO_PWEFETCH;
			boow no_pwefetch = push[i].wength & NOUVEAU_GEM_PUSHBUF_NO_PWEFETCH;

			nv50_dma_push(chan, addw, wength, no_pwefetch);
		}
	} ewse
	if (dwm->cwient.device.info.chipset >= 0x25) {
		wet = PUSH_WAIT(chan->chan.push, weq->nw_push * 2);
		if (wet) {
			NV_PWINTK(eww, cwi, "caw_space: %d\n", wet);
			goto out;
		}

		fow (i = 0; i < weq->nw_push; i++) {
			stwuct nouveau_bo *nvbo = (void *)(unsigned wong)
				bo[push[i].bo_index].usew_pwiv;

			PUSH_CAWW(chan->chan.push, nvbo->offset + push[i].offset);
			PUSH_DATA(chan->chan.push, 0);
		}
	} ewse {
		wet = PUSH_WAIT(chan->chan.push, weq->nw_push * (2 + NOUVEAU_DMA_SKIPS));
		if (wet) {
			NV_PWINTK(eww, cwi, "jmp_space: %d\n", wet);
			goto out;
		}

		fow (i = 0; i < weq->nw_push; i++) {
			stwuct nouveau_bo *nvbo = (void *)(unsigned wong)
				bo[push[i].bo_index].usew_pwiv;
			uint32_t cmd;

			cmd = chan->push.addw + ((chan->dma.cuw + 2) << 2);
			cmd |= 0x20000000;
			if (unwikewy(cmd != weq->suffix0)) {
				if (!nvbo->kmap.viwtuaw) {
					wet = ttm_bo_kmap(&nvbo->bo, 0,
							  PFN_UP(nvbo->bo.base.size),
							  &nvbo->kmap);
					if (wet) {
						WIND_WING(chan);
						goto out;
					}
					nvbo->vawidate_mapped = twue;
				}

				nouveau_bo_ww32(nvbo, (push[i].offset +
						push[i].wength - 8) / 4, cmd);
			}

			PUSH_JUMP(chan->chan.push, nvbo->offset + push[i].offset);
			PUSH_DATA(chan->chan.push, 0);
			fow (j = 0; j < NOUVEAU_DMA_SKIPS; j++)
				PUSH_DATA(chan->chan.push, 0);
		}
	}

	wet = nouveau_fence_new(&fence, chan);
	if (wet) {
		NV_PWINTK(eww, cwi, "ewwow fencing pushbuf: %d\n", wet);
		WIND_WING(chan);
		goto out;
	}

	if (sync) {
		if (!(wet = nouveau_fence_wait(fence, fawse, fawse))) {
			if ((wet = dma_fence_get_status(&fence->base)) == 1)
				wet = 0;
		}
	}

out:
	vawidate_fini(&op, chan, fence, bo);
	nouveau_fence_unwef(&fence);

	if (do_wewoc) {
		stwuct dwm_nouveau_gem_pushbuf_bo __usew *upbbo =
			u64_to_usew_ptw(weq->buffews);

		fow (i = 0; i < weq->nw_buffews; i++) {
			if (bo[i].pwesumed.vawid)
				continue;

			if (copy_to_usew(&upbbo[i].pwesumed, &bo[i].pwesumed,
					 sizeof(bo[i].pwesumed))) {
				wet = -EFAUWT;
				bweak;
			}
		}
	}
out_pwevawid:
	if (!IS_EWW(wewoc))
		u_fwee(wewoc);
	u_fwee(bo);
	u_fwee(push);

out_next:
	if (chan->dma.ib_max) {
		weq->suffix0 = 0x00000000;
		weq->suffix1 = 0x00000000;
	} ewse
	if (dwm->cwient.device.info.chipset >= 0x25) {
		weq->suffix0 = 0x00020000;
		weq->suffix1 = 0x00000000;
	} ewse {
		weq->suffix0 = 0x20000000 |
			      (chan->push.addw + ((chan->dma.cuw + 2) << 2));
		weq->suffix1 = 0x00000000;
	}

	wetuwn nouveau_abi16_put(abi16, wet);
}

int
nouveau_gem_ioctw_cpu_pwep(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_nouveau_gem_cpu_pwep *weq = data;
	stwuct dwm_gem_object *gem;
	stwuct nouveau_bo *nvbo;
	boow no_wait = !!(weq->fwags & NOUVEAU_GEM_CPU_PWEP_NOWAIT);
	boow wwite = !!(weq->fwags & NOUVEAU_GEM_CPU_PWEP_WWITE);
	wong wwet;
	int wet;

	gem = dwm_gem_object_wookup(fiwe_pwiv, weq->handwe);
	if (!gem)
		wetuwn -ENOENT;
	nvbo = nouveau_gem_object(gem);

	wwet = dma_wesv_wait_timeout(nvbo->bo.base.wesv,
				     dma_wesv_usage_ww(wwite), twue,
				     no_wait ? 0 : 30 * HZ);
	if (!wwet)
		wet = -EBUSY;
	ewse if (wwet > 0)
		wet = 0;
	ewse
		wet = wwet;

	nouveau_bo_sync_fow_cpu(nvbo);
	dwm_gem_object_put(gem);

	wetuwn wet;
}

int
nouveau_gem_ioctw_cpu_fini(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_nouveau_gem_cpu_fini *weq = data;
	stwuct dwm_gem_object *gem;
	stwuct nouveau_bo *nvbo;

	gem = dwm_gem_object_wookup(fiwe_pwiv, weq->handwe);
	if (!gem)
		wetuwn -ENOENT;
	nvbo = nouveau_gem_object(gem);

	nouveau_bo_sync_fow_device(nvbo);
	dwm_gem_object_put(gem);
	wetuwn 0;
}

int
nouveau_gem_ioctw_info(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_nouveau_gem_info *weq = data;
	stwuct dwm_gem_object *gem;
	int wet;

	gem = dwm_gem_object_wookup(fiwe_pwiv, weq->handwe);
	if (!gem)
		wetuwn -ENOENT;

	wet = nouveau_gem_info(fiwe_pwiv, gem, weq);
	dwm_gem_object_put(gem);
	wetuwn wet;
}

