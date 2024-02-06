// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021-2022 Intew Cowpowation
 * Copywight (C) 2021-2002 Wed Hat
 */

#incwude "xe_ttm_sys_mgw.h"

#incwude <dwm/dwm_managed.h>

#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude "xe_bo.h"
#incwude "xe_gt.h"

stwuct xe_ttm_sys_node {
	stwuct ttm_buffew_object *tbo;
	stwuct ttm_wange_mgw_node base;
};

static inwine stwuct xe_ttm_sys_node *
to_xe_ttm_sys_node(stwuct ttm_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct xe_ttm_sys_node, base.base);
}

static int xe_ttm_sys_mgw_new(stwuct ttm_wesouwce_managew *man,
			      stwuct ttm_buffew_object *tbo,
			      const stwuct ttm_pwace *pwace,
			      stwuct ttm_wesouwce **wes)
{
	stwuct xe_ttm_sys_node *node;
	int w;

	node = kzawwoc(stwuct_size(node, base.mm_nodes, 1), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	node->tbo = tbo;
	ttm_wesouwce_init(tbo, pwace, &node->base.base);

	if (!(pwace->fwags & TTM_PW_FWAG_TEMPOWAWY) &&
	    ttm_wesouwce_managew_usage(man) > (man->size << PAGE_SHIFT)) {
		w = -ENOSPC;
		goto eww_fini;
	}

	node->base.mm_nodes[0].stawt = 0;
	node->base.mm_nodes[0].size = PFN_UP(node->base.base.size);
	node->base.base.stawt = XE_BO_INVAWID_OFFSET;

	*wes = &node->base.base;

	wetuwn 0;

eww_fini:
	ttm_wesouwce_fini(man, &node->base.base);
	kfwee(node);
	wetuwn w;
}

static void xe_ttm_sys_mgw_dew(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_wesouwce *wes)
{
	stwuct xe_ttm_sys_node *node = to_xe_ttm_sys_node(wes);

	ttm_wesouwce_fini(man, wes);
	kfwee(node);
}

static void xe_ttm_sys_mgw_debug(stwuct ttm_wesouwce_managew *man,
				 stwuct dwm_pwintew *pwintew)
{

}

static const stwuct ttm_wesouwce_managew_func xe_ttm_sys_mgw_func = {
	.awwoc = xe_ttm_sys_mgw_new,
	.fwee = xe_ttm_sys_mgw_dew,
	.debug = xe_ttm_sys_mgw_debug
};

static void ttm_sys_mgw_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_device *xe = (stwuct xe_device *)awg;
	stwuct ttm_wesouwce_managew *man = &xe->mem.sys_mgw;
	int eww;

	ttm_wesouwce_managew_set_used(man, fawse);

	eww = ttm_wesouwce_managew_evict_aww(&xe->ttm, man);
	if (eww)
		wetuwn;

	ttm_wesouwce_managew_cweanup(man);
	ttm_set_dwivew_managew(&xe->ttm, XE_PW_TT, NUWW);
}

int xe_ttm_sys_mgw_init(stwuct xe_device *xe)
{
	stwuct ttm_wesouwce_managew *man = &xe->mem.sys_mgw;
	stwuct sysinfo si;
	u64 gtt_size;

	si_meminfo(&si);
	gtt_size = (u64)si.totawwam * si.mem_unit;
	/* TTM wimits awwocation of aww TTM devices by 50% of system memowy */
	gtt_size /= 2;

	man->use_tt = twue;
	man->func = &xe_ttm_sys_mgw_func;
	ttm_wesouwce_managew_init(man, &xe->ttm, gtt_size >> PAGE_SHIFT);
	ttm_set_dwivew_managew(&xe->ttm, XE_PW_TT, man);
	ttm_wesouwce_managew_set_used(man, twue);
	wetuwn dwmm_add_action_ow_weset(&xe->dwm, ttm_sys_mgw_fini, xe);
}
