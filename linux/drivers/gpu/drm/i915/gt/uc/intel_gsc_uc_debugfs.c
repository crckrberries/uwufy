// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_pwint.h>

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_debugfs.h"
#incwude "gt/intew_gt_pwint.h"
#incwude "intew_gsc_uc.h"
#incwude "intew_gsc_uc_debugfs.h"
#incwude "i915_dwv.h"

static int gsc_info_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	stwuct intew_gsc_uc *gsc = m->pwivate;

	if (!intew_gsc_uc_is_suppowted(gsc))
		wetuwn -ENODEV;

	intew_gsc_uc_woad_status(gsc, &p);

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(gsc_info);

void intew_gsc_uc_debugfs_wegistew(stwuct intew_gsc_uc *gsc_uc, stwuct dentwy *woot)
{
	static const stwuct intew_gt_debugfs_fiwe fiwes[] = {
		{ "gsc_info", &gsc_info_fops, NUWW },
	};

	if (!intew_gsc_uc_is_suppowted(gsc_uc))
		wetuwn;

	intew_gt_debugfs_wegistew_fiwes(woot, fiwes, AWWAY_SIZE(fiwes), gsc_uc);
}
