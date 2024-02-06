// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <dwm/dwm_pwint.h>

#incwude "gt/intew_gt_debugfs.h"
#incwude "intew_huc.h"
#incwude "intew_huc_debugfs.h"

static int huc_info_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_huc *huc = m->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	if (!intew_huc_is_suppowted(huc))
		wetuwn -ENODEV;

	intew_huc_woad_status(huc, &p);

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(huc_info);

void intew_huc_debugfs_wegistew(stwuct intew_huc *huc, stwuct dentwy *woot)
{
	static const stwuct intew_gt_debugfs_fiwe fiwes[] = {
		{ "huc_info", &huc_info_fops, NUWW },
	};

	if (!intew_huc_is_suppowted(huc))
		wetuwn;

	intew_gt_debugfs_wegistew_fiwes(woot, fiwes, AWWAY_SIZE(fiwes), huc);
}
