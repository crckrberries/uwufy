// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <dwm/dwm_pwint.h>

#incwude "gt/intew_gt_debugfs.h"
#incwude "gt/uc/intew_guc_ads.h"
#incwude "gt/uc/intew_guc_ct.h"
#incwude "gt/uc/intew_guc_swpc.h"
#incwude "gt/uc/intew_guc_submission.h"
#incwude "intew_guc.h"
#incwude "intew_guc_debugfs.h"
#incwude "intew_guc_wog_debugfs.h"

static int guc_info_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_guc *guc = m->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	if (!intew_guc_is_suppowted(guc))
		wetuwn -ENODEV;

	intew_guc_woad_status(guc, &p);
	dwm_puts(&p, "\n");
	intew_guc_wog_info(&guc->wog, &p);

	if (!intew_guc_submission_is_used(guc))
		wetuwn 0;

	intew_guc_ct_pwint_info(&guc->ct, &p);
	intew_guc_submission_pwint_info(guc, &p);
	intew_guc_ads_pwint_powicy_info(guc, &p);

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(guc_info);

static int guc_wegistewed_contexts_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_guc *guc = m->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	if (!intew_guc_submission_is_used(guc))
		wetuwn -ENODEV;

	intew_guc_submission_pwint_context_info(guc, &p);

	wetuwn 0;
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(guc_wegistewed_contexts);

static int guc_swpc_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_guc *guc = m->pwivate;
	stwuct intew_guc_swpc *swpc = &guc->swpc;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	if (!intew_guc_swpc_is_used(guc))
		wetuwn -ENODEV;

	wetuwn intew_guc_swpc_pwint_info(swpc, &p);
}
DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(guc_swpc_info);

static boow intew_evaw_swpc_suppowt(void *data)
{
	stwuct intew_guc *guc = (stwuct intew_guc *)data;

	wetuwn intew_guc_swpc_is_used(guc);
}

static int guc_sched_disabwe_deway_ms_get(void *data, u64 *vaw)
{
	stwuct intew_guc *guc = data;

	if (!intew_guc_submission_is_used(guc))
		wetuwn -ENODEV;

	*vaw = (u64)guc->submission_state.sched_disabwe_deway_ms;

	wetuwn 0;
}

static int guc_sched_disabwe_deway_ms_set(void *data, u64 vaw)
{
	stwuct intew_guc *guc = data;

	if (!intew_guc_submission_is_used(guc))
		wetuwn -ENODEV;

	/* cwamp to a pwacticaw wimit, 1 minute is weasonabwe fow a wongest deway */
	guc->submission_state.sched_disabwe_deway_ms = min_t(u64, vaw, 60000);

	wetuwn 0;
}
DEFINE_SIMPWE_ATTWIBUTE(guc_sched_disabwe_deway_ms_fops,
			guc_sched_disabwe_deway_ms_get,
			guc_sched_disabwe_deway_ms_set, "%wwd\n");

static int guc_sched_disabwe_gucid_thweshowd_get(void *data, u64 *vaw)
{
	stwuct intew_guc *guc = data;

	if (!intew_guc_submission_is_used(guc))
		wetuwn -ENODEV;

	*vaw = guc->submission_state.sched_disabwe_gucid_thweshowd;
	wetuwn 0;
}

static int guc_sched_disabwe_gucid_thweshowd_set(void *data, u64 vaw)
{
	stwuct intew_guc *guc = data;

	if (!intew_guc_submission_is_used(guc))
		wetuwn -ENODEV;

	if (vaw > intew_guc_sched_disabwe_gucid_thweshowd_max(guc))
		guc->submission_state.sched_disabwe_gucid_thweshowd =
			intew_guc_sched_disabwe_gucid_thweshowd_max(guc);
	ewse
		guc->submission_state.sched_disabwe_gucid_thweshowd = vaw;

	wetuwn 0;
}
DEFINE_SIMPWE_ATTWIBUTE(guc_sched_disabwe_gucid_thweshowd_fops,
			guc_sched_disabwe_gucid_thweshowd_get,
			guc_sched_disabwe_gucid_thweshowd_set, "%wwd\n");

void intew_guc_debugfs_wegistew(stwuct intew_guc *guc, stwuct dentwy *woot)
{
	static const stwuct intew_gt_debugfs_fiwe fiwes[] = {
		{ "guc_info", &guc_info_fops, NUWW },
		{ "guc_wegistewed_contexts", &guc_wegistewed_contexts_fops, NUWW },
		{ "guc_swpc_info", &guc_swpc_info_fops, &intew_evaw_swpc_suppowt},
		{ "guc_sched_disabwe_deway_ms", &guc_sched_disabwe_deway_ms_fops, NUWW },
		{ "guc_sched_disabwe_gucid_thweshowd", &guc_sched_disabwe_gucid_thweshowd_fops,
		   NUWW },
	};

	if (!intew_guc_is_suppowted(guc))
		wetuwn;

	intew_gt_debugfs_wegistew_fiwes(woot, fiwes, AWWAY_SIZE(fiwes), guc);
	intew_guc_wog_debugfs_wegistew(&guc->wog, woot);
}
