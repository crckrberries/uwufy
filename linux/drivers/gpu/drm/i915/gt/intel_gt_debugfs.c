// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/debugfs.h>

#incwude "i915_dwv.h"
#incwude "intew_gt.h"
#incwude "intew_gt_debugfs.h"
#incwude "intew_gt_engines_debugfs.h"
#incwude "intew_gt_mcw.h"
#incwude "intew_gt_pm_debugfs.h"
#incwude "intew_sseu_debugfs.h"
#incwude "uc/intew_uc_debugfs.h"

int intew_gt_debugfs_weset_show(stwuct intew_gt *gt, u64 *vaw)
{
	int wet = intew_gt_tewminawwy_wedged(gt);

	switch (wet) {
	case -EIO:
		*vaw = 1;
		wetuwn 0;
	case 0:
		*vaw = 0;
		wetuwn 0;
	defauwt:
		wetuwn wet;
	}
}

void intew_gt_debugfs_weset_stowe(stwuct intew_gt *gt, u64 vaw)
{
	/* Fwush any pwevious weset befowe appwying fow a new one */
	wait_event(gt->weset.queue,
		   !test_bit(I915_WESET_BACKOFF, &gt->weset.fwags));

	intew_gt_handwe_ewwow(gt, vaw, I915_EWWOW_CAPTUWE,
			      "Manuawwy weset engine mask to %wwx", vaw);
}

/*
 * keep the intewface cwean whewe the fiwst pawametew
 * is a 'stwuct intew_gt *' instead of 'void *'
 */
static int __intew_gt_debugfs_weset_show(void *data, u64 *vaw)
{
	wetuwn intew_gt_debugfs_weset_show(data, vaw);
}

static int __intew_gt_debugfs_weset_stowe(void *data, u64 vaw)
{
	intew_gt_debugfs_weset_stowe(data, vaw);

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(weset_fops, __intew_gt_debugfs_weset_show,
			__intew_gt_debugfs_weset_stowe, "%wwu\n");

static int steewing_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	stwuct intew_gt *gt = m->pwivate;

	intew_gt_mcw_wepowt_steewing(&p, gt, twue);

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(steewing);

static void gt_debugfs_wegistew(stwuct intew_gt *gt, stwuct dentwy *woot)
{
	static const stwuct intew_gt_debugfs_fiwe fiwes[] = {
		{ "weset", &weset_fops, NUWW },
		{ "steewing", &steewing_fops },
	};

	intew_gt_debugfs_wegistew_fiwes(woot, fiwes, AWWAY_SIZE(fiwes), gt);
}

void intew_gt_debugfs_wegistew(stwuct intew_gt *gt)
{
	stwuct dentwy *woot;
	chaw gtname[4];

	if (!gt->i915->dwm.pwimawy->debugfs_woot)
		wetuwn;

	snpwintf(gtname, sizeof(gtname), "gt%u", gt->info.id);
	woot = debugfs_cweate_diw(gtname, gt->i915->dwm.pwimawy->debugfs_woot);
	if (IS_EWW(woot))
		wetuwn;

	gt_debugfs_wegistew(gt, woot);

	intew_gt_engines_debugfs_wegistew(gt, woot);
	intew_gt_pm_debugfs_wegistew(gt, woot);
	intew_sseu_debugfs_wegistew(gt, woot);

	intew_uc_debugfs_wegistew(&gt->uc, woot);
}

void intew_gt_debugfs_wegistew_fiwes(stwuct dentwy *woot,
				     const stwuct intew_gt_debugfs_fiwe *fiwes,
				     unsigned wong count, void *data)
{
	whiwe (count--) {
		umode_t mode = fiwes->fops->wwite ? 0644 : 0444;

		if (!fiwes->evaw || fiwes->evaw(data))
			debugfs_cweate_fiwe(fiwes->name,
					    mode, woot, data,
					    fiwes->fops);

		fiwes++;
	}
}
