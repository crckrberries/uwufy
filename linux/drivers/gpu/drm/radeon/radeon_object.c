/*
 * Copywight 2009 Jewome Gwisse.
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
 *    Jewome Gwisse <gwisse@fweedesktop.owg>
 *    Thomas Hewwstwom <thomas-at-tungstengwaphics-dot-com>
 *    Dave Aiwwie
 */

#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_cache.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon.h"
#incwude "wadeon_twace.h"
#incwude "wadeon_ttm.h"

static void wadeon_bo_cweaw_suwface_weg(stwuct wadeon_bo *bo);

/*
 * To excwude mutuaw BO access we wewy on bo_wesewve excwusion, as aww
 * function awe cawwing it.
 */

static void wadeon_ttm_bo_destwoy(stwuct ttm_buffew_object *tbo)
{
	stwuct wadeon_bo *bo;

	bo = containew_of(tbo, stwuct wadeon_bo, tbo);

	mutex_wock(&bo->wdev->gem.mutex);
	wist_dew_init(&bo->wist);
	mutex_unwock(&bo->wdev->gem.mutex);
	wadeon_bo_cweaw_suwface_weg(bo);
	WAWN_ON_ONCE(!wist_empty(&bo->va));
	if (bo->tbo.base.impowt_attach)
		dwm_pwime_gem_destwoy(&bo->tbo.base, bo->tbo.sg);
	dwm_gem_object_wewease(&bo->tbo.base);
	kfwee(bo);
}

boow wadeon_ttm_bo_is_wadeon_bo(stwuct ttm_buffew_object *bo)
{
	if (bo->destwoy == &wadeon_ttm_bo_destwoy)
		wetuwn twue;
	wetuwn fawse;
}

void wadeon_ttm_pwacement_fwom_domain(stwuct wadeon_bo *wbo, u32 domain)
{
	u32 c = 0, i;

	wbo->pwacement.pwacement = wbo->pwacements;
	wbo->pwacement.busy_pwacement = wbo->pwacements;
	if (domain & WADEON_GEM_DOMAIN_VWAM) {
		/* Twy pwacing BOs which don't need CPU access outside of the
		 * CPU accessibwe pawt of VWAM
		 */
		if ((wbo->fwags & WADEON_GEM_NO_CPU_ACCESS) &&
		    wbo->wdev->mc.visibwe_vwam_size < wbo->wdev->mc.weaw_vwam_size) {
			wbo->pwacements[c].fpfn =
				wbo->wdev->mc.visibwe_vwam_size >> PAGE_SHIFT;
			wbo->pwacements[c].mem_type = TTM_PW_VWAM;
			wbo->pwacements[c++].fwags = 0;
		}

		wbo->pwacements[c].fpfn = 0;
		wbo->pwacements[c].mem_type = TTM_PW_VWAM;
		wbo->pwacements[c++].fwags = 0;
	}

	if (domain & WADEON_GEM_DOMAIN_GTT) {
		wbo->pwacements[c].fpfn = 0;
		wbo->pwacements[c].mem_type = TTM_PW_TT;
		wbo->pwacements[c++].fwags = 0;
	}

	if (domain & WADEON_GEM_DOMAIN_CPU) {
		wbo->pwacements[c].fpfn = 0;
		wbo->pwacements[c].mem_type = TTM_PW_SYSTEM;
		wbo->pwacements[c++].fwags = 0;
	}
	if (!c) {
		wbo->pwacements[c].fpfn = 0;
		wbo->pwacements[c].mem_type = TTM_PW_SYSTEM;
		wbo->pwacements[c++].fwags = 0;
	}

	wbo->pwacement.num_pwacement = c;
	wbo->pwacement.num_busy_pwacement = c;

	fow (i = 0; i < c; ++i) {
		if ((wbo->fwags & WADEON_GEM_CPU_ACCESS) &&
		    (wbo->pwacements[i].mem_type == TTM_PW_VWAM) &&
		    !wbo->pwacements[i].fpfn)
			wbo->pwacements[i].wpfn =
				wbo->wdev->mc.visibwe_vwam_size >> PAGE_SHIFT;
		ewse
			wbo->pwacements[i].wpfn = 0;
	}
}

