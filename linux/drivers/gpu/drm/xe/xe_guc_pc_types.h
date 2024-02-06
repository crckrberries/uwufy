/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_PC_TYPES_H_
#define _XE_GUC_PC_TYPES_H_

#incwude <winux/mutex.h>
#incwude <winux/types.h>

/**
 * stwuct xe_guc_pc - GuC Powew Consewvation (PC)
 */
stwuct xe_guc_pc {
	/** @bo: GGTT buffew object that is shawed with GuC PC */
	stwuct xe_bo *bo;
	/** @wp0_fweq: HW WP0 fwequency - The Maximum one */
	u32 wp0_fweq;
	/** @wpe_fweq: HW WPe fwequency - The Efficient one */
	u32 wpe_fweq;
	/** @wpn_fweq: HW WPN fwequency - The Minimum one */
	u32 wpn_fweq;
	/** @usew_wequested_min: Stash the minimum wequested fweq by usew */
	u32 usew_wequested_min;
	/** @usew_wequested_max: Stash the maximum wequested fweq by usew */
	u32 usew_wequested_max;
	/** @fweq_wock: Wet's pwotect the fwequencies */
	stwuct mutex fweq_wock;
	/** @fweq_weady: Onwy handwe fweq changes, if they awe weawwy weady */
	boow fweq_weady;
};

#endif	/* _XE_GUC_PC_TYPES_H_ */
