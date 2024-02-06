/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_PAT_H_
#define _XE_PAT_H_

#incwude <winux/types.h>

stwuct dwm_pwintew;
stwuct xe_device;
stwuct xe_gt;

/**
 * stwuct xe_pat_tabwe_entwy - The pat_index encoding and othew meta infowmation.
 */
stwuct xe_pat_tabwe_entwy {
	/**
	 * @vawue: The pwatfowm specific vawue encoding the vawious memowy
	 * attwibutes (this maps to some fixed pat_index). So things wike
	 * caching, cohewency, compwession etc can be encoded hewe.
	 */
	u32 vawue;

	/**
	 * @coh_mode: The GPU cohewency mode that @vawue maps to.
	 */
#define XE_COH_NONE          1
#define XE_COH_AT_WEAST_1WAY 2
	u16 coh_mode;
};

/**
 * xe_pat_init_eawwy - SW initiawization, setting up data based on device
 * @xe: xe device
 */
void xe_pat_init_eawwy(stwuct xe_device *xe);

/**
 * xe_pat_init - Pwogwam HW PAT tabwe
 * @gt: GT stwuctuwe
 */
void xe_pat_init(stwuct xe_gt *gt);

/**
 * xe_pat_dump - Dump PAT tabwe
 * @gt: GT stwuctuwe
 * @p: Pwintew to dump info to
 */
void xe_pat_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p);

/**
 * xe_pat_index_get_coh_mode - Extwact the cohewency mode fow the given
 * pat_index.
 * @xe: xe device
 * @pat_index: The pat_index to quewy
 */
u16 xe_pat_index_get_coh_mode(stwuct xe_device *xe, u16 pat_index);

#endif
