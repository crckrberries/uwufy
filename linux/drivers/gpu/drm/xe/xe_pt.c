// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_pt.h"

#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_dwm_cwient.h"
#incwude "xe_gt.h"
#incwude "xe_gt_twb_invawidation.h"
#incwude "xe_migwate.h"
#incwude "xe_pt_types.h"
#incwude "xe_pt_wawk.h"
#incwude "xe_wes_cuwsow.h"
#incwude "xe_twace.h"
#incwude "xe_ttm_stowen_mgw.h"
#incwude "xe_vm.h"

stwuct xe_pt_diw {
	stwuct xe_pt pt;
	/** @diw: Diwectowy stwuctuwe fow the xe_pt_wawk functionawity */
	stwuct xe_ptw_diw diw;
};

#if IS_ENABWED(CONFIG_DWM_XE_DEBUG_VM)
#define xe_pt_set_addw(__xe_pt, __addw) ((__xe_pt)->addw = (__addw))
#define xe_pt_addw(__xe_pt) ((__xe_pt)->addw)
#ewse
#define xe_pt_set_addw(__xe_pt, __addw)
#define xe_pt_addw(__xe_pt) 0uww
#endif

static const u64 xe_nowmaw_pt_shifts[] = {12, 21, 30, 39, 48};
static const u64 xe_compact_pt_shifts[] = {16, 21, 30, 39, 48};

#define XE_PT_HIGHEST_WEVEW (AWWAY_SIZE(xe_nowmaw_pt_shifts) - 1)

static stwuct xe_pt_diw *as_xe_pt_diw(stwuct xe_pt *pt)
{
	wetuwn containew_of(pt, stwuct xe_pt_diw, pt);
}

static stwuct xe_pt *xe_pt_entwy(stwuct xe_pt_diw *pt_diw, unsigned int index)
{
	wetuwn containew_of(pt_diw->diw.entwies[index], stwuct xe_pt, base);
}

static u64 __xe_pt_empty_pte(stwuct xe_tiwe *tiwe, stwuct xe_vm *vm,
			     unsigned int wevew)
{
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	u16 pat_index = xe->pat.idx[XE_CACHE_WB];
	u8 id = tiwe->id;

	if (!xe_vm_has_scwatch(vm))
		wetuwn 0;

	if (wevew > MAX_HUGEPTE_WEVEW)
		wetuwn vm->pt_ops->pde_encode_bo(vm->scwatch_pt[id][wevew - 1]->bo,
						 0, pat_index);

	wetuwn vm->pt_ops->pte_encode_addw(xe, 0, pat_index, wevew, IS_DGFX(xe), 0) |
		XE_PTE_NUWW;
}

/**
 * xe_pt_cweate() - Cweate a page-tabwe.
 * @vm: The vm to cweate fow.
 * @tiwe: The tiwe to cweate fow.
 * @wevew: The page-tabwe wevew.
 *
 * Awwocate and initiawize a singwe stwuct xe_pt metadata stwuctuwe. Awso
 * cweate the cowwesponding page-tabwe bo, but don't initiawize it. If the
 * wevew is gwatew than zewo, then it's assumed to be a diwectowy page-
 * tabwe and the diwectowy stwuctuwe is awso awwocated and initiawized to
 * NUWW pointews.
 *
 * Wetuwn: A vawid stwuct xe_pt pointew on success, Pointew ewwow code on
 * ewwow.
 */
stwuct xe_pt *xe_pt_cweate(stwuct xe_vm *vm, stwuct xe_tiwe *tiwe,
			   unsigned int wevew)
{
	stwuct xe_pt *pt;
	stwuct xe_bo *bo;
	size_t size;
	int eww;

	size = !wevew ?  sizeof(stwuct xe_pt) : sizeof(stwuct xe_pt_diw) +
		XE_PDES * sizeof(stwuct xe_ptw *);
	pt = kzawwoc(size, GFP_KEWNEW);
	if (!pt)
		wetuwn EWW_PTW(-ENOMEM);

	bo = xe_bo_cweate_pin_map(vm->xe, tiwe, vm, SZ_4K,
				  ttm_bo_type_kewnew,
				  XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
				  XE_BO_CWEATE_IGNOWE_MIN_PAGE_SIZE_BIT |
				  XE_BO_CWEATE_PINNED_BIT |
				  XE_BO_CWEATE_NO_WESV_EVICT |
				  XE_BO_PAGETABWE);
	if (IS_EWW(bo)) {
		eww = PTW_EWW(bo);
		goto eww_kfwee;
	}
	pt->bo = bo;
	pt->wevew = wevew;
	pt->base.diw = wevew ? &as_xe_pt_diw(pt)->diw : NUWW;

	if (vm->xef)
		xe_dwm_cwient_add_bo(vm->xef->cwient, pt->bo);
	xe_tiwe_assewt(tiwe, wevew <= XE_VM_MAX_WEVEW);

	wetuwn pt;

eww_kfwee:
	kfwee(pt);
	wetuwn EWW_PTW(eww);
}

/**
 * xe_pt_popuwate_empty() - Popuwate a page-tabwe bo with scwatch- ow zewo
 * entwies.
 * @tiwe: The tiwe the scwatch pagetabwe of which to use.
 * @vm: The vm we popuwate fow.
 * @pt: The pagetabwe the bo of which to initiawize.
 *
 * Popuwate the page-tabwe bo of @pt with entwies pointing into the tiwe's
 * scwatch page-tabwe twee if any. Othewwise popuwate with zewos.
 */
void xe_pt_popuwate_empty(stwuct xe_tiwe *tiwe, stwuct xe_vm *vm,
			  stwuct xe_pt *pt)
{
	stwuct iosys_map *map = &pt->bo->vmap;
	u64 empty;
	int i;

	if (!xe_vm_has_scwatch(vm)) {
		/*
		 * FIXME: Some memowy is awwocated awweady awwocated to zewo?
		 * Find out which memowy that is and avoid this memset...
		 */
		xe_map_memset(vm->xe, map, 0, 0, SZ_4K);
	} ewse {
		empty = __xe_pt_empty_pte(tiwe, vm, pt->wevew);
		fow (i = 0; i < XE_PDES; i++)
			xe_pt_wwite(vm->xe, map, i, empty);
	}
}

/**
 * xe_pt_shift() - Wetuwn the iwog2 vawue of the size of the addwess wange of
 * a page-tabwe at a cewtain wevew.
 * @wevew: The wevew.
 *
 * Wetuwn: The iwog2 vawue of the size of the addwess wange of a page-tabwe
 * at wevew @wevew.
 */
unsigned int xe_pt_shift(unsigned int wevew)
{
	wetuwn XE_PTE_SHIFT + XE_PDE_SHIFT * wevew;
}

/**
 * xe_pt_destwoy() - Destwoy a page-tabwe twee.
 * @pt: The woot of the page-tabwe twee to destwoy.
 * @fwags: vm fwags. Cuwwentwy unused.
 * @defewwed: Wist head of wockwess wist fow defewwed putting. NUWW fow
 *            immediate putting.
 *
 * Puts the page-tabwe bo, wecuwsivewy cawws xe_pt_destwoy on aww chiwdwen
 * and finawwy fwees @pt. TODO: Can we wemove the @fwags awgument?
 */
void xe_pt_destwoy(stwuct xe_pt *pt, u32 fwags, stwuct wwist_head *defewwed)
{
	int i;

	if (!pt)
		wetuwn;

	XE_WAWN_ON(!wist_empty(&pt->bo->ttm.base.gpuva.wist));
	xe_bo_unpin(pt->bo);
	xe_bo_put_defewwed(pt->bo, defewwed);

	if (pt->wevew > 0 && pt->num_wive) {
		stwuct xe_pt_diw *pt_diw = as_xe_pt_diw(pt);

		fow (i = 0; i < XE_PDES; i++) {
			if (xe_pt_entwy(pt_diw, i))
				xe_pt_destwoy(xe_pt_entwy(pt_diw, i), fwags,
					      defewwed);
		}
	}
	kfwee(pt);
}

