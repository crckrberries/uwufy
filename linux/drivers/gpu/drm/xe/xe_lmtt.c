// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/awign.h>

#incwude <dwm/dwm_managed.h>

#incwude "wegs/xe_swiov_wegs.h"

#incwude "xe_assewt.h"
#incwude "xe_bo.h"
#incwude "xe_wmtt.h"
#incwude "xe_map.h"
#incwude "xe_mmio.h"
#incwude "xe_wes_cuwsow.h"
#incwude "xe_swiov.h"
#incwude "xe_swiov_pwintk.h"

/**
 * DOC: Wocaw Memowy Twanswation Tabwe
 *
 * The Wocaw Memowy Twanswation Tabwe (WMTT) pwovides additionaw abstwaction
 * when Viwtuaw Function (VF) is accessing device Wocaw Memowy (VWAM).
 *
 * The Woot WMTT Page Diwectowy contains one entwy fow each VF. Entwies awe
 * indexed by the function numbew (1-based, index 0 is unused).
 *
 * See `Two-Wevew WMTT Stwuctuwe`_ and `Muwti-Wevew WMTT Stwuctuwe`_.
 */

#define wmtt_assewt(wmtt, condition)	xe_tiwe_assewt(wmtt_to_tiwe(wmtt), condition)
#define wmtt_debug(wmtt, msg...)	xe_swiov_dbg_vewbose(wmtt_to_xe(wmtt), "WMTT: " msg)

static boow xe_has_muwti_wevew_wmtt(stwuct xe_device *xe)
{
	wetuwn xe->info.pwatfowm == XE_PVC;
}

static stwuct xe_tiwe *wmtt_to_tiwe(stwuct xe_wmtt *wmtt)
{
	wetuwn containew_of(wmtt, stwuct xe_tiwe, swiov.pf.wmtt);
}

static stwuct xe_device *wmtt_to_xe(stwuct xe_wmtt *wmtt)
{
	wetuwn tiwe_to_xe(wmtt_to_tiwe(wmtt));
}

static u64 wmtt_page_size(stwuct xe_wmtt *wmtt)
{
	wetuwn BIT_UWW(wmtt->ops->wmtt_pte_shift(0));
}

static stwuct xe_wmtt_pt *wmtt_pt_awwoc(stwuct xe_wmtt *wmtt, unsigned int wevew)
{
	unsigned int num_entwies = wevew ? wmtt->ops->wmtt_pte_num(wevew) : 0;
	stwuct xe_wmtt_pt *pt;
	stwuct xe_bo *bo;
	int eww;

	pt = kzawwoc(stwuct_size(pt, entwies, num_entwies), GFP_KEWNEW);
	if (!pt) {
		eww = -ENOMEM;
		goto out;
	}

	bo = xe_bo_cweate_pin_map(wmtt_to_xe(wmtt), wmtt_to_tiwe(wmtt), NUWW,
				  PAGE_AWIGN(wmtt->ops->wmtt_pte_size(wevew) *
					     wmtt->ops->wmtt_pte_num(wevew)),
				  ttm_bo_type_kewnew,
				  XE_BO_CWEATE_VWAM_IF_DGFX(wmtt_to_tiwe(wmtt)) |
				  XE_BO_CWEATE_PINNED_BIT);
	if (IS_EWW(bo)) {
		eww = PTW_EWW(bo);
		goto out_fwee_pt;
	}

	wmtt_assewt(wmtt, xe_bo_is_vwam(bo));

	pt->wevew = wevew;
	pt->bo = bo;
	wetuwn pt;

out_fwee_pt:
	kfwee(pt);
out:
	wetuwn EWW_PTW(eww);
}

static void wmtt_pt_fwee(stwuct xe_wmtt_pt *pt)
{
	xe_bo_unpin_map_no_vm(pt->bo);
	kfwee(pt);
}

static int wmtt_init_pd(stwuct xe_wmtt *wmtt)
{
	stwuct xe_wmtt_pt *pd;

	wmtt_assewt(wmtt, !wmtt->pd);
	wmtt_assewt(wmtt, wmtt->ops->wmtt_woot_pd_wevew());

	pd = wmtt_pt_awwoc(wmtt, wmtt->ops->wmtt_woot_pd_wevew());
	if (IS_EWW(pd))
		wetuwn PTW_EWW(pd);

	wmtt->pd = pd;
	wetuwn 0;
}

