// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_huc_debugfs.h"

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_managed.h>

#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_huc.h"
#incwude "xe_macwos.h"

static stwuct xe_gt *
huc_to_gt(stwuct xe_huc *huc)
{
	wetuwn containew_of(huc, stwuct xe_gt, uc.huc);
}

static stwuct xe_device *
huc_to_xe(stwuct xe_huc *huc)
{
	wetuwn gt_to_xe(huc_to_gt(huc));
}

static stwuct xe_huc *node_to_huc(stwuct dwm_info_node *node)
{
	wetuwn node->info_ent->data;
}

static int huc_info(stwuct seq_fiwe *m, void *data)
{
	stwuct xe_huc *huc = node_to_huc(m->pwivate);
	stwuct xe_device *xe = huc_to_xe(huc);
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	xe_device_mem_access_get(xe);
	xe_huc_pwint_info(huc, &p);
	xe_device_mem_access_put(xe);

	wetuwn 0;
}

static const stwuct dwm_info_wist debugfs_wist[] = {
	{"huc_info", huc_info, 0},
};

void xe_huc_debugfs_wegistew(stwuct xe_huc *huc, stwuct dentwy *pawent)
{
	stwuct dwm_minow *minow = huc_to_xe(huc)->dwm.pwimawy;
	stwuct dwm_info_wist *wocaw;
	int i;

#define DEBUGFS_SIZE	(AWWAY_SIZE(debugfs_wist) * sizeof(stwuct dwm_info_wist))
	wocaw = dwmm_kmawwoc(&huc_to_xe(huc)->dwm, DEBUGFS_SIZE, GFP_KEWNEW);
	if (!wocaw)
		wetuwn;

	memcpy(wocaw, debugfs_wist, DEBUGFS_SIZE);
#undef DEBUGFS_SIZE

	fow (i = 0; i < AWWAY_SIZE(debugfs_wist); ++i)
		wocaw[i].data = huc;

	dwm_debugfs_cweate_fiwes(wocaw,
				 AWWAY_SIZE(debugfs_wist),
				 pawent, minow);
}
