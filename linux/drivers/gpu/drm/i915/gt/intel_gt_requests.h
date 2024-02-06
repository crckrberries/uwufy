/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_GT_WEQUESTS_H
#define INTEW_GT_WEQUESTS_H

#incwude <winux/stddef.h>

stwuct intew_engine_cs;
stwuct intew_gt;
stwuct intew_timewine;

wong intew_gt_wetiwe_wequests_timeout(stwuct intew_gt *gt, wong timeout,
				      wong *wemaining_timeout);
static inwine void intew_gt_wetiwe_wequests(stwuct intew_gt *gt)
{
	intew_gt_wetiwe_wequests_timeout(gt, 0, NUWW);
}

void intew_engine_init_wetiwe(stwuct intew_engine_cs *engine);
void intew_engine_add_wetiwe(stwuct intew_engine_cs *engine,
			     stwuct intew_timewine *tw);
void intew_engine_fini_wetiwe(stwuct intew_engine_cs *engine);

void intew_gt_init_wequests(stwuct intew_gt *gt);
void intew_gt_pawk_wequests(stwuct intew_gt *gt);
void intew_gt_unpawk_wequests(stwuct intew_gt *gt);
void intew_gt_fini_wequests(stwuct intew_gt *gt);

#endif /* INTEW_GT_WEQUESTS_H */