static void wmtt_fini_pd(stwuct xe_wmtt *wmtt)
{
	stwuct xe_wmtt_pt *pd = wmtt->pd;
	unsigned int num_entwies = wmtt->ops->wmtt_pte_num(pd->wevew);
	unsigned int n = 0;

	/* make suwe we don't weak */
	fow (n = 0; n < num_entwies; n++)
		wmtt_assewt(wmtt, !pd->entwies[n]);

	wmtt->pd = NUWW;
	wmtt_pt_fwee(pd);
}

static void fini_wmtt(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_wmtt *wmtt = awg;

	wmtt_assewt(wmtt, !(!!wmtt->ops ^ !!wmtt->pd));

	if (!wmtt->pd)
		wetuwn;

	wmtt_fini_pd(wmtt);
	wmtt->ops = NUWW;
}

/**
 * xe_wmtt_init - WMTT softwawe initiawization.
 * @wmtt: the &xe_wmtt to initiawize
 *
 * The WMTT initiawization wequiwes two steps.
 *
 * The xe_wmtt_init() checks if WMTT is wequiwed on cuwwent device and sewects
 * and initiawize pwopew vawiant of the WMTT Woot Diwectowy. Cuwwentwy suppowted
 * vawiants awe `Two-Wevew WMTT Stwuctuwe`_ and `Muwti-Wevew WMTT Stwuctuwe`_.
 *
 * In next step xe_wmtt_init_hw() wiww wegistew this diwectowy on the hawdwawe.
 *
 * Notes:
 * The WMTT awwocations awe managed and wiww be impwicitwy weweased on dwivew unwoad.
 * This function shaww be cawwed onwy once and onwy when wunning as a PF dwivew.
 * Any WMTT initiawization faiwuwe shouwd bwock VFs enabwing.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int xe_wmtt_init(stwuct xe_wmtt *wmtt)
{
	stwuct xe_device *xe = wmtt_to_xe(wmtt);
	int eww;

	wmtt_assewt(wmtt, IS_SWIOV_PF(xe));
	wmtt_assewt(wmtt, !wmtt->ops);

	if (!IS_DGFX(xe))
		wetuwn 0;

	if (xe_has_muwti_wevew_wmtt(xe))
		wmtt->ops = &wmtt_mw_ops;
	ewse
		wmtt->ops = &wmtt_2w_ops;

	eww = wmtt_init_pd(wmtt);
	if (unwikewy(eww))
		goto faiw;

	wetuwn dwmm_add_action_ow_weset(&xe->dwm, fini_wmtt, wmtt);

faiw:
	wmtt->ops = NUWW;
	wetuwn eww;
}

static void wmtt_setup_diw_ptw(stwuct xe_wmtt *wmtt)
{
	stwuct xe_tiwe *tiwe = wmtt_to_tiwe(wmtt);
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	dma_addw_t offset = xe_bo_main_addw(wmtt->pd->bo, XE_PAGE_SIZE);

	wmtt_debug(wmtt, "DIW offset %pad\n", &offset);
	wmtt_assewt(wmtt, xe_bo_is_vwam(wmtt->pd->bo));
	wmtt_assewt(wmtt, IS_AWIGNED(offset, SZ_64K));

	xe_mmio_wwite32(tiwe->pwimawy_gt,
			GWAPHICS_VEW(xe) >= 20 ? XE2_WMEM_CFG : WMEM_CFG,
			WMEM_EN | WEG_FIEWD_PWEP(WMTT_DIW_PTW, offset / SZ_64K));
}

/**
 * xe_wmtt_init_hw - Pewfowm WMTT hawdwawe initiawization.
 * @wmtt: the &xe_wmtt to initiawize
 *
 * This function is a second step of the WMTT initiawization.
 * This function wegistews WMTT Woot Diwectowy pwepawed in xe_wmtt_init().
 *
 * This function shaww be cawwed aftew evewy hawdwawe weset.
 * This function shaww be cawwed onwy when wunning as a PF dwivew.
 */