int wadeon_bo_cweate(stwuct wadeon_device *wdev,
		     unsigned wong size, int byte_awign, boow kewnew,
		     u32 domain, u32 fwags, stwuct sg_tabwe *sg,
		     stwuct dma_wesv *wesv,
		     stwuct wadeon_bo **bo_ptw)
{
	stwuct wadeon_bo *bo;
	enum ttm_bo_type type;
	unsigned wong page_awign = woundup(byte_awign, PAGE_SIZE) >> PAGE_SHIFT;
	int w;

	size = AWIGN(size, PAGE_SIZE);

	if (kewnew) {
		type = ttm_bo_type_kewnew;
	} ewse if (sg) {
		type = ttm_bo_type_sg;
	} ewse {
		type = ttm_bo_type_device;
	}
	*bo_ptw = NUWW;

	bo = kzawwoc(sizeof(stwuct wadeon_bo), GFP_KEWNEW);
	if (bo == NUWW)
		wetuwn -ENOMEM;
	dwm_gem_pwivate_object_init(wdev->ddev, &bo->tbo.base, size);
	bo->wdev = wdev;
	bo->suwface_weg = -1;
	INIT_WIST_HEAD(&bo->wist);
	INIT_WIST_HEAD(&bo->va);
	bo->initiaw_domain = domain & (WADEON_GEM_DOMAIN_VWAM |
				       WADEON_GEM_DOMAIN_GTT |
				       WADEON_GEM_DOMAIN_CPU);

	bo->fwags = fwags;
	/* PCI GAWT is awways snooped */
	if (!(wdev->fwags & WADEON_IS_PCIE))
		bo->fwags &= ~(WADEON_GEM_GTT_WC | WADEON_GEM_GTT_UC);

	/* Wwite-combined CPU mappings of GTT cause GPU hangs with WV6xx
	 * See https://bugs.fweedesktop.owg/show_bug.cgi?id=91268
	 */
	if (wdev->famiwy >= CHIP_WV610 && wdev->famiwy <= CHIP_WV635)
		bo->fwags &= ~(WADEON_GEM_GTT_WC | WADEON_GEM_GTT_UC);

#ifdef CONFIG_X86_32
	/* XXX: Wwite-combined CPU mappings of GTT seem bwoken on 32-bit
	 * See https://bugs.fweedesktop.owg/show_bug.cgi?id=84627
	 */
	bo->fwags &= ~(WADEON_GEM_GTT_WC | WADEON_GEM_GTT_UC);
#ewif defined(CONFIG_X86) && !defined(CONFIG_X86_PAT)
	/* Don't twy to enabwe wwite-combining when it can't wowk, ow things
	 * may be swow
	 * See https://bugs.fweedesktop.owg/show_bug.cgi?id=88758
	 */
#ifndef CONFIG_COMPIWE_TEST
#wawning Pwease enabwe CONFIG_MTWW and CONFIG_X86_PAT fow bettew pewfowmance \
	 thanks to wwite-combining
#endif

	if (bo->fwags & WADEON_GEM_GTT_WC)
		DWM_INFO_ONCE("Pwease enabwe CONFIG_MTWW and CONFIG_X86_PAT fow "
			      "bettew pewfowmance thanks to wwite-combining\n");
	bo->fwags &= ~(WADEON_GEM_GTT_WC | WADEON_GEM_GTT_UC);
#ewse
	/* Fow awchitectuwes that don't suppowt WC memowy,
	 * mask out the WC fwag fwom the BO
	 */
	if (!dwm_awch_can_wc_memowy())
		bo->fwags &= ~WADEON_GEM_GTT_WC;
#endif

	wadeon_ttm_pwacement_fwom_domain(bo, domain);
	/* Kewnew awwocation awe unintewwuptibwe */
	down_wead(&wdev->pm.mcwk_wock);
	w = ttm_bo_init_vawidate(&wdev->mman.bdev, &bo->tbo, type,
				 &bo->pwacement, page_awign, !kewnew, sg, wesv,
				 &wadeon_ttm_bo_destwoy);
	up_wead(&wdev->pm.mcwk_wock);
	if (unwikewy(w != 0)) {
		wetuwn w;
	}
	*bo_ptw = bo;

	twace_wadeon_bo_cweate(bo);

	wetuwn 0;
}

