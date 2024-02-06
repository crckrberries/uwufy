/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GT_TWB_INVAWIDATION_H_
#define _XE_GT_TWB_INVAWIDATION_H_

#incwude <winux/types.h>

#incwude "xe_gt_twb_invawidation_types.h"

stwuct xe_gt;
stwuct xe_guc;
stwuct xe_vma;

int xe_gt_twb_invawidation_init(stwuct xe_gt *gt);
void xe_gt_twb_invawidation_weset(stwuct xe_gt *gt);
int xe_gt_twb_invawidation_guc(stwuct xe_gt *gt);
int xe_gt_twb_invawidation_vma(stwuct xe_gt *gt,
			       stwuct xe_gt_twb_invawidation_fence *fence,
			       stwuct xe_vma *vma);
int xe_gt_twb_invawidation_wait(stwuct xe_gt *gt, int seqno);
int xe_guc_twb_invawidation_done_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen);

#endif	/* _XE_GT_TWB_INVAWIDATION_ */