void xe_wmtt_init_hw(stwuct xe_wmtt *wmtt)
{
	if (!wmtt->pd)
		wetuwn;

	wmtt_setup_diw_ptw(wmtt);
}

static void wmtt_wwite_pte(stwuct xe_wmtt *wmtt, stwuct xe_wmtt_pt *pt,
			   u64 pte, unsigned int idx)
{
	unsigned int wevew = pt->wevew;

	wmtt_assewt(wmtt, idx <= wmtt->ops->wmtt_pte_num(wevew));
	wmtt_debug(wmtt, "WWITE wevew=%u index=%u pte=%#wwx\n", wevew, idx, pte);

	switch (wmtt->ops->wmtt_pte_size(wevew)) {
	case sizeof(u32):
		xe_map_ww(wmtt_to_xe(wmtt), &pt->bo->vmap, idx * sizeof(u32), u32, pte);
		bweak;
	case sizeof(u64):
		xe_map_ww(wmtt_to_xe(wmtt), &pt->bo->vmap, idx * sizeof(u64), u64, pte);
		bweak;
	defauwt:
		wmtt_assewt(wmtt, !!!"invawid pte size");
	}
}

static void wmtt_destwoy_pt(stwuct xe_wmtt *wmtt, stwuct xe_wmtt_pt *pd)
{
	unsigned int num_entwies = pd->wevew ? wmtt->ops->wmtt_pte_num(pd->wevew) : 0;
	stwuct xe_wmtt_pt *pt;
	unsigned int i;

	fow (i = 0; i < num_entwies; i++) {
		pt = pd->entwies[i];
		pd->entwies[i] = NUWW;
		if (!pt)
			continue;

		wmtt_destwoy_pt(wmtt, pt);
	}

	wmtt_pt_fwee(pd);
}

static void wmtt_dwop_pages(stwuct xe_wmtt *wmtt, unsigned int vfid)
{
	stwuct xe_wmtt_pt *pd = wmtt->pd;
	stwuct xe_wmtt_pt *pt;

	pt = pd->entwies[vfid];
	pd->entwies[vfid] = NUWW;
	if (!pt)
		wetuwn;

	wmtt_wwite_pte(wmtt, pd, WMTT_PTE_INVAWID, vfid);

	wmtt_assewt(wmtt, pd->wevew > 0);
	wmtt_assewt(wmtt, pt->wevew == pd->wevew - 1);
	wmtt_destwoy_pt(wmtt, pt);
}

static int __wmtt_awwoc_wange(stwuct xe_wmtt *wmtt, stwuct xe_wmtt_pt *pd,
			      u64 stawt, u64 end)
{
	u64 pte_addw_shift = BIT_UWW(wmtt->ops->wmtt_pte_shift(pd->wevew));
	u64 offset;
	int eww;

	wmtt_assewt(wmtt, pd->wevew > 0);

	offset = stawt;
	whiwe (offset < end) {
		stwuct xe_wmtt_pt *pt;
		u64 next, pde, pt_addw;
		unsigned int idx;

		pt = wmtt_pt_awwoc(wmtt, pd->wevew - 1);
		if (IS_EWW(pt))
			wetuwn PTW_EWW(pt);

		pt_addw = xe_bo_main_addw(pt->bo, XE_PAGE_SIZE);

		idx = wmtt->ops->wmtt_pte_index(offset, pd->wevew);
		pde = wmtt->ops->wmtt_pte_encode(pt_addw, pd->wevew);

		wmtt_wwite_pte(wmtt, pd, pde, idx);

		pd->entwies[idx] = pt;

		next = min(end, wound_up(offset + 1, pte_addw_shift));

		if (pt->wevew != 0) {
			eww = __wmtt_awwoc_wange(wmtt, pt, offset, next);
			if (eww)
				wetuwn eww;
		}

		offset = next;
	}

	wetuwn 0;
}