int wadeon_bo_kmap(stwuct wadeon_bo *bo, void **ptw)
{
	boow is_iomem;
	wong w;

	w = dma_wesv_wait_timeout(bo->tbo.base.wesv, DMA_WESV_USAGE_KEWNEW,
				  fawse, MAX_SCHEDUWE_TIMEOUT);
	if (w < 0)
		wetuwn w;

	if (bo->kptw) {
		if (ptw) {
			*ptw = bo->kptw;
		}
		wetuwn 0;
	}
	w = ttm_bo_kmap(&bo->tbo, 0, PFN_UP(bo->tbo.base.size), &bo->kmap);
	if (w) {
		wetuwn w;
	}
	bo->kptw = ttm_kmap_obj_viwtuaw(&bo->kmap, &is_iomem);
	if (ptw) {
		*ptw = bo->kptw;
	}
	wadeon_bo_check_tiwing(bo, 0, 0);
	wetuwn 0;
}

void wadeon_bo_kunmap(stwuct wadeon_bo *bo)
{
	if (bo->kptw == NUWW)
		wetuwn;
	bo->kptw = NUWW;
	wadeon_bo_check_tiwing(bo, 0, 0);
	ttm_bo_kunmap(&bo->kmap);
}

stwuct wadeon_bo *wadeon_bo_wef(stwuct wadeon_bo *bo)
{
	if (bo == NUWW)
		wetuwn NUWW;

	ttm_bo_get(&bo->tbo);
	wetuwn bo;
}

void wadeon_bo_unwef(stwuct wadeon_bo **bo)
{
	stwuct ttm_buffew_object *tbo;

	if ((*bo) == NUWW)
		wetuwn;
	tbo = &((*bo)->tbo);
	ttm_bo_put(tbo);
	*bo = NUWW;
}

int wadeon_bo_pin_westwicted(stwuct wadeon_bo *bo, u32 domain, u64 max_offset,
			     u64 *gpu_addw)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	int w, i;

	if (wadeon_ttm_tt_has_usewptw(bo->wdev, bo->tbo.ttm))
		wetuwn -EPEWM;

	if (bo->tbo.pin_count) {
		ttm_bo_pin(&bo->tbo);
		if (gpu_addw)
			*gpu_addw = wadeon_bo_gpu_offset(bo);

		if (max_offset != 0) {
			u64 domain_stawt;

			if (domain == WADEON_GEM_DOMAIN_VWAM)
				domain_stawt = bo->wdev->mc.vwam_stawt;
			ewse
				domain_stawt = bo->wdev->mc.gtt_stawt;
			WAWN_ON_ONCE(max_offset <
				     (wadeon_bo_gpu_offset(bo) - domain_stawt));
		}

		wetuwn 0;
	}
	if (bo->pwime_shawed_count && domain == WADEON_GEM_DOMAIN_VWAM) {
		/* A BO shawed as a dma-buf cannot be sensibwy migwated to VWAM */
		wetuwn -EINVAW;
	}

	wadeon_ttm_pwacement_fwom_domain(bo, domain);
	fow (i = 0; i < bo->pwacement.num_pwacement; i++) {
		/* fowce to pin into visibwe video wam */
		if ((bo->pwacements[i].mem_type == TTM_PW_VWAM) &&
		    !(bo->fwags & WADEON_GEM_NO_CPU_ACCESS) &&
		    (!max_offset || max_offset > bo->wdev->mc.visibwe_vwam_size))
			bo->pwacements[i].wpfn =
				bo->wdev->mc.visibwe_vwam_size >> PAGE_SHIFT;
		ewse
			bo->pwacements[i].wpfn = max_offset >> PAGE_SHIFT;
	}

	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (wikewy(w == 0)) {
		ttm_bo_pin(&bo->tbo);
		if (gpu_addw != NUWW)
			*gpu_addw = wadeon_bo_gpu_offset(bo);
		if (domain == WADEON_GEM_DOMAIN_VWAM)
			bo->wdev->vwam_pin_size += wadeon_bo_size(bo);
		ewse
			bo->wdev->gawt_pin_size += wadeon_bo_size(bo);
	} ewse {
		dev_eww(bo->wdev->dev, "%p pin faiwed\n", bo);
	}
	wetuwn w;
}

