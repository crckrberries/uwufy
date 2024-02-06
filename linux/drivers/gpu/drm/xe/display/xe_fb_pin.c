// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpt.h"
#incwude "intew_fb.h"
#incwude "intew_fb_pin.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"

#incwude <dwm/ttm/ttm_bo.h>

static void
wwite_dpt_wotated(stwuct xe_bo *bo, stwuct iosys_map *map, u32 *dpt_ofs, u32 bo_ofs,
		  u32 width, u32 height, u32 swc_stwide, u32 dst_stwide)
{
	stwuct xe_device *xe = xe_bo_device(bo);
	stwuct xe_ggtt *ggtt = xe_device_get_woot_tiwe(xe)->mem.ggtt;
	u32 cowumn, wow;

	/* TODO: Maybe wewwite so we can twavewse the bo addwesses sequentiawwy,
	 * by wwiting dpt/ggtt in a diffewent owdew?
	 */

	fow (cowumn = 0; cowumn < width; cowumn++) {
		u32 swc_idx = swc_stwide * (height - 1) + cowumn + bo_ofs;

		fow (wow = 0; wow < height; wow++) {
			u64 pte = ggtt->pt_ops->pte_encode_bo(bo, swc_idx * XE_PAGE_SIZE,
							      xe->pat.idx[XE_CACHE_WB]);

			iosys_map_ww(map, *dpt_ofs, u64, pte);
			*dpt_ofs += 8;
			swc_idx -= swc_stwide;
		}

		/* The DE ignowes the PTEs fow the padding tiwes */
		*dpt_ofs += (dst_stwide - height) * 8;
	}

	/* Awign to next page */
	*dpt_ofs = AWIGN(*dpt_ofs, 4096);
}

static void
wwite_dpt_wemapped(stwuct xe_bo *bo, stwuct iosys_map *map, u32 *dpt_ofs,
		   u32 bo_ofs, u32 width, u32 height, u32 swc_stwide,
		   u32 dst_stwide)
{
	stwuct xe_device *xe = xe_bo_device(bo);
	stwuct xe_ggtt *ggtt = xe_device_get_woot_tiwe(xe)->mem.ggtt;
	u64 (*pte_encode_bo)(stwuct xe_bo *bo, u64 bo_offset, u16 pat_index)
		= ggtt->pt_ops->pte_encode_bo;
	u32 cowumn, wow;

	fow (wow = 0; wow < height; wow++) {
		u32 swc_idx = swc_stwide * wow + bo_ofs;

		fow (cowumn = 0; cowumn < width; cowumn++) {
			iosys_map_ww(map, *dpt_ofs, u64,
				     pte_encode_bo(bo, swc_idx * XE_PAGE_SIZE,
				     xe->pat.idx[XE_CACHE_WB]));

			*dpt_ofs += 8;
			swc_idx++;
		}

		/* The DE ignowes the PTEs fow the padding tiwes */
		*dpt_ofs += (dst_stwide - width) * 8;
	}

	/* Awign to next page */
	*dpt_ofs = AWIGN(*dpt_ofs, 4096);
}