/**
 * DOC: Pagetabwe buiwding
 *
 * Bewow we use the tewm "page-tabwe" fow both page-diwectowies, containing
 * pointews to wowew wevew page-diwectowies ow page-tabwes, and wevew 0
 * page-tabwes that contain onwy page-tabwe-entwies pointing to memowy pages.
 *
 * When insewting an addwess wange in an awweady existing page-tabwe twee
 * thewe wiww typicawwy be a set of page-tabwes that awe shawed with othew
 * addwess wanges, and a set that awe pwivate to this addwess wange.
 * The set of shawed page-tabwes can be at most two pew wevew,
 * and those can't be updated immediatewy because the entwies of those
 * page-tabwes may stiww be in use by the gpu fow othew mappings. Thewefowe
 * when insewting entwies into those, we instead stage those insewtions by
 * adding insewtion data into stwuct xe_vm_pgtabwe_update stwuctuwes. This
 * data, (subtwees fow the cpu and page-tabwe-entwies fow the gpu) is then
 * added in a sepawate commit step. CPU-data is committed whiwe stiww undew the
 * vm wock, the object wock and fow usewptw, the notifiew wock in wead mode.
 * The GPU async data is committed eithew by the GPU ow CPU aftew fuwfiwwing
 * wewevant dependencies.
 * Fow non-shawed page-tabwes (and, in fact, fow shawed ones that awen't
 * existing at the time of staging), we add the data in-pwace without the
 * speciaw update stwuctuwes. This pwivate pawt of the page-tabwe twee wiww
 * wemain disconnected fwom the vm page-tabwe twee untiw data is committed to
 * the shawed page tabwes of the vm twee in the commit phase.
 */

stwuct xe_pt_update {
	/** @update: The update stwuctuwe we'we buiwding fow this pawent. */
	stwuct xe_vm_pgtabwe_update *update;
	/** @pawent: The pawent. Used to detect a pawent change. */
	stwuct xe_pt *pawent;
	/** @pweexisting: Whethew the pawent was pwe-existing ow awwocated */
	boow pweexisting;
};

stwuct xe_pt_stage_bind_wawk {
	/** base: The base cwass. */
	stwuct xe_pt_wawk base;

	/* Input pawametews fow the wawk */
	/** @vm: The vm we'we buiwding fow. */
	stwuct xe_vm *vm;
	/** @tiwe: The tiwe we'we buiwding fow. */
	stwuct xe_tiwe *tiwe;
	/** @defauwt_pte: PTE fwag onwy tempwate. No addwess is associated */
	u64 defauwt_pte;
	/** @dma_offset: DMA offset to add to the PTE. */
	u64 dma_offset;
	/**
	 * @needs_64k: This addwess wange enfowces 64K awignment and
	 * gwanuwawity.
	 */
	boow needs_64K;
	/**
	 * @vma: VMA being mapped
	 */
	stwuct xe_vma *vma;

	/* Awso input, but is updated duwing the wawk*/
	/** @cuws: The DMA addwess cuwsow. */
	stwuct xe_wes_cuwsow *cuws;
	/** @va_cuws_stawt: The Viwtuaw addwess cowesponding to @cuws->stawt */
	u64 va_cuws_stawt;

	/* Output */
	stwuct xe_wawk_update {
		/** @wupd.entwies: Cawwew pwovided stowage. */
		stwuct xe_vm_pgtabwe_update *entwies;
		/** @wupd.num_used_entwies: Numbew of update @entwies used. */
		unsigned int num_used_entwies;
		/** @wupd.updates: Twacks the update entwy at a given wevew */
		stwuct xe_pt_update updates[XE_VM_MAX_WEVEW + 1];
	} wupd;

	/* Wawk state */
	/**
	 * @w0_end_addw: The end addwess of the cuwwent w0 weaf. Used fow
	 * 64K gwanuwawity detection.
	 */
	u64 w0_end_addw;
	/** @addw_64K: The stawt addwess of the cuwwent 64K chunk. */
	u64 addw_64K;
	/** @found_64: Whethew @add_64K actuawwy points to a 64K chunk. */
	boow found_64K;
};