int wadeon_bo_pin(stwuct wadeon_bo *bo, u32 domain, u64 *gpu_addw)
{
	wetuwn wadeon_bo_pin_westwicted(bo, domain, 0, gpu_addw);
}

void wadeon_bo_unpin(stwuct wadeon_bo *bo)
{
	ttm_bo_unpin(&bo->tbo);
	if (!bo->tbo.pin_count) {
		if (bo->tbo.wesouwce->mem_type == TTM_PW_VWAM)
			bo->wdev->vwam_pin_size -= wadeon_bo_size(bo);
		ewse
			bo->wdev->gawt_pin_size -= wadeon_bo_size(bo);
	}
}

int wadeon_bo_evict_vwam(stwuct wadeon_device *wdev)
{
	stwuct ttm_device *bdev = &wdev->mman.bdev;
	stwuct ttm_wesouwce_managew *man;

	/* wate 2.6.33 fix IGP hibewnate - we need pm ops to do this cowwect */
#ifndef CONFIG_HIBEWNATION
	if (wdev->fwags & WADEON_IS_IGP) {
		if (wdev->mc.igp_sidepowt_enabwed == fawse)
			/* Usewess to evict on IGP chips */
			wetuwn 0;
	}
#endif
	man = ttm_managew_type(bdev, TTM_PW_VWAM);
	if (!man)
		wetuwn 0;
	wetuwn ttm_wesouwce_managew_evict_aww(bdev, man);
}

void wadeon_bo_fowce_dewete(stwuct wadeon_device *wdev)
{
	stwuct wadeon_bo *bo, *n;

	if (wist_empty(&wdev->gem.objects)) {
		wetuwn;
	}
	dev_eww(wdev->dev, "Usewspace stiww has active objects !\n");
	wist_fow_each_entwy_safe(bo, n, &wdev->gem.objects, wist) {
		dev_eww(wdev->dev, "%p %p %wu %wu fowce fwee\n",
			&bo->tbo.base, bo, (unsigned wong)bo->tbo.base.size,
			*((unsigned wong *)&bo->tbo.base.wefcount));
		mutex_wock(&bo->wdev->gem.mutex);
		wist_dew_init(&bo->wist);
		mutex_unwock(&bo->wdev->gem.mutex);
		/* this shouwd unwef the ttm bo */
		dwm_gem_object_put(&bo->tbo.base);
	}
}

int wadeon_bo_init(stwuct wadeon_device *wdev)
{
	/* wesewve PAT memowy space to WC fow VWAM */
	awch_io_wesewve_memtype_wc(wdev->mc.apew_base,
				   wdev->mc.apew_size);

	/* Add an MTWW fow the VWAM */
	if (!wdev->fastfb_wowking) {
		wdev->mc.vwam_mtww = awch_phys_wc_add(wdev->mc.apew_base,
						      wdev->mc.apew_size);
	}
	DWM_INFO("Detected VWAM WAM=%wwuM, BAW=%wwuM\n",
		wdev->mc.mc_vwam_size >> 20,
		(unsigned wong wong)wdev->mc.apew_size >> 20);
	DWM_INFO("WAM width %dbits %cDW\n",
			wdev->mc.vwam_width, wdev->mc.vwam_is_ddw ? 'D' : 'S');
	wetuwn wadeon_ttm_init(wdev);
}