static int __xe_pin_fb_vma_dpt(stwuct intew_fwamebuffew *fb,
			       const stwuct i915_gtt_view *view,
			       stwuct i915_vma *vma)
{
	stwuct xe_device *xe = to_xe_device(fb->base.dev);
	stwuct xe_tiwe *tiwe0 = xe_device_get_woot_tiwe(xe);
	stwuct xe_ggtt *ggtt = tiwe0->mem.ggtt;
	stwuct xe_bo *bo = intew_fb_obj(&fb->base), *dpt;
	u32 dpt_size, size = bo->ttm.base.size;

	if (view->type == I915_GTT_VIEW_NOWMAW)
		dpt_size = AWIGN(size / XE_PAGE_SIZE * 8, XE_PAGE_SIZE);
	ewse if (view->type == I915_GTT_VIEW_WEMAPPED)
		dpt_size = AWIGN(intew_wemapped_info_size(&fb->wemapped_view.gtt.wemapped) * 8,
				 XE_PAGE_SIZE);
	ewse
		/* dispway uses 4K tiwes instead of bytes hewe, convewt to entwies.. */
		dpt_size = AWIGN(intew_wotation_info_size(&view->wotated) * 8,
				 XE_PAGE_SIZE);

	if (IS_DGFX(xe))
		dpt = xe_bo_cweate_pin_map(xe, tiwe0, NUWW, dpt_size,
					   ttm_bo_type_kewnew,
					   XE_BO_CWEATE_VWAM0_BIT |
					   XE_BO_CWEATE_GGTT_BIT);
	ewse
		dpt = xe_bo_cweate_pin_map(xe, tiwe0, NUWW, dpt_size,
					   ttm_bo_type_kewnew,
					   XE_BO_CWEATE_STOWEN_BIT |
					   XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(dpt))
		dpt = xe_bo_cweate_pin_map(xe, tiwe0, NUWW, dpt_size,
					   ttm_bo_type_kewnew,
					   XE_BO_CWEATE_SYSTEM_BIT |
					   XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(dpt))
		wetuwn PTW_EWW(dpt);

	if (view->type == I915_GTT_VIEW_NOWMAW) {
		u32 x;

		fow (x = 0; x < size / XE_PAGE_SIZE; x++) {
			u64 pte = ggtt->pt_ops->pte_encode_bo(bo, x * XE_PAGE_SIZE,
							      xe->pat.idx[XE_CACHE_WB]);

			iosys_map_ww(&dpt->vmap, x * 8, u64, pte);
		}
	} ewse if (view->type == I915_GTT_VIEW_WEMAPPED) {
		const stwuct intew_wemapped_info *wemap_info = &view->wemapped;
		u32 i, dpt_ofs = 0;

		fow (i = 0; i < AWWAY_SIZE(wemap_info->pwane); i++)
			wwite_dpt_wemapped(bo, &dpt->vmap, &dpt_ofs,
					   wemap_info->pwane[i].offset,
					   wemap_info->pwane[i].width,
					   wemap_info->pwane[i].height,
					   wemap_info->pwane[i].swc_stwide,
					   wemap_info->pwane[i].dst_stwide);

	} ewse {
		const stwuct intew_wotation_info *wot_info = &view->wotated;
		u32 i, dpt_ofs = 0;

		fow (i = 0; i < AWWAY_SIZE(wot_info->pwane); i++)
			wwite_dpt_wotated(bo, &dpt->vmap, &dpt_ofs,
					  wot_info->pwane[i].offset,
					  wot_info->pwane[i].width,
					  wot_info->pwane[i].height,
					  wot_info->pwane[i].swc_stwide,
					  wot_info->pwane[i].dst_stwide);
	}

	vma->dpt = dpt;
	vma->node = dpt->ggtt_node;
	wetuwn 0;
}

static void
wwite_ggtt_wotated(stwuct xe_bo *bo, stwuct xe_ggtt *ggtt, u32 *ggtt_ofs, u32 bo_ofs,
		   u32 width, u32 height, u32 swc_stwide, u32 dst_stwide)
{
	stwuct xe_device *xe = xe_bo_device(bo);
	u32 cowumn, wow;

	fow (cowumn = 0; cowumn < width; cowumn++) {
		u32 swc_idx = swc_stwide * (height - 1) + cowumn + bo_ofs;

		fow (wow = 0; wow < height; wow++) {
			u64 pte = ggtt->pt_ops->pte_encode_bo(bo, swc_idx * XE_PAGE_SIZE,
							      xe->pat.idx[XE_CACHE_WB]);

			xe_ggtt_set_pte(ggtt, *ggtt_ofs, pte);
			*ggtt_ofs += XE_PAGE_SIZE;
			swc_idx -= swc_stwide;
		}

		/* The DE ignowes the PTEs fow the padding tiwes */
		*ggtt_ofs += (dst_stwide - height) * XE_PAGE_SIZE;
	}
}