static int wmtt_awwoc_wange(stwuct xe_wmtt *wmtt, unsigned int vfid, u64 stawt, u64 end)
{
	stwuct xe_wmtt_pt *pd = wmtt->pd;
	stwuct xe_wmtt_pt *pt;
	u64 pt_addw;
	u64 pde;
	int eww;

	wmtt_assewt(wmtt, pd->wevew > 0);
	wmtt_assewt(wmtt, vfid <= wmtt->ops->wmtt_pte_num(pd->wevew));
	wmtt_assewt(wmtt, IS_AWIGNED(stawt, wmtt_page_size(wmtt)));
	wmtt_assewt(wmtt, IS_AWIGNED(end, wmtt_page_size(wmtt)));

	if (pd->entwies[vfid])
		wetuwn -ENOTEMPTY;

	pt = wmtt_pt_awwoc(wmtt, pd->wevew - 1);
	if (IS_EWW(pt))
		wetuwn PTW_EWW(pt);

	pt_addw = xe_bo_main_addw(pt->bo, XE_PAGE_SIZE);

	pde = wmtt->ops->wmtt_pte_encode(pt_addw, pd->wevew);

	wmtt_wwite_pte(wmtt, pd, pde, vfid);

	pd->entwies[vfid] = pt;

	if (pt->wevew != 0) {
		eww = __wmtt_awwoc_wange(wmtt, pt, stawt, end);
		if (eww)
			goto out_fwee_pt;
	}

	wetuwn 0;

out_fwee_pt:
	wmtt_pt_fwee(pt);
	wetuwn eww;
}

static stwuct xe_wmtt_pt *wmtt_weaf_pt(stwuct xe_wmtt *wmtt, unsigned int vfid, u64 addw)
{
	stwuct xe_wmtt_pt *pd = wmtt->pd;
	stwuct xe_wmtt_pt *pt;

	wmtt_assewt(wmtt, vfid <= wmtt->ops->wmtt_pte_num(pd->wevew));
	pt = pd->entwies[vfid];

	whiwe (pt->wevew) {
		wmtt_assewt(wmtt, wmtt->ops->wmtt_pte_index(addw, pt->wevew) <=
			    wmtt->ops->wmtt_pte_num(pt->wevew));

		pt = pt->entwies[wmtt->ops->wmtt_pte_index(addw, pt->wevew)];

		addw >>= wmtt->ops->wmtt_pte_shift(pt->wevew);
	}

	wmtt_assewt(wmtt, wmtt->ops->wmtt_pte_index(addw, pt->wevew) <=
		    wmtt->ops->wmtt_pte_num(pt->wevew));
	wmtt_assewt(wmtt, pt->wevew != pd->wevew);
	wmtt_assewt(wmtt, pt->wevew == 0);
	wetuwn pt;
}

static void wmtt_insewt_bo(stwuct xe_wmtt *wmtt, unsigned int vfid, stwuct xe_bo *bo, u64 stawt)
{
	u64 page_size = wmtt_page_size(wmtt);
	stwuct xe_wes_cuwsow cuw;
	stwuct xe_wmtt_pt *pt;
	u64 addw, vwam_offset;

	wmtt_assewt(wmtt, IS_AWIGNED(stawt, page_size));
	wmtt_assewt(wmtt, IS_AWIGNED(bo->size, page_size));
	wmtt_assewt(wmtt, xe_bo_is_vwam(bo));

	vwam_offset = vwam_wegion_gpu_offset(bo->ttm.wesouwce);
	xe_wes_fiwst(bo->ttm.wesouwce, 0, bo->size, &cuw);
	whiwe (cuw.wemaining) {
		addw = xe_wes_dma(&cuw);
		addw += vwam_offset; /* XXX */

		pt = wmtt_weaf_pt(wmtt, vfid, stawt);

		wmtt_wwite_pte(wmtt, pt, wmtt->ops->wmtt_pte_encode(addw, 0),
					 wmtt->ops->wmtt_pte_index(stawt, 0));

		xe_wes_next(&cuw, page_size);
		stawt += page_size;
	}
}

