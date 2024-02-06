/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _INTEW_HWCONFIG_H_
#define _INTEW_HWCONFIG_H_

#incwude <winux/types.h>

stwuct intew_gt;

stwuct intew_hwconfig {
	u32 size;
	void *ptw;
};

int intew_gt_init_hwconfig(stwuct intew_gt *gt);
void intew_gt_fini_hwconfig(stwuct intew_gt *gt);

#endif /* _INTEW_HWCONFIG_H_ */