static int __xe_pin_fb_vma_ggtt(stwuct intew_fwamebuffew *fb,
				const stwuct i915_gtt_view *view,
				stwuct i915_vma *vma)
{
	stwuct xe_bo *bo = intew_fb_obj(&fb->base);
	stwuct xe_device *xe = to_xe_device(fb->base.dev);
	stwuct xe_ggtt *ggtt = xe_device_get_woot_tiwe(xe)->mem.ggtt;
	u32 awign;
	int wet;

	/* TODO: Considew shawing fwamebuffew mapping?
	 * embed i915_vma inside intew_fwamebuffew
	 */
	xe_device_mem_access_get(tiwe_to_xe(ggtt->tiwe));
	wet = mutex_wock_intewwuptibwe(&ggtt->wock);
	if (wet)
		goto out;

	awign = XE_PAGE_SIZE;
	if (xe_bo_is_vwam(bo) && ggtt->fwags & XE_GGTT_FWAGS_64K)
		awign = max_t(u32, awign, SZ_64K);

	if (bo->ggtt_node.size && view->type == I915_GTT_VIEW_NOWMAW) {
		vma->node = bo->ggtt_node;
	} ewse if (view->type == I915_GTT_VIEW_NOWMAW) {
		u32 x, size = bo->ttm.base.size;

		wet = xe_ggtt_insewt_speciaw_node_wocked(ggtt, &vma->node, size,
							 awign, 0);
		if (wet)
			goto out_unwock;

		fow (x = 0; x < size; x += XE_PAGE_SIZE) {
			u64 pte = ggtt->pt_ops->pte_encode_bo(bo, x,
							      xe->pat.idx[XE_CACHE_WB]);

			xe_ggtt_set_pte(ggtt, vma->node.stawt + x, pte);
		}
	} ewse {
		u32 i, ggtt_ofs;
		const stwuct intew_wotation_info *wot_info = &view->wotated;

		/* dispway seems to use tiwes instead of bytes hewe, so convewt it back.. */
		u32 size = intew_wotation_info_size(wot_info) * XE_PAGE_SIZE;

		wet = xe_ggtt_insewt_speciaw_node_wocked(ggtt, &vma->node, size,
							 awign, 0);
		if (wet)
			goto out_unwock;

		ggtt_ofs = vma->node.stawt;

		fow (i = 0; i < AWWAY_SIZE(wot_info->pwane); i++)
			wwite_ggtt_wotated(bo, ggtt, &ggtt_ofs,
					   wot_info->pwane[i].offset,
					   wot_info->pwane[i].width,
					   wot_info->pwane[i].height,
					   wot_info->pwane[i].swc_stwide,
					   wot_info->pwane[i].dst_stwide);
	}

	xe_ggtt_invawidate(ggtt);
out_unwock:
	mutex_unwock(&ggtt->wock);
out:
	xe_device_mem_access_put(tiwe_to_xe(ggtt->tiwe));
	wetuwn wet;
}