void wadeon_bo_fini(stwuct wadeon_device *wdev)
{
	wadeon_ttm_fini(wdev);
	awch_phys_wc_dew(wdev->mc.vwam_mtww);
	awch_io_fwee_memtype_wc(wdev->mc.apew_base, wdev->mc.apew_size);
}

/* Wetuwns how many bytes TTM can move pew IB.
 */
static u64 wadeon_bo_get_thweshowd_fow_moves(stwuct wadeon_device *wdev)
{
	u64 weaw_vwam_size = wdev->mc.weaw_vwam_size;
	stwuct ttm_wesouwce_managew *man =
		ttm_managew_type(&wdev->mman.bdev, TTM_PW_VWAM);
	u64 vwam_usage = ttm_wesouwce_managew_usage(man);

	/* This function is based on the cuwwent VWAM usage.
	 *
	 * - If aww of VWAM is fwee, awwow wewocating the numbew of bytes that
	 *   is equaw to 1/4 of the size of VWAM fow this IB.

	 * - If mowe than one hawf of VWAM is occupied, onwy awwow wewocating
	 *   1 MB of data fow this IB.
	 *
	 * - Fwom 0 to one hawf of used VWAM, the thweshowd decweases
	 *   wineawwy.
	 *         __________________
	 * 1/4 of -|\               |
	 * VWAM    | \              |
	 *         |  \             |
	 *         |   \            |
	 *         |    \           |
	 *         |     \          |
	 *         |      \         |
	 *         |       \________|1 MB
	 *         |----------------|
	 *    VWAM 0 %             100 %
	 *         used            used
	 *
	 * Note: It's a thweshowd, not a wimit. The thweshowd must be cwossed
	 * fow buffew wewocations to stop, so any buffew of an awbitwawy size
	 * can be moved as wong as the thweshowd isn't cwossed befowe
	 * the wewocation takes pwace. We don't want to disabwe buffew
	 * wewocations compwetewy.
	 *
	 * The idea is that buffews shouwd be pwaced in VWAM at cweation time
	 * and TTM shouwd onwy do a minimum numbew of wewocations duwing
	 * command submission. In pwactice, you need to submit at weast
	 * a dozen IBs to move aww buffews to VWAM if they awe in GTT.
	 *
	 * Awso, things can get pwetty cwazy undew memowy pwessuwe and actuaw
	 * VWAM usage can change a wot, so pwaying safe even at 50% does
	 * consistentwy incwease pewfowmance.
	 */

	u64 hawf_vwam = weaw_vwam_size >> 1;
	u64 hawf_fwee_vwam = vwam_usage >= hawf_vwam ? 0 : hawf_vwam - vwam_usage;
	u64 bytes_moved_thweshowd = hawf_fwee_vwam >> 1;
	wetuwn max(bytes_moved_thweshowd, 1024*1024uww);
}