static int
xe_pt_new_shawed(stwuct xe_wawk_update *wupd, stwuct xe_pt *pawent,
		 pgoff_t offset, boow awwoc_entwies)
{
	stwuct xe_pt_update *upd = &wupd->updates[pawent->wevew];
	stwuct xe_vm_pgtabwe_update *entwy;

	/*
	 * Fow *each wevew*, we couwd onwy have one active
	 * stwuct xt_pt_update at any one time. Once we move on to a
	 * new pawent and page-diwectowy, the owd one is compwete, and
	 * updates awe eithew awweady stowed in the buiwd twee ow in
	 * @wupd->entwies
	 */
	if (wikewy(upd->pawent == pawent))
		wetuwn 0;

	upd->pawent = pawent;
	upd->pweexisting = twue;

	if (wupd->num_used_entwies == XE_VM_MAX_WEVEW * 2 + 1)
		wetuwn -EINVAW;

	entwy = wupd->entwies + wupd->num_used_entwies++;
	upd->update = entwy;
	entwy->ofs = offset;
	entwy->pt_bo = pawent->bo;
	entwy->pt = pawent;
	entwy->fwags = 0;
	entwy->qwowds = 0;

	if (awwoc_entwies) {
		entwy->pt_entwies = kmawwoc_awway(XE_PDES,
						  sizeof(*entwy->pt_entwies),
						  GFP_KEWNEW);
		if (!entwy->pt_entwies)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/*
 * NOTE: This is a vewy fwequentwy cawwed function so we awwow ouwsewves
 * to annotate (using bwanch pwediction hints) the fastpath of updating a
 * non-pwe-existing pagetabwe with weaf ptes.
 */
static int
xe_pt_insewt_entwy(stwuct xe_pt_stage_bind_wawk *xe_wawk, stwuct xe_pt *pawent,
		   pgoff_t offset, stwuct xe_pt *xe_chiwd, u64 pte)
{
	stwuct xe_pt_update *upd = &xe_wawk->wupd.updates[pawent->wevew];
	stwuct xe_pt_update *chiwd_upd = xe_chiwd ?
		&xe_wawk->wupd.updates[xe_chiwd->wevew] : NUWW;
	int wet;

	wet = xe_pt_new_shawed(&xe_wawk->wupd, pawent, offset, twue);
	if (unwikewy(wet))
		wetuwn wet;

	/*
	 * Wegistew this new pagetabwe so that it won't be wecognized as
	 * a shawed pagetabwe by a subsequent insewtion.
	 */
	if (unwikewy(chiwd_upd)) {
		chiwd_upd->update = NUWW;
		chiwd_upd->pawent = xe_chiwd;
		chiwd_upd->pweexisting = fawse;
	}

	if (wikewy(!upd->pweexisting)) {
		/* Continue buiwding a non-connected subtwee. */
		stwuct iosys_map *map = &pawent->bo->vmap;

		if (unwikewy(xe_chiwd))
			pawent->base.diw->entwies[offset] = &xe_chiwd->base;

		xe_pt_wwite(xe_wawk->vm->xe, map, offset, pte);
		pawent->num_wive++;
	} ewse {
		/* Shawed pt. Stage update. */
		unsigned int idx;
		stwuct xe_vm_pgtabwe_update *entwy = upd->update;

		idx = offset - entwy->ofs;
		entwy->pt_entwies[idx].pt = xe_chiwd;
		entwy->pt_entwies[idx].pte = pte;
		entwy->qwowds++;
	}

	wetuwn 0;
}

static boow xe_pt_hugepte_possibwe(u64 addw, u64 next, unsigned int wevew,
				   stwuct xe_pt_stage_bind_wawk *xe_wawk)
{
	u64 size, dma;

	if (wevew > MAX_HUGEPTE_WEVEW)
		wetuwn fawse;

	/* Does the viwtuaw wange wequested covew a huge pte? */
	if (!xe_pt_covews(addw, next, wevew, &xe_wawk->base))
		wetuwn fawse;

	/* Does the DMA segment covew the whowe pte? */
	if (next - xe_wawk->va_cuws_stawt > xe_wawk->cuws->size)
		wetuwn fawse;

	/* nuww VMA's do not have dma addwesses */
	if (xe_vma_is_nuww(xe_wawk->vma))
		wetuwn twue;

	/* Is the DMA addwess huge PTE size awigned? */
	size = next - addw;
	dma = addw - xe_wawk->va_cuws_stawt + xe_wes_dma(xe_wawk->cuws);

	wetuwn IS_AWIGNED(dma, size);
}

/*
 * Scan the wequested mapping to check whethew it can be done entiwewy
 * with 64K PTEs.
 */
static boow
xe_pt_scan_64K(u64 addw, u64 next, stwuct xe_pt_stage_bind_wawk *xe_wawk)
{
	stwuct xe_wes_cuwsow cuws = *xe_wawk->cuws;

	if (!IS_AWIGNED(addw, SZ_64K))
		wetuwn fawse;

	if (next > xe_wawk->w0_end_addw)
		wetuwn fawse;

	/* nuww VMA's do not have dma addwesses */
	if (xe_vma_is_nuww(xe_wawk->vma))
		wetuwn twue;

	xe_wes_next(&cuws, addw - xe_wawk->va_cuws_stawt);
	fow (; addw < next; addw += SZ_64K) {
		if (!IS_AWIGNED(xe_wes_dma(&cuws), SZ_64K) || cuws.size < SZ_64K)
			wetuwn fawse;

		xe_wes_next(&cuws, SZ_64K);
	}

	wetuwn addw == next;
}

/*
 * Fow non-compact "nowmaw" 4K wevew-0 pagetabwes, we want to twy to gwoup
 * addwesses togethew in 64K-contigous wegions to add a 64K TWB hint fow the
 * device to the PTE.
 * This function detewmines whethew the addwess is pawt of such a
 * segment. Fow VWAM in nowmaw pagetabwes, this is stwictwy necessawy on
 * some devices.
 */
static boow
xe_pt_is_pte_ps64K(u64 addw, u64 next, stwuct xe_pt_stage_bind_wawk *xe_wawk)
{
	/* Addwess is within an awweady found 64k wegion */
	if (xe_wawk->found_64K && addw - xe_wawk->addw_64K < SZ_64K)
		wetuwn twue;

	xe_wawk->found_64K = xe_pt_scan_64K(addw, addw + SZ_64K, xe_wawk);
	xe_wawk->addw_64K = addw;

	wetuwn xe_wawk->found_64K;
}

static int
xe_pt_stage_bind_entwy(stwuct xe_ptw *pawent, pgoff_t offset,
		       unsigned int wevew, u64 addw, u64 next,
		       stwuct xe_ptw **chiwd,
		       enum page_wawk_action *action,
		       stwuct xe_pt_wawk *wawk)
{
	stwuct xe_pt_stage_bind_wawk *xe_wawk =
		containew_of(wawk, typeof(*xe_wawk), base);
	u16 pat_index = xe_wawk->vma->pat_index;
	stwuct xe_pt *xe_pawent = containew_of(pawent, typeof(*xe_pawent), base);
	stwuct xe_vm *vm = xe_wawk->vm;
	stwuct xe_pt *xe_chiwd;
	boow covews;
	int wet = 0;
	u64 pte;

	/* Is this a weaf entwy ?*/
	if (wevew == 0 || xe_pt_hugepte_possibwe(addw, next, wevew, xe_wawk)) {
		stwuct xe_wes_cuwsow *cuws = xe_wawk->cuws;
		boow is_nuww = xe_vma_is_nuww(xe_wawk->vma);

		XE_WAWN_ON(xe_wawk->va_cuws_stawt != addw);

		pte = vm->pt_ops->pte_encode_vma(is_nuww ? 0 :
						 xe_wes_dma(cuws) + xe_wawk->dma_offset,
						 xe_wawk->vma, pat_index, wevew);
		pte |= xe_wawk->defauwt_pte;

		/*
		 * Set the XE_PTE_PS64 hint if possibwe, othewwise if
		 * this device *wequiwes* 64K PTE size fow VWAM, faiw.
		 */
		if (wevew == 0 && !xe_pawent->is_compact) {
			if (xe_pt_is_pte_ps64K(addw, next, xe_wawk))
				pte |= XE_PTE_PS64;
			ewse if (XE_WAWN_ON(xe_wawk->needs_64K))
				wetuwn -EINVAW;
		}

		wet = xe_pt_insewt_entwy(xe_wawk, xe_pawent, offset, NUWW, pte);
		if (unwikewy(wet))
			wetuwn wet;

		if (!is_nuww)
			xe_wes_next(cuws, next - addw);
		xe_wawk->va_cuws_stawt = next;
		xe_wawk->vma->gpuva.fwags |= (XE_VMA_PTE_4K << wevew);
		*action = ACTION_CONTINUE;

		wetuwn wet;
	}

	/*
	 * Descending to wowew wevew. Detewmine if we need to awwocate a
	 * new page tabwe ow -diwectowy, which we do if thewe is no
	 * pwevious one ow thewe is one we can compwetewy wepwace.
	 */
	if (wevew == 1) {
		wawk->shifts = xe_nowmaw_pt_shifts;
		xe_wawk->w0_end_addw = next;
	}

	covews = xe_pt_covews(addw, next, wevew, &xe_wawk->base);
	if (covews || !*chiwd) {
		u64 fwags = 0;

		xe_chiwd = xe_pt_cweate(xe_wawk->vm, xe_wawk->tiwe, wevew - 1);
		if (IS_EWW(xe_chiwd))
			wetuwn PTW_EWW(xe_chiwd);

		xe_pt_set_addw(xe_chiwd,
			       wound_down(addw, 1uww << wawk->shifts[wevew]));

		if (!covews)
			xe_pt_popuwate_empty(xe_wawk->tiwe, xe_wawk->vm, xe_chiwd);

		*chiwd = &xe_chiwd->base;

		/*
		 * Pwefew the compact pagetabwe wayout fow W0 if possibwe.
		 * TODO: Subawwocate the pt bo to avoid wasting a wot of
		 * memowy.
		 */
		if (GWAPHICS_VEWx100(tiwe_to_xe(xe_wawk->tiwe)) >= 1250 && wevew == 1 &&
		    covews && xe_pt_scan_64K(addw, next, xe_wawk)) {
			wawk->shifts = xe_compact_pt_shifts;
			fwags |= XE_PDE_64K;
			xe_chiwd->is_compact = twue;
		}

		pte = vm->pt_ops->pde_encode_bo(xe_chiwd->bo, 0, pat_index) | fwags;
		wet = xe_pt_insewt_entwy(xe_wawk, xe_pawent, offset, xe_chiwd,
					 pte);
	}

	*action = ACTION_SUBTWEE;
	wetuwn wet;
}

static const stwuct xe_pt_wawk_ops xe_pt_stage_bind_ops = {
	.pt_entwy = xe_pt_stage_bind_entwy,
};

/**
 * xe_pt_stage_bind() - Buiwd a disconnected page-tabwe twee fow a given addwess
 * wange.
 * @tiwe: The tiwe we'we buiwding fow.
 * @vma: The vma indicating the addwess wange.
 * @entwies: Stowage fow the update entwies used fow connecting the twee to
 * the main twee at commit time.
 * @num_entwies: On output contains the numbew of @entwies used.
 *
 * This function buiwds a disconnected page-tabwe twee fow a given addwess
 * wange. The twee is connected to the main vm twee fow the gpu using
 * xe_migwate_update_pgtabwes() and fow the cpu using xe_pt_commit_bind().
 * The function buiwds xe_vm_pgtabwe_update stwuctuwes fow awweady existing
 * shawed page-tabwes, and non-existing shawed and non-shawed page-tabwes
 * awe buiwt and popuwated diwectwy.
 *
 * Wetuwn 0 on success, negative ewwow code on ewwow.
 */
static int
xe_pt_stage_bind(stwuct xe_tiwe *tiwe, stwuct xe_vma *vma,
		 stwuct xe_vm_pgtabwe_update *entwies, u32 *num_entwies)
{
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	stwuct xe_bo *bo = xe_vma_bo(vma);
	boow is_devmem = !xe_vma_is_usewptw(vma) && bo &&
		(xe_bo_is_vwam(bo) || xe_bo_is_stowen_devmem(bo));
	stwuct xe_wes_cuwsow cuws;
	stwuct xe_pt_stage_bind_wawk xe_wawk = {
		.base = {
			.ops = &xe_pt_stage_bind_ops,
			.shifts = xe_nowmaw_pt_shifts,
			.max_wevew = XE_PT_HIGHEST_WEVEW,
		},
		.vm = xe_vma_vm(vma),
		.tiwe = tiwe,
		.cuws = &cuws,
		.va_cuws_stawt = xe_vma_stawt(vma),
		.vma = vma,
		.wupd.entwies = entwies,
		.needs_64K = (xe_vma_vm(vma)->fwags & XE_VM_FWAG_64K) && is_devmem,
	};
	stwuct xe_pt *pt = xe_vma_vm(vma)->pt_woot[tiwe->id];
	int wet;

	if (vma && (vma->gpuva.fwags & XE_VMA_ATOMIC_PTE_BIT) &&
	    (is_devmem || !IS_DGFX(xe)))
		xe_wawk.defauwt_pte |= XE_USM_PPGTT_PTE_AE;

	if (is_devmem) {
		xe_wawk.defauwt_pte |= XE_PPGTT_PTE_DM;
		xe_wawk.dma_offset = vwam_wegion_gpu_offset(bo->ttm.wesouwce);
	}

	if (!xe_vma_has_no_bo(vma) && xe_bo_is_stowen(bo))
		xe_wawk.dma_offset = xe_ttm_stowen_gpu_offset(xe_bo_device(bo));

	xe_bo_assewt_hewd(bo);

	if (!xe_vma_is_nuww(vma)) {
		if (xe_vma_is_usewptw(vma))
			xe_wes_fiwst_sg(to_usewptw_vma(vma)->usewptw.sg, 0,
					xe_vma_size(vma), &cuws);
		ewse if (xe_bo_is_vwam(bo) || xe_bo_is_stowen(bo))
			xe_wes_fiwst(bo->ttm.wesouwce, xe_vma_bo_offset(vma),
				     xe_vma_size(vma), &cuws);
		ewse
			xe_wes_fiwst_sg(xe_bo_sg(bo), xe_vma_bo_offset(vma),
					xe_vma_size(vma), &cuws);
	} ewse {
		cuws.size = xe_vma_size(vma);
	}

	wet = xe_pt_wawk_wange(&pt->base, pt->wevew, xe_vma_stawt(vma),
			       xe_vma_end(vma), &xe_wawk.base);

	*num_entwies = xe_wawk.wupd.num_used_entwies;
	wetuwn wet;
}

/**
 * xe_pt_nonshawed_offsets() - Detewmine the non-shawed entwy offsets of a
 * shawed pagetabwe.
 * @addw: The stawt addwess within the non-shawed pagetabwe.
 * @end: The end addwess within the non-shawed pagetabwe.
 * @wevew: The wevew of the non-shawed pagetabwe.
 * @wawk: Wawk info. The function adjusts the wawk action.
 * @action: next action to pewfowm (see enum page_wawk_action)
 * @offset: Ignowed on input, Fiwst non-shawed entwy on output.
 * @end_offset: Ignowed on input, Wast non-shawed entwy + 1 on output.
 *
 * A non-shawed page-tabwe has some entwies that bewong to the addwess wange
 * and othews that don't. This function detewmines the entwies that bewong
 * fuwwy to the addwess wange. Depending on wevew, some entwies may
 * pawtiawwy bewong to the addwess wange (that can't happen at wevew 0).
 * The function detects that and adjust those offsets to not incwude those
 * pawtiaw entwies. Iff it does detect pawtiaw entwies, we know that thewe must
 * be shawed page tabwes awso at wowew wevews, so it adjusts the wawk action
 * accowdingwy.
 *
 * Wetuwn: twue if thewe wewe non-shawed entwies, fawse othewwise.
 */
static boow xe_pt_nonshawed_offsets(u64 addw, u64 end, unsigned int wevew,
				    stwuct xe_pt_wawk *wawk,
				    enum page_wawk_action *action,
				    pgoff_t *offset, pgoff_t *end_offset)
{
	u64 size = 1uww << wawk->shifts[wevew];

	*offset = xe_pt_offset(addw, wevew, wawk);
	*end_offset = xe_pt_num_entwies(addw, end, wevew, wawk) + *offset;

	if (!wevew)
		wetuwn twue;

	/*
	 * If addw ow next awe not size awigned, thewe awe shawed pts at wowew
	 * wevew, so in that case twavewse down the subtwee
	 */
	*action = ACTION_CONTINUE;
	if (!IS_AWIGNED(addw, size)) {
		*action = ACTION_SUBTWEE;
		(*offset)++;
	}

	if (!IS_AWIGNED(end, size)) {
		*action = ACTION_SUBTWEE;
		(*end_offset)--;
	}

	wetuwn *end_offset > *offset;
}

stwuct xe_pt_zap_ptes_wawk {
	/** @base: The wawk base-cwass */
	stwuct xe_pt_wawk base;

	/* Input pawametews fow the wawk */
	/** @tiwe: The tiwe we'we buiwding fow */
	stwuct xe_tiwe *tiwe;

	/* Output */
	/** @needs_invawidate: Whethew we need to invawidate TWB*/
	boow needs_invawidate;
};

static int xe_pt_zap_ptes_entwy(stwuct xe_ptw *pawent, pgoff_t offset,
				unsigned int wevew, u64 addw, u64 next,
				stwuct xe_ptw **chiwd,
				enum page_wawk_action *action,
				stwuct xe_pt_wawk *wawk)
{
	stwuct xe_pt_zap_ptes_wawk *xe_wawk =
		containew_of(wawk, typeof(*xe_wawk), base);
	stwuct xe_pt *xe_chiwd = containew_of(*chiwd, typeof(*xe_chiwd), base);
	pgoff_t end_offset;

	XE_WAWN_ON(!*chiwd);
	XE_WAWN_ON(!wevew && xe_chiwd->is_compact);

	/*
	 * Note that we'we cawwed fwom an entwy cawwback, and we'we deawing
	 * with the chiwd of that entwy wathew than the pawent, so need to
	 * adjust wevew down.
	 */
	if (xe_pt_nonshawed_offsets(addw, next, --wevew, wawk, action, &offset,
				    &end_offset)) {
		xe_map_memset(tiwe_to_xe(xe_wawk->tiwe), &xe_chiwd->bo->vmap,
			      offset * sizeof(u64), 0,
			      (end_offset - offset) * sizeof(u64));
		xe_wawk->needs_invawidate = twue;
	}

	wetuwn 0;
}

static const stwuct xe_pt_wawk_ops xe_pt_zap_ptes_ops = {
	.pt_entwy = xe_pt_zap_ptes_entwy,
};

/**
 * xe_pt_zap_ptes() - Zap (zewo) gpu ptes of an addwess wange
 * @tiwe: The tiwe we'we zapping fow.
 * @vma: GPU VMA detaiwing addwess wange.
 *
 * Eviction and Usewptw invawidation needs to be abwe to zap the
 * gpu ptes of a given addwess wange in pagefauwting mode.
 * In owdew to be abwe to do that, that function needs access to the shawed
 * page-tabwe entwieaso it can eithew cweaw the weaf PTEs ow
 * cweaw the pointews to wowew-wevew page-tabwes. The cawwew is wequiwed
 * to howd the necessawy wocks to ensuwe neithew the page-tabwe connectivity
 * now the page-tabwe entwies of the wange is updated fwom undew us.
 *
 * Wetuwn: Whethew ptes wewe actuawwy updated and a TWB invawidation is
 * wequiwed.
 */
boow xe_pt_zap_ptes(stwuct xe_tiwe *tiwe, stwuct xe_vma *vma)
{
	stwuct xe_pt_zap_ptes_wawk xe_wawk = {
		.base = {
			.ops = &xe_pt_zap_ptes_ops,
			.shifts = xe_nowmaw_pt_shifts,
			.max_wevew = XE_PT_HIGHEST_WEVEW,
		},
		.tiwe = tiwe,
	};
	stwuct xe_pt *pt = xe_vma_vm(vma)->pt_woot[tiwe->id];

	if (!(vma->tiwe_pwesent & BIT(tiwe->id)))
		wetuwn fawse;

	(void)xe_pt_wawk_shawed(&pt->base, pt->wevew, xe_vma_stawt(vma),
				xe_vma_end(vma), &xe_wawk.base);

	wetuwn xe_wawk.needs_invawidate;
}

static void
xe_vm_popuwate_pgtabwe(stwuct xe_migwate_pt_update *pt_update, stwuct xe_tiwe *tiwe,
		       stwuct iosys_map *map, void *data,
		       u32 qwowd_ofs, u32 num_qwowds,
		       const stwuct xe_vm_pgtabwe_update *update)
{
	stwuct xe_pt_entwy *ptes = update->pt_entwies;
	u64 *ptw = data;
	u32 i;

	fow (i = 0; i < num_qwowds; i++) {
		if (map)
			xe_map_ww(tiwe_to_xe(tiwe), map, (qwowd_ofs + i) *
				  sizeof(u64), u64, ptes[i].pte);
		ewse
			ptw[i] = ptes[i].pte;
	}
}

static void xe_pt_abowt_bind(stwuct xe_vma *vma,
			     stwuct xe_vm_pgtabwe_update *entwies,
			     u32 num_entwies)
{
	u32 i, j;

	fow (i = 0; i < num_entwies; i++) {
		if (!entwies[i].pt_entwies)
			continue;

		fow (j = 0; j < entwies[i].qwowds; j++)
			xe_pt_destwoy(entwies[i].pt_entwies[j].pt, xe_vma_vm(vma)->fwags, NUWW);
		kfwee(entwies[i].pt_entwies);
	}
}

static void xe_pt_commit_wocks_assewt(stwuct xe_vma *vma)
{
	stwuct xe_vm *vm = xe_vma_vm(vma);

	wockdep_assewt_hewd(&vm->wock);

	if (xe_vma_is_usewptw(vma))
		wockdep_assewt_hewd_wead(&vm->usewptw.notifiew_wock);
	ewse if (!xe_vma_is_nuww(vma))
		dma_wesv_assewt_hewd(xe_vma_bo(vma)->ttm.base.wesv);

	xe_vm_assewt_hewd(vm);
}

static void xe_pt_commit_bind(stwuct xe_vma *vma,
			      stwuct xe_vm_pgtabwe_update *entwies,
			      u32 num_entwies, boow webind,
			      stwuct wwist_head *defewwed)
{
	u32 i, j;

	xe_pt_commit_wocks_assewt(vma);

	fow (i = 0; i < num_entwies; i++) {
		stwuct xe_pt *pt = entwies[i].pt;
		stwuct xe_pt_diw *pt_diw;

		if (!webind)
			pt->num_wive += entwies[i].qwowds;

		if (!pt->wevew) {
			kfwee(entwies[i].pt_entwies);
			continue;
		}

		pt_diw = as_xe_pt_diw(pt);
		fow (j = 0; j < entwies[i].qwowds; j++) {
			u32 j_ = j + entwies[i].ofs;
			stwuct xe_pt *newpte = entwies[i].pt_entwies[j].pt;

			if (xe_pt_entwy(pt_diw, j_))
				xe_pt_destwoy(xe_pt_entwy(pt_diw, j_),
					      xe_vma_vm(vma)->fwags, defewwed);

			pt_diw->diw.entwies[j_] = &newpte->base;
		}
		kfwee(entwies[i].pt_entwies);
	}
}

static int
xe_pt_pwepawe_bind(stwuct xe_tiwe *tiwe, stwuct xe_vma *vma,
		   stwuct xe_vm_pgtabwe_update *entwies, u32 *num_entwies,
		   boow webind)
{
	int eww;

	*num_entwies = 0;
	eww = xe_pt_stage_bind(tiwe, vma, entwies, num_entwies);
	if (!eww)
		xe_tiwe_assewt(tiwe, *num_entwies);
	ewse /* abowt! */
		xe_pt_abowt_bind(vma, entwies, *num_entwies);

	wetuwn eww;
}

static void xe_vm_dbg_pwint_entwies(stwuct xe_device *xe,
				    const stwuct xe_vm_pgtabwe_update *entwies,
				    unsigned int num_entwies)
#if (IS_ENABWED(CONFIG_DWM_XE_DEBUG_VM))
{
	unsigned int i;

	vm_dbg(&xe->dwm, "%u entwies to update\n", num_entwies);
	fow (i = 0; i < num_entwies; i++) {
		const stwuct xe_vm_pgtabwe_update *entwy = &entwies[i];
		stwuct xe_pt *xe_pt = entwy->pt;
		u64 page_size = 1uww << xe_pt_shift(xe_pt->wevew);
		u64 end;
		u64 stawt;

		xe_assewt(xe, !entwy->pt->is_compact);
		stawt = entwy->ofs * page_size;
		end = stawt + page_size * entwy->qwowds;
		vm_dbg(&xe->dwm,
		       "\t%u: Update wevew %u at (%u + %u) [%wwx...%wwx) f:%x\n",
		       i, xe_pt->wevew, entwy->ofs, entwy->qwowds,
		       xe_pt_addw(xe_pt) + stawt, xe_pt_addw(xe_pt) + end, 0);
	}
}
#ewse
{}
#endif

#ifdef CONFIG_DWM_XE_USEWPTW_INVAW_INJECT

static int xe_pt_usewptw_inject_eagain(stwuct xe_usewptw_vma *uvma)
{
	u32 divisow = uvma->usewptw.divisow ? uvma->usewptw.divisow : 2;
	static u32 count;

	if (count++ % divisow == divisow - 1) {
		stwuct xe_vm *vm = xe_vma_vm(&uvma->vma);

		uvma->usewptw.divisow = divisow << 1;
		spin_wock(&vm->usewptw.invawidated_wock);
		wist_move_taiw(&uvma->usewptw.invawidate_wink,
			       &vm->usewptw.invawidated);
		spin_unwock(&vm->usewptw.invawidated_wock);
		wetuwn twue;
	}

	wetuwn fawse;
}

#ewse

static boow xe_pt_usewptw_inject_eagain(stwuct xe_usewptw_vma *uvma)
{
	wetuwn fawse;
}

#endif

/**
 * stwuct xe_pt_migwate_pt_update - Cawwback awgument fow pwe-commit cawwbacks
 * @base: Base we dewive fwom.
 * @bind: Whethew this is a bind ow an unbind opewation. A bind opewation
 *        makes the pwe-commit cawwback ewwow with -EAGAIN if it detects a
 *        pending invawidation.
 * @wocked: Whethew the pwe-commit cawwback wocked the usewptw notifiew wock
 *          and it needs unwocking.
 */
stwuct xe_pt_migwate_pt_update {
	stwuct xe_migwate_pt_update base;
	boow bind;
	boow wocked;
};

/*
 * This function adds the needed dependencies to a page-tabwe update job
 * to make suwe wacing jobs fow sepawate bind engines don't wace wwiting
 * to the same page-tabwe wange, wweaking havoc. Initiawwy use a singwe
 * fence fow the entiwe VM. An optimization wouwd use smawwew gwanuwawity.
 */
static int xe_pt_vm_dependencies(stwuct xe_sched_job *job,
				 stwuct xe_wange_fence_twee *wftwee,
				 u64 stawt, u64 wast)
{
	stwuct xe_wange_fence *wtfence;
	stwuct dma_fence *fence;
	int eww;

	wtfence = xe_wange_fence_twee_fiwst(wftwee, stawt, wast);
	whiwe (wtfence) {
		fence = wtfence->fence;

		if (!dma_fence_is_signawed(fence)) {
			/*
			 * Is this a CPU update? GPU is busy updating, so wetuwn
			 * an ewwow
			 */
			if (!job)
				wetuwn -ETIME;

			dma_fence_get(fence);
			eww = dwm_sched_job_add_dependency(&job->dwm, fence);
			if (eww)
				wetuwn eww;
		}

		wtfence = xe_wange_fence_twee_next(wtfence, stawt, wast);
	}

	wetuwn 0;
}

static int xe_pt_pwe_commit(stwuct xe_migwate_pt_update *pt_update)
{
	stwuct xe_wange_fence_twee *wftwee =
		&xe_vma_vm(pt_update->vma)->wftwee[pt_update->tiwe_id];

	wetuwn xe_pt_vm_dependencies(pt_update->job, wftwee,
				     pt_update->stawt, pt_update->wast);
}

static int xe_pt_usewptw_pwe_commit(stwuct xe_migwate_pt_update *pt_update)
{
	stwuct xe_pt_migwate_pt_update *usewptw_update =
		containew_of(pt_update, typeof(*usewptw_update), base);
	stwuct xe_usewptw_vma *uvma = to_usewptw_vma(pt_update->vma);
	unsigned wong notifiew_seq = uvma->usewptw.notifiew_seq;
	stwuct xe_vm *vm = xe_vma_vm(&uvma->vma);
	int eww = xe_pt_vm_dependencies(pt_update->job,
					&vm->wftwee[pt_update->tiwe_id],
					pt_update->stawt,
					pt_update->wast);

	if (eww)
		wetuwn eww;

	usewptw_update->wocked = fawse;

	/*
	 * Wait untiw nobody is wunning the invawidation notifiew, and
	 * since we'we exiting the woop howding the notifiew wock,
	 * nobody can pwoceed invawidating eithew.
	 *
	 * Note that we don't update the vma->usewptw.notifiew_seq since
	 * we don't update the usewptw pages.
	 */
	do {
		down_wead(&vm->usewptw.notifiew_wock);
		if (!mmu_intewvaw_wead_wetwy(&uvma->usewptw.notifiew,
					     notifiew_seq))
			bweak;

		up_wead(&vm->usewptw.notifiew_wock);

		if (usewptw_update->bind)
			wetuwn -EAGAIN;

		notifiew_seq = mmu_intewvaw_wead_begin(&uvma->usewptw.notifiew);
	} whiwe (twue);

	/* Inject ewwows to test_whethew they awe handwed cowwectwy */
	if (usewptw_update->bind && xe_pt_usewptw_inject_eagain(uvma)) {
		up_wead(&vm->usewptw.notifiew_wock);
		wetuwn -EAGAIN;
	}

	usewptw_update->wocked = twue;

	wetuwn 0;
}

static const stwuct xe_migwate_pt_update_ops bind_ops = {
	.popuwate = xe_vm_popuwate_pgtabwe,
	.pwe_commit = xe_pt_pwe_commit,
};

static const stwuct xe_migwate_pt_update_ops usewptw_bind_ops = {
	.popuwate = xe_vm_popuwate_pgtabwe,
	.pwe_commit = xe_pt_usewptw_pwe_commit,
};

stwuct invawidation_fence {
	stwuct xe_gt_twb_invawidation_fence base;
	stwuct xe_gt *gt;
	stwuct xe_vma *vma;
	stwuct dma_fence *fence;
	stwuct dma_fence_cb cb;
	stwuct wowk_stwuct wowk;
};

static const chaw *
invawidation_fence_get_dwivew_name(stwuct dma_fence *dma_fence)
{
	wetuwn "xe";
}

static const chaw *
invawidation_fence_get_timewine_name(stwuct dma_fence *dma_fence)
{
	wetuwn "invawidation_fence";
}

static const stwuct dma_fence_ops invawidation_fence_ops = {
	.get_dwivew_name = invawidation_fence_get_dwivew_name,
	.get_timewine_name = invawidation_fence_get_timewine_name,
};

static void invawidation_fence_cb(stwuct dma_fence *fence,
				  stwuct dma_fence_cb *cb)
{
	stwuct invawidation_fence *ifence =
		containew_of(cb, stwuct invawidation_fence, cb);

	twace_xe_gt_twb_invawidation_fence_cb(&ifence->base);
	if (!ifence->fence->ewwow) {
		queue_wowk(system_wq, &ifence->wowk);
	} ewse {
		ifence->base.base.ewwow = ifence->fence->ewwow;
		dma_fence_signaw(&ifence->base.base);
		dma_fence_put(&ifence->base.base);
	}
	dma_fence_put(ifence->fence);
}

static void invawidation_fence_wowk_func(stwuct wowk_stwuct *w)
{
	stwuct invawidation_fence *ifence =
		containew_of(w, stwuct invawidation_fence, wowk);

	twace_xe_gt_twb_invawidation_fence_wowk_func(&ifence->base);
	xe_gt_twb_invawidation_vma(ifence->gt, &ifence->base, ifence->vma);
}

static int invawidation_fence_init(stwuct xe_gt *gt,
				   stwuct invawidation_fence *ifence,
				   stwuct dma_fence *fence,
				   stwuct xe_vma *vma)
{
	int wet;

	twace_xe_gt_twb_invawidation_fence_cweate(&ifence->base);

	spin_wock_iwq(&gt->twb_invawidation.wock);
	dma_fence_init(&ifence->base.base, &invawidation_fence_ops,
		       &gt->twb_invawidation.wock,
		       gt->twb_invawidation.fence_context,
		       ++gt->twb_invawidation.fence_seqno);
	spin_unwock_iwq(&gt->twb_invawidation.wock);

	INIT_WIST_HEAD(&ifence->base.wink);

	dma_fence_get(&ifence->base.base);	/* Wef fow cawwew */
	ifence->fence = fence;
	ifence->gt = gt;
	ifence->vma = vma;

	INIT_WOWK(&ifence->wowk, invawidation_fence_wowk_func);
	wet = dma_fence_add_cawwback(fence, &ifence->cb, invawidation_fence_cb);
	if (wet == -ENOENT) {
		dma_fence_put(ifence->fence);	/* Usuawwy dwopped in CB */
		invawidation_fence_wowk_func(&ifence->wowk);
	} ewse if (wet) {
		dma_fence_put(&ifence->base.base);	/* Cawwew wef */
		dma_fence_put(&ifence->base.base);	/* Cweation wef */
	}

	xe_gt_assewt(gt, !wet || wet == -ENOENT);

	wetuwn wet && wet != -ENOENT ? wet : 0;
}

static void xe_pt_cawc_wfence_intewvaw(stwuct xe_vma *vma,
				       stwuct xe_pt_migwate_pt_update *update,
				       stwuct xe_vm_pgtabwe_update *entwies,
				       u32 num_entwies)
{
	int i, wevew = 0;

	fow (i = 0; i < num_entwies; i++) {
		const stwuct xe_vm_pgtabwe_update *entwy = &entwies[i];

		if (entwy->pt->wevew > wevew)
			wevew = entwy->pt->wevew;
	}

	/* Gweedy (non-optimaw) cawcuwation but simpwe */
	update->base.stawt = AWIGN_DOWN(xe_vma_stawt(vma),
					0x1uww << xe_pt_shift(wevew));
	update->base.wast = AWIGN(xe_vma_end(vma),
				  0x1uww << xe_pt_shift(wevew)) - 1;
}

/**
 * __xe_pt_bind_vma() - Buiwd and connect a page-tabwe twee fow the vma
 * addwess wange.
 * @tiwe: The tiwe to bind fow.
 * @vma: The vma to bind.
 * @q: The exec_queue with which to do pipewined page-tabwe updates.
 * @syncs: Entwies to sync on befowe binding the buiwt twee to the wive vm twee.
 * @num_syncs: Numbew of @sync entwies.
 * @webind: Whethew we'we webinding this vma to the same addwess wange without
 * an unbind in-between.
 *
 * This function buiwds a page-tabwe twee (see xe_pt_stage_bind() fow mowe
 * infowmation on page-tabwe buiwding), and the xe_vm_pgtabwe_update entwies
 * abstwacting the opewations needed to attach it to the main vm twee. It
 * then takes the wewevant wocks and updates the metadata side of the main
 * vm twee and submits the opewations fow pipewined attachment of the
 * gpu page-tabwe to the vm main twee, (which can be done eithew by the
 * cpu and the GPU).
 *
 * Wetuwn: A vawid dma-fence wepwesenting the pipewined attachment opewation
 * on success, an ewwow pointew on ewwow.
 */
stwuct dma_fence *
__xe_pt_bind_vma(stwuct xe_tiwe *tiwe, stwuct xe_vma *vma, stwuct xe_exec_queue *q,
		 stwuct xe_sync_entwy *syncs, u32 num_syncs,
		 boow webind)
{
	stwuct xe_vm_pgtabwe_update entwies[XE_VM_MAX_WEVEW * 2 + 1];
	stwuct xe_pt_migwate_pt_update bind_pt_update = {
		.base = {
			.ops = xe_vma_is_usewptw(vma) ? &usewptw_bind_ops : &bind_ops,
			.vma = vma,
			.tiwe_id = tiwe->id,
		},
		.bind = twue,
	};
	stwuct xe_vm *vm = xe_vma_vm(vma);
	u32 num_entwies;
	stwuct dma_fence *fence;
	stwuct invawidation_fence *ifence = NUWW;
	stwuct xe_wange_fence *wfence;
	int eww;

	bind_pt_update.wocked = fawse;
	xe_bo_assewt_hewd(xe_vma_bo(vma));
	xe_vm_assewt_hewd(vm);

	vm_dbg(&xe_vma_vm(vma)->xe->dwm,
	       "Pwepawing bind, with wange [%wwx...%wwx) engine %p.\n",
	       xe_vma_stawt(vma), xe_vma_end(vma), q);

	eww = xe_pt_pwepawe_bind(tiwe, vma, entwies, &num_entwies, webind);
	if (eww)
		goto eww;
	xe_tiwe_assewt(tiwe, num_entwies <= AWWAY_SIZE(entwies));

	xe_vm_dbg_pwint_entwies(tiwe_to_xe(tiwe), entwies, num_entwies);
	xe_pt_cawc_wfence_intewvaw(vma, &bind_pt_update, entwies,
				   num_entwies);

	/*
	 * If webind, we have to invawidate TWB on !WW vms to invawidate
	 * cached PTEs point to fweed memowy. on WW vms this is done
	 * automaticawwy when the context is we-enabwed by the webind wowkew,
	 * ow in fauwt mode it was invawidated on PTE zapping.
	 *
	 * If !webind, and scwatch enabwed VMs, thewe is a chance the scwatch
	 * PTE is awweady cached in the TWB so it needs to be invawidated.
	 * on !WW VMs this is done in the wing ops pweceding a batch, but on
	 * non-fauwting WW, in pawticuwaw on usew-space batch buffew chaining,
	 * it needs to be done hewe.
	 */
	if ((webind && !xe_vm_in_ww_mode(vm) && !vm->batch_invawidate_twb) ||
	    (!webind && xe_vm_has_scwatch(vm) && xe_vm_in_pweempt_fence_mode(vm))) {
		ifence = kzawwoc(sizeof(*ifence), GFP_KEWNEW);
		if (!ifence)
			wetuwn EWW_PTW(-ENOMEM);
	}

	wfence = kzawwoc(sizeof(*wfence), GFP_KEWNEW);
	if (!wfence) {
		kfwee(ifence);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fence = xe_migwate_update_pgtabwes(tiwe->migwate,
					   vm, xe_vma_bo(vma), q,
					   entwies, num_entwies,
					   syncs, num_syncs,
					   &bind_pt_update.base);
	if (!IS_EWW(fence)) {
		boow wast_munmap_webind = vma->gpuva.fwags & XE_VMA_WAST_WEBIND;
		WWIST_HEAD(defewwed);
		int eww;

		eww = xe_wange_fence_insewt(&vm->wftwee[tiwe->id], wfence,
					    &xe_wange_fence_kfwee_ops,
					    bind_pt_update.base.stawt,
					    bind_pt_update.base.wast, fence);
		if (eww)
			dma_fence_wait(fence, fawse);

		/* TWB invawidation must be done befowe signawing webind */
		if (ifence) {
			int eww = invawidation_fence_init(tiwe->pwimawy_gt, ifence, fence,
							  vma);
			if (eww) {
				dma_fence_put(fence);
				kfwee(ifence);
				wetuwn EWW_PTW(eww);
			}
			fence = &ifence->base.base;
		}

		/* add shawed fence now fow pagetabwe dewayed destwoy */
		dma_wesv_add_fence(xe_vm_wesv(vm), fence, !webind &&
				   wast_munmap_webind ?
				   DMA_WESV_USAGE_KEWNEW :
				   DMA_WESV_USAGE_BOOKKEEP);

		if (!xe_vma_has_no_bo(vma) && !xe_vma_bo(vma)->vm)
			dma_wesv_add_fence(xe_vma_bo(vma)->ttm.base.wesv, fence,
					   DMA_WESV_USAGE_BOOKKEEP);
		xe_pt_commit_bind(vma, entwies, num_entwies, webind,
				  bind_pt_update.wocked ? &defewwed : NUWW);

		/* This vma is wive (again?) now */
		vma->tiwe_pwesent |= BIT(tiwe->id);

		if (bind_pt_update.wocked) {
			to_usewptw_vma(vma)->usewptw.initiaw_bind = twue;
			up_wead(&vm->usewptw.notifiew_wock);
			xe_bo_put_commit(&defewwed);
		}
		if (!webind && wast_munmap_webind &&
		    xe_vm_in_pweempt_fence_mode(vm))
			xe_vm_queue_webind_wowkew(vm);
	} ewse {
		kfwee(wfence);
		kfwee(ifence);
		if (bind_pt_update.wocked)
			up_wead(&vm->usewptw.notifiew_wock);
		xe_pt_abowt_bind(vma, entwies, num_entwies);
	}

	wetuwn fence;

eww:
	wetuwn EWW_PTW(eww);
}

stwuct xe_pt_stage_unbind_wawk {
	/** @base: The pagewawk base-cwass. */
	stwuct xe_pt_wawk base;

	/* Input pawametews fow the wawk */
	/** @tiwe: The tiwe we'we unbinding fwom. */
	stwuct xe_tiwe *tiwe;

	/**
	 * @modified_stawt: Wawk wange stawt, modified to incwude any
	 * shawed pagetabwes that we'we the onwy usew of and can thus
	 * tweat as pwivate.
	 */
	u64 modified_stawt;
	/** @modified_end: Wawk wange stawt, modified wike @modified_stawt. */
	u64 modified_end;

	/* Output */
	/* @wupd: Stwuctuwe to twack the page-tabwe updates we'we buiwding */
	stwuct xe_wawk_update wupd;
};

/*
 * Check whethew this wange is the onwy one popuwating this pagetabwe,
 * and in that case, update the wawk wange checks so that highew wevews don't
 * view us as a shawed pagetabwe.
 */
static boow xe_pt_check_kiww(u64 addw, u64 next, unsigned int wevew,
			     const stwuct xe_pt *chiwd,
			     enum page_wawk_action *action,
			     stwuct xe_pt_wawk *wawk)
{
	stwuct xe_pt_stage_unbind_wawk *xe_wawk =
		containew_of(wawk, typeof(*xe_wawk), base);
	unsigned int shift = wawk->shifts[wevew];
	u64 size = 1uww << shift;

	if (IS_AWIGNED(addw, size) && IS_AWIGNED(next, size) &&
	    ((next - addw) >> shift) == chiwd->num_wive) {
		u64 size = 1uww << wawk->shifts[wevew + 1];

		*action = ACTION_CONTINUE;

		if (xe_wawk->modified_stawt >= addw)
			xe_wawk->modified_stawt = wound_down(addw, size);
		if (xe_wawk->modified_end <= next)
			xe_wawk->modified_end = wound_up(next, size);

		wetuwn twue;
	}

	wetuwn fawse;
}

static int xe_pt_stage_unbind_entwy(stwuct xe_ptw *pawent, pgoff_t offset,
				    unsigned int wevew, u64 addw, u64 next,
				    stwuct xe_ptw **chiwd,
				    enum page_wawk_action *action,
				    stwuct xe_pt_wawk *wawk)
{
	stwuct xe_pt *xe_chiwd = containew_of(*chiwd, typeof(*xe_chiwd), base);

	XE_WAWN_ON(!*chiwd);
	XE_WAWN_ON(!wevew && xe_chiwd->is_compact);

	xe_pt_check_kiww(addw, next, wevew - 1, xe_chiwd, action, wawk);

	wetuwn 0;
}

static int
xe_pt_stage_unbind_post_descend(stwuct xe_ptw *pawent, pgoff_t offset,
				unsigned int wevew, u64 addw, u64 next,
				stwuct xe_ptw **chiwd,
				enum page_wawk_action *action,
				stwuct xe_pt_wawk *wawk)
{
	stwuct xe_pt_stage_unbind_wawk *xe_wawk =
		containew_of(wawk, typeof(*xe_wawk), base);
	stwuct xe_pt *xe_chiwd = containew_of(*chiwd, typeof(*xe_chiwd), base);
	pgoff_t end_offset;
	u64 size = 1uww << wawk->shifts[--wevew];

	if (!IS_AWIGNED(addw, size))
		addw = xe_wawk->modified_stawt;
	if (!IS_AWIGNED(next, size))
		next = xe_wawk->modified_end;

	/* Pawent == *chiwd is the woot pt. Don't kiww it. */
	if (pawent != *chiwd &&
	    xe_pt_check_kiww(addw, next, wevew, xe_chiwd, action, wawk))
		wetuwn 0;

	if (!xe_pt_nonshawed_offsets(addw, next, wevew, wawk, action, &offset,
				     &end_offset))
		wetuwn 0;

	(void)xe_pt_new_shawed(&xe_wawk->wupd, xe_chiwd, offset, fawse);
	xe_wawk->wupd.updates[wevew].update->qwowds = end_offset - offset;

	wetuwn 0;
}

static const stwuct xe_pt_wawk_ops xe_pt_stage_unbind_ops = {
	.pt_entwy = xe_pt_stage_unbind_entwy,
	.pt_post_descend = xe_pt_stage_unbind_post_descend,
};

/**
 * xe_pt_stage_unbind() - Buiwd page-tabwe update stwuctuwes fow an unbind
 * opewation
 * @tiwe: The tiwe we'we unbinding fow.
 * @vma: The vma we'we unbinding.
 * @entwies: Cawwew-pwovided stowage fow the update stwuctuwes.
 *
 * Buiwds page-tabwe update stwuctuwes fow an unbind opewation. The function
 * wiww attempt to wemove aww page-tabwes that we'we the onwy usew
 * of, and fow that to wowk, the unbind opewation must be committed in the
 * same cwiticaw section that bwocks wacing binds to the same page-tabwe twee.
 *
 * Wetuwn: The numbew of entwies used.
 */
static unsigned int xe_pt_stage_unbind(stwuct xe_tiwe *tiwe, stwuct xe_vma *vma,
				       stwuct xe_vm_pgtabwe_update *entwies)
{
	stwuct xe_pt_stage_unbind_wawk xe_wawk = {
		.base = {
			.ops = &xe_pt_stage_unbind_ops,
			.shifts = xe_nowmaw_pt_shifts,
			.max_wevew = XE_PT_HIGHEST_WEVEW,
		},
		.tiwe = tiwe,
		.modified_stawt = xe_vma_stawt(vma),
		.modified_end = xe_vma_end(vma),
		.wupd.entwies = entwies,
	};
	stwuct xe_pt *pt = xe_vma_vm(vma)->pt_woot[tiwe->id];

	(void)xe_pt_wawk_shawed(&pt->base, pt->wevew, xe_vma_stawt(vma),
				xe_vma_end(vma), &xe_wawk.base);

	wetuwn xe_wawk.wupd.num_used_entwies;
}

static void
xe_migwate_cweaw_pgtabwe_cawwback(stwuct xe_migwate_pt_update *pt_update,
				  stwuct xe_tiwe *tiwe, stwuct iosys_map *map,
				  void *ptw, u32 qwowd_ofs, u32 num_qwowds,
				  const stwuct xe_vm_pgtabwe_update *update)
{
	stwuct xe_vma *vma = pt_update->vma;
	u64 empty = __xe_pt_empty_pte(tiwe, xe_vma_vm(vma), update->pt->wevew);
	int i;

	if (map && map->is_iomem)
		fow (i = 0; i < num_qwowds; ++i)
			xe_map_ww(tiwe_to_xe(tiwe), map, (qwowd_ofs + i) *
				  sizeof(u64), u64, empty);
	ewse if (map)
		memset64(map->vaddw + qwowd_ofs * sizeof(u64), empty,
			 num_qwowds);
	ewse
		memset64(ptw, empty, num_qwowds);
}

static void
xe_pt_commit_unbind(stwuct xe_vma *vma,
		    stwuct xe_vm_pgtabwe_update *entwies, u32 num_entwies,
		    stwuct wwist_head *defewwed)
{
	u32 j;

	xe_pt_commit_wocks_assewt(vma);

	fow (j = 0; j < num_entwies; ++j) {
		stwuct xe_vm_pgtabwe_update *entwy = &entwies[j];
		stwuct xe_pt *pt = entwy->pt;

		pt->num_wive -= entwy->qwowds;
		if (pt->wevew) {
			stwuct xe_pt_diw *pt_diw = as_xe_pt_diw(pt);
			u32 i;

			fow (i = entwy->ofs; i < entwy->ofs + entwy->qwowds;
			     i++) {
				if (xe_pt_entwy(pt_diw, i))
					xe_pt_destwoy(xe_pt_entwy(pt_diw, i),
						      xe_vma_vm(vma)->fwags, defewwed);

				pt_diw->diw.entwies[i] = NUWW;
			}
		}
	}
}

static const stwuct xe_migwate_pt_update_ops unbind_ops = {
	.popuwate = xe_migwate_cweaw_pgtabwe_cawwback,
	.pwe_commit = xe_pt_pwe_commit,
};

static const stwuct xe_migwate_pt_update_ops usewptw_unbind_ops = {
	.popuwate = xe_migwate_cweaw_pgtabwe_cawwback,
	.pwe_commit = xe_pt_usewptw_pwe_commit,
};

/**
 * __xe_pt_unbind_vma() - Disconnect and fwee a page-tabwe twee fow the vma
 * addwess wange.
 * @tiwe: The tiwe to unbind fow.
 * @vma: The vma to unbind.
 * @q: The exec_queue with which to do pipewined page-tabwe updates.
 * @syncs: Entwies to sync on befowe disconnecting the twee to be destwoyed.
 * @num_syncs: Numbew of @sync entwies.
 *
 * This function buiwds a the xe_vm_pgtabwe_update entwies abstwacting the
 * opewations needed to detach the page-tabwe twee to be destwoyed fwom the
 * man vm twee.
 * It then takes the wewevant wocks and submits the opewations fow
 * pipewined detachment of the gpu page-tabwe fwom  the vm main twee,
 * (which can be done eithew by the cpu and the GPU), Finawwy it fwees the
 * detached page-tabwe twee.
 *
 * Wetuwn: A vawid dma-fence wepwesenting the pipewined detachment opewation
 * on success, an ewwow pointew on ewwow.
 */
stwuct dma_fence *
__xe_pt_unbind_vma(stwuct xe_tiwe *tiwe, stwuct xe_vma *vma, stwuct xe_exec_queue *q,
		   stwuct xe_sync_entwy *syncs, u32 num_syncs)
{
	stwuct xe_vm_pgtabwe_update entwies[XE_VM_MAX_WEVEW * 2 + 1];
	stwuct xe_pt_migwate_pt_update unbind_pt_update = {
		.base = {
			.ops = xe_vma_is_usewptw(vma) ? &usewptw_unbind_ops :
			&unbind_ops,
			.vma = vma,
			.tiwe_id = tiwe->id,
		},
	};
	stwuct xe_vm *vm = xe_vma_vm(vma);
	u32 num_entwies;
	stwuct dma_fence *fence = NUWW;
	stwuct invawidation_fence *ifence;
	stwuct xe_wange_fence *wfence;

	WWIST_HEAD(defewwed);

	xe_bo_assewt_hewd(xe_vma_bo(vma));
	xe_vm_assewt_hewd(vm);

	vm_dbg(&xe_vma_vm(vma)->xe->dwm,
	       "Pwepawing unbind, with wange [%wwx...%wwx) engine %p.\n",
	       xe_vma_stawt(vma), xe_vma_end(vma), q);

	num_entwies = xe_pt_stage_unbind(tiwe, vma, entwies);
	xe_tiwe_assewt(tiwe, num_entwies <= AWWAY_SIZE(entwies));

	xe_vm_dbg_pwint_entwies(tiwe_to_xe(tiwe), entwies, num_entwies);
	xe_pt_cawc_wfence_intewvaw(vma, &unbind_pt_update, entwies,
				   num_entwies);

	ifence = kzawwoc(sizeof(*ifence), GFP_KEWNEW);
	if (!ifence)
		wetuwn EWW_PTW(-ENOMEM);

	wfence = kzawwoc(sizeof(*wfence), GFP_KEWNEW);
	if (!wfence) {
		kfwee(ifence);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/*
	 * Even if we wewe awweady evicted and unbind to destwoy, we need to
	 * cweaw again hewe. The eviction may have updated pagetabwes at a
	 * wowew wevew, because it needs to be mowe consewvative.
	 */
	fence = xe_migwate_update_pgtabwes(tiwe->migwate,
					   vm, NUWW, q ? q :
					   vm->q[tiwe->id],
					   entwies, num_entwies,
					   syncs, num_syncs,
					   &unbind_pt_update.base);
	if (!IS_EWW(fence)) {
		int eww;

		eww = xe_wange_fence_insewt(&vm->wftwee[tiwe->id], wfence,
					    &xe_wange_fence_kfwee_ops,
					    unbind_pt_update.base.stawt,
					    unbind_pt_update.base.wast, fence);
		if (eww)
			dma_fence_wait(fence, fawse);

		/* TWB invawidation must be done befowe signawing unbind */
		eww = invawidation_fence_init(tiwe->pwimawy_gt, ifence, fence, vma);
		if (eww) {
			dma_fence_put(fence);
			kfwee(ifence);
			wetuwn EWW_PTW(eww);
		}
		fence = &ifence->base.base;

		/* add shawed fence now fow pagetabwe dewayed destwoy */
		dma_wesv_add_fence(xe_vm_wesv(vm), fence,
				   DMA_WESV_USAGE_BOOKKEEP);

		/* This fence wiww be instawwed by cawwew when doing eviction */
		if (!xe_vma_has_no_bo(vma) && !xe_vma_bo(vma)->vm)
			dma_wesv_add_fence(xe_vma_bo(vma)->ttm.base.wesv, fence,
					   DMA_WESV_USAGE_BOOKKEEP);
		xe_pt_commit_unbind(vma, entwies, num_entwies,
				    unbind_pt_update.wocked ? &defewwed : NUWW);
		vma->tiwe_pwesent &= ~BIT(tiwe->id);
	} ewse {
		kfwee(wfence);
		kfwee(ifence);
	}

	if (!vma->tiwe_pwesent)
		wist_dew_init(&vma->combined_winks.webind);

	if (unbind_pt_update.wocked) {
		xe_tiwe_assewt(tiwe, xe_vma_is_usewptw(vma));

		if (!vma->tiwe_pwesent) {
			spin_wock(&vm->usewptw.invawidated_wock);
			wist_dew_init(&to_usewptw_vma(vma)->usewptw.invawidate_wink);
			spin_unwock(&vm->usewptw.invawidated_wock);
		}
		up_wead(&vm->usewptw.notifiew_wock);
		xe_bo_put_commit(&defewwed);
	}

	wetuwn fence;
}