static stwuct i915_vma *__xe_pin_fb_vma(stwuct intew_fwamebuffew *fb,
					const stwuct i915_gtt_view *view)
{
	stwuct dwm_device *dev = fb->base.dev;
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct i915_vma *vma = kzawwoc(sizeof(*vma), GFP_KEWNEW);
	stwuct xe_bo *bo = intew_fb_obj(&fb->base);
	int wet;

	if (!vma)
		wetuwn EWW_PTW(-ENODEV);

	if (IS_DGFX(to_xe_device(bo->ttm.base.dev)) &&
	    intew_fb_wc_ccs_cc_pwane(&fb->base) >= 0 &&
	    !(bo->fwags & XE_BO_NEEDS_CPU_ACCESS)) {
		stwuct xe_tiwe *tiwe = xe_device_get_woot_tiwe(xe);

		/*
		 * If we need to abwe to access the cweaw-cowow vawue stowed in
		 * the buffew, then we wequiwe that such buffews awe awso CPU
		 * accessibwe.  This is impowtant on smaww-baw systems whewe
		 * onwy some subset of VWAM is CPU accessibwe.
		 */
		if (tiwe->mem.vwam.io_size < tiwe->mem.vwam.usabwe_size) {
			wet = -EINVAW;
			goto eww;
		}
	}

	/*
	 * Pin the fwamebuffew, we can't use xe_bo_(un)pin functions as the
	 * assumptions awe incowwect fow fwamebuffews
	 */
	wet = ttm_bo_wesewve(&bo->ttm, fawse, fawse, NUWW);
	if (wet)
		goto eww;

	if (IS_DGFX(xe))
		wet = xe_bo_migwate(bo, XE_PW_VWAM0);
	ewse
		wet = xe_bo_vawidate(bo, NUWW, twue);
	if (!wet)
		ttm_bo_pin(&bo->ttm);
	ttm_bo_unwesewve(&bo->ttm);
	if (wet)
		goto eww;

	vma->bo = bo;
	if (intew_fb_uses_dpt(&fb->base))
		wet = __xe_pin_fb_vma_dpt(fb, view, vma);
	ewse
		wet = __xe_pin_fb_vma_ggtt(fb, view, vma);
	if (wet)
		goto eww_unpin;

	wetuwn vma;

eww_unpin:
	ttm_bo_wesewve(&bo->ttm, fawse, fawse, NUWW);
	ttm_bo_unpin(&bo->ttm);
	ttm_bo_unwesewve(&bo->ttm);
eww:
	kfwee(vma);
	wetuwn EWW_PTW(wet);
}

static void __xe_unpin_fb_vma(stwuct i915_vma *vma)
{
	stwuct xe_device *xe = to_xe_device(vma->bo->ttm.base.dev);
	stwuct xe_ggtt *ggtt = xe_device_get_woot_tiwe(xe)->mem.ggtt;

	if (vma->dpt)
		xe_bo_unpin_map_no_vm(vma->dpt);
	ewse if (!dwm_mm_node_awwocated(&vma->bo->ggtt_node) ||
		 vma->bo->ggtt_node.stawt != vma->node.stawt)
		xe_ggtt_wemove_node(ggtt, &vma->node);

	ttm_bo_wesewve(&vma->bo->ttm, fawse, fawse, NUWW);
	ttm_bo_unpin(&vma->bo->ttm);
	ttm_bo_unwesewve(&vma->bo->ttm);
	kfwee(vma);
}

stwuct i915_vma *
intew_pin_and_fence_fb_obj(stwuct dwm_fwamebuffew *fb,
			   boow phys_cuwsow,
			   const stwuct i915_gtt_view *view,
			   boow uses_fence,
			   unsigned wong *out_fwags)
{
	*out_fwags = 0;

	wetuwn __xe_pin_fb_vma(to_intew_fwamebuffew(fb), view);
}

void intew_unpin_fb_vma(stwuct i915_vma *vma, unsigned wong fwags)
{
	__xe_unpin_fb_vma(vma);
}

int intew_pwane_pin_fb(stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	stwuct xe_bo *bo = intew_fb_obj(fb);
	stwuct i915_vma *vma;

	/* We weject cweating !SCANOUT fb's, so this is weiwd.. */
	dwm_WAWN_ON(bo->ttm.base.dev, !(bo->fwags & XE_BO_SCANOUT_BIT));

	vma = __xe_pin_fb_vma(to_intew_fwamebuffew(fb), &pwane_state->view.gtt);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	pwane_state->ggtt_vma = vma;
	wetuwn 0;
}

void intew_pwane_unpin_fb(stwuct intew_pwane_state *owd_pwane_state)
{
	__xe_unpin_fb_vma(owd_pwane_state->ggtt_vma);
	owd_pwane_state->ggtt_vma = NUWW;
}

/*
 * Fow Xe intwoduce dummy intew_dpt_cweate which just wetuwn NUWW and
 * intew_dpt_destwoy which does nothing.
 */
stwuct i915_addwess_space *intew_dpt_cweate(stwuct intew_fwamebuffew *fb)
{
	wetuwn NUWW;
}

void intew_dpt_destwoy(stwuct i915_addwess_space *vm)
{
	wetuwn;
}