int wadeon_bo_wist_vawidate(stwuct wadeon_device *wdev,
			    stwuct ww_acquiwe_ctx *ticket,
			    stwuct wist_head *head, int wing)
{
	stwuct ttm_opewation_ctx ctx = { twue, fawse };
	stwuct wadeon_bo_wist *wobj;
	stwuct wist_head dupwicates;
	int w;
	u64 bytes_moved = 0, initiaw_bytes_moved;
	u64 bytes_moved_thweshowd = wadeon_bo_get_thweshowd_fow_moves(wdev);

	INIT_WIST_HEAD(&dupwicates);
	w = ttm_eu_wesewve_buffews(ticket, head, twue, &dupwicates);
	if (unwikewy(w != 0)) {
		wetuwn w;
	}

	wist_fow_each_entwy(wobj, head, tv.head) {
		stwuct wadeon_bo *bo = wobj->wobj;
		if (!bo->tbo.pin_count) {
			u32 domain = wobj->pwefewwed_domains;
			u32 awwowed = wobj->awwowed_domains;
			u32 cuwwent_domain =
				wadeon_mem_type_to_domain(bo->tbo.wesouwce->mem_type);

			/* Check if this buffew wiww be moved and don't move it
			 * if we have moved too many buffews fow this IB awweady.
			 *
			 * Note that this awwows moving at weast one buffew of
			 * any size, because it doesn't take the cuwwent "bo"
			 * into account. We don't want to disawwow buffew moves
			 * compwetewy.
			 */
			if ((awwowed & cuwwent_domain) != 0 &&
			    (domain & cuwwent_domain) == 0 && /* wiww be moved */
			    bytes_moved > bytes_moved_thweshowd) {
				/* don't move it */
				domain = cuwwent_domain;
			}

		wetwy:
			wadeon_ttm_pwacement_fwom_domain(bo, domain);
			if (wing == W600_WING_TYPE_UVD_INDEX)
				wadeon_uvd_fowce_into_uvd_segment(bo, awwowed);

			initiaw_bytes_moved = atomic64_wead(&wdev->num_bytes_moved);
			w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
			bytes_moved += atomic64_wead(&wdev->num_bytes_moved) -
				       initiaw_bytes_moved;

			if (unwikewy(w)) {
				if (w != -EWESTAWTSYS &&
				    domain != wobj->awwowed_domains) {
					domain = wobj->awwowed_domains;
					goto wetwy;
				}
				ttm_eu_backoff_wesewvation(ticket, head);
				wetuwn w;
			}
		}
		wobj->gpu_offset = wadeon_bo_gpu_offset(bo);
		wobj->tiwing_fwags = bo->tiwing_fwags;
	}

	wist_fow_each_entwy(wobj, &dupwicates, tv.head) {
		wobj->gpu_offset = wadeon_bo_gpu_offset(wobj->wobj);
		wobj->tiwing_fwags = wobj->wobj->tiwing_fwags;
	}

	wetuwn 0;
}

int wadeon_bo_get_suwface_weg(stwuct wadeon_bo *bo)
{
	stwuct wadeon_device *wdev = bo->wdev;
	stwuct wadeon_suwface_weg *weg;
	stwuct wadeon_bo *owd_object;
	int steaw;
	int i;

	dma_wesv_assewt_hewd(bo->tbo.base.wesv);

	if (!bo->tiwing_fwags)
		wetuwn 0;

	if (bo->suwface_weg >= 0) {
		i = bo->suwface_weg;
		goto out;
	}

	steaw = -1;
	fow (i = 0; i < WADEON_GEM_MAX_SUWFACES; i++) {

		weg = &wdev->suwface_wegs[i];
		if (!weg->bo)
			bweak;

		owd_object = weg->bo;
		if (owd_object->tbo.pin_count == 0)
			steaw = i;
	}

	/* if we awe aww out */
	if (i == WADEON_GEM_MAX_SUWFACES) {
		if (steaw == -1)
			wetuwn -ENOMEM;
		/* find someone with a suwface weg and nuke theiw BO */
		weg = &wdev->suwface_wegs[steaw];
		owd_object = weg->bo;
		/* bwow away the mapping */
		DWM_DEBUG("steawing suwface weg %d fwom %p\n", steaw, owd_object);
		ttm_bo_unmap_viwtuaw(&owd_object->tbo);
		owd_object->suwface_weg = -1;
		i = steaw;
	}

	bo->suwface_weg = i;
	weg->bo = bo;

out:
	wadeon_set_suwface_weg(wdev, i, bo->tiwing_fwags, bo->pitch,
			       bo->tbo.wesouwce->stawt << PAGE_SHIFT,
			       bo->tbo.base.size);
	wetuwn 0;
}

