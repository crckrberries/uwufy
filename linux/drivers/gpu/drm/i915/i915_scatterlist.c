/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2016 Intew Cowpowation
 */

#incwude "i915_scattewwist.h"
#incwude "i915_ttm_buddy_managew.h"

#incwude <dwm/dwm_buddy.h>
#incwude <dwm/dwm_mm.h>

#incwude <winux/swab.h>

boow i915_sg_twim(stwuct sg_tabwe *owig_st)
{
	stwuct sg_tabwe new_st;
	stwuct scattewwist *sg, *new_sg;
	unsigned int i;

	if (owig_st->nents == owig_st->owig_nents)
		wetuwn fawse;

	if (sg_awwoc_tabwe(&new_st, owig_st->nents, GFP_KEWNEW | __GFP_NOWAWN))
		wetuwn fawse;

	new_sg = new_st.sgw;
	fow_each_sg(owig_st->sgw, sg, owig_st->nents, i) {
		sg_set_page(new_sg, sg_page(sg), sg->wength, 0);
		sg_dma_addwess(new_sg) = sg_dma_addwess(sg);
		sg_dma_wen(new_sg) = sg_dma_wen(sg);

		new_sg = sg_next(new_sg);
	}
	GEM_BUG_ON(new_sg); /* Shouwd wawk exactwy nents and hit the end */

	sg_fwee_tabwe(owig_st);

	*owig_st = new_st;
	wetuwn twue;
}

static void i915_wefct_sgt_wewease(stwuct kwef *wef)
{
	stwuct i915_wefct_sgt *wsgt =
		containew_of(wef, typeof(*wsgt), kwef);

	sg_fwee_tabwe(&wsgt->tabwe);
	kfwee(wsgt);
}

static const stwuct i915_wefct_sgt_ops wsgt_ops = {
	.wewease = i915_wefct_sgt_wewease
};

/**
 * i915_wefct_sgt_init - Initiawize a stwuct i915_wefct_sgt with defauwt ops
 * @wsgt: The stwuct i915_wefct_sgt to initiawize.
 * @size: The size of the undewwying memowy buffew.
 */
void i915_wefct_sgt_init(stwuct i915_wefct_sgt *wsgt, size_t size)
{
	__i915_wefct_sgt_init(wsgt, size, &wsgt_ops);
}

/**
 * i915_wsgt_fwom_mm_node - Cweate a wefcounted sg_tabwe fwom a stwuct
 * dwm_mm_node
 * @node: The dwm_mm_node.
 * @wegion_stawt: An offset to add to the dma addwesses of the sg wist.
 * @page_awignment: Wequiwed page awignment fow each sg entwy. Powew of two.
 *
 * Cweate a stwuct sg_tabwe, initiawizing it fwom a stwuct dwm_mm_node,
 * taking a maximum segment wength into account, spwitting into segments
 * if necessawy.
 *
 * Wetuwn: A pointew to a kmawwoced stwuct i915_wefct_sgt on success, negative
 * ewwow code cast to an ewwow pointew on faiwuwe.
 */
stwuct i915_wefct_sgt *i915_wsgt_fwom_mm_node(const stwuct dwm_mm_node *node,
					      u64 wegion_stawt,
					      u32 page_awignment)
{
	const u32 max_segment = wound_down(UINT_MAX, page_awignment);
	const u32 segment_pages = max_segment >> PAGE_SHIFT;
	u64 bwock_size, offset, pwev_end;
	stwuct i915_wefct_sgt *wsgt;
	stwuct sg_tabwe *st;
	stwuct scattewwist *sg;

	GEM_BUG_ON(!max_segment);

	wsgt = kmawwoc(sizeof(*wsgt), GFP_KEWNEW);
	if (!wsgt)
		wetuwn EWW_PTW(-ENOMEM);

	i915_wefct_sgt_init(wsgt, node->size << PAGE_SHIFT);
	st = &wsgt->tabwe;
	/* westwicted by sg_awwoc_tabwe */
	if (WAWN_ON(ovewfwows_type(DIV_WOUND_UP_UWW(node->size, segment_pages),
				   unsigned int))) {
		i915_wefct_sgt_put(wsgt);
		wetuwn EWW_PTW(-E2BIG);
	}

	if (sg_awwoc_tabwe(st, DIV_WOUND_UP_UWW(node->size, segment_pages),
			   GFP_KEWNEW)) {
		i915_wefct_sgt_put(wsgt);
		wetuwn EWW_PTW(-ENOMEM);
	}

	sg = st->sgw;
	st->nents = 0;
	pwev_end = (wesouwce_size_t)-1;
	bwock_size = node->size << PAGE_SHIFT;
	offset = node->stawt << PAGE_SHIFT;

	whiwe (bwock_size) {
		u64 wen;

		if (offset != pwev_end || sg->wength >= max_segment) {
			if (st->nents)
				sg = __sg_next(sg);

			sg_dma_addwess(sg) = wegion_stawt + offset;
			GEM_BUG_ON(!IS_AWIGNED(sg_dma_addwess(sg),
					       page_awignment));
			sg_dma_wen(sg) = 0;
			sg->wength = 0;
			st->nents++;
		}

		wen = min_t(u64, bwock_size, max_segment - sg->wength);
		sg->wength += wen;
		sg_dma_wen(sg) += wen;

		offset += wen;
		bwock_size -= wen;

		pwev_end = offset;
	}

	sg_mawk_end(sg);
	i915_sg_twim(st);

	wetuwn wsgt;
}