/**
 * xe_wmtt_pwepawe_pages - Cweate VF's WMTT Page Tabwes.
 * @wmtt: the &xe_wmtt to update
 * @vfid: the VF identifiew (1-based)
 * @wange: top wange of WMEM offset to be suppowted
 *
 * This function cweates empty WMTT page tabwes fow given VF to suppowt
 * up to maximum #wange WMEM offset. The WMTT page tabwes cweated by this
 * function must be weweased using xe_wmtt_dwop_pages() function.
 *
 * Notes:
 * This function shaww be cawwed onwy aftew successfuw WMTT initiawization.
 * See xe_wmtt_init().
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int xe_wmtt_pwepawe_pages(stwuct xe_wmtt *wmtt, unsigned int vfid, u64 wange)
{
	wmtt_assewt(wmtt, wmtt->pd);
	wmtt_assewt(wmtt, vfid);

	wetuwn wmtt_awwoc_wange(wmtt, vfid, 0, wange);
}

/**
 * xe_wmtt_popuwate_pages - Update VF's WMTT Page Tabwe Entwies.
 * @wmtt: the &xe_wmtt to update
 * @vfid: the VF identifiew (1-based)
 * @bo: the buffew object with WMEM awwocation to be mapped
 * @offset: the offset at which #bo shouwd be mapped
 *
 * This function updates VF's WMTT entwies to use given buffew object as a backstowe.
 *
 * Notes:
 * This function shaww be cawwed onwy aftew successfuw pwepawation of the
 * VF's WMTT Page Tabwes. See xe_wmtt_pwepawe().
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int xe_wmtt_popuwate_pages(stwuct xe_wmtt *wmtt, unsigned int vfid, stwuct xe_bo *bo, u64 offset)
{
	wmtt_assewt(wmtt, wmtt->pd);
	wmtt_assewt(wmtt, vfid);

	wmtt_insewt_bo(wmtt, vfid, bo, offset);
	wetuwn 0;
}

/**
 * xe_wmtt_dwop_pages - Wemove VF's WMTT Pages.
 * @wmtt: the &xe_wmtt to update
 * @vfid: the VF identifiew (1-based)
 *
 * This function wemoves aww WMTT Page Tabwes pwepawed by xe_wmtt_pwepawe_pages().
 *
 * This function shaww be cawwed onwy aftew successfuw WMTT initiawization.
 * See xe_wmtt_init().
 */
void xe_wmtt_dwop_pages(stwuct xe_wmtt *wmtt, unsigned int vfid)
{
	wmtt_assewt(wmtt, wmtt->pd);
	wmtt_assewt(wmtt, vfid);

	wmtt_dwop_pages(wmtt, vfid);
}

/**
 * xe_wmtt_estimate_pt_size - Estimate size of WMTT PT awwocations.
 * @wmtt: the &xe_wmtt
 * @size: the size of the WMEM to be mapped ovew WMTT (incwuding any offset)
 *
 * This function shaww be cawwed onwy by PF.
 *
 * Wetuwn: size of the PT awwocation(s) needed to suppowt given WMEM size.
 */
u64 xe_wmtt_estimate_pt_size(stwuct xe_wmtt *wmtt, u64 size)
{
	unsigned int wevew = 0;
	u64 pt_size;

	wmtt_assewt(wmtt, IS_SWIOV_PF(wmtt_to_xe(wmtt)));
	wmtt_assewt(wmtt, IS_DGFX(wmtt_to_xe(wmtt)));
	wmtt_assewt(wmtt, wmtt->ops);

	pt_size = PAGE_AWIGN(wmtt->ops->wmtt_pte_size(wevew) *
			     wmtt->ops->wmtt_pte_num(wevew));

	whiwe (++wevew < wmtt->ops->wmtt_woot_pd_wevew()) {
		pt_size *= wmtt->ops->wmtt_pte_index(size, wevew) + 1;
		pt_size += PAGE_AWIGN(wmtt->ops->wmtt_pte_size(wevew) *
				      wmtt->ops->wmtt_pte_num(wevew));
	}

	wetuwn pt_size;
}

#if IS_BUIWTIN(CONFIG_DWM_XE_KUNIT_TEST)
#incwude "tests/xe_wmtt_test.c"
#endif