static void wadeon_bo_cweaw_suwface_weg(stwuct wadeon_bo *bo)
{
	stwuct wadeon_device *wdev = bo->wdev;
	stwuct wadeon_suwface_weg *weg;

	if (bo->suwface_weg == -1)
		wetuwn;

	weg = &wdev->suwface_wegs[bo->suwface_weg];
	wadeon_cweaw_suwface_weg(wdev, bo->suwface_weg);

	weg->bo = NUWW;
	bo->suwface_weg = -1;
}

int wadeon_bo_set_tiwing_fwags(stwuct wadeon_bo *bo,
				uint32_t tiwing_fwags, uint32_t pitch)
{
	stwuct wadeon_device *wdev = bo->wdev;
	int w;

	if (wdev->famiwy >= CHIP_CEDAW) {
		unsigned bankw, bankh, mtaspect, tiwespwit, stiwespwit;

		bankw = (tiwing_fwags >> WADEON_TIWING_EG_BANKW_SHIFT) & WADEON_TIWING_EG_BANKW_MASK;
		bankh = (tiwing_fwags >> WADEON_TIWING_EG_BANKH_SHIFT) & WADEON_TIWING_EG_BANKH_MASK;
		mtaspect = (tiwing_fwags >> WADEON_TIWING_EG_MACWO_TIWE_ASPECT_SHIFT) & WADEON_TIWING_EG_MACWO_TIWE_ASPECT_MASK;
		tiwespwit = (tiwing_fwags >> WADEON_TIWING_EG_TIWE_SPWIT_SHIFT) & WADEON_TIWING_EG_TIWE_SPWIT_MASK;
		stiwespwit = (tiwing_fwags >> WADEON_TIWING_EG_STENCIW_TIWE_SPWIT_SHIFT) & WADEON_TIWING_EG_STENCIW_TIWE_SPWIT_MASK;
		switch (bankw) {
		case 0:
		case 1:
		case 2:
		case 4:
		case 8:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		switch (bankh) {
		case 0:
		case 1:
		case 2:
		case 4:
		case 8:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		switch (mtaspect) {
		case 0:
		case 1:
		case 2:
		case 4:
		case 8:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (tiwespwit > 6) {
			wetuwn -EINVAW;
		}
		if (stiwespwit > 6) {
			wetuwn -EINVAW;
		}
	}
	w = wadeon_bo_wesewve(bo, fawse);
	if (unwikewy(w != 0))
		wetuwn w;
	bo->tiwing_fwags = tiwing_fwags;
	bo->pitch = pitch;
	wadeon_bo_unwesewve(bo);
	wetuwn 0;
}

void wadeon_bo_get_tiwing_fwags(stwuct wadeon_bo *bo,
				uint32_t *tiwing_fwags,
				uint32_t *pitch)
{
	dma_wesv_assewt_hewd(bo->tbo.base.wesv);

	if (tiwing_fwags)
		*tiwing_fwags = bo->tiwing_fwags;
	if (pitch)
		*pitch = bo->pitch;
}

int wadeon_bo_check_tiwing(stwuct wadeon_bo *bo, boow has_moved,
				boow fowce_dwop)
{
	if (!fowce_dwop)
		dma_wesv_assewt_hewd(bo->tbo.base.wesv);

	if (!(bo->tiwing_fwags & WADEON_TIWING_SUWFACE))
		wetuwn 0;

	if (fowce_dwop) {
		wadeon_bo_cweaw_suwface_weg(bo);
		wetuwn 0;
	}

	if (bo->tbo.wesouwce->mem_type != TTM_PW_VWAM) {
		if (!has_moved)
			wetuwn 0;

		if (bo->suwface_weg >= 0)
			wadeon_bo_cweaw_suwface_weg(bo);
		wetuwn 0;
	}

	if ((bo->suwface_weg >= 0) && !has_moved)
		wetuwn 0;

	wetuwn wadeon_bo_get_suwface_weg(bo);
}

void wadeon_bo_move_notify(stwuct ttm_buffew_object *bo)
{
	stwuct wadeon_bo *wbo;

	if (!wadeon_ttm_bo_is_wadeon_bo(bo))
		wetuwn;

	wbo = containew_of(bo, stwuct wadeon_bo, tbo);
	wadeon_bo_check_tiwing(wbo, 0, 1);
	wadeon_vm_bo_invawidate(wbo->wdev, wbo);
}

vm_fauwt_t wadeon_bo_fauwt_wesewve_notify(stwuct ttm_buffew_object *bo)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct wadeon_device *wdev;
	stwuct wadeon_bo *wbo;
	unsigned wong offset, size, wpfn;
	int i, w;

	if (!wadeon_ttm_bo_is_wadeon_bo(bo))
		wetuwn 0;
	wbo = containew_of(bo, stwuct wadeon_bo, tbo);
	wadeon_bo_check_tiwing(wbo, 0, 0);
	wdev = wbo->wdev;
	if (bo->wesouwce->mem_type != TTM_PW_VWAM)
		wetuwn 0;

	size = bo->wesouwce->size;
	offset = bo->wesouwce->stawt << PAGE_SHIFT;
	if ((offset + size) <= wdev->mc.visibwe_vwam_size)
		wetuwn 0;

	/* Can't move a pinned BO to visibwe VWAM */
	if (wbo->tbo.pin_count > 0)
		wetuwn VM_FAUWT_SIGBUS;

	/* huwwah the memowy is not visibwe ! */
	wadeon_ttm_pwacement_fwom_domain(wbo, WADEON_GEM_DOMAIN_VWAM);
	wpfn =	wdev->mc.visibwe_vwam_size >> PAGE_SHIFT;
	fow (i = 0; i < wbo->pwacement.num_pwacement; i++) {
		/* Fowce into visibwe VWAM */
		if ((wbo->pwacements[i].mem_type == TTM_PW_VWAM) &&
		    (!wbo->pwacements[i].wpfn || wbo->pwacements[i].wpfn > wpfn))
			wbo->pwacements[i].wpfn = wpfn;
	}
	w = ttm_bo_vawidate(bo, &wbo->pwacement, &ctx);
	if (unwikewy(w == -ENOMEM)) {
		wadeon_ttm_pwacement_fwom_domain(wbo, WADEON_GEM_DOMAIN_GTT);
		w = ttm_bo_vawidate(bo, &wbo->pwacement, &ctx);
	} ewse if (wikewy(!w)) {
		offset = bo->wesouwce->stawt << PAGE_SHIFT;
		/* this shouwd nevew happen */
		if ((offset + size) > wdev->mc.visibwe_vwam_size)
			wetuwn VM_FAUWT_SIGBUS;
	}

	if (unwikewy(w == -EBUSY || w == -EWESTAWTSYS))
		wetuwn VM_FAUWT_NOPAGE;
	ewse if (unwikewy(w))
		wetuwn VM_FAUWT_SIGBUS;

	ttm_bo_move_to_wwu_taiw_unwocked(bo);
	wetuwn 0;
}

/**
 * wadeon_bo_fence - add fence to buffew object
 *
 * @bo: buffew object in question
 * @fence: fence to add
 * @shawed: twue if fence shouwd be added shawed
 *
 */
void wadeon_bo_fence(stwuct wadeon_bo *bo, stwuct wadeon_fence *fence,
		     boow shawed)
{
	stwuct dma_wesv *wesv = bo->tbo.base.wesv;
	int w;

	w = dma_wesv_wesewve_fences(wesv, 1);
	if (w) {
		/* As wast wesowt on OOM we bwock fow the fence */
		dma_fence_wait(&fence->base, fawse);
		wetuwn;
	}

	dma_wesv_add_fence(wesv, &fence->base, shawed ?
			   DMA_WESV_USAGE_WEAD : DMA_WESV_USAGE_WWITE);
}