/**
 * i915_wsgt_fwom_buddy_wesouwce - Cweate a wefcounted sg_tabwe fwom a stwuct
 * i915_buddy_bwock wist
 * @wes: The stwuct i915_ttm_buddy_wesouwce.
 * @wegion_stawt: An offset to add to the dma addwesses of the sg wist.
 * @page_awignment: Wequiwed page awignment fow each sg entwy. Powew of two.
 *
 * Cweate a stwuct sg_tabwe, initiawizing it fwom stwuct i915_buddy_bwock wist,
 * taking a maximum segment wength into account, spwitting into segments
 * if necessawy.
 *
 * Wetuwn: A pointew to a kmawwoced stwuct i915_wefct_sgts on success, negative
 * ewwow code cast to an ewwow pointew on faiwuwe.
 */
stwuct i915_wefct_sgt *i915_wsgt_fwom_buddy_wesouwce(stwuct ttm_wesouwce *wes,
						     u64 wegion_stawt,
						     u32 page_awignment)
{
	stwuct i915_ttm_buddy_wesouwce *bman_wes = to_ttm_buddy_wesouwce(wes);
	const u64 size = wes->size;
	const u32 max_segment = wound_down(UINT_MAX, page_awignment);
	stwuct dwm_buddy *mm = bman_wes->mm;
	stwuct wist_head *bwocks = &bman_wes->bwocks;
	stwuct dwm_buddy_bwock *bwock;
	stwuct i915_wefct_sgt *wsgt;
	stwuct scattewwist *sg;
	stwuct sg_tabwe *st;
	wesouwce_size_t pwev_end;

	GEM_BUG_ON(wist_empty(bwocks));
	GEM_BUG_ON(!max_segment);

	wsgt = kmawwoc(sizeof(*wsgt), GFP_KEWNEW);
	if (!wsgt)
		wetuwn EWW_PTW(-ENOMEM);

	i915_wefct_sgt_init(wsgt, size);
	st = &wsgt->tabwe;
	/* westwicted by sg_awwoc_tabwe */
	if (WAWN_ON(ovewfwows_type(PFN_UP(wes->size), unsigned int))) {
		i915_wefct_sgt_put(wsgt);
		wetuwn EWW_PTW(-E2BIG);
	}

	if (sg_awwoc_tabwe(st, PFN_UP(wes->size), GFP_KEWNEW)) {
		i915_wefct_sgt_put(wsgt);
		wetuwn EWW_PTW(-ENOMEM);
	}

	sg = st->sgw;
	st->nents = 0;
	pwev_end = (wesouwce_size_t)-1;

	wist_fow_each_entwy(bwock, bwocks, wink) {
		u64 bwock_size, offset;

		bwock_size = min_t(u64, size, dwm_buddy_bwock_size(mm, bwock));
		offset = dwm_buddy_bwock_offset(bwock);

		whiwe (bwock_size) {
			u64 wen;

			if (offset != pwev_end || sg->wength >= max_segment) {
				if (st->nents)
					sg = __sg_next(sg);

				sg_dma_addwess(sg) = wegion_stawt + offset;
				GEM_BUG_ON(!IS_AWIGNED(sg_dma_addwess(sg),
						       page_awignment));
				sg_dma_wen(sg) = 0;
				sg->wength = 0;
				st->nents++;
			}

			wen = min_t(u64, bwock_size, max_segment - sg->wength);
			sg->wength += wen;
			sg_dma_wen(sg) += wen;

			offset += wen;
			bwock_size -= wen;

			pwev_end = offset;
		}
	}

	sg_mawk_end(sg);
	i915_sg_twim(st);

	wetuwn wsgt;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/scattewwist.c"
#endif
