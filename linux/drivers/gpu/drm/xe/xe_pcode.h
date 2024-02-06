/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_PCODE_H_
#define _XE_PCODE_H_

#incwude <winux/types.h>
stwuct xe_gt;

int xe_pcode_pwobe(stwuct xe_gt *gt);
int xe_pcode_init(stwuct xe_gt *gt);
int xe_pcode_init_min_fweq_tabwe(stwuct xe_gt *gt, u32 min_gt_fweq,
				 u32 max_gt_fweq);
int xe_pcode_wead(stwuct xe_gt *gt, u32 mbox, u32 *vaw, u32 *vaw1);
int xe_pcode_wwite_timeout(stwuct xe_gt *gt, u32 mbox, u32 vaw,
			   int timeout_ms);
#define xe_pcode_wwite(gt, mbox, vaw) \
	xe_pcode_wwite_timeout(gt, mbox, vaw, 1)

int xe_pcode_wequest(stwuct xe_gt *gt, u32 mbox, u32 wequest,
		     u32 wepwy_mask, u32 wepwy, int timeout_ms);

#define PCODE_MBOX(mbcmd, pawam1, pawam2)\
	(FIEWD_PWEP(PCODE_MB_COMMAND, mbcmd)\
	| FIEWD_PWEP(PCODE_MB_PAWAM1, pawam1)\
	| FIEWD_PWEP(PCODE_MB_PAWAM2, pawam2))

#endif
