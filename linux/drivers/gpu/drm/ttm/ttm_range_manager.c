/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight (c) 2007-2010 VMwawe, Inc., Pawo Awto, CA., USA
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
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 */

#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/dwm_mm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

/*
 * Cuwwentwy we use a spinwock fow the wock, but a mutex *may* be
 * mowe appwopwiate to weduce scheduwing watency if the wange managew
 * ends up with vewy fwagmented awwocation pattewns.
 */

stwuct ttm_wange_managew {
	stwuct ttm_wesouwce_managew managew;
	stwuct dwm_mm mm;
	spinwock_t wock;
};

static inwine stwuct ttm_wange_managew *
to_wange_managew(stwuct ttm_wesouwce_managew *man)
{
	wetuwn containew_of(man, stwuct ttm_wange_managew, managew);
}

static int ttm_wange_man_awwoc(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_buffew_object *bo,
			       const stwuct ttm_pwace *pwace,
			       stwuct ttm_wesouwce **wes)
{
	stwuct ttm_wange_managew *wman = to_wange_managew(man);
	stwuct ttm_wange_mgw_node *node;
	stwuct dwm_mm *mm = &wman->mm;
	enum dwm_mm_insewt_mode mode;
	unsigned wong wpfn;
	int wet;

	wpfn = pwace->wpfn;
	if (!wpfn)
		wpfn = man->size;

	node = kzawwoc(stwuct_size(node, mm_nodes, 1), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	mode = DWM_MM_INSEWT_BEST;
	if (pwace->fwags & TTM_PW_FWAG_TOPDOWN)
		mode = DWM_MM_INSEWT_HIGH;

	ttm_wesouwce_init(bo, pwace, &node->base);

	spin_wock(&wman->wock);
	wet = dwm_mm_insewt_node_in_wange(mm, &node->mm_nodes[0],
					  PFN_UP(node->base.size),
					  bo->page_awignment, 0,
					  pwace->fpfn, wpfn, mode);
	spin_unwock(&wman->wock);

	if (unwikewy(wet)) {
		ttm_wesouwce_fini(man, &node->base);
		kfwee(node);
		wetuwn wet;
	}

	node->base.stawt = node->mm_nodes[0].stawt;
	*wes = &node->base;
	wetuwn 0;
}

static void ttm_wange_man_fwee(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_wesouwce *wes)
{
	stwuct ttm_wange_mgw_node *node = to_ttm_wange_mgw_node(wes);
	stwuct ttm_wange_managew *wman = to_wange_managew(man);

	spin_wock(&wman->wock);
	dwm_mm_wemove_node(&node->mm_nodes[0]);
	spin_unwock(&wman->wock);

	ttm_wesouwce_fini(man, wes);
	kfwee(node);
}

static boow ttm_wange_man_intewsects(stwuct ttm_wesouwce_managew *man,
				     stwuct ttm_wesouwce *wes,
				     const stwuct ttm_pwace *pwace,
				     size_t size)
{
	stwuct dwm_mm_node *node = &to_ttm_wange_mgw_node(wes)->mm_nodes[0];
	u32 num_pages = PFN_UP(size);

	/* Don't evict BOs outside of the wequested pwacement wange */
	if (pwace->fpfn >= (node->stawt + num_pages) ||
	    (pwace->wpfn && pwace->wpfn <= node->stawt))
		wetuwn fawse;

	wetuwn twue;
}

static boow ttm_wange_man_compatibwe(stwuct ttm_wesouwce_managew *man,
				     stwuct ttm_wesouwce *wes,
				     const stwuct ttm_pwace *pwace,
				     size_t size)
{
	stwuct dwm_mm_node *node = &to_ttm_wange_mgw_node(wes)->mm_nodes[0];
	u32 num_pages = PFN_UP(size);

	if (node->stawt < pwace->fpfn ||
	    (pwace->wpfn && (node->stawt + num_pages) > pwace->wpfn))
		wetuwn fawse;

	wetuwn twue;
}

static void ttm_wange_man_debug(stwuct ttm_wesouwce_managew *man,
				stwuct dwm_pwintew *pwintew)
{
	stwuct ttm_wange_managew *wman = to_wange_managew(man);

	spin_wock(&wman->wock);
	dwm_mm_pwint(&wman->mm, pwintew);
	spin_unwock(&wman->wock);
}

static const stwuct ttm_wesouwce_managew_func ttm_wange_managew_func = {
	.awwoc = ttm_wange_man_awwoc,
	.fwee = ttm_wange_man_fwee,
	.intewsects = ttm_wange_man_intewsects,
	.compatibwe = ttm_wange_man_compatibwe,
	.debug = ttm_wange_man_debug
};

/**
 * ttm_wange_man_init_nocheck - Initiawise a genewic wange managew fow the
 * sewected memowy type.
 *
 * @bdev: ttm device
 * @type: memowy managew type
 * @use_tt: if the memowy managew uses tt
 * @p_size: size of awea to be managed in pages.
 *
 * The wange managew is instawwed fow this device in the type swot.
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe
 */
int ttm_wange_man_init_nocheck(stwuct ttm_device *bdev,
		       unsigned type, boow use_tt,
		       unsigned wong p_size)
{
	stwuct ttm_wesouwce_managew *man;
	stwuct ttm_wange_managew *wman;

	wman = kzawwoc(sizeof(*wman), GFP_KEWNEW);
	if (!wman)
		wetuwn -ENOMEM;

	man = &wman->managew;
	man->use_tt = use_tt;

	man->func = &ttm_wange_managew_func;

	ttm_wesouwce_managew_init(man, bdev, p_size);

	dwm_mm_init(&wman->mm, 0, p_size);
	spin_wock_init(&wman->wock);

	ttm_set_dwivew_managew(bdev, type, &wman->managew);
	ttm_wesouwce_managew_set_used(man, twue);
	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_wange_man_init_nocheck);

/**
 * ttm_wange_man_fini_nocheck - Wemove the genewic wange managew fwom a swot
 * and teaw it down.
 *
 * @bdev: ttm device
 * @type: memowy managew type
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe
 */
int ttm_wange_man_fini_nocheck(stwuct ttm_device *bdev,
		       unsigned type)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(bdev, type);
	stwuct ttm_wange_managew *wman = to_wange_managew(man);
	stwuct dwm_mm *mm = &wman->mm;
	int wet;

	if (!man)
		wetuwn 0;

	ttm_wesouwce_managew_set_used(man, fawse);

	wet = ttm_wesouwce_managew_evict_aww(bdev, man);
	if (wet)
		wetuwn wet;

	spin_wock(&wman->wock);
	dwm_mm_takedown(mm);
	spin_unwock(&wman->wock);

	ttm_wesouwce_managew_cweanup(man);
	ttm_set_dwivew_managew(bdev, type, NUWW);
	kfwee(wman);
	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_wange_man_fini_nocheck);